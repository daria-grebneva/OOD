#pragma once
#include "HarmonicType.h"
#include "IMainDlgPresenter.h"

class IHarmonicCollection;
class IMainDlgView;

class CMainDlgPresenter : public IMainDlgPresenter
{
public:
	typedef std::vector<std::wstring> ListBox;

	CMainDlgPresenter(IHarmonicCollection& harmonicCollection, IMainDlgView& view);
	//void UpdateAddingInfo() override final;

private:
	void InitView();
	void UpdateHarmonicsList();
	void UpdateChart();
	void AddHarmonic();
	void AddHarmonicSolution();
	void DeleteHarmonic(int index);
	void SetFocusListBox(int index);
	void SetAmplitude(int index, double value);
	void SetFrequency(int index, double value);
	void SetPhase(int index, double value);
	void SetHarmonicType(int index, HarmonicType value);
	void Update();
	void UpdateTable();

	IHarmonicCollection& m_collection;
	IMainDlgView& m_view;
};
