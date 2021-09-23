// Manual_Sub_Loader_Fixed_Pos.cpp: 구현 파일
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "Manual_Sub_Loader_Fixed_Pos.h"
#include "afxdialogex.h"


// CManual_Sub_Loader_Fixed_Pos 대화 상자

IMPLEMENT_DYNAMIC(CManual_Sub_Loader_Fixed_Pos, CDialogEx)

CManual_Sub_Loader_Fixed_Pos::CManual_Sub_Loader_Fixed_Pos(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_MANUAL_SUB_LOADER_FIXED_POS, pParent)
{
	Create(IDD_DLG_MANUAL_SUB_LOADER_FIXED_POS, pParent);
}

CManual_Sub_Loader_Fixed_Pos::~CManual_Sub_Loader_Fixed_Pos()
{
}

void CManual_Sub_Loader_Fixed_Pos::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CManual_Sub_Loader_Fixed_Pos, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_GET_WAIT_POS_LOADER_Z, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderGetWaitPosLoaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_GET_STICK_LOAD_IN_BOX_1ST_POS_LOADER_Z, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderGetStickLoadInBox1stPosLoaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_GET_STICK_UNLOAD_TO_STAGE_POS_LOADER_Z, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderGetStickUnloadToStagePosLoaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_GET_STICK_LOAD_IN_STAGE_1ST_POS_LOADER_Z, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderGetStickLoadInStage1stPosLoaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_GET_STICK_UNLOAD_TO_BOX_POS_LOADER_Z, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderGetStickUnloadToBoxPosLoaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_GET_WAIT_POS_LOADER_X, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderGetWaitPosLoaderX)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_SET_WAIT_POS_LOADER_Z, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderSetWaitPosLoaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_SET_STICK_LOAD_IN_BOX_1ST_POS_LOADER_Z, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderSetStickLoadInBox1stPosLoaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_SET_STICK_UNLOAD_TO_STAGE_POS_LOADER_Z, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderSetStickUnloadToStagePosLoaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_SET_STICK_LOAD_IN_STAGE_1ST_POS_LOADER_Z, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderSetStickLoadInStage1stPosLoaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_SET_STICK_UNLOAD_TO_BOX_POS_LOADER_Z, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderSetStickUnloadToBoxPosLoaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_SET_STEP_DOWN_OFFSET_LOADER_Z, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderSetStepDownOffsetLoaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_SET_WAIT_POS_LOADER_X, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderSetWaitPosLoaderX)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MOVE_WAIT_POS_LOADER_Z, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderMoveWaitPosLoaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MOVE_STICK_LOAD_IN_BOX_1ST_POS_LOADER_Z, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderMoveStickLoadInBox1stPosLoaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MOVE_STICK_UNLOAD_TO_STAGE_POS_LOADER_Z, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderMoveStickUnloadToStagePosLoaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MOVE_STICK_LOAD_IN_STAGE_1ST_POS_LOADER_Z, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderMoveStickLoadInStage1stPosLoaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MOVE_STICK_UNLOAD_TO_BOX_POS_LOADER_Z, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderMoveStickUnloadToBoxPosLoaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MOVE_WAIT_POS_LOADER_X, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderMoveWaitPosLoaderX)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_FIXED_SAVE, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderFixedSave)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_GET_STICK_LOAD_IN_BOX_2ND_POS_LOADER_Z, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderGetStickLoadInBox2ndPosLoaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_SET_STICK_LOAD_IN_BOX_2ND_POS_LOADER_Z, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderSetStickLoadInBox2ndPosLoaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MOVE_STICK_LOAD_IN_BOX_2ND_POS_LOADER_Z, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderMoveStickLoadInBox2ndPosLoaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_GET_STICK_LOAD_IN_STAGE_2ND_POS_LOADER_Z, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderGetStickLoadInStage2ndPosLoaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_SET_STICK_LOAD_IN_STAGE_2ND_POS_LOADER_Z, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderSetStickLoadInStage2ndPosLoaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MOVE_STICK_LOAD_IN_STAGE_2ND_POS_LOADER_Z, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderMoveStickLoadInStage2ndPosLoaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_SET_TENSION_OFFSET_LOADER_X, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderSetTensionOffsetLoaderX)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_GET_WAIT_POS_LOADER_Y, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderGetWaitPosLoaderY)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_GET_STICK_LOAD_POS_LOADER_Y, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderGetStickLoadPosLoaderY)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_GET_STICK_UNLOAD_POS_LOADER_Y, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderGetStickUnloadPosLoaderY)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_GET_INSPECTION_POS_LOADER_Y, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderGetInspectionPosLoaderY)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_SET_WAIT_POS_LOADER_Y, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderSetWaitPosLoaderY)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_SET_STICK_LOAD_POS_LOADER_Y, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderSetStickLoadPosLoaderY)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_SET_STICK_UNLOAD_POS_LOADER_Y, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderSetStickUnloadPosLoaderY)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_SET_INSPECTION_POS_LOADER_Y, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderSetInspectionPosLoaderY)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MOVE_WAIT_POS_LOADER_Y, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderMoveWaitPosLoaderY)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MOVE_STICK_LOAD_POS_LOADER_Y, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderMoveStickLoadPosLoaderY)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MOVE_STICK_UNLOAD_POS_LOADER_Y, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderMoveStickUnloadPosLoaderY)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MOVE_INSPECTION_POS_LOADER_Y, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderMoveInspectionPosLoaderY)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_GET_STICK_ALIGN_POS_LOADER_Z, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderGetStickAlignPosLoaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_SET_STICK_ALIGN_POS_LOADER_Z, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderSetStickAlignPosLoaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MOVE_STICK_ALIGN_POS_LOADER_Z, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderMoveStickAlignPosLoaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_GET_WAIT_POS_LOADER_ZL, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderGetWaitPosLoaderZl)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_SET_DOWN_POS_LOADER_ZL, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderSetDownPosLoaderZl)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_SET_WAIT_POS_LOADER_ZL, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderSetWaitPosLoaderZl)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_SET_WAIT_POS_LOADER_ZR, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderSetWaitPosLoaderZr)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_GET_WAIT_POS_LOADER_ZR, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderGetWaitPosLoaderZr)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_GET_DOWN_POS_LOADER_ZL, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderGetDownPosLoaderZl)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_GET_DOWN_POS_LOADER_ZR, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderGetDownPosLoaderZr)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_SET_DOWN_POS_LOADER_ZR, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderSetDownPosLoaderZr)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MOVE_WAIT_POS_LOADER_ZL, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderMoveWaitPosLoaderZl)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MOVE_WAIT_POS_LOADER_ZR, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderMoveWaitPosLoaderZr)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MOVE_DOWN_POS_LOADER_ZL, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderMoveDownPosLoaderZl)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MOVE_DOWN_POS_LOADER_ZR, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderMoveDownPosLoaderZr)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_SET_STEP_DOWN_COUNT, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderSetStepDownCount)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_SET_STEP_UP_OFFSET_LOADER_Z, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderSetStepUpOffsetLoaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_SET_VIBRATION_COUNT, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderSetVibrationCount)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_SET_VIBRATION_VEL, &CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderSetVibrationVel)
END_MESSAGE_MAP()


