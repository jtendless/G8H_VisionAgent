// ManualStageSubDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "ManualStageSubDlg.h"
#include "afxdialogex.h"


// CManualStageSubDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CManualStageSubDlg, CDialogEx)

CManualStageSubDlg::CManualStageSubDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_MANUAL_SUB_STAGE, pParent)
{
	m_bDialog_Entry = FALSE;
	Create(IDD_DLG_MANUAL_SUB_STAGE, pParent);
	
}

CManualStageSubDlg::~CManualStageSubDlg()
{

}

void CManualStageSubDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
BEGIN_MESSAGE_MAP(CManualStageSubDlg, CDialogEx)
	//	ON_EN_CHANGE(IDC_EDIT_MANUAL_STAGE_UP_POL_POS_X, &CManualStageSubDlg::OnEnChangeEditManualStageUpPolPosX)
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
	

	ON_BN_CLICKED(IDC_BTN_MANUAL_STAGE_PC_ALIGN_STANBY_SET,&CManualStageSubDlg::OnBnClickedBtnSetPcAlignStanby)
	ON_BN_CLICKED(IDC_BTN_MANUAL_STAGE_ALIGN_MARK_FIND_OK_PANEL_SET,&CManualStageSubDlg::OnBnClickedBtnSetPanelAlignMarkFindOk)
	ON_BN_CLICKED(IDC_BTN_MANUAL_STAGE_ALIGN_BUSY_PANEL_SET,&CManualStageSubDlg::OnBnClickedBtnSetPanelAlignBusy)
	ON_BN_CLICKED(IDC_BTN_MANUAL_STAGE_ALIGN_NG_PANEL_SET,&CManualStageSubDlg::OnBnClickedBtnSetPanelAlignNg)
	ON_BN_CLICKED(IDC_BTN_MANUAL_STAGE_ALIGN_MOVE_OK_REPLY_PANEL_SET,&CManualStageSubDlg::OnBnClickedBtnSetPanelAlignMoveOkReply)
	ON_BN_CLICKED(IDC_BTN_MANUAL_STAGE_ALIGN_OK_PANEL_SET,&CManualStageSubDlg::OnBnClickedBtnSetPanelAlignOk)
	ON_BN_CLICKED(IDC_BTN_MANUAL_STAGE_MEASUREMENT_RUN_BEEM_AXIS_SET,&CManualStageSubDlg::OnBnClickedBtnSetBeemAxisMeasurementRun)
	ON_BN_CLICKED(IDC_BTN_MANUAL_STAGE_MEASUREMENT_DONE_BEEM_AXIS_SET,&CManualStageSubDlg::OnBnClickedBtnSetBeemAxisMeasurementDone)
	ON_BN_CLICKED(IDC_BTN_MANUAL_STAGE_MEASUREMENT_RUN_LC_SET,&CManualStageSubDlg::OnBnClickedBtnSetLcMeasurementRun)
	ON_BN_CLICKED(IDC_BTN_MANUAL_STAGE_MEASUREMENT_DONE_LC_SET,&CManualStageSubDlg::OnBnClickedBtnSetLcMeasurementDone)
    ON_BN_CLICKED(IDC_BTN_MANUAL_STAGE_MEASUREMENT_RUN_SAMPLE_POL_SET,&CManualStageSubDlg::OnBnClickedBtnSetSamplePolMeasurementRun)
    ON_BN_CLICKED(IDC_BTN_MANUAL_STAGE_MEASUREMENT_DONE_SAMPLE_POL_SET,&CManualStageSubDlg::OnBnClickedBtnSetSamplePolMeasurementDone)
    ON_BN_CLICKED(IDC_BTN_MANUAL_STAGE_MEASUREMENT_RUN_LCM_SET,&CManualStageSubDlg::OnBnClickedBtnSetLcmMeasurementRun)
    ON_BN_CLICKED(IDC_BTN_MANUAL_STAGE_MEASUREMENT_DONE_LCM_SET,&CManualStageSubDlg::OnBnClickedBtnSetLcmMeasurementDone)
    ON_BN_CLICKED(IDC_BTN_MANUAL_STAGE_MEASUREMENT_RUN_LCL_SET,&CManualStageSubDlg::OnBnClickedBtnSetLclMeasurementRun)
    ON_BN_CLICKED(IDC_BTN_MANUAL_STAGE_MEASUREMENT_DONE_LCL_SET,&CManualStageSubDlg::OnBnClickedBtnSetLclMeasurementDone)
   
    ON_BN_CLICKED(IDC_BTN_MANUAL_STAGE_WRITE_POL_ADJUST_POS_PANEL,&CManualStageSubDlg::OnBnClickedBtnWritePanelAxisAdjustPos)
  

