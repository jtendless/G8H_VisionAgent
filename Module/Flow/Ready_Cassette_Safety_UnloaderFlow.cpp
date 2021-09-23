#include "stdafx.h"
#include "Ready_Cassette_Safety_UnloaderFlow.h"
#include "Log/Logger.h"
#include "Vision/Devs.h"
#include "Data/ModelData.h"
#include "CamAreaModul.h"
#include "Data/SystemData.h"
#include "VisionAgentDlg.h"
#include "Data/ManualData.h"

CReady_Cassette_Safety_UnloaderFlow::CReady_Cassette_Safety_UnloaderFlow()
{
}


CReady_Cassette_Safety_UnloaderFlow::~CReady_Cassette_Safety_UnloaderFlow()
{
}

BOOL CReady_Cassette_Safety_UnloaderFlow::InitProcess()
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
BOOL CReady_Cassette_Safety_UnloaderFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_IDLE);

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
BOOL CReady_Cassette_Safety_UnloaderFlow::Start()
{
	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_START, _T("_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_START"));
	return TRUE;
}
BOOL CReady_Cassette_Safety_UnloaderFlow::Stop()
{
	m_bStopBit = TRUE;
	SetStop(); //!!
	return TRUE;
}
UINT CReady_Cassette_Safety_UnloaderFlow::ThreadFunction(LPVOID lpParam)
{
	CReady_Cassette_Safety_UnloaderFlow* pFlow = NULL;

	pFlow = (CReady_Cassette_Safety_UnloaderFlow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}
VOID CReady_Cassette_Safety_UnloaderFlow::ThreadFunctionEntry(VOID)
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

			SetCurrentStep(_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}


		switch (GetCurrentTotalStep())
		{
		case _eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_IDLE:
		{
			break;
		}
		case _eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_START:
		{
			SetStep(_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_INTERLOCK_CHECK, _T("_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_INTERLOCK_CHECK"));
			break;
		}

		case _eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_INTERLOCK_CHECK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_ERROR, _T("_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_ERROR"));
			}
			else
			{
				//SetStep(_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_SUB_Z_UP, _T("_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_SUB_Z_UP"));
			}
			break;

