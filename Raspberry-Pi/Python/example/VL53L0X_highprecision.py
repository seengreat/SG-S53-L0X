'''
Project  :VL53L0X-IIC-Raspberry Pi 4B
Describe :Use an IIC to measure distance.
Experimental Platform :Raspberry Pi 4B + VL53L0X 
Hardware Connection :Raspberry Pi 4B -> SG-S53-L0X Module
			3V3	 ->	VCC					SCL.1 -> SCL
			GND	 ->	GND					SDA.1 -> SDA
Library Version :
Web Site		 :www.seengreat.com
'''
from ctypes import *
import os
p = os.getcwd()+'/VL53L0X_python.so'

vl53l0x_lib = CDLL(p)

if __name__ == '__main__':
    vl53l0x_lib.VL53L0X_init(1)
    while True:
        vl53l0x_lib.VL53L0X_single_example()