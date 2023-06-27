/***************************************************************************************
 * Project  :VL53L0X-IIC-STM32
 * Describe :Use an IIC to measure distance.
 * Experimental Platform :STM32F103C8T6 + VL53L0X 
 * Hardware Connection :STM32f103 -> SG-S53-L0X Module
 *			3V3	 ->	VCC					PB10 -> SCL
 *			GND	 ->	GND					PB11 -> SDA
 * Library Version :ST_V3.5
 * Web Site		 :www.seengreat.com
***************************************************************************************/

#include "vl53l0x.h"
#include "vl_iic.h"
#include "usart.h"
#include "delay.h"
#include "vl53l0x_platform.h"
#include "vl53l0x_api.h"
#include "vl53l0x_def.h"


VL53L0X_Dev_t dev;
VL53L0X_RangingMeasurementData_t rdata;
VL53L0X_DeviceInfo_t pVL53L0X_DeviceInfo;
vu16 Distance = 0;

int main(void)
{
	uint8_t status = VL53L0X_ERROR_NONE;
	Uart1Init(115200 ,0,0);
	delay_init();
	
	printf("\r\n---------- SG-S53-L0X Module ----------\r\n");
	printf("STM32F103C8T6 ");
	printf("V1.0 Build 2023/4/10 10:35\r\n");
	//mode: 0:defult; 1: high precision; 2:long distance; 3:high speed
	status = vl53l0x_Init(&dev, 0);
	if(status == VL53L0X_ERROR_NONE)
		printf("VL53L0X init \r\n");
	else
		printf("init error\r\n");
	
	//VL53L0X_Error VL53L0X_GetDeviceInfo(VL53L0X_DEV Dev,VL53L0X_DeviceInfo_t *pVL53L0X_DeviceInfo);
	status = VL53L0X_GetDeviceInfo(&dev,&pVL53L0X_DeviceInfo);
	if(status == VL53L0X_ERROR_NONE)
	{
		printf("VL53L0X_GetDeviceInfo:\r\n");
		printf("Device name is %s\r\n",pVL53L0X_DeviceInfo.Name);
		printf("Device type is %s\r\n",pVL53L0X_DeviceInfo.ProductType);
		printf("Device id is %s\r\n",pVL53L0X_DeviceInfo.ProductId);
		printf("ProductRevisionMajor is %d\r\n",pVL53L0X_DeviceInfo.ProductRevisionMajor);
		printf("ProductRevisionMinor is %d\r\n",pVL53L0X_DeviceInfo.ProductRevisionMinor);
	}
	
	while(1)
	{
		vl53l0x_single_test(&dev, &rdata);
//		vl53l0x_continuous_range(&dev, &rdata);
		
	}
	
}


