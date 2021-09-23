#include "stdafx.h"
#include "Flow/Camera_Swap_Flow.h"
#include "Vision/Devs.h"
#include "VisionAgentDlg.h"
#include "Data/SystemData.h"
#include "Data/ManualData.h"

CCamera_Swap_Flow::CCamera_Swap_Flow()
{
}


CCamera_Swap_Flow::~CCamera_Swap_Flow()
{
}

BOOL CCamera_Swap_Flow::InitProcess()
{
	m_StateComplete = NULL;
	m_FlowFinish = TRUE;
	m_bTerminate = FALSE;
	m_bFlowDone = TRUE;
	m_nSwap_Mode = _eCam_Swap_None;

	//SetProcessLog(Process_Msg);
	//SetAlarmLog(LogMsg_Alarm);

	hHandle = CreateEvent(NULL, TRUE, FALSE, NULL);
	SetHandle(hHandle);
	pThread = AfxBeginThread(ThreadFunction, this);
	return TRUE;
}
BOOL CCamera_Swap_Flow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_eCAMERA_SWAP_FLOW_IDLE, _T("_eCAMERA_SWAP_FLOW_IDLE"));

	do
	{
		Sleep(10);
	} while (IsTerminate() == 0);

	if (hHandle != NULL)
	{
		CloseHandle(hHandle);
	}

	return TRUE;
}
BOOL CCamera_Swap_Flow::Start(int nSwapMode)
{
	m_bStopBit = FALSE;
	m_stepFlag = 0;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	//SetStep(_eORIGIN_ALL_AXIS_FLOW_START, _T("_eORIGIN_ALL_AXIS_FLOW_START"));
	
	m_nSwap_Mode = nSwapMode;

	SetStep(_eCAMERA_SWAP_FLOW_START, _T("_eCAMERA_SWAP_FLOW_START"));
	return TRUE;
}
BOOL CCamera_Swap_Flow::Stop()
{
	m_nSwap_Mode = _eCam_Swap_None;
	m_bStopBit = TRUE;
	SetStop(); //!!
	return TRUE;
}
UINT CCamera_Swap_Flow::ThreadFunction(LPVOID lpParam)
{
	CCamera_Swap_Flow* pFlow = NULL;

	pFlow = (CCamera_Swap_Flow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}
VOID CCamera_Swap_Flow::ThreadFunctionEntry(VOID)
{
	DWORD	dwResult = 0;
	double	dStrt_Time = GetTickCount();
	double	dEnd_Time = GetTickCount();
	double	dWait_Time = GetTickCount();
	int		nWork_Mask_Mode = -1;
	int		nWork_Mask_Index = -1;
	BOOL	bComplete_Step = FALSE;
	CVisionAgentDlg *pMain = (CVisionAgentDlg*)AfxGetMainWnd();
	CString Str = _T("");

	BOOL bResult = FALSE;
	double dVel = 5.0;
	double dAcc = 10.0;
	double dDec = 10.0;
	int LimitSignal = 0;
	int i, nRtn;

	double dSrcPosX = 0.0, dSrcPosY = 0.0, dTargetPosX = 0.0, dTargetPosY = 0.0;
	double dPosZ[3] = { 0.0, 0.0, 0.0 };

	while (m_FlowFinish)
	{
		WaitForSingleObject(hHandle, INFINITE);
		ResetEvent(hHandle);

		if (SharedInfo::bMachineStopFlag == TRUE)// && m_bStopBit == FALSE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(_eCAMERA_SWAP_FLOW_IDLE); //KJT 20210318
			continue; //!!
		}
		

		switch (GetCurrentTotalStep())
		{
		case _eCAMERA_SWAP_FLOW_IDLE:
		{
			break;
		}

		case _eCAMERA_SWAP_FLOW_START:
			SetStep(_eCAMERA_SWAP_FLOW_INTERLOCK_CHECK, _T("_eCAMERA_SWAP_FLOW_INTERLOCK_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eCAMERA_SWAP_FLOW_INTERLOCK_CHECK:
			if (FlowInterlock() == FALSE)
			{
				m_bFlowDone = TRUE;
				SetStep(_eCAMERA_SWAP_FLOW_IDLE, _T("_eCAMERA_SWAP_FLOW_IDLE"));
			}
			else
			{
				if (m_nSwap_Mode == _eCam_Swap_PreAlignToReview || m_nSwap_Mode == _eCam_Swap_Review20XToReview10X ||
					m_nSwap_Mode == _eCam_Swap_Review50XToReview10X || m_nSwap_Mode == _eCam_Swap_Review50XToReview10X)
				{
					SharedInfo::nGantryZ1View = eViewReview10X;
				}
				else if (m_nSwap_Mode == _eCam_Swap_Review10XToReview20X || m_nSwap_Mode == _eCam_Swap_ReviewPreAlignTo20X ||
					m_nSwap_Mode == _eCam_Swap_Review50XTo20X || m_nSwap_Mode == _eCam_Swap_Review50XTo20X)
				{
					SharedInfo::nGantryZ1View = eViewReview20X;
				}
				else if (m_nSwap_Mode == _eCam_Swap_Review10XToReview50X || m_nSwap_Mode == _eCam_Swap_Review20XTo50X ||
					m_nSwap_Mode == _eCam_Swap_PreAlignToReview50X)
				{
					SharedInfo::nGantryZ1View = eViewReview50X;
				}
				else if (m_nSwap_Mode == _eCam_Swap_ReviewToPreAlign || m_nSwap_Mode == _eCam_Swap_Review20XToPreAlign ||
					m_nSwap_Mode == _eCam_Swap_Review50XToPreAlign)
				{
					SharedInfo::nGantryZ1View = eViewPreAlign;
				}

				SetStep(_eCAMERA_SWAP_FLOW_UNLOADER_READY, _T("_eCAMERA_SWAP_FLOW_UNLOADER_READY"));
			}
			break;
		
#pragma region //Unloader Ready
		case _eCAMERA_SWAP_FLOW_UNLOADER_READY:
			Devs::m_Ready_UnloaderFlow.Start();

			SetStep(_eCAMERA_SWAP_FLOW_UNLOADER_READY_CHECK, _T("_eCAMERA_SWAP_FLOW_UNLOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eCAMERA_SWAP_FLOW_UNLOADER_READY_CHECK:
			if (Devs::m_Ready_UnloaderFlow.IsFlowDone())
			{
				SetStep(_eCAMERA_SWAP_FLOW_LOADER_READY, _T("_eCAMERA_SWAP_FLOW_LOADER_READY"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eCAMERA_SWAP_FLOW_UNLOADER_READY_CHECK : Time Out"), eCAMERA_SWAP_FLOW + 0);
				SetStep(_eCAMERA_SWAP_FLOW_ERROR, _T("_eCAMERA_SWAP_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eCAMERA_SWAP_FLOW_UNLOADER_READY_CHECK, _T("_eCAMERA_SWAP_FLOW_UNLOADER_READY_CHECK"));
			}
			break;
#pragma endregion

#pragma region //Loader Ready
		case _eCAMERA_SWAP_FLOW_LOADER_READY:
			Devs::m_Ready_LoaderFlow.Start();

			SetStep(_eCAMERA_SWAP_FLOW_LOADER_READY_CHECK, _T("_eCAMERA_SWAP_LOADER_READY_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _eCAMERA_SWAP_FLOW_LOADER_READY_CHECK:
			if (Devs::m_Ready_LoaderFlow.IsFlowDone())
			{
				SetStep(_eCAMERA_SWAP_FLOW_GANTRY_XYZ_POS, _T("_eCAMERA_SWAP_FLOW_GANTRY_XYZ_POS"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eCAMERA_SWAP_FLOW_LOADER_READY_CHECK : Time Out"), eCAMERA_SWAP_FLOW + 1);
				SetStep(_eCAMERA_SWAP_FLOW_ERROR, _T("_eCAMERA_SWAP_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eCAMERA_SWAP_FLOW_LOADER_READY_CHECK, _T("_eCAMERA_SWAP_FLOW_LOADER_READY_CHECK"));
			}
			break;
#pragma endregion

		case _eCAMERA_SWAP_FLOW_GANTRY_XYZ_POS:
			if (m_nSwap_Mode == _eCam_Swap_PreAlignToReview)
			{
				dSrcPosX = SharedInfo::GetCmdPos(AXIS_GANTRY_X);
				dSrcPosY = SharedInfo::GetCmdPos(AXIS_VIRTUAL_GANTRY_Y);
				dTargetPosX = dSrcPosX + CSystemData::m_Coordinate.Info.dOffsetReview10xToPreAlign_X;
				dTargetPosY = dSrcPosY + CSystemData::m_Coordinate.Info.dOffsetReview10xToPreAlign_Y;

				dPosZ[0] = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Inspection_Review_Pos;
				//dPosZ[1] = CManualData::m_ManualDataGantry.Info.m_dGantry_Z2_Wait_Pos;
				//dPosZ[2] = CManualData::m_ManualDataGantry.Info.m_dGantry_Z3_Wait_Pos;

				Devs::m_GantryMotion.Move_GantryXYZ(dTargetPosX, dTargetPosY, dPosZ, TRUE);

				SetStep(_eCAMERA_SWAP_FLOW_GANTRY_XYZ_POS_CHECK, _T("_eCAMERA_SWAP_FLOW_GANTRY_XYZ_POS_CHECK"));
				SetTimeOut(TIME_OUT_MOTION);
			}
			else if (m_nSwap_Mode == _eCam_Swap_ReviewToPreAlign)
			{
				dSrcPosX = SharedInfo::GetCmdPos(AXIS_GANTRY_X);
				dSrcPosY = SharedInfo::GetCmdPos(AXIS_VIRTUAL_GANTRY_Y);
				dTargetPosX = dSrcPosX - CSystemData::m_Coordinate.Info.dOffsetReview10xToPreAlign_X;
				dTargetPosY = dSrcPosY - CSystemData::m_Coordinate.Info.dOffsetReview10xToPreAlign_Y;

				dPosZ[0] = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_PreAlign_Pos;

				Devs::m_GantryMotion.Move_GantryXYZ(dTargetPosX, dTargetPosY, dPosZ, TRUE);

				SetStep(_eCAMERA_SWAP_FLOW_GANTRY_XYZ_POS_CHECK, _T("_eCAMERA_SWAP_FLOW_GANTRY_XYZ_POS_CHECK"));
				SetTimeOut(TIME_OUT_MOTION);
			}
			else if (m_nSwap_Mode == _eCam_Swap_Review10XToReview20X)
			{
				dSrcPosX = SharedInfo::GetCmdPos(AXIS_GANTRY_X);
				dSrcPosY = SharedInfo::GetCmdPos(AXIS_VIRTUAL_GANTRY_Y);
				dTargetPosX = dSrcPosX - CSystemData::m_Coordinate.Info.dOffsetReview10xTo20x_X;
				dTargetPosY = dSrcPosY - CSystemData::m_Coordinate.Info.dOffsetReview10xTo20x_Y;

				dPosZ[0] = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Inspection_Review_Pos;

				Devs::m_GantryMotion.Move_GantryXYZ(dTargetPosX, dTargetPosY, dPosZ, FALSE);

				SetStep(_eCAMERA_SWAP_FLOW_GANTRY_XYZ_POS_CHECK, _T("_eCAMERA_SWAP_FLOW_GANTRY_XYZ_POS_CHECK"));
				SetTimeOut(TIME_OUT_MOTION);
			}
			else if (m_nSwap_Mode == _eCam_Swap_Review20XToReview10X)
			{
				dSrcPosX = SharedInfo::GetCmdPos(AXIS_GANTRY_X);
				dSrcPosY = SharedInfo::GetCmdPos(AXIS_VIRTUAL_GANTRY_Y);
				dTargetPosX = dSrcPosX + CSystemData::m_Coordinate.Info.dOffsetReview10xTo20x_X;
				dTargetPosY = dSrcPosY + CSystemData::m_Coordinate.Info.dOffsetReview10xTo20x_Y;

				dPosZ[0] = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Inspection_Review_Pos;

				Devs::m_GantryMotion.Move_GantryXYZ(dTargetPosX, dTargetPosY, dPosZ, FALSE);

				SetStep(_eCAMERA_SWAP_FLOW_GANTRY_XYZ_POS_CHECK, _T("_eCAMERA_SWAP_FLOW_GANTRY_XYZ_POS_CHECK"));
				SetTimeOut(TIME_OUT_MOTION);
			}
			else if (m_nSwap_Mode == _eCam_Swap_Review10XToReview50X)
			{
				dSrcPosX = SharedInfo::GetCmdPos(AXIS_GANTRY_X);
				dSrcPosY = SharedInfo::GetCmdPos(AXIS_VIRTUAL_GANTRY_Y);
				dTargetPosX = dSrcPosX - CSystemData::m_Coordinate.Info.dOffsetReview10xTo50x_X;
				dTargetPosY = dSrcPosY - CSystemData::m_Coordinate.Info.dOffsetReview10xTo50x_Y;

				dPosZ[0] = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Inspection_Review_Pos;

				Devs::m_GantryMotion.Move_GantryXYZ(dTargetPosX, dTargetPosY, dPosZ, FALSE);

				SetStep(_eCAMERA_SWAP_FLOW_GANTRY_XYZ_POS_CHECK, _T("_eCAMERA_SWAP_FLOW_GANTRY_XYZ_POS_CHECK"));
				SetTimeOut(TIME_OUT_MOTION);
			}
			else if (m_nSwap_Mode == _eCam_Swap_Review50XToReview10X)
			{
				dSrcPosX = SharedInfo::GetCmdPos(AXIS_GANTRY_X);
				dSrcPosY = SharedInfo::GetCmdPos(AXIS_VIRTUAL_GANTRY_Y);
				dTargetPosX = dSrcPosX + CSystemData::m_Coordinate.Info.dOffsetReview10xTo50x_X;
				dTargetPosY = dSrcPosY + CSystemData::m_Coordinate.Info.dOffsetReview10xTo50x_Y;

				dPosZ[0] = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Inspection_Review_Pos;

				Devs::m_GantryMotion.Move_GantryXYZ(dTargetPosX, dTargetPosY, dPosZ, FALSE);

				SetStep(_eCAMERA_SWAP_FLOW_GANTRY_XYZ_POS_CHECK, _T("_eCAMERA_SWAP_FLOW_GANTRY_XYZ_POS_CHECK"));
				SetTimeOut(TIME_OUT_MOTION);
			}
			else if (m_nSwap_Mode == _eCam_Swap_Review20XToPreAlign)
			{
				dSrcPosX = SharedInfo::GetCmdPos(AXIS_GANTRY_X);
				dSrcPosY = SharedInfo::GetCmdPos(AXIS_VIRTUAL_GANTRY_Y);
				dTargetPosX = dSrcPosX - CSystemData::m_Coordinate.Info.dOffsetReview10xToPreAlign_X + CSystemData::m_Coordinate.Info.dOffsetReview10xTo20x_X;
				dTargetPosY = dSrcPosY - CSystemData::m_Coordinate.Info.dOffsetReview10xToPreAlign_Y + CSystemData::m_Coordinate.Info.dOffsetReview10xTo20x_Y;

				dPosZ[0] = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Inspection_Review_Pos;

				Devs::m_GantryMotion.Move_GantryXYZ(dTargetPosX, dTargetPosY, dPosZ, TRUE);

				SetStep(_eCAMERA_SWAP_FLOW_GANTRY_XYZ_POS_CHECK, _T("_eCAMERA_SWAP_FLOW_GANTRY_XYZ_POS_CHECK"));
				SetTimeOut(TIME_OUT_MOTION);
			}
			else if (m_nSwap_Mode == _eCam_Swap_ReviewPreAlignTo20X)
			{
				dSrcPosX = SharedInfo::GetCmdPos(AXIS_GANTRY_X);
				dSrcPosY = SharedInfo::GetCmdPos(AXIS_VIRTUAL_GANTRY_Y);
				dTargetPosX = dSrcPosX + CSystemData::m_Coordinate.Info.dOffsetReview10xToPreAlign_X - CSystemData::m_Coordinate.Info.dOffsetReview10xTo20x_X;
				dTargetPosY = dSrcPosY + CSystemData::m_Coordinate.Info.dOffsetReview10xToPreAlign_Y - CSystemData::m_Coordinate.Info.dOffsetReview10xTo20x_Y;

				dPosZ[0] = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Inspection_Review_Pos;

				Devs::m_GantryMotion.Move_GantryXYZ(dTargetPosX, dTargetPosY, dPosZ, TRUE);

				SetStep(_eCAMERA_SWAP_FLOW_GANTRY_XYZ_POS_CHECK, _T("_eCAMERA_SWAP_FLOW_GANTRY_XYZ_POS_CHECK"));
				SetTimeOut(TIME_OUT_MOTION);
			}
			else if (m_nSwap_Mode == _eCam_Swap_Review20XTo50X)
			{
				dSrcPosX = SharedInfo::GetCmdPos(AXIS_GANTRY_X);
				dSrcPosY = SharedInfo::GetCmdPos(AXIS_VIRTUAL_GANTRY_Y);
				dTargetPosX = dSrcPosX - CSystemData::m_Coordinate.Info.dOffsetReview10xTo50x_X + CSystemData::m_Coordinate.Info.dOffsetReview10xTo20x_X;
				dTargetPosY = dSrcPosY - CSystemData::m_Coordinate.Info.dOffsetReview10xTo50x_Y + CSystemData::m_Coordinate.Info.dOffsetReview10xTo20x_Y;

				dPosZ[0] = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Inspection_Review_Pos;

				Devs::m_GantryMotion.Move_GantryXYZ(dTargetPosX, dTargetPosY, dPosZ, FALSE);

				SetStep(_eCAMERA_SWAP_FLOW_GANTRY_XYZ_POS_CHECK, _T("_eCAMERA_SWAP_FLOW_GANTRY_XYZ_POS_CHECK"));
				SetTimeOut(TIME_OUT_MOTION);
			}
			else if (m_nSwap_Mode == _eCam_Swap_Review50XTo20X)
			{
				dSrcPosX = SharedInfo::GetCmdPos(AXIS_GANTRY_X);
				dSrcPosY = SharedInfo::GetCmdPos(AXIS_VIRTUAL_GANTRY_Y);
				dTargetPosX = dSrcPosX + CSystemData::m_Coordinate.Info.dOffsetReview10xTo50x_X - CSystemData::m_Coordinate.Info.dOffsetReview10xTo20x_X;
				dTargetPosY = dSrcPosY + CSystemData::m_Coordinate.Info.dOffsetReview10xTo50x_Y - CSystemData::m_Coordinate.Info.dOffsetReview10xTo20x_Y;

				dPosZ[0] = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Inspection_Review_Pos;

				Devs::m_GantryMotion.Move_GantryXYZ(dTargetPosX, dTargetPosY, dPosZ, FALSE);

				SetStep(_eCAMERA_SWAP_FLOW_GANTRY_XYZ_POS_CHECK, _T("_eCAMERA_SWAP_FLOW_GANTRY_XYZ_POS_CHECK"));
				SetTimeOut(TIME_OUT_MOTION);
			}
			else if (m_nSwap_Mode == _eCam_Swap_PreAlignToReview50X)
			{
				dSrcPosX = SharedInfo::GetCmdPos(AXIS_GANTRY_X);
				dSrcPosY = SharedInfo::GetCmdPos(AXIS_VIRTUAL_GANTRY_Y);
				dTargetPosX = dSrcPosX + CSystemData::m_Coordinate.Info.dOffsetReview10xToPreAlign_X - CSystemData::m_Coordinate.Info.dOffsetReview10xTo50x_X;
				dTargetPosY = dSrcPosY + CSystemData::m_Coordinate.Info.dOffsetReview10xToPreAlign_Y - CSystemData::m_Coordinate.Info.dOffsetReview10xTo50x_Y;

				dPosZ[0] = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Inspection_Review_Pos;

				Devs::m_GantryMotion.Move_GantryXYZ(dTargetPosX, dTargetPosY, dPosZ, TRUE);

				SetStep(_eCAMERA_SWAP_FLOW_GANTRY_XYZ_POS_CHECK, _T("_eCAMERA_SWAP_FLOW_GANTRY_XYZ_POS_CHECK"));
				SetTimeOut(TIME_OUT_MOTION);
			}
			else if (m_nSwap_Mode == _eCam_Swap_Review50XToPreAlign)
			{
				dSrcPosX = SharedInfo::GetCmdPos(AXIS_GANTRY_X);
				dSrcPosY = SharedInfo::GetCmdPos(AXIS_VIRTUAL_GANTRY_Y);
				dTargetPosX = dSrcPosX - CSystemData::m_Coordinate.Info.dOffsetReview10xToPreAlign_X + CSystemData::m_Coordinate.Info.dOffsetReview10xTo50x_X;
				dTargetPosY = dSrcPosY - CSystemData::m_Coordinate.Info.dOffsetReview10xToPreAlign_Y + CSystemData::m_Coordinate.Info.dOffsetReview10xTo50x_Y;

				dPosZ[0] = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Inspection_Review_Pos;

				Devs::m_GantryMotion.Move_GantryXYZ(dTargetPosX, dTargetPosY, dPosZ, TRUE);

				SetStep(_eCAMERA_SWAP_FLOW_GANTRY_XYZ_POS_CHECK, _T("_eCAMERA_SWAP_FLOW_GANTRY_XYZ_POS_CHECK"));
				SetTimeOut(TIME_OUT_MOTION);
			}
			else
			{
				Total_Msg(_T("Swap mode error"));
				SharedInfo::SetAlarm(_T("_eCAMERA_SWAP_FLOW_GANTRY_XY_POS : Swap mode"), eCAMERA_SWAP_FLOW + 3);
				SetStep(_eCAMERA_SWAP_FLOW_ERROR, _T("_eCAMERA_SWAP_FLOW_ERROR"));
			}			
			break;

		case _eCAMERA_SWAP_FLOW_GANTRY_XYZ_POS_CHECK:
			if (Devs::m_GantryMotion.Is_Gantry_X_Pos(dTargetPosX) == TRUE && Devs::m_GantryMotion.Is_Gantry_Y_Pos(dTargetPosY) &&
				Devs::m_GantryMotion.Is_Gantry_Z1_Pos(dPosZ[0]) == TRUE )
			{
				SetStep(_eCAMERA_SWAP_FLOW_DONE, _T("_eCAMERA_SWAP_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SharedInfo::SetAlarm(_T("_eCAMERA_SWAP_FLOW_GANTRY_XY_POS_CHECK : Time Out"), eCAMERA_SWAP_FLOW + 4);
				SetStep(_eCAMERA_SWAP_FLOW_ERROR, _T("_eCAMERA_SWAP_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_eCAMERA_SWAP_FLOW_GANTRY_XYZ_POS_CHECK, _T("_eCAMERA_SWAP_FLOW_GANTRY_XYZ_POS_CHECK"));
			}
			break;

		case _eCAMERA_SWAP_FLOW_DONE:
		{
			m_bFlowDone = TRUE;

			SetStep(_eCAMERA_SWAP_FLOW_IDLE, _T("_eCAMERA_SWAP_FLOW_IDLE"));
		}
			break;

		case _eCAMERA_SWAP_FLOW_ERROR:
			break;

		case _eCAMERA_SWAP_FLOW_STOP:
			break;

		default:
		{
			break;
		}
		}

		Sleep(100); //!!
	}
}

BOOL CCamera_Swap_Flow::FlowInterlock()
{
	CString Str = _T("");

	/////////////////////////////////////////////////////////////////////////////
	if (Devs::m_GantryMotion.CheckGantryXYZFlowInterlock(_T("Camera_Swap_Flow"), eCAMERA_SWAP_FLOW, 20) == FALSE)
	{
		return FALSE;
	}

	//if (SharedInfo::GetServoOnStatus(AXIS_CAMERA_Z1) != TRUE)
	//{
	//	Total_Msg(_T("Camera Z1 Servo On Check !!!"));
	//	return FALSE;
	//}

	return TRUE;
}