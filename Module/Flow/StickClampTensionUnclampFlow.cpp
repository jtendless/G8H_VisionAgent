#include "stdafx.h"
#include "StickClampTensionUnclampFlow.h"
#include "Log/Logger.h"
#include "Vision/Devs.h"
#include "Data/ModelData.h"
#include "Data/ManualData.h"
#include "CamAreaModul.h"
#include "Data/SystemData.h"
//#include "../WkLibFlow/WkLibFlow.h"
#include "Flow/BaseFlow.h"

CStickClampTensionUnclampFlow::CStickClampTensionUnclampFlow()
{
}


CStickClampTensionUnclampFlow::~CStickClampTensionUnclampFlow()
{
}

BOOL CStickClampTensionUnclampFlow::InitProcess()
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

BOOL CStickClampTensionUnclampFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_IDLE);

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

BOOL CStickClampTensionUnclampFlow::Start(int nStep)
{
	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(nStep, _T("_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_START"));
	return TRUE;
}
BOOL CStickClampTensionUnclampFlow::Stop()
{
	m_bStopBit = TRUE;
	SetStop(); //!!
	return TRUE;
}

UINT CStickClampTensionUnclampFlow::ThreadFunction(LPVOID lpParam)
{
	CStickClampTensionUnclampFlow* pFlow = NULL;

	pFlow = (CStickClampTensionUnclampFlow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}

VOID CStickClampTensionUnclampFlow::ThreadFunctionEntry(VOID)
{
	DWORD	dwResult = 0;
	double	dStrt_Time = GetTickCount();
	double	dEnd_Time = GetTickCount();
	double	dWait_Time = GetTickCount();
	int		nWork_Mask_Mode = -1;
	int		nWork_Mask_Index = -1;
	BOOL	bComplete_Step = FALSE;
	BOOL	bIsForceZero = FALSE;

	CString Str = _T("");

	while (m_FlowFinish)
	{
		WaitForSingleObject(hHandle, INFINITE);
		ResetEvent(hHandle);

		if (SharedInfo::bMachineStopFlag == TRUE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}

		switch (GetCurrentTotalStep())
		{
		case _eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_IDLE:
		{
			break;
		}
		case _eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_START:
		{
			m_timeStart = CTime::GetCurrentTime(); //KJT 20210329

			SetStep(_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_INTERLOCK, _T("_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_INTERLOCK"));
			break;
		}

		case _eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_INTERLOCK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_ERROR, _T("_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_ERROR"));
			}
			else
			{
				SetStep(_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_CLAMP_TENSION_START, _T("_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_CLAMP_TENSION_START"));
			}
			break;

		case _eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_CLAMP_TENSION_START:
			Devs::m_StickClampTensionFlow.Start(Devs::m_StickClampTensionFlow._eSTICK_CLAMP_TENSION_FLOW_START);

			SetStep(_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_CLAMP_TENSION_DONE_CHECK, _T("_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_CLAMP_TENSION_DONE_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_CLAMP_TENSION_DONE_CHECK:
			if (Devs::m_StickClampTensionFlow.IsFlowDone())
			{
				if (Devs::m_GripperZMotion.Is_GripperLeftZ_ClampPos() && Devs::m_GripperZMotion.Is_GripperRightZ_ClampPos())
					SetStep(_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_INSPECTION_STAGE_VAC_ON, _T("_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_INSPECTION_STAGE_VAC_ON"));
				else
					SetStep(_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_GRIPPER_Z_DOWN_CLAMP_POS, _T("_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_GRIPPER_Z_DOWN_CLAMP_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_CLAMP_TENSION_DONE_CHECK : Time Out"), eSTICK_CLAMP_TENSION_UNCLAMP_FLOW + 0);
				SetStep(_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_ERROR, _T("_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_CLAMP_TENSION_DONE_CHECK, _T("_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_CLAMP_TENSION_DONE_CHECK"));
			}
			break;

		case _eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_GRIPPER_Z_DOWN_CLAMP_POS:
			Devs::m_GripperZMotion.Move_GripperLeftZ_ClampPos();
			Sleep(10);
			Devs::m_GripperZMotion.Move_GripperRightZ_ClampPos();

			SetStep(_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_GRIPPER_Z_DOWN_CLAMP_POS_CHECK, _T("_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_GRIPPER_Z_DOWN_CLAMP_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_GRIPPER_Z_DOWN_CLAMP_POS_CHECK:
			if (Devs::m_GripperZMotion.Is_GripperLeftZ_ClampPos() && Devs::m_GripperZMotion.Is_GripperRightZ_ClampPos())
			{
				SetStep(_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_INSPECTION_STAGE_VAC_ON, _T("_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_INSPECTION_STAGE_VAC_ON"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_GRIPPER_Z_DOWN_CLAMP_POS_CHECK : Time Out"), eSTICK_CLAMP_TENSION_UNCLAMP_FLOW + 1);
				SetStep(_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_ERROR, _T("_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_GRIPPER_Z_DOWN_CLAMP_POS_CHECK, _T("_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_GRIPPER_Z_DOWN_CLAMP_POS_CHECK"));
			}
			break;

		case _eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_INSPECTION_STAGE_VAC_ON:
			Devs::m_InspectionStageMotion.Inspect_Stage_Vac_On();
			Sleep(1000); //!! //KJT 20210317

			SetStep(_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_INSPECTION_STAGE_VAC_ON_CHECK, _T("_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_INSPECTION_STAGE_VAC_ON_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_INSPECTION_STAGE_VAC_ON_CHECK:
			if (Devs::m_InspectionStageMotion.Is_Inspect_Stage_Vac_On())
			{
				Sleep(1000); //!! //KJT 20210317
				SetStep(_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_STRETCH_SET_RELEASE_PARA, _T("_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_STRETCH_SET_RELEASE_PARA"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_INSPECTION_STAGE_VAC_ON_CHECK : Time Out"), eSTICK_CLAMP_TENSION_UNCLAMP_FLOW + 2);
				SetStep(_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_ERROR, _T("_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_INSPECTION_STAGE_VAC_ON_CHECK, _T("_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_INSPECTION_STAGE_VAC_ON_CHECK"));
			}
			break;

		case _eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_STRETCH_SET_RELEASE_PARA:
			Devs::m_StretchMotion.SetReleaseStepValue();
			Sleep(1000); //!!
			Devs::m_StretchMotion.SendReleaseSetPara();
			Sleep(1000); //!!

			SetStep(_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_STRETCH_RELEASE_START, _T("_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_STRETCH_RELEASE_START"));
			break;

		case _eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_STRETCH_RELEASE_START:
			Devs::m_StretchMotion.StretchStart(TRUE);

			SetStep(_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_STRETCH_RELEASE_CHECK, _T("_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_STRETCH_RELEASE_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_STRETCH_RELEASE_CHECK:
			if (Devs::m_StretchMotion.StretchFinish() == TRUE)
			{
				Devs::m_StretchMotion.StretchStop();
				Sleep(100);

				SetStep(_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_GRIPPER_CLAMP_OFF, _T("_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_GRIPPER_CLAMP_OFF"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_STRETCH_RELEASE_CHECK : Time Out"), eSTICK_CLAMP_TENSION_UNCLAMP_FLOW + 3);
				SetStep(_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_ERROR, _T("_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_STRETCH_RELEASE_CHECK, _T("_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_STRETCH_RELEASE_CHECK"));
			}
			break;

		case _eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_GRIPPER_CLAMP_OFF:
			Devs::m_ClampMotion.ClampOff_All();

			SetStep(_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_GRIPPER_CLAMP_OFF_CHECK, _T("_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_GRIPPER_CLAMP_OFF_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_GRIPPER_CLAMP_OFF_CHECK:
			if (Devs::m_ClampMotion.Is_ClampOff_All())
			{
				SetStep(_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_STRETCH_BWD_POS, _T("_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_STRETCH_BWD_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_GRIPPER_CLAMP_OFF_CHECK : Time Out"), eSTICK_CLAMP_TENSION_UNCLAMP_FLOW + 4);
				SetStep(_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_ERROR, _T("_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_GRIPPER_CLAMP_OFF_CHECK, _T("_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_GRIPPER_CLAMP_OFF_CHECK"));
			}
			break;

		case _eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_STRETCH_BWD_POS:
			Devs::m_StretchMotion.Stretch_BwdPos_All();
			Sleep(1000); //!!

			SetStep(_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_STRETCH_BWD_POS_CHECK, _T("_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_STRETCH_BWD_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_STRETCH_BWD_POS_CHECK:
			if (Devs::m_StretchMotion.Is_Stretch_BwdPos_All())
			{
				SetStep(_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_DONE, _T("_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_STRETCH_BWD_POS_CHECK : Time Out"), eSTICK_CLAMP_TENSION_UNCLAMP_FLOW + 5);
				SetStep(_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_ERROR, _T("_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_STRETCH_BWD_POS_CHECK, _T("_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_STRETCH_BWD_POS_CHECK"));
			}
			break;

		case _eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_DONE:
		{
			m_bFlowDone = TRUE;

			SharedInfo::CalTactTime(_T("STICK_CLAMP_TENSION_UNCLAMP_FLOW"), m_timeStart); //KJT 20210329

			SetStep(_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_IDLE, _T("_eSTICK_CLAMP_TENSION_UNCLAMP_FLOW_IDLE"));
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

BOOL CStickClampTensionUnclampFlow::FlowInterlock()
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

	return TRUE;
}