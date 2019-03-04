#pragma once
#include "Tea.h"

class CBlackTea : public CTea
{
public:
	CBlackTea(TeaSort sort = TeaSort::Black)
		: CTea(GetTeaDescription(sort))
	{
	}

	std::string GetTeaDescription(TeaSort sort)
	{
		return "Black";
	}
};
