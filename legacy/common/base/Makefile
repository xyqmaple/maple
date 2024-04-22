
lib-csrcs := $(wildcard *.c)
lib-cobjs := $(lib-csrcs:.c=.o)
lib-ssrcs := $(wildcard *.S)
lib-sobjs := $(lib-ssrcs:.S=.o)
lib-common := $(addprefix lib,$(notdir $(shell pwd)))
lib-dynamic := $(addsuffix .so,$(lib-common))
lib-static := $(addsuffix .a,$(lib-common))

targets := $(lib-dynamic) $(lib-static)

.DEFAULT_GOAL := build

%.o: %.c
	$(Q)$(CC) $(CFLAGS) -fPIC -c $^

%.so: $(lib-cobjs)
	$(Q)$(CC) -shared $^ -o $@

%.a: $(lib-cobjs)
	$(Q)$(AR) rcs $@ $^

build: $(targets)
	$(Q)cp $(targets) $(TOP_DIR)/output/libs/

clean:
	$(Q)-rm $(targets)

distclean: clean

.PHONY: build clean distclean
