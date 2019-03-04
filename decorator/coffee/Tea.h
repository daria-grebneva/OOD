#pragma once
#include "Beverage.h"
#include "TeaSort.h"

// ���
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
