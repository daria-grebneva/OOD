#pragma once
#include "CShape.h"
class ISolidShape : public virtual CShape
{
public:
	ISolidShape() = default;
	virtual ~ISolidShape() = default;
	virtual Color GetFillColor() const = 0;
};
