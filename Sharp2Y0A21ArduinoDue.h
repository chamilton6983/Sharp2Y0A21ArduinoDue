#pragma once
#ifndef Sharp2Y0A21ArduinoDue_h
#define Sharp2Y0A21ArduinoDue_h
#include <Arduino.h>

class Sharp2Y0A21ArduinoDue
{
public:
	Sharp2Y0A21ArduinoDue();
	~Sharp2Y0A21ArduinoDue();
	void begin(int pin);
	int getDistanceRaw();
	int getDistanceVolts();
	int getDistanceCM();
	int getAverageDistanceRaw();
	int getAverageDistanceVolts();
	int getAverageDistanceCM();
	void setAveraging(int avg);
	int getAveraging();
	void setADCAccuracy(int bits);
	int getADCAccuracy();
	void setPolyAccuracy(int poly);
	int getPolyAccuracy();
	void setPin(int pin);
	int getPin();
private:
	int _mapRawToVolts(int raw);
	int _mapVoltsToCM(int volts);
	int _pin;
	int _avg;
	int _bits;
	int _max;
	int _poly;
};

#endif