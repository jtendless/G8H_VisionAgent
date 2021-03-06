// ManualPolSubDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "ManualPolSubDlg.h"
#include "afxdialogex.h"


// CManualPolSubDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CManualPolSubDlg, CDialogEx)

CManualPolSubDlg::CManualPolSubDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_MANUAL_SUB_POL, pParent)
{
	m_bDialog_Entry = FALSE;
	Create(IDD_DLG_MANUAL_SUB_POL, pParent);
	
}

CManualPolSubDlg::~CManualPolSubDlg()
{
}

void CManualPolSubDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CManualPolSubDlg, CDialogEx)


	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()

	ON_BN_CLICKED(IDC_BTN_MANUAL_POL_ALIGN_MARK_FIND_OK_DN_POL_SET, &CManualPolSubDlg::OnBnClickedBtnSetDnPolAlignMarkFindOk)
														  
	ON_BN_CLICKED(IDC_BTN_MANUAL_POL_ALIGN_MARK_FIND_OK_UP_POL_SET, &CManualPolSubDlg::OnBnClickedBtnSetUpPolAlignMarkFindOk)
	ON_BN_CLICKED(IDC_BTN_MANUAL_POL_ALIGN_BUSY_DN_POL_SET, &CManualPolSubDlg::OnBnClickedBtnSetDnPolAlignBusy)
														  
	ON_BN_CLICKED(IDC_BTN_MANUAL_POL_ALIGN_BUSY_UP_POL_SET, &CManualPolSubDlg::OnBnClickedBtnSetUpPolAlignBusy)
	ON_BN_CLICKED(IDC_BTN_MANUAL_POL_ALIGN_NG_DN_POL_SET, &CManualPolSubDlg::OnBnClickedBtnSetDnPolAlignNg)
														   
	ON_BN_CLICKED(IDC_BTN_MANUAL_POL_ALIGN_NG_UP_POL_SET, &CManualPolSubDlg::OnBnClickedBtnSetUpPolAlignNg)
	ON_BN_CLICKED(IDC_BTN_MANUAL_POL_ALIGN_MOVE_OK_REPLY_DN_POL_SET, &CManualPolSubDlg::OnBnClickedBtnSetDnPolAlignMoveOkReply)
														  
	ON_BN_CLICKED(IDC_BTN_MANUAL_POL_ALIGN_MOVE_OK_REPLY_UP_POL_SET, &CManualPolSubDlg::OnBnClickedBtnSetUpPolAlignMoveOkReply)
	ON_BN_CLICKED(IDC_BTN_MANUAL_POL_ALIGN_OK_DN_POL_SET, &CManualPolSubDlg::OnBnClickedBtnSetDnPolAlignOk)
														  
	ON_BN_CLICKED(IDC_BTN_MANUAL_POL_ALIGN_ALIGN_OK_UP_SET, &CManualPolSubDlg::OnBnClickedBtnSetUpPolAlignOk)
														   
	ON_BN_CLICKED(IDC_BTN_MANUAL_POL_UP_DDMOTOR_RUN_SET, &CManualPolSubDlg::OnBnClickedBtnSetUpDdMotorRun)
	ON_BN_CLICKED(IDC_BTN_MANUAL_POL_DN_DDMOTOR_RUN_SET, &CManualPolSubDlg::OnBnClickedBtnSetDnDdMotorRun)

	ON_BN_CLICKED(IDC_BTN_MANUAL_POL_WRITE_POL_ADJUST_POS_UP, &CManualPolSubDlg::OnBnClickedBtnWriteUpPolAxisAdjustPos)												   
	ON_BN_CLICKED(IDC_BTN_MANUAL_POL_WRITE_POL_ADJUST_POS_DN, &CManualPolSubDlg::OnBnClickedBtnWriteDnPolAxisAdjustPos)
	ON_BN_CLICKED(IDC_BTN_MANUAL_POL_WRITE_POL_OFFSET_UP, &CManualPolSubDlg::OnBnClickedBtnWriteUpPolOffset)
	ON_BN_CLICKED(IDC_BTN_MANUAL_POL_WRITE_POL_OFFSET_DN, &CManualPolSubDlg::OnBnClickedBtnWriteDnPolOffset)
	ON_BN_CLICKED(IDC_BTN_MANUAL_POL_ACCUMULAT_MOVE_VALUE_UP, &CManualPolSubDlg::OnBnClickedBtnWriteUpDdAccumulateMoveValue)
	ON_BN_CLICKED(IDC_BTN_MANUAL_POL_ACCUMULAT_MOVE_VALUE_DN, &CManualPolSubDlg::OnBnClickedBtnWriteDnDdAccumulateMoveValue)





