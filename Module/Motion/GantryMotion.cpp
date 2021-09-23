#include "stdafx.h"
#include "GantryMotion.h"
#include "VisionAgent.h"
#include "VisionAgentDlg.h"
#include "Vision/Devs.h"
#include "Vision/SharedInfo.h"
#include "Log/Logger.h"
#include "Motion/LoaderMotion.h"
#include "FmmLight1.h"
#include "Data/ManualData.h"
#include "Data/SystemData.h"
#include "Data/ModelData.h"
#include "Data/MachineData.h"
//#include "NavMotorCDlg.h"
#include "SystemDlg.h"

CGantryMotion::CGantryMotion()
{
	m_bApplySwAlignData = FALSE;
	m_bApplyGlassMappingData = FALSE;
}


CGantryMotion::~CGantryMotion()
{
}

BOOL CGantryMotion::InitProcess()
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
	InitParam();

	return TRUE;
}

BOOL CGantryMotion::InitParam()
{
#ifndef SIM_MODE
	pMappingProc = &Devs::m_MappingProc;
#endif

#ifndef SIM_MODE
	//m_pFocusValue = &SharedInfo::m_dLaserDispFVal;
#endif


	//m_dCameraROffsetX = &SharedInfo::TargetOffset.Dist_MT10X_RT10X_X;
	//m_dCameraROffsetY = &SharedInfo::TargetOffset.Dist_MT10X_RT10X_Y;

#ifndef SIM_MODE
	m_bAutoFocusingFlag = TRUE;
	//pMappingProc->InitializeGlassMapping(eMAPPING_ID_10X);
	//pMappingProc->InitializeGlassMapping(eMAPPING_ID_PreAlign);

	pMappingProc->LoadGlassMappingFile(eMAPPING_ID_10X);
	pMappingProc->LoadGlassMappingFile(eMAPPING_ID_20X);

	m_dReview10xTargetOffsetXTmp = 0;
	m_dReview10xTargetOffsetYTmp = 0;
	m_dReview10xTargetOffsetX = &m_dReview10xTargetOffsetXTmp;
	m_dReview10xTargetOffsetY = &m_dReview10xTargetOffsetYTmp;

#endif // !SIM_MODE

	m_dBackLightWaitPos[0] = 300;
	m_dBackLightWaitPos[1] = -300;
	return TRUE;
}

