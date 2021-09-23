#include "stdafx.h"
#include "StretchMotion.h"
#include "Vision/Devs.h"
#include "Vision/SharedInfo.h"
#include "CalcAlign/CalcAlign.h"
#include "Log/Logger.h"
#include "Data/ManualData.h"
#include "Data/ModelData.h"

CStretchMotion::CStretchMotion()
{
}


CStretchMotion::~CStretchMotion()
{
}

BOOL CStretchMotion::InitProcess()
{
	//m_bTerminate = FALSE;
	m_StateFinish = TRUE;

	ForceControlIndex = 0;
	
	//SetProcessLog(Process_Msg);
	//SetAlarmLog(LogMsg_Alarm);

	hMotionHandle = CreateEvent(NULL, TRUE, FALSE, NULL);
	SetHandle(hMotionHandle);
	pMotionThread = AfxBeginThread(MotionThreadFunction, this);// , THREAD_PRIORITY_ABOVE_NORMAL);

	return TRUE;
}

BOOL CStretchMotion::EndProcess()
{
	int i = 0;

	m_StateFinish = FALSE;

	SetStep(eSTRETCH_MOTION_IDLE, FALSE);

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

BOOL CStretchMotion::Start()
{
	m_bMotionDone = FALSE;
	m_bStopBit = FALSE;
	m_nCurStep = eSTRETCH_MOTION_START;
	SetStep(m_nCurStep, _T("m_nCurStep"));
	return TRUE;
}

BOOL CStretchMotion::Stop()
{
	m_bStopBit = TRUE;
	SetStop(); //!!
	return TRUE;
}

UINT CStretchMotion::MotionThreadFunction(LPVOID lpParam)
{
	CStretchMotion* pStretchMotion = NULL;

	pStretchMotion = (CStretchMotion*)lpParam;

	pStretchMotion->MotionThreadFunctionEntry();

	pStretchMotion->m_bTerminate = 1;

	return 0;
}

VOID CStretchMotion::MotionThreadFunctionEntry(VOID)
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

			SetCurrentStep(eSTRETCH_MOTION_START); //KJT 20210318
			continue; //!!
		}

		switch (GetCurrentTotalStep())
		{
		case eSTRETCH_MOTION_START:
			SetStep(eSTRETCH_MOTION_DONE, _T("eSTRETCH_MOTION_DONE"));
			break;


		case eSTRETCH_MOTION_DONE:
			m_bMotionDone = TRUE;
			SetStep(eSTRETCH_MOTION_IDLE, _T("eSTRETCH_MOTION_IDLE"));
			break;

		case eSTRETCH_MOTION_EXIT:
			m_StateFinish = FALSE;
			break;
		}
	}
}

BOOL CStretchMotion::IsAxisHome(UINT nAxisNo)
{
	return SharedInfo::AxisHomeStatus[nAxisNo];
}

BOOL CStretchMotion::MoveAxis(enum_Axis eAxis, double dPos)
{
	double	dSpeed = 0.0, dAccel = 0.0, dDecel = 0.0;

	//ÇöÀç ¸ðÅÍÀÇ ÆÄ¶ó¹ÌÅÍ ¹Þ¾Æ¿À±â
	if (!GetAxisWorkParam(eAxis, &dSpeed, &dAccel, &dDecel)) return FALSE;
	//ÇØ´ç ¸ðÅÍ¿¡ ÆÄ¶ó¹ÌÅÍ Àü´Þ
	AbsMove(eAxis, dPos, dSpeed, dAccel, dDecel);
	return TRUE;
}
BOOL CStretchMotion::IsMoveDone(enum_Axis eAxis, double dPos)
{
	double dCmdPos = SharedInfo::GetCmdPos(eAxis);
	return (IsSamePosition(dCmdPos, dPos) && IsMotionDone(eAxis));
}

