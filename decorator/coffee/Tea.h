#pragma once
#include "Beverage.h"
#include "TeaSort.h"

// „ай
class CTea : public CBeverage
{
public:
	CTea(std::string description = "")
		: CBeverage(description + " Tea")
	{
	}

	double GetCost() const override
	{
		return 30;
	}
};
