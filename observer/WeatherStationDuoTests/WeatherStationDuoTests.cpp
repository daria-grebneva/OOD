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
	void Update(SWeatherInfo const& data) override
	{
		m_stationName << data.stationName;
	}
};

TEST_CASE(" ", "[CObserver]")
{
	SECTION("Separation of stations and their notifications")
	{
		std::stringstream stationNames;
		Observer observer(stationNames);
		CWeatherData observable1;
		observable1.SetStationName("in");
		CWeatherData observable2;
		observable2.SetStationName("out");

		observable1.RegisterObserver(observer, 0);
		observable2.RegisterObserver(observer, 1);
		observable1.NotifyObservers();
		observable2.NotifyObservers();

		REQUIRE(stationNames.str() == "inout");
		stationNames = std::stringstream();
		observable2.NotifyObservers();
		observable1.NotifyObservers();
		REQUIRE(stationNames.str() == "outin");
	}
}
