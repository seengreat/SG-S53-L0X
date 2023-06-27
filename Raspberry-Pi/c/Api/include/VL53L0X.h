#ifndef _VL53L0X_H_
#define _VL53L0X_H_

#include "vl53l0x_def.h"
#include "vl53l0x_api.h"
#include "vl53l0x_platform.h"
#ifdef __cplusplus
extern "C" {
#endif
#include "stdint.h"

typedef struct 
{
  FixPoint1616_t sigal;
  FixPoint1616_t sigma;
  uint32_t timingBudget;
  uint8_t preVcselPeriod;
  uint8_t finalVcselPeriod;
} __attribute__((packed)) mode_setData;

VL53L0X_Error vl53l0x_Init(VL53L0X_Dev_t *dev, uint8_t mode);
VL53L0X_Error vl53l0x_Mode_Set(VL53L0X_Dev_t *dev,uint8_t mode);
VL53L0X_Error vl53l0x_Calibration(VL53L0X_Dev_t *dev);
VL53L0X_Error vl53l0x_continuous_range(VL53L0X_Dev_t *dev,VL53L0X_RangingMeasurementData_t *rdata);
VL53L0X_Error vl53l0x_single_range(VL53L0X_Dev_t *dev, VL53L0X_RangingMeasurementData_t *rdata);

#ifdef __cplusplus
}
#endif

#endif
