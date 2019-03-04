#pragma once
#include "Tea.h"

class CHerbalTea : public CTea
{
public:
	CHerbalTea(TeaSort sort = TeaSort::Black)
		: CTea(GetTeaDescription(sort))
	{
	}

	std::string GetTeaDescription(TeaSort sort)
	{
		return "Herbal";
	}
};
