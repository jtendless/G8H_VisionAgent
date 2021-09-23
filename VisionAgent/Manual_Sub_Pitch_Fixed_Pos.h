#pragma once

// CManual_Sub_Pitch_Fixed_Pos 대화 상자

class CManual_Sub_Pitch_Fixed_Pos : public CDialogEx
{
	DECLARE_DYNAMIC(CManual_Sub_Pitch_Fixed_Pos)

public:
	CManual_Sub_Pitch_Fixed_Pos(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CManual_Sub_Pitch_Fixed_Pos();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_MANUAL_SUB_PITCH_FIXED_POS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	CColorStatic m_stcPos_L[eGRIPPER_ROW_MAX];
	CColorStatic m_stcPos_R[eGRIPPER_ROW_MAX];
	CNumEdit m_editPos_L[eGRIPPER_ROW_MAX];
	CNumEdit m_editPos_R[eGRIPPER_ROW_MAX];

	void	InitCtrl();
	BOOL	Is_Comp_Usable();
	void	InitPara();
	void	CheckChangeData();

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonManualSubPitchFixedSave();
	afx_msg void OnBnClickedButtonManualSubPitchGetWaitPosPitchL(UINT id);
	afx_msg void OnBnClickedButtonManualSubPitchSetWaitPosPitchL(UINT id);
	afx_msg void OnBnClickedButtonManualSubPitchMoveWaitPosPitchL(UINT id);
	afx_msg void OnBnClickedButtonManualSubPitchGetWaitPosPitchR(UINT id);
	afx_msg void OnBnClickedButtonManualSubPitchSetWaitPosPitchR(UINT id);
	afx_msg void OnBnClickedButtonManualSubPitchMoveWaitPosPitchR(UINT id);
};
