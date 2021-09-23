#include "stdafx.h"
#include "ClampMotion.h"
#include "Vision/Devs.h"
#include "Vision/SharedInfo.h"
#include "CalcAlign/CalcAlign.h"
#include "Log/Logger.h"
#include "Data/ManualData.h"
#include "Data/ModelData.h"

CClampMotion::CClampMotion()
{
}


CClampMotion::~CClampMotion()
{
}

BOOL CClampMotion::InitProcess()
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

BOOL CClampMotion::EndProcess()
{
	int i = 0;

	m_StateFinish = FALSE;

	SetStep(eCLAMP_MOTION_IDLE, FALSE);

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

BOOL CClampMotion::Start()
{
	m_bMotionDone = FALSE;
	m_bStopBit = FALSE;
	m_nCurStep = eCLAMP_MOTION_START;
	SetStep(m_nCurStep, _T("m_nCurStep"));
	return TRUE;
}

BOOL CClampMotion::Stop()
{
	m_bStopBit = TRUE;
	SetStop(); //!!
	return TRUE;
}

UINT CClampMotion::MotionThreadFunction(LPVOID lpParam)
{
	CClampMotion* pClampMotion = NULL;

	pClampMotion = (CClampMotion*)lpParam;

	pClampMotion->MotionThreadFunctionEntry();

	pClampMotion->m_bTerminate = 1;

	return 0;
}

VOID CClampMotion::MotionThreadFunctionEntry(VOID)
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

			SetCurrentStep(eCLAMP_MOTION_START); //KJT 20210318
			continue; //!!
		}

		switch (GetCurrentTotalStep())
		{
		case eCLAMP_MOTION_START:
			SetStep(eCLAMP_MOTION_DONE, _T("eCLAMP_MOTION_DONE"));
			break;


		case eCLAMP_MOTION_DONE:
			m_bMotionDone = TRUE;
			SetStep(eCLAMP_MOTION_IDLE, _T("eCLAMP_MOTION_IDLE"));
			break;

		case eCLAMP_MOTION_EXIT:
			m_StateFinish = FALSE;
			break;
		}
	}
}

BOOL CClampMotion::InitPara()
{
	for (int i = 0; i < eGRIPPER_ROW_MAX; i++)
	{
		//m_nClampAxisL[i] = AXIS_GRIPPER_CLAMP_L1 + i;
		//m_nClampAxisR[i] = AXIS_GRIPPER_CLAMP_R1 + i;
	}

	m_ClampStartIndex = 0;

	return TRUE;
}

BOOL CClampMotion::IsAxisHome(UINT nAxisNo)
{
	return SharedInfo::AxisHomeStatus[nAxisNo];
}

BOOL CClampMotion::MoveAxis(enum_Axis eAxis, double dPos)
{
	double	dSpeed = 0.0, dAccel = 0.0, dDecel = 0.0;

	//현재 모터의 파라미터 받아오기
	if (!GetAxisWorkParam(eAxis, &dSpeed, &dAccel, &dDecel)) return FALSE;
	//해당 모터에 파라미터 전달
	AbsMove(eAxis, dPos, dSpeed, dAccel, dDecel);
	return TRUE;
}
BOOL CClampMotion::IsMoveDone(enum_Axis eAxis, double dPos)
{
	double dCmdPos = SharedInfo::GetCmdPos(eAxis);
	return (IsSamePosition(dCmdPos, dPos) && IsMotionDone(eAxis));
}

