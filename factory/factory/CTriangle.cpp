#include "stdafx.h"
#include "CTriangle.h"
#include "CUtils.h"
#include "Config.h"

CTriangle::CTriangle(const CPoint& v1, const CPoint& v2, const CPoint& v3, const Color& outlineColor, const Color& fillColor)
	: m_vertex1(v1)
	, m_vertex2(v2)
	, m_vertex3(v3)
	, CSolidShape(outlineColor, fillColor)
{
}

double CTriangle::GetPerimeter() const
{
	return (GetDistanceBetweenVertices(m_vertex2, m_vertex1) + GetDistanceBetweenVertices(m_vertex3, m_vertex2) + GetDistanceBetweenVertices(m_vertex1, m_vertex3));
}

double CTriangle::GetArea() const
{
	return abs(0.5 * (m_vertex1.x * (m_vertex2.y - m_vertex3.y) + m_vertex2.x * (m_vertex3.y - m_vertex1.y) + m_vertex3.x * (m_vertex1.y - m_vertex2.y)));
}

CPoint CTriangle::GetVertex1() const
{
	return m_vertex1;
}

CPoint CTriangle::GetVertex2() const
{
	return m_vertex2;
}

CPoint CTriangle::GetVertex3() const
{
	return m_vertex3;
}

void CTriangle::Draw(ICanvas& canvas) const
{
	std::vector<CPoint> points = {
		GetVertex1(),
		GetVertex2(),
		GetVertex3()
	};

	canvas.FillPolygon(points, CUtils::ColorToHex(GetFillColor()));

	uint32_t outlineColor = CUtils::ColorToHex(GetOutlineColor());
	canvas.DrawLine(points[0], points[1], outlineColor);
	canvas.DrawLine(points[1], points[2], outlineColor);
	canvas.DrawLine(points[0], points[2], outlineColor);
}

double CTriangle::GetDistanceBetweenVertices(const CPoint& vertex1, const CPoint& vertex2) const
{
	return sqrt(pow((vertex1.x - vertex2.x), QUADRATIC_DEGREE) + pow((vertex1.y - vertex2.y), QUADRATIC_DEGREE));
}

std::string CTriangle::ToString() const
{
	std::ostringstream strm;
	strm << std::fixed << std::setprecision(PRECISION);
	strm << "perimeter:" << GetPerimeter() << " area:" << GetArea()
		 << " fill color:" << GetFillColor() << " outline color:" << GetOutlineColor()
		 << " vertex 1: { " << m_vertex1.x << ", " << m_vertex1.y << " }"
		 << " vertex 2: { " << m_vertex2.x << ", " << m_vertex2.y << " }"
		 << " vertex 3: { " << m_vertex3.x << ", " << m_vertex3.y << " }"
		 << std::endl;

	return strm.str();
}