// CManual_Sub_Loader_Fixed_Pos 메시지 처리기

BOOL CManual_Sub_Loader_Fixed_Pos::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	InitCtrl();

	return TRUE;
}
//------------------------------------------------------------------
void CManual_Sub_Loader_Fixed_Pos::OnShowWindow(BOOL bShow, UINT nStatus)
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
void CManual_Sub_Loader_Fixed_Pos::OnSize(UINT nType, int cx, int cy)
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
	GetDlgItem(IDC_BUTTON_MANUAL_SUB_LOADER_FIXED_SAVE)->MoveWindow(RectSaveBtn);
}
//------------------------------------------------------------------
void CManual_Sub_Loader_Fixed_Pos::OnTimer(UINT_PTR nIDEvent)
{
	//if (Devs::m_JogMotion.IsMotionDone(AXIS_LOADING_STAGE_X1) == TRUE)

	CDialogEx::OnTimer(nIDEvent);
}
//------------------------------------------------------------------
void	CManual_Sub_Loader_Fixed_Pos::InitCtrl()
{
#pragma region //stc
	//Loader Z
	m_stcPos[_eLOADER_Z_WAIT_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_LOADER_CURRENT_WAIT_POS_LOADER_Z, this);
	m_stcPos[_eLOADER_Z_STICK_LOAD_IN_BOX_1ST_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_LOADER_CURRENT_STICK_LOAD_IN_BOX_1ST_POS_LOADER_Z, this);
	m_stcPos[_eLOADER_Z_VIBRATION_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_LOADER_CURRENT_STICK_LOAD_IN_BOX_2ND_POS_LOADER_Z, this);
	m_stcPos[_eLOADER_Z_STICK_UNLOAD_TO_STAGE_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_LOADER_CURRENT_STICK_UNLOAD_TO_STAGE_POS_LOADER_Z, this);

	m_stcPos[_eLOADER_Z_STICK_LOAD_IN_STAGE_1ST_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_LOADER_CURRENT_STICK_LOAD_IN_STAGE_1ST_POS_LOADER_Z, this);
	m_stcPos[_eLOADER_Z_VIBRATION_OFFSET].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_LOADER_CURRENT_STICK_LOAD_IN_STAGE_2ND_POS_LOADER_Z, this);
	m_stcPos[_eLOADER_Z_STICK_UNLOAD_TO_BOX_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_LOADER_CURRENT_STICK_UNLOAD_TO_BOX_POS_LOADER_Z, this);

	m_stcPos[_eLOADER_Z_STEP_DOWN_COUNT].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_LOADER_STEP_DOWN_COUNT, this);
	m_stcPos[_eLOADER_Z_STEP_DOWN_OFFSET].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_LOADER_STEP_DOWN_OFFSET_LOADER_Z, this);
	m_stcPos[_eLOADER_Z_STEP_UP_OFFSET].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_LOADER_STEP_UP_OFFSET_LOADER_Z, this);
	m_stcPos[_eLOADER_Z_VIBRATION_COUNT].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_LOADER_VIBRATION_COUNT, this);
	m_stcPos[_eLOADER_Z_VIBRATION_VEL].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_LOADER_VIBRATION_VEL, this);

	//Loader X
	m_stcPos[_eLOADER_X_WAIT_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_LOADER_CURRENT_WAIT_POS_LOADER_X, this);
	m_stcPos[_eLOADER_X_TENSION_OFFSET].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_LOADER_CURRENT_TENSION_OFFSET_LOADER_X, this);

	//21.02.10 sjc
	//loader Y
	m_stcPos[_eLOADER_Y_WAIT_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_LOADER_CURRENT_WAIT_POS_LOADER_Y, this);
	m_stcPos[_eLOADER_Y_STICK_LOAD_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_LOADER_CURRENT_STICK_LOAD_POS_LOADER_Y, this);
	m_stcPos[_eLOADER_Y_STICK_UNLOAD_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_LOADER_CURRENT_STICK_UNLOAD_POS_LOADER_Y, this);
	m_stcPos[_eLOADER_Y_INSPECTION_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_LOADER_CURRENT_INSPECTION_POS_LOADER_Y, this);
	
	//21.02.26 SJC
	//LOADER Z ADD
	m_stcPos[_eLOADER_Z_INSPECTION_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_LOADER_CURRENT_STICK_ALIGN_POS_LOADER_Z, this);
	//21.02.28 sjc
	//loader zl zr
	m_stcPos[_eLOADER_ZL_WAIT_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_LOADER_CURRENT_WAIT_POS_LOADER_ZL, this);
	m_stcPos[_eLOADER_ZR_WAIT_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_LOADER_CURRENT_WAIT_POS_LOADER_ZR, this);
	m_stcPos[_eLOADER_ZL_DOWN_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_LOADER_CURRENT_DOWN_POS_LOADER_ZL, this);
	m_stcPos[_eLOADER_ZR_DOWN_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_LOADER_CURRENT_DOWN_POS_LOADER_ZR, this);

