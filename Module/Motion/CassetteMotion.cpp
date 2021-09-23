#include "stdafx.h"
#include "CassetteMotion.h"
#include "Vision/Devs.h"
#include "Vision/SharedInfo.h"
#include "CalcAlign/CalcAlign.h"
#include "Log/Logger.h"
#include "Data/ManualData.h"

CCassetteMotion::CCassetteMotion()
{
}


CCassetteMotion::~CCassetteMotion()
{
}

BOOL CCassetteMotion::InitProcess()
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

BOOL CCassetteMotion::EndProcess()
{
	int i = 0;

	m_StateFinish = FALSE;

	SetStep(eCASSETTE_MOTION_IDLE, FALSE);

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

BOOL CCassetteMotion::Start()
{
	m_bMotionDone = FALSE;
	m_bStopBit = FALSE;
	m_nCurStep = eCASSETTE_MOTION_START;
	SetStep(m_nCurStep, _T("m_nCurStep"));
	return TRUE;
}

BOOL CCassetteMotion::Stop()
{
	m_bStopBit = TRUE;
	SetStop(); //!!
	return TRUE;
}

UINT CCassetteMotion::MotionThreadFunction(LPVOID lpParam)
{
	CCassetteMotion* pCassetteMotion = NULL;

	pCassetteMotion = (CCassetteMotion*)lpParam;

	pCassetteMotion->MotionThreadFunctionEntry();

	pCassetteMotion->m_bTerminate = 1;

	return 0;
}

VOID CCassetteMotion::MotionThreadFunctionEntry(VOID)
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

			SetCurrentStep(eCASSETTE_MOTION_START); //KJT 20210318
			continue; //!!
		}
	

		switch (GetCurrentTotalStep())
		{
		case eCASSETTE_MOTION_START:
			SetStep(eCASSETTE_MOTION_DONE, _T("eCASSETTE_MOTION_DONE"));
			break;

			////

		case eCASSETTE_MOTION_DONE:
			m_bMotionDone = TRUE;
			SetStep(eCASSETTE_MOTION_IDLE, _T("eCASSETTE_MOTION_IDLE"));
			break;

		case eCASSETTE_MOTION_EXIT:
			m_StateFinish = FALSE;
			break;
		}
	}
}

BOOL CCassetteMotion::IsAxisHome(UINT nAxisNo)
{
	return SharedInfo::AxisHomeStatus[nAxisNo];
}

BOOL CCassetteMotion::MoveAxis(enum_Axis eAxis, double dPos)
{
	double	dSpeed = 0.0, dAccel = 0.0, dDecel = 0.0;

	//현재 모터의 파라미터 받아오기
	if (!GetAxisWorkParam(eAxis, &dSpeed, &dAccel, &dDecel)) return FALSE;
	//해당 모터에 파라미터 전달
	AbsMove(eAxis, dPos, dSpeed, dAccel, dDecel);
	return TRUE;
}
BOOL CCassetteMotion::IsMoveDone(enum_Axis eAxis, double dPos)
{
	double dCmdPos = SharedInfo::GetCmdPos(eAxis);
	return (IsSamePosition(dCmdPos, dPos) && IsMotionDone(eAxis));
}

