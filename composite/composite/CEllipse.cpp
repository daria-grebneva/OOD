#include "stdafx.h"
#include "CEllipse.h"

CEllipse::CEllipse(PointD const& center, double horizontalRadius, double verticalRadius)
	: m_center(center)
	, m_horizontalRadius(horizontalRadius)
	, m_verticalRadius(verticalRadius)
{
}

RectD CEllipse::GetFrame()
{
	auto leftTop = PointD{ m_center.x - m_horizontalRadius, m_center.y - m_verticalRadius };
	return RectD{ leftTop.x, leftTop.y, 2 * m_horizontalRadius, 2 * m_verticalRadius };
}

void CEllipse::SetFrame(const RectD& rect)
{
	m_center = PointD{ rect.left + rect.width / 2, rect.top + rect.height / 2 };
	m_horizontalRadius = rect.width / 2;
	m_verticalRadius = rect.height / 2;
}

void CEllipse::DrawFigure(ICanvas& canvas) const
{
	double width = 2 * m_horizontalRadius;
	double height = 2 * m_verticalRadius;
	canvas.DrawEllipse(m_center.x, m_center.y, width, height);
}
