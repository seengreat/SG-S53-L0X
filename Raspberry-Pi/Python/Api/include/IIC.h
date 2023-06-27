#ifndef _IIC_H_
#define _IIC_H_
#include "stdint.h"
#include <string.h>

int IIC_init(char * devpath, uint8_t devaddr);
// void IIC_write_byte(uint8_t data);
int IIC_write_multiByte(int fd, uint8_t reg, uint8_t *buff, uint16_t len);
// int32_t IIC_read_byte(uint8_t slave);
int IIC_read_multiByte(int fd, uint8_t reg, uint8_t *buff, uint16_t len);

#endif
