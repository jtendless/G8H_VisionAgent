#include "stdafx.h"
#include "MaskEdgeTenstionAlignFlow.h"
#include "Log/Logger.h"
#include "Vision/Devs.h"
#include "Data/ModelData.h"
#include "CamAreaModul.h"
#include "Data/SystemData.h"
#include "FmmLight1.h"
#include "VisionAgentDlg.h"

CMaskEdgeTenstionAlignFlow::CMaskEdgeTenstionAlignFlow()
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


CMaskEdgeTenstionAlignFlow::~CMaskEdgeTenstionAlignFlow()
{
}

BOOL CMaskEdgeTenstionAlignFlow::InitProcess()
{
	m_StateComplete = NULL;
	m_FlowFinish = TRUE;
	m_bTerminate = FALSE;
	m_bFlowDone = TRUE;

#pragma region //Step Group
	int nGroupIndex = 0;

	m_sGroupInfo[nGroupIndex].m_bProcessingFlag = FALSE;
	m_sGroupInfo[nGroupIndex].nStartStep = _eEDGE_TENSION_ALIGN_FLOW_START;
	m_sGroupInfo[nGroupIndex].nEndStep = _eEDGE_TENSION_ALIGN_FLOW_INTERLOCK;
	m_sGroupInfo[nGroupIndex].strGroupName.Format(_T("%d. Start"), nGroupIndex + 1);
	nGroupIndex++;

	m_sGroupInfo[nGroupIndex].m_bProcessingFlag = FALSE;
	m_sGroupInfo[nGroupIndex].nStartStep = _eEDGE_TENSION_ALIGN_FLOW_UNLOADER_READY;
	m_sGroupInfo[nGroupIndex].nEndStep = _eEDGE_TENSION_ALIGN_FLOW_GANTRY_ZX_READY_CHECK;
	m_sGroupInfo[nGroupIndex].strGroupName.Format(_T("%d. Other Axis Ready"), nGroupIndex + 1);
	nGroupIndex++;

	m_sGroupInfo[nGroupIndex].m_bProcessingFlag = FALSE;
	m_sGroupInfo[nGroupIndex].nStartStep = _eEDGE_TENSION_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST;
	m_sGroupInfo[nGroupIndex].nEndStep = _eEDGE_TENSION_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK;
	m_sGroupInfo[nGroupIndex].strGroupName.Format(_T("%d. Gantry XY Align Pos"), nGroupIndex + 1);
	nGroupIndex++;

	//m_sGroupInfo[nGroupIndex].m_bProcessingFlag = FALSE;
	//m_sGroupInfo[nGroupIndex].nStartStep = _eEDGE_TENSION_ALIGN_FLOW_GANTRY_Z1_INSPECTION_POS_1ST;
	//m_sGroupInfo[nGroupIndex].nEndStep = _eEDGE_TENSION_ALIGN_FLOW_GANTRY_Z1_INSPECTION_POS_1ST_CHECK;
	//m_sGroupInfo[nGroupIndex].strGroupName.Format(_T("%d. Gantry Z1 Inspection Pos"), nGroupIndex + 1);
	//nGroupIndex++;

	m_sGroupInfo[nGroupIndex].m_bProcessingFlag = FALSE;
	m_sGroupInfo[nGroupIndex].nStartStep = _eEDGE_TENSION_ALIGN_FLOW_AUTOFOCUS_CHECK;
	m_sGroupInfo[nGroupIndex].nEndStep = _eEDGE_TENSION_ALIGN_FLOW_GRAB_DONE_CHECK;
	m_sGroupInfo[nGroupIndex].strGroupName.Format(_T("%d. Autofocus And Image Grab"), nGroupIndex + 1);
	nGroupIndex++;

	m_sGroupInfo[nGroupIndex].m_bProcessingFlag = FALSE;
	m_sGroupInfo[nGroupIndex].nStartStep = _eEDGE_TENSION_ALIGN_FLOW_GRIPPER_Z_TENSTION_POS;
	m_sGroupInfo[nGroupIndex].nEndStep = _eEDGE_TENSION_ALIGN_FLOW_GRIPPER_Z_TENSTION_POS_CHECK;
	m_sGroupInfo[nGroupIndex].strGroupName.Format(_T("%d. Gripper Z Tension Pos"), nGroupIndex + 1);
	nGroupIndex++;

	m_sGroupInfo[nGroupIndex].m_bProcessingFlag = FALSE;
	m_sGroupInfo[nGroupIndex].nStartStep = _eEDGE_TENSION_ALIGN_FLOW_STRETCH_TENSTION_START;
	m_sGroupInfo[nGroupIndex].nEndStep = _eEDGE_TENSION_ALIGN_FLOW_STRETCH_TENSTION_DONE_CHECK;
	m_sGroupInfo[nGroupIndex].strGroupName.Format(_T("%d. Stretch Tension Start"), nGroupIndex + 1);
	nGroupIndex++;

	//m_sGroupInfo[nGroupIndex].m_bProcessingFlag = FALSE;
	//m_sGroupInfo[nGroupIndex].nStartStep = _eEDGE_TENSION_ALIGN_FLOW_PITCH_TENSTION_START;
	//m_sGroupInfo[nGroupIndex].nEndStep = _eEDGE_TENSION_ALIGN_FLOW_PITCH_TENSTION_DONE_CHECK;
	//m_sGroupInfo[nGroupIndex].strGroupName.Format(_T("%d. Pitch Tension Start"), nGroupIndex + 1);
	//nGroupIndex++;

	m_sGroupInfo[nGroupIndex].m_bProcessingFlag = FALSE;
	m_sGroupInfo[nGroupIndex].nStartStep = _eEDGE_TENSION_ALIGN_FLOW_GRIPPER_Z_CLAMP_POS;
	m_sGroupInfo[nGroupIndex].nEndStep = _eEDGE_TENSION_ALIGN_FLOW_GRIPPER_Z_CLAMP_POS_CHECK;
	m_sGroupInfo[nGroupIndex].strGroupName.Format(_T("%d. Gripper Z Clamp Pos"), nGroupIndex + 1);
	nGroupIndex++;

	//m_sGroupInfo[nGroupIndex].m_bProcessingFlag = FALSE;
	//m_sGroupInfo[nGroupIndex].nStartStep = _eEDGE_TENSION_ALIGN_FLOW_FINISH_GANTRY_Z1_WAIT_POS;
	//m_sGroupInfo[nGroupIndex].nEndStep = _eEDGE_TENSION_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK;
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
BOOL CMaskEdgeTenstionAlignFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eEDGE_TENSION_ALIGN_FLOW_IDLE);

	if (hHandle != NULL)
	{
		CloseHandle(hHandle);
		hHandle = NULL;
	}

	return TRUE;
}

