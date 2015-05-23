void initializeGPS()
{
    GPS.begin(9600);
}

// sends gps data over UDP to the rover
void sendGpsData()
{
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write("N" + GPS.latitude);
    Udp.write("W" + GPS.longitude);
    Udp.endPacket();
}
