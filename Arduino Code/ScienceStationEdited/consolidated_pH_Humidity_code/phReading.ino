int phReading()
{
	float Count;
	float Voltage;
	float pH;
	Count = analogRead(pHPin);
	Voltage = Count / 1023 * 5.0;// convert from count to raw voltage
	pH = Voltage/0.36;
	//Serial.print("Voltage: ");
	//Serial.println(Voltage);
	//Serial.print("pH: ");
	//Serial.println(pH);
	return pH*1000; //multiply by 1000 before converting to int so that all sig figs are preserved
}
