// VisionAgentMachine_Jog_InfoDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentDlg.h"
#include "VisionAgentMachineJogDlg.h"
#include "VisionAgentMachineJogInfoDlg.h"
#include "afxdialogex.h"

#define DISPLAY_TIME	WM_USER + 1001

// CVisionAgentMachineJogInfoDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CVisionAgentMachineJogInfoDlg, CDialogEx)

CVisionAgentMachineJogInfoDlg::CVisionAgentMachineJogInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CVisionAgentMachineJogInfoDlg::IDD, pParent)
	, m_bInit(false)
{
	m_eAxis = AXIS_NONE;

	//pGantryTop = &Devs::GantryTopMotion;
	//pGantryBottom = &Devs::GantryTopMotion;
	//pMaskLoader = &Devs::MaskLoaderMotion;
	m_JogMotion = &Devs::m_JogMotion;

}

CVisionAgentMachineJogInfoDlg::~CVisionAgentMachineJogInfoDlg()
{
	
}

void CVisionAgentMachineJogInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVisionAgentMachineJogInfoDlg, CDialogEx)
	ON_BN_CLICKED(IDC_MACHINE_JOG_INFO_CLOSSE_BTN, &CVisionAgentMachineJogInfoDlg::OnBnClickedMachineJogInfoClosseBtn)
	ON_BN_CLICKED(IDC_MACHINE_JOG_INFO_SERVO_ON_BTN, &CVisionAgentMachineJogInfoDlg::OnBnClickedMachineJogInfoServoOnBtn)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_MACHINE_JOG_INFO_ALARM_BTN, &CVisionAgentMachineJogInfoDlg::OnBnClickedMachineJogInfoAlarmBtn)
	ON_BN_CLICKED(IDC_MACHINE_JOG_INFO_ORIGIN_BTN, &CVisionAgentMachineJogInfoDlg::OnBnClickedMachineJogInfoOriginBtn)
	ON_BN_CLICKED(IDC_MACHINE_JOG_INFO_STOP_BTN, &CVisionAgentMachineJogInfoDlg::OnBnClickedMachineJogInfoStopBtn)
	ON_BN_CLICKED(IDC_MACHINE_JOG_INFO_POS_MOVE_BTN, &CVisionAgentMachineJogInfoDlg::OnBnClickedMachineJogInfoPosMoveBtn)
	ON_BN_CLICKED(IDC_MACHINE_JOG_INFO_RELATIVE_MINUS_BTN, &CVisionAgentMachineJogInfoDlg::OnBnClickedMachineJogInfoRelativeMinusBtn)
	ON_BN_CLICKED(IDC_MACHINE_JOG_INFO_RELATIVE_PLUS_BTN, &CVisionAgentMachineJogInfoDlg::OnBnClickedMachineJogInfoRelativePlusBtn)
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CVisionAgentMachineJogInfoDlg 메시지 처리기입니다.

void CVisionAgentMachineJogInfoDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	if (bShow == TRUE)
	{
		//m_JogMotion.MoveCompleteCallBack(JogMoveComplete);
		SetTimer(1, 100, NULL);
	}
	else if (bShow == FALSE)
	{
		KillTimer(1);
	}
}

BOOL CVisionAgentMachineJogInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	//SetBackgroundColor(RGB(255, 255, 255));
	InitCtrl();
	InitDefaultPara();

	SetTimer(1, 100, NULL);

	CVisionAgentDlg *pVisionAgentDlg;
	pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	m_bInit = TRUE;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CVisionAgentMachineJogInfoDlg::InitCtrl()
{
	CString str;
	
	//m_EditInfoSizeX.SubclassDlgItem(IDC_VISON_AGENT_MODEL_FRAME_STAGE_EDIT_HEIGHT_Z, this);
	m_EditPosition.SubclassDlgItem(IDC_MACHINE_JOG_INFO_POSITION_EDIT, this);
	m_EditVel.SubclassDlgItem(IDC_MACHINE_JOG_INFO_VEL_EDIT, this);
	m_EditAcc.SubclassDlgItem(IDC_MACHINE_JOG_INFO_ACC_EDIT, this);
	m_EditDec.SubclassDlgItem(IDC_MACHINE_JOG_INFO_DEC_EDIT, this);
	m_EditJogVelHight.SubclassDlgItem(IDC_MACHINE_JOG_INFO_JOG_VEL_HIGH_EDIT, this);
	m_EditJogVelMid.SubclassDlgItem(IDC_MACHINE_JOG_INFO_JOG_VEL_MID_EDIT, this);
	m_EditJogVelLow.SubclassDlgItem(IDC_MACHINE_JOG_INFO_JOG_VEL_LOW_EDIT, this);

	m_stcServoOnLed.SubclassDlgItem(IDC_MACHINE_JOG_INFO_SERVO_ON_LED_STC, this);
	m_stcAlarmLed.SubclassDlgItem(IDC_MACHINE_JOG_INFO_ALARM_LED_STC, this);
	m_stcInMotionLed.SubclassDlgItem(IDC_MACHINE_JOG_INFO_INMOTION_LED_STC, this);
	m_stcHomeLed.SubclassDlgItem(IDC_MACHINE_JOG_INFO_HOME_LED_STC, this);
	m_stcLimitMinusLed.SubclassDlgItem(IDC_MACHINE_JOG_INFO_LIMIT_MINUS_LED_STC, this);
	m_stcLimitPlusLed.SubclassDlgItem(IDC_MACHINE_JOG_INFO_LIMIT_PLUS_LED_STC, this);
	m_stcHomingLed.SubclassDlgItem(IDC_MACHINE_JOG_INFO_HOMING_LED_STC, this);
	m_stcOriginLed.SubclassDlgItem(IDC_MACHINE_JOG_INFO_ORIGIN_LED_STC, this);
		
	m_ComboVelLevel.SubclassDlgItem(IDC_MACHINE_JOG_INFO_JOG_VEL_LEVEL_COMBO, this);

	m_EditPosMove.SubclassDlgItem(IDC_MACHINE_JOG_INFO_POS_MOVE_EDIT, this);
	m_EditRelativeMove.SubclassDlgItem(IDC_MACHINE_JOG_INFO_RELATIVE_MOVE_EDIT, this);

	this->SetWindowText(m_strAxis);
}

void CVisionAgentMachineJogInfoDlg::InitDefaultPara()
{
	CVisionAgentDlg *pVisionAgentDlg;
	pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	CString Str;

	Str.Format(_T("%.5f"), 0.0);

	m_EditPosition.SetWindowText(Str);
	m_EditVel.SetWindowText(Str);

	m_stcServoOnLed.SetBackgroundColor(LLTGRAY);
	m_stcAlarmLed.SetBackgroundColor(LLTGRAY);
	m_stcInMotionLed.SetBackgroundColor(LLTGRAY);
	m_stcHomeLed.SetBackgroundColor(LLTGRAY);
	m_stcLimitMinusLed.SetBackgroundColor(LLTGRAY);
	m_stcLimitPlusLed.SetBackgroundColor(LLTGRAY);
	m_stcHomingLed.SetBackgroundColor(LLTGRAY);
	m_stcOriginLed.SetBackgroundColor(LLTGRAY);

	m_ComboVelLevel.AddString(_T("LOW"));
	m_ComboVelLevel.AddString(_T("MEDIUM"));
	m_ComboVelLevel.AddString(_T("HIGH"));
	m_ComboVelLevel.SetCurSel(eAXIS_SPEED_MEDIUM);

	m_EditPosMove.SetWindowText(Str);
	m_EditRelativeMove.SetWindowText(Str);

	Str.Format(_T("%.3f"), CMachineData::m_MachineDataMotor.Info.dManualHighVel[m_eAxis]);
	m_EditJogVelHight.SetWindowText(Str);
	Str.Format(_T("%.3f"), CMachineData::m_MachineDataMotor.Info.dManualMediumVel[m_eAxis]);
	m_EditJogVelMid.SetWindowText(Str);
	Str.Format(_T("%.3f"), CMachineData::m_MachineDataMotor.Info.dManualLowVel[m_eAxis]);
	m_EditJogVelLow.SetWindowText(Str);
	Str.Format(_T("%.3f"), CMachineData::m_MachineDataMotor.Info.dAutoAccel[m_eAxis]);
	m_EditAcc.SetWindowText(Str);
	Str.Format(_T("%.3f"), CMachineData::m_MachineDataMotor.Info.dAutoDecel[m_eAxis]);
	m_EditDec.SetWindowText(Str);
}


