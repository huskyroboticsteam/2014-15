int humidityReading()
{
  // read the value from the pin
  double humReading = 0;
  double sensorRH = 0;
  humReading = analogRead(humPin); 
  // calculate the sensor humidity
  if(humcalibrated){
    sensorRH = humReading/humcalibratedValue*100.0;
  }
  return sensorRH*10; //multiply percentage before 10 before converting to int to preserve sig figs
}
