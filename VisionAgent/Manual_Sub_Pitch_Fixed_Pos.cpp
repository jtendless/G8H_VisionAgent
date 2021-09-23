// Manual_Sub_Pitch_Fixed_Pos.cpp: 구현 파일
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "Manual_Sub_Pitch_Fixed_Pos.h"
#include "afxdialogex.h"


// CManual_Sub_Pitch_Fixed_Pos 대화 상자

IMPLEMENT_DYNAMIC(CManual_Sub_Pitch_Fixed_Pos, CDialogEx)

CManual_Sub_Pitch_Fixed_Pos::CManual_Sub_Pitch_Fixed_Pos(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_MANUAL_SUB_PITCH_FIXED_POS, pParent)
{
	Create(IDD_DLG_MANUAL_SUB_PITCH_FIXED_POS, pParent);
}

CManual_Sub_Pitch_Fixed_Pos::~CManual_Sub_Pitch_Fixed_Pos()
{
}

void CManual_Sub_Pitch_Fixed_Pos::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CManual_Sub_Pitch_Fixed_Pos, CDialogEx)
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_PITCH_FIXED_SAVE, &CManual_Sub_Pitch_Fixed_Pos::OnBnClickedButtonManualSubPitchFixedSave)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BUTTON_MANUAL_SUB_PITCH_GET_WAIT_POS_PITCH_L1, IDC_BUTTON_MANUAL_SUB_PITCH_GET_WAIT_POS_PITCH_L8, &CManual_Sub_Pitch_Fixed_Pos::OnBnClickedButtonManualSubPitchGetWaitPosPitchL)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BUTTON_MANUAL_SUB_PITCH_SET_WAIT_POS_PITCH_L1, IDC_BUTTON_MANUAL_SUB_PITCH_SET_WAIT_POS_PITCH_L8, &CManual_Sub_Pitch_Fixed_Pos::OnBnClickedButtonManualSubPitchSetWaitPosPitchL)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BUTTON_MANUAL_SUB_PITCH_MOVE_WAIT_POS_PITCH_L1, IDC_BUTTON_MANUAL_SUB_PITCH_MOVE_WAIT_POS_PITCH_L8, &CManual_Sub_Pitch_Fixed_Pos::OnBnClickedButtonManualSubPitchMoveWaitPosPitchL)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BUTTON_MANUAL_SUB_PITCH_GET_WAIT_POS_PITCH_R1, IDC_BUTTON_MANUAL_SUB_PITCH_GET_WAIT_POS_PITCH_R8, &CManual_Sub_Pitch_Fixed_Pos::OnBnClickedButtonManualSubPitchGetWaitPosPitchR)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BUTTON_MANUAL_SUB_PITCH_SET_WAIT_POS_PITCH_R1, IDC_BUTTON_MANUAL_SUB_PITCH_SET_WAIT_POS_PITCH_R8, &CManual_Sub_Pitch_Fixed_Pos::OnBnClickedButtonManualSubPitchSetWaitPosPitchR)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BUTTON_MANUAL_SUB_PITCH_MOVE_WAIT_POS_PITCH_R1, IDC_BUTTON_MANUAL_SUB_PITCH_MOVE_WAIT_POS_PITCH_R8, &CManual_Sub_Pitch_Fixed_Pos::OnBnClickedButtonManualSubPitchMoveWaitPosPitchR)
END_MESSAGE_MAP()


// CManual_Sub_Pitch_Fixed_Pos 메시지 처리기

BOOL CManual_Sub_Pitch_Fixed_Pos::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitCtrl();

	return TRUE;
}
//------------------------------------------------------------------
void CManual_Sub_Pitch_Fixed_Pos::OnSize(UINT nType, int cx, int cy)
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
	GetDlgItem(IDC_BUTTON_MANUAL_SUB_PITCH_FIXED_SAVE)->MoveWindow(RectSaveBtn);
}
//------------------------------------------------------------------
void CManual_Sub_Pitch_Fixed_Pos::OnShowWindow(BOOL bShow, UINT nStatus)
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
void	CManual_Sub_Pitch_Fixed_Pos::InitCtrl()
{
	m_stcPos_L[eGRIPPER_ROW1].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_PITCH_CURRENT_WAIT_POS_PITCH_L1, this);
	m_stcPos_L[eGRIPPER_ROW2].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_PITCH_CURRENT_WAIT_POS_PITCH_L2, this);
	m_stcPos_L[eGRIPPER_ROW3].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_PITCH_CURRENT_WAIT_POS_PITCH_L3, this);
	//m_stcPos_L[eGRIPPER_ROW4].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_PITCH_CURRENT_WAIT_POS_PITCH_L4, this);
	//m_stcPos_L[eGRIPPER_ROW5].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_PITCH_CURRENT_WAIT_POS_PITCH_L5, this);
