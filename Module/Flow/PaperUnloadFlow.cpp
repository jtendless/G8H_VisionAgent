#include "stdafx.h"
#include "PaperUnloadFlow.h"
#include "Log/Logger.h"
#include "Vision/Devs.h"
#include "Data/ModelData.h"
#include "Data/ManualData.h"
#include "Data/MachineData.h"
#include "CamAreaModul.h"
#include "Data/SystemData.h"
//#include "../WkLibFlow/WkLibFlow.h"
#include "Flow/BaseFlow.h"
#include "FmmLight1.h"

CPaperUnloadFlow::CPaperUnloadFlow()
{
}


CPaperUnloadFlow::~CPaperUnloadFlow()
{
}

BOOL CPaperUnloadFlow::InitProcess()
{
	m_StateComplete = NULL;
	m_FlowFinish = TRUE;
	m_bTerminate = FALSE;
	m_bFlowDone = TRUE;

	m_dTargetPosZ = 0.0;
	m_dTargetPosX = 0.0;

#pragma region //Step Group
	int nGroupIndex = 0;

	m_sGroupInfo[nGroupIndex].m_bProcessingFlag = FALSE;
	m_sGroupInfo[nGroupIndex].nStartStep = _ePAPER_UNLOAD_FLOW_START;
	m_sGroupInfo[nGroupIndex].nEndStep = _ePAPER_UNLOAD_FLOW_INTERLOCK;
	m_sGroupInfo[nGroupIndex].strGroupName.Format(_T("%d. Start"), nGroupIndex + 1);
	nGroupIndex++;

	m_nMaxGroupCount = nGroupIndex;

#pragma region //KJT 20210221
	m_nGroupStepIndex = 0;
	for (int i = 0; i < m_nMaxGroupCount; i++)
	{
		m_bGroupStepDone[i] = FALSE;
	}
#pragma endregion
#pragma endregion

	hHandle = CreateEvent(NULL, TRUE, FALSE, NULL);
	SetHandle(hHandle);
	pThread = AfxBeginThread(ThreadFunction, this);
	//pMappingProc = CMappingProc::GetInstance();
	return TRUE;
}

