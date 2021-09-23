// Manual_Sub_GripperZ_Fixed_Pos.cpp : implementation file
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "Manual_Sub_GripperZ_Fixed_Pos.h"
#include "afxdialogex.h"


// CManual_Sub_GripperZ_Fixed_Pos dialog

IMPLEMENT_DYNAMIC(CManual_Sub_GripperZ_Fixed_Pos, CDialogEx)

CManual_Sub_GripperZ_Fixed_Pos::CManual_Sub_GripperZ_Fixed_Pos(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_MANUAL_SUB_GRIPPER_Z_FIXED_POS, pParent)
{
	Create(IDD_DLG_MANUAL_SUB_GRIPPER_Z_FIXED_POS, pParent);
}

CManual_Sub_GripperZ_Fixed_Pos::~CManual_Sub_GripperZ_Fixed_Pos()
{
}

void CManual_Sub_GripperZ_Fixed_Pos::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CManual_Sub_GripperZ_Fixed_Pos, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_Z_FIXED_SAVE, &CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZFixedSave)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_Z_GET_WAIT_POS, &CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZGetWaitPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_Z_GET_UNCLAMP_POS, &CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZGetUnclampPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_Z_GET_LOADING_POS, &CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZGetLoadingPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_Z_GET_CLAMP_POS, &CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZGetClampPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_Z_GET_TENSION_POS, &CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZGetTensionPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_Z_SET_WAIT_POS, &CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZSetWaitPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_Z_SET_UNCLAMP_POS, &CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZSetUnclampPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_Z_SET_LOADING_POS, &CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZSetLoadingPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_Z_SET_CLAMP_POS, &CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZSetClampPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_Z_SET_TENSION_POS, &CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZSetTensionPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_Z_MOVE_WAIT_POS, &CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZMoveWaitPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_Z_MOVE_UNCLAMP_POS, &CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZMoveUnclampPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_Z_MOVE_LOADING_POS, &CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZMoveLoadingPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_Z_MOVE_CLAMP_POS, &CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZMoveClampPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_Z_MOVE_TENSION_POS, &CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZMoveTensionPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_Z_GET_WAIT_POS2, &CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZGetWaitPos2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_Z_GET_LOADING_POS2, &CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZGetLoadingPos2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_Z_GET_CLAMP_POS2, &CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZGetClampPos2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_Z_GET_TENSION_POS2, &CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZGetTensionPos2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_Z_GET_UNCLAMP_POS2, &CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZGetUnclampPos2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_Z_SET_WAIT_POS2, &CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZSetWaitPos2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_Z_SET_LOADING_POS2, &CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZSetLoadingPos2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_Z_SET_CLAMP_POS2, &CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZSetClampPos2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_Z_SET_TENSION_POS2, &CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZSetTensionPos2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_Z_SET_UNCLAMP_POS2, &CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZSetUnclampPos2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_Z_MOVE_WAIT_POS2, &CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZMoveWaitPos2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_Z_MOVE_LOADING_POS2, &CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZMoveLoadingPos2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_Z_MOVE_CLAMP_POS2, &CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZMoveClampPos2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_Z_MOVE_TENSION_POS2, &CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZMoveTensionPos2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_Z_MOVE_UNCLAMP_POS2, &CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZMoveUnclampPos2)
END_MESSAGE_MAP()


// CManual_Sub_GripperZ_Fixed_Pos message handlers

BOOL CManual_Sub_GripperZ_Fixed_Pos::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitCtrl();

	return TRUE;
}

void CManual_Sub_GripperZ_Fixed_Pos::OnShowWindow(BOOL bShow, UINT nStatus)
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

void CManual_Sub_GripperZ_Fixed_Pos::OnSize(UINT nType, int cx, int cy)
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
	GetDlgItem(IDC_BUTTON_MANUAL_SUB_GRIPPER_Z_FIXED_SAVE)->MoveWindow(RectSaveBtn);
}

