#pragma once
#include "IStyle.h"

class ILineStyle : public IStyle
{
public:
	virtual boost::optional<float> GetLineThickness() const = 0;
	virtual void SetLineThickness(float thikness) = 0;
};