//	ON_STN_CLICKED(IDC_STC_MANUAL_STAGE_ALIGN_STANBY, &CManualStageSubDlg::OnStnClickedStcManualStageAlignStanby)
ON_BN_CLICKED(IDC_BTN_MANUAL_STAGE_PC_DD_MOTOR_STOP, &CManualStageSubDlg::OnBnClickedBtnManualStagePcDdMotorStop)
ON_BN_CLICKED(IDC_BTN_MANUAL_STAGE_MEASUREMENT_STOP_BEEM_AXIS_SET, &CManualStageSubDlg::OnBnClickedBtnManualStageMeasurementStopBeemAxisSet)
ON_BN_CLICKED(IDC_BTN_MANUAL_STAGE_MEASUREMENT_STOP_LC_SET, &CManualStageSubDlg::OnBnClickedBtnManualStageMeasurementStopLcSet)
ON_BN_CLICKED(IDC_BTN_MANUAL_STAGE_MEASUREMENT_STOP_SAMPLE_POL_SET, &CManualStageSubDlg::OnBnClickedBtnManualStageMeasurementStopSamplePolSet)
ON_BN_CLICKED(IDC_BTN_MANUAL_STAGE_MEASUREMENT_STOP_LCM_SET, &CManualStageSubDlg::OnBnClickedBtnManualStageMeasurementStopLcmSet)
ON_BN_CLICKED(IDC_BTN_MANUAL_STAGE_MEASUREMENT_STOP_LCL_SET, &CManualStageSubDlg::OnBnClickedBtnManualStageMeasurementStopLclSet)
END_MESSAGE_MAP()

