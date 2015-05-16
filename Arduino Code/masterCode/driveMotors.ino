// Mar 7, 2015. Husky Robotics, made by Electrical Team
// Using the PMW to communicate to the MDC2230 motor controller
// Dual motor, only forwards and backwards
//#include <Arduino.h>
//#include "megaBoardDefine.h"

void writeToDriveMotors()
{
    if(networkStatus == 1) {
        // Refresh timeout
        timeLastPacket = millis();

        // Process new values;t
        leftMotor.writeMicroseconds(map(leftPower, 0, 255, MIN_FREQUENCY, MAX_FREQUENCY));
        rightMotor.writeMicroseconds(map(rightPower, 255, 0, MIN_FREQUENCY, MAX_FREQUENCY));
        //Serial.println("WRITTEN");
    }
}

void attachDriveMotors()
{
    // Attach the driving motors
    leftMotor.attach(MOTOR_PIN_L);
    rightMotor.attach(MOTOR_PIN_R);
}


int dirToMicroseconds(int dir) {
  if(dir == 0) {
    return MIN_FREQUENCY;
  }
  if(dir == 2) {
    return MAX_FREQUENCY;
  }
  return NEUTRAL_FREQUENCY;
}


void driveMotorFullSpeed() {
      	// For Joystick
    // potValue = analogRead(potPin);
    
    // For motor current testing
    potValue = 1023;
    
      	// PWM have pulse seconds from 1000 microseconds to 2000
      	sendValue = map(potValue, 0, 1023, 1250, 1750);
      	if (sendValue < 1480 || sendValue > 1520)
      	{
      		leftMotor.writeMicroseconds(sendValue);
      		rightMotor.writeMicroseconds(sendValue);
      	}	else {
      		leftMotor.writeMicroseconds(1500);
      		rightMotor.writeMicroseconds(1500);
      	}
    // delay(10);
}
