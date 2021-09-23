#pragma once


// CVisionAgentSystem_ESCDlg 대화 상자

class CVisionAgentSystem_ESCDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVisionAgentSystem_ESCDlg)

public:
	CVisionAgentSystem_ESCDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CVisionAgentSystem_ESCDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SYSTEM_ESC_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	BOOL InitCtrl();
	BOOL InitPara();
	BOOL SavePara();
	BOOL CheckChangeData();
	CNumEdit m_EditVolt1;
	CNumEdit m_EditVolt2;
	CEdit m_EditReceiveData;

	CButton m_checkAutoDeleteDirPathUse[MAX_AUTO_DELETE_DIR_PATH];
	CNumEdit m_editFileStoreDay[MAX_AUTO_DELETE_DIR_PATH];

	CNumEdit m_editHighTemperature;
	CNumEdit m_editLowTemperature;
	CButton m_chkUseTemperatureCheck;
	CButton m_chkUseDoorOpenCheck;
	CButton m_chkUseAuto3DConnection;

	afx_msg void OnBnClickedButtonVoltSetting();
	afx_msg void OnBnClickedButtonSystemRemote();
	afx_msg void OnBnClickedButtonOutputOn();
	afx_msg void OnBnClickedButtonOutputOff();
	afx_msg void OnBnClickedButtonOutputCheck();
	afx_msg void OnBnClickedButtonVoltCheck();
	afx_msg void OnBnClickedButtonToggleOn();
	afx_msg void OnBnClickedButtonToggleOff();
	afx_msg void OnBnClickedButtonToggleCheck();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonToggleCheck2();
	afx_msg void OnBnClickedButtonToggleCheck3();
	afx_msg void OnBnClickedButtonToggleCheck4();
	afx_msg void OnBnClickedButtonToggleCheck5();
	afx_msg void OnBnClickedButtonToggleCheck6();
	afx_msg void OnBnClickedButtonToggleCheck7();
	afx_msg void OnBnClickedButtonToggleCheck8();
	afx_msg void OnBnClickedButtonToggleCheck9();
};
