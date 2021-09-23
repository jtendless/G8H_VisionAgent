#include "stdafx.h"
#include "StickClampTensionFlow.h"
#include "Log/Logger.h"
#include "Vision/Devs.h"
#include "Data/ModelData.h"
#include "Data/ManualData.h"
#include "CamAreaModul.h"
#include "Data/SystemData.h"
//#include "../WkLibFlow/WkLibFlow.h"
#include "Flow/BaseFlow.h"

CStickClampTensionFlow::CStickClampTensionFlow()
{
}


CStickClampTensionFlow::~CStickClampTensionFlow()
{
}

BOOL CStickClampTensionFlow::InitProcess()
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

BOOL CStickClampTensionFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eSTICK_CLAMP_TENSION_FLOW_IDLE);

	if (hHandle != NULL)
	{
		CloseHandle(hHandle);
		hHandle = NULL;
	}

	return TRUE;
}

BOOL CStickClampTensionFlow::Start(int nStep)
{
	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(nStep, _T("_eSTICK_CLAMP_TENSION_FLOW_START"));
	return TRUE;
}
BOOL CStickClampTensionFlow::Stop()
{
	m_bStopBit = TRUE;
	SetStop(); //!!
	return TRUE;
}

UINT CStickClampTensionFlow::ThreadFunction(LPVOID lpParam)
{
	CStickClampTensionFlow* pFlow = NULL;

	pFlow = (CStickClampTensionFlow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}

VOID CStickClampTensionFlow::ThreadFunctionEntry(VOID)
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

			SetCurrentStep(_eSTICK_CLAMP_TENSION_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}

		switch (GetCurrentTotalStep())
		{
		case _eSTICK_CLAMP_TENSION_FLOW_IDLE:
		{
			break;
		}
		case _eSTICK_CLAMP_TENSION_FLOW_START:
		{
			m_timeStart = CTime::GetCurrentTime(); //KJT 20210329

			SetStep(_eSTICK_CLAMP_TENSION_FLOW_INTERLOCK, _T("_eSTICK_CLAMP_TENSION_FLOW_INTERLOCK"));
			break;
		}

		case _eSTICK_CLAMP_TENSION_FLOW_INTERLOCK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(_eSTICK_CLAMP_TENSION_FLOW_ERROR, _T("_eSTICK_CLAMP_TENSION_FLOW_ERROR"));
			}
			else
			{
				if (SharedInfo::MachineState.bAutoRunFlag == TRUE && SharedInfo::nPrevFlowID == eMAIN_ALIGN_FLOW)
					SetStep(_eSTICK_CLAMP_TENSION_FLOW_GRIPPER_CLAMP_OFF, _T("_eSTICK_CLAMP_TENSION_FLOW_GRIPPER_CLAMP_OFF"));
				else
					SetStep(_eSTICK_CLAMP_TENSION_FLOW_UNLOADER_READY, _T("_eSTICK_CLAMP_TENSION_FLOW_UNLOADER_READY"));
			}
			break;

#pragma region //Unloader Ready
		case _eSTICK_CLAMP_TENSION_FLOW_UNLOADER_READY:
			Devs::m_Ready_UnloaderFlow.Start();

			SetStep(_eSTICK_CLAMP_TENSION_FLOW_UNLOADER_READY_CHECK, _T("_eSTICK_CLAMP_TENSION_FLOW_UNLOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_CLAMP_TENSION_FLOW_UNLOADER_READY_CHECK:
			if (Devs::m_Ready_UnloaderFlow.IsFlowDone())
			{
				SetStep(_eSTICK_CLAMP_TENSION_FLOW_GANTRY_ZX_READY, _T("_eSTICK_CLAMP_TENSION_FLOW_GANTRY_ZX_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_CLAMP_TENSION_FLOW_UNLOADER_READY_CHECK : Time Out"), eSTICK_CLAMP_TENSION_FLOW + 0);
				SetStep(_eSTICK_CLAMP_TENSION_FLOW_ERROR, _T("_eSTICK_CLAMP_TENSION_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_CLAMP_TENSION_FLOW_UNLOADER_READY_CHECK, _T("_eSTICK_CLAMP_TENSION_FLOW_UNLOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Gantry ZX Ready
		case _eSTICK_CLAMP_TENSION_FLOW_GANTRY_ZX_READY:
			Devs::m_Ready_GantryZX_Flow.Start();

			SetStep(_eSTICK_CLAMP_TENSION_FLOW_GANTRY_ZX_READY_CHECK, _T("_eSTICK_CLAMP_TENSION_FLOW_GANTRY_ZX_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_CLAMP_TENSION_FLOW_GANTRY_ZX_READY_CHECK:
			if (Devs::m_Ready_GantryZX_Flow.IsFlowDone())
			{
				SetStep(_eSTICK_CLAMP_TENSION_FLOW_LOADER_READY, _T("_eSTICK_CLAMP_TENSION_FLOW_LOADER_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_CLAMP_TENSION_FLOW_GANTRY_ZX_READY_CHECK : Time Out"), eSTICK_CLAMP_TENSION_FLOW + 2);
				SetStep(_eSTICK_CLAMP_TENSION_FLOW_ERROR, _T("_eSTICK_CLAMP_TENSION_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_CLAMP_TENSION_FLOW_GANTRY_ZX_READY_CHECK, _T("_eSTICK_CLAMP_TENSION_FLOW_GANTRY_ZX_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Loader Ready
		case _eSTICK_CLAMP_TENSION_FLOW_LOADER_READY:
			Devs::m_Ready_LoaderFlow.Start();

			SetStep(_eSTICK_CLAMP_TENSION_FLOW_LOADER_READY_CHECK, _T("_eSTICK_CLAMP_TENSION_FLOW_LOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_CLAMP_TENSION_FLOW_LOADER_READY_CHECK:
			if (Devs::m_Ready_LoaderFlow.IsFlowDone())
			{
				SetStep(_eSTICK_CLAMP_TENSION_FLOW_PAPER_UNLOADER_ZXY_READY, _T("_eSTICK_CLAMP_TENSION_FLOW_PAPER_UNLOADER_ZXY_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_CLAMP_TENSION_FLOW_LOADER_READY_CHECK : Time Out"), eSTICK_CLAMP_TENSION_FLOW + 1);
				SetStep(_eSTICK_CLAMP_TENSION_FLOW_ERROR, _T("_eSTICK_CLAMP_TENSION_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_CLAMP_TENSION_FLOW_LOADER_READY_CHECK, _T("_eSTICK_CLAMP_TENSION_FLOW_LOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //PaperUnloader Ready
		case _eSTICK_CLAMP_TENSION_FLOW_PAPER_UNLOADER_ZXY_READY:
			Devs::m_Ready_PaperUnloaderFlow.Start();

			SetStep(_eSTICK_CLAMP_TENSION_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK, _T("_eSTICK_CLAMP_TENSION_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_CLAMP_TENSION_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK:
			if (Devs::m_Ready_PaperUnloaderFlow.IsFlowDone())
			{
				SetStep(_eSTICK_CLAMP_TENSION_FLOW_GRIPPER_CLAMP_OFF, _T("_eSTICK_CLAMP_TENSION_FLOW_GRIPPER_CLAMP_OFF"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_CLAMP_TENSION_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK : Time Out"), eBOX_ALIGN_FLOW + 1);
				SetStep(_eSTICK_CLAMP_TENSION_FLOW_ERROR, _T("_eSTICK_CLAMP_TENSION_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_CLAMP_TENSION_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK, _T("_eSTICK_CLAMP_TENSION_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK"));
			}
			break;
#pragma endregion

		case _eSTICK_CLAMP_TENSION_FLOW_GRIPPER_CLAMP_OFF:
			Devs::m_ClampMotion.ClampOff_All();
			Sleep(30); //!!

			SetStep(_eSTICK_CLAMP_TENSION_FLOW_GRIPPER_CLAMP_OFF_CHECK, _T("_eSTICK_CLAMP_TENSION_FLOW_GRIPPER_CLAMP_OFF_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_CLAMP_TENSION_FLOW_GRIPPER_CLAMP_OFF_CHECK:
			if (Devs::m_ClampMotion.Is_ClampOff_All())
			{
				SetStep(_eSTICK_CLAMP_TENSION_FLOW_STRETCH_BWD_POS, _T("_eSTICK_CLAMP_TENSION_FLOW_STRETCH_BWD_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_CLAMP_TENSION_FLOW_GRIPPER_CLAMP_OFF_CHECK : Time Out"), eSTICK_CLAMP_TENSION_FLOW + 3);
				SetStep(_eSTICK_CLAMP_TENSION_FLOW_ERROR, _T("_eSTICK_CLAMP_TENSION_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_CLAMP_TENSION_FLOW_GRIPPER_CLAMP_OFF_CHECK);
			}
			break;

		case _eSTICK_CLAMP_TENSION_FLOW_STRETCH_BWD_POS:
			Devs::m_StretchMotion.Stretch_BwdPos_All();
			Sleep(3000); //!!

			SetStep(_eSTICK_CLAMP_TENSION_FLOW_STRETCH_BWD_POS_CHECK, _T("_eSTICK_CLAMP_TENSION_FLOW_STRETCH_BWD_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_CLAMP_TENSION_FLOW_STRETCH_BWD_POS_CHECK:
			if (Devs::m_StretchMotion.Is_Stretch_BwdPos_All())
			{
				//if (Devs::m_PitchMotion.Is_Pitch_ActiveWorkPos() == FALSE)
				//	SetStep(_eSTICK_CLAMP_TENSION_FLOW_PITCH_WORK_POS, _T("_eSTICK_CLAMP_TENSION_FLOW_PITCH_WORK_POS"));
				//else
					SetStep(_eSTICK_CLAMP_TENSION_FLOW_GRIPPER_Z_LOAD_POS, _T("_eSTICK_CLAMP_TENSION_FLOW_GRIPPER_Z_LOAD_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_CLAMP_TENSION_FLOW_STRETCH_BWD_POS_CHECK : Time Out"), eSTICK_CLAMP_TENSION_FLOW + 4);
				SetStep(_eSTICK_CLAMP_TENSION_FLOW_ERROR, _T("_eSTICK_CLAMP_TENSION_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_CLAMP_TENSION_FLOW_STRETCH_BWD_POS_CHECK, _T("_eSTICK_CLAMP_TENSION_FLOW_STRETCH_BWD_POS_CHECK"));
			}
			break;

		//case _eSTICK_CLAMP_TENSION_FLOW_PITCH_WORK_POS:
			//Devs::m_PitchWorkPosMoveFlow.Start(Devs::m_PitchWorkPosMoveFlow._ePITCH_WORK_POS_MOVE_FLOW_START);

			//SetStep(_eSTICK_CLAMP_TENSION_FLOW_PITCH_WORK_POS_CHECK, _T("_eSTICK_CLAMP_TENSION_FLOW_PITCH_WORK_POS_CHECK"));
			//SetTimeOut(TIME_OUT_MOTION);
		//	break;

		//case _eSTICK_CLAMP_TENSION_FLOW_PITCH_WORK_POS_CHECK:
			//if (Devs::m_PitchWorkPosMoveFlow.IsFlowDone() == TRUE)
			//{
			//	SetStep(_eSTICK_CLAMP_TENSION_FLOW_GRIPPER_Z_LOAD_POS, _T("_eSTICK_CLAMP_TENSION_FLOW_GRIPPER_Z_LOAD_POS"));
			//}
			//else if (IsTimeOut())
			//{
			//	SetStep(_eSTICK_CLAMP_TENSION_FLOW_ERROR, _T("_eSTICK_CLAMP_TENSION_FLOW_ERROR"));
			//}
			//else
			//{
			//	SetCheckStep(_eSTICK_CLAMP_TENSION_FLOW_PITCH_WORK_POS_CHECK, _T("_eSTICK_CLAMP_TENSION_FLOW_PITCH_WORK_POS_CHECK"));
			//}
		//	break;

		case _eSTICK_CLAMP_TENSION_FLOW_GRIPPER_Z_LOAD_POS:
			Devs::m_GripperZMotion.Move_GripperLeftZ_LoadingPos();
			Sleep(10); //!!
			//Devs::m_GripperZMotion.Move_GripperRightZ_LoadingPos();

			SetStep(_eSTICK_CLAMP_TENSION_FLOW_GRIPPER_Z_LOAD_POS_CHECK, _T("_eSTICK_CLAMP_TENSION_FLOW_GRIPPER_Z_LOAD_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_CLAMP_TENSION_FLOW_GRIPPER_Z_LOAD_POS_CHECK:
			if (Devs::m_GripperZMotion.Is_GripperLeftZ_LoadingPos() && Devs::m_GripperZMotion.Is_GripperRightZ_LoadingPos())
			{
				SetStep(_eSTICK_CLAMP_TENSION_FLOW_STRETCH_FWD_POS, _T("_eSTICK_CLAMP_TENSION_FLOW_STRETCH_FWD_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_CLAMP_TENSION_FLOW_GRIPPER_Z_LOAD_POS_CHECK : Time Out"), eSTICK_CLAMP_TENSION_FLOW + 5);
				SetStep(_eSTICK_CLAMP_TENSION_FLOW_ERROR, _T("_eSTICK_CLAMP_TENSION_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_CLAMP_TENSION_FLOW_GRIPPER_Z_LOAD_POS_CHECK);
			}
			break;

		case _eSTICK_CLAMP_TENSION_FLOW_STRETCH_FWD_POS:
			Devs::m_StretchMotion.Stretch_FwdPos_Active();
			Sleep(3000); //!!

			SetStep(_eSTICK_CLAMP_TENSION_FLOW_STRETCH_FWD_POS_CHECK, _T("_eSTICK_CLAMP_TENSION_FLOW_STRETCH_FWD_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_CLAMP_TENSION_FLOW_STRETCH_FWD_POS_CHECK:
			if (Devs::m_StretchMotion.Is_Stretch_FwdPos_Active())
			{
				SetStep(_eSTICK_CLAMP_TENSION_FLOW_GRIPPER_Z_UP_CLAMP_POS, _T("_eSTICK_CLAMP_TENSION_FLOW_GRIPPER_Z_UP_CLAMP_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_CLAMP_TENSION_FLOW_STRETCH_FWD_POS_CHECK : Time Out"), eSTICK_CLAMP_TENSION_FLOW + 6);
				SetStep(_eSTICK_CLAMP_TENSION_FLOW_ERROR, _T("_eSTICK_CLAMP_TENSION_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_CLAMP_TENSION_FLOW_STRETCH_FWD_POS_CHECK);
			}
			break;

		case _eSTICK_CLAMP_TENSION_FLOW_GRIPPER_Z_UP_CLAMP_POS:
			Devs::m_GripperZMotion.Move_GripperLeftZ_ClampPos();
			Sleep(10); //!!
			//Devs::m_GripperZMotion.Move_GripperRightZ_ClampPos();

			SetStep(_eSTICK_CLAMP_TENSION_FLOW_GRIPPER_Z_UP_CLAMP_POS_CHECK, _T("_eSTICK_CLAMP_TENSION_FLOW_GRIPPER_Z_UP_CLAMP_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_CLAMP_TENSION_FLOW_GRIPPER_Z_UP_CLAMP_POS_CHECK:
			if (Devs::m_GripperZMotion.Is_GripperLeftZ_ClampPos() && Devs::m_GripperZMotion.Is_GripperRightZ_ClampPos())
			{
				SetStep(_eSTICK_CLAMP_TENSION_FLOW_GRIPPER_CLAMP_ON, _T("_eSTICK_CLAMP_TENSION_FLOW_GRIPPER_CLAMP_ON"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_CLAMP_TENSION_FLOW_GRIPPER_Z_UP_CLAMP_POS_CHECK : Time Out"), eSTICK_CLAMP_TENSION_FLOW + 7);
				SetStep(_eSTICK_CLAMP_TENSION_FLOW_ERROR, _T("_eSTICK_CLAMP_TENSION_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_CLAMP_TENSION_FLOW_GRIPPER_Z_UP_CLAMP_POS_CHECK);
			}
			break;

		case _eSTICK_CLAMP_TENSION_FLOW_GRIPPER_CLAMP_ON:
			Devs::m_ClampMotion.ClampOn_Active();
			Sleep(30); //!!

			SetStep(_eSTICK_CLAMP_TENSION_FLOW_GRIPPER_CLAMP_ON_CHECK, _T("_eSTICK_CLAMP_TENSION_FLOW_GRIPPER_CLAMP_ON_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_CLAMP_TENSION_FLOW_GRIPPER_CLAMP_ON_CHECK:
			if (Devs::m_ClampMotion.Is_ClampOn_Active())
			{
				SetStep(_eSTICK_CLAMP_TENSION_FLOW_INSPECTION_STAGE_VAC_OFF, _T("_eSTICK_CLAMP_TENSION_FLOW_INSPECTION_STAGE_VAC_OFF"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_CLAMP_TENSION_FLOW_GRIPPER_CLAMP_ON_CHECK : Time Out"), eSTICK_CLAMP_TENSION_FLOW + 8);
				SetStep(_eSTICK_CLAMP_TENSION_FLOW_ERROR, _T("_eSTICK_CLAMP_TENSION_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_CLAMP_TENSION_FLOW_GRIPPER_CLAMP_ON_CHECK);
			}
			break;

		case _eSTICK_CLAMP_TENSION_FLOW_INSPECTION_STAGE_VAC_OFF:
			Devs::m_InspectionStageMotion.Inspect_Stage_Vac_Off();
			Sleep(1000); //!!

			SetStep(_eSTICK_CLAMP_TENSION_FLOW_INSPECTION_STAGE_VAC_OFF_CHECK, _T("_eSTICK_CLAMP_TENSION_FLOW_INSPECTION_STAGE_VAC_OFF_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_CLAMP_TENSION_FLOW_INSPECTION_STAGE_VAC_OFF_CHECK:
			if (Devs::m_InspectionStageMotion.Is_Inspect_Stage_Vac_Off())
			{
				SetStep(_eSTICK_CLAMP_TENSION_FLOW_GRIPPER_Z_TENSION_POS, _T("_eSTICK_CLAMP_TENSION_FLOW_GRIPPER_Z_TENSION_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_CLAMP_TENSION_FLOW_INSPECTION_STAGE_VAC_OFF_CHECK : Time Out"), eSTICK_CLAMP_TENSION_FLOW + 9);
				SetStep(_eSTICK_CLAMP_TENSION_FLOW_ERROR, _T("_eSTICK_CLAMP_TENSION_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_CLAMP_TENSION_FLOW_INSPECTION_STAGE_VAC_OFF_CHECK);
			}
			break;

		case _eSTICK_CLAMP_TENSION_FLOW_GRIPPER_Z_TENSION_POS:
			Devs::m_GripperZMotion.Move_GripperLeftZ_TensionPos();
			Sleep(10); //!!
			//Devs::m_GripperZMotion.Move_GripperRightZ_TensionPos();

			SetStep(_eSTICK_CLAMP_TENSION_FLOW_GRIPPER_Z_TENSION_POS_CHECK, _T("_eSTICK_CLAMP_TENSION_FLOW_GRIPPER_Z_TENSION_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_CLAMP_TENSION_FLOW_GRIPPER_Z_TENSION_POS_CHECK:
			if (Devs::m_GripperZMotion.Is_GripperLeftZ_TensionPos() && Devs::m_GripperZMotion.Is_GripperRightZ_TensionPos())
			{
				SetStep(_eSTICK_CLAMP_TENSION_FLOW_STRETCH_FORCE_ZERO, _T("_eSTICK_CLAMP_TENSION_FLOW_STRETCH_FORCE_ZERO"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_CLAMP_TENSION_FLOW_GRIPPER_Z_TENSION_POS_CHECK : Time Out"), eSTICK_CLAMP_TENSION_FLOW + 10);
				SetStep(_eSTICK_CLAMP_TENSION_FLOW_ERROR, _T("_eSTICK_CLAMP_TENSION_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_CLAMP_TENSION_FLOW_GRIPPER_Z_TENSION_POS_CHECK);
			}
			break;

		case _eSTICK_CLAMP_TENSION_FLOW_STRETCH_FORCE_ZERO:
			for (int k = 0; k < 3; k++)
			{
				for (int i = 0; i < eGRIPPER_ROW_MAX; i++)
				{
					if (CModelData::m_StretchPara.Info.bStretchUse[i])
					{
						Devs::MotionIf.StretchForceZero(i);
						Sleep(3000); //!!

						Str.Format(_T("StretchForceZero(Retry:%d/3) L%d, R%d"), k + 1, i + 1, i + 1);
					}
				}
				Sleep(1000); //!!
			}

			SetStep(_eSTICK_CLAMP_TENSION_FLOW_STRETCH_FORCE_ZERO_CHECK, _T("_eSTICK_CLAMP_TENSION_FLOW_STRETCH_FORCE_ZERO_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_CLAMP_TENSION_FLOW_STRETCH_FORCE_ZERO_CHECK:
			bIsForceZero = TRUE;
			for (int i = 0; i < eGRIPPER_ROW_MAX; i++)
			{
				if (CModelData::m_StretchPara.Info.bStretchUse[i])
				{
					if (fabs(SharedInfo::dSF_LoadcellForce[i]) > 0.05 || fabs(SharedInfo::dSF_LoadcellForce[eGRIPPER_ROW_MAX + i]) > 0.05)
					{
						bIsForceZero = FALSE;
						break;
					}
				}
			}
			if (bIsForceZero)
			{
				Sleep(1000);
				SetStep(_eSTICK_CLAMP_TENSION_FLOW_STRETCH_SET_PARA, _T("_eSTICK_CLAMP_TENSION_FLOW_STRETCH_SET_PARA"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_CLAMP_TENSION_FLOW_STRETCH_FORCE_ZERO_CHECK : Time Out"), eSTICK_CLAMP_TENSION_FLOW + 11);
				SetStep(_eSTICK_CLAMP_TENSION_FLOW_ERROR, _T("_eSTICK_CLAMP_TENSION_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_CLAMP_TENSION_FLOW_STRETCH_FORCE_ZERO_CHECK, _T("_eSTICK_CLAMP_TENSION_FLOW_STRETCH_FORCE_ZERO_CHECK"));
			}
			break;

		case _eSTICK_CLAMP_TENSION_FLOW_STRETCH_SET_PARA:
			Devs::m_StretchMotion.StretchSetStepValue(CModelData::m_StretchPara.Info.nStepCount, CModelData::m_StretchPara.Info.dStretchNewton);
			Sleep(1000); //!!
			Devs::m_StretchMotion.SendStretchSetPara();
			Sleep(1000); //!!

			SetCheckStep(_eSTICK_CLAMP_TENSION_FLOW_STRETCH_TENSION_START, _T("_eSTICK_CLAMP_TENSION_FLOW_STRETCH_TENSION_START"));
			break;

		case _eSTICK_CLAMP_TENSION_FLOW_STRETCH_TENSION_START:
			Devs::m_StretchMotion.StretchStart();
			
			SetStep(_eSTICK_CLAMP_TENSION_FLOW_STRETCH_TENSION_CHECK, _T("_eSTICK_CLAMP_TENSION_FLOW_STRETCH_TENSION_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_CLAMP_TENSION_FLOW_STRETCH_TENSION_CHECK:
			if (Devs::m_StretchMotion.StretchFinish() == TRUE)
			{
				Devs::m_StretchMotion.StretchStop();
				Sleep(100);

				SetStep(_eSTICK_CLAMP_TENSION_FLOW_GRIPPER_Z_DOWN_CLAMP_POS, _T("_eSTICK_CLAMP_TENSION_FLOW_GRIPPER_Z_DOWN_CLAMP_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_CLAMP_TENSION_FLOW_STRETCH_TENSION_CHECK : Time Out"), eSTICK_CLAMP_TENSION_FLOW + 12);
				SetStep(_eSTICK_CLAMP_TENSION_FLOW_ERROR, _T("_eSTICK_CLAMP_TENSION_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_CLAMP_TENSION_FLOW_STRETCH_TENSION_CHECK, _T("_eSTICK_CLAMP_TENSION_FLOW_STRETCH_TENSION_CHECK"));
			}
			break;

		case _eSTICK_CLAMP_TENSION_FLOW_GRIPPER_Z_DOWN_CLAMP_POS:
			Devs::m_GripperZMotion.Move_GripperLeftZ_ClampPos();
			Sleep(10);
			//Devs::m_GripperZMotion.Move_GripperRightZ_ClampPos();

			SetStep(_eSTICK_CLAMP_TENSION_FLOW_GRIPPER_Z_DOWN_CLAMP_POS_CHECK, _T("_eSTICK_CLAMP_TENSION_FLOW_GRIPPER_Z_DOWN_CLAMP_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSTICK_CLAMP_TENSION_FLOW_GRIPPER_Z_DOWN_CLAMP_POS_CHECK:
			if (Devs::m_GripperZMotion.Is_GripperLeftZ_ClampPos() && Devs::m_GripperZMotion.Is_GripperRightZ_ClampPos())
			{
				SetStep(_eSTICK_CLAMP_TENSION_FLOW_DONE, _T("_eSTICK_CLAMP_TENSION_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSTICK_CLAMP_TENSION_FLOW_GRIPPER_Z_DOWN_CLAMP_POS_CHECK : Time Out"), eSTICK_CLAMP_TENSION_FLOW + 13);
				SetStep(_eSTICK_CLAMP_TENSION_FLOW_ERROR, _T("_eSTICK_CLAMP_TENSION_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSTICK_CLAMP_TENSION_FLOW_GRIPPER_Z_DOWN_CLAMP_POS_CHECK);
			}
			break;

		case _eSTICK_CLAMP_TENSION_FLOW_ERROR:
			break;

		case _eSTICK_CLAMP_TENSION_FLOW_DONE:
		{
			m_bFlowDone = TRUE;

			SharedInfo::CalTactTime(_T("STICK_CLAMP_TENSION_FLOW"), m_timeStart); //KJT 20210329

			SetStep(_eSTICK_CLAMP_TENSION_FLOW_IDLE, _T("_eSTICK_CLAMP_TENSION_FLOW_IDLE"));
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

BOOL CStickClampTensionFlow::FlowInterlock()
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