#pragma region //Clamp On
//Move
BOOL CClampMotion::ClampOn(enum_eGRIPPER_ROW eRow) //한쌍으로
{
#if 1
	//double dTorque = CManualData::m_ManualDataClamp.Clamp.m_dClampTorque;
	//double dVel = 5;
	//int StartIndex = AXIS_GRIPPER_CLAMP_L1; //!!
	//int nType = 0, nAxis = -1;
	//BOOL bSelectGripper[GRIPPER_ROW];
	//int nSelectRowIndex = 0;

	////eAxis = (enum_Axis)m_nClampAxisL[0];
	//SharedInfo::GetActualAxisNoByEnumAxis((enum_Axis)StartIndex, &nType, &nAxis);

	//nSelectRowIndex = (1 << eRow);

	//Devs::MotionIf.ClampTorqueMove(nSelectRowIndex, nAxis, dTorque, dVel, 1, 1, 1);

	//Sleep(PC_COM_AJIN_MOTION_DELAY);
#endif
	//21.02.02 sjc add
	int i = eRow;
	SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_L1_OPEN_SOL + (i * 2)), FALSE);
	Sleep(1);
	SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_R1_OPEN_SOL + (i * 2)), FALSE);
	Sleep(1);
	SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_L1_CLOSE_SOL + (i * 2)), TRUE);
	Sleep(1);
	SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_R1_CLOSE_SOL + (i * 2)), TRUE);
	Sleep(1);	

	return TRUE;
}
BOOL CClampMotion::ClampOn_Active()
{
#if 1
	//double dTorque = CManualData::m_ManualDataClamp.Clamp.m_dClampTorque;
	//double dVel = 5;
	//int StartIndex = AXIS_GRIPPER_CLAMP_L1; //!!
	//int nType = 0, nAxis = -1;
	//BOOL bSelectGripper[GRIPPER_ROW];
	//int nSelectRowIndex = 0;

	////eAxis = (enum_Axis)m_nClampAxisL[0];
	//SharedInfo::GetActualAxisNoByEnumAxis((enum_Axis)StartIndex, &nType, &nAxis);

	for (int i = 0; i < GRIPPER_ROW; i++)
	{
		if (CModelData::m_StretchPara.Info.bStretchUse[i])
		{
			//nSelectRowIndex |= (1 << i);
			//21.02.02 sjc
			SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_L1_OPEN_SOL + (i * 2)), FALSE);
			Sleep(1);
			SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_R1_OPEN_SOL + (i * 2)), FALSE);
			Sleep(1);
			SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_L1_CLOSE_SOL + (i * 2)), TRUE);
			Sleep(1);
			SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_R1_CLOSE_SOL + (i * 2)), TRUE);
			Sleep(1);
		}			
	}

	//Devs::MotionIf.ClampTorqueMove(nSelectRowIndex, nAxis, dTorque, dVel, 1, 1, 1);

	Sleep(PC_COM_AJIN_MOTION_DELAY);
