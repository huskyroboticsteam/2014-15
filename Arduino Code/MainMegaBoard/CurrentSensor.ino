// Apr 11, 2015. Husky Robotics, made by Electrical Team
// Using Analog read from current sensor ACS758
#include <Arduino.h>

// Reading the rare data from the motor
// @Measured: 121 Static;
//            149 Max current powered from the motor controller;
//            169 Max current powered directly from battery;
int current1Max = 0;
int current1Min = 169;
int current2Max = 0;
int current2Min = 169;

void getReadingFromCurrentSensor() {
  int currentReading1 = analogRead(currentSensorPin1);
  delay(500);
  if (currentReading1 > current1Max) {
     current1Max = currentReading1;
  }  
  if (currentReading1 < current1Min) {
     current1Min = currentReading1;
  }
  
  int currentReading2 = analogRead(currentSensorPin2);
  delay(500);
  if (currentReading2 > current2Max) {
     current2Max = currentReading2;
  }  
  if (currentReading2 < current2Min) {
     current2Min = currentReading2;
  }
  printReading(currentReading1, currentReading2);

}

void printReading(currentReading1, currentReading2) {
  Serial.print("A1 Reads:");
  Serial.println(currentReading1);
  Serial.print("    Max:");
  Serial.println(current1Max);
  Serial.print("    Min:");
  Serial.println(current1Min);

 Serial.print("A2 Reads:");
 Serial.println(currentReading2);
 Serial.print("    Max:");
 Serial.println(current2Max);
 Serial.print("    Min:");
 Serial.println(current2Min);
}
