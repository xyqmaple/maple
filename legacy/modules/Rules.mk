# Folder paths
PLATFORM_DIR = $(shell cd ../../..; pwd)
#KERNEL_DIR = $(PLATFORM_DIR)/kernel
KERNEL_DIR = /lib/modules/$(shell uname -r)/build
MAPLE_DIR = $(PLATFORM_DIR)/maple
MODULES_DIR = $(MAPLE_DIR)/modules

# File name
CURR_DIR_NAME = $(shell echo $(notdir $(shell pwd)))

# Compiler-related
TOOL_PREFIX =
CC = $(TOOL_PREFIX)gcc
#MAKE_ENV = ARCH=arm CROSS_COMPILE=$(TOOL_PREFIX)

# Headerfile-related
MODULES_SUBDIR = $(addprefix $(MODULES_DIR)/, $(filter-out Rules.mk zoo, $(notdir $(wildcard ../*))))

EXTRA_CFLAGS = $(addprefix -I, $(MODULES_SUBDIR))

