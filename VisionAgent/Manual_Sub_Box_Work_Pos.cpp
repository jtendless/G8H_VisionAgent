// Manual_Sub_LoadingStage_Work.cpp: 구현 파일
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "Manual_Sub_Box_Work_Pos.h"
#include "afxdialogex.h"


// CManual_Sub_Box_Work_Pos 대화 상자

IMPLEMENT_DYNAMIC(CManual_Sub_Box_Work_Pos, CDialogEx)

CManual_Sub_Box_Work_Pos::CManual_Sub_Box_Work_Pos(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_MANUAL_SUB_BOX_WORK_POS, pParent)
{
	Create(IDD_DLG_MANUAL_SUB_BOX_WORK_POS, pParent);
}

CManual_Sub_Box_Work_Pos::~CManual_Sub_Box_Work_Pos()
{
}

void CManual_Sub_Box_Work_Pos::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CManual_Sub_Box_Work_Pos, CDialogEx)
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_MANUAL_SUB_BOX_WORK_JOG_LOADING_STAGE_Y1, &CManual_Sub_Box_Work_Pos::OnBnClickedCheckManualSubBoxWorkJogLoadingStageY1)
	ON_BN_CLICKED(IDC_CHECK_MANUAL_SUB_BOX_WORK_JOG_LOADING_STAGE_Y2, &CManual_Sub_Box_Work_Pos::OnBnClickedCheckManualSubBoxWorkJogLoadingStageY2)
	ON_BN_CLICKED(IDC_CHECK_MANUAL_SUB_BOX_WORK_JOG_LOADING_STAGE_X, &CManual_Sub_Box_Work_Pos::OnBnClickedCheckManualSubBoxWorkJogLoadingStageX)
	ON_BN_CLICKED(IDC_CHECK_MANUAL_SUB_BOX_WORK_JOG_BOX_ALIGN_CAMERA_Y_LEFT, &CManual_Sub_Box_Work_Pos::OnBnClickedCheckManualSubBoxWorkJogBoxAlignCameraYLeft)
	ON_BN_CLICKED(IDC_CHECK_MANUAL_SUB_BOX_WORK_JOG_BOX_ALIGN_CAMERA_Y_RIGHT, &CManual_Sub_Box_Work_Pos::OnBnClickedCheckManualSubBoxWorkJogBoxAlignCameraYRight)
	ON_BN_CLICKED(IDC_CHECK_MANUAL_SUB_BOX_WORK_RELATIVE_LOADING_STAGE_Y1, &CManual_Sub_Box_Work_Pos::OnBnClickedCheckManualSubBoxWorkRelativeLoadingStageY1)
	ON_BN_CLICKED(IDC_CHECK_MANUAL_SUB_BOX_WORK_RELATIVE_LOADING_STAGE_Y2, &CManual_Sub_Box_Work_Pos::OnBnClickedCheckManualSubBoxWorkRelativeLoadingStageY2)
	ON_BN_CLICKED(IDC_CHECK_MANUAL_SUB_BOX_WORK_RELATIVE_LOADING_STAGE_X, &CManual_Sub_Box_Work_Pos::OnBnClickedCheckManualSubBoxWorkRelativeLoadingStageX)
	ON_BN_CLICKED(IDC_CHECK_MANUAL_SUB_BOX_WORK_RELATIVE_BOX_ALIGN_CAMERA_Y_LEFT, &CManual_Sub_Box_Work_Pos::OnBnClickedCheckManualSubBoxWorkRelativeBoxAlignCameraYLeft)
	ON_BN_CLICKED(IDC_CHECK_MANUAL_SUB_BOX_WORK_RELATIVE_BOX_ALIGN_CAMERA_Y_RIGHT, &CManual_Sub_Box_Work_Pos::OnBnClickedCheckManualSubBoxWorkRelativeBoxAlignCameraYRight)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_BOX_CCW_LOADING_STAGE_Y1, &CManual_Sub_Box_Work_Pos::OnBnClickedButtonManualSubBoxCcwLoadingStageY1)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_BOX_CCW_LOADING_STAGE_Y2, &CManual_Sub_Box_Work_Pos::OnBnClickedButtonManualSubBoxCcwLoadingStageY2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_BOX_CCW_LOADING_STAGE_X, &CManual_Sub_Box_Work_Pos::OnBnClickedButtonManualSubBoxCcwLoadingStageX)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_BOX_CCW_BOX_ALIGN_CAMERA_Y_LEFT, &CManual_Sub_Box_Work_Pos::OnBnClickedButtonManualSubBoxCcwBoxAlignCameraYLeft)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_BOX_CCW_BOX_ALIGN_CAMERA_Y_RIGHT, &CManual_Sub_Box_Work_Pos::OnBnClickedButtonManualSubBoxCcwBoxAlignCameraYRight)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_BOX_CW_LOADING_STAGE_Y1, &CManual_Sub_Box_Work_Pos::OnBnClickedButtonManualSubBoxCwLoadingStageY1)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_BOX_CW_LOADING_STAGE_Y2, &CManual_Sub_Box_Work_Pos::OnBnClickedButtonManualSubBoxCwLoadingStageY2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_BOX_CW_LOADING_STAGE_X, &CManual_Sub_Box_Work_Pos::OnBnClickedButtonManualSubBoxCwLoadingStageX)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_BOX_CW_BOX_ALIGN_CAMERA_Y_LEFT, &CManual_Sub_Box_Work_Pos::OnBnClickedButtonManualSubBoxCwBoxAlignCameraYLeft)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_BOX_CW_BOX_ALIGN_CAMERA_Y_RIGHT, &CManual_Sub_Box_Work_Pos::OnBnClickedButtonManualSubBoxCwBoxAlignCameraYRight)
