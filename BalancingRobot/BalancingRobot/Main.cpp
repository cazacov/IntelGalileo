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
	/* 
	PID coefficients may vary depending on mechanical properties of the robot/motors/battery
	Here are some instructions how to tune the PID
	http://robotics.stackexchange.com/questions/167/what-are-good-strategies-for-tuning-pid-loops 
	*/

	// Angle regulator. This PID adjusts the desired angle (normally 0) depending 
	// on the mean spead of the robot. The goal is to keep the mean speed near 0. 
	// (robot is staying on one place and does not not drive away)
	angleRegulator.init(-0.02, 0, 0); // P is negative, because to compensate positive speed we mast tilt the robot little bit back 

	// Speed regulator. This PID gets the desired angle from the angle regulator and 
	// adjusts the acceleartion (power applied to motors) to keep the angle near the desired value.
	speedRegulator.init(35, 0.2, 0);

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
		float actualAngle, deltaAngle;
		while (micros() < nextIteration)
		{
			// do nothing 
		}
		unsigned long now = micros();
		gyroscope.getAngleFiltered(actualAngle, deltaAngle, now);
		
		targetAngle = angleRegulator.getResult(speedIntegrator.getSum(), 0, now - lastIteration);

		float motorSpeed = 0;
		motorSpeed = speedRegulator.getResult(actualAngle - targetAngle, deltaAngle, now - lastIteration);

		n++;
		if (n % 20 == 0) // Print on every 20th iteration
		{
			wprintf(L"%d\t%f\t%f\t%f\t%f\n", n, targetAngle, actualAngle, deltaAngle, motorSpeed);
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