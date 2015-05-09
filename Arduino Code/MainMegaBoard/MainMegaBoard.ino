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
  
  // set up the arm to steady
  for(int i = 0; i < 3; i++) {
    armMotor[i].attach(TALON_ARM[i]);
    armMotor[i].writeMicroseconds(NEUTRAL_FREQUENCY);
  }
}

void loop() {
  // Pass in the pot value from 0 to 1023
  driveMotorFullSpeed(1023);
  // getReadingFromCurrentSensor();
  armRiseAndBack();
  delay(100);
  
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
        // handMotor[i].write(handPos[i]);
      }
    }
  }
}

