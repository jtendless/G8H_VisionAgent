#include "stdafx.h"
#include "AutoLaserFocusFlow.h"
#include "Log/Logger.h"
#include "Vision/Devs.h"
#include "Data/ModelData.h"
#include "CamAreaModul.h"
#include "Data/SystemData.h"
#include "VisionAgent.h"
#include "VisionAgentDlg.h"
#include "SystemDlg.h"
#include "LLC4_AF_ModuleDlg.h"
#include "FmmLight1.h"

CAutoLaserFocusFlow::CAutoLaserFocusFlow()
{
}


CAutoLaserFocusFlow::~CAutoLaserFocusFlow()
{
}

BOOL CAutoLaserFocusFlow::InitProcess()
{
	m_StateComplete = NULL;
	m_FlowFinish = TRUE;
	m_bTerminate = FALSE;
	m_bFlowDone = TRUE;
	m_bReadyDone = FALSE;
	//SetProcessLog(Process_Msg);
	//SetAlarmLog(Alarm_Msg);

	hHandle = CreateEvent(NULL, TRUE, FALSE, NULL);
	SetHandle(hHandle);
	pThread = AfxBeginThread(ThreadFunction, this);

	//pMappingProc = CMappingProc::GetInstance();.
	return TRUE;
}

BOOL CAutoLaserFocusFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eAUTO_LASER_FOCUS_FLOW_START, FALSE);

	if (hHandle != NULL)
	{
		CloseHandle(hHandle);
		hHandle = NULL;
	}

	return TRUE;
}

BOOL CAutoLaserFocusFlow::Start()
{

	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;

	SetStep(_eAUTO_LASER_FOCUS_FLOW_START, _T("_eAUTO_LASER_FOCUS_FLOW_START"));

	return TRUE;
}

BOOL CAutoLaserFocusFlow::FocusStart()
{

	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;

	SetStep(_eAUTO_LASER_FOCUS_FLOW_AUTOFOCUS_ON, _T("_eAUTO_LASER_FOCUS_FLOW_AUTOFOCUS_ON"));

	return TRUE;
}

BOOL CAutoLaserFocusFlow::Stop()
{
	m_bStopBit = TRUE;
	return TRUE;
}

