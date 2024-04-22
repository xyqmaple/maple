/**
 * @file message.c
 * @author yeqiang_xu <yeqiang_xu@maxio-tech.com>
 * @brief 
 * @version 0.1
 * @date 2022-08-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdlib.h>
#include <errno.h>

#include "log.h"
#include "types.h"
#include "usb/ch9.h"
#include "message.h"

/**
 * @brief Retrieve a descriptor from the default control pipe.
 * 
 * @param handle a device handle
 * @param desc_type the descriptor type, see libusb_descriptor_type
 * @param desc_index the index of the descriptor to retrieve
 * @param data output buffer for descriptor
 * @param length size of data buffer
 * @return number of bytes returned in data, or LIBUSB_ERROR code on failure
 */
static inline int usb_get_descriptor(libusb_device_handle *handle, u8 desc_type, 
	u8 desc_index, u8 *data, u16 length)
{
	return libusb_control_transfer(handle, LIBUSB_ENDPOINT_IN | 
		LIBUSB_REQUEST_TYPE_STANDARD | LIBUSB_RECIPIENT_DEVICE, 
		LIBUSB_REQUEST_GET_DESCRIPTOR, (u16)((desc_type << 8) | 
		desc_index), 0, data, length, USB_CTRL_XFER_TIMEOUT);
}

/**
 * @brief Retrieve a device descriptor from the default control pipe.
 * 
 * @param handle a device handle
 * @return device descriptor on success, otherwise NULL.
 */
struct libusb_device_descriptor *usb_get_device_descriptor(
	libusb_device_handle *handle)
{
	int ret;
	struct libusb_device_descriptor *desc;

	desc = calloc(1, sizeof(*desc));
	if (!desc) {
		pr_err("failed to alloc device descriptor!\n");
		return NULL;
	}

	ret = usb_get_descriptor(handle, LIBUSB_DT_DEVICE, 0, 
		(u8 *)desc, sizeof(*desc));
	if (ret < 0) {
		pr_err("failed to get desc: %s!\n", libusb_error_name(ret));
		goto out;
	}

	return desc;
out:
	free(desc);
	return NULL;
}

/**
 * @brief Retrieve a bos descriptor from the default control pipe.
 * 
 * @param handle a device handle
 * @return bos descriptor on success, otherwise NULL.
 */
struct libusb_bos_descriptor *usb_get_bos_descriptor(libusb_device_handle *handle)
{
	int ret;
	struct libusb_bos_descriptor *desc;

	ret = libusb_get_bos_descriptor(handle, &desc);
	if (ret < 0) {
		pr_err("failed to get bos desc: %s!\n", libusb_error_name(ret));
		return NULL;
	}
	return desc;
}

struct libusb_config_descriptor *usb_get_config_descriptor(
	libusb_device_handle *handle, u8 index)
{
	int ret;
	libusb_device *dev = libusb_get_device(handle);
	struct libusb_config_descriptor *desc;

	ret = libusb_get_config_descriptor(dev, index, &desc);
	if (ret < 0) {
		pr_err("failed to get config desc: %s!\n", libusb_error_name(ret));
		return NULL;
	}
	return desc;
}

int usb_get_configruation(libusb_device_handle *handle)
{
	int ret;
	u8 cfg;

	ret = libusb_control_transfer(handle, LIBUSB_ENDPOINT_IN | 
		LIBUSB_REQUEST_TYPE_STANDARD | LIBUSB_RECIPIENT_DEVICE, 
		LIBUSB_REQUEST_GET_CONFIGURATION, 0, 0, &cfg, sizeof(cfg), 
		USB_CTRL_XFER_TIMEOUT);
	if (ret < 0) {
		pr_err("failed to get configuration: %s!\n", libusb_error_name(ret));
		return -EIO;
	}

	pr_debug("current configure: %u\n", cfg);
	return (int)cfg;
}

int usb_get_interface(libusb_device_handle *handle, u16 intf)
{
	int ret;
	u8 alt;

	ret = libusb_control_transfer(handle, LIBUSB_ENDPOINT_IN | 
		LIBUSB_REQUEST_TYPE_STANDARD | LIBUSB_RECIPIENT_INTERFACE,
		LIBUSB_REQUEST_GET_INTERFACE, 0, intf, &alt, sizeof(alt),
		USB_CTRL_XFER_TIMEOUT);
	if (ret < 0) {
		pr_err("failed to get interface %u: %s!\n", intf, 
			libusb_error_name(ret));
		return -EIO;
	}

	pr_debug("interface %u alternate %u\n", intf, alt);
	return (int)alt;
}

