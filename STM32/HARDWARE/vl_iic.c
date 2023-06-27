#include "vl_iic.h"
#include "stm32f10x_gpio.h"
#include "delay.h"

void IIC_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE );
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE );
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB, GPIO_Pin_10);
	GPIO_SetBits(GPIOB, GPIO_Pin_11);
	
}

void IIC_Start(void)
{
	SDA_OUT(); 	
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL=0;
}	  

void IIC_Stop(void)
{
	SDA_OUT();
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL=1;	
	IIC_SDA=1;
	delay_us(4); 	
}

u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();    
	IIC_SDA=1;delay_us(1);	   
	IIC_SCL=1;delay_us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;
	return 0;  
} 

void IIC_Ack(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}
    
void IIC_NAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}					 				     
		  
void IIC_Send_Byte(u8 txd)
{      
    u8 t;   
	  SDA_OUT(); 	    
    IIC_SCL=0;
    for(t=0;t<8;t++)
    {   
				if((txd&0x80)>>7)
					IIC_SDA=1;
				else
					IIC_SDA=0;
        txd<<=1; 	  
				delay_us(2);   
				IIC_SCL=1;
				delay_us(2); 
				IIC_SCL=0;	
				delay_us(2);
    }	
} 	    
 
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();
	IIC_SDA = 1;
  for(i=0;i<8;i++ )
	{
        IIC_SCL=1; 
        delay_us(1);
		    receive<<=1;
				if(READ_SDA)receive |= 1;
				IIC_SCL=0;  
				delay_us(1); 
	}	
	if (!ack)
			IIC_NAck();
	else
			IIC_Ack();
	return receive;
}

uint8_t IIC_Read_multiByte(uint8_t slave, uint8_t reg, uint8_t *buff, uint16_t len)
{
	IIC_Start();
	IIC_Send_Byte(slave);
	if(IIC_Wait_Ack()) 
	{
		IIC_Stop();
		return 1;
	}
	IIC_Send_Byte(reg);
	IIC_Wait_Ack();
	delay_us(5);
	IIC_Start(); 
	IIC_Send_Byte(slave|0x01);
	IIC_Wait_Ack();
	while(len)
	{
		
		if(1 == len)
		{
			*buff = IIC_Read_Byte(0);
			//IIC_NAck();
		}
		else
		{
			*buff = IIC_Read_Byte(1);
			//IIC_Ack();
		}
		buff++;
		len--;
	}
	IIC_Stop();

	return 0;
}


uint8_t IIC_Write_multiByte(uint8_t slave, uint8_t reg, uint8_t *buff, uint16_t len)
{
	IIC_Start();
	IIC_Send_Byte(slave);
	delay_us(50);
	if(IIC_Wait_Ack()) 
	{
		//printf("IIC stop!");
		IIC_Stop();
		//IIC_Write_multiByte(slave, reg, buff, len);
		return 1;
	}
	IIC_Send_Byte(reg);
	IIC_Wait_Ack();
	while(len--)
	{
		IIC_Send_Byte(*buff++);
		IIC_Wait_Ack();
	}
	IIC_Stop();
	delay_us(4);
	return 0;
}