BOOL CManualStageSubDlg::OnInitDialog()
{

	//m_pManualStageSubDlg = new CManualStageSubDlg(this);

	
					
	m_Edit_StageWritePanelPosX1.SubclassDlgItem(IDC_EDIT_MANUAL_STAGE_WRITE_PANEL_POS_X1, this);
	m_Edit_StageWritePanelPosY1.SubclassDlgItem(IDC_EDIT_MANUAL_STAGE_WRITE_PANEL_POS_Y1, this);
	m_Edit_StageWritePanelPosX2.SubclassDlgItem(IDC_EDIT_MANUAL_STAGE_WRITE_PANEL_POS_X2, this);
	m_Edit_StageWritePanelPosY2.SubclassDlgItem(IDC_EDIT_MANUAL_STAGE_WRITE_PANEL_POS_Y2, this);
	


	m_Edit_StagePanelPosX1.SubclassDlgItem(IDC_EDIT_MANUAL_STAGE_PANEL_POS_X1, this);
	m_Edit_StagePanelPosY1.SubclassDlgItem(IDC_EDIT_MANUAL_STAGE_PANEL_POS_Y1, this);
	m_Edit_StagePanelPosX2.SubclassDlgItem(IDC_EDIT_MANUAL_STAGE_PANEL_POS_X2, this);
	m_Edit_StagePanelPosY2.SubclassDlgItem(IDC_EDIT_MANUAL_STAGE_PANEL_POS_Y2, this);

	//

	m_stcIsAlignStanby.SubclassDlgItem(IDC_STC_MANUAL_STAGE_ALIGN_STANBY, this);

	m_stcIsPanelAlignRunCmd.SubclassDlgItem(IDC_STC_MANUAL_STAGE_ALIGN_RUN_CMD_PANEL, this);

	m_stcIsPanelAlignMoveDone .SubclassDlgItem(IDC_STC_MANUAL_STAGE_ALIGN_MOVE_DONE_PANEL, this);

	m_stcIsPanelAlignResetCmd .SubclassDlgItem(IDC_STC_MANUAL_STAGE_ALIGN_RESET_CMD_PANEL, this);

	m_stcIsPanelAlignProcessing .SubclassDlgItem(IDC_STC_MANUAL_STAGE_ALIGN_PROCESSING_PANEL, this);

	m_stcIsPanelAlignDone .SubclassDlgItem(IDC_STC_MANUAL_STAGE_ALIGN_DONE_PANEL, this);
	

	m_stcIsBeemAxisRoateReply .SubclassDlgItem(IDC_STC_MANUAL_STAGE_ROATE_REPLY_BEEMAXIS, this);
	m_stcIsBeemAxisStanby .SubclassDlgItem(IDC_STC_MANUAL_STAGE_STANBY_BEEM_AXIS, this);
	m_stcIsBeemAxisRoateNG .SubclassDlgItem(IDC_STC_MANUAL_STAGE_ROATE_NG_BEEM_AXIS, this);
	m_stcIsBeemAxisRoateDoneReply.SubclassDlgItem(IDC_STC_MANUAL_STAGE_ROATE_DONE_REPLY_BEEM_AXIS, this);
	m_stcIsBeemAxisRoateStopReply .SubclassDlgItem(IDC_STC_MANUAL_STAGE_ROATE_STOP_REPLY_BEEM_AXIS, this);

	m_stcIsLcRoateReply.SubclassDlgItem(IDC_STC_MANUAL_STAGE_ROATE_REPLY_LC, this);
	m_stcIsLcStanby.SubclassDlgItem(IDC_STC_MANUAL_STAGE_STANBY_LC, this);
	m_stcIsLcRoateNG.SubclassDlgItem(IDC_STC_MANUAL_STAGE_ROATE_NG_LC, this);
	m_stcIsLcRoateDoneReply.SubclassDlgItem(IDC_STC_MANUAL_STAGE_ROATE_DONE_REPLY_LC, this);
	m_stcIsLcRoateStopReply.SubclassDlgItem(IDC_STC_MANUAL_STAGE_ROATE_STOP_REPLY_LC, this);

	m_stcIsSamplePolRoateReply.SubclassDlgItem(IDC_STC_MANUAL_STAGE_ROATE_REPLY_SAMPLE_POL, this);
	m_stcIsSamplePolStanby.SubclassDlgItem(IDC_STC_MANUAL_STAGE_STANBY_SAMPLE_POL, this);
	m_stcIsSamplePolRoateNG.SubclassDlgItem(IDC_STC_MANUAL_STAGE_ROATE_NG_SAMPLE, this);
	m_stcIsSamplePolRoateDoneReply.SubclassDlgItem(IDC_STC_MANUAL_STAGE_ROATE_DONE_REPLY_SAMPLE_POL, this);
	m_stcIsSamplePolRoateStopReply.SubclassDlgItem(IDC_STC_MANUAL_STAGE_ROATE_STOP_REPLY_SAMPLE_POL, this);

	m_stcIsLcmRoateReply.SubclassDlgItem(IDC_STC_MANUAL_STAGE_ROATE_REPLY_LCM, this);
	m_stcIsLcmStanby.SubclassDlgItem(IDC_STC_MANUAL_STAGE_STANBY_LCM, this);
	m_stcIsLcmRoateNG.SubclassDlgItem(IDC_STC_MANUAL_STAGE_ROATE_NG_LCM, this);
	m_stcIsLcmRoateDoneReply.SubclassDlgItem(IDC_STC_MANUAL_STAGE_ROATE_DONE_REPLY_LCM, this);
	m_stcIsLcmRoateStopReply.SubclassDlgItem(IDC_STC_MANUAL_STAGE_ROATE_STOP_REPLY_LCM, this);

	m_stcIsLclRoateReply.SubclassDlgItem(IDC_STC_MANUAL_STAGE_ROATE_REPLY_LCL, this);
	m_stcIsLclStanby.SubclassDlgItem(IDC_STC_MANUAL_STAGE_STANBY_LCL, this);
	m_stcIsLclRoateNG.SubclassDlgItem(IDC_STC_MANUAL_STAGE_ROATE_NG_LCL, this);
	m_stcIsLclRoateDoneReply.SubclassDlgItem(IDC_STC_MANUAL_STAGE_ROATE_DONE_REPLY_LCL, this);
	m_stcIsLclRoateStopReply.SubclassDlgItem(IDC_STC_MANUAL_STAGE_ROATE_STOP_REPLY_LCL, this);



	m_stcPcAlignStanby.SubclassDlgItem(IDC_STC_MANUAL_STAGE_PC_ALIGN_STANBY, this);
	m_stcMeasurementRunBeemAxis.SubclassDlgItem(IDC_STC_MANUAL_STAGE_MEASUREMENT_RUN_BEEM_AXIS, this);
	m_stcMeasurementRunLc.SubclassDlgItem(IDC_STC_MANUAL_STAGE_MEASUREMENT_RUN_LC, this);
	m_stcMeasurementRunSameplePol.SubclassDlgItem(IDC_STC_MANUAL_STAGE_MEASUREMENT_RUN_SAMEPLE_POL, this);
	m_stcMeasurementRunLcm.SubclassDlgItem(IDC_STC_MANUAL_STAGE_MEASUREMENT_RUN_LCM, this);
	m_stcMeasurementRunLcl.SubclassDlgItem(IDC_STC_MANUAL_STAGE_MEASUREMENT_RUN_LCL, this);

	m_stcMeasurementDoneBeemAxis.SubclassDlgItem(IDC_STC_MANUAL_STAGE_MEASUREMENT_DONE_BEEM_AXIS, this);
	m_stcMeasurementDoneLc.SubclassDlgItem(IDC_STC_MANUAL_STAGE_MEASUREMENT_DONE_LC, this);
	m_stcMeasurementDoneSameplePol.SubclassDlgItem(IDC_STC_MANUAL_STAGE_MEASUREMENT_DONE_SAMEPLE_POL, this);
	m_stcMeasurementDoneLcm.SubclassDlgItem(IDC_STC_MANUAL_STAGE_MEASUREMENT_DONE_LCM, this);
	m_stcMeasurementDoneLcl.SubclassDlgItem(IDC_STC_MANUAL_STAGE_MEASUREMENT_DONE_LCL, this);

	m_stcMeasurementStopBeemAxis.SubclassDlgItem(IDC_STC_MANUAL_STAGE_MEASUREMENT_STOP_BEEM_AXIS, this);
	m_stcMeasurementStopLc.SubclassDlgItem(IDC_STC_MANUAL_STAGE_MEASUREMENT_STOP_LC, this);
	m_stcMeasurementStopSameplePol.SubclassDlgItem(IDC_STC_MANUAL_STAGE_MEASUREMENT_STOP_SAMEPLE_POL, this);
	m_stcMeasurementStopLcm.SubclassDlgItem(IDC_STC_MANUAL_STAGE_MEASUREMENT_STOP_LCM, this);
	m_stcMeasurementStopLcl.SubclassDlgItem(IDC_STC_MANUAL_STAGE_MEASUREMENT_STOP_LCL, this);


	m_stcPanelAlignMarkFindOk.SubclassDlgItem(IDC_STC_MANUAL_STAGE_PANEL_ALIGN_MARK_FIND_OK, this);
	m_stcPanelAlignBusy.SubclassDlgItem(IDC_STC_MANUAL_STAGE_PANEL_ALIGN_BUSY, this);
	m_stcPanelAlignNg.SubclassDlgItem(IDC_STC_MANUAL_STAGE_PANEL_ALIGN_NG, this);
	m_stcPanelAlignOk.SubclassDlgItem(IDC_STC_MANUAL_STAGE_PANEL_ALIGN_OK, this);
	m_stcPanelAlignMoveOk.SubclassDlgItem(IDC_STC_MANUAL_STAGE_PANEL_ALIGN_MOVE_OK, this);




	CString strTemp1 = _T("Input");

	m_Edit_StageWritePanelPosX1.SetWindowTextW(strTemp1);
	m_Edit_StageWritePanelPosX2.SetWindowTextW(strTemp1);
	m_Edit_StageWritePanelPosY1.SetWindowTextW(strTemp1);
	m_Edit_StageWritePanelPosY2.SetWindowTextW(strTemp1);


	return 0;
}

void CManualStageSubDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow)
	{
		SetTimer(1, 100, NULL);
	}
	else
	{
		KillTimer(1);
	} 
}

void CManualStageSubDlg::OnTimer(UINT_PTR nIDEvent)
{
	CString strTemp = _T("");
	
	DOUBLE dX = 0, dY = 0, dT = 0;
	DOUBLE dX1 = 0, dY1 = 0, dX2 = 0, dY2 = 0;

	Devs::m_StageMotion.ReadPanelMotorPos(&dX1, &dX2, &dY1,&dY2);

	strTemp.Format(_T("%.5f"), dX1);
	m_Edit_StagePanelPosX1.SetWindowTextW(strTemp);

	strTemp.Format(_T("%.5f"), dX2);
	m_Edit_StagePanelPosX2.SetWindowTextW(strTemp);

	strTemp.Format(_T("%.5f"), dY1);
	m_Edit_StagePanelPosY1.SetWindowTextW(strTemp);

	strTemp.Format(_T("%.5f"), dY2);
	m_Edit_StagePanelPosY2.SetWindowTextW(strTemp);

	




	//
	if (Devs::m_StageMotion.IsAlignStanby())
	{
		m_stcIsAlignStanby.SetBackgroundColor(GREEN);
	}
	else
	{
		m_stcIsAlignStanby.SetBackgroundColor(BTN_LAMP_OFF);
	}

	

	if (Devs::m_StageMotion.IsPanelAlignRunCmd())
	{
		m_stcIsPanelAlignRunCmd.SetBackgroundColor(GREEN);
	}

	else
	{
		m_stcIsPanelAlignRunCmd.SetBackgroundColor(BTN_LAMP_OFF);
	}

	

	if (Devs::m_StageMotion.IsPanelAlignMoveDone())
	{
		m_stcIsPanelAlignMoveDone.SetBackgroundColor(GREEN);
	}

	else
	{
		m_stcIsPanelAlignMoveDone.SetBackgroundColor(BTN_LAMP_OFF);
	}

	

	if (Devs::m_StageMotion.IsPanelAlignResetCmd())
	{
		m_stcIsPanelAlignResetCmd.SetBackgroundColor(GREEN);
	}

	else
	{
		m_stcIsPanelAlignResetCmd.SetBackgroundColor(BTN_LAMP_OFF);
	}

	
	if (Devs::m_StageMotion.IsPanelAlignProcessing())
	{
		m_stcIsPanelAlignProcessing.SetBackgroundColor(GREEN);
	}

	else
	{
		m_stcIsPanelAlignProcessing.SetBackgroundColor(BTN_LAMP_OFF);
	}

	

	if (Devs::m_StageMotion.IsPanelAlignDone())
	{
		m_stcIsPanelAlignDone.SetBackgroundColor(GREEN);
	}

	else
	{
		m_stcIsPanelAlignDone.SetBackgroundColor(BTN_LAMP_OFF);
	}

	

	if (Devs::m_StageMotion.IsPlcBeamAxisRunReply())
	{
		m_stcIsBeemAxisRoateReply.SetBackgroundColor(GREEN);
	}

	else
	{
		m_stcIsBeemAxisRoateReply.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsPlcBeamAxisStanby())
	{
		m_stcIsBeemAxisStanby.SetBackgroundColor(GREEN);
	}

	else
	{
		m_stcIsBeemAxisStanby.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsPlcBeamAxisNG())
	{
		m_stcIsBeemAxisRoateNG.SetBackgroundColor(GREEN);
	}

	else
	{
		m_stcIsBeemAxisRoateNG.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsPlcBeamAxisDoneReply())
	{
		m_stcIsBeemAxisRoateDoneReply.SetBackgroundColor(GREEN);
	}

	else
	{
		m_stcIsBeemAxisRoateDoneReply.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsPlcBeamAxisStopReply())
	{
		m_stcIsBeemAxisRoateStopReply.SetBackgroundColor(GREEN);
	}

	else
	{
		m_stcIsBeemAxisRoateStopReply.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsPlcBlackLcRunReply())
	{
		m_stcIsLcRoateReply.SetBackgroundColor(GREEN);
	}

	else
	{
		m_stcIsLcRoateReply.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsPlcBlackLcStanby())
	{
		m_stcIsLcStanby.SetBackgroundColor(GREEN);
	}

	else
	{
		m_stcIsLcStanby.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsPlcBlackLcNG())
	{
		m_stcIsLcRoateNG.SetBackgroundColor(GREEN);
	}

	else
	{
		m_stcIsLcRoateNG.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsPlcBlackLcDoneReply())
	{
		m_stcIsLcRoateDoneReply.SetBackgroundColor(GREEN);
	}

	else
	{
		m_stcIsLcRoateDoneReply.SetBackgroundColor(BTN_LAMP_OFF);
	}
	if (Devs::m_StageMotion.IsPlcBlackLcStopReply())
	{
		m_stcIsLcRoateStopReply.SetBackgroundColor(GREEN);
	}

	else
	{
		m_stcIsLcRoateStopReply.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsPlcSamplePolRunReply())
	{
		m_stcIsSamplePolRoateReply.SetBackgroundColor(GREEN);
	}

	else
	{
		m_stcIsSamplePolRoateReply.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsPlcSamplePolStanby())
	{
		m_stcIsSamplePolStanby.SetBackgroundColor(GREEN);
	}

	else
	{
		m_stcIsSamplePolStanby.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsPlcSamplePolNG())
	{
		m_stcIsSamplePolRoateNG.SetBackgroundColor(GREEN);
	}

	else
	{
		m_stcIsSamplePolRoateNG.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsPlcSamplePolDoneReply())
	{
		m_stcIsSamplePolRoateDoneReply.SetBackgroundColor(GREEN);
	}

	else
	{
		m_stcIsSamplePolRoateDoneReply.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsPlcSamplePolStopReply())
	{
		m_stcIsSamplePolRoateStopReply.SetBackgroundColor(GREEN);
	}

	else
	{
		m_stcIsSamplePolRoateStopReply.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsPlcLcmRunReply())
	{
		m_stcIsLcmRoateReply.SetBackgroundColor(GREEN);
	}

	else
	{
		m_stcIsLcmRoateReply.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsPlcLcmStanby())
	{
		m_stcIsLcmStanby.SetBackgroundColor(GREEN);
	}

	else
	{
		m_stcIsLcmStanby.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsPlcLcmNG())
	{
		m_stcIsLcmRoateNG.SetBackgroundColor(GREEN);
	}

	else
	{
		m_stcIsLcmRoateNG.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsPlcLcmDoneReply())
	{
		m_stcIsLcmRoateDoneReply.SetBackgroundColor(GREEN);
	}

	else
	{
		m_stcIsLcmRoateDoneReply.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsPlcLcmStopReply())
	{
		m_stcIsLcmRoateStopReply.SetBackgroundColor(GREEN);
	}

	else
	{
		m_stcIsLcmRoateStopReply.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsPlcLclRunReply())
	{
		m_stcIsLclRoateReply.SetBackgroundColor(GREEN);
	}

	else
	{
		m_stcIsLclRoateReply.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsPlcLclStanby())
	{
		m_stcIsLclStanby.SetBackgroundColor(GREEN);
	}

	else
	{
		m_stcIsLclStanby.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsPlcLclNG())
	{
		m_stcIsLclRoateNG.SetBackgroundColor(GREEN);
	}

	else
	{
		m_stcIsLclRoateNG.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsPlcLclDoneReply())
	{
		m_stcIsLclRoateDoneReply.SetBackgroundColor(GREEN);
	}

	else
	{
		m_stcIsLclRoateDoneReply.SetBackgroundColor(BTN_LAMP_OFF);

	}	if (Devs::m_StageMotion.IsPlcLclStopReply())
	{
		m_stcIsLclRoateStopReply.SetBackgroundColor(GREEN);
	}

	else
	{
		m_stcIsLclRoateStopReply.SetBackgroundColor(BTN_LAMP_OFF);
	}



	if (Devs::m_StageMotion.IsPcAlignStanby() == 1)
	{
		m_stcPcAlignStanby.SetBackgroundColor(GREEN);
	}
	else
	{
		m_stcPcAlignStanby.SetBackgroundColor(BTN_LAMP_OFF);
	}
	
	if (Devs::m_StageMotion.IsPanelAlignMarkFindOk() == 1)
	{
		m_stcPanelAlignMarkFindOk.SetBackgroundColor(GREEN);
	}
	else
	{
		m_stcPanelAlignMarkFindOk.SetBackgroundColor(BTN_LAMP_OFF);
	}
	
	if (Devs::m_StageMotion.IsPanelAlignBusy() == 1)
	{
		m_stcPanelAlignBusy.SetBackgroundColor(GREEN);
	}
	else
	{
		m_stcPanelAlignBusy.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IstPanelAlignNg() == 1)
	{
		m_stcPanelAlignNg.SetBackgroundColor(GREEN);
	}
	else
	{
		m_stcPanelAlignNg.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsPanelAlignMoveOkReply() == 1)
	{
		m_stcPanelAlignMoveOk.SetBackgroundColor(GREEN);
	}
	else
	{
		m_stcPanelAlignMoveOk.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsPanelAlignOk() == 1)
	{
		m_stcPanelAlignOk.SetBackgroundColor(GREEN);
	}
	else
	{
		m_stcPanelAlignOk.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsBeamAxisMeasurementRun() == 1)
	{
		m_stcMeasurementRunBeemAxis.SetBackgroundColor(GREEN);
	}
	else
	{
		m_stcMeasurementRunBeemAxis.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsBeamAxisMeasurementDone() == 1)
	{
		m_stcMeasurementDoneBeemAxis.SetBackgroundColor(GREEN);
	}
	else
	{
		m_stcMeasurementDoneBeemAxis.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsBlackLcMeasurementRun() == 1)
	{
		m_stcMeasurementRunLc.SetBackgroundColor(GREEN);
	}
	else
	{
		m_stcMeasurementRunLc.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsBlackLcMeasurementDone() == 1)
	{
		m_stcMeasurementDoneLc.SetBackgroundColor(GREEN);
	}
	else
	{
		m_stcMeasurementDoneLc.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsSamplePolMeasurementRun() == 1)
	{
		m_stcMeasurementRunSameplePol.SetBackgroundColor(GREEN);
	}
	else
	{
		m_stcMeasurementRunSameplePol.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsSamplePolMeasurementDone() == 1)
	{
		m_stcMeasurementDoneSameplePol.SetBackgroundColor(GREEN);
	}
	else
	{
		m_stcMeasurementDoneSameplePol.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsLcmMeasurementRun() == 1)
	{
		m_stcMeasurementRunLcm.SetBackgroundColor(GREEN);
	}
	else
	{
		m_stcMeasurementRunLcm.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsLcmMeasurementDone() == 1)
	{
		m_stcMeasurementDoneLcm.SetBackgroundColor(GREEN);
	}
	else
	{
		m_stcMeasurementDoneLcm.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsLclMeasurementRun() == 1)
	{
		m_stcMeasurementRunLcl.SetBackgroundColor(GREEN);
	}
	else
	{
		m_stcMeasurementRunLcl.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsLclMeasurementDone() == 1)
	{
		m_stcMeasurementDoneLcl.SetBackgroundColor(GREEN);
	}
	else
	{
		m_stcMeasurementDoneLcl.SetBackgroundColor(BTN_LAMP_OFF);
	}

	//Stop
	//if (Devs::m_StageMotion.IsPlcLclStopReply())
	//{
	//	m_stcIsLclRoateStopReply.SetBackgroundColor(GREEN);
	//}

	//Stop

	if (Devs::m_StageMotion.IsBeamAxisMeasurementStop() == 1)
	{
		m_stcMeasurementStopBeemAxis.SetBackgroundColor(GREEN);
	}
	else
	{
		m_stcMeasurementStopBeemAxis.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsBlackLcMeasurementStop() == 1)
	{
		m_stcMeasurementStopLc.SetBackgroundColor(GREEN);
	}
	else
	{
		m_stcMeasurementStopLc.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsSamplePolMeasurementStop() == 1)
	{
		m_stcMeasurementStopSameplePol.SetBackgroundColor(GREEN);
	}
	else
	{
		m_stcMeasurementStopSameplePol.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsLcmMeasurementStop() == 1)
	{
		m_stcMeasurementStopLcm.SetBackgroundColor(GREEN);
	}
	else
	{
		m_stcMeasurementStopLcm.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsLclMeasurementStop() == 1)
	{
		m_stcMeasurementStopLcl.SetBackgroundColor(GREEN);
	}
	else
	{
		m_stcMeasurementStopLcl.SetBackgroundColor(BTN_LAMP_OFF);
	}
	//Stop
	//if (Devs::m_StageMotion.IsPlcLclStopReply())
	//{
	//	m_stcIsLclRoateStopReply.SetBackgroundColor(GREEN);
	//}

	//else
	//{
	//	m_stcIsLclRoateStopReply.SetBackgroundColor(BTN_LAMP_OFF);
	//}






	CDialogEx::OnTimer(nIDEvent);
}


