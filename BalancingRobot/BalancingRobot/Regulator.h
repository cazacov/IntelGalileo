#pragma once
#include "Gyroscope.h"
#include "Integrator.h"

#define INTEGRAL_MEMORY_LENGTH 50

class Regulator
{
private:
	float phi0;
	float deltaPhi0;
	float integral;
	float KP;
	float KI;
	float KD;
	float KSI;
	float memory[INTEGRAL_MEMORY_LENGTH];

	void pushToMemory(float newValue);
	float getIntegral();
	int memoryIndex;
	Integrator* speedIntegrator;
public:
	Regulator();
	~Regulator();
	void init(void);
	void calibrate(Gyroscope* gyroscope);
	float getNextSpeed(float phi, float deltaPhi, int timeMs);
};

