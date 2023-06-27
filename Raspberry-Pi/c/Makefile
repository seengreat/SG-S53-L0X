CC = $(CROSS_COMPILE)gcc
AR = $(CROSS_COMPILE)ar
RM = rm

CFLAGS = -O0 -g -Wall -c
#CFLAGS = -O2 -Wall -c

OUTPUT_DIR = bin
OBJ_DIR = obj

ROOT_DIR := $(shell pwd)
# API_DIR := /home/pi/c/SG53LXX

TARGET_LIB = $(OUTPUT_DIR)/libVL53L0X_c.a

INCLUDES = \
	-I.\
	-I$(ROOT_DIR) \
	-I$(ROOT_DIR)/Api/include 

# PYTHON_INCLUDES = \
#     -I/usr/include/python2.7

VPATH = \
	$(ROOT_DIR)/Api/src	\
	$(ROOT_DIR)/example

LIB_SRCS = \
	vl53l0x_api_calibration.c \
	vl53l0x_api_core.c \
	vl53l0x_api_ranging.c \
	vl53l0x_api_strings.c \
	vl53l0x_api.c \
	vl53l0x_platform.c \
	IIC.c		\
	vl53l0x_api_strings.c	\
	VL53L0X.c



LIB_OBJS  = $(LIB_SRCS:%.c=$(OBJ_DIR)/%.o)

EXAMPLES_SRC = $(wildcard example/*)
EXAMPLES_BIN = $(EXAMPLES_SRC:example/%.c=$(OUTPUT_DIR)/%)

.PHONY: all
all: ${TARGET_LIB}

$(TARGET_LIB): $(LIB_OBJS)
	mkdir -p $(dir $@)
	$(AR) -rcs $@ $^

$(OBJ_DIR)/%.o:%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) $< -o $@

$(EXAMPLES_BIN): bin/%:example/%.c
	mkdir -p $(dir $@)
	$(CC) -L$(OUTPUT_DIR) $^ -lVL53L0X_c	$(INCLUDES) -o $@

example:${OUTPUT_DIR} ${TARGET_LIB} ${EXAMPLES_BIN}

.PHONY: clean
clean:
	-${RM} -rf ./$(OUTPUT_DIR)/*  ./$(OBJ_DIR)/*