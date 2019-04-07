#pragma once
#include "IDrawable.h"
#include "IGroupShape.h"
#include "IStyle.h"
#include <memory>

class IShape : public IDrawable
{
public:
	virtual RectD GetFrame() = 0;
	virtual void SetFrame(const RectD & rect) = 0;

	virtual std::shared_ptr<IStyle> & GetLineStyle() = 0;
	virtual std::shared_ptr<const IStyle> & GetLineStyle()const = 0;

	virtual std::shared_ptr<IStyle> & GetFillStyle() = 0;
	virtual std::shared_ptr<const IStyle> & GetFillStyle()const = 0;

	virtual std::shared_ptr<IGroupShape> GetGroup() = 0;
	virtual std::shared_ptr<const IGroupShape> GetGroup() const = 0;

	virtual ~IShape() = default;
};