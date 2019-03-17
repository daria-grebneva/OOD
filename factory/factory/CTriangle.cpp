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
