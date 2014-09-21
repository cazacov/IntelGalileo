// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "arduino.h"

int _tmain(int argc, _TCHAR* argv[])
{
	return RunArduinoSketch();
}

int pin_motor_a_dir = 4;
int pin_motor_b_dir = 7;

int pin_motor_a_speed = 5;
int pin_motor_b_speed = 6;


void setup()
{
	pinMode(pin_motor_a_dir, OUTPUT);
	pinMode(pin_motor_b_dir, OUTPUT);
	pinMode(pin_motor_a_speed, OUTPUT);
	pinMode(pin_motor_b_speed, OUTPUT);

	wprintf(L"Motor shield initialized\n");

	wprintf(L"Motor shield initialized\n");
}

// the loop routine runs over and over again forever:
void loop()
{
	digitalWrite(pin_motor_a_dir, HIGH);
	digitalWrite(pin_motor_b_dir, HIGH);
	analogWrite(pin_motor_a_speed, 128);
	analogWrite(pin_motor_b_speed, 128);

	delay(1000);
}