END_MESSAGE_MAP()


// CManualPolSubDlg 메시지 처리기입니다.


BOOL CManualPolSubDlg::OnInitDialog()
{
	m_Edit_StageWriteUpPolPosX.SubclassDlgItem(IDC_EDIT_MANUAL_POL_WRITE_UP_POL_POS_X, this);
	m_Edit_StageWriteUpPolPosY.SubclassDlgItem(IDC_EDIT_MANUAL_POL_WRITE_UP_POL_POS_Y, this);
	m_Edit_StageWriteUpPolPosT.SubclassDlgItem(IDC_EDIT_MANUAL_POL_WRITE_UP_POL_POS_T, this);
																									   
	m_Edit_StageWriteDnPolPosX.SubclassDlgItem(IDC_EDIT_MANUAL_POL_WRITE_DN_POL_POS_X, this);
	m_Edit_StageWriteDnPolPosY.SubclassDlgItem(IDC_EDIT_MANUAL_POL_WRITE_DN_POL_POS_Y, this);
	m_Edit_StageWriteDnPolPosT.SubclassDlgItem(IDC_EDIT_MANUAL_POL_WRITE_DN_POL_POS_T, this);

	m_Edit_StageAccumluteMoveValueUp.SubclassDlgItem(IDC_EDIT_MANUAL_POL_ACCUMULATE_MOVE_UP, this);
	m_Edit_StageAccumluteMoveValueDn.SubclassDlgItem(IDC_EDIT_MANUAL_POL_ACCUMULATE_MOVE_DN, this);
	m_Edit_StagePolOffsetUp.SubclassDlgItem(IDC_EDIT_MANUAL_POL_POL_OFFSET_UP, this);
	m_Edit_StagePolOffsetDn.SubclassDlgItem(IDC_EDIT_MANUAL_POL_POL_OFFSET_DN, this);

	m_Edit_StageUpPolPosX.SubclassDlgItem(IDC_EDIT_MANUAL_STAGE_UP_POL_POS_X, this);
	m_Edit_StageUpPolPosY.SubclassDlgItem(IDC_EDIT_MANUAL_STAGE_UP_POL_POS_Y, this);
	m_Edit_StageUpPolPosT.SubclassDlgItem(IDC_EDIT_MANUAL_STAGE_UP_POL_POS_T, this);
																							   
	m_Edit_StageDnPolPosX.SubclassDlgItem(IDC_EDIT_MANUAL_STAGE_DOWN_POL_POS_X, this);
	m_Edit_StageDnPolPosY.SubclassDlgItem(IDC_EDIT_MANUAL_STAGE_DOWN_POL_POS_Y, this);
	m_Edit_StageDnPolPosT.SubclassDlgItem(IDC_EDIT_MANUAL_STAGE_DOWN_POL_POS_T, this);

	m_stcIsDnPolAlignRunCmd.SubclassDlgItem(IDC_STC_MANUAL_POL_ALIGN_RUN_CMD_DN_POL, this);
	m_stcIsUpPolAlignRunCmd.SubclassDlgItem(IDC_STC_MANUAL_POL_ALIGN_RUN_CMD_UP_POL, this);

	m_stcIsDnPolAlignMoveDone.SubclassDlgItem(IDC_STC_MANUAL_POL_ALIGN_MOVE_DONE_DN_POL, this);
	m_stcIsUpPolAlignMoveDone.SubclassDlgItem(IDC_STC_MANUAL_POL_ALIGN_MOVE_DONE_UP_POL, this);
																									
	m_stcIsDnPolAlignResetCmd.SubclassDlgItem(IDC_STC_MANUAL_POL_ALIGN_RESET_CMD_DN_POL, this);
	m_stcIsUpPolAlignResetCmd.SubclassDlgItem(IDC_STC_MANUAL_POL_ALIGN_RESET_CMD_UP_POL, this);
																									
	m_stcIsDnPolAlignProcessing.SubclassDlgItem(IDC_STC_MANUAL_POL_ALIGN_PROCESSING_DN_POL, this);
	m_stcIsUpPolAlignProcessing.SubclassDlgItem(IDC_STC_MANUAL_POL_ALIGN_PROCESSING_UP_POL, this);

	m_stcIsDnPolAlignDone.SubclassDlgItem(IDC_STC_MANUAL_POL_ALIGN_DONE_DN_POL, this);
	m_stcIsUpPolAlignDone.SubclassDlgItem(IDC_STC_MANUAL_POL_ALIGN_DONE_UP_POL, this);

	m_stcIsRecipeChangeCmd.SubclassDlgItem(IDC_STC_MANUAL_POL_RECIPE_CHANGE_CMD, this);
	m_stcIsRecipeDeleteCmd.SubclassDlgItem(IDC_STC_MANUAL_POL_RECIPE_DELETE_CMD, this);
	m_stcIsRecipeAddCmd.SubclassDlgItem(IDC_STC_MANUAL_POL_RECIPE_ADD_CMD, this);



	//XH 20191112
	m_stcDdMotorRunUp.SubclassDlgItem(IDC_STC_MANUAL_POL_DD_MOTOR_RUN_UP, this);
	m_stcDdMotorRunDn.SubclassDlgItem(IDC_STC_MANUAL_POL_DD_MOTOR_RUN_DN, this);

	m_stcAlignMarkFindOkUp.SubclassDlgItem(IDC_STC_MANUAL_POL_ALIGN_MARK_FIND_OK_UP, this);
	m_stcAlignMarkFindOkDn.SubclassDlgItem(IDC_STC_MANUAL_POL_ALIGN_MARK_FIND_OK_DN, this);

	m_stcAlignBusyUp.SubclassDlgItem(IDC_STC_MANUAL_POL_ALIGN_BUSY_UP, this);
	m_stcAlignBusyDn.SubclassDlgItem(IDC_STC_MANUAL_POL_ALIGN_BUSY_DN, this);

	m_stcAlignNgUp.SubclassDlgItem(IDC_STC_MANUAL_POL_ALIGN_NG_UP, this);
	m_stcAlignNgDn.SubclassDlgItem(IDC_STC_MANUAL_POL_ALIGN_NG_DN, this);

	m_stcAlignOkUp.SubclassDlgItem(IDC_STC_MANUAL_POL_ALIGN_ALIGN_OK_UP, this);
	m_stcAlignOkDn.SubclassDlgItem(IDC_STC_MANUAL_POL_ALIGN_ALIGN_OK_DN, this);

	m_stcAlignMoveOkReplyUp.SubclassDlgItem(IDC_STC_MANUAL_POL_ALIGN_MOVE_OK_REPLY_UP, this);
	m_stcAlignMoveOkReplyDn.SubclassDlgItem(IDC_STC_MANUAL_POL_ALIGN_MOVE_OK_REPLY_DN, this);


	CString strTemp1 = _T("Input");
	m_Edit_StageWriteUpPolPosX.SetWindowTextW(strTemp1);
	m_Edit_StageWriteUpPolPosY.SetWindowTextW(strTemp1);
	m_Edit_StageWriteUpPolPosT.SetWindowTextW(strTemp1);
	m_Edit_StageWriteDnPolPosX.SetWindowTextW(strTemp1);
	m_Edit_StageWriteDnPolPosY.SetWindowTextW(strTemp1);
	m_Edit_StageWriteDnPolPosT.SetWindowTextW(strTemp1);

	m_Edit_StageAccumluteMoveValueUp.SetWindowTextW(strTemp1);
	m_Edit_StageAccumluteMoveValueDn.SetWindowTextW(strTemp1);
	m_Edit_StagePolOffsetUp.SetWindowTextW(strTemp1);
	m_Edit_StagePolOffsetDn.SetWindowTextW(strTemp1);


	//




	return 0;
}

