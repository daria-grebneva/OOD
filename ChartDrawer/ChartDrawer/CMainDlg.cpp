#include "stdafx.h"
#include "CMainDlg.h"
#include "SelectedViewType.h"
#include "afxdialogex.h"
#include "resource.h"
//#include "resource1.h"

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
	DDX_Control(pDX, IDC_AMPLITUDE, m_amplitude);
	DDX_Control(pDX, IDC_HARMONICS_LISTBOX, m_harmonicsList);
	DDX_Control(pDX, IDC_RADIO_SIN, m_buttonSin);
	DDX_Control(pDX, IDC_RADIO_COS, m_buttonCos);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_buttonAdd);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_buttonDelete);
	DDX_Control(pDX, IDC_FREQUENCE, m_frequency);
	DDX_Control(pDX, IDC_PHASE, m_phase);
	DDX_Control(pDX, IDC_TABS, m_tabs);
	DDX_Control(pDX, IDC_LIST_TABLE_X, m_tableX);
	DDX_Control(pDX, IDC_LIST_TABLE_Y, m_tableY);
	//DDX_Control(pDX, IDD_TAB_CHART, m_tabChart);
	//DDX_Control(pDX, IDD_TAB_TABLE, m_tabTable);
}

BEGIN_MESSAGE_MAP(CMainDlg, CDialogEx)
	ON_EN_KILLFOCUS(IDC_AMPLITUDE, &CMainDlg::OnKillfocusAmplitude)
	ON_EN_KILLFOCUS(IDC_FREQUENCE, &CMainDlg::OnKillfocusFrequency)
	ON_EN_KILLFOCUS(IDC_PHASE, &CMainDlg::OnKillfocusPhase)
	ON_BN_CLICKED(IDC_RADIO_SIN, &CMainDlg::OnClickedRadioSin)
	ON_BN_CLICKED(IDC_RADIO_COS, &CMainDlg::OnClickedRadioCos)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CMainDlg::OnClickedAddHarmonic)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CMainDlg::OnClickedDeleteHarmonic)
	ON_LBN_SELCHANGE(IDC_HARMONICS_LISTBOX, &CMainDlg::OnSetFocusListBox)

	//ON_COMMAND(IDD_DIALOG1, &CMainDlg::OnKillFocusAmplitude)
	//ON_CBN_SELCHANGE(IDC_COMBO1, &CMainDlg::OnCbnSelchangeCombo1)
	//ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CMainDlg::OnTcnSelchangeTab1)
	//ON_CBN_SELCHANGE(IDC_COMBO3, &CMainDlg::OnCbnSelchangeCombo3)
	//ON_LBN_SELCHANGE(IDC_HARMONICS_LISTBOX, &CMainDlg::OnLbnSelchangeHarmonicsListbox)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABS, &CMainDlg::OnTcnSelchangeTabs)
END_MESSAGE_MAP()

BOOL CMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE); // Set big icon
	SetIcon(m_hIcon, FALSE); // Set small icon

	m_chart.SubclassDlgItem(IDC_CHART, this);
	GetDlgItem(IDC_BUTTON_DELETE)->EnableWindow(false);
	m_tabs.InsertItem(static_cast<int>(SelectedViewType::Chart), _T("Chart View"));
	m_tabs.InsertItem(static_cast<int>(SelectedViewType::Table), _T("Table View"));
	m_tableX.ShowWindow(SW_HIDE);
	m_tableY.ShowWindow(SW_HIDE);
	m_chart.ShowWindow(SW_SHOW);

	m_init();

	return TRUE; // return TRUE  unless you set the focus to a control
}

void CMainDlg::AddHarmonicsToTableBox(std::vector<std::pair<double, double>> const & table)
{
	m_tableX.ResetContent();
	m_tableY.ResetContent();
	for (auto & str : table)
	{
		m_tableX.AddString(std::to_wstring(str.first).c_str());
		m_tableY.AddString(std::to_wstring(str.second).c_str());
	}
}

