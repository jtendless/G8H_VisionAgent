#include "stdafx.h"
#include "ReadyFlow.h"
#include "Log/Logger.h"
#include "Vision/Devs.h"
#include "Data/ModelData.h"
#include "CamAreaModul.h"
#include "Data/SystemData.h"
#include "VisionAgentDlg.h"

CReadyFlow::CReadyFlow()
{
}


CReadyFlow::~CReadyFlow()
{
}

BOOL CReadyFlow::InitProcess()
{
	m_StateComplete = NULL;
	m_FlowFinish = TRUE;
	m_bTerminate = FALSE;
	m_bFlowDone = TRUE;

	//SetProcessLog(Process_Msg);
	//SetAlarmLog(LogMsg_Alarm);

	hHandle = CreateEvent(NULL, TRUE, FALSE, NULL);
	SetHandle(hHandle);
	pThread = AfxBeginThread(ThreadFunction, this);
	return TRUE;
}
BOOL CReadyFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eREADY_FLOW_IDLE);

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
BOOL CReadyFlow::Start()
{
	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(_eREADY_FLOW_START, _T("_eREADY_FLOW_START"));
	return TRUE;
}
BOOL CReadyFlow::Stop()
{
	m_bStopBit = TRUE;
	SetStop(); //!!
	return TRUE;
}
UINT CReadyFlow::ThreadFunction(LPVOID lpParam)
{
	CReadyFlow* pFlow = NULL;

	pFlow = (CReadyFlow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}
VOID CReadyFlow::ThreadFunctionEntry(VOID)
{
	DWORD	dwResult = 0;
	double	dStrt_Time = GetTickCount();
	double	dEnd_Time = GetTickCount();
	double	dWait_Time = GetTickCount();
	int		nWork_Mask_Mode = -1;
	int		nWork_Mask_Index = -1;
	BOOL	bComplete_Step = FALSE;
	CVisionAgentDlg *pMain = (CVisionAgentDlg*)AfxGetMainWnd();
	CString Str = _T(""), StrAxisName = _T("");

	while (m_FlowFinish)
	{
		WaitForSingleObject(hHandle, INFINITE);
		ResetEvent(hHandle);

		if (SharedInfo::bMachineStopFlag == TRUE && m_bStopBit == FALSE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(_eREADY_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}

	
		switch (GetCurrentTotalStep())
		{
		case _eREADY_FLOW_IDLE:
		{
			break;
		}
		case _eREADY_FLOW_START:
		{
			SetStep(_eREADY_FLOW_INTERLOCK_CHECK, _T("_eREADY_FLOW_INTERLOCK_CHECK"));
			break;
		}
#pragma region //All Ready
		case _eREADY_FLOW_INTERLOCK_CHECK:
			if (SharedInfo::CheckAllAxisServoOn(&StrAxisName) == FALSE)
			{
				Str.Format(_T("%s Check Servo On !!!"), StrAxisName);
				Total_Msg(Str);
				SetStep(_eREADY_FLOW_ERROR, _T("_eREADY_FLOW_ERROR"));
			}
			else if (SharedInfo::CheckAllAxisHomeStatus(&StrAxisName) == FALSE)
			{
				Str.Format(_T("%s Check Home Status !!!"), StrAxisName);
				Total_Msg(Str);
				SetStep(_eREADY_FLOW_ERROR, _T("_eREADY_FLOW_ERROR"));
			}
			else
			{
				SetStep(_eREADY_FLOW_BOX_ALIGN_CAMERA_Y_WAIT_POS, _T("_eREADY_FLOW_BOX_ALIGN_CAMERA_Y_WAIT_POS"));
			}
			break;

		case _eREADY_FLOW_BOX_ALIGN_CAMERA_Y_WAIT_POS:
			Devs::m_BoxMotion.BoxAlignCameraYL_WaitPos();
			Sleep(20);
			Devs::m_BoxMotion.BoxAlignCameraYR_WaitPos();

			SetStep(_eREADY_FLOW_BOX_ALIGN_CAMERA_Y_WAIT_POS_CHECK, _T("_eREADY_FLOW_BOX_ALIGN_CAMERA_Y_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eREADY_FLOW_BOX_ALIGN_CAMERA_Y_WAIT_POS_CHECK:
			if (Devs::m_BoxMotion.Is_BoxAlignCameraYL_WaitPos() && Devs::m_BoxMotion.Is_BoxAlignCameraYR_WaitPos())
			{
				SetStep(_eREADY_FLOW_UNLOADER_VAC_OFF, _T("_eREADY_FLOW_UNLOADER_VAC_OFF"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eREADY_FLOW_ERROR, _T("_eREADY_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eREADY_FLOW_BOX_ALIGN_CAMERA_Y_WAIT_POS_CHECK);
			}
			break;

		case _eREADY_FLOW_UNLOADER_VAC_OFF:
			Devs::m_UnloaderMotion.Stick_All_Vac_Off();

			SetStep(_eREADY_FLOW_UNLOADER_VAC_OFF_CHECK, _T("_eREADY_FLOW_UNLOADER_VAC_OFF_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eREADY_FLOW_UNLOADER_VAC_OFF_CHECK:
			if (Devs::m_UnloaderMotion.Is_Stick_All_Vac_Off())
			{
				SetStep(_eREADY_FLOW_UNLOADER_Z_UP, _T("_eREADY_FLOW_UNLOADER_Z_UP"));
			}
			else if (IsTimeOut())
			{
				Total_Msg(_T("Unloader Vac Off Check !!"));
				SetStep(_eREADY_FLOW_ERROR, _T("_eREADY_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eREADY_FLOW_UNLOADER_VAC_OFF_CHECK);
			}
			break;

		case _eREADY_FLOW_UNLOADER_Z_UP:
			Devs::m_UnloaderMotion.UnloaderZ_WaitPos();

			SetStep(_eREADY_FLOW_UNLOADER_Z_UP_CHECK, _T("_eREADY_FLOW_UNLOADER_Z_UP_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eREADY_FLOW_UNLOADER_Z_UP_CHECK:
			if (Devs::m_UnloaderMotion.Is_UnloaderZ_WaitPos())
			{
				SetStep(_eREADY_FLOW_UNLOADER_Y_WAIT_POS, _T("_eREADY_FLOW_UNLOADER_Y_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				Total_Msg(_T("Unloader Z Up Pos Check !!"));
				SetStep(_eREADY_FLOW_ERROR, _T("_eREADY_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eREADY_FLOW_UNLOADER_Z_UP_CHECK);
			}
			break;

		case _eREADY_FLOW_UNLOADER_Y_WAIT_POS:
			Devs::m_UnloaderMotion.UnloaderY_WaitPos();

			SetStep(_eREADY_FLOW_UNLOADER_Y_WAIT_POS_CHECK, _T("_eREADY_FLOW_UNLOADER_Y_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eREADY_FLOW_UNLOADER_Y_WAIT_POS_CHECK:
			if (Devs::m_UnloaderMotion.Is_UnloaderY_WaitPos())
			{
				SetStep(_eREADY_FLOW_LOADER_VAC_OFF, _T("_eREADY_FLOW_LOADER_VAC_OFF"));
			}
			else if (IsTimeOut())
			{
				Total_Msg(_T("Unloader Y Wait Pos Check !!"));
				SetStep(_eREADY_FLOW_ERROR, _T("_eREADY_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eREADY_FLOW_UNLOADER_Y_WAIT_POS_CHECK);
			}
			break;

		case _eREADY_FLOW_LOADER_VAC_OFF:
			Devs::m_LoaderMotion.Stick_All_Vac_Off();
			Devs::m_LoaderMotion.Paper_All_Vac_Off();

			SetStep(_eREADY_FLOW_LOADER_VAC_OFF_CHECK, _T("_eREADY_FLOW_LOADER_VAC_OFF_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eREADY_FLOW_LOADER_VAC_OFF_CHECK:
			if (Devs::m_LoaderMotion.Is_Stick_All_Vac_Off()/* && Devs::m_LoaderMotion.Is_Paper_All_Vac_Off()*/)
			{
				SetStep(_eREADY_FLOW_LOADER_BLOW_ON, _T("_eREADY_FLOW_LOADER_BLOW_ON"));
			}
			else if (IsTimeOut())
			{
				Total_Msg(_T("Loader Vac Off Check !!"));
				SetStep(_eREADY_FLOW_ERROR, _T("_eREADY_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eREADY_FLOW_LOADER_VAC_OFF_CHECK);
			}
			break;

		case _eREADY_FLOW_LOADER_BLOW_ON:
			Devs::m_LoaderMotion.Stick_Blow_On();
			Sleep(10);
			Devs::m_LoaderMotion.Paper_Blow_On();

			SetStep(_eREADY_FLOW_LOADER_BLOW_ON_CHECK, _T("_eREADY_FLOW_LOADER_BLOW_ON_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eREADY_FLOW_LOADER_BLOW_ON_CHECK:
			if (Devs::m_LoaderMotion.Is_Stick_Blow_On() && Devs::m_LoaderMotion.Is_Paper_Blow_On())
			{
				Sleep(1000); //!!

				SetStep(_eREADY_FLOW_LOADER_BLOW_OFF, _T("_eREADY_FLOW_LOADER_BLOW_OFF"));
			}
			else if (IsTimeOut())
			{
				Total_Msg(_T("Loader Blow On Check !!"));
				SetStep(_eREADY_FLOW_ERROR, _T("_eREADY_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eREADY_FLOW_LOADER_BLOW_ON_CHECK);
			}
			break;

		case _eREADY_FLOW_LOADER_BLOW_OFF:
			Devs::m_LoaderMotion.Stick_Blow_Off();
			Sleep(10);
			Devs::m_LoaderMotion.Paper_Blow_Off();

			SetStep(_eREADY_FLOW_LOADER_BLOW_OFF_CHECK, _T("_eREADY_FLOW_LOADER_BLOW_OFF_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eREADY_FLOW_LOADER_BLOW_OFF_CHECK:
			if (Devs::m_LoaderMotion.Is_Stick_Blow_Off() && Devs::m_LoaderMotion.Is_Paper_Blow_Off())
			{
				SetStep(_eREADY_FLOW_LOADER_CYLINDER_UP, _T("_eREADY_FLOW_LOADER_CYLINDER_UP"));
			}
			else if (IsTimeOut())
			{
				Total_Msg(_T("Loader Blow Off Check !!"));
				SetStep(_eREADY_FLOW_ERROR, _T("_eREADY_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eREADY_FLOW_LOADER_BLOW_OFF_CHECK);
			}
			break;

		case _eREADY_FLOW_LOADER_CYLINDER_UP:
			Devs::m_LoaderMotion.Cylinder_Up();

			SetStep(_eREADY_FLOW_LOADER_CYLINDER_UP_CHECK, _T("_eREADY_FLOW_LOADER_CYLINDER_UP_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eREADY_FLOW_LOADER_CYLINDER_UP_CHECK:
			if (Devs::m_LoaderMotion.Cylinder_Up())
			{
				SetStep(_eREADY_FLOW_LOADER_Z_UP, _T("_eREADY_FLOW_LOADER_Z_UP"));
			}
			else if (IsTimeOut())
			{
				Total_Msg(_T("Loader Cylinder Up Check !!"));
				SetStep(_eREADY_FLOW_ERROR, _T("_eREADY_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eREADY_FLOW_LOADER_CYLINDER_UP_CHECK);
			}
			break;

		case _eREADY_FLOW_LOADER_Z_UP:
			Devs::m_LoaderMotion.Is_LoaderZ_WaitPos();

			SetStep(_eREADY_FLOW_LOADER_Z_UP_CHECK, _T("_eREADY_FLOW_LOADER_Z_UP_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eREADY_FLOW_LOADER_Z_UP_CHECK:
			if (Devs::m_LoaderMotion.Is_LoaderZ_WaitPos())
			{
				SetStep(_eREADY_FLOW_GANTRY_Z_ALL_WAIT_POS, _T("_eREADY_FLOW_GANTRY_Z_ALL_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				Total_Msg(_T("Loader Z Up Pos Check !!"));
				SetStep(_eREADY_FLOW_ERROR, _T("_eREADY_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eREADY_FLOW_LOADER_Z_UP_CHECK);
			}
			break;

		case _eREADY_FLOW_GANTRY_Z_ALL_WAIT_POS:
			Devs::m_GantryMotion.Move_GantryZ_All_Wait_Pos();

			SetStep(_eREADY_FLOW_GANTRY_Z_ALL_WAIT_POS_CHECK, _T("_eREADY_FLOW_GANTRY_Z_ALL_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eREADY_FLOW_GANTRY_Z_ALL_WAIT_POS_CHECK:
			if (Devs::m_GantryMotion.Is_GantryZ_All_Wait_Pos())
			{
				SetStep(_eREADY_FLOW_GANTRY_XY_WAIT_POS, _T("_eREADY_FLOW_GANTRY_XY_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eREADY_FLOW_ERROR, _T("_eREADY_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eREADY_FLOW_GANTRY_Z_ALL_WAIT_POS_CHECK);
			}
			break;

		case _eREADY_FLOW_GANTRY_XY_WAIT_POS:
			Devs::m_GantryMotion.Move_Gantry_X_Wait_Pos();
			Sleep(20); //!!
			Devs::m_GantryMotion.Move_Gantry_Y_Wait_Pos();
			Sleep(20); //!!

			SetStep(_eREADY_FLOW_GANTRY_XY_WAIT_POS_CHECK, _T("_eREADY_FLOW_GANTRY_XY_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eREADY_FLOW_GANTRY_XY_WAIT_POS_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Wait_Pos() && Devs::m_GantryMotion.Is_Gantry_Y_Wait_Pos())
			{
			}
			else if (IsTimeOut())
			{
				SetStep(_eREADY_FLOW_ERROR, _T("_eREADY_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eREADY_FLOW_GANTRY_XY_WAIT_POS_CHECK);
			}
			break;

		case _eREADY_FLOW_GRIPPER_CLAMP_OFF:
			Devs::m_ClampMotion.ClampOff_All();

			SetStep(_eREADY_FLOW_GRIPPER_CLAMP_OFF_CHECK, _T("_eREADY_FLOW_GRIPPER_CLAMP_OFF_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eREADY_FLOW_GRIPPER_CLAMP_OFF_CHECK:
			if (Devs::m_ClampMotion.ClampOff_All())
			{
				SetStep(_eREADY_FLOW_GRIPPER_Z_WAIT_POS, _T("_eREADY_FLOW_GRIPPER_Z_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eREADY_FLOW_ERROR, _T("_eREADY_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eREADY_FLOW_GRIPPER_CLAMP_OFF_CHECK, _T("_eREADY_FLOW_GRIPPER_CLAMP_OFF_CHECK"));
			}
			break;

		case _eREADY_FLOW_GRIPPER_Z_WAIT_POS:
			Devs::m_GripperZMotion.Move_GripperLeftZ_WaitPos();
			Sleep(100); //!!
			
			SetStep(_eREADY_FLOW_GRIPPER_Z_WAIT_POS_CHECK, _T("_eREADY_FLOW_GRIPPER_Z_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eREADY_FLOW_GRIPPER_Z_WAIT_POS_CHECK:
			if (Devs::m_GripperZMotion.Is_GripperLeftZ_WaitPos())
			{
				SetStep(_eREADY_FLOW_GRIPPER_STRETCH_WAIT_POS, _T("_eREADY_FLOW_GRIPPER_STRETCH_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eREADY_FLOW_ERROR, _T("_eREADY_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eREADY_FLOW_GRIPPER_Z_WAIT_POS_CHECK, _T("_eREADY_FLOW_GRIPPER_Z_WAIT_POS_CHECK"));
			}
			break;

		case _eREADY_FLOW_GRIPPER_STRETCH_WAIT_POS:
			Devs::m_StretchMotion.Stretch_WaitPos_All();

			SetStep(_eREADY_FLOW_GRIPPER_STRETCH_WAIT_POS_CHECK, _T("_eREADY_FLOW_GRIPPER_STRETCH_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eREADY_FLOW_GRIPPER_STRETCH_WAIT_POS_CHECK:
			if (Devs::m_StretchMotion.Is_Stretch_WaitPos_All())
			{
				SetStep(_eREADY_FLOW_GRIPPER_PITCH_WAIT_POS, _T("_eREADY_FLOW_GRIPPER_PITCH_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eREADY_FLOW_ERROR, _T("_eREADY_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eREADY_FLOW_GRIPPER_STRETCH_WAIT_POS_CHECK, _T("_eREADY_FLOW_GRIPPER_STRETCH_WAIT_POS_CHECK"));
			}
			break;

		case _eREADY_FLOW_GRIPPER_PITCH_WAIT_POS:
			//21.02.04 sjc no pitch servo
			//Devs::m_PitchMotion.Pitch_WaitPos_All();

			SetStep(_eREADY_FLOW_GRIPPER_PITCH_WAIT_POS_CHECK, _T("_eREADY_FLOW_GRIPPER_PITCH_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eREADY_FLOW_GRIPPER_PITCH_WAIT_POS_CHECK:
			//21.02.04 sjc no pitch servo
			//if (Devs::m_PitchMotion.Is_Pitch_WaitPos_All())
			if(1)
			{
			}
			else if (IsTimeOut())
			{
				Total_Msg(_T("Gripper Pitch Wait Pos Check !!"));
				SetStep(_eREADY_FLOW_ERROR, _T("_eREADY_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eREADY_FLOW_GRIPPER_PITCH_WAIT_POS_CHECK);
			}
			break;

		case _eREADY_FLOW_LOADING_STAGE_UVW_WAIT_POS:
			
			break;

		case _eREADY_FLOW_LOADING_STAGE_UVW_WAIT_POS_CHECK:
			break;

#pragma endregion
		case _eREADY_FLOW_DONE:
		{
			m_bFlowDone = TRUE;
			SetStep(_eREADY_FLOW_IDLE, _T("_eREADY_FLOW_IDLE"));
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