#include "stdafx.h"
#include "CstRecvDoneFlow.h"
#include "Log/Logger.h"
#include "Vision/Devs.h"
#include "Data/ModelData.h"
#include "CamAreaModul.h"
#include "Data/SystemData.h"
#include "VisionAgentDlg.h"

CCstRecvDoneFlow::CCstRecvDoneFlow()
{
}


CCstRecvDoneFlow::~CCstRecvDoneFlow()
{
}

BOOL CCstRecvDoneFlow::InitProcess()
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
BOOL CCstRecvDoneFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eCST_RECV_DONE_FLOW_IDLE);

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
BOOL CCstRecvDoneFlow::Start()
{
	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(_eCST_RECV_DONE_FLOW_START, _T("_eCST_RECV_DONE_FLOW_START"));
	return TRUE;
}
BOOL CCstRecvDoneFlow::Stop()
{
	m_bStopBit = TRUE;
	SetStop(); //!!
	return TRUE;
}
UINT CCstRecvDoneFlow::ThreadFunction(LPVOID lpParam)
{
	CCstRecvDoneFlow* pFlow = NULL;

	pFlow = (CCstRecvDoneFlow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}
VOID CCstRecvDoneFlow::ThreadFunctionEntry(VOID)
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

			SetCurrentStep(_eCST_RECV_DONE_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}


		switch (GetCurrentTotalStep())
		{
		case _eCST_RECV_DONE_FLOW_IDLE:
		{
			break;
		}
		case _eCST_RECV_DONE_FLOW_START:
		{
			SetStep(_eCST_RECV_DONE_FLOW_INTERLOCK_CHECK, _T("_eCST_RECV_DONE_FLOW_INTERLOCK_CHECK"));
			break;
		}

		case _eCST_RECV_DONE_FLOW_INTERLOCK_CHECK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(_eCST_RECV_DONE_FLOW_ERROR, _T("_eCST_RECV_DONE_FLOW_ERROR"));
			}
			else
			{
				SetStep(_eCST_RECV_DONE_FLOW_CST_PICKUP_UNIT_FWD_2ND, _T("_eCST_RECV_DONE_FLOW_CST_PICKUP_UNIT_FWD_2ND"));
			}
			break;

		case _eCST_RECV_DONE_FLOW_CST_PICKUP_UNIT_FWD_2ND:
			Devs::m_CassetteMotion.CSTPickUpUnitFwd();
			Sleep(500); //!!

			SetStep(_eCST_RECV_DONE_FLOW_CST_PICKUP_UNIT_FWD_2ND_CHECK, _T("_eCST_RECV_DONE_FLOW_CST_PICKUP_UNIT_FWD_2ND_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eCST_RECV_DONE_FLOW_CST_PICKUP_UNIT_FWD_2ND_CHECK:
			if (Devs::m_CassetteMotion.Is_CSTPickUpUnitFwd())
			{
				SetStep(_eCST_RECV_DONE_FLOW_CST_PICKUP_UNIT_UNCLMAP_2ND, _T("_eCST_RECV_DONE_FLOW_CST_PICKUP_UNIT_UNCLMAP_2ND"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eCST_RECV_DONE_FLOW_CST_PICKUP_UNIT_FWD_2ND_CHECK Time Out !!!"), eCST_RECV_DONE_FLOW + 29);
				SetStep(_eCST_RECV_DONE_FLOW_ERROR, _T("_eCST_RECV_DONE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eCST_RECV_DONE_FLOW_CST_PICKUP_UNIT_FWD_2ND_CHECK, _T("_eCST_RECV_DONE_FLOW_CST_PICKUP_UNIT_FWD_2ND_CHECK"));
			}
			break;

		case _eCST_RECV_DONE_FLOW_CST_PICKUP_UNIT_UNCLMAP_2ND:
			Devs::m_CassetteMotion.CSTPickUpUnitUnclamp();
			Sleep(500); //!!

			SetStep(_eCST_RECV_DONE_FLOW_CST_PICKUP_UNIT_UNCLMAP_2ND_CHECK, _T("_eCST_RECV_DONE_FLOW_CST_PICKUP_UNIT_UNCLMAP_2ND_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eCST_RECV_DONE_FLOW_CST_PICKUP_UNIT_UNCLMAP_2ND_CHECK:
			if (Devs::m_CassetteMotion.Is_CSTPickUpUnitUnclamp())
			{
				SetStep(_eCST_RECV_DONE_FLOW_CST_PICKUP_UNIT_BWD_2ND, _T("_eCST_RECV_DONE_FLOW_CST_PICKUP_UNIT_BWD_2ND"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eCST_RECV_DONE_FLOW_CST_PICKUP_UNIT_UNCLMAP_2ND_CHECK Time Out !!!"), eCST_RECV_DONE_FLOW + 30);
				SetStep(_eCST_RECV_DONE_FLOW_ERROR, _T("_eCST_RECV_DONE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eCST_RECV_DONE_FLOW_CST_PICKUP_UNIT_UNCLMAP_2ND_CHECK, _T("_eCST_RECV_DONE_FLOW_CST_PICKUP_UNIT_UNCLMAP_2ND_CHECK"));
			}
			break;

		case _eCST_RECV_DONE_FLOW_CST_PICKUP_UNIT_BWD_2ND:
			Devs::m_CassetteMotion.CSTPickUpUnitBwd();
			Sleep(500); //!!

			SetStep(_eCST_RECV_DONE_FLOW_CST_PICKUP_UNIT_BWD_2ND_CHECK, _T("_eCST_RECV_DONE_FLOW_CST_PICKUP_UNIT_BWD_2ND_CHECK"));
			break;

		case _eCST_RECV_DONE_FLOW_CST_PICKUP_UNIT_BWD_2ND_CHECK:
			if (Devs::m_CassetteMotion.Is_CSTPickUpUnitBwd())
			{
				if (SharedInfo::DInputValue[_DIN_MAGAZINE_EXIST_DETECT_L])
				{
					SharedInfo::SetAlarm(_T("_eCST_RECV_DONE_FLOW_CST_PICKUP_UNIT_BWD_2ND_CHECK Cst Unsafe Pos Detect On Error !!!"), eCST_RECV_READY_FLOW + 13);
					SetStep(_eCST_RECV_DONE_FLOW_ERROR, _T("_eCST_RECV_READY_FLOW_ERROR"));
				}
				else if (SharedInfo::DInputValue[_DIN_MAGAZINE_EXIST_DETECT_R])
				{
					SharedInfo::SetAlarm(_T("_eCST_RECV_DONE_FLOW_CST_PICKUP_UNIT_BWD_2ND_CHECK Cst Backward Detect On Error !!!"), eCST_RECV_READY_FLOW + 14);
					SetStep(_eCST_RECV_DONE_FLOW_ERROR, _T("_eCST_RECV_READY_FLOW_ERROR"));
				}
				else
				{
					SetStep(_eCST_RECV_DONE_FLOW_DONE, _T("_eCST_RECV_DONE_FLOW_DONE"));
				}
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eCST_RECV_DONE_FLOW_CST_PICKUP_UNIT_BWD_2ND_CHECK Time Out !!!"), eCST_RECV_DONE_FLOW + 32);
				SetStep(_eCST_RECV_DONE_FLOW_ERROR, _T("_eCST_RECV_DONE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eCST_RECV_DONE_FLOW_CST_PICKUP_UNIT_BWD_2ND_CHECK, _T("_eCST_RECV_DONE_FLOW_CST_PICKUP_UNIT_BWD_2ND_CHECK"));
			}
			break;

		case _eCST_RECV_DONE_FLOW_ERROR:
			
			break;

		case _eCST_RECV_DONE_FLOW_DONE:
		{
			m_bFlowDone = TRUE;

			SetStep(_eCST_RECV_DONE_FLOW_IDLE, _T("_eCST_RECV_DONE_FLOW_IDLE"));			
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

BOOL CCstRecvDoneFlow::FlowInterlock()
{
	CString Str = _T("");
	int i = 0;

#pragma region //Interlock
	//if (SharedInfo::DInputValue[_DIN_MAGAZINE_EXIST_DETECT_L] == FALSE)
	//{
	//	SharedInfo::SetAlarm(_T("CstRecvReadyFlow : Check _DIN_MAGAZINE_EXIST_DETECT_L Status !!!"), eCST_RECV_READY_FLOW);
	//	return FALSE;
	//}
	//if (SharedInfo::DInputValue[_DIN_MAGAZINE_EXIST_DETECT_R] == FALSE)
	//{
	//	SharedInfo::SetAlarm(_T("CstRecvReadyFlow : Check _DIN_MAGAZINE_EXIST_DETECT_R Status !!!"), eCST_RECV_READY_FLOW);
	//	return FALSE;
	//}

	if (Devs::m_UnloaderMotion.Is_UnloaderZ_WaitPos() == FALSE)
	{
		SharedInfo::SetAlarm(_T("CstRecvReadyFlow : Check StickUnloaderZ Not Wait Pos !!!"), eCST_RECV_READY_FLOW + 3);
		return FALSE;
	}
#pragma endregion

	return TRUE;
}