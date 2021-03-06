#include "stdafx.h"
#include "Display.h"
#include "StatsDisplay.h"

using namespace std;

int main()
{
	CWeatherData data;

	CDisplay display;
	data.RegisterObserver(display, 0);

	CStatsDisplay statsDisplay;
	data.RegisterObserver(statsDisplay, 1);

	data.SetMeasurements(1, 2, 761, 30, 60);
	cout << "----------------" << endl;
	data.SetMeasurements(11, 12, 750, 10, 30);
	cout << "----------------" << endl;

	return 0;
}
