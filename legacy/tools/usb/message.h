/**
 * @file message.h
 * @author yeqiang_xu <yeqiang_xu@maxio-tech.com>
 * @brief 
 * @version 0.1
 * @date 2022-08-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _USB_MESSAGE_H_
#define _USB_MESSAGE_H_

#include "usb/ch9.h"
#include "libusb.h"

#define USB_CTRL_XFER_TIMEOUT		1000 /* ms */

struct libusb_device_descriptor *usb_get_device_descriptor(
	libusb_device_handle *handle);
struct libusb_bos_descriptor *usb_get_bos_descriptor(
	libusb_device_handle *handle);
struct libusb_config_descriptor *usb_get_config_descriptor(
	libusb_device_handle *handle, u8 index);

int usb_get_configruation(libusb_device_handle *handle);

int usb_get_interface(libusb_device_handle *handle, u16 intf);
int usb_set_interface(libusb_device_handle *handle, u16 intf, u16 alt);

int usb_get_device_status(libusb_device_handle *handle);
int usb_get_interface_status(libusb_device_handle *handle, u16 intf);
int usb_get_endpoint_status(libusb_device_handle *handle, u16 ep_num);

int usb_set_endpoint_feature(libusb_device_handle *handle, u16 ep_num, u16 feature);
int usb_clear_endpoint_feature(libusb_device_handle *handle, u16 ep_num, u16 feature);

static inline void usb_put_device_descriptor(struct libusb_device_descriptor *desc)
{
	free(desc);
}

static inline void usb_put_bos_descriptor(struct libusb_bos_descriptor *desc)
{
	libusb_free_bos_descriptor(desc);
}

static inline void usb_put_config_descriptor(struct libusb_config_descriptor *desc)
{
	libusb_free_config_descriptor(desc);
}

static inline int usb_set_endpoint_halt(libusb_device_handle *handle, u8 ep_num)
{
	return usb_set_endpoint_feature(handle, ep_num, USB_ENDPOINT_HALT);
}

static inline int usb_clear_endpoint_halt(libusb_device_handle *handle, u8 ep_num)
{
	return usb_clear_endpoint_feature(handle, ep_num, USB_ENDPOINT_HALT);
}

#endif /* !_USB_MESSAGE_H_ */
