#include "stdafx.h"
#include "StickLoadInCstToStageFlow.h"
#include "Log/Logger.h"
#include "Vision/Devs.h"
#include "Data/ModelData.h"
#include "CamAreaModul.h"
#include "Data/SystemData.h"
#include "Data/ManualData.h"


CStickLoadInCstToStageFlow::CStickLoadInCstToStageFlow()
{
}


CStickLoadInCstToStageFlow::~CStickLoadInCstToStageFlow()
{
}

BOOL CStickLoadInCstToStageFlow::InitProcess()
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
	//pMappingProc = CMappingProc::GetInstance();
	return TRUE;
}
BOOL CStickLoadInCstToStageFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_IDLE, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_IDLE"));

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
BOOL CStickLoadInCstToStageFlow::Start(int nStep)
{
	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(nStep, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_START"));
	return TRUE;
}
BOOL CStickLoadInCstToStageFlow::Stop()
{
	m_bStopBit = TRUE;
	SetStop(); //!!
	return TRUE;
}
UINT CStickLoadInCstToStageFlow::ThreadFunction(LPVOID lpParam)
{
	CStickLoadInCstToStageFlow* pFlow = NULL;

	pFlow = (CStickLoadInCstToStageFlow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}

VOID CStickLoadInCstToStageFlow::ThreadFunctionEntry(VOID)
{
	DWORD	dwResult = 0;
	double	dStrt_Time = GetTickCount();
	double	dEnd_Time = GetTickCount();
	double	dWait_Time = GetTickCount();
	int		nWork_Mask_Mode = -1;
	int		nWork_Mask_Index = -1;
	BOOL	bComplete_Step = FALSE;

	int nSafetyPosErrorBy;
	CString Str = _T("");

	while (m_FlowFinish)
	{
		WaitForSingleObject(hHandle, INFINITE);
		ResetEvent(hHandle);

		if (SharedInfo::bMachineStopFlag == TRUE && m_bStopBit == FALSE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}

		switch (GetCurrentTotalStep())
		{
		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_IDLE:
		{
			break;
		}
		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_START:
		{
			SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_INTERLOCK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_INTERLOCK"));
			break;
		}

		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_INTERLOCK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_READY, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_READY"));
			}
			break;

#pragma region //Unloader Ready
		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_READY:
			Devs::m_Ready_UnloaderFlow.Start();

			SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_READY_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_READY_CHECK:
			if (Devs::m_Ready_UnloaderFlow.IsFlowDone())
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_LOADER_READY, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_LOADER_READY"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_READY_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Loader Ready
		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_LOADER_READY:
			Devs::m_Ready_LoaderFlow.Start();

			SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_LOADER_READY_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_LOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_LOADER_READY_CHECK:
			if (Devs::m_Ready_LoaderFlow.IsFlowDone())
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_BOX_CAMERA_READY, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_BOX_CAMERA_READY"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_LOADER_READY_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_LOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Box Camera Ready
		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_BOX_CAMERA_READY:
			Devs::m_BoxMotion.BoxAlignCameraYL_WaitPos();
			Sleep(20);
			Devs::m_BoxMotion.BoxAlignCameraYR_WaitPos();
			Sleep(500); //!!

			SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_BOX_CAMERA_READY_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_BOX_CAMERA_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_BOX_CAMERA_READY_CHECK:
			if (Devs::m_BoxMotion.Is_BoxAlignCameraYL_WaitPos() == TRUE && Devs::m_BoxMotion.Is_BoxAlignCameraYR_WaitPos() == TRUE)
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_GANTRY_ZXY_READY, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_GANTRY_ZXY_READY"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_BOX_CAMERA_READY_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_BOX_CAMERA_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Gantry Z, XY Ready
		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_GANTRY_ZXY_READY:
			Devs::m_Ready_GantryAvoidUldFlow.Start();

			SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_GANTRY_ZXY_READY_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_GANTRY_ZXY_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_GANTRY_ZXY_READY_CHECK:
			if (Devs::m_Ready_GantryAvoidUldFlow.IsFlowDone())
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_BOX_CAMERA_WAIT_POS, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_BOX_CAMERA_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_GANTRY_ZXY_READY_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_GANTRY_ZXY_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //BoxCamY, Inspection Uvw Ready
		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_BOX_CAMERA_WAIT_POS:
			Devs::m_BoxMotion.BoxAlignCameraYL_WaitPos();
			Sleep(20); //!!
			Devs::m_BoxMotion.BoxAlignCameraYR_WaitPos();
			Sleep(20); //!!

			SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_BOX_CAMERA_WAIT_POS_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_BOX_CAMERA_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_BOX_CAMERA_WAIT_POS_CHECK:
			if (Devs::m_BoxMotion.Is_BoxAlignCameraYL_WaitPos() && Devs::m_BoxMotion.Is_BoxAlignCameraYR_WaitPos())
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_INSP_UVW_UNLOAD_POS, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_INSP_UVW_UNLOAD_POS"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_BOX_CAMERA_WAIT_POS_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_BOX_CAMERA_WAIT_POS_CHECK"));
			}
			break;

		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_INSP_UVW_UNLOAD_POS:
			Devs::m_InspectionStageMotion.InspectionStageUVW_StickUnloadPos();

			SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_INSP_UVW_UNLOAD_POS_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_INSP_UVW_UNLOAD_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_INSP_UVW_UNLOAD_POS_CHECK:
			if (Devs::m_InspectionStageMotion.Is_InspectionStageUVW_StickUnloadPos())
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_Z_SEND_POS, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_Z_SEND_POS"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_INSP_UVW_UNLOAD_POS_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_INSP_UVW_UNLOAD_POS_CHECK"));
			}
			break;
