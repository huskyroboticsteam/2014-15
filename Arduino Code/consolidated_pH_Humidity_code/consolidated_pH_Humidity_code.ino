const int humPin = A0;
boolean humcalibrated = true;
double humcalibratedValue = 640.0;
int TimeBetweenReadings = 500;
const int pHPin = A1;
void setup() {
  // initialize serial communications:
  Serial.begin(9600);
}

void loop() {
  
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
  
  
  delay(TimeBetweenReadings);// delay in between reads for stability
}

