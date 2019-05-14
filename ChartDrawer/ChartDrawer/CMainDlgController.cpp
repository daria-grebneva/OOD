#include "stdafx.h"
#include "CMainDlgController.h"
#include "CEquationSolver.h"
#include "CMainDlg.h"

CMainDlgController::CMainDlgController(CEquationSolver& solver, CWnd* parent)
	: m_solver(solver)
	, m_dlg(solver, *this, parent)
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

void CMainDlgController::SetCoeffA(double a)
{
	m_solver.SetQuadraticCoeff(a);
}

void CMainDlgController::SetCoeffB(double b)
{
	m_solver.SetLinearCoeff(b);
}

void CMainDlgController::SetCoeffC(double c)
{
	m_solver.SetConstantCoeff(c);
}