BOOL CPaperUnloadFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_ePAPER_UNLOAD_FLOW_IDLE, _T("_ePAPER_UNLOAD_FLOW_IDLE"));

	if (hHandle != NULL)
	{
		CloseHandle(hHandle);
		hHandle = NULL;
	}

	return TRUE;
}
BOOL CPaperUnloadFlow::Start(enum_CassetteFloor eTargetFloor)
{
	m_nStepDownCount = 0;
	m_nVibrationCount = 0;
	m_nMaxStepDownCount = CManualData::m_ManualDataLoader.Info.m_nLoaderZ_StepDownCount;
	m_nMaxVibrationCount = CManualData::m_ManualDataLoader.Info.m_nLoaderZ_VibrationCount;

	m_eTargetFloor = eTargetFloor;

	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(_ePAPER_UNLOAD_FLOW_START, _T("_ePAPER_UNLOAD_FLOW_START"));
	return TRUE;
}
BOOL CPaperUnloadFlow::Stop()
{
	m_bStopBit = TRUE;
	return TRUE;
}
UINT CPaperUnloadFlow::ThreadFunction(LPVOID lpParam)
{
	CPaperUnloadFlow* pFlow = NULL;

	pFlow = (CPaperUnloadFlow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}
VOID CPaperUnloadFlow::ThreadFunctionEntry(VOID)
{
	DWORD	dwResult = 0;
	double	dStrt_Time = GetTickCount();
	double	dEnd_Time = GetTickCount();
	double	dWait_Time = GetTickCount();
	int		nWork_Mask_Mode = -1;
	int		nWork_Mask_Index = -1;
	BOOL	bComplete_Step = FALSE;
	double dOffset = 0.0;

	double dVel = 20.0;
	double dAccel = 20.0;
	double dDecel = 20.0;

	CString Str = _T("");
	int nSafetyPosErrorBy = -1;

	while (m_FlowFinish)
	{
		WaitForSingleObject(hHandle, INFINITE);
		ResetEvent(hHandle);

		if (SharedInfo::bMachineStopFlag == TRUE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(_ePAPER_UNLOAD_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}

		switch (GetCurrentTotalStep())
		{
		case _ePAPER_UNLOAD_FLOW_IDLE:
		{
			break;
		}
		case _ePAPER_UNLOAD_FLOW_START:
		{
			m_timeStart = CTime::GetCurrentTime(); //KJT 20210329
			SharedInfo::m_timeUnitTact = m_timeStart;

			SharedInfo::nCurFlowID = ePAPER_UNLOAD_FLOW;

			m_nStepDownCount = 0;
			m_nVibrationCount = 0; 
			m_nMaxStepDownCount = CManualData::m_ManualDataLoader.Info.m_nLoaderZ_StepDownCount;
			m_nMaxVibrationCount = CManualData::m_ManualDataLoader.Info.m_nLoaderZ_VibrationCount;

			SharedInfo::LightAllOff();

#pragma region //KJT 20210221
			m_nGroupStepIndex = 0;
			for (int i = 0; i < m_nMaxGroupCount; i++)
			{
				m_bGroupStepDone[i] = FALSE;
			}
#pragma endregion

			SetStep(_ePAPER_UNLOAD_FLOW_INTERLOCK, _T("_ePAPER_UNLOAD_FLOW_INTERLOCK"));
			break;
		}
		case _ePAPER_UNLOAD_FLOW_INTERLOCK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(_ePAPER_UNLOAD_FLOW_ERROR, _T("_ePAPER_UNLOAD_FLOW_ERROR"));
			}
			else
			{
				SetStep(_ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_Y_PAPER_UNLOAD_POS, _T("_ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_Y_PAPER_UNLOAD_POS"));
			}
			break;

#pragma region //1. Paper Unload	
		case _ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_Y_PAPER_UNLOAD_POS:
			Devs::m_UnloaderMotion.PaperUnloaderY_All_UnloadPaperPos();

			SetStep(_ePAPER_UNLOAD_FLOW_CST_RECV_READY_MOVE, _T("_ePAPER_UNLOAD_FLOW_CST_RECV_READY_MOVE"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_Y_PAPER_UNLOAD_POS_CHECK:
			if (Devs::m_UnloaderMotion.Is_PaperUnloaderY_All_UnloadPaperPos())
			{
				SetStep(_ePAPER_UNLOAD_FLOW_CST_RECV_READY_DONE_CHECK, _T("_ePAPER_UNLOAD_FLOW_CST_RECV_READY_DONE_CHECK"));
			}
			//else if (IsTimeOut())
			//{
			//	SharedInfo::SetAlarm(_T("_ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_Y_PAPER_UNLOAD_POS_CHECK : Time Out"), ePAPER_UNLOAD_FLOW + 18);
			//	SetStep(_ePAPER_UNLOAD_FLOW_ERROR, _T("_ePAPER_UNLOAD_FLOW_ERROR"));
			//}
			else
			{
				SetCheckStep(_ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_Y_PAPER_UNLOAD_POS_CHECK, _T("_ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_Y_PAPER_UNLOAD_POS_CHECK"));
			}
			break;

		case _ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_Z_PAPER_UNLOAD_DOWN_POS:
			Devs::m_UnloaderMotion.PaperUnloaderZ_All_UnloadPaperPos();

			SetStep(_ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_Z_PAPER_UNLOAD_DOWN_POS_CHECK, _T("_ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_Z_PAPER_UNLOAD_DOWN_POS_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_Z_PAPER_UNLOAD_DOWN_POS_CHECK:
			if (Devs::m_UnloaderMotion.Is_PaperUnloaderZ_All_UnloadPaperPos())
			{
				SetStep(_ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_VAC_OFF, _T("_ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_VAC_OFF"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_Z_PAPER_UNLOAD_DOWN_POS_CHECK : Time Out"), ePAPER_UNLOAD_FLOW + 19);
				SetStep(_ePAPER_UNLOAD_FLOW_ERROR, _T("_ePAPER_UNLOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_Z_PAPER_UNLOAD_DOWN_POS_CHECK, _T("_ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_Z_PAPER_UNLOAD_DOWN_POS_CHECK"));
			}
			break;

		case _ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_VAC_OFF:
			Devs::m_UnloaderMotion.PaperUnloader_Active_Vac_Off();

			Sleep(500); //!!
			SetStep(_ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_VAC_OFF_CHECK, _T("_ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_VAC_OFF_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_VAC_OFF_CHECK:
			if (Devs::m_UnloaderMotion.Is_PaperUnloader_Active_Vac_Off())
			{
				SetStep(_ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_Z_FINISH_WAIT_POS, _T("_ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_Z_FINISH_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_VAC_OFF_CHECK : Time Out"), ePAPER_UNLOAD_FLOW + 20);
				SetStep(_ePAPER_UNLOAD_FLOW_ERROR, _T("_ePAPER_UNLOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_VAC_OFF_CHECK, _T("_ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_VAC_OFF_CHECK"));
			}
			break;

		case _ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_Z_FINISH_WAIT_POS:
			Devs::m_UnloaderMotion.PaperUnloaderZ_All_WaitPos();

			SetStep(_ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_Z_FINISH_WAIT_POS_CHECK, _T("_ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_Z_FINISH_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;	

		case _ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_Z_FINISH_WAIT_POS_CHECK:
			if (Devs::m_UnloaderMotion.Is_PaperUnloaderZ_All_WaitPos())
			{
				SetStep(_ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_Y_FINISH_WAIT_POS, _T("_ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_Y_FINISH_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_Z_FINISH_WAIT_POS_CHECK : Time Out"), ePAPER_UNLOAD_FLOW + 22);
				SetStep(_ePAPER_UNLOAD_FLOW_ERROR, _T("_ePAPER_UNLOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_Z_FINISH_WAIT_POS_CHECK, _T("_ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_Z_FINISH_WAIT_POS_CHECK"));
			}
			break;

		case _ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_Y_FINISH_WAIT_POS:
			Devs::m_UnloaderMotion.PaperUnloaderY_All_WaitPos();

			SetStep(_ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_Y_FINISH_WAIT_POS_CHECK, _T("_ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_Y_FINISH_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_Y_FINISH_WAIT_POS_CHECK:
			if (Devs::m_UnloaderMotion.Is_PaperUnloaderY_All_WaitPos())
			{
				SetStep(_ePAPER_UNLOAD_FLOW_CST_RECV_DONE_MOVE, _T("_ePAPER_UNLOAD_FLOW_CST_RECV_DONE_MOVE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_Y_FINISH_WAIT_POS_CHECK : Time Out"), ePAPER_UNLOAD_FLOW + 22);
				SetStep(_ePAPER_UNLOAD_FLOW_ERROR, _T("_ePAPER_UNLOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_Y_FINISH_WAIT_POS_CHECK, _T("_ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_Y_FINISH_WAIT_POS_CHECK"));
			}
			break;
#pragma endregion //1. Paper Unload

#pragma region //Cst Move
		case _ePAPER_UNLOAD_FLOW_CST_RECV_READY_MOVE:
			Devs::m_CstRecvReadyFlow.Start(m_eTargetFloor);
			Sleep(20);

			SetStep(_ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_Y_PAPER_UNLOAD_POS_CHECK, _T("_ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_Y_PAPER_UNLOAD_POS_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _ePAPER_UNLOAD_FLOW_CST_RECV_READY_DONE_CHECK:
			if (Devs::m_CstRecvReadyFlow.IsFlowDone())
			{
				SetStep(_ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_Z_PAPER_UNLOAD_DOWN_POS, _T("_ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_Z_PAPER_UNLOAD_DOWN_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_ePAPER_UNLOAD_FLOW_CST_RECV_READY_DONE_CHECK : Time Out"), ePAPER_UNLOAD_FLOW + 29);
				SetStep(_ePAPER_UNLOAD_FLOW_ERROR, _T("_ePAPER_UNLOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_ePAPER_UNLOAD_FLOW_CST_RECV_READY_DONE_CHECK, _T("_ePAPER_UNLOAD_FLOW_CST_RECV_READY_DONE_CHECK"));
			}
			break;

		case _ePAPER_UNLOAD_FLOW_CST_RECV_DONE_MOVE:
			Devs::m_CstRecvDoneFlow.Start();
			Sleep(20);

			SetStep(_ePAPER_UNLOAD_FLOW_CST_RECV_DONE_DONE_CHECK, _T("_ePAPER_UNLOAD_FLOW_CST_RECV_DONE_DONE_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _ePAPER_UNLOAD_FLOW_CST_RECV_DONE_DONE_CHECK:
			if (Devs::m_CstRecvDoneFlow.IsFlowDone())
			{
				SetStep(_ePAPER_UNLOAD_FLOW_DONE, _T("_ePAPER_UNLOAD_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_ePAPER_UNLOAD_FLOW_CST_RECV_DONE_DONE_CHECK : Time Out"), eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW + 29);
				SetStep(_ePAPER_UNLOAD_FLOW_ERROR, _T("_ePAPER_UNLOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_ePAPER_UNLOAD_FLOW_CST_RECV_DONE_DONE_CHECK, _T("_ePAPER_UNLOAD_FLOW_CST_RECV_DONE_DONE_CHECK"));
			}
			break;
#pragma endregion

		case _ePAPER_UNLOAD_FLOW_DONE:
		{
			SharedInfo::nPrevFlowID = ePAPER_UNLOAD_FLOW; //KJT 20210326

			m_bFlowDone = TRUE;

			SharedInfo::CalTactTime(_T("PAPER_UNLOAD_FLOW"), m_timeStart); //KJT 20210329

			SetStep(_ePAPER_UNLOAD_FLOW_IDLE, _T("_ePAPER_UNLOAD_FLOW_IDLE"));
			break;
		}
		default:
		{
			break;
		}
		}

		Sleep(50); //!!
	}
}

BOOL CPaperUnloadFlow::FlowInterlock()
{
	CString Str = _T("");

#ifndef SIM_MODE
	if (Devs::m_GantryMotion.CheckGantryXYZFlowInterlock(_T("PaperUnloadFlow"), ePAPER_UNLOAD_FLOW, 50) == FALSE)
	{
		return FALSE;
	}

	//Servo On Check
	if (SharedInfo::GetServoOnStatus(AXIS_UNLOADER_ZL) == FALSE)
	{
		SharedInfo::SetAlarm(_T("PaperUnloadFlow : Check PaperUnloader ZL Servo On !!!"), ePAPER_UNLOAD_FLOW);
		return FALSE;
	}
	else if (SharedInfo::GetServoOnStatus(AXIS_UNLOADER_ZR) == FALSE)
	{
		SharedInfo::SetAlarm(_T("PaperUnloadFlow : Check PaperUnloader ZR Servo On !!!"), ePAPER_UNLOAD_FLOW);
		return FALSE;
	}
	else if (SharedInfo::GetServoOnStatus(AXIS_UNLOADER_XL) == FALSE)
	{
		SharedInfo::SetAlarm(_T("PaperUnloadFlow : Check PaperUnloader XL Servo On !!!"), ePAPER_UNLOAD_FLOW);
		return FALSE;
	}
	else if (SharedInfo::GetServoOnStatus(AXIS_UNLOADER_XR) == FALSE)
	{
		SharedInfo::SetAlarm(_T("PaperUnloadFlow : Check PaperUnloader XR Servo On !!!"), ePAPER_UNLOAD_FLOW);
		return FALSE;
	}

	//Home Status Check
	if (SharedInfo::GetHomeStatus(AXIS_UNLOADER_ZL) == FALSE)
	{
		SharedInfo::SetAlarm(_T("PaperUnloadFlow : Check PaperUnloader ZL Home Status !!!"), ePAPER_UNLOAD_FLOW);
		return FALSE;
	}
	else if (SharedInfo::GetHomeStatus(AXIS_UNLOADER_ZR) == FALSE)
	{
		SharedInfo::SetAlarm(_T("PaperUnloadFlow : Check PaperUnloader ZR Home Status !!!"), ePAPER_UNLOAD_FLOW);
		return FALSE;
	}
	else if (SharedInfo::GetHomeStatus(AXIS_UNLOADER_XL) == FALSE)
	{
		SharedInfo::SetAlarm(_T("PaperUnloadFlow : Check PaperUnloader XL Home Status !!!"), ePAPER_UNLOAD_FLOW);
		return FALSE;
	}
	else if (SharedInfo::GetHomeStatus(AXIS_UNLOADER_XR) == FALSE)
	{
		SharedInfo::SetAlarm(_T("PaperUnloadFlow : Check PaperUnloader XR Home Status !!!"), ePAPER_UNLOAD_FLOW);
		return FALSE;
	}
#endif

	return TRUE;
}