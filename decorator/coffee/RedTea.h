#pragma once
#include "Tea.h"

class CRedTea : public CTea
{
public:
	CRedTea(TeaSort sort = TeaSort::Black)
		: CTea(GetTeaDescription(sort))
	{
	}

	std::string GetTeaDescription(TeaSort sort)
	{
		return "Red";
	}
};
