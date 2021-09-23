#pragma once


// CAutoRunStartDlg dialog

class CAutoRunStartDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAutoRunStartDlg)

public:
	CAutoRunStartDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CAutoRunStartDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_AUTO_RUN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	virtual BOOL OnInitDialog();

public:
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	int m_nStartFlow;
	int m_nEndFlow;

	BOOL m_OKFlag;

	CComboBox m_comboStartFlow;
	CComboBox m_comboStep;
	CComboBox m_comboEndFlow;

	BOOL InitCtrl();
	BOOL InitPara();

	enum_AutoRunFlowName GetFlowNum(CString strFlowName);
	CString GetFlowName(int nFlow);

	afx_msg void OnBnClickedOk();
	afx_msg void OnCbnSelchangeComboAutoRunStartFlow();
	afx_msg void OnCbnSelchangeComboAutoRunEndFlow();
	afx_msg void OnBnClickedCancel();
};
