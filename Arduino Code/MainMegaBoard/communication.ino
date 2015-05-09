int processNetworkData() {
  //Serial.println(freeRam());
  // Check size of available packet
  int packetSize = Udp.parsePacket();

  // Process packet if available
  if(packetSize == 5)
  {
    hasIP=true;
    //printPacketInfo(packetBuffer);
    //Serial.println("GOOD");

    // read the packet into packetBufffer
    Udp.read(packetBuffer, 96);

    // Process packet into values
    leftPower  = ((unsigned char)packetBuffer[0]) & 0xFFFF;
    rightPower  = ((unsigned char)packetBuffer[1]) & 0xFFFF;
    readByteAsInt(packetBuffer[2], arm, 4);
    readByteAsInt(packetBuffer[3], hand, 3);
    readByteAsInt(packetBuffer[4], misc, 4);

    //printPacketValues();
    return 1;
  }
  return 0;
}

// Prints data about packet, packet sender
void printPacketInfo(int packetSize) {
  Serial.print("Received packet of size ");
  Serial.println(packetSize);
  Serial.print("From ");
  IPAddress remote = Udp.remoteIP();
  for (int i = 0; i < 4; i++)
  {
    Serial.print(remote[i], DEC);
    if (i < 3)
    {
      Serial.print(".");
    }
  }
  Serial.print(", port ");
  Serial.println(Udp.remotePort());
}

// Prints readable versions of packet
void printPacketValues() {
  Serial.print("Left: ");
  Serial.println(leftPower);
  Serial.print("Right: ");
  Serial.println(rightPower);

  for(int i = 0; i < 4; i++)
  {
    Serial.print("Arm:");
    Serial.println(arm[i]);
  }

  for(int i = 0; i < 3; i++)
  {
    Serial.print("Hand:");
    Serial.println(hand[i]);
  }

  for(int i = 0; i < 4; i++)
  {
    Serial.print("Misc:");
    Serial.println(misc[i]);
  }
}

void readByteAsInt(byte data, int* buffer, byte bufferSize) {
  byte mask = 0x03;

  for(byte i = 0; i < bufferSize; i++)
  {
    *buffer = data & mask;
    data >>= 2;
    buffer++;
  }
}

int dirToMicroseconds(int dir) {
  if(dir == 0) {
    return MIN_FREQUENCY;
  }
  if(dir == 2) {
    return MAX_FREQUENCY;
  }
  return NEUTRAL_FREQUENCY;
}

// Handle i2c Event
void receivei2c(int howMany) {
  if(howMany == 9) {
    char i2cData[8];
    Wire.read();
  
    for(int i = 0; i < 8;  i++) {
      char c = Wire.read();
      i2cData[i] = c;
    }
    
    if(hasIP) {
      Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
      Udp.write(i2cData);
      Udp.endPacket();
    }
  }
}
