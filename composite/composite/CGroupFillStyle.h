#pragma once
#include "IShapes.h"
#include "IStyle.h"

class CGroupFillStyle : public IStyle
{
public:
	CGroupFillStyle(std::shared_ptr<const IShapes> m_shapes);
	boost::optional<bool> IsEnabled() const override;
	void Enable(bool enable) override;

	boost::optional<RGBAColor> GetColor() const override;
	void SetColor(RGBAColor color) override;

private:
	std::shared_ptr<const IShapes> m_shapes;
};
