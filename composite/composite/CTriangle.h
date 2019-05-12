#pragma once
#include "CShape.h"
#include "CommonTypes.h"

class CTriangle : public CShape
{
public:
	CTriangle(PointD const& p1, PointD const& p2, PointD const& p3);

	void DrawFigure(ICanvas& canvas) const override;

	RectD GetFrame() override;
	void SetFrame(const RectD& rect) override;

private:
	void UpdatePoint(PointD& point, const RectD& newFrame);
	PointD m_p1;
	PointD m_p2;
	PointD m_p3;
};
