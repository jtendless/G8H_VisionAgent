#include "stdafx.h"
#include "InspectTPFlow.h"
#include "Log/Logger.h"
#include "Vision/Devs.h"
#include "Data/ModelData.h"
#include "CamAreaModul.h"
#include "Data/SystemData.h"
#include "FmmLight1.h"


CInspectTPFlow::CInspectTPFlow()
{
	m_nAlignPoint = 0;
	m_bDirReverse = FALSE;

	for (int i = 0; i < MAX_TP_COUNT; i++)
	{
		m_dMeasurePosXY[0][i] = 0.0;
		m_dMeasurePosXY[1][i] = 0.0;

		m_dVisionResultValue[0][i] = 0.0;
		m_dVisionResultValue[1][i] = 0.0;
	}
}

CInspectTPFlow::~CInspectTPFlow()
{
}

BOOL CInspectTPFlow::InitProcess()
{
	m_StateComplete = NULL;
	m_FlowFinish = TRUE;
	m_bTerminate = FALSE;
	m_bFlowDone = TRUE;

#pragma region //Step Group
	int nGroupIndex = 0;

	m_sGroupInfo[nGroupIndex].m_bProcessingFlag = FALSE;
	m_sGroupInfo[nGroupIndex].nStartStep = _eINSPECT_TP_FLOW_START;
	m_sGroupInfo[nGroupIndex].nEndStep = _eINSPECT_TP_FLOW_START;
	m_sGroupInfo[nGroupIndex].strGroupName.Format(_T("%d. Start"), nGroupIndex + 1);
	nGroupIndex++;
		

	m_nMaxGroupCount = nGroupIndex;
#pragma endregion

	//SetProcessLog(Process_Msg);
	//SetAlarmLog(Alarm_Msg);

	hHandle = CreateEvent(NULL, TRUE, FALSE, NULL);
	SetHandle(hHandle);
	pThread = AfxBeginThread(ThreadFunction, this);

	return TRUE;
}

BOOL CInspectTPFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eINSPECT_TP_FLOW_IDLE);

	if (hHandle != NULL)
	{
		CloseHandle(hHandle);
		hHandle = NULL;
	}

	return TRUE;
}

BOOL CInspectTPFlow::Start(enum_TP_Type nTPType, int nStep)
{
	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	m_nKindOfTP = nTPType;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(nStep, _T("_eINSPECT_TP_FLOW_START"));
	return TRUE;
}

BOOL CInspectTPFlow::Stop()
{
	m_bStopBit = TRUE;
	return TRUE;
}

