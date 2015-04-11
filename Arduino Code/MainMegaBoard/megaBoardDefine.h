// Apr 11, 2015. Husky Robotics, made by Electrical Team
#include <Arduino.h>
#include <Servo.h>

const int BAUD_RATE = 9600;
int currentSensorPin = A1;

int potPin = A0;
int potValue;
int sendValue;

Servo motor1;
Servo motor2;
int motorPin1 = 3;
int motorPin2 = 5;
