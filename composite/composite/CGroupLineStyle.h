#pragma once
#include "ILineStyle.h"

typedef std::function<void(std::function<void(ILineStyle&)>)> LineGroup;

class CGroupLineStyle : public ILineStyle
{
public:
	CGroupLineStyle(LineGroup& group);
	boost::optional<bool> IsEnabled() const override;
	void Enable(bool enable) override;

	boost::optional<RGBAColor> GetColor() const override;
	void SetColor(RGBAColor color) override;

	boost::optional<float> GetLineThiñkness() const override;
	void SetLineThiñkness(float thikness) override;

private:
	LineGroup& m_group;
};
