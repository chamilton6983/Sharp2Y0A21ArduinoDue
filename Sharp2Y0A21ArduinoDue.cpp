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
	setPin(pin);
	setAveraging(10);
	setADCAccuracy(10);
	setPolyAccuracy(5);
}

int Sharp2Y0A21ArduinoDue::getDistanceRaw()
{
	int raw = analogRead(_pin);
	return raw;
}

int Sharp2Y0A21ArduinoDue::getDistanceVolts()
{
	int raw = getDistanceRaw();
	int volts = _mapRawToVolts(raw);
	return volts;
}

int Sharp2Y0A21ArduinoDue::getDistanceCM()
{
	int volts = getDistanceVolts();
	int cm = _mapVoltsToCM(volts);
	if (cm < 8)
	{
		cm = 0;
	}
	else if (cm > 80)
	{
		cm = 255;
	}
	return cm;
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

int Sharp2Y0A21ArduinoDue::getAveraging()
{
	return _avg;
}

void Sharp2Y0A21ArduinoDue::setADCAccuracy(int bits)
{
	_bits = bits;
	double max = pow(2, bits);
	_max = max;
	analogReadResolution(_bits);
}

int Sharp2Y0A21ArduinoDue::getADCAccuracy()
{
	return _bits;
}

void Sharp2Y0A21ArduinoDue::setPolyAccuracy(int poly)
{
	if (poly <= 5)
	{
		_poly = poly;
	}
	else
	{
		_poly = 5;
	}
}

int Sharp2Y0A21ArduinoDue::getPolyAccuracy()
{
	return _poly;
}

void Sharp2Y0A21ArduinoDue::setPin(int pin)
{
	_pin = pin;
	pinMode(_pin, INPUT);
}

int Sharp2Y0A21ArduinoDue::getPin()
{
	return _pin;
}

int Sharp2Y0A21ArduinoDue::_mapRawToVolts(int raw)
{
	int volts = map(raw, 0, _max - 1, 0, 3300);
	return volts;
}

int Sharp2Y0A21ArduinoDue::_mapVoltsToCM(int volts)
{
	int cm;
	switch (_poly)
	{
	case 1:
		cm = (-0.023646 * volts) + 65.48;
		break;
	case 2:
		cm = (0.000019481 * pow(volts, 2)) + (-0.087711 * volts) + 101.03;
		break;
	case 3:
		cm = (-0.000000013681 * pow(volts, 3)) + (0.000086017 * pow(volts, 2)) + (-0.17777 * volts) + 132.82;
		break;
	case 4:
		cm = (0.000000000010404 * pow(volts, 4)) + (-0.000000083226 * pow(volts, 3)) + (0.00024228 * pow(volts, 2)) + (-0.31232 * volts) + 168.89;
		break;
	case 5:
		cm = (-0.0000000000000078233 * pow(volts, 5)) + (0.000000000075274 * (pow(volts, 4)) + (-0.0000002814 * pow(volts, 3)) + (0.00051584 * pow(volts, 2)) + (-0.47973 * volts) + 204.6);
		break;
	default:
		cm = (-0.023646 * volts) + 65.48;
		break;
	}
	return cm;
}