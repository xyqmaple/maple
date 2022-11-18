/**
 * @file core.c
 * @author yeqiang_xu <yeqiang_xu@maxio-tech.com>
 * @brief 
 * @version 0.1
 * @date 2022-08-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <errno.h>

#include "defs.h"
#include "log.h"
#include "core.h"
#include "debug.h"
#include "message.h"
#include "msc.h"
#include "video.h"

#define INIT_CMD(_name, _cmd_exec) \
	{ .name = _name, .cmd_exec = _cmd_exec, .flag = 0 }
#define INIT_CMD_FLAG(_name, _cmd_exec, _flag) \
	{ .name = _name, .cmd_exec = _cmd_exec, .flag = _flag }

static int usbtool_cmd_list_dev(struct usbtool *tool);
static int usbtool_cmd_list_devs(struct usbtool *tool);
static int usbtool_cmd_get_desc(struct usbtool *tool);
static int usbtool_cmd_msc_set(struct usbtool *tool);
static int usbtool_cmd_uvc_capture(struct usbtool *tool);
static int usbtool_cmd_custom(struct usbtool *tool);

static struct usbtool *g_usbtool;

static struct option g_longopts[] = {
	{"CMD",		required_argument,	0,	'C'},
	{"help",	no_argument,		0,	'h'},
	{"PID",		required_argument,	0,	'P'},
	{"VID",		required_argument,	0,	'V'},
	{0,		0,			0,	0},
};

static const char *g_optstring = "C:hP:V:";

static struct usr_cmd_ops g_cmd_ops[] = {
	[USR_CMD_LIST_DEV] = INIT_CMD("list_dev", usbtool_cmd_list_dev),
	[USR_CMD_LIST_DEVS] = INIT_CMD("list_devs", usbtool_cmd_list_devs),
	[USR_CMD_GET_DESC] = INIT_CMD("get_desc", usbtool_cmd_get_desc),
	[USR_CMD_MSC_SET] = INIT_CMD_FLAG("msc_set", usbtool_cmd_msc_set,
		USR_CMD_BIND_FUNC),
	[USR_CMD_UVC_CAP] = INIT_CMD("uvc_cap", usbtool_cmd_uvc_capture),
	[USR_CMD_CUSTOM] = INIT_CMD_FLAG("custom", usbtool_cmd_custom, 
		USR_CMD_BIND_FUNC),
	[USR_CMD_MAX] = INIT_CMD(NULL, NULL),
};

static void usage_usr_command(void)
{
	int i;
	pr_debug("\t\tSelect a command from the following parameters: ");

	for (i = 0; g_cmd_ops[i].name; i++) {
		printf("%s ", g_cmd_ops[i].name);
	}
	printf("\n");
}

static void usage(const char *name)
{
	pr_notice("SYNOPSIS\n");
	pr_debug("\t%s [<options>]\n", name);

	pr_notice("OPTIONS\n");
	pr_debug("\t-C <Command>, --CMD=<Command>\n");
	usage_usr_command();

	pr_debug("\t-h, --help\n");
	pr_debug("\t-P <ProductID>, --PID=<ProductID>\n");
	pr_debug("\t-V <VendorID>, --VID=<VendorID>\n");
}

static int parse_usr_command(const char *cmd)
{
	int i;
	int ret;

	for (i = 0; g_cmd_ops[i].name; i++) {
		ret = strcmp(g_cmd_ops[i].name, cmd);
		if (0 == ret)
			return i;
	}

	return USR_CMD_INVALID;
}

static int parse_usr_param(struct usr_param *param, int argc, char *argv[])
{
	int c;
	int option_index = 0;

	while (1) {
		c = getopt_long(argc, argv, g_optstring, g_longopts, &option_index);
		if (c == -1)
			break;

		switch (c) {
		case 'C':
			param->cmd = parse_usr_command(optarg);
			break;

		case 'h':
			goto out;

		case 'P':
			param->pid = strtol(optarg, NULL, 0);
			break;
		
		case 'V':
			param->vid = strtol(optarg, NULL, 0);
			break;
		
		default:
			pr_err("Character '%c' is not support!\n", c);
			goto out;
		}
	}
	pr_div("VID:0x%x, PID:0x%x\n", param->vid, param->pid);
	return 0;
out:
	usage(argv[0]);
	return -EINVAL;
}

static int usbtool_cmd_list_dev(struct usbtool *tool)
{
	return 0;
}

static int usbtool_cmd_list_devs(struct usbtool *tool)
{
	int ret;
	int i = 0, j = 0;
	struct libusb_device **devs = tool->devwrap.dev_list;
	struct libusb_device *dev;
	struct libusb_device_descriptor desc;
	u8 path[8];

	for (dev = devs[i++]; dev; dev = devs[i++]) {
		ret = libusb_get_device_descriptor(dev, &desc);
		if (ret < 0) {
			pr_err("failed to get device descriptor!(%d)\n", ret);
			return ret;
		}

		pr_debug("0x%04x:0x%04x (bus %d, device %d)", 
			desc.idVendor, desc.idProduct,
			libusb_get_bus_number(dev), libusb_get_device_address(dev));

		ret = libusb_get_port_numbers(dev, path, sizeof(path));
		if (ret > 0) {
			printf(" path: %d", path[0]);
			for (j = 1; j < ret; j++)
				printf(".%d", path[j]);
		}
		printf("\n");
	}
	return 0;
}

static int usbtool_cmd_get_desc(struct usbtool *tool)
{
	struct libusb_device_descriptor *dev_desc;
	libusb_device_handle *handle = tool->devwrap.handle;

	dev_desc = usb_get_device_descriptor(handle);
	if (!dev_desc)
		return -EIO;

	usb_print_device_descriptor(dev_desc);
	usb_put_device_descriptor(dev_desc);
	return 0;
}

static int usbtool_cmd_msc_set(struct usbtool *tool)
{
	int i;
	libusb_device_handle *handle = tool->devwrap.handle;
	struct msc_device *msc = tool->devwrap.msc;

	// usb_get_configruation(handle);
	// usb_get_interface(handle, 0);
	// usb_get_device_status(handle);
	// usb_set_endpoint_halt(handle, msc->grp[0].ep_out);
	// usb_clear_endpoint_halt(handle, msc->grp[0].ep_out);
	// usb_set_interface(handle, 0, 0);

	for (i = 0; i < msc->grp_num; i++) {
		msc->grp_act = i;
		msc_test_unit_ready(handle, 0);
	}

	return 0;
}

static int usbtool_cmd_uvc_capture(struct usbtool *tool)
{
	int ret;
	struct video_device *video = NULL;

	ret = video_init(&tool->devwrap);
	if (ret < 0)
		return ret;

	video = tool->devwrap.video;

	ret = video_start(video);
	if (ret < 0)
		goto out;

	sleep(5);
	video_stop(video);
out:
	video_exit(tool->devwrap.video);
	return ret;
}

static int usbtool_cmd_custom(struct usbtool *tool)
{
	return 0;
}

static int usb_bind_function(struct usbdev_wrap *wrap, u8 cfg, u8 intf, u8 alt)
{
	int ret = -EIO;
	struct libusb_device_descriptor *dev_desc;
	struct libusb_config_descriptor *cfg_desc;
	const struct libusb_interface *interface;
	const struct libusb_interface_descriptor *intf_desc;
	libusb_device_handle *handle = wrap->handle;

	dev_desc = usb_get_device_descriptor(handle);
	if (!dev_desc)
		goto out;
	wrap->dev_desc = dev_desc;

	cfg_desc = usb_get_config_descriptor(handle, cfg);
	if (!cfg_desc)
		goto out2;
	wrap->cfg_desc = cfg_desc;

	ret = -EINVAL;
	if (intf >= cfg_desc->bNumInterfaces) {
		pr_err("select intf(%u) < max intf(%u)\n", intf, 
			cfg_desc->bNumInterfaces);
		goto out3;
	}
	interface = &cfg_desc->interface[intf];

	if (alt >= interface->num_altsetting) {
		pr_err("select alt(%u) < max alt(%u)\n", alt,
			interface->num_altsetting);
		goto out3;
	}
	intf_desc = &interface->altsetting[alt];

	pr_notice("Bind function ...\n");

	switch (dev_desc->bDeviceClass) {
	case USB_CLASS_PER_INTERFACE:
		switch (intf_desc->bInterfaceClass) {
		case USB_CLASS_MASS_STORAGE:
			wrap->func |= USBDEV_F_MSC;
			ret = msc_init(wrap);
			break;

		default:
			pr_warn("bInterfaceClass(0x%02x) is unknown!\n", 
				intf_desc->bInterfaceClass);
		}
		break;

	case USB_CLASS_MASS_STORAGE:
		wrap->func |= USBDEV_F_MSC;
		ret = msc_init(wrap);
		break;

	default:
		pr_warn("bDeviceClass(0x%02x) is unknown!\n", dev_desc->bDeviceClass);
	}

	if (ret < 0)
		goto out3;

	return 0;

out3:
	usb_put_config_descriptor(cfg_desc);
	wrap->cfg_desc = NULL;
out2:
	usb_put_device_descriptor(dev_desc);
	wrap->dev_desc = NULL;
out:
	return ret;
}

static void usb_unbind_function(struct usbdev_wrap *wrap)
{
	if (wrap->func & USBDEV_F_MSC) {
		msc_exit(wrap->msc);
		wrap->msc = NULL;
	}

	usb_put_config_descriptor(wrap->cfg_desc);
	wrap->cfg_desc = NULL;
	usb_put_device_descriptor(wrap->dev_desc);
	wrap->dev_desc = NULL;
}

static int usbtool_init(struct usbtool *tool)
{
	int ret;
	struct usr_param *param = &tool->param;
	libusb_context *ctx = tool->devwrap.ctx;
	libusb_device_handle *handle;

	ret = libusb_init(&tool->devwrap.ctx);
	if (ret < 0) {
		pr_err("failed to init libusb!(%d)\n", ret);
		return ret;
	}

	ret = libusb_get_device_list(tool->devwrap.ctx, &tool->devwrap.dev_list);
	if (ret < 0) {
		pr_err("failed to get device list!(%d)\n", ret);
		goto out;
	}

	if (!param->vid && !param->pid)
		return 0;

	/*
	 * If both VID and PID are not zero, it is considered to need to open
	 * the specified USB device.
	 */
	handle = libusb_open_device_with_vid_pid(ctx, param->vid, param->pid);
	if (!handle) {
		pr_err("failed to open device!(0x%04x:0x%04x)\n", param->vid, param->pid);
		goto out2;
	}
	tool->devwrap.handle = handle;

	return 0;
