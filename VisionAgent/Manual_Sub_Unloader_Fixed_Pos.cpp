// Manual_Sub_Unloader_Fixed_Pos.cpp: 구현 파일
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "Manual_Sub_Unloader_Fixed_Pos.h"
#include "afxdialogex.h"


// CManual_Sub_Unloader_Fixed_Pos 대화 상자

IMPLEMENT_DYNAMIC(CManual_Sub_Unloader_Fixed_Pos, CDialogEx)

CManual_Sub_Unloader_Fixed_Pos::CManual_Sub_Unloader_Fixed_Pos(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_MANUAL_SUB_UNLOADER_FIXED_POS, pParent)
{
	Create(IDD_DLG_MANUAL_SUB_UNLOADER_FIXED_POS, pParent);
}

CManual_Sub_Unloader_Fixed_Pos::~CManual_Sub_Unloader_Fixed_Pos()
{
}

void CManual_Sub_Unloader_Fixed_Pos::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CManual_Sub_Unloader_Fixed_Pos, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_GET_WAIT_POS_UNLOADER_Y, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderGetWaitPosUnloaderY)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_GET_LOAD_IN_STAGE_POS_UNLOADER_Y, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderGetLoadInStagePosUnloaderY)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_GET_UNLOAD_TO_CST_POS_UNLOADER_Y, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderGetUnloadToCstPosUnloaderY)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_GET_LOAD_IN_CST_POS_UNLOADER_Y, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderGetLoadInCstPosUnloaderY)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_GET_UNLOAD_TO_STAGE_POS_UNLOADER_Y, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderGetUnloadToStagePosUnloaderY)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_GET_WAIT_POS_UNLOADER_X, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderGetWaitPosUnloaderX)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_GET_WAIT_POS_UNLOADER_Z, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderGetWaitPosUnloaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_GET_LOAD_IN_STAGE_POS_UNLOADER_Z, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderGetLoadInStagePosUnloaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_GET_UNLOAD_TO_CST_POS_UNLOADER_Z, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderGetUnloadToCstPosUnloaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_GET_LOAD_IN_CST_POS_UNLOADER_Z, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderGetLoadInCstPosUnloaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_GET_UNLOAD_TO_STAGE_POS_UNLOADER_Z, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderGetUnloadToStagePosUnloaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_SET_WAIT_POS_UNLOADER_Y, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetWaitPosUnloaderY)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_SET_LOAD_IN_STAGE_POS_UNLOADER_Y, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetLoadInStagePosUnloaderY)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_SET_UNLOAD_TO_CST_POS_UNLOADER_Y, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetUnloadToCstPosUnloaderY)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_SET_LOAD_IN_CST_POS_UNLOADER_Y, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetLoadInCstPosUnloaderY)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_SET_UNLOAD_TO_STAGE_POS_UNLOADER_Y, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetUnloadToStagePosUnloaderY)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_SET_WAIT_POS_UNLOADER_X, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetWaitPosUnloaderX)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_SET_WAIT_POS_UNLOADER_Z, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetWaitPosUnloaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_SET_LOAD_IN_STAGE_POS_UNLOADER_Z, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetLoadInStagePosUnloaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_SET_UNLOAD_TO_CST_POS_UNLOADER_Z, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetUnloadToCstPosUnloaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_SET_LOAD_IN_CST_POS_UNLOADER_Z, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetLoadInCstPosUnloaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_SET_UNLOAD_TO_STAGE_POS_UNLOADER_Z, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetUnloadToStagePosUnloaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MOVE_WAIT_POS_UNLOADER_Y, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderMoveWaitPosUnloaderY)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MOVE_LOAD_IN_STAGE_POS_UNLOADER_Y, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderMoveLoadInStagePosUnloaderY)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MOVE_UNLOAD_TO_CST_POS_UNLOADER_Y, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderMoveUnloadToCstPosUnloaderY)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MOVE_LOAD_IN_CST_POS_UNLOADER_Y, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderMoveLoadInCstPosUnloaderY)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MOVE_UNLOAD_TO_STAGE_POS_UNLOADER_Y, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderMoveUnloadToStagePosUnloaderY)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MOVE_WAIT_POS_UNLOADER_X, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderMoveWaitPosUnloaderX)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MOVE_WAIT_POS_UNLOADER_Z, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderMoveWaitPosUnloaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MOVE_LOAD_IN_STAGE_POS_UNLOADER_Z, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderMoveLoadInStagePosUnloaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MOVE_UNLOAD_TO_CST_POS_UNLOADER_Z, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderMoveUnloadToCstPosUnloaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MOVE_LOAD_IN_CST_POS_UNLOADER_Z, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderMoveLoadInCstPosUnloaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MOVE_UNLOAD_TO_STAGE_POS_UNLOADER_Z, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderMoveUnloadToStagePosUnloaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_FIXED_SAVE, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderFixedSave)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_SET_STEP_DOWN_OFFSET_UNLOADER_Z, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetStepDownOffsetUnloaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_SET_TENSION_OFFSET_UNLOADER_X, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetTensionOffsetUnloaderX)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_GET_LOAD_PAPER_POS_UNLOADER_Z, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderGetLoadPaperPosUnloaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_GET_UNLOAD_PAPER_POS_UNLOADER_Z, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderGetUnloadPaperPosUnloaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_GET_UNLOAD_PAPER_POS_UNLOADER_Y, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderGetUnloadPaperPosUnloaderY)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_GET_LOAD_PAPER_POS_UNLOADER_Y, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderGetLoadPaperPosUnloaderY)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_SET_LOAD_PAPER_POS_UNLOADER_Z, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetLoadPaperPosUnloaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_SET_UNLOAD_PAPER_POS_UNLOADER_Z, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetUnloadPaperPosUnloaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_SET_LOAD_PAPER_POS_UNLOADER_Y, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetLoadPaperPosUnloaderY)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_SET_UNLOAD_PAPER_POS_UNLOADER_Y, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetUnloadPaperPosUnloaderY)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MOVE_LOAD_PAPER_POS_UNLOADER_Z, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderMoveLoadPaperPosUnloaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MOVE_UNLOAD_PAPER_POS_UNLOADER_Z, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderMoveUnloadPaperPosUnloaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MOVE_LOAD_PAPER_POS_UNLOADER_Y, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderMoveLoadPaperPosUnloaderY)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MOVE_UNLOAD_PAPER_POS_UNLOADER_Y, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderMoveUnloadPaperPosUnloaderY)	
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MOVE_WAIT_POS_UNLOADER_ZL, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderMoveWaitPosUnloaderZl)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MOVE_DOWN_POS_UNLOADER_ZL, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderMoveDownPosUnloaderZl)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_GET_WAIT_POS_UNLOADER_ZL, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderGetWaitPosUnloaderZl)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_GET_DOWN_POS_UNLOADER_ZL, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderGetDownPosUnloaderZl)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_SET_WAIT_POS_UNLOADER_ZL, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetWaitPosUnloaderZl)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_SET_DOWN_POS_UNLOADER_ZL, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetDownPosUnloaderZl)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_GET_STICK_LOAD_IN_BOX_2ND_POS_LOADER_Z, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderGetStickLoadInBox2ndPosLoaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_SET_STICK_LOAD_IN_BOX_2ND_POS_LOADER_Z, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetStickLoadInBox2ndPosLoaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MOVE_STICK_LOAD_IN_BOX_2ND_POS_LOADER_Z, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderMoveStickLoadInBox2ndPosLoaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_SET_STICK_LOAD_IN_STAGE_2ND_POS_LOADER_Z, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetStickLoadInStage2ndPosLoaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_GET_CASSETTE_SAFETY_POS_UNLOADER_Y, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderGetCassetteSafetyPosUnloaderY)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_SET_CASSETTE_SAFETY_POS_UNLOADER_Y, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetCassetteSafetyPosUnloaderY)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MOVE_CASSETTE_SAFETY_POS_UNLOADER_Y, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderMoveCassetteSafetyPosUnloaderY)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_SET_STEP_DOWN_COUNT, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetStepDownCount)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_SET_STEP_UP_OFFSET_UNLOADER_Z, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetStepUpOffsetUnloaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_SET_VIBRATION_COUNT, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetVibrationCount)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_SET_VIBRATION_VEL, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetVibrationVel)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_GET_PAPER_LOAD_POS_UNLOADER_ZL, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderGetPaperLoadPosUnloaderZl)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_GET_PAPER_UNLOAD_POS_UNLOADER_ZL, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderGetPaperUnloadPosUnloaderZl)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_SET_PAPER_LOAD_POS_UNLOADER_ZL, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetPaperLoadPosUnloaderZl)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_SET_PAPER_UNLOAD_POS_UNLOADER_ZL, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetPaperUnloadPosUnloaderZl)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MOVE_PAPER_LOAD_POS_UNLOADER_ZL, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderMovePaperLoadPosUnloaderZl)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MOVE_PAPER_UNLOAD_POS_UNLOADER_ZL, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderMovePaperUnloadPosUnloaderZl)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_GET_WAIT_POS_PAPER_UNLOADER_XL, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderGetWaitPosPaperUnloaderXl)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_SET_WAIT_POS_PAPER_UNLOADER_XL, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetWaitPosPaperUnloaderXl)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_SET_TENSION_OFFSET_PAPER_UNLOADER_XL, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetTensionOffsetPaperUnloaderXl)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MOVE_WAIT_POS_PAPER_UNLOADER_XL, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderMoveWaitPosPaperUnloaderXl)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_GET_LOAD_PAPER_WAITING_POS_UNLOADER_Y, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderGetLoadPaperWaitingPosUnloaderY)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_SET_LOAD_PAPER_WAITING_POS_UNLOADER_Y, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetLoadPaperWaitingPosUnloaderY)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MOVE_LOAD_PAPER_WAITING_POS_UNLOADER_Y, &CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderMoveLoadPaperWaitingPosUnloaderY)
END_MESSAGE_MAP()


