#pragma once


// CManual_Sub_Clamp_Manual 대화 상자
enum
{
	_eMANUAL_INDEX_CLAMP_1_CLAMP_ON = 0,
	_eMANUAL_INDEX_CLAMP_2_CLAMP_ON,
	_eMANUAL_INDEX_CLAMP_3_CLAMP_ON,
	_eMANUAL_INDEX_CLAMP_4_CLAMP_ON,
	_eMANUAL_INDEX_CLAMP_5_CLAMP_ON,
#ifdef GRIPPER_8
	_eMANUAL_INDEX_CLAMP_6_CLAMP_ON,
	_eMANUAL_INDEX_CLAMP_7_CLAMP_ON,
	_eMANUAL_INDEX_CLAMP_8_CLAMP_ON,
#endif

	_eMANUAL_INDEX_CLAMP_1_CLAMP_OFF, 
	_eMANUAL_INDEX_CLAMP_2_CLAMP_OFF,
	_eMANUAL_INDEX_CLAMP_3_CLAMP_OFF,
	_eMANUAL_INDEX_CLAMP_4_CLAMP_OFF,
	_eMANUAL_INDEX_CLAMP_5_CLAMP_OFF,
#ifdef GRIPPER_8
	_eMANUAL_INDEX_CLAMP_6_CLAMP_OFF,
	_eMANUAL_INDEX_CLAMP_7_CLAMP_OFF,
	_eMANUAL_INDEX_CLAMP_8_CLAMP_OFF,
#endif

	_eMANUAL_INDEX_CLAMP_ACTIVE_CLAMP_ON,
	_eMANUAL_INDEX_CLAMP_ACTIVE_CLAMP_OFF,
	_eMANUAL_INDEX_CLAMP_ALL_CLAMP_ON,
	_eMANUAL_INDEX_CLAMP_ALL_CLAMP_OFF,

	_eMANUAL_INDEX_CLAMP_POS_MAX,
};

class CManual_Sub_Clamp_Manual : public CDialogEx
{
	DECLARE_DYNAMIC(CManual_Sub_Clamp_Manual)

public:
	CManual_Sub_Clamp_Manual(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CManual_Sub_Clamp_Manual();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_MANUAL_SUB_CLAMP_MANUAL };

#endif
	CColorStatic	m_stLamp_Work[_eMANUAL_INDEX_CLAMP_POS_MAX];
	int				m_nWork_State[_eMANUAL_INDEX_CLAMP_POS_MAX];
	bool			m_bWork_Lamp_State[_eMANUAL_INDEX_CLAMP_POS_MAX];
	double			m_dMotion_Strt_Tick[_eMANUAL_INDEX_CLAMP_POS_MAX];
	BOOL			m_bPrevStatus_InPos[_eMANUAL_INDEX_CLAMP_POS_MAX];
	BOOL			m_bMotionDone[_eMANUAL_INDEX_CLAMP_POS_MAX];

	CColorStatic	m_stcSet_L[eGRIPPER_ROW_MAX];
	CColorStatic	m_stcSet_R[eGRIPPER_ROW_MAX];
	CColorStatic	m_stcMeasure_L[eGRIPPER_ROW_MAX];
	CColorStatic	m_stcMeasure_R[eGRIPPER_ROW_MAX];

	void	InitCtrl();
	BOOL	Is_Comp_Usable();
	void	InitPara();
	void	CheckChangeData();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	afx_msg void OnBnClickedButtonManualSubClampManualClamp1On();
	afx_msg void OnBnClickedButtonManualSubClampManualClamp2On();
	afx_msg void OnBnClickedButtonManualSubClampManualClamp3On();
	afx_msg void OnBnClickedButtonManualSubClampManualClamp4On();
	afx_msg void OnBnClickedButtonManualSubClampManualClamp5On();
	afx_msg void OnBnClickedButtonManualSubClampManualClamp6On();
	afx_msg void OnBnClickedButtonManualSubClampManualClamp7On();
	afx_msg void OnBnClickedButtonManualSubClampManualClamp8On();
	afx_msg void OnBnClickedButtonManualSubClampManualClamp1Off();
	afx_msg void OnBnClickedButtonManualSubClampManualClamp2Off();
	afx_msg void OnBnClickedButtonManualSubClampManualClamp3Off();
	afx_msg void OnBnClickedButtonManualSubClampManualClamp4Off();
	afx_msg void OnBnClickedButtonManualSubClampManualClamp5Off();
	afx_msg void OnBnClickedButtonManualSubClampManualClamp6Off();
	afx_msg void OnBnClickedButtonManualSubClampManualClamp7Off();
	afx_msg void OnBnClickedButtonManualSubClampManualClamp8Off();
	afx_msg void OnBnClickedButtonManualSubClampManualActiveClampOn();
	afx_msg void OnBnClickedButtonManualSubClampManualAllClampOn();
	afx_msg void OnBnClickedButtonManualSubClampManualActiveClampOff();
	afx_msg void OnBnClickedButtonManualSubClampManualAllClampOff();
};
