#include "stdafx.h"
#include "BoxMotion.h"
#include "Vision/Devs.h"
#include "Vision/SharedInfo.h"
#include "CalcAlign/CalcAlign.h"
#include "Log/Logger.h"
#include "Data/ManualData.h"
#include "Data/MachineData.h"
#include "Data/ModelData.h"

CBoxMotion::CBoxMotion()
{
}


CBoxMotion::~CBoxMotion()
{
}

BOOL CBoxMotion::InitProcess()
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

BOOL CBoxMotion::EndProcess()
{
	int i = 0;

	m_StateFinish = FALSE;

	SetStep(eBOX_MOTION_IDLE, FALSE);

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

BOOL CBoxMotion::Stop()
{
	m_bStopBit = TRUE;
	SetStop(); //!!
	return TRUE;
}

UINT CBoxMotion::MotionThreadFunction(LPVOID lpParam)
{
	CBoxMotion* pBoxMotion = NULL;

	pBoxMotion = (CBoxMotion*)lpParam;

	pBoxMotion->MotionThreadFunctionEntry();

	pBoxMotion->m_bTerminate = 1;

	return 0;
}

VOID CBoxMotion::MotionThreadFunctionEntry(VOID)
{
	int ErrorCheck = 0;
	CString szMsg;
	double dPosX = 0.0, dPosY1 = 0.0, dPosY2 = 0.0;

	while (m_StateFinish)
	{
		WaitForSingleObject(hMotionHandle, INFINITE);
		ResetEvent(hMotionHandle);

		if (SharedInfo::bMachineStopFlag == TRUE)// && m_bStopBit == FALSE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(eBOX_MOTION_IDLE); //KJT 20210318
			continue; //!!
		}

		
		switch (GetCurrentTotalStep())
		{
		case eBOX_MOTION_IDLE:
			break;

		case eBOX_MOTION_ERROR:
			break;

#pragma region //UVW Home (Y1, Y2, X)
		case eLOADING_STAGE_ORIGIN_SERVO_ALL_OFF:
			ServoOnOff(AXIS_LOADING_STAGE_Y1, FALSE);
			Sleep(300);
			ServoOnOff(AXIS_LOADING_STAGE_Y2, FALSE);
			Sleep(300);
			ServoOnOff(AXIS_LOADING_STAGE_X, FALSE);
			Sleep(300);

			SetCheckStep(eLOADING_STAGE_ORIGIN_SERVO_ALL_OFF_CHECK, _T("eLOADING_STAGE_ORIGIN_SERVO_ALL_OFF_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eLOADING_STAGE_ORIGIN_SERVO_ALL_OFF_CHECK:
			if (SharedInfo::AxisServoOnStatus[REMOTE_AXIS_AJIN_LOADING_STAGE_Y1] == 0 &&
				SharedInfo::AxisServoOnStatus[REMOTE_AXIS_AJIN_LOADING_STAGE_Y2] == 0 &&
				SharedInfo::AxisServoOnStatus[REMOTE_AXIS_AJIN_LOADING_STAGE_X] == 0)
			{
				SetStep(eLOADING_STAGE_ORIGIN_Y1Y2_SERVO_ON, _T("eLOADING_STAGE_ORIGIN_Y1Y2_SERVO_ON"));
			}
			else if (IsTimeOut())
			{
				//	SetAlarm(_T("ERROR : eLOADING_STAGE_ORIGIN_SERVO_ALL_OFF_CHECK"));
			}
			else
			{
				SetCheckStep(eLOADING_STAGE_ORIGIN_SERVO_ALL_OFF_CHECK, _T("eLOADING_STAGE_ORIGIN_SERVO_ALL_OFF_CHECK"));
			}
			break;

		case eLOADING_STAGE_ORIGIN_Y1Y2_SERVO_ON:
			Devs::MotionIf.AxisSetServoOnStatus(REMOTE_AXIS_AJIN_LOADING_STAGE_Y1, 1);
			Sleep(10);
			Devs::MotionIf.AxisSetServoOnStatus(REMOTE_AXIS_AJIN_LOADING_STAGE_Y2, 1);

			SetCheckStep(eLOADING_STAGE_ORIGIN_Y1Y2_SERVO_ON_CHECK, _T("eLOADING_STAGE_ORIGIN_Y1Y2_SERVO_ON_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eLOADING_STAGE_ORIGIN_Y1Y2_SERVO_ON_CHECK:
			if (SharedInfo::AxisServoOnStatus[REMOTE_AXIS_AJIN_LOADING_STAGE_Y1] == 1 &&
				SharedInfo::AxisServoOnStatus[REMOTE_AXIS_AJIN_LOADING_STAGE_Y2] == 1)
			{
				SetStep(eLOADING_STAGE_ORIGIN_Y1Y2_START, _T("eLOADING_STAGE_ORIGIN_Y1Y2_START"));
			}
			else if (IsTimeOut())
			{
				//SetAlarm(_T("ERROR : eLOADING_STAGE_ORIGIN_Y1Y2_SERVO_ON_CHECK"));
			}
			else
			{
				SetCheckStep(eLOADING_STAGE_ORIGIN_Y1Y2_SERVO_ON_CHECK, _T("eLOADING_STAGE_ORIGIN_Y1Y2_SERVO_ON_CHECK"));
			}
			break;

		case eLOADING_STAGE_ORIGIN_Y1Y2_START:
			Devs::MotionIf.AxisHomeStart(REMOTE_AXIS_AJIN_LOADING_STAGE_Y1);
			Sleep(200);
			Devs::MotionIf.AxisHomeStart(REMOTE_AXIS_AJIN_LOADING_STAGE_Y2);
			Sleep(200);
			SetCheckStep(eLOADING_STAGE_ORIGIN_Y1Y2_HOME_BIT_CHECK, _T("eLOADING_STAGE_ORIGIN_Y1Y2_HOME_BIT_CHECK"));
			break;

		case eLOADING_STAGE_ORIGIN_Y1Y2_HOME_BIT_CHECK:
			if (!IsAxisHome(REMOTE_AXIS_AJIN_LOADING_STAGE_Y1) && !IsAxisHome(REMOTE_AXIS_AJIN_LOADING_STAGE_Y2))
			{
				SetCheckStep(eLOADING_STAGE_ORIGIN_Y1Y2_HOME_COMPLETE_CHECK, _T("eLOADING_STAGE_ORIGIN_Y1Y2_HOME_COMPLETE_CHECK"));
			}
			else
			{
				SetCheckStep(eLOADING_STAGE_ORIGIN_Y1Y2_HOME_BIT_CHECK, _T("eLOADING_STAGE_ORIGIN_Y1Y2_HOME_BIT_CHECK"));
			}
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eLOADING_STAGE_ORIGIN_Y1Y2_HOME_COMPLETE_CHECK:
			if (IsAxisHome(REMOTE_AXIS_AJIN_LOADING_STAGE_Y1) && IsAxisHome(REMOTE_AXIS_AJIN_LOADING_STAGE_Y2))
			{
				//21.02.25 sjc
				SetStep(eLOADING_STAGE_ORIGIN_Y1_Y2_ORIGIN_POS, _T("eLOADING_STAGE_ORIGIN_Y1_Y2_ORIGIN_POS"));
				//SetStep(eLOADING_STAGE_ORIGIN_X_SERVO_ON, _T("eLOADING_STAGE_ORIGIN_X_SERVO_ON"));
			}
			else if (IsTimeOut())
			{
				//SetAlarm(_T("ERROR : eLOADING_STAGE_ORIGIN_Y1Y2_HOME_COMPLETE_CHECK"));
			}
			else
			{
				SetCheckStep(eLOADING_STAGE_ORIGIN_Y1Y2_HOME_COMPLETE_CHECK, _T("eLOADING_STAGE_ORIGIN_Y1Y2_HOME_COMPLETE_CHECK"));
			}
			break;

		case eLOADING_STAGE_ORIGIN_Y1_Y2_ORIGIN_POS:
			Devs::MotionIf.AxisPosMove(REMOTE_AXIS_AJIN_LOADING_STAGE_Y1, CMachineData::m_MachineDataMotor.Info.dOriginPos[AXIS_LOADING_STAGE_Y1], 1, 3, 3, eMOTION_ABS);
			Sleep(10);
			Devs::MotionIf.AxisPosMove(REMOTE_AXIS_AJIN_LOADING_STAGE_Y2, CMachineData::m_MachineDataMotor.Info.dOriginPos[AXIS_LOADING_STAGE_Y2], 1, 3, 3, eMOTION_ABS);

			SetCheckStep(eLOADING_STAGE_ORIGIN_Y1_Y2_ORIGIN_POS_CHECK, _T("eLOADING_STAGE_ORIGIN_Y1_Y2_ORIGIN_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eLOADING_STAGE_ORIGIN_Y1_Y2_ORIGIN_POS_CHECK:
			dPosY1 = SharedInfo::GetCmdPos(AXIS_LOADING_STAGE_Y1);
			dPosY2 = SharedInfo::GetCmdPos(AXIS_LOADING_STAGE_Y2);
			if ((IsSamePosition(dPosY1, CMachineData::m_MachineDataMotor.Info.dOriginPos[AXIS_LOADING_STAGE_Y1]) && IsMotionDone(AXIS_LOADING_STAGE_Y1)) &&
				(IsSamePosition(dPosY2, CMachineData::m_MachineDataMotor.Info.dOriginPos[AXIS_LOADING_STAGE_Y2]) && IsMotionDone(AXIS_LOADING_STAGE_Y2)))
			{
				SetStep(eLOADING_STAGE_ORIGIN_X_SERVO_ON, _T("eLOADING_STAGE_ORIGIN_X_SERVO_ON"));
			}
			else if (IsTimeOut())
			{
				//SetAlarm(_T("ERROR : eLOADING_STAGE_ORIGIN_X_SERVO_ON_CHECK"));
			}
			else
			{
				SetCheckStep(eLOADING_STAGE_ORIGIN_Y1_Y2_ORIGIN_POS_CHECK, _T("eLOADING_STAGE_ORIGIN_Y1_Y2_ORIGIN_POS_CHECK"));
			}
			break;

		case eLOADING_STAGE_ORIGIN_X_SERVO_ON:
			Devs::MotionIf.AxisSetServoOnStatus(REMOTE_AXIS_AJIN_LOADING_STAGE_X, 1);

			SetCheckStep(eLOADING_STAGE_ORIGIN_X_SERVO_ON_CHECK, _T("eLOADING_STAGE_ORIGIN_X_SERVO_ON_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eLOADING_STAGE_ORIGIN_X_SERVO_ON_CHECK:
			if (SharedInfo::AxisServoOnStatus[REMOTE_AXIS_AJIN_LOADING_STAGE_X] == 1)
			{
				SetStep(eLOADING_STAGE_ORIGIN_X_START, _T("eLOADING_STAGE_ORIGIN_X_START"));
			}
			else if (IsTimeOut())
			{
				//SetAlarm(_T("ERROR : eLOADING_STAGE_ORIGIN_X_SERVO_ON_CHECK"));
			}
			else
			{
				SetCheckStep(eLOADING_STAGE_ORIGIN_X_SERVO_ON_CHECK, _T("eLOADING_STAGE_ORIGIN_X_SERVO_ON_CHECK"));
			}
			break;

		case eLOADING_STAGE_ORIGIN_X_START:
			Devs::MotionIf.AxisHomeStart(REMOTE_AXIS_AJIN_LOADING_STAGE_X);
			Sleep(1000);
			SetCheckStep(eLOADING_STAGE_ORIGIN_X_HOME_BIT_CHECK, _T("eLOADING_STAGE_ORIGIN_X_HOME_BIT_CHECK"));
			break;

		case eLOADING_STAGE_ORIGIN_X_HOME_BIT_CHECK:
			if (!IsAxisHome(REMOTE_AXIS_AJIN_LOADING_STAGE_X))
			{
				SetCheckStep(eLOADING_STAGE_ORIGIN_X_HOME_COMPLETE_CHECK, _T("eLOADING_STAGE_ORIGIN_X_HOME_COMPLETE_CHECK"));
			}
			else
			{
				SetCheckStep(eLOADING_STAGE_ORIGIN_X_HOME_BIT_CHECK, _T("eLOADING_STAGE_ORIGIN_X_HOME_BIT_CHECK"));
			}
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eLOADING_STAGE_ORIGIN_X_HOME_COMPLETE_CHECK:
			if (IsAxisHome(REMOTE_AXIS_AJIN_LOADING_STAGE_X))
			{
				//21.02.25 sjc
				SetStep(eLOADING_STAGE_ORIGIN_X_ORIGIN_POS, _T("eLOADING_STAGE_ORIGIN_X_ORIGIN_POS"));
				//SetStep(eBOX_MOTION_DONE, _T("eBOX_MOTION_DONE"));
			}
			else if (IsTimeOut())
			{
				//	SetAlarm(_T("ERROR : eBOX_MOTION_ORIGIN_Y_HOME_COMPLETE_CHECK"));
			}
			else
			{
				SetCheckStep(eLOADING_STAGE_ORIGIN_X_HOME_COMPLETE_CHECK, _T("eBOX_MOTION_ORIGIN_X_HOME_COMPLETE_CHECK"));
			}
			break;
		case eLOADING_STAGE_ORIGIN_X_ORIGIN_POS:
			Devs::MotionIf.AxisPosMove(REMOTE_AXIS_AJIN_LOADING_STAGE_X, CMachineData::m_MachineDataMotor.Info.dOriginPos[AXIS_LOADING_STAGE_X], 1, 3, 3, eMOTION_ABS);

			SetCheckStep(eLOADING_STAGE_ORIGIN_X_ORIGIN_POS_CHECK, _T("eLOADING_STAGE_ORIGIN_X_ORIGIN_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eLOADING_STAGE_ORIGIN_X_ORIGIN_POS_CHECK:
			dPosX = SharedInfo::GetCmdPos(AXIS_LOADING_STAGE_X);
			if ((IsSamePosition(dPosX, CMachineData::m_MachineDataMotor.Info.dOriginPos[AXIS_LOADING_STAGE_X]) && IsMotionDone(AXIS_LOADING_STAGE_X)))
			{
				SharedInfo::UvwCmdPos[MASK_UVW][0] = 0.0; //!!!
				SharedInfo::UvwCmdPos[MASK_UVW][1] = 0.0; //!!!
				SharedInfo::UvwCmdPos[MASK_UVW][2] = 0.0; //!!!
				Devs::MotionIf.UvwXYTSetZero(MASK_UVW); //!!!

				//Box Laser Relay
				//Devs::m_BaseMotion.SetDOutputBitValue(_DOUT_BOX_LASER_POINT, TRUE);
				Sleep(20);

				SetStep(eBOX_MOTION_DONE, _T("eBOX_MOTION_DONE"));
			}
			else if (IsTimeOut())
			{
				//SetAlarm(_T("ERROR : eLOADING_STAGE_ORIGIN_X_ORIGIN_POS_CHECK"));
			}
			else
			{
				SetCheckStep(eLOADING_STAGE_ORIGIN_X_ORIGIN_POS_CHECK, _T("eLOADING_STAGE_ORIGIN_X_ORIGIN_POS_CHECK"));
			}
			break;
#pragma endregion

		case eBOX_MOTION_DONE:
			SharedInfo::UvwCmdPos[MASK_UVW][0] = 0.0; //!!!
			SharedInfo::UvwCmdPos[MASK_UVW][1] = 0.0; //!!!
			SharedInfo::UvwCmdPos[MASK_UVW][2] = 0.0; //!!!
			Devs::MotionIf.UvwXYTSetZero(MASK_UVW); //!!!
			m_bMotionDone = TRUE;

			SetStep(eBOX_MOTION_IDLE, _T("eBOX_MOTION_IDLE"));			
			break;

		case eBOX_MOTION_EXIT:
			m_StateFinish = FALSE;
			break;

		}

	}
}

#pragma region //Vision
BOOL CBoxMotion::FindBoxAlignPattern_Left(double *dDiffPosX, double *dDiffPosY)
{
#ifndef SIM_MODE
	wk_MilCameraInfo CameraInfo;
	wk_MilPatFindData	PateData;

	CameraInfo = Devs::m_CameraBoxAlignLeft->GetCameraInfo();
	CameraInfo.nBlackWhite = CModelData::m_AlignPara.Info.nBoxAlignLeftBlackWhiteType; //0
	CameraInfo.nBin = CModelData::m_AlignPara.Info.nBoxAlignLeftThreshold;
	Devs::m_CameraBoxAlignLeft->SetCameraInfo(CameraInfo);
	PateData = Devs::m_CameraBoxAlignLeft->GetPatFindData();
	Devs::m_CameraBoxAlignLeft->SetPatFindData(PateData);
	Devs::m_CameraBoxAlignLeft->OnInspPattern();
	PateData = Devs::m_CameraBoxAlignLeft->GetPatFindData();

	*dDiffPosX = PateData.dPosX;
	*dDiffPosY = PateData.dPosY;
#else
	*dDiffPosX = 0.0;
	*dDiffPosY = 0.0;
#endif
#ifndef SIM_MODE
	if (PateData.dScore < 60.0) return FALSE;
	else 
#endif
		return TRUE;
}
BOOL CBoxMotion::FindBoxAlignPattern_Right(double *dDiffPosX, double *dDiffPosY)
{
#ifndef SIM_MODE
	wk_MilCameraInfo CameraInfo;
	wk_MilPatFindData	PateData;

	CameraInfo = Devs::m_CameraBoxAlignRight->GetCameraInfo();
	CameraInfo.nBlackWhite = CModelData::m_AlignPara.Info.nBoxAlignRightBlackWhiteType; //0
	CameraInfo.nBin = CModelData::m_AlignPara.Info.nBoxAlignRightThreshold;
	Devs::m_CameraBoxAlignRight->SetCameraInfo(CameraInfo);
	PateData = Devs::m_CameraBoxAlignRight->GetPatFindData();
	Devs::m_CameraBoxAlignRight->SetPatFindData(PateData);
	Devs::m_CameraBoxAlignRight->OnInspPattern();
	PateData = Devs::m_CameraBoxAlignRight->GetPatFindData();

	*dDiffPosX = PateData.dPosX;
	*dDiffPosY = PateData.dPosY;
#else
	*dDiffPosX = 0.0;
	*dDiffPosY = 0.0;
#endif
#ifndef SIM_MODE
	if (PateData.dScore < 60.0) return FALSE;
#endif
	return TRUE;
}
#pragma endregion

#pragma region //Uvw
BOOL CBoxMotion::UVWStageAlignMove(int nAlignMode, double dCmdPointXY[4][2], double dActPointXY[4][2]) //KJT 20200830
{
	int nRtn;
	double dUvwPos[3] = { 0.0 };
	double dUvwVel[3] = { 0.0 };
	double dUvwAccel[3] = { 0.0 };
	double dUvwDecel[3] = { 0.0 };

	double dVel = 1.0;			// 10.0;//pDlg->m_dJogSpeed[m_nSpeedMode]; // Üù????Ù® ?Ù®ÙÒ?Üù? 10?Ù¬?? ???Ù´?? 20170804 by lsh
	double dAccel = dVel * 0.5;	// *2.0;
	double dDecel = dVel * 0.5;	// *2.0;

	double dXYT[3] = { 0.0 };
	double dXYTR[3] = { 0.0 };
	double dError[3] = { 0.0 };
	double dX, dY, dT;
	CString Str;

	double RefT[4] = { 0.0, };
	double NewPositionT[4] = { 0.0, };
	double DiffT[4] = { 0.0, };
	double dUVWX[3] = { 0.0, };
	double DiffPosition[3] = { 0.0, };
	double R = 0.0;
	double m_AlignRefPointValue[4][2];
	double m_AlignVisionResultValue[4][2];

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

	Make2PointAlignData(3, dCmdPointXY[0], dCmdPointXY[3], dActPointXY[0], dActPointXY[3], &dX, &dY, &dT);

	dXYT[0] = -dX;
	dXYT[1] = -dY;
	dXYT[2] = -dT;

	dError[0] = dXYT[0];
	dError[1] = dXYT[1];
	dError[2] = dXYT[2] * (180.0 / PI);

	SharedInfo::UvwCmdPos[MASK_UVW][0] += dError[0];
	dXYT[0] = SharedInfo::UvwCmdPos[MASK_UVW][0];

	SharedInfo::UvwCmdPos[MASK_UVW][1] += dError[1];
	dXYT[1] = SharedInfo::UvwCmdPos[MASK_UVW][1];

	SharedInfo::UvwCmdPos[MASK_UVW][2] += dError[2];
	dXYT[2] = SharedInfo::UvwCmdPos[MASK_UVW][2];

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

	nRtn = Devs::MotionIf.UvwPosMove(MASK_UVW, dUvwPos, dUvwVel, dUvwAccel, dUvwDecel, 0);
	TRACE(_T("LoadingStage UvwPosMove dUvwPos[0]:%.5f, dUvwPos[1]:%.5f, dUvwPos[2]:%.5f\n"), dUvwPos[0], dUvwPos[1], dUvwPos[2]);

	return nRtn;
}
void CBoxMotion::Make2PointAlignData(int nNo, double dRefLeftXY[2], double dRefRightXY[2], double dObjLeftXY[2], double dObjRightXY[2], double *dX, double *dY, double *dT)
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
#pragma endregion

BOOL CBoxMotion::LoadingStageUvw_HomeStart()
{
	m_bMotionDone = FALSE;
	SetStep(eLOADING_STAGE_ORIGIN_SERVO_ALL_OFF, _T("eLOADING_STAGE_ORIGIN_SERVO_ALL_OFF"));
	return TRUE;
}

BOOL CBoxMotion::IsAxisHome(UINT nAxisNo)
{
	return SharedInfo::AxisHomeStatus[nAxisNo];
}

BOOL CBoxMotion::MoveAxis(enum_Axis eAxis, double dPos)
{
	double	dSpeed = 0.0, dAccel = 0.0, dDecel = 0.0;

	//ÇöÀç ¸ðÅÍÀÇ ÆÄ¶ó¹ÌÅÍ ¹Þ¾Æ¿À±â
	if (!GetAxisWorkParam(eAxis, &dSpeed, &dAccel, &dDecel)) return FALSE;
	//ÇØ´ç ¸ðÅÍ¿¡ ÆÄ¶ó¹ÌÅÍ Àü´Þ
	AbsMove(eAxis, dPos, dSpeed, dAccel, dDecel);
	return TRUE;
}
BOOL CBoxMotion::IsMoveDone(enum_Axis eAxis, double dPos)
{
	double dCmdPos = SharedInfo::GetCmdPos(eAxis);
	return (IsSamePosition(dCmdPos, dPos) && IsMotionDone(eAxis));
}

int CBoxMotion::UVWStagePosMove(double UVW[3], double dVel[3], double dAccel[3], double dDecel[3])
{
#if !UVW_MOVE_TYPE
	//KJT 20210304. FMM
	XYTToUVW(UVW[0], UVW[1], UVW[2], &m_dUVWTargetPos[0], &m_dUVWTargetPos[1], &m_dUVWTargetPos[2]);
	m_dUVWTargetPos[0] += SharedInfo::AxisCmdPos[REMOTE_AXIS_AJIN_LOADING_STAGE_Y1];
	m_dUVWTargetPos[1] += SharedInfo::AxisCmdPos[REMOTE_AXIS_AJIN_LOADING_STAGE_Y2];
	m_dUVWTargetPos[2] += SharedInfo::AxisCmdPos[REMOTE_AXIS_AJIN_LOADING_STAGE_X];
#endif

#ifndef SIM_MODE
	Devs::MotionIf.UvwPosMove(MASK_UVW, UVW, dVel, dAccel, dDecel, eMOTION_REL);
#endif
	return 0;
}
BOOL CBoxMotion::IsUVWStagePos(double UVW[3])
{
	if (SharedInfo::AxisInMotionStatus[REMOTE_AXIS_AJIN_LOADING_STAGE_Y1] == 0 &&
		SharedInfo::AxisInMotionStatus[REMOTE_AXIS_AJIN_LOADING_STAGE_Y2] == 0 &&
		SharedInfo::AxisInMotionStatus[REMOTE_AXIS_AJIN_LOADING_STAGE_X] == 0)
	{
#if 1
		double dUvwPos[3] = { 0.0, };
		Devs::MotionIf.UvwGetTargetPos(MASK_UVW, dUvwPos);
		Sleep(100);
#endif//
		//sjc
		if (IsSamePosition(SharedInfo::dUVWTargetPos[MASK_UVW][0], SharedInfo::AxisCmdPos[REMOTE_AXIS_AJIN_LOADING_STAGE_X]) &&
			IsSamePosition(SharedInfo::dUVWTargetPos[MASK_UVW][1], SharedInfo::AxisCmdPos[REMOTE_AXIS_AJIN_LOADING_STAGE_Y1]) &&
			IsSamePosition(SharedInfo::dUVWTargetPos[MASK_UVW][2], SharedInfo::AxisCmdPos[REMOTE_AXIS_AJIN_LOADING_STAGE_Y2]))
		{
			Sleep(100); //Temp
			return TRUE;
		}
	}
	
	return FALSE;
}
BOOL CBoxMotion::GetUVWPos(double *dRefPosX, double *dRefPosY, double *dDiffPosX, double *dDiffPosY, double *dUVWX, double *dUVWY, double *dUVWZ, BOOL b2PointFlag)
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

#pragma region //Loading Stage UVW
BOOL CBoxMotion::LoadingStageUVW_WaitPos()
{
	CString Str = _T("");
	double dVel = 1.;
	double dAccel = dVel * 2.0;
	double dDecel = dVel * 2.0;
	double dUvwPos[3] = { 0.0, 0.0, 0.0 };
	double dUvwVel[3] = { 1.0, 1.0, 1.0 };
	double dUvwAccel[3] = { 2.0, 2.0, 2.0 };
	double dUvwDecel[3] = { 2.0, 2.0, 2.0 };
	double dUVWScale = 2;

	dUvwPos[0] = CManualData::m_ManualDataBox.Info.m_dLoadingStageX_Wait_Pos;
	dUvwPos[1] = CManualData::m_ManualDataBox.Info.m_dLoadingStageY_Wait_Pos;
	dUvwPos[2] = CManualData::m_ManualDataBox.Info.m_dLoadingStageT_Wait_Pos;

	dUvwVel[0] = dVel;
	dUvwVel[1] = dVel;
	dUvwVel[2] = dVel;
	dUvwAccel[0] = dUvwVel[0] * dUVWScale;
	dUvwAccel[1] = dUvwVel[1] * dUVWScale;
	dUvwAccel[2] = dUvwVel[2] * dUVWScale;
	dUvwDecel[0] = dUvwVel[0] * dUVWScale;
	dUvwDecel[1] = dUvwVel[1] * dUVWScale;
	dUvwDecel[2] = dUvwVel[2] * dUVWScale;

	Devs::m_BoxMotion.UVWStagePosMove(dUvwPos, dUvwVel, dUvwAccel, dUvwDecel);

	Str.Format(_T("Loading Stage UVW Move To Wait Pos X:%.5f, Y:%.5f, T:%.5f)"), dUvwPos[0], dUvwPos[1], dUvwPos[2]);
	Total_Msg(Str);

	return TRUE;
}
BOOL CBoxMotion::LoadingStageUVW_StickLoadPos()
{
	CString Str = _T("");
	double dVel = 1.;
	double dAccel = dVel * 2.0;
	double dDecel = dVel * 2.0;
	double dUvwPos[3] = { 0.0, 0.0, 0.0 };
	double dUvwVel[3] = { 1.0, 1.0, 1.0 };
	double dUvwAccel[3] = { 2.0, 2.0, 2.0 };
	double dUvwDecel[3] = { 2.0, 2.0, 2.0 };
	double dUVWScale = 2;

	dUvwPos[0] = CManualData::m_ManualDataBox.Info.m_dLoadingStageX_StickLoad_Pos;
	dUvwPos[1] = CManualData::m_ManualDataBox.Info.m_dLoadingStageY_StickLoad_Pos;
	dUvwPos[2] = CManualData::m_ManualDataBox.Info.m_dLoadingStageT_StickLoad_Pos;

	dUvwVel[0] = dVel;
	dUvwVel[1] = dVel;
	dUvwVel[2] = dVel;
	dUvwAccel[0] = dUvwVel[0] * dUVWScale;
	dUvwAccel[1] = dUvwVel[1] * dUVWScale;
	dUvwAccel[2] = dUvwVel[2] * dUVWScale;
	dUvwDecel[0] = dUvwVel[0] * dUVWScale;
	dUvwDecel[1] = dUvwVel[1] * dUVWScale;
	dUvwDecel[2] = dUvwVel[2] * dUVWScale;

	Devs::m_BoxMotion.UVWStagePosMove(dUvwPos, dUvwVel, dUvwAccel, dUvwDecel);

	Str.Format(_T("Loading Stage UVW Move To StickLoad Pos X:%.5f, Y:%.5f, T:%.5f)"), dUvwPos[0], dUvwPos[1], dUvwPos[2]);
	Total_Msg(Str);

	return TRUE;
}
BOOL CBoxMotion::LoadingStageUVW_StickUnloadPos()
{
	CString Str = _T("");
	double dVel = 1.;
	double dAccel = dVel * 2.0;
	double dDecel = dVel * 2.0;
	double dUvwPos[3] = { 0.0, 0.0, 0.0 };
	double dUvwVel[3] = { 1.0, 1.0, 1.0 };
	double dUvwAccel[3] = { 2.0, 2.0, 2.0 };
	double dUvwDecel[3] = { 2.0, 2.0, 2.0 };
	double dUVWScale = 2;

	dUvwPos[0] = CManualData::m_ManualDataBox.Info.m_dLoadingStageX_StickUnload_Pos;
	dUvwPos[1] = CManualData::m_ManualDataBox.Info.m_dLoadingStageY_StickUnload_Pos;
	dUvwPos[2] = CManualData::m_ManualDataBox.Info.m_dLoadingStageT_StickUnload_Pos;

	dUvwVel[0] = dVel;
	dUvwVel[1] = dVel;
	dUvwVel[2] = dVel;
	dUvwAccel[0] = dUvwVel[0] * dUVWScale;
	dUvwAccel[1] = dUvwVel[1] * dUVWScale;
	dUvwAccel[2] = dUvwVel[2] * dUVWScale;
	dUvwDecel[0] = dUvwVel[0] * dUVWScale;
	dUvwDecel[1] = dUvwVel[1] * dUVWScale;
	dUvwDecel[2] = dUvwVel[2] * dUVWScale;

	Devs::m_BoxMotion.UVWStagePosMove(dUvwPos, dUvwVel, dUvwAccel, dUvwDecel);

	Str.Format(_T("Loading Stage UVW Move To StickUnload Pos X:%.5f, Y:%.5f, T:%.5f)"), dUvwPos[0], dUvwPos[1], dUvwPos[2]);
	Total_Msg(Str);

	return TRUE;
}

BOOL CBoxMotion::Is_LoadingStageUVW_WaitPos()
{
	if (SharedInfo::AxisInMotionStatus[REMOTE_AXIS_AJIN_LOADING_STAGE_Y1] == 0 &&
		SharedInfo::AxisInMotionStatus[REMOTE_AXIS_AJIN_LOADING_STAGE_Y2] == 0 &&
		SharedInfo::AxisInMotionStatus[REMOTE_AXIS_AJIN_LOADING_STAGE_X] == 0)
	{
		double dX = CManualData::m_ManualDataBox.Info.m_dLoadingStageX_Wait_Pos;
		double dY = CManualData::m_ManualDataBox.Info.m_dLoadingStageY_Wait_Pos;
		double dT = CManualData::m_ManualDataBox.Info.m_dLoadingStageT_Wait_Pos;
		if (IsSamePosition(dX, SharedInfo::UvwCmdPos[MASK_UVW][0]) &&
			IsSamePosition(dY, SharedInfo::UvwCmdPos[MASK_UVW][1]) &&
			IsSamePosition(dT, SharedInfo::UvwCmdPos[MASK_UVW][2]))
		{
			return TRUE;
		}
	}

	return FALSE;
}
BOOL CBoxMotion::Is_LoadingStageUVW_StickLoadPos()
{
	if (SharedInfo::AxisInMotionStatus[REMOTE_AXIS_AJIN_LOADING_STAGE_Y1] == 0 &&
		SharedInfo::AxisInMotionStatus[REMOTE_AXIS_AJIN_LOADING_STAGE_Y2] == 0 &&
		SharedInfo::AxisInMotionStatus[REMOTE_AXIS_AJIN_LOADING_STAGE_X] == 0)
	{
		double dX = CManualData::m_ManualDataBox.Info.m_dLoadingStageX_StickLoad_Pos;
		double dY = CManualData::m_ManualDataBox.Info.m_dLoadingStageY_StickLoad_Pos;
		double dT = CManualData::m_ManualDataBox.Info.m_dLoadingStageT_StickLoad_Pos;
		if (IsSamePosition(dX, SharedInfo::UvwCmdPos[MASK_UVW][0]) &&
			IsSamePosition(dY, SharedInfo::UvwCmdPos[MASK_UVW][1]) &&
			IsSamePosition(dT, SharedInfo::UvwCmdPos[MASK_UVW][2]))
		{
			return TRUE;
		}
	}

	return FALSE;
}
BOOL CBoxMotion::Is_LoadingStageUVW_StickUnloadPos()
{
	if (SharedInfo::AxisInMotionStatus[REMOTE_AXIS_AJIN_LOADING_STAGE_Y1] == 0 &&
		SharedInfo::AxisInMotionStatus[REMOTE_AXIS_AJIN_LOADING_STAGE_Y2] == 0 &&
		SharedInfo::AxisInMotionStatus[REMOTE_AXIS_AJIN_LOADING_STAGE_X] == 0)
	{
		double dX = CManualData::m_ManualDataBox.Info.m_dLoadingStageX_StickUnload_Pos;
		double dY = CManualData::m_ManualDataBox.Info.m_dLoadingStageY_StickUnload_Pos;
		double dT = CManualData::m_ManualDataBox.Info.m_dLoadingStageT_StickUnload_Pos;
		if (IsSamePosition(dX, SharedInfo::UvwCmdPos[MASK_UVW][0]) &&
			IsSamePosition(dY, SharedInfo::UvwCmdPos[MASK_UVW][1]) &&
			IsSamePosition(dT, SharedInfo::UvwCmdPos[MASK_UVW][2]))
		{
			return TRUE;
		}
	}

	return FALSE;
}
#pragma endregion

#pragma region //BoxAlignCamera YL
//Move
BOOL CBoxMotion::BoxAlignCameraYL_WaitPos()
{
	//21.02.04 sjc no box cam servo
	return TRUE;
	/*CString Str = _T("");
	enum_Axis eAxis = AXIS_BOX_ALIGN_CAMERA_YL;
	double dPos = CManualData::m_ManualDataBox.Info.m_dBoxAlignCameraYL_Wait_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("BoxAlignCamera YL Move To Wait Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;*/
}
BOOL CBoxMotion::BoxAlignCameraYL_InspectionPos()
{
	//21.02.04 sjc no box cam servo
	return TRUE;
	//CString Str = _T("");
	//enum_Axis eAxis = AXIS_BOX_ALIGN_CAMERA_YL;
	//double dPos = CManualData::m_ManualDataBox.Info.m_dBoxAlignCameraYL_Inspection_Pos;

	//if (CheckPosInterlock(dPos) == FALSE) //!!
	//	return FALSE;

	//BOOL bRtn = MoveAxis(eAxis, dPos);
	//if (bRtn == TRUE)
	//{
	//	Str.Format(_T("BoxAlignCamera YL Move To Inspection Pos (Pos : %.5f)"), dPos);
	//	Total_Msg(Str);
	//}

	//return bRtn;
}
//MoveDone Check
BOOL CBoxMotion::Is_BoxAlignCameraYL_WaitPos()
{
	//21.02.04 sjc no box cam servo
	return TRUE;
	/*enum_Axis eAxis = AXIS_BOX_ALIGN_CAMERA_YL;
	double dPos = CManualData::m_ManualDataBox.Info.m_dBoxAlignCameraYL_Wait_Pos;
	return IsMoveDone(eAxis, dPos);*/
}
BOOL CBoxMotion::Is_BoxAlignCameraYL_InspectionPos()
{
	//21.02.04 sjc no box cam servo
	return TRUE;
	/*enum_Axis eAxis = AXIS_BOX_ALIGN_CAMERA_YL;
	double dPos = CManualData::m_ManualDataBox.Info.m_dBoxAlignCameraYL_Inspection_Pos;
	return IsMoveDone(eAxis, dPos);*/
}
#pragma region

#pragma region //BoxAlignCamera YR
//Move
BOOL CBoxMotion::BoxAlignCameraYR_WaitPos()
{
	//21.02.04 sjc no box cam servo
	return TRUE;
	//CString Str = _T("");
	//enum_Axis eAxis = AXIS_BOX_ALIGN_CAMERA_YR;
	//double dPos = CManualData::m_ManualDataBox.Info.m_dBoxAlignCameraYR_Wait_Pos;
	//BOOL bRtn = MoveAxis(eAxis, dPos);
	//if (bRtn == TRUE)
	//{
	//	Str.Format(_T("BoxAlignCamera YR Move To Wait Pos (Pos : %.5f)"), dPos);
	//	Total_Msg(Str);
	//}

	//return bRtn;
}
BOOL CBoxMotion::BoxAlignCameraYR_InspectionPos()
{
	//21.02.04 sjc no box cam servo
	return TRUE;
	//CString Str = _T("");
	//enum_Axis eAxis = AXIS_BOX_ALIGN_CAMERA_YR;
	//double dPos = CManualData::m_ManualDataBox.Info.m_dBoxAlignCameraYR_Inspection_Pos;

	//if (CheckPosInterlock(dPos) == FALSE) //!!
	//	return FALSE;

	//BOOL bRtn = MoveAxis(eAxis, dPos);
	//if (bRtn == TRUE)
	//{
	//	Str.Format(_T("BoxAlignCamera YR Move To Inspection Pos (Pos : %.5f)"), dPos);
	//	Total_Msg(Str);
	//}

	//return bRtn;
}
//MoveDone Check
BOOL CBoxMotion::Is_BoxAlignCameraYR_WaitPos()
{
	//21.02.04 sjc no box cam servo
	return TRUE;
	/*enum_Axis eAxis = AXIS_BOX_ALIGN_CAMERA_YR;
	double dPos = CManualData::m_ManualDataBox.Info.m_dBoxAlignCameraYR_Wait_Pos;
	return IsMoveDone(eAxis, dPos);*/
}
BOOL CBoxMotion::Is_BoxAlignCameraYR_InspectionPos()
{
	//21.02.04 sjc no box cam servo
	return TRUE;
	/*enum_Axis eAxis = AXIS_BOX_ALIGN_CAMERA_YR;
	double dPos = CManualData::m_ManualDataBox.Info.m_dBoxAlignCameraYR_Inspection_Pos;
	return IsMoveDone(eAxis, dPos);*/
}
#pragma region

BOOL CBoxMotion::BoxMagnetic_Chuck_On()
{
	//Devs::m_BaseMotion.SetDOutputBitValue(_DOUT_MAGNETIC_CHUCK_ON, TRUE); 
	return TRUE;	
}

BOOL CBoxMotion::BoxMagnetic_Chuck_Off()
{
	//Devs::m_BaseMotion.SetDOutputBitValue(_DOUT_MAGNETIC_CHUCK_ON, FALSE);
	return TRUE;
}

BOOL CBoxMotion::Is_BoxMagnetic_Chuck_On()
{
	//if (SharedInfo::DOutputValue[_DOUT_MAGNETIC_CHUCK_ON] == 1)
	//	return TRUE;
	//else
		return FALSE;
}

BOOL CBoxMotion::Is_BoxMagnetic_Chuck_Off()
{
	//if (SharedInfo::DOutputValue[_DOUT_MAGNETIC_CHUCK_ON] == 0)
	//	return TRUE;
	//else
		return FALSE;
}

BOOL CBoxMotion::CheckPosInterlock(double dTargetPos)
{
	double dPosGantryY = SharedInfo::GetActPos(AXIS_VIRTUAL_GANTRY_Y);
	if (dPosGantryY < CManualData::m_ManualDataGantry.Info.m_dGantry_Y_Paper_Unload_Pos)
	{
		Total_Msg(_T("Gantry Y Pos Check !!!"));
		return FALSE;
	}

	return TRUE;
}