#endif
	return TRUE;
}
BOOL CClampMotion::ClampOn_All()
{
#if 1
	//double dTorque = CManualData::m_ManualDataClamp.Clamp.m_dClampTorque;
	//double dVel = 5;
	//int StartIndex = AXIS_GRIPPER_CLAMP_L1; //!!
	//int nType = 0, nAxis = -1;
	//BOOL bSelectGripper[GRIPPER_ROW];
	//int nSelectRowIndex = 0xFF;

	////eAxis = (enum_Axis)m_nClampAxisL[0];
	//SharedInfo::GetActualAxisNoByEnumAxis((enum_Axis)StartIndex, &nType, &nAxis);

	//Devs::MotionIf.ClampTorqueMove(nSelectRowIndex, nAxis, dTorque, dVel, 1, 1, 1);

	//Sleep(PC_COM_AJIN_MOTION_DELAY);
#endif
	//21.02.02 sjc add
	for (int i = 0; i < GRIPPER_ROW; i++)
	{
		SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_L1_OPEN_SOL + (i * 2)), FALSE);
		Sleep(1);
		SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_R1_OPEN_SOL + (i * 2)), FALSE);
		Sleep(1);
		SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_L1_CLOSE_SOL + (i * 2)), TRUE);
		Sleep(1);
		SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_R1_CLOSE_SOL + (i * 2)), TRUE);
		Sleep(1);
	}

	return TRUE;
}
//MoveDone Check
BOOL CClampMotion::Is_ClampOn(enum_eGRIPPER_ROW eRow)
{
#ifdef SIM_MODE
	return TRUE;
#endif


	BOOL clampOn = TRUE, clampOff = TRUE;
	int i = eRow;
	////if (CModelData::m_StretchPara.Info.bStretchUse[i])
	////{
	//	clampOff = clampOff && SharedInfo::DInputValue[_DIN_GRIPPER_L1_OPEN_DETECT_SENSOR1 + (i * 2)]
	//		&& SharedInfo::DInputValue[_DIN_GRIPPER_R1_OPEN_DETECT_SENSOR1 + (i * 2)];
	//	clampOn = clampOn && SharedInfo::DInputValue[_DIN_GRIPPER_L1_CLOSE_DETECT_SENSOR1 + (i * 2)]
	//		&& SharedInfo::DInputValue[_DIN_GRIPPER_R1_CLOSE_DETECT_SENSOR1 + (i * 2)];
	////}

	return (!clampOff && clampOn);
}
BOOL CClampMotion::Is_ClampOn_Active()
{
#ifdef SIM_MODE
	return FALSE;
#endif

	//for (int i = 0; i < GRIPPER_ROW; i++)
	//{
	//	if (CModelData::m_StretchPara.Info.bStretchUse[i])
	//	{
	//		if (fabs(SharedInfo::m_nClampTorquedMonitorValue[i] - CManualData::m_ManualDataClamp.Clamp.m_dClampTorque) > 0.01 ||
	//			fabs(SharedInfo::m_nClampTorquedMonitorValue[i + GRIPPER_ROW] - CManualData::m_ManualDataClamp.Clamp.m_dClampTorque) > 0.01)
	//			return FALSE;
	//	}
	//}

	//return TRUE;
	//21.02.02 sjc add
	BOOL clampOn = TRUE, clampOff = TRUE;
	//for (int i = 0; i < GRIPPER_ROW; i++)
	//{
	//	if (CModelData::m_StretchPara.Info.bStretchUse[i])
	//	{
	//		clampOff = clampOff && SharedInfo::DInputValue[_DIN_GRIP_L1_OPEN_DETECT_SENSOR + (i * 2)]
	//			&& SharedInfo::DInputValue[_DIN_GRIP_R1_OPEN_DETECT_SENSOR + (i * 2)];
	//		clampOn = clampOn && SharedInfo::DInputValue[_DIN_GRIP_L1_CLOSE_DETECT_SENSOR + (i * 2)]
	//			&& SharedInfo::DInputValue[_DIN_GRIP_R1_CLOSE_DETECT_SENSOR + (i * 2)];
	//	}
	//}
	return (!clampOff && clampOn);
}
BOOL CClampMotion::Is_ClampOn_All()
{
#ifdef SIM_MODE
	return TRUE;
#endif

	//for (int i = 0; i < GRIPPER_ROW; i++)
	//{
	//	if (fabs(SharedInfo::m_nClampTorquedMonitorValue[i] - CManualData::m_ManualDataClamp.Clamp.m_dClampTorque) > 0.01 ||
	//		fabs(SharedInfo::m_nClampTorquedMonitorValue[i + GRIPPER_ROW] - CManualData::m_ManualDataClamp.Clamp.m_dClampTorque) > 0.01)
	//		return FALSE;
	//}
	//21.02.02 sjc add
	BOOL clampOn = TRUE, clampOff = TRUE;
	//for (int i = 0; i < GRIPPER_ROW; i++)
	//{
	//	clampOff = clampOff && SharedInfo::DInputValue[_DIN_GRIP_L1_OPEN_DETECT_SENSOR + (i * 2)]
	//		&& SharedInfo::DInputValue[_DIN_GRIP_R1_OPEN_DETECT_SENSOR + (i * 2)];
	//	clampOn = clampOn && SharedInfo::DInputValue[_DIN_GRIP_L1_CLOSE_DETECT_SENSOR + (i * 2)]
	//		&& SharedInfo::DInputValue[_DIN_GRIP_R1_CLOSE_DETECT_SENSOR + (i * 2)];
	//}
	return (!clampOff && clampOn);
	//return TRUE;
}
#pragma endregion

