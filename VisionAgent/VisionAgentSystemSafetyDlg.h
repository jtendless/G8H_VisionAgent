#pragma once


// CVisionAgentSystemSafetyDlg 대화 상자입니다.

class CVisionAgentSystemSafetyDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVisionAgentSystemSafetyDlg)

public:
	CVisionAgentSystemSafetyDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CVisionAgentSystemSafetyDlg();

	void OnShowWindow(bool bShow, UINT nStatus);

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SYSTEM_SAFETY_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
