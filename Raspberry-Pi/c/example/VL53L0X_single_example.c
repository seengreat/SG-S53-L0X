/***************************************************************************************
 * Project  :VL53L0X-IIC-Raspberry Pi
 * Describe :Use an IIC to measure distance.
 * Experimental Platform :Raspberry Pi + VL53L0X 
 * Hardware Connection :Raspberry Pi -> SG-S53-L0X Module
 *      3V3  -> VCC         SCL.1 -> SCL
 *      GND  -> GND         SDA.1 -> SDA
 * Library Version :
 * Web Site    :www.seengreat.com
***************************************************************************************/

#include "VL53L0X.h"
#include "vl53l0x_platform.h"
#include "vl53l0x_api.h"
#include "vl53l0x_def.h"
#include "string.h"
#include "stdio.h"
// #include "vl53l0x_api_calibration.h"

VL53L0X_Dev_t dev;
VL53L0X_RangingMeasurementData_t rdata;
VL53L0X_DeviceInfo_t pVL53L0X_DeviceInfo;

int main(int argc, char const *argv[])
{
    int8_t status = VL53L0X_ERROR_NONE;
    printf("\n---------- SG-S53-L0X Module ----------\n");
    printf("Raspberry Pi 4 Model B ");
    printf("V1.0 Build 2023/4/14 10:35\n");
    //mode: 0:defult; 1: high precision; 2:long distance; 3:high speed
    status = vl53l0x_Init(&dev, 0);
    if(status == VL53L0X_ERROR_NONE)
        printf("VL53L0X init \n");
    else
        printf("init error\n");

    status = VL53L0X_GetDeviceInfo(&dev,&pVL53L0X_DeviceInfo);
	if(status == VL53L0X_ERROR_NONE)
	{
		printf("VL53L0X_GetDeviceInfo:\n");
		printf("Device name is %s\n",pVL53L0X_DeviceInfo.Name);
		printf("Device id is %s\n",pVL53L0X_DeviceInfo.ProductId);
        printf("Device type is %d\n",pVL53L0X_DeviceInfo.ProductType);
		printf("ProductRevisionMajor is %d\n",pVL53L0X_DeviceInfo.ProductRevisionMajor);
		printf("ProductRevisionMinor is %d\n",pVL53L0X_DeviceInfo.ProductRevisionMinor);
	}

    while (1)
    {
        vl53l0x_single_range(&dev, &rdata);
    }
    return 0;
}
