#pragma once
#include "stdafx.h"
#include "HarmonicType.h"
#include "Signals.h"

class IHarmonic
{
public:
	virtual ~IHarmonic() = default;

	virtual double CalculateValue(double x) const = 0;

	typedef sig::signal<void()> HarmonicChangeSignal;

	virtual sig::connection DoOnHarmonicChange(const HarmonicChangeSignal::slot_type& handler) = 0;

	virtual double GetAmplitude() const = 0;
	virtual void SetAmplitude(double amplitude) = 0;

	virtual double GetFrequency() const = 0;
	virtual void SetFrequency(double frequency) = 0;

	virtual double GetPhase() const = 0;
	virtual void SetPhase(double phase) = 0;

	virtual HarmonicType GetHarmonicType() const = 0;
	virtual void SetHarmonicType(HarmonicType type) = 0;	
};
