#pragma once
#include "WeatherData.h"

class CDisplay : public IObserver<SWeatherInfo>
{
public:
	CDisplay(CWeatherData& in, CWeatherData& out)
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
		std::cout << data.stationName << std::endl;
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}

	CWeatherData& m_in;
	CWeatherData& m_out;
};