#pragma region //Stretch MovePos
//MovePos
//ÇÑ½ÖÀ¸·Î Move
BOOL CStretchMotion::Stretch_WaitPos(enum_eGRIPPER_ROW eRow)
{
	CString Str = _T("");
	//21.04.03 sjc
	double dPosLeft = 0.0; //CManualData::m_ManualDataStretch.Info.m_dStretchLeft_WaitPos;
	double dPosRight = 0.0; //CManualData::m_ManualDataStretch.Info.m_dStretchRight_WaitPos;
#ifndef GRIPPER_0
	enum_Axis eStretchLeft = (enum_Axis)(AXIS_GRIPPER_STRETCH_L1 + eRow);
	enum_Axis eStretchRight = (enum_Axis)(AXIS_GRIPPER_STRETCH_R1 + eRow);
	if (eRow == (enum_eGRIPPER_ROW)eGRIPPER_ROW1)
	{
		dPosLeft = CManualData::m_ManualDataStretch.Info.m_dStretchLeft_1_WaitPos;
		dPosRight = CManualData::m_ManualDataStretch.Info.m_dStretchRight_1_WaitPos;
	}
	else if (eRow == (enum_eGRIPPER_ROW)eGRIPPER_ROW2)
	{
		dPosLeft = CManualData::m_ManualDataStretch.Info.m_dStretchLeft_2_WaitPos;
		dPosRight = CManualData::m_ManualDataStretch.Info.m_dStretchRight_2_WaitPos;
	}
	else if (eRow == (enum_eGRIPPER_ROW)eGRIPPER_ROW3)
	{
		dPosLeft = CManualData::m_ManualDataStretch.Info.m_dStretchLeft_3_WaitPos;
		dPosRight = CManualData::m_ManualDataStretch.Info.m_dStretchRight_3_WaitPos;
	}
	BOOL bRtnL = MoveAxis(eStretchLeft, dPosLeft);
	if (bRtnL == TRUE)
	{
		Str.Format(_T("Gripper L%d Move To Wait Pos (Wait Pos : %.5f)"), eRow + 1, dPosLeft);
		Total_Msg(Str);
	}
	Sleep(20);

	BOOL bRtnR = MoveAxis(eStretchRight, dPosRight);
	if (bRtnR == TRUE)
	{
		Str.Format(_T("Gripper R%d Move To Wait Pos (Wait Pos : %.5f)"), eRow + 1, dPosRight);
		Total_Msg(Str);
	}
	Sleep(20);
#else
	BOOL bRtnL = FALSE;
	BOOL bRtnR = FALSE;
#endif
	return (bRtnL && bRtnR);
}
BOOL CStretchMotion::Stretch_FwdPos(enum_eGRIPPER_ROW eRow)
{
	CString Str = _T("");
	//21.04.03 sjc
	double dPosLeft = 0.0;// CManualData::m_ManualDataStretch.Info.m_dStretchLeft_ForwardPos;
	double dPosRight = 0.0;// CManualData::m_ManualDataStretch.Info.m_dStretchRight_ForwardPos;
#ifndef GRIPPER_0
	enum_Axis eStretchLeft = (enum_Axis)(AXIS_GRIPPER_STRETCH_L1 + eRow);
	enum_Axis eStretchRight = (enum_Axis)(AXIS_GRIPPER_STRETCH_R1 + eRow);
	if (eRow == (enum_eGRIPPER_ROW)eGRIPPER_ROW1)
	{
		dPosLeft = CManualData::m_ManualDataStretch.Info.m_dStretchLeft_1_ForwardPos;
		dPosRight = CManualData::m_ManualDataStretch.Info.m_dStretchRight_1_ForwardPos;
	}
	else if (eRow == (enum_eGRIPPER_ROW)eGRIPPER_ROW2)
	{
		dPosLeft = CManualData::m_ManualDataStretch.Info.m_dStretchLeft_2_ForwardPos;
		dPosRight = CManualData::m_ManualDataStretch.Info.m_dStretchRight_2_ForwardPos;
	}
	else if (eRow == (enum_eGRIPPER_ROW)eGRIPPER_ROW3)
	{
		dPosLeft = CManualData::m_ManualDataStretch.Info.m_dStretchLeft_3_ForwardPos;
		dPosRight = CManualData::m_ManualDataStretch.Info.m_dStretchRight_3_ForwardPos;
	}
	BOOL bRtnL = MoveAxis(eStretchLeft, dPosLeft);
	if (bRtnL == TRUE)
	{
		Str.Format(_T("Gripper L%d Move To Fwd Pos (Pos : %.5f)"), eRow + 1, dPosLeft);
		Total_Msg(Str);
	}
	Sleep(100); //!!

	BOOL bRtnR = MoveAxis(eStretchRight, dPosRight);
	if (bRtnR == TRUE)
	{
		Str.Format(_T("Gripper R%d Move To Fwd Pos (Pos : %.5f)"), eRow + 1, dPosRight);
		Total_Msg(Str);
	}
	Sleep(100); //!!
#else
	BOOL bRtnL = FALSE;
	BOOL bRtnR = FALSE;
#endif
	return (bRtnL && bRtnR);
}
BOOL CStretchMotion::Stretch_BwdPos(enum_eGRIPPER_ROW eRow)
{
	CString Str = _T("");
	//21.04.03 sjc
	double dPosLeft = 0.0; //CManualData::m_ManualDataStretch.Info.m_dStretchLeft_BackwardPos;
	double dPosRight = 0.0; //CManualData::m_ManualDataStretch.Info.m_dStretchRight_BackwardPos;
#ifndef GRIPPER_0
	enum_Axis eStretchLeft = (enum_Axis)(AXIS_GRIPPER_STRETCH_L1 + eRow);
	enum_Axis eStretchRight = (enum_Axis)(AXIS_GRIPPER_STRETCH_R1 + eRow);
	if (eRow == (enum_eGRIPPER_ROW)eGRIPPER_ROW1)
	{
		dPosLeft = CManualData::m_ManualDataStretch.Info.m_dStretchLeft_1_BackwardPos;
		dPosRight = CManualData::m_ManualDataStretch.Info.m_dStretchRight_1_BackwardPos;
	}
	else if (eRow == (enum_eGRIPPER_ROW)eGRIPPER_ROW2)
	{
		dPosLeft = CManualData::m_ManualDataStretch.Info.m_dStretchLeft_2_BackwardPos;
		dPosRight = CManualData::m_ManualDataStretch.Info.m_dStretchRight_2_BackwardPos;
	}
	else if (eRow == (enum_eGRIPPER_ROW)eGRIPPER_ROW3)
	{
		dPosLeft = CManualData::m_ManualDataStretch.Info.m_dStretchLeft_3_BackwardPos;
		dPosRight = CManualData::m_ManualDataStretch.Info.m_dStretchRight_3_BackwardPos;
	}
	BOOL bRtnL = MoveAxis(eStretchLeft, dPosLeft);
	if (bRtnL == TRUE)
	{
		Str.Format(_T("Gripper L%d Move To Bwd Pos (Pos : %.5f)"), eRow + 1, dPosLeft);
		Total_Msg(Str);
	}
	Sleep(100); //!!

	BOOL bRtnR = MoveAxis(eStretchRight, dPosRight);
	if (bRtnR == TRUE)
	{
		Str.Format(_T("Gripper R%d Move To Bwd Pos (Pos : %.5f)"), eRow + 1, dPosRight);
		Total_Msg(Str);
	}
	Sleep(100); //!!
#else
BOOL bRtnL = FALSE;
BOOL bRtnR = FALSE;
#endif
	return (bRtnL && bRtnR);
}
BOOL CStretchMotion::Stretch_WaitPos_All()
{
	CString Str = _T("");
	double dPosLeft = 0.0, dPosRight = 0.0;
	enum_Axis eStretchLeft = AXIS_NONE, eStretchRight = AXIS_NONE;
	BOOL bRtnL = FALSE, bRtnR = FALSE, bResult = TRUE;
	int i = 0;
	for (i = 0; i < eGRIPPER_ROW_MAX; i++)
	{
		bResult = Stretch_WaitPos((enum_eGRIPPER_ROW)i);
		Sleep(100); //!!
	}	

	return bResult;
}
BOOL CStretchMotion::Stretch_FwdPos_Active()
{
	CString Str = _T("");
	double dPosLeft = 0.0, dPosRight = 0.0;
	enum_Axis eStretchLeft = AXIS_NONE, eStretchRight = AXIS_NONE;
	BOOL bRtnL = FALSE, bRtnR = FALSE, bResult = TRUE;
	int i = 0;
	for (i = 0; i < eGRIPPER_ROW_MAX; i++)
	{
		if (CModelData::m_StretchPara.Info.bStretchUse[i])
		{
			bResult = Stretch_FwdPos((enum_eGRIPPER_ROW)i);
			Sleep(100); //!!
		}
	}

	return bResult;
}
BOOL CStretchMotion::Stretch_FwdPos_All()
{
	CString Str = _T("");
	double dPosLeft = 0.0, dPosRight = 0.0;
	enum_Axis eStretchLeft = AXIS_NONE, eStretchRight = AXIS_NONE;
	BOOL bRtnL = FALSE, bRtnR = FALSE, bResult = TRUE;
	int i = 0;
	for (i = 0; i < eGRIPPER_ROW_MAX; i++)
	{
		bRtnL = Stretch_FwdPos((enum_eGRIPPER_ROW)i);
		Sleep(100); //!!
	}

	return bResult;
}
BOOL CStretchMotion::Stretch_BwdPos_All()
{
	CString Str = _T("");
	double dPosLeft = 0.0, dPosRight = 0.0;
	enum_Axis eStretchLeft = AXIS_NONE, eStretchRight = AXIS_NONE;
	BOOL bRtnL = FALSE, bRtnR = FALSE, bResult = TRUE;
	int i = 0;
	for (i = 0; i < eGRIPPER_ROW_MAX; i++)
	{
		bRtnL = Stretch_BwdPos((enum_eGRIPPER_ROW)i);
		Sleep(100); //!!
	}

	return bResult;
}

