// Mar 7, 2015. Husky Robotics, made by Electrical Team
// Using the PMW to communicate to the MDC2230 motor controller
// Dual motor, only forwards and backwards

int potPin = A0;
int potValue;
int setValue;
#include <Servo.h>

Servo motor1;
Servo motor2;

void setup() {
	Serial.begin(115200);
	motor1.attach(3);
	motor2.attach(5);
}

void loop() {
  	potValue = analogRead(potPin);
  	// PWM have pulse seconds from 1000 microseconds to 2000
  	sendValue = map(potValue, 0, 1023, 1250, 1750);
  	if (sendValue < 1480 || sendValue > 1520)
  	{
  		motor1.writeMicroseconds(potValue);
  		motor2.writeMicroseconds(potValue);
  	}	else {
  		motor1.writeMicroseconds(1500);
  		motor2.writeMicroseconds(1500);
  	}
}