// CManual_Sub_Unloader_Fixed_Pos 메시지 처리기

BOOL CManual_Sub_Unloader_Fixed_Pos::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	InitCtrl();

	return TRUE;
}

//------------------------------------------------------------------
void CManual_Sub_Unloader_Fixed_Pos::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow == TRUE)
	{
		InitPara();

		//SetTimer(1, 100, NULL);
	}
	else if (bShow == FALSE)
	{
		//KillTimer(1);
	}
}
//------------------------------------------------------------------
void CManual_Sub_Unloader_Fixed_Pos::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (Is_Comp_Usable() == FALSE)	return;
	int nOffset = 5;
	CRect	RectSaveBtn;
	int		nBtnSize_X = 100;
	int		nBtnSize_Y = 50;
	RectSaveBtn.left = cx - nOffset - nBtnSize_X;
	RectSaveBtn.top = cy - nOffset - nBtnSize_Y;
	RectSaveBtn.right = cx - nOffset;
	RectSaveBtn.bottom = cy - nOffset;
	GetDlgItem(IDC_BUTTON_MANUAL_SUB_UNLOADER_FIXED_SAVE)->MoveWindow(RectSaveBtn);
}
//------------------------------------------------------------------
void CManual_Sub_Unloader_Fixed_Pos::OnTimer(UINT_PTR nIDEvent)
{
	//if (Devs::m_JogMotion.IsMotionDone(AXIS_LOADING_STAGE_X1) == TRUE)

	CDialogEx::OnTimer(nIDEvent);
}
//------------------------------------------------------------------
void	CManual_Sub_Unloader_Fixed_Pos::InitCtrl()
{
	//Paper Unloader Y
	m_stcPos[_eUNLOADER_Y_WAIT_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_UNLOADER_CURRENT_WAIT_POS_UNLOADER_Y, this);
	m_stcPos[_eUNLOADER_Y_LOAD_IN_STAGE_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_UNLOADER_CURRENT_LOAD_IN_STAGE_POS_UNLOADER_Y, this);
	m_stcPos[_eUNLOADER_Y_UNLOAD_TO_CST_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_UNLOADER_CURRENT_UNLOAD_TO_CST_POS_UNLOADER_Y, this);
	m_stcPos[_eUNLOADER_Y_LOAD_IN_CST_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_UNLOADER_CURRENT_LOAD_IN_CST_POS_UNLOADER_Y, this);
	m_stcPos[_eUNLOADER_Y_UNLOAD_TO_STAGE_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_UNLOADER_CURRENT_UNLOAD_TO_STAGE_POS_UNLOADER_Y, this);

	//Paper Unloader X
	m_stcPos[_ePAPER_UNLOADER_XL_WAIT_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_UNLOADER_CURRENT_WAIT_POS_PAPER_UNLOADER_XL, this);
	m_stcPos[_ePAPER_UNLOADER_XL_TENSION_OFFSET].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_UNLOADER_CURRENT_TENSION_OFFSET_PAPER_UNLOADER_XL, this);

	//Mask Unloader X
	m_stcPos[_eUNLOADER_X_WAIT_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_UNLOADER_CURRENT_WAIT_POS_UNLOADER_X, this);
	m_stcPos[_eUNLOADER_X_TENSION_OFFSET].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_UNLOADER_CURRENT_TENSION_OFFSET_UNLOADER_X, this);

	m_stcPos[_eUNLOADER_Z_WAIT_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_UNLOADER_CURRENT_WAIT_POS_UNLOADER_Z, this);
	m_stcPos[_eUNLOADER_Z_LOAD_IN_STAGE_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_UNLOADER_CURRENT_LOAD_IN_STAGE_POS_UNLOADER_Z, this);
	m_stcPos[_eUNLOADER_Z_UNLOAD_TO_CST_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_UNLOADER_CURRENT_UNLOAD_TO_CST_POS_UNLOADER_Z, this);
	m_stcPos[_eUNLOADER_Z_LOAD_IN_CST_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_UNLOADER_CURRENT_LOAD_IN_CST_POS_UNLOADER_Z, this);
	m_stcPos[_eUNLOADER_Z_UNLOAD_TO_STAGE_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_UNLOADER_CURRENT_UNLOAD_TO_STAGE_POS_UNLOADER_Z, this);

	m_stcPos[_eUNLOADER_Z_STEP_DOWN_COUNT].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_UNLOADER_STEP_DOWN_COUNT, this);
	m_stcPos[_eUNLOADER_Z_STEP_DOWN_OFFSET].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_UNLOADER_CURRENT_STEP_DOWN_OFFSET_UNLOADER_Z, this);
	m_stcPos[_eUNLOADER_Z_STEP_UP_OFFSET].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_UNLOADER_STEP_UP_OFFSET_UNLOADER_Z, this);
	m_stcPos[_eUNLOADER_Z_VIBRATION_COUNT].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_UNLOADER_VIBRATION_COUNT, this);
	m_stcPos[_eUNLOADER_Z_VIBRATION_VEL].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_UNLOADER_VIBRATION_VEL, this);
		
	//21.02.15 sjc
	m_stcPos[_eUNLOADER_Z_PAPER_LOAD_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_UNLOADER_CURRENT_LOAD_PAPER_POS_UNLOADER_Z, this);
	m_stcPos[_eUNLOADER_Z_PAPER_UNLOAD_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_UNLOADER_CURRENT_UNLOAD_PAPER_POS_UNLOADER_Z, this);

	m_stcPos[_eUNLOADER_Z_VIBRATION_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_UNLOADER_CURRENT_STICK_LOAD_IN_BOX_2ND_POS_LOADER_Z, this);
	m_stcPos[_eUNLOADER_Z_VIBRATION_OFFSET].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_UNLOADER_CURRENT_STICK_LOAD_IN_STAGE_2ND_POS_LOADER_Z, this);

	m_stcPos[_eUNLOADER_Y_PAPER_LOAD_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_UNLOADER_CURRENT_LOAD_PAPER_POS_UNLOADER_Y, this);
	m_stcPos[_eUNLOADER_Y_PAPER_LOAD_WAITING_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_UNLOADER_CURRENT_LOAD_PAPER_WAITING_POS_UNLOADER_Y, this);
	m_stcPos[_eUNLOADER_Y_PAPER_UNLOAD_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_UNLOADER_CURRENT_UNLOAD_PAPER_POS_UNLOADER_Y, this);
	m_stcPos[_eUNLOADER_Y_CASSETTE_SAFETY_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_UNLOADER_CURRENT_CASSETTE_SAFETY_POS_UNLOADER_Y, this);
	//
	//21.02.25 SJC
	m_stcPos[_ePAPER_UNLOADER_ZL_WAIT_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_UNLOADER_CURRENT_WAIT_POS_UNLOADER_ZL, this);
	m_stcPos[_ePAPER_UNLOADER_ZL_DOWN_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_UNLOADER_CURRENT_DOWN_POS_UNLOADER_ZL, this);
	//

	m_stcPos[_ePAPER_UNLOADER_ZL_PAPER_LOAD_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_UNLOADER_CURRENT_PAPER_LOAD_POS_UNLOADER_ZL, this);
	m_stcPos[_ePAPER_UNLOADER_ZL_PAPER_UNLOAD_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_UNLOADER_CURRENT_PAPER_UNLOAD_POS_UNLOADER_ZL, this);

	//Edit
	//Paper Unloader Y
	m_editPos[_eUNLOADER_Y_WAIT_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_UNLOADER_WAIT_POS_UNLOADER_Y, this);
	m_editPos[_eUNLOADER_Y_LOAD_IN_STAGE_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_UNLOADER_LOAD_IN_STAGE_POS_UNLOADER_Y, this);
	m_editPos[_eUNLOADER_Y_UNLOAD_TO_CST_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_UNLOADER_UNLOAD_TO_CST_POS_UNLOADER_Y, this);
	//21.02.15 SJC
	m_editPos[_eUNLOADER_Y_PAPER_LOAD_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_UNLOADER_LOAD_PAPER_POS_UNLOADER_Y, this);
	m_editPos[_eUNLOADER_Y_PAPER_LOAD_WAITING_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_UNLOADER_LOAD_PAPER_WAITING_POS_UNLOADER_Y, this);
	m_editPos[_eUNLOADER_Y_PAPER_UNLOAD_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_UNLOADER_UNLOAD_PAPER_POS_UNLOADER_Y, this);
	m_editPos[_eUNLOADER_Y_CASSETTE_SAFETY_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_UNLOADER_CASSETTE_SAFETY_POS_UNLOADER_Y, this);
	//
	m_editPos[_eUNLOADER_Y_LOAD_IN_CST_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_UNLOADER_LOAD_IN_CST_POS_UNLOADER_Y, this);
	m_editPos[_eUNLOADER_Y_UNLOAD_TO_STAGE_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_UNLOADER_UNLOAD_TO_STAGE_POS_UNLOADER_Y, this);

	//Paper Unloader X
	m_editPos[_ePAPER_UNLOADER_XL_WAIT_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_UNLOADER_WAIT_POS_PAPER_UNLOADER_XL, this);
	m_editPos[_ePAPER_UNLOADER_XL_TENSION_OFFSET].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_UNLOADER_TENSION_OFFSET_PAPER_UNLOADER_XL, this);	

	//Mask Unloader X
	m_editPos[_eUNLOADER_X_WAIT_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_UNLOADER_WAIT_POS_UNLOADER_X, this);
	m_editPos[_eUNLOADER_X_TENSION_OFFSET].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_UNLOADER_TENSION_OFFSET_UNLOADER_X, this);

	m_editPos[_eUNLOADER_Z_WAIT_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_UNLOADER_WAIT_POS_UNLOADER_Z, this);
	m_editPos[_eUNLOADER_Z_LOAD_IN_STAGE_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_UNLOADER_LOAD_IN_STAGE_POS_UNLOADER_Z, this);
	m_editPos[_eUNLOADER_Z_UNLOAD_TO_CST_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_UNLOADER_UNLOAD_TO_CST_POS_UNLOADER_Z, this);
	//21.02.15 SJC
	m_editPos[_eUNLOADER_Z_PAPER_LOAD_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_UNLOADER_LOAD_PAPER_POS_UNLOADER_Z, this);
	m_editPos[_eUNLOADER_Z_PAPER_UNLOAD_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_UNLOADER_UNLOAD_PAPER_POS_UNLOADER_Z, this);
	m_editPos[_eUNLOADER_Z_VIBRATION_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_UNLOADER_STICK_LOAD_IN_BOX_2ND_POS_LOADER_Z, this);
	m_editPos[_eUNLOADER_Z_VIBRATION_OFFSET].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_UNLOADER_STICK_LOAD_IN_STAGE_2ND_POS_LOADER_Z, this);
	//
	m_editPos[_eUNLOADER_Z_LOAD_IN_CST_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_UNLOADER_LOAD_IN_CST_POS_UNLOADER_Z, this);
	m_editPos[_eUNLOADER_Z_UNLOAD_TO_STAGE_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_UNLOADER_UNLOAD_TO_STAGE_POS_UNLOADER_Z, this);

	m_editPos[_eUNLOADER_Z_STEP_DOWN_COUNT].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_UNLOADER_STEP_DOWN_COUNT, this);
	m_editPos[_eUNLOADER_Z_STEP_DOWN_OFFSET].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_UNLOADER_STEP_DOWN_OFFSET_UNLOADER_Z, this);
	m_editPos[_eUNLOADER_Z_STEP_UP_OFFSET].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_UNLOADER_STEP_UP_OFFSET_UNLOADER_Z, this);
	m_editPos[_eUNLOADER_Z_VIBRATION_COUNT].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_UNLOADER_VIBRATION_COUNT, this);
	m_editPos[_eUNLOADER_Z_VIBRATION_VEL].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_UNLOADER_VIBRATION_VEL, this);
	
	//21.02.25 SJC
	m_editPos[_ePAPER_UNLOADER_ZL_WAIT_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_UNLOADER_WAIT_POS_UNLOADER_ZL, this);
	m_editPos[_ePAPER_UNLOADER_ZL_DOWN_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_UNLOADER_DOWN_POS_UNLOADER_ZL, this);
	//

	m_editPos[_ePAPER_UNLOADER_ZL_PAPER_LOAD_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_UNLOADER_PAPER_LOAD_POS_UNLOADER_ZL, this);
	m_editPos[_ePAPER_UNLOADER_ZL_PAPER_UNLOAD_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_UNLOADER_PAPER_UNLOAD_POS_UNLOADER_ZL, this);
}
//------------------------------------------------------------------
BOOL	CManual_Sub_Unloader_Fixed_Pos::Is_Comp_Usable()
{
	if (GetDlgItem(IDC_BUTTON_MANUAL_SUB_UNLOADER_FIXED_SAVE)->GetSafeHwnd() == NULL) return FALSE;
	return TRUE;
}
//------------------------------------------------------------------
void CManual_Sub_Unloader_Fixed_Pos::InitPara()
{
	CString Str = _T("");

	//Paper Unloader Y
	Str.Format(_T("%.5f"), CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Wait_Pos);
	m_stcPos[_eUNLOADER_Y_WAIT_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Load_In_Stage_Pos);
	m_stcPos[_eUNLOADER_Y_LOAD_IN_STAGE_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Unload_To_Cst_Pos);
	m_stcPos[_eUNLOADER_Y_UNLOAD_TO_CST_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Load_In_Cst_Pos);
	m_stcPos[_eUNLOADER_Y_LOAD_IN_CST_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Unload_To_Stage_Pos);
	m_stcPos[_eUNLOADER_Y_UNLOAD_TO_STAGE_POS].SetWindowText(Str);

	//Paper Unloader X
	Str.Format(_T("%.5f"), CManualData::m_ManualDataUnloader.Info.m_dPaperUnloader_XL_Wait_Pos);
	m_stcPos[_ePAPER_UNLOADER_XL_WAIT_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataUnloader.Info.m_dPaperUnloader_XL_Tension_Offset);
	m_stcPos[_ePAPER_UNLOADER_XL_TENSION_OFFSET].SetWindowText(Str);

	//Mask Unloader X
	Str.Format(_T("%.5f"), CManualData::m_ManualDataUnloader.Info.m_dUnloaderX_Wait_Pos);
	m_stcPos[_eUNLOADER_X_WAIT_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataUnloader.Info.m_dUnloaderX_Tension_Offset);
	m_stcPos[_eUNLOADER_X_TENSION_OFFSET].SetWindowText(Str);

	//Unloader Z
	Str.Format(_T("%.5f"), CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Wait_Pos);
	m_stcPos[_eUNLOADER_Z_WAIT_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Load_In_Stage_Pos);
	m_stcPos[_eUNLOADER_Z_LOAD_IN_STAGE_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Unload_To_Cst_Pos);
	m_stcPos[_eUNLOADER_Z_UNLOAD_TO_CST_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Load_In_Cst_Pos);
	m_stcPos[_eUNLOADER_Z_LOAD_IN_CST_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Unload_To_Stage_Pos);
	m_stcPos[_eUNLOADER_Z_UNLOAD_TO_STAGE_POS].SetWindowText(Str);
		
	Str.Format(_T("%d"), CManualData::m_ManualDataUnloader.Info.m_nUnloaderZ_StepDownCount);
	m_stcPos[_eUNLOADER_Z_STEP_DOWN_COUNT].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_StepDownOffset);
	m_stcPos[_eUNLOADER_Z_STEP_DOWN_OFFSET].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_StepUpOffset);
	m_stcPos[_eUNLOADER_Z_STEP_UP_OFFSET].SetWindowText(Str);
	Str.Format(_T("%d"), CManualData::m_ManualDataUnloader.Info.m_nUnloaderZ_VibrationCount);
	m_stcPos[_eUNLOADER_Z_VIBRATION_COUNT].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_VibrationVel);
	m_stcPos[_eUNLOADER_Z_VIBRATION_VEL].SetWindowText(Str);

	//21.02.15 SJC
	Str.Format(_T("%.5f"), CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Paper_Load_Pos);
	m_stcPos[_eUNLOADER_Z_PAPER_LOAD_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Paper_Unload_Pos);
	m_stcPos[_eUNLOADER_Z_PAPER_UNLOAD_POS].SetWindowText(Str);

	Str.Format(_T("%.5f"), CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Vibration_Pos);
	m_stcPos[_eUNLOADER_Z_VIBRATION_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_VibrationOffset);
	m_stcPos[_eUNLOADER_Z_VIBRATION_OFFSET].SetWindowText(Str);


	Str.Format(_T("%.5f"), CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Paper_Load_Pos);
	m_stcPos[_eUNLOADER_Y_PAPER_LOAD_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Paper_Load_Waiting_Pos);
	m_stcPos[_eUNLOADER_Y_PAPER_LOAD_WAITING_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Paper_Unload_Pos);
	m_stcPos[_eUNLOADER_Y_PAPER_UNLOAD_POS].SetWindowText(Str);	
	Str.Format(_T("%.5f"), CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Cassette_Safety_Pos);
	m_stcPos[_eUNLOADER_Y_CASSETTE_SAFETY_POS].SetWindowText(Str);

	//
	//21.02.25 SJC
	Str.Format(_T("%.5f"), CManualData::m_ManualDataUnloader.Info.m_dUnloaderZL_Wait_Pos);
	m_stcPos[_ePAPER_UNLOADER_ZL_WAIT_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataUnloader.Info.m_dUnloaderZL_Down_Pos);
	m_stcPos[_ePAPER_UNLOADER_ZL_DOWN_POS].SetWindowText(Str);
	//

	Str.Format(_T("%.5f"), CManualData::m_ManualDataUnloader.Info.m_dUnloaderZL_Paper_Load_Pos);
	m_stcPos[_ePAPER_UNLOADER_ZL_PAPER_LOAD_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataUnloader.Info.m_dUnloaderZL_Paper_Unload_Pos);
	m_stcPos[_ePAPER_UNLOADER_ZL_PAPER_UNLOAD_POS].SetWindowText(Str);
}
//------------------------------------------------------------------
BOOL CManual_Sub_Unloader_Fixed_Pos::CheckChangeData()
{
	CString Str = _T(""), StrMsg = _T("");

#pragma region //KJT 20210806 Interlock Add
	double dOffset = 0.0;
	m_editPos[_eUNLOADER_X_TENSION_OFFSET].GetWindowText(Str);
	dOffset = _ttof(Str);
	if (dOffset < CSystemData::m_Coordinate.Info.dMax_Tension_Offset_UnloaderX)
	{
		StrMsg.Format(_T("Unloader X Tension Offset Value Error !! (Offset:%.5f < %.5fmm)"), dOffset, CSystemData::m_Coordinate.Info.dMax_Tension_Offset_UnloaderX);
		AfxMessageBox(StrMsg);
		return FALSE;
	}
	m_editPos[_ePAPER_UNLOADER_XL_TENSION_OFFSET].GetWindowText(Str);
	dOffset = _ttof(Str);
	if (dOffset < CSystemData::m_Coordinate.Info.dMax_Tension_Offset_UnloaderX)
	{
		StrMsg.Format(_T("PaperUnloader X Tension Offset Value Error !! (Offset:%.5f < %.5fmm)"), dOffset, CSystemData::m_Coordinate.Info.dMax_Tension_Offset_PaperUnloaderX);
		AfxMessageBox(StrMsg);
		return FALSE;
	}
#pragma endregion

	//Paper Unloader Y
	m_stcPos[_eUNLOADER_Y_WAIT_POS].GetWindowText(Str);
	CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Wait_Pos = _ttof(Str);
	m_stcPos[_eUNLOADER_Y_LOAD_IN_STAGE_POS].GetWindowText(Str);
	CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Load_In_Stage_Pos = _ttof(Str);
	m_stcPos[_eUNLOADER_Y_UNLOAD_TO_CST_POS].GetWindowText(Str);
	CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Unload_To_Cst_Pos = _ttof(Str);
	m_stcPos[_eUNLOADER_Y_LOAD_IN_CST_POS].GetWindowText(Str);
	CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Load_In_Cst_Pos = _ttof(Str);
	m_stcPos[_eUNLOADER_Y_UNLOAD_TO_STAGE_POS].GetWindowText(Str);
	CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Unload_To_Stage_Pos = _ttof(Str);

	//Paper Unloader X
	m_stcPos[_ePAPER_UNLOADER_XL_WAIT_POS].GetWindowText(Str);
	CManualData::m_ManualDataUnloader.Info.m_dPaperUnloader_XL_Wait_Pos = _ttof(Str);
	m_stcPos[_ePAPER_UNLOADER_XL_TENSION_OFFSET].GetWindowText(Str);
	CManualData::m_ManualDataUnloader.Info.m_dPaperUnloader_XL_Tension_Offset = _ttof(Str);

	//Mask Unloader X
	m_stcPos[_eUNLOADER_X_WAIT_POS].GetWindowText(Str);
	CManualData::m_ManualDataUnloader.Info.m_dUnloaderX_Wait_Pos = _ttof(Str);
	m_stcPos[_eUNLOADER_X_TENSION_OFFSET].GetWindowText(Str);
	CManualData::m_ManualDataUnloader.Info.m_dUnloaderX_Tension_Offset = _ttof(Str);
	
	//Unloader Z
	m_stcPos[_eUNLOADER_Z_WAIT_POS].GetWindowText(Str);
	CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Wait_Pos = _ttof(Str);
	m_stcPos[_eUNLOADER_Z_LOAD_IN_STAGE_POS].GetWindowText(Str);
	CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Load_In_Stage_Pos = _ttof(Str);
	m_stcPos[_eUNLOADER_Z_UNLOAD_TO_CST_POS].GetWindowText(Str);
	CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Unload_To_Cst_Pos = _ttof(Str);
	m_stcPos[_eUNLOADER_Z_LOAD_IN_CST_POS].GetWindowText(Str);
	CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Load_In_Cst_Pos = _ttof(Str);
	m_stcPos[_eUNLOADER_Z_UNLOAD_TO_STAGE_POS].GetWindowText(Str);
	CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Unload_To_Stage_Pos = _ttof(Str);

	m_stcPos[_eUNLOADER_Z_STEP_DOWN_COUNT].GetWindowText(Str);
	CManualData::m_ManualDataUnloader.Info.m_nUnloaderZ_StepDownCount = _ttoi(Str);
	m_stcPos[_eUNLOADER_Z_STEP_DOWN_OFFSET].GetWindowText(Str);
	CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_StepDownOffset = _ttof(Str);
	m_stcPos[_eUNLOADER_Z_STEP_UP_OFFSET].GetWindowText(Str);
	CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_StepUpOffset = _ttof(Str);
	m_stcPos[_eUNLOADER_Z_VIBRATION_COUNT].GetWindowText(Str);
	CManualData::m_ManualDataUnloader.Info.m_nUnloaderZ_VibrationCount = _ttoi(Str);
	m_stcPos[_eUNLOADER_Z_VIBRATION_VEL].GetWindowText(Str);
	CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_VibrationVel = _ttof(Str);
	//

	//21.02.15 SJC
	m_stcPos[_eUNLOADER_Z_PAPER_LOAD_POS].GetWindowText(Str);
	CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Paper_Load_Pos = _ttof(Str);
	m_stcPos[_eUNLOADER_Z_PAPER_UNLOAD_POS].GetWindowText(Str);
	CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Paper_Unload_Pos = _ttof(Str);
	
	m_stcPos[_eUNLOADER_Z_VIBRATION_POS].GetWindowText(Str);
	CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Vibration_Pos = _ttof(Str);
	m_stcPos[_eUNLOADER_Z_VIBRATION_OFFSET].GetWindowText(Str);
	CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_VibrationOffset = _ttof(Str);


	m_stcPos[_eUNLOADER_Y_PAPER_LOAD_POS].GetWindowText(Str);
	CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Paper_Load_Pos = _ttof(Str);
	m_stcPos[_eUNLOADER_Y_PAPER_LOAD_WAITING_POS].GetWindowText(Str);
	CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Paper_Load_Waiting_Pos = _ttof(Str);
	m_stcPos[_eUNLOADER_Y_PAPER_UNLOAD_POS].GetWindowText(Str);
	CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Paper_Unload_Pos = _ttof(Str);
	m_stcPos[_eUNLOADER_Y_CASSETTE_SAFETY_POS].GetWindowText(Str);
	CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Cassette_Safety_Pos = _ttof(Str);
	//

	//21.02.25 SJC
	m_stcPos[_ePAPER_UNLOADER_ZL_WAIT_POS].GetWindowText(Str);
	CManualData::m_ManualDataUnloader.Info.m_dUnloaderZL_Wait_Pos = _ttof(Str);
	m_stcPos[_ePAPER_UNLOADER_ZL_DOWN_POS].GetWindowText(Str);
	CManualData::m_ManualDataUnloader.Info.m_dUnloaderZL_Down_Pos = _ttof(Str);


	m_stcPos[_ePAPER_UNLOADER_ZL_PAPER_LOAD_POS].GetWindowText(Str);
	CManualData::m_ManualDataUnloader.Info.m_dUnloaderZL_Paper_Load_Pos = _ttof(Str);
	m_stcPos[_ePAPER_UNLOADER_ZL_PAPER_UNLOAD_POS].GetWindowText(Str);
	CManualData::m_ManualDataUnloader.Info.m_dUnloaderZL_Paper_Unload_Pos = _ttof(Str);

	return TRUE;
}

