#pragma once


// CVisionAgentSafetyMap 대화 상자

class CVisionAgentSafetyMap : public CDialogEx
{
	DECLARE_DYNAMIC(CVisionAgentSafetyMap)

public:
	CVisionAgentSafetyMap(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CVisionAgentSafetyMap();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SAFETY_MAP };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bDoorStatus[4];
	BOOL m_bDoorDOStatus[4];
	BOOL m_bEMOStatus[4];
	CColorButton m_btn_Door[4];
	CColorButton m_btn_EMO[4];

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonDoor1();
	afx_msg void OnBnClickedButtonDoor2();
	afx_msg void OnBnClickedButtonDoor3();
	afx_msg void OnBnClickedButtonDoor4();
};
