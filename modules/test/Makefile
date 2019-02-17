-include ../Rules.mk

KERNEL_DIR ?= /lib/modules/$(shell uname -r)/build

TARGET = test.ko
obj-m := test.o

.PHONY: clean release

default: release

release:
	make -C $(KERNEL_DIR) M=`pwd` $(MAKE_ENV) EXTRA_CFLAGS="$(EXTRA_CFLAGS)" modules
	@rm -rf .tmp_versions *.mod.* *.o .*.mod .*.ko.cmd .*.o.cmd .cache.mk

clean:
	@rm -rf .tmp_versions *.mod.* *.o .*.mod .*.ko.cmd .*.o.cmd *.ko .cache.mk Module.symvers modules.order
