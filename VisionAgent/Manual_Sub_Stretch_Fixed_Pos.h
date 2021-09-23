#pragma once

enum {
	_eSTRETCH_LEFT_1_WAIT_POS = 0,
	_eSTRETCH_LEFT_1_FWD_POS,
	_eSTRETCH_LEFT_1_BWD_POS,
	_eSTRETCH_LEFT_2_WAIT_POS,
	_eSTRETCH_LEFT_2_FWD_POS,
	_eSTRETCH_LEFT_2_BWD_POS,
	_eSTRETCH_LEFT_3_WAIT_POS,
	_eSTRETCH_LEFT_3_FWD_POS,
	_eSTRETCH_LEFT_3_BWD_POS,
	_eSTRETCH_RIGHT_1_WAIT_POS,
	_eSTRETCH_RIGHT_1_FWD_POS,
	_eSTRETCH_RIGHT_1_BWD_POS,
	_eSTRETCH_RIGHT_2_WAIT_POS,
	_eSTRETCH_RIGHT_2_FWD_POS,
	_eSTRETCH_RIGHT_2_BWD_POS,
	_eSTRETCH_RIGHT_3_WAIT_POS,
	_eSTRETCH_RIGHT_3_FWD_POS,
	_eSTRETCH_RIGHT_3_BWD_POS,

	_eSTRETCH_POS_MAX,
};
// CManual_Sub_Stretch_Fixed_Pos 대화 상자

class CManual_Sub_Stretch_Fixed_Pos : public CDialogEx
{
	DECLARE_DYNAMIC(CManual_Sub_Stretch_Fixed_Pos)

public:
	CManual_Sub_Stretch_Fixed_Pos(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CManual_Sub_Stretch_Fixed_Pos();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_MANUAL_SUB_STRETCH_FIXED_POS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	CColorStatic m_stcPos[_eSTRETCH_POS_MAX];
	CNumEdit m_editPos[_eSTRETCH_POS_MAX];
	double			m_dCmd_Pos[_eSTRETCH_POS_MAX];
	bool			m_bOn_Motion[_eSTRETCH_POS_MAX];

	void	InitCtrl();
	BOOL	Is_Comp_Usable();
	void	InitPara();
	void	CheckChangeData();

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedButtonManualSubStretchFixedSave();
	afx_msg void OnBnClickedButtonManualSubStretchGetWaitPosStretchLeft();
	afx_msg void OnBnClickedButtonManualSubStretchGetForwardPosStretchLeft();
	afx_msg void OnBnClickedButtonManualSubStretchGetBackwardPosStretchLeft();
	afx_msg void OnBnClickedButtonManualSubStretchGetWaitPosStretchRight();
	afx_msg void OnBnClickedButtonManualSubStretchGetForwardPosStretchRight();
	afx_msg void OnBnClickedButtonManualSubStretchGetBackwardPosStretchRight();
	afx_msg void OnBnClickedButtonManualSubStretchSetWaitPosStretchLeft();
	afx_msg void OnBnClickedButtonManualSubStretchSetForwardPosStretchLeft();
	afx_msg void OnBnClickedButtonManualSubStretchSetBackwardPosStretchLeft();
	afx_msg void OnBnClickedButtonManualSubStretchSetWaitPosStretchRight();
	afx_msg void OnBnClickedButtonManualSubStretchSetForwardPosStretchRight();
	afx_msg void OnBnClickedButtonManualSubStretchSetBackwardPosStretchRight();
	afx_msg void OnBnClickedButtonManualSubStretchMoveWaitPosStretchLeft();
	afx_msg void OnBnClickedButtonManualSubStretchMoveForwardPosStretchLeft();
	afx_msg void OnBnClickedButtonManualSubStretchMoveBackwardPosStretchLeft();
	afx_msg void OnBnClickedButtonManualSubStretchMoveWaitPosStretchRight();
	afx_msg void OnBnClickedButtonManualSubStretchMoveForwardPosStretchRight();
	afx_msg void OnBnClickedButtonManualSubStretchMoveBackwardPosStretchRight();
	afx_msg void OnBnClickedButtonManualSubStretchGetWaitPosStretchLeft2();
	afx_msg void OnBnClickedButtonManualSubStretchGetForwardPosStretchLeft2();
	afx_msg void OnBnClickedButtonManualSubStretchGetBackwardPosStretchLeft2();
	afx_msg void OnBnClickedButtonManualSubStretchGetWaitPosStretchLeft3();
	afx_msg void OnBnClickedButtonManualSubStretchGetForwardPosStretchLeft3();
	afx_msg void OnBnClickedButtonManualSubStretchGetBackwardPosStretchLeft3();
	afx_msg void OnBnClickedButtonManualSubStretchGetWaitPosStretchRight2();
	afx_msg void OnBnClickedButtonManualSubStretchGetForwardPosStretchRight2();
	afx_msg void OnBnClickedButtonManualSubStretchGetBackwardPosStretchRight2();
	afx_msg void OnBnClickedButtonManualSubStretchGetWaitPosStretchRight3();
	afx_msg void OnBnClickedButtonManualSubStretchGetForwardPosStretchRight3();
	afx_msg void OnBnClickedButtonManualSubStretchGetBackwardPosStretchRight3();
	afx_msg void OnBnClickedButtonManualSubStretchSetWaitPosStretchLeft2();
	afx_msg void OnBnClickedButtonManualSubStretchSetForwardPosStretchLeft2();
	afx_msg void OnBnClickedButtonManualSubStretchSetBackwardPosStretchLeft2();
	afx_msg void OnBnClickedButtonManualSubStretchSetWaitPosStretchLeft3();
	afx_msg void OnBnClickedButtonManualSubStretchSetForwardPosStretchLeft3();
	afx_msg void OnBnClickedButtonManualSubStretchSetBackwardPosStretchLeft3();
	afx_msg void OnBnClickedButtonManualSubStretchSetWaitPosStretchRight2();
	afx_msg void OnBnClickedButtonManualSubStretchSetForwardPosStretchRight2();
	afx_msg void OnBnClickedButtonManualSubStretchSetBackwardPosStretchRight2();
	afx_msg void OnBnClickedButtonManualSubStretchSetWaitPosStretchRight3();
	afx_msg void OnBnClickedButtonManualSubStretchSetForwardPosStretchRight3();
	afx_msg void OnBnClickedButtonManualSubStretchSetBackwardPosStretchRight3();
	afx_msg void OnBnClickedButtonManualSubStretchMoveWaitPosStretchLeft2();
	afx_msg void OnBnClickedButtonManualSubStretchMoveForwardPosStretchLeft2();
	afx_msg void OnBnClickedButtonManualSubStretchMoveBackwardPosStretchLeft2();
	afx_msg void OnBnClickedButtonManualSubStretchMoveWaitPosStretchLeft3();
	afx_msg void OnBnClickedButtonManualSubStretchMoveForwardPosStretchLeft3();
	afx_msg void OnBnClickedButtonManualSubStretchMoveBackwardPosStretchLeft3();
	afx_msg void OnBnClickedButtonManualSubStretchMoveWaitPosStretchRight2();
	afx_msg void OnBnClickedButtonManualSubStretchMoveForwardPosStretchRight2();
	afx_msg void OnBnClickedButtonManualSubStretchMoveBackwardPosStretchRight2();
	afx_msg void OnBnClickedButtonManualSubStretchMoveWaitPosStretchRight3();
	afx_msg void OnBnClickedButtonManualSubStretchMoveForwardPosStretchRight3();
	afx_msg void OnBnClickedButtonManualSubStretchMoveBackwardPosStretchRight3();
};
