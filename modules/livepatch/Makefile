-include ../Rules.mk

TARGET = livepatch-sample.ko
obj-m := livepatch-sample.o

.PHONY: clean release

default: release

release:
	make -C $(KERNEL_DIR) M=`pwd` $(MAKE_ENV) EXTRA_CFLAGS="$(EXTRA_CFLAGS)" modules

clean:
	make -C $(KERNEL_DIR) M=`pwd` $(MAKE_ENV) EXTRA_CFLAGS="$(EXTRA_CFLAGS)" modules clean

