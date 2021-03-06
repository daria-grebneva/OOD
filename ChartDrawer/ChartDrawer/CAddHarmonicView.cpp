#include "stdafx.h"
#include "CAddHarmonicView.h"
#include "afxdialogex.h"
#include "resource.h"
#include "resource1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CAddHarmonicView::CAddHarmonicView(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ADD_NEW_HARMONIC_DIALOG, pParent)
{
}

BOOL CAddHarmonicView::PreTranslateMessage(MSG* msg)
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

void CAddHarmonicView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_AMPLITUDE, m_amplitude);
	DDX_Control(pDX, IDC_RADIO_SIN, m_buttonSin);
	DDX_Control(pDX, IDC_RADIO_COS, m_buttonCos);
	DDX_Control(pDX, IDC_FREQUENCE, m_frequency);
	DDX_Control(pDX, IDC_PHASE, m_phase);
	DDX_Control(pDX, IDOK, m_buttonOK);
}

BEGIN_MESSAGE_MAP(CAddHarmonicView, CDialogEx)
	ON_EN_KILLFOCUS(IDC_AMPLITUDE, &CAddHarmonicView::OnKillfocusAmplitude)
	ON_EN_KILLFOCUS(IDC_FREQUENCE, &CAddHarmonicView::OnKillfocusFrequency)
	ON_EN_KILLFOCUS(IDC_PHASE, &CAddHarmonicView::OnKillfocusPhase)
	ON_BN_CLICKED(IDC_RADIO_SIN, &CAddHarmonicView::OnClickedRadioSin)
	ON_BN_CLICKED(IDC_RADIO_COS, &CAddHarmonicView::OnClickedRadioCos)
	ON_BN_CLICKED(IDOK, &CAddHarmonicView::OnClickedAddHarmonic)
END_MESSAGE_MAP()

BOOL CAddHarmonicView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_init();

	return TRUE; // return TRUE  unless you set the focus to a control
}

sig::connection CAddHarmonicView::DoOnAmplitudeChange(const HarmonicCoeffChangeSignal::slot_type& handler)
{
	return m_amplitudeChanged.connect(handler);
}

sig::connection CAddHarmonicView::DoOnFrequencyChange(const HarmonicCoeffChangeSignal::slot_type& handler)
{
	return m_frequencyChanged.connect(handler);
}

sig::connection CAddHarmonicView::DoOnPhaseChange(const HarmonicCoeffChangeSignal::slot_type& handler)
{
	return m_phaseChanged.connect(handler);
}

sig::connection CAddHarmonicView::DoOnHarmonicTypeChange(const HarmonicTypeChangeSignal::slot_type& handler)
{
	return m_typeChanged.connect(handler);
}

sig::connection CAddHarmonicView::DoOnInit(const InitSignal::slot_type& handler)
{
	return m_init.connect(handler);
}

sig::connection CAddHarmonicView::DoOnAddHarmonic(const HarmonicAddSignal::slot_type& handler)
{
	return m_addHarmonic.connect(handler);
}

void CAddHarmonicView::InitDefaultHarmonic()
{
	m_buttonSin.SetCheck(1);
	m_buttonCos.SetCheck(0);
}

void CAddHarmonicView::UpdateFields(double amplitude, double frequency, double phase, HarmonicType type)
{
	m_amplitude.SetWindowTextW((boost::wformat(L"%1%") % amplitude).str().c_str());
	m_frequency.SetWindowTextW((boost::wformat(L"%1%") % frequency).str().c_str());
	m_phase.SetWindowTextW((boost::wformat(L"%1%") % phase).str().c_str());

	auto functionType = (type == HarmonicType::Sin) ? IDC_RADIO_SIN : IDC_RADIO_COS;
	CheckRadioButton(IDC_RADIO_SIN, IDC_RADIO_COS, functionType);
	UpdateHarmonic();
}

void CAddHarmonicView::SetHarmonicText(const std::wstring& text)
{
	SetDlgItemText(IDC_STATIC_HARMONIC, text.c_str());
}

void CAddHarmonicView::UpdateHarmonic()
{
	SetHarmonicText((boost::wformat(L"%1% * %4%(%2% * x + %3%)")
		% GetHarmonicCoeffValue(m_amplitude)
		% GetHarmonicCoeffValue(m_frequency)
		% GetHarmonicCoeffValue(m_phase)
		% ((m_buttonSin.GetCheck() == 1) ? "sin" : "cos"))
						.str());
}

double CAddHarmonicView::GetHarmonicCoeffValue(CEdit& coef)
{
	CString val;
	coef.GetWindowTextW(val);
	return boost::lexical_cast<double>(val.GetBuffer());
}

void CAddHarmonicView::OnKillfocusAmplitude()
{
	try
	{
		OnChangeAmplitude();
	}
	catch (std::exception& e)
	{
		MessageBox(L"Entered wrong data");
	}
}

void CAddHarmonicView::OnClickedAddHarmonic()
{
	m_addHarmonic();

	EndDialog(1);
}

void CAddHarmonicView::OnKillfocusFrequency()
{
	try
	{
		OnChangeFrequency();
	}
	catch (std::exception& e)
	{
		MessageBox(L"Entered wrong data");
	}
}

void CAddHarmonicView::OnKillfocusPhase()
{
	try
	{
		OnChangePhase();
	}
	catch (std::exception& e)
	{
		MessageBox(L"Entered wrong data");
	}
}

void CAddHarmonicView::OnClickedRadioSin()
{
	if (UpdateData())
	{
		m_typeChanged(HarmonicType::Sin);
		UpdateHarmonic();
	}
}

void CAddHarmonicView::OnClickedRadioCos()
{
	if (UpdateData())
	{
		m_typeChanged(HarmonicType::Cos);
		UpdateHarmonic();
	}
}

void CAddHarmonicView::OnChangeAmplitude()
{
	if (UpdateData())
	{
		m_amplitudeChanged(GetHarmonicCoeffValue(m_amplitude));
		UpdateHarmonic();
	}
}

void CAddHarmonicView::OnChangeFrequency()
{
	if (UpdateData())
	{
		m_frequencyChanged(GetHarmonicCoeffValue(m_frequency));
		UpdateHarmonic();
	}
}

void CAddHarmonicView::OnChangePhase()
{
	if (UpdateData())
	{
		m_phaseChanged(GetHarmonicCoeffValue(m_phase));
		UpdateHarmonic();
	}
}