BOOL CStretchMotion::Stretch_WaitPos_L(enum_eGRIPPER_ROW eRow)
{
	CString Str = _T("");
	double dPosLeft=0.0;// = CManualData::m_ManualDataStretch.Info.m_dStretchLeft_WaitPos;
	//double dPosRight=0.0;// = CManualData::m_ManualDataStretch.Info.m_dStretchRight_WaitPos;
#ifndef GRIPPER_0
	enum_Axis eStretchLeft = (enum_Axis)(AXIS_GRIPPER_STRETCH_L1 + eRow);
	if (eRow == (enum_eGRIPPER_ROW)eGRIPPER_ROW1)
	{
		dPosLeft = CManualData::m_ManualDataStretch.Info.m_dStretchLeft_1_WaitPos;
		//dPosRight = CManualData::m_ManualDataStretch.Info.m_dStretchRight_1_WaitPos;
	}
	else if (eRow == (enum_eGRIPPER_ROW)eGRIPPER_ROW2)
	{
		dPosLeft = CManualData::m_ManualDataStretch.Info.m_dStretchLeft_2_WaitPos;
		//dPosRight = CManualData::m_ManualDataStretch.Info.m_dStretchRight_2_WaitPos;
	}
	else if (eRow == (enum_eGRIPPER_ROW)eGRIPPER_ROW3)
	{
		dPosLeft = CManualData::m_ManualDataStretch.Info.m_dStretchLeft_3_WaitPos;
		//dPosRight = CManualData::m_ManualDataStretch.Info.m_dStretchRight_3_WaitPos;
	}

	BOOL bRtnL = MoveAxis(eStretchLeft, dPosLeft);
	if (bRtnL == TRUE)
	{
		Str.Format(_T("Gripper L%d Move To Wait Pos (Wait Pos : %.5f)"), eRow + 1, dPosLeft);
		Total_Msg(Str);
	}
	Sleep(20);
#else
	BOOL bRtnL = FALSE;
#endif
	return (bRtnL);
}
BOOL CStretchMotion::Stretch_FwdPos_L(enum_eGRIPPER_ROW eRow)
{
	CString Str = _T("");
	double dPosLeft = 0.0;// CManualData::m_ManualDataStretch.Info.m_dStretchLeft_1_ForwardPos;
#ifndef GRIPPER_0
	enum_Axis eStretchLeft = (enum_Axis)(AXIS_GRIPPER_STRETCH_L1 + eRow);
	if (eRow == (enum_eGRIPPER_ROW)eGRIPPER_ROW1)
	{
		dPosLeft = CManualData::m_ManualDataStretch.Info.m_dStretchLeft_1_ForwardPos;
	}
	else if (eRow == (enum_eGRIPPER_ROW)eGRIPPER_ROW2)
	{
		dPosLeft = CManualData::m_ManualDataStretch.Info.m_dStretchLeft_2_ForwardPos;
	}
	else if (eRow == (enum_eGRIPPER_ROW)eGRIPPER_ROW3)
	{
		dPosLeft = CManualData::m_ManualDataStretch.Info.m_dStretchLeft_3_ForwardPos;
	}
	BOOL bRtnL = MoveAxis(eStretchLeft, dPosLeft);
	if (bRtnL == TRUE)
	{
		Str.Format(_T("Gripper L%d Move To Fwd Pos (Pos : %.5f)"), eRow + 1, dPosLeft);
		Total_Msg(Str);
	}
	Sleep(100); //!!
#else
	BOOL bRtnL = FALSE;
#endif
	return (bRtnL);
}
BOOL CStretchMotion::Stretch_BwdPos_L(enum_eGRIPPER_ROW eRow)
{
	CString Str = _T("");
	double dPosLeft = 0.0;// CManualData::m_ManualDataStretch.Info.m_dStretchLeft_1_BackwardPos;
#ifndef GRIPPER_0
	enum_Axis eStretchLeft = (enum_Axis)(AXIS_GRIPPER_STRETCH_L1 + eRow);
	if (eRow == (enum_eGRIPPER_ROW)eGRIPPER_ROW1)
	{
		dPosLeft = CManualData::m_ManualDataStretch.Info.m_dStretchLeft_1_BackwardPos;
	}
	else if (eRow == (enum_eGRIPPER_ROW)eGRIPPER_ROW2)
	{
		dPosLeft = CManualData::m_ManualDataStretch.Info.m_dStretchLeft_2_BackwardPos;
	}
	else if (eRow == (enum_eGRIPPER_ROW)eGRIPPER_ROW3)
	{
		dPosLeft = CManualData::m_ManualDataStretch.Info.m_dStretchLeft_3_BackwardPos;
	}
	BOOL bRtnL = MoveAxis(eStretchLeft, dPosLeft);
	if (bRtnL == TRUE)
	{
		Str.Format(_T("Gripper L%d Move To Bwd Pos (Pos : %.5f)"), eRow + 1, dPosLeft);
		Total_Msg(Str);
	}
	Sleep(100); //!!
#else
	BOOL bRtnL = FALSE;
#endif
	return (bRtnL);
}
BOOL CStretchMotion::Stretch_WaitPos_R(enum_eGRIPPER_ROW eRow)
{
	CString Str = _T("");
	//21.04.03 sjc
	double dPosRight = 0.0; CManualData::m_ManualDataStretch.Info.m_dStretchRight_1_WaitPos;
#ifndef GRIPPER_0
	enum_Axis eStretchRight = (enum_Axis)(AXIS_GRIPPER_STRETCH_R1 + eRow);
	if (eRow == (enum_eGRIPPER_ROW)eGRIPPER_ROW1)
	{
		//dPosLeft = CManualData::m_ManualDataStretch.Info.m_dStretchLeft_1_WaitPos;
		dPosRight = CManualData::m_ManualDataStretch.Info.m_dStretchRight_1_WaitPos;
	}
	else if (eRow == (enum_eGRIPPER_ROW)eGRIPPER_ROW2)
	{
		//dPosLeft = CManualData::m_ManualDataStretch.Info.m_dStretchLeft_2_WaitPos;
		dPosRight = CManualData::m_ManualDataStretch.Info.m_dStretchRight_2_WaitPos;
	}
	else if (eRow == (enum_eGRIPPER_ROW)eGRIPPER_ROW3)
	{
		//dPosLeft = CManualData::m_ManualDataStretch.Info.m_dStretchLeft_3_WaitPos;
		dPosRight = CManualData::m_ManualDataStretch.Info.m_dStretchRight_3_WaitPos;
	}
	BOOL bRtnR = MoveAxis(eStretchRight, dPosRight);
	if (bRtnR == TRUE)
	{
		Str.Format(_T("Gripper R%d Move To Wait Pos (Wait Pos : %.5f)"), eRow + 1, dPosRight);
		Total_Msg(Str);
	}
	Sleep(20);
#else
	BOOL bRtnR = FALSE;
#endif
	return (bRtnR);
}
BOOL CStretchMotion::Stretch_FwdPos_R(enum_eGRIPPER_ROW eRow)
{
	CString Str = _T("");
	//21.04.03 sjc
	double dPosRight = 0.0; // CManualData::m_ManualDataStretch.Info.m_dStretchRight_ForwardPos;
#ifndef GRIPPER_0
	enum_Axis eStretchRight = (enum_Axis)(AXIS_GRIPPER_STRETCH_R1 + eRow);
	if (eRow == (enum_eGRIPPER_ROW)eGRIPPER_ROW1)
	{
		//dPosLeft = CManualData::m_ManualDataStretch.Info.m_dStretchLeft_1_ForwardPos;
		dPosRight = CManualData::m_ManualDataStretch.Info.m_dStretchRight_1_ForwardPos;
	}
	else if (eRow == (enum_eGRIPPER_ROW)eGRIPPER_ROW2)
	{
		//dPosLeft = CManualData::m_ManualDataStretch.Info.m_dStretchLeft_2_ForwardPos;
		dPosRight = CManualData::m_ManualDataStretch.Info.m_dStretchRight_2_ForwardPos;
	}
	else if (eRow == (enum_eGRIPPER_ROW)eGRIPPER_ROW3)
	{
		//dPosLeft = CManualData::m_ManualDataStretch.Info.m_dStretchLeft_3_ForwardPos;
		dPosRight = CManualData::m_ManualDataStretch.Info.m_dStretchRight_3_ForwardPos;
	}
	BOOL bRtnR = MoveAxis(eStretchRight, dPosRight);
	if (bRtnR == TRUE)
	{
		Str.Format(_T("Gripper R%d Move To Fwd Pos (Pos : %.5f)"), eRow + 1, dPosRight);
		Total_Msg(Str);
	}
	Sleep(100); //!!
#else
	BOOL bRtnR = FALSE;
#endif
	return (bRtnR);
}
BOOL CStretchMotion::Stretch_BwdPos_R(enum_eGRIPPER_ROW eRow)
{
	CString Str = _T("");
	//21.04.03 sjc
	double dPosRight = 0.0; // CManualData::m_ManualDataStretch.Info.m_dStretchRight_BackwardPos;
#ifndef GRIPPER_0
	enum_Axis eStretchRight = (enum_Axis)(AXIS_GRIPPER_STRETCH_R1 + eRow);
	if (eRow == (enum_eGRIPPER_ROW)eGRIPPER_ROW1)
	{
		//dPosLeft = CManualData::m_ManualDataStretch.Info.m_dStretchLeft_1_BackwardPos;
		dPosRight = CManualData::m_ManualDataStretch.Info.m_dStretchRight_1_BackwardPos;
	}
	else if (eRow == (enum_eGRIPPER_ROW)eGRIPPER_ROW2)
	{
		//dPosLeft = CManualData::m_ManualDataStretch.Info.m_dStretchLeft_2_BackwardPos;
		dPosRight = CManualData::m_ManualDataStretch.Info.m_dStretchRight_2_BackwardPos;
	}
	else if (eRow == (enum_eGRIPPER_ROW)eGRIPPER_ROW3)
	{
		//dPosLeft = CManualData::m_ManualDataStretch.Info.m_dStretchLeft_3_BackwardPos;
		dPosRight = CManualData::m_ManualDataStretch.Info.m_dStretchRight_3_BackwardPos;
	}
	BOOL bRtnR = MoveAxis(eStretchRight, dPosRight);
	if (bRtnR == TRUE)
	{
		Str.Format(_T("Gripper R%d Move To Bwd Pos (Pos : %.5f)"), eRow + 1, dPosRight);
		Total_Msg(Str);
	}
	Sleep(100); //!!
#else
	BOOL bRtnR = FALSE;
#endif
	return (bRtnR);
}

