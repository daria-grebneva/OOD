#pragma once
#include "WindDirection.h"

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	double windSpeed = 0;
	CWindDirection windDirection = 0;
};
