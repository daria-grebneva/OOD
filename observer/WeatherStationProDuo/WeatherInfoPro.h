#pragma once
#include "WeatherInfo.h"
#include "WindDirection.h"

struct SWeatherInfoPro : public SWeatherInfo
{
	double windSpeed = 0;
	CWindDirection windDirection = 0;
};
