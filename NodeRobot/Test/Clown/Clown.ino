/*************************************************** 
  This is a library for our I2C LED Backpacks

  Designed specifically to work with the Adafruit LED Matrix backpacks 
  ----> http://www.adafruit.com/products/872
  ----> http://www.adafruit.com/products/871
  ----> http://www.adafruit.com/products/870

  These displays use I2C to communicate, 2 pins are required to 
  interface. There are multiple selectable I2C addresses. For backpacks
  with 2 Address Select pins: 0x70, 0x71, 0x72 or 0x73. For backpacks
  with 3 Address Select pins: 0x70 thru 0x77

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/
#include <Arduino.h>
#include <Servo.h> 
//#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

void turnAround();

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

Servo servoX;  // create servo object to control a servo 
int pin_motor_a_dir = 4;
int pin_motor_b_dir = 7;

int pin_motor_a_speed = 5;
int pin_motor_b_speed = 6;

void setup() {
  Serial.begin(9600);
  Serial.println("8x8 LED Matrix Test");
  servoX.attach(10);  // attaches the servoX on pin pinX  
  servoX.write(90);  
  matrix.begin(0x70);  // pass in the address
  
  pinMode(pin_motor_a_dir, OUTPUT);
    pinMode(pin_motor_b_dir, OUTPUT);
    pinMode(pin_motor_a_speed, OUTPUT);
    pinMode(pin_motor_b_speed, OUTPUT);

    // Stop motors
    digitalWrite(pin_motor_a_speed, 0); 
    digitalWrite(pin_motor_b_speed, 0); 
}

static const uint8_t PROGMEM
  smile_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10100101,
    B10011001,
    B01000010,
    B00111100 },
  neutral_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10111101,
    B10000001,
    B01000010,
    B00111100 },
  frown_bmp[] =
  { B00111100,
    B01000010,
    B10100101,
    B10000001,
    B10011001,
    B10100101,
    B01000010,
    B00111100 };

void loop() {
  servoX.write(90);
  matrix.clear();
  matrix.setRotation(3);  
  matrix.drawBitmap(0, 0, smile_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(1000);
  matrix.clear();
  
  servoX.write(30);
  delay(1000);
  matrix.clear();
  matrix.setRotation(3);  
  matrix.drawBitmap(0, 0, smile_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(1000);
  matrix.clear();
  
  servoX.write(120);
  delay(1000);
  matrix.clear();
  matrix.setRotation(3);  
  matrix.drawBitmap(0, 0, smile_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(500);
  matrix.clear();
  
  servoX.write(90);
  
  delay(1000);

  matrix.setTextSize(1);
  matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  matrix.setTextColor(LED_ON);
  for (int8_t x=0; x>=-36; x--) {
    matrix.clear();
    matrix.setCursor(x,0);
    matrix.print("Hello");
    matrix.writeDisplay();
    delay(100);
  }
  matrix.setRotation(3);
  for (int8_t x=7; x>=-48; x--) {
    matrix.clear();
    matrix.setCursor(x,0);
    matrix.print("Meetup!");
    matrix.writeDisplay();
    delay(100);
  }

  delay(1000);
  matrix.clear();
  matrix.setRotation(3);  
  matrix.drawBitmap(0, 0, smile_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(1000);
  matrix.clear();
  for (int8_t x=7; x>=-126; x--) {
    matrix.clear();
    matrix.setCursor(x,0);
    matrix.print("'Clown in the Cloud'");
    matrix.writeDisplay();
    delay(100);
  }
  delay(1000);
  turnAround();
}

void turnAround()
{
   // Motor A
    digitalWrite(pin_motor_a_dir, HIGH);    // forward
    //analogWrite(pin_motor_a_speed, 255);    // 100% power

    // Motor B
    digitalWrite(pin_motor_b_dir, LOW);     // backward
    //analogWrite(pin_motor_b_speed, 255);    // 50% power
   digitalWrite(pin_motor_a_speed, HIGH); 
    digitalWrite(pin_motor_b_speed, HIGH); 
   delay(1350);
   // Stop motors
    digitalWrite(pin_motor_a_speed, 0); 
    digitalWrite(pin_motor_b_speed, 0); 
}
