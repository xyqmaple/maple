/**
 * @file msc.c
 * @author yeqiang_xu <yeqiang_xu@maxio-tech.com>
 * @brief Driver for USB Mass Sotrage compliant devices
 * @version 0.1
 * @date 2022-08-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "defs.h"
#include "log.h"
#include "byteorder/generic.h"
#include "scsi/scsi_proto.h"
#include "msc.h"

static u32 g_cmd_tag = 0;

static struct msc_device *g_msc_dev = NULL;

struct scsi_cmnd *msc_alloc_cmnd(size_t len)
{
	struct scsi_cmnd *srb = NULL;

	srb = calloc(1, sizeof(*srb));
	if (!srb) {
		pr_err("failed to alloc cmnd!\n");
		return NULL;
	}
	
	if (!len)
		return srb;

	srb->data_buf = calloc(1, len);
	if (!srb->data_buf) {
		pr_err("failed to alloc buf(%lu)!\n", len);
		goto out;
	}
	srb->buf_len = len;
	/*
	 * The default data transfer size is the same as the buffer size and
	 * you can adjust it outside as needed.
	 */
	srb->xfer_len = len;
	return srb;
out:
	free(srb);
	return NULL;
}

void msc_free_cmnd(struct scsi_cmnd *srb)
{
	if (!srb)
		return;
	
	free(srb->data_buf);
	free(srb);
}

static const char *scsi_opcode_name(u8 code)
{
	switch (code) {
	case INQUIRY:
		return "INQUIRY";
	case MODE_SELECT:
		return "MODE SELECT(6)";
	case MODE_SELECT_10:
		return "MODE SELECT(10)";
	case MODE_SENSE:
		return "MODE SENSE(6)";
	case MODE_SENSE_10:
		return "MODE SENSE(10)";
	case ALLOW_MEDIUM_REMOVAL:
		return "PREVENT-ALLOW MEDIUM REMOVAL";
	case READ_6:
		return "READ(6)";
	case READ_10:
		return "READ(10)";
	case READ_12:
		return "READ(12)";
	case READ_CAPACITY:
		return "READ CAPACITY";
	case READ_HEADER:
		return "READ HEADER";
	case READ_TOC:
		return "READ TOC";
	case READ_FORMAT_CAPACITIES:
		return "READ FORMAT CAPACITIES";
	case REQUEST_SENSE:
		return "REQUEST SENSE";
	case START_STOP:
		return "START-STOP UNIT";
	case SYNCHRONIZE_CACHE:
		return "SYNCHRONIZE CACHE";
	case TEST_UNIT_READY:
		return "TEST UNIT READY";
	case VERIFY:
		return "VERIFY";
	case WRITE_6:
		return "WRITE(6)";
	case WRITE_10:
		return "WRITE(10)";
	case WRITE_12:
		return "WRITE(12)";
	default:
		return "UNKNOWN";
	}
}

static int msc_check_cmnd(struct scsi_cmnd *srb)
{
	if (srb->cmd_len > US_BULK_CB_MAX_LEN) {
		pr_err("cmd len(%u) over limit!\n", srb->cmd_len);
		return -EINVAL;
	}
	pr_debug("SCSI command: %s\n", scsi_opcode_name(srb->cmnd[0]));

	if (srb->xfer_len > srb->buf_len) {
		pr_err("The size of data transffered(%u) exceeds "
			"the buffer(%u)!\n", srb->xfer_len, srb->buf_len);
		return -EINVAL;
	}
	return 0;
}

/**
 * @brief Send command block wrapper
 * 
 * @param handle 
 * @param srb 
 * @return The length of received data on success. Otherwise, a negative errno.
 */
static int msc_bot_cbw_stage(libusb_device_handle *handle, struct scsi_cmnd *srb)
{
	int ret;
	int act_len;
	struct msc_group *grp = &g_msc_dev->grp[g_msc_dev->grp_act];
	struct bulk_cb_wrap cbw;

	memset(&cbw, 0, sizeof(cbw));
	cbw.Signature = cpu_to_le32(US_BULK_CB_SIGN);
	cbw.Tag = ++g_cmd_tag;
	cbw.DataTransferLength = cpu_to_le32(srb->xfer_len);
	cbw.Flags = srb->direction;
	cbw.Lun = srb->lun;
	cbw.Length = srb->cmd_len;
	memcpy(cbw.CDB, srb->cmnd, cbw.Length);

	ret = libusb_bulk_transfer(handle, grp->ep_out, (u8 *)&cbw, 
		US_BULK_CB_WRAP_LEN, &act_len, MSC_BULK_XFER_TIMEOUT);
	if (ret < 0) {
		pr_err("failed to send CBW: %s!\n", libusb_error_name(ret));
		return -EIO;
	}

	return act_len;
}