void CVisionAgentMachineJogInfoDlg::ControlsEnable(BOOL bEnable)
{
	m_ComboVelLevel.EnableWindow(bEnable);

	m_EditPosMove.EnableWindow(bEnable);
	m_EditRelativeMove.EnableWindow(bEnable);
	GetDlgItem(IDC_MACHINE_JOG_INFO_JOG_MINUS_BTN)->EnableWindow(bEnable);
	GetDlgItem(IDC_MACHINE_JOG_INFO_JOG_PLUS_BTN)->EnableWindow(bEnable);
	GetDlgItem(IDC_MACHINE_JOG_INFO_POS_MOVE_BTN)->EnableWindow(bEnable);
	GetDlgItem(IDC_MACHINE_JOG_INFO_RELATIVE_MINUS_BTN)->EnableWindow(bEnable);
	GetDlgItem(IDC_MACHINE_JOG_INFO_RELATIVE_PLUS_BTN)->EnableWindow(bEnable);
}


void CVisionAgentMachineJogInfoDlg::OnBnClickedMachineJogInfoClosseBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnCancel();
}


void CVisionAgentMachineJogInfoDlg::OnBnClickedMachineJogInfoServoOnBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int nJogVelLevel;
	int nStatus;
	int nAxisType = -1, nAxisNo = -1;
	CString str;
	int nRet;
	m_EditRelativeMove.GetWindowText(str);
	nJogVelLevel = m_ComboVelLevel.GetCurSel();

	SharedInfo::GetActualAxisNoByEnumAxis(m_eAxis, &nAxisType, &nAxisNo);

	switch (nAxisType)
	{
	case AXIS_TYPE_DIRECT_AJIN:
		nStatus = SharedInfo::GetServoOnStatus(m_eAxis);
		if (nStatus == 0)
		{
			nRet = AfxMessageBox(_T("Servo On?"), MB_OKCANCEL);
			if (nRet == IDNO)	return;
		}
		else
		{
			nRet = AfxMessageBox(_T("Servo Off?"), MB_OKCANCEL);
			if (nRet == IDNO)	return;
		}
		//AxmSignalServoOn(nAxisNo, !nStatus);
		break;
	case AXIS_TYPE_REMOTE_UMAC:
		nStatus = SharedInfo::GetServoOnStatus(m_eAxis);
		if (nStatus == 0)
		{
			nRet = AfxMessageBox(_T("Servo On?"), MB_OKCANCEL);
			if (nRet == IDNO)	return;
		}
		else
		{
			nRet = AfxMessageBox(_T("Servo Off?"), MB_OKCANCEL);
			if (nRet == IDNO)	return;
		}
		//Devs::SharedInfo.UmacSetServoOnStatus(nAxisNo, !nStatus);
		break;
	case AXIS_TYPE_REMOTE_AJIN:
		nStatus = SharedInfo::GetServoOnStatus(m_eAxis);
		if (nStatus == 0)
		{
			nRet = AfxMessageBox(_T("Servo On?"), MB_OKCANCEL);
			if (nRet == IDNO)	return;
		}
		else
		{
			nRet = AfxMessageBox(_T("Servo Off?"), MB_OKCANCEL);
			if (nRet == IDNO)	return;
		}
		//Devs::SharedInfo.AxisSetServoOnStatus(nAxisNo, !nStatus);
		break;
	}

}

