// Apr 18, 2015. Husky Robotics, made by Electrical Team
// Using Analog read from current sensor ACS758
#include <Arduino.h>

void moveArm() {
  for(int i = 0; i < 4; i++) {
    armMotor[i].writeMicroseconds(dirToMicroseconds(arm[i]));
  }
}

void moveHand() {
  for(int i = 0; i < 3; i++) {
    Serial.print("Hand: ");
    Serial.print(i);
    Serial.println(hand[i]);
    if(hand[i] == 0 || hand[i] == 2) {
      if(hand[i] == 0 && handPos[i] < 180) {
        handPos[i] += 5;
      } else if(handPos[i] > 0) {
        handPos[i] -= 5;
      }
      handMotor[i].write(handPos[i]);
    }
  }
}