#pragma endregion

#pragma region //Edit
	//Loader Z
	m_editPos[_eLOADER_Z_WAIT_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_LOADER_WAIT_POS_LOADER_Z, this);
	m_editPos[_eLOADER_Z_STICK_LOAD_IN_BOX_1ST_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_LOADER_STICK_LOAD_IN_BOX_1ST_POS_LOADER_Z, this);
	m_editPos[_eLOADER_Z_VIBRATION_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_LOADER_STICK_LOAD_IN_BOX_2ND_POS_LOADER_Z, this);
	m_editPos[_eLOADER_Z_STICK_UNLOAD_TO_STAGE_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_LOADER_STICK_UNLOAD_TO_STAGE_POS_LOADER_Z, this);

	m_editPos[_eLOADER_Z_STICK_LOAD_IN_STAGE_1ST_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_LOADER_STICK_LOAD_IN_STAGE_1ST_POS_LOADER_Z, this);
	m_editPos[_eLOADER_Z_VIBRATION_OFFSET].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_LOADER_STICK_LOAD_IN_STAGE_2ND_POS_LOADER_Z, this);
	m_editPos[_eLOADER_Z_STICK_UNLOAD_TO_BOX_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_LOADER_STICK_UNLOAD_TO_BOX_POS_LOADER_Z, this);
		
	m_editPos[_eLOADER_Z_STEP_DOWN_COUNT].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_LOADER_STEP_DOWN_COUNT, this);
	m_editPos[_eLOADER_Z_STEP_DOWN_OFFSET].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_LOADER_STEP_DOWN_OFFSET_LOADER_Z, this);
	m_editPos[_eLOADER_Z_STEP_UP_OFFSET].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_LOADER_STEP_UP_OFFSET_LOADER_Z, this);
	m_editPos[_eLOADER_Z_VIBRATION_COUNT].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_LOADER_VIBRATION_COUNT, this);
	m_editPos[_eLOADER_Z_VIBRATION_VEL].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_LOADER_VIBRATION_VEL, this);


	//Loader X
	m_editPos[_eLOADER_X_WAIT_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_LOADER_WAIT_POS_LOADER_X, this);
	m_editPos[_eLOADER_X_TENSION_OFFSET].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_LOADER_TENSION_OFFSET_LOADER_X, this);
	
	//21.02.10 SJC
	//LOADER Y
	m_editPos[_eLOADER_Y_WAIT_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_LOADER_WAIT_POS_LOADER_Y, this);
	m_editPos[_eLOADER_Y_STICK_LOAD_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_LOADER_STICK_LOAD_POS_LOADER_Y, this);
	m_editPos[_eLOADER_Y_STICK_UNLOAD_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_LOADER_STICK_UNLOAD_POS_LOADER_Y, this);
	m_editPos[_eLOADER_Y_INSPECTION_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_LOADER_ALIGN_POS_LOADER_Y, this);
	//21.02.26 SJC
	m_editPos[_eLOADER_Z_INSPECTION_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_LOADER_STICK_ALIGN_POS_LOADER_Z, this);
	//21.02.28 sjc
	//loader zl zr
	m_editPos[_eLOADER_ZL_WAIT_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_LOADER_WAIT_POS_LOADER_ZL, this);
	m_editPos[_eLOADER_ZL_DOWN_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_LOADER_DOWN_POS_LOADER_ZL, this);
	m_editPos[_eLOADER_ZR_WAIT_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_LOADER_WAIT_POS_LOADER_ZR, this);
	m_editPos[_eLOADER_ZR_DOWN_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_LOADER_DOWN_POS_LOADER_ZR, this);
#pragma endregion
}
//------------------------------------------------------------------
BOOL	CManual_Sub_Loader_Fixed_Pos::Is_Comp_Usable()
{
	if (GetDlgItem(IDC_BUTTON_MANUAL_SUB_LOADER_FIXED_SAVE)->GetSafeHwnd() == NULL) return FALSE;
	return TRUE;
}
//------------------------------------------------------------------
void CManual_Sub_Loader_Fixed_Pos::InitPara()
{
	CString Str = _T("");

#pragma region //Loader Z
	Str.Format(_T("%.5f"), CManualData::m_ManualDataLoader.Info.m_dLoaderZ_Wait_Pos);
	m_stcPos[_eLOADER_Z_WAIT_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataLoader.Info.m_dLoaderZ_StickLoadInBox1st_Pos);
	m_stcPos[_eLOADER_Z_STICK_LOAD_IN_BOX_1ST_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataLoader.Info.m_dLoaderZ_Vibration_Pos); //KJT 20210317
	m_stcPos[_eLOADER_Z_VIBRATION_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataLoader.Info.m_dLoaderZ_StickUnloadToStage_Pos);
	m_stcPos[_eLOADER_Z_STICK_UNLOAD_TO_STAGE_POS].SetWindowText(Str);

	Str.Format(_T("%.5f"), CManualData::m_ManualDataLoader.Info.m_dLoaderZ_StickLoadInStage1st_Pos);
	m_stcPos[_eLOADER_Z_STICK_LOAD_IN_STAGE_1ST_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataLoader.Info.m_dLoaderZ_VibrationOffset); //KJT 20210317
	m_stcPos[_eLOADER_Z_VIBRATION_OFFSET].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataLoader.Info.m_dLoaderZ_StickUnoadToBox_Pos);
	m_stcPos[_eLOADER_Z_STICK_UNLOAD_TO_BOX_POS].SetWindowText(Str);

	Str.Format(_T("%d"), CManualData::m_ManualDataLoader.Info.m_nLoaderZ_StepDownCount);
	m_stcPos[_eLOADER_Z_STEP_DOWN_COUNT].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataLoader.Info.m_dLoaderZ_StepDownOffset);
	m_stcPos[_eLOADER_Z_STEP_DOWN_OFFSET].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataLoader.Info.m_dLoaderZ_StepUpOffset);
	m_stcPos[_eLOADER_Z_STEP_UP_OFFSET].SetWindowText(Str);
	Str.Format(_T("%d"), CManualData::m_ManualDataLoader.Info.m_nLoaderZ_VibrationCount);
	m_stcPos[_eLOADER_Z_VIBRATION_COUNT].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataLoader.Info.m_dLoaderZ_VibrationVel);
	m_stcPos[_eLOADER_Z_VIBRATION_VEL].SetWindowText(Str);
