#pragma once
#include "CMainDlg.h"
#include "IHarmonicCollection.h"
#include "IMainDlgController.h"

class IHarmonicCollection;

class CMainDlgController : private IMainDlgController
{
public:
	CMainDlgController(IHarmonicCollection& collection, CWnd* parent = nullptr);
	CMainDlg& GetDialog();
	void ShowDialog();

private:
	void SetAmplitude(int index, double a) override;
	void SetFrequence(int index, double b) override;
	void SetPhase(int index, double c) override;

private:
	CMainDlg m_dlg;
	IHarmonicCollection& m_collection;
};
