#pragma once
#include "IGroupShape.h"
#include "ILineStyle.h"
#include "CGroupFillStyle.h"
#include "CGroupLineStyle.h"

class CGroupShape : public IGroupShape
{
public:
	CGroupShape();

	RectD GetFrame() override;
	void SetFrame(const RectD & rect) override;

	std::shared_ptr<ILineStyle> GetLineStyle() override;
	std::shared_ptr<const ILineStyle> GetLineStyle() const override;

	std::shared_ptr<IStyle> GetFillStyle() override;
	std::shared_ptr<const IStyle> GetFillStyle()const override;

	std::shared_ptr<IGroupShape> GetGroup() override;
	std::shared_ptr<const IGroupShape> GetGroup() const override;

	size_t GetShapesCount()const override;
	void InsertShape(const std::shared_ptr<IShape> & shape, size_t position = std::numeric_limits<size_t>::max()) override;
	std::shared_ptr<IShape> GetShapeAtIndex(size_t index) override;
	void RemoveShapeAtIndex(size_t index) override;
	void Draw(ICanvas & canvas) const override;

private:
	std::vector<std::shared_ptr<IShape>> m_shapes;

	std::shared_ptr<IStyle> m_groupFillStyle;
	std::shared_ptr<ILineStyle> m_groupLineStyle;
};