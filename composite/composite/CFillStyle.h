#pragma once
#include "CommonTypes.h"
#include "IStyle.h"

class CFillStyle : public IStyle
{
public:

	CFillStyle(bool enable, RGBAColor color);

	boost::optional<bool> IsEnabled()const override;
	void Enable(bool enable) override;

	boost::optional<RGBAColor> GetColor()const override;
	void SetColor(RGBAColor color) override;

private:
	bool m_enable;
	RGBAColor m_color;
};
