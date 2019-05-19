#pragma once
#include "CHarmonicType.h"

class IHarmonicCollection;
class IMainDlgView;

class CMainDlgPresenter
{
public:
	CMainDlgPresenter(IHarmonicCollection& solver, IMainDlgView& view);

private:
	void InitView();
	void UpdateSolution();
	void UpdateChart();

	IHarmonicCollection& m_solver;
	IMainDlgView& m_view;
};
