#pragma once
class CWindDirection
{
public:
	CWindDirection() = default;

	CWindDirection(unsigned int direction)
	{
		if (direction > 360)
		{
			direction = direction % 360;
		}

		m_direction = direction;
	}

	operator unsigned int() const
	{
		return m_direction;
	}

	CWindDirection operator+(CWindDirection& second)
	{
		auto result = second.m_direction + this->m_direction;
		if ((second.m_direction - this->m_direction) > 180
			|| (this->m_direction - second.m_direction) > 180)
		{
			result = result - 180;
		}
		return result;
	}

private:
	unsigned int m_direction = 0;
};
