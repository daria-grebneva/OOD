#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

class CWindDirection
{
public:
	CWindDirection() = default;

	CWindDirection(unsigned int direction)
	{
		m_x += cos(direction * M_PI / 180);
		m_y += sin(direction * M_PI / 180);
		double deg = atan2(m_y, m_x) * 180 / M_PI;

		m_direction = (deg < 0) ? (360 + deg) : deg;
	}

	operator double() const
	{
		return m_direction;
	}

private:
	double m_x = 0;
	double m_y = 0;
	double m_direction = 0;
};
