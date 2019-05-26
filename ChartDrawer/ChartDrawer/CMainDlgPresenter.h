#pragma once
#include "CHarmonicType.h"

class IHarmonicCollection;
class IMainDlgView;

class CMainDlgPresenter
{
public:
	typedef std::vector<std::wstring> ListBox;

	CMainDlgPresenter(IHarmonicCollection& solver, IMainDlgView& view);

private:
	void InitView();
	void UpdateHarmonicsList();
	void UpdateChart();
	void AddHarmonic();
	void DeleteHarmonic(int index);
	void SetAmplitude(int index, double value);
	void SetFrequency(int index, double value);
	void SetPhase(int index, double value);
	void SetHarmonicType(int index, CHarmonicType value);
	void Update();

	IHarmonicCollection& m_collection;
	IMainDlgView& m_view;
};
