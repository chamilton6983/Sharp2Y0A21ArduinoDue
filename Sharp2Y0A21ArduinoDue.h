#pragma once
#ifndef Sharp2Y0A21ArduinoDue_h
#define Sharp2Y0A21ArduinoDue_h
#include <Arduino.h>

class Sharp2Y0A21ArduinoDue
{
public:
	Sharp2Y0A21ArduinoDue();
	~Sharp2Y0A21ArduinoDue();
	void initialise(int pin);
	int getDistanceRaw();
	int getDistanceVolts();
	int getDistanceCM();
	int getAverageDistanceRaw();
	int getAverageDistanceVolts();
	int getAverageDistanceCM();
	void setAveraging(int avg);
	void setAccuracy(int bits);
	void setPin(int pin);
private:
	int _mapRawToVolts(int raw);
	int _mapVoltsToCM(int volts);
	int _pin;
	int _avg;
	int _bits;
};

#endif