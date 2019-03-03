#pragma once
#include "Beverage.h"
#include "MilkshakePortionType.h"

// Молочный коктейль
class CMilkshake : public CBeverage
{
public:
	CMilkshake(MilkshakePortionType portionType = MilkshakePortionType::Standart)
		: CBeverage(GetDescription(portionType) + " Milkshake")
		, m_portionType(portionType)
	{
	}

	std::string GetDescription(MilkshakePortionType portionType)
	{
		std::string portion = "";
		switch (portionType)
		{
		case MilkshakePortionType::Small:
			portion = "Small";
			break;
		case MilkshakePortionType::Standart:
			portion = "Standart";
			break;
		case MilkshakePortionType::Big:
			portion = "Big";
			break;
		default:
			break;
		}

		return portion;
	}

	double GetCost() const override
	{
		switch (m_portionType)
		{
		case MilkshakePortionType::Small:
			return 50;
			break;
		case MilkshakePortionType::Standart:
			return 60;
			break;
		case MilkshakePortionType::Big:
			return 80;
			break;
		default:
			return 0;
			break;
		}
	}

private:
	MilkshakePortionType m_portionType;
};
