#include "stdafx.h"
#include "CameraCalFlow.h"
#include "Log/Logger.h"
#include "Vision/Devs.h"
#include "Data/ModelData.h"
#include "CamAreaModul.h"
#include "Data/SystemData.h"
#include "FmmLight1.h"
#include <math.h>

CCameraCalFlow::CCameraCalFlow()
{
	m_nCurPoint = 0;
	m_nMaxRepeatCnt = 0;
	m_nCurRepeatCnt = 0;
}

CCameraCalFlow::~CCameraCalFlow()
{
}

BOOL CCameraCalFlow::InitProcess()
{
	m_StateComplete = NULL;
	m_FlowFinish = TRUE;
	m_bTerminate = FALSE;
	m_bFlowDone = TRUE;

#pragma region //Step Group
	int nGroupIndex = 0;

	m_sGroupInfo[nGroupIndex].m_bProcessingFlag = FALSE;
	m_sGroupInfo[nGroupIndex].nStartStep = eCAMERA_CAL_FLOW_START;
	m_sGroupInfo[nGroupIndex].nEndStep = eCAMERA_CAL_FLOW_INTERLOCK;
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

BOOL CCameraCalFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(eCAMERA_CAL_FLOW_IDLE, _T("eCAMERA_CAL_FLOW_IDLE"));

	if (hHandle != NULL)
	{
		CloseHandle(hHandle);
		hHandle = NULL;
	}

	return TRUE;
}

BOOL CCameraCalFlow::StateStop()
{
	SetStop();
	return TRUE;
}

BOOL CCameraCalFlow::Start(int nCalID/* = eMAPPING_ID_10X*/)
{
	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;

	m_nCalID = nCalID;

	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(eCAMERA_CAL_FLOW_START, _T("eCAMERA_CAL_FLOW_START"));
	return TRUE;
}

BOOL CCameraCalFlow::Stop()
{
	m_bStopBit = TRUE;
	SetCurrentStep(eCAMERA_CAL_FLOW_IDLE); //KJT 20210318
	return TRUE;
}

UINT CCameraCalFlow::ThreadFunction(LPVOID lpParam)
{
	CCameraCalFlow* pRightAngle = NULL;

	pRightAngle = (CCameraCalFlow*)lpParam;

	pRightAngle->ThreadFunctionEntry();

	pRightAngle->m_bTerminate = 1;

	return 0;
}

