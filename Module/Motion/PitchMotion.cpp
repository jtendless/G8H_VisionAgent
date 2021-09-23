#include "stdafx.h"
#include "PitchMotion.h"
#include "Vision/Devs.h"
#include "Vision/SharedInfo.h"
#include "CalcAlign/CalcAlign.h"
#include "Log/Logger.h"
#include "Data/ManualData.h"
#include "Data/ModelData.h"
#include "Data/MachineData.h"

CPitchMotion::CPitchMotion()
{
}


CPitchMotion::~CPitchMotion()
{
}

BOOL CPitchMotion::InitProcess()
{
	//m_bTerminate = FALSE;
	m_StateFinish = TRUE;
	
	//SetProcessLog(Process_Msg);
	//SetAlarmLog(LogMsg_Alarm);

	hMotionHandle = CreateEvent(NULL, TRUE, FALSE, NULL);
	SetHandle(hMotionHandle);
	pMotionThread = AfxBeginThread(MotionThreadFunction, this);// , THREAD_PRIORITY_ABOVE_NORMAL);

	return TRUE;
}

BOOL CPitchMotion::EndProcess()
{
	int i = 0;

	m_StateFinish = FALSE;

	SetStep(ePITCH_MOTION_IDLE, FALSE);

	if (hMotionHandle != NULL)
	{
		CloseHandle(hMotionHandle);
		hMotionHandle = NULL;
	}
#if 0
	do
	{
		Sleep(10);
	} while (m_bTerminate == 0);
#endif
	//delete this;

	return TRUE;
}

BOOL CPitchMotion::Stop()
{
	m_bStopBit = TRUE;
	SetStop(); //!!
	return TRUE;
}

BOOL CPitchMotion::ResetStopBit()
{
	SharedInfo::bMachineStopFlag = FALSE;
	m_bStopBit = FALSE;
	return TRUE;
}

UINT CPitchMotion::MotionThreadFunction(LPVOID lpParam)
{
	CPitchMotion* pPitchMotion = NULL;

	pPitchMotion = (CPitchMotion*)lpParam;

	pPitchMotion->MotionThreadFunctionEntry();

	pPitchMotion->m_bTerminate = 1;

	return 0;
}

VOID CPitchMotion::MotionThreadFunctionEntry(VOID)
{
	int ErrorCheck = 0;
	CString szMsg;
	BOOL bResult;
	int nWaitPosCnt = 0;

	while (m_StateFinish)
	{
		WaitForSingleObject(hMotionHandle, INFINITE);
		ResetEvent(hMotionHandle);

		if (SharedInfo::bMachineStopFlag == TRUE && m_bStopBit == FALSE)
		{
			m_bStopBit = TRUE;
			continue; //!!
		}

		if (SharedInfo::bMachineStopFlag == TRUE)
			continue;

		switch (GetCurrentTotalStep())
		{
		case ePITCH_MOTION_IDLE:
			break;

		case ePITCH_MOTION_START:
			SetStep(ePITCH_MOTION_DONE, _T("ePITCH_MOTION_DONE"));
			break;

		case ePITCH_MOTION_DONE:
			m_bMotionDone = TRUE;
			SetStep(ePITCH_MOTION_IDLE, _T("ePITCH_MOTION_IDLE"));
			break;

		case ePITCH_MOTION_EXIT:
			m_StateFinish = FALSE;
			break;
		}
	}
}

BOOL CPitchMotion::IsAxisHome(UINT nAxisNo)
{
	return SharedInfo::AxisHomeStatus[nAxisNo];
}

BOOL CPitchMotion::MoveAxis(enum_Axis eAxis, double dPos)
{
	double	dSpeed = 0.0, dAccel = 0.0, dDecel = 0.0;

	//현재 모터의 파라미터 받아오기
	if (!GetAxisWorkParam(eAxis, &dSpeed, &dAccel, &dDecel)) return FALSE;
	//해당 모터에 파라미터 전달
	AbsMove(eAxis, dPos, dSpeed, dAccel, dDecel);
	return TRUE;
}
BOOL CPitchMotion::IsMoveDone(enum_Axis eAxis, double dPos)
{
	double dCmdPos = SharedInfo::GetCmdPos(eAxis);
	return (IsSamePosition(dCmdPos, dPos) && IsMotionDone(eAxis));
}

