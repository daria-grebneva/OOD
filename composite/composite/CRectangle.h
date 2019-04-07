#pragma once
#include "CShape.h"

class CRectangle : public CShape
{
public:
	void Draw(const ICanvas & canvas) final;
};
