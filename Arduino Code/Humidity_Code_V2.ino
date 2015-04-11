
const int humPin = A0;
int readingNumber = 0;
double readingSum = 0;
boolean calibrated = true;
double calibratedValue = 640.0;
void setup() {
  // initialize serial communications:
  Serial.begin(9600);
}

void loop() {
  // read the value from the pin
  double humReading = 0;
  humReading = analogRead(humPin); 
  readingSum+=humReading;
  // calculate the sensor humidity
  if(calibrated){
    double sensorRH = humReading/calibratedValue*100.0;
    Serial.print(sensorRH);
    Serial.println("%");
    // wait a second
    delay(1000);
  }
  //Water Calibration
  if(readingNumber==10 && calibrated){
    double readingAvg=readingSum/10.0;
    Serial.println(readingAvg);
    Serial.println(humReading);
    readingNumber = 0;
    readingSum = 0; 
  }
  delay(100);
  readingNumber++;
}
