#pragma once


// CManualStageSubDlg 대화 상자입니다.


class CManualStageSubDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManualStageSubDlg)

public:
	CManualStageSubDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CManualStageSubDlg();

	bool m_bDialog_Entry;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_MANUAL_SUB_STAGE };
#endif
	


	CEdit m_Edit_StagePanelPosX1, m_Edit_StagePanelPosY1;
	CEdit m_Edit_StagePanelPosX2, m_Edit_StagePanelPosY2;

	CEdit m_Edit_StageWritePanelPosX1, m_Edit_StageWritePanelPosY1;
	CEdit m_Edit_StageWritePanelPosX2, m_Edit_StageWritePanelPosY2;


	
	CColorStatic m_stcIsAlignStanby;

	CColorStatic m_stcIsPanelAlignRunCmd;
	
	CColorStatic m_stcIsPanelAlignMoveDone;
	
	CColorStatic m_stcIsPanelAlignResetCmd;
	
	CColorStatic m_stcIsPanelAlignProcessing;
	
	CColorStatic m_stcIsPanelAlignDone;


	CColorStatic m_stcIsBeemAxisRoateReply;
	CColorStatic m_stcIsBeemAxisStanby;
	CColorStatic m_stcIsBeemAxisRoateNG;
	CColorStatic m_stcIsBeemAxisRoateDoneReply;
	CColorStatic m_stcIsBeemAxisRoateStopReply;

	CColorStatic m_stcIsLcRoateReply;
	CColorStatic m_stcIsLcStanby;
	CColorStatic m_stcIsLcRoateNG;
	CColorStatic m_stcIsLcRoateDoneReply;
	CColorStatic m_stcIsLcRoateStopReply;

	CColorStatic m_stcIsSamplePolRoateReply;
	CColorStatic m_stcIsSamplePolStanby;
	CColorStatic m_stcIsSamplePolRoateNG;
	CColorStatic m_stcIsSamplePolRoateDoneReply;
	CColorStatic m_stcIsSamplePolRoateStopReply;
	
	CColorStatic m_stcIsLcmRoateReply;
	CColorStatic m_stcIsLcmStanby;
	CColorStatic m_stcIsLcmRoateNG;
	CColorStatic m_stcIsLcmRoateDoneReply;
	CColorStatic m_stcIsLcmRoateStopReply;
	
	CColorStatic m_stcIsLclRoateReply;
	CColorStatic m_stcIsLclStanby;
	CColorStatic m_stcIsLclRoateNG;
	CColorStatic m_stcIsLclRoateDoneReply;
	CColorStatic m_stcIsLclRoateStopReply;
	



	CColorStatic m_stcPcAlignStanby;
	CColorStatic m_stcMeasurementRunBeemAxis;
	CColorStatic m_stcMeasurementRunLc;
	CColorStatic m_stcMeasurementRunSameplePol;
	CColorStatic m_stcMeasurementRunLcm;
	CColorStatic m_stcMeasurementRunLcl;

	CColorStatic m_stcMeasurementDoneBeemAxis;
	CColorStatic m_stcMeasurementDoneLc;
	CColorStatic m_stcMeasurementDoneSameplePol;
	CColorStatic m_stcMeasurementDoneLcm;
	CColorStatic m_stcMeasurementDoneLcl;

	CColorStatic m_stcPanelAlignMarkFindOk;
	CColorStatic m_stcPanelAlignBusy;
	CColorStatic m_stcPanelAlignNg;
	CColorStatic m_stcPanelAlignOk;
	CColorStatic m_stcPanelAlignMoveOk;

	CColorStatic m_stcMeasurementStopBeemAxis;
	CColorStatic m_stcMeasurementStopLc;
	CColorStatic m_stcMeasurementStopSameplePol;
	CColorStatic m_stcMeasurementStopLcm;
	CColorStatic m_stcMeasurementStopLcl;



	BOOL bTempStanby=1;
	BOOL bTempRunBeemAxis=1;
	BOOL bTempRunLc=1;
	BOOL bTempRunSamplePol=1;
	BOOL bTempRunLcm=1;
	BOOL bTempRunLcl=1;

	BOOL bTempDoneBeemAxis=1;
	BOOL bTempDoneLc=1;
	BOOL bTempDoneSamplePol=1;
	BOOL bTempDoneLcm=1;
	BOOL bTempDoneLcl=1;

	BOOL bTempMarkFindok=1;
	BOOL bTempMarkBusy=1;
	BOOL bTempMarkNg=1;
	BOOL bTempMarkOk=1;
	BOOL bTempMarkMoveOk=1;



protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//afx_msg void OnBnClickedBtnManualTest();
//	afx_msg void OnEnChangeEditManualStageUpPolPosX();


	afx_msg void OnBnClickedBtnSetPcAlignStanby();

	afx_msg void OnBnClickedBtnSetPanelAlignMarkFindOk();

	afx_msg void OnBnClickedBtnSetPanelAlignBusy();

	afx_msg void OnBnClickedBtnSetPanelAlignNg();

	afx_msg void OnBnClickedBtnSetPanelAlignMoveOkReply();

	afx_msg void OnBnClickedBtnSetPanelAlignOk();

	afx_msg void OnBnClickedBtnSetBeemAxisMeasurementRun();

	afx_msg void OnBnClickedBtnSetBeemAxisMeasurementDone();

	afx_msg void OnBnClickedBtnSetLcMeasurementRun();

	afx_msg void OnBnClickedBtnSetLcMeasurementDone();

	afx_msg void OnBnClickedBtnSetSamplePolMeasurementRun();

	afx_msg void OnBnClickedBtnSetSamplePolMeasurementDone();

	afx_msg void OnBnClickedBtnSetLcmMeasurementRun();

	afx_msg void OnBnClickedBtnSetLcmMeasurementDone();

	afx_msg void OnBnClickedBtnSetLclMeasurementRun();

	afx_msg void OnBnClickedBtnSetLclMeasurementDone();

	

	afx_msg void OnBnClickedBtnWritePanelAxisAdjustPos();
	

	




//	afx_msg void OnStnClickedStcManualStageAlignStanby();
	afx_msg void OnBnClickedBtnManualStagePcDdMotorStop();
	afx_msg void OnBnClickedBtnManualStageMeasurementStopBeemAxisSet();
	afx_msg void OnBnClickedBtnManualStageMeasurementStopLcSet();
	afx_msg void OnBnClickedBtnManualStageMeasurementStopSamplePolSet();
	afx_msg void OnBnClickedBtnManualStageMeasurementStopLcmSet();
	afx_msg void OnBnClickedBtnManualStageMeasurementStopLclSet();
};
