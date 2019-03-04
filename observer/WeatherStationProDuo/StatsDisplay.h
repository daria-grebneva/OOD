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
		m_temperatureData.Update(data.temperature);
		m_humidityData.Update(data.humidity);
		m_pressureData.Update(data.pressure);

		std::cout << data.stationName << std::endl;
		std::cout << "Temperature: " << std::endl;
		m_temperatureData.Display();
		std::cout << "Humidity: " << std::endl;
		m_humidityData.Display();
		std::cout << "Pressure: " << std::endl;
		m_pressureData.Display();
	}

	CStats<double> m_temperatureData;
	CStats<double> m_humidityData;
	CStats<double> m_pressureData;
};
