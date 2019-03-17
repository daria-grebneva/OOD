#pragma once
#include "CPoint.h"
#include "CSolidShape.h"
#include "ICanvas.h"

class CCircle : public CSolidShape
{
public:
	CCircle(const CPoint& center, double radius,
		const Color& outlineColor,
		const Color& fillColor);
	~CCircle() = default;
	CPoint GetCenter() const;
	double GetRadius() const;
	void Draw(ICanvas& canvas) const;

private:
	double m_radius;
	CPoint m_center;
};
