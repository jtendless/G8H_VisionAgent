#include "stdafx.h"
#include "PPAFlow.h"
#include "Log/Logger.h"
#include "Vision/Devs.h"
#include "Data/ModelData.h"
#include "CamAreaModul.h"
#include "Data/SystemData.h"

CPPAFlow::CPPAFlow()
{
}


CPPAFlow::~CPPAFlow()
{
}

BOOL CPPAFlow::InitProcess()
{
	m_StateComplete = NULL;
	m_FlowFinish = TRUE;
	m_bTerminate = FALSE;
	m_bFlowDone = TRUE;

	//SetProcessLog(LogMsg_Process);
	//SetAlarmLog(LogMsg_Alarm);

	hHandle = CreateEvent(NULL, TRUE, FALSE, NULL);
	SetHandle(hHandle);
	pThread = AfxBeginThread(ThreadFunction, this);
	//pMappingProc = CMappingProc::GetInstance();
	return TRUE;
}
BOOL CPPAFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_ePPA_FLOW_IDLE);

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
BOOL CPPAFlow::Start()
{
	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(_ePPA_FLOW_START, _T("_ePPA_FLOW_START"));
	return TRUE;
}
BOOL CPPAFlow::Stop()
{
	m_bStopBit = TRUE;
	SetStop(); //!!
	return TRUE;
}
UINT CPPAFlow::ThreadFunction(LPVOID lpParam)
{
	CPPAFlow* pFlow = NULL;

	pFlow = (CPPAFlow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}
VOID CPPAFlow::ThreadFunctionEntry(VOID)
{
	DWORD	dwResult = 0;
	double	dStrt_Time = GetTickCount();
	double	dEnd_Time = GetTickCount();
	double	dWait_Time = GetTickCount();
	int		nWork_Mask_Mode = -1;
	int		nWork_Mask_Index = -1;
	BOOL	bComplete_Step = FALSE;
	
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
		case _ePPA_FLOW_IDLE:
		{
			break;
		}
		case _ePPA_FLOW_START:
		{
			break;
		}
		case _ePPA_FLOW_DONE:
		{
			m_bFlowDone = TRUE;
			SetStep(_ePPA_FLOW_DONE, _T("_ePPA_FLOW_DONE"));
			break;
		}
		case _ePPA_FLOW_STOP:
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