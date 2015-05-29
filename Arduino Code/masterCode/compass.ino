
/*void initializeCompass()
{
  compass.init();
  compass.enableDefault();
  compass.m_min = (LSM303::vector<int16_t>){-32767, -32767, -32767};
  compass.m_max = (LSM303::vector<int16_t>){+32767, +32767, +32767};
  Wire.begin();
  //20 (SDA), 21 (SCL)
}

void updateCompass()
{
  compass.read();
  Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
  Udp.write("Heading: ");  // 0 = North, 90 = East, 180 = South, 270 = West
  Udp.write(compass.heading());
  Udp.endPacket();
}
*/