END_MESSAGE_MAP()


// CManual_Sub_Box_Work_Pos 메시지 처리기

//------------------------------------------------------------------
BOOL CManual_Sub_Box_Work_Pos::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitCtrl();

	return TRUE;
}
//------------------------------------------------------------------
void CManual_Sub_Box_Work_Pos::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (Is_Comp_Usable() == TRUE)
	{
		if (bShow == TRUE)
		{
			InitPara();

			SetTimer(1, 100, NULL);
		}
		else if (bShow == FALSE)
		{
			KillTimer(1);
		}
	}
}
//------------------------------------------------------------------
void CManual_Sub_Box_Work_Pos::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (Is_Comp_Usable() == FALSE)	return;
}
//------------------------------------------------------------------
void CManual_Sub_Box_Work_Pos::OnTimer(UINT_PTR nIDEvent)
{
	CString Str = _T("");

	Str.Format(_T("%.5f"), SharedInfo::GetCmdPos(AXIS_LOADING_STAGE_Y1));
	m_stcCurPos[_eMANUAL_BOX_AXIS_LOADING_STAGE_Y1].SetWindowText(Str);
	Str.Format(_T("%.5f"), SharedInfo::GetCmdPos(AXIS_LOADING_STAGE_Y2));
	m_stcCurPos[_eMANUAL_BOX_AXIS_LOADING_STAGE_Y2].SetWindowText(Str);
	Str.Format(_T("%.5f"), SharedInfo::GetCmdPos(AXIS_LOADING_STAGE_X));
	m_stcCurPos[_eMANUAL_BOX_AXIS_LOADING_STAGE_X].SetWindowText(Str);
	//21.02.04 sjc no box cam servo
	//Str.Format(_T("%.5f"), SharedInfo::GetCmdPos(AXIS_BOX_ALIGN_CAMERA_YL));
	//m_stcCurPos[_eMANUAL_BOX_AXIS_BOX_ALIGN_CAMERA_YL].SetWindowText(Str);
	//Str.Format(_T("%.5f"), SharedInfo::GetCmdPos(AXIS_BOX_ALIGN_CAMERA_YR));
	//m_stcCurPos[_eMANUAL_BOX_AXIS_BOX_ALIGN_CAMERA_YR].SetWindowText(Str);

	CDialogEx::OnTimer(nIDEvent);
}

