// Apr 18, 2015. Husky Robotics, made by Electrical Team
// Using Analog read from current sensor ACS758
#include <Arduino.h>

void armRiseAndBack() {
  for(int i = 0; i < 3; i++) {
    armMotor[i].writeMicroseconds(SPEEDUP_FREQUENCY);
    Serial.println(TALON_ARM[i]);
    delay(5000);
    armMotor[i].writeMicroseconds(SPEEDDOWN_FREWQUENCY);
    delay(5000);
    armMotor[i].writeMicroseconds(NEUTRAL_FREQUENCY);
  }
}
