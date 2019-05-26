#pragma once

#include "CChartView.h"
#include "IMainDlgView.h"

class CEquationSolver;
class IMainDlgController;

class CMainDlg
	: public CDialogEx
	, public IMainDlgView
{
public:
	CMainDlg(CWnd* pParent = NULL); // standard constructor

#ifdef AFX_DESIGN_TIME
	enum
	{
		IDD = IDD_DIALOG1
	};
#endif

	void SetHarmonicParams(double amplitude, double frequency, double phase) final;
	void AddHarmonicsToListBox(ListBox const& harmonicsList) override final;
	void InitDefaultHarmonic() override final;
	IChartView& GetChartView() final;
	CListBox m_harmonicsList;
	CButton m_buttonSin;
	CButton m_buttonCos;
	CButton m_buttonAdd;
	CButton m_buttonDelete;

	sig::connection DoOnAmplitudeChange(const HarmonicCoeffChangeSignal::slot_type& handler) final;
	sig::connection DoOnFrequencyChange(const HarmonicCoeffChangeSignal::slot_type& handler) final;
	sig::connection DoOnPhaseChange(const HarmonicCoeffChangeSignal::slot_type& handler) final;
	sig::connection DoOnHarmonicTypeChange(const HarmonicTypeChangeSignal::slot_type& handler) final;
	sig::connection DoOnAddHarmonic(const HarmonicAddSignal::slot_type& handler) final;
	sig::connection DoOnDeleteHarmonic(const HarmonicDeleteSignal::slot_type& handler) final;
	sig::connection DoOnInit(const InitSignal::slot_type& handler) final;

protected:
	BOOL PreTranslateMessage(MSG* msg) override;
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support

	// Implementation
private:

	void OnChangeAmplitude();
	void OnChangeFrequency();
	void OnChangePhase();

	void OnOK() final;

	afx_msg void OnKillfocusAmplitude();
	afx_msg void OnKillfocusFrequency();
	afx_msg void OnKillfocusPhase();
	afx_msg void OnClickedRadioSin();
	afx_msg void OnClickedRadioCos();
	afx_msg void OnClickedAddHarmonic();
	afx_msg void OnClickedDeleteHarmonic();

	double m_amplitude = 0;
	double m_frequency = 0;
	double m_phase = 0;
	
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	HarmonicCoeffChangeSignal m_amplitudeChanged;
	HarmonicCoeffChangeSignal m_frequencyChanged;
	HarmonicCoeffChangeSignal m_phaseChanged;
	HarmonicTypeChangeSignal m_typeChanged;
	HarmonicAddSignal m_addHarmonic;
	HarmonicDeleteSignal m_deleteHarmonic;
	InitSignal m_init;

private:
	CChartView m_chart;
};
