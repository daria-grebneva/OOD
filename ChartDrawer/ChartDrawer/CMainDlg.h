
// MainDlg.h : header file
//
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
		IDD = IDD_MODELVIEWCONTROLLER_DIALOG
	};
#endif

	void SetHarmonicParams(double a, double b, double c) final;
	void SetNoSolution() final;
	void SetInfiniteSolutions() final;
	void SetSingleSolution(double solution) final;
	void SetTwoRootsSolutuion(double root1, double root2) final;
	IChartView& GetChartView() final;

	sig::connection DoOnAmplitudeChange(const HarmonicChangeSignal::slot_type& handler) final;
	sig::connection DoOnFrequencyChange(const HarmonicChangeSignal::slot_type& handler) final;
	sig::connection DoOnPhaseChange(const HarmonicChangeSignal::slot_type& handler) final;
	sig::connection DoOnInit(const InitSignal::slot_type& handler) final;

protected:
	BOOL PreTranslateMessage(MSG* msg) override;
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support

	// Implementation
private:
	void SetSolutionText(const std::wstring& text);
	void SetEquationText(const std::wstring& text);
	void UpdateEquation();
	void OnChangeAmplitude();
	void OnChangeFrequency();
	void OnChangePhase();

	void OnOK() final;

	afx_msg void OnKillfocusAmplitude();
	afx_msg void OnKillfocusFrequency();
	afx_msg void OnKillfocusPhase();

	double m_amplitude = 0;
	double m_frequency = 0;
	double m_phase = 0;

	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

	HarmonicChangeSignal m_amplitudeChanged;
	HarmonicChangeSignal m_frequencyChanged;
	HarmonicChangeSignal m_phaseChanged;
	InitSignal m_init;

private:
	CChartView m_chart;
};
