/**
 * @file core.h
 * @author yeqiang_xu <yeqiang_xu@maxio-tech.com>
 * @brief 
 * @version 0.1
 * @date 2022-08-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _USB_CORE_H_
#define _USB_CORE_H_

#include "types.h"
#include "libusb.h"

struct usbtool;

enum usr_command {
	USR_CMD_INVALID = -1,
	USR_CMD_LIST_DEV = 0,
	USR_CMD_LIST_DEVS,
	USR_CMD_GET_DESC,
	USR_CMD_MSC_SET,
	USR_CMD_UVC_CAP,
	USR_CMD_CUSTOM,
	USR_CMD_MAX,
};

enum usr_cmd_flag {
	USR_CMD_BIND_FUNC = (1 << 0),
};

struct usr_cmd_ops {
	const char		*name;
	u32			flag;
	int	(*cmd_exec)(struct usbtool *tool);
};

struct usr_param {
	u16		vid;
	u16		pid;
	int		cmd;
};

enum usbdev_function {
	USBDEV_F_MSC = (1 << 0),
	USBDEV_F_UVC = (1 << 1),
};

struct usbdev_wrap {
	libusb_context		*ctx;
	libusb_device		**dev_list;

	libusb_device		*dev;
	libusb_device_handle	*handle;

	struct libusb_device_descriptor *dev_desc;
	struct libusb_config_descriptor *cfg_desc;

	u32			func;
	struct msc_device	*msc;
	struct video_device	*video;
};

struct usbtool {
	struct usr_param	param;
	struct usbdev_wrap	devwrap;
	struct usr_cmd_ops	*ops;
};

#endif /* !_USB_CORE_H_ */
