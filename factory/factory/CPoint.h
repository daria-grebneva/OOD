#pragma once
class CPoint
{
public:
	CPoint() = default;
	CPoint(double x, double y);
	~CPoint() = default;

	double x = 0;
	double y = 0;
};