UINT CInspectTPFlow::ThreadFunction(LPVOID lpParam)
{
	CInspectTPFlow* pFlow = NULL;

	pFlow = (CInspectTPFlow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}

VOID CInspectTPFlow::ThreadFunctionEntry(VOID)
{
	DWORD	dwResult = 0;
	double	dStrt_Time = GetTickCount();
	double	dEnd_Time = GetTickCount();
	double	dWait_Time = GetTickCount();
	int		nWork_Mask_Mode = -1;
	int		nWork_Mask_Index = -1;
	int     nRtn;
	BOOL	bComplete_Step = FALSE;
	CString Str = _T("");

	double dRefPos[4][2] = { 0.0, };
	double dActPos[4][2] = { 0.0, };
	double dPosX = 0.0, dPosY = 0.0;
	double dDiffXTemp = 0.0;
	//KJT 20210304
	double dVel[3] = { 1.0, 1.0, 1.0 };
	double dAcc[3] = { 2.0, 2.0, 2.0 };
	double dDecel[3] = { 2.0, 2.0, 2.0 };

	int nRing, nCoaxial;
	int nBackLightVal[BACKLIGHT_CH_COUNT] = { BACKLIGHT_OFF_VALUE, };


	SYSTEMTIME st;

	while (m_FlowFinish)
	{
		WaitForSingleObject(hHandle, INFINITE);
		ResetEvent(hHandle);

		if (SharedInfo::bMachineStopFlag == TRUE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(_eINSPECT_TP_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}

		switch (GetCurrentTotalStep())
		{
		case _eINSPECT_TP_FLOW_IDLE:
		{
			break;
		}
		case _eINSPECT_TP_FLOW_START:
		{
			m_timeStart = CTime::GetCurrentTime(); //KJT 20210329
			SharedInfo::m_timeUnitTact = m_timeStart;

			SharedInfo::nCurFlowID = eTP_FLOW;

			GetLocalTime(&st);
			m_strPath.Format(_T("%s\\Result\\TP\\TP_%s_%04d%02d%02d%02d%02d%02d.csv"), SharedInfo::VisionAgentPath, SharedInfo::Active.tchStickId, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond); //KJT 20210412

#if 0
			double dPosY = 35.875;
			double dRatio = 0.99975;

			m_dMeasurePosXY[0][0] = -419.3952;
			m_dMeasurePosXY[1][0] = dPosY;

			m_dMeasurePosXY[0][1] = -267.7152;
			m_dMeasurePosXY[1][1] = dPosY;
			
			m_dMeasurePosXY[0][2] = -75.84;
			m_dMeasurePosXY[1][2] = dPosY;

			m_dMeasurePosXY[0][3] = 75.84;
			m_dMeasurePosXY[1][3] = dPosY;

			m_dMeasurePosXY[0][4] = 267.7152;
			m_dMeasurePosXY[1][4] = dPosY;

			m_dMeasurePosXY[0][5] = 419.3952;
			m_dMeasurePosXY[1][5] = dPosY;


			m_dMeasurePosXY[0][6] = -419.3952;
			m_dMeasurePosXY[1][6] = dPosY * (-1);

			m_dMeasurePosXY[0][7] = -267.7152;
			m_dMeasurePosXY[1][7] = dPosY * (-1);

			m_dMeasurePosXY[0][8] = -75.84;
			m_dMeasurePosXY[1][8] = dPosY * (-1);

			m_dMeasurePosXY[0][9] = 75.84;
			m_dMeasurePosXY[1][9] = dPosY * (-1);

			m_dMeasurePosXY[0][10] = 267.7152;
			m_dMeasurePosXY[1][10] = dPosY * (-1);

			m_dMeasurePosXY[0][11] = 419.3952;
			m_dMeasurePosXY[1][11] = dPosY * (-1);

			for (int i = 0; i < HALF_EDGEING_HOLE_MAX; i++)
			{
				m_dMeasurePosXY[0][i] *= dRatio;

				m_dMeasurePosXY[0][i] *= STICK_FLIP_XY;
				m_dMeasurePosXY[1][i] *= STICK_FLIP_XY;
			}
#else //KJT 20210411

			m_nRepeatCount = 0;
			m_nMaxRepeatCount = 0;

			if (m_nKindOfTP == eNORAML_TP)
			{
				m_nMaxRepeatCount = CModelData::m_MaterialPara.Info.nTPRepeatCount;

				for (int i = 0; i < MAX_TP_COUNT; i++)
				{
					m_dMeasurePosXY[0][i] = CModelData::m_MaterialPara.Info.dTPPosX[i] * STICK_FLIP_XY;
					m_dMeasurePosXY[1][i] = CModelData::m_MaterialPara.Info.dTPPosY[i] * STICK_FLIP_XY;
				}
			}
			else
			{
				m_nMaxRepeatCount = CModelData::m_AtMaterialPara.Info.nTPRepeatCount;

				for (int i = 0; i < MAX_TP_COUNT; i++)
				{
					m_dMeasurePosXY[0][i] = CModelData::m_AtMaterialPara.Info.dTPPosX[i] * STICK_FLIP_XY;
					m_dMeasurePosXY[1][i] = CModelData::m_AtMaterialPara.Info.dTPPosY[i] * STICK_FLIP_XY;
				}
			}
#endif

			/////////////
			SharedInfo::nGantryZ1View = eViewReview10X;

			m_nAlignPoint = 0;
			m_bDirReverse = FALSE;

			for (int i = 0; i < MAX_TP_COUNT; i++)
			{
				m_dVisionResultValue[0][i] = 0.0;
				m_dVisionResultValue[1][i] = 0.0;

				//for (int j = 0; j < MAX_HALF_EDGE_REPEAT_COUNT; j++)
				//{
				//	SharedInfo::dTPVisionResultValue[0][i] = 0.0;
				//	SharedInfo::dTPVisionResultValue[1][i] = 0.0;
				//}
			}

			//SharedInfo::nTPCurCount = 0;

			SharedInfo::LightAllOff();
			Sleep(500);

#if 0
			for (int i = 0; i < BACKLIGHT_CH_COUNT; i++)
				nBackLightVal[i] = CModelData::m_AlignPara.Info.nTPBacklight;

			nRing = CModelData::m_AlignPara.Info.nTPRing;
			nCoaxial = CModelData::m_AlignPara.Info.nTPCoAxial;

			//Sleep(500);
			//g_CommLight_8ch.SetLight_Review_Coaxial(CModelData::m_AlignPara.Info.nTPCoAxial); //15
			//Sleep(30);
			//g_CommLight_12ch.SetLight_Review_Ring(CModelData::m_AlignPara.Info.nTPRing); //4
			//Sleep(500);

			if (CModelData::m_AlignPara.Info.nTPLightType == eLight_Back)
			{
				if (CModelData::m_InspectionPara.Info.nMeasureCameraMode == eViewReview20X)
				{
					for (int i = 0; i < BACKLIGHT_CH_COUNT; i++)
						nBackLightVal[i] *= CModelData::m_AlignPara.Info.dx20BackLightScale;
				}
				else if (CModelData::m_InspectionPara.Info.nMeasureCameraMode == eViewReview50X)
				{
					for (int i = 0; i < BACKLIGHT_CH_COUNT; i++)
						nBackLightVal[i] *= CModelData::m_AlignPara.Info.dx50BackLightScale;
				}

				g_CommBack_Light.BackLightOn(nBackLightVal);
				Sleep(30);
			}
			else
			{
				if (CModelData::m_InspectionPara.Info.nMeasureCameraMode == eViewReview20X)
				{
					nRing *= CModelData::m_AlignPara.Info.dx20RingScale;
					nCoaxial *= CModelData::m_AlignPara.Info.dx20CoAxialScale;
				}
				else if (CModelData::m_InspectionPara.Info.nMeasureCameraMode == eViewReview50X)
				{
					nRing *= CModelData::m_AlignPara.Info.dx50RingScale;
					nCoaxial *= CModelData::m_AlignPara.Info.dx50CoAxialScale;
				}

				g_CommReview_Light.SetLight_Review(nRing, nCoaxial);
				Sleep(30);
			}
#else //KJT 20210824
			for (int i = 0; i < BACKLIGHT_CH_COUNT; i++)
				nBackLightVal[i] = CModelData::m_AlignPara.Info.nTPBacklight[CModelData::m_InspectionPara.Info.nMeasureCameraMode];

			nRing = CModelData::m_AlignPara.Info.nTPRing[CModelData::m_InspectionPara.Info.nMeasureCameraMode];
			nCoaxial = CModelData::m_AlignPara.Info.nTPCoAxial[CModelData::m_InspectionPara.Info.nMeasureCameraMode];

			if (CModelData::m_AlignPara.Info.nTPLightType == eLight_Back)
			{
				g_CommBack_Light.BackLightOn(nBackLightVal);
				Sleep(30);
			}
			else
			{
				g_CommReview_Light.SetLight_Review(nRing, nCoaxial);
				Sleep(30);
			}
#endif

			if (CModelData::m_InspectionPara.Info.bMappingDataUse)
			{
				Devs::m_MappingProc.InitializeGlassMapping(eMAPPING_ID_10X);
				if (Devs::m_MappingProc.LoadGlassMappingFile(eMAPPING_ID_10X) == FALSE)
				{
					Alarm_Msg(_T("LoadGlassMappingFile Fail !!"));
					SharedInfo::SetAlarm(_T("_eINSPECT_TP_FLOW_START : Mapping Data"), eTP_FLOW + 0);
					SetStep(_eINSPECT_TP_FLOW_ERROR, _T("_eINSPECT_TP_FLOW_ERROR"));
					break;
				}
			}

			SetStep(_eINSPECT_TP_FLOW_INTERLOCK, _T("_eINSPECT_TP_FLOW_INTERLOCK"));
			break;
		}
		case _eINSPECT_TP_FLOW_INTERLOCK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(_eINSPECT_TP_FLOW_ERROR, _T("_eINSPECT_TP_FLOW_ERROR"));
			}
			else
			{
				if (SharedInfo::MachineState.bAutoRunFlag == TRUE && SharedInfo::nPrevFlowID == eMAIN_ALIGN_FLOW) //KJT 20210415
				{
					if (CModelData::m_InspectionPara.Info.bSWAlignFlowUse == TRUE)
						SetStep(_eINSPECT_TP_FLOW_SW_ALIGN_START, _T("_eINSPECT_TP_FLOW_SW_ALIGN_START"));
					else
						SetStep(_eINSPECT_TP_FLOW_GANTRY_XY_MEASURE_POS_1ST, _T("_eINSPECT_TP_FLOW_GANTRY_XY_MEASURE_POS_1ST"));
				}
				else
					SetStep(_eINSPECT_TP_FLOW_UNLOADER_READY, _T("_eINSPECT_TP_FLOW_UNLOADER_READY"));

			}
			break;

#pragma region //Unloader Ready
		case _eINSPECT_TP_FLOW_UNLOADER_READY:
			Devs::m_Ready_UnloaderFlow.Start();

			SetStep(_eINSPECT_TP_FLOW_UNLOADER_READY_CHECK, _T("_eINSPECT_TP_FLOW_UNLOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eINSPECT_TP_FLOW_UNLOADER_READY_CHECK:
			if (Devs::m_Ready_UnloaderFlow.IsFlowDone())
			{
				SetStep(_eINSPECT_TP_FLOW_GANTRY_ZX_READY, _T("_eINSPECT_TP_FLOW_GANTRY_ZX_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eINSPECT_TP_FLOW_UNLOADER_READY_CHECK : Time Out"), eTP_FLOW + 1);
				SetStep(_eINSPECT_TP_FLOW_ERROR, _T("_eINSPECT_TP_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eINSPECT_TP_FLOW_UNLOADER_READY_CHECK, _T("_eINSPECT_TP_FLOW_UNLOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Gantry Z, X Ready
		case _eINSPECT_TP_FLOW_GANTRY_ZX_READY:
			Devs::m_Ready_GantryZX_Flow.Start();

			SetStep(_eINSPECT_TP_FLOW_GANTRY_ZX_READY_CHECK, _T("_eINSPECT_TP_FLOW_GANTRY_ZX_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eINSPECT_TP_FLOW_GANTRY_ZX_READY_CHECK:
			if (Devs::m_Ready_GantryZX_Flow.IsFlowDone())
			{
				SetStep(_eINSPECT_TP_FLOW_LOADER_READY, _T("_eINSPECT_TP_FLOW_LOADER_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eINSPECT_TP_FLOW_GANTRY_ZX_READY_CHECK : Time Out"), eTP_FLOW + 4);
				SetStep(_eINSPECT_TP_FLOW_ERROR, _T("_eINSPECT_TP_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eINSPECT_TP_FLOW_GANTRY_ZX_READY_CHECK, _T("_eINSPECT_TP_FLOW_GANTRY_ZX_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Loader Ready
		case _eINSPECT_TP_FLOW_LOADER_READY:
			Devs::m_Ready_LoaderFlow.Start();

			SetStep(_eINSPECT_TP_FLOW_LOADER_READY_CHECK, _T("_eINSPECT_TP_FLOW_LOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eINSPECT_TP_FLOW_LOADER_READY_CHECK:
			if (Devs::m_Ready_LoaderFlow.IsFlowDone())
			{
				SetStep(_eINSPECT_TP_FLOW_PAPER_UNLOADER_ZXY_READY, _T("_eINSPECT_TP_FLOW_PAPER_UNLOADER_ZXY_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eINSPECT_TP_FLOW_LOADER_READY_CHECK : Time Out"), eTP_FLOW + 2);
				SetStep(_eINSPECT_TP_FLOW_ERROR, _T("_eINSPECT_TP_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eINSPECT_TP_FLOW_LOADER_READY_CHECK, _T("_eINSPECT_TP_FLOW_LOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //PaperUnloader Ready
		case _eINSPECT_TP_FLOW_PAPER_UNLOADER_ZXY_READY:
			Devs::m_Ready_PaperUnloaderFlow.Start();

			SetStep(_eINSPECT_TP_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK, _T("_eINSPECT_TP_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eINSPECT_TP_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK:
			if (Devs::m_Ready_PaperUnloaderFlow.IsFlowDone())
			{
				if (CModelData::m_InspectionPara.Info.bSWAlignFlowUse == TRUE)
					SetStep(_eINSPECT_TP_FLOW_SW_ALIGN_START, _T("_eINSPECT_TP_FLOW_SW_ALIGN_START"));
				else
					SetStep(_eINSPECT_TP_FLOW_GANTRY_XY_MEASURE_POS_1ST, _T("_eINSPECT_TP_FLOW_GANTRY_XY_MEASURE_POS_1ST"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eINSPECT_TP_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK : Time Out"), eBOX_ALIGN_FLOW + 1);
				SetStep(_eINSPECT_TP_FLOW_ERROR, _T("_eINSPECT_TP_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eINSPECT_TP_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK, _T("_eINSPECT_TP_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK"));
			}
			break;
#pragma endregion

		case _eINSPECT_TP_FLOW_SW_ALIGN_START:
			Devs::m_SwAlignFlow.m_eSwAlignType = eSwAlign_EdgeSlot; //KJT 20210419
			Devs::m_SwAlignFlow.Start(Devs::m_SwAlignFlow._eSW_ALIGN_FLOW_START);

			SetStep(_eINSPECT_TP_FLOW_SW_ALIGN_DONE_CHECK, _T("_eINSPECT_TP_FLOW_SW_ALIGN_DONE_CHECK"));
			SetTimeOut(TIME_OUT_STATE);
			break;

		case _eINSPECT_TP_FLOW_SW_ALIGN_DONE_CHECK:
			if (Devs::m_SwAlignFlow.IsFlowDone())
			{
#if 0
				for (int i = 0; i < BACKLIGHT_CH_COUNT; i++)
					nBackLightVal[i] = CModelData::m_AlignPara.Info.nTPBacklight;

				nRing = CModelData::m_AlignPara.Info.nTPRing;
				nCoaxial = CModelData::m_AlignPara.Info.nTPCoAxial;				

				if (CModelData::m_AlignPara.Info.nTPLightType == eLight_Back)
				{
					if (CModelData::m_InspectionPara.Info.nMeasureCameraMode == eViewReview20X)
					{
						for (int i = 0; i < BACKLIGHT_CH_COUNT; i++)
							nBackLightVal[i] *= CModelData::m_AlignPara.Info.dx20BackLightScale;
					}
					else if (CModelData::m_InspectionPara.Info.nMeasureCameraMode == eViewReview50X)
					{
						for (int i = 0; i < BACKLIGHT_CH_COUNT; i++)
							nBackLightVal[i] *= CModelData::m_AlignPara.Info.dx50BackLightScale;
					}

					g_CommBack_Light.BackLightOn(nBackLightVal);
					Sleep(30);
				}
				else
				{
					if (CModelData::m_InspectionPara.Info.nMeasureCameraMode == eViewReview20X)
					{
						nRing *= CModelData::m_AlignPara.Info.dx20RingScale;
						nCoaxial *= CModelData::m_AlignPara.Info.dx20CoAxialScale;
					}
					else if (CModelData::m_InspectionPara.Info.nMeasureCameraMode == eViewReview50X)
					{
						nRing *= CModelData::m_AlignPara.Info.dx50RingScale;
						nCoaxial *= CModelData::m_AlignPara.Info.dx50CoAxialScale;
					}

					g_CommReview_Light.SetLight_Review(nRing, nCoaxial);
					Sleep(30);
				}
#else //KJT 20210824
				for (int i = 0; i < BACKLIGHT_CH_COUNT; i++)
					nBackLightVal[i] = CModelData::m_AlignPara.Info.nTPBacklight[CModelData::m_InspectionPara.Info.nMeasureCameraMode];

				nRing = CModelData::m_AlignPara.Info.nTPRing[CModelData::m_InspectionPara.Info.nMeasureCameraMode];
				nCoaxial = CModelData::m_AlignPara.Info.nTPCoAxial[CModelData::m_InspectionPara.Info.nMeasureCameraMode];

				if (CModelData::m_AlignPara.Info.nTPLightType == eLight_Back)
				{
					g_CommBack_Light.BackLightOn(nBackLightVal);
					Sleep(30);
				}
				else
				{
					g_CommReview_Light.SetLight_Review(nRing, nCoaxial);
					Sleep(30);
				}
#endif

				SetCheckStep(_eINSPECT_TP_FLOW_GANTRY_XY_MEASURE_POS_1ST, _T("_eINSPECT_TP_FLOW_GANTRY_XY_MEASURE_POS_1ST"));
				SetTimeOut(TIME_OUT_MOTION);
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eINSPECT_TP_FLOW_SW_ALIGN_DONE_CHECK : Time Out"), eTP_FLOW + 5);
				SetStep(_eINSPECT_TP_FLOW_ERROR, _T("_eINSPECT_TP_FLOW_ERROR"));
				break;
			}
			else
			{
				SetCheckStep(_eINSPECT_TP_FLOW_SW_ALIGN_DONE_CHECK, _T("_eINSPECT_TP_FLOW_SW_ALIGN_DONE_CHECK"));
			}
			break;

#pragma region //Gantry XYZ First Pos Move
		case _eINSPECT_TP_FLOW_GANTRY_XY_MEASURE_POS_1ST:
			m_dTargetPosX = dPosX = m_dMeasurePosXY[0][m_nAlignPoint];
			m_dTargetPosY = dPosY = m_dMeasurePosXY[1][m_nAlignPoint];

			if (CModelData::m_InspectionPara.Info.nMeasureCameraMode == eViewReview20X)
			{
				Devs::m_GantryMotion.ConvertTo20XPos(&m_dTargetPosX, &m_dTargetPosY);
			}

			SharedInfo::GetMappingPos(CModelData::m_InspectionPara.Info.bSWAlignFlowUse, CModelData::m_InspectionPara.Info.bMappingDataUse, &m_dTargetPosX, &m_dTargetPosY); //KJT 20210312
			
			Devs::m_GantryMotion.Move_Gantry_X_Pos(m_dTargetPosX, TRUE);
			Sleep(20); //!!
			Devs::m_GantryMotion.Move_Gantry_Y_Pos(m_dTargetPosY);
			Sleep(20); //!!

			SetStep(_eINSPECT_TP_FLOW_GANTRY_XY_MEASURE_POS_1ST_CHECK, _T("_eINSPECT_TP_FLOW_GANTRY_XY_MEASURE_POS_1ST_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eINSPECT_TP_FLOW_GANTRY_XY_MEASURE_POS_1ST_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Pos(m_dTargetPosX) && Devs::m_GantryMotion.Is_Gantry_Y_Pos(m_dTargetPosY))
			{				
				if (CModelData::m_AlignPara.Info.nTPLightType == eLight_Back)
				{
					if (Devs::m_InspectionStageMotion.Is_BackLight_X_Pos(m_dTargetPosX))
					{
						Sleep(500); //!!

						//SetStep(_eINSPECT_TP_FLOW_GANTRY_Z1_MEASURE_POS, _T("_eINSPECT_TP_FLOW_GANTRY_Z1_MEASURE_POS"));
						SetStep(_eINSPECT_TP_FLOW_GANTRY_Z3_MEASURE_POS, _T("_eINSPECT_TP_FLOW_GANTRY_Z3_MEASURE_POS"));
					}
					else
						SetCheckStep(_eINSPECT_TP_FLOW_GANTRY_XY_MEASURE_POS_1ST_CHECK, _T("_eINSPECT_TP_FLOW_GANTRY_XY_MEASURE_POS_1ST_CHECK"));
				}
				else
				{
					//SetStep(_eINSPECT_TP_FLOW_GANTRY_Z1_MEASURE_POS, _T("_eINSPECT_TP_FLOW_GANTRY_Z1_MEASURE_POS"));
					SetStep(_eINSPECT_TP_FLOW_GANTRY_Z3_MEASURE_POS, _T("_eINSPECT_TP_FLOW_GANTRY_Z3_MEASURE_POS"));
				}
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eINSPECT_TP_FLOW_GANTRY_XY_MEASURE_POS_1ST_CHECK : Time Out"), eTP_FLOW + 6);
				SetStep(_eINSPECT_TP_FLOW_ERROR, _T("_eINSPECT_TP_FLOW_ERROR"));
				break;
			}
			else
			{
				SetCheckStep(_eINSPECT_TP_FLOW_GANTRY_XY_MEASURE_POS_1ST_CHECK, _T("_eINSPECT_TP_FLOW_GANTRY_XY_MEASURE_POS_1ST_CHECK"));
			}
			break;

		case _eINSPECT_TP_FLOW_GANTRY_Z3_MEASURE_POS:
			Devs::m_GantryMotion.Move_GantryZ1_InspectionReview_Pos();
			Sleep(20); //!!

			SetStep(_eINSPECT_TP_FLOW_GANTRY_Z3_MEASURE_POS_CHECK, _T("_eINSPECT_TP_FLOW_GANTRY_Z3_MEASURE_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eINSPECT_TP_FLOW_GANTRY_Z3_MEASURE_POS_CHECK:
			if (Devs::m_GantryMotion.Is_GantryZ1_InspectionReview_Pos())
			{
				Sleep(500); //!!
				SetStep(_eINSPECT_TP_FLOW_AUTOFOCUS_CHECK, _T("_eINSPECT_TP_FLOW_AUTOFOCUS_CHECK"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eINSPECT_TP_FLOW_GANTRY_Z3_MEASURE_POS_CHECK : Time Out"), eTP_FLOW + 7);
				SetStep(_eINSPECT_TP_FLOW_ERROR, _T("_eINSPECT_TP_FLOW_ERROR"));
				break;
			}
			else
			{
				SetCheckStep(_eINSPECT_TP_FLOW_GANTRY_Z3_MEASURE_POS_CHECK, _T("_eINSPECT_TP_FLOW_GANTRY_Z3_MEASURE_POS_CHECK"));
			}
			break;
#pragma endregion

		case _eINSPECT_TP_FLOW_GANTRY_XY_MEASURE_POS_2ND:
			m_dTargetPosX = dPosX = m_dMeasurePosXY[0][m_nAlignPoint];
			m_dTargetPosY = dPosY = m_dMeasurePosXY[1][m_nAlignPoint];

			if (CModelData::m_InspectionPara.Info.nMeasureCameraMode == eViewReview20X)
			{
				Devs::m_GantryMotion.ConvertTo20XPos(&m_dTargetPosX, &m_dTargetPosY);
			}

			SharedInfo::GetMappingPos(CModelData::m_InspectionPara.Info.bSWAlignFlowUse, CModelData::m_InspectionPara.Info.bMappingDataUse, &m_dTargetPosX, &m_dTargetPosY); //KJT 20210312
		
			Devs::m_GantryMotion.Move_Gantry_X_Pos(m_dTargetPosX, TRUE);
			Sleep(20); //!!
			Devs::m_GantryMotion.Move_Gantry_Y_Pos(m_dTargetPosY);
			Sleep(20); //!!

			SetStep(_eINSPECT_TP_FLOW_GANTRY_XY_MEASURE_POS_2ND_CHECK, _T("_eINSPECT_TP_FLOW_GANTRY_XY_MEASURE_POS_2ND_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eINSPECT_TP_FLOW_GANTRY_XY_MEASURE_POS_2ND_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Pos(m_dTargetPosX) && Devs::m_GantryMotion.Is_Gantry_Y_Pos(m_dTargetPosY))
			{
				if (CModelData::m_AlignPara.Info.nTPLightType == eLight_Back)
				{
					if (Devs::m_InspectionStageMotion.Is_BackLight_X_Pos(m_dTargetPosX))
					{
						Sleep(500); //!!

						SetStep(_eINSPECT_TP_FLOW_AUTOFOCUS_CHECK, _T("_eINSPECT_TP_FLOW_AUTOFOCUS_CHECK"));
					}
					else
						SetCheckStep(_eINSPECT_TP_FLOW_GANTRY_XY_MEASURE_POS_2ND_CHECK, _T("_eINSPECT_TP_FLOW_GANTRY_XY_MEASURE_POS_2ND_CHECK"));
				}
				else
				{
					SharedInfo::SetAlarm(_T("_eINSPECT_TP_FLOW_GANTRY_XY_MEASURE_POS_2ND_CHECK : Time Out"), eTP_FLOW + 8);
					SetStep(_eINSPECT_TP_FLOW_AUTOFOCUS_CHECK, _T("_eINSPECT_TP_FLOW_AUTOFOCUS_CHECK"));
					break;
				}
			}
			else if (IsTimeOut())
			{
				SetStep(_eINSPECT_TP_FLOW_ERROR, _T("_eINSPECT_TP_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eINSPECT_TP_FLOW_GANTRY_XY_MEASURE_POS_2ND_CHECK, _T("_eINSPECT_TP_FLOW_GANTRY_XY_MEASURE_POS_2ND_CHECK"));
			}
			break;

		case _eINSPECT_TP_FLOW_AUTOFOCUS_CHECK: //KJT 20210313
			if (CModelData::m_AlignPara.Info.nTPFocusType == eFocusType_Laser || CModelData::m_AlignPara.Info.nTPFocusType == eFocusType_Both)
				SetStep(_eINSPECT_TP_FLOW_LASER_FOCUS_START, _T("_eINSPECT_TP_FLOW_LASER_FOCUS_START"));
			else if (CModelData::m_AlignPara.Info.nTPFocusType == eFocusType_Image)
				SetStep(_eINSPECT_TP_FLOW_IMAGE_FOCUS_START, _T("_eINSPECT_TP_FLOW_IMAGE_FOCUS_START"));
			else
				SetStep(_eINSPECT_TP_FLOW_GRAB_START, _T("_eINSPECT_TP_FLOW_GRAB_START"));
			break;

		case _eINSPECT_TP_FLOW_LASER_FOCUS_START:
			Devs::m_GantryMotion.LaserFocusMove();

			SetStep(_eINSPECT_TP_FLOW_LASER_FOCUS_CHECK, _T("_eINSPECT_TP_FLOW_LASER_FOCUS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eINSPECT_TP_FLOW_LASER_FOCUS_CHECK: //KJT 20210313
			if (Devs::m_GantryMotion.LaserFocusMoveCheck())
			{
				Sleep(500); //!!	//KJT 20210321

				if (CModelData::m_AlignPara.Info.nTPFocusType == eFocusType_Both)
					SetStep(_eINSPECT_TP_FLOW_IMAGE_FOCUS_START, _T("_eINSPECT_TP_FLOW_IMAGE_FOCUS_START"));
				else
					SetStep(_eINSPECT_TP_FLOW_GRAB_START, _T("_eINSPECT_TP_FLOW_GRAB_START"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eINSPECT_TP_FLOW_LASER_FOCUS_CHECK : Time Out"), eTP_FLOW + 9);
				SetStep(_eINSPECT_TP_FLOW_ERROR, _T("_eINSPECT_TP_FLOW_ERROR"));
				break;
			}
			else
			{
				SetCheckStep(_eINSPECT_TP_FLOW_LASER_FOCUS_CHECK, _T("_eINSPECT_TP_FLOW_LASER_FOCUS_CHECK"));
			}
			break;

		case _eINSPECT_TP_FLOW_IMAGE_FOCUS_START:
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
			SetStep(_eINSPECT_TP_FLOW_IMAGE_FOCUS_CHECK, _T("_eINSPECT_TP_FLOW_IMAGE_FOCUS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eINSPECT_TP_FLOW_IMAGE_FOCUS_CHECK:
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
				SetStep(_eINSPECT_TP_FLOW_GRAB_START, _T("_eINSPECT_TP_FLOW_GRAB_START"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eINSPECT_TP_FLOW_IMAGE_FOCUS_CHECK : Time Out"), eTP_FLOW + 10);
				SetStep(_eINSPECT_TP_FLOW_ERROR, _T("_eINSPECT_TP_FLOW_ERROR"));
				break;
			}
			else
			{
				SetCheckStep(_eINSPECT_TP_FLOW_IMAGE_FOCUS_CHECK, _T("_eINSPECT_TP_FLOW_IMAGE_FOCUS_CHECK"));
			}
#else
			Sleep(IMAGE_FOCUS_DELAY);
			SetStep(_eINSPECT_TP_FLOW_GRAB_START, _T("_eINSPECT_TP_FLOW_GRAB_START"));
#endif
			break;
#pragma region //2Point Align
		case _eINSPECT_TP_FLOW_GRAB_START:
			SharedInfo::bMainAlignGrabDone = TRUE;

			if (CModelData::m_AlignPara.Info.nTPMarkType == eMark_Pattern)
			{
				nRtn = Devs::m_GantryMotion.FindPattern_TP(&m_dVisionResultValue[0][m_nAlignPoint], &m_dVisionResultValue[1][m_nAlignPoint], CModelData::m_InspectionPara.Info.nMeasureCameraMode); //KJT 20210824
			}
			else
			{
				nRtn = Devs::m_GantryMotion.FindBlob_TP(&m_dVisionResultValue[0][m_nAlignPoint], &m_dVisionResultValue[1][m_nAlignPoint], CModelData::m_InspectionPara.Info.nMeasureCameraMode); //KJT 20210824
			}

			if (nRtn == 0)
			{
				SharedInfo::SetAlarm(_T("_eINSPECT_TP_FLOW_GRAB_START : Find Hole"), eTP_FLOW + 11);
				SetStep(_eINSPECT_TP_FLOW_ERROR, _T("_eINSPECT_TP_FLOW_ERROR"));
				break;
			}

			//SharedInfo::dTPVisionResultValue[0][m_nAlignPoint] = m_dVisionResultValue[0][m_nAlignPoint];
			//SharedInfo::dTPVisionResultValue[1][m_nAlignPoint] = m_dVisionResultValue[1][m_nAlignPoint];

			Str.Format(_T("AlignCnt:%d Diff X:%.5f, Y:%.5f"), m_nAlignPoint, m_dVisionResultValue[0][m_nAlignPoint], m_dVisionResultValue[1][m_nAlignPoint]);
			Total_Msg(Str);

			SetStep(_eINSPECT_TP_FLOW_GRAB_DONE_CHECK, _T("_eINSPECT_TP_FLOW_GRAB_DONE_CHECK"));
			break;

		case _eINSPECT_TP_FLOW_GRAB_DONE_CHECK:
			//if (m_nAlignPoint >= HALF_EDGEING_HOLE_MAX - 1)
			if(m_nAlignPoint >= CModelData::m_AtMaterialPara.Info.nTPCount - 1)
			{						
				if (++m_nRepeatCount >= m_nMaxRepeatCount)
				{
					m_nAlignPoint = 0;

					SaveTPResult(m_nRepeatCount);

					SharedInfo::LightAllOff(); //KJT 20210226

					if (SharedInfo::MachineState.bAutoRunFlag == TRUE && CModelData::m_InspectionPara.Info.bSWAlignFlowUse) //KJT 20210415
						SetStep(_eINSPECT_TP_FLOW_DONE, _T("_eINSPECT_TP_FLOW_DONE"));
					else
						//SetStep(_eINSPECT_TP_FLOW_FINISH_GANTRY_Z1_WAIT_POS, _T("_eINSPECT_TP_FLOW_FINISH_GANTRY_Z1_WAIT_POS"));
						SetStep(_eINSPECT_TP_FLOW_FINISH_GANTRY_Z3_WAIT_POS, _T("_eINSPECT_TP_FLOW_FINISH_GANTRY_Z3_WAIT_POS"));
				}
				else
				{
					SaveTPResult(m_nRepeatCount);

					Str.Format(_T("m_nAlignPoint:%d Diff X[0]:%.5f, Y[0]:%.5f"), m_nAlignPoint, m_dVisionResultValue[0][m_nAlignPoint], m_dVisionResultValue[1][m_nAlignPoint]);
					Total_Msg(Str);
					
					Sleep(100);
					m_nAlignPoint = 0;
					SetStep(_eINSPECT_TP_FLOW_GANTRY_XY_MEASURE_POS_2ND, _T("_eINSPECT_TP_FLOW_GANTRY_XY_MEASURE_POS_2ND"));
				}
			}
			else
			{
				Str.Format(_T("m_nAlignPoint:%d Diff X[0]:%.5f, Y[0]:%.5f"), m_nAlignPoint, m_dVisionResultValue[0][m_nAlignPoint], m_dVisionResultValue[1][m_nAlignPoint]);
				Total_Msg(Str);

				m_nAlignPoint++;

				Sleep(100);
				SetStep(_eINSPECT_TP_FLOW_GANTRY_XY_MEASURE_POS_2ND, _T("_eINSPECT_TP_FLOW_GANTRY_XY_MEASURE_POS_2ND"));
			}
			break;
#pragma endregion

		case _eINSPECT_TP_FLOW_FINISH_GANTRY_Z3_WAIT_POS:
			Devs::m_GantryMotion.Move_GantryZ_All_Wait_Pos();
			Sleep(20); //!!

			SetStep(_eINSPECT_TP_FLOW_FINISH_GANTRY_Z3_WAIT_POS_CHECK, _T("_eINSPECT_TP_FLOW_FINISH_GANTRY_Z3_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);

			break;

		case _eINSPECT_TP_FLOW_FINISH_GANTRY_Z3_WAIT_POS_CHECK:
			if (Devs::m_GantryMotion.Is_GantryZ_All_Wait_Pos())
			{
				if (SharedInfo::MachineState.bAutoRunFlag == TRUE && SharedInfo::Active.ProcessEndFlow != eCOMBO_AUTO_RUN_FLOW_TP)
					SetStep(_eINSPECT_TP_FLOW_DONE, _T("_eINSPECT_TP_FLOW_DONE"));
				else
					SetStep(_eINSPECT_TP_FLOW_FINISH_GANTRY_XY_WAIT_POS, _T("_eINSPECT_TP_FLOW_FINISH_GANTRY_XY_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eINSPECT_TP_FLOW_FINISH_GANTRY_Z3_WAIT_POS_CHECK : Time Out"), eTP_FLOW + 12);
				SetStep(_eINSPECT_TP_FLOW_ERROR, _T("_eINSPECT_TP_FLOW_ERROR"));
				break;
			}
			else
			{
				SetCheckStep(_eINSPECT_TP_FLOW_FINISH_GANTRY_Z3_WAIT_POS_CHECK, _T("_eINSPECT_TP_FLOW_FINISH_GANTRY_Z3_WAIT_POS_CHECK"));
			}
			break;

		case _eINSPECT_TP_FLOW_FINISH_GANTRY_XY_WAIT_POS:
			Devs::m_GantryMotion.Move_Gantry_X_Wait_Pos();
			Sleep(20); //!!
			Devs::m_GantryMotion.Move_Gantry_Y_Wait_Pos();
			Sleep(20); //!!

			SetStep(_eINSPECT_TP_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK, _T("_eINSPECT_TP_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eINSPECT_TP_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Wait_Pos() && Devs::m_GantryMotion.Is_Gantry_Y_Wait_Pos())
			{
				SetStep(_eINSPECT_TP_FLOW_DONE, _T("_eINSPECT_TP_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eINSPECT_TP_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK : Time Out"), eTP_FLOW + 13);
				SetStep(_eINSPECT_TP_FLOW_ERROR, _T("_eINSPECT_TP_FLOW_ERROR"));
				break;
			}
			else
			{
				SetCheckStep(_eINSPECT_TP_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK, _T("_eINSPECT_TP_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK"));
			}
			break;

		case _eINSPECT_TP_FLOW_ERROR:
			break;

		case _eINSPECT_TP_FLOW_DONE:
		{
			SharedInfo::nPrevFlowID = eTP_FLOW; //KJT 20210326

			m_bFlowDone = TRUE;

			SharedInfo::CalTactTime(_T("TP_FLOW"), m_timeStart); //KJT 20210329

			SetStep(_eINSPECT_TP_FLOW_IDLE, _T("_eINSPECT_TP_FLOW_IDLE"));
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

BOOL CInspectTPFlow::FlowInterlock()
{
	/////////////////////////////////////////////////////////////////////////////
	if (Devs::m_GantryMotion.CheckGantryXYZFlowInterlock(_T("InspectTPFlow"), eTP_FLOW, 30) == FALSE)
	{
		return FALSE;
	}	

	////Servo On Check
	//if (SharedInfo::GetServoOnStatus(AXIS_GANTRY_X) != TRUE)
	//{
	//	Total_Msg(_T("Gantry X Servo On Check !!!"));
	//	return FALSE;
	//}
	//if (SharedInfo::GetServoOnStatus(AXIS_VIRTUAL_GANTRY_Y) != TRUE)
	//{
	//	Total_Msg(_T("Gantry Y Servo On Check !!!"));
	//	return FALSE;
	//}

	////Home Status Check
	//if (SharedInfo::GetHomeStatus(AXIS_GANTRY_X) != TRUE)
	//{
	//	Total_Msg(_T("Gantry X Home Status Check !!!"));
	//	return FALSE;
	//}
	//if (SharedInfo::GetHomeStatus(AXIS_VIRTUAL_GANTRY_Y) != TRUE)
	//{
	//	Total_Msg(_T("Gantry Y Home Status Check !!!"));
	//	return FALSE;
	//}

	//if (Devs::m_CassetteMotion.Is_CSTPickUpUnitBwd() == FALSE)
	//{
	//	Total_Msg(_T("Check Pickup Unit Backward !!!"));
	//	return FALSE;
	//}
	//if (SharedInfo::DInputValue[_DIN_CST_UNSAFE_POS_DETECT] == TRUE)
	//{
	//	Total_Msg(_T("Check CST Unsafe Pos Detect Sensor !!!"));
	//	return FALSE;
	//}
	//if (SharedInfo::DInputValue[_DIN_CST_BACKWARD_DETECT] == TRUE)
	//{
	//	Total_Msg(_T("Check CST Backward Detect Sensor !!!"));
	//	return FALSE;
	//}

	return TRUE;
}

int CInspectTPFlow::SaveTPResult(int nRepeatCount)
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

	if (!f.Open(m_strPath, CFile::modeWrite | CFile::modeNoTruncate | CFile::shareDenyNone))
	{
		if (f.Open(m_strPath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyNone))
		{
			StrTitle.Format(_T("MaskID, Repeat, PointNo, PosX, PosY, FindX, FindY"));

			//for (int i = 0; i < 12; i++)
			//{
			//	StrTitle.AppendFormat(_T(", Temp%d"), i + 1);
			//}

			//StrTitle.AppendFormat(_T("Mask,%s\n\n"), SharedInfo::Active.tchStickId);
			StrTitle.AppendFormat(_T("\n"));
			f.WriteString(StrTitle);
		}
		else
		{
			TRACE("File Open Faile~!!\r\n");
			return false;
		}
	}

	f.SeekToEnd();

	
	//int nCountX = HALF_EDGEING_HOLE_MAX / 2;
	int nCountX = CModelData::m_AtMaterialPara.Info.nTPCount;// / 2;

	{
		for (i = 0; i < nCountX; i++)
		{
			str.AppendFormat(_T("%s, %d, %d"), SharedInfo::Active.tchStickId, nRepeatCount, i+1);
			str.AppendFormat(_T(", %.8f, %.8f, %.8f, %.8f\n"), m_dMeasurePosXY[0][i] * STICK_FLIP_XY, m_dMeasurePosXY[1][i] * STICK_FLIP_XY, m_dVisionResultValue[0][i] * STICK_FLIP_XY, m_dVisionResultValue[1][i] * STICK_FLIP_XY);
		}


		/*
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//Half Edge X
		//Top
		str.AppendFormat(_T("TP\nX\n"));
		str.AppendFormat(_T("TargetPos,"));
		for (i = 0; i < nCountX; i++)
		{
			str.AppendFormat(_T("%10.1f,"), m_dMeasurePosXY[0][i] * STICK_FLIP_XY);
		}
		str.AppendFormat(_T("\n"));
		str.AppendFormat(_T("RealPos,"));
		for (i = 0; i < nCountX; i++)
		{
			str.AppendFormat(_T("%10.1f,"), m_dMeasurePosXY[0][i]);
		}
		str.AppendFormat(_T("\n"));
		str.AppendFormat(_T("Diff,"));
		for (i = 0; i < nCountX; i++)
		{
			str.AppendFormat(_T("%10.1f,"), m_dVisionResultValue[0][i] * 1000 * STICK_FLIP_XY);
		}
		str.AppendFormat(_T("\n\n"));

		//Bottom
		//str.AppendFormat(_T("TargetPos,"));
		//for (i = nCountX; i < nCountX; i++)
		//{
		//	str.AppendFormat(_T("%10.1f,"), m_dMeasurePosXY[0][i] * STICK_FLIP_XY);
		//}
		//str.AppendFormat(_T("\n"));
		//str.AppendFormat(_T("RealPos,"));
		//for (i = nCountX; i < nCountX; i++)
		//{
		//	str.AppendFormat(_T("%10.1f,"), m_dMeasurePosXY[0][i]);
		//}
		//str.AppendFormat(_T("\n"));
		//str.AppendFormat(_T("Diff,"));
		//for (i = nCountX; i < nCountX; i++)
		//{
		//	str.AppendFormat(_T("%10.1f,"), m_dVisionResultValue[0][i] * 1000 * STICK_FLIP_XY);
		//}
		//str.AppendFormat(_T("\n\n"));

		//Half Edge Y
		//Top
		str.AppendFormat(_T("Y\n"));
		str.AppendFormat(_T("TargetPos,"));
		for (i = 0; i < nCountX; i++)
		{
			str.AppendFormat(_T("%10.1f,"), m_dMeasurePosXY[1][i] * STICK_FLIP_XY);
		}
		str.AppendFormat(_T("\n"));
		str.AppendFormat(_T("RealPos,"));
		for (i = 0; i < nCountX; i++)
		{
			str.AppendFormat(_T("%10.1f,"), m_dMeasurePosXY[1][i]);
		}
		str.AppendFormat(_T("\n"));
		str.AppendFormat(_T("Diff,"));
		for (i = 0; i < nCountX; i++)
		{
			str.AppendFormat(_T("%10.1f,"), m_dVisionResultValue[1][i] * 1000 * STICK_FLIP_XY);
		}
		str.AppendFormat(_T("\n\n"));

		//Bottom
		//str.AppendFormat(_T("TargetPos,"));
		//for (i = nCountX; i < nCountX; i++)
		//{
		//	str.AppendFormat(_T("%10.1f,"), m_dMeasurePosXY[1][i] * STICK_FLIP_XY);
		//}
		//str.AppendFormat(_T("\n"));
		//str.AppendFormat(_T("RealPos,"));
		//for (i = nCountX; i < nCountX; i++)
		//{
		//	str.AppendFormat(_T("%10.1f,"), m_dMeasurePosXY[1][i]);
		//}
		//str.AppendFormat(_T("\n"));
		//str.AppendFormat(_T("Diff,"));
		//for (i = nCountX; i < nCountX; i++)
		//{
		//	str.AppendFormat(_T("%10.1f,"), m_dVisionResultValue[1][i] * 1000 * STICK_FLIP_XY);
		//}		
		str.AppendFormat(_T("\n"));
		*/
	}

	f.WriteString(str);
	f.Close();

	return 0;
}