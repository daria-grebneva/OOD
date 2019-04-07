#pragma once
#include "CommonTypes.h"
#include "IShape.h"
#include "CFillStyle.h"
#include "CLineStyle.h"

class CShape : public IShape
{
public:
	RectD GetFrame();
	void SetFrame(const RectD & rect);

	std::shared_ptr<ILineStyle> GetLineStyle() override;
	std::shared_ptr<const ILineStyle> GetLineStyle() const override;

	std::shared_ptr<IStyle> GetFillStyle() override;
	std::shared_ptr<const IStyle> GetFillStyle()const override;

	std::shared_ptr<IGroupShape> GetGroup() override;
	std::shared_ptr<const IGroupShape> GetGroup() const override;

	void Draw(const ICanvas & canvas) const override;

	~CShape() override = default;

	//TODO:: public?
protected:
	virtual void DrawBehavior(ICanvas & canvas)const = 0;

private:
	std::shared_ptr<IStyle> m_fillStyle;
	std::shared_ptr<ILineStyle> m_lineStyle;
};