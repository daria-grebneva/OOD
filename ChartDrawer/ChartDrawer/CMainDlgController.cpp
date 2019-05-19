#include "stdafx.h"
#include "CMainDlgController.h"
#include "CEquationSolver.h"
#include "CMainDlg.h"

CMainDlgController::CMainDlgController(IHarmonicCollection& collection, CWnd* parent)
	: m_collection(collection)
	, m_dlg(collection, *this, parent)
{
}

CMainDlg& CMainDlgController::GetDialog()
{
	return m_dlg;
}

void CMainDlgController::ShowDialog()
{
	m_dlg.DoModal();
}

void CMainDlgController::SetAmplitude(int index, double a)
{
	m_collection.GetHarmonic(index)->SetAmplitude(a);
}

void CMainDlgController::SetFrequence(int index, double b)
{
	m_collection.GetHarmonic(index)->SetFrequency(b);
}

void CMainDlgController::SetPhase(int index, double c)
{
	m_collection.GetHarmonic(index)->SetPhase(c);
}
