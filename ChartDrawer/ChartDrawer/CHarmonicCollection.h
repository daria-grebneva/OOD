#pragma once
#include "stdafx.h"
#include "IHarmonicCollection.h"

class CHarmonicCollection : public IHarmonicCollection
{
public:
	CHarmonicCollection(){};
	~CHarmonicCollection(){};

	double CalculateValue(double x) const override final;
	sig::connection DoOnSolutionChange(const HarmonicChangeSignal::slot_type& handler) override final;

	IHarmonicCollectionPointer GetHarmonic(size_t index) const override final;
	void AddHarmonic(double amplitude, double frequency, double phase, CHarmonicType type) override final;
	void DeleteHarmonic(size_t index) override final;

	size_t GetHarmonicsCount() const override final;

private:
	std::vector<IHarmonicCollectionPointer> m_collection;
	HarmonicChangeSignal m_harmonicsUpdateSignal;
};