/**
 * @brief Transfer data
 * 
 * @param handle 
 * @param srb 
 * @return The length of received data on success. Otherwise, a negative errno. 
 */
static int msc_bot_data_stage(libusb_device_handle *handle, struct scsi_cmnd *srb)
{
	int ret;
	int act_len;
	struct msc_group *grp = &g_msc_dev->grp[g_msc_dev->grp_act];
	u8 ep = srb->direction ? grp->ep_in : grp->ep_out;

	if (!srb->xfer_len) /* skip */
		return 0;

	ret = libusb_bulk_transfer(handle, ep, srb->data_buf, srb->xfer_len,
		&act_len, MSC_BULK_XFER_TIMEOUT);
	if (ret < 0) {
		pr_err("failed to transfer data: %s!\n", libusb_error_name(ret));
		return -EIO;
	}

	return act_len;
}

/**
 * @brief Receive command status wrapper
 * 
 * @param handle 
 * @param srb 
 * @return The length of received data on success. Otherwise, a negative errno.
 */
static int msc_bot_csw_stage(libusb_device_handle *handle, struct scsi_cmnd *srb)
{
	int ret;
	int act_len;
	struct msc_group *grp = &g_msc_dev->grp[g_msc_dev->grp_act];
	struct bulk_cs_wrap csw;

	ret = libusb_bulk_transfer(handle, grp->ep_in, (u8 *)&csw, 
		US_BULK_CS_WRAP_LEN, &act_len, MSC_BULK_XFER_TIMEOUT);
	if (ret < 0) {
		pr_err("failed to recv CSW: %s!\n", libusb_error_name(ret));
		return -EIO;
	}

	if (US_BULK_CS_SIGN != le32_to_cpu(csw.Signature)) {
		pr_err("failed to verify CSW Signature(0x%x)!\n", 
			le32_to_cpu(csw.Signature));
		return -EAGAIN;
	}

	if (csw.Tag != g_cmd_tag) {
		pr_err("failed to verify CSW Tag!(Except:0x%x, Receive:0x%x)\n",
			g_cmd_tag, csw.Tag);
		return -EAGAIN;
	}

	if (csw.Status != US_BULK_STAT_OK) {
		pr_err("failed to verify CSW Status(%u)!\n", csw.Status);
		return -EAGAIN;
	}

	return act_len;
}

int msc_submit_cmnd(libusb_device_handle *handle, struct scsi_cmnd *srb)
{
	int ret;

	ret = msc_check_cmnd(srb);
	if (ret < 0)
		return ret;

	ret = msc_bot_cbw_stage(handle, srb);
	if (ret < 0)
		return ret;
	
	ret = msc_bot_data_stage(handle, srb);
	if (ret < 0)
		return ret;

	ret = msc_bot_csw_stage(handle, srb);
	if (ret < 0)
		return ret;

	return 0;
}

int msc_test_unit_ready(libusb_device_handle *handle, u8 lun)
{
	int ret;
	struct scsi_cmnd *srb;

	srb = msc_alloc_cmnd(0);
	if (!srb)
		return -ENOMEM;

	srb->direction = US_BULK_FLAG_OUT;
	srb->lun = lun;
	srb->cmd_len = 6;
	srb->cmnd[0] = TEST_UNIT_READY;

	ret = msc_submit_cmnd(handle, srb);
	if (ret < 0)
		goto out;

	pr_info("TEST_UNIT_READY OK!\n");
out:
	msc_free_cmnd(srb);
	return ret;
}

int msc_select_active_group(struct msc_device *msc, u8 grp_idx)
{
	if (grp_idx >= msc->grp_num) {
		pr_err("grp_idx(%u) shall less than %u!\n", grp_idx, msc->grp_num);
		return -EINVAL;
	}

	msc->grp_act = grp_idx;
	return 0;
}

