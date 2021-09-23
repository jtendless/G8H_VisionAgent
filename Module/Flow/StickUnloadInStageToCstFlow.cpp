#include "stdafx.h"
#include "StickUnloadInStageToCstFlow.h"
#include "Log/Logger.h"
#include "Vision/Devs.h"
#include "Data/ModelData.h"
#include "CamAreaModul.h"
#include "Data/SystemData.h"
#include "Data/ManualData.h"
#include "Data/MachineData.h"

CStickUnloadInStageToCstFlow::CStickUnloadInStageToCstFlow()
{
}


CStickUnloadInStageToCstFlow::~CStickUnloadInStageToCstFlow()
{
}

BOOL CStickUnloadInStageToCstFlow::InitProcess()
{

#pragma region //Step Group
	int nGroupIndex = 0;

	m_sGroupInfo[nGroupIndex].m_bProcessingFlag = FALSE;
	m_sGroupInfo[nGroupIndex].nStartStep = _eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_START;
	m_sGroupInfo[nGroupIndex].nEndStep = _eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_INTERLOCK;
	m_sGroupInfo[nGroupIndex].strGroupName.Format(_T("%d. Start - Ready"), nGroupIndex + 1);
	nGroupIndex++;

	m_nMaxGroupCount = nGroupIndex;
#pragma endregion

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
BOOL CStickUnloadInStageToCstFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_IDLE, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_IDLE"));

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
BOOL CStickUnloadInStageToCstFlow::Start()
{
	m_nStepDownCount = 0;
	m_nVibrationCount = 0;
	m_nMaxStepDownCount = CManualData::m_ManualDataUnloader.Info.m_nUnloaderZ_StepDownCount;
	m_nMaxVibrationCount = CManualData::m_ManualDataUnloader.Info.m_nUnloaderZ_VibrationCount;


	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_START, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_START"));
	return TRUE;
}
BOOL CStickUnloadInStageToCstFlow::Stop()
{
	m_bStopBit = TRUE;
	SetStop(); //!!
	return TRUE;
}
UINT CStickUnloadInStageToCstFlow::ThreadFunction(LPVOID lpParam)
{
	CStickUnloadInStageToCstFlow* pFlow = NULL;

	pFlow = (CStickUnloadInStageToCstFlow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}
VOID CStickUnloadInStageToCstFlow::ThreadFunctionEntry(VOID)
{
	DWORD	dwResult = 0;
	double	dStrt_Time = GetTickCount();
	double	dEnd_Time = GetTickCount();
	double	dWait_Time = GetTickCount();
	int		nWork_Mask_Mode = -1;
	int		nWork_Mask_Index = -1;
	BOOL	bComplete_Step = FALSE;
	BOOL	bRtn = FALSE;

	double dOffset = 0.0;

	double dVel = 20.0;
	double dAccel = 20.0;
	double dDecel = 20.0;

	int nSheetCount = 0;

	int nSafetyPosErrorBy;
	CString Str = _T("");
	
	while (m_FlowFinish)
	{
		WaitForSingleObject(hHandle, INFINITE);
		ResetEvent(hHandle);

		if (SharedInfo::bMachineStopFlag == TRUE)// && m_bStopBit == FALSE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}
	

		switch (GetCurrentTotalStep())
		{
		case _eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_IDLE:
		{
			break;
		}
		case _eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_START:
		{
			m_timeStart = CTime::GetCurrentTime(); //KJT 20210329
			SharedInfo::m_timeUnitTact = m_timeStart;

			SharedInfo::nCurFlowID = eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW;

			m_nStepDownCount = 0;
			m_nVibrationCount = 0;
			m_nMaxStepDownCount = CManualData::m_ManualDataUnloader.Info.m_nUnloaderZ_StepDownCount;
			m_nMaxVibrationCount = CManualData::m_ManualDataUnloader.Info.m_nUnloaderZ_VibrationCount;


			//KJT 20210402
			if (CModelData::m_InspectionPara.Info.bOnlyUnloadingMode) //KJT 20210823 Add
			{
				SharedInfo::Active.eLastStickCstTargetFloor = eCASSETTE_FLOOR_1;
				SharedInfo::ActiveInfoSave();
			}
			else
			{
				bRtn = SharedInfo::FindFloorSlotUnloadToCst(&m_eTargetFloor/*, &m_eTargetSlot*/);
				if (bRtn == FALSE)
				{
					m_eTargetFloor = eCASSETTE_FLOOR_NONE;
					//m_eTargetSlot = eCASSETTE_SLOT_NONE;
					//Total_Msg(_T("PPA After Cst Target Floor, Slot Unknown !!"));
					Total_Msg(_T("PPA After Cst Target Floor Unknown !!"));
					SharedInfo::SetAlarm(_T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW : Valid CST Floor Not Exist Error !!!"), eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW + 0);
					SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR"));
					break;
				}
				else
				{
					SharedInfo::Active.eLastStickCstTargetFloor = m_eTargetFloor; //Junying TPCD
					SharedInfo::ActiveInfoSave();
				}
			}

			SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_INTERLOCK, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_INTERLOCK"));
			break;
		}

		case _eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_INTERLOCK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR"));
			}
			else
			{
				SharedInfo::SetAcitveStickPos(eACTIVE_STICK_POS_INSPECTION_STAGE); //KJT 20210328

				if (CModelData::m_InspectionPara.Info.bOnlyUnloadingMode) //KJT 20210601
				{
					SharedInfo::Active.nFinalGrade = eGRADE_S; //Default
					SharedInfo::Active.nFinalJudge = eMaterialJudge_Good; //KJT 20210521  //CIM__
					SharedInfo::ActiveInfoSave();
					SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_READY, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_READY"));
				}
				else
				{
					if (SharedInfo::CheckFinalGrade())
						SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_READY, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_READY"));
					else
					{
						SharedInfo::SetAlarm(_T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_INTERLOCK Final Grade None Error !!!"), eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW + 0);
						SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR"));
					}
				}
			}
			break;

#pragma region //Unloader Ready
		case _eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_READY:
			Devs::m_Ready_UnloaderFlow.Start();

			SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_READY_CHECK, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_FLOW);
			break;

		case _eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_READY_CHECK:
			if (Devs::m_Ready_UnloaderFlow.IsFlowDone())
			{
				SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_GANTRY_ZX_READY, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_GANTRY_ZX_READY"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_READY_CHECK, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Gantry ZX Ready
		case _eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_GANTRY_ZX_READY:
			Devs::m_Ready_GantryZX_Flow.Start();

			SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_GANTRY_ZX_READY_CHECK, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_GANTRY_ZX_READY_CHECK"));
			SetTimeOut(TIME_OUT_FLOW);
			break;

		case _eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_GANTRY_ZX_READY_CHECK:
			if (Devs::m_Ready_GantryZX_Flow.IsFlowDone())
			{
				SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_LOADER_ZXY_READY, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_LOADER_ZXY_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_GANTRY_ZX_READY_CHECK : Time Out"), eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW + 1);
				SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_GANTRY_ZX_READY_CHECK, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_GANTRY_ZX_READY_CHECK"));
			}
			break;
#pragma endregion


#pragma region //Loader ZXY Ready
		case _eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_LOADER_ZXY_READY:
			Devs::m_Ready_LoaderFlow.Start();

			SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_LOADER_ZXY_READY_CHECK, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_LOADER_ZXY_READY_CHECK"));
			SetTimeOut(TIME_OUT_FLOW);
			break;

		case _eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_LOADER_ZXY_READY_CHECK:
			if (Devs::m_Ready_LoaderFlow.IsFlowDone())
			{
				SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Y_STICK_LOAD_IN_STAGE_POS, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Y_STICK_LOAD_IN_STAGE_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_LOADER_ZXY_READY_CHECK : Time Out"), eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW + 0);
				SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_LOADER_ZXY_READY_CHECK, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_LOADER_ZXY_READY_CHECK"));
			}
			break;
#pragma endregion
#if 0 //KJT 20210810 Junying Hide
#pragma region //PaperUnloaderZX Ready
		case _eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_PAPER_UNLOADER_ZX_READY:
			Devs::m_Ready_PaperUnloaderZXFlow.Start();

			SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_PAPER_UNLOADER_ZX_READY_CHECK, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_PAPER_UNLOADER_ZX_READY_CHECK"));
			SetTimeOut(TIME_OUT_FLOW);
			break;

		case _eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_PAPER_UNLOADER_ZX_READY_CHECK:
			if (Devs::m_Ready_LoaderFlow.IsFlowDone())
			{
				SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Y_STICK_LOAD_IN_STAGE_POS, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Y_STICK_LOAD_IN_STAGE_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_PAPER_UNLOADER_ZX_READY_CHECK : Time Out"), eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW + 0);
				SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_PAPER_UNLOADER_ZX_READY_CHECK, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_PAPER_UNLOADER_ZX_READY_CHECK"));
			}
			break;
#pragma endregion
#endif
		case _eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Y_STICK_LOAD_IN_STAGE_POS:
			Devs::m_UnloaderMotion.GantryY_StickLoadInStagePos();

			SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Y_STICK_LOAD_IN_STAGE_POS_CHECK, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Y_STICK_LOAD_IN_STAGE_POS_CHECK"));
			SetTimeOut(TIME_OUT_FLOW);
			break;

		case _eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Y_STICK_LOAD_IN_STAGE_POS_CHECK:
			if (Devs::m_UnloaderMotion.Is_GantryY_StickLoadInStagePos())
			{
				SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_X_STICK_LOAD_POS, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_X_STICK_LOAD_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Y_STICK_LOAD_IN_STAGE_POS_CHECK : Time Out"), eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW + 1);
				SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Y_STICK_LOAD_IN_STAGE_POS_CHECK, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Y_STICK_LOAD_IN_STAGE_POS_CHECK"));
			}
			break;

		case _eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_X_STICK_LOAD_POS:
			Devs::m_UnloaderMotion.UnloaderX_PickUpPos();

			SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_X_STICK_LOAD_POS_CHECK, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_X_STICK_LOAD_POS_CHECK"));
			SetTimeOut(TIME_OUT_FLOW);
			break;

		case _eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_X_STICK_LOAD_POS_CHECK:
			if (Devs::m_UnloaderMotion.Is_UnloaderX_PickUpPos())
			{
				SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Z_STICK_LOAD_POS, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Z_STICK_LOAD_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_X_STICK_LOAD_POS_CHECK : Time Out"), eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW + 1);
				SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_X_STICK_LOAD_POS_CHECK, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_X_STICK_LOAD_POS_CHECK"));
			}
			break;

		case _eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Z_STICK_LOAD_POS:
			Devs::m_UnloaderMotion.UnloaderZ_LoadInStagePos();
			
			SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Z_STICK_LOAD_POS_CHECK, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Z_STICK_LOAD_POS_CHECK"));
			SetTimeOut(TIME_OUT_FLOW);
			break;

		case _eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Z_STICK_LOAD_POS_CHECK:
			if (Devs::m_UnloaderMotion.Is_UnloaderZ_LoadInStagePos())
			{
				SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_VAC_ON, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_VAC_ON"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Z_STICK_LOAD_POS_CHECK : Time Out"), eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW + 1);
				SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Z_STICK_LOAD_POS_CHECK, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Z_STICK_LOAD_POS_CHECK"));
			}
			break;

		case _eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_VAC_ON:
			Devs::m_UnloaderMotion.Stick_Active_Vac_On();

			SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_VAC_ON_CHECK, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_VAC_ON_CHECK"));
			SetTimeOut(TIME_OUT_FLOW);
			break;

		case _eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_VAC_ON_CHECK:
			if (Devs::m_UnloaderMotion.Is_Stick_Active_Vac_On())
			{
				SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_INSP_STAGE_VAC_OFF, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_INSP_STAGE_VAC_OFF"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_VAC_ON_CHECK : Time Out"), eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW + 11);
				SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_VAC_ON_CHECK, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_VAC_ON_CHECK"));
			}
			break;

		case _eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_INSP_STAGE_VAC_OFF:
			Devs::m_InspectionStageMotion.Inspect_Stage_Vac_Off();
			Sleep(100); //!!

			SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_INSP_STAGE_VAC_OFF_CHECK, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_INSP_STAGE_VAC_OFF_CHECK"));
			SetTimeOut(TIME_OUT_FLOW);
			break;

		case _eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_INSP_STAGE_VAC_OFF_CHECK:
			if (Devs::m_InspectionStageMotion.Is_Inspect_Stage_Vac_Off())
			{
				SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Z_WAIT_POS_2ND, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Z_WAIT_POS_2ND"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_INSP_STAGE_VAC_OFF_CHECK : Time Out"), eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW + 12);
				SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_INSP_STAGE_VAC_OFF_CHECK, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_INSP_STAGE_VAC_OFF_CHECK"));
			}
			break;

		case _eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Z_WAIT_POS_2ND:
			Devs::m_UnloaderMotion.UnloaderZ_WaitPos();

			SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Z_WAIT_POS_2ND_CHECK, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Z_WAIT_POS_2ND_CHECK"));
			SetTimeOut(TIME_OUT_FLOW);
			break;

		case _eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Z_WAIT_POS_2ND_CHECK:
			if (Devs::m_UnloaderMotion.Is_UnloaderZ_WaitPos())
			{
				if (Devs::m_UnloaderMotion.Is_Stick_Active_Vac_On() == FALSE)
				{
					Total_Msg(_T("Check Unlaoder Stick Active Vac On !!!"));
					SharedInfo::SetAlarm(_T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Z_WAIT_POS_2ND_CHECK : Vac On"), eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW + 13);
					SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR"));
				}
				else
				{
					SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_X_TENSION_POS, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_X_TENSION_POS"));
				}
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Z_WAIT_POS_2ND_CHECK : Time Out"), eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW + 14);
				SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Z_WAIT_POS_2ND_CHECK, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Z_WAIT_POS_2ND_CHECK"));
			}
			break;

		case _eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_X_TENSION_POS:
			m_dTargetPosUldX = SharedInfo::GetCmdPos(AXIS_UNLOADER_X);
			m_dTargetPosUldX += CManualData::m_ManualDataUnloader.Info.m_dUnloaderX_Tension_Offset;
			if (SharedInfo::CheckSafetyPos(AXIS_UNLOADER_X, m_dTargetPosUldX, &Str, &nSafetyPosErrorBy) == FALSE)
			{
				Total_Msg(Str);
				AfxMessageBox(Str);
				SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR"));
				break;
			}

			Devs::m_LoaderMotion.MoveAxis(AXIS_UNLOADER_X, m_dTargetPosUldX);
			Str.Format(_T("Unloader X Tension Offset %.5f (To Pos : %.5f)"), CManualData::m_ManualDataUnloader.Info.m_dUnloaderX_Tension_Offset, m_dTargetPosUldX);
			Total_Msg(Str);

			SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_X_TENSION_POS_CHECK, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_X_TENSION_POS_CHECK"));
			SetTimeOut(TIME_OUT_FLOW);
			break;

		case _eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_X_TENSION_POS_CHECK:
			if (Devs::m_LoaderMotion.IsMoveDone(AXIS_UNLOADER_X, m_dTargetPosUldX))
			{
				SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_CST_RECV_READY_MOVE, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_CST_RECV_READY_MOVE"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_X_TENSION_POS_CHECK, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_X_TENSION_POS_CHECK"));
			}
			break;

