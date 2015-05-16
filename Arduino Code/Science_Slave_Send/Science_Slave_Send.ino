// Wire Slave Sender
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Sends data as an I2C/TWI slave device
// Refer to the "Wire Master Reader" example for use with this

// Created 29 March 2006

// This example code is in the public domain.





char Message[] = "";



#include <Wire.h>

void setup()
{
  Wire.begin(2);                // join i2c bus with address #2
  Wire.onRequest(requestEvent); // register event
}

void loop()
{
  Message = ""
  //Humidity Reading
  // read the value from the pin
  double humReading = 0;
  humReading = analogRead(humPin); 
  // calculate the sensor humidity
  if(humcalibrated){
    double sensorRH = humReading/humcalibratedValue*100.0;
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
  //End pH Reading
  
  //CURRENT MESSAGE LENGTH IS 12
  Message = (("p:" + pH).substring(0,3)) + (("h:" + sensorRH).substring(0,3));
  
  delay(TimeBetweenReadings);// delay in between reads for stability
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent()
{
  Wire.write(Message); // respond with message of 6 bytes
                       // as expected by master
}
