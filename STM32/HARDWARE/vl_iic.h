#ifndef __VL_IIC_H_
#define __VL_IIC_H_
#include "stdint.h"
#include "delay.h"
#define STATUS_OK       0x00
#define STATUS_FAIL     0x01

#define SDA_IN()  {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=8<<12;}
#define SDA_OUT() {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=3<<12;}

#define IIC_SCL    PBout(10) //SCL
#define IIC_SDA    PBout(11) //SDA	 
#define READ_SDA   PBin(11) 

void IIC_Init(void);
void IIC_Start(void);
void IIC_Stop(void);
u8 IIC_Wait_Ack(void);
void IIC_Ack(void);
void IIC_NAck(void);
void IIC_Send_Byte(u8 txd);
u8 IIC_Read_Byte(unsigned char ack);
void IIC_Send_Byte(u8 txd);
uint8_t IIC_Write_multiByte(uint8_t slave, uint8_t reg, uint8_t *buff, uint16_t len);
uint8_t IIC_Read_multiByte(uint8_t slave, uint8_t reg, uint8_t *buff, uint16_t len);

#endif

