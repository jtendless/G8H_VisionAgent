// Manual_Sub_Gantry_Fixed_Pos.cpp: 구현 파일
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "Manual_Sub_Gantry_Fixed_Pos.h"
#include "afxdialogex.h"


// CManual_Sub_Gantry_Fixed_Pos 대화 상자

IMPLEMENT_DYNAMIC(CManual_Sub_Gantry_Fixed_Pos, CDialogEx)

CManual_Sub_Gantry_Fixed_Pos::CManual_Sub_Gantry_Fixed_Pos(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_MANUAL_SUB_GANTRY_FIXED_POS, pParent)
{
	Create(IDD_DLG_MANUAL_SUB_GANTRY_FIXED_POS, pParent);
}

CManual_Sub_Gantry_Fixed_Pos::~CManual_Sub_Gantry_Fixed_Pos()
{
}

void CManual_Sub_Gantry_Fixed_Pos::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CManual_Sub_Gantry_Fixed_Pos, CDialogEx)
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_GET_WAIT_POS_GANTRY_X, &CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonGetWaitPosGantryX)
	ON_BN_CLICKED(IDC_BUTTON_GET_WAIT_POS_GANTRY_Y, &CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonGetWaitPosGantryY)
	ON_BN_CLICKED(IDC_BUTTON_GET_STICK_LOAD_IN_BOX_POS_GANTRY_Y, &CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonGetStickLoadInBoxPosGantryY)
	ON_BN_CLICKED(IDC_BUTTON_GET_UNLOAD_PAPER_POS_GANTRY_Y, &CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonGetUnloadPaperPosGantryY)
	ON_BN_CLICKED(IDC_BUTTON_GET_STICK_UNLOAD_TO_STAGE_POS_GANTRY_Y, &CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonGetStickUnloadToStagePosGantryY)
	ON_BN_CLICKED(IDC_BUTTON_GET_STICK_LOAD_IN_STAGE_POS_GANTRY_Y, &CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonGetStickLoadInStagePosGantryY)
	ON_BN_CLICKED(IDC_BUTTON_GET_STICK_UNLOAD_TO_BOX_POS_GANTRY_Y, &CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonGetStickUnloadToBoxPosGantryY)
	ON_BN_CLICKED(IDC_BUTTON_GET_WAIT_POS_CAMERA_Z1, &CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonGetWaitPosCameraZ1)	
	ON_BN_CLICKED(IDC_BUTTON_MOVE_WAIT_POS_GANTRY_X, &CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonMoveWaitPosGantryX)
	ON_BN_CLICKED(IDC_BUTTON_MOVE_WAIT_POS_GANTRY_Y, &CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonMoveWaitPosGantryY)
	ON_BN_CLICKED(IDC_BUTTON_SET_WAIT_POS_GANTRY_X, &CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonSetWaitPosGantryX)
	ON_BN_CLICKED(IDC_BUTTON_SET_WAIT_POS_GANTRY_Y, &CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonSetWaitPosGantryY)
	ON_BN_CLICKED(IDC_BUTTON_SET_STICK_LOAD_IN_BOX_POS_GANTRY_Y, &CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonSetStickLoadInBoxPosGantryY)
	ON_BN_CLICKED(IDC_BUTTON_SET_UNLOAD_PAPER_POS_GANTRY_Y, &CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonSetUnloadPaperPosGantryY)
	ON_BN_CLICKED(IDC_BUTTON_SET_STICK_UNLOAD_TO_STAGE_POS_GANTRY_Y, &CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonSetStickUnloadToStagePosGantryY)
	ON_BN_CLICKED(IDC_BUTTON_SET_STICK_LOAD_IN_STAGE_POS_GANTRY_Y, &CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonSetStickLoadInStagePosGantryY)
	ON_BN_CLICKED(IDC_BUTTON_SET_STICK_UNLOAD_TO_BOX_POS_GANTRY_Y, &CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonSetStickUnloadToBoxPosGantryY)
	ON_BN_CLICKED(IDC_BUTTON_SET_WAIT_POS_CAMERA_Z1, &CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonSetWaitPosCameraZ1)	
	ON_BN_CLICKED(IDC_BUTTON_MOVE_STICK_LOAD_IN_BOX_POS_GANTRY_Y, &CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonMoveStickLoadInBoxPosGantryY)
	ON_BN_CLICKED(IDC_BUTTON_MOVE_UNLOAD_PAPER_POS_GANTRY_Y, &CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonMoveUnloadPaperPosGantryY)
	ON_BN_CLICKED(IDC_BUTTON_MOVE_STICK_UNLOAD_TO_STAGE_POS_GANTRY_Y, &CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonMoveStickUnloadToStagePosGantryY)
	ON_BN_CLICKED(IDC_BUTTON_MOVE_WAIT_POS_CAMERA_Z1, &CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonMoveWaitPosCameraZ1)		
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GANTRY_FIXED_SAVE, &CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonManualSubGantryFixedSave)
	ON_BN_CLICKED(IDC_BUTTON_MOVE_STICK_LOAD_IN_STAGE_POS_GANTRY_Y, &CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonMoveStickLoadInStagePosGantryY)
	ON_BN_CLICKED(IDC_BUTTON_GET_INSPECTION_REVIEW_POS_CAMERA_Z3, &CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonGetInspectionReviewPosCameraZ1)
	ON_BN_CLICKED(IDC_BUTTON_GET_MAPPING_REVIEW_POS_CAMERA_Z3, &CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonGetMappingReviewPosCameraZ1)
	ON_BN_CLICKED(IDC_BUTTON_SET_INSPECTION_REVIEW_POS_CAMERA_Z3, &CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonSetInspectionReviewPosCameraZ1)
	ON_BN_CLICKED(IDC_BUTTON_SET_MAPPING_REVIEW_POS_CAMERA_Z3, &CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonSetMappingReviewPosCameraZ1)
	ON_BN_CLICKED(IDC_BUTTON_MOVE_INSPECTION_REVIEW_POS_CAMERA_Z3, &CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonMoveInspectionReviewPosCameraZ1)
	ON_BN_CLICKED(IDC_BUTTON_MOVE_MAPPING_REVIEW_POS_CAMERA_Z3, &CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonMoveMappingReviewPosCameraZ1)
END_MESSAGE_MAP()


// CManual_Sub_Gantry_Fixed_Pos 메시지 처리기

BOOL CManual_Sub_Gantry_Fixed_Pos::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitCtrl();

	return TRUE;
}
//------------------------------------------------------------------
void	CManual_Sub_Gantry_Fixed_Pos::InitCtrl()
{
	//Static Pos
	m_stcPos[_eGANTRY_X_WAIT_POS].SubclassDlgItem(IDC_STATIC_CURRENT_WAIT_POS_GANTRY_X, this);

	m_stcPos[_eGANTRY_Y_WAIT_POS].SubclassDlgItem(IDC_STATIC_CURRENT_WAIT_POS_GANTRY_Y, this);
	m_stcPos[_eGANTRY_Y_STICK_LOAD_IN_BOX_POS].SubclassDlgItem(IDC_STATIC_CURRENT_STICK_LOAD_IN_BOX_POS_GANTRY_Y, this);
	m_stcPos[_eGANTRY_Y_PAPER_UNLOAD_POS].SubclassDlgItem(IDC_STATIC_CURRENT_UNLOAD_PAPER_POS_GANTRY_Y, this);
	m_stcPos[_eGANTRY_Y_STICK_UNLOAD_TO_STAGE_POS].SubclassDlgItem(IDC_STATIC_CURRENT_STICK_UNLOAD_TO_STAGE_POS_GANTRY_Y, this);
	m_stcPos[_eGANTRY_Y_STICK_LOAD_IN_STAGE_POS].SubclassDlgItem(IDC_STATIC_CURRENT_STICK_LOAD_IN_STAGE_POS_GANTRY_Y, this);
	m_stcPos[_eGANTRY_Y_STICK_UNLOAD_TO_BOX_POS].SubclassDlgItem(IDC_STATIC_CURRENT_STICK_UNLOAD_TO_BOX_POS_GANTRY_Y, this);
	//21.02.09 SJC
	m_stcPos[_eGANTRY_Y_LOADING_SAFE_POS].SubclassDlgItem(IDC_STATIC_CURRENT_LOAD_SAFE_POS_GANTRY_Y, this);
	m_stcPos[_eGANTRY_Y_UNLOADING_SAFE_POS].SubclassDlgItem(IDC_STATIC_CURRENT_UNLOAD_SAFE_POS_GANTRY_Y, this);
	//
	m_stcPos[_eGANTRY_Z1_WAIT_POS].SubclassDlgItem(IDC_STATIC_CURRENT_WAIT_POS_CAMERA_Z1, this);	
	m_stcPos[_eGANTRY_Z1_PRE_ALIGN_POS].SubclassDlgItem(IDC_STATIC_CURRENT_PRE_ALIGN_POS_CAMERA_Z2, this);
	m_stcPos[_eGANTRY_Z1_INSPECTION_REVIEW_POS].SubclassDlgItem(IDC_STATIC_CURRENT_INSPECTION_REVIEW_POS_CAMERA_Z3, this);
	m_stcPos[_eGANTRY_Z1_MAPPING_REVIEW_POS].SubclassDlgItem(IDC_STATIC_CURRENT_MAPPING_REVIEW_POS_CAMERA_Z3, this);

	//m_stcPos[_eGANTRY_Z1_INSPECTION_AOI_POS].SubclassDlgItem(IDC_STATIC_CURRENT_INSPECTION_AOI_POS_CAMERA_Z1, this);
	//

	//m_stcPos[_eGANTRY_Z2_WAIT_POS].SubclassDlgItem(IDC_STATIC_CURRENT_WAIT_POS_CAMERA_Z2, this);
	//m_stcPos[_eGANTRY_Z2_PRE_ALIGN_POS].SubclassDlgItem(IDC_STATIC_CURRENT_PRE_ALIGN_POS_CAMERA_Z2, this);
	//m_stcPos[_eGANTRY_Z2_INSPECTION_3D_POS].SubclassDlgItem(IDC_STATIC_CURRENT_INSPECTION_3D_POS_CAMERA_Z2, this);	//21.02.09 SJC
	//m_stcPos[_eGANTRY_Z2_REVIEW_AOI_POS].SubclassDlgItem(IDC_STATIC_CURRENT_AOI_REVIEW_POS_CAMERA_Z2, this);

	//m_stcPos[_eGANTRY_Z3_WAIT_POS].SubclassDlgItem(IDC_STATIC_CURRENT_WAIT_POS_CAMERA_Z3, this);
	//m_stcPos[_eGANTRY_Z3_INSPECTION_REVIEW_POS].SubclassDlgItem(IDC_STATIC_CURRENT_INSPECTION_REVIEW_POS_CAMERA_Z3, this);
	//m_stcPos[_eGANTRY_Z3_MAPPING_REVIEW_POS].SubclassDlgItem(IDC_STATIC_CURRENT_MAPPING_REVIEW_POS_CAMERA_Z3, this);

	//m_stcPos[_eGANTRY_3D_CAMERA_SUB_Z_WAIT_POS].SubclassDlgItem(IDC_STATIC_CURRENT_WAIT_POS_3D_CAMERA_SUB_Z, this);
	
	//EditPos
	m_editPos[_eGANTRY_X_WAIT_POS].SubclassDlgItem(IDC_EDIT_WAIT_POS_GANTRY_X, this);

	m_editPos[_eGANTRY_Y_WAIT_POS].SubclassDlgItem(IDC_EDIT_WAIT_POS_GANTRY_Y, this);
	m_editPos[_eGANTRY_Y_STICK_LOAD_IN_BOX_POS].SubclassDlgItem(IDC_EDIT_STICK_LOAD_IN_BOX_POS_GANTRY_Y, this);
	m_editPos[_eGANTRY_Y_PAPER_UNLOAD_POS].SubclassDlgItem(IDC_EDIT_PAPER_UNLOAD_POS_GANTRY_Y, this);
	m_editPos[_eGANTRY_Y_STICK_UNLOAD_TO_STAGE_POS].SubclassDlgItem(IDC_EDIT_STICK_UNLOAD_TO_STAGE_POS_GANTRY_Y, this);
	m_editPos[_eGANTRY_Y_STICK_LOAD_IN_STAGE_POS].SubclassDlgItem(IDC_EDIT_STICK_LOAD_IN_STAGE_POS_GANTRY_Y, this);
	m_editPos[_eGANTRY_Y_STICK_UNLOAD_TO_BOX_POS].SubclassDlgItem(IDC_EDIT_STICK_UNLOAD_TO_BOX_POS_GANTRY_Y, this);

	//21.02.09 SJC
	m_editPos[_eGANTRY_Y_LOADING_SAFE_POS].SubclassDlgItem(IDC_EDIT_LOAD_SAFE_POS_GANTRY_Y, this);
	m_editPos[_eGANTRY_Y_UNLOADING_SAFE_POS].SubclassDlgItem(IDC_EDIT_UNLOAD_SAFE_POS_GANTRY_Y, this);
	//
	m_editPos[_eGANTRY_Z1_WAIT_POS].SubclassDlgItem(IDC_EDIT_WAIT_POS_CAMERA_Z1, this);
	m_editPos[_eGANTRY_Z1_PRE_ALIGN_POS].SubclassDlgItem(IDC_EDIT_PRE_ALIGN_POS_CAMERA_Z2, this);
	m_editPos[_eGANTRY_Z1_INSPECTION_REVIEW_POS].SubclassDlgItem(IDC_EDIT_INSPECTION_REVIEW_POS_CAMERA_Z3, this);
	m_editPos[_eGANTRY_Z1_MAPPING_REVIEW_POS].SubclassDlgItem(IDC_EDIT_MAPPING_REVIEW_POS_CAMERA_Z3, this);

	//m_editPos[_eGANTRY_Z1_INSPECTION_AOI_POS].SubclassDlgItem(IDC_EDIT_INSPECTION_AOI_POS_CAMERA_Z1, this);
	//
	//m_editPos[_eGANTRY_Z2_WAIT_POS].SubclassDlgItem(IDC_EDIT_WAIT_POS_CAMERA_Z2, this);	
	//m_editPos[_eGANTRY_Z2_PRE_ALIGN_POS].SubclassDlgItem(IDC_EDIT_PRE_ALIGN_POS_CAMERA_Z2, this);
	//m_editPos[_eGANTRY_Z2_INSPECTION_3D_POS].SubclassDlgItem(IDC_EDIT_INSPECTION_3D_POS_CAMERA_Z2, this);
	//m_editPos[_eGANTRY_Z2_REVIEW_AOI_POS].SubclassDlgItem(IDC_EDIT_AOI_REVIEW_POS_CAMERA_Z2, this);
	////
	//m_editPos[_eGANTRY_Z3_WAIT_POS].SubclassDlgItem(IDC_EDIT_WAIT_POS_CAMERA_Z3, this);
	//m_editPos[_eGANTRY_Z3_INSPECTION_REVIEW_POS].SubclassDlgItem(IDC_EDIT_INSPECTION_REVIEW_POS_CAMERA_Z3, this);
	//m_editPos[_eGANTRY_Z3_MAPPING_REVIEW_POS].SubclassDlgItem(IDC_EDIT_MAPPING_REVIEW_POS_CAMERA_Z3, this);

	//m_editPos[_eGANTRY_3D_CAMERA_SUB_Z_WAIT_POS].SubclassDlgItem(IDC_EDIT_WAIT_POS_3D_CAMERA_SUB_Z, this);
}
//------------------------------------------------------------------
void CManual_Sub_Gantry_Fixed_Pos::InitPara()
{
	CString Str = _T("");
	int i = 0;

	for (i = 0; i < _eGANTRY_POS_MAX; i++)
	{
		m_dCmd_Pos[i] = 0.000;
		m_bOn_Motion[i] = false;
	}

	//Gantry X
	Str.Format(_T("%.5f"), CManualData::m_ManualDataGantry.Info.m_dGantry_X_Wait_Pos);
	m_stcPos[_eGANTRY_X_WAIT_POS].SetWindowText(Str);

	//Gantry Y
	Str.Format(_T("%.5f"), CManualData::m_ManualDataGantry.Info.m_dGantry_Y_Wait_Pos);
	m_stcPos[_eGANTRY_Y_WAIT_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataGantry.Info.m_dGantry_Y_Stick_Load_In_Box_Pos);
	m_stcPos[_eGANTRY_Y_STICK_LOAD_IN_BOX_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataGantry.Info.m_dGantry_Y_Paper_Unload_Pos);
	m_stcPos[_eGANTRY_Y_PAPER_UNLOAD_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataGantry.Info.m_dGantry_Y_Stick_Unload_To_Stage_Pos);
	m_stcPos[_eGANTRY_Y_STICK_UNLOAD_TO_STAGE_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataGantry.Info.m_dGantry_Y_Stick_Load_In_Stage_Pos);
	m_stcPos[_eGANTRY_Y_STICK_LOAD_IN_STAGE_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataGantry.Info.m_dGantry_Y_Stick_Unload_To_Box_Pos);
	m_stcPos[_eGANTRY_Y_STICK_UNLOAD_TO_BOX_POS].SetWindowText(Str);
	//21.02.09 SJC
	Str.Format(_T("%.5f"), CManualData::m_ManualDataGantry.Info.m_dGantry_Y_Loading_Safe_Pos);
	m_stcPos[_eGANTRY_Y_LOADING_SAFE_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataGantry.Info.m_dGantry_Y_Unloading_Safe_Pos);
	m_stcPos[_eGANTRY_Y_UNLOADING_SAFE_POS].SetWindowText(Str);
	//
	//Gantry Z1
	Str.Format(_T("%.5f"), CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Wait_Pos);
	m_stcPos[_eGANTRY_Z1_WAIT_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_PreAlign_Pos);
	m_stcPos[_eGANTRY_Z1_PRE_ALIGN_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Inspection_Review_Pos);
	m_stcPos[_eGANTRY_Z1_INSPECTION_REVIEW_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataGantry.Info.m_dGantry_Z3_Mapping_Review_Pos);
	m_stcPos[_eGANTRY_Z1_MAPPING_REVIEW_POS].SetWindowText(Str);

	//Str.Format(_T("%.5f"), CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Inspection_AOI_Pos);
	//m_stcPos[_eGANTRY_Z1_INSPECTION_AOI_POS].SetWindowText(Str);

	////Gantry Z2
	//Str.Format(_T("%.5f"), CManualData::m_ManualDataGantry.Info.m_dGantry_Z2_Wait_Pos);
	//m_stcPos[_eGANTRY_Z2_WAIT_POS].SetWindowText(Str);
	//Str.Format(_T("%.5f"), CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_PreAlign_Pos);
	//m_stcPos[_eGANTRY_Z2_PRE_ALIGN_POS].SetWindowText(Str);
	//Str.Format(_T("%.5f"), CManualData::m_ManualDataGantry.Info.m_dGantry_Z2_Inspection_3D_Pos);
	//m_stcPos[_eGANTRY_Z2_INSPECTION_3D_POS].SetWindowText(Str);
	//Str.Format(_T("%.5f"), CManualData::m_ManualDataGantry.Info.m_dGantry_Z2_AOI_Review_Pos);
	//m_stcPos[_eGANTRY_Z2_REVIEW_AOI_POS].SetWindowText(Str);
	////21.02.09 SJC
	//

	////Gantry Z3
	//Str.Format(_T("%.5f"), CManualData::m_ManualDataGantry.Info.m_dGantry_Z3_Wait_Pos);
	//m_stcPos[_eGANTRY_Z3_WAIT_POS].SetWindowText(Str);
	//Str.Format(_T("%.5f"), CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Inspection_Review_Pos);
	//m_stcPos[_eGANTRY_Z3_INSPECTION_REVIEW_POS].SetWindowText(Str);
	//Str.Format(_T("%.5f"), CManualData::m_ManualDataGantry.Info.m_dGantry_Z3_Mapping_Review_Pos);
	//m_stcPos[_eGANTRY_Z3_MAPPING_REVIEW_POS].SetWindowText(Str);
	////3D Camera Sub Z
	//Str.Format(_T("%.5f"), CManualData::m_ManualDataGantry.Info.m_d3D_Camera_Sub_Z_Wait_Pos);
	//m_stcPos[_eGANTRY_3D_CAMERA_SUB_Z_WAIT_POS].SetWindowText(Str);
}
//------------------------------------------------------------------
void CManual_Sub_Gantry_Fixed_Pos::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (Is_Comp_Usable() == FALSE) return;
	CRect	RectSaveBtn;
	int		nOffset = 5;	
	int		nBtnSize_X = 100;
	int		nBtnSize_Y = 50;
	RectSaveBtn.left = cx - nOffset - nBtnSize_X;
	RectSaveBtn.top = cy - nOffset - nBtnSize_Y;
	RectSaveBtn.right = cx - nOffset;
	RectSaveBtn.bottom = cy - nOffset;
	GetDlgItem(IDC_BUTTON_MANUAL_SUB_GANTRY_FIXED_SAVE)->MoveWindow(RectSaveBtn);
}
//------------------------------------------------------------------
void CManual_Sub_Gantry_Fixed_Pos::OnShowWindow(BOOL bShow, UINT nStatus)
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
BOOL	CManual_Sub_Gantry_Fixed_Pos::Is_Comp_Usable()
{
	int i = 0;
	for (i = 0; i < _eGANTRY_POS_MAX; i++)
	{
		if (m_stcPos[i].GetSafeHwnd() == NULL) return FALSE;
		if (m_editPos[i].GetSafeHwnd() == NULL) return FALSE;
	}

	if (GetDlgItem(IDC_BUTTON_MANUAL_SUB_GANTRY_FIXED_SAVE)->GetSafeHwnd() == NULL) return FALSE;

	return TRUE;
}
//------------------------------------------------------------------
void CManual_Sub_Gantry_Fixed_Pos::OnTimer(UINT_PTR nIDEvent)
{
	
	CDialogEx::OnTimer(nIDEvent);
}
//------------------------------------------------------------------
void CManual_Sub_Gantry_Fixed_Pos::CheckChangeData()
{
	CString Str = _T("");

	//Gantry X
	m_stcPos[_eGANTRY_X_WAIT_POS].GetWindowText(Str);
	CManualData::m_ManualDataGantry.Info.m_dGantry_X_Wait_Pos = _ttof(Str);

	//Gantry Y
	m_stcPos[_eGANTRY_Y_WAIT_POS].GetWindowText(Str);
	CManualData::m_ManualDataGantry.Info.m_dGantry_Y_Wait_Pos = _ttof(Str);
	m_stcPos[_eGANTRY_Y_STICK_LOAD_IN_BOX_POS].GetWindowText(Str);
	CManualData::m_ManualDataGantry.Info.m_dGantry_Y_Stick_Load_In_Box_Pos = _ttof(Str);
	m_stcPos[_eGANTRY_Y_PAPER_UNLOAD_POS].GetWindowText(Str);
	CManualData::m_ManualDataGantry.Info.m_dGantry_Y_Paper_Unload_Pos = _ttof(Str);
	m_stcPos[_eGANTRY_Y_STICK_UNLOAD_TO_STAGE_POS].GetWindowText(Str);
	CManualData::m_ManualDataGantry.Info.m_dGantry_Y_Stick_Unload_To_Stage_Pos = _ttof(Str);
	m_stcPos[_eGANTRY_Y_STICK_LOAD_IN_STAGE_POS].GetWindowText(Str);
	CManualData::m_ManualDataGantry.Info.m_dGantry_Y_Stick_Load_In_Stage_Pos = _ttof(Str);
	m_stcPos[_eGANTRY_Y_STICK_UNLOAD_TO_BOX_POS].GetWindowText(Str);
	CManualData::m_ManualDataGantry.Info.m_dGantry_Y_Stick_Unload_To_Box_Pos = _ttof(Str);
		
	//Gantry Z1
	m_stcPos[_eGANTRY_Z1_WAIT_POS].GetWindowText(Str);
	CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Wait_Pos = _ttof(Str);
	m_stcPos[_eGANTRY_Z1_PRE_ALIGN_POS].GetWindowText(Str);
	CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_PreAlign_Pos = _ttof(Str);
	m_stcPos[_eGANTRY_Z1_INSPECTION_REVIEW_POS].GetWindowText(Str);
	CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Inspection_Review_Pos = _ttof(Str);
	m_stcPos[_eGANTRY_Z1_MAPPING_REVIEW_POS].GetWindowText(Str);
	CManualData::m_ManualDataGantry.Info.m_dGantry_Z3_Mapping_Review_Pos = _ttof(Str);

	//m_stcPos[_eGANTRY_Z1_INSPECTION_AOI_POS].GetWindowText(Str);
	//CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Inspection_AOI_Pos = _ttof(Str);

	////Gantry Z2
	//m_stcPos[_eGANTRY_Z2_WAIT_POS].GetWindowText(Str);
	//CManualData::m_ManualDataGantry.Info.m_dGantry_Z2_Wait_Pos = _ttof(Str);
	//m_stcPos[_eGANTRY_Z2_PRE_ALIGN_POS].GetWindowText(Str);
	//CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_PreAlign_Pos = _ttof(Str);
	//m_stcPos[_eGANTRY_Z2_INSPECTION_3D_POS].GetWindowText(Str);
	//CManualData::m_ManualDataGantry.Info.m_dGantry_Z2_Inspection_3D_Pos = _ttof(Str);
	//m_stcPos[_eGANTRY_Z2_REVIEW_AOI_POS].GetWindowText(Str);
	//CManualData::m_ManualDataGantry.Info.m_dGantry_Z2_AOI_Review_Pos = _ttof(Str);
	//
	////Gantry Z3
	//m_stcPos[_eGANTRY_Z3_WAIT_POS].GetWindowText(Str);
	//CManualData::m_ManualDataGantry.Info.m_dGantry_Z3_Wait_Pos = _ttof(Str);
	//m_stcPos[_eGANTRY_Z3_INSPECTION_REVIEW_POS].GetWindowText(Str);
	//CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Inspection_Review_Pos = _ttof(Str);
	//m_stcPos[_eGANTRY_Z3_MAPPING_REVIEW_POS].GetWindowText(Str);
	//CManualData::m_ManualDataGantry.Info.m_dGantry_Z3_Mapping_Review_Pos = _ttof(Str);

	////3D Camera Sub Z
	//m_stcPos[_eGANTRY_3D_CAMERA_SUB_Z_WAIT_POS].GetWindowText(Str);
	//CManualData::m_ManualDataGantry.Info.m_d3D_Camera_Sub_Z_Wait_Pos = _ttof(Str);
	//21.03.01 sjc
	m_stcPos[_eGANTRY_Y_LOADING_SAFE_POS].GetWindowText(Str);
	CManualData::m_ManualDataGantry.Info.m_dGantry_Y_Loading_Safe_Pos = _ttof(Str);
	m_stcPos[_eGANTRY_Y_UNLOADING_SAFE_POS].GetWindowText(Str);
	CManualData::m_ManualDataGantry.Info.m_dGantry_Y_Unloading_Safe_Pos = _ttof(Str);
}

