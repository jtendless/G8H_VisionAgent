#include "stdafx.h"
#include "GripperZMotion.h"
#include "Vision/Devs.h"
#include "Vision/SharedInfo.h"
#include "CalcAlign/CalcAlign.h"
#include "Log/Logger.h"
#include "Data/ManualData.h"

CGripperZMotion::CGripperZMotion()
{
}


CGripperZMotion::~CGripperZMotion()
{
}

BOOL CGripperZMotion::InitProcess()
{
	m_StateComplete = NULL;
	m_StateFinish = TRUE;
	m_bMotionDone = FALSE;
	//m_bTerminate = FALSE;

	hMotionHandle = CreateEvent(NULL, TRUE, FALSE, NULL);
	SetHandle(hMotionHandle);
	pMotionThread = AfxBeginThread(MotionThreadFunction, this, THREAD_PRIORITY_ABOVE_NORMAL);

	//SetProcessLog(Process_Msg);
	//SetAlarmLog(LogMsg_Alarm);

	m_bStopBit = FALSE;	             SharedInfo::bMachineStopFlag = FALSE;

	return TRUE;
}

BOOL CGripperZMotion::EndProcess()
{
	int i = 0;

	m_StateFinish = FALSE;

	SetStep(eGRIPPER_Z_MOTION_IDLE, FALSE);

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

BOOL CGripperZMotion::Stop()
{
	m_bStopBit = TRUE;
	SetStop(); //!!
	return TRUE;
}

BOOL CGripperZMotion::ResetStopBit()
{
	SharedInfo::bMachineStopFlag = FALSE;
	m_bStopBit = FALSE;
	return TRUE;
}

UINT CGripperZMotion::MotionThreadFunction(LPVOID lpParam)
{
	CGripperZMotion* pGripperZMotion = NULL;

	pGripperZMotion = (CGripperZMotion*)lpParam;

	pGripperZMotion->MotionThreadFunctionEntry();

	pGripperZMotion->m_bTerminate = 1;

	return 0;
}

VOID CGripperZMotion::MotionThreadFunctionEntry(VOID)
{
	int ErrorCheck = 0;
	CString szMsg;

	while (m_StateFinish)
	{
		WaitForSingleObject(hMotionHandle, INFINITE);
		ResetEvent(hMotionHandle);

		if (SharedInfo::bMachineStopFlag == TRUE)// && m_bStopBit == FALSE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(eGRIPPER_Z_MOTION_IDLE); //KJT 20210318
			continue; //!!
		}

	
		switch (GetCurrentTotalStep())
		{
		case eGRIPPER_Z_MOTION_IDLE:			
			break;

		case eGRIPPER_Z_MOTION_DONE:
			m_bMotionDone = TRUE;
			SetStep(eGRIPPER_Z_MOTION_IDLE, _T("eGRIPPER_Z_MOTION_IDLE"));
			break;

		case eGRIPPER_Z_MOTION_EXIT:
			m_StateFinish = FALSE;
			break;
		}
	}
}

BOOL CGripperZMotion::IsAxisHome(UINT nAxisNo)
{
	return SharedInfo::AxisHomeStatus[nAxisNo];
}

BOOL CGripperZMotion::MoveAxis(enum_Axis eAxis, double dPos)
{
	double	dSpeed = 0.0, dAccel = 0.0, dDecel = 0.0;

	//현재 모터의 파라미터 받아오기
	if (!GetAxisWorkParam(eAxis, &dSpeed, &dAccel, &dDecel)) return FALSE;
	//해당 모터에 파라미터 전달
	AbsMove(eAxis, dPos, dSpeed, dAccel, dDecel);
	return TRUE;
}

BOOL CGripperZMotion::IsMoveDone(enum_Axis eAxis, double dPos)
{
	double dCmdPos = SharedInfo::GetCmdPos(eAxis);
	return (IsSamePosition(dCmdPos, dPos) && IsMotionDone(eAxis));
}

//Move

