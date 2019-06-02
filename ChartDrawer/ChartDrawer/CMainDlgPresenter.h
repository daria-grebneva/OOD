#pragma once
#include "HarmonicType.h"

class IHarmonicCollection;
class IMainDlgView;

class CMainDlgPresenter
{
public:
	typedef std::vector<std::wstring> ListBox;

	CMainDlgPresenter(IHarmonicCollection& harmonicCollection, IMainDlgView& view);

private:
	void InitView();
	void UpdateHarmonicsList();
	void UpdateChart();
	void AddHarmonic();
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
