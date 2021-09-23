#include "stdafx.h"
#include "PaperLoadUnloadFlow.h"
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

CPaperLoadUnloadFlow::CPaperLoadUnloadFlow()
{
}


CPaperLoadUnloadFlow::~CPaperLoadUnloadFlow()
{
}

BOOL CPaperLoadUnloadFlow::InitProcess()
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
	m_sGroupInfo[nGroupIndex].nStartStep = _ePAPER_LOAD_UNLOAD_FLOW_START;
	m_sGroupInfo[nGroupIndex].nEndStep = _ePAPER_LOAD_UNLOAD_FLOW_INTERLOCK;
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

BOOL CPaperLoadUnloadFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_ePAPER_LOAD_UNLOAD_FLOW_IDLE, _T("_ePAPER_LOAD_UNLOAD_FLOW_IDLE"));

	if (hHandle != NULL)
	{
		CloseHandle(hHandle);
		hHandle = NULL;
	}

	return TRUE;
}
BOOL CPaperLoadUnloadFlow::Start(enum_CassetteFloor eTargetFloor)
{
	m_nStepDownCount = 0;
	m_nVibrationCount = 0;
	m_nMaxStepDownCount = CManualData::m_ManualDataLoader.Info.m_nLoaderZ_StepDownCount;
	m_nMaxVibrationCount = CManualData::m_ManualDataLoader.Info.m_nLoaderZ_VibrationCount;

	m_eTargetFloor = eTargetFloor;

	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(_ePAPER_LOAD_UNLOAD_FLOW_START, _T("_ePAPER_LOAD_UNLOAD_FLOW_START"));
	return TRUE;
}
BOOL CPaperLoadUnloadFlow::Stop()
{
	m_bStopBit = TRUE;
	return TRUE;
}
UINT CPaperLoadUnloadFlow::ThreadFunction(LPVOID lpParam)
{
	CPaperLoadUnloadFlow* pFlow = NULL;

	pFlow = (CPaperLoadUnloadFlow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}
VOID CPaperLoadUnloadFlow::ThreadFunctionEntry(VOID)
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

			SetCurrentStep(_ePAPER_LOAD_UNLOAD_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}

		switch (GetCurrentTotalStep())
		{
		case _ePAPER_LOAD_UNLOAD_FLOW_IDLE:
		{
			break;
		}
		case _ePAPER_LOAD_UNLOAD_FLOW_START:
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

			SetStep(_ePAPER_LOAD_UNLOAD_FLOW_INTERLOCK, _T("_ePAPER_LOAD_UNLOAD_FLOW_INTERLOCK"));
			break;
		}
		case _ePAPER_LOAD_UNLOAD_FLOW_INTERLOCK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(_ePAPER_LOAD_UNLOAD_FLOW_ERROR, _T("_ePAPER_LOAD_UNLOAD_FLOW_ERROR"));
			}
			else
			{
				m_bGroupStepDone[m_nGroupStepIndex++] = TRUE; //KJT 20210221
				if (SharedInfo::MachineState.bAutoRunFlag == TRUE && SharedInfo::Active.ProcessEndFlow != eCOMBO_AUTO_RUN_FLOW_PPA)
					SetStep(_ePAPER_LOAD_UNLOAD_FLOW_UNLOADER_READY, _T("_ePAPER_LOAD_UNLOAD_FLOW_UNLOADER_READY"));
			}
			break;

