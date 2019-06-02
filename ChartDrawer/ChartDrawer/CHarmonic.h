#pragma once
#include "IHarmonic.h"

class CHarmonic : public IHarmonic
{
public:
	CHarmonic(double amplitude, double frequency, double phase, HarmonicType type);
	~CHarmonic() {};

	double CalculateValue(double x) const override final;

	sig::connection DoOnHarmonicChange(const HarmonicChangeSignal::slot_type& handler) override final;
	
	double GetAmplitude() const override final;
	void SetAmplitude(double amplitude) override final;

	double GetFrequency() const override final;
	void SetFrequency(double frequency) override final;

	double GetPhase() const override final;
	void SetPhase(double phase) override final;

	HarmonicType GetHarmonicType() const override final;
	void SetHarmonicType(HarmonicType type) override final;

private:
	double m_amplitude;
	double m_frequency;
	double m_phase;
	HarmonicType m_harmonicType;

	HarmonicChangeSignal m_harmonicChanged;
};
