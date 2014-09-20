#include "Regulator.h"
#include "stdafx.h"
#include "arduino.h"

Regulator::Regulator()
{
	KP = 30;
	KD = 0;
	KI = 0;
	KSI = 0.01;
	speedIntegrator = new Integrator(20);
}

Regulator::~Regulator()
{
	if (speedIntegrator != NULL)
	{
		delete speedIntegrator;
		speedIntegrator = NULL;
	}
}

void Regulator::calibrate(Gyroscope* gyroscope)
{
	int calibrationEnd = millis() + 2 * 1000; // 2 seconds

	int iterationCount = 0;
	double meanPhi = 0;
	double meanDeltaPhi = 0;

	while (millis() < calibrationEnd)
	{
		float phi, deltaPhi;
		gyroscope->getAngleY(phi, deltaPhi);
		meanPhi += phi;
		meanDeltaPhi += deltaPhi;
		iterationCount++;
	}

	phi0 = meanPhi / iterationCount;
	deltaPhi0 = meanDeltaPhi / iterationCount;

	Log(L"Calibration done. Phi0=%f\t Delta0=%f\n", phi0, deltaPhi0);
}

void Regulator::init(void)
{
	integral = 0;
	for (int i = 0; i < INTEGRAL_MEMORY_LENGTH; i++)
	{
		memory[i] = 0;
	}
	int memoryIndex = 0;
}

void Regulator::pushToMemory(float newValue)
{
	memory[memoryIndex++] = newValue;
	if (memoryIndex >= INTEGRAL_MEMORY_LENGTH)
	{
		memoryIndex = 0;
	}
}

float Regulator::getIntegral()
{
	float sum = 0;
	for (int i = 0; i < INTEGRAL_MEMORY_LENGTH; i++)
	{
		sum += memory[i];
	}
	return sum / INTEGRAL_MEMORY_LENGTH;
}

float Regulator::getNextSpeed(float phi, float deltaPhi, int timeMs)
{
	pushToMemory(phi);
	float integral = getIntegral();

	float result = phi * KP + deltaPhi * KD + integral * KI + speedIntegrator->getSum() * KSI;
	speedIntegrator->pushValue(result);
	return result;
}
