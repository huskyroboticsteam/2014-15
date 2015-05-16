#include "Arduino.h"
const int humPin = A0;
boolean humcalibrated = true;
double humcalibratedValue = 640.0;
int TimeBetweenReadings = 500;
const int pHPin = A1;
