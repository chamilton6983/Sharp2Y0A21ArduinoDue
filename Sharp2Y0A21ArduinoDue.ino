#include <Sharp2Y0A21ArduinoDue.h>

Sharp2Y0A21ArduinoDue Sensor;

int distance;
const int pin = A0;
const int rate = 9600;

void setup()
{
	Serial.begin(rate);
	Sensor.initialise(pin);
}

void loop()
{
	distance = Sensor.getDistanceRaw();
	Serial.print("\n");
	Serial.print(distance);
	delay(100);
}
