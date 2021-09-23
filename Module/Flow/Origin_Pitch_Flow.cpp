#include "stdafx.h"
#include "Origin_Pitch_Flow.h"
#include "Vision/Devs.h"
#include "VisionAgentDlg.h"

COrigin_Pitch_Flow::COrigin_Pitch_Flow()
{
}


COrigin_Pitch_Flow::~COrigin_Pitch_Flow()
{
}

BOOL COrigin_Pitch_Flow::InitProcess()
{
	m_StateComplete = NULL;
	m_FlowFinish = TRUE;
	m_bTerminate = FALSE;
	m_bFlowDone = TRUE;

	//SetProcessLog(Process_Msg);
	//SetAlarmLog(LogMsg_Alarm);

	hHandle = CreateEvent(NULL, TRUE, FALSE, NULL);
	SetHandle(hHandle);
	pThread = AfxBeginThread(ThreadFunction, this);
	return TRUE;
}
BOOL COrigin_Pitch_Flow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eORIGIN_PITCH_FLOW_IDLE, _T("_eORIGIN_PITCH_FLOW_IDLE"));

	do
	{
		Sleep(10);
	} while (IsTerminate() == 0);

	if (hHandle != NULL)
	{
		CloseHandle(hHandle);
	}

	return TRUE;
}
BOOL COrigin_Pitch_Flow::Start()
{
	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(_eORIGIN_PITCH_FLOW_START, _T("_eORIGIN_PITCH_FLOW_START"));
	return TRUE;
}
BOOL COrigin_Pitch_Flow::Stop()
{
	m_bStopBit = TRUE;
	SetStop(); //!!
	return TRUE;
}
UINT COrigin_Pitch_Flow::ThreadFunction(LPVOID lpParam)
{
	COrigin_Pitch_Flow* pFlow = NULL;

	pFlow = (COrigin_Pitch_Flow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}
VOID COrigin_Pitch_Flow::ThreadFunctionEntry(VOID)
{
	DWORD	dwResult = 0;
	double	dStrt_Time = GetTickCount();
	double	dEnd_Time = GetTickCount();
	double	dWait_Time = GetTickCount();
	int		nWork_Mask_Mode = -1;
	int		nWork_Mask_Index = -1;
	BOOL	bComplete_Step = FALSE;
	CVisionAgentDlg *pMain = (CVisionAgentDlg*)AfxGetMainWnd();
	CString Str = _T("");
	BOOL bResult = TRUE;
	int i = 0;

	double dVel = 3.0;
	double dAcc = 10.0;
	double dDec = 10.0;
	BOOL bHomeStatus_L = FALSE, bHomeStatus_R = FALSE;
	
	int nWaitPosCnt = 0;

	while (m_FlowFinish)
	{
		WaitForSingleObject(hHandle, INFINITE);
		ResetEvent(hHandle);

		if (SharedInfo::bMachineStopFlag == TRUE && m_bStopBit == FALSE)
		{
			m_bStopBit = TRUE;

			continue; //!!
		}
		if (SharedInfo::bMachineStopFlag == TRUE)
			continue;

		switch (GetCurrentTotalStep())
		{
		case _eORIGIN_PITCH_FLOW_IDLE:
		{
			break;
		}
		case _eORIGIN_PITCH_FLOW_START:
			for (i = 0; i < eGRIPPER_ROW_MAX; i++)
			{
				m_nAxisPitch_L[i] = REMOTE_AXIS_AJIN_GRIPPER_PITCH_L1 + i;
				m_nAxisPitch_R[i] = REMOTE_AXIS_AJIN_GRIPPER_PITCH_R1 + i;

				bLimitSignal_L[i] = FALSE;
				bLimitSignal_R[i] = FALSE;
			}
			m_nCurAxisRowIndex = eGRIPPER_ROW_MAX - 1;

			SetStep(_eORIGIN_PITCH_FLOW_INTERLOCK_CHECK, _T("_eORIGIN_PITCH_FLOW_INTERLOCK_CHECK"));
			break;

		case _eORIGIN_PITCH_FLOW_INTERLOCK_CHECK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(_eORIGIN_PITCH_FLOW_ERROR, _T("_eORIGIN_PITCH_FLOW_ERROR"));
			}
			else
			{
				SetStep(_eORIGIN_PITCH_FLOW_SERVO_OFF, _T("_eORIGIN_PITCH_FLOW_SERVO_OFF"));
			}
			break;

#pragma region //Pitch Home
		case _eORIGIN_PITCH_FLOW_SERVO_OFF:
			Devs::MotionIf.AxisSetServoOnStatus(m_nAxisPitch_L[m_nCurAxisRowIndex], FALSE);
			Sleep(30);
			Devs::MotionIf.AxisSetServoOnStatus(m_nAxisPitch_R[m_nCurAxisRowIndex], FALSE);
			Sleep(500); //!!

			SetCheckStep(_eORIGIN_PITCH_FLOW_SERVO_OFF_CHECK, _T("_eORIGIN_PITCH_FLOW_SERVO_OFF_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eORIGIN_PITCH_FLOW_SERVO_OFF_CHECK:
			if (SharedInfo::AxisServoOnStatus[m_nAxisPitch_L[m_nCurAxisRowIndex]] == TRUE && SharedInfo::AxisServoOnStatus[m_nAxisPitch_R[m_nCurAxisRowIndex]] == TRUE)
				bResult = FALSE;
			else
				bResult = TRUE;

			if (bResult == TRUE)
			{
				SetStep(_eORIGIN_PITCH_FLOW_SERVO_ON, _T("_eORIGIN_PITCH_FLOW_SERVO_ON"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eORIGIN_PITCH_FLOW_ERROR, _T("_eORIGIN_PITCH_FLOW_ERROR"));
			}
			else
			{
SetCheckStep(_eORIGIN_PITCH_FLOW_SERVO_OFF_CHECK, _T("_eORIGIN_PITCH_FLOW_SERVO_OFF_CHECK"));
			}
			break;

		case _eORIGIN_PITCH_FLOW_SERVO_ON:
			Devs::MotionIf.AxisSetServoOnStatus(m_nAxisPitch_L[m_nCurAxisRowIndex], TRUE);
			Sleep(30);
			Devs::MotionIf.AxisSetServoOnStatus(m_nAxisPitch_R[m_nCurAxisRowIndex], TRUE);
			Sleep(500); //!!

			SetCheckStep(_eORIGIN_PITCH_FLOW_SERVO_ON_CHECK, _T("_eORIGIN_PITCH_FLOW_SERVO_ON_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eORIGIN_PITCH_FLOW_SERVO_ON_CHECK:
			if (SharedInfo::AxisServoOnStatus[m_nAxisPitch_L[m_nCurAxisRowIndex]] == FALSE && SharedInfo::AxisServoOnStatus[m_nAxisPitch_R[m_nCurAxisRowIndex]] == FALSE)
				bResult = FALSE;
			else
				bResult = TRUE;

			if (bResult == TRUE)
			{
				SetStep(_eORIGIN_PITCH_FLOW_N_LIMIT_POS, _T("_eORIGIN_PITCH_FLOW_N_LIMIT_POS"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eORIGIN_PITCH_FLOW_ERROR, _T("_eORIGIN_PITCH_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eORIGIN_PITCH_FLOW_SERVO_ON_CHECK, _T("_eORIGIN_PITCH_FLOW_SERVO_ON_CHECK"));
			}
			break;

		case _eORIGIN_PITCH_FLOW_N_LIMIT_POS:
			bLimitSignal_L[m_nCurAxisRowIndex] = FALSE;
			bLimitSignal_R[m_nCurAxisRowIndex] = FALSE;

			Str.Format(_T("Pitch L%d, R%d Move To N_Limit Pos Start"), m_nCurAxisRowIndex + 1, m_nCurAxisRowIndex + 1);
			Total_Msg(Str);

			Devs::MotionIf.AxisVelMove(m_nAxisPitch_L[m_nCurAxisRowIndex], -dVel, dAcc, dDec);
			Sleep(30); //!!
			Devs::MotionIf.AxisVelMove(m_nAxisPitch_R[m_nCurAxisRowIndex], -dVel, dAcc, dDec);

			SetCheckStep(_eORIGIN_PITCH_FLOW_N_LIMIT_POS_CHECK, _T("_eORIGIN_PITCH_FLOW_N_LIMIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eORIGIN_PITCH_FLOW_N_LIMIT_POS_CHECK:
			for (i = 0; i < eGRIPPER_ROW_MAX; i++)
			{
				if (bLimitSignal_L[i] == FALSE && SharedInfo::AxisNLimitSignal[m_nAxisPitch_L[i]])
				{
					bLimitSignal_L[i] = TRUE;
					Devs::MotionIf.AxisMoveStop(m_nAxisPitch_L[i], dDec * 2);

					Str.Format(_T("Pitch L%d N Limit Detect. AxisMoveStop"), i + 1);
					Total_Msg(Str);
				}
				if (bLimitSignal_R[i] == FALSE && SharedInfo::AxisNLimitSignal[m_nAxisPitch_R[i]])
				{
					bLimitSignal_R[i] = TRUE;
					Devs::MotionIf.AxisMoveStop(m_nAxisPitch_R[i], dDec * 2);

					Str.Format(_T("Pitch R%d N Limit Detect. AxisMoveStop"), i + 1);
					Total_Msg(Str);
				}
			}

			if (m_nCurAxisRowIndex > 0)
			{
				m_nCurAxisRowIndex--;

				Sleep(1000); //!!
				SetStep(_eORIGIN_PITCH_FLOW_SERVO_OFF, _T("_eORIGIN_PITCH_FLOW_SERVO_OFF"));
			}
			else
			{
				bResult = TRUE;
				for (i = 0; i < eGRIPPER_ROW_MAX; i++)
				{
					if (bLimitSignal_L[i] == FALSE || bLimitSignal_R[i] == FALSE)
					{
						bResult = FALSE;
						break;
					}
				}

				if (bResult == TRUE) //All N_Limit Pos Move Done
				{
					SetStep(_eORIGIN_PITCH_FLOW_N_LIMIT_EJECT_POS, _T("_eORIGIN_PITCH_FLOW_N_LIMIT_EJECT_POS"));
				}
				else if (IsTimeOut())
				{
					SetStep(_eORIGIN_PITCH_FLOW_ERROR, _T("_eORIGIN_PITCH_FLOW_ERROR"));
				}
				else
				{
					SetCheckStep(_eORIGIN_PITCH_FLOW_N_LIMIT_POS_CHECK, _T("_eORIGIN_PITCH_FLOW_N_LIMIT_POS_CHECK"));
				}
			}
			break;

		case _eORIGIN_PITCH_FLOW_N_LIMIT_EJECT_POS:
			m_HomeStartPos_L = SharedInfo::AxisCmdPos[m_nAxisPitch_L[m_nCurAxisRowIndex]];
			m_HomeStartPos_R = SharedInfo::AxisCmdPos[m_nAxisPitch_R[m_nCurAxisRowIndex]];

			bLimitSignal_L[m_nCurAxisRowIndex] = TRUE;
			bLimitSignal_R[m_nCurAxisRowIndex] = TRUE;

			Str.Format(_T("Pitch L%d, R%d Move To N_Limit Eject Pos Start"), m_nCurAxisRowIndex + 1, m_nCurAxisRowIndex + 1);
			Total_Msg(Str);

			Devs::MotionIf.AxisVelMove(m_nAxisPitch_L[m_nCurAxisRowIndex], dVel, dAcc, dDec);
			Sleep(30); //!!
			Devs::MotionIf.AxisVelMove(m_nAxisPitch_R[m_nCurAxisRowIndex], dVel, dAcc, dDec);

			SetCheckStep(_eORIGIN_PITCH_FLOW_N_LIMIT_EJECT_POS_CHECK, _T("_eORIGIN_PITCH_FLOW_N_LIMIT_EJECT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eORIGIN_PITCH_FLOW_N_LIMIT_EJECT_POS_CHECK:
			if (bLimitSignal_L[m_nCurAxisRowIndex] == TRUE && (SharedInfo::AxisNLimitSignal[bLimitSignal_L[m_nCurAxisRowIndex]] == 0 || fabs(m_HomeStartPos_L - SharedInfo::AxisCmdPos[bLimitSignal_L[m_nCurAxisRowIndex]]) > 1))
			{
				bLimitSignal_L[m_nCurAxisRowIndex] = FALSE;
				Devs::MotionIf.AxisMoveStop(m_nAxisPitch_L[m_nCurAxisRowIndex], dDec * 2);

				Str.Format(_T("Pitch L%d N_Limit Eject. AxisMoveStop"), m_nCurAxisRowIndex + 1);
				Total_Msg(Str);
			}
			if (bLimitSignal_R[m_nCurAxisRowIndex] == TRUE && (SharedInfo::AxisNLimitSignal[bLimitSignal_R[m_nCurAxisRowIndex]] == 0 || fabs(m_HomeStartPos_R - SharedInfo::AxisCmdPos[bLimitSignal_R[m_nCurAxisRowIndex]]) > 1))
			{
				bLimitSignal_R[m_nCurAxisRowIndex] = FALSE;
				Devs::MotionIf.AxisMoveStop(m_nAxisPitch_R[m_nCurAxisRowIndex], dDec * 2);

				Str.Format(_T("Pitch R%d N_Limit Eject. AxisMoveStop"), m_nCurAxisRowIndex + 1);
				Total_Msg(Str);
			}

			if (bLimitSignal_L[m_nCurAxisRowIndex] == FALSE && bLimitSignal_R[m_nCurAxisRowIndex] == FALSE)
			{
				Sleep(1000); //!!
				SetCheckStep(_eORIGIN_PITCH_FLOW_HOME_MOVE, _T("_eORIGIN_PITCH_FLOW_HOME_MOVE"));
			}
			else
			{
				SetCheckStep(_eORIGIN_PITCH_FLOW_N_LIMIT_EJECT_POS_CHECK, _T("_eORIGIN_PITCH_FLOW_N_LIMIT_EJECT_POS_CHECK"));
			}
			break;

		case _eORIGIN_PITCH_FLOW_HOME_MOVE:
			Str.Format(_T("Pitch L%d, R%d Move To Home Pos Start"), m_nCurAxisRowIndex + 1, m_nCurAxisRowIndex + 1);
			Total_Msg(Str);

			m_HomeStartPos_L = SharedInfo::AxisCmdPos[m_nAxisPitch_L[m_nCurAxisRowIndex]];
			Devs::MotionIf.AxisHomeStart(m_nAxisPitch_L[m_nCurAxisRowIndex]);
			Sleep(30);
			m_HomeStartPos_R = SharedInfo::AxisCmdPos[m_nAxisPitch_R[m_nCurAxisRowIndex]];
			Devs::MotionIf.AxisHomeStart(m_nAxisPitch_R[m_nCurAxisRowIndex]);
			Sleep(1000); //!!

			bHomeStatus_L = FALSE;
			bHomeStatus_R = FALSE;

			SetCheckStep(_eORIGIN_PITCH_FLOW_HOME_CHECK, _T("_eORIGIN_PITCH_FLOW_HOME_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eORIGIN_PITCH_FLOW_HOME_CHECK:
			if (bHomeStatus_L == FALSE && 
				!SharedInfo::AxisInMotionStatus[m_nAxisPitch_L[m_nCurAxisRowIndex]] && fabs(m_HomeStartPos_L - SharedInfo::AxisCmdPos[m_nAxisPitch_L[m_nCurAxisRowIndex]]) > 5 && SharedInfo::AxisHomeStatus[m_nAxisPitch_L[m_nCurAxisRowIndex]])
			{
				bHomeStatus_L = TRUE;

				Str.Format(_T("Pitch L%d Home Done"), m_nCurAxisRowIndex + 1);
				Total_Msg(Str);
			}

			if (bHomeStatus_R == FALSE &&
				!SharedInfo::AxisInMotionStatus[m_nAxisPitch_R[m_nCurAxisRowIndex]] && fabs(m_HomeStartPos_R - SharedInfo::AxisCmdPos[m_nAxisPitch_R[m_nCurAxisRowIndex]]) > 5 && SharedInfo::AxisHomeStatus[m_nAxisPitch_R[m_nCurAxisRowIndex]])
			{
				bHomeStatus_R = TRUE;

				Str.Format(_T("Pitch R%d Home Done"), m_nCurAxisRowIndex + 1);
				Total_Msg(Str);
			}

			if (bHomeStatus_L == TRUE && bHomeStatus_R == TRUE)
			{
				if (m_nCurAxisRowIndex < eGRIPPER_ROW_MAX - 1)
				{
					m_nCurAxisRowIndex++;

					SetStep(_eORIGIN_PITCH_FLOW_N_LIMIT_EJECT_POS, _T("_eORIGIN_PITCH_FLOW_N_LIMIT_EJECT_POS"));
				}
				else
				{
#if 0
					SetStep(_eORIGIN_PITCH_FLOW_WAIT_POS_MOVE, _T("_eORIGIN_PITCH_FLOW_WAIT_POS_MOVE"));
#else
					SetStep(_eORIGIN_PITCH_FLOW_DONE, _T("_eORIGIN_PITCH_FLOW_DONE"));
#endif
				}
			}
			else if (IsTimeOut())
			{
				SetStep(_eORIGIN_PITCH_FLOW_ERROR, _T("_eORIGIN_PITCH_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eORIGIN_PITCH_FLOW_HOME_CHECK, _T("_eORIGIN_PITCH_FLOW_HOME_CHECK"));
			}
			break;

		case _eORIGIN_PITCH_FLOW_WAIT_POS_MOVE:
			for (i = eGRIPPER_ROW_MAX - 1; i >= 0; i--)
			{
				Devs::m_PitchMotion.PitchLeft_WaitPos((enum_Axis)(AXIS_GRIPPER_PITCH_L1 + i));
				Sleep(30);
				Devs::m_PitchMotion.PitchRight_WaitPos((enum_Axis)(AXIS_GRIPPER_PITCH_R1 + i));
				Sleep(3000); //!!
			}

			SetStep(_eORIGIN_PITCH_FLOW_WAIT_POS_CHECK, _T("_eORIGIN_PITCH_FLOW_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eORIGIN_PITCH_FLOW_WAIT_POS_CHECK:
			nWaitPosCnt = 0;
			for (i = 0; i < eGRIPPER_ROW_MAX; i++)
			{
				if (Devs::m_PitchMotion.Is_PitchLeft_WaitPos((enum_Axis)(AXIS_GRIPPER_PITCH_L1 + i)) &&
					Devs::m_PitchMotion.Is_PitchLeft_WaitPos((enum_Axis)(AXIS_GRIPPER_PITCH_R1 + i)))
				{
					nWaitPosCnt++;
				}
			}
			if (nWaitPosCnt == eGRIPPER_ROW_MAX)
			{
				SetStep(_eORIGIN_PITCH_FLOW_DONE, _T("_eORIGIN_PITCH_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eORIGIN_PITCH_FLOW_ERROR, _T("_eORIGIN_PITCH_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eORIGIN_PITCH_FLOW_WAIT_POS_CHECK, _T("_eORIGIN_PITCH_FLOW_WAIT_POS_CHECK"));
			}
			break;
#pragma endregion

		case _eORIGIN_PITCH_FLOW_DONE:
		{
			m_bFlowDone = TRUE;
			break;
		}
		case _eORIGIN_PITCH_FLOW_STOP:
		{
			break;
		}
		default:
		{
			break;
		}
		}

		Sleep(100); //!!
	}
}

BOOL COrigin_Pitch_Flow::FlowInterlock()
{
	CString Str = _T("");
	int i = 0;

	for (i = 0; i < eGRIPPER_ROW_MAX; i++)
	{
		if (SharedInfo::GetServoOnStatus((enum_Axis)(AXIS_GRIPPER_PITCH_L1 + i)) != TRUE)
		{
			Str.Format(_T("Pitch L%d Servo On Check !!!"), i + 1);
			Total_Msg(Str);
			return FALSE;
		}
		if (SharedInfo::GetServoOnStatus((enum_Axis)(AXIS_GRIPPER_PITCH_R1 + i)) != TRUE)
		{
			Str.Format(_T("Pitch R%d Servo On Check !!!"), i + 1);
			Total_Msg(Str);
			return FALSE;
		}
	}

	return TRUE;
}
