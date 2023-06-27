CC = $(CROSS_COMPILE)gcc
RM = rm

CFLAGS = -O0 -g -Wall -c
#CFLAGS = -O2 -Wall -c

OUTPUT_DIR = example
OBJ_DIR = obj

ROOT_DIR := $(shell pwd)
# API_DIR := /home/pi/Python/SG53LXX

TARGET_LIB = $(OUTPUT_DIR)/VL53L0X_python

INCLUDES = \
	-I$(ROOT_DIR) \
	-I$(ROOT_DIR)/Api/include  \
	-I$(ROOT_DIR)/lib

PYTHON_INCLUDES = \
    -I/usr/include/python2.7

VPATH = \
	$(ROOT_DIR)/Api/src \
	$(ROOT_DIR)/lib

LIB_SRCS = \
	vl53l0x_api_calibration.c \
	vl53l0x_api_core.c \
	vl53l0x_api_ranging.c \
	vl53l0x_api_strings.c \
	vl53l0x_api.c \
	vl53l0x_platform.c \
    VL53L0X_python.c	\
	IIC.c		\
	vl53l0x_api_strings.c	\
	VL53L0X.c



LIB_OBJS  = $(LIB_SRCS:%.c=$(OBJ_DIR)/%.o)

.PHONY: all
all: ${TARGET_LIB}

$(TARGET_LIB): $(LIB_OBJS)
	$(CC) -shared $^ $(PYTHON_INCLUDES) $(INCLUDES) -lpthread -o $@.so

$(OBJ_DIR)/%.o:%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(PYTHON_INCLUDES) $(INCLUDES) $< -o $@

.PHONY: clean
clean:
	-${RM} -rf ./$(OUTPUT_DIR)/*  ./$(OBJ_DIR)/*