#!/bin/sh

# --------------------------------------------------------------------------- #
# Default Configuration
# --------------------------------------------------------------------------- #
IP=dwc3
bcdUSB="0x0310"
UDC="10c00000.dwc3"

# --------------------------------------------------------------------------- #
# Function
# --------------------------------------------------------------------------- #

parse_param()
{
        if [ "$1" = "dwc2" ]; then
                IP=$1
                bcdUSB="0x0200"
                UDC="14000000.dwc2"

        elif [ "$1" = "dwc3" ]; then
                IP=$1
                bcdUSB="0x0310"
                UDC="10c00000.dwc3"
        fi
}

prepare_block_device()
{
        dd if=/dev/zero of=/mnt/mass_storage.img bs=1M count=20
        losetup /dev/loop0 /mnt/mass_storage.img
        mount /dev/loop0 /tmp
}

config_mass_storage()
{
        mount -t configfs none /sys/kernel/config
        cd /sys/kernel/config/usb_gadget

        # Create a new gadget instance
        mkdir mass_storage
        cd mass_storage

        # echo "0x0310" > bcdUSB
        echo $bcdUSB > bcdUSB
        echo "0x0100" > bcdDevice
        echo "0x0525" > idVendor
        echo "0xa4a5" > idProduct

        mkdir strings/0x0409
        echo "12345678" > strings/0x0409/serialnumber
        echo "Maxio" > strings/0x0409/manufacturer
        echo "MarsG2x" > strings/0x0409/product

        # Create function instance
        mkdir functions/mass_storage.0
        echo /dev/loop0 > functions/mass_storage.0/lun.0/file

        # Create configuration instance
        mkdir configs/c1.1
        mkdir configs/c1.1/strings/0x0409
        echo "mass storage" > configs/c1.1/strings/0x0409/configuration

        # Bind function instance to configuration instance
        ln -s functions/mass_storage.0 configs/c1.1

        # Configure usb controller to be used
        ls /sys/class/udc # Loop up usb controller information
        # echo "10c00000.dwc3" > UDC
        echo $UDC > UDC
}

# --------------------------------------------------------------------------- #
# Execute
# --------------------------------------------------------------------------- #

for arg in $* ; do
        parse_param $arg
done

prepare_block_device
config_mass_storage

