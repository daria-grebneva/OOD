#include "stdafx.h"
#include "CRegularPolygon.h"
#include "CUtils.h"
#include "Config.h"

CRegularPolygon::CRegularPolygon(const CPoint& center, double radius, size_t pointsCount, const Color& outlineColor, const Color& fillColor)
	: m_center(center)
	, m_radius(radius)
	, m_pointsCount(pointsCount)
	, CSolidShape(outlineColor, fillColor)
{
}

void CRegularPolygon::Draw(ICanvas& canvas) const
{
	std::vector<CPoint> points = GetVertices();

	canvas.FillPolygon(points, CUtils::ColorToHex(GetFillColor()));
	uint32_t outlineColor = CUtils::ColorToHex(GetOutlineColor());

	for (auto i = points.size() - 1; i != 0; --i)
	{
		canvas.DrawLine(points[i], points[i - 1], outlineColor);
	}
}

CPoint CRegularPolygon::GetCenter() const
{
	return m_center;
}

double CRegularPolygon::GetRadius() const
{
	return m_radius;
}

size_t CRegularPolygon::GetPointsCount() const
{
	return m_pointsCount;
}

std::vector<CPoint> CRegularPolygon::GetVertices() const
{
	std::vector<CPoint> result;
	const double STEP = 360.0 / m_pointsCount;

	for (double angle = 0; angle != 360.0; angle += STEP)
	{
		CPoint point;
		double radians = static_cast<double>(angle * M_PI / 180.0);
		point.x = m_center.x + m_radius * cos(radians);
		point.y = m_center.y + m_radius * sin(radians);

		result.emplace_back(point);
	}

	return result;
}
