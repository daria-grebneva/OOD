#include "stdafx.h"
#include "../WeatherStationDuo/Observer.h"
#include "../WeatherStationDuo/WeatherData.h"

using namespace std;

class Observer : public IObserver<SWeatherInfo>
{
public:
	Observer(std::stringstream& name)
		: m_stationName(name){};

private:
	std::stringstream& m_stationName;
	void Update(SWeatherInfo const& data, const IObservable<SWeatherInfo>& obs) override
	{
		m_stationName << data.stationName;
	}
};

TEST_CASE(" ", "[CObserver]")
{
	SECTION("Separate stations and their notifications")
	{
		std::stringstream stationNames;
		Observer display(stationNames);
		CWeatherData in;
		CWeatherData out;

		in.SetStationName("in");
		out.SetStationName("out");
		in.RegisterObserver(display, 1);
		out.RegisterObserver(display, 2);
		in.SetMeasurements(11, 12, 13);
		in.SetMeasurements(14, 15, 16);
		out.SetMeasurements(1, 2, 3);
		out.SetMeasurements(4, 5, 6);

		REQUIRE(stationNames.str() == "ininoutout");
		stationNames = std::stringstream();

		out.SetMeasurements(1, 2, 3);
		out.SetMeasurements(4, 5, 6);
		in.SetMeasurements(11, 12, 13);
		in.SetMeasurements(14, 15, 16);

		REQUIRE(stationNames.str() == "outoutinin");
	}
}