#pragma endregion

#pragma region //Loader Sub Z(ZL, ZR)
	Str.Format(_T("%.5f"), CManualData::m_ManualDataLoader.Info.m_dLoaderZL_Wait_Pos);
	m_stcPos[_eLOADER_ZL_WAIT_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataLoader.Info.m_dLoaderZR_Wait_Pos);
	m_stcPos[_eLOADER_ZR_WAIT_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataLoader.Info.m_dLoaderZL_Down_Pos);
	m_stcPos[_eLOADER_ZL_DOWN_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataLoader.Info.m_dLoaderZR_Down_Pos);
	m_stcPos[_eLOADER_ZR_DOWN_POS].SetWindowText(Str);
#pragma endregion

#pragma region //Loader X
	Str.Format(_T("%.5f"), CManualData::m_ManualDataLoader.Info.m_dLoaderX_Wait_Pos);
	m_stcPos[_eLOADER_X_WAIT_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataLoader.Info.m_dLoaderX_Tension_Offset);
	m_stcPos[_eLOADER_X_TENSION_OFFSET].SetWindowText(Str);
#pragma endregion

#pragma region //Loader Y
	//21.02.10 SJC
	Str.Format(_T("%.5f"), CManualData::m_ManualDataLoader.Info.m_dLoaderY_Wait_Pos);
	m_stcPos[_eLOADER_Y_WAIT_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataLoader.Info.m_dLoaderY_Stick_Load_Pos);
	m_stcPos[_eLOADER_Y_STICK_LOAD_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataLoader.Info.m_dLoaderY_Stick_Unload_Pos);
	m_stcPos[_eLOADER_Y_STICK_UNLOAD_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataLoader.Info.m_dLoaderY_Inspection_Pos);
	m_stcPos[_eLOADER_Y_INSPECTION_POS].SetWindowText(Str);
#pragma endregion
	//21.02.26 SJC
	Str.Format(_T("%.5f"), CManualData::m_ManualDataLoader.Info.m_dLoaderZ_Inspection_Pos);
	m_stcPos[_eLOADER_Z_INSPECTION_POS].SetWindowText(Str);
}
//------------------------------------------------------------------
BOOL CManual_Sub_Loader_Fixed_Pos::CheckChangeData()
{
	CString Str = _T(""), StrMsg = _T("");

#pragma region //KJT 20210806 Interlock Add
	double dOffset = 0.0;
	m_editPos[_eLOADER_X_TENSION_OFFSET].GetWindowText(Str);
	dOffset = _ttof(Str);
	if (dOffset < CSystemData::m_Coordinate.Info.dMax_Tension_Offset_LoaderX)
	{
		StrMsg.Format(_T("Loader X Tension Offset Value Error !! (Offset:%.5f < %.5fmm)"), dOffset, CSystemData::m_Coordinate.Info.dMax_Tension_Offset_LoaderX);
		AfxMessageBox(StrMsg);
		return FALSE;
	}
#pragma endregion

#pragma region //Loader Z
	m_stcPos[_eLOADER_Z_WAIT_POS].GetWindowText(Str);
	CManualData::m_ManualDataLoader.Info.m_dLoaderZ_Wait_Pos = _ttof(Str);
	m_stcPos[_eLOADER_Z_STICK_LOAD_IN_BOX_1ST_POS].GetWindowText(Str);
	CManualData::m_ManualDataLoader.Info.m_dLoaderZ_StickLoadInBox1st_Pos = _ttof(Str);
	m_stcPos[_eLOADER_Z_VIBRATION_POS].GetWindowText(Str);
	CManualData::m_ManualDataLoader.Info.m_dLoaderZ_Vibration_Pos = _ttof(Str);
	m_stcPos[_eLOADER_Z_STICK_UNLOAD_TO_STAGE_POS].GetWindowText(Str);
	CManualData::m_ManualDataLoader.Info.m_dLoaderZ_StickUnloadToStage_Pos = _ttof(Str);

	m_stcPos[_eLOADER_Z_STICK_LOAD_IN_STAGE_1ST_POS].GetWindowText(Str);
	CManualData::m_ManualDataLoader.Info.m_dLoaderZ_StickLoadInStage1st_Pos = _ttof(Str);
	m_stcPos[_eLOADER_Z_VIBRATION_OFFSET].GetWindowText(Str);
	CManualData::m_ManualDataLoader.Info.m_dLoaderZ_VibrationOffset = _ttof(Str);
	m_stcPos[_eLOADER_Z_STICK_UNLOAD_TO_BOX_POS].GetWindowText(Str);
	CManualData::m_ManualDataLoader.Info.m_dLoaderZ_StickUnoadToBox_Pos = _ttof(Str);

	
	m_stcPos[_eLOADER_Z_STEP_DOWN_COUNT].GetWindowText(Str);
	CManualData::m_ManualDataLoader.Info.m_nLoaderZ_StepDownCount = _ttoi(Str);
	m_stcPos[_eLOADER_Z_STEP_DOWN_OFFSET].GetWindowText(Str);
	CManualData::m_ManualDataLoader.Info.m_dLoaderZ_StepDownOffset = _ttof(Str);
	m_stcPos[_eLOADER_Z_STEP_UP_OFFSET].GetWindowText(Str);
	CManualData::m_ManualDataLoader.Info.m_dLoaderZ_StepUpOffset = _ttof(Str);
	m_stcPos[_eLOADER_Z_VIBRATION_COUNT].GetWindowText(Str);
	CManualData::m_ManualDataLoader.Info.m_nLoaderZ_VibrationCount = _ttoi(Str);
	m_stcPos[_eLOADER_Z_VIBRATION_VEL].GetWindowText(Str);
	CManualData::m_ManualDataLoader.Info.m_dLoaderZ_VibrationVel = _ttof(Str);	

#pragma endregion

#pragma region //Loader SUB Z(ZL,ZR)
	m_stcPos[_eLOADER_ZL_WAIT_POS].GetWindowText(Str);
	CManualData::m_ManualDataLoader.Info.m_dLoaderZL_Wait_Pos = _ttof(Str);
	m_stcPos[_eLOADER_ZR_WAIT_POS].GetWindowText(Str);
	CManualData::m_ManualDataLoader.Info.m_dLoaderZR_Wait_Pos = _ttof(Str);
	m_stcPos[_eLOADER_ZL_DOWN_POS].GetWindowText(Str);
	CManualData::m_ManualDataLoader.Info.m_dLoaderZL_Down_Pos = _ttof(Str);
	m_stcPos[_eLOADER_ZR_DOWN_POS].GetWindowText(Str);
	CManualData::m_ManualDataLoader.Info.m_dLoaderZR_Down_Pos = _ttof(Str);
#pragma endregion

#pragma region //Loader X
	m_stcPos[_eLOADER_X_WAIT_POS].GetWindowText(Str);
	CManualData::m_ManualDataLoader.Info.m_dLoaderX_Wait_Pos = _ttof(Str);
	m_stcPos[_eLOADER_X_TENSION_OFFSET].GetWindowText(Str);
	CManualData::m_ManualDataLoader.Info.m_dLoaderX_Tension_Offset = _ttof(Str);
#pragma endregion
#pragma region //Loader Y
	//21.02.10 sjc
	m_stcPos[_eLOADER_Y_WAIT_POS].GetWindowText(Str);
	CManualData::m_ManualDataLoader.Info.m_dLoaderY_Wait_Pos = _ttof(Str);
	m_stcPos[_eLOADER_Y_STICK_LOAD_POS].GetWindowText(Str);
	CManualData::m_ManualDataLoader.Info.m_dLoaderY_Stick_Load_Pos = _ttof(Str);
	m_stcPos[_eLOADER_Y_STICK_UNLOAD_POS].GetWindowText(Str);
	CManualData::m_ManualDataLoader.Info.m_dLoaderY_Stick_Unload_Pos = _ttof(Str);
	m_stcPos[_eLOADER_Y_INSPECTION_POS].GetWindowText(Str);
	CManualData::m_ManualDataLoader.Info.m_dLoaderY_Inspection_Pos = _ttof(Str);
#pragma endregion
	m_stcPos[_eLOADER_Z_INSPECTION_POS].GetWindowText(Str);
	CManualData::m_ManualDataLoader.Info.m_dLoaderZ_Inspection_Pos = _ttof(Str);

	return TRUE;
}

