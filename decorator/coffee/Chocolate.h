#pragma once
#include "CondimentDecorator.h"

// Шоколадная крошка
class CChocolate : public CCondimentDecorator
{
public:
	CChocolate(IBeveragePtr&& beverage, unsigned slice)
		: CCondimentDecorator(move(beverage))
		, m_slice(slice)
	{
		m_slice = (m_slice > MAX_SLICES_COUNT) ? MAX_SLICES_COUNT : m_slice;
	}

	double GetCondimentCost() const override
	{
		return 10 * m_slice;
	}

	std::string GetCondimentDescription() const override
	{
		return "Chocolate " + std::to_string(m_slice) + " slices";
	}

private:
	unsigned m_slice;
	unsigned const MAX_SLICES_COUNT = 5;
};
