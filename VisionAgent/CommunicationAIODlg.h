#pragma once


// CCommunicationAIODlg 대화 상자

class CCommunicationAIODlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCommunicationAIODlg)

public:
	CCommunicationAIODlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CCommunicationAIODlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_COMMUNICATION_AIO };
#endif
	int					m_nAi[AI_MODULE_SIZE];
	
	CColorStatic		m_staticAiNo[AI_MODULE_SIZE];
	CColorStatic		m_staticAiName[AI_MODULE_SIZE];
	CColorStatic		m_staticDataAiData[AI_MODULE_SIZE];

	CString m_strAiLabel[AI_MODULE_SIZE * AI_MODULE_CNT];

	int m_nCardNoAI;

	void	InitDlg();
	void	InitAiLabel();
	void	ChangeUI();
	BOOL	Is_Comp_Safe_Hwnd();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedCommunicationAiPreviousBtn();
	afx_msg void OnBnClickedCommunicationAiNextBtn();
};
