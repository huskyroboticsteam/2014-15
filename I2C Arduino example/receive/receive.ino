#include <Wire.h>

void setup()
{
    Wire.begin(4);
    Wire.onReceive(receiveEvent);
    Serial.begin(9600);
    pinMode(13, OUTPUT);
}

void loop()
{
    delay(10);
}

void receiveEvent(int howMany)
{
    boolean c = Wire.read();
    if (c)
    {
        digitalWrite(13, HIGH);
    }
    else
    {
        digitalWrite(13, LOW);
    }
}
