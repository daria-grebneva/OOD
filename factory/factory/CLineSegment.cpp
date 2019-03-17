#include "stdafx.h"
#include "CLineSegment.h"
#include "CUtils.h"
#include "Config.h"

CLineSegment::CLineSegment(const CPoint& start, const CPoint& end, const Color& color)
	: m_start(start)
	, m_end(end)
	, CShape(color)
{
}

CPoint CLineSegment::GetStartPoint() const
{
	return m_start;
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_end;
}

void CLineSegment::Draw(ICanvas& canvas) const
{
	canvas.DrawLine(GetStartPoint(), GetEndPoint(), CUtils::ColorToHex(GetOutlineColor()));
}

double CLineSegment::GetDistanceBetweenVertices(const CPoint& vertex1, const CPoint& vertex2) const
{
	return sqrt(pow((vertex1.x - vertex2.x), QUADRATIC_DEGREE) + pow((vertex1.y - vertex2.y), QUADRATIC_DEGREE));
}