//MovePosDone Check
BOOL CStretchMotion::Is_Stretch_WaitPos(enum_eGRIPPER_ROW eRow)
{
	//21.04.03 sjc
	double dPosLeft = 0.0;// CManualData::m_ManualDataStretch.Info.m_dStretchLeft_WaitPos;
	double dPosRight = 0.0;// CManualData::m_ManualDataStretch.Info.m_dStretchRight_WaitPos;
#ifndef GRIPPER_0
	enum_Axis eStretchLeft = (enum_Axis)(AXIS_GRIPPER_STRETCH_L1 + eRow);
	enum_Axis eStretchRight = (enum_Axis)(AXIS_GRIPPER_STRETCH_R1 + eRow);
	if (eRow == (enum_eGRIPPER_ROW)eGRIPPER_ROW1)
	{
		dPosLeft = CManualData::m_ManualDataStretch.Info.m_dStretchLeft_1_WaitPos;
		dPosRight = CManualData::m_ManualDataStretch.Info.m_dStretchRight_1_WaitPos;
	}
	else if (eRow == (enum_eGRIPPER_ROW)eGRIPPER_ROW2)
	{
		dPosLeft = CManualData::m_ManualDataStretch.Info.m_dStretchLeft_2_WaitPos;
		dPosRight = CManualData::m_ManualDataStretch.Info.m_dStretchRight_2_WaitPos;
	}
	else if (eRow == (enum_eGRIPPER_ROW)eGRIPPER_ROW3)
	{
		dPosLeft = CManualData::m_ManualDataStretch.Info.m_dStretchLeft_3_WaitPos;
		dPosRight = CManualData::m_ManualDataStretch.Info.m_dStretchRight_3_WaitPos;
	}
	BOOL bRtnL = IsMoveDone(eStretchLeft, dPosLeft);
	BOOL bRtnR = IsMoveDone(eStretchRight, dPosRight);
#else
	BOOL bRtnL = FALSE;
	BOOL bRtnR = FALSE;
#endif
	return (bRtnL && bRtnR);
}
BOOL CStretchMotion::Is_Stretch_FwdPos(enum_eGRIPPER_ROW eRow)
{
	//21.04.03 sjc
	double dPosLeft = 0.0;// CManualData::m_ManualDataStretch.Info.m_dStretchLeft_ForwardPos;
	double dPosRight = 0.0; //CManualData::m_ManualDataStretch.Info.m_dStretchRight_ForwardPos;
#ifndef GRIPPER_0
	enum_Axis eStretchLeft = (enum_Axis)(AXIS_GRIPPER_STRETCH_L1 + eRow);
	enum_Axis eStretchRight = (enum_Axis)(AXIS_GRIPPER_STRETCH_R1 + eRow);
	if (eRow == (enum_eGRIPPER_ROW)eGRIPPER_ROW1)
	{
		dPosLeft = CManualData::m_ManualDataStretch.Info.m_dStretchLeft_1_ForwardPos;
		dPosRight = CManualData::m_ManualDataStretch.Info.m_dStretchRight_1_ForwardPos;
	}
	else if (eRow == (enum_eGRIPPER_ROW)eGRIPPER_ROW2)
	{
		dPosLeft = CManualData::m_ManualDataStretch.Info.m_dStretchLeft_2_ForwardPos;
		dPosRight = CManualData::m_ManualDataStretch.Info.m_dStretchRight_2_ForwardPos;
	}
	else if (eRow == (enum_eGRIPPER_ROW)eGRIPPER_ROW3)
	{
		dPosLeft = CManualData::m_ManualDataStretch.Info.m_dStretchLeft_3_ForwardPos;
		dPosRight = CManualData::m_ManualDataStretch.Info.m_dStretchRight_3_ForwardPos;
	}

	BOOL bRtnL = IsMoveDone(eStretchLeft, dPosLeft);
	BOOL bRtnR = IsMoveDone(eStretchRight, dPosRight);
#else
	BOOL bRtnL = FALSE;
	BOOL bRtnR = FALSE;
#endif
	return (bRtnL && bRtnR);
}
BOOL CStretchMotion::Is_Stretch_BwdPos(enum_eGRIPPER_ROW eRow)
{
	//21.04.03 sjc
	double dPosLeft = 0.0;// CManualData::m_ManualDataStretch.Info.m_dStretchLeft_BackwardPos;
	double dPosRight = 0.0;// CManualData::m_ManualDataStretch.Info.m_dStretchRight_BackwardPos;
#ifndef GRIPPER_0
	enum_Axis eStretchLeft = (enum_Axis)(AXIS_GRIPPER_STRETCH_L1 + eRow);
	enum_Axis eStretchRight = (enum_Axis)(AXIS_GRIPPER_STRETCH_R1 + eRow);
	if (eRow == (enum_eGRIPPER_ROW)eGRIPPER_ROW1)
	{
		dPosLeft = CManualData::m_ManualDataStretch.Info.m_dStretchLeft_1_BackwardPos;
		dPosRight = CManualData::m_ManualDataStretch.Info.m_dStretchRight_1_BackwardPos;
	}
	else if (eRow == (enum_eGRIPPER_ROW)eGRIPPER_ROW2)
	{
		dPosLeft = CManualData::m_ManualDataStretch.Info.m_dStretchLeft_2_BackwardPos;
		dPosRight = CManualData::m_ManualDataStretch.Info.m_dStretchRight_2_BackwardPos;
	}
	else if (eRow == (enum_eGRIPPER_ROW)eGRIPPER_ROW3)
	{
		dPosLeft = CManualData::m_ManualDataStretch.Info.m_dStretchLeft_3_BackwardPos;
		dPosRight = CManualData::m_ManualDataStretch.Info.m_dStretchRight_3_BackwardPos;
	}
	BOOL bRtnL = IsMoveDone(eStretchLeft, dPosLeft);
	BOOL bRtnR = IsMoveDone(eStretchRight, dPosRight);
#else
	BOOL bRtnL = FALSE;
	BOOL bRtnR = FALSE;
#endif
	return (bRtnL && bRtnR);
}

