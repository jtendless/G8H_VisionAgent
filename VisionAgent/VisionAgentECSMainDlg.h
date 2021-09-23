#pragma once

#include "CIM/CimModule.h"

// CVisionAgentECSMainDlg 대화 상자입니다.

class CVisionAgentECSMainDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVisionAgentECSMainDlg)

public:
	CVisionAgentECSMainDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CVisionAgentECSMainDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VISION_AGENT_ECS_MAIN_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	void RecalcLayout();
	CCimModule *pCimModule;

	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCimModeOnBtn();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	BOOL InitPara();

	CComboBox m_ErrorCodeCombo;

	CEdit	m_CimMessageID[5];
	CEdit	m_CimMessageDate[5];
	CEdit	m_CimMessage[5];
	CEdit	 m_ErrorMessage;
	CEdit	 m_ErrorID;	
	CEdit	 m_ProductJobCount;
	CEdit	 m_DummyJobCount;

	
	CClrButton m_BtnCimOn;
	CClrButton m_BtnCimOff;
	CClrButton m_BtnCimPCOn;
	CClrButton m_BtnCimPCOff;
	CClrButton m_BtnCimStatus;
	CClrButton m_BtnAutoRecipeOn;
	CClrButton m_BtnAutoRecipeOff;


	CClrButton m_BtnUpstreamInlineOn;
	CClrButton m_BtnUpstreamInlineOff;
	CClrButton m_BtnDownstreamInlineOn;
	CClrButton m_BtnDownstreamInlineOff;
	
	CClrButton m_BtnRun;
	CClrButton m_BtnIdle;
	CClrButton m_BtnPause;
	CClrButton m_BtnPM;
	CClrButton m_BtnBM;
	int m_nPrevMachineState;


	CClrButton m_BtnCassetteVCROn;
	CClrButton m_BtnCassetteVCROff;
	CClrButton m_BtnCassetteVCRNomal;
	CClrButton m_BtnCassetteVCRKeyIn;
	CClrButton m_BtnCassetteVCRSkip;

	
	CClrButton m_BtnCimPCCommand[8];
	CClrButton m_BtnCimPCCommandReply[8];
	CClrButton m_BtnMachineEvent[25];
	CClrButton m_BtnMachineEventReply[25];

#if 0

	CClrButton m_BtnFrameVCROn;
	CClrButton m_BtnFrameVCROff;
	CClrButton m_BtnFrameVCRKeyIn;
	CClrButton m_BtnFrameVCRSkip;
	CClrButton m_BtnFrameVCRNomal;

	CClrButton m_BtnMaskVCROn;
	CClrButton m_BtnMaskVCROff;
	CClrButton m_BtnMaskVCRKeyIn;
	CClrButton m_BtnMaskVCRSkip;
	CClrButton m_BtnMaskVCRNomal;
#endif
	CClrButton m_BtnOperatorCall;

	BOOL OperatorCallFlag;
	afx_msg void OnBnClickedMachineManagementRunBtn();
	afx_msg void OnBnClickedMachineManagementIdleBtn();
	afx_msg void OnBnClickedMachineManagementPauseBtn();
	afx_msg void OnBnClickedMachineManagementPmBtn();
	afx_msg void OnBnClickedMachineManagementBmBtn();
	afx_msg void OnBnClickedTimeoutManagementSetBtn();
	afx_msg void OnBnClickedCimMessageConfirmBtn1();
	afx_msg void OnBnClickedCimMessageConfirmBtn2();
	afx_msg void OnBnClickedCimMessageConfirmBtn3();
	afx_msg void OnBnClickedCimMessageConfirmBtn4();
	afx_msg void OnBnClickedCimMessageConfirmBtn5();
	afx_msg void OnBnClickedAlarmManagementErrorSetBtn();
//	afx_msg void OnBnClickedJobManagementRequestBtn();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedUpstreamInlineOnBtn();
	afx_msg void OnBnClickedUpstreamInlineOffBtn();
	afx_msg void OnBnClickedDownstreamInlineOnBtn();
	afx_msg void OnBnClickedDownstreamInlineOffBtn();
	afx_msg void OnBnClickedAutoRecipeOnBtn();
	afx_msg void OnBnClickedAutoRecipeOffBtn();
	afx_msg void OnBnClickedAlarmManagementWarningSetBtn();
	afx_msg void OnBnClickedAlarmManagementResetBtn();
	afx_msg void OnBnClickedCimModeOffBtn();
	afx_msg void OnBnClickedOperatorCallBtn();
	afx_msg void OnBnClickedAutoCassetteVcrOnBtn();
	afx_msg void OnBnClickedAutoCassetteVcrOffBtn();
	afx_msg void OnBnClickedAutoCassetteVcrKeyInBtn();
	afx_msg void OnBnClickedAutoCassetteVcrSkipBtn();
	afx_msg void OnBnClickedCIMPCCommandReplyBtn(UINT id);
	afx_msg void OnBnClickedMachineEventBtn(UINT id);
	afx_msg void OnBnClickedBtnModuleWindowOpen();
	afx_msg void OnBnClickedBtnJobPlus();
	afx_msg void OnBnClickedBtnJobMinus();
	afx_msg void OnBnClickedMachineManagementIdleBtn2();
	afx_msg void OnBnClickedMachineManagementIdleBtn3();
};