enum_Axis CManual_Sub_Unloader_Fixed_Pos::GetAxisNo(enum_Unloader_Axis eUnloaderAxis, CString *strDiscription)
{
	CString Str = _T("");

	enum_Axis eAxis = AXIS_NONE;
	switch (eUnloaderAxis)
	{
	case _eMANUAL_UNLOADER_AXIS_Y:		eAxis = AXIS_UNLOADER_YL; Str = _T("UnLoader Y");  break; //PaperUnloader Y
	case _eMANUAL_PAPER_UNLOADER_AXIS_XL:		eAxis = AXIS_UNLOADER_XL; Str = _T("PaperUnLoader XL");  break; //PaperUnloader XL
	case _eMANUAL_PAPER_UNLOADER_AXIS_XR:		eAxis = AXIS_UNLOADER_XR; Str = _T("PaperUnLoader XR");  break; //PaperUnloader XR
	case _eMANUAL_UNLOADER_AXIS_X:		eAxis = AXIS_UNLOADER_X; Str = _T("Unloader X"); break; //MaskUnloader X
	case _eMANUAL_UNLOADER_AXIS_Z:		eAxis = AXIS_UNLOADER_Z; Str = _T("Unloader Z"); break;
	case _eMANUAL_UNLOADER_AXIS_SUB_ZL:	eAxis = AXIS_UNLOADER_ZL; Str = _T("Unloader Sub ZL"); break;
	case _eMANUAL_UNLOADER_AXIS_SUB_ZR:	eAxis = AXIS_UNLOADER_ZR; Str = _T("Unloader Sub ZR"); break;
	case _eMANUAL_UNLOADER_AXIS_GANTRY_Y:		eAxis = AXIS_VIRTUAL_GANTRY_Y; Str = _T("UnLoader Gantry Y");  break;
	}

	*strDiscription = Str;

	return eAxis;
}

