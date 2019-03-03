#pragma once
#include "Coffee.h"

// Латте
class CLatte : public CCoffee
{
public:
	CLatte(PortionType portionType = PortionType::Standart)
		: CCoffee("Latte", portionType)
	{
	}

	double GetCost() const override
	{
		switch (m_portionType)
		{
		case PortionType::Standart:
			return 90;
			break;
		case PortionType::Double:
			return 130;
			break;
		default:
			break;
		}
	}
};
