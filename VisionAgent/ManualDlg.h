#pragma once

enum 
{
	MANUAL_GANTRY_DLG = 0,
	MANUAL_INSPECT_DLG,
	MANUAL_CLAMP_DLG,
	MANUAL_STRETCH_DLG,
	MANUAL_GRIPPER_Z_DLG,
	
	MAX_MANUAL_DLG
};
enum 
{
	MANUAL_SUB_MANUAL = 0,
	MANUAL_SUB_FIXED_POS,

	MAX_MANUAL_SUB_DLG
};
// CManualDlg 대화 상자입니다.
class CManual_Sub_Gantry_Manual;
class CManual_Sub_Gantry_Fixed_Pos;

class CManual_Sub_Clamp_Manual;
class CManual_Sub_Clamp_Fixed_Pos;

class CManual_Sub_Stretch_Manual;
class CManual_Sub_Stretch_Fixed_Pos;

class CManual_Sub_GripperZ_Manual;
class CManual_Sub_GripperZ_Fixed_Pos;


class CManualDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManualDlg)

public:
	CManualDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CManualDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VISION_AGENT_MANUAL_DIALOG };
#endif
protected:
	int m_nCurrentNo = 0;
	int m_nCurrentSubNo = 0;

private:
	CManual_Sub_Gantry_Manual		*m_pManual_Sub_Gantry_Manual;
	CManual_Sub_Gantry_Fixed_Pos	*m_pManual_Sub_Gantry_Fixed_Pos;

	CManual_Sub_Clamp_Manual		*m_pManual_Sub_Camp_Manual;
	CManual_Sub_Clamp_Fixed_Pos	*m_pManual_Sub_Clamp_Fixed_Pos;

	CManual_Sub_Stretch_Manual		*m_pManual_Sub_Stretch_Manual;
	CManual_Sub_Stretch_Fixed_Pos	*m_pManual_Sub_Stretch_Fixed_Pos;

	CManual_Sub_GripperZ_Manual	*m_pManual_Sub_GripperZ_Manual;
	CManual_Sub_GripperZ_Fixed_Pos	*m_pManual_Sub_GripperZ_Fixed_Pos;

	void Dialog_Init();
	void ShowDlg(int nDlgNo, int nSubDlgNo);
	void Dlg_HideWindow();

	CButton m_btnManual[MAX_MANUAL_DLG];
	CButton m_btnSubManual[MAX_MANUAL_SUB_DLG];
	
	CColorStatic m_stcManual_Dlg_Lamp[MAX_MANUAL_DLG];
	CColorStatic m_stcManual_Sub_Dlg_Lamp[MAX_MANUAL_SUB_DLG];

	INT m_nCurMainBtn;
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

	virtual BOOL DestroyWindow();
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButtonManualGantry();
	afx_msg void OnBnClickedButtonManualInspect();
	afx_msg void OnBnClickedButtonManualClamp();
	afx_msg void OnBnClickedButtonManualStretch();
	afx_msg void OnBnClickedButtonManualGripperZ();
	afx_msg void OnBnClickedButtonManual();
	afx_msg void OnBnClickedButtonFixedPos();
	afx_msg void OnBnClickedButtonClose();
};
