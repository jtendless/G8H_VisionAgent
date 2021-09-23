#include "stdafx.h"
#include "GlassFlatnessFlow.h"
#include "Log/Logger.h"
#include "Vision/Devs.h"
#include "Data/ModelData.h"
#include "CamAreaModul.h"
#include "Data/SystemData.h"
#include "FmmLight1.h"

CGlassFlatnessFlow::CGlassFlatnessFlow()
{
	m_nCurRepeatCount = 0;
	m_nMaxRepeatCount = 0;
	m_nMeasurePoint = 0;
}


CGlassFlatnessFlow::~CGlassFlatnessFlow()
{
}

BOOL CGlassFlatnessFlow::InitProcess()
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
	//pMappingProc = CMappingProc::GetInstance();
	return TRUE;
}

BOOL CGlassFlatnessFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(eGLASS_FLATNESS_FLOW_IDLE, FALSE);

	if (hHandle != NULL)
	{
		CloseHandle(hHandle);
		hHandle = NULL;
	}

	return TRUE;
}

BOOL CGlassFlatnessFlow::StateStop()
{
	SetStop();
	return TRUE;
}

BOOL CGlassFlatnessFlow::Start()
{
	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;

	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(eGLASS_FLATNESS_FLOW_START, _T("eGLASS_FLATNESS_FLOW_START"));
	return TRUE;
}

BOOL CGlassFlatnessFlow::Stop()
{
	m_bStopBit = TRUE;
	SetCurrentStep(eGLASS_FLATNESS_FLOW_IDLE); //KJT 20210318
	return TRUE;
}

UINT CGlassFlatnessFlow::ThreadFunction(LPVOID lpParam)
{
	CGlassFlatnessFlow* pRightAngle = NULL;

	pRightAngle = (CGlassFlatnessFlow*)lpParam;

	pRightAngle->ThreadFunctionEntry();

	pRightAngle->m_bTerminate = 1;

	return 0;
}

