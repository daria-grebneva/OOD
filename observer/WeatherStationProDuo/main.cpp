// WeatherStationProDuo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "WeatherData.h"

int main()
{
	CWeatherData data1;
	data1.SetStationName("in");
	CWeatherData data2;
	data2.SetStationName("out");

	CDisplay display1;
	CDisplay display2;
	CStatsDisplay statsDisplay1;
	CStatsDisplay statsDisplay2;
	data1.RegisterObserver(display1, 1);
	data1.RegisterObserver(statsDisplay1, 2);
	data2.RegisterObserver(display2, 1);
	data2.RegisterObserver(statsDisplay2, 2);

	data1.SetMeasurements(3, 0.7, 760, 20, 25);
	std::cout << "----------------" << std::endl;
	data2.SetMeasurements(4, 0.8, 761, 30, 40);

	return 0;
}
