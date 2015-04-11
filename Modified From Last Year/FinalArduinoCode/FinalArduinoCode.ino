/*
  ethernetshieldtests.ino
 Processes sensors and UDP packets to determine motor outputs.
 */


#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>         // UDP library from: bjoern@cs.stanford.edu 12/30/2008

#include <Wire.h>

#include <Servo.h>
#include <map>
#include <string>

boolean hasIP = false;

// Motor Constants
const int TALON_LEFT = 3, TALON_RIGHT = 5,
MIN_FREQUENCY = 1001, NEUTRAL_FREQUENCY = 1500, MAX_FREQUENCY = 2041,
COMPRESSOR = 26, TALON_ARM[4] = {11, 8, 7, 6}, 
HAND[3] = {2, 3, 5}, AGAR_SPIKE[2] = {22, 24}, TIMEOUT = 1000, PRESSURE = A0;

// Motors
Servo leftMotor, rightMotor;
Servo armMotor[4];
Servo handMotor[3];

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

// MAC address, IP address, and port for UDP
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 177);
unsigned int localPort = 5005;

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


// Returns the amount of RAM Free
int freeRam ()
{
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

// Prints data about packet, packet sender
void printPacketInfo(int packetSize) {
  Serial.print("Received packet of size ");
  Serial.println(packetSize);
  Serial.print("From ");
  IPAddress remote = Udp.remoteIP();
  for (int i = 0; i < 4; i++)
  {
    Serial.print(remote[i], DEC);
    if (i < 3)
    {
      Serial.print(".");
    }
  }
  Serial.print(", port ");
  Serial.println(Udp.remotePort());
}

// Prints readable versions of packet
void printPacketValues() {
  Serial.print("Left: ");
  Serial.println(leftPower);
  Serial.print("Right: ");
  Serial.println(rightPower);

  for(int i = 0; i < 4; i++)
  {
    Serial.print("Arm:");
    Serial.println(arm[i]);
  }

  for(int i = 0; i < 3; i++)
  {
    Serial.print("Hand:");
    Serial.println(hand[i]);
  }

  for(int i = 0; i < 4; i++)
  {
    Serial.print("Misc:");
    Serial.println(misc[i]);
  }
}

void readByteAsInt(byte data, int* buffer, byte bufferSize) {
  byte mask = 0x03;

  for(byte i = 0; i < bufferSize; i++)
  {
    *buffer = data & mask;
    data >>= 2;
    buffer++;
  }
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

int processNetworkData() {
  //Serial.println(freeRam());
  // Check size of available packet
  int packetSize = Udp.parsePacket();

  // Process packet if available
  if(packetSize == 5)
  {
    hasIP=true;
    //printPacketInfo(packetBuffer);
    //Serial.println("GOOD");

    // read the packet into packetBufffer
    Udp.read(packetBuffer, 96);

    // Process packet into values
    leftPower  = ((unsigned char)packetBuffer[0]) & 0xFFFF;
    rightPower  = ((unsigned char)packetBuffer[1]) & 0xFFFF;
    readByteAsInt(packetBuffer[2], arm, 4);
    readByteAsInt(packetBuffer[3], hand, 3);
    readByteAsInt(packetBuffer[4], misc, 4);

    //printPacketValues();
    return 1;
  }
  return 0;
}

// Handle i2c Event
void receivei2c(int howMany) {
  if(howMany == 9) {
    char i2cData[8];
    Wire.read();
  
    for(int i = 0; i < 8;  i++) {
      char c = Wire.read();
      i2cData[i] = c;
    }
    
    if(hasIP) {
      Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
      Udp.write(i2cData);
      Udp.endPacket();
    }
  }
}

void setup() {

  // start the Ethernet and UDP:
  Ethernet.begin(mac,ip);
  Udp.begin(localPort);

  // i2c
  Wire.begin(4); // Join i2c with address #1
  Wire.onReceive(receivei2c);

  // Start serial
  Serial.begin(9600);

  // Initialize drive motors
  leftMotor.attach(TALON_LEFT);
  rightMotor.attach(TALON_RIGHT);
  leftMotor.writeMicroseconds(NEUTRAL_FREQUENCY);
  rightMotor.writeMicroseconds(NEUTRAL_FREQUENCY);

  for(int i = 0; i < 4; i++) {
    armMotor[i].attach(TALON_ARM[i]);
    armMotor[i].writeMicroseconds(NEUTRAL_FREQUENCY);
  }
  for(int i = 0; i < 3; i++) {
    handMotor[i].attach(HAND[i]);
  }

  pinMode(AGAR_SPIKE[0], OUTPUT);
  pinMode(AGAR_SPIKE[1], OUTPUT);
  pinMode(COMPRESSOR, OUTPUT);

  digitalWrite(AGAR_SPIKE[0], HIGH);
  digitalWrite(AGAR_SPIKE[1], HIGH);
  digitalWrite(COMPRESSOR, LOW);

  Serial.println("Intialized");
}

void loop() {
  // Check timeout, disable if necessary
  if(millis() - timeLastPacket >= TIMEOUT) {
    //Serial.println("TIMEOUT");
    leftMotor.writeMicroseconds(NEUTRAL_FREQUENCY);
    rightMotor.writeMicroseconds(NEUTRAL_FREQUENCY);
  }

  // Get sensor information
  pressureValue= analogRead(PRESSURE) * 0.363;
  //Serial.println(pressureValue);
  if(pressureValue < 125) {
    digitalWrite(COMPRESSOR, HIGH);
  } 
  else if(pressureValue > 165) {
    digitalWrite(COMPRESSOR, LOW);
  }

  int networkStatus = processNetworkData();

  if(networkStatus == 1) {
    // Refresh timeout
    timeLastPacket = millis();

    // Process new values;
    leftMotor.writeMicroseconds(map(leftPower, 0, 255, MIN_FREQUENCY, MAX_FREQUENCY));
    rightMotor.writeMicroseconds(map(rightPower, 0, 255, MIN_FREQUENCY, MAX_FREQUENCY));
    for(int i = 0; i < 4; i++) {
      armMotor[i].writeMicroseconds(dirToMicroseconds(arm[i]));
    }
    
    for(int i = 0; i < 3; i++) {
      Serial.print("Hand: ");
      Serial.print(i);
      Serial.println(hand[i]);
      if(hand[i] == 0 || hand[i] == 2) {
        if(hand[i] == 0 && handPos[i] < 180) {
          handPos[i] += 5;
        } else if(handPos[i] > 0) {
          handPos[i] -= 5;
        }
        handMotor[i].write(handPos[i]);
      }
    }

    // Compressor
    if(misc[0]) {
      digitalWrite(COMPRESSOR, HIGH);
    }

    if(misc[1] == 0) {
      digitalWrite(AGAR_SPIKE[0], HIGH);
      digitalWrite(AGAR_SPIKE[1], LOW);
    } 
    else if(misc[1] == 2) {
      digitalWrite(AGAR_SPIKE[0], LOW);
      digitalWrite(AGAR_SPIKE[1], HIGH);
    } 
    else {
      digitalWrite(AGAR_SPIKE[0], HIGH);
      digitalWrite(AGAR_SPIKE[1], HIGH);
    }
    
    // i2c Sci-Dump
    Wire.beginTransmission(42);
    Wire.write(misc[2]);
    Wire.endTransmission();
  }

  delay(5);
}


