#pragma once
#include "stdafx.h"
#include "WindDirection.h"
#include "Observer.h"
#include "WeatherData.h"

struct SWeatherInfoProDuo : public SWeatherInfo
{
	double windSpeed = 0;
	CWindDirection windDirection = 0;
};

class CDisplayProDuo : public IObserver<SWeatherInfoProDuo>
{
private:
	/* ����� Update ������ ���������, ����� ���������� ����������� ��� ������ ��������
	������ CObservable �� ����� �������� ��� �����, �.�. � ���������� IObserver ��
	�������� ���������
	*/
	void Update(SWeatherInfoProDuo const& data, const IObservable<SWeatherInfoProDuo>& observable) override
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

class CStatsDisplayProDuo : public IObserver<SWeatherInfoProDuo>
{
private:
	/* ����� Update ������ ���������, ����� ���������� ����������� ��� ������ ��������
	������ CObservable �� ����� �������� ��� �����, �.�. � ���������� IObserver ��
	�������� ���������
	*/
	void Update(SWeatherInfoProDuo const& data, const IObservable<SWeatherInfoProDuo>& observable) override
	{
		temperatureData.Update(data.temperature);
		humidifyData.Update(data.humidity);
		pressureData.Update(data.pressure);
		windSpeed.Update(data.windSpeed);
		windDirection.Update(data.windDirection);

		std::cout << data.stationName << std::endl;
		std::cout << "Temperature: " << std::endl;
		temperatureData.Display();
		std::cout << "Humidify: " << std::endl;
		humidifyData.Display();
		std::cout << "Pressure: " << std::endl;
		pressureData.Display();
		std::cout << "Wind Speed: " << std::endl;
		windSpeed.Display();
		std::cout << "Wind Direction: " << std::endl;
		windDirection.Display();
	}

	CStats<double> temperatureData;
	CStats<double> humidifyData;
	CStats<double> pressureData;
	CStats<double> windSpeed;
	CStats<CWindDirection> windDirection;
};

class CWeatherDataProDuo : public CObservable<SWeatherInfoProDuo>
{
public:
	// ����������� � �������� �������
	double GetTemperature() const
	{
		return m_temperature;
	}
	// ������������� ��������� (0...100)
	double GetHumidity() const
	{
		return m_humidity;
	}
	// ����������� �������� (� ��.��.��)
	double GetPressure() const
	{
		return m_pressure;
	}

	double GetWindSpeed() const
	{
		return m_windSpeed;
	}

	CWindDirection GetWindDirection() const
	{
		return m_windDirection;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure, double windSpeed, CWindDirection windDirection)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;
		m_windSpeed = windSpeed;
		m_windDirection = windDirection;

		MeasurementsChanged();
	}

	void SetStationName(std::string const& name)
	{
		m_stationName = name;
	}

	std::string GetStationName() const
	{
		return m_stationName;
	}

protected:
	SWeatherInfoProDuo GetChangedData() const override
	{
		SWeatherInfoProDuo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		info.stationName = GetStationName();
		info.windSpeed = GetWindSpeed();
		info.windDirection = GetWindDirection();
		return info;
	}

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	std::string m_stationName;
	double m_windSpeed = 0;
	CWindDirection m_windDirection = 0;
};

