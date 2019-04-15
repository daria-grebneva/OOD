#include "stdafx.h"
#include "CGroupFillStyle.h"
#include "CShape.h"

CGroupFillStyle::CGroupFillStyle(FillGroup& group)
	: m_group(group)
{
}

boost::optional<bool> CGroupFillStyle::IsEnabled() const
{
	boost::optional<bool> isEnabled;

	auto callback = [&](IStyle& style) {
		if (!isEnabled.is_initialized())
		{
			isEnabled = style.IsEnabled();
		}
		else if (isEnabled != style.IsEnabled())
		{
			isEnabled = boost::none;
		}
	};

	m_group(callback);

	return isEnabled;
}

void CGroupFillStyle::Enable(bool enable)
{
	m_group([&](IStyle& style) { style.Enable(enable); });
}

boost::optional<RGBAColor> CGroupFillStyle::GetColor() const
{
	boost::optional<RGBAColor> color = CShape::ColorToHex("000000ff");

	auto callback = [&](IStyle& style) {
		if (!color.is_initialized())
		{
			color = style.GetColor();
		}
	};

	m_group(callback);

	return color;
}

void CGroupFillStyle::SetColor(RGBAColor color)
{
	m_group([&](IStyle& style) { style.SetColor(color); });
}
