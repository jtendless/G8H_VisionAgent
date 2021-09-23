#include "stdafx.h"
#include "StickPaperUnloadFlow.h"
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

CStickPaperUnloadFlow::CStickPaperUnloadFlow()
{
}


CStickPaperUnloadFlow::~CStickPaperUnloadFlow()
{
}

BOOL CStickPaperUnloadFlow::InitProcess()
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
	m_sGroupInfo[nGroupIndex].nStartStep = _eSTICK_PAPER_UNLOAD_FLOW_START;
	m_sGroupInfo[nGroupIndex].nEndStep = _eSTICK_PAPER_UNLOAD_FLOW_INTERLOCK;
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
BOOL CStickPaperUnloadFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eSTICK_PAPER_UNLOAD_FLOW_IDLE, _T("_eSTICK_PAPER_UNLOAD_FLOW_IDLE"));

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
BOOL CStickPaperUnloadFlow::Start()
{
	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(_eSTICK_PAPER_UNLOAD_FLOW_START, _T("_eSTICK_PAPER_UNLOAD_FLOW_START"));
	return TRUE;
}
BOOL CStickPaperUnloadFlow::Stop()
{
	m_bStopBit = TRUE;
	//SetStop(); //!!
	return TRUE;
}
UINT CStickPaperUnloadFlow::ThreadFunction(LPVOID lpParam)
{
	CStickPaperUnloadFlow* pFlow = NULL;

	pFlow = (CStickPaperUnloadFlow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}
VOID CStickPaperUnloadFlow::ThreadFunctionEntry(VOID)
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

			SetCurrentStep(_eSTICK_PAPER_UNLOAD_FLOW_IDLE);
			continue; //!!
		}

		switch (GetCurrentTotalStep())
		{
		case _eSTICK_PAPER_UNLOAD_FLOW_IDLE:
		{
			break;
		}
		case _eSTICK_PAPER_UNLOAD_FLOW_START:
		{
			m_timeStart = CTime::GetCurrentTime(); //KJT 20210329
			SharedInfo::m_timeUnitTact = m_timeStart;

			SharedInfo::nCurFlowID = eSTICK_PAPER_UNLOAD_FLOW;

			m_nStepDownCount = 0;
			m_nVibrationCount = 0;
			m_nMaxStepDownCount = CManualData::m_ManualDataLoader.Info.m_nLoaderZ_StepDownCount;
			m_nMaxVibrationCount = CManualData::m_ManualDataLoader.Info.m_nLoaderZ_VibrationCount;

			SharedInfo::LightAllOff();

			SetStep(_eSTICK_PAPER_UNLOAD_FLOW_INTERLOCK, _T("_eSTICK_PAPER_UNLOAD_FLOW_INTERLOCK"));
			break;
		}
		case _eSTICK_PAPER_UNLOAD_FLOW_INTERLOCK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(_eSTICK_PAPER_UNLOAD_FLOW_ERROR, _T("_eSTICK_PAPER_UNLOAD_FLOW_ERROR"));
			}
			else
			{				
				SetStep(_eSTICK_PAPER_UNLOAD_FLOW_PAPER_UNLOADER_Y_UNLOAD_START, _T("_eSTICK_PAPER_UNLOAD_FLOW_PAPER_UNLOADER_Y_UNLOAD_START"));
			}
			break;

		case _eSTICK_PAPER_UNLOAD_FLOW_PAPER_UNLOADER_Y_UNLOAD_START:	
			m_dPrevPos = SharedInfo::GetCmdPos(AXIS_UNLOADER_YL);
			if (SharedInfo::Active.eLastStickCstTargetFloor == eCASSETTE_FLOOR_NONE)
				Devs::m_PaperUnloadFlow.Start(eCASSETTE_FLOOR_1);
			else
				Devs::m_PaperUnloadFlow.Start(SharedInfo::Active.eLastStickCstTargetFloor);
			Sleep(100);

			SetStep(_eSTICK_PAPER_UNLOAD_FLOW_LOADER_Y_UNLOAD_UNLOAD_START, _T("_eSTICK_PAPER_UNLOAD_FLOW_LOADER_Y_UNLOAD_UNLOAD_START"));
			SetTimeOut(TIME_OUT_STATE); //TIME_OUT_STATE
			break;

		case _eSTICK_PAPER_UNLOAD_FLOW_LOADER_Y_UNLOAD_UNLOAD_START:
			m_dCurPos = SharedInfo::GetCmdPos(AXIS_UNLOADER_YL);
			if (Devs::m_PaperUnloadFlow.GetCurrentFlowStep() > Devs::m_PaperUnloadFlow._ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_Y_PAPER_UNLOAD_POS && m_dCurPos > m_dPrevPos + 100.0)
			{
				Devs::m_StickUnloadBoxToStageFlow.Start();

				SetStep(_eSTICK_PAPER_UNLOAD_FLOW_STICK_PAPER_UNLOAD_DONE_CHECK, _T("_eSTICK_PAPER_UNLOAD_FLOW_STICK_PAPER_UNLOAD_DONE_CHECK"));
				SetTimeOut(TIME_OUT_STATE);
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_UNLOAD_FLOW_LOADER_Y_UNLOAD_UNLOAD_START : PaperUnloaderY Move Time Out"), eSTICK_PAPER_UNLOAD_FLOW + 4);
				SetStep(_eSTICK_PAPER_UNLOAD_FLOW_ERROR, _T("_eSTICK_PAPER_UNLOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_PAPER_UNLOAD_FLOW_LOADER_Y_UNLOAD_UNLOAD_START, _T("_eSTICK_PAPER_UNLOAD_FLOW_LOADER_Y_UNLOAD_UNLOAD_START"));
			}
			break;

		case _eSTICK_PAPER_UNLOAD_FLOW_STICK_PAPER_UNLOAD_DONE_CHECK:
			if (Devs::m_PaperUnloadFlow.IsFlowDone() && Devs::m_StickUnloadBoxToStageFlow.IsFlowDone())
			{
				SetStep(_eSTICK_PAPER_UNLOAD_FLOW_DONE, _T("_eSTICK_PAPER_UNLOAD_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_PAPER_UNLOAD_FLOW_STICK_PAPER_UNLOAD_DONE_CHECK : Time Out"), eSTICK_PAPER_UNLOAD_FLOW + 4);
				SetStep(_eSTICK_PAPER_UNLOAD_FLOW_ERROR, _T("_eSTICK_PAPER_UNLOAD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_PAPER_UNLOAD_FLOW_STICK_PAPER_UNLOAD_DONE_CHECK, _T("_eSTICK_PAPER_UNLOAD_FLOW_STICK_PAPER_UNLOAD_DONE_CHECK"));
			}
			break;

		case _eSTICK_PAPER_UNLOAD_FLOW_ERROR:
			//Devs::m_BoxMotion.BoxMagnetic_Chuck_Off();
			break;

		case _eSTICK_PAPER_UNLOAD_FLOW_DONE:
		{
			//Devs::m_BoxMotion.BoxMagnetic_Chuck_Off();

			SharedInfo::nPrevFlowID = eSTICK_PAPER_UNLOAD_FLOW; //KJT 20210326

			m_bFlowDone = TRUE;

			SharedInfo::CalTactTime(_T("STICK_LOAD_IN_BOX_TO_STAGE_FLOW"), m_timeStart); //KJT 20210329

			SetStep(_eSTICK_PAPER_UNLOAD_FLOW_IDLE, _T("_eSTICK_PAPER_UNLOAD_FLOW_IDLE"));
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
BOOL CStickPaperUnloadFlow::FlowInterlock()
{
	CString Str = _T("");
#ifndef SIM_MODE
		
	if (Devs::m_LoaderMotion.CheckLoaderFlowInterlock(_T("StickPaperLoadFlow"), eSTICK_PAPER_UNLOAD_FLOW, 40) == FALSE)
	{
		return FALSE;
	}

	/////////////////////////////////////////////////////////////////////////////
	if (Devs::m_GantryMotion.CheckGantryXYZFlowInterlock(_T("StickPaperLoadFlow"), eSTICK_PAPER_UNLOAD_FLOW, 60) == FALSE)
	{
		return FALSE;
	}

	if (CMachineData::m_MachineDataMotor.Info.dAutoVel[AXIS_UNLOADER_YL] < CMachineData::m_MachineDataMotor.Info.dAutoVel[AXIS_LOADER_YL]) //!!!! Junying TPCD
	{
		Str.Format(_T("StickPaperUnloadFlow : PaperUnloaderY, LoaderY Auto Velocity Check (PaperUnloaderY < LoaderY) !!"), eSTICK_PAPER_UNLOAD_FLOW);
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, eSTICK_PAPER_UNLOAD_FLOW + 70);
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