BOOL CMaskEdgeTenstionAlignFlow::Start(int nStep)
{
	memset(Devs::m_GantryMotion.m_dTpX, 0, sizeof(Devs::m_GantryMotion.m_dTpX));
	memset(Devs::m_GantryMotion.m_dTpY, 0, sizeof(Devs::m_GantryMotion.m_dTpY));

	m_pReviewCoaxial = &CModelData::m_AlignPara.Info.nEdge4PAlignCoAxial;
	m_pReviewRing = &CModelData::m_AlignPara.Info.nEdge4PAlignRing;
	m_pReviewThreshold = &CModelData::m_AlignPara.Info.nEdge4PAlignThreshold;
	m_pReviewMarkFind = &CModelData::m_AlignPara.Info.nEdge4PAlignMarkType;

	m_bLaserFocusUseFlag = FALSE;
	m_bAutoFocusUseFlag = FALSE;

	switch (CModelData::m_PpaPara.Info.nPpaFocusType)
	{
	case eFocusType_Laser:
		m_bLaserFocusUseFlag = TRUE;
		m_bAutoFocusUseFlag = FALSE;
		break;

	case eFocusType_Image:
		m_bLaserFocusUseFlag = FALSE;
		m_bAutoFocusUseFlag = TRUE;
		break;

	case eFocusType_Both:
		m_bLaserFocusUseFlag = TRUE;
		m_bAutoFocusUseFlag = TRUE;
		break;
	}

	m_bFlowDone = FALSE;
	m_bStopBit = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(nStep, _T("_eEDGE_TENSION_ALIGN_FLOW_START"));
	return TRUE;
}
BOOL CMaskEdgeTenstionAlignFlow::Stop()
{
	m_bStopBit = TRUE;
	return TRUE;
}

