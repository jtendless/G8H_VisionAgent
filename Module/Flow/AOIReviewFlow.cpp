#include "stdafx.h"
#include "AOIReviewFlow.h"
#include "Log/Logger.h"
#include "Vision/Devs.h"
#include "Data/ModelData.h"
#include "CamAreaModul.h"
#include "Data/SystemData.h"
#include "VisionAgent.h"
#include "VisionAgentDlg.h"

CAOIReviewFlow::CAOIReviewFlow()
{
}


CAOIReviewFlow::~CAOIReviewFlow()
{
}

BOOL CAOIReviewFlow::InitProcess()
{
	m_StateComplete = NULL;
	m_FlowFinish = TRUE;
	m_bTerminate = FALSE;
	m_bFlowDone = TRUE;

#pragma region //Step Group
	int nGroupIndex = 0;

	m_sGroupInfo[nGroupIndex].m_bProcessingFlag = FALSE;
	m_sGroupInfo[nGroupIndex].nStartStep = _eAOI_REVIEW_FLOW_START;
	m_sGroupInfo[nGroupIndex].nEndStep = _eAOI_REVIEW_FLOW_INTERLOCK_CHECK;
	m_sGroupInfo[nGroupIndex].strGroupName.Format(_T("%d. Start"), nGroupIndex + 1);
	nGroupIndex++;

	m_sGroupInfo[nGroupIndex].m_bProcessingFlag = FALSE;
	m_sGroupInfo[nGroupIndex].nStartStep = _eAOI_REVIEW_FLOW_UNLOADER_READY;
	m_sGroupInfo[nGroupIndex].nEndStep = _eAOI_REVIEW_FLOW_GANTRY_ZX_READY_CHECK;
	m_sGroupInfo[nGroupIndex].strGroupName.Format(_T("%d. Other Axis Ready"), nGroupIndex + 1);
	nGroupIndex++;

	m_sGroupInfo[nGroupIndex].m_bProcessingFlag = FALSE;
	m_sGroupInfo[nGroupIndex].nStartStep = _eAOI_REVIEW_FLOW_CHECK_EXIST_DEFECT;
	m_sGroupInfo[nGroupIndex].nEndStep = _eAOI_REVIEW_FLOW_GANTRY_Z_ALL_FINISH_WAIT_POS_CHECK;
	m_sGroupInfo[nGroupIndex].strGroupName.Format(_T("%d. Review AOI"), nGroupIndex + 1);
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

BOOL CAOIReviewFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eAOI_REVIEW_FLOW_IDLE, _T("_eAOI_REVIEW_FLOW_IDLE"));

	if (hHandle != NULL)
	{
		CloseHandle(hHandle);
		hHandle = NULL;
	}

	return TRUE;
}

BOOL CAOIReviewFlow::Start(int nStep)
{
	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(nStep, _T("_eAOI_REVIEW_FLOW_START"));
	return TRUE;
}
BOOL CAOIReviewFlow::Stop()
{
	m_bStopBit = TRUE;
	return TRUE;
}

