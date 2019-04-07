#pragma once
#include "CShape.h"

class CTriangle : public CShape
{
public:
	void Draw(const ICanvas & canvas) final;
};
