#include "stdafx.h"
#include "Ready_Gripper_Flow.h"
#include "Log/Logger.h"
#include "Vision/Devs.h"
#include "Data/ModelData.h"
#include "CamAreaModul.h"
#include "Data/SystemData.h"
#include "VisionAgentDlg.h"

CReady_Gripper_Flow::CReady_Gripper_Flow()
{
}


CReady_Gripper_Flow::~CReady_Gripper_Flow()
{
}

BOOL CReady_Gripper_Flow::InitProcess()
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
BOOL CReady_Gripper_Flow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eREADY_GRIPPER_FLOW_IDLE, _T("_eREADY_GRIPPER_FLOW_IDLE"));

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

BOOL CReady_Gripper_Flow::Start()
{
	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(_eREADY_GRIPPER_FLOW_START, _T("_eREADY_GRIPPER_FLOW_START"));
	return TRUE;
}
BOOL CReady_Gripper_Flow::Stop()
{
	m_bStopBit = TRUE;
	SetStop(); //!!
	return TRUE;
}

UINT CReady_Gripper_Flow::ThreadFunction(LPVOID lpParam)
{
	CReady_Gripper_Flow* pFlow = NULL;

	pFlow = (CReady_Gripper_Flow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}

VOID CReady_Gripper_Flow::ThreadFunctionEntry(VOID)
{
	DWORD	dwResult = 0;
	double	dStrt_Time = GetTickCount();
	double	dEnd_Time = GetTickCount();
	double	dWait_Time = GetTickCount();
	int		nWork_Mask_Mode = -1;
	int		nWork_Mask_Index = -1;
	BOOL	bComplete_Step = FALSE;
	CVisionAgentDlg *pMain = (CVisionAgentDlg*)AfxGetMainWnd();
	CString Str = _T(""), StrAxisName = _T("");

	while (m_FlowFinish)
	{
		WaitForSingleObject(hHandle, INFINITE);
		ResetEvent(hHandle);

		if (SharedInfo::bMachineStopFlag == TRUE)// && m_bStopBit == FALSE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(_eREADY_GRIPPER_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}

		
		switch (GetCurrentTotalStep())
		{
		case _eREADY_GRIPPER_FLOW_IDLE:
		{
			break;
		}
		case _eREADY_GRIPPER_FLOW_START:
		{
			SetStep(_eREADY_GRIPPER_FLOW_INTERLOCK_CHECK, _T("_eREADY_GRIPPER_FLOW_INTERLOCK_CHECK"));
			break;
		}

		case _eREADY_GRIPPER_FLOW_INTERLOCK_CHECK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(_eREADY_GRIPPER_FLOW_ERROR, _T("_eREADY_GRIPPER_FLOW_ERROR"));
			}
			else
			{
				SetStep(_eREADY_GRIPPER_FLOW_GRIPPER_CLAMP_OFF, _T("_eREADY_GRIPPER_FLOW_GRIPPER_CLAMP_OFF"));
			}
			break;

		case _eREADY_GRIPPER_FLOW_GRIPPER_CLAMP_OFF:
			Devs::m_ClampMotion.ClampOff_All();

			SetStep(_eREADY_GRIPPER_FLOW_GRIPPER_CLAMP_OFF_CHECK, _T("_eREADY_GRIPPER_FLOW_GRIPPER_CLAMP_OFF_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eREADY_GRIPPER_FLOW_GRIPPER_CLAMP_OFF_CHECK:
			if (Devs::m_ClampMotion.Is_ClampOff_All())
			{
				SetStep(_eREADY_GRIPPER_FLOW_GRIPPER_STRETCH_WAIT_POS, _T("_eREADY_GRIPPER_FLOW_GRIPPER_STRETCH_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eREADY_GRIPPER_FLOW_GRIPPER_CLAMP_OFF_CHECK : Time Out!!!"), eREADY_GRIPPER_FLOW + 0);
				SetStep(_eREADY_GRIPPER_FLOW_ERROR, _T("_eREADY_GRIPPER_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eREADY_GRIPPER_FLOW_GRIPPER_CLAMP_OFF_CHECK, _T("_eREADY_GRIPPER_FLOW_GRIPPER_CLAMP_OFF_CHECK"));
			}
			break;

		case _eREADY_GRIPPER_FLOW_GRIPPER_STRETCH_WAIT_POS:
			Devs::m_StretchMotion.Stretch_WaitPos_All();

			SetStep(_eREADY_GRIPPER_FLOW_GRIPPER_STRETCH_WAIT_POS_CHECK, _T("_eREADY_GRIPPER_FLOW_GRIPPER_STRETCH_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eREADY_GRIPPER_FLOW_GRIPPER_STRETCH_WAIT_POS_CHECK:
			if (Devs::m_StretchMotion.Is_Stretch_WaitPos_All())
			{
				SetStep(_eREADY_GRIPPER_FLOW_GRIPPER_Z_WAIT_POS, _T("_eREADY_GRIPPER_FLOW_GRIPPER_Z_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eREADY_GRIPPER_FLOW_GRIPPER_STRETCH_WAIT_POS_CHECK : Time Out!!!"), eREADY_GRIPPER_FLOW + 1);
				SetStep(_eREADY_GRIPPER_FLOW_ERROR, _T("_eREADY_GRIPPER_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eREADY_GRIPPER_FLOW_GRIPPER_STRETCH_WAIT_POS_CHECK, _T("_eREADY_GRIPPER_FLOW_GRIPPER_STRETCH_WAIT_POS_CHECK"));
			}
			break;

		case _eREADY_GRIPPER_FLOW_GRIPPER_Z_WAIT_POS:
			Devs::m_GripperZMotion.Move_GripperLeftZ_WaitPos();
			Sleep(10); //!!

			SetStep(_eREADY_GRIPPER_FLOW_GRIPPER_Z_WAIT_POS_CHECK, _T("_eREADY_GRIPPER_FLOW_GRIPPER_Z_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eREADY_GRIPPER_FLOW_GRIPPER_Z_WAIT_POS_CHECK:
			if (Devs::m_GripperZMotion.Is_GripperLeftZ_WaitPos() && Devs::m_GripperZMotion.Is_GripperRightZ_WaitPos())
			{
				SetStep(_eREADY_GRIPPER_FLOW_DONE, _T("_eREADY_GRIPPER_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eREADY_GRIPPER_FLOW_GRIPPER_Z_WAIT_POS_CHECK : Time Out!!!"), eREADY_GRIPPER_FLOW + 2);
				SetStep(_eREADY_GRIPPER_FLOW_ERROR, _T("_eREADY_GRIPPER_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eREADY_GRIPPER_FLOW_GRIPPER_Z_WAIT_POS_CHECK, _T("_eREADY_GRIPPER_FLOW_GRIPPER_Z_WAIT_POS_CHECK"));
			}
			break;
		

		case _eREADY_GRIPPER_FLOW_ERROR:
			break;

		case _eREADY_GRIPPER_FLOW_DONE:
		{
			m_bFlowDone = TRUE;

			SetStep(_eREADY_GRIPPER_FLOW_IDLE, _T("_eREADY_GRIPPER_FLOW_IDLE"));			
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

BOOL CReady_Gripper_Flow::FlowInterlock()
{
	CString Str = _T("");
	int i = 0;
#ifndef GRIPPER_0
	for (i = 0; i < eGRIPPER_ROW_MAX; i++)
	{
		//21.02.04 sjc no gripper servo
		////Clamp
		//if (SharedInfo::GetServoOnStatus((enum_Axis)(AXIS_GRIPPER_CLAMP_L1 + i)) == FALSE)
		//{
		//	Str.Format(_T("Check Clamp L%d Servo On !!!"), i + 1);
		//	Total_Msg(Str);
		//	return FALSE;
		//}

		//if (SharedInfo::GetServoOnStatus((enum_Axis)(AXIS_GRIPPER_CLAMP_R1 + i)) == FALSE)
		//{
		//	Str.Format(_T("Check Clamp R%d Servo On !!!"), i + 1);
		//	Total_Msg(Str);
		//	return FALSE;
		//}

		//Stretch

		if (SharedInfo::GetServoOnStatus((enum_Axis)(AXIS_GRIPPER_STRETCH_L1 + i)) == FALSE)
		{
			Str.Format(_T("Ready_Gripper_Flow : Check Stretch L%d Servo On !!!"), i + 1);
			Total_Msg(Str);
			SharedInfo::SetAlarm(Str, eREADY_GRIPPER_FLOW + 10 + i);
			return FALSE;
		}
		if (SharedInfo::GetServoOnStatus((enum_Axis)(AXIS_GRIPPER_STRETCH_R1 + i)) == FALSE)
		{
			Str.Format(_T("Ready_Gripper_Flow : Check Stretch R%d Servo On !!!"), i + 1);
			Total_Msg(Str);
			SharedInfo::SetAlarm(Str, eREADY_GRIPPER_FLOW + 10 + i + 1);
			return FALSE;
		}

	}

	if (SharedInfo::GetServoOnStatus(AXIS_GRIPPER_ZL) == FALSE)
	{
		Str.Format(_T("Ready_Gripper_Flow : Check Gripper ZL Servo On !!!"));		
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, eREADY_GRIPPER_FLOW + 10 + i + 1);
		return FALSE;
	}
	if (SharedInfo::GetServoOnStatus(AXIS_GRIPPER_ZR) == FALSE)
	{
		Str.Format(_T("Ready_Gripper_Flow : Check Gripper ZR Servo On !!!"));
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, eREADY_GRIPPER_FLOW + 10 + i + 2);
		return FALSE;
	}
#endif
	return TRUE;
}