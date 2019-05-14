#include "stdafx.h"
#include "CShape.h"
#include "CUtils.h"

CShape::CShape()
	: m_fillStyle(std::make_shared<CFillStyle>(true, Colors::WHITE))
	, m_lineStyle(std::make_shared<CLineStyle>(true, Colors::WHITE, 0))
{
}

std::shared_ptr<ILineStyle> CShape::GetLineStyle()
{
	return m_lineStyle;
}

std::shared_ptr<const ILineStyle> CShape::GetLineStyle() const
{
	return m_lineStyle;
}

std::shared_ptr<IStyle> CShape::GetFillStyle()
{
	return m_fillStyle;
}

std::shared_ptr<const IStyle> CShape::GetFillStyle() const
{
	return m_fillStyle;
}

std::shared_ptr<IGroupShape> CShape::GetGroup()
{
	return nullptr;
}

std::shared_ptr<const IGroupShape> CShape::GetGroup() const
{
	return nullptr;
}

RGBAColor CShape::GetLineColor() const
{
	return (m_lineStyle->IsEnabled() ? m_lineStyle->GetColor().get() : ColorToHex("000000ff"));
}

RGBAColor CShape::GetFillColor() const
{
	return (m_fillStyle->IsEnabled() ? m_fillStyle->GetColor().get() : ColorToHex("000000ff"));
}

float CShape::GetLineThickness() const
{
	return (m_lineStyle->IsEnabled() ? m_lineStyle->GetLineThickness().get() : 0);
}

void CShape::Draw(ICanvas& canvas) const
{
	canvas.SetLineColor(GetLineColor());
	canvas.SetFillColor(GetFillColor());
	canvas.SetLineThickness(GetLineThickness());

	DrawFigure(canvas);
}

RGBAColor CShape::ColorToHex(const std::string color)
{
	uint32_t x;
	std::stringstream ss;
	ss << std::hex << color;
	ss >> x;
	return x;
}