void CManualPolSubDlg::OnShowWindow(BOOL bShow, UINT nStatus)
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

void CManualPolSubDlg::OnTimer(UINT_PTR nIDEvent)
{
	CString strTemp = _T("");
	
	DOUBLE dX = 0, dY = 0, dT = 0;
	DOUBLE dX1 = 0, dY1 = 0, dX2 = 0, dY2 = 0;

	Devs::m_StageMotion.ReadUpPolMotorPos(&dX, &dY, &dT);

	strTemp.Format(_T("%.5f"), dX);
	m_Edit_StageUpPolPosX.SetWindowTextW(strTemp);

	strTemp.Format(_T("%.5f"), dY);
	m_Edit_StageUpPolPosY.SetWindowTextW(strTemp);

	strTemp.Format(_T("%.5f"), dT);
	m_Edit_StageUpPolPosT.SetWindowTextW(strTemp);

	Devs::m_StageMotion.ReadDnPolMotorPos(&dX, &dY, &dT);

	strTemp.Format(_T("%.5f"), dX);
	m_Edit_StageDnPolPosX.SetWindowTextW(strTemp);

	strTemp.Format(_T("%.5f"), dY);
	m_Edit_StageDnPolPosY.SetWindowTextW(strTemp);

	strTemp.Format(_T("%.5f"), dT);
	m_Edit_StageDnPolPosT.SetWindowTextW(strTemp);






	if (Devs::m_StageMotion.IsDnPolAlignRunCmd())
	{
		m_stcIsDnPolAlignRunCmd.SetBackgroundColor(GREEN);
	}
	else
	{
		m_stcIsDnPolAlignRunCmd.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsUpPolAlignRunCmd())
	{
		m_stcIsUpPolAlignRunCmd.SetBackgroundColor(GREEN);
	}

	else
	{
		m_stcIsUpPolAlignRunCmd.SetBackgroundColor(BTN_LAMP_OFF);
	}
	//
	if (Devs::m_StageMotion.IsDnPolAlignMoveDone())
	{
		m_stcIsDnPolAlignMoveDone.SetBackgroundColor(GREEN);
	}

	else
	{
		m_stcIsDnPolAlignMoveDone.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsUpPolAlignMoveDone())
	{
		m_stcIsUpPolAlignMoveDone.SetBackgroundColor(GREEN);
	}

	else
	{
		m_stcIsUpPolAlignMoveDone.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsDnPolAlignResetCmd())
	{
		m_stcIsDnPolAlignResetCmd.SetBackgroundColor(GREEN);
	}

	else
	{
		m_stcIsDnPolAlignResetCmd.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsUpPolAlignResetCmd())
	{
		m_stcIsUpPolAlignResetCmd.SetBackgroundColor(GREEN);
	}

	else
	{
		m_stcIsUpPolAlignResetCmd.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsDnPolAlignProcessing())
	{
		m_stcIsDnPolAlignProcessing.SetBackgroundColor(GREEN);
	}

	else
	{
		m_stcIsDnPolAlignProcessing.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsUpPolAlignProcessing())
	{
		m_stcIsUpPolAlignProcessing.SetBackgroundColor(GREEN);
	}

	else
	{
		m_stcIsUpPolAlignProcessing.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsDnPolAlignDone())
	{
		m_stcIsDnPolAlignDone.SetBackgroundColor(GREEN);
	}

	else
	{
		m_stcIsDnPolAlignDone.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsUpPolAlignDone())
	{
		m_stcIsUpPolAlignDone.SetBackgroundColor(GREEN);
	}

	else
	{
		m_stcIsUpPolAlignDone.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_WorkInfoMotion.IsRecipeChangeCmd())
	{
		m_stcIsRecipeChangeCmd.SetBackgroundColor(GREEN);
	}

	else
	{
		m_stcIsRecipeChangeCmd.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_WorkInfoMotion.IsRecipeDeleteCmd())
	{
		m_stcIsRecipeDeleteCmd.SetBackgroundColor(GREEN);
	}

	else
	{
		m_stcIsRecipeDeleteCmd.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_WorkInfoMotion.IsRecipeAddCmd())
	{
		m_stcIsRecipeAddCmd.SetBackgroundColor(GREEN);
	}

	else
	{
		m_stcIsRecipeAddCmd.SetBackgroundColor(BTN_LAMP_OFF);
	}



	//
	if (Devs::m_StageMotion.IsDnPolAlignMarkFindOk() == 1)
	{
		m_stcAlignMarkFindOkDn.SetBackgroundColor(GREEN);
	}
	else
	{
		m_stcAlignMarkFindOkDn.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsUpPolAlignMarkFindOk() == 1)
	{
		m_stcAlignMarkFindOkUp.SetBackgroundColor(GREEN);
	}
	else
	{
		m_stcAlignMarkFindOkUp.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsDnPolAlignBusy() == 1)
	{
		m_stcAlignBusyDn.SetBackgroundColor(GREEN);
	}
	else
	{
		m_stcAlignBusyDn.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsUpPolAlignBusy() == 1)
	{
		m_stcAlignBusyUp.SetBackgroundColor(GREEN);
	}
	else
	{
		m_stcAlignBusyUp.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsDnPolAlignNg() == 1)
	{
		m_stcAlignNgDn.SetBackgroundColor(GREEN);
	}
	else
	{
		m_stcAlignNgDn.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsUpPolAlignNg() == 1)
	{
		m_stcAlignNgUp.SetBackgroundColor(GREEN);
	}
	else
	{
		m_stcAlignNgUp.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsDnPolAlignMoveOkReply() == 1)
	{
		m_stcAlignMoveOkReplyDn.SetBackgroundColor(GREEN);
	}
	else
	{
		m_stcAlignMoveOkReplyDn.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsUpPolAlignMoveOkReply() == 1)
	{
		m_stcAlignMoveOkReplyUp.SetBackgroundColor(GREEN);
	}
	else
	{
		m_stcAlignMoveOkReplyUp.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsDnPolAlignOk() == 1)
	{
		m_stcAlignOkDn.SetBackgroundColor(GREEN);
	}
	else
	{
		m_stcAlignOkDn.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsUpPolAlignOk() == 1)
	{
		m_stcAlignOkUp.SetBackgroundColor(GREEN);
	}
	else
	{
		m_stcAlignOkUp.SetBackgroundColor(BTN_LAMP_OFF);
	}


	if (Devs::m_StageMotion.IsUpDdMotorRun() == 1)
	{
		m_stcDdMotorRunUp.SetBackgroundColor(GREEN);
	}
	else
	{
		m_stcDdMotorRunUp.SetBackgroundColor(BTN_LAMP_OFF);
	}

	if (Devs::m_StageMotion.IsDnDdMotorRun() == 1)
	{
		m_stcDdMotorRunDn.SetBackgroundColor(GREEN);
	}
	else
	{
		m_stcDdMotorRunDn.SetBackgroundColor(BTN_LAMP_OFF);
	}


}

