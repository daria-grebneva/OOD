#include "stdafx.h"
#include "CAddHarmonicDlgPresenter.h"
#include "CMainDlgPresenter.h"
#include "HarmonicType.h"
#include "IAddHarmonicView.h"
#include "IHarmonicCollection.h"
#include "IMainDlgView.h"

CAddHarmonicDlgPresenter::CAddHarmonicDlgPresenter(IHarmonicCollection& harmonicCollection, IAddHarmonicView& view, IMainDlgView& mainView)
	: m_collection(harmonicCollection)
	, m_view(view)
	, m_mainView(mainView)
{
	m_view.DoOnAmplitudeChange(std::bind(&CAddHarmonicDlgPresenter::SetAmplitude, this, std::placeholders::_1));
	m_view.DoOnFrequencyChange(std::bind(&CAddHarmonicDlgPresenter::SetFrequency, this, std::placeholders::_1));
	m_view.DoOnPhaseChange(std::bind(&CAddHarmonicDlgPresenter::SetPhase, this, std::placeholders::_1));
	m_view.DoOnHarmonicTypeChange(std::bind(&CAddHarmonicDlgPresenter::SetHarmonicType, this, std::placeholders::_1));
	m_view.DoOnAddHarmonic(std::bind(&CAddHarmonicDlgPresenter::AddHarmonic, this));
	m_view.DoOnInit(std::bind(&CAddHarmonicDlgPresenter::InitView, this));
}

void CAddHarmonicDlgPresenter::SetAmplitude(double value)
{
	m_harmonic.amplitude = value;
}

void CAddHarmonicDlgPresenter::SetFrequency(double value)
{
	m_harmonic.frequency = value;
}

void CAddHarmonicDlgPresenter::SetPhase(double value)
{
	m_harmonic.phase = value;
}

void CAddHarmonicDlgPresenter::SetHarmonicType(HarmonicType value)
{
	m_harmonic.type = value;
}

void CAddHarmonicDlgPresenter::InitView()
{
	m_view.InitDefaultHarmonic();
	m_view.UpdateFields(1, 1, 0, HarmonicType::Sin);
}

void CAddHarmonicDlgPresenter::AddHarmonic()
{
	m_collection.AddHarmonic(m_harmonic.amplitude, m_harmonic.frequency, m_harmonic.phase, m_harmonic.type);
	m_mainView.UpdateAddingInfo();
}
