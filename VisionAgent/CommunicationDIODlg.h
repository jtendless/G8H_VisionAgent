#pragma once


// CCommunicationDIODlg 대화 상자
class CBaseMotion;
class CCommunicationDIODlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCommunicationDIODlg)

public:
	CCommunicationDIODlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CCommunicationDIODlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_COMMUNICATION_DIO };
#endif

	CBaseMotion		*m_pBaseMotion;
	CColorStatic	m_ledDI[DIO_MODULE_SIZE];
	CColorStatic	m_ledDO[DIO_MODULE_SIZE];
	CStatic			m_staticDI[DIO_MODULE_SIZE];
	CButton			m_btnDO[DIO_MODULE_SIZE];

	CString m_strDI_Label[DIO_MODULE_SIZE * DI_MODULE_CNT];
	CString m_strDO_Label[DIO_MODULE_SIZE * DO_MODULE_CNT];

	int m_nCardNoDI;
	int m_nCardNoDO;

	BOOL Is_Comp_Safe_Hwnd();
	void InitDlg();
	void InitDiLabel();
	void InitDoLabel();
	void SetDo(UINT nNum, BOOL bOnOff);
	void ChangeUI();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedCommunicationDiPreviousBtn();
	afx_msg void OnBnClickedCommunicationDiNextBtn();
	afx_msg void OnBnClickedCommunicationDoPreviousBtn();
	afx_msg void OnBnClickedCommunicationDoNextBtn();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedCommunicationDoBtn1();
	afx_msg void OnBnClickedCommunicationDoBtn2();
	afx_msg void OnBnClickedCommunicationDoBtn3();
	afx_msg void OnBnClickedCommunicationDoBtn4();
	afx_msg void OnBnClickedCommunicationDoBtn5();
	afx_msg void OnBnClickedCommunicationDoBtn6();
	afx_msg void OnBnClickedCommunicationDoBtn7();
	afx_msg void OnBnClickedCommunicationDoBtn8();
	afx_msg void OnBnClickedCommunicationDoBtn9();
	afx_msg void OnBnClickedCommunicationDoBtn10();
	afx_msg void OnBnClickedCommunicationDoBtn11();
	afx_msg void OnBnClickedCommunicationDoBtn12();
	afx_msg void OnBnClickedCommunicationDoBtn13();
	afx_msg void OnBnClickedCommunicationDoBtn14();
	afx_msg void OnBnClickedCommunicationDoBtn15();
	afx_msg void OnBnClickedCommunicationDoBtn16();
	afx_msg void OnBnClickedCommunicationDoBtn17();
	afx_msg void OnBnClickedCommunicationDoBtn18();
	afx_msg void OnBnClickedCommunicationDoBtn19();
	afx_msg void OnBnClickedCommunicationDoBtn20();
	afx_msg void OnBnClickedCommunicationDoBtn21();
	afx_msg void OnBnClickedCommunicationDoBtn22();
	afx_msg void OnBnClickedCommunicationDoBtn23();
	afx_msg void OnBnClickedCommunicationDoBtn24();
	afx_msg void OnBnClickedCommunicationDoBtn25();
	afx_msg void OnBnClickedCommunicationDoBtn26();
	afx_msg void OnBnClickedCommunicationDoBtn27();
	afx_msg void OnBnClickedCommunicationDoBtn28();
	afx_msg void OnBnClickedCommunicationDoBtn29();
	afx_msg void OnBnClickedCommunicationDoBtn30();
	afx_msg void OnBnClickedCommunicationDoBtn31();
	afx_msg void OnBnClickedCommunicationDoBtn32();
	
};
