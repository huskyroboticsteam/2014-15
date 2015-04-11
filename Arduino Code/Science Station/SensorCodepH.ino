int TimeBetweenReadings = 500;
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  Serial.println("Time (s)    Voltage Readings from A0 (N)");
}
void loop() {
float Count;
float Voltage;
float SensorReading;
int ReadingNumber=0;
float Time;//the print below does the division first to avoid overflows
  //Serial.print(ReadingNumber/1000.0*TimeBetweenReadings); 
  Count = analogRead(A0);
  Voltage = Count / 1023 * 5.0;// convert from count to raw voltage
  //Serial.print("            ");
  Serial.print("Voltage: ");
  Serial.println(Voltage);
  Serial.print("pH: ");
  Serial.println(Voltage/0.36);
  delay(TimeBetweenReadings);// delay in between reads for stability
  ReadingNumber++;
}
