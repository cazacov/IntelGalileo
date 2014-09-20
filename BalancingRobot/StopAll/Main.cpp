// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "arduino.h"

int _tmain(int argc, _TCHAR* argv[])
{
    return RunArduinoSketch();
}

int motorADir = 7;
int motorBDir = 4;

int motorASpeed = 6;
int motorBSpeed = 5;


void setup()
{
	pinMode(motorADir, OUTPUT);
	pinMode(motorBDir, OUTPUT);
	pinMode(motorASpeed, OUTPUT);
	pinMode(motorBSpeed, OUTPUT);

	wprintf(L"Motor shield initialized\n");

	digitalWrite(motorADir, LOW);
	digitalWrite(motorBDir, LOW);
	analogWrite(motorASpeed, 0);
	analogWrite(motorBSpeed, 0);
	wprintf(L"Motors stopped\n");
}

// the loop routine runs over and over again forever:
void loop()
{
}