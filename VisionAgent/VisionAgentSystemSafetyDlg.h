#pragma once


// CVisionAgentSystemSafetyDlg ��ȭ �����Դϴ�.

class CVisionAgentSystemSafetyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVisionAgentSystemSafetyDlg)

public:
	CVisionAgentSystemSafetyDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CVisionAgentSystemSafetyDlg();

	void OnShowWindow(bool bShow, UINT nStatus);

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SYSTEM_SAFETY_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
