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

double CLineSegment::GetArea() const
{
	return 0;
}

double CLineSegment::GetPerimeter() const
{
	return GetDistanceBetweenVertices(m_end, m_start);
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

std::string CLineSegment::ToString() const
{
	std::ostringstream strm;
	strm << std::fixed << std::setprecision(PRECISION);
	strm << "perimeter:" << GetPerimeter() << " area:" << GetArea()
		 << " outline color:" << GetOutlineColor()
		 << " start vertex: { " << m_start.x << ", " << m_start.y << " }"
		 << " end vertex: { " << m_end.x << ", " << m_end.y << " }"
		 << std::endl;

	return strm.str();
}