BOOL CGantryMotion::EndProcess()
{

	m_StateFinish = FALSE;

	SetStep(eGANTRY_MOTION_EXIT, _T("eGANTRY_MOTION_EXIT"));



	SetStep(eGANTRY_MOTION_IDLE, FALSE);

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

BOOL CGantryMotion::Stop()
{
	m_bStopBit = TRUE;
	SetStop(); //!!
	return TRUE;
}

int CGantryMotion::SetParentDlg(void *pDlg)
{
	m_pParentDlg = pDlg;

	return TRUE;
}

UINT CGantryMotion::MotionThreadFunction(LPVOID lpParam)
{
	CGantryMotion* GantryMotion = NULL;

	GantryMotion = (CGantryMotion*)lpParam;


	GantryMotion->MotionThreadFunctionEntry();


	//GantryMotion->m_bTerminate = 1;

	return 0;
}

VOID CGantryMotion::MotionThreadFunctionEntry(VOID)
{
	int ErrorCheck = 0;
	CString szMsg;
	BOOL bResult;
	double dVel = 5.;
	double dAcc = 10.;
	double dDec = 10;
	int LimitSignal;
	enum_Axis	eAxis;
	//m_dROffset = 0;
	BOOL bRtn = FALSE;
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	while (m_StateFinish)
	{
		WaitForSingleObject(hMotionHandle, INFINITE);
		ResetEvent(hMotionHandle);

		if (SharedInfo::bMachineStopFlag == TRUE)// && m_bStopBit == FALSE)
		{
			m_bStopBit = TRUE;

			SetCurrentStep(eGANTRY_MOTION_IDLE); //KJT 20210318
			continue; //!!
		}

		switch (GetCurrentTotalStep())
		{
		case eGANTRY_MOTION_IDLE:
			break;

#pragma region //Gantry XYZ Move
		case eGANTRY_XYZ_MOVE_START:
			SetStep(eGANTRY_XYZ_MOVE_INTERLOCK_CHECK, _T("eGANTRY_XYZ_MOVE_INTERLOCK_CHECK"));
			break;

		case eGANTRY_XYZ_MOVE_INTERLOCK_CHECK:
			if (CheckGantryXYZMoveInterlock() == FALSE)
			{
				SetStep(eGANTRY_MOTION_ERROR, _T("eGANTRY_MOTION_ERROR"));
			}
			else
			{
				////21.03.01 sjc
				//SharedInfo::LightAllOff();
				////g_CommLight_8ch.SetLight_Review_Coaxial(0);
				////g_CommLight_12ch.SetLight_Review_Ring(0);
				////g_CommLight_8ch.SetLight_PreAlign(0, 0);

				if (m_bZUp)
					SetStep(eGANTRY_Z_MOVE_ALL_WAIT_POS, _T("eGANTRY_Z_MOVE_ALL_WAIT_POS"));
				else
					SetStep(eGANTRY_XY_MOVE_POS, _T("eGANTRY_XY_MOVE_POS"));
			}
			break;

		case eGANTRY_Z_MOVE_ALL_WAIT_POS:
			Move_GantryZ_All_Wait_Pos();

			SetStep(eGANTRY_Z_MOVE_ALL_WAIT_POS_CHECK, _T("eGANTRY_Z_MOVE_ALL_WAIT_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eGANTRY_Z_MOVE_ALL_WAIT_POS_CHECK:
			if (Is_GantryZ_All_Wait_Pos() == TRUE)
			{
				Total_Msg(_T("Gantry Z All Wait Pos Ok"));

				SetStep(eGANTRY_XY_MOVE_POS, _T("eGANTRY_XY_MOVE_POS"));
			}
			else if (IsTimeOut())
			{
				Total_Msg(_T("TimeOut Error !!!"));
				SetStep(eGANTRY_MOTION_ERROR, _T("eGANTRY_MOTION_ERROR"));
			}
			else
			{
				SetCheckStep(eGANTRY_Z_MOVE_ALL_WAIT_POS_CHECK);
			}
			break;

		case eGANTRY_XY_MOVE_POS:
			//SharedInfo::GetMappingPos(m_bApplySwAlignData, m_bApplyGlassMappingData, &m_dTargetPos_X, &m_dTargetPos_Y);
			SharedInfo::GetMappingPos(m_bApplySwAlignData, m_bApplyGlassMappingData, &m_dTargetPos_X, &m_dTargetPos_Y);

			Move_Gantry_X_Pos(m_dTargetPos_X, FALSE);
			Sleep(GANTRY_COM_DELAY);
			Move_Gantry_Y_Pos(m_dTargetPos_Y);

			SetStep(eGANTRY_XY_MOVE_POS_CHECK, _T("eGANTRY_XY_MOVE_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eGANTRY_XY_MOVE_POS_CHECK:
			if (Is_Gantry_X_Pos(m_dTargetPos_X) && Is_Gantry_Y_Pos(m_dTargetPos_Y))
			{
				SetStep(eGANTRY_Z_MOVE_INSPECTION_POS, _T("eGANTRY_Z_MOVE_DOWN_POS"));
			}
			else if (IsTimeOut())
			{
				Total_Msg(_T("TimeOut Error !!!"));
				SetStep(eGANTRY_MOTION_ERROR, _T("eGANTRY_MOTION_ERROR"));
			}
			else
			{
				SetCheckStep(eGANTRY_XY_MOVE_POS_CHECK, _T("eGANTRY_XY_MOVE_POS_CHECK"));
			}
			break;

		case eGANTRY_Z_MOVE_INSPECTION_POS:
			Move_GantryZ1_Pos(m_dTargetPos_Z1);
			Sleep(20); //!!
			//Move_GantryZ2_Pos(m_dTargetPos_Z2);
			//Sleep(20); //!!
			//Move_GantryZ3_Pos(m_dTargetPos_Z3);
			//Sleep(20); //!!

			SetStep(eGANTRY_Z_MOVE_INSPECTION_POS_CHECK, _T("eGANTRY_Z_MOVE_INSPECTION_POS_CHECK"));
			SetTimeOut(TIME_OUT_MOTION);
			break;

		case eGANTRY_Z_MOVE_INSPECTION_POS_CHECK:
			if (Is_Move_GantryZ1_Pos(m_dTargetPos_Z1))
			{
				SetStep(eGANTRY_MOTION_DONE, _T("eGANTRY_MOTION_DONE"));
			}
			else if (IsTimeOut())
			{
				Total_Msg(_T("TimeOut Error !!!"));
				SetStep(eGANTRY_MOTION_ERROR, _T("eGANTRY_MOTION_ERROR"));
			}
			else
			{
				SetCheckStep(eGANTRY_Z_MOVE_INSPECTION_POS_CHECK);
			}
			break;
#pragma endregion

		case eGANTRY_MOTION_DONE:
			SetStep(eGANTRY_MOTION_IDLE, _T("eGANTRY_MOTION_DONE"));

			if (m_StateComplete != NULL)
			{
				m_StateComplete(NULL);
			}

			Sleep(200);
			m_bMotionDone = TRUE;
			//SharedInfo::MachineState.bSemiAutoRunFlag = FALSE;
			break;

		case eGANTRY_MOTION_EXIT:
			//SetStep(eGANTRY_MOTION_EXIT,FALSE);
			m_StateFinish = FALSE;
			break;
		}

		Sleep(100); //!!
	}
}

BOOL CGantryMotion::MoveAxis(enum_Axis eAxis, double dPos)
{
	double	dSpeed = 0.0, dAccel = 0.0, dDecel = 0.0;

	//현재 모터의 파라미터 받아오기
	if (!GetAxisWorkParam(eAxis, &dSpeed, &dAccel, &dDecel)) return FALSE;

#if 0
	dSpeed = 5.0;
	dAccel = 20.0;
	dDecel = 20.0;
#endif

	//해당 모터에 파라미터 전달
	AbsMove(eAxis, dPos, dSpeed, dAccel, dDecel);
	return TRUE;
}
BOOL CGantryMotion::MoveAxis_With_BackLightX(enum_Axis eAxis, double dPos, BOOL bWithMoveBackLightX, double dAOICamOffset/* = 0.0*/, BOOL bDirBwd/* = FALSE*/, enum_AOI_Vel_Level eAoiVelLevel/* = eAOI_Vel_50*/)
{
	double	dSpeed = 0.0, dAccel = 0.0, dDecel = 0.0;

	//현재 모터의 파라미터 받아오기
	if (!GetAxisWorkParam(eAxis, &dSpeed, &dAccel, &dDecel)) return FALSE;

#if 0
	dSpeed = 5.0;
	dAccel = 20.0;
	dDecel = 20.0;
#endif

	//해당 모터에 파라미터 전달
	AbsMove(eAxis, dPos, dSpeed, dAccel, dDecel, bWithMoveBackLightX, dAOICamOffset, bDirBwd, eAoiVelLevel);
	return TRUE;
}
BOOL CGantryMotion::IsMoveDone(enum_Axis eAxis, double dPos)
{
	double dCmdPos = SharedInfo::GetCmdPos(eAxis);
	return (IsSamePosition(dCmdPos, dPos) && IsMotionDone(eAxis));
}

#pragma region //Pos Move
//Move
BOOL	CGantryMotion::Move_Gantry_X_Pos(double dPos, BOOL bWithMoveBackLightX, double dAOICamOffset /* = 0.0*/, BOOL bDirBwd/* = FALSE*/, enum_AOI_Vel_Level eAoiVelLevel/* = eAOI_Vel_50*/)
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_GANTRY_X;
	BOOL bRtn = MoveAxis_With_BackLightX(eAxis, dPos, bWithMoveBackLightX, dAOICamOffset, bDirBwd, eAoiVelLevel);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Gantry X Move  (Pos : %.5f)"), dPos);
		Total_Msg(Str);

		if (bWithMoveBackLightX)
		{
			Str.Format(_T("With BackLight X Move  (Pos : %.5f)"), dPos + dAOICamOffset);
			Total_Msg(Str);
		}
	}

	return bRtn;
}
BOOL	CGantryMotion::Move_Gantry_Y_Pos(double dPos)
{
	BOOL bRtn = FALSE;
	return bRtn;
}
BOOL	CGantryMotion::Move_Gantry_Z1_Pos(double dPos) //PreAlign, Review Z
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_CAMERA_Z1;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Gantry Z1 Move (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
//BOOL	CGantryMotion::Move_Gantry_Z2_Pos(double dPos) //AOI Z
//{
//	CString Str = _T("");
//	enum_Axis eAxis = AXIS_CAMERA_Z2;
//	BOOL bRtn = MoveAxis(eAxis, dPos);
//	if (bRtn == TRUE)
//	{
//		Str.Format(_T("Gantry Z2 Move (Pos : %.5f)"), dPos);
//		Total_Msg(Str);
//	}
//
//	return bRtn;
//}
//BOOL	CGantryMotion::Move_Gantry_Z3_Pos(double dPos) //AOI Z
//{
//	CString Str = _T("");
//	enum_Axis eAxis = AXIS_CAMERA_Z3;
//	BOOL bRtn = MoveAxis(eAxis, dPos);
//	if (bRtn == TRUE)
//	{
//		Str.Format(_T("Gantry Z2 Move (Pos : %.5f)"), dPos);
//		Total_Msg(Str);
//	}
//
//	return bRtn;
//}
//Move Done Check
BOOL	CGantryMotion::Is_Gantry_X_Pos(double dPos)
{
	enum_Axis eAxis = AXIS_GANTRY_X;
	return IsMoveDone(eAxis, dPos);
}
BOOL	CGantryMotion::Is_Gantry_Y_Pos(double dPos)
{
	enum_Axis eAxis = AXIS_GANTRY_Y1;
	return IsMoveDone(eAxis, dPos);
}
BOOL	CGantryMotion::Is_Gantry_Z1_Pos(double dPos) //PreAlign, Review Z
{
	enum_Axis eAxis = AXIS_CAMERA_Z1;
	return IsMoveDone(eAxis, dPos);
}
//BOOL	CGantryMotion::Is_Gantry_Z2_Pos(double dPos) //AOI Z
//{
//	enum_Axis eAxis = AXIS_CAMERA_Z2;
//	return IsMoveDone(eAxis, dPos);
//}
//BOOL	CGantryMotion::Is_Gantry_Z3_Pos(double dPos) //AOI Z
//{
//	enum_Axis eAxis = AXIS_CAMERA_Z3;
//	return IsMoveDone(eAxis, dPos);
//}

BOOL    CGantryMotion::ConvertTo20XPos(double *dPosX, double *dPosY)
{
	*dPosX = *dPosX - CSystemData::m_Coordinate.Info.dOffsetReview10xTo20x_X;
	*dPosY = *dPosY - CSystemData::m_Coordinate.Info.dOffsetReview10xTo20x_Y;

	return TRUE;
}

////XYZ
BOOL CGantryMotion::Move_GantryXYZ_Review10X(double dPosX, double dPosY, BOOL UpMoveFlag, BOOL MappingFlag, BOOL LaserValueFlag, BOOL bThetaFlag, BOOL SwMappingFlag)
{
	DOUBLE dXR_Offset = 0.0;
	DOUBLE dYR_Offset = 0.0;
	//DOUBLE dMappingOffsetY = 0.0;

	//if (fabs(*m_dCameraROffsetX) > CAMERA_OFFSET_ERROR_LIMIT || fabs(*m_dCameraROffsetY) > CAMERA_OFFSET_ERROR_LIMIT)
	//{
	//	Log_Msg(_T("Camera Offset is too High"));
	//	return 0;
	//}
	m_bMotionDone = FALSE;
	m_bReviewCAMFlag = TRUE;

	m_dTargetPos_Z1 = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Wait_Pos;
	//m_dTargetPos_Z2 = CManualData::m_ManualDataGantry.Info.m_dGantry_Z2_Wait_Pos;
	//m_dTargetPos_Z3 = CManualData::m_ManualDataGantry.Info.m_dGantry_Z3_Wait_Pos;
	m_dTargetPos_X = dPosX;
	m_dTargetPos_Y = dPosY;

#ifndef SIM_MODE
	if (bThetaFlag == TRUE)
	{
		pMappingProc->GetXYTAlign_CalibPosXY(1, &m_dTargetPos_X, &m_dTargetPos_Y);
	}

	if (SwMappingFlag == TRUE)
	{
		pMappingProc->GetSWMapping_CalibPosXY(eMAPPING_ID_10X, &m_dTargetPos_X, &m_dTargetPos_Y);
	}

	if (MappingFlag == TRUE)
	{
		pMappingProc->GetGlassMapping_CalibPosXY(eMAPPING_ID_10X, &m_dTargetPos_X, &m_dTargetPos_Y);
	}

	if (fabs(*m_dReview10xTargetOffsetX) > CAMERA_OFFSET_ERROR_LIMIT || fabs(*m_dReview10xTargetOffsetY) > CAMERA_OFFSET_ERROR_LIMIT)
	{
		Total_Msg(_T("Camera Offset is too High"));
		return 0;
	}

	m_dTargetPos_X += *m_dReview10xTargetOffsetX;
	m_dTargetPos_Y += *m_dReview10xTargetOffsetY;

#endif

	m_bStopBit = FALSE;	             SharedInfo::bMachineStopFlag = FALSE;

	if (UpMoveFlag == TRUE)
		SetStep(eGANTRY_Z_MOVE_ALL_WAIT_POS, _T("eGANTRY_Z_MOVE_ALL_WAIT_POS"));
	else
		SetStep(eGANTRY_XY_MOVE_POS, _T("eGANTRY_XY_MOVE_POS"));
	return TRUE;
}
BOOL CGantryMotion::Is_MoveDone()
{
	return m_bMotionDone;
}
#pragma endregion

#pragma region //Gantry X
//Move
BOOL	CGantryMotion::Move_Gantry_X_Wait_Pos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_GANTRY_X;
	double dPos = CManualData::m_ManualDataGantry.Info.m_dGantry_X_Wait_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Gantry X Move To Wait Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
//MoveDone Check
BOOL	CGantryMotion::Is_Gantry_X_Wait_Pos()
{
	enum_Axis eAxis = AXIS_GANTRY_X;
	double	dPos = CManualData::m_ManualDataGantry.Info.m_dGantry_X_Wait_Pos;
	return IsMoveDone(eAxis, dPos);
}
#pragma endregion

#pragma region //Gantry Y
//Move
BOOL	CGantryMotion::Move_Gantry_Y_Wait_Pos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_GANTRY_Y1;
	double dPos = CManualData::m_ManualDataGantry.Info.m_dGantry_Y_Wait_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Gantry Y Move To Wait Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
BOOL	CGantryMotion::Move_Gantry_Y_StickLoadInBox_Pos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_GANTRY_Y1;
	double dPos = CManualData::m_ManualDataGantry.Info.m_dGantry_Y_Stick_Load_In_Box_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Gantry Y Move To Stick Load In Box Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
BOOL	CGantryMotion::Move_Gantry_Y_PaperUnload_Pos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_GANTRY_Y1;
	double dPos = CManualData::m_ManualDataGantry.Info.m_dGantry_Y_Paper_Unload_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Gantry Y Move To Paper Unload Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
BOOL	CGantryMotion::Move_Gantry_Y_StickUnloadToStage_Pos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_GANTRY_Y1;
	double dPos = CManualData::m_ManualDataGantry.Info.m_dGantry_Y_Stick_Unload_To_Stage_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Gantry Y Move To Stick Unload To Stage Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
BOOL	CGantryMotion::Move_Gantry_Y_StickLoadInStage_Pos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_GANTRY_Y1;
	double dPos = CManualData::m_ManualDataGantry.Info.m_dGantry_Y_Stick_Load_In_Stage_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Gantry Y Move To Stick Load In Stage Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
BOOL	CGantryMotion::Move_Gantry_Y_StickUnloadToBox_Pos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_GANTRY_Y1;
	double dPos = CManualData::m_ManualDataGantry.Info.m_dGantry_Y_Stick_Unload_To_Box_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Gantry Y Move To Stick Unload To Box Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
//21.02.15 sjc
/*BOOL	Move_Gantry_Y_StickLoading_Safe_Pos();
BOOL	Move_Gantry_Y_StickUnloading_Safe_Pos();
*/
BOOL	CGantryMotion::Move_Gantry_Y_StickLoading_Safe_Pos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_GANTRY_Y1;
	double dPos = CManualData::m_ManualDataGantry.Info.m_dGantry_Y_Loading_Safe_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Gantry Y Move To Stick Loading Safe Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}

BOOL	CGantryMotion::Move_Gantry_Y_StickUnloading_Safe_Pos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_GANTRY_Y1;
	double dPos = CManualData::m_ManualDataGantry.Info.m_dGantry_Y_Unloading_Safe_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Gantry Y Move To Stick Unloading Safe Pos (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
//MoveDone Check
BOOL	CGantryMotion::Is_Gantry_Y_Wait_Pos()
{
	enum_Axis eAxis = AXIS_GANTRY_Y1;
	double	dPos = CManualData::m_ManualDataGantry.Info.m_dGantry_Y_Wait_Pos;

	return IsMoveDone(eAxis, dPos);
}
BOOL	CGantryMotion::Is_Gantry_Y_StickLoadInBox_Pos()
{
	enum_Axis eAxis = AXIS_GANTRY_Y1;
	double	dPos = CManualData::m_ManualDataGantry.Info.m_dGantry_Y_Stick_Load_In_Box_Pos;

	return IsMoveDone(eAxis, dPos);
}
BOOL	CGantryMotion::Is_Gantry_Y_PaperUnload_Pos()
{
	enum_Axis eAxis = AXIS_GANTRY_Y1;
	double	dPos = CManualData::m_ManualDataGantry.Info.m_dGantry_Y_Paper_Unload_Pos;

	return IsMoveDone(eAxis, dPos);
}
BOOL	CGantryMotion::Is_Gantry_Y_StickUnloadToStage_Pos()
{
	enum_Axis eAxis = AXIS_GANTRY_Y1;
	double	dPos = CManualData::m_ManualDataGantry.Info.m_dGantry_Y_Stick_Unload_To_Stage_Pos;

	return IsMoveDone(eAxis, dPos);
}
BOOL	CGantryMotion::Is_Gantry_Y_StickLoadInStage_Pos()
{
	enum_Axis eAxis = AXIS_GANTRY_Y1;
	double	dPos = CManualData::m_ManualDataGantry.Info.m_dGantry_Y_Stick_Load_In_Stage_Pos;

	return IsMoveDone(eAxis, dPos);
}
BOOL	CGantryMotion::Is_Gantry_Y_StickUnloadToBox_Pos()
{
	enum_Axis eAxis = AXIS_GANTRY_Y1;
	double	dPos = CManualData::m_ManualDataGantry.Info.m_dGantry_Y_Stick_Unload_To_Box_Pos;

	return IsMoveDone(eAxis, dPos);
}
//21.02.15 sjc
BOOL	CGantryMotion::Is_Gantry_Y_StickLoading_Safe_Pos()
{
	enum_Axis eAxis = AXIS_GANTRY_Y1;
	double	dPos = CManualData::m_ManualDataGantry.Info.m_dGantry_Y_Loading_Safe_Pos;

	return IsMoveDone(eAxis, dPos);
}

BOOL	CGantryMotion::Is_Gantry_Y_StickUnloading_Safe_Pos()
{
	enum_Axis eAxis = AXIS_GANTRY_Y1;
	double	dPos = CManualData::m_ManualDataGantry.Info.m_dGantry_Y_Unloading_Safe_Pos;

	return IsMoveDone(eAxis, dPos);
}
#pragma endregion

#pragma region //GantryZ All Wait
BOOL	CGantryMotion::Move_GantryZ_All_Wait_Pos()
{
	BOOL bRtn1 = Move_GantryZ1_Wait_Pos();
	Sleep(20); //!!
	//BOOL bRtn2 = Move_GantryZ2_Wait_Pos();
	//Sleep(20); //!!
	//BOOL bRtn3 = Move_GantryZ3_Wait_Pos();
	//Sleep(20); //!!
	//BOOL bRtn4 = Move_3D_Camera_Sub_Z_Wait_Pos();
	//Sleep(20); //!!

	return (bRtn1);
}
BOOL	CGantryMotion::Is_GantryZ_All_Wait_Pos()
{
	BOOL bRtn1 = Is_GantryZ1_Wait_Pos();
	//BOOL bRtn2 = Is_GantryZ2_Wait_Pos();
	//BOOL bRtn3 = Is_GantryZ3_Wait_Pos();
	//BOOL bRtn4 = Is_3D_Camera_Sub_Z_Wait_Pos();

	return (bRtn1);
}
#pragma endregion

#pragma region //Gantry Z1
//Move
BOOL	CGantryMotion::Move_GantryZ1_Pos(double dPos)
{
	enum_Axis eAxis = AXIS_CAMERA_Z1;

	CString Str = _T("");
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Gantry Z1 Move (Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
BOOL	CGantryMotion::Move_GantryZ1_Wait_Pos()
{
	enum_Axis eAxis = AXIS_CAMERA_Z1;

	CString Str = _T("");
	double dPos = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Wait_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Gantry Z1 Move (Wait Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
BOOL	CGantryMotion::Move_GantryZ1_PreAlign_Pos()
{
	enum_Axis eAxis = AXIS_CAMERA_Z1;

	CString Str = _T("");
	double dPos = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_PreAlign_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Gantry Z1 Move (PreAlign Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}

//
//BOOL	CGantryMotion::Move_GantryZ2_Inspect_3D_Pos()
//{
//	enum_Axis eAxis = AXIS_CAMERA_Z2;
//
//	CString Str = _T("");
//	double dPos = CManualData::m_ManualDataGantry.Info.m_dGantry_Z2_Inspection_3D_Pos;
//	BOOL bRtn = MoveAxis(eAxis, dPos);
//	if (bRtn == TRUE)
//	{
//		Str.Format(_T("Gantry Z2 Move (Inspect 3D Pos : %.5f)"), dPos);
//		Total_Msg(Str);
//	}
//
//	return bRtn;
//}
//
//BOOL	CGantryMotion::Move_GantryZ2_AOI_Review_Pos()
//{
//	enum_Axis eAxis = AXIS_CAMERA_Z2;
//
//	CString Str = _T("");
//	double dPos = CManualData::m_ManualDataGantry.Info.m_dGantry_Z2_AOI_Review_Pos;
//	BOOL bRtn = MoveAxis(eAxis, dPos);
//	if (bRtn == TRUE)
//	{
//		Str.Format(_T("Gantry Z2 Move (AOI Review Pos : %.5f)"), dPos);
//		Total_Msg(Str);
//	}
//
//	return bRtn;
//}

//MoveDone Check
BOOL	CGantryMotion::Is_Move_GantryZ1_Pos(double dPos)
{
	enum_Axis eAxis = AXIS_CAMERA_Z1;
	return IsMoveDone(eAxis, dPos);
}
BOOL	CGantryMotion::Is_GantryZ1_Wait_Pos()
{
	enum_Axis eAxis = AXIS_CAMERA_Z1;
	double	dPos = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Wait_Pos;
	return IsMoveDone(eAxis, dPos);
}
BOOL	CGantryMotion::Is_GantryZ1_PreAlign_Pos()
{
	enum_Axis eAxis = AXIS_CAMERA_Z1;
	double	dPos = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_PreAlign_Pos;
	return IsMoveDone(eAxis, dPos);
}
#pragma endregion

#pragma region //Gantry Z2
//Move
//BOOL	CGantryMotion::Move_GantryZ2_Pos(double dPos)
//{
//	enum_Axis eAxis = AXIS_CAMERA_Z2;
//
//	CString Str = _T("");
//	BOOL bRtn = MoveAxis(eAxis, dPos);
//	if (bRtn == TRUE)
//	{
//		Str.Format(_T("Gantry Z2 Move (Pos : %.5f)"), dPos);
//		Total_Msg(Str);
//	}
//
//	return bRtn;
//}
//BOOL	CGantryMotion::Move_GantryZ2_Wait_Pos()
//{
//	CString Str = _T("");
//	enum_Axis eAxis = AXIS_CAMERA_Z2;
//	double dPos = CManualData::m_ManualDataGantry.Info.m_dGantry_Z2_Wait_Pos;
//	BOOL bRtn = MoveAxis(eAxis, dPos);
//	if (bRtn == TRUE)
//	{
//		Str.Format(_T("Gantry Z2 Move (Wait Pos : %.5f)"), dPos);
//		Total_Msg(Str);
//	}
//
//	return bRtn;
//}
BOOL	CGantryMotion::Move_GantryZ1_InspectionAOI_Pos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_CAMERA_Z1;
	double dPos = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Inspection_AOI_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Gantry Z1 Move (Inspection AOI Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
BOOL CGantryMotion::Move_GantryZ1_InspectionMappingGlassPos()
{
	CString Str = _T("");
	enum_Axis eAxis = AXIS_CAMERA_Z1;
	double dPos = CSystemData::m_Option.Info.m_dAOI_Z_MappingGlassPos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Gantry Z1 Move (Inspection Mapping Glass Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
//MoveDone Check
//BOOL	CGantryMotion::Is_Move_GantryZ2_Pos(double dPos)
//{
//	enum_Axis eAxis = AXIS_CAMERA_Z2;
//	return IsMoveDone(eAxis, dPos);
//}
//BOOL	CGantryMotion::Is_GantryZ2_Wait_Pos()
//{
//	enum_Axis eAxis = AXIS_CAMERA_Z2;
//	double	dPos = CManualData::m_ManualDataGantry.Info.m_dGantry_Z2_Wait_Pos;
//	return IsMoveDone(eAxis, dPos);
//}
BOOL	CGantryMotion::Is_GantryZ1_InspectionAOI_Pos()
{
	enum_Axis eAxis = AXIS_CAMERA_Z1;
	double	dPos = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Inspection_AOI_Pos;
	return IsMoveDone(eAxis, dPos);
}
BOOL	CGantryMotion::Is_GantryZ1_InspectionMappingGlassPos()
{
	enum_Axis eAxis = AXIS_CAMERA_Z1;
	double	dPos = CSystemData::m_Option.Info.m_dAOI_Z_MappingGlassPos;
	return IsMoveDone(eAxis, dPos);
}
#pragma endregion

#pragma region //3D Camera Main Z
//Move
//BOOL CGantryMotion::Move_GantryZ3_Pos(double dPos)
//{
//	////21.02.04 sjc no 3d camera servo
//	//return TRUE;
//	enum_Axis eAxis = AXIS_CAMERA_Z3;
//
//	CString Str = _T("");
//	BOOL bRtn = MoveAxis(eAxis, dPos);
//	if (bRtn == TRUE)
//	{
//		Str.Format(_T("Review Camera Z Move (Pos : %.5f)"), dPos);
//		Total_Msg(Str);
//	}
//
//	return bRtn;
//}
//BOOL	CGantryMotion::Move_GantryZ3_Wait_Pos()
//{
//	////21.02.04 sjc no 3d camera servo
//	//return TRUE;
//	CString Str = _T("");
//	enum_Axis eAxis = AXIS_CAMERA_Z3;
//	double dPos = CManualData::m_ManualDataGantry.Info.m_dGantry_Z3_Wait_Pos;
//	BOOL bRtn = MoveAxis(eAxis, dPos);
//	if (bRtn == TRUE)
//	{
//		Str.Format(_T("Review Camera Z Move (Wait Pos : %.5f)"), dPos);
//		Total_Msg(Str);
//	}
//
//	return bRtn;
//}
BOOL	CGantryMotion::Move_GantryZ1_InspectionReview_Pos()
{
	////21.02.04 sjc no 3d camera servo
	//return TRUE;
	CString Str = _T("");
	enum_Axis eAxis = AXIS_CAMERA_Z1;
	double dPos = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Inspection_Review_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Review Camera Z Move (Inspection Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}
BOOL	CGantryMotion::Move_GantryZ1_InspectionMapping_Pos()
{
	////21.02.04 sjc no 3d camera servo
	//return TRUE;
	CString Str = _T("");
	enum_Axis eAxis = AXIS_CAMERA_Z1;
	double dPos = CManualData::m_ManualDataGantry.Info.m_dGantry_Z3_Mapping_Review_Pos;
	BOOL bRtn = MoveAxis(eAxis, dPos);
	if (bRtn == TRUE)
	{
		Str.Format(_T("Review Camera Z Move (Mapping Pos : %.5f)"), dPos);
		Total_Msg(Str);
	}

	return bRtn;
}

//MoveDone Check
//BOOL	CGantryMotion::Is_Move_GantryZ3_Pos(double dPos)
//{
//	////21.02.04 sjc no 3d camera servo
//	//return TRUE;
//	enum_Axis eAxis = AXIS_CAMERA_Z3;
//	return IsMoveDone(eAxis, dPos);
//}
//BOOL	CGantryMotion::Is_GantryZ3_Wait_Pos()
//{
//	////21.02.04 sjc no 3d camera servo
//	//return TRUE;
//	enum_Axis eAxis = AXIS_CAMERA_Z3; 
//	double	dPos = CManualData::m_ManualDataGantry.Info.m_dGantry_Z3_Wait_Pos;
//	return IsMoveDone(eAxis, dPos);
//}
BOOL	CGantryMotion::Is_GantryZ1_InspectionReview_Pos()
{
	////21.02.04 sjc no 3d camera servo
	//return TRUE;
	enum_Axis eAxis = AXIS_CAMERA_Z1;
	double	dPos = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Inspection_Review_Pos;
	return IsMoveDone(eAxis, dPos);
}
BOOL	CGantryMotion::Is_GantryZ1_InspectionMapping_Pos()
{
	////21.02.04 sjc no 3d camera servo
	//return TRUE;
	enum_Axis eAxis = AXIS_CAMERA_Z1;
	double	dPos = CManualData::m_ManualDataGantry.Info.m_dGantry_Z3_Mapping_Review_Pos;
	return IsMoveDone(eAxis, dPos);
}
#pragma endregion


#pragma region //Vision
BOOL CGantryMotion::FindVerticalBlob_PreAlign(double *dDiffPosX, double *dDiffPosY)
{
#ifndef SIM_MODE
	wk_MilCameraInfo CameraInfo;
	wk_MilBlobData	BlobData;
	stBlobResult stResult;
	stResult.bResult = FALSE;

	//CameraInfo = Devs::m_CameraPreAlign->GetCameraInfo();
	//CameraInfo.nBlackWhite = CModelData::m_AlignPara.Info.nVerticalPreAlignBlackWhiteType; //1;
	//CameraInfo.nBin = CModelData::m_AlignPara.Info.nVerticalPreAlignThreshold;// 150;
	//Devs::m_CameraPreAlign->SetCameraInfo(CameraInfo);
	//BlobData = Devs::m_CameraPreAlign->GetBlobData();
	//BlobData.dMarkSizeX = CModelData::m_GlassPara.Info.dGlassAlignMarkSizeX; //0.1;
	//BlobData.dMarkSizeY = CModelData::m_GlassPara.Info.dGlassAlignMarkSizeY; //0.1;
	//Devs::m_CameraPreAlign->SetBlobData(BlobData);
	//stResult = Devs::m_CameraPreAlign->FindBlobInspect();
	//BlobData = Devs::m_CameraPreAlign->GetBlobData();
	//*dDiffPosX = BlobData.dPosX;
	//*dDiffPosY = BlobData.dPosY;
#else
	*dDiffPosX = 0.0;
	*dDiffPosY = 0.0;
#endif
#ifndef SIM_MODE
	return stResult.bResult;
#else
return TRUE;
#endif
}
BOOL CGantryMotion::FindVerticalBlob_Review10X(double *dDiffPosX, double *dDiffPosY)
{
#ifndef SIM_MODE
	wk_MilCameraInfo CameraInfo;
	wk_MilBlobData	BlobData;
	stBlobResult stResult;

	CameraInfo = Devs::m_Camera10X->GetCameraInfo();
	CameraInfo.nBlackWhite = CModelData::m_AlignPara.Info.nVerticalMainAlignBlackWhiteType; //1
	CameraInfo.nBin = CModelData::m_AlignPara.Info.nVerticalMainAlignThreshold;// 150;

	Devs::m_Camera10X->SetCameraInfo(CameraInfo);
	BlobData = Devs::m_Camera10X->GetBlobData();
	BlobData.dMarkSizeX = CModelData::m_GlassPara.Info.dGlassAlignMarkSizeX; //0.1;
	BlobData.dMarkSizeY = CModelData::m_GlassPara.Info.dGlassAlignMarkSizeY; //0.1;
	Devs::m_Camera10X->SetBlobData(BlobData);
	stResult = Devs::m_Camera10X->FindBlobInspect();
	BlobData = Devs::m_Camera10X->GetBlobData();
	*dDiffPosX = BlobData.dPosX;
	*dDiffPosY = BlobData.dPosY;
#else
	*dDiffPosX = 0.0;
	*dDiffPosY = 0.0;
#endif
#ifndef SIM_MODE
	return stResult.bResult;
#else
return TRUE;
#endif
}
BOOL CGantryMotion::FindBlob_TagKey4PAlign_Review10X(double *dDiffPosX, double *dDiffPosY)
{
#ifndef SIM_MODE
	wk_MilCameraInfo CameraInfo;
	wk_MilBlobData	BlobData;
	stBlobResult stResult;
	double dResX = 0.0, dResY = 0.0;

	CameraInfo = Devs::m_Camera10X->GetCameraInfo();
	CameraInfo.nBlackWhite = CModelData::m_PpaPara.Info.nPpaBlackWhiteType; //1; 
	CameraInfo.nBin = CModelData::m_PpaPara.Info.nPpaThreshold[CModelData::m_InspectionPara.Info.nMeasureCameraMode]; //100; //KJT 20210824
	Devs::m_Camera10X->SetCameraInfo(CameraInfo);

	BlobData = Devs::m_Camera10X->GetBlobData();
	BlobData.dMarkSizeX = CModelData::m_MaterialPara.Info.dTegkey_SizeX; //0.045; //TagKeyX
	BlobData.dMarkSizeY = CModelData::m_MaterialPara.Info.dTegkey_SizeY; //0.050; //TagKeyY
	Devs::m_Camera10X->SetBlobData(BlobData);
	stResult = Devs::m_Camera10X->FindBlobInspect();
	//Devs::m_Camera10X->FindBlobTagKey();
	BlobData = Devs::m_Camera10X->GetBlobData();
	*dDiffPosX = BlobData.dPosX;
	*dDiffPosY = BlobData.dPosY;
#else
	*dDiffPosX = 0.0;
	*dDiffPosY = 0.0;
#endif
#ifndef SIM_MODE
	return stResult.bResult;
#else
return TRUE;
#endif
}
BOOL CGantryMotion::FindBlob_SwAlign_Review10X(double *dDiffPosX, double *dDiffPosY) //KJT 20210308
{
#ifndef SIM_MODE
	wk_MilCameraInfo CameraInfo;
	wk_MilBlobData	BlobData;
	stBlobResult stResult;

	CameraInfo = Devs::m_Camera10X->GetCameraInfo();
	CameraInfo.nBlackWhite = CModelData::m_AlignPara.Info.nSwAlignBlackWhiteType; //1;
	CameraInfo.nBin = CModelData::m_AlignPara.Info.nSwAlignThreshold; //100;

	Devs::m_Camera10X->SetCameraInfo(CameraInfo);

	BlobData = Devs::m_Camera10X->GetBlobData();
	BlobData.dMarkSizeX = CModelData::m_MaterialPara.Info.dSlotSizeX[0][0];
	BlobData.dMarkSizeY = CModelData::m_MaterialPara.Info.dSlotSizeY[0][0];
	Devs::m_Camera10X->SetBlobData(BlobData);
	stResult = Devs::m_Camera10X->FindBlobInspect();
	BlobData = Devs::m_Camera10X->GetBlobData();
	*dDiffPosX = BlobData.dPosX;
	*dDiffPosY = BlobData.dPosY;
#else
	*dDiffPosX = 0.0;
	*dDiffPosY = 0.0;
#endif
#ifndef SIM_MODE
	return stResult.bResult;
#else
return TRUE;
#endif
}
BOOL CGantryMotion::FindBlob_Edge4PAlign_Review10X(double *dDiffPosX, double *dDiffPosY)
{
#ifndef SIM_MODE
	wk_MilCameraInfo CameraInfo;
	wk_MilBlobData	BlobData;
	stBlobResult stResult;

	CameraInfo = Devs::m_Camera10X->GetCameraInfo();
	CameraInfo.nBlackWhite = CModelData::m_AlignPara.Info.nEdge4PAlignBlackWhiteType; //1;
	CameraInfo.nBin = CModelData::m_AlignPara.Info.nEdge4PAlignThreshold; //100;
	Devs::m_Camera10X->SetCameraInfo(CameraInfo);

	BlobData = Devs::m_Camera10X->GetBlobData();
	BlobData.dMarkSizeX = CModelData::m_MaterialPara.Info.dSlotSizeX[0][0];
	BlobData.dMarkSizeY = CModelData::m_MaterialPara.Info.dSlotSizeY[0][0];
	Devs::m_Camera10X->SetBlobData(BlobData);
	stResult = Devs::m_Camera10X->FindBlobInspect();
	BlobData = Devs::m_Camera10X->GetBlobData();
	*dDiffPosX = BlobData.dPosX;
	*dDiffPosY = BlobData.dPosY;
#else
	*dDiffPosX = 0.0;
	*dDiffPosY = 0.0;
#endif
#ifndef SIM_MODE
	return stResult.bResult;
#else
return TRUE;
#endif

}
BOOL CGantryMotion::FindBlob_FrameMain4PAlign_Review10X(double *dDiffPosX, double *dDiffPosY)
{
#ifndef SIM_MODE
	wk_MilCameraInfo CameraInfo;
	wk_MilBlobData	BlobData;
	stBlobResult stResult;

	CameraInfo = Devs::m_Camera10X->GetCameraInfo();
	CameraInfo.nBlackWhite = CModelData::m_AlignPara.Info.nVerticalMainAlignBlackWhiteType; //1;
	CameraInfo.nBin = CModelData::m_AlignPara.Info.nVerticalMainAlignThreshold; //100;

	Devs::m_Camera10X->SetCameraInfo(CameraInfo);

	BlobData = Devs::m_Camera10X->GetBlobData();
	BlobData.dMarkSizeX = CModelData::m_GlassPara.Info.dGlassAlignMarkSizeX; //0.1;
	BlobData.dMarkSizeY = CModelData::m_GlassPara.Info.dGlassAlignMarkSizeY; //0.1;
	Devs::m_Camera10X->SetBlobData(BlobData);
	stResult = Devs::m_Camera10X->FindBlobInspect();
	BlobData = Devs::m_Camera10X->GetBlobData();
	*dDiffPosX = BlobData.dPosX;
	*dDiffPosY = BlobData.dPosY;
#else
	*dDiffPosX = 0.0;
	*dDiffPosY = 0.0;
#endif
#ifndef SIM_MODE
	return stResult.bResult;
#else
return TRUE;
#endif
}
BOOL CGantryMotion::FindHoleBlob_2P_PreAlign(double *dDiffPosX, double *dDiffPosY, int nAlignPoint)
{
#ifndef SIM_MODE
	wk_MilCameraInfo CameraInfo;
	wk_MilBlobData	BlobData;
	stBlobResult stResult;
	stResult.bResult = FALSE;

	//CameraInfo = Devs::m_CameraPreAlign->GetCameraInfo();
	//CameraInfo.nBlackWhite = CModelData::m_AlignPara.Info.nPreAlignBlackWhiteType; //0
	//if (nAlignPoint == 0)
	//	CameraInfo.nBin = CModelData::m_AlignPara.Info.nPreAlignThreshold_L; //100
	//else
	//	CameraInfo.nBin = CModelData::m_AlignPara.Info.nPreAlignThreshold_R; //100

	//Devs::m_CameraPreAlign->SetCameraInfo(CameraInfo);
	//BlobData = Devs::m_CameraPreAlign->GetBlobData();
	//BlobData.dMarkSizeX = CModelData::m_MaterialPara.Info.dAlignHoleSizeX; //0.08; //Inner Hole
	//BlobData.dMarkSizeY = CModelData::m_MaterialPara.Info.dAlignHoleSizeY; //0.08; //Inner Hole
	//Devs::m_CameraPreAlign->SetBlobData(BlobData);
	//stResult = Devs::m_CameraPreAlign->FindBlobInspect();
	//BlobData = Devs::m_CameraPreAlign->GetBlobData();
	//*dDiffPosX = BlobData.dPosX;
	//*dDiffPosY = BlobData.dPosY;
#else
	*dDiffPosX = 0.0;
	*dDiffPosY = 0.0;
#endif
#ifndef SIM_MODE
	return stResult.bResult;
#else
return TRUE;
#endif
}
BOOL CGantryMotion::FindHoleBlob_2P_Review10X(double *dDiffPosX, double *dDiffPosY)
{
#ifndef SIM_MODE
	wk_MilCameraInfo CameraInfo;
	wk_MilBlobData	BlobData;
	stBlobResult stResult;

	CameraInfo = Devs::m_Camera10X->GetCameraInfo();
	CameraInfo.nBlackWhite = CModelData::m_AlignPara.Info.nMain2PAlignBlackWhiteType; //0
	CameraInfo.nBin = CModelData::m_AlignPara.Info.nMain2PAlignThreshold; //Inner Hole : 100

	Devs::m_Camera10X->SetCameraInfo(CameraInfo);
	BlobData = Devs::m_Camera10X->GetBlobData();
	BlobData.dMarkSizeX = CModelData::m_MaterialPara.Info.dAlignHoleSizeX; //0.08; //Inner Hole : 0.08
	BlobData.dMarkSizeY = CModelData::m_MaterialPara.Info.dAlignHoleSizeY; //0.08; //Inner Hole : 0.08
	Devs::m_Camera10X->SetBlobData(BlobData);
	stResult = Devs::m_Camera10X->FindBlobInspect();
	BlobData = Devs::m_Camera10X->GetBlobData();
	*dDiffPosX = BlobData.dPosX;
	*dDiffPosY = BlobData.dPosY;
#else
	*dDiffPosX = 0.0;
	*dDiffPosY = 0.0;
#endif
#ifndef SIM_MODE
	return stResult.bResult;
#else
return TRUE;
#endif
}

BOOL CGantryMotion::FindBlob_Tegkey_Review10X(double *dDiffPosX, double *dDiffPosY) //KJT 20210225
{
#ifndef SIM_MODE
	wk_MilCameraInfo CameraInfo;
	wk_MilBlobData	BlobData;
	stBlobResult stResult;

	CameraInfo = Devs::m_Camera10X->GetCameraInfo();
	CameraInfo.nBlackWhite = CModelData::m_AlignPara.Info.nTegkeyAlignBlackWhiteType; //1
	CameraInfo.nBin = CModelData::m_AlignPara.Info.nTegkeyAlignThreshold;

	Devs::m_Camera10X->SetCameraInfo(CameraInfo);
	BlobData = Devs::m_Camera10X->GetBlobData();
	BlobData.dMarkSizeX = CModelData::m_MaterialPara.Info.dTegkey_SizeX; //0.045;
	BlobData.dMarkSizeY = CModelData::m_MaterialPara.Info.dTegkey_SizeY; //0.05;
	Devs::m_Camera10X->SetBlobData(BlobData);
	stResult = Devs::m_Camera10X->FindBlobInspect();
	BlobData = Devs::m_Camera10X->GetBlobData();
	*dDiffPosX = BlobData.dPosX;
	*dDiffPosY = BlobData.dPosY;
#else
	*dDiffPosX = 0.0;
	*dDiffPosY = 0.0;
#endif
#ifndef SIM_MODE
	return stResult.bResult;
#else
return TRUE;
#endif
}

BOOL CGantryMotion::FindBlob_TP(double *dDiffPosX, double *dDiffPosY, int nCamNo) //KJT 20210329 //KJT 20210824
{
#ifndef SIM_MODE
	wk_MilCameraInfo CameraInfo;
	wk_MilBlobData	BlobData;
	stBlobResult stResult;

	//if (CModelData::m_InspectionPara.Info.nMeasureCameraMode == eViewReview20X)
	//{
	//	CameraInfo = Devs::m_Camera20X->GetCameraInfo();
	//	CameraInfo.nBlackWhite = CModelData::m_AlignPara.Info.nTPBlackWhiteType; //Black
	//	CameraInfo.nBin = CModelData::m_AlignPara.Info.nTPThreshold; // 40;
	//	Devs::m_Camera20X->SetCameraInfo(CameraInfo);
	//	BlobData = Devs::m_Camera20X->GetBlobData();
	//	BlobData.dMarkSizeX = CModelData::m_AtMaterialPara.Info.dTPSizeX; //0.035;
	//	BlobData.dMarkSizeY = CModelData::m_AtMaterialPara.Info.dTPSizeY; //0.035;
	//	Devs::m_Camera20X->SetBlobData(BlobData);
	//	stResult = Devs::m_Camera20X->FindBlobInspect();
	//	BlobData = Devs::m_Camera20X->GetBlobData();
	//	*dDiffPosX = BlobData.dPosX;
	//	*dDiffPosY = BlobData.dPosY;
	//}
	//else
	{
		CameraInfo = Devs::m_Camera10X->GetCameraInfo();
		CameraInfo.nBlackWhite = CModelData::m_AlignPara.Info.nTPBlackWhiteType; //Black
		CameraInfo.nBin = CModelData::m_AlignPara.Info.nTPThreshold[nCamNo]; // 40; //KJT 20210824

		Devs::m_Camera10X->SetCameraInfo(CameraInfo);
		BlobData = Devs::m_Camera10X->GetBlobData();
		BlobData.dMarkSizeX = CModelData::m_AtMaterialPara.Info.dTPSizeX; //0.035;
		BlobData.dMarkSizeY = CModelData::m_AtMaterialPara.Info.dTPSizeY; //0.035;
		Devs::m_Camera10X->SetBlobData(BlobData);
		stResult = Devs::m_Camera10X->FindBlobInspect();
		BlobData = Devs::m_Camera10X->GetBlobData();
		*dDiffPosX = BlobData.dPosX;
		*dDiffPosY = BlobData.dPosY;
	}
#else
	*dDiffPosX = 0.0;
	*dDiffPosY = 0.0;
#endif
#ifndef SIM_MODE
	return stResult.bResult;
#else
return TRUE;
#endif
}

BOOL CGantryMotion::FindPattern_TP(double *dDiffPosX, double *dDiffPosY, int nCamNo) //KJT 20210824
{
#ifndef SIM_MODE
	wk_MilCameraInfo CameraInfo;
	wk_MilPatFindData	PateData;

	//if (CModelData::m_InspectionPara.Info.nMeasureCameraMode == eViewReview20X)
	//{
	//	CameraInfo = Devs::m_Camera20X->GetCameraInfo();
	//	CameraInfo.nBlackWhite = CModelData::m_AlignPara.Info.nTPBlackWhiteType; //Black
	//	CameraInfo.nBin = CModelData::m_AlignPara.Info.nTPThreshold; // 40;
	//	Devs::m_Camera20X->SetCameraInfo(CameraInfo);
	//	PateData = Devs::m_Camera20X->GetPatFindData();
	//	Devs::m_Camera20X->SetPatFindData(PateData);
	//	Devs::m_Camera20X->OnInspPattern();
	//	PateData = Devs::m_Camera20X->GetPatFindData();
	//	*dDiffPosX = PateData.dPosX;
	//	*dDiffPosY = PateData.dPosY;
	//}
	//else
	{
		CameraInfo = Devs::m_Camera10X->GetCameraInfo();
		CameraInfo.nBlackWhite = CModelData::m_AlignPara.Info.nTPBlackWhiteType; //Black
		CameraInfo.nBin = CModelData::m_AlignPara.Info.nTPThreshold[nCamNo]; // 40; //KJT 20210824

		Devs::m_Camera10X->SetCameraInfo(CameraInfo);
		PateData = Devs::m_Camera10X->GetPatFindData();
		Devs::m_Camera10X->SetPatFindData(PateData);
		Devs::m_Camera10X->OnInspPattern();
		PateData = Devs::m_Camera10X->GetPatFindData();
		*dDiffPosX = PateData.dPosX;
		*dDiffPosY = PateData.dPosY;
	}
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

BOOL CGantryMotion::FindBlob_PPA_Review10X(double *dDiffPosX, double *dDiffPosY)
{
#ifndef SIM_MODE
	wk_MilCameraInfo CameraInfo;
	wk_MilBlobData	BlobData;
	stBlobResult stResult;

	CameraInfo = Devs::m_Camera10X->GetCameraInfo();
	CameraInfo.nBlackWhite = CModelData::m_PpaPara.Info.nPpaBlackWhiteType;
	CameraInfo.nBin = CModelData::m_PpaPara.Info.nPpaThreshold[CModelData::m_InspectionPara.Info.nMeasureCameraMode]; //KJT 20210824

	Devs::m_Camera10X->SetCameraInfo(CameraInfo);

	BlobData = Devs::m_Camera10X->GetBlobData();
	BlobData.nQuantityX = CModelData::m_PpaPara.Info.nDivX + 1; //KJT 20210726
	BlobData.nQuantityY = CModelData::m_PpaPara.Info.nDivY + 1;
	BlobData.dPitchX = CModelData::m_MaterialPara.Info.dSlotPitchX[0][0];
	BlobData.dPitchY = CModelData::m_MaterialPara.Info.dSlotPitchY[0][0];
	BlobData.dMarkSizeX = CModelData::m_MaterialPara.Info.dSlotSizeX[0][0];
	BlobData.dMarkSizeY = CModelData::m_MaterialPara.Info.dSlotSizeY[0][0];
	Devs::m_Camera10X->SetBlobData(BlobData);

	stResult = Devs::m_Camera10X->FindBlobPpa();
	
	*dDiffPosX = stResult.dPosX;
	*dDiffPosY = stResult.dPosY;
#else
	*dDiffPosX = 0.0;
	*dDiffPosY = 0.0;
#endif
#ifndef SIM_MODE
	return stResult.bResult;
#else
return TRUE;
#endif
}

BOOL CGantryMotion::RepeatFindCircle(int CamNo, double dRadius, double *dDiffX, double *dDiffY, double *dScore) //KJT 20210727
{
	CString Str = _T("");

#ifndef SIM_MODE
	stModCirclePara ModCirclePara;
	wk_MilModelFindData m_ModelFindData;
	stModResult ModResult;

	ModCirclePara.dRadius = dRadius;
	//if (CamNo == eViewPreAlign)
	//{
	//	ModResult = Devs::m_CameraPreAlign->FindModCircleFind(ModCirclePara);
	//	Sleep(200);
	//	m_ModelFindData = Devs::m_CameraPreAlign->GetModelFindData();

	//	Str.Format(_T("PreAlign "));
	//}
	//else //eViewReview10X, eViewReview20X
	{
		ModResult = Devs::m_Camera10X->FindModCircleFind(ModCirclePara);
		Sleep(200);
		m_ModelFindData = Devs::m_Camera10X->GetModelFindData();

	}

	*dDiffX = m_ModelFindData.dPosX;
	*dDiffY = m_ModelFindData.dPosY;
	*dScore = m_ModelFindData.dScore;
#else
	*dDiffX = 0.0;
	*dDiffY = 0.0;
	*dScore = 0.0;
#endif

	Str.AppendFormat(_T("RepeatFindCircle Result X:%.5f, Y:%.5f, Score:%.5f"), *dDiffX, *dDiffY, *dScore);
	Total_Msg(Str);
#ifndef SIM_MODE
	return ModResult.bResult;
#else
return TRUE;
#endif
}
BOOL CGantryMotion::RepeatFindBlob(int nCamNo, int nBlackWhite, int nBin, double dSizeX, double dSizeY, double *dDiffX, double *dDiffY) //KJT 20210727
{
	CString Str = _T("");

#ifndef SIM_MODE
	wk_MilCameraInfo CameraInfo;
	wk_MilBlobData	BlobData;
	stBlobResult stResult;
	double dResX = 0.0, dResY = 0.0;

	//if (nCamNo == eViewPreAlign)
	//{
	//	CameraInfo = Devs::m_CameraPreAlign->GetCameraInfo();
	//	CameraInfo.nBlackWhite = nBlackWhite; //1
	//	CameraInfo.nBin = nBin; // 100;
	//	Devs::m_CameraPreAlign->SetCameraInfo(CameraInfo);

	//	BlobData = Devs::m_CameraPreAlign->GetBlobData();
	//	BlobData.dMarkSizeX = dSizeX; // CModelData::m_MaterialPara.Info.dTegkey_SizeX; // 0.045; //TagKeyX
	//	BlobData.dMarkSizeY = dSizeY; // CModelData::m_MaterialPara.Info.dTegkey_SizeY; //0.050; //TagKeyY
	//	Devs::m_CameraPreAlign->SetBlobData(BlobData);
	//	stResult = Devs::m_CameraPreAlign->FindBlobInspect();
	//	//Devs::m_CameraPreAlign->FindBlobTagKey();
	//	BlobData = Devs::m_CameraPreAlign->GetBlobData();

	//	Str.Format(_T("PreAlign "));
	//}
	//else //eViewReview10X, eViewReview20X
	{
		CameraInfo = Devs::m_Camera10X->GetCameraInfo();
		CameraInfo.nBlackWhite = nBlackWhite; //1
		CameraInfo.nBin = nBin; // 100;

		Devs::m_Camera10X->SetCameraInfo(CameraInfo);

		BlobData = Devs::m_Camera10X->GetBlobData();
		BlobData.dMarkSizeX = dSizeX; // 0.045; //TagKeyX
		BlobData.dMarkSizeY = dSizeY; //0.050; //TagKeyY
		Devs::m_Camera10X->SetBlobData(BlobData);
		stResult = Devs::m_Camera10X->FindBlobInspect();
		//Devs::m_Camera10X->FindBlobTagKey();
		BlobData = Devs::m_Camera10X->GetBlobData();

	}

	*dDiffX = BlobData.dPosX;
	*dDiffY = BlobData.dPosY;
#else
	*dDiffX = 0.0;
	*dDiffY = 0.0;
#endif

	Str.AppendFormat(_T("RepeatFindBlob Result X:%.5f, Y:%.5f"), *dDiffX, *dDiffY);
	Total_Msg(Str);
#ifndef SIM_MODE
	return stResult.bResult;
#else
return TRUE;
#endif
}
#pragma endregion
BOOL CGantryMotion::FindCircleCentering(int nCamNo, double dRadius) //KJT 20210727
{
#ifndef SIM_MODE
	CString Str = _T("");
	double dDiffX = 0.0;
	double dDiffY = 0.0;
	double dScore = 0.0;
	double dPosX = 0.0, dPosY = 0.0;

	stModCirclePara ModCirclePara;
	wk_MilModelFindData m_ModelFindData;
	stModResult ModResult;

	ModCirclePara.dRadius = dRadius;//?? 
	//ModCirclePara.dRadius = dRadius / 2;//??

	//if (nCamNo == eViewPreAlign)
	//{
	//	ModResult = Devs::m_CameraPreAlign->FindModCircleFind(ModCirclePara);
	//	Sleep(200);
	//	m_ModelFindData = Devs::m_CameraPreAlign->GetModelFindData();
	//}
	//else //eViewReview10X, eViewReview20X
	{
		ModResult = Devs::m_Camera10X->FindModCircleFind(ModCirclePara);
		Sleep(200);
		m_ModelFindData = Devs::m_Camera10X->GetModelFindData();
	}

	dDiffX = m_ModelFindData.dPosX;
	dDiffY = m_ModelFindData.dPosY;
	dScore = m_ModelFindData.dScore;
	dPosX = 0.0, dPosY = 0.0;

	Str.Format(_T("Find Circle Result X:%.5f, Y:%.5f, Score:%.5f"), dDiffX, dDiffY, dScore);
	Total_Msg(Str);

	if (fabs(dDiffX) > 0.001 && dDiffX < 0.5)
	{
		dPosX = SharedInfo::GetCmdPos(AXIS_GANTRY_X);
		dPosX += m_ModelFindData.dPosX;

		Devs::m_GantryMotion.Move_Gantry_X_Pos(dPosX, FALSE);
		Sleep(20);
	}
	
	if (fabs(dDiffY) > 0.001 && dDiffY < 0.5)
	{
		dPosY = SharedInfo::GetActPos(AXIS_GANTRY_Y1);
		dPosY += m_ModelFindData.dPosY;
		
		Devs::m_GantryMotion.Move_Gantry_Y_Pos(dPosY);
		Sleep(20);
	}
#endif
#ifndef SIM_MODE
	return ModResult.bResult;
#else
	return TRUE;
#endif
}

BOOL CGantryMotion::FindBlobCentering(int nCamNo, int nBlackWhite, int nBin, double dSizeX, double dSizeY)
{
	CString Str = _T("");
	double dDiffX = 0.0;
	double dDiffY = 0.0;
	double dScore = 0.0;
	double dPosX = 0.0, dPosY = 0.0;

#ifndef SIM_MODE
	wk_MilCameraInfo CameraInfo;
	wk_MilBlobData	BlobData;
	stBlobResult stResult;

	if (nCamNo == eCamView_6G)
	{
		CameraInfo = Devs::m_Camera6G_LT->GetCameraInfo();
		CameraInfo.nBlackWhite = nBlackWhite; //1
		CameraInfo.nBin = nBin; // 100;

		Devs::m_Camera6G_LT->SetCameraInfo(CameraInfo);

		BlobData = Devs::m_Camera6G_LT->GetBlobData();
		BlobData.dMarkSizeX = dSizeX; // 0.045; //TagKeyX
		BlobData.dMarkSizeY = dSizeY; //0.050; //TagKeyY
		Devs::m_Camera6G_LT->SetBlobData(BlobData);
		stResult = Devs::m_Camera6G_LT->FindBlobInspect();
		BlobData = Devs::m_Camera6G_LT->GetBlobData();

		Str.Format(_T("6G "));
	}

	dDiffX = BlobData.dPosX;
	dDiffY = BlobData.dPosY;
#else
	dDiffX = 0.0;
	dDiffY = 0.0;
#endif
#ifndef SIM_MODE
	Str.AppendFormat(_T("Find Blob Result X:%.5f, Y:%.5f"), dDiffX, dDiffY);
	Total_Msg(Str);

	if (stResult.bResult == TRUE)
	{
		if (fabs(dDiffX) > 0.001 && dDiffX < 0.5)
		{
			dPosX = SharedInfo::GetCmdPos(AXIS_GANTRY_X);
			dPosX += dDiffX;

			Devs::m_GantryMotion.Move_Gantry_X_Pos(dPosX, FALSE);
			Sleep(20);
		}

		if (fabs(dDiffY) > 0.001 && dDiffY < 0.5)
		{
			dPosY = SharedInfo::GetActPos(AXIS_GANTRY_Y1);
			dPosY += dDiffY;

			Devs::m_GantryMotion.Move_Gantry_Y_Pos(dPosY);
			Sleep(20);
		}
	}

	return stResult.bResult;
#else
return TRUE;
#endif
}


BOOL CGantryMotion::CameraSwap_Review10XCamToPreAlignCam()
{
	double dSrcPosX = 0.0, dSrcPosY = 0.0, dTargetPosX = 0.0, dTargetPosY = 0.0;
	double dPosZ[3] = { 0.0, 0.0, 0.0 };	

	dSrcPosX = SharedInfo::GetCmdPos(AXIS_GANTRY_X);
	dSrcPosY = SharedInfo::GetCmdPos(AXIS_GANTRY_Y1);
	dTargetPosX = dSrcPosX - CSystemData::m_Coordinate.Info.dOffsetReview10xToPreAlign_X;
	dTargetPosY = dSrcPosY - CSystemData::m_Coordinate.Info.dOffsetReview10xToPreAlign_Y;

	dPosZ[0] = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Wait_Pos;
	dPosZ[1] = CManualData::m_ManualDataGantry.Info.m_dGantry_Z2_Wait_Pos; //!!
	dPosZ[2] = CManualData::m_ManualDataGantry.Info.m_dGantry_Z3_Wait_Pos; //!!

	Move_GantryXYZ(dTargetPosX, dTargetPosY, dPosZ, TRUE);

	return TRUE;
}
BOOL CGantryMotion::CameraSwap_PreAlignCamToReview10XCam()
{
	double dSrcPosX = 0.0, dSrcPosY = 0.0, dTargetPosX = 0.0, dTargetPosY = 0.0;
	double dPosZ[3] = { 0.0, 0.0, 0.0 };

	dSrcPosX = SharedInfo::GetCmdPos(AXIS_GANTRY_X);
	dSrcPosY = SharedInfo::GetActPos(AXIS_GANTRY_Y1);
	dTargetPosX = dSrcPosX + CSystemData::m_Coordinate.Info.dOffsetReview10xToPreAlign_X;
	dTargetPosY = dSrcPosY + CSystemData::m_Coordinate.Info.dOffsetReview10xToPreAlign_Y;

	dPosZ[0] = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Wait_Pos;
	dPosZ[1] = CManualData::m_ManualDataGantry.Info.m_dGantry_Z2_Wait_Pos; //!!
	dPosZ[2] = CManualData::m_ManualDataGantry.Info.m_dGantry_Z3_Wait_Pos; //!!

	Move_GantryXYZ(dTargetPosX, dTargetPosY, dPosZ, TRUE);

	return TRUE;
}
BOOL CGantryMotion::CameraSwap_Review10XCamToAOI()
{
	double dSrcPosX = 0.0, dSrcPosY = 0.0, dTargetPosX = 0.0, dTargetPosY = 0.0;
	double dPosZ[3] = { 0.0, 0.0, 0.0 };

	dSrcPosX = SharedInfo::GetCmdPos(AXIS_GANTRY_X);
	dSrcPosY = SharedInfo::GetActPos(AXIS_GANTRY_Y1);
	dTargetPosX = dSrcPosX - CSystemData::m_Coordinate.Info.dOffsetReview10xToAoi_X;
	dTargetPosY = dSrcPosY - CSystemData::m_Coordinate.Info.dOffsetReview10xToAoi_Y;

	dPosZ[0] = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Wait_Pos;
	dPosZ[1] = CManualData::m_ManualDataGantry.Info.m_dGantry_Z2_Wait_Pos; //!!
	dPosZ[2] = CManualData::m_ManualDataGantry.Info.m_dGantry_Z3_Wait_Pos; //!!

	Move_GantryXYZ(dTargetPosX, dTargetPosY, dPosZ, TRUE);

	return TRUE;
}
BOOL CGantryMotion::CameraSwap_AOIToReview10XCam()
{
	double dSrcPosX = 0.0, dSrcPosY = 0.0, dTargetPosX = 0.0, dTargetPosY = 0.0;
	double dPosZ[3] = { 0.0, 0.0, 0.0 };

	dSrcPosX = SharedInfo::GetCmdPos(AXIS_GANTRY_X);
	dSrcPosY = SharedInfo::GetActPos(AXIS_GANTRY_Y1);
	dTargetPosX = dSrcPosX + CSystemData::m_Coordinate.Info.dOffsetReview10xToAoi_X;
	dTargetPosY = dSrcPosY + CSystemData::m_Coordinate.Info.dOffsetReview10xToAoi_Y;

	dPosZ[0] = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Wait_Pos;
	dPosZ[1] = CManualData::m_ManualDataGantry.Info.m_dGantry_Z2_Wait_Pos; //!!
	dPosZ[2] = CManualData::m_ManualDataGantry.Info.m_dGantry_Z3_Wait_Pos; //!!

	Move_GantryXYZ(dTargetPosX, dTargetPosY, dPosZ, TRUE);

	return TRUE;
}
BOOL CGantryMotion::CameraSwap_Review10XCamTo3D()
{
	double dSrcPosX = 0.0, dSrcPosY = 0.0, dTargetPosX = 0.0, dTargetPosY = 0.0;
	double dPosZ[3] = { 0.0, 0.0, 0.0 };

	dSrcPosX = SharedInfo::GetCmdPos(AXIS_GANTRY_X);
	dSrcPosY = SharedInfo::GetActPos(AXIS_GANTRY_Y1);
	dTargetPosX = dSrcPosX - CSystemData::m_Coordinate.Info.dOffsetReview10xTo3dCam_X;
	dTargetPosY = dSrcPosY - CSystemData::m_Coordinate.Info.dOffsetReview10xTo3dCam_Y;

	dPosZ[0] = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Wait_Pos;
	dPosZ[1] = CManualData::m_ManualDataGantry.Info.m_dGantry_Z2_Wait_Pos;
	dPosZ[2] = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Inspection_Review_Pos;  //!!

	Move_GantryXYZ(dTargetPosX, dTargetPosY, dPosZ, TRUE);

	return TRUE;
}
BOOL CGantryMotion::CameraSwap_3DToReview10XCam()
{
	double dSrcPosX = 0.0, dSrcPosY = 0.0, dTargetPosX = 0.0, dTargetPosY = 0.0;
	double dPosZ[3] = { 0.0, 0.0, 0.0 };

	dSrcPosX = SharedInfo::GetCmdPos(AXIS_GANTRY_X);
	dSrcPosY = SharedInfo::GetActPos(AXIS_GANTRY_Y1);
	dTargetPosX = dSrcPosX + CSystemData::m_Coordinate.Info.dOffsetReview10xTo3dCam_X;
	dTargetPosY = dSrcPosY + CSystemData::m_Coordinate.Info.dOffsetReview10xTo3dCam_Y;

	dPosZ[0] = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Inspection_AOI_Pos;
	dPosZ[1] = CManualData::m_ManualDataGantry.Info.m_dGantry_Z2_Wait_Pos; //!!
	dPosZ[2] = CManualData::m_ManualDataGantry.Info.m_dGantry_Z3_Wait_Pos; //!!

	Move_GantryXYZ(dTargetPosX, dTargetPosY, dPosZ, TRUE);

	return TRUE;
}

BOOL CGantryMotion::Move_GantryXYZ_AlignHoleLeft_PreAlign()
{
	//21.06.10 sjc m_AtMaterialPara -> m_MaterialPara
	double dPosX = CModelData::m_MaterialPara.Info.dAlignLeftHoleX - CSystemData::m_Coordinate.Info.dOffsetReview10xToPreAlign_X;
	double dPosY = CModelData::m_MaterialPara.Info.dAlignLeftHoleY - CSystemData::m_Coordinate.Info.dOffsetReview10xToPreAlign_Y;

	double dPosZ[3] = { 0.0, 0.0, 0.0 };
	dPosZ[0] = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Wait_Pos;
	dPosZ[1] = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_PreAlign_Pos; //!!
	dPosZ[2] = CManualData::m_ManualDataGantry.Info.m_dGantry_Z3_Wait_Pos; //!!

	Move_GantryXYZ(dPosX, dPosY, dPosZ, TRUE);

	return TRUE;
}
BOOL CGantryMotion::Move_GantryXYZ_AlignHoleRight_PreAlign()
{
	//21.06.10 sjc m_AtMaterialPara -> m_MaterialPara
	double dPosX = CModelData::m_MaterialPara.Info.dAlignRightHoleX - CSystemData::m_Coordinate.Info.dOffsetReview10xToPreAlign_X;
	double dPosY = CModelData::m_MaterialPara.Info.dAlignRightHoleY - CSystemData::m_Coordinate.Info.dOffsetReview10xToPreAlign_Y;

	double dPosZ[3] = { 0.0, 0.0, 0.0 };
	dPosZ[0] = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Wait_Pos;
	dPosZ[1] = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_PreAlign_Pos; //!!
	dPosZ[2] = CManualData::m_ManualDataGantry.Info.m_dGantry_Z3_Wait_Pos; //!!

	Move_GantryXYZ(dPosX, dPosY, dPosZ, TRUE);

	return TRUE;
}
BOOL CGantryMotion::Move_GantryXYZ_AlignHoleLeft_Review10X()
{
	//21.06.10 sjc m_AtMaterialPara -> m_MaterialPara
	double dPosX = CModelData::m_MaterialPara.Info.dAlignLeftHoleX;
	double dPosY = CModelData::m_MaterialPara.Info.dAlignLeftHoleY;

	double dPosZ[3] = { 0.0, 0.0, 0.0 };
	dPosZ[0] = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Wait_Pos;
	dPosZ[1] = CManualData::m_ManualDataGantry.Info.m_dGantry_Z2_Wait_Pos; //!!
	dPosZ[2] = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Inspection_Review_Pos; //!!

	Move_GantryXYZ(dPosX, dPosY, dPosZ, TRUE);

	return TRUE;
}
BOOL CGantryMotion::Move_GantryXYZ_AlignHoleRight_Review10X()
{	//21.06.10 sjc m_AtMaterialPara -> m_MaterialPara
	double dPosX = CModelData::m_MaterialPara.Info.dAlignRightHoleX;
	double dPosY = CModelData::m_MaterialPara.Info.dAlignRightHoleY;

	double dPosZ[3] = { 0.0, 0.0, 0.0 };
	dPosZ[0] = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Wait_Pos;
	dPosZ[1] = CManualData::m_ManualDataGantry.Info.m_dGantry_Z2_Wait_Pos; //!!
	dPosZ[2] = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Inspection_Review_Pos; //!!

	Move_GantryXYZ(dPosX, dPosY, dPosZ, TRUE);

	return TRUE;
}

BOOL CGantryMotion::Move_GantryXYZ(double dPosX, double dPosY, double dPosZ[3], BOOL bZUp, int nBackLightVal/* = 0*/, BOOL bApplySwAlignData/* = FALSE*/, BOOL bApplyGlassMappingData/* = FALSE*/) //KJT 20210425
{
	m_dTargetPos_X = dPosX;
	m_dTargetPos_Y = dPosY;

	m_dTargetPos_Z1 = dPosZ[0];
	//m_dTargetPos_Z2 = dPosZ[1];
	//m_dTargetPos_Z3 = dPosZ[2];

	m_bZUp = bZUp;

	m_bApplySwAlignData = bApplySwAlignData; //KJT 20210312
	m_bApplyGlassMappingData = bApplyGlassMappingData;

	m_bMotionDone = FALSE; //!!
	SharedInfo::bMachineStopFlag = FALSE; //!!
	SetStep(eGANTRY_XYZ_MOVE_START, _T("eGANTRY_XYZ_MOVE_START"));

	return TRUE;
}

#pragma region //PPA
BOOL CGantryMotion::MakeNormalPpaPosition(INT nDivX, INT nDivY)
{
	CString Str = _T("");
	INT nTotalSlotCntX, nTotalSlotCntY = 0;
	DOUBLE dPPAPosX, dPPAPosY = 0.;

	//PPA Position Data Reset
	ResetPpaData();

	m_nMaxCellCntX = (INT)CModelData::m_MaterialPara.Info.nCellCountX;
	m_nMaxCellCntY = (INT)CModelData::m_MaterialPara.Info.nCellCountY;
	m_nMaxPatCntX = nDivX;
	m_nMaxPatCntY = nDivY;
	m_nMaxPpaCnt = 0;

	for (INT nCellCntY = 0; nCellCntY < m_nMaxCellCntY; nCellCntY++)
	{
		for (INT nCellCntX = 0; nCellCntX < m_nMaxCellCntX; nCellCntX++)
		{
			//KJT 20210328 !!!
			nTotalSlotCntX = (int)(float)(CModelData::m_AtMaterialPara.Info.dSlotTotalPitchX[nCellCntX][nCellCntY] / CModelData::m_AtMaterialPara.Info.dSlotPitchX[nCellCntX][nCellCntY] + 1);
			nTotalSlotCntY = (int)(float)(CModelData::m_AtMaterialPara.Info.dSlotTotalPitchY[nCellCntX][nCellCntY] / CModelData::m_AtMaterialPara.Info.dSlotPitchY[nCellCntX][nCellCntY] + 1);

			for (int j = 0; j < (int)m_nMaxPatCntY; j++)
			{
				for (int i = 0; i < (int)m_nMaxPatCntX; i++)
				{
					////PosY
					dPPAPosY = CModelData::m_MaterialPara.Info.dCellLeftTopY[nCellCntX][nCellCntY];
					dPPAPosY += CModelData::m_MaterialPara.Info.dSlotCenterShiftY[nCellCntX][nCellCntY];
					if (m_nMaxPatCntY > 1)
						dPPAPosY -= CModelData::m_MaterialPara.Info.dSlotTotalPitchY[nCellCntX][nCellCntY] / (m_nMaxPatCntY - 1) * j;
					else
						dPPAPosY -= CModelData::m_MaterialPara.Info.dSlotTotalPitchY[nCellCntX][nCellCntY] / 2;

					if (m_nMaxPatCntY > 1)
					{
						if (nTotalSlotCntY % 2 == 0 && j % 2 == 1 && (m_nMaxPatCntY == 1 || m_nMaxPatCntY == 3))
						{
							dPPAPosY -= CModelData::m_MaterialPara.Info.dSlotPitchY[nCellCntX][nCellCntY] / 2;
						}
						else if (nTotalSlotCntY % 2 == 0 && m_nMaxPatCntY == 4) //KJT 20210526
						{
							if (j == 1)
								dPPAPosY += CModelData::m_MaterialPara.Info.dSlotPitchY[nCellCntX][nCellCntY] / (m_nMaxPatCntY - 1);
							else if (j == 2)
								dPPAPosY -= CModelData::m_MaterialPara.Info.dSlotPitchY[nCellCntX][nCellCntY] / (m_nMaxPatCntY - 1);
						}
						else if (nTotalSlotCntY % 2 == 0 && m_nMaxPatCntY == 5) //KJT 20210526
						{
							if (j == 1)
								dPPAPosY += CModelData::m_MaterialPara.Info.dSlotPitchY[nCellCntX][nCellCntY] / (m_nMaxPatCntY - 1);
							else if (j == 2)
								dPPAPosY -= CModelData::m_MaterialPara.Info.dSlotPitchY[nCellCntX][nCellCntY] / 2;
							else if (j == 3)
								dPPAPosY -= CModelData::m_MaterialPara.Info.dSlotPitchY[nCellCntX][nCellCntY] / (m_nMaxPatCntY - 1);
						}
					}
					else if (m_nMaxPatCntY == 1)
					{
						if (nTotalSlotCntY % 2 == 0)
						{
							dPPAPosY -= CModelData::m_MaterialPara.Info.dSlotPitchY[nCellCntX][nCellCntY] / 2;
						}
					}
					dPPAPosY *= STICK_FLIP_XY;

					////PosX
					dPPAPosX = CModelData::m_MaterialPara.Info.dCellLeftTopX[nCellCntX][nCellCntY];
					dPPAPosX += CModelData::m_MaterialPara.Info.dSlotCenterShiftX[nCellCntX][nCellCntY];

					if (m_nMaxPatCntX > 1)
						dPPAPosX += CModelData::m_MaterialPara.Info.dSlotTotalPitchX[nCellCntX][nCellCntY] / (m_nMaxPatCntX - 1) * i;
					else
						dPPAPosX += CModelData::m_MaterialPara.Info.dSlotTotalPitchX[nCellCntX][nCellCntY] / 2;

					if (m_nMaxPatCntX > 1)
					{
						if (nTotalSlotCntX % 2 == 0 && i % 2 == 1 && (m_nMaxPatCntX == 1 || m_nMaxPatCntX == 3))
						{
							dPPAPosX -= CModelData::m_MaterialPara.Info.dSlotPitchX[nCellCntX][nCellCntY] / 2;
						}
						else if (nTotalSlotCntX % 2 == 0 && m_nMaxPatCntX == 4) //KJT 20210526
						{
							if (i == 1)
								dPPAPosX += CModelData::m_MaterialPara.Info.dSlotPitchX[nCellCntX][nCellCntY] / (m_nMaxPatCntX - 1);
							else if (i == 2)
								dPPAPosX -= CModelData::m_MaterialPara.Info.dSlotPitchX[nCellCntX][nCellCntY] / (m_nMaxPatCntX - 1);
						}
						else if (nTotalSlotCntX % 2 == 0 && m_nMaxPatCntX == 5) //KJT 20210526
						{
							if (i == 1)
								dPPAPosX += CModelData::m_MaterialPara.Info.dSlotPitchX[nCellCntX][nCellCntY] / (m_nMaxPatCntX - 1);
							else if (i == 2)
								dPPAPosX -= CModelData::m_MaterialPara.Info.dSlotPitchX[nCellCntX][nCellCntY] / 2;
							else if (i == 3)
								dPPAPosX -= CModelData::m_MaterialPara.Info.dSlotPitchX[nCellCntX][nCellCntY] / (m_nMaxPatCntX - 1);
						}
					}
					else if (m_nMaxPatCntX == 1)
					{
						if (nTotalSlotCntX % 2 == 0)
						{
							dPPAPosX -= CModelData::m_MaterialPara.Info.dSlotPitchX[nCellCntX][nCellCntY] / 2;
						}
					}
					dPPAPosX *= STICK_FLIP_XY;

					PPAPos[nCellCntX][nCellCntY][i][j].dPosX = dPPAPosX;
					PPAPos[nCellCntX][nCellCntY][i][j].dPosY = dPPAPosY;
					PPAPos[nCellCntX][nCellCntY][i][j].dCdX = CModelData::m_MaterialPara.Info.dSlotSizeX[nCellCntX][nCellCntY];
					PPAPos[nCellCntX][nCellCntY][i][j].dCdY = CModelData::m_MaterialPara.Info.dSlotSizeY[nCellCntX][nCellCntY];

					m_nMaxPpaCnt++;

					Str.Format(_T("PPA Pos %2d - X:%.5f, Y:%.5f (CD_X:%.5f, CD_Y:%.5f)"),
						m_nMaxPpaCnt,
						Devs::m_GantryMotion.PPAPos[nCellCntX][nCellCntY][i][j].dPosX,
						Devs::m_GantryMotion.PPAPos[nCellCntX][nCellCntY][i][j].dPosY,
						Devs::m_GantryMotion.PPAPos[nCellCntX][nCellCntY][i][j].dCdX,
						Devs::m_GantryMotion.PPAPos[nCellCntX][nCellCntY][i][j].dCdY);
					Total_Msg(Str);
				}
			}
		}
	}

	return TRUE;
}
BOOL CGantryMotion::MakeIndividualNormalPpaPosition(INT nStickIndex, INT nDivX, INT nDivY)
{
	INT nActiveStick = nStickIndex;
	INT nTotalSlotCntX, nTotalSlotCntY = 0;
	DOUBLE dPPAPosX, dPPAPosY = 0.;

	//PPA Position Data Reset
	ResetPpaData();

	m_nMaxCellCntX = (INT)CModelData::m_MaterialPara.Info.nCellCountX;
	m_nMaxCellCntY = (INT)CModelData::m_MaterialPara.Info.nCellCountY;
	m_nMaxPatCntX = nDivX;
	m_nMaxPatCntY = nDivY;
	m_nMaxPpaCnt = 0;

	for (INT nCellCntY = 0; nCellCntY < m_nMaxCellCntY; nCellCntY++)
	{
		for (INT nCellCntX = 0; nCellCntX < m_nMaxCellCntX; nCellCntX++)
		{
			nTotalSlotCntX = (int)(float)(CModelData::m_MaterialPara.Info.dSlotTotalPitchX[nCellCntX][nCellCntY] / CModelData::m_MaterialPara.Info.dSlotPitchX[nCellCntX][nCellCntY] + 1);
			nTotalSlotCntY = (int)(float)(CModelData::m_MaterialPara.Info.dSlotTotalPitchY[nCellCntX][nCellCntY] / CModelData::m_MaterialPara.Info.dSlotPitchY[nCellCntX][nCellCntY] + 1);

			for (int j = 0; j < (int)m_nMaxPatCntY; j++)
			{
				for (int i = 0; i < (int)m_nMaxPatCntX; i++)
				{
					////PosY
					dPPAPosY = CModelData::m_MaterialPara.Info.dCellLeftTopX[nCellCntX][nCellCntY];
					dPPAPosY += CModelData::m_MaterialPara.Info.dSlotCenterShiftX[nCellCntX][nCellCntY];

					if (m_nMaxPatCntY > 1)
						dPPAPosY -= CModelData::m_MaterialPara.Info.dSlotTotalPitchY[nCellCntX][nCellCntY] / (m_nMaxPatCntY - 1) * j;
					else
						dPPAPosY -= CModelData::m_MaterialPara.Info.dSlotTotalPitchY[nCellCntX][nCellCntY] / 2;

					if (m_nMaxPatCntY > 1)
					{
						if (nTotalSlotCntY % 2 == 0 && j % 2 == 1 && (m_nMaxPatCntY == 1 || m_nMaxPatCntY == 3))
						{
							dPPAPosY -= CModelData::m_MaterialPara.Info.dSlotPitchY[nCellCntX][nCellCntY] / 2;
						}
						else if (nTotalSlotCntY % 2 == 0 && m_nMaxPatCntY == 4) //KJT 20210526
						{
							if (j == 1)
								dPPAPosY += CModelData::m_MaterialPara.Info.dSlotPitchY[nCellCntX][nCellCntY] / (m_nMaxPatCntY - 1);
							else if (j == 2)
								dPPAPosY -= CModelData::m_MaterialPara.Info.dSlotPitchY[nCellCntX][nCellCntY] / (m_nMaxPatCntY - 1);
						}
						else if (nTotalSlotCntY % 2 == 0 && m_nMaxPatCntY == 5) //KJT 20210526
						{
							if (j == 1)
								dPPAPosY += CModelData::m_MaterialPara.Info.dSlotPitchY[nCellCntX][nCellCntY] / (m_nMaxPatCntY - 1);
							else if (j == 2)
								dPPAPosY -= CModelData::m_MaterialPara.Info.dSlotPitchY[nCellCntX][nCellCntY] / 2;
							else if (j == 3)
								dPPAPosY -= CModelData::m_MaterialPara.Info.dSlotPitchY[nCellCntX][nCellCntY] / (m_nMaxPatCntY - 1);
						}
					}
					else if (m_nMaxPatCntY == 1)
					{
						if (nTotalSlotCntY % 2 == 0)
						{
							dPPAPosY -= CModelData::m_MaterialPara.Info.dSlotPitchY[nCellCntX][nCellCntY] / 2;
						}
					}
					dPPAPosY *= STICK_FLIP_XY;

					////PosX
					dPPAPosX = CModelData::m_MaterialPara.Info.dCellLeftTopX[nCellCntX][nCellCntY];
					dPPAPosX += CModelData::m_MaterialPara.Info.dSlotCenterShiftX[nCellCntX][nCellCntY];

					if (m_nMaxPatCntX > 1)
						dPPAPosX += CModelData::m_MaterialPara.Info.dSlotTotalPitchX[nCellCntX][nCellCntY] / (m_nMaxPatCntX - 1) * i;
					else
						dPPAPosX += CModelData::m_MaterialPara.Info.dSlotTotalPitchX[nCellCntX][nCellCntY] / 2;

					if (m_nMaxPatCntX > 1)
					{
						if (nTotalSlotCntX % 2 == 0 && i % 2 == 1 && (m_nMaxPatCntX == 1 || m_nMaxPatCntX == 3))
						{
							dPPAPosX -= CModelData::m_MaterialPara.Info.dSlotPitchX[nCellCntX][nCellCntY] / 2;
						}
						else if (nTotalSlotCntX % 2 == 0 && m_nMaxPatCntX == 4) //KJT 20210526
						{
							if (i == 1)
								dPPAPosX += CModelData::m_MaterialPara.Info.dSlotPitchX[nCellCntX][nCellCntY] / (m_nMaxPatCntX - 1);
							else if (i == 2)
								dPPAPosX -= CModelData::m_MaterialPara.Info.dSlotPitchX[nCellCntX][nCellCntY] / (m_nMaxPatCntX - 1);
						}
						else if (nTotalSlotCntX % 2 == 0 && m_nMaxPatCntX == 5) //KJT 20210526
						{
							if (i == 1)
								dPPAPosX += CModelData::m_MaterialPara.Info.dSlotPitchX[nCellCntX][nCellCntY] / (m_nMaxPatCntX - 1);
							else if (i == 2)
								dPPAPosX -= CModelData::m_MaterialPara.Info.dSlotPitchX[nCellCntX][nCellCntY] / 2;
							else if (i == 3)
								dPPAPosX -= CModelData::m_MaterialPara.Info.dSlotPitchX[nCellCntX][nCellCntY] / (m_nMaxPatCntX - 1);
						}
					}
					else if (m_nMaxPatCntX == 1)
					{
						if (nTotalSlotCntX % 2 == 0)
						{
							dPPAPosX -= CModelData::m_MaterialPara.Info.dSlotPitchX[nCellCntX][nCellCntY] / 2;
						}
					}
					dPPAPosX *= STICK_FLIP_XY;

					PPAPos[nCellCntX][nCellCntY][i][j].dPosX = dPPAPosX;
					PPAPos[nCellCntX][nCellCntY][i][j].dPosY = dPPAPosY;
					PPAPos[nCellCntX][nCellCntY][i][j].dCdX = CModelData::m_MaterialPara.Info.dSlotSizeX[nCellCntX][nCellCntY];
					PPAPos[nCellCntX][nCellCntY][i][j].dCdY = CModelData::m_MaterialPara.Info.dSlotSizeY[nCellCntX][nCellCntY];

					m_nMaxPpaCnt++;
				}
			}
		}
	}

	return TRUE;
}
BOOL CGantryMotion::MakeAtPpaPosition(INT nDivX, INT nDivY)
{
	CString Str = _T("");
	INT nTotalSlotCntX, nTotalSlotCntY = 0;
	DOUBLE dPPAPosX, dPPAPosY = 0.;

	//PPA Position Data Reset
	ResetPpaData();

	m_nMaxCellCntX = (INT)CModelData::m_AtMaterialPara.Info.nCellCountX;
	m_nMaxCellCntY = (INT)CModelData::m_AtMaterialPara.Info.nCellCountY;
	m_nMaxPatCntX = nDivX;
	m_nMaxPatCntY = nDivY;
	m_nMaxPpaCnt = 0;

	for (INT nCellCntY = 0; nCellCntY < m_nMaxCellCntY; nCellCntY++)
	{
		for (INT nCellCntX = 0; nCellCntX < m_nMaxCellCntX; nCellCntX++)
		{
			nTotalSlotCntX = (int)(float)(CModelData::m_AtMaterialPara.Info.dSlotTotalPitchX[nCellCntX][nCellCntY] / CModelData::m_AtMaterialPara.Info.dSlotPitchX[nCellCntX][nCellCntY] + 1);
			nTotalSlotCntY = (int)(float)(CModelData::m_AtMaterialPara.Info.dSlotTotalPitchY[nCellCntX][nCellCntY] / CModelData::m_AtMaterialPara.Info.dSlotPitchY[nCellCntX][nCellCntY] + 1);

			for (int j = 0; j < (int)m_nMaxPatCntY; j++)
			{
				for (int i = 0; i < (int)m_nMaxPatCntX; i++)
				{
					////PosY
					dPPAPosY = CModelData::m_AtMaterialPara.Info.dCellLeftTopY[nCellCntX][nCellCntY];
					dPPAPosY += CModelData::m_AtMaterialPara.Info.dSlotCenterShiftY[nCellCntX][nCellCntY];
					if (m_nMaxPatCntY > 1)
						dPPAPosY -= CModelData::m_AtMaterialPara.Info.dSlotTotalPitchY[nCellCntX][nCellCntY] / (m_nMaxPatCntY - 1) * j;
					else
						dPPAPosY -= CModelData::m_AtMaterialPara.Info.dSlotTotalPitchY[nCellCntX][nCellCntY] / 2;

					if (m_nMaxPatCntY > 1)
					{
						if (nTotalSlotCntY % 2 == 0 && j % 2 == 1 && (m_nMaxPatCntY == 1 || m_nMaxPatCntY == 3))
						{
							dPPAPosY -= CModelData::m_AtMaterialPara.Info.dSlotPitchY[nCellCntX][nCellCntY] / 2;
						}
						else if (nTotalSlotCntY % 2 == 0 && m_nMaxPatCntY == 4) //KJT 20210526
						{
							if (j == 1)
								dPPAPosY += CModelData::m_MaterialPara.Info.dSlotPitchY[nCellCntX][nCellCntY] / (m_nMaxPatCntY - 1);
							else if (j == 2)
								dPPAPosY -= CModelData::m_MaterialPara.Info.dSlotPitchY[nCellCntX][nCellCntY] / (m_nMaxPatCntY - 1);
						}
						else if (nTotalSlotCntY % 2 == 0 && m_nMaxPatCntY == 5) //KJT 20210526
						{
							if (j == 1)
								dPPAPosY += CModelData::m_MaterialPara.Info.dSlotPitchY[nCellCntX][nCellCntY] / (m_nMaxPatCntY - 1);
							else if (j == 2)
								dPPAPosY -= CModelData::m_MaterialPara.Info.dSlotPitchY[nCellCntX][nCellCntY] / 2;
							else if (j == 3)
								dPPAPosY -= CModelData::m_MaterialPara.Info.dSlotPitchY[nCellCntX][nCellCntY] / (m_nMaxPatCntY - 1);
						}
					}
					else if (m_nMaxPatCntY == 1)
					{
						if (nTotalSlotCntY % 2 == 0)
						{
							dPPAPosY -= CModelData::m_AtMaterialPara.Info.dSlotPitchY[nCellCntX][nCellCntY] / 2;
						}
					}
					dPPAPosY *= STICK_FLIP_XY;

					////PosX
					dPPAPosX = CModelData::m_AtMaterialPara.Info.dCellLeftTopX[nCellCntX][nCellCntY];
					dPPAPosX += CModelData::m_AtMaterialPara.Info.dSlotCenterShiftX[nCellCntX][nCellCntY];

					if (m_nMaxPatCntX > 1)
						dPPAPosX += CModelData::m_AtMaterialPara.Info.dSlotTotalPitchX[nCellCntX][nCellCntY] / (m_nMaxPatCntX - 1) * i;
					else
						dPPAPosX += CModelData::m_AtMaterialPara.Info.dSlotTotalPitchX[nCellCntX][nCellCntY] / 2;

					if (m_nMaxPatCntX > 1)
					{
						if (nTotalSlotCntX % 2 == 0 && i % 2 == 1 && (m_nMaxPatCntX == 1 || m_nMaxPatCntX == 3))
						{
							dPPAPosX -= CModelData::m_AtMaterialPara.Info.dSlotPitchX[nCellCntX][nCellCntY] / 2;
						}
						else if (nTotalSlotCntX % 2 == 0 && m_nMaxPatCntX == 4) //KJT 20210526
						{
							if (i == 1)
								dPPAPosX += CModelData::m_MaterialPara.Info.dSlotPitchX[nCellCntX][nCellCntY] / (m_nMaxPatCntX - 1);
							else if (i == 2)
								dPPAPosX -= CModelData::m_MaterialPara.Info.dSlotPitchX[nCellCntX][nCellCntY] / (m_nMaxPatCntX - 1);
						}
						else if (nTotalSlotCntX % 2 == 0 && m_nMaxPatCntX == 5) //KJT 20210526
						{
							if (i == 1)
								dPPAPosX += CModelData::m_MaterialPara.Info.dSlotPitchX[nCellCntX][nCellCntY] / (m_nMaxPatCntX - 1);
							else if (i == 2)
								dPPAPosX -= CModelData::m_MaterialPara.Info.dSlotPitchX[nCellCntX][nCellCntY] / 2;
							else if (i == 3)
								dPPAPosX -= CModelData::m_MaterialPara.Info.dSlotPitchX[nCellCntX][nCellCntY] / (m_nMaxPatCntX - 1);
						}
					}
					else if (m_nMaxPatCntX == 1)
					{
						if (nTotalSlotCntX % 2 == 0)
						{
							dPPAPosX -= CModelData::m_AtMaterialPara.Info.dSlotPitchX[nCellCntX][nCellCntY] / 2;
						}
					}
					dPPAPosX *= STICK_FLIP_XY;

					PPAPos[nCellCntX][nCellCntY][i][j].dPosX = dPPAPosX;
					PPAPos[nCellCntX][nCellCntY][i][j].dPosY = dPPAPosY;
					PPAPos[nCellCntX][nCellCntY][i][j].dCdX = CModelData::m_AtMaterialPara.Info.dSlotSizeX[nCellCntX][nCellCntY];
					PPAPos[nCellCntX][nCellCntY][i][j].dCdY = CModelData::m_AtMaterialPara.Info.dSlotSizeY[nCellCntX][nCellCntY];

					m_nMaxPpaCnt++;

					Str.Format(_T("PPA Pos %2d - X:%.5f, Y:%.5f (CD_X:%.5f, CD_Y:%.5f)"),
						m_nMaxPpaCnt,
						Devs::m_GantryMotion.PPAPos[nCellCntX][nCellCntY][i][j].dPosX,
						Devs::m_GantryMotion.PPAPos[nCellCntX][nCellCntY][i][j].dPosY,
						Devs::m_GantryMotion.PPAPos[nCellCntX][nCellCntY][i][j].dCdX,
						Devs::m_GantryMotion.PPAPos[nCellCntX][nCellCntY][i][j].dCdY);
					Total_Msg(Str);
				}
			}
		}
	}

	return TRUE;
}

BOOL CGantryMotion::MakeIndividualAtPpaPosition(INT nStickIndex, INT nDivX, INT nDivY)
{
	INT nActiveStick = nStickIndex;
	INT nTotalSlotCntX, nTotalSlotCntY = 0;
	DOUBLE dPPAPosX, dPPAPosY = 0.;

	//PPA Position Data Reset
	ResetPpaData();

	m_nMaxCellCntX = (INT)CModelData::m_AtMaterialPara.Info.nCellCountX;
	m_nMaxCellCntY = (INT)CModelData::m_AtMaterialPara.Info.nCellCountY;
	m_nMaxPatCntX = nDivX;
	m_nMaxPatCntY = nDivY;
	m_nMaxPpaCnt = 0;

	for (INT nCellCntY = 0; nCellCntY < m_nMaxCellCntY; nCellCntY++)
	{
		for (INT nCellCntX = 0; nCellCntX < m_nMaxCellCntX; nCellCntX++)
		{
			nTotalSlotCntX = (int)(float)(CModelData::m_AtMaterialPara.Info.dSlotTotalPitchX[nCellCntX][nCellCntY] / CModelData::m_AtMaterialPara.Info.dSlotPitchX[nCellCntX][nCellCntY] + 1);
			nTotalSlotCntY = (int)(float)(CModelData::m_AtMaterialPara.Info.dSlotTotalPitchY[nCellCntX][nCellCntY] / CModelData::m_AtMaterialPara.Info.dSlotPitchY[nCellCntX][nCellCntY] + 1);

			for (int j = 0; j < (int)m_nMaxPatCntY; j++)
			{
				for (int i = 0; i < (int)m_nMaxPatCntX; i++)
				{
					////PosY
					dPPAPosY = CModelData::m_AtMaterialPara.Info.dCellLeftTopX[nCellCntX][nCellCntY];
					dPPAPosY += CModelData::m_AtMaterialPara.Info.dSlotCenterShiftX[nCellCntX][nCellCntY];

					if (m_nMaxPatCntY > 1)
						dPPAPosY -= CModelData::m_AtMaterialPara.Info.dSlotTotalPitchY[nCellCntX][nCellCntY] / (m_nMaxPatCntY - 1) * j;
					else
						dPPAPosY -= CModelData::m_AtMaterialPara.Info.dSlotTotalPitchY[nCellCntX][nCellCntY] / 2;

					if (m_nMaxPatCntY > 1)
					{
						if (nTotalSlotCntY % 2 == 0 && j % 2 == 1 && (m_nMaxPatCntY == 1 || m_nMaxPatCntY == 3))
						{
							dPPAPosY -= CModelData::m_AtMaterialPara.Info.dSlotPitchY[nCellCntX][nCellCntY] / 2;
						}
					}
					else if (m_nMaxPatCntY == 1)
					{
						if (nTotalSlotCntY % 2 == 0)
						{
							dPPAPosY -= CModelData::m_AtMaterialPara.Info.dSlotPitchY[nCellCntX][nCellCntY] / 2;
						}
					}
					dPPAPosY *= STICK_FLIP_XY;

					////PosX
					dPPAPosX = CModelData::m_AtMaterialPara.Info.dCellLeftTopX[nCellCntX][nCellCntY];
					dPPAPosX += CModelData::m_AtMaterialPara.Info.dSlotCenterShiftX[nCellCntX][nCellCntY];

					if (m_nMaxPatCntX > 1)
						dPPAPosX += CModelData::m_AtMaterialPara.Info.dSlotTotalPitchX[nCellCntX][nCellCntY] / (m_nMaxPatCntX - 1) * i;
					else
						dPPAPosX += CModelData::m_AtMaterialPara.Info.dSlotTotalPitchX[nCellCntX][nCellCntY] / 2;

					if (m_nMaxPatCntX > 1)
					{
						if (nTotalSlotCntX % 2 == 0 && i % 2 == 1 && (m_nMaxPatCntX == 1 || m_nMaxPatCntX == 3))
						{
							dPPAPosX -= CModelData::m_AtMaterialPara.Info.dSlotPitchX[nCellCntX][nCellCntY] / 2;
						}
					}
					else if (m_nMaxPatCntX == 1)
					{
						if (nTotalSlotCntX % 2 == 0)
						{
							dPPAPosX -= CModelData::m_AtMaterialPara.Info.dSlotPitchX[nCellCntX][nCellCntY] / 2;
						}
					}
					dPPAPosX *= STICK_FLIP_XY;

					PPAPos[nCellCntX][nCellCntY][i][j].dPosX = dPPAPosX;
					PPAPos[nCellCntX][nCellCntY][i][j].dPosY = dPPAPosY;
					PPAPos[nCellCntX][nCellCntY][i][j].dCdX = CModelData::m_AtMaterialPara.Info.dSlotSizeX[nCellCntX][nCellCntY];
					PPAPos[nCellCntX][nCellCntY][i][j].dCdY = CModelData::m_AtMaterialPara.Info.dSlotSizeY[nCellCntX][nCellCntY];

					m_nMaxPpaCnt++;
				}
			}
		}
	}

	return TRUE;
}

BOOL CGantryMotion::ResetPpaData()
{
	memset(PPAPos, 0, sizeof(PPAPos));

	return TRUE;
}
BOOL CGantryMotion::CheckCamSameValue(double m_AlignVisionPreResultValueX, double m_AlignVisionResultValueX, double m_AlignVisionPreResultValueY, double m_AlignVisionResultValueY)
{

	if (m_AlignVisionPreResultValueX == m_AlignVisionResultValueX && m_AlignVisionPreResultValueY == m_AlignVisionResultValueY)
		return FALSE;

	return TRUE;
}
BOOL CGantryMotion::GetPpaMaxMinCenterData(int nCellXNum, double *dPpaX, double *dPpaY)
{
	INT nCellIndexY = 0;
	INT nPatIndexX = 0;
	INT nPatIndexY = 0;

	DOUBLE dMaxX = -99999999., dMaxY = -99999999.;
	DOUBLE dMinX = 99999999., dMinY = 99999999.;

	INT nInspNum = 0;

	for (nCellIndexY = 0; nCellIndexY < m_nMaxCellCntY; nCellIndexY++)
	{
		for (nPatIndexX = 0; nPatIndexX < m_nMaxPatCntX; nPatIndexX++)
		{
			for (nPatIndexY = 0; nPatIndexY < m_nMaxPatCntY; nPatIndexY++)
			{
				if (dMaxX < PPAPos[nCellXNum][nCellIndexY][nPatIndexX][nPatIndexY].dResultPpaX)
					dMaxX = PPAPos[nCellXNum][nCellIndexY][nPatIndexX][nPatIndexY].dResultPpaX;

				if (dMaxY < PPAPos[nCellXNum][nCellIndexY][nPatIndexX][nPatIndexY].dResultPpaY)
					dMaxY = PPAPos[nCellXNum][nCellIndexY][nPatIndexX][nPatIndexY].dResultPpaY;

				if (dMinX > PPAPos[nCellXNum][nCellIndexY][nPatIndexX][nPatIndexY].dResultPpaX)
					dMinX = PPAPos[nCellXNum][nCellIndexY][nPatIndexX][nPatIndexY].dResultPpaX;

				if (dMinY > PPAPos[nCellXNum][nCellIndexY][nPatIndexX][nPatIndexY].dResultPpaY)
					dMinY = PPAPos[nCellXNum][nCellIndexY][nPatIndexX][nPatIndexY].dResultPpaY;

				nInspNum++;
			}
		}
	}

	if (nInspNum == 0)
		return FALSE;

	*dPpaX = (dMaxX + dMinX) / 2;
	*dPpaY = (dMaxY + dMinY) / 2;

	return TRUE;
}
#pragma endregion

BOOL CGantryMotion::CheckGantryXYZMoveInterlock()
{
	CString Str = _T("");

	//Servo On Check
	if (SharedInfo::GetServoOnStatus(AXIS_GANTRY_X) != TRUE)
	{
		Total_Msg(_T("Gantry X Servo On Check !!!"));
		return FALSE;
	}
	if (SharedInfo::GetServoOnStatus(AXIS_GANTRY_Y1) != TRUE)
	{
		Total_Msg(_T("Gantry Y Servo On Check !!!"));
		return FALSE;
	}

	//Home Status Check
	if (SharedInfo::GetHomeStatus(AXIS_GANTRY_X) != TRUE)
	{
		Total_Msg(_T("Gantry X Home Status Check !!!"));
		return FALSE;
	}
	if (SharedInfo::GetHomeStatus(AXIS_GANTRY_Y1) != TRUE)
	{
		Total_Msg(_T("Gantry Y Home Status Check !!!"));
		return FALSE;
	}	

	return TRUE;
}

BOOL CGantryMotion::CheckGantryXYZFlowInterlock(CString StrFlow, int nFlow, int nStartNo)
{
	CString Str;

	if (SharedInfo::GetServoOnStatus(AXIS_GANTRY_X) != TRUE)
	{		
		Str.Format(_T("%s : Gantry X Servo On Check"), StrFlow);
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, nFlow + nStartNo + 0);
		return FALSE;
	}
	if (SharedInfo::GetServoOnStatus(AXIS_GANTRY_Y1) != TRUE)
	{		
		Str.Format(_T("%s : Gantry Y Servo On Check"), StrFlow);
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, nFlow + nStartNo + 1);		
		return FALSE;
	}
	if (SharedInfo::GetServoOnStatus(AXIS_CAMERA_Z1) != TRUE)
	{		
		Str.Format(_T("%s : Camera Z1 Servo On Check"), StrFlow);
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, nFlow + nStartNo + 2);		
		return FALSE;
	}
	//if (SharedInfo::GetServoOnStatus(AXIS_CAMERA_Z2) != TRUE)
	//{		
	//	Str.Format(_T("%s : Camera Z2 Servo On Check"), StrFlow);
	//	Total_Msg(Str);
	//	SharedInfo::SetAlarm(Str, nFlow + nStartNo + 3);		
	//	return FALSE;
	//}
	//if (SharedInfo::GetServoOnStatus(AXIS_CAMERA_Z3) != TRUE)
	//{		
	//	Str.Format(_T("%s : Camera Z3 Servo On Check"), StrFlow);
	//	Total_Msg(Str);
	//	SharedInfo::SetAlarm(Str, nFlow + nStartNo + 4);		
	//	return FALSE;
	//}


	if (SharedInfo::GetHomeStatus(AXIS_GANTRY_Y1) != TRUE)
	{	
		Str.Format(_T("%s : Gantry Y Homing Check"), StrFlow);
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, nFlow + nStartNo + 5);		
		return FALSE;
	}
	if (SharedInfo::GetHomeStatus(AXIS_GANTRY_X) != TRUE)
	{	
		Str.Format(_T("%s : Gantry X Homing Check"), StrFlow);
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, nFlow + nStartNo + 6);		
		return FALSE;
	}

	if (SharedInfo::GetHomeStatus(AXIS_CAMERA_Z1) != TRUE)
	{		
		Str.Format(_T("%s : Camera Z1 Homing Check"), StrFlow);
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, nFlow + nStartNo + 7);		
		return FALSE;
	}
	//if (SharedInfo::GetHomeStatus(AXIS_CAMERA_Z2) != TRUE)
	//{		
	//	Str.Format(_T("%s : Camera Z2 Homing Check"), StrFlow);
	//	Total_Msg(Str);
	//	SharedInfo::SetAlarm(Str, nFlow + nStartNo + 8);		
	//	return FALSE;
	//}
	//if (SharedInfo::GetHomeStatus(AXIS_CAMERA_Z3) != TRUE)
	//{	
	//	Str.Format(_T("%s : Camera Z3 Homing Check"), StrFlow);
	//	Total_Msg(Str);
	//	SharedInfo::SetAlarm(Str, nFlow + nStartNo + 9);		
	//	return FALSE;
	//}

	return TRUE;
}

DOUBLE CGantryMotion::GetLaserDispValue()
{
#ifdef SIM_MODE
	return 0.5;
#endif

	return SharedInfo::m_dLaserDispFVal;


	return 0;
}

BOOL CGantryMotion::LaserFocusMove(BOOL bIsGlass /*= FALSE*/)
{
	CString Str = _T("");
#ifdef SIM_MODE
	return TRUE;
#endif

	//21.02.22 sjc z1 -> z3
	int retryCnt = 0;
	if (fabs(SharedInfo::m_dLaserDispFVal) == 0.0)
	{
		//m_dPosZ = SharedInfo::VisionAxisCmdPos[DIRECT_AXIS_AJIN_CAMERA_Z3] + 0.01;
		m_dPosZ = SharedInfo::VisionAxisCmdPos[DIRECT_AXIS_CAMERA_Z1];// +0.01;
	}
	else if (fabs(SharedInfo::m_dLaserDispFVal) >= 2.0)
	{
		//m_dPosZ = SharedInfo::VisionAxisCmdPos[DIRECT_AXIS_AJIN_CAMERA_Z3] - 0.01;
		m_dPosZ = SharedInfo::VisionAxisCmdPos[DIRECT_AXIS_CAMERA_Z1]-0.01;
	}
	else
	{
		if(bIsGlass == TRUE)
			m_dLaserPosZ = SharedInfo::m_dLaserDispFVal - CSystemData::m_Coordinate.Info.dLaserFocusOffsetGlass;
		else
			m_dLaserPosZ = SharedInfo::m_dLaserDispFVal - CSystemData::m_Coordinate.Info.dLaserFocusOffsetStick;

		m_dPosZ = SharedInfo::VisionAxisCmdPos[DIRECT_AXIS_CAMERA_Z1] - m_dLaserPosZ;
	}

	if (m_dPosZ < CMachineData::m_MachineDataMotor.Info.dSafetyPosMin[AXIS_CAMERA_Z1]) //27.0
	{
		Str.Format(_T("LaserFocusMove Error !! (TargetPosZ:%.5f, SafetyMinZ:%.5f"), m_dPosZ, CMachineData::m_MachineDataMotor.Info.dSafetyPosMin[AXIS_CAMERA_Z1]);
		Total_Msg(Str);
		return FALSE;
	}

	Move_GantryZ1_Pos(m_dPosZ);

	return TRUE;
}
BOOL CGantryMotion::LaserFocusMoveCheck()
{
#ifdef SIM_MODE
	return TRUE;
#endif

	return IsMoveDone(AXIS_CAMERA_Z1, m_dPosZ);
}
BOOL CGantryMotion::LaserFocusDoneCheck()
{

#ifdef SIM_MODE
	return TRUE;
#endif
	CString Str = _T("");
	int RetryCnt = 0;
	BOOL bResult = TRUE;
	while (1)
	{
		if (fabs(SharedInfo::m_dLaserDispFVal) > 0.001)
			break;
		Sleep(10);
		RetryCnt++;
		if (RetryCnt > 500)
		{
			bResult = FALSE;
			break;
		}
	}
	if (bResult == FALSE)
		return FALSE;

	//21.02.22 sjc z1 -> z3
	m_dPosZ = SharedInfo::VisionAxisCmdPos[DIRECT_AXIS_CAMERA_Z1] - SharedInfo::m_dLaserDispFVal + CSystemData::m_Coordinate.Info.dLaserFocusOffsetGlass;
	Str.Format(_T("Laser Pos : %10.5f"), m_dPosZ);
	Total_Msg(Str);
	if (m_dPosZ < CMachineData::m_MachineDataMotor.Info.dSafetyPosMin[AXIS_CAMERA_Z1]) //27.0
	{
		Str.Format(_T("Camera Z1 Safety Pos Min Error !! (Safety Pos Min : %.5f)"), CMachineData::m_MachineDataMotor.Info.dSafetyPosMin[AXIS_CAMERA_Z1]);
		Total_Msg(Str);
		return FALSE;
	}

	return TRUE;
}

int CGantryMotion::CameraZ1ImageFocusMove(double dRelPos)
{
	CVisionAgentDlg* pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	int nAxisNo = DIRECT_AXIS_CAMERA_Z1;

	double dCurPos = 0.0;
	double dPos = 0.0;
#if 0
	double dVel = 200.0;		// 100.0;//300.0;// 200;// 100.0;// 200.0;// pDlg->m_VelocityData.m_WorkVelocity.m_dMotorVel[MOTOR_CAMERA_Z1][m_nSpeedMode];
	double dAccel = 200.0;		// dVel * 2.0;// 2.0; //50.0;// 50.0;// 100.0;// 250.0; //_UMAC_ACCEL_TIME_250;// dVel * 10.0;// 0.5;
	double dDecel = 100.0;		// dVel * 1.0; //50.0;// 50.0;// 100.0;// 100.0;// 250.0; //_UMAC_ACCEL_TIME_250;// dVel * 10.0;// 10.0;// 0.5;// 0.5;
#else //KJT 20210803
	double dVel = CSystemData::m_Option.Info.m_dSmart_Vel;
	double dAccel = CSystemData::m_Option.Info.m_dSmart_Accel;
	double dDecel = CSystemData::m_Option.Info.m_dSmart_Decel;

	if (dVel < 0.001 || dVel > 3000.0)
		dVel = 200.0;
	if (dAccel < 0.001 || dAccel > 3000.0)
		dAccel = 200.0;
	if (dDecel < 0.001 || dDecel > 3000.0)
		dDecel = 100.0;
#endif
	//if (IsAxisMotionReady(nAxisNo) == 0) return RET_MOTION_IS_NOT_READY;
	//if (dRelPos == 0.0) return TRUE; //DO NOT USE!!

	//////////////////////////////////////////////////////////////////////
	//Software Focus Move
	//Modify
	if (1) //pStateMan->IsGlassAlignMapping() == FALSE)
	{
		dPos = SharedInfo::m_dAutoFocusStartPosZ;
	}	

	dPos = dPos + dRelPos;
	dPos = dPos - CSystemData::m_Coordinate.Info.dOffsetCameraZ[DIRECT_AXIS_CAMERA_Z1];
	AxmStatusGetCmdPos(nAxisNo, &dCurPos);

	//sunghaklee(2019.02.24)
	//if (fabs(dPos - dCurPos) >= 0.000001)
	if (fabs(dPos - dCurPos) >= 0.001)
	{
		AxmMoveStartPos(nAxisNo, dPos, dVel, dAccel, dDecel);
	}

	return TRUE;
}


//21.03.05 SJC
BOOL CGantryMotion::Get_GantryXY_ReviewGlassAlignPos(int idx, double* dPosX, double* dPosY)
{
	switch (idx)
	{
	case 0:
		*dPosX = CModelData::m_GlassPara.Info.dGlassAlignMark_LB_X;
		*dPosY = CModelData::m_GlassPara.Info.dGlassAlignMark_LB_Y;
		break;
	case 1:
		*dPosX = CModelData::m_GlassPara.Info.dGlassAlignMark_LT_X;
		*dPosY = CModelData::m_GlassPara.Info.dGlassAlignMark_LT_Y;
		break;
	case 2:
		*dPosX = CModelData::m_GlassPara.Info.dGlassAlignMark_RT_X;
		*dPosY = CModelData::m_GlassPara.Info.dGlassAlignMark_RT_Y;
		break;
	case 3:
		*dPosX = CModelData::m_GlassPara.Info.dGlassAlignMark_RB_X;
		*dPosY = CModelData::m_GlassPara.Info.dGlassAlignMark_RB_Y;
		break;
	default:
		return FALSE;
	}
	
	return TRUE;
}

BOOL CGantryMotion::Move_GantryXY_ReviewGlassAlignPos(int idx, int bWithMoveBackLightX /*= 0*/)
{
	double dPosX,dPosY;
	
	
	BOOL nRtn;
	nRtn = Devs::m_GantryMotion.Get_GantryXY_ReviewGlassAlignPos(idx, &dPosX, &dPosY);
	if (nRtn == FALSE) return nRtn;
	nRtn = Devs::m_GantryMotion.Move_Gantry_X_Pos(dPosX, bWithMoveBackLightX);
	if (nRtn == FALSE) return nRtn;
	Sleep(10);
	nRtn = Devs::m_GantryMotion.Move_Gantry_Y_Pos(dPosY);
	if (nRtn == FALSE) return nRtn;

	return TRUE;
}

BOOL CGantryMotion::Is_GantryXY_ReviewGlassAlignPos(int idx)
{
	double dPosX, dPosY;
	BOOL nRtn,nRtn2;
	CString Str;
	nRtn = Devs::m_GantryMotion.Get_GantryXY_ReviewGlassAlignPos(idx, &dPosX, &dPosY);
	if (nRtn == FALSE)
	{
		Str.Format(_T("Get Reveiw Glass Align Pos Error. Index = %d "), idx);
		Total_Msg(Str);
		return nRtn;
	}
	enum_Axis eAxis1 = AXIS_GANTRY_X;
	enum_Axis eAxis2 = AXIS_GANTRY_Y1;
	
	nRtn = IsMoveDone(eAxis1, dPosX);
	Sleep(10);
	nRtn2 = IsMoveDone(eAxis2, dPosY);

	return (nRtn && nRtn2);
}