UINT CAOIReviewFlow::ThreadFunction(LPVOID lpParam)
{
	CAOIReviewFlow* pFlow = NULL;

	pFlow = (CAOIReviewFlow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}

VOID CAOIReviewFlow::ThreadFunctionEntry(VOID)
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

	while (m_FlowFinish)
	{
		WaitForSingleObject(hHandle, INFINITE);
		ResetEvent(hHandle);

		if (SharedInfo::bMachineStopFlag == TRUE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(_eAOI_REVIEW_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}

		switch (GetCurrentTotalStep())
		{
		case _eAOI_REVIEW_FLOW_IDLE:
		{
			break;
		}
		case _eAOI_REVIEW_FLOW_START:
		{
			m_timeStart = CTime::GetCurrentTime(); //KJT 20210329
			SharedInfo::m_timeUnitTact = m_timeStart;

			SharedInfo::nCurFlowID = eAOI_REVIEW_FLOW;

			m_nCurLineIndex = 0;
			m_nFrameIndex = 0;
			m_nDefectIndex = 0;
			m_dTargetPosX = 0.0;
			m_dTargetPosY = 0.0;

			//MakeReviewDir(); //KJT 20210309 Move

			SetStep(_eAOI_REVIEW_FLOW_INTERLOCK_CHECK, _T("_eAOI_REVIEW_FLOW_INTERLOCK_CHECK"));
			break;
		}

		case _eAOI_REVIEW_FLOW_INTERLOCK_CHECK:
			if (FlowInterlock() == FALSE)
			{
				SetStep(_eAOI_REVIEW_FLOW_ERROR, _T("_eAOI_REVIEW_FLOW_ERROR"));
			}
			else
			{
				SetStep(_eAOI_REVIEW_FLOW_UNLOADER_READY, _T("_eAOI_REVIEW_FLOW_UNLOADER_READY"));
			}
			break;

#pragma region //Unloader Ready
		case _eAOI_REVIEW_FLOW_UNLOADER_READY:
			Devs::m_Ready_UnloaderFlow.Start();

			SetStep(_eAOI_REVIEW_FLOW_UNLOADER_READY_CHECK, _T("_eAOI_REVIEW_FLOW_UNLOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eAOI_REVIEW_FLOW_UNLOADER_READY_CHECK:
			if (Devs::m_Ready_UnloaderFlow.IsFlowDone())
			{
				SetStep(_eAOI_REVIEW_FLOW_LOADER_READY, _T("_eAOI_REVIEW_FLOW_LOADER_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eAOI_REVIEW_FLOW_UNLOADER_READY_CHECK : Time Out !!!"), eAOI_REVIEW_FLOW + 0);
				SetStep(_eAOI_REVIEW_FLOW_ERROR, _T("_eAOI_REVIEW_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eAOI_REVIEW_FLOW_UNLOADER_READY_CHECK, _T("_eAOI_REVIEW_FLOW_UNLOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Loader Ready
		case _eAOI_REVIEW_FLOW_LOADER_READY:
			Devs::m_Ready_LoaderFlow.Start();

			SetStep(_eAOI_REVIEW_FLOW_LOADER_READY_CHECK, _T("_eAOI_REVIEW_FLOW_LOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eAOI_REVIEW_FLOW_LOADER_READY_CHECK:
			if (Devs::m_Ready_LoaderFlow.IsFlowDone())
			{
				//SetStep(_eAOI_REVIEW_FLOW_BOX_CAMERA_READY, _T("_eAOI_REVIEW_FLOW_BOX_CAMERA_READY"));
				SetStep(_eAOI_REVIEW_FLOW_GANTRY_ZX_READY, _T("_eAOI_REVIEW_FLOW_GANTRY_ZX_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eAOI_REVIEW_FLOW_LOADER_READY_CHECK : Time Out !!!"), eAOI_REVIEW_FLOW + 1);
				SetStep(_eAOI_REVIEW_FLOW_ERROR, _T("_eAOI_REVIEW_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eAOI_REVIEW_FLOW_LOADER_READY_CHECK, _T("_eAOI_REVIEW_FLOW_LOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Box Camera Ready
		//case _eAOI_REVIEW_FLOW_BOX_CAMERA_READY:
		//	Devs::m_BoxMotion.BoxAlignCameraYL_WaitPos();
		//	Sleep(20);
		//	Devs::m_BoxMotion.BoxAlignCameraYR_WaitPos();
		//	Sleep(500); //!!

		//	SetStep(_eAOI_REVIEW_FLOW_BOX_CAMERA_READY_CHECK, _T("_eAOI_REVIEW_FLOW_BOX_CAMERA_READY_CHECK"));
		//	SetTimeOut(TIME_OUT_MOTION);
		//	break;

		//case _eAOI_REVIEW_FLOW_BOX_CAMERA_READY_CHECK:
		//	if (Devs::m_BoxMotion.Is_BoxAlignCameraYL_WaitPos() == TRUE && Devs::m_BoxMotion.Is_BoxAlignCameraYR_WaitPos() == TRUE)
		//	{
		//		SetStep(_eAOI_REVIEW_FLOW_GANTRY_ZX_READY, _T("_eAOI_REVIEW_FLOW_GANTRY_ZX_READY"));
		//	}
		//	else if (IsTimeOut())
		//	{
		//		SharedInfo::SetAlarm(_T("_eAOI_REVIEW_FLOW_BOX_CAMERA_READY_CHECK : Time Out !!!"), eAOI_REVIEW_FLOW + 2);
		//		SetStep(_eAOI_REVIEW_FLOW_ERROR, _T("_eAOI_REVIEW_FLOW_ERROR"));
		//	}
		//	else
		//	{
		//		SetCheckStep(_eAOI_REVIEW_FLOW_BOX_CAMERA_READY_CHECK, _T("_eAOI_REVIEW_FLOW_BOX_CAMERA_READY_CHECK"));
		//	}
		//	break;
#pragma endregion

#pragma region //Gantry Z,X Ready
		case _eAOI_REVIEW_FLOW_GANTRY_ZX_READY:
			Devs::m_Ready_GantryZX_Flow.Start();

			SetStep(_eAOI_REVIEW_FLOW_GANTRY_ZX_READY_CHECK, _T("_eAOI_REVIEW_FLOW_GANTRY_ZX_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eAOI_REVIEW_FLOW_GANTRY_ZX_READY_CHECK:
			if (Devs::m_Ready_GantryZX_Flow.IsFlowDone())
			{
				SetStep(_eAOI_REVIEW_FLOW_CHECK_EXIST_DEFECT, _T("_eAOI_REVIEW_FLOW_CHECK_EXIST_DEFECT"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eAOI_REVIEW_FLOW_GANTRY_ZX_READY_CHECK : Time Out !!!"), eAOI_REVIEW_FLOW + 3);
				SetStep(_eAOI_REVIEW_FLOW_ERROR, _T("_eAOI_REVIEW_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eAOI_REVIEW_FLOW_GANTRY_ZX_READY_CHECK, _T("_eAOI_REVIEW_FLOW_GANTRY_ZX_READY_CHECK"));
			}
			break;
#pragma endregion

		case _eAOI_REVIEW_FLOW_CHECK_EXIST_DEFECT:
			if (CheckExistDefect(m_nCurLineIndex, m_nFrameIndex, m_nDefectIndex))
			{
				SetStep(_eAOI_REVIEW_FLOW_GANTRY_XY_DEFECT_POS, _T("_eAOI_REVIEW_FLOW_GANTRY_XY_DEFECT_POS"));
			}
			else
			{
				SetStep(_eAOI_REVIEW_FLOW_GANTRY_Z_ALL_FINISH_WAIT_POS, _T("_eAOI_REVIEW_FLOW_GANTRY_Z_ALL_FINISH_WAIT_POS"));
			}
			break;

		case _eAOI_REVIEW_FLOW_GANTRY_XY_DEFECT_POS:
			GetTargetPos(&m_dTargetPosX, &m_dTargetPosY);
			Devs::m_GantryMotion.Move_Gantry_X_Pos(m_dTargetPosX, FALSE);
			Sleep(20); //!!
			Devs::m_GantryMotion.Move_Gantry_Y_Pos(m_dTargetPosY);
			Sleep(20); //!!

			SetStep(_eAOI_REVIEW_FLOW_GANTRY_XY_DEFECT_POS_CHECK, _T("_eAOI_REVIEW_FLOW_GANTRY_XY_DEFECT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eAOI_REVIEW_FLOW_GANTRY_XY_DEFECT_POS_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Pos(m_dTargetPosX) && Devs::m_GantryMotion.Is_Gantry_Y_Pos(m_dTargetPosY))
			{
				SetStep(_eAOI_REVIEW_FLOW_GANTRY_Z2_INSPECTION_POS, _T("_eAOI_REVIEW_FLOW_GANTRY_Z2_INSPECTION_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eAOI_REVIEW_FLOW_GANTRY_XY_DEFECT_POS_CHECK : Time Out !!!"), eAOI_REVIEW_FLOW + 4);
				SetStep(_eAOI_REVIEW_FLOW_ERROR, _T("_eAOI_REVIEW_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eAOI_REVIEW_FLOW_GANTRY_XY_DEFECT_POS_CHECK, _T("_eAOI_REVIEW_FLOW_GANTRY_XY_DEFECT_POS_CHECK"));
			}
			break;

		//case _eAOI_REVIEW_FLOW_GANTRY_Z2_INSPECTION_POS:
		//	Devs::m_GantryMotion.Move_GantryZ2_AOI_Review_Pos();

		//	SetStep(_eAOI_REVIEW_FLOW_GANTRY_Z2_INSPECTION_POS_CHECK, _T("_eAOI_REVIEW_FLOW_GANTRY_Z2_INSPECTION_POS_CHECK"));
		//	SetTimeOut(TIME_OUT_MOTION);
		//	break;

		//case _eAOI_REVIEW_FLOW_GANTRY_Z2_INSPECTION_POS_CHECK:
		//	if (Devs::m_GantryMotion.Is_GantryZ2_AOI_Review_Pos())
		//	{
		//		//if (CModelData::m_AlignPara.Info.nMain2PAlignFocusType == eFocusType_Laser || CModelData::m_AlignPara.Info.nMain2PAlignFocusType == eFocusType_Both)
		//			SetStep(_eAOI_REVIEW_FLOW_ZOOM_20X_MOVE, _T("_eAOI_REVIEW_FLOW_ZOOM_20X_MOVE"));
		//		//else if (CModelData::m_AlignPara.Info.nMain2PAlignFocusType == eFocusType_Image)
		//		//	SetStep(_eAOI_REVIEW_FLOW_IMAGE_FOCUS_START, _T("_eAOI_REVIEW_FLOW_IMAGE_FOCUS_START"));
		//	}
		//	else if (IsTimeOut())
		//	{
		//		SharedInfo::SetAlarm(_T("_eAOI_REVIEW_FLOW_GANTRY_Z1_INSPECTION_POS_CHECK : Time Out !!!"), eAOI_REVIEW_FLOW + 5);
		//		SetStep(_eAOI_REVIEW_FLOW_ERROR, _T("_eAOI_REVIEW_FLOW_ERROR"));
		//	}
		//	else
		//	{
		//		SetCheckStep(_eAOI_REVIEW_FLOW_GANTRY_Z2_INSPECTION_POS_CHECK, _T("_eAOI_REVIEW_FLOW_GANTRY_Z2_INSPECTION_POS_CHECK"));
		//	}
		//	break;

//		case _eAOI_REVIEW_FLOW_LASER_FOCUS_START:
//			Devs::m_GantryMotion.LaserFocusMove();
//
//			SetStep(_eAOI_REVIEW_FLOW_LASER_FOCUS_CHECK, _T("_eAOI_REVIEW_FLOW_LASER_FOCUS_CHECK"));
//			SetTimeOut(TIME_OUT_MOTION);
//			break;
//
//		case _eAOI_REVIEW_FLOW_LASER_FOCUS_CHECK:
//			if (Devs::m_GantryMotion.LaserFocusMoveCheck())
//			{
//				Sleep(500); //!!	//KJT 20210321
//				
//				SetStep(_eAOI_REVIEW_FLOW_IMAGE_FOCUS_START, _T("_eAOI_REVIEW_FLOW_IMAGE_FOCUS_START"));
//			}
//			else if (IsTimeOut())
//			{
//				SharedInfo::SetAlarm(_T("_eAOI_REVIEW_FLOW_LASER_FOCUS_CHECK : Time Out !!!"), eAOI_REVIEW_FLOW + 6);
//				SetStep(_eAOI_REVIEW_FLOW_ERROR, _T("_eAOI_REVIEW_FLOW_ERROR"));
//			}
//			else
//			{
//				SetCheckStep(_eAOI_REVIEW_FLOW_LASER_FOCUS_CHECK, _T("_eAOI_REVIEW_FLOW_LASER_FOCUS_CHECK"));
//			}
//			break;
//
//		case _eAOI_REVIEW_FLOW_IMAGE_FOCUS_START:
//#ifndef SIM_MODE
//			g_pReview10x->m_bAfEnd = FALSE;
//			g_pReview10x->AutofoucsRun();
//#endif
//			SetStep(_eAOI_REVIEW_FLOW_IMAGE_FOCUS_CHECK, _T("_eAOI_REVIEW_FLOW_IMAGE_FOCUS_CHECK"));
//			SetTimeOut(TIME_OUT_MOTION);
//			break;
//
//		case _eAOI_REVIEW_FLOW_IMAGE_FOCUS_CHECK:
//#ifndef SIM_MODE
//			if (g_pReview10x->m_bAfEnd == TRUE)
//			{
//				Sleep(IMAGE_FOCUS_DELAY);
//				SetStep(_eAOI_REVIEW_FLOW_GRAB, _T("_eAOI_REVIEW_FLOW_GRAB"));
//			}
//			else if (IsTimeOut())
//			{
//				SharedInfo::SetAlarm(_T("_eAOI_REVIEW_FLOW_IMAGE_FOCUS_CHECK : Time Out !!!"), eAOI_REVIEW_FLOW + 7);
//				SetStep(_eAOI_REVIEW_FLOW_ERROR, _T("_eAOI_REVIEW_FLOW_ERROR"));
//			}
//			else
//			{
//				SetCheckStep(_eAOI_REVIEW_FLOW_IMAGE_FOCUS_CHECK, _T("_eAOI_REVIEW_FLOW_IMAGE_FOCUS_CHECK"));
//			}
//#else
//			Sleep(IMAGE_FOCUS_DELAY);
//			SetStep(_eAOI_REVIEW_FLOW_GRAB, _T("_eAOI_REVIEW_FLOW_GRAB"));
//#endif
//			break;

		case _eAOI_REVIEW_FLOW_ZOOM_20X_MOVE:
			break;

		case _eAOI_REVIEW_FLOW_ZOOM_20X_MOVE_CHECK:
			break;

		case _eAOI_REVIEW_FLOW_GRAB:
			//Image Save
			Str.Format(_T("%s\\Review_Line%d_Frame%d_Defect%d.bmp"), SharedInfo::STR_AOI_DEFECT_REVIEW_PATH, m_nCurLineIndex + 1, m_nFrameIndex + 1, m_nDefectIndex);
#ifndef SIM_MODE
			Devs::m_Camera10X->SaveDisplayImage(Str);
#endif

			m_nDefectIndex++;
			
			SetStep(_eAOI_REVIEW_FLOW_CHECK_EXIST_DEFECT, _T("_eAOI_REVIEW_FLOW_CHECK_EXIST_DEFECT"));
			break;

		case _eAOI_REVIEW_FLOW_GANTRY_Z_ALL_FINISH_WAIT_POS:
			Devs::m_GantryMotion.Move_GantryZ_All_Wait_Pos();
			Sleep(20); //!!

			SetStep(_eAOI_REVIEW_FLOW_GANTRY_Z_ALL_FINISH_WAIT_POS_CHECK, _T("_eAOI_REVIEW_FLOW_GANTRY_Z_ALL_FINISH_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eAOI_REVIEW_FLOW_GANTRY_Z_ALL_FINISH_WAIT_POS_CHECK:
			if (Devs::m_GantryMotion.Is_GantryZ_All_Wait_Pos())
			{
				SetStep(_eAOI_REVIEW_FLOW_DONE, _T("_eAOI_REVIEW_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eAOI_REVIEW_FLOW_GANTRY_Z_ALL_FINISH_WAIT_POS_CHECK : Time Out !!!"), eAOI_REVIEW_FLOW + 8);
				SetStep(_eAOI_REVIEW_FLOW_ERROR, _T("_eAOI_REVIEW_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eAOI_REVIEW_FLOW_GANTRY_Z_ALL_FINISH_WAIT_POS_CHECK, _T("_eAOI_REVIEW_FLOW_GANTRY_Z_ALL_FINISH_WAIT_POS_CHECK"));
			}
			break;

		case _eAOI_REVIEW_FLOW_DONE:
		{
			SharedInfo::nPrevFlowID = eAOI_REVIEW_FLOW; //KJT 20210326

			m_bFlowDone = TRUE;

			SharedInfo::CalTactTime(_T("AOI_REVIEW_FLOW"), m_timeStart); //KJT 20210329

			SetStep(_eAOI_REVIEW_FLOW_IDLE, _T("_eAOI_REVIEW_FLOW_IDLE"));
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

BOOL CAOIReviewFlow::GetTargetPos(double *dPosX, double *dPosY)
{
	*dPosX = SharedInfo::m_AOIDefectInfo[m_nCurLineIndex].dRealX[m_nFrameIndex][m_nDefectIndex];
	*dPosY = SharedInfo::m_AOIDefectInfo[m_nCurLineIndex].dRealY[m_nFrameIndex][m_nDefectIndex];
	
	return TRUE;
}

BOOL CAOIReviewFlow::CheckExistDefect(int nLineIndex, int nFrameIndex, int nDefectIndex)
{
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	CString Str = _T("");
	int i = 0, j = 0, k = 0;

	for (i = nLineIndex; i < SharedInfo::m_nAOIMaxScanLineCount; i++)
	{
		if (pDlg->m_SocketServer_AOI.ReadDefectInfoFile(i) == FALSE)
			return FALSE;

		for (j = nFrameIndex; j < SharedInfo::m_AOIDefectInfo[i].nFrameTotalCount; j++)
		{
			if (nDefectIndex < SharedInfo::m_AOIDefectInfo[i].nDefectCount[j])
			{
				m_nCurLineIndex = i;
				m_nFrameIndex = j;
				Str.Format(_T("Defect Exist Line_%d, Frame_%d, Index_%d"), m_nCurLineIndex + 1, m_nFrameIndex + 1, nDefectIndex + 1);
				Total_Msg(Str);
				return TRUE;
			}
			else
				nDefectIndex = 0;
		}
		nFrameIndex = 0;
		nDefectIndex = 0;
	}

	return FALSE;
}

//BOOL CAOIReviewFlow::MakeReviewDir()
//{
//	CString Str = _T("");
//
//	Str = SharedInfo::STR_SAVE_IMAGE_DIR_PATH;
//	::CreateDirectory(Str, NULL);
//	Str.AppendFormat(_T("\\AOI"));
//	::CreateDirectory(Str, NULL);
//	Str.Format(_T("D:\\SAVE_IMAGE\\AOI\\Review"));
//	::CreateDirectory(Str, NULL);
//
//	return TRUE;
//}

BOOL CAOIReviewFlow::FlowInterlock()
{
	/////////////////////////////////////////////////////////////////////////////
	if (Devs::m_LoaderMotion.CheckLoaderFlowInterlock(_T("AOIReviewFlow"), eAOI_REVIEW_FLOW, 30) == FALSE)
	{
		return FALSE;
	}

	/////////////////////////////////////////////////////////////////////////////
	if (Devs::m_UnloaderMotion.CheckUnloaderFlowInterlock(_T("AOIReviewFlow"), eAOI_REVIEW_FLOW, 40) == FALSE)
	{
		return FALSE;
	}

	/////////////////////////////////////////////////////////////////////////////
	if (Devs::m_GantryMotion.CheckGantryXYZFlowInterlock(_T("AOIReviewFlow"), eAOI_REVIEW_FLOW, 50) == FALSE)
	{
		return FALSE;
	}

	return TRUE;
}