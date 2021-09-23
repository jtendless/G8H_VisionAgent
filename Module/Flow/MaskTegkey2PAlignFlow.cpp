#include "stdafx.h"
#include "MaskTegkey2PAlignFlow.h"
#include "Log/Logger.h"
#include "Vision/Devs.h"
#include "Data/ModelData.h"
#include "CamAreaModul.h"
#include "Data/SystemData.h"
#include "FmmLight1.h"

CMaskTegkey2PAlignFlow::CMaskTegkey2PAlignFlow()
{
	m_dDiffPos[0] = 0.;
	m_dDiffPos[1] = 0.;
	m_dDiffPos[2] = 0.;

	m_dTarget[0] = 0.;
	m_dTarget[1] = 0.;
	m_dTarget[2] = 0.;

	m_nAlignPoint = 0;
	m_bDirReverse = FALSE;

	m_AlignPointValue[0][0] = 0.0;
	m_AlignPointValue[1][0] = 0.0;
	m_AlignPointValue[0][1] = 0.0;
	m_AlignPointValue[1][1] = 0.0;

	m_AlignVisionResultValue[0][0] = 0.0;
	m_AlignVisionResultValue[1][0] = 0.0;
	m_AlignVisionResultValue[0][1] = 0.0;
	m_AlignVisionResultValue[1][1] = 0.0;
}


CMaskTegkey2PAlignFlow::~CMaskTegkey2PAlignFlow()
{
}

BOOL CMaskTegkey2PAlignFlow::InitProcess()
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
#ifndef SIM_MODE
	pMappingProc = &Devs::m_MappingProc;
#endif
	return TRUE;
}

BOOL CMaskTegkey2PAlignFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_IDLE);

	if (hHandle != NULL)
	{
		CloseHandle(hHandle);
		hHandle = NULL;
	}

	return TRUE;
}

