#pragma once
#include "ISlide.h"
#include "CGroupShape.h"

class CSlide : public ISlide
{
public:
	CSlide(double width, double height);
	double GetWidth()const override;
	double GetHeight()const override;

	void AddShape(std::shared_ptr<IShape> const& shape) override;
	void Draw(ICanvas& canvas) const override;

private:
	double m_width;
	double m_height;
	std::vector<std::shared_ptr<IShape>> m_shapes;
};