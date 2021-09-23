#include "stdafx.h"
#include "Inspection3DFlow.h"
#include "Log/Logger.h"
#include "Vision/Devs.h"
#include "Data/ModelData.h"
#include "Data/ManualData.h"
#include "CamAreaModul.h"
#include "Data/SystemData.h"
#include "VisionAgent.h"
#include "VisionAgentDlg.h"
#include "FmmLight1.h"
#include "H8Dlg.h"

CInspection3DFlow::CInspection3DFlow()
{
	for (int i = 0; i < MAX_3D_HOLE_COUNT; i++)
	{
		m_dMeasurePosXY[i][0] = 0.0;
		m_dMeasurePosXY[i][1] = 0.0;

		m_dGradientResult[i][0] = 0.0;
		m_dGradientResult[i][1] = 0.0;
		m_dGradientResult[i][2] = 0.0;
		m_dGradientResult[i][3] = 0.0;

		m_nSlotCenterPos[i][0] = 0;
		m_nSlotCenterPos[i][1] = 0;
		m_nSlotStartPos[i][0] = 0;
		m_nSlotStartPos[i][1] = 0;
		m_nSlotSize[i][0] = 0;
		m_nSlotSize[i][1] = 0;
	}

	m_nMaxPosCount = 0;
}


CInspection3DFlow::~CInspection3DFlow()
{
}

BOOL CInspection3DFlow::InitProcess()
{
	m_StateComplete = NULL;
	m_FlowFinish = TRUE;
	m_bTerminate = FALSE;
	m_bFlowDone = TRUE;

#pragma region //Step Group
	int nGroupIndex = 0;

	m_sGroupInfo[nGroupIndex].m_bProcessingFlag = FALSE;
	m_sGroupInfo[nGroupIndex].nStartStep = _eINSPECT_3D_FLOW_START;
	m_sGroupInfo[nGroupIndex].nEndStep = _eINSPECT_3D_FLOW_INTERLOCK_CHECK;
	m_sGroupInfo[nGroupIndex].strGroupName.Format(_T("%d. Start"), nGroupIndex + 1);
	nGroupIndex++;

	m_sGroupInfo[nGroupIndex].m_bProcessingFlag = FALSE;
	m_sGroupInfo[nGroupIndex].nStartStep = _eINSPECT_3D_FLOW_UNLOADER_READY;
	m_sGroupInfo[nGroupIndex].nEndStep = _eINSPECT_3D_FLOW_GANTRY_ZX_READY_CHECK;
	m_sGroupInfo[nGroupIndex].strGroupName.Format(_T("%d. Other Axis Ready"), nGroupIndex + 1);
	nGroupIndex++;

	m_sGroupInfo[nGroupIndex].m_bProcessingFlag = FALSE;
	m_sGroupInfo[nGroupIndex].nStartStep = _eINSPECT_3D_FLOW_ACQUISITION_START;
	m_sGroupInfo[nGroupIndex].nEndStep = _eINSPECT_3D_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK;
	m_sGroupInfo[nGroupIndex].strGroupName.Format(_T("%d. Measure 3D"), nGroupIndex + 1);
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

BOOL CInspection3DFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eINSPECT_3D_FLOW_IDLE);

#if 0
	do
	{
		Sleep(10);
	} while (IsTerminate() == 0);
#endif

	if (hHandle != NULL)
	{
		CloseHandle(hHandle);
	}

	return TRUE;
}

BOOL CInspection3DFlow::Start(enum_3D_Type n3DType, int nStep)
{
	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	m_nKindOf3D = n3DType;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(nStep, _T("_eINSPECT_3D_FLOW_START"));
	return TRUE;
}
BOOL CInspection3DFlow::Stop()
{
	m_bStopBit = TRUE;
	return TRUE;
}

