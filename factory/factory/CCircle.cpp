#include "stdafx.h"
#include "CCircle.h"
#include "CUtils.h"
#include "Config.h"

CCircle::CCircle(const CPoint& center, double radius, const Color& outlineColor, const Color& fillColor)
	: m_center(center)
	, m_radius(radius)
	, CSolidShape(outlineColor, fillColor)
{
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}

void CCircle::Draw(ICanvas& canvas) const
{
	canvas.FillCircle(m_center, m_radius, CUtils::ColorToHex(GetFillColor()));
	canvas.DrawCircle(GetCenter(), GetRadius(), CUtils::ColorToHex(GetOutlineColor()));
}
