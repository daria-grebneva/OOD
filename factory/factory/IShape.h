#pragma once
#include "Color.h"
#include "ICanvasDrawable.h"

class IShape : public ICanvasDrawable
{
public:
	IShape() = default;
	virtual ~IShape() = default;
	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString() const = 0;
	virtual Color GetOutlineColor() const = 0;
	virtual void Draw(ICanvas& canvas) const = 0;
};
