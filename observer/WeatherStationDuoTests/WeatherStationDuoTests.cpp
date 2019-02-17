#include "stdafx.h"
#include "../WeatherStationDuo/Observer.h"
#include "../WeatherStationDuo/WeatherData.h"

using namespace std;

struct info
{
	string observableName;
};

class Observer : public IObserver<info>
{
public:
	Observer(std::ostream& output)
		: m_output(output){};

private:
	ostream& m_output;
	void Update(info const& data, const IObservable<info>& observabl) override
	{
		m_output << data.observableName;
	}
};

class Observable : public CObservable<info>
{
public:
	void SetName(std::string const& name)
	{
		m_name = name;
	}
	std::string GetName() const
	{
		return m_name;
	}

protected:
	info GetChangedData() const override
	{
		info data;
		data.observableName = this->GetName();
		return data;
	}

private:
	std::string m_name;
};

TEST_CASE(" ", "[CObserver]")
{
	SECTION("separation of stations and their notifications")
	{
		ostringstream output;
		Observer observer(output);
		Observable observable1;
		observable1.SetName("in");
		Observable observable2;
		observable2.SetName("out");

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