BOOL CMaskTegkey2PAlignFlow::Start(int nStep)
{
	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(nStep, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_START"));
	return TRUE;
}

BOOL CMaskTegkey2PAlignFlow::Stop()
{
	m_bStopBit = TRUE;
	return TRUE;
}

UINT CMaskTegkey2PAlignFlow::ThreadFunction(LPVOID lpParam)
{
	CMaskTegkey2PAlignFlow* pFlow = NULL;

	pFlow = (CMaskTegkey2PAlignFlow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}

VOID CMaskTegkey2PAlignFlow::ThreadFunctionEntry(VOID)
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

	int nBackLightVal[BACKLIGHT_CH_COUNT] = { BACKLIGHT_OFF_VALUE, };

	while (m_FlowFinish)
	{
		WaitForSingleObject(hHandle, INFINITE);
		ResetEvent(hHandle);

		if (SharedInfo::bMachineStopFlag == TRUE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}

		switch (GetCurrentTotalStep())
		{
		case _eMASK_TEGKEY_2P_ALIGN_FLOW_IDLE:
		{
			break;
		}
		case _eMASK_TEGKEY_2P_ALIGN_FLOW_START:
		{
			m_timeStart = CTime::GetCurrentTime(); //KJT 20210329

#ifndef SIM_MODE
			if (CModelData::m_InspectionPara.Info.bMappingDataUse)
			{
				Devs::m_MappingProc.InitializeGlassMapping(eMAPPING_ID_10X);
				if (Devs::m_MappingProc.LoadGlassMappingFile(eMAPPING_ID_10X) == FALSE)
				{
					SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_ERROR, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_ERROR"));
					break;
				}
			}
#endif

			//KJT 20210225 Temp. Tegkey 2Point Align
			m_AlignPointValue[0][0] = CModelData::m_MaterialPara.Info.dTegkey_LT_X * STICK_FLIP_XY;
			m_AlignPointValue[1][0] = CModelData::m_MaterialPara.Info.dTegkey_LT_Y * STICK_FLIP_XY;
			m_AlignPointValue[0][1] = CModelData::m_MaterialPara.Info.dTegkey_RT_X * STICK_FLIP_XY;
			m_AlignPointValue[1][1] = CModelData::m_MaterialPara.Info.dTegkey_RT_Y * STICK_FLIP_XY;

			/////////////
			SharedInfo::nGantryZ1View = eViewReview10X;

			m_nAlignPoint = 0;
			m_bDirReverse = FALSE;

			m_AlignVisionResultValue[0][0] = 0.0;
			m_AlignVisionResultValue[1][0] = 0.0;
			m_AlignVisionResultValue[0][1] = 0.0;
			m_AlignVisionResultValue[1][1] = 0.0;

			SharedInfo::dTegkey2PAlignVisionResultValue[0][0] = m_AlignVisionResultValue[0][0];
			SharedInfo::dTegkey2PAlignVisionResultValue[1][0] = m_AlignVisionResultValue[1][0];
			SharedInfo::dTegkey2PAlignVisionResultValue[0][1] = m_AlignVisionResultValue[0][1];
			SharedInfo::dTegkey2PAlignVisionResultValue[1][1] = m_AlignVisionResultValue[1][1];
			SharedInfo::nTegkey2PAlignCurCount = 0;

			SharedInfo::LightAllOff();
			for (int i = 0; i < BACKLIGHT_CH_COUNT; i++)
				nBackLightVal[i] = CModelData::m_AlignPara.Info.nTegkeyAlignBacklight;

			Sleep(500);
			//g_CommLight_8ch.SetLight_Review_Coaxial(CModelData::m_AlignPara.Info.nTegkeyAlignCoAxial);
			Sleep(30);
			//g_CommLight_12ch.SetLight_Review_Ring(CModelData::m_AlignPara.Info.nTegkeyAlignRing);
			Sleep(30);
			//g_CommMLCLedLight.BackLightOn(nBackLightVal);
			Sleep(500);

			Devs::m_MappingProc.ReleaseSWMapping(eMAPPING_ID_10X); //!! KJT 20200913
			Devs::m_MappingProc.ReleaseXYTAlignData(eMAPPING_ID_10X); //!! KJT 20200913

			SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_INTERLOCK, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_INTERLOCK"));
			break;
		}
		case _eMASK_TEGKEY_2P_ALIGN_FLOW_INTERLOCK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_ERROR, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_ERROR"));
			}
			else
			{
				if (SharedInfo::MachineState.bAutoRunFlag == TRUE && SharedInfo::nPrevFlowID == eMAIN_ALIGN_FLOW) //KJT 20210326
					SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST"));
				else
					SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_UNLOADER_READY, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_UNLOADER_READY"));
			}
			break;

#pragma region //Unloader Ready
		case _eMASK_TEGKEY_2P_ALIGN_FLOW_UNLOADER_READY:
			Devs::m_Ready_UnloaderFlow.Start();

			SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_UNLOADER_READY_CHECK, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_UNLOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMASK_TEGKEY_2P_ALIGN_FLOW_UNLOADER_READY_CHECK:
			if (Devs::m_Ready_UnloaderFlow.IsFlowDone())
			{
				SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_LOADER_READY, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_LOADER_READY"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_ERROR, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_UNLOADER_READY_CHECK, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_UNLOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Loader Ready
		case _eMASK_TEGKEY_2P_ALIGN_FLOW_LOADER_READY:
			Devs::m_Ready_LoaderFlow.Start();

			SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_LOADER_READY_CHECK, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_LOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMASK_TEGKEY_2P_ALIGN_FLOW_LOADER_READY_CHECK:
			if (Devs::m_Ready_LoaderFlow.IsFlowDone())
			{
				SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_BOX_CAMERA_READY, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_BOX_CAMERA_READY"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_ERROR, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_LOADER_READY_CHECK, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_LOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Box Camera Ready
		case _eMASK_TEGKEY_2P_ALIGN_FLOW_BOX_CAMERA_READY:
			Devs::m_BoxMotion.BoxAlignCameraYL_WaitPos();
			Sleep(20);
			Devs::m_BoxMotion.BoxAlignCameraYR_WaitPos();
			Sleep(500); //!!

			SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_BOX_CAMERA_READY_CHECK, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_BOX_CAMERA_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMASK_TEGKEY_2P_ALIGN_FLOW_BOX_CAMERA_READY_CHECK:
			if (Devs::m_BoxMotion.Is_BoxAlignCameraYL_WaitPos() == TRUE && Devs::m_BoxMotion.Is_BoxAlignCameraYR_WaitPos() == TRUE)
			{
				SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_GANTRY_ZX_READY, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_GANTRY_ZX_READY"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_ERROR, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_BOX_CAMERA_READY_CHECK, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_BOX_CAMERA_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Gantry Z, X Ready
		case _eMASK_TEGKEY_2P_ALIGN_FLOW_GANTRY_ZX_READY:
			Devs::m_Ready_GantryZX_Flow.Start();

			SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_GANTRY_ZX_READY_CHECK, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_GANTRY_ZX_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMASK_TEGKEY_2P_ALIGN_FLOW_GANTRY_ZX_READY_CHECK:
			if (Devs::m_Ready_GantryZX_Flow.IsFlowDone())
			{
				SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_ERROR, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_GANTRY_ZX_READY_CHECK, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_GANTRY_ZX_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Gantry XYZ First Pos Move
		case _eMASK_TEGKEY_2P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST:
			m_dTargetPosX = dPosX = GetAlignPos_X(m_nAlignPoint);
			m_dTargetPosY = dPosY = GetAlignPos_Y(m_nAlignPoint);
#ifndef SIM_MODE
			if (CModelData::m_InspectionPara.Info.bMappingDataUse)
			{
				pMappingProc->GetGlassMapping_CalibPosXY(eMAPPING_ID_10X, &m_dTargetPosX, &m_dTargetPosY);
				Str.Format(_T("Mapping Data X:%10.5f, Y:%10.5f => X:%10.5f, Y:%10.5f"), dPosX, dPosY, m_dTargetPosX, m_dTargetPosY);
				Total_Msg(Str);
			}
#endif

			Devs::m_GantryMotion.Move_Gantry_X_Pos(m_dTargetPosX, TRUE);
			Sleep(20); //!!
			Devs::m_GantryMotion.Move_Gantry_Y_Pos(m_dTargetPosY);
			Sleep(20); //!!

			SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMASK_TEGKEY_2P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Pos(m_dTargetPosX) && Devs::m_GantryMotion.Is_Gantry_Y_Pos(m_dTargetPosY))
			{
				Sleep(500); //!!

				SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_GANTRY_Z1_INSPECTION_POS_1ST, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_GANTRY_Z1_INSPECTION_POS_1ST"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_ERROR, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK"));
			}
			break;

		case _eMASK_TEGKEY_2P_ALIGN_FLOW_GANTRY_Z1_INSPECTION_POS_1ST:
			//Devs::m_GantryMotion.Move_GantryZ1_InspectionReview_Pos();
			Sleep(20); //!!

			SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_GANTRY_Z1_INSPECTION_POS_1ST_CHECK, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_GANTRY_Z1_INSPECTION_POS_1ST_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMASK_TEGKEY_2P_ALIGN_FLOW_GANTRY_Z1_INSPECTION_POS_1ST_CHECK:
			//if (Devs::m_GantryMotion.Is_GantryZ1_InspectionReview_Pos())
			//{
			//	Sleep(500); //!!
			//	SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_AUTOFOCUS_CHECK, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_AUTOFOCUS_CHECK"));
			//}
			//else if (IsTimeOut())
			//{
			//	SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_ERROR, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_ERROR"));
			//}
			//else
			//{
			//	SetCheckStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_GANTRY_Z1_INSPECTION_POS_1ST_CHECK, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_GANTRY_Z1_INSPECTION_POS_1ST_CHECK"));
			//}
			break;
#pragma endregion

		case _eMASK_TEGKEY_2P_ALIGN_FLOW_GANTRY_Z1_INSPECTION_POS_2ND:
			//Devs::m_GantryMotion.Move_GantryZ1_InspectionReview_Pos();
			Sleep(20); //!!

			SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_GANTRY_Z1_INSPECTION_POS_2ND_CHECK, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_GANTRY_Z1_INSPECTION_POS_2ND_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMASK_TEGKEY_2P_ALIGN_FLOW_GANTRY_Z1_INSPECTION_POS_2ND_CHECK:
			//if (Devs::m_GantryMotion.Is_GantryZ1_InspectionReview_Pos())
			//{
			//	Sleep(100); //!!
			//	SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND"));
			//}
			//else if (IsTimeOut())
			//{
			//	SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_ERROR, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_ERROR"));
			//}
			//else
			//{
			//	SetCheckStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_GANTRY_Z1_INSPECTION_POS_2ND_CHECK, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_GANTRY_Z1_INSPECTION_POS_2ND_CHECK"));
			//}
			break;

		case _eMASK_TEGKEY_2P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND:
			m_dTargetPosX = dPosX = GetAlignPos_X(m_nAlignPoint);
			m_dTargetPosY = dPosY = GetAlignPos_Y(m_nAlignPoint);
#ifndef SIM_MODE
			if (CModelData::m_InspectionPara.Info.bMappingDataUse)
			{
				pMappingProc->GetGlassMapping_CalibPosXY(eMAPPING_ID_10X, &m_dTargetPosX, &m_dTargetPosY);
				Str.Format(_T("Mapping Data X:%10.5f, Y:%10.5f => X:%10.5f, Y:%10.5f"), dPosX, dPosY, m_dTargetPosX, m_dTargetPosY);
				Total_Msg(Str);
			}
#endif

			Devs::m_GantryMotion.Move_Gantry_X_Pos(m_dTargetPosX, TRUE);
			Sleep(20); //!!
			Devs::m_GantryMotion.Move_Gantry_Y_Pos(m_dTargetPosY);
			Sleep(20); //!!

			SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMASK_TEGKEY_2P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Pos(m_dTargetPosX) && Devs::m_GantryMotion.Is_Gantry_Y_Pos(m_dTargetPosY))
			{
				Sleep(500); //!!
				SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_AUTOFOCUS_CHECK, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_AUTOFOCUS_CHECK"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_ERROR, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK"));
			}
			break;

		case _eMASK_TEGKEY_2P_ALIGN_FLOW_AUTOFOCUS_CHECK:
			if (CModelData::m_AlignPara.Info.nMain2PAlignFocusType == eFocusType_Laser || CModelData::m_AlignPara.Info.nMain2PAlignFocusType == eFocusType_Both)
				SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_LASER_FOCUS_START, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_LASER_FOCUS_START"));
			else if (CModelData::m_AlignPara.Info.nMain2PAlignFocusType == eFocusType_Image)
				SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_IMAGE_FOCUS_START, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_IMAGE_FOCUS_START"));
			else
				SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_GRAB_START, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_GRAB_START"));
			break;

		case _eMASK_TEGKEY_2P_ALIGN_FLOW_LASER_FOCUS_START:
			Devs::m_GantryMotion.LaserFocusMove();

			SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_LASER_FOCUS_CHECK, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_LASER_FOCUS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMASK_TEGKEY_2P_ALIGN_FLOW_LASER_FOCUS_CHECK:
			if (Devs::m_GantryMotion.LaserFocusMoveCheck())
			{
				Sleep(500); //!!	//KJT 20210321

				if (CModelData::m_AlignPara.Info.nMain2PAlignFocusType == eFocusType_Both)
					SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_IMAGE_FOCUS_START, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_IMAGE_FOCUS_START"));
				else
					SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_GRAB_START, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_GRAB_START"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_ERROR, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_LASER_FOCUS_CHECK, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_LASER_FOCUS_CHECK"));
			}
			break;

		case _eMASK_TEGKEY_2P_ALIGN_FLOW_IMAGE_FOCUS_START:
