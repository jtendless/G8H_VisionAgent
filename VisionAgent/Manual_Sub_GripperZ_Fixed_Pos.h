#pragma once


// CManual_Sub_GripperZ_Fixed_Pos dialog

class CManual_Sub_GripperZ_Fixed_Pos : public CDialogEx
{
	DECLARE_DYNAMIC(CManual_Sub_GripperZ_Fixed_Pos)

public:
	CManual_Sub_GripperZ_Fixed_Pos(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CManual_Sub_GripperZ_Fixed_Pos();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_MANUAL_SUB_GRIPPER_Z_FIXED_POS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	void	InitCtrl();
	BOOL	Is_Comp_Usable();
	void	InitPara();
	void	CheckChangeData();
	double	GetTargetPos(enum_Gripper_Z_Pos eGripperZPos);
	BOOL	ManualAbsMove(double dPos);
	BOOL	ManualAbsMoveZR(double dPos);
	enum_Axis GetAxisNo(CString *strDiscription);

	CColorStatic m_stcPos[eGRIPPER_Z_POS_MAX];
	CNumEdit m_editPos[eGRIPPER_Z_POS_MAX];
	double			m_dCmd_Pos[eGRIPPER_Z_POS_MAX];
	bool			m_bOn_Motion[eGRIPPER_Z_POS_MAX];
	afx_msg void OnBnClickedButtonManualSubGripperZFixedSave();
	afx_msg void OnBnClickedButtonManualSubGripperZGetWaitPos();
	afx_msg void OnBnClickedButtonManualSubGripperZGetUnclampPos();
	afx_msg void OnBnClickedButtonManualSubGripperZGetLoadingPos();
	afx_msg void OnBnClickedButtonManualSubGripperZGetClampPos();
	afx_msg void OnBnClickedButtonManualSubGripperZGetTensionPos();
	afx_msg void OnBnClickedButtonManualSubGripperZSetWaitPos();
	afx_msg void OnBnClickedButtonManualSubGripperZSetUnclampPos();
	afx_msg void OnBnClickedButtonManualSubGripperZSetLoadingPos();
	afx_msg void OnBnClickedButtonManualSubGripperZSetClampPos();
	afx_msg void OnBnClickedButtonManualSubGripperZSetTensionPos();
	afx_msg void OnBnClickedButtonManualSubGripperZMoveWaitPos();
	afx_msg void OnBnClickedButtonManualSubGripperZMoveUnclampPos();
	afx_msg void OnBnClickedButtonManualSubGripperZMoveLoadingPos();
	afx_msg void OnBnClickedButtonManualSubGripperZMoveClampPos();
	afx_msg void OnBnClickedButtonManualSubGripperZMoveTensionPos();
	afx_msg void OnBnClickedButtonManualSubGripperZGetWaitPos2();
	afx_msg void OnBnClickedButtonManualSubGripperZGetLoadingPos2();
	afx_msg void OnBnClickedButtonManualSubGripperZGetClampPos2();
	afx_msg void OnBnClickedButtonManualSubGripperZGetTensionPos2();
	afx_msg void OnBnClickedButtonManualSubGripperZGetUnclampPos2();
	afx_msg void OnBnClickedButtonManualSubGripperZSetWaitPos2();
	afx_msg void OnBnClickedButtonManualSubGripperZSetLoadingPos2();
	afx_msg void OnBnClickedButtonManualSubGripperZSetClampPos2();
	afx_msg void OnBnClickedButtonManualSubGripperZSetTensionPos2();
	afx_msg void OnBnClickedButtonManualSubGripperZSetUnclampPos2();
	afx_msg void OnBnClickedButtonManualSubGripperZMoveWaitPos2();
	afx_msg void OnBnClickedButtonManualSubGripperZMoveLoadingPos2();
	afx_msg void OnBnClickedButtonManualSubGripperZMoveClampPos2();
	afx_msg void OnBnClickedButtonManualSubGripperZMoveTensionPos2();
	afx_msg void OnBnClickedButtonManualSubGripperZMoveUnclampPos2();
};
