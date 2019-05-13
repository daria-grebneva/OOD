#include "stdafx.h"
#include "CGroupLineStyle.h"
#include "CShape.h"

CGroupLineStyle::CGroupLineStyle(std::shared_ptr<const IShapes> shapes)
	: m_shapes(move(shapes))
{
}

boost::optional<bool> CGroupLineStyle::IsEnabled() const
{
	boost::optional<bool> isEnabled = boost::none;

	if (m_shapes->GetShapesCount() != 0)
	{
		auto style = m_shapes->GetShapeAtIndex(0)->GetLineStyle();

		isEnabled = style->IsEnabled();

		if (m_shapes->GetShapesCount() > 1)
		{
			for (int i = 1; i < m_shapes->GetShapesCount(); i++)
			{
				auto style = m_shapes->GetShapeAtIndex(i)->GetLineStyle();
				if (style->IsEnabled() != isEnabled)
				{
					isEnabled = boost::none;
					break;
				}
			}
		}
	}

	return isEnabled;
}

void CGroupLineStyle::Enable(bool enable)
{
	if (m_shapes->GetShapesCount() != 0)
	{
		for (size_t i = 0; i < m_shapes->GetShapesCount(); i++)
		{
			auto shape = m_shapes->GetShapeAtIndex(i);
			auto style = shape->GetLineStyle();
			style->Enable(true);
		}
	}
}

boost::optional<RGBAColor> CGroupLineStyle::GetColor() const
{
	boost::optional<RGBAColor> color = boost::none;

	if (m_shapes->GetShapesCount() != 0)
	{
		auto style = m_shapes->GetShapeAtIndex(0)->GetLineStyle();

		color = style->GetColor();

		if (m_shapes->GetShapesCount() > 1)
		{
			for (int i = 1; i < m_shapes->GetShapesCount(); i++)
			{
				auto style = m_shapes->GetShapeAtIndex(i)->GetLineStyle();
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

void CGroupLineStyle::SetColor(RGBAColor color)
{
	if (m_shapes->GetShapesCount() != 0)
	{
		for (size_t i = 0; i < m_shapes->GetShapesCount(); i++)
		{
			auto shape = m_shapes->GetShapeAtIndex(i);
			auto style = shape->GetLineStyle();
			style->SetColor(color);
		}
	}
}

boost::optional<float> CGroupLineStyle::GetLineThickness() const
{
	boost::optional<float> outlineThikness = boost::none;

	if (m_shapes->GetShapesCount() != 0)
	{
		auto style = m_shapes->GetShapeAtIndex(0)->GetLineStyle();

		outlineThikness = style->GetLineThickness();

		if (m_shapes->GetShapesCount() > 1)
		{
			for (int i = 1; i < m_shapes->GetShapesCount(); i++)
			{
				auto style = m_shapes->GetShapeAtIndex(i)->GetLineStyle();
				if (style->GetLineThickness() != outlineThikness || !style->IsEnabled())
				{
					outlineThikness = boost::none;
					break;
				}
			}
		}
	}

	return outlineThikness;
}

void CGroupLineStyle::SetLineThickness(float thikness)
{
	if (m_shapes->GetShapesCount() != 0)
	{
		for (size_t i = 0; i < m_shapes->GetShapesCount(); i++)
		{
			auto shape = m_shapes->GetShapeAtIndex(i);
			auto style = shape->GetLineStyle();
			style->SetLineThickness(thikness);
		}
	}
}
