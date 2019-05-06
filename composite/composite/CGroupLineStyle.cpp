#include "stdafx.h"
#include "CGroupLineStyle.h"
#include "CShape.h"

CGroupLineStyle::CGroupLineStyle(std::shared_ptr<const IShapes> shapes)
	: m_shapes(move(shapes))
{
}

boost::optional<bool> CGroupLineStyle::IsEnabled() const
{
	boost::optional<bool> isEnabled;

	auto style = m_shapes->GetShapeAtIndex(0)->GetLineStyle();

	return style->IsEnabled();
}

void CGroupLineStyle::Enable(bool enable)
{
	if (m_shapes->GetShapesCount() != 0)
	{
		for (int i = 0; i < m_shapes->GetShapesCount(); i++)
		{
			auto style = m_shapes->GetShapeAtIndex(0)->GetLineStyle();
			style->Enable(true);
		}
	}
}

boost::optional<RGBAColor> CGroupLineStyle::GetColor() const
{
	boost::optional<RGBAColor> color = CShape::ColorToHex("000000ff");

	auto style = m_shapes->GetShapeAtIndex(0)->GetLineStyle();

	if (style->IsEnabled())
	{
		color = style->GetColor();
	}

	return color;
}

void CGroupLineStyle::SetColor(RGBAColor color)
{
	if (m_shapes->GetShapesCount() != 0)
	{
		for (int i = 0; i < m_shapes->GetShapesCount(); i++)
		{
			auto shape = m_shapes->GetShapeAtIndex(i);
			auto style = shape->GetLineStyle();
			style->SetColor(color);
		}
	}
}

boost::optional<float> CGroupLineStyle::GetLineThickness() const
{
	boost::optional<float> outlineThikness;

	auto style = m_shapes->GetShapeAtIndex(0)->GetLineStyle();

	if (style->IsEnabled())
	{
		outlineThikness = style->GetLineThickness();
	}

	return outlineThikness;
}

void CGroupLineStyle::SetLineThickness(float thikness)
{
	if (m_shapes->GetShapesCount() != 0)
	{
		for (int i = 0; i < m_shapes->GetShapesCount(); i++)
		{
			auto shape = m_shapes->GetShapeAtIndex(i);
			auto style = shape->GetLineStyle();
			style->SetLineThickness(thikness);
		}
	}
}
