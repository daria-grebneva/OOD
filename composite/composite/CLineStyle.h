#pragma once
#include "CommonTypes.h"
#include "ILineStyle.h"

class CLineStyle : public ILineStyle
{
public:
	CLineStyle(bool enabled, RGBAColor color, float thickness);

	boost::optional<bool> IsEnabled() const override;
	void Enable(bool enable) override;

	boost::optional<RGBAColor> GetColor() const override;
	void SetColor(RGBAColor color) override;

	boost::optional<float> GetLineThiñkness() const;
	void SetLineThiñkness(float thikness);

private:
	bool m_enable;
	RGBAColor m_color;
	float m_thickness;
};
