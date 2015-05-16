#include "sciencestationDefine.h"
#include "humidityReading.h"
#include "sendReadings.h"
#include "phReading.h"
#include <Wire.h>

void setup() {
  // initialize serial communications:
  Wire.begin();
}

void loop() {
  sendReadings(humidityReading(), phReading());
  delay(TimeBetweenReadings);// delay in between reads for stability
}

