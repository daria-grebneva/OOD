#pragma once
#include "IStyle.h"

class ILineStyle : public IStyle
{
public:
	virtual boost::optional<float> GetLineThikness() const = 0;
	virtual void SetLineThikness(float thikness) = 0;
};