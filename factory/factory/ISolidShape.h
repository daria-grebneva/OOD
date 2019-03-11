#pragma once
#include "IShape.h"
class ISolidShape : public virtual IShape
{
public:
	ISolidShape() = default;
	virtual ~ISolidShape() = default;
	virtual Color GetFillColor() const = 0;
};
