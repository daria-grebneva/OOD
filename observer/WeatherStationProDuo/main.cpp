// WeatherStationProDuo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Display.h"
#include "DisplayPro.h"
#include "StatsDisplay.h"
#include "StatsDisplayPro.h"

int main()
{
	CWeatherData data1;
	CWeatherDataPro data2;
	data1.SetStationName("in");
	data2.SetStationName("out");

	CDisplay display1;
	CDisplayPro display2;
	CStatsDisplay statsDisplay1;
	CStatsDisplayPro statsDisplay2;
	data1.RegisterObserver(display1, 1);
	data1.RegisterObserver(statsDisplay1, 2);
	data2.RegisterObserver(display2, 1);
	data2.RegisterObserver(statsDisplay2, 2);

	data1.SetMeasurements(1, 2, 760);
	data1.SetMeasurements(3, 4, 761);
	std::cout << "----------------" << std::endl;
	data2.SetMeasurements(5, 6, 750, 30, 40);
	data2.SetMeasurements(7, 8, 751, 50, 60);

	return 0;
}