#pragma endregion

#pragma region //1. CST Z, PiciupUnit Send Ready
		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_Z_SEND_POS:
			Devs::m_CassetteMotion.CassetteZ_1FloorPos(); //Temp !!

			SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_Z_SEND_POS_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_Z_SEND_POS_CHECK"));
			break;

		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_Z_SEND_POS_CHECK:
			if (Devs::m_CassetteMotion.Is_CassetteZ_1FloorPos())
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_UNCLMAP_1ST, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_UNCLMAP_1ST"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_Z_SEND_POS_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_Z_SEND_POS_CHECK"));
			}
			break;

		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_UNCLMAP_1ST:
			Devs::m_CassetteMotion.CSTPickUpUnitUnclamp();
			Sleep(500); //!!

			SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_UNCLMAP_1ST_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_UNCLMAP_1ST_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_UNCLMAP_1ST_CHECK:
			if (Devs::m_CassetteMotion.Is_CSTPickUpUnitUnclamp())
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_FWD_1ST, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_FWD_1ST"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_UNCLMAP_1ST_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_UNCLMAP_1ST_CHECK"));
			}
			break;

		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_FWD_1ST:
			Devs::m_CassetteMotion.CSTPickUpUnitFwd();
			Sleep(500); //!!

			SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_FWD_1ST_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_FWD_1ST_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_FWD_1ST_CHECK:
			if (Devs::m_CassetteMotion.Is_CSTPickUpUnitFwd())
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_CLMAP, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_CLMAP"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_FWD_1ST_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_FWD_1ST_CHECK"));
			}
			break;

		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_CLMAP:
			Devs::m_CassetteMotion.CSTPickUpUnitClamp();
			Sleep(500); //!!

			SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_CLMAP_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_CLMAP_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_CLMAP_CHECK:
			if (Devs::m_CassetteMotion.Is_CSTPickUpUnitClamp())
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_BWD_1ST, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_BWD_1ST"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_CLMAP_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_CLMAP_CHECK"));
			}
			break;

		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_BWD_1ST:
			Devs::m_CassetteMotion.CSTPickUpUnitBwd();
			Sleep(500); //!!

			SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_BWD_1ST_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_BWD_1ST_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_BWD_1ST_CHECK:
			if (Devs::m_CassetteMotion.Is_CSTPickUpUnitBwd())
			{
				//if (SharedInfo::DInputValue[_DIN_MAGAZINE_SAFETY_POS_DETECT_2]/* && SharedInfo::DInputValue[_DIN_MAGAZINE_EXIST_DETECT_1]*/)
				//	SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Y_LOAD_IN_CST_POS, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Y_LOAD_IN_CST_POS"));
				//else
				//{
				//	Total_Msg(_T("Check CST Detect !!"));
				//	SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR"));
				//}
			}
			else if (IsTimeOut())
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_BWD_1ST_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_BWD_1ST_CHECK"));
			}
			break;
#pragma endregion

