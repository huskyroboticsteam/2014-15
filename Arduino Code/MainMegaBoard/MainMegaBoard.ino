// Apr 11, 2015. Husky Robotics, made by Electrical Team

#include <Arduino.h>
#include "megaBoardDefine.h"
#include "communication.h"
#include <Servo.h>
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>         // UDP library from: bjoern@cs.stanford.edu 12/30/2008
#include <Wire.h>

void setup() {
  Serial.begin(BAUD_RATE);
  Serial1.begin(BAUD_RATE);
  leftMotor.attach(motorPin1);
  rightMotor.attach(motorPin2);
  MotorStop();
  
  // start the Ethernet and UDP:
  Ethernet.begin(mac,ip);
  Udp.begin(localPort);
  // i2c
  Wire.begin(4); // Join i2c with address #1
  Wire.onReceive(receivei2c); // Call back
  
  // set up the arm to steady
  for(int i = 0; i < 3; i++) {
    armMotor[i].attach(TALON_ARM[i]);
    armMotor[i].writeMicroseconds(NEUTRAL_FREQUENCY);
  }
  
  Serial.println("Intialized");
}

void loop() {
  // Pass in the pot value from 0 to 1023
  // driveMotorFullSpeed(1023);
  // getReadingFromCurrentSensor();
  // armRiseAndBack();
  // delay(100);
  
  // Check timeout, disable if necessary
  if(millis() - timeLastPacket >= TIMEOUT) {
    //Serial.println("TIMEOUT");
    leftMotor.writeMicroseconds(NEUTRAL_FREQUENCY);
    rightMotor.writeMicroseconds(NEUTRAL_FREQUENCY);
  } else {
    int networkStatus = processNetworkData();
    if(networkStatus == 1) {
      // Refresh timeout
      timeLastPacket = millis();
  
      // Process new values;
      driveMotor();
      moveArm();
      moveHand();
    }
  }
}