BOOL CGripperZMotion::Move_GripperLeftZ_WaitPos()
{
	CString Str = _T("");

#ifndef GRIPPER_0
	enum_Axis eAxis = AXIS_GRIPPER_ZL;
#else
	enum_Axis eAxis = AXIS_NONE;
#endif

	double dPos = CManualData::m_ManualDataGripperZ.Info.m_dGripperLeftZ_WaitPos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Gripper Left Z Move To Wait Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}
	
	return bRtn;
}
BOOL CGripperZMotion::Move_GripperLeftZ_LoadingPos()
{
	CString Str = _T("");
#ifndef GRIPPER_0
	enum_Axis eAxis = AXIS_GRIPPER_ZL;
#else
	enum_Axis eAxis = AXIS_NONE;
#endif
	double dPos = CManualData::m_ManualDataGripperZ.Info.m_dGripperLeftZ_LoadingPos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Gripper Left Z Move To Loading Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
BOOL CGripperZMotion::Move_GripperLeftZ_ClampPos()
{
	CString Str = _T("");
#ifndef GRIPPER_0
	enum_Axis eAxis = AXIS_GRIPPER_ZL;
#else
	enum_Axis eAxis = AXIS_NONE;
#endif
	double dPos = CManualData::m_ManualDataGripperZ.Info.m_dGripperLeftZ_ClampPos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Gripper Left Z Move To Clamp Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
BOOL CGripperZMotion::Move_GripperLeftZ_TensionPos()
{
	CString Str = _T("");
#ifndef GRIPPER_0
	enum_Axis eAxis = AXIS_GRIPPER_ZL;
#else
	enum_Axis eAxis = AXIS_NONE;
#endif
	double dPos = CManualData::m_ManualDataGripperZ.Info.m_dGripperLeftZ_TensionPos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Gripper Left Z Move To Tension Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
BOOL CGripperZMotion::Move_GripperLeftZ_UnclampPos()
{
	CString Str = _T("");
#ifndef GRIPPER_0
	enum_Axis eAxis = AXIS_GRIPPER_ZL;
#else
	enum_Axis eAxis = AXIS_NONE;
#endif
	double dPos = CManualData::m_ManualDataGripperZ.Info.m_dGripperLeftZ_UnclampPos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Gripper Left Z Move To Unclamp Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}
	return bRtn;
}
//Move Done Check
BOOL CGripperZMotion::Is_GripperLeftZ_WaitPos()
{
#ifndef GRIPPER_0
	enum_Axis eAxis = AXIS_GRIPPER_ZL;
#else
	enum_Axis eAxis = AXIS_NONE;
#endif
	double dPos = CManualData::m_ManualDataGripperZ.Info.m_dGripperLeftZ_WaitPos;
	return IsMoveDone(eAxis, dPos);
}
BOOL CGripperZMotion::Is_GripperLeftZ_LoadingPos()
{
#ifndef GRIPPER_0
	enum_Axis eAxis = AXIS_GRIPPER_ZL;
#else
	enum_Axis eAxis = AXIS_NONE;
#endif
	double dPos = CManualData::m_ManualDataGripperZ.Info.m_dGripperLeftZ_LoadingPos;
	return IsMoveDone(eAxis, dPos);
}
BOOL CGripperZMotion::Is_GripperLeftZ_ClampPos()
{
#ifndef GRIPPER_0
	enum_Axis eAxis = AXIS_GRIPPER_ZL;
#else
	enum_Axis eAxis = AXIS_NONE;
#endif
	double dPos = CManualData::m_ManualDataGripperZ.Info.m_dGripperLeftZ_ClampPos;
	return IsMoveDone(eAxis, dPos);
}
BOOL CGripperZMotion::Is_GripperLeftZ_TensionPos()
{
#ifndef GRIPPER_0
	enum_Axis eAxis = AXIS_GRIPPER_ZL;
#else
	enum_Axis eAxis = AXIS_NONE;
#endif
	double dPos = CManualData::m_ManualDataGripperZ.Info.m_dGripperLeftZ_TensionPos;
	return IsMoveDone(eAxis, dPos);
}
BOOL CGripperZMotion::Is_GripperLeftZ_UnclampPos()
{
#ifndef GRIPPER_0
	enum_Axis eAxis = AXIS_GRIPPER_ZL;
#else
	enum_Axis eAxis = AXIS_NONE;
#endif
	double dPos = CManualData::m_ManualDataGripperZ.Info.m_dGripperLeftZ_UnclampPos;
	return IsMoveDone(eAxis, dPos);
}

BOOL CGripperZMotion::Move_GripperRightZ_WaitPos()
{
	CString Str = _T("");
#ifndef GRIPPER_0
	enum_Axis eAxis = AXIS_GRIPPER_ZR;
#else
	enum_Axis eAxis = AXIS_NONE;
#endif
	double dPos = CManualData::m_ManualDataGripperZ.Info.m_dGripperRightZ_WaitPos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Gripper Right Z Move To Wait Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
BOOL CGripperZMotion::Move_GripperRightZ_LoadingPos()
{
	CString Str = _T("");
#ifndef GRIPPER_0
	enum_Axis eAxis = AXIS_GRIPPER_ZR;
#else
	enum_Axis eAxis = AXIS_NONE;
#endif
	double dPos = CManualData::m_ManualDataGripperZ.Info.m_dGripperRightZ_LoadingPos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Gripper Right Z Move To Loading Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
BOOL CGripperZMotion::Move_GripperRightZ_ClampPos()
{
	CString Str = _T("");
#ifndef GRIPPER_0
	enum_Axis eAxis = AXIS_GRIPPER_ZR;
#else
	enum_Axis eAxis = AXIS_NONE;
#endif
	double dPos = CManualData::m_ManualDataGripperZ.Info.m_dGripperRightZ_ClampPos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Gripper Right Z Move To Clamp Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
BOOL CGripperZMotion::Move_GripperRightZ_TensionPos()
{
	CString Str = _T("");
#ifndef GRIPPER_0
	enum_Axis eAxis = AXIS_GRIPPER_ZR;
#else
	enum_Axis eAxis = AXIS_NONE;
#endif
	double dPos = CManualData::m_ManualDataGripperZ.Info.m_dGripperRightZ_TensionPos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Gripper Right Z Move To Tension Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
BOOL CGripperZMotion::Move_GripperRightZ_UnclampPos()
{
	CString Str = _T("");
#ifndef GRIPPER_0
	enum_Axis eAxis = AXIS_GRIPPER_ZR;
#else
	enum_Axis eAxis = AXIS_NONE;
#endif
	double dPos = CManualData::m_ManualDataGripperZ.Info.m_dGripperRightZ_UnclampPos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Gripper Right Z Move To Unclamp Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}
	return bRtn;
}

//Move Done Check
BOOL CGripperZMotion::Is_GripperRightZ_WaitPos()
{
#ifndef GRIPPER_0
	enum_Axis eAxis = AXIS_GRIPPER_ZR;
#else
	enum_Axis eAxis = AXIS_NONE;
#endif
	double dPos = CManualData::m_ManualDataGripperZ.Info.m_dGripperRightZ_WaitPos;
	return IsMoveDone(eAxis, dPos);
}
BOOL CGripperZMotion::Is_GripperRightZ_LoadingPos()
{
#ifndef GRIPPER_0
	enum_Axis eAxis = AXIS_GRIPPER_ZR;
#else
	enum_Axis eAxis = AXIS_NONE;
#endif
	double dPos = CManualData::m_ManualDataGripperZ.Info.m_dGripperRightZ_LoadingPos;
	return IsMoveDone(eAxis, dPos);
}
BOOL CGripperZMotion::Is_GripperRightZ_ClampPos()
{
#ifndef GRIPPER_0
	enum_Axis eAxis = AXIS_GRIPPER_ZR;
#else
	enum_Axis eAxis = AXIS_NONE;
#endif
	double dPos = CManualData::m_ManualDataGripperZ.Info.m_dGripperRightZ_ClampPos;
	return IsMoveDone(eAxis, dPos);
}
BOOL CGripperZMotion::Is_GripperRightZ_TensionPos()
{
#ifndef GRIPPER_0
	enum_Axis eAxis = AXIS_GRIPPER_ZR;
#else
	enum_Axis eAxis = AXIS_NONE;
#endif
	double dPos = CManualData::m_ManualDataGripperZ.Info.m_dGripperRightZ_TensionPos;
	return IsMoveDone(eAxis, dPos);
}
BOOL CGripperZMotion::Is_GripperRightZ_UnclampPos()
{
#ifndef GRIPPER_0
	enum_Axis eAxis = AXIS_GRIPPER_ZR;
#else
	enum_Axis eAxis = AXIS_NONE;
#endif
	double dPos = CManualData::m_ManualDataGripperZ.Info.m_dGripperRightZ_UnclampPos;
	return IsMoveDone(eAxis, dPos);
}