#pragma once
#include "Beverage.h"
#include "TeaSort.h"

// ×àé
class CTea : public CBeverage
{
public:
	CTea(TeaSort sort = TeaSort::Black)
		: CBeverage(GetSortOfTea(sort) + " Tea")
		, m_sort(sort)
	{
	}

	std::string GetSortOfTea(TeaSort sort)
	{
		switch (sort)
		{
		case TeaSort::Red:
			return "Red";
			break;
		case TeaSort::Green:
			return "Green";
			break;
		case TeaSort::Black:
			return "Black";
			break;
		case TeaSort::Herbal:
			return "Herbal";
			break;
		default:
			break;
		}
	}

	double GetCost() const override
	{
		return 30;
	}

	TeaSort m_sort;
};