//////////////////////////////////////////////////////////////////////////


void CManualStageSubDlg::OnBnClickedBtnSetPcAlignStanby()
{	
	if (Devs::m_StageMotion.IsPcAlignStanby ()==0)
	{
		Devs::m_StageMotion.SetPcAlignStanby();
	}
	else
	{
		Devs::m_StageMotion.ResetPcAlignStanby();
	}
	
}

void CManualStageSubDlg::OnBnClickedBtnSetPanelAlignMarkFindOk()
{
	if (Devs::m_StageMotion.IsPanelAlignMarkFindOk() == 0)
	{
		
		Devs::m_StageMotion.SetPanelAlignMarkFindOk();
	}
	else
	{
		Devs::m_StageMotion.ResetPanelAlignMarkFindOk();
	}
	
}



void CManualStageSubDlg::OnBnClickedBtnSetPanelAlignBusy()
{
	if (Devs::m_StageMotion.IsPanelAlignBusy() == 0)
	{
		Devs::m_StageMotion.SetPanelAlignBusy();
	}
	else
	{
		Devs::m_StageMotion.ResetPanelAlignBusy();
	}

}






void CManualStageSubDlg::OnBnClickedBtnSetPanelAlignNg()
{
	if (Devs::m_StageMotion.IstPanelAlignNg() == 0)
	{
		Devs::m_StageMotion.SetPanelAlignNg();
	}
	else
	{
		Devs::m_StageMotion.ResetPanelAlignNg();
	}
	
}


