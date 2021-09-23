#pragma once

#include "VisionAgentMachineOriginDlg.h"
#include "VisionAgentMachineJogDlg.h"
#include "VisionAgentMachineMotorDlg.h"

// CMachineDlg 대화 상자
enum
{
	MACHINE_ORIGIN_DLG = 0,
	MACHINE_JOG_DLG,
	MACHINE_MOTOR_DLG,

	MAX_MACHINE_DLG
};
enum 
{
	MACHINE_SUB_PAGE_1 = 0,
	MACHINE_SUB_PAGE_2,
	MACHINE_SUB_PAGE_3,
	MACHINE_SUB_PAGE_4,

	MAX_MACHINE_SUB_DLG
};

class CMachineDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMachineDlg)

public:
	CMachineDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CMachineDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VISION_AGENT_MACHINE_DIALOG };
#endif
	int m_nCurrentNo = 0;
	int m_nCurrentSubNo = 0;

	CButton m_btnMachine[MAX_MACHINE_DLG];
	CButton m_btnSubMachine[MAX_MACHINE_SUB_DLG];

	CColorStatic m_stcMachine_Dlg_Lamp[MAX_MACHINE_DLG];
	CColorStatic m_stcMachine_Sub_Dlg_Lamp[MAX_MACHINE_SUB_DLG];

	CVisionAgentMachineOriginDlg		*m_pMachineSubOriginDlg;
	CVisionAgentMachineJogDlg			*m_pMachineSubJogDlg;
	CVisionAgentMachineMotorDlg			*m_pMachineSubMotorDlg;

	void Dialog_Init();
	void ShowDlg(int nDlgNo, int nSubDlgNo);
	void Dlg_HideWindow();

	BOOL Is_Comp_Safe_Hwnd();
	BOOL RecalcLayout();
	BOOL ShowData();

	void ChangeUI();
	void CheckData();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	virtual void OnCancel();	
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL DestroyWindow();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnBnClickedButtonMachineMenuOrigin();
	afx_msg void OnBnClickedButtonMachineMenuJog();
	afx_msg void OnBnClickedButtonMachineMenuMotor();
	afx_msg void OnBnClickedButtonSub1();
	afx_msg void OnBnClickedButtonSub2();
	afx_msg void OnBnClickedButtonSub3();
	afx_msg void OnBnClickedButtonMachineSave();
	afx_msg void OnBnClickedButtonSub4();
};