enum_Axis CManual_Sub_Loader_Fixed_Pos::GetAxisNo(enum_Loader_Axis eLoaderAxis, CString *strDiscription)
{
	CString Str = _T("");

	enum_Axis eAxis = AXIS_NONE;
	switch (eLoaderAxis)
	{
	case _eMANUAL_LOADER_AXIS_Z:		eAxis = AXIS_LOADER_Z; Str = _T("Loader Z");  break;
	case _eMANUAL_LOADER_AXIS_X:		eAxis = AXIS_LOADER_X; Str = _T("Loader X"); break;
	//case _eMANUAL_LOADER_AXIS_SUB_ZL:	eAxis = AXIS_LOADER_ZL; Str = _T("Loader Sub ZL"); break;
	//case _eMANUAL_LOADER_AXIS_SUB_ZR:	eAxis = AXIS_LOADER_ZR; Str = _T("Loader Sub ZR"); break;
	case _eMANUAL_LOADER_AXIS_Y:		eAxis = AXIS_LOADER_YL; Str = _T("Loader Y"); break;
	}

	*strDiscription = Str;

	return eAxis;
}

BOOL CManual_Sub_Loader_Fixed_Pos::ManualAbsMove(enum_Loader_Axis eLoaderAxis, double dPos)
{
	CString strAxisName = _T(""), Str = _T("");
	double dVel = 0.0, dAccel = 0.0, dDecel = 0.0;
	enum_Axis eAxis = GetAxisNo(eLoaderAxis, &strAxisName);
	double dCurPos = 0.0;

	SharedInfo::GetManualSpeed(eAxis, eAXIS_SPEED_MEDIUM, &dVel, &dAccel, &dDecel);

	Str.Format(_T("%s Abs Move To Pos: %.5f Start?"), strAxisName, dPos);
	int nResult = AfxMessageBox(Str, MB_OKCANCEL);
	if (nResult == IDOK)
	{
		dCurPos = SharedInfo::GetCmdPos(eAxis);

		Devs::m_JogMotion.AbsMove(eAxis, dPos, dVel, dAccel, dDecel);

		Str.Format(_T("[Manual-Loader-Fixed] %s Abs Move %.5f -> %.5f"), strAxisName, dCurPos, dPos);
		Total_Msg(Str);
	}

	return TRUE;
}

double CManual_Sub_Loader_Fixed_Pos::GetTargetPos(enum_Loader_Pos eLoaderPos)
{
	CString Str = _T("");
	double dPos = 0.0;
	m_editPos[eLoaderPos].GetWindowText(Str);
	dPos = _ttof(Str);

	return dPos;
}

