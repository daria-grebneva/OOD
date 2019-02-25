#pragma once
#include "WeatherData.h"

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:
	/* ����� Update ������ ���������, ����� ���������� ����������� ��� ������ ��������
	������ CObservable �� ����� �������� ��� �����, �.�. � ���������� IObserver ��
	�������� ���������
	*/
	void Update(SWeatherInfo const& data) override
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

	CStats<double> temperatureData;
	CStats<double> humidityData;
	CStats<double> pressureData;
};