BOOL CManual_Sub_Unloader_Fixed_Pos::ManualAbsMove(enum_Unloader_Axis eUnloaderAxis, double dPos)
{
	CString strAxisName = _T(""), Str = _T("");
	double dVel = 0.0, dAccel = 0.0, dDecel = 0.0;
	enum_Axis eAxis = GetAxisNo(eUnloaderAxis, &strAxisName);
	double dCurPos = 0.0;

	SharedInfo::GetManualSpeed(eAxis, eAXIS_SPEED_MEDIUM, &dVel, &dAccel, &dDecel);

	Str.Format(_T("%s Abs Move To Pos: %.5f Start?"), strAxisName, dPos);
	int nResult = AfxMessageBox(Str, MB_OKCANCEL);
	if (nResult == IDOK)
	{
		dCurPos = SharedInfo::GetCmdPos(eAxis);

		Devs::m_JogMotion.AbsMove(eAxis, dPos, dVel, dAccel, dDecel);
		
		Str.Format(_T("[Manual-Unloader-Fixed] %s Abs Move %.5f -> %.5f"), strAxisName, dCurPos, dPos);
		Total_Msg(Str);
	}

	return TRUE;
}

double CManual_Sub_Unloader_Fixed_Pos::GetTargetPos(enum_Unloader_Pos eUnloaderPos)
{
	CString Str = _T("");
	double dPos = 0.0;
	m_editPos[eUnloaderPos].GetWindowText(Str);
	dPos = _ttof(Str);

	return dPos;
}

