// Manual_Sub_LoadingStage_Fixed_Pos.cpp: 구현 파일
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "Manual_Sub_Box_Fixed_Pos.h"
#include "afxdialogex.h"


// CManual_Sub_Box_Fixed_Pos 대화 상자

IMPLEMENT_DYNAMIC(CManual_Sub_Box_Fixed_Pos, CDialogEx)

CManual_Sub_Box_Fixed_Pos::CManual_Sub_Box_Fixed_Pos(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_MANUAL_SUB_BOX_FIXED_POS, pParent)
{
	Create(IDD_DLG_MANUAL_SUB_BOX_FIXED_POS, pParent);
}

CManual_Sub_Box_Fixed_Pos::~CManual_Sub_Box_Fixed_Pos()
{
}

void CManual_Sub_Box_Fixed_Pos::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CManual_Sub_Box_Fixed_Pos, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_BOX_GET_WAIT_POS_LOADING_STAGE_XYT, &CManual_Sub_Box_Fixed_Pos::OnBnClickedButtonManualSubBoxGetWaitPosLoadingStageXYT)			
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_BOX_SET_WAIT_POS_LOADING_STAGE_XYT, &CManual_Sub_Box_Fixed_Pos::OnBnClickedButtonManualSubBoxSetWaitPosLoadingStageXYT)				
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_BOX_MOVE_WAIT_POS_LOADING_STAGE_XYT, &CManual_Sub_Box_Fixed_Pos::OnBnClickedButtonManualSubBoxMoveWaitPosLoadingStageXYT)	
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_BOX_FIXED_SAVE, &CManual_Sub_Box_Fixed_Pos::OnBnClickedButtonManualSubBoxFixedSave)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_BOX_GET_STICK_LOAD_POS_LOADING_STAGE_XYT, &CManual_Sub_Box_Fixed_Pos::OnBnClickedButtonManualSubBoxGetStickLoadPosLoadingStageXYT)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_BOX_GET_STICK_UNLOAD_POS_LOADING_STAGE_XYT, &CManual_Sub_Box_Fixed_Pos::OnBnClickedButtonManualSubBoxGetStickUnloadPosLoadingStageXYT)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_BOX_SET_STICK_LOAD_POS_LOADING_STAGE_XYT, &CManual_Sub_Box_Fixed_Pos::OnBnClickedButtonManualSubBoxSetStickLoadPosLoadingStageXYT)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_BOX_SET_STICK_UNLOAD_POS_LOADING_STAGE_XYT, &CManual_Sub_Box_Fixed_Pos::OnBnClickedButtonManualSubBoxSetStickUnloadPosLoadingStageXYT)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_BOX_MOVE_STICK_LOAD_POS_LOADING_STAGE_XYT, &CManual_Sub_Box_Fixed_Pos::OnBnClickedButtonManualSubBoxMoveStickLoadPosLoadingStageXYT)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_BOX_MOVE_STICK_UNLOAD_POS_LOADING_STAGE_XYT, &CManual_Sub_Box_Fixed_Pos::OnBnClickedButtonManualSubBoxMoveStickUnloadPosLoadingStageXYT)
END_MESSAGE_MAP()


// CManual_Sub_Box_Fixed_Pos 메시지 처리기

