SG-S53-L0X(VL53L0X)  from seengreat:www.seengreat.com
 =======================================
# Instructions
## 1.1、Overview
This product uses I2C interface to achieve distance measurement, with a measurement distance of up to 2 meters; Supports Raspberry Pi models, as well as Arduino and STM32; We provide C and Python versions of Raspberry Pi demo codes, as well as Arduino and STM32 versions of demo codes. The demo codes can achieve three ranging working modes: single ranging, continuous ranging, and timed ranging, as well as four ranging configuration modes: default mode, high speed, high accuracy, and long range.<br>
## 1.2、Product parameters
|Size	|25mm*18mm|
|-----------|---------------|
|Supply voltage	|3.3V/5V|
|Ranging distance	|30~2000mm|
|Ranging accuracy	|±5%( high speed mode)，±3%(high accuracy mode)|
|Ranging time (min):|	20ms(short distance mode)，200ms (medium/long distance mode)|
|Field of view|	25°|
|Laser wavelength|	940nm|
|Control Chip|	VL53L0X|
|Signal interface|	I2C|

# Usage
## 2.1 Raspberry Pi demo codes usage
### 2.1.1 Hardware interface configuration description
The module with Raspberry Pi motherboard wiring is defined in the following table:<br>
|PIN	|Describe	|Raspberry Pi|
|-----------|-----------|-------------|
|VCC	|Power supply |positive(3.3V/5V)	|3.3V|
|GND	|Power supply ground	|GND|
|SDA	|I2C data line	|SDA1|
|SCL	|I2C clock line	|SCL1|
|SHT	|shutdown control, can connects to IO pin	|NC|
|GP1	|Interrupt output, can connects to IO pin	|NC|
<br>Table2-1 Definition of SG-S53-L0X and Raspberry Pi pin<br>
## 2.1.2、Wiringpi Library Installation
sudo apt-get install wiringpi<br>
wget https://project-downloads.drogon.net/wiringpi-latest.deb #Version 4B upgrade of Raspberry Pi<br>
sudo dpkg -i wiringpi-latest.deb<br>

gpio -v #<br>
If  version 2.52 appears, the installation is successful<br>
For the Bullseye branch system, use the following command:<br>
git clone https://github.com/WiringPi/WiringPi<br>
cd WiringPi<br>
./build<br>
gpio -v<br>
Running “gpio - v” will result in version 2.70. If it does not appear, it indicates an installation error<br>
If the error prompt "ImportError: No module named 'wiringpi'" appears when running the python version of the demo code, run the following command<br>
For Python 2. x version<br>
pip install wiringpi<br>
For Python 3. x version <br>
pip3 install wiringpi<br>
Note: If the installation fails, you can try the following compilation and installation:<br>
git clone --recursive https://github.com/WiringPi/WiringPi-Python.git<br>
Note: The -- recursive option can automatically pull the submodule, otherwise you need to download it manually.<br>
Enter the WiringPi Python folder you just downloaded, enter the following command, compile and install:<br>
For Python 2. x version<br>
sudo python setup.py install<br>
For Python 3. x version<br>
sudo python3 setup.py install<br>
 If the following error occurs: <br>
Error:Building this module requires either that swig is installed(e.g.'sudo apt install swig') or that wiringpi wrap.c from thesource distribution (on pypi) is available.<br>
At this time, enter the command sudo apt install swig to install swig. After that, compile and install sudo python3 setup.py install. If a message similar to the following appears, the installation is successful.<br>
ges<br>
Adding wiringpi 2.60.0 to easy-install.pth file<br>
Installed /usr/local/lib/python3.7/dist-packages/wiringpi-2.60.0-py3.7-linux-armv7<br>
Processing dependencies for wiringpi==2.60.0Finished processing dependencies for wiringpi==2.60.0<br>
### 2.1.3、Install Python library
#python3<br>
The demo codes uses the python 3 environment. To run the python demo codes , you need to install smbus:<br>
sudo apt-get install -y python-smbus<br>
### 2.1.4、Configure the I2C interface
sudo raspi-config<br>
Enable I2C interface<br>
Interfacing Options -> I2C -> Yes <br>
Install the i2c-tools tool to confirm<br>
sudo apt-get install i2c-tools<br>
View connected I2C devices<br>
i2cdetect -y 1<br>
Check the address and indicate that the module has successfully connected to Raspberry Pi, and the displayed address is 0X29;<br>
### 2.1.5、Run the demo codes
C：<br>
After downloading the demo codes, enter the Raspberry Pi/c directory and compile the code<br>
sudo make clean<br>
sudo make <br>
sudo make example<br>
After waiting for the program to compile, enter the “bin” directory<br>
Run demo codes<br>
sudo ./VL53L0X_single_example<br>
Connect the module according to the demo codes description. After running the demo codes , the Raspberry Pi terminal outputs device information and measured distance (using a single ranging as an example)(Unit:mm). <br>
Python：<br>
Enter the Raspberry Pi/Python directory<br>
sudo make<br>
Wait for the program compilation to complete, enter the example directory, and run the demo codes:<br>
sudo python VL53L0X_singleexample.py   <br>
The demo codes phenomenon in the Python version is similar to that in the C language version<br>
## 2.2 Arduino Demo Codes Usage
### 2.2.1 Wiring instructions
|PIN	|Describe	|Arduino|
|-----------|-----------|--------|
|VCC	|Power supply positive(3.3V/5V)	|5V|
|GND	|Power supply ground	|GND|
|SDA	|I2C data line	|SDA|
|SCL	|I2C clock line	|SCL|
|SHT	|shutdown control, can connects to IO pin	|NC|
|GP1	|Interrupt output, can connects to IO pin	|NC|
<br>Table2-2 Definition of SG-S53-L0X and Arduino <br>
### 2.2.2 Demo codes usage
Open the project file demo_codes\Arduino\VL53L0X_single_example\VL53L0X_single_example.ino with the Arduino IDE, import API.zip from the Arduino directory into Arduino:<br>
Sketch->Include Library->Add ZIP Library...<br>
Then click Verify, and upload it to the development board after verification.<br>
Click the tool, open the serial port monitor, set the baud rate to 115200, and observe the data changes.<br>
Open the serial port monitor and the display is as follows. Set the baud rate to 115200 (as shown in "1" in the figure below). <br>
## 2.3 STM32 Demo Codes Usage
### 2.3.1 Wiring instructions
|PIN	|Describe	|STM32 |
|-----------|-----------|--------|
|VCC	|Power supply positive(3.3V/5V)	|3.3V|
|GND	|Power supply ground	|GND|
|SDA	|I2C data line	|PB11|
|SCL	|I2C clock line	|PB10|
|SHT	|shutdown control, can connects to IO pin	|NC|
|GP1	|Interrupt output, can connects to IO pin	|NC|
<br>Table2-3 Definition of SG-S53-L0X and STM32 <br>
### 2.3.2 Demo codes usage
Use Keil uVision5 software to open the VL53L0X.uvprojx project file in the directory demo_codes\STM32\USER, and connect the module with STM32 according to the above table; download the program to the STM32 development board after compiling without errors;<br>
The debugging information output serial port in the demo codes is USART1, where PA9 is Tx and PA10 is Rx; After connecting the cable, open the Serial Port Debugging Assistant, select the serial port number, adjust the baud rate to 115200, click "Open"<br>

__Thank you for choosing the products of Shengui Technology Co.,Ltd. For more details about this product, please visit:
www.seengreat.com__