//------------------------------------------------------------------
void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonSave()
{
	CString strPath = GetHomeDir();
	strPath.AppendFormat(_T("Data\\"));
	::CreateDirectory(strPath, NULL);
	strPath.AppendFormat(_T("Manual\\"));
	::CreateDirectory(strPath, NULL);

	CheckChangeData();
	CManualData::m_ManualDataUnloader.Save();
}

#pragma region //Get
//Paper Unloader Y
void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderGetWaitPosUnloaderY()
{
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_UNLOADER_YL);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eUNLOADER_Y_WAIT_POS].SetWindowText(Str);
}

void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderGetLoadInStagePosUnloaderY()
{
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_VIRTUAL_GANTRY_Y);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eUNLOADER_Y_LOAD_IN_STAGE_POS].SetWindowText(Str);
}
void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderGetUnloadToCstPosUnloaderY()
{
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_VIRTUAL_GANTRY_Y);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eUNLOADER_Y_UNLOAD_TO_CST_POS].SetWindowText(Str);
}

void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderGetLoadInCstPosUnloaderY()
{
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_UNLOADER_YL);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eUNLOADER_Y_LOAD_IN_CST_POS].SetWindowText(Str);
}
void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderGetUnloadToStagePosUnloaderY()
{
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_UNLOADER_YL);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eUNLOADER_Y_UNLOAD_TO_STAGE_POS].SetWindowText(Str);
}