void CManualStageSubDlg::OnBnClickedBtnSetPanelAlignMoveOkReply()
{
	if (Devs::m_StageMotion.IsPanelAlignMoveOkReply() == 0)
	{
		Devs::m_StageMotion.SetPanelAlignMoveOkReply();
	}
	else
	{
		Devs::m_StageMotion.ResetPanelAlignMoveOkReply();
	}
	
}



void CManualStageSubDlg::OnBnClickedBtnSetPanelAlignOk()
{
	if (Devs::m_StageMotion.IsPanelAlignOk() == 0)
	{
		Devs::m_StageMotion.SetPanelAlignOk();
	}
	else
	{
		Devs::m_StageMotion.ResetPanelAlignOk();
	}
	
}



void CManualStageSubDlg::OnBnClickedBtnSetBeemAxisMeasurementRun()
{
	if (Devs::m_StageMotion.IsBeamAxisMeasurementRun() == 0)
	{
		Devs::m_StageMotion.SetBeamAxisMeasurementRun();
	}
	else
	{
		Devs::m_StageMotion.ResetBeamAxisMeasurementRun();
	}
	
}



void CManualStageSubDlg::OnBnClickedBtnSetBeemAxisMeasurementDone()
{
	if (Devs::m_StageMotion.IsBeamAxisMeasurementDone() == 0)
	{
		Devs::m_StageMotion.SetBeamAxisMeasurementDone();
	}
	else
	{
		Devs::m_StageMotion.ResetBeamAxisMeasurementDone();
	}
	
}



