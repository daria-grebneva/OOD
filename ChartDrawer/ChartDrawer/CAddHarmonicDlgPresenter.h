#pragma once
#include "HarmonicType.h"

class IHarmonicCollection;
class IAddHarmonicView;
class IMainDlgView;

class CAddHarmonicDlgPresenter
{
public:
	//typedef std::vector<std::wstring> ListBox;

	CAddHarmonicDlgPresenter(IHarmonicCollection& harmonicCollection, IAddHarmonicView& view, IMainDlgView& mainView);

private:
	struct Harmonic
	{
		double amplitude = 1;
		double frequency = 1;
		double phase = 0;
		HarmonicType type = HarmonicType::Sin;
	};

	Harmonic m_harmonic;

	void InitView();
	/*void UpdateHarmonicsList();
	void UpdateChart();*/
	void AddHarmonic();
	/*void DeleteHarmonic(int index);
	void SetFocusListBox(int index);*/
	void SetAmplitude(double value);
	void SetFrequency(double value);
	void SetPhase(double value);
	void SetHarmonicType(HarmonicType value);
	void Update();

	IAddHarmonicView& m_view;
	IHarmonicCollection& m_collection;
	IMainDlgView& m_mainView;
};
