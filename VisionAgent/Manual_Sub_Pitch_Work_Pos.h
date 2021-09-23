#pragma once

enum {
	_eMANUAL_WORK_PITCH_LEFT = 0,
	_eMANUAL_WORK_PITCH_RIGHT,

	_eMANUAL_WORK_PITCH_MAX
};
// CManual_Sub_Pitch_Work_Pos 대화 상자

class CManual_Sub_Pitch_Work_Pos : public CDialogEx
{
	DECLARE_DYNAMIC(CManual_Sub_Pitch_Work_Pos)

public:
	CManual_Sub_Pitch_Work_Pos(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CManual_Sub_Pitch_Work_Pos();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_MANUAL_SUB_PITCH_WORK_POS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	enum_Axis	m_eAxisID;
	bool		m_bIs_Motor_Run[_eMANUAL_WORK_PITCH_MAX];

	void	Init_Title_Set();
	BOOL	Is_Comp_Usable();
	void	ChangeUI();
	void	ChangeData();

	CComboBox m_cbxSpeed_PitchLeft;
	CComboBox m_cbxSpeed_PitchRight;

	CComboBox m_cbxStep_PitchLeft;
	CComboBox m_cbxStep_PitchRight;

	CButton m_chbSpeed_PitchLeft;
	CButton m_chbSpeed_PitchRight;

	CButton m_chbStep_PitchLeft;
	CButton m_chbStep_PitchRight;
};
