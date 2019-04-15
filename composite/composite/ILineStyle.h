#pragma once
#include "IStyle.h"

class ILineStyle : public IStyle
{
public:
	virtual boost::optional<float> GetLineThiñkness() const = 0;
	virtual void SetLineThiñkness(float thikness) = 0;
};
