#pragma once


// CManual_Sub_Gantry_Fixed_Pos 대화 상자

class CManual_Sub_Gantry_Fixed_Pos : public CDialogEx
{
	DECLARE_DYNAMIC(CManual_Sub_Gantry_Fixed_Pos)

public:
	CManual_Sub_Gantry_Fixed_Pos(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CManual_Sub_Gantry_Fixed_Pos();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_MANUAL_SUB_GANTRY_FIXED_POS };
#endif

	void	InitCtrl();
	BOOL	Is_Comp_Usable();
	void	InitPara();
	void	CheckChangeData();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	enum_Axis GetAxisNo(enum_Gantry_Axis eGantryAxis, CString *strDiscription);
	BOOL ManualAbsMove(enum_Gantry_Axis eGantryAxis, double dPos);
	double GetTargetPos(enum_Gantry_Pos eGantryPos);

	CColorStatic m_stcPos[_eGANTRY_POS_MAX];
	CNumEdit m_editPos[_eGANTRY_POS_MAX];
	double			m_dCmd_Pos[_eGANTRY_POS_MAX];
	bool			m_bOn_Motion[_eGANTRY_POS_MAX];

	afx_msg void OnBnClickedButtonGetWaitPosGantryX();
	afx_msg void OnBnClickedButtonGetWaitPosGantryY();
	afx_msg void OnBnClickedButtonGetStickLoadInBoxPosGantryY();
	afx_msg void OnBnClickedButtonGetUnloadPaperPosGantryY();
	afx_msg void OnBnClickedButtonGetStickUnloadToStagePosGantryY();
	afx_msg void OnBnClickedButtonGetStickLoadInStagePosGantryY();
	afx_msg void OnBnClickedButtonGetStickUnloadToBoxPosGantryY();
	afx_msg void OnBnClickedButtonGetWaitPosCameraZ1();	

	afx_msg void OnBnClickedButtonSetWaitPosGantryX();
	afx_msg void OnBnClickedButtonSetWaitPosGantryY();
	afx_msg void OnBnClickedButtonSetStickLoadInBoxPosGantryY();
	afx_msg void OnBnClickedButtonSetUnloadPaperPosGantryY();
	afx_msg void OnBnClickedButtonSetStickUnloadToStagePosGantryY();
	afx_msg void OnBnClickedButtonSetStickLoadInStagePosGantryY();
	afx_msg void OnBnClickedButtonSetStickUnloadToBoxPosGantryY();
	afx_msg void OnBnClickedButtonSetWaitPosCameraZ1();	

	afx_msg void OnBnClickedButtonMoveWaitPosGantryX();
	afx_msg void OnBnClickedButtonMoveWaitPosGantryY();
	afx_msg void OnBnClickedButtonMoveStickLoadInBoxPosGantryY();
	afx_msg void OnBnClickedButtonMoveUnloadPaperPosGantryY();
	afx_msg void OnBnClickedButtonMoveStickUnloadToStagePosGantryY();
	afx_msg void OnBnClickedButtonMoveStickLoadInStagePosGantryY();
	afx_msg void OnBnClickedButtonMoveStickUnloadToBoxPosGantryY();
	afx_msg void OnBnClickedButtonMoveWaitPosCameraZ1();	
	afx_msg void OnBnClickedButtonManualSubGantryFixedSave();
	afx_msg void OnBnClickedButtonGetPreAlignPosCameraZ1();
	afx_msg void OnBnClickedButtonSetPreAlignPosCameraZ1();	
	afx_msg void OnBnClickedButtonGetInspectionReviewPosCameraZ1();
	afx_msg void OnBnClickedButtonGetMappingReviewPosCameraZ1();
	afx_msg void OnBnClickedButtonSetInspectionReviewPosCameraZ1();
	afx_msg void OnBnClickedButtonSetMappingReviewPosCameraZ1();
	afx_msg void OnBnClickedButtonMoveInspectionReviewPosCameraZ1();
	afx_msg void OnBnClickedButtonMoveMappingReviewPosCameraZ1();
};
