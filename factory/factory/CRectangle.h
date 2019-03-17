#pragma once
#include "CPoint.h"
#include "CSolidShape.h"
#include "Color.h"
#include "ICanvas.h"

class CRectangle : public CSolidShape
{

public:
	CRectangle(const CPoint& leftTop, double width, double height, const Color& outlineColor, const Color& fillColor);
	~CRectangle() = default;
	CPoint GetLeftTop() const;
	CPoint GetRightTop() const;
	CPoint GetLeftBottom() const;
	CPoint GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;
	void Draw(ICanvas& canvas) const;

private:
	double m_width = 0;
	double m_height = 0;
	CPoint m_leftTop;
};
