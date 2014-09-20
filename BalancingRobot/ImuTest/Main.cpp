// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "arduino.h"
#include <Wire.h>

int _tmain(int argc, _TCHAR* argv[])
{
	return RunArduinoSketch();
}

/* IMU Fusion Board - ADXL345 & IMU3000
Example Arduino Sketch to read the Gyro and Accelerometer Data

Written by www.hobbytronics.co.uk
See the latest version at www.hobbytronics.co.uk/arduino-adxl345-imu3000
08-Apr-2011
*/

#define GYRO 0x68         // gyro I2C address
#define REG_GYRO_X 0x1D   // IMU-3000 Register address for GYRO_XOUT_H
#define ACCEL 0x53        // Accel I2c Address
#define ADXL345_POWER_CTL 0x2D

byte buffer[12];   // Array to store ADC values 
int16_t gyro_x;
int16_t gyro_y;
int16_t gyro_z;
int16_t accel_x;
int16_t accel_y;
int16_t accel_z;
int i;
#include <Wire.h>

// Write a value to address register on device
void writeTo(int device, byte address, byte val) {
	Wire.beginTransmission(device); // start transmission to device 
	Wire.write(address);             // send register address
	Wire.write(val);                 // send value to write
	Wire.endTransmission();         // end transmission
}

void setup()
{
	wprintf_s(L"Initialization...");
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
	wprintf_s(L"Done\n");
}

int n = 0;

void loop()
{
	// Read the Gyro X, Y and Z and Accel X, Y and Z all through the gyro

	// First set the register start address for X on Gyro  
	Wire.beginTransmission(GYRO);
	Wire.write(REG_GYRO_X); //Register Address GYRO_XOUT_H
	Wire.endTransmission();

	// New read the 12 data bytes
	//Wire.beginTransmission(GYRO);
	Wire.requestFrom(GYRO, 12); // Read 12 bytes
	i = 0;
	while (Wire.available())
	{
		buffer[i] = Wire.read();
		i++;
	}
	//Wire.endTransmission();

	//Combine bytes into integers
	// Gyro format is MSB first

	gyro_x = (int16_t)(buffer[0]) << 8 | buffer[1];
	gyro_y = (int16_t)(buffer[2]) << 8 | buffer[3];
	gyro_z = (int16_t)(buffer[4]) << 8 | buffer[5];

	accel_y = (int16_t)(buffer[7]) << 8 | buffer[6];
	accel_x = (int16_t)(buffer[9]) << 8 | buffer[8];
	accel_z = (int16_t)(buffer[11]) << 8 | buffer[10];

	/*
	wprintf_s(L"%02X%02X\t%02X%02X\t%02X%02X\t\t%d\n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], gyro_y);

	gyro_x = buffer[0] << 8 | buffer[1];
	gyro_y = buffer[2] << 8 | buffer[3];
	gyro_z = buffer[4] << 8 | buffer[5];
	*/
	

	
	// Accel is LSB first. Also because of orientation of chips
	// accel y output is in same orientation as gyro x
	// and accel x is gyro -y
	/*
	accel_y = buffer[7] << 8 | buffer[6];
	accel_x = buffer[9] << 8 | buffer[8];
	accel_z = buffer[11] << 8 | buffer[10];
	*/

	if (n % 20 == 0)
	{
		wprintf_s(L"%d\tgX:%d\tgY:%d\tgZ:%d\t\taX:%d\taY:%d\taZ:%d\n", n, gyro_x, gyro_y, gyro_z, accel_x, accel_y, accel_z);
	}
	n++;
}