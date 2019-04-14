#pragma once
#include "CShape.h"
#include "CommonTypes.h"

class CEllipse : public CShape
{
public:
	CEllipse(PointD const& center, float horizontalRadius, float verticalRadius);
	RectD GetFrame() override;
	void SetFrame(const RectD & rect) override;
	void DrawFigure(ICanvas & canvas)const override;

private:
	PointD m_center;
	float m_horizontalRadius;
	float m_verticalRadius;

};