#pragma region //Cassette Z
//Move
BOOL CCassetteMotion::CassetteZ_MoveFloor(enum_CassetteFloor eFloor)
{
	CString Str = _T("");
	double dPos = 0.0;

	if (eFloor < eCASSETTE_FLOOR_1 || eFloor > eCASSETTE_FLOOR_4)
	{
		Str.Format(_T("Check Target Floor !!!"));
		Total_Msg(Str);
		return FALSE;
	}

	if (Devs::m_CassetteMotion.Is_CSTPickUpUnitBwd() == FALSE)
	{
		Str.Format(_T("Check Pickup Unit Backward !!!"));
		Total_Msg(Str);
		return FALSE;
	}

	if (Devs::m_CassetteMotion.Is_CSTSafefySensorOn() == TRUE)
	{
		Str.Format(_T("Check CST Safety Sensor !!!"));
		Total_Msg(Str);
		return FALSE;
	}

	if (Devs::m_CassetteMotion.Is_CSTPaperSensorOn() == TRUE)
	{
		Str.Format(_T("Check CST Detect Pickup Sensor !!!"));
		Total_Msg(Str);
		return FALSE;
	}

	enum_Axis eAxis = AXIS_MAGAZINE_LIFT_Z;
	if (eFloor == eCASSETTE_FLOOR_1)
	{
		dPos = CManualData::m_ManualDataCassette.Info.m_dCassetteZ_1Floor_Pos;
		Str.Format(_T("Cassette Z Move To Floor1 Pos (Pos : %.5f)"), dPos);
	}
	else if (eFloor == eCASSETTE_FLOOR_2)
	{
		dPos = CManualData::m_ManualDataCassette.Info.m_dCassetteZ_2Floor_Pos;
		Str.Format(_T("Cassette Z Move To Floor2 Pos (Pos : %.5f)"), dPos);
	}
	else if (eFloor == eCASSETTE_FLOOR_3)
	{
		dPos = CManualData::m_ManualDataCassette.Info.m_dCassetteZ_3Floor_Pos;
		Str.Format(_T("Cassette Z Move To Floor3 Pos (Pos : %.5f)"), dPos);
	}
	else if (eFloor == eCASSETTE_FLOOR_4)
	{
		dPos = CManualData::m_ManualDataCassette.Info.m_dCassetteZ_4Floor_Pos;
		Str.Format(_T("Cassette Z Move To Floor4 Pos (Pos : %.5f)"), dPos);
	}
	
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Total_Msg(Str);
	}

	return bRtn;
}
BOOL CCassetteMotion::CassetteZ_WaitPos()
{
	CString Str = _T("");

	if (Devs::m_CassetteMotion.Is_CSTPickUpUnitBwd() == FALSE)
	{
		Str.Format(_T("Check Pickup Unit Backward !!!"));
		Total_Msg(Str);
		return FALSE;
	}

	if (Devs::m_CassetteMotion.Is_CSTSafefySensorOn() == TRUE)
	{
		Str.Format(_T("Check CST Safety Sensor !!!"));
		Total_Msg(Str);
		return FALSE;
	}

	if (Devs::m_CassetteMotion.Is_CSTPaperSensorOn() == TRUE)
	{
		Str.Format(_T("Check CST Detect Pickup Sensor !!!"));
		Total_Msg(Str);
		return FALSE;
	}

	enum_Axis eAxis = AXIS_MAGAZINE_LIFT_Z;
	double dPos = CManualData::m_ManualDataCassette.Info.m_dCassetteZ_Wait_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Cassette Z Move To Wait Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
BOOL CCassetteMotion::CassetteZ_1FloorPos()
{
	CString Str = _T("");

	if (Devs::m_CassetteMotion.Is_CSTPickUpUnitBwd() == FALSE)
	{
		Str.Format(_T("Check Pickup Unit Backward !!!"));
		Total_Msg(Str);
		return FALSE;
	}

	if (Devs::m_CassetteMotion.Is_CSTSafefySensorOn() == TRUE)
	{
		Str.Format(_T("Check CST Safety Sensor !!!"));
		Total_Msg(Str);
		return FALSE;
	}

	if (Devs::m_CassetteMotion.Is_CSTPaperSensorOn() == TRUE)
	{
		Str.Format(_T("Check CST Detect Pickup Sensor !!!"));
		Total_Msg(Str);
		return FALSE;
	}

	enum_Axis eAxis = AXIS_MAGAZINE_LIFT_Z;
	double dPos = CManualData::m_ManualDataCassette.Info.m_dCassetteZ_1Floor_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Cassette Z Move To 1Floor Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
BOOL CCassetteMotion::CassetteZ_2FloorPos()
{
	CString Str = _T("");

	if (Devs::m_CassetteMotion.Is_CSTPickUpUnitBwd() == FALSE)
	{
		Str.Format(_T("Check Pickup Unit Backward !!!"));
		Total_Msg(Str);
		return FALSE;
	}

	if (Devs::m_CassetteMotion.Is_CSTSafefySensorOn() == TRUE)
	{
		Str.Format(_T("Check CST Safety Sensor !!!"));
		Total_Msg(Str);
		return FALSE;
	}

	if (Devs::m_CassetteMotion.Is_CSTPaperSensorOn() == TRUE)
	{
		Str.Format(_T("Check CST Detect Pickup Sensor !!!"));
		Total_Msg(Str);
		return FALSE;
	}


	enum_Axis eAxis = AXIS_MAGAZINE_LIFT_Z;
	double dPos = CManualData::m_ManualDataCassette.Info.m_dCassetteZ_2Floor_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Cassette Z Move To 2Floor Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
BOOL CCassetteMotion::CassetteZ_3FloorPos()
{
	CString Str = _T("");
	
	if (Devs::m_CassetteMotion.Is_CSTPickUpUnitBwd() == FALSE)
	{
		Str.Format(_T("Check Pickup Unit Backward !!!"));
		Total_Msg(Str);
		return FALSE;
	}

	if (Devs::m_CassetteMotion.Is_CSTSafefySensorOn() == TRUE)
	{
		Str.Format(_T("Check CST Safety Sensor !!!"));
		Total_Msg(Str);
		return FALSE;
	}

	if (Devs::m_CassetteMotion.Is_CSTPaperSensorOn() == TRUE)
	{
		Str.Format(_T("Check CST Detect Pickup Sensor !!!"));
		Total_Msg(Str);
		return FALSE;
	}

	enum_Axis eAxis = AXIS_MAGAZINE_LIFT_Z;
	double dPos = CManualData::m_ManualDataCassette.Info.m_dCassetteZ_3Floor_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Cassette Z Move To 3Floor Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
BOOL CCassetteMotion::CassetteZ_4FloorPos()
{
	CString Str = _T("");

	if (Devs::m_CassetteMotion.Is_CSTPickUpUnitBwd() == FALSE)
	{
		Str.Format(_T("Check Pickup Unit Backward !!!"));
		Total_Msg(Str);
		return FALSE;
	}

	if (Devs::m_CassetteMotion.Is_CSTSafefySensorOn() == TRUE)
	{
		Str.Format(_T("Check CST Safety Sensor !!!"));
		Total_Msg(Str);
		return FALSE;
	}

	if (Devs::m_CassetteMotion.Is_CSTPaperSensorOn() == TRUE)
	{
		Str.Format(_T("Check CST Detect Pickup Sensor !!!"));
		Total_Msg(Str);
		return FALSE;
	}

	enum_Axis eAxis = AXIS_MAGAZINE_LIFT_Z;
	double dPos = CManualData::m_ManualDataCassette.Info.m_dCassetteZ_4Floor_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Cassette Z Move To 4Floor Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
#if 0 //Junying TPCD Floor1~4 Use
BOOL CCassetteMotion::CassetteZ_5FloorPos()
{
	CString Str = _T("");

	if (Devs::m_CassetteMotion.Is_CSTPickUpUnitBwd() == FALSE)
	{
		Str.Format(_T("Check Pickup Unit Backward !!!"));
		Total_Msg(Str);
		return FALSE;
	}

	if (Devs::m_CassetteMotion.Is_CSTSafefySensorOn() == TRUE)
	{
		Str.Format(_T("Check CST Safety Sensor !!!"));
		Total_Msg(Str);
		return FALSE;
	}

	enum_Axis eAxis = AXIS_MAGAZINE_LIFT_Z;
	double dPos = CManualData::m_ManualDataCassette.Info.m_dCassetteZ_5Floor_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Cassette Z Move To 5Floor Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
BOOL CCassetteMotion::CassetteZ_6FloorPos()
{
	CString Str = _T("");

	if (Devs::m_CassetteMotion.Is_CSTPickUpUnitBwd() == FALSE)
	{
		Str.Format(_T("Check Pickup Unit Backward !!!"));
		Total_Msg(Str);
		return FALSE;
	}

	if (Devs::m_CassetteMotion.Is_CSTSafefySensorOn() == TRUE)
	{
		Str.Format(_T("Check CST Safety Sensor !!!"));
		Total_Msg(Str);
		return FALSE;
	}

	enum_Axis eAxis = AXIS_MAGAZINE_LIFT_Z;
	double dPos = CManualData::m_ManualDataCassette.Info.m_dCassetteZ_6Floor_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Cassette Z Move To 6Floor Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
#endif
//MoveDone Check
BOOL CCassetteMotion::Is_CassetteZ_Floor(enum_CassetteFloor eFloor)
{
	enum_Axis eAxis = AXIS_MAGAZINE_LIFT_Z;

	if (eFloor == eCASSETTE_FLOOR_1)
	{
		double dPos = CManualData::m_ManualDataCassette.Info.m_dCassetteZ_1Floor_Pos;
		return IsMoveDone(eAxis, dPos);
	}
	else if (eFloor == eCASSETTE_FLOOR_2)
	{
		double dPos = CManualData::m_ManualDataCassette.Info.m_dCassetteZ_2Floor_Pos;
		return IsMoveDone(eAxis, dPos);
	}
	else if (eFloor == eCASSETTE_FLOOR_3)
	{
		double dPos = CManualData::m_ManualDataCassette.Info.m_dCassetteZ_3Floor_Pos;
		return IsMoveDone(eAxis, dPos);
	}
	else if (eFloor == eCASSETTE_FLOOR_4)
	{
		double dPos = CManualData::m_ManualDataCassette.Info.m_dCassetteZ_4Floor_Pos;
		return IsMoveDone(eAxis, dPos);
	}
	else
		return FALSE;
}
BOOL CCassetteMotion::Is_CassetteZ_WaitPos()
{
	enum_Axis eAxis = AXIS_MAGAZINE_LIFT_Z;
	double dPos = CManualData::m_ManualDataCassette.Info.m_dCassetteZ_Wait_Pos;
	return IsMoveDone(eAxis, dPos);
}
BOOL CCassetteMotion::Is_CassetteZ_1FloorPos()
{
	enum_Axis eAxis = AXIS_MAGAZINE_LIFT_Z;
	double dPos = CManualData::m_ManualDataCassette.Info.m_dCassetteZ_1Floor_Pos;
	return IsMoveDone(eAxis, dPos);
}
BOOL CCassetteMotion::Is_CassetteZ_2FloorPos()
{
	enum_Axis eAxis = AXIS_MAGAZINE_LIFT_Z;
	double dPos = CManualData::m_ManualDataCassette.Info.m_dCassetteZ_2Floor_Pos;
	return IsMoveDone(eAxis, dPos);
}
BOOL CCassetteMotion::Is_CassetteZ_3FloorPos()
{
	enum_Axis eAxis = AXIS_MAGAZINE_LIFT_Z;
	double dPos = CManualData::m_ManualDataCassette.Info.m_dCassetteZ_3Floor_Pos;
	return IsMoveDone(eAxis, dPos);
}
BOOL CCassetteMotion::Is_CassetteZ_4FloorPos()
{
	enum_Axis eAxis = AXIS_MAGAZINE_LIFT_Z;
	double dPos = CManualData::m_ManualDataCassette.Info.m_dCassetteZ_4Floor_Pos;
	return IsMoveDone(eAxis, dPos);
}
#if 0 //Junying TPCD Floor1~4 Use
BOOL CCassetteMotion::Is_CassetteZ_5FloorPos()
{
	enum_Axis eAxis = AXIS_MAGAZINE_LIFT_Z;
	double dPos = CManualData::m_ManualDataCassette.Info.m_dCassetteZ_5Floor_Pos;
	return IsMoveDone(eAxis, dPos);
}
BOOL CCassetteMotion::Is_CassetteZ_6FloorPos()
{
	enum_Axis eAxis = AXIS_MAGAZINE_LIFT_Z;
	double dPos = CManualData::m_ManualDataCassette.Info.m_dCassetteZ_6Floor_Pos;
	return IsMoveDone(eAxis, dPos);
}
#endif
#pragma endregion

#pragma region //IO
BOOL CCassetteMotion::CSTPickUpUnitFwd()
{
	SetDOutputBitValue((enum_Do)(_DOUT_PICK_UNIT_BWD), FALSE);
	Sleep(500); //!!
	SetDOutputBitValue((enum_Do)(_DOUT_PICK_UNIT_FWD), TRUE);

	Total_Msg(_T("CST PickUp Unit Fwd"));
	return TRUE;
}
BOOL CCassetteMotion::CSTPickUpUnitBwd()
{
	SetDOutputBitValue((enum_Do)(_DOUT_PICK_UNIT_FWD), FALSE);
	Sleep(500);
	SetDOutputBitValue((enum_Do)(_DOUT_PICK_UNIT_BWD), TRUE);

	Total_Msg(_T("CST PickUp Unit Bwd"));
	return TRUE;
}
BOOL CCassetteMotion::CSTPickUpUnitClamp()
{
	SetDOutputBitValue((enum_Do)(_DOUT_PICK_UNIT_OPEN_SOL), FALSE);
	Sleep(500);
	SetDOutputBitValue((enum_Do)(_DOUT_PICK_UNIT_CLOSE_SOL), TRUE);

	Total_Msg(_T("CST PickUp Unit Clamp"));
	return TRUE;
}
BOOL CCassetteMotion::CSTPickUpUnitUnclamp()
{
	SetDOutputBitValue((enum_Do)(_DOUT_PICK_UNIT_CLOSE_SOL), FALSE);
	Sleep(500);
	SetDOutputBitValue((enum_Do)(_DOUT_PICK_UNIT_OPEN_SOL), TRUE);

	Total_Msg(_T("CST PickUp Unit Unclamp"));
	return TRUE;
}

BOOL CCassetteMotion::Is_CSTPickUpUnitFwd()
{
	if (SharedInfo::DInputValue[_DIN_PICK_UP_UNIT_BWD] == FALSE && SharedInfo::DInputValue[_DIN_PICK_UP_UNIT_FWD] == TRUE)
		return TRUE;
	else
		return FALSE;
}
BOOL CCassetteMotion::Is_CSTPickUpUnitBwd()
{
	if (SharedInfo::DInputValue[_DIN_PICK_UP_UNIT_FWD] == FALSE && SharedInfo::DInputValue[_DIN_PICK_UP_UNIT_BWD] == TRUE)
		return TRUE;
	else
		return FALSE;
}
BOOL CCassetteMotion::Is_CSTPickUpUnitClamp()
{
	if (SharedInfo::DInputValue[_DIN_PICK_UP_UNIT_UNCLAMP] == FALSE && SharedInfo::DInputValue[_DIN_PICK_UP_UNIT_CLAMP] == TRUE)
		return TRUE;
	else
		return FALSE;
}
BOOL CCassetteMotion::Is_CSTPickUpUnitUnclamp()
{
	if (SharedInfo::DInputValue[_DIN_PICK_UP_UNIT_CLAMP] == FALSE && SharedInfo::DInputValue[_DIN_PICK_UP_UNIT_UNCLAMP] == TRUE)
		return TRUE;
	else
		return FALSE;
}

BOOL CCassetteMotion::Is_CSTSafefySensorOn()
{
	if (SharedInfo::DInputValue[_DIN_MAGAZINE_EXIST_DETECT_L])
		return TRUE;
	else
		return FALSE;
}

BOOL CCassetteMotion::Is_CSTPaperSensorOn()
{
	if (SharedInfo::DInputValue[_DIN_MAGAZINE_EXIST_DETECT_R])
		return TRUE;
	else
		return FALSE;
}

BOOL CCassetteMotion::Is_CSTSafetyAndPaperSensorOn()
{
	if (SharedInfo::DInputValue[_DIN_MAGAZINE_EXIST_DETECT_L] && SharedInfo::DInputValue[_DIN_MAGAZINE_EXIST_DETECT_R])
		return TRUE;
	else
		return FALSE;
}

BOOL CCassetteMotion::CSTPaperBoxUnitFwd()
{	
	if (Devs::m_CassetteMotion.Is_CassetteZ_WaitPos() == FALSE)
	{
		Total_Msg(_T("Check Cassette Z Wait Pos !!!"));		
		return FALSE;
	}

	if (Devs::m_CassetteMotion.Is_CSTSafefySensorOn() == TRUE)
	{
		Total_Msg(_T("Check CST Safety Sensor !!!"));		
		return FALSE;
	}

	//SetDOutputBitValue((enum_Do)(_DOUT_PAPER_BOX_BWD), FALSE);
	//Sleep(500);
	//SetDOutputBitValue((enum_Do)(_DOUT_PAPER_BOX_FWD), TRUE);

	Total_Msg(_T("CST Paper Box Unit Fwd"));
	return TRUE;
}

BOOL CCassetteMotion::CSTPaperBoxUnitBwd()
{
	//SetDOutputBitValue((enum_Do)(_DOUT_PAPER_BOX_FWD), FALSE);
	//Sleep(500);
	//SetDOutputBitValue((enum_Do)(_DOUT_PAPER_BOX_BWD), TRUE);

	Total_Msg(_T("CST Paper Box Unit Bwd"));
	return TRUE;
}

BOOL CCassetteMotion::Is_CSTPaperBoxUnitFwd()
{	
	//if (SharedInfo::DInputValue[_DIN_ULD_PAPER_BOX_LEFT_FWD] == TRUE && SharedInfo::DInputValue[_DIN_ULD_PAPER_BOX_RIGHT_FWD] == TRUE)
		return TRUE;
	//else
	//	return FALSE;
}

BOOL CCassetteMotion::Is_CSTPaperBoxUnitBwd()
{
	//if (SharedInfo::DInputValue[_DIN_ULD_PAPER_BOX_LEFT_BWD] == TRUE && SharedInfo::DInputValue[_DIN_ULD_PAPER_BOX_RIGHT_BWD] == TRUE)
		return TRUE;
	//else
		//return FALSE;
}
#pragma endregion