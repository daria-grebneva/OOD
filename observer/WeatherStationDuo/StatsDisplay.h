#pragma once
#include "WeatherData.h"

class CStatsDisplay : public IObserver<SWeatherInfo>
{
public:
	CStatsDisplay(CWeatherData& in, CWeatherData& out)
		: m_in(in)
		, m_out(out)
	{
	}

private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data, const IObservable<SWeatherInfo>& obs) override
	{
		if (&obs == &m_in) //сравнивать указания на один и тот же объект
		{
			inTemperatureData.Update(data.temperature);
			inHumidityData.Update(data.humidity);
			inPressureData.Update(data.pressure);

			std::cout << data.stationName << std::endl;
			std::cout << "Temperature: " << std::endl;
			inTemperatureData.Display();
			std::cout << "Humidity: " << std::endl;
			inHumidityData.Display();
			std::cout << "Pressure: " << std::endl;
			inPressureData.Display();
		}
		else if (&obs == &m_out)
		{
			outTemperatureData.Update(data.temperature);
			outHumidityData.Update(data.humidity);
			outPressureData.Update(data.pressure);

			std::cout << data.stationName << std::endl;
			std::cout << "Temperature: " << std::endl;
			outTemperatureData.Display();
			std::cout << "Humidity: " << std::endl;
			outHumidityData.Display();
			std::cout << "Pressure: " << std::endl;
			outPressureData.Display();
		}
	}
	CStats inTemperatureData;
	CStats inHumidityData;
	CStats inPressureData;

	CStats outTemperatureData;
	CStats outHumidityData;
	CStats outPressureData;

	CWeatherData& m_in;
	CWeatherData& m_out;
};
