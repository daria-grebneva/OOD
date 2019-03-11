#include "stdafx.h"
#include "CSolidShape.h"

CSolidShape::CSolidShape(const Color& outlineColor, const Color& fillColor)
	: CShape(outlineColor)
	, m_fillColor(fillColor)
{
}

Color CSolidShape::GetOutlineColor() const
{
	return CShape::GetOutlineColor();
}

Color CSolidShape::GetFillColor() const
{
	return m_fillColor;
}
