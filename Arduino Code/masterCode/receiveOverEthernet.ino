//#include <SPI.h>         // needed for Arduino versions later than 0018
//#include <Ethernet.h>
//#include <EthernetUdp.h>         // UDP library from: bjoern@cs.stanford.edu 12/30/2008
//#include "megaBoardDefine.h"


// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
//byte mac[] = {
//  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
//};
//IPAddress ip(192, 168, 1, 177);
boolean hasIP = false;
unsigned int localPort = 8888;      // local port to listen on

// Recieved Data


// buffers for receiving and sending data
//char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
//char  ReplyBuffer[] = "acknowledged";       // a string to send back

// An EthernetUDP instance to let us send and receive packets over UDP
//EthernetUDP Udp;

void receiveWirelessData()
{
    //Serial.print("Network Status: ");
    //Serial.println(networkStatus);
    networkStatus = processNetworkData();
}

void initializeWireless()
{ // begin wireless communication
    Serial.begin(BAUD_RATE);
    Ethernet.begin(mac, ip);
    Udp.begin(UDP_PORT);
    timeLastPacket = millis();
    Serial.println("INITIALIZED");
    
}


void readByteAsInt(byte data, int* buffer, byte bufferSize)
{
    byte mask = 0x03;
    for(byte i = 0; i < bufferSize; i++) {
        *buffer = data & mask;
        data >>= 2;
        buffer++;
    } 
}

void receiveOverEthernet() {
    // if there's data available, read a packet
      int packetSize = Udp.parsePacket();
      if (packetSize) {
        //Serial.print("Received packet of size ");
        //Serial.println(packetSize);
        Serial.print("From ");
        IPAddress remote = Udp.remoteIP();
        for (int i = 0; i < 4; i++) {
          Serial.print(remote[i], DEC);
          if (i < 3) {
            Serial.print(".");
          }
        }
        Serial.print(", port ");
        Serial.println(Udp.remotePort());

        // read the packet into packetBufffer
        Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
        int *buffer;
        for (int i = 0; i < packetSize; i++) {
          readByteAsInt(packetBuffer[i], buffer, 1);
        }
        Serial.println("Contents:");
        Serial.println(packetBuffer);
        Serial.println("Converted:");
        for (int i = 0; i < packetSize; i++) {
          Serial.println(buffer[i]); 
        }

        // send a reply, to the IP address and port that sent us the packet we received
        Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
        Udp.write(ReplyBuffer);
        Udp.endPacket();
    }
    delay(10);
}

// parses the raw data from the received packet to a writeable format for the motors
int processNetworkData() {
    //Serial.println("CHECKING");
    //Serial.println(freeRam());
    // Check size of available packet
    int packetSize = Udp.parsePacket();
    //Serial.print("Packet size: ");
    //Serial.println(packetSize);
    // Process packet if available
    if(packetSize == 5) {
        hasIP = true;
        //printPacketInfo(packetBuffer);
        //Serial.println("GOOD");
        // read the packet into packetBufffer
        Udp.read(packetBuffer, 96);
        // Process packet into values
        leftPower  = ((unsigned char)packetBuffer[0]) & 0xFFFF;
        rightPower  = ((unsigned char)packetBuffer[1]) & 0xFFFF;
        readByteAsInt(packetBuffer[2], arm, 3);
        readByteAsInt(packetBuffer[3], hand, 4);
        readByteAsInt(packetBuffer[4], misc, 4);
        printPacketValues();
        return 1;
    }
    return 0;
}

void printPacketValues() {
/*  Serial.print("Left: ");
  Serial.println(leftPower);
  Serial.print("Right: ");
  Serial.println(rightPower);

  for(int i = 0; i < 3; i++)
  {
    Serial.print("Arm:");
    Serial.println(arm[i]);
  }*/
  

  /*for(int i = 0; i < 3; i++)
  {
    Serial.print("Hand:");
    Serial.println(hand[i]);
  }*/
/*
  for(int i = 0; i < 4; i++)
  {
    Serial.print("Misc:");
    Serial.println(misc[i]);
  }*/
}

// check to see if there is still a live wireless connection. If not, stop all motors.
void timeoutCheck()
{
    if(millis() - timeLastPacket >= TIMEOUT) {
        // Serial.println("TIMEOUT");
        leftMotor.writeMicroseconds(NEUTRAL_FREQUENCY);
        rightMotor.writeMicroseconds(NEUTRAL_FREQUENCY);
    }
}
