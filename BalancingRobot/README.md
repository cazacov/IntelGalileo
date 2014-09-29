Balancing robot
============

This self-balancing robot built from Lego is controlled by Microsoft Windows 8.1 running on the Galileo prototyping board.

[<img src="_img/robot.jpg?raw=true" alt="Balancing robot" width="480" height="640"/>]

## Parts list ##
- [Intel Galileo](http://en.wikipedia.org/wiki/Intel_Galileo) board
- 2 [LEGO XL motors](http://shop.lego.com/en-US/LEGO-Power-Functions-XL-Motor-8882) (other 9V motors should be also Ok)
- DFRduino [L298P motor shield](http://www.dfrobot.com/index.php?route=product/product&product_id=69)
- DC-DC step down converter (I use one based on LM2596 IC)
- [Sparkfun IMU Fusion board](https://www.sparkfun.com/products/10252) (3D accelerometer, 3D gyroscope)
- 8.4 V battery (any battery 7.4 V - 9 V that can power two motors should be Ok)

## Motors ##
Any 9V DC motors should be Ok. I used ones from Lego because they are perfectly suited to rapid prototyping. 
[<img src="_img/motors.jpg?raw=true" alt="Motors" width="640" height="480"/>]

##Power circuit##
The battery provides about 8.4 volts, the exact voltage varies depending on load. The Galileo board needs a stabilized 5V current supply over 5.6 mm jack. I took DC-DC step down converter based on LM2596 chip.

Motors are controlled by the Arduino motor shield that gets the power directly from the battery. 
[<img src="_img/power.jpg?raw=true" alt="Power circuits" width="640" height="480"/>]

##Accelerometer and gyroscopes##
It could be counterintuitive, but the robot is easier to balance if the heavy battery is placed on the very top of it. The robot then acts like an [inverted pendulum](http://en.wikipedia.org/wiki/Inverted_pendulum) that's relatively easy to control. 

Most of models I saw before place the acceleometer to the bottom of the robot, near the rotation axis. In my case the interference from the horizontal movements caused by the motors was too high and the values read from the accelerator were of very poor quality. I decided to put the accelerometer to the robot's center of gravity, that's at about 60% of the total height.  

[<img src="_img/accelerometer.jpg?raw=true" alt="Power circuits" width="480" height="640"/>]

##Microcomputer##
Intel Galileo board running Windows is the "brain" of the robot. [Here](http://windowsondevices.com) you can sign up for the Windows Developer Program for IoT. The motor shield uses four digital pins on the board:

| Pin |         Action        |
|-----|:---------------------:|
| 4   | Motor 1 - Direction   |
| 5   | Motor 1 - Speed (PWM) |
| 6   | Motor 2 - Speed (PWM) |
| 7   | Motor 2 - Direction   |

The accelerometer/gyroscope unit IMU 3000 has I2C interface and must be connected to analog pins A4 and A5 of the board:

| Galileo Pin | IMU board |
|-------------|:---------:|
| A4          | SDA       |
| A5          | SCL       |
| GND         | GND       |
| 3.3V        | VCC       |

[<img src="_img/galileo.jpg?raw=true" alt="Galileo board" width="640" height="480"/>]

### Using I2C on Galileo ###
Code example:

''' cpp
#include <Wire.h>
#define GYRO 0x68         // gyro I2C address
#define REG_GYRO_X 0x1D   // IMU-3000 Register address for GYRO_XOUT_H
#define ACCEL 0x53        // Accel I2c Address
#define ADXL345_POWER_CTL 0x2D

void setup()
{
	Wire.begin();
	// Set Gyro settings
	// Sample Rate 1kHz, Filter Bandwidth 42Hz, Gyro Range 500 d/s 
	writeTo(GYRO, 0x16, 0x0B);
	//set accel register data address
	writeTo(GYRO, 0x18, 0x32);
	// set accel i2c slave address
	writeTo(GYRO, 0x14, ACCEL);
	// Set passthrough mode to Accel so we can turn it on
	writeTo(GYRO, 0x3D, 0x08);
	// set accel power control to 'measure'
	writeTo(ACCEL, ADXL345_POWER_CTL, 8);
	//cancel pass through to accel, gyro will now read accel for us   
	writeTo(GYRO, 0x3D, 0x28);
}

byte buffer[12];   // Array to store ADC values 
void loop()
{
// First set the register start address for X on Gyro  
   Wire.beginTransmission(GYRO);
   Wire.write(REG_GYRO_X); //Register Address GYRO_XOUT_H
   Wire.endTransmission();

// Now read the 12 data bytes
   Wire.requestFrom(GYRO, 12); // Read 12 bytes
   i = 0;
   while (Wire.available())
   {
      buffer[i] = Wire.read();
      i++;
   } 
}

void writeTo(int device, byte address, byte val) {
	Wire.beginTransmission(device); // start transmission to device 
	Wire.write(address);            // send register address
	Wire.write(val);                // send value to write
	Wire.endTransmission();         // end transmission
}

'''