void CManualPolSubDlg::OnEnChangeEditManualStagePolOffsetDn()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CManualPolSubDlg::OnBnClickedBtnSetDnPolAlignMarkFindOk()
{
	if (Devs::m_StageMotion.IsDnPolAlignMarkFindOk() ==0)
	{
		Devs::m_StageMotion.SetDnPolAlignMarkFindOk();
	}
	else
	{
		Devs::m_StageMotion.ResetDnPolAlignMarkFindOk();
	}
}

void CManualPolSubDlg::OnBnClickedBtnSetUpPolAlignMarkFindOk()
{
	if (Devs::m_StageMotion.IsUpPolAlignMarkFindOk() == 0)
	{
		Devs::m_StageMotion.SetUpPolAlignMarkFindOk();
	}
	else
	{
		Devs::m_StageMotion.ResetUpPolAlignMarkFindOk();
	}
}

void CManualPolSubDlg::OnBnClickedBtnSetDnPolAlignBusy()
{
	if (Devs::m_StageMotion.IsDnPolAlignBusy() == 0)
	{
		Devs::m_StageMotion.SetDnPolAlignBusy();
	}
	else
	{
		Devs::m_StageMotion.ResetDnPolAlignBusy();
	}
}



void CManualPolSubDlg::OnBnClickedBtnSetUpPolAlignBusy()
{
	if (Devs::m_StageMotion.IsUpPolAlignBusy() == 0)
	{
		Devs::m_StageMotion.SetUpPolAlignBusy();
	}
	else
	{
		Devs::m_StageMotion.ResetUpPolAlignBusy();
	}
}

