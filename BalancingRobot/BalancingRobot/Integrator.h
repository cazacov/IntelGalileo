#pragma once
class Integrator
{
private:
	int capacity;
	int index;
	float* values;
public:
	Integrator(int capacity);
	~Integrator();

	void pushValue(float newValue);
	float getSum();
};

