#pragma once

#define IDT_ALARM_BLINK   100
#define ALARM_LISTCTRL_MAX_COL 6
#define ALARM_LISTCTRL_MAX_ROW 100
// CVisionAgentAlarmDlg 대화 상자

//#include "ListCtrl/CommonListCtrl.h"

class CVisionAgentAlarmDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVisionAgentAlarmDlg)

public:
	CVisionAgentAlarmDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CVisionAgentAlarmDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VISION_AGENT_ALARM_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
protected:
	DWORD	 m_tick;
	CString	m_msg;
	UINT	m_nErrCode;

	CFont alarmfont;

	CCommonListCtrl *m_pListCtrl;

	void InitListControlPara();
	void UpdateUI();

public:
	BOOL SetAlarm(LPCTSTR Msg, UINT nErrCode = 0);
	void ShowAlarm(BOOL bVisible);
	void GetAlarmLevelDescription(UINT nErrCode, UINT*  uLevel, LPCTSTR* msg); //uLevel(0 == Light, 1 == Heavy)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedBtnAlarmClose();
	afx_msg void OnBnClickedBtnAlarmReset();
	afx_msg void OnDestroy();
};