//PaperUnloader X
void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderGetWaitPosPaperUnloaderXl()
{
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_UNLOADER_XL);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_ePAPER_UNLOADER_XL_WAIT_POS].SetWindowText(Str);
}

//Mask Unloader X
void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderGetWaitPosUnloaderX()
{
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_UNLOADER_X);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eUNLOADER_X_WAIT_POS].SetWindowText(Str);
}
//Unloader Z
void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderGetWaitPosUnloaderZ()
{
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_UNLOADER_Z);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eUNLOADER_Z_WAIT_POS].SetWindowText(Str);
}
void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderGetLoadInStagePosUnloaderZ()
{
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_UNLOADER_Z);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eUNLOADER_Z_LOAD_IN_STAGE_POS].SetWindowText(Str);
}
void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderGetUnloadToCstPosUnloaderZ()
{
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_UNLOADER_Z);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eUNLOADER_Z_UNLOAD_TO_CST_POS].SetWindowText(Str);
}
void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderGetLoadInCstPosUnloaderZ()
{
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_UNLOADER_Z);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eUNLOADER_Z_LOAD_IN_CST_POS].SetWindowText(Str);
}
void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderGetUnloadToStagePosUnloaderZ()
{
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_UNLOADER_Z);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eUNLOADER_Z_UNLOAD_TO_STAGE_POS].SetWindowText(Str);
}
#pragma endregion

#pragma region //Set
//Paper Unloader Y
void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetWaitPosUnloaderY()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eUNLOADER_Y_WAIT_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Unloader-Fixed] Unloader Y Pos Set Click (Wait Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}
void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetLoadInStagePosUnloaderY()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eUNLOADER_Y_LOAD_IN_STAGE_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Unloader-Fixed] Unloader Y Pos Set Click (Load In Stage Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}
void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetUnloadToCstPosUnloaderY()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eUNLOADER_Y_UNLOAD_TO_CST_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Unloader-Fixed] Unloader Y Pos Set Click (Unload To Cst Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}
void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetLoadInCstPosUnloaderY()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eUNLOADER_Y_LOAD_IN_CST_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Unloader-Fixed] Unloader Y Pos Set Click (Load In Cst Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}
void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetUnloadToStagePosUnloaderY()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eUNLOADER_Y_UNLOAD_TO_STAGE_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Unloader-Fixed] Unloader Y Pos Set Click (Unload To Stage Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}

//PaperUnloader X
void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetWaitPosPaperUnloaderXl()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _ePAPER_UNLOADER_XL_WAIT_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Unloader-Fixed] Paper Unloader XL Pos Set Click (Wait Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}

void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetTensionOffsetPaperUnloaderXl()
{
	CString Str = _T(""), StrMsg = _T("");
	double dOffset = 0.0;
	int nIndex = _ePAPER_UNLOADER_XL_TENSION_OFFSET;
	m_editPos[nIndex].GetWindowText(Str);

#pragma region //KJT 20210721 Interlock Add
	dOffset = _ttof(Str);
	if (dOffset < CSystemData::m_Coordinate.Info.dMax_Tension_Offset_PaperUnloaderX)
	{
		StrMsg.Format(_T("Paper Unloader X Tension Offset Set Error !! (Offset:%.5f < %.5fmm)"), dOffset, CSystemData::m_Coordinate.Info.dMax_Tension_Offset_PaperUnloaderX);
		AfxMessageBox(StrMsg);
		return;
	}
#pragma endregion

	m_stcPos[nIndex].SetWindowText(Str);

	StrMsg.Format(_T("[Manual-Unloader-Fixed] Paper Unloader XL Offset Set Click (Offset : %.5f)"), dOffset);
	Total_Msg(StrMsg);
}

