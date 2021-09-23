#pragma once


// CVisionAgentECSDfsDlg 대화 상자입니다.

class CVisionAgentECSDfsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVisionAgentECSDfsDlg)

public:
	CVisionAgentECSDfsDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CVisionAgentECSDfsDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VISION_AGENT_ECS_DFS_DIALOG };
#endif

	CIPAddressCtrl	m_IpCtrlIpAddress;
	CEdit m_EdtiUserId;
	CEdit m_EdtiUserPw;
	CEdit	m_EditEqpId;
	CEdit	m_EditUnitId;
	CEdit	m_EditStepId;
	CEdit	m_EditProcessId;
	CEdit	m_EditFrameId;

	BOOL InitItem();

	BOOL ChangeUi();
	BOOL ChangeData();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnConnect();
	afx_msg void OnBnClickedBtnClose();
	afx_msg void OnBnClickedBtnFileUpload();
	afx_msg void OnBnClickedBtnFileDownload();
	afx_msg void OnBnClickedBtnNewFolder();
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedBtnDfsSave();
	
	afx_msg void OnBnClickedBtnGetDirInfo();
};
