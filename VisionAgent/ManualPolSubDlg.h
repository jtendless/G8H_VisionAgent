#pragma once


// CManualPolSubDlg 대화 상자입니다.

class CManualPolSubDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CManualPolSubDlg)

public:
	CManualPolSubDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CManualPolSubDlg();

	bool m_bDialog_Entry;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_MANUAL_SUB_POL };
#endif

	CEdit m_Edit_StageUpPolPosX, m_Edit_StageUpPolPosY, m_Edit_StageUpPolPosT;
	CEdit m_Edit_StageDnPolPosX, m_Edit_StageDnPolPosY, m_Edit_StageDnPolPosT;

	CEdit m_Edit_StageWriteUpPolPosX, m_Edit_StageWriteUpPolPosY, m_Edit_StageWriteUpPolPosT;
	CEdit m_Edit_StageWriteDnPolPosX, m_Edit_StageWriteDnPolPosY, m_Edit_StageWriteDnPolPosT;

	CEdit m_Edit_StageAccumluteMoveValueUp;
	CEdit m_Edit_StageAccumluteMoveValueDn;

	CEdit m_Edit_StagePolOffsetUp;
	CEdit m_Edit_StagePolOffsetDn;


	CColorStatic m_stcIsDnPolAlignRunCmd;
	CColorStatic m_stcIsUpPolAlignRunCmd;

	CColorStatic m_stcIsDnPolAlignMoveDone;
	CColorStatic m_stcIsUpPolAlignMoveDone;

	CColorStatic m_stcIsDnPolAlignResetCmd;
	CColorStatic m_stcIsUpPolAlignResetCmd;

	CColorStatic m_stcIsDnPolAlignProcessing;
	CColorStatic m_stcIsUpPolAlignProcessing;

	CColorStatic m_stcIsDnPolAlignDone;
	CColorStatic m_stcIsUpPolAlignDone;

	CColorStatic m_stcIsRecipeChangeCmd;
	CColorStatic m_stcIsRecipeDeleteCmd;
	CColorStatic m_stcIsRecipeAddCmd;

	//
	CColorStatic m_stcDdMotorRunUp;
	CColorStatic m_stcDdMotorRunDn;

	CColorStatic m_stcAlignMarkFindOkUp;
	CColorStatic m_stcAlignMarkFindOkDn;

	CColorStatic m_stcAlignBusyUp;
	CColorStatic m_stcAlignBusyDn;

	CColorStatic m_stcAlignNgUp;
	CColorStatic m_stcAlignNgDn;

	CColorStatic m_stcAlignOkUp;
	CColorStatic m_stcAlignOkDn;

	CColorStatic m_stcAlignMoveOkReplyUp;
	CColorStatic m_stcAlignMoveOkReplyDn;
	

	//
	BOOL  m_bDdMotorRunUp=1;
	BOOL  m_bDdMotorRunDn=1;

	BOOL m_bAlignMarkFindOkUp=1;
	BOOL m_bAlignMarkFindOkDn=1;

	BOOL m_bAlignBusyUp=1;
	BOOL m_bAlignBusyDn=1;

	BOOL m_bAlignNgUp=1;
	BOOL m_bAlignNgDn=1;

	BOOL m_bAlignOkUp=1;
	BOOL m_bAlignOkDn=1;

	BOOL m_bAlignMoveOkReplyUp=1;
	BOOL m_bAlignMoveOkReplyDn=1;







protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnEnChangeEditManualStagePolOffsetDn();

	afx_msg void OnBnClickedBtnSetDnPolAlignMarkFindOk();

	afx_msg void OnBnClickedBtnSetUpPolAlignMarkFindOk();

	afx_msg void OnBnClickedBtnSetDnPolAlignBusy();


	afx_msg void OnBnClickedBtnSetUpPolAlignBusy();

	afx_msg void OnBnClickedBtnSetDnPolAlignNg();

	afx_msg void OnBnClickedBtnSetUpPolAlignNg();

	afx_msg void OnBnClickedBtnSetDnPolAlignMoveOkReply();

	afx_msg void OnBnClickedBtnSetUpPolAlignMoveOkReply();

	afx_msg void OnBnClickedBtnSetDnPolAlignOk();

	afx_msg void OnBnClickedBtnSetUpPolAlignOk();

	afx_msg void OnBnClickedBtnSetUpDdMotorRun();

	afx_msg void OnBnClickedBtnSetDnDdMotorRun();

	afx_msg void OnBnClickedBtnWriteUpPolAxisAdjustPos();
	afx_msg void OnBnClickedBtnWriteDnPolAxisAdjustPos();

	afx_msg void OnBnClickedBtnWriteUpPolOffset();
	afx_msg void OnBnClickedBtnWriteDnPolOffset();

	afx_msg void OnBnClickedBtnWriteUpDdAccumulateMoveValue();
	afx_msg void OnBnClickedBtnWriteDnDdAccumulateMoveValue();

	


};
