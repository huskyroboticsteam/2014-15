// Apr 11, 2015. Husky Robotics, made by Electrical Team
#include <Arduino.h>
#include <Servo.h>

// Need Analog input with male pin
const int BAUD_RATE = 9600;
const int currentSensorPin = A1;

int potPin = A0;
int potValue;
int sendValue;

// Need PWM input with male pin for motor controller
// connect to RS232
Servo leftMotor, rightMotor;
const int motorPin1 = 12;
const int motorPin2 = 13;

// Need PWM input with male pin for the direct arm motor controller
// Talon Senior
Servo armMotor[3];
const int TALON_ARM[3] = {2, 3, 4};
const int NEUTRAL_FREQUENCY = 1500;
const int SPEEDUP_FREQUENCY = 1750;
const int SPEEDDOWN_FREWQUENCY = 1250;
const int MIN_FREQUENCY = 1001; 
const int MAX_FREQUENCY = 2041;

// Turn table continous rotation servo
const int CONT_SERVO_CENTER = 80; //in degrees 
