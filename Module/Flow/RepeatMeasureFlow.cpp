#include "stdafx.h"
#include "RepeatMeasureFlow.h"
#include "Log/Logger.h"
#include "Vision/Devs.h"
#include "Data/ModelData.h"
#include "CamAreaModul.h"
#include "Data/SystemData.h"
#include "VisionAgentDlg.h"
#include "FmmLight1.h"
#include "SystemDlg.h"
#include "LLC4_AF_ModuleDlg.h"

CRepeatMeasureFlow::CRepeatMeasureFlow()
{
}


CRepeatMeasureFlow::~CRepeatMeasureFlow()
{
}

BOOL CRepeatMeasureFlow::InitProcess()
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
BOOL CRepeatMeasureFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eREPEAT_MEASURE_FLOW_IDLE);

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

BOOL CRepeatMeasureFlow::Start(REPEAT_DATA RepeatFlagData)
{
	SYSTEMTIME st;
	GetLocalTime(&st);

	TCHAR	exepath[MAX_PATH];
	GetModuleFileName(NULL, exepath, sizeof(exepath));
	path = exepath;
	int i = path.ReverseFind('\\');
	path = path.Left(i);

	CString Str = _T("");
	Str.Format(_T("%s\\Result"), SharedInfo::VisionAgentPath);
	::CreateDirectory(Str, NULL);
	Str.AppendFormat(_T("\\Repeat"));
	::CreateDirectory(Str, NULL);

	if (SharedInfo::m_nRepeatTableCnt == 1)
		path.AppendFormat(_T("\\Result\\Repeat\\Repeat_Stop_%04d%02d%02d%02d%02d%02d.csv"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	else
		path.AppendFormat(_T("\\Result\\Repeat\\Repeat_Move_%04d%02d%02d%02d%02d%02d.csv"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

	memcpy(&m_sRepeatFlagData, &RepeatFlagData, sizeof(REPEAT_DATA));

	SharedInfo::m_nRepeatCurPointIndex = 0;
	if (RepeatFlagData.nRepeat < 1)
		RepeatFlagData.nRepeat = 1; //Default

	SharedInfo::m_nMoveRepeatTarget = RepeatFlagData.nRepeat;
	if (RepeatFlagData.nCountDelay > 5000 || RepeatFlagData.nCountDelay < 0)
		m_nCountDelay = 1000; //Default
	else
		m_nCountDelay = RepeatFlagData.nCountDelay;

	if (RepeatFlagData.nLaserFocusDoneDelay > 5000 || RepeatFlagData.nLaserFocusDoneDelay < 10)
		m_nLaserFocusDoneDelay = 500; //Default
	else
		m_nLaserFocusDoneDelay = RepeatFlagData.nLaserFocusDoneDelay;

	m_nCamNumber = RepeatFlagData.nCamNumber; //!!

	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(_eREPEAT_MEASURE_FLOW_START, _T("_eREPEAT_MEASURE_FLOW_START"));

	return TRUE;
}
BOOL CRepeatMeasureFlow::Stop()
{
	m_bStopBit = TRUE;
	SetStop(); //!!
	return TRUE;
}
UINT CRepeatMeasureFlow::ThreadFunction(LPVOID lpParam)
{
	CRepeatMeasureFlow* pFlow = NULL;

	pFlow = (CRepeatMeasureFlow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}

VOID CRepeatMeasureFlow::ThreadFunctionEntry(VOID)
{
	DWORD	dwResult = 0;
	double	dStrt_Time = GetTickCount();
	double	dEnd_Time = GetTickCount();
	double	dWait_Time = GetTickCount();
	int		nWork_Mask_Mode = -1;
	int		nWork_Mask_Index = -1;
	int     nRtn;
	BOOL	bComplete_Step = FALSE;
	CVisionAgentDlg *pMain = (CVisionAgentDlg*)AfxGetMainWnd();
	CString Str = _T(""), StrAxisName = _T("");
	BOOL bGrabResult = FALSE;
	int nBlackWhite = 0, nBin = 0;
	double dSizeX = 0.0, dSizeY = 0.0, dRadius = 0.0;	
	double dResX = 0.0, dResY = 0.0;

	int nRing, nCoaxial;	
	int nBackLightVal[BACKLIGHT_CH_COUNT] = { BACKLIGHT_OFF_VALUE, };

	while (m_FlowFinish)
	{
		WaitForSingleObject(hHandle, INFINITE);
		ResetEvent(hHandle);

		if (SharedInfo::bMachineStopFlag == TRUE)// && m_bStopBit == FALSE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(_eREPEAT_MEASURE_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}

		switch (GetCurrentTotalStep())
		{
		case _eREPEAT_MEASURE_FLOW_IDLE:
		{
			break;
		}
		case _eREPEAT_MEASURE_FLOW_START:
			m_timeStart = CTime::GetCurrentTime(); //KJT 20210329
			m_timeStart_1Cycle = m_timeStart; //KJT 20210417
			SharedInfo::m_timeTotalTact = m_timeStart;
			SharedInfo::m_timeUnitTact = m_timeStart;

			SharedInfo::nCurFlowID = eREPEAT_MEASURE_FLOW;

			SharedInfo::m_nRepeatCurPointIndex = 0;
			SharedInfo::m_nStopRepeatCnt = 0;
			SharedInfo::m_nMoveRepeatCnt = 0;

			SharedInfo::LightAllOff();

			for (int i = 0; i < BACKLIGHT_CH_COUNT; i++)
				nBackLightVal[i] = SharedInfo::m_sRepeatTable[0].nZoomBackLight;

			SetStep(_eREPEAT_MEASURE_FLOW_INTERLOCK_CHECK, _T("_eREPEAT_MEASURE_FLOW_INTERLOCK_CHECK"));
			break;

		case _eREPEAT_MEASURE_FLOW_INTERLOCK_CHECK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(_eREPEAT_MEASURE_FLOW_ERROR, _T("_eREPEAT_MEASURE_FLOW_ERROR"));
			}
			else
			{
				SetStep(_eREPEAT_MEASURE_FLOW_UNLOADER_READY, _T("_eREPEAT_MEASURE_FLOW_UNLOADER_READY"));
			}
			break;

#pragma region //Unloader Ready
		case _eREPEAT_MEASURE_FLOW_UNLOADER_READY:
			Devs::m_Ready_UnloaderFlow.Start();

			SetStep(_eREPEAT_MEASURE_FLOW_UNLOADER_READY_CHECK, _T("_eREPEAT_MEASURE_FLOW_UNLOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eREPEAT_MEASURE_FLOW_UNLOADER_READY_CHECK:
			if (Devs::m_Ready_UnloaderFlow.IsFlowDone())
			{
				SetStep(_eREPEAT_MEASURE_FLOW_GANTRY_ZX_READY, _T("_eREPEAT_MEASURE_FLOW_GANTRY_ZX_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eREPEAT_MEASURE_FLOW_UNLOADER_READY_CHECK : Time Out"), eREPEAT_MEASURE_FLOW + 0);
				SetStep(_eREPEAT_MEASURE_FLOW_ERROR, _T("_eREPEAT_MEASURE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eREPEAT_MEASURE_FLOW_UNLOADER_READY_CHECK, _T("_eREPEAT_MEASURE_FLOW_UNLOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Gantry Z,X Ready
		case _eREPEAT_MEASURE_FLOW_GANTRY_ZX_READY:
			Devs::m_Ready_GantryZX_Flow.Start();

			SetStep(_eREPEAT_MEASURE_FLOW_GANTRY_ZX_READY_CHECK, _T("_eREPEAT_MEASURE_FLOW_GANTRY_ZX_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eREPEAT_MEASURE_FLOW_GANTRY_ZX_READY_CHECK:
			if (Devs::m_Ready_GantryZX_Flow.IsFlowDone())
			{
				SetStep(_eREPEAT_MEASURE_FLOW_LOADER_READY, _T("_eREPEAT_MEASURE_FLOW_LOADER_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eREPEAT_MEASURE_FLOW_GANTRY_ZX_READY_CHECK : Time Out"), eREPEAT_MEASURE_FLOW + 2);
				SetStep(_eREPEAT_MEASURE_FLOW_ERROR, _T("_eREPEAT_MEASURE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eREPEAT_MEASURE_FLOW_GANTRY_ZX_READY_CHECK, _T("_eREPEAT_MEASURE_FLOW_GANTRY_ZX_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Loader Ready
		case _eREPEAT_MEASURE_FLOW_LOADER_READY:
			Devs::m_Ready_LoaderFlow.Start();

			SetStep(_eREPEAT_MEASURE_FLOW_LOADER_READY_CHECK, _T("_eREPEAT_MEASURE_FLOW_LOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eREPEAT_MEASURE_FLOW_LOADER_READY_CHECK:
			if (Devs::m_Ready_LoaderFlow.IsFlowDone())
			{
				SetStep(_eREPEAT_MEASURE_FLOW_INSPECTION_POS_CHECK, _T("_eREPEAT_MEASURE_FLOW_INSPECTION_POS_CHECK"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eREPEAT_MEASURE_FLOW_LOADER_READY_CHECK : Time Out"), eREPEAT_MEASURE_FLOW + 1);
				SetStep(_eREPEAT_MEASURE_FLOW_ERROR, _T("_eREPEAT_MEASURE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eREPEAT_MEASURE_FLOW_LOADER_READY_CHECK, _T("_eREPEAT_MEASURE_FLOW_LOADER_READY_CHECK"));
			}
			break;
#pragma endregion

		case _eREPEAT_MEASURE_FLOW_INSPECTION_POS_CHECK:
			if (SharedInfo::m_nStopRepeatCnt < SharedInfo::m_sRepeatTable[SharedInfo::m_nRepeatCurPointIndex].nCount)
			{
				if (SharedInfo::m_nStopRepeatCnt == 0)
					SetStep(_eREPEAT_MEASURE_FLOW_LIGHT_ON, _T("_eREPEAT_MEASURE_FLOW_LIGHT_ON"));
				else
				{
					if (SharedInfo::m_sRepeatTable[SharedInfo::m_nRepeatCurPointIndex].nFocus == eFocusType_Laser ||
						SharedInfo::m_sRepeatTable[SharedInfo::m_nRepeatCurPointIndex].nFocus == eFocusType_Both)
						SetStep(_eREPEAT_MEASURE_FLOW_LASER_FOCUS_START, _T("_eREPEAT_MEASURE_FLOW_LASER_FOCUS_START"));
					else if (SharedInfo::m_sRepeatTable[SharedInfo::m_nRepeatCurPointIndex].nFocus == eFocusType_Image)
						SetStep(_eREPEAT_MEASURE_FLOW_IMAGE_FOCUS_START, _T("_eREPEAT_MEASURE_FLOW_IMAGE_FOCUS_START"));
					else
						SetStep(_eREPEAT_MEASURE_FLOW_GRAB, _T("_eREPEAT_MEASURE_FLOW_GRAB"));
				}

				Str.Format(_T("Repeat:%d/%d, Move:%d/%d, Stop:%d/%d"), 
					SharedInfo::m_nMoveRepeatCnt + 1, SharedInfo::m_nMoveRepeatTarget, SharedInfo::m_nRepeatCurPointIndex + 1, SharedInfo::m_nRepeatTableCnt, SharedInfo::m_nStopRepeatCnt + 1, SharedInfo::m_sRepeatTable[SharedInfo::m_nRepeatCurPointIndex].nCount);
				Total_Msg(Str);
			}
			else
			{
				SharedInfo::m_nStopRepeatCnt = 0;
				SharedInfo::m_nRepeatCurPointIndex++;
				if (SharedInfo::m_nRepeatCurPointIndex < SharedInfo::m_nRepeatTableCnt)
				{
					SetStep(_eREPEAT_MEASURE_FLOW_LIGHT_ON, _T("_eREPEAT_MEASURE_FLOW_LIGHT_ON"));

					Str.Format(_T("Repeat:%d/%d, Move:%d/%d, Stop:%d/%d"),
						SharedInfo::m_nMoveRepeatCnt + 1, SharedInfo::m_nMoveRepeatTarget, SharedInfo::m_nRepeatCurPointIndex + 1, SharedInfo::m_nRepeatTableCnt, SharedInfo::m_nStopRepeatCnt + 1, SharedInfo::m_sRepeatTable[SharedInfo::m_nRepeatCurPointIndex].nCount);
					Total_Msg(Str);
				}
				else if (SharedInfo::m_nMoveRepeatCnt < SharedInfo::m_nMoveRepeatTarget - 1)
				{
					SharedInfo::m_nMoveRepeatCnt++;

					SharedInfo::m_nStopRepeatCnt = 0;
					SharedInfo::m_nRepeatCurPointIndex = 0;

					Str.Format(_T("Repeat:%d/%d, Move:%d/%d, Stop:%d/%d"),
						SharedInfo::m_nMoveRepeatCnt + 1, SharedInfo::m_nMoveRepeatTarget, SharedInfo::m_nRepeatCurPointIndex + 1, SharedInfo::m_nRepeatTableCnt, SharedInfo::m_nStopRepeatCnt + 1, SharedInfo::m_sRepeatTable[SharedInfo::m_nRepeatCurPointIndex].nCount);
					Total_Msg(Str);

					SetStep(_eREPEAT_MEASURE_FLOW_LIGHT_ON, _T("_eREPEAT_MEASURE_FLOW_LIGHT_ON"));
				}
				else
				{
					//21.02.24 sjc
					SharedInfo::LightAllOff();

					SetStep(_eREPEAT_MEASURE_FLOW_GANTRY_Z_FINISH_POS, _T("_eREPEAT_MEASURE_FLOW_GANTRY_Z_FINISH_POS"));
				}
			}
			break;

		case _eREPEAT_MEASURE_FLOW_LIGHT_ON: //KJT 20210728
			for (int i = 0; i < BACKLIGHT_CH_COUNT; i++)
				nBackLightVal[i] = SharedInfo::m_sRepeatTable[SharedInfo::m_nRepeatCurPointIndex].nZoomBackLight;

			nRing = SharedInfo::m_sRepeatTable[SharedInfo::m_nRepeatCurPointIndex].nZoomRing;
			nCoaxial = SharedInfo::m_sRepeatTable[SharedInfo::m_nRepeatCurPointIndex].nZoomCoaxial;

#if 0
			if (m_nCamNumber == eViewReview10X)
			{
				// 21.02.24 sjc
				g_CommReview_Light.SetLight_Review(nRing, nCoaxial);
				Sleep(50);
				g_CommBack_Light.BackLightOn(nBackLightVal);
				//
				//g_CommLight_8ch.SetLight_Review_Coaxial(SharedInfo::m_sRepeatTable[SharedInfo::m_nRepeatCurPointIndex].nZoomCoaxial);
				//g_CommLight_12ch.SetLight_Review_Ring(SharedInfo::m_sRepeatTable[SharedInfo::m_nRepeatCurPointIndex].nZoomRing);
				////for (int i = 0; i < BACKLIGHT_CH_COUNT; i++)
				////	nBackLightVal[i] = SharedInfo::m_sRepeatTable[SharedInfo::m_nRepeatCurPointIndex].nZoomBackLight;

				//g_CommMLCLedLight.BackLightOn(nBackLightVal);
				Str.Format(_T("BackLight On. 0:%d, 1:%d, 2:%d, 3:%d, 4:%d, 5:%d, 6:%d, 7:%d"), nBackLightVal[0], nBackLightVal[1], nBackLightVal[2],
					nBackLightVal[3], nBackLightVal[4], nBackLightVal[5], nBackLightVal[6], nBackLightVal[7]);
				Total_Msg(Str);
			}
			else if (m_nCamNumber == eViewReview20X)
			{
				//pMain->m_pSystemDlg->m_pLLC4AFDlg->OnBnClickedLlc2(); //KJT 20210727

				for (int i = 0; i < BACKLIGHT_CH_COUNT; i++)
					nBackLightVal[i] *= CModelData::m_AlignPara.Info.dx20BackLightScale;

				nRing *= CModelData::m_AlignPara.Info.dx20RingScale;
				nCoaxial *= CModelData::m_AlignPara.Info.dx20CoAxialScale;

				g_CommReview_Light.SetLight_Review(nRing, nCoaxial);
				Sleep(50);
				g_CommBack_Light.BackLightOn(nBackLightVal);

				Str.Format(_T("BackLight On. 0:%d, 1:%d, 2:%d, 3:%d, 4:%d, 5:%d, 6:%d, 7:%d"), nBackLightVal[0], nBackLightVal[1], nBackLightVal[2],
					nBackLightVal[3], nBackLightVal[4], nBackLightVal[5], nBackLightVal[6], nBackLightVal[7]);
				Total_Msg(Str);
			}
			else if (m_nCamNumber == eViewReview50X)
			{
				//pMain->m_pSystemDlg->m_pLLC4AFDlg->OnBnClickedLlc3(); //KJT 20210727

				for (int i = 0; i < BACKLIGHT_CH_COUNT; i++)
					nBackLightVal[i] *= CModelData::m_AlignPara.Info.dx50BackLightScale;

				nRing *= CModelData::m_AlignPara.Info.dx50RingScale;
				nCoaxial *= CModelData::m_AlignPara.Info.dx50CoAxialScale;

				g_CommReview_Light.SetLight_Review(nRing, nCoaxial);
				Sleep(50);
				g_CommBack_Light.BackLightOn(nBackLightVal);

				Str.Format(_T("BackLight On. 0:%d, 1:%d, 2:%d, 3:%d, 4:%d, 5:%d, 6:%d, 7:%d"), nBackLightVal[0], nBackLightVal[1], nBackLightVal[2],
					nBackLightVal[3], nBackLightVal[4], nBackLightVal[5], nBackLightVal[6], nBackLightVal[7]);
				Total_Msg(Str);
			}
#else //KJT 20210824
			if (m_nCamNumber != eViewPreAlign)
			{
				// 21.02.24 sjc
				g_CommReview_Light.SetLight_Review(nRing, nCoaxial);
				Sleep(50);
				g_CommBack_Light.BackLightOn(nBackLightVal);
				//
				//g_CommLight_8ch.SetLight_Review_Coaxial(SharedInfo::m_sRepeatTable[SharedInfo::m_nRepeatCurPointIndex].nZoomCoaxial);
				//g_CommLight_12ch.SetLight_Review_Ring(SharedInfo::m_sRepeatTable[SharedInfo::m_nRepeatCurPointIndex].nZoomRing);
				////for (int i = 0; i < BACKLIGHT_CH_COUNT; i++)
				////	nBackLightVal[i] = SharedInfo::m_sRepeatTable[SharedInfo::m_nRepeatCurPointIndex].nZoomBackLight;

				//g_CommMLCLedLight.BackLightOn(nBackLightVal);
				Str.Format(_T("BackLight On. 0:%d, 1:%d, 2:%d, 3:%d, 4:%d, 5:%d, 6:%d, 7:%d"), nBackLightVal[0], nBackLightVal[1], nBackLightVal[2],
					nBackLightVal[3], nBackLightVal[4], nBackLightVal[5], nBackLightVal[6], nBackLightVal[7]);
				Total_Msg(Str);
			}
#endif
			else if (m_nCamNumber == eViewPreAlign)
			{
				//g_CommZomm_Ring.SetLight_Zoom_Ring(SharedInfo::m_sRepeatTable[SharedInfo::m_nRepeatCurPointIndex].nPreRing);
				//Sleep(20);
				//g_CommZomm_Ring.Zoom_Light_On(TRUE);
				//Sleep(20);
				//g_CommZomm_Coaxial.SetLight_Zoom_Ring(SharedInfo::m_sRepeatTable[SharedInfo::m_nRepeatCurPointIndex].nPreCoaxial);
				//Sleep(20);
				//g_CommZomm_Coaxial.Zoom_Light_On(TRUE);
				//g_CommLight_8ch.SetLight_PreAlign(SharedInfo::m_sRepeatTable[SharedInfo::m_nRepeatCurPointIndex].nPreCoaxial, SharedInfo::m_sRepeatTable[SharedInfo::m_nRepeatCurPointIndex].nPreRing);
				g_CommLoader_Light.SetLight_PreAlign(SharedInfo::m_sRepeatTable[SharedInfo::m_nRepeatCurPointIndex].nPreCoaxial, SharedInfo::m_sRepeatTable[SharedInfo::m_nRepeatCurPointIndex].nPreRing); //KJT 20210728
			}

			SetStep(_eREPEAT_MEASURE_FLOW_GANTRY_XY_INSPECTION_POS, _T("_eREPEAT_MEASURE_FLOW_GANTRY_XY_INSPECTION_POS"));
			break;

		case _eREPEAT_MEASURE_FLOW_GANTRY_XY_INSPECTION_POS:
			if (m_nCamNumber == eViewReview10X || m_nCamNumber == eViewReview20X)
			{
				m_dTargetPosX = SharedInfo::m_sRepeatTable[SharedInfo::m_nRepeatCurPointIndex].dPosX;
				m_dTargetPosY = SharedInfo::m_sRepeatTable[SharedInfo::m_nRepeatCurPointIndex].dPosY;
			}
			else if (m_nCamNumber == eViewPreAlign)
			{
				m_dTargetPosX = SharedInfo::m_sRepeatTable[SharedInfo::m_nRepeatCurPointIndex].dPosX - CSystemData::m_Coordinate.Info.dOffsetReview10xToPreAlign_X;
				m_dTargetPosY = SharedInfo::m_sRepeatTable[SharedInfo::m_nRepeatCurPointIndex].dPosY - CSystemData::m_Coordinate.Info.dOffsetReview10xToPreAlign_Y;
			}

			if (SharedInfo::m_sRepeatTable[SharedInfo::m_nRepeatCurPointIndex].nZoomBackLight > 0)
				m_bWithBackLightXMove = TRUE;
			else
				m_bWithBackLightXMove = FALSE;

			Devs::m_GantryMotion.Move_Gantry_X_Pos(m_dTargetPosX, m_bWithBackLightXMove);
			Sleep(20); //!!
			Devs::m_GantryMotion.Move_Gantry_Y_Pos(m_dTargetPosY);
			Sleep(20); //!!

			SetStep(_eREPEAT_MEASURE_FLOW_GANTRY_XY_INSPECTION_POS_CHECK, _T("_eREPEAT_MEASURE_FLOW_GANTRY_XY_INSPECTION_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eREPEAT_MEASURE_FLOW_GANTRY_XY_INSPECTION_POS_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Pos(m_dTargetPosX) && Devs::m_GantryMotion.Is_Gantry_Y_Pos(m_dTargetPosY))
			{
				if (m_bWithBackLightXMove)
				{
					if (Devs::m_InspectionStageMotion.Is_BackLight_X_Pos(m_dTargetPosX))
					{
						Sleep(100); //!!

						m_nGrabRetryCnt = 0;
						SetStep(_eREPEAT_MEASURE_FLOW_GANTRY_Z_INSPECTION_POS, _T("_eREPEAT_MEASURE_FLOW_GANTRY_Z_INSPECTION_POS"));
					}
					else if (IsTimeOut())
					{
						SharedInfo::SetAlarm(_T("_eREPEAT_MEASURE_FLOW_GANTRY_XY_INSPECTION_POS_CHECK : BackLight Pos"), eREPEAT_MEASURE_FLOW + 3);
						SetStep(_eREPEAT_MEASURE_FLOW_ERROR, _T("_eREPEAT_MEASURE_FLOW_ERROR"));
					}
					else
					{
						SetCheckStep(_eREPEAT_MEASURE_FLOW_GANTRY_XY_INSPECTION_POS_CHECK, _T("_eREPEAT_MEASURE_FLOW_GANTRY_XY_INSPECTION_POS_CHECK"));
					}
				}
				else
				{
					Sleep(100); //!!

					m_nGrabRetryCnt = 0;
					SetStep(_eREPEAT_MEASURE_FLOW_GANTRY_Z_INSPECTION_POS, _T("_eREPEAT_MEASURE_FLOW_GANTRY_Z_INSPECTION_POS"));
				}			
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eREPEAT_MEASURE_FLOW_GANTRY_XY_INSPECTION_POS_CHECK : Time Out"), eREPEAT_MEASURE_FLOW + 4);
				SetStep(_eREPEAT_MEASURE_FLOW_ERROR, _T("_eREPEAT_MEASURE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eREPEAT_MEASURE_FLOW_GANTRY_XY_INSPECTION_POS_CHECK, _T("_eREPEAT_MEASURE_FLOW_GANTRY_XY_INSPECTION_POS_CHECK"));
			}
			break;

		case _eREPEAT_MEASURE_FLOW_GANTRY_Z_INSPECTION_POS:
			m_dTargetPosZ = SharedInfo::m_sRepeatTable[SharedInfo::m_nRepeatCurPointIndex].dPosZ;
			//Devs::m_GantryMotion.Move_Gantry_Z1_Pos(m_dTargetPosZ);
			Devs::m_GantryMotion.Move_GantryZ1_Pos(m_dTargetPosZ);
			Sleep(100);

			SetStep(_eREPEAT_MEASURE_FLOW_GANTRY_Z_INSPECTION_POS_CHECK, _T("_eREPEAT_MEASURE_FLOW_GANTRY_Z_INSPECTION_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eREPEAT_MEASURE_FLOW_GANTRY_Z_INSPECTION_POS_CHECK:
			if (Devs::m_GantryMotion.Is_Move_GantryZ1_Pos(m_dTargetPosZ))
			{
				//21.02.24 sjc
				//Sleep(1000); //!!			
				Sleep(100); //!!			

				if (m_nCamNumber == eViewPreAlign)
				{
					SetStep(_eREPEAT_MEASURE_FLOW_GRAB, _T("_eREPEAT_MEASURE_FLOW_GRAB"));
				}
				else
				{
					//sunghaklee
					//if (SharedInfo::m_nStopRepeatCnt == 0)
					//{
					//	SetStep(_eREPEAT_MEASURE_FLOW_LASER_FOCUS_START, _T("_eREPEAT_MEASURE_FLOW_LASER_FOCUS_START"));
					//}
					//else // if (SharedInfo::m_nStopRepeatCnt > 0)
					{
						if (SharedInfo::m_sRepeatTable[SharedInfo::m_nRepeatCurPointIndex].nFocus == eFocusType_Both
							|| SharedInfo::m_sRepeatTable[SharedInfo::m_nRepeatCurPointIndex].nFocus == eFocusType_Laser)
							SetStep(_eREPEAT_MEASURE_FLOW_LASER_FOCUS_START, _T("_eREPEAT_MEASURE_FLOW_LASER_FOCUS_START"));
						else if (SharedInfo::m_sRepeatTable[SharedInfo::m_nRepeatCurPointIndex].nFocus == eFocusType_Image)
							SetStep(_eREPEAT_MEASURE_FLOW_IMAGE_FOCUS_START, _T("_eREPEAT_MEASURE_FLOW_IMAGE_FOCUS_START"));						
						else
							SetStep(_eREPEAT_MEASURE_FLOW_GRAB, _T("_eREPEAT_MEASURE_FLOW_GRAB"));
					}
				}
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eREPEAT_MEASURE_FLOW_GANTRY_Z_INSPECTION_POS_CHECK : Time Out"), eREPEAT_MEASURE_FLOW + 5);
				SetStep(_eREPEAT_MEASURE_FLOW_ERROR, _T("_eREPEAT_MEASURE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eREPEAT_MEASURE_FLOW_GANTRY_Z_INSPECTION_POS_CHECK, _T("_eREPEAT_MEASURE_FLOW_GANTRY_Z_INSPECTION_POS_CHECK"));
			}
			break;
			
		case _eREPEAT_MEASURE_FLOW_LASER_FOCUS_START:
			Devs::m_GantryMotion.LaserFocusMove(SharedInfo::m_nIsGlassMode);//Glass

			if (SharedInfo::m_nStopRepeatCnt == 0 || SharedInfo::m_nMoveRepeatCnt == 0)
			{
				Sleep(10);
			}
			else
			{
				Sleep(10);
			}

			SetStep(_eREPEAT_MEASURE_FLOW_LASER_FOCUS_CHECK, _T("_eREPEAT_MEASURE_FLOW_LASER_FOCUS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eREPEAT_MEASURE_FLOW_LASER_FOCUS_CHECK:
			if (Devs::m_GantryMotion.LaserFocusMoveCheck())
			{
				Str.Format(_T("Laser Focus Done Delay %.3fsec"), m_nLaserFocusDoneDelay * 0.001);
				Total_Msg(Str);
				Sleep(m_nLaserFocusDoneDelay); //!!	

				//sunghaklee
				//if (SharedInfo::m_nStopRepeatCnt == 0)
				//	SetStep(_eREPEAT_MEASURE_FLOW_IMAGE_FOCUS_START, _T("_eREPEAT_MEASURE_FLOW_IMAGE_FOCUS_START"));
				//else
				{
					if (SharedInfo::m_sRepeatTable[SharedInfo::m_nRepeatCurPointIndex].nFocus == eFocusType_Both)
						SetStep(_eREPEAT_MEASURE_FLOW_IMAGE_FOCUS_START, _T("_eREPEAT_MEASURE_FLOW_IMAGE_FOCUS_START"));
					else
						SetStep(_eREPEAT_MEASURE_FLOW_GRAB, _T("_eREPEAT_MEASURE_FLOW_GRAB"));
				}
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eREPEAT_MEASURE_FLOW_LASER_FOCUS_CHECK : Time Out"), eREPEAT_MEASURE_FLOW + 6);
				SetStep(_eREPEAT_MEASURE_FLOW_ERROR, _T("_eREPEAT_MEASURE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eREPEAT_MEASURE_FLOW_LASER_FOCUS_CHECK, _T("_eREPEAT_MEASURE_FLOW_LASER_FOCUS_CHECK"));
			}
			break;

		case _eREPEAT_MEASURE_FLOW_IMAGE_FOCUS_START:
#ifndef SIM_MODE
			//if (CModelData::m_InspectionPara.Info.nMeasureCameraMode == eViewReview20X)
			//{
			//	g_pReview20x->m_bAfEnd = FALSE;
			//	g_pReview20x->AutofoucsRun(eViewReview20X);
			//}
			//else
			{
				g_pReview10x->m_bAfEnd = FALSE;
				g_pReview10x->AutofoucsRun();
			}
#endif
			SetStep(_eREPEAT_MEASURE_FLOW_IMAGE_FOCUS_CHECK, _T("_eREPEAT_MEASURE_FLOW_IMAGE_FOCUS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eREPEAT_MEASURE_FLOW_IMAGE_FOCUS_CHECK:
#ifndef SIM_MODE

			//if (CModelData::m_InspectionPara.Info.nMeasureCameraMode == eViewReview20X)
			//{
			//	nRtn = g_pReview20x->m_bAfEnd;
			//}
			//else
			{
				nRtn = g_pReview10x->m_bAfEnd;
			}

			if (nRtn == TRUE)
			{
				Sleep(IMAGE_FOCUS_DELAY);
				SetStep(_eREPEAT_MEASURE_FLOW_GRAB, _T("_eREPEAT_MEASURE_FLOW_GRAB"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eREPEAT_MEASURE_FLOW_IMAGE_FOCUS_CHECK : Time Out"), eREPEAT_MEASURE_FLOW + 7);
				SetStep(_eREPEAT_MEASURE_FLOW_ERROR, _T("_eREPEAT_MEASURE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eREPEAT_MEASURE_FLOW_IMAGE_FOCUS_CHECK, _T("_eREPEAT_MEASURE_FLOW_IMAGE_FOCUS_CHECK"));
			}
#else
			Sleep(IMAGE_FOCUS_DELAY);
			SetStep(_eREPEAT_MEASURE_FLOW_GRAB, _T("_eREPEAT_MEASURE_FLOW_GRAB"));
#endif
			break;

		case _eREPEAT_MEASURE_FLOW_GRAB:
			m_dGrabValue[0] = 0;
			m_dGrabValue[1] = 0;
#ifndef SIM_MODE
			if (SharedInfo::m_sRepeatTable[SharedInfo::m_nRepeatCurPointIndex].nFindType == eFind_Circle)
			{
				dRadius = SharedInfo::m_sRepeatTable[SharedInfo::m_nRepeatCurPointIndex].dSizeX / 2;
				Devs::m_GantryMotion.RepeatFindCircle(m_nCamNumber, dRadius, &m_dGrabValue[0], &m_dGrabValue[1], &m_dGrabScore);
				Total_Msg(_T("FindCircle"));
			}
			else if (SharedInfo::m_sRepeatTable[SharedInfo::m_nRepeatCurPointIndex].nFindType == eFind_Blob)
			{
				nBlackWhite = SharedInfo::m_sRepeatTable[SharedInfo::m_nRepeatCurPointIndex].nFind;
				nBin = SharedInfo::m_sRepeatTable[SharedInfo::m_nRepeatCurPointIndex].nThreshold;
				dSizeX = SharedInfo::m_sRepeatTable[SharedInfo::m_nRepeatCurPointIndex].dSizeX;
				dSizeY = SharedInfo::m_sRepeatTable[SharedInfo::m_nRepeatCurPointIndex].dSizeY;
				
				Devs::m_GantryMotion.RepeatFindBlob(m_nCamNumber, nBlackWhite, nBin, dSizeX, dSizeY, &m_dGrabValue[0], &m_dGrabValue[1]);
				Total_Msg(_T("FindBlob"));
			}
			else if (SharedInfo::m_sRepeatTable[SharedInfo::m_nRepeatCurPointIndex].nFindType == eFind_PPA)
			{
				/////////////////////////////////////////
#ifndef SIM_MODE
#if 0
				if (CModelData::m_InspectionPara.Info.nMeasureCameraMode == eViewReview20X)
				{
					m_CameraInfo = Devs::m_Camera20X->GetCameraInfo();

					m_CameraInfo.nBlackWhite = CModelData::m_PpaPara.Info.nPpaBlackWhiteType;
					m_CameraInfo.nBin = CModelData::m_PpaPara.Info.nPpaThreshold;
					Devs::m_Camera20X->SetCameraInfo(m_CameraInfo);
					m_BlobData = Devs::m_Camera20X->GetBlobData();

					if (CModelData::m_InspectionPara.Info.nStickTensionUseMode == eSTICK_TENSION_ALIGN)
					{
						m_BlobData.dMarkSizeX = CModelData::m_AtMaterialPara.Info.dSlotSizeX[0][0];
						m_BlobData.dMarkSizeY = CModelData::m_AtMaterialPara.Info.dSlotSizeY[0][0];
						m_BlobData.dPitchX = CModelData::m_AtMaterialPara.Info.dSlotPitchX[0][0];
						m_BlobData.dPitchY = CModelData::m_AtMaterialPara.Info.dSlotPitchY[0][0];
					}
					else
					{
						m_BlobData.dMarkSizeX = CModelData::m_MaterialPara.Info.dSlotSizeX[0][0];
						m_BlobData.dMarkSizeY = CModelData::m_MaterialPara.Info.dSlotSizeY[0][0];
						m_BlobData.dPitchX = CModelData::m_MaterialPara.Info.dSlotPitchX[0][0];
						m_BlobData.dPitchY = CModelData::m_MaterialPara.Info.dSlotPitchY[0][0];
					}

					//KJT 20210308
					m_BlobData.nQuantityX = CModelData::m_PpaPara.Info.nDivX + 1; //KJT 20210726
					m_BlobData.nQuantityY = CModelData::m_PpaPara.Info.nDivY + 1;

					m_BlobData.dRangeRateX = 0.8;
					m_BlobData.dRangeRateY = 0.8;

					Devs::m_Camera20X->SetBlobData(m_BlobData);
					stResult = Devs::m_Camera20X->FindBlobPpa();
				}
				else
				{
					m_CameraInfo = Devs::m_Camera10X->GetCameraInfo();

					m_CameraInfo.nBlackWhite = CModelData::m_PpaPara.Info.nPpaBlackWhiteType;
					m_CameraInfo.nBin = CModelData::m_PpaPara.Info.nPpaThreshold;
					Devs::m_Camera10X->SetCameraInfo(m_CameraInfo);
					m_BlobData = Devs::m_Camera10X->GetBlobData();

					if (CModelData::m_InspectionPara.Info.nStickTensionUseMode == eSTICK_TENSION_ALIGN)
					{
						m_BlobData.dMarkSizeX = CModelData::m_AtMaterialPara.Info.dSlotSizeX[0][0];
						m_BlobData.dMarkSizeY = CModelData::m_AtMaterialPara.Info.dSlotSizeY[0][0];
						m_BlobData.dPitchX = CModelData::m_AtMaterialPara.Info.dSlotPitchX[0][0];
						m_BlobData.dPitchY = CModelData::m_AtMaterialPara.Info.dSlotPitchY[0][0];
					}
					else
					{
						m_BlobData.dMarkSizeX = CModelData::m_MaterialPara.Info.dSlotSizeX[0][0];
						m_BlobData.dMarkSizeY = CModelData::m_MaterialPara.Info.dSlotSizeY[0][0];
						m_BlobData.dPitchX = CModelData::m_MaterialPara.Info.dSlotPitchX[0][0];
						m_BlobData.dPitchY = CModelData::m_MaterialPara.Info.dSlotPitchY[0][0];
					}

					//KJT 20210308
					m_BlobData.nQuantityX = CModelData::m_PpaPara.Info.nDivX + 1; //KJT 20210726
					m_BlobData.nQuantityY = CModelData::m_PpaPara.Info.nDivY + 1;

					m_BlobData.dRangeRateX = 0.8;
					m_BlobData.dRangeRateY = 0.8;

					Devs::m_Camera10X->SetBlobData(m_BlobData);
					stResult = Devs::m_Camera10X->FindBlobPpa();
				}
#else //KJT 20210726
					m_CameraInfo = Devs::m_Camera10X->GetCameraInfo();

					m_CameraInfo.nBlackWhite = SharedInfo::m_sRepeatTable[SharedInfo::m_nRepeatCurPointIndex].nFind;
					m_CameraInfo.nBin = SharedInfo::m_sRepeatTable[SharedInfo::m_nRepeatCurPointIndex].nThreshold;

#if 0//KJT 20210728 Junying
					SharedInfo::GetReviewCamResolution(m_nCamNumber, &dResX, &dResY);
					m_CameraInfo.dResolX = dResX;
					m_CameraInfo.dResolY = dResY;
#endif

					Devs::m_Camera10X->SetCameraInfo(m_CameraInfo);
					m_BlobData = Devs::m_Camera10X->GetBlobData();

					m_BlobData.dMarkSizeX = SharedInfo::m_sRepeatTable[SharedInfo::m_nRepeatCurPointIndex].dSizeX;
					m_BlobData.dMarkSizeY = SharedInfo::m_sRepeatTable[SharedInfo::m_nRepeatCurPointIndex].dSizeY;
					m_BlobData.dPitchX = CModelData::m_AtMaterialPara.Info.dSlotPitchX[0][0];
					m_BlobData.dPitchY = CModelData::m_AtMaterialPara.Info.dSlotPitchY[0][0];

					//KJT 20210721
					//SharedInfo::GetSlotQtyXY(&m_BlobData.nQuantityX, &m_BlobData.nQuantityY);
					m_BlobData.nQuantityX = 1;
					m_BlobData.nQuantityY = 1;

					m_BlobData.dRangeRateX = 0.8;
					m_BlobData.dRangeRateY = 0.8;

					Devs::m_Camera10X->SetBlobData(m_BlobData);
					stResult = Devs::m_Camera10X->FindBlobPpa2(); //KJT 20210727
#endif

				if (stResult.bResult == FALSE) //KJT 20210404
				{
					SetStep(_eREPEAT_MEASURE_FLOW_ERROR, _T("_eREPEAT_MEASURE_FLOW_ERROR"));
				}

				m_dGrabValue[0] = stResult.dPosX;
				m_dGrabValue[1] = stResult.dPosY;

				m_AlignVisionResultCdValue[0] = stResult.dCdX;
				m_AlignVisionResultCdValue[1] = stResult.dCdY;


				for (int j = 0; j < m_BlobData.nQuantityX * m_BlobData.nQuantityY; j++) //KJT 20210726
				{
					for (int k = 0; k < 4; k++)
					{
						m_AlignVisionResultCornerRValue[j][k] = Devs::m_Camera10X->m_dCornerRadius[j][k];
					}
				}
#endif
				////////////////////////////////////////////////
			}
#else
			m_dGrabValue[0] = 0.0;
			m_dGrabValue[1] = 0.0;
			m_dGrabScore = 100.0;
#endif

			bGrabResult = TRUE;
			if (m_dGrabValue[0] == 0 && m_dGrabValue[1] == 0 && m_dGrabScore == 0)
			{
				bGrabResult = FALSE;
				m_nGrabRetryCnt++;
			}

			m_RepeatInfo[0].dRefPosX = SharedInfo::m_sRepeatTable[SharedInfo::m_nRepeatCurPointIndex].dPosX;
			m_RepeatInfo[0].dRefPosY = SharedInfo::m_sRepeatTable[SharedInfo::m_nRepeatCurPointIndex].dPosY;
			m_RepeatInfo[0].dRefPosZ = SharedInfo::GetCmdPos(AXIS_CAMERA_Z1);

			m_RepeatInfo[0].dFindX = m_dGrabValue[0];
			m_RepeatInfo[0].dFindY = m_dGrabValue[1];

			if (m_nGrabRetryCnt > 4)
			if (m_nGrabRetryCnt > 4)
			{
				SetStep(_eREPEAT_MEASURE_FLOW_ERROR, _T("_eREPEAT_MEASURE_FLOW_ERROR"));
				break;
			}

			if (bGrabResult == FALSE)
			{
				SetStep(_eREPEAT_MEASURE_FLOW_LASER_FOCUS_START, _T("_eREPEAT_MEASURE_FLOW_LASER_FOCUS_START"));
				break;
			}

			SaveRepeatResult(m_RepeatInfo, SharedInfo::m_nMoveRepeatCnt, SharedInfo::m_nRepeatCurPointIndex, SharedInfo::m_nStopRepeatCnt);
			SharedInfo::m_nStopRepeatCnt++;

			if (m_nCountDelay > 0)
			{
				Str.Format(_T("Count Delay %.3fsec"), m_nCountDelay * 0.001);
				Total_Msg(Str);
				Sleep(m_nCountDelay); //!!
			}

			SetStep(_eREPEAT_MEASURE_FLOW_INSPECTION_POS_CHECK, _T("_eREPEAT_MEASURE_FLOW_INSPECTION_POS_CHECK"));			
			break;

		case _eREPEAT_MEASURE_FLOW_GANTRY_Z_FINISH_POS:
			Devs::m_GantryMotion.Move_GantryZ1_Wait_Pos();

			SetStep(_eREPEAT_MEASURE_FLOW_GANTRY_Z_FINISH_POS_CHECK, _T("_eREPEAT_MEASURE_FLOW_GANTRY_Z_FINISH_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eREPEAT_MEASURE_FLOW_GANTRY_Z_FINISH_POS_CHECK:
			if (Devs::m_GantryMotion.Is_GantryZ1_Wait_Pos())
			{
				SetStep(_eREPEAT_MEASURE_FLOW_GANTRY_X_FINISH_POS, _T("_eREPEAT_MEASURE_FLOW_GANTRY_X_FINISH_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eREPEAT_MEASURE_FLOW_GANTRY_Z_FINISH_POS_CHECK : Time Out"), eREPEAT_MEASURE_FLOW + 8);
				SetStep(_eREPEAT_MEASURE_FLOW_ERROR, _T("_eREPEAT_MEASURE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eREPEAT_MEASURE_FLOW_GANTRY_Z_FINISH_POS_CHECK, _T("_eREPEAT_MEASURE_FLOW_GANTRY_Z_FINISH_POS_CHECK"));
			}
			break;

		case _eREPEAT_MEASURE_FLOW_GANTRY_X_FINISH_POS:
			Devs::m_GantryMotion.Move_Gantry_X_Wait_Pos();

			SetStep(_eREPEAT_MEASURE_FLOW_GANTRY_X_FINISH_POS_CHECK, _T("_eREPEAT_MEASURE_FLOW_GANTRY_X_FINISH_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eREPEAT_MEASURE_FLOW_GANTRY_X_FINISH_POS_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Wait_Pos())
			{
				SetStep(_eREPEAT_MEASURE_FLOW_DONE, _T("_eREPEAT_MEASURE_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eREPEAT_MEASURE_FLOW_GANTRY_X_FINISH_POS_CHECK : Time Out"), eREPEAT_MEASURE_FLOW + 9);
				SetStep(_eREPEAT_MEASURE_FLOW_ERROR, _T("_eREPEAT_MEASURE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eREPEAT_MEASURE_FLOW_GANTRY_X_FINISH_POS_CHECK, _T("_eREPEAT_MEASURE_FLOW_GANTRY_X_FINISH_POS_CHECK"));
			}
			break;

		case _eREPEAT_MEASURE_FLOW_ERROR:
			break;

		case _eREPEAT_MEASURE_FLOW_DONE:
		{
			m_bFlowDone = TRUE;

			SharedInfo::CalTactTime(_T("REPEAT_MEASURE_FLOW"), m_timeStart); //KJT 20210329

			SetStep(_eREPEAT_MEASURE_FLOW_IDLE, _T("_eREPEAT_MEASURE_FLOW_IDLE"));
			break;
		}
		default:
		{
			break;
		}
		}

		//Sleep(100); //!!
		Sleep(10); //!!
	}
}

BOOL CRepeatMeasureFlow::FlowInterlock()
{
	/////////////////////////////////////////////////////////////////////////////
	if (Devs::m_GantryMotion.CheckGantryXYZFlowInterlock(_T("RepeatMeasureFlow"), eREPEAT_MEASURE_FLOW, 20) == FALSE)
	{
		return FALSE;
	}

//21.02.24 sjc temp del
//#pragma region	//Loader Vac Check
//	for (i = 0; i < 5; i++)
//	{
//		if (SharedInfo::DInputValue[_DIN_LD_STICK_VAC_1 + i])
//		{
//			Str.Format(_T("Check Loader DIn Stick Vac_%d Status !!!"), i + 1);
//			Total_Msg(Str);
//			return FALSE;
//		}
//		if (SharedInfo::DOutputValue[_DOUT_LD_STICK_VAC_1 + i])
//		{
//			Str.Format(_T("Check Loader DOut Stick Vac_%d Status !!!"), i + 1);
//			Total_Msg(Str);
//			return FALSE;
//		}
//
//		if (i < 4)
//		{
//			if (i == 0 && SharedInfo::DInputValue[_DIN_LD_PAPER_VAC_1])
//			{
//				Str.Format(_T("Check Loader DIn Paper Vac_1_2 Status !!!"));
//				Total_Msg(Str);
//				return FALSE;
//			}
//			else if (i == 0 && SharedInfo::DOutputValue[_DOUT_LD_PAPER_VAC_1])
//			{
//				Str.Format(_T("Check Loader DOut Vac_1_2 Status !!!"));
//				Total_Msg(Str);
//				return FALSE;
//			}
//			else if (SharedInfo::DInputValue[_DIN_LD_PAPER_VAC_1 + i])
//			{
//				Str.Format(_T("Check Loader DIn Paper Vac_%d Status !!!"), i );
//				Total_Msg(Str);
//				return FALSE;
//			}
//			else if (SharedInfo::DOutputValue[_DOUT_LD_PAPER_VAC_1 + i])
//			{
//				Str.Format(_T("Check Loader DOut Paper Vac_%d Status !!!"), i );
//				Total_Msg(Str);
//				return FALSE;
//			}
//		}
//	}
//#pragma endregion
//
//#pragma region	//Unloader Vac Check
//	for (i = 0; i < 5; i++)
//	{
//		if (SharedInfo::DInputValue[_DIN_ULD_STICK_VAC_1 + i])
//		{
//			Str.Format(_T("Check Unloader DIn Stick Vac_%d Status !!!"), i + 1);
//			Total_Msg(Str);
//			return FALSE;
//		}
//		if (SharedInfo::DOutputValue[_DOUT_ULD_STICK_VAC_1 + i])
//		{
//			Str.Format(_T("Check Unloader DOut Stick Vac_%d Status !!!"), i + 1);
//			Total_Msg(Str);
//			return FALSE;
//		}
//	}
//#pragma endregion
//
//#pragma region //Pickup Unit, CST
//	if (Devs::m_CassetteMotion.Is_CSTPickUpUnitBwd() == FALSE)
//	{
//		Total_Msg(_T("Check Pickup Unit Backward !!!"));
//		return FALSE;
//	}
//	if (SharedInfo::DInputValue[_DIN_MAGAZINE_SAFETY_POS_DETECT_2])
//	{
//		Total_Msg(_T("Check CST Unsafe Pos Detect Sensor !!!"));
//		return FALSE;
//	}
//	if (SharedInfo::DInputValue[_DIN_MAGAZINE_EXIST_DETECT_1])
//	{
//		Total_Msg(_T("Check CST Backward Detect Sensor !!!"));
//		return FALSE;
//	}
//#pragma endregion

	return TRUE;
}

#if 0
int CRepeatMeasureFlow::SaveRepeatResult(REPEAT_INFO resinfo[4], int Repeat, int Position, int Count)
{
	CString strLastCnt;

	SYSTEMTIME st;

	GetLocalTime(&st);

	CStdioFile f, flog;
	CString str;
	CString StrTitle;
	string strMaskID[100];
	CString strTemp = path;
	int nQtyX = 0, nQtyY = 0;

	SharedInfo::GetSlotQtyXY(&nQtyX, &nQtyY); //KJT 20210729
	nQtyX = 1;
	nQtyY = 1;

	if (!f.Open(strTemp, CFile::modeWrite | CFile::modeNoTruncate | CFile::shareDenyNone))
	{
		if (f.Open(strTemp, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyNone))
		{			
			StrTitle.Format(_T("Date, Repeat, Position, Count, PosX, PosY, PosZ, FindX, FindY"));

			for (int i = 0; i < 12; i++)
			{
				StrTitle.AppendFormat(_T(", Temp%d"), i + 1);
			}
			StrTitle.AppendFormat(_T("\n"));
			f.WriteString(StrTitle);
		}

		else {

			TRACE("File Open Faile~!!\r\n");

			return false;
		}
	}

	f.SeekToEnd();
	str.Format(_T("%04d%02d%02d_%02d%02d%02d"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

	str.AppendFormat(_T(", %d, %d, %d"), Repeat, Position, Count);
	str.AppendFormat(_T(", %.8f, %.8f, %.8f, %.8f, %.8f"), resinfo[0].dRefPosX, resinfo[0].dRefPosY, resinfo[0].dRefPosZ, resinfo[0].dFindX, resinfo[0].dFindY);

	for (int i = 0; i < 12; i++)
	{
		str.AppendFormat(_T(", %.2f"), g_CommTempTur.m_dTempValue[i]);
	}

	str.AppendFormat(_T("\n"));

	if (SharedInfo::m_sRepeatTable[Position].nFindType == eFind_PPA)
	{
		//CD X
		str.AppendFormat(_T("CDX\n"));
		for (int i = 0; i < nQtyX; i++) //KJT 20210726
		{
			str.AppendFormat(_T(", %d, %d, %d, "), Repeat, Position, Count);

			//for (int j = 0; j < Devs::m_GantryMotion.m_nMaxCellCntX; j++)
			//{			
			for (int k = 0; k < nQtyY; k++) //KJT 20210726
			{
				if (CModelData::m_InspectionPara.Info.nStickTensionUseMode == eSTICK_TENSION_ALIGN) //KJT 20210406
					//str.AppendFormat(_T("%10.5f,"), (CModelData::m_AtMaterialPara.Info.dSlotSizeX[0][0] - m_AlignVisionResultCdValue[0]) * 1000);
					str.AppendFormat(_T("%10.5f,"), (m_AlignVisionResultCdValue[0]) * 1000);
				else
					//str.AppendFormat(_T("%10.5f,"), (CModelData::m_MaterialPara.Info.dSlotSizeX[0][0] - m_AlignVisionResultCdValue[0]) * 1000);
					str.AppendFormat(_T("%10.5f,"), (m_AlignVisionResultCdValue[0]) * 1000);
			}
			//}

			str.AppendFormat(_T("\n"));
		}

		//CD Y
		str.AppendFormat(_T("CDY\n"));
		for (int i = 0; i < nQtyX; i++) //KJT 20210726
		{
			str.AppendFormat(_T(", %d, %d, %d, "), Repeat, Position, Count);

			//for (int j = 0; j < Devs::m_GantryMotion.m_nMaxCellCntX; j++)
			//{
			for (int k = 0; k < nQtyY; k++) //KJT 20210726
			{
				if (CModelData::m_InspectionPara.Info.nStickTensionUseMode == eSTICK_TENSION_ALIGN) //KJT 20210406
					//str.AppendFormat(_T("%10.5f,"), (CModelData::m_AtMaterialPara.Info.dSlotSizeY[0][0] - m_AlignVisionResultCdValue[1]) * 1000);
					str.AppendFormat(_T("%10.5f,"), (m_AlignVisionResultCdValue[1]) * 1000);
				else
					//str.AppendFormat(_T("%10.5f,"), (CModelData::m_MaterialPara.Info.dSlotSizeY[0][0] - m_AlignVisionResultCdValue[1]) * 1000);
					str.AppendFormat(_T("%10.5f,"), (m_AlignVisionResultCdValue[1]) * 1000);
			}
			//}
			str.AppendFormat(_T("\n"));
		}

		//Corner R
		str.AppendFormat(_T("Corner_R\n"));
		str.AppendFormat(_T(", %d, %d, %d, "), Repeat, Position, Count);
		for (int j = 0; j < (nQtyX * nQtyY); j++) //KJT 20210726
		{
			for (int k = 0; k < 4; k++)
			{
				str.AppendFormat(_T("%10.5f,"), m_AlignVisionResultCornerRValue[j][k] * 1000);
			}
		}

		str.AppendFormat(_T("\n"));
	}


	f.WriteString(str);

	
	f.Close();

	return 0;
}
#else //KJT 20210729
int CRepeatMeasureFlow::SaveRepeatResult(REPEAT_INFO resinfo[4], int Repeat, int Position, int Count)
{
	CString strLastCnt;

	SYSTEMTIME st;

	GetLocalTime(&st);

	CStdioFile f, flog;
	CString str;
	CString StrTitle;
	string strMaskID[100];
	CString strTemp = path;
	int nQtyX = 0, nQtyY = 0;

	SharedInfo::GetSlotQtyXY(&nQtyX, &nQtyY); //KJT 20210729

	if (!f.Open(strTemp, CFile::modeWrite | CFile::modeNoTruncate | CFile::shareDenyNone))
	{
		if (f.Open(strTemp, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyNone))
		{
			if (SharedInfo::m_sRepeatTable[Position].nFindType == eFind_PPA)
				StrTitle.Format(_T("Date, Repeat, Position, Count, PosX, PosY, PosZ, FindX, FindY, CDX, CDY, Corner_R1, Corner_R2, Corner_R3, Corner_R4"));
			else
				StrTitle.Format(_T("Date, Repeat, Position, Count, PosX, PosY, PosZ, FindX, FindY"));

			for (int i = 0; i < 12; i++)
			{
				StrTitle.AppendFormat(_T(", Temp%d"), i + 1);
			}
			StrTitle.AppendFormat(_T("\n"));
			f.WriteString(StrTitle);
		}

		else {

			TRACE("File Open Faile~!!\r\n");

			return false;
		}
	}

	f.SeekToEnd();
	str.Format(_T("%04d%02d%02d_%02d%02d%02d"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

	str.AppendFormat(_T(", %d, %d, %d"), Repeat, Position, Count);
	str.AppendFormat(_T(", %.8f, %.8f, %.8f, %.8f, %.8f"), resinfo[0].dRefPosX, resinfo[0].dRefPosY, resinfo[0].dRefPosZ, resinfo[0].dFindX, resinfo[0].dFindY);

	if (SharedInfo::m_sRepeatTable[Position].nFindType == eFind_PPA)
	{
		//CD XY
		str.AppendFormat(_T(",%10.5f"), (m_AlignVisionResultCdValue[0]) * 1000);
		str.AppendFormat(_T(",%10.5f"), (m_AlignVisionResultCdValue[1]) * 1000);

		//Corner R
		for (int j = 0; j < (nQtyX * nQtyY); j++) //KJT 20210726
		{
			for (int k = 0; k < 4; k++)
			{
				str.AppendFormat(_T(",%10.5f"), m_AlignVisionResultCornerRValue[j][k] * 1000);
			}
		}
	}

	for (int i = 0; i < 12; i++)
	{
		str.AppendFormat(_T(", %.2f"), g_CommTempTur.m_dTempValue[i]);
	}

	str.AppendFormat(_T("\n"));

	f.WriteString(str);


	f.Close();

	return 0;
}
#endif
void CRepeatMeasureFlow::FindBlob()
{
#ifndef SIM_MODE
	//wk_MilCameraInfo CameraInfo;
	//wk_MilBlobData	BlobData;

	//if (m_nCamNumber == eRepeat_PreAlign)
	//{
	//	CameraInfo = Devs::m_CameraPreAlign->GetCameraInfo();
	//	CameraInfo.nBlackWhite = 1;
	//	CameraInfo.nBin = 100; // CModelData::m_PpaPara.Info.nPpaThreshold; //200;
	//	Devs::m_CameraPreAlign->SetCameraInfo(CameraInfo);

	//	BlobData = Devs::m_CameraPreAlign->GetBlobData();
	//	BlobData.dMarkSizeX = CModelData::m_MaterialPara.Info.dTegkey_SizeX; // 0.045; //TagKeyX
	//	BlobData.dMarkSizeY = CModelData::m_MaterialPara.Info.dTegkey_SizeY; //0.050; //TagKeyY
	//	Devs::m_CameraPreAlign->SetBlobData(BlobData);
	//	//Devs::m_CameraPreAlign->FindBlobInspect();
	//	Devs::m_CameraPreAlign->FindBlobTegKey();
	//	BlobData = Devs::m_CameraPreAlign->GetBlobData();
	//}
	//else //Review10X
	//{
	//	CameraInfo = Devs::m_Camera10X->GetCameraInfo();
	//	CameraInfo.nBlackWhite = 1;
	//	CameraInfo.nBin = 100; // CModelData::m_PpaPara.Info.nPpaThreshold; //200;
	//	Devs::m_Camera10X->SetCameraInfo(CameraInfo);

	//	BlobData = Devs::m_Camera10X->GetBlobData();
	//	BlobData.dMarkSizeX = CModelData::m_MaterialPara.Info.dTegkey_SizeX; // 0.045; //TagKeyX
	//	BlobData.dMarkSizeY = CModelData::m_MaterialPara.Info.dTegkey_SizeY; //0.050; //TagKeyY
	//	Devs::m_Camera10X->SetBlobData(BlobData);
	//	//Devs::m_Camera10X->FindBlobInspect();
	//	Devs::m_Camera10X->FindBlobTagKey();
	//	BlobData = Devs::m_Camera10X->GetBlobData();
	//}

	//m_dGrabValue[0] = BlobData.dPosX;
	//m_dGrabValue[1] = BlobData.dPosY;
#else
	m_dGrabValue[0] = 0.0;
	m_dGrabValue[1] = 0.0;
#endif
}