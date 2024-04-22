-include .config

TOP_DIR := $(shell pwd)
CC := $(CONFIG_CROSS_COMPILE)gcc
AR := $(CONFIG_CROSS_COMPILE)ar

CFLAGS := -Wall -Wno-unused-variable -Wno-unused-function
CFLAGS += -I$(TOP_DIR)/include/uapi
CFLAGS += -I$(TOP_DIR)/include/generated
CFLAGS += -include $(TOP_DIR)/include/uapi/kconfig.h
LDFLAGS := -L$(TOP_DIR)/output/libs
LDLIBS := -lbase

export TOP_DIR
export CC
export AR
export CFLAGS
export LDFLAGS
export LDLIBS

ifeq ("$(origin V)","command line")
BUILD_VERBOSE := $(V)
endif
ifndef BUILD_VERBOSE
BUILD_VERBOSE := 0
endif

ifeq ($(BUILD_VERBOSE),1)
Q :=
else
Q := @
endif

export Q

.DEFAULT_GOAL := build

MCONF := scripts/kconfig/mconf
$(MCONF):
	$(Q)make CC=gcc HOSTCC=gcc -C scripts/kconfig

menuconfig: $(MCONF)
	$(Q)rm -rf $(TOP_DIR)/include/config
	$(Q)rm -rf $(TOP_DIR)/include/generated
	$(Q)$(MCONF) Kconfig

pre:
	$(Q)mkdir -p $(TOP_DIR)/output/libs

build: pre
	$(Q)make -C common/base
	$(Q)make -C tools/usb
	$(Q)make -C tools/reg
	$(Q)make -C test

clean:
	$(Q)make -C test clean
	$(Q)make -C tools/usb clean
	$(Q)make -C tools/reg clean
	$(Q)make -C common/base clean
	$(Q)make CC=gcc HOSTCC=gcc -C scripts/kconfig clean

distclean:
	$(Q)make -C test distclean
	$(Q)make -C tools/usb distclean
	$(Q)make -C tools/reg distclean
	$(Q)make -C common/base distclean
	$(Q)make CC=gcc HOSTCC=gcc -C scripts/kconfig distclean
	$(Q)rm -rf $(TOP_DIR)/output
	$(Q)rm -f $(TOP_DIR)/scripts/kconfig/.*.cmd \
		$(TOP_DIR)/scripts/kconfig/.depend

.PHONY: build clean distclean menuconfig