#ifdef GRIPPER_8
	m_stcPos_L[eGRIPPER_ROW6].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_PITCH_CURRENT_WAIT_POS_PITCH_L6, this);
	m_stcPos_L[eGRIPPER_ROW7].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_PITCH_CURRENT_WAIT_POS_PITCH_L7, this);
	m_stcPos_L[eGRIPPER_ROW8].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_PITCH_CURRENT_WAIT_POS_PITCH_L8, this);
#endif

	m_stcPos_R[eGRIPPER_ROW1].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_PITCH_CURRENT_WAIT_POS_PITCH_R1, this);
	m_stcPos_R[eGRIPPER_ROW2].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_PITCH_CURRENT_WAIT_POS_PITCH_R2, this);
	m_stcPos_R[eGRIPPER_ROW3].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_PITCH_CURRENT_WAIT_POS_PITCH_R3, this);
	//m_stcPos_R[eGRIPPER_ROW4].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_PITCH_CURRENT_WAIT_POS_PITCH_R4, this);
	//m_stcPos_R[eGRIPPER_ROW5].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_PITCH_CURRENT_WAIT_POS_PITCH_R5, this);
#ifdef GRIPPER_8
	m_stcPos_R[eGRIPPER_ROW6].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_PITCH_CURRENT_WAIT_POS_PITCH_R6, this);
	m_stcPos_R[eGRIPPER_ROW7].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_PITCH_CURRENT_WAIT_POS_PITCH_R7, this);
	m_stcPos_R[eGRIPPER_ROW8].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_PITCH_CURRENT_WAIT_POS_PITCH_R8, this);
#endif

	m_editPos_L[eGRIPPER_ROW1].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_PITCH_WAIT_POS_PITCH_L1, this);
	m_editPos_L[eGRIPPER_ROW2].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_PITCH_WAIT_POS_PITCH_L2, this);
	m_editPos_L[eGRIPPER_ROW3].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_PITCH_WAIT_POS_PITCH_L3, this);
	//m_editPos_L[eGRIPPER_ROW4].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_PITCH_WAIT_POS_PITCH_L4, this);
	//m_editPos_L[eGRIPPER_ROW5].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_PITCH_WAIT_POS_PITCH_L5, this);
#ifdef GRIPPER_8
	m_editPos_L[eGRIPPER_ROW6].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_PITCH_WAIT_POS_PITCH_L6, this);
	m_editPos_L[eGRIPPER_ROW7].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_PITCH_WAIT_POS_PITCH_L7, this);
	m_editPos_L[eGRIPPER_ROW8].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_PITCH_WAIT_POS_PITCH_L8, this);
#endif

	m_editPos_R[eGRIPPER_ROW1].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_PITCH_WAIT_POS_PITCH_R1, this);
	m_editPos_R[eGRIPPER_ROW2].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_PITCH_WAIT_POS_PITCH_R2, this);
	m_editPos_R[eGRIPPER_ROW3].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_PITCH_WAIT_POS_PITCH_R3, this);
	//m_editPos_R[eGRIPPER_ROW4].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_PITCH_WAIT_POS_PITCH_R4, this);
	//m_editPos_R[eGRIPPER_ROW5].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_PITCH_WAIT_POS_PITCH_R5, this);
#ifdef GRIPPER_8
	m_editPos_R[eGRIPPER_ROW6].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_PITCH_WAIT_POS_PITCH_R6, this);
	m_editPos_R[eGRIPPER_ROW7].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_PITCH_WAIT_POS_PITCH_R7, this);
	m_editPos_R[eGRIPPER_ROW8].SubclassDlgItem(IDC_EDIT_MANUAL_SUB_PITCH_WAIT_POS_PITCH_R8, this);
#endif
}
//------------------------------------------------------------------
BOOL	CManual_Sub_Pitch_Fixed_Pos::Is_Comp_Usable()
{
	if (GetDlgItem(IDC_BUTTON_MANUAL_SUB_PITCH_FIXED_SAVE)->GetSafeHwnd() == NULL) return FALSE;
	return TRUE;
}
//------------------------------------------------------------------
void CManual_Sub_Pitch_Fixed_Pos::OnTimer(UINT_PTR nIDEvent)
{

	CDialogEx::OnTimer(nIDEvent);
}
//------------------------------------------------------------------
void CManual_Sub_Pitch_Fixed_Pos::InitPara()
{
	CString Str = _T("");
	int i = 0;
	for (i = 0; i < eGRIPPER_ROW_MAX; i++)
	{
		Str.Format(_T("%.5f"), CManualData::m_ManualDataPitch.Info.m_dPitchLeft_WaitPos[i]);
		m_stcPos_L[i].SetWindowText(Str);

		Str.Format(_T("%.5f"), CManualData::m_ManualDataPitch.Info.m_dPitchRight_WaitPos[i]);
		m_stcPos_R[i].SetWindowText(Str);
	}
}
//------------------------------------------------------------------
void CManual_Sub_Pitch_Fixed_Pos::CheckChangeData()
{
	CString Str = _T("");
	int i = 0;
	for (i = 0; i < eGRIPPER_ROW_MAX; i++)
	{
		m_stcPos_L[i].GetWindowText(Str);
		CManualData::m_ManualDataPitch.Info.m_dPitchLeft_WaitPos[i] = _ttof(Str);

		m_stcPos_R[i].GetWindowText(Str);
		CManualData::m_ManualDataPitch.Info.m_dPitchRight_WaitPos[i] = _ttof(Str);
	}
}