UINT CAutoLaserFocusFlow::ThreadFunction(LPVOID lpParam)
{
	CAutoLaserFocusFlow* pFlow = NULL;

	pFlow = (CAutoLaserFocusFlow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}

VOID CAutoLaserFocusFlow::ThreadFunctionEntry(VOID)
{
	DWORD	dwResult = 0;
	double	dStrt_Time = GetTickCount();
	double	dEnd_Time = GetTickCount();
	double	dWait_Time = GetTickCount();
	int		nWork_Mask_Mode = -1;
	int		nWork_Mask_Index = -1;
	BOOL	bComplete_Step = FALSE;
	DWORD	dPrevTime, dCurrentTime;
	int nHour, nMin, nSec;
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	CString Str = _T("");

	while (m_FlowFinish)
	{
		WaitForSingleObject(hHandle, INFINITE);
		ResetEvent(hHandle);

		if (SharedInfo::bMachineStopFlag == TRUE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(_eAUTO_LASER_FOCUS_FLOW_IDLE);
			continue;
		}
		
		switch (GetCurrentTotalStep())
		{
		case _eAUTO_LASER_FOCUS_FLOW_IDLE:
		{
			break;
		}
		case _eAUTO_LASER_FOCUS_FLOW_START:
		{
			SetStep(_eAUTO_LASER_FOCUS_FLOW_CONNECT_CHECK, _T("_eAUTO_LASER_FOCUS_FLOW_CONNECT_CHECK"));
			break;
		}

		case _eAUTO_LASER_FOCUS_FLOW_CONNECT_CHECK:
		{
			if (pDlg->m_pSystemDlg->m_pLLC4AFDlg->IsATFSerialConnection()
				&& pDlg->m_pSystemDlg->m_pLLC4AFDlg->IsLLCSerialConnection())
			{
				SetStep(_eAUTO_LASER_FOCUS_FLOW_MOTOR_CHECK, _T("_eAUTO_LASER_FOCUS_FLOW_MOTOR_CHECK"));
			}
			else
			{
				Total_Msg(_T("LLC Not Connect !!!"));
				SetStep(_eAUTO_LASER_FOCUS_FLOW_ERROR, _T("_eAUTO_LASER_FOCUS_FLOW_ERROR"));
			}
			SetTimeOut(TIME_OUT_DEFAULT);
			break;
		}
		case _eAUTO_LASER_FOCUS_FLOW_MOTOR_CHECK:

			if (pDlg->m_pSystemDlg->m_pLLC4AFDlg->LLCGetMotorStatus())
			{
				SetStep(_eAUTO_LASER_FOCUS_FLOW_MOTOR_HOME_STATUS_CHECK, _T("_eAUTO_LASER_FOCUS_FLOW_MOTOR_HOME_STATUS_CHECK"));
			}
			else
			{
				SetStep(_eAUTO_LASER_FOCUS_FLOW_MOTOR_ON, _T("_eAUTO_LASER_FOCUS_FLOW_MOTOR_ON"));
			}

			SetTimeOut(TIME_OUT_DEFAULT);
			break;

		case _eAUTO_LASER_FOCUS_FLOW_MOTOR_HOME_STATUS_CHECK:

			if (pDlg->m_pSystemDlg->m_pLLC4AFDlg->LLCGetHomeStatus() > 0)
			{
				SetStep(_eAUTO_LASER_FOCUS_FLOW_DEFAULT_CAMERA_CHECK, _T("_eAUTO_LASER_FOCUS_FLOW_DEFAULT_CAMERA_CHECK"));
			}
			else
			{
				SetStep(_eAUTO_LASER_FOCUS_FLOW_MOTOR_HOME, _T("_eAUTO_LASER_FOCUS_FLOW_MOTOR_HOME"));
			}

			SetTimeOut(TIME_OUT_DEFAULT);
			break;

		case _eAUTO_LASER_FOCUS_FLOW_MOTOR_ON:

			pDlg->m_pSystemDlg->m_pLLC4AFDlg->OnBnClickedLlcMotorOn();

			SetStep(_eAUTO_LASER_FOCUS_FLOW_MOTOR_ON_CHECK, _T("_eAUTO_LASER_FOCUS_FLOW_MOTOR_ON_CHECK"));
			SetTimeOut(TIME_OUT_DEFAULT);
			break;

		case _eAUTO_LASER_FOCUS_FLOW_MOTOR_ON_CHECK:
			if (pDlg->m_pSystemDlg->m_pLLC4AFDlg->LLCGetMotorStatus())
			{
				SetStep(_eAUTO_LASER_FOCUS_FLOW_MOTOR_HOME, _T("_eAUTO_LASER_FOCUS_FLOW_MOTOR_HOME"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eAUTO_LASER_FOCUS_FLOW_ERROR, _T("_eAUTO_LASER_FOCUS_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eAUTO_LASER_FOCUS_FLOW_MOTOR_ON_CHECK, _T("_eAUTO_LASER_FOCUS_FLOW_MOTOR_ON_CHECK"));
			}
			break;


		case _eAUTO_LASER_FOCUS_FLOW_MOTOR_HOME:

			pDlg->m_pSystemDlg->m_pLLC4AFDlg->OnBnClickedLlcHome();

			SetStep(_eAUTO_LASER_FOCUS_FLOW_MOTOR_HOME_CHECK, _T("_eAUTO_LASER_FOCUS_FLOW_MOTOR_HOME_CHECK"));
			SetTimeOut(TIME_OUT_DEFAULT);
			break;

		case _eAUTO_LASER_FOCUS_FLOW_MOTOR_HOME_CHECK:
			if (pDlg->m_pSystemDlg->m_pLLC4AFDlg->LLCGetHomeStatus() > 0)
			{
				SetStep(_eAUTO_LASER_FOCUS_FLOW_DEFAULT_CAMERA_CHECK, _T("_eAUTO_LASER_FOCUS_FLOW_DEFAULT_CAMERA_CHECK"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eAUTO_LASER_FOCUS_FLOW_ERROR, _T("_eAUTO_LASER_FOCUS_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eAUTO_LASER_FOCUS_FLOW_MOTOR_HOME_CHECK, _T("_eAUTO_LASER_FOCUS_FLOW_MOTOR_HOME_CHECK"));
			}
			break;

		case _eAUTO_LASER_FOCUS_FLOW_DEFAULT_CAMERA_CHECK:

			if (pDlg->m_pSystemDlg->m_pLLC4AFDlg->LLCGetCurrentObjective() < 0)
			{
				SetStep(_eAUTO_LASER_FOCUS_FLOW_DEFAULT_CAMERA_SET, _T("_eAUTO_LASER_FOCUS_FLOW_DEFAULT_CAMERA_SET"));
			}
			else
			{
				SetStep(_eAUTO_LASER_FOCUS_FLOW_LASER_CHECK, _T("_eAUTO_LASER_FOCUS_FLOW_LASER_CHECK"));
			}
			SetTimeOut(TIME_OUT_DEFAULT);
			break;


		case _eAUTO_LASER_FOCUS_FLOW_DEFAULT_CAMERA_SET:

			pDlg->m_pSystemDlg->m_pLLC4AFDlg->OnBnClickedLlc1();

			SetStep(_eAUTO_LASER_FOCUS_FLOW_DEFAULT_CAMERA_SET_CHECK, _T("_eAUTO_LASER_FOCUS_FLOW_DEFAULT_CAMERA_SET_CHECK"));
			SetTimeOut(TIME_OUT_DEFAULT);
			break;

		case _eAUTO_LASER_FOCUS_FLOW_DEFAULT_CAMERA_SET_CHECK:
			if (pDlg->m_pSystemDlg->m_pLLC4AFDlg->LLCGetCurrentObjective() == 0)
			{
				SetStep(_eAUTO_LASER_FOCUS_FLOW_LASER_CHECK, _T("_eAUTO_LASER_FOCUS_FLOW_LASER_CHECK"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eAUTO_LASER_FOCUS_FLOW_ERROR, _T("_eAUTO_LASER_FOCUS_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eAUTO_LASER_FOCUS_FLOW_DEFAULT_CAMERA_SET_CHECK, _T("_eAUTO_LASER_FOCUS_FLOW_DEFAULT_CAMERA_SET_CHECK"));
			}
			break;




		case _eAUTO_LASER_FOCUS_FLOW_LASER_CHECK:

			if (pDlg->m_pSystemDlg->m_pLLC4AFDlg->GetLaserOnStatus())
			{
				m_bReadyDone = TRUE;

				SetStep(_eAUTO_LASER_FOCUS_FLOW_DONE, _T("_eAUTO_LASER_FOCUS_FLOW_DONE"));
			}
			else
			{
				SetStep(_eAUTO_LASER_FOCUS_FLOW_LASER_ON, _T("_eAUTO_LASER_FOCUS_FLOW_LASER_ON"));
			}
			SetTimeOut(TIME_OUT_DEFAULT);
			break;


		case _eAUTO_LASER_FOCUS_FLOW_LASER_ON:

			pDlg->m_pSystemDlg->m_pLLC4AFDlg->OnBnClickedLaserOn();

			SetStep(_eAUTO_LASER_FOCUS_FLOW_LASER_ON_CHECK, _T("_eAUTO_LASER_FOCUS_FLOW_LASER_ON_CHECK"));
			SetTimeOut(TIME_OUT_DEFAULT);
			break;

		case _eAUTO_LASER_FOCUS_FLOW_LASER_ON_CHECK:
			if (pDlg->m_pSystemDlg->m_pLLC4AFDlg->GetLaserOnStatus())
			{
				m_bReadyDone = TRUE;
				SetStep(_eAUTO_LASER_FOCUS_FLOW_DONE, _T("_eAUTO_LASER_FOCUS_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eAUTO_LASER_FOCUS_FLOW_ERROR, _T("_eAUTO_LASER_FOCUS_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eAUTO_LASER_FOCUS_FLOW_LASER_ON_CHECK, _T("_eAUTO_LASER_FOCUS_FLOW_LASER_ON_CHECK"));
			}
			break;


		case _eAUTO_LASER_FOCUS_FLOW_AUTOFOCUS_ON:
			
			pDlg->m_pSystemDlg->m_pLLC4AFDlg->OnBnClickedAfOn();

			SetStep(_eAUTO_LASER_FOCUS_FLOW_AUTOFOCUS_ON_CHECK, _T("_eAUTO_LASER_FOCUS_FLOW_AUTOFOCUS_ON_CHECK"));
			SetTimeOut(TIME_OUT_DEFAULT);
			break;

		case _eAUTO_LASER_FOCUS_FLOW_AUTOFOCUS_ON_CHECK:
			if (pDlg->m_pSystemDlg->m_pLLC4AFDlg->GetLaserInFocusStatus())
			{
				SetStep(_eAUTO_LASER_FOCUS_FLOW_AUTOFOCUS_OFF, _T("_eAUTO_LASER_FOCUS_FLOW_AUTOFOCUS_OFF"));
			}
			else if (IsTimeOut())
			{
				Total_Msg(_T("Laser Focus Fail !!!"));
				SetStep(_eAUTO_LASER_FOCUS_FLOW_AUTOFOCUS_OFF, _T("_eAUTO_LASER_FOCUS_FLOW_AUTOFOCUS_OFF"));
			}
			else
			{
				SetCheckStep(_eAUTO_LASER_FOCUS_FLOW_AUTOFOCUS_ON_CHECK, _T("_eAUTO_LASER_FOCUS_FLOW_AUTOFOCUS_ON_CHECK"));
			}
			break;


		case _eAUTO_LASER_FOCUS_FLOW_AUTOFOCUS_OFF:

			pDlg->m_pSystemDlg->m_pLLC4AFDlg->OnBnClickedAfOff();

			SetStep(_eAUTO_LASER_FOCUS_FLOW_AUTOFOCUS_OFF_CHECK, _T("_eAUTO_LASER_FOCUS_FLOW_AUTOFOCUS_OFF_CHECK"));
			SetTimeOut(TIME_OUT_DEFAULT);
			break;

		case _eAUTO_LASER_FOCUS_FLOW_AUTOFOCUS_OFF_CHECK:
			if (pDlg->m_pSystemDlg->m_pLLC4AFDlg->GetLaserAFStatus() == FALSE)
			{
				SetStep(_eAUTO_LASER_FOCUS_FLOW_DONE, _T("_eAUTO_LASER_FOCUS_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eAUTO_LASER_FOCUS_FLOW_DONE, _T("_eAUTO_LASER_FOCUS_FLOW_DONE"));
			}
			else
			{
				SetCheckStep(_eAUTO_LASER_FOCUS_FLOW_AUTOFOCUS_OFF_CHECK, _T("_eAUTO_LASER_FOCUS_FLOW_AUTOFOCUS_OFF_CHECK"));
			}
			break;

		case _eAUTO_LASER_FOCUS_FLOW_ERROR:
			
			break;

		case _eAUTO_LASER_FOCUS_FLOW_DONE:
		{
			m_bFlowDone = TRUE;

			//SharedInfo::CalTactTime(_T("AUTO_LASER_FOCUS_FLOW"), m_timeStart); //KJT 20210329
			
			SetStep(_eAUTO_LASER_FOCUS_FLOW_IDLE, _T("_eAUTO_LASER_FOCUS_FLOW_IDLE"));
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