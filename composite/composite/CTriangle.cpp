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
	const auto oldFrame = GetFrame();
	auto SetNewPoint = [&](PointD& point) {
		double scaleX = (point.x - oldFrame.left) / oldFrame.width;
		double scaleY = (point.y - oldFrame.top) / oldFrame.height;
		point = PointD{ rect.left + rect.width * scaleX, rect.top + rect.height * scaleY };
	};

	SetNewPoint(m_p1);
	SetNewPoint(m_p2);
	SetNewPoint(m_p3);
}

void CTriangle::DrawFigure(ICanvas& canvas) const
{
	canvas.DrawTriangle(m_p1, m_p2, m_p3);
}