#pragma region //Clamp Off
//Move
BOOL CClampMotion::ClampOff(enum_eGRIPPER_ROW eRow)
{
	CString Str = _T("");
	//double dVel = 5;
	////Torquq mode stop	
	//double dPos;
	//int StartIndex;
	//enum_Axis eAxis = AXIS_NONE;
	//int nType = 0, nAxis = -1;

	//eAxis = (enum_Axis)(AXIS_GRIPPER_CLAMP_L1); //!!
	//SharedInfo::GetActualAxisNoByEnumAxis(eAxis, &nType, &nAxis);
	//StartIndex = nAxis;
	//int CurrentGripperUseIndex = (1 << eRow);

	//Devs::MotionIf.ClampTorqueMoveStop(CurrentGripperUseIndex, StartIndex, 0);

	//21.02.02 sjc add
	int i = eRow;
	SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_L1_OPEN_SOL + (i * 2)), FALSE);
	Sleep(1);
	SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_R1_OPEN_SOL + (i * 2)), FALSE);
	Sleep(1);
	SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_L1_CLOSE_SOL + (i * 2)), TRUE);
	Sleep(1);
	SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_R1_CLOSE_SOL + (i * 2)), TRUE);
	Sleep(1);

	Str.Format(_T("Clamp Off %dRow"), eRow + 1);
	Total_Msg(Str);
	return TRUE;
}
BOOL CClampMotion::ClampOff_Active()
{
	//double dVel = 5;
	////Torquq mode stop	
	//double dPos;
	//int StartIndex;
	//enum_Axis eAxis = AXIS_NONE;
	//int nType = 0, nAxis = -1;

	//eAxis = (enum_Axis)(AXIS_GRIPPER_CLAMP_L1); //!!
	//SharedInfo::GetActualAxisNoByEnumAxis(eAxis, &nType, &nAxis);
	//StartIndex = nAxis;
	//int CurrentGripperUseIndex = 0;

	for (int i = 0; i < MAX_STRETCH_SIZE; i++)
	{
		if (CModelData::m_StretchPara.Info.bStretchUse[i])
		{
			//CurrentGripperUseIndex |= (1 << i);
			SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_L1_CLOSE_SOL + (i * 2)), FALSE);
			Sleep(1);
			SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_R1_CLOSE_SOL + (i * 2)), FALSE);
			Sleep(1);
			SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_L1_OPEN_SOL + (i * 2)), TRUE);
			Sleep(1);
			SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_R1_OPEN_SOL + (i * 2)), TRUE);
			Sleep(1);
		}
	}

	//Devs::MotionIf.ClampTorqueMoveStop(CurrentGripperUseIndex, StartIndex, 0);

	Total_Msg(_T("Clamp Off Active"));
	return TRUE;
}
BOOL CClampMotion::ClampOff_All()
{
	//double dVel = 5;
	////Torquq mode stop	
	//double dPos;
	//int StartIndex;
	//enum_Axis eAxis = AXIS_NONE;
	//int nType = 0, nAxis = -1;

	//eAxis = (enum_Axis)(AXIS_GRIPPER_CLAMP_L1); //!!
	//SharedInfo::GetActualAxisNoByEnumAxis(eAxis, &nType, &nAxis);
	//StartIndex = nAxis;

	//int CurrentGripperUseIndex = 0xFF;
	//BOOL bCheckFlag = FALSE;

	//Devs::MotionIf.ClampTorqueMoveStop(CurrentGripperUseIndex, StartIndex, 0);
	//21.02.02 sjc add
	for (int i = 0; i < GRIPPER_ROW; i++)
	{
		SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_L1_CLOSE_SOL + (i * 2)), FALSE);
		Sleep(10);
		SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_R1_CLOSE_SOL + (i * 2)), FALSE);
		Sleep(10);
		SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_L1_OPEN_SOL + (i * 2)), TRUE);
		Sleep(10);
		SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_R1_OPEN_SOL + (i * 2)), TRUE);
		Sleep(10);
	}
	Total_Msg(_T("Clamp Off All"));
	return TRUE;
}
//MoveDone Check
BOOL CClampMotion::Is_ClampOff(enum_eGRIPPER_ROW eRow)
{
#ifdef SIM_MODE
	return TRUE;
#endif

	//if (SharedInfo::AxisInMotionStatus[REMOTE_AXIS_AJIN_GRIPPER_CLAMP_L1 + eRow] == 0 &&
	//	SharedInfo::AxisInMotionStatus[REMOTE_AXIS_AJIN_GRIPPER_CLAMP_R1 + eRow] == 0)
	//{
	//	if (fabs(SharedInfo::GetActPos((enum_Axis)(AXIS_GRIPPER_CLAMP_L1 + eRow)) - 0.) < 0.01 &&
	//		fabs(SharedInfo::GetActPos((enum_Axis)(AXIS_GRIPPER_CLAMP_R1 + eRow)) - 0.) < 0.01)
	//		return TRUE;
	//}

	//21.02.02 sjc add
	BOOL clampOn = TRUE, clampOff = TRUE;
	int i = eRow;
	//if (CModelData::m_StretchPara.Info.bStretchUse[i])
	//{
	//	clampOff = clampOff && SharedInfo::DInputValue[_DIN_GRIP_L1_OPEN_DETECT_SENSOR + (i * 2)]
	//		&& SharedInfo::DInputValue[_DIN_GRIP_R1_OPEN_DETECT_SENSOR + (i * 2)];
	//	clampOn = clampOn && SharedInfo::DInputValue[_DIN_GRIP_L1_CLOSE_DETECT_SENSOR + (i * 2)]
	//		&& SharedInfo::DInputValue[_DIN_GRIP_R1_CLOSE_DETECT_SENSOR + (i * 2)];
	////}
	
	return (clampOff && !clampOn);

	return FALSE;
}
//21.04.03 sjc
BOOL CClampMotion::Is_ClampOff_Left(enum_eGRIPPER_ROW eRow)
{
#ifdef SIM_MODE
	return TRUE;
#endif
	//21.02.02 sjc add
	BOOL clampOn = TRUE, clampOff = TRUE;
	int i = eRow;
	//if (CModelData::m_StretchPara.Info.bStretchUse[i])
	////{
	//clampOff = clampOff && SharedInfo::DInputValue[_DIN_GRIP_L1_OPEN_DETECT_SENSOR + (i * 2)];
	//clampOn = clampOn && SharedInfo::DInputValue[_DIN_GRIP_L1_CLOSE_DETECT_SENSOR + (i * 2)];
	////}

	return (clampOff && !clampOn);

	return FALSE;
}
BOOL CClampMotion::Is_ClampOff_Right(enum_eGRIPPER_ROW eRow)
{
#ifdef SIM_MODE
	return TRUE;
#endif
	//21.02.02 sjc add
	BOOL clampOn = TRUE, clampOff = TRUE;
	int i = eRow;
	//if (CModelData::m_StretchPara.Info.bStretchUse[i])
	//{
	//clampOff = clampOff && SharedInfo::DInputValue[_DIN_GRIP_R1_OPEN_DETECT_SENSOR + (i * 2)];
	//clampOn = clampOn && SharedInfo::DInputValue[_DIN_GRIP_R1_CLOSE_DETECT_SENSOR + (i * 2)];
	//}

	return (clampOff && !clampOn);

	return FALSE;
}
BOOL CClampMotion::Is_ClampOff_Active()
{
#ifdef SIM_MODE
	return FALSE;
#endif

	//for (int i = 0; i < MAX_STRETCH_SIZE; i++)
	//{
	//	if (CModelData::m_StretchPara.Info.bStretchUse[i])
	//	{
	//		//if (SharedInfo::AxisInMotionStatus[REMOTE_AXIS_AJIN_GRIPPER_CLAMP_L1 + i] == 0 &&
	//		//	SharedInfo::AxisInMotionStatus[REMOTE_AXIS_AJIN_GRIPPER_CLAMP_R1 + i] == 0)
	//		{
	//			if (fabs(SharedInfo::GetActPos((enum_Axis)(AXIS_GRIPPER_CLAMP_L1 + i)) - 0.) > 0.01 ||
	//				fabs(SharedInfo::GetActPos((enum_Axis)(AXIS_GRIPPER_CLAMP_R1 + i)) - 0.) > 0.01)
	//				return FALSE;
	//		}
	//	}
	//}

	//return TRUE;
		//21.02.02 sjc add
	BOOL clampOn = TRUE, clampOff = TRUE;
	//for (int i = 0; i < GRIPPER_ROW; i++)
	//{
	//	if (CModelData::m_StretchPara.Info.bStretchUse[i])
	//	{
	//		clampOff = clampOff && SharedInfo::DInputValue[_DIN_GRIP_L1_OPEN_DETECT_SENSOR + (i * 2)]
	//			&& SharedInfo::DInputValue[_DIN_GRIP_R1_OPEN_DETECT_SENSOR + (i * 2)];
	//		clampOn = clampOn && SharedInfo::DInputValue[_DIN_GRIP_L1_CLOSE_DETECT_SENSOR + (i * 2)]
	//			&& SharedInfo::DInputValue[_DIN_GRIP_R1_CLOSE_DETECT_SENSOR + (i * 2)];
	//	}
	//}
	return (clampOff && !clampOn);
}
BOOL CClampMotion::Is_ClampOff_All()
{
#ifdef SIM_MODE
	return TRUE;
#endif

	//for (int i = 0; i < MAX_STRETCH_SIZE; i++)
	//{
	//	//if (SharedInfo::AxisInMotionStatus[REMOTE_AXIS_AJIN_GRIPPER_CLAMP_L1 + i] == 0 &&
	//	//	SharedInfo::AxisInMotionStatus[REMOTE_AXIS_AJIN_GRIPPER_CLAMP_R1 + i] == 0)
	//	{
	//		if (fabs(SharedInfo::GetActPos((enum_Axis)(AXIS_GRIPPER_CLAMP_L1 + i)) - 0.) > 0.01 ||
	//			fabs(SharedInfo::GetActPos((enum_Axis)(AXIS_GRIPPER_CLAMP_R1 + i)) - 0.) > 0.01)
	//			return FALSE;
	//	}
	//}

	//21.02.02 sjc add
	BOOL clampOn = TRUE, clampOff = TRUE;
	//for (int i = 0; i < GRIPPER_ROW; i++)
	//{
	//	clampOff = clampOff && SharedInfo::DInputValue[_DIN_GRIP_L1_OPEN_DETECT_SENSOR + (i * 2)]
	//		&& SharedInfo::DInputValue[_DIN_GRIP_R1_OPEN_DETECT_SENSOR + (i * 2)];
	//	clampOn = clampOn && SharedInfo::DInputValue[_DIN_GRIP_L1_CLOSE_DETECT_SENSOR + (i * 2)]
	//		&& SharedInfo::DInputValue[_DIN_GRIP_R1_CLOSE_DETECT_SENSOR + (i * 2)];
	//}
	return (clampOff && !clampOn);
}

