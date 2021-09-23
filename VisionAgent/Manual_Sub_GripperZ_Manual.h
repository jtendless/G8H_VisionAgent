#pragma once

enum
{
	_eMANUAL_WORK_INDEX_GRIPPER_Z_WAIT_POS = 0,
	_eMANUAL_WORK_INDEX_GRIPPER_Z_LOADING_POS,
	_eMANUAL_WORK_INDEX_GRIPPER_Z_CLAMP_POS,
	_eMANUAL_WORK_INDEX_GRIPPER_Z_TENSTION_POS,
	_eMANUAL_WORK_INDEX_GRIPPER_Z_UNCLAMP_POS,

	_eMANUAL_WORK_INDEX_GRIPPER_RIGHT_Z_WAIT_POS,
	_eMANUAL_WORK_INDEX_GRIPPER_RIGHT_Z_LOADING_POS,
	_eMANUAL_WORK_INDEX_GRIPPER_RIGHT_Z_CLAMP_POS,
	_eMANUAL_WORK_INDEX_GRIPPER_RIGHT_Z_TENSTION_POS,
	_eMANUAL_WORK_INDEX_GRIPPER_RIGHT_Z_UNCLAMP_POS,
	_eMANUAL_WORK_INDEX_GRIPPER_Z_MAX,
};

// CManual_Sub_GripperZ_Manual dialog

class CManual_Sub_GripperZ_Manual : public CDialogEx
{
	DECLARE_DYNAMIC(CManual_Sub_GripperZ_Manual)

public:
	CManual_Sub_GripperZ_Manual(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CManual_Sub_GripperZ_Manual();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_MANUAL_SUB_GRIPPER_Z_MANUAL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
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

	CColorStatic m_stLamp_Work[_eMANUAL_WORK_INDEX_GRIPPER_Z_MAX];
	int				m_nWork_State[_eMANUAL_WORK_INDEX_GRIPPER_Z_MAX];
	bool			m_bWork_Lamp_State[_eMANUAL_WORK_INDEX_GRIPPER_Z_MAX];
	double			m_dMotion_Strt_Tick[_eMANUAL_WORK_INDEX_GRIPPER_Z_MAX];
	BOOL			m_bPrevStatus_InPos[_eMANUAL_WORK_INDEX_GRIPPER_Z_MAX];
	BOOL			m_bMotionDone[_eMANUAL_WORK_INDEX_GRIPPER_Z_MAX];

	afx_msg void OnBnClickedButtonManualSubGripperZManualWaitPos();
	afx_msg void OnBnClickedButtonManualSubGripperZManualLoadingPos();
	afx_msg void OnBnClickedButtonManualSubGripperZManualClampPos();
	afx_msg void OnBnClickedButtonManualSubGripperZManualTensionPos();
	afx_msg void OnBnClickedButtonManualSubGripperZManualUnclampPos();
	afx_msg void OnBnClickedButtonManualSubGripperZManualWaitPos2();
	afx_msg void OnBnClickedButtonManualSubGripperZManualLoadingPos2();
	afx_msg void OnBnClickedButtonManualSubGripperZManualClampPos3();
	afx_msg void OnBnClickedButtonManualSubGripperZManualTensionPos2();
	afx_msg void OnBnClickedButtonManualSubGripperZManualUnclampPos2();
};