void CManualStageSubDlg::OnBnClickedBtnSetLcMeasurementRun()
{
	if (Devs::m_StageMotion.IsBlackLcMeasurementRun() == 0)
	{
		Devs::m_StageMotion.SetBlackLcMeasurementRun();
	}
	else
	{
		Devs::m_StageMotion.ResetBlackLcMeasurementRun();
	}
	
}



void CManualStageSubDlg::OnBnClickedBtnSetLcMeasurementDone()
{
	if (Devs::m_StageMotion.IsBlackLcMeasurementDone() == 0)
	{
		Devs::m_StageMotion.SetBlackLcMeasurementDone();
	}
	else
	{
		Devs::m_StageMotion.ResetBlackLcMeasurementDone();
	}
	
}



void CManualStageSubDlg::OnBnClickedBtnSetSamplePolMeasurementRun()
{
	if (Devs::m_StageMotion.IsSamplePolMeasurementRun() == 0)
	{
		Devs::m_StageMotion.SetSamplePolMeasurementRun();
	}
	else
	{
		Devs::m_StageMotion.ResetSamplePolMeasurementRun();
	}
	
}



void CManualStageSubDlg::OnBnClickedBtnSetSamplePolMeasurementDone()
{
	if (Devs::m_StageMotion.IsSamplePolMeasurementDone() == 0)
	{
		Devs::m_StageMotion.SetSamplePolMeasurementDone();
	}
	else
	{
		Devs::m_StageMotion.ResetSamplePolMeasurementDone();
	}
}