void CManualPolSubDlg::OnBnClickedBtnSetDnPolAlignNg()
{
	if (Devs::m_StageMotion.IsDnPolAlignNg() == 0)
	{
		Devs::m_StageMotion.SetDnPolAlignNg();
	}
	else
	{
		Devs::m_StageMotion.ResetDnPolAlignNg();
	}
	
}



void CManualPolSubDlg::OnBnClickedBtnSetUpPolAlignNg()
{
	if (Devs::m_StageMotion.IsUpPolAlignNg() == 0)
	{
		Devs::m_StageMotion.SetUpPolAlignNg();
	}
	else
	{
		Devs::m_StageMotion.ResetUpPolAlignNg();
	}

}

void CManualPolSubDlg::OnBnClickedBtnSetDnPolAlignMoveOkReply()
{
	if (Devs::m_StageMotion.IsDnPolAlignMoveOkReply() == 0)
	{
		Devs::m_StageMotion.SetDnPolAlignMoveOkReply();
	}
	else
	{
		Devs::m_StageMotion.ResetDnPolAlignMoveOkReply();
	}
}

void CManualPolSubDlg::OnBnClickedBtnSetUpPolAlignMoveOkReply()
{
	if (Devs::m_StageMotion.IsUpPolAlignMoveOkReply() == 0)
	{
		Devs::m_StageMotion.SetUpPolAlignMoveOkReply();
	}
	else
	{
		Devs::m_StageMotion.ResetUpPolAlignMoveOkReply();
	}
}

