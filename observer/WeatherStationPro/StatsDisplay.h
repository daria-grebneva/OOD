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
		temperatureData.Update(data.temperature);
		humidityData.Update(data.humidity);
		pressureData.Update(data.pressure);
		windSpeed.Update(data.windSpeed);
		windDirection.Update(data.windDirection);

		std::cout << "Temperature: " << std::endl;
		temperatureData.Display();
		std::cout << "Humidity: " << std::endl;
		humidityData.Display();
		std::cout << "Pressure: " << std::endl;
		pressureData.Display();
		std::cout << "Wind Speed: " << std::endl;
		windSpeed.Display();
		std::cout << "Wind Direction: " << std::endl;
		windDirection.Display();
	}
	CStats<double> temperatureData;
	CStats<double> humidityData;
	CStats<double> pressureData;
	CStats<double> windSpeed;
	CStats<CWindDirection> windDirection;
};