void CManual_Sub_GripperZ_Fixed_Pos::OnTimer(UINT_PTR nIDEvent)
{	

	CDialogEx::OnTimer(nIDEvent);
}

void	CManual_Sub_GripperZ_Fixed_Pos::InitCtrl()
{
	//Stc
	m_stcPos[eGRIPPER_Z_WAIT_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_GRIPPER_Z_CURRENT_WAIT_POS, this);
	m_stcPos[eGRIPPER_Z_LOADING_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_GRIPPER_Z_CURRENT_LOADING_POS, this);
	m_stcPos[eGRIPPER_Z_CLAMP_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_GRIPPER_Z_CURRENT_CLAMP_POS, this);
	m_stcPos[eGRIPPER_Z_TENSION_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_GRIPPER_Z_CURRENT_TENSION_POS, this);
	m_stcPos[eGRIPPER_Z_UNCLAMP_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_GRIPPER_Z_CURRENT_UNCLAMP_POS, this);

	//Stc
	m_stcPos[eGRIPPER_RIGHT_Z_WAIT_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_GRIPPER_Z_CURRENT_WAIT_POS2, this);
	m_stcPos[eGRIPPER_RIGHT_Z_LOADING_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_GRIPPER_Z_CURRENT_LOADING_POS2, this);
	m_stcPos[eGRIPPER_RIGHT_Z_CLAMP_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_GRIPPER_Z_CURRENT_CLAMP_POS2, this);
	m_stcPos[eGRIPPER_RIGHT_Z_TENSION_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_GRIPPER_Z_CURRENT_TENSION_POS2, this);
	m_stcPos[eGRIPPER_RIGHT_Z_UNCLAMP_POS].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_GRIPPER_Z_CURRENT_UNCLAMP_POS2, this);

	//Edit
	m_editPos[eGRIPPER_Z_WAIT_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_GRIPPER_Z_WAIT_POS, this);
	m_editPos[eGRIPPER_Z_LOADING_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_GRIPPER_Z_LOADING_POS, this);
	m_editPos[eGRIPPER_Z_CLAMP_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_GRIPPER_Z_CLAMP_POS, this);
	m_editPos[eGRIPPER_Z_TENSION_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_GRIPPER_Z_TENSION_POS, this);
	m_editPos[eGRIPPER_Z_UNCLAMP_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_GRIPPER_Z_UNCLAMP_POS, this);


	//Edit
	m_editPos[eGRIPPER_RIGHT_Z_WAIT_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_GRIPPER_Z_WAIT_POS2, this);
	m_editPos[eGRIPPER_RIGHT_Z_LOADING_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_GRIPPER_Z_LOADING_POS2, this);
	m_editPos[eGRIPPER_RIGHT_Z_CLAMP_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_GRIPPER_Z_CLAMP_POS2, this);
	m_editPos[eGRIPPER_RIGHT_Z_TENSION_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_GRIPPER_Z_TENSION_POS2, this);
	m_editPos[eGRIPPER_RIGHT_Z_UNCLAMP_POS].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_GRIPPER_Z_UNCLAMP_POS2, this);
}

BOOL	CManual_Sub_GripperZ_Fixed_Pos::Is_Comp_Usable()
{
	if (GetDlgItem(IDC_BUTTON_MANUAL_SUB_GRIPPER_Z_FIXED_SAVE)->GetSafeHwnd() == NULL) return FALSE;
	return TRUE;
}

