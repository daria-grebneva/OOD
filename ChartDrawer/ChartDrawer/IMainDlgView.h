#pragma once

#include "HarmonicType.h"
#include "Signals.h"

class IChartView;

class IMainDlgView
{
public:
	typedef sig::signal<void(int value1, double value2)> HarmonicCoeffChangeSignal;
	typedef sig::signal<void(int value1, HarmonicType value2)> HarmonicTypeChangeSignal;
	typedef sig::signal<void()> HarmonicAddSignal;
	typedef sig::signal<void()> HarmonicAddSolutionSignal;
	typedef sig::signal<void(int value1)> HarmonicDeleteSignal;
	typedef sig::signal<void(int value1)> HarmonicFocusListBoxChangeSignal;

	typedef sig::signal<void()> InitSignal;
	typedef std::vector<std::wstring> ListBox;

	virtual IChartView& GetChartView() = 0;
	virtual void AddHarmonicsToListBox(ListBox const& list) = 0;
	virtual void AddHarmonicsToTableBox(std::vector<std::pair<double, double>> const& table) = 0;
	virtual void InitDefaultHarmonic() = 0;
	virtual void UpdateFields(double amplitude, double frequency, double phase, HarmonicType type) = 0;
	virtual void UpdateAddingInfo() = 0;

	virtual void SetHarmonicParams(double a, double b, double c) = 0;

	// Signals
	virtual sig::connection DoOnInit(const InitSignal::slot_type& handler) = 0;
	virtual sig::connection DoOnAmplitudeChange(const HarmonicCoeffChangeSignal::slot_type& handler) = 0;
	virtual sig::connection DoOnFrequencyChange(const HarmonicCoeffChangeSignal::slot_type& handler) = 0;
	virtual sig::connection DoOnPhaseChange(const HarmonicCoeffChangeSignal::slot_type& handler) = 0;
	virtual sig::connection DoOnHarmonicTypeChange(const HarmonicTypeChangeSignal::slot_type& handler) = 0;
	virtual sig::connection DoOnAddHarmonic(const HarmonicAddSignal::slot_type& handler) = 0;
	virtual sig::connection DoOnDeleteHarmonic(const HarmonicDeleteSignal::slot_type& handler) = 0;
	virtual sig::connection DoOnSetFocusListBox(const HarmonicFocusListBoxChangeSignal::slot_type& handler) = 0;
	virtual sig::connection DoOnAddHarmonicSolution(const HarmonicAddSolutionSignal::slot_type& handler) = 0;

	virtual ~IMainDlgView() = default;
};
