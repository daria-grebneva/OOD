#include "stdafx.h"
#include "CGroupLineStyle.h"


CGroupLineStyle::CGroupLineStyle(LineEnumerator & enumerator)
	: m_enumerator(enumerator)
{
}

boost::optional<bool> CGroupLineStyle::IsEnabled()const
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

	m_enumerator(callback);

	return isEnabled;
}

void CGroupLineStyle::Enable(bool enable)
{
	m_enumerator([&](ILineStyle& style) {
		style.Enable(enable);
	});
}

boost::optional<RGBAColor> CGroupLineStyle::GetColor()const
{
	boost::optional<RGBAColor> color = RGBAColor{ 0x000000 };

	auto callback = [&](ILineStyle& style) {
		if (!color.is_initialized())
		{
			color = style.GetColor();
		}
	};

	m_enumerator(callback);

	return color;
}

void CGroupLineStyle::SetColor(RGBAColor color)
{
	m_enumerator([&](ILineStyle& style) {
		style.SetColor(color);
	});
}

boost::optional<float> CGroupLineStyle::GetLineThikness() const
{
	boost::optional<float> outlineThikness;

	auto callback = [&](ILineStyle& style) {
		if (!outlineThikness.is_initialized())
		{
			outlineThikness = style.IsEnabled();
		}
		else if (outlineThikness != style.GetLineThikness())
		{
			outlineThikness = boost::none;
		}
	};

	m_enumerator(callback);

	return outlineThikness;
}

void CGroupLineStyle::SetLineThikness(float thikness)
{
	m_enumerator([&](ILineStyle& style) {
		style.SetLineThikness(thikness);
	});
}