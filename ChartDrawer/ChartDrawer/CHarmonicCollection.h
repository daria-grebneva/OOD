#pragma once
#include "stdafx.h"
#include "IHarmonicCollection.h"

class CHarmonicCollection : public IHarmonicCollection
{
public:
	CHarmonicCollection(){};
	~CHarmonicCollection(){};

	double CalculateValue(double x) const override final;
	sig::connection DoOnHarmonicChange(const HarmonicChangeSignal::slot_type& handler) override final;

	IHarmonicPointer GetHarmonic(size_t index) const override final;
	void AddHarmonic(double amplitude, double frequency, double phase, HarmonicType type) override final;
	void DeleteHarmonic(size_t index) override final;

	size_t GetHarmonicsCount() const override final;

private:
	std::vector<IHarmonicPointer> m_collection;
	HarmonicChangeSignal m_harmonicsUpdateSignal;
};
