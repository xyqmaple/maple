# Dir related
BASE_DIR = $(shell pwd)
OUTPUT = $(BASE_DIR)/../output/app

# File related
SRCS = $(wildcard src/*.c src/*/*.c src/*/*/*.c)
TARGETS = $(SRCS:%.c=%)

# Compiler related
CROSS_COMPILE ?=
AR = $(CROSS_COMPILE)ar
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld

# Flags related
CFLAGS += -O2 -Wall
CFLAGS += -I./include

EXIST = $(shell if [ -d $(OUTPUT) ]; then echo "exist"; else echo "notexist"; fi;)

# Execute content
.PHONY = clean all

all: build copy

build: $(TARGETS)
$(TARGETS):%:%.c
	$(CC) $(CFLAGS) $< -o $@

copy:
ifneq ($(EXIST), "exist")
	@mkdir -p $(OUTPUT)
endif
	cp $(TARGETS) $(OUTPUT)/

clean:
	@rm -rf $(TARGETS)