#pragma region //2. Stick Load In CST
		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Y_LOAD_IN_CST_POS:
			Devs::m_UnloaderMotion.GantryY_StickLoadInCstPos(0);

			SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Y_LOAD_IN_CST_POS_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Y_LOAD_IN_CST_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Y_LOAD_IN_CST_POS_CHECK:
			if (Devs::m_UnloaderMotion.Is_UnloaderY_LoadInCstPos(0))
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Z_LOAD_IN_CST_POS, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Z_LOAD_IN_CST_POS"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Y_LOAD_IN_CST_POS_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Y_LOAD_IN_CST_POS_CHECK"));
			}
			break;

		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Z_LOAD_IN_CST_POS:
			Devs::m_UnloaderMotion.UnloaderZ_UnloadToCstPos();

			SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Z_LOAD_IN_CST_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Z_LOAD_IN_CST_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Z_LOAD_IN_CST_CHECK:
			if (Devs::m_UnloaderMotion.Is_UnloaderZ_UnloadToCstPos())
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_VAC_ON, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_VAC_ON"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Z_LOAD_IN_CST_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Z_LOAD_IN_CST_CHECK"));
			}
			break;

		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_VAC_ON:
			Devs::m_UnloaderMotion.Stick_Active_Vac_On();

			SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_STEP_DOWN, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_STEP_DOWN"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_STEP_DOWN:
			m_dTargetPosUldZ = SharedInfo::GetCmdPos(AXIS_UNLOADER_Z);
			m_dTargetPosUldZ -= CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_StepDownOffset;
			if (SharedInfo::CheckSafetyPos(AXIS_UNLOADER_Z, m_dTargetPosUldZ, &Str, &nSafetyPosErrorBy) == FALSE)
			{
				Total_Msg(Str);
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR"));
				break;
			}

			Devs::m_UnloaderMotion.MoveAxis(AXIS_UNLOADER_Z, m_dTargetPosUldZ);
			Str.Format(_T("Unloader Z Step Down %.5f (To Pos : %.5f)"), CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_StepDownOffset, m_dTargetPosUldZ);
			Total_Msg(Str);

			SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Z_STICK_LOAD_STEP_DOWN_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Z_STICK_LOAD_STEP_DOWN_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Z_STICK_LOAD_STEP_DOWN_CHECK:
			if (Devs::m_UnloaderMotion.IsMoveDone(AXIS_UNLOADER_Z, m_dTargetPosUldZ))
			{
				Sleep(1000); //!!
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_VAC_ON_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_VAC_ON_CHECK"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Z_STICK_LOAD_STEP_DOWN_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Z_STICK_LOAD_STEP_DOWN_CHECK"));
			}
			break;

		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_VAC_ON_CHECK:
			if (Devs::m_UnloaderMotion.Is_Stick_Active_Vac_On())
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Z_WAIT_POS, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Z_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_STEP_DOWN, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_STEP_DOWN"));
			}
			break;

		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Z_WAIT_POS:
			Devs::m_UnloaderMotion.UnloaderZ_WaitPos();

			SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Z_WAIT_POS_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Z_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Z_WAIT_POS_CHECK:
			if (Devs::m_UnloaderMotion.Is_UnloaderZ_WaitPos())
			{
				if (Devs::m_UnloaderMotion.Is_Stick_Active_Vac_On() == FALSE)
				{
					Total_Msg(_T("Check Unlaoder Stick Active Vac On !!!"));
					SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR"));
				}
				else
				{
					SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_FWD_2ND, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_FWD_2ND"));
				}
			}
			else if (IsTimeOut())
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Z_WAIT_POS_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Z_WAIT_POS_CHECK"));
			}
			break;
#pragma endregion

#pragma region //3. PickupUnit Wait
		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_FWD_2ND:
			Devs::m_CassetteMotion.CSTPickUpUnitFwd();
			Sleep(500); //!!

			SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_FWD_2ND_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_FWD_2ND_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_FWD_2ND_CHECK:
			if (Devs::m_CassetteMotion.Is_CSTPickUpUnitFwd())
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_UNCLMAP_2ND, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_UNCLMAP_2ND"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_FWD_2ND_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_FWD_2ND_CHECK"));
			}
			break;

		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_UNCLMAP_2ND:
			Devs::m_CassetteMotion.CSTPickUpUnitUnclamp();
			Sleep(500); //!!

			SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_UNCLMAP_2ND_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_UNCLMAP_2ND_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_UNCLMAP_2ND_CHECK:
			if (Devs::m_CassetteMotion.Is_CSTPickUpUnitUnclamp())
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_BWD_2ND, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_BWD_2ND"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_UNCLMAP_2ND_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_UNCLMAP_2ND_CHECK"));
			}
			break;

		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_BWD_2ND:
			Devs::m_CassetteMotion.CSTPickUpUnitBwd();
			Sleep(500); //!!

			SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_BWD_2ND_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_BWD_2ND_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_BWD_2ND_CHECK:
			if (Devs::m_CassetteMotion.Is_CSTPickUpUnitBwd())
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Y_UNLOAD_TO_STAGE_POS, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Y_UNLOAD_TO_STAGE_POS"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_BWD_2ND_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_BWD_2ND_CHECK"));
			}
			break;
#pragma endregion

