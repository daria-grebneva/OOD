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
			ProcessData(m_inTemperatureData, m_inHumidityData, m_inPressureData, data);
		}
		else if (&obs == &m_out)
		{
			ProcessData(m_outTemperatureData, m_outHumidityData, m_outPressureData, data);
		}
	}

	void ProcessData(CStats temperatureData, CStats humidityData, CStats pressureData, SWeatherInfo const& data)
	{
		temperatureData.Update(data.temperature);
		humidityData.Update(data.humidity);
		pressureData.Update(data.pressure);

		std::cout << data.stationName << std::endl;
		std::cout << "Temperature: " << std::endl;
		temperatureData.Display();
		std::cout << "Humidity: " << std::endl;
		humidityData.Display();
		std::cout << "Pressure: " << std::endl;
		pressureData.Display();
	}

	CStats m_inTemperatureData;
	CStats m_inHumidityData;
	CStats m_inPressureData;

	CStats m_outTemperatureData;
	CStats m_outHumidityData;
	CStats m_outPressureData;

	CWeatherData& m_in;
	CWeatherData& m_out;
};
