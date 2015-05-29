void initializeScience(){
  for (int i = 0; i < 8; i++){
    pinMode(digitalOutputs[i], OUTPUT);
  }
  pinMode(PH_SENSOR, INPUT);
}

double readpH(){
  int val = analogRead(PH_SENSOR);
  double pH = 700.0 - (val - 241.0) * 300.0 / 77.0;
  Serial.print("pH: ");
  Serial.println(pH);
  Udp.beginPacket(DestinationAddress, DestinationPort);
  Udp.write(pH);
  Udp.endPacket();
  return pH;
}

void writeToScienceBoard(){
  for (int i = 0; i < 8; i++){
    if (cameraPanTilt[i] == -1){
      digitalWrite(digitalOutputs[i * 2], HIGH);
      digitalWrite(digitalOutputs[i * 2 + 1], LOW);
    } else if (cameraPanTilt[i] == 1){
      digitalWrite(digitalOutputs[i * 2], LOW);
      digitalWrite(digitalOutputs[i * 2 + 1], HIGH);
    } else {
      digitalWrite(digitalOutputs[i * 2], LOW);
      digitalWrite(digitalOutputs[i * 2 + 1], LOW);
    }
  }
}