#ifndef SIM_MODE
			g_pReview10x->m_bAfEnd = FALSE;
			g_pReview10x->AutofoucsRun();
#endif
			SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_IMAGE_FOCUS_CHECK, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_IMAGE_FOCUS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMASK_TEGKEY_2P_ALIGN_FLOW_IMAGE_FOCUS_CHECK:
#ifndef SIM_MODE
			if (g_pReview10x->m_bAfEnd == TRUE)
			{
				Sleep(IMAGE_FOCUS_DELAY);
				SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_GRAB_START, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_GRAB_START"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_ERROR, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_IMAGE_FOCUS_CHECK, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_IMAGE_FOCUS_CHECK"));
			}
#else
			Sleep(IMAGE_FOCUS_DELAY);
			SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_GRAB_START, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_GRAB_START"));
#endif
			break;
#pragma region //2Point Align
		case _eMASK_TEGKEY_2P_ALIGN_FLOW_GRAB_START:
			SharedInfo::bTegkey2PAlignGrabDone = TRUE;

			Devs::m_GantryMotion.FindBlob_Tegkey_Review10X(&m_AlignVisionResultValue[0][m_nAlignPoint], &m_AlignVisionResultValue[1][m_nAlignPoint]);

			SharedInfo::dTegkey2PAlignVisionResultValue[0][m_nAlignPoint] = m_AlignVisionResultValue[0][m_nAlignPoint];
			SharedInfo::dTegkey2PAlignVisionResultValue[1][m_nAlignPoint] = m_AlignVisionResultValue[1][m_nAlignPoint];

			Str.Format(_T("AlignCnt:%d Diff X:%.5f, Y:%.5f"), m_nAlignPoint, m_AlignVisionResultValue[0][m_nAlignPoint], m_AlignVisionResultValue[1][m_nAlignPoint]);
			Total_Msg(Str);

			SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_GRAB_DONE_CHECK, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_GRAB_DONE_CHECK"));
			break;

		case _eMASK_TEGKEY_2P_ALIGN_FLOW_GRAB_DONE_CHECK:
			if ((m_bDirReverse == FALSE && m_nAlignPoint == 1) || (m_bDirReverse == TRUE && m_nAlignPoint == 0))
			{
				SharedInfo::nTegkey2PAlignCurCount++;
				Str.Format(_T("AlignCurCount:%d Diff X[0]:%.5f, Y[0]:%.5f, X[1]:%.5f, Y[1]:%.5f"), SharedInfo::nTegkey2PAlignCurCount, m_AlignVisionResultValue[0][0], m_AlignVisionResultValue[1][0], m_AlignVisionResultValue[0][1], m_AlignVisionResultValue[1][1]);
				Total_Msg(Str);

				if (m_bDirReverse == FALSE)
				{
					m_bDirReverse = TRUE;
					m_nAlignPoint = 1;
				}
				else
				{
					m_bDirReverse = FALSE;
					m_nAlignPoint = 0;
				}

				Sleep(100);
				Devs::m_InspectionStageMotion.GetUVWPos(m_AlignPointValue[0], m_AlignPointValue[1], m_AlignVisionResultValue[0], m_AlignVisionResultValue[1], &m_dDiffPos[0], &m_dDiffPos[1], &m_dDiffPos[2], TRUE);

				Str.Format(_T("Uvw Diff Pos X:%.5f, Y:%.5f, T:%.5f"), m_dDiffPos[0], m_dDiffPos[1], m_dDiffPos[2]);
				Total_Msg(Str);

				dDiffXTemp = m_AlignVisionResultValue[0][0] + m_AlignVisionResultValue[0][1];
				Str.Format(_T("Diff_X:%.5f"), dDiffXTemp);
				Total_Msg(Str);

				SharedInfo::AlignCenterDiffInfo.dDiff_Tegkey2PAlignX = (fabs(m_AlignVisionResultValue[0][0]) + fabs(m_AlignVisionResultValue[0][1])) / 2;
				Str.Format(_T("Center Diff_X:%.5f"), SharedInfo::AlignCenterDiffInfo.dDiff_Tegkey2PAlignX);
				Total_Msg(Str);
				SharedInfo::AlignCenterDiffInfoSave(); //!!
				Sleep(100);

				if (dDiffXTemp < CModelData::m_AlignPara.Info.dTegkeyAlignTargetX &&
					fabs(m_AlignVisionResultValue[1][0]) < CModelData::m_AlignPara.Info.dTegkeyAlignTargetX &&
					fabs(m_AlignVisionResultValue[1][1]) < CModelData::m_AlignPara.Info.dTegkeyAlignTargetY
					&&
					fabs(m_dDiffPos[2] < 0.001))
				{
					SharedInfo::LightAllOff(); //KJT 20210226

					SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_FINISH_GANTRY_Z1_WAIT_POS, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_FINISH_GANTRY_Z1_WAIT_POS"));
				}
				else
				{
					SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_INSPECTION_UVW_MOVE_START, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_INSPECTION_UVW_MOVE_START"));
				}
			}
			else
			{
				if (m_bDirReverse == FALSE)
					m_nAlignPoint = 1;
				else
					m_nAlignPoint = 0;

				Sleep(1000);
				SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_GANTRY_Z1_INSPECTION_POS_2ND, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_GANTRY_Z1_INSPECTION_POS_2ND"));
			}
			break;

		case _eMASK_TEGKEY_2P_ALIGN_FLOW_INSPECTION_UVW_MOVE_START:
		{
#pragma region //AutoRun, ManualRun Interlock
			if (SharedInfo::bTegkey2PAlignGrabDone == FALSE) //KJT 20210225
			{
				Total_Msg(_T("Main All Grab Done False !!"));
				SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_ERROR, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_ERROR"));
				break;
			}
#pragma endregion

			memset(dRefPos, 0, sizeof(dRefPos));
			memset(dActPos, 0, sizeof(dActPos));

			//0:LB, 1:LT, 2:RT, 3:RB
			dRefPos[0][0] = m_AlignPointValue[0][0];
			dRefPos[0][1] = m_AlignPointValue[1][0];

			dRefPos[1][0] = m_AlignPointValue[0][0];
			dRefPos[1][1] = m_AlignPointValue[1][0] + 200.0;

			dRefPos[2][0] = m_AlignPointValue[0][1];
			dRefPos[2][1] = m_AlignPointValue[1][1] + 200.0;

			dRefPos[3][0] = m_AlignPointValue[0][1];
			dRefPos[3][1] = m_AlignPointValue[1][1];


			dActPos[0][0] = m_AlignPointValue[0][0] + m_AlignVisionResultValue[0][0];
			dActPos[0][1] = m_AlignPointValue[1][0] + m_AlignVisionResultValue[1][0];

			dActPos[1][0] = m_AlignPointValue[0][0];
			dActPos[1][1] = m_AlignPointValue[1][0] + 200.0;

			dActPos[2][0] = m_AlignPointValue[0][1];			//dRefPos[2][0] = m_AlignPointValue[0][1]; //KJT 20200904 ???
			dActPos[2][1] = m_AlignPointValue[1][1] + 200.0;	//dRefPos[2][1] = m_AlignPointValue[1][1] + 200.0;

			dActPos[3][0] = m_AlignPointValue[0][1] + m_AlignVisionResultValue[0][1];
			dActPos[3][1] = m_AlignPointValue[1][1] + m_AlignVisionResultValue[1][1];

			Devs::m_InspectionStageMotion.UVWStageAlignMove(0, dRefPos, dActPos);
			Sleep(1000); //!!
			SharedInfo::bTegkey2PAlignGrabDone = FALSE;

			SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_INSPECTION_UVW_MOVE_DONE_CHECK, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_INSPECTION_UVW_MOVE_DONE_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
		}
		break;
