// Mar 7, 2015. Husky Robotics, made by Electrical Team
// Using the PMW to communicate to the MDC2230 motor controller
// Dual motor, only forwards and backwards
#include <Arduino.h>

// void driveMotorFullSpeed(int potValue) {
void driveMotor() {
    // PWM have pulse seconds from 1000 microseconds to 2000
  int leftSignal = map(leftPower, 0, 255, MIN_FREQUENCY, MAX_FREQUENCY);
  int rightSignal= map(rightPower, 0, 255, MIN_FREQUENCY, MAX_FREQUENCY);
  if (leftSignal < 1480 || leftSignal > 1520 || rightSignal < 1480 || leftSignal > 1520) {
    leftMotor.writeMicroseconds(leftSignal);
    rightMotor.writeMicroseconds(-rightSignal);
  }	else {
    MotorStop();
  }
}

void MotorStop() {
   leftMotor.writeMicroseconds(NEUTRAL_FREQUENCY);
   rightMotor.writeMicroseconds(NEUTRAL_FREQUENCY);
}