enum_Axis CManual_Sub_Gantry_Fixed_Pos::GetAxisNo(enum_Gantry_Axis eGantryAxis, CString *strDiscription)
{
	CString Str = _T("");

	enum_Axis eAxis = AXIS_NONE;
	switch (eGantryAxis)
	{
	case _eMANUAL_GANTRY_AXIS_GANTRY_X:		eAxis = AXIS_GANTRY_X; Str = _T("Gantry X");  break;
	case _eMANUAL_GANTRY_AXIS_GANTRY_Y:		eAxis = AXIS_GANTRY_Y1; Str = _T("Gantry Y"); break;
	case _eMANUAL_GANTRY_AXIS_GANTRY_Z1:	eAxis = AXIS_CAMERA_Z1; Str = _T("Camera Z1"); break;
	//case _eMANUAL_GANTRY_AXIS_GANTRY_Z2:	eAxis = AXIS_CAMERA_Z2; Str = _T("Camera Z2"); break;
	//case _eMANUAL_GANTRY_AXIS_GANTRY_Z3:	eAxis = AXIS_CAMERA_Z3; Str = _T("Camera Z3"); break;
	//case _eMANUAL_GANTRY_AXIS_3D_CAMERA_SUB_Z: eAxis = AXIS_3D_CAMERA_SUB_Z; Str = _T("3D Camera Sub Z"); break;
	}

	*strDiscription = Str;

	return eAxis;
}

