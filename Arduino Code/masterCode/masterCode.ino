// HARDWARE: Arduino MEGA 2560
#include "Arduino.h"
#include "megaBoardDefine.h"
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <Servo.h>
#include <Wire.h>

void setup()
{
    Serial.println("STARTING");
    attachDriveMotors();
    attachArmMotors();
    attachHandMotors();
    initializeWireless();
}

void loop()
{
    overCurrentCheck();
    timeoutCheck();
    compressorPressureCheck();    
    receiveWirelessData();
    writeToDriveMotors();
    writeToArmMotors();
    writeToHandMotors();
}
