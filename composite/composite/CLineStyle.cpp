#include "stdafx.h"
#include "CLineStyle.h"

CLineStyle::CLineStyle(bool enabled, RGBAColor color, float thickness)
	: m_enable(enabled)
	, m_color(color)
	, m_thickness(thickness)
{
}

boost::optional<bool> CLineStyle::IsEnabled()const
{
	return m_enable;
}

void CLineStyle::Enable(bool enable)
{
	m_enable = enable;
}

boost::optional<RGBAColor> CLineStyle::GetColor()const
{
	return m_color;
}

void CLineStyle::SetColor(RGBAColor color)
{
	m_color = color;
}

boost::optional<float> CLineStyle::GetLineThikness() const
{
	return m_thickness;
}

void CLineStyle::SetLineThikness(float thikness)
{
	m_thickness = thikness;
}