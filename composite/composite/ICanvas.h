#pragma once
#include "CommonTypes.h"
#include <vector>

class ICanvas
{
public:
	virtual void SetLineColor(RGBAColor color) = 0;
	virtual void SetLineThickness(float thickness) = 0;
	virtual void SetFillColor(RGBAColor const& color) = 0;
	/*virtual void MoveTo(double x, double y) = 0;
	virtual void LineTo(double x, double y) = 0;*/
	virtual void DrawLine(const PointD& startPoint, const PointD& endPoint) = 0;
	virtual void DrawEllipse(double left, double top, double width, double height) = 0;
	virtual void DrawTriangle(PointD const& p1, PointD const& p2, PointD const& p3) = 0;
	virtual void DrawRectangle(PointD const& leftTop, double width, double height) = 0;
	//virtual void FillShape(std::vector<PointD> const& points) = 0;
	//virtual void LineShape(std::vector<PointD> const& points) = 0;

	//virtual ~ICanvas() = 0;

};