void CMainDlg::SetHarmonicParams(double amplitude, double frequency, double phase)
{
	m_amplitude.SetWindowTextW((boost::wformat(L"%1%") % amplitude).str().c_str());
	m_frequency.SetWindowTextW((boost::wformat(L"%1%") % frequency).str().c_str());
	m_phase.SetWindowTextW((boost::wformat(L"%1%") % phase).str().c_str());
	if (m_hWnd)
	{
		UpdateData(FALSE);
	}
}

sig::connection CMainDlg::DoOnInit(const InitSignal::slot_type& handler)
{
	return m_init.connect(handler);
}

void CMainDlg::InitDefaultHarmonic()
{
	int num = m_harmonicsList.GetCount() - 1;
	m_harmonicsList.SetCurSel(num);
	m_buttonSin.SetCheck(1);
	m_buttonCos.SetCheck(0);
	GetDlgItem(IDC_BUTTON_DELETE)->EnableWindow(true);
	GetDlgItem(IDC_AMPLITUDE)->EnableWindow(true);
	GetDlgItem(IDC_FREQUENCE)->EnableWindow(true);
	GetDlgItem(IDC_PHASE)->EnableWindow(true);
	GetDlgItem(IDC_RADIO_SIN)->EnableWindow(true);
	GetDlgItem(IDC_RADIO_COS)->EnableWindow(true);
}

void CMainDlg::UpdateFields(double amplitude, double frequency, double phase, HarmonicType type)
{
	int index = m_harmonicsList.GetCurSel();
	if (index >= 0)
	{
		m_amplitude.SetWindowTextW((boost::wformat(L"%1%") % amplitude).str().c_str());
		m_frequency.SetWindowTextW((boost::wformat(L"%1%") % frequency).str().c_str());
		m_phase.SetWindowTextW((boost::wformat(L"%1%") % phase).str().c_str());

		auto functionType = (type == HarmonicType::Sin) ? IDC_RADIO_SIN : IDC_RADIO_COS;
		CheckRadioButton(IDC_RADIO_SIN, IDC_RADIO_COS, functionType);
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

double CMainDlg::GetHarmonicCoeffValue(CEdit & coef)
{
	CString val;
	coef.GetWindowTextW(val);
	return boost::lexical_cast<double>(val.GetBuffer());
}

void CMainDlg::OnChangeAmplitude()
{
	if (UpdateData())
	{
		int index = m_harmonicsList.GetCurSel();
		if (index >= 0)
		{
			m_amplitudeChanged(index, GetHarmonicCoeffValue(m_amplitude));
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
			m_frequencyChanged(index, GetHarmonicCoeffValue(m_frequency));
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
			m_phaseChanged(index, GetHarmonicCoeffValue(m_phase));
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
		int index = m_harmonicsList.GetCurSel();
		if (index >= 0)
		{
			m_setFocusList(index);
		}
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
			if (m_harmonicsList.GetCount() == 0)
			{
				GetDlgItem(IDC_BUTTON_DELETE)->EnableWindow(false);
				GetDlgItem(IDC_AMPLITUDE)->EnableWindow(false);
				GetDlgItem(IDC_FREQUENCE)->EnableWindow(false);
				GetDlgItem(IDC_PHASE)->EnableWindow(false);
				GetDlgItem(IDC_RADIO_SIN)->EnableWindow(false);
				GetDlgItem(IDC_RADIO_COS)->EnableWindow(false);
			}
			else
			{
				m_harmonicsList.SetCurSel((m_harmonicsList.GetCount() - 1 >= index ? index : index - 1));
			}
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


void CMainDlg::OnTcnSelchangeTabs(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
	auto selected = m_tabs.GetCurSel();

	if (selected == static_cast<int>(SelectedViewType::Chart))
	{
		m_chart.ShowWindow(SW_SHOW);
		m_tableX.ShowWindow(SW_HIDE);
		m_tableY.ShowWindow(SW_HIDE);
	} 
	else
	{
		m_chart.ShowWindow(SW_HIDE);
		m_tableX.ShowWindow(SW_SHOW);
		m_tableY.ShowWindow(SW_SHOW);
	}
}