BOOL CStretchMotion::Is_Stretch_WaitPos_Active()
{
	//21.04.03 sjc
	//double dPosLeft = 0.0, dPosRight = 0.0;
	//enum_Axis eStretchLeft = AXIS_NONE, eStretchRight = AXIS_NONE;
	//BOOL bRtnL = FALSE, bRtnR = FALSE, bResult = TRUE;
	//int i = 0;
	//for (i = 0; i < eGRIPPER_ROW_MAX; i++)
	//{
	//	dPosLeft = CManualData::m_ManualDataStretch.Info.m_dStretchLeft_WaitPos;
	//	dPosRight = CManualData::m_ManualDataStretch.Info.m_dStretchRight_WaitPos;
	//	eStretchLeft = (enum_Axis)(AXIS_GRIPPER_STRETCH_L1 + i);
	//	eStretchRight = (enum_Axis)(AXIS_GRIPPER_STRETCH_R1 + i);

	//	bRtnL = IsMoveDone(eStretchLeft, dPosLeft);
	//	bRtnR = IsMoveDone(eStretchRight, dPosRight);

	//	if (bRtnL == FALSE || bRtnR == FALSE)
	//	{
	//		bResult = FALSE;
	//		break;
	//	}
	//}

	BOOL bResult = TRUE;
	for (int i = 0; i < eGRIPPER_ROW_MAX; i++)
	{
		if (CModelData::m_StretchPara.Info.bStretchUse[i] == TRUE)
		{
			bResult = bResult && Is_Stretch_WaitPos((enum_eGRIPPER_ROW)i);
		}
	}
	return bResult;
}
BOOL CStretchMotion::Is_Stretch_WaitPos_All()
{
	//21.04.03 sjc
	//double dPosLeft = 0.0, dPosRight = 0.0;
	//enum_Axis eStretchLeft = AXIS_NONE, eStretchRight = AXIS_NONE;
	//BOOL bRtnL = FALSE, bRtnR = FALSE, bResult = TRUE;
	//int i = 0;
	//for (i = 0; i < eGRIPPER_ROW_MAX; i++)
	//{
	//	if (CModelData::m_StretchPara.Info.bStretchUse[i])
	//	{
	//		dPosLeft = CManualData::m_ManualDataStretch.Info.m_dStretchLeft_WaitPos;
	//		dPosRight = CManualData::m_ManualDataStretch.Info.m_dStretchRight_WaitPos;
	//		eStretchLeft = (enum_Axis)(AXIS_GRIPPER_STRETCH_L1 + i);
	//		eStretchRight = (enum_Axis)(AXIS_GRIPPER_STRETCH_R1 + i);

	//		bRtnL = IsMoveDone(eStretchLeft, dPosLeft);
	//		bRtnR = IsMoveDone(eStretchRight, dPosRight);

	//		if (bRtnL == FALSE || bRtnR == FALSE)
	//		{
	//			bResult = FALSE;
	//			break;
	//		}
	//	}
	//}
	BOOL bResult = TRUE;
	for (int i = 0; i < 3; i++)
	{
		bResult = bResult && Is_Stretch_WaitPos((enum_eGRIPPER_ROW)i);
	}

	return bResult;
}
BOOL CStretchMotion::Is_Stretch_FwdPos_Active()
{
	//21.04.03 SJC
	//double dPosLeft = 0.0, dPosRight = 0.0;
	//enum_Axis eStretchLeft = AXIS_NONE, eStretchRight = AXIS_NONE;
	//BOOL bRtnL = FALSE, bRtnR = FALSE, bResult = TRUE;
	//int i = 0;
	//for (i = 0; i < eGRIPPER_ROW_MAX; i++)
	//{
	//	if (CModelData::m_StretchPara.Info.bStretchUse[i])
	//	{
	//		dPosLeft = CManualData::m_ManualDataStretch.Info.m_dStretchLeft_ForwardPos;
	//		dPosRight = CManualData::m_ManualDataStretch.Info.m_dStretchRight_ForwardPos;
	//		eStretchLeft = (enum_Axis)(AXIS_GRIPPER_STRETCH_L1 + i);
	//		eStretchRight = (enum_Axis)(AXIS_GRIPPER_STRETCH_R1 + i);

	//		bRtnL = IsMoveDone(eStretchLeft, dPosLeft);
	//		bRtnR = IsMoveDone(eStretchRight, dPosRight);

	//		if (bRtnL == FALSE || bRtnR == FALSE)
	//		{
	//			bResult = FALSE;
	//			break;
	//		}
	//	}
	//}

	BOOL bResult = TRUE;
	for (int i = 0; i < eGRIPPER_ROW_MAX; i++)
	{
		if (CModelData::m_StretchPara.Info.bStretchUse[i] == TRUE)
		{
			bResult = bResult && Is_Stretch_FwdPos((enum_eGRIPPER_ROW)i);
		}
	}
	return bResult;
}
BOOL CStretchMotion::Is_Stretch_FwdPos_All()
{
	//21.04.03 sjc
	//double dPosLeft = 0.0, dPosRight = 0.0;
	//enum_Axis eStretchLeft = AXIS_NONE, eStretchRight = AXIS_NONE;
	//BOOL bRtnL = FALSE, bRtnR = FALSE, bResult = TRUE;
	//int i = 0;
	//for (i = 0; i < eGRIPPER_ROW_MAX; i++)
	//{
	//	dPosLeft = CManualData::m_ManualDataStretch.Info.m_dStretchLeft_ForwardPos;
	//	dPosRight = CManualData::m_ManualDataStretch.Info.m_dStretchRight_ForwardPos;
	//	eStretchLeft = (enum_Axis)(AXIS_GRIPPER_STRETCH_L1 + i);
	//	eStretchRight = (enum_Axis)(AXIS_GRIPPER_STRETCH_R1 + i);

	//	bRtnL = IsMoveDone(eStretchLeft, dPosLeft);
	//	bRtnR = IsMoveDone(eStretchRight, dPosRight);

	//	if (bRtnL == FALSE || bRtnR == FALSE)
	//	{
	//		bResult = FALSE;
	//		break;
	//	}
	//}

	BOOL bResult = TRUE;
	for (int i = 0; i < 3; i++)
	{
		bResult = bResult && Is_Stretch_FwdPos((enum_eGRIPPER_ROW)i);
	}

	return bResult;
}
BOOL CStretchMotion::Is_Stretch_BwdPos_Active()
{
	//21.04.03 sjc
	//double dPosLeft = 0.0, dPosRight = 0.0;
	//enum_Axis eStretchLeft = AXIS_NONE, eStretchRight = AXIS_NONE;
	//BOOL bRtnL = FALSE, bRtnR = FALSE, bResult = TRUE;
	//int i = 0;
	//for (i = 0; i < eGRIPPER_ROW_MAX; i++)
	//{
	//	if (CModelData::m_StretchPara.Info.bStretchUse[i])
	//	{
	//		dPosLeft = CManualData::m_ManualDataStretch.Info.m_dStretchLeft_BackwardPos;
	//		dPosRight = CManualData::m_ManualDataStretch.Info.m_dStretchRight_BackwardPos;
	//		eStretchLeft = (enum_Axis)(AXIS_GRIPPER_STRETCH_L1 + i);
	//		eStretchRight = (enum_Axis)(AXIS_GRIPPER_STRETCH_R1 + i);

	//		bRtnL = IsMoveDone(eStretchLeft, dPosLeft);
	//		bRtnR = IsMoveDone(eStretchRight, dPosRight);

	//		if (bRtnL == FALSE || bRtnR == FALSE)
	//		{
	//			bResult = FALSE;
	//			break;
	//		}
	//	}
	//}
	BOOL bResult = TRUE;
	for (int i = 0; i < eGRIPPER_ROW_MAX; i++)
	{
		if (CModelData::m_StretchPara.Info.bStretchUse[i] == TRUE)
		{
			bResult = bResult && Is_Stretch_BwdPos((enum_eGRIPPER_ROW)i);
		}
	}
	return bResult;
}
BOOL CStretchMotion::Is_Stretch_BwdPos_All()
{
	//21.04.03 sjc
	//double dPosLeft = 0.0, dPosRight = 0.0;
	//enum_Axis eStretchLeft = AXIS_NONE, eStretchRight = AXIS_NONE;
	//BOOL bRtnL = FALSE, bRtnR = FALSE, bResult = TRUE;
	//int i = 0;
	//for (i = 0; i < eGRIPPER_ROW_MAX; i++)
	//{
	//	dPosLeft = CManualData::m_ManualDataStretch.Info.m_dStretchLeft_BackwardPos;
	//	dPosRight = CManualData::m_ManualDataStretch.Info.m_dStretchRight_BackwardPos;
	//	eStretchLeft = (enum_Axis)(AXIS_GRIPPER_STRETCH_L1 + i);
	//	eStretchRight = (enum_Axis)(AXIS_GRIPPER_STRETCH_R1 + i);

	//	bRtnL = IsMoveDone(eStretchLeft, dPosLeft);
	//	bRtnR = IsMoveDone(eStretchRight, dPosRight);

	//	if (bRtnL == FALSE || bRtnR == FALSE)
	//	{
	//		bResult = FALSE;
	//		break;
	//	}
	//}
	BOOL bResult = TRUE;
	for (int i = 0; i < 3; i++)
	{
		bResult = bResult && Is_Stretch_BwdPos((enum_eGRIPPER_ROW)i);
	}

	return bResult;
}

