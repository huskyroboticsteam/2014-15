SoftwareSerial mySerial(3, 2); // 3 to tx, 2 to rx

Adafruit_GPS GPS(&mySerial);
#define GPSECHO  true
boolean usingInterrupt = false;
void useInterrupt(boolean); // Func prototype keeps Arduino 0023 happy

SIGNAL(TIMER0_COMPA_vect) {
  char c = GPS.read();
#ifdef UDR0
  if (GPSECHO)
    if (c) UDR0 = c;
#endif
}

void useInterrupt(boolean v) {
  if (v) {
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
    usingInterrupt = true;
  } else {
    TIMSK0 &= ~_BV(OCIE0A);
    usingInterrupt = false;
  }
}

uint32_t timer = millis();

void initializeGPS()
{
  GPS.begin(9600);
  
  // uncomment this line to turn on RMC (recommended minimum) and GGA (fix data) including altitude
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  // uncomment this line to turn on only the "minimum recommended" data
  //GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
  // For parsing data, we don't suggest using anything but either RMC only or RMC+GGA since
  // the parser doesn't care about other sentences at this time
  
  // Set the update rate
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
  // For the parsing code to work nicely and have time to sort thru the data, and
  // print it out we don't suggest using anything higher than 1 Hz

  // Request updates on antenna status, comment out to keep quiet
  GPS.sendCommand(PGCMD_ANTENNA);

  // the nice thing about this code is you can have a timer0 interrupt go off
  // every 1 millisecond, and read data from the GPS for you. that makes the
  // loop code a heck of a lot easier!
  useInterrupt(true);

  delay(1000);
  // Ask for firmware version
  mySerial.println(PMTK_Q_RELEASE);
}

float longitude = 0.0;
int longitudeDegrees = 0;
float longitudeMinutes = 0.0;

float latitude = 0.0;
int latitudeDegrees = 0;
float latitudeMinutes = 0.0;

void updateGPS()
{
    if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA()))
      true;  // we can fail to parse a sentence in which case we should just wait for another
  }

  if (timer > millis())  timer = millis();

  if (millis() - timer > 2000) { 
    timer = millis(); // reset the timer
    
    if (GPS.fix) {
      Serial.println("Fixed"); //If the GPS is fixed, it sees 3 satellites and can track position, allowing it to use the functions below.
    }
    else
    {
      Serial.println("Not fixed");
    }
  longitude = GPS.longitude;
  longitudeDegrees = longitude/100;
  longitudeMinutes = (longitude/100 - longitudeDegrees)*100;
  
  latitude = GPS.latitude;
  latitudeDegrees = latitude/100;
  latitudeMinutes = (latitude/100 - latitudeDegrees)*100;
  }
}
