// Wire Slave Sender
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Sends data as an I2C/TWI slave device
// Refer to the "Wire Master Reader" example for use with this

// Created 29 March 2006

// This example code is in the public domain.
#include <Wire.h>
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include <Wire.h>
SoftwareSerial mySerial(3, 2);
Adafruit_GPS GPS(&mySerial);
const int humPin = A0;
boolean humcalibrated = true;
double humcalibratedValue = 640.0;
int TimeBetweenReadings = 500;
const int pHPin = A1;


// Set GPSECHO to 'false' to turn off echoing the GPS data to the Serial console
// Set to 'true' if you want to debug and listen to the raw GPS sentences. 
#define GPSECHO  true

// this keeps track of whether we're using the interrupt
// off by default!
boolean usingInterrupt = false;
String sendMessage;
boolean message = 1;
byte x =0 ;
void useInterrupt(boolean); 

void setup()
{
  Wire.begin(2);                // join i2c bus with address #2
  Wire.onRequest(requestEvent); // register event
   Serial.begin(115200);
  Serial.println("Adafruit GPS library basic test!");
  //Wire.begin();

  // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
  GPS.begin(9600);
  
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
   
  // Set the update rate
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate
  // For the parsing code to work nicely and have time to sort thru the data, and
  // print it out we don't suggest using anything higher than 1 Hz

  // Request updates on antenna status, comment out to keep quiet
  GPS.sendCommand(PGCMD_ANTENNA);

  useInterrupt(true);

  delay(1000);
  // Ask for firmware version
  mySerial.println(PMTK_Q_RELEASE);
}
uint32_t timer = millis();
void loop()
{
  sendMessage = "";
  //Humidity Reading
  // read the value from the pin
  double humReading = 0;
  humReading = analogRead(humPin); 
  // calculate the sensor humidity
  double sensorRH = 0;
  if(humcalibrated){
    sensorRH = humReading/humcalibratedValue*100.0;
    Serial.print(sensorRH);
    Serial.println("%");
  }
  //End Humidity Reading
  
  //pH Reading
  float Count;
  float Voltage;
  float pH;
  Count = analogRead(pHPin);
  Voltage = Count / 1023 * 5.0;// convert from count to raw voltage
  pH = Voltage/0.36;
  Serial.print("Voltage: ");
  Serial.println(Voltage);
  Serial.print("pH: ");
  Serial.println(pH);
  sendMessage += "Perc: ";// /*
  sendMessage += ((int)(sensorRH));//*/ 
  sendMessage += " Volt: "; 
  sendMessage += ((int)(Voltage* 100));
  sendMessage += " pH: " ;
  sendMessage += ((int)(100*pH));
  sendMessage += gpsRun();
  Serial.println("sending ... : ");
  Serial.println(sendMessage);
  delay(TimeBetweenReadings);// delay in between reads for stability
  
}

SIGNAL(TIMER0_COMPA_vect) {
  char c = GPS.read();
  // if you want to debug, this is a good time to do it!
#ifdef UDR0
  if (GPSECHO)
    if (c) UDR0 = c;  
    // writing direct to UDR0 is much much faster than Serial.print 
    // but only one character can be written at a time. 
#endif 
}
// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent()
{
  Serial.println("ITS calling");
  Wire.write(sendMessage.c_str()); // respond with message of 6 bytes
                       // as expected by master
}
void useInterrupt(boolean v) {
  if (v) {
    // Timer0 is already used for millis() - we'll just interrupt somewhere
    // in the middle and call the "Compare A" function above
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
    usingInterrupt = true;
  } else {
    // do not call the interrupt function COMPA anymore
    TIMSK0 &= ~_BV(OCIE0A);
    usingInterrupt = false;
  }
}

String gpsRun()                     // run over and over again
{  
  String result = "";
  if (! usingInterrupt) {
    // read data from the GPS in the 'main loop'
    char c = GPS.read();
    // if you want to debug, this is a good time to do it!
    if (GPSECHO)
      if (c) Serial.print(c);
  }
  
  // if a sentence is received, we can check the checksum, parse it...
  if (GPS.newNMEAreceived()) {
    // a tricky thing here is if we print the NMEA sentence, or data
    // we end up not listening and catching other sentences! 
    // so be very wary if using OUTPUT_ALLDATA and trytng to print out data
    //Serial.println(GPS.lastNMEA());   // this also sets the newNMEAreceived() flag to false
  
    if (!GPS.parse(GPS.lastNMEA())) 
        // this also sets the newNMEAreceived() flag to false
      return "Not parsed";  // we can fail to parse a sentence in which case we should just wait for another
  }

  // if millis() or timer wraps around, we'll just reset it
  if (timer > millis())  timer = millis();

  // approximately every 2 seconds or so, print out the current stats
  if (millis() - timer > 100) { 
    timer = millis(); // reset the timer
    
    Serial.print("\nTime: ");
    Serial.print(GPS.hour, DEC); Serial.print(':');
    Serial.print(GPS.minute, DEC); Serial.print(':');
    Serial.println(GPS.seconds, DEC);
    
    
    
    
    if (GPS.fix) {
      Serial.println("Fixed"); //If the GPS is fixed, it sees 3 satellites and can track position, allowing it to use the functions below.
      result += "Lat: ";
      if(GPS.lat == 'N') {
        result += 0.01*GPS.latitude;
        Serial.print("Latitude: "); Serial.print(0.01* GPS.latitude); Serial.println("GPS.lat");
      } else { 
        result += -0.01*GPS.latitude;
        Serial.print("Latitude: "); Serial.print(-0.01* GPS.latitude); Serial.println("GPS.lat"); 
      } //Gives degrees multiplied by 100 for latitude and longitude. .latitude gives the number and .lat gives direction (always north and west for our purposes)
      result += ", Long: ";
      if(GPS.lon = 'W') {
       result += -0.01*GPS.longitude;
        Serial.print("Longitude: "); Serial.print(-0.01 *GPS.longitude); Serial.println('GPS.lon');
      } else {
        result += 0.01*GPS.longitude;
        Serial.print("Longitude: "); Serial.print(0.01 *GPS.longitude); Serial.println('GPS.lon');
      }
      Serial.println("THIS ISRETURNING");
      Serial.println("---------");
      Serial.print("Angle: "); Serial.print(GPS.angle); Serial.println(" degrees");
      Serial.print("Altitude: "); Serial.print(GPS.altitude); Serial.println(" meters"); // Angle and altitude appear to be very inaccurate but could use further testing
      
      Serial.print("Number of Satellites: "); Serial.println((int)GPS.satellites); Serial.println();
    }
    else
    {
      result += 'N';
      result += 'F';
     
      Serial.println("Not fixed");
    }
  }
  return result;
}
