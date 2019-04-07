#pragma once
#include "IStyle.h"

typedef std::function<void(std::function<void(IStyle&)>)> FillEnumerator;

class CGroupFillStyle : public IStyle
{
public:
	CGroupFillStyle(FillEnumerator & enumerator);
	boost::optional<bool> IsEnabled()const override;
	void Enable(bool enable) override;

	boost::optional<RGBAColor> GetColor()const override;
	void SetColor(RGBAColor color) override;
private:
	FillEnumerator & m_enumerator;
};