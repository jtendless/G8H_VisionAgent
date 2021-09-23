#pragma once

enum
{
	_eMANUAL_WORK_INDEX_STRETCH_ACTIVE_WAIT_POS = 0,
	_eMANUAL_WORK_INDEX_STRETCH_ACTIVE_FWD_POS,
	_eMANUAL_WORK_INDEX_STRETCH_ACTIVE_BWD_POS,

	_eMANUAL_WORK_INDEX_STRETCH_ALL_WAIT_POS,
	_eMANUAL_WORK_INDEX_STRETCH_ALL_FWD_POS,
	_eMANUAL_WORK_INDEX_STRETCH_ALL_BWD_POS,

	_eMANUAL_WORK_INDEX_STRETCH_POS_MAX,
};
// CManual_Sub_Stretch_Manual 대화 상자

class CManual_Sub_Stretch_Manual : public CDialogEx
{
	DECLARE_DYNAMIC(CManual_Sub_Stretch_Manual)

public:
	CManual_Sub_Stretch_Manual(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CManual_Sub_Stretch_Manual();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_MANUAL_SUB_STRETCH_MANUAL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	void	InitCtrl();
	BOOL	Is_Comp_Usable();
	void	InitPara();
	void	CheckChangeData();

	CColorStatic	m_stLamp_Work[_eMANUAL_WORK_INDEX_STRETCH_POS_MAX];
	int				m_nWork_State[_eMANUAL_WORK_INDEX_STRETCH_POS_MAX];
	bool			m_bWork_Lamp_State[_eMANUAL_WORK_INDEX_STRETCH_POS_MAX];
	double			m_dMotion_Strt_Tick[_eMANUAL_WORK_INDEX_STRETCH_POS_MAX];
	BOOL			m_bPrevStatus_InPos[_eMANUAL_WORK_INDEX_STRETCH_POS_MAX];
	BOOL			m_bMotionDone[_eMANUAL_WORK_INDEX_STRETCH_POS_MAX];

	CColorStatic	m_stcSet_L[eGRIPPER_ROW_MAX];
	CColorStatic	m_stcSet_R[eGRIPPER_ROW_MAX];
	CColorStatic	m_stcMeasure_L[eGRIPPER_ROW_MAX];
	CColorStatic	m_stcMeasure_R[eGRIPPER_ROW_MAX];
	CColorStatic	m_stcStatus_L[eGRIPPER_ROW_MAX];
	CColorStatic	m_stcStatus_R[eGRIPPER_ROW_MAX];
	//21.03.06 sjc
	CColorStatic	m_stLeft_Clamp_On[eGRIPPER_ROW_MAX];
	CColorStatic	m_stRight_Clamp_On[eGRIPPER_ROW_MAX];
	BOOL	SetDOutputBitValue(enum_Do eBit, int nValue);
	CColorStatic	m_stLeft_Clamp_Off[eGRIPPER_ROW_MAX];
	CColorStatic	m_stRight_Clamp_Off[eGRIPPER_ROW_MAX];

	CButton			m_chkLeft_ClampOn[eGRIPPER_ROW_MAX];
	CButton			m_chkRight_ClampOn[eGRIPPER_ROW_MAX];
	CButton			m_chkLeft_ClampOff[eGRIPPER_ROW_MAX];
	CButton			m_chkRight_ClampOff[eGRIPPER_ROW_MAX];

	int m_nStretchSetZeroCh;
	int m_nStretchSetZeroCnt;
	double m_nStretchSetZeroChTick;
	double m_nStretchSetZeroCntTick;

	afx_msg void OnBnClickedButtonManualSubGripperManualActiveWaitPos();
	afx_msg void OnBnClickedButtonManualSubGripperManualActiveFwdPos();
	afx_msg void OnBnClickedButtonManualSubGripperManualActiveBwdPos();
	afx_msg void OnBnClickedButtonManualSubGripperManualAllWaitPos();
	afx_msg void OnBnClickedButtonManualSubGripperManualAllFwdPos();
	afx_msg void OnBnClickedButtonManualSubGripperManualAllBwdPos();
	afx_msg void OnBnClickedButtonManualSubGripperManualStretchStart();
	afx_msg void OnBnClickedButtonManualSubGripperManualStretchStop();
	afx_msg void OnBnClickedButtonManualSubGripperManualStretchForceZero();
	afx_msg void OnBnClickedButtonManualSubGripperManualReleaseStart();
	afx_msg void OnBnClickedButtonManualSubGripperManualClampOnL1();
	afx_msg void OnBnClickedButtonManualSubGripperManualClampOnL2();
	afx_msg void OnBnClickedButtonManualSubGripperManualClampOnL3();
	afx_msg void OnBnClickedButtonManualSubGripperManualClampOnR1();
	afx_msg void OnBnClickedButtonManualSubGripperManualClampOnR2();
	afx_msg void OnBnClickedButtonManualSubGripperManualClampOnR3();
	afx_msg void OnBnClickedButtonManualSubGripperManualClampOffL1();
	afx_msg void OnBnClickedButtonManualSubGripperManualClampOffL2();
	afx_msg void OnBnClickedButtonManualSubGripperManualClampOffL3();
	afx_msg void OnBnClickedButtonManualSubGripperManualClampOffR1();
	afx_msg void OnBnClickedButtonManualSubGripperManualClampOffR2();
	afx_msg void OnBnClickedButtonManualSubGripperManualClampOffR3();
	afx_msg void OnBnClickedButtonManualSubGripperManualClampOnAll();
	afx_msg void OnBnClickedButtonManualSubGripperManualClampOffAll();
};