void CManualStageSubDlg::OnBnClickedBtnSetLcmMeasurementRun()
{
	if (Devs::m_StageMotion.IsLcmMeasurementRun() == 0)
	{
		Devs::m_StageMotion.SetLcmMeasurementRun();
	}
	else
	{
		Devs::m_StageMotion.ResetLcmMeasurementRun();
	}
	
}



void CManualStageSubDlg::OnBnClickedBtnSetLcmMeasurementDone()
{
	if (Devs::m_StageMotion.IsLcmMeasurementDone()== 0)
	{
		Devs::m_StageMotion.SetLcmMeasurementDone();
	}
	else
	{
		Devs::m_StageMotion.ResetLcmMeasurementDone();
	}
	
}



void CManualStageSubDlg::OnBnClickedBtnSetLclMeasurementRun()
{
	if (Devs::m_StageMotion.IsLclMeasurementRun()== 0)
	{
		Devs::m_StageMotion.SetLclMeasurementRun();
	}
	else
	{
		Devs::m_StageMotion.ResetLclMeasurementRun();
	}
		
}


void CManualStageSubDlg::OnBnClickedBtnSetLclMeasurementDone()
{
	if (Devs::m_StageMotion.IsLclMeasurementDone() == 0)
	{
		Devs::m_StageMotion.SetLclMeasurementDone();
	}
	else
	{
		Devs::m_StageMotion.ResetLclMeasurementDone();
	}
		
}


void CManualStageSubDlg::OnBnClickedBtnWritePanelAxisAdjustPos()
{
	CString strX1= _T("");
	CString strX2= _T("");
	CString strY1= _T("");
	CString strY2= _T("");

	m_Edit_StageWritePanelPosX1.GetWindowTextW(strX1);
	m_Edit_StageWritePanelPosX2.GetWindowTextW(strX2);
	m_Edit_StageWritePanelPosY1.GetWindowTextW(strY1);
	m_Edit_StageWritePanelPosY2.GetWindowTextW(strY2);

	double dX1 = _ttof(strX1), dX2 = _ttof(strX2);
	double dY1 = _ttof(strY1), dY2 = _ttof(strY2);
	Devs::m_StageMotion.WritePanelAxisAdjustPos(dX1, dX2, dY1, dY2);
}






// CManualStageSubDlg 메시지 처리기입니다.





void CManualStageSubDlg::OnBnClickedBtnManualStagePcDdMotorStop()
{
	Devs::m_StageMotion.SetDdMotorStop();
}


void CManualStageSubDlg::OnBnClickedBtnManualStageMeasurementStopBeemAxisSet()
{
		if (Devs::m_StageMotion.IsBeamAxisMeasurementStop()== 0)
	{
		Devs::m_StageMotion.SetBeamAxisMeasurementStop();
	}
	else
	{
		Devs::m_StageMotion.ResetBeamAxisMeasurementStop();
	}
}


void CManualStageSubDlg::OnBnClickedBtnManualStageMeasurementStopLcSet()
{
	if (Devs::m_StageMotion.IsBlackLcMeasurementStop() == 0)
	{
		Devs::m_StageMotion.SetBlackLcMeasurementStop();
	}
	else
	{
		Devs::m_StageMotion.ResetBlackLcMeasurementStop();
	}
}


void CManualStageSubDlg::OnBnClickedBtnManualStageMeasurementStopSamplePolSet()
{
	if (Devs::m_StageMotion.IsSamplePolMeasurementStop() == 0)
	{
		Devs::m_StageMotion.SetSamplePolMeasurementStop();
	}
	else
	{
		Devs::m_StageMotion.ResetSamplePolMeasurementStop();
	}
}


void CManualStageSubDlg::OnBnClickedBtnManualStageMeasurementStopLcmSet()
{
	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (Devs::m_StageMotion.IsLcmMeasurementStop() == 0)
	{
		Devs::m_StageMotion.SetLcmMeasurementStop();
	}
	else
	{
		Devs::m_StageMotion.ResetLcmMeasurementStop();
	}
}


void CManualStageSubDlg::OnBnClickedBtnManualStageMeasurementStopLclSet()
{
	if (Devs::m_StageMotion.IsLclMeasurementStop() == 0)
	{
		Devs::m_StageMotion.SetLclMeasurementStop();
	}
	else
	{
		Devs::m_StageMotion.ResetLclMeasurementStop();
	}
}
