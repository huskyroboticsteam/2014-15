// Apr 11, 2015. Husky Robotics, made by Electrical Team
// Using Analog read from current sensor ACS758
#include <Arduino.h>

// Reading the rare data from the motor
// @Measured: 121 Static;
//            149 Max current powered from the motor controller;
//            169 Max current powered directly from battery;
int currentReadingMax = 0;
int currentReadingMin = 169;

void getReadingFromCurrentSensor() {
  // Data gathering
  int currentReading = analogRead(currentSensorPin);
  delay(500);
  if (currentReading > currentReadingMax) {
     currentReadingMax = currentReading;
  }  
  if (currentReading < currentReadingMin) {
     currentReadingMin = currentReading;
  }

  // Data translating to milliAmps
  int current = rareDataToAmp(currentReading); // in milliAmps
  int currentMax = rareDataToAmp(currentReadingMax);
  int currentMin = rareDataToAmp(currentReadingMin);
  printReading(current, currentMax, currentMin);
}

// Turn the rare analog read from Arduino to current reading
// @requires: an analog reading input from ACS758
// @throws:   If input is smaller than 100 or larger than 200, 
//            throws error message in console
// @returns:  a current value in milliAmps. 
int rareDataToAmp(int currentReading) {
  // From the Datasheet, we have 40mV/A, which equals to 25 mA/mV
  int sensitivity = 25;
  // turn the analog read to milliVolt
  int voltageRead = map(currentReading, 0, 1023, 0, 5000);
  return voltageRead * sensitivity;
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