BOOL CManual_Sub_Box_Fixed_Pos::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	InitCtrl();

	return TRUE;
}
//------------------------------------------------------------------
void CManual_Sub_Box_Fixed_Pos::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow == TRUE)
	{
		InitPara();

		//SetTimer(1, 100, NULL);
	}
	else if (bShow == FALSE)
	{
		KillTimer(1);
	}
}
//------------------------------------------------------------------
void CManual_Sub_Box_Fixed_Pos::OnSize(UINT nType, int cx, int cy)
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
	GetDlgItem(IDC_BUTTON_MANUAL_SUB_BOX_FIXED_SAVE)->MoveWindow(RectSaveBtn);
}
//------------------------------------------------------------------
void CManual_Sub_Box_Fixed_Pos::OnTimer(UINT_PTR nIDEvent)
{
	//if (Devs::m_JogMotion.IsMotionDone(AXIS_LOADING_STAGE_X1) == TRUE)

	CDialogEx::OnTimer(nIDEvent);
}
//------------------------------------------------------------------
void	CManual_Sub_Box_Fixed_Pos::InitCtrl()
{
	//Static Pos
	m_stcPos[_eBOX_LOADING_STAGE_X_WAIT_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_BOX_CURRENT_WAIT_POS_LOADING_STAGE_X, this);
	m_stcPos[_eBOX_LOADING_STAGE_X_STICK_LOAD_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_BOX_CURRENT_STICK_LOAD_POS_LOADING_STAGE_X, this);
	m_stcPos[_eBOX_LOADING_STAGE_X_STICK_UNLOAD_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_BOX_CURRENT_STICK_UNLOAD_POS_LOADING_STAGE_X, this);

	m_stcPos[_eBOX_LOADING_STAGE_Y_WAIT_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_BOX_CURRENT_WAIT_POS_LOADING_STAGE_Y, this);
	m_stcPos[_eBOX_LOADING_STAGE_Y_STICK_LOAD_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_BOX_CURRENT_STICK_LOAD_POS_LOADING_STAGE_Y, this);
	m_stcPos[_eBOX_LOADING_STAGE_Y_STICK_UNLOAD_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_BOX_CURRENT_STICK_UNLOAD_POS_LOADING_STAGE_Y, this);

	m_stcPos[_eBOX_LOADING_STAGE_T_WAIT_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_BOX_CURRENT_WAIT_POS_LOADING_STAGE_T, this);
	m_stcPos[_eBOX_LOADING_STAGE_T_STICK_LOAD_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_BOX_CURRENT_STICK_LOAD_POS_LOADING_STAGE_T, this);
	m_stcPos[_eBOX_LOADING_STAGE_T_STICK_UNLOAD_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_BOX_CURRENT_STICK_UNLOAD_POS_LOADING_STAGE_T, this);
		
	//EditPos
	m_editPos[_eBOX_LOADING_STAGE_X_WAIT_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_BOX_WAIT_POS_LOADING_STAGE_X, this);
	m_editPos[_eBOX_LOADING_STAGE_X_STICK_LOAD_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_BOX_STICK_LOAD_POS_LOADING_STAGE_X, this);
	m_editPos[_eBOX_LOADING_STAGE_X_STICK_UNLOAD_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_BOX_STICK_UNLOAD_POS_LOADING_STAGE_X, this);
	
	m_editPos[_eBOX_LOADING_STAGE_Y_WAIT_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_BOX_WAIT_POS_LOADING_STAGE_Y, this);
	m_editPos[_eBOX_LOADING_STAGE_Y_STICK_LOAD_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_BOX_STICK_LOAD_POS_LOADING_STAGE_Y, this);
	m_editPos[_eBOX_LOADING_STAGE_Y_STICK_UNLOAD_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_BOX_STICK_UNLOAD_POS_LOADING_STAGE_Y, this);
	
	m_editPos[_eBOX_LOADING_STAGE_T_WAIT_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_BOX_WAIT_POS_LOADING_STAGE_T, this);
	m_editPos[_eBOX_LOADING_STAGE_T_STICK_LOAD_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_BOX_STICK_LOAD_POS_LOADING_STAGE_T, this);
	m_editPos[_eBOX_LOADING_STAGE_T_STICK_UNLOAD_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_BOX_STICK_UNLOAD_POS_LOADING_STAGE_T, this);
}
//------------------------------------------------------------------
BOOL	CManual_Sub_Box_Fixed_Pos::Is_Comp_Usable()
{
	int i = 0;
	for (i = 0; i < _eBOX_POS_MAX; i++)
	{
		if (m_stcPos[i].GetSafeHwnd() == NULL) return FALSE;
		if (m_editPos[i].GetSafeHwnd() == NULL) return FALSE;
	}

	if (GetDlgItem(IDC_BUTTON_MANUAL_SUB_BOX_FIXED_SAVE)->GetSafeHwnd() == NULL) return FALSE;
	
	return TRUE;
}
//------------------------------------------------------------------
void CManual_Sub_Box_Fixed_Pos::InitPara()
{
	CString Str = _T("");
	int i = 0;

	for (i = 0; i < _eBOX_POS_MAX; i++)
	{
		m_dCmd_Pos[i] = 0.000;
		m_bOn_Motion[i] = false;
	}

	//LoadingStage X
	Str.Format(_T("%.5f"), CManualData::m_ManualDataBox.Info.m_dLoadingStageX_Wait_Pos);
	m_stcPos[_eBOX_LOADING_STAGE_X_WAIT_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataBox.Info.m_dLoadingStageX_StickLoad_Pos);
	m_stcPos[_eBOX_LOADING_STAGE_X_STICK_LOAD_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataBox.Info.m_dLoadingStageX_StickUnload_Pos);
	m_stcPos[_eBOX_LOADING_STAGE_X_STICK_UNLOAD_POS].SetWindowText(Str);

	//LoadingStage Y
	Str.Format(_T("%.5f"), CManualData::m_ManualDataBox.Info.m_dLoadingStageY_Wait_Pos);
	m_stcPos[_eBOX_LOADING_STAGE_Y_WAIT_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataBox.Info.m_dLoadingStageY_StickLoad_Pos);
	m_stcPos[_eBOX_LOADING_STAGE_Y_STICK_LOAD_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataBox.Info.m_dLoadingStageY_StickUnload_Pos);
	m_stcPos[_eBOX_LOADING_STAGE_Y_STICK_UNLOAD_POS].SetWindowText(Str);

	//LoadingStage T
	Str.Format(_T("%.5f"), CManualData::m_ManualDataBox.Info.m_dLoadingStageT_Wait_Pos);
	m_stcPos[_eBOX_LOADING_STAGE_T_WAIT_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataBox.Info.m_dLoadingStageT_StickLoad_Pos);
	m_stcPos[_eBOX_LOADING_STAGE_T_STICK_LOAD_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataBox.Info.m_dLoadingStageT_StickUnload_Pos);
	m_stcPos[_eBOX_LOADING_STAGE_T_STICK_UNLOAD_POS].SetWindowText(Str);

	/////
	m_editPos[_eBOX_LOADING_STAGE_X_WAIT_POS].SetWindowText(_T("0.0"));
	m_editPos[_eBOX_LOADING_STAGE_X_STICK_LOAD_POS].SetWindowText(_T("0.0"));
	m_editPos[_eBOX_LOADING_STAGE_X_STICK_UNLOAD_POS].SetWindowText(_T("0.0"));

	m_editPos[_eBOX_LOADING_STAGE_Y_WAIT_POS].SetWindowText(_T("0.0"));
	m_editPos[_eBOX_LOADING_STAGE_Y_STICK_LOAD_POS].SetWindowText(_T("0.0"));
	m_editPos[_eBOX_LOADING_STAGE_Y_STICK_UNLOAD_POS].SetWindowText(_T("0.0"));

	m_editPos[_eBOX_LOADING_STAGE_T_WAIT_POS].SetWindowText(_T("0.0"));
	m_editPos[_eBOX_LOADING_STAGE_T_STICK_LOAD_POS].SetWindowText(_T("0.0"));
	m_editPos[_eBOX_LOADING_STAGE_T_STICK_UNLOAD_POS].SetWindowText(_T("0.0"));
}
//------------------------------------------------------------------
void CManual_Sub_Box_Fixed_Pos::CheckChangeData()
{
	CString Str = _T("");

	//LoadingStage X
	m_stcPos[_eBOX_LOADING_STAGE_X_WAIT_POS].GetWindowText(Str);
	CManualData::m_ManualDataBox.Info.m_dLoadingStageX_Wait_Pos = _ttof(Str);
	m_stcPos[_eBOX_LOADING_STAGE_X_STICK_LOAD_POS].GetWindowText(Str);
	CManualData::m_ManualDataBox.Info.m_dLoadingStageX_StickLoad_Pos = _ttof(Str);
	m_stcPos[_eBOX_LOADING_STAGE_X_STICK_UNLOAD_POS].GetWindowText(Str);
	CManualData::m_ManualDataBox.Info.m_dLoadingStageX_StickUnload_Pos = _ttof(Str);

	//LoadingStage Y
	m_stcPos[_eBOX_LOADING_STAGE_Y_WAIT_POS].GetWindowText(Str);
	CManualData::m_ManualDataBox.Info.m_dLoadingStageY_Wait_Pos = _ttof(Str);
	m_stcPos[_eBOX_LOADING_STAGE_Y_STICK_LOAD_POS].GetWindowText(Str);
	CManualData::m_ManualDataBox.Info.m_dLoadingStageY_StickLoad_Pos = _ttof(Str);
	m_stcPos[_eBOX_LOADING_STAGE_Y_STICK_UNLOAD_POS].GetWindowText(Str);
	CManualData::m_ManualDataBox.Info.m_dLoadingStageY_StickUnload_Pos = _ttof(Str);

	//LoadingStage T
	m_stcPos[_eBOX_LOADING_STAGE_T_WAIT_POS].GetWindowText(Str);
	CManualData::m_ManualDataBox.Info.m_dLoadingStageT_Wait_Pos = _ttof(Str);
	m_stcPos[_eBOX_LOADING_STAGE_T_STICK_LOAD_POS].GetWindowText(Str);
	CManualData::m_ManualDataBox.Info.m_dLoadingStageT_StickLoad_Pos = _ttof(Str);
	m_stcPos[_eBOX_LOADING_STAGE_T_STICK_UNLOAD_POS].GetWindowText(Str);
	CManualData::m_ManualDataBox.Info.m_dLoadingStageT_StickUnload_Pos = _ttof(Str);
}

