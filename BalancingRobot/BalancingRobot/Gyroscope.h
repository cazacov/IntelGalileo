#pragma once

#include "stdafx.h"
#include "arduino.h"

class Gyroscope
{
private:
	float phi0;
	float deltaPhi0;
	unsigned long lastMeasureTime;
	float lastAngleY;
	// Write a value to address register on device
	void writeTo(int device, byte address, byte val);
	void rawRead(int16_t &accX, int16_t &accY, int16_t &accZ, int16_t &gyroX, int16_t &gyroY, int16_t &gyroZ);
public:
	Gyroscope();
	~Gyroscope();

	void init(void);
	void calibrate();
	void getAngleY(float &phi, float &deltaPhi);
	void getAngleFiltered(float &phi, float &deltaPhi, unsigned long measureTime);
};

