
srcs := $(wildcard *.c)
objs := $(srcs:.c=.o)
target := reg

LDFLAGS += -static

.DEFAULT_GOAL := build

%: %.c
	$(Q)$(CC) $(CFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

build: $(target)

clean:
	$(Q)-rm $(target)

distclean: clean

.PHONY: build clean distclean
