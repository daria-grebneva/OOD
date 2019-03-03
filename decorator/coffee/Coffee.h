#pragma once
#include "Beverage.h"
#include "PortionType.h"

// Кофе
class CCoffee : public CBeverage
{
public:
	CCoffee(const std::string& description = "Coffee", PortionType portionType = PortionType::Standart)
		: CBeverage(GetDescription(portionType) + description)
		, m_portionType(portionType)
	{
	}

	std::string GetDescription(PortionType portionType)
	{
		std::string portion = "";
		switch (portionType)
		{
		case PortionType::Standart:
			portion = "standart";
			break;
		case PortionType::Double:
			portion = "double";
			break;
		default:
			break;
		}

		return "Get a " + portion + " cup of ";
	}

	double GetCost() const override
	{
		return 60;
	}

	PortionType m_portionType;
};
