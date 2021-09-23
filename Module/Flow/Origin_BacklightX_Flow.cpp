#include "stdafx.h"
#include "Origin_BacklightX_Flow.h"
#include "Vision/Devs.h"
#include "VisionAgentDlg.h"

COrigin_BacklightX_Flow::COrigin_BacklightX_Flow()
{
}


COrigin_BacklightX_Flow::~COrigin_BacklightX_Flow()
{
}

BOOL COrigin_BacklightX_Flow::InitProcess()
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
BOOL COrigin_BacklightX_Flow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eORIGIN_BACKLIGHT_X_FLOW_IDLE, _T("_eORIGIN_BACKLIGHT_X_FLOW_IDLE"));

	if (hHandle != NULL)
	{
		CloseHandle(hHandle);
	}

	return TRUE;
}
BOOL COrigin_BacklightX_Flow::Start()
{
	eRemoteAxis = REMOTE_AXIS_AJIN_LOADER_X;

	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(_eORIGIN_BACKLIGHT_X_FLOW_START, _T("_eORIGIN_BACKLIGHT_X_FLOW_START"));
	return TRUE;
}
BOOL COrigin_BacklightX_Flow::Stop()
{
	m_bStopBit = TRUE;
	return TRUE;
}
UINT COrigin_BacklightX_Flow::ThreadFunction(LPVOID lpParam)
{
	COrigin_BacklightX_Flow* pFlow = NULL;

	pFlow = (COrigin_BacklightX_Flow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}

VOID COrigin_BacklightX_Flow::ThreadFunctionEntry(VOID)
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

		if (SharedInfo::bMachineStopFlag == TRUE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(_eORIGIN_BACKLIGHT_X_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}

		switch (GetCurrentTotalStep())
		{
		case _eORIGIN_BACKLIGHT_X_FLOW_IDLE:
		{
			break;
		}
		case _eORIGIN_BACKLIGHT_X_FLOW_START:
			m_timeStart = CTime::GetCurrentTime(); //KJT 20210329

			SetStep(_eORIGIN_BACKLIGHT_X_FLOW_INTERLOCK_CHECK, _T("_eORIGIN_BACKLIGHT_X_FLOW_INTERLOCK_CHECK"));
			break;

		case _eORIGIN_BACKLIGHT_X_FLOW_INTERLOCK_CHECK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(_eORIGIN_BACKLIGHT_X_FLOW_ERROR, _T("_eORIGIN_BACKLIGHT_X_FLOW_ERROR"));
			}
			else
			{
				SetStep(_eORIGIN_BACKLIGHT_X_FLOW_HOME_START, _T("_eORIGIN_BACKLIGHT_X_FLOW_HOME_START"));
			}
			break;

		case _eORIGIN_BACKLIGHT_X_FLOW_SERVO_OFF:
			Devs::MotionIf.AxisSetServoOnStatus(REMOTE_AXIS_AJIN_BACKLIGHT_X, FALSE);
			Sleep(100);

			SetCheckStep(_eORIGIN_BACKLIGHT_X_FLOW_SERVO_OFF_CHECK, _T("_eORIGIN_BACKLIGHT_X_FLOW_SERVO_OFF_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eORIGIN_BACKLIGHT_X_FLOW_SERVO_OFF_CHECK:
			if (SharedInfo::AxisServoOnStatus[REMOTE_AXIS_AJIN_BACKLIGHT_X] == FALSE)
			{
				SetStep(_eORIGIN_BACKLIGHT_X_FLOW_SERVO_ON, _T("_eORIGIN_BACKLIGHT_X_FLOW_SERVO_ON"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eORIGIN_BACKLIGHT_X_FLOW_ERROR, _T("_eORIGIN_BACKLIGHT_X_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eORIGIN_BACKLIGHT_X_FLOW_SERVO_OFF_CHECK, _T("_eORIGIN_BACKLIGHT_X_FLOW_SERVO_OFF_CHECK"));
			}
			break;

		case _eORIGIN_BACKLIGHT_X_FLOW_SERVO_ON:
			Devs::MotionIf.AxisSetServoOnStatus(REMOTE_AXIS_AJIN_BACKLIGHT_X, TRUE);
			Sleep(100);

			SetCheckStep(_eORIGIN_BACKLIGHT_X_FLOW_SERVO_ON_CHECK, _T("_eORIGIN_BACKLIGHT_X_FLOW_SERVO_ON_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eORIGIN_BACKLIGHT_X_FLOW_SERVO_ON_CHECK:
			if (SharedInfo::AxisServoOnStatus[REMOTE_AXIS_AJIN_BACKLIGHT_X] == TRUE)
			{
				SetStep(_eORIGIN_BACKLIGHT_X_FLOW_HOME_START, _T("_eORIGIN_BACKLIGHT_X_FLOW_HOME_START"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eORIGIN_BACKLIGHT_X_FLOW_ERROR, _T("_eORIGIN_BACKLIGHT_X_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eORIGIN_BACKLIGHT_X_FLOW_SERVO_ON_CHECK, _T("_eORIGIN_BACKLIGHT_X_FLOW_SERVO_ON_CHECK"));
			}
			break;

		case _eORIGIN_BACKLIGHT_X_FLOW_HOME_START:
			Devs::MotionIf.AxisHomeStart(REMOTE_AXIS_AJIN_BACKLIGHT_X);
			Sleep(100); //!!

			SetStep(_eORIGIN_BACKLIGHT_X_FLOW_HOME_BIT_OFF_CHECK, _T("_eORIGIN_BACKLIGHT_X_FLOW_HOME_BIT_OFF_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eORIGIN_BACKLIGHT_X_FLOW_HOME_BIT_OFF_CHECK:
			if (!SharedInfo::AxisHomeStatus[REMOTE_AXIS_AJIN_BACKLIGHT_X])
			{
				SetStep(_eORIGIN_BACKLIGHT_X_FLOW_HOME_COMP_CHECK, _T("_eORIGIN_BACKLIGHT_X_FLOW_HOME_COMP_CHECK"));
				SetTimeOut(TIME_OUT_MOTION);
			}
			else if (IsTimeOut())
			{
				SetStep(_eORIGIN_BACKLIGHT_X_FLOW_ERROR, _T("_eORIGIN_BACKLIGHT_X_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eORIGIN_BACKLIGHT_X_FLOW_HOME_BIT_OFF_CHECK, _T("_eORIGIN_BACKLIGHT_X_FLOW_HOME_BIT_OFF_CHECK"));
			}
			break;

		case _eORIGIN_BACKLIGHT_X_FLOW_HOME_COMP_CHECK:
			if (SharedInfo::AxisInMotionStatus[REMOTE_AXIS_AJIN_BACKLIGHT_X] == FALSE && SharedInfo::AxisHomeStatus[REMOTE_AXIS_AJIN_BACKLIGHT_X])
			{
				SetStep(_eORIGIN_BACKLIGHT_X_FLOW_WAIT_POS, _T("_eORIGIN_BACKLIGHT_X_FLOW_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eORIGIN_BACKLIGHT_X_FLOW_ERROR, _T("_eORIGIN_BACKLIGHT_X_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eORIGIN_BACKLIGHT_X_FLOW_HOME_COMP_CHECK, _T("_eORIGIN_BACKLIGHT_X_FLOW_HOME_COMP_CHECK"));
			}
			break;

		case _eORIGIN_BACKLIGHT_X_FLOW_WAIT_POS:
			Devs::m_InspectionStageMotion.BackLightX_WaitPos();
			Sleep(1000);

			SetStep(_eORIGIN_BACKLIGHT_X_FLOW_WAIT_POS_CHECK, _T("_eORIGIN_BACKLIGHT_X_FLOW_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eORIGIN_BACKLIGHT_X_FLOW_WAIT_POS_CHECK:
			if (Devs::m_InspectionStageMotion.Is_BackLightX_WaitPos())
			{
				SetStep(_eORIGIN_BACKLIGHT_X_FLOW_DONE, _T("_eORIGIN_BACKLIGHT_X_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eORIGIN_BACKLIGHT_X_FLOW_ERROR, _T("_eORIGIN_BACKLIGHT_X_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eORIGIN_BACKLIGHT_X_FLOW_WAIT_POS_CHECK, _T("_eORIGIN_BACKLIGHT_X_FLOW_WAIT_POS_CHECK"));
			}
			break;

		case _eORIGIN_BACKLIGHT_X_FLOW_DONE:
		{
			m_bFlowDone = TRUE;

			SharedInfo::CalTactTime(_T("ORIGIN_BACKLIGHT_X_FLOW"), m_timeStart); //KJT 20210329

			SetStep(_eORIGIN_BACKLIGHT_X_FLOW_IDLE, _T("_eORIGIN_BACKLIGHT_X_FLOW_IDLE"));
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

BOOL COrigin_BacklightX_Flow::FlowInterlock()
{
	CString Str = _T("");

	return TRUE;
}
