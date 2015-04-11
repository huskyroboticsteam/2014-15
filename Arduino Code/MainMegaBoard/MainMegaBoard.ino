// Apr 11, 2015. Husky Robotics, made by Electrical Team

#include <Arduino.h>
#include "megaBoardDefine.h"
#include <Servo.h>

void setup() {
  Serial.begin(BAUD_RATE);
  motor1.attach(motorPin1);
  motor2.attach(motorPin2);
}

void loop() {
  driveMotorFullSpeed();
  getReadingFromCurrentSensor();
}
