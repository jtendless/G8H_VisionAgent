#pragma once

//#include "MeasurementSubAoiDlg.h"
#include "VisionAgentMeasurementBrightnessDlg.h"

// CMeasurementDlg 대화 상자입니다.
enum 
{
	MEASUREMENT_BRIGHTNESS_DLG,

	MAX_MEASUREMENT_DLG
};
enum
{
	MEASUREMENT_SUB_PAGE_1 = 0,
	MEASUREMENT_SUB_PAGE_2,
	MEASUREMENT_SUB_PAGE_3,
	MEASUREMENT_SUB_PAGE_4,
	MEASUREMENT_SUB_PAGE_5,

	MAX_MEASUREMENT_SUB_DLG
};
class CMeasurementDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMeasurementDlg)

public:
	CMeasurementDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMeasurementDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VISION_AGENT_MASUREMENT_DIALOG };
#endif
protected:
	int m_nCurrentNo = 0;
	int m_nCurrentSubNo = 0;
private:
	void Dialog_Init();
	void ShowDlg(int nDlgNo, int nSubDlgNo);
	void Dlg_HideWindow();
	BOOL InitPara();

	CButton m_btnMeasurement[MAX_MEASUREMENT_DLG];
	CButton m_btnSubMeasurement[MAX_MEASUREMENT_SUB_DLG];

	CColorStatic m_stcMeasurement_Dlg_Lamp[MAX_MEASUREMENT_DLG];
	CColorStatic m_stcMeasurement_Sub_Dlg_Lamp[MAX_MEASUREMENT_SUB_DLG];

	CVisionAgentMeasurementBrightnessDlg		m_BrightnessDlg;

public:
	BOOL Is_Comp_Safe_Hwnd();
	BOOL RecalcLayout();
	BOOL ShowData();

	void ChangeUI();
	void ChangeData();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual BOOL DestroyWindow();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnBnClickedButtonSubPage1();
	afx_msg void OnBnClickedButtonMeasurementBrightness();
	afx_msg void OnBnClickedButtonSubPage2();
	afx_msg void OnBnClickedButtonSubPage3();
	afx_msg void OnBnClickedButtonSubPage4();
	afx_msg void OnBnClickedButtonSubPage5();
};
