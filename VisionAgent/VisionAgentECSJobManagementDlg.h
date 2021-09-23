#pragma once
#include "ListCtrl/CommonListCtrl.h"

#define ECS_JOB_MANAGEMENT_LIST_MAX_COL 3
#define ECS_JOB_MANAGEMENT_LIST_MAX_RAW 47
// CVisionAgentECSJobManagementDlg 대화 상자입니다.

class CVisionAgentECSJobManagementDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVisionAgentECSJobManagementDlg)

public:
	CVisionAgentECSJobManagementDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CVisionAgentECSJobManagementDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VISION_AGENT_ECS_JOB_MANAGEMENT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
#if 1
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
#endif
public :
	CEdit	 m_JobCodeLotSeqEdit;
	CEdit	 m_JobCodeSlotSeqEdit;
	CEdit	 m_JobIDEdit;
	CButton	 m_GlassRadio;

	char* ConvertPlcString(CString strData);
	//TSpread*		m_Cimspread;
	//TSpread*		m_Stagespread;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
	CCommonListCtrl *m_pCimListCtrl;
	CCommonListCtrl *m_pStageListCtrl;
	CString m_CurString;
	CStringArray	m_procsTexts;
#if 1
	void InitSpreadContent();
	void InitListControlPara();
	void SetCimJobDataToListCtrl(CCommonListCtrl*	Spread, MASK_JOB_DATA JobData);
	void GetJobDataFromSpread(CCommonListCtrl*	Spread, PMASK_JOB_DATA JobData);
	//void GetSpread(TSpread*	Spread, PMATERIAL_DATA_B JobData);
	
	afx_msg void OnBnClickedEcsJobDataRequestBtn();
	afx_msg void OnBnClickedEcsJobDataSendOutBtn();
	afx_msg void OnBnClickedEcsJobDataFetchedOutBtn();
	afx_msg void OnBnClickedEcsJobDataChangeBtn();
	afx_msg void OnBnClickedEcsJobDataStoredBtn();
	afx_msg void OnBnClickedEcsProcessStartBtn();
	afx_msg void OnBnClickedEcsProcessEndBtn();
	afx_msg void OnBnClickedEcsJobJudgeReportBtn();
	afx_msg void OnBnClickedEcsProcessDataReportBtn();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedBtnSaveEcsJobData();
#endif

	afx_msg void OnBnClickedEcsJobDataReceiveBtn();
};