//Mask Unloader X
void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetWaitPosUnloaderX()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eUNLOADER_X_WAIT_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Unloader-Fixed] Unloader X Pos Set Click (Wait Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}
void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetTensionOffsetUnloaderX()
{
	CString Str = _T(""), StrMsg = _T("");
	double dOffset = 0.0;
	int nIndex = _eUNLOADER_X_TENSION_OFFSET;
	m_editPos[nIndex].GetWindowText(Str);

#pragma region //KJT 20210721 Interlock Add
	dOffset = _ttof(Str);
	if (dOffset < CSystemData::m_Coordinate.Info.dMax_Tension_Offset_UnloaderX)
	{
		StrMsg.Format(_T("Stick Unloader X Tension Offset Set Error !! (Offset:%.5f < %.5fmm)"), dOffset, CSystemData::m_Coordinate.Info.dMax_Tension_Offset_UnloaderX);
		AfxMessageBox(StrMsg);
		return;
	}
#pragma endregion

	m_stcPos[nIndex].SetWindowText(Str);

	StrMsg.Format(_T("[Manual-Unloader-Fixed] Stick Unloader X Tension Offset Set Click (Offset : %.5f)"), dOffset);
	Total_Msg(StrMsg);
}
//Unloader Z
void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetWaitPosUnloaderZ()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eUNLOADER_Z_WAIT_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Unloader-Fixed] Unloader Z Pos Set Click (Wait Pos : %.5f)"), dPos);
	StrMsg.Format(StrMsg);
	Total_Msg(StrMsg);
}
void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetLoadInStagePosUnloaderZ()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eUNLOADER_Z_LOAD_IN_STAGE_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Unloader-Fixed] Unloader Z Pos Set Click (Load In Stage Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}
void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetUnloadToCstPosUnloaderZ()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eUNLOADER_Z_UNLOAD_TO_CST_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Unloader-Fixed] Unloader Z Pos Set Click (Unload To Cst Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}
void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetLoadInCstPosUnloaderZ()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eUNLOADER_Z_LOAD_IN_CST_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Unloader-Fixed] Unloader Z Pos Set Click (Load In Cst Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}
void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetUnloadToStagePosUnloaderZ()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eUNLOADER_Z_UNLOAD_TO_STAGE_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Unloader-Fixed] Unloader Z Pos Set Click (Unload To Stage Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}
void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetStepDownCount()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eUNLOADER_Z_STEP_DOWN_COUNT;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	int nCount = _ttoi(Str);
	StrMsg.Format(_T("[Manual-Unloader-Fixed] Unloader Z Step Down Count Set Click (Step Count : %d)"), nCount);
	Total_Msg(StrMsg);
}

void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetStepDownOffsetUnloaderZ()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eUNLOADER_Z_STEP_DOWN_OFFSET;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Unloader-Fixed] Unloader Z Step Down Offset Set Click (Step Offset : %.5f)"), dPos);
	Total_Msg(StrMsg);
}


void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetStepUpOffsetUnloaderZ()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eUNLOADER_Z_STEP_UP_OFFSET;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Unloader-Fixed] Unloader Z Step Up Offset Set Click (Step Offset : %.5f)"), dPos);
	Total_Msg(StrMsg);
}


void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetVibrationCount()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eUNLOADER_Z_VIBRATION_COUNT;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	int nCount = _ttoi(Str); //KJT 20210727
	StrMsg.Format(_T("[Manual-Unloader-Fixed] Unloader Z Vibration Count Set Click (Vibration Count : %d)"), nCount);
	Total_Msg(StrMsg);
}

void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetStickLoadInStage2ndPosLoaderZ()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eUNLOADER_Z_VIBRATION_OFFSET;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Unloader-Fixed] Unloader Z Vibration Offset Set Click (Vibration Offset : %.5f)"), dPos);
	Total_Msg(StrMsg);
}


void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetVibrationVel()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eUNLOADER_Z_VIBRATION_VEL;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dVel = _ttof(Str);
	StrMsg.Format(_T("[Manual-Unloader-Fixed] Unloader Z Vibration Vel Set Click (Vibration Vel : %.5f)"), dVel);
	Total_Msg(StrMsg);
}

#pragma endregion

#pragma region //Move
//Paper Unloader Y
void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderMoveWaitPosUnloaderY()
{
	double dPos = GetTargetPos(_eUNLOADER_Y_WAIT_POS);
	ManualAbsMove(_eMANUAL_UNLOADER_AXIS_Y, dPos);
}

void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderMoveLoadInStagePosUnloaderY()
{
	double dPos = GetTargetPos(_eUNLOADER_Y_LOAD_IN_STAGE_POS);
	ManualAbsMove(_eMANUAL_UNLOADER_AXIS_GANTRY_Y, dPos);
}
void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderMoveUnloadToCstPosUnloaderY()
{
	double dPos = GetTargetPos(_eUNLOADER_Y_UNLOAD_TO_CST_POS);
	ManualAbsMove(_eMANUAL_UNLOADER_AXIS_GANTRY_Y, dPos);
}

void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderMoveLoadInCstPosUnloaderY()
{
	double dPos = GetTargetPos(_eUNLOADER_Y_LOAD_IN_CST_POS);
	ManualAbsMove(_eMANUAL_UNLOADER_AXIS_Y, dPos);
}
void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderMoveUnloadToStagePosUnloaderY()
{
	double dPos = GetTargetPos(_eUNLOADER_Y_UNLOAD_TO_STAGE_POS);
	ManualAbsMove(_eMANUAL_UNLOADER_AXIS_Y, dPos);
}

//PaperUnloader X
void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderMoveWaitPosPaperUnloaderXl()
{
	double dPos = GetTargetPos(_ePAPER_UNLOADER_XL_WAIT_POS);
	ManualAbsMove(_eMANUAL_PAPER_UNLOADER_AXIS_XL, dPos);
}

//Mask Unloader X
void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderMoveWaitPosUnloaderX()
{
	double dPos = GetTargetPos(_eUNLOADER_X_WAIT_POS);
	ManualAbsMove(_eMANUAL_UNLOADER_AXIS_X, dPos);
}
//Unloader Z
void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderMoveWaitPosUnloaderZ()
{
	double dPos = GetTargetPos(_eUNLOADER_Z_WAIT_POS);
	ManualAbsMove(_eMANUAL_UNLOADER_AXIS_Z, dPos);
}
void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderMoveLoadInStagePosUnloaderZ()
{
	double dPos = GetTargetPos(_eUNLOADER_Z_LOAD_IN_STAGE_POS);
	ManualAbsMove(_eMANUAL_UNLOADER_AXIS_Z, dPos);
}
void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderMoveUnloadToCstPosUnloaderZ()
{
	double dPos = GetTargetPos(_eUNLOADER_Z_UNLOAD_TO_CST_POS);
	ManualAbsMove(_eMANUAL_UNLOADER_AXIS_Z, dPos);
}
void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderMoveLoadInCstPosUnloaderZ()
{
	double dPos = GetTargetPos(_eUNLOADER_Z_LOAD_IN_CST_POS);
	ManualAbsMove(_eMANUAL_UNLOADER_AXIS_Z, dPos);
}
void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderMoveUnloadToStagePosUnloaderZ()
{
	double dPos = GetTargetPos(_eUNLOADER_Z_UNLOAD_TO_STAGE_POS);
	ManualAbsMove(_eMANUAL_UNLOADER_AXIS_Z, dPos);
}
#pragma endregion

void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderFixedSave()
{
	CheckChangeData();
	CManualData::m_ManualDataUnloader.Save();

	AfxMessageBox(_T("Save Ok"));
}


void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderGetLoadPaperPosUnloaderZ()
{
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_UNLOADER_Z);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eUNLOADER_Z_PAPER_LOAD_POS].SetWindowText(Str);
}


