#include "stdafx.h"
#include "Origin_3DCameraZ_Flow.h"
#include "Vision/Devs.h"
#include "VisionAgentDlg.h"
#include "Motion/GantryMotion.h"

COrigin_3DCameraZ_Flow::COrigin_3DCameraZ_Flow()
{
}


COrigin_3DCameraZ_Flow::~COrigin_3DCameraZ_Flow()
{
}

BOOL COrigin_3DCameraZ_Flow::InitProcess()
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
BOOL COrigin_3DCameraZ_Flow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eORIGIN_3D_CAMERA_Z_FLOW_IDLE, _T("_eORIGIN_3D_CAMERA_Z_FLOW_IDLE"));

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
BOOL COrigin_3DCameraZ_Flow::Start()
{
	eRemoteAxis = REMOTE_AXIS_AJIN_3D_CAMERA_Z1;

	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(_eORIGIN_3D_CAMERA_Z_FLOW_START, _T("_eORIGIN_3D_CAMERA_Z_FLOW_START"));
	return TRUE;
}
BOOL COrigin_3DCameraZ_Flow::Stop()
{
	m_bStopBit = TRUE;
	SetStop(); //!!
	return TRUE;
}
UINT COrigin_3DCameraZ_Flow::ThreadFunction(LPVOID lpParam)
{
	COrigin_3DCameraZ_Flow* pFlow = NULL;

	pFlow = (COrigin_3DCameraZ_Flow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}
VOID COrigin_3DCameraZ_Flow::ThreadFunctionEntry(VOID)
{
	DWORD	dwResult = 0;
	double	dStrt_Time = GetTickCount();
	double	dEnd_Time = GetTickCount();
	double	dWait_Time = GetTickCount();
	int		nWork_Mask_Mode = -1;
	int		nWork_Mask_Index = -1;
	BOOL	bComplete_Step = FALSE;
	CVisionAgentDlg *pMain = (CVisionAgentDlg*)AfxGetMainWnd();
	CString Str = _T("");

	while (m_FlowFinish)
	{
		WaitForSingleObject(hHandle, INFINITE);
		ResetEvent(hHandle);

		if (SharedInfo::bMachineStopFlag == TRUE && m_bStopBit == FALSE)
		{
			m_bStopBit = TRUE;

			continue; //!!
		}
		if (SharedInfo::bMachineStopFlag == TRUE)
			continue;

		switch (GetCurrentTotalStep())
		{
		case _eORIGIN_3D_CAMERA_Z_FLOW_IDLE:
		{
			break;
		}
		case _eORIGIN_3D_CAMERA_Z_FLOW_START:
			SetStep(_eORIGIN_3D_CAMERA_Z_FLOW_INTERLOCK_CHECK, _T("_eORIGIN_3D_CAMERA_Z_FLOW_INTERLOCK_CHECK"));
			break;

		case _eORIGIN_3D_CAMERA_Z_FLOW_INTERLOCK_CHECK:
			if (FlowInterlock() == FALSE)
			{
				m_bFlowDone = TRUE;
				SetStep(_eORIGIN_3D_CAMERA_Z_FLOW_IDLE, _T("_eORIGIN_3D_CAMERA_Z_FLOW_IDLE"));
			}
			else
			{
				SetStep(eGANTRY_MOTION_3D_CAMERA_Z_HOME_START, _T("eGANTRY_MOTION_3D_CAMERA_Z_HOME_START"));
			}
			break;

#pragma region //3D Camera Z Home
		case eGANTRY_MOTION_3D_CAMERA_Z_HOME_START:
			Devs::MotionIf.AxisHomeStart(eRemoteAxis);
			Sleep(3000); //!!

			SetStep(eGANTRY_MOTION_3D_CAMERA_Z_HOME_CHECK, _T("eGANTRY_MOTION_3D_CAMERA_Z_HOME_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eGANTRY_MOTION_3D_CAMERA_Z_HOME_CHECK:
			if (SharedInfo::AxisInMotionStatus[eRemoteAxis] == FALSE && SharedInfo::AxisHomeStatus[eRemoteAxis])
			{
				SetStep(eGANTRY_MOTION_3D_CAMERA_Z_WAIT_POS, _T("eGANTRY_MOTION_3D_CAMERA_Z_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eORIGIN_3D_CAMERA_Z_FLOW_ERROR, _T("_eORIGIN_3D_CAMERA_Z_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eGANTRY_MOTION_3D_CAMERA_Z_HOME_CHECK, _T("eGANTRY_MOTION_3D_CAMERA_Z_HOME_CHECK"));
			}
			break;

		case eGANTRY_MOTION_3D_CAMERA_Z_WAIT_POS:
			Devs::m_GantryMotion.Move_3D_Camera_Main_Z_Wait_Pos();

			SetStep(eGANTRY_MOTION_3D_CAMERA_Z_WAIT_POS_CHECK, _T("eGANTRY_MOTION_3D_CAMERA_Z_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eGANTRY_MOTION_3D_CAMERA_Z_WAIT_POS_CHECK:
			if (Devs::m_GantryMotion.Is_3D_Camera_Main_Z_Wait_Pos())
			{
				SetStep(_eORIGIN_3D_CAMERA_Z_FLOW_DONE, _T("_eORIGIN_3D_CAMERA_Z_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eORIGIN_3D_CAMERA_Z_FLOW_ERROR, _T("_eORIGIN_3D_CAMERA_Z_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eGANTRY_MOTION_3D_CAMERA_Z_WAIT_POS_CHECK, _T("eGANTRY_MOTION_3D_CAMERA_Z_WAIT_POS_CHECK"));
			}
			break;
#pragma endregion		

		case _eORIGIN_3D_CAMERA_Z_FLOW_DONE:
		{
			m_bFlowDone = TRUE;
			break;
		}
		case _eORIGIN_3D_CAMERA_Z_FLOW_STOP:
		{
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

BOOL COrigin_3DCameraZ_Flow::FlowInterlock()
{
	CString Str = _T("");

	//if (SharedInfo::GetServoOnStatus(AXIS_3D_CAMERA_MAIN_Z) != TRUE)
	//{
	//	Total_Msg(_T("3D Camera Main Servo On Check !!!"));
	//	return FALSE;
	//}

	return TRUE;
}