BOOL	CManual_Sub_Box_Work_Pos::Is_Comp_Usable()
{
	int i = 0;
	for (i = 0; i < _eMANUAL_BOX_AXIS_MAX; i++)
	{
		if (m_stcCurPos[i].GetSafeHwnd() == NULL) return FALSE;
		if (m_cbxSpeed[i].GetSafeHwnd() == NULL) return FALSE;
		if (m_cbxStep[i].GetSafeHwnd() == NULL) return FALSE;
		if (m_btnJogMove[i].GetSafeHwnd() == NULL) return FALSE;
		if (m_btnRelativeMove[i].GetSafeHwnd() == NULL) return FALSE;
		if (m_btnMovePlus[i].GetSafeHwnd() == NULL) return FALSE;
		if (m_btnMoveMinus[i].GetSafeHwnd() == NULL) return FALSE;
	}

	return TRUE;
}
//------------------------------------------------------------------
void CManual_Sub_Box_Work_Pos::InitCtrl()
{
	m_stcCurPos[_eMANUAL_BOX_AXIS_LOADING_STAGE_Y1].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_BOX_WORK_CURRENT_LOADING_STAGE_Y1, this);
	m_stcCurPos[_eMANUAL_BOX_AXIS_LOADING_STAGE_Y2].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_BOX_WORK_CURRENT_LOADING_STAGE_Y2, this);
	m_stcCurPos[_eMANUAL_BOX_AXIS_LOADING_STAGE_X].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_BOX_WORK_CURRENT_LOADING_STAGE_X, this);
	m_stcCurPos[_eMANUAL_BOX_AXIS_BOX_ALIGN_CAMERA_YL].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_BOX_WORK_CURRENT_BOX_ALIGN_CAMERA_Y_LEFT, this);
	m_stcCurPos[_eMANUAL_BOX_AXIS_BOX_ALIGN_CAMERA_YR].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_BOX_WORK_CURRENT_BOX_ALIGN_CAMERA_Y_RIGHT, this);

	m_cbxSpeed[_eMANUAL_BOX_AXIS_LOADING_STAGE_Y1].SubclassDlgItem(IDC_COMBO_MANUAL_SUB_BOX_WORK_SPEED_LOADING_STAGE_Y1, this);
	m_cbxSpeed[_eMANUAL_BOX_AXIS_LOADING_STAGE_Y2].SubclassDlgItem(IDC_COMBO_MANUAL_SUB_BOX_WORK_SPEED_LOADING_STAGE_Y2, this);
	m_cbxSpeed[_eMANUAL_BOX_AXIS_LOADING_STAGE_X].SubclassDlgItem(IDC_COMBO_MANUAL_SUB_BOX_WORK_SPEED_LOADING_STAGE_X, this);
	m_cbxSpeed[_eMANUAL_BOX_AXIS_BOX_ALIGN_CAMERA_YL].SubclassDlgItem(IDC_COMBO_MANUAL_SUB_BOX_WORK_SPEED_BOX_ALIGN_CAMERA_Y_LEFT, this);
	m_cbxSpeed[_eMANUAL_BOX_AXIS_BOX_ALIGN_CAMERA_YR].SubclassDlgItem(IDC_COMBO_MANUAL_SUB_BOX_WORK_SPEED_BOX_ALIGN_CAMERA_Y_RIGHT, this);

	m_cbxStep[_eMANUAL_BOX_AXIS_LOADING_STAGE_Y1].SubclassDlgItem(IDC_COMBO_MANUAL_SUB_BOX_STEP_LOADING_STAGE_Y1, this);
	m_cbxStep[_eMANUAL_BOX_AXIS_LOADING_STAGE_Y2].SubclassDlgItem(IDC_COMBO_MANUAL_SUB_BOX_STEP_LOADING_STAGE_Y2, this);
	m_cbxStep[_eMANUAL_BOX_AXIS_LOADING_STAGE_X].SubclassDlgItem(IDC_COMBO_MANUAL_SUB_BOX_STEP_LOADING_STAGE_X, this);
	m_cbxStep[_eMANUAL_BOX_AXIS_BOX_ALIGN_CAMERA_YL].SubclassDlgItem(IDC_COMBO_MANUAL_SUB_BOX_STEP_BOX_ALIGN_CAMERA_Y_LEFT, this);
	m_cbxStep[_eMANUAL_BOX_AXIS_BOX_ALIGN_CAMERA_YR].SubclassDlgItem(IDC_COMBO_MANUAL_SUB_BOX_STEP_BOX_ALIGN_CAMERA_Y_RIGHT, this);

	m_btnJogMove[_eMANUAL_BOX_AXIS_LOADING_STAGE_Y1].SubclassDlgItem(IDC_CHECK_MANUAL_SUB_BOX_WORK_JOG_LOADING_STAGE_Y1, this);
	m_btnJogMove[_eMANUAL_BOX_AXIS_LOADING_STAGE_Y2].SubclassDlgItem(IDC_CHECK_MANUAL_SUB_BOX_WORK_JOG_LOADING_STAGE_Y2, this);
	m_btnJogMove[_eMANUAL_BOX_AXIS_LOADING_STAGE_X].SubclassDlgItem(IDC_CHECK_MANUAL_SUB_BOX_WORK_JOG_LOADING_STAGE_X, this);
	m_btnJogMove[_eMANUAL_BOX_AXIS_BOX_ALIGN_CAMERA_YL].SubclassDlgItem(IDC_CHECK_MANUAL_SUB_BOX_WORK_JOG_BOX_ALIGN_CAMERA_Y_LEFT, this);
	m_btnJogMove[_eMANUAL_BOX_AXIS_BOX_ALIGN_CAMERA_YR].SubclassDlgItem(IDC_CHECK_MANUAL_SUB_BOX_WORK_JOG_BOX_ALIGN_CAMERA_Y_RIGHT, this);

	m_btnRelativeMove[_eMANUAL_BOX_AXIS_LOADING_STAGE_Y1].SubclassDlgItem(IDC_CHECK_MANUAL_SUB_BOX_WORK_RELATIVE_LOADING_STAGE_Y1, this);
	m_btnRelativeMove[_eMANUAL_BOX_AXIS_LOADING_STAGE_Y2].SubclassDlgItem(IDC_CHECK_MANUAL_SUB_BOX_WORK_RELATIVE_LOADING_STAGE_Y2, this);
	m_btnRelativeMove[_eMANUAL_BOX_AXIS_LOADING_STAGE_X].SubclassDlgItem(IDC_CHECK_MANUAL_SUB_BOX_WORK_RELATIVE_LOADING_STAGE_X, this);
	m_btnRelativeMove[_eMANUAL_BOX_AXIS_BOX_ALIGN_CAMERA_YL].SubclassDlgItem(IDC_CHECK_MANUAL_SUB_BOX_WORK_RELATIVE_BOX_ALIGN_CAMERA_Y_LEFT, this);
	m_btnRelativeMove[_eMANUAL_BOX_AXIS_BOX_ALIGN_CAMERA_YR].SubclassDlgItem(IDC_CHECK_MANUAL_SUB_BOX_WORK_RELATIVE_BOX_ALIGN_CAMERA_Y_RIGHT, this);

	m_btnMovePlus[_eMANUAL_BOX_AXIS_LOADING_STAGE_Y1].SubclassDlgItem(IDC_BUTTON_MANUAL_SUB_BOX_CW_LOADING_STAGE_Y1, this);
	m_btnMovePlus[_eMANUAL_BOX_AXIS_LOADING_STAGE_Y2].SubclassDlgItem(IDC_BUTTON_MANUAL_SUB_BOX_CW_LOADING_STAGE_Y2, this);
	m_btnMovePlus[_eMANUAL_BOX_AXIS_LOADING_STAGE_X].SubclassDlgItem(IDC_BUTTON_MANUAL_SUB_BOX_CW_LOADING_STAGE_X, this);
	m_btnMovePlus[_eMANUAL_BOX_AXIS_BOX_ALIGN_CAMERA_YL].SubclassDlgItem(IDC_BUTTON_MANUAL_SUB_BOX_CW_BOX_ALIGN_CAMERA_Y_LEFT, this);
	m_btnMovePlus[_eMANUAL_BOX_AXIS_BOX_ALIGN_CAMERA_YR].SubclassDlgItem(IDC_BUTTON_MANUAL_SUB_BOX_CW_BOX_ALIGN_CAMERA_Y_RIGHT, this);

	m_btnMoveMinus[_eMANUAL_BOX_AXIS_LOADING_STAGE_Y1].SubclassDlgItem(IDC_BUTTON_MANUAL_SUB_BOX_CCW_LOADING_STAGE_Y1, this);
	m_btnMoveMinus[_eMANUAL_BOX_AXIS_LOADING_STAGE_Y2].SubclassDlgItem(IDC_BUTTON_MANUAL_SUB_BOX_CCW_LOADING_STAGE_Y2, this);
	m_btnMoveMinus[_eMANUAL_BOX_AXIS_LOADING_STAGE_X].SubclassDlgItem(IDC_BUTTON_MANUAL_SUB_BOX_CCW_LOADING_STAGE_X, this);
	m_btnMoveMinus[_eMANUAL_BOX_AXIS_BOX_ALIGN_CAMERA_YL].SubclassDlgItem(IDC_BUTTON_MANUAL_SUB_BOX_CCW_BOX_ALIGN_CAMERA_Y_LEFT, this);
	m_btnMoveMinus[_eMANUAL_BOX_AXIS_BOX_ALIGN_CAMERA_YR].SubclassDlgItem(IDC_BUTTON_MANUAL_SUB_BOX_CCW_BOX_ALIGN_CAMERA_Y_RIGHT, this);

	CString strSpeed[3] = { _T("LOW"), _T("MEDIUM"), _T("HIGH") };
	CString strStep[7] = { _T("0.001"), _T("0.005"), _T("0.010"), _T("0.050"), _T("0.100"), _T("	0.500"), _T("1.000") };
	int i = 0, j = 0;
	for (i = 0; i < _eMANUAL_BOX_AXIS_MAX; i++)
	{
		ChangeMoveType((enum_Box_Axis)i, _eMOVE_TYPE_JOG);

		m_cbxSpeed[i].ResetContent();
		for (j = 0; j < 3; j++)
		{
			m_cbxSpeed[i].AddString(strSpeed[j]);
		}

		m_cbxStep[i].ResetContent();
		for (j = 0; j < 7; j++)
		{
			m_cbxStep[i].AddString(strStep[j]);
		}
	}
}
//------------------------------------------------------------------
void CManual_Sub_Box_Work_Pos::InitPara()
{
}

