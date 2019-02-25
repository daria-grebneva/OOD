#pragma once
#include "WeatherDataPro.h"

class CDisplayPro : public IObserver<SWeatherInfoPro>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	void Update(SWeatherInfoPro const& data) override
	{
		std::cout << data.stationName << std::endl;
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "Current Wind Speed " << data.windSpeed << std::endl;
		std::cout << "Current Wind Direction " << data.windDirection << std::endl;
		std::cout << "----------------" << std::endl;
	}
};
