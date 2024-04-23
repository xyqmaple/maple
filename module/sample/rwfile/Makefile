
CUR_DIR := $(shell dirname $(abspath $(firstword $(MAKEFILE_LIST))))
KERNEL_DIR := /lib/modules/$(shell uname -r)/build
CFG_FILE := $(CUR_DIR)/mod_cfg.h

TARGET		:= rwfile.ko
obj-m		:= rwfile.o
rwfile-y	:= core.o

build: prepare
	$(Q)make -C $(KERNEL_DIR) M=$(CUR_DIR) EXTRA_CFLAGS="$(EXTRA_CFLAGS)" modules

prepare:
	$(Q)echo "#define CONFIG_PRIV_FILE_PATH \"$(CUR_DIR)/data.bin\"" > $(CFG_FILE)

clean:
	$(Q)make -C $(KERNEL_DIR) M=$(CUR_DIR) clean
	$(Q)rm -f $(CFG_FILE)

distclean: clean

.PHONY: build clean distclean