#include "stdafx.h"
#include "StickLoadInStageToBoxFlow.h"
#include "Log/Logger.h"
#include "Vision/Devs.h"
#include "Data/ModelData.h"
#include "Data/ManualData.h"
#include "CamAreaModul.h"
#include "Data/SystemData.h"
//#include "../WkLibFlow/WkLibFlow.h"
#include "Flow/BaseFlow.h"

CStickLoadInStageToBoxFlow::CStickLoadInStageToBoxFlow()
{
}


CStickLoadInStageToBoxFlow::~CStickLoadInStageToBoxFlow()
{
}

BOOL CStickLoadInStageToBoxFlow::InitProcess()
{
	m_StateComplete = NULL;
	m_FlowFinish = TRUE;
	m_bTerminate = FALSE;
	m_bFlowDone = TRUE;

	m_dTargetPosZ = 0.0;

	//SetProcessLog(Process_Msg);
	//SetAlarmLog(LogMsg_Alarm);

	hHandle = CreateEvent(NULL, TRUE, FALSE, NULL);
	SetHandle(hHandle);
	pThread = AfxBeginThread(ThreadFunction, this);
	//pMappingProc = CMappingProc::GetInstance();
	return TRUE;
}

BOOL CStickLoadInStageToBoxFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_IDLE);

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