enum_Axis CManual_Sub_Box_Fixed_Pos::GetAxisNo(enum_Box_Axis eBoxAxis, CString *strDiscription)
{
	CString Str = _T("");

	enum_Axis eAxis = AXIS_NONE;
	switch (eBoxAxis)
	{
	case _eMANUAL_BOX_AXIS_LOADING_STAGE_Y1:		eAxis = AXIS_LOADING_STAGE_Y1; Str = _T("LoadingStage Y1");  break;
	case _eMANUAL_BOX_AXIS_LOADING_STAGE_Y2:		eAxis = AXIS_LOADING_STAGE_Y2; Str = _T("LoadingStage Y2");  break;
	case _eMANUAL_BOX_AXIS_LOADING_STAGE_X:			eAxis = AXIS_LOADING_STAGE_X; Str = _T("LoadingStage X");  break;
	//case _eMANUAL_BOX_AXIS_BOX_ALIGN_CAMERA_YL:		eAxis = AXIS_BOX_ALIGN_CAMERA_YL; Str = _T("BoxAlignCamera YL");  break;
	//case _eMANUAL_BOX_AXIS_BOX_ALIGN_CAMERA_YR:		eAxis = AXIS_BOX_ALIGN_CAMERA_YR; Str = _T("BoxAlignCamera YR");  break;
	}

	*strDiscription = Str;

	return eAxis;
}

