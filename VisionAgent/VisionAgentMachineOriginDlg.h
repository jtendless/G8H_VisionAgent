#pragma once

#include "../Module/Control/ColorStatic.h"
#include "../Module/Control/ClrButton.h"
#include "../Module/Control/NumEdit.h"

// CVisionAgentMachineOriginDlg 대화 상자

enum en_MACHINE_ORIGIN_DEF
{
	MACHINE_ORIGIN_WORKSTAGE = 0,
	MACHINE_ORIGIN_GANTRY_Y,
	MACHINE_ORIGIN_GANTRY_Z,
	//
	MACHINE_ORIGIN_FRAME_UPDOWN,			// 합착이재기
	MACHINE_ORIGIN_STAGE_UVW,
	//
	MACHINE_ORIGIN_GLASS_POPUP_Z,
	MACHINE_ORIGIN_FRAME_GRIPPER_SSIDE,		// FRAME GRIPPER 단변
	MACHINE_ORIGIN_FRAME_GRIPPER_LSIDE,		// FRAME GRIPPER 장변
	//
	MACHINE_ORIGIN_GLASS_RELEASE_SSIDE,
	MACHINE_ORIGIN_GLASS_RELEASE_SMOVE,
	MACHINE_ORIGIN_GLASS_RELEASE_LSIDE,
	MACHINE_ORIGIN_GLASS_RELEASE_LMOVE,
	//
	MACHINE_ORIGIN_FRAME_TRANSFER_MOVE,
	MACHINE_ORIGIN_ROLLER_RELEASE_MOVE,
	MACHINE_ORIGIN_GLASS_RELEASE_LSIDE_R,	// 장변R
	MACHINE_ORIGIN_ROLLER_RELEASE,
	//
	MACHINE_ORIGIN_CLEANNING,
	MACHINE_ORIGIN_FRAME_TRANSFER_L,
	//
	MACHINE_ORIGIN_MAX,
};

class CVisionAgentMachineOriginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVisionAgentMachineOriginDlg)

public:
	CVisionAgentMachineOriginDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CVisionAgentMachineOriginDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VISION_AGENT_MACHINE_ORIGIN_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedMachineOriginInterlockCheck();
	afx_msg void OnBnClickedMachineOriginAllStopBtn();
	afx_msg void OnBnClickedMachineOriginAllServoOffBtn();

	bool m_bDialog_Entry;

	void InitCtrl();
	void InitPara();
	void BtnEnable(bool bEnable);

	//CMachineOriginState *pMachineOrigin;

	CColorStatic		m_stcAllOriginLed;
	CColorStatic		m_stcAllServoOnOffLed;
	CClrButton			m_btnAllServoOn;
	CClrButton			m_btnAllServoOff;
	CClrButton			m_btnAllOrgin;
	CJogMotion			*m_JogMotion;

	CComboBox			m_ComboAxis[MACHINE_ORIGIN_MAX];
	CClrButton			m_BtnServoOn[MACHINE_ORIGIN_MAX];
	CClrButton			m_BtnServoOff[MACHINE_ORIGIN_MAX];
	CClrButton			m_BtnOrgin[MACHINE_ORIGIN_MAX];
	CColorStatic		m_stcOriginLed[MACHINE_ORIGIN_MAX];
	CColorStatic		m_stcServoOnOffLed[MACHINE_ORIGIN_MAX];
	CColorStatic		m_stcOriginGroupLed[MACHINE_ORIGIN_MAX];

	CButton				m_CheckInterlock;

	BOOL GetAxisOriginParamByUI(en_MACHINE_ORIGIN_DEF eJogUIDefine, enum_Axis* peAxis, double* pPosAbs, double* pPosRel, double* pJogSpeed, double* pAccel, double* pDecel,  CString* strDiscription);

	BOOL GetAxisOriginGroupParam(en_MACHINE_ORIGIN_DEF eJogUIDefine);

	int	m_nAxisNo[AXIS_MAX];
	int m_nMoving;
	int m_nAllOriginIng;	
	int m_nUmacOriginIngStatus[2]; //KJT 20210320	
	int m_nRemoteAjinOriginIngStatus[MAX_AXIS_SIZE]; //KJT 20210320	
	int m_nDirectAjinOriginIngStatus[DIRECT_AXIS_MAX]; //KJT 20210320	
	afx_msg void OnBnClickedButtonMachineOriginAll();
	afx_msg void OnBnClickedButtonMachineServoOnAll();
	afx_msg void OnBnClickedButtonMachineOriginGantryY();
	afx_msg void OnBnClickedButtonMachineOriginGantryX();
	afx_msg void OnBnClickedButtonMachineOriginCameraZ();	
	afx_msg void OnBnClickedButtonMachineOriginLoadingStage();
	afx_msg void OnBnClickedButtonMachineOriginGripperClamp();
	afx_msg void OnBnClickedButtonMachineOriginGripperStretch();
	afx_msg void OnBnClickedButtonMachineOriginInspectionStage();
	afx_msg void OnBnClickedButtonMachineServoOnGantryY();
	afx_msg void OnBnClickedButtonMachineServoOnGantryX();
	afx_msg void OnBnClickedButtonMachineServoOnCameraZ();
	afx_msg void OnBnClickedButtonMachineServoOnBoxAlignCameraY();
	afx_msg void OnBnClickedButtonMachineServoOnLoadingStage();
	afx_msg void OnBnClickedButtonMachineServoOnGripperClamp();
	afx_msg void OnBnClickedButtonMachineServoOnGripperStretch();
	afx_msg void OnBnClickedButtonMachineServoOnInspectionStage();
	afx_msg void OnBnClickedButtonMachineServoOffGantryY();
	afx_msg void OnBnClickedButtonMachineServoOffGantryX();
	afx_msg void OnBnClickedButtonMachineServoOffCameraZ();
	afx_msg void OnBnClickedButtonMachineServoOffLoadingStage();
	afx_msg void OnBnClickedButtonMachineServoOffGripperClamp();
	afx_msg void OnBnClickedButtonMachineServoOffGripperStretch();
	afx_msg void OnBnClickedButtonMachineServoOffInspectionStage();
};
