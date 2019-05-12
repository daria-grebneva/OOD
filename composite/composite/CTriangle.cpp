#include "stdafx.h"
#include "CTriangle.h"

CTriangle::CTriangle(PointD const& p1, PointD const& p2, PointD const& p3)
	: m_p1(p1)
	, m_p2(p2)
	, m_p3(p3)
{
}

RectD CTriangle::GetFrame()
{
	double minX = std::min({ m_p1.x, m_p2.x, m_p3.x });
	double maxX = std::max({ m_p1.x, m_p2.x, m_p3.x });

	double minY = std::min({ m_p1.x, m_p2.x, m_p3.x });
	double maxY = std::max({ m_p1.x, m_p2.x, m_p3.x });

	return RectD{ minX, minY, maxX - minX, maxY - minY };
}

void CTriangle::SetFrame(const RectD& rect)
{
	UpdatePoint(m_p1, rect);
	UpdatePoint(m_p2, rect);
	UpdatePoint(m_p3, rect);
}

void CTriangle::UpdatePoint(PointD& point, const RectD& newFrame)
{
	const auto oldFrame = GetFrame();
	double scaleX = (point.x - oldFrame.left) / oldFrame.width;
	double scaleY = (point.y - oldFrame.top) / oldFrame.height;
	point = PointD{ newFrame.left + newFrame.width * scaleX, newFrame.top + newFrame.height * scaleY };
}

void CTriangle::DrawFigure(ICanvas& canvas) const
{
	canvas.DrawTriangle(m_p1, m_p2, m_p3);
}
