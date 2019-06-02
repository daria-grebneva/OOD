#include "stdafx.h"
#include "CMainDlg.h"
#include "afxdialogex.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CMainDlg::CMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
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
	DDX_Control(pDX, IDC_HARMONICS_LISTBOX, m_harmonicsList);
	DDX_Control(pDX, IDC_RADIO_SIN, m_buttonSin);
	DDX_Control(pDX, IDC_RADIO_COS, m_buttonCos);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_buttonAdd);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_buttonDelete);
	DDX_Text(pDX, IDC_FREQUENCE, m_frequency);
	DDX_Text(pDX, IDC_PHASE, m_phase);
}

BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_EN_KILLFOCUS(IDC_AMPLITUDE, &CMainDlg::OnKillfocusAmplitude)
	ON_EN_KILLFOCUS(IDC_FREQUENCE, &CMainDlg::OnKillfocusFrequency)
	ON_EN_KILLFOCUS(IDC_PHASE, &CMainDlg::OnKillfocusPhase)
	ON_BN_CLICKED(IDC_RADIO_SIN, &CMainDlg::OnClickedRadioSin)
	ON_BN_CLICKED(IDC_RADIO_COS, &CMainDlg::OnClickedRadioCos)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CMainDlg::OnClickedAddHarmonic)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CMainDlg::OnClickedDeleteHarmonic)
	ON_LBN_SETFOCUS(IDC_HARMONICS_LISTBOX, &CMainDlg::OnSetFocusListBox)
	//ON_COMMAND(IDD_DIALOG1, &CMainDlg::OnKillFocusAmplitude)
	//ON_CBN_SELCHANGE(IDC_COMBO1, &CMainDlg::OnCbnSelchangeCombo1)
	//ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CMainDlg::OnTcnSelchangeTab1)
	//ON_CBN_SELCHANGE(IDC_COMBO3, &CMainDlg::OnCbnSelchangeCombo3)
	//ON_LBN_SELCHANGE(IDC_HARMONICS_LISTBOX, &CMainDlg::OnLbnSelchangeHarmonicsListbox)
END_MESSAGE_MAP()

BOOL CMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE); // Set big icon
	SetIcon(m_hIcon, FALSE); // Set small icon

	m_chart.SubclassDlgItem(IDC_CHART, this);

	m_init();

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
	GetDlgItem(IDC_CHART)->ShowWindow(true);
}

void CMainDlg::InitDefaultHarmonic()
{
	int num = m_harmonicsList.GetCount() - 1;
	m_harmonicsList.SetCurSel(num);
	m_buttonSin.SetCheck(1);
	m_buttonCos.SetCheck(0);
}

void CMainDlg::UpdateFields(double amplitude, double frequency, double phase, HarmonicType type)
{
	int index = m_harmonicsList.GetCurSel();
	if (index >= 0)
	{
		//TODO::обновить данные гармоники
	}
}

IChartView& CMainDlg::GetChartView()
{
	return m_chart;
}

sig::connection CMainDlg::DoOnAmplitudeChange(const HarmonicCoeffChangeSignal::slot_type& handler)
{
	return m_amplitudeChanged.connect(handler);
}

sig::connection CMainDlg::DoOnFrequencyChange(const HarmonicCoeffChangeSignal::slot_type& handler)
{
	return m_frequencyChanged.connect(handler);
}

sig::connection CMainDlg::DoOnPhaseChange(const HarmonicCoeffChangeSignal::slot_type& handler)
{
	return m_phaseChanged.connect(handler);
}

sig::connection CMainDlg::DoOnHarmonicTypeChange(const HarmonicTypeChangeSignal::slot_type& handler)
{
	return m_typeChanged.connect(handler);
}

sig::connection CMainDlg::DoOnAddHarmonic(const HarmonicAddSignal::slot_type& handler)
{
	return m_addHarmonic.connect(handler);
}

sig::connection CMainDlg::DoOnDeleteHarmonic(const HarmonicDeleteSignal::slot_type& handler)
{
	return m_deleteHarmonic.connect(handler);
}

sig::connection CMainDlg::DoOnSetFocusListBox(const HarmonicFocusListBoxChangeSignal::slot_type& handler)
{
	return m_setFocusList.connect(handler);
}

void CMainDlg::OnChangeAmplitude()
{
	if (UpdateData())
	{
		int index = m_harmonicsList.GetCurSel();
		if (index >= 0)
		{
			m_amplitudeChanged(index, m_amplitude);
			m_harmonicsList.SetCurSel(index);
		}
	}
}

void CMainDlg::OnChangeFrequency()
{
	if (UpdateData())
	{
		int index = m_harmonicsList.GetCurSel();
		if (index >= 0)
		{
			m_frequencyChanged(index, m_frequency);
			m_harmonicsList.SetCurSel(index);
		}
	}
}

void CMainDlg::OnChangePhase()
{
	if (UpdateData())
	{
		int index = m_harmonicsList.GetCurSel();
		if (index >= 0)
		{
			m_phaseChanged(index, m_phase);
			m_harmonicsList.SetCurSel(index);
		}
	}
}

void CMainDlg::OnOK()
{
}

void CMainDlg::OnKillfocusAmplitude()
{
	OnChangeAmplitude();
}

void CMainDlg::OnClickedRadioSin()
{
	if (UpdateData())
	{
		int index = m_harmonicsList.GetCurSel();
		if (index >= 0)
		{
			m_typeChanged(index, HarmonicType::Sin);
			m_harmonicsList.SetCurSel(index);
		}
	}
}

void CMainDlg::OnClickedRadioCos()
{
	if (UpdateData())
	{
		int index = m_harmonicsList.GetCurSel();
		if (index >= 0)
		{
			m_typeChanged(index, HarmonicType::Cos);
			m_harmonicsList.SetCurSel(index);
		}
	}
}

void CMainDlg::OnClickedAddHarmonic()
{
	if (UpdateData())
	{
		m_addHarmonic();
		int index = m_harmonicsList.GetCount() - 1;
		m_harmonicsList.SetCurSel(index);
	}
}

void CMainDlg::OnSetFocusListBox()
{
	if (UpdateData())
	{
	}
}

void CMainDlg::OnClickedDeleteHarmonic()
{
	if (UpdateData())
	{
		int index = m_harmonicsList.GetCurSel();
		if (index >= 0)
		{
			m_deleteHarmonic(index);
		}
	}
}

void CMainDlg::OnKillfocusFrequency()
{
	OnChangeFrequency();
}

void CMainDlg::OnKillfocusPhase()
{
	OnChangePhase();
}

void CMainDlg::AddHarmonicsToListBox(ListBox const& harmonicsList)
{
	m_harmonicsList.ResetContent();

	for (auto& str : harmonicsList)
	{
		m_harmonicsList.AddString(str.c_str());
	}
}
