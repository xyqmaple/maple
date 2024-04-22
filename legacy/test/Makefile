
srcs := $(wildcard *.c)
objs := $(srcs:.c=.o)
bins := $(srcs:.c=)

LDFLAGS += -static

.DEFAULT_GOAL := build

%: %.c
	$(Q)$(CC) $(CFLAGS) $(LDFLAGS) $< $(LDLIBS) -o $@

build: $(bins)

clean:
	$(Q)-rm $(bins)

distclean: clean

.PHONY: build clean distclean
