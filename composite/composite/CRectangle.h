#pragma once
#include "CShape.h"
#include "CommonTypes.h"

class CRectangle : public CShape
{
public:
	CRectangle(PointD const& leftTop, double width, double height);
	RectD GetFrame() override;
	void SetFrame(const RectD& rect) override;
	void DrawFigure(ICanvas& canvas) const override;

private:
	PointD m_leftTop;
	double m_width;
	double m_height;
};
