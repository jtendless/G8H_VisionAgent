#include "stdafx.h"
#include "VerticalAlignFlow.h"
#include "Log/Logger.h"
#include "Vision/Devs.h"
#include "Data/ModelData.h"
#include "CamAreaModul.h"
#include "Data/SystemData.h"
#include "FmmLight1.h"

CVerticalAlignFlow::CVerticalAlignFlow()
{
	m_dDiffPos[0] = 0.0;
	m_dDiffPos[1] = 0.0;
	m_dDiffPos[2] = 0.0;

	m_dTarget[0] = 0.0;
	m_dTarget[1] = 0.0;
	m_dTarget[2] = 0.0;

	m_nAlignCnt = 0;
	m_bDirReverse = FALSE;
}

CVerticalAlignFlow::~CVerticalAlignFlow()
{

}

BOOL CVerticalAlignFlow::InitProcess()
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
	//pMappingProc = CMappingProc::GetInstance();
	return TRUE;
}

BOOL CVerticalAlignFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(eVERTICAL_ALIGN_FLOW_IDLE, FALSE);

	if (hHandle != NULL)
	{
		CloseHandle(hHandle);
		hHandle = NULL;
	}

	do
	{
		Sleep(10);

	} while (m_bTerminate == 0);

	//delete this;

	return TRUE;
}

BOOL CVerticalAlignFlow::SetHorizontalPosX(double *dPosX, double *dPosY)
{
	memcpy(dHorizontalPosX, dPosX, sizeof(double) * 2);
	memcpy(dHorizontalPosY, dPosY, sizeof(double) * 2);
	return TRUE;
}

BOOL CVerticalAlignFlow::SetVerticalPosXY(double *dPosX, double *dPosY)
{
	m_AlignPointValue[0][0] = dPosX[0];
	m_AlignPointValue[1][0] = dPosY[0];

	m_AlignPointValue[0][1] = dPosX[1];
	m_AlignPointValue[1][1] = dPosY[1];
	return TRUE;
}
double CVerticalAlignFlow::GetVerticalPos_X_PreAlign(int nAlignCount)
{
	double dPos = m_AlignPointValue[0][nAlignCount] - CSystemData::m_Coordinate.Info.dOffsetReview10xToPreAlign_X;
	return dPos;
}
double CVerticalAlignFlow::GetVerticalPos_Y_PreAlign(int nAlignCount)
{
	double dPos = m_AlignPointValue[1][nAlignCount] - CSystemData::m_Coordinate.Info.dOffsetReview10xToPreAlign_Y;
	return dPos;
}
double CVerticalAlignFlow::GetVerticalPos_X_Review(int nAlignCount)
{
	double dPos = m_AlignPointValue[0][nAlignCount];
	return dPos;
}
double CVerticalAlignFlow::GetVerticalPos_Y_Review(int nAlignCount)
{
	double dPos = m_AlignPointValue[1][nAlignCount];
	return dPos;
}
BOOL CVerticalAlignFlow::SetPreAlignUseMode(BOOL bUse)
{
	m_bPreAlignUse = bUse;
	
	m_bPreAlignDone = FALSE;

	return TRUE;
}
BOOL CVerticalAlignFlow::StateStop()
{
	SetStop();
	return TRUE;
}
BOOL CVerticalAlignFlow::Start(int nCamIndex)
{
	//SharedInfo::MachineState.bSemiAutoRunFlag = TRUE;
	m_nMappingID = nCamIndex;

	m_dTarget[0] = CModelData::m_AlignPara.Info.dVerticalMainAlignTargetX;// CModelData::m_GlassPara.Info.dGlassMainAlignTargetX;
	m_dTarget[1] = CModelData::m_AlignPara.Info.dVerticalMainAlignTargetY;// CModelData::m_GlassPara.Info.dGlassMainAlignTargetY;
	m_dTarget[2] = 0.001;// CModelData::m_GlassPara.Info.dGlassMainAlignTargetT;

	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;

	m_bLaserFocusUseFlag = FALSE;
	m_bAutoFocusUseFlag = FALSE;

	switch (CModelData::m_AlignPara.Info.nVerticalMainAlignFocusType)
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

	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(eVERTICAL_ALIGN_FLOW_START, _T("eVERTICAL_ALIGN_FLOW_START"));
	return TRUE;
}

BOOL CVerticalAlignFlow::Stop()
{
	m_bStopBit = TRUE;
	SetStop(); //!!
	//SharedInfo::MachineState.bSemiAutoRunFlag = FALSE;
	return TRUE;
}


UINT CVerticalAlignFlow::ThreadFunction(LPVOID lpParam)
{
	CVerticalAlignFlow* pVerticalAlign = NULL;

	pVerticalAlign = (CVerticalAlignFlow*)lpParam;

	pVerticalAlign->ThreadFunctionEntry();

	pVerticalAlign->m_bTerminate = 1;

	return 0;
}