void CManual_Sub_GripperZ_Fixed_Pos::InitPara()
{
	CString Str = _T("");

	Str.Format(_T("%.5f"), CManualData::m_ManualDataGripperZ.Info.m_dGripperLeftZ_WaitPos);
	m_stcPos[eGRIPPER_Z_WAIT_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataGripperZ.Info.m_dGripperLeftZ_LoadingPos);
	m_stcPos[eGRIPPER_Z_LOADING_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataGripperZ.Info.m_dGripperLeftZ_ClampPos);
	m_stcPos[eGRIPPER_Z_CLAMP_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataGripperZ.Info.m_dGripperLeftZ_TensionPos);
	m_stcPos[eGRIPPER_Z_TENSION_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataGripperZ.Info.m_dGripperLeftZ_UnclampPos);
	m_stcPos[eGRIPPER_Z_UNCLAMP_POS].SetWindowText(Str);

	Str.Format(_T("%.5f"), CManualData::m_ManualDataGripperZ.Info.m_dGripperRightZ_WaitPos);
	m_stcPos[eGRIPPER_RIGHT_Z_WAIT_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataGripperZ.Info.m_dGripperRightZ_LoadingPos);
	m_stcPos[eGRIPPER_RIGHT_Z_LOADING_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataGripperZ.Info.m_dGripperRightZ_ClampPos);
	m_stcPos[eGRIPPER_RIGHT_Z_CLAMP_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataGripperZ.Info.m_dGripperRightZ_TensionPos);
	m_stcPos[eGRIPPER_RIGHT_Z_TENSION_POS].SetWindowText(Str);
	Str.Format(_T("%.5f"), CManualData::m_ManualDataGripperZ.Info.m_dGripperRightZ_UnclampPos);
	m_stcPos[eGRIPPER_RIGHT_Z_UNCLAMP_POS].SetWindowText(Str);
}

void CManual_Sub_GripperZ_Fixed_Pos::CheckChangeData()
{
	CString Str = _T("");
	
	m_stcPos[eGRIPPER_Z_WAIT_POS].GetWindowText(Str);
	CManualData::m_ManualDataGripperZ.Info.m_dGripperLeftZ_WaitPos = _ttof(Str);
	m_stcPos[eGRIPPER_Z_LOADING_POS].GetWindowText(Str);
	CManualData::m_ManualDataGripperZ.Info.m_dGripperLeftZ_LoadingPos = _ttof(Str);
	m_stcPos[eGRIPPER_Z_CLAMP_POS].GetWindowText(Str);
	CManualData::m_ManualDataGripperZ.Info.m_dGripperLeftZ_ClampPos = _ttof(Str);
	m_stcPos[eGRIPPER_Z_TENSION_POS].GetWindowText(Str);
	CManualData::m_ManualDataGripperZ.Info.m_dGripperLeftZ_TensionPos = _ttof(Str);
	m_stcPos[eGRIPPER_Z_UNCLAMP_POS].GetWindowText(Str);
	CManualData::m_ManualDataGripperZ.Info.m_dGripperLeftZ_UnclampPos = _ttof(Str);

	m_stcPos[eGRIPPER_RIGHT_Z_WAIT_POS].GetWindowText(Str);
	CManualData::m_ManualDataGripperZ.Info.m_dGripperRightZ_WaitPos = _ttof(Str);
	m_stcPos[eGRIPPER_RIGHT_Z_LOADING_POS].GetWindowText(Str);
	CManualData::m_ManualDataGripperZ.Info.m_dGripperRightZ_LoadingPos = _ttof(Str);
	m_stcPos[eGRIPPER_RIGHT_Z_CLAMP_POS].GetWindowText(Str);
	CManualData::m_ManualDataGripperZ.Info.m_dGripperRightZ_ClampPos = _ttof(Str);
	m_stcPos[eGRIPPER_RIGHT_Z_TENSION_POS].GetWindowText(Str);
	CManualData::m_ManualDataGripperZ.Info.m_dGripperRightZ_TensionPos = _ttof(Str);
	m_stcPos[eGRIPPER_RIGHT_Z_UNCLAMP_POS].GetWindowText(Str);
	CManualData::m_ManualDataGripperZ.Info.m_dGripperRightZ_UnclampPos = _ttof(Str);

}

void CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZFixedSave()
{
	CheckChangeData();
	CManualData::m_ManualDataGripperZ.Save();

	AfxMessageBox(_T("Save Ok"));
}

#pragma region //Get
void CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZGetWaitPos()
{
#ifndef GRIPPER_0
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_GRIPPER_ZL);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[eGRIPPER_Z_WAIT_POS].SetWindowText(Str);
#endif
}


void CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZGetUnclampPos()
{
#ifndef GRIPPER_0
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_GRIPPER_ZL);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[eGRIPPER_Z_UNCLAMP_POS].SetWindowText(Str);
#endif
}


void CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZGetLoadingPos()
{
#ifndef GRIPPER_0
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_GRIPPER_ZL);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[eGRIPPER_Z_LOADING_POS].SetWindowText(Str);
#endif
}


void CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZGetClampPos()
{
#ifndef GRIPPER_0
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_GRIPPER_ZL);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[eGRIPPER_Z_CLAMP_POS].SetWindowText(Str);
#endif
}


void CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZGetTensionPos()
{
#ifndef GRIPPER_0
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_GRIPPER_ZL);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[eGRIPPER_Z_TENSION_POS].SetWindowText(Str);
#endif
}
#pragma endregion

#pragma region //Set
void CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZSetWaitPos()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = eGRIPPER_Z_WAIT_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Gripper-Fixed] Gripper Left Z Pos Set Click (Wait Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}


void CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZSetUnclampPos()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = eGRIPPER_Z_UNCLAMP_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Gripper-Fixed] Gripper Left Z Pos Set Click (Unclamp Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}


void CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZSetLoadingPos()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = eGRIPPER_Z_LOADING_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Gripper-Fixed] Gripper Left Z Pos Set Click (Loading Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}


void CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZSetClampPos()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = eGRIPPER_Z_CLAMP_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Gripper-Fixed] Gripper Left Z Pos Set Click (Clamp Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}


void CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZSetTensionPos()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = eGRIPPER_Z_TENSION_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Gripper-Fixed] Gripper Left Z Pos Set Click (Tension Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}
#pragma endregion

#pragma region //Move
void CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZMoveWaitPos()
{
	double dPos = GetTargetPos(eGRIPPER_Z_WAIT_POS);
	ManualAbsMove(dPos);
}


void CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZMoveUnclampPos()
{
	double dPos = GetTargetPos(eGRIPPER_Z_UNCLAMP_POS);
	ManualAbsMove(dPos);
}


void CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZMoveLoadingPos()
{
	double dPos = GetTargetPos(eGRIPPER_Z_LOADING_POS);
	ManualAbsMove(dPos);
}


void CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZMoveClampPos()
{
	double dPos = GetTargetPos(eGRIPPER_Z_CLAMP_POS);
	ManualAbsMove(dPos);
}


void CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZMoveTensionPos()
{
	double dPos = GetTargetPos(eGRIPPER_Z_TENSION_POS);
	ManualAbsMove(dPos);
}
#pragma endregion

BOOL CManual_Sub_GripperZ_Fixed_Pos::ManualAbsMove(double dPos)
{
#ifndef GRIPPER_0
	CString strAxisName = _T("Gripper Left Z"), Str = _T("");
	double dVel = 0.0, dAccel = 0.0, dDecel = 0.0;
	enum_Axis eAxis = AXIS_GRIPPER_ZL;
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
#endif
	return TRUE;
}

double CManual_Sub_GripperZ_Fixed_Pos::GetTargetPos(enum_Gripper_Z_Pos eGripperZPos)
{
	CString Str = _T("");
	double dPos = 0.0;
	m_editPos[eGripperZPos].GetWindowText(Str);
	dPos = _ttof(Str);

	return dPos;
}

void CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZGetWaitPos2()
{
#ifndef GRIPPER_0
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_GRIPPER_ZR);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[eGRIPPER_RIGHT_Z_WAIT_POS].SetWindowText(Str);
#endif
}


void CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZGetLoadingPos2()
{
#ifndef GRIPPER_0
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_GRIPPER_ZR);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[eGRIPPER_RIGHT_Z_LOADING_POS].SetWindowText(Str);
#endif
}


void CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZGetClampPos2()
{
#ifndef GRIPPER_0
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_GRIPPER_ZR);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[eGRIPPER_RIGHT_Z_CLAMP_POS].SetWindowText(Str);
#endif
}


void CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZGetTensionPos2()
{
#ifndef GRIPPER_0
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_GRIPPER_ZR);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[eGRIPPER_RIGHT_Z_TENSION_POS].SetWindowText(Str);
#endif
}


void CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZGetUnclampPos2()
{
#ifndef GRIPPER_0
	CString Str = _T("");
	double dCurPos = SharedInfo::GetCmdPos(AXIS_GRIPPER_ZR);
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos[eGRIPPER_RIGHT_Z_UNCLAMP_POS].SetWindowText(Str);
#endif
}


void CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZSetWaitPos2()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = eGRIPPER_RIGHT_Z_WAIT_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Gripper-Fixed] Gripper Right Z Pos Set Click (Wait Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}


void CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZSetLoadingPos2()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = eGRIPPER_RIGHT_Z_LOADING_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Gripper-Fixed] Gripper Right Z Pos Set Click (Loading Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}


void CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZSetClampPos2()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = eGRIPPER_RIGHT_Z_CLAMP_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Gripper-Fixed] Gripper Right Z Pos Set Click (Clamp Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}


void CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZSetTensionPos2()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = eGRIPPER_RIGHT_Z_TENSION_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Gripper-Fixed] Gripper Right Z Pos Set Click (Tension Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}


void CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZSetUnclampPos2()
{
	CString Str = _T(""), StrMsg = _T("");
	int nIndex = eGRIPPER_RIGHT_Z_UNCLAMP_POS;
	m_editPos[nIndex].GetWindowText(Str);
	m_stcPos[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Gripper-Fixed] Gripper Right Z Pos Set Click (Unclamp Pos : %.5f)"), dPos);
	Total_Msg(StrMsg);
}


void CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZMoveWaitPos2()
{
	double dPos = GetTargetPos(eGRIPPER_RIGHT_Z_WAIT_POS);
	ManualAbsMove(dPos);
}


void CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZMoveLoadingPos2()
{
	double dPos = GetTargetPos(eGRIPPER_RIGHT_Z_LOADING_POS);
	ManualAbsMove(dPos);
}


void CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZMoveClampPos2()
{
	double dPos = GetTargetPos(eGRIPPER_RIGHT_Z_CLAMP_POS);
	ManualAbsMove(dPos);
}


void CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZMoveTensionPos2()
{
	double dPos = GetTargetPos(eGRIPPER_RIGHT_Z_TENSION_POS);
	ManualAbsMove(dPos);
}


void CManual_Sub_GripperZ_Fixed_Pos::OnBnClickedButtonManualSubGripperZMoveUnclampPos2()
{
	double dPos = GetTargetPos(eGRIPPER_RIGHT_Z_UNCLAMP_POS);
	ManualAbsMove(dPos);
}

BOOL CManual_Sub_GripperZ_Fixed_Pos::ManualAbsMoveZR(double dPos)
{
#ifndef GRIPPER_0
	CString strAxisName = _T("Gripper Left Z"), Str = _T("");
	double dVel = 0.0, dAccel = 0.0, dDecel = 0.0;
	enum_Axis eAxis = AXIS_GRIPPER_ZL;
	double dCurPos = 0.0;

	SharedInfo::GetManualSpeed(eAxis, eAXIS_SPEED_MEDIUM, &dVel, &dAccel, &dDecel);

	Str.Format(_T("%s Abs Move To Pos :%.5f Start?"), strAxisName, dPos);
	int nResult = AfxMessageBox(Str, MB_OKCANCEL);
	if (nResult == IDOK)
	{
		dCurPos = SharedInfo::GetCmdPos(eAxis);

		Devs::m_JogMotion.AbsMove(eAxis, dPos, dVel, dAccel, dDecel);

		Str.Format(_T("[Manual-Loader-Fixed] %s Abs Move %.5f -> %.5f"), strAxisName, dCurPos, dPos);
		Total_Msg(Str);
	}
#endif
	return TRUE;
}