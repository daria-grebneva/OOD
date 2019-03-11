#pragma once
#include "CPoint.h"
#include "CShape.h"
#include "ICanvas.h"

class CLineSegment : public CShape
{
public:
	CLineSegment(const CPoint& start, const CPoint& end, const Color& color);
	~CLineSegment() = default;
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;
	void Draw(ICanvas& canvas) const;

private:
	double GetDistanceBetweenVertices(const CPoint& vertex1, const CPoint& vertex2) const;

	CPoint m_start;
	CPoint m_end;
};
