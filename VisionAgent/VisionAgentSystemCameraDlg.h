#pragma once


// CVisionAgentSystemCameraDlg ��ȭ �����Դϴ�.

class CVisionAgentSystemCameraDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVisionAgentSystemCameraDlg)

public:
	CVisionAgentSystemCameraDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CVisionAgentSystemCameraDlg();


	void OnShowWindow(bool bShow, UINT nStatus);

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SYSTEM_CAMERA_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