BOOL CManual_Sub_Gantry_Fixed_Pos::ManualAbsMove(enum_Gantry_Axis eGantryAxis, double dPos)
{
	CString strAxisName = _T(""), Str = _T("");
	double dVel = 0.0, dAccel = 0.0, dDecel = 0.0;
	enum_Axis eAxis = GetAxisNo(eGantryAxis, &strAxisName);
	double dCurPos = 0.0;

	SharedInfo::GetManualSpeed(eAxis, eAXIS_SPEED_MEDIUM, &dVel, &dAccel, &dDecel);

	Str.Format(_T("%s Abs Move To Pos: %.5f Start?"), strAxisName, dPos);
	int nResult = AfxMessageBox(Str, MB_OKCANCEL);
	if (nResult == IDOK)
	{
		dCurPos = SharedInfo::GetCmdPos(eAxis);

		Devs::m_JogMotion.AbsMove(eAxis, dPos, dVel, dAccel, dDecel);

		Str.Format(_T("[Manual-Gantry-Fixed] %s Abs Move %.5f -> %.5f"), strAxisName, dCurPos, dPos);
		Total_Msg(Str);
	}

	return TRUE;
}

double CManual_Sub_Gantry_Fixed_Pos::GetTargetPos(enum_Gantry_Pos eGantryPos)
{
	CString Str = _T("");
	double dPos = 0.0;
	m_editPos[eGantryPos].GetWindowText(Str);
	dPos = _ttof(Str);

	return dPos;
}