static int msc_init_group(struct msc_device *msc)
{
	int i, j, k;
	struct usbdev_wrap *devwrap = msc->devwrap;
	struct libusb_config_descriptor *cfg_desc = devwrap->cfg_desc;
	const struct libusb_endpoint_descriptor *ep_desc;
	int nb_ifaces, nb_alts, nb_eps;
	u8 nb_epin = 0, nb_epout = 0;

	nb_ifaces = cfg_desc->bNumInterfaces;

	for (i = 0; i < nb_ifaces; i++) {
		pr_debug("\tinterface[%d]: id = %d\n", i, 
			cfg_desc->interface[i].altsetting[0].bInterfaceNumber);

		nb_alts = cfg_desc->interface[i].num_altsetting;
		
		for (j = 0; j < nb_alts; j++) {
			nb_eps = cfg_desc->interface[i].altsetting[j].bNumEndpoints;

			pr_debug("\tinterface[%d].altsetting[%d]: num endpoints = %d\n",
				i, j, nb_eps);
			
			for (k = 0; k < nb_eps; k++) {
				ep_desc = &cfg_desc->interface[i].altsetting[j].endpoint[k];

				pr_debug("\tendpoint[%d].address: 0x%02x\n", k, ep_desc->bEndpointAddress);

				if ((ep_desc->bmAttributes & LIBUSB_TRANSFER_TYPE_MASK) & LIBUSB_TRANSFER_TYPE_BULK) {
					if (ep_desc->bEndpointAddress & LIBUSB_ENDPOINT_IN) {
						if (nb_epin < MSC_GROUP_MAX_NUM)
							msc->grp[nb_epin++].ep_in = ep_desc->bEndpointAddress;
						else
							pr_warn("epin number > %d\n", MSC_GROUP_MAX_NUM);
					} else {
						if (nb_epout < MSC_GROUP_MAX_NUM)
							msc->grp[nb_epout++].ep_out = ep_desc->bEndpointAddress;
						else
							pr_warn("epout number > %d\n", MSC_GROUP_MAX_NUM);
					}
				}
			}
		}
	}

	msc->grp_num = min(nb_epin, nb_epout);

	if (!msc->grp_num) {
		pr_err("failed to find groups!\n");
		return -ENODEV;
	}

	pr_info("found %u groups!\n", msc->grp_num);
	for (i = 0; i < msc->grp_num; i++) {
		pr_debug("\tepout:0x%02x, epin:0x%02x\n", msc->grp[i].ep_out, 
			msc->grp[i].ep_in);
	}
	return 0;
}

int msc_init(struct usbdev_wrap *devwrap)
{
	int ret;
	int i;
	struct msc_device *msc = NULL;
	libusb_device_handle *handle = devwrap->handle;
	struct libusb_config_descriptor *cfg_desc = devwrap->cfg_desc;
	int nb_ifaces;

	if (g_msc_dev) {
		pr_warn("msc device already exist!\n");
		return 0;
	}

	msc = calloc(1, sizeof(*msc));
	if (!msc) {
		pr_err("failed to alloc msc device!\n");
		return -ENOMEM;
	}
	g_msc_dev = msc;
	g_msc_dev->devwrap = devwrap;

	ret = msc_init_group(msc);
	if (ret < 0)
		return ret;

	ret = libusb_set_auto_detach_kernel_driver(handle, 1);
	if (ret < 0) {
		pr_err("failed to detach kernel driver: %s!\n", libusb_error_name(ret));
		goto out;
	}
	nb_ifaces = cfg_desc->bNumInterfaces;

	for (i = 0; i < nb_ifaces; i++) {
		ret = libusb_kernel_driver_active(handle, i);
		pr_notice("Kernel driver attached for interface %d: %d\n", i, ret);
		pr_notice("Claiming interface %d...\n", i);
		ret = libusb_claim_interface(handle, i);
		if (ret < 0) {
			pr_err("ERR: %s\n", libusb_error_name(ret));
			goto out;
		}
	}

	devwrap->msc = g_msc_dev;

	pr_info("init msc device ok!\n");
	return 0;
out:
	free(g_msc_dev);
	g_msc_dev = NULL;
	return ret;
}

void msc_exit(struct msc_device *msc)
{
	if (!g_msc_dev)
		return;

	if (msc != g_msc_dev) {
		pr_warn("ptr(0x%p) mismatch to msc device(0x%p)!\n", 
			msc, g_msc_dev);
		return;
	}

	free(g_msc_dev);
	g_msc_dev = NULL;
	pr_info("deinit msc device ok!\n");
}