BOOL CManual_Sub_Box_Fixed_Pos::ManualAbsMove(enum_Box_Axis eBoxAxis, double dPos)
{
	CString strAxisName = _T(""), Str = _T("");
	double dVel = 0.0, dAccel = 0.0, dDecel = 0.0;
	enum_Axis eAxis = GetAxisNo(eBoxAxis, &strAxisName);
	double dCurPos = 0.0;
	BOOL bRtn = FALSE;

	SharedInfo::GetManualSpeed(eAxis, eAXIS_SPEED_MEDIUM, &dVel, &dAccel, &dDecel);

	Str.Format(_T("%s Abs Move To Pos: %.5f Start?"), strAxisName, dPos);
	int nResult = AfxMessageBox(Str, MB_OKCANCEL);
	if (nResult == IDOK)
	{
		dCurPos = SharedInfo::GetCmdPos(eAxis);

		bRtn = Devs::m_JogMotion.AbsMove(eAxis, dPos, dVel, dAccel, dDecel);
		if (bRtn == TRUE)
		{
			Str.Format(_T("[Manual-Box-Fixed] %s Abs Move %.5f -> %.5f"), strAxisName, dCurPos, dPos);
			Total_Msg(Str);
		}
	}

	return TRUE;
}

double CManual_Sub_Box_Fixed_Pos::GetTargetPos(enum_Box_Pos eBoxPos)
{
	CString Str = _T("");
	double dPos = 0.0;
	m_editPos[eBoxPos].GetWindowText(Str);
	dPos = _ttof(Str);

	return dPos;
}

