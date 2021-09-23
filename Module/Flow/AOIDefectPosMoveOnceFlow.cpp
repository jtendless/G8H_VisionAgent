#include "stdafx.h"
#include "AOIDefectPosMoveOnceFlow.h"
#include "Log/Logger.h"
#include "Vision/Devs.h"
#include "Data/ModelData.h"
#include "Data/ManualData.h"
#include "CamAreaModul.h"
#include "Data/SystemData.h"
#include "VisionAgent.h"
#include "VisionAgentDlg.h"
#include "FmmLight1.h"

CAOIDefectPosMoveOnceFlow::CAOIDefectPosMoveOnceFlow()
{
}


CAOIDefectPosMoveOnceFlow::~CAOIDefectPosMoveOnceFlow()
{
}

BOOL CAOIDefectPosMoveOnceFlow::InitProcess()
{
	m_StateComplete = NULL;
	m_FlowFinish = TRUE;
	m_bTerminate = FALSE;
	m_bFlowDone = TRUE;

	m_dTargetPosX = 0.0;
	m_dTargetPosY = 0.0;
	m_bBackLightWith = FALSE;

	//SetProcessLog(Process_Msg);
	//SetAlarmLog(Alarm_Msg);

	hHandle = CreateEvent(NULL, TRUE, FALSE, NULL);
	SetHandle(hHandle);
	pThread = AfxBeginThread(ThreadFunction, this);
	//pMappingProc = CMappingProc::GetInstance();
	return TRUE;
}

BOOL CAOIDefectPosMoveOnceFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_IDLE, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_IDLE"));

	if (hHandle != NULL)
	{
		CloseHandle(hHandle);
		hHandle = NULL;
	}

	return TRUE;
}
BOOL CAOIDefectPosMoveOnceFlow::Start(double dPosX, double dPosY, BOOL bBackLightWith)
{
	m_dTargetPosX = dPosX;
	m_dTargetPosY = dPosY;
	m_bBackLightWith = bBackLightWith;

	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_START, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_START"));
	return TRUE;
}
BOOL CAOIDefectPosMoveOnceFlow::Stop()
{
	m_bStopBit = TRUE;
	return TRUE;
}
UINT CAOIDefectPosMoveOnceFlow::ThreadFunction(LPVOID lpParam)
{
	CAOIDefectPosMoveOnceFlow* pFlow = NULL;

	pFlow = (CAOIDefectPosMoveOnceFlow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}

VOID CAOIDefectPosMoveOnceFlow::ThreadFunctionEntry(VOID)
{
	DWORD	dwResult = 0;
	double	dStrt_Time = GetTickCount();
	double	dEnd_Time = GetTickCount();
	double	dWait_Time = GetTickCount();
	int		nWork_Mask_Mode = -1;
	int		nWork_Mask_Index = -1;
	BOOL	bComplete_Step = FALSE;
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	int nBackLightVal[BACKLIGHT_CH_COUNT] = { BACKLIGHT_OFF_VALUE, };

	double dPos = 0.0, dDiff = 0.0;

	while (m_FlowFinish)
	{
		WaitForSingleObject(hHandle, INFINITE);
		ResetEvent(hHandle);

		if (SharedInfo::bMachineStopFlag == TRUE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}

		switch (GetCurrentTotalStep())
		{
		case _eAOI_DEFECT_POS_MOVE_ONCE_FLOW_IDLE:
		{
			break;
		}
		case _eAOI_DEFECT_POS_MOVE_ONCE_FLOW_START:
		{
			m_timeStart = CTime::GetCurrentTime(); //KJT 20210329
			SharedInfo::m_timeUnitTact = m_timeStart;

			SharedInfo::nCurFlowID = eAOI_DEFECT_POS_MOVE_ONCE_FLOW;

			SharedInfo::nGantryZ1View = eViewReview10X;

			if (SharedInfo::LoadGlassMappingData() == FALSE) //KJT 20210524
			{
				SetStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_ERROR, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_ERROR"));
				break;
			}
			//if (SharedInfo::LoadSwMappingData() == FALSE) //KJT 20210524
			//{
			//	SetStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_ERROR, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_ERROR"));
			//	break;
			//}

			//g_CommLight_8ch.SetLight_Review_Coaxial(0);
			//g_CommLight_12ch.SetLight_Review_Ring(0);
			//g_CommLight_8ch.SetLight_PreAlign(0, 0);

			//g_CommMLCLedLight.AoiLightOff();
			//g_CommMLCLedLight.BackLightOff();

			//SharedInfo::LightAllOff();

			for (int i = 0; i < BACKLIGHT_CH_COUNT; i++)
				nBackLightVal[i] = CModelData::m_InspectionPara.Info.nAOIReviewBacklight; // 10;

			SetStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_INTERLOCK_CHECK, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_INTERLOCK_CHECK"));
			break;
		}

		case _eAOI_DEFECT_POS_MOVE_ONCE_FLOW_INTERLOCK_CHECK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_ERROR, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_ERROR"));
			}
			else
			{
				SetStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_UNLOADER_READY, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_UNLOADER_READY"));
			}			
			break;

#pragma region //Unloader Ready
		case _eAOI_DEFECT_POS_MOVE_ONCE_FLOW_UNLOADER_READY:
			Devs::m_Ready_UnloaderFlow.Start();

			SetStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_UNLOADER_READY_CHECK, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_UNLOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eAOI_DEFECT_POS_MOVE_ONCE_FLOW_UNLOADER_READY_CHECK:
			if (Devs::m_Ready_UnloaderFlow.IsFlowDone())
			{
				SetStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_LOADER_READY, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_LOADER_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_UNLOADER_READY_CHECK : Time Out !!!"), eAOI_DEFECT_POS_MOVE_ONCE_FLOW + 0);
				SetStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_ERROR, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_UNLOADER_READY_CHECK, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_UNLOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Loader Ready
		case _eAOI_DEFECT_POS_MOVE_ONCE_FLOW_LOADER_READY:
			Devs::m_Ready_LoaderFlow.Start();

			SetStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_LOADER_READY_CHECK, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_LOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eAOI_DEFECT_POS_MOVE_ONCE_FLOW_LOADER_READY_CHECK:
			if (Devs::m_Ready_LoaderFlow.IsFlowDone())
			{
				//SetStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_BOX_CAMERA_READY, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_BOX_CAMERA_READY"));
				SetStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_GANTRY_ZX_READY, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_GANTRY_ZX_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_LOADER_READY_CHECK : Time Out !!!"), eAOI_DEFECT_POS_MOVE_ONCE_FLOW + 1);
				SetStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_ERROR, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_LOADER_READY_CHECK, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_LOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Box Camera Ready
//		case _eAOI_DEFECT_POS_MOVE_ONCE_FLOW_BOX_CAMERA_READY:
//			Devs::m_BoxMotion.BoxAlignCameraYL_WaitPos();
//			Sleep(20);
//			Devs::m_BoxMotion.BoxAlignCameraYR_WaitPos();
//			Sleep(500); //!!
//
//			SetStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_BOX_CAMERA_READY_CHECK, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_BOX_CAMERA_READY_CHECK"));
//			SetTimeOut(TIME_OUT_MOTION);
//			break;
//
//		case _eAOI_DEFECT_POS_MOVE_ONCE_FLOW_BOX_CAMERA_READY_CHECK:
//			if (Devs::m_BoxMotion.Is_BoxAlignCameraYL_WaitPos() == TRUE && Devs::m_BoxMotion.Is_BoxAlignCameraYR_WaitPos() == TRUE)
//			{
//				dPos = SharedInfo::GetCmdPos(AXIS_CAMERA_Z1);
//				dDiff = fabs(dPos) - fabs(CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_InspectionReview_Pos);
//				//!!!
//				if (SharedInfo::GetCmdPos(AXIS_CAMERA_Z2) < CManualData::m_ManualDataGantry.Info.m_dGantry_Z2_Wait_Pos - 0.002 ||
//					SharedInfo::GetCmdPos(AXIS_3D_CAMERA_MAIN_Z) < CManualData::m_ManualDataGantry.Info.m_d3D_Camera_Main_Z_Wait_Pos - 0.002)
//					SetStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_GANTRY_ZX_READY, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_GANTRY_ZX_READY"));
//#if 0
//				else if (dDiff < 0.3)
//#else
//				else if (SharedInfo::m_bCameraZ1AOIReviewDown == TRUE)
//#endif
//				{
//					if (SharedInfo::GetActPos(AXIS_VIRTUAL_GANTRY_Y) < CModelData::m_GlassPara.Info.dGlassAlignMark_LB_Y - 0.002 || //-240.0
//						SharedInfo::GetActPos(AXIS_VIRTUAL_GANTRY_Y) > CModelData::m_GlassPara.Info.dGlassAlignMark_LT_Y + 0.002 || //240.0
//						SharedInfo::GetCmdPos(AXIS_GANTRY_X) < CModelData::m_GlassPara.Info.dGlassAlignMark_LT_X - 0.002 || //-440.0
//						SharedInfo::GetCmdPos(AXIS_GANTRY_X) > CModelData::m_GlassPara.Info.dGlassAlignMark_RT_X + 0.002) //440.0
//						SetStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_GANTRY_ZX_READY, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_GANTRY_ZX_READY"));
//					else
//						SetStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_GANTRY_XY_MOVE_POS, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_GANTRY_XY_MOVE_POS"));
//				}
//				else
//					SetStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_GANTRY_ZX_READY, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_GANTRY_ZX_READY"));
//			}
//			else if (IsTimeOut())
//			{
//				SharedInfo::SetAlarm(_T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_BOX_CAMERA_READY_CHECK : Time Out !!!"), eAOI_DEFECT_POS_MOVE_ONCE_FLOW + 2);
//				SetStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_ERROR, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_ERROR"));
//			}
//			else
//			{
//				SetCheckStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_BOX_CAMERA_READY_CHECK, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_BOX_CAMERA_READY_CHECK"));
//			}
//			break;
#pragma endregion

#pragma region //Gantry Z,X Ready
		case _eAOI_DEFECT_POS_MOVE_ONCE_FLOW_GANTRY_ZX_READY:
			Devs::m_Ready_GantryZX_Flow.Start();

			SetStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_GANTRY_ZX_READY_CHECK, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_GANTRY_ZX_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eAOI_DEFECT_POS_MOVE_ONCE_FLOW_GANTRY_ZX_READY_CHECK:
			if (Devs::m_Ready_GantryZX_Flow.IsFlowDone())
			{
				SetStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_GANTRY_XY_MOVE_POS, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_GANTRY_XY_MOVE_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_GANTRY_ZX_READY_CHECK : Time Out !!!"), eAOI_DEFECT_POS_MOVE_ONCE_FLOW + 3);
				SetStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_ERROR, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_GANTRY_ZX_READY_CHECK, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_GANTRY_ZX_READY_CHECK"));
			}
			break;
#pragma endregion

		case _eAOI_DEFECT_POS_MOVE_ONCE_FLOW_GANTRY_XY_MOVE_POS:
			m_bBackLightWith = TRUE; //Temp
			if (m_bBackLightWith)
			{
				//g_CommMLCLedLight.BackLightOn(nBackLightVal);
				Sleep(20);
			}
			else
			{
				if (CSystemData::m_Option.Info.m_bAOIMappingGlassMode == FALSE)
				{
					//g_CommLight_8ch.SetLight_Review_Coaxial(15);
					Sleep(20);
					//g_CommLight_12ch.SetLight_Review_Ring(0);
					Sleep(20);
				}
				else
				{
					//g_CommLight_8ch.SetLight_Review_Coaxial(CModelData::m_AlignPara.Info.nVerticalMainAlignCoAxial);
					Sleep(20);
					//g_CommLight_12ch.SetLight_Review_Ring(CModelData::m_AlignPara.Info.nVerticalMainAlignRing);
					Sleep(20);
				}
			}

			SharedInfo::GetMappingPos(TRUE, CModelData::m_InspectionPara.Info.bMappingDataUse, &m_dTargetPosX, &m_dTargetPosY); //KJT 20210524

			Devs::m_GantryMotion.Move_Gantry_X_Pos(m_dTargetPosX, m_bBackLightWith);
			Sleep(GANTRY_COM_DELAY);
			Devs::m_GantryMotion.Move_Gantry_Y_Pos(m_dTargetPosY);

			SetStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_GANTRY_XY_MOVE_POS_CHECK, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_GANTRY_XY_MOVE_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eAOI_DEFECT_POS_MOVE_ONCE_FLOW_GANTRY_XY_MOVE_POS_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Pos(m_dTargetPosX) && Devs::m_GantryMotion.Is_Gantry_Y_Pos(m_dTargetPosY))
			{
				if (m_bBackLightWith == TRUE)
				{
					if (Devs::m_InspectionStageMotion.Is_BackLight_X_Pos(m_dTargetPosX) == TRUE)
						SetStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_GANTRY_Z_MOVE_INSPECTION_POS, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_GANTRY_Z_MOVE_INSPECTION_POS"));
					else
						SetCheckStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_GANTRY_XY_MOVE_POS_CHECK, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_GANTRY_XY_MOVE_POS_CHECK"));
				}
				else
					SetStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_GANTRY_Z_MOVE_INSPECTION_POS, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_GANTRY_Z_MOVE_INSPECTION_POS"));
				
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_GANTRY_XY_MOVE_POS_CHECK : Time Out !!!"), eAOI_DEFECT_POS_MOVE_ONCE_FLOW + 4);
				SetStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_ERROR, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_GANTRY_XY_MOVE_POS_CHECK, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_GANTRY_XY_MOVE_POS_CHECK"));
			}
			break;

		//case _eAOI_DEFECT_POS_MOVE_ONCE_FLOW_GANTRY_Z_MOVE_INSPECTION_POS:
		//	Devs::m_GantryMotion.Move_GantryZ2_AOI_Review_Pos();
		//	Sleep(20); //!!

		//	SetStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_GANTRY_Z_MOVE_INSPECTION_POS_CHECK, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_GANTRY_Z_MOVE_INSPECTION_POS_CHECK"));
		//	SetTimeOut(TIME_OUT_MOTION);
		//	break;

		//case _eAOI_DEFECT_POS_MOVE_ONCE_FLOW_GANTRY_Z_MOVE_INSPECTION_POS_CHECK:
		//	if (Devs::m_GantryMotion.Is_GantryZ2_AOI_Review_Pos())
		//	{
		//		SharedInfo::m_bCameraZ1AOIReviewDown = TRUE;

		//		Sleep(100);
		//		SetStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_ZOOM_20X_MOVE, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_ZOOM_20X_MOVE"));
		//	}
		//	else if (IsTimeOut())
		//	{
		//		SharedInfo::SetAlarm(_T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_GANTRY_Z_MOVE_INSPECTION_POS_CHECK : Time Out !!!"), eAOI_DEFECT_POS_MOVE_ONCE_FLOW + 5);
		//		SetStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_ERROR, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_ERROR"));
		//	}
		//	else
		//	{
		//		SetCheckStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_GANTRY_Z_MOVE_INSPECTION_POS_CHECK, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_GANTRY_Z_MOVE_INSPECTION_POS_CHECK"));
		//	}
		//	break;

//		case _eAOI_DEFECT_POS_MOVE_ONCE_FLOW_LASER_FOCUS_START:
//			Devs::m_GantryMotion.LaserFocusMove();
//
//			SetStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_LASER_FOCUS_CHECK, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_LASER_FOCUS_CHECK"));
//			SetTimeOut(TIME_OUT_MOTION);
//			break;
//
//		case _eAOI_DEFECT_POS_MOVE_ONCE_FLOW_LASER_FOCUS_CHECK:
//			if (Devs::m_GantryMotion.LaserFocusMoveCheck())
//			{
//				Sleep(500); //!!	//KJT 20210321
//
//				SetStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_IMAGE_FOCUS_START, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_IMAGE_FOCUS_START"));
//			}
//			else if (IsTimeOut())
//			{
//				SharedInfo::SetAlarm(_T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_LASER_FOCUS_CHECK : Time Out !!!"), eAOI_DEFECT_POS_MOVE_ONCE_FLOW + 6);
//				SetStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_ERROR, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_ERROR"));
//			}
//			else
//			{
//				SetCheckStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_LASER_FOCUS_CHECK, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_LASER_FOCUS_CHECK"));
//			}
//			break;
//
//		case _eAOI_DEFECT_POS_MOVE_ONCE_FLOW_IMAGE_FOCUS_START:
//#ifndef SIM_MODE
//			g_pReview10x->m_bAfEnd = FALSE;
//			g_pReview10x->AutofoucsRun();
//#endif
//			SetStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_IMAGE_FOCUS_CHECK, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_IMAGE_FOCUS_CHECK"));
//			SetTimeOut(TIME_OUT_MOTION);
//			break;
//
//		case _eAOI_DEFECT_POS_MOVE_ONCE_FLOW_IMAGE_FOCUS_CHECK:
//#ifndef SIM_MODE
//			if (g_pReview10x->m_bAfEnd == TRUE)
//			{
//				Sleep(IMAGE_FOCUS_DELAY);
//				SetStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_DONE, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_DONE"));
//			}
//			else if (IsTimeOut())
//			{
//				SharedInfo::SetAlarm(_T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_IMAGE_FOCUS_CHECK : Time Out !!!"), eAOI_DEFECT_POS_MOVE_ONCE_FLOW + 7);
//				SetStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_ERROR, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_ERROR"));
//			}
//			else
//			{
//				SetCheckStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_IMAGE_FOCUS_CHECK, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_IMAGE_FOCUS_CHECK"));
//			}
//#else
//			Sleep(IMAGE_FOCUS_DELAY);
//			SetStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_DONE, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_DONE"));
//#endif
//			break;

		case _eAOI_DEFECT_POS_MOVE_ONCE_FLOW_ZOOM_20X_MOVE:
			break;

		case _eAOI_DEFECT_POS_MOVE_ONCE_FLOW_ZOOM_20X_MOVE_CHECK:
			break;

		case _eAOI_DEFECT_POS_MOVE_ONCE_FLOW_ERROR:
			break;

		case _eAOI_DEFECT_POS_MOVE_ONCE_FLOW_DONE:
		{
			pDlg->m_SocketServer_AOI.Req_GantryXYZMoveDone(m_dTargetPosX, m_dTargetPosY, CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Inspection_AOI_Pos);

			SharedInfo::bMachineStopFlag = TRUE;
			m_bFlowDone = TRUE;

			SharedInfo::CalTactTime(_T("AOI_DEFECT_POS_MOVE_ONCE_FLOW"), m_timeStart); //KJT 20210329

			SetStep(_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_IDLE, _T("_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_IDLE"));
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

BOOL CAOIDefectPosMoveOnceFlow::FlowInterlock()
{
#if 0
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
	if (m_bBackLightWith == TRUE && SharedInfo::GetServoOnStatus(AXIS_BACKLIGHT_X) != TRUE)
	{
		Total_Msg(_T("BackLight X Servo On Check !!!"));
		return FALSE;
	}

	//Home Status Check
	if (SharedInfo::GetHomeStatus(AXIS_GANTRY_X) != TRUE)
	{
		Total_Msg(_T("Gantry X Home Status Check !!!"));
		SharedInfo::SetAlarm(Str, eAOI_DEFECT_POS_MOVE_ONCE_FLOW + 0);
		return FALSE;
	}
	if (SharedInfo::GetHomeStatus(AXIS_VIRTUAL_GANTRY_Y) != TRUE)
	{
		Total_Msg(_T("Gantry Y Home Status Check !!!"));
		return FALSE;
	}
	if (m_bBackLightWith == TRUE && SharedInfo::GetHomeStatus(AXIS_BACKLIGHT_X) != TRUE)
	{
		Total_Msg(_T("BackLight X Home Status Check !!!"));
		return FALSE;
	}
#endif

	/////////////////////////////////////////////////////////////////////////////
	if (Devs::m_LoaderMotion.CheckLoaderFlowInterlock(_T("AOIDefectPosMoveOnceFlow"), eAOI_DEFECT_POS_MOVE_ONCE_FLOW, 30) == FALSE)
	{
		return FALSE;
	}

	/////////////////////////////////////////////////////////////////////////////
	if (Devs::m_UnloaderMotion.CheckUnloaderFlowInterlock(_T("AOIDefectPosMoveOnceFlow"), eAOI_DEFECT_POS_MOVE_ONCE_FLOW, 40) == FALSE)
	{
		return FALSE;
	}

	/////////////////////////////////////////////////////////////////////////////
	if (Devs::m_GantryMotion.CheckGantryXYZFlowInterlock(_T("AOIDefectPosMoveOnceFlow"), eAOI_DEFECT_POS_MOVE_ONCE_FLOW, 50) == FALSE)
	{
		return FALSE;
	}

	return TRUE;
}