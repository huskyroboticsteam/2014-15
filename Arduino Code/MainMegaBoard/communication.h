// Start from 2013's code made by Talyor Cramer
#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>         // UDP library from: bjoern@cs.stanford.edu 12/30/2008
#include <Wire.h>

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

// MAC address, IP address, and port for UDP
boolean hasIP = false;
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 177);
unsigned int localPort = 5005;
const int TIMEOUT = 1000;

// buffers for receiving and sending data
char packetBuffer[96]; //buffer to hold incoming packet,
char  ReplyBuffer[] = "acknowledged";       // a string to send back
unsigned long timeLastPacket = millis() - TIMEOUT;

// Recieved Data
int leftPower   = 128;
int rightPower  = 128;
int arm[4] = {
  1, 1, 1, 1};
int hand[3] = {
  1, 1, 1};
int misc[4] = {
  1, 1, 1, 1};
  
// Changing values
int handPos[3] = {90, 90, 90};

// Sent Data
int pressureValue  = 0;

