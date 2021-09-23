#include "stdafx.h"
#include "Origin_Stretch_Flow.h"
#include "Vision/Devs.h"
#include "VisionAgentDlg.h"

COrigin_Stretch_Flow::COrigin_Stretch_Flow()
{
}


COrigin_Stretch_Flow::~COrigin_Stretch_Flow()
{
}

BOOL COrigin_Stretch_Flow::InitProcess()
{
	m_StateComplete = NULL;
	m_FlowFinish = TRUE;
	m_bTerminate = FALSE;
	m_bFlowDone = TRUE;

	//SetProcessLog(Process_Msg);
	//SetAlarmLog(Alarm_Msg);

	hHandle = CreateEvent(NULL, TRUE, FALSE, NULL);
	SetHandle(hHandle);
	pThread = AfxBeginThread(ThreadFunction, this);
	return TRUE;
}
BOOL COrigin_Stretch_Flow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eORIGIN_STRETCH_FLOW_IDLE, _T("_eORIGIN_STRETCH_FLOW_IDLE"));

	if (hHandle != NULL)
	{
		CloseHandle(hHandle);
	}

	return TRUE;
}
BOOL COrigin_Stretch_Flow::Start()
{
	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(_eORIGIN_STRETCH_FLOW_START, _T("_eORIGIN_STRETCH_FLOW_START"));
	return TRUE;
}
BOOL COrigin_Stretch_Flow::Stop()
{
	m_bStopBit = TRUE;
	return TRUE;
}
UINT COrigin_Stretch_Flow::ThreadFunction(LPVOID lpParam)
{
	COrigin_Stretch_Flow* pFlow = NULL;

	pFlow = (COrigin_Stretch_Flow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}

VOID COrigin_Stretch_Flow::ThreadFunctionEntry(VOID)
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

	while (m_FlowFinish)
	{
		WaitForSingleObject(hHandle, INFINITE);
		ResetEvent(hHandle);

		if (SharedInfo::bMachineStopFlag == TRUE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(_eORIGIN_STRETCH_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}

		switch (GetCurrentTotalStep())
		{
		case _eORIGIN_STRETCH_FLOW_IDLE:
		{
			break;
		}
		case _eORIGIN_STRETCH_FLOW_START:
			m_timeStart = CTime::GetCurrentTime(); //KJT 20210329

			SetStep(_eORIGIN_STRETCH_FLOW_INTERLOCK_CHECK, _T("_eORIGIN_STRETCH_FLOW_INTERLOCK_CHECK"));
			break;

		case _eORIGIN_STRETCH_FLOW_INTERLOCK_CHECK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(_eORIGIN_STRETCH_FLOW_ERROR, _T("_eORIGIN_STRETCH_FLOW_ERROR"));
			}
			else
			{
				SetStep(_eORIGIN_STRETCH_FLOW_CLAMP_OFF, _T("_eORIGIN_STRETCH_FLOW_CLAMP_OFF"));
			}
			break;


		case _eORIGIN_STRETCH_FLOW_CLAMP_OFF:
			Devs::m_ClampMotion.ClampOff_All();
			SetStep(_eORIGIN_STRETCH_FLOW_CLAMP_OFF_CHECK, _T("_eORIGIN_STRETCH_FLOW_CLAMP_OFF_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eORIGIN_STRETCH_FLOW_CLAMP_OFF_CHECK:
			if (Devs::m_ClampMotion.Is_ClampOff_All())
			{
				SetStep(_eORIGIN_STRETCH_FLOW_SERVO_OFF, _T("_eORIGIN_STRETCH_FLOW_SERVO_OFF"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eORIGIN_STRETCH_FLOW_CLAMP_OFF_CHECK : Time Out !!!"), eORIGIN_STRETCH_FLOW + 0);
				SetStep(_eORIGIN_STRETCH_FLOW_ERROR, _T("_eORIGIN_STRETCH_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eORIGIN_STRETCH_FLOW_CLAMP_OFF_CHECK, _T("_eORIGIN_STRETCH_FLOW_CLAMP_OFF_CHECK"));
			}
			break;

		case _eORIGIN_STRETCH_FLOW_SERVO_OFF:
#ifndef GRIPPER_0
			for (i = 0; i < eGRIPPER_ROW_MAX; i++)
			{
				Devs::MotionIf.AxisSetServoOnStatus(REMOTE_AXIS_AJIN_GRIPPER_STRETCH_L1 + i, FALSE);
				Sleep(30);
				Devs::MotionIf.AxisSetServoOnStatus(REMOTE_AXIS_AJIN_GRIPPER_STRETCH_R1 + i, FALSE);
				Sleep(500); //!!
			}
#endif
			Sleep(1000);

			SetCheckStep(_eORIGIN_STRETCH_FLOW_SERVO_OFF_CHECK, _T("_eORIGIN_STRETCH_FLOW_SERVO_OFF_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eORIGIN_STRETCH_FLOW_SERVO_OFF_CHECK:
			bResult = TRUE;
#ifndef GRIPPER_0
			for (i = 0; i < eGRIPPER_ROW_MAX; i++)
			{
				if (SharedInfo::AxisServoOnStatus[REMOTE_AXIS_AJIN_GRIPPER_STRETCH_L1 + i] == TRUE ||
					SharedInfo::AxisServoOnStatus[REMOTE_AXIS_AJIN_GRIPPER_STRETCH_R1 + i] == TRUE)
				{
					bResult = FALSE;
					break;
				}
			}
#endif
			if (bResult == TRUE)
			{
				SetStep(_eORIGIN_STRETCH_FLOW_SERVO_ON, _T("_eORIGIN_STRETCH_FLOW_SERVO_ON"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eORIGIN_STRETCH_FLOW_SERVO_OFF_CHECK : Time Out !!!"), eORIGIN_STRETCH_FLOW + 1);
				SetStep(_eORIGIN_STRETCH_FLOW_ERROR, _T("_eORIGIN_STRETCH_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eORIGIN_STRETCH_FLOW_SERVO_OFF_CHECK, _T("_eORIGIN_STRETCH_FLOW_SERVO_OFF_CHECK"));
			}
			break;

		case _eORIGIN_STRETCH_FLOW_SERVO_ON:
#ifndef GRIPPER_0
			for (i = 0; i < eGRIPPER_ROW_MAX; i++)
			{
				Devs::MotionIf.AxisSetServoOnStatus(REMOTE_AXIS_AJIN_GRIPPER_STRETCH_L1 + i, TRUE);
				Sleep(30);
				Devs::MotionIf.AxisSetServoOnStatus(REMOTE_AXIS_AJIN_GRIPPER_STRETCH_R1 + i, TRUE);
				Sleep(500); //!!
			}
#endif
			Sleep(1000);

			SetCheckStep(_eORIGIN_STRETCH_FLOW_SERVO_ON_CHECK, _T("_eORIGIN_STRETCH_FLOW_SERVO_ON_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eORIGIN_STRETCH_FLOW_SERVO_ON_CHECK:
			bResult = TRUE;
#ifndef GRIPPER_0
			for (i = 0; i < eGRIPPER_ROW_MAX; i++)
			{
				if (SharedInfo::AxisServoOnStatus[REMOTE_AXIS_AJIN_GRIPPER_STRETCH_L1 + i] == FALSE ||
					SharedInfo::AxisServoOnStatus[REMOTE_AXIS_AJIN_GRIPPER_STRETCH_R1 + i] == FALSE)
				{
					bResult = FALSE;
					break;
				}
			}
#endif
			if (bResult == TRUE)
			{
				SetStep(_eORIGIN_STRETCH_FLOW_HOME_MOVE, _T("_eORIGIN_STRETCH_FLOW_HOME_MOVE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eORIGIN_STRETCH_FLOW_SERVO_ON_CHECK : Time Out !!!"), eORIGIN_STRETCH_FLOW + 2);
				SetStep(_eORIGIN_STRETCH_FLOW_ERROR, _T("_eORIGIN_STRETCH_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eORIGIN_STRETCH_FLOW_SERVO_ON_CHECK, _T("_eORIGIN_STRETCH_FLOW_SERVO_ON_CHECK"));
			}
			break;

		case _eORIGIN_STRETCH_FLOW_HOME_MOVE:
#ifndef GRIPPER_0
			for (i = 0; i < eGRIPPER_ROW_MAX; i++)
			{
				Devs::MotionIf.AxisHomeStart(REMOTE_AXIS_AJIN_GRIPPER_STRETCH_L1 + i);
				Sleep(100);
				Devs::MotionIf.AxisHomeStart(REMOTE_AXIS_AJIN_GRIPPER_STRETCH_R1 + i);
				Sleep(100); //!!
			}
#endif
			SetCheckStep(_eORIGIN_STRETCH_FLOW_HOME_BIT_OFF_CHECK, _T("_eORIGIN_STRETCH_FLOW_HOME_BIT_OFF_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;
			
		case _eORIGIN_STRETCH_FLOW_HOME_BIT_OFF_CHECK:
			bResult = TRUE;
#ifndef GRIPPER_0
			for (i = 0; i < eGRIPPER_ROW_MAX; i++)
			{
				if (SharedInfo::AxisHomeStatus[REMOTE_AXIS_AJIN_GRIPPER_STRETCH_L1 + i] == TRUE ||
					SharedInfo::AxisHomeStatus[REMOTE_AXIS_AJIN_GRIPPER_STRETCH_R1 + i] == TRUE)
				{
					bResult = FALSE;
					break;
				}
			}
#endif
			if (bResult == TRUE)
			{
				SetStep(_eORIGIN_STRETCH_FLOW_HOME_COMP_CHECK, _T("_eORIGIN_STRETCH_FLOW_HOME_COMP_CHECK"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eORIGIN_STRETCH_FLOW_HOME_BIT_OFF_CHECK : Time Out !!!"), eORIGIN_STRETCH_FLOW + 3);
				SetStep(_eORIGIN_STRETCH_FLOW_ERROR, _T("_eORIGIN_STRETCH_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eORIGIN_STRETCH_FLOW_HOME_BIT_OFF_CHECK, _T("_eORIGIN_STRETCH_FLOW_HOME_BIT_OFF_CHECK"));
			}
			break;

		case _eORIGIN_STRETCH_FLOW_HOME_COMP_CHECK:
			bResult = TRUE;
#ifndef GRIPPER_0
			for (i = 0; i < eGRIPPER_ROW_MAX; i++)
			{
				if (SharedInfo::AxisInMotionStatus[REMOTE_AXIS_AJIN_GRIPPER_STRETCH_L1 + i] || SharedInfo::AxisHomeStatus[REMOTE_AXIS_AJIN_GRIPPER_STRETCH_L1 + i] == FALSE ||
					SharedInfo::AxisInMotionStatus[REMOTE_AXIS_AJIN_GRIPPER_STRETCH_R1 + i] || SharedInfo::AxisHomeStatus[REMOTE_AXIS_AJIN_GRIPPER_STRETCH_R1 + i] == FALSE)
				{
					bResult = FALSE;
					break;
				}
			}
#endif
			if (bResult == TRUE)
			{
				Sleep(1000);
				SetStep(_eORIGIN_STRETCH_FLOW_WAIT_POS_MOVE, _T("_eORIGIN_STRETCH_FLOW_WAIT_POS_MOVE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eORIGIN_STRETCH_FLOW_HOME_COMP_CHECK : Time Out !!!"), eORIGIN_STRETCH_FLOW + 4);
				SetStep(_eORIGIN_STRETCH_FLOW_ERROR, _T("_eORIGIN_STRETCH_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eORIGIN_STRETCH_FLOW_HOME_COMP_CHECK, _T("_eORIGIN_STRETCH_FLOW_HOME_COMP_CHECK"));
			}
			break;

		case _eORIGIN_STRETCH_FLOW_WAIT_POS_MOVE:
			for (i = 0; i < eGRIPPER_ROW_MAX; i++)
			{
				Devs::m_StretchMotion.Stretch_WaitPos((enum_eGRIPPER_ROW)i);
				Sleep(500);
			}

			SetStep(_eORIGIN_STRETCH_FLOW_WAIT_POS_CHECK, _T("_eORIGIN_STRETCH_FLOW_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eORIGIN_STRETCH_FLOW_WAIT_POS_CHECK:
			if (Devs::m_StretchMotion.Is_Stretch_WaitPos_All())
			{
				SetStep(_eORIGIN_STRETCH_FLOW_DONE, _T("_eORIGIN_STRETCH_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eORIGIN_STRETCH_FLOW_WAIT_POS_CHECK : Time Out !!!"), eORIGIN_STRETCH_FLOW + 5);
				SetStep(_eORIGIN_STRETCH_FLOW_ERROR, _T("_eORIGIN_STRETCH_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eORIGIN_STRETCH_FLOW_WAIT_POS_CHECK, _T("_eORIGIN_STRETCH_FLOW_WAIT_POS_CHECK"));
			}
			break;

		case _eORIGIN_STRETCH_FLOW_DONE:
		{
			m_bFlowDone = TRUE;

			SharedInfo::CalTactTime(_T("ORIGIN_STRETCH_FLOW"), m_timeStart); //KJT 20210329

			SetStep(_eORIGIN_STRETCH_FLOW_IDLE, _T("_eORIGIN_STRETCH_FLOW_IDLE"));
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

BOOL COrigin_Stretch_Flow::FlowInterlock()
{
	CString Str = _T("");
	int i = 0;

	//if (Devs::m_ClampMotion.ClampOff_All() == FALSE)
	//{
	//	Total_Msg(_T("Check Clamp All Off !!!"));
	//	return FALSE;
	//}

	return TRUE;
}
