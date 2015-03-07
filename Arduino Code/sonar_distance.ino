/*

sonar_distance.ino

Created by Taylor Cramer for the Husky Robotics Team

Made for use with an HC-SR04 sound-based distance center.

*/

const uint8_t ANALOG_PIN_OFFSET = 14;
const uint8_t TRIG_PIN = 2, ECHO_PIN = 3;
const int NUM_SMOOTHING_FRAMES = 5;

/*
  Triggers a short burst of sound
*/
void triggerSound() {
  // Start with a short LOW pulse to ensure a clean HIGH pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(5);
  digitalWrite(TRIG_PIN, LOW);
}

/*
  Converts sound to distance
  @param microseconds length of time before echo has heard
  @return the distance sound has traveled (inches)
*/
int timeToInches(long microseconds) {
  long microseconds_per_inch = 74;
  return (int) (microseconds / microseconds_per_inch / 2);
}

void setup() {
  // Starts serial input
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  // Trigger a burst of sound and 
  triggerSound();
  
  // Read in the duration of the echo and convert to inches
  long ping_duration = pulseIn(ECHO_PIN, HIGH);
  
  // This is the distance!!! USE THIS!!!!!
  int inches = timeToInches(ping_duration);
  
  Serial.println(inches);
  
  delay(100);
}
