#pragma once
#include "Tea.h"

class CGreenTea : public CTea
{
public:
	CGreenTea(TeaSort sort = TeaSort::Black)
		: CTea(GetTeaDescription(sort))
	{
	}

	std::string GetTeaDescription(TeaSort sort)
	{
		return "Green";
	}
};