void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderGetUnloadPaperPosUnloaderZ()
{
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_UNLOADER_Z);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eUNLOADER_Z_PAPER_UNLOAD_POS].SetWindowText(Str);
}


void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderGetStickLoadInBox2ndPosLoaderZ()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_UNLOADER_Z);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eUNLOADER_Z_VIBRATION_POS].SetWindowText(Str);
}


void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderGetLoadPaperPosUnloaderY()
{
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_UNLOADER_YL);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eUNLOADER_Y_PAPER_LOAD_POS].SetWindowText(Str);
}

void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderGetLoadPaperWaitingPosUnloaderY()
{
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_UNLOADER_YL);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eUNLOADER_Y_PAPER_LOAD_WAITING_POS].SetWindowText(Str);
}

void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderGetUnloadPaperPosUnloaderY()
{
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_UNLOADER_YL);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eUNLOADER_Y_PAPER_UNLOAD_POS].SetWindowText(Str);
}


void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderGetCassetteSafetyPosUnloaderY()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_UNLOADER_YL);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eUNLOADER_Y_CASSETTE_SAFETY_POS].SetWindowText(Str);
}



void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetLoadPaperPosUnloaderZ()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eUNLOADER_Z_PAPER_LOAD_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Unloader-Fixed] Unloader Z Pos Set Click (Load Paper Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}


void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetUnloadPaperPosUnloaderZ()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eUNLOADER_Z_PAPER_UNLOAD_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Unloader-Fixed] Unloader Z Pos Set Click (Unload Paper Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}


void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetStickLoadInBox2ndPosLoaderZ()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eUNLOADER_Z_VIBRATION_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Unloader-Fixed] Unloader Z Vibration Pos Set Click (Unload Vibration Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}


void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetLoadPaperPosUnloaderY()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eUNLOADER_Y_PAPER_LOAD_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Unloader-Fixed] Unloader Y Pos Set Click (Load Paper Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}

void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetLoadPaperWaitingPosUnloaderY()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eUNLOADER_Y_PAPER_LOAD_WAITING_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Unloader-Fixed] Unloader Y Pos Set Click (Load Paper Waiting Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}

void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetUnloadPaperPosUnloaderY()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eUNLOADER_Y_PAPER_UNLOAD_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Unloader-Fixed] Unloader Y Pos Set Click (Unload Paper Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}


void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetCassetteSafetyPosUnloaderY()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eUNLOADER_Y_CASSETTE_SAFETY_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Unloader-Fixed] Unloader Y Pos Set Click (Unload Safety Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}

void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderMoveLoadPaperPosUnloaderZ()
{
	double dPos = GetTargetPos(_eUNLOADER_Z_PAPER_LOAD_POS);
	ManualAbsMove(_eMANUAL_UNLOADER_AXIS_Z, dPos);
}


void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderMoveUnloadPaperPosUnloaderZ()
{
	double dPos = GetTargetPos(_eUNLOADER_Z_PAPER_UNLOAD_POS);
	ManualAbsMove(_eMANUAL_UNLOADER_AXIS_Z, dPos);
}



void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderMoveStickLoadInBox2ndPosLoaderZ()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	double dPos = GetTargetPos(_eUNLOADER_Z_VIBRATION_POS);
	ManualAbsMove(_eMANUAL_UNLOADER_AXIS_Z, dPos);
}


void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderMoveLoadPaperPosUnloaderY()
{
	double dPos = GetTargetPos(_eUNLOADER_Y_PAPER_LOAD_POS);
	ManualAbsMove(_eMANUAL_UNLOADER_AXIS_Y, dPos);
}

void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderMoveLoadPaperWaitingPosUnloaderY()
{
	double dPos = GetTargetPos(_eUNLOADER_Y_PAPER_LOAD_WAITING_POS);
	ManualAbsMove(_eMANUAL_UNLOADER_AXIS_Y, dPos);
}

void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderMoveUnloadPaperPosUnloaderY()
{
	double dPos = GetTargetPos(_eUNLOADER_Y_PAPER_UNLOAD_POS);
	ManualAbsMove(_eMANUAL_UNLOADER_AXIS_Y, dPos);
}


void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderMoveCassetteSafetyPosUnloaderY()
{
	double dPos = GetTargetPos(_eUNLOADER_Y_CASSETTE_SAFETY_POS);
	ManualAbsMove(_eMANUAL_UNLOADER_AXIS_Y, dPos);
}

void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderMoveWaitPosUnloaderZl()
{
	double dPos = GetTargetPos(_ePAPER_UNLOADER_ZL_WAIT_POS);
	ManualAbsMove(_eMANUAL_UNLOADER_AXIS_SUB_ZL, dPos);
}


void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderMoveDownPosUnloaderZl()
{
	double dPos = GetTargetPos(_ePAPER_UNLOADER_ZL_DOWN_POS);
	ManualAbsMove(_eMANUAL_UNLOADER_AXIS_SUB_ZL, dPos);
}

void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderGetWaitPosUnloaderZl()
{
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_UNLOADER_ZL);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_ePAPER_UNLOADER_ZL_WAIT_POS].SetWindowText(Str);
}


void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderGetDownPosUnloaderZl()
{
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_UNLOADER_ZL);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_ePAPER_UNLOADER_ZL_DOWN_POS].SetWindowText(Str);
}

void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetWaitPosUnloaderZl()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _ePAPER_UNLOADER_ZL_WAIT_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Unloader-Fixed] Unloader ZL Pos Set Click (Wait Pos : %.5f)"), dPos);
	StrMsg.Format(StrMsg);
	Total_Msg(StrMsg);
}


void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetDownPosUnloaderZl()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _ePAPER_UNLOADER_ZL_DOWN_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Unloader-Fixed] Unloader ZL Pos Set Click (Down Pos : %.5f)"), dPos);
	StrMsg.Format(StrMsg);
	Total_Msg(StrMsg);
}


void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderGetPaperLoadPosUnloaderZl()
{
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_UNLOADER_ZL);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_ePAPER_UNLOADER_ZL_PAPER_LOAD_POS].SetWindowText(Str);
}


void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderGetPaperUnloadPosUnloaderZl()
{
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_UNLOADER_ZL);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_ePAPER_UNLOADER_ZL_PAPER_UNLOAD_POS].SetWindowText(Str);
}


void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetPaperLoadPosUnloaderZl()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _ePAPER_UNLOADER_ZL_PAPER_LOAD_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Unloader-Fixed] Unloader ZL Pos Set Click (Paper Load Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}

void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderSetPaperUnloadPosUnloaderZl()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _ePAPER_UNLOADER_ZL_PAPER_UNLOAD_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Unloader-Fixed] Unloader ZL Pos Set Click (Paper Unlaad Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}


void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderMovePaperLoadPosUnloaderZl()
{
	double dPos = GetTargetPos(_ePAPER_UNLOADER_ZL_PAPER_LOAD_POS);
	ManualAbsMove(_eMANUAL_UNLOADER_AXIS_SUB_ZL, dPos);
}

void CManual_Sub_Unloader_Fixed_Pos::OnBnClickedButtonManualSubUnloaderMovePaperUnloadPosUnloaderZl()
{
	double dPos = GetTargetPos(_ePAPER_UNLOADER_ZL_PAPER_UNLOAD_POS);
	ManualAbsMove(_eMANUAL_UNLOADER_AXIS_SUB_ZL, dPos);
}