UINT CInspection3DFlow::ThreadFunction(LPVOID lpParam)
{
	CInspection3DFlow* pFlow = NULL;

	pFlow = (CInspection3DFlow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}

VOID CInspection3DFlow::ThreadFunctionEntry(VOID)
{
/*
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

	SYSTEMTIME st;

	while (m_FlowFinish)
	{
		WaitForSingleObject(hHandle, INFINITE);
		ResetEvent(hHandle);

		if (SharedInfo::bMachineStopFlag == TRUE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(_eINSPECT_3D_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}

		switch (GetCurrentTotalStep())
		{
		case _eINSPECT_3D_FLOW_IDLE:
		{
			break;
		}
		case _eINSPECT_3D_FLOW_START:
		{
			m_timeStart = CTime::GetCurrentTime(); //KJT 20210329
			SharedInfo::m_timeUnitTact = m_timeStart;

			SharedInfo::nCurFlowID = e3D_FLOW;

			GetLocalTime(&st);
			m_strPath.Format(_T("%s\\Result\\3D\\3D_Gradient\\SlotGradient_%s_%04d%02d%02d%02d%02d%02d.csv"), SharedInfo::VisionAgentPath, SharedInfo::Active.tchStickId, st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

			SharedInfo::LightAllOff();

			m_nRepeatCount = 0;
			m_nMaxRepeatCount = 0;
			m_nCurPosCount = 0;

			pDlg->m_pH8Dlg->m_b3D_TriggerContinuous = FALSE;

			if (CModelData::m_InspectionPara.Info.bMappingDataUse)
			{
				if (SharedInfo::LoadGlassMappingData() == FALSE) //KJT 20210328
				{
					SharedInfo::SetAlarm(_T("_eINSPECT_3D_FLOW_START : Mapping Data !!!"), e3D_FLOW + 0);
					SetStep(_eINSPECT_3D_FLOW_ERROR, _T("_eINSPECT_3D_FLOW_ERROR"));
					break;
				}
			}			

			if (m_nKindOf3D == eNORAML_3D)
			{
				m_nMaxRepeatCount = CModelData::m_MaterialPara.Info.n3DHoleRepeatCount;
				m_nMaxPosCount = CModelData::m_AtMaterialPara.Info.n3DHoleCount;

				for (int i = 0; i < MAX_3D_HOLE_COUNT; i++)
				{
					if (i >= m_nMaxPosCount) break;

					m_dMeasurePosXY[i][0] = CModelData::m_MaterialPara.Info.d3DHolePosX[i] * STICK_FLIP_XY;
					m_dMeasurePosXY[i][1] = CModelData::m_MaterialPara.Info.d3DHolePosY[i] * STICK_FLIP_XY;
				}
			}
			else
			{
				m_nMaxRepeatCount = CModelData::m_AtMaterialPara.Info.n3DHoleRepeatCount;
				m_nMaxPosCount = CModelData::m_AtMaterialPara.Info.n3DHoleCount;

				for (int i = 0; i < MAX_3D_HOLE_COUNT; i++)
				{
					if (i >= m_nMaxPosCount) break;

					m_dMeasurePosXY[i][0] = CModelData::m_AtMaterialPara.Info.d3DHolePosX[i] * STICK_FLIP_XY;
					m_dMeasurePosXY[i][1] = CModelData::m_AtMaterialPara.Info.d3DHolePosY[i] * STICK_FLIP_XY;
				}
			}
			SetStep(_eINSPECT_3D_FLOW_INTERLOCK_CHECK, _T("_eINSPECT_3D_FLOW_INTERLOCK_CHECK"));
			break;
		}

		case _eINSPECT_3D_FLOW_INTERLOCK_CHECK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(_eINSPECT_3D_FLOW_ERROR, _T("_eINSPECT_3D_FLOW_ERROR"));
			}
			else
			{
				SetStep(_eINSPECT_3D_FLOW_UNLOADER_READY, _T("_eINSPECT_3D_FLOW_UNLOADER_READY"));
			}
			break;

#pragma region //Unloader Ready
		case _eINSPECT_3D_FLOW_UNLOADER_READY:
			Devs::m_Ready_UnloaderFlow.Start();

			SetStep(_eINSPECT_3D_FLOW_UNLOADER_READY_CHECK, _T("_eINSPECT_3D_FLOW_UNLOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eINSPECT_3D_FLOW_UNLOADER_READY_CHECK:
			if (Devs::m_Ready_UnloaderFlow.IsFlowDone())
			{
				Sleep(100); //!!
				SetStep(_eINSPECT_3D_FLOW_LOADER_READY, _T("_eINSPECT_3D_FLOW_LOADER_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eINSPECT_3D_FLOW_UNLOADER_READY_CHECK : Time Out !!!"), e3D_FLOW + 1);
				SetStep(_eINSPECT_3D_FLOW_ERROR, _T("_eINSPECT_3D_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eINSPECT_3D_FLOW_UNLOADER_READY_CHECK, _T("_eINSPECT_3D_FLOW_UNLOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Loader Ready
		case _eINSPECT_3D_FLOW_LOADER_READY:
			Devs::m_Ready_LoaderFlow.Start();

			SetStep(_eINSPECT_3D_FLOW_LOADER_READY_CHECK, _T("_eINSPECT_3D_FLOW_LOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eINSPECT_3D_FLOW_LOADER_READY_CHECK:
			if (Devs::m_Ready_LoaderFlow.IsFlowDone())
			{
				Sleep(100); //!!
				//SetStep(_eINSPECT_3D_FLOW_BOX_CAMERA_READY, _T("_eINSPECT_3D_FLOW_BOX_CAMERA_READY"));
				SetStep(_eINSPECT_3D_FLOW_GANTRY_ZX_READY, _T("_eINSPECT_3D_FLOW_GANTRY_ZX_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eINSPECT_3D_FLOW_LOADER_READY_CHECK : Time Out !!!"), e3D_FLOW + 2);
				SetStep(_eINSPECT_3D_FLOW_ERROR, _T("_eINSPECT_3D_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eINSPECT_3D_FLOW_LOADER_READY_CHECK, _T("_eINSPECT_3D_FLOW_LOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Box Camera Ready
		case _eINSPECT_3D_FLOW_BOX_CAMERA_READY:
			Devs::m_BoxMotion.BoxAlignCameraYL_WaitPos();
			Sleep(20);
			Devs::m_BoxMotion.BoxAlignCameraYR_WaitPos();
			Sleep(20); //!!

			SetStep(_eINSPECT_3D_FLOW_BOX_CAMERA_READY_CHECK, _T("_eINSPECT_3D_FLOW_BOX_CAMERA_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eINSPECT_3D_FLOW_BOX_CAMERA_READY_CHECK:
			if (Devs::m_BoxMotion.Is_BoxAlignCameraYL_WaitPos() == TRUE && Devs::m_BoxMotion.Is_BoxAlignCameraYR_WaitPos() == TRUE)
			{
				SetStep(_eINSPECT_3D_FLOW_GANTRY_ZX_READY, _T("_eINSPECT_3D_FLOW_GANTRY_ZX_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eINSPECT_3D_FLOW_BOX_CAMERA_READY_CHECK : Time Out !!!"), e3D_FLOW + 3);
				SetStep(_eINSPECT_3D_FLOW_ERROR, _T("_eINSPECT_3D_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eINSPECT_3D_FLOW_BOX_CAMERA_READY_CHECK, _T("_eINSPECT_3D_FLOW_BOX_CAMERA_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Gantry Z,X Ready
		case _eINSPECT_3D_FLOW_GANTRY_ZX_READY:
			Devs::m_Ready_GantryZX_Flow.Start();

			SetStep(_eINSPECT_3D_FLOW_GANTRY_ZX_READY_CHECK, _T("_eINSPECT_3D_FLOW_GANTRY_ZX_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eINSPECT_3D_FLOW_GANTRY_ZX_READY_CHECK:
			if (Devs::m_Ready_GantryZX_Flow.IsFlowDone())
			{
				Sleep(100); //!!
				SetStep(_eINSPECT_3D_FLOW_ACQUISITION_START, _T("_eINSPECT_3D_FLOW_ACQUISITION_START"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eINSPECT_3D_FLOW_GANTRY_ZX_READY_CHECK : Time Out !!!"), e3D_FLOW + 4);
				SetStep(_eINSPECT_3D_FLOW_ERROR, _T("_eINSPECT_3D_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eINSPECT_3D_FLOW_GANTRY_ZX_READY_CHECK, _T("_eINSPECT_3D_FLOW_GANTRY_ZX_READY_CHECK"));
			}
			break;
#pragma endregion

		//SW Align is not need
		//case _eINSPECT_3D_FLOW_SW_ALIGN_START:
		//	Devs::m_SwAlignFlow.m_eSwAlignType = eSwAlign_EdgeSlot; //KJT 20210419
		//	Devs::m_SwAlignFlow.Start(Devs::m_SwAlignFlow._eSW_ALIGN_FLOW_START);

		//	SetStep(_eINSPECT_3D_FLOW_SW_ALIGN_DONE_CHECK, _T("_eINSPECT_3D_FLOW_SW_ALIGN_DONE_CHECK"));
		//	SetTimeOut(TIME_OUT_STATE);
		//	break;

		//case _eINSPECT_3D_FLOW_SW_ALIGN_DONE_CHECK:
		//	if (Devs::m_SwAlignFlow.IsFlowDone())
		//	{
		//		SetCheckStep(_eINSPECT_3D_FLOW_ACQUISITION_START, _T("_eINSPECT_3D_FLOW_ACQUISITION_START"));
		//		SetTimeOut(TIME_OUT_MOTION);
		//	}
		//	else if (IsTimeOut())
		//	{
		//		SharedInfo::SetAlarm(_T("_eINSPECT_3D_FLOW_SW_ALIGN_DONE_CHECK : Time Out"), e3D_FLOW + 4);
		//		SetStep(_eINSPECT_3D_FLOW_ERROR, _T("_eINSPECT_3D_FLOW_ERROR"));
		//		break;
		//	}
		//	else
		//	{
		//		SetCheckStep(_eINSPECT_3D_FLOW_SW_ALIGN_DONE_CHECK, _T("_eINSPECT_3D_FLOW_SW_ALIGN_DONE_CHECK"));
		//	}
		//	break;

		case _eINSPECT_3D_FLOW_ACQUISITION_START:
			pDlg->m_pH8Dlg->CHdl_StopAcquisition();
			Sleep(100);

			if (pDlg->m_pH8Dlg->CHdl_StartAcquisition() == TRUE)
			{
				SetStep(_eINSPECT_3D_FLOW_GANTRY_XY_INSPECTION_POS_1ST, _T("_eINSPECT_3D_FLOW_GANTRY_XY_INSPECTION_POS_1ST"));
			}
			else
			{
				SharedInfo::SetAlarm(_T("_eINSPECT_3D_FLOW_ACQUISITION_START : Time Out !!!"), e3D_FLOW + 5);
				SetStep(_eINSPECT_3D_FLOW_ERROR, _T("_eINSPECT_3D_FLOW_ERROR"));
			}
			break;

#pragma region //Gantry XYZ First Pos Move
		case _eINSPECT_3D_FLOW_GANTRY_XY_INSPECTION_POS_1ST:
			m_dTargetPosX = dPosX = GetMeasurementPos(m_nCurPosCount).dPosX;
			m_dTargetPosY = dPosY = GetMeasurementPos(m_nCurPosCount).dPosY;

#ifndef SIM_MODE
			if (CModelData::m_InspectionPara.Info.bMappingDataUse)
			{
				Devs::m_MappingProc.GetGlassMapping_CalibPosXY(eMAPPING_ID_10X, &m_dTargetPosX, &m_dTargetPosY);
				Str.Format(_T("Mapping Data X:%10.5f, Y:%10.5f => X:%10.5f, Y:%10.5f"), dPosX, dPosY, m_dTargetPosX, m_dTargetPosY);
				Total_Msg(Str);
			}
#endif

			Devs::m_GantryMotion.Move_Gantry_X_Pos(m_dTargetPosX, FALSE);
			Sleep(20); //!!
			Devs::m_GantryMotion.Move_Gantry_Y_Pos(m_dTargetPosY);
			Sleep(20); //!!

			SetStep(_eINSPECT_3D_FLOW_GANTRY_XY_INSPECTION_POS_1ST_CHECK, _T("_eINSPECT_3D_FLOW_GANTRY_XY_INSPECTION_POS_1ST_CHECK"));
			break;

		case _eINSPECT_3D_FLOW_GANTRY_XY_INSPECTION_POS_1ST_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Pos(m_dTargetPosX) && Devs::m_GantryMotion.Is_Gantry_Y_Pos(m_dTargetPosY))
			{
				SetStep(_eINSPECT_3D_FLOW_3D_CAM_Z_INSPECTION_POS_1ST, _T("_eINSPECT_3D_FLOW_3D_CAM_Z_INSPECTION_POS_1ST"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eINSPECT_3D_FLOW_GANTRY_XY_INSPECTION_POS_1ST_CHECK : Time Out !!!"), e3D_FLOW + 6);
				SetStep(_eINSPECT_3D_FLOW_ERROR, _T("_eINSPECT_3D_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eINSPECT_3D_FLOW_GANTRY_XY_INSPECTION_POS_1ST_CHECK, _T("_eINSPECT_3D_FLOW_GANTRY_XY_INSPECTION_POS_1ST_CHECK"));
			}
			break;
//
//		case _eINSPECT_3D_FLOW_3D_CAM_Z_INSPECTION_POS_1ST:
//			Devs::m_GantryMotion.Move_GantryZ2_Inspect_3D_Pos();
//
//			SetStep(_eINSPECT_3D_FLOW_3D_CAM_Z_INSPECTION_POS_1ST_CHECK, _T("_eINSPECT_3D_FLOW_3D_CAM_Z_INSPECTION_POS_1ST_CHECK"));
//			SetTimeOut(TIME_OUT_MOTION);
//			break;
//
//		case _eINSPECT_3D_FLOW_3D_CAM_Z_INSPECTION_POS_1ST_CHECK:
//			if (Devs::m_GantryMotion.Is_GantryZ2_Inspect_3D_Pos())
//			{
//				Sleep(500); //!!
//				SetStep(_eINSPECT_3D_FLOW_TRIGGER_SHOT, _T("_eINSPECT_3D_FLOW_TRIGGER_SHOT"));
//			}
//			else if (IsTimeOut())
//			{
//				SharedInfo::SetAlarm(_T("_eINSPECT_3D_FLOW_3D_CAM_Z_INSPECTION_POS_1ST_CHECK : Time Out !!!"), e3D_FLOW + 7);
//				SetStep(_eINSPECT_3D_FLOW_ERROR, _T("_eINSPECT_3D_FLOW_ERROR"));
//			}
//			else
//			{
//				SetCheckStep(_eINSPECT_3D_FLOW_3D_CAM_Z_INSPECTION_POS_1ST_CHECK, _T("_eINSPECT_3D_FLOW_3D_CAM_Z_INSPECTION_POS_1ST_CHECK"));
//			}
//			break;
//#pragma endregion
//
//		case _eINSPECT_3D_FLOW_3D_CAM_Z_INSPECTION_POS_2ND:
//			Devs::m_GantryMotion.Move_GantryZ2_Inspect_3D_Pos();
//
//			SetStep(_eINSPECT_3D_FLOW_3D_CAM_Z_INSPECTION_POS_2ND_CHECK, _T("_eINSPECT_3D_FLOW_3D_CAM_Z_INSPECTION_POS_2ND_CHECK"));
//			SetTimeOut(TIME_OUT_MOTION);
//			break;
//
//		case _eINSPECT_3D_FLOW_3D_CAM_Z_INSPECTION_POS_2ND_CHECK:
//			if (Devs::m_GantryMotion.Is_GantryZ2_Inspect_3D_Pos())
//			{
//				Sleep(100); //!!
//				SetStep(_eINSPECT_3D_FLOW_GANTRY_XY_INSPECTION_POS_2ND, _T("_eINSPECT_3D_FLOW_GANTRY_XY_INSPECTION_POS_2ND"));
//			}
//			else if (IsTimeOut())
//			{
//				SharedInfo::SetAlarm(_T("_eINSPECT_3D_FLOW_3D_CAM_Z_INSPECTION_POS_2ND_CHECK : Time Out !!!"), e3D_FLOW + 8);
//				SetStep(_eINSPECT_3D_FLOW_ERROR, _T("_eINSPECT_3D_FLOW_ERROR"));
//			}
//			else
//			{
//				SetCheckStep(_eINSPECT_3D_FLOW_3D_CAM_Z_INSPECTION_POS_2ND_CHECK, _T("_eINSPECT_3D_FLOW_3D_CAM_Z_INSPECTION_POS_2ND_CHECK"));
//			}
//			break;

		case _eINSPECT_3D_FLOW_GANTRY_XY_INSPECTION_POS_2ND:
			m_dTargetPosX = dPosX = GetMeasurementPos(m_nCurPosCount).dPosX;
			m_dTargetPosY = dPosY = GetMeasurementPos(m_nCurPosCount).dPosY;

#ifndef SIM_MODE
			if (CModelData::m_InspectionPara.Info.bMappingDataUse)
			{
				Devs::m_MappingProc.GetGlassMapping_CalibPosXY(eMAPPING_ID_10X, &m_dTargetPosX, &m_dTargetPosY);
				Str.Format(_T("Mapping Data X:%10.5f, Y:%10.5f => X:%10.5f, Y:%10.5f"), dPosX, dPosY, m_dTargetPosX, m_dTargetPosY);
				Total_Msg(Str);
			}
#endif

			Devs::m_GantryMotion.Move_Gantry_X_Pos(m_dTargetPosX, FALSE);
			Sleep(20); //!!
			Devs::m_GantryMotion.Move_Gantry_Y_Pos(m_dTargetPosY);
			Sleep(20); //!!

			SetStep(_eINSPECT_3D_FLOW_GANTRY_XY_INSPECTION_POS_2ND_CHECK, _T("_eINSPECT_3D_FLOW_GANTRY_XY_INSPECTION_POS_2ND_CHECK"));
			break;

		case _eINSPECT_3D_FLOW_GANTRY_XY_INSPECTION_POS_2ND_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Pos(m_dTargetPosX) && Devs::m_GantryMotion.Is_Gantry_Y_Pos(m_dTargetPosY))
			{
				Sleep(100); //!!
				SetStep(_eINSPECT_3D_FLOW_TRIGGER_SHOT, _T("_eINSPECT_3D_FLOW_TRIGGER_SHOT"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eINSPECT_3D_FLOW_GANTRY_XY_INSPECTION_POS_2ND_CHECK : Time Out !!!"), e3D_FLOW + 9);
				SetStep(_eINSPECT_3D_FLOW_ERROR, _T("_eINSPECT_3D_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eINSPECT_3D_FLOW_GANTRY_XY_INSPECTION_POS_2ND_CHECK, _T("_eINSPECT_3D_FLOW_GANTRY_XY_INSPECTION_POS_2ND_CHECK"));
			}
			break;

		case _eINSPECT_3D_FLOW_TRIGGER_SHOT:
			if (pDlg->m_pH8Dlg->CHdl_TriggerShot(m_nCurPosCount) == TRUE)
			{
				SetStep(_eINSPECT_3D_FLOW_MEASURE_GRADIENT, _T("_eINSPECT_3D_FLOW_MEASURE_GRADIENT"));
			}
			else
			{
				SharedInfo::SetAlarm(_T("_eINSPECT_3D_FLOW_TRIGGER_SHOT : Shot Error"), e3D_FLOW + 10);
				SetStep(_eINSPECT_3D_FLOW_ERROR, _T("_eINSPECT_3D_FLOW_ERROR"));
			}
			break;

		case _eINSPECT_3D_FLOW_MEASURE_GRADIENT:
			if (pDlg->m_pH8Dlg->MeasurementGriadient(eImageType_Gray))
			{			
				m_nSlotCenterPos[m_nCurPosCount][0] = pDlg->m_pH8Dlg->m_nFind_Cx;
				m_nSlotCenterPos[m_nCurPosCount][1] = pDlg->m_pH8Dlg->m_nFind_Cy;

				m_nSlotStartPos[m_nCurPosCount][0] = pDlg->m_pH8Dlg->m_nFind_Sx;
				m_nSlotStartPos[m_nCurPosCount][1] = pDlg->m_pH8Dlg->m_nFind_Sy;

				m_nSlotSize[m_nCurPosCount][0] = pDlg->m_pH8Dlg->m_nFind_W;
				m_nSlotSize[m_nCurPosCount][1] = pDlg->m_pH8Dlg->m_nFind_H;

				m_dGradientResult[m_nCurPosCount][0] = pDlg->m_pH8Dlg->m_dGradient[0];
				m_dGradientResult[m_nCurPosCount][1] = pDlg->m_pH8Dlg->m_dGradient[1];
				m_dGradientResult[m_nCurPosCount][2] = pDlg->m_pH8Dlg->m_dGradient[2];
				m_dGradientResult[m_nCurPosCount][3] = pDlg->m_pH8Dlg->m_dGradient[3];

				m_nCurPosCount++;				
				if (m_nCurPosCount >= CModelData::m_AtMaterialPara.Info.n3DHoleCount)
				{
					if (++m_nRepeatCount >= m_nMaxRepeatCount)
					{
						SaveMeasureSlotGradientResult(m_nRepeatCount);
						
						m_nCurPosCount = 0;
						SetStep(_eINSPECT_3D_FLOW_ACQUISITION_STOP, _T("_eINSPECT_3D_FLOW_ACQUISITION_STOP"));					}
					else
					{
						SaveMeasureSlotGradientResult(m_nRepeatCount);
						
						Sleep(100);
						m_nCurPosCount = 0;
						SetStep(_eINSPECT_3D_FLOW_GANTRY_XY_INSPECTION_POS_2ND, _T("_eINSPECT_3D_FLOW_GANTRY_XY_INSPECTION_POS_2ND"));
					}
				}
				else
				{
					SetStep(_eINSPECT_3D_FLOW_GANTRY_XY_INSPECTION_POS_2ND, _T("_eINSPECT_3D_FLOW_GANTRY_XY_INSPECTION_POS_2ND"));
				}
			}
			else
			{
				SharedInfo::SetAlarm(_T("_eINSPECT_3D_FLOW_MEASURE_GRADIENT : Calculation Error !!!"), e3D_FLOW + 11);
				SetStep(_eINSPECT_3D_FLOW_ERROR, _T("_eINSPECT_3D_FLOW_ERROR"));
			}
			break;

		case _eINSPECT_3D_FLOW_ACQUISITION_STOP:
			if (pDlg->m_pH8Dlg->CHdl_StopAcquisition() == TRUE)
			{
				SetStep(_eINSPECT_3D_FLOW_FINISH_3D_CAM_Z_WAIT_POS, _T("_eINSPECT_3D_FLOW_FINISH_3D_CAM_Z_WAIT_POS"));
			}
			else
			{
				SharedInfo::SetAlarm(_T("_eINSPECT_3D_FLOW_ACQUISITION_STOP : Stop Error !!!"), e3D_FLOW + 12);
				SetStep(_eINSPECT_3D_FLOW_ERROR, _T("_eINSPECT_3D_FLOW_ERROR"));
			}
			break;

		case _eINSPECT_3D_FLOW_FINISH_3D_CAM_Z_WAIT_POS:
			Devs::m_GantryMotion.Move_GantryZ_All_Wait_Pos();

			SetStep(_eINSPECT_3D_FLOW_FINISH_3D_CAM_Z_WAIT_POS_CHECK, _T("_eINSPECT_3D_FLOW_FINISH_3D_CAM_Z_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eINSPECT_3D_FLOW_FINISH_3D_CAM_Z_WAIT_POS_CHECK:
			if (Devs::m_GantryMotion.Is_GantryZ_All_Wait_Pos())
			{
				if (SharedInfo::MachineState.bAutoRunFlag == TRUE && SharedInfo::Active.ProcessEndFlow != eCOMBO_AUTO_RUN_FLOW_3D)
					SetStep(_eINSPECT_3D_FLOW_DONE, _T("_eINSPECT_3D_FLOW_DONE"));
				else 
					SetStep(_eINSPECT_3D_FLOW_FINISH_GANTRY_XY_WAIT_POS, _T("_eINSPECT_3D_FLOW_FINISH_GANTRY_XY_WAIT_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eINSPECT_3D_FLOW_FINISH_3D_CAM_Z_WAIT_POS_CHECK : Time Out !!!"), e3D_FLOW + 13);
				SetStep(_eINSPECT_3D_FLOW_ERROR, _T("_eINSPECT_3D_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eINSPECT_3D_FLOW_FINISH_3D_CAM_Z_WAIT_POS_CHECK, _T("_eINSPECT_3D_FLOW_FINISH_3D_CAM_Z_WAIT_POS_CHECK"));
			}
			break;

		case _eINSPECT_3D_FLOW_FINISH_GANTRY_XY_WAIT_POS:
			Devs::m_GantryMotion.Move_Gantry_X_Wait_Pos();
			Sleep(20);
			Devs::m_GantryMotion.Move_Gantry_Y_Wait_Pos();
			Sleep(20);

			SetStep(_eINSPECT_3D_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK, _T("_eINSPECT_3D_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eINSPECT_3D_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Wait_Pos() && Devs::m_GantryMotion.Is_Gantry_Y_Wait_Pos())
			{
				SetStep(_eINSPECT_3D_FLOW_DONE, _T("_eINSPECT_3D_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eINSPECT_3D_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK : Time Out !!!"), e3D_FLOW + 14);
				SetStep(_eINSPECT_3D_FLOW_ERROR, _T("_eINSPECT_3D_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eINSPECT_3D_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK, _T("_eINSPECT_3D_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK"));
			}
			break;

		case _eINSPECT_3D_FLOW_ERROR:
			break;

		case _eINSPECT_3D_FLOW_DONE:
		{
			SharedInfo::nPrevFlowID = e3D_FLOW; //KJT 20210326

			m_bFlowDone = TRUE;

			SharedInfo::CalTactTime(_T("3D_FLOW"), m_timeStart); //KJT 20210329

			SetStep(_eINSPECT_3D_FLOW_IDLE, _T("_eINSPECT_3D_FLOW_IDLE"));
			break;
		}
		default:
		{
			break;
		}
		}

		Sleep(100); //!!
	}
*/
}

//DO NOT USE
//BOOL CInspection3DFlow::Set3DInspectionPos(double dPosX[6][1], double dPosY[6][1])
//{
//	int i = 0;
//
//	m_nMaxPosCount = 5; //Tegkey Temp
//
//	for (i = 0; i < m_nMaxPosCount; i++)
//	{
//		m_dInspectionPos[i][0] = dPosX[i];
//		m_dInspectionPos[i][1] = dPosY[i];
//	}
//
//	return TRUE;
//}

stPOS_XYZ CInspection3DFlow::GetMeasurementPos(int nMeasurementPoint)
{
	stPOS_XYZ stPosXYZ;

	stPosXYZ.dPosX = m_dMeasurePosXY[nMeasurementPoint][0];
	stPosXYZ.dPosX -= CSystemData::m_Coordinate.Info.dOffsetReview10xTo3dCam_X;

	stPosXYZ.dPosY = m_dMeasurePosXY[nMeasurementPoint][1];
	stPosXYZ.dPosY -= CSystemData::m_Coordinate.Info.dOffsetReview10xTo3dCam_Y;

	stPosXYZ.dPosZ1 = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Wait_Pos;
	stPosXYZ.dPosZ2 = CManualData::m_ManualDataGantry.Info.m_dGantry_Z2_Inspection_3D_Pos;
	stPosXYZ.dPosZ3 = CManualData::m_ManualDataGantry.Info.m_dGantry_Z3_Wait_Pos;

	return stPosXYZ;
}

BOOL CInspection3DFlow::FlowInterlock()
{
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	
	if (pDlg->m_pH8Dlg->m_b3D_H8_Connected == FALSE)
	{
		SharedInfo::SetAlarm(_T("Inspection3DFlow : 3D Camera Connection Error !!!"), e3D_FLOW + 20);
		return FALSE;
	}

	if (m_nMaxPosCount <= 0)
	{
		SharedInfo::SetAlarm(_T("Inspection3DFlow : 3D Measure Point Count Error !!! (Count : 0)"), e3D_FLOW + 21);
		return FALSE;
	}
	if (pDlg->m_pH8Dlg->m_b3D_H8_Connected == FALSE)
	{
		SharedInfo::SetAlarm(_T("Inspection3DFlow : 3D Not Connected Error !!!"), e3D_FLOW + 22);
		return FALSE;
	}
	
	/////////////////////////////////////////////////////////////////////////////
	if (Devs::m_GantryMotion.CheckGantryXYZFlowInterlock(_T("Inspection3DFlow"), e3D_FLOW, 30) == FALSE)
	{
		return FALSE;
	}



	//if (Devs::m_CassetteMotion.Is_CSTPickUpUnitBwd() == FALSE)
	//{
	//	SharedInfo::SetAlarm(_T("Cst Pickup Unit Backward Error !!!"), e3D_FLOW + 21);
	//	return FALSE;
	//}	
	//if (SharedInfo::DInputValue[_DIN_CST_UNSAFE_POS_DETECT] == TRUE)
	//{
	//	SharedInfo::SetAlarm(_T("CST Unsafe Pos Detect Error !!!"), e3D_FLOW + 16);
	//	return FALSE;
	//}
	//if (SharedInfo::DInputValue[_DIN_CST_BACKWARD_DETECT] == TRUE)
	//{
	//	SharedInfo::SetAlarm(_T("CST Backward Detect Error !!!"), e3D_FLOW + 17);
	//	return FALSE;
	//}

	

	return TRUE;
}

BOOL CInspection3DFlow::SaveMeasureSlotGradientResult(int nRepeatCount)
{
	CVisionAgentDlg *pVisionAgentDlg;
	pVisionAgentDlg = (CVisionAgentDlg *)AfxGetMainWnd();

	CString strLastCnt;
	SYSTEMTIME st;
	GetLocalTime(&st);

	CStdioFile f, flog;
	CString str;
	CString StrTitle;
	string strMaskID[100];
	int i = 0;

	if (!f.Open(m_strPath, CFile::modeWrite | CFile::modeNoTruncate | CFile::shareDenyNone))
	{
		if (f.Open(m_strPath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::shareDenyNone))
		{
			StrTitle.AppendFormat(_T("Mask,%s\n\n"), SharedInfo::Active.tchStickId);
			f.WriteString(StrTitle);
		}
		else
		{
			TRACE("File Open Faile~!!\r\n");
			return FALSE;
		}
	}

	f.SeekToEnd();

	{
		/////////////////////////////////////////////////////////////////////////////////////////////////
		//Slot Gradition
		str.AppendFormat(_T("Slot Gradient\nLT\n"));

		str.AppendFormat(_T("TargetPosX,"));
		for (int i = 0; i < m_nCurPosCount; i++)
		{
			str.AppendFormat(_T("%.5f,"), m_dMeasurePosXY[i][0] * STICK_FLIP_XY);
		}
		str.AppendFormat(_T("\n"));
		str.AppendFormat(_T("RealPosX,"));
		for (int i = 0; i < m_nCurPosCount; i++)
		{
			str.AppendFormat(_T("%.5f,"), m_dMeasurePosXY[i][0]);
		}
		str.AppendFormat(_T("\n"));

		str.AppendFormat(_T("TargetPosY,"));
		for (int i = 0; i < m_nCurPosCount; i++)
		{
			str.AppendFormat(_T("%.5f,"), m_dMeasurePosXY[i][1] * STICK_FLIP_XY);
		}
		str.AppendFormat(_T("\n"));
		str.AppendFormat(_T("RealPosY,"));
		for (int i = 0; i < m_nCurPosCount; i++)
		{
			str.AppendFormat(_T("%.5f,"), m_dMeasurePosXY[i][1]);
		}
		str.AppendFormat(_T("\n"));

		str.AppendFormat(_T("m_nSlotCenterPosX,"));
		for (int i = 0; i < m_nCurPosCount; i++)
		{
			str.AppendFormat(_T("%d,"), m_nSlotCenterPos[i][0]);
		}
		str.AppendFormat(_T("\n"));
		str.AppendFormat(_T("m_nSlotCenterPosY,"));
		for (int i = 0; i < m_nCurPosCount; i++)
		{
			str.AppendFormat(_T("%d,"), m_nSlotCenterPos[i][1]);
		}
		str.AppendFormat(_T("\n"));

		str.AppendFormat(_T("m_nSlotStartPosX,"));
		for (int i = 0; i < m_nCurPosCount; i++)
		{
			str.AppendFormat(_T("%d,"), m_nSlotStartPos[i][0]);
		}
		str.AppendFormat(_T("\n"));
		str.AppendFormat(_T("m_nSlotStartPosY,"));
		for (int i = 0; i < m_nCurPosCount; i++)
		{
			str.AppendFormat(_T("%d,"), m_nSlotStartPos[i][1]);
		}
		str.AppendFormat(_T("\n"));

		str.AppendFormat(_T("m_nSlotSizeX,"));
		for (int i = 0; i < m_nCurPosCount; i++)
		{
			str.AppendFormat(_T("%d,"), m_nSlotSize[i][0]);
		}
		str.AppendFormat(_T("\n"));
		str.AppendFormat(_T("m_nSlotSizeY,"));
		for (int i = 0; i < m_nCurPosCount; i++)
		{
			str.AppendFormat(_T("%d,"), m_nSlotSize[i][1]);
		}
		str.AppendFormat(_T("\n"));

		////
		str.AppendFormat(_T("Gradient_L,"));
		for (int i = 0; i < m_nCurPosCount; i++)
		{
			str.AppendFormat(_T("%.5f,"), m_dGradientResult[i][0]);
		}
		str.AppendFormat(_T("\n"));
		str.AppendFormat(_T("Gradient_R,"));
		for (int i = 0; i < m_nCurPosCount; i++)
		{
			str.AppendFormat(_T("%.5f,"), m_dGradientResult[i][1]);
		}
		str.AppendFormat(_T("\n"));
		str.AppendFormat(_T("Gradient_T,"));
		for (int i = 0; i < m_nCurPosCount; i++)
		{
			str.AppendFormat(_T("%.5f,"), m_dGradientResult[i][2]);
		}
		str.AppendFormat(_T("\n"));
		str.AppendFormat(_T("Gradient_B,"));
		for (int i = 0; i < m_nCurPosCount; i++)
		{
			str.AppendFormat(_T("%.5f,"), m_dGradientResult[i][3]);
		}
		str.AppendFormat(_T("\n"));
	}

	f.WriteString(str);
	f.Close();

	return TRUE;
}