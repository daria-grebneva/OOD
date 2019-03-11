#include "stdafx.h"
#include "CShape.h"

CShape::CShape(const Color& color)
	: m_outlineColor(color)
{
}

Color CShape::GetOutlineColor() const
{
	return m_outlineColor;
}