VOID CGlassFlatnessFlow::ThreadFunctionEntry(VOID)
{
	DWORD	dwResult = 0;
	double	dStrt_Time = GetTickCount();
	double	dEnd_Time = GetTickCount();
	double	dWait_Time = GetTickCount();
	int		nWork_Mask_Mode = -1;
	int		nWork_Mask_Index = -1;
	BOOL	bComplete_Step = FALSE;
	CString Str = _T("");
	double dDiffXTemp = 0.0;
	double dPosX = 0.0, dPosY = 0.0, dPosZ = 0.0;
	//KJT 20210304
	double dVel[3] = { 1.0, 1.0, 1.0 };
	double dAcc[3] = { 2.0, 2.0, 2.0 };
	double dDecel[3] = { 2.0, 2.0, 2.0 };
	int nBackLightVal[BACKLIGHT_CH_COUNT] = { BACKLIGHT_OFF_VALUE, };

	CVisionAgentDlg *pVisionAgentDlg = (CVisionAgentDlg*)AfxGetMainWnd();
	SYSTEMTIME st;

	while (m_FlowFinish)
	{
		WaitForSingleObject(hHandle, INFINITE);
		ResetEvent(hHandle);

		if (SharedInfo::bMachineStopFlag == TRUE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(eGLASS_FLATNESS_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}

		switch (GetCurrentTotalStep())
		{
		case eGLASS_FLATNESS_FLOW_IDLE:
		{
			break;
		}
		case eGLASS_FLATNESS_FLOW_START:
			m_timeStart = CTime::GetCurrentTime(); //KJT 20210329
			SharedInfo::m_timeUnitTact = m_timeStart;

			SharedInfo::nCurFlowID = eGLASS_FLATNESS_FLOW;

#ifndef SIM_MODE
			if (CModelData::m_InspectionPara.Info.bMappingDataUse)
			{
				Devs::m_MappingProc.InitializeGlassMapping(eMAPPING_ID_10X);
				if (Devs::m_MappingProc.LoadGlassMappingFile(eMAPPING_ID_10X) == FALSE)
				{					
					SetStep(eGLASS_FLATNESS_FLOW_ERROR, _T("eGLASS_FLATNESS_FLOW_ERROR"));
					break;
				}
			}
#endif

			SharedInfo::nGantryZ1View = eViewReview10X;

			m_nMeasurePoint = 0;
			m_nCurRepeatCount = 0;
			m_nMaxRepeatCount = Devs::m_GlassFlatnessFlow.m_nMaxRepeatCount;				

			GetLocalTime(&st);
			m_strFilePath.Format(_T("%s\\Result\\Flatness\\Flatness_%04d%02d%02d%02d%02d%02d.csv"), SharedInfo::VisionAgentPath, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

			SharedInfo::LightAllOff();

			//g_CommLight_8ch.SetLight_Review_Coaxial(CModelData::m_AlignPara.Info.nVerticalMainAlignCoAxial);
			//Sleep(20);
			//g_CommLight_12ch.SetLight_Review_Ring(CModelData::m_AlignPara.Info.nVerticalMainAlignRing);

			for (int i = 0; i < BACKLIGHT_CH_COUNT; i++)
				nBackLightVal[i] = SharedInfo::m_nFlatnessBackLight;
			
			//21.02.24 sjc
			g_CommReview_Light.SetLight_Review(SharedInfo::m_nFlatnessLightRing, SharedInfo::m_nFlatnessLightCoaxial);
			Sleep(50);
			g_CommBack_Light.BackLightOn(nBackLightVal);
			Sleep(20);

			SetStep(eGLASS_FLATNESS_FLOW_INTERLOCK, _T("eGLASS_FLATNESS_FLOW_INTERLOCK"));
			break;

		case eGLASS_FLATNESS_FLOW_INTERLOCK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(eGLASS_FLATNESS_FLOW_ERROR, _T("eGLASS_FLATNESS_FLOW_ERROR"));
			}
			else
			{
				SetStep(eGLASS_FLATNESS_FLOW_UNLOADER_READY, _T("eGLASS_FLATNESS_FLOW_UNLOADER_READY"));
			}
			break;

#pragma region //Unloader Ready
		case eGLASS_FLATNESS_FLOW_UNLOADER_READY:
			Devs::m_Ready_UnloaderFlow.Start();

			SetStep(eGLASS_FLATNESS_FLOW_UNLOADER_READY_CHECK, _T("eGLASS_FLATNESS_FLOW_UNLOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eGLASS_FLATNESS_FLOW_UNLOADER_READY_CHECK:
			if (Devs::m_Ready_UnloaderFlow.IsFlowDone())
			{
				SetStep(eGLASS_FLATNESS_FLOW_LOADER_READY, _T("eGLASS_FLATNESS_FLOW_LOADER_READY"));
			}
			else if (IsTimeOut())
			{	
				SharedInfo::SetAlarm(_T("eGLASS_FLATNESS_FLOW_UNLOADER_READY_CHECK : Time Out"), eGLASS_FLATNESS_FLOW + 0);
				SetStep(eGLASS_FLATNESS_FLOW_ERROR, _T("eGLASS_FLATNESS_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eGLASS_FLATNESS_FLOW_UNLOADER_READY_CHECK, _T("eGLASS_FLATNESS_FLOW_UNLOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Loader Ready
		case eGLASS_FLATNESS_FLOW_LOADER_READY:
			Devs::m_Ready_LoaderFlow.Start();

			SetStep(eGLASS_FLATNESS_FLOW_LOADER_READY_CHECK, _T("eGLASS_FLATNESS_FLOW_LOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eGLASS_FLATNESS_FLOW_LOADER_READY_CHECK:
			if (Devs::m_Ready_LoaderFlow.IsFlowDone())
			{
				//SetStep(eGLASS_FLATNESS_FLOW_BOX_CAMERA_READY, _T("eGLASS_FLATNESS_FLOW_BOX_CAMERA_READY"));
				SetStep(eGLASS_FLATNESS_FLOW_GANTRY_ZX_READY, _T("eGLASS_FLATNESS_FLOW_GANTRY_ZX_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eGLASS_FLATNESS_FLOW_LOADER_READY_CHECK : Time Out"), eGLASS_FLATNESS_FLOW + 1);
				SetStep(eGLASS_FLATNESS_FLOW_ERROR, _T("eGLASS_FLATNESS_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eGLASS_FLATNESS_FLOW_LOADER_READY_CHECK, _T("eGLASS_FLATNESS_FLOW_LOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Box Camera Ready
		case eGLASS_FLATNESS_FLOW_BOX_CAMERA_READY:
			Devs::m_BoxMotion.BoxAlignCameraYL_WaitPos();
			Sleep(20);
			Devs::m_BoxMotion.BoxAlignCameraYR_WaitPos();
			Sleep(500); //!!

			SetStep(eGLASS_FLATNESS_FLOW_BOX_CAMERA_READY_CHECK, _T("eGLASS_FLATNESS_FLOW_BOX_CAMERA_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eGLASS_FLATNESS_FLOW_BOX_CAMERA_READY_CHECK:
			if (Devs::m_BoxMotion.Is_BoxAlignCameraYL_WaitPos() == TRUE && Devs::m_BoxMotion.Is_BoxAlignCameraYR_WaitPos() == TRUE)
			{
				SetStep(eGLASS_FLATNESS_FLOW_GANTRY_ZX_READY, _T("eGLASS_FLATNESS_FLOW_GANTRY_ZX_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eGLASS_FLATNESS_FLOW_BOX_CAMERA_READY_CHECK : Time Out"), eGLASS_FLATNESS_FLOW + 2);
				SetStep(eGLASS_FLATNESS_FLOW_ERROR, _T("eGLASS_FLATNESS_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eGLASS_FLATNESS_FLOW_BOX_CAMERA_READY_CHECK, _T("eGLASS_FLATNESS_FLOW_BOX_CAMERA_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Gantry ZX Ready
		case eGLASS_FLATNESS_FLOW_GANTRY_ZX_READY:
			Devs::m_Ready_GantryZX_Flow.Start();

			SetStep(eGLASS_FLATNESS_FLOW_GANTRY_ZX_READY_CHECK, _T("eGLASS_FLATNESS_FLOW_GANTRY_ZX_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eGLASS_FLATNESS_FLOW_GANTRY_ZX_READY_CHECK:
			if (Devs::m_Ready_GantryZX_Flow.IsFlowDone())
			{
				SetStep(eGLASS_FLATNESS_FLOW_AXIS_GANTRY_XY_MEASURE_POS_1ST, _T("eGLASS_FLATNESS_FLOW_AXIS_GANTRY_XY_MEASURE_POS_1ST"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eGLASS_FLATNESS_FLOW_GANTRY_ZX_READY_CHECK : Time Out"), eGLASS_FLATNESS_FLOW + 3);
				SetStep(eGLASS_FLATNESS_FLOW_ERROR, _T("eGLASS_FLATNESS_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eGLASS_FLATNESS_FLOW_GANTRY_ZX_READY_CHECK, _T("eGLASS_FLATNESS_FLOW_GANTRY_ZX_READY_CHECK"));
			}
			break;
#pragma endregion

		case eGLASS_FLATNESS_FLOW_AXIS_GANTRY_XY_MEASURE_POS_1ST:
			m_dTargetPosX = dPosX = SharedInfo::m_sFlatnessTable[m_nMeasurePoint].dPosX;
			m_dTargetPosY = dPosY = SharedInfo::m_sFlatnessTable[m_nMeasurePoint].dPosY;

#ifndef SIM_MODE
			if (CModelData::m_InspectionPara.Info.bMappingDataUse)
			{
				Devs::m_MappingProc.GetGlassMapping_CalibPosXY(eMAPPING_ID_10X, &m_dTargetPosX, &m_dTargetPosY);
				Str.Format(_T("Mapping Data X:%10.5f, Y:%10.5f => X:%10.5f, Y:%10.5f"), dPosX, dPosY, m_dTargetPosX, m_dTargetPosY);
				Total_Msg(Str);
			}
#endif

			Devs::m_GantryMotion.Move_Gantry_X_Pos(m_dTargetPosX, FALSE);
			Sleep(20); //!!
			Devs::m_GantryMotion.Move_Gantry_Y_Pos(m_dTargetPosY);
			Sleep(20); //!!

			SetStep(eGLASS_FLATNESS_FLOW_AXIS_GANTRY_XY_MEASURE_POS_1ST_CHECK, _T("eGLASS_FLATNESS_FLOW_AXIS_GANTRY_XY_MEASURE_POS_1ST_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eGLASS_FLATNESS_FLOW_AXIS_GANTRY_XY_MEASURE_POS_1ST_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Pos(m_dTargetPosX) && Devs::m_GantryMotion.Is_Gantry_Y_Pos(m_dTargetPosY))
			{
				//SetStep(eGLASS_FLATNESS_FLOW_AXIS_CAMERA_Z1_INSPECTION_POS, _T("eGLASS_FLATNESS_FLOW_AXIS_CAMERA_Z1_INSPECTION_POS"));
				SetStep(eGLASS_FLATNESS_FLOW_AXIS_CAMERA_Z3_INSPECTION_POS, _T("eGLASS_FLATNESS_FLOW_AXIS_CAMERA_Z3_INSPECTION_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eGLASS_FLATNESS_FLOW_AXIS_GANTRY_XY_MEASURE_POS_1ST_CHECK : Time Out"), eGLASS_FLATNESS_FLOW + 4);
				SetStep(eGLASS_FLATNESS_FLOW_ERROR, _T("eGLASS_FLATNESS_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eGLASS_FLATNESS_FLOW_AXIS_GANTRY_XY_MEASURE_POS_1ST_CHECK, _T("eGLASS_FLATNESS_FLOW_AXIS_GANTRY_XY_MEASURE_POS_1ST_CHECK"));
			}
			break;

		case eGLASS_FLATNESS_FLOW_AXIS_CAMERA_Z3_INSPECTION_POS:
			//Devs::m_GantryMotion.Move_GantryZ3_InspectionReview_Pos();

			m_dTargetPosZ = dPosZ = SharedInfo::m_sFlatnessTable[m_nMeasurePoint].dPosZ;

			Devs::m_GantryMotion.Move_Gantry_Z1_Pos(m_dTargetPosZ);

			SetStep(eGLASS_FLATNESS_FLOW_AXIS_CAMERA_Z3_INSPECTION_POS_CHECK, _T("eGLASS_FLATNESS_FLOW_AXIS_CAMERA_Z3_INSPECTION_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eGLASS_FLATNESS_FLOW_AXIS_CAMERA_Z3_INSPECTION_POS_CHECK:
			//if (Devs::m_GantryMotion.Is_GantryZ3_InspectionReview_Pos())
			if (Devs::m_GantryMotion.Is_Gantry_Z1_Pos(m_dTargetPosZ))
			{
				Sleep(500); //!!
				SetStep(eGLASS_FLATNESS_FLOW_AUTOFOCUS_CHECK, _T("eGLASS_FLATNESS_FLOW_AUTOFOCUS_CHECK"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eGLASS_FLATNESS_FLOW_AXIS_CAMERA_Z3_INSPECTION_POS_CHECK : Time Out"), eGLASS_FLATNESS_FLOW + 5);
				SetStep(eGLASS_FLATNESS_FLOW_ERROR, _T("eGLASS_FLATNESS_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eGLASS_FLATNESS_FLOW_AXIS_CAMERA_Z3_INSPECTION_POS_CHECK, _T("eGLASS_FLATNESS_FLOW_AXIS_CAMERA_Z3_INSPECTION_POS_CHECK"));
			}
			break;

		case eGLASS_FLATNESS_FLOW_AXIS_GANTRY_XY_MEASURE_POS_2ND:
			m_dTargetPosX = dPosX = SharedInfo::m_sFlatnessTable[m_nMeasurePoint].dPosX;
			m_dTargetPosY = dPosY = SharedInfo::m_sFlatnessTable[m_nMeasurePoint].dPosY;

#ifndef SIM_MODE
			if (CModelData::m_InspectionPara.Info.bMappingDataUse)
			{
				Devs::m_MappingProc.GetGlassMapping_CalibPosXY(eMAPPING_ID_10X, &m_dTargetPosX, &m_dTargetPosY);
				Str.Format(_T("Mapping Data X:%10.5f, Y:%10.5f => X:%10.5f, Y:%10.5f"), dPosX, dPosY, m_dTargetPosX, m_dTargetPosY);
				Total_Msg(Str);
			}
#endif

			Devs::m_GantryMotion.Move_Gantry_X_Pos(m_dTargetPosX, FALSE);
			Sleep(20); //!!
			Devs::m_GantryMotion.Move_Gantry_Y_Pos(m_dTargetPosY);
			Sleep(20); //!!

			SetStep(eGLASS_FLATNESS_FLOW_AXIS_GANTRY_XY_MEASURE_POS_2ND_CHECK, _T("eGLASS_FLATNESS_FLOW_AXIS_GANTRY_XY_MEASURE_POS_2ND_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eGLASS_FLATNESS_FLOW_AXIS_GANTRY_XY_MEASURE_POS_2ND_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Pos(m_dTargetPosX) && Devs::m_GantryMotion.Is_Gantry_Y_Pos(m_dTargetPosY))
			{
				//SetStep(eGLASS_FLATNESS_FLOW_AUTOFOCUS_CHECK, _T("eGLASS_FLATNESS_FLOW_AUTOFOCUS_CHECK"));
				SetStep(eGLASS_FLATNESS_FLOW_AXIS_CAMERA_Z3_INSPECTION_POS, _T("eGLASS_FLATNESS_FLOW_AXIS_CAMERA_Z3_INSPECTION_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eGLASS_FLATNESS_FLOW_AXIS_GANTRY_XY_MEASURE_POS_2ND_CHECK : Time Out"), eGLASS_FLATNESS_FLOW + 6);
				SetStep(eGLASS_FLATNESS_FLOW_ERROR, _T("eGLASS_FLATNESS_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eGLASS_FLATNESS_FLOW_AXIS_GANTRY_XY_MEASURE_POS_2ND_CHECK, _T("eGLASS_FLATNESS_FLOW_AXIS_GANTRY_XY_MEASURE_POS_2ND_CHECK"));
			}
			break;


		case eGLASS_FLATNESS_FLOW_AUTOFOCUS_CHECK:
			if (SharedInfo::m_nFlatnessTool == eFocusType_Laser || SharedInfo::m_nFlatnessTool == eFocusType_Both)
				SetStep(eGLASS_FLATNESS_FLOW_LASER_FOCUS_START, _T("eGLASS_FLATNESS_FLOW_LASER_FOCUS_START"));
			else if (SharedInfo::m_nFlatnessTool == eFocusType_Image)
				SetStep(eGLASS_FLATNESS_FLOW_IMAGE_FOCUS_START, _T("eGLASS_FLATNESS_FLOW_IMAGE_FOCUS_START"));
			else
				SetStep(eGLASS_FLATNESS_FLOW_MEASURE_LASER_FOCUS_VALUE, _T("eGLASS_FLATNESS_FLOW_MEASURE_LASER_FOCUS_VALUE"));
			break;

		case eGLASS_FLATNESS_FLOW_LASER_FOCUS_START:
			Devs::m_GantryMotion.LaserFocusMove();

			SetStep(eGLASS_FLATNESS_FLOW_LASER_FOCUS_CHECK, _T("eGLASS_FLATNESS_FLOW_LASER_FOCUS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eGLASS_FLATNESS_FLOW_LASER_FOCUS_CHECK:
			if (Devs::m_GantryMotion.LaserFocusMoveCheck())
			{
				Sleep(500); //!!	//KJT 20210321

				if (SharedInfo::m_nFlatnessTool == eFocusType_Both)
					SetStep(eGLASS_FLATNESS_FLOW_IMAGE_FOCUS_START, _T("eGLASS_FLATNESS_FLOW_IMAGE_FOCUS_START"));
				else
					SetStep(eGLASS_FLATNESS_FLOW_MEASURE_LASER_FOCUS_VALUE, _T("eGLASS_FLATNESS_FLOW_MEASURE_LASER_FOCUS_VALUE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eGLASS_FLATNESS_FLOW_LASER_FOCUS_CHECK : Time Out"), eGLASS_FLATNESS_FLOW + 7);
				SetStep(eGLASS_FLATNESS_FLOW_ERROR, _T("eGLASS_FLATNESS_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eGLASS_FLATNESS_FLOW_LASER_FOCUS_CHECK, _T("eGLASS_FLATNESS_FLOW_LASER_FOCUS_CHECK"));
			}
			break;

		case eGLASS_FLATNESS_FLOW_IMAGE_FOCUS_START:
#ifndef SIM_MODE
			g_pReview10x->m_bAfEnd = FALSE;
			g_pReview10x->AutofoucsRun();
#endif
			SetStep(eGLASS_FLATNESS_FLOW_IMAGE_FOCUS_CHECK, _T("eGLASS_FLATNESS_FLOW_IMAGE_FOCUS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eGLASS_FLATNESS_FLOW_IMAGE_FOCUS_CHECK:
#ifndef SIM_MODE
			if (g_pReview10x->m_bAfEnd == TRUE)
			{
				Sleep(IMAGE_FOCUS_DELAY);
				SetStep(eGLASS_FLATNESS_FLOW_MEASURE_LASER_FOCUS_VALUE, _T("eGLASS_FLATNESS_FLOW_MEASURE_LASER_FOCUS_VALUE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eGLASS_FLATNESS_FLOW_IMAGE_FOCUS_CHECK : Time Out"), eGLASS_FLATNESS_FLOW + 8);
				SetStep(eGLASS_FLATNESS_FLOW_ERROR, _T("eGLASS_FLATNESS_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eGLASS_FLATNESS_FLOW_IMAGE_FOCUS_CHECK, _T("eGLASS_FLATNESS_FLOW_IMAGE_FOCUS_CHECK"));
			}
#else
			Sleep(IMAGE_FOCUS_DELAY);
			SetStep(eGLASS_FLATNESS_FLOW_MEASURE_LASER_FOCUS_VALUE, _T("eGLASS_FLATNESS_FLOW_MEASURE_LASER_FOCUS_VALUE"));
#endif
			break;

		case eGLASS_FLATNESS_FLOW_MEASURE_LASER_FOCUS_VALUE:
			Sleep(100);
			m_dResultLaserValue[m_nMeasurePoint] = SharedInfo::m_dLaserDispFVal;
			SharedInfo::m_sFlatnessTable[m_nMeasurePoint].dResultZ = SharedInfo::GetCmdPos(AXIS_CAMERA_Z1);
			Str.Format(_T("Flatness MeasurePoint:%d, LaserFocusValue:%.5f"), m_nMeasurePoint, m_dResultLaserValue[m_nMeasurePoint]);
			Total_Msg(Str);

			SaveFlatnessResult(m_nMeasurePoint, m_nCurRepeatCount);

			if (m_nMeasurePoint >= SharedInfo::m_nFlatnessTableCnt - 1)
			{	
				if (m_nCurRepeatCount >= m_nMaxRepeatCount - 1)
				{
					SetStep(eGLASS_FLATNESS_FLOW_FINISH_GANTRY_Z3_WAIT_POS, _T("eGLASS_FLATNESS_FLOW_FINISH_GANTRY_Z3_WAIT_POS"));
				}
				else
				{
					m_nCurRepeatCount++;
					m_nMeasurePoint = 0;
					SetStep(eGLASS_FLATNESS_FLOW_AXIS_GANTRY_XY_MEASURE_POS_2ND, _T("eGLASS_FLATNESS_FLOW_AXIS_GANTRY_XY_MEASURE_POS_2ND"));
				}
			}
			else
			{
				m_nMeasurePoint++;
				SetStep(eGLASS_FLATNESS_FLOW_AXIS_GANTRY_XY_MEASURE_POS_2ND, _T("eGLASS_FLATNESS_FLOW_AXIS_GANTRY_XY_MEASURE_POS_2ND"));
			}
			break;		

		case eGLASS_FLATNESS_FLOW_FINISH_GANTRY_Z3_WAIT_POS:
			Devs::m_GantryMotion.Move_GantryZ_All_Wait_Pos();

			SetStep(eGLASS_FLATNESS_FLOW_FINISH_GANTRY_Z3_WAIT_POS_CHECK, _T("eGLASS_FLATNESS_FLOW_FINISH_GANTRY_Z3_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);

			break;

		case eGLASS_FLATNESS_FLOW_FINISH_GANTRY_Z3_WAIT_POS_CHECK:
			if (Devs::m_GantryMotion.Is_GantryZ_All_Wait_Pos())
			{
				SetStep(eGLASS_FLATNESS_FLOW_FINISH_GANTRY_XY_WAIT_POS, _T("eGLASS_FLATNESS_FLOW_FINISH_GANTRY_XY_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eGLASS_FLATNESS_FLOW_FINISH_GANTRY_Z3_WAIT_POS_CHECK : Time Out"), eGLASS_FLATNESS_FLOW + 9);
				SetStep(eGLASS_FLATNESS_FLOW_ERROR, _T("eGLASS_FLATNESS_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eGLASS_FLATNESS_FLOW_FINISH_GANTRY_Z3_WAIT_POS_CHECK, _T("eGLASS_FLATNESS_FLOW_FINISH_GANTRY_Z3_WAIT_POS_CHECK"));
			}
			break;

		case eGLASS_FLATNESS_FLOW_FINISH_GANTRY_XY_WAIT_POS:
			Devs::m_GantryMotion.Move_Gantry_X_Wait_Pos();
			Sleep(20); //!!
			Devs::m_GantryMotion.Move_Gantry_Y_Wait_Pos();
			Sleep(20); //!!

			SetStep(eGLASS_FLATNESS_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK, _T("eGLASS_FLATNESS_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eGLASS_FLATNESS_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Wait_Pos() && Devs::m_GantryMotion.Is_Gantry_Y_Wait_Pos())
			{
				SetStep(eGLASS_FLATNESS_FLOW_DONE, _T("eGLASS_FLATNESS_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eGLASS_FLATNESS_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK : Time Out"), eGLASS_FLATNESS_FLOW + 10);
				SetStep(eGLASS_FLATNESS_FLOW_ERROR, _T("eGLASS_FLATNESS_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eGLASS_FLATNESS_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK, _T("eGLASS_FLATNESS_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK"));
			}
			break;

		case eGLASS_FLATNESS_FLOW_ERROR:
			break;

		case eGLASS_FLATNESS_FLOW_DONE:
		{
			SharedInfo::nPrevFlowID = eGLASS_FLATNESS_FLOW; //KJT 20210326

			m_bFlowDone = TRUE;

			SharedInfo::CalTactTime(_T("eGLASS_FLATNESS_FLOW"), m_timeStart); //KJT 20210329

			SetStep(eGLASS_FLATNESS_FLOW_IDLE, _T("eGLASS_FLATNESS_FLOW_IDLE"));
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

BOOL CGlassFlatnessFlow::FlowInterlock()
{	
	/////////////////////////////////////////////////////////////////////////////
	if (Devs::m_GantryMotion.CheckGantryXYZFlowInterlock(_T("GlassFlatnessFlow"), eGLASS_FLATNESS_FLOW, 30) == FALSE)
	{
		return FALSE;
	}

	//if (Devs::m_CassetteMotion.Is_CSTPickUpUnitBwd() == FALSE)
	//{
	//	SharedInfo::SetAlarm(_T("eGLASS_FLATNESS_FLOW CstPickUnit Backward Error"), 100);
	//	return FALSE;
	//}
	//if (SharedInfo::DInputValue[_DIN_CST_UNSAFE_POS_DETECT] == TRUE)
	//{
	//	SharedInfo::SetAlarm(_T("eGLASS_FLATNESS_FLOW CST Unsafe Pos Error"), 100);
	//	return FALSE;
	//}
	//if (SharedInfo::DInputValue[_DIN_CST_BACKWARD_DETECT] == TRUE)
	//{
	//	SharedInfo::SetAlarm(_T("eGLASS_FLATNESS_FLOW CST Backward Detect Error"), 100);
	//	return FALSE;
	//}

	//if (SharedInfo::m_nFlatnessTableCnt <= 0)
	//{
	//	SharedInfo::SetAlarm(_T("Glass Flatness Count : 0"), 100);
	//	return FALSE;
	//}

	return TRUE;
}

int CGlassFlatnessFlow::SaveFlatnessResult(int nMeasurePointNo, int nRepeatCount)
{
	CVisionAgentDlg *pVisionAgentDlg;
	pVisionAgentDlg = (CVisionAgentDlg *)AfxGetMainWnd();

	CString strLastCnt;
	SYSTEMTIME st;
	GetLocalTime(&st);

	CStdioFile f, flog;
	CString str;
	CString StrTitle;
	string strMaskID[100];
	int i = 0;

	if (!f.Open(m_strFilePath, CFile::modeWrite | CFile::modeNoTruncate | CFile::shareDenyNone))
	{
		if (f.Open(m_strFilePath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyNone))
		{
			StrTitle.Format(_T("Date, Point, Repeat, TargetX, TargetY, ResultZ, LaserFocus\n"));
			f.WriteString(StrTitle);
		}
		else
		{
			TRACE("File Open Faile~!!\r\n");
			return false;
		}
	}

	f.SeekToEnd();

	//for (i = 0; i < SharedInfo::m_nFlatnessTableCnt; i++)
	//{
		str.Format(_T("%02d%02d%02d,"), st.wHour, st.wMinute, st.wSecond);
		str.AppendFormat(_T("%d,"), nMeasurePointNo + 1);
		str.AppendFormat(_T("%d,"), nRepeatCount + 1);
		str.AppendFormat(_T("%.5f,"), SharedInfo::m_sFlatnessTable[nMeasurePointNo].dPosX);
		str.AppendFormat(_T("%.5f,"), SharedInfo::m_sFlatnessTable[nMeasurePointNo].dPosY);
		str.AppendFormat(_T("%.5f,"), SharedInfo::m_sFlatnessTable[nMeasurePointNo].dResultZ);
		str.AppendFormat(_T("%.5f\n"), m_dResultLaserValue[nMeasurePointNo]);
	//}

	f.WriteString(str);
	f.Close();

	return 0;
}