#pragma region //Pitch MovePos
//MovePos
BOOL CPitchMotion::PitchLeft_WaitPos(enum_Axis eAxis)
{
#pragma region //Interlock
	if (Devs::m_ClampMotion.Is_ClampOff_All() == FALSE)
	{
		Total_Msg(_T("Check Clamp Off !!!"));
		return FALSE;
	}
#pragma endregion

	CString Str = _T("");
	double dPos = CManualData::m_ManualDataPitch.Info.m_dPitchLeft_WaitPos[eAxis - AXIS_GRIPPER_PITCH_L1];
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("%s Move To Pos (Wait Pos : %.5f)"), SharedInfo::GetAxisName(eAxis), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}

BOOL CPitchMotion::PitchRight_WaitPos(enum_Axis eAxis)
{
#pragma region //Interlock
	if (Devs::m_ClampMotion.Is_ClampOff_All() == FALSE)
	{
		Total_Msg(_T("Check Clamp Off !!!"));
		return FALSE;
	}
#pragma endregion

	CString Str = _T("");
	double dPos = CManualData::m_ManualDataPitch.Info.m_dPitchRight_WaitPos[eAxis - AXIS_GRIPPER_PITCH_R1];
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("%s Move To Wait Pos (Wait Pos : %.5f)"), SharedInfo::GetAxisName(eAxis), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
BOOL CPitchMotion::Pitch_WaitPos(enum_eGRIPPER_ROW eRow)
{
	CString Str = _T("");
	double dPosLeft = CManualData::m_ManualDataPitch.Info.m_dPitchLeft_WaitPos[eRow];
	double dPosRight = CManualData::m_ManualDataPitch.Info.m_dPitchRight_WaitPos[eRow];
	enum_Axis ePitchLeft = (enum_Axis)(AXIS_GRIPPER_PITCH_L1 + eRow);
	enum_Axis ePitchRight = (enum_Axis)(AXIS_GRIPPER_PITCH_R1 + eRow);

	BOOL bRtnL = MoveAxis(ePitchLeft, dPosLeft);
	if (bRtnL == TRUE)
	{
		Str.Format(_T("%s Move To Pos (Wait Pos : %.5f)"), SharedInfo::GetAxisName(ePitchLeft), dPosLeft);
		Total_Msg(Str);
	}
	BOOL bRtnR = MoveAxis(ePitchRight, dPosRight);
	if (bRtnR == TRUE)
	{
		Str.Format(_T("%s Move To Pos (Wait Pos : %.5f)"), SharedInfo::GetAxisName(ePitchRight), dPosRight);
		Total_Msg(Str);
	}

	return (bRtnL && bRtnR);
}
BOOL CPitchMotion::Pitch_WaitPos_All()
{
	double dPosLeft = 0.0, dPosRight = 0.0;
	enum_Axis ePitchLeft = AXIS_NONE, ePitchRight = AXIS_NONE;
	BOOL bRtnL = FALSE, bRtnR = FALSE, bResult = TRUE;
	int i = 0;

	Total_Msg(_T("Pitch All Wait Pos Move"));
	for (i = eGRIPPER_ROW_MAX - 1; i >= 0; i--)
	{
		dPosLeft = CManualData::m_ManualDataPitch.Info.m_dPitchLeft_WaitPos[i];
		dPosRight = CManualData::m_ManualDataPitch.Info.m_dPitchRight_WaitPos[i];
		ePitchLeft = (enum_Axis)(AXIS_GRIPPER_PITCH_L1 + i);
		ePitchRight = (enum_Axis)(AXIS_GRIPPER_PITCH_R1 + i);

		bRtnL = MoveAxis(ePitchLeft, dPosLeft);
		if (bRtnL == TRUE)
		{
			CString Str = SharedInfo::GetAxisName(ePitchLeft);
			Total_Msg(_T("%s Move To Wait Pos (Wait Pos : %.5f)"), Str, dPosLeft);
		}
		Sleep(20);

		bRtnR = MoveAxis(ePitchRight, dPosRight);
		if (bRtnR == TRUE)
		{
			CString Str = SharedInfo::GetAxisName(ePitchRight);
			Total_Msg(_T("%s Move To Wait Pos (Wait Pos : %.5f)"), Str, dPosRight);
		}

		if (bRtnL == FALSE || bRtnR == FALSE)
		{
			bResult = FALSE;
			break;
		}

		Sleep(1000); //!!!
	}

	return bResult;
}
//MoveDone Pos
BOOL CPitchMotion::Is_PitchLeft_WaitPos(enum_Axis eAxis)
{
	double dPos = CManualData::m_ManualDataPitch.Info.m_dPitchLeft_WaitPos[eAxis - AXIS_GRIPPER_PITCH_L1];
	return IsMoveDone(eAxis, dPos);
}

BOOL CPitchMotion::Is_PitchRight_WaitPos(enum_Axis eAxis)
{
	double dPos = CManualData::m_ManualDataPitch.Info.m_dPitchRight_WaitPos[eAxis - AXIS_GRIPPER_PITCH_R1];
	return IsMoveDone(eAxis, dPos);
}
//한쌍으로 Move
BOOL CPitchMotion::Is_Pitch_WaitPos(int nRowIndex)
{
	double dPosLeft = CManualData::m_ManualDataPitch.Info.m_dPitchLeft_WaitPos[nRowIndex];
	double dPosRight = CManualData::m_ManualDataPitch.Info.m_dPitchRight_WaitPos[nRowIndex];
	enum_Axis ePitchLeft = (enum_Axis)(AXIS_GRIPPER_PITCH_L1 + nRowIndex);
	enum_Axis ePitchRight = (enum_Axis)(AXIS_GRIPPER_PITCH_R1 + nRowIndex);

	BOOL bRtnL = IsMoveDone(ePitchLeft, dPosLeft);
	BOOL bRtnR = IsMoveDone(ePitchRight, dPosRight);

	return (bRtnL && bRtnR);
}
BOOL CPitchMotion::Is_Pitch_WaitPos_All()
{
	double dPosLeft = 0.0, dPosRight = 0.0;
	enum_Axis ePitchLeft = AXIS_NONE, ePitchRight = AXIS_NONE;
	BOOL bRtnL = FALSE, bRtnR = FALSE, bResult = TRUE;
	int i = 0;
	for (i = 0; i < eGRIPPER_ROW_MAX; i++)
	{
		dPosLeft = CManualData::m_ManualDataPitch.Info.m_dPitchLeft_WaitPos[i];
		dPosRight = CManualData::m_ManualDataPitch.Info.m_dPitchRight_WaitPos[i];
		ePitchLeft = (enum_Axis)(AXIS_GRIPPER_PITCH_L1 + i);
		ePitchRight = (enum_Axis)(AXIS_GRIPPER_PITCH_R1 + i);

		bRtnL = IsMoveDone(ePitchLeft, dPosLeft);
		bRtnR = IsMoveDone(ePitchRight, dPosRight);

		if (bRtnL == FALSE || bRtnR == FALSE)
		{
			bResult = FALSE;
			break;
		}
	}

	return bResult;
}
#pragma endregion

#pragma region //Pitch Tension
BOOL CPitchMotion::PitchTensionMove_L(double dOffset) //Change to MotionAgent !!
{
	CString Str = _T("");
	double	dSpeed = 0.0, dAccel = 0.0, dDecel = 0.0;
	enum_Axis eAxis = AXIS_NONE;

	for (int i = 0; i < eGRIPPER_ROW_MAX; i++)
	{
		if (CModelData::m_StretchPara.Info.bStretchUse[i])
		{
			eAxis = (enum_Axis)(AXIS_GRIPPER_PITCH_L1 + i);
			m_dPitchTargetPos_L[i] = SharedInfo::GetCmdPos(eAxis) - dOffset;

			if (!GetAxisWorkParam(eAxis, &dSpeed, &dAccel, &dDecel)) return FALSE;

			AbsMove(eAxis, m_dPitchTargetPos_L[i], dSpeed, dAccel, dDecel);
			Sleep(10);

			Str.Format(_T("Tension Pitch L%d Move To %.5f (Dist:%.5f)"), i + 1, m_dPitchTargetPos_L[i], dOffset * (-1));
			Total_Msg(Str);
		}
	}
}
BOOL CPitchMotion::Is_PitchTensionMove_L()
{
	enum_Axis eAxis = AXIS_NONE;

	for (int i = 0; i < eGRIPPER_ROW_MAX; i++)
	{
		if (CModelData::m_StretchPara.Info.bStretchUse[i])
		{
			eAxis = (enum_Axis)(AXIS_GRIPPER_PITCH_L1 + i);

			if (IsMoveDone(eAxis, m_dPitchTargetPos_L[i]) == FALSE)
				return FALSE;
		}
	}

	return TRUE;
}
BOOL CPitchMotion::PitchTensionMove_R(double dOffset) //Change to MotionAgent !!
{
	CString Str = _T("");
	double	dSpeed = 0.0, dAccel = 0.0, dDecel = 0.0;
	enum_Axis eAxis = AXIS_NONE;

	for (int i = 0; i < eGRIPPER_ROW_MAX; i++)
	{
		if (CModelData::m_StretchPara.Info.bStretchUse[i])
		{
			eAxis = (enum_Axis)(AXIS_GRIPPER_PITCH_R1 + i);
			m_dPitchTargetPos_R[i] = SharedInfo::GetCmdPos(eAxis) - dOffset;

			if (!GetAxisWorkParam(eAxis, &dSpeed, &dAccel, &dDecel)) return FALSE;

			AbsMove(eAxis, m_dPitchTargetPos_R[i], dSpeed, dAccel, dDecel);
			Sleep(10);

			Str.Format(_T("Tension Pitch R%d Move To %.5f (Dist:%.5f)"), i + 1, m_dPitchTargetPos_R[i], dOffset * (-1));
			Total_Msg(Str);
		}
	}
}
BOOL CPitchMotion::Is_PitchTensionMove_R()
{
	enum_Axis eAxis = AXIS_NONE;

	for (int i = 0; i < eGRIPPER_ROW_MAX; i++)
	{
		if (CModelData::m_StretchPara.Info.bStretchUse[i])
		{
			eAxis = (enum_Axis)(AXIS_GRIPPER_PITCH_R1 + i);

			if (IsMoveDone(eAxis, m_dPitchTargetPos_R[i]) == FALSE)
				return FALSE;
		}
	}

	return TRUE;
}

BOOL CPitchMotion::Move_PitchTensionPos(int nAxisIndex, int nAxisNo[MAX_STRETCH_AXIS_SIZE], double dTargetPos[MAX_STRETCH_AXIS_SIZE])
{
	double dVel = 1.0; //!!

	Devs::MotionIf.PitchPosMove(nAxisIndex, nAxisNo, dTargetPos, dVel);
	return TRUE;
}
BOOL CPitchMotion::Is_PitchTensionPos(int nAxisIndex, int nAxisNo[MAX_STRETCH_AXIS_SIZE], double dTargetPos[MAX_STRETCH_AXIS_SIZE])
{
	enum_Axis eAxis = AXIS_NONE;

	for (int i = 0; i < eGRIPPER_ROW_MAX; i++)
	{
		if (CModelData::m_StretchPara.Info.bStretchUse[i])
		{
			eAxis = (enum_Axis)(AXIS_GRIPPER_PITCH_L1 + i);

			if (IsMoveDone(eAxis, m_dPitchTargetPos[i]) == FALSE)
				return FALSE;

			eAxis = (enum_Axis)(AXIS_GRIPPER_PITCH_R1 + i);
			if (IsMoveDone(eAxis, m_dPitchTargetPos[i + eGRIPPER_ROW_MAX]) == FALSE)
				return FALSE;
		}
	}

	return TRUE;
}

BOOL CPitchMotion::Gripper2PAlignTensionPitchMoveStart(double dDiffY1, double dDiffY2)
{
	CString Str = _T("");
	double dValueL = 0.0, dValueR = 0.0;

	m_nAxisIndex = 0;
	for (int i = 0; i < MAX_STRETCH_SIZE; i++)
	{
		m_nAxisNo[i] = REMOTE_AXIS_AJIN_GRIPPER_PITCH_L1 + i;
		m_nAxisNo[i + eGRIPPER_ROW_MAX] = REMOTE_AXIS_AJIN_GRIPPER_PITCH_R1 + i;

		m_dPitchTargetPos[i] = SharedInfo::GetCmdPos((enum_Axis)(AXIS_GRIPPER_PITCH_L1 + i));
		m_dPitchTargetPos[i + eGRIPPER_ROW_MAX] = SharedInfo::GetCmdPos((enum_Axis)(AXIS_GRIPPER_PITCH_R1 + i));

		if (CModelData::m_StretchPara.Info.bStretchUse[i])
		{
			//0:LB, 1:LT
			m_nAxisIndex = m_nAxisIndex | (1 << i);

			dValueL = dDiffY1;

			if (dValueL > 0.025) dValueL = 0.025;
			else if (dValueL < -0.025) dValueL = -0.025;

			m_dPitchTargetPos[i] -= dValueL;

			//2:RT, 3:RB
			m_nAxisIndex = m_nAxisIndex | (1 << (i + eGRIPPER_ROW_MAX));

			dValueR = dDiffY2;

			if (dValueR > 0.025) dValueR = 0.025;
			else if (dValueR < -0.025) dValueR = -0.025;

			m_dPitchTargetPos[i + eGRIPPER_ROW_MAX] -= dValueR;

			Str.Format(_T("PitchTensionMove To Pos L%d:%.5f(Diff:%.5f), R%d:%.5f(Diff:%.5f)"),
				i + 1, m_dPitchTargetPos[i], -dValueL,
				i + 1, m_dPitchTargetPos[i + eGRIPPER_ROW_MAX], -dValueR);
			Total_Msg(Str);
		}
	}

	Move_PitchTensionPos(m_nAxisIndex, m_nAxisNo, m_dPitchTargetPos);

	return TRUE;
}
BOOL CPitchMotion::Gripper2PAlignTensionPitchMoveDoneCheck()
{
	for (int i = 0; i < MAX_STRETCH_SIZE; i++)
	{
		if (CModelData::m_StretchPara.Info.bStretchUse[i])
		{
			if (IsPitchPosMove((enum_Axis)(AXIS_GRIPPER_PITCH_L1 + i), m_dPitchTargetPos[i]) == FALSE)
				return FALSE;

			if (IsPitchPosMove((enum_Axis)(AXIS_GRIPPER_PITCH_R1 + i), m_dPitchTargetPos[i + eGRIPPER_ROW_MAX]) == FALSE)
				return FALSE;
		}
	}

	return TRUE;
}
BOOL CPitchMotion::Gripper4PAlignTensionPitchMoveStart(double m_AlignPoint[2][4])
{
#if 0 //Individual Move
	CString Str = _T("");
	double dValueL = 0.0, dValueR = 0.0;

	int nMaxAlignCount = 4;
	int nAlignPointIndex_L = 0;
	int nAlignPointIndex_R = 0;

	m_nAxisIndex = 0;
	for (int i = 0; i < MAX_STRETCH_SIZE; i++)
	{
		m_nAxisNo[i] = REMOTE_AXIS_AJIN_GRIPPER_PITCH_L1 + i;
		m_nAxisNo[i + GRIPPER_ROW] = REMOTE_AXIS_AJIN_GRIPPER_PITCH_R1 + i;

		m_dPitchTargetPos[i] = SharedInfo::GetCmdPos((enum_Axis)(AXIS_GRIPPER_PITCH_L1 + i));
		m_dPitchTargetPos[i + GRIPPER_ROW] = SharedInfo::GetCmdPos((enum_Axis)(AXIS_GRIPPER_PITCH_R1 + i));

		if (CModelData::m_StretchPara.Info.bStretchUse[i])
		{
			//0:LB, 1:LT
			m_nAxisIndex = m_nAxisIndex | (1 << i);

			dValueL = m_AlignPoint[1][nAlignPointIndex_L];

			if (dValueL > 0.025) dValueL = 0.025;
			else if (dValueL < -0.025) dValueL = -0.025;

			m_dPitchTargetPos[i] -= dValueL;

			//2:RT, 3:RB
			m_nAxisIndex = m_nAxisIndex | (1 << (i + GRIPPER_ROW));

			nAlignPointIndex_R = nMaxAlignCount - 1 - nAlignPointIndex_L;
			dValueR = m_AlignPoint[1][nAlignPointIndex_R];

			if (dValueR > 0.025) dValueR = 0.025;
			else if (dValueR < -0.025) dValueR = -0.025;

			m_dPitchTargetPos[i + GRIPPER_ROW] -= dValueR;

			nAlignPointIndex_L++; //!!

			Str.Format(_T("PitchTensionMove To Pos L%d:%.5f(Diff:%.5f), R%d:%.5f(Diff:%.5f)"),
				i + 1, m_dPitchTargetPos[i], -dValueL,
				i + 1, m_dPitchTargetPos[i + GRIPPER_ROW], -dValueR);
			Total_Msg(Str);
		}
	}
#else //Couple Move
	CString Str = _T("");
	double dSumL = 0.0, dSumR = 0.0, dAvgL = 0.0, dAvgR = 0.0;
	double dValueL = 0.0, dValueR = 0.0;
	int nPitchUseCount = 0;

	int nMaxAlignCount = 4;
	int nAlignPointIndex_L = 0;
	int nAlignPointIndex_R = 0;

	m_nAxisIndex = 0;
	for (int i = 0; i < MAX_STRETCH_SIZE; i++)
	{
		m_nAxisNo[i] = REMOTE_AXIS_AJIN_GRIPPER_PITCH_L1 + i;
		m_nAxisNo[i + eGRIPPER_ROW_MAX] = REMOTE_AXIS_AJIN_GRIPPER_PITCH_R1 + i;

		m_dPitchTargetPos[i] = SharedInfo::GetCmdPos((enum_Axis)(AXIS_GRIPPER_PITCH_L1 + i));
		m_dPitchTargetPos[i + eGRIPPER_ROW_MAX] = SharedInfo::GetCmdPos((enum_Axis)(AXIS_GRIPPER_PITCH_R1 + i));

		if (CModelData::m_StretchPara.Info.bStretchUse[i])
		{
			nPitchUseCount++;

			//0:LB, 1:LT
			m_nAxisIndex = m_nAxisIndex | (1 << i);

			dSumL += m_AlignPoint[1][nAlignPointIndex_L];			

			//2:RT, 3:RB
			m_nAxisIndex = m_nAxisIndex | (1 << (i + eGRIPPER_ROW_MAX));

			nAlignPointIndex_R = nMaxAlignCount - 1 - nAlignPointIndex_L;
			
			dSumR += m_AlignPoint[1][nAlignPointIndex_R];

			nAlignPointIndex_L++; //!!
		}
	}

	dAvgL = dSumL / nPitchUseCount;
	dAvgR = dSumR / nPitchUseCount;
	
	dValueL = dAvgL;
	if (dValueL > 0.025) dValueL = 0.025;
	else if (dValueL < -0.025) dValueL = -0.025;

	dValueR = dAvgR;
	if (dValueR > 0.025) dValueR = 0.025;
	else if (dValueR < -0.025) dValueR = -0.025;

	for (int i = 0; i < MAX_STRETCH_SIZE; i++)
	{
		if (CModelData::m_StretchPara.Info.bStretchUse[i])
		{
			m_dPitchTargetPos[i] -= dValueL;
			m_dPitchTargetPos[i + eGRIPPER_ROW_MAX] -= dValueR;

			Str.Format(_T("PitchTensionMove To Pos L%d:%.5f(Diff:%.5f), R%d:%.5f(Diff:%.5f)"),
				i + 1, m_dPitchTargetPos[i], -dValueL,
				i + 1, m_dPitchTargetPos[i + eGRIPPER_ROW_MAX], -dValueR);
			Total_Msg(Str);
		}
	}
#endif	

	Move_PitchTensionPos(m_nAxisIndex, m_nAxisNo, m_dPitchTargetPos);

	return TRUE;
}
BOOL CPitchMotion::Gripper4PAlignTensionPitchMoveDoneCheck()
{
	for (int i = 0; i < MAX_STRETCH_SIZE; i++)
	{
		if (CModelData::m_StretchPara.Info.bStretchUse[i])
		{
			if (IsPitchPosMove((enum_Axis)(AXIS_GRIPPER_PITCH_L1 + i), m_dPitchTargetPos[i]) == FALSE)
				return FALSE;

			if (IsPitchPosMove((enum_Axis)(AXIS_GRIPPER_PITCH_R1 + i), m_dPitchTargetPos[i + eGRIPPER_ROW_MAX]) == FALSE)
				return FALSE;
		}
	}

	return TRUE;
}
#pragma endregion

BOOL CPitchMotion::PitchPosMove(enum_Axis eAxisNo, double dPos)
{
	double	dSpeed = 0.0, dAccel = 0.0, dDecel = 0.0;

	if (!GetAxisWorkParam(eAxisNo, &dSpeed, &dAccel, &dDecel)) return FALSE;

	AbsMove(eAxisNo, dPos, dSpeed, dAccel, dDecel);

	return TRUE;
}
BOOL CPitchMotion::IsPitchPosMove(enum_Axis eAxisNo, double dPos)
{
	double dCmdPos = SharedInfo::GetCmdPos(eAxisNo);

	return (IsSamePosition(dCmdPos, dPos) && IsMotionDone(eAxisNo));
}