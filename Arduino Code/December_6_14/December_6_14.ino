/*

December_6_14 Arduino Test

Prints serial input to console and changes pin 13 (LED) value
on input.

*/

// Stores whether or not the pin is at high value
boolean isHigh;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output and set to low
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  isHigh = false;
  
  // Starts serial communication with baud rate 115200
  Serial.begin(115200);
}

// the loop function runs over and over again forever
void loop() {
  // Checks if the arduino has recieved serial input
  if(Serial.available() > 0) {
    // Read in serial input
    char value = Serial.read();
    // Print out the value read to the console
    Serial.print("Read: ");
    Serial.println(value);
    
    // Switches the value of pin 13 (LED) between high and low
    if(isHigh) {
      digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
      isHigh = false;
    } else {
      digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
      isHigh = true;
    }
  }
}
