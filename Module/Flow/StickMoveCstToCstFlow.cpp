#include "stdafx.h"
#include "StickMoveCstToCstFlow.h"
#include "Log/Logger.h"
#include "Vision/Devs.h"
#include "Data/ModelData.h"
#include "Data/ManualData.h"
#include "CamAreaModul.h"
#include "Data/SystemData.h"
//#include "../WkLibFlow/WkLibFlow.h"
#include "Flow/BaseFlow.h"
#include "FmmLight1.h"

CStickMoveCstToCstFlow::CStickMoveCstToCstFlow()
{
}


CStickMoveCstToCstFlow::~CStickMoveCstToCstFlow()
{
}

BOOL CStickMoveCstToCstFlow::InitProcess()
{
	m_StateComplete = NULL;
	m_FlowFinish = TRUE;
	m_bTerminate = FALSE;
	m_bFlowDone = TRUE;

	m_dTargetPosUldZ = 0.0;
	m_SourceFloor = 0;
	m_SourceSlot = 0;
	m_TargetFloor = 0;
	m_TargetSlot = 0;

#pragma region //Step Group
	m_sGroupInfo[0].m_bProcessingFlag = FALSE;
	m_sGroupInfo[0].nStartStep = _eSTICK_MOVE_CST_TO_CST_FLOW_START;
	m_sGroupInfo[0].nEndStep = _eSTICK_MOVE_CST_TO_CST_FLOW_GANTRY_ZXY_READY_CHECK;
	m_sGroupInfo[0].strGroupName.Format(_T("1. Start - Ready"));

	m_nMaxGroupCount = 1;
#pragma endregion

	hHandle = CreateEvent(NULL, TRUE, FALSE, NULL);
	SetHandle(hHandle);
	pThread = AfxBeginThread(ThreadFunction, this);
	//pMappingProc = CMappingProc::GetInstance();
	return TRUE;
}

