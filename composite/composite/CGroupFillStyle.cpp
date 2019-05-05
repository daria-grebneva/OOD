#include "stdafx.h"
#include "CGroupFillStyle.h"
#include "CShape.h"

CGroupFillStyle::CGroupFillStyle(std::shared_ptr<const IShapes> shapes)
	: m_shapes(move(shapes))
{
}

boost::optional<bool> CGroupFillStyle::IsEnabled() const
{
	boost::optional<bool> isEnabled;

	auto style = m_shapes->GetShapeAtIndex(0)->GetFillStyle();

	isEnabled = style->IsEnabled();
	if (m_shapes->GetShapesCount() > 1)
	{
		for (int i = 1; i < m_shapes->GetShapesCount(); i++)
		{
			auto style = m_shapes->GetShapeAtIndex(0)->GetFillStyle();
			if (style->IsEnabled() != isEnabled)
			{
				isEnabled = boost::none;
				break;
			}
		}
	}

	return isEnabled;
}

void CGroupFillStyle::Enable(bool enable)
{
	if (m_shapes->GetShapesCount() != 0)
	{
		for (int i = 0; i < m_shapes->GetShapesCount(); i++)
		{
			auto style = m_shapes->GetShapeAtIndex(0)->GetFillStyle();
			style->Enable(true);
		}
	}
}

boost::optional<RGBAColor> CGroupFillStyle::GetColor() const
{
	boost::optional<RGBAColor> color = CShape::ColorToHex("000000ff");
	auto style = m_shapes->GetShapeAtIndex(0)->GetFillStyle();

	if (style->IsEnabled())
	{
		color = style->GetColor();
		if (m_shapes->GetShapesCount() > 1)
		{
			for (int i = 1; i < m_shapes->GetShapesCount(); i++)
			{
				auto style = m_shapes->GetShapeAtIndex(0)->GetFillStyle();

				if (style->GetColor() != color || !style->IsEnabled())
				{
					color = boost::none;
					break;
				}
			}
		}
	}

	return color;
}

void CGroupFillStyle::SetColor(RGBAColor color)
{
	if (m_shapes->GetShapesCount() != 0)
	{
		for (int i = 0; i < m_shapes->GetShapesCount(); i++)
		{
			auto shape = m_shapes->GetShapeAtIndex(i);
			auto style = shape->GetFillStyle();
			style->SetColor(color);
		}
	}
}
