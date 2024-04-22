/**
 * @file msc.h
 * @author yeqiang_xu <yeqiang_xu@maxio-tech.com>
 * @brief  Driver for USB Mass Sotrage compliant devices Header File
 * @version 0.1
 * @date 2022-08-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _USB_MSC_H_
#define _USB_MSC_H_

#include "types.h"
#include "usb/storage.h"
#include "libusb.h"
#include "core.h"

#define MSC_BULK_XFER_TIMEOUT		5000
#define MSC_GROUP_MAX_NUM		16

/**
 * @data_buf: Buffer for storing sending or receiving data.
 * @buf_len: The size of @data_buf.
 * @xfer_len: The length of data expected to be transmitted(send/receive)
 * @act_len: The length of data actually transmiteed(send/receive)
 */
struct scsi_cmnd {
	u8		direction;
	u8		lun;
	u8		cmd_len;
	u8		cmnd[US_BULK_CB_MAX_LEN];

	void		*data_buf;
	u32		buf_len;
	u32		xfer_len;
	u32		act_len;
};

struct msc_group {
	u8		ep_in;
	u8		ep_out;
};

struct msc_device {
	u8			grp_num;
	u8			grp_act; /* active */
	struct msc_group	grp[MSC_GROUP_MAX_NUM];

	struct usbdev_wrap	*devwrap;
};

struct scsi_cmnd *msc_alloc_cmnd(size_t len);
void msc_free_cmnd(struct scsi_cmnd *srb);

int msc_submit_cmnd(libusb_device_handle *handle, struct scsi_cmnd *srb);

int msc_test_unit_ready(libusb_device_handle *handle, u8 lun);

int msc_init(struct usbdev_wrap *dev);
void msc_exit(struct msc_device *msc);

#endif /* !_USB_MSC_H_ */