out2:
	libusb_free_device_list(tool->devwrap.dev_list, 1);
out:
	libusb_exit(tool->devwrap.ctx);
	return ret;
}

static void usbtool_exit(struct usbtool *tool)
{
	libusb_close(tool->devwrap.handle);
	libusb_free_device_list(tool->devwrap.dev_list, 1);
	libusb_exit(tool->devwrap.ctx);
}

static int execute_usr_command(struct usbtool *tool, int cmd)
{
	int ret;

	if (cmd < 0 || cmd >= USR_CMD_MAX)
		return -EINVAL;

	ret = usbtool_init(tool);
	if (ret < 0)
		return ret;

	if (tool->ops[cmd].flag & USR_CMD_BIND_FUNC) {
		ret = usb_bind_function(&tool->devwrap, 0, 0, 0);
		if (ret < 0)
			goto out;
	}

	if (tool->ops[cmd].cmd_exec)
		ret = tool->ops[cmd].cmd_exec(tool);

	if (tool->ops[cmd].flag & USR_CMD_BIND_FUNC)
		usb_unbind_function(&tool->devwrap);
out:
	usbtool_exit(tool);
	return ret;
}

int main(int argc, char *argv[])
{
	int ret;
	struct usbtool *tool;

	tool = calloc(1, sizeof(*tool));
	if (!tool) {
		pr_err("failed to alloc usbtool!\n");
		return -ENOMEM;
	}
	g_usbtool = tool;
	g_usbtool->ops = g_cmd_ops;

	ret = parse_usr_param(&tool->param, argc, argv);
	if (ret < 0)
		goto out;

	ret = execute_usr_command(tool, tool->param.cmd);
	if (ret < 0) {
		pr_err("failed to execute command %d!(%d)\n",
			tool->param.cmd, ret);
		goto out;
	}

out:
	free(tool);
	g_usbtool = NULL;
	return ret;
}
