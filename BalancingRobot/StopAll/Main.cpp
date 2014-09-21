#include "stdafx.h"
#include "arduino.h"

int _tmain(int argc, _TCHAR* argv[])
{
    return RunArduinoSketch();
}

int pin_motor_a_dir = 7;
int pin_motor_b_dir = 4;

int pin_motor_a_speed = 6;
int pin_motor_b_speed = 5;


void setup()
{
	pinMode(pin_motor_a_dir, OUTPUT);
	pinMode(pin_motor_b_dir, OUTPUT);
	pinMode(pin_motor_a_speed, OUTPUT);
	pinMode(pin_motor_b_speed, OUTPUT);

	wprintf(L"Motor shield initialized\n");

	digitalWrite(pin_motor_a_dir, LOW);
	digitalWrite(pin_motor_b_dir, LOW);
	analogWrite(pin_motor_a_speed, 0);
	analogWrite(pin_motor_b_speed, 0);
	wprintf(L"Motors stopped\n");
	exit(0);
}

// the loop routine runs over and over again forever:
void loop()
{
}