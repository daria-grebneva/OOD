#pragma once
#include "Coffee.h"

// Капуччино
class CCapuccino : public CCoffee
{
public:
	CCapuccino(PortionType portionType = PortionType::Standart)
		: CCoffee("Capuccino", portionType)
	{
	}

	double GetCost() const override
	{
		switch (m_portionType)
		{
		case PortionType::Standart:
			return 80;
			break;
		case PortionType::Double:
			return 120;
			break;
		default:
			break;
		}
	}
};
