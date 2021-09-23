#pragma once

#include "Control/ClrButton.h"

// CManual_Sub_Clamp_Fixed_Pos 대화 상자
class CManual_Sub_Clamp_Fixed_Pos : public CDialogEx
{
	DECLARE_DYNAMIC(CManual_Sub_Clamp_Fixed_Pos)

public:
	CManual_Sub_Clamp_Fixed_Pos(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CManual_Sub_Clamp_Fixed_Pos();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_MANUAL_SUB_CLAMP_FIXED_POS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	BOOL	Is_Comp_Usable();
	void InitCtrl();
	void InitPara();
	void	CheckChangeData();

	CNumEdit m_editClampTorque;
	CColorStatic m_stcClampTorque;

	CClrButton m_btnSave;
	afx_msg void OnBnClickedButtonManualSubClampFixedSetTorque();
	afx_msg void OnBnClickedButtonManualSubClampFixedPosSave();
};
