#pragma once
#include "IShape.h"

class CShape : public virtual IShape
{
public:
	CShape(const Color& color);
	~CShape() = default;
	Color GetOutlineColor() const override;

private:
	Color m_outlineColor;
};
