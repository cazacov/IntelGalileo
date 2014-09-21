#include "Regulator.h"
#include "stdafx.h"
#include "arduino.h"

Regulator::Regulator(int integratorLength)
{
	integrator = new Integrator(integratorLength);
}

Regulator::~Regulator()
{
	if (integrator != NULL)
	{
		delete integrator;
		integrator = NULL;
	}
}

void Regulator::init(float pKP, float pKI, float pKD)
{
	KP = pKP;
	KI = pKI;
	KD = pKD;
}

float Regulator::getResult(float currentValue, float deltaValue, long timeMicros)
{
	integrator->pushValue(currentValue);
	float result = currentValue * KP + deltaValue * KD + integrator->getSum() * KI;
	return result;
}
