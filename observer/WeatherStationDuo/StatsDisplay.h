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
	/* ����� Update ������ ���������, ����� ���������� ����������� ��� ������ ��������
	������ CObservable �� ����� �������� ��� �����, �.�. � ���������� IObserver ��
	�������� ���������
	*/
	void Update(SWeatherInfo const& data, const IObservable<SWeatherInfo>& obs) override
	{
		if (&obs == &m_in) //���������� �������� �� ���� � ��� �� ������
		{
			ProcessData(inTemperatureData, inHumidityData, inPressureData, data);
		}
		else if (&obs == &m_out)
		{
			ProcessData(outTemperatureData, outHumidityData, outPressureData, data);
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

	CStats inTemperatureData;
	CStats inHumidityData;
	CStats inPressureData;

	CStats outTemperatureData;
	CStats outHumidityData;
	CStats outPressureData;

	CWeatherData& m_in;
	CWeatherData& m_out;
};
