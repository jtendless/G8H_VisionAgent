#pragma once

enum
{
	_eMANUAL_INDEX_PITCH_WAIT_POS = 0,
	_eMANUAL_INDEX_PITCH_WORK_POS,

	_eMANUAL_INDEX_PITCH_POS_MAX,
};
// CManual_Sub_Pitch_Manual 대화 상자

class CManual_Sub_Pitch_Manual : public CDialogEx
{
	DECLARE_DYNAMIC(CManual_Sub_Pitch_Manual)

public:
	CManual_Sub_Pitch_Manual(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CManual_Sub_Pitch_Manual();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_MANUAL_SUB_PITCH_MANUAL };
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

	CColorStatic	m_stLamp_Work[_eMANUAL_INDEX_PITCH_POS_MAX];
	int				m_nWork_State[_eMANUAL_INDEX_PITCH_POS_MAX];
	bool			m_bWork_Lamp_State[_eMANUAL_INDEX_PITCH_POS_MAX];
	double			m_dMotion_Strt_Tick[_eMANUAL_INDEX_PITCH_POS_MAX];
	BOOL			m_bPrevStatus_InPos[_eMANUAL_INDEX_PITCH_POS_MAX];
	BOOL			m_bMotionDone[_eMANUAL_INDEX_PITCH_POS_MAX];

	double dWorkPos_L[eGRIPPER_ROW_MAX] = { 0.0, };
	double dWorkPos_R[eGRIPPER_ROW_MAX] = { 0.0, };

	afx_msg void OnBnClickedButtonManualSubPitchManualWorkPos();
	afx_msg void OnBnClickedButtonManualSubPitchManualWaitPos();
};