#pragma region //Get Button
//Gantry X
void CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonGetWaitPosGantryX()
{
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_GANTRY_X);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eGANTRY_X_WAIT_POS].SetWindowText(Str);
}
//Gantry Y
void CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonGetWaitPosGantryY()
{
	CString Str = _T("");
	double dCurPos = SharedInfo::GetActPos(AXIS_GANTRY_Y1);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eGANTRY_Y_WAIT_POS].SetWindowText(Str);
}
void CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonGetStickLoadInBoxPosGantryY()
{
	CString Str = _T("");
	double dCurPos = SharedInfo::GetActPos(AXIS_GANTRY_Y1);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eGANTRY_Y_STICK_LOAD_IN_BOX_POS].SetWindowText(Str);
}
void CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonGetUnloadPaperPosGantryY()
{
	CString Str = _T("");
	double dCurPos = SharedInfo::GetActPos(AXIS_GANTRY_Y1);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eGANTRY_Y_PAPER_UNLOAD_POS].SetWindowText(Str);
}
void CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonGetStickUnloadToStagePosGantryY()
{
	CString Str = _T("");
	double dCurPos = SharedInfo::GetActPos(AXIS_GANTRY_Y1);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eGANTRY_Y_STICK_UNLOAD_TO_STAGE_POS].SetWindowText(Str);
}
void CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonGetStickLoadInStagePosGantryY()
{
	CString Str = _T("");
	double dCurPos = SharedInfo::GetActPos(AXIS_GANTRY_Y1);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eGANTRY_Y_STICK_LOAD_IN_STAGE_POS].SetWindowText(Str);
}
void CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonGetStickUnloadToBoxPosGantryY()
{
	CString Str = _T("");
	double dCurPos = SharedInfo::GetActPos(AXIS_GANTRY_Y1);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eGANTRY_Y_STICK_UNLOAD_TO_BOX_POS].SetWindowText(Str);
}