void CManualPolSubDlg::OnBnClickedBtnSetDnPolAlignOk()
{
	if (Devs::m_StageMotion.IsDnPolAlignOk() == 0)
	{
		Devs::m_StageMotion.SetDnPolAlignOk();
	}
	else
	{
		Devs::m_StageMotion.ResetDnPolAlignOk();
	}
}

void CManualPolSubDlg::OnBnClickedBtnSetUpPolAlignOk()
{
	if (Devs::m_StageMotion.IsUpPolAlignOk() == 0)
	{
		Devs::m_StageMotion.SetUpPolAlignOk();
	}
	else
	{
		Devs::m_StageMotion.ResetUpPolAlignOk();
	}
}

void CManualPolSubDlg::OnBnClickedBtnSetUpDdMotorRun()
{
	if (Devs::m_StageMotion.IsUpDdMotorRun() == 0)
	{
		Devs::m_StageMotion.SetUpDdMotorRun();
	}
	else
	{
		Devs::m_StageMotion.ResetUpDdMotorRun();
	}
}

void CManualPolSubDlg::OnBnClickedBtnSetDnDdMotorRun()
{
	if (Devs::m_StageMotion.IsDnDdMotorRun() == 0)
	{
		Devs::m_StageMotion.SetDnDdMotorRun();
	}
	else
	{
		Devs::m_StageMotion.ResetDnDdMotorRun();
	}
}



