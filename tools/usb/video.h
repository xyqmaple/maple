/**
 * @file video.h
 * @author yeqiang_xu <yeqiang_xu@maxio-tech.com>
 * @brief 
 * @version 0.1
 * @date 2022-10-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _USB_VIDEO_H_
#define _USB_VIDEO_H_

#include "libuvc/libuvc.h"
#include "core.h"

struct video_device {
	uvc_context_t		*ctx;
	uvc_device_t		*dev;
	uvc_device_handle_t	*devh;
	uvc_stream_ctrl_t	ctrl;

	struct usbdev_wrap	*devwrap;
};

int video_start(struct video_device *video);
int video_stop(struct video_device *video);

int video_init(struct usbdev_wrap *devwrap);
void video_exit(struct video_device *video);

#endif /* !_USB_VIDEO_H_ */
