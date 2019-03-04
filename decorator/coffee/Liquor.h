#pragma once
#include "CondimentDecorator.h"
#include "LiquorType.h"

// Сироп
class CLiquor : public CCondimentDecorator
{
public:
	CLiquor(IBeveragePtr&& beverage, LiquorType liquorType = LiquorType::Chocolate)
		: CCondimentDecorator(move(beverage))
		, m_liquorType(liquorType)
	{
	}

	double GetCondimentCost() const override
	{
		return 50;
	}

	std::string GetCondimentDescription() const override
	{
		return CLiquor::GetLiquorType(m_liquorType) + " Liquor";
	}

private:
	LiquorType m_liquorType;

	static std::string GetLiquorType(LiquorType liquorType)
	{
		switch (liquorType)
		{
		case LiquorType::Walnut:
			return "Walnut";
			break;
		case LiquorType::Chocolate:
			return "Chocolate";
			break;
		default:
			return "";
			break;
		}
	}
};
