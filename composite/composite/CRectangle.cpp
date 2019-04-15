#include "stdafx.h"
#include "CRectangle.h"

CRectangle::CRectangle(PointD const& leftTop, double width, double height)
	: m_leftTop(leftTop)
	, m_width(width)
	, m_height(height)
{
}

RectD CRectangle::GetFrame()
{
	return RectD{ m_leftTop.x, m_leftTop.y, m_width, m_height };
}

void CRectangle::SetFrame(const RectD& rect)
{
	m_leftTop = PointD{ rect.left, rect.top };
	m_width = rect.width;
	m_height = rect.height;
}

void CRectangle::DrawFigure(ICanvas& canvas) const
{
	canvas.DrawRectangle(m_leftTop, m_width, m_height);
}
