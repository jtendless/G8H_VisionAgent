#include "stdafx.h"
#include "RightAngleFlow.h"
#include "Log/Logger.h"
#include "Vision/Devs.h"
#include "Data/ModelData.h"
#include "CamAreaModul.h"
#include "Data/SystemData.h"
#include "FmmLight1.h"

CRightAngleFlow::CRightAngleFlow()
{
	m_dDiffPos[0] = 0.0;
	m_dDiffPos[1] = 0.0;
	m_dDiffPos[2] = 0.0;

	m_nAlignPoint = 0;
	m_bDirReverse = FALSE;
}


CRightAngleFlow::~CRightAngleFlow()
{
}

BOOL CRightAngleFlow::InitProcess()
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


BOOL CRightAngleFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(eRIGHT_ANGLE_FLOW_IDLE, _T("eRIGHT_ANGLE_FLOW_IDLE"));

	if (hHandle != NULL)
	{
		CloseHandle(hHandle);
		hHandle = NULL;
	}

	return TRUE;
}

double CRightAngleFlow::GetRightAnglePos_X_PreAlign(int nAlignCount)
{
	double dPos = m_AlignPointValue[0][nAlignCount] - CSystemData::m_Coordinate.Info.dOffsetReview10xToPreAlign_X;
	return dPos;
}
double CRightAngleFlow::GetRightAnglePos_Y_PreAlign(int nAlignCount)
{
	double dPos = m_AlignPointValue[1][nAlignCount] - CSystemData::m_Coordinate.Info.dOffsetReview10xToPreAlign_Y;
	return dPos;
}
double CRightAngleFlow::GetRightAnglePos_X_Review(int nAlignCount)
{
	double dPos = m_AlignPointValue[0][nAlignCount];
	return dPos;
}
double CRightAngleFlow::GetRightAnglePos_Y_Review(int nAlignCount)
{
	double dPos = m_AlignPointValue[1][nAlignCount];
	return dPos;
}
void CRightAngleFlow::SetPreAlignUseMode(BOOL bUse/*= TRUE*/)
{
	m_bPreAlignUse = bUse;

	m_bPreAlignDone = FALSE;
}

void CRightAngleFlow::SetFinishGantryWaitPosSkip(BOOL bSkip/* = FALSE*/)
{
	m_bGantryWaitPosSkip = bSkip;
}

BOOL CRightAngleFlow::StateStop()
{
	SetStop();
	return TRUE;
}

BOOL CRightAngleFlow::Start(enum_MappingID eMappingID)
{
	//SharedInfo::MachineState.bSemiAutoRunFlag = TRUE;
	m_nMappingID = eMappingID;

	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;

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
	SetStep(eRIGHT_ANGLE_FLOW_START, _T("eRIGHT_ANGLE_FLOW_START"));
	return TRUE;
}

BOOL CRightAngleFlow::Stop()
{
	m_bStopBit = TRUE;
	//SharedInfo::MachineState.bSemiAutoRunFlag = FALSE;
	return TRUE;
}

UINT CRightAngleFlow::ThreadFunction(LPVOID lpParam)
{
	CRightAngleFlow* pRightAngle = NULL;

	pRightAngle = (CRightAngleFlow*)lpParam;

	pRightAngle->ThreadFunctionEntry();

	pRightAngle->m_bTerminate = 1;

	return 0;
}

