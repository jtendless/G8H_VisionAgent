#include "stdafx.h"
#include "SwAlignFlow.h"
#include "Log/Logger.h"
#include "Vision/Devs.h"
#include "Data/ModelData.h"
#include "CamAreaModul.h"
#include "Data/SystemData.h"
#include "FmmLight1.h"

CSwAlignFlow::CSwAlignFlow()
{
	m_dDiffPos[0] = 0.0;
	m_dDiffPos[1] = 0.0;
	m_dDiffPos[2] = 0.0;

	m_dTarget[0] = 0.0;
	m_dTarget[1] = 0.0;
	m_dTarget[2] = 0.0;

	m_nAlignPoint = 0;

	memset(m_AlignPointValue, 0x0, sizeof(m_AlignPointValue));
	memset(m_AlignVisionResultValue, 0x0, sizeof(m_AlignVisionResultValue));

	m_eSwAlignType = eSwAlign_EdgeSlot; //KJT 20210419
}


CSwAlignFlow::~CSwAlignFlow()
{
}

BOOL CSwAlignFlow::InitProcess()
{
	m_StateComplete = NULL;
	m_FlowFinish = TRUE;
	m_bTerminate = FALSE;
	m_bFlowDone = TRUE;

#pragma region //Step Group
	int nGroupIndex = 0;

	m_sGroupInfo[nGroupIndex].m_bProcessingFlag = FALSE;
	m_sGroupInfo[nGroupIndex].nStartStep = _eSW_ALIGN_FLOW_START;
	m_sGroupInfo[nGroupIndex].nEndStep = _eSW_ALIGN_FLOW_INTERLOCK;
	m_sGroupInfo[nGroupIndex].strGroupName.Format(_T("%d. Start"), nGroupIndex + 1);
	nGroupIndex++;

	m_nMaxGroupCount = nGroupIndex;
#pragma endregion

	//SetProcessLog(Process_Msg);
	//SetAlarmLog(Alarm_Msg);

	hHandle = CreateEvent(NULL, TRUE, FALSE, NULL);
	SetHandle(hHandle);
	pThread = AfxBeginThread(ThreadFunction, this);
	//pMappingProc = CMappingProc::GetInstance();
	return TRUE;
}
BOOL CSwAlignFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eSW_ALIGN_FLOW_IDLE);

	if (hHandle != NULL)
	{
		CloseHandle(hHandle);
		hHandle = NULL;
	}

	return TRUE;
}
BOOL CSwAlignFlow::Start(int nStep)
{
	memset(Devs::m_GantryMotion.m_dTpX, 0, sizeof(Devs::m_GantryMotion.m_dTpX));
	memset(Devs::m_GantryMotion.m_dTpY, 0, sizeof(Devs::m_GantryMotion.m_dTpY));

	m_bFlowDone = FALSE;
	m_bStopBit = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(nStep, _T("_eSW_ALIGN_FLOW_START"));
	return TRUE;
}
BOOL CSwAlignFlow::Stop()
{
	m_bStopBit = TRUE;
	return TRUE;
}