#pragma region //Stretch
BOOL CStretchMotion::SendStretchSetPara()
{
	int nUsefulAxisNo[MAX_STRETCH_AXIS_SIZE] = { 0 };
	memset(nUsefulAxisNo, 0x0, sizeof(int)* MAX_STRETCH_AXIS_USE);
	//double dTargetForce[MAX_STEP][MAX_STRETCH_AXIS_SIZE] = { 0.0 };

	for (int i = 0; i < MAX_STRETCH_SIZE; i++)
	{
		if (CModelData::m_StretchPara.Info.bStretchUse[i])
		{
			nUsefulAxisNo[i] = 1;
			nUsefulAxisNo[i + MAX_STRETCH_SIZE] = 1;
		}
		else
		{
			nUsefulAxisNo[i] = 0;
			nUsefulAxisNo[i + MAX_STRETCH_SIZE] = 0;
		}
	}

	Devs::MotionIf.ForceControlSetPara(ForceControlIndex, nUsefulAxisNo, CModelData::m_StretchPara.Info.nStepCount, \
		CModelData::m_StretchPara.Info.dSpeedMax, CModelData::m_StretchPara.Info.dSpeedMin, \
		CModelData::m_StretchPara.Info.dOkRange, CModelData::m_StretchPara.Info.dDecelRange);


	Total_Msg(_T("Stretch Set Para"));
	return TRUE;
}
BOOL CStretchMotion::StretchSetStepValue(int nStepCnt, double dStepValue[MAX_STEP][MAX_STRETCH_SIZE])
{
	double dTargetForce[MAX_STEP][MAX_STRETCH_SIZE];
	memset(dTargetForce, 0x0, sizeof(dTargetForce));

	for (int nStep = 0; nStep < nStepCnt; nStep++)
	{
		for (int i = 0; i < MAX_STRETCH_SIZE; i++)
		{
			if (CModelData::m_StretchPara.Info.bStretchUse[i])
			{
				dTargetForce[nStep][i] = dStepValue[nStep][i];
			}
		}
	}
	Sleep(10);
	Devs::MotionIf.ForceControlSetStepValue(ForceControlIndex, nStepCnt, dTargetForce);
	Sleep(10);
	Total_Msg(_T("Stretch Set Step Value"));

	return TRUE;
}
BOOL CStretchMotion::SendReleaseSetPara()
{
	int nUsefulAxisNo[MAX_STRETCH_AXIS_SIZE] = { 0 };
	memset(nUsefulAxisNo, 0x0, sizeof(int)* MAX_STRETCH_AXIS_USE);
	//double dTargetForce[MAX_STEP][MAX_STRETCH_AXIS_SIZE] = { 0.0 };

	int nStepCount = 1; //!!

	for (int i = 0; i < MAX_STRETCH_SIZE; i++)
	{
		if (CModelData::m_StretchPara.Info.bStretchUse[i])
		{
			nUsefulAxisNo[i] = 1;
			nUsefulAxisNo[i + MAX_STRETCH_SIZE] = 1;
		}
		else
		{
			nUsefulAxisNo[i] = 0;
			nUsefulAxisNo[i + MAX_STRETCH_SIZE] = 0;
		}
	}

	Devs::MotionIf.ForceControlSetPara(ForceControlIndex, nUsefulAxisNo, nStepCount, \
		CModelData::m_StretchPara.Info.dSpeedMax, CModelData::m_StretchPara.Info.dSpeedMin, \
		CModelData::m_StretchPara.Info.dOkRange, CModelData::m_StretchPara.Info.dDecelRange);

	Total_Msg(_T("Release Set Para"));
	return TRUE;
}
BOOL CStretchMotion::SetReleaseStepValue()
{
	double dTargetForce[MAX_STEP][MAX_STRETCH_SIZE];
	memset(dTargetForce, 0x0, sizeof(dTargetForce));

	int nStepCnt = 1;
	double dForceVal = 1.0;

	for (int i = 0; i < MAX_STRETCH_SIZE; i++)
	{
		if (CModelData::m_StretchPara.Info.bStretchUse[i])
		{
			dTargetForce[0][i] = dForceVal;
		}
	}

	Sleep(10);
	Devs::MotionIf.ForceControlSetStepValue(ForceControlIndex, nStepCnt, dTargetForce);
	Sleep(10);
	Total_Msg(_T("Stretch Release Set Step Value"));

	return TRUE;
}
BOOL CStretchMotion::StretchStart(BOOL bReleaseFlag/* = FALSE*/)
{
	int nAxisSize = 0;
	int j = 0;
	int nAxisNo[MAX_STRETCH_AXIS_SIZE];

	for (int i = 0; i < eGRIPPER_ROW_MAX; i++)
	{
		if (CModelData::m_StretchPara.Info.bStretchUse[i])
		{
			nAxisSize++;
		}
#ifndef GRIPPER_0
		nAxisNo[i] = REMOTE_AXIS_AJIN_GRIPPER_STRETCH_L1 + i;
		nAxisNo[i + eGRIPPER_ROW_MAX] = REMOTE_AXIS_AJIN_GRIPPER_STRETCH_R1 + i;
#endif
	}

	Devs::MotionIf.ForceControlStart(FORCE_CONTROL_SF, nAxisSize * 2, nAxisNo, bReleaseFlag);

	return TRUE;
}
BOOL CStretchMotion::StretchStop()
{
	int nAxisSize = 0;;
	int nAxisNo[MAX_STRETCH_SIZE];
	SharedInfo::bMachineStopFlag = TRUE;
	for (int i = 0; i < MAX_STRETCH_SIZE; i++)
	{
		if (CModelData::m_StretchPara.Info.bStretchUse[i])
		{
			nAxisSize++;
		}
	}

	Devs::MotionIf.ForceControlStop(FORCE_CONTROL_SF, nAxisSize * 2, nAxisNo, 100);
	return TRUE;
}
int CStretchMotion::StretchFinish()
{
#ifdef SIM_MODE
	return TRUE;
#endif

	for (int i = 0; i < MAX_STRETCH_SIZE; i++)
	{
		if (CModelData::m_StretchPara.Info.bStretchUse[i])
		{
			if (SharedInfo::nStretchStatus[i] != STRETCH_STATUS_SUCCESS ||
				SharedInfo::nStretchStatus[i + MAX_STRETCH_SIZE] != STRETCH_STATUS_SUCCESS)
			{
				return FALSE;
			}
		}
	}

	return TRUE;
}
#pragma endregion

