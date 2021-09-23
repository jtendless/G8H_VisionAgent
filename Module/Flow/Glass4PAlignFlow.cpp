#include "stdafx.h"
#include "Glass4PAlignFlow.h"
#include "Log/Logger.h"
#include "Vision/Devs.h"
#include "Data/ModelData.h"
#include "CamAreaModul.h"
#include "Data/SystemData.h"
#include "FmmLight1.h"

CGlass4PAlignFlow::CGlass4PAlignFlow()
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

CGlass4PAlignFlow::~CGlass4PAlignFlow()
{
}

BOOL CGlass4PAlignFlow::InitProcess()
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
	//pMappingProc = CMappingProc::GetInstance();
	return TRUE;
}
BOOL CGlass4PAlignFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eGLASS_4P_ALIGN_FLOW_IDLE);

	if (hHandle != NULL)
	{
		CloseHandle(hHandle);
		hHandle = NULL;
	}

	return TRUE;
}
BOOL CGlass4PAlignFlow::Start(int nStep)
{
	memset(Devs::m_GantryMotion.m_dTpX, 0, sizeof(Devs::m_GantryMotion.m_dTpX));
	memset(Devs::m_GantryMotion.m_dTpY, 0, sizeof(Devs::m_GantryMotion.m_dTpY));

	m_bFlowDone = FALSE;
	m_bStopBit = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(nStep, _T("_eGLASS_4P_ALIGN_FLOW_START"));
	return TRUE;
}
BOOL CGlass4PAlignFlow::Stop()
{
	m_bStopBit = TRUE;
	return TRUE;
}