BOOL CStickLoadInStageToBoxFlow::Start(int nStep)
{
	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(nStep, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_START"));
	return TRUE;
}
BOOL CStickLoadInStageToBoxFlow::Stop()
{
	m_bStopBit = TRUE;
	SetStop(); //!!
	return TRUE;
}
UINT CStickLoadInStageToBoxFlow::ThreadFunction(LPVOID lpParam)
{
	CStickLoadInStageToBoxFlow* pFlow = NULL;

	pFlow = (CStickLoadInStageToBoxFlow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}

VOID CStickLoadInStageToBoxFlow::ThreadFunctionEntry(VOID)
{
	DWORD	dwResult = 0;
	double	dStrt_Time = GetTickCount();
	double	dEnd_Time = GetTickCount();
	double	dWait_Time = GetTickCount();
	int		nWork_Mask_Mode = -1;
	int		nWork_Mask_Index = -1;
	BOOL	bComplete_Step = FALSE;

	CString Str = _T("");
	int nSafetyPosErrorBy = -1;

	while (m_FlowFinish)
	{
		WaitForSingleObject(hHandle, INFINITE);
		ResetEvent(hHandle);

		if (SharedInfo::bMachineStopFlag == TRUE)// && m_bStopBit == FALSE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}

		
		switch (GetCurrentTotalStep())
		{
		case _eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_IDLE:
		{
			break;
		}
		case _eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_START:
		{
			m_timeStart = CTime::GetCurrentTime(); //KJT 20210329

			SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_INTERLOCK, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_INTERLOCK"));
			break;
		}
		case _eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_INTERLOCK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_ERROR, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_ERROR"));
			}
			else
			{
				SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_UNLOADER_READY, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_UNLOADER_READY"));
			}
			break;

#pragma region //Unloader Ready
		case _eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_UNLOADER_READY:
			Devs::m_Ready_UnloaderFlow.Start();

			SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_UNLOADER_READY_CHECK, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_UNLOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_UNLOADER_READY_CHECK:
			if (Devs::m_Ready_UnloaderFlow.IsFlowDone())
			{
				SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_GANTRY_ZX_READY, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_GANTRY_ZX_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_UNLOADER_READY_CHECK : Time Out"), eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW + 0);
				SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_ERROR, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_UNLOADER_READY_CHECK, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_UNLOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Gantry Z,X Ready
		case _eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_GANTRY_ZX_READY:
			Devs::m_Ready_GantryZX_Flow.Start();

			SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_GANTRY_ZX_READY_CHECK, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_GANTRY_ZX_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_GANTRY_ZX_READY_CHECK:
			if (Devs::m_Ready_GantryZX_Flow.IsFlowDone())
			{
				SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_READY, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_GANTRY_ZX_READY_CHECK : Time Out"), eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW + 2);
				SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_ERROR, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_GANTRY_ZX_READY_CHECK, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_GANTRY_ZX_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Loader Ready
		case _eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_READY:
			Devs::m_Ready_LoaderFlow.Start();

			SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_READY_CHECK, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_READY_CHECK:
			if (Devs::m_Ready_LoaderFlow.IsFlowDone())
			{
#ifndef GRIPPER_0
				SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_GRIPPER_READY, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_GRIPPER_READY"));
#else
				SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_INSPECTION_UVW_STICK_LOAD_POS, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_INSPECTION_UVW_STICK_LOAD_POS"));
#endif
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_READY_CHECK : Time Out"), eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW + 1);
				SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_ERROR, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_READY_CHECK, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#ifndef GRIPPER_0
#pragma region //Gripper Ready
		case _eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_GRIPPER_READY:
			Devs::m_Ready_Gripper_Flow.Start();

			SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_GRIPPER_READY_CHECK, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_GRIPPER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_GRIPPER_READY_CHECK:
			if (Devs::m_Ready_Gripper_Flow.IsFlowDone())
			{
				SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_INSPECTION_UVW_STICK_LOAD_POS, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_INSPECTION_UVW_STICK_LOAD_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_GRIPPER_READY_CHECK : Time Out"), eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW + 4);
				SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_ERROR, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_GRIPPER_READY_CHECK, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_GRIPPER_READY_CHECK"));
			}
			break;
#pragma endregion
#endif

#pragma region //Inspection Uvw Ready
		case _eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_INSPECTION_UVW_STICK_LOAD_POS:
			Devs::m_InspectionStageMotion.InspectionStageUVW_StickLoadPos();

			SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_INSPECTION_UVW_STICK_LOAD_POS_CHECK, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_INSPECTION_UVW_STICK_LOAD_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_INSPECTION_UVW_STICK_LOAD_POS_CHECK:
			if (Devs::m_InspectionStageMotion.Is_InspectionStageUVW_StickLoadPos())
			{
				SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Y_STICK_LOAD_IN_STAGE_POS, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Y_STICK_LOAD_IN_STAGE_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_INSPECTION_UVW_STICK_LOAD_POS_CHECK : Time Out"), eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW + 5);
				SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_ERROR, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_INSPECTION_UVW_STICK_LOAD_POS_CHECK, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_INSPECTION_UVW_STICK_LOAD_POS_CHECK"));
			}
			break;
#pragma endregion

#pragma region //1. PickUp In Stage
		case _eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Y_STICK_LOAD_IN_STAGE_POS:
			Devs::m_LoaderMotion.LoaderY_Stick_UnloadPos();
			Sleep(20); //!!!

			SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Y_STICK_LOAD_IN_STAGE_POS_CHECK, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Y_STICK_LOAD_IN_STAGE_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Y_STICK_LOAD_IN_STAGE_POS_CHECK:
			if (Devs::m_LoaderMotion.Is_LoaderY_Stick_UnloadPos())
			{
				SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_X_WAIT_POS, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_X_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Y_STICK_LOAD_IN_STAGE_POS_CHECK : Time Out"), eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW + 6);
				SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_ERROR, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Y_STICK_LOAD_IN_STAGE_POS_CHECK);
			}
			break;

		case _eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_X_WAIT_POS:
			Devs::m_LoaderMotion.LoaderX_WaitPos();

			SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_X_WAIT_POS_CHECK, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_X_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_X_WAIT_POS_CHECK:
			if (Devs::m_LoaderMotion.Is_LoaderX_WaitPos())
			{
				//SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_LOAD_CYLINDER_UP, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_LOAD_CYLINDER_UP"));
				SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_LOAD_DOWN_POS, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_LOAD_DOWN_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_X_WAIT_POS_CHECK : Time Out"), eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW + 7);
				SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_ERROR, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_X_WAIT_POS_CHECK);
			}
			break;

		//case _eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_LOAD_SUB_Z_UP:
		//	Devs::m_LoaderMotion.LoaderZL_WaitPos();
		//	Sleep(10);
		//	Devs::m_LoaderMotion.LoaderZR_WaitPos();

		//	SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_LOAD_SUB_Z_UP_CHECK, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_LOAD_SUB_Z_UP_CHECK"));
		//	SetTimeOut(TIME_OUT_MOTION);
		//	break;

		//case _eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_LOAD_SUB_Z_UP_CHECK:
		//	if (Devs::m_LoaderMotion.Is_LoaderZL_WaitPos() && Devs::m_LoaderMotion.Is_LoaderZR_WaitPos())
		//	{
		//		SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_LOAD_DOWN_POS, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_LOAD_DOWN_POS"));
		//	}
		//	else if (IsTimeOut())
		//	{
		//		SharedInfo::SetAlarm(_T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_LOAD_SUB_Z_UP_CHECK : Time Out"), eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW + 8);
		//		SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_ERROR, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_ERROR"));
		//	}
		//	else
		//	{
		//		SetCheckStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_LOAD_DOWN_POS);
		//	}
		//	break;

		case _eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_LOAD_DOWN_POS:
			Devs::m_LoaderMotion.LoaderZ_StickLoadInStage1stPos();

			SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_LOAD_DOWN_POS_CHECK, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_LOAD_DOWN_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_LOAD_DOWN_POS_CHECK:
			if (Devs::m_LoaderMotion.Is_LoaderZ_StickLoadInStage1stPos())
			{
				SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_LOAD_VAC_ON, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_LOAD_VAC_ON"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_LOAD_DOWN_POS_CHECK : Time Out"), eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW + 9);
				SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_ERROR, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_LOAD_DOWN_POS_CHECK);
			}
			break;

		case _eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_LOAD_VAC_ON:
			Devs::m_LoaderMotion.Stick_Active_Vac_On();

			Sleep(1000); //!!
			SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_LOAD_STEP_DOWN, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_LOAD_STEP_DOWN"));
			break;

		case _eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_LOAD_STEP_DOWN:
			m_dTargetPosZ = SharedInfo::GetCmdPos(AXIS_LOADER_Z);
			m_dTargetPosZ -= CManualData::m_ManualDataLoader.Info.m_dLoaderZ_StepDownOffset;
			if (SharedInfo::CheckSafetyPos(AXIS_LOADER_Z, m_dTargetPosZ, &Str, &nSafetyPosErrorBy) == FALSE)
			{
				Total_Msg(Str);
				SharedInfo::SetAlarm(_T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_LOAD_STEP_DOWN : Time Out"), eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW + 10);
				SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_ERROR, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_ERROR"));
				break;
			}

			Devs::m_LoaderMotion.MoveAxis(AXIS_LOADER_Z, m_dTargetPosZ);
			Str.Format(_T("Loader Z Step Down %.5f (To Pos : %.5f)"), CManualData::m_ManualDataLoader.Info.m_dLoaderZ_StepDownOffset, m_dTargetPosZ);
			Total_Msg(Str);

			SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_LOAD_STEP_DOWN_CHECK, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_LOAD_STEP_DOWN_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_LOAD_STEP_DOWN_CHECK:
			if (Devs::m_LoaderMotion.IsMoveDone(AXIS_LOADER_Z, m_dTargetPosZ))
			{
				Sleep(2000); //!!
				SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_LOAD_VAC_ON_CHECK, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_LOAD_VAC_ON_CHECK"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_LOAD_STEP_DOWN_CHECK : Time Out"), eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW + 11);
				SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_ERROR, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_LOAD_STEP_DOWN_CHECK);
			}
			break;

		case _eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_LOAD_VAC_ON_CHECK:
			if (Devs::m_LoaderMotion.Is_Stick_Active_Vac_On())
			{
				SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_INSPECTION_STAGE_VAC_OFF, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_INSPECTION_STAGE_VAC_OFF"));
			}
			else
			{
				SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_LOAD_STEP_DOWN, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_LOAD_STEP_DOWN"));
			}
			break;

		case _eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_INSPECTION_STAGE_VAC_OFF:
			Devs::m_InspectionStageMotion.Inspect_Stage_Vac_Off();
			Sleep(1000); //!!

			SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_INSPECTION_STAGE_VAC_OFF_CHECK, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_INSPECTION_STAGE_VAC_OFF_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_INSPECTION_STAGE_VAC_OFF_CHECK:
			if (Devs::m_InspectionStageMotion.Is_Inspect_Stage_Vac_Off())
			{
				SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_LOAD_WAIT_POS, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_LOAD_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_INSPECTION_STAGE_VAC_OFF_CHECK : Time Out"), eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW + 12);
				SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_ERROR, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_INSPECTION_STAGE_VAC_OFF_CHECK);
			}
			break;

		case _eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_LOAD_WAIT_POS:
			Devs::m_LoaderMotion.LoaderZ_WaitPos();

			SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_LOAD_WAIT_POS_CHECK, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_LOAD_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_LOAD_WAIT_POS_CHECK:
			if (Devs::m_LoaderMotion.Is_LoaderZ_WaitPos())
			{
				if (Devs::m_LoaderMotion.Is_Stick_Active_Vac_On() == FALSE)
				{
					Total_Msg(_T("Check Loader Stick Active Vac On !!!"));
					SharedInfo::SetAlarm(_T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_LOAD_WAIT_POS_CHECK : Vac On"), eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW + 13);
					SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_ERROR, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_ERROR"));
				}
				else
				{
					SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Y_STICK_UNLOAD_TO_BOX_POS, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Y_STICK_UNLOAD_TO_BOX_POS"));
				}
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_LOAD_WAIT_POS_CHECK : Time Out"), eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW + 14);
				SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_ERROR, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_LOAD_WAIT_POS_CHECK);
			}
			break;
