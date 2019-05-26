#include "stdafx.h"
#include "CMainDlgPresenter.h"
#include "IChartView.h"
#include "IHarmonicCollection.h"
#include "CHarmonicType.h"
#include "IMainDlgView.h"

CMainDlgPresenter::CMainDlgPresenter(IHarmonicCollection& solver, IMainDlgView& view)
	: m_collection(solver)
	, m_view(view)
{
	m_view.DoOnAmplitudeChange(std::bind(&CMainDlgPresenter::SetAmplitude, this, std::placeholders::_1, std::placeholders::_2));
	m_view.DoOnFrequencyChange(std::bind(&CMainDlgPresenter::SetFrequency, this, std::placeholders::_1, std::placeholders::_2));
	m_view.DoOnPhaseChange(std::bind(&CMainDlgPresenter::SetPhase, this, std::placeholders::_1, std::placeholders::_2));
	m_view.DoOnHarmonicTypeChange(std::bind(&CMainDlgPresenter::SetHarmonicType, this, std::placeholders::_1, std::placeholders::_2));
	m_view.DoOnAddHarmonic(std::bind(&CMainDlgPresenter::AddHarmonic, this));
	m_view.DoOnDeleteHarmonic(std::bind(&CMainDlgPresenter::DeleteHarmonic, this, std::placeholders::_1));
	m_view.DoOnInit(std::bind(&CMainDlgPresenter::InitView, this));
	m_collection.DoOnSolutionChange([this] {
		Update();
	});
}


void CMainDlgPresenter::SetAmplitude(int index, double value)
{
	m_collection.GetHarmonic(index)->SetAmplitude(value);
}

void CMainDlgPresenter::SetFrequency(int index, double value)
{
	m_collection.GetHarmonic(index)->SetFrequency(value);
}

void CMainDlgPresenter::SetPhase(int index, double value)
{
	m_collection.GetHarmonic(index)->SetPhase(value);
}

void CMainDlgPresenter::SetHarmonicType(int index, CHarmonicType value)
{
	m_collection.GetHarmonic(index)->SetHarmonicType(value);
}


void CMainDlgPresenter::InitView()
{
	Update();
	AddHarmonic();
}

void CMainDlgPresenter::Update()
{
	UpdateHarmonicsList();
	//UpdateTable(); TODO::update table
	UpdateChart(); 
}

void CMainDlgPresenter::AddHarmonic()
{
	m_collection.AddHarmonic(0, 0, 0, CHarmonicType::Sin);
	m_collection.GetHarmonic(m_collection.GetHarmonicsCount() - 1)
		->DoOnSolutionChange(std::bind(&CMainDlgPresenter::Update, this));
	m_view.InitDefaultHarmonic();
}


void CMainDlgPresenter::DeleteHarmonic(int index)
{
	m_collection.DeleteHarmonic(index);
}

void CMainDlgPresenter::UpdateHarmonicsList()
{
	ListBox harmonics;

	for (size_t i = 0; i < m_collection.GetHarmonicsCount(); ++i)
	{
		auto harmonic = m_collection.GetHarmonic(i);

		auto amplitude = harmonic->GetAmplitude();
		auto frequency = harmonic->GetFrequency();
		auto phase = harmonic->GetPhase();
		auto type = harmonic->GetHarmonicType();

		std::string typeStr = (type == CHarmonicType::Sin) ? "sin" : "cos";

		auto strm = (boost::wformat(L"%1% * %2%(%3%x + %4%)") % amplitude % typeStr.c_str() % frequency % phase).str();
		harmonics.push_back(strm.c_str());
	}

	m_view.AddHarmonicsToListBox(harmonics);
}

void CMainDlgPresenter::UpdateChart()
{
	IChartView::Points2D points;
	for (double x = -10.0; x <= +10; x += 0.1)
	{
		points.emplace_back(x, m_collection.CalculateValue(x));
	}
	m_view.GetChartView().SetData(points);
}
