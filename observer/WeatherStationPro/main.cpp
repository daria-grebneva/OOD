#include "stdafx.h"
#include "WeatherData.h"

using namespace std;

int main()
{
	CWeatherData data;

	CDisplay display;
	data.RegisterObserver(display, 0);

	CStatsDisplay statsDisplay;
	data.RegisterObserver(statsDisplay, 1);

	data.SetMeasurements(3, 0.7, 760, 0, 120);
	cout << "----------------" << endl;
	data.SetMeasurements(6, 0.9, 754, 5, 360);
	cout << "----------------" << endl;
	data.SetMeasurements(10, 0.5, 761, 30, 80);
	cout << "----------------" << endl;
	data.SetMeasurements(-14, 0.6, 761, 15, 240);

	return 0;
}