#pragma endregion //1. PickUp In Stage

#pragma region //2. Unload To Inspection Box
		case _eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Y_STICK_UNLOAD_TO_BOX_POS:
			Devs::m_LoaderMotion.LoaderY_Stick_LoadPos();
			Sleep(20); //!!!

			SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Y_STICK_UNLOAD_TO_BOX_POS_CHECK, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Y_STICK_UNLOAD_TO_BOX_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Y_STICK_UNLOAD_TO_BOX_POS_CHECK:
			if (Devs::m_LoaderMotion.Is_LoaderY_Stick_LoadPos())
			{
				SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_UNLOAD_DOWN_POS, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_UNLOAD_DOWN_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Y_STICK_UNLOAD_TO_BOX_POS_CHECK : Time Out"), eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW + 15);
				SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_ERROR, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Y_STICK_UNLOAD_TO_BOX_POS_CHECK);
			}
			break;

		case _eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_UNLOAD_DOWN_POS:
			Devs::m_LoaderMotion.LoaderZ_StickUnloadToBoxPos();

			SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_UNLOAD_DOWN_POS_CHECK, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_UNLOAD_DOWN_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_UNLOAD_DOWN_POS_CHECK:
			if (Devs::m_LoaderMotion.Is_LoaderZ_StickUnloadToBoxPos())
			{
				SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_UNLOAD_VAC_OFF, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_UNLOAD_VAC_OFF"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_UNLOAD_DOWN_POS_CHECK : Time Out"), eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW + 16);
				SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_ERROR, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_UNLOAD_DOWN_POS_CHECK);
			}
			break;

		case _eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_UNLOAD_VAC_OFF:
			Devs::m_LoaderMotion.Stick_Active_Vac_Off();

			SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_UNLOAD_VAC_OFF_CHECK, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_UNLOAD_VAC_OFF_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_UNLOAD_VAC_OFF_CHECK:
			if (Devs::m_LoaderMotion.Is_Stick_Active_Vac_Off())
			{
				SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_FINISH_WAIT_POS, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_FINISH_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_UNLOAD_VAC_OFF_CHECK : Time Out"), eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW + 17);
				SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_ERROR, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_STICK_UNLOAD_VAC_OFF_CHECK);
			}
			break;

		case _eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_FINISH_WAIT_POS:
			Devs::m_LoaderMotion.LoaderZ_WaitPos();

			SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_FINISH_WAIT_POS_CHECK, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_FINISH_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_FINISH_WAIT_POS_CHECK:
			if (Devs::m_LoaderMotion.Is_LoaderZ_WaitPos())
			{
				SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_GANTRY_Y_WAIT_POS, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_GANTRY_Y_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_FINISH_WAIT_POS_CHECK : Time Out"), eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW + 18);
				SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_ERROR, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_LOADER_Z_FINISH_WAIT_POS_CHECK);
			}
			break;

		case _eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_GANTRY_Y_WAIT_POS:
			Devs::m_GantryMotion.Move_Gantry_Y_Wait_Pos();
			Sleep(20); //!!!

			SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_GANTRY_Y_WAIT_POS_CHECK, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_GANTRY_Y_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_GANTRY_Y_WAIT_POS_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_Y_Wait_Pos())
			{
				SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_DONE, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_GANTRY_Y_WAIT_POS_CHECK : Time Out"), eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW + 19);
				SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_ERROR, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_GANTRY_Y_WAIT_POS_CHECK);
			}
			break;

