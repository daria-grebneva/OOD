#pragma once

#include "Signals.h"

class IChartView;

class IMainDlgView
{
public:
	typedef sig::signal<void(double value)> HarmonicChangeSignal;

	typedef sig::signal<void()> InitSignal;

	virtual IChartView& GetChartView() = 0;

	virtual void SetNoSolution() = 0;
	virtual void SetInfiniteSolutions() = 0;
	virtual void SetSingleSolution(double solution) = 0;
	virtual void SetTwoRootsSolutuion(double root1, double root2) = 0;

	virtual void SetHarmonicParams(double a, double b, double c) = 0;

	// Signals
	virtual sig::connection DoOnInit(const InitSignal::slot_type& handler) = 0;
	virtual sig::connection DoOnAmplitudeChange(const HarmonicChangeSignal::slot_type& handler) = 0;
	virtual sig::connection DoOnFrequencyChange(const HarmonicChangeSignal::slot_type& handler) = 0;
	virtual sig::connection DoOnPhaseChange(const HarmonicChangeSignal::slot_type& handler) = 0;

	virtual ~IMainDlgView() = default;
};
