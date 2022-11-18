/**
 * @file debug.c
 * @author yeqiang_xu <yeqiang_xu@maxio-tech.com>
 * @brief 
 * @version 0.1
 * @date 2022-08-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>

#include "types.h"
#include "log.h"
#include "debug.h"

static void dump_data(u8 *data, u32 length)
{
	u32 i;

	for (i = 0; i < length; i++)
	{
		printf("%02x ", data[i]);
		if (!((i+1) % 16))
			printf("\n");
	}
	printf("\n");
}

void usb_print_device_descriptor(struct libusb_device_descriptor *desc)
{
	pr_debug("Reading Device Descriptor:\n");
	pr_debug("            length: %u\n", desc->bLength);
	pr_debug("       bcdUSB(hex): %04x\n", desc->bcdUSB);
	pr_debug("       C:SC:P(hex): %02x:%02x:%02x\n", desc->bDeviceClass,
		desc->bDeviceSubClass, desc->bDeviceProtocol);
	pr_debug("      VID:PID(hex): %04x:%04x\n", desc->idVendor, desc->idProduct);
	pr_debug("          EP0 MaxP: %u\n", desc->bMaxPacketSize0);
	pr_debug("    bcdDevice(hex): %04x\n", desc->bcdDevice);
	pr_debug("   iMan:iProd:iSer: %u:%u:%u\n", desc->iManufacturer, 
		desc->iProduct, desc->iSerialNumber);
	pr_debug("          nb confs: %u\n", desc->bNumConfigurations);
}
