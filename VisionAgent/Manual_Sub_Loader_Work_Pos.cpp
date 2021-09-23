// Manual_Sub_Loader_Work_Pos.cpp: 구현 파일
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "Manual_Sub_Loader_Work_Pos.h"
#include "afxdialogex.h"


// CManual_Sub_Loader_Work_Pos 대화 상자

IMPLEMENT_DYNAMIC(CManual_Sub_Loader_Work_Pos, CDialogEx)

CManual_Sub_Loader_Work_Pos::CManual_Sub_Loader_Work_Pos(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_MANUAL_SUB_LOADER_WORK_POS, pParent)
{
	Create(IDD_DLG_MANUAL_SUB_LOADER_WORK_POS, pParent);
}

CManual_Sub_Loader_Work_Pos::~CManual_Sub_Loader_Work_Pos()
{
}

void CManual_Sub_Loader_Work_Pos::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CManual_Sub_Loader_Work_Pos, CDialogEx)
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_MANUAL_SUB_LOADER_WORK_JOG_LOADER_Z, &CManual_Sub_Loader_Work_Pos::OnBnClickedCheckManualSubLoaderWorkJogLoaderZ)
	ON_BN_CLICKED(IDC_CHECK_MANUAL_SUB_LOADER_WORK_JOG_LOADER_X, &CManual_Sub_Loader_Work_Pos::OnBnClickedCheckManualSubLoaderWorkJogLoaderX)
	ON_BN_CLICKED(IDC_CHECK_MANUAL_SUB_LOADER_WORK_RELATIVE_LOADER_Z, &CManual_Sub_Loader_Work_Pos::OnBnClickedCheckManualSubLoaderWorkRelativeLoaderZ)
	ON_BN_CLICKED(IDC_CHECK_MANUAL_SUB_LOADER_WORK_RELATIVE_LOADER_X, &CManual_Sub_Loader_Work_Pos::OnBnClickedCheckManualSubLoaderWorkRelativeLoaderX)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_WORK_CCW_LOADER_Z, &CManual_Sub_Loader_Work_Pos::OnBnClickedButtonManualSubLoaderWorkCcwLoaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_WORK_CCW_LOADER_X, &CManual_Sub_Loader_Work_Pos::OnBnClickedButtonManualSubLoaderWorkCcwLoaderX)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_WORK_CW_LOADER_Z, &CManual_Sub_Loader_Work_Pos::OnBnClickedButtonManualSubLoaderWorkCwLoaderZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_WORK_CW_LOADER_X, &CManual_Sub_Loader_Work_Pos::OnBnClickedButtonManualSubLoaderWorkCwLoaderX)
	ON_BN_CLICKED(IDC_CHECK_MANUAL_SUB_LOADER_WORK_JOG_LOADER_Z2, &CManual_Sub_Loader_Work_Pos::OnBnClickedCheckManualSubLoaderWorkJogLoaderZ2)
	ON_BN_CLICKED(IDC_CHECK_MANUAL_SUB_LOADER_WORK_RELATIVE_LOADER_Z2, &CManual_Sub_Loader_Work_Pos::OnBnClickedCheckManualSubLoaderWorkRelativeLoaderZ2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_WORK_CCW_LOADER_Z2, &CManual_Sub_Loader_Work_Pos::OnBnClickedButtonManualSubLoaderWorkCcwLoaderZ2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_WORK_CW_LOADER_Z2, &CManual_Sub_Loader_Work_Pos::OnBnClickedButtonManualSubLoaderWorkCwLoaderZ2)
	ON_BN_CLICKED(IDC_CHECK_MANUAL_SUB_LOADER_WORK_JOG_LOADER_Z3, &CManual_Sub_Loader_Work_Pos::OnBnClickedCheckManualSubLoaderWorkJogLoaderZ3)
	ON_BN_CLICKED(IDC_CHECK_MANUAL_SUB_LOADER_WORK_RELATIVE_LOADER_Z3, &CManual_Sub_Loader_Work_Pos::OnBnClickedCheckManualSubLoaderWorkRelativeLoaderZ3)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_WORK_CCW_LOADER_Z3, &CManual_Sub_Loader_Work_Pos::OnBnClickedButtonManualSubLoaderWorkCcwLoaderZ3)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_WORK_CW_LOADER_Z3, &CManual_Sub_Loader_Work_Pos::OnBnClickedButtonManualSubLoaderWorkCwLoaderZ3)
