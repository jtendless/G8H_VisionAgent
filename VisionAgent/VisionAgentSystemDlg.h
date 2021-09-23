#pragma once
#include "../Module/Vision/VisionAgentDefine.h"

#include "VisionAgentSystemCameraDlg.h"
#include "VisionAgentSystemSafetyDlg.h"
#include "VisionAgentSystemOptionDlg.h"



// CVisionAgentSystemDlg ��ȭ �����Դϴ�.

class CVisionAgentSystemDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVisionAgentSystemDlg)

public:
	CVisionAgentSystemDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CVisionAgentSystemDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SYSTEM_DIALOG };
#endif
	void Dialog_Init();
	void ShowDlg(int nDlgNo, int nSubDlgNo);
	void Dlg_HideWindow();

	int m_nCurrentManualNo = 0;

	CButton m_btnSystem[MAX_SYSTEM_DLG];
	CColorStatic m_stcSystem_Dlg_Lamp[MAX_SYSTEM_DLG];

	CVisionAgentSystemCameraDlg		m_SystemCameraDlg;
	CVisionAgentSystemSafetyDlg			m_SystemSafetyDlg;
	CVisionAgentSystemOptionDlg			m_SystemOptionDlg;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnSystemSafety();
	afx_msg void OnBnClickedBtnSystemOption();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonSystemSave();
	afx_msg void OnBnClickedButtonSystemClose();
	afx_msg void OnBnClickedBtnSystemCamera();
};
