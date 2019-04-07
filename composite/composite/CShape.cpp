#include "stdafx.h"
#include "CShape.h"

CShape::CShape()
	: m_fillStyle(std::make_shared<CFillStyle>(true, RGBAColor{ 0xFFFFFF }))
	, m_lineStyle(std::make_shared<CLineStyle>(true, RGBAColor{ 0xFFFF00 }, 2.f))
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

void CShape::Draw(ICanvas & canvas) const
{
	canvas.SetLineThickness(m_lineStyle->IsEnabled() ? m_lineStyle->GetLineThikness().get() : 0);
	canvas.SetLineColor(m_lineStyle->IsEnabled() ? m_lineStyle->GetColor().get() : RGBAColor{ 0x000000 });
	canvas.SetFillColor(m_fillStyle->IsEnabled() ? m_fillStyle->GetColor().get() : RGBAColor{ 0x000000 });

	DrawBehavior(canvas);
}