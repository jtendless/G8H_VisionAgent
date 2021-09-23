#include "stdafx.h"
#include "Ready_GantryZX_Flow.h"
#include "Log/Logger.h"
#include "Vision/Devs.h"
#include "Data/ModelData.h"
#include "CamAreaModul.h"
#include "Data/SystemData.h"
#include "VisionAgentDlg.h"

CReady_GantryZX_Flow::CReady_GantryZX_Flow()
{
}


CReady_GantryZX_Flow::~CReady_GantryZX_Flow()
{
}

BOOL CReady_GantryZX_Flow::InitProcess()
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

BOOL CReady_GantryZX_Flow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eREADY_GANTRY_ZX_FLOW_IDLE, _T("_eREADY_GANTRY_ZX_FLOW_IDLE"));

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

BOOL CReady_GantryZX_Flow::Start()
{
	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(_eREADY_GANTRY_ZX_FLOW_START, _T("_eREADY_GANTRY_ZX_FLOW_START"));
	return TRUE;
}
BOOL CReady_GantryZX_Flow::Stop()
{
	m_bStopBit = TRUE;
	SetStop(); //!!
	return TRUE;
}

UINT CReady_GantryZX_Flow::ThreadFunction(LPVOID lpParam)
{
	CReady_GantryZX_Flow* pFlow = NULL;

	pFlow = (CReady_GantryZX_Flow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}

VOID CReady_GantryZX_Flow::ThreadFunctionEntry(VOID)
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

			SetCurrentStep(_eREADY_GANTRY_ZX_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}		

		switch (GetCurrentTotalStep())
		{
		case _eREADY_GANTRY_ZX_FLOW_IDLE:
		{
			break;
		}
		case _eREADY_GANTRY_ZX_FLOW_START:
		{
			SetStep(_eREADY_GANTRY_ZX_FLOW_INTERLOCK_CHECK, _T("_eREADY_GANTRY_ZX_FLOW_INTERLOCK_CHECK"));
			break;
		}

		case _eREADY_GANTRY_ZX_FLOW_INTERLOCK_CHECK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(_eREADY_GANTRY_ZX_FLOW_ERROR, _T("_eREADY_GANTRY_ZX_FLOW_ERROR"));
			}
			else
			{
				SetStep(_eREADY_GANTRY_ZX_FLOW_Z_ALL_WAIT_POS, _T("_eREADY_GANTRY_ZX_FLOW_Z_ALL_WAIT_POS"));
			}
			break;

		case _eREADY_GANTRY_ZX_FLOW_Z_ALL_WAIT_POS:
			Devs::m_GantryMotion.Move_GantryZ_All_Wait_Pos();

			SetStep(_eREADY_GANTRY_ZX_FLOW_Z_ALL_WAIT_POS_CHECK, _T("_eREADY_GANTRY_ZX_FLOW_Z_ALL_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eREADY_GANTRY_ZX_FLOW_Z_ALL_WAIT_POS_CHECK:
			if (Devs::m_GantryMotion.Is_GantryZ_All_Wait_Pos())
			{
				SetStep(_eREADY_GANTRY_ZX_FLOW_X_WAIT_POS, _T("_eREADY_GANTRY_ZX_FLOW_X_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eREADY_GANTRY_ZX_FLOW_Z_ALL_WAIT_POS_CHECK : Time Out!!!"), eREADY_GANTRY_ZX_FLOW + 0);
				SetStep(_eREADY_GANTRY_ZX_FLOW_ERROR, _T("_eREADY_GANTRY_ZX_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eREADY_GANTRY_ZX_FLOW_Z_ALL_WAIT_POS_CHECK, _T("_eREADY_GANTRY_ZX_FLOW_Z_ALL_WAIT_POS_CHECK"));
			}
			break;

		case _eREADY_GANTRY_ZX_FLOW_X_WAIT_POS:
			Devs::m_GantryMotion.Move_Gantry_X_Wait_Pos();
			Sleep(10); //!!

			SetStep(_eREADY_GANTRY_ZX_FLOW_X_WAIT_POS_CHECK, _T("_eREADY_GANTRY_ZX_FLOW_X_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eREADY_GANTRY_ZX_FLOW_X_WAIT_POS_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Wait_Pos())
			{
				SetStep(_eREADY_GANTRY_ZX_FLOW_DONE, _T("_eREADY_GANTRY_ZX_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eREADY_GANTRY_ZX_FLOW_X_WAIT_POS_CHECK : Time Out!!!"), eREADY_GANTRY_ZX_FLOW + 1);
				SetStep(_eREADY_GANTRY_ZX_FLOW_ERROR, _T("_eREADY_GANTRY_ZX_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eREADY_GANTRY_ZX_FLOW_X_WAIT_POS_CHECK, _T("_eREADY_GANTRY_ZX_FLOW_X_WAIT_POS_CHECK"));
			}
			break;

		case _eREADY_GANTRY_ZX_FLOW_ERROR:
			break;

		case _eREADY_GANTRY_ZX_FLOW_DONE:
		{
			m_bFlowDone = TRUE;
			
			SetStep(_eREADY_GANTRY_ZX_FLOW_IDLE, _T("_eREADY_GANTRY_ZX_FLOW_IDLE"));
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

BOOL CReady_GantryZX_Flow::FlowInterlock()
{
	if (Devs::m_GantryMotion.CheckGantryXYZFlowInterlock(_T("Ready_GantryZX_Flow"), eREADY_GANTRY_ZX_FLOW, 10) == FALSE)
	{
		return FALSE;
	}

	return TRUE;
}