#pragma endregion

		case _eMASK_TEGKEY_2P_ALIGN_FLOW_INSPECTION_UVW_MOVE_DONE_CHECK:
#if UVW_MOVE_TYPE //KJT 20210322
			if (Devs::m_InspectionStageMotion.IsUVWStagePos(m_dDiffPos) == TRUE)
#else //KJT 20210304. FMM
			if (Devs::m_InspectionStageMotion.IsUVWStagePos())
#endif
			{
				SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_GANTRY_Z1_INSPECTION_POS_2ND, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_GANTRY_Z1_INSPECTION_POS_2ND"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_ERROR, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_INSPECTION_UVW_MOVE_DONE_CHECK, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_INSPECTION_UVW_MOVE_DONE_CHECK"));
			}
			break;

		case _eMASK_TEGKEY_2P_ALIGN_FLOW_FINISH_GANTRY_Z1_WAIT_POS:
			Devs::m_GantryMotion.Move_GantryZ_All_Wait_Pos();
			Sleep(20); //!!

			SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_FINISH_GANTRY_Z1_WAIT_POS_CHECK, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_FINISH_GANTRY_Z1_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);

			break;

		case _eMASK_TEGKEY_2P_ALIGN_FLOW_FINISH_GANTRY_Z1_WAIT_POS_CHECK:
			if (Devs::m_GantryMotion.Is_GantryZ_All_Wait_Pos())
			{
				//if (SharedInfo::MachineState.bAutoRunFlag == TRUE && SharedInfo::Active.ProcessEndFlow != eCOMBO_AUTO_RUN_FLOW_TEGKEY_ALIGN)
				//	SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_DONE, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_DONE"));
				//else
					SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_ERROR, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_FINISH_GANTRY_Z1_WAIT_POS_CHECK, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_FINISH_GANTRY_Z1_WAIT_POS_CHECK"));
			}
			break;

		case _eMASK_TEGKEY_2P_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS:
			Devs::m_GantryMotion.Move_Gantry_X_Wait_Pos();
			Sleep(20); //!!
			Devs::m_GantryMotion.Move_Gantry_Y_Wait_Pos();
			Sleep(20); //!!

			SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eMASK_TEGKEY_2P_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Wait_Pos() && Devs::m_GantryMotion.Is_Gantry_Y_Wait_Pos())
			{
				SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_DONE, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_ERROR, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK"));
			}
			break;

		case _eMASK_TEGKEY_2P_ALIGN_FLOW_ERROR:
			break;

		case _eMASK_TEGKEY_2P_ALIGN_FLOW_DONE:
		{
			m_bFlowDone = TRUE;

			SharedInfo::nPrevFlowID = eTEGKEY_ALIGN_FLOW; //KJT 20210326

			SharedInfo::CalTactTime(_T("MASK_TEGKEY_2P_ALIGN_FLOW"), m_timeStart); //KJT 20210329

			SetStep(_eMASK_TEGKEY_2P_ALIGN_FLOW_IDLE, _T("_eMASK_TEGKEY_2P_ALIGN_FLOW_IDLE"));
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

BOOL CMaskTegkey2PAlignFlow::GetXYTPos(double *dRefPosX, double *dRefPosY, double *dDiffPosX, double *dDiffPosY, double *ResultX, double *ResultY, double *ResultT)
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
double CMaskTegkey2PAlignFlow::GetAlignPos_X(int nAlignCount)
{
	double dPos = m_AlignPointValue[0][nAlignCount];
	return dPos;
}
double CMaskTegkey2PAlignFlow::GetAlignPos_Y(int nAlignCount)
{
	double dPos = m_AlignPointValue[1][nAlignCount];
	return dPos;
}

BOOL CMaskTegkey2PAlignFlow::FlowInterlock()
{
	CString Str = _T("");

	//Servo On Check
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