#pragma region //Get
//Loader Z
void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderGetWaitPosLoaderZ()
{
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_LOADER_Z);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eLOADER_Z_WAIT_POS].SetWindowText(Str);
}
void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderGetStickLoadInBox1stPosLoaderZ()
{
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_LOADER_Z);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eLOADER_Z_STICK_LOAD_IN_BOX_1ST_POS].SetWindowText(Str);
}
void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderGetStickLoadInBox2ndPosLoaderZ()
{
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_LOADER_Z);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eLOADER_Z_VIBRATION_POS].SetWindowText(Str);
}
void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderGetStickUnloadToStagePosLoaderZ()
{
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_LOADER_Z);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eLOADER_Z_STICK_UNLOAD_TO_STAGE_POS].SetWindowText(Str);
}
void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderGetStickLoadInStage1stPosLoaderZ()
{
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_LOADER_Z);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eLOADER_Z_STICK_LOAD_IN_STAGE_1ST_POS].SetWindowText(Str);
}
void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderGetStickLoadInStage2ndPosLoaderZ()
{
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_LOADER_Z);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eLOADER_Z_VIBRATION_OFFSET].SetWindowText(Str);
}
void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderGetStickUnloadToBoxPosLoaderZ()
{
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_LOADER_Z);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eLOADER_Z_STICK_UNLOAD_TO_BOX_POS].SetWindowText(Str);
}



//Loader X
void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderGetWaitPosLoaderX()
{
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_LOADER_X);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eLOADER_X_WAIT_POS].SetWindowText(Str);
}
#pragma endregion

#pragma region //Set
//Loader Z
void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderSetWaitPosLoaderZ()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eLOADER_Z_WAIT_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Loader-Fixed] Loader Z Pos Set Click (Wait Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}
void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderSetStickLoadInBox1stPosLoaderZ()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eLOADER_Z_STICK_LOAD_IN_BOX_1ST_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Loader-Fixed] Loader Z Pos Set Click (Stick Load In Box 1st Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}
void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderSetStickLoadInBox2ndPosLoaderZ()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eLOADER_Z_VIBRATION_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Loader-Fixed] Loader Z Pos Set Click (Vibration Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}
void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderSetStickUnloadToStagePosLoaderZ()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eLOADER_Z_STICK_UNLOAD_TO_STAGE_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Loader-Fixed] Loader Z Pos Set Click (Stick Unload To Stage Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}
void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderSetStickLoadInStage1stPosLoaderZ()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eLOADER_Z_STICK_LOAD_IN_STAGE_1ST_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Loader-Fixed] Loader Z Pos Set Click (Stick Load In Stage 1st Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}


void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderSetVibrationCount()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eLOADER_Z_VIBRATION_COUNT;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	int nCount = _ttoi(Str);
	StrMsg.Format(_T("[Manual-Loader-Fixed] Loader Z Pos Set Click (Vibration Count : %d)"), nCount);
	Total_Msg(StrMsg);
}


void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderSetStickLoadInStage2ndPosLoaderZ()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eLOADER_Z_VIBRATION_OFFSET;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Loader-Fixed] Loader Z Pos Set Click (Vibration Offset : %.5f)"), dPos);
	Total_Msg(StrMsg);
}

void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderSetVibrationVel()
{
	// TODO: Add your control notification handler code here

	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eLOADER_Z_VIBRATION_VEL;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dVel = _ttof(Str);
	StrMsg.Format(_T("[Manual-Loader-Fixed] Loader Z Pos Set Click (Vibration Vel : %.5f)"), dVel);
	Total_Msg(StrMsg);
}


void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderSetStickUnloadToBoxPosLoaderZ()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eLOADER_Z_STICK_UNLOAD_TO_BOX_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Loader-Fixed] Loader Z Pos Set Click (Stick Unload To Box Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}

void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderSetStepDownCount()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eLOADER_Z_STEP_DOWN_COUNT;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	int nCount = _ttoi(Str);
	StrMsg.Format(_T("[Manual-Loader-Fixed] Loader Z Set Click (Step Down Count : %d)"), nCount);
	Total_Msg(StrMsg);
}

void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderSetStepDownOffsetLoaderZ()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eLOADER_Z_STEP_DOWN_OFFSET;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Loader-Fixed] Loader Z Set Click (Step Down Offset : %.5f)"), dPos);
	Total_Msg(StrMsg);
}

void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderSetStepUpOffsetLoaderZ()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eLOADER_Z_STEP_UP_OFFSET;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Loader-Fixed] Loader Z Set Click (Step up Offset : %.5f)"), dPos);
	Total_Msg(StrMsg);
}


//Loader X
void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderSetWaitPosLoaderX()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eLOADER_X_WAIT_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Loader-Fixed] Loader X Pos Set Click (Wait Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}
void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderSetTensionOffsetLoaderX()
{
	CString Str = _T(""), StrMsg = _T("");
	double dOffset = 0.0;
	int nIndex = _eLOADER_X_TENSION_OFFSET;
	m_editPos[nIndex].GetWindowText(Str);

#pragma region //KJT 20210721 Interlock Add
	dOffset = _ttof(Str);
	if (dOffset < CSystemData::m_Coordinate.Info.dMax_Tension_Offset_LoaderX)
	{
		StrMsg.Format(_T("Loader X Tension Offset Set Error !! (Offset:%.5f < %.5fmm)"), dOffset, CSystemData::m_Coordinate.Info.dMax_Tension_Offset_LoaderX);
		AfxMessageBox(StrMsg);
		return;
	}
#pragma endregion

	m_stcPos[nIndex].SetWindowText(Str);

	StrMsg.Format(_T("[Manual-Loader-Fixed] Loader X Tension Offset Set Click (Pos : %.5f)"), dOffset);
	Total_Msg(StrMsg);
}
#pragma endregion