void CManual_Sub_Box_Work_Pos::ChangeMoveType(enum_Box_Axis eBoxAxis, enum_Move_Type eType)
{
	eMoveType[eBoxAxis] = eType;

	if (eType == _eMOVE_TYPE_JOG)
	{
		m_btnJogMove[eBoxAxis].SetColor(BLACK, DKGREEN);
		m_btnRelativeMove[eBoxAxis].SetColor(BLACK, LLTGRAY);
	}
	else //if (eType == _eMOVE_TYPE_RELATIVE)
	{
		m_btnJogMove[eBoxAxis].SetColor(BLACK, LLTGRAY);
		m_btnRelativeMove[eBoxAxis].SetColor(BLACK, DKGREEN);
	}
}

void CManual_Sub_Box_Work_Pos::ManualMove_Relative(enum_Box_Axis eBoxAxis, enum_MoveDir eDir)
{
	CString strAxisName = _T(""), Str = _T("");;
	enum_Axis eAxis = GetAxisNo(eBoxAxis, &strAxisName);
	double dVel = 0.0, dAccel = 0.0, dDecel = 0.0;
	BOOL bRet = FALSE;

	if (eAxis == AXIS_NONE)
		return;

	int nSpeed_Index = m_cbxSpeed[eBoxAxis].GetCurSel();
	bRet = SharedInfo::GetManualSpeed(eAxis, (enum_AXIS_SPEED)nSpeed_Index, &dVel, &dAccel, &dDecel);
	if (bRet == FALSE)
		return;

	if (eMoveType[eBoxAxis] != _eMOVE_TYPE_RELATIVE)
		return;

	double dMoveDist = 0.0, dMoveTargetPos = 0.0;
	CString strStep;
	m_cbxStep[eBoxAxis].GetWindowText(strStep);
	dMoveDist = _ttof(strStep);

	double dCurPos = SharedInfo::GetCmdPos(eAxis);

	if (eDir == eMOVE_DIR_N)
	{
		dVel = dVel * (-1);

		dMoveTargetPos = dCurPos - dMoveDist;
		Str.Format(_T("%s Move ?  %.5f - %.5f = %.5f"), strAxisName, dCurPos, dMoveDist, dMoveTargetPos);
	}
	else
	{
		dMoveTargetPos = dCurPos + dMoveDist;
		Str.Format(_T("%s Move ?  %.5f + %.5f = %.5f"), strAxisName, dCurPos, dMoveDist, dMoveTargetPos);
	}

	Devs::m_JogMotion.RelMove(eAxis, dMoveDist, dVel, dAccel, dDecel);
	Total_Msg(_T("%s Move %.5f -> .5f"), strAxisName, dCurPos, dMoveTargetPos);
}

