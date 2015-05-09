// Mar 7, 2015. Husky Robotics, made by Electrical Team
// Using the PMW to communicate to the MDC2230 motor controller
// Dual motor, only forwards and backwards
#include <Arduino.h>

void driveMotorFullSpeed(int potValue) {
        // For motor current testing

        
  	// PWM have pulse seconds from 1000 microseconds to 2000
  	sendValue = map(potValue, 0, 1023, 1250, 1750);
  	if (sendValue < 1480 || sendValue > 1520)
  	{
  		leftMotor.writeMicroseconds(sendValue);
  		rightMotor.writeMicroseconds(-sendValue);
  	}	else {
  		leftMotor.writeMicroseconds(1500);
  		rightMotor.writeMicroseconds(1500);
  	}
    // delay(10);
}
