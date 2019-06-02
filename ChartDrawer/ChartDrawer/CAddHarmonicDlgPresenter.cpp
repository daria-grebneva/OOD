#include "stdafx.h"
#include "CAddHarmonicDlgPresenter.h"
#include "HarmonicType.h"
//#include "IChartView.h"
//#include "IHarmonicCollection.h"
#include "IAddHarmonicView.h"

CAddHarmonicDlgPresenter::CAddHarmonicDlgPresenter()
{
	/*m_view.DoOnAmplitudeChange(std::bind(&CAddHarmonicDlgPresenter::SetAmplitude, this, std::placeholders::_1, std::placeholders::_2));
	m_view.DoOnFrequencyChange(std::bind(&CAddHarmonicDlgPresenter::SetFrequency, this, std::placeholders::_1, std::placeholders::_2));
	m_view.DoOnPhaseChange(std::bind(&CAddHarmonicDlgPresenter::SetPhase, this, std::placeholders::_1, std::placeholders::_2));
	m_view.DoOnHarmonicTypeChange(std::bind(&CAddHarmonicDlgPresenter::SetHarmonicType, this, std::placeholders::_1, std::placeholders::_2));
	m_view.DoOnAddHarmonic(std::bind(&CAddHarmonicDlgPresenter::AddHarmonic, this));
	m_view.DoOnDeleteHarmonic(std::bind(&CAddHarmonicDlgPresenter::DeleteHarmonic, this, std::placeholders::_1));
	m_view.DoOnSetFocusListBox(std::bind(&CAddHarmonicDlgPresenter::SetFocusListBox, this, std::placeholders::_1));*/
	//m_view.DoOnInit(std::bind(&CAddHarmonicDlgPresenter::InitView, this));
	//m_view = new CAddHarmonicView();
	/*m_collection.DoOnHarmonicChange([this] {
	Update();
	});*/
}

//void CAddHarmonicDlgPresenter::SetAmplitude(int index, double value)
//{
//	m_collection.GetHarmonic(index)->SetAmplitude(value);
//}
//
//void CAddHarmonicDlgPresenter::SetFrequency(int index, double value)
//{
//	m_collection.GetHarmonic(index)->SetFrequency(value);
//}
//
//void CAddHarmonicDlgPresenter::SetPhase(int index, double value)
//{
//	m_collection.GetHarmonic(index)->SetPhase(value);
//}
//
//void CAddHarmonicDlgPresenter::SetHarmonicType(int index, HarmonicType value)
//{
//	m_collection.GetHarmonic(index)->SetHarmonicType(value);
//}
//
//void CAddHarmonicDlgPresenter::InitView()
//{
//	m_view.ShowWindow();
//}
//
//void CAddHarmonicDlgPresenter::Update()
//{
//	UpdateHarmonicsList();
//	//UpdateTable(); TODO::update table
//	UpdateChart();
//}
//
//void CAddHarmonicDlgPresenter::AddHarmonic()
//{
//	m_collection.AddHarmonic(1, 1, 0, HarmonicType::Sin);
//	m_collection.GetHarmonic(m_collection.GetHarmonicsCount() - 1)
//		->DoOnHarmonicChange(std::bind(&CAddHarmonicDlgPresenter::Update, this));
//	m_view.InitDefaultHarmonic();
//	m_view.UpdateFields(1, 1, 0, HarmonicType::Sin);
//}
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