BOOL CStickMoveCstToCstFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_IDLE, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_IDLE"));

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
BOOL CStickMoveCstToCstFlow::Start(int nStep)
{
	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(nStep, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_START"));
	return TRUE;
}
BOOL CStickMoveCstToCstFlow::Stop()
{
	m_bStopBit = TRUE;
	SetStop(); //!!
	return TRUE;
}

UINT CStickMoveCstToCstFlow::ThreadFunction(LPVOID lpParam)
{
	CStickMoveCstToCstFlow* pFlow = NULL;

	pFlow = (CStickMoveCstToCstFlow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}

VOID CStickMoveCstToCstFlow::ThreadFunctionEntry(VOID)
{
#if 0
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

		if (SharedInfo::bMachineStopFlag == TRUE)// && m_bStopBit == FALSE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(_eSTICK_MOVE_CST_TO_CST_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}

		
		switch (GetCurrentTotalStep())
		{
		case _eSTICK_MOVE_CST_TO_CST_FLOW_IDLE:
		{
			break;
		}
		case _eSTICK_MOVE_CST_TO_CST_FLOW_START:
		{
			//Temp
			m_SourceFloor = 0;
			m_SourceSlot = 0;
			m_TargetFloor = 0;
			m_TargetSlot = 0;

			SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_INTERLOCK, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_INTERLOCK"));
			break;
		}
		case _eSTICK_MOVE_CST_TO_CST_FLOW_INTERLOCK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_ERROR, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_ERROR"));
			}
			else
			{
				SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_READY, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_READY"));
			}
			break;

#pragma region //Unloader Ready
		case _eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_READY:
			Devs::m_Ready_UnloaderFlow.Start();

			SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_READY_CHECK, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_READY_CHECK:
			if (Devs::m_Ready_UnloaderFlow.IsFlowDone())
			{
				SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_LOADER_READY, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_LOADER_READY"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_ERROR, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_READY_CHECK, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Loader Ready
		case _eSTICK_MOVE_CST_TO_CST_FLOW_LOADER_READY:
			Devs::m_Ready_LoaderFlow.Start();

			SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_LOADER_READY_CHECK, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_LOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_MOVE_CST_TO_CST_FLOW_LOADER_READY_CHECK:
			if (Devs::m_Ready_LoaderFlow.IsFlowDone())
			{
				SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_BOX_CAMERA_READY, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_BOX_CAMERA_READY"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_ERROR, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_MOVE_CST_TO_CST_FLOW_LOADER_READY_CHECK, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_LOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Box Camera Ready
		case _eSTICK_MOVE_CST_TO_CST_FLOW_BOX_CAMERA_READY:
			Devs::m_BoxMotion.BoxAlignCameraYL_WaitPos();
			Sleep(20);
			Devs::m_BoxMotion.BoxAlignCameraYR_WaitPos();
			Sleep(500); //!!

			SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_BOX_CAMERA_READY_CHECK, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_BOX_CAMERA_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_MOVE_CST_TO_CST_FLOW_BOX_CAMERA_READY_CHECK:
			if (Devs::m_BoxMotion.Is_BoxAlignCameraYL_WaitPos() == TRUE && Devs::m_BoxMotion.Is_BoxAlignCameraYR_WaitPos() == TRUE)
			{
				SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_GANTRY_ZXY_READY, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_GANTRY_ZXY_READY"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_ERROR, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_MOVE_CST_TO_CST_FLOW_BOX_CAMERA_READY_CHECK, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_BOX_CAMERA_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Gantry Z, XY Ready
		case _eSTICK_MOVE_CST_TO_CST_FLOW_GANTRY_ZXY_READY:
			Devs::m_Ready_GantryAvoidUldFlow.Start();

			SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_GANTRY_ZXY_READY_CHECK, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_GANTRY_ZXY_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_MOVE_CST_TO_CST_FLOW_GANTRY_ZXY_READY_CHECK:
			if (Devs::m_Ready_GantryAvoidUldFlow.IsFlowDone())
			{
				SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_CST_Z_SEND_POS, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_CST_Z_SEND_POS"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_ERROR, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_MOVE_CST_TO_CST_FLOW_GANTRY_ZXY_READY_CHECK, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_GANTRY_ZXY_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //1. CST Z, PiciupUnit Send Ready
		case _eSTICK_MOVE_CST_TO_CST_FLOW_CST_Z_SEND_POS:
			Devs::m_CassetteMotion.CassetteZ_1FloorPos(); //Temp !!

			SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_CST_Z_SEND_POS_CHECK, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_CST_Z_SEND_POS_CHECK"));
			break;

		case _eSTICK_MOVE_CST_TO_CST_FLOW_CST_Z_SEND_POS_CHECK:
			if (Devs::m_CassetteMotion.Is_CassetteZ_1FloorPos())
			{
				SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_CST_PICKUP_UNIT_UNCLMAP_1ST, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_CST_PICKUP_UNIT_UNCLMAP_1ST"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_ERROR, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_MOVE_CST_TO_CST_FLOW_CST_Z_SEND_POS_CHECK, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_CST_Z_SEND_POS_CHECK"));
			}
			break;

		case _eSTICK_MOVE_CST_TO_CST_FLOW_CST_PICKUP_UNIT_UNCLMAP_1ST:
			Devs::m_CassetteMotion.CSTPickUpUnitUnclamp();
			Sleep(500); //!!

			SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_CST_PICKUP_UNIT_UNCLMAP_1ST_CHECK, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_CST_PICKUP_UNIT_UNCLMAP_1ST_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_MOVE_CST_TO_CST_FLOW_CST_PICKUP_UNIT_UNCLMAP_1ST_CHECK:
			if (Devs::m_CassetteMotion.Is_CSTPickUpUnitUnclamp())
			{
				SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_CST_PICKUP_UNIT_FWD_1ST, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_CST_PICKUP_UNIT_FWD_1ST"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_ERROR, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_MOVE_CST_TO_CST_FLOW_CST_PICKUP_UNIT_UNCLMAP_1ST_CHECK, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_CST_PICKUP_UNIT_UNCLMAP_1ST_CHECK"));
			}
			break;

		case _eSTICK_MOVE_CST_TO_CST_FLOW_CST_PICKUP_UNIT_FWD_1ST:
			Devs::m_CassetteMotion.CSTPickUpUnitFwd();
			Sleep(500); //!!

			SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_CST_PICKUP_UNIT_FWD_1ST_CHECK, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_CST_PICKUP_UNIT_FWD_1ST_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_MOVE_CST_TO_CST_FLOW_CST_PICKUP_UNIT_FWD_1ST_CHECK:
			if (Devs::m_CassetteMotion.Is_CSTPickUpUnitFwd())
			{
				SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_CST_PICKUP_UNIT_CLMAP, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_CST_PICKUP_UNIT_CLMAP"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_ERROR, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_MOVE_CST_TO_CST_FLOW_CST_PICKUP_UNIT_FWD_1ST_CHECK, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_CST_PICKUP_UNIT_FWD_1ST_CHECK"));
			}
			break;

		case _eSTICK_MOVE_CST_TO_CST_FLOW_CST_PICKUP_UNIT_CLMAP:
			Devs::m_CassetteMotion.CSTPickUpUnitClamp();
			Sleep(500); //!!

			SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_CST_PICKUP_UNIT_CLMAP_CHECK, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_CST_PICKUP_UNIT_CLMAP_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_MOVE_CST_TO_CST_FLOW_CST_PICKUP_UNIT_CLMAP_CHECK:
			if (Devs::m_CassetteMotion.Is_CSTPickUpUnitClamp())
			{
				SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_CST_PICKUP_UNIT_BWD_1ST, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_CST_PICKUP_UNIT_BWD_1ST"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_ERROR, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_MOVE_CST_TO_CST_FLOW_CST_PICKUP_UNIT_CLMAP_CHECK, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_CST_PICKUP_UNIT_CLMAP_CHECK"));
			}
			break;

		case _eSTICK_MOVE_CST_TO_CST_FLOW_CST_PICKUP_UNIT_BWD_1ST:
			Devs::m_CassetteMotion.CSTPickUpUnitBwd();
			Sleep(500); //!!

			SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_CST_PICKUP_UNIT_BWD_1ST_CHECK, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_CST_PICKUP_UNIT_BWD_1ST_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_MOVE_CST_TO_CST_FLOW_CST_PICKUP_UNIT_BWD_1ST_CHECK:
			if (Devs::m_CassetteMotion.Is_CSTPickUpUnitBwd())
			{
				//if (SharedInfo::DInputValue[_DIN_MAGAZINE_SAFETY_POS_DETECT_2]/* && SharedInfo::DInputValue[_DIN_MAGAZINE_EXIST_DETECT_1]*/)
				//	SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_Y_LOAD_IN_CST_POS, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_Y_LOAD_IN_CST_POS"));
				//else
				//{
				//	Total_Msg(_T("Check CST Detect !!"));
				//	SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_ERROR, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_ERROR"));
				//}
			}
			else if (IsTimeOut())
			{
				SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_ERROR, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_MOVE_CST_TO_CST_FLOW_CST_PICKUP_UNIT_BWD_1ST_CHECK, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_CST_PICKUP_UNIT_BWD_1ST_CHECK"));
			}
			break;
