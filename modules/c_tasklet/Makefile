-include ../Rules.mk

TARGET = c_tasklet.ko
obj-m := c_tasklet.o

EXTRA_CFLAGS += -DCONFIG_CUSTOM_DELAY_WORK

.PHONY: clean release

default: release

release:
	make -C $(KERNEL_DIR) M=`pwd` $(MAKE_ENV) EXTRA_CFLAGS="$(EXTRA_CFLAGS)" modules
	@rm -rf .tmp_versions *.mod.* *.o .*.mod .*.ko.cmd .*.o.cmd .cache.mk

clean:
	@rm -rf .tmp_versions *.mod.* *.o .*.mod .*.ko.cmd .*.o.cmd *.ko .cache.mk Module.symvers modules.order
