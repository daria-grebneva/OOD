#pragma once
#include "CShape.h"
#include "CommonTypes.h"

class CEllipse : public CShape
{
public:
	CEllipse(PointD const& center, double horizontalRadius, double verticalRadius);
	RectD GetFrame() override;
	void SetFrame(const RectD& rect) override;
	void DrawFigure(ICanvas& canvas) const override;

private:
	PointD m_center;
	double m_horizontalRadius;
	double m_verticalRadius;
};
