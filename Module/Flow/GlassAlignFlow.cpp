#include "stdafx.h"
#include "GlassAlignFlow.h"
#include "Log/Logger.h"
#include "Vision/Devs.h"
#include "Data/ModelData.h"
#include "CamAreaModul.h"
#include "Data/SystemData.h"
#include "FmmLight1.h"

CGlassAlignFlow::CGlassAlignFlow()
{
	m_dDiffPos[0] = 0.0;
	m_dDiffPos[1] = 0.0;
	m_dDiffPos[2] = 0.0;

	m_dTarget[0] = 0.0;
	m_dTarget[1] = 0.0;
	m_dTarget[2] = 0.0;

	m_nAlignPoint = 0; 
	m_nAlignCnt = 0;
	m_bDirReverse = FALSE;
}

CGlassAlignFlow::~CGlassAlignFlow()
{

}

BOOL CGlassAlignFlow::InitProcess()
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

BOOL CGlassAlignFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(eGLASS_ALIGN_FLOW_IDLE, FALSE);

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

BOOL CGlassAlignFlow::SetHorizontalPosX(double *dPosX, double *dPosY)
{
	memcpy(dHorizontalPosX, dPosX, sizeof(double) * 2);
	memcpy(dHorizontalPosY, dPosY, sizeof(double) * 2);
	return TRUE;
}

BOOL CGlassAlignFlow::SetVerticalPosXY(double *dPosX, double *dPosY)
{
	m_AlignPointValue[0][0] = dPosX[0];
	m_AlignPointValue[1][0] = dPosY[0];

	m_AlignPointValue[0][1] = dPosX[1];
	m_AlignPointValue[1][1] = dPosY[1];
	return TRUE;
}

//21.03.04
BOOL CGlassAlignFlow::GetAlignPos(int nIndex,double *dPosX, double *dPosY)
{
	if (nIndex > 3) return FALSE;

	*dPosY = m_dAlign4PointPos[nIndex][1];
	*dPosX = m_dAlign4PointPos[nIndex][1];

	return TRUE;
}

double CGlassAlignFlow::GetVerticalPos_X_PreAlign(int nAlignCount)
{
	double dPos = m_AlignPointValue[0][nAlignCount] - CSystemData::m_Coordinate.Info.dOffsetReview10xToPreAlign_X;
	return dPos;
}
double CGlassAlignFlow::GetVerticalPos_Y_PreAlign(int nAlignCount)
{
	double dPos = m_AlignPointValue[1][nAlignCount] - CSystemData::m_Coordinate.Info.dOffsetReview10xToPreAlign_Y;
	return dPos;
}
double CGlassAlignFlow::GetVerticalPos_X_Review(int nAlignCount)
{
	double dPos = m_AlignPointValue[0][nAlignCount];
	return dPos;
}
double CGlassAlignFlow::GetVerticalPos_Y_Review(int nAlignCount)
{
	double dPos = m_AlignPointValue[1][nAlignCount];
	return dPos;
}
BOOL CGlassAlignFlow::SetPreAlignUseMode(BOOL bUse)
{
	m_bPreAlignUse = bUse;
	
	m_bPreAlignDone = FALSE;

	return TRUE;
}
BOOL CGlassAlignFlow::StateStop()
{
	SetStop();
	return TRUE;
}
BOOL CGlassAlignFlow::Start()
{
	//SharedInfo::MachineState.bSemiAutoRunFlag = TRUE;
	m_nMappingID = eMAPPING_ID_10X;

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
	SetStep(eGLASS_ALIGN_FLOW_START, _T("eGLASS_ALIGN_FLOW_START"));
	return TRUE;
}

BOOL CGlassAlignFlow::Stop()
{
	m_bStopBit = TRUE;
	SetStop(); //!!
	//SharedInfo::MachineState.bSemiAutoRunFlag = FALSE;
	return TRUE;
}


UINT CGlassAlignFlow::ThreadFunction(LPVOID lpParam)
{
	CGlassAlignFlow* pVerticalAlign = NULL;

	pVerticalAlign = (CGlassAlignFlow*)lpParam;

	pVerticalAlign->ThreadFunctionEntry();

	pVerticalAlign->m_bTerminate = 1;

	return 0;
}