#pragma endregion

#pragma region //2. Stick Load In CST
		case _eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_Y_LOAD_IN_CST_POS:
			Devs::m_UnloaderMotion.GantryY_StickLoadInCstPos(m_SourceSlot);

			SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_Y_LOAD_IN_CST_POS_CHECK, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_Y_LOAD_IN_CST_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_Y_LOAD_IN_CST_POS_CHECK:
			if (Devs::m_UnloaderMotion.Is_UnloaderY_LoadInCstPos(m_SourceSlot))
			{
				SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_Z_LOAD_IN_CST_POS, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_Z_LOAD_IN_CST_POS"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_ERROR, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_Y_LOAD_IN_CST_POS_CHECK, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_Y_LOAD_IN_CST_POS_CHECK"));
			}
			break;

		case _eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_Z_LOAD_IN_CST_POS:
			//Devs::m_UnloaderMotion.UnloaderZ_UnloadToCstPos();

			SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_Z_LOAD_IN_CST_CHECK, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_Z_LOAD_IN_CST_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_Z_LOAD_IN_CST_CHECK:
			if (Devs::m_UnloaderMotion.Is_UnloaderZ_UnloadToCstPos())
			{
				SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_VAC_ON, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_VAC_ON"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_ERROR, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_Z_LOAD_IN_CST_CHECK, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_Z_LOAD_IN_CST_CHECK"));
			}
			break;

		case _eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_VAC_ON:
			Devs::m_UnloaderMotion.Stick_Active_Vac_On();

			SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_STEP_DOWN, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_STEP_DOWN"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_STEP_DOWN:
			m_dTargetPosUldZ = SharedInfo::GetCmdPos(AXIS_UNLOADER_Z);
			m_dTargetPosUldZ -= CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_StepDownOffset;
			if (SharedInfo::CheckSafetyPos(AXIS_UNLOADER_Z, m_dTargetPosUldZ, &Str, &nSafetyPosErrorBy) == FALSE)
			{
				Total_Msg(Str);
				SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_ERROR, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_ERROR"));
				break;
			}

			Devs::m_UnloaderMotion.MoveAxis(AXIS_UNLOADER_Z, m_dTargetPosUldZ);
			Str.Format(_T("Unloader Z Step Down %.5f (To Pos : %.5f)"), CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_StepDownOffset, m_dTargetPosUldZ);
			Total_Msg(Str);

			SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_Z_STICK_LOAD_STEP_DOWN_CHECK, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_Z_STICK_LOAD_STEP_DOWN_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_Z_STICK_LOAD_STEP_DOWN_CHECK:
			if (Devs::m_UnloaderMotion.IsMoveDone(AXIS_UNLOADER_Z, m_dTargetPosUldZ))
			{
				Sleep(1000); //!!
				SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_VAC_ON_CHECK, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_VAC_ON_CHECK"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_ERROR, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_Z_STICK_LOAD_STEP_DOWN_CHECK, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_Z_STICK_LOAD_STEP_DOWN_CHECK"));
			}
			break;

		case _eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_VAC_ON_CHECK:
			if (Devs::m_UnloaderMotion.Is_Stick_Active_Vac_On())
			{
				SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_Z_WAIT_POS, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_Z_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_ERROR, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_STEP_DOWN, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_STEP_DOWN"));
			}
			break;

		case _eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_Z_WAIT_POS:
			Devs::m_UnloaderMotion.UnloaderZ_WaitPos();

			SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_Z_WAIT_POS_CHECK, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_Z_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_Z_WAIT_POS_CHECK:
			if (Devs::m_UnloaderMotion.Is_UnloaderZ_WaitPos())
			{
				if (Devs::m_UnloaderMotion.Is_Stick_Active_Vac_On() == FALSE)
				{
					Total_Msg(_T("Check Unlaoder Stick Active Vac On !!!"));
					SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_ERROR, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_ERROR"));
				}
				else
				{
					//To Do
				}
			}
			else if (IsTimeOut())
			{
				SetStep(_eSTICK_MOVE_CST_TO_CST_FLOW_ERROR, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_Z_WAIT_POS_CHECK, _T("_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_Z_WAIT_POS_CHECK"));
			}
			break;
