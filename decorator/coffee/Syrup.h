#pragma once
#include "CondimentDecorator.h"
#include "SyrupType.h"

// Добавка "Сироп"
class CSyrup : public CCondimentDecorator
{
public:
	CSyrup(IBeveragePtr&& beverage, SyrupType syrupType)
		: CCondimentDecorator(move(beverage))
		, m_syrupType(syrupType)
	{
	}

protected:
	double GetCondimentCost() const override
	{
		return 15;
	}
	std::string GetCondimentDescription() const override
	{
		return std::string(m_syrupType == SyrupType::Chocolate ? "Chocolate" : "Maple")
			+ " syrup";
	}

private:
	SyrupType m_syrupType;
};
