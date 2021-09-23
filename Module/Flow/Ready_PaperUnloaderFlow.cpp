#include "stdafx.h"
#include "Ready_PaperUnloaderFlow.h"
#include "Log/Logger.h"
#include "Vision/Devs.h"
#include "Data/ModelData.h"
#include "CamAreaModul.h"
#include "Data/SystemData.h"
#include "VisionAgentDlg.h"

CReady_PaperUnloaderFlow::CReady_PaperUnloaderFlow()
{
}


CReady_PaperUnloaderFlow::~CReady_PaperUnloaderFlow()
{
}

BOOL CReady_PaperUnloaderFlow::InitProcess()
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
BOOL CReady_PaperUnloaderFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eREADY_PAPER_UNLOADER_FLOW_IDLE);

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
BOOL CReady_PaperUnloaderFlow::Start()
{
	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(_eREADY_PAPER_UNLOADER_FLOW_START, _T("_eREADY_PAPER_UNLOADER_FLOW_START"));
	return TRUE;
}
BOOL CReady_PaperUnloaderFlow::Stop()
{
	m_bStopBit = TRUE;
	SetStop(); //!!
	return TRUE;
}
UINT CReady_PaperUnloaderFlow::ThreadFunction(LPVOID lpParam)
{
	CReady_PaperUnloaderFlow* pFlow = NULL;

	pFlow = (CReady_PaperUnloaderFlow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}
VOID CReady_PaperUnloaderFlow::ThreadFunctionEntry(VOID)
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

		if (SharedInfo::bMachineStopFlag == TRUE)// && m_bStopBit == FALSE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(_eREADY_PAPER_UNLOADER_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}


		switch (GetCurrentTotalStep())
		{
		case _eREADY_PAPER_UNLOADER_FLOW_IDLE:
		{
			break;
		}
		case _eREADY_PAPER_UNLOADER_FLOW_START:
		{
			SetStep(_eREADY_PAPER_UNLOADER_FLOW_INTERLOCK_CHECK, _T("_eREADY_PAPER_UNLOADER_FLOW_INTERLOCK_CHECK"));
			break;
		}

		case _eREADY_PAPER_UNLOADER_FLOW_INTERLOCK_CHECK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(_eREADY_PAPER_UNLOADER_FLOW_ERROR, _T("_eREADY_PAPER_UNLOADER_FLOW_ERROR"));
			}
			else
			{
				SetStep(_eREADY_PAPER_UNLOADER_FLOW_PAPER_UNLOADER_Z_WAIT_POS, _T("_eREADY_PAPER_UNLOADER_FLOW_PAPER_UNLOADER_Z_WAIT_POS"));
			}
			break;

		case _eREADY_PAPER_UNLOADER_FLOW_PAPER_UNLOADER_Z_WAIT_POS:
			Devs::m_UnloaderMotion.PaperUnloaderZ_All_WaitPos();
			Sleep(10);

			SetStep(_eREADY_PAPER_UNLOADER_FLOW_PAPER_UNLOADER_Z_WAIT_POS_CHECK, _T("_eREADY_PAPER_UNLOADER_FLOW_PAPER_UNLOADER_Z_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eREADY_PAPER_UNLOADER_FLOW_PAPER_UNLOADER_Z_WAIT_POS_CHECK:
			if (Devs::m_UnloaderMotion.Is_PaperUnloaderZ_All_WaitPos())
			{
				SetStep(_eREADY_PAPER_UNLOADER_FLOW_PAPER_UNLOADER_X_WAIT_POS, _T("_eREADY_PAPER_UNLOADER_FLOW_PAPER_UNLOADER_X_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eREADY_PAPER_UNLOADER_FLOW_PAPER_UNLOADER_Z_WAIT_POS_CHECK : Time Out !!!"), eREADY_PAPER_UNLOADER_FLOW + 1);
				SetStep(_eREADY_PAPER_UNLOADER_FLOW_ERROR, _T("_eREADY_PAPER_UNLOADER_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eREADY_PAPER_UNLOADER_FLOW_PAPER_UNLOADER_Z_WAIT_POS_CHECK, _T("_eREADY_PAPER_UNLOADER_FLOW_PAPER_UNLOADER_Z_WAIT_POS_CHECK"));
			}
			break;

		case _eREADY_PAPER_UNLOADER_FLOW_PAPER_UNLOADER_X_WAIT_POS:
			Devs::m_UnloaderMotion.PaperUnloaderX_All_WaitPos();
			Sleep(10);

			SetStep(_eREADY_PAPER_UNLOADER_FLOW_PAPER_UNLOADER_X_WAIT_POS_CHECK, _T("_eREADY_PAPER_UNLOADER_FLOW_PAPER_UNLOADER_X_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eREADY_PAPER_UNLOADER_FLOW_PAPER_UNLOADER_X_WAIT_POS_CHECK:
			if (Devs::m_UnloaderMotion.Is_PaperUnloaderX_All_WaitPos())
			{
				SetStep(_eREADY_PAPER_UNLOADER_FLOW_PAPER_UNLOADER_Y_WAIT_POS, _T("_eREADY_PAPER_UNLOADER_FLOW_PAPER_UNLOADER_Y_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eREADY_PAPER_UNLOADER_FLOW_PAPER_UNLOADER_X_WAIT_POS_CHECK : Time Out !!!"), eREADY_PAPER_UNLOADER_FLOW + 1);
				SetStep(_eREADY_PAPER_UNLOADER_FLOW_ERROR, _T("_eREADY_PAPER_UNLOADER_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eREADY_PAPER_UNLOADER_FLOW_PAPER_UNLOADER_X_WAIT_POS_CHECK, _T("_eREADY_PAPER_UNLOADER_FLOW_PAPER_UNLOADER_X_WAIT_POS_CHECK"));
			}
			break;

		case _eREADY_PAPER_UNLOADER_FLOW_PAPER_UNLOADER_Y_WAIT_POS:
			Devs::m_UnloaderMotion.PaperUnloaderY_All_WaitPos();
			Sleep(10);

			SetStep(_eREADY_PAPER_UNLOADER_FLOW_PAPER_UNLOADER_Y_WAIT_POS_CHECK, _T("_eREADY_PAPER_UNLOADER_FLOW_PAPER_UNLOADER_Y_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eREADY_PAPER_UNLOADER_FLOW_PAPER_UNLOADER_Y_WAIT_POS_CHECK:
			if (Devs::m_UnloaderMotion.Is_PaperUnloaderY_All_WaitPos())
			{
				SetStep(_eREADY_PAPER_UNLOADER_FLOW_DONE, _T("_eREADY_PAPER_UNLOADER_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eREADY_PAPER_UNLOADER_FLOW_PAPER_UNLOADER_Y_WAIT_POS_CHECK : Time Out !!!"), eREADY_PAPER_UNLOADER_FLOW + 1);
				SetStep(_eREADY_PAPER_UNLOADER_FLOW_ERROR, _T("_eREADY_PAPER_UNLOADER_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eREADY_PAPER_UNLOADER_FLOW_PAPER_UNLOADER_Y_WAIT_POS_CHECK, _T("_eREADY_PAPER_UNLOADER_FLOW_PAPER_UNLOADER_Y_WAIT_POS_CHECK"));
			}
			break;

		case _eREADY_PAPER_UNLOADER_FLOW_DONE:
		{
			m_bFlowDone = TRUE;

			SetStep(_eREADY_PAPER_UNLOADER_FLOW_IDLE, _T("_eREADY_PAPER_UNLOADER_FLOW_IDLE"));			
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

BOOL CReady_PaperUnloaderFlow::FlowInterlock()
{
	CString Str = _T("");
	int i = 0;

	//Vac Off Check
#pragma region	//Paper Unloader Vac Check
	if (Devs::m_UnloaderMotion.Is_PaperUnloader_All_Vac_Off() == FALSE)
	{
		SharedInfo::SetAlarm(_T("Ready_PaperUnloaderFlow : Check Vac Off !!!"), eREADY_PAPER_UNLOADER_FLOW + 10);
		return FALSE;
	}
#pragma endregion

	//Servo On Check
	if (SharedInfo::GetServoOnStatus(AXIS_UNLOADER_ZL) == FALSE)
	{
		Str.Format(_T("Ready_PaperUnloaderFlow : Check PaperUnloader ZL Servo On !!!"));
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, eREADY_PAPER_UNLOADER_FLOW + 2);
		return FALSE;
	}
	else if (SharedInfo::GetServoOnStatus(AXIS_UNLOADER_ZR) == FALSE)
	{
		Str.Format(_T("Ready_PaperUnloaderFlow : Check PaperUnloader ZR Servo On !!!"));
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, eREADY_PAPER_UNLOADER_FLOW + 2);
		return FALSE;
	}
	else if (SharedInfo::GetServoOnStatus(AXIS_UNLOADER_XL) == FALSE)
	{
		Str.Format(_T("Ready_PaperUnloaderFlow : Check PaperUnloader XL Servo On !!!"));
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, eREADY_PAPER_UNLOADER_FLOW + 2);
		return FALSE;
	}
	else if (SharedInfo::GetServoOnStatus(AXIS_UNLOADER_XR) == FALSE)
	{
		Str.Format(_T("Ready_PaperUnloaderFlow : Check PaperUnloader XR Servo On !!!"));
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, eREADY_PAPER_UNLOADER_FLOW + 2);
		return FALSE;
	}
	else if (SharedInfo::GetServoOnStatus(AXIS_UNLOADER_YL) == FALSE)
	{
		Str.Format(_T("Ready_PaperUnloaderFlow : Check PaperUnloader YL Servo On !!!"));
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, eREADY_PAPER_UNLOADER_FLOW + 2);
		return FALSE;
	}
	else if (SharedInfo::GetServoOnStatus(AXIS_UNLOADER_YR) == FALSE)
	{
		Str.Format(_T("Ready_PaperUnloaderFlow : Check PaperUnloader YR Servo On !!!"));
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, eREADY_PAPER_UNLOADER_FLOW + 2);
		return FALSE;
	}

	//Home Status Check
	if (SharedInfo::GetHomeStatus(AXIS_UNLOADER_ZL) == FALSE)
	{
		Str.Format(_T("Ready_PaperUnloaderFlow : Check PaperUnloader ZL Home Status !!!"));
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, eREADY_PAPER_UNLOADER_FLOW + 9);
		return FALSE;
	}
	else if (SharedInfo::GetHomeStatus(AXIS_UNLOADER_ZR) == FALSE)
	{
		Str.Format(_T("Ready_PaperUnloaderFlow : Check PaperUnloader ZR Home Status !!!"));
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, eREADY_PAPER_UNLOADER_FLOW + 9);
		return FALSE;
	}
	else if (SharedInfo::GetHomeStatus(AXIS_UNLOADER_XL) == FALSE)
	{
		Str.Format(_T("Ready_PaperUnloaderFlow : Check PaperUnloader XL Home Status !!!"));
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, eREADY_PAPER_UNLOADER_FLOW + 9);
		return FALSE;
	}
	else if (SharedInfo::GetHomeStatus(AXIS_UNLOADER_XR) == FALSE)
	{
		Str.Format(_T("Ready_PaperUnloaderFlow : Check PaperUnloader XR Home Status !!!"));
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, eREADY_PAPER_UNLOADER_FLOW + 9);
		return FALSE;
	}
	else if (SharedInfo::GetHomeStatus(AXIS_UNLOADER_YL) == FALSE)
	{
		Str.Format(_T("Ready_PaperUnloaderFlow : Check PaperUnloader YL Home Status !!!"));
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, eREADY_PAPER_UNLOADER_FLOW + 9);
		return FALSE;
	}
	else if (SharedInfo::GetHomeStatus(AXIS_UNLOADER_YR) == FALSE)
	{
		Str.Format(_T("Ready_PaperUnloaderFlow : Check PaperUnloader YR Home Status !!!"));
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, eREADY_PAPER_UNLOADER_FLOW + 9);
		return FALSE;
	}

	return TRUE;
}