BOOL CStretchMotion::Gripper2PAlignTensionStretchMoveStart(double dDiffX1, double dDiffX2)
{
#if 0
	CString Str = _T("");
	double dValueL = 0.0, dValueR = 0.0;
	double dVel = 0.;
	double dAccel = 0.;
	double dDecel = 0.;
	double dPos = 0.0;

	for (int i = 0; i < MAX_STRETCH_SIZE; i++)
	{
		if (CModelData::m_StretchPara.Info.bStretchUse[i])
		{
			//[0]
			dValueL = dDiffX1;

			if (dValueL > 0.025) dValueL = 0.025;
			else if (dValueL < -0.025) dValueL = -0.025;

			m_dStretchTargetPos_L[i] = SharedInfo::GetCmdPos((enum_Axis)(AXIS_GRIPPER_STRETCH_L1 + i)) - dValueL;

			//[1]
			dValueR = dDiffX2;

			if (dValueR > 0.025) dValueR = 0.025;
			else if (dValueR < -0.025) dValueR = -0.025;

			m_dStretchTargetPos_R[i] = SharedInfo::GetCmdPos((enum_Axis)(AXIS_GRIPPER_STRETCH_R1 + i)) + dValueR;

			//Move
			StretchPosMove(AXIS_GRIPPER_STRETCH_L1 + i, m_dStretchTargetPos_L[i]);
			Sleep(PC_COM_AJIN_MOTION_DELAY);
			StretchPosMove(AXIS_GRIPPER_STRETCH_R1 + i, m_dStretchTargetPos_R[i]);
			Sleep(PC_COM_AJIN_MOTION_DELAY);

			Str.Format(_T("Tension Stretch L%d Move To %.5f (Dist:%.5f)"), i + 1, m_dStretchTargetPos_L[i], dValueL);
			Total_Msg(Str);
			Str.Format(_T("Tension Stretch R%d Move To %.5f (Dist:%.5f)"), i + 1, m_dStretchTargetPos_R[i], dValueR);
			Total_Msg(Str);

		}
	}
#else
	CString Str = _T("");
	double dValueL = 0.0, dValueR = 0.0;
	double dVel = 0.;
	double dAccel = 0.;
	double dDecel = 0.;
	double dPos = 0.0;

	m_nAxisIndex = 0;
	for (int i = 0; i < MAX_STRETCH_SIZE; i++)
	{
#ifndef GRIPPER_0
		m_nAxisNo[i] = REMOTE_AXIS_AJIN_GRIPPER_STRETCH_L1 + i;
		m_nAxisNo[i + eGRIPPER_ROW_MAX] = REMOTE_AXIS_AJIN_GRIPPER_STRETCH_R1 + i;

		m_dStretchTargetPos[i] = SharedInfo::GetCmdPos((enum_Axis)(AXIS_GRIPPER_STRETCH_L1 + i));
		m_dStretchTargetPos[i + eGRIPPER_ROW_MAX] = SharedInfo::GetCmdPos((enum_Axis)(AXIS_GRIPPER_STRETCH_R1 + i));
#endif
		if (CModelData::m_StretchPara.Info.bStretchUse[i])
		{
			//[0]
			m_nAxisIndex = m_nAxisIndex | (1 << i);

			dValueL = dDiffX1;

			if (dValueL > 0.025) dValueL = 0.025;
			else if (dValueL < -0.025) dValueL = -0.025;

			m_dStretchTargetPos[i] -= dValueL;

			//[1]
			m_nAxisIndex = m_nAxisIndex | (1 << (i + eGRIPPER_ROW_MAX));

			dValueR = dDiffX2;

			if (dValueR > 0.025) dValueR = 0.025;
			else if (dValueR < -0.025) dValueR = -0.025;

			m_dStretchTargetPos[i + eGRIPPER_ROW_MAX] += dValueR;

			Str.Format(_T("Tension Stretch L%d Move To %.5f (Dist:%.5f)"), i + 1, m_dStretchTargetPos[i], dValueL);
			Total_Msg(Str);
			Str.Format(_T("Tension Stretch R%d Move To %.5f (Dist:%.5f)"), i + 1, m_dStretchTargetPos[i + eGRIPPER_ROW_MAX], dValueR);
			Total_Msg(Str);

		}
	}

	Move_StretchTensionPos(m_nAxisIndex, m_nAxisNo, m_dStretchTargetPos);
#endif

	return TRUE;
}
BOOL CStretchMotion::Gripper2PAlignTensionStretchMoveDoneCheck()
{
#if 0
	for (int i = 0; i < MAX_STRETCH_SIZE; i++)
	{
		if (CModelData::m_StretchPara.Info.bStretchUse[i])
		{
			if (IsStretchPosMove((enum_Axis)(AXIS_GRIPPER_STRETCH_L1 + i), m_dStretchTargetPos_L[i]) == FALSE)
				return FALSE;

			if (IsStretchPosMove((enum_Axis)(AXIS_GRIPPER_STRETCH_R1 + i), m_dStretchTargetPos_R[i]) == FALSE)
				return FALSE;
		}
	}
#else
#ifndef GRIPPER_0
	for (int i = 0; i < MAX_STRETCH_SIZE; i++)
	{
		if (CModelData::m_StretchPara.Info.bStretchUse[i])
		{
			if (IsStretchPosMove((enum_Axis)(AXIS_GRIPPER_STRETCH_L1 + i), m_dStretchTargetPos[i]) == FALSE)
				return FALSE;

			if (IsStretchPosMove((enum_Axis)(AXIS_GRIPPER_STRETCH_R1 + i), m_dStretchTargetPos[i + eGRIPPER_ROW_MAX]) == FALSE)
				return FALSE;
		}
	}
#endif
#endif

	return TRUE;
}

