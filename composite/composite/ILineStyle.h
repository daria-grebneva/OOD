#pragma once
#include "IStyle.h"

class ILineStyle : public IStyle
{
public:
	virtual boost::optional<float> GetLineThi�kness() const = 0;
	virtual void SetLineThi�kness(float thikness) = 0;
};
