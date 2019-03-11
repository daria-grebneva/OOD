#pragma once
#include "CShape.h"
#include "Color.h"
#include "ISolidShape.h"

class CSolidShape : public ISolidShape
	, public CShape
{
public:
	CSolidShape(const Color& outlineColor, const Color& fillColor);
	virtual ~CSolidShape() = default;
	Color GetOutlineColor() const override;
	Color GetFillColor() const override;

private:
	Color m_fillColor;
};
