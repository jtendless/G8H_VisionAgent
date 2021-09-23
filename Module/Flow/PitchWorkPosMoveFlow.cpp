#include "stdafx.h"
#include "PitchWorkPosMoveFlow.h"
#include "Vision/Devs.h"
#include "VisionAgentDlg.h"
#include "Motion/BoxMotion.h"
#include "Data/ManualData.h"
#include "Data/ModelData.h"

CPitchWorkPosMoveFlow::CPitchWorkPosMoveFlow()
{
}


CPitchWorkPosMoveFlow::~CPitchWorkPosMoveFlow()
{
}

BOOL CPitchWorkPosMoveFlow::InitProcess()
{
	m_StateComplete = NULL;
	m_FlowFinish = TRUE;
	m_bTerminate = FALSE;
	m_bFlowDone = TRUE;

	for (int i = 0; i < eGRIPPER_ROW_MAX; i++)
	{
		m_eRemoteAxisPitch_L[i] = (enum_REMOTE_AXIS_AJIN)(REMOTE_AXIS_AJIN_GRIPPER_PITCH_L1 + i);
		m_eRemoteAxisPitch_R[i] = (enum_REMOTE_AXIS_AJIN)(REMOTE_AXIS_AJIN_GRIPPER_PITCH_R1 + i);

		m_bLimitSignal_L[i] = FALSE;
		m_bLimitSignal_R[i] = FALSE;

		dWorkPos_L[i] = 0.0;
		dWorkPos_R[i] = 0.0;
	}

	//SetProcessLog(Process_Msg);
//SetAlarmLog(LogMsg_Alarm);

	hHandle = CreateEvent(NULL, TRUE, FALSE, NULL);
	SetHandle(hHandle);
	pThread = AfxBeginThread(ThreadFunction, this);
	return TRUE;
}

