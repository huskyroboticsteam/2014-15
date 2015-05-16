#include "sciencestationDefine.h"
#include <Wire.h>

void setup() {
  // initialize serial communications:
  Wire.begin();
}

void loop() {
  sendReadings(humidityReading(), phReading());
  delay(TimeBetweenReadings);// delay in between reads for stability
}