VOID CGlassAlignFlow::ThreadFunctionEntry(VOID)
{
	int ErrorCheck = 0;
	CString szMsg;
	BOOL bResult;

	double RefT[2] = { 0, }, NewPositionT[2] = { 0, }, DiffT[2] = { 0, }, DiffPosition[3] = { 0, };
	double dUVWX[3];
	double TargetError = 0.;
	double dError;
	double pPosX[2];

	double dVel[3] = { 0.1,0.1,0.1 };
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

			SetCurrentStep(eGLASS_ALIGN_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}

		
		int nVal[BACKLIGHT_CH_COUNT] = { BACKLIGHT_OFF_VALUE, };
		switch (GetCurrentTotalStep())
		{
		case eGLASS_ALIGN_FLOW_IDLE:
			break;

		case eGLASS_ALIGN_FLOW_START:

			m_timeStart = CTime::GetCurrentTime(); //KJT 20210329

			//LB
			m_AlignPointValue[0][0] = CModelData::m_GlassPara.Info.dGlassAlignMark_LB_X;
			m_AlignPointValue[1][0] = CModelData::m_GlassPara.Info.dGlassAlignMark_LB_Y;
			//LT
			m_AlignPointValue[0][1] = CModelData::m_GlassPara.Info.dGlassAlignMark_LT_X; //-397.33766;
			m_AlignPointValue[1][1] = CModelData::m_GlassPara.Info.dGlassAlignMark_LT_Y; //35.53009;
			//RT
			m_AlignPointValue[0][2] = CModelData::m_GlassPara.Info.dGlassAlignMark_RT_X; //397.33766;
			m_AlignPointValue[1][2] = CModelData::m_GlassPara.Info.dGlassAlignMark_RT_Y; //35.53009;
			//RB
			m_AlignPointValue[0][3] = CModelData::m_GlassPara.Info.dGlassAlignMark_RB_X; //397.33766;
			m_AlignPointValue[1][3] = CModelData::m_GlassPara.Info.dGlassAlignMark_RB_Y; //-35.53009;

		
			SharedInfo::LightAllOff(); //KJT 20210311

			m_nAlignPoint = 0;
			m_nAlignCnt = 0;
			m_bDirReverse = FALSE;

			SetStep(eGLASS_ALIGN_FLOW_INTERLOCK, _T("eGLASS_ALIGN_FLOW_INTERLOCK"));
			break;

		case eGLASS_ALIGN_FLOW_INTERLOCK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(eGLASS_ALIGN_FLOW_ERROR, _T("eGLASS_ALIGN_FLOW_ERROR"));
			}
			else
			{
				if (m_bPreAlignUse == TRUE && m_bPreAlignDone == FALSE)
				{
					SharedInfo::nGantryZ1View = eViewPreAlign;
					
					if (CModelData::m_AlignPara.Info.nVerticalPreAlignLightType == eLight_Back)
					{
						SharedInfo::BackLightOn(CModelData::m_AlignPara.Info.nVerticalPreAlignBackLight);						
					}
					else
					{
						g_CommZomm_Coaxial.SetLight_Zoom_Coaxial(CModelData::m_AlignPara.Info.nVerticalPreAlignCoAxial);
						Sleep(10);
						g_CommZomm_Coaxial.Zoom_Light_On(TRUE);
						Sleep(10);
						g_CommZomm_Ring.SetLight_Zoom_Ring(CModelData::m_AlignPara.Info.nVerticalPreAlignRing);
						Sleep(10);
						g_CommZomm_Ring.Zoom_Light_On(TRUE);

						g_CommLoader_Light.SetLight_PreAlign(CModelData::m_AlignPara.Info.nVerticalPreAlignCoAxial, CModelData::m_AlignPara.Info.nVerticalPreAlignRing); //KJT 20210728
					}

					//g_CommLight_8ch.SetLight_PreAlign(CModelData::m_AlignPara.Info.nVerticalPreAlignCoAxial, CModelData::m_AlignPara.Info.nVerticalPreAlignRing);
				}
				else
				{
					SharedInfo::nGantryZ1View = eViewReview10X;

					if (CModelData::m_AlignPara.Info.nVerticalMainAlignLightType == eLight_Back)
					{
						SharedInfo::BackLightOn(CModelData::m_AlignPara.Info.nVerticalMainAlignBackLight);						
					}
					else
					{
						g_CommReview_Light.SetLight_Review(CModelData::m_AlignPara.Info.nVerticalMainAlignRing, CModelData::m_AlignPara.Info.nVerticalMainAlignCoAxial);
					}
					
					//g_CommLight_8ch.SetLight_Review_Coaxial(CModelData::m_AlignPara.Info.nVerticalMainAlignCoAxial);
					//Sleep(20);
					//g_CommLight_12ch.SetLight_Review_Ring(CModelData::m_AlignPara.Info.nVerticalMainAlignRing);
				}

				SetStep(eGLASS_ALIGN_FLOW_UNLOADER_READY, _T("eGLASS_ALIGN_FLOW_UNLOADER_READY"));
			}
			break;

#pragma region //Unloader Ready
		case eGLASS_ALIGN_FLOW_UNLOADER_READY:
			Devs::m_Ready_UnloaderFlow.Start();

			SetStep(eGLASS_ALIGN_FLOW_UNLOADER_READY_CHECK, _T("eGLASS_ALIGN_FLOW_UNLOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eGLASS_ALIGN_FLOW_UNLOADER_READY_CHECK:
			if (Devs::m_Ready_UnloaderFlow.IsFlowDone())
			{
				SetStep(eGLASS_ALIGN_FLOW_GANTRY_ZX_READY, _T("eGLASS_ALIGN_FLOW_GANTRY_ZX_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eGLASS_ALIGN_FLOW_UNLOADER_READY_CHECK : Time Out"), eGLASS_4P_ALIGN_FLOW + 0);
				SetStep(eGLASS_ALIGN_FLOW_ERROR, _T("eGLASS_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eGLASS_ALIGN_FLOW_UNLOADER_READY_CHECK, _T("eGLASS_ALIGN_FLOW_UNLOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Gantry Z,X Ready
		case eGLASS_ALIGN_FLOW_GANTRY_ZX_READY:
			Devs::m_Ready_GantryZX_Flow.Start();

			SetStep(eGLASS_ALIGN_FLOW_GANTRY_ZX_READY_CHECK, _T("eGLASS_ALIGN_FLOW_GANTRY_ZX_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eGLASS_ALIGN_FLOW_GANTRY_ZX_READY_CHECK:
			if (Devs::m_Ready_GantryZX_Flow.IsFlowDone())
			{
				SetStep(eGLASS_ALIGN_FLOW_LOADER_READY, _T("eGLASS_ALIGN_FLOW_LOADER_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eGLASS_ALIGN_FLOW_GANTRY_ZX_READY_CHECK : Time Out"), eGLASS_4P_ALIGN_FLOW + 2);
				SetStep(eGLASS_ALIGN_FLOW_ERROR, _T("eGLASS_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eGLASS_ALIGN_FLOW_GANTRY_ZX_READY_CHECK, _T("eGLASS_ALIGN_FLOW_GANTRY_ZX_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Loader Ready
		case eGLASS_ALIGN_FLOW_LOADER_READY:
			Devs::m_Ready_LoaderFlow.Start();

			SetStep(eGLASS_ALIGN_FLOW_LOADER_READY_CHECK, _T("eGLASS_ALIGN_FLOW_LOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eGLASS_ALIGN_FLOW_LOADER_READY_CHECK:
			if (Devs::m_Ready_LoaderFlow.IsFlowDone())
			{
				SetStep(eGLASS_ALIGN_FLOW_PAPER_UNLOADER_ZXY_READY, _T("eGLASS_ALIGN_FLOW_PAPER_UNLOADER_ZXY_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eGLASS_ALIGN_FLOW_LOADER_READY_CHECK : Time Out"), eGLASS_4P_ALIGN_FLOW + 1);
				SetStep(eGLASS_ALIGN_FLOW_ERROR, _T("eGLASS_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eGLASS_ALIGN_FLOW_LOADER_READY_CHECK, _T("eGLASS_ALIGN_FLOW_LOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //PaperUnloader Ready
		case eGLASS_ALIGN_FLOW_PAPER_UNLOADER_ZXY_READY:
			Devs::m_Ready_PaperUnloaderFlow.Start();

			SetStep(eGLASS_ALIGN_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK, _T("eGLASS_ALIGN_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eGLASS_ALIGN_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK:
			if (Devs::m_Ready_PaperUnloaderFlow.IsFlowDone())
			{
				m_nAlignPoint = 0;
				m_nAlignCnt = 0;

				//sunghaklee
				if (m_bPreAlignUse == TRUE && m_bPreAlignDone == FALSE)
				{
					m_dTarget[0] = CModelData::m_AlignPara.Info.dVerticalPreAlignTargetX;// CModelData::m_GlassPara.Info.dGlassPreAlignTargetX;
					m_dTarget[1] = CModelData::m_AlignPara.Info.dVerticalPreAlignTargetY;// CModelData::m_GlassPara.Info.dGlassPreAlignTargetY;
					m_dTarget[2] = 0.001;// CModelData::m_GlassPara.Info.dGlassPreAlignTargetT;

					SetStep(eGLASS_ALIGN_FLOW_AXIS_GANTRY_PRE_ALIGN_XY_POS, _T("eGLASS_ALIGN_FLOW_AXIS_GANTRY_PRE_ALIGN_XY_POS"));
				}
				else
				{
					m_dTarget[0] = CModelData::m_AlignPara.Info.dVerticalMainAlignTargetX;// CModelData::m_GlassPara.Info.dGlassMainAlignTargetX;
					m_dTarget[1] = CModelData::m_AlignPara.Info.dVerticalMainAlignTargetY;// CModelData::m_GlassPara.Info.dGlassMainAlignTargetY;
					m_dTarget[2] = 0.001;/// CModelData::m_GlassPara.Info.dGlassMainAlignTargetT;

					SetStep(eGLASS_ALIGN_FLOW_AXIS_GANTRY_XY_MOVE_1ST_ALIGN_POS, _T("eGLASS_ALIGN_FLOW_AXIS_GANTRY_XY_MOVE_1ST_ALIGN_POS"));
				}
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eGLASS_ALIGN_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK : Time Out"), eBOX_ALIGN_FLOW + 1);
				SetStep(eGLASS_ALIGN_FLOW_ERROR, _T("eGLASS_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eGLASS_ALIGN_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK, _T("eGLASS_ALIGN_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK"));
			}
			break;
#pragma endregion

		case eGLASS_ALIGN_FLOW_AXIS_GANTRY_PRE_ALIGN_XY_POS:
			if (CModelData::m_AlignPara.Info.nVerticalPreAlignLightType == eLight_Back)
			{
				Devs::m_GantryMotion.Move_Gantry_X_Pos(GetVerticalPos_X_PreAlign(m_nAlignPoint), TRUE, CSystemData::m_Coordinate.Info.dOffsetReview10xToPreAlign_X);
				Sleep(10);
				Devs::m_GantryMotion.Move_Gantry_Y_Pos(GetVerticalPos_Y_PreAlign(m_nAlignPoint));
			}
			else
			{
				Devs::m_GantryMotion.Move_Gantry_X_Pos(GetVerticalPos_X_PreAlign(m_nAlignPoint), FALSE);
				Sleep(10);
				Devs::m_GantryMotion.Move_Gantry_Y_Pos(GetVerticalPos_Y_PreAlign(m_nAlignPoint));
			}

			SetStep(eGLASS_ALIGN_FLOW_AXIS_GANTRY_PRE_ALIGN_XY_POS_CHECK, _T("eGLASS_ALIGN_FLOW_AXIS_GANTRY_PRE_ALIGN_XY_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eGLASS_ALIGN_FLOW_AXIS_GANTRY_PRE_ALIGN_XY_POS_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Pos(GetVerticalPos_X_PreAlign(m_nAlignPoint)) && Devs::m_GantryMotion.Is_Gantry_Y_Pos(GetVerticalPos_Y_PreAlign(m_nAlignPoint)))
			{
				SetStep(eGLASS_ALIGN_FLOW_AXIS_Z_PRE_ALGIN_CAM_DOWN_POS, _T("eGLASS_ALIGN_FLOW_AXIS_Z_PRE_ALGIN_CAM_DOWN_POS"));
			}			
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eGLASS_ALIGN_FLOW_AXIS_GANTRY_PRE_ALIGN_XY_POS_CHECK : Time Out"), eGLASS_4P_ALIGN_FLOW + 3);
				SetStep(eGLASS_ALIGN_FLOW_ERROR, _T("eGLASS_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eGLASS_ALIGN_FLOW_AXIS_GANTRY_PRE_ALIGN_XY_POS_CHECK);
			}
			break;

#pragma region //PreAlign Camera
		case eGLASS_ALIGN_FLOW_AXIS_Z_PRE_ALGIN_CAM_DOWN_POS:
			Devs::m_GantryMotion.Move_GantryZ1_PreAlign_Pos();

			SetStep(eGLASS_ALIGN_FLOW_AXIS_Z_PRE_ALGIN_CAM_DOWN_POS_CHECK, _T("eGLASS_ALIGN_FLOW_AXIS_Z_PRE_ALGIN_CAM_DOWN_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eGLASS_ALIGN_FLOW_AXIS_Z_PRE_ALGIN_CAM_DOWN_POS_CHECK:
			if (Devs::m_GantryMotion.Is_GantryZ1_PreAlign_Pos() == TRUE)
			{
				SetStep(eGLASS_ALIGN_FLOW_GRAB_START, _T("eGLASS_ALIGN_FLOW_GRAB_START"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eGLASS_ALIGN_FLOW_AXIS_Z_PRE_ALGIN_CAM_DOWN_POS_CHECK : Time Out"), eGLASS_4P_ALIGN_FLOW + 4);
				SetStep(eGLASS_ALIGN_FLOW_ERROR, _T("eGLASS_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eGLASS_ALIGN_FLOW_AXIS_Z_PRE_ALGIN_CAM_DOWN_POS_CHECK);
			}
			break;

		case eGLASS_ALIGN_FLOW_AXIS_Z_PRE_ALGIN_CAM_UP_POS:
			Devs::m_GantryMotion.Move_GantryZ_All_Wait_Pos();
			
			SetStep(eGLASS_ALIGN_FLOW_AXIS_Z_PRE_ALGIN_CAM_UP_POS_CHECK, _T("eGLASS_ALIGN_FLOW_AXIS_Z_PRE_ALGIN_CAM_UP_POS_CHECK"));

			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eGLASS_ALIGN_FLOW_AXIS_Z_PRE_ALGIN_CAM_UP_POS_CHECK:
			if (Devs::m_GantryMotion.Is_GantryZ_All_Wait_Pos() == TRUE)
			{
				SharedInfo::LightAllOff(); //KJT 20210311

				SharedInfo::nGantryZ1View = eViewReview10X;

				if (CModelData::m_AlignPara.Info.nVerticalMainAlignLightType == eLight_Back)
				{
					SharedInfo::BackLightOn(CModelData::m_AlignPara.Info.nVerticalMainAlignBackLight);
				}
				else
				{
					g_CommReview_Light.SetLight_Review(CModelData::m_AlignPara.Info.nVerticalMainAlignRing, CModelData::m_AlignPara.Info.nVerticalMainAlignCoAxial);
				}				
				
				m_dTarget[0] = CModelData::m_AlignPara.Info.dVerticalMainAlignTargetX;// CModelData::m_GlassPara.Info.dGlassMainAlignTargetX;
				m_dTarget[1] = CModelData::m_AlignPara.Info.dVerticalMainAlignTargetY;// CModelData::m_GlassPara.Info.dGlassMainAlignTargetY;
				m_dTarget[2] = 0.001;// CModelData::m_GlassPara.Info.dGlassMainAlignTargetT;

				SetStep(eGLASS_ALIGN_FLOW_AXIS_GANTRY_XY_MOVE_1ST_ALIGN_POS, _T("eGLASS_ALIGN_FLOW_AXIS_GANTRY_XY_MOVE_1ST_ALIGN_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eGLASS_ALIGN_FLOW_AXIS_Z_PRE_ALGIN_CAM_UP_POS_CHECK : Time Out"), eGLASS_4P_ALIGN_FLOW + 5);
				SetStep(eGLASS_ALIGN_FLOW_ERROR, _T("eGLASS_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eGLASS_ALIGN_FLOW_AXIS_Z_PRE_ALGIN_CAM_UP_POS_CHECK, _T("eGLASS_ALIGN_FLOW_AXIS_Z_PRE_ALGIN_CAM_UP_POS_CHECK"));
			}
			break;

#pragma endregion

#pragma endregion
		case eGLASS_ALIGN_FLOW_AXIS_GANTRY_XY_MOVE_1ST_ALIGN_POS:
			m_nAlignPoint = 0;
			m_nAlignCnt = 0;

			if (CModelData::m_AlignPara.Info.nVerticalMainAlignLightType == eLight_Back)
			{
				Devs::m_GantryMotion.Move_GantryXY_ReviewGlassAlignPos(0, TRUE);
			}
			else
			{
				Devs::m_GantryMotion.Move_GantryXY_ReviewGlassAlignPos(0);
			}

			Sleep(10);
			SetStep(eGLASS_ALIGN_FLOW_AXIS_GANTRY_XY_MOVE_1ST_ALIGN_POS_CHECK, _T("eGLASS_ALIGN_FLOW_AXIS_GANTRY_XY_MOVE_1ST_ALIGN_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;
		case eGLASS_ALIGN_FLOW_AXIS_GANTRY_XY_MOVE_1ST_ALIGN_POS_CHECK:
			if (Devs::m_GantryMotion.Is_GantryXY_ReviewGlassAlignPos(0))
			{
				//m_nAlignPoint=1;
				SetStep(eGLASS_ALIGN_FLOW_AXIS_Z_REVIEW10X_CAM_DOWN_POS, _T("eGLASS_ALIGN_FLOW_AXIS_Z_REVIEW10X_CAM_DOWN_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eGLASS_ALIGN_FLOW_AXIS_GANTRY_XY_MOVE_1ST_ALIGN_POS_CHECK : Time Out"), eGLASS_4P_ALIGN_FLOW + 6);
				SetStep(eGLASS_ALIGN_FLOW_ERROR, _T("eGLASS_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eGLASS_ALIGN_FLOW_AXIS_GANTRY_XY_MOVE_1ST_ALIGN_POS_CHECK, _T("eGLASS_ALIGN_FLOW_AXIS_GANTRY_XY_MOVE_1ST_ALIGN_POS_CHECK"));
			}
			break;
#pragma region //Review 10X
		case eGLASS_ALIGN_FLOW_AXIS_Z_REVIEW10X_CAM_DOWN_POS:
			Devs::m_GantryMotion.Move_GantryZ1_InspectionMapping_Pos();

			SetStep(eGLASS_ALIGN_FLOW_AXIS_Z_REVIEW10X_CAM_DOWN_POS_CHECK, _T("eGLASS_ALIGN_FLOW_AXIS_Z_REVIEW10X_CAM_DOWN_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eGLASS_ALIGN_FLOW_AXIS_Z_REVIEW10X_CAM_DOWN_POS_CHECK:
			if (Devs::m_GantryMotion.Is_GantryZ1_InspectionMapping_Pos() == TRUE)
			{
				//g_CommReview_Light.SetLight_Review(CModelData::m_GlassPara.Info.nBrightness10XRing, CModelData::m_GlassPara.Info.nBrightness10XCoaxial);

				Sleep(500); //!!
				if (m_bLaserFocusUseFlag == TRUE)
					SetStep(eGLASS_ALIGN_FLOW_AXIS_Z_REVIEW10X_LASER_FOCUS_START, _T("eGLASS_ALIGN_FLOW_AXIS_Z_REVIEW10X_LASER_FOCUS_START"));
				else if (m_bAutoFocusUseFlag == TRUE)
					SetStep(eGLASS_ALIGN_FLOW_AXIS_Z_REVIEW10X_IMAGE_FOCUS_START, _T("eGLASS_ALIGN_FLOW_AXIS_Z_REVIEW10X_IMAGE_FOCUS_START"));
				else
					SetStep(eGLASS_ALIGN_FLOW_GRAB_START, _T("eGLASS_ALIGN_FLOW_GRAB_START"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eGLASS_ALIGN_FLOW_AXIS_Z_REVIEW10X_CAM_DOWN_POS_CHECK : Time Out"), eGLASS_4P_ALIGN_FLOW + 7);
				SetStep(eGLASS_ALIGN_FLOW_ERROR, _T("eGLASS_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eGLASS_ALIGN_FLOW_AXIS_Z_REVIEW10X_CAM_DOWN_POS_CHECK);
			}
			break;

		case eGLASS_ALIGN_FLOW_AXIS_Z_REVIEW10X_LASER_FOCUS_START:
			Devs::m_GantryMotion.LaserFocusMove(1);//Glass

			SetStep(eGLASS_ALIGN_FLOW_AXIS_Z_REVIEW10X_LASER_FOCUS_CHECK, _T("eGLASS_ALIGN_FLOW_AXIS_Z_REVIEW10X_LASER_FOCUS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eGLASS_ALIGN_FLOW_AXIS_Z_REVIEW10X_LASER_FOCUS_CHECK:
			if (Devs::m_GantryMotion.LaserFocusMoveCheck())
			{
				if (m_bAutoFocusUseFlag == TRUE)
					SetStep(eGLASS_ALIGN_FLOW_AXIS_Z_REVIEW10X_IMAGE_FOCUS_START, _T("eGLASS_ALIGN_FLOW_AXIS_Z_REVIEW10X_IMAGE_FOCUS_START"));
				else
					SetStep(eGLASS_ALIGN_FLOW_GRAB_START, _T("eGLASS_ALIGN_FLOW_GRAB_START"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eGLASS_ALIGN_FLOW_AXIS_Z_REVIEW10X_LASER_FOCUS_CHECK : Time Out"), eGLASS_4P_ALIGN_FLOW + 8);
				SetStep(eGLASS_ALIGN_FLOW_ERROR, _T("eGLASS_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eGLASS_ALIGN_FLOW_AXIS_Z_REVIEW10X_LASER_FOCUS_CHECK, _T("eGLASS_ALIGN_FLOW_AXIS_Z_REVIEW10X_LASER_FOCUS_CHECK"));
			}
			break;

		case eGLASS_ALIGN_FLOW_AXIS_Z_REVIEW10X_IMAGE_FOCUS_START:
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
				Sleep(500);
#ifndef SIM_MODE
				g_pReview10x->m_bAfEnd = FALSE;
				g_pReview10x->AutofoucsRun();
#endif
				break;

//			case eMAPPING_ID_PreAlign:
//				//g_CommLight_8ch.SetLight_PreAlign(CModelData::m_AlignPara.Info.nPreAlignCoAxial_L, CModelData::m_AlignPara.Info.nPreAlignRing_L);
//				g_CommZomm_Coaxial.SetLight_Zoom_Coaxial(CModelData::m_AlignPara.Info.nPreAlignCoAxial_L);
//				Sleep(10);
//				g_CommZomm_Coaxial.Zoom_Light_On(TRUE);
//				Sleep(10);
//				g_CommZomm_Ring.SetLight_Zoom_Ring(CModelData::m_AlignPara.Info.nPreAlignRing_L);
//				Sleep(10);
//				g_CommZomm_Ring.Zoom_Light_On(TRUE);
//				Sleep(500);
//#ifndef SIM_MODE
//				g_pPreAlign->m_bAfEnd = TRUE;
//				//g_pPreAlign->AutofoucsRun();
//#endif
//				break;
			}
#endif

			SetStep(eGLASS_ALIGN_FLOW_AXIS_Z_REVIEW10X_IMAGE_FOCUS_CHECK, _T("eGLASS_ALIGN_FLOW_AXIS_Z_REVIEW10X_IMAGE_FOCUS_CHECK"));
			SetTimeOut(TIME_OUT_DUAL);
			break;

		case eGLASS_ALIGN_FLOW_AXIS_Z_REVIEW10X_IMAGE_FOCUS_CHECK:
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
//			case eMAPPING_ID_PreAlign:
//#ifndef SIM_MODE
//				if (g_pPreAlign->m_bAfEnd == TRUE)
//#endif
//				{
//					bResult = TRUE;
//				}
//				break;
			}
#else
			bResult = TRUE;
#endif
			if (bResult == TRUE)
			{
				m_nGrabRetryCnt = 0;
				Sleep(IMAGE_FOCUS_DELAY);
				SetStep(eGLASS_ALIGN_FLOW_GRAB_START, _T("eGLASS_ALIGN_FLOW_GRAB_START"));

			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eGLASS_ALIGN_FLOW_AXIS_Z_REVIEW10X_IMAGE_FOCUS_CHECK : Time Out"), eGLASS_4P_ALIGN_FLOW + 9);
				SetStep(eGLASS_ALIGN_FLOW_ERROR, _T("eGLASS_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eGLASS_ALIGN_FLOW_AXIS_Z_REVIEW10X_IMAGE_FOCUS_CHECK, _T("eGLASS_ALIGN_FLOW_AXIS_Z_REVIEW10X_IMAGE_FOCUS_CHECK"));
			}
			break;
#pragma endregion //Review10X

		case eGLASS_ALIGN_FLOW_GRAB_START:
			Sleep(1000);
			if (m_bPreAlignUse == TRUE && m_bPreAlignDone == FALSE)
			{
				bResult = Devs::m_GantryMotion.FindVerticalBlob_PreAlign(&m_AlignVisionResultValue[0][m_nAlignPoint], &m_AlignVisionResultValue[1][m_nAlignPoint]);
			}
			else
			{
				bResult = Devs::m_GantryMotion.FindVerticalBlob_Review10X(&m_AlignVisionResultValue[0][m_nAlignPoint], &m_AlignVisionResultValue[1][m_nAlignPoint]);
			}

			if (bResult == FALSE)
			{
				Total_Msg(_T("Image Grab Error"));
				SharedInfo::SetAlarm(_T("eGLASS_ALIGN_FLOW_GRAB_START : Find Hole"), eGLASS_4P_ALIGN_FLOW + 10);
				SetStep(eGLASS_ALIGN_FLOW_ERROR, _T("eGLASS_ALIGN_FLOW_ERROR"));
				break;
			}

			//m_AlignPointValue[0][m_nAlignPoint] = m_AlignVisionResultValue[0][m_nAlignPoint];
			//m_AlignPointValue[1][m_nAlignPoint] = m_AlignVisionResultValue[1][m_nAlignPoint];
			SetStep(eGLASS_ALIGN_FLOW_GRAB_CHECK, _T("eGLASS_ALIGN_FLOW_GRAB_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;
		case eGLASS_ALIGN_FLOW_GRAB_CHECK:
			if (m_nAlignPoint == 3)
			{
				szMsg.Format(_T("AlignCurCount:%d Diff X[0]:%.5f, Y[0]:%.5f, X[1]:%.5f, Y[1]:%.5f, X[2]:%.5f, Y[2]:%.5f, X[3]:%.5f, Y[3]:%.5f"),
				m_nAlignCnt,
				m_AlignVisionResultValue[0][0], m_AlignVisionResultValue[1][0], m_AlignVisionResultValue[0][1], m_AlignVisionResultValue[1][1],
				m_AlignVisionResultValue[0][2], m_AlignVisionResultValue[1][2], m_AlignVisionResultValue[0][3], m_AlignVisionResultValue[1][3]);
				//Total_Msg(szMsg);
				Vision_Msg(szMsg);

				m_nAlignPoint = 0;
				szMsg.Format(_T("next Align Point %d"), m_nAlignPoint + 1);
				Total_Msg(szMsg);

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
				szMsg.Format(_T("Uvw Diff Pos X:%.5f, Y:%.5f, T:%.5f"), m_dDiffPos[0], m_dDiffPos[1], m_dDiffPos[2]);
				Total_Msg(szMsg);

				if (fabs(m_dDiffPos[0]) <= m_dTarget[0] && fabs(m_dDiffPos[1]) <= m_dTarget[1] && fabs(m_dDiffPos[2]) <= m_dTarget[2])
				{
					//21.03.05 sjc temp del
					//if (0)
					//{
						//UpdateSwAlignData(); //SWMapping //Only One
					//}

					if (m_bPreAlignUse == TRUE && m_bPreAlignDone == FALSE)
					{			
						m_bPreAlignUse = FALSE;
						m_bPreAlignDone = TRUE;
						SetStep(eGLASS_ALIGN_FLOW_AXIS_Z_PRE_ALGIN_CAM_UP_POS, _T("eGLASS_ALIGN_FLOW_AXIS_Z_PRE_ALGIN_CAM_UP_POS"));
						break;
					}
					else
					{
						SetStep(eGLASS_ALIGN_FLOW_AXIS_Z_FINISH_CAM_UP_POS, _T("eGLASS_ALIGN_FLOW_AXIS_Z_FINISH_CAM_UP_POS"));
					}
				}
				else
				{
					m_nAlignCnt++;
					SetStep(eGLASS_ALIGN_FLOW_UVW_MOVE_START, _T("eGLASS_ALIGN_FLOW_UVW_MOVE_START"));
				}
			}
			else
			{
				m_nAlignPoint++;
				szMsg.Format(_T("next Align Point %d"), m_nAlignPoint + 1);
				Total_Msg(szMsg);

				//sunghaklee
				if (m_bPreAlignUse == TRUE && m_bPreAlignDone == FALSE)
				{
					SetStep(eGLASS_ALIGN_FLOW_AXIS_GANTRY_PRE_ALIGN_XY_POS, _T("eGLASS_ALIGN_FLOW_AXIS_GANTRY_PRE_ALIGN_XY_POS"));
				}
				else
				{
					SetStep(eGLASS_ALIGN_FLOW_AXIS_GANTRY_XY_MOVE_ALIGN_POS, _T("eGLASS_ALIGN_FLOW_AXIS_GANTRY_XY_MOVE_ALIGN_POS"));
				}
			}
			break;

		case eGLASS_ALIGN_FLOW_AXIS_GANTRY_XY_MOVE_ALIGN_POS:
			if (CModelData::m_AlignPara.Info.nVerticalMainAlignLightType == eLight_Back)
			{
				Devs::m_GantryMotion.Move_GantryXY_ReviewGlassAlignPos(m_nAlignPoint, TRUE);
			}
			else
			{
				Devs::m_GantryMotion.Move_GantryXY_ReviewGlassAlignPos(m_nAlignPoint);
			}

			Sleep(10);
			SetStep(eGLASS_ALIGN_FLOW_AXIS_GANTRY_XY_MOVE_ALIGN_POS_CHECK, _T("eGLASS_ALIGN_FLOW_AXIS_GANTRY_XY_MOVE_ALIGN_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eGLASS_ALIGN_FLOW_AXIS_GANTRY_XY_MOVE_ALIGN_POS_CHECK:
			if (Devs::m_GantryMotion.Is_GantryXY_ReviewGlassAlignPos(m_nAlignPoint))
			{
				SetStep(eGLASS_ALIGN_FLOW_AXIS_Z_REVIEW10X_CAM_DOWN_POS, _T("eGLASS_ALIGN_FLOW_AXIS_Z_REVIEW10X_CAM_DOWN_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eGLASS_ALIGN_FLOW_AXIS_GANTRY_XY_MOVE_ALIGN_POS_CHECK : Time Out"), eGLASS_4P_ALIGN_FLOW + 11);
				SetStep(eGLASS_ALIGN_FLOW_ERROR, _T("eGLASS_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eGLASS_ALIGN_FLOW_AXIS_GANTRY_XY_MOVE_ALIGN_POS_CHECK, _T("eGLASS_ALIGN_FLOW_AXIS_GANTRY_XY_MOVE_ALIGN_POS_CHECK"));
			}
			break;

		case eGLASS_ALIGN_FLOW_UVW_MOVE_START:
		{
			//KJT 20200830
			double dRefPos[4][2] = { 0.0, };
			double dActPos[4][2] = { 0.0, };
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

						
			Devs::m_InspectionStageMotion.UVWStageAlignMove(_e4Point_Align_Mode, dRefPos, dActPos);
			Sleep(1000); //!!

			SetStep(eGLASS_ALIGN_FLOW_UVW_MOVE_CHECK, _T("eGLASS_ALIGN_FLOW_UVW_MOVE_CHECK"));
		}
			break;

		case eGLASS_ALIGN_FLOW_UVW_MOVE_CHECK:
			if (Devs::m_InspectionStageMotion.IsUVWStagePos(m_dDiffPos) == TRUE)
			{
				if (m_bPreAlignUse == TRUE && m_bPreAlignDone == FALSE)
				{
					SetStep(eGLASS_ALIGN_FLOW_AXIS_GANTRY_PRE_ALIGN_XY_POS, _T("eGLASS_ALIGN_FLOW_AXIS_GANTRY_PRE_ALIGN_XY_POS"));
				}
				else
				{
					SetStep(eGLASS_ALIGN_FLOW_AXIS_GANTRY_XY_MOVE_ALIGN_POS, _T("eGLASS_ALIGN_FLOW_AXIS_GANTRY_XY_MOVE_ALIGN_POS"));
				}
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eGLASS_ALIGN_FLOW_UVW_MOVE_CHECK : Time Out"), eGLASS_4P_ALIGN_FLOW + 12);
				SetStep(eGLASS_ALIGN_FLOW_ERROR, _T("eGLASS_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eGLASS_ALIGN_FLOW_UVW_MOVE_CHECK, _T("eGLASS_ALIGN_FLOW_UVW_MOVE_CHECK"));
			}
			break;

		case eGLASS_ALIGN_FLOW_AXIS_Z_FINISH_CAM_UP_POS:
			Devs::m_GantryMotion.Move_GantryZ_All_Wait_Pos();
			
			//if (GetStepFlag() == TRUE)
			//	break;
			SetStep(eGLASS_ALIGN_FLOW_AXIS_Z_FINISH_CAM_UP_POS_CHECK, _T("eGLASS_ALIGN_FLOW_AXIS_Z_FINISH_CAM_UP_POS_CHECK"));

			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eGLASS_ALIGN_FLOW_AXIS_Z_FINISH_CAM_UP_POS_CHECK:
			if (Devs::m_GantryMotion.Is_GantryZ_All_Wait_Pos() == TRUE)
			{
				g_CommReview_Light.SetLight_Review(0, 0);
				SetStep(eGLASS_ALIGN_FLOW_DONE, _T("eGLASS_ALIGN_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eGLASS_ALIGN_FLOW_AXIS_Z_FINISH_CAM_UP_POS_CHECK : Time Out"), eGLASS_4P_ALIGN_FLOW + 13);
				SetStep(eGLASS_ALIGN_FLOW_ERROR, _T("eGLASS_ALIGN_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eGLASS_ALIGN_FLOW_AXIS_Z_FINISH_CAM_UP_POS_CHECK, _T("eGLASS_ALIGN_FLOW_AXIS_Z_FINISH_CAM_UP_POS_CHECK"));
			}
			break;

		case eGLASS_ALIGN_FLOW_DONE:
			SharedInfo::LightAllOff();

			m_bFlowDone = TRUE;

			SharedInfo::CalTactTime(_T("eGLASS_ALIGN_FLOW"), m_timeStart); //KJT 20210329

			SetStep(eGLASS_ALIGN_FLOW_IDLE, _T("eGLASS_ALIGN_FLOW_IDLE"));
			break;

		case eGLASS_ALIGN_FLOW_EXIT:
			break;


		}

		Sleep(100); //!!
	}
}

BOOL CGlassAlignFlow::GetXYTPos(double *dRefPosX, double *dRefPosY, double *dDiffPosX, double *dDiffPosY, double *ResultX, double *ResultY, double *ResultT)
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

BOOL CGlassAlignFlow::FlowInterlock()
{
	/////////////////////////////////////////////////////////////////////////////
	if (Devs::m_GantryMotion.CheckGantryXYZFlowInterlock(_T("GlassAlignFlow"), eGLASS_4P_ALIGN_FLOW, 30) == FALSE)
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