void CManual_Sub_Box_Work_Pos::ManualMove_Jog(enum_Box_Axis eBoxAxis, enum_MoveDir eDir)
{
	CString strAxisName = _T(""), Str = _T("");;
	enum_Axis eAxis = GetAxisNo(eBoxAxis, &strAxisName);
	double dVel = 0.0, dAccel = 0.0, dDecel = 0.0;
	BOOL bRet = FALSE;

	if (eAxis == AXIS_NONE)
		return;

	if (eMoveType[eBoxAxis] != _eMOVE_TYPE_JOG)
		return;

	int nSpeed_Index = m_cbxSpeed[eBoxAxis].GetCurSel();
	bRet = SharedInfo::GetManualSpeed(eAxis, (enum_AXIS_SPEED)nSpeed_Index, &dVel, &dAccel, &dDecel);
	if (bRet == FALSE)
		return;

	if (eDir == eMOVE_DIR_N)
		dVel = dVel * (-1);

	SharedInfo::m_eAxisJog = eAxis;

	Devs::m_JogMotion.JogMove(eAxis, dVel, dAccel, dDecel);
}

enum_Axis CManual_Sub_Box_Work_Pos::GetAxisNo(enum_Box_Axis eBoxAxis, CString *strDiscription)
{
	CString Str = _T("");

	enum_Axis eAxis = AXIS_NONE;
	switch (eBoxAxis)
	{
	case _eMANUAL_BOX_AXIS_LOADING_STAGE_Y1:				eAxis = AXIS_LOADING_STAGE_Y1; Str = _T("LoadingStage Y1");  break;
	case _eMANUAL_BOX_AXIS_LOADING_STAGE_Y2:				eAxis = AXIS_LOADING_STAGE_Y2; Str = _T("LoadingStage Y2"); break;
	case _eMANUAL_BOX_AXIS_LOADING_STAGE_X:				eAxis = AXIS_LOADING_STAGE_X; Str = _T("LoadingStage X"); break;
		//21.02.04 sjc no box cam servo
	//case _eMANUAL_BOX_AXIS_BOX_ALIGN_CAMERA_YL:		eAxis = AXIS_BOX_ALIGN_CAMERA_YL; Str = _T("BoxAlignCamera YL"); break;
	//case _eMANUAL_BOX_AXIS_BOX_ALIGN_CAMERA_YR :		eAxis = AXIS_BOX_ALIGN_CAMERA_YR; Str = _T("BoxAlignCamera YR"); break;
	}

	*strDiscription = Str;

	return eAxis;
}

