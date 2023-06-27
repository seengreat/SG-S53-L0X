#ifndef _IIC_H_
#define _IIC_H_
#include "Wire.h"

int32_t IIC_init();
void IIC_write_byte(uint8_t data);
int32_t IIC_write_multiByte(uint8_t slave, uint8_t reg, uint8_t *buff, uint16_t len);
int32_t IIC_read_byte(uint8_t slave);
int32_t IIC_read_multiByte(uint8_t slave, uint8_t reg, uint8_t *buff, uint16_t len);

#endif