#pragma region //Get Button
void CManual_Sub_Box_Fixed_Pos::OnBnClickedButtonManualSubBoxGetWaitPosLoadingStageXYT()
{
	CString Str = _T("");

	Str.Format(_T("%.5f"), SharedInfo::UvwCmdPos[MASK_UVW][0]);
	m_editPos[_eBOX_LOADING_STAGE_X_WAIT_POS].SetWindowText(Str);

	Str.Format(_T("%.5f"), SharedInfo::UvwCmdPos[MASK_UVW][1]);
	m_editPos[_eBOX_LOADING_STAGE_Y_WAIT_POS].SetWindowText(Str);

	Str.Format(_T("%.5f"), SharedInfo::UvwCmdPos[MASK_UVW][2]);
	m_editPos[_eBOX_LOADING_STAGE_T_WAIT_POS].SetWindowText(Str);
}
void CManual_Sub_Box_Fixed_Pos::OnBnClickedButtonManualSubBoxGetStickLoadPosLoadingStageXYT()
{
	CString Str = _T("");

	Str.Format(_T("%.5f"), SharedInfo::UvwCmdPos[MASK_UVW][0]);
	m_editPos[_eBOX_LOADING_STAGE_X_STICK_LOAD_POS].SetWindowText(Str);

	Str.Format(_T("%.5f"), SharedInfo::UvwCmdPos[MASK_UVW][1]);
	m_editPos[_eBOX_LOADING_STAGE_Y_STICK_LOAD_POS].SetWindowText(Str);

	Str.Format(_T("%.5f"), SharedInfo::UvwCmdPos[MASK_UVW][2]);
	m_editPos[_eBOX_LOADING_STAGE_T_STICK_LOAD_POS].SetWindowText(Str);
}
void CManual_Sub_Box_Fixed_Pos::OnBnClickedButtonManualSubBoxGetStickUnloadPosLoadingStageXYT()
{
	CString Str = _T("");

	Str.Format(_T("%.5f"), SharedInfo::UvwCmdPos[MASK_UVW][0]);
	m_editPos[_eBOX_LOADING_STAGE_X_STICK_UNLOAD_POS].SetWindowText(Str);

	Str.Format(_T("%.5f"), SharedInfo::UvwCmdPos[MASK_UVW][1]);
	m_editPos[_eBOX_LOADING_STAGE_Y_STICK_UNLOAD_POS].SetWindowText(Str);

	Str.Format(_T("%.5f"), SharedInfo::UvwCmdPos[MASK_UVW][2]);
	m_editPos[_eBOX_LOADING_STAGE_T_STICK_UNLOAD_POS].SetWindowText(Str);
}
#pragma endregion