//Alarm
void CVisionAgentMachineJogInfoDlg::OnBnClickedMachineJogInfoAlarmBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisionAgentDlg *pVisionAgentDlg;
	pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	m_JogMotion->AlarmReset(m_eAxis);

	//int nAxisType = -1, nAxisNo = -1, nStatus;
	//if (!SharedInfo::GetActualAxisNoByEnumAxis(m_nAxis, &nAxisType, &nAxisNo)) return;
	//if (nAxisType == AXIS_TYPE_DIRECT_AJIN)
	//{
	//	nStatus = pVisionAgentDlg->m_nDirectAxisAjinAlarmStatus[nAxisNo];
	//	AxmSignalServoAlarmReset(nAxisNo,! nStatus);
	//	Sleep(100);
	//	AxmSignalServoAlarmReset(nAxisNo, nStatus);
	//}
	//else if (nAxisType == AXIS_TYPE_REMOTE_UMAC)
	//{
	//	nStatus = pVisionAgentDlg->m_nRemoteAxisUmacAlarmStatus[nAxisNo];
	//	//Devs::SharedInfo.UmacSetAlarmClear(nAxisNo, !nStatus);
	//	Sleep(100);
	//	//Devs::SharedInfo.UmacSetAlarmClear(nAxisNo, nStatus);
	//}
	//else if (nAxisType == AXIS_TYPE_REMOTE_AJIN)
	//{
	//	nStatus = pVisionAgentDlg->m_nRemoteAxisAjinAlarmStatus[nAxisNo];
	//	//Devs::SharedInfo.AxisSetAlarmClear(nAxisNo, !nStatus);
	//	Sleep(100);
	//	//Devs::SharedInfo.AxisSetAlarmClear(nAxisNo, nStatus);
	//}
}

//Origin
void CVisionAgentMachineJogInfoDlg::OnBnClickedMachineJogInfoOriginBtn()
{
	int nJogVelLevel;
	int nAxisType = -1, nAxisNo = -1;
	CString Str;

	m_EditRelativeMove.GetWindowText(Str);
	nJogVelLevel = m_ComboVelLevel.GetCurSel();

	Str.Format(_T("%s Origin Start?"), m_strAxis);
	int nResult = AfxMessageBox(Str, MB_OKCANCEL);
	if (nResult == IDOK)
	{
		m_JogMotion->OriginStart(m_eAxis);
	}
}


void CVisionAgentMachineJogInfoDlg::OnBnClickedMachineJogInfoStopBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nJogVelLevel;
	int nAxisType = -1, nAxisNo = -1;
	CString str;

	m_EditRelativeMove.GetWindowText(str);
	nJogVelLevel = m_ComboVelLevel.GetCurSel();

	//Devs::m_JogMotion.JogStop(SharedInfo::m_nAxisJog);
	//SharedInfo::m_nAxisJog = AXIS_NONE;

	SharedInfo::GetActualAxisNoByEnumAxis(m_eAxis, &nAxisType, &nAxisNo);
	switch (nAxisType)
	{
	case AXIS_TYPE_DIRECT_AJIN:
		AxmMoveStop(nAxisNo, CMachineData::m_MachineDataMotor.Info.dAutoDecel[m_eAxis]);
		break;

	case AXIS_TYPE_REMOTE_UMAC:
		Devs::MotionIf.UmacMoveStop(nAxisNo, CMachineData::m_MachineDataMotor.Info.dAutoDecel[m_eAxis]);
		break;
	case AXIS_TYPE_REMOTE_AJIN:
		Devs::MotionIf.AxisMoveStop(nAxisNo, CMachineData::m_MachineDataMotor.Info.dAutoDecel[m_eAxis]);
		break;
	}
	//CVisionAgentDlg *pVisionAgentDlg;
	//pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	//int nAxisNo = m_nAxisNo;
	//double dUvwDecel[3] = { 0.0, 0.0, 0.0 };
	//double dDecel = pVisionAgentDlg->m_dJogSpeed[m_ComboJogSpeed.GetCurSel()] * 2.0;
	//dUvwDecel[0] = dDecel;
	//dUvwDecel[1] = dDecel;
	//dUvwDecel[2] = dDecel;
	//if (m_bMotionControlFlag == MOTION_CONTROL_AJIN)
	//	//Devs::SharedInfo.AxisMoveStop(nAxisNo, dDecel);
	//else if (m_bMotionControlFlag == MOTION_CONTROL_AJIN_VISION)
	//	AxmMoveSStop(nAxisNo);
	//if (m_bMotionControlFlag == MOTION_CONTROL_UVW)
	//	//Devs::SharedInfo.UvwMoveStop(nAxisNo, dUvwDecel);
}

BOOL CVisionAgentMachineJogInfoDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CVisionAgentDlg *pVisionAgentDlg;
	pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	int nAxisType = -1, nAxisNo = -1;
	enum_AXIS_SPEED eJogVelLevel;
	double dJogVel = 0, dAcc = 0, dDec = 0;

	if (SharedInfo::GetActualAxisNoByEnumAxis(m_eAxis, &nAxisType, &nAxisNo))
	{
#if 1
		eJogVelLevel = (enum_AXIS_SPEED)m_ComboVelLevel.GetCurSel();
		SharedInfo::GetManualSpeed(m_eAxis, (enum_AXIS_SPEED)eJogVelLevel, &dJogVel, &dAcc, &dDec); //KJT 20210424

		switch (pMsg->message)
		{
		case WM_LBUTTONDOWN:
		{
			if (pMsg->hwnd == GetDlgItem(IDC_MACHINE_JOG_INFO_JOG_MINUS_BTN)->GetSafeHwnd())
			{
				if (nAxisType == AXIS_TYPE_REMOTE_AJIN)
				{
					Devs::MotionIf.AxisVelMove(nAxisNo, -dJogVel, dAcc, dDec);
				}
				else if (nAxisType == AXIS_TYPE_DIRECT_AJIN)
				{
					AxmMoveVel(nAxisNo, -dJogVel, dAcc, dDec);
				}
				else if (nAxisType == AXIS_TYPE_REMOTE_UMAC)
				{
					Devs::MotionIf.UmacVelMove(nAxisNo, -dJogVel, dAcc, dDec);
				}
			}
			else if (pMsg->hwnd == GetDlgItem(IDC_MACHINE_JOG_INFO_JOG_PLUS_BTN)->GetSafeHwnd())
			{
				if (nAxisType == AXIS_TYPE_REMOTE_AJIN)
				{
					Devs::MotionIf.AxisVelMove(nAxisNo, dJogVel, dAcc, dDec);
				}
				else if (nAxisType == AXIS_TYPE_DIRECT_AJIN)
				{
					AxmMoveVel(nAxisNo, dJogVel, dAcc, dDec);
				}
				else if (nAxisType == AXIS_TYPE_REMOTE_UMAC)
				{
					Devs::MotionIf.UmacVelMove(nAxisNo, dJogVel, dAcc, dDec);
				}
			}
			break;
		}
		case WM_LBUTTONUP:
		{
			if (pMsg->hwnd == GetDlgItem(IDC_MACHINE_JOG_INFO_JOG_MINUS_BTN)->GetSafeHwnd() || pMsg->hwnd == GetDlgItem(IDC_MACHINE_JOG_INFO_JOG_PLUS_BTN)->GetSafeHwnd())
			{
				if (nAxisType == AXIS_TYPE_REMOTE_AJIN)
				{
					Devs::MotionIf.AxisMoveStop(nAxisNo, dDec);
				}
				else if (nAxisType == AXIS_TYPE_DIRECT_AJIN)
				{
					AxmMoveSStop(nAxisNo);
				}
				else if (nAxisType == AXIS_TYPE_REMOTE_UMAC)
				{
					Devs::MotionIf.UmacMoveStop(nAxisNo, dDec);
				}
			}
			break;
		}
		}
#endif
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CVisionAgentMachineJogInfoDlg::OnBnClickedMachineJogInfoPosMoveBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisionAgentDlg *pVisionAgentDlg;
	pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	enum_AXIS_SPEED eJogVelLevel;
	int nAxisType = -1, nAxisNo = -1;
	double dVel = 1.0, dAccel = 1.0, dDecel = 1.0, dTargetPos = 0.0;
	CString Str = _T("");
	BOOL bRtn = FALSE;

	m_EditRelativeMove.GetWindowText(Str);
	dTargetPos = _wtoi(Str);

	eJogVelLevel = (enum_AXIS_SPEED)m_ComboVelLevel.GetCurSel();
	SharedInfo::GetManualSpeed(m_eAxis, (enum_AXIS_SPEED)eJogVelLevel, &dVel, &dAccel, &dDecel); //KJT 20210424

	if (m_eAxis == AXIS_GANTRY_X && m_JogMotion->m_nWithMoveBackLightX == 1)
	{
		if (SharedInfo::GetServoOnStatus(m_eAxis) == FALSE)
		{
			Str.Format(_T("%s Servo Off !!"), m_strAxis);
			AfxMessageBox(Str);
			return;
		}
}
	else if (SharedInfo::GetServoOnStatus(m_eAxis) == FALSE)
	{
		Str.Format(_T("%s Servo Off !!"), m_strAxis);
		AfxMessageBox(Str);
		return;
	}

	Str.Format(_T("%s Abs Move To Pos:%.5f Start?"), m_strAxis, dTargetPos);
	int nResult = AfxMessageBox(Str, MB_OKCANCEL);
	if (nResult == IDOK)
	{
#pragma region
		if (CModelData::m_InspectionPara.Info.bMappingDataUse)
		{
			double dPosPrevX = 0.0, dPosPrevY = 0.0, dPosMapX = 0.0, dPosMapY = 0.0;
			if (m_eAxis == AXIS_GANTRY_X)
			{
				dPosPrevX = dPosMapX = dTargetPos;
				dPosPrevY = dPosMapY = SharedInfo::GetActPos(AXIS_GANTRY_Y1);
				Devs::m_MappingProc.GetGlassMapping_CalibPosXY(eMAPPING_ID_10X, &dTargetPos, &dPosMapY);
				Str.Format(_T("Mapping Data X:%.5f, Y:%.5f => X:%.5f, Y:%.5f"), dPosPrevX, dPosPrevY, dTargetPos, dPosMapY);
				Total_Msg(Str);
			}
			else if (m_eAxis == AXIS_GANTRY_Y1)
			{
				dPosPrevX = dPosMapX = SharedInfo::GetCmdPos(AXIS_GANTRY_X);
				dPosPrevY = dPosMapY = dTargetPos;
				Devs::m_MappingProc.GetGlassMapping_CalibPosXY(eMAPPING_ID_10X, &dPosMapX, &dTargetPos);
				Str.Format(_T("Mapping Data X:%.5f, Y:%.5f => X:%.5f, Y:%.5f"), dPosPrevX, dPosPrevY, dPosMapX, dTargetPos);
				Total_Msg(Str);
			}
		}
#pragma endregion

		if (m_eAxis == AXIS_GANTRY_X)
		{
			double dBackLightOffset = CSystemData::m_Coordinate.Info.dOffsetReview10xToAoi_X;
			if (m_JogMotion->m_bWithMoveAOICameraX == TRUE)
			{
				bRtn = m_JogMotion->AbsMove(m_eAxis, dTargetPos, dVel, dAccel, dDecel, m_JogMotion->m_nWithMoveBackLightX, dBackLightOffset);
				if (m_JogMotion->m_nWithMoveBackLightX)
					Str.Format(_T("Gantry X Abs Move (TargetPos:%.5f, Vel:%.1f, Accel:%.1f, Decel:%.1f, BackLightX:%.5f"), dTargetPos, dVel, dAccel, dDecel, dTargetPos + dBackLightOffset);
				else
					Str.Format(_T("Gantry X Abs Move (TargetPos:%.5f, Vel:%.1f, Accel:%.1f, Decel:%.1f"), dTargetPos, dVel, dAccel, dDecel);
			}
			else
			{
				bRtn = m_JogMotion->AbsMove(m_eAxis, dTargetPos, dVel, dAccel, dDecel, m_JogMotion->m_nWithMoveBackLightX);
				if (m_JogMotion->m_nWithMoveBackLightX)
					Str.Format(_T("Gantry X Abs Move (TargetPos:%.5f, Vel:%.1f, Accel:%.1f, Decel:%.1f, BackLightX:%.5f"), dTargetPos, dVel, dAccel, dDecel, dTargetPos);
				else
					Str.Format(_T("Gantry X Abs Move (TargetPos:%.5f, Vel:%.1f, Accel:%.1f, Decel:%.1f"), dTargetPos, dVel, dAccel, dDecel);
			}
		}
		else
		{
			bRtn = m_JogMotion->AbsMove(m_eAxis, dTargetPos, dVel, dAccel, dDecel);
			Str.Format(_T("%s Abs Move (TargetPos:%.5f, Vel:%.1f, Accel:%.1f, Decel:%.1f"), m_strAxis, dTargetPos, dVel, dAccel, dDecel);
		}
		if (bRtn == TRUE)
			Total_Msg(Str);
	}

}


