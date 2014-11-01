// Controlling a servo position using a potentiometer (variable resistor) 
// by Michal Rinott <http://people.interaction-ivrea.it/m.rinott> 

#include <Servo.h> 
 
Servo servoX;  // create servo object to control a servo 
Servo servoY;  // create servo object to control a servo 
 
int pinX = 10;  
int pinY = 11;  
 
void setup() 
{ 
  servoX.attach(pinX);  // attaches the servoX on pin pinX
  servoY.attach(pinY);  // attaches the servoY on pin pinY  
  servoX.write(90);
  servoX.write(90);  
} 
 
void loop() 
{ 
    int del = 20;
    int x, y;
    for (x = 90; x > 30; x--)
    {
      servoX.write(x);  
      delay(del);
    }
    for (x = 30; x < 160; x++)
    {
      servoX.write(x);  
      delay(del);
    }
    for (x = 160; x > 90; x--)
    {
      servoX.write(x);  
      delay(del);
    }
    /*
    for (y = 90; y > 60; y--)
    {
      servoY.write(y);  
      delay(del);
    }
    for (y = 30; y < 120; y++)
    {
      servoY.write(y);  
      delay(del);
    }
    for (y = 120; y > 90; y--)
    {
      servoY.write(y);  
      delay(del);
    }
    */
    delay(3000);
} 
