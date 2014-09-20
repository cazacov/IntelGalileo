// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "arduino.h"
#include "Gyroscope.h"
#include "Motors.h"
#include "Regulator.h"
#include "KeyboardController.h"

#define TICK_LENGTH 10

int _tmain(int argc, _TCHAR* argv[])
{
    return RunArduinoSketch();
}

Gyroscope gyroscope;
Motors motors;
Regulator regulator;
KeyboardController keyboard;

void setup()
{
	motors.init();
	gyroscope.init();
	keyboard.init();
	wprintf(L"Press Esc to exit\n");

	/*int n = 0;
	unsigned long end = millis() + 1000;
	while (millis() < end)
	{
		float p, d;
		gyroscope.getAngleY(p, d);
		n++;
	}
	wprintf(L"Measures per second: %d\n", n);*/
}

// the loop routine runs over and over again forever:
void loop()
{
	wprintf(L"Calibration in 3 seconds\n");
	delay(3000);
	wprintf(L"Calibrating...");
	gyroscope.calibrate();
	wprintf(L"Done\n");

	// main cycle
	regulator.init();
	delay(100);

	unsigned long lastIteration = millis();
	unsigned long nextIteration = lastIteration + TICK_LENGTH;

	int n = 0;

	do {
		float phi, delta;
		while (millis() < nextIteration)
		{
			// do nothing 
		}
		unsigned  long now = millis();
		gyroscope.getAngleFiltered(phi, delta, now);
		
		float motorSpeed = 0;
		motorSpeed = regulator.getNextSpeed(phi, delta, now - lastIteration);

		n++;

		if (n % 10 == 0)
		{
			wprintf(L"%d %f\t%f\t%f\n", n, phi, delta, motorSpeed);
		}

		motors.setSpeedBoth(motorSpeed);
		lastIteration = now;
		nextIteration = now + TICK_LENGTH;

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