#include "stdafx.h"
#include "Origin_GantryX_Flow.h"
#include "Vision/Devs.h"
#include "VisionAgentDlg.h"
#include "Data/ManualData.h"

COrigin_GantryX_Flow::COrigin_GantryX_Flow()
{
}


COrigin_GantryX_Flow::~COrigin_GantryX_Flow()
{
}

BOOL COrigin_GantryX_Flow::InitProcess()
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
	return TRUE;
}

BOOL COrigin_GantryX_Flow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eORIGIN_GANTRY_X_FLOW_IDLE, _T("_eORIGIN_GANTRY_X_FLOW_IDLE"));

	if (hHandle != NULL)
	{
		CloseHandle(hHandle);
	}

	return TRUE;
}
BOOL COrigin_GantryX_Flow::Start()
{
	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(_eORIGIN_GANTRY_X_FLOW_START, _T("_eORIGIN_GANTRY_X_FLOW_START"));
	return TRUE;
}
BOOL COrigin_GantryX_Flow::Stop()
{
	m_bStopBit = TRUE;
	return TRUE;
}
UINT COrigin_GantryX_Flow::ThreadFunction(LPVOID lpParam)
{
	COrigin_GantryX_Flow* pFlow = NULL;

	pFlow = (COrigin_GantryX_Flow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}

VOID COrigin_GantryX_Flow::ThreadFunctionEntry(VOID)
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

		if (SharedInfo::bMachineStopFlag == TRUE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(_eORIGIN_GANTRY_X_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}

		switch (GetCurrentTotalStep())
		{
		case _eORIGIN_GANTRY_X_FLOW_IDLE:
		{
			break;
		}
		case _eORIGIN_GANTRY_X_FLOW_START:
			m_timeStart = CTime::GetCurrentTime(); //KJT 20210329

			SetStep(_eORIGIN_GANTRY_X_FLOW_INTERLOCK_CHECK, _T("_eORIGIN_GANTRY_X_FLOW_INTERLOCK_CHECK"));
			break;

		case _eORIGIN_GANTRY_X_FLOW_INTERLOCK_CHECK:
			if (FlowInterlock() == FALSE)
			{
				m_bFlowDone = TRUE;
				SetStep(_eORIGIN_GANTRY_X_FLOW_IDLE, _T("_eORIGIN_GANTRY_X_FLOW_IDLE"));
			}
			else
			{
				SetStep(_eORIGIN_GANTRY_X_FLOW_HOME_START, _T("_eORIGIN_GANTRY_X_FLOW_HOME_START"));
			}
			break;

		case _eORIGIN_GANTRY_X_FLOW_HOME_START:
			Devs::MotionIf.UmacHomeStart(REMOTE_AXIS_UMAC_GANTRY_X); //KJT 20210416

			SetStep(_eORIGIN_GANTRY_X_FLOW_HOME_BIT_OFF_CHECK, _T("_eORIGIN_GANTRY_X_FLOW_HOME_BIT_OFF_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eORIGIN_GANTRY_X_FLOW_HOME_BIT_OFF_CHECK:
			if (!SharedInfo::UmacHomeStatus[REMOTE_AXIS_UMAC_GANTRY_X])
			{
				SetStep(_eORIGIN_GANTRY_X_FLOW_HOME_COMP_CHECK, _T("_eORIGIN_GANTRY_X_FLOW_HOME_COMP_CHECK"));
				SetTimeOut(TIME_OUT_MOTION);//KJT 20210416
			}
			else if (IsTimeOut())
			{
				SetStep(_eORIGIN_GANTRY_X_FLOW_ERROR, _T("_eORIGIN_GANTRY_X_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eORIGIN_GANTRY_X_FLOW_HOME_BIT_OFF_CHECK, _T("_eORIGIN_GANTRY_X_FLOW_HOME_BIT_OFF_CHECK"));
			}
			break;

		case _eORIGIN_GANTRY_X_FLOW_HOME_COMP_CHECK:
			if (SharedInfo::UmacHomeStatus[REMOTE_AXIS_UMAC_GANTRY_X] && SharedInfo::UmacInMotionStatus[REMOTE_AXIS_UMAC_GANTRY_X] == FALSE)
			{
				SetStep(_eORIGIN_GANTRY_X_FLOW_MOVE_WAIT_POS, _T("_eORIGIN_GANTRY_X_FLOW_MOVE_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eORIGIN_GANTRY_X_FLOW_ERROR, _T("_eORIGIN_GANTRY_X_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eORIGIN_GANTRY_X_FLOW_HOME_COMP_CHECK, _T("_eORIGIN_GANTRY_X_FLOW_HOME_COMP_CHECK"));
			}
			break;

		case _eORIGIN_GANTRY_X_FLOW_MOVE_WAIT_POS:
			Devs::m_GantryMotion.Move_Gantry_X_Wait_Pos();
			Sleep(100); //!!

			SetStep(_eORIGIN_GANTRY_X_FLOW_MOVE_WAIT_POS_CHECK, _T("_eORIGIN_GANTRY_X_FLOW_MOVE_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eORIGIN_GANTRY_X_FLOW_MOVE_WAIT_POS_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Wait_Pos())
			{
				SetStep(_eORIGIN_GANTRY_X_FLOW_DONE, _T("_eORIGIN_GANTRY_X_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eORIGIN_GANTRY_X_FLOW_ERROR, _T("_eORIGIN_GANTRY_X_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eORIGIN_GANTRY_X_FLOW_MOVE_WAIT_POS_CHECK, _T("_eORIGIN_GANTRY_X_FLOW_MOVE_WAIT_POS_CHECK"));
			}
			break;

		case _eORIGIN_GANTRY_X_FLOW_DONE:
		{
			m_bFlowDone = TRUE;

			SharedInfo::CalTactTime(_T("ORIGIN_GANTRY_X_FLOW"), m_timeStart); //KJT 20210329

			SetStep(_eORIGIN_GANTRY_X_FLOW_IDLE, _T("_eORIGIN_GANTRY_X_FLOW_IDLE"));
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

BOOL COrigin_GantryX_Flow::FlowInterlock()
{
	CString Str = _T("");

	if (SharedInfo::GetServoOnStatus(AXIS_GANTRY_X) != TRUE)
	{
		Total_Msg(_T("Gantry X Servo On Check !!!"));
		return FALSE;
	}

	if (SharedInfo::GetCmdPos(AXIS_CAMERA_Z1) < CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Wait_Pos - 0.002)
	{
		Total_Msg(_T("Camera Z1 Pos Check !!! (Cur Pos < Wait Pos)"));
		return FALSE;
	}
	//if (SharedInfo::GetCmdPos(AXIS_CAMERA_Z2) < CManualData::m_ManualDataGantry.Info.m_dGantry_Z2_Wait_Pos - 0.002)
	//{
	//	Total_Msg(_T("Camera Z2 Pos Check !!! (Cur Pos < Wait Pos)"));
	//	return FALSE;
	//}
	//if (SharedInfo::GetCmdPos(AXIS_CAMERA_Z3) < CManualData::m_ManualDataGantry.Info.m_dGantry_Z3_Wait_Pos - 0.002)
	//{
	//	Total_Msg(_T("3D Camera Z Pos Check !!! (Cur Pos < Wait Pos)"));
	//	return FALSE;
	//}

	if (SharedInfo::GetCmdPos(AXIS_UNLOADER_YL) < CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Wait_Pos - 0.002)
	{
		Total_Msg(_T("Unloader Y Pos Check !!!  (Cur Pos < Wait Pos)"));
		return FALSE;
	}

	return TRUE;
}