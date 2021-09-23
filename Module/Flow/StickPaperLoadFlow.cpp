#include "stdafx.h"
#include "StickPaperLoadFlow.h"
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

CStickPaperLoadFlow::CStickPaperLoadFlow()
{
}


CStickPaperLoadFlow::~CStickPaperLoadFlow()
{
}

BOOL CStickPaperLoadFlow::InitProcess()
{
	m_StateComplete = NULL;
	m_FlowFinish = TRUE;
	m_bTerminate = FALSE;
	m_bFlowDone = TRUE;

	m_dTargetPosZ_Loader = 0.0;
	m_dTargetPosZ_PaperUnloader = 0.0;
	m_dTargetPosX = 0.0;

#pragma region //Step Group
	int nGroupIndex = 0;

	m_sGroupInfo[nGroupIndex].m_bProcessingFlag = FALSE;
	m_sGroupInfo[nGroupIndex].nStartStep = _eSTICK_PAPER_LOAD_FLOW_START;
	m_sGroupInfo[nGroupIndex].nEndStep = _eSTICK_PAPER_LOAD_FLOW_INTERLOCK;
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
BOOL CStickPaperLoadFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eSTICK_PAPER_LOAD_FLOW_IDLE, _T("_eSTICK_PAPER_LOAD_FLOW_IDLE"));

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
BOOL CStickPaperLoadFlow::Start()
{
	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(_eSTICK_PAPER_LOAD_FLOW_START, _T("_eSTICK_PAPER_LOAD_FLOW_START"));
	return TRUE;
}
BOOL CStickPaperLoadFlow::Stop()
{
	m_bStopBit = TRUE;
	//SetStop(); //!!
	return TRUE;
}
UINT CStickPaperLoadFlow::ThreadFunction(LPVOID lpParam)
{
	CStickPaperLoadFlow* pFlow = NULL;

	pFlow = (CStickPaperLoadFlow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}
VOID CStickPaperLoadFlow::ThreadFunctionEntry(VOID)
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

			SetCurrentStep(_eSTICK_PAPER_LOAD_FLOW_IDLE);
			continue; //!!
		}

		switch (GetCurrentTotalStep())
		{
		case _eSTICK_PAPER_LOAD_FLOW_IDLE:
		{
			break;
		}
		case _eSTICK_PAPER_LOAD_FLOW_START:
		{
			m_timeStart = CTime::GetCurrentTime(); //KJT 20210329
			SharedInfo::m_timeUnitTact = m_timeStart;

			SharedInfo::nCurFlowID = eSTICK_PAPER_LOAD_FLOW;

			m_nStepDownCount = 0;
			m_nVibrationCount = 0;
			m_nMaxStepDownCount = CManualData::m_ManualDataLoader.Info.m_nLoaderZ_StepDownCount;
			m_nMaxVibrationCount = CManualData::m_ManualDataLoader.Info.m_nLoaderZ_VibrationCount;

			SharedInfo::LightAllOff();

			SetStep(_eSTICK_PAPER_LOAD_FLOW_INTERLOCK, _T("_eSTICK_PAPER_LOAD_FLOW_INTERLOCK"));
			break;
		}
		case _eSTICK_PAPER_LOAD_FLOW_INTERLOCK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
			}
			else
			{
				m_bGroupStepDone[m_nGroupStepIndex++] = TRUE; //KJT 20210221

				memcpy(SharedInfo::Active.tchStickId, SharedInfo::BoxStickExistInfo.tchStickId[eBOX_SHEET_MAX - SharedInfo::BoxStickExistInfo.nStickCount], sizeof(SharedInfo::Active.tchStickId));
				SharedInfo::SetAcitveStickPos(eACTIVE_STICK_POS_BOX); //KJT 20210328
				
				if (SharedInfo::MachineState.bAutoRunFlag == TRUE && SharedInfo::nPrevFlowID == eBOX_ALIGN_FLOW)
					SetStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_Y_LOAD_IN_BOX_POS, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Y_LOAD_IN_BOX_POS"));
				else
					SetStep(_eSTICK_PAPER_LOAD_FLOW_UNLOADER_READY, _T("_eSTICK_PAPER_LOAD_FLOW_UNLOADER_READY"));
			}
			break;

