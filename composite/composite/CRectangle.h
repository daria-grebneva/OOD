#pragma once
#include "CShape.h"
#include "CommonTypes.h"

class CRectangle : public CShape
{
public:
	CRectangle(PointD const & leftTop, float width, float height);
	RectD GetFrame() override;
	void SetFrame(const RectD & rect) override;
	void DrawFigure(ICanvas & canvas) const override;

private:
	PointD m_leftTop;
	float m_width;
	float m_height;
};