VOID CRightAngleFlow::ThreadFunctionEntry(VOID)
{
	int ErrorCheck = 0;
	CString szMsg;
	BOOL bResult = FALSE;
	CString Str = _T("");

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

	while (m_FlowFinish)
	{
		WaitForSingleObject(hHandle, INFINITE);
		ResetEvent(hHandle);

		if (SharedInfo::bMachineStopFlag == TRUE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(eRIGHT_ANGLE_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}

		switch (GetCurrentTotalStep())
		{
		case eRIGHT_ANGLE_FLOW_IDLE:
			break;

		case eRIGHT_ANGLE_FLOW_START:
			m_timeStart = CTime::GetCurrentTime(); //KJT 20210329
			SharedInfo::m_timeUnitTact = m_timeStart;

			SharedInfo::nCurFlowID = eRIGHT_ANGLE_FLOW;

			SharedInfo::LightAllOff();
			Sleep(500);

			m_nAlignPoint = 0;
			m_bDirReverse = FALSE;

			m_nGrabRetryCnt = 0;

			SetStep(eRIGHT_ANGLE_FLOW_INTERLOCK, _T("eRIGHT_ANGLE_FLOW_INTERLOCK"));
			break;

		case eRIGHT_ANGLE_FLOW_INTERLOCK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(eRIGHT_ANGLE_FLOW_ERROR, _T("eRIGHT_ANGLE_FLOW_ERROR"));
			}
			else
			{
				if (m_bPreAlignUse == TRUE && m_bPreAlignDone == FALSE)
				{
					SharedInfo::nGantryZ1View = eViewPreAlign;
					
					//g_CommZomm_Coaxial.SetLight_Zoom_Coaxial(CModelData::m_AlignPara.Info.nVerticalPreAlignCoAxial);
					//Sleep(10);
					//g_CommZomm_Coaxial.Zoom_Light_On(TRUE);
					//Sleep(10);
					//g_CommZomm_Ring.SetLight_Zoom_Ring(CModelData::m_AlignPara.Info.nVerticalPreAlignRing);
					//Sleep(10);
					//g_CommZomm_Ring.Zoom_Light_On(TRUE);

					g_CommLoader_Light.SetLight_PreAlign(CModelData::m_AlignPara.Info.nVerticalPreAlignCoAxial, CModelData::m_AlignPara.Info.nVerticalPreAlignRing); //KJT 20210728
				}
				else
				{
					SharedInfo::nGantryZ1View = eViewReview10X;		

					g_CommReview_Light.SetLight_Review(CModelData::m_AlignPara.Info.nVerticalMainAlignRing, CModelData::m_AlignPara.Info.nVerticalMainAlignCoAxial);
					Sleep(10);
				}

				SetStep(eRIGHT_ANGLE_FLOW_UNLOADER_READY, _T("eRIGHT_ANGLE_FLOW_UNLOADER_READY"));
			}
			break;

#pragma region //Unloader Ready
		case eRIGHT_ANGLE_FLOW_UNLOADER_READY:
			Devs::m_Ready_UnloaderFlow.Start();

			SetStep(eRIGHT_ANGLE_FLOW_UNLOADER_READY_CHECK, _T("eRIGHT_ANGLE_FLOW_UNLOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eRIGHT_ANGLE_FLOW_UNLOADER_READY_CHECK:
			if (Devs::m_Ready_UnloaderFlow.IsFlowDone())
			{
				SetStep(eRIGHT_ANGLE_FLOW_LOADER_READY, _T("eRIGHT_ANGLE_FLOW_LOADER_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eRIGHT_ANGLE_FLOW_UNLOADER_READY_CHECK : Time Out !!!"), eRIGHT_ANGLE_FLOW + 0);
				SetStep(eRIGHT_ANGLE_FLOW_ERROR, _T("eRIGHT_ANGLE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eRIGHT_ANGLE_FLOW_UNLOADER_READY_CHECK, _T("eRIGHT_ANGLE_FLOW_UNLOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Loader Ready
		case eRIGHT_ANGLE_FLOW_LOADER_READY:
			Devs::m_Ready_LoaderFlow.Start();

			SetStep(eRIGHT_ANGLE_FLOW_LOADER_READY_CHECK, _T("eRIGHT_ANGLE_FLOW_LOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eRIGHT_ANGLE_FLOW_LOADER_READY_CHECK:
			if (Devs::m_Ready_LoaderFlow.IsFlowDone())
			{
				//SetStep(eRIGHT_ANGLE_FLOW_BOX_CAMERA_READY, _T("eRIGHT_ANGLE_FLOW_BOX_CAMERA_READY"));
				SetStep(eRIGHT_ANGLE_FLOW_GANTRY_ZX_READY, _T("eRIGHT_ANGLE_FLOW_GANTRY_ZX_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eRIGHT_ANGLE_FLOW_LOADER_READY_CHECK : Time Out !!!"), eRIGHT_ANGLE_FLOW + 1);
				SetStep(eRIGHT_ANGLE_FLOW_ERROR, _T("eRIGHT_ANGLE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eRIGHT_ANGLE_FLOW_LOADER_READY_CHECK, _T("eRIGHT_ANGLE_FLOW_LOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Box Camera Ready
		case eRIGHT_ANGLE_FLOW_BOX_CAMERA_READY:
			Devs::m_BoxMotion.BoxAlignCameraYL_WaitPos();
			Sleep(20);
			Devs::m_BoxMotion.BoxAlignCameraYR_WaitPos();
			Sleep(500); //!!

			SetStep(eRIGHT_ANGLE_FLOW_BOX_CAMERA_READY_CHECK, _T("eRIGHT_ANGLE_FLOW_BOX_CAMERA_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eRIGHT_ANGLE_FLOW_BOX_CAMERA_READY_CHECK:
			if (Devs::m_BoxMotion.Is_BoxAlignCameraYL_WaitPos() == TRUE && Devs::m_BoxMotion.Is_BoxAlignCameraYR_WaitPos() == TRUE)
			{
				if (m_bGantryWaitPosSkip == TRUE)
					SetStep(eRIGHT_ANGLE_FLOW_AXIS_GANTRY_XY_VERTICA_POS_CHECK, _T("eRIGHT_ANGLE_FLOW_AXIS_GANTRY_XY_VERTICA_POS_CHECK"));
				else
					SetStep(eRIGHT_ANGLE_FLOW_GANTRY_ZX_READY, _T("eRIGHT_ANGLE_FLOW_GANTRY_ZX_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eRIGHT_ANGLE_FLOW_BOX_CAMERA_READY_CHECK : Time Out !!!"), eRIGHT_ANGLE_FLOW + 2);
				SetStep(eRIGHT_ANGLE_FLOW_ERROR, _T("eRIGHT_ANGLE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eRIGHT_ANGLE_FLOW_BOX_CAMERA_READY_CHECK, _T("eRIGHT_ANGLE_FLOW_BOX_CAMERA_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Gantry Z,X Ready
		case eRIGHT_ANGLE_FLOW_GANTRY_ZX_READY:
			Devs::m_Ready_GantryZX_Flow.Start();

			SetStep(eRIGHT_ANGLE_FLOW_GANTRY_ZX_READY_CHECK, _T("eRIGHT_ANGLE_FLOW_GANTRY_ZX_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eRIGHT_ANGLE_FLOW_GANTRY_ZX_READY_CHECK:
			if (Devs::m_Ready_GantryZX_Flow.IsFlowDone())
			{
				SetStep(eRIGHT_ANGLE_FLOW_AXIS_GANTRY_XY_MOVE_VERTICAL_POS, _T("eRIGHT_ANGLE_FLOW_AXIS_GANTRY_XY_MOVE_VERTICAL_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eRIGHT_ANGLE_FLOW_GANTRY_ZX_READY_CHECK : Time Out !!!"), eRIGHT_ANGLE_FLOW + 3);
				SetStep(eRIGHT_ANGLE_FLOW_ERROR, _T("eRIGHT_ANGLE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eRIGHT_ANGLE_FLOW_GANTRY_ZX_READY_CHECK, _T("eRIGHT_ANGLE_FLOW_GANTRY_ZX_READY_CHECK"));
			}
			break;
#pragma endregion

		case eRIGHT_ANGLE_FLOW_AXIS_GANTRY_XY_MOVE_VERTICAL_POS:
			if (m_bPreAlignUse == TRUE && m_bPreAlignDone == FALSE)
			{
				Devs::m_GantryMotion.Move_Gantry_X_Pos(GetRightAnglePos_X_PreAlign(m_nAlignPoint), FALSE);
				Sleep(10);
				Devs::m_GantryMotion.Move_Gantry_Y_Pos(GetRightAnglePos_Y_PreAlign(m_nAlignPoint));
			}
			else
			{
				Devs::m_GantryMotion.Move_Gantry_X_Pos(GetRightAnglePos_X_Review(m_nAlignPoint), FALSE);
				Sleep(10);
				Devs::m_GantryMotion.Move_Gantry_Y_Pos(GetRightAnglePos_Y_Review(m_nAlignPoint));
			}

			SetStep(eRIGHT_ANGLE_FLOW_AXIS_GANTRY_XY_VERTICA_POS_CHECK, _T("eRIGHT_ANGLE_FLOW_AXIS_GANTRY_XY_VERTICA_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eRIGHT_ANGLE_FLOW_AXIS_GANTRY_XY_VERTICA_POS_CHECK:
			if (m_bPreAlignUse == TRUE && m_bPreAlignDone == FALSE)
			{
				if (Devs::m_GantryMotion.Is_Gantry_X_Pos(GetRightAnglePos_X_PreAlign(m_nAlignPoint)) && Devs::m_GantryMotion.Is_Gantry_Y_Pos(GetRightAnglePos_Y_PreAlign(m_nAlignPoint)))
					SetStep(eRIGHT_ANGLE_FLOW_AXIS_Z_PRE_ALGIN_CAM_DOWN_POS, _T("eRIGHT_ANGLE_FLOW_AXIS_Z_PRE_ALGIN_CAM_DOWN_POS"));
				else
					SetCheckStep(eRIGHT_ANGLE_FLOW_AXIS_GANTRY_XY_VERTICA_POS_CHECK);
			}
			else if (Devs::m_GantryMotion.Is_Gantry_X_Pos(GetRightAnglePos_X_Review(m_nAlignPoint)) && Devs::m_GantryMotion.Is_Gantry_Y_Pos(GetRightAnglePos_Y_Review(m_nAlignPoint)))
			{
				SetStep(eRIGHT_ANGLE_FLOW_AXIS_Z_REVIEW10X_CAM_DOWN_POS, _T("eRIGHT_ANGLE_FLOW_AXIS_Z_REVIEW10X_CAM_DOWN_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eRIGHT_ANGLE_FLOW_AXIS_GANTRY_XY_VERTICA_POS_CHECK : Time Out !!!"), eRIGHT_ANGLE_FLOW + 4);
				SetStep(eRIGHT_ANGLE_FLOW_ERROR, _T("eRIGHT_ANGLE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eRIGHT_ANGLE_FLOW_AXIS_GANTRY_XY_VERTICA_POS_CHECK);
			}
			break;

#pragma region //PreAlign Camera
		case eRIGHT_ANGLE_FLOW_AXIS_Z_PRE_ALGIN_CAM_DOWN_POS:
			Devs::m_GantryMotion.Move_GantryZ1_PreAlign_Pos();

			SetStep(eRIGHT_ANGLE_FLOW_AXIS_Z_PRE_ALGIN_CAM_DOWN_POS_CHECK, _T("eRIGHT_ANGLE_FLOW_AXIS_Z_PRE_ALGIN_CAM_DOWN_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eRIGHT_ANGLE_FLOW_AXIS_Z_PRE_ALGIN_CAM_DOWN_POS_CHECK:
			if (Devs::m_GantryMotion.Is_GantryZ1_PreAlign_Pos() == TRUE)
			{
				SetStep(eRIGHT_ANGLE_FLOW_GRAB_START, _T("eRIGHT_ANGLE_FLOW_GRAB_START"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eRIGHT_ANGLE_FLOW_AXIS_Z_PRE_ALGIN_CAM_DOWN_POS_CHECK : Time Out !!!"), eRIGHT_ANGLE_FLOW + 5);
				SetStep(eRIGHT_ANGLE_FLOW_ERROR, _T("eRIGHT_ANGLE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eRIGHT_ANGLE_FLOW_AXIS_Z_PRE_ALGIN_CAM_DOWN_POS_CHECK);
			}
			break;
#pragma endregion

#pragma region //Review 10X
		case eRIGHT_ANGLE_FLOW_AXIS_Z_REVIEW10X_CAM_DOWN_POS:
			//Devs::m_GantryMotion.Move_GantryZ3_InspectionReview_Pos();
			Devs::m_GantryMotion.Move_GantryZ1_InspectionMapping_Pos();

			SetStep(eRIGHT_ANGLE_FLOW_AXIS_Z_REVIEW10X_CAM_DOWN_POS_CHECK, _T("eRIGHT_ANGLE_FLOW_AXIS_Z_REVIEW10X_CAM_DOWN_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eRIGHT_ANGLE_FLOW_AXIS_Z_REVIEW10X_CAM_DOWN_POS_CHECK:
			//if (Devs::m_GantryMotion.Is_GantryZ3_InspectionReview_Pos() == TRUE)
			if (Devs::m_GantryMotion.Is_GantryZ1_InspectionMapping_Pos() == TRUE)
			{
				Sleep(500); //!!

				if (m_bLaserFocusUseFlag == TRUE)
					SetStep(eRIGHT_ANGLE_FLOW_AXIS_Z_REVIEW10X_LASER_FOCUS_START, _T("eRIGHT_ANGLE_FLOW_AXIS_Z_REVIEW10X_LASER_FOCUS_START"));
				else if (m_bAutoFocusUseFlag == TRUE)
					SetStep(eRIGHT_ANGLE_FLOW_AXIS_Z_REVIEW10X_IMAGE_FOCUS_START, _T("eRIGHT_ANGLE_FLOW_AXIS_Z_REVIEW10X_IMAGE_FOCUS_START"));
				else
					SetStep(eRIGHT_ANGLE_FLOW_GRAB_START, _T("eRIGHT_ANGLE_FLOW_GRAB_START"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eRIGHT_ANGLE_FLOW_AXIS_Z_REVIEW10X_CAM_DOWN_POS_CHECK : Time Out !!!"), eRIGHT_ANGLE_FLOW + 6);
				SetStep(eRIGHT_ANGLE_FLOW_ERROR, _T("eRIGHT_ANGLE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eRIGHT_ANGLE_FLOW_AXIS_Z_REVIEW10X_CAM_DOWN_POS_CHECK);
			}
			break;

		case eRIGHT_ANGLE_FLOW_AXIS_Z_REVIEW10X_LASER_FOCUS_START:
			bResult = Devs::m_GantryMotion.LaserFocusMove(1);//Glass
			if (bResult) //KJT 20210601
			{
				SetStep(eRIGHT_ANGLE_FLOW_AXIS_Z_REVIEW10X_LASER_FOCUS_CHECK, _T("eRIGHT_ANGLE_FLOW_AXIS_Z_REVIEW10X_LASER_FOCUS_CHECK"));
				SetTimeOut(TIME_OUT_MOTION);
			}
			else
			{
				if (m_bAutoFocusUseFlag == TRUE)
					SetStep(eRIGHT_ANGLE_FLOW_AXIS_Z_REVIEW10X_IMAGE_FOCUS_START, _T("eRIGHT_ANGLE_FLOW_AXIS_Z_REVIEW10X_IMAGE_FOCUS_START"));
				else
					SetStep(eRIGHT_ANGLE_FLOW_GRAB_START, _T("eRIGHT_ANGLE_FLOW_GRAB_START"));
			}
			break;

		case eRIGHT_ANGLE_FLOW_AXIS_Z_REVIEW10X_LASER_FOCUS_CHECK:
			if (Devs::m_GantryMotion.LaserFocusMoveCheck())
			{
				Sleep(500); //!!	//KJT 20210321

				if (m_bAutoFocusUseFlag == TRUE)
					SetStep(eRIGHT_ANGLE_FLOW_AXIS_Z_REVIEW10X_IMAGE_FOCUS_START, _T("eRIGHT_ANGLE_FLOW_AXIS_Z_REVIEW10X_IMAGE_FOCUS_START"));
				else
					SetStep(eRIGHT_ANGLE_FLOW_GRAB_START, _T("eRIGHT_ANGLE_FLOW_GRAB_START"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eRIGHT_ANGLE_FLOW_AXIS_Z_REVIEW10X_LASER_FOCUS_CHECK : Time Out !!!"), eRIGHT_ANGLE_FLOW + 7);
				SetStep(eRIGHT_ANGLE_FLOW_ERROR, _T("eRIGHT_ANGLE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eRIGHT_ANGLE_FLOW_AXIS_Z_REVIEW10X_LASER_FOCUS_CHECK, _T("eRIGHT_ANGLE_FLOW_AXIS_Z_REVIEW10X_LASER_FOCUS_CHECK"));
			}
			break;

		case eRIGHT_ANGLE_FLOW_AXIS_Z_REVIEW10X_IMAGE_FOCUS_START:
			Total_Msg(_T("Auto Focus Start"));

#ifndef SIM_MODE
			switch (m_nMappingID)
			{
#if 0 //KJT 20210820 Junying Not Use
			case eMAPPING_ID_20X:
				//g_pReview20x->m_bAfEnd = FALSE;
				//g_pReview20x->AutofoucsRun(eViewReview20X);
				break;
#endif
			case eMAPPING_ID_10X:
			case eMAPPING_ID_20X: //KJT 20210820 Add
			case eMAPPING_ID_50X: //KJT 20210820 Add
				g_pReview10x->m_bAfEnd = FALSE;
				g_pReview10x->AutofoucsRun();
				break;
			}
#endif

			SetStep(eRIGHT_ANGLE_FLOW_AXIS_Z_REVIEW10X_IMAGE_FOCUS_CHECK, _T("eRIGHT_ANGLE_FLOW_AXIS_Z_REVIEW10X_IMAGE_FOCUS_CHECK"));
			SetTimeOut(TIME_OUT_DUAL);
			break;

		case eRIGHT_ANGLE_FLOW_AXIS_Z_REVIEW10X_IMAGE_FOCUS_CHECK:
			bResult = FALSE;

#ifndef SIM_MODE
			switch (m_nMappingID)
			{
#if 0 //KJT 20210820 Junying Not Use
			case eMAPPING_ID_20X:
				//if (g_pReview20x->m_bAfEnd == TRUE)
				{
					bResult = TRUE;
				}
				break;
#endif
			case eMAPPING_ID_10X:
			case eMAPPING_ID_20X: //KJT 20210820 Add
			case eMAPPING_ID_50X: //KJT 20210820 Add
				if (g_pReview10x->m_bAfEnd == TRUE)
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
				Sleep(IMAGE_FOCUS_DELAY);
				SetStep(eRIGHT_ANGLE_FLOW_GRAB_START, _T("eRIGHT_ANGLE_FLOW_GRAB_START"));

			}
			else if (IsTimeOut())
			{
				SetStep(eRIGHT_ANGLE_FLOW_AXIS_Z_REVIEW10X_IMAGE_FOCUS_CHECK, _T("eRIGHT_ANGLE_FLOW_AXIS_Z_REVIEW10X_IMAGE_FOCUS_CHECK"));
			}
			else
			{
				SetCheckStep(eRIGHT_ANGLE_FLOW_AXIS_Z_REVIEW10X_IMAGE_FOCUS_CHECK, _T("eRIGHT_ANGLE_FLOW_AXIS_Z_REVIEW10X_IMAGE_FOCUS_CHECK"));
			}
			break;
#pragma endregion //Review10X

		case eRIGHT_ANGLE_FLOW_GRAB_START:
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
				if (m_nGrabRetryCnt >= 3)
				{
					SharedInfo::SetAlarm(_T("eRIGHT_ANGLE_FLOW_GRAB : Retry 3 Over !!!"), eRIGHT_ANGLE_FLOW + 8);
					SetStep(eRIGHT_ANGLE_FLOW_ERROR, _T("eRIGHT_ANGLE_FLOW_ERROR"));
					break;
				}

				if (m_bLaserFocusUseFlag == TRUE)
					SetStep(eRIGHT_ANGLE_FLOW_AXIS_Z_REVIEW10X_LASER_FOCUS_START, _T("eRIGHT_ANGLE_FLOW_AXIS_Z_REVIEW10X_LASER_FOCUS_START"));
				else if (m_bAutoFocusUseFlag == TRUE)
					SetStep(eRIGHT_ANGLE_FLOW_AXIS_Z_REVIEW10X_IMAGE_FOCUS_START, _T("eRIGHT_ANGLE_FLOW_AXIS_Z_REVIEW10X_IMAGE_FOCUS_START"));
				else
					SetStep(eRIGHT_ANGLE_FLOW_GRAB_START, _T("eRIGHT_ANGLE_FLOW_GRAB_START"));

				break;
			}
			else
				m_nGrabRetryCnt = 0;

			Str.Format(_T("AlignPoint:%d Diff X:%.5f, Y:%.5f"), m_nAlignPoint, m_AlignVisionResultValue[0][m_nAlignPoint], m_AlignVisionResultValue[1][m_nAlignPoint]);
			Total_Msg(Str);

			if ((m_bDirReverse == FALSE && m_nAlignPoint == 1) || (m_bDirReverse == TRUE && m_nAlignPoint == 0))
			{
				Str.Format(_T("AlignResult Diff X[0]:%.5f, Y[0]:%.5f, X[1]:%.5f, Y[1]:%.5f"), m_AlignVisionResultValue[0][0], m_AlignVisionResultValue[1][0], m_AlignVisionResultValue[0][1], m_AlignVisionResultValue[1][1]);
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

				m_ErrorY = m_AlignVisionResultValue[1][1] - m_AlignVisionResultValue[1][0]; //KJT 20210305

				Sleep(100);
				Devs::m_InspectionStageMotion.GetUVWPos(m_AlignPointValue[0], m_AlignPointValue[1], m_AlignVisionResultValue[0], m_AlignVisionResultValue[1], &m_dDiffPos[0], &m_dDiffPos[1], &m_dDiffPos[2], TRUE);
				
				Str.Format(_T("Result Diff X:%.5f, Y:%.5f, T:%.5f, errorX:%.5f"), m_dDiffPos[0], m_dDiffPos[1], m_dDiffPos[2], m_ErrorY);
				Total_Msg(Str);
				
				if (m_bGantryWaitPosSkip == TRUE)
					SetStep(eRIGHT_ANGLE_FLOW_DONE, _T("eRIGHT_ANGLE_FLOW_DONE"));
				else
					SetStep(eRIGHT_ANGLE_FLOW_FINISH_GANTRY_Z3_WAIT_POS, _T("eRIGHT_ANGLE_FLOW_FINISH_GANTRY_Z3_WAIT_POS"));
			}
			else
			{
				if (m_bDirReverse == FALSE)
					m_nAlignPoint = 1;
				else
					m_nAlignPoint = 0;

				Sleep(1000);
				SetStep(eRIGHT_ANGLE_FLOW_AXIS_GANTRY_XY_MOVE_VERTICAL_POS, _T("eRIGHT_ANGLE_FLOW_AXIS_GANTRY_XY_MOVE_VERTICAL_POS"));
			}
			break;

		case eRIGHT_ANGLE_FLOW_FINISH_GANTRY_Z3_WAIT_POS:
			Devs::m_GantryMotion.Move_GantryZ_All_Wait_Pos();

			//if (GetStepFlag() == TRUE)
			//	break;
			SetStep(eRIGHT_ANGLE_FLOW_FINISH_GANTRY_Z3_WAIT_POS_CHECK, _T("eRIGHT_ANGLE_FLOW_FINISH_GANTRY_Z3_WAIT_POS_CHECK"));

			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eRIGHT_ANGLE_FLOW_FINISH_GANTRY_Z3_WAIT_POS_CHECK:
			if (Devs::m_GantryMotion.Is_GantryZ_All_Wait_Pos() == TRUE)
			{
				SetStep(eRIGHT_ANGLE_FLOW_DONE, _T("eRIGHT_ANGLE_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eRIGHT_ANGLE_FLOW_FINISH_GANTRY_Z1_WAIT_POS_CHECK : Time Out !!!"), eRIGHT_ANGLE_FLOW + 9);
				SetStep(eRIGHT_ANGLE_FLOW_ERROR, _T("eRIGHT_ANGLE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eRIGHT_ANGLE_FLOW_FINISH_GANTRY_Z3_WAIT_POS_CHECK, _T("eRIGHT_ANGLE_FLOW_FINISH_GANTRY_Z3_WAIT_POS_CHECK"));
			}
			break;

		case eRIGHT_ANGLE_FLOW_FINISH_GANTRY_XY_WAIT_POS:
			Devs::m_GantryMotion.Move_Gantry_X_Wait_Pos();
			Sleep(20); //!!
			Devs::m_GantryMotion.Move_Gantry_Y_Wait_Pos();
			Sleep(20); //!!

			SetStep(eRIGHT_ANGLE_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK, _T("eRIGHT_ANGLE_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eRIGHT_ANGLE_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Wait_Pos() && Devs::m_GantryMotion.Is_Gantry_Y_Wait_Pos())
			{
				SetStep(eRIGHT_ANGLE_FLOW_DONE, _T("eRIGHT_ANGLE_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eRIGHT_ANGLE_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK : Time Out !!!"), eRIGHT_ANGLE_FLOW + 10);
				SetStep(eRIGHT_ANGLE_FLOW_ERROR, _T("eRIGHT_ANGLE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eRIGHT_ANGLE_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK, _T("eRIGHT_ANGLE_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK"));
			}
			break;

		case eRIGHT_ANGLE_FLOW_DONE:
			m_bFlowDone = TRUE;

			SharedInfo::CalTactTime(_T("RIGHT_ANGLE_FLOW"), m_timeStart); //KJT 20210329

			SetStep(eRIGHT_ANGLE_FLOW_IDLE, _T("eRIGHT_ANGLE_FLOW_IDLE"));
			break;
		}

		Sleep(100); //!!
	}
}

BOOL CRightAngleFlow::SetRightAnglePosXY(double *dPosX, double *dPosY)
{
	m_AlignPointValue[0][0] = dPosX[0];
	m_AlignPointValue[1][0] = dPosY[0];

	m_AlignPointValue[0][1] = dPosX[1];
	m_AlignPointValue[1][1] = dPosY[1];
	return TRUE;
}

BOOL CRightAngleFlow::GetXYTPos(double *dRefPosX, double *dRefPosY, double *dDiffPosX, double *dDiffPosY, double *ResultX, double *ResultY, double *ResultT)
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

BOOL CRightAngleFlow::FlowInterlock()
{
	/////////////////////////////////////////////////////////////////////////////
	if (Devs::m_GantryMotion.CheckGantryXYZFlowInterlock(_T("RightAngleFlow"), eRIGHT_ANGLE_FLOW, 30) == FALSE)
	{
		return FALSE;
	}

	//if (Devs::m_CassetteMotion.Is_CSTPickUpUnitBwd() == FALSE)
	//{
	//	SharedInfo::SetAlarm(_T("Pickup Unit Backward : Off Error !!!"), eRIGHT_ANGLE_FLOW + 11);
	//	return FALSE;
	//}
	//if (SharedInfo::DInputValue[_DIN_CST_UNSAFE_POS_DETECT] == TRUE)
	//{
	//	SharedInfo::SetAlarm(_T("CST Unsafe Pos Detect On Error !!!"), eRIGHT_ANGLE_FLOW + 12);
	//	return FALSE;
	//}
	//if (SharedInfo::DInputValue[_DIN_CST_BACKWARD_DETECT] == TRUE)
	//{
	//	SharedInfo::SetAlarm(_T("CST Backward Detect On Error !!!"), eRIGHT_ANGLE_FLOW + 13);
	//	return FALSE;
	//}

	return TRUE;
}