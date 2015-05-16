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
    attachDriveMotors();
    attachArmMotors();
    initializeWireless();
}

void loop()
{
    timeoutCheck();
    receiveWirelessData();
    writeToDriveMotors();
    writeToArmMotors();
}
