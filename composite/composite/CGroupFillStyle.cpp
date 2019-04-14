#include "stdafx.h"
#include "CGroupFillStyle.h"
#include "CShape.h"


CGroupFillStyle::CGroupFillStyle(FillEnumerator & enumerator)
	: m_enumerator(enumerator)
{
}

boost::optional<bool> CGroupFillStyle::IsEnabled()const
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

	m_enumerator(callback);

	return isEnabled;
}

void CGroupFillStyle::Enable(bool enable)
{
	m_enumerator([&](IStyle& style) { style.Enable(enable); });
}

boost::optional<RGBAColor> CGroupFillStyle::GetColor()const
{
	boost::optional<RGBAColor> color = CShape::ColorToHex( "0xFFFFFF" );

	auto callback = [&](IStyle& style) {
		if (!color.is_initialized())
		{
			color = style.GetColor();
		}
	};

	m_enumerator(callback);

	return color;
}

void CGroupFillStyle::SetColor(RGBAColor color)
{
	m_enumerator([&](IStyle& style) { style.SetColor(color); });
}