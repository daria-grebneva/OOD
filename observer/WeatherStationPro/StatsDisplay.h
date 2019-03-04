#pragma once
#include "WeatherData.h"

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		m_temperatureData.Update(data.temperature);
		m_humidityData.Update(data.humidity);
		m_pressureData.Update(data.pressure);
		m_windSpeed.Update(data.windSpeed);
		m_windDirection.Update(data.windDirection);

		std::cout << "Temperature: " << std::endl;
		m_temperatureData.Display();
		std::cout << "Humidity: " << std::endl;
		m_humidityData.Display();
		std::cout << "Pressure: " << std::endl;
		m_pressureData.Display();
		std::cout << "Wind Speed: " << std::endl;
		m_windSpeed.Display();
		std::cout << "Wind Direction: " << std::endl;
		m_windDirection.Display();
	}
	CStats<double> m_temperatureData;
	CStats<double> m_humidityData;
	CStats<double> m_pressureData;
	CStats<double> m_windSpeed;
	CStats<CWindDirection> m_windDirection;
};
