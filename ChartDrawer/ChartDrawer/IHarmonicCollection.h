#pragma once
#include "stdafx.h"
#include "IHarmonic.h"

typedef std::shared_ptr<IHarmonic> IHarmonicCollectionPointer;

class IHarmonicCollection
{
public:

	typedef sig::signal<void()> HarmonicChangeSignal;

	virtual ~IHarmonicCollection() = default;

	virtual double CalculateValue(double x) const = 0;

	virtual sig::connection DoOnSolutionChange(const HarmonicChangeSignal::slot_type& handler) = 0;

	virtual IHarmonicCollectionPointer GetHarmonic(size_t index) const = 0;
	virtual void AddHarmonic(double aplitude, double frequency, double phase, CHarmonicType type) = 0;
	virtual void DeleteHarmonic(size_t index) = 0;
	virtual size_t GetHarmonicsCount() const = 0;
};
