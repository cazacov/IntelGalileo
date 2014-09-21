// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "arduino.h"
#include "Gyroscope.h"
#include "Motors.h"
#include "Regulator.h"
#include "KeyboardController.h"

#define TICK_PER_SECOND 75
#define TICK_LENGTH_MICROSECONDS 1000000L / TICK_PER_SECOND

int _tmain(int argc, _TCHAR* argv[])
{
    return RunArduinoSketch();
}

Gyroscope gyroscope;
Motors motors;
Regulator angleRegulator(TICK_PER_SECOND);
Regulator speedRegulator(TICK_PER_SECOND / 2);
KeyboardController keyboard;
Integrator speedIntegrator(TICK_PER_SECOND);

float targetSpeed = 0;
float targetAngle = 0;

void setup()
{
	motors.init();
	gyroscope.init();
	keyboard.init();
	angleRegulator.init(-0.1, 0, 0);
	speedRegulator.init(30, 0, 0);
	wprintf(L"Press Esc to exit\n");
}

// the loop routine runs over and over again forever:
void loop()
{
	wprintf(L"Calibration in 3 seconds\n");
	delay(3000);
	wprintf(L"Calibrating...");
	gyroscope.calibrate();

	wprintf(L"Cycle tyme in microseconds: %ld \n", TICK_LENGTH_MICROSECONDS);

	// main cycle
	delay(100);

	unsigned long lastIteration = micros();
	unsigned long nextIteration = lastIteration + TICK_LENGTH_MICROSECONDS;

	int n = 0;

	do {
		float phi, delta;
		while (micros() < nextIteration)
		{
			// do nothing 
		}
		unsigned long now = micros();
		gyroscope.getAngleFiltered(phi, delta, now);
		
		targetAngle = angleRegulator.getResult(speedIntegrator.getSum(), 0, now - lastIteration);

		float motorSpeed = 0;
		motorSpeed = speedRegulator.getResult(phi - targetAngle, delta, now - lastIteration);

		n++;
		if (n % 10 == 0)
		{
			wprintf(L"%d\t%f\t%f\t%f\t%f\n", n, targetAngle, phi, delta, motorSpeed);
		}

		motors.setSpeedBoth(motorSpeed);
		speedIntegrator.pushValue(motorSpeed);
		lastIteration = now;
		nextIteration = now + TICK_LENGTH_MICROSECONDS;

		keyboard.processEvents();
		if (keyboard.shouldExit())
		{
			break;
		}
	} while (true);
	
	motors.stopAll();
	wprintf(L"Exiting...\n");
	exit(0);
}