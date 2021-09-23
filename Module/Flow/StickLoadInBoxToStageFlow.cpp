#include "stdafx.h"
#include "StickLoadInBoxToStageFlow.h"
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

CStickLoadInBoxToStageFlow::CStickLoadInBoxToStageFlow()
{
}


CStickLoadInBoxToStageFlow::~CStickLoadInBoxToStageFlow()
{
}

BOOL CStickLoadInBoxToStageFlow::InitProcess()
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
	m_sGroupInfo[nGroupIndex].nStartStep = _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_START;
	m_sGroupInfo[nGroupIndex].nEndStep = _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_INTERLOCK;
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

	hHandle = CreateEvent(NULL, TRUE, FALSE, NULL);
	SetHandle(hHandle);
	pThread = AfxBeginThread(ThreadFunction, this);
	//pMappingProc = CMappingProc::GetInstance();
	return TRUE;
}
BOOL CStickLoadInBoxToStageFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_IDLE, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_IDLE"));

	//do
	//{
	//	Sleep(10);
	//} while (IsTerminate() == 0);

	if (hHandle != NULL)
	{
		CloseHandle(hHandle);
	}

	return TRUE;
}
BOOL CStickLoadInBoxToStageFlow::Start(int nStep)
{
	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(nStep, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_START"));
	return TRUE;
}
BOOL CStickLoadInBoxToStageFlow::Stop()
{
	m_bStopBit = TRUE;
	//SetStop(); //!!
	return TRUE;
}
UINT CStickLoadInBoxToStageFlow::ThreadFunction(LPVOID lpParam)
{
	CStickLoadInBoxToStageFlow* pFlow = NULL;

	pFlow = (CStickLoadInBoxToStageFlow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}
VOID CStickLoadInBoxToStageFlow::ThreadFunctionEntry(VOID)
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

		if (SharedInfo::bMachineStopFlag == TRUE)// && m_bStopBit == FALSE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_IDLE);
			continue; //!!
		}

		switch (GetCurrentTotalStep())
		{
		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_IDLE:
		{
			break;
		}
		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_START:
		{
			m_timeStart = CTime::GetCurrentTime(); //KJT 20210329
			SharedInfo::m_timeUnitTact = m_timeStart;

			SharedInfo::nCurFlowID = eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW;

			m_nStepDownCount = 0;
			m_nVibrationCount = 0;
			m_nMaxStepDownCount = CManualData::m_ManualDataLoader.Info.m_nLoaderZ_StepDownCount;
			m_nMaxVibrationCount = CManualData::m_ManualDataLoader.Info.m_nLoaderZ_VibrationCount;

			SharedInfo::LightAllOff();

			SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_INTERLOCK, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_INTERLOCK"));
			break;
		}
		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_INTERLOCK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				m_bGroupStepDone[m_nGroupStepIndex++] = TRUE; //KJT 20210221

				memcpy(SharedInfo::Active.tchStickId, SharedInfo::BoxStickExistInfo.tchStickId[eBOX_SHEET_MAX - SharedInfo::BoxStickExistInfo.nStickCount], sizeof(SharedInfo::Active.tchStickId));
				SharedInfo::SetAcitveStickPos(eACTIVE_STICK_POS_BOX); //KJT 20210328
				
				if (SharedInfo::MachineState.bAutoRunFlag == TRUE)
					SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_INSPECTION_UVW_STICK_LOAD_POS, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_INSPECTION_UVW_STICK_LOAD_POS"));
				else
					SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_UNLOADER_READY, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_UNLOADER_READY"));
			}
			break;

#pragma region //Unloader Ready
		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_UNLOADER_READY:
			Devs::m_Ready_UnloaderFlow.Start();

			SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_UNLOADER_READY_CHECK, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_UNLOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_UNLOADER_READY_CHECK:
			if (Devs::m_Ready_UnloaderFlow.IsFlowDone())
			{
				SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_GANTRY_ZXY_READY, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_GANTRY_ZXY_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_UNLOADER_READY_CHECK : Time Out"), eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW + 0);
				SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_UNLOADER_READY_CHECK, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_UNLOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Gantry Z,X Ready
		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_GANTRY_ZXY_READY:
			Devs::m_Ready_GantryAvoidBoxFlow.Start();

			SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_GANTRY_ZXY_READY_CHECK, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_GANTRY_ZXY_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_GANTRY_ZXY_READY_CHECK:
			if (Devs::m_Ready_GantryAvoidBoxFlow.IsFlowDone())
			{
				SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_ZX_READY, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_ZX_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_GANTRY_ZXY_READY_CHECK : Time Out"), eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW + 2);
				SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_GANTRY_ZXY_READY_CHECK, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_GANTRY_ZXY_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Loader ZX Ready
		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_ZX_READY:
			Devs::m_Ready_LoaderFlow.Start();

			SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_ZX_READY_CHECK, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_ZX_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_ZX_READY_CHECK:
			if (Devs::m_Ready_LoaderFlow.IsFlowDone())
			{
				SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_PAPER_UNLOADER_ZXY_READY, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_PAPER_UNLOADER_ZXY_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_ZX_READY_CHECK : Time Out"), eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW + 1);
				SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_ZX_READY_CHECK, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_ZX_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //PaperUnloader Ready
		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_PAPER_UNLOADER_ZXY_READY:
			Devs::m_Ready_PaperUnloaderFlow.Start();

			SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK:
			if (Devs::m_Ready_PaperUnloaderFlow.IsFlowDone())
			{
#ifndef GRIPPER_0
				SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_GRIPPER_READY, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_GRIPPER_READY"));
#else
				SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_INSPECTION_UVW_STICK_LOAD_POS, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_INSPECTION_UVW_STICK_LOAD_POS"));
#endif
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK : Time Out"), eBOX_ALIGN_FLOW + 1);
				SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK"));
			}
			break;
#pragma endregion

#ifndef GRIPPER_0
#pragma region //Gripper Ready
		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_GRIPPER_READY:
			Devs::m_Ready_Gripper_Flow.Start();

			SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_GRIPPER_READY_CHECK, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_GRIPPER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_GRIPPER_READY_CHECK:
			if (Devs::m_Ready_Gripper_Flow.IsFlowDone())
			{
				SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_INSPECTION_UVW_STICK_LOAD_POS, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_INSPECTION_UVW_STICK_LOAD_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_GRIPPER_READY_CHECK : Time Out"), eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW + 4);
				SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_GRIPPER_READY_CHECK, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_GRIPPER_READY_CHECK"));
			}
			break;
#pragma endregion
#endif

#pragma region //Inspection Uvw Ready
		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_INSPECTION_UVW_STICK_LOAD_POS:			
			Devs::m_InspectionStageMotion.InspectionStageUVW_WaitPos();
			Sleep(500); //!		

			SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_INSPECTION_UVW_STICK_LOAD_POS_CHECK, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_INSPECTION_UVW_STICK_LOAD_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_INSPECTION_UVW_STICK_LOAD_POS_CHECK:			
			if (Devs::m_InspectionStageMotion.Is_InspectionStageUVW_WaitPos())
			{
				SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Y_LOAD_IN_BOX_POS, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Y_LOAD_IN_BOX_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_INSPECTION_UVW_STICK_LOAD_POS_CHECK : Time Out"), eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW + 5);
				SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_INSPECTION_UVW_STICK_LOAD_POS_CHECK, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_INSPECTION_UVW_STICK_LOAD_POS_CHECK"));
			}
			break;
#pragma endregion

#pragma region //1. Loader Pickup In Box
		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Y_LOAD_IN_BOX_POS:
			Devs::m_LoaderMotion.LoaderY_Stick_LoadPos();
			Sleep(20); //!!!
			SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Y_LOAD_IN_BOX_POS_CHECK, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Y_LOAD_IN_BOX_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Y_LOAD_IN_BOX_POS_CHECK:
			if (Devs::m_LoaderMotion.Is_LoaderY_Stick_LoadPos())
			{
				SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_X_LOAD_IN_BOX_POS, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_X_LOAD_IN_BOX_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Y_LOAD_IN_BOX_POS_CHECK : Time Out"), eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW + 6);
				SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Y_LOAD_IN_BOX_POS_CHECK);
			}
			break;

		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_X_LOAD_IN_BOX_POS:
			Devs::m_LoaderMotion.LoaderX_StickPickUpPos();

			SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_X_LOAD_IN_BOX_POS_CHECK, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_X_LOAD_IN_BOX_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_X_LOAD_IN_BOX_POS_CHECK:
			if (Devs::m_LoaderMotion.Is_LoaderX_StickPickUpPos())
			{
				SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_DOWN_POS, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_DOWN_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_X_LOAD_IN_BOX_POS_CHECK : Time Out"), eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW + 7);
				SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_X_LOAD_IN_BOX_POS_CHECK, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_X_LOAD_IN_BOX_POS_CHECK"));
			}
			break;

		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_DOWN_POS:
			m_dTargetPosZ = CManualData::m_ManualDataLoader.Info.m_dLoaderZ_StickLoadInBox1st_Pos;
			dOffset = (CModelData::m_AtMaterialPara.Info.dPaperThickness * (eBOX_SHEET_MAX - SharedInfo::BoxStickExistInfo.nStickCount)) * (-1);
			dOffset += (CModelData::m_AtMaterialPara.Info.dStickThickness * (eBOX_SHEET_MAX - SharedInfo::BoxStickExistInfo.nStickCount)) * (-1);
			m_dTargetPosZ += dOffset;

			if (SharedInfo::CheckSafetyPos(AXIS_LOADER_Z, m_dTargetPosZ, &Str, &nSafetyPosErrorBy) == FALSE)
			{
				if (nSafetyPosErrorBy == eTARGET_POS_ERROR_BY_SAFETY_MIN)
					SharedInfo::SetAxisAlarm(AXIS_LOADER_Z, eTARGET_POS_ERROR_BY_SAFETY_MIN);
				else if (nSafetyPosErrorBy == eTARGET_POS_ERROR_BY_SAFETY_MAX)
					SharedInfo::SetAxisAlarm(AXIS_LOADER_Z, eTARGET_POS_ERROR_BY_SAFETY_MAX);

				Total_Msg(Str);
				SharedInfo::SetAlarm(_T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_DOWN_POS : AXIS_LOADER_Z Pos Limit"), eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW + 8);
				SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR"));
				break;
			}

			Devs::m_LoaderMotion.MoveAxis(AXIS_LOADER_Z, m_dTargetPosZ);
			Str.Format(_T("Loader Z Stick Load Pos Down %.5f (Offset Pos : %.5f)"), m_dTargetPosZ, dOffset);
			Total_Msg(Str);

			SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_DOWN_POS_CHECK, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_DOWN_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_DOWN_POS_CHECK:
			if (Devs::m_LoaderMotion.IsMoveDone(AXIS_LOADER_Z, m_dTargetPosZ))
			{
				SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_VAC_ON, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_VAC_ON"));				
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_DOWN_POS_CHECK : Time Out"), eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW + 10);
				SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_DOWN_POS_CHECK, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_DOWN_POS_CHECK"));
			}
			break;

		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_VAC_ON:
			//Devs::m_BoxMotion.BoxMagnetic_Chuck_On();
			//Sleep(100);
			//Devs::m_LoaderMotion.Paper_Active_Vac_On();
			//Sleep(50);
			Devs::m_LoaderMotion.Stick_Active_Vac_On();
			Sleep(10);
			SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_STEP_DOWN, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_STEP_DOWN"));
			break;

		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_STEP_DOWN:
			m_dTargetPosZ = SharedInfo::GetCmdPos(AXIS_LOADER_Z);
			m_dTargetPosZ -= CManualData::m_ManualDataLoader.Info.m_dLoaderZ_StepDownOffset;
			if (SharedInfo::CheckSafetyPos(AXIS_LOADER_Z, m_dTargetPosZ, &Str, &nSafetyPosErrorBy) == FALSE)
			{
				if (nSafetyPosErrorBy == eTARGET_POS_ERROR_BY_SAFETY_MIN)
					SharedInfo::SetAxisAlarm(AXIS_LOADER_Z, eTARGET_POS_ERROR_BY_SAFETY_MIN);
				else if (nSafetyPosErrorBy == eTARGET_POS_ERROR_BY_SAFETY_MAX)
					SharedInfo::SetAxisAlarm(AXIS_LOADER_Z, eTARGET_POS_ERROR_BY_SAFETY_MAX);

				Total_Msg(Str);
				SharedInfo::SetAlarm(_T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_STEP_DOWN : AXIS_LOADER_Z Pos Limit"), eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW + 11);
				SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR"));
				break;
			}

			Devs::m_LoaderMotion.MoveAxis(AXIS_LOADER_Z, m_dTargetPosZ);
			Str.Format(_T("Loader Z Step Down %.5f (To Pos : %.5f)"), CManualData::m_ManualDataLoader.Info.m_dLoaderZ_StepDownOffset, m_dTargetPosZ);
			Total_Msg(Str);

			SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_STEP_DOWN_CHECK, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_STEP_DOWN_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_STEP_DOWN_CHECK:
			if (Devs::m_LoaderMotion.IsMoveDone(AXIS_LOADER_Z, m_dTargetPosZ))
			{
				Sleep(100);

				if (Devs::m_LoaderMotion.Is_Stick_Active_Vac_On())
				{
					m_nVibrationCount = 0; //KJT 20210317
					SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_STEP_UP, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_STEP_UP")); //KJT 20210316
					break;
				}
				else if (++m_nStepDownCount < m_nMaxStepDownCount)
				{
					SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_STEP_DOWN, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_STEP_DOWN"));
				}
				else
				{
					Str.Format(_T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_STEP_DOWN_CHECK : Count %d Over"), m_nMaxStepDownCount);
					SharedInfo::SetAlarm(Str, eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW + 12);
					SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR"));
				}
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_STEP_DOWN_CHECK : Time Out"), eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW + 12);
				SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_STEP_DOWN_CHECK, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_STEP_DOWN_CHECK"));
			}
			break;

		//case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_VAC_ON_CHECK:
		//	if (Devs::m_BoxMotion.Is_BoxMagnetic_Chuck_On() && Devs::m_LoaderMotion.Is_Stick_Active_Vac_On() && Devs::m_LoaderMotion.Is_Paper_Active_Vac_On())
		//	{
		//		m_bGroupStepDone[m_nGroupStepIndex++] = TRUE; //KJT 20210221

		//		//Sleep(1000); //!!
		//		Sleep(500); //!!
		//		if (SharedInfo::BoxStickExistInfo.nStickCount > 1)
		//		{
		//			m_nVibrationCount = 0; //KJT 20210317
		//			SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_STEP_UP, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_STEP_UP")); //KJT 20210316
		//		}
		//		else //KJT 20210328
		//		{
		//			SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_WAIT_POS, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_WAIT_POS")); //KJT 20210316
		//		}
		//	}
		//	else
		//	{
		//		SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_STEP_DOWN, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_STEP_DOWN"));
		//	}
		//	break;

		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_STEP_UP: //KJT 20210316
			m_dTargetPosZ = SharedInfo::GetCmdPos(AXIS_LOADER_Z);
			m_dTargetPosZ += CManualData::m_ManualDataLoader.Info.m_dLoaderZ_StepUpOffset;

			Devs::m_LoaderMotion.MoveAxis(AXIS_LOADER_Z, m_dTargetPosZ);
			Str.Format(_T("Loader Z Step Up %.5f (To Pos : %.5f)"), CManualData::m_ManualDataLoader.Info.m_dLoaderZ_StepUpOffset, m_dTargetPosZ);
			Total_Msg(Str);

			SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_STEP_UP_CHECK, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_STEP_UP_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_STEP_UP_CHECK: //KJT 20210316
			if (Devs::m_LoaderMotion.IsMoveDone(AXIS_LOADER_Z, m_dTargetPosZ))
			{
				//Sleep(3000); //!!
				//Sleep(1000); //!!
				//if (SharedInfo::GetCmdPos(AXIS_LOADER_Z) >= CManualData::m_ManualDataLoader.Info.m_dLoaderZ_Vibration_Pos)
				//	SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_VIBRATION_DOWN_POS, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_VIBRATION_DOWN_POS"));
				//else
				//	SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_STEP_UP, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_STEP_UP"));

				SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_VIBRATION_UP_POS, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_VIBRATION_UP_POS"));			
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_STEP_UP_CHECK : Time Out"), eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW + 13);
				SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_STEP_UP_CHECK, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_STEP_UP_CHECK"));
			}
			break;

		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_VIBRATION_UP_POS: //KJT 20210317
			m_dTargetPosZ = SharedInfo::GetCmdPos(AXIS_LOADER_Z);
			m_dTargetPosZ += CManualData::m_ManualDataLoader.Info.m_dLoaderZ_VibrationOffset;

			//KJT 20210323
			dVel = CManualData::m_ManualDataLoader.Info.m_dLoaderZ_VibrationVel;
			dAccel = dVel * 5.0;
			dDecel = dVel * 5.0;
			Devs::m_JogMotion.AbsMove(AXIS_LOADER_Z, m_dTargetPosZ, dVel, dAccel, dDecel);

			Str.Format(_T("Loader Z Step Up %.5f (To Pos : %.5f)"), CManualData::m_ManualDataLoader.Info.m_dLoaderZ_VibrationOffset, m_dTargetPosZ);
			Total_Msg(Str);

			SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_VIBRATION_UP_POS_CHECK, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_VIBRATION_UP_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_VIBRATION_UP_POS_CHECK:
			if (Devs::m_LoaderMotion.IsMoveDone(AXIS_LOADER_Z, m_dTargetPosZ))
			{
				//Sleep(500); //!!
				//if (SharedInfo::GetCmdPos(AXIS_LOADER_Z) >= CManualData::m_ManualDataLoader.Info.m_dLoaderZ_Vibration_Pos)
				//	SetStep(_ePAPER_UNLOAD_FLOW_LOADER_Z_VIBRATION_DOWN_POS, _T("_ePAPER_UNLOAD_FLOW_LOADER_Z_VIBRATION_DOWN_POS"));
				//else
				//	SetStep(_ePAPER_UNLOAD_FLOW_LOADER_Z_STICK_LOAD_STEP_UP, _T("_ePAPER_UNLOAD_FLOW_LOADER_Z_STICK_LOAD_STEP_UP"));

				SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_VIBRATION_DOWN_POS, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_VIBRATION_DOWN_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_VIBRATION_UP_POS_CHECK : Time Out"), eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW + 14);
				SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_VIBRATION_UP_POS_CHECK, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_VIBRATION_UP_POS_CHECK"));
			}
			break;


		//case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_VIBRATION_POS: //KJT 20210317
		//	Devs::m_BoxMotion.BoxMagnetic_Chuck_Off();
		//	Sleep(10);
		//	Devs::m_LoaderMotion.LoaderZ_Vibration_Pos();
		//	Sleep(10);

		//	SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_VIBRATION_POS_CHECK, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_VIBRATION_POS_CHECK"));
		//	SetTimeOut(TIME_OUT_MOTION);
		//	break;

		//case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_VIBRATION_POS_CHECK:
		//	if (Devs::m_BoxMotion.Is_BoxMagnetic_Chuck_Off() && Devs::m_LoaderMotion.Is_LoaderZ_Vibration_Pos())
		//	{
		//		SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_VIBRATION_DOWN_POS, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_VIBRATION_DOWN_POS"));
		//	}
		//	else if (IsTimeOut())
		//	{
		//		SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR"));
		//	}
		//	else
		//	{
		//		SetCheckStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_VIBRATION_POS_CHECK, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_VIBRATION_POS_CHECK"));
		//	}
		//	break;

		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_VIBRATION_DOWN_POS: //KJT 20210317
			m_dTargetPosZ = SharedInfo::GetCmdPos(AXIS_LOADER_Z);
			m_dTargetPosZ -= CManualData::m_ManualDataLoader.Info.m_dLoaderZ_VibrationOffset;
			if (SharedInfo::CheckSafetyPos(AXIS_LOADER_Z, m_dTargetPosZ, &Str, &nSafetyPosErrorBy) == FALSE)
			{
				if (nSafetyPosErrorBy == eTARGET_POS_ERROR_BY_SAFETY_MIN)
					SharedInfo::SetAxisAlarm(AXIS_LOADER_Z, eTARGET_POS_ERROR_BY_SAFETY_MIN);
				else if (nSafetyPosErrorBy == eTARGET_POS_ERROR_BY_SAFETY_MAX)
					SharedInfo::SetAxisAlarm(AXIS_LOADER_Z, eTARGET_POS_ERROR_BY_SAFETY_MAX);

				Total_Msg(Str);
				SharedInfo::SetAlarm(_T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_VIBRATION_DOWN_POS : AXIS_LOADER_Z Pos Limit"), eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW + 15);
				SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR"));
				break;
			}

			//KJT 20210323
			dVel = CManualData::m_ManualDataLoader.Info.m_dLoaderZ_VibrationVel;
			dAccel = dVel * 5.0;
			dDecel = dVel * 5.0;
			Devs::m_JogMotion.AbsMove(AXIS_LOADER_Z, m_dTargetPosZ, dVel, dAccel, dDecel);

			Str.Format(_T("Loader Z Vibration Down %.5f (To Pos : %.5f)"), CManualData::m_ManualDataLoader.Info.m_dLoaderZ_VibrationOffset, m_dTargetPosZ);
			Total_Msg(Str);

			//Sleep(1000); //!!
			Sleep(500); //!!
			SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_VIBRATION_DOWN_POS_CHECK, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_VIBRATION_DOWN_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_VIBRATION_DOWN_POS_CHECK:
			if (Devs::m_LoaderMotion.IsMoveDone(AXIS_LOADER_Z, m_dTargetPosZ))
			{
				if (++m_nVibrationCount >= m_nMaxVibrationCount)
					SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_WAIT_POS, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_WAIT_POS"));
				else					
					SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_VIBRATION_UP_POS, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_VIBRATION_UP_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_VIBRATION_DOWN_POS_CHECK : Time Out"), eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW + 16);
				SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_VIBRATION_DOWN_POS_CHECK, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_VIBRATION_DOWN_POS_CHECK"));
			}
			break;

		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_WAIT_POS:
			//Devs::m_BoxMotion.BoxMagnetic_Chuck_Off();
			//Sleep(10);
			Devs::m_LoaderMotion.LoaderZ_WaitPos();

			SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_WAIT_POS_CHECK, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_WAIT_POS_CHECK:
			if (Devs::m_LoaderMotion.Is_LoaderZ_WaitPos())
			{
				if (Devs::m_LoaderMotion.Is_Stick_Active_Vac_On() == FALSE)
				{
					Total_Msg(_T("Check Loader Sitck Active Vac On !!!"));
					SharedInfo::SetAlarm(_T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_WAIT_POS_CHECK : Vac On"), eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW + 17);
					SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR"));
				}
				//else if (Devs::m_LoaderMotion.Is_Paper_Active_Vac_On() == FALSE)
				//{
				//	Total_Msg(_T("Check Loader Paper Active Vac On !!!"));
				//	SharedInfo::SetAlarm(_T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_WAIT_POS_CHECK : Vac On"), eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW + 18);
				//	SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR"));
				//}
				else
				{
					SharedInfo::SetAcitveStickPos(eACTIVE_STICK_POS_LOADER); //KJT 20210328
					SharedInfo::SetBoxStickExistInfo((enum_BoxSheet)(eBOX_SHEET_MAX - SharedInfo::BoxStickExistInfo.nStickCount), FALSE);

					SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_X_TENSION_POS, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_X_TENSION_POS"));
				}
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_WAIT_POS_CHECK : Time Out"), eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW + 19);
				SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_WAIT_POS_CHECK, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_LOAD_WAIT_POS_CHECK"));
			}
			break;

		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_X_TENSION_POS:
			m_dTargetPosX = SharedInfo::GetCmdPos(AXIS_LOADER_X);
			m_dTargetPosX += CManualData::m_ManualDataLoader.Info.m_dLoaderX_Tension_Offset;
			if (SharedInfo::CheckSafetyPos(AXIS_LOADER_X, m_dTargetPosX, &Str, &nSafetyPosErrorBy) == FALSE)
			{
				if (nSafetyPosErrorBy == eTARGET_POS_ERROR_BY_SAFETY_MIN)
					SharedInfo::SetAxisAlarm(AXIS_LOADER_X, eTARGET_POS_ERROR_BY_SAFETY_MIN);
				else if (nSafetyPosErrorBy == eTARGET_POS_ERROR_BY_SAFETY_MAX)
					SharedInfo::SetAxisAlarm(AXIS_LOADER_X, eTARGET_POS_ERROR_BY_SAFETY_MAX);

				Total_Msg(Str);
				SharedInfo::SetAlarm(_T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_X_TENSION_POS : AXIS_LOADER_X Pos Limit"), eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW + 28);
				SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR"));
				break;
			}

			Devs::m_LoaderMotion.MoveAxis(AXIS_LOADER_X, m_dTargetPosX);
			Str.Format(_T("Loader X Tension Offset %.5f (To Pos : %.5f)"), CManualData::m_ManualDataLoader.Info.m_dLoaderX_Tension_Offset, m_dTargetPosX);
			Total_Msg(Str);

			SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_X_TENSION_POS_CHECK, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_X_TENSION_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_X_TENSION_POS_CHECK:
			if (Devs::m_LoaderMotion.IsMoveDone(AXIS_LOADER_X, m_dTargetPosX))
			{
				m_bGroupStepDone[m_nGroupStepIndex++] = TRUE; //KJT 20210221
				SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Y_STICK_UNLOAD_TO_INSPECTION_STAGE_POS, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Y_STICK_UNLOAD_TO_INSPECTION_STAGE_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_X_TENSION_POS_CHECK : Time Out"), eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW + 29);
				SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_X_TENSION_POS_CHECK, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_X_TENSION_POS_CHECK"));
			}
			break;

#pragma region //2. Unload To Inspection Stage
		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Y_STICK_UNLOAD_TO_INSPECTION_STAGE_POS:
			Devs::m_LoaderMotion.LoaderY_Stick_UnloadPos();
			Sleep(20); //!!!

			SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Y_STICK_UNLOAD_TO_INSPECTION_STAGE_POS_CHECK, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Y_STICK_UNLOAD_TO_INSPECTION_STAGE_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Y_STICK_UNLOAD_TO_INSPECTION_STAGE_POS_CHECK:
			if (Devs::m_LoaderMotion.Is_LoaderY_Stick_UnloadPos())
			{
				m_bGroupStepDone[m_nGroupStepIndex++] = TRUE; //KJT 20210221
				SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_UNLOAD_DOWN_POS, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_UNLOAD_DOWN_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Y_STICK_UNLOAD_TO_INSPECTION_STAGE_POS_CHECK : Time Out"), eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW + 30);
				SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Y_STICK_UNLOAD_TO_INSPECTION_STAGE_POS_CHECK, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Y_STICK_UNLOAD_TO_INSPECTION_STAGE_POS_CHECK"));
			}
			break;

		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_UNLOAD_DOWN_POS:
			Devs::m_LoaderMotion.LoaderZ_StickUnloadToStagePos();

			SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_UNLOAD_DOWN_POS_CHECK, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_UNLOAD_DOWN_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_UNLOAD_DOWN_POS_CHECK:
			if (Devs::m_LoaderMotion.Is_LoaderZ_StickUnloadToStagePos())
			{
				SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_VAC_OFF, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_VAC_OFF"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_UNLOAD_DOWN_POS_CHECK : Time Out"), eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW + 31);
				SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_UNLOAD_DOWN_POS_CHECK, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_UNLOAD_DOWN_POS_CHECK"));
			}
			break;

		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_VAC_OFF:
			Devs::m_LoaderMotion.Stick_Active_Vac_Off();
			Sleep(500); //!! //KJT 20210317

			SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_VAC_OFF_CHECK, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_VAC_OFF_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_VAC_OFF_CHECK:
			if (Devs::m_LoaderMotion.Is_Stick_Active_Vac_Off())
			{
				SharedInfo::SetAcitveStickPos(eACTIVE_STICK_POS_INSPECTION_STAGE); //KJT 20210328

				SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_INSPECTION_STAGE_VAC_ON, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_INSPECTION_STAGE_VAC_ON"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_VAC_OFF_CHECK : Time Out"), eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW + 32);
				SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_VAC_OFF_CHECK, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_VAC_OFF_CHECK"));
			}
			break;

		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_INSPECTION_STAGE_VAC_ON:
			Devs::m_InspectionStageMotion.Inspect_Stage_Vac_On();
			Sleep(500); //!! //KJT 20210317

			SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_FINISH_WAIT_POS, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_FINISH_WAIT_POS"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_FINISH_WAIT_POS:
			Devs::m_LoaderMotion.LoaderZ_WaitPos();

			SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_FINISH_WAIT_POS_CHECK, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_FINISH_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_FINISH_WAIT_POS_CHECK:
			if (Devs::m_LoaderMotion.Is_LoaderZ_WaitPos())
			{
				SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_X_FINISH_WAIT_POS, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_X_FINISH_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_UNLOAD_WAIT_POS_CHECK : Time Out"), eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW + 33);
				SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_FINISH_WAIT_POS_CHECK, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Z_FINISH_WAIT_POS_CHECK"));
			}
			break;

		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_X_FINISH_WAIT_POS:
			Devs::m_LoaderMotion.LoaderX_WaitPos();

			SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_X_FINISH_WAIT_POS_CHECK, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_X_FINISH_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_X_FINISH_WAIT_POS_CHECK:
			if (Devs::m_LoaderMotion.Is_LoaderX_WaitPos())
			{
				SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Y_FINISH_WAIT_POS, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Y_FINISH_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_X_FINISH_WAIT_POS_CHECK : Time Out"), eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW + 33);
				SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_X_FINISH_WAIT_POS_CHECK, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_X_FINISH_WAIT_POS_CHECK"));
			}
			break;

		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Y_FINISH_WAIT_POS:
			Devs::m_LoaderMotion.LoaderY_WaitPos();
			Sleep(20); //!!!

			SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Y_FINISH_WAIT_POS_CHECK, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Y_FINISH_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Y_FINISH_WAIT_POS_CHECK:
			if (Devs::m_LoaderMotion.Is_LoaderY_WaitPos())
			{
				SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_DONE, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Y_FINISH_WAIT_POS_CHECK : Time Out"), eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW + 34);
				SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Y_FINISH_WAIT_POS_CHECK, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_LOADER_Y_FINISH_WAIT_POS_CHECK"));
			}
			break;
#pragma endregion //2. Unload To Inspection Stage

		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_ERROR:
			Devs::m_BoxMotion.BoxMagnetic_Chuck_Off();
			break;

		case _eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_DONE:
		{
			Devs::m_BoxMotion.BoxMagnetic_Chuck_Off();

			SharedInfo::nPrevFlowID = eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW; //KJT 20210326

			m_bFlowDone = TRUE;

			SharedInfo::CalTactTime(_T("STICK_LOAD_IN_BOX_TO_STAGE_FLOW"), m_timeStart); //KJT 20210329

			SetStep(_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_IDLE, _T("_eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW_IDLE"));
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
BOOL CStickLoadInBoxToStageFlow::FlowInterlock()
{
	
#ifndef SIM_MODE
		
	if (Devs::m_LoaderMotion.CheckLoaderFlowInterlock(_T("StickLoadInBoxToStageFlow"), eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW, 40) == FALSE)
	{
		return FALSE;
	}

	/////////////////////////////////////////////////////////////////////////////
	if (Devs::m_GantryMotion.CheckGantryXYZFlowInterlock(_T("StickLoadInBoxToStageFlow"), eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW, 60) == FALSE)
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
	//if (SharedInfo::DInputValue[_DIN_MAGAZINE_SAFETY_POS_DETECT_2] == FALSE)
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