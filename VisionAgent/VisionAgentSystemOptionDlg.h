#pragma once


// CVisionAgentSystemOptionDlg ��ȭ �����Դϴ�.

class CVisionAgentSystemOptionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVisionAgentSystemOptionDlg)

public:
	CVisionAgentSystemOptionDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CVisionAgentSystemOptionDlg();

	void OnShowWindow(bool bShow, UINT nStatus);

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SYSTEM_OPTION_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
