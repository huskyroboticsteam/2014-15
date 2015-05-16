#include <Wire.h>

//With two arduino unos: Connect A4 to A4, A5 to A5, and share common ground.

void setup()
{
    Wire.begin();
}

boolean message = 1;
byte x=0;

void loop()
{
    Wire.beginTransmission(4);
    Wire.write(message);
    Wire.endTransmission();
    delay(1000);
    x++;
    message = !message;
}
