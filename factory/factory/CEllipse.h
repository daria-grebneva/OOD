#pragma once
#include "CPoint.h"
#include "CSolidShape.h"
#include "ICanvas.h"

class CEllipse : public CSolidShape
{
public:
	CEllipse(const CPoint& center, double horizontalRadius, double verticalRadius, const Color& outlineColor, const Color& fillColor);
	~CEllipse() = default;
	const CPoint GetCenter() const;
	const double GetHorizontalRadius() const;
	const double GetVerticalRadius() const;
	std::string ToString() const override;
	void Draw(ICanvas& canvas) const;

private:
	CPoint m_center;
	double m_horizontalRadius;
	double m_verticalRadius;
};