UINT CMaskEdgeTenstionAlignFlow::ThreadFunction(LPVOID lpParam)
{
	CMaskEdgeTenstionAlignFlow* pFlow = NULL;

	pFlow = (CMaskEdgeTenstionAlignFlow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}

VOID CMaskEdgeTenstionAlignFlow::ThreadFunctionEntry(VOID)
{
	ERROR_INFO resinfo;
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

	double RefT;
	double NewPositionT;
	double DiffT;
	double dRandNum;
	
	SYSTEMTIME st;
	int nReF = 0;
	int nIndex = 0;
	CString strTemp = _T("");
	INT nOkCnt = 0;

	int nBackLightVal[BACKLIGHT_CH_COUNT] = { BACKLIGHT_OFF_VALUE, };

	while (m_FlowFinish)
	{
		WaitForSingleObject(hHandle, INFINITE);
		ResetEvent(hHandle);

		if (SharedInfo::bMachineStopFlag == TRUE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(_eEDGE_TENSION_ALIGN_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}

		switch (GetCurrentTotalStep())
		{
		case _eEDGE_TENSION_ALIGN_FLOW_IDLE:
		{
			break;
		}
		case _eEDGE_TENSION_ALIGN_FLOW_START:
		{
			m_timeStart = CTime::GetCurrentTime(); //KJT 20210329

#ifndef SIM_MODE
			if (CModelData::m_InspectionPara.Info.bMappingDataUse)
			{
				Devs::m_MappingProc.InitializeGlassMapping(eMAPPING_ID_10X);
				if (Devs::m_MappingProc.LoadGlassMappingFile(eMAPPING_ID_10X) == FALSE)
				{
					SetStep(_eEDGE_TENSION_ALIGN_FLOW_ERROR, _T("_eEDGE_TENSION_ALIGN_FLOW_ERROR"));
					break;
				}
			}
#endif
#if 0
#pragma region //Temp
			//LB
			m_AlignPointValue[0][0] = -405.13925;
			m_AlignPointValue[1][0] = -35.55;
			//LT
			m_AlignPointValue[0][1] = -405.13925;
			m_AlignPointValue[1][1] = 35.55;
			//RT
			m_AlignPointValue[0][2] = 405.13925;
			m_AlignPointValue[1][2] = 35.55;
			//RB
			m_AlignPointValue[0][3] = 405.13925;
			m_AlignPointValue[1][3] = -35.55;
#pragma endregion
#endif
			//LB
			m_AlignPointValue[0][0] = SharedInfo::GetReview10X_EdgeTensionAlignCellPosXY_LB().dPosX;
			m_AlignPointValue[1][0] = SharedInfo::GetReview10X_EdgeTensionAlignCellPosXY_LB().dPosY;
			//LT
			m_AlignPointValue[0][1] = SharedInfo::GetReview10X_EdgeTensionAlignCellPosXY_LT().dPosX;
			m_AlignPointValue[1][1] = SharedInfo::GetReview10X_EdgeTensionAlignCellPosXY_LT().dPosY;
			//RT
			m_AlignPointValue[0][2] = SharedInfo::GetReview10X_EdgeTensionAlignCellPosXY_RT().dPosX;
			m_AlignPointValue[1][2] = SharedInfo::GetReview10X_EdgeTensionAlignCellPosXY_RT().dPosY;
			//RB
			m_AlignPointValue[0][3] = SharedInfo::GetReview10X_EdgeTensionAlignCellPosXY_RB().dPosX;
			m_AlignPointValue[1][3] = SharedInfo::GetReview10X_EdgeTensionAlignCellPosXY_RB().dPosY;

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

			g_CommReview_Light.SetLight_Review(CModelData::m_AlignPara.Info.nEdge4PAlignCoAxial, CModelData::m_AlignPara.Info.nEdge4PAlignCoAxial);
			Sleep(30);
			SharedInfo::BackLightOn(CModelData::m_AlignPara.Info.nEdge4PAlignBacklight);

			SetStep(_eEDGE_TENSION_ALIGN_FLOW_INTERLOCK, _T("_eEDGE_TENSION_ALIGN_FLOW_INTERLOCK"));
			break;
		}
		case _eEDGE_TENSION_ALIGN_FLOW_ERROR:
			break;

		case _eEDGE_TENSION_ALIGN_FLOW_INTERLOCK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(_eEDGE_TENSION_ALIGN_FLOW_ERROR, _T("_eEDGE_TENSION_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetStep(_eEDGE_TENSION_ALIGN_FLOW_UNLOADER_READY, _T("_eEDGE_TENSION_ALIGN_FLOW_UNLOADER_READY"));
			}
			break;

#pragma region //Unloader Ready
		case _eEDGE_TENSION_ALIGN_FLOW_UNLOADER_READY:
			Devs::m_Ready_UnloaderFlow.Start();

			SetStep(_eEDGE_TENSION_ALIGN_FLOW_UNLOADER_READY_CHECK, _T("_eEDGE_TENSION_ALIGN_FLOW_UNLOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eEDGE_TENSION_ALIGN_FLOW_UNLOADER_READY_CHECK:
			if (Devs::m_Ready_UnloaderFlow.IsFlowDone())
			{
				SetStep(_eEDGE_TENSION_ALIGN_FLOW_GANTRY_ZX_READY, _T("_eEDGE_TENSION_ALIGN_FLOW_GANTRY_ZX_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eEDGE_TENSION_ALIGN_FLOW_UNLOADER_READY_CHECK : Time Out"), eEDGE_TENSION_ALIGN_FLOW + 0);
				SetStep(_eEDGE_TENSION_ALIGN_FLOW_ERROR, _T("_eEDGE_TENSION_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eEDGE_TENSION_ALIGN_FLOW_UNLOADER_READY_CHECK, _T("_eEDGE_TENSION_ALIGN_FLOW_UNLOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Gantry Z, X Ready
		case _eEDGE_TENSION_ALIGN_FLOW_GANTRY_ZX_READY:
			Devs::m_Ready_GantryZX_Flow.Start();

			SetStep(_eEDGE_TENSION_ALIGN_FLOW_GANTRY_ZX_READY_CHECK, _T("_eEDGE_TENSION_ALIGN_FLOW_GANTRY_ZX_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eEDGE_TENSION_ALIGN_FLOW_GANTRY_ZX_READY_CHECK:
			if (Devs::m_Ready_GantryZX_Flow.IsFlowDone())
			{
				SetStep(_eEDGE_TENSION_ALIGN_FLOW_LOADER_READY, _T("_eEDGE_TENSION_ALIGN_FLOW_LOADER_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eEDGE_TENSION_ALIGN_FLOW_GANTRY_ZX_READY_CHECK : Time Out"), eEDGE_TENSION_ALIGN_FLOW + 2);
				SetStep(_eEDGE_TENSION_ALIGN_FLOW_ERROR, _T("_eEDGE_TENSION_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eEDGE_TENSION_ALIGN_FLOW_GANTRY_ZX_READY_CHECK, _T("_eEDGE_TENSION_ALIGN_FLOW_GANTRY_ZX_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Loader Ready
		case _eEDGE_TENSION_ALIGN_FLOW_LOADER_READY:
			Devs::m_Ready_LoaderFlow.Start();

			SetStep(_eEDGE_TENSION_ALIGN_FLOW_LOADER_READY_CHECK, _T("_eEDGE_TENSION_ALIGN_FLOW_LOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eEDGE_TENSION_ALIGN_FLOW_LOADER_READY_CHECK:
			if (Devs::m_Ready_LoaderFlow.IsFlowDone())
			{
				//SetStep(_eEDGE_TENSION_ALIGN_FLOW_BOX_CAMERA_READY, _T("_eEDGE_TENSION_ALIGN_FLOW_BOX_CAMERA_READY"));
				SetStep(_eEDGE_TENSION_ALIGN_FLOW_PAPER_UNLOADER_ZXY_READY, _T("_eEDGE_TENSION_ALIGN_FLOW_PAPER_UNLOADER_ZXY_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eEDGE_TENSION_ALIGN_FLOW_LOADER_READY_CHECK : Time Out"), eEDGE_TENSION_ALIGN_FLOW + 1);
				SetStep(_eEDGE_TENSION_ALIGN_FLOW_ERROR, _T("_eEDGE_TENSION_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eEDGE_TENSION_ALIGN_FLOW_LOADER_READY_CHECK, _T("_eEDGE_TENSION_ALIGN_FLOW_LOADER_READY_CHECK"));
			}
			break;
#pragma endregion

//#pragma region //Box Camera Ready
//		case _eEDGE_TENSION_ALIGN_FLOW_BOX_CAMERA_READY:
//			Devs::m_BoxMotion.BoxAlignCameraYL_WaitPos();
//			Sleep(20);
//			Devs::m_BoxMotion.BoxAlignCameraYR_WaitPos();
//			Sleep(500); //!!
//
//			SetStep(_eEDGE_TENSION_ALIGN_FLOW_BOX_CAMERA_READY_CHECK, _T("_eEDGE_TENSION_ALIGN_FLOW_BOX_CAMERA_READY_CHECK"));
//			SetTimeOut(TIME_OUT_MOTION);
//			break;
//
//		case _eEDGE_TENSION_ALIGN_FLOW_BOX_CAMERA_READY_CHECK:
//			if (Devs::m_BoxMotion.Is_BoxAlignCameraYL_WaitPos() == TRUE && Devs::m_BoxMotion.Is_BoxAlignCameraYR_WaitPos() == TRUE)
//			{
//				SetStep(_eEDGE_TENSION_ALIGN_FLOW_GANTRY_ZX_READY, _T("_eEDGE_TENSION_ALIGN_FLOW_GANTRY_ZX_READY"));
//			}
//			else if (IsTimeOut())
//			{
//				SetStep(_eEDGE_TENSION_ALIGN_FLOW_ERROR, _T("_eEDGE_TENSION_ALIGN_FLOW_ERROR"));
//			}
//			else
//			{
//				SetCheckStep(_eEDGE_TENSION_ALIGN_FLOW_BOX_CAMERA_READY_CHECK, _T("_eEDGE_TENSION_ALIGN_FLOW_BOX_CAMERA_READY_CHECK"));
//			}
//			break;
//#pragma endregion

#pragma region //PaperUnloader Ready
		case _eEDGE_TENSION_ALIGN_FLOW_PAPER_UNLOADER_ZXY_READY:
			Devs::m_Ready_PaperUnloaderFlow.Start();

			SetStep(_eEDGE_TENSION_ALIGN_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK, _T("_eEDGE_TENSION_ALIGN_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eEDGE_TENSION_ALIGN_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK:
			if (Devs::m_Ready_PaperUnloaderFlow.IsFlowDone())
			{
				SetStep(_eEDGE_TENSION_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST, _T("_eEDGE_TENSION_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eEDGE_TENSION_ALIGN_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK : Time Out"), eBOX_ALIGN_FLOW + 1);
				SetStep(_eEDGE_TENSION_ALIGN_FLOW_ERROR, _T("_eEDGE_TENSION_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eEDGE_TENSION_ALIGN_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK, _T("_eEDGE_TENSION_ALIGN_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Gantry XYZ First Pos Move
		case _eEDGE_TENSION_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST:
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

			SetStep(_eEDGE_TENSION_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK, _T("_eEDGE_TENSION_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eEDGE_TENSION_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Pos(m_dTargetPosX) && Devs::m_GantryMotion.Is_Gantry_Y_Pos(m_dTargetPosY))
			{
				if (Devs::m_InspectionStageMotion.Is_BackLight_X_Pos(m_dTargetPosX))
					SetStep(_eEDGE_TENSION_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_1ST, _T("_eEDGE_TENSION_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_1ST"));
				else
					SetCheckStep(_eEDGE_TENSION_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK);
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eEDGE_TENSION_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK : Time Out"), eEDGE_TENSION_ALIGN_FLOW + 3);
				SetStep(_eEDGE_TENSION_ALIGN_FLOW_ERROR, _T("_eEDGE_TENSION_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eEDGE_TENSION_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK);
			}
			break;

		case _eEDGE_TENSION_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_1ST:
			Devs::m_GantryMotion.Move_GantryZ1_InspectionReview_Pos();
			Sleep(20); //!!

			SetStep(_eEDGE_TENSION_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_1ST_CHECK, _T("_eEDGE_TENSION_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_1ST_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eEDGE_TENSION_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_1ST_CHECK:
			if (Devs::m_GantryMotion.Is_GantryZ1_InspectionReview_Pos())
			{
				Sleep(500); //!!
				SetStep(_eEDGE_TENSION_ALIGN_FLOW_AUTOFOCUS_CHECK, _T("_eEDGE_TENSION_ALIGN_FLOW_AUTOFOCUS_CHECK"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eEDGE_TENSION_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_1ST_CHECK : Time Out"), eEDGE_TENSION_ALIGN_FLOW + 4);
				SetStep(_eEDGE_TENSION_ALIGN_FLOW_ERROR, _T("_eEDGE_TENSION_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eEDGE_TENSION_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_1ST_CHECK, _T("_eEDGE_TENSION_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_1ST_CHECK"));
			}
			break;
#pragma endregion

		case _eEDGE_TENSION_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_2ND:
			Devs::m_GantryMotion.Move_GantryZ1_InspectionReview_Pos();
			Sleep(20); //!!

			SetStep(_eEDGE_TENSION_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_2ND_CHECK, _T("_eEDGE_TENSION_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_2ND_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eEDGE_TENSION_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_2ND_CHECK:
			if (Devs::m_GantryMotion.Is_GantryZ1_InspectionReview_Pos())
			{
				Sleep(100); //!!
				SetStep(_eEDGE_TENSION_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND, _T("_eEDGE_TENSION_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eEDGE_TENSION_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_2ND_CHECK : Time Out"), eEDGE_TENSION_ALIGN_FLOW + 5);
				SetStep(_eEDGE_TENSION_ALIGN_FLOW_ERROR, _T("_eEDGE_TENSION_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eEDGE_TENSION_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_2ND_CHECK, _T("_eEDGE_TENSION_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_2ND_CHECK"));
			}
			break;

		case _eEDGE_TENSION_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND:
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

			SetStep(_eEDGE_TENSION_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK, _T("_eEDGE_TENSION_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eEDGE_TENSION_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Pos(m_dTargetPosX) && Devs::m_GantryMotion.Is_Gantry_Y_Pos(m_dTargetPosY))
			{
				if (Devs::m_InspectionStageMotion.Is_BackLight_X_Pos(m_dTargetPosX))
				{
					Sleep(500); //!!
					SetStep(_eEDGE_TENSION_ALIGN_FLOW_AUTOFOCUS_CHECK, _T("_eEDGE_TENSION_ALIGN_FLOW_AUTOFOCUS_CHECK"));
				}
				else
					SetCheckStep(_eEDGE_TENSION_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK, _T("_eEDGE_TENSION_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eEDGE_TENSION_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK : Time Out"), eEDGE_TENSION_ALIGN_FLOW + 6);
				SetStep(_eEDGE_TENSION_ALIGN_FLOW_ERROR, _T("_eEDGE_TENSION_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eEDGE_TENSION_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK, _T("_eEDGE_TENSION_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK"));
			}
			break;

		case _eEDGE_TENSION_ALIGN_FLOW_AUTOFOCUS_CHECK:
			if (CModelData::m_AlignPara.Info.nEdge4PAlignFocusType == eFocusType_Laser || CModelData::m_AlignPara.Info.nEdge4PAlignFocusType == eFocusType_Both)
				SetStep(_eEDGE_TENSION_ALIGN_FLOW_LASER_FOCUS_START, _T("_eEDGE_TENSION_ALIGN_FLOW_LASER_FOCUS_START"));
			else if (CModelData::m_AlignPara.Info.nEdge4PAlignFocusType == eFocusType_Image)
				SetStep(_eEDGE_TENSION_ALIGN_FLOW_IMAGE_FOCUS_START, _T("_eEDGE_TENSION_ALIGN_FLOW_IMAGE_FOCUS_START"));
			else
				SetStep(_eEDGE_TENSION_ALIGN_FLOW_GRAB_START, _T("_eEDGE_TENSION_ALIGN_FLOW_GRAB_START"));
			break;

		case _eEDGE_TENSION_ALIGN_FLOW_LASER_FOCUS_START:
			Devs::m_GantryMotion.LaserFocusMove();

			SetStep(_eEDGE_TENSION_ALIGN_FLOW_LASER_FOCUS_CHECK, _T("_eEDGE_TENSION_ALIGN_FLOW_LASER_FOCUS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eEDGE_TENSION_ALIGN_FLOW_LASER_FOCUS_CHECK:
			if (Devs::m_GantryMotion.LaserFocusMoveCheck())
			{
				Sleep(500); //!!	//KJT 20210321

				if (CModelData::m_AlignPara.Info.nEdge4PAlignFocusType == eFocusType_Both)
					SetStep(_eEDGE_TENSION_ALIGN_FLOW_IMAGE_FOCUS_START, _T("_eEDGE_TENSION_ALIGN_FLOW_IMAGE_FOCUS_START"));
				else
					SetStep(_eEDGE_TENSION_ALIGN_FLOW_GRAB_START, _T("_eEDGE_TENSION_ALIGN_FLOW_GRAB_START"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eEDGE_TENSION_ALIGN_FLOW_LASER_FOCUS_CHECK : Time Out"), eEDGE_TENSION_ALIGN_FLOW + 7);
				SetStep(_eEDGE_TENSION_ALIGN_FLOW_ERROR, _T("_eEDGE_TENSION_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eEDGE_TENSION_ALIGN_FLOW_LASER_FOCUS_CHECK, _T("_eEDGE_TENSION_ALIGN_FLOW_LASER_FOCUS_CHECK"));
			}
			break;

		case _eEDGE_TENSION_ALIGN_FLOW_IMAGE_FOCUS_START:
#ifndef SIM_MODE
			g_pReview10x->m_bAfEnd = FALSE;
			g_pReview10x->AutofoucsRun();
#endif

			SetStep(_eEDGE_TENSION_ALIGN_FLOW_IMAGE_FOCUS_CHECK, _T("_eEDGE_TENSION_ALIGN_FLOW_IMAGE_FOCUS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eEDGE_TENSION_ALIGN_FLOW_IMAGE_FOCUS_CHECK:
#ifndef SIM_MODE
			if (g_pReview10x->m_bAfEnd == TRUE)
			{
				Sleep(IMAGE_FOCUS_DELAY);
				SetStep(_eEDGE_TENSION_ALIGN_FLOW_GRAB_START, _T("_eEDGE_TENSION_ALIGN_FLOW_GRAB_START"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eEDGE_TENSION_ALIGN_FLOW_IMAGE_FOCUS_CHECK : Time Out"), eEDGE_TENSION_ALIGN_FLOW + 8);
				SetStep(_eEDGE_TENSION_ALIGN_FLOW_ERROR, _T("_eEDGE_TENSION_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eEDGE_TENSION_ALIGN_FLOW_IMAGE_FOCUS_CHECK, _T("_eEDGE_TENSION_ALIGN_FLOW_IMAGE_FOCUS_CHECK"));
			}
#else
			Sleep(IMAGE_FOCUS_DELAY);
			SetStep(_eEDGE_TENSION_ALIGN_FLOW_GRAB_START, _T("_eEDGE_TENSION_ALIGN_FLOW_GRAB_START"));
#endif
			break;

		case _eEDGE_TENSION_ALIGN_FLOW_GRAB_START:
			SharedInfo::bMainEdgeAlignGrabDone = FALSE;

			nRtn = Devs::m_GantryMotion.FindBlob_Edge4PAlign_Review10X(&m_AlignVisionResultValue[0][m_nAlignPoint], &m_AlignVisionResultValue[1][m_nAlignPoint]);

			if (nRtn == FALSE)
			{
				SetStep(_eEDGE_TENSION_ALIGN_FLOW_ERROR, _T("_eEDGE_TENSION_ALIGN_FLOW_ERROR"));
				break;
			}

			SharedInfo::dMainEdge4PAlignVisionResultValue[0][m_nAlignPoint] = m_AlignVisionResultValue[0][m_nAlignPoint];
			SharedInfo::dMainEdge4PAlignVisionResultValue[1][m_nAlignPoint] = m_AlignVisionResultValue[1][m_nAlignPoint];

			Str.Format(_T("AlignCnt:%d Diff X:%.5f, Y:%.5f"), m_nAlignPoint, m_AlignVisionResultValue[0][m_nAlignPoint], m_AlignVisionResultValue[1][m_nAlignPoint]);
			Total_Msg(Str);

			SetStep(_eEDGE_TENSION_ALIGN_FLOW_GRAB_DONE_CHECK, _T("_eEDGE_TENSION_ALIGN_FLOW_GRAB_DONE_CHECK"));
			break;

		case _eEDGE_TENSION_ALIGN_FLOW_GRAB_DONE_CHECK:
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
				Devs::m_InspectionStageMotion.GetUVWPos(m_AlignPointValue[0], m_AlignPointValue[1], m_AlignVisionResultValue[0], m_AlignVisionResultValue[1], &m_dDiffPos[0], &m_dDiffPos[1], &m_dDiffPos[2], TRUE);

				Str.Format(_T("Uvw Diff Pos X:%.5f, Y:%.5f, T:%.5f"), m_dDiffPos[0], m_dDiffPos[1], m_dDiffPos[2]);
				Total_Msg(Str);

				
				if (fabs(m_dDiffPos[0]) <= (float)CModelData::m_AlignPara.Info.dEdge4PAlignTargetX &&
					fabs(m_dDiffPos[1]) <= (float)CModelData::m_AlignPara.Info.dEdge4PAlignTargetY &&
					(fabs(m_dDiffPos[2]) < 0.001 || (360 - fabs(m_dDiffPos[2])) < 0.001)) //KJT 20210319
				{
					SharedInfo::UpdateSwAlignData(m_AlignPointValue, m_AlignVisionResultValue); //SWMapping

					SetStep(_eEDGE_TENSION_ALIGN_FLOW_FINISH_GANTRY_Z3_WAIT_POS, _T("_eEDGE_TENSION_ALIGN_FLOW_FINISH_GANTRY_Z3_WAIT_POS"));
				}
				else
				{
					SetStep(_eEDGE_TENSION_ALIGN_FLOW_GRIPPER_Z_TENSTION_POS, _T("_eEDGE_TENSION_ALIGN_FLOW_GRIPPER_Z_TENSTION_POS"));
				}
			}
			else
			{
				m_nAlignPoint++;
				Sleep(1000);
				SetStep(_eEDGE_TENSION_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_2ND, _T("_eEDGE_TENSION_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_2ND"));
			}
			break;

		case _eEDGE_TENSION_ALIGN_FLOW_GRIPPER_Z_TENSTION_POS:
			if (SharedInfo::bMainEdgeAlignGrabDone == FALSE)
			{
				Total_Msg(_T("Grab Done False !!"));
				SetStep(_eEDGE_TENSION_ALIGN_FLOW_ERROR, _T("_eEDGE_TENSION_ALIGN_FLOW_ERROR"));
				break;
			}

			Devs::m_GripperZMotion.Move_GripperLeftZ_TensionPos();
			Sleep(10);
			//Devs::m_GripperZMotion.Move_GripperRightZ_TensionPos();

			SetStep(_eEDGE_TENSION_ALIGN_FLOW_GRIPPER_Z_TENSTION_POS_CHECK, _T("_eEDGE_TENSION_ALIGN_FLOW_GRIPPER_Z_TENSTION_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eEDGE_TENSION_ALIGN_FLOW_GRIPPER_Z_TENSTION_POS_CHECK:
			if (Devs::m_GripperZMotion.Is_GripperLeftZ_TensionPos() && Devs::m_GripperZMotion.Is_GripperRightZ_TensionPos())
			{
				SetStep(_eEDGE_TENSION_ALIGN_FLOW_STRETCH_TENSTION_START, _T("_eEDGE_TENSION_ALIGN_FLOW_STRETCH_TENSTION_START"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eEDGE_TENSION_ALIGN_FLOW_GRIPPER_Z_TENSTION_POS_CHECK : Time Out"), eEDGE_TENSION_ALIGN_FLOW + 9);
				SetStep(_eEDGE_TENSION_ALIGN_FLOW_ERROR, _T("_eEDGE_TENSION_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eEDGE_TENSION_ALIGN_FLOW_GRIPPER_Z_TENSTION_POS_CHECK, _T("_eEDGE_TENSION_ALIGN_FLOW_GRIPPER_Z_TENSTION_POS_CHECK"));
			}
			break;

		case _eEDGE_TENSION_ALIGN_FLOW_STRETCH_TENSTION_START:
			if (SharedInfo::bMainEdgeAlignGrabDone == FALSE)
			{
				Total_Msg(_T("Grab Done False !!"));
				SetStep(_eEDGE_TENSION_ALIGN_FLOW_ERROR, _T("_eEDGE_TENSION_ALIGN_FLOW_ERROR"));
				break;
			}

			Devs::m_StretchMotion.Gripper4PAlignTensionStretchMoveStart(m_AlignVisionResultValue);

			SetCheckStep(_eEDGE_TENSION_ALIGN_FLOW_STRETCH_TENSTION_DONE_CHECK, _T("_eEDGE_TENSION_ALIGN_FLOW_STRETCH_TENSTION_DONE_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eEDGE_TENSION_ALIGN_FLOW_STRETCH_TENSTION_DONE_CHECK:
			if (Devs::m_StretchMotion.Gripper4PAlignTensionStretchMoveDoneCheck())
			{
				Sleep(1000); //!!
				//SetCheckStep(_eEDGE_TENSION_ALIGN_FLOW_PITCH_TENSTION_START, _T("_eEDGE_TENSION_ALIGN_FLOW_PITCH_TENSTION_START"));
				SetCheckStep(_eEDGE_TENSION_ALIGN_FLOW_GRIPPER_Z_CLAMP_POS, _T("_eEDGE_TENSION_ALIGN_FLOW_GRIPPER_Z_CLAMP_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eEDGE_TENSION_ALIGN_FLOW_STRETCH_TENSTION_DONE_CHECK : Time Out"), eEDGE_TENSION_ALIGN_FLOW + 10);
				SetStep(_eEDGE_TENSION_ALIGN_FLOW_ERROR, _T("_eEDGE_TENSION_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eEDGE_TENSION_ALIGN_FLOW_STRETCH_TENSTION_DONE_CHECK, _T("_eEDGE_TENSION_ALIGN_FLOW_STRETCH_TENSTION_DONE_CHECK"));
			}
			break;

		//case _eEDGE_TENSION_ALIGN_FLOW_PITCH_TENSTION_START:
			//if (SharedInfo::bMainEdgeAlignGrabDone == FALSE)
			//{
			//	Total_Msg(_T("Grab Done False !!"));
			//	SetStep(_eEDGE_TENSION_ALIGN_FLOW_ERROR, _T("_eEDGE_TENSION_ALIGN_FLOW_ERROR"));
			//	break;
			//}

			//Devs::m_PitchMotion.Gripper4PAlignTensionPitchMoveStart(m_AlignVisionResultValue);
			//SharedInfo::bMainEdgeAlignGrabDone = FALSE;

			//SetCheckStep(_eEDGE_TENSION_ALIGN_FLOW_PITCH_TENSTION_DONE_CHECK, _T("_eEDGE_TENSION_ALIGN_FLOW_PITCH_TENSTION_DONE_CHECK"));
			//SetTimeOut(TIME_OUT_MOTION);
			//break;

		//case _eEDGE_TENSION_ALIGN_FLOW_PITCH_TENSTION_DONE_CHECK:
			//if (Devs::m_PitchMotion.Gripper4PAlignTensionPitchMoveDoneCheck())
			//{
			//	Sleep(1000); //!!
			//	SetCheckStep(_eEDGE_TENSION_ALIGN_FLOW_GRIPPER_Z_CLAMP_POS, _T("_eEDGE_TENSION_ALIGN_FLOW_GRIPPER_Z_CLAMP_POS"));
			//}
			//else if (IsTimeOut())
			//{
			//	SetStep(_eEDGE_TENSION_ALIGN_FLOW_ERROR, _T("_eEDGE_TENSION_ALIGN_FLOW_ERROR"));
			//}
			//else
			//{
			//	SetCheckStep(_eEDGE_TENSION_ALIGN_FLOW_PITCH_TENSTION_DONE_CHECK, _T("_eEDGE_TENSION_ALIGN_FLOW_PITCH_TENSTION_DONE_CHECK"));
			//}
			//break;

		case _eEDGE_TENSION_ALIGN_FLOW_GRIPPER_Z_CLAMP_POS:
			Devs::m_GripperZMotion.Move_GripperLeftZ_ClampPos();
			Sleep(10);
			//Devs::m_GripperZMotion.Move_GripperRightZ_ClampPos();

			SetStep(_eEDGE_TENSION_ALIGN_FLOW_GRIPPER_Z_CLAMP_POS_CHECK, _T("_eEDGE_TENSION_ALIGN_FLOW_GRIPPER_Z_CLAMP_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eEDGE_TENSION_ALIGN_FLOW_GRIPPER_Z_CLAMP_POS_CHECK:
			if (Devs::m_GripperZMotion.Is_GripperLeftZ_ClampPos() && Devs::m_GripperZMotion.Is_GripperRightZ_ClampPos())
			{
				SetStep(_eEDGE_TENSION_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_2ND, _T("_eEDGE_TENSION_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_2ND"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eEDGE_TENSION_ALIGN_FLOW_GRIPPER_Z_CLAMP_POS_CHECK : Time Out"), eEDGE_TENSION_ALIGN_FLOW + 11);
				SetStep(_eEDGE_TENSION_ALIGN_FLOW_ERROR, _T("_eEDGE_TENSION_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eEDGE_TENSION_ALIGN_FLOW_GRIPPER_Z_CLAMP_POS_CHECK, _T("_eEDGE_TENSION_ALIGN_FLOW_GRIPPER_Z_CLAMP_POS_CHECK"));
			}
			break;

#pragma endregion
		case _eEDGE_TENSION_ALIGN_FLOW_FINISH_GANTRY_Z3_WAIT_POS:
			Devs::m_GantryMotion.Move_GantryZ_All_Wait_Pos();
			Sleep(20); //!!

			SetStep(_eEDGE_TENSION_ALIGN_FLOW_FINISH_GANTRY_Z3_WAIT_POS_CHECK, _T("_eEDGE_TENSION_ALIGN_FLOW_FINISH_GANTRY_Z3_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);

			break;

		case _eEDGE_TENSION_ALIGN_FLOW_FINISH_GANTRY_Z3_WAIT_POS_CHECK:
			if (Devs::m_GantryMotion.Is_GantryZ_All_Wait_Pos())
			{
				SetStep(_eEDGE_TENSION_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS, _T("_eEDGE_TENSION_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eEDGE_TENSION_ALIGN_FLOW_FINISH_GANTRY_Z3_WAIT_POS_CHECK : Time Out"), eEDGE_TENSION_ALIGN_FLOW + 12);
				SetStep(_eEDGE_TENSION_ALIGN_FLOW_ERROR, _T("_eEDGE_TENSION_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eEDGE_TENSION_ALIGN_FLOW_FINISH_GANTRY_Z3_WAIT_POS_CHECK, _T("_eEDGE_TENSION_ALIGN_FLOW_FINISH_GANTRY_Z3_WAIT_POS_CHECK"));
			}
			break;

		case _eEDGE_TENSION_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS:
			Devs::m_GantryMotion.Move_Gantry_X_Wait_Pos();
			Sleep(20); //!!
			Devs::m_GantryMotion.Move_Gantry_Y_Wait_Pos();
			Sleep(20); //!!

			SetStep(_eEDGE_TENSION_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK, _T("_eEDGE_TENSION_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eEDGE_TENSION_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Wait_Pos() && Devs::m_GantryMotion.Is_Gantry_Y_Wait_Pos())
			{
				SetStep(_eEDGE_TENSION_ALIGN_FLOW_DONE, _T("_eEDGE_TENSION_ALIGN_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eEDGE_TENSION_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK : Time Out"), eEDGE_TENSION_ALIGN_FLOW + 13);
				SetStep(_eEDGE_TENSION_ALIGN_FLOW_ERROR, _T("_eEDGE_TENSION_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eEDGE_TENSION_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK);
			}
			break;

		case _eEDGE_TENSION_ALIGN_FLOW_DONE:
		{
			m_bFlowDone = TRUE;

			SharedInfo::CalTactTime(_T("EDGE_TENSION_ALIGN_FLOW"), m_timeStart); //KJT 20210329

			SetStep(_eEDGE_TENSION_ALIGN_FLOW_IDLE, _T("_eEDGE_TENSION_ALIGN_FLOW_IDLE"));
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

double CMaskEdgeTenstionAlignFlow::GetAlignPos_X(int nAlignCount)
{
	double dPos = m_AlignPointValue[0][nAlignCount];
	return dPos;
}
double CMaskEdgeTenstionAlignFlow::GetAlignPos_Y(int nAlignCount)
{
	double dPos = m_AlignPointValue[1][nAlignCount];
	return dPos;
}

BOOL CMaskEdgeTenstionAlignFlow::FlowInterlock()
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

	//if (Devs::m_ClampMotion.Is_ClampOn_Active() != TRUE)
	//{
	//	Total_Msg(_T("Check Acitve Clamp On !!!"));
	//	return FALSE;
	//}

	return TRUE;
}