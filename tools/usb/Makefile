-include $(TOP_DIR)/.config

cdir := $(shell pwd)
srcs := $(wildcard *.c)
objs := $(srcs:.c=.o)
target := usbtool

USBTOOL_CFLAGS := -I./libusb/include/libusb-1.0
USBTOOL_CFLAGS += -I./libuvc/include

USBTOOL_LDFLAGS := -static
USBTOOL_LDFLAGS += -L./libusb/lib
USBTOOL_LDFLAGS += -L./libuvc/lib/x86_64-linux-gnu

USBTOOL_LDLIBS := -lusb-1.0 -luvc -lpthread

# FLAG: Check libusb is installed
f_libusb_install := $(shell if [ -d $(cdir)/libusb/include ]; then echo "installed"; fi)
f_libuvc_install := $(shell if [ -d $(cdir)/libuvc/include ]; then echo "installed"; fi)

.DEFAULT_GOAL := build

%.o: %.c
	$(Q)$(CC) $(CFLAGS) $(USBTOOL_CFLAGS) -c $^

$(target): $(objs)
	$(Q)$(CC) $(LDFLAGS) $(USBTOOL_LDFLAGS) $^ $(LDLIBS) $(USBTOOL_LDLIBS) -o $@

build_libusb:
ifneq ("$(f_libusb_install)","installed")
	$(Q)bash ./libusb/zoo build
endif

build_libuvc:
ifneq ("$(f_libuvc_install)","installed")
	$(Q)bash ./libuvc/zoo build
endif

build: build_libusb build_libuvc $(target)

clean:
	$(Q)rm -f $(target) $(objs)
	$(Q)bash ./libuvc/zoo clean
	$(Q)bash ./libusb/zoo clean

distclean:
	$(Q)rm -f $(target) $(objs)
	$(Q)bash ./libuvc/zoo distclean
	$(Q)bash ./libusb/zoo distclean

.PHONY: build clean distclean