UINT CSwAlignFlow::ThreadFunction(LPVOID lpParam)
{
	CSwAlignFlow* pFlow = NULL;

	pFlow = (CSwAlignFlow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}

VOID CSwAlignFlow::ThreadFunctionEntry(VOID)
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
	BOOL bResult = FALSE;

	double dRefPos[4][2] = { 0.0, };
	double dActPos[4][2] = { 0.0, };

	double dPosX = 0.0, dPosY = 0.0;

	double dResultDiffX = 0.0, dResultDiffY = 0.0;
	double dAverageDiffX = 0.0, dAverageDiffY = 0.0;

	int nRing, nCoaxial;
	int nBackLightVal[BACKLIGHT_CH_COUNT] = { BACKLIGHT_OFF_VALUE, };	

	while (m_FlowFinish)
	{
		WaitForSingleObject(hHandle, INFINITE);
		ResetEvent(hHandle);

		if (SharedInfo::bMachineStopFlag == TRUE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(_eSW_ALIGN_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}

		switch (GetCurrentTotalStep())
		{
		case _eSW_ALIGN_FLOW_IDLE:
		{
			break;
		}
		case _eSW_ALIGN_FLOW_START:
		{
			m_timeStart = CTime::GetCurrentTime(); //KJT 20210329
			SharedInfo::m_timeUnitTact = m_timeStart;

			SharedInfo::nCurFlowID = eSW_FLOW;

			SharedInfo::LightAllOff();
			Sleep(500); //KJT 20210820 !!
						
			for (int i = 0; i < BACKLIGHT_CH_COUNT; i++)
				nBackLightVal[i] = CModelData::m_AlignPara.Info.nSwAlignBacklight; // 10;

			nRing = CModelData::m_AlignPara.Info.nSwAlignRing;
			nCoaxial = CModelData::m_AlignPara.Info.nSwAlignCoAxial;

			Sleep(500);

			 //KJT 20210419
			if (m_eSwAlignType == eSwAlign_EdgeSlot)
			{
				//KJT 20210328
				Devs::m_MappingProc.InitializeGlassMapping(eMAPPING_ID_10X);
				if (Devs::m_MappingProc.LoadGlassMappingFile(eMAPPING_ID_10X) == FALSE)
				{
					SharedInfo::SetAlarm(_T("_eSW_ALIGN_FLOW_START : Mapping Data"), eSW_FLOW + 0);
					SetStep(_eSW_ALIGN_FLOW_ERROR, _T("_eSW_ALIGN_FLOW_ERROR"));
					break;
				}

				//LB
				m_AlignPointValue[0][0] = SharedInfo::GetReview10X_EdgeAlignSlotPosXY_LB().dPosX;
				m_AlignPointValue[1][0] = SharedInfo::GetReview10X_EdgeAlignSlotPosXY_LB().dPosY;
				//LT
				m_AlignPointValue[0][1] = SharedInfo::GetReview10X_EdgeAlignSlotPosXY_LT().dPosX;
				m_AlignPointValue[1][1] = SharedInfo::GetReview10X_EdgeAlignSlotPosXY_LT().dPosY;
				//RT
				m_AlignPointValue[0][2] = SharedInfo::GetReview10X_EdgeAlignSlotPosXY_RT().dPosX;
				m_AlignPointValue[1][2] = SharedInfo::GetReview10X_EdgeAlignSlotPosXY_RT().dPosY;
				//RB
				m_AlignPointValue[0][3] = SharedInfo::GetReview10X_EdgeAlignSlotPosXY_RB().dPosX;
				m_AlignPointValue[1][3] = SharedInfo::GetReview10X_EdgeAlignSlotPosXY_RB().dPosY;

				//g_CommLight_8ch.SetLight_Review_Coaxial(CModelData::m_AlignPara.Info.nSwAlignCoAxial);
				//Sleep(30);
				//g_CommLight_12ch.SetLight_Review_Ring(CModelData::m_AlignPara.Info.nSwAlignRing);
				//Sleep(30);
				//g_CommMLCLedLight.BackLightOn(nBackLightVal);
				//Sleep(500);

				if (CModelData::m_AlignPara.Info.nSwAlignLightType == eLight_Back)
				{
					SharedInfo::BackLightOn(CModelData::m_AlignPara.Info.nSwAlignBacklight);
					Sleep(30);
				}
				else
				{
					g_CommReview_Light.SetLight_Review(CModelData::m_AlignPara.Info.nSwAlignRing, CModelData::m_AlignPara.Info.nSwAlignCoAxial);
					Sleep(30);
				}
			}
			//DO NOT USE
			else if (m_eSwAlignType == eSwAlign_EdgeCell)
			{
				//sunghaklee
				SetStep(_eSW_ALIGN_FLOW_ERROR, _T("_eSW_ALIGN_FLOW_ERROR"));
				break;

				//////////////////////////////////////////////////////////
				//KJT 20210328
				Devs::m_MappingProc.InitializeGlassMapping(eMAPPING_ID_10X);
				if (Devs::m_MappingProc.LoadGlassMappingFile(eMAPPING_ID_10X) == FALSE)
				{
					SetStep(_eSW_ALIGN_FLOW_ERROR, _T("_eSW_ALIGN_FLOW_ERROR"));
					break;
				}

				//LB
				//m_AlignPointValue[0][0] = SharedInfo::GetReview10X_EdgeAlignCellPosXY_LB().dPosX;
				//m_AlignPointValue[1][0] = SharedInfo::GetReview10X_EdgeAlignCellPosXY_LB().dPosY;
				////LT
				//m_AlignPointValue[0][1] = SharedInfo::GetReview10X_EdgeAlignCellPosXY_LT().dPosX;
				//m_AlignPointValue[1][1] = SharedInfo::GetReview10X_EdgeAlignCellPosXY_LT().dPosY;
				////RT
				//m_AlignPointValue[0][2] = SharedInfo::GetReview10X_EdgeAlignCellPosXY_RT().dPosX;
				//m_AlignPointValue[1][2] = SharedInfo::GetReview10X_EdgeAlignCellPosXY_RT().dPosY;
				////RB
				//m_AlignPointValue[0][3] = SharedInfo::GetReview10X_EdgeAlignCellPosXY_RB().dPosX;
				//m_AlignPointValue[1][3] = SharedInfo::GetReview10X_EdgeAlignCellPosXY_RB().dPosY;

				//g_CommLight_8ch.SetLight_Review_Coaxial(CModelData::m_AlignPara.Info.nSwAlignCoAxial);
				//Sleep(30);
				//g_CommLight_12ch.SetLight_Review_Ring(CModelData::m_AlignPara.Info.nSwAlignRing);
				//Sleep(30);
				//g_CommMLCLedLight.BackLightOn(nBackLightVal);
				//Sleep(500);

				if (CModelData::m_AlignPara.Info.nSwAlignLightType == eLight_Back)
				{
					SharedInfo::BackLightOn(CModelData::m_AlignPara.Info.nSwAlignBacklight);
					Sleep(30);
				}
				else
				{
					g_CommReview_Light.SetLight_Review(CModelData::m_AlignPara.Info.nSwAlignRing, CModelData::m_AlignPara.Info.nSwAlignCoAxial);
					Sleep(30);
				}
			}
			//DO NOT USE
			else if (m_eSwAlignType == eSwAlign_Tegkey)
			{
				//sunghaklee
				SetStep(_eSW_ALIGN_FLOW_ERROR, _T("_eSW_ALIGN_FLOW_ERROR"));
				break;

				//KJT 20210328
				Devs::m_MappingProc.InitializeGlassMapping(eMAPPING_ID_10X);
				if (Devs::m_MappingProc.LoadGlassMappingFile(eMAPPING_ID_10X) == FALSE)
				{
					SetStep(_eSW_ALIGN_FLOW_ERROR, _T("_eSW_ALIGN_FLOW_ERROR"));
					break;
				}

#if 0 //TegKey
				//LB
				m_AlignPointValue[0][0] = CModelData::m_MaterialPara.Info.dTegkey_LB_X; //-397.33766;
				m_AlignPointValue[1][0] = CModelData::m_MaterialPara.Info.dTegkey_LB_Y; //-35.53009;
				//LT
				m_AlignPointValue[0][1] = CModelData::m_MaterialPara.Info.dTegkey_LT_X; //-397.33766;
				m_AlignPointValue[1][1] = CModelData::m_MaterialPara.Info.dTegkey_LT_Y; //35.53009;
				//RT
				m_AlignPointValue[0][2] = CModelData::m_MaterialPara.Info.dTegkey_RT_X; //397.33766;
				m_AlignPointValue[1][2] = CModelData::m_MaterialPara.Info.dTegkey_RT_Y; //35.53009;
				//RB
				m_AlignPointValue[0][3] = CModelData::m_MaterialPara.Info.dTegkey_RB_X; //397.33766;
				m_AlignPointValue[1][3] = CModelData::m_MaterialPara.Info.dTegkey_RB_Y; //-35.53009;
#else //TEST //KJT 20210416
				double dTegkeyPos[2][18] = { 0.0, };
				////1
				dTegkeyPos[0][0] = -430.4009;
				dTegkeyPos[1][0] = 32.9881;

				dTegkeyPos[0][5] = 420.9031;
				dTegkeyPos[1][5] = 32.9881;

				////3
				dTegkeyPos[0][12] = -430.4009;
				dTegkeyPos[1][12] = -32.4871;

				dTegkeyPos[0][17] = 420.9031;
				dTegkeyPos[1][17] = -32.4871;

				//LB
				m_AlignPointValue[0][3] = dTegkeyPos[0][0] + 86.8246;
				m_AlignPointValue[1][3] = dTegkeyPos[1][0] + 0.9546;
				//LT
				m_AlignPointValue[0][0] = dTegkeyPos[0][5] - 77.369;
				m_AlignPointValue[1][0] = dTegkeyPos[1][5] + 0.9546;
				//RT
				m_AlignPointValue[0][2] = dTegkeyPos[0][12] + 86.8246;
				m_AlignPointValue[1][2] = dTegkeyPos[1][12] - 1.447;
				//RB
				m_AlignPointValue[0][1] = dTegkeyPos[0][17] - 77.369;
				m_AlignPointValue[1][1] = dTegkeyPos[1][17] - 1.447;

				for (int i = 0; i < 4; i++)
				{
					m_AlignPointValue[0][i] *= CModelData::m_AtMaterialPara.Info.dTensionRatioX;
					m_AlignPointValue[1][i] *= CModelData::m_AtMaterialPara.Info.dTensionRatioY; //KJT 20210415

					m_AlignPointValue[0][i] *= STICK_FLIP_XY;
					m_AlignPointValue[1][i] *= STICK_FLIP_XY;
				}

				//g_CommLight_8ch.SetLight_Review_Coaxial(CModelData::m_AlignPara.Info.nSwAlignCoAxial);
				//Sleep(30);
				//g_CommLight_12ch.SetLight_Review_Ring(CModelData::m_AlignPara.Info.nSwAlignRing);
				//Sleep(30);
				//g_CommMLCLedLight.BackLightOn(nBackLightVal);
				//Sleep(500);

				if (CModelData::m_AlignPara.Info.nSwAlignLightType == eLight_Back)
				{
					SharedInfo::BackLightOn(CModelData::m_AlignPara.Info.nSwAlignBacklight);
					Sleep(30);
				}
				else
				{
					g_CommReview_Light.SetLight_Review(CModelData::m_AlignPara.Info.nSwAlignRing, CModelData::m_AlignPara.Info.nSwAlignCoAxial);
					Sleep(30);
				}
#endif
			}
			else if (m_eSwAlignType == eSwAlign_Glass) //KJT 20210419
			{
				m_AlignPointValue[0][0] = CModelData::m_GlassPara.Info.dGlassAlignMark_LB_X;
				m_AlignPointValue[1][0] = CModelData::m_GlassPara.Info.dGlassAlignMark_LB_Y;
				//LT
				m_AlignPointValue[0][1] = CModelData::m_GlassPara.Info.dGlassAlignMark_LT_X;
				m_AlignPointValue[1][1] = CModelData::m_GlassPara.Info.dGlassAlignMark_LT_Y;
				//RT
				m_AlignPointValue[0][2] = CModelData::m_GlassPara.Info.dGlassAlignMark_RT_X;
				m_AlignPointValue[1][2] = CModelData::m_GlassPara.Info.dGlassAlignMark_RT_Y;
				//RB
				m_AlignPointValue[0][3] = CModelData::m_GlassPara.Info.dGlassAlignMark_RB_X;
				m_AlignPointValue[1][3] = CModelData::m_GlassPara.Info.dGlassAlignMark_RB_Y;

				if (CModelData::m_AlignPara.Info.nVerticalMainAlignLightType == eLight_Back) //KJT 20210820
				{
					SharedInfo::BackLightOn(CModelData::m_AlignPara.Info.nVerticalMainAlignBackLight);
					Sleep(30);
				}
				else
				{
					g_CommReview_Light.SetLight_Review(CModelData::m_AlignPara.Info.nVerticalMainAlignRing, CModelData::m_AlignPara.Info.nVerticalMainAlignCoAxial);
					Sleep(30);
				}
			}

			Devs::m_MappingProc.ReleaseSWMapping(eMAPPING_ID_10X); //!! KJT 20200913
			Devs::m_MappingProc.ReleaseXYTAlignData(eMAPPING_ID_10X); //!! KJT 20200913
			/////////////
			SharedInfo::nGantryZ1View = eViewReview10X;

			m_bUpdateSWAlignData = FALSE;
			m_bVerify = FALSE;
			m_bVerifyFirst = TRUE;

			m_nAlignPoint = 0;

			memset(m_AlignVisionResultValue, 0x0, sizeof(m_AlignVisionResultValue));
			memset(SharedInfo::dSwAlignVisionResultValue, 0x0, sizeof(SharedInfo::dSwAlignVisionResultValue));

			SharedInfo::nSwAlignCurCount = 0;
			m_nGrabRetryCnt = 0;

			SetStep(_eSW_ALIGN_FLOW_INTERLOCK, _T("_eSW_ALIGN_FLOW_INTERLOCK"));
			break;
		}

		case _eSW_ALIGN_FLOW_INTERLOCK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(_eSW_ALIGN_FLOW_ERROR, _T("_eSW_ALIGN_FLOW_ERROR"));
			}
			else
			{
				if ((SharedInfo::MachineState.bAutoRunFlag == TRUE &&
					(SharedInfo::nPrevFlowID == eMAIN_ALIGN_FLOW || SharedInfo::nPrevFlowID == eTEGKEY_ALIGN_FLOW)) || //SharedInfo::nPrevFlowID == eMEASURE_HALF_EDGE_FLOW)) ||
					SharedInfo::nPrevFlowID == eGLASS_MAPPING_FLOW) //KJT 20210419
					SetStep(_eSW_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST, _T("_eSW_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST"));
				else
					SetStep(_eSW_ALIGN_FLOW_UNLOADER_READY, _T("_eSW_ALIGN_FLOW_UNLOADER_READY"));
			}
			break;

#pragma region //Unloader Ready
		case _eSW_ALIGN_FLOW_UNLOADER_READY:
			Devs::m_Ready_UnloaderFlow.Start();

			SetStep(_eSW_ALIGN_FLOW_UNLOADER_READY_CHECK, _T("_eSW_ALIGN_FLOW_UNLOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSW_ALIGN_FLOW_UNLOADER_READY_CHECK:
			if (Devs::m_Ready_UnloaderFlow.IsFlowDone())
			{
				SetStep(_eSW_ALIGN_FLOW_GANTRY_ZX_READY, _T("_eSW_ALIGN_FLOW_GANTRY_ZX_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSW_ALIGN_FLOW_UNLOADER_READY_CHECK : Time Out"), eSW_FLOW + 1);
				SetStep(_eSW_ALIGN_FLOW_ERROR, _T("_eSW_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSW_ALIGN_FLOW_UNLOADER_READY_CHECK, _T("_eSW_ALIGN_FLOW_UNLOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Gantry Z, X Ready
		case _eSW_ALIGN_FLOW_GANTRY_ZX_READY:
			Devs::m_Ready_GantryZX_Flow.Start();

			SetStep(_eSW_ALIGN_FLOW_GANTRY_ZX_READY_CHECK, _T("_eSW_ALIGN_FLOW_GANTRY_ZX_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSW_ALIGN_FLOW_GANTRY_ZX_READY_CHECK:
			if (Devs::m_Ready_GantryZX_Flow.IsFlowDone())
			{
				SetStep(_eSW_ALIGN_FLOW_LOADER_READY, _T("_eSW_ALIGN_FLOW_LOADER_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSW_ALIGN_FLOW_GANTRY_ZX_READY_CHECK : Time Out"), eSW_FLOW + 3);
				SetStep(_eSW_ALIGN_FLOW_ERROR, _T("_eSW_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSW_ALIGN_FLOW_GANTRY_ZX_READY_CHECK, _T("_eSW_ALIGN_FLOW_GANTRY_ZX_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Loader Ready
		case _eSW_ALIGN_FLOW_LOADER_READY:
			Devs::m_Ready_LoaderFlow.Start();

			SetStep(_eSW_ALIGN_FLOW_LOADER_READY_CHECK, _T("_eSW_ALIGN_FLOW_LOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSW_ALIGN_FLOW_LOADER_READY_CHECK:
			if (Devs::m_Ready_LoaderFlow.IsFlowDone())
			{
				SetStep(_eSW_ALIGN_FLOW_PAPER_UNLOADER_ZXY_READY, _T("_eSW_ALIGN_FLOW_PAPER_UNLOADER_ZXY_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSW_ALIGN_FLOW_LOADER_READY_CHECK : Time Out"), eSW_FLOW + 2);
				SetStep(_eSW_ALIGN_FLOW_ERROR, _T("_eSW_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSW_ALIGN_FLOW_LOADER_READY_CHECK, _T("_eSW_ALIGN_FLOW_LOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //PaperUnloader Ready
		case _eSW_ALIGN_FLOW_PAPER_UNLOADER_ZXY_READY:
			Devs::m_Ready_PaperUnloaderFlow.Start();

			SetStep(_eSW_ALIGN_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK, _T("_eSW_ALIGN_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSW_ALIGN_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK:
			if (Devs::m_Ready_PaperUnloaderFlow.IsFlowDone())
			{
				m_nAlignPoint = 0;
				SetStep(_eSW_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST, _T("_eSW_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSW_ALIGN_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK : Time Out"), eBOX_ALIGN_FLOW + 1);
				SetStep(_eSW_ALIGN_FLOW_ERROR, _T("_eSW_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSW_ALIGN_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK, _T("_eSW_ALIGN_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Gantry XYZ First Pos Move
		case _eSW_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST:
			m_dTargetPosX = dPosX = GetAlignPos_X(m_nAlignPoint);
			m_dTargetPosY = dPosY = GetAlignPos_Y(m_nAlignPoint);

#if 1 //KJT 20210421
			if (m_eSwAlignType != eSwAlign_Glass)
			{
				if (m_nAlignPoint == 0 || m_nAlignPoint == 1) //m_nAlignPoint 0:LB, 1:LT
				{
					dPosX += SharedInfo::dMain2PAlignResultShiftX[1];

					Str.Format(_T("m_dTargetPosX + Main2PAlignResultShiftX. %.5f + %.5f = %.5f"), m_dTargetPosX, SharedInfo::dMain2PAlignResultShiftX[1], dPosX);
					Total_Msg(Str);
				}
				else //if (m_nAlignPoint == 2 || m_nAlignPoint == 3) //m_nAlignPoint 2:RT, 3:RB
				{
					dPosX += SharedInfo::dMain2PAlignResultShiftX[0];

					Str.Format(_T("m_dTargetPosX + Main2PAlignResultShiftX. %.5f + %.5f = %.5f"), m_dTargetPosX, SharedInfo::dMain2PAlignResultShiftX[0], dPosX);
					Total_Msg(Str);
				}
				m_dTargetPosX = dPosX;
			}
#endif

#ifndef SIM_MODE
			if (CModelData::m_InspectionPara.Info.bMappingDataUse && m_eSwAlignType != eSwAlign_Glass) //KJT 20210419
			{
				Devs::m_MappingProc.GetGlassMapping_CalibPosXY(eMAPPING_ID_10X, &m_dTargetPosX, &m_dTargetPosY);
				Str.Format(_T("Mapping Data X:%10.5f, Y:%10.5f => X:%10.5f, Y:%10.5f"), dPosX, dPosY, m_dTargetPosX, m_dTargetPosY);
				Total_Msg(Str);
			}
#endif
			if (m_eSwAlignType != eSwAlign_Glass)
			{
				Devs::m_GantryMotion.Move_Gantry_X_Pos(m_dTargetPosX, TRUE);
				Sleep(20); //!!
				Devs::m_GantryMotion.Move_Gantry_Y_Pos(m_dTargetPosY);
				Sleep(20); //!!
			}
			else
			{
				if (CModelData::m_AlignPara.Info.nSwAlignLightType == eLight_Back)
				{
					Devs::m_GantryMotion.Move_Gantry_X_Pos(m_dTargetPosX, TRUE);
					Sleep(20); //!!
					Devs::m_GantryMotion.Move_Gantry_Y_Pos(m_dTargetPosY);
					Sleep(20); //!!
				}
				else
				{
					Devs::m_GantryMotion.Move_Gantry_X_Pos(m_dTargetPosX, FALSE);
					Sleep(20); //!!
					Devs::m_GantryMotion.Move_Gantry_Y_Pos(m_dTargetPosY);
					Sleep(20); //!!
				}
			}

			SetStep(_eSW_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK, _T("_eSW_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSW_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Pos(m_dTargetPosX) && Devs::m_GantryMotion.Is_Gantry_Y_Pos(m_dTargetPosY))
			{
				if (m_eSwAlignType != eSwAlign_Glass)
				{
					if (CModelData::m_AlignPara.Info.nSwAlignLightType == eLight_Back)
					{
						if (Devs::m_InspectionStageMotion.Is_BackLight_X_Pos(m_dTargetPosX))
							//SetStep(_eSW_ALIGN_FLOW_GANTRY_Z1_INSPECTION_POS_1ST, _T("_eSW_ALIGN_FLOW_GANTRY_Z1_INSPECTION_POS_1ST"));
							SetStep(_eSW_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_1ST, _T("_eSW_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_1ST"));
						else
							SetCheckStep(_eSW_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK, _T("_eSW_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK"));
					}
					else
					{
						//SetStep(_eSW_ALIGN_FLOW_GANTRY_Z1_INSPECTION_POS_1ST, _T("_eSW_ALIGN_FLOW_GANTRY_Z1_INSPECTION_POS_1ST"));
						SetStep(_eSW_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_1ST, _T("_eSW_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_1ST"));
					}
				}
				else
				{
					if (CModelData::m_AlignPara.Info.nSwAlignLightType == eLight_Back)
					{
						if (Devs::m_InspectionStageMotion.Is_BackLight_X_Pos(m_dTargetPosX))
						{
							if (Devs::m_InspectionStageMotion.Is_BackLight_X_Pos(m_dTargetPosX))
								//SetStep(_eSW_ALIGN_FLOW_GANTRY_Z1_INSPECTION_POS_1ST, _T("_eSW_ALIGN_FLOW_GANTRY_Z1_INSPECTION_POS_1ST"));
								SetStep(_eSW_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_1ST, _T("_eSW_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_1ST"));
							else
								SetCheckStep(_eSW_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK, _T("_eSW_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK"));
						}
					}
					else
					{
						//SetStep(_eSW_ALIGN_FLOW_GANTRY_Z1_INSPECTION_POS_1ST, _T("_eSW_ALIGN_FLOW_GANTRY_Z1_INSPECTION_POS_1ST"));
						SetStep(_eSW_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_1ST, _T("_eSW_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_1ST"));
					}
				}
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSW_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK : Time Out"), eSW_FLOW + 4);
				SetStep(_eSW_ALIGN_FLOW_ERROR, _T("_eSW_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSW_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK, _T("_eSW_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK"));
			}
			break;

		case _eSW_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_1ST:
			Devs::m_GantryMotion.Move_GantryZ1_InspectionReview_Pos();
			Sleep(20); //!!

			SetStep(_eSW_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_1ST_CHECK, _T("_eSW_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_1ST_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSW_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_1ST_CHECK:
			if (Devs::m_GantryMotion.Is_GantryZ1_InspectionReview_Pos())
			{
				Sleep(500); //!!
				SetStep(_eSW_ALIGN_FLOW_AUTOFOCUS_CHECK, _T("_eSW_ALIGN_FLOW_AUTOFOCUS_CHECK"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSW_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_1ST_CHECK : Time Out"), eSW_FLOW + 5);
				SetStep(_eSW_ALIGN_FLOW_ERROR, _T("_eSW_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSW_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_1ST_CHECK, _T("_eSW_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_1ST_CHECK"));
			}
			break;
#pragma endregion

#if 0 //Not Use
		case _eSW_ALIGN_FLOW_GANTRY_Z1_INSPECTION_POS_2ND:
			Devs::m_GantryMotion.Move_GantryZ1_InspectionReview_Pos();
			Sleep(20); //!!

			SetStep(_eSW_ALIGN_FLOW_GANTRY_Z1_INSPECTION_POS_2ND_CHECK, _T("_eSW_ALIGN_FLOW_GANTRY_Z1_INSPECTION_POS_2ND_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSW_ALIGN_FLOW_GANTRY_Z1_INSPECTION_POS_2ND_CHECK:
			if (Devs::m_GantryMotion.Is_GantryZ1_InspectionReview_Pos())
			{
				SetStep(_eSW_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND, _T("_eSW_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eSW_ALIGN_FLOW_ERROR, _T("_eSW_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSW_ALIGN_FLOW_GANTRY_Z1_INSPECTION_POS_2ND_CHECK, _T("_eSW_ALIGN_FLOW_GANTRY_Z1_INSPECTION_POS_2ND_CHECK"));
			}
			break;
#endif

		case _eSW_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND:
#if 0
			if (m_bVerify == FALSE)
			{
				m_dTargetPosX = dPosX = GetAlignPos_X(m_nAlignPoint);
				m_dTargetPosY = dPosY = GetAlignPos_Y(m_nAlignPoint);
			}
			else
			{
				if (m_bVerifyFirst == TRUE)
				{
					m_dTargetPosX = dPosX = GetAlignPos_X(m_nAlignPoint);
					m_dTargetPosY = dPosY = GetAlignPos_Y(m_nAlignPoint);
				}
				else
				{
					m_dTargetPosX = dPosX = m_SwAlignPointValue[0][m_nAlignPoint];
					m_dTargetPosY = dPosY = m_SwAlignPointValue[1][m_nAlignPoint];
				}
			}
#else //KJT 20210412
			m_dTargetPosX = dPosX = GetAlignPos_X(m_nAlignPoint);
			m_dTargetPosY = dPosY = GetAlignPos_Y(m_nAlignPoint);
#endif

#ifndef SIM_MODE
			//KJT 20210304
			if (m_bUpdateSWAlignData)
			{
				dPosX = m_dTargetPosX;
				dPosY = m_dTargetPosY;
				if (CModelData::m_InspectionPara.Info.bAlignDataUse) //KJT 20210304
				{
					if (m_eSwAlignType == eSwAlign_Glass || CModelData::m_InspectionPara.Info.nAlignDataUseMode == eALIGN_DATA_USE_XYT_ALIGN_DATA) //KJT 20210421
					{
						Devs::m_MappingProc.GetXYTAlign_CalibPosXY(eMAPPING_ID_10X, &m_dTargetPosX, &m_dTargetPosY);

						m_SwAlignPointValue[0][m_nAlignPoint] = m_dTargetPosX;
						m_SwAlignPointValue[1][m_nAlignPoint] = m_dTargetPosY;

						Str.Format(_T("XYTMapping Data X:%10.5f, Y:%10.5f => X:%10.5f, Y:%10.5f"), dPosX, dPosY, m_dTargetPosX, m_dTargetPosY);
						Total_Msg(Str);
					}
					else if (CModelData::m_InspectionPara.Info.nAlignDataUseMode == eALIGN_DATA_USE_SW_MAPPING_DATA)
					{
						Devs::m_MappingProc.GetSWMapping_CalibPosXY(eMAPPING_ID_10X, &m_dTargetPosX, &m_dTargetPosY);

						m_SwAlignPointValue[0][m_nAlignPoint] = m_dTargetPosX;
						m_SwAlignPointValue[1][m_nAlignPoint] = m_dTargetPosY;

						Str.Format(_T("SWMapping Data X:%10.5f, Y:%10.5f => X:%10.5f, Y:%10.5f"), dPosX, dPosY, m_dTargetPosX, m_dTargetPosY);
						Total_Msg(Str);
					}
				}
			}
			else
			{
#if 1 //KJT 20210421
				if (m_eSwAlignType != eSwAlign_Glass)
				{
					if (m_nAlignPoint == 0 || m_nAlignPoint == 1) //m_nAlignPoint 0:LB, 1:LT
					{
						dPosX += SharedInfo::dMain2PAlignResultShiftX[1];

						Str.Format(_T("m_dTargetPosX + Main2PAlignResultShiftX. %.5f + %.5f = %.5f"), m_dTargetPosX, SharedInfo::dMain2PAlignResultShiftX[1], dPosX);
						Total_Msg(Str);
					}
					else //if (m_nAlignPoint == 2 || m_nAlignPoint == 3) //m_nAlignPoint 2:RT, 3:RB
					{
						dPosX += SharedInfo::dMain2PAlignResultShiftX[0];

						Str.Format(_T("m_dTargetPosX + Main2PAlignResultShiftX. %.5f + %.5f = %.5f"), m_dTargetPosX, SharedInfo::dMain2PAlignResultShiftX[0], dPosX);
						Total_Msg(Str);
					}
					m_dTargetPosX = dPosX;
				}
#endif
			}

			dPosX = m_dTargetPosX;
			dPosY = m_dTargetPosY;
			if (CModelData::m_InspectionPara.Info.bMappingDataUse && m_eSwAlignType != eSwAlign_Glass)
			{
				Devs::m_MappingProc.GetGlassMapping_CalibPosXY(eMAPPING_ID_10X, &m_dTargetPosX, &m_dTargetPosY);
				Str.Format(_T("Mapping Data X:%10.5f, Y:%10.5f => X:%10.5f, Y:%10.5f"), dPosX, dPosY, m_dTargetPosX, m_dTargetPosY);
				Total_Msg(Str);
			}
#endif
			if (m_eSwAlignType != eSwAlign_Glass)
			{
				Devs::m_GantryMotion.Move_Gantry_X_Pos(m_dTargetPosX, TRUE);
				Sleep(20); //!!
				Devs::m_GantryMotion.Move_Gantry_Y_Pos(m_dTargetPosY);
				Sleep(20); //!!
			}
			else
			{
				Devs::m_GantryMotion.Move_Gantry_X_Pos(m_dTargetPosX, FALSE);
				Sleep(20); //!!
				Devs::m_GantryMotion.Move_Gantry_Y_Pos(m_dTargetPosY);
				Sleep(20); //!!
			}

			SetStep(_eSW_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK, _T("_eSW_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSW_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Pos(m_dTargetPosX) && Devs::m_GantryMotion.Is_Gantry_Y_Pos(m_dTargetPosY))
			{
				if (m_eSwAlignType != eSwAlign_Glass)
				{
					if (CModelData::m_AlignPara.Info.nSwAlignLightType == eLight_Back)
					{
						if (Devs::m_InspectionStageMotion.Is_BackLight_X_Pos(m_dTargetPosX))
						{
							Sleep(100); //!!
							SetStep(_eSW_ALIGN_FLOW_AUTOFOCUS_CHECK, _T("_eSW_ALIGN_FLOW_AUTOFOCUS_CHECK"));
						}
						else
							SetCheckStep(_eSW_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK, _T("_eSW_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK"));
					}
					else
					{
						Sleep(100); //!!
						SetStep(_eSW_ALIGN_FLOW_AUTOFOCUS_CHECK, _T("_eSW_ALIGN_FLOW_AUTOFOCUS_CHECK"));
					}
				}
				else
				{
					if (CModelData::m_AlignPara.Info.nSwAlignLightType == eLight_Back)
					{
						if (Devs::m_InspectionStageMotion.Is_BackLight_X_Pos(m_dTargetPosX))
						{
							Sleep(100); //!!
							SetStep(_eSW_ALIGN_FLOW_AUTOFOCUS_CHECK, _T("_eSW_ALIGN_FLOW_AUTOFOCUS_CHECK"));
						}
						else
							SetCheckStep(_eSW_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK, _T("_eSW_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK"));
					}
					else
					{
						Sleep(100); //!!
						SetStep(_eSW_ALIGN_FLOW_AUTOFOCUS_CHECK, _T("_eSW_ALIGN_FLOW_AUTOFOCUS_CHECK"));
					}
				}
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSW_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK : Time Out"), eSW_FLOW + 6);
				SetStep(_eSW_ALIGN_FLOW_ERROR, _T("_eSW_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSW_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK, _T("_eSW_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK"));
			}
			break;

		case _eSW_ALIGN_FLOW_AUTOFOCUS_CHECK:
			if (CModelData::m_AlignPara.Info.nSwAlignFocusType == eFocusType_Laser || CModelData::m_AlignPara.Info.nSwAlignFocusType == eFocusType_Both)
				SetStep(_eSW_ALIGN_FLOW_LASER_FOCUS_START, _T("_eSW_ALIGN_FLOW_LASER_FOCUS_START"));
			else if (CModelData::m_AlignPara.Info.nSwAlignFocusType == eFocusType_Image)
				SetStep(_eSW_ALIGN_FLOW_IMAGE_FOCUS_START, _T("_eSW_ALIGN_FLOW_IMAGE_FOCUS_START"));
			else
				SetStep(_eSW_ALIGN_FLOW_GRAB_START, _T("_eSW_ALIGN_FLOW_GRAB_START"));
			break;

		case _eSW_ALIGN_FLOW_LASER_FOCUS_START:
			if (m_eSwAlignType == eSwAlign_Glass) //KJT 20210820
				Devs::m_GantryMotion.LaserFocusMove(1);
			else
				Devs::m_GantryMotion.LaserFocusMove(0);

			SetStep(_eSW_ALIGN_FLOW_LASER_FOCUS_CHECK, _T("_eSW_ALIGN_FLOW_LASER_FOCUS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSW_ALIGN_FLOW_LASER_FOCUS_CHECK:
			if (Devs::m_GantryMotion.LaserFocusMoveCheck())
			{
				Sleep(500); //!!	//KJT 20210321

				if (CModelData::m_AlignPara.Info.nSwAlignFocusType == eFocusType_Both)
					SetStep(_eSW_ALIGN_FLOW_IMAGE_FOCUS_START, _T("_eSW_ALIGN_FLOW_IMAGE_FOCUS_START"));
				else
					SetStep(_eSW_ALIGN_FLOW_GRAB_START, _T("_eSW_ALIGN_FLOW_GRAB_START"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSW_ALIGN_FLOW_LASER_FOCUS_CHECK : Time Out"), eSW_FLOW + 7);
				SetStep(_eSW_ALIGN_FLOW_ERROR, _T("_eSW_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSW_ALIGN_FLOW_LASER_FOCUS_CHECK, _T("_eSW_ALIGN_FLOW_LASER_FOCUS_CHECK"));
			}
			break;

		case _eSW_ALIGN_FLOW_IMAGE_FOCUS_START:
#ifndef SIM_MODE
			g_pReview10x->m_bAfEnd = FALSE;
			g_pReview10x->AutofoucsRun();
#endif

			SetStep(_eSW_ALIGN_FLOW_IMAGE_FOCUS_CHECK, _T("_eSW_ALIGN_FLOW_IMAGE_FOCUS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSW_ALIGN_FLOW_IMAGE_FOCUS_CHECK:
#ifndef SIM_MODE
			if (g_pReview10x->m_bAfEnd == TRUE)
			{
				Sleep(IMAGE_FOCUS_DELAY);
				SetStep(_eSW_ALIGN_FLOW_GRAB_START, _T("_eSW_ALIGN_FLOW_GRAB_START"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSW_ALIGN_FLOW_IMAGE_FOCUS_CHECK : Time Out"), eSW_FLOW + 8);
				SetStep(_eSW_ALIGN_FLOW_ERROR, _T("_eSW_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSW_ALIGN_FLOW_IMAGE_FOCUS_CHECK, _T("_eSW_ALIGN_FLOW_IMAGE_FOCUS_CHECK"));
			}
#else
			Sleep(IMAGE_FOCUS_DELAY);
			SetStep(_eSW_ALIGN_FLOW_GRAB_START, _T("_eSW_ALIGN_FLOW_GRAB_START"));
#endif
			break;

		case _eSW_ALIGN_FLOW_GRAB_START:
			SharedInfo::bMainEdgeAlignGrabDone = FALSE;
			if (m_eSwAlignType == eSwAlign_Tegkey)
				bResult = Devs::m_GantryMotion.FindBlob_Tegkey_Review10X(&m_AlignVisionResultValue[0][m_nAlignPoint], &m_AlignVisionResultValue[1][m_nAlignPoint]);
			else if (m_eSwAlignType == eSwAlign_Glass)
			{
#ifndef SIM_MODE
				stModCirclePara ModCirclePara;
				ModCirclePara.dRadius = CModelData::m_GlassPara.Info.dGlassAlignMarkSizeX / 2.0;
				m_CameraInfo.nBin = CModelData::m_AlignPara.Info.nVerticalMainAlignThreshold;
				m_ModResult = Devs::m_Camera10X->FindModCircleFind(ModCirclePara);
				Sleep(200);
				m_ModelFindData = Devs::m_Camera10X->GetModelFindData();
				bResult = m_ModResult.bResult;
				if (m_ModResult.bResult == FALSE) //KJT 20210404
				{
					m_nGrabRetryCnt++;
					if (m_nGrabRetryCnt > 3)
					{
						SharedInfo::SetAlarm(_T("_eSW_ALIGN_FLOW_GRAB_START : Retry Count"), eSW_FLOW + 9);
						SetStep(_eSW_ALIGN_FLOW_ERROR, _T("_eSW_ALIGN_FLOW_ERROR"));
						break;
					}

					if (CModelData::m_AlignPara.Info.nSwAlignFocusType == eFocusType_Laser || CModelData::m_AlignPara.Info.nSwAlignFocusType == eFocusType_Both)
						SetStep(_eSW_ALIGN_FLOW_LASER_FOCUS_START, _T("_eSW_ALIGN_FLOW_LASER_FOCUS_START"));
					else if (CModelData::m_AlignPara.Info.nSwAlignFocusType == eFocusType_Image)
						SetStep(_eSW_ALIGN_FLOW_IMAGE_FOCUS_START, _T("_eSW_ALIGN_FLOW_IMAGE_FOCUS_START"));
					else
						SetStep(_eSW_ALIGN_FLOW_GRAB_START, _T("_eSW_ALIGN_FLOW_GRAB_START"));

					break;
				}
				else
				{
					m_AlignVisionResultValue[0][m_nAlignPoint] = m_ModelFindData.dPosX;
					m_AlignVisionResultValue[1][m_nAlignPoint] = m_ModelFindData.dPosY;
				}
#else
				m_AlignVisionResultValue[0][m_nAlignPoint] = 0.0;
				m_AlignVisionResultValue[1][m_nAlignPoint] = 0.0;
#endif
			}
			else //if (m_eSwAlignType == eSwAlign_EdgeSlot || m_eSwAlignType == eSwAlign_EdgeCell)
			{
				bResult = Devs::m_GantryMotion.FindBlob_SwAlign_Review10X(&m_AlignVisionResultValue[0][m_nAlignPoint], &m_AlignVisionResultValue[1][m_nAlignPoint]);//Temp

				if (bResult == FALSE)
				{
					SharedInfo::SetAlarm(_T("_eSW_ALIGN_FLOW_GRAB_START : Find Hole"), eSW_FLOW + 10);
					SetStep(_eSW_ALIGN_FLOW_ERROR, _T("_eSW_ALIGN_FLOW_ERROR"));
					break;
				}
			}

			SharedInfo::dSwAlignVisionResultValue[0][m_nAlignPoint] = m_AlignVisionResultValue[0][m_nAlignPoint];
			SharedInfo::dSwAlignVisionResultValue[1][m_nAlignPoint] = m_AlignVisionResultValue[1][m_nAlignPoint];

			Str.Format(_T("AlignCnt:%d Diff X:%.5f, Y:%.5f"), m_nAlignPoint, m_AlignVisionResultValue[0][m_nAlignPoint], m_AlignVisionResultValue[1][m_nAlignPoint]);
			Total_Msg(Str);

			SetStep(_eSW_ALIGN_FLOW_GRAB_DONE_CHECK, _T("_eSW_ALIGN_FLOW_GRAB_DONE_CHECK"));
			break;

		case _eSW_ALIGN_FLOW_GRAB_DONE_CHECK:
			SharedInfo::bMainEdgeAlignGrabDone = TRUE;
			m_nGrabRetryCnt = 0;
			if (m_nAlignPoint == 3)
			{
				m_nAlignPoint = 0;

				SharedInfo::nSwAlignCurCount++;
				Str.Format(_T("AlignCurCount:%d Diff X[0]:%.5f, Y[0]:%.5f, X[1]:%.5f, Y[1]:%.5f, X[2]:%.5f, Y[2]:%.5f, X[3]:%.5f, Y[3]:%.5f"),
					SharedInfo::nSwAlignCurCount,
					m_AlignVisionResultValue[0][0], m_AlignVisionResultValue[1][0], m_AlignVisionResultValue[0][1], m_AlignVisionResultValue[1][1],
					m_AlignVisionResultValue[0][2], m_AlignVisionResultValue[1][2], m_AlignVisionResultValue[0][3], m_AlignVisionResultValue[1][3]);
				Total_Msg(Str);

				Sleep(100);
#if 0
				Devs::m_InspectionStageMotion.GetUVWPos(m_AlignPointValue[0], m_AlignPointValue[1], m_AlignVisionResultValue[0], m_AlignVisionResultValue[1], &m_dDiffPos[0], &m_dDiffPos[1], &m_dDiffPos[2], FALSE);
#else //KJT 20210724
				////LB->LT->RT->RB
				dCmdPointXY[0][0] = m_AlignPointValue[0][0];
				dCmdPointXY[0][1] = m_AlignPointValue[1][0];
				dCmdPointXY[1][0] = m_AlignPointValue[0][1];
				dCmdPointXY[1][1] = m_AlignPointValue[1][1];
				dCmdPointXY[2][0] = m_AlignPointValue[0][2];
				dCmdPointXY[2][1] = m_AlignPointValue[1][2];
				dCmdPointXY[3][0] = m_AlignPointValue[0][3];
				dCmdPointXY[3][1] = m_AlignPointValue[1][3];

				dActPointXY[0][0] = m_AlignPointValue[0][0] + m_AlignVisionResultValue[0][0];
				dActPointXY[0][1] = m_AlignPointValue[1][0] + m_AlignVisionResultValue[1][0];
				dActPointXY[1][0] = m_AlignPointValue[0][1] + m_AlignVisionResultValue[0][1];
				dActPointXY[1][1] = m_AlignPointValue[1][1] + m_AlignVisionResultValue[1][1];
				dActPointXY[2][0] = m_AlignPointValue[0][2] + m_AlignVisionResultValue[0][2];
				dActPointXY[2][1] = m_AlignPointValue[1][2] + m_AlignVisionResultValue[1][2];
				dActPointXY[3][0] = m_AlignPointValue[0][3] + m_AlignVisionResultValue[0][3];
				dActPointXY[3][1] = m_AlignPointValue[1][3] + m_AlignVisionResultValue[1][3];

				SharedInfo::GetDiffXYT(dCmdPointXY, dActPointXY, &m_dDiffPos[0], &m_dDiffPos[1], &m_dDiffPos[2]);
#endif				

				Str.Format(_T("Uvw Diff Pos X:%.5f, Y:%.5f, T:%.5f"), m_dDiffPos[0], m_dDiffPos[1], m_dDiffPos[2]);
				Total_Msg(Str);

				//////////////////////////////////////////////////////////////////////////////////////
				//sunghaklee(2021.04.23) :Append
				//if (SharedInfo::nPrevFlowID == eGLASS_MAPPING_FLOW)
				//{
				//	SharedInfo::UpdateSwAlignData(m_AlignPointValue, m_AlignVisionResultValue);
				//	m_bUpdateSWAlignData = TRUE;
				//	SetStep(_eSW_ALIGN_FLOW_DONE, _T("_eSW_ALIGN_FLOW_DONE"));
				//	break;
				//}

				//KJT 20210317
				if (m_bVerify && m_bVerifyFirst)
					m_bVerifyFirst = FALSE;
#if 0
				if (fabs(m_AlignVisionResultValue[0][1] + m_AlignVisionResultValue[0][2]) < fabs(m_AlignVisionResultValue[0][3] + m_AlignVisionResultValue[0][0]))
					dResultDiffX = fabs(m_AlignVisionResultValue[0][3] + m_AlignVisionResultValue[0][0]);
				else
					dResultDiffX = fabs(m_AlignVisionResultValue[0][1] + m_AlignVisionResultValue[0][2]);

				if (fabs(m_AlignVisionResultValue[1][0] + m_AlignVisionResultValue[1][1]) < fabs(m_AlignVisionResultValue[1][2] + m_AlignVisionResultValue[1][3]))
					dResultDiffY = fabs(m_AlignVisionResultValue[1][2] + m_AlignVisionResultValue[1][3]);
				else
					dResultDiffY = fabs(m_AlignVisionResultValue[1][0] + m_AlignVisionResultValue[1][1]);

				Str.Format(_T("Diff_X:%.5f, Diff_Y:%.5f"), dResultDiffX, dResultDiffY);
				Total_Msg(Str);

				if (m_bVerify && m_bVerifyFirst)
					m_bVerifyFirst = FALSE;

				if (fabs(dResultDiffX) < CModelData::m_AlignPara.Info.dSwAlignTargetX && //Temp
					fabs(dResultDiffY) < CModelData::m_AlignPara.Info.dSwAlignTargetY &&
					fabs(m_AlignVisionResultValue[0][0]) < CModelData::m_AlignPara.Info.dSwAlignTargetX &&
					fabs(m_AlignVisionResultValue[1][0]) < CModelData::m_AlignPara.Info.dSwAlignTargetY &&
					fabs(m_AlignVisionResultValue[0][1]) < CModelData::m_AlignPara.Info.dSwAlignTargetX &&
					fabs(m_AlignVisionResultValue[1][1]) < CModelData::m_AlignPara.Info.dSwAlignTargetY &&
					fabs(m_AlignVisionResultValue[0][2]) < CModelData::m_AlignPara.Info.dSwAlignTargetX &&
					fabs(m_AlignVisionResultValue[1][2]) < CModelData::m_AlignPara.Info.dSwAlignTargetY &&
					fabs(m_AlignVisionResultValue[0][3]) < CModelData::m_AlignPara.Info.dSwAlignTargetX &&
					fabs(m_AlignVisionResultValue[1][3]) < CModelData::m_AlignPara.Info.dSwAlignTargetY &&
					fabs(m_dDiffPos[2]) < 0.001)
#else //KJT 20210317
				dAverageDiffX = (m_AlignVisionResultValue[0][0] + m_AlignVisionResultValue[0][1] + m_AlignVisionResultValue[0][2] + m_AlignVisionResultValue[0][3]) / 4;
				dAverageDiffY = (m_AlignVisionResultValue[1][0] + m_AlignVisionResultValue[1][1] + m_AlignVisionResultValue[1][2] + m_AlignVisionResultValue[1][3]) / 4;

				Str.Format(_T("AlignCurCount:%d, Diff_X:%.5f, Diff_Y:%.5f"), SharedInfo::nSwAlignCurCount, dAverageDiffX, dAverageDiffY);
				Total_Msg(Str);

				if (fabs(dAverageDiffX) < (float)CModelData::m_AlignPara.Info.dSwAlignTargetX && //Temp
					fabs(dAverageDiffY) < (float)CModelData::m_AlignPara.Info.dSwAlignTargetY &&
					(fabs(m_dDiffPos[2]) < 0.001 || (360 - fabs(m_dDiffPos[2])) < 0.001)) //KJT 20210319
#endif
				{
					if (CModelData::m_InspectionPara.Info.bSwAlignVerifyUse && m_bVerify == FALSE)
					{
						m_bVerify = TRUE;

						SharedInfo::UpdateSwAlignData(m_AlignPointValue, m_AlignVisionResultValue);
						m_bUpdateSWAlignData = TRUE;

						Str.Format(_T("AlignCurCount:%d, UpdateSwAlignData (SpecIn)"), SharedInfo::nSwAlignCurCount);
						Total_Msg(Str);
						SetStep(_eSW_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND, _T("_eSW_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND"));
						break;
					}
					else
					{
						Str.Format(_T("AlignCurCount:%d, UpdateSwAlignData (Verify, SpecIn)"), SharedInfo::nSwAlignCurCount);
						Total_Msg(Str);

						SharedInfo::LightAllOff();

						if ((SharedInfo::MachineState.bAutoRunFlag == TRUE && CModelData::m_InspectionPara.Info.bPPAUse) ||
							SharedInfo::nPrevFlowID == eGLASS_MAPPING_FLOW) //KJT 20210419
							SetStep(_eSW_ALIGN_FLOW_DONE, _T("_eSW_ALIGN_FLOW_DONE"));
						else
							//SetStep(_eSW_ALIGN_FLOW_FINISH_GANTRY_Z1_WAIT_POS, _T("_eSW_ALIGN_FLOW_FINISH_GANTRY_Z1_WAIT_POS"));
							SetStep(_eSW_ALIGN_FLOW_FINISH_GANTRY_Z3_WAIT_POS, _T("_eSW_ALIGN_FLOW_FINISH_GANTRY_Z3_WAIT_POS"));

						break;
					}
				}
				else
				{
					if (CModelData::m_InspectionPara.Info.bSwAlignVerifyUse) //KJT 20210428
					{
						if (m_bVerify)
						{
							//KJT 20210412 !!
							m_AlignVisionResultValue[0][0] += (m_SwAlignPointValue[0][0] - m_AlignPointValue[0][0]);
							m_AlignVisionResultValue[1][0] += (m_SwAlignPointValue[1][0] - m_AlignPointValue[1][0]);
							m_AlignVisionResultValue[0][1] += (m_SwAlignPointValue[0][1] - m_AlignPointValue[0][1]);
							m_AlignVisionResultValue[1][1] += (m_SwAlignPointValue[1][1] - m_AlignPointValue[1][1]);
							m_AlignVisionResultValue[0][2] += (m_SwAlignPointValue[0][2] - m_AlignPointValue[0][2]);
							m_AlignVisionResultValue[1][2] += (m_SwAlignPointValue[1][2] - m_AlignPointValue[1][2]);
							m_AlignVisionResultValue[0][3] += (m_SwAlignPointValue[0][3] - m_AlignPointValue[0][3]);
							m_AlignVisionResultValue[1][3] += (m_SwAlignPointValue[1][3] - m_AlignPointValue[1][3]);

							SharedInfo::UpdateSwAlignData(m_AlignPointValue, m_AlignVisionResultValue);
							m_bUpdateSWAlignData = TRUE;

							Str.Format(_T("SWAlignCurCount:%d, UpdateSwAlignData (SpecOut)"), SharedInfo::nSwAlignCurCount);
							Total_Msg(Str);
						}
						else
						{
#if 1 //KJT 20210421
							if (m_eSwAlignType != eSwAlign_Glass)
							{
								//LB
								m_AlignVisionResultValue[0][0] += SharedInfo::dMain2PAlignResultShiftX[1];
								//LT
								m_AlignVisionResultValue[0][1] += SharedInfo::dMain2PAlignResultShiftX[1];
								//RT
								m_AlignVisionResultValue[0][2] += SharedInfo::dMain2PAlignResultShiftX[0];
								//RB
								m_AlignVisionResultValue[0][3] += SharedInfo::dMain2PAlignResultShiftX[0];
							}
#endif

							SharedInfo::UpdateSwAlignData(m_AlignPointValue, m_AlignVisionResultValue);
							m_bUpdateSWAlignData = TRUE;

							Str.Format(_T("SWAlignCurCount:%d, UpdateSwAlignData (Verify, SpecOut)"), SharedInfo::nSwAlignCurCount);
							Total_Msg(Str);
						}

						m_bVerify = TRUE;

						SetStep(_eSW_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND, _T("_eSW_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND"));
					}
					else
					{
#if 1 //KJT 20210421
						if (m_eSwAlignType != eSwAlign_Glass)
						{
							//LB
							m_AlignVisionResultValue[0][0] += SharedInfo::dMain2PAlignResultShiftX[1];
							//LT
							m_AlignVisionResultValue[0][1] += SharedInfo::dMain2PAlignResultShiftX[1];
							//RT
							m_AlignVisionResultValue[0][2] += SharedInfo::dMain2PAlignResultShiftX[0];
							//RB
							m_AlignVisionResultValue[0][3] += SharedInfo::dMain2PAlignResultShiftX[0];
						}
#endif

						SharedInfo::UpdateSwAlignData(m_AlignPointValue, m_AlignVisionResultValue);
						m_bUpdateSWAlignData = TRUE;

						Str.Format(_T("SWAlignCurCount:%d, UpdateSwAlignData (Verify NotUse)"), SharedInfo::nSwAlignCurCount);
						Total_Msg(Str);

						SharedInfo::LightAllOff();

						if ((SharedInfo::MachineState.bAutoRunFlag == TRUE && CModelData::m_InspectionPara.Info.bPPAUse) ||
							SharedInfo::nPrevFlowID == eGLASS_MAPPING_FLOW) //KJT 20210419
							SetStep(_eSW_ALIGN_FLOW_DONE, _T("_eSW_ALIGN_FLOW_DONE"));
						else
							SetStep(_eSW_ALIGN_FLOW_FINISH_GANTRY_Z3_WAIT_POS, _T("_eSW_ALIGN_FLOW_FINISH_GANTRY_Z3_WAIT_POS"));
					}
					break;
				}
			}
			else
			{
				Str.Format(_T("SWAlignCurCount:%d Diff X[%d]:%.5f, Y[%d]:%.5f"),
					SharedInfo::nSwAlignCurCount, m_nAlignPoint, m_AlignVisionResultValue[0][m_nAlignPoint], m_nAlignPoint, m_AlignVisionResultValue[1][m_nAlignPoint]);
				Total_Msg(Str);

				m_nAlignPoint++;
				Sleep(500);
				SetStep(_eSW_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND, _T("_eSW_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND"));
			}
			break;

		case _eSW_ALIGN_FLOW_FINISH_GANTRY_Z3_WAIT_POS:
			Devs::m_GantryMotion.Move_GantryZ_All_Wait_Pos();
			Sleep(20); //!!

			SetStep(_eSW_ALIGN_FLOW_FINISH_GANTRY_Z3_WAIT_POS_CHECK, _T("_eSW_ALIGN_FLOW_FINISH_GANTRY_Z3_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);

			break;

		case _eSW_ALIGN_FLOW_FINISH_GANTRY_Z3_WAIT_POS_CHECK:
			if (Devs::m_GantryMotion.Is_GantryZ_All_Wait_Pos())
			{
				//if (SharedInfo::MachineState.bAutoRunFlag == TRUE && SharedInfo::Active.ProcessEndFlow != eCOMBO_AUTO_RUN_FLOW_SW_ALIGN)
				if (SharedInfo::MachineState.bAutoRunFlag == TRUE)
					SetStep(_eSW_ALIGN_FLOW_DONE, _T("_eSW_ALIGN_FLOW_DONE"));
				else
					SetStep(_eSW_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS, _T("_eSW_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSW_ALIGN_FLOW_FINISH_GANTRY_Z3_WAIT_POS_CHECK : Find Hole"), eSW_FLOW + 11);
				SetStep(_eSW_ALIGN_FLOW_ERROR, _T("_eSW_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSW_ALIGN_FLOW_FINISH_GANTRY_Z3_WAIT_POS_CHECK, _T("_eSW_ALIGN_FLOW_FINISH_GANTRY_Z3_WAIT_POS_CHECK"));
			}
			break;

		case _eSW_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS:
			Devs::m_GantryMotion.Move_Gantry_X_Wait_Pos();
			Sleep(20); //!!
			Devs::m_GantryMotion.Move_Gantry_Y_Wait_Pos();
			Sleep(20); //!!

			SetStep(_eSW_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK, _T("_eSW_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eSW_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Wait_Pos() && Devs::m_GantryMotion.Is_Gantry_Y_Wait_Pos())
			{
				SetStep(_eSW_ALIGN_FLOW_DONE, _T("_eSW_ALIGN_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eSW_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK : Find Hole"), eSW_FLOW + 12);
				SetStep(_eSW_ALIGN_FLOW_ERROR, _T("_eSW_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eSW_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK, _T("_eSW_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK"));
			}
			break;

		case _eSW_ALIGN_FLOW_ERROR:
			break;

		case _eSW_ALIGN_FLOW_DONE:
		{
			SharedInfo::LightAllOff();

			SharedInfo::nPrevFlowID = eSW_FLOW; //KJT 20210326

			m_bFlowDone = TRUE;

			SharedInfo::CalTactTime(_T("SW_ALIGN_FLOW"), m_timeStart); //KJT 20210329

			SetStep(_eSW_ALIGN_FLOW_IDLE, _T("_eSW_ALIGN_FLOW_IDLE"));
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

double CSwAlignFlow::GetAlignPos_X(int nAlignCount)
{
	double dPos = m_AlignPointValue[0][nAlignCount];
	return dPos;
}
double CSwAlignFlow::GetAlignPos_Y(int nAlignCount)
{
	double dPos = m_AlignPointValue[1][nAlignCount];
	return dPos;
}

BOOL CSwAlignFlow::FlowInterlock()
{
	/////////////////////////////////////////////////////////////////////////////
	if (Devs::m_GantryMotion.CheckGantryXYZFlowInterlock(_T("SwAlignFlow"), eSW_FLOW, 30) == FALSE)
	{
		return FALSE;
	}	

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