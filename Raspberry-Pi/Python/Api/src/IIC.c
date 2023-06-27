#include "IIC.h"
#include "vl53l0x_def.h"
#include "sys/ioctl.h"
#include "linux/i2c-dev.h"
#include "fcntl.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"
#include <string.h>

int IIC_init(char * devpath, uint8_t devaddr)
{
  int fd;
    if ((fd = open(devpath, O_RDWR)) < 0) {
        /* ERROR HANDLING: you can check errno to see what went wrong */
        printf("Failed to open the i2c bus\n");
        return -1;
    }
    if (ioctl(fd, I2C_SLAVE, devaddr) < 0) {
        printf("Failed to acquire bus access and/or talk to slave.\n");
        /* ERROR HANDLING; you can check errno to see what went wrong */
        return -1;
    }
    return fd;
}

// void IIC_write_byte(uint8_t slave,uint8_t data)
// {
    
// }

int IIC_write_multiByte(int fd, uint8_t reg, uint8_t *buff, uint16_t len)
{
  uint8_t * data = malloc(len+1);
  data[0] = reg;
  memcpy(data+1,buff,len);
  if (write(fd, data, len+1) != len+1)
  {
    printf("write error!(write)\n");
    free(data);
    return 1;
  }
  free(data);
  return 0;
}

// int32_t IIC_read_byte(uint8_t slave)
// {
//   Wire.requestFrom(slave,1);
//   while(Wire.available() < 1) delay(1);
//   int32_t rec = Wire.read();
//   return rec;
// }

int IIC_read_multiByte(int fd, uint8_t reg, uint8_t *buff, uint16_t len)
{
  if(write(fd, &reg, 1) != 1)
  {
    return 1;
  }

  if (read(fd, buff, len) != len)
  {
    printf("read error.\n");
    return 1;
  }
  
  return 0;
}
