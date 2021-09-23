#include "stdafx.h"
#include "Origin_MasterSlaveAxis_Flow.h"
#include "Vision/Devs.h"
#include "VisionAgentDlg.h"
#include "Data/ManualData.h"

COrigin_MasterSlaveAxis_Flow::COrigin_MasterSlaveAxis_Flow()
{
}


COrigin_MasterSlaveAxis_Flow::~COrigin_MasterSlaveAxis_Flow()
{
}

BOOL COrigin_MasterSlaveAxis_Flow::InitProcess()
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
BOOL COrigin_MasterSlaveAxis_Flow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eORIGIN_MASTER_SLAVE_AXIS_FLOW_IDLE, _T("_eORIGIN_MASTER_SLAVE_AXIS_FLOW_IDLE"));

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
BOOL COrigin_MasterSlaveAxis_Flow::Start(enum_Axis eAxis)
{
	m_eAxis_Master = eAxis;
	if (m_eAxis_Master == AXIS_UNLOADER_ZL)
	{
		m_eAxis_Slave = AXIS_UNLOADER_ZR;
		m_nRemoteAxis_Master = REMOTE_AXIS_AJIN_UNLOADER_ZL;
		m_nRemoteAxis_Slave = REMOTE_AXIS_AJIN_UNLOADER_ZR;
	}
	else if (m_eAxis_Master == AXIS_UNLOADER_XL)
	{
		m_eAxis_Slave = AXIS_UNLOADER_XR;
		m_nRemoteAxis_Master = REMOTE_AXIS_AJIN_UNLOADER_XL;
		m_nRemoteAxis_Slave = REMOTE_AXIS_AJIN_UNLOADER_XR;
	}
	else if (m_eAxis_Master == AXIS_UNLOADER_YL)
	{
		m_eAxis_Slave = AXIS_UNLOADER_YR;
		m_nRemoteAxis_Master = REMOTE_AXIS_AJIN_UNLOADER_YL;
		m_nRemoteAxis_Slave = REMOTE_AXIS_AJIN_UNLOADER_YR;
	}
#ifndef GRIPPER_0
	else if (m_eAxis_Master == AXIS_GRIPPER_ZL)
	{
		m_eAxis_Slave = AXIS_GRIPPER_ZR;
		m_nRemoteAxis_Master = REMOTE_AXIS_AJIN_GRIPPER_ZL;
		m_nRemoteAxis_Slave = REMOTE_AXIS_AJIN_GRIPPER_ZR;
	}
#endif

	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(_eORIGIN_MASTER_SLAVE_AXIS_FLOW_START, _T("_eORIGIN_MASTER_SLAVE_AXIS_FLOW_START"));
	return TRUE;
}
BOOL COrigin_MasterSlaveAxis_Flow::Stop()
{
	m_bStopBit = TRUE;
	SetStop(); //!!
	return TRUE;
}
UINT COrigin_MasterSlaveAxis_Flow::ThreadFunction(LPVOID lpParam)
{
	COrigin_MasterSlaveAxis_Flow* pFlow = NULL;

	pFlow = (COrigin_MasterSlaveAxis_Flow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}
VOID COrigin_MasterSlaveAxis_Flow::ThreadFunctionEntry(VOID)
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

	while (m_FlowFinish)
	{
		WaitForSingleObject(hHandle, INFINITE);
		ResetEvent(hHandle);

		if (SharedInfo::bMachineStopFlag == TRUE)// && m_bStopBit == FALSE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(_eORIGIN_MASTER_SLAVE_AXIS_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}		

		switch (GetCurrentTotalStep())
		{
		case _eORIGIN_MASTER_SLAVE_AXIS_FLOW_IDLE:
		{
			break;
		}
		case _eORIGIN_MASTER_SLAVE_AXIS_FLOW_START:
			SetStep(_eORIGIN_MASTER_SLAVE_AXIS_FLOW_INTERLOCK_CHECK, _T("_eORIGIN_MASTER_SLAVE_AXIS_FLOW_INTERLOCK_CHECK"));
			break;

		case _eORIGIN_MASTER_SLAVE_AXIS_FLOW_INTERLOCK_CHECK:
			if (FlowInterlock() == FALSE)
			{
				m_bFlowDone = TRUE;
				SetStep(_eORIGIN_MASTER_SLAVE_AXIS_FLOW_IDLE, _T("_eORIGIN_MASTER_SLAVE_AXIS_FLOW_IDLE"));
			}
			else
			{
				SetStep(_eORIGIN_MASTER_SLAVE_AXIS_FLOW_HOME_START, _T("_eORIGIN_MASTER_SLAVE_AXIS_FLOW_HOME_START"));
			}
			break;

		case _eORIGIN_MASTER_SLAVE_AXIS_FLOW_HOME_START:
			Devs::MotionIf.AxisHomeStart(m_nRemoteAxis_Master);
			Sleep(3000); //!!

			SetStep(_eORIGIN_MASTER_SLAVE_AXIS_FLOW_HOME_COMP_CHECK, _T("_eORIGIN_MASTER_SLAVE_AXIS_FLOW_HOME_COMP_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eORIGIN_MASTER_SLAVE_AXIS_FLOW_HOME_COMP_CHECK:
			if (SharedInfo::AxisInMotionStatus[m_nRemoteAxis_Master] == FALSE && SharedInfo::AxisHomeStatus[m_nRemoteAxis_Master] &&
				SharedInfo::AxisInMotionStatus[m_nRemoteAxis_Slave] == FALSE && SharedInfo::AxisHomeStatus[m_nRemoteAxis_Slave])
			{
				Sleep(500);
				SetStep(_eORIGIN_MASTER_SLAVE_AXIS_FLOW_SYNC_POS, _T("_eORIGIN_MASTER_SLAVE_AXIS_FLOW_SYNC_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eORIGIN_MASTER_SLAVE_AXIS_FLOW_HOME_COMP_CHECK : Time Out !!!"), eORIGIN_MASTER_SLAVE_AXIS_FLOW + 0);
				SetStep(_eORIGIN_MASTER_SLAVE_AXIS_FLOW_ERROR, _T("_eORIGIN_MASTER_SLAVE_AXIS_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eORIGIN_MASTER_SLAVE_AXIS_FLOW_HOME_COMP_CHECK, _T("_eORIGIN_MASTER_SLAVE_AXIS_FLOW_HOME_COMP_CHECK"));
			}
			break;

		case _eORIGIN_MASTER_SLAVE_AXIS_FLOW_SYNC_POS:
			m_dSyncPos = SharedInfo::GetCmdPos(m_eAxis_Master);
			Devs::m_UnloaderMotion.MoveAxis(m_eAxis_Slave, m_dSyncPos);

			SetStep(_eORIGIN_MASTER_SLAVE_AXIS_FLOW_SYNC_POS_CHECK, _T("_eORIGIN_MASTER_SLAVE_AXIS_FLOW_SYNC_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eORIGIN_MASTER_SLAVE_AXIS_FLOW_SYNC_POS_CHECK:
			if (Devs::m_BaseMotion.IsAxisMoveDone(m_eAxis_Slave, m_dSyncPos))
			{
				Sleep(500);
				SetStep(_eORIGIN_MASTER_SLAVE_AXIS_FLOW_DONE, _T("_eORIGIN_MASTER_SLAVE_AXIS_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eORIGIN_MASTER_SLAVE_AXIS_FLOW_SYNC_POS_CHECK : Time Out !!!"), eORIGIN_MASTER_SLAVE_AXIS_FLOW + 1);
				SetStep(_eORIGIN_MASTER_SLAVE_AXIS_FLOW_ERROR, _T("_eORIGIN_MASTER_SLAVE_AXIS_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eORIGIN_MASTER_SLAVE_AXIS_FLOW_SYNC_POS_CHECK, _T("_eORIGIN_MASTER_SLAVE_AXIS_FLOW_SYNC_POS_CHECK"));
			}
			break;

		case _eORIGIN_MASTER_SLAVE_AXIS_FLOW_DONE:
		{
			m_bFlowDone = TRUE;

			SetStep(_eORIGIN_MASTER_SLAVE_AXIS_FLOW_IDLE, _T("(_eORIGIN_MASTER_SLAVE_AXIS_FLOW_IDLE"));
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

BOOL COrigin_MasterSlaveAxis_Flow::FlowInterlock()
{
	CString Str = _T("");
	double dPos = 0.0;

	if (m_eAxis_Master != AXIS_UNLOADER_ZL &&
		m_eAxis_Master != AXIS_UNLOADER_XL &&
		m_eAxis_Master != AXIS_UNLOADER_YL
#ifndef GRIPPER_0
		&&
		m_eAxis_Master != AXIS_GRIPPER_ZL
#endif
		)
	{
		Str.Format(_T("Axis Number Invalid !!"));
		SharedInfo::SetAlarm(Str, eORIGIN_MASTER_SLAVE_AXIS_FLOW + 20);
		return FALSE;
	}

	//Servo On Check
	if (SharedInfo::GetServoOnStatus(m_eAxis_Master) != TRUE)
	{
		Str.Format(_T("Origin_MasterSlaveAxis_Flow : %s Servo On Check !!!"), SharedInfo::GetAxisName(m_eAxis_Master));
		SharedInfo::SetAlarm(Str, eORIGIN_MASTER_SLAVE_AXIS_FLOW + 20);
		return FALSE;
	}
	if (SharedInfo::GetServoOnStatus(m_eAxis_Slave) != TRUE)
	{
		Str.Format(_T("Origin_MasterSlaveAxis_Flow : %s Servo On Check !!!"), SharedInfo::GetAxisName(m_eAxis_Slave));
		SharedInfo::SetAlarm(Str, eORIGIN_MASTER_SLAVE_AXIS_FLOW + 20);
		return FALSE;
	}
	
	//IO Check
	if (m_eAxis_Master == AXIS_UNLOADER_ZL || m_eAxis_Master == AXIS_UNLOADER_XL || m_eAxis_Master == AXIS_UNLOADER_YL)
	{
		if (Devs::m_UnloaderMotion.Is_PaperUnloader_Vac_Off(eVAC_UNLOADER_PAPER_ALL) == FALSE)
		{
			SharedInfo::SetAlarm(_T("Origin_MasterSlaveAxis_Flow : PaperUnloader Vac Off Check !!!"), eORIGIN_MASTER_SLAVE_AXIS_FLOW + 28);
			return FALSE;
		}
	}
#ifndef GRIPPER_0
	if (m_eAxis_Master == AXIS_GRIPPER_ZL)
	{
		for (int i = 0; i < eGRIPPER_ROW_MAX; i++)
		{
			if (SharedInfo::DInputValue[_DIN_GRIP_L1_OPEN_DETECT_SENSOR + (i * 2)] == FALSE || SharedInfo::DInputValue[_DIN_GRIP_R1_OPEN_DETECT_SENSOR + (i * 2)] == FALSE)
			{
				SharedInfo::SetAlarm(_T("Origin_MasterSlaveAxis_Flow : Gripper Clamp Open Check !!!"), eORIGIN_MASTER_SLAVE_AXIS_FLOW + 28);
				return FALSE;
			}
		}
	}
#endif

	return TRUE;
}