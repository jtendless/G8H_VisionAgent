#include "stdafx.h"
#include "Ready_LoaderFlow.h"
#include "Log/Logger.h"
#include "Vision/Devs.h"
#include "Data/ModelData.h"
#include "CamAreaModul.h"
#include "Data/SystemData.h"
#include "VisionAgentDlg.h"

CReady_LoaderFlow::CReady_LoaderFlow()
{
}


CReady_LoaderFlow::~CReady_LoaderFlow()
{
}

BOOL CReady_LoaderFlow::InitProcess()
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
BOOL CReady_LoaderFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eREADY_LOADER_FLOW_IDLE);

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
BOOL CReady_LoaderFlow::Start()
{
	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(_eREADY_LOADER_FLOW_START, _T("_eREADY_LOADER_FLOW_START"));
	return TRUE;
}
BOOL CReady_LoaderFlow::Stop()
{
	m_bStopBit = TRUE;
	SetStop(); //!!
	return TRUE;
}
UINT CReady_LoaderFlow::ThreadFunction(LPVOID lpParam)
{
	CReady_LoaderFlow* pFlow = NULL;

	pFlow = (CReady_LoaderFlow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}

VOID CReady_LoaderFlow::ThreadFunctionEntry(VOID)
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

			SetCurrentStep(_eREADY_LOADER_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}


		switch (GetCurrentTotalStep())
		{
		case _eREADY_LOADER_FLOW_IDLE:
		{
			break;
		}
		case _eREADY_LOADER_FLOW_START:
		{
			SetStep(_eREADY_LOADER_FLOW_INTERLOCK_CHECK, _T("_eREADY_LOADER_FLOW_INTERLOCK_CHECK"));
			break;
		}

		case _eREADY_LOADER_FLOW_INTERLOCK_CHECK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(_eREADY_LOADER_FLOW_ERROR, _T("_eREADY_LOADER_FLOW_ERROR"));
			}
			else
			{
				SetStep(_eREADY_LOADER_FLOW_LOADER_Z_UP, _T("_eREADY_LOADER_FLOW_LOADER_Z_UP"));
			}
			break;

		case _eREADY_LOADER_FLOW_LOADER_Z_UP:
			Devs::m_LoaderMotion.LoaderZ_WaitPos();
			Sleep(10); //!!

			SetStep(_eREADY_LOADER_FLOW_LOADER_Z_UP_CHECK, _T("_eREADY_LOADER_FLOW_LOADER_Z_UP_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eREADY_LOADER_FLOW_LOADER_Z_UP_CHECK:
			if (Devs::m_LoaderMotion.Is_LoaderZ_WaitPos())
			{
				SetStep(_eREADY_LOADER_FLOW_LOADER_X_WAIT_POS, _T("_eREADY_LOADER_FLOW_LOADER_X_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eREADY_LOADER_FLOW_LOADER_Z_UP_CHECK : Time Out !!!"), eREADY_LOADER_FLOW + 1);
				SetStep(_eREADY_LOADER_FLOW_ERROR, _T("_eREADY_LOADER_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eREADY_LOADER_FLOW_LOADER_Z_UP_CHECK, _T("_eREADY_LOADER_FLOW_LOADER_Z_UP_CHECK"));
			}
			break;

		case _eREADY_LOADER_FLOW_LOADER_X_WAIT_POS:
			Devs::m_LoaderMotion.LoaderX_WaitPos();
			Sleep(10); //!!

			SetStep(_eREADY_LOADER_FLOW_LOADER_X_WAIT_POS_CHECK, _T("_eREADY_LOADER_FLOW_LOADER_X_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eREADY_LOADER_FLOW_LOADER_X_WAIT_POS_CHECK:
			if (Devs::m_LoaderMotion.Is_LoaderX_WaitPos())
			{
				SetStep(_eREADY_LOADER_FLOW_LOADER_Y_WAIT_POS, _T("_eREADY_LOADER_FLOW_LOADER_Y_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eREADY_LOADER_FLOW_LOADER_X_WAIT_POS_CHECK : Time Out !!!"), eREADY_LOADER_FLOW + 2);
				SetStep(_eREADY_LOADER_FLOW_ERROR, _T("_eREADY_LOADER_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eREADY_LOADER_FLOW_LOADER_X_WAIT_POS_CHECK, _T("_eREADY_LOADER_FLOW_LOADER_X_WAIT_POS_CHECK"));
			}
			break;

		case _eREADY_LOADER_FLOW_LOADER_Y_WAIT_POS:
			Devs::m_LoaderMotion.LoaderY_WaitPos();
			Sleep(10); //!!

			SetStep(_eREADY_LOADER_FLOW_LOADER_Y_WAIT_POS_CHECK, _T("_eREADY_LOADER_FLOW_LOADER_Y_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eREADY_LOADER_FLOW_LOADER_Y_WAIT_POS_CHECK:
			if (Devs::m_LoaderMotion.Is_LoaderY_WaitPos())
			{
				SetStep(_eREADY_LOADER_FLOW_DONE, _T("_eREADY_LOADER_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eREADY_LOADER_FLOW_LOADER_Y_WAIT_POS_CHECK : Time Out !!!"), eREADY_LOADER_FLOW + 3);
				SetStep(_eREADY_LOADER_FLOW_ERROR, _T("_eREADY_LOADER_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eREADY_LOADER_FLOW_LOADER_Y_WAIT_POS_CHECK, _T("_eREADY_LOADER_FLOW_LOADER_Y_WAIT_POS_CHECK"));
			}
			break;

		case _eREADY_LOADER_FLOW_ERROR:
			break;

		case _eREADY_LOADER_FLOW_DONE:
		{
			m_bFlowDone = TRUE;

			SetStep(_eREADY_LOADER_FLOW_IDLE, _T("_eREADY_LOADER_FLOW_IDLE"));
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

BOOL CReady_LoaderFlow::FlowInterlock()
{
	CString Str = _T("");
	int i = 0;

#pragma region //Loader Vac Off Check
	if (Devs::m_LoaderMotion.Is_Stick_Active_Vac_On() == TRUE)
	{
		SharedInfo::SetAlarm(_T("Ready_LoaderFlow : Vac On !!!"), eREADY_LOADER_FLOW + 10);
		return FALSE;
	}

	if (Devs::m_LoaderMotion.CheckLoaderFlowInterlock(_T("Ready_LoaderFlow"), eREADY_LOADER_FLOW, 20) == FALSE)
	{
		return FALSE;
	}
#pragma endregion



	return TRUE;
}