#pragma once
#include "IStyle.h"

typedef std::function<void(std::function<void(IStyle&)>)> FillGroup;

class CGroupFillStyle : public IStyle
{
public:
	CGroupFillStyle(FillGroup& group);
	boost::optional<bool> IsEnabled() const override;
	void Enable(bool enable) override;

	boost::optional<RGBAColor> GetColor() const override;
	void SetColor(RGBAColor color) override;

private:
	FillGroup& m_group;
};
