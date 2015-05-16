// Apr 11, 2015. Husky Robotics, made by Electrical Team
#include "Arduino.h"
#include <Servo.h>
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <Wire.h>


// WIRELESS COMMUNICATION
// Port to listen for UDP connections on 
const int UDP_PORT = 8888;
IPAddress ip(192, 168, 1, 177);
EthernetUDP Udp;
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet
char  ReplyBuffer[] = "acknowledged";       // a string to send back
unsigned long timeLastPacket; // to be set to millis() in main code. millis() returns the current system time
int networkStatus = 1;
int leftPower   = 128;
int rightPower  = 128;
int arm[3] = {1, 1, 1};
int hand[3] = {1, 1, 1};
int misc[4] = {1, 1, 1, 1};

// Need Analog input with male pin
#define BAUD_RATE 9600

int potValue;
int sendValue;


// MOTOR CONSTANTS

// Need PWM input with male pin for motor controller
// connect to RS232
Servo leftMotor;
Servo rightMotor;
#define MOTOR_PIN_L   3   // connected to didigal 6      GREY WIRE
#define MOTOR_PIN_R   5  // connected to didigal 5       WHITE WIRE
int handPos[3] = {90, 90, 90};
// Need PWM input with male pin for the direct arm motor controller
Servo armMotor[3];
Servo handMotor[4];
const int HAND[4] = {28, 27, 26, 25};      // pins for motor control
const int TALON_ARM[3] = {6, 7, 8};   // pins for motor control
#define NEUTRAL_FREQUENCY      1500
#define SPEEDUP_FREQUENCY      1750   // For arm
#define SPEEDDOWN_FREWQUENCY   1250   // For arm


// SENSOR PINS
#define CURRENT_SENSOR_PIN  A1  // connected to analog 1     for monitoring current on the big ass battery
#define COMPRESSOR_PIN      A0  // connected to analog 0     for reading pressure
#define COMPRESSOR_CONTROL  23  // connected to digital 23   for increasing pressure on pneumatic suspension

// CONTROL AND LOGIC CONSTANTS
#define TIMEOUT  1000  // in milliseconds. This is to test to see if there is still wireless connection
#define MIN_FREQUENCY       1250
#define MAX_FREQUENCY       1750