void CManual_Sub_Pitch_Fixed_Pos::OnBnClickedButtonManualSubPitchFixedSave()
{
	CheckChangeData();
	CManualData::m_ManualDataPitch.Save();

	AfxMessageBox(_T("Save Ok"));
}

#pragma region //Pitch Left
void CManual_Sub_Pitch_Fixed_Pos::OnBnClickedButtonManualSubPitchGetWaitPosPitchL(UINT id)
{
	CString Str = _T("");

	int nIndex = id - IDC_BUTTON_MANUAL_SUB_PITCH_GET_WAIT_POS_PITCH_L1;

	double dCurPos = SharedInfo::GetCmdPos((enum_Axis)(AXIS_GRIPPER_PITCH_L1 + nIndex));
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos_L[nIndex].SetWindowText(Str);
}

void CManual_Sub_Pitch_Fixed_Pos::OnBnClickedButtonManualSubPitchSetWaitPosPitchL(UINT id)
{
	CString Str = _T(""), StrMsg = _T("");

	int nIndex = id - IDC_BUTTON_MANUAL_SUB_PITCH_GET_WAIT_POS_PITCH_L1;

	m_editPos_L[nIndex].GetWindowText(Str);
	m_stcPos_L[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Pitch-Fixed] Pitch L%d Pos Set Click (Wait Pos : %.5f)"), nIndex + 1, dPos);
	Total_Msg(StrMsg);
}

void CManual_Sub_Pitch_Fixed_Pos::OnBnClickedButtonManualSubPitchMoveWaitPosPitchL(UINT id)
{
	CString Str = _T(""), StrMsg = _T("");

	int nIndex = id - IDC_BUTTON_MANUAL_SUB_PITCH_GET_WAIT_POS_PITCH_L1;

	m_editPos_L[nIndex].GetWindowText(Str);

	double dPos = _ttof(Str);

	StrMsg.Format(_T("Pitch L%d Move ? (Pos:%.5f)"), nIndex + 1, dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	Devs::m_PitchMotion.PitchPosMove((enum_Axis)(AXIS_GRIPPER_PITCH_L1 + nIndex), dPos);

	Str.Format(_T("Pitch L%d,Wait Pos Move (Pos:%.5f)"), dPos);
	Total_Msg(Str);
}
#pragma endregion

#pragma region //Pitch Right
void CManual_Sub_Pitch_Fixed_Pos::OnBnClickedButtonManualSubPitchGetWaitPosPitchR(UINT id)
{
	CString Str = _T("");

	int nIndex = id - IDC_BUTTON_MANUAL_SUB_PITCH_GET_WAIT_POS_PITCH_R1;

	double dCurPos = SharedInfo::GetCmdPos((enum_Axis)(AXIS_GRIPPER_PITCH_R1 + nIndex));
	Str.Format(_T("%.5f"), dCurPos);
	m_editPos_R[nIndex].SetWindowText(Str);
}

void CManual_Sub_Pitch_Fixed_Pos::OnBnClickedButtonManualSubPitchSetWaitPosPitchR(UINT id)
{
	CString Str = _T(""), StrMsg = _T("");

	int nIndex = id - IDC_BUTTON_MANUAL_SUB_PITCH_GET_WAIT_POS_PITCH_R1;

	m_editPos_R[nIndex].GetWindowText(Str);
	m_stcPos_R[nIndex].SetWindowText(Str);

	double dPos = _ttof(Str);
	StrMsg.Format(_T("[Manual-Pitch-Fixed] Pitch R%d Pos Set Click (Wait Pos : %.5f)"), nIndex + 1, dPos);
	Total_Msg(StrMsg);
}

void CManual_Sub_Pitch_Fixed_Pos::OnBnClickedButtonManualSubPitchMoveWaitPosPitchR(UINT id)
{
	CString Str = _T(""), StrMsg = _T("");

	int nIndex = id - IDC_BUTTON_MANUAL_SUB_PITCH_GET_WAIT_POS_PITCH_R1;

	m_editPos_R[nIndex].GetWindowText(Str);

	double dPos = _ttof(Str);

	StrMsg.Format(_T("Pitch R%d Move ? (Pos:%.5f)"), nIndex + 1, dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	Devs::m_PitchMotion.PitchPosMove((enum_Axis)(AXIS_GRIPPER_PITCH_R1 + nIndex), dPos);

	Str.Format(_T("Pitch R%d,Wait Pos Move (Pos:%.5f)"), dPos);
	Total_Msg(Str);
}
#pragma endregion