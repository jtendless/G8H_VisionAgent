#pragma once

// CSystemDlg 대화 상자입니다.

class CSystemOptionSubDlg;
class CSystemMachineCommunicationSubDlg;
class CSystemSaftySubDlg;
class CVisionAgentSystem_CoordinateDlg;
class CVisionAgentSystem_ESCDlg;

typedef enum en_SYSTEM_DLG_DEF_BTN
{	
	SYSTEM_SAFTY_DLG = 0,
	SYSTEM_OPTION_DLG,	
	SYSTEM_COORDINATE_DLG,
	SYSTEM_ESC_DLG, //KJT 20210329

	MAX_SYSTEM_DLG
}enum_SYSTEM_DLG_DEF_BTN;
typedef enum en_SYSTEM_SUB_DLG_DEF_BTN
{
	SYSTEM_SUB_PAGE1_DLG,
	SYSTEM_SUB_PAGE2_DLG,

	MAX_SYSTEM_SUB_DLG
}enum_SYSTEM_SUB_DLG_DEF_BTN;

class CSystemDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSystemDlg)

public:
	CSystemDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSystemDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VISION_AGENT_SYSTEM_DIALOG };
#endif
protected:
	int m_nCurrentNo = 0;
	int m_nCurrentSubNo = 0;

private:
	void Dialog_Init();
	void ShowDlg(int nDlgNo, int nSubDlgNo);
	void Dlg_HideWindow();

	CButton m_btnSystem[MAX_SYSTEM_DLG];
	CButton m_btnSubSystem[MAX_SYSTEM_SUB_DLG];

	CColorStatic m_stcSystem_Dlg_Lamp[MAX_SYSTEM_DLG];
	CColorStatic m_stcSystem_Sub_Dlg_Lamp[MAX_SYSTEM_SUB_DLG];

public:
	CSystemOptionSubDlg					*m_pSystemOptionSubDlg;	
	CSystemSaftySubDlg					*m_pSystemSaftySubDlg;
	CVisionAgentSystem_CoordinateDlg	*m_pSystemCoordinateDlg;
	CVisionAgentSystem_ESCDlg			*m_pSystemESCDlg;//21.04.09 sjc

	BOOL Is_Comp_Safe_Hwnd();
	BOOL RecalcLayout();
	BOOL ShowData();
	BOOL OnEraseBkgnd();

	void ChangeUI();
	void ChangeData();


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL DestroyWindow();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonSubPage1();
	afx_msg void OnBnClickedButtonSubPage2();
	afx_msg void OnBnClickedBtnSystemClose();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSize(UINT nType, int cx, int cy);	
	afx_msg void OnBnClickedButtonSystemSafty();
	afx_msg void OnBnClickedButtonSystemOption();
	afx_msg void OnBnClickedButtonSystemCoordinate();
	afx_msg void OnBnClickedBtnSystemSave();
	afx_msg void OnBnClickedButtonSystemEsc();
	afx_msg void OnBnClickedButtonSystemOption2();
};
