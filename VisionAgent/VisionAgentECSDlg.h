#pragma once


// CVisionAgentECSDlg 대화 상자입니다.
#include "VisionAgentECSMainDlg.h"
#include "VisionAgentECSJobManagementDlg.h"
#include "VisionAgentECSSheetDlg.h"
#include "VisionAgentECSErrorDlg.h"
#include "VisionAgentECSDfsDlg.h"
class CVisionAgentECSDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVisionAgentECSDlg)

public:
	CVisionAgentECSDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CVisionAgentECSDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VISION_AGENT_ECS_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public :
	CVisionAgentECSMainDlg *m_pMain;
	CVisionAgentECSJobManagementDlg *m_pJobManagement;
	CVisionAgentECSSheetDlg *m_pSheet;
	CVisionAgentECSErrorDlg	*m_pAlarm;
	CVisionAgentECSDfsDlg		*m_pDfs;
	CTabCtrl		m_tab1;
	void RecalcLayout();
	virtual BOOL OnInitDialog();
	afx_msg void	OnTcnSelChange(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