#pragma region //4. Stick Unload To Stage
		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Y_UNLOAD_TO_STAGE_POS:
			Devs::m_UnloaderMotion.GantryY_StickUnloadToStagePos();

			SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Y_UNLOAD_TO_STAGE_POS_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Y_UNLOAD_TO_STAGE_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Y_UNLOAD_TO_STAGE_POS_CHECK:
			if (Devs::m_UnloaderMotion.Is_UnloaderY_UnloadToStagePos())
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_X_TENSION_POS, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_X_TENSION_POS"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Y_UNLOAD_TO_STAGE_POS_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Y_UNLOAD_TO_STAGE_POS_CHECK"));
			}
			break;

		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_X_TENSION_POS:
			m_dTargetPosUldX = SharedInfo::GetCmdPos(AXIS_UNLOADER_X);
			m_dTargetPosUldX += CManualData::m_ManualDataUnloader.Info.m_dUnloaderX_Tension_Offset;
			if (SharedInfo::CheckSafetyPos(AXIS_UNLOADER_X, m_dTargetPosUldX, &Str, &nSafetyPosErrorBy) == FALSE)
			{
				Total_Msg(Str);
				AfxMessageBox(Str);
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR"));
				break;
			}

			Devs::m_LoaderMotion.MoveAxis(AXIS_UNLOADER_X, m_dTargetPosUldX);
			Str.Format(_T("Unloader X Tension Offset %.5f (To Pos : %.5f)"), CManualData::m_ManualDataUnloader.Info.m_dUnloaderX_Tension_Offset, m_dTargetPosUldX);
			Total_Msg(Str);

			SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_X_TENSION_POS_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_X_TENSION_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_X_TENSION_POS_CHECK:
			if (Devs::m_LoaderMotion.IsMoveDone(AXIS_UNLOADER_X, m_dTargetPosUldX))
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Z_UNLOAD_TO_STAGE_POS, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Z_UNLOAD_TO_STAGE_POS"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_X_TENSION_POS_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_X_TENSION_POS_CHECK"));
			}
			break;

		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Z_UNLOAD_TO_STAGE_POS:
			Devs::m_UnloaderMotion.UnloaderZ_LoadInStagePos();

			SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Z_UNLOAD_TO_STAGE_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Z_UNLOAD_TO_STAGE_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Z_UNLOAD_TO_STAGE_CHECK:
			if (Devs::m_UnloaderMotion.Is_UnloaderZ_LoadInStagePos())
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_VAC_OFF, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_VAC_OFF"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Z_UNLOAD_TO_STAGE_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Z_UNLOAD_TO_STAGE_CHECK"));
			}
			break;

		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_VAC_OFF:
			Devs::m_UnloaderMotion.Stick_Active_Vac_Off();

			SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_VAC_OFF_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_VAC_OFF_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_VAC_OFF_CHECK:
			if (Devs::m_UnloaderMotion.Is_Stick_Active_Vac_Off())
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Z_WAIT_POS_FINISH, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Z_WAIT_POS_FINISH"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_VAC_OFF_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_VAC_OFF_CHECK"));
			}
			break;

		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Z_WAIT_POS_FINISH:
			Devs::m_UnloaderMotion.UnloaderZ_WaitPos();

			SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Z_WAIT_POS_FINISH_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Z_WAIT_POS_FINISH_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Z_WAIT_POS_FINISH_CHECK:
			if (Devs::m_UnloaderMotion.Is_UnloaderZ_WaitPos())
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_X_WAIT_POS_FINISH, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_X_WAIT_POS_FINISH"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Z_WAIT_POS_FINISH_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Z_WAIT_POS_FINISH_CHECK"));
			}
			break;

		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_X_WAIT_POS_FINISH:
			Devs::m_UnloaderMotion.UnloaderX_WaitPos();

			SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_X_WAIT_POS_FINISH_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_X_WAIT_POS_FINISH_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_X_WAIT_POS_FINISH_CHECK:
			if (Devs::m_UnloaderMotion.Is_UnloaderX_WaitPos())
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Y_WAIT_POS_FINISH, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Y_WAIT_POS_FINISH"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_X_WAIT_POS_FINISH_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_X_WAIT_POS_FINISH_CHECK"));
			}
			break;

		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Y_WAIT_POS_FINISH:
			Devs::m_UnloaderMotion.UnloaderY_WaitPos();

			SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Y_WAIT_POS_FINISH_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Y_WAIT_POS_FINISH_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Y_WAIT_POS_FINISH_CHECK:
			if (Devs::m_UnloaderMotion.Is_UnloaderY_WaitPos())
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_DONE, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Y_WAIT_POS_FINISH_CHECK, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Y_WAIT_POS_FINISH_CHECK"));
			}
			break;
#pragma endregion

		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR:
			break;

		case _eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_DONE:
		{
			m_bFlowDone = TRUE;

			SetStep(_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_IDLE, _T("_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_IDLE"));
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

BOOL CStickLoadInCstToStageFlow::FlowInterlock()
{
	CString Str = _T("");

	if (Devs::m_CassetteMotion.Is_CSTPickUpUnitBwd() == FALSE)
	{
		Total_Msg(_T("Check Pickup Unit Backward !!!"));
		return FALSE;
	}
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

	return TRUE;
}