VOID CCameraCalFlow::ThreadFunctionEntry(VOID)
{
	DWORD	dwResult = 0;
	double	dStrt_Time = GetTickCount();
	double	dEnd_Time = GetTickCount();
	double	dWait_Time = GetTickCount();
	int		nWork_Mask_Mode = -1;
	int		nWork_Mask_Index = -1;
	BOOL	bComplete_Step = FALSE;
	CString Str = _T("");
	double dDiffXTemp = 0.0;
	double dPosX = 0.0, dPosY = 0.0, dPosZ1 = 0.0;
	double dDiffX = 0.0, dDiffY = 0.0;
	//KJT 20210304
	double dVel[3] = { 1.0, 1.0, 1.0 };
	double dAcc[3] = { 2.0, 2.0, 2.0 };
	double dDecel[3] = { 2.0, 2.0, 2.0 };
	CVisionAgentDlg *pVisionAgentDlg = (CVisionAgentDlg*)AfxGetMainWnd();
	BOOL bResult = FALSE;

	SYSTEMTIME st;
	GetLocalTime(&st);
	CString StrDirPath = _T(""), StrFilePath = _T("");

	DOUBLE dPixelX = 0., dPixelY = 0., dWorldX = 0., dWorldY = 0.;
	INT nSize;

	while (m_FlowFinish)
	{
		WaitForSingleObject(hHandle, INFINITE);
		ResetEvent(hHandle);

		if (SharedInfo::bMachineStopFlag == TRUE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(eCAMERA_CAL_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}

		switch (GetCurrentTotalStep())
		{
		case eCAMERA_CAL_FLOW_IDLE:
		{
			break;
		}
		case eCAMERA_CAL_FLOW_START:
			m_timeStart = CTime::GetCurrentTime(); //KJT 20210329
			SharedInfo::m_timeUnitTact = m_timeStart;

			SharedInfo::nCurFlowID = eCAMERA_CAL_FLOW;

#ifndef SIM_MODE
			switch (m_nCalID)
			{
			case eMAPPING_ID_10X:
				SharedInfo::nGantryZ1View = eViewReview10X;
				break;
			case eMAPPING_ID_20X:
				SharedInfo::nGantryZ1View = eViewReview20X;
				break;
			case eMAPPING_ID_50X:
				SharedInfo::nGantryZ1View = eViewReview50X;
				break;
			}
			Devs::m_Camera10X->ClearCalibData();

			for (int i = 0; i < MAX_CAMERA_CAL_COUNT; i++)
			{
				SharedInfo::m_CameraCalTable[i].dWorldX = 0.0;
				SharedInfo::m_CameraCalTable[i].dWorldY = 0.0;
			}
#endif

			//SharedInfo::nGantryZ1View = eViewReview10X;

			m_nCurPoint = 0;
			m_nCurRepeatCnt = 0;

			m_nGrabFailRetryCnt = 0;
			m_nGrabRetryCnt = 0;

			m_bCentered = FALSE;
			m_dCenterPosX = 0.0;
			m_dCenterPosY = 0.0;
			m_dOffsetCx = 0.0;
			m_dOffsetCy = 0.0;

			GetLocalTime(&st);
			m_strFilePath.Format(_T("%s\\Result\\CameraCal\\CameraCal_%04d%02d%02d%02d%02d%02d.csv"), SharedInfo::VisionAgentPath, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

			SharedInfo::LightAllOff();

			g_CommReview_Light.SetLight_Review(CModelData::m_AlignPara.Info.nVerticalMainAlignRing, CModelData::m_AlignPara.Info.nVerticalMainAlignCoAxial);
			Sleep(20);

			SetStep(eCAMERA_CAL_FLOW_INTERLOCK, _T("eCAMERA_CAL_FLOW_INTERLOCK"));
			break;

		case eCAMERA_CAL_FLOW_INTERLOCK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(eCAMERA_CAL_FLOW_ERROR, _T("eCAMERA_CAL_FLOW_ERROR"));
			}
			else
			{
				SetStep(eCAMERA_CAL_FLOW_UNLOADER_READY, _T("eCAMERA_CAL_FLOW_UNLOADER_READY"));
			}
			break;

#pragma region //Unloader Ready
		case eCAMERA_CAL_FLOW_UNLOADER_READY:
			Devs::m_Ready_UnloaderFlow.Start();

			SetStep(eCAMERA_CAL_FLOW_UNLOADER_READY_CHECK, _T("eCAMERA_CAL_FLOW_UNLOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eCAMERA_CAL_FLOW_UNLOADER_READY_CHECK:
			if (Devs::m_Ready_UnloaderFlow.IsFlowDone())
			{
				SetStep(eCAMERA_CAL_FLOW_GANTRY_ZX_READY, _T("eCAMERA_CAL_FLOW_GANTRY_ZX_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eCAMERA_CAL_FLOW_UNLOADER_READY_CHECK Time Out"), eCAMERA_CAL_FLOW + 0);
				SetStep(eCAMERA_CAL_FLOW_ERROR, _T("eCAMERA_CAL_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eCAMERA_CAL_FLOW_UNLOADER_READY_CHECK, _T("eCAMERA_CAL_FLOW_UNLOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Gantry ZX Ready
		case eCAMERA_CAL_FLOW_GANTRY_ZX_READY:
			Devs::m_Ready_GantryZX_Flow.Start();

			SetStep(eCAMERA_CAL_FLOW_GANTRY_ZX_READY_CHECK, _T("eCAMERA_CAL_FLOW_GANTRY_ZX_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eCAMERA_CAL_FLOW_GANTRY_ZX_READY_CHECK:
			if (Devs::m_Ready_GantryZX_Flow.IsFlowDone())
			{
				SetStep(eCAMERA_CAL_FLOW_LOADER_READY, _T("eCAMERA_CAL_FLOW_LOADER_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eCAMERA_CAL_FLOW_GANTRY_ZX_READY_CHECK Time Out"), eCAMERA_CAL_FLOW + 3);
				SetStep(eCAMERA_CAL_FLOW_ERROR, _T("eCAMERA_CAL_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eCAMERA_CAL_FLOW_GANTRY_ZX_READY_CHECK, _T("eCAMERA_CAL_FLOW_GANTRY_ZX_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Loader Ready
		case eCAMERA_CAL_FLOW_LOADER_READY:
			Devs::m_Ready_LoaderFlow.Start();

			SetStep(eCAMERA_CAL_FLOW_LOADER_READY_CHECK, _T("eCAMERA_CAL_FLOW_LOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eCAMERA_CAL_FLOW_LOADER_READY_CHECK:
			if (Devs::m_Ready_LoaderFlow.IsFlowDone())
			{
				SetStep(eCAMERA_CAL_FLOW_PAPER_UNLOADER_ZXY_READY, _T("eCAMERA_CAL_FLOW_PAPER_UNLOADER_ZXY_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eCAMERA_CAL_FLOW_LOADER_READY_CHECK Time Out"), eCAMERA_CAL_FLOW + 1);
				SetStep(eCAMERA_CAL_FLOW_ERROR, _T("eCAMERA_CAL_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eCAMERA_CAL_FLOW_LOADER_READY_CHECK, _T("eCAMERA_CAL_FLOW_LOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //PaperUnloader Ready
		case eCAMERA_CAL_FLOW_PAPER_UNLOADER_ZXY_READY:
			Devs::m_Ready_PaperUnloaderFlow.Start();

			SetStep(eCAMERA_CAL_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK, _T("eCAMERA_CAL_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eCAMERA_CAL_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK:
			if (Devs::m_Ready_PaperUnloaderFlow.IsFlowDone())
			{
				SetStep(eCAMERA_CAL_FLOW_GANTRY_XY_MEASURE_POS_1ST, _T("eCAMERA_CAL_FLOW_GANTRY_XY_MEASURE_POS_1ST"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eCAMERA_CAL_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK : Time Out"), eBOX_ALIGN_FLOW + 1);
				SetStep(eCAMERA_CAL_FLOW_ERROR, _T("eCAMERA_CAL_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eCAMERA_CAL_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK, _T("eCAMERA_CAL_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK"));
			}
			break;
#pragma endregion

		case eCAMERA_CAL_FLOW_GANTRY_XY_MEASURE_POS_1ST:
			m_bCentered = FALSE;
			m_dTargetPosX = dPosX = m_dCenterPosX;
			m_dTargetPosY = dPosY = m_dCenterPosY;

			Devs::m_GantryMotion.Move_Gantry_X_Pos(m_dTargetPosX, FALSE);
			Sleep(20); //!!
			Devs::m_GantryMotion.Move_Gantry_Y_Pos(m_dTargetPosY);
			Sleep(20); //!!

			SetStep(eCAMERA_CAL_FLOW_GANTRY_XY_MEASURE_POS_1ST_CHECK, _T("eCAMERA_CAL_FLOW_GANTRY_XY_MEASURE_POS_1ST_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eCAMERA_CAL_FLOW_GANTRY_XY_MEASURE_POS_1ST_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Pos(m_dTargetPosX) && Devs::m_GantryMotion.Is_Gantry_Y_Pos(m_dTargetPosY))
			{
				SetStep(eCAMERA_CAL_FLOW_CAMERA_Z1_INSPECTION_POS, _T("eCAMERA_CAL_FLOW_CAMERA_Z1_INSPECTION_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eCAMERA_CAL_FLOW_GANTRY_XY_PRE_ALIGN_POS_CHECK Time Out"), eCAMERA_CAL_FLOW + 4);
				SetStep(eCAMERA_CAL_FLOW_ERROR, _T("eCAMERA_CAL_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eCAMERA_CAL_FLOW_GANTRY_XY_MEASURE_POS_1ST_CHECK, _T("eCAMERA_CAL_FLOW_GANTRY_XY_MEASURE_POS_1ST_CHECK"));
			}
			break;

		case eCAMERA_CAL_FLOW_GANTRY_XY_MEASURE_POS_2ND:
			m_dTargetPosX = dPosX = SharedInfo::m_CameraCalTable[m_nCurPoint].dPixelX + m_dOffsetCx;
			m_dTargetPosY = dPosY = SharedInfo::m_CameraCalTable[m_nCurPoint].dPixelY + m_dOffsetCy;

			Devs::m_GantryMotion.Move_Gantry_X_Pos(m_dTargetPosX, FALSE);
			Sleep(20); //!!
			Devs::m_GantryMotion.Move_Gantry_Y_Pos(m_dTargetPosY);
			Sleep(20); //!!

			SetStep(eCAMERA_CAL_FLOW_GANTRY_XY_MEASURE_POS_2ND_CHECK, _T("eCAMERA_CAL_FLOW_GANTRY_XY_MEASURE_POS_2ND_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eCAMERA_CAL_FLOW_GANTRY_XY_MEASURE_POS_2ND_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Pos(m_dTargetPosX) && Devs::m_GantryMotion.Is_Gantry_Y_Pos(m_dTargetPosY))
			{
				SetStep(eCAMERA_CAL_FLOW_AUTOFOCUS_CHECK, _T("eCAMERA_CAL_FLOW_AUTOFOCUS_CHECK"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eCAMERA_CAL_FLOW_AXIS_GANTRY_XY_MEASURE_POS_2ND_CHECK Time Out"), eCAMERA_CAL_FLOW + 6);
				SetStep(eCAMERA_CAL_FLOW_ERROR, _T("eCAMERA_CAL_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eCAMERA_CAL_FLOW_GANTRY_XY_MEASURE_POS_2ND_CHECK, _T("eCAMERA_CAL_FLOW_GANTRY_XY_MEASURE_POS_2ND_CHECK"));
			}
			break;

		case eCAMERA_CAL_FLOW_CAMERA_Z1_INSPECTION_POS:
			Devs::m_GantryMotion.Move_GantryZ1_InspectionReview_Pos();

			SetStep(eCAMERA_CAL_FLOW_CAMERA_Z1_INSPECTION_POS_CHECK, _T("eCAMERA_CAL_FLOW_GANTRY_Z1_PRE_ALIGN_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eCAMERA_CAL_FLOW_CAMERA_Z1_INSPECTION_POS_CHECK:
			if (Devs::m_GantryMotion.Is_GantryZ1_InspectionReview_Pos())
			{
				Sleep(500); //!!
				SetStep(eCAMERA_CAL_FLOW_AUTOFOCUS_CHECK, _T("eCAMERA_CAL_FLOW_AUTOFOCUS_CHECK"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eCAMERA_CAL_FLOW_CAMERA_Z1_INSPECTION_POS_CHECK Time Out"), eCAMERA_CAL_FLOW + 5);
				SetStep(eCAMERA_CAL_FLOW_ERROR, _T("eCAMERA_CAL_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eCAMERA_CAL_FLOW_CAMERA_Z1_INSPECTION_POS_CHECK, _T("eCAMERA_CAL_FLOW_CAMERA_Z1_INSPECTION_POS_CHECK"));
			}
			break;

		case eCAMERA_CAL_FLOW_AUTOFOCUS_CHECK:
			if (m_bCentered == FALSE) //KJT 20210820
			{
				if (CModelData::m_AlignPara.Info.nVerticalMainAlignFocusType == eFocusType_Laser || CModelData::m_AlignPara.Info.nVerticalMainAlignFocusType == eFocusType_Both)
					SetStep(eCAMERA_CAL_FLOW_LASER_FOCUS_START, _T("eCAMERA_CAL_FLOW_LASER_FOCUS_START"));
				else if (CModelData::m_AlignPara.Info.nVerticalMainAlignFocusType == eFocusType_Image)
					SetStep(eCAMERA_CAL_FLOW_IMAGE_FOCUS_START, _T("eCAMERA_CAL_FLOW_IMAGE_FOCUS_START"));
				else
				{
					if (CSystemData::m_CameraCal.Info[m_nCalID].m_nCaliFindType == eFind_Circle) //KJT 20210820 Add
						SetStep(eCAMERA_CAL_FLOW_VISION_GRAB_CIRCLE, _T("eCAMERA_CAL_FLOW_VISION_GRAB_CIRCLE"));
					else
						SetStep(eCAMERA_CAL_FLOW_VISION_GRAB_BLOB, _T("eCAMERA_CAL_FLOW_VISION_GRAB_BLOB"));
				}
			}
			else
			{
				if (CSystemData::m_CameraCal.Info[m_nCalID].m_nCaliFindType == eFind_Circle) //KJT 20210820 Add
					SetStep(eCAMERA_CAL_FLOW_VISION_GRAB_CIRCLE, _T("eCAMERA_CAL_FLOW_VISION_GRAB_CIRCLE"));
				else
					SetStep(eCAMERA_CAL_FLOW_VISION_GRAB_BLOB, _T("eCAMERA_CAL_FLOW_VISION_GRAB_BLOB"));
			}
			break;

		case eCAMERA_CAL_FLOW_LASER_FOCUS_START:
			bResult = Devs::m_GantryMotion.LaserFocusMove();
			if (bResult) //KJT 20210601
			{
				SetStep(eCAMERA_CAL_FLOW_LASER_FOCUS_CHECK, _T("eCAMERA_CAL_FLOW_LASER_FOCUS_CHECK"));
				SetTimeOut(TIME_OUT_MOTION);
			}
			else
			{
				if (CModelData::m_AlignPara.Info.nVerticalMainAlignFocusType == eFocusType_Both)
					SetStep(eCAMERA_CAL_FLOW_IMAGE_FOCUS_START, _T("eCAMERA_CAL_FLOW_IMAGE_FOCUS_START"));
				else
				{
					if (CSystemData::m_CameraCal.Info[m_nCalID].m_nCaliFindType == eFind_Circle) //KJT 20210820 Add
						SetStep(eCAMERA_CAL_FLOW_VISION_GRAB_CIRCLE, _T("eCAMERA_CAL_FLOW_VISION_GRAB_CIRCLE"));
					else
						SetStep(eCAMERA_CAL_FLOW_VISION_GRAB_BLOB, _T("eCAMERA_CAL_FLOW_VISION_GRAB_BLOB"));
				}
			}
			break;

		case eCAMERA_CAL_FLOW_LASER_FOCUS_CHECK:
			if (Devs::m_GantryMotion.LaserFocusMoveCheck())
			{
				Sleep(500); //!!	//KJT 20210321

				if (CModelData::m_AlignPara.Info.nVerticalMainAlignFocusType == eFocusType_Both)
					SetStep(eCAMERA_CAL_FLOW_IMAGE_FOCUS_START, _T("eCAMERA_CAL_FLOW_IMAGE_FOCUS_START"));
				else
				{
					if (CSystemData::m_CameraCal.Info[m_nCalID].m_nCaliFindType == eFind_Circle) //KJT 20210820 Add
						SetStep(eCAMERA_CAL_FLOW_VISION_GRAB_CIRCLE, _T("eCAMERA_CAL_FLOW_VISION_GRAB_CIRCLE"));
					else
						SetStep(eCAMERA_CAL_FLOW_VISION_GRAB_BLOB, _T("eCAMERA_CAL_FLOW_VISION_GRAB_BLOB"));
				}
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eCAMERA_CAL_FLOW_LASER_FOCUS_CHECK Time Out"), eCAMERA_CAL_FLOW + 7);
				SetStep(eCAMERA_CAL_FLOW_ERROR, _T("eCAMERA_CAL_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eCAMERA_CAL_FLOW_LASER_FOCUS_CHECK, _T("eCAMERA_CAL_FLOW_LASER_FOCUS_CHECK"));
			}
			break;

		case eCAMERA_CAL_FLOW_IMAGE_FOCUS_START:
#ifndef SIM_MODE
			switch (m_nCalID)
			{
			case eMAPPING_ID_10X:
				g_pReview10x->m_bAfEnd = FALSE;
				g_pReview10x->AutofoucsRun();
				break;
			case eMAPPING_ID_20X:
				g_pReview10x->m_bAfEnd = FALSE;
				g_pReview10x->AutofoucsRun();
				break;
			case eMAPPING_ID_50X:
				g_pReview10x->m_bAfEnd = FALSE;
				g_pReview10x->AutofoucsRun();
				break;
			}
#endif
			SetStep(eCAMERA_CAL_FLOW_IMAGE_FOCUS_CHECK, _T("eCAMERA_CAL_FLOW_IMAGE_FOCUS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eCAMERA_CAL_FLOW_IMAGE_FOCUS_CHECK:
#ifndef SIM_MODE
			bResult = FALSE;
			switch (m_nCalID)
			{
			case eMAPPING_ID_10X:
				if (g_pReview10x->m_bAfEnd == TRUE)
					bResult = TRUE;
				break;
			case eMAPPING_ID_20X:
				if (g_pReview10x->m_bAfEnd == TRUE)
					bResult = TRUE;
				break;
			case eMAPPING_ID_50X:
				if (g_pReview10x->m_bAfEnd == TRUE)
					bResult = TRUE;
				break;
			}
#else
			bResult = TRUE;
#endif
			if (bResult)
			{
				Sleep(IMAGE_FOCUS_DELAY);
				if (CSystemData::m_CameraCal.Info[m_nCalID].m_nCaliFindType == eFind_Circle) //KJT 20210820 Add
					SetStep(eCAMERA_CAL_FLOW_VISION_GRAB_CIRCLE, _T("eCAMERA_CAL_FLOW_VISION_GRAB_CIRCLE"));
				else
					SetStep(eCAMERA_CAL_FLOW_VISION_GRAB_BLOB, _T("eCAMERA_CAL_FLOW_VISION_GRAB_BLOB"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eCAMERA_CAL_FLOW_IMAGE_FOCUS_CHECK Time Out"), eCAMERA_CAL_FLOW + 8);
				SetStep(eCAMERA_CAL_FLOW_ERROR, _T("eCAMERA_CAL_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eCAMERA_CAL_FLOW_IMAGE_FOCUS_CHECK, _T("eCAMERA_CAL_FLOW_IMAGE_FOCUS_CHECK"));
			}
			break;

		case eCAMERA_CAL_FLOW_VISION_GRAB_CIRCLE:
#ifndef SIM_MODE
			m_dVisionResult[0] = 0;
			m_dVisionResult[1] = 0;

			ModCirclePara.dRadius = CModelData::m_GlassPara.Info.dGlassAlignMarkSizeX / 2.0; // 0.1 / 2; // CModelData::m_GlassPara.Info.dGlassAlignMarkSizeX; //KJT 20210312
			switch (m_nCalID)
			{
			case eMAPPING_ID_10X:
				m_CameraInfo.nBin = CModelData::m_AlignPara.Info.nVerticalMainAlignThreshold;
				m_ModResult = Devs::m_Camera10X->FindModCircleFind(ModCirclePara);
				Sleep(200);
				m_ModelFindData = Devs::m_Camera10X->GetModelFindData();
				break;

			case eMAPPING_ID_20X:
				m_CameraInfo.nBin = CModelData::m_AlignPara.Info.nVerticalMainAlignThreshold;
				m_ModResult = Devs::m_Camera10X->FindModCircleFind(ModCirclePara);
				Sleep(200);
				m_ModelFindData = Devs::m_Camera10X->GetModelFindData();
				break;
			case eMAPPING_ID_50X:
				m_CameraInfo.nBin = CModelData::m_AlignPara.Info.nVerticalMainAlignThreshold;
				m_ModResult = Devs::m_Camera10X->FindModCircleFind(ModCirclePara);
				Sleep(200);
				m_ModelFindData = Devs::m_Camera10X->GetModelFindData();
				break;
			}

			if (m_ModResult.bResult == FALSE) //KJT 20210404
			{
				m_nGrabFailRetryCnt++;
				if (m_nGrabFailRetryCnt > 3)
				{
					SharedInfo::SetAlarm(_T("eCAMERA_CAL_FLOW_IMAGE_FOCUS_CHECK Retry 3 Over !!!"), eCAMERA_CAL_FLOW + 16);
					SetStep(eCAMERA_CAL_FLOW_ERROR, _T("eCAMERA_CAL_FLOW_ERROR"));
					break;
				}

				SetStep(eCAMERA_CAL_FLOW_AUTOFOCUS_CHECK, _T("eCAMERA_CAL_FLOW_AUTOFOCUS_CHECK"));
				break;
			}
			else
				m_nGrabFailRetryCnt = 0;

			m_dVisionResult[0] = m_ModelFindData.dPosX;
			m_dVisionResult[1] = m_ModelFindData.dPosY;
#endif

#ifndef SIM_MODE
			if (m_ModelFindData.dScore < 90 || //CSystemData::m_Stage.Info.m_dTargetScore ||
				(fabs(1.0 - m_ModelFindData.dScale) > 0.1 ))//CSystemData::m_Stage.Info.m_dTargetScale)) //Score:90, Scale +-0.1
			{
				m_nGrabRetryCnt++;

				Str.Format(_T("Find Result Error Score:%.5f, Scale:%.5f (GrabRetry:%d)"), m_ModelFindData.dScore, m_ModelFindData.dScale, m_nGrabRetryCnt);
				Total_Msg(Str);

				//if (CSystemData::m_Option.Info.m_bGrabErrorImageSave)
				{
					GetLocalTime(&st);
					StrDirPath.Format(_T("%s\\GrabError\\CameraCal"), SharedInfo::STR_SAVE_IMAGE_DIR_PATH);
					::CreateDirectory(StrDirPath, NULL);
					dPosZ1 = SharedInfo::GetCmdPos(AXIS_CAMERA_Z1);
					StrFilePath.Format(_T("%s\\CameraCal_%04d%02d%02d_%d_Point%d_Retry%d_X%.5f_Y%.5f_Z%.5f.png"),
						StrDirPath, st.wYear, st.wMonth, st.wDay, m_nCurRepeatCnt, m_nCurPoint, m_nGrabRetryCnt, m_dTargetPosX, m_dTargetPosY, dPosZ1);
					Devs::m_Camera10X->SaveDisplayImage(StrFilePath);
				}

				if (m_nGrabRetryCnt > 3)
				{
					m_nGrabRetryCnt = 0;
					SharedInfo::SetAlarm(_T("eCAMERA_CAL_FLOW_VISION_GRAB_CIRCLE Retry 3 Over !!!"), eCAMERA_CAL_FLOW + 16);
					SetStep(eCAMERA_CAL_FLOW_ERROR, _T("eCAMERA_CAL_FLOW_ERROR"));
					break;
				}
				else
				{
					m_nGrabRetryCnt = 0;
					SetStep(eCAMERA_CAL_FLOW_AUTOFOCUS_CHECK, _T("eCAMERA_CAL_FLOW_AUTOFOCUS_CHECK"));
					break;
				}
			}
			else
			{
				if (m_bCentered == FALSE)
					SetStep(eCAMERA_CAL_FLOW_VISION_GRAB_1ST_CHECK, _T("eCAMERA_CAL_FLOW_VISION_GRAB_1ST_CHECK"));
				else
					SetStep(eCAMERA_CAL_FLOW_VISION_GRAB_2ND_CHECK, _T("eCAMERA_CAL_FLOW_VISION_GRAB_2ND_CHECK"));
			}
#endif
			break;

		case eCAMERA_CAL_FLOW_VISION_GRAB_BLOB: //KJT 20210820 Add
#ifndef SIM_MODE
			m_dVisionResult[0] = 0.0;
			m_dVisionResult[1] = 0.0;

			bResult = Devs::m_GantryMotion.FindVerticalBlob_Review10X(&m_dVisionResult[0], &m_dVisionResult[1]);
			if (bResult == FALSE) //KJT 20210404
			{
				m_nGrabFailRetryCnt++;
				if (m_nGrabFailRetryCnt > 3)
				{
					SharedInfo::SetAlarm(_T("eCAMERA_CAL_FLOW_VISION_GRAB_BLOB Retry 3 Over !!!"), eCAMERA_CAL_FLOW + 16);
					SetStep(eCAMERA_CAL_FLOW_ERROR, _T("eCAMERA_CAL_FLOW_ERROR"));
					break;
				}

				SetStep(eCAMERA_CAL_FLOW_AUTOFOCUS_CHECK, _T("eCAMERA_CAL_FLOW_AUTOFOCUS_CHECK"));
				break;
			}
			else
				m_nGrabFailRetryCnt = 0;

			if (m_bCentered == FALSE)
				SetStep(eCAMERA_CAL_FLOW_VISION_GRAB_1ST_CHECK, _T("eCAMERA_CAL_FLOW_VISION_GRAB_1ST_CHECK"));
			else
				SetStep(eCAMERA_CAL_FLOW_VISION_GRAB_2ND_CHECK, _T("eCAMERA_CAL_FLOW_VISION_GRAB_2ND_CHECK"));
#endif
			break;

		case eCAMERA_CAL_FLOW_VISION_GRAB_1ST_CHECK:
#ifndef SIM_MODE
			dDiffX = m_dVisionResult[0];
			dDiffY = m_dVisionResult[1];
#else
			dDiffX = 0.0;
			dDiffY = 0.0;
#endif
			if (fabs(dDiffX) < 0.0002 && fabs(dDiffY) < 0.0002)
			{
				m_bCentered = TRUE;

				m_dOffsetCx = SharedInfo::GetCmdPos(AXIS_GANTRY_X) - m_dCenterPosX;
				m_dOffsetCy = SharedInfo::GetActPos(AXIS_VIRTUAL_GANTRY_Y) - m_dCenterPosY;

				Sleep(CSystemData::m_CameraCal.Info[m_nCalID].m_nCalibDelay);
				SetStep(eCAMERA_CAL_FLOW_GANTRY_XY_MEASURE_POS_2ND, _T("eCAMERA_CAL_FLOW_GANTRY_XY_MEASURE_POS_2ND"));
			}
			else
			{
				SetStep(eCAMERA_CAL_FLOW_GANTRY_XY_CENTERING_MOVE, _T("eCAMERA_CAL_FLOW_GANTRY_XY_CENTERING_MOVE"));
			}
			break;

		case eCAMERA_CAL_FLOW_GANTRY_XY_CENTERING_MOVE:
#ifndef SIM_MODE
			m_dTargetPosX = SharedInfo::GetCmdPos(AXIS_GANTRY_X);
			m_dTargetPosY = SharedInfo::GetActPos(AXIS_VIRTUAL_GANTRY_Y);
			if (fabs(m_dVisionResult[0]) > 0.0003 && fabs(m_dVisionResult[0]) < 2.0)
			{
				m_dTargetPosX += m_dVisionResult[0];

				Devs::m_GantryMotion.Move_Gantry_X_Pos(m_dTargetPosX, FALSE);
				Sleep(20);
			}

			if (fabs(m_dVisionResult[1]) > 0.0003 && fabs(m_dVisionResult[1]) < 2.0)
			{
				m_dTargetPosY += m_dVisionResult[1];

				Devs::m_GantryMotion.Move_Gantry_Y_Pos(m_dTargetPosY);
				Sleep(20);
			}
#else
			m_dTargetPosX = SharedInfo::GetCmdPos(AXIS_GANTRY_X);
			m_dTargetPosY = SharedInfo::GetActPos(AXIS_VIRTUAL_GANTRY_Y);
			Devs::m_GantryMotion.Move_Gantry_X_Pos(m_dTargetPosX, FALSE);
			Devs::m_GantryMotion.Move_Gantry_Y_Pos(m_dTargetPosY);
#endif
			SetStep(eCAMERA_CAL_FLOW_GANTRY_XY_CENTERING_MOVE_DONE_CHECK, _T("eCAMERA_CAL_FLOW_GANTRY_XY_CENTERING_MOVE_DONE_CHECK"));
			break;

		case eCAMERA_CAL_FLOW_GANTRY_XY_CENTERING_MOVE_DONE_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Pos(m_dTargetPosX) && Devs::m_GantryMotion.Is_Gantry_Y_Pos(m_dTargetPosY))
			{
				SetStep(eCAMERA_CAL_FLOW_VISION_GRAB_CIRCLE, _T("eCAMERA_CAL_FLOW_VISION_GRAB_CIRCLE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eCAMERA_CAL_FLOW_GANTRY_XY_CENTERING_MOVE_DONE_CHECK Time Out !!!"), eCAMERA_CAL_FLOW + 11);
				SetStep(eCAMERA_CAL_FLOW_ERROR, _T("eCAMERA_CAL_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eCAMERA_CAL_FLOW_GANTRY_XY_CENTERING_MOVE_DONE_CHECK, _T("eCAMERA_CAL_FLOW_GANTRY_XY_CENTERING_MOVE_DONE_CHECK"));
			}
			break;

		case eCAMERA_CAL_FLOW_VISION_GRAB_2ND_CHECK:
#ifndef SIM_MODE
			SharedInfo::m_CameraCalTable[m_nCurPoint].dWorldX = ((SharedInfo::m_CameraCalTable[m_nCurPoint].dPixelX) * (-1)) - (m_dVisionResult[0] - SharedInfo::m_CameraCalTable[m_nCurPoint].dWorldX);
			SharedInfo::m_CameraCalTable[m_nCurPoint].dWorldY = ((SharedInfo::m_CameraCalTable[m_nCurPoint].dPixelY) * (-1)) - (m_dVisionResult[1] - SharedInfo::m_CameraCalTable[m_nCurPoint].dWorldY);
#endif
			if (++m_nCurPoint >= SharedInfo::m_nCameraCalTableCnt)
			{
				m_nCurPoint = 0;
				SetStep(eCAMERA_CAL_FLOW_CAL_DATA, _T("eCAMERA_CAL_FLOW_CAL_DATA"));
			}
			else
			{
				Sleep(CSystemData::m_CameraCal.Info[m_nCalID].m_nCalibDelay);
				SetStep(eCAMERA_CAL_FLOW_GANTRY_XY_MEASURE_POS_2ND, _T("eCAMERA_CAL_FLOW_GANTRY_XY_MEASURE_POS_2ND"));
			}
			break;



		case eCAMERA_CAL_FLOW_CAL_DATA:
			dPixelX = 0.0, dPixelY = 0.0, dWorldX = 0.0, dWorldY = 0.0;
#ifndef SIM_MODE
			if (m_nCurRepeatCnt > 0)
				Devs::m_Camera10X->ClearCalibData();

			for (int i = 0; i < SharedInfo::m_nCameraCalTableCnt; i++)
			{
				dWorldX = SharedInfo::m_CameraCalTable[i].dPixelX * (-1);
				dWorldY = SharedInfo::m_CameraCalTable[i].dPixelY * (-1);

				dPixelX = SharedInfo::m_CameraCalTable[i].dWorldX + dWorldX;
				dPixelY = SharedInfo::m_CameraCalTable[i].dWorldY + dWorldY;

				Devs::m_Camera10X->SetCalibData(i, dPixelX, dPixelY, dWorldX, dWorldY, 0);
			}

			Devs::m_Camera10X->MakeCalibData(m_nCalID);
			Sleep(500);
			Devs::m_Camera10X->LoadCalibData(m_nCalID);
#endif
			m_nCurRepeatCnt++;
			if (m_nCurRepeatCnt >= CSystemData::m_CameraCal.Info[m_nCalID].m_nCalibRepeat)
			{
				SharedInfo::LightAllOff();
				SetStep(eCAMERA_CAL_FLOW_FINISH_GANTRY_Z1_WAIT_POS, _T("eCAMERA_CAL_FLOW_FINISH_GANTRY_Z1_WAIT_POS"));
			}
			else
			{
				Sleep(CSystemData::m_CameraCal.Info[m_nCalID].m_nCalibDelay);
				SetStep(eCAMERA_CAL_FLOW_GANTRY_XY_MEASURE_POS_2ND, _T("eCAMERA_CAL_FLOW_GANTRY_XY_MEASURE_POS_2ND"));
			}			
			break;

		case eCAMERA_CAL_FLOW_FINISH_GANTRY_Z1_WAIT_POS:
			Devs::m_GantryMotion.Move_GantryZ_All_Wait_Pos();

			SetStep(eCAMERA_CAL_FLOW_FINISH_GANTRY_Z1_WAIT_POS_CHECK, _T("eCAMERA_CAL_FLOW_FINISH_GANTRY_Z1_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);

			break;

		case eCAMERA_CAL_FLOW_FINISH_GANTRY_Z1_WAIT_POS_CHECK:
			if (Devs::m_GantryMotion.Is_GantryZ_All_Wait_Pos())
			{
				SetStep(eCAMERA_CAL_FLOW_FINISH_GANTRY_XY_WAIT_POS, _T("eCAMERA_CAL_FLOW_FINISH_GANTRY_XY_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eCAMERA_CAL_FLOW_FINISH_GANTRY_Z1_WAIT_POS_CHECK Time Out"), eCAMERA_CAL_FLOW + 9);
				SetStep(eCAMERA_CAL_FLOW_ERROR, _T("eCAMERA_CAL_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eCAMERA_CAL_FLOW_FINISH_GANTRY_Z1_WAIT_POS_CHECK, _T("eCAMERA_CAL_FLOW_FINISH_GANTRY_Z1_WAIT_POS_CHECK"));
			}
			break;

		case eCAMERA_CAL_FLOW_FINISH_GANTRY_XY_WAIT_POS:
			Devs::m_GantryMotion.Move_Gantry_X_Wait_Pos();
			Sleep(20); //!!
			Devs::m_GantryMotion.Move_Gantry_Y_Wait_Pos();
			Sleep(20); //!!

			SetStep(eCAMERA_CAL_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK, _T("eCAMERA_CAL_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eCAMERA_CAL_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Wait_Pos() && Devs::m_GantryMotion.Is_Gantry_Y_Wait_Pos())
			{
				SetStep(eCAMERA_CAL_FLOW_DONE, _T("eCAMERA_CAL_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("eCAMERA_CAL_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK Time Out"), eCAMERA_CAL_FLOW + 10);
				SetStep(eCAMERA_CAL_FLOW_ERROR, _T("eCAMERA_CAL_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(eCAMERA_CAL_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK, _T("eCAMERA_CAL_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK"));
			}
			break;

		case eCAMERA_CAL_FLOW_ERROR:
			break;

		case eCAMERA_CAL_FLOW_DONE:
		{
			SharedInfo::nPrevFlowID = eCAMERA_CAL_FLOW; //KJT 20210326

			m_bFlowDone = TRUE;

			SharedInfo::CalTactTime(_T("CAMERA_CAL_FLOW"), m_timeStart); //KJT 20210329

			SetStep(eCAMERA_CAL_FLOW_IDLE, _T("eCAMERA_CAL_FLOW_IDLE"));
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

BOOL CCameraCalFlow::FlowInterlock()
{
	CString Str = _T("");

	if (Devs::m_CassetteMotion.Is_CSTPickUpUnitBwd() == FALSE)
	{
		SharedInfo::SetAlarm(_T("Cst PickUnit Backward Error"), eCAMERA_CAL_FLOW + 11);
		return FALSE;
	}
	//if (SharedInfo::DInputValue[_DIN_CST_UNSAFE_POS_DETECT] == TRUE)
	//{
	//	SharedInfo::SetAlarm(_T("CST Unsafe Pos Error"), eCAMERA_CAL_FLOW + 12);
	//	return FALSE;
	//}
	//if (SharedInfo::DInputValue[_DIN_CST_BACKWARD_DETECT] == TRUE)
	//{
	//	SharedInfo::SetAlarm(_T("CST Backward Detect Error"), eCAMERA_CAL_FLOW + 13);
	//	return FALSE;
	//}

	if (SharedInfo::m_nCameraCalTableCnt <= 0)
	{
		SharedInfo::SetAlarm(_T("Camera Cal Point Count Error (CurCount <= 0)"), eCAMERA_CAL_FLOW + 14);
		return FALSE;
	}

	return TRUE;
}

int CCameraCalFlow::SaveCameraCalResult(int nRepeatCount)
{
	
	return 0;
}