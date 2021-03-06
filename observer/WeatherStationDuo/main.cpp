#include "stdafx.h"
#include "WeatherData.h"
#include "StatsDisplay.h"

int main()
{
	CWeatherData in;
	CWeatherData out;
	CStatsDisplay display(in, out);

	in.SetStationName("in");
	out.SetStationName("out");
	in.RegisterObserver(display, 1);
	out.RegisterObserver(display, 2);

	in.SetMeasurements(11, 12, 13);
	in.SetMeasurements(14, 15, 16);
	out.SetMeasurements(1, 2, 3);
	out.SetMeasurements(4, 5, 6);

	return 0;
}