int usb_set_interface(libusb_device_handle *handle, u16 intf, u16 alt)
{
	int ret;

	ret = libusb_control_transfer(handle, LIBUSB_ENDPOINT_OUT |
		LIBUSB_REQUEST_TYPE_STANDARD | LIBUSB_RECIPIENT_INTERFACE,
		LIBUSB_REQUEST_SET_INTERFACE, alt, intf, NULL, 0,
		USB_CTRL_XFER_TIMEOUT);
	if (ret < 0) {
		pr_err("failed to set interface %u, alt %u: %s!\n", intf, 
			alt, libusb_error_name(ret));
		return -EIO;
	}

	return 0;
}

int usb_get_device_status(libusb_device_handle *handle)
{
	int ret;
	u16 state;

	ret = libusb_control_transfer(handle, LIBUSB_ENDPOINT_IN |
		LIBUSB_REQUEST_TYPE_STANDARD | LIBUSB_RECIPIENT_DEVICE,
		LIBUSB_REQUEST_GET_STATUS, 0, 0, (u8 *)&state, sizeof(state),
		USB_CTRL_XFER_TIMEOUT);
	if (ret < 0) {
		pr_err("failed to get dev status: %s!\n", libusb_error_name(ret));
		return -EIO;
	}

	pr_debug("device state: 0x%04x\n", state);
	return (int)state;
}

int usb_get_interface_status(libusb_device_handle *handle, u16 intf)
{
	int ret;
	u16 state;

	ret = libusb_control_transfer(handle, LIBUSB_ENDPOINT_IN |
		LIBUSB_REQUEST_TYPE_STANDARD | LIBUSB_RECIPIENT_DEVICE,
		LIBUSB_REQUEST_GET_STATUS, 0, intf, (u8 *)&state, sizeof(state),
		USB_CTRL_XFER_TIMEOUT);
	if (ret < 0) {
		pr_err("failed to get intf(%u) status: %s!\n", 
			intf, libusb_error_name(ret));
		return -EIO;
	}

	pr_debug("interface %u state: 0x%04x\n", intf, state);
	return (int)state;
}

int usb_get_endpoint_status(libusb_device_handle *handle, u16 ep_num)
{
	int ret;
	u16 state;

	ret = libusb_control_transfer(handle, LIBUSB_ENDPOINT_IN |
		LIBUSB_REQUEST_TYPE_STANDARD | LIBUSB_RECIPIENT_DEVICE,
		LIBUSB_REQUEST_GET_STATUS, 0, ep_num, (u8 *)&state, sizeof(state), 
		USB_CTRL_XFER_TIMEOUT);
	if (ret < 0) {
		pr_err("failed to get ep(0x%x) status: %s!\n", 
			ep_num, libusb_error_name(ret));
		return -EIO;
	}

	pr_debug("endpoint 0x%02x state: 0x%04x\n", ep_num, state);
	return (int)state;
}

int usb_set_endpoint_feature(libusb_device_handle *handle, u16 ep_num, u16 feature)
{
	int ret;

	ret = libusb_control_transfer(handle, LIBUSB_ENDPOINT_OUT | 
		LIBUSB_REQUEST_TYPE_STANDARD | LIBUSB_RECIPIENT_ENDPOINT, 
		LIBUSB_REQUEST_SET_FEATURE, feature, ep_num, NULL, 0, 
		USB_CTRL_XFER_TIMEOUT);
	if (ret < 0) {
		pr_err("failed to set ep(0x%x) feature(%u): %s!\n", 
			ep_num, feature, libusb_error_name(ret));
		return -EIO;
	}

	return 0;
}

int usb_clear_endpoint_feature(libusb_device_handle *handle, u16 ep_num, u16 feature)
{
	int ret;

	ret = libusb_control_transfer(handle, LIBUSB_ENDPOINT_OUT | 
		LIBUSB_REQUEST_TYPE_STANDARD | LIBUSB_RECIPIENT_ENDPOINT, 
		LIBUSB_REQUEST_CLEAR_FEATURE, feature, ep_num, NULL, 0, 
		USB_CTRL_XFER_TIMEOUT);
	if (ret < 0) {
		pr_err("failed to clear ep(0x%x) feature(%u): %s!\n", 
			ep_num, feature, libusb_error_name(ret));
		return -EIO;
	}

	return 0;
}
