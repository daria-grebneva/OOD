#include "stdafx.h"
#include "CRectangle.h"
#include "CUtils.h"
#include "Config.h"

CRectangle::CRectangle(const CPoint& leftTop, double width, double height, const Color& outlineColor, const Color& fillColor)
	: m_leftTop(leftTop)
	, m_width(width)
	, m_height(height)
	, CSolidShape::CSolidShape(outlineColor, fillColor)
{
}

double CRectangle::GetArea() const
{
	return m_width * m_height;
}

double CRectangle::GetPerimeter() const
{
	return 2.0 * (m_width + m_height);
}

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTop;
}

CPoint CRectangle::GetRightTop() const
{
	return { m_leftTop.x + m_width, m_leftTop.y };
}

CPoint CRectangle::GetLeftBottom() const
{
	return { m_leftTop.x, m_leftTop.y + m_height };
}

CPoint CRectangle::GetRightBottom() const
{
	return { m_leftTop.x + m_width, m_leftTop.y + m_height };
}

double CRectangle::GetWidth() const
{
	return m_width;
}

double CRectangle::GetHeight() const
{
	return m_height;
}

void CRectangle::Draw(ICanvas& canvas) const
{
	std::vector<CPoint> points = {
		GetLeftTop(),
		GetRightTop(),
		GetRightBottom(),
		GetLeftBottom(),
	};

	canvas.FillPolygon(points, CUtils::ColorToHex(GetFillColor()));

	uint32_t outlineColor = CUtils::ColorToHex(GetOutlineColor());
	canvas.DrawLine(points[0], points[1], outlineColor);
	canvas.DrawLine(points[1], points[2], outlineColor);
	canvas.DrawLine(points[2], points[3], outlineColor);
	canvas.DrawLine(points[3], points[0], outlineColor);
}

std::string CRectangle::ToString() const
{
	std::ostringstream strm;
	strm << std::fixed << std::setprecision(PRECISION);
	strm << "perimeter:" << GetPerimeter() << " area:" << GetArea()
		 << " fill color:" << GetFillColor() << " outline color:" << GetOutlineColor()
		 << " widht:" << m_width << " height:" << m_height
		 << " left top vertex: { " << m_leftTop.x << ", " << m_leftTop.y << " }" << std::endl;

	return strm.str();
}
