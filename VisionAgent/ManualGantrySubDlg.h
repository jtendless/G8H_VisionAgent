#pragma once


// CManualGantrySubDlg 대화 상자입니다.


class CManualGantrySubDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManualGantrySubDlg)

public:
	CManualGantrySubDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CManualGantrySubDlg();

	BOOL m_bDialog_Entry;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_MANUAL_SUB_GANTRY };
#endif
	CEdit m_Edit_GantryPosX1, m_Edit_GantryPosY1, m_Edit_GantryPosZ1;
	CEdit m_Edit_GantryPosX2, m_Edit_GantryPosY2, m_Edit_GantryPosZ2;


	CEdit m_Edit_GantryGetLcValue;

	CColorStatic m_stcTestLed;

	BOOL(CStageMotion::*FindPatternLeft)(double, double);
	BOOL(CStageMotion::*FindPatternRight)(double, double);


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnManualTest();


	afx_msg void OnBnClickedBtnManualFindMark1();
	afx_msg void OnBnClickedBtnManualFindMark2();
	
	afx_msg void OnBnClickedBtnManualFindPatternLeft();
	afx_msg void OnBnClickedBtnManualFindPatternRight();
};
