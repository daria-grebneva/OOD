#pragma once
#include "stdafx.h"
#include "Observer.h"
#include "WeatherData.h"
#include "WeatherInfoPro.h"

class CWeatherDataPro : public CObservable<SWeatherInfoPro>
{
public:
	// Температура в градусах Цельсия
	double GetTemperature() const
	{
		return m_temperature;
	}
	// Относительная влажность (0...100)
	double GetHumidity() const
	{
		return m_humidity;
	}
	// Атмосферное давление (в мм.рт.ст)
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
	SWeatherInfoPro GetChangedData() const override
	{
		SWeatherInfoPro info;
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
