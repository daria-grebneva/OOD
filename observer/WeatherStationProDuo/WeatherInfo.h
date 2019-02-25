#pragma once
#include <string>

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	std::string stationName;
};
