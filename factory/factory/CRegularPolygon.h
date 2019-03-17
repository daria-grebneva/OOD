#pragma once
#include "CPoint.h"
#include "CSolidShape.h"
#include "Color.h"
#include "ICanvas.h"

class CRegularPolygon : public CSolidShape
{
public:
	CRegularPolygon(const CPoint& center, double radius, size_t pointsCount, const Color& outlineColor, const Color& fillColor);
	~CRegularPolygon() = default;
	void Draw(ICanvas& canvas) const override;
	CPoint GetCenter() const;
	double GetRadius() const;
	size_t GetPointsCount() const;

private:
	CPoint m_center;
	double m_radius;
	size_t m_pointsCount;
	std::vector<CPoint> GetVertices() const;
};
