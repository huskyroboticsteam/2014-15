// May 22, 2015. Husky Robotics, made by Electrical Team.......
#include "Arduino.h"
#include <Adafruit_GPS.h>  // include this file in the Arduino libraries folder
#include <Servo.h>
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LSM303.h>

// WIRELESS COMMUNICATION
// Port to listen for UDP connections on 
const int UDP_PORT = 8888;
//IPAddress ip(Ethernet.localIP());
// IPAddress ip(192, 168, 1, 177);
EthernetUDP Udp;
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress DestinationAddress(192, 168, 1, 3);
unsigned int DestinationPort = 8888;
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet
char  ReplyBuffer[] = "acknowledged";       // a string to send back
unsigned long timeLastPacket; // to be set to millis() in main code. millis() returns the current system time
int networkStatus = 1;
int leftPower   = 128;
int rightPower  = 128;
int arm[3] = {1, 1, 1};
int hand[4] = {1, 1, 1, 1};
int misc[4] = {1, 1, 1, 1};
int cameraPanTilt[4] = {0, 0, 0, 0};
int digitalOutputs[] = {38, 40, 42, 44, 46, 48, 50, 52};
// Need Analog input with male pin
#define BAUD_RATE 9600
int potValue;
int sendValue;


// MOTOR CCONTROL
// Need PWM input with male pin for motor controller
// connect to RS232
Servo leftMotor;
Servo rightMotor;
#define MOTOR_PIN_L   3   // connected to didigal 6      GREY WIRE
#define MOTOR_PIN_R   5  // connected to didigal 5       WHITE WIRE
int handPos[3] = {90, 90, 90};
// Need PWM input with male pin for the direct arm motor controller
Servo armMotor[3];
Servo handMotor[3];
const int GRIPPER[] = {33, 35};    // Pins for opening/closing the grippers.
const int HAND[3] = {2, 4, 9};      // pins for motor control
const int TALON_ARM[3] = {6, 7, 8};   // pins for motor control
int compressorStateOld = 0;
#define NEUTRAL_FREQUENCY      1500
#define SPEEDUP_FREQUENCY      1650   // For arm // was 1750 changed for pan tilt
#define SPEEDDOWN_FREQUENCY   1350   // For arm // was 1250 changed for pan tilt
// MIN AND MAX HAND SERVO VALUES
#define MIN_HAND  50
#define MAX_HAND  104
// Max and min pressures are COMPRESSOR_PRESSURE +- COMPRESSOR_BAND.
#define COMPRESSOR_PRESSURE  140
#define COMPRESSOR_BAND      20


// SENSOR PINS
#define CURRENT_SENSOR_PIN  A3  // connected to analog 1     for monitoring current on the big ass battery
#define COMPRESSOR_PIN      A0  // connected to analog 0     for reading pressure
#define COMPRESSOR_CONTROL  36  // connected to digital 2   for increasing pressure on pneumatic suspension
#define PH_SENSOR           A5

// CONTROL AND LOGIC CONSTANTS
#define TIMEOUT  1000  // in milliseconds. This is to test to see if there is still wireless connection
#define MIN_FREQUENCY       1250
#define MAX_FREQUENCY       1750
#define ALARM_PIN           40   // connected to digital 40
#define DANGER_CURRENT      85  // Amps


// GPS AND COMPASS CONSTANTS AND VARIABLES
char GPSbuff[50];
uint32_t GPStimer = millis();
SoftwareSerial GPS_Port(A9, A8);
// A8 plugs into RX, A9 into TX
Adafruit_GPS GPS(&GPS_Port);
// LSM303 compass;