BOOL CClampMotion::Is_ClampOff_Active_L()
{
#ifdef SIM_MODE
	return FALSE;
#endif
	//21.02.04 sjc
	BOOL clampOn = TRUE, clampOff = TRUE;
	//for (int i = 0; i < GRIPPER_ROW; i++)
	//{
	//	if (CModelData::m_StretchPara.Info.bStretchUse[i])
	//	{
	//		clampOff = clampOff && SharedInfo::DInputValue[_DIN_GRIP_L1_OPEN_DETECT_SENSOR + (i * 2)];
	//		clampOn = clampOn && SharedInfo::DInputValue[_DIN_GRIP_L1_CLOSE_DETECT_SENSOR + (i * 2)];
	//	}
	//}
	return (clampOff && !clampOn);

	//for (int i = 0; i < MAX_STRETCH_SIZE; i++)
	//{
	//	if (CModelData::m_StretchPara.Info.bStretchUse[i])
	//	{
	//		//if (SharedInfo::AxisInMotionStatus[REMOTE_AXIS_AJIN_GRIPPER_CLAMP_R1 + i] == 0)
	//		{
	//			if (fabs(SharedInfo::GetActPos((enum_Axis)(AXIS_GRIPPER_CLAMP_R1 + i)) - 0.) > 0.01)
	//				return FALSE;
	//		}
	//	}
	//}

	//return TRUE;
}