void CVisionAgentMachineJogInfoDlg::OnBnClickedMachineJogInfoRelativeMinusBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	enum_AXIS_SPEED eJogVelLevel;
	int nAxisType = -1, nAxisNo = -1;
	double dVel = 1.0, dAccel = 1.0, dDecel = 1.0, dDelta = 0.0;
	CString Str = _T("");

	m_EditRelativeMove.GetWindowText(Str);
	dDelta = _wtoi(Str);

	eJogVelLevel = (enum_AXIS_SPEED)m_ComboVelLevel.GetCurSel();
	SharedInfo::GetManualSpeed(m_eAxis, (enum_AXIS_SPEED)eJogVelLevel, &dVel, &dAccel, &dDecel); //KJT 20210424

	if (m_eAxis == AXIS_GANTRY_X && m_JogMotion->m_nWithMoveBackLightX == 1)
	{
		if (SharedInfo::GetServoOnStatus(m_eAxis) == FALSE)
		{
			Str.Format(_T("%s Servo Off !!"), m_strAxis);
			AfxMessageBox(Str);
			return;
		}
	}
	else if (SharedInfo::GetServoOnStatus(m_eAxis) == FALSE)
	{
		Str.Format(_T("%s Servo Off !!"), m_strAxis);
		AfxMessageBox(Str);
		return;
	}

	Str.Format(_T("%s Relative Move -Dist:%.5f Start?"), m_strAxis, dDelta); //KJT 20200812
	int nResult = AfxMessageBox(Str, MB_OKCANCEL);
	if (nResult == IDOK)
	{
		if (m_eAxis == AXIS_GANTRY_X)
		{
			double dBackLightOffset = CSystemData::m_Coordinate.Info.dOffsetReview10xToAoi_X;
			if (m_JogMotion->m_bWithMoveAOICameraX == TRUE)
				m_JogMotion->RelMove((enum_Axis)m_eAxis, -dDelta, dVel, dAccel, dDecel, m_JogMotion->m_nWithMoveBackLightX, dBackLightOffset);
			else
				m_JogMotion->RelMove((enum_Axis)m_eAxis, -dDelta, dVel, dAccel, dDecel, m_JogMotion->m_nWithMoveBackLightX);
		}
		else
			m_JogMotion->RelMove((enum_Axis)m_eAxis, -dDelta, dVel, dAccel, dDecel);
	}
	
}


