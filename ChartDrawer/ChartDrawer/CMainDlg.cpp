
// MainDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CMainDlg.h"
//#include "CEquationSolver.h"
#include "afxdialogex.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MODELVIEWPRESENTER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

BOOL CMainDlg::PreTranslateMessage(MSG* msg)
{
	if (msg->message == WM_KEYDOWN && msg->wParam == VK_RETURN)
	{
		auto focus = GetFocus();
		if (focus == GetDlgItem(IDC_AMPLITUDE))
		{
			OnChangeAmplitude();
			return TRUE;
		}
		else if (focus == GetDlgItem(IDC_FREQUENCE))
		{
			OnChangeFrequency();
			return TRUE;
		}
		else if (focus == GetDlgItem(IDC_PHASE))
		{
			OnChangePhase();
			return TRUE;
		}
	}
	return CDialogEx::PreTranslateMessage(msg);
}

void CMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_AMPLITUDE, m_amplitude);
	DDX_Text(pDX, IDC_FREQUENCE, m_frequency);
	DDX_Text(pDX, IDC_PHASE, m_phase);
}

BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_EN_KILLFOCUS(IDC_AMPLITUDE, &CMainDlg::OnKillfocusAmplitude)
	ON_EN_KILLFOCUS(IDC_FREQUENCE, &CMainDlg::OnKillfocusFrequency)
	ON_EN_KILLFOCUS(IDC_PHASE, &CMainDlg::OnKillfocusPhase)
END_MESSAGE_MAP()

BOOL CMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE); // Set big icon
	SetIcon(m_hIcon, FALSE); // Set small icon

	m_chart.SubclassDlgItem(IDC_CHART, this);

	m_init();

	UpdateEquation();

	return TRUE; // return TRUE  unless you set the focus to a control
}

void CMainDlg::SetHarmonicParams(double amplitude, double frequency, double phase)
{
	m_amplitude = amplitude;
	m_frequency = frequency;
	m_phase = phase;
	if (m_hWnd)
	{
		UpdateData(FALSE);
	}
}

sig::connection CMainDlg::DoOnInit(const InitSignal::slot_type& handler)
{
	return m_init.connect(handler);
}

IChartView& CMainDlg::GetChartView()
{
	return m_chart;
}

void CMainDlg::SetNoSolution()
{
	SetSolutionText(L"No real roots");
}

void CMainDlg::SetInfiniteSolutions()
{
	SetSolutionText(L"Infinite number of roots");
}

void CMainDlg::SetSingleSolution(double solution)
{
	SetSolutionText((boost::wformat(L"One root: %1%") % solution).str());
}

void CMainDlg::SetTwoRootsSolutuion(double root1, double root2)
{
	SetSolutionText((boost::wformat(L"Two roots: %1% and %2%") % root1 % root2).str());
}

sig::connection CMainDlg::DoOnAmplitudeChange(const HarmonicChangeSignal::slot_type& handler)
{
	return m_amplitudeChanged.connect(handler);
}

sig::connection CMainDlg::DoOnFrequencyChange(const HarmonicChangeSignal::slot_type& handler)
{
	return m_frequencyChanged.connect(handler);
}

sig::connection CMainDlg::DoOnPhaseChange(const HarmonicChangeSignal::slot_type& handler)
{
	return m_phaseChanged.connect(handler);
}

void CMainDlg::SetSolutionText(const std::wstring& text)
{
	SetDlgItemText(IDC_SOLUTION, text.c_str());
}

void CMainDlg::SetEquationText(const std::wstring& text)
{
	SetDlgItemText(IDC_EQUATION, text.c_str());
}

void CMainDlg::UpdateEquation()
{
	auto ToSignedString = [](double value) {
		std::wostringstream strm;
		strm << std::abs(value);

		return ((value < 0) ? L"- " : L"+ ") + strm.str();
	};

	SetEquationText((boost::wformat(L"%1%x\u00b2 %2%x %3% = 0") % m_amplitude % ToSignedString(m_frequency) % ToSignedString(m_phase)).str());
}

void CMainDlg::OnChangeAmplitude()
{
	if (UpdateData())
	{
		m_amplitudeChanged(m_amplitude);
		UpdateEquation();
	}
}

void CMainDlg::OnChangeFrequency()
{
	if (UpdateData())
	{
		m_frequencyChanged(m_frequency);
		UpdateEquation();
	}
}

void CMainDlg::OnChangePhase()
{
	if (UpdateData())
	{
		m_phaseChanged(m_phase);
		UpdateEquation();
	}
}

void CMainDlg::OnOK()
{
}

void CMainDlg::OnKillfocusAmplitude()
{
	OnChangeAmplitude();
}

void CMainDlg::OnKillfocusFrequency()
{
	OnChangeFrequency();
}

void CMainDlg::OnKillfocusPhase()
{
	OnChangePhase();
}
