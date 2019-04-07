#pragma once
#include "ILineStyle.h"

typedef std::function<void(std::function<void(ILineStyle&)>)> LineEnumerator;

class CGroupLineStyle : public ILineStyle
{
public:
	CGroupLineStyle(LineEnumerator & enumerator);
	boost::optional<bool> IsEnabled()const override;
	void Enable(bool enable) override;

	boost::optional<RGBAColor> GetColor()const override;
	void SetColor(RGBAColor color) override;

	boost::optional<float> GetLineThikness() const override;
	void SetLineThikness(float thikness) override;
private:
	LineEnumerator & m_enumerator;
};