void CVisionAgentMachineJogInfoDlg::OnBnClickedMachineJogInfoRelativePlusBtn()   
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisionAgentDlg *pVisionAgentDlg;
	pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	enum_AXIS_SPEED eJogVelLevel;
	int nAxisType = -1, nAxisNo = -1;
	double dVel = 1.0, dAccel = 1.0, dDecel = 1.0, dDelta = 0.0;
	CString Str = _T("");

	m_EditRelativeMove.GetWindowText(Str);
	dDelta = _wtoi(Str);

	eJogVelLevel = (enum_AXIS_SPEED)m_ComboVelLevel.GetCurSel();
	SharedInfo::GetManualSpeed(m_eAxis, (enum_AXIS_SPEED)eJogVelLevel, &dVel, &dAccel, &dDecel); //KJT 20210424

	if (m_eAxis == AXIS_GANTRY_X && m_JogMotion->m_nWithMoveBackLightX == 1)
	{
		if (SharedInfo::GetServoOnStatus(m_eAxis) == FALSE)
		{
			Str.Format(_T("%s Servo Off !!"), m_strAxis);
			AfxMessageBox(Str);
			return;
		}
	}
	else if (SharedInfo::GetServoOnStatus(m_eAxis) == FALSE)
	{
		Str.Format(_T("%s Servo Off !!"), m_strAxis);
		AfxMessageBox(Str);
		return;
	}

	Str.Format(_T("%s Relative Move +Dist:%.5f Start?"), m_strAxis, dDelta); //KJT 20200812
	int nResult = AfxMessageBox(Str, MB_OKCANCEL);
	if (nResult == IDOK)
	{
		if (m_eAxis == AXIS_GANTRY_X)
		{
			double dBackLightOffset = CSystemData::m_Coordinate.Info.dOffsetReview10xToAoi_X;
			if (m_JogMotion->m_bWithMoveAOICameraX == TRUE)
				m_JogMotion->RelMove(m_eAxis, dDelta, dVel, dAccel, dDecel, m_JogMotion->m_nWithMoveBackLightX, dBackLightOffset);
			else
				m_JogMotion->RelMove(m_eAxis, dDelta, dVel, dAccel, dDecel, m_JogMotion->m_nWithMoveBackLightX);
		}
		else
			m_JogMotion->RelMove(m_eAxis, dDelta, dVel, dAccel, dDecel);

		Str.Format(_T("%s RelMove Plus %.5f"), m_strAxis, dDelta);
		Total_Msg(Str);
	}
}


void CVisionAgentMachineJogInfoDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CVisionAgentDlg *pVisionAgentDlg;
	pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	//int i, nAxisNo, nDInputNo, nDOutputNo, nStatus;
	int  nAxisType = -1, nAxisNo =-1;
	//int nAInputNo, nStatus;
	int nHomeSignal, nHomeStatus, nPLimitSignal, nNLimitSignal, nServoOnStatus, nAlarmStatus;
	bool bBusy = false;
	double dPos = 0.0, dVel;
	double dCncVel = 0.0, dCncAcc = 0.0, dCncDec = 0.0;
	double dJogVel = 0.0, dJogAcc = 0.0, dJogDec = 0.0; 
	CString Str;

	nHomeSignal = 0;
	nHomeStatus = 0;
	nNLimitSignal = 0;
	nPLimitSignal = 0;
	nAlarmStatus = 0;
	nServoOnStatus = 0;
	
	if (nIDEvent == 1)
	{
		if (IsWindowVisible())
		{	

			dPos			= SharedInfo::GetCmdPos(m_eAxis);
			dVel			= SharedInfo::GetCmdVel(m_eAxis);
			nHomeSignal		= SharedInfo::GetHomeSignal(m_eAxis);
			nHomeStatus		= SharedInfo::GetHomeStatus(m_eAxis);// pVisionAgentDlg->m_nDirectAxisAjinHomeStatus[nAxisNo];
			nPLimitSignal	= SharedInfo::GetPLimitSignal(m_eAxis); //pVisionAgentDlg->m_nDirectAxisAjinPLimitSignal[nAxisNo];
			nNLimitSignal	= SharedInfo::GetNLimitSignal(m_eAxis); //pVisionAgentDlg->m_nDirectAxisAjinNLimitSignal[nAxisNo];
			nServoOnStatus	= SharedInfo::GetServoOnStatus(m_eAxis); //pVisionAgentDlg->m_nDirectAxisAjinServoOnStatus[nAxisNo];
			nAlarmStatus	= SharedInfo::GetAlarmStatus(m_eAxis);  //pVisionAgentDlg->m_nDirectAxisAjinAlarmStatus[nAxisNo];
			bBusy = SharedInfo::GetInMotion(m_eAxis);

			nHomeSignal == 1 ? m_stcHomeLed.SetBackgroundColor(GREEN) : m_stcHomeLed.SetBackgroundColor(DKGRAY);
			nHomeStatus == 1 ? m_stcOriginLed.SetBackgroundColor(GREEN) : m_stcOriginLed.SetBackgroundColor(DKGRAY); 

			nNLimitSignal == 1 ? m_stcLimitMinusLed.SetBackgroundColor(GREEN) : m_stcLimitMinusLed.SetBackgroundColor(DKGRAY);
			nPLimitSignal == 1 ? m_stcLimitPlusLed.SetBackgroundColor(GREEN) : m_stcLimitPlusLed.SetBackgroundColor(DKGRAY);
			nServoOnStatus == 1 ? m_stcServoOnLed.SetBackgroundColor(GREEN) : m_stcServoOnLed.SetBackgroundColor(DKGRAY);
			nAlarmStatus == 1 ? m_stcAlarmLed.SetBackgroundColor(GREEN) : m_stcAlarmLed.SetBackgroundColor(DKGRAY);
			bBusy == true ? m_stcInMotionLed.SetBackgroundColor(GREEN) : m_stcInMotionLed.SetBackgroundColor(LLTGRAY);

			Str.Format(_T("%.5f"), dPos);
			m_EditPosition.SetWindowText(Str);

			Str.Format(_T("%.5f"), dVel);
			m_EditVel.SetWindowText(Str);
		}
	}
	
	CDialogEx::OnTimer(nIDEvent);
}

