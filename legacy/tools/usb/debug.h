/**
 * @file debug.h
 * @author yeqiang_xu <yeqiang_xu@maxio-tech.com>
 * @brief 
 * @version 0.1
 * @date 2022-08-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _USB_DEBUG_H_
#define _USB_DEBUG_H_

#include "libusb.h"

void usb_print_device_descriptor(struct libusb_device_descriptor *desc);

#endif /* !_USB_DEBUG_H_ */
