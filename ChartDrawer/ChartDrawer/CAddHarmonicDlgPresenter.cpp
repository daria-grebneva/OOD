#include "stdafx.h"
#include "CAddHarmonicDlgPresenter.h"
#include "CMainDlgPresenter.h"
#include "HarmonicType.h"
//#include "IChartView.h"
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
	/*m_view.DoOnDeleteHarmonic(std::bind(&CAddHarmonicDlgPresenter::DeleteHarmonic, this, std::placeholders::_1));
	m_view.DoOnSetFocusListBox(std::bind(&CAddHarmonicDlgPresenter::SetFocusListBox, this, std::placeholders::_1));*/
	m_view.DoOnInit(std::bind(&CAddHarmonicDlgPresenter::InitView, this));
	//m_view = new CAddHarmonicView();
	m_collection.DoOnHarmonicChange([this] {
		Update();
	});
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
	//Update();
	//m_collection.AddHarmonic(1, 1, 0, HarmonicType::Sin);
	/*m_collection.GetHarmonic(m_collection.GetHarmonicsCount() - 1)
		->DoOnHarmonicChange(std::bind(&CMainDlgPresenter::Update, this));*/
	m_view.InitDefaultHarmonic();
	m_view.UpdateFields(1, 1, 0, HarmonicType::Sin);
}
//
void CAddHarmonicDlgPresenter::Update()
{
	//UpdateHarmonicsList();
	////UpdateTable(); TODO::update table
	//UpdateChart();
}

void CAddHarmonicDlgPresenter::AddHarmonic()
{
	m_collection.AddHarmonic(m_harmonic.amplitude, m_harmonic.frequency, m_harmonic.phase, m_harmonic.type);
	m_mainView.UpdateAddingInfo();
	//m_presenter.NotifyOnAdding();
	//m_collection.AddHarmonic(3, 4, m_harmonic.phase, m_harmonic.type);
	/*m_collection.GetHarmonic(m_collection.GetHarmonicsCount() - 1)
		->DoOnHarmonicChange(std::bind(&CAddHarmonicDlgPresenter::Update, this));*/
	/*m_view.InitDefaultHarmonic();
	m_view.UpdateFields(1, 1, 0, HarmonicType::Sin);*/
}
//
//void CAddHarmonicDlgPresenter::DeleteHarmonic(int index)
//{
//	m_collection.DeleteHarmonic(index);
//}
//
//void CAddHarmonicDlgPresenter::SetFocusListBox(int index)
//{
//	auto harmonic = m_collection.GetHarmonic(index);
//	m_view.UpdateFields(harmonic->GetAmplitude(), harmonic->GetFrequency(), harmonic->GetPhase(), harmonic->GetHarmonicType()); //TODO:: реализовать метод, обновл€ющий пол€
//}
//
//void CAddHarmonicDlgPresenter::UpdateHarmonicsList()
//{
//	ListBox harmonics;
//
//	for (size_t i = 0; i < m_collection.GetHarmonicsCount(); ++i)
//	{
//		auto harmonic = m_collection.GetHarmonic(i);
//
//		auto amplitude = harmonic->GetAmplitude();
//		auto frequency = harmonic->GetFrequency();
//		auto phase = harmonic->GetPhase();
//		auto type = harmonic->GetHarmonicType();
//
//		std::string typeStr = (type == HarmonicType::Sin) ? "sin" : "cos";
//
//		auto strm = (boost::wformat(L"%1% * %2%(%3%x + %4%)") % amplitude % typeStr.c_str() % frequency % phase).str();
//		harmonics.push_back(strm.c_str());
//	}
//
//	m_view.AddHarmonicsToListBox(harmonics);
//}
//
//void CAddHarmonicDlgPresenter::UpdateChart()
//{
//	IChartView::Points2D points;
//	for (double x = -10.0; x <= +10; x += 0.1)
//	{
//		points.emplace_back(x, m_collection.CalculateValue(x));
//	}
//	m_view.GetChartView().SetData(points);
//}
