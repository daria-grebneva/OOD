#pragma once
#include "CShape.h"
#include "Color.h"

class CSolidShape : public CShape
{
public:
	CSolidShape(const Color& outlineColor, const Color& fillColor);
	virtual ~CSolidShape() = default;
	Color GetOutlineColor() const;
	Color GetFillColor() const;

private:
	Color m_fillColor;
};
