#include "stdafx.h"
#include "CGroupLineStyle.h"
#include "CShape.h"

CGroupLineStyle::CGroupLineStyle(LineGroup& group)
	: m_group(group)
{
}

boost::optional<bool> CGroupLineStyle::IsEnabled() const
{
	boost::optional<bool> isEnabled;

	auto callback = [&](ILineStyle& style) {
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

void CGroupLineStyle::Enable(bool enable)
{
	m_group([&](ILineStyle& style) {
		style.Enable(enable);
	});
}

boost::optional<RGBAColor> CGroupLineStyle::GetColor() const
{
	boost::optional<RGBAColor> color = CShape::ColorToHex("000000ff");

	auto callback = [&](ILineStyle& style) {
		if (!color.is_initialized())
		{
			color = style.GetColor();
		}
	};

	m_group(callback);

	return color;
}

void CGroupLineStyle::SetColor(RGBAColor color)
{
	m_group([&](ILineStyle& style) {
		if (style.IsEnabled())
		{
			style.SetColor(CShape::ColorToHex("ffff00ff"));
		}
	});
}

boost::optional<float> CGroupLineStyle::GetLineThiñkness() const
{
	boost::optional<float> outlineThikness;

	auto callback = [&](ILineStyle& style) {
		if (!outlineThikness.is_initialized())
		{
			outlineThikness = style.IsEnabled();
		}
		else if (outlineThikness != style.GetLineThiñkness())
		{
			outlineThikness = boost::none;
		}
	};

	m_group(callback);

	return outlineThikness;
}

void CGroupLineStyle::SetLineThiñkness(float thikness)
{
	m_group([&](ILineStyle& style) {
		style.SetLineThiñkness(thikness);
	});
}
