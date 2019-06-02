#include "stdafx.h"
#include "CMainDlgPresenter.h"
#include "CAddHarmonicDlgPresenter.h"
#include "CAddHarmonicView.h"
#include "HarmonicType.h"
#include "IChartView.h"
#include "IHarmonicCollection.h"
#include "IMainDlgView.h"

CMainDlgPresenter::CMainDlgPresenter(IHarmonicCollection& harmonicCollection, IMainDlgView& view)
	: m_collection(harmonicCollection)
	, m_view(view)
{
	m_view.DoOnAmplitudeChange(std::bind(&CMainDlgPresenter::SetAmplitude, this, std::placeholders::_1, std::placeholders::_2));
	m_view.DoOnFrequencyChange(std::bind(&CMainDlgPresenter::SetFrequency, this, std::placeholders::_1, std::placeholders::_2));
	m_view.DoOnPhaseChange(std::bind(&CMainDlgPresenter::SetPhase, this, std::placeholders::_1, std::placeholders::_2));
	m_view.DoOnHarmonicTypeChange(std::bind(&CMainDlgPresenter::SetHarmonicType, this, std::placeholders::_1, std::placeholders::_2));
	m_view.DoOnAddHarmonic(std::bind(&CMainDlgPresenter::AddHarmonic, this));
	m_view.DoOnDeleteHarmonic(std::bind(&CMainDlgPresenter::DeleteHarmonic, this, std::placeholders::_1));
	m_view.DoOnSetFocusListBox(std::bind(&CMainDlgPresenter::SetFocusListBox, this, std::placeholders::_1));
	m_view.DoOnInit(std::bind(&CMainDlgPresenter::InitView, this));
	m_collection.DoOnHarmonicChange([this] {
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

void CMainDlgPresenter::SetHarmonicType(int index, HarmonicType value)
{
	m_collection.GetHarmonic(index)->SetHarmonicType(value);
}

void CMainDlgPresenter::InitView()
{
	Update();
	m_collection.AddHarmonic(1, 1, 0, HarmonicType::Sin);
	m_collection.GetHarmonic(m_collection.GetHarmonicsCount() - 1)
		->DoOnHarmonicChange(std::bind(&CMainDlgPresenter::Update, this));
	m_view.InitDefaultHarmonic();
	m_view.UpdateFields(1, 1, 0, HarmonicType::Sin);
}

void CMainDlgPresenter::Update()
{
	UpdateHarmonicsList();
	UpdateTable(); // TODO::update table
	UpdateChart();
}

void CMainDlgPresenter::UpdateTable()
{
	std::vector<std::pair<double, double>> harmonicsList;
	for (double x = -10.0; x <= +10; x += 0.1)
	{
		harmonicsList.push_back({ x, m_collection.CalculateValue(x) });
	}
	m_view.AddHarmonicsToTableBox(harmonicsList);
}

void CMainDlgPresenter::AddHarmonic()
{

	m_collection.AddHarmonic(1, 1, 0, HarmonicType::Sin);
	m_collection.GetHarmonic(m_collection.GetHarmonicsCount() - 1)
		->DoOnHarmonicChange(std::bind(&CMainDlgPresenter::Update, this));
	m_view.InitDefaultHarmonic();
	m_view.UpdateFields(1, 1, 0, HarmonicType::Sin);
	//TODO:: вызвать новое окно
	/*CAddHarmonicView dlg2;
	dlg2.DoModal();*/
}

void CMainDlgPresenter::DeleteHarmonic(int index)
{
	m_collection.DeleteHarmonic(index);
}

void CMainDlgPresenter::SetFocusListBox(int index)
{
	auto harmonic = m_collection.GetHarmonic(index);
	m_view.UpdateFields(harmonic->GetAmplitude(), harmonic->GetFrequency(), harmonic->GetPhase(), harmonic->GetHarmonicType()); //TODO:: реализовать метод, обновл€ющий пол€
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

		std::string typeStr = (type == HarmonicType::Sin) ? "sin" : "cos";

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
