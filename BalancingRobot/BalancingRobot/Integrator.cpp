#include "Integrator.h"
#include <stdlib.h>

Integrator::Integrator(int capacity)
{
	this->capacity = capacity;
	values = (float*)malloc(sizeof(float)* capacity);
	for (int i = 0; i < capacity; i++)
	{
		values[i] = 0;
	}
	index = 0;
}

void Integrator::pushValue(float newValue)
{
	values[index++] = newValue;
	index %= capacity;
}

float Integrator::getSum()
{
	float result = 0;
	for (int i = 0; i < capacity; i++)
	{
		result += values[i];
	}
	return result/capacity;
}

Integrator::~Integrator()
{
	free(values);
}
