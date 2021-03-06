#pragma once

#define ALARM_LISTCTRL_MAX_COL 8
#define ALARM_LISTCTRL_MAX_ROW 100

// CVisionAgentECSErrorDlg 대화 상자입니다.

class CVisionAgentECSErrorDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVisionAgentECSErrorDlg)

public:
	CVisionAgentECSErrorDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CVisionAgentECSErrorDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VISION_AGENT_ECS_ERROR_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
public :
	//TSpread*		m_spread;
	CCommonListCtrl *m_pListCtrl;
	CString m_CurString;
	CStringArray	m_procsTexts;
	//void InitSpread();
	void InitListControlPara();
	void ChangeUI();
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedEcsErrorAllClearBtn();
	afx_msg void OnBnClickedEcsErrorClearBtn();
	int nSpreadRowSel;
	afx_msg void OnDestroy();
	afx_msg void OnNMClickListRecipeData(NMHDR *pNMHDR, LRESULT *pResult);
};
