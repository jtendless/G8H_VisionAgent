#pragma once


// CSystemMachineCommunicationSubDlg 대화 상자

class CSystemMachineCommunicationSubDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSystemMachineCommunicationSubDlg)

public:
	CSystemMachineCommunicationSubDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSystemMachineCommunicationSubDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_SYSTEM_SUB_MACHINE_COMMUNICATION_PAGE_1 };
#endif
		   
	void ChangeUI();
	void ChangeData();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	
	CStatic m_stNaming_Gantry_Flash_Port;
	CComboBox m_cbxGantry_Flash_Port;
	CStatic m_stNaming_Mask_Flash_Port;
	CComboBox m_cbxMask_Flash_Port;
	CStatic m_stNaming_Back_Light_Port;
	CComboBox m_cbxBack_Light_Port;
	CStatic m_stNaming_Laser_Dist_Port;
	CComboBox m_cbxLaser_Dist_Port;
	CStatic m_stNaming_BCR_IP;
	CEdit m_edtBCR_IP;
	CStatic m_stNaming_BCR_Port;
	CEdit m_edtBCR_Port;
	CButton m_btnSave;

	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
