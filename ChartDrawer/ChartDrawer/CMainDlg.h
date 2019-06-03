#pragma once

#include "CChartView.h"
#include "IMainDlgView.h"

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
	void AddHarmonicsToTableBox(std::vector<std::pair<double, double>> const& table) override final;
	void InitDefaultHarmonic() override final;
	void UpdateFields(double amplitude, double frequency, double phase, HarmonicType type) override final;
	void UpdateAddingInfo() override final;
	IChartView& GetChartView() final;
	CListBox m_harmonicsList;
	CListBox m_tableX;
	CListBox m_tableY;
	CButton m_buttonSin;
	CButton m_buttonCos;
	CButton m_buttonAdd;
	CButton m_buttonDelete;
	CEdit m_amplitude;
	CEdit m_frequency;
	CEdit m_phase;
	CTabCtrl m_tabs;
	CEdit m_x;
	CEdit m_y;

	sig::connection DoOnAmplitudeChange(const HarmonicCoeffChangeSignal::slot_type& handler) final;
	sig::connection DoOnFrequencyChange(const HarmonicCoeffChangeSignal::slot_type& handler) final;
	sig::connection DoOnPhaseChange(const HarmonicCoeffChangeSignal::slot_type& handler) final;
	sig::connection DoOnHarmonicTypeChange(const HarmonicTypeChangeSignal::slot_type& handler) final;
	sig::connection DoOnAddHarmonicButtonClicked(const HarmonicAddSignal::slot_type& handler) final;
	sig::connection DoOnDeleteHarmonic(const HarmonicDeleteSignal::slot_type& handler) final;
	sig::connection DoOnInit(const InitSignal::slot_type& handler) final;
	sig::connection DoOnSetFocusListBox(const HarmonicFocusListBoxChangeSignal::slot_type& handler) final;
	sig::connection DoOnAddHarmonic(const HarmonicAddSolutionSignal::slot_type& handler) final;

protected:
	BOOL PreTranslateMessage(MSG* msg) override;
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support

	// Implementation
private:
	void OnChangeAmplitude();
	void OnChangeFrequency();
	void OnChangePhase();
	void SetEnable(bool enable);

	void OnOK() final;

	afx_msg void OnKillfocusAmplitude();
	afx_msg void OnKillfocusFrequency();
	afx_msg void OnKillfocusPhase();
	afx_msg void OnClickedRadioSin();
	afx_msg void OnClickedRadioCos();
	afx_msg void OnClickedAddHarmonic();
	afx_msg void OnClickedDeleteHarmonic();
	afx_msg void OnSetFocusListBox();
	afx_msg void OnKillFocusListBox();

	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	HarmonicCoeffChangeSignal m_amplitudeChanged;
	HarmonicCoeffChangeSignal m_frequencyChanged;
	HarmonicCoeffChangeSignal m_phaseChanged;
	HarmonicTypeChangeSignal m_typeChanged;
	HarmonicAddSignal m_addHarmonic;
	HarmonicAddSolutionSignal m_addHarmonicSolution;
	HarmonicDeleteSignal m_deleteHarmonic;
	HarmonicFocusListBoxChangeSignal m_setFocusList;
	InitSignal m_init;

	double GetHarmonicCoeffValue(CEdit& coef);

private:
	CChartView m_chart;

public:
	afx_msg void OnTcnSelchangeTabs(NMHDR* pNMHDR, LRESULT* pResult);
};
