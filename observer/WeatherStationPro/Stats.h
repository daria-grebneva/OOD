#pragma once
#include <climits>
#include <iostream>
template <typename T>
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
		std::cout << "	max : " << m_max << std::endl;
		std::cout << "	min : " << m_min << std::endl;
		std::cout << "	average : " << m_average << std::endl;
	}

private:
	double m_min = std::numeric_limits<double>::infinity();
	double m_max = -std::numeric_limits<double>::infinity();
	double m_acc = 0;
	double m_average = 0;
	unsigned m_countAcc = 0;
};
