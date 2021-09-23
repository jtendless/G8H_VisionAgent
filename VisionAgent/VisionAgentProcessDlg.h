#pragma once

// CVisionAgentProcessDlg dialog

class CVisionAgentProcessDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVisionAgentProcessDlg)

public:
	CVisionAgentProcessDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CVisionAgentProcessDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VISION_AGENT_PROCESS_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	BOOL m_bShowFlag;

public:
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual BOOL DestroyWindow();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);

	BOOL InitCtrl();
	void RecalcLayout();
};
