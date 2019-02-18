#include "stdafx.h"
#include "../WeatherStationDuo/Observer.h"
#include "../WeatherStationDuo/WeatherData.h"

using namespace std;

class Observer : public IObserver<SWeatherInfo>
{
public:
	Observer(std::ostream& output)
		: m_output(output){};

private:
	ostream& m_output;
	void Update(SWeatherInfo const& data) override
	{
		m_output << data.stationName;
	}
};

TEST_CASE(" ", "[CObserver]")
{
	SECTION("separation of stations and their notifications")
	{
		ostringstream output;
		Observer observer(output);
		CWeatherData observable1;
		observable1.SetStationName("in");
		CWeatherData observable2;
		observable2.SetStationName("out");

		observable1.RegisterObserver(observer, 0);
		observable2.RegisterObserver(observer, 1);
		observable1.NotifyObservers();
		observable2.NotifyObservers();

		REQUIRE(output.str() == "inout");
		output = ostringstream();
		observable2.NotifyObservers();
		observable1.NotifyObservers();
		REQUIRE(output.str() == "outin");
	}
}