END_MESSAGE_MAP()


// CManual_Sub_Loader_Work_Pos 메시지 처리기

//------------------------------------------------------------------
BOOL CManual_Sub_Loader_Work_Pos::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitCtrl();

	return TRUE;
}
//------------------------------------------------------------------
void CManual_Sub_Loader_Work_Pos::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (Is_Comp_Usable() == TRUE)
	{
		InitPara();
		if (bShow == TRUE)
		{
			SetTimer(1, 100, NULL);
		}
		else if (bShow == FALSE)
		{
			KillTimer(1);
		}
	}
}
//------------------------------------------------------------------
void CManual_Sub_Loader_Work_Pos::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (Is_Comp_Usable() == FALSE)	return;
}
//------------------------------------------------------------------
void CManual_Sub_Loader_Work_Pos::OnTimer(UINT_PTR nIDEvent)
{
	CString Str = _T("");

	Str.Format(_T("%.5f"), SharedInfo::GetCmdPos(AXIS_LOADER_Z));
	m_stcCurPos[_eMANUAL_LOADER_AXIS_Z].SetWindowText(Str);

	Str.Format(_T("%.5f"), SharedInfo::GetCmdPos(AXIS_LOADER_X));
	m_stcCurPos[_eMANUAL_LOADER_AXIS_X].SetWindowText(Str);

	CDialogEx::OnTimer(nIDEvent);
}
//------------------------------------------------------------------
BOOL	CManual_Sub_Loader_Work_Pos::Is_Comp_Usable()
{
	int i = 0;
	for (i = 0; i < _eMANUAL_LOADER_AXIS_MAX-1; i++)
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
void CManual_Sub_Loader_Work_Pos::InitCtrl()
{
	m_stcCurPos[_eMANUAL_LOADER_AXIS_Z].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_LOADER_WORK_CURRENT_LOADER_Z, this);
	m_stcCurPos[_eMANUAL_LOADER_AXIS_X].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_LOADER_WORK_CURRENT_LOADER_X, this);

	m_cbxSpeed[_eMANUAL_LOADER_AXIS_Z].SubclassDlgItem(IDC_COMBO_MANUAL_SUB_LOADER_WORK_SPEED_LOADER_Z, this);
	m_cbxSpeed[_eMANUAL_LOADER_AXIS_X].SubclassDlgItem(IDC_COMBO_MANUAL_SUB_LOADER_WORK_SPEED_LOADER_X, this);

	m_cbxStep[_eMANUAL_LOADER_AXIS_Z].SubclassDlgItem(IDC_COMBO_MANUAL_SUB_LOADER_WORK_STEP_LOADER_Z, this);
	m_cbxStep[_eMANUAL_LOADER_AXIS_X].SubclassDlgItem(IDC_COMBO_MANUAL_SUB_LOADER_WORK_STEP_LOADER_X, this);

	m_btnJogMove[_eMANUAL_LOADER_AXIS_Z].SubclassDlgItem(IDC_CHECK_MANUAL_SUB_LOADER_WORK_JOG_LOADER_Z, this);
	m_btnJogMove[_eMANUAL_LOADER_AXIS_X].SubclassDlgItem(IDC_CHECK_MANUAL_SUB_LOADER_WORK_JOG_LOADER_X, this);

	m_btnRelativeMove[_eMANUAL_LOADER_AXIS_Z].SubclassDlgItem(IDC_CHECK_MANUAL_SUB_LOADER_WORK_RELATIVE_LOADER_Z, this);
	m_btnRelativeMove[_eMANUAL_LOADER_AXIS_X].SubclassDlgItem(IDC_CHECK_MANUAL_SUB_LOADER_WORK_RELATIVE_LOADER_X, this);

	m_btnMovePlus[_eMANUAL_LOADER_AXIS_Z].SubclassDlgItem(IDC_BUTTON_MANUAL_SUB_LOADER_WORK_CW_LOADER_Z, this);
	m_btnMovePlus[_eMANUAL_LOADER_AXIS_X].SubclassDlgItem(IDC_BUTTON_MANUAL_SUB_LOADER_WORK_CW_LOADER_X, this);

	m_btnMoveMinus[_eMANUAL_LOADER_AXIS_Z].SubclassDlgItem(IDC_BUTTON_MANUAL_SUB_LOADER_WORK_CCW_LOADER_Z, this);
	m_btnMoveMinus[_eMANUAL_LOADER_AXIS_X].SubclassDlgItem(IDC_BUTTON_MANUAL_SUB_LOADER_WORK_CCW_LOADER_X, this);
	//21.02.05 sjc loader sub z
	m_stcCurPos[_eMANUAL_LOADER_AXIS_SUB_ZL].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_LOADER_WORK_CURRENT_LOADER_Z2, this);
	m_cbxSpeed[_eMANUAL_LOADER_AXIS_SUB_ZL].SubclassDlgItem(IDC_COMBO_MANUAL_SUB_LOADER_WORK_SPEED_LOADER_Z2, this);
	m_cbxStep[_eMANUAL_LOADER_AXIS_SUB_ZL].SubclassDlgItem(IDC_COMBO_MANUAL_SUB_LOADER_WORK_STEP_LOADER_Z2, this);
	m_btnJogMove[_eMANUAL_LOADER_AXIS_SUB_ZL].SubclassDlgItem(IDC_CHECK_MANUAL_SUB_LOADER_WORK_JOG_LOADER_Z2, this);
	m_btnRelativeMove[_eMANUAL_LOADER_AXIS_SUB_ZL].SubclassDlgItem(IDC_CHECK_MANUAL_SUB_LOADER_WORK_RELATIVE_LOADER_Z2, this);
	m_btnMovePlus[_eMANUAL_LOADER_AXIS_SUB_ZL].SubclassDlgItem(IDC_BUTTON_MANUAL_SUB_LOADER_WORK_CW_LOADER_Z2, this);
	m_btnMoveMinus[_eMANUAL_LOADER_AXIS_SUB_ZL].SubclassDlgItem(IDC_BUTTON_MANUAL_SUB_LOADER_WORK_CCW_LOADER_Z2, this);
	//
	m_stcCurPos[_eMANUAL_LOADER_AXIS_SUB_ZR].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_LOADER_WORK_CURRENT_LOADER_Z3, this);
	m_cbxSpeed[_eMANUAL_LOADER_AXIS_SUB_ZR].SubclassDlgItem(IDC_COMBO_MANUAL_SUB_LOADER_WORK_SPEED_LOADER_Z3, this);
	m_cbxStep[_eMANUAL_LOADER_AXIS_SUB_ZR].SubclassDlgItem(IDC_COMBO_MANUAL_SUB_LOADER_WORK_STEP_LOADER_Z3, this);
	m_btnJogMove[_eMANUAL_LOADER_AXIS_SUB_ZR].SubclassDlgItem(IDC_CHECK_MANUAL_SUB_LOADER_WORK_JOG_LOADER_Z3, this);
	m_btnRelativeMove[_eMANUAL_LOADER_AXIS_SUB_ZR].SubclassDlgItem(IDC_CHECK_MANUAL_SUB_LOADER_WORK_RELATIVE_LOADER_Z3, this);
	m_btnMovePlus[_eMANUAL_LOADER_AXIS_SUB_ZR].SubclassDlgItem(IDC_BUTTON_MANUAL_SUB_LOADER_WORK_CW_LOADER_Z3, this);
	m_btnMoveMinus[_eMANUAL_LOADER_AXIS_SUB_ZR].SubclassDlgItem(IDC_BUTTON_MANUAL_SUB_LOADER_WORK_CCW_LOADER_Z3, this);

	CString strSpeed[3] = { _T("LOW"), _T("MEDIUM"), _T("HIGH") };
	CString strStep[7] = { _T("0.001"), _T("0.005"), _T("0.010"), _T("0.050"), _T("0.100"), _T("	0.500"), _T("1.000") };
	int i = 0, j = 0;
	for (i = 0; i < _eMANUAL_LOADER_AXIS_MAX-1; i++)
	{
		ChangeMoveType((enum_Loader_Axis)i, _eMOVE_TYPE_JOG);

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
void CManual_Sub_Loader_Work_Pos::InitPara()
{
	//저장된 데이터를 UI에 표시
}
void CManual_Sub_Loader_Work_Pos::ChangeMoveType(enum_Loader_Axis eLoaderAxis, enum_Move_Type eType)
{
	eMoveType[eLoaderAxis] = eType;

	if (eType == _eMOVE_TYPE_JOG)
	{
		m_btnJogMove[eLoaderAxis].SetColor(BLACK, DKGREEN);
		m_btnRelativeMove[eLoaderAxis].SetColor(BLACK, LLTGRAY);
	}
	else //if (eType == _eMOVE_TYPE_RELATIVE)
	{
		m_btnJogMove[eLoaderAxis].SetColor(BLACK, LLTGRAY);
		m_btnRelativeMove[eLoaderAxis].SetColor(BLACK, DKGREEN);
	}
}

void CManual_Sub_Loader_Work_Pos::ManualMove_Relative(enum_Loader_Axis eLoaderAxis, enum_MoveDir eDir)
{
	CString strAxisName = _T(""), Str = _T("");;
	enum_Axis eAxis = GetAxisNo(eLoaderAxis, &strAxisName);
	double dVel = 0.0, dAccel = 0.0, dDecel = 0.0;
	BOOL bRet = FALSE;

	if (eAxis == AXIS_NONE)
		return;

	int nSpeed_Index = m_cbxSpeed[eLoaderAxis].GetCurSel();
	bRet = SharedInfo::GetManualSpeed(eAxis, (enum_AXIS_SPEED)nSpeed_Index, &dVel, &dAccel, &dDecel);
	if (bRet == FALSE)
		return;

	if (eMoveType[eLoaderAxis] != _eMOVE_TYPE_RELATIVE)
		return;

	double dMoveDist = 0.0, dMoveTargetPos = 0.0;
	CString strStep;
	m_cbxStep[eLoaderAxis].GetWindowText(strStep);
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

void CManual_Sub_Loader_Work_Pos::ManualMove_Jog(enum_Loader_Axis eLoaderAxis, enum_MoveDir eDir)
{
	CString strAxisName = _T(""), Str = _T("");;
	enum_Axis eAxis = GetAxisNo(eLoaderAxis, &strAxisName);
	double dVel = 0.0, dAccel = 0.0, dDecel = 0.0;
	BOOL bRet = FALSE;

	if (eAxis == AXIS_NONE)
		return;

	if (eMoveType[eLoaderAxis] != _eMOVE_TYPE_JOG)
		return;

	int nSpeed_Index = m_cbxSpeed[eLoaderAxis].GetCurSel();
	bRet = SharedInfo::GetManualSpeed(eAxis, (enum_AXIS_SPEED)nSpeed_Index, &dVel, &dAccel, &dDecel);
	if (bRet == FALSE)
		return;

	if (eDir == eMOVE_DIR_N)
		dVel = dVel * (-1);

	SharedInfo::m_eAxisJog = eAxis;

	Devs::m_JogMotion.JogMove(eAxis, dVel, dAccel, dDecel);
}

enum_Axis CManual_Sub_Loader_Work_Pos::GetAxisNo(enum_Loader_Axis eLoaderAxis, CString *strDiscription)
{
	CString Str = _T("");

	enum_Axis eAxis = AXIS_NONE;
	switch (eLoaderAxis)
	{
	case _eMANUAL_LOADER_AXIS_Z:				eAxis = AXIS_LOADER_Z; Str = _T("Loader Z");  break;
	case _eMANUAL_LOADER_AXIS_X:				eAxis = AXIS_LOADER_X; Str = _T("Loader X");  break;
	//case _eMANUAL_LOADER_AXIS_SUB_ZL:			eAxis = AXIS_LOADER_ZL; Str = _T("Loader Sub ZL");  break;
	//case _eMANUAL_LOADER_AXIS_SUB_ZR:			eAxis = AXIS_LOADER_ZR; Str = _T("Loader Sub ZR");  break;
	}

	*strDiscription = Str;

	return eAxis;
}



BOOL CManual_Sub_Loader_Work_Pos::PreTranslateMessage(MSG* pMsg)
{
	int i = 0;
	switch (pMsg->message)
	{
	case WM_LBUTTONDOWN:
	{
		for (i = 0; i < _eMANUAL_LOADER_AXIS_MAX-1; i++)
		{
			if (pMsg->hwnd == m_btnMoveMinus[i].GetSafeHwnd() && eMoveType[i] == _eMOVE_TYPE_JOG)
			{
				ManualMove_Jog((enum_Loader_Axis)i, eMOVE_DIR_N);
				//Total_Msg(_T("Jog Start Minus"));
				break;
			}
			else if (pMsg->hwnd == m_btnMovePlus[i].GetSafeHwnd() && eMoveType[i] == _eMOVE_TYPE_JOG)
			{
				ManualMove_Jog((enum_Loader_Axis)i, eMOVE_DIR_P);
				//Total_Msg(_T("Jog Start Plus"));
				break;
			}
		}
		break;
	}
	case WM_LBUTTONUP:
	{
		for (i = 0; i < _eMANUAL_LOADER_AXIS_MAX-1; i++)
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
void CManual_Sub_Loader_Work_Pos::OnBnClickedCheckManualSubLoaderWorkJogLoaderZ()
{
	ChangeMoveType(_eMANUAL_LOADER_AXIS_Z, _eMOVE_TYPE_JOG);
}
void CManual_Sub_Loader_Work_Pos::OnBnClickedCheckManualSubLoaderWorkJogLoaderX()
{
	ChangeMoveType(_eMANUAL_LOADER_AXIS_X, _eMOVE_TYPE_JOG);
}
//21.02.05 SJC
void CManual_Sub_Loader_Work_Pos::OnBnClickedCheckManualSubLoaderWorkJogLoaderZ2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ChangeMoveType(_eMANUAL_LOADER_AXIS_SUB_ZL, _eMOVE_TYPE_JOG);
}

void CManual_Sub_Loader_Work_Pos::OnBnClickedCheckManualSubLoaderWorkJogLoaderZ3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ChangeMoveType(_eMANUAL_LOADER_AXIS_SUB_ZR, _eMOVE_TYPE_JOG);
}

#pragma endregion

#pragma region //Relative Button
void CManual_Sub_Loader_Work_Pos::OnBnClickedCheckManualSubLoaderWorkRelativeLoaderZ()
{
	ChangeMoveType(_eMANUAL_LOADER_AXIS_Z, _eMOVE_TYPE_RELATIVE);
}
void CManual_Sub_Loader_Work_Pos::OnBnClickedCheckManualSubLoaderWorkRelativeLoaderX()
{
	ChangeMoveType(_eMANUAL_LOADER_AXIS_X, _eMOVE_TYPE_RELATIVE);
}
void CManual_Sub_Loader_Work_Pos::OnBnClickedCheckManualSubLoaderWorkRelativeLoaderZ2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ChangeMoveType(_eMANUAL_LOADER_AXIS_SUB_ZL, _eMOVE_TYPE_RELATIVE);
}

void CManual_Sub_Loader_Work_Pos::OnBnClickedCheckManualSubLoaderWorkRelativeLoaderZ3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ChangeMoveType(_eMANUAL_LOADER_AXIS_SUB_ZR, _eMOVE_TYPE_RELATIVE);
}

#pragma endregion

#pragma region // - Button
void CManual_Sub_Loader_Work_Pos::OnBnClickedButtonManualSubLoaderWorkCcwLoaderZ()
{
	enum_Loader_Axis eLoaderAxis = _eMANUAL_LOADER_AXIS_Z;
	if (eMoveType[eLoaderAxis] == _eMOVE_TYPE_RELATIVE)
		ManualMove_Relative(eLoaderAxis, eMOVE_DIR_N);
}
void CManual_Sub_Loader_Work_Pos::OnBnClickedButtonManualSubLoaderWorkCcwLoaderX()
{
	enum_Loader_Axis eLoaderAxis = _eMANUAL_LOADER_AXIS_X;
	if (eMoveType[eLoaderAxis] == _eMOVE_TYPE_RELATIVE)
		ManualMove_Relative(eLoaderAxis, eMOVE_DIR_N);
}
void CManual_Sub_Loader_Work_Pos::OnBnClickedButtonManualSubLoaderWorkCcwLoaderZ2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	enum_Loader_Axis eLoaderAxis = _eMANUAL_LOADER_AXIS_SUB_ZL;
	if (eMoveType[eLoaderAxis] == _eMOVE_TYPE_RELATIVE)
		ManualMove_Relative(eLoaderAxis, eMOVE_DIR_N);
}

