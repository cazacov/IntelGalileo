// Uses DFRobot L298P Motor Shield v1.1

#include "Motors.h"
#include "arduino.h"

#define PIN_MOTOR_A_DIR		4
#define PIN_MOTOR_B_DIR		7
#define PIN_MOTOR_A_SPEED	5
#define PIN_MOTOR_B_SPEED	6

Motors::Motors()
{
}


Motors::~Motors()
{
}

void Motors::init()
{
	pinMode(PIN_MOTOR_A_SPEED, OUTPUT);
	digitalWrite(PIN_MOTOR_A_SPEED, LOW);
	pinMode(PIN_MOTOR_B_SPEED, OUTPUT);
	digitalWrite(PIN_MOTOR_B_SPEED, LOW);

	pinMode(PIN_MOTOR_A_DIR, OUTPUT);
	pinMode(PIN_MOTOR_B_DIR, OUTPUT);
	digitalWrite(PIN_MOTOR_A_DIR, HIGH);
	digitalWrite(PIN_MOTOR_B_DIR, HIGH);
	delay(1000);
}

void Motors::setSpeedBoth(float speed)
{
	digitalWrite(PIN_MOTOR_A_DIR, speed >= 0 ? HIGH : LOW);
	digitalWrite(PIN_MOTOR_B_DIR, speed >= 0 ? HIGH : LOW);

	int spdInt = 30 + fabs(speed) * 225.5 / 100.0;

	if (spdInt > 255)
	{
		spdInt = 255;
	}
	if (spdInt == 0)
	{
		digitalWrite(PIN_MOTOR_A_SPEED, LOW);
		digitalWrite(PIN_MOTOR_B_SPEED, LOW);
	}
	else
	{
		analogWrite(PIN_MOTOR_A_SPEED, spdInt);
		analogWrite(PIN_MOTOR_B_SPEED, spdInt);
	}
}

void Motors::stopAll()
{
	digitalWrite(PIN_MOTOR_A_SPEED, LOW);
	digitalWrite(PIN_MOTOR_B_SPEED, LOW);
}