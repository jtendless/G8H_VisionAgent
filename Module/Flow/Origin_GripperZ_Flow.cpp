#include "stdafx.h"
#include "Origin_GripperZ_Flow.h"
#include "Vision/Devs.h"
#include "VisionAgentDlg.h"

COrigin_GripperZ_Flow::COrigin_GripperZ_Flow()
{
}


COrigin_GripperZ_Flow::~COrigin_GripperZ_Flow()
{
}

BOOL COrigin_GripperZ_Flow::InitProcess()
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
BOOL COrigin_GripperZ_Flow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eORIGIN_GRIPPER_Z_FLOW_IDLE, _T("_eORIGIN_GRIPPER_Z_FLOW_IDLE"));

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
BOOL COrigin_GripperZ_Flow::Start()
{
	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(_eORIGIN_GRIPPER_Z_FLOW_START, _T("_eORIGIN_GRIPPER_Z_FLOW_START"));
	return TRUE;
}
BOOL COrigin_GripperZ_Flow::Stop()
{
	m_bStopBit = TRUE;
	SetStop(); //!!
	return TRUE;
}
UINT COrigin_GripperZ_Flow::ThreadFunction(LPVOID lpParam)
{
	COrigin_GripperZ_Flow* pFlow = NULL;

	pFlow = (COrigin_GripperZ_Flow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}
VOID COrigin_GripperZ_Flow::ThreadFunctionEntry(VOID)
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

	while (m_FlowFinish)
	{
		WaitForSingleObject(hHandle, INFINITE);
		ResetEvent(hHandle);

		if (SharedInfo::bMachineStopFlag == TRUE)// && m_bStopBit == FALSE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(_eORIGIN_GRIPPER_Z_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}
		

		switch (GetCurrentTotalStep())
		{
		case _eORIGIN_GRIPPER_Z_FLOW_IDLE:
		{
			break;
		}
		case _eORIGIN_GRIPPER_Z_FLOW_START:
			SetStep(_eORIGIN_GRIPPER_Z_FLOW_INTERLOCK_CHECK, _T("_eORIGIN_GRIPPER_Z_FLOW_INTERLOCK_CHECK"));
			break;

		case _eORIGIN_GRIPPER_Z_FLOW_INTERLOCK_CHECK:
			if (FlowInterlock() == FALSE)
			{
				m_bFlowDone = TRUE;
				SetStep(_eORIGIN_GRIPPER_Z_FLOW_IDLE, _T("_eORIGIN_GRIPPER_Z_FLOW_IDLE"));
			}
			else
			{
				SetStep(eORIGIN_GRIPPER_Z_FLOW_CLAMP_OFF, _T("eORIGIN_GRIPPER_Z_FLOW_CLAMP_OFF"));
			}
			break;

		case eORIGIN_GRIPPER_Z_FLOW_CLAMP_OFF:		
			Devs::m_ClampMotion.ClampOff_All();
			SetStep(eORIGIN_GRIPPER_Z_FLOW_CLAMP_OFF_CHECK, _T("eORIGIN_GRIPPER_Z_FLOW_CLAMP_OFF_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eORIGIN_GRIPPER_Z_FLOW_CLAMP_OFF_CHECK:
			if (Devs::m_ClampMotion.Is_ClampOff_All())
			{
				SetStep(eORIGIN_GRIPPER_Z_FLOW_HOME_START, _T("eORIGIN_GRIPPER_Z_FLOW_HOME_START"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eORIGIN_GRIPPER_Z_FLOW_CLAMP_OFF_CHECK : Time Out !!!"), eORIGIN_GRIPPER_Z_FLOW + 0);
				SetStep(_eORIGIN_GRIPPER_Z_FLOW_ERROR, _T("_eORIGIN_GRIPPER_Z_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eORIGIN_GRIPPER_Z_FLOW_CLAMP_OFF_CHECK, _T("eORIGIN_GRIPPER_Z_FLOW_CLAMP_OFF_CHECK"));
			}
			break;			

#pragma region //GripperZ Home
		case eORIGIN_GRIPPER_Z_FLOW_HOME_START:
#ifndef GRIPPER_0
			Devs::MotionIf.AxisHomeStart(REMOTE_AXIS_AJIN_GRIPPER_ZL);
#endif
			Sleep(1000);
			
			SetStep(eORIGIN_GRIPPER_Z_FLOW_HOME_COMP_CHECK, _T("eORIGIN_GRIPPER_Z_FLOW_HOME_COMP_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eORIGIN_GRIPPER_Z_FLOW_HOME_COMP_CHECK:
#ifndef GRIPPER_0
			if (SharedInfo::AxisHomeStatus[REMOTE_AXIS_AJIN_GRIPPER_ZL] && SharedInfo::AxisHomeStatus[REMOTE_AXIS_AJIN_GRIPPER_ZR] &&
				SharedInfo::AxisInMotionStatus[REMOTE_AXIS_AJIN_GRIPPER_ZL] == FALSE && SharedInfo::AxisInMotionStatus[REMOTE_AXIS_AJIN_GRIPPER_ZR] == FALSE)// &&
				//SharedInfo::AxisCmdPos[REMOTE_AXIS_AJIN_GRIPPER_ZL] == SharedInfo::AxisCmdPos[REMOTE_AXIS_AJIN_GRIPPER_ZR])
			{
				Sleep(3000); //!!! GantryZ Sync Delay
				SetStep(eORIGIN_GRIPPER_Z_FLOW_MOVE_WAIT_POS, _T("eORIGIN_GRIPPER_Z_FLOW_MOVE_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eORIGIN_GRIPPER_Z_FLOW_HOME_COMP_CHECK : Time Out !!!"), eORIGIN_GRIPPER_Z_FLOW + 1);
				SetStep(_eORIGIN_GRIPPER_Z_FLOW_ERROR, _T("_eORIGIN_GRIPPER_Z_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eORIGIN_GRIPPER_Z_FLOW_HOME_COMP_CHECK, _T("eORIGIN_GRIPPER_Z_FLOW_HOME_COMP_CHECK"));
			}
#endif
			break;

		case eORIGIN_GRIPPER_Z_FLOW_MOVE_WAIT_POS:
			Devs::m_GripperZMotion.Move_GripperLeftZ_WaitPos();
			Devs::m_GripperZMotion.Move_GripperRightZ_WaitPos();
			Sleep(100); //!!

			SetStep(eORIGIN_GRIPPER_Z_FLOW_MOVE_WAIT_POS_CHECK, _T("eORIGIN_GRIPPER_Z_FLOW_MOVE_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eORIGIN_GRIPPER_Z_FLOW_MOVE_WAIT_POS_CHECK:
			if (Devs::m_GripperZMotion.Is_GripperLeftZ_WaitPos() && Devs::m_GripperZMotion.Is_GripperRightZ_WaitPos())
			{
				SetStep(_eORIGIN_GRIPPER_Z_FLOW_DONE, _T("_eORIGIN_GRIPPER_Z_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eORIGIN_GRIPPER_Z_FLOW_MOVE_WAIT_POS_CHECK : Time Out !!!"), eORIGIN_GRIPPER_Z_FLOW + 2);
				SetStep(_eORIGIN_GRIPPER_Z_FLOW_ERROR, _T("_eORIGIN_GRIPPER_Z_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eORIGIN_GRIPPER_Z_FLOW_MOVE_WAIT_POS_CHECK, _T("eORIGIN_GRIPPER_Z_FLOW_MOVE_WAIT_POS_CHECK"));
			}
			break;
#pragma endregion

		case _eORIGIN_GRIPPER_Z_FLOW_DONE:
		{
			m_bFlowDone = TRUE;

			SetStep(_eORIGIN_GRIPPER_Z_FLOW_IDLE, _T("_eORIGIN_GRIPPER_Z_FLOW_IDLE"));
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

BOOL COrigin_GripperZ_Flow::FlowInterlock()
{
	CString Str = _T("");
#ifndef GRIPPER_0
	if (SharedInfo::GetServoOnStatus(AXIS_GRIPPER_ZL) != TRUE)
	{
		Total_Msg(_T("Gripper ZL Servo On Check !!!"));
		SharedInfo::SetAlarm(_T("Origin_GripperZ_Flow : Gripper ZL Servo On Check !!!"), eORIGIN_GRIPPER_Z_FLOW + 20);
		return FALSE;
	}
	if (SharedInfo::GetServoOnStatus(AXIS_GRIPPER_ZR) != TRUE)
	{
		Total_Msg(_T("Gripper ZR Servo On Check !!!"));
		SharedInfo::SetAlarm(_T("Origin_GripperZ_Flow : Gripper ZR Servo On Check !!!"), eORIGIN_GRIPPER_Z_FLOW + 21);
		return FALSE;
	}
#endif
	return TRUE;
}