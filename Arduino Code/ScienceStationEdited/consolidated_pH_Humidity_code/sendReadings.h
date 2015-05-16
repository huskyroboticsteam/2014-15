#include <Wire.h>
void sendReadings(int humidity, int pH)
{
	Wire.beginTransmission(4);

// Need to insert code to convert the ints to bytes before they can be sent via I2C.

	//Wire.write(humidity);
	//Wire.write(" ");
	//Wire.write(pH);
	Wire.endTransmission();
}