#pragma region //4. Stick Unload To Cst
		case _eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Y_UNLOAD_POS:
			Devs::m_UnloaderMotion.GantryY_StickUnloadToCstPos(0); //Junying TPCD Slot1 Fixed !!

			SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Y_UNLOAD_POS_CHECK, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Y_UNLOAD_POS_CHECK"));
			SetTimeOut(TIME_OUT_FLOW);
			break;

		case _eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Y_UNLOAD_POS_CHECK:
			if (Devs::m_UnloaderMotion.Is_GantryY_StickUnloadToCstPos(0)) //Junying TPCD Slot1 Fixed !!
			{
				SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_CST_RECV_READY_DONE_CHECK, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_CST_RECV_READY_DONE_CHECK"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Y_UNLOAD_POS_CHECK : Time Out"), eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW + 27);
				SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Y_UNLOAD_POS_CHECK, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Y_UNLOAD_POS_CHECK"));
			}
			break;		

		case _eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Z_UNLOAD_POS:
			Devs::m_UnloaderMotion.UnloaderZ_UnloadToCstPos();

			SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Z_UNLOAD_POS_CHECK, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Z_UNLOAD_POS_CHECK"));
			SetTimeOut(TIME_OUT_FLOW);
			break;

		case _eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Z_UNLOAD_POS_CHECK:
			if (Devs::m_UnloaderMotion.Is_UnloaderZ_UnloadToCstPos())
			{
				SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_VAC_OFF_2ND, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_VAC_OFF_2ND"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Z_UNLOAD_POS_CHECK : Time Out"), eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW + 28);
				SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Z_UNLOAD_POS_CHECK, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Z_UNLOAD_POS_CHECK"));
			}
			break;

		case _eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_VAC_OFF_2ND:
			Devs::m_UnloaderMotion.Stick_Active_Vac_Off();
			Sleep(10);

			SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_VAC_OFF_2ND_CHECK, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_VAC_OFF_2ND_CHECK"));
			SetTimeOut(TIME_OUT_FLOW);
			break;

		case _eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_VAC_OFF_2ND_CHECK:
			if (Devs::m_UnloaderMotion.Is_Stick_Active_Vac_Off())
			{
				nSheetCount = SharedInfo::CstStickExistInfo.nStickCount[m_eTargetFloor]/*[m_eTargetSlot]*/;
				memcpy(SharedInfo::CstStickExistInfo.tchStickId[m_eTargetFloor]/*[m_eTargetSlot]*/[(eCST_BOX_SHEET_MAX - 1) - nSheetCount], SharedInfo::Active.tchStickId, sizeof(SharedInfo::Active.tchStickId));
				SharedInfo::CstStickExistInfo.nJudge[m_eTargetFloor]/*[m_eTargetSlot]*/[(eCST_BOX_SHEET_MAX - 1) - nSheetCount] = SharedInfo::Active.nFinalJudge;
				SharedInfo::SetAcitveStickPos(eACTIVE_STICK_POS_CST); //KJT 20210328
				SharedInfo::SetCstStickExistInfo(m_eTargetFloor,/* m_eTargetSlot,*/ (enum_CstBoxSheet)((eCST_BOX_SHEET_MAX - 1) - nSheetCount), TRUE);

				SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Z_WAIT_POS_FINISH, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Z_WAIT_POS_FINISH"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_VAC_OFF_2ND_CHECK : Time Out"), eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW + 29);
				SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_VAC_OFF_2ND_CHECK, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_VAC_OFF_2ND_CHECK"));
			}
			break;

		case _eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Z_WAIT_POS_FINISH:
			Devs::m_UnloaderMotion.UnloaderZ_WaitPos();

			SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Z_WAIT_POS_FINISH_CHECK, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Z_WAIT_POS_FINISH_CHECK"));
			SetTimeOut(TIME_OUT_FLOW);
			break;

		case _eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Z_WAIT_POS_FINISH_CHECK:
			if (Devs::m_UnloaderMotion.Is_UnloaderZ_WaitPos())
			{
				//SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_X_WAIT_POS_2ND, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_X_WAIT_POS_2ND"));
				SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_CST_RECV_DONE_MOVE, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_CST_RECV_DONE_MOVE"));
				SetTimeOut(TIME_OUT_FLOW);
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Z_WAIT_POS_FINISH_CHECK : Time Out"), eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW + 30);
				SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Z_WAIT_POS_FINISH_CHECK, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Z_WAIT_POS_FINISH_CHECK"));
			}
			break;

		case _eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_X_WAIT_POS_2ND:
			Devs::m_UnloaderMotion.UnloaderX_WaitPos();

			SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_X_WAIT_POS_2ND_CHECK, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_X_WAIT_POS_2ND_CHECK"));
			SetTimeOut(TIME_OUT_FLOW);
			break;

		case _eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_X_WAIT_POS_2ND_CHECK:
			if (Devs::m_UnloaderMotion.Is_UnloaderX_WaitPos())
			{
				SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_CST_RECV_DONE_MOVE, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_CST_RECV_DONE_MOVE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_X_WAIT_POS_2ND_CHECK : Time Out"), eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW + 32);
				SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_X_WAIT_POS_2ND_CHECK, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_X_WAIT_POS_2ND_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Cst Move
		case _eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_CST_RECV_READY_MOVE:
			Devs::m_CstRecvReadyFlow.Start(m_eTargetFloor);
			Sleep(20);

			SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Y_UNLOAD_POS, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Y_UNLOAD_POS"));
			break;

		case _eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_CST_RECV_READY_DONE_CHECK:
			if (Devs::m_CstRecvReadyFlow.IsFlowDone())
			{
				SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Z_UNLOAD_POS, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_UNLOADER_Z_UNLOAD_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_CST_RECV_READY_DONE_CHECK : Time Out"), ePAPER_UNLOAD_FLOW + 29);
				SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_CST_RECV_READY_DONE_CHECK, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_CST_RECV_READY_DONE_CHECK"));
			}
			break;

		case _eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_CST_RECV_DONE_MOVE:
			Devs::m_CstRecvDoneFlow.Start();
			Sleep(20);

			SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_CST_RECV_DONE_DONE_CHECK, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_CST_RECV_DONE_DONE_CHECK"));
			break;

		case _eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_CST_RECV_DONE_DONE_CHECK:
			if (Devs::m_CstRecvDoneFlow.IsFlowDone())
			{
				SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_DONE, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_CST_RECV_DONE_DONE_CHECK : Time Out"), eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW + 29);
				SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_CST_RECV_DONE_DONE_CHECK, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_CST_RECV_DONE_DONE_CHECK"));
			}
			break;
#pragma endregion 
		
		case _eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_ERROR:
				break;

		case _eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_DONE:
		{
			SharedInfo::nPrevFlowID = eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW; //KJT 20210326

			m_bFlowDone = TRUE;

			SharedInfo::CalTactTime(_T("STICK_UNLOAD_IN_STAGE_TO_CST_FLOW"), m_timeStart); //KJT 20210329

			SetStep(_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_IDLE, _T("_eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW_IDLE"));
			break;
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

BOOL CStickUnloadInStageToCstFlow::FlowInterlock()
{
	CString Str = _T("");

	if (Devs::m_CassetteMotion.Is_CSTPickUpUnitBwd() == FALSE)
	{
		Total_Msg(_T("Check Pickup Unit Backward !!!"));
		SharedInfo::SetAlarm(_T("StickUnloadInStageToCstFlow : Check Pickup Unit Backward"), eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW + 41);
		return FALSE;
	}

	if (Devs::m_CassetteMotion.Is_CSTSafefySensorOn() == TRUE)
	{
		Total_Msg(_T("Check CST Safety Sensor !!!"));
		SharedInfo::SetAlarm(_T("StickUnloadInStageToCstFlow : Check CST Safety Sensor"), eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW + 42);
		return FALSE;
	}

	if (Devs::m_UnloaderMotion.CheckUnloaderFlowInterlock(_T("StickUnloadInStageToCstFlow"), eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW, 50) == FALSE)
	{
		return FALSE;
	}

	/////////////////////////////////////////////////////////////////////////////
	if (Devs::m_GantryMotion.CheckGantryXYZFlowInterlock(_T("StickUnloadInStageToCstFlow"), eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW, 70) == FALSE)
	{
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

double CStickUnloadInStageToCstFlow::GetCSTTargetSlotPos()
{
	double dOffset = 10.0; //Temp

	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Unload_To_Cst_Pos;

	//dPos += (CModelData::m_MaterialPara.Info.dStickSizeY + dOffset) * SharedInfo::CstStickExistInfo.nCnt_Floor[0]; //Temp

	return dPos;
}