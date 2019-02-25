#pragma once
#include "Observer.h"
#include <algorithm>
#include <climits>
#include <iostream>
#include <string>
#include <vector>

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	std::string stationName;
};

class CWeatherData : public CObservable<SWeatherInfo>
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

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;

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
	SWeatherInfo GetChangedData() const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		info.stationName = GetStationName();
		return info;
	}

private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	std::string m_stationName;
};

class CDisplay : public IObserver<SWeatherInfo>
{
public:
	CDisplay(CWeatherData& in, CWeatherData& out)
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
		std::cout << data.stationName << std::endl;
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}
	CWeatherData& m_in;
	CWeatherData& m_out;
};

class CStats
{

public:
	void Update(const double& value)
	{
		if (m_min > value)
		{
			m_min = value;
		}
		if (m_max < value)
		{
			m_max = value;
		}
		m_acc += value;
		++m_countAcc;
		m_average = m_acc / m_countAcc;
	}
	void Display()
	{
		std::cout << "Max Temp " << m_max << std::endl;
		std::cout << "Min Temp " << m_min << std::endl;
		std::cout << "Average Temp " << m_average << std::endl;
		std::cout << "----------------" << std::endl;
	}

private:
	double m_min = std::numeric_limits<double>::infinity();
	double m_max = -std::numeric_limits<double>::infinity();
	double m_acc = 0;
	double m_average = 0;
	unsigned m_countAcc = 0;
};

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
			std::cout << "IN" << std::endl;
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
		else
		{
			temperatureData1.Update(data.temperature);
			humidityData1.Update(data.humidity);
			pressureData1.Update(data.pressure);

			std::cout << data.stationName << std::endl;
			std::cout << "Temperature: " << std::endl;
			temperatureData1.Display();
			std::cout << "Humidity: " << std::endl;
			humidityData1.Display();
			std::cout << "Pressure: " << std::endl;
			pressureData1.Display();
		}
	}
	CStats temperatureData;
	CStats humidityData;
	CStats pressureData;

	CStats temperatureData1;
	CStats humidityData1;
	CStats pressureData1;

	CWeatherData& m_in;
	CWeatherData& m_out;
};
