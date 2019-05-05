#pragma once
#include "ILineStyle.h"
#include "IShapes.h"

class CGroupLineStyle : public ILineStyle
{
public:
	CGroupLineStyle(std::shared_ptr<const IShapes> m_shapes);
	boost::optional<bool> IsEnabled() const override;
	void Enable(bool enable) override;

	boost::optional<RGBAColor> GetColor() const override;
	void SetColor(RGBAColor color) override;

	boost::optional<float> GetLineThi�kness() const override;
	void SetLineThi�kness(float thikness) override;

private:
	std::shared_ptr<const IShapes> m_shapes;
};