#pragma region //Move
//Loader Z
void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderMoveWaitPosLoaderZ()
{	
	double dPos = GetTargetPos(_eLOADER_Z_WAIT_POS);

	CString Str;
	Str.Format(_T("Loader Z Move ? (Wait Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	ManualAbsMove(_eMANUAL_LOADER_AXIS_Z, dPos);
}
void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderMoveStickLoadInBox1stPosLoaderZ()
{
	if (Devs::m_LoaderMotion.Is_LoaderY_Stick_LoadPos() == FALSE)
	{
		AfxMessageBox(_T("Check Load Y Stick LoadPos !!!"));
		return;
	}

	double dPos = GetTargetPos(_eLOADER_Z_STICK_LOAD_IN_BOX_1ST_POS);

	CString Str;
	Str.Format(_T("Loader Z Move ? (Stick Load In Box 1st Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	ManualAbsMove(_eMANUAL_LOADER_AXIS_Z, dPos);
}
void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderMoveStickLoadInBox2ndPosLoaderZ()
{
	if (Devs::m_LoaderMotion.Is_LoaderY_Stick_LoadPos() == FALSE)
	{
		AfxMessageBox(_T("Check Load Y Stick LoadPos !!!"));

		return;
	}

	double dPos = GetTargetPos(_eLOADER_Z_VIBRATION_POS);

	CString Str;
	Str.Format(_T("Loader Z Move ? (Vibration Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	ManualAbsMove(_eMANUAL_LOADER_AXIS_Z, dPos);
}
void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderMoveStickUnloadToStagePosLoaderZ()
{
	if (Devs::m_LoaderMotion.Is_LoaderY_Stick_UnloadPos() == FALSE)
	{
		AfxMessageBox(_T("Check Load Y Stick UnLoadPos !!!"));
		return;
	}

	double dPos = GetTargetPos(_eLOADER_Z_STICK_UNLOAD_TO_STAGE_POS);

	CString Str;
	Str.Format(_T("Loader Z Move ? (Stick Unload To Stage Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	ManualAbsMove(_eMANUAL_LOADER_AXIS_Z, dPos);
}
void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderMoveStickLoadInStage1stPosLoaderZ()
{
	if (Devs::m_LoaderMotion.Is_LoaderY_Stick_UnloadPos() == FALSE)
	{
		AfxMessageBox(_T("Check Load Y Stick UnLoadPos !!!"));
		return;
	}

	double dPos = GetTargetPos(_eLOADER_Z_STICK_LOAD_IN_STAGE_1ST_POS);

	CString Str;
	Str.Format(_T("Loader Z Move ? (Stick Load In Stage 1st Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	ManualAbsMove(_eMANUAL_LOADER_AXIS_Z, dPos);
}
void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderMoveStickLoadInStage2ndPosLoaderZ()
{
	double dPos = GetTargetPos(_eLOADER_Z_VIBRATION_OFFSET);
	ManualAbsMove(_eMANUAL_LOADER_AXIS_Z, dPos);
}
void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderMoveStickUnloadToBoxPosLoaderZ()
{
	if (Devs::m_LoaderMotion.Is_LoaderY_Stick_LoadPos() == FALSE)
	{
		AfxMessageBox(_T("Check Load Y Stick LoadPos !!!"));
		return;
	}

	double dPos = GetTargetPos(_eLOADER_Z_STICK_UNLOAD_TO_BOX_POS);

	CString Str;
	Str.Format(_T("Loader Z Move ? (Stick Unload To Box Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	ManualAbsMove(_eMANUAL_LOADER_AXIS_Z, dPos);
}
//Loader X
void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderMoveWaitPosLoaderX()
{
	double dPos = GetTargetPos(_eLOADER_X_WAIT_POS);

	CString Str;
	Str.Format(_T("Loader X Move ? (Wait Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	ManualAbsMove(_eMANUAL_LOADER_AXIS_X, dPos);
}
#pragma endregion




void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderFixedSave()
{
	CheckChangeData();
	CManualData::m_ManualDataLoader.Save();

	AfxMessageBox(_T("Save Ok"));
}


//21.02.10 SJC
//LOADER Y
void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderGetWaitPosLoaderY()
{
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_LOADER_YL);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eLOADER_Y_WAIT_POS].SetWindowText(Str);
}


void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderGetStickLoadPosLoaderY()
{
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_LOADER_YL);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eLOADER_Y_STICK_LOAD_POS].SetWindowText(Str);
}


void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderGetStickUnloadPosLoaderY()
{
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_LOADER_YL);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eLOADER_Y_STICK_UNLOAD_POS].SetWindowText(Str);
}


void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderGetInspectionPosLoaderY()
{
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_LOADER_YL);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eLOADER_Y_INSPECTION_POS].SetWindowText(Str);
}

//set
void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderSetWaitPosLoaderY()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eLOADER_Y_WAIT_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Loader-Fixed] Loader Y Pos Set Click (Wait Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}


void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderSetStickLoadPosLoaderY()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eLOADER_Y_STICK_LOAD_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Loader-Fixed] Loader Y Pos Set Click (Stick Load Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}


void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderSetStickUnloadPosLoaderY()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eLOADER_Y_STICK_UNLOAD_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Loader-Fixed] Loader Y Pos Set Click (Stick Unload Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}


void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderSetInspectionPosLoaderY()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eLOADER_Y_INSPECTION_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Loader-Fixed] Loader Y Pos Set Click (Inspection Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}

//move
void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderMoveWaitPosLoaderY()
{
	double dPos = SharedInfo::GetCmdPos(AXIS_LOADER_Z);
	if (dPos < CManualData::m_ManualDataLoader.Info.m_dLoaderZ_Wait_Pos)
	{
		AfxMessageBox(_T("Check Load Z WaitPos !!!"));
		return;
	}

	dPos = GetTargetPos(_eLOADER_Y_WAIT_POS);

	CString Str;
	Str.Format(_T("Loader Y Move ? (Wait Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	ManualAbsMove(_eMANUAL_LOADER_AXIS_Y, dPos);
}


void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderMoveStickLoadPosLoaderY()
{
	double dPos = SharedInfo::GetCmdPos(AXIS_LOADER_Z);
	if (dPos < CManualData::m_ManualDataLoader.Info.m_dLoaderZ_Wait_Pos)
	{
		AfxMessageBox(_T("Check Load Z WaitPos !!!"));
		return;
	}

	dPos = GetTargetPos(_eLOADER_Y_STICK_LOAD_POS);

	CString Str;
	Str.Format(_T("Loader Y Move ? (Stick Load Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	ManualAbsMove(_eMANUAL_LOADER_AXIS_Y, dPos);
}


void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderMoveStickUnloadPosLoaderY()
{
	double dPos = SharedInfo::GetCmdPos(AXIS_LOADER_Z);
	if (dPos < CManualData::m_ManualDataLoader.Info.m_dLoaderZ_Wait_Pos)
	{
		AfxMessageBox(_T("Check Load Z WaitPos !!!"));
		return;
	}

	dPos = SharedInfo::GetCmdPos(AXIS_VIRTUAL_GANTRY_Y);
	if (dPos < (CManualData::m_ManualDataGantry.Info.m_dGantry_Y_Loading_Safe_Pos - 0.1))
	{
		AfxMessageBox(_T("Check Gantry Y Loading SafePos !!!"));
		return;
	}

	dPos = GetTargetPos(_eLOADER_Y_STICK_UNLOAD_POS);

	CString Str;
	Str.Format(_T("Loader Y Move ? (Stick Unload Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	ManualAbsMove(_eMANUAL_LOADER_AXIS_Y, dPos);
}


void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderMoveInspectionPosLoaderY()
{
	double dPos = SharedInfo::GetCmdPos(AXIS_LOADER_Z);
	if (dPos < CManualData::m_ManualDataLoader.Info.m_dLoaderZ_Wait_Pos)
	{
		AfxMessageBox(_T("Check Load Z WaitPos !!!"));
		return;
	}

	dPos = GetTargetPos(_eLOADER_Y_INSPECTION_POS);

	CString Str;
	Str.Format(_T("Loader Y Move ? (Box Cam Inspection Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	ManualAbsMove(_eMANUAL_LOADER_AXIS_Y, dPos);
}


void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderGetStickAlignPosLoaderZ()
{
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_LOADER_Z);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eLOADER_Z_INSPECTION_POS].SetWindowText(Str);
}


void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderSetStickAlignPosLoaderZ()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eLOADER_Z_INSPECTION_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Loader-Fixed] Loader Z Inspect Pos (Stick Inspect Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}


void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderMoveStickAlignPosLoaderZ()
{
	if (Devs::m_LoaderMotion.Is_LoaderY_Stick_LoadPos() == FALSE)
	{
		AfxMessageBox(_T("Check Load Y Stick LoadPos !!!"));
		return;
	}

	double dPos = GetTargetPos(_eLOADER_Z_INSPECTION_POS);

	CString Str;
	Str.Format(_T("Loader Z Move ? (Box Align Inspection Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	ManualAbsMove(_eMANUAL_LOADER_AXIS_Z, dPos);
}


void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderGetWaitPosLoaderZl()
{
	// TODO: Add your control notification handler code here

	//CString Str = _T("");
	//double dCurPos = SharedInfo::GetCmdPos(AXIS_LOADER_ZL);
	//Str.Format(_T("%.5f"), dCurPos);
	//m_editPos[_eLOADER_ZL_WAIT_POS].SetWindowText(Str);
}


void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderGetWaitPosLoaderZr()
{
	// TODO: Add your control notification handler code here

	//CString Str = _T("");
	//double dCurPos = SharedInfo::GetCmdPos(AXIS_LOADER_ZR);
	//Str.Format(_T("%.5f"), dCurPos);
	//m_editPos[_eLOADER_ZR_WAIT_POS].SetWindowText(Str);
}



void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderGetDownPosLoaderZl()
{
	// TODO: Add your control notification handler code here

	//CString Str = _T("");
	//double dCurPos = SharedInfo::GetCmdPos(AXIS_LOADER_ZL);
	//Str.Format(_T("%.5f"), dCurPos);
	//m_editPos[_eLOADER_ZL_DOWN_POS].SetWindowText(Str);
}



void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderGetDownPosLoaderZr()
{
	// TODO: Add your control notification handler code here

	//CString Str = _T("");
	//double dCurPos = SharedInfo::GetCmdPos(AXIS_LOADER_ZR);
	//Str.Format(_T("%.5f"), dCurPos);
	//m_editPos[_eLOADER_ZR_DOWN_POS].SetWindowText(Str);
}


void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderSetWaitPosLoaderZl()
{
	// TODO: Add your control notification handler code here

	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eLOADER_ZL_WAIT_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Loader-Fixed] Loader ZL Pos Set Click (Wait Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}


void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderSetWaitPosLoaderZr()
{
	// TODO: Add your control notification handler code here

	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eLOADER_ZR_WAIT_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Loader-Fixed] Loader ZR Pos Set Click (Wait Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}

void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderSetDownPosLoaderZl()
{
	// TODO: Add your control notification handler code here

	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eLOADER_ZL_DOWN_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Loader-Fixed] Loader ZL Pos Set Click (Down Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}

void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderSetDownPosLoaderZr()
{
	// TODO: Add your control notification handler code here

	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eLOADER_ZR_DOWN_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Loader-Fixed] Loader ZR Pos Set Click (Down Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}


void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderMoveWaitPosLoaderZl()
{
	// TODO: Add your control notification handler code here

	double dPos = GetTargetPos(_eLOADER_ZL_WAIT_POS);
	
	CString Str;
	Str.Format(_T("Loader ZL Move ? (Wait Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	ManualAbsMove(_eMANUAL_LOADER_AXIS_SUB_ZL, dPos);
}


void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderMoveWaitPosLoaderZr()
{
	// TODO: Add your control notification handler code here

	double dPos = GetTargetPos(_eLOADER_ZR_WAIT_POS);

	CString Str;
	Str.Format(_T("Loader ZR Move ? (Wait Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	ManualAbsMove(_eMANUAL_LOADER_AXIS_SUB_ZR, dPos);
}


void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderMoveDownPosLoaderZl()
{
	// TODO: Add your control notification handler code here

	double dPos = GetTargetPos(_eLOADER_ZL_DOWN_POS);

	CString Str;
	Str.Format(_T("Loader ZL Move ? (Down Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	ManualAbsMove(_eMANUAL_LOADER_AXIS_SUB_ZL, dPos);
}


void CManual_Sub_Loader_Fixed_Pos::OnBnClickedButtonManualSubLoaderMoveDownPosLoaderZr()
{
	// TODO: Add your control notification handler code here

	double dPos = GetTargetPos(_eLOADER_ZR_DOWN_POS);

	CString Str;
	Str.Format(_T("Loader ZR Move ? (Down Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	ManualAbsMove(_eMANUAL_LOADER_AXIS_SUB_ZR, dPos);
}
