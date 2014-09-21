#pragma once
#include "Integrator.h"

class Regulator
{
private:
	float phi0;
	float deltaPhi0;
	float integral;
	float KP;
	float KI;
	float KD;
	Integrator* integrator;
public:
	Regulator(int integratorLength);
	~Regulator();
	void init(float pKP, float pKI, float pKD);
	float getResult(float currentValue, float deltaValue, long timeMicros);
};