void CManual_Sub_Loader_Work_Pos::OnBnClickedButtonManualSubLoaderWorkCcwLoaderZ3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	enum_Loader_Axis eLoaderAxis = _eMANUAL_LOADER_AXIS_SUB_ZR;
	if (eMoveType[eLoaderAxis] == _eMOVE_TYPE_RELATIVE)
		ManualMove_Relative(eLoaderAxis, eMOVE_DIR_N);
}
#pragma endregion

#pragma region // + Button
void CManual_Sub_Loader_Work_Pos::OnBnClickedButtonManualSubLoaderWorkCwLoaderZ()
{
	enum_Loader_Axis eLoaderAxis = _eMANUAL_LOADER_AXIS_Z;
	if (eMoveType[eLoaderAxis] == _eMOVE_TYPE_RELATIVE)
		ManualMove_Relative(eLoaderAxis, eMOVE_DIR_P);
}
void CManual_Sub_Loader_Work_Pos::OnBnClickedButtonManualSubLoaderWorkCwLoaderX()
{
	enum_Loader_Axis eLoaderAxis = _eMANUAL_LOADER_AXIS_X;
	if (eMoveType[eLoaderAxis] == _eMOVE_TYPE_RELATIVE)
		ManualMove_Relative(eLoaderAxis, eMOVE_DIR_P);
}
void CManual_Sub_Loader_Work_Pos::OnBnClickedButtonManualSubLoaderWorkCwLoaderZ2()
{
	enum_Loader_Axis eLoaderAxis = _eMANUAL_LOADER_AXIS_SUB_ZL;
	if (eMoveType[eLoaderAxis] == _eMOVE_TYPE_RELATIVE)
		ManualMove_Relative(eLoaderAxis, eMOVE_DIR_P);
}
void CManual_Sub_Loader_Work_Pos::OnBnClickedButtonManualSubLoaderWorkCwLoaderZ3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	enum_Loader_Axis eLoaderAxis = _eMANUAL_LOADER_AXIS_SUB_ZR;
	if (eMoveType[eLoaderAxis] == _eMOVE_TYPE_RELATIVE)
		ManualMove_Relative(eLoaderAxis, eMOVE_DIR_P);
}
#pragma endregion










