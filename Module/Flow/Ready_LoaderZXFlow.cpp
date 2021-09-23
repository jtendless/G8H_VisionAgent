#include "stdafx.h"
#include "Ready_LoaderZXFlow.h"
#include "Log/Logger.h"
#include "Vision/Devs.h"
#include "Data/ModelData.h"
#include "CamAreaModul.h"
#include "Data/SystemData.h"
#include "VisionAgentDlg.h"

CReady_LoaderZXFlow::CReady_LoaderZXFlow()
{
}


CReady_LoaderZXFlow::~CReady_LoaderZXFlow()
{
}

BOOL CReady_LoaderZXFlow::InitProcess()
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
BOOL CReady_LoaderZXFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eREADY_LOADER_ZX_FLOW_IDLE);

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
BOOL CReady_LoaderZXFlow::Start()
{
	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(_eREADY_LOADER_ZX_FLOW_START, _T("_eREADY_LOADER_ZX_FLOW_START"));
	return TRUE;
}
BOOL CReady_LoaderZXFlow::Stop()
{
	m_bStopBit = TRUE;
	SetStop(); //!!
	return TRUE;
}
UINT CReady_LoaderZXFlow::ThreadFunction(LPVOID lpParam)
{
	CReady_LoaderZXFlow* pFlow = NULL;

	pFlow = (CReady_LoaderZXFlow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}

VOID CReady_LoaderZXFlow::ThreadFunctionEntry(VOID)
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

			SetCurrentStep(_eREADY_LOADER_ZX_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}


		switch (GetCurrentTotalStep())
		{
		case _eREADY_LOADER_ZX_FLOW_IDLE:
		{
			break;
		}
		case _eREADY_LOADER_ZX_FLOW_START:
		{
			SetStep(_eREADY_LOADER_ZX_FLOW_INTERLOCK_CHECK, _T("_eREADY_LOADER_ZX_FLOW_INTERLOCK_CHECK"));
			break;
		}

		case _eREADY_LOADER_ZX_FLOW_INTERLOCK_CHECK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(_eREADY_LOADER_ZX_FLOW_ERROR, _T("_eREADY_LOADER_ZX_FLOW_ERROR"));
			}
			else
			{
				SetStep(_eREADY_LOADER_ZX_FLOW_LOADER_Z_WAIT_POS, _T("_eREADY_LOADER_ZX_FLOW_LOADER_Z_WAIT_POS"));
			}
			break;

		case _eREADY_LOADER_ZX_FLOW_LOADER_Z_WAIT_POS:
			Devs::m_LoaderMotion.LoaderZ_WaitPos();
			Sleep(10); //!!

			SetStep(_eREADY_LOADER_ZX_FLOW_LOADER_Z_WAIT_POS_CHECK, _T("_eREADY_LOADER_ZX_FLOW_LOADER_Z_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eREADY_LOADER_ZX_FLOW_LOADER_Z_WAIT_POS_CHECK:
			if (Devs::m_LoaderMotion.Is_LoaderZ_WaitPos())
			{
				SetStep(_eREADY_LOADER_ZX_FLOW_LOADER_X_WAIT_POS, _T("_eREADY_LOADER_ZX_FLOW_LOADER_X_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eREADY_LOADER_ZX_FLOW_LOADER_Z_WAIT_POS_CHECK : Time Out !!!"), eREADY_LOADER_FLOW + 1);
				SetStep(_eREADY_LOADER_ZX_FLOW_ERROR, _T("_eREADY_LOADER_ZX_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eREADY_LOADER_ZX_FLOW_LOADER_Z_WAIT_POS_CHECK, _T("_eREADY_LOADER_ZX_FLOW_LOADER_Z_WAIT_POS_CHECK"));
			}
			break;

		case _eREADY_LOADER_ZX_FLOW_LOADER_X_WAIT_POS:
			Devs::m_LoaderMotion.LoaderX_WaitPos();
			Sleep(10); //!!

			SetStep(_eREADY_LOADER_ZX_FLOW_LOADER_X_WAIT_POS_CHECK, _T("_eREADY_LOADER_ZX_FLOW_LOADER_X_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eREADY_LOADER_ZX_FLOW_LOADER_X_WAIT_POS_CHECK:
			if (Devs::m_LoaderMotion.Is_LoaderX_WaitPos())
			{
				SetStep(_eREADY_LOADER_ZX_FLOW_DONE, _T("_eREADY_LOADER_ZX_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eREADY_LOADER_ZX_FLOW_LOADER_X_WAIT_POS_CHECK : Time Out !!!"), eREADY_LOADER_FLOW + 2);
				SetStep(_eREADY_LOADER_ZX_FLOW_ERROR, _T("_eREADY_LOADER_ZX_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eREADY_LOADER_ZX_FLOW_LOADER_X_WAIT_POS_CHECK, _T("_eREADY_LOADER_ZX_FLOW_LOADER_X_WAIT_POS_CHECK"));
			}
			break;

		case _eREADY_LOADER_ZX_FLOW_ERROR:
			break;

		case _eREADY_LOADER_ZX_FLOW_DONE:
		{
			m_bFlowDone = TRUE;

			SetStep(_eREADY_LOADER_ZX_FLOW_IDLE, _T("_eREADY_LOADER_ZX_FLOW_IDLE"));
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

BOOL CReady_LoaderZXFlow::FlowInterlock()
{
	CString Str = _T("");
	int i = 0;

#pragma region //Loader Vac Off Check
	if (Devs::m_LoaderMotion.Is_Stick_Active_Vac_On() == TRUE)
	{
		SharedInfo::SetAlarm(_T("Ready_LoaderFlow : Vac On !!!"), eREADY_LOADER_FLOW + 10);
		return FALSE;
	}

	//Servo On Check
	if (SharedInfo::GetServoOnStatus(AXIS_LOADER_Z) == FALSE)
	{
		SharedInfo::SetAlarm(_T("Ready_LoaderFlow : Check Loader Z Servo On !!!"), eREADY_LOADER_FLOW + 10);
		return FALSE;
	}
	else if (SharedInfo::GetServoOnStatus(AXIS_LOADER_X) == FALSE)
	{
		SharedInfo::SetAlarm(_T("Ready_LoaderFlow : Check Loader X Servo On !!!"), eREADY_LOADER_FLOW + 10);
		return FALSE;
	}

	//Home Status Check
	if (SharedInfo::GetHomeStatus(AXIS_LOADER_Z) == FALSE)
	{
		SharedInfo::SetAlarm(_T("Ready_LoaderFlow : Check Loader Z Home Status !!!"), eREADY_LOADER_FLOW + 10);
		return FALSE;
	}
	else if (SharedInfo::GetHomeStatus(AXIS_LOADER_X) == FALSE)
	{
		SharedInfo::SetAlarm(_T("Ready_LoaderFlow : Check Loader X Home Status !!!"), eREADY_LOADER_FLOW + 10);
		return FALSE;
	}
#pragma endregion



	return TRUE;
}