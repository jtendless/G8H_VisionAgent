#include "stdafx.h"
#include "AOIFlow.h"
#include "Log/Logger.h"
#include "Vision/Devs.h"
#include "Data/ModelData.h"
#include "Data/ManualData.h"
#include "CamAreaModul.h"
#include "Data/SystemData.h"
#include "VisionAgent.h"
#include "VisionAgentDlg.h"
#include "FmmLight1.h"

CAOIFlow::CAOIFlow()
{
}


CAOIFlow::~CAOIFlow()
{
}

BOOL CAOIFlow::InitProcess()
{
	m_StateComplete = NULL;
	m_FlowFinish = TRUE;
	m_bTerminate = FALSE;
	m_bFlowDone = TRUE;

#pragma region //Step Group
	int nGroupIndex = 0;

	m_sGroupInfo[nGroupIndex].m_bProcessingFlag = FALSE;
	m_sGroupInfo[nGroupIndex].nStartStep = _eAOI_FLOW_START;
	m_sGroupInfo[nGroupIndex].nEndStep = _eAOI_FLOW_INTERLOCK_CHECK;
	m_sGroupInfo[nGroupIndex].strGroupName.Format(_T("%d. Start"), nGroupIndex + 1);
	nGroupIndex++;

	m_sGroupInfo[nGroupIndex].m_bProcessingFlag = FALSE;
	m_sGroupInfo[nGroupIndex].nStartStep = _eAOI_FLOW_UNLOADER_READY;
	m_sGroupInfo[nGroupIndex].nEndStep = _eAOI_FLOW_GANTRY_ZX_READY_CHECK;
	m_sGroupInfo[nGroupIndex].strGroupName.Format(_T("%d. Other Axis Ready"), nGroupIndex + 1);
	nGroupIndex++;

	m_sGroupInfo[nGroupIndex].m_bProcessingFlag = FALSE;
	m_sGroupInfo[nGroupIndex].nStartStep = _eAOI_FLOW_INSPECTION_READY_REQ;
	m_sGroupInfo[nGroupIndex].nEndStep = _eAOI_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK;
	m_sGroupInfo[nGroupIndex].strGroupName.Format(_T("%d. Measure AOI"), nGroupIndex + 1);
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
BOOL CAOIFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eAOI_FLOW_IDLE, _T("_eAOI_FLOW_IDLE"));

	if (hHandle != NULL)
	{
		CloseHandle(hHandle);
		hHandle = NULL;
	}

	return TRUE;
}
BOOL CAOIFlow::Start(int nStep)
{
	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(nStep, _T("_eAOI_FLOW_START"));
	return TRUE;
}
BOOL CAOIFlow::Stop()
{
	m_bStopBit = TRUE;
	return TRUE;
}
UINT CAOIFlow::ThreadFunction(LPVOID lpParam)
{
	CAOIFlow* pFlow = NULL;

	pFlow = (CAOIFlow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}
VOID CAOIFlow::ThreadFunctionEntry(VOID)
{
	DWORD	dwResult = 0;
	double	dStrt_Time = GetTickCount();
	double	dEnd_Time = GetTickCount();
	double	dWait_Time = GetTickCount();
	int		nWork_Mask_Mode = -1;
	int		nWork_Mask_Index = -1;
	BOOL	bComplete_Step = FALSE;
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	CString Str = _T("");

	double dPosX = 0.0, dPosY = 0.0;

	while (m_FlowFinish)
	{
		WaitForSingleObject(hHandle, INFINITE);
		ResetEvent(hHandle);

		if (SharedInfo::bMachineStopFlag == TRUE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(_eAOI_FLOW_IDLE); //KJT 20210318

			//Devs::m_BaseMotion.SetDOutputBitValue((enum_Do)_DOUT_AOI_LASER_FOCUS_POWER, FALSE);
			Total_Msg(_T("AOI Laser Focus Power Off"));

			Total_Msg(_T("m_bAOIReqMoveProcessing FALSE"));
			pDlg->m_SocketServer_AOI.SendInspectionStopReq();
			continue; //!!
		}

		if (SharedInfo::bMachineStopFlag == TRUE)
			continue;

		if (pDlg->m_SocketServer_AOI.m_nConnect == FALSE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(_eAOI_FLOW_IDLE); //KJT 20210430

			Total_Msg(_T("AOI Disconnected !!"));
			continue;
		}

		switch (GetCurrentTotalStep())
		{
		case _eAOI_FLOW_IDLE:
		{
			break;
		}
		case _eAOI_FLOW_START:
		{
			m_timeStart = CTime::GetCurrentTime(); //KJT 20210329
			SharedInfo::m_timeUnitTact = m_timeStart;

			SharedInfo::nCurFlowID = eAOI_FLOW;

			if (SharedInfo::LoadGlassMappingData() == FALSE) //KJT 20210328
			{
				SetStep(_eAOI_FLOW_ERROR, _T("_eAOI_FLOW_ERROR"));
				break;
			}
			//if (SharedInfo::LoadSwMappingData() == FALSE) //KJT 20210328
			//{
			//	SetStep(_eAOI_FLOW_ERROR, _T("_eAOI_FLOW_ERROR"));
			//	break;
			//}

			Total_Msg(_T("m_bAOIReqMoveProcessing TRUE"));
			SharedInfo::m_eAoiMachineStatus = CAOIProtocolDefine::AOI_MACHINE_STATUS_READY; //!!
			Total_Msg(_T("Set AOI_MACHINE_STATUS_READY"));

			m_dStartPosX = 0.0;
			m_dStartPosY = 0.0;
			m_dEndPosX = 0.0;
			m_dEndPosY = 0.0;

			m_nRetry = 0;

			SharedInfo::m_AOIDefectTotalCount = 0;

			SharedInfo::m_eAoiVelLevel = (enum_AOI_Vel_Level)CModelData::m_InspectionPara.Info.nAOIScanSpeedLevel; //KJT 20210315

			SharedInfo::LightAllOff();

			//Devs::m_BaseMotion.SetDOutputBitValue((enum_Do)_DOUT_AOI_LASER_FOCUS_POWER, TRUE);
			Total_Msg(_T("AOI Laser Focus Power On"));

			memset(&SharedInfo::m_AOIDefectInfo, 0, sizeof(SharedInfo::m_AOIDefectInfo));

#if 0
			SharedInfo::DeleteDirectoryFile(SharedInfo::STR_AOI_DEFECT_INFO_FILE_PATH);
			Sleep(1000);
			SharedInfo::DeleteDirectoryFile(SharedInfo::STR_AOI_DEFECT_REVIEW_PATH);
			Sleep(1000);
#endif

			SetStep(_eAOI_FLOW_INTERLOCK_CHECK, _T("_eAOI_FLOW_INTERLOCK_CHECK"));
			break;
		}

		case _eAOI_FLOW_INTERLOCK_CHECK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(_eAOI_FLOW_ERROR, _T("_eAOI_FLOW_ERROR"));
			}
			else
			{
				SetStep(_eAOI_FLOW_UNLOADER_READY, _T("_eAOI_FLOW_UNLOADER_READY"));
			}
			break;

#pragma region //Unloader Ready
		case _eAOI_FLOW_UNLOADER_READY:
			Devs::m_Ready_UnloaderFlow.Start();

			SetStep(_eAOI_FLOW_UNLOADER_READY_CHECK, _T("_eAOI_FLOW_UNLOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eAOI_FLOW_UNLOADER_READY_CHECK:
			if (Devs::m_Ready_UnloaderFlow.IsFlowDone())
			{
				SetStep(_eAOI_FLOW_LOADER_READY, _T("_eAOI_FLOW_LOADER_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eAOI_FLOW_UNLOADER_READY_CHECK : Time Out !!!"), eAOI_FLOW + 0);
				SetStep(_eAOI_FLOW_ERROR, _T("_eAOI_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eAOI_FLOW_UNLOADER_READY_CHECK, _T("_eAOI_FLOW_UNLOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Loader Ready
		case _eAOI_FLOW_LOADER_READY:
			Devs::m_Ready_LoaderFlow.Start();

			SetStep(_eAOI_FLOW_LOADER_READY_CHECK, _T("_eAOI_FLOW_LOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eAOI_FLOW_LOADER_READY_CHECK:
			if (Devs::m_Ready_LoaderFlow.IsFlowDone())
			{
				//SetStep(_eAOI_FLOW_BOX_CAMERA_READY, _T("_eAOI_FLOW_BOX_CAMERA_READY"));
				SetStep(_eAOI_FLOW_GANTRY_ZX_READY, _T("_eAOI_FLOW_GANTRY_ZX_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eAOI_FLOW_LOADER_READY_CHECK : Time Out !!!"), eAOI_FLOW + 1);
				SetStep(_eAOI_FLOW_ERROR, _T("_eAOI_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eAOI_FLOW_LOADER_READY_CHECK, _T("_eAOI_FLOW_LOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Box Camera Ready
		//case _eAOI_FLOW_BOX_CAMERA_READY:
		//	Devs::m_BoxMotion.BoxAlignCameraYL_WaitPos();
		//	Sleep(20);
		//	Devs::m_BoxMotion.BoxAlignCameraYR_WaitPos();
		//	Sleep(500); //!!

		//	SetStep(_eAOI_FLOW_BOX_CAMERA_READY_CHECK, _T("_eAOI_FLOW_BOX_CAMERA_READY_CHECK"));
		//	SetTimeOut(TIME_OUT_MOTION);
		//	break;

		//case _eAOI_FLOW_BOX_CAMERA_READY_CHECK:
		//	if (Devs::m_BoxMotion.Is_BoxAlignCameraYL_WaitPos() == TRUE && Devs::m_BoxMotion.Is_BoxAlignCameraYR_WaitPos() == TRUE)
		//	{
		//		SetStep(_eAOI_FLOW_GANTRY_ZX_READY, _T("_eAOI_FLOW_GANTRY_ZX_READY"));
		//	}
		//	else if (IsTimeOut())
		//	{
		//		SharedInfo::SetAlarm(_T("_eAOI_FLOW_BOX_CAMERA_READY_CHECK : Time Out !!!"), eAOI_FLOW + 2);
		//		SetStep(_eAOI_FLOW_ERROR, _T("_eAOI_FLOW_ERROR"));
		//	}
		//	else
		//	{
		//		SetCheckStep(_eAOI_FLOW_BOX_CAMERA_READY_CHECK, _T("_eAOI_FLOW_BOX_CAMERA_READY_CHECK"));
		//	}
		//	break;
#pragma endregion

#pragma region //Gantry Z,X Ready
		case _eAOI_FLOW_GANTRY_ZX_READY:
			Devs::m_Ready_GantryZX_Flow.Start();

			SetStep(_eAOI_FLOW_GANTRY_ZX_READY_CHECK, _T("_eAOI_FLOW_GANTRY_ZX_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eAOI_FLOW_GANTRY_ZX_READY_CHECK:
			if (Devs::m_Ready_GantryZX_Flow.IsFlowDone())
			{
				SetStep(_eAOI_FLOW_INSPECTION_READY_REQ, _T("_eAOI_FLOW_INSPECTION_READY_REQ"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eAOI_FLOW_GANTRY_ZX_READY_CHECK : Time Out !!!"), eAOI_FLOW + 2);
				SetStep(_eAOI_FLOW_ERROR, _T("_eAOI_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eAOI_FLOW_GANTRY_ZX_READY_CHECK, _T("_eAOI_FLOW_GANTRY_ZX_READY_CHECK"));
			}
			break;
#pragma endregion

		case _eAOI_FLOW_INSPECTION_READY_REQ:
			SharedInfo::m_bAOIInspectionReady = FALSE; //!!
			if (m_nRetry == 0)
				SharedInfo::m_eAOIInspectionType = CAOIProtocolDefine::AOI_INSPECTION_TYPE_SLOT;
			else
				SharedInfo::m_eAOIInspectionType = CAOIProtocolDefine::AOI_INSPECTION_TYPE_PARTICLE;

			pDlg->m_SocketServer_AOI.SendInspectionReadyReq();

			Sleep(500); //!!
			SetStep(_eAOI_FLOW_INSPECTION_READY_CHECK, _T("_eAOI_FLOW_INSPECTION_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eAOI_FLOW_INSPECTION_READY_CHECK:
			if (SharedInfo::m_bAOIInspectionReady)
			{
				SetStep(_eAOI_FLOW_SET_SURFACE_INFO_REQ, _T("_eAOI_FLOW_SET_SURFACE_INFO_REQ"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eAOI_FLOW_INSPECTION_READY_CHECK : Time Out !!!"), eAOI_FLOW + 3);
				SetStep(_eAOI_FLOW_ERROR, _T("_eAOI_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eAOI_FLOW_INSPECTION_READY_CHECK, _T("_eAOI_FLOW_INSPECTION_READY_CHECK"));
			}
			break;

		case _eAOI_FLOW_SET_SURFACE_INFO_REQ:
			SharedInfo::m_bAOISetSurfaceInfoOk = FALSE; //!!
			pDlg->m_SocketServer_AOI.SendSurfaceInfoReq(0, 0);

			Sleep(1000); //!!
			SetStep(_eAOI_FLOW_SET_SURFACE_INFO_CHECK, _T("_eAOI_FLOW_SET_SURFACE_INFO_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eAOI_FLOW_SET_SURFACE_INFO_CHECK:
			if (SharedInfo::m_bAOISetSurfaceInfoOk)
			{
				SetStep(_eAOI_FLOW_INSPECTION_START_END_POS_INFO_REQ, _T("_eAOI_FLOW_INSPECTION_START_END_POS_INFO_REQ"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eAOI_FLOW_SET_SURFACE_INFO_CHECK : Time Out !!!"), eAOI_FLOW + 4);
				SetStep(_eAOI_FLOW_ERROR, _T("_eAOI_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eAOI_FLOW_SET_SURFACE_INFO_CHECK, _T("_eAOI_FLOW_SET_SURFACE_INFO_CHECK"));
			}
			break;

		case _eAOI_FLOW_INSPECTION_START_END_POS_INFO_REQ:
			SharedInfo::m_bRecvInspectionStartEndPos = FALSE; //!!
			SharedInfo::m_bRecvInspectionStartEndPosError = FALSE;
			pDlg->m_SocketServer_AOI.SendInspectionStartEndPosInfoReq();

			Sleep(1000); //!!
			SetStep(_eAOI_FLOW_INSPECTION_START_END_POS_INFO_CHECK, _T("_eAOI_FLOW_INSPECTION_START_END_POS_INFO_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eAOI_FLOW_INSPECTION_START_END_POS_INFO_CHECK:
			if (SharedInfo::m_bRecvInspectionStartEndPos)
			{
				m_dStartPosX = SharedInfo::m_dInspectionStartPos[0];
				m_dStartPosX -= CSystemData::m_Coordinate.Info.dOffsetReview10xToAoi_X;
				m_dStartPosY = SharedInfo::m_dInspectionStartPos[1];
				m_dStartPosY -= CSystemData::m_Coordinate.Info.dOffsetReview10xToAoi_Y;
				m_dEndPosX = SharedInfo::m_dInspectionEndPos[0];
				m_dEndPosX -= CSystemData::m_Coordinate.Info.dOffsetReview10xToAoi_X;
				m_dEndPosY = SharedInfo::m_dInspectionEndPos[1];
				m_dEndPosY -= CSystemData::m_Coordinate.Info.dOffsetReview10xToAoi_Y;

				m_dTargetPosX = dPosX = m_dStartPosX;
				m_dTargetPosY = dPosY = m_dStartPosY;

				SharedInfo::GetMappingPos(CModelData::m_InspectionPara.Info.bSWAlignFlowUse, CModelData::m_InspectionPara.Info.bMappingDataUse, &m_dTargetPosX, &m_dTargetPosY); //KJT 20210312

				m_nScanLineIndex = SharedInfo::m_nAOIScanLineIndex;
				m_nMaxScanLineCount = SharedInfo::m_nAOIMaxScanLineCount;

				Str.Format(_T("AOI Scan %d/%d"), m_nScanLineIndex + 1, m_nMaxScanLineCount);
				Total_Msg(Str);

				SetStep(_eAOI_FLOW_GANTRY_XY_MOVE_TO_INSP_START_POS, _T("_eAOI_FLOW_GANTRY_XY_MOVE_TO_INSP_START_POS"));
			}
			else if (SharedInfo::m_bRecvInspectionStartEndPosError)
			{
				SharedInfo::SetAlarm(_T("_eAOI_FLOW_INSPECTION_START_END_POS : Pos Error !!!"), eAOI_FLOW + 6);
				SetStep(_eAOI_FLOW_ERROR, _T("_eAOI_FLOW_ERROR"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eAOI_FLOW_INSPECTION_START_END_POS_INFO_CHECK : Time Out !!!"), eAOI_FLOW + 7);
				SetStep(_eAOI_FLOW_ERROR, _T("_eAOI_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eAOI_FLOW_INSPECTION_START_END_POS_INFO_CHECK, _T("_eAOI_FLOW_INSPECTION_START_END_POS_INFO_CHECK"));
			}
			break;

		case _eAOI_FLOW_GANTRY_XY_MOVE_TO_INSP_START_POS: //KJT 2021039
			if (SharedInfo::m_eAOIInspectionType == CAOIProtocolDefine::AOI_INSPECTION_TYPE_SLOT)
				Devs::m_GantryMotion.Move_Gantry_X_Pos(m_dTargetPosX, TRUE, CSystemData::m_Coordinate.Info.dOffsetReview10xToAoi_X, SharedInfo::m_nAOICamDir);
			else
				Devs::m_GantryMotion.Move_Gantry_X_Pos(m_dTargetPosX, FALSE, CSystemData::m_Coordinate.Info.dOffsetReview10xToAoi_X, SharedInfo::m_nAOICamDir);

			Sleep(20); //!!
			Devs::m_GantryMotion.Move_Gantry_Y_Pos(m_dTargetPosY);
			Sleep(20); //!!

			SetStep(_eAOI_FLOW_GANTRY_XY_MOVE_TO_INSP_START_POS_CHECK, _T("_eAOI_FLOW_GANTRY_XY_MOVE_TO_INSP_START_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eAOI_FLOW_GANTRY_XY_MOVE_TO_INSP_START_POS_CHECK: //KJT 20210309
			if (SharedInfo::m_eAOIInspectionType == CAOIProtocolDefine::AOI_INSPECTION_TYPE_SLOT &&
				Devs::m_GantryMotion.Is_Gantry_X_Pos(m_dTargetPosX) && Devs::m_GantryMotion.Is_Gantry_Y_Pos(m_dTargetPosY) &&
				Devs::m_InspectionStageMotion.Is_BackLight_X_Pos(m_dTargetPosX + CSystemData::m_Coordinate.Info.dOffsetReview10xToAoi_X))
			{
				SetStep(_eAOI_FLOW_GANTRY_Z1_INSP_POS, _T("_eAOI_FLOW_GANTRY_Z1_INSP_POS"));
			}
			else if (SharedInfo::m_eAOIInspectionType == CAOIProtocolDefine::AOI_INSPECTION_TYPE_PARTICLE &&
				Devs::m_GantryMotion.Is_Gantry_X_Pos(m_dTargetPosX) && Devs::m_GantryMotion.Is_Gantry_Y_Pos(m_dTargetPosY))
			{
				SetStep(_eAOI_FLOW_GANTRY_Z1_INSP_POS, _T("_eAOI_FLOW_GANTRY_Z1_INSP_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eAOI_FLOW_GANTRY_XY_MOVE_TO_INSP_START_POS_CHECK : Time Out !!!"), eAOI_FLOW + 8);
				SetStep(_eAOI_FLOW_ERROR, _T("_eAOI_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eAOI_FLOW_GANTRY_XY_MOVE_TO_INSP_START_POS_CHECK, _T("_eAOI_FLOW_GANTRY_XY_MOVE_TO_INSP_START_POS_CHECK"));
			}
			break;

		case _eAOI_FLOW_GANTRY_Z1_INSP_POS:
			if (CSystemData::m_Option.Info.m_bAOIMappingGlassMode == FALSE)
				Devs::m_GantryMotion.Move_GantryZ1_InspectionAOI_Pos();
			else
				Devs::m_GantryMotion.Move_GantryZ1_InspectionMappingGlassPos();

			Sleep(20); //!!

			SetStep(_eAOI_FLOW_GANTRY_Z1_INSP_POS_CHECK, _T("_eAOI_FLOW_GANTRY_Z1_INSP_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eAOI_FLOW_GANTRY_Z1_INSP_POS_CHECK:
			if ((CSystemData::m_Option.Info.m_bAOIMappingGlassMode == FALSE && Devs::m_GantryMotion.Is_GantryZ1_InspectionAOI_Pos())
				||
				(CSystemData::m_Option.Info.m_bAOIMappingGlassMode == TRUE && Devs::m_GantryMotion.Is_GantryZ1_InspectionMappingGlassPos()))
			{
				SetStep(_eAOI_FLOW_INSPECTION_START_REQ, _T("_eAOI_FLOW_INSPECTION_START_REQ"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eAOI_FLOW_GANTRY_Z2_INSP_POS_CHECK : Time Out !!!"), eAOI_FLOW + 9);
				SetStep(_eAOI_FLOW_ERROR, _T("_eAOI_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eAOI_FLOW_GANTRY_Z1_INSP_POS_CHECK, _T("_eAOI_FLOW_GANTRY_Z1_INSP_POS_CHECK"));
			}
			break;

		case _eAOI_FLOW_INSPECTION_START_REQ:
			SharedInfo::m_bRecvInspectionStartOk = FALSE; //!!
			pDlg->m_SocketServer_AOI.SendInspectionStartReq();

			Sleep(1000); //!!
			SetStep(_eAOI_FLOW_INSPECTION_START_CHECK, _T("_eAOI_FLOW_INSPECTION_START_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eAOI_FLOW_INSPECTION_START_CHECK:
			if (SharedInfo::m_bRecvInspectionStartOk)
			{
				SetStep(_eAOI_FLOW_GANTRY_X_MOVE_TO_INSP_END_POS, _T("_eAOI_FLOW_GANTRY_X_MOVE_TO_INSP_END_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eAOI_FLOW_INSPECTION_START_CHECK : Time Out !!!"), eAOI_FLOW + 10);
				SetStep(_eAOI_FLOW_ERROR, _T("_eAOI_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eAOI_FLOW_INSPECTION_START_CHECK, _T("_eAOI_FLOW_INSPECTION_START_CHECK"));
			}
			break;

		case _eAOI_FLOW_GANTRY_X_MOVE_TO_INSP_END_POS:
			SharedInfo::m_bRecvAOIDefectInfo = FALSE; //!!
			if (SharedInfo::m_eAoiVelLevel < 0)
				SharedInfo::m_eAoiVelLevel = eAOI_Vel_50;
			else if (SharedInfo::m_eAoiVelLevel >= eAOI_Vel_Max)
				SharedInfo::m_eAoiVelLevel = eAOI_Vel_50;

			m_dTargetPosX = dPosX = m_dEndPosX;
			m_dTargetPosY = dPosY = m_dEndPosY;

			SharedInfo::GetMappingPos(TRUE, CModelData::m_InspectionPara.Info.bMappingDataUse, &m_dTargetPosX, &m_dTargetPosY); //KJT 20210312

			if (SharedInfo::m_eAOIInspectionType == CAOIProtocolDefine::AOI_INSPECTION_TYPE_SLOT)
				Devs::m_GantryMotion.Move_Gantry_X_Pos(m_dTargetPosX, TRUE, CSystemData::m_Coordinate.Info.dOffsetReview10xToAoi_X, SharedInfo::m_nAOICamDir, SharedInfo::m_eAoiVelLevel);
			else
				Devs::m_GantryMotion.Move_Gantry_X_Pos(m_dTargetPosX, FALSE, CSystemData::m_Coordinate.Info.dOffsetReview10xToAoi_X, SharedInfo::m_nAOICamDir, SharedInfo::m_eAoiVelLevel);

			Sleep(20); //!!

			SetStep(_eAOI_FLOW_GANTRY_X_MOVE_TO_INSP_END_POS_CHECK, _T("_eAOI_FLOW_GANTRY_X_MOVE_TO_INSP_END_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eAOI_FLOW_GANTRY_X_MOVE_TO_INSP_END_POS_CHECK: //KJT 20210309
			if (SharedInfo::m_eAOIInspectionType == CAOIProtocolDefine::AOI_INSPECTION_TYPE_SLOT &&
				Devs::m_GantryMotion.Is_Gantry_X_Pos(m_dTargetPosX) && Devs::m_InspectionStageMotion.Is_BackLight_X_Pos(m_dTargetPosX + CSystemData::m_Coordinate.Info.dOffsetReview10xToAoi_X))
			{
				pDlg->m_SocketServer_AOI.SendMoveDoneReq(AXIS_GANTRY_X, m_dTargetPosX + CSystemData::m_Coordinate.Info.dOffsetReview10xToAoi_X); //!!

				SetStep(_eAOI_FLOW_RECV_AOI_DEFECT_INFO_CHECK, _T("_eAOI_FLOW_RECV_AOI_DEFECT_INFO_CHECK"));
				SetTimeOut(TIME_OUT_MOTION);
			}
			else if (SharedInfo::m_eAOIInspectionType == CAOIProtocolDefine::AOI_INSPECTION_TYPE_PARTICLE &&
				Devs::m_GantryMotion.Is_Gantry_X_Pos(m_dTargetPosX))
			{
				pDlg->m_SocketServer_AOI.SendMoveDoneReq(AXIS_GANTRY_X, m_dTargetPosX + CSystemData::m_Coordinate.Info.dOffsetReview10xToAoi_X); //!!

				SetStep(_eAOI_FLOW_RECV_AOI_DEFECT_INFO_CHECK, _T("_eAOI_FLOW_RECV_AOI_DEFECT_INFO_CHECK"));
				SetTimeOut(TIME_OUT_MOTION);
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eAOI_FLOW_GANTRY_X_MOVE_TO_INSP_END_POS_CHECK : Time Out !!!"), eAOI_FLOW + 11);
				SetStep(_eAOI_FLOW_ERROR, _T("_eAOI_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eAOI_FLOW_GANTRY_X_MOVE_TO_INSP_END_POS_CHECK, _T("_eAOI_FLOW_GANTRY_X_MOVE_TO_INSP_END_POS_CHECK"));
			}
			break;

		case _eAOI_FLOW_RECV_AOI_DEFECT_INFO_CHECK:
			if (SharedInfo::m_bRecvAOIDefectInfo)
			{
				if (SharedInfo::m_bExistAOIDefect)
				{
					pDlg->m_SocketServer_AOI.ReadDefectInfoFile(m_nScanLineIndex);

					pDlg->m_SocketServer_AOI.SaveDefectInfo(m_nScanLineIndex); //KJT 20210309
				}

				if (m_nScanLineIndex < m_nMaxScanLineCount - 1)
				{
					SetStep(_eAOI_FLOW_INSPECTION_START_END_POS_INFO_REQ, _T("_eAOI_FLOW_INSPECTION_START_END_POS_INFO_REQ"));
				}
				else
				{
					if (CSystemData::m_Option.Info.m_bAOIAgingMode == TRUE)
					{
						SetStep(_eAOI_FLOW_INSPECTION_READY_REQ, _T("_eAOI_FLOW_INSPECTION_READY_REQ"));
					}
					else
					{
						SharedInfo::LightAllOff();

						m_nRetry++;
						if (m_nRetry > 1)
						{
							SharedInfo::m_eAoiMachineStatus = CAOIProtocolDefine::AOI_MACHINE_STATUS_NOT_READY; //!!
							Total_Msg(_T("Set AOI_MACHINE_STATUS_NOT_READY"));	

							SetStep(_eAOI_FLOW_FINISH_GANTRY_Z1_WAIT_POS, _T("_eAOI_FLOW_FINISH_GANTRY_Z1_WAIT_POS"));
						}
						else
						{
							SetStep(_eAOI_FLOW_INSPECTION_READY_REQ, _T("_eAOI_FLOW_INSPECTION_READY_REQ"));
						}
					}
				}
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eAOI_FLOW_RECV_AOI_DEFECT_INFO_CHECK : Time Out !!!"), eAOI_FLOW + 12);
				SetStep(_eAOI_FLOW_ERROR, _T("_eAOI_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eAOI_FLOW_RECV_AOI_DEFECT_INFO_CHECK, _T("_eAOI_FLOW_RECV_AOI_DEFECT_INFO_CHECK"));
			}
			break;

		case _eAOI_FLOW_FINISH_GANTRY_Z1_WAIT_POS:
			Devs::m_GantryMotion.Move_GantryZ1_Wait_Pos();
			Sleep(20); //!!

			SetStep(_eAOI_FLOW_FINISH_GANTRY_Z1_WAIT_POS_CHECK, _T("_eAOI_FLOW_FINISH_GANTRY_Z2_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eAOI_FLOW_FINISH_GANTRY_Z1_WAIT_POS_CHECK:
			if (Devs::m_GantryMotion.Is_GantryZ1_Wait_Pos())
			{
				SetStep(_eAOI_FLOW_FINISH_GANTRY_XY_WAIT_POS, _T("_eAOI_FLOW_FINISH_GANTRY_XY_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eAOI_FLOW_FINISH_GANTRY_Z2_WAIT_POS_CHECK : Time Out !!!"), eAOI_FLOW + 13);
				SetStep(_eAOI_FLOW_ERROR, _T("_eAOI_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eAOI_FLOW_FINISH_GANTRY_Z1_WAIT_POS_CHECK, _T("_eAOI_FLOW_FINISH_GANTRY_Z1_WAIT_POS_CHECK"));
			}
			break;

		case _eAOI_FLOW_FINISH_GANTRY_XY_WAIT_POS:
			Devs::m_GantryMotion.Move_Gantry_X_Wait_Pos();
			Sleep(20); //!!
			Devs::m_GantryMotion.Move_Gantry_Y_Wait_Pos();
			Sleep(20);
			Devs::m_InspectionStageMotion.BackLightX_WaitPos();
			Sleep(20);

			SetStep(_eAOI_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK, _T("_eAOI_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eAOI_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Wait_Pos() && Devs::m_GantryMotion.Is_Gantry_Y_Wait_Pos() && Devs::m_InspectionStageMotion.Is_BackLightX_WaitPos())
			{
				SetStep(_eAOI_FLOW_DONE, _T("_eAOI_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eAOI_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK : Time Out !!!"), eAOI_FLOW + 14);
				SetStep(_eAOI_FLOW_ERROR, _T("_eAOI_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eAOI_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK, _T("_eAOI_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK"));
			}
			break;

		case _eAOI_FLOW_ERROR:
			//Devs::m_BaseMotion.SetDOutputBitValue((enum_Do)_DOUT_AOI_LASER_FOCUS_POWER, FALSE);
			Total_Msg(_T("AOI Laser Focus Power Off"));

			SharedInfo::m_eAoiMachineStatus = CAOIProtocolDefine::AOI_MACHINE_STATUS_NOT_READY; //!!
			Total_Msg(_T("Set AOI_MACHINE_STATUS_NOT_READY"));
			break;

		case _eAOI_FLOW_DONE:
		{
			//Devs::m_BaseMotion.SetDOutputBitValue((enum_Do)_DOUT_AOI_LASER_FOCUS_POWER, FALSE);
			Total_Msg(_T("AOI Laser Focus Power Off"));

			SharedInfo::m_eAoiMachineStatus = CAOIProtocolDefine::AOI_MACHINE_STATUS_NOT_READY; //!!
			Total_Msg(_T("Set AOI_MACHINE_STATUS_NOT_READY"));
			
			pDlg->m_SocketServer_AOI.Req_GantryXYZMoveDone(CManualData::m_ManualDataGantry.Info.m_dGantry_X_Wait_Pos,
				CManualData::m_ManualDataGantry.Info.m_dGantry_Y_Wait_Pos, CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Wait_Pos);

			SharedInfo::nPrevFlowID = eAOI_FLOW; //KJT 20210326

			m_bFlowDone = TRUE;

			SharedInfo::CalTactTime(_T("AOI_FLOW"), m_timeStart); //KJT 20210329

			SetStep(_eAOI_FLOW_IDLE, _T("_eAOI_FLOW_IDLE"));
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

BOOL CAOIFlow::FlowInterlock()
{
	/////////////////////////////////////////////////////////////////////////////
	if (Devs::m_LoaderMotion.CheckLoaderFlowInterlock(_T("AOIFlow"), eAOI_FLOW, 30) == FALSE)
	{
		return FALSE;
	}

	/////////////////////////////////////////////////////////////////////////////
	if (Devs::m_UnloaderMotion.CheckUnloaderFlowInterlock(_T("AOIFlow"), eAOI_FLOW, 40) == FALSE)
	{
		return FALSE;
	}

	/////////////////////////////////////////////////////////////////////////////
	if (Devs::m_GantryMotion.CheckGantryXYZFlowInterlock(_T("AOIFlow"), eAOI_FLOW, 50) == FALSE)
	{
		return FALSE;
	}

	return TRUE;
}