#pragma once
#include "CFillStyle.h"
#include "CLineStyle.h"
#include "CommonTypes.h"
#include "IShape.h"

class CShape : public IShape
{
public:
	CShape();

	std::shared_ptr<ILineStyle> GetLineStyle() override;
	std::shared_ptr<const ILineStyle> GetLineStyle() const override;

	std::shared_ptr<IStyle> GetFillStyle() override;
	std::shared_ptr<const IStyle> GetFillStyle() const override;

	std::shared_ptr<IGroupShape> GetGroup() override;
	std::shared_ptr<const IGroupShape> GetGroup() const override;

	void Draw(ICanvas& canvas) const override;

	virtual void DrawFigure(ICanvas& canvas) const = 0;
	static RGBAColor ColorToHex(const std::string color);
	~CShape() override = default;

private:
	std::shared_ptr<IStyle> m_fillStyle;
	std::shared_ptr<ILineStyle> m_lineStyle;
	RGBAColor GetLineColor() const;
	RGBAColor GetFillColor() const;
	float GetLineThiñkness() const;
};
