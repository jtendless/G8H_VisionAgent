#include "stdafx.h"
#include "StickUnloadBoxToStageFlow.h"
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

CStickUnloadBoxToStageFlow::CStickUnloadBoxToStageFlow()
{
}


CStickUnloadBoxToStageFlow::~CStickUnloadBoxToStageFlow()
{
}

BOOL CStickUnloadBoxToStageFlow::InitProcess()
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
	m_sGroupInfo[nGroupIndex].nStartStep = _eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_START;
	m_sGroupInfo[nGroupIndex].nEndStep = _eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_INTERLOCK;
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
BOOL CStickUnloadBoxToStageFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_IDLE, _T("_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_IDLE"));

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
BOOL CStickUnloadBoxToStageFlow::Start()
{
	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_START, _T("_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_START"));
	return TRUE;
}
BOOL CStickUnloadBoxToStageFlow::Stop()
{
	m_bStopBit = TRUE;
	//SetStop(); //!!
	return TRUE;
}
UINT CStickUnloadBoxToStageFlow::ThreadFunction(LPVOID lpParam)
{
	CStickUnloadBoxToStageFlow* pFlow = NULL;

	pFlow = (CStickUnloadBoxToStageFlow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}
VOID CStickUnloadBoxToStageFlow::ThreadFunctionEntry(VOID)
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

			SetCurrentStep(_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_IDLE);
			continue; //!!
		}

		switch (GetCurrentTotalStep())
		{
		case _eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_IDLE:
		{
			break;
		}
		case _eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_START:
		{
			m_timeStart = CTime::GetCurrentTime(); //KJT 20210329
			SharedInfo::m_timeUnitTact = m_timeStart;

			SharedInfo::nCurFlowID = eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW;

			m_nStepDownCount = 0;
			m_nVibrationCount = 0;
			m_nMaxStepDownCount = CManualData::m_ManualDataLoader.Info.m_nLoaderZ_StepDownCount;
			m_nMaxVibrationCount = CManualData::m_ManualDataLoader.Info.m_nLoaderZ_VibrationCount;

			SharedInfo::LightAllOff();

			SetStep(_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_INTERLOCK, _T("_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_INTERLOCK"));
			break;
		}
		case _eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_INTERLOCK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_ERROR, _T("_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				m_bGroupStepDone[m_nGroupStepIndex++] = TRUE; //KJT 20210221

				memcpy(SharedInfo::Active.tchStickId, SharedInfo::BoxStickExistInfo.tchStickId[eBOX_SHEET_MAX - SharedInfo::BoxStickExistInfo.nStickCount], sizeof(SharedInfo::Active.tchStickId));
				SharedInfo::SetAcitveStickPos(eACTIVE_STICK_POS_BOX); //KJT 20210328
				
				SetStep(_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_INSPECTION_UVW_STICK_LOAD_POS, _T("_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_INSPECTION_UVW_STICK_LOAD_POS"));					
			}
			break;

#pragma region //Inspection Uvw Ready
		case _eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_INSPECTION_UVW_STICK_LOAD_POS:			
			Devs::m_InspectionStageMotion.InspectionStageUVW_WaitPos();
			Sleep(500); //!		

			SetStep(_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_INSPECTION_UVW_STICK_LOAD_POS_CHECK, _T("_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_INSPECTION_UVW_STICK_LOAD_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_INSPECTION_UVW_STICK_LOAD_POS_CHECK:			
			if (Devs::m_InspectionStageMotion.Is_InspectionStageUVW_WaitPos())
			{
				SetStep(_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_Y_STICK_UNLOAD_TO_INSPECTION_STAGE_POS, _T("_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_Y_STICK_UNLOAD_TO_INSPECTION_STAGE_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_INSPECTION_UVW_STICK_LOAD_POS_CHECK : Time Out"), eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW + 5);
				SetStep(_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_ERROR, _T("_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_INSPECTION_UVW_STICK_LOAD_POS_CHECK, _T("_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_INSPECTION_UVW_STICK_LOAD_POS_CHECK"));
			}
			break;
#pragma endregion

#pragma region //2. Unload To Inspection Stage
		case _eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_Y_STICK_UNLOAD_TO_INSPECTION_STAGE_POS:
			Devs::m_LoaderMotion.LoaderY_Stick_UnloadPos();
			Sleep(20); //!!!

			SetStep(_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_Y_STICK_UNLOAD_TO_INSPECTION_STAGE_POS_CHECK, _T("_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_Y_STICK_UNLOAD_TO_INSPECTION_STAGE_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_Y_STICK_UNLOAD_TO_INSPECTION_STAGE_POS_CHECK:
			if (Devs::m_LoaderMotion.Is_LoaderY_Stick_UnloadPos())
			{
				m_bGroupStepDone[m_nGroupStepIndex++] = TRUE; //KJT 20210221
				SetStep(_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_UNLOAD_DOWN_POS, _T("_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_UNLOAD_DOWN_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_Y_STICK_UNLOAD_TO_INSPECTION_STAGE_POS_CHECK : Time Out"), eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW + 30);
				SetStep(_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_ERROR, _T("_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_Y_STICK_UNLOAD_TO_INSPECTION_STAGE_POS_CHECK, _T("_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_Y_STICK_UNLOAD_TO_INSPECTION_STAGE_POS_CHECK"));
			}
			break;

		case _eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_UNLOAD_DOWN_POS:
			Devs::m_LoaderMotion.LoaderZ_StickUnloadToStagePos();

			SetStep(_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_UNLOAD_DOWN_POS_CHECK, _T("_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_UNLOAD_DOWN_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_UNLOAD_DOWN_POS_CHECK:
			if (Devs::m_LoaderMotion.Is_LoaderZ_StickUnloadToStagePos())
			{
				SetStep(_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_VAC_OFF, _T("_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_VAC_OFF"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_UNLOAD_DOWN_POS_CHECK : Time Out"), eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW + 31);
				SetStep(_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_ERROR, _T("_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_UNLOAD_DOWN_POS_CHECK, _T("_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_UNLOAD_DOWN_POS_CHECK"));
			}
			break;

		case _eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_VAC_OFF:
			Devs::m_LoaderMotion.Stick_Active_Vac_Off();
			Sleep(500); //!! //KJT 20210317

			SetStep(_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_VAC_OFF_CHECK, _T("_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_VAC_OFF_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_VAC_OFF_CHECK:
			if (Devs::m_LoaderMotion.Is_Stick_Active_Vac_Off())
			{
				SharedInfo::SetAcitveStickPos(eACTIVE_STICK_POS_INSPECTION_STAGE); //KJT 20210328

				SetStep(_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_INSPECTION_STAGE_VAC_ON, _T("_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_INSPECTION_STAGE_VAC_ON"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_VAC_OFF_CHECK : Time Out"), eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW + 32);
				SetStep(_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_ERROR, _T("_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_VAC_OFF_CHECK, _T("_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_VAC_OFF_CHECK"));
			}
			break;

		case _eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_INSPECTION_STAGE_VAC_ON:
			Devs::m_InspectionStageMotion.Inspect_Stage_Vac_On();
			Sleep(500); //!! //KJT 20210317

			SetStep(_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_Z_FINISH_WAIT_POS, _T("_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_Z_FINISH_WAIT_POS"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_Z_FINISH_WAIT_POS:
			Devs::m_LoaderMotion.LoaderZ_WaitPos();

			SetStep(_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_Z_FINISH_WAIT_POS_CHECK, _T("_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_Z_FINISH_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_Z_FINISH_WAIT_POS_CHECK:
			if (Devs::m_LoaderMotion.Is_LoaderZ_WaitPos())
			{
				SetStep(_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_X_FINISH_WAIT_POS, _T("_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_X_FINISH_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_UNLOAD_WAIT_POS_CHECK : Time Out"), eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW + 33);
				SetStep(_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_ERROR, _T("_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_Z_FINISH_WAIT_POS_CHECK, _T("_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_Z_FINISH_WAIT_POS_CHECK"));
			}
			break;

		case _eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_X_FINISH_WAIT_POS:
			Devs::m_LoaderMotion.LoaderX_WaitPos();

			SetStep(_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_X_FINISH_WAIT_POS_CHECK, _T("_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_X_FINISH_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_X_FINISH_WAIT_POS_CHECK:
			if (Devs::m_LoaderMotion.Is_LoaderX_WaitPos())
			{
				SetStep(_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_Y_FINISH_WAIT_POS, _T("_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_Y_FINISH_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_X_FINISH_WAIT_POS_CHECK : Time Out"), eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW + 33);
				SetStep(_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_ERROR, _T("_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_X_FINISH_WAIT_POS_CHECK, _T("_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_X_FINISH_WAIT_POS_CHECK"));
			}
			break;

		case _eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_Y_FINISH_WAIT_POS:
			Devs::m_LoaderMotion.LoaderY_WaitPos();
			Sleep(20); //!!!

			SetStep(_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_Y_FINISH_WAIT_POS_CHECK, _T("_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_Y_FINISH_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_Y_FINISH_WAIT_POS_CHECK:
			if (Devs::m_LoaderMotion.Is_LoaderY_WaitPos())
			{
				SetStep(_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_DONE, _T("_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_Y_FINISH_WAIT_POS_CHECK : Time Out"), eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW + 34);
				SetStep(_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_ERROR, _T("_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_Y_FINISH_WAIT_POS_CHECK, _T("_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_Y_FINISH_WAIT_POS_CHECK"));
			}
			break;
#pragma endregion //2. Unload To Inspection Stage

		case _eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_ERROR:
			Devs::m_BoxMotion.BoxMagnetic_Chuck_Off();
			break;

		case _eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_DONE:
		{
			Devs::m_BoxMotion.BoxMagnetic_Chuck_Off();

			SharedInfo::nPrevFlowID = eSTICK_LOAD_IN_BOX_TO_STAGE_FLOW; //KJT 20210326

			m_bFlowDone = TRUE;

			SharedInfo::CalTactTime(_T("STICK_LOAD_IN_BOX_TO_STAGE_FLOW"), m_timeStart); //KJT 20210329

			SetStep(_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_IDLE, _T("_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_IDLE"));
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
BOOL CStickUnloadBoxToStageFlow::FlowInterlock()
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