#pragma region //Set Button
void CManual_Sub_Box_Fixed_Pos::OnBnClickedButtonManualSubBoxSetWaitPosLoadingStageXYT()
{
	CString Str = _T(""), StrMsg = _T("");
	double dX = 0.0, dY = 0.0, dT = 0.0;

	m_editPos[_eBOX_LOADING_STAGE_X_WAIT_POS].GetWindowText(Str);
	m_stcPos[_eBOX_LOADING_STAGE_X_WAIT_POS].SetWindowText(Str);
	dX = _ttof(Str);

	m_editPos[_eBOX_LOADING_STAGE_Y_WAIT_POS].GetWindowText(Str);
	m_stcPos[_eBOX_LOADING_STAGE_Y_WAIT_POS].SetWindowText(Str);
	dY = _ttof(Str);

	m_editPos[_eBOX_LOADING_STAGE_T_WAIT_POS].GetWindowText(Str);
	m_stcPos[_eBOX_LOADING_STAGE_T_WAIT_POS].SetWindowText(Str);
	dT = _ttof(Str);

	StrMsg.Format(_T("[Manual-Box-Fixed] LoadingStage XYT Wait Pos Set Click (X:%.5f, Y:%.5F, T:%.5F)"), dX, dY, dT);
	Total_Msg(StrMsg);
}
void CManual_Sub_Box_Fixed_Pos::OnBnClickedButtonManualSubBoxSetStickLoadPosLoadingStageXYT()
{
	CString Str = _T(""), StrMsg = _T("");
	double dX = 0.0, dY = 0.0, dT = 0.0;

	m_editPos[_eBOX_LOADING_STAGE_X_STICK_LOAD_POS].GetWindowText(Str);
	m_stcPos[_eBOX_LOADING_STAGE_X_STICK_LOAD_POS].SetWindowText(Str);
	dX = _ttof(Str);

	m_editPos[_eBOX_LOADING_STAGE_Y_STICK_LOAD_POS].GetWindowText(Str);
	m_stcPos[_eBOX_LOADING_STAGE_Y_STICK_LOAD_POS].SetWindowText(Str);
	dY = _ttof(Str);

	m_editPos[_eBOX_LOADING_STAGE_T_STICK_LOAD_POS].GetWindowText(Str);
	m_stcPos[_eBOX_LOADING_STAGE_T_STICK_LOAD_POS].SetWindowText(Str);
	dT = _ttof(Str);

	StrMsg.Format(_T("[Manual-Box-Fixed] LoadingStage Y Stick Load Pos Set Click (X:%.5f, Y:%.5f, T:%.5f)"), dX, dY, dT);
	Total_Msg(StrMsg);
}
void CManual_Sub_Box_Fixed_Pos::OnBnClickedButtonManualSubBoxSetStickUnloadPosLoadingStageXYT()
{
	CString Str = _T(""), StrMsg = _T("");
	double dX = 0.0, dY = 0.0, dT = 0.0;

	m_editPos[_eBOX_LOADING_STAGE_X_STICK_UNLOAD_POS].GetWindowText(Str);
	m_stcPos[_eBOX_LOADING_STAGE_X_STICK_UNLOAD_POS].SetWindowText(Str);
	dX = _ttof(Str);

	m_editPos[_eBOX_LOADING_STAGE_Y_STICK_UNLOAD_POS].GetWindowText(Str);
	m_stcPos[_eBOX_LOADING_STAGE_Y_STICK_UNLOAD_POS].SetWindowText(Str);
	dY = _ttof(Str);

	m_editPos[_eBOX_LOADING_STAGE_T_STICK_UNLOAD_POS].GetWindowText(Str);
	m_stcPos[_eBOX_LOADING_STAGE_T_STICK_UNLOAD_POS].SetWindowText(Str);
	dT = _ttof(Str);

	StrMsg.Format(_T("[Manual-Box-Fixed] LoadingStage XYT Stick Unload Pos Set Click (X:%.5f, Y:%.5f, T:%.5f)"), dX, dY, dT);
	Total_Msg(StrMsg);
}
#pragma endregion

