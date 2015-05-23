//#include <SPI.h>         // needed for Arduino versions later than 0018
//#include <Ethernet.h>
//#include <EthernetUdp.h>         // UDP library from: bjoern@cs.stanford.edu 12/30/2008
//#include "megaBoardDefine.h"

// PWM output ports
/*
const int LEFT_MOTOR_PWM = 3;
const int RIGHT_MOTOR_PWM = 5;
*/
// Port to listen for UDP connections on 
//const int UDP_PORT = 8888;

// ROBOTEQ constants
const int ROBOTEQ_MIN_FREQUENCY = 1250;
const int ROBOTEQ_MAX_FREQUENCY = 1750;

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
//byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
//IPAddress ip(192, 168, 1, 177);

// buffers for receiving and sending data
//char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
//char  ReplyBuffer[] = "acknowledged";       // a string to send back

// An EthernetUDP instance to let us send and receive packets over UDP
//EthernetUDP Udp;

void udpToPwm()
{
    int packetSize = Udp.parsePacket();
    if (packetSize) { // if there's data available, read a packet
        Serial.print("Received packet of size ");
        Serial.println(packetSize);
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

