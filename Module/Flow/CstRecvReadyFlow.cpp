#include "stdafx.h"
#include "CstRecvReadyFlow.h"
#include "Log/Logger.h"
#include "Vision/Devs.h"
#include "Data/ModelData.h"
#include "CamAreaModul.h"
#include "Data/SystemData.h"
#include "VisionAgentDlg.h"

CCstRecvReadyFlow::CCstRecvReadyFlow()
{
}


CCstRecvReadyFlow::~CCstRecvReadyFlow()
{
}

BOOL CCstRecvReadyFlow::InitProcess()
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
BOOL CCstRecvReadyFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eCST_RECV_READY_FLOW_IDLE);

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
BOOL CCstRecvReadyFlow::Start(enum_CassetteFloor eFloor)
{
	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;

	m_eTargetFloor = eFloor;

	SetStep(_eCST_RECV_READY_FLOW_START, _T("_eCST_RECV_READY_FLOW_START"));
	return TRUE;
}
BOOL CCstRecvReadyFlow::Stop()
{
	m_bStopBit = TRUE;
	SetStop(); //!!
	return TRUE;
}
UINT CCstRecvReadyFlow::ThreadFunction(LPVOID lpParam)
{
	CCstRecvReadyFlow* pFlow = NULL;

	pFlow = (CCstRecvReadyFlow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}
VOID CCstRecvReadyFlow::ThreadFunctionEntry(VOID)
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

			SetCurrentStep(_eCST_RECV_READY_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}


		switch (GetCurrentTotalStep())
		{
		case _eCST_RECV_READY_FLOW_IDLE:
		{
			break;
		}
		case _eCST_RECV_READY_FLOW_START:
		{
			SetStep(_eCST_RECV_READY_FLOW_INTERLOCK_CHECK, _T("_eCST_RECV_READY_FLOW_INTERLOCK_CHECK"));
			break;
		}

		case _eCST_RECV_READY_FLOW_INTERLOCK_CHECK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(_eCST_RECV_READY_FLOW_ERROR, _T("_eCST_RECV_READY_FLOW_ERROR"));
			}
			else
			{
				SetStep(_eCST_RECV_READY_FLOW_CST_Z_RECV_POS, _T("_eCST_RECV_READY_FLOW_CST_Z_RECV_POS"));
			}
			break;

		case _eCST_RECV_READY_FLOW_CST_Z_RECV_POS:
			Devs::m_CassetteMotion.CassetteZ_MoveFloor(m_eTargetFloor);

			SetStep(_eCST_RECV_READY_FLOW_CST_Z_RECV_POS_CHECK, _T("_eCST_RECV_READY_FLOW_CST_Z_RECV_POS_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eCST_RECV_READY_FLOW_CST_Z_RECV_POS_CHECK:
			if (Devs::m_CassetteMotion.Is_CassetteZ_Floor(m_eTargetFloor))
			{
				SetStep(_eCST_RECV_READY_FLOW_CST_PICKUP_UNIT_UNCLMAP_1ST, _T("_eCST_RECV_READY_FLOW_CST_PICKUP_UNIT_UNCLMAP_1ST"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eCST_RECV_READY_FLOW_CST_Z_RECV_POS_CHECK : Time Out"), eCST_RECV_READY_FLOW + 22);
				SetStep(_eCST_RECV_READY_FLOW_ERROR, _T("_eCST_RECV_READY_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eCST_RECV_READY_FLOW_CST_Z_RECV_POS_CHECK, _T("_eCST_RECV_READY_FLOW_CST_Z_RECV_POS_CHECK"));
			}
			break;

		case _eCST_RECV_READY_FLOW_CST_PICKUP_UNIT_UNCLMAP_1ST:
			Devs::m_CassetteMotion.CSTPickUpUnitUnclamp();
			Sleep(500); //!!

			SetStep(_eCST_RECV_READY_FLOW_CST_PICKUP_UNIT_UNCLMAP_1ST_CHECK, _T("_eCST_RECV_READY_FLOW_CST_PICKUP_UNIT_UNCLMAP_1ST_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eCST_RECV_READY_FLOW_CST_PICKUP_UNIT_UNCLMAP_1ST_CHECK:
			if (Devs::m_CassetteMotion.Is_CSTPickUpUnitUnclamp())
			{
				SetStep(_eCST_RECV_READY_FLOW_CST_PICKUP_UNIT_FWD_1ST, _T("_eCST_RECV_READY_FLOW_CST_PICKUP_UNIT_FWD_1ST"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eCST_RECV_READY_FLOW_CST_PICKUP_UNIT_UNCLMAP_1ST_CHECK Time Out !!!"), eCST_RECV_READY_FLOW + 10);
				SetStep(_eCST_RECV_READY_FLOW_ERROR, _T("_eCST_RECV_READY_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eCST_RECV_READY_FLOW_CST_PICKUP_UNIT_UNCLMAP_1ST_CHECK, _T("_eCST_RECV_READY_FLOW_CST_PICKUP_UNIT_UNCLMAP_1ST_CHECK"));
			}
			break;

		case _eCST_RECV_READY_FLOW_CST_PICKUP_UNIT_FWD_1ST:
			Devs::m_CassetteMotion.CSTPickUpUnitFwd();
			Sleep(500); //!!

			SetStep(_eCST_RECV_READY_FLOW_CST_PICKUP_UNIT_FWD_1ST_CHECK, _T("_eCST_RECV_READY_FLOW_CST_PICKUP_UNIT_FWD_1ST_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eCST_RECV_READY_FLOW_CST_PICKUP_UNIT_FWD_1ST_CHECK:
			if (Devs::m_CassetteMotion.Is_CSTPickUpUnitFwd())
			{
				SetStep(_eCST_RECV_READY_FLOW_CST_PICKUP_UNIT_CLMAP, _T("_eCST_RECV_READY_FLOW_CST_PICKUP_UNIT_CLMAP"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eCST_RECV_READY_FLOW_CST_PICKUP_UNIT_FWD_1ST_CHECK Time Out !!!"), eCST_RECV_READY_FLOW + 11);
				SetStep(_eCST_RECV_READY_FLOW_ERROR, _T("_eCST_RECV_READY_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eCST_RECV_READY_FLOW_CST_PICKUP_UNIT_FWD_1ST_CHECK, _T("_eCST_RECV_READY_FLOW_CST_PICKUP_UNIT_FWD_1ST_CHECK"));
			}
			break;

		case _eCST_RECV_READY_FLOW_CST_PICKUP_UNIT_CLMAP:
			Devs::m_CassetteMotion.CSTPickUpUnitClamp();
			Sleep(500); //!!

			SetStep(_eCST_RECV_READY_FLOW_CST_PICKUP_UNIT_CLMAP_CHECK, _T("_eCST_RECV_READY_FLOW_CST_PICKUP_UNIT_CLMAP_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eCST_RECV_READY_FLOW_CST_PICKUP_UNIT_CLMAP_CHECK:
			if (Devs::m_CassetteMotion.Is_CSTPickUpUnitClamp())
			{
				SetStep(_eCST_RECV_READY_FLOW_CST_PICKUP_UNIT_BWD_1ST, _T("_eCST_RECV_READY_FLOW_CST_PICKUP_UNIT_BWD_1ST"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eCST_RECV_READY_FLOW_CST_PICKUP_UNIT_CLMAP_CHECK Time Out !!!"), eCST_RECV_READY_FLOW + 12);
				SetStep(_eCST_RECV_READY_FLOW_ERROR, _T("_eCST_RECV_READY_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eCST_RECV_READY_FLOW_CST_PICKUP_UNIT_CLMAP_CHECK, _T("_eCST_RECV_READY_FLOW_CST_PICKUP_UNIT_CLMAP_CHECK"));
			}
			break;

		case _eCST_RECV_READY_FLOW_CST_PICKUP_UNIT_BWD_1ST:
			Devs::m_CassetteMotion.CSTPickUpUnitBwd();
			Sleep(500); //!!

			SetStep(_eCST_RECV_READY_FLOW_CST_PICKUP_UNIT_BWD_1ST_CHECK, _T("_eCST_RECV_READY_FLOW_CST_PICKUP_UNIT_BWD_1ST_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eCST_RECV_READY_FLOW_CST_PICKUP_UNIT_BWD_1ST_CHECK:
			if (Devs::m_CassetteMotion.Is_CSTPickUpUnitBwd())
			{
				if (SharedInfo::DInputValue[_DIN_MAGAZINE_EXIST_DETECT_L] == FALSE)
				{
					SharedInfo::SetAlarm(_T("_eCST_RECV_READY_FLOW_CST_PICKUP_UNIT_BWD_1ST_CHECK Cst Unsafe Pos Detect Off Error !!!"), eCST_RECV_READY_FLOW + 13);
					SetStep(_eCST_RECV_READY_FLOW_ERROR, _T("_eCST_RECV_READY_FLOW_ERROR"));
				}
				else if (SharedInfo::DInputValue[_DIN_MAGAZINE_EXIST_DETECT_R] == FALSE)
				{
					SharedInfo::SetAlarm(_T("_eCST_RECV_READY_FLOW_CST_PICKUP_UNIT_BWD_1ST_CHECK Cst Backward Detect Off Error !!!"), eCST_RECV_READY_FLOW + 14);
					SetStep(_eCST_RECV_READY_FLOW_ERROR, _T("_eCST_RECV_READY_FLOW_ERROR"));
				}
				else
				{
					SetStep(_eCST_RECV_READY_FLOW_DONE, _T("_eCST_RECV_READY_FLOW_DONE"));
				}
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eCST_RECV_READY_FLOW_CST_PICKUP_UNIT_BWD_1ST_CHECK Time Out !!!"), eCST_RECV_READY_FLOW + 15);
				SetStep(_eCST_RECV_READY_FLOW_ERROR, _T("_eCST_RECV_READY_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eCST_RECV_READY_FLOW_CST_PICKUP_UNIT_BWD_1ST_CHECK, _T("_eCST_RECV_READY_FLOW_CST_PICKUP_UNIT_BWD_1ST_CHECK"));
			}
			break;

		case _eCST_RECV_READY_FLOW_ERROR:
			
			break;

		case _eCST_RECV_READY_FLOW_DONE:
		{
			m_bFlowDone = TRUE;

			SetStep(_eCST_RECV_READY_FLOW_IDLE, _T("_eCST_RECV_READY_FLOW_IDLE"));			
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

BOOL CCstRecvReadyFlow::FlowInterlock()
{
	CString Str = _T("");
	int i = 0;

#pragma region //Interlock
	if (SharedInfo::DInputValue[_DIN_MAGAZINE_EXIST_DETECT_L])
	{
		SharedInfo::SetAlarm(_T("CstRecvReadyFlow : Check _DIN_MAGAZINE_EXIST_DETECT_L Status !!!"), eCST_RECV_READY_FLOW + 0);
		return FALSE;
	}
	if (SharedInfo::DInputValue[_DIN_MAGAZINE_EXIST_DETECT_R])
	{
		SharedInfo::SetAlarm(_T("CstRecvReadyFlow : Check _DIN_MAGAZINE_EXIST_DETECT_R Status !!!"), eCST_RECV_READY_FLOW + 1);
		return FALSE;
	}
	if (SharedInfo::DInputValue[_DIN_PICK_UP_UNIT_BWD] == FALSE)
	{
		SharedInfo::SetAlarm(_T("CstRecvReadyFlow : Check _DIN_PICK_UP_UNIT_BWD Status !!!"), eCST_RECV_READY_FLOW + 2);
		return FALSE;
	}

	if (Devs::m_UnloaderMotion.Is_UnloaderZ_WaitPos() == FALSE)
	{
		SharedInfo::SetAlarm(_T("CstRecvReadyFlow : Check StickUnloaderZ Not Wait Pos !!!"), eCST_RECV_READY_FLOW + 3);
		return FALSE;
	}
#pragma endregion

	return TRUE;
}