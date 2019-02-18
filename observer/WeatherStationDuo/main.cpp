#include "stdafx.h"
#include "WeatherData.h"

int main()
{
	CWeatherData in;
	CWeatherData out;
	CDisplay display;

	in.SetStationName("in");
	out.SetStationName("out");
	in.RegisterObserver(display, 1);
	out.RegisterObserver(display, 2);
	in.SetMeasurements(1, 2, 3);
	out.SetMeasurements(11, 12, 13);

	return 0;
}
