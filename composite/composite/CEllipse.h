#pragma once
#include "CShape.h"

class CEllipse : public CShape
{
public:
	void Draw(const ICanvas & canvas) final;
};