#if 0 //Hide
		case _eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_SUB_Z_UP:			
			Devs::m_UnloaderMotion.UnloaderZL_WaitPos();
			Sleep(10);
			Devs::m_UnloaderMotion.UnloaderZR_WaitPos();
			Sleep(10);

			//SetStep(_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_SUB_Z_UP_CHECK, _T("_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_SUB_Z_UP_CHECK"));
			//SetTimeOut(TIME_OUT_MOTION);
			SetStep(_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_Z_UP, _T("_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_Z_UP"));
			break;

		case _eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_Z_UP:
			Devs::m_UnloaderMotion.UnloaderZ_WaitPos();
			Sleep(10);

			//SetStep(_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_Z_UP_CHECK, _T("_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_Z_UP_CHECK"));
			//SetTimeOut(TIME_OUT_MOTION);
			SetStep(_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_SUB_Z_UP_CHECK, _T("_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_SUB_Z_UP_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_SUB_Z_UP_CHECK:
			if (Devs::m_UnloaderMotion.Is_UnloaderZL_WaitPos() && Devs::m_UnloaderMotion.Is_UnloaderZR_WaitPos())
			{
				//SetStep(_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_Z_UP, _T("_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_Z_UP"));
				SetStep(_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_Z_UP_CHECK, _T("_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_Z_UP_CHECK"));
				SetTimeOut(TIME_OUT_MOTION);
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_SUB_Z_UP_CHECK"), eREADY_CASSETTE_SAFETY_UNLOADER_FLOW + 0);
				SetStep(_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_ERROR, _T("_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_SUB_Z_UP_CHECK, _T("_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_SUB_Z_UP_CHECK"));
			}
			break;

	

		case _eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_Z_UP_CHECK:
			if (Devs::m_UnloaderMotion.Is_UnloaderZ_WaitPos())
			{
				SetStep(_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_X_WAIT_POS, _T("_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_X_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_Z_UP_CHECK"), eREADY_CASSETTE_SAFETY_UNLOADER_FLOW + 1);
				SetStep(_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_ERROR, _T("_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_Z_UP_CHECK, _T("_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_Z_UP_CHECK"));
			}
			break;

		case _eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_X_WAIT_POS:
			Devs::m_UnloaderMotion.UnloaderX_WaitPos();

			SetStep(_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_X_WAIT_POS_CHECK, _T("_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_X_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_X_WAIT_POS_CHECK:
			if (Devs::m_UnloaderMotion.Is_UnloaderX_WaitPos())			
			{
				SetStep(_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_Y_CASSETTE_SAFETY_POS, _T("_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_Y_CASSETTE_SAFETY_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_X_WAIT_POS_CHECK"), eREADY_CASSETTE_SAFETY_UNLOADER_FLOW + 2);
				SetStep(_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_ERROR, _T("_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_X_WAIT_POS_CHECK, _T("_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_X_WAIT_POS_CHECK"));
			}
			break;
		
		case _eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_Y_CASSETTE_SAFETY_POS:
			Devs::m_UnloaderMotion.UnloaderY_CassetteSafetyPos();

			SetStep(_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_Y_CASSETTE_SAFETY_POS_CHECK, _T("_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_Y_CASSETTE_SAFETY_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_Y_CASSETTE_SAFETY_POS_CHECK:
			if (Devs::m_UnloaderMotion.Is_UnloaderY_CassetteSafetyPos())
			{
				SetStep(_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_DONE, _T("_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_Y_CASSETTE_SAFETY_POS_CHECK"), eREADY_CASSETTE_SAFETY_UNLOADER_FLOW + 3);
				SetStep(_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_ERROR, _T("_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_Y_CASSETTE_SAFETY_POS_CHECK, _T("_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_Y_CASSETTE_SAFETY_POS_CHECK"));
			}
			break;
#endif

		case _eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_ERROR:
			break;

		case _eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_DONE:
		{
			m_bFlowDone = TRUE;

			SetStep(_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_IDLE, _T("_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_IDLE"));			
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

BOOL CReady_Cassette_Safety_UnloaderFlow::FlowInterlock()
{
	CString Str = _T("");
	int i = 0;

	//Vac Off Check
#pragma region	//Unloader Vac Check
	for (i = 0; i < 4; i++)
	{
		//if (SharedInfo::DInputValue[_DIN_ULD_STICK_VAC_1 + (i*2)] || SharedInfo::DInputValue[_DIN_ULD_STICK_VAC_2 + (i*2)])
		//{
		//	Str.Format(_T("Check Unloader DIn Stick Vac_%d Status !!!"), i + 1);
		//	Total_Msg(Str);
		//	return FALSE;
		//}
		//if (SharedInfo::DOutputValue[_DOUT_ULD_STICK_VAC_1 + i])
		//{
		//	Str.Format(_T("Check Unloader DOut Stick Vac_%d Status !!!"), i + 1);
		//	Total_Msg(Str);
		//	return FALSE;
		//}
	}
	//Devs::m_UnloaderMotion.Stick_All_Vac_Off();
#pragma endregion

	double  dPos = SharedInfo::GetActPos(AXIS_VIRTUAL_GANTRY_Y);
	if (dPos > CManualData::m_ManualDataGantry.Info.m_dGantry_Y_Wait_Pos)
	{
		CString Str;
		Str.Format(_T("%s : Check Gantry Y Wait Pos !!!"), _T("Ready_Cassette_Safety_UnloaderFlow"));
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, eREADY_CASSETTE_SAFETY_UNLOADER_FLOW + 5);
		return FALSE;
	}

	if (Devs::m_UnloaderMotion.CheckUnloaderFlowInterlock(_T("Ready_Cassette_Safety_UnloaderFlow"), eREADY_CASSETTE_SAFETY_UNLOADER_FLOW, 10) == FALSE)
	{
		return FALSE;
	}

	if (Devs::m_LoaderMotion.CheckLoaderFlowInterlock(_T("Ready_Cassette_Safety_UnloaderFlow"), eREADY_CASSETTE_SAFETY_UNLOADER_FLOW, 20) == FALSE)
	{
		return FALSE;
	}	

	return TRUE;
}