UINT CGlass4PAlignFlow::ThreadFunction(LPVOID lpParam)
{
	CGlass4PAlignFlow* pFlow = NULL;

	pFlow = (CGlass4PAlignFlow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}

VOID CGlass4PAlignFlow::ThreadFunctionEntry(VOID)
{
	DWORD	dwResult = 0;
	double	dStrt_Time = GetTickCount();
	double	dEnd_Time = GetTickCount();
	double	dWait_Time = GetTickCount();
	int		nWork_Mask_Mode = -1;
	int		nWork_Mask_Index = -1;
	BOOL	bComplete_Step = FALSE;
	CString Str = _T("");
	BOOL bResult = FALSE;

	double dRefPos[4][2] = { 0.0, };
	double dActPos[4][2] = { 0.0, };

	double dPosX = 0.0, dPosY = 0.0;
	double dVel[3] = { 1.0, 1.0, 1.0 };
	double dAcc[3] = { 2.0, 2.0, 2.0 };
	double dDecel[3] = { 2.0, 2.0, 2.0 };

	double dResultDiffX = 0.0, dResultDiffY = 0.0;

	int nBackLightVal[BACKLIGHT_CH_COUNT] = { 100, };

	while (m_FlowFinish)
	{
		WaitForSingleObject(hHandle, INFINITE);
		ResetEvent(hHandle);

		if (SharedInfo::bMachineStopFlag == TRUE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(_eGLASS_4P_ALIGN_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}

		switch (GetCurrentTotalStep())
		{
		case _eGLASS_4P_ALIGN_FLOW_IDLE:
		{
			break;
		}
		case _eGLASS_4P_ALIGN_FLOW_START:
		{
			m_timeStart = CTime::GetCurrentTime(); //KJT 20210329

			//LB
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

			/////////////
			SharedInfo::nGantryZ1View = eViewReview10X;

			m_nAlignPoint = 0;

			memset(m_AlignVisionResultValue, 0x0, sizeof(m_AlignVisionResultValue));

			SharedInfo::nGlass4PAlignCurCount = 0;

			SharedInfo::LigthAllOff();

			Sleep(500);
			g_CommLight_8ch.SetLight_Review_Coaxial(CModelData::m_AlignPara.Info.nVerticalMainAlignCoAxial);
			Sleep(30);
			g_CommLight_12ch.SetLight_Review_Ring(CModelData::m_AlignPara.Info.nVerticalMainAlignRing);
			Sleep(30);
			g_CommMLCLedLight.BackLightOn(nBackLightVal);
			Sleep(500);

			Devs::m_MappingProc.ReleaseSWMapping(eMAPPING_ID_10X); //!! KJT 20200913
			Devs::m_MappingProc.ReleaseXYTAlignData(eMAPPING_ID_10X); //!! KJT 20200913

			SetStep(_eGLASS_4P_ALIGN_FLOW_INTERLOCK, _T("_eGLASS_4P_ALIGN_FLOW_INTERLOCK"));
			break;
		}

		case _eGLASS_4P_ALIGN_FLOW_INTERLOCK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(_eGLASS_4P_ALIGN_FLOW_ERROR, _T("_eGLASS_4P_ALIGN_FLOW_ERROR"));
			}
			else
			{
				if (m_bPreAlignUse == TRUE && m_bPreAlignDone == FALSE)
				{
					SharedInfo::nGantryZ1View = eViewPreAlign;

					g_CommLight_8ch.SetLight_PreAlign(CModelData::m_AlignPara.Info.nVerticalPreAlignCoAxial, CModelData::m_AlignPara.Info.nVerticalPreAlignRing);
				}
				else
				{
					SharedInfo::nGantryZ1View = eViewReview10X;

					g_CommLight_8ch.SetLight_Review_Coaxial(CModelData::m_AlignPara.Info.nVerticalMainAlignCoAxial);
					Sleep(20);
					g_CommLight_12ch.SetLight_Review_Ring(CModelData::m_AlignPara.Info.nVerticalMainAlignRing);
				}

				SetStep(_eGLASS_4P_ALIGN_FLOW_UNLOADER_READY, _T("_eGLASS_4P_ALIGN_FLOW_UNLOADER_READY"));
			}
			break;

#pragma region //Unloader Ready
		case _eGLASS_4P_ALIGN_FLOW_UNLOADER_READY:
			Devs::m_Ready_UnloaderFlow.Start();

			SetStep(_eGLASS_4P_ALIGN_FLOW_UNLOADER_READY_CHECK, _T("_eGLASS_4P_ALIGN_FLOW_UNLOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eGLASS_4P_ALIGN_FLOW_UNLOADER_READY_CHECK:
			if (Devs::m_Ready_UnloaderFlow.IsFlowDone())
			{
				SetStep(_eGLASS_4P_ALIGN_FLOW_LOADER_READY, _T("_eGLASS_4P_ALIGN_FLOW_LOADER_READY"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eGLASS_4P_ALIGN_FLOW_ERROR, _T("_eGLASS_4P_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eGLASS_4P_ALIGN_FLOW_UNLOADER_READY_CHECK, _T("_eGLASS_4P_ALIGN_FLOW_UNLOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Loader Ready
		case _eGLASS_4P_ALIGN_FLOW_LOADER_READY:
			Devs::m_Ready_LoaderFlow.Start();

			SetStep(_eGLASS_4P_ALIGN_FLOW_LOADER_READY_CHECK, _T("_eGLASS_4P_ALIGN_FLOW_LOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eGLASS_4P_ALIGN_FLOW_LOADER_READY_CHECK:
			if (Devs::m_Ready_LoaderFlow.IsFlowDone())
			{
				SetStep(_eGLASS_4P_ALIGN_FLOW_BOX_CAMERA_READY, _T("_eGLASS_4P_ALIGN_FLOW_BOX_CAMERA_READY"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eGLASS_4P_ALIGN_FLOW_ERROR, _T("_eGLASS_4P_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eGLASS_4P_ALIGN_FLOW_LOADER_READY_CHECK, _T("_eGLASS_4P_ALIGN_FLOW_LOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Box Camera Ready
		case _eGLASS_4P_ALIGN_FLOW_BOX_CAMERA_READY:
			Devs::m_BoxMotion.BoxAlignCameraYL_WaitPos();
			Sleep(20);
			Devs::m_BoxMotion.BoxAlignCameraYR_WaitPos();
			Sleep(500); //!!

			SetStep(_eGLASS_4P_ALIGN_FLOW_BOX_CAMERA_READY_CHECK, _T("_eGLASS_4P_ALIGN_FLOW_BOX_CAMERA_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eGLASS_4P_ALIGN_FLOW_BOX_CAMERA_READY_CHECK:
			if (Devs::m_BoxMotion.Is_BoxAlignCameraYL_WaitPos() == TRUE && Devs::m_BoxMotion.Is_BoxAlignCameraYR_WaitPos() == TRUE)
			{
				SetStep(_eGLASS_4P_ALIGN_FLOW_GANTRY_ZX_READY, _T("_eGLASS_4P_ALIGN_FLOW_GANTRY_ZX_READY"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eGLASS_4P_ALIGN_FLOW_ERROR, _T("_eGLASS_4P_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eGLASS_4P_ALIGN_FLOW_BOX_CAMERA_READY_CHECK, _T("_eGLASS_4P_ALIGN_FLOW_BOX_CAMERA_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Gantry Z, X Ready
		case _eGLASS_4P_ALIGN_FLOW_GANTRY_ZX_READY:
			Devs::m_Ready_GantryZX_Flow.Start();

			SetStep(_eGLASS_4P_ALIGN_FLOW_GANTRY_ZX_READY_CHECK, _T("_eGLASS_4P_ALIGN_FLOW_GANTRY_ZX_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eGLASS_4P_ALIGN_FLOW_GANTRY_ZX_READY_CHECK:
			if (Devs::m_Ready_GantryZX_Flow.IsFlowDone())
			{
				SetStep(_eGLASS_4P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST, _T("_eGLASS_4P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eGLASS_4P_ALIGN_FLOW_ERROR, _T("_eGLASS_4P_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eGLASS_4P_ALIGN_FLOW_GANTRY_ZX_READY_CHECK, _T("_eGLASS_4P_ALIGN_FLOW_GANTRY_ZX_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Gantry XYZ First Pos Move
		case _eGLASS_4P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST:
			if (m_bPreAlignUse == TRUE && m_bPreAlignDone == FALSE)
			{
				Devs::m_GantryMotion.Move_Gantry_X_Pos(GetGlass4PAlignPos_X_PreAlign(m_nAlignPoint), FALSE);
				Sleep(10);
				Devs::m_GantryMotion.Move_Gantry_Y_Pos(GetGlass4PAlignPos_Y_PreAlign(m_nAlignPoint));
			}
			else
			{
				Devs::m_GantryMotion.Move_Gantry_X_Pos(GetGlass4PAlignPos_X_Review10X(m_nAlignPoint), FALSE);
				Sleep(10);
				Devs::m_GantryMotion.Move_Gantry_Y_Pos(GetGlass4PAlignPos_Y_Review10X(m_nAlignPoint));
			}

			SetStep(_eGLASS_4P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK, _T("_eGLASS_4P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eGLASS_4P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK:
			if (m_bPreAlignUse == TRUE && m_bPreAlignDone == FALSE)
			{
				if (Devs::m_GantryMotion.Is_Gantry_X_Pos(GetGlass4PAlignPos_X_PreAlign(m_nAlignPoint)) && Devs::m_GantryMotion.Is_Gantry_Y_Pos(GetGlass4PAlignPos_Y_PreAlign(m_nAlignPoint)))
					SetStep(_eGLASS_4P_ALIGN_FLOW_GANTRY_Z1_PRE_ALIGN_INSPECTION_POS, _T("_eGLASS_4P_ALIGN_FLOW_GANTRY_Z1_PRE_ALIGN_INSPECTION_POS"));
				else
					SetCheckStep(_eGLASS_4P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK);
			}
			else if (Devs::m_GantryMotion.Is_Gantry_X_Pos(GetGlass4PAlignPos_X_Review10X(m_nAlignPoint)) && Devs::m_GantryMotion.Is_Gantry_Y_Pos(GetGlass4PAlignPos_Y_Review10X(m_nAlignPoint)))
			{
				SetStep(_eGLASS_4P_ALIGN_FLOW_GANTRY_Z1_REVIEW10X_INSPECTION_POS, _T("_eGLASS_4P_ALIGN_FLOW_GANTRY_Z1_REVIEW10X_INSPECTION_POS"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eGLASS_4P_ALIGN_FLOW_ERROR, _T("_eGLASS_4P_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eGLASS_4P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK, _T("_eGLASS_4P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK"));
			}
			break;

		case _eGLASS_4P_ALIGN_FLOW_GANTRY_Z1_PRE_ALIGN_INSPECTION_POS:
			Devs::m_GantryMotion.Move_GantryZ1_PreAlign_Pos();

			Sleep(20); //!!
			SetStep(_eGLASS_4P_ALIGN_FLOW_GANTRY_Z1_PRE_ALIGN_INSPECTION_POS_CHECK, _T("_eGLASS_4P_ALIGN_FLOW_GANTRY_Z1_PRE_ALIGN_INSPECTION_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);

			break;
			
		case _eGLASS_4P_ALIGN_FLOW_GANTRY_Z1_PRE_ALIGN_INSPECTION_POS_CHECK:
			if (Devs::m_GantryMotion.Is_GantryZ1_PreAlign_Pos())
			{
				Sleep(500); //!!
				SetStep(_eGLASS_4P_ALIGN_FLOW_GRAB_START, _T("_eGLASS_4P_ALIGN_FLOW_GRAB_START"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eGLASS_4P_ALIGN_FLOW_ERROR, _T("_eGLASS_4P_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eGLASS_4P_ALIGN_FLOW_GANTRY_Z1_PRE_ALIGN_INSPECTION_POS_CHECK, _T("_eGLASS_4P_ALIGN_FLOW_GANTRY_Z1_PRE_ALIGN_INSPECTION_POS_CHECK"));
			}
			break;

		case _eGLASS_4P_ALIGN_FLOW_GANTRY_Z1_REVIEW10X_INSPECTION_POS:
			Devs::m_GantryMotion.Move_GantryZ1_InspectionReview_Pos();

			Sleep(20); //!!

			SetStep(_eGLASS_4P_ALIGN_FLOW_GANTRY_Z1_REVIEW10X_INSPECTION_POS_CHECK, _T("_eGLASS_4P_ALIGN_FLOW_GANTRY_Z1_REVIEW10X_INSPECTION_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eGLASS_4P_ALIGN_FLOW_GANTRY_Z1_REVIEW10X_INSPECTION_POS_CHECK:
			if (Devs::m_GantryMotion.Is_GantryZ1_InspectionReview_Pos())
			{
				Sleep(500); //!!
				SetStep(_eGLASS_4P_ALIGN_FLOW_AUTOFOCUS_CHECK, _T("_eGLASS_4P_ALIGN_FLOW_AUTOFOCUS_CHECK"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eGLASS_4P_ALIGN_FLOW_ERROR, _T("_eGLASS_4P_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eGLASS_4P_ALIGN_FLOW_GANTRY_Z1_REVIEW10X_INSPECTION_POS_CHECK, _T("_eGLASS_4P_ALIGN_FLOW_GANTRY_Z1_REVIEW10X_INSPECTION_POS_CHECK"));
			}
			break;
#pragma endregion

		case _eGLASS_4P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND:
			if (m_bPreAlignUse == TRUE && m_bPreAlignDone == FALSE)
			{
				Devs::m_GantryMotion.Move_Gantry_X_Pos(GetGlass4PAlignPos_X_PreAlign(m_nAlignPoint), FALSE);
				Sleep(10);
				Devs::m_GantryMotion.Move_Gantry_Y_Pos(GetGlass4PAlignPos_Y_PreAlign(m_nAlignPoint));
			}
			else
			{
				Devs::m_GantryMotion.Move_Gantry_X_Pos(GetGlass4PAlignPos_X_Review10X(m_nAlignPoint), FALSE);
				Sleep(10);
				Devs::m_GantryMotion.Move_Gantry_Y_Pos(GetGlass4PAlignPos_Y_Review10X(m_nAlignPoint));
			}

			SetStep(_eGLASS_4P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK, _T("_eGLASS_4P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eGLASS_4P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK:
			if (m_bPreAlignUse == TRUE && m_bPreAlignDone == FALSE)
			{
				if (Devs::m_GantryMotion.Is_Gantry_X_Pos(GetGlass4PAlignPos_X_PreAlign(m_nAlignPoint)) && Devs::m_GantryMotion.Is_Gantry_Y_Pos(GetGlass4PAlignPos_Y_PreAlign(m_nAlignPoint)))
				{
					Sleep(500);
					SetStep(_eGLASS_4P_ALIGN_FLOW_GRAB_START, _T("_eGLASS_4P_ALIGN_FLOW_GRAB_START"));
				}
				else
					SetCheckStep(_eGLASS_4P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK);
			}
			else if (Devs::m_GantryMotion.Is_Gantry_X_Pos(GetGlass4PAlignPos_X_Review10X(m_nAlignPoint)) && Devs::m_GantryMotion.Is_Gantry_Y_Pos(GetGlass4PAlignPos_Y_Review10X(m_nAlignPoint)))
			{
				Sleep(500);
				SetStep(_eGLASS_4P_ALIGN_FLOW_AUTOFOCUS_CHECK, _T("_eGLASS_4P_ALIGN_FLOW_AUTOFOCUS_CHECK"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eGLASS_4P_ALIGN_FLOW_ERROR, _T("_eGLASS_4P_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eGLASS_4P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK, _T("_eGLASS_4P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK"));
			}
			break;

		case _eGLASS_4P_ALIGN_FLOW_AUTOFOCUS_CHECK:
			if (CModelData::m_AlignPara.Info.nVerticalMainAlignFocusType == eFocusType_Laser || CModelData::m_AlignPara.Info.nVerticalMainAlignFocusType == eFocusType_Both)
				SetStep(_eGLASS_4P_ALIGN_FLOW_LASER_FOCUS_START, _T("_eGLASS_4P_ALIGN_FLOW_LASER_FOCUS_START"));
			else if (CModelData::m_AlignPara.Info.nVerticalMainAlignFocusType == eFocusType_Image)
				SetStep(_eGLASS_4P_ALIGN_FLOW_IMAGE_FOCUS_START, _T("_eGLASS_4P_ALIGN_FLOW_IMAGE_FOCUS_START"));
			else
				SetStep(_eGLASS_4P_ALIGN_FLOW_GRAB_START, _T("_eGLASS_4P_ALIGN_FLOW_GRAB_START"));
			break;

		case _eGLASS_4P_ALIGN_FLOW_LASER_FOCUS_START:
			Devs::m_GantryMotion.LaserFocusMove();

			SetStep(_eGLASS_4P_ALIGN_FLOW_LASER_FOCUS_CHECK, _T("_eGLASS_4P_ALIGN_FLOW_LASER_FOCUS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eGLASS_4P_ALIGN_FLOW_LASER_FOCUS_CHECK:
			if (Devs::m_GantryMotion.LaserFocusMoveCheck())
			{
				Sleep(500); //!!	//KJT 20210321

				if (CModelData::m_AlignPara.Info.nVerticalMainAlignFocusType == eFocusType_Both)
					SetStep(_eGLASS_4P_ALIGN_FLOW_IMAGE_FOCUS_START, _T("_eGLASS_4P_ALIGN_FLOW_IMAGE_FOCUS_START"));
				else
					SetStep(_eGLASS_4P_ALIGN_FLOW_GRAB_START, _T("_eGLASS_4P_ALIGN_FLOW_GRAB_START"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eGLASS_4P_ALIGN_FLOW_ERROR, _T("_eGLASS_4P_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eGLASS_4P_ALIGN_FLOW_LASER_FOCUS_CHECK, _T("_eGLASS_4P_ALIGN_FLOW_LASER_FOCUS_CHECK"));
			}
			break;

		case _eGLASS_4P_ALIGN_FLOW_IMAGE_FOCUS_START:
#ifndef SIM_MODE
			g_pReview10x->m_bAfEnd = FALSE;
			g_pReview10x->AutofoucsRun();
#endif

			SetStep(_eGLASS_4P_ALIGN_FLOW_IMAGE_FOCUS_CHECK, _T("_eGLASS_4P_ALIGN_FLOW_IMAGE_FOCUS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eGLASS_4P_ALIGN_FLOW_IMAGE_FOCUS_CHECK:
#ifndef SIM_MODE
			if (g_pReview10x->m_bAfEnd == TRUE)
			{
				Sleep(IMAGE_FOCUS_DELAY);
				SetStep(_eGLASS_4P_ALIGN_FLOW_GRAB_START, _T("_eGLASS_4P_ALIGN_FLOW_GRAB_START"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eGLASS_4P_ALIGN_FLOW_ERROR, _T("_eGLASS_4P_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eGLASS_4P_ALIGN_FLOW_IMAGE_FOCUS_CHECK, _T("_eGLASS_4P_ALIGN_FLOW_IMAGE_FOCUS_CHECK"));
			}
#else
			Sleep(IMAGE_FOCUS_DELAY);
			SetStep(_eGLASS_4P_ALIGN_FLOW_GRAB_START, _T("_eGLASS_4P_ALIGN_FLOW_GRAB_START"));
#endif
			break;

		case _eGLASS_4P_ALIGN_FLOW_GRAB_START:
			if (m_bPreAlignUse == TRUE && m_bPreAlignDone == FALSE)
			{
				bResult = Devs::m_GantryMotion.FindVerticalBlob_PreAlign(&m_AlignVisionResultValue[0][m_nAlignPoint], &m_AlignVisionResultValue[1][m_nAlignPoint]);
			}
			else
			{
				bResult = Devs::m_GantryMotion.FindVerticalBlob_Review10X(&m_AlignVisionResultValue[0][m_nAlignPoint], &m_AlignVisionResultValue[1][m_nAlignPoint]);
			}

			if (bResult == FALSE) //KJT 20210404
			{
				m_nGrabRetryCnt++;
				if (m_nGrabRetryCnt > 3)
				{
					SetStep(_eGLASS_4P_ALIGN_FLOW_ERROR, _T("_eGLASS_4P_ALIGN_FLOW_ERROR"));
					break;
				}

				if (CModelData::m_AlignPara.Info.nVerticalMainAlignFocusType == eFocusType_Laser || CModelData::m_AlignPara.Info.nVerticalMainAlignFocusType == eFocusType_Both)
					SetStep(_eGLASS_4P_ALIGN_FLOW_LASER_FOCUS_START, _T("_eGLASS_4P_ALIGN_FLOW_LASER_FOCUS_START"));
				else if (CModelData::m_AlignPara.Info.nVerticalMainAlignFocusType == eFocusType_Image)
					SetStep(_eGLASS_4P_ALIGN_FLOW_IMAGE_FOCUS_START, _T("_eGLASS_4P_ALIGN_FLOW_IMAGE_FOCUS_START"));
				else
					SetStep(_eGLASS_4P_ALIGN_FLOW_GRAB_START, _T("_eGLASS_4P_ALIGN_FLOW_GRAB_START"));

				break;
			}

			Str.Format(_T("AlignCnt:%d Diff X:%.5f, Y:%.5f"), m_nAlignPoint, m_AlignVisionResultValue[0][m_nAlignPoint], m_AlignVisionResultValue[1][m_nAlignPoint]);
			Total_Msg(Str);

			SetStep(_eGLASS_4P_ALIGN_FLOW_GRAB_DONE_CHECK, _T("_eGLASS_4P_ALIGN_FLOW_GRAB_DONE_CHECK"));
			break;

		case _eGLASS_4P_ALIGN_FLOW_GRAB_DONE_CHECK:
			m_nGrabRetryCnt = 0;
			if (m_nAlignPoint == 3)
			{
				m_nAlignPoint = 0;

				SharedInfo::nGlass4PAlignCurCount++;
				Str.Format(_T("AlignCurCount:%d Diff X[0]:%.5f, Y[0]:%.5f, X[1]:%.5f, Y[1]:%.5f, X[2]:%.5f, Y[2]:%.5f, X[3]:%.5f, Y[3]:%.5f"),
					SharedInfo::nGlass4PAlignCurCount,
					m_AlignVisionResultValue[0][0], m_AlignVisionResultValue[1][0], m_AlignVisionResultValue[0][1], m_AlignVisionResultValue[1][1],
					m_AlignVisionResultValue[0][2], m_AlignVisionResultValue[1][2], m_AlignVisionResultValue[0][3], m_AlignVisionResultValue[1][3]);
				Total_Msg(Str);

				Sleep(100);
				Devs::m_InspectionStageMotion.GetUVWPos(m_AlignPointValue[0], m_AlignPointValue[1], m_AlignVisionResultValue[0], m_AlignVisionResultValue[1], &m_dDiffPos[0], &m_dDiffPos[1], &m_dDiffPos[2], FALSE);

				Str.Format(_T("Uvw Diff Pos X:%.5f, Y:%.5f, T:%.5f"), m_dDiffPos[0], m_dDiffPos[1], m_dDiffPos[2]);
				Total_Msg(Str);

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


				//KJT 20210314
				if ((m_bPreAlignUse == TRUE
					&&
					(fabs(dResultDiffX) < CModelData::m_AlignPara.Info.dVerticalPreAlignTargetX &&
						fabs(dResultDiffY) < CModelData::m_AlignPara.Info.dVerticalPreAlignTargetY && //Y
						(fabs(m_dDiffPos[2]) < 0.001 || (360 - fabs(m_dDiffPos[2])) < 0.001))) //KJT 20210417
					||
					((m_bPreAlignUse == FALSE || m_bPreAlignDone == TRUE)
						&&
						(fabs(dResultDiffX) < CModelData::m_AlignPara.Info.dVerticalMainAlignTargetX &&
							fabs(dResultDiffY) < CModelData::m_AlignPara.Info.dVerticalMainAlignTargetY && //Y
							(fabs(m_dDiffPos[2]) < 0.001 || (360 - fabs(m_dDiffPos[2])) < 0.001)))) //T
				{
					if (m_bPreAlignUse == TRUE && m_bPreAlignDone == FALSE)
					{
						m_bPreAlignDone = TRUE;

						m_nAlignPoint = 0;

						SharedInfo::nVerticalAlignCurCount = 0;

						SharedInfo::nGantryZ1View = eViewReview10X;

						g_CommLight_8ch.SetLight_PreAlign(0, 0);
						Sleep(500);

						g_CommLight_8ch.SetLight_Review_Coaxial(CModelData::m_AlignPara.Info.nVerticalMainAlignCoAxial);
						Sleep(20);
						g_CommLight_12ch.SetLight_Review_Ring(CModelData::m_AlignPara.Info.nVerticalMainAlignRing);

						SetStep(_eGLASS_4P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST, _T("_eGLASS_4P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST"));
					}
					else
					{
						SharedInfo::LigthAllOff();

						SetStep(_eGLASS_4P_ALIGN_FLOW_FINISH_GANTRY_Z1_WAIT_POS, _T("_eGLASS_4P_ALIGN_FLOW_FINISH_GANTRY_Z1_WAIT_POS"));
					}
				}
				else
				{
					SetStep(_eGLASS_4P_ALIGN_FLOW_INSPECTION_UVW_MOVE_START, _T("_eGLASS_4P_ALIGN_FLOW_INSPECTION_UVW_MOVE_START"));
				}
			}
			else
			{
				Str.Format(_T("AlignCurCount:%d Diff X[%d]:%.5f, Y[%d]:%.5f"),
					SharedInfo::nGlass4PAlignCurCount, m_nAlignPoint, m_AlignVisionResultValue[0][m_nAlignPoint], m_nAlignPoint, m_AlignVisionResultValue[1][m_nAlignPoint]);
				Total_Msg(Str);

				m_nAlignPoint++;
				Sleep(1000);
				SetStep(_eGLASS_4P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND, _T("_eGLASS_4P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND"));
			}
			break;

		case _eGLASS_4P_ALIGN_FLOW_INSPECTION_UVW_MOVE_START:
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
			Devs::m_InspectionStageMotion.UVWStageAlignMove_4P(dRefPos, dActPos);
			Sleep(1000); //KJT 20210302
#else //FMM
			Devs::m_InspectionStageMotion.UVWStagePosMove(m_dDiffPos, dVel, dAcc, dDecel); //FMM
#endif

			SetStep(_eGLASS_4P_ALIGN_FLOW_INSPECTION_UVW_MOVE_DONE_CHECK, _T("_eGLASS_4P_ALIGN_FLOW_INSPECTION_UVW_MOVE_DONE_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eGLASS_4P_ALIGN_FLOW_INSPECTION_UVW_MOVE_DONE_CHECK:
#if UVW_MOVE_TYPE //KJT 20210322
			if (Devs::m_InspectionStageMotion.IsUVWStagePos(m_dDiffPos) == TRUE)
#else //KJT 20210304. FMM
			if (Devs::m_InspectionStageMotion.IsUVWStagePos())
#endif
			{
				SetStep(_eGLASS_4P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND, _T("_eGLASS_4P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eGLASS_4P_ALIGN_FLOW_ERROR, _T("_eGLASS_4P_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eGLASS_4P_ALIGN_FLOW_INSPECTION_UVW_MOVE_DONE_CHECK, _T("_eGLASS_4P_ALIGN_FLOW_INSPECTION_UVW_MOVE_DONE_CHECK"));
			}
			break;

		case _eGLASS_4P_ALIGN_FLOW_FINISH_GANTRY_Z1_WAIT_POS:
			Devs::m_GantryMotion.Move_GantryZ_All_Wait_Pos();
			Sleep(20); //!!

			SetStep(_eGLASS_4P_ALIGN_FLOW_FINISH_GANTRY_Z1_WAIT_POS_CHECK, _T("_eGLASS_4P_ALIGN_FLOW_FINISH_GANTRY_Z1_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);

			break;

		case _eGLASS_4P_ALIGN_FLOW_FINISH_GANTRY_Z1_WAIT_POS_CHECK:
			if (Devs::m_GantryMotion.Is_GantryZ_All_Wait_Pos())
			{
				SetStep(_eGLASS_4P_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS, _T("_eGLASS_4P_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eGLASS_4P_ALIGN_FLOW_ERROR, _T("_eGLASS_4P_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eGLASS_4P_ALIGN_FLOW_FINISH_GANTRY_Z1_WAIT_POS_CHECK, _T("_eGLASS_4P_ALIGN_FLOW_FINISH_GANTRY_Z1_WAIT_POS_CHECK"));
			}
			break;

		case _eGLASS_4P_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS:
			Devs::m_GantryMotion.Move_Gantry_X_Wait_Pos();
			Sleep(20); //!!
			Devs::m_GantryMotion.Move_Gantry_Y_Wait_Pos();
			Sleep(20); //!!

			SetStep(_eGLASS_4P_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK, _T("_eGLASS_4P_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eGLASS_4P_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Wait_Pos() && Devs::m_GantryMotion.Is_Gantry_Y_Wait_Pos())
			{
				SetStep(_eGLASS_4P_ALIGN_FLOW_DONE, _T("_eGLASS_4P_ALIGN_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SetStep(_eGLASS_4P_ALIGN_FLOW_ERROR, _T("_eGLASS_4P_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eGLASS_4P_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK, _T("_eGLASS_4P_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK"));
			}
			break;

		case _eGLASS_4P_ALIGN_FLOW_ERROR:
			break;

		case _eGLASS_4P_ALIGN_FLOW_DONE:
		{
			m_bFlowDone = TRUE;

			SharedInfo::CalTactTime(_T("GLASS_4P_ALIGN_FLOW"), m_timeStart); //KJT 20210329

			SetStep(_eGLASS_4P_ALIGN_FLOW_IDLE, _T("_eGLASS_4P_ALIGN_FLOW_IDLE"));
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

double CGlass4PAlignFlow::GetGlass4PAlignPos_X_PreAlign(int nAlignCount)
{
	double dPos = m_AlignPointValue[0][nAlignCount] - CSystemData::m_Coordinate.Info.dOffsetReview10xToPreAlign_X;
	return dPos;
}
double CGlass4PAlignFlow::GetGlass4PAlignPos_Y_PreAlign(int nAlignCount)
{
	double dPos = m_AlignPointValue[1][nAlignCount] - CSystemData::m_Coordinate.Info.dOffsetReview10xToPreAlign_Y;
	return dPos;
}
double CGlass4PAlignFlow::GetGlass4PAlignPos_X_Review10X(int nAlignCount)
{
	double dPos = m_AlignPointValue[0][nAlignCount];
	return dPos;
}
double CGlass4PAlignFlow::GetGlass4PAlignPos_Y_Review10X(int nAlignCount)
{
	double dPos = m_AlignPointValue[1][nAlignCount];
	return dPos;
}
void CGlass4PAlignFlow::SetPreAlignUseMode(BOOL bUse/* = FALSE*/)
{
	m_bPreAlignUse = bUse;

	m_bPreAlignDone = FALSE;
}

BOOL CGlass4PAlignFlow::FlowInterlock()
{
	if (Devs::m_CassetteMotion.Is_CSTPickUpUnitBwd() == FALSE)
	{
		Total_Msg(_T("Check Pickup Unit Backward !!!"));
		return FALSE;
	}
	if (SharedInfo::DInputValue[_DIN_CST_UNSAFE_POS_DETECT] == TRUE)
	{
		Total_Msg(_T("Check CST Unsafe Pos Detect Sensor !!!"));
		return FALSE;
	}
	if (SharedInfo::DInputValue[_DIN_CST_BACKWARD_DETECT] == TRUE)
	{
		Total_Msg(_T("Check CST Backward Detect Sensor !!!"));
		return FALSE;
	}

	return TRUE;
}