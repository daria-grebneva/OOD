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
	//m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

BOOL CAddHarmonicView::PreTranslateMessage(MSG* msg)
{
	if (msg->message == WM_KEYDOWN && msg->wParam == VK_RETURN)
	{
		auto focus = GetFocus();
		/*	if (focus == GetDlgItem(IDC_AMPLITUDE))
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
		}*/
	}
	return CDialogEx::PreTranslateMessage(msg);
}

void CAddHarmonicView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	/*DDX_Control(pDX, IDC_AMPLITUDE, m_amplitude);
	DDX_Control(pDX, IDC_HARMONICS_LISTBOX, m_harmonicsList);
	DDX_Control(pDX, IDC_RADIO_SIN, m_buttonSin);
	DDX_Control(pDX, IDC_RADIO_COS, m_buttonCos);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_buttonAdd);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_buttonDelete);
	DDX_Control(pDX, IDC_FREQUENCE, m_frequency);
	DDX_Control(pDX, IDC_PHASE, m_phase);*/
}

//BEGIN_MESSAGE_MAP(CAddHarmonicView, CDialogEx)
	/*ON_EN_KILLFOCUS(IDC_AMPLITUDE, &CAddHarmonicView::OnKillfocusAmplitude)
	ON_EN_KILLFOCUS(IDC_FREQUENCE, &CAddHarmonicView::OnKillfocusFrequency)
	ON_EN_KILLFOCUS(IDC_PHASE, &CAddHarmonicView::OnKillfocusPhase)
	ON_BN_CLICKED(IDC_RADIO_SIN, &CAddHarmonicView::OnClickedRadioSin)
	ON_BN_CLICKED(IDC_RADIO_COS, &CAddHarmonicView::OnClickedRadioCos)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CAddHarmonicView::OnClickedAddHarmonic)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CAddHarmonicView::OnClickedDeleteHarmonic)
	ON_LBN_SELCHANGE(IDC_HARMONICS_LISTBOX, &CAddHarmonicView::OnSetFocusListBox)*/

	//ON_COMMAND(IDD_DIALOG1, &CAddHarmonicView::OnKillFocusAmplitude)
	//ON_CBN_SELCHANGE(IDC_COMBO1, &CAddHarmonicView::OnCbnSelchangeCombo1)
	//ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CAddHarmonicView::OnTcnSelchangeTab1)
	//ON_CBN_SELCHANGE(IDC_COMBO3, &CAddHarmonicView::OnCbnSelchangeCombo3)
	//ON_LBN_SELCHANGE(IDC_HARMONICS_LISTBOX, &CAddHarmonicView::OnLbnSelchangeHarmonicsListbox)
//END_MESSAGE_MAP()