#pragma region //Unloader Ready
		case _ePAPER_LOAD_UNLOAD_FLOW_UNLOADER_READY:
			Devs::m_Ready_UnloaderFlow.Start();

			SetStep(_ePAPER_LOAD_UNLOAD_FLOW_UNLOADER_READY_CHECK, _T("_ePAPER_LOAD_UNLOAD_FLOW_UNLOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _ePAPER_LOAD_UNLOAD_FLOW_UNLOADER_READY_CHECK:
			if (Devs::m_Ready_UnloaderFlow.IsFlowDone())
			{
				SetStep(_ePAPER_LOAD_UNLOAD_FLOW_GANTRY_ZX_READY, _T("_ePAPER_LOAD_UNLOAD_FLOW_GANTRY_ZX_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_ePAPER_LOAD_UNLOAD_FLOW_UNLOADER_READY_CHECK : Time Out"), ePAPER_UNLOAD_FLOW + 0);
				SetStep(_ePAPER_LOAD_UNLOAD_FLOW_ERROR, _T("_ePAPER_LOAD_UNLOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_ePAPER_LOAD_UNLOAD_FLOW_UNLOADER_READY_CHECK, _T("_ePAPER_LOAD_UNLOAD_FLOW_UNLOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Gantry Z,X Ready
		case _ePAPER_LOAD_UNLOAD_FLOW_GANTRY_ZX_READY:
			Devs::m_Ready_GantryZX_Flow.Start();

			SetStep(_ePAPER_LOAD_UNLOAD_FLOW_GANTRY_ZX_READY_CHECK, _T("_ePAPER_LOAD_UNLOAD_FLOW_GANTRY_ZX_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _ePAPER_LOAD_UNLOAD_FLOW_GANTRY_ZX_READY_CHECK:
			if (Devs::m_Ready_GantryZX_Flow.IsFlowDone())
			{
				SetStep(_ePAPER_LOAD_UNLOAD_FLOW_LOADER_READY, _T("_ePAPER_LOAD_UNLOAD_FLOW_LOADER_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_ePAPER_LOAD_UNLOAD_FLOW_GANTRY_ZX_READY_CHECK : Time Out"), ePAPER_UNLOAD_FLOW + 2);
				SetStep(_ePAPER_LOAD_UNLOAD_FLOW_ERROR, _T("_ePAPER_LOAD_UNLOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_ePAPER_LOAD_UNLOAD_FLOW_GANTRY_ZX_READY_CHECK, _T("_ePAPER_LOAD_UNLOAD_FLOW_GANTRY_ZX_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Loader Ready
		case _ePAPER_LOAD_UNLOAD_FLOW_LOADER_READY:
			Devs::m_Ready_LoaderFlow.Start();

			SetStep(_ePAPER_LOAD_UNLOAD_FLOW_LOADER_READY_CHECK, _T("_ePAPER_LOAD_UNLOAD_FLOW_LOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _ePAPER_LOAD_UNLOAD_FLOW_LOADER_READY_CHECK:
			if (Devs::m_Ready_LoaderFlow.IsFlowDone())
			{
				SetStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_ZX_READY, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_ZX_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_ePAPER_LOAD_UNLOAD_FLOW_LOADER_READY_CHECK : Time Out"), ePAPER_UNLOAD_FLOW + 1);
				SetStep(_ePAPER_LOAD_UNLOAD_FLOW_ERROR, _T("_ePAPER_LOAD_UNLOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_ePAPER_LOAD_UNLOAD_FLOW_LOADER_READY_CHECK, _T("_ePAPER_LOAD_UNLOAD_FLOW_LOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //PaperUnloader Ready
		case _ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_ZX_READY:
			Devs::m_Ready_PaperUnloaderZXFlow.Start();

			SetStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_ZX_READY_CHECK, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_ZX_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_ZX_READY_CHECK:
			if (Devs::m_Ready_PaperUnloaderZXFlow.IsFlowDone())
			{
				SetStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Y_PAPER_LOAD_IN_BOX_POS, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Y_PAPER_LOAD_IN_BOX_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_ZX_READY_CHECK : Time Out"), ePAPER_UNLOAD_FLOW + 1);
				SetStep(_ePAPER_LOAD_UNLOAD_FLOW_ERROR, _T("_ePAPER_LOAD_UNLOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_ZX_READY_CHECK, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_ZX_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //1. PickUp In Box
		case _ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Y_PAPER_LOAD_IN_BOX_POS:
			Devs::m_UnloaderMotion.PaperUnloaderY_All_LoadPaperPos();
			Sleep(20); //!!!

			SetStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Y_PAPER_LOAD_IN_BOX_POS_CHECK, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Y_PAPER_LOAD_IN_BOX_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Y_PAPER_LOAD_IN_BOX_POS_CHECK:
			if (Devs::m_UnloaderMotion.Is_PaperUnloaderY_All_LoadPaperPos())
			{
				SetStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_X_PAPER_LOAD_POS, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_X_PAPER_LOAD_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Y_PAPER_LOAD_IN_BOX_POS_CHECK : Time Out"), ePAPER_UNLOAD_FLOW + 5);
				SetStep(_ePAPER_LOAD_UNLOAD_FLOW_ERROR, _T("_ePAPER_LOAD_UNLOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Y_PAPER_LOAD_IN_BOX_POS_CHECK, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Y_PAPER_LOAD_IN_BOX_POS_CHECK"));
			}
			break;

		case _ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_X_PAPER_LOAD_POS:
			Devs::m_UnloaderMotion.PaperUnloaderX_All_PickUpPos();
			Sleep(20); //!!!

			SetStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_X_PAPER_LOAD_POS_CHECK, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_X_PAPER_LOAD_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_X_PAPER_LOAD_POS_CHECK:
			if (Devs::m_UnloaderMotion.Is_PaperUnloaderX_All_PickUpPos())
			{
				SetStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_PAPER_LOAD_DOWN_POS, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_PAPER_LOAD_DOWN_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_X_PAPER_LOAD_POS_CHECK : Time Out"), ePAPER_UNLOAD_FLOW + 6);
				SetStep(_ePAPER_LOAD_UNLOAD_FLOW_ERROR, _T("_ePAPER_LOAD_UNLOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_X_PAPER_LOAD_POS_CHECK, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_X_PAPER_LOAD_POS_CHECK"));
			}
			break;

		case _ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_PAPER_LOAD_DOWN_POS:
			dOffset = (CModelData::m_AtMaterialPara.Info.dPaperThickness * (eBOX_SHEET_MAX - SharedInfo::BoxStickExistInfo.nStickCount)) * (-1);

			m_dTargetPosZ = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZL_Paper_Load_Pos;
			m_dTargetPosZ += dOffset;			
			if (SharedInfo::CheckSafetyPos(AXIS_UNLOADER_ZL, m_dTargetPosZ, &Str, &nSafetyPosErrorBy) == FALSE)
			{
				if (nSafetyPosErrorBy == eTARGET_POS_ERROR_BY_SAFETY_MIN)
					SharedInfo::SetAxisAlarm(AXIS_UNLOADER_ZL, eTARGET_POS_ERROR_BY_SAFETY_MIN);
				else if (nSafetyPosErrorBy == eTARGET_POS_ERROR_BY_SAFETY_MAX)
					SharedInfo::SetAxisAlarm(AXIS_UNLOADER_ZL, eTARGET_POS_ERROR_BY_SAFETY_MAX);

				Total_Msg(Str);
				SharedInfo::SetAlarm(_T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_PAPER_LOAD_DOWN_POS : AXIS_UNLOADER_ZL Pos limit"), ePAPER_UNLOAD_FLOW + 6);
				SetStep(_ePAPER_LOAD_UNLOAD_FLOW_ERROR, _T("_ePAPER_LOAD_UNLOAD_FLOW_ERROR"));
				break;
			}

			Devs::m_UnloaderMotion.MoveAxis(AXIS_UNLOADER_ZL, m_dTargetPosZ);
			Sleep(20);

			Str.Format(_T("PaperUnloaderZ Move To Paper Load Pos. Offset:%.5f (Pos Z:%.5f)"), dOffset, m_dTargetPosZ);
			Total_Msg(Str);

			SetStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_PAPER_LOAD_DOWN_POS_CHECK, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_PAPER_LOAD_DOWN_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_PAPER_LOAD_DOWN_POS_CHECK:
			if (Devs::m_UnloaderMotion.IsMoveDone(AXIS_UNLOADER_ZL, m_dTargetPosZ))
			{
				SetStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_VAC_ON, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_VAC_ON"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_ePAPER_LOAD_UNLOAD_FLOW_LOADER_Z_DOWN_POS_CHECK : Time Out"), ePAPER_UNLOAD_FLOW + 8);
				SetStep(_ePAPER_LOAD_UNLOAD_FLOW_ERROR, _T("_ePAPER_LOAD_UNLOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_PAPER_LOAD_DOWN_POS_CHECK, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_PAPER_LOAD_DOWN_POS_CHECK"));
			}
			break;

		case _ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_VAC_ON:
			Devs::m_UnloaderMotion.PaperUnloader_Active_Vac_On();

			Sleep(500); //!!
			m_nStepDownCount = 0;
			SetStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_STEP_DOWN, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_STEP_DOWN"));
			break;

		case _ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_STEP_DOWN:
			m_dTargetPosZ = SharedInfo::GetCmdPos(AXIS_UNLOADER_ZL);
			m_dTargetPosZ -= CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_StepDownOffset;
			if (SharedInfo::CheckSafetyPos(AXIS_UNLOADER_ZL, m_dTargetPosZ, &Str, &nSafetyPosErrorBy) == FALSE)
			{
				if (nSafetyPosErrorBy == eTARGET_POS_ERROR_BY_SAFETY_MIN)
					SharedInfo::SetAxisAlarm(AXIS_UNLOADER_ZL, eTARGET_POS_ERROR_BY_SAFETY_MIN);
				else if (nSafetyPosErrorBy == eTARGET_POS_ERROR_BY_SAFETY_MAX)
					SharedInfo::SetAxisAlarm(AXIS_UNLOADER_ZL, eTARGET_POS_ERROR_BY_SAFETY_MAX);

				Total_Msg(Str);
				SharedInfo::SetAlarm(_T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_STEP_DOWN : AXIS_UNLOADER_ZL Pos Limit"), ePAPER_UNLOAD_FLOW + 9);
				SetStep(_ePAPER_LOAD_UNLOAD_FLOW_ERROR, _T("_ePAPER_LOAD_UNLOAD_FLOW_ERROR"));
				break;
			}

			Devs::m_UnloaderMotion.MoveAxis(AXIS_UNLOADER_ZL, m_dTargetPosZ);
			Sleep(20);

			Str.Format(_T("PaperUnloaderZ Step Down Offset:%.5f (Pos ZL:%.5f)"), CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_StepDownOffset, m_dTargetPosZ);
			Total_Msg(Str);

			SetStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_STEP_DOWN_CHECK, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_STEP_DOWN_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_STEP_DOWN_CHECK:
			if (Devs::m_UnloaderMotion.IsMoveDone(AXIS_UNLOADER_ZL, m_dTargetPosZ))
			{
				Sleep(100);

				if (Devs::m_UnloaderMotion.Is_PaperUnloader_Active_Vac_On())
				{
					m_nVibrationCount = 0; //KJT 20210317
					SetStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_STICK_LOAD_STEP_UP, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_STICK_LOAD_STEP_UP"));
					break;
				}
				else if (++m_nStepDownCount < m_nMaxStepDownCount)
				{
					SetStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_STEP_DOWN, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_STEP_DOWN"));
				}
				else
				{
					Str.Format(_T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_STEP_DOWN_CHECK : Count %d Over"), m_nMaxStepDownCount);
					SharedInfo::SetAlarm(Str, ePAPER_UNLOAD_FLOW + 11);
					SetStep(_ePAPER_LOAD_UNLOAD_FLOW_ERROR, _T("_ePAPER_LOAD_UNLOAD_FLOW_ERROR"));
				}
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_STEP_DOWN_CHECK : Time Out"), ePAPER_UNLOAD_FLOW + 11);
				SetStep(_ePAPER_LOAD_UNLOAD_FLOW_ERROR, _T("_ePAPER_LOAD_UNLOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_STEP_DOWN_CHECK, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_STEP_DOWN_CHECK"));
			}
			break;

		case _ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_STICK_LOAD_STEP_UP:
			m_dTargetPosZ = SharedInfo::GetCmdPos(AXIS_UNLOADER_ZL);
			m_dTargetPosZ += CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_StepUpOffset;

			Devs::m_UnloaderMotion.MoveAxis(AXIS_UNLOADER_ZL, m_dTargetPosZ);
			Sleep(20);
			
			Str.Format(_T("PaperUnloaderZ Step Up Offset:%.5f (Pos Z:%.5f)"), CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_StepUpOffset, m_dTargetPosZ);
			Total_Msg(Str);

			SetStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_STICK_LOAD_STEP_UP_CHECK, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_STICK_LOAD_STEP_UP_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_STICK_LOAD_STEP_UP_CHECK: //KJT 20210316
			if (Devs::m_UnloaderMotion.IsMoveDone(AXIS_UNLOADER_ZL, m_dTargetPosZ))
			{
				m_nVibrationCount = 0;
				SetStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_UP_POS, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_UP_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_STICK_LOAD_STEP_UP_CHECK : Time Out"), ePAPER_UNLOAD_FLOW + 12);
				SetStep(_ePAPER_LOAD_UNLOAD_FLOW_ERROR, _T("_ePAPER_LOAD_UNLOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_STICK_LOAD_STEP_UP_CHECK, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_STICK_LOAD_STEP_UP_CHECK"));
			}
			break;

		case _ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_UP_POS:
			m_dTargetPosZ = SharedInfo::GetCmdPos(AXIS_UNLOADER_ZL);
			m_dTargetPosZ += CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_VibrationOffset;

			//KJT 20210323
			dVel = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_VibrationVel;
			dAccel = dVel * 5.0;
			dDecel = dVel * 5.0;
			Devs::m_JogMotion.AbsMove(AXIS_UNLOADER_ZL, m_dTargetPosZ, dVel, dAccel, dDecel);
			Sleep(20);
			
			Str.Format(_T("PaperUnloaderZ Vibration Up Offset:%.5f (Pos Z:%.5f)"), CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_StepUpOffset, m_dTargetPosZ);
			Total_Msg(Str);

			SetStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_UP_POS_CHECK, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_UP_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_UP_POS_CHECK:
			if (Devs::m_UnloaderMotion.IsMoveDone(AXIS_UNLOADER_ZL, m_dTargetPosZ))
			{
				SetStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_DOWN_POS, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_DOWN_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_UP_POS_CHECK : Time Out"), ePAPER_UNLOAD_FLOW + 13);
				SetStep(_ePAPER_LOAD_UNLOAD_FLOW_ERROR, _T("_ePAPER_LOAD_UNLOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_UP_POS_CHECK, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_UP_POS_CHECK"));
			}
			break;

		case _ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_DOWN_POS: //KJT 20210317
			m_dTargetPosZ = SharedInfo::GetCmdPos(AXIS_UNLOADER_ZL);
			m_dTargetPosZ -= CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_VibrationOffset;
			if (SharedInfo::CheckSafetyPos(AXIS_UNLOADER_ZL, m_dTargetPosZ, &Str, &nSafetyPosErrorBy) == FALSE)
			{
				if (nSafetyPosErrorBy == eTARGET_POS_ERROR_BY_SAFETY_MIN)
					SharedInfo::SetAxisAlarm(AXIS_UNLOADER_ZL, eTARGET_POS_ERROR_BY_SAFETY_MIN);
				else if (nSafetyPosErrorBy == eTARGET_POS_ERROR_BY_SAFETY_MAX)
					SharedInfo::SetAxisAlarm(AXIS_UNLOADER_ZL, eTARGET_POS_ERROR_BY_SAFETY_MAX);

				Total_Msg(Str);
				SharedInfo::SetAlarm(_T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_DOWN_POS : AXIS_UNLOADER_ZL Pos Limit"), ePAPER_UNLOAD_FLOW + 14);
				SetStep(_ePAPER_LOAD_UNLOAD_FLOW_ERROR, _T("_ePAPER_LOAD_UNLOAD_FLOW_ERROR"));
				break;
			}

			//KJT 20210323
			dVel = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_VibrationVel;
			dAccel = dVel * 5.0;
			dDecel = dVel * 5.0;
			Devs::m_JogMotion.AbsMove(AXIS_UNLOADER_ZL, m_dTargetPosZ, dVel, dAccel, dDecel);
			Sleep(20);

			Str.Format(_T("PaperUnloaderZ Vibration Down Offset:%.5f (Pos ZL:%.5f)"), CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_VibrationOffset, m_dTargetPosZ);
			Total_Msg(Str);

			Sleep(500); //!!
			SetStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_DOWN_POS_CHECK, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_DOWN_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_DOWN_POS_CHECK:
			if (Devs::m_UnloaderMotion.IsMoveDone(AXIS_UNLOADER_ZL, m_dTargetPosZ))
			{				
				if (++m_nVibrationCount >= m_nMaxVibrationCount)
					SetStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_WAIT_POS, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_WAIT_POS"));
				else
					SetStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_UP_POS, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_UP_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_ePAPER_LOAD_UNLOAD_FLOW_LOADER_Z_VIBRATION_DOWN_POS_CHECK : Time Out"), ePAPER_UNLOAD_FLOW + 15);
				SetStep(_ePAPER_LOAD_UNLOAD_FLOW_ERROR, _T("_ePAPER_LOAD_UNLOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_DOWN_POS_CHECK, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_DOWN_POS_CHECK"));
			}
			break;

		case _ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_WAIT_POS:
			Devs::m_UnloaderMotion.PaperUnloaderZ_All_WaitPos();

			SetStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_WAIT_POS_CHECK, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_WAIT_POS_CHECK:
			if (Devs::m_UnloaderMotion.Is_PaperUnloaderZ_All_WaitPos())
			{
				if (Devs::m_UnloaderMotion.Is_PaperUnloader_Active_Vac_On() == FALSE)
				{
					Total_Msg(_T("Check PaperUnloader Active Vac On !!!"));
					SharedInfo::SetAlarm(_T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_WAIT_POS_CHECK : Vac On"), ePAPER_UNLOAD_FLOW + 16);
					SetStep(_ePAPER_LOAD_UNLOAD_FLOW_ERROR, _T("_ePAPER_LOAD_UNLOAD_FLOW_ERROR"));
				}
				else
				{
					SetStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_X_TENSION_POS, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_X_TENSION_POS"));
				}
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_ePAPER_LOAD_UNLOAD_FLOW_LOADER_Z_WAIT_POS_CHECK : Time Out"), ePAPER_UNLOAD_FLOW + 17);
				SetStep(_ePAPER_LOAD_UNLOAD_FLOW_ERROR, _T("_ePAPER_LOAD_UNLOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_WAIT_POS_CHECK, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_WAIT_POS_CHECK"));
			}
			break;

		case _ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_X_TENSION_POS:
			m_dTargetPosX = SharedInfo::GetCmdPos(AXIS_UNLOADER_XL);
			m_dTargetPosX += CManualData::m_ManualDataUnloader.Info.m_dUnloaderX_Tension_Offset;
			if (SharedInfo::CheckSafetyPos(AXIS_UNLOADER_XL, m_dTargetPosX, &Str, &nSafetyPosErrorBy) == FALSE)
			{
				if (nSafetyPosErrorBy == eTARGET_POS_ERROR_BY_SAFETY_MIN)
					SharedInfo::SetAxisAlarm(AXIS_LOADER_X, eTARGET_POS_ERROR_BY_SAFETY_MIN);
				else if (nSafetyPosErrorBy == eTARGET_POS_ERROR_BY_SAFETY_MAX)
					SharedInfo::SetAxisAlarm(AXIS_LOADER_X, eTARGET_POS_ERROR_BY_SAFETY_MAX);

				Total_Msg(Str);
				SharedInfo::SetAlarm(_T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_X_TENSION_POS : AXIS_UNLOADER_XL Pos Limit"), ePAPER_UNLOAD_FLOW + 28);
				SetStep(_ePAPER_LOAD_UNLOAD_FLOW_ERROR, _T("_ePAPER_LOAD_UNLOAD_FLOW_ERROR"));
				break;
			}

			Devs::m_UnloaderMotion.MoveAxis(AXIS_UNLOADER_XL, m_dTargetPosX);

			Str.Format(_T("PaperUnloaderX Tension Pos Move. Offset:%.5f (Pos X:%.5f)"), CManualData::m_ManualDataUnloader.Info.m_dUnloaderX_Tension_Offset, m_dTargetPosX);
			Total_Msg(Str);

			SetStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_X_TENSION_POS_CHECK, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_X_TENSION_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_X_TENSION_POS_CHECK:
			if (Devs::m_UnloaderMotion.IsMoveDone(AXIS_UNLOADER_XL, m_dTargetPosX))
			{
				SetStep(_ePAPER_LOAD_UNLOAD_FLOW_CST_RECV_READY_MOVE, _T("_ePAPER_LOAD_UNLOAD_FLOW_CST_RECV_READY_MOVE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_X_TENSION_POS_CHECK : Time Out"), ePAPER_UNLOAD_FLOW + 29);
				SetStep(_ePAPER_LOAD_UNLOAD_FLOW_ERROR, _T("_ePAPER_LOAD_UNLOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_X_TENSION_POS_CHECK, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_X_TENSION_POS_CHECK"));
			}
			break;
#pragma endregion //1. PickUp In Box

#pragma region //2. Paper Unload		
		case _ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Y_PAPER_UNLOAD_POS:
			Devs::m_UnloaderMotion.PaperUnloaderY_All_UnloadPaperPos();
			Sleep(20); //!!!

			SetStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Y_PAPER_UNLOAD_POS_CHECK, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Y_PAPER_UNLOAD_POS_CHECK"));
			SetTimeOut(TIME_OUT_STATE); //TIME_OUT_MOTION
			break;

		case _ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Y_PAPER_UNLOAD_POS_CHECK:
			if (Devs::m_UnloaderMotion.Is_PaperUnloaderY_All_UnloadPaperPos())
			{
				SetStep(_ePAPER_LOAD_UNLOAD_FLOW_CST_RECV_READY_DONE_CHECK, _T("_ePAPER_LOAD_UNLOAD_FLOW_CST_RECV_READY_DONE_CHECK"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Y_PAPER_UNLOAD_POS_CHECK : Time Out"), ePAPER_UNLOAD_FLOW + 18);
				SetStep(_ePAPER_LOAD_UNLOAD_FLOW_ERROR, _T("_ePAPER_LOAD_UNLOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Y_PAPER_UNLOAD_POS_CHECK, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Y_PAPER_UNLOAD_POS_CHECK"));
			}
			break;

		case _ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_PAPER_UNLOAD_DOWN_POS:
			Devs::m_UnloaderMotion.PaperUnloaderZ_All_UnloadPaperPos();

			SetStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_PAPER_UNLOAD_DOWN_POS_CHECK, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_PAPER_UNLOAD_DOWN_POS_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_PAPER_UNLOAD_DOWN_POS_CHECK:
			if (Devs::m_UnloaderMotion.Is_PaperUnloaderZ_All_UnloadPaperPos())
			{
				SetStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_VAC_OFF, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_VAC_OFF"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_PAPER_UNLOAD_DOWN_POS_CHECK : Time Out"), ePAPER_UNLOAD_FLOW + 19);
				SetStep(_ePAPER_LOAD_UNLOAD_FLOW_ERROR, _T("_ePAPER_LOAD_UNLOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_PAPER_UNLOAD_DOWN_POS_CHECK, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_PAPER_UNLOAD_DOWN_POS_CHECK"));
			}
			break;

		case _ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_VAC_OFF:
			Devs::m_UnloaderMotion.PaperUnloader_Active_Vac_Off();

			Sleep(500); //!!
			SetStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_VAC_OFF_CHECK, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_VAC_OFF_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_VAC_OFF_CHECK:
			if (Devs::m_UnloaderMotion.Is_PaperUnloader_Active_Vac_Off())
			{
				SetStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_FINISH_WAIT_POS, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_FINISH_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_VAC_OFF_CHECK : Time Out"), ePAPER_UNLOAD_FLOW + 20);
				SetStep(_ePAPER_LOAD_UNLOAD_FLOW_ERROR, _T("_ePAPER_LOAD_UNLOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_VAC_OFF_CHECK, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_VAC_OFF_CHECK"));
			}
			break;

		case _ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_FINISH_WAIT_POS:
			Devs::m_UnloaderMotion.PaperUnloaderZ_All_WaitPos();

			SetStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_FINISH_WAIT_POS_CHECK, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_FINISH_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;	

		case _ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_FINISH_WAIT_POS_CHECK:
			if (Devs::m_UnloaderMotion.Is_PaperUnloaderZ_All_WaitPos())
			{
				SetStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Y_FINISH_WAIT_POS, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Y_FINISH_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_FINISH_WAIT_POS_CHECK : Time Out"), ePAPER_UNLOAD_FLOW + 22);
				SetStep(_ePAPER_LOAD_UNLOAD_FLOW_ERROR, _T("_ePAPER_LOAD_UNLOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_FINISH_WAIT_POS_CHECK, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_FINISH_WAIT_POS_CHECK"));
			}
			break;

		case _ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Y_FINISH_WAIT_POS:
			Devs::m_UnloaderMotion.PaperUnloaderY_All_WaitPos();

			SetStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Y_FINISH_WAIT_POS_CHECK, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Y_FINISH_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Y_FINISH_WAIT_POS_CHECK:
			if (Devs::m_UnloaderMotion.Is_PaperUnloaderY_All_WaitPos())
			{
				SetStep(_ePAPER_LOAD_UNLOAD_FLOW_CST_RECV_DONE_MOVE, _T("_ePAPER_LOAD_UNLOAD_FLOW_CST_RECV_DONE_MOVE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Y_FINISH_WAIT_POS_CHECK : Time Out"), ePAPER_UNLOAD_FLOW + 22);
				SetStep(_ePAPER_LOAD_UNLOAD_FLOW_ERROR, _T("_ePAPER_LOAD_UNLOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Y_FINISH_WAIT_POS_CHECK, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Y_FINISH_WAIT_POS_CHECK"));
			}
			break;
#pragma endregion //2. Paper Unload

#pragma region //Cst Move
		case _ePAPER_LOAD_UNLOAD_FLOW_CST_RECV_READY_MOVE:
			Devs::m_CstRecvReadyFlow.Start(m_eTargetFloor);
			Sleep(20);

			SetStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Y_PAPER_UNLOAD_POS, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Y_PAPER_UNLOAD_POS"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _ePAPER_LOAD_UNLOAD_FLOW_CST_RECV_READY_DONE_CHECK:
			if (Devs::m_CstRecvReadyFlow.IsFlowDone())
			{
				SetStep(_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_PAPER_UNLOAD_DOWN_POS, _T("_ePAPER_LOAD_UNLOAD_FLOW_PAPER_UNLOADER_Z_PAPER_UNLOAD_DOWN_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_ePAPER_LOAD_UNLOAD_FLOW_CST_RECV_READY_DONE_CHECK : Time Out"), ePAPER_UNLOAD_FLOW + 29);
				SetStep(_ePAPER_LOAD_UNLOAD_FLOW_ERROR, _T("_ePAPER_LOAD_UNLOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_ePAPER_LOAD_UNLOAD_FLOW_CST_RECV_READY_DONE_CHECK, _T("_ePAPER_LOAD_UNLOAD_FLOW_CST_RECV_READY_DONE_CHECK"));
			}
			break;

		case _ePAPER_LOAD_UNLOAD_FLOW_CST_RECV_DONE_MOVE:
			Devs::m_CstRecvDoneFlow.Start();
			Sleep(20);

			SetStep(_ePAPER_LOAD_UNLOAD_FLOW_CST_RECV_DONE_DONE_CHECK, _T("_ePAPER_LOAD_UNLOAD_FLOW_CST_RECV_DONE_DONE_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _ePAPER_LOAD_UNLOAD_FLOW_CST_RECV_DONE_DONE_CHECK:
			if (Devs::m_CstRecvDoneFlow.IsFlowDone())
			{
				SetStep(_ePAPER_LOAD_UNLOAD_FLOW_DONE, _T("_ePAPER_LOAD_UNLOAD_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_ePAPER_LOAD_UNLOAD_FLOW_CST_RECV_DONE_DONE_CHECK : Time Out"), eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW + 29);
				SetStep(_ePAPER_LOAD_UNLOAD_FLOW_ERROR, _T("_ePAPER_LOAD_UNLOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_ePAPER_LOAD_UNLOAD_FLOW_CST_RECV_DONE_DONE_CHECK, _T("_ePAPER_LOAD_UNLOAD_FLOW_CST_RECV_DONE_DONE_CHECK"));
			}
			break;
#pragma endregion

		case _ePAPER_LOAD_UNLOAD_FLOW_DONE:
		{
			SharedInfo::nPrevFlowID = ePAPER_UNLOAD_FLOW; //KJT 20210326

			m_bFlowDone = TRUE;

			SharedInfo::CalTactTime(_T("PAPER_UNLOAD_FLOW"), m_timeStart); //KJT 20210329

			SetStep(_ePAPER_LOAD_UNLOAD_FLOW_IDLE, _T("_ePAPER_LOAD_UNLOAD_FLOW_IDLE"));
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

BOOL CPaperLoadUnloadFlow::FlowInterlock()
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