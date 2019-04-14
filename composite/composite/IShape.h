#pragma once
#include "IDrawable.h"
#include "ILineStyle.h"
#include "IStyle.h"
#include <memory>

class IGroupShape;

class IShape : public IDrawable
{
public:
	virtual RectD GetFrame() = 0;
	virtual void SetFrame(const RectD & rect) = 0;

	virtual std::shared_ptr<ILineStyle> GetLineStyle() = 0;
	virtual std::shared_ptr<const ILineStyle> GetLineStyle()const = 0;

	virtual std::shared_ptr<IStyle> GetFillStyle() = 0;
	virtual std::shared_ptr<const IStyle> GetFillStyle()const = 0;

	virtual std::shared_ptr<IGroupShape> GetGroup() = 0;
	virtual std::shared_ptr<const IGroupShape> GetGroup() const = 0;

	virtual ~IShape() = default;
};