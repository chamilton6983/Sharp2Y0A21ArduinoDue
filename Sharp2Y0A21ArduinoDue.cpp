#include "Sharp2Y0A21ArduinoDue.h"

Sharp2Y0A21ArduinoDue::Sharp2Y0A21ArduinoDue()
{
	_pin = 0;
	_avg = 0;
	_bits = 0;
}

Sharp2Y0A21ArduinoDue::~Sharp2Y0A21ArduinoDue()
{
}

void Sharp2Y0A21ArduinoDue::begin(int pin)
{
	_pin = pin;
	pinMode(pin, INPUT);
	setAveraging(10);
	setAccuracy(10);
}

int Sharp2Y0A21ArduinoDue::getDistanceRaw()
{
	return analogRead(_pin);
}

int Sharp2Y0A21ArduinoDue::getDistanceVolts()
{
	return _mapRawToVolts(getDistanceRaw());
}

int Sharp2Y0A21ArduinoDue::getDistanceCM()
{
	return _mapVoltsToCM(getDistanceVolts());
}

int Sharp2Y0A21ArduinoDue::getAverageDistanceRaw()
{
	int sum = 0;
	for (int i = 0; i < _avg; i++)
	{
		sum = sum + getDistanceRaw();
	}
	return (sum / _avg);
}

int Sharp2Y0A21ArduinoDue::getAverageDistanceVolts()
{
	int sum = 0;
	for (int i = 0; i < _avg; i++)
	{
		sum = sum + getDistanceVolts();
	}
	return (sum / _avg);
}

int Sharp2Y0A21ArduinoDue::getAverageDistanceCM()
{
	int sum = 0;
	for (int i = 0; i < _avg; i++)
	{
		sum = sum + getDistanceCM();
	}
	return (sum / _avg);
}

void Sharp2Y0A21ArduinoDue::setAveraging(int avg)
{
	_avg = avg;
}

void Sharp2Y0A21ArduinoDue::setAccuracy(int bits)
{
	_bits = bits;
	analogReadResolution(_bits);
}

void Sharp2Y0A21ArduinoDue::setPin(int pin)
{
	_pin = pin;
	pinMode(_pin, INPUT);
}

int Sharp2Y0A21ArduinoDue::_mapRawToVolts(int raw)
{
	return map(raw, 0, ((2 ^ _bits) - 1), 0, 3300);
}

int Sharp2Y0A21ArduinoDue::_mapVoltsToCM(int volts)
{
	int cm = 0;
	
	//TODO

	if (cm < 10)
	{
		cm = 0;
	}
	else if (cm > 80)
	{
		cm = 255;
	}
	return cm;
}