BOOL CManual_Sub_Box_Work_Pos::PreTranslateMessage(MSG* pMsg)
{
	int i = 0;
	switch (pMsg->message)
	{
	case WM_LBUTTONDOWN:
	{
		for (i = 0; i < _eMANUAL_BOX_AXIS_MAX; i++)
		{
			if (pMsg->hwnd == m_btnMoveMinus[i].GetSafeHwnd() && eMoveType[i] == _eMOVE_TYPE_JOG)
			{
				ManualMove_Jog((enum_Box_Axis)i, eMOVE_DIR_N);
				//Total_Msg(_T("Jog Start Minus"));
				break;
			}
			else if (pMsg->hwnd == m_btnMovePlus[i].GetSafeHwnd() && eMoveType[i] == _eMOVE_TYPE_JOG)
			{
				ManualMove_Jog((enum_Box_Axis)i, eMOVE_DIR_P);
				//Total_Msg(_T("Jog Start Plus"));
				break;
			}
		}
		break;
	}
	case WM_LBUTTONUP:
	{
		for (i = 0; i < _eMANUAL_BOX_AXIS_MAX; i++)
		{
			if (pMsg->hwnd == m_btnMoveMinus[i].GetSafeHwnd() && eMoveType[i] == _eMOVE_TYPE_JOG && SharedInfo::m_eAxisJog != AXIS_NONE)
			{
				Devs::m_JogMotion.JogStop(SharedInfo::m_eAxisJog);
				SharedInfo::m_eAxisJog = AXIS_NONE;
				Total_Msg(_T("Jog Stop"));
				break;
			}
			else if (pMsg->hwnd == m_btnMovePlus[i].GetSafeHwnd() && eMoveType[i] == _eMOVE_TYPE_JOG && SharedInfo::m_eAxisJog != AXIS_NONE)
			{

				Devs::m_JogMotion.JogStop(SharedInfo::m_eAxisJog);
				SharedInfo::m_eAxisJog = AXIS_NONE;
				Total_Msg(_T("Jog Stop"));
				break;
			}
		}
		break;
	}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

#pragma region //Jog Button
void CManual_Sub_Box_Work_Pos::OnBnClickedCheckManualSubBoxWorkJogLoadingStageY1()
{
	ChangeMoveType(_eMANUAL_BOX_AXIS_LOADING_STAGE_Y1, _eMOVE_TYPE_JOG);
}
void CManual_Sub_Box_Work_Pos::OnBnClickedCheckManualSubBoxWorkJogLoadingStageY2()
{
	ChangeMoveType(_eMANUAL_BOX_AXIS_LOADING_STAGE_Y2, _eMOVE_TYPE_JOG);
}
void CManual_Sub_Box_Work_Pos::OnBnClickedCheckManualSubBoxWorkJogLoadingStageX()
{
	ChangeMoveType(_eMANUAL_BOX_AXIS_LOADING_STAGE_X, _eMOVE_TYPE_JOG);
}
void CManual_Sub_Box_Work_Pos::OnBnClickedCheckManualSubBoxWorkJogBoxAlignCameraYLeft()
{
	ChangeMoveType(_eMANUAL_BOX_AXIS_BOX_ALIGN_CAMERA_YL, _eMOVE_TYPE_JOG);
}
void CManual_Sub_Box_Work_Pos::OnBnClickedCheckManualSubBoxWorkJogBoxAlignCameraYRight()
{
	ChangeMoveType(_eMANUAL_BOX_AXIS_BOX_ALIGN_CAMERA_YR, _eMOVE_TYPE_JOG);
}
#pragma endregion

#pragma region //Relative Button
void CManual_Sub_Box_Work_Pos::OnBnClickedCheckManualSubBoxWorkRelativeLoadingStageY1()
{
	ChangeMoveType(_eMANUAL_BOX_AXIS_LOADING_STAGE_Y1, _eMOVE_TYPE_RELATIVE);
}
void CManual_Sub_Box_Work_Pos::OnBnClickedCheckManualSubBoxWorkRelativeLoadingStageY2()
{
	ChangeMoveType(_eMANUAL_BOX_AXIS_LOADING_STAGE_Y2, _eMOVE_TYPE_RELATIVE);
}
void CManual_Sub_Box_Work_Pos::OnBnClickedCheckManualSubBoxWorkRelativeLoadingStageX()
{
	ChangeMoveType(_eMANUAL_BOX_AXIS_LOADING_STAGE_X, _eMOVE_TYPE_RELATIVE);
}
void CManual_Sub_Box_Work_Pos::OnBnClickedCheckManualSubBoxWorkRelativeBoxAlignCameraYLeft()
{
	ChangeMoveType(_eMANUAL_BOX_AXIS_BOX_ALIGN_CAMERA_YL, _eMOVE_TYPE_RELATIVE);
}
void CManual_Sub_Box_Work_Pos::OnBnClickedCheckManualSubBoxWorkRelativeBoxAlignCameraYRight()
{
	ChangeMoveType(_eMANUAL_BOX_AXIS_BOX_ALIGN_CAMERA_YR, _eMOVE_TYPE_RELATIVE);
}
#pragma endregion

#pragma region // - Button
void CManual_Sub_Box_Work_Pos::OnBnClickedButtonManualSubBoxCcwLoadingStageY1()
{
	enum_Box_Axis eBoxAxis = _eMANUAL_BOX_AXIS_LOADING_STAGE_Y1;
	if (eMoveType[eBoxAxis] == _eMOVE_TYPE_RELATIVE)
		ManualMove_Relative(eBoxAxis, eMOVE_DIR_N);
}
void CManual_Sub_Box_Work_Pos::OnBnClickedButtonManualSubBoxCcwLoadingStageY2()
{
	enum_Box_Axis eBoxAxis = _eMANUAL_BOX_AXIS_LOADING_STAGE_Y2;
	if (eMoveType[eBoxAxis] == _eMOVE_TYPE_RELATIVE)
		ManualMove_Relative(eBoxAxis, eMOVE_DIR_N);
}
void CManual_Sub_Box_Work_Pos::OnBnClickedButtonManualSubBoxCcwLoadingStageX()
{
	enum_Box_Axis eBoxAxis = _eMANUAL_BOX_AXIS_LOADING_STAGE_X;
	if (eMoveType[eBoxAxis] == _eMOVE_TYPE_RELATIVE)
		ManualMove_Relative(eBoxAxis, eMOVE_DIR_N);
}
void CManual_Sub_Box_Work_Pos::OnBnClickedButtonManualSubBoxCcwBoxAlignCameraYLeft()
{
	enum_Box_Axis eBoxAxis = _eMANUAL_BOX_AXIS_BOX_ALIGN_CAMERA_YL;
	if (eMoveType[eBoxAxis] == _eMOVE_TYPE_RELATIVE)
		ManualMove_Relative(eBoxAxis, eMOVE_DIR_N);
}
void CManual_Sub_Box_Work_Pos::OnBnClickedButtonManualSubBoxCcwBoxAlignCameraYRight()
{
	enum_Box_Axis eBoxAxis = _eMANUAL_BOX_AXIS_BOX_ALIGN_CAMERA_YR;
	if (eMoveType[eBoxAxis] == _eMOVE_TYPE_RELATIVE)
		ManualMove_Relative(eBoxAxis, eMOVE_DIR_N);
}
#pragma endregion

#pragma region //+ Button
void CManual_Sub_Box_Work_Pos::OnBnClickedButtonManualSubBoxCwLoadingStageY1()
{
	enum_Box_Axis eBoxAxis = _eMANUAL_BOX_AXIS_LOADING_STAGE_Y1;
	if (eMoveType[eBoxAxis] == _eMOVE_TYPE_RELATIVE)
		ManualMove_Relative(eBoxAxis, eMOVE_DIR_P);
}


void CManual_Sub_Box_Work_Pos::OnBnClickedButtonManualSubBoxCwLoadingStageY2()
{
	enum_Box_Axis eBoxAxis = _eMANUAL_BOX_AXIS_LOADING_STAGE_Y2;
	if (eMoveType[eBoxAxis] == _eMOVE_TYPE_RELATIVE)
		ManualMove_Relative(eBoxAxis, eMOVE_DIR_P);
}


void CManual_Sub_Box_Work_Pos::OnBnClickedButtonManualSubBoxCwLoadingStageX()
{
	enum_Box_Axis eBoxAxis = _eMANUAL_BOX_AXIS_LOADING_STAGE_X;
	if (eMoveType[eBoxAxis] == _eMOVE_TYPE_RELATIVE)
		ManualMove_Relative(eBoxAxis, eMOVE_DIR_P);
}


void CManual_Sub_Box_Work_Pos::OnBnClickedButtonManualSubBoxCwBoxAlignCameraYLeft()
{
	enum_Box_Axis eBoxAxis = _eMANUAL_BOX_AXIS_BOX_ALIGN_CAMERA_YL;
	if (eMoveType[eBoxAxis] == _eMOVE_TYPE_RELATIVE)
		ManualMove_Relative(eBoxAxis, eMOVE_DIR_P);
}


void CManual_Sub_Box_Work_Pos::OnBnClickedButtonManualSubBoxCwBoxAlignCameraYRight()
{
	enum_Box_Axis eBoxAxis = _eMANUAL_BOX_AXIS_BOX_ALIGN_CAMERA_YR;
	if (eMoveType[eBoxAxis] == _eMOVE_TYPE_RELATIVE)
		ManualMove_Relative(eBoxAxis, eMOVE_DIR_P);
}
#pragma endregion