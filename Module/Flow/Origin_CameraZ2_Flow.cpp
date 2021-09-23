#include "stdafx.h"
#include "Flow/Origin_CameraZ2_Flow.h"
#include "Vision/Devs.h"
#include "VisionAgentDlg.h"

COrigin_CameraZ2_Flow::COrigin_CameraZ2_Flow()
{
}


COrigin_CameraZ2_Flow::~COrigin_CameraZ2_Flow()
{
}

BOOL COrigin_CameraZ2_Flow::InitProcess()
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
BOOL COrigin_CameraZ2_Flow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eORIGIN_CAMERA_Z2_FLOW_IDLE, _T("_eORIGIN_CAMERA_Z2_FLOW_IDLE"));

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
BOOL COrigin_CameraZ2_Flow::Start()
{
	m_nHomingAxis = DIRECT_AXIS_AJIN_CAMERA_Z1;

	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(_eORIGIN_CAMERA_Z2_FLOW_START, _T("_eORIGIN_CAMERA_Z2_FLOW_START"));
	return TRUE;
}
BOOL COrigin_CameraZ2_Flow::Stop()
{
	m_bStopBit = TRUE;
	SetStop(); //!!
	return TRUE;
}
UINT COrigin_CameraZ2_Flow::ThreadFunction(LPVOID lpParam)
{
	COrigin_CameraZ2_Flow* pFlow = NULL;

	pFlow = (COrigin_CameraZ2_Flow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}
VOID COrigin_CameraZ2_Flow::ThreadFunctionEntry(VOID)
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

	BOOL bResult = FALSE;
	double dVel = 5.0;
	double dAcc = 10.0;
	double dDec = 10.0;
	int LimitSignal = 0;

	while (m_FlowFinish)
	{
		WaitForSingleObject(hHandle, INFINITE);
		ResetEvent(hHandle);

		if (SharedInfo::bMachineStopFlag == TRUE)// && m_bStopBit == FALSE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(_eORIGIN_CAMERA_Z2_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}
		
		switch (GetCurrentTotalStep())
		{
		case _eORIGIN_CAMERA_Z2_FLOW_IDLE:
		{
			break;
		}
		case _eORIGIN_CAMERA_Z2_FLOW_START:
			SetStep(_eORIGIN_CAMERA_Z2_FLOW_INTERLOCK_CHECK, _T("_eORIGIN_CAMERA_Z2_FLOW_INTERLOCK_CHECK"));
			break;

		case _eORIGIN_CAMERA_Z2_FLOW_INTERLOCK_CHECK:
			if (FlowInterlock() == FALSE)
			{
				m_bFlowDone = TRUE;
				SetStep(_eORIGIN_CAMERA_Z2_FLOW_IDLE, _T("_eORIGIN_CAMERA_Z2_FLOW_IDLE"));
			}
			else
			{
				SetStep(eORIGIN_CAMERA_Z2_FLOW_PLIMIT_POS, _T("eORIGIN_CAMERA_Z2_FLOW_PLIMIT_POS"));
			}
			break;

		case eORIGIN_CAMERA_Z2_FLOW_PLIMIT_POS:
			AxmMoveVel(m_nHomingAxis, dVel, dAcc, dDec);
			SetCheckStep(eORIGIN_CAMERA_Z2_FLOW_PLIMIT_POS_CHECK, _T("eORIGIN_CAMERA_Z2_FLOW_PLIMIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eORIGIN_CAMERA_Z2_FLOW_PLIMIT_POS_CHECK:
			LimitSignal = SharedInfo::VisionAxisPLimitSignal[m_nHomingAxis];
			if (LimitSignal == 1)
			{
				AxmMoveStop(m_nHomingAxis, dDec * 2);

				SetStep(eORIGIN_CAMERA_Z2_FLOW_PLIMIT_EJECT_POS, _T("eORIGIN_CAMERA_Z2_FLOW_PLIMIT_EJECT_POS"));
			}
			else
			{
				SetCheckStep(eORIGIN_CAMERA_Z2_FLOW_PLIMIT_POS_CHECK, _T("eORIGIN_CAMERA_Z2_FLOW_PLIMIT_POS_CHECK"));
			}
			break;

		case eORIGIN_CAMERA_Z2_FLOW_PLIMIT_EJECT_POS:
			m_HomeStartPos = SharedInfo::VisionAxisCmdPos[m_nHomingAxis];
			AxmMoveVel(m_nHomingAxis, -dVel, dAcc, dDec);

			SetCheckStep(eORIGIN_CAMERA_Z2_FLOW_PLIMIT_EJECT_POS_CHECK, _T("eORIGIN_CAMERA_Z2_FLOW_PLIMIT_EJECT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eORIGIN_CAMERA_Z2_FLOW_PLIMIT_EJECT_POS_CHECK:
			if (SharedInfo::VisionAxisPLimitSignal[m_nHomingAxis] == 0 || fabs(m_HomeStartPos - SharedInfo::VisionAxisCmdPos[m_nHomingAxis]) > 1)
				bResult = TRUE;
			else
				bResult = FALSE;

			if (bResult)
			{
				AxmMoveStop(m_nHomingAxis, dDec * 2);
				SetCheckStep(eORIGIN_CAMERA_Z2_FLOW_STOP_CHECK, _T("eORIGIN_CAMERA_Z2_FLOW_STOP_CHECK"));
			}
			else
			{
				SetCheckStep(eORIGIN_CAMERA_Z2_FLOW_PLIMIT_EJECT_POS_CHECK);
			}
			break;

		case eORIGIN_CAMERA_Z2_FLOW_STOP_CHECK:
			if (SharedInfo::VisionAxisInMotionStatus[m_nHomingAxis] == 1)
				bResult = TRUE;
			else
				bResult = FALSE;

			if (bResult == FALSE)
			{
				SetStep(eORIGIN_CAMERA_Z2_FLOW_HOME_START, _T("eORIGIN_CAMERA_Z2_FLOW_HOME_START"));
			}
			else
			{
				SetCheckStep(eORIGIN_CAMERA_Z2_FLOW_STOP_CHECK);
			}
			break;

		case eORIGIN_CAMERA_Z2_FLOW_HOME_START:
			m_HomeStartPos = SharedInfo::VisionAxisCmdPos[m_nHomingAxis];
			AxmHomeSetStart(m_nHomingAxis);

			SetCheckStep(eORIGIN_CAMERA_Z2_FLOW_HOME_COMP_CHECK, _T("eORIGIN_CAMERA_Z2_FLOW_HOME_COMP_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eORIGIN_CAMERA_Z2_FLOW_HOME_COMP_CHECK:
			if (SharedInfo::VisionAxisInMotionStatus[m_nHomingAxis] == FALSE && SharedInfo::VisionAxisHomeStatus[m_nHomingAxis] == TRUE)
				bResult = TRUE;
			else
				bResult = FALSE;

			if (bResult)
			{
				SetStep(eORIGIN_CAMERA_Z2_FLOW_WAIT_POS, _T("eORIGIN_CAMERA_Z2_FLOW_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eORIGIN_CAMERA_Z2_FLOW_ERROR, _T("_eORIGIN_CAMERA_Z2_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eORIGIN_CAMERA_Z2_FLOW_HOME_COMP_CHECK, _T("eORIGIN_CAMERA_Z2_FLOW_HOME_COMP_CHECK"));
			}
			break;
		//case eORIGIN_CAMERA_Z2_FLOW_WAIT_POS:
		//	Devs::m_GantryMotion.Move_GantryZ2_Wait_Pos();

		//	SetCheckStep(eORIGIN_CAMERA_Z2_FLOW_WAIT_POS_CHECK, _T("eORIGIN_CAMERA_Z2_FLOW_WAIT_POS_CHECK"));
		//	SetTimeOut(TIME_OUT_MOTION);
		//	break;

		//case eORIGIN_CAMERA_Z2_FLOW_WAIT_POS_CHECK:
		//	if (Devs::m_GantryMotion.Is_GantryZ2_Wait_Pos())
		//	{
		//		SetStep(_eORIGIN_CAMERA_Z2_FLOW_DONE, _T("_eORIGIN_CAMERA_Z2_FLOW_DONE"));
		//	}
		//	else if (IsTimeOut())
		//	{
		//		SetStep(_eORIGIN_CAMERA_Z2_FLOW_ERROR, _T("_eORIGIN_CAMERA_Z2_FLOW_ERROR"));
		//	}
		//	else
		//	{
		//		SetCheckStep(eORIGIN_CAMERA_Z2_FLOW_WAIT_POS_CHECK);
		//	}
		//	break;

		case _eORIGIN_CAMERA_Z2_FLOW_DONE:
		{
			m_bFlowDone = TRUE;

			SetStep(_eORIGIN_CAMERA_Z2_FLOW_IDLE, _T("_eORIGIN_CAMERA_Z2_FLOW_IDLE"));
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

BOOL COrigin_CameraZ2_Flow::FlowInterlock()
{
	CString Str = _T("");

	if (SharedInfo::GetServoOnStatus(AXIS_CAMERA_Z1) != TRUE)
	{
		Total_Msg(_T("Camera Z2 Servo On Check !!!"));
		return FALSE;
	}

	return TRUE;
}