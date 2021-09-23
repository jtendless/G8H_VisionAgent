#include "stdafx.h"
#include "MeasureCdFlow.h"
#include "Log/Logger.h"
#include "Vision/Devs.h"
#include "Data/ModelData.h"
#include "CamAreaModul.h"
#include "Data/SystemData.h"
#include "FmmLight1.h"

CMeasureCdFlow::CMeasureCdFlow()
{
	memset(m_dMeasurePosXY, 0x0, sizeof(m_dMeasurePosXY));
	memset(m_VisionResultCdValue, 0x0, sizeof(m_VisionResultCdValue));
}

CMeasureCdFlow::~CMeasureCdFlow()
{
}

BOOL CMeasureCdFlow::InitProcess()
{
	m_StateComplete = NULL;
	m_FlowFinish = TRUE;
	m_bTerminate = FALSE;
	m_bFlowDone = TRUE;

#pragma region //Step Group
	int nGroupIndex = 0;



	m_nMaxGroupCount = nGroupIndex;
#pragma endregion

	//SetProcessLog(Process_Msg);
	//SetAlarmLog(Alarm_Msg);

	hHandle = CreateEvent(NULL, TRUE, FALSE, NULL);
	SetHandle(hHandle);
	pThread = AfxBeginThread(ThreadFunction, this);

	return TRUE;
}

BOOL CMeasureCdFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eMEASURE_CD_FLOW_IDLE);

	if (hHandle != NULL)
	{
		CloseHandle(hHandle);
		hHandle = NULL;
	}

	return TRUE;
}

BOOL CMeasureCdFlow::Start(int nStep)
{
	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(nStep, _T("_eMEASURE_CD_FLOW_START"));
	return TRUE;
}

BOOL CMeasureCdFlow::Stop()
{
	m_bStopBit = TRUE;
	return TRUE;
}

