#include "vl53l0x.h"
#include "vl_iic.h"
#include "vl53l0x_def.h"
#include "vl53l0x_api.h"
#include "vl53l0x_platform.h"
//#include "stm32f10x_gpio.h"
//#include "delay.h"


extern vu16 Distance;

mode_setData Mode_Setdata[]=
{
	{
		(FixPoint1616_t)(0.25*65536),
		(FixPoint1616_t)(18*65536),
		33000,
		14,
		10
	},	//defult
	{
		(FixPoint1616_t)(0.25*65536),
		(FixPoint1616_t)(18*65536),
		200000,
		14,
		10
	},  //high precision
	{
		(FixPoint1616_t)(0.1*65536),
		(FixPoint1616_t)(60*65536),
		33000,
		18,
		14
	},  //long distance
	{
		(FixPoint1616_t)(0.25*65536),
		(FixPoint1616_t)(32*65536),
		20000,
		14,
		10
	}	//high speed
};

//void VL53l0x_GPIO_Init(void)
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	
//	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE );
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOB, &GPIO_InitStructure);
//}

VL53L0X_Error vl53l0x_Init(VL53L0X_Dev_t *dev, uint8_t mode)
{
	VL53L0X_Error status = VL53L0X_ERROR_NONE;
	
	
	dev->I2cDevAddr = 0x52;        //I2C address(defult:0x52)
	dev->comms_type = 1;           //I2C communication mode
	dev->comms_speed_khz = 400;    //I2C communication speed
	
	//VL53l0x_GPIO_Init();
	IIC_Init();

	status = VL53L0X_DataInit(dev);//device init
	if(status!=VL53L0X_ERROR_NONE) 
	{
		printf("datainit  failed!  \r\n");
		return status;
	}
	
	
	
	status = vl53l0x_Calibration(dev);	//SPAD,temperature calibration
	
	//Set measurement mode
	vl53l0x_Mode_Set(dev, mode);		
	
//	status = VL53L0X_SetDeviceMode(dev,VL53L0X_DEVICEMODE_SINGLE_RANGING);
//	if(status!=VL53L0X_ERROR_NONE) 
//	{
//		return status;
//	}	
	
	
	
	return status;
}

/***************************
* VL53L0X continuous ranging
* dev: device I2C param struct
* rdata: result struct
*****************************/
VL53L0X_Error vl53l0x_continuous_range(VL53L0X_Dev_t *dev, VL53L0X_RangingMeasurementData_t *rdata)
{
  VL53L0X_Error status = VL53L0X_ERROR_NONE;
  uint8_t isDataReady = 0;
  status = VL53L0X_SetDeviceMode(dev, VL53L0X_DEVICEMODE_CONTINUOUS_RANGING);
  if (status != VL53L0X_ERROR_NONE)
    return status;
    
  status = VL53L0X_StartMeasurement(dev);
  if (status != VL53L0X_ERROR_NONE)
    return status;
  while (1)
  {
    do {
      status = VL53L0X_GetMeasurementDataReady(dev, &isDataReady);
      if (status != 0)
        break; /* the error is set */

      if (isDataReady == 1)
        break; /* done note that status == 0 */


      VL53L0X_PollingDelay(dev);
    } while (1);

    if (isDataReady == 1)
    {
      status = VL53L0X_GetRangingMeasurementData(dev, rdata);
      
      printf("Continuous measurenment distance is: %d\r\n",rdata->RangeMilliMeter);
    }
    status = VL53L0X_ClearInterruptMask(dev, 0);
  }
}

/***************************
* VL53L0X single ranging
* dev: device I2C param struct
* rdata: result struct
*****************************/
VL53L0X_Error vl53l0x_single_test(VL53L0X_Dev_t *dev, VL53L0X_RangingMeasurementData_t *rdata)
{
  VL53L0X_Error status = VL53L0X_ERROR_NONE;

  status = VL53L0X_PerformSingleRangingMeasurement(dev, rdata);
  if (status != VL53L0X_ERROR_NONE)
    return status;
  printf("Single measurenment distance is: %d\r\n",rdata->RangeMilliMeter);
  status = VL53L0X_ClearInterruptMask(dev, 0);

  return status;
}

/***************************
* Set measurement mode
* mode: 0:defult; 1: high precision; 2:long distance; 3:high speed
******************************/
VL53L0X_Error vl53l0x_Mode_Set(VL53L0X_Dev_t *dev,uint8_t mode)
{
	VL53L0X_Error status = VL53L0X_ERROR_NONE;
	uint8_t VhvSet;
	uint8_t PhaseCal;
	
	VL53L0X_ResetDevice(dev);
	status = VL53L0X_StaticInit(dev);
	
	status = VL53L0X_PerformRefCalibration(dev, &VhvSet, &PhaseCal);	
	if(status != VL53L0X_ERROR_NONE) return status;
	delay_ms(2);
	
	status = VL53L0X_SetLimitCheckEnable(dev,VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE,1); //enable sigma check
	if(status != VL53L0X_ERROR_NONE) return status;
	delay_ms(2);
	
	status = VL53L0X_SetLimitCheckEnable(dev,VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE,1); 
	if(status != VL53L0X_ERROR_NONE) return status;
	delay_ms(2);
	
	status = VL53L0X_SetLimitCheckValue(dev,VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE,Mode_Setdata[mode].sigma); 
	if(status != VL53L0X_ERROR_NONE) return status;
	delay_ms(2);
	
	status = VL53L0X_SetLimitCheckValue(dev,VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE,Mode_Setdata[mode].signal); 
	if(status != VL53L0X_ERROR_NONE) return status;
	delay_ms(2);
	
	status = VL53L0X_SetMeasurementTimingBudgetMicroSeconds(dev,Mode_Setdata[mode].timingBudget); 
	if(status != VL53L0X_ERROR_NONE) return status;
	delay_ms(2);
	
	status = VL53L0X_SetVcselPulsePeriod(dev,VL53L0X_VCSEL_PERIOD_PRE_RANGE,Mode_Setdata[mode].preVcselPeriod); 
	if(status != VL53L0X_ERROR_NONE) return status;
	delay_ms(2);
	
	status = VL53L0X_SetVcselPulsePeriod(dev,VL53L0X_VCSEL_PERIOD_FINAL_RANGE,Mode_Setdata[mode].finalVcselPeriod); 
	if(status != VL53L0X_ERROR_NONE) return status;
	
	return status;
}

/******************
* VL53L0X calibration : temperature,SPAD
*******************/
VL53L0X_Error vl53l0x_Calibration(VL53L0X_Dev_t *dev)
{
	VL53L0X_Error status = VL53L0X_ERROR_NONE;
	uint8_t VhvSettings;
	uint8_t PhaseCal;
	uint32_t refSpadCount;
	uint8_t isApertureSpads;
	
	status = VL53L0X_StaticInit(dev);
	if(status!=VL53L0X_ERROR_NONE) 
	{
		return status;
	}
	
	status = VL53L0X_PerformRefCalibration(dev, &VhvSettings, &PhaseCal);
	if(status!=VL53L0X_ERROR_NONE) 
	{
		return status;
	}
	
	status = VL53L0X_PerformRefSpadManagement(dev, &refSpadCount, &isApertureSpads);
	if(status!=VL53L0X_ERROR_NONE) 
	{
		return status;
	}

	return status;
}


