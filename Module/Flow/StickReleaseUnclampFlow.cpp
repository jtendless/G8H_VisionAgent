#include "stdafx.h"
#include "StickReleaseUnclampFlow.h"
#include "Log/Logger.h"
#include "Vision/Devs.h"
#include "Data/ModelData.h"
#include "Data/ManualData.h"
#include "CamAreaModul.h"
#include "Data/SystemData.h"
//#include "../WkLibFlow/WkLibFlow.h"
#include "Flow/BaseFlow.h"

CStickReleaseUnclampFlow::CStickReleaseUnclampFlow()
{
}


CStickReleaseUnclampFlow::~CStickReleaseUnclampFlow()
{
}

BOOL CStickReleaseUnclampFlow::InitProcess()
{
	m_StateComplete = NULL;
	m_FlowFinish = TRUE;
	m_bTerminate = FALSE;
	m_bFlowDone = TRUE;

	//SetProcessLog(Process_Msg);
	//SetAlarmLog(Alarm_Msg);

	hHandle = CreateEvent(NULL, TRUE, FALSE, NULL);
	SetHandle(hHandle);
	pThread = AfxBeginThread(ThreadFunction, this);
	//pMappingProc = CMappingProc::GetInstance();
	return TRUE;
}

BOOL CStickReleaseUnclampFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eSTICK_RELEASE_UNCLAMP_FLOW_IDLE);

	if (hHandle != NULL)
	{
		CloseHandle(hHandle);
		hHandle = NULL;
	}

	return TRUE;
}

