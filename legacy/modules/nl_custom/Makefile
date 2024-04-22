-include ../Rules.mk

TARGET = nl_custom.ko
obj-m := nl_custom.o

.PHONY: clean release

default: release

release:
	make -C $(KERNEL_DIR) M=`pwd` $(MAKE_ENV) EXTRA_CFLAGS="$(EXTRA_CFLAGS)" modules
	$(CC) -O2 test.c

clean:
	make -C $(KERNEL_DIR) M=`pwd` $(MAKE_ENV) EXTRA_CFLAGS="$(EXTRA_CFLAGS)" modules clean

