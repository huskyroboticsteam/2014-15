// Apr 11, 2015. Husky Robotics, made by Electrical Team
// Using Analog read from current sensor ACS758
//#include <Arduino.h>
//#include "megaBoardDefine.h"

// Reading the rare data from the motor
// @Measured: 121 Static;
//            149 Max current powered from the motor controller;
//            169 Max current powered directly from battery;
int currentReadingMax = 0;
int currentReadingMin = 169;

// Turn the rare analog read from Arduino to current reading
// @requires: an analog reading input from ACS758
// @throws:   If input is smaller than 101 or larger than 189, 
//            throws error message in console
// @returns:  a current value in milliAmps. 
int rawDataToAmp(int analogReading) {
  // From the Datasheet, we have 40mV/A, which equals to 25 mA/mV
  int sensitivity = 25;
  // Value measured, Apr. 11, 2015, Beck Pang & Andrew DeBartolo
  int staticVoltage = 121;
  int MaxCurrentPassThrough = 169;
  
  int currentReading = analogReading - staticVoltage;
  int voltageRead;
  if (analogReading < staticVoltage - 20) {
    Serial.println("Current Sensor has floating VCC"); 
    return -1;
  } else if (analogReading > MaxCurrentPassThrough + 20) {
    Serial.println("Warning: Too much current consumed by the source");
    voltageRead = map(currentReading, 0, 1023, 0, 5000);
  } else {
  // turn the analog read to milliVolt
    voltageRead = map(currentReading, 0, 1023, 0, 5000);
  }
  return voltageRead * sensitivity;
}


void overCurrentCheck()
{
    int currentReading = analogRead(CURRENT_SENSOR_PIN);
    int current = rawDataToAmp(currentReading);
    if (current > DANGER_CURRENT) {
        digitalWrite(ALARM_PIN, HIGH);
        for (int i = 0; i <= 10; i++) {
            Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
            Udp.write("OVER CURRENT!!!!!!!!!");
            Udp.endPacket();
        }
        for(int i = 0; i < 3; i++) {
            armMotor[i].writeMicroseconds(NEUTRAL_FREQUENCY);
        }
        leftMotor.writeMicroseconds(NEUTRAL_FREQUENCY);
        rightMotor.writeMicroseconds(NEUTRAL_FREQUENCY);
        delay(15000);
    }
}


void printReading(int current, int currentMax, int currentMin) {
  Serial.print("A1 Reads current: ");
  Serial.print(current);
  Serial.println("mA");
  Serial.print("    Max:");
  Serial.print(currentReadingMax);
  Serial.println("mA");
  Serial.print("    Min:");
  Serial.print(currentReadingMin);
  Serial.println("mA");
}
