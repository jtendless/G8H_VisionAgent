#include "stdafx.h"
#include "Flow/Origin_AllAxis_Flow.h"
#include "Vision/Devs.h"
#include "VisionAgentDlg.h"


COrigin_AllAxis_Flow::COrigin_AllAxis_Flow()
{
}


COrigin_AllAxis_Flow::~COrigin_AllAxis_Flow()
{
}

BOOL COrigin_AllAxis_Flow::InitProcess()
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
BOOL COrigin_AllAxis_Flow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eORIGIN_ALL_AXIS_FLOW_IDLE, _T("_eORIGIN_ALL_AXIS_FLOW_IDLE"));

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
BOOL COrigin_AllAxis_Flow::Start()
{
	m_bStopBit = FALSE;
	m_stepFlag = 0;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	//SetStep(_eORIGIN_ALL_AXIS_FLOW_START, _T("_eORIGIN_ALL_AXIS_FLOW_START"));
	
	SetStep(eORIGIN_ALL_AXIS_SERVO_OFF, _T("eORIGIN_ALL_AXIS_SERVO_OFF"));
	return TRUE;
}
BOOL COrigin_AllAxis_Flow::Stop()
{
	m_bStopBit = TRUE;
	SetStop(); //!!
	return TRUE;
}
UINT COrigin_AllAxis_Flow::ThreadFunction(LPVOID lpParam)
{
	COrigin_AllAxis_Flow* pFlow = NULL;

	pFlow = (COrigin_AllAxis_Flow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}
VOID COrigin_AllAxis_Flow::ThreadFunctionEntry(VOID)
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

	BOOL bResult = FALSE;
	double dVel = 5.0;
	double dAcc = 10.0;
	double dDec = 10.0;
	int LimitSignal = 0;
	int i, nRtn;

	while (m_FlowFinish)
	{
		WaitForSingleObject(hHandle, INFINITE);
		ResetEvent(hHandle);

		if (SharedInfo::bMachineStopFlag == TRUE)// && m_bStopBit == FALSE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(_eORIGIN_ALL_AXIS_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}
	
		switch (GetCurrentTotalStep())
		{
		case _eORIGIN_ALL_AXIS_FLOW_IDLE:
		{
			break;
		}
		case _eORIGIN_ALL_AXIS_FLOW_START:

			m_timeStart = CTime::GetCurrentTime(); //KJT 20210329
			SharedInfo::m_timeUnitTact = m_timeStart;

			SharedInfo::nCurFlowID = eORIGIN_ALL_FLOW;

			SetStep(_eORIGIN_ALL_AXIS_FLOW_INTERLOCK_CHECK, _T("_eORIGIN_ALL_AXIS_FLOW_INTERLOCK_CHECK"));
			break;

		case _eORIGIN_ALL_AXIS_FLOW_INTERLOCK_CHECK:
			if (FlowInterlock() == FALSE)
			{
				m_bFlowDone = TRUE;
				SetStep(_eORIGIN_ALL_AXIS_FLOW_IDLE, _T("_eORIGIN_ALL_AXIS_FLOW_IDLE"));
			}
			else
			{
				SetStep(eORIGIN_ALL_AXIS_DOUT_SET, _T("eORIGIN_ALL_AXIS_DOUT_SET"));
			}
			break;

			//DOUT SETTING
		case eORIGIN_ALL_AXIS_DOUT_SET:
			SetStep(eORIGIN_ALL_AXIS_SERVO_ON, _T("eORIGIN_ALL_AXIS_SERVO_ON"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eORIGIN_ALL_AXIS_SERVO_OFF:
			m_timeStart = CTime::GetCurrentTime(); //KJT 20210329
			SharedInfo::m_timeUnitTact = m_timeStart;

			SharedInfo::nCurFlowID = eORIGIN_ALL_FLOW;

			if (m_stepFlag == 0)
			{
				m_stepFlag++;
				for (int i = AXIS_GANTRY_Y1; i < AXIS_MAX; i++)
				{
					m_Motion->ServoOnOff((enum_Axis)i, FALSE);
					Sleep(300);
				}
				SetStep(eORIGIN_ALL_AXIS_SERVO_OFF_CHECK, _T("eORIGIN_ALL_AXIS_SERVO_OFF_CHECK"));
				SetTimeOut(TIME_OUT_MOTION);
			}
			break;
		case eORIGIN_ALL_AXIS_SERVO_OFF_CHECK:
		{
			int servoOnCheck = 0;
			m_stepFlag = 0;
			for (int i = AXIS_GANTRY_Y1; i < AXIS_MAX; i++)
			{
				servoOnCheck = servoOnCheck || SharedInfo::GetServoOnStatus((enum_Axis)i);
				Sleep(10);
			}
			if (servoOnCheck == 0)
			{
				Sleep(100);
				SetStep(eORIGIN_ALL_AXIS_SERVO_ON, _T("eORIGIN_ALL_AXIS_SERVO_ON"));
				SetTimeOut(TIME_OUT_MOTION);
				m_stepFlag = 0;
				break;
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eORIGIN_ALL_AXIS_SERVO_OFF_CHECK : Time Out"), eORIGIN_ALL_FLOW + 0);
				SetStep(_eORIGIN_ALL_AXIS_FLOW_ERROR, _T("_eORIGIN_ALL_AXIS_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eORIGIN_ALL_AXIS_SERVO_OFF_CHECK, _T("eORIGIN_ALL_AXIS_SERVO_OFF_CHECK"));
			}
			break;
		}
		case eORIGIN_ALL_AXIS_SERVO_ON:
		{
			if (m_stepFlag == 0)
			{
				m_stepFlag++;
				for (int i = AXIS_GANTRY_Y1; i < AXIS_MAX; i++)
				{
					m_Motion->ServoOnOff((enum_Axis)i, TRUE);
					Sleep(300);
				}
				SetStep(eORIGIN_ALL_AXIS_SERVO_ON_CHECK, _T("eORIGIN_ALL_AXIS_SERVO_ON_CHECK"));
				SetTimeOut(TIME_OUT_MOTION);
			}
			break;
		}
		case eORIGIN_ALL_AXIS_SERVO_ON_CHECK:
		{
			int servoOnCheck = 1;
			m_stepFlag = 0;
			for (int i = AXIS_GANTRY_Y1; i < AXIS_MAX; i++)
			{
				servoOnCheck = servoOnCheck && SharedInfo::GetServoOnStatus((enum_Axis)i);
				Sleep(10);
			}
			if (servoOnCheck == 1)
			{
				SetTimeOut(TIME_OUT_MOTION);
				break;
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eORIGIN_ALL_AXIS_SERVO_ON_CHECK : Time Out"), eORIGIN_ALL_FLOW + 1);
				SetStep(_eORIGIN_ALL_AXIS_FLOW_ERROR, _T("_eORIGIN_ALL_AXIS_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eORIGIN_ALL_AXIS_SERVO_ON_CHECK, _T("eORIGIN_ALL_AXIS_SERVO_ON_CHECK"));
			}
			break;
		}
		
		//TO DO

		case _eORIGIN_ALL_AXIS_FLOW_DONE:
		{
			SharedInfo::nPrevFlowID = eORIGIN_ALL_FLOW; //KJT 20210326
		
			SharedInfo::CalTactTime(_T("eORIGIN_ALL_FLOW"), m_timeStart); //KJT 20210329

			m_bFlowDone = TRUE;

			SetStep(_eORIGIN_ALL_AXIS_FLOW_IDLE, _T("_eORIGIN_ALL_AXIS_FLOW_IDLE"));
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

BOOL COrigin_AllAxis_Flow::FlowInterlock()
{
	return TRUE;
}