BOOL CStretchMotion::Gripper4PAlignTensionStretchMoveStart(double m_AlignPoint[2][4])
{
	CString Str = _T("");
	double dValueL = 0.0, dValueR = 0.0;

	int nMaxAlignCount = 4;
	int nAlignPointIndex_L = 0;
	int nAlignPointIndex_R = 0;

	for (int i = 0; i < MAX_STRETCH_SIZE; i++)
	{
		if (CModelData::m_StretchPara.Info.bStretchUse[i])
		{
			//0:LB, 1:LT
			dValueL = m_AlignPoint[0][nAlignPointIndex_L];

			if (dValueL > 0.025) dValueL = 0.025;
			else if (dValueL < -0.025) dValueL = -0.025;
#ifndef GRIPPER_0
			m_dStretchTargetPos_L[i] = SharedInfo::GetCmdPos((enum_Axis)(AXIS_GRIPPER_STRETCH_L1 + i)) - dValueL;

			//2:RT, 3:RB
			nAlignPointIndex_R = nMaxAlignCount - 1 - nAlignPointIndex_L;

			dValueR = m_AlignPoint[0][nAlignPointIndex_R];

			if (dValueR > 0.025) dValueR = 0.025;
			else if (dValueR < -0.025) dValueR = -0.025;

			m_dStretchTargetPos_R[i] = SharedInfo::GetCmdPos((enum_Axis)(AXIS_GRIPPER_STRETCH_R1 + i)) + dValueR;

			//Move
			StretchPosMove(AXIS_GRIPPER_STRETCH_L1 + i, m_dStretchTargetPos_L[i]);
			Sleep(PC_COM_AJIN_MOTION_DELAY);
			StretchPosMove(AXIS_GRIPPER_STRETCH_R1 + i, m_dStretchTargetPos_R[i]);
			Sleep(PC_COM_AJIN_MOTION_DELAY);
#endif
			Str.Format(_T("Tension Stretch L%d Move To %.5f (Dist:%.5f)"), i + 1, m_dStretchTargetPos_L[i], dValueL);
			Total_Msg(Str);
			Str.Format(_T("Tension Stretch R%d Move To %.5f (Dist:%.5f)"), i + 1, m_dStretchTargetPos_R[i], dValueR);
			Total_Msg(Str);

			nAlignPointIndex_L++; //!!
		}
	}

	return TRUE;
}


BOOL CStretchMotion::Gripper4PAlignTensionStretchMoveDoneCheck()
{
#ifndef GRIPPER_0
	for (int i = 0; i < MAX_STRETCH_SIZE; i++)
	{
		if (CModelData::m_StretchPara.Info.bStretchUse[i])
		{
			if (IsStretchPosMove((enum_Axis)(AXIS_GRIPPER_STRETCH_L1 + i), m_dStretchTargetPos_L[i]) == FALSE)
				return FALSE;

			if (IsStretchPosMove((enum_Axis)(AXIS_GRIPPER_STRETCH_R1 + i), m_dStretchTargetPos_R[i]) == FALSE)
				return FALSE;
		}
	}
#endif
	return TRUE;
}

BOOL CStretchMotion::Move_StretchTensionPos(int nAxisIndex, int nAxisNo[MAX_STRETCH_AXIS_SIZE], double dTargetPos[MAX_STRETCH_AXIS_SIZE])
{
	double dVel = 0.01; //!!

	Devs::MotionIf.StretchPosMove(nAxisIndex, nAxisNo, dTargetPos, dVel);
	return TRUE;
}
BOOL CStretchMotion::Is_StretchTensionPos(int nAxisIndex, int nAxisNo[MAX_STRETCH_AXIS_SIZE], double dTargetPos[MAX_STRETCH_AXIS_SIZE])
{
	enum_Axis eAxis = AXIS_NONE;
#ifndef GRIPPER_0
	for (int i = 0; i < eGRIPPER_ROW_MAX; i++)
	{
		if (CModelData::m_StretchPara.Info.bStretchUse[i])
		{
			eAxis = (enum_Axis)(AXIS_GRIPPER_STRETCH_L1 + i);

			if (IsMoveDone(eAxis, m_dStretchTargetPos[i]) == FALSE)
				return FALSE;

			eAxis = (enum_Axis)(AXIS_GRIPPER_STRETCH_R1 + i);
			if (IsMoveDone(eAxis, m_dStretchTargetPos[i + eGRIPPER_ROW_MAX]) == FALSE)
				return FALSE;
		}
	}
#endif
	return TRUE;
}

BOOL CStretchMotion::StretchPosMove(int nAxisNo, double dPos)
{
	double	dSpeed = 0.0, dAccel = 0.0, dDecel = 0.0;

	enum_Axis	eAxis = (enum_Axis)nAxisNo;

	if (!GetAxisWorkParam(eAxis, &dSpeed, &dAccel, &dDecel)) return FALSE;

	AbsMove(eAxis, dPos, dSpeed, dAccel, dDecel);

	return TRUE;
}
BOOL CStretchMotion::IsStretchPosMove(int nAxisNo, double dPos)
{
	enum_Axis	eAxis = (enum_Axis)nAxisNo;

	double dCmdPos = SharedInfo::GetCmdPos(eAxis);

	return (IsSamePosition(dCmdPos, dPos) && IsMotionDone(eAxis));
}
#pragma endregion