#include "stdafx.h"
#include "Origin_LoaderX_Flow.h"
#include "Vision/Devs.h"
#include "VisionAgentDlg.h"

COrigin_LoaderX_Flow::COrigin_LoaderX_Flow()
{
}


COrigin_LoaderX_Flow::~COrigin_LoaderX_Flow()
{
}

BOOL COrigin_LoaderX_Flow::InitProcess()
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
BOOL COrigin_LoaderX_Flow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eORIGIN_LOADER_X_FLOW_IDLE, _T("_eORIGIN_LOADER_X_FLOW_IDLE"));

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
BOOL COrigin_LoaderX_Flow::Start()
{
	eRemoteAxis = REMOTE_AXIS_AJIN_LOADER_X;

	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(_eORIGIN_LOADER_X_FLOW_START, _T("_eORIGIN_LOADER_X_FLOW_START"));
	return TRUE;
}
BOOL COrigin_LoaderX_Flow::Stop()
{
	m_bStopBit = TRUE;
	SetStop(); //!!
	return TRUE;
}
UINT COrigin_LoaderX_Flow::ThreadFunction(LPVOID lpParam)
{
	COrigin_LoaderX_Flow* pFlow = NULL;

	pFlow = (COrigin_LoaderX_Flow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}
VOID COrigin_LoaderX_Flow::ThreadFunctionEntry(VOID)
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

			SetCurrentStep(_eORIGIN_LOADER_X_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}
		if (SharedInfo::bMachineStopFlag == TRUE)
			continue;

		switch (GetCurrentTotalStep())
		{
		case _eORIGIN_LOADER_X_FLOW_IDLE:
		{
			break;
		}
		case _eORIGIN_LOADER_X_FLOW_START:
			SetStep(_eORIGIN_LOADER_X_FLOW_INTERLOCK_CHECK, _T("_eORIGIN_LOADER_X_FLOW_INTERLOCK_CHECK"));
			break;

		case _eORIGIN_LOADER_X_FLOW_INTERLOCK_CHECK:
			if (FlowInterlock() == FALSE)
			{
				m_bFlowDone = TRUE;
				SetStep(_eORIGIN_LOADER_X_FLOW_IDLE, _T("_eORIGIN_LOADER_X_FLOW_IDLE"));
			}
			else
			{
				SetStep(eORIGIN_LOADER_X_FLOW_HOME_START, _T("eORIGIN_LOADER_X_FLOW_HOME_START"));
			}
			break;

#pragma region //LopaderX Home
		case eORIGIN_LOADER_X_FLOW_HOME_START:
			Devs::MotionIf.AxisHomeStart(eRemoteAxis);
			Sleep(3000); //!!

			SetStep(eORIGIN_LOADER_X_FLOW_HOME_COMP_CHECK, _T("eORIGIN_LOADER_X_FLOW_HOME_COMP_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eORIGIN_LOADER_X_FLOW_HOME_COMP_CHECK:
			if (SharedInfo::AxisInMotionStatus[eRemoteAxis] == FALSE && SharedInfo::AxisHomeStatus[eRemoteAxis])
			{
				SetStep(eORIGIN_LOADER_X_FLOW_WAIT_POS, _T("eORIGIN_LOADER_X_FLOW_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eORIGIN_LOADER_X_FLOW_ERROR, _T("_eORIGIN_LOADER_X_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eORIGIN_LOADER_X_FLOW_HOME_COMP_CHECK, _T("eORIGIN_LOADER_X_FLOW_HOME_COMP_CHECK"));
			}
			break;

		case eORIGIN_LOADER_X_FLOW_WAIT_POS:
			Devs::m_LoaderMotion.LoaderX_WaitPos();

			SetStep(eORIGIN_LOADER_X_FLOW_WAIT_POS_CHECK, _T("eORIGIN_LOADER_X_FLOW_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eORIGIN_LOADER_X_FLOW_WAIT_POS_CHECK:
			if (Devs::m_LoaderMotion.Is_LoaderX_WaitPos())
			{
				SetStep(_eORIGIN_LOADER_X_FLOW_DONE, _T("_eORIGIN_LOADER_X_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eORIGIN_LOADER_X_FLOW_ERROR, _T("_eORIGIN_LOADER_X_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eORIGIN_LOADER_X_FLOW_WAIT_POS_CHECK, _T("eORIGIN_LOADER_X_FLOW_WAIT_POS_CHECK"));
			}
			break;
#pragma endregion

		case _eORIGIN_LOADER_X_FLOW_DONE:
		{
			m_bFlowDone = TRUE;

			SetStep(_eORIGIN_LOADER_X_FLOW_IDLE, _T("_eORIGIN_LOADER_X_FLOW_IDLE"));
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

BOOL COrigin_LoaderX_Flow::FlowInterlock()
{
	CString Str = _T("");

	if (SharedInfo::GetServoOnStatus(AXIS_LOADER_X) != TRUE)
	{
		Total_Msg(_T("Loader X Servo On Check !!!"));
		return FALSE;
	}

	return TRUE;
}