#pragma endregion

		case _eSTICK_MOVE_CST_TO_CST_FLOW_ERROR:
			break;

		case _eSTICK_MOVE_CST_TO_CST_FLOW_DONE:
			m_bFlowDone = TRUE;
			break;
		}

		Sleep(100); //!!
	}
#endif
}

BOOL CStickMoveCstToCstFlow::FlowInterlock()
{
#if 0
	CString Str = _T("");

#ifndef SIM_MODE
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
#endif

	if (m_SourceFloor == m_TargetFloor && m_SourceSlot == m_TargetSlot)
	{
		Total_Msg(_T("Check Source/Target !!!"));
		return FALSE;
	}

	if (SharedInfo::CstStickExistInfo.bExistStick[m_SourceFloor][m_SourceSlot] == FALSE)
	{
		Str.Format(_T("Check Exist Stick In CST (Floor:%d, Slot:%d)"), m_SourceFloor + 1, m_SourceSlot + 1);
		Total_Msg(Str);
		return FALSE;
	}
	if (SharedInfo::CstStickExistInfo.bExistStick[m_TargetFloor][m_TargetSlot] == TRUE)
	{
		Str.Format(_T("Check Not Exist Stick In CST (Floor:%d, Slot:%d)"), m_TargetFloor + 1, m_TargetSlot + 1);
		Total_Msg(Str);
		return FALSE;
	}
#endif
	return TRUE;
}