BOOL CStickReleaseUnclampFlow::Start(int nStep)
{
	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(nStep, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_START"));
	return TRUE;
}
BOOL CStickReleaseUnclampFlow::Stop()
{
	m_bStopBit = TRUE;
	return TRUE;
}

UINT CStickReleaseUnclampFlow::ThreadFunction(LPVOID lpParam)
{
	CStickReleaseUnclampFlow* pFlow = NULL;

	pFlow = (CStickReleaseUnclampFlow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}

VOID CStickReleaseUnclampFlow::ThreadFunctionEntry(VOID)
{
	DWORD	dwResult = 0;
	double	dStrt_Time = GetTickCount();
	double	dEnd_Time = GetTickCount();
	double	dWait_Time = GetTickCount();
	int		nWork_Mask_Mode = -1;
	int		nWork_Mask_Index = -1;
	BOOL	bComplete_Step = FALSE;

	CString Str = _T("");

	while (m_FlowFinish)
	{
		WaitForSingleObject(hHandle, INFINITE);
		ResetEvent(hHandle);

		if (SharedInfo::bMachineStopFlag == TRUE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(_eSTICK_RELEASE_UNCLAMP_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}

		switch (GetCurrentTotalStep())
		{
		case _eSTICK_RELEASE_UNCLAMP_FLOW_IDLE:
		{
			break;
		}
		case _eSTICK_RELEASE_UNCLAMP_FLOW_START:
		{
			m_timeStart = CTime::GetCurrentTime(); //KJT 20210329

			SetStep(_eSTICK_RELEASE_UNCLAMP_FLOW_INTERLOCK, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_INTERLOCK"));
			break;
		}

		case _eSTICK_RELEASE_UNCLAMP_FLOW_INTERLOCK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(_eSTICK_RELEASE_UNCLAMP_FLOW_ERROR, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_ERROR"));
			}
			else
			{
				SetStep(_eSTICK_RELEASE_UNCLAMP_FLOW_UNLOADER_READY, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_UNLOADER_READY"));
			}
			break;

#pragma region //Unloader Ready
		case _eSTICK_RELEASE_UNCLAMP_FLOW_UNLOADER_READY:
			Devs::m_Ready_UnloaderFlow.Start();

			SetStep(_eSTICK_RELEASE_UNCLAMP_FLOW_UNLOADER_READY_CHECK, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_UNLOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_RELEASE_UNCLAMP_FLOW_UNLOADER_READY_CHECK:
			if (Devs::m_Ready_UnloaderFlow.IsFlowDone())
			{
				SetStep(_eSTICK_RELEASE_UNCLAMP_FLOW_GANTRY_ZX_READY, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_GANTRY_ZX_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_RELEASE_UNCLAMP_FLOW_UNLOADER_READY_CHECK : Time Out"), eSTICK_RELEASE_UNCLAMP_FLOW + 0);
				SetStep(_eSTICK_RELEASE_UNCLAMP_FLOW_ERROR, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_RELEASE_UNCLAMP_FLOW_UNLOADER_READY_CHECK, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_UNLOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Gantry ZX Ready
		case _eSTICK_RELEASE_UNCLAMP_FLOW_GANTRY_ZX_READY:
			Devs::m_Ready_GantryZX_Flow.Start();

			SetStep(_eSTICK_RELEASE_UNCLAMP_FLOW_GANTRY_ZX_READY_CHECK, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_GANTRY_ZX_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_RELEASE_UNCLAMP_FLOW_GANTRY_ZX_READY_CHECK:
			if (Devs::m_Ready_GantryZX_Flow.IsFlowDone())
			{
				SetStep(_eSTICK_RELEASE_UNCLAMP_FLOW_LOADER_READY, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_LOADER_READY"));

				if (Devs::m_InspectionStageMotion.Is_Inspect_Stage_Vac_Off() == FALSE)
					SetStep(_eSTICK_RELEASE_UNCLAMP_FLOW_INSPECTION_STAGE_VAC_OFF, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_INSPECTION_STAGE_VAC_OFF"));
				else
					SetStep(_eSTICK_RELEASE_UNCLAMP_FLOW_GRIPPER_Z_TENSION_POS, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_GRIPPER_Z_TENSION_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_RELEASE_UNCLAMP_FLOW_GANTRY_ZX_READY_CHECK : Time Out"), eSTICK_RELEASE_UNCLAMP_FLOW + 2);
				SetStep(_eSTICK_RELEASE_UNCLAMP_FLOW_ERROR, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_RELEASE_UNCLAMP_FLOW_GANTRY_ZX_READY_CHECK, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_GANTRY_ZX_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Loader Ready
		case _eSTICK_RELEASE_UNCLAMP_FLOW_LOADER_READY:
			Devs::m_Ready_LoaderFlow.Start();

			SetStep(_eSTICK_RELEASE_UNCLAMP_FLOW_LOADER_READY_CHECK, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_LOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_RELEASE_UNCLAMP_FLOW_LOADER_READY_CHECK:
			if (Devs::m_Ready_LoaderFlow.IsFlowDone())
			{
				//SetStep(_eSTICK_RELEASE_UNCLAMP_FLOW_BOX_CAMERA_READY, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_BOX_CAMERA_READY"));
				SetStep(_eSTICK_RELEASE_UNCLAMP_FLOW_PAPER_UNLOADER_ZXY_READY, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_PAPER_UNLOADER_ZXY_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_RELEASE_UNCLAMP_FLOW_LOADER_READY_CHECK : Time Out"), eSTICK_RELEASE_UNCLAMP_FLOW + 1);
				SetStep(_eSTICK_RELEASE_UNCLAMP_FLOW_ERROR, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_RELEASE_UNCLAMP_FLOW_LOADER_READY_CHECK, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_LOADER_READY_CHECK"));
			}
			break;
#pragma endregion

//#pragma region //Box Camera Ready
//		case _eSTICK_RELEASE_UNCLAMP_FLOW_BOX_CAMERA_READY:
//			Devs::m_BoxMotion.BoxAlignCameraYL_WaitPos();
//			Sleep(20);
//			Devs::m_BoxMotion.BoxAlignCameraYR_WaitPos();
//			Sleep(500); //!!
//
//			SetStep(_eSTICK_RELEASE_UNCLAMP_FLOW_BOX_CAMERA_READY_CHECK, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_BOX_CAMERA_READY_CHECK"));
//			SetTimeOut(TIME_OUT_MOTION);
//			break;
//
//		case _eSTICK_RELEASE_UNCLAMP_FLOW_BOX_CAMERA_READY_CHECK:
//			if (Devs::m_BoxMotion.Is_BoxAlignCameraYL_WaitPos() == TRUE && Devs::m_BoxMotion.Is_BoxAlignCameraYR_WaitPos() == TRUE)
//			{
//				SetStep(_eSTICK_RELEASE_UNCLAMP_FLOW_GANTRY_ZX_READY, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_GANTRY_ZX_READY"));
//			}
//			else if (IsTimeOut())
//			{
//				SetStep(_eSTICK_RELEASE_UNCLAMP_FLOW_ERROR, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_ERROR"));
//			}
//			else
//			{
//				SetCheckStep(_eSTICK_RELEASE_UNCLAMP_FLOW_BOX_CAMERA_READY_CHECK, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_BOX_CAMERA_READY_CHECK"));
//			}
//			break;
//#pragma endregion

#pragma region //PaperUnloaderZX Ready
		case _eSTICK_RELEASE_UNCLAMP_FLOW_PAPER_UNLOADER_ZXY_READY:
			Devs::m_Ready_PaperUnloaderFlow.Start();

			SetStep(_eSTICK_RELEASE_UNCLAMP_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_RELEASE_UNCLAMP_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK:
			if (Devs::m_Ready_LoaderFlow.IsFlowDone())
			{
				SetStep(_eSTICK_RELEASE_UNCLAMP_FLOW_INSPECTION_STAGE_VAC_OFF, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_INSPECTION_STAGE_VAC_OFF"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_RELEASE_UNCLAMP_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK : Time Out"), eSTICK_UNLOAD_IN_STAGE_TO_CST_FLOW + 0);
				SetStep(_eSTICK_RELEASE_UNCLAMP_FLOW_ERROR, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_RELEASE_UNCLAMP_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK"));
			}
			break;
#pragma endregion

		case _eSTICK_RELEASE_UNCLAMP_FLOW_INSPECTION_STAGE_VAC_OFF:
			Devs::m_InspectionStageMotion.Inspect_Stage_Vac_Off();
			Sleep(1000); //!!

			SetStep(_eSTICK_RELEASE_UNCLAMP_FLOW_INSPECTION_STAGE_VAC_OFF_CHECK, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_INSPECTION_STAGE_VAC_OFF_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_RELEASE_UNCLAMP_FLOW_INSPECTION_STAGE_VAC_OFF_CHECK:
			if (Devs::m_InspectionStageMotion.Is_Inspect_Stage_Vac_Off())
			{
				SetStep(_eSTICK_RELEASE_UNCLAMP_FLOW_GRIPPER_Z_TENSION_POS, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_GRIPPER_Z_TENSION_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_RELEASE_UNCLAMP_FLOW_INSPECTION_STAGE_VAC_OFF_CHECK : Time Out"), eSTICK_RELEASE_UNCLAMP_FLOW + 3);
				SetStep(_eSTICK_RELEASE_UNCLAMP_FLOW_ERROR, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_RELEASE_UNCLAMP_FLOW_INSPECTION_STAGE_VAC_OFF_CHECK, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_INSPECTION_STAGE_VAC_OFF_CHECK"));
			}
			break;

		case _eSTICK_RELEASE_UNCLAMP_FLOW_GRIPPER_Z_TENSION_POS:
			Devs::m_GripperZMotion.Move_GripperLeftZ_TensionPos();
			Sleep(10);
			//Devs::m_GripperZMotion.Move_GripperRightZ_TensionPos();
			//Sleep(10);

			SetStep(_eSTICK_RELEASE_UNCLAMP_FLOW_GRIPPER_Z_TENSION_POS_CHECK, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_GRIPPER_Z_TENSION_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_RELEASE_UNCLAMP_FLOW_GRIPPER_Z_TENSION_POS_CHECK:
			if (Devs::m_GripperZMotion.Is_GripperLeftZ_TensionPos() && Devs::m_GripperZMotion.Is_GripperRightZ_TensionPos())
			{
				SetStep(_eSTICK_RELEASE_UNCLAMP_FLOW_STRETCH_SET_RELEASE_PARA, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_STRETCH_SET_RELEASE_PARA"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_RELEASE_UNCLAMP_FLOW_GRIPPER_Z_TENSION_POS_CHECK : Time Out"), eSTICK_RELEASE_UNCLAMP_FLOW + 4);
				SetStep(_eSTICK_RELEASE_UNCLAMP_FLOW_ERROR, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_RELEASE_UNCLAMP_FLOW_GRIPPER_Z_TENSION_POS_CHECK, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_GRIPPER_Z_TENSION_POS_CHECK"));
			}
			break;

		case _eSTICK_RELEASE_UNCLAMP_FLOW_STRETCH_SET_RELEASE_PARA:
			Devs::m_StretchMotion.SetReleaseStepValue();
			Sleep(1000); //!!
			Devs::m_StretchMotion.SendReleaseSetPara();
			Sleep(1000); //!!

			SetStep(_eSTICK_RELEASE_UNCLAMP_FLOW_STRETCH_RELEASE_START, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_STRETCH_RELEASE_START"));
			break;

		case _eSTICK_RELEASE_UNCLAMP_FLOW_STRETCH_RELEASE_START:
			Devs::m_StretchMotion.StretchStart(TRUE);

			SetStep(_eSTICK_RELEASE_UNCLAMP_FLOW_STRETCH_RELEASE_CHECK, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_STRETCH_RELEASE_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);

			break;

		case _eSTICK_RELEASE_UNCLAMP_FLOW_STRETCH_RELEASE_CHECK:
			if (Devs::m_StretchMotion.StretchFinish() == TRUE)
			{
				Devs::m_StretchMotion.StretchStop();
				Sleep(100);

				SetStep(_eSTICK_RELEASE_UNCLAMP_FLOW_GRIPPER_Z_CLAMP_POS, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_GRIPPER_Z_CLAMP_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_RELEASE_UNCLAMP_FLOW_STRETCH_RELEASE_CHECK : Time Out"), eSTICK_RELEASE_UNCLAMP_FLOW + 5);
				SetStep(_eSTICK_RELEASE_UNCLAMP_FLOW_ERROR, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_RELEASE_UNCLAMP_FLOW_STRETCH_RELEASE_CHECK, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_STRETCH_RELEASE_CHECK"));
			}
			break;

		case _eSTICK_RELEASE_UNCLAMP_FLOW_GRIPPER_Z_CLAMP_POS:
			Devs::m_GripperZMotion.Move_GripperLeftZ_ClampPos();
			Sleep(10);
			//Devs::m_GripperZMotion.Move_GripperRightZ_ClampPos();
			//Sleep(10);

			SetStep(_eSTICK_RELEASE_UNCLAMP_FLOW_GRIPPER_Z_CLAMP_POS_CHECK, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_GRIPPER_Z_CLAMP_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_RELEASE_UNCLAMP_FLOW_GRIPPER_Z_CLAMP_POS_CHECK:
			if (Devs::m_GripperZMotion.Is_GripperLeftZ_TensionPos() && Devs::m_GripperZMotion.Is_GripperRightZ_TensionPos())
			{
				SetStep(_eSTICK_RELEASE_UNCLAMP_FLOW_INSPECTION_STAGE_VAC_ON, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_INSPECTION_STAGE_VAC_ON"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_RELEASE_UNCLAMP_FLOW_GRIPPER_Z_CLAMP_POS_CHECK : Time Out"), eSTICK_RELEASE_UNCLAMP_FLOW + 6);
				SetStep(_eSTICK_RELEASE_UNCLAMP_FLOW_ERROR, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_RELEASE_UNCLAMP_FLOW_GRIPPER_Z_CLAMP_POS_CHECK, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_GRIPPER_Z_CLAMP_POS_CHECK"));
			}
			break;

		case _eSTICK_RELEASE_UNCLAMP_FLOW_INSPECTION_STAGE_VAC_ON:
			Devs::m_InspectionStageMotion.Inspect_Stage_Vac_On();
			Sleep(500); //!!

			SetStep(_eSTICK_RELEASE_UNCLAMP_FLOW_INSPECTION_STAGE_VAC_ON_CHECK, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_INSPECTION_STAGE_VAC_ON_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_RELEASE_UNCLAMP_FLOW_INSPECTION_STAGE_VAC_ON_CHECK:
			if (Devs::m_InspectionStageMotion.Is_Inspect_Stage_Vac_On())
			{
				Sleep(1000); //!!
				SetStep(_eSTICK_RELEASE_UNCLAMP_FLOW_GRIPPER_CLAMP_OFF, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_GRIPPER_CLAMP_OFF"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_RELEASE_UNCLAMP_FLOW_INSPECTION_STAGE_VAC_ON_CHECK : Time Out"), eSTICK_RELEASE_UNCLAMP_FLOW + 7);
				SetStep(_eSTICK_RELEASE_UNCLAMP_FLOW_ERROR, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_RELEASE_UNCLAMP_FLOW_INSPECTION_STAGE_VAC_ON_CHECK);
			}
			break;


		case _eSTICK_RELEASE_UNCLAMP_FLOW_GRIPPER_CLAMP_OFF:
			Devs::m_ClampMotion.ClampOff_All();

			SetStep(_eSTICK_RELEASE_UNCLAMP_FLOW_GRIPPER_CLAMP_OFF_CHECK, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_GRIPPER_CLAMP_OFF_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_RELEASE_UNCLAMP_FLOW_GRIPPER_CLAMP_OFF_CHECK:
			if (Devs::m_ClampMotion.Is_ClampOff_All())
			{
				SetStep(_eSTICK_RELEASE_UNCLAMP_FLOW_STRETCH_BWD_POS, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_STRETCH_BWD_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_RELEASE_UNCLAMP_FLOW_GRIPPER_CLAMP_OFF_CHECK : Time Out"), eSTICK_RELEASE_UNCLAMP_FLOW + 8);
				SetStep(_eSTICK_RELEASE_UNCLAMP_FLOW_ERROR, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_RELEASE_UNCLAMP_FLOW_GRIPPER_CLAMP_OFF_CHECK, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_GRIPPER_CLAMP_OFF_CHECK"));
			}
			break;

		case _eSTICK_RELEASE_UNCLAMP_FLOW_STRETCH_BWD_POS:
			Devs::m_StretchMotion.Stretch_BwdPos_All();
			Sleep(1000); //!!

			SetStep(_eSTICK_RELEASE_UNCLAMP_FLOW_STRETCH_BWD_POS_CHECK, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_STRETCH_BWD_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_RELEASE_UNCLAMP_FLOW_STRETCH_BWD_POS_CHECK:
			if (Devs::m_StretchMotion.Is_Stretch_BwdPos_All())
			{
				SetStep(_eSTICK_RELEASE_UNCLAMP_FLOW_DONE, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_RELEASE_UNCLAMP_FLOW_STRETCH_BWD_POS_CHECK : Time Out"), eSTICK_RELEASE_UNCLAMP_FLOW + 9);
				SetStep(_eSTICK_RELEASE_UNCLAMP_FLOW_ERROR, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_RELEASE_UNCLAMP_FLOW_STRETCH_BWD_POS_CHECK, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_STRETCH_BWD_POS_CHECK"));
			}
			break;

		case _eSTICK_RELEASE_UNCLAMP_FLOW_ERROR:
			break;

		case _eSTICK_RELEASE_UNCLAMP_FLOW_DONE:
		{
			m_bFlowDone = TRUE;

			SharedInfo::CalTactTime(_T("STICK_RELEASE_UNCLAMP_FLOW"), m_timeStart); //KJT 20210329

			SetStep(_eSTICK_RELEASE_UNCLAMP_FLOW_IDLE, _T("_eSTICK_RELEASE_UNCLAMP_FLOW_IDLE"));
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

BOOL CStickReleaseUnclampFlow::FlowInterlock()
{
	//if (Devs::m_CassetteMotion.Is_CSTPickUpUnitBwd() == FALSE)
	//{
	//	Total_Msg(_T("Check Pickup Unit Backward !!!"));
	//	return FALSE;
	//}
	//if (SharedInfo::DInputValue[_DIN_CST_UNSAFE_POS_DETECT] == TRUE)
	//{
	//	Total_Msg(_T("Check CST Unsafe Pos Detect Sensor !!!"));
	//	return FALSE;
	//}
	//if (SharedInfo::DInputValue[_DIN_CST_BACKWARD_DETECT] == TRUE)
	//{
	//	Total_Msg(_T("Check CST Backward Detect Sensor !!!"));
	//	return FALSE;
	//}

	//if (Devs::m_ClampMotion.Is_ClampOn_Active() != TRUE)
	//{
	//	Total_Msg(_T("Check Acitve Clamp On !!!"));
	//	return FALSE;
	//}

	return TRUE;
}