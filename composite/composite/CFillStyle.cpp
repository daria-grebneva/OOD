#include "stdafx.h"
#include "CFillStyle.h"


CFillStyle::CFillStyle(bool enable, RGBAColor color)
	: m_enable(enable)
	, m_color(color)
{
}

boost::optional<bool> CFillStyle::IsEnabled()const
{
	return m_enable;
}

void CFillStyle::Enable(bool enable)
{
	m_enable = enable;
}

boost::optional<RGBAColor> CFillStyle::GetColor()const
{
	return m_color;
}

void CFillStyle::SetColor(RGBAColor color)
{
	m_color = color;
}