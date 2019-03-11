#include "stdafx.h"
#include "CEllipse.h"
#include "CUtils.h"
#include "Config.h"

CEllipse::CEllipse(const CPoint& center, double horizontalRadius, double verticalRadius, const Color& outlineColor, const Color& fillColor)
	: m_center(center)
	, m_horizontalRadius(horizontalRadius)
	, m_verticalRadius(verticalRadius)
	, CSolidShape(outlineColor, fillColor)
{
}

const CPoint CEllipse::GetCenter() const
{
	return m_center;
}

const double CEllipse::GetHorizontalRadius() const
{
	return m_horizontalRadius;
}

const double CEllipse::GetVerticalRadius() const
{
	return m_verticalRadius;
}

std::string CEllipse::ToString() const
{
	std::ostringstream strm;
	strm << std::fixed << std::setprecision(PRECISION);
	strm << "perimeter:" << GetPerimeter() << " area:" << GetArea()
		 << " fill color:" << GetFillColor() << " outline color:" << GetOutlineColor()
		 << " center.x:" << m_center.x << " center.y:" << m_center.y
		 << " horisontal radius:" << m_horizontalRadius << " vertical radius:" << m_verticalRadius << std::endl;

	return strm.str();
}

void CEllipse::Draw(ICanvas& canvas) const
{
	auto width = m_horizontalRadius * 2.f;
	auto height = m_verticalRadius * 2.f;
	canvas.FillEllipse((m_center.x - m_horizontalRadius), (m_center.y - m_verticalRadius), width, height, CUtils::ColorToHex(GetFillColor()));
	canvas.DrawEllipse((m_center.x - m_horizontalRadius), (m_center.y - m_verticalRadius), width, height, CUtils::ColorToHex(GetOutlineColor()));
}