BOOL CPitchWorkPosMoveFlow::EndProcess()
{
	m_FlowFinish = FALSE;

	SetStep(_ePITCH_WORK_POS_MOVE_FLOW_IDLE);

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

BOOL CPitchWorkPosMoveFlow::Start(int nStep)
{
	m_bStopBit = FALSE;
	m_bFlowDone = FALSE;
	SharedInfo::bMachineStopFlag = FALSE;
	SetStep(nStep, _T("_ePITCH_WORK_POS_MOVE_FLOW_START"));
	return TRUE;
}
BOOL CPitchWorkPosMoveFlow::Stop()
{
	m_bStopBit = TRUE;
	SetStop(); //!!
	return TRUE;
}
UINT CPitchWorkPosMoveFlow::ThreadFunction(LPVOID lpParam)
{
	CPitchWorkPosMoveFlow* pFlow = NULL;

	pFlow = (CPitchWorkPosMoveFlow*)lpParam;

	pFlow->ThreadFunctionEntry();

	pFlow->SetTerminate(TRUE);

	return 0;
}

VOID CPitchWorkPosMoveFlow::ThreadFunctionEntry(VOID)
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
	int i = 0;
	BOOL bResult = TRUE;
	int nWingIndex = 0;
	double dVel = 3.0;
	double dAccel = 10.0;
	double dDecel = 10.0;

	while (m_FlowFinish)
	{
		WaitForSingleObject(hHandle, INFINITE);
		ResetEvent(hHandle);

		if (SharedInfo::bMachineStopFlag == TRUE && m_bStopBit == FALSE)
		{
			m_bStopBit = TRUE;

			Devs::m_BaseMotion.SetDOutputBitValue(_DOUT_LASER_POINT_1_on_off, TRUE);

			continue; //!!
		}
		if (SharedInfo::bMachineStopFlag == TRUE)
			continue;

		switch (GetCurrentTotalStep())
		{
		case _ePITCH_WORK_POS_MOVE_FLOW_IDLE:
		{
			break;
		}
		case _ePITCH_WORK_POS_MOVE_FLOW_START:
			m_nFirstUseRowIndex = -1;
			m_nLastUseRowIndex = -1;
			m_nStickWingLastIndex = 0;
			for (i = 0; i < eGRIPPER_ROW_MAX; i++)
			{
				if (m_nFirstUseRowIndex == -1 && CModelData::m_StretchPara.Info.bStretchUse[i] == TRUE)
				{
					m_nFirstUseRowIndex = i;
				}
				if (m_nFirstUseRowIndex != -1 && m_nLastUseRowIndex == -1 && CModelData::m_StretchPara.Info.bStretchUse[i] == FALSE)
				{
					m_nLastUseRowIndex = i - 1;
					m_nStickWingLastIndex = m_nLastUseRowIndex - m_nFirstUseRowIndex;
					break;
				}
			}
			if (m_nFirstUseRowIndex == -1 || m_nLastUseRowIndex == -1)
			{
				Total_Msg(_T("Check Stretch Use State !!!"));
				SetStep(_ePITCH_WORK_POS_MOVE_FLOW_ERROR, _T("_ePITCH_WORK_POS_MOVE_FLOW_ERROR"));
			}
			else
			{
				SetStep(_ePITCH_WORK_POS_MOVE_FLOW_INTERLOCK_CHECK, _T("_ePITCH_WORK_POS_MOVE_FLOW_INTERLOCK_CHECK"));
			}
			break;

		case _ePITCH_WORK_POS_MOVE_FLOW_INTERLOCK_CHECK:
			bResult = TRUE;
			nWingIndex = 0;
			for (i = 0; i < eGRIPPER_ROW_MAX; i++)
			{
				if (CModelData::m_StretchPara.Info.bStretchUse[i] == TRUE)
				{
					dWorkPos_L[i] = CModelData::m_MaterialPara.Info.dStickWingCenterYOffset[nWingIndex];
					dWorkPos_R[i] = CModelData::m_MaterialPara.Info.dStickWingCenterYOffset[nWingIndex];
					if (Devs::m_PitchMotion.IsPitchPosMove((enum_Axis)(AXIS_GRIPPER_PITCH_L1 + i), dWorkPos_L[i]) == FALSE ||
						Devs::m_PitchMotion.IsPitchPosMove((enum_Axis)(AXIS_GRIPPER_PITCH_R1 + i), dWorkPos_R[i]) == FALSE)
					{
						bResult = FALSE;
						break;
					}
					nWingIndex++;
				}
			}
			if (bResult == TRUE)
			{
				SetStep(_ePITCH_WORK_POS_MOVE_FLOW_DONE, _T("_ePITCH_WORK_POS_MOVE_FLOW_DONE"));
			}
			else
			{
				if (FlowInterlock() == FALSE)
				{
					SetStep(_ePITCH_WORK_POS_MOVE_FLOW_ERROR, _T("_ePITCH_WORK_POS_MOVE_FLOW_ERROR"));
				}
				else
				{
					if (m_nFirstUseRowIndex > 0)
					{
						m_nCurAxisRowIndex = 0;
						SetStep(_ePITCH_WORK_POS_MOVE_FLOW_UNUSE_ROW_UP_P_LIMIT_POS, _T("_ePITCH_WORK_POS_MOVE_FLOW_UNUSE_ROW_UP_P_LIMIT_POS"));
					}
					else
					{
						m_nCurAxisRowIndex = eGRIPPER_ROW_MAX - 1;
						SetStep(_ePITCH_WORK_POS_MOVE_FLOW_UNUSE_ROW_DOWN_N_LIMIT_POS, _T("_ePITCH_WORK_POS_MOVE_FLOW_UNUSE_ROW_DOWN_N_LIMIT_POS"));
					}
				}
			}
			break;

		case _ePITCH_WORK_POS_MOVE_FLOW_UNUSE_ROW_UP_P_LIMIT_POS:
			m_bLimitSignal_L[m_nCurAxisRowIndex] = FALSE;
			m_bLimitSignal_R[m_nCurAxisRowIndex] = FALSE;

			SharedInfo::GetAutoSpeed((enum_Axis)(AXIS_GRIPPER_PITCH_L1 + m_nCurAxisRowIndex), &dVel, &dAccel, &dDecel);
			Devs::MotionIf.AxisVelMove(m_eRemoteAxisPitch_L[m_nCurAxisRowIndex], dVel, dAccel, dDecel);
			Sleep(30); //!!
			SharedInfo::GetAutoSpeed((enum_Axis)(AXIS_GRIPPER_PITCH_R1 + m_nCurAxisRowIndex), &dVel, &dAccel, &dDecel);
			Devs::MotionIf.AxisVelMove(m_eRemoteAxisPitch_R[m_nCurAxisRowIndex], dVel, dAccel, dDecel);

			SetStep(_ePITCH_WORK_POS_MOVE_FLOW_UNUSE_ROW_UP_P_LIMIT_POS_CHECK, _T("_ePITCH_WORK_POS_MOVE_FLOW_UNUSE_ROW_UP_P_LIMIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _ePITCH_WORK_POS_MOVE_FLOW_UNUSE_ROW_UP_P_LIMIT_POS_CHECK:
			for (i = 0; i < m_nFirstUseRowIndex; i++)
			{
				if (m_bLimitSignal_L[i] == FALSE && SharedInfo::AxisPLimitSignal[m_eRemoteAxisPitch_L[i]])
				{
					m_bLimitSignal_L[i] = TRUE;
					SharedInfo::GetAutoSpeed((enum_Axis)(AXIS_GRIPPER_PITCH_L1 + i), &dVel, &dAccel, &dDecel);
					Devs::MotionIf.AxisMoveStop(m_eRemoteAxisPitch_L[i], dDecel * 2);

					Str.Format(_T("Pitch L%d P Limit Detect. AxisMoveStop"), i + 1);
					Total_Msg(Str);
				}
				if (m_bLimitSignal_R[i] == FALSE && SharedInfo::AxisPLimitSignal[m_eRemoteAxisPitch_R[i]])
				{
					m_bLimitSignal_R[i] = TRUE;
					SharedInfo::GetAutoSpeed((enum_Axis)(AXIS_GRIPPER_PITCH_L1 + i), &dVel, &dAccel, &dDecel);
					Devs::MotionIf.AxisMoveStop(m_eRemoteAxisPitch_R[i], dDecel * 2);

					Str.Format(_T("Pitch R%d P Limit Detect. AxisMoveStop"), i + 1);
					Total_Msg(Str);
				}
			}

			if (m_nCurAxisRowIndex < m_nFirstUseRowIndex - 1)
			{
				m_nCurAxisRowIndex++;

				Sleep(1000); //!!
				SetStep(_ePITCH_WORK_POS_MOVE_FLOW_UNUSE_ROW_UP_P_LIMIT_POS, _T("_ePITCH_WORK_POS_MOVE_FLOW_UNUSE_ROW_UP_P_LIMIT_POS"));
			}
			else
			{
				bResult = TRUE;
				for (i = 0; i < m_nFirstUseRowIndex; i++)
				{
					if (m_bLimitSignal_L[i] == FALSE || m_bLimitSignal_R[i] == FALSE)
					{
						bResult = FALSE;
						break;
					}
				}
				if (bResult == TRUE)
				{
					if (m_nLastUseRowIndex < eGRIPPER_ROW_MAX - 1)
					{
						m_nCurAxisRowIndex = eGRIPPER_ROW_MAX - 1;
						SetStep(_ePITCH_WORK_POS_MOVE_FLOW_UNUSE_ROW_DOWN_N_LIMIT_POS, _T("_ePITCH_WORK_POS_MOVE_FLOW_UNUSE_ROW_DOWN_N_LIMIT_POS"));
					}
					else
					{
						m_nCurAxisRowIndex = 0;
						SetStep(_ePITCH_WORK_POS_MOVE_FLOW_USE_ROW_WORK_POS, _T("_ePITCH_WORK_POS_MOVE_FLOW_USE_ROW_WORK_POS"));
					}
				}
				else if (IsTimeOut())
				{
					SetStep(_ePITCH_WORK_POS_MOVE_FLOW_ERROR, _T("_ePITCH_WORK_POS_MOVE_FLOW_ERROR"));
				}
				else
				{
					SetCheckStep(_ePITCH_WORK_POS_MOVE_FLOW_UNUSE_ROW_UP_P_LIMIT_POS_CHECK, _T("_ePITCH_WORK_POS_MOVE_FLOW_UNUSE_ROW_UP_P_LIMIT_POS_CHECK"));
				}
			}
			break;

		case _ePITCH_WORK_POS_MOVE_FLOW_UNUSE_ROW_DOWN_N_LIMIT_POS:
			m_bLimitSignal_L[m_nCurAxisRowIndex] = FALSE;
			m_bLimitSignal_R[m_nCurAxisRowIndex] = FALSE;

			SharedInfo::GetAutoSpeed((enum_Axis)(AXIS_GRIPPER_PITCH_L1 + m_nCurAxisRowIndex), &dVel, &dAccel, &dDecel);
			Devs::MotionIf.AxisVelMove(m_eRemoteAxisPitch_L[m_nCurAxisRowIndex], -dVel, dAccel, dDecel);
			Sleep(30); //!!
			SharedInfo::GetAutoSpeed((enum_Axis)(AXIS_GRIPPER_PITCH_R1 + m_nCurAxisRowIndex), &dVel, &dAccel, &dDecel);
			Devs::MotionIf.AxisVelMove(m_eRemoteAxisPitch_R[m_nCurAxisRowIndex], -dVel, dAccel, dDecel);

			SetStep(_ePITCH_WORK_POS_MOVE_FLOW_UNUSE_ROW_DOWN_N_LIMIT_POS_CHECK, _T("_ePITCH_WORK_POS_MOVE_FLOW_UNUSE_ROW_DOWN_N_LIMIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _ePITCH_WORK_POS_MOVE_FLOW_UNUSE_ROW_DOWN_N_LIMIT_POS_CHECK:
			for (i = eGRIPPER_ROW_MAX - 1; i >= m_nFirstUseRowIndex; i--)
			{
				if (m_bLimitSignal_L[i] == FALSE && SharedInfo::AxisNLimitSignal[m_eRemoteAxisPitch_L[i]])
				{
					m_bLimitSignal_L[i] = TRUE;
					SharedInfo::GetAutoSpeed((enum_Axis)(AXIS_GRIPPER_PITCH_L1 + i), &dVel, &dAccel, &dDecel);
					Devs::MotionIf.AxisMoveStop(m_eRemoteAxisPitch_L[i], dDecel * 2);

					Str.Format(_T("Pitch L%d N Limit Detect. AxisMoveStop"), i + 1);
					Total_Msg(Str);
				}
				if (m_bLimitSignal_R[i] == FALSE && SharedInfo::AxisNLimitSignal[m_eRemoteAxisPitch_R[i]])
				{
					m_bLimitSignal_R[i] = TRUE;
					SharedInfo::GetAutoSpeed((enum_Axis)(AXIS_GRIPPER_PITCH_L1 + i), &dVel, &dAccel, &dDecel);
					Devs::MotionIf.AxisMoveStop(m_eRemoteAxisPitch_R[i], dDecel * 2);

					Str.Format(_T("Pitch R%d N Limit Detect. AxisMoveStop"), i + 1);
					Total_Msg(Str);
				}
			}

			if (m_nCurAxisRowIndex > m_nFirstUseRowIndex)
			{
				m_nCurAxisRowIndex--;

				Sleep(1000); //!!
				SetStep(_ePITCH_WORK_POS_MOVE_FLOW_UNUSE_ROW_DOWN_N_LIMIT_POS, _T("_ePITCH_WORK_POS_MOVE_FLOW_UNUSE_ROW_DOWN_N_LIMIT_POS"));
			}
			else
			{
				bResult = TRUE;
				for (i = eGRIPPER_ROW_MAX - 1; i >= m_nFirstUseRowIndex; i--)
				{
					if (m_bLimitSignal_L[i] == FALSE || m_bLimitSignal_R[i] == FALSE)
					{
						bResult = FALSE;
						break;
					}
				}
				if (bResult == TRUE)
				{
					m_nCurAxisRowIndex = 0;
					SetStep(_ePITCH_WORK_POS_MOVE_FLOW_USE_ROW_WORK_POS, _T("_ePITCH_WORK_POS_MOVE_FLOW_USE_ROW_WORK_POS"));
				}
				else if (IsTimeOut())
				{
					SetStep(_ePITCH_WORK_POS_MOVE_FLOW_ERROR, _T("_ePITCH_WORK_POS_MOVE_FLOW_ERROR"));
				}
				else
				{
					SetCheckStep(_ePITCH_WORK_POS_MOVE_FLOW_UNUSE_ROW_DOWN_N_LIMIT_POS_CHECK, _T("_ePITCH_WORK_POS_MOVE_FLOW_UNUSE_ROW_DOWN_N_LIMIT_POS_CHECK"));
				}
			}
			break;

		case _ePITCH_WORK_POS_MOVE_FLOW_USE_ROW_WORK_POS:
			nWingIndex = 0;
			for (i = 0; i < eGRIPPER_ROW_MAX; i++)
			{
				if (CModelData::m_StretchPara.Info.bStretchUse[i] == TRUE)
				{
					dWorkPos_L[i] = CModelData::m_MaterialPara.Info.dStickWingCenterYOffset[nWingIndex];
					Devs::m_PitchMotion.PitchPosMove((enum_Axis)(AXIS_GRIPPER_PITCH_L1 + i), dWorkPos_L[i]);
					Sleep(30); //!!
					dWorkPos_R[i] = CModelData::m_MaterialPara.Info.dStickWingCenterYOffset[nWingIndex];
					Devs::m_PitchMotion.PitchPosMove((enum_Axis)(AXIS_GRIPPER_PITCH_R1 + i), dWorkPos_R[i]);
					
					Str.Format(_T("Pitch L%d, R%d Safe Pos Move(L%d:%.5f, R%d:%.5f)"), i + 1, i + 1, i + 1, dWorkPos_L[i], i + 1, dWorkPos_R[i]);
					Total_Msg(Str);
					Sleep(1000); //!!

					nWingIndex++;
				}	
			}
			SetStep(_ePITCH_WORK_POS_MOVE_FLOW_USE_ROW_WORK_POS_CHECK, _T("_ePITCH_WORK_POS_MOVE_FLOW_USE_ROW_WORK_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case _ePITCH_WORK_POS_MOVE_FLOW_USE_ROW_WORK_POS_CHECK:
			bResult = TRUE;
			for (i = 0; i < eGRIPPER_ROW_MAX; i++)
			{
				if (CModelData::m_StretchPara.Info.bStretchUse[i] == TRUE)
				{
					if (Devs::m_PitchMotion.IsPitchPosMove((enum_Axis)(AXIS_GRIPPER_PITCH_L1 + i), dWorkPos_L[i]) == FALSE ||
						Devs::m_PitchMotion.IsPitchPosMove((enum_Axis)(AXIS_GRIPPER_PITCH_R1 + i), dWorkPos_R[i]) == FALSE)
					{
						bResult = FALSE;
						break;
					}
				}
			}
			if (bResult)
			{
				SetStep(_ePITCH_WORK_POS_MOVE_FLOW_DONE, _T("_ePITCH_WORK_POS_MOVE_FLOW_DONE"));
			}
			else if (IsTimeOut())
			{
				SetStep(_ePITCH_WORK_POS_MOVE_FLOW_ERROR, _T("_ePITCH_WORK_POS_MOVE_FLOW_ERROR"));
			}
			else
			{
				SetCheckStep(_ePITCH_WORK_POS_MOVE_FLOW_USE_ROW_WORK_POS_CHECK, _T("_ePITCH_WORK_POS_MOVE_FLOW_USE_ROW_WORK_POS_CHECK"));
			}
			break;
		
		case _ePITCH_WORK_POS_MOVE_FLOW_STOP:
			break;

		case _ePITCH_WORK_POS_MOVE_FLOW_ERROR:
			break;

		case _ePITCH_WORK_POS_MOVE_FLOW_DONE:
		{
			m_bFlowDone = TRUE;
			break;
		}
		
		default:
			break;
		}

		Sleep(100); //!!
	}
}

BOOL CPitchWorkPosMoveFlow::FlowInterlock()
{
	CString Str = _T("");

#ifndef SIM_MODE
	if (Devs::m_ClampMotion.Is_ClampOff_All() == FALSE)
	{
		Total_Msg(_T("Check Clamp Off Staus!!!"));
		return FALSE;
	}
	if (Devs::m_StretchMotion.Is_Stretch_BwdPos_All() == FALSE)
	{
		Total_Msg(_T("Check Stretch Backward Staus!!!"));
		return FALSE;
	}
#endif

	return TRUE;
}