#pragma once


// CManualGantrySubDlg ��ȭ �����Դϴ�.


class CManualGantrySubDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManualGantrySubDlg)

public:
	CManualGantrySubDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CManualGantrySubDlg();

	BOOL m_bDialog_Entry;

// ��ȭ ���� �������Դϴ�.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
