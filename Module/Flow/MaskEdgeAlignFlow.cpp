#include "stdafx.h"
#include "MaskEdgeAlignFlow.h"
#include "Log/Logger.h"
#include "Vision/Devs.h"
#include "Data/ModelData.h"
#include "CamAreaModul.h"
#include "Data/SystemData.h"
#include "FmmLight1.h"

CMaskEdgeAlignFlow::CMaskEdgeAlignFlow()
{
	m_dDiffPos[0] = 0.;
	m_dDiffPos[1] = 0.;
	m_dDiffPos[2] = 0.;

	m_dTarget[0] = 0.;
	m_dTarget[1] = 0.;
	m_dTarget[2] = 0.;

	m_nAlignPoint = 0;

	memset(m_AlignPointValue, 0x0, sizeof(m_AlignPointValue));
	memset(m_AlignVisionResultValue, 0x0, sizeof(m_AlignVisionResultValue));
}


CMaskEdgeAlignFlow::~CMaskEdgeAlignFlow()
{
}

BOOL CMaskEdgeAlignFlow::InitProcess()
{
	m_StateComplete = NULL;
	m_FlowFinish = TRUE;
	m_bTerminate = FALSE;
	m_bFlowDone = TRUE;

#pragma region //Step Group
	int nGroupIndex = 0;

	m_sGroupInfo[nGroupIndex].m_bProcessingFlag = FALSE;
	m_sGroupInfo[nGroupIndex].nStartStep = _eMASK_EDGE_ALIGN_FLOW_START;
	m_sGroupInfo[nGroupIndex].nEndStep = _eMASK_EDGE_ALIGN_FLOW_INTERLOCK;
	m_sGroupInfo[nGroupIndex].strGroupName.Format(_T("%d. Start"), nGroupIndex + 1);
	nGroupIndex++;

	m_sGroupInfo[nGroupIndex].m_bProcessingFlag = FALSE;
	m_sGroupInfo[nGroupIndex].nStartStep = _eMASK_EDGE_ALIGN_FLOW_UNLOADER_READY;
	m_sGroupInfo[nGroupIndex].nEndStep = _eMASK_EDGE_ALIGN_FLOW_GANTRY_ZX_READY_CHECK;
	m_sGroupInfo[nGroupIndex].strGroupName.Format(_T("%d. Other Axis Ready"), nGroupIndex + 1);
	nGroupIndex++;

	m_sGroupInfo[nGroupIndex].m_bProcessingFlag = FALSE;
	m_sGroupInfo[nGroupIndex].nStartStep = _eMASK_EDGE_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST;
	m_sGroupInfo[nGroupIndex].nEndStep = _eMASK_EDGE_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK;
	m_sGroupInfo[nGroupIndex].strGroupName.Format(_T("%d. Gantry XY Align Pos"), nGroupIndex + 1);
	nGroupIndex++;

	//m_sGroupInfo[nGroupIndex].m_bProcessingFlag = FALSE;
	//m_sGroupInfo[nGroupIndex].nStartStep = _eMASK_EDGE_ALIGN_FLOW_GANTRY_Z1_INSPECTION_POS_1ST;
	//m_sGroupInfo[nGroupIndex].nEndStep = _eMASK_EDGE_ALIGN_FLOW_GANTRY_Z1_INSPECTION_POS_1ST_CHECK;
	//m_sGroupInfo[nGroupIndex].strGroupName.Format(_T("%d. Gantry Z1 Inspection Pos"), nGroupIndex + 1);
	//nGroupIndex++;

	m_sGroupInfo[nGroupIndex].m_bProcessingFlag = FALSE;
	m_sGroupInfo[nGroupIndex].nStartStep = _eMASK_EDGE_ALIGN_FLOW_AUTOFOCUS_CHECK;
	m_sGroupInfo[nGroupIndex].nEndStep = _eMASK_EDGE_ALIGN_FLOW_GRAB_DONE_CHECK;
	m_sGroupInfo[nGroupIndex].strGroupName.Format(_T("%d. Autofocus And Image Grab"), nGroupIndex + 1);
	nGroupIndex++;

	m_sGroupInfo[nGroupIndex].m_bProcessingFlag = FALSE;
	m_sGroupInfo[nGroupIndex].nStartStep = _eMASK_EDGE_ALIGN_FLOW_INSPECTION_UVW_MOVE_START;
	m_sGroupInfo[nGroupIndex].nEndStep = _eMASK_EDGE_ALIGN_FLOW_INSPECTION_UVW_MOVE_DONE_CHECK;
	m_sGroupInfo[nGroupIndex].strGroupName.Format(_T("%d. Uvw Move"), nGroupIndex + 1);
	nGroupIndex++;

	//m_sGroupInfo[nGroupIndex].m_bProcessingFlag = FALSE;
	//m_sGroupInfo[nGroupIndex].nStartStep = _eMASK_EDGE_ALIGN_FLOW_FINISH_GANTRY_Z1_WAIT_POS;
	//m_sGroupInfo[nGroupIndex].nEndStep = _eMASK_EDGE_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK;
	//m_sGroupInfo[nGroupIndex].strGroupName.Format(_T("%d. Gantry ZXY Finish Wait Pos"), nGroupIndex + 1);
	//nGroupIndex++;

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
BOOL CMaskEdgeAlignFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eMASK_EDGE_ALIGN_FLOW_IDLE);

	if (hHandle != NULL)
	{
		CloseHandle(hHandle);
		hHandle = NULL;
	}

	return TRUE;
}
BOOL CMaskEdgeAlignFlow::Start(int nStep)
{
	memset(Devs::m_GantryMotion.m_dTpX, 0, sizeof(Devs::m_GantryMotion.m_dTpX));
	memset(Devs::m_GantryMotion.m_dTpY, 0, sizeof(Devs::m_GantryMotion.m_dTpY));

	m_bFlowDone = FALSE;
	m_bStopBit = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(nStep, _T("_eMASK_EDGE_ALIGN_FLOW_START"));
	return TRUE;
}
BOOL CMaskEdgeAlignFlow::Stop()
{
	m_bStopBit = TRUE;
	return TRUE;
}
UINT CMaskEdgeAlignFlow::ThreadFunction(LPVOID lpParam)
{
	CMaskEdgeAlignFlow* pFlow = NULL;

	pFlow = (CMaskEdgeAlignFlow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}
VOID CMaskEdgeAlignFlow::ThreadFunctionEntry(VOID)
{
	DWORD	dwResult = 0;
	double	dStrt_Time = GetTickCount();
	double	dEnd_Time = GetTickCount();
	double	dWait_Time = GetTickCount();
	int		nWork_Mask_Mode = -1;
	int		nWork_Mask_Index = -1;
	BOOL	bComplete_Step = FALSE;
	CString Str = _T("");
	double dVel[3] = { 1.0, 1.0, 1.0 };
	double dAcc[3] = { 2.0, 2.0, 2.0 };
	double dDecel[3] = { 2.0, 2.0, 2.0 };

	double dRefPos[4][2] = { 0.0, };
	double dActPos[4][2] = { 0.0, };

	double dPosX = 0.0, dPosY = 0.0;

	double dDiffXTemp = 0.0, dDiffYTemp = 0.0;

	int nBackLightVal[BACKLIGHT_CH_COUNT] = { BACKLIGHT_OFF_VALUE, };

	while (m_FlowFinish)
	{
		WaitForSingleObject(hHandle, INFINITE);
		ResetEvent(hHandle);

		if (SharedInfo::bMachineStopFlag == TRUE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(_eMASK_EDGE_ALIGN_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}

		switch (GetCurrentTotalStep())
		{
		case _eMASK_EDGE_ALIGN_FLOW_IDLE:
		{
			break;
		}
		case _eMASK_EDGE_ALIGN_FLOW_START:
		{
			m_timeStart = CTime::GetCurrentTime(); //KJT 20210329

#ifndef SIM_MODE
			if (CModelData::m_InspectionPara.Info.bMappingDataUse)
			{
				Devs::m_MappingProc.InitializeGlassMapping(eMAPPING_ID_10X);
				if (Devs::m_MappingProc.LoadGlassMappingFile(eMAPPING_ID_10X) == FALSE)
				{
					SetStep(_eMASK_EDGE_ALIGN_FLOW_ERROR, _T("_eMASK_EDGE_ALIGN_FLOW_ERROR"));
					break;
				}
			}
#endif

#if 1
#if 0
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
#else //KJT 20210303 Slot
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
#endif
#else //Stick LT
			//Fixed Test. KJT 20210301. Line EdgeAlign Ok
			//LB
			m_AlignPointValue[0][0] = -428.5406843;
			m_AlignPointValue[1][0] = -35.46667;
			//LT
			m_AlignPointValue[0][1] = -428.5406843;
			m_AlignPointValue[1][1] = 35.47133;
			//RT
			m_AlignPointValue[0][2] = 428.5954488;
			m_AlignPointValue[1][2] = 35.47133;
			//RB
			m_AlignPointValue[0][3] = 428.5954488;
			m_AlignPointValue[1][3] = -35.46667;
#endif

			/////////////
			SharedInfo::nGantryZ1View = eViewReview10X;

			m_nAlignPoint = 0;

			memset(m_AlignVisionResultValue, 0x0, sizeof(m_AlignVisionResultValue));
			memset(SharedInfo::dMainEdge4PAlignVisionResultValue, 0x0, sizeof(SharedInfo::dMainEdge4PAlignVisionResultValue));

			SharedInfo::nMainEdge4PAlignCurCount = 0;

			SharedInfo::LightAllOff();
			for (int i = 0; i < BACKLIGHT_CH_COUNT; i++)
				nBackLightVal[i] = CModelData::m_AlignPara.Info.nEdge4PAlignBacklight; // 10;

			//Sleep(500);
			//g_CommLight_8ch.SetLight_Review_Coaxial(CModelData::m_AlignPara.Info.nEdge4PAlignCoAxial);
			//Sleep(30);
			//g_CommLight_12ch.SetLight_Review_Ring(CModelData::m_AlignPara.Info.nEdge4PAlignRing);
			//Sleep(30);
			//g_CommMLCLedLight.BackLightOn(nBackLightVal);
			//Sleep(500);

			g_CommReview_Light.SetLight_Review(CModelData::m_AlignPara.Info.nEdge4PAlignRing, CModelData::m_AlignPara.Info.nEdge4PAlignCoAxial);
			Sleep(30);
			SharedInfo::BackLightOn(CModelData::m_AlignPara.Info.nEdge4PAlignBacklight);


			Devs::m_MappingProc.ReleaseSWMapping(eMAPPING_ID_10X); //!! KJT 20200913
			Devs::m_MappingProc.ReleaseXYTAlignData(eMAPPING_ID_10X); //!! KJT 20200913

			SetStep(_eMASK_EDGE_ALIGN_FLOW_INTERLOCK, _T("_eMASK_EDGE_ALIGN_FLOW_INTERLOCK"));
			break;
		}
		
		case _eMASK_EDGE_ALIGN_FLOW_INTERLOCK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(_eMASK_EDGE_ALIGN_FLOW_ERROR, _T("_eMASK_EDGE_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetStep(_eMASK_EDGE_ALIGN_FLOW_UNLOADER_READY, _T("_eMASK_EDGE_ALIGN_FLOW_UNLOADER_READY"));
			}
			break;

#pragma region //Unloader Ready
		case _eMASK_EDGE_ALIGN_FLOW_UNLOADER_READY:
			Devs::m_Ready_UnloaderFlow.Start();

			SetStep(_eMASK_EDGE_ALIGN_FLOW_UNLOADER_READY_CHECK, _T("_eMASK_EDGE_ALIGN_FLOW_UNLOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMASK_EDGE_ALIGN_FLOW_UNLOADER_READY_CHECK:
			if (Devs::m_Ready_UnloaderFlow.IsFlowDone())
			{
				SetStep(_eMASK_EDGE_ALIGN_FLOW_LOADER_READY, _T("_eMASK_EDGE_ALIGN_FLOW_LOADER_READY"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eMASK_EDGE_ALIGN_FLOW_ERROR, _T("_eMASK_EDGE_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMASK_EDGE_ALIGN_FLOW_UNLOADER_READY_CHECK, _T("_eMASK_EDGE_ALIGN_FLOW_UNLOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Loader Ready
		case _eMASK_EDGE_ALIGN_FLOW_LOADER_READY:
			Devs::m_Ready_LoaderFlow.Start();

			SetStep(_eMASK_EDGE_ALIGN_FLOW_LOADER_READY_CHECK, _T("_eMASK_EDGE_ALIGN_FLOW_LOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMASK_EDGE_ALIGN_FLOW_LOADER_READY_CHECK:
			if (Devs::m_Ready_LoaderFlow.IsFlowDone())
			{
				//SetStep(_eMASK_EDGE_ALIGN_FLOW_BOX_CAMERA_READY, _T("_eMASK_EDGE_ALIGN_FLOW_BOX_CAMERA_READY"));
				SetStep(_eMASK_EDGE_ALIGN_FLOW_GANTRY_ZX_READY, _T("_eMASK_EDGE_ALIGN_FLOW_GANTRY_ZX_READY"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eMASK_EDGE_ALIGN_FLOW_ERROR, _T("_eMASK_EDGE_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMASK_EDGE_ALIGN_FLOW_LOADER_READY_CHECK, _T("_eMASK_EDGE_ALIGN_FLOW_LOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Box Camera Ready
		case _eMASK_EDGE_ALIGN_FLOW_BOX_CAMERA_READY:
			Devs::m_BoxMotion.BoxAlignCameraYL_WaitPos();
			Sleep(20);
			Devs::m_BoxMotion.BoxAlignCameraYR_WaitPos();
			Sleep(500); //!!

			SetStep(_eMASK_EDGE_ALIGN_FLOW_BOX_CAMERA_READY_CHECK, _T("_eMASK_EDGE_ALIGN_FLOW_BOX_CAMERA_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMASK_EDGE_ALIGN_FLOW_BOX_CAMERA_READY_CHECK:
			if (Devs::m_BoxMotion.Is_BoxAlignCameraYL_WaitPos() == TRUE && Devs::m_BoxMotion.Is_BoxAlignCameraYR_WaitPos() == TRUE)
			{
				SetStep(_eMASK_EDGE_ALIGN_FLOW_GANTRY_ZX_READY, _T("_eMASK_EDGE_ALIGN_FLOW_GANTRY_ZX_READY"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eMASK_EDGE_ALIGN_FLOW_ERROR, _T("_eMASK_EDGE_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMASK_EDGE_ALIGN_FLOW_BOX_CAMERA_READY_CHECK, _T("_eMASK_EDGE_ALIGN_FLOW_BOX_CAMERA_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Gantry Z, X Ready
		case _eMASK_EDGE_ALIGN_FLOW_GANTRY_ZX_READY:
			Devs::m_Ready_GantryZX_Flow.Start();

			SetStep(_eMASK_EDGE_ALIGN_FLOW_GANTRY_ZX_READY_CHECK, _T("_eMASK_EDGE_ALIGN_FLOW_GANTRY_ZX_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMASK_EDGE_ALIGN_FLOW_GANTRY_ZX_READY_CHECK:
			if (Devs::m_Ready_GantryZX_Flow.IsFlowDone())
			{
				SetStep(_eMASK_EDGE_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST, _T("_eMASK_EDGE_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eMASK_EDGE_ALIGN_FLOW_ERROR, _T("_eMASK_EDGE_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMASK_EDGE_ALIGN_FLOW_GANTRY_ZX_READY_CHECK, _T("_eMASK_EDGE_ALIGN_FLOW_GANTRY_ZX_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Gantry XYZ First Pos Move
		case _eMASK_EDGE_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST:
			m_dTargetPosX = dPosX = GetAlignPos_X(m_nAlignPoint);
			m_dTargetPosY = dPosY = GetAlignPos_Y(m_nAlignPoint);

#ifndef SIM_MODE
			if (CModelData::m_InspectionPara.Info.bMappingDataUse)
			{
				Devs::m_MappingProc.GetGlassMapping_CalibPosXY(eMAPPING_ID_10X, &m_dTargetPosX, &m_dTargetPosY);
				Str.Format(_T("Mapping Data X:%10.5f, Y:%10.5f => X:%10.5f, Y:%10.5f"), dPosX, dPosY, m_dTargetPosX, m_dTargetPosY);
				Total_Msg(Str);
			}
#endif
			Devs::m_GantryMotion.Move_Gantry_X_Pos(m_dTargetPosX, TRUE);
			Sleep(20); //!!
			Devs::m_GantryMotion.Move_Gantry_Y_Pos(m_dTargetPosY);
			Sleep(20); //!!

			SetStep(_eMASK_EDGE_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK, _T("_eMASK_EDGE_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMASK_EDGE_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Pos(m_dTargetPosX) && Devs::m_GantryMotion.Is_Gantry_Y_Pos(m_dTargetPosY))
			{
				if (Devs::m_InspectionStageMotion.Is_BackLight_X_Pos(m_dTargetPosX))
					//SetStep(_eMASK_EDGE_ALIGN_FLOW_GANTRY_Z1_INSPECTION_POS_1ST, _T("_eMASK_EDGE_ALIGN_FLOW_GANTRY_Z1_INSPECTION_POS_1ST"));
					SetStep(_eMASK_EDGE_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_1ST, _T("_eMASK_EDGE_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_1ST"));
				else
					SetCheckStep(_eMASK_EDGE_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK, _T("_eMASK_EDGE_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eMASK_EDGE_ALIGN_FLOW_ERROR, _T("_eMASK_EDGE_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMASK_EDGE_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK, _T("_eMASK_EDGE_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK"));
			}
			break;

		case _eMASK_EDGE_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_1ST:
			Devs::m_GantryMotion.Move_GantryZ1_InspectionReview_Pos();			
			Sleep(20); //!!

			SetStep(_eMASK_EDGE_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_1ST_CHECK, _T("_eMASK_EDGE_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_1ST_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMASK_EDGE_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_1ST_CHECK:
			if (Devs::m_GantryMotion.Is_GantryZ1_InspectionReview_Pos())
			{
				Sleep(500); //!!
				SetStep(_eMASK_EDGE_ALIGN_FLOW_AUTOFOCUS_CHECK, _T("_eMASK_EDGE_ALIGN_FLOW_AUTOFOCUS_CHECK"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eMASK_EDGE_ALIGN_FLOW_ERROR, _T("_eMASK_EDGE_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMASK_EDGE_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_1ST_CHECK, _T("_eMASK_EDGE_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_1ST_CHECK"));
			}
			break;
#pragma endregion

		case _eMASK_EDGE_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_2ND:
			Devs::m_GantryMotion.Move_GantryZ1_InspectionReview_Pos();
			Sleep(20); //!!

			SetStep(_eMASK_EDGE_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_2ND_CHECK, _T("_eMASK_EDGE_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_2ND_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMASK_EDGE_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_2ND_CHECK:
			if (Devs::m_GantryMotion.Is_GantryZ1_InspectionReview_Pos())
			{
				SetStep(_eMASK_EDGE_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND, _T("_eMASK_EDGE_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eMASK_EDGE_ALIGN_FLOW_ERROR, _T("_eMASK_EDGE_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMASK_EDGE_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_2ND_CHECK, _T("_eMASK_EDGE_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_2ND_CHECK"));
			}
			break;

		case _eMASK_EDGE_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND:
			m_dTargetPosX = dPosX = GetAlignPos_X(m_nAlignPoint);
			m_dTargetPosY = dPosY = GetAlignPos_Y(m_nAlignPoint);

#ifndef SIM_MODE
			if (CModelData::m_InspectionPara.Info.bMappingDataUse)
			{
				Devs::m_MappingProc.GetGlassMapping_CalibPosXY(eMAPPING_ID_10X, &m_dTargetPosX, &m_dTargetPosY);
				Str.Format(_T("Mapping Data X:%10.5f, Y:%10.5f => X:%10.5f, Y:%10.5f"), dPosX, dPosY, m_dTargetPosX, m_dTargetPosY);
				Total_Msg(Str);
			}
#endif
			Devs::m_GantryMotion.Move_Gantry_X_Pos(m_dTargetPosX, TRUE);
			Sleep(20); //!!
			Devs::m_GantryMotion.Move_Gantry_Y_Pos(m_dTargetPosY);
			Sleep(20); //!!

			SetStep(_eMASK_EDGE_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK, _T("_eMASK_EDGE_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMASK_EDGE_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Pos(m_dTargetPosX) && Devs::m_GantryMotion.Is_Gantry_Y_Pos(m_dTargetPosY))
			{
				if (Devs::m_InspectionStageMotion.Is_BackLight_X_Pos(m_dTargetPosX))
				{
					Sleep(500); //!!
					SetStep(_eMASK_EDGE_ALIGN_FLOW_AUTOFOCUS_CHECK, _T("_eMASK_EDGE_ALIGN_FLOW_AUTOFOCUS_CHECK"));
				}
				else
					SetCheckStep(_eMASK_EDGE_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK, _T("_eMASK_EDGE_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eMASK_EDGE_ALIGN_FLOW_ERROR, _T("_eMASK_EDGE_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMASK_EDGE_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK, _T("_eMASK_EDGE_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK"));
			}
			break;

		case _eMASK_EDGE_ALIGN_FLOW_AUTOFOCUS_CHECK:
			if (CModelData::m_AlignPara.Info.nEdge4PAlignFocusType == eFocusType_Laser || CModelData::m_AlignPara.Info.nEdge4PAlignFocusType == eFocusType_Both)
				SetStep(_eMASK_EDGE_ALIGN_FLOW_LASER_FOCUS_START, _T("_eMASK_EDGE_ALIGN_FLOW_LASER_FOCUS_START"));
			else if (CModelData::m_AlignPara.Info.nEdge4PAlignFocusType == eFocusType_Image)
				SetStep(_eMASK_EDGE_ALIGN_FLOW_IMAGE_FOCUS_START, _T("_eMASK_EDGE_ALIGN_FLOW_IMAGE_FOCUS_START"));
			else
				SetStep(_eMASK_EDGE_ALIGN_FLOW_GRAB_START, _T("_eMASK_EDGE_ALIGN_FLOW_GRAB_START"));
			break;

		case _eMASK_EDGE_ALIGN_FLOW_LASER_FOCUS_START:
			Devs::m_GantryMotion.LaserFocusMove();

			SetStep(_eMASK_EDGE_ALIGN_FLOW_LASER_FOCUS_CHECK, _T("_eMASK_EDGE_ALIGN_FLOW_LASER_FOCUS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMASK_EDGE_ALIGN_FLOW_LASER_FOCUS_CHECK:
			if (Devs::m_GantryMotion.LaserFocusMoveCheck())
			{
				Sleep(500); //!!	//KJT 20210321

				if (CModelData::m_AlignPara.Info.nEdge4PAlignFocusType == eFocusType_Both)
					SetStep(_eMASK_EDGE_ALIGN_FLOW_IMAGE_FOCUS_START, _T("_eMASK_EDGE_ALIGN_FLOW_IMAGE_FOCUS_START"));
				else
					SetStep(_eMASK_EDGE_ALIGN_FLOW_GRAB_START, _T("_eMASK_EDGE_ALIGN_FLOW_GRAB_START"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eMASK_EDGE_ALIGN_FLOW_ERROR, _T("_eMASK_EDGE_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMASK_EDGE_ALIGN_FLOW_LASER_FOCUS_CHECK, _T("_eMASK_EDGE_ALIGN_FLOW_LASER_FOCUS_CHECK"));
			}
			break;

		case _eMASK_EDGE_ALIGN_FLOW_IMAGE_FOCUS_START:
#ifndef SIM_MODE
			g_pReview10x->m_bAfEnd = FALSE;
			g_pReview10x->AutofoucsRun();
#endif

			SetStep(_eMASK_EDGE_ALIGN_FLOW_IMAGE_FOCUS_CHECK, _T("_eMASK_EDGE_ALIGN_FLOW_IMAGE_FOCUS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMASK_EDGE_ALIGN_FLOW_IMAGE_FOCUS_CHECK:
#ifndef SIM_MODE
			if (g_pReview10x->m_bAfEnd == TRUE)
			{
				Sleep(IMAGE_FOCUS_DELAY);
				SetStep(_eMASK_EDGE_ALIGN_FLOW_GRAB_START, _T("_eMASK_EDGE_ALIGN_FLOW_GRAB_START"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eMASK_EDGE_ALIGN_FLOW_ERROR, _T("_eMASK_EDGE_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMASK_EDGE_ALIGN_FLOW_IMAGE_FOCUS_CHECK, _T("_eMASK_EDGE_ALIGN_FLOW_IMAGE_FOCUS_CHECK"));
			}
#else
			Sleep(IMAGE_FOCUS_DELAY);
			SetStep(_eMASK_EDGE_ALIGN_FLOW_GRAB_START, _T("_eMASK_EDGE_ALIGN_FLOW_GRAB_START"));
#endif
			break;

		case _eMASK_EDGE_ALIGN_FLOW_GRAB_START:
			SharedInfo::bMainEdgeAlignGrabDone = FALSE;
			Devs::m_GantryMotion.FindBlob_Edge4PAlign_Review10X(&m_AlignVisionResultValue[0][m_nAlignPoint], &m_AlignVisionResultValue[1][m_nAlignPoint]);

			SharedInfo::dMainEdge4PAlignVisionResultValue[0][m_nAlignPoint] = m_AlignVisionResultValue[0][m_nAlignPoint];
			SharedInfo::dMainEdge4PAlignVisionResultValue[1][m_nAlignPoint] = m_AlignVisionResultValue[1][m_nAlignPoint];

			Str.Format(_T("AlignCnt:%d Diff X:%.5f, Y:%.5f"), m_nAlignPoint, m_AlignVisionResultValue[0][m_nAlignPoint], m_AlignVisionResultValue[1][m_nAlignPoint]);
			Total_Msg(Str);

			SetStep(_eMASK_EDGE_ALIGN_FLOW_GRAB_DONE_CHECK, _T("_eMASK_EDGE_ALIGN_FLOW_GRAB_DONE_CHECK"));
			break;

		case _eMASK_EDGE_ALIGN_FLOW_GRAB_DONE_CHECK:
			if (m_AlignVisionResultValue[0][m_nAlignPoint] == 0.0 && m_AlignVisionResultValue[1][m_nAlignPoint] == 0.0) //KJT 20210314
			{
				Sleep(IMAGE_FOCUS_DELAY);
				SetStep(_eMASK_EDGE_ALIGN_FLOW_GRAB_START, _T("_eMASK_EDGE_ALIGN_FLOW_GRAB_START"));
			}
			else
			{
				SharedInfo::bMainEdgeAlignGrabDone = TRUE;
				if (m_nAlignPoint == 3)
				{
					m_nAlignPoint = 0;

					SharedInfo::nMainEdge4PAlignCurCount++;
					Str.Format(_T("AlignCurCount:%d Diff X[0]:%.5f, Y[0]:%.5f, X[1]:%.5f, Y[1]:%.5f, X[2]:%.5f, Y[2]:%.5f, X[3]:%.5f, Y[3]:%.5f"),
						SharedInfo::nMainEdge4PAlignCurCount,
						m_AlignVisionResultValue[0][0], m_AlignVisionResultValue[1][0], m_AlignVisionResultValue[0][1], m_AlignVisionResultValue[1][1],
						m_AlignVisionResultValue[0][2], m_AlignVisionResultValue[1][2], m_AlignVisionResultValue[0][3], m_AlignVisionResultValue[1][3]);
					Total_Msg(Str);

					Sleep(100);
					Devs::m_InspectionStageMotion.GetUVWPos(m_AlignPointValue[0], m_AlignPointValue[1], m_AlignVisionResultValue[0], m_AlignVisionResultValue[1], &m_dDiffPos[0], &m_dDiffPos[1], &m_dDiffPos[2], FALSE);

					Str.Format(_T("Uvw Diff Pos X:%.5f, Y:%.5f, T:%.5f"), m_dDiffPos[0], m_dDiffPos[1], m_dDiffPos[2]);
					Total_Msg(Str);

					//dDiffXTemp = (m_AlignVisionResultValue[0][0] + m_AlignVisionResultValue[0][1] + m_AlignVisionResultValue[0][2] + m_AlignVisionResultValue[0][3]) / 4;
					//dDiffYTemp = (m_AlignVisionResultValue[1][0] + m_AlignVisionResultValue[1][3] + m_AlignVisionResultValue[1][1] + m_AlignVisionResultValue[1][2]) / 4;
					//KJT 20210302
					if (fabs(m_AlignVisionResultValue[0][1] + m_AlignVisionResultValue[0][2]) < fabs(m_AlignVisionResultValue[0][3] + m_AlignVisionResultValue[0][0]))
						dDiffXTemp = fabs(m_AlignVisionResultValue[0][1] + m_AlignVisionResultValue[0][2]);
					else
						dDiffXTemp = fabs(m_AlignVisionResultValue[0][3] + m_AlignVisionResultValue[0][0]);

					if (fabs(m_AlignVisionResultValue[1][0] + m_AlignVisionResultValue[1][1]) < fabs(m_AlignVisionResultValue[1][2] + m_AlignVisionResultValue[1][3]))
						dDiffYTemp = fabs(m_AlignVisionResultValue[1][0] + m_AlignVisionResultValue[1][1]);
					else
						dDiffYTemp = fabs(m_AlignVisionResultValue[1][2] + m_AlignVisionResultValue[1][3]);

					Str.Format(_T("Diff_X:%.5f, Diff_Y:%.5f"), dDiffXTemp, dDiffYTemp);
					Total_Msg(Str);

					//KJT 20210301
#if 1
					if (fabs(dDiffXTemp) < (float)CModelData::m_AlignPara.Info.dEdge4PAlignTargetX &&
						fabs(dDiffYTemp) < (float)CModelData::m_AlignPara.Info.dEdge4PAlignTargetY &&
						//fabs(m_AlignVisionResultValue[0][0]) < CModelData::m_AlignPara.Info.dEdge4PAlignTargetX &&
						//fabs(m_AlignVisionResultValue[1][0]) < CModelData::m_AlignPara.Info.dEdge4PAlignTargetY &&
						//fabs(m_AlignVisionResultValue[0][1]) < CModelData::m_AlignPara.Info.dEdge4PAlignTargetX &&
						//fabs(m_AlignVisionResultValue[1][1]) < CModelData::m_AlignPara.Info.dEdge4PAlignTargetY &&
						//fabs(m_AlignVisionResultValue[0][2]) < CModelData::m_AlignPara.Info.dEdge4PAlignTargetX &&
						//fabs(m_AlignVisionResultValue[1][2]) < CModelData::m_AlignPara.Info.dEdge4PAlignTargetY &&
						//fabs(m_AlignVisionResultValue[0][3]) < CModelData::m_AlignPara.Info.dEdge4PAlignTargetX &&
						//fabs(m_AlignVisionResultValue[1][3]) < CModelData::m_AlignPara.Info.dEdge4PAlignTargetY &&
						(fabs(m_dDiffPos[2]) < 0.001 || (360 - fabs(m_dDiffPos[2])) < 0.001)) //KJT 20210319
					{
						SharedInfo::UpdateSwAlignData(m_AlignPointValue, m_AlignVisionResultValue); //SWMapping

						SharedInfo::LightAllOff(); //KJT 20210226

						SetStep(_eMASK_EDGE_ALIGN_FLOW_FINISH_GANTRY_Z3_WAIT_POS, _T("_eMASK_EDGE_ALIGN_FLOW_FINISH_GANTRY_Z3_WAIT_POS"));
					}
					else
					{
						SetStep(_eMASK_EDGE_ALIGN_FLOW_INSPECTION_UVW_MOVE_START, _T("_eMASK_EDGE_ALIGN_FLOW_INSPECTION_UVW_MOVE_START"));
					}
#else
					if (fabs(m_dDiffPos[2]) < 0.001 &&
						fabs(dDiffXTemp) < CModelData::m_AlignPara.Info.dEdge4PAlignTargetX &&
						fabs(dDiffYTemp) < CModelData::m_AlignPara.Info.dEdge4PAlignTargetY)
					{
						SharedInfo::LightAllOff(); //KJT 20210226

						SetStep(_eMASK_EDGE_ALIGN_FLOW_FINISH_GANTRY_Z1_WAIT_POS, _T("_eMASK_EDGE_ALIGN_FLOW_FINISH_GANTRY_Z1_WAIT_POS"));
					}
					else
					{
						if (fabs(m_dDiffPos[2]) > 0.001)
						{
							m_dDiffPos[0] = 0.0;
							m_dDiffPos[1] = 0.0;
						}
						else if (fabs(dDiffXTemp) > CModelData::m_AlignPara.Info.dEdge4PAlignTargetX || fabs(dDiffYTemp) > CModelData::m_AlignPara.Info.dEdge4PAlignTargetY)
						{
							m_dDiffPos[2] = 0.0;
						}

						SetStep(_eMASK_EDGE_ALIGN_FLOW_INSPECTION_UVW_MOVE_START, _T("_eMASK_EDGE_ALIGN_FLOW_INSPECTION_UVW_MOVE_START"));
					}
#endif
				}
				else
				{
					m_nAlignPoint++;
					Sleep(1000);
					SetStep(_eMASK_EDGE_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_2ND, _T("_eMASK_EDGE_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_2ND"));
				}
			}
			break;

		case _eMASK_EDGE_ALIGN_FLOW_INSPECTION_UVW_MOVE_START:
		{
			if (SharedInfo::bMainEdgeAlignGrabDone == FALSE)
			{
				Total_Msg(_T("Grab Done False !!"));
				SetStep(_eMASK_EDGE_ALIGN_FLOW_ERROR, _T("_eMASK_EDGE_ALIGN_FLOW_ERROR"));
				break;
			}

#if UVW_MOVE_TYPE //KJT 20210322
			memset(dRefPos, 0, sizeof(dRefPos));
			memset(dActPos, 0, sizeof(dActPos));

			//0:LB, 1:LT, 2:RT, 3:RB
			dRefPos[0][0] = m_AlignPointValue[0][0];
			dRefPos[0][1] = m_AlignPointValue[1][0];

			dRefPos[1][0] = m_AlignPointValue[0][1];
			dRefPos[1][1] = m_AlignPointValue[1][1];

			dRefPos[2][0] = m_AlignPointValue[0][2];
			dRefPos[2][1] = m_AlignPointValue[1][2];

			dRefPos[3][0] = m_AlignPointValue[0][3];
			dRefPos[3][1] = m_AlignPointValue[1][3];


			dActPos[0][0] = m_AlignPointValue[0][0] + m_AlignVisionResultValue[0][0];
			dActPos[0][1] = m_AlignPointValue[1][0] + m_AlignVisionResultValue[1][0];

			dActPos[1][0] = m_AlignPointValue[0][1] + m_AlignVisionResultValue[0][1];
			dActPos[1][1] = m_AlignPointValue[1][1] + m_AlignVisionResultValue[1][1];

			dActPos[2][0] = m_AlignPointValue[0][2] + m_AlignVisionResultValue[0][2];
			dActPos[2][1] = m_AlignPointValue[1][2] + m_AlignVisionResultValue[1][2];

			dActPos[3][0] = m_AlignPointValue[0][3] + m_AlignVisionResultValue[0][3];
			dActPos[3][1] = m_AlignPointValue[1][3] + m_AlignVisionResultValue[1][3];

			//Devs::m_InspectionStageMotion.UVWStageAlignMove(dRefPos, dActPos);
			//Devs::m_InspectionStageMotion.UVWStageAlignMove_4P(dRefPos, dActPos);
			Sleep(1000); //KJT 20210302
#else //KJT 20210304. FMM
			Devs::m_InspectionStageMotion.UVWStagePosMove(m_dDiffPos, dVel, dAcc, dDecel);
#endif
			
			SharedInfo::bMainEdgeAlignGrabDone = FALSE;

			SetStep(_eMASK_EDGE_ALIGN_FLOW_INSPECTION_UVW_MOVE_DONE_CHECK, _T("_eMASK_EDGE_ALIGN_FLOW_INSPECTION_UVW_MOVE_DONE_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
		}
		break;

		case _eMASK_EDGE_ALIGN_FLOW_INSPECTION_UVW_MOVE_DONE_CHECK:
#if UVW_MOVE_TYPE //KJT 20210322
			if (Devs::m_InspectionStageMotion.IsUVWStagePos(m_dDiffPos) == TRUE)
#else //KJT 20210304. FMM
			if (Devs::m_InspectionStageMotion.IsUVWStagePos())
#endif
			{
				SetStep(_eMASK_EDGE_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_2ND, _T("_eMASK_EDGE_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_2ND"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eMASK_EDGE_ALIGN_FLOW_ERROR, _T("_eMASK_EDGE_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMASK_EDGE_ALIGN_FLOW_INSPECTION_UVW_MOVE_DONE_CHECK, _T("_eMASK_EDGE_ALIGN_FLOW_INSPECTION_UVW_MOVE_DONE_CHECK"));
			}
			break;

		case _eMASK_EDGE_ALIGN_FLOW_FINISH_GANTRY_Z3_WAIT_POS:
			Devs::m_GantryMotion.Move_GantryZ_All_Wait_Pos();
			Sleep(20); //!!

			SetStep(_eMASK_EDGE_ALIGN_FLOW_FINISH_GANTRY_Z3_WAIT_POS_CHECK, _T("_eMASK_EDGE_ALIGN_FLOW_FINISH_GANTRY_Z3_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);

			break;

		case _eMASK_EDGE_ALIGN_FLOW_FINISH_GANTRY_Z3_WAIT_POS_CHECK:
			if (Devs::m_GantryMotion.Is_GantryZ_All_Wait_Pos())
			{
				SetStep(_eMASK_EDGE_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS, _T("_eMASK_EDGE_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eMASK_EDGE_ALIGN_FLOW_ERROR, _T("_eMASK_EDGE_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMASK_EDGE_ALIGN_FLOW_FINISH_GANTRY_Z3_WAIT_POS_CHECK, _T("_eMASK_EDGE_ALIGN_FLOW_FINISH_GANTRY_Z3_WAIT_POS_CHECK"));
			}
			break;

		case _eMASK_EDGE_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS:
			Devs::m_GantryMotion.Move_Gantry_X_Wait_Pos();
			Sleep(20); //!!
			Devs::m_GantryMotion.Move_Gantry_Y_Wait_Pos();
			Sleep(20); //!!

			SetStep(_eMASK_EDGE_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK, _T("_eMASK_EDGE_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMASK_EDGE_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Wait_Pos() && Devs::m_GantryMotion.Is_Gantry_Y_Wait_Pos())
			{
				SetStep(_eMASK_EDGE_ALIGN_FLOW_DONE, _T("_eMASK_EDGE_ALIGN_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eMASK_EDGE_ALIGN_FLOW_ERROR, _T("_eMASK_EDGE_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMASK_EDGE_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK, _T("_eMASK_EDGE_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK"));
			}
			break;

		case _eMASK_EDGE_ALIGN_FLOW_ERROR:
			break;

		case _eMASK_EDGE_ALIGN_FLOW_DONE:
		{
			SharedInfo::nPrevFlowID = eEDGE_ALIGN_FLOW; //KJT 20210326

			m_bFlowDone = TRUE;

			SharedInfo::CalTactTime(_T("MASK_EDGE_ALIGN_FLOW"), m_timeStart); //KJT 20210329

			SetStep(_eMASK_EDGE_ALIGN_FLOW_IDLE, _T("_eMASK_EDGE_ALIGN_FLOW_IDLE"));
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

BOOL CMaskEdgeAlignFlow::GetXYTPos(double *dRefPosX, double *dRefPosY, double *dDiffPosX, double *dDiffPosY, double *ResultX, double *ResultY, double *ResultT)
{

	double dVel[3] = { 1., };
	double dAcc[3] = { 2., };
	double dDecel[3] = { 2., };

	double R;

	double dError;
#if 0
	double RefT[2], NewPositionT[2], DiffT[2], DiffPosition[3] = { 0, };
	for (int i = 0; i < 2; i++)
	{




		RefT[i] = atan((dRefPosX[i] / dRefPosY[i]));
		NewPositionT[i] = atan((dRefPosX[i] + dDiffPosX[i]) / (dRefPosY[i] + dDiffPosY[i]));
		DiffT[i] = NewPositionT[i] - RefT[i];
		DiffPosition[0] += dDiffPosX[i];
		DiffPosition[1] += dDiffPosY[i];
		DiffPosition[2] += DiffT[i];


	}
	*ResultX = DiffPosition[0] / 2;
	*ResultY = DiffPosition[1] / 2;
	*ResultT = DiffPosition[2] / 2 * (180. / PI);
	//*ResultX = -*ResultX;
	//*ResultY = -*ResultY;
	//*ResultT = -*ResultT;
#else
	double RefT, NewPositionT, DiffT[2], DiffPosition[3] = { 0, };
	RefT = atan2((dRefPosY[1] - dRefPosY[0]), (dRefPosX[1] - dRefPosX[0]));


	NewPositionT = atan2((dRefPosY[1] + dDiffPosY[1]) - (dRefPosY[0] + dDiffPosY[0])
		, (dRefPosX[1] + dDiffPosX[1]) - (dRefPosX[0] + dDiffPosX[0]));

	for (int i = 0; i < 2; i++)
	{


		DiffPosition[0] += dDiffPosX[i];
		DiffPosition[1] += dDiffPosY[i];



	}
	DiffPosition[2] = NewPositionT - RefT;
	*ResultX = DiffPosition[0] / 2;
	*ResultY = DiffPosition[1] / 2;
	*ResultT = DiffPosition[2] * (180. / PI);
#endif
	*ResultX = *ResultX * (-1);
	*ResultY = *ResultY * (-1);
	*ResultT = *ResultT * (-1);

	Total_Msg(_T("EdgeAlign Result X : %.5f, Y : %.5f, T : %.7f"), *ResultX, *ResultY, *ResultT);

#if 0
	R = sqrt(dRefPosX[0] * dRefPosX[0] + dRefPosY[1] * dRefPosY[1]);
	*dErrorX = fabs(*ResultX) + fabs(R * (*ResultT / (180. / PI) * 2));
	*dErrorY = fabs(*ResultY) + fabs(R * (*ResultT / (180. / PI) * 2));

#endif
	dError = sqrt(*ResultX  * *ResultX + *ResultY * *ResultY);
#if 1

#endif




	//Total_Msg(_T("MFA Align Error X : %.5f, Y : %.5f, E : %.5f"), *dErrorX, *dErrorY, dError);


	return TRUE;
}
double CMaskEdgeAlignFlow::GetAlignPos_X(int nAlignCount)
{
	double dPos = m_AlignPointValue[0][nAlignCount];
	return dPos;
}
double CMaskEdgeAlignFlow::GetAlignPos_Y(int nAlignCount)
{
	double dPos = m_AlignPointValue[1][nAlignCount];
	return dPos;
}

BOOL CMaskEdgeAlignFlow::FlowInterlock()
{
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