BOOL CClampMotion::Is_ClampOff_Active_R()
{
#ifdef SIM_MODE
	return FALSE;
#endif
	//21.02.04 sjc
	BOOL clampOn = TRUE, clampOff = TRUE;
	//for (int i = 0; i < GRIPPER_ROW; i++)
	//{
	//	if (CModelData::m_StretchPara.Info.bStretchUse[i])
	//	{
	//		clampOff = clampOff && SharedInfo::DInputValue[_DIN_GRIP_R1_OPEN_DETECT_SENSOR + (i * 2)];
	//		clampOn = clampOn && SharedInfo::DInputValue[_DIN_GRIP_R1_CLOSE_DETECT_SENSOR + (i * 2)];
	//	}
	//}
	return (clampOff && !clampOn);

	//for (int i = 0; i < MAX_STRETCH_SIZE; i++)
	//{
	//	if (CModelData::m_StretchPara.Info.bStretchUse[i])
	//	{
	//		//if (SharedInfo::AxisInMotionStatus[REMOTE_AXIS_AJIN_GRIPPER_CLAMP_R1 + i] == 0)
	//		{
	//			if (fabs(SharedInfo::GetActPos((enum_Axis)(AXIS_GRIPPER_CLAMP_R1 + i)) - 0.) > 0.01)
	//				return FALSE;
	//		}
	//	}
	//}

	//return TRUE;
}
#pragma endregion