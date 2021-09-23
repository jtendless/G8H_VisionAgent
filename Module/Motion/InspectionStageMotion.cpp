#include "stdafx.h"
#include "InspectionStageMotion.h"
#include "Vision/Devs.h"
#include "Vision/SharedInfo.h"
#include "CalcAlign/CalcAlign.h"
#include "Log/Logger.h"
#include "Data/MachineData.h"
#include "Data/ManualData.h"

CInspectionStageMotion::CInspectionStageMotion()
{
}


CInspectionStageMotion::~CInspectionStageMotion()
{
}

BOOL CInspectionStageMotion::InitProcess()
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

BOOL CInspectionStageMotion::EndProcess()
{
	int i = 0;

	m_StateFinish = FALSE;

	SetStep(eINSPECTION_STAGE_MOTION_IDLE, FALSE);

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

BOOL CInspectionStageMotion::Start()
{
	m_bMotionDone = FALSE;
	m_bStopBit = FALSE;
	m_nCurStep = eINSPECTION_STAGE_MOTION_START;
	SetStep(m_nCurStep, _T("m_nCurStep"));
	return TRUE;
}

BOOL CInspectionStageMotion::Stop()
{
	m_bStopBit = TRUE;
	SetStop(); //!!
	return TRUE;
}

UINT CInspectionStageMotion::MotionThreadFunction(LPVOID lpParam)
{
	CInspectionStageMotion* pInspectionStageMotion = NULL;

	pInspectionStageMotion = (CInspectionStageMotion*)lpParam;

	pInspectionStageMotion->MotionThreadFunctionEntry();

	pInspectionStageMotion->m_bTerminate = 1;

	return 0;
}

VOID CInspectionStageMotion::MotionThreadFunctionEntry(VOID)
{
	int ErrorCheck = 0;
	CString szMsg;
	double dPosX1 = 0.0, dPosX2 = 0.0, dPosY1 = 0.0, dPosY2 = 0.0;

	while (m_StateFinish)
	{
		WaitForSingleObject(hMotionHandle, INFINITE);
		ResetEvent(hMotionHandle);

		if (SharedInfo::bMachineStopFlag == TRUE)// && m_bStopBit == FALSE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(eINSPECTION_STAGE_MOTION_IDLE); //KJT 20210318
			continue; //!!
		}

		switch (GetCurrentTotalStep())
		{
		case eINSPECTION_STAGE_MOTION_IDLE:
			break;

		case eINSPECTION_STAGE_MOTION_START:
			SetStep(eINSPECTION_STAGE_MOTION_DONE, _T("eINSPECTION_STAGE_MOTION_DONE"));
			break;

#pragma region //UVW Home (X, Y1, Y2)
		case eINSPECTION_STAGE_ORIGIN_SERVO_ALL_OFF:
			ServoOnOff(AXIS_GLASS_UVW_Y1, FALSE);
			Sleep(300);
			ServoOnOff(AXIS_GLASS_UVW_Y2, FALSE);
			Sleep(300);
			ServoOnOff(AXIS_GLASS_UVW_X1, FALSE);
			Sleep(300);
			ServoOnOff(AXIS_GLASS_UVW_X2, FALSE);
			Sleep(300);

			SetCheckStep(eINSPECTION_STAGE_ORIGIN_SERVO_ALL_OFF_CHECK, _T("eINSPECTION_STAGE_ORIGIN_SERVO_ALL_OFF_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eINSPECTION_STAGE_ORIGIN_SERVO_ALL_OFF_CHECK:
			if (SharedInfo::AxisServoOnStatus[REMOTE_AXIS_GLASS_UVW_Y1] == 0 &&
				SharedInfo::AxisServoOnStatus[REMOTE_AXIS_GLASS_UVW_Y2] == 0 &&
				SharedInfo::AxisServoOnStatus[REMOTE_AXIS_GLASS_UVW_X1] == 0 &&
				SharedInfo::AxisServoOnStatus[REMOTE_AXIS_GLASS_UVW_X2] == 0)
			{
				SetStep(eINSPECTION_STAGE_ORIGIN_STAGE_Y1_Y2_SERVO_ON, _T("eINSPECTION_STAGE_ORIGIN_STAGE_Y1_Y2_SERVO_ON"));
			}
			else if (IsTimeOut())
			{
				//	SetAlarm(_T("ERROR : eINSPECTION_STAGE_ORIGIN_SERVO_ALL_OFF_CHECK"));
			}
			else
			{
				SetCheckStep(eINSPECTION_STAGE_ORIGIN_SERVO_ALL_OFF_CHECK, _T("eINSPECTION_STAGE_ORIGIN_SERVO_ALL_OFF_CHECK"));
			}
			break;

		case eINSPECTION_STAGE_ORIGIN_STAGE_Y1_Y2_SERVO_ON:
			Devs::MotionIf.AxisSetServoOnStatus(REMOTE_AXIS_GLASS_UVW_Y1, 1);
			Sleep(200);
			Devs::MotionIf.AxisSetServoOnStatus(REMOTE_AXIS_GLASS_UVW_Y2, 1);

			SetCheckStep(eINSPECTION_STAGE_ORIGIN_STAGE_Y1_Y2_SERVO_ON_CHECK, _T("eINSPECTION_STAGE_ORIGIN_STAGE_Y1_Y2_SERVO_ON_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eINSPECTION_STAGE_ORIGIN_STAGE_Y1_Y2_SERVO_ON_CHECK:
			if (SharedInfo::AxisServoOnStatus[REMOTE_AXIS_GLASS_UVW_Y1] == 1 &&
				SharedInfo::AxisServoOnStatus[REMOTE_AXIS_GLASS_UVW_Y2] == 1)
			{
				SetStep(eINSPECTION_STAGE_ORIGIN_Y1_Y2_START, _T("eINSPECTION_STAGE_ORIGIN_Y1_Y2_START"));
			}
			else if (IsTimeOut())
			{
				//SetAlarm(_T("ERROR : eINSPECTION_STAGE_ORIGIN_STAGE_Y1_Y2_SERVO_ON_CHECK"));
			}
			else
			{
				SetCheckStep(eINSPECTION_STAGE_ORIGIN_STAGE_Y1_Y2_SERVO_ON_CHECK, _T("eINSPECTION_STAGE_ORIGIN_STAGE_Y1_Y2_SERVO_ON_CHECK"));
			}
			break;

		case eINSPECTION_STAGE_ORIGIN_Y1_Y2_START:
			Devs::MotionIf.AxisHomeStart(REMOTE_AXIS_GLASS_UVW_Y1);
			Sleep(200);
			Devs::MotionIf.AxisHomeStart(REMOTE_AXIS_GLASS_UVW_Y2);
			Sleep(200);
			SetCheckStep(eINSPECTION_STAGE_ORIGIN_Y1_Y2_HOME_BIT_CHECK, _T("eINSPECTION_STAGE_ORIGIN_Y1_Y2_HOME_BIT_CHECK"));
			break;

		case eINSPECTION_STAGE_ORIGIN_Y1_Y2_HOME_BIT_CHECK:
			if (!IsAxisHome(REMOTE_AXIS_GLASS_UVW_Y1) && !IsAxisHome(REMOTE_AXIS_GLASS_UVW_Y2))
			{
				SetCheckStep(eINSPECTION_STAGE_ORIGIN_Y1_Y2_HOME_COMPLETE_CHECK, _T("eINSPECTION_STAGE_ORIGIN_Y1_Y2_HOME_COMPLETE_CHECK"));
			}
			else
			{
				SetCheckStep(eINSPECTION_STAGE_ORIGIN_Y1_Y2_HOME_BIT_CHECK, _T("eINSPECTION_STAGE_ORIGIN_Y1_Y2_HOME_BIT_CHECK"));
			}
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eINSPECTION_STAGE_ORIGIN_Y1_Y2_HOME_COMPLETE_CHECK:
			if (IsAxisHome(REMOTE_AXIS_GLASS_UVW_Y1) && IsAxisHome(REMOTE_AXIS_GLASS_UVW_Y2))
			{
				//SetStep(eINSPECTION_STAGE_ORIGIN_X_SERVO_ON, _T("eINSPECTION_STAGE_ORIGIN_X_SERVO_ON"));
				SetStep(eINSPECTION_STAGE_ORIGIN_Y1_Y2_ORIGIN_POS, _T("eINSPECTION_STAGE_ORIGIN_Y1_Y2_ORIGIN_POS"));
			}
			else if (IsTimeOut())
			{
				//SetAlarm(_T("ERROR : eINSPECTION_STAGE_ORIGIN_Y1_Y2_HOME_COMPLETE_CHECK"));
			}
			else
			{
				SetCheckStep(eINSPECTION_STAGE_ORIGIN_Y1_Y2_HOME_COMPLETE_CHECK, _T("eINSPECTION_STAGE_ORIGIN_Y1_Y2_HOME_COMPLETE_CHECK"));
			}
			break;

		case eINSPECTION_STAGE_ORIGIN_Y1_Y2_ORIGIN_POS:
			Devs::MotionIf.AxisPosMove(REMOTE_AXIS_GLASS_UVW_Y1, CMachineData::m_MachineDataMotor.Info.dOriginPos[REMOTE_AXIS_GLASS_UVW_Y2], 1, 3, 3, eMOTION_ABS);
			Sleep(10);
			Devs::MotionIf.AxisPosMove(REMOTE_AXIS_GLASS_UVW_Y1, CMachineData::m_MachineDataMotor.Info.dOriginPos[REMOTE_AXIS_GLASS_UVW_Y2], 1, 3, 3, eMOTION_ABS);

			SetCheckStep(eINSPECTION_STAGE_ORIGIN_Y1_Y2_ORIGIN_POS_CHECK, _T("eINSPECTION_STAGE_ORIGIN_Y1_Y2_ORIGIN_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eINSPECTION_STAGE_ORIGIN_Y1_Y2_ORIGIN_POS_CHECK:
			dPosY1 = SharedInfo::GetCmdPos(AXIS_GLASS_UVW_Y1);
			dPosY2 = SharedInfo::GetCmdPos(AXIS_GLASS_UVW_Y2);
			if ((IsSamePosition(dPosY1, CMachineData::m_MachineDataMotor.Info.dOriginPos[AXIS_GLASS_UVW_Y1]) && IsMotionDone(AXIS_GLASS_UVW_Y1)) &&
				(IsSamePosition(dPosY2, CMachineData::m_MachineDataMotor.Info.dOriginPos[AXIS_GLASS_UVW_Y2]) && IsMotionDone(AXIS_GLASS_UVW_Y2)))
			{
				SetStep(eINSPECTION_STAGE_ORIGIN_X_SERVO_ON, _T("eINSPECTION_STAGE_ORIGIN_X_SERVO_ON"));
			}
			else if (IsTimeOut())
			{
				//SetAlarm(_T("ERROR : eINSPECTION_STAGE_ORIGIN_Y1_Y2_ORIGIN_POS_CHECK"));
			}
			else
			{
				SetCheckStep(eINSPECTION_STAGE_ORIGIN_Y1_Y2_ORIGIN_POS_CHECK, _T("eINSPECTION_STAGE_ORIGIN_Y1_Y2_ORIGIN_POS_CHECK"));
			}
			break;

		case eINSPECTION_STAGE_ORIGIN_X_SERVO_ON:
			Devs::MotionIf.AxisSetServoOnStatus(REMOTE_AXIS_GLASS_UVW_X1, 1);
			Sleep(200);
			Devs::MotionIf.AxisSetServoOnStatus(REMOTE_AXIS_GLASS_UVW_X2, 1);

			SetCheckStep(eINSPECTION_STAGE_ORIGIN_X_SERVO_ON_CHECK, _T("eINSPECTION_STAGE_ORIGIN_X_SERVO_ON_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eINSPECTION_STAGE_ORIGIN_X_SERVO_ON_CHECK:
			if (SharedInfo::AxisServoOnStatus[REMOTE_AXIS_GLASS_UVW_X1] == 1 && SharedInfo::AxisServoOnStatus[REMOTE_AXIS_GLASS_UVW_X2] == 1)
			{
				SetStep(eINSPECTION_STAGE_ORIGIN_X_START, _T("eINSPECTION_STAGE_ORIGIN_X_START"));
			}
			else if (IsTimeOut())
			{
				//SetAlarm(_T("ERROR : eINSPECTION_STAGE_ORIGIN_X_SERVO_ON_CHECK"));
			}
			else
			{
				SetCheckStep(eINSPECTION_STAGE_ORIGIN_X_SERVO_ON_CHECK, _T("eINSPECTION_STAGE_ORIGIN_X_SERVO_ON_CHECK"));
			}
			break;

		case eINSPECTION_STAGE_ORIGIN_X_START:
			Devs::MotionIf.AxisHomeStart(REMOTE_AXIS_GLASS_UVW_X1);
			Sleep(200);
			Devs::MotionIf.AxisHomeStart(REMOTE_AXIS_GLASS_UVW_X2);
			Sleep(200);
			SetCheckStep(eINSPECTION_STAGE_ORIGIN_X_HOME_BIT_CHECK, _T("eINSPECTION_STAGE_ORIGIN_X_HOME_BIT_CHECK"));
			break;

		case eINSPECTION_STAGE_ORIGIN_X_HOME_BIT_CHECK:
			if (!IsAxisHome(REMOTE_AXIS_GLASS_UVW_X1) && !IsAxisHome(REMOTE_AXIS_GLASS_UVW_X2))
			{
				SetCheckStep(eINSPECTION_STAGE_ORIGIN_X_HOME_COMPLETE_CHECK, _T("eINSPECTION_STAGE_ORIGIN_X_HOME_COMPLETE_CHECK"));
			}
			else
			{
				SetCheckStep(eINSPECTION_STAGE_ORIGIN_X_HOME_BIT_CHECK, _T("eINSPECTION_STAGE_ORIGIN_X_HOME_BIT_CHECK"));
			}
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eINSPECTION_STAGE_ORIGIN_X_HOME_COMPLETE_CHECK:
			if (IsAxisHome(REMOTE_AXIS_GLASS_UVW_X1) && IsAxisHome(REMOTE_AXIS_GLASS_UVW_X2))
			{
				//21.02.25 sjc
				SetStep(eINSPECTION_STAGE_ORIGIN_X_ORIGIN_POS, _T("eINSPECTION_STAGE_ORIGIN_X_ORIGIN_POS"));
				//SetStep(eINSPECTION_STAGE_MOTION_DONE, _T("eINSPECTION_STAGE_ORIGIN_X_ORIGIN_POS"));
			}
			else if (IsTimeOut())
			{
				//	SetAlarm(_T("ERROR : eINSPECTION_STAGE_ORIGIN_X_HOME_COMPLETE_CHECK"));
			}
			else
			{
				SetCheckStep(eINSPECTION_STAGE_ORIGIN_X_HOME_COMPLETE_CHECK, _T("eINSPECTION_STAGE_ORIGIN_X_HOME_COMPLETE_CHECK"));
			}
			break;

		case eINSPECTION_STAGE_ORIGIN_X_ORIGIN_POS:
			Devs::MotionIf.AxisPosMove(REMOTE_AXIS_GLASS_UVW_X1, CMachineData::m_MachineDataMotor.Info.dOriginPos[REMOTE_AXIS_GLASS_UVW_X2], 1, 3, 3, eMOTION_ABS);

			SetCheckStep(eINSPECTION_STAGE_ORIGIN_X_ORIGIN_POS_CHECK, _T("eINSPECTION_STAGE_ORIGIN_X_ORIGIN_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eINSPECTION_STAGE_ORIGIN_X_ORIGIN_POS_CHECK:
			dPosX1 = SharedInfo::GetCmdPos(AXIS_GLASS_UVW_X1);
			dPosX2 = SharedInfo::GetCmdPos(AXIS_GLASS_UVW_X2);
			if ((IsSamePosition(dPosX1, CMachineData::m_MachineDataMotor.Info.dOriginPos[AXIS_GLASS_UVW_X1]) && IsMotionDone(AXIS_GLASS_UVW_X1)) &&
				(IsSamePosition(dPosX2, CMachineData::m_MachineDataMotor.Info.dOriginPos[AXIS_GLASS_UVW_X2]) && IsMotionDone(AXIS_GLASS_UVW_X2)))
			{
				SharedInfo::UvwCmdPos[FRAME_UVW][0] = 0.0; //!!!
				SharedInfo::UvwCmdPos[FRAME_UVW][1] = 0.0; //!!!
				SharedInfo::UvwCmdPos[FRAME_UVW][2] = 0.0; //!!!
				Devs::MotionIf.UvwXYTSetZero(FRAME_UVW); //!!!

				SetStep(eINSPECTION_STAGE_MOTION_DONE, _T("eINSPECTION_STAGE_MOTION_DONE"));
			}
			else if (IsTimeOut())
			{
				//SetAlarm(_T("ERROR : eINSPECTION_STAGE_ORIGIN_X_ORIGIN_POS_CHECK"));
			}
			else
			{
				SetCheckStep(eINSPECTION_STAGE_ORIGIN_X_ORIGIN_POS_CHECK, _T("eINSPECTION_STAGE_ORIGIN_X_ORIGIN_POS_CHECK"));
			}
			break;
#pragma endregion


		case eINSPECTION_STAGE_MOTION_DONE:
			m_bMotionDone = TRUE;
			SharedInfo::UvwCmdPos[FRAME_UVW][0] = 0.0; //!!!
			SharedInfo::UvwCmdPos[FRAME_UVW][1] = 0.0; //!!!
			SharedInfo::UvwCmdPos[FRAME_UVW][2] = 0.0; //!!!
			Devs::MotionIf.UvwXYTSetZero(FRAME_UVW); //!!!
			SetStep(eINSPECTION_STAGE_MOTION_IDLE, _T("eINSPECTION_STAGE_MOTION_IDLE"));
			break;

		case eINSPECTION_STAGE_MOTION_EXIT:
			m_StateFinish = FALSE;
			break;
		}
	}
}

BOOL CInspectionStageMotion::InspectionStageUvw_HomeStart()
{
	m_bMotionDone = FALSE;
	SetStep(eINSPECTION_STAGE_ORIGIN_SERVO_ALL_OFF, _T("eINSPECTION_STAGE_ORIGIN_SERVO_ALL_OFF"));
	return TRUE;
}

BOOL CInspectionStageMotion::IsAxisHome(UINT nAxisNo)
{
	return SharedInfo::AxisHomeStatus[nAxisNo];
}

BOOL CInspectionStageMotion::MoveAxis(enum_Axis eAxis, double dPos)
{
	double	dSpeed = 0.0, dAccel = 0.0, dDecel = 0.0;

	//ÇöÀç ¸ðÅÍÀÇ ÆÄ¶ó¹ÌÅÍ ¹Þ¾Æ¿À±â
	if (!GetAxisWorkParam(eAxis, &dSpeed, &dAccel, &dDecel)) return FALSE;
	//ÇØ´ç ¸ðÅÍ¿¡ ÆÄ¶ó¹ÌÅÍ Àü´Þ
	AbsMove(eAxis, dPos, dSpeed, dAccel, dDecel);
	return TRUE;
}
BOOL CInspectionStageMotion::IsMoveDone(enum_Axis eAxis, double dPos)
{
	double dCmdPos = SharedInfo::GetCmdPos(eAxis);
	return (IsSamePosition(dCmdPos, dPos) && IsMotionDone(eAxis));
}

int CInspectionStageMotion::UVWStagePosMove(double UVW[3], double dVel[3], double dAccel[3], double dDecel[3])
{
#ifndef SIM_MODE
	Devs::MotionIf.UvwPosMove(FRAME_UVW, UVW, dVel, dAccel, dDecel, eMOTION_REL);
#endif

	return 0;
}
BOOL CInspectionStageMotion::IsUVWStagePos(double UVW[3])
{
	CString Str = _T("");

	if (SharedInfo::GetInMotion(AXIS_GLASS_UVW_Y1) == 0.0 &&
		SharedInfo::GetInMotion(AXIS_GLASS_UVW_Y2) == 0.0 &&
		SharedInfo::GetInMotion(AXIS_GLASS_UVW_X1) == 0.0 &&
		SharedInfo::GetInMotion(AXIS_GLASS_UVW_X2) == 0.0)
	{
#if 1
		double dUvwPos[3] = { 0.0, };
		Devs::MotionIf.UvwGetTargetPos(FRAME_UVW, dUvwPos);
		Sleep(100);
#endif
		if (IsSamePosition(SharedInfo::dUVWTargetPos[FRAME_UVW][0], SharedInfo::GetCmdPos(AXIS_GLASS_UVW_Y1)) &&
			IsSamePosition(SharedInfo::dUVWTargetPos[FRAME_UVW][1], SharedInfo::GetCmdPos(AXIS_GLASS_UVW_Y2)) &&
			IsSamePosition(SharedInfo::dUVWTargetPos[FRAME_UVW][2], SharedInfo::GetCmdPos(AXIS_GLASS_UVW_X1)) &&
			IsSamePosition(SharedInfo::dUVWTargetPos[FRAME_UVW][2], SharedInfo::GetCmdPos(AXIS_GLASS_UVW_X2)))
		{
			Str.Format(_T("Glass Uvw IsUVWStagePos Ok (dUVWTargetPos[0]:%.5f, dUVWTargetPos[1]:%.5f, dUVWTargetPos[2]:%.5f)"), 
				SharedInfo::dUVWTargetPos[FRAME_UVW][0], SharedInfo::dUVWTargetPos[FRAME_UVW][1], SharedInfo::dUVWTargetPos[FRAME_UVW][2]);
			Sleep(1000); //Temp
			return TRUE;
		}
	}

	return FALSE;
}
BOOL CInspectionStageMotion::GetUVWPos(double *dRefPosX, double *dRefPosY, double *dDiffPosX, double *dDiffPosY, double *dUVWX, double *dUVWY, double *dUVWZ, BOOL b2PointFlag)
{
#ifndef SIM_MODE
	CCalcAlign CalcAlign;

	_3POINT Result;
	int PointCnt;
	if (b2PointFlag == TRUE)
		PointCnt = 2;
	else
		PointCnt = 4;
	_2POINT RefPos[4];
	_2POINT DiffPos[4];
	for (int i = 0; i < PointCnt; i++)
	{
		RefPos[i].dx = dRefPosX[i];
		RefPos[i].dy = dRefPosY[i];
		DiffPos[i].dx = dDiffPosX[i] + dRefPosX[i];
		DiffPos[i].dy = dDiffPosY[i] + dRefPosY[i];
	}
	CalcAlign.clearAlignPoint();

	CalcAlign.setAlignPoint(RefPos[0], RefPos[1], DiffPos[0], DiffPos[1]);
	if (b2PointFlag == FALSE)
		CalcAlign.setAlignPoint(RefPos[3], RefPos[2], DiffPos[3], DiffPos[2]);
	Result = CalcAlign.getAlignResultXYT();


	*dUVWX = -Result.dx;
	*dUVWY = -Result.dy;
	*dUVWZ = -Result.dt * 180 / PI;
#endif

	return TRUE;
}

//sunghaklee(2021.02.25)
BOOL CInspectionStageMotion::UVWStageAlignMove(int nAlignMode, double dCmdPointXY[4][2], double dActPointXY[4][2]) //KJT 20200830
{
	int nRtn;
	double dUvwPos[3] = { 0.0, 0.0, 0.0 };
	double dUvwVel[3] = { 0.0, 0.0, 0.0 };
	double dUvwAccel[3] = { 0.0, 0.0, 0.0 };
	double dUvwDecel[3] = { 0.0, 0.0, 0.0 };

	double dVel = 1.0;			// 10.0;//pDlg->m_dJogSpeed[m_nSpeedMode]; // Üù????Ù® ?Ù®ÙÒ?Üù? 10?Ù¬?? ???Ù´?? 20170804 by lsh
	double dAccel = dVel * 0.5;	// *2.0;
	double dDecel = dVel * 0.5;	// *2.0;

	double dXYT[3] = { 0.0, 0.0, 0.0 };
	double dXYTR[3] = { 0.0, 0.0, 0.0 };
	double dError[3] = { 0.0, 0.0, 0.0 };
	double dX = 0.0, dY = 0.0, dT =0.0;
	CString Str = _T("");

	double RefT[4] = { 0.0, 0.0 , 0.0, 0.0 };
	double NewPositionT[4] = { 0.0, 0.0 , 0.0 , 0.0 };
	double DiffT[4] = { 0.0, 0.0, 0.0, 0.0 };
	double dUVWX[3] = { 0.0, 0.0, 0.0 };
	double DiffPosition[3] = { 0.0, 0.0 , 0.0 };
	double R = 0.0;
	double m_AlignRefPointValue[4][2] = { { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 } };
	double m_AlignVisionResultValue[4][2] = { { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 } };

	//Add
	memset(&m_AlignRefPointValue, 0x0, sizeof(m_AlignRefPointValue));
	memset(&m_AlignVisionResultValue, 0x0, sizeof(m_AlignVisionResultValue));

	DiffPosition[0] = 0.0;
	DiffPosition[1] = 0.0;
	DiffPosition[2] = 0.0;

	m_AlignRefPointValue[0][0] = dCmdPointXY[0][0];
	m_AlignRefPointValue[0][1] = dCmdPointXY[0][1];
	m_AlignRefPointValue[1][0] = dCmdPointXY[1][0];
	m_AlignRefPointValue[1][1] = dCmdPointXY[1][1];
	m_AlignRefPointValue[2][0] = dCmdPointXY[2][0];
	m_AlignRefPointValue[2][1] = dCmdPointXY[2][1];
	m_AlignRefPointValue[3][0] = dCmdPointXY[3][0];
	m_AlignRefPointValue[3][1] = dCmdPointXY[3][1];

	m_AlignVisionResultValue[0][0] = dActPointXY[0][0] - dCmdPointXY[0][0];
	m_AlignVisionResultValue[0][1] = dActPointXY[0][1] - dCmdPointXY[0][1];
	m_AlignVisionResultValue[1][0] = dActPointXY[1][0] - dCmdPointXY[1][0];
	m_AlignVisionResultValue[1][1] = dActPointXY[1][1] - dCmdPointXY[1][1];
	m_AlignVisionResultValue[2][0] = dActPointXY[2][0] - dCmdPointXY[2][0];
	m_AlignVisionResultValue[2][1] = dActPointXY[2][1] - dCmdPointXY[2][1];
	m_AlignVisionResultValue[3][0] = dActPointXY[3][0] - dCmdPointXY[3][0];
	m_AlignVisionResultValue[3][1] = dActPointXY[3][1] - dCmdPointXY[3][1];

	int nMeasureCount = 4;

	//sunghaklee(2021.02.25) : Add
	//AlignMode
	//_eHorizontal_Align_Mode = 0,
	//_eVertical_Align_Mode = 1,
	//_e4Point_Align_Mode = 2
	//0:LB, 1:LT, 2:RT, 3:RB ---> Caution!!!
	if (nAlignMode == _eHorizontal_Align_Mode)
	{
		Make2PointAlignData(3, dCmdPointXY[0], dCmdPointXY[3], dActPointXY[0], dActPointXY[3], &dX, &dY, &dT);
	}
	else if (nAlignMode == _eVertical_Align_Mode)
	{
		Make2PointAlignData(3, dCmdPointXY[0], dCmdPointXY[3], dActPointXY[0], dActPointXY[3], &dX, &dY, &dT);
	}
	else//_e4Point_Align_Mode
	{
		Make2PointAlignData(0, dCmdPointXY[0], dCmdPointXY[1], dActPointXY[0], dActPointXY[1], &dX, &dY, &dT);
		dXYT[0] += dX;
		dXYT[1] += dY;
		dXYT[2] += dT;

		Make2PointAlignData(1, dCmdPointXY[1], dCmdPointXY[2], dActPointXY[1], dActPointXY[2], &dX, &dY, &dT);
		dXYT[0] += dX;
		dXYT[1] += dY;
		dXYT[2] += dT;

		Make2PointAlignData(2, dCmdPointXY[3], dCmdPointXY[2], dActPointXY[3], dActPointXY[2], &dX, &dY, &dT);
		dXYT[0] += dX;
		dXYT[1] += dY;
		dXYT[2] += dT;

		Make2PointAlignData(3, dCmdPointXY[0], dCmdPointXY[3], dActPointXY[0], dActPointXY[3], &dX, &dY, &dT);

		dXYT[0] += dX;
		dXYT[1] += dY;
		dXYT[2] += dT;

		dXYT[0] /= 4.0;
		dXYT[1] /= 4.0;
		dXYT[2] /= 4.0;

		dX = dXYT[0];
		dY = dXYT[1];
		dT = dXYT[2];
	}
	
	
	//sunghaklee(2021.02.25)
	//dXYT[0] = dX; //dXYT[0] += dX;
	//dXYT[1] = dY; //dXYT[1] += dY;
	//dXYT[2] = dT; //dXYT[2] += dT;
	//Caution..........................!!
	dXYT[0] = -dX; 
	dXYT[1] = -dY;
	dXYT[2] = -dT; //imsi 

#if 0
	dError[0] = dXYT[0];
	dError[1] = dXYT[1];
	dError[2] = dXYT[2] * (180.0 / PI);

	SharedInfo::UvwCmdPos[FRAME_UVW][0] += dError[0];
	dXYT[0] = SharedInfo::UvwCmdPos[FRAME_UVW][0];

	SharedInfo::UvwCmdPos[FRAME_UVW][1] += dError[1];
	dXYT[1] = SharedInfo::UvwCmdPos[FRAME_UVW][1];

	SharedInfo::UvwCmdPos[FRAME_UVW][2] += dError[2];
	dXYT[2] = SharedInfo::UvwCmdPos[FRAME_UVW][2];
#else
	dError[0] = dXYT[0];
	dError[1] = dXYT[1];
	//sunghaklee(2021.02.25)
	//dError[2] = dXYT[2];
	dError[2] = dXYT[2] * (180.0 / PI);

	//Unit of SharedInfo::UvwCmdPos is degree
	SharedInfo::UvwCmdPos[FRAME_UVW][0] += dError[0];
	dXYT[0] = SharedInfo::UvwCmdPos[FRAME_UVW][0];

	SharedInfo::UvwCmdPos[FRAME_UVW][1] += dError[1];
	dXYT[1] = SharedInfo::UvwCmdPos[FRAME_UVW][1];

	SharedInfo::UvwCmdPos[FRAME_UVW][2] += dError[2];
	//sunghaklee(2021.02.25)
	//dXYT[2] = SharedInfo::UvwCmdPos[MASK_UVW][2] * (180.0 / PI);
	dXYT[2] = SharedInfo::UvwCmdPos[FRAME_UVW][2];
#endif

	//sunghaklee(2021.02.25)
	//dUvwPos[0] = -dXYT[0];
	//dUvwPos[1] = -dXYT[1];
	//dUvwPos[2] = -dXYT[2];
	dUvwPos[0] = dXYT[0];
	dUvwPos[1] = dXYT[1];
	dUvwPos[2] = dXYT[2];


	dUvwVel[0] = dVel;
	dUvwVel[1] = dVel;
	dUvwVel[2] = dVel;

	dUvwAccel[0] = dAccel;
	dUvwAccel[1] = dAccel;
	dUvwAccel[2] = dAccel;

	dUvwDecel[0] = dDecel;
	dUvwDecel[1] = dDecel;
	dUvwDecel[2] = dDecel;
		
	nRtn = Devs::MotionIf.UvwPosMove(FRAME_UVW, dUvwPos, dUvwVel, dUvwAccel, dUvwDecel, 0);

	Str.Format(_T("InspectionStage Error X:%.5f, Y:%.5f, T:%.5f\n"), dError[0], dError[1], dError[2]);
	Total_Msg(Str);
	Str.Format(_T("InspectionStage UvwPosMove dUvwPos[0]:%.5f, dUvwPos[1]:%.5f, dUvwPos[2]:%.5f\n"), dUvwPos[0], dUvwPos[1], dUvwPos[2]);
	Total_Msg(Str);
	TRACE(Str);	

	return nRtn;
}
void CInspectionStageMotion::Make2PointAlignData(int nNo, double dRefLeftXY[2], double dRefRightXY[2], double dObjLeftXY[2], double dObjRightXY[2], double *dX, double *dY, double *dT)
{
	double dRefXCenter = (dRefLeftXY[0] + dRefRightXY[0]) * 0.5;
	double dRefYCenter = (dRefLeftXY[1] + dRefRightXY[1]) * 0.5;
	double dObjXCenter = (dObjLeftXY[0] + dObjRightXY[0]) * 0.5;
	double dObjYCenter = (dObjLeftXY[1] + dObjRightXY[1]) * 0.5;

	double dObjTilt = atan2((dObjRightXY[1] - dObjLeftXY[1]), (dObjRightXY[0] - dObjLeftXY[0]));
	double dRefTilt = atan2((dRefRightXY[1] - dRefLeftXY[1]), (dRefRightXY[0] - dRefLeftXY[0]));

	*dX = dObjXCenter - dRefXCenter;
	*dY = dObjYCenter - dRefYCenter;
	*dT = (dObjTilt - dRefTilt);
}

#pragma region //InspectionStage UVW
//Move
BOOL CInspectionStageMotion::InspectionStageUVW_WaitPos()
{
	CString Str = _T("");
	double dPos[3] = { 0.0, 0.0, 0.0 };

	dPos[0] = CManualData::m_ManualDataInspect.Info.m_dInspectionStageX_Wait_Pos;
	dPos[1] = CManualData::m_ManualDataInspect.Info.m_dInspectionStageY_Wait_Pos;
	dPos[2] = CManualData::m_ManualDataInspect.Info.m_dInspectionStageT_Wait_Pos;

	Devs::MotionIf.UvwTargetPosMove(FRAME_UVW, dPos);

	Str.Format(_T("Inspection Stage UVW Move To Wait Pos Y1:%.5f, Y2:%.5f, X:%.5f)"), dPos[0], dPos[1], dPos[2]);
	Total_Msg(Str);

	return TRUE;
}
BOOL CInspectionStageMotion::InspectionStageUVW_StickLoadPos()
{
	CString Str = _T("");
	double dPos[3] = { 0.0, 0.0, 0.0 };

	dPos[0] = CManualData::m_ManualDataInspect.Info.m_dInspectionStageX_StickLoad_Pos;
	dPos[1] = CManualData::m_ManualDataInspect.Info.m_dInspectionStageY_StickLoad_Pos;
	dPos[2] = CManualData::m_ManualDataInspect.Info.m_dInspectionStageT_StickLoad_Pos;

	Devs::MotionIf.UvwTargetPosMove(FRAME_UVW, dPos);

	Str.Format(_T("Inspection Stage UVW Move To StickLoad Pos (X:%.5f, Y:%.5f, T:%.5f)"), dPos[0], dPos[1], dPos[2]);
	Total_Msg(Str);

	return TRUE;
}
BOOL CInspectionStageMotion::InspectionStageUVW_StickUnloadPos()
{
	CString Str = _T("");
	double dPos[3] = { 0.0, 0.0, 0.0 };

	dPos[0] = CManualData::m_ManualDataInspect.Info.m_dInspectionStageX_StickUnload_Pos;
	dPos[1] = CManualData::m_ManualDataInspect.Info.m_dInspectionStageY_StickUnload_Pos;
	dPos[2] = CManualData::m_ManualDataInspect.Info.m_dInspectionStageT_StickUnload_Pos;

	Devs::MotionIf.UvwTargetPosMove(FRAME_UVW, dPos);

	Str.Format(_T("Inspection Stage UVW Move To StickUnload Pos Y1:%.5f, Y2:%.5f, X:%.5f)"), dPos[0], dPos[1], dPos[2]);
	Total_Msg(Str);

	return TRUE;
}
//MoveDone Check
BOOL CInspectionStageMotion::Is_InspectionStageUVW_WaitPos()
{
	if (SharedInfo::AxisInMotionStatus[REMOTE_AXIS_GLASS_UVW_Y1] == 0 &&
		SharedInfo::AxisInMotionStatus[REMOTE_AXIS_GLASS_UVW_Y2] == 0 &&
		SharedInfo::AxisInMotionStatus[REMOTE_AXIS_GLASS_UVW_X1] == 0 &&
		SharedInfo::AxisInMotionStatus[REMOTE_AXIS_GLASS_UVW_X2] == 0)
	{
		//double dUvwPos[3] = { 0.0, };
		//Devs::MotionIf.UvwGetTargetPos(FRAME_UVW, dUvwPos);
		//Sleep(100);

		double dX = CManualData::m_ManualDataInspect.Info.m_dInspectionStageX_Wait_Pos;
		double dY = CManualData::m_ManualDataInspect.Info.m_dInspectionStageY_Wait_Pos;
		double dT = CManualData::m_ManualDataInspect.Info.m_dInspectionStageT_Wait_Pos;
		if (IsSamePosition(dX, SharedInfo::UvwCmdPos[FRAME_UVW][0]) &&
			IsSamePosition(dY, SharedInfo::UvwCmdPos[FRAME_UVW][1]) &&
			IsSamePosition(dT, SharedInfo::UvwCmdPos[FRAME_UVW][2]))
		{
			return TRUE;
		}
	}

	return FALSE;
}
BOOL CInspectionStageMotion::Is_InspectionStageUVW_StickLoadPos()
{

	return FALSE;
}
BOOL CInspectionStageMotion::Is_InspectionStageUVW_StickUnloadPos()
{

	return FALSE;
}
#pragma endregion

#pragma region //IO

BOOL	CInspectionStageMotion::Inspect_Stage_Vac_On()
{
	//21.02.04 sjc no stage vac
	//return TRUE;

	//SetDOutputBitValue((enum_Do)_DOUT_INSPECTION_STAGE_VAC, TRUE);
	//Total_Msg(_T("Inspection Stage Vac On"));
	//return TRUE;
	
	//g_CommESC.Esc_Send_Msg(_T("SYSTem:REMote"));	
	//Sleep(10);
	//g_CommESC.Esc_Send_Msg(_T("OUTPut 1"));
	//Sleep(10);

	return TRUE;
}
BOOL	CInspectionStageMotion::Inspect_Stage_Vac_Off()
{
	//21.02.04 sjc no stage vac
	//return TRUE;
	//SetDOutputBitValue((enum_Do)_DOUT_INSPECTION_STAGE_VAC, FALSE); //1 !!
	//Total_Msg(_T("Inspection Stage Vac Off"));
	//Sleep(1000);

	//SetDOutputBitValue((enum_Do)_DOUT_INSPECTION_STAGE_PURGE, TRUE); //2 !!
	//Total_Msg(_T("Inspection Stage Purge On"));
	//Sleep(1000);
	//SetDOutputBitValue((enum_Do)_DOUT_INSPECTION_STAGE_PURGE, FALSE); //3 !!
	//Total_Msg(_T("Inspection Stage Purge Off"));
	//Sleep(1000);

	//return TRUE;

	//g_CommESC.Esc_Send_Msg(_T("SYSTem:REMote"));
	//Sleep(10);
	//g_CommESC.Esc_Send_Msg(_T("TOGGle 1"));
	//Sleep(10);
	//g_CommESC.Esc_Send_Msg(_T("OUTPut 0"));
	//Sleep(10);

	return TRUE;
}

BOOL	CInspectionStageMotion::Is_Inspect_Stage_Vac_On()
{
	//21.02.04 sjc no stage vac
	//return TRUE;
	//if (SharedInfo::DInputValue[_DIN_INSPECTION_STAGE_VAC_ON] == TRUE)
	//	return TRUE;
	//else
	//	return FALSE;

	//g_CommESC.Esc_Send_Msg(_T("OUTPut?"));
	//Sleep(100);

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)theApp.GetMainWnd();
	CString str;
	str = pDlg->m_pch;

	if (_ttoi(str) > 0) return TRUE;
	else return FALSE;
}
BOOL	CInspectionStageMotion::Is_Inspect_Stage_Vac_Off()
{
	//21.02.04 sjc no stage vac
	//return TRUE;
	//if (SharedInfo::DInputValue[_DIN_INSPECTION_STAGE_VAC_ON] == FALSE)
	//	return TRUE;
	//else
	//	return FALSE;

	//g_CommESC.Esc_Send_Msg(_T("OUTPut?"));
	//Sleep(100);

	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)theApp.GetMainWnd();
	CString str;
	str = pDlg->m_pch;

	if (_ttoi(str) < 1) return TRUE;
	else return FALSE;
}
#pragma endregion