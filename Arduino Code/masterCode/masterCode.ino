// HARDWARE: Arduino MEGA 2560
#include "Arduino.h"
//#include <Adafruit_GPS.h>  // include this file in the Arduino libraries folder
#include <Servo.h>
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
//#include <SoftwareSerial.h>
#include <Wire.h>

void setup()
{
    attachDriveMotors();
    attachArmMotors();
    attachHandMotors();
    initializeWireless();
//    initializeGPS();
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
//    updateGPS();
}
