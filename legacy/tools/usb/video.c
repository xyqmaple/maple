/**
 * @file video.c
 * @author yeqiang_xu <yeqiang_xu@maxio-tech.com>
 * @brief 
 * @version 0.1
 * @date 2022-10-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include "defs.h"
#include "log.h"
#include "video.h"

static void video_stream_callback(uvc_frame_t *frame, void *ptr)
{
	pr_info("length = %u\n", frame->data_bytes);
	/* NOTE: Do something if necessary. */
}

int video_start(struct video_device *video)
{
	int ret;

	ret = uvc_get_stream_ctrl_format_size(video->devh, &video->ctrl, 
		UVC_FRAME_FORMAT_MJPEG, 640, 480, 30);
	uvc_print_stream_ctrl(&video->ctrl, stderr);

	if (ret < 0) {
		uvc_perror(ret, "get_stream_ctrl_format_size");
		return ret;
	}

	ret = uvc_start_streaming(video->devh, &video->ctrl, 
		video_stream_callback, video, 0);
	if (ret < 0) {
		uvc_perror(ret, "start_streaming");
		return ret;
	}

	return 0;
}

int video_stop(struct video_device *video)
{
	uvc_stop_streaming(video->devh);
	return 0;
}

int video_init(struct usbdev_wrap *devwrap)
{
	int ret;
	struct video_device *video = NULL;

	video = calloc(1, sizeof(*video));
	if (!video) {
		pr_err("failed to alloc video device!\n");
		return -ENOMEM;
	}
	video->devwrap = devwrap;

	/* !NOTE: Don't replace "NULL" with "devwrap->ctx" in the following
	 * function. Otherwise, stream callback function may not be executed 
	 * as normal.
	 */
	ret = uvc_init(&video->ctx, NULL);
	if (ret < 0) {
		uvc_perror(ret, "uvc_init");
		goto out;
	}
	pr_info("UVC initialized\n");

	ret = uvc_find_device(video->ctx, &video->dev, 0, 0, NULL);
	if (ret < 0) {
		uvc_perror(ret, "uvc_find_device");
		goto out2;
	}
	pr_info("Device found\n");

	ret = uvc_open(video->dev, &video->devh);
	if (ret < 0) {
		uvc_perror(ret, "uvc_open");
		goto out3;
	}
	pr_info("Device opened");

	uvc_print_diag(video->devh, stderr);

	devwrap->video = video;
	pr_info("init video device ok!\n");
	return 0;
out3:
	uvc_unref_device(video->dev);
out2:
	uvc_exit(video->ctx);
	pr_debug("UVC exited\n");
out:
	free(video);
	return ret;
}

void video_exit(struct video_device *video)
{
	struct usbdev_wrap *devwrap = NULL;

	if (!video)
		return;

	devwrap = video->devwrap;

	uvc_close(video->devh);
	uvc_unref_device(video->dev);
	uvc_exit(video->ctx);

	free(video);
	devwrap->video = NULL;
}
