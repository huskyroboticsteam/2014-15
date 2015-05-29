
void attachHandMotors()
{
    for (int i; i <= 2; i++) {
        handMotor[i].attach(HAND[i]);
    }
    for (int i; i <= 2; i++){
        pinMode(GRIPPER[i], OUTPUT);
    }
    digitalWrite(GRIPPER[0], HIGH);
}

void writeToHandMotors()
{
    int segments = 3;
    for(int i = 0; i < segments; i++) {
        /*Serial.print("Hand: ");
        Serial.print(i);
        Serial.println(hand[i]);*/
        delay(20);
        if(hand[i] == 0 || hand[i] == 2) {
            if(hand[i] == 0 && handPos[i] < MAX_HAND) {
                handPos[i] += 1;
            }
            else if(hand[i] == 2 && handPos[i] > MIN_HAND) {
                handPos[i] -= 1;
            }
            handMotor[i].write(handPos[i]);
        }
    }
    if(hand[segments] == 0){
        digitalWrite(GRIPPER[1], HIGH);
        digitalWrite(GRIPPER[2], LOW);
    //    Serial.println("Close");
    } else if (hand[segments] == 2){
        digitalWrite(GRIPPER[1], LOW);
        digitalWrite(GRIPPER[2], HIGH);
     //   Serial.println("Open");
    } else {
        digitalWrite(GRIPPER[1], LOW);
        digitalWrite(GRIPPER[2], LOW);
      //  Serial.println("Hold");
    }
}