VOID CVerticalAlignFlow::ThreadFunctionEntry(VOID)
{
	int ErrorCheck = 0;
	CString szMsg;
	BOOL bResult;

	double RefT[2] = { 0.0, }, NewPositionT[2] = { 0.0, }, DiffT[2] = { 0.0, }, DiffPosition[3] = { 0.0, };
	double dUVWX[3];
	double TargetError = 0.;
	double dError;
	double pPosX[2];

	double dVel[3] = { 0.1, 0.1, 0.1 };
	double dAcc[3] = { 0.2,  0.2,  0.2 };
	double dDecel[3] = { 0.2,  0.2,  0.2 };

	DWORD dTickCnt;

	DWORD dResult = 0;
	double dDiffXTemp = 0.0;

	while (m_FlowFinish)
	{
		WaitForSingleObject(hHandle, INFINITE);
		ResetEvent(hHandle);

		if (SharedInfo::bMachineStopFlag == TRUE)// && m_bStopBit == FALSE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(eVERTICAL_ALIGN_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}

		int nVal[BACKLIGHT_CH_COUNT] = { BACKLIGHT_OFF_VALUE, };
		switch (GetCurrentTotalStep())
		{
		case eVERTICAL_ALIGN_FLOW_IDLE:
			break;

		case eVERTICAL_ALIGN_FLOW_START:
			m_timeStart = CTime::GetCurrentTime(); //KJT 20210329
			SharedInfo::m_timeUnitTact = m_timeStart;

			SharedInfo::nCurFlowID = eVERTICAL_ALIGN_FLOW;

			/*
			g_CommLight_8ch.SetLight_Review_Coaxial(0);
			g_CommLight_12ch.SetLight_Review_Ring(0);
			g_CommLight_8ch.SetLight_PreAlign(0, 0);

			g_CommMLCLedLight.AoiLightOff();
			g_CommMLCLedLight.BackLightOff();
			Sleep(500);
			*/

			SharedInfo::LightAllOff();

			m_nAlignCnt = 0;
			m_bDirReverse = FALSE;
			m_nGrabRetryCnt = 0;

			SharedInfo::nVerticalAlignCurCount = 0;

			SetStep(eVERTICAL_ALIGN_FLOW_INTERLOCK, _T("eVERTICAL_ALIGN_FLOW_INTERLOCK"));
			break;

		case eVERTICAL_ALIGN_FLOW_INTERLOCK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(eVERTICAL_ALIGN_FLOW_ERROR, _T("eVERTICAL_ALIGN_FLOW_ERROR"));
			}
			else
			{
				if (m_bPreAlignUse == TRUE && m_bPreAlignDone == FALSE)
				{
					SharedInfo::nGantryZ1View = eViewPreAlign;

					g_CommLoader_Light.SetLight_PreAlign(CModelData::m_AlignPara.Info.nVerticalPreAlignCoAxial, CModelData::m_AlignPara.Info.nVerticalPreAlignRing); //KJT 20210728
				}
				else
				{
					SharedInfo::nGantryZ1View = eViewReview10X;
					g_CommReview_Light.SetLight_Review(CModelData::m_AlignPara.Info.nVerticalMainAlignRing, CModelData::m_AlignPara.Info.nVerticalMainAlignCoAxial);
					//g_CommLight_8ch.SetLight_Review_Coaxial(CModelData::m_AlignPara.Info.nVerticalMainAlignCoAxial);
					//Sleep(20);
					//g_CommLight_12ch.SetLight_Review_Ring(CModelData::m_AlignPara.Info.nVerticalMainAlignRing);
				}

				SetStep(eVERTICAL_ALIGN_FLOW_UNLOADER_READY, _T("eVERTICAL_ALIGN_FLOW_UNLOADER_READY"));
			}
			break;

#pragma region //Unloader Ready
		case eVERTICAL_ALIGN_FLOW_UNLOADER_READY:
			Devs::m_Ready_UnloaderFlow.Start();

			SetStep(eVERTICAL_ALIGN_FLOW_UNLOADER_READY_CHECK, _T("eVERTICAL_ALIGN_FLOW_UNLOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eVERTICAL_ALIGN_FLOW_UNLOADER_READY_CHECK:
			if (Devs::m_Ready_UnloaderFlow.IsFlowDone())
			{
				SetStep(eVERTICAL_ALIGN_FLOW_GANTRY_ZX_READY, _T("eVERTICAL_ALIGN_FLOW_GANTRY_ZX_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eVERTICAL_ALIGN_FLOW_UNLOADER_READY_CHECK : Time Out !!!"), eVERTICAL_ALIGN_FLOW + 0);
				SetStep(eVERTICAL_ALIGN_FLOW_ERROR, _T("eVERTICAL_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eVERTICAL_ALIGN_FLOW_UNLOADER_READY_CHECK, _T("eVERTICAL_ALIGN_FLOW_UNLOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Gantry Z,X Ready
		case eVERTICAL_ALIGN_FLOW_GANTRY_ZX_READY:
			Devs::m_Ready_GantryZX_Flow.Start();

			SetStep(eVERTICAL_ALIGN_FLOW_GANTRY_ZX_READY_CHECK, _T("eVERTICAL_ALIGN_FLOW_GANTRY_ZX_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eVERTICAL_ALIGN_FLOW_GANTRY_ZX_READY_CHECK:
			if (Devs::m_Ready_GantryZX_Flow.IsFlowDone())
			{
				SetStep(eVERTICAL_ALIGN_FLOW_LOADER_READY, _T("eVERTICAL_ALIGN_FLOW_LOADER_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eVERTICAL_ALIGN_FLOW_GANTRY_ZX_READY_CHECK : Time Out !!!"), eVERTICAL_ALIGN_FLOW + 2);
				SetStep(eVERTICAL_ALIGN_FLOW_ERROR, _T("eVERTICAL_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eVERTICAL_ALIGN_FLOW_GANTRY_ZX_READY_CHECK, _T("eVERTICAL_ALIGN_FLOW_GANTRY_ZX_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Loader Ready
		case eVERTICAL_ALIGN_FLOW_LOADER_READY:
			Devs::m_Ready_LoaderFlow.Start();

			SetStep(eVERTICAL_ALIGN_FLOW_LOADER_READY_CHECK, _T("eVERTICAL_ALIGN_FLOW_LOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eVERTICAL_ALIGN_FLOW_LOADER_READY_CHECK:
			if (Devs::m_Ready_LoaderFlow.IsFlowDone())
			{				
				SetStep(eVERTICAL_ALIGN_FLOW_PAPER_UNLOADER_READY, _T("eVERTICAL_ALIGN_FLOW_PAPER_UNLOADER_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eVERTICAL_ALIGN_FLOW_LOADER_READY_CHECK : Time Out !!!"), eVERTICAL_ALIGN_FLOW + 1);
				SetStep(eVERTICAL_ALIGN_FLOW_ERROR, _T("eVERTICAL_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eVERTICAL_ALIGN_FLOW_LOADER_READY_CHECK, _T("eVERTICAL_ALIGN_FLOW_LOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //PaperUnloader Ready
		case eVERTICAL_ALIGN_FLOW_PAPER_UNLOADER_READY:
			Devs::m_Ready_PaperUnloaderFlow.Start();

			SetStep(eVERTICAL_ALIGN_FLOW_PAPER_UNLOADER_READY_CHECK, _T("eVERTICAL_ALIGN_FLOW_PAPER_UNLOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eVERTICAL_ALIGN_FLOW_PAPER_UNLOADER_READY_CHECK:
			if (Devs::m_Ready_PaperUnloaderFlow.IsFlowDone())
			{
				SetStep(eVERTICAL_ALIGN_FLOW_AXIS_GANTRY_XY_MOVE_VERTICAL_POS, _T("eVERTICAL_ALIGN_FLOW_AXIS_GANTRY_XY_MOVE_VERTICAL_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eVERTICAL_ALIGN_FLOW_PAPER_UNLOADER_READY_CHECK : Time Out !!!"), eVERTICAL_ALIGN_FLOW + 1);
				SetStep(eVERTICAL_ALIGN_FLOW_ERROR, _T("eVERTICAL_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eVERTICAL_ALIGN_FLOW_PAPER_UNLOADER_READY_CHECK, _T("eVERTICAL_ALIGN_FLOW_PAPER_UNLOADER_READY_CHECK"));
			}
			break;
#pragma endregion

		case eVERTICAL_ALIGN_FLOW_AXIS_GANTRY_XY_MOVE_VERTICAL_POS:
			if (m_bPreAlignUse == TRUE && m_bPreAlignDone == FALSE)
			{
				Devs::m_GantryMotion.Move_Gantry_X_Pos(GetVerticalPos_X_PreAlign(m_nAlignCnt), FALSE);
				Sleep(10);
				Devs::m_GantryMotion.Move_Gantry_Y_Pos(GetVerticalPos_Y_PreAlign(m_nAlignCnt));
			}
			else
			{
				Devs::m_GantryMotion.Move_Gantry_X_Pos(GetVerticalPos_X_Review(m_nAlignCnt), FALSE);
				Sleep(10);
				Devs::m_GantryMotion.Move_Gantry_Y_Pos(GetVerticalPos_Y_Review(m_nAlignCnt));
			}

			SetStep(eVERTICAL_ALIGN_FLOW_AXIS_GANTRY_XY_VERTICA_POS_CHECK, _T("eVERTICAL_ALIGN_FLOW_AXIS_GANTRY_XY_VERTICA_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eVERTICAL_ALIGN_FLOW_AXIS_GANTRY_XY_VERTICA_POS_CHECK:
			if (m_bPreAlignUse == TRUE && m_bPreAlignDone == FALSE)
			{
				if (Devs::m_GantryMotion.Is_Gantry_X_Pos(GetVerticalPos_X_PreAlign(m_nAlignCnt)) && Devs::m_GantryMotion.Is_Gantry_Y_Pos(GetVerticalPos_Y_PreAlign(m_nAlignCnt)))
					SetStep(eVERTICAL_ALIGN_FLOW_AXIS_Z_PRE_ALGIN_CAM_DOWN_POS, _T("eVERTICAL_ALIGN_FLOW_AXIS_Z_PRE_ALGIN_CAM_DOWN_POS"));
				else
					SetCheckStep(eVERTICAL_ALIGN_FLOW_AXIS_GANTRY_XY_VERTICA_POS_CHECK);
			}
			else if (Devs::m_GantryMotion.Is_Gantry_X_Pos(GetVerticalPos_X_Review(m_nAlignCnt)) && Devs::m_GantryMotion.Is_Gantry_Y_Pos(GetVerticalPos_Y_Review(m_nAlignCnt)))
			{				
				SetStep(eVERTICAL_ALIGN_FLOW_AXIS_Z_REVIEW10X_CAM_DOWN_POS, _T("eVERTICAL_ALIGN_FLOW_AXIS_Z_REVIEW10X_CAM_DOWN_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eVERTICAL_ALIGN_FLOW_AXIS_GANTRY_XY_VERTICA_POS_CHECK : Time Out !!!"), eVERTICAL_ALIGN_FLOW + 3);
				SetStep(eVERTICAL_ALIGN_FLOW_ERROR, _T("eVERTICAL_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eVERTICAL_ALIGN_FLOW_AXIS_GANTRY_XY_VERTICA_POS_CHECK);
			}
			break;

#pragma region //PreAlign Camera
		case eVERTICAL_ALIGN_FLOW_AXIS_Z_PRE_ALGIN_CAM_DOWN_POS:
			Devs::m_GantryMotion.Move_GantryZ1_PreAlign_Pos();

			SetStep(eVERTICAL_ALIGN_FLOW_AXIS_Z_PRE_ALGIN_CAM_DOWN_POS_CHECK, _T("eVERTICAL_ALIGN_FLOW_AXIS_Z_PRE_ALGIN_CAM_DOWN_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eVERTICAL_ALIGN_FLOW_AXIS_Z_PRE_ALGIN_CAM_DOWN_POS_CHECK:
			if (Devs::m_GantryMotion.Is_GantryZ1_PreAlign_Pos() == TRUE)
			{
				SetStep(eVERTICAL_ALIGN_FLOW_GRAB_START, _T("eVERTICAL_ALIGN_FLOW_GRAB_START"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eVERTICAL_ALIGN_FLOW_AXIS_Z_PRE_ALGIN_CAM_DOWN_POS_CHECK : Time Out !!!"), eVERTICAL_ALIGN_FLOW + 4);
				SetStep(eVERTICAL_ALIGN_FLOW_ERROR, _T("eVERTICAL_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eVERTICAL_ALIGN_FLOW_AXIS_Z_PRE_ALGIN_CAM_DOWN_POS_CHECK);
			}
			break;
#pragma endregion

#pragma region //Review 10X
		case eVERTICAL_ALIGN_FLOW_AXIS_Z_REVIEW10X_CAM_DOWN_POS:
			Devs::m_GantryMotion.Move_GantryZ1_InspectionReview_Pos();

			SetStep(eVERTICAL_ALIGN_FLOW_AXIS_Z_REVIEW10X_CAM_DOWN_POS_CHECK, _T("eVERTICAL_ALIGN_FLOW_AXIS_Z_REVIEW10X_CAM_DOWN_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eVERTICAL_ALIGN_FLOW_AXIS_Z_REVIEW10X_CAM_DOWN_POS_CHECK:
			if (Devs::m_GantryMotion.Is_GantryZ1_InspectionReview_Pos() == TRUE)
			{
				Sleep(500); //!!

				if (m_bLaserFocusUseFlag == TRUE)
					SetStep(eVERTICAL_ALIGN_FLOW_AXIS_Z_REVIEW10X_LASER_FOCUS_START, _T("eVERTICAL_ALIGN_FLOW_AXIS_Z_REVIEW10X_LASER_FOCUS_START"));
				else if (m_bAutoFocusUseFlag == TRUE)
					SetStep(eVERTICAL_ALIGN_FLOW_AXIS_Z_REVIEW10X_IMAGE_FOCUS_START, _T("eVERTICAL_ALIGN_FLOW_AXIS_Z_REVIEW10X_IMAGE_FOCUS_START"));
				else
					SetStep(eVERTICAL_ALIGN_FLOW_GRAB_START, _T("eVERTICAL_ALIGN_FLOW_GRAB_START"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eVERTICAL_ALIGN_FLOW_AXIS_Z_REVIEW10X_CAM_DOWN_POS_CHECK : Time Out !!!"), eVERTICAL_ALIGN_FLOW + 5);
				SetStep(eVERTICAL_ALIGN_FLOW_ERROR, _T("eVERTICAL_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eVERTICAL_ALIGN_FLOW_AXIS_Z_REVIEW10X_CAM_DOWN_POS_CHECK);
			}
			break;

		case eVERTICAL_ALIGN_FLOW_AXIS_Z_REVIEW10X_LASER_FOCUS_START:
			Devs::m_GantryMotion.LaserFocusMove();

			SetStep(eVERTICAL_ALIGN_FLOW_AXIS_Z_REVIEW10X_LASER_FOCUS_CHECK, _T("eVERTICAL_ALIGN_FLOW_AXIS_Z_REVIEW10X_LASER_FOCUS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eVERTICAL_ALIGN_FLOW_AXIS_Z_REVIEW10X_LASER_FOCUS_CHECK:
			if (Devs::m_GantryMotion.LaserFocusMoveCheck())
			{
				if (m_bAutoFocusUseFlag == TRUE)
					SetStep(eVERTICAL_ALIGN_FLOW_AXIS_Z_REVIEW10X_IMAGE_FOCUS_START, _T("eVERTICAL_ALIGN_FLOW_AXIS_Z_REVIEW10X_IMAGE_FOCUS_START"));
				else
					SetStep(eVERTICAL_ALIGN_FLOW_GRAB_START, _T("eVERTICAL_ALIGN_FLOW_GRAB_START"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eVERTICAL_ALIGN_FLOW_AXIS_Z_REVIEW10X_LASER_FOCUS_CHECK : Time Out !!!"), eVERTICAL_ALIGN_FLOW + 6);
				SetStep(eVERTICAL_ALIGN_FLOW_ERROR, _T("eVERTICAL_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eVERTICAL_ALIGN_FLOW_AXIS_Z_REVIEW10X_LASER_FOCUS_CHECK, _T("eVERTICAL_ALIGN_FLOW_AXIS_Z_REVIEW10X_LASER_FOCUS_CHECK"));
			}
			break;

		case eVERTICAL_ALIGN_FLOW_AXIS_Z_REVIEW10X_IMAGE_FOCUS_START:
			Total_Msg(_T("Auto Focus Start"));

#ifndef SIM_MODE
			switch (m_nMappingID)
			{
#if 0 //KJT 20210820 Junying Not Use
			case eMAPPING_ID_20X:
				//g_CommLight_8ch.SetLight_Review_Coaxial(CModelData::m_GlassPara.Info.nBrightness20XCoaxial);
				//Sleep(20);
				//g_CommLight_12ch.SetLight_Review_Ring(CModelData::m_GlassPara.Info.nBrightness20XRing);

				Sleep(500);
#ifndef SIM_MODE
				//g_pReview20x->m_bAfEnd = FALSE;
				//g_pReview20x->AutofoucsRun(eViewReview20X);
#endif
				break;
#endif
			case eMAPPING_ID_10X:
			case eMAPPING_ID_20X: //KJT 20210820 Add
			case eMAPPING_ID_50X: //KJT 20210820 Add
				//g_CommLight_8ch.SetLight_Review_Coaxial(CModelData::m_GlassPara.Info.nBrightness10XCoaxial);
				//Sleep(20);
				//g_CommLight_12ch.SetLight_Review_Ring(CModelData::m_GlassPara.Info.nBrightness10XRing);

				Sleep(500);
#ifndef SIM_MODE
				g_pReview10x->m_bAfEnd = FALSE;
				g_pReview10x->AutofoucsRun();
#endif
				break;

			case eMAPPING_ID_PreAlign:
				//g_CommLight_8ch.SetLight_PreAlign(CModelData::m_AlignPara.Info.nPreAlignCoAxial_L, CModelData::m_AlignPara.Info.nPreAlignRing_L);
				//g_CommZomm_Coaxial.SetLight_Zoom_Coaxial(CModelData::m_AlignPara.Info.nPreAlignCoAxial_L);
				//Sleep(10);
				//g_CommZomm_Coaxial.Zoom_Light_On(TRUE);
				//Sleep(10);
				//g_CommZomm_Ring.SetLight_Zoom_Ring(CModelData::m_AlignPara.Info.nPreAlignRing_L);
				//Sleep(10);
				//g_CommZomm_Ring.Zoom_Light_On(TRUE);
				//Sleep(500);

				g_CommLoader_Light.SetLight_PreAlign(CModelData::m_AlignPara.Info.nPreAlignCoAxial_L, CModelData::m_AlignPara.Info.nPreAlignRing_L); //KJT 20210728
#ifndef SIM_MODE
				g_pPreAlign->m_bAfEnd = TRUE;
				//g_pPreAlign->AutofoucsRun();
#endif
				break;
			}
#endif

			SetStep(eVERTICAL_ALIGN_FLOW_AXIS_Z_REVIEW10X_IMAGE_FOCUS_CHECK, _T("eVERTICAL_ALIGN_FLOW_AXIS_Z_REVIEW10X_IMAGE_FOCUS_CHECK"));
			SetTimeOut(TIME_OUT_DUAL);
			break;

		case eVERTICAL_ALIGN_FLOW_AXIS_Z_REVIEW10X_IMAGE_FOCUS_CHECK:
			bResult = FALSE;

			//#ifndef SIM_MODE
#if 1
			switch (m_nMappingID)
			{
#if 0 //KJT 20210820 Junying Not Use
			case eMAPPING_ID_20X:
#ifndef SIM_MODE
				//if (g_pReview20x->m_bAfEnd == TRUE)
#endif
				{
					bResult = TRUE;
				}
				break;
#endif
			case eMAPPING_ID_10X:
			case eMAPPING_ID_20X: //KJT 20210820 Add
			case eMAPPING_ID_50X: //KJT 20210820 Add
#ifndef SIM_MODE
				if (g_pReview10x->m_bAfEnd == TRUE)
#endif
				{
					bResult = TRUE;
				}
				break;
			case eMAPPING_ID_PreAlign:
#ifndef SIM_MODE
				if (g_pPreAlign->m_bAfEnd == TRUE)
#endif
				{
					bResult = TRUE;
				}
				break;
			}
#else
			bResult = TRUE;
#endif
			if (bResult == TRUE)
			{
				m_nGrabRetryCnt = 0;
				Sleep(IMAGE_FOCUS_DELAY);
				SetStep(eVERTICAL_ALIGN_FLOW_GRAB_START, _T("eVERTICAL_ALIGN_FLOW_GRAB_START"));

			}
			else if (IsTimeOut())
			{
				SetStep(eVERTICAL_ALIGN_FLOW_AXIS_Z_REVIEW10X_IMAGE_FOCUS_CHECK, _T("eVERTICAL_ALIGN_FLOW_AXIS_Z_REVIEW10X_IMAGE_FOCUS_CHECK"));
			}
			else
			{
				SetCheckStep(eVERTICAL_ALIGN_FLOW_AXIS_Z_REVIEW10X_IMAGE_FOCUS_CHECK, _T("eVERTICAL_ALIGN_FLOW_AXIS_Z_REVIEW10X_IMAGE_FOCUS_CHECK"));
			}
			break;
#pragma endregion //Review10X

		case eVERTICAL_ALIGN_FLOW_GRAB_START:
			if (m_bPreAlignUse == TRUE && m_bPreAlignDone == FALSE)
			{
				bResult = Devs::m_GantryMotion.FindVerticalBlob_PreAlign(&m_AlignVisionResultValue[0][m_nAlignCnt], &m_AlignVisionResultValue[1][m_nAlignCnt]);
			}
			else
			{
				bResult = Devs::m_GantryMotion.FindVerticalBlob_Review10X(&m_AlignVisionResultValue[0][m_nAlignCnt], &m_AlignVisionResultValue[1][m_nAlignCnt]);
			}

			if (bResult == FALSE)
			{
				SharedInfo::SetAlarm(_T("eVERTICAL_ALIGN_FLOW_GRAB_START : Grab Error !!!"), eVERTICAL_ALIGN_FLOW + 7);
				SetStep(eVERTICAL_ALIGN_FLOW_ERROR, _T("eVERTICAL_ALIGN_FLOW_ERROR"));
				break;
			}

			if ((m_bDirReverse == FALSE && m_nAlignCnt == 1) || (m_bDirReverse == TRUE && m_nAlignCnt == 0))
			{
				m_AlignVisionPreResultValue[0][m_nAlignCnt] = m_AlignVisionResultValue[0][m_nAlignCnt];
				m_AlignVisionPreResultValue[1][m_nAlignCnt] = m_AlignVisionResultValue[1][m_nAlignCnt];
				
				if (m_bDirReverse == FALSE)
				{
					m_bDirReverse = TRUE;
					m_nAlignCnt = 1;
				}
				else
				{
					m_bDirReverse = FALSE;
					m_nAlignCnt = 0;
				}

				Sleep(100);
				Devs::m_InspectionStageMotion.GetUVWPos(m_AlignPointValue[0], m_AlignPointValue[1], m_AlignVisionResultValue[0], m_AlignVisionResultValue[1], &m_dDiffPos[0], &m_dDiffPos[1], &m_dDiffPos[2], TRUE);

				m_ErrorX = m_AlignVisionResultValue[0][1] - m_AlignVisionResultValue[0][0]; //KJT 20210314
				m_ErrorY = m_AlignVisionResultValue[1][0] + m_AlignVisionResultValue[1][1]; //KJT 20210314

				dDiffXTemp = m_AlignVisionResultValue[0][0] + m_AlignVisionResultValue[0][1];
				if ((m_bPreAlignUse == TRUE
					&&
					(dDiffXTemp < CModelData::m_AlignPara.Info.dVerticalPreAlignTargetX && //X
					fabs(m_AlignVisionResultValue[1][0]) < CModelData::m_AlignPara.Info.dVerticalPreAlignTargetY && fabs(m_AlignVisionResultValue[1][1]) < CModelData::m_AlignPara.Info.dVerticalPreAlignTargetY && //Y
					fabs(m_dDiffPos[2]) <= 0.001))
					||
					((m_bPreAlignUse == FALSE || m_bPreAlignDone == TRUE)
					&&
					(dDiffXTemp < CModelData::m_AlignPara.Info.dVerticalMainAlignTargetX && //X
						fabs(m_AlignVisionResultValue[1][0]) < CModelData::m_AlignPara.Info.dVerticalMainAlignTargetY && fabs(m_AlignVisionResultValue[1][1]) < CModelData::m_AlignPara.Info.dVerticalMainAlignTargetY && //Y
						fabs(m_dDiffPos[2]) <= 0.001))) //T
				{
					if (m_bPreAlignUse == TRUE && m_bPreAlignDone == FALSE)
					{
						m_bPreAlignDone = TRUE;

						m_nAlignCnt = 0;

						SharedInfo::nGantryZ1View = eViewReview10X;
						//21.03.01 SJC
						g_CommReview_Light.SetLight_Review(CModelData::m_AlignPara.Info.nVerticalMainAlignRing, CModelData::m_AlignPara.Info.nVerticalMainAlignCoAxial);//review light
						//g_CommLight_8ch.SetLight_Review_Coaxial(CModelData::m_AlignPara.Info.nVerticalMainAlignCoAxial);
						//Sleep(20);
						//g_CommLight_12ch.SetLight_Review_Ring(CModelData::m_AlignPara.Info.nVerticalMainAlignRing);
						//21.03.06 sjc
						SetStep(eVERTICAL_ALIGN_FLOW_GANTRY_ZX_READY, _T("eVERTICAL_ALIGN_FLOW_GANTRY_ZX_READY"));
						//SetStep(eVERTICAL_ALIGN_FLOW_AXIS_GANTRY_XY_MOVE_VERTICAL_POS, _T("eVERTICAL_ALIGN_FLOW_AXIS_GANTRY_XY_MOVE_VERTICAL_POS"));
					}
					else
					{
						SetStep(eVERTICAL_ALIGN_FLOW_AXIS_Z_FINISH_CAM_UP_POS, _T("eVERTICAL_ALIGN_FLOW_AXIS_Z_FINISH_CAM_UP_POS"));
					}
				}
				else
				{
					SetStep(eVERTICAL_ALIGN_FLOW_UVW_MOVE_START, _T("eVERTICAL_ALIGN_FLOW_UVW_MOVE_START"));
				}
			}
			else
			{
				m_AlignVisionPreResultValue[0][m_nAlignCnt] = m_AlignVisionResultValue[0][m_nAlignCnt];
				m_AlignVisionPreResultValue[1][m_nAlignCnt] = m_AlignVisionResultValue[1][m_nAlignCnt];
				
				if (m_bDirReverse == FALSE)
					m_nAlignCnt = 1;
				else
					m_nAlignCnt = 0;

				Sleep(1000);
				SetStep(eVERTICAL_ALIGN_FLOW_AXIS_GANTRY_XY_MOVE_VERTICAL_POS, _T("eVERTICAL_ALIGN_FLOW_AXIS_GANTRY_XY_MOVE_VERTICAL_POS"));

			}
			break;

		case eVERTICAL_ALIGN_FLOW_UVW_MOVE_START:
		{
			//KJT 20200830
			double dRefPos[4][2] = { 0.0, };
			double dActPos[4][2] = { 0.0, };
			//0:LB, 1:LT, 2:RT, 3:RB
			dRefPos[0][0] = m_AlignPointValue[0][0];
			dRefPos[0][1] = m_AlignPointValue[1][0];

			dRefPos[1][0] = m_AlignPointValue[0][0];
			dRefPos[1][1] = m_AlignPointValue[1][0] + 200.0;

			dRefPos[2][0] = m_AlignPointValue[0][1];
			dRefPos[2][1] = m_AlignPointValue[1][1] + 200.0;

			dRefPos[3][0] = m_AlignPointValue[0][1];
			dRefPos[3][1] = m_AlignPointValue[1][1];

			/////////////

			dActPos[0][0] = m_AlignPointValue[0][0] + m_AlignVisionResultValue[0][0];
			dActPos[0][1] = m_AlignPointValue[1][0] + m_AlignVisionResultValue[1][0];

			dActPos[1][0] = m_AlignPointValue[0][0];
			dActPos[1][1] = m_AlignPointValue[1][0] + 200.0;

			dActPos[2][0] = m_AlignPointValue[0][1];
			dActPos[2][1] = m_AlignPointValue[1][1] + 200.0;

			dActPos[3][0] = m_AlignPointValue[0][1] + m_AlignVisionResultValue[0][1];
			dActPos[3][1] = m_AlignPointValue[1][1] + m_AlignVisionResultValue[1][1];

						
			Devs::m_InspectionStageMotion.UVWStageAlignMove(_eVertical_Align_Mode, dRefPos, dActPos);
			Sleep(1000); //!!

			SetStep(eVERTICAL_ALIGN_FLOW_UVW_MOVE_CHECK, _T("eVERTICAL_ALIGN_FLOW_UVW_MOVE_CHECK"));
		}
			break;

		case eVERTICAL_ALIGN_FLOW_UVW_MOVE_CHECK:
			if (Devs::m_InspectionStageMotion.IsUVWStagePos(m_dDiffPos) == TRUE)
			{
				SetStep(eVERTICAL_ALIGN_FLOW_AXIS_GANTRY_XY_MOVE_VERTICAL_POS, _T("eVERTICAL_ALIGN_FLOW_AXIS_GANTRY_XY_MOVE_VERTICAL_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eVERTICAL_ALIGN_FLOW_UVW_MOVE_CHECK : Time Out !!!"), eVERTICAL_ALIGN_FLOW + 7);
				SetStep(eVERTICAL_ALIGN_FLOW_ERROR, _T("eVERTICAL_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eVERTICAL_ALIGN_FLOW_UVW_MOVE_CHECK, _T("eVERTICAL_ALIGN_FLOW_UVW_MOVE_CHECK"));
			}
			break;

		case eVERTICAL_ALIGN_FLOW_AXIS_Z_FINISH_CAM_UP_POS:
			Devs::m_GantryMotion.Move_GantryZ_All_Wait_Pos();

			//if (GetStepFlag() == TRUE)
			//	break;
			SetStep(eVERTICAL_ALIGN_FLOW_AXIS_Z_FINISH_CAM_UP_POS_CHECK, _T("eVERTICAL_ALIGN_FLOW_AXIS_Z_FINISH_CAM_UP_POS_CHECK"));

			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eVERTICAL_ALIGN_FLOW_AXIS_Z_FINISH_CAM_UP_POS_CHECK:
			if (Devs::m_GantryMotion.Is_GantryZ_All_Wait_Pos() == TRUE)
			{
				SetStep(eVERTICAL_ALIGN_FLOW_DONE, _T("eVERTICAL_ALIGN_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eVERTICAL_ALIGN_FLOW_AXIS_Z_FINISH_CAM_UP_POS_CHECK : Time Out !!!"), eVERTICAL_ALIGN_FLOW + 8);
				SetStep(eVERTICAL_ALIGN_FLOW_ERROR, _T("eVERTICAL_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eVERTICAL_ALIGN_FLOW_AXIS_Z_FINISH_CAM_UP_POS_CHECK, _T("eVERTICAL_ALIGN_FLOW_AXIS_Z_FINISH_CAM_UP_POS_CHECK"));
			}
			break;
		case eVERTICAL_ALIGN_FLOW_DONE:
			m_bFlowDone = TRUE;

			SharedInfo::nPrevFlowID = eVERTICAL_ALIGN_FLOW; //KJT 20210326

			SharedInfo::CalTactTime(_T("VERTICAL_ALIGN_FLOW"), m_timeStart); //KJT 20210329

			SetStep(eVERTICAL_ALIGN_FLOW_IDLE, _T("eVERTICAL_ALIGN_FLOW_IDLE"));
			break;
		}

		Sleep(100); //!!
	}
}

BOOL CVerticalAlignFlow::GetXYTPos(double *dRefPosX, double *dRefPosY, double *dDiffPosX, double *dDiffPosY, double *ResultX, double *ResultY, double *ResultT)
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

	Total_Msg(_T("Vertical Align Result X : %.5f, Y : %.5f, T : %.7f"), *ResultX, *ResultY, *ResultT);

#if 0
	R = sqrt(dRefPosX[0] * dRefPosX[0] + dRefPosY[1] * dRefPosY[1]);
	*dErrorX = fabs(*ResultX) + fabs(R * (*ResultT / (180. / PI) * 2));
	*dErrorY = fabs(*ResultY) + fabs(R * (*ResultT / (180. / PI) * 2));

#endif
	dError = sqrt(*ResultX  * *ResultX + *ResultY * *ResultY);

	//Total_Msg(_T("MFA Align Error X : %.5f, Y : %.5f, E : %.5f"), *dErrorX, *dErrorY, dError);

	return TRUE;
}

BOOL CVerticalAlignFlow::FlowInterlock()
{
	/////////////////////////////////////////////////////////////////////////////
	if (Devs::m_GantryMotion.CheckGantryXYZFlowInterlock(_T("VerticalAlignFlow"), eVERTICAL_ALIGN_FLOW, 30) == FALSE)
	{
		return FALSE;
	}

	//if (Devs::m_CassetteMotion.Is_CSTPickUpUnitBwd() == FALSE)
	//{
	//	Total_Msg(_T("Check Pickup Unit Backward !!!"));
	//	return FALSE;
	//}
	//if (SharedInfo::DInputValue[_DIN_MAGAZINE_SAFETY_POS_DETECT_2] == TRUE)
	//{
	//	Total_Msg(_T("Check CST Unsafe Pos Detect Sensor !!!"));
	//	return FALSE;
	//}
	//if (SharedInfo::DInputValue[_DIN_MAGAZINE_EXIST_DETECT_1] == TRUE)
	//{
	//	Total_Msg(_T("Check CST Backward Detect Sensor !!!"));
	//	return FALSE;
	//}

	return TRUE;
}