void CManualPolSubDlg::OnBnClickedBtnWriteUpPolAxisAdjustPos()
{
	CString strX = _T("");
	CString strY = _T("");
	CString strT = _T("");

	m_Edit_StageWriteUpPolPosX.GetWindowTextW(strX);
	m_Edit_StageWriteUpPolPosY.GetWindowTextW(strY);
	m_Edit_StageWriteUpPolPosT.GetWindowTextW(strT);

	double dX = _ttof(strX), dY = _ttof(strY), dT = _ttof(strT);
	Devs::m_StageMotion.WriteUpPolAxisAdjustPos(dX, dY, dT);
}

void CManualPolSubDlg::OnBnClickedBtnWriteDnPolAxisAdjustPos()
{
	CString strX = _T("");
	CString strY = _T("");
	CString strT = _T("");

	m_Edit_StageWriteDnPolPosX.GetWindowTextW(strX);
	m_Edit_StageWriteDnPolPosY.GetWindowTextW(strY);
	m_Edit_StageWriteDnPolPosT.GetWindowTextW(strT);

	double dX = _ttof(strX), dY = _ttof(strY), dT = _ttof(strT);
	Devs::m_StageMotion.WriteUpPolAxisAdjustPos(dX, dY, dT);
}
void CManualPolSubDlg::OnBnClickedBtnWriteUpPolOffset()
{
	DOUBLE dResultX, dResultY, dResultT;
	CString strOffset = _T("");
	m_Edit_StagePolOffsetUp.GetWindowTextW(strOffset);

	Devs::m_StageMotion.ReadUpPolMotorPos(&dResultX, &dResultY, &dResultT);

	double dOffset = _ttof(strOffset) + dResultT;
	
	Devs::m_StageMotion.WriteUpPolOffset(dOffset);
}

void CManualPolSubDlg::OnBnClickedBtnWriteDnPolOffset()
{
	DOUBLE dResultX, dResultY, dResultT;
	CString strOffset = _T("");
	m_Edit_StagePolOffsetDn.GetWindowTextW(strOffset);

	Devs::m_StageMotion.ReadDnPolMotorPos(&dResultX, &dResultY, &dResultT);

	double dOffset = _ttof(strOffset) + dResultT;

	Devs::m_StageMotion.WriteDnPolOffset(dOffset);
}

void CManualPolSubDlg::OnBnClickedBtnWriteUpDdAccumulateMoveValue()
{
	CString strOffset = _T("");
	m_Edit_StageAccumluteMoveValueUp.GetWindowTextW(strOffset);
	double dOffset = _ttof(strOffset);

	Devs::m_StageMotion.WriteUpDdAccumulateMoveValue(dOffset);
}

void CManualPolSubDlg::OnBnClickedBtnWriteDnDdAccumulateMoveValue()
{
	CString strOffset = _T("");
	m_Edit_StageAccumluteMoveValueDn.GetWindowTextW(strOffset);
	double dOffset = _ttof(strOffset);

	Devs::m_StageMotion.WriteDnDdAccumulateMoveValue(dOffset);
}