#pragma region //Unloader Ready
		case _eSTICK_PAPER_LOAD_FLOW_UNLOADER_READY:
			Devs::m_Ready_UnloaderFlow.Start();

			SetStep(_eSTICK_PAPER_LOAD_FLOW_UNLOADER_READY_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_UNLOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eSTICK_PAPER_LOAD_FLOW_UNLOADER_READY_CHECK:
			if (Devs::m_Ready_UnloaderFlow.IsFlowDone())
			{
				SetStep(_eSTICK_PAPER_LOAD_FLOW_GANTRY_ZX_READY, _T("_eSTICK_PAPER_LOAD_FLOW_GANTRY_ZX_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_UNLOADER_READY_CHECK : Time Out"), eSTICK_CLAMP_TENSION_FLOW + 0);
				SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_PAPER_LOAD_FLOW_UNLOADER_READY_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_UNLOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Gantry ZX Ready
		case _eSTICK_PAPER_LOAD_FLOW_GANTRY_ZX_READY:
			Devs::m_Ready_GantryZX_Flow.Start();

			SetStep(_eSTICK_PAPER_LOAD_FLOW_GANTRY_ZX_READY_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_GANTRY_ZX_READY_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eSTICK_PAPER_LOAD_FLOW_GANTRY_ZX_READY_CHECK:
			if (Devs::m_Ready_GantryZX_Flow.IsFlowDone())
			{
				SetStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_READY, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_GANTRY_ZX_READY_CHECK : Time Out"), eSTICK_CLAMP_TENSION_FLOW + 2);
				SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_PAPER_LOAD_FLOW_GANTRY_ZX_READY_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_GANTRY_ZX_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Loader Ready
		case _eSTICK_PAPER_LOAD_FLOW_LOADER_READY:
			Devs::m_Ready_LoaderFlow.Start();

			SetStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_READY_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eSTICK_PAPER_LOAD_FLOW_LOADER_READY_CHECK:
			if (Devs::m_Ready_LoaderFlow.IsFlowDone())
			{
				SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_ZX_READY, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_ZX_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_LOADER_READY_CHECK : Time Out"), eSTICK_CLAMP_TENSION_FLOW + 1);
				SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_READY_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //PaperUnloader ZX Ready
		case _eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_ZX_READY:
			Devs::m_Ready_PaperUnloaderZXFlow.Start();

			SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_ZX_READY_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_ZX_READY_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_ZX_READY_CHECK:
			if (Devs::m_Ready_PaperUnloaderZXFlow.IsFlowDone())
			{
				SetStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_Y_LOAD_IN_BOX_POS, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Y_LOAD_IN_BOX_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_ZX_READY_CHECK : Time Out"), eBOX_ALIGN_FLOW + 1);
				SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_ZX_READY_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_ZX_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //1. Loader Pickup In Box
			{
		case _eSTICK_PAPER_LOAD_FLOW_LOADER_Y_LOAD_IN_BOX_POS:
			Devs::m_LoaderMotion.LoaderY_Stick_LoadPos();
			Sleep(20); //!!!
			//SetStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_Y_LOAD_IN_BOX_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Y_LOAD_IN_BOX_POS_CHECK"));
			SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Y_PAPER_LOAD_IN_BOX_POS, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Y_PAPER_LOAD_IN_BOX_POS"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eSTICK_PAPER_LOAD_FLOW_LOADER_Y_LOAD_IN_BOX_POS_CHECK:
			if (Devs::m_LoaderMotion.Is_LoaderY_Stick_LoadPos())
			{
				//21.03.05 sjc temp skip
				//SetStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_SUB_Z_DOWN_POS, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_SUB_Z_DOWN_POS"));
				//SetStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_VAC_ON, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_VAC_ON"));

				m_bGroupStepDone[m_nGroupStepIndex++] = TRUE; //KJT 20210221
				SetStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_X_LOAD_IN_BOX_POS, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_X_LOAD_IN_BOX_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Y_LOAD_IN_BOX_POS_CHECK : Time Out"), eSTICK_PAPER_LOAD_FLOW + 6);
				SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_Y_LOAD_IN_BOX_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Y_LOAD_IN_BOX_POS_CHECK"));
			}
			break;

		case _eSTICK_PAPER_LOAD_FLOW_LOADER_X_LOAD_IN_BOX_POS:
			Devs::m_LoaderMotion.LoaderX_StickPickUpPos();
			Sleep(20); //!!

			SetStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_X_LOAD_IN_BOX_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_X_LOAD_IN_BOX_POS_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eSTICK_PAPER_LOAD_FLOW_LOADER_X_LOAD_IN_BOX_POS_CHECK:
			if (Devs::m_LoaderMotion.Is_LoaderX_StickPickUpPos())
			{
				m_bGroupStepDone[m_nGroupStepIndex++] = TRUE; //KJT 20210221
				//SetStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_CYLINDER_DOWN, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_CYLINDER_DOWN"));
				SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_PAPER_LOAD_DOWN_POS, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_PAPER_LOAD_DOWN_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_LOADER_X_LOAD_IN_BOX_POS_CHECK : Time Out"), eSTICK_PAPER_LOAD_FLOW + 7);
				SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_X_LOAD_IN_BOX_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_X_LOAD_IN_BOX_POS_CHECK"));
			}
			break;

			//case _eSTICK_PAPER_LOAD_FLOW_LOADER_SUB_Z_DOWN_POS:
			//	Devs::m_LoaderMotion.LoaderZL_DownPos();
			//	Sleep(10);
			//	Devs::m_LoaderMotion.LoaderZR_DownPos();
			//	SetStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_DOWN_POS, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_DOWN_POS"));
			//	SetTimeOut(TIME_OUT_STATE);
			//	break;

		case _eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_DOWN_POS:
#if 0
			Devs::m_LoaderMotion.LoaderZ_StickLoadInBox1stPos();
#else
			m_dTargetPosZ_Loader = CManualData::m_ManualDataLoader.Info.m_dLoaderZ_StickLoadInBox1st_Pos;
			dOffset = (CModelData::m_AtMaterialPara.Info.dPaperThickness * (eBOX_SHEET_MAX - SharedInfo::BoxStickExistInfo.nStickCount)) * (-1);
			dOffset += (CModelData::m_AtMaterialPara.Info.dStickThickness * (eBOX_SHEET_MAX - SharedInfo::BoxStickExistInfo.nStickCount)) * (-1);
			m_dTargetPosZ_Loader += dOffset;

			if (SharedInfo::CheckSafetyPos(AXIS_LOADER_Z, m_dTargetPosZ_Loader, &Str, &nSafetyPosErrorBy) == FALSE)
			{
				if (nSafetyPosErrorBy == eTARGET_POS_ERROR_BY_SAFETY_MIN)
					SharedInfo::SetAxisAlarm(AXIS_LOADER_Z, eTARGET_POS_ERROR_BY_SAFETY_MIN);
				else if (nSafetyPosErrorBy == eTARGET_POS_ERROR_BY_SAFETY_MAX)
					SharedInfo::SetAxisAlarm(AXIS_LOADER_Z, eTARGET_POS_ERROR_BY_SAFETY_MAX);

				Total_Msg(Str);
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_DOWN_POS : AXIS_LOADER_Z Pos Limit"), eSTICK_PAPER_LOAD_FLOW + 8);
				SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
				break;
			}

			Devs::m_LoaderMotion.MoveAxis(AXIS_LOADER_Z, m_dTargetPosZ_Loader);
			Sleep(20); //!!
			Str.Format(_T("Loader Z Stick Load Pos Down %.5f (-Offset Pos : %.5f)"), m_dTargetPosZ_Loader, dOffset);
			Total_Msg(Str);
#endif

			//SetStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_DOWN_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_DOWN_POS_CHECK"));
			SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_PAPER_LOAD_DOWN_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_PAPER_LOAD_DOWN_POS_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

			//case _eSTICK_PAPER_LOAD_FLOW_LOADER_SUB_Z_DOWN_POS_CHECK:
			//	if (Devs::m_LoaderMotion.Is_LoaderZL_DownPos() && Devs::m_LoaderMotion.Is_LoaderZR_DownPos())
			//	{
			//		//SetStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_DOWN_POS, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_DOWN_POS"));
			//		SetStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_DOWN_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_DOWN_POS_CHECK"));
			//	}
			//	else if (IsTimeOut())
			//	{
			//		SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_LOADER_SUB_Z_DOWN_POS_CHECK : Time Out"), eSTICK_PAPER_LOAD_FLOW + 9);
			//		SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
			//	}
			//	else
			//	{
			//		SetCheckStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_SUB_Z_DOWN_POS_CHECK);
			//	}
			//	break;



		case _eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_DOWN_POS_CHECK:
#if 0
			if (Devs::m_LoaderMotion.Is_LoaderZ_StickLoadInBox1stPos())
#else
			if (Devs::m_LoaderMotion.IsMoveDone(AXIS_LOADER_Z, m_dTargetPosZ_Loader))
#endif
			{
				m_bGroupStepDone[m_nGroupStepIndex++] = TRUE; //KJT 20210221
				SetStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_VAC_ON, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_VAC_ON"));
				//
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_DOWN_POS_CHECK : Time Out"), eSTICK_PAPER_LOAD_FLOW + 10);
				SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_DOWN_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_DOWN_POS_CHECK"));
			}
			break;

		case _eSTICK_PAPER_LOAD_FLOW_LOADER_VAC_ON:
			//Devs::m_BoxMotion.BoxMagnetic_Chuck_On();
			//Sleep(100);
			//Devs::m_LoaderMotion.Paper_Active_Vac_On();
			//Sleep(50);
			Devs::m_LoaderMotion.Stick_Active_Vac_On();
			Sleep(10);
			SetStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_STEP_DOWN, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_STEP_DOWN"));
			break;

		case _eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_STEP_DOWN:
			m_dTargetPosZ_Loader = SharedInfo::GetCmdPos(AXIS_LOADER_Z);
			m_dTargetPosZ_Loader -= CManualData::m_ManualDataLoader.Info.m_dLoaderZ_StepDownOffset;
			if (SharedInfo::CheckSafetyPos(AXIS_LOADER_Z, m_dTargetPosZ_Loader, &Str, &nSafetyPosErrorBy) == FALSE)
			{
				if (nSafetyPosErrorBy == eTARGET_POS_ERROR_BY_SAFETY_MIN)
					SharedInfo::SetAxisAlarm(AXIS_LOADER_Z, eTARGET_POS_ERROR_BY_SAFETY_MIN);
				else if (nSafetyPosErrorBy == eTARGET_POS_ERROR_BY_SAFETY_MAX)
					SharedInfo::SetAxisAlarm(AXIS_LOADER_Z, eTARGET_POS_ERROR_BY_SAFETY_MAX);

				Total_Msg(Str);
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_STEP_DOWN : AXIS_LOADER_Z Pos Limit"), eSTICK_PAPER_LOAD_FLOW + 11);
				SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
				break;
			}

			Devs::m_LoaderMotion.MoveAxis(AXIS_LOADER_Z, m_dTargetPosZ_Loader);
			Str.Format(_T("Loader Z Step Down %.5f (To Pos : %.5f)"), CManualData::m_ManualDataLoader.Info.m_dLoaderZ_StepDownOffset, m_dTargetPosZ_Loader);
			Total_Msg(Str);

			SetStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_STEP_DOWN_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_STEP_DOWN_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_STEP_DOWN_CHECK:
			if (Devs::m_LoaderMotion.IsMoveDone(AXIS_LOADER_Z, m_dTargetPosZ_Loader))
			{
				Sleep(3000); //!! //KJT 20210823 2000->3000

				if (Devs::m_LoaderMotion.Is_Stick_Active_Vac_On())
				{
					m_nVibrationCount = 0; //KJT 20210317
					//SetStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_STEP_UP, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_STEP_UP")); //KJT 20210316
					SetStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_WAIT_POS, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_WAIT_POS")); //KJT 20210316
					break;
				}
				else if (++m_nStepDownCount < m_nMaxStepDownCount)
				{
					SetStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_STEP_DOWN, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_STEP_DOWN"));
				}
				else
				{
					Str.Format(_T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_STEP_DOWN_CHECK : Count %d Over"), m_nMaxStepDownCount);
					SharedInfo::SetAlarm(Str, eSTICK_PAPER_LOAD_FLOW + 12);
					SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
				}
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_STEP_DOWN_CHECK : Time Out"), eSTICK_PAPER_LOAD_FLOW + 12);
				SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_STEP_DOWN_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_STEP_DOWN_CHECK"));
			}
			break;

			//case _eSTICK_PAPER_LOAD_FLOW_LOADER_VAC_ON_CHECK:
			//	if (Devs::m_BoxMotion.Is_BoxMagnetic_Chuck_On() && Devs::m_LoaderMotion.Is_Stick_Active_Vac_On() && Devs::m_LoaderMotion.Is_Paper_Active_Vac_On())
			//	{
			//		m_bGroupStepDone[m_nGroupStepIndex++] = TRUE; //KJT 20210221

			//		//Sleep(1000); //!!
			//		Sleep(500); //!!
			//		if (SharedInfo::BoxStickExistInfo.nStickCount > 1)
			//		{
			//			m_nVibrationCount = 0; //KJT 20210317
			//			SetStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_STEP_UP, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_STEP_UP")); //KJT 20210316
			//		}
			//		else //KJT 20210328
			//		{
			//			SetStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_WAIT_POS, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_WAIT_POS")); //KJT 20210316
			//		}
			//	}
			//	else
			//	{
			//		SetStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_STEP_DOWN, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_STEP_DOWN"));
			//	}
			//	break;

		case _eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_STEP_UP: //KJT 20210316
			m_dTargetPosZ_Loader = SharedInfo::GetCmdPos(AXIS_LOADER_Z);
			m_dTargetPosZ_Loader += CManualData::m_ManualDataLoader.Info.m_dLoaderZ_StepUpOffset;

			Devs::m_LoaderMotion.MoveAxis(AXIS_LOADER_Z, m_dTargetPosZ_Loader);
			Str.Format(_T("Loader Z Step Up %.5f (To Pos : %.5f)"), CManualData::m_ManualDataLoader.Info.m_dLoaderZ_StepUpOffset, m_dTargetPosZ_Loader);
			Total_Msg(Str);

			SetStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_STEP_UP_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_STEP_UP_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_STEP_UP_CHECK: //KJT 20210316
			if (Devs::m_LoaderMotion.IsMoveDone(AXIS_LOADER_Z, m_dTargetPosZ_Loader))
			{
				//Sleep(3000); //!!
				//Sleep(1000); //!!
				//if (SharedInfo::GetCmdPos(AXIS_LOADER_Z) >= CManualData::m_ManualDataLoader.Info.m_dLoaderZ_Vibration_Pos)
				//	SetStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_VIBRATION_DOWN_POS, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_VIBRATION_DOWN_POS"));
				//else
				//	SetStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_STEP_UP, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_STEP_UP"));

				SetStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_VIBRATION_UP_POS, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_VIBRATION_UP_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_STEP_UP_CHECK : Time Out"), eSTICK_PAPER_LOAD_FLOW + 13);
				SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_STEP_UP_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_STEP_UP_CHECK"));
			}
			break;

		case _eSTICK_PAPER_LOAD_FLOW_LOADER_Z_VIBRATION_UP_POS: //KJT 20210317
			m_dTargetPosZ_Loader = SharedInfo::GetCmdPos(AXIS_LOADER_Z);
			m_dTargetPosZ_Loader += CManualData::m_ManualDataLoader.Info.m_dLoaderZ_VibrationOffset;

			//KJT 20210323
			dVel = CManualData::m_ManualDataLoader.Info.m_dLoaderZ_VibrationVel;
			dAccel = dVel * 5.0;
			dDecel = dVel * 5.0;
			Devs::m_JogMotion.AbsMove(AXIS_LOADER_Z, m_dTargetPosZ_Loader, dVel, dAccel, dDecel);

			Str.Format(_T("Loader Z Step Up %.5f (To Pos : %.5f)"), CManualData::m_ManualDataLoader.Info.m_dLoaderZ_VibrationOffset, m_dTargetPosZ_Loader);
			Total_Msg(Str);

			SetStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_VIBRATION_UP_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_VIBRATION_UP_POS_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eSTICK_PAPER_LOAD_FLOW_LOADER_Z_VIBRATION_UP_POS_CHECK:
			if (Devs::m_LoaderMotion.IsMoveDone(AXIS_LOADER_Z, m_dTargetPosZ_Loader))
			{
				//Sleep(500); //!!
				//if (SharedInfo::GetCmdPos(AXIS_LOADER_Z) >= CManualData::m_ManualDataLoader.Info.m_dLoaderZ_Vibration_Pos)
				//	SetStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_VIBRATION_DOWN_POS, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_VIBRATION_DOWN_POS"));
				//else
				//	SetStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_STEP_UP, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_STEP_UP"));

				SetStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_VIBRATION_DOWN_POS, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_VIBRATION_DOWN_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_VIBRATION_UP_POS_CHECK : Time Out"), eSTICK_PAPER_LOAD_FLOW + 14);
				SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_VIBRATION_UP_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_VIBRATION_UP_POS_CHECK"));
			}
			break;


			//case _eSTICK_PAPER_LOAD_FLOW_LOADER_Z_VIBRATION_POS: //KJT 20210317
			//	Devs::m_BoxMotion.BoxMagnetic_Chuck_Off();
			//	Sleep(10);
			//	Devs::m_LoaderMotion.LoaderZ_Vibration_Pos();
			//	Sleep(10);

			//	SetStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_VIBRATION_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_VIBRATION_POS_CHECK"));
			//	SetTimeOut(TIME_OUT_STATE);
			//	break;

			//case _eSTICK_PAPER_LOAD_FLOW_LOADER_Z_VIBRATION_POS_CHECK:
			//	if (Devs::m_BoxMotion.Is_BoxMagnetic_Chuck_Off() && Devs::m_LoaderMotion.Is_LoaderZ_Vibration_Pos())
			//	{
			//		SetStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_VIBRATION_DOWN_POS, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_VIBRATION_DOWN_POS"));
			//	}
			//	else if (IsTimeOut())
			//	{
			//		SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
			//	}
			//	else
			//	{
			//		SetCheckStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_VIBRATION_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_VIBRATION_POS_CHECK"));
			//	}
			//	break;

		case _eSTICK_PAPER_LOAD_FLOW_LOADER_Z_VIBRATION_DOWN_POS: //KJT 20210317
			m_dTargetPosZ_Loader = SharedInfo::GetCmdPos(AXIS_LOADER_Z);
			m_dTargetPosZ_Loader -= CManualData::m_ManualDataLoader.Info.m_dLoaderZ_VibrationOffset;
			if (SharedInfo::CheckSafetyPos(AXIS_LOADER_Z, m_dTargetPosZ_Loader, &Str, &nSafetyPosErrorBy) == FALSE)
			{
				if (nSafetyPosErrorBy == eTARGET_POS_ERROR_BY_SAFETY_MIN)
					SharedInfo::SetAxisAlarm(AXIS_LOADER_Z, eTARGET_POS_ERROR_BY_SAFETY_MIN);
				else if (nSafetyPosErrorBy == eTARGET_POS_ERROR_BY_SAFETY_MAX)
					SharedInfo::SetAxisAlarm(AXIS_LOADER_Z, eTARGET_POS_ERROR_BY_SAFETY_MAX);

				Total_Msg(Str);
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_VIBRATION_DOWN_POS : AXIS_LOADER_Z Pos Limit"), eSTICK_PAPER_LOAD_FLOW + 15);
				SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
				break;
			}

			//KJT 20210323
			dVel = CManualData::m_ManualDataLoader.Info.m_dLoaderZ_VibrationVel;
			dAccel = dVel * 5.0;
			dDecel = dVel * 5.0;
			Devs::m_JogMotion.AbsMove(AXIS_LOADER_Z, m_dTargetPosZ_Loader, dVel, dAccel, dDecel);

			Str.Format(_T("Loader Z Vibration Down %.5f (To Pos : %.5f)"), CManualData::m_ManualDataLoader.Info.m_dLoaderZ_VibrationOffset, m_dTargetPosZ_Loader);
			Total_Msg(Str);

			//Sleep(1000); //!!
			Sleep(500); //!!
			SetStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_VIBRATION_DOWN_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_VIBRATION_DOWN_POS_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eSTICK_PAPER_LOAD_FLOW_LOADER_Z_VIBRATION_DOWN_POS_CHECK:
			if (Devs::m_LoaderMotion.IsMoveDone(AXIS_LOADER_Z, m_dTargetPosZ_Loader))
			{
				if (++m_nVibrationCount >= m_nMaxVibrationCount)
					SetStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_WAIT_POS, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_WAIT_POS"));
				else
					SetStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_VIBRATION_UP_POS, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_VIBRATION_UP_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_VIBRATION_DOWN_POS_CHECK : Time Out"), eSTICK_PAPER_LOAD_FLOW + 16);
				SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_VIBRATION_DOWN_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_VIBRATION_DOWN_POS_CHECK"));
			}
			break;

		case _eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_WAIT_POS:
			//Devs::m_BoxMotion.BoxMagnetic_Chuck_Off();
			//Sleep(10);
			Devs::m_LoaderMotion.LoaderZ_WaitPos();

			SetStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_WAIT_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;



		case _eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_WAIT_POS_CHECK:
			if (Devs::m_LoaderMotion.Is_LoaderZ_WaitPos())
			{
				if (Devs::m_LoaderMotion.Is_Stick_Active_Vac_On() == FALSE)
				{
					Total_Msg(_T("Check Loader Sitck Active Vac On !!!"));
					SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_WAIT_POS_CHECK : Vac On"), eSTICK_PAPER_LOAD_FLOW + 17);
					SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
				}
				//else if (Devs::m_LoaderMotion.Is_Paper_Active_Vac_On() == FALSE)
				//{
				//	Total_Msg(_T("Check Loader Paper Active Vac On !!!"));
				//	SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_WAIT_POS_CHECK : Vac On"), eSTICK_PAPER_LOAD_FLOW + 18);
				//	SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
				//}
				else
				{
					SharedInfo::SetAcitveStickPos(eACTIVE_STICK_POS_LOADER); //KJT 20210328
					SharedInfo::SetBoxStickExistInfo((enum_BoxSheet)(eBOX_SHEET_MAX - SharedInfo::BoxStickExistInfo.nStickCount), FALSE);

					m_bGroupStepDone[m_nGroupStepIndex++] = TRUE; //KJT 20210221

					SetStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_X_TENSION_POS, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_X_TENSION_POS"));
				}
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_WAIT_POS_CHECK : Time Out"), eSTICK_PAPER_LOAD_FLOW + 19);
				SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_WAIT_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_WAIT_POS_CHECK"));
			}
			break;

		case _eSTICK_PAPER_LOAD_FLOW_LOADER_X_TENSION_POS:
			m_dTargetPosX = SharedInfo::GetCmdPos(AXIS_LOADER_X);
			m_dTargetPosX += CManualData::m_ManualDataLoader.Info.m_dLoaderX_Tension_Offset;
			if (SharedInfo::CheckSafetyPos(AXIS_LOADER_X, m_dTargetPosX, &Str, &nSafetyPosErrorBy) == FALSE)
			{
				if (nSafetyPosErrorBy == eTARGET_POS_ERROR_BY_SAFETY_MIN)
					SharedInfo::SetAxisAlarm(AXIS_LOADER_X, eTARGET_POS_ERROR_BY_SAFETY_MIN);
				else if (nSafetyPosErrorBy == eTARGET_POS_ERROR_BY_SAFETY_MAX)
					SharedInfo::SetAxisAlarm(AXIS_LOADER_X, eTARGET_POS_ERROR_BY_SAFETY_MAX);

				Total_Msg(Str);
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_LOADER_X_TENSION_POS : Pos Limit"), eSTICK_PAPER_LOAD_FLOW + 28);
				SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
				break;
			}

			Devs::m_LoaderMotion.MoveAxis(AXIS_LOADER_X, m_dTargetPosX);
			Str.Format(_T("Loader X Tension Offset %.5f (To Pos : %.5f)"), CManualData::m_ManualDataLoader.Info.m_dLoaderX_Tension_Offset, m_dTargetPosX);
			Total_Msg(Str);

			SetStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_X_TENSION_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_X_TENSION_POS_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eSTICK_PAPER_LOAD_FLOW_LOADER_X_TENSION_POS_CHECK:
			if (Devs::m_LoaderMotion.IsMoveDone(AXIS_LOADER_X, m_dTargetPosX))
			{
				//SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Y_PAPER_LOAD_IN_BOX_POS, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Y_PAPER_LOAD_IN_BOX_POS"));
				SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STICK_LOAD_STEP_UP, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STICK_LOAD_STEP_UP"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_LOADER_X_TENSION_POS_CHECK : Time Out"), eSTICK_PAPER_LOAD_FLOW + 29);
				SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_X_TENSION_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_X_TENSION_POS_CHECK"));
			}
			break;
			}
#pragma endregion //1. Loader Pickup In Box

#pragma region //2. Paper PickUp In Box
		case _eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Y_PAPER_LOAD_IN_BOX_POS:
			Devs::m_UnloaderMotion.PaperUnloaderY_All_LoadPaperPos();
			Sleep(20); //!!!

			SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Y_PAPER_LOAD_IN_BOX_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Y_PAPER_LOAD_IN_BOX_POS_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Y_PAPER_LOAD_IN_BOX_POS_CHECK:
			if (Devs::m_UnloaderMotion.Is_PaperUnloaderY_All_LoadPaperPos())
			{
				SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_X_PAPER_LOAD_POS, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_X_PAPER_LOAD_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Y_PAPER_LOAD_IN_BOX_POS_CHECK : Time Out"), ePAPER_UNLOAD_FLOW + 5);
				SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Y_PAPER_LOAD_IN_BOX_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Y_PAPER_LOAD_IN_BOX_POS_CHECK"));
			}
			break;

		case _eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_X_PAPER_LOAD_POS:
			Devs::m_UnloaderMotion.PaperUnloaderX_All_PickUpPos();
			Sleep(20); //!!!

			SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_X_PAPER_LOAD_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_X_PAPER_LOAD_POS_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_X_PAPER_LOAD_POS_CHECK:
			if (Devs::m_UnloaderMotion.Is_PaperUnloaderX_All_PickUpPos())
			{
				SetStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_Y_LOAD_IN_BOX_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Y_LOAD_IN_BOX_POS_CHECK"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_X_PAPER_LOAD_POS_CHECK : Time Out"), ePAPER_UNLOAD_FLOW + 6);
				SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_X_PAPER_LOAD_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_X_PAPER_LOAD_POS_CHECK"));
			}
			break;

		case _eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_PAPER_LOAD_DOWN_POS:
			dOffset = (CModelData::m_AtMaterialPara.Info.dPaperThickness * (eBOX_SHEET_MAX - SharedInfo::BoxStickExistInfo.nStickCount)) * (-1);

			m_dTargetPosZ_PaperUnloader = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZL_Paper_Load_Pos;
			m_dTargetPosZ_PaperUnloader += dOffset;
			if (SharedInfo::CheckSafetyPos(AXIS_UNLOADER_ZL, m_dTargetPosZ_PaperUnloader, &Str, &nSafetyPosErrorBy) == FALSE)
			{
				if (nSafetyPosErrorBy == eTARGET_POS_ERROR_BY_SAFETY_MIN)
					SharedInfo::SetAxisAlarm(AXIS_UNLOADER_ZL, eTARGET_POS_ERROR_BY_SAFETY_MIN);
				else if (nSafetyPosErrorBy == eTARGET_POS_ERROR_BY_SAFETY_MAX)
					SharedInfo::SetAxisAlarm(AXIS_UNLOADER_ZL, eTARGET_POS_ERROR_BY_SAFETY_MAX);

				Total_Msg(Str);
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_PAPER_LOAD_DOWN_POS : AXIS_UNLOADER_ZL Pos limit"), ePAPER_UNLOAD_FLOW + 6);
				SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
				break;
			}

			Devs::m_UnloaderMotion.MoveAxis(AXIS_UNLOADER_ZL, m_dTargetPosZ_PaperUnloader);
			Sleep(20);

			Str.Format(_T("PaperUnloaderZ Move To Paper Load Pos. Offset:%.5f (Pos Z:%.5f)"), dOffset, m_dTargetPosZ_PaperUnloader);
			Total_Msg(Str);

			//SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_PAPER_LOAD_DOWN_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_PAPER_LOAD_DOWN_POS_CHECK"));
			SetStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_DOWN_POS, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_DOWN_POS"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_PAPER_LOAD_DOWN_POS_CHECK:
			if (Devs::m_UnloaderMotion.IsMoveDone(AXIS_UNLOADER_ZL, m_dTargetPosZ_PaperUnloader))
			{
				SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_VAC_ON, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_VAC_ON"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_DOWN_POS_CHECK : Time Out"), ePAPER_UNLOAD_FLOW + 8);
				SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_PAPER_LOAD_DOWN_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_PAPER_LOAD_DOWN_POS_CHECK"));
			}
			break;

		case _eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_VAC_ON:
			Devs::m_UnloaderMotion.PaperUnloader_Active_Vac_On();

			Sleep(500); //!!
			m_nStepDownCount = 0;
			SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STEP_DOWN, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STEP_DOWN"));
			break;

		case _eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STEP_DOWN:
			m_dTargetPosZ_PaperUnloader = SharedInfo::GetCmdPos(AXIS_UNLOADER_ZL);
			m_dTargetPosZ_PaperUnloader -= CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_StepDownOffset;
			if (SharedInfo::CheckSafetyPos(AXIS_UNLOADER_ZL, m_dTargetPosZ_PaperUnloader, &Str, &nSafetyPosErrorBy) == FALSE)
			{
				if (nSafetyPosErrorBy == eTARGET_POS_ERROR_BY_SAFETY_MIN)
					SharedInfo::SetAxisAlarm(AXIS_UNLOADER_ZL, eTARGET_POS_ERROR_BY_SAFETY_MIN);
				else if (nSafetyPosErrorBy == eTARGET_POS_ERROR_BY_SAFETY_MAX)
					SharedInfo::SetAxisAlarm(AXIS_UNLOADER_ZL, eTARGET_POS_ERROR_BY_SAFETY_MAX);

				Total_Msg(Str);
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STEP_DOWN : AXIS_UNLOADER_ZL Pos Limit"), ePAPER_UNLOAD_FLOW + 9);
				SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
				break;
			}

			Devs::m_UnloaderMotion.MoveAxis(AXIS_UNLOADER_ZL, m_dTargetPosZ_PaperUnloader);
			Sleep(20);

			Str.Format(_T("PaperUnloaderZ Step Down Offset:%.5f (Pos ZL:%.5f)"), CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_StepDownOffset, m_dTargetPosZ_PaperUnloader);
			Total_Msg(Str);

			SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STEP_DOWN_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STEP_DOWN_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STEP_DOWN_CHECK:
			if (Devs::m_UnloaderMotion.IsMoveDone(AXIS_UNLOADER_ZL, m_dTargetPosZ_PaperUnloader))
			{
				Sleep(3000); //!! //KJT 20210823 2000->3000

				if (Devs::m_UnloaderMotion.Is_PaperUnloader_Active_Vac_On())
				{
					m_nVibrationCount = 0; //KJT 20210317
					//SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STICK_LOAD_STEP_UP, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STICK_LOAD_STEP_UP"));
					SetStep(_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_DOWN_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_STICK_LOAD_DOWN_POS_CHECK"));
					break;
				}
				else if (++m_nStepDownCount < m_nMaxStepDownCount)
				{
					SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STEP_DOWN, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STEP_DOWN"));
				}
				else
				{
					Str.Format(_T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STEP_DOWN_CHECK : Count %d Over"), m_nMaxStepDownCount);
					SharedInfo::SetAlarm(Str, ePAPER_UNLOAD_FLOW + 11);
					SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
				}
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STEP_DOWN_CHECK : Time Out"), ePAPER_UNLOAD_FLOW + 11);
				SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STEP_DOWN_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STEP_DOWN_CHECK"));
			}
			break;

		case _eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STICK_LOAD_STEP_UP:
			m_dTargetPosZ_PaperUnloader = SharedInfo::GetCmdPos(AXIS_UNLOADER_ZL);
			m_dTargetPosZ_PaperUnloader += CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_StepUpOffset;

			Devs::m_UnloaderMotion.MoveAxis(AXIS_UNLOADER_ZL, m_dTargetPosZ_PaperUnloader);
			Sleep(20);

			Str.Format(_T("PaperUnloaderZ Step Up Offset:%.5f (Pos Z:%.5f)"), CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_StepUpOffset, m_dTargetPosZ_PaperUnloader);
			Total_Msg(Str);

			SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STICK_LOAD_STEP_UP_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STICK_LOAD_STEP_UP_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STICK_LOAD_STEP_UP_CHECK: //KJT 20210316
			if (Devs::m_UnloaderMotion.IsMoveDone(AXIS_UNLOADER_ZL, m_dTargetPosZ_PaperUnloader))
			{
				m_nVibrationCount = 0;
				SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_UP_POS, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_UP_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STICK_LOAD_STEP_UP_CHECK : Time Out"), ePAPER_UNLOAD_FLOW + 12);
				SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STICK_LOAD_STEP_UP_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STICK_LOAD_STEP_UP_CHECK"));
			}
			break;

		case _eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_UP_POS:
			m_dTargetPosZ_PaperUnloader = SharedInfo::GetCmdPos(AXIS_UNLOADER_ZL);
			m_dTargetPosZ_PaperUnloader += CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_VibrationOffset;

			//KJT 20210323
			dVel = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_VibrationVel;
			dAccel = dVel * 5.0;
			dDecel = dVel * 5.0;
			Devs::m_JogMotion.AbsMove(AXIS_UNLOADER_ZL, m_dTargetPosZ_PaperUnloader, dVel, dAccel, dDecel);
			Sleep(20);

			Str.Format(_T("PaperUnloaderZ Vibration Up Offset:%.5f (Pos Z:%.5f)"), CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_StepUpOffset, m_dTargetPosZ_PaperUnloader);
			Total_Msg(Str);

			SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_UP_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_UP_POS_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_UP_POS_CHECK:
			if (Devs::m_UnloaderMotion.IsMoveDone(AXIS_UNLOADER_ZL, m_dTargetPosZ_PaperUnloader))
			{
				SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_DOWN_POS, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_DOWN_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_UP_POS_CHECK : Time Out"), ePAPER_UNLOAD_FLOW + 13);
				SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_UP_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_UP_POS_CHECK"));
			}
			break;

		case _eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_DOWN_POS: //KJT 20210317
			m_dTargetPosZ_PaperUnloader = SharedInfo::GetCmdPos(AXIS_UNLOADER_ZL);
			m_dTargetPosZ_PaperUnloader -= CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_VibrationOffset;
			if (SharedInfo::CheckSafetyPos(AXIS_UNLOADER_ZL, m_dTargetPosZ_PaperUnloader, &Str, &nSafetyPosErrorBy) == FALSE)
			{
				if (nSafetyPosErrorBy == eTARGET_POS_ERROR_BY_SAFETY_MIN)
					SharedInfo::SetAxisAlarm(AXIS_UNLOADER_ZL, eTARGET_POS_ERROR_BY_SAFETY_MIN);
				else if (nSafetyPosErrorBy == eTARGET_POS_ERROR_BY_SAFETY_MAX)
					SharedInfo::SetAxisAlarm(AXIS_UNLOADER_ZL, eTARGET_POS_ERROR_BY_SAFETY_MAX);

				Total_Msg(Str);
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_DOWN_POS : AXIS_UNLOADER_ZL Pos Limit"), ePAPER_UNLOAD_FLOW + 14);
				SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
				break;
			}

			//KJT 20210323
			dVel = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_VibrationVel;
			dAccel = dVel * 5.0;
			dDecel = dVel * 5.0;
			Devs::m_JogMotion.AbsMove(AXIS_UNLOADER_ZL, m_dTargetPosZ_PaperUnloader, dVel, dAccel, dDecel);
			Sleep(20);

			Str.Format(_T("PaperUnloaderZ Vibration Down Offset:%.5f (Pos ZL:%.5f)"), CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_VibrationOffset, m_dTargetPosZ_PaperUnloader);
			Total_Msg(Str);

			Sleep(500); //!!
			SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_DOWN_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_DOWN_POS_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_DOWN_POS_CHECK:
			if (Devs::m_UnloaderMotion.IsMoveDone(AXIS_UNLOADER_ZL, m_dTargetPosZ_PaperUnloader))
			{
				if (++m_nVibrationCount >= m_nMaxVibrationCount)
					SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_WAIT_POS, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_WAIT_POS"));
				else
					SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_UP_POS, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_UP_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_VIBRATION_DOWN_POS_CHECK : Time Out"), ePAPER_UNLOAD_FLOW + 15);
				SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_DOWN_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_DOWN_POS_CHECK"));
			}
			break;

		case _eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_WAIT_POS:
			Devs::m_UnloaderMotion.PaperUnloaderZ_All_WaitPos();

			SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_WAIT_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_WAIT_POS_CHECK:
			if (Devs::m_UnloaderMotion.Is_PaperUnloaderZ_All_WaitPos())
			{
				if (Devs::m_UnloaderMotion.Is_PaperUnloader_Active_Vac_On() == FALSE)
				{
					Total_Msg(_T("Check PaperUnloader Active Vac On !!!"));
					SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_WAIT_POS_CHECK : Vac On"), ePAPER_UNLOAD_FLOW + 16);
					SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
				}
				else
				{
					SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_X_TENSION_POS, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_X_TENSION_POS"));
				}
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_LOADER_Z_WAIT_POS_CHECK : Time Out"), ePAPER_UNLOAD_FLOW + 17);
				SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_WAIT_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_WAIT_POS_CHECK"));
			}
			break;

		case _eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_X_TENSION_POS:
			m_dTargetPosX = SharedInfo::GetCmdPos(AXIS_UNLOADER_XL);
			m_dTargetPosX += CManualData::m_ManualDataUnloader.Info.m_dUnloaderX_Tension_Offset;
			if (SharedInfo::CheckSafetyPos(AXIS_UNLOADER_XL, m_dTargetPosX, &Str, &nSafetyPosErrorBy) == FALSE)
			{
				if (nSafetyPosErrorBy == eTARGET_POS_ERROR_BY_SAFETY_MIN)
					SharedInfo::SetAxisAlarm(AXIS_LOADER_X, eTARGET_POS_ERROR_BY_SAFETY_MIN);
				else if (nSafetyPosErrorBy == eTARGET_POS_ERROR_BY_SAFETY_MAX)
					SharedInfo::SetAxisAlarm(AXIS_LOADER_X, eTARGET_POS_ERROR_BY_SAFETY_MAX);

				Total_Msg(Str);
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_X_TENSION_POS : AXIS_UNLOADER_XL Pos Limit"), ePAPER_UNLOAD_FLOW + 28);
				SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
				break;
			}

			Devs::m_UnloaderMotion.MoveAxis(AXIS_UNLOADER_XL, m_dTargetPosX);

			Str.Format(_T("PaperUnloaderX Tension Pos Move. Offset:%.5f (Pos X:%.5f)"), CManualData::m_ManualDataUnloader.Info.m_dUnloaderX_Tension_Offset, m_dTargetPosX);
			Total_Msg(Str);

			SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_X_TENSION_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_X_TENSION_POS_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_X_TENSION_POS_CHECK:
			if (Devs::m_UnloaderMotion.IsMoveDone(AXIS_UNLOADER_XL, m_dTargetPosX))
			{
				SetStep(_eSTICK_PAPER_LOAD_FLOW_DONE, _T("_eSTICK_PAPER_LOAD_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_X_TENSION_POS_CHECK : Time Out"), ePAPER_UNLOAD_FLOW + 29);
				SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_X_TENSION_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_X_TENSION_POS_CHECK"));
			}
			break;
#pragma endregion //2. Paper PickUp In Box

		case _eSTICK_PAPER_LOAD_FLOW_ERROR:
			Devs::m_BoxMotion.BoxMagnetic_Chuck_Off();
			break;

		case _eSTICK_PAPER_LOAD_FLOW_DONE:
		{
			Devs::m_BoxMotion.BoxMagnetic_Chuck_Off();

			SharedInfo::nPrevFlowID = eSTICK_PAPER_LOAD_FLOW; //KJT 20210326

			m_bFlowDone = TRUE;

			SharedInfo::CalTactTime(_T("STICK_LOAD_IN_BOX_TO_STAGE_FLOW"), m_timeStart); //KJT 20210329

			SetStep(_eSTICK_PAPER_LOAD_FLOW_IDLE, _T("_eSTICK_PAPER_LOAD_FLOW_IDLE"));
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
BOOL CStickPaperLoadFlow::FlowInterlock()
{
	
#ifndef SIM_MODE
		
	if (Devs::m_LoaderMotion.CheckLoaderFlowInterlock(_T("StickPaperLoadFlow"), eSTICK_PAPER_LOAD_FLOW, 40) == FALSE)
	{
		return FALSE;
	}

	/////////////////////////////////////////////////////////////////////////////
	if (Devs::m_GantryMotion.CheckGantryXYZFlowInterlock(_T("StickPaperLoadFlow"), eSTICK_PAPER_LOAD_FLOW, 60) == FALSE)
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


#if 0 //Move Reserve
#pragma region //2. PaperUnloader PickUp In Box
{
		case _eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Y_PAPER_LOAD_POS:
			Devs::m_UnloaderMotion.UnloaderY_LoadPaperPos();
			Sleep(20); //!!!

			SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Y_PAPER_LOAD_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Y_PAPER_LOAD_POS"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Y_PAPER_LOAD_POS_CHECK:
			if (Devs::m_UnloaderMotion.Is_UnloaderY_LoadPaperPos())
			{
				m_bGroupStepDone[m_nGroupStepIndex++] = TRUE; //KJT 20210221
				SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_X_PAPER_LOAD_POS, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_X_PAPER_LOAD_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Y_PAPER_LOAD_POS_CHECK : Time Out"), eSTICK_PAPER_LOAD_FLOW + 20);
				SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Y_PAPER_LOAD_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Y_PAPER_LOAD_POS_CHECK"));
			}
			break;

		case _eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_X_PAPER_LOAD_POS:
			Devs::m_UnloaderMotion.PaperUnloaderXL_PickUpPos();
			Sleep(20); //!!!
			Devs::m_UnloaderMotion.PaperUnloaderXR_PickUpPos();
			Sleep(20); //!!!

			SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Y_PAPER_LOAD_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Y_PAPER_LOAD_POS"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_X_PAPER_LOAD_POS_CHECK:
			if (Devs::m_UnloaderMotion.Is_PaperUnloaderXL_PickUpPos() && Devs::m_UnloaderMotion.Is_PaperUnloaderXR_PickUpPos())
			{
				SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_PAPER_LOAD_DOWN_POS, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_PAPER_LOAD_DOWN_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_X_PAPER_LOAD_POS_CHECK : Time Out"), eSTICK_PAPER_LOAD_FLOW + 20);
				SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_X_PAPER_LOAD_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_X_PAPER_LOAD_POS_CHECK"));
			}
			break;

		case _eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_PAPER_LOAD_DOWN_POS:
			Devs::m_UnloaderMotion.UnloaderZL_DownPos();
			Sleep(20); //!!!
			Devs::m_UnloaderMotion.UnloaderZR_DownPos();
			Sleep(20); //!!!

			SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_PAPER_LOAD_DOWN_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_PAPER_LOAD_DOWN_POS_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_PAPER_LOAD_DOWN_POS_CHECK:
			if (Devs::m_UnloaderMotion.Is_UnloaderZL_DownPos() && Devs::m_UnloaderMotion.Is_UnloaderZR_DownPos())
			{
				m_bGroupStepDone[m_nGroupStepIndex++] = TRUE; //KJT 20210221
				SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_VAC_ON, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_VAC_ON"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_PAPER_LOAD_DOWN_POS_CHECK : Time Out"), eSTICK_PAPER_LOAD_FLOW + 21);
				SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_PAPER_LOAD_DOWN_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_PAPER_LOAD_DOWN_POS_CHECK"));
			}
			break;

		case _eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_VAC_ON:
			Devs::m_UnloaderMotion.Paper_Active_Vac_On();
			Sleep(10);

			m_nStepDownCount = 0;
			m_nVibrationCount = 0;
			m_nMaxStepDownCount = CManualData::m_ManualDataUnloader.Info.m_nUnloaderZ_StepDownCount;
			m_nMaxVibrationCount = CManualData::m_ManualDataUnloader.Info.m_nUnloaderZ_VibrationCount;

			SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STEP_DOWN, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STEP_DOWN"));
			break;

		case _eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STEP_DOWN:
			m_dTargetPosZL = SharedInfo::GetCmdPos(AXIS_UNLOADER_ZL);
			m_dTargetPosZL -= CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_StepDownOffset;
			if (SharedInfo::CheckSafetyPos(AXIS_UNLOADER_ZL, m_dTargetPosZL, &Str, &nSafetyPosErrorBy) == FALSE)
			{
				if (nSafetyPosErrorBy == eTARGET_POS_ERROR_BY_SAFETY_MIN)
					SharedInfo::SetAxisAlarm(AXIS_UNLOADER_ZL, eTARGET_POS_ERROR_BY_SAFETY_MIN);
				else if (nSafetyPosErrorBy == eTARGET_POS_ERROR_BY_SAFETY_MAX)
					SharedInfo::SetAxisAlarm(AXIS_UNLOADER_ZL, eTARGET_POS_ERROR_BY_SAFETY_MAX);

				Total_Msg(Str);
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STEP_DOWN AXIS_UNLOADER_ZL Pos Limit"), eSTICK_PAPER_LOAD_FLOW + 11);
				SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
				break;
			}
			m_dTargetPosZR = SharedInfo::GetCmdPos(AXIS_UNLOADER_ZR);
			m_dTargetPosZR -= CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_StepDownOffset;
			if (SharedInfo::CheckSafetyPos(AXIS_UNLOADER_ZR, m_dTargetPosZR, &Str, &nSafetyPosErrorBy) == FALSE)
			{
				if (nSafetyPosErrorBy == eTARGET_POS_ERROR_BY_SAFETY_MIN)
					SharedInfo::SetAxisAlarm(AXIS_UNLOADER_ZR, eTARGET_POS_ERROR_BY_SAFETY_MIN);
				else if (nSafetyPosErrorBy == eTARGET_POS_ERROR_BY_SAFETY_MAX)
					SharedInfo::SetAxisAlarm(AXIS_UNLOADER_ZR, eTARGET_POS_ERROR_BY_SAFETY_MAX);

				Total_Msg(Str);
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STEP_DOWN AXIS_UNLOADER_ZR Pos Limit"), eSTICK_PAPER_LOAD_FLOW + 11);
				SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
				break;
			}
			Devs::m_UnloaderMotion.MoveAxis(AXIS_UNLOADER_ZL, m_dTargetPosZL);
			Sleep(20);
			Devs::m_UnloaderMotion.MoveAxis(AXIS_UNLOADER_ZR, m_dTargetPosZR);
			Str.Format(_T("Unloader Z Step Down Offset:%.5f (Pos ZL:%.5f, ZR:%.5f)"), CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_StepDownOffset, m_dTargetPosZL, m_dTargetPosZR);
			Total_Msg(Str);

			SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STEP_DOWN_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STEP_DOWN_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STEP_DOWN_CHECK:
			if (Devs::m_UnloaderMotion.IsMoveDone(AXIS_UNLOADER_ZL, m_dTargetPosZL) && Devs::m_UnloaderMotion.IsMoveDone(AXIS_UNLOADER_ZR, m_dTargetPosZR))
			{
				Sleep(100);

				if (Devs::m_UnloaderMotion.Is_Paper_Active_Vac_On())
				{
					m_nVibrationCount = 0; //KJT 20210317
					SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STEP_UP, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STEP_UP")); //KJT 20210316
					break;
				}
				else if (++m_nStepDownCount < m_nMaxStepDownCount)
				{
					SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STEP_DOWN, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STEP_DOWN"));
				}
				else
				{
					Str.Format(_T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STEP_DOWN_CHECK : Count %d Over"), m_nMaxStepDownCount);
					SharedInfo::SetAlarm(Str, eSTICK_PAPER_LOAD_FLOW + 12);
					SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
				}
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STEP_DOWN_CHECK : Time Out"), eSTICK_PAPER_LOAD_FLOW + 12);
				SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STEP_DOWN_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STEP_DOWN_CHECK"));
			}
			break;
		case _eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STEP_UP:
			m_dTargetPosZL = SharedInfo::GetCmdPos(AXIS_UNLOADER_ZL);
			m_dTargetPosZL += CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_StepUpOffset;

			m_dTargetPosZR = SharedInfo::GetCmdPos(AXIS_UNLOADER_ZR);
			m_dTargetPosZR += CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_StepUpOffset;

			Devs::m_UnloaderMotion.MoveAxis(AXIS_UNLOADER_ZL, m_dTargetPosZL);
			Sleep(20);
			Devs::m_UnloaderMotion.MoveAxis(AXIS_UNLOADER_ZR, m_dTargetPosZR);

			Str.Format(_T("Unloader Z Step Up Offset:%.5f (Pos ZL:%.5f, ZR:%.5f)"), CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_StepUpOffset, m_dTargetPosZL, m_dTargetPosZR);
			Total_Msg(Str);

			SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STEP_UP_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STEP_UP_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STEP_UP_CHECK: //KJT 20210316
			if (Devs::m_UnloaderMotion.IsMoveDone(AXIS_UNLOADER_ZL, m_dTargetPosZL) && Devs::m_UnloaderMotion.IsMoveDone(AXIS_UNLOADER_ZR, m_dTargetPosZR))
			{
				SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_UP_POS, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_UP_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STEP_UP_CHECK : Time Out"), eSTICK_PAPER_LOAD_FLOW + 13);
				SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STEP_UP_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_STEP_UP_CHECK"));
			}
			break;

		case _eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_UP_POS:
			m_dTargetPosZL = SharedInfo::GetCmdPos(AXIS_UNLOADER_ZL);
			m_dTargetPosZL += CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_VibrationOffset;

			m_dTargetPosZR = SharedInfo::GetCmdPos(AXIS_UNLOADER_ZR);
			m_dTargetPosZR += CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_VibrationOffset;

			//KJT 20210323
			dVel = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_VibrationVel;
			dAccel = dVel * 5.0;
			dDecel = dVel * 5.0;

			Devs::m_JogMotion.AbsMove(AXIS_UNLOADER_ZL, m_dTargetPosZ, dVel, dAccel, dDecel);
			Sleep(20);
			Devs::m_JogMotion.AbsMove(AXIS_UNLOADER_ZR, m_dTargetPosZ, dVel, dAccel, dDecel);

			Str.Format(_T("Unloader Z Vibration Up Offset:%.5f (Pos ZL:%.5f, ZR:%.5f)"), CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_VibrationOffset, m_dTargetPosZL, m_dTargetPosZR);
			Total_Msg(Str);

			SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_UP_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_UP_POS_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_UP_POS_CHECK:
			if (Devs::m_UnloaderMotion.IsMoveDone(AXIS_UNLOADER_ZL, m_dTargetPosZL) && Devs::m_UnloaderMotion.IsMoveDone(AXIS_UNLOADER_ZR, m_dTargetPosZR))
			{
				SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_DOWN_POS, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_DOWN_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_UP_POS_CHECK : Time Out"), eSTICK_PAPER_LOAD_FLOW + 14);
				SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_UP_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_UP_POS_CHECK"));
			}
			break;

		case _eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_DOWN_POS:
			m_dTargetPosZL = SharedInfo::GetCmdPos(AXIS_UNLOADER_ZL);
			m_dTargetPosZL -= CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_VibrationOffset;
			if (SharedInfo::CheckSafetyPos(AXIS_UNLOADER_ZL, m_dTargetPosZL, &Str, &nSafetyPosErrorBy) == FALSE)
			{
				if (nSafetyPosErrorBy == eTARGET_POS_ERROR_BY_SAFETY_MIN)
					SharedInfo::SetAxisAlarm(AXIS_LOADER_Z, eTARGET_POS_ERROR_BY_SAFETY_MIN);
				else if (nSafetyPosErrorBy == eTARGET_POS_ERROR_BY_SAFETY_MAX)
					SharedInfo::SetAxisAlarm(AXIS_LOADER_Z, eTARGET_POS_ERROR_BY_SAFETY_MAX);

				Total_Msg(Str);
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_DOWN_POS : AXIS_UNLOADER_ZL Pos Limit"), eSTICK_PAPER_LOAD_FLOW + 15);
				SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
				break;
			}
			m_dTargetPosZR = SharedInfo::GetCmdPos(AXIS_UNLOADER_ZR);
			m_dTargetPosZR -= CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_VibrationOffset;
			if (SharedInfo::CheckSafetyPos(AXIS_UNLOADER_ZR, m_dTargetPosZR, &Str, &nSafetyPosErrorBy) == FALSE)
			{
				if (nSafetyPosErrorBy == eTARGET_POS_ERROR_BY_SAFETY_MIN)
					SharedInfo::SetAxisAlarm(AXIS_LOADER_Z, eTARGET_POS_ERROR_BY_SAFETY_MIN);
				else if (nSafetyPosErrorBy == eTARGET_POS_ERROR_BY_SAFETY_MAX)
					SharedInfo::SetAxisAlarm(AXIS_LOADER_Z, eTARGET_POS_ERROR_BY_SAFETY_MAX);

				Total_Msg(Str);
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_DOWN_POS : AXIS_UNLOADER_ZR Pos Limit"), eSTICK_PAPER_LOAD_FLOW + 15);
				SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
				break;
			}

			//KJT 20210323
			dVel = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_VibrationVel;
			dAccel = dVel * 5.0;
			dDecel = dVel * 5.0;
			Devs::m_JogMotion.AbsMove(AXIS_UNLOADER_ZL, m_dTargetPosZL, dVel, dAccel, dDecel);
			Sleep(20);
			Devs::m_JogMotion.AbsMove(AXIS_UNLOADER_ZR, m_dTargetPosZR, dVel, dAccel, dDecel);

			Str.Format(_T("Unloader Z Vibration Down Offset:%.5f (Pos ZL:%.5f, ZR:%.5f)"), CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_VibrationOffset, m_dTargetPosZL, m_dTargetPosZR);
			Total_Msg(Str);

			//Sleep(1000); //!!
			Sleep(500); //!!
			SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_DOWN_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_DOWN_POS_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_DOWN_POS_CHECK:
			if (Devs::m_UnloaderMotion.IsMoveDone(AXIS_UNLOADER_ZL, m_dTargetPosZL) && Devs::m_UnloaderMotion.IsMoveDone(AXIS_UNLOADER_ZR, m_dTargetPosZR))
			{
				if (++m_nVibrationCount >= m_nMaxVibrationCount)
					SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_WAIT_POS, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_WAIT_POS"));
				else
					SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_UP_POS, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_UP_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_DOWN_POS_CHECK : Time Out"), eSTICK_PAPER_LOAD_FLOW + 16);
				SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_DOWN_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_VIBRATION_DOWN_POS_CHECK"));
			}
			break;

		case _eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_WAIT_POS:
			Devs::m_UnloaderMotion.UnloaderZL_WaitPos();
			Sleep(20);
			Devs::m_UnloaderMotion.UnloaderZR_WaitPos();

			SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_WAIT_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_WAIT_POS_CHECK:
			if (Devs::m_UnloaderMotion.Is_UnloaderZL_WaitPos() && Devs::m_UnloaderMotion.Is_UnloaderZR_WaitPos())
			{
				if (Devs::m_UnloaderMotion.Is_Paper_Active_Vac_On() == FALSE)
				{
					Total_Msg(_T("Check PaperLoader Active Vac On !!!"));
					SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_WAIT_POS_CHECK : PaperUnloader Vac On Error"), eSTICK_PAPER_LOAD_FLOW + 17);
					SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
				}
				else
				{
					SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_X_TENSION_POS, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_X_TENSION_POS"));
				}
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_WAIT_POS_CHECK : Time Out"), eSTICK_PAPER_LOAD_FLOW + 19);
				SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_WAIT_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Z_WAIT_POS_CHECK"));
			}
			break;

		case _eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_X_TENSION_POS:
			m_dTargetPosXL = SharedInfo::GetCmdPos(AXIS_UNLOADER_XL);
			m_dTargetPosXL += CManualData::m_ManualDataUnloader.Info.m_dUnloaderX_Tension_Offset;
			if (SharedInfo::CheckSafetyPos(AXIS_UNLOADER_XL, m_dTargetPosXL, &Str, &nSafetyPosErrorBy) == FALSE)
			{
				if (nSafetyPosErrorBy == eTARGET_POS_ERROR_BY_SAFETY_MIN)
					SharedInfo::SetAxisAlarm(AXIS_LOADER_X, eTARGET_POS_ERROR_BY_SAFETY_MIN);
				else if (nSafetyPosErrorBy == eTARGET_POS_ERROR_BY_SAFETY_MAX)
					SharedInfo::SetAxisAlarm(AXIS_LOADER_X, eTARGET_POS_ERROR_BY_SAFETY_MAX);

				Total_Msg(Str);
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_X_TENSION_POS : AXIS_UNLOADER_XL Pos Limit"), eSTICK_PAPER_LOAD_FLOW + 28);
				SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
				break;
			}
			m_dTargetPosXR = SharedInfo::GetCmdPos(AXIS_UNLOADER_XR);
			m_dTargetPosXR += CManualData::m_ManualDataUnloader.Info.m_dUnloaderX_Tension_Offset;
			if (SharedInfo::CheckSafetyPos(AXIS_UNLOADER_XR, m_dTargetPosXL, &Str, &nSafetyPosErrorBy) == FALSE)
			{
				if (nSafetyPosErrorBy == eTARGET_POS_ERROR_BY_SAFETY_MIN)
					SharedInfo::SetAxisAlarm(AXIS_LOADER_X, eTARGET_POS_ERROR_BY_SAFETY_MIN);
				else if (nSafetyPosErrorBy == eTARGET_POS_ERROR_BY_SAFETY_MAX)
					SharedInfo::SetAxisAlarm(AXIS_LOADER_X, eTARGET_POS_ERROR_BY_SAFETY_MAX);

				Total_Msg(Str);
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_X_TENSION_POS : AXIS_UNLOADER_XR Pos Limit"), eSTICK_PAPER_LOAD_FLOW + 28);
				SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
				break;
			}

			Devs::m_UnloaderMotion.MoveAxis(AXIS_UNLOADER_XL, m_dTargetPosXL);
			Sleep(20);
			Devs::m_UnloaderMotion.MoveAxis(AXIS_UNLOADER_XR, m_dTargetPosXR);

			Str.Format(_T("Unloader X Tension. Offset:%.5f (Pos XL:%.5f, XR:%.5f)"), CManualData::m_ManualDataUnloader.Info.m_dUnloaderX_Tension_Offset, m_dTargetPosXL, m_dTargetPosXR);
			Total_Msg(Str);

			SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_X_TENSION_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_X_TENSION_POS_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_X_TENSION_POS_CHECK:
			if (Devs::m_UnloaderMotion.IsMoveDone(AXIS_UNLOADER_XL, m_dTargetPosXL) && Devs::m_UnloaderMotion.IsMoveDone(AXIS_UNLOADER_XR, m_dTargetPosXR))
			{
				SetStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Y_PAPER_UNLOAD_POS, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_Y_PAPER_UNLOAD_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_X_TENSION_POS_CHECK : Time Out"), eSTICK_PAPER_LOAD_FLOW + 29);
				SetStep(_eSTICK_PAPER_LOAD_FLOW_ERROR, _T("_eSTICK_PAPER_LOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_X_TENSION_POS_CHECK, _T("_eSTICK_PAPER_LOAD_FLOW_PAPER_UNLOADER_X_TENSION_POS_CHECK"));
			}
			break;
}
#pragma endregion //2. PaperUnloader PickUp In Box
#endif