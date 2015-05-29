void initializeCompressor()
{
    pinMode(COMPRESSOR_CONTROL, OUTPUT);
    pinMode(COMPRESSOR_PIN, INPUT);
    Serial.println("INITIALIZED");
}


void compressorPressureCheck()
{
    int pressureValue = analogRead(COMPRESSOR_PIN) * 0.363;
    //pressureValue = 75 + 75 * sin(millis() / 1000.0) + random(0, 200) / 100.0;
    // Serial.println(pressureValue);
    // Need to use a bang bang with hysteresis band controller.
    // This requires desired operating pressure, band, and previous state
    int error = pressureValue - COMPRESSOR_PRESSURE;
    // Negative error means pressure is low.
    
    // State 0: Pressure is below hysteresis band
    // State 1: Pressure is within band on upswing
    // State 2: Pressure is above hysteresis band
    // State 3: Pressure is within band on downswing
    // Process flow is 0 -> 1 -> 2 -> 3 -> 0 -> ...
    
    /*
    Pressure vs Time Plot
    Solid line - Desired Pressure (COMPRESSOR_PRESSURE)
    Dashed line - Hysteresis band (COMPRESSOR_PRESSURE +- COMPRESSOR_BAND)
          /--\              /--    State 2
    _ _ _/ _ _\ _ _ _ _ _ _/ _ _ _ _ _ _ _ _ _ _
        /      \          /
    ___/________\________/____     State 1 or 3
      /          \      /          
    _/ _ _ _ _ _ _\ _ _/ _ _ _ _ _ _ _ _ _ _ _ _
    /              \--/            State 0
   
    */
    if (error < -COMPRESSOR_BAND){
      // State 0
      compressorStateOld = 0;
      //Serial.println("State 0, Out of Band and Low Pressure");
      digitalWrite(COMPRESSOR_CONTROL, HIGH);
      armMotor[1].writeMicroseconds(1250);
    } else if (error >= -COMPRESSOR_BAND && error <= COMPRESSOR_BAND){
      // State 1 or 3
      if (compressorStateOld == 0){
        // State 1
        digitalWrite(COMPRESSOR_CONTROL, HIGH);
        //Serial.println("State 1, In Band on Upswing");
      } else {
        // State 3
        digitalWrite(COMPRESSOR_CONTROL, LOW);
        //Serial.println("State 3, In Band on Downswing");
      }
    } else if (error > COMPRESSOR_BAND){
      // State 2
      digitalWrite(COMPRESSOR_CONTROL, LOW);
      compressorStateOld = 2;
      //Serial.println("State 2, Out of Band and High Pressure");
    } else {
      Serial.println("How did I get here?");
    }
}