#pragma endregion //2. Unload To Inspection Box

		case _eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_ERROR:
			break;

		case _eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_DONE:
			m_bFlowDone = TRUE;

			SharedInfo::CalTactTime(_T("STICK_LOAD_IN_STAGE_TO_BOX_FLOW"), m_timeStart); //KJT 20210329

			SetStep(_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_IDLE, _T("_eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW_IDLE"));
			break;
		}

		Sleep(100); //!!
	}
}

BOOL CStickLoadInStageToBoxFlow::FlowInterlock()
{
#ifndef SIM_MODE

	/////////////////////////////////////////////////////////////////////////////
	if (Devs::m_GantryMotion.CheckGantryXYZFlowInterlock(_T("StickLoadInStageToBoxFlow"), eSTICK_LOAD_IN_STAGE_TO_BOX_FLOW, 30) == FALSE)
	{
		return FALSE;
	}

	//21.02.04 sjc no jig lock sensor
	//if (SharedInfo::DInputValue[BOX_STAGE_JIG_LOCK_SENSOR] == FALSE)
	//{
	//	Total_Msg(_T("Check Box Stage Jig Lock Sensor !!!"));
	//	return FALSE;
	//}
	//if (SharedInfo::DInputValue[PAPER_STAGE_JIG_LOCK_SENSOR] == FALSE)
	//{
	//	Total_Msg(_T("Check Paper Jig Lock Sensor !!!"));
	//	return FALSE;
	//}

	//if (Devs::m_CassetteMotion.Is_CSTPickUpUnitBwd() == FALSE)
	//{
	//	Total_Msg(_T("Check Pickup Unit Backward !!!"));
	//	return FALSE;
	//}
	//if (SharedInfo::DInputValue[_DIN_MAGAZINE_SAFETY_POS_DETECT_2] == TRUE)
	//{
	//	Total_Msg(_T("Check CST Unsafe Pos Detect Sensor !!!"));
	//	return FALSE;
	//}
	//if (SharedInfo::DInputValue[_DIN_MAGAZINE_EXIST_DETECT_1] == TRUE)
	//{
	//	Total_Msg(_T("Check CST Backward Detect Sensor !!!"));
	//	return FALSE;
	//}
#endif

	return TRUE;
}