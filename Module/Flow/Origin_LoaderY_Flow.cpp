#include "stdafx.h"
#include "Origin_LoaderY_Flow.h"
#include "Vision/Devs.h"
#include "VisionAgentDlg.h"
#include "Data/ManualData.h"

COrigin_LoaderY_Flow::COrigin_LoaderY_Flow()
{
}


COrigin_LoaderY_Flow::~COrigin_LoaderY_Flow()
{
}

BOOL COrigin_LoaderY_Flow::InitProcess()
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
BOOL COrigin_LoaderY_Flow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eORIGIN_LOADER_Y_FLOW_IDLE, _T("_eORIGIN_LOADER_Y_FLOW_IDLE"));

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
BOOL COrigin_LoaderY_Flow::Start()
{
	eRemoteAxis = REMOTE_AXIS_AJIN_LOADER_YL;

	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(_eORIGIN_LOADER_Y_FLOW_START, _T("_eORIGIN_LOADER_Y_FLOW_START"));
	return TRUE;
}
BOOL COrigin_LoaderY_Flow::Stop()
{
	m_bStopBit = TRUE;
	SetStop(); //!!
	return TRUE;
}
UINT COrigin_LoaderY_Flow::ThreadFunction(LPVOID lpParam)
{
	COrigin_LoaderY_Flow* pFlow = NULL;

	pFlow = (COrigin_LoaderY_Flow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}
VOID COrigin_LoaderY_Flow::ThreadFunctionEntry(VOID)
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

			SetCurrentStep(_eORIGIN_LOADER_Y_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}
		

		switch (GetCurrentTotalStep())
		{
		case _eORIGIN_LOADER_Y_FLOW_IDLE:
		{
			break;
		}
		case _eORIGIN_LOADER_Y_FLOW_START:
			SetStep(_eORIGIN_LOADER_Y_FLOW_INTERLOCK_CHECK, _T("_eORIGIN_LOADER_Y_FLOW_INTERLOCK_CHECK"));
			break;

		case _eORIGIN_LOADER_Y_FLOW_INTERLOCK_CHECK:
			if (FlowInterlock() == FALSE)
			{
				m_bFlowDone = TRUE;
				SetStep(_eORIGIN_LOADER_Y_FLOW_IDLE, _T("_eORIGIN_LOADER_Y_FLOW_IDLE"));
			}
			else
			{
				SetStep(_eORIGIN_LOADER_Y_FLOW_HOME_START, _T("_eORIGIN_LOADER_Y_FLOW_HOME_START"));
			}
			break;

		case _eORIGIN_LOADER_Y_FLOW_HOME_START:
			Devs::MotionIf.AxisHomeStart(eRemoteAxis);
			Sleep(3000); //!!

			SetStep(_eORIGIN_LOADER_Y_FLOW_HOME_COMP_CHECK, _T("_eORIGIN_LOADER_Y_FLOW_HOME_COMP_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eORIGIN_LOADER_Y_FLOW_HOME_COMP_CHECK:
			if (SharedInfo::AxisInMotionStatus[eRemoteAxis] == FALSE && SharedInfo::AxisHomeStatus[eRemoteAxis])
			{
				SetStep(_eORIGIN_LOADER_Y_FLOW_WAIT_POS, _T("_eORIGIN_LOADER_Y_FLOW_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eORIGIN_LOADER_Y_FLOW_HOME_COMP_CHECK : Time Out !!!"), eORIGIN_LOADER_Y_FLOW + 0);
				SetStep(_eORIGIN_LOADER_Y_FLOW_ERROR, _T("_eORIGIN_LOADER_Y_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eORIGIN_LOADER_Y_FLOW_HOME_COMP_CHECK, _T("_eORIGIN_LOADER_Y_FLOW_HOME_COMP_CHECK"));
			}
			break;

		case _eORIGIN_LOADER_Y_FLOW_WAIT_POS:
			Devs::m_LoaderMotion.LoaderY_WaitPos();

			SetStep(_eORIGIN_LOADER_Y_FLOW_WAIT_POS_CHECK, _T("_eORIGIN_LOADER_Y_FLOW_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eORIGIN_LOADER_Y_FLOW_WAIT_POS_CHECK:
			if (Devs::m_LoaderMotion.Is_LoaderY_WaitPos())
			{
				SetStep(_eORIGIN_LOADER_Y_FLOW_DONE, _T("_eORIGIN_LOADER_Y_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eORIGIN_LOADER_Y_FLOW_WAIT_POS_CHECK : Time Out !!!"), eORIGIN_LOADER_Y_FLOW + 1);
				SetStep(_eORIGIN_LOADER_Y_FLOW_ERROR, _T("_eORIGIN_LOADER_Y_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eORIGIN_LOADER_Y_FLOW_WAIT_POS_CHECK, _T("_eORIGIN_LOADER_Y_FLOW_WAIT_POS_CHECK"));
			}
			break;

		case _eORIGIN_LOADER_Y_FLOW_DONE:
		{
			m_bFlowDone = TRUE;

			SetStep(_eORIGIN_LOADER_Y_FLOW_IDLE, _T("(_eORIGIN_LOADER_Y_FLOW_IDLE"));
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

BOOL COrigin_LoaderY_Flow::FlowInterlock()
{
	CString Str = _T("");
	double dPos = 0.0;

	if (SharedInfo::GetServoOnStatus(AXIS_LOADER_YL) != TRUE)
	{
		Total_Msg(_T("Loader YL Servo On Check !!!"));
		SharedInfo::SetAlarm(_T("Origin_LoaderY_Flow : Loader YL Servo On Check !!!"), eORIGIN_LOADER_Y_FLOW + 20);
		return FALSE;
	}


	//dPos = SharedInfo::GetActPos(AXIS_VIRTUAL_GANTRY_Y);
	////if (dPos < CManualData::m_ManualDataGantry.Info.m_dGantry_Y_Paper_Unload_Pos)
	//if (dPos < CManualData::m_ManualDataGantry.Info.m_dGantry_Y_Wait_Pos)
	//{
	//	Total_Msg(_T("Gantry Y Paper Unload Pos Check !!!"));
	//	SharedInfo::SetAlarm(_T("Origin_LoaderY_Flow : Gantry Y Paper Unload Pos Check !!!"), eORIGIN_LOADER_Y_FLOW + 22);
	//	return FALSE;
	//}

	return TRUE;
}