#pragma region //Move Button
//Loading Stage X
void CManual_Sub_Box_Fixed_Pos::OnBnClickedButtonManualSubBoxMoveWaitPosLoadingStageXYT()
{
	//double dPos = GetTargetPos(_eBOX_LOADING_STAGE_X_WAIT_POS);
	//ManualAbsMove(_eMANUAL_BOX_AXIS_LOADING_STAGE_Y1, dPos);

	CString Str = _T("");
	double dVel = 1.0;
	double dAccel = dVel * 2.0;
	double dDecel = dVel * 2.0;
	double dUvwPos[3] = { 0.0, 0.0, 0.0 };
	double dUvwVel[3] = { 1.0, 1.0, 1.0 };
	double dUvwAccel[3] = { 2.0, 2.0, 2.0 };
	double dUvwDecel[3] = { 2.0, 2.0, 2.0 };
	double dUVWScale = 2;
		
	dUvwPos[0] = GetTargetPos(_eBOX_LOADING_STAGE_X_WAIT_POS);
	dUvwPos[1] = GetTargetPos(_eBOX_LOADING_STAGE_Y_WAIT_POS);
	dUvwPos[2] = GetTargetPos(_eBOX_LOADING_STAGE_T_WAIT_POS);

	Str.Format(_T("Loading Stage Uvw Move To Wait Pos ? (X:%.5f, Y:%.5f, T:%.5f)"), dUvwPos[0], dUvwPos[1], dUvwPos[2]);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	dUvwVel[0] = dVel;
	dUvwVel[1] = dVel;
	dUvwVel[2] = dVel;
	dUvwAccel[0] = dUvwVel[0] * dUVWScale;
	dUvwAccel[1] = dUvwVel[1] * dUVWScale;
	dUvwAccel[2] = dUvwVel[2] * dUVWScale;
	dUvwDecel[0] = dUvwVel[0] * dUVWScale;
	dUvwDecel[1] = dUvwVel[1] * dUVWScale;
	dUvwDecel[2] = dUvwVel[2] * dUVWScale;

	Devs::m_BoxMotion.UVWStagePosMove(dUvwPos, dUvwVel, dUvwAccel, dUvwDecel);
}
void CManual_Sub_Box_Fixed_Pos::OnBnClickedButtonManualSubBoxMoveStickLoadPosLoadingStageXYT()
{
	//double dPos = GetTargetPos(_eBOX_LOADING_STAGE_X_STICK_LOAD_POS);
	//ManualAbsMove(_eMANUAL_BOX_AXIS_LOADING_STAGE_Y1, dPos);

	CString Str = _T("");
	double dVel = 1.0;
	double dAccel = dVel * 2.0;
	double dDecel = dVel * 2.0;
	double dUvwPos[3] = { 0.0, 0.0, 0.0 };
	double dUvwVel[3] = { 1.0, 1.0, 1.0 };
	double dUvwAccel[3] = { 2.0, 2.0, 2.0 };
	double dUvwDecel[3] = { 2.0, 2.0, 2.0 };
	double dUVWScale = 2;

	dUvwPos[0] = GetTargetPos(_eBOX_LOADING_STAGE_X_STICK_LOAD_POS);
	dUvwPos[1] = GetTargetPos(_eBOX_LOADING_STAGE_Y_STICK_LOAD_POS);
	dUvwPos[2] = GetTargetPos(_eBOX_LOADING_STAGE_T_STICK_LOAD_POS);

	Str.Format(_T("Loading Stage Uvw Move To Load Pos ? (X:%.5f, Y:%.5f, T:%.5f)"), dUvwPos[0], dUvwPos[1], dUvwPos[2]);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	dUvwVel[0] = dVel;
	dUvwVel[1] = dVel;
	dUvwVel[2] = dVel;
	dUvwAccel[0] = dUvwVel[0] * dUVWScale;
	dUvwAccel[1] = dUvwVel[1] * dUVWScale;
	dUvwAccel[2] = dUvwVel[2] * dUVWScale;
	dUvwDecel[0] = dUvwVel[0] * dUVWScale;
	dUvwDecel[1] = dUvwVel[1] * dUVWScale;
	dUvwDecel[2] = dUvwVel[2] * dUVWScale;

	Devs::m_BoxMotion.UVWStagePosMove(dUvwPos, dUvwVel, dUvwAccel, dUvwDecel);
}
void CManual_Sub_Box_Fixed_Pos::OnBnClickedButtonManualSubBoxMoveStickUnloadPosLoadingStageXYT()
{
	//double dPos = GetTargetPos(_eBOX_LOADING_STAGE_X_STICK_UNLOAD_POS);
	//ManualAbsMove(_eMANUAL_BOX_AXIS_LOADING_STAGE_Y1, dPos);

	CString Str = _T("");
	double dVel = 1.0;
	double dAccel = dVel * 2.0;
	double dDecel = dVel * 2.0;
	double dUvwPos[3] = { 0.0, 0.0, 0.0 };
	double dUvwVel[3] = { 1.0, 1.0, 1.0 };
	double dUvwAccel[3] = { 2.0, 2.0, 2.0 };
	double dUvwDecel[3] = { 2.0, 2.0, 2.0 };
	double dUVWScale = 2;

	dUvwPos[0] = GetTargetPos(_eBOX_LOADING_STAGE_X_STICK_UNLOAD_POS);
	dUvwPos[1] = GetTargetPos(_eBOX_LOADING_STAGE_Y_STICK_UNLOAD_POS);
	dUvwPos[2] = GetTargetPos(_eBOX_LOADING_STAGE_T_STICK_UNLOAD_POS);

	Str.Format(_T("Loading Stage Uvw Move To Unload Pos ? (X:%.5f, Y:%.5f, T:%.5f)"), dUvwPos[0], dUvwPos[1], dUvwPos[2]);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	dUvwVel[0] = dVel;
	dUvwVel[1] = dVel;
	dUvwVel[2] = dVel;
	dUvwAccel[0] = dUvwVel[0] * dUVWScale;
	dUvwAccel[1] = dUvwVel[1] * dUVWScale;
	dUvwAccel[2] = dUvwVel[2] * dUVWScale;
	dUvwDecel[0] = dUvwVel[0] * dUVWScale;
	dUvwDecel[1] = dUvwVel[1] * dUVWScale;
	dUvwDecel[2] = dUvwVel[2] * dUVWScale;

	Devs::m_BoxMotion.UVWStagePosMove(dUvwPos, dUvwVel, dUvwAccel, dUvwDecel);
}
//Loading Stage Y
void CManual_Sub_Box_Fixed_Pos::OnBnClickedButtonManualSubBoxMoveWaitPosLoadingStageY2()
{
	double dPos = GetTargetPos(_eBOX_LOADING_STAGE_Y_WAIT_POS);
	ManualAbsMove(_eMANUAL_BOX_AXIS_LOADING_STAGE_Y2, dPos);
}
void CManual_Sub_Box_Fixed_Pos::OnBnClickedButtonManualSubBoxMoveStickLoadPosLoadingStageY2()
{
	double dPos = GetTargetPos(_eBOX_LOADING_STAGE_Y_STICK_LOAD_POS);
	ManualAbsMove(_eMANUAL_BOX_AXIS_LOADING_STAGE_Y2, dPos);
}
void CManual_Sub_Box_Fixed_Pos::OnBnClickedButtonManualSubBoxMoveStickUnloadPosLoadingStageY2()
{
	double dPos = GetTargetPos(_eBOX_LOADING_STAGE_Y_STICK_UNLOAD_POS);
	ManualAbsMove(_eMANUAL_BOX_AXIS_LOADING_STAGE_Y2, dPos);
}
//Loading Stage X
void CManual_Sub_Box_Fixed_Pos::OnBnClickedButtonManualSubBoxMoveWaitPosLoadingStageX()
{
	double dPos = GetTargetPos(_eBOX_LOADING_STAGE_X_WAIT_POS);
	ManualAbsMove(_eMANUAL_BOX_AXIS_LOADING_STAGE_X, dPos);
}
void CManual_Sub_Box_Fixed_Pos::OnBnClickedButtonManualSubBoxMoveStickLoadPosLoadingStageX()
{
	double dPos = GetTargetPos(_eBOX_LOADING_STAGE_X_STICK_LOAD_POS);
	ManualAbsMove(_eMANUAL_BOX_AXIS_LOADING_STAGE_X, dPos);
}
void CManual_Sub_Box_Fixed_Pos::OnBnClickedButtonManualSubBoxMoveStickUnloadPosLoadingStageX()
{
	double dPos = GetTargetPos(_eBOX_LOADING_STAGE_X_STICK_UNLOAD_POS);
	ManualAbsMove(_eMANUAL_BOX_AXIS_LOADING_STAGE_X, dPos);
}
#pragma endregion

void CManual_Sub_Box_Fixed_Pos::OnBnClickedButtonManualSubBoxFixedSave()
{
	CheckChangeData();
	CManualData::m_ManualDataBox.Save();

	AfxMessageBox(_T("Save Ok"));
}
