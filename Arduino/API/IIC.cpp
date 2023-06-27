#include "IIC.h"
#include "Wire.h"
#include "Arduino.h"
#include "vl53l0x_def.h"

int32_t IIC_init()
{
  Wire.begin();
  return VL53L0X_ERROR_NONE;
}

void IIC_write_byte(uint8_t slave,uint8_t data)
{
  Wire.beginTransmission(slave);
  Wire.write(data);
  Wire.endTransmission();
}

int32_t IIC_write_multiByte(uint8_t slave, uint8_t reg, uint8_t *buff, uint16_t len)
{
  Wire.beginTransmission(slave);
  Wire.write(reg);
  
  while(len--)
  {
    Wire.write((uint8_t)buff[0]);
    buff++;
  }
  Wire.endTransmission();
  return VL53L0X_ERROR_NONE;
}

int32_t IIC_read_byte(uint8_t slave)
{
  Wire.requestFrom(slave,1);
  while(Wire.available() < 1) delay(1);
  int32_t rec = Wire.read();
  return rec;
}

int32_t IIC_read_multiByte(uint8_t slave, uint8_t reg, uint8_t *buff, uint16_t len)
{
  IIC_write_byte(slave, reg);
  Wire.requestFrom(slave, (byte)len);
//  while(Wire.available() < 1) delay(1);
  while(len--)
  {
    buff[0] = Wire.read();
    buff++;
  }
  
  return VL53L0X_ERROR_NONE;
}