//Gantry Z1
void CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonGetWaitPosCameraZ1()
{
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_CAMERA_Z1);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eGANTRY_Z1_WAIT_POS].SetWindowText(Str);
}
//void CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonGetInspectionAoiPosCameraZ1()
//{
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	CString Str = _T("");
//	double dCurPos = SharedInfo::GetCmdPos(AXIS_CAMERA_Z1);
//	Str.Format(_T("%.5f"), dCurPos);
//	m_editPos[_eGANTRY_Z1_INSPECTION_AOI_POS].SetWindowText(Str);
//}

//Gantry Z2
//void CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonGetWaitPosCameraZ2()
//{
//	CString Str = _T("");
//	double dCurPos = SharedInfo::GetCmdPos(AXIS_CAMERA_Z2);
//	Str.Format(_T("%.5f"), dCurPos);
//	m_editPos[_eGANTRY_Z2_WAIT_POS].SetWindowText(Str);
//}
void CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonGetPreAlignPosCameraZ1()
{
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_CAMERA_Z1);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eGANTRY_Z1_PRE_ALIGN_POS].SetWindowText(Str);
}
//
//void CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonGetInspection3dPosCameraZ2()
//{
//	CString Str = _T("");
//	double dCurPos = SharedInfo::GetCmdPos(AXIS_CAMERA_Z2);
//	Str.Format(_T("%.5f"), dCurPos);
//	m_editPos[_eGANTRY_Z2_INSPECTION_3D_POS].SetWindowText(Str);
//}
//
//void CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonGetAoiReviewPosCameraZ2()
//{
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	CString Str = _T("");
//	double dCurPos = SharedInfo::GetCmdPos(AXIS_CAMERA_Z2);
//	Str.Format(_T("%.5f"), dCurPos);
//	m_editPos[_eGANTRY_Z2_REVIEW_AOI_POS].SetWindowText(Str);
//}

//Gantry Z3
//21.02.09 sjc 3d->review
//void CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonGetWaitPosCameraZ3()
//{	
//	CString Str = _T("");
//	double dCurPos = SharedInfo::GetCmdPos(AXIS_CAMERA_Z3);
//	Str.Format(_T("%.5f"), dCurPos);
//	m_editPos[_eGANTRY_Z3_WAIT_POS].SetWindowText(Str);
//}

void CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonGetInspectionReviewPosCameraZ1()
{
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_CAMERA_Z1);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eGANTRY_Z1_INSPECTION_REVIEW_POS].SetWindowText(Str);
}
void CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonGetMappingReviewPosCameraZ1()
{
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_CAMERA_Z1);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[_eGANTRY_Z1_MAPPING_REVIEW_POS].SetWindowText(Str);
}

//3D Camera Sub Z
//void CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonGetWaitPos3dCameraSubZ()
//{
//	//CString Str = _T("");
//	//double dCurPos = SharedInfo::GetCmdPos(AXIS_3D_CAMERA_SUB_Z);
//	//Str.Format(_T("%.5f"), dCurPos);
//	//m_editPos[_eGANTRY_3D_CAMERA_SUB_Z_WAIT_POS].SetWindowText(Str);
//}
#pragma endregion

#pragma region //Set Button
//Gantry X
void CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonSetWaitPosGantryX()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eGANTRY_X_WAIT_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Gantry-Fixed] Gantry X Pos Set Click (Wait Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}
//Gantry Y
void CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonSetWaitPosGantryY()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eGANTRY_Y_WAIT_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Gantry-Fixed] Gantry Y Pos Set Click (Wait Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}
void CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonSetStickLoadInBoxPosGantryY()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eGANTRY_Y_STICK_LOAD_IN_BOX_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Gantry-Fixed] Gantry Y Pos Set Click Stick Load In Box Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}
void CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonSetUnloadPaperPosGantryY()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eGANTRY_Y_PAPER_UNLOAD_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Gantry-Fixed] Gantry Y Pos Set Click (Paper Unload Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}
void CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonSetStickUnloadToStagePosGantryY()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eGANTRY_Y_STICK_UNLOAD_TO_STAGE_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Gantry-Fixed] Gantry Y Pos Set Click (Stick Unload To Stage Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}
void CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonSetStickLoadInStagePosGantryY()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eGANTRY_Y_STICK_LOAD_IN_STAGE_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Gantry-Fixed] Gantry Y Pos Set Click (Stick Load In Stage Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}
void CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonSetStickUnloadToBoxPosGantryY()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eGANTRY_Y_STICK_UNLOAD_TO_BOX_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Gantry-Fixed] Gantry Y Pos Set Click (Stick Unload To Box Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}
//Gantry Z1
void CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonSetWaitPosCameraZ1()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eGANTRY_Z1_WAIT_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Gantry-Fixed] Gantry Z1 Pos Set Click (Wait Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}
//
//void CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonSetInspectionAoiPosCameraZ1()
//{
//	CString Str = _T(""), StrMsg = _T("");
//	int nIndex = _eGANTRY_Z1_INSPECTION_AOI_POS;
//	m_editPos[nIndex].GetWindowText(Str);
//	m_stcPos[nIndex].SetWindowText(Str);
//
//	double dPos = _ttof(Str);
//	StrMsg.Format(_T("[Manual-Gantry-Fixed] Gantry Z1 Pos Set Click (Inspect AOI Pos : %.5f)"), dPos);
//	Total_Msg(StrMsg);
//}
//
//
////Gantry Z2
//void CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonSetWaitPosCameraZ2()
//{
//	CString Str = _T(""), StrMsg = _T("");
//	int nIndex = _eGANTRY_Z2_WAIT_POS;
//	m_editPos[nIndex].GetWindowText(Str);
//	m_stcPos[nIndex].SetWindowText(Str);
//
//	double dPos = _ttof(Str);
//	StrMsg.Format(_T("[Manual-Gantry-Fixed] Gantry Z2 Pos Set Click (Wait Pos : %.5f)"), dPos);
//	Total_Msg(StrMsg);
//}

void CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonSetPreAlignPosCameraZ1()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eGANTRY_Z1_PRE_ALIGN_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Gantry-Fixed] Gantry Z2 Pos Set Click (PreAlign Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}
//void CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonSetInspection3dPosCameraZ2()
//{
//	CString Str = _T(""), StrMsg = _T("");
//	int nIndex = _eGANTRY_Z2_INSPECTION_3D_POS;
//	m_editPos[nIndex].GetWindowText(Str);
//	m_stcPos[nIndex].SetWindowText(Str);
//
//	double dPos = _ttof(Str);
//	StrMsg.Format(_T("[Manual-Gantry-Fixed] Gantry Z2 Pos Set Click (Inspect 3D Pos : %.5f)"), dPos);
//	Total_Msg(StrMsg);
//}
//
//void CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonSetAoiReviewPosCameraZ2()
//{
//	CString Str = _T(""), StrMsg = _T("");
//	int nIndex = _eGANTRY_Z2_REVIEW_AOI_POS;
//	m_editPos[nIndex].GetWindowText(Str);
//	m_stcPos[nIndex].SetWindowText(Str);
//
//	double dPos = _ttof(Str);
//	StrMsg.Format(_T("[Manual-Gantry-Fixed] Gantry Z2 Pos Set Click (AOI Review Pos : %.5f)"), dPos);
//	Total_Msg(StrMsg);
//}
//
////Gantry Z3
//void CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonSetWaitPosCameraZ3()
//{
//	CString Str = _T(""), StrMsg = _T("");
//	int nIndex = _eGANTRY_Z3_WAIT_POS;
//	m_editPos[nIndex].GetWindowText(Str);
//	m_stcPos[nIndex].SetWindowText(Str);
//
//	double dPos = _ttof(Str);
//	StrMsg.Format(_T("[Manual-Gantry-Fixed] Gantry Z3 Pos Set Click (Wait Pos : %.5f)"), dPos);
//	Total_Msg(StrMsg);
//}

void CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonSetInspectionReviewPosCameraZ1()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eGANTRY_Z1_INSPECTION_REVIEW_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Gantry-Fixed] Gantry Z1 Pos Set Click (Inspection Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}
void CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonSetMappingReviewPosCameraZ1()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = _eGANTRY_Z1_MAPPING_REVIEW_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Gantry-Fixed] Gantry Z1 Pos Set Click (Mapping Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}


//3D Camera Sub Z
//void CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonSetWaitPos3dCameraSubZ()
//{
//	//CString Str = _T(""), StrMsg = _T("");
//	//int nIndex = _eGANTRY_3D_CAMERA_SUB_Z_WAIT_POS;
//	//m_editPos[nIndex].GetWindowText(Str);
//	//m_stcPos[nIndex].SetWindowText(Str);
//
//	//double dPos = _ttof(Str);
//	//StrMsg.Format(_T("[Manual-Gantry-Fixed] 3D Camera Sub Z Pos Set Click (Wait Pos : %.5f)"), dPos);
//	//Total_Msg(StrMsg);
//}
#pragma endregion

#pragma region //Move Button
//Gantry X
void CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonMoveWaitPosGantryX()
{
	CString Str;
	if (SharedInfo::GetCmdPos(AXIS_CAMERA_Z1) < CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Wait_Pos - 0.002)
	{
		Str.Format(_T("Camera Z1 Pos Check !!! (Cur Pos < Wait Pos)"));
		Total_Msg(Str);
		AfxMessageBox(Str);
		return;
	}
	//if (SharedInfo::GetCmdPos(AXIS_CAMERA_Z2) < CManualData::m_ManualDataGantry.Info.m_dGantry_Z2_Wait_Pos - 0.002)
	//{		
	//	Str.Format(_T("Camera Z2 Pos Check !!! (Cur Pos < Wait Pos)"));
	//	Total_Msg(Str);
	//	AfxMessageBox(Str);
	//	return;
	//}
	//if (SharedInfo::GetCmdPos(AXIS_CAMERA_Z3) < CManualData::m_ManualDataGantry.Info.m_dGantry_Z3_Wait_Pos - 0.002)
	//{
	//	Str.Format(_T("Camera Z3 Pos Check !!! (Cur Pos < Wait Pos)"));
	//	Total_Msg(Str);
	//	AfxMessageBox(Str);
	//	return;
	//}

	double dPos = GetTargetPos(_eGANTRY_X_WAIT_POS);

	//CString Str;
	Str.Format(_T("Gantry X Move ? (Wait Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	ManualAbsMove(_eMANUAL_GANTRY_AXIS_GANTRY_X, dPos);
}
//Gantry Y
void CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonMoveWaitPosGantryY()
{
	CString Str = _T("");
	double dPos = 0.0;
	if (SharedInfo::GetCmdPos(AXIS_CAMERA_Z1) < CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Wait_Pos - 0.002)
	{
		Str.Format(_T("Camera Z1 Pos Check !!! (Cur Pos < Wait Pos)"));
		Total_Msg(Str);
		AfxMessageBox(Str);
		return;
	}

	dPos = GetTargetPos(_eGANTRY_Y_WAIT_POS);

	//CString Str;
	Str.Format(_T("Gantry Y Move ? (Wait Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	ManualAbsMove(_eMANUAL_GANTRY_AXIS_GANTRY_Y, dPos);
}
void CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonMoveStickLoadInBoxPosGantryY()
{
	double dPos = GetTargetPos(_eGANTRY_Y_STICK_LOAD_IN_BOX_POS);
	ManualAbsMove(_eMANUAL_GANTRY_AXIS_GANTRY_Y, dPos);
}
void CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonMoveUnloadPaperPosGantryY()
{
	double dPos = GetTargetPos(_eGANTRY_Y_PAPER_UNLOAD_POS);
	ManualAbsMove(_eMANUAL_GANTRY_AXIS_GANTRY_Y, dPos);
}
void CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonMoveStickUnloadToStagePosGantryY()
{
	double dPos = GetTargetPos(_eGANTRY_Y_STICK_UNLOAD_TO_STAGE_POS);
	ManualAbsMove(_eMANUAL_GANTRY_AXIS_GANTRY_Y, dPos);
}
void CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonMoveStickLoadInStagePosGantryY()
{
	double dPos = GetTargetPos(_eGANTRY_Y_STICK_LOAD_IN_STAGE_POS);
	ManualAbsMove(_eMANUAL_GANTRY_AXIS_GANTRY_Y, dPos);
}
void CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonMoveStickUnloadToBoxPosGantryY()
{
	double dPos = GetTargetPos(_eGANTRY_Y_STICK_UNLOAD_TO_BOX_POS);
	ManualAbsMove(_eMANUAL_GANTRY_AXIS_GANTRY_Y, dPos);
}
//Gantry Z1
void CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonMoveWaitPosCameraZ1()
{
	double dPos = GetTargetPos(_eGANTRY_Z1_WAIT_POS);
	
	CString Str;
	Str.Format(_T("Camera Z1 Move ? (Wait Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	ManualAbsMove(_eMANUAL_GANTRY_AXIS_GANTRY_Z1, dPos);
}

void CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonMoveInspectionReviewPosCameraZ1()
{
	double dPos = GetTargetPos(_eGANTRY_Z1_INSPECTION_REVIEW_POS);

	CString Str;
	Str.Format(_T("Camera Z1 Move ? (Inspect Review Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	ManualAbsMove(_eMANUAL_GANTRY_AXIS_GANTRY_Z1, dPos);
}

void CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonMoveMappingReviewPosCameraZ1()
{
	double dPos = GetTargetPos(_eGANTRY_Z1_MAPPING_REVIEW_POS);

	CString Str;
	Str.Format(_T("Camera Z1 Move ? (Mapping Review Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	ManualAbsMove(_eMANUAL_GANTRY_AXIS_GANTRY_Z1, dPos);
}

#pragma endregion

void CManual_Sub_Gantry_Fixed_Pos::OnBnClickedButtonManualSubGantryFixedSave()
{
	CheckChangeData();
	CManualData::m_ManualDataGantry.Save();

	AfxMessageBox(_T("Save Ok"));
}