UINT CMeasureCdFlow::ThreadFunction(LPVOID lpParam)
{
	CMeasureCdFlow* pFlow = NULL;

	pFlow = (CMeasureCdFlow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}

VOID CMeasureCdFlow::ThreadFunctionEntry(VOID)
{
	DWORD	dwResult = 0;
	double	dStrt_Time = GetTickCount();
	double	dEnd_Time = GetTickCount();
	double	dWait_Time = GetTickCount();
	int		nWork_Mask_Mode = -1;
	int		nWork_Mask_Index = -1;
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

	m_nGrabRetryCnt = 0;

	int nRing = 0, nCoaxial = 0;
	int nBackLightVal[BACKLIGHT_CH_COUNT] = { BACKLIGHT_OFF_VALUE, };

	SYSTEMTIME st;

	while (m_FlowFinish)
	{
		WaitForSingleObject(hHandle, INFINITE);
		ResetEvent(hHandle);

		if (SharedInfo::bMachineStopFlag == TRUE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(_eMEASURE_CD_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}

		switch (GetCurrentTotalStep())
		{
		case _eMEASURE_CD_FLOW_IDLE:
		{
			break;
		}
		case _eMEASURE_CD_FLOW_START:
		{
			m_timeStart = CTime::GetCurrentTime(); //KJT 20210329
			SharedInfo::m_timeUnitTact = m_timeStart;

			GetLocalTime(&st);
			m_strPath.Format(_T("%s\\Result\\MeasureCd\\MeasureCd_%s_%04d%02d%02d%02d%02d%02d.csv"), SharedInfo::VisionAgentPath, SharedInfo::Active.tchStickId, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond); //KJT 20210412

			memset(m_dMeasurePosXY, 0x0, sizeof(m_dMeasurePosXY));
			memset(m_VisionResultCdValue, 0x0, sizeof(m_VisionResultCdValue));

			int nPoint = 0;

			m_nMeasureType = 1;

			if (m_nMeasureType == 0)
			{
				double dTegkeyPos[2][18] = { 0.0, };
				////1
				dTegkeyPos[0][0] = -430.4009;
				dTegkeyPos[1][0] = 32.9881;

				dTegkeyPos[0][1] = -266.2073;
				dTegkeyPos[1][1] = 32.9881;

				dTegkeyPos[0][2] = -94.4297;
				dTegkeyPos[1][2] = 32.9881;

				dTegkeyPos[0][3] = 77.3479;
				dTegkeyPos[1][3] = 32.9881;

				dTegkeyPos[0][4] = 249.1255;
				dTegkeyPos[1][4] = 32.9881;

				dTegkeyPos[0][5] = 420.9031;
				dTegkeyPos[1][5] = 32.9881;

				////2
				dTegkeyPos[0][6] = -430.4009;
				dTegkeyPos[1][6] = 0.1241;

				dTegkeyPos[0][7] = -266.2073;
				dTegkeyPos[1][7] = 0.1241;

				dTegkeyPos[0][8] = -94.4297;
				dTegkeyPos[1][8] = 0.1241;

				dTegkeyPos[0][9] = 77.3479;
				dTegkeyPos[1][9] = 0.1241;

				dTegkeyPos[0][10] = 249.1255;
				dTegkeyPos[1][10] = 0.1241;

				dTegkeyPos[0][11] = 420.9031;
				dTegkeyPos[1][11] = 0.1241;

				////3
				dTegkeyPos[0][12] = -430.4009;
				dTegkeyPos[1][12] = -32.4871;

				dTegkeyPos[0][13] = -266.2073;
				dTegkeyPos[1][13] = -32.4871;

				dTegkeyPos[0][14] = -94.4297;
				dTegkeyPos[1][14] = -32.4871;

				dTegkeyPos[0][15] = 77.3479;
				dTegkeyPos[1][15] = -32.4871;

				dTegkeyPos[0][16] = 249.1255;
				dTegkeyPos[1][16] = -32.4871;

				dTegkeyPos[0][17] = 420.9031;
				dTegkeyPos[1][17] = -32.4871;


				////1
				m_dMeasurePosXY[0][0] = dTegkeyPos[0][0] + 11.1742;
				m_dMeasurePosXY[1][0] = dTegkeyPos[1][0] + 0.9546;

				m_dMeasurePosXY[0][1] = dTegkeyPos[0][0] + 86.8246;
				m_dMeasurePosXY[1][1] = dTegkeyPos[1][0] + 0.9546;

				m_dMeasurePosXY[0][2] = dTegkeyPos[0][1] - 1.7186;
				m_dMeasurePosXY[1][2] = dTegkeyPos[1][1] + 0.9546;

				m_dMeasurePosXY[0][3] = dTegkeyPos[0][2] + 18.7582;
				m_dMeasurePosXY[1][3] = dTegkeyPos[1][2] + 0.9546;

				m_dMeasurePosXY[0][4] = dTegkeyPos[0][3] - 77.369;
				m_dMeasurePosXY[1][4] = dTegkeyPos[1][3] + 0.9546;

				m_dMeasurePosXY[0][5] = dTegkeyPos[0][3] - 1.7186;
				m_dMeasurePosXY[1][5] = dTegkeyPos[1][3] + 0.9546;

				m_dMeasurePosXY[0][6] = dTegkeyPos[0][4] + 18.7582;
				m_dMeasurePosXY[1][6] = dTegkeyPos[1][4] + 0.9546;

				m_dMeasurePosXY[0][7] = dTegkeyPos[0][5] - 77.369;
				m_dMeasurePosXY[1][7] = dTegkeyPos[1][5] + 0.9546;

				m_dMeasurePosXY[0][8] = dTegkeyPos[0][5] - 1.7186;
				m_dMeasurePosXY[1][8] = dTegkeyPos[1][5] + 0.9546;

				////2
				m_dMeasurePosXY[0][9] = dTegkeyPos[0][6] + 11.1742;
				m_dMeasurePosXY[1][9] = dTegkeyPos[1][6] - 0.0566; // 0.1198;

				m_dMeasurePosXY[0][10] = dTegkeyPos[0][6] + 86.8246;
				m_dMeasurePosXY[1][10] = dTegkeyPos[1][6] - 0.0566; // 0.1198;

				m_dMeasurePosXY[0][11] = dTegkeyPos[0][7] - 1.7186;
				m_dMeasurePosXY[1][11] = dTegkeyPos[1][7] - 0.0566; // 0.1198;

				m_dMeasurePosXY[0][12] = dTegkeyPos[0][8] + 18.7582;
				m_dMeasurePosXY[1][12] = dTegkeyPos[1][8] - 0.0566; // 0.1198;

				m_dMeasurePosXY[0][13] = dTegkeyPos[0][9] - 77.369;
				m_dMeasurePosXY[1][13] = dTegkeyPos[1][9] - 0.0566; // 0.1198;

				m_dMeasurePosXY[0][14] = dTegkeyPos[0][9] - 1.7186;
				m_dMeasurePosXY[1][14] = dTegkeyPos[1][9] - 0.0566; // 0.1198;

				m_dMeasurePosXY[0][15] = dTegkeyPos[0][10] + 18.7582;
				m_dMeasurePosXY[1][15] = dTegkeyPos[1][10] - 0.0566; // 0.1198;

				m_dMeasurePosXY[0][16] = dTegkeyPos[0][11] - 77.369;
				m_dMeasurePosXY[1][16] = dTegkeyPos[1][11] - 0.0566; // 0.1198;

				m_dMeasurePosXY[0][17] = dTegkeyPos[0][11] - 1.7186;
				m_dMeasurePosXY[1][17] = dTegkeyPos[1][11] - 0.0566; // 0.1198;

				////3
				m_dMeasurePosXY[0][18] = dTegkeyPos[0][12] + 11.1742;
				m_dMeasurePosXY[1][18] = dTegkeyPos[1][12] - 1.447;

				m_dMeasurePosXY[0][19] = dTegkeyPos[0][12] + 86.8246;
				m_dMeasurePosXY[1][19] = dTegkeyPos[1][12] - 1.447;

				m_dMeasurePosXY[0][20] = dTegkeyPos[0][13] - 1.7186;
				m_dMeasurePosXY[1][20] = dTegkeyPos[1][13] - 1.447;

				m_dMeasurePosXY[0][21] = dTegkeyPos[0][14] + 18.7582;
				m_dMeasurePosXY[1][21] = dTegkeyPos[1][14] - 1.447;

				m_dMeasurePosXY[0][22] = dTegkeyPos[0][15] - 77.369;
				m_dMeasurePosXY[1][22] = dTegkeyPos[1][15] - 1.447;

				m_dMeasurePosXY[0][23] = dTegkeyPos[0][15] - 1.7186;
				m_dMeasurePosXY[1][23] = dTegkeyPos[1][15] - 1.447;

				m_dMeasurePosXY[0][24] = dTegkeyPos[0][16] + 18.7582;
				m_dMeasurePosXY[1][24] = dTegkeyPos[1][16] - 1.447;

				m_dMeasurePosXY[0][25] = dTegkeyPos[0][17] - 77.369;
				m_dMeasurePosXY[1][25] = dTegkeyPos[1][17] - 1.447;

				m_dMeasurePosXY[0][26] = dTegkeyPos[0][17] - 1.7186;
				m_dMeasurePosXY[1][26] = dTegkeyPos[1][17] - 1.447;

				m_nMeasureCountMax = 27; //Temp
				for (int i = 0; i < m_nMeasureCountMax; i++)
				{
					Str.Format(_T("CD MeasurePos[%d] X:%.5f, Y:%.5f"), i, m_dMeasurePosXY[0][i], m_dMeasurePosXY[1][i]);

					m_dMeasurePosXY[0][i] *= CModelData::m_AtMaterialPara.Info.dTensionRatioX;
					m_dMeasurePosXY[1][i] *= CModelData::m_AtMaterialPara.Info.dTensionRatioY; //KJT 20210415

					m_dMeasurePosXY[0][i] *= STICK_FLIP_XY;
					m_dMeasurePosXY[1][i] *= STICK_FLIP_XY;

					Str.AppendFormat(_T(", Real X:%.5f, Y:%.5f"), m_dMeasurePosXY[0][i], m_dMeasurePosXY[1][i]);
					Total_Msg(Str);
				}
			}
			else //KJT 20210429 TEST Glass
			{
				m_dMeasurePosXY[0][0] = -10.0;
				m_dMeasurePosXY[1][0] = -10.0;

				m_dMeasurePosXY[0][1] = -10.0;
				m_dMeasurePosXY[1][1] = 10.0;

				m_dMeasurePosXY[0][2] = 10.0;
				m_dMeasurePosXY[1][2] = 10.0;

				m_dMeasurePosXY[0][3] = 10.0;
				m_dMeasurePosXY[1][3] = -10.0;

				m_nMeasureCountMax = 4; //Temp
			}


			/////////////
			SharedInfo::nGantryZ1View = eViewReview10X;

			m_nMeasurePoint = 0;

			SharedInfo::LightAllOff();
			Sleep(500);

			//KJT 20210824
			for (int i = 0; i < BACKLIGHT_CH_COUNT; i++)
				nBackLightVal[i] = CModelData::m_PpaPara.Info.nPpaBacklight[CModelData::m_InspectionPara.Info.nMeasureCameraMode];

			nRing = CModelData::m_PpaPara.Info.nPpaRing[CModelData::m_InspectionPara.Info.nMeasureCameraMode];
			nCoaxial = CModelData::m_PpaPara.Info.nPpaCoAxial[CModelData::m_InspectionPara.Info.nMeasureCameraMode];

			if (CModelData::m_PpaPara.Info.nPpaLightType == eLight_Back)
			{
				g_CommBack_Light.BackLightOn(nBackLightVal);
				Sleep(30);
			}
			else
			{
				g_CommReview_Light.SetLight_Review(nRing, nCoaxial);
				Sleep(30);
			}

			if (SharedInfo::LoadGlassMappingData() == FALSE) //KJT 20210328
			{
				SetStep(_eMEASURE_CD_FLOW_ERROR, _T("_eMEASURE_CD_FLOW_ERROR"));
				break;
			}

			SetStep(_eMEASURE_CD_FLOW_INTERLOCK, _T("_eMEASURE_CD_FLOW_INTERLOCK"));
			break;
		}
		case _eMEASURE_CD_FLOW_INTERLOCK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(_eMEASURE_CD_FLOW_ERROR, _T("_eMEASURE_CD_FLOW_ERROR"));
			}
			else
			{
				SetStep(_eMEASURE_CD_FLOW_UNLOADER_READY, _T("_eMEASURE_CD_FLOW_UNLOADER_READY"));
			}
			break;

#pragma region //Unloader Ready
		case _eMEASURE_CD_FLOW_UNLOADER_READY:
			Devs::m_Ready_UnloaderFlow.Start();

			SetStep(_eMEASURE_CD_FLOW_UNLOADER_READY_CHECK, _T("_eMEASURE_CD_FLOW_UNLOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMEASURE_CD_FLOW_UNLOADER_READY_CHECK:
			if (Devs::m_Ready_UnloaderFlow.IsFlowDone())
			{
				SetStep(_eMEASURE_CD_FLOW_GANTRY_ZX_READY, _T("_eMEASURE_CD_FLOW_GANTRY_ZX_READY"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eMEASURE_CD_FLOW_ERROR, _T("_eMEASURE_CD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMEASURE_CD_FLOW_UNLOADER_READY_CHECK, _T("_eMEASURE_CD_FLOW_UNLOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Gantry Z, X Ready
		case _eMEASURE_CD_FLOW_GANTRY_ZX_READY:
			Devs::m_Ready_GantryZX_Flow.Start();

			SetStep(_eMEASURE_CD_FLOW_GANTRY_ZX_READY_CHECK, _T("_eMEASURE_CD_FLOW_GANTRY_ZX_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMEASURE_CD_FLOW_GANTRY_ZX_READY_CHECK:
			if (Devs::m_Ready_GantryZX_Flow.IsFlowDone())
			{
				SetStep(_eMEASURE_CD_FLOW_LOADER_READY, _T("_eMEASURE_CD_FLOW_LOADER_READY"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eMEASURE_CD_FLOW_ERROR, _T("_eMEASURE_CD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMEASURE_CD_FLOW_GANTRY_ZX_READY_CHECK, _T("_eMEASURE_CD_FLOW_GANTRY_ZX_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Loader Ready
		case _eMEASURE_CD_FLOW_LOADER_READY:
			Devs::m_Ready_LoaderFlow.Start();

			SetStep(_eMEASURE_CD_FLOW_LOADER_READY_CHECK, _T("_eMEASURE_CD_FLOW_LOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMEASURE_CD_FLOW_LOADER_READY_CHECK:
			if (Devs::m_Ready_LoaderFlow.IsFlowDone())
			{
				SetStep(_eMEASURE_CD_FLOW_PAPER_UNLOADER_ZXY_READY, _T("_eMEASURE_CD_FLOW_PAPER_UNLOADER_ZXY_READY"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eMEASURE_CD_FLOW_ERROR, _T("_eMEASURE_CD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMEASURE_CD_FLOW_LOADER_READY_CHECK, _T("_eMEASURE_CD_FLOW_LOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //PaperUnloader Ready
		case _eMEASURE_CD_FLOW_PAPER_UNLOADER_ZXY_READY:
			Devs::m_Ready_PaperUnloaderFlow.Start();

			SetStep(_eMEASURE_CD_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK, _T("_eMEASURE_CD_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMEASURE_CD_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK:
			if (Devs::m_Ready_PaperUnloaderFlow.IsFlowDone())
			{
				SetStep(_eMEASURE_CD_FLOW_GANTRY_XY_MEASURE_POS_1ST, _T("_eMEASURE_CD_FLOW_GANTRY_XY_MEASURE_POS_1ST"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eMEASURE_CD_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK : Time Out"), eBOX_ALIGN_FLOW + 1);
				SetStep(_eMEASURE_CD_FLOW_ERROR, _T("_eMEASURE_CD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMEASURE_CD_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK, _T("_eMEASURE_CD_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Gantry XYZ First Pos Move
		case _eMEASURE_CD_FLOW_GANTRY_XY_MEASURE_POS_1ST:
			m_dTargetPosX = dPosX = m_dMeasurePosXY[0][m_nMeasurePoint];
			m_dTargetPosY = dPosY = m_dMeasurePosXY[1][m_nMeasurePoint];

			if (m_nMeasureType == 0)
				SharedInfo::GetMappingPos(TRUE, CModelData::m_InspectionPara.Info.bMappingDataUse, &m_dTargetPosX, &m_dTargetPosY); //KJT 20210312
			else
				SharedInfo::GetMappingPos(FALSE, CModelData::m_InspectionPara.Info.bMappingDataUse, &m_dTargetPosX, &m_dTargetPosY); //KJT 20210312

			Devs::m_GantryMotion.Move_Gantry_X_Pos(m_dTargetPosX, TRUE);
			Sleep(20); //!!
			Devs::m_GantryMotion.Move_Gantry_Y_Pos(m_dTargetPosY);
			Sleep(20); //!!

			SetStep(_eMEASURE_CD_FLOW_GANTRY_XY_MEASURE_POS_1ST_CHECK, _T("_eMEASURE_CD_FLOW_GANTRY_XY_MEASURE_POS_1ST_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMEASURE_CD_FLOW_GANTRY_XY_MEASURE_POS_1ST_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Pos(m_dTargetPosX) && Devs::m_GantryMotion.Is_Gantry_Y_Pos(m_dTargetPosY))
			{
				Sleep(500); //!!

				SetStep(_eMEASURE_CD_FLOW_GANTRY_Z1_MEASURE_POS, _T("_eMEASURE_CD_FLOW_GANTRY_Z1_MEASURE_POS"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eMEASURE_CD_FLOW_ERROR, _T("_eMEASURE_CD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMEASURE_CD_FLOW_GANTRY_XY_MEASURE_POS_1ST_CHECK, _T("_eMEASURE_CD_FLOW_GANTRY_XY_MEASURE_POS_1ST_CHECK"));
			}
			break;

		case _eMEASURE_CD_FLOW_GANTRY_Z1_MEASURE_POS:
			Devs::m_GantryMotion.Move_GantryZ1_InspectionReview_Pos();
			Sleep(20); //!!

			SetStep(_eMEASURE_CD_FLOW_GANTRY_Z1_MEASURE_POS_CHECK, _T("_eMEASURE_CD_FLOW_GANTRY_Z1_MEASURE_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMEASURE_CD_FLOW_GANTRY_Z1_MEASURE_POS_CHECK:
			if (Devs::m_GantryMotion.Is_GantryZ1_InspectionReview_Pos())
			{
				Sleep(500); //!!
				SetStep(_eMEASURE_CD_FLOW_AUTOFOCUS_CHECK, _T("_eMEASURE_CD_FLOW_AUTOFOCUS_CHECK"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eMEASURE_CD_FLOW_ERROR, _T("_eMEASURE_CD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMEASURE_CD_FLOW_GANTRY_Z1_MEASURE_POS_CHECK, _T("_eMEASURE_CD_FLOW_GANTRY_Z1_MEASURE_POS_CHECK"));
			}
			break;
#pragma endregion

		case _eMEASURE_CD_FLOW_GANTRY_XY_MEASURE_POS_2ND:
			m_dTargetPosX = dPosX = m_dMeasurePosXY[0][m_nMeasurePoint];
			m_dTargetPosY = dPosY = m_dMeasurePosXY[1][m_nMeasurePoint];

			if (m_nMeasureType == 0)
				SharedInfo::GetMappingPos(TRUE, CModelData::m_InspectionPara.Info.bMappingDataUse, &m_dTargetPosX, &m_dTargetPosY); //KJT 20210312
			else
				SharedInfo::GetMappingPos(FALSE, CModelData::m_InspectionPara.Info.bMappingDataUse, &m_dTargetPosX, &m_dTargetPosY); //KJT 20210312

			Devs::m_GantryMotion.Move_Gantry_X_Pos(m_dTargetPosX, TRUE);
			Sleep(20); //!!
			Devs::m_GantryMotion.Move_Gantry_Y_Pos(m_dTargetPosY);
			Sleep(20); //!!

			SetStep(_eMEASURE_CD_FLOW_GANTRY_XY_MEASURE_POS_2ND_CHECK, _T("_eMEASURE_CD_FLOW_GANTRY_XY_MEASURE_POS_2ND_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMEASURE_CD_FLOW_GANTRY_XY_MEASURE_POS_2ND_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Pos(m_dTargetPosX) && Devs::m_GantryMotion.Is_Gantry_Y_Pos(m_dTargetPosY))
			{
				Sleep(500); //!!

				SetStep(_eMEASURE_CD_FLOW_AUTOFOCUS_CHECK, _T("_eMEASURE_CD_FLOW_AUTOFOCUS_CHECK"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eMEASURE_CD_FLOW_ERROR, _T("_eMEASURE_CD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMEASURE_CD_FLOW_GANTRY_XY_MEASURE_POS_2ND_CHECK, _T("_eMEASURE_CD_FLOW_GANTRY_XY_MEASURE_POS_2ND_CHECK"));
			}
			break;

		case _eMEASURE_CD_FLOW_AUTOFOCUS_CHECK: //KJT 20210313
			if (CModelData::m_PpaPara.Info.nPpaFocusType == eFocusType_Both || CModelData::m_PpaPara.Info.nPpaFocusType == eFocusType_Laser)
				SetStep(_eMEASURE_CD_FLOW_LASER_FOCUS_START, _T("_eMEASURE_CD_FLOW_LASER_FOCUS_START"));
			else if (CModelData::m_PpaPara.Info.nPpaFocusType == eFocusType_Image)
				SetStep(_eMEASURE_CD_FLOW_IMAGE_FOCUS_START, _T("_eMEASURE_CD_FLOW_IMAGE_FOCUS_START"));
			else
				SetStep(_eMEASURE_CD_FLOW_GRAB_START, _T("_eMEASURE_CD_FLOW_GRAB_START"));
			break;

		case _eMEASURE_CD_FLOW_LASER_FOCUS_START:
			Devs::m_GantryMotion.LaserFocusMove();

			SetStep(_eMEASURE_CD_FLOW_LASER_FOCUS_CHECK, _T("_eMEASURE_CD_FLOW_LASER_FOCUS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMEASURE_CD_FLOW_LASER_FOCUS_CHECK: //KJT 20210313
			if (Devs::m_GantryMotion.LaserFocusMoveCheck())
			{
				Sleep(500); //!!	//KJT 20210321

				if (CModelData::m_PpaPara.Info.nPpaFocusType == eFocusType_Both)
					SetStep(_eMEASURE_CD_FLOW_IMAGE_FOCUS_START, _T("_eMEASURE_CD_FLOW_IMAGE_FOCUS_START"));
				else
					SetStep(_eMEASURE_CD_FLOW_GRAB_START, _T("_eMEASURE_CD_FLOW_GRAB_START"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eMEASURE_CD_FLOW_ERROR, _T("_eMEASURE_CD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMEASURE_CD_FLOW_LASER_FOCUS_CHECK, _T("_eMEASURE_CD_FLOW_LASER_FOCUS_CHECK"));
			}
			break;

		case _eMEASURE_CD_FLOW_IMAGE_FOCUS_START:
#ifndef SIM_MODE
			g_pReview10x->m_bAfEnd = FALSE;
			g_pReview10x->AutofoucsRun();
#endif
			SetStep(_eMEASURE_CD_FLOW_IMAGE_FOCUS_CHECK, _T("_eMEASURE_CD_FLOW_IMAGE_FOCUS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMEASURE_CD_FLOW_IMAGE_FOCUS_CHECK:
#ifndef SIM_MODE
			if (g_pReview10x->m_bAfEnd == TRUE)
			{
				Sleep(IMAGE_FOCUS_DELAY);
				SetStep(_eMEASURE_CD_FLOW_GRAB_START, _T("_eMEASURE_CD_FLOW_GRAB_START"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eMEASURE_CD_FLOW_ERROR, _T("_eMEASURE_CD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMEASURE_CD_FLOW_IMAGE_FOCUS_CHECK, _T("_eMEASURE_CD_FLOW_IMAGE_FOCUS_CHECK"));
			}
#else
			Sleep(IMAGE_FOCUS_DELAY);
			SetStep(_eMEASURE_CD_FLOW_GRAB_START, _T("_eMEASURE_CD_FLOW_GRAB_START"));
#endif
			break;

		case _eMEASURE_CD_FLOW_GRAB_START:
#ifndef SIM_MODE
			if (m_nMeasureType == 0)
			{
				m_CameraInfo = Devs::m_Camera10X->GetCameraInfo();

				m_CameraInfo.nBlackWhite = CModelData::m_PpaPara.Info.nPpaBlackWhiteType;
				m_CameraInfo.nBin = CModelData::m_PpaPara.Info.nPpaThreshold[CModelData::m_InspectionPara.Info.nMeasureCameraMode]; //KJT 20210824

#if 0//KJT 20210728 Junying
				double dResX = 0.0, dResY = 0.0;
				SharedInfo::GetReviewCamResolution(SharedInfo::nGantryZ1View, &dResX, &dResY);
				m_CameraInfo.dResolX = dResX;
				m_CameraInfo.dResolY = dResY;
#endif
				Devs::m_Camera10X->SetCameraInfo(m_CameraInfo);
				m_BlobData = Devs::m_Camera10X->GetBlobData();
#if 0
				m_BlobData.dMarkSizeX = CModelData::Stick.Info[m_nActiveStick].MarkSizeX;
				m_BlobData.dMarkSizeY = CModelData::Stick.Info[m_nActiveStick].MarkSizeY;
#else
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
				m_BlobData.nQuantityX = 1;
				m_BlobData.nQuantityY = 1;

				m_BlobData.dRangeRateX = 0.8;
				m_BlobData.dRangeRateY = 0.8;
#endif
			}
			else //KJT 20210429 TEST Glass
			{
				m_CameraInfo = Devs::m_Camera10X->GetCameraInfo();

				m_CameraInfo.nBlackWhite = 1;
				m_CameraInfo.nBin = CModelData::m_AlignPara.Info.nVerticalMainAlignThreshold;
#if 0//KJT 20210728 Junying
				double dResX = 0.0, dResY = 0.0;
				SharedInfo::GetReviewCamResolution(SharedInfo::nGantryZ1View, &dResX, &dResY);
				m_CameraInfo.dResolX = dResX;
				m_CameraInfo.dResolY = dResY;
#endif
				Devs::m_Camera10X->SetCameraInfo(m_CameraInfo);
				m_BlobData = Devs::m_Camera10X->GetBlobData();

				m_BlobData.dMarkSizeX = CModelData::m_GlassPara.Info.dGlassAlignMarkSizeX;
				m_BlobData.dMarkSizeY = CModelData::m_GlassPara.Info.dGlassAlignMarkSizeY;
				m_BlobData.dPitchX = 0.0;
				m_BlobData.dPitchY = 0.0;

				m_BlobData.nQuantityX = 1;
				m_BlobData.nQuantityY = 1;

				m_BlobData.dRangeRateX = 0.8;
				m_BlobData.dRangeRateY = 0.8;
			}

			Devs::m_Camera10X->SetBlobData(m_BlobData);
			stResult = Devs::m_Camera10X->FindBlobPpa();

			if (stResult.bResult == FALSE) //KJT 20210404
			{
				m_nGrabRetryCnt++;
				if (m_nGrabRetryCnt > 3)
				{
					SetStep(_eMEASURE_CD_FLOW_ERROR, _T("_eMEASURE_CD_FLOW_ERROR"));
					break;
				}
				//KJT 20210313
				if (CModelData::m_PpaPara.Info.nPpaFocusType == eFocusType_Both || CModelData::m_PpaPara.Info.nPpaFocusType == eFocusType_Laser)
					SetStep(_eMEASURE_CD_FLOW_LASER_FOCUS_START, _T("_eMEASURE_CD_FLOW_LASER_FOCUS_START"));
				else if (CModelData::m_PpaPara.Info.nPpaFocusType == eFocusType_Image)
					SetStep(_eMEASURE_CD_FLOW_IMAGE_FOCUS_START, _T("_eMEASURE_CD_FLOW_IMAGE_FOCUS_START"));
				else
					SetStep(_eMEASURE_CD_FLOW_GRAB_START, _T("_eMEASURE_CD_FLOW_GRAB_START"));

				break;
			}
			Sleep(50);

			m_VisionResultCdValue[0][m_nMeasurePoint] = stResult.dCdX;
			m_VisionResultCdValue[1][m_nMeasurePoint] = stResult.dCdY;
#else
			m_VisionResultCdValue[0][m_nMeasurePoint] = 0.0;
			m_VisionResultCdValue[1][m_nMeasurePoint] = 0.0;
#endif

			SetStep(_eMEASURE_CD_FLOW_GRAB_DONE_CHECK, _T("_eMEASURE_CD_FLOW_GRAB_DONE_CHECK"));
			break;

		case _eMEASURE_CD_FLOW_GRAB_DONE_CHECK:
			m_nGrabRetryCnt = 0;
			if (m_nMeasurePoint >= m_nMeasureCountMax - 1)
			{
				m_nMeasurePoint = 0;

				SaveMeaureCdResult();

				SharedInfo::LightAllOff(); //KJT 20210226

				SetStep(_eMEASURE_CD_FLOW_FINISH_GANTRY_Z1_WAIT_POS, _T("_eMEASURE_CD_FLOW_FINISH_GANTRY_Z1_WAIT_POS"));
			}
			else
			{
				Str.Format(_T("m_nMeasurePoint:%d Cd Diff X[0]:%.5f, Y[0]:%.5f"), m_nMeasurePoint, m_VisionResultCdValue[0][m_nMeasurePoint], m_VisionResultCdValue[1][m_nMeasurePoint]);
				Total_Msg(Str);

				m_nMeasurePoint++;

				Sleep(100);
				SetStep(_eMEASURE_CD_FLOW_GANTRY_XY_MEASURE_POS_2ND, _T("_eMEASURE_CD_FLOW_GANTRY_XY_MEASURE_POS_2ND"));
			}
			break;

		case _eMEASURE_CD_FLOW_FINISH_GANTRY_Z1_WAIT_POS:
			Devs::m_GantryMotion.Move_GantryZ_All_Wait_Pos();
			Sleep(20); //!!

			SetStep(_eMEASURE_CD_FLOW_FINISH_GANTRY_Z1_WAIT_POS_CHECK, _T("_eMEASURE_CD_FLOW_FINISH_GANTRY_Z1_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);

			break;

		case _eMEASURE_CD_FLOW_FINISH_GANTRY_Z1_WAIT_POS_CHECK:
			if (Devs::m_GantryMotion.Is_GantryZ_All_Wait_Pos())
			{
				SetStep(_eMEASURE_CD_FLOW_FINISH_GANTRY_XY_WAIT_POS, _T("_eMEASURE_CD_FLOW_FINISH_GANTRY_XY_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eMEASURE_CD_FLOW_ERROR, _T("_eMEASURE_CD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMEASURE_CD_FLOW_FINISH_GANTRY_Z1_WAIT_POS_CHECK, _T("_eMEASURE_CD_FLOW_FINISH_GANTRY_Z1_WAIT_POS_CHECK"));
			}
			break;

		case _eMEASURE_CD_FLOW_FINISH_GANTRY_XY_WAIT_POS:
			Devs::m_GantryMotion.Move_Gantry_X_Wait_Pos();
			Sleep(20); //!!
			Devs::m_GantryMotion.Move_Gantry_Y_Wait_Pos();
			Sleep(20); //!!

			SetStep(_eMEASURE_CD_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK, _T("_eMEASURE_CD_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMEASURE_CD_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Wait_Pos() && Devs::m_GantryMotion.Is_Gantry_Y_Wait_Pos())
			{
				SetStep(_eMEASURE_CD_FLOW_DONE, _T("_eMEASURE_CD_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eMEASURE_CD_FLOW_ERROR, _T("_eMEASURE_CD_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMEASURE_CD_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK, _T("_eMEASURE_CD_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK"));
			}
			break;

		case _eMEASURE_CD_FLOW_ERROR:
			break;

		case _eMEASURE_CD_FLOW_DONE:
		{
			SharedInfo::nPrevFlowID = eMEASURE_CD_FLOW;

			m_bFlowDone = TRUE;

			SharedInfo::CalTactTime(_T("MEASURE_CD_FLOW"), m_timeStart); //KJT 20210329

			SetStep(_eMEASURE_CD_FLOW_IDLE, _T("_eMEASURE_CD_FLOW_IDLE"));
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

BOOL CMeasureCdFlow::FlowInterlock()
{
	CString Str = _T("");

	//Servo On Check
	if (SharedInfo::GetServoOnStatus(AXIS_GANTRY_X) != TRUE)
	{
		Total_Msg(_T("Gantry X Servo On Check !!!"));
		return FALSE;
	}
	if (SharedInfo::GetServoOnStatus(AXIS_VIRTUAL_GANTRY_Y) != TRUE)
	{
		Total_Msg(_T("Gantry Y Servo On Check !!!"));
		return FALSE;
	}

	//Home Status Check
	if (SharedInfo::GetHomeStatus(AXIS_GANTRY_X) != TRUE)
	{
		Total_Msg(_T("Gantry X Home Status Check !!!"));
		return FALSE;
	}
	if (SharedInfo::GetHomeStatus(AXIS_VIRTUAL_GANTRY_Y) != TRUE)
	{
		Total_Msg(_T("Gantry Y Home Status Check !!!"));
		return FALSE;
	}

	if (Devs::m_CassetteMotion.Is_CSTPickUpUnitBwd() == FALSE)
	{
		Total_Msg(_T("Check Pickup Unit Backward !!!"));
		return FALSE;
	}
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

BOOL CMeasureCdFlow::SaveMeaureCdResult()
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
			StrTitle.AppendFormat(_T("Mask,%s\n\n"), SharedInfo::Active.tchStickId);
			f.WriteString(StrTitle);
		}
		else
		{
			TRACE("File Open Faile~!!\r\n");
			return false;
		}
	}

	f.SeekToEnd();


	int nCountX = MAX_TP_COUNT / 2;

	{
		////////////////////////////////////////////////////////////////////////////////////////////////
		str.AppendFormat(_T("Measure Cd\n"));

		//X
		str.AppendFormat(_T("TargetPos,"));
		for (i = 0; i < m_nMeasureCountMax; i++)
		{
			str.AppendFormat(_T("%.5f,"), m_dMeasurePosXY[0][i] * STICK_FLIP_XY);
		}
		str.AppendFormat(_T("\n"));
		str.AppendFormat(_T("RealPos,"));
		for (i = 0; i < m_nMeasureCountMax; i++)
		{
			str.AppendFormat(_T("%.5f,"), m_dMeasurePosXY[0][i]);
		}
		str.AppendFormat(_T("\n"));
		str.AppendFormat(_T("Diff X,"));
		for (i = 0; i < m_nMeasureCountMax; i++)
		{
			if (CModelData::m_InspectionPara.Info.nStickTensionUseMode == eSTICK_TENSION_ALIGN) //KJT 20210406
				str.AppendFormat(_T("%.1f,"), (CModelData::m_AtMaterialPara.Info.dSlotSizeX[0][0] - m_VisionResultCdValue[0][i]) * 1000);
			else
				str.AppendFormat(_T("%.1f,"), (CModelData::m_MaterialPara.Info.dSlotSizeX[0][0] - m_VisionResultCdValue[0][i]) * 1000);
		}
		str.AppendFormat(_T("\n\n"));

		//Y
		str.AppendFormat(_T("TargetPos,"));
		for (i = 0; i < m_nMeasureCountMax; i++)
		{
			str.AppendFormat(_T("%.5f,"), m_dMeasurePosXY[1][i] * STICK_FLIP_XY);
		}
		str.AppendFormat(_T("\n"));
		str.AppendFormat(_T("RealPos,"));
		for (i = 0; i < m_nMeasureCountMax; i++)
		{
			str.AppendFormat(_T("%.5f,"), m_dMeasurePosXY[1][i]);
		}
		str.AppendFormat(_T("\n"));
		str.AppendFormat(_T("Diff Y,"));
		for (i = 0; i < m_nMeasureCountMax; i++)
		{
			if (CModelData::m_InspectionPara.Info.nStickTensionUseMode == eSTICK_TENSION_ALIGN) //KJT 20210406
				str.AppendFormat(_T("%.1f,"), (CModelData::m_AtMaterialPara.Info.dSlotSizeY[0][0] - m_VisionResultCdValue[1][i]) * 1000);
			else
				str.AppendFormat(_T("%.1f,"), (CModelData::m_MaterialPara.Info.dSlotSizeY[0][0] - m_VisionResultCdValue[1][i]) * 1000);
		}
		str.AppendFormat(_T("\n"));
	}

	f.WriteString(str);
	f.Close();

	return 0;
}