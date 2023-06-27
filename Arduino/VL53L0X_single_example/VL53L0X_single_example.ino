/***************************************************************************************
 * Project  :VL53L0X-IIC-Arduino
 * Describe :Use an IIC to measure distance.
 * Experimental Platform :Arduino UNO + VL53L0X 
 * Hardware Connection :Arduino -> SG-S53-L0X Module
 *      5V   -> VCC         SCL -> SCL
 *      GND  -> GND         SDA -> SDA
 * Web Site    :www.seengreat.com
***************************************************************************************/


#include "VL53L0X.h"
#include "vl53l0x_platform.h"
#include "vl53l0x_api.h"
#include "vl53l0x_def.h"

VL53L0X_Dev_t dev;
VL53L0X_RangingMeasurementData_t rdata;
VL53L0X_DeviceInfo_t pVL53L0X_DeviceInfo;

void setup() {
  uint8_t status = VL53L0X_ERROR_NONE;
  Serial.begin(115200);
  Serial.print("\r\n---------- SG-S53-L0X Module ----------\r\n");
  Serial.print("Arduino UNO ");
  Serial.print("V1.0 Build 2023/4/14 10:35\r\n");
  //mode: 0:defult; 1: high precision; 2:long distance; 3:high speed
  status = vl53l0x_Init(&dev, 0);
  if(status == VL53L0X_ERROR_NONE)
    Serial.print("VL53L0X init \r\n");
  else
    Serial.print("init error\r\n");
   //  status = vl53l0x_Calibration(dev);  //SPAD,temperature calibration
  
  status = VL53L0X_GetDeviceInfo(&dev,&pVL53L0X_DeviceInfo);
  if(status == VL53L0X_ERROR_NONE)
  {
    Serial.print("VL53L0X_GetDeviceInfo:\r\n");
    Serial.print("Device name is ");
    Serial.println(pVL53L0X_DeviceInfo.Name);
    Serial.print("Device type is ");
    Serial.println(pVL53L0X_DeviceInfo.ProductType);
    Serial.print("Device id is ");
    Serial.println(pVL53L0X_DeviceInfo.ProductId);
    Serial.print("ProductRevisionMajor is ");
    Serial.println(pVL53L0X_DeviceInfo.ProductRevisionMajor);
    Serial.print("ProductRevisionMinor is ");
    Serial.println(pVL53L0X_DeviceInfo.ProductRevisionMinor);
  }
}

void loop() {
  vl53l0x_single_test(&dev, &rdata);
  
}
