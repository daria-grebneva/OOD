#pragma once
#include "Color.h"
#include "ICanvas.h"

class CShape
{
public:
	CShape(const Color& color);
	virtual ~CShape() = default;
	Color GetOutlineColor() const;
	virtual void Draw(ICanvas& canvas) const = 0;

private:
	Color m_outlineColor;
};
