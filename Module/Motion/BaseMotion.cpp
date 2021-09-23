#include "stdafx.h"
#include "Motion/BaseMotion.h"
#include "Vision/SharedInfo.h"
#include "Vision/Devs.h"
#include "Data/MachineData.h"
#include "Data/SystemData.h"
#include "Log/Logger.h"
#include "Data/ManualData.h"

//----------------------------------------------------------
CBaseMotion::CBaseMotion()
{
	m_nWithMoveBackLightX = 0;
	m_bWithMoveAOICameraX = FALSE;
}
//----------------------------------------------------------
CBaseMotion::~CBaseMotion()
{

}

BOOL CBaseMotion::IsMovingCheck(double dPos1, double dPos2)
{
	if (fabs(dPos1 - dPos2) <= 1)
		return TRUE;
	else
		return FALSE;
}

BOOL CBaseMotion::IsSamePosition(double dPos1, double dPos2)
{
	if (fabs(dPos1 - dPos2) <= 0.002)
		return TRUE;
	else
		return FALSE;
}
BOOL CBaseMotion::IsSameUVWPosition(double dPos1, double dPos2)
{
	if (fabs(dPos1 - dPos2) <= 0.01)
		return TRUE;
	else
		return FALSE;
}

//----------------------------------------------------------
BOOL CBaseMotion::IsMotionDone(enum_Axis eAxis)
{
	int nAxisType = -1; // 0 DirectAjin, 1:RemoteUmac, 2:RemoteAjin
	int nAxisNo = -1;
	BOOL bRet = FALSE;
	enum_Axis eTemp = eAxis;
	
	SharedInfo::GetActualAxisNoByEnumAxis(eTemp, &nAxisType, &nAxisNo);
	
	switch (nAxisType)
	{
	case AXIS_TYPE_DIRECT_AJIN:
		bRet = IsVisionMotionDone(nAxisNo);
		break;
	case AXIS_TYPE_REMOTE_UMAC:
		bRet = IsUmacMotionDone(nAxisNo);
		break;
	case AXIS_TYPE_REMOTE_AJIN:
		bRet = IsAjinMotionDone(nAxisNo);
		break;
	}

	return bRet;
}
BOOL CBaseMotion::IsAxisMoveDone(enum_Axis eAxis, double dTargetPos)
{
	double dPos = 0.0;
	
	dPos = SharedInfo::GetCmdPos(eAxis);

	return (IsSamePosition(dPos, dTargetPos) && IsMotionDone(eAxis));
}
//----------------------------------------------------------
BOOL CBaseMotion::IsUmacMotionDone(int nAxisNo)
{
	return (!SharedInfo::UmacInMotionStatus[nAxisNo]);
}
//----------------------------------------------------------
BOOL CBaseMotion::IsAjinMotionDone(int nAxisNo)
{
	return (!SharedInfo::AxisInMotionStatus[nAxisNo]);
}
//----------------------------------------------------------
BOOL CBaseMotion::IsVisionMotionDone(int nAxisNo)
{
	return (!SharedInfo::VisionAxisInMotionStatus[nAxisNo]);
}
//----------------------------------------------------------
//Jog 부분 이식.
BOOL CBaseMotion::UMacAxisMove(int nAxis, double dPosition, double dVel, double dAccel, double dDecel, MOTION_MODE Mode, int nWithMoveBackLightX/* = 0*/, double dAOICamOffset /* = 0.0*/, BOOL bDirBwd/* = FALSE*/, enum_AOI_Vel_Level eAoiVelLevel/* = eAOI_Vel_50*/)
{
	CString Str = _T("");
	int nFwdDelay = 0, nBwdDelay = 0;
	double dFwdScale = 1.0, dBwdScale = 1.0;

	switch (Mode)
	{
	case eMOTION_ABS:
	case eMOTION_REL:
		if (nAxis == REMOTE_AXIS_UMAC_GANTRY_X)
		{
			nFwdDelay = CSystemData::m_Coordinate.Info.nBackLightXFwdStartDelay[eAoiVelLevel];
			dFwdScale = CSystemData::m_Coordinate.Info.dBackLightXFwdAccDecScale[eAoiVelLevel];
			nBwdDelay = CSystemData::m_Coordinate.Info.nBackLightXBwdStartDelay[eAoiVelLevel];
			dBwdScale = CSystemData::m_Coordinate.Info.dBackLightXBwdAccDecScale[eAoiVelLevel];

			Devs::MotionIf.UmacPosMove(nAxis, dPosition, dVel, dAccel, dDecel, Mode, nWithMoveBackLightX, dAOICamOffset, bDirBwd, nFwdDelay, nBwdDelay, dFwdScale, dBwdScale);
			
			Str.Format(_T("BackLightX Dir:%d, FwdDelay:%d, FwdAccDecScale:%.5f, BwdDelay:%d, BwdAccDecScale:%.5f)"), bDirBwd, nFwdDelay, dFwdScale, nBwdDelay, dBwdScale);
			Total_Msg(Str);
		}
		else
			Devs::MotionIf.UmacPosMove(nAxis, dPosition, dVel, dAccel, dDecel, Mode);
		break;

	case eMOTION_VEL:
		if (nAxis == REMOTE_AXIS_UMAC_GANTRY_X)
			Devs::MotionIf.UmacVelMove(nAxis, dVel, dAccel, dDecel, nWithMoveBackLightX);
		else
			Devs::MotionIf.UmacVelMove(nAxis, dVel, dAccel, dDecel);

		break;
	}

	return TRUE;
}
//----------------------------------------------------------
BOOL CBaseMotion::IsUMacAxisMove(int nAxis, double dPosition)
{
	double dVel = 0., dAccel = 0., dDecel = 0.;	
	double dCmdPos = SharedInfo::UmacCmdPos[nAxis];
	return (IsSamePosition(dCmdPos, dPosition) && IsUmacMotionDone(nAxis));
}
//----------------------------------------------------------
BOOL CBaseMotion::UMacAxisStop(int nAxis, int nWithMoveBackLightX/* = 0*/) //KJT 20200824
{
	double dVel = 0., dAccel = 0., dDecel = 0.;
	
	if (nAxis == REMOTE_AXIS_UMAC_GANTRY_X)
		Devs::MotionIf.UmacMoveStop(nAxis, dDecel, nWithMoveBackLightX);
	else
		Devs::MotionIf.UmacMoveStop(nAxis, dDecel);

	return TRUE;
}
//----------------------------------------------------------
BOOL CBaseMotion::AjinAxisMove(int nAxis, double dPosition, double dVel, double dAccel, double dDecel, MOTION_MODE Mode)
{
	switch (Mode)
	{
	case eMOTION_ABS:
		Devs::MotionIf.AxisPosMove(nAxis, dPosition, dVel, dAccel, dDecel, Mode);
	case eMOTION_REL:
		Devs::MotionIf.AxisPosMove(nAxis, dPosition, dVel, dAccel, dDecel, Mode);
		break;
	case eMOTION_VEL:
		Devs::MotionIf.AxisVelMove(nAxis, dVel, dAccel, dDecel);
		break;
	}

	return TRUE;
}
//----------------------------------------------------------
BOOL CBaseMotion::IsAjinAxisMove(int nAxis, double dPosition)
{
	double dVel = 0., dAccel = 0., dDecel = 0.;
	double dCmdPos = SharedInfo::AxisCmdPos[nAxis];
	return (IsSamePosition(dCmdPos, dPosition) && IsAjinMotionDone(nAxis));
}
//----------------------------------------------------------
BOOL CBaseMotion::AjinAxisStop(int nAxis)
{
	double dVel = 0., dAccel = 0., dDecel = 0.;

	Devs::MotionIf.AxisMoveStop(nAxis, dDecel);
	return TRUE;
}
//----------------------------------------------------------
BOOL CBaseMotion::VisionAxisMove(int nAxis, double dPosition, double dVel, double dAccel, double dDecel, MOTION_MODE Mode)
{
	double dPos = dPosition - CSystemData::m_Coordinate.Info.dOffsetCameraZ[nAxis]; //!!!

	double dCmdPos = SharedInfo::VisionAxisCmdPos[nAxis];
	switch (Mode)
	{
	case eMOTION_ABS:
		AxmMoveStartPos(nAxis, dPos, dVel, dAccel, dDecel);
		break;
	case eMOTION_REL:
		AxmMoveStartPos(nAxis, dPos + dCmdPos, dVel, dAccel, dDecel);
		break;
	case eMOTION_VEL:
		AxmMoveVel(nAxis, dVel, dAccel, dDecel);
		break;
	}

	return TRUE;
}
//----------------------------------------------------------
BOOL CBaseMotion::IsVisionAxisMove(int nAxis, double dPosition)
{
	double dVel = 0., dAccel = 0., dDecel = 0.;
	double dCmdPos = SharedInfo::VisionAxisCmdPos[nAxis];
	return (IsSamePosition(dCmdPos, dPosition) && IsVisionMotionDone(nAxis));
}
//----------------------------------------------------------
BOOL CBaseMotion::VisionAxisStop(enum_DIRECT_AXIS eAxis)
{
	//KJT 20200812
	enum_Axis eRetAxis = SharedInfo::GetVisionAxisNoByDirectAxis(eAxis);
	double dDecel = CMachineData::m_MachineDataMotor.Info.dAutoDecel[eRetAxis];
	AxmMoveStop(eAxis, 200); //!! enum_DIRECT_AXIS
	return TRUE;
}
//----------------------------------------------------------
void CBaseMotion::JogMove(enum_Axis eAxis, double dVel, double dAcc, double dDec, int nWithMoveBackLightX/* = 0*/, double dAOICamOffset /* = 0.0*/) //KJT 20200929
{
	int nAxisType = -1; // 0 DirectAjin, 1:RemoteUmac, 2:RemoteAjin
	int nAxisNo = -1;
	double dPos = 0;
	CString Str;

	if (dVel < 0)
	{
		SharedInfo::m_nJogDir = eDIR_MINUS;
	}
	else
	{
		SharedInfo::m_nJogDir = eDIR_PLUS;
	}

	//KJT 20210730 Hide
	//if (SharedInfo::GetAlarm())
	//{
	//	SharedInfo::SetAlarm(_T("Alarm Status !!"), 100);
	//	return;
	//}


	dPos = SharedInfo::GetCmdPos(eAxis);


	//if (!m_Safety.AxisAllMotionSafetyCheck(eAxis, dPos))
	//{
	//	JogStop(eAxis);
	//	return;
	//}

	if (SharedInfo::m_eAxisJogInterlock == SharedInfo::m_eAxisJog)
	{
		if (SharedInfo::m_nJogInterlockDir == SharedInfo::m_nJogDir)
		{
#if 0 //KJT 임시 막고
			if (!m_Safety.AxisAllMotionSafetyCheck(SharedInfo::m_eAxisJog, dPos))
			{
				SharedInfo::m_eAxisJogInterlock = SharedInfo::m_eAxisJog;
				SharedInfo::m_nJogInterlockDir = SharedInfo::m_nJogDir;

				//Jog Stop
				Devs::JogMotion.JogStop(SharedInfo::m_eAxisJog);
				//SharedInfo::m_eAxisJog = AXIS_NONE;
			}
#endif
		}
		else
		{

		}
	}
	else
	{
#if 0 //KJT 임시 막고
		if (!m_Safety.AxisAllMotionSafetyCheck(SharedInfo::m_eAxisJog, dPos))
		{
			SharedInfo::m_eAxisJogInterlock = SharedInfo::m_eAxisJog;
			SharedInfo::m_nJogInterlockDir = SharedInfo::m_nJogDir;

			//Jog Stop
			Devs::JogMotion.JogStop(SharedInfo::m_eAxisJog);
			//SharedInfo::m_eAxisJog = AXIS_NONE;
		}
#endif
	}


#ifndef SIM_MODE
	SharedInfo::GetActualAxisNoByEnumAxis(eAxis, &nAxisType, &nAxisNo);
	//JOG 인트락 추가.

	switch (nAxisType)
	{
	case AXIS_TYPE_DIRECT_AJIN:
		VisionAxisMove(nAxisNo, 0, dVel, dAcc, dDec, eMOTION_VEL);
		break;

	case AXIS_TYPE_REMOTE_UMAC:
		if (nAxisNo == REMOTE_AXIS_UMAC_GANTRY_X)
			UMacAxisMove(nAxisNo, 0, dVel, dAcc, dDec, eMOTION_VEL, nWithMoveBackLightX, dAOICamOffset);
		else
			UMacAxisMove(nAxisNo, 0, dVel, dAcc, dDec, eMOTION_VEL);
		break;

	case AXIS_TYPE_REMOTE_AJIN:
		AjinAxisMove(nAxisNo, 0, dVel, dAcc, dDec, eMOTION_VEL);
		break;
	}
#else
	if (!SharedInfo::GetAlarm())
	{
		SimulAxisJogMove(eAxis, dPos, dVel, dAcc, dDec);
	}

#endif
}
//----------------------------------------------------------
void CBaseMotion::JogStop(enum_Axis eAxis, int nWithMoveBackLightX/* = 0*/) //KJT 20200824
{
	int nAxisType = -1; // 0 DirectAjin, 1:RemoteUmac, 2:RemoteAjin
	int nAxisNo = -1;

	/*Choi
	SharedInfo::m_eAxisJog = AXIS_NONE;
	*/

#ifndef SIM_MODE
	SharedInfo::GetActualAxisNoByEnumAxis(eAxis, &nAxisType, &nAxisNo);

	switch (nAxisType)
	{
	case AXIS_TYPE_DIRECT_AJIN:
		VisionAxisStop((enum_DIRECT_AXIS)nAxisNo);
		break;

	case AXIS_TYPE_REMOTE_UMAC:
		if (nAxisNo == REMOTE_AXIS_UMAC_GANTRY_X)
			UMacAxisStop(nAxisNo, nWithMoveBackLightX);
		else
			UMacAxisStop(nAxisNo);

		break;

	case AXIS_TYPE_REMOTE_AJIN:
		AjinAxisStop(nAxisNo);
		break;
	}
#else
	SimulAxisJogStop(eAxis);
#endif

}
//----------------------------------------------------------
BOOL CBaseMotion::AbsMove(enum_Axis eAxis, double dPos, double dVel, double dAcc, double dDec, int nWithMoveBackLightX/* = 0*/, double dAOICamOffset/* = 0.0*/, BOOL bDirBwd/* = FALSE*/, enum_AOI_Vel_Level eAoiVelLevel/* = eAOI_Vel_50*/)
{
	int nAxisType = -1; // 0 DirectAjin, 1:RemoteUmac, 2:RemoteAjin
	int nAxisNo = -1;
	CString Str = _T("");
	CString StrSafety = _T("");
	double dPosBacklightX = 0.0;
	double dPosTemp = 0.0;

	if (SharedInfo::GetAlarm())
	{
		Str.Format(_T("Alarm Status !!"));
		Total_Msg(Str);
		//SharedInfo::SetAlarm(Str, 100); //KJT 20210719 Hide
		return FALSE;
	}

	if (SharedInfo::GetServoOnStatus(eAxis) == FALSE)
	{
		Str.Format(_T("%s Servo Off !!!"), SharedInfo::GetAxisName(eAxis));
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, 101);
		return FALSE;
	}

	//21.02.05 sjc add eAxis != AXIS_CAMERA_Z3 &&
	if (eAxis != AXIS_CAMERA_Z1 && SharedInfo::GetHomeStatus(eAxis) == FALSE)
	{
		Str.Format(_T("Check Home Status %s !!!"), SharedInfo::GetAxisName(eAxis));
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, 102);
		return FALSE;
	}

	if (dPos < CMachineData::m_MachineDataMotor.Info.dSafetyPosMin[eAxis])
	{
		Str.Format(_T("%s Target Pos Invalid !!! (Target Pos : %.5f, Safety Min Pos : %.5f)"),
			SharedInfo::GetAxisName(eAxis), dPos, CMachineData::m_MachineDataMotor.Info.dSafetyPosMin[eAxis]);
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, 103);
		return FALSE;
	}
	if (dPos > CMachineData::m_MachineDataMotor.Info.dSafetyPosMax[eAxis])
	{
		Str.Format(_T("%s Target Pos Invalid !!! (Target Pos : %.5f, Safety Max Pos : %.5f)"),
			SharedInfo::GetAxisName(eAxis), dPos, CMachineData::m_MachineDataMotor.Info.dSafetyPosMax[eAxis]);
		Total_Msg(Str);
		SharedInfo::SetAlarm(Str, 104);
		return FALSE;
	}


	//움직여도 되는지 확인하는 부분
	/*
	if (!m_Safety.AxisAllMotionSafetyCheck(eAxis, dPos))	return;
	*/
#ifndef SIM_MODE
	//실제 납품시 구동됨.
	SharedInfo::GetActualAxisNoByEnumAxis(eAxis, &nAxisType, &nAxisNo);

	switch (nAxisType)
	{
	case AXIS_TYPE_DIRECT_AJIN:

		if (SharedInfo::CheckSystemSafetyPos(eAxis, dPos, &StrSafety) == FALSE)
		{
			Str.Format(_T("System Safety : %s Target Pos Invalid !!! (Target Pos : %.5f)"), SharedInfo::GetAxisName(eAxis), dPos);
			Total_Msg(Str);			
			return FALSE;
		}

		VisionAxisMove(nAxisNo, dPos, dVel, dAcc, dDec, eMOTION_ABS);
		break;

	case AXIS_TYPE_REMOTE_UMAC:
		
		if (SharedInfo::CheckSystemSafetyPos(eAxis, dPos, &StrSafety) == FALSE)
		{
			Str.Format(_T("System Safety : %s Target Pos Invalid !!! (Target Pos : %.5f)"), SharedInfo::GetAxisName(eAxis), dPos);
			Total_Msg(Str);
			return FALSE;
		}

		if (nAxisNo == REMOTE_AXIS_UMAC_GANTRY_X)
			UMacAxisMove(nAxisNo, dPos, dVel, dAcc, dDec, eMOTION_ABS, nWithMoveBackLightX, dAOICamOffset, bDirBwd, eAoiVelLevel);
		else
			UMacAxisMove(nAxisNo, dPos, dVel, dAcc, dDec, eMOTION_ABS);
		break;

	case AXIS_TYPE_REMOTE_AJIN:
		
		if (SharedInfo::CheckSystemSafetyPos(eAxis, dPos, &StrSafety) == FALSE)
		{
			Str.Format(_T("System Safety : %s Target Pos Invalid !!! (Target Pos : %.5f)"), SharedInfo::GetAxisName(eAxis), dPos);
			Total_Msg(Str);
			return FALSE;
		}

		AjinAxisMove(nAxisNo, dPos, dVel, dAcc, dDec, eMOTION_ABS);
		break;
	}
#else
	SimulAxisAbsMove(eAxis, dPos, dVel, dAcc, dDec);
#endif

	return TRUE;
}
//----------------------------------------------------------
BOOL CBaseMotion::RelMove(enum_Axis eAxis, double dDist, double dVel, double dAcc, double dDec, int nWithMoveBackLightX/* = 0*/, double dAOICamOffset/* = 0.0*/) //KJT 20200929
{
	int nAxisType = -1; // 0 DirectAjin, 1:RemoteUmac, 2:RemoteAjin
	int nAxisNo = -1;
	double dPos = 0.;
	CString Str = _T("");
	CString StrSafety = _T("");

	if (SharedInfo::GetAlarm())
	{
		Str.Format(_T("Alarm Status !!"));
		Total_Msg(Str);
		//SharedInfo::SetAlarm(Str, 100); //KJT 20210731 Hide
		return FALSE;		
	}

	/*Choi
	if (!m_Safety.AxisAllMotionSafetyCheck(eAxis, dPos))
		return;
	*/

#ifndef SIM_MODE
	SharedInfo::GetActualAxisNoByEnumAxis(eAxis, &nAxisType, &nAxisNo);

	switch (nAxisType)
	{
	case AXIS_TYPE_DIRECT_AJIN:

		dPos = SharedInfo::GetCmdPos(eAxis) + dDist;
		if (SharedInfo::CheckSystemSafetyPos(eAxis, dPos, &StrSafety) == FALSE)
		{
			Str.Format(_T("System Safety : %s Target Pos Invalid !!! (Target Pos : %.5f)"), SharedInfo::GetAxisName(eAxis), dPos);
			Total_Msg(Str);
			return FALSE;
		}

		VisionAxisMove(nAxisNo, dDist, dVel, dAcc, dDec, eMOTION_REL);
		break;

	case AXIS_TYPE_REMOTE_UMAC:

		dPos = SharedInfo::GetCmdPos(eAxis) + dDist;
		if (SharedInfo::CheckSystemSafetyPos(eAxis, dPos, &StrSafety) == FALSE)
		{
			Str.Format(_T("System Safety : %s Target Pos Invalid !!! (Target Pos : %.5f)"), SharedInfo::GetAxisName(eAxis), dPos);
			Total_Msg(Str);
			return FALSE;
		}

		if (nAxisNo == REMOTE_AXIS_UMAC_GANTRY_X)
			UMacAxisMove(nAxisNo, dDist, dVel, dAcc, dDec, eMOTION_REL, nWithMoveBackLightX, dAOICamOffset);
		else
			UMacAxisMove(nAxisNo, dDist, dVel, dAcc, dDec, eMOTION_REL);

		break;

	case AXIS_TYPE_REMOTE_AJIN:
		
		dPos = SharedInfo::GetCmdPos(eAxis) + dDist;
		if (SharedInfo::CheckSystemSafetyPos(eAxis, dPos, &StrSafety) == FALSE)
		{
			Str.Format(_T("System Safety : %s Target Pos Invalid !!! (Target Pos : %.5f)"), SharedInfo::GetAxisName(eAxis), dPos);
			Total_Msg(Str);
			return FALSE;
		}

		AjinAxisMove(nAxisNo, dDist, dVel, dAcc, dDec, eMOTION_REL);
		break;
	}
#else
	dPos = SharedInfo::GetCmdPos(eAxis) + dDist;
	SimulAxisAbsMove(eAxis, dPos, dVel, dAcc, dDec);
#endif

	return TRUE;
}
//----------------------------------------------------------
BOOL CBaseMotion::StopAll()
{
	VisionAxisStop(DIRECT_AXIS_TEMP);

	Devs::MotionIf.SystemMoveStop(0);

	Total_Msg(_T("StopAll"));

	//Devs::CimMotion.SetMachineAutoModeOnOff(FALSE);

	SharedInfo::bMachineStopFlag = TRUE;

	return TRUE;
}
//----------------------------------------------------------
BOOL CBaseMotion::OriginStart(enum_Axis eAxis)
{
	CString Str = _T("");
	int nAxisType = -1; // 0 DirectAjin, 1:RemoteUmac, 2:RemoteAjin
	int nAxisNo = -1;
	double dPos = 0;

	if (SharedInfo::GetAlarm())
	{
		AfxMessageBox(_T("Check Alarm Status !!!"));
		return FALSE;
	}

	if (SharedInfo::GetServoOnStatus(eAxis) == FALSE)
	{
		AfxMessageBox(_T("Check Servo On !!!"));
		return FALSE;
	}

	SharedInfo::GetActualAxisNoByEnumAxis(eAxis, &nAxisType, &nAxisNo);

#ifndef SIM_MODE
	SharedInfo::bMachineStopFlag = FALSE;

	switch (nAxisType)
	{
	case AXIS_TYPE_DIRECT_AJIN:
		break;

	case AXIS_TYPE_REMOTE_UMAC:		
		SharedInfo::UmacOriginIngStatus[REMOTE_AXIS_UMAC_GANTRY_Y1] = 0;
		SharedInfo::UmacOriginIngStatus[REMOTE_AXIS_UMAC_GANTRY_Y2] = 0;
		SharedInfo::UmacOriginIngStatus[REMOTE_AXIS_UMAC_GANTRY_X] = 0;
		
		Devs::MotionIf.UmacHomeStart(nAxisNo);
		break;

	case AXIS_TYPE_REMOTE_AJIN:
		if (nAxisNo == REMOTE_AXIS_GLASS_UVW_Y1 || nAxisNo == REMOTE_AXIS_GLASS_UVW_Y2 || nAxisNo == REMOTE_AXIS_GLASS_UVW_X1 || nAxisNo == REMOTE_AXIS_GLASS_UVW_X2)
		{
			SharedInfo::RemoteAjinOriginIngStatus[REMOTE_AXIS_GLASS_UVW_Y1] = 0;
			SharedInfo::RemoteAjinOriginIngStatus[REMOTE_AXIS_GLASS_UVW_Y2] = 0;
			SharedInfo::RemoteAjinOriginIngStatus[REMOTE_AXIS_GLASS_UVW_X1] = 0;
			SharedInfo::RemoteAjinOriginIngStatus[REMOTE_AXIS_GLASS_UVW_X2] = 0;
		}	
		else
		{
			Str.Format(_T("AxisHomeStart %s"), SharedInfo::GetAxisName(eAxis));
			Total_Msg(Str);
			Devs::MotionIf.AxisHomeStart(nAxisNo);
			break;
		}
	}
#endif // !SIM_MODE

	return TRUE;
}
//----------------------------------------------------------
BOOL CBaseMotion::AlarmReset(enum_Axis eAxis)
{
#ifndef SIM_MODE
	int nAxisType = -1, nAxisNo = -1;
	if (!SharedInfo::GetActualAxisNoByEnumAxis(eAxis, &nAxisType, &nAxisNo)) return FALSE;

	if (nAxisType == AXIS_TYPE_DIRECT_AJIN)
	{
		AxmSignalServoAlarmReset(nAxisNo, ENABLE);
	}
	else if (nAxisType == AXIS_TYPE_REMOTE_UMAC)
	{
		//Devs::MotionIf.UmacSetAlarmClear(nAxisNo, ENABLE);
	}
	else if (nAxisType == AXIS_TYPE_REMOTE_AJIN)
	{
		//Devs::MotionIf.AxisSetAlarmClear(nAxisNo, ENABLE);
	}
#endif // !SIM_MODE
	return TRUE;
}
//----------------------------------------------------------
BOOL CBaseMotion::ServoOnOff(enum_Axis eAxis, BOOL nOnOff)
{
	int nAxisType = -1; // 0 DirectAjin, 1:RemoteUmac, 2:RemoteAjin
	int nAxisNo = -1;
	double dPos = 0.0;
	int nRet, nStatus;

	SharedInfo::GetActualAxisNoByEnumAxis(eAxis, &nAxisType, &nAxisNo);
	nStatus = nOnOff;

#ifndef SIM_MODE
	switch (nAxisType)
	{
	case AXIS_TYPE_DIRECT_AJIN:
		AxmSignalServoOn(nAxisNo, nStatus);
		break;
	case AXIS_TYPE_REMOTE_UMAC:
		Devs::MotionIf.UmacSetServoOnStatus(nAxisNo, nStatus);
		break;
	case AXIS_TYPE_REMOTE_AJIN:
		Devs::MotionIf.AxisSetServoOnStatus(nAxisNo, nStatus);
		break;
	}
#endif // !SIM_MODE

#ifdef SIM_MODE
	switch (nAxisType)
	{
	case AXIS_TYPE_DIRECT_AJIN:
		SharedInfo::VisionAxisServoOnStatus[nAxisNo] = nStatus;
		break;
	case AXIS_TYPE_REMOTE_UMAC:
		SharedInfo::UmacServoOnStatus[nAxisNo] = nStatus;
		break;
	case AXIS_TYPE_REMOTE_AJIN:
		SharedInfo::AxisServoOnStatus[nAxisNo] = nStatus;
		break;
	}
#endif  // SIM_MODE

	return TRUE;
}
//--------------------------------------------------------------------------
BOOL CBaseMotion::GetActualAxisNoByEnumAxis(enum_Axis eAxis, int* pAxisType, int* nRemoteAxis)
{
	int nType = -1; // 0 DirectAjin, 1:RemoteUmac, 2:RemoteAjin
	int nAxis = -1;
	BOOL bResult = TRUE;

	switch (eAxis)
	{
	case AXIS_GANTRY_Y1:		nType = AXIS_TYPE_REMOTE_UMAC;		nAxis = REMOTE_AXIS_UMAC_GANTRY_Y1;		break;
	case AXIS_GANTRY_Y2:	nType = AXIS_TYPE_REMOTE_UMAC;		nAxis = REMOTE_AXIS_UMAC_GANTRY_Y2;		break;
	case AXIS_GANTRY_X:		nType = AXIS_TYPE_REMOTE_UMAC;		nAxis = REMOTE_AXIS_UMAC_GANTRY_X;		break;

	case AXIS_CAMERA_Z1:		nType = AXIS_TYPE_REMOTE_AJIN;		nAxis = REMOTE_AXIS_CAMERA_Z1;		break;
	case AXIS_CAMERA_Z2:		nType = AXIS_TYPE_REMOTE_AJIN;		nAxis = REMOTE_AXIS_CAMERA_Z2;		break;
	
		//TO DO

	default: bResult = FALSE;
		break;
	}
#pragma endregion

	*pAxisType = nType;
	*nRemoteAxis = nAxis;

	return bResult;
}
//--------------------------------------------------------------------------
BOOL CBaseMotion::GetAxisJogParam(enum_Axis pAxis, double* pJogSpeed, double* pAccel, double* pDecel, int nSelJogSpeed)
{
	BOOL bResult = TRUE;
	int nTemp = (int)pAxis;
	/*Choi
	if (pAxis == AXIS_GRIPPER_VIRTUAL_F)
	{
		nTemp = AXIS_GRIPPER_Y_LF;
	}

	if (pAxis == AXIS_GRIPPER_VIRTUAL_B)
	{
		nTemp = AXIS_GRIPPER_Y_LB;
	}

	*pJogSpeed = CSystemData::m_Velocity.m_dJog[nTemp][nSelJogSpeed];
	*pAccel = CSystemData::m_Velocity.m_dAcc[nTemp];
	*pDecel = CSystemData::m_Velocity.m_dDec[nTemp];

	if (*pJogSpeed > CSystemData::m_Velocity.m_dMaxLimit[nTemp])
	{
		bResult = FALSE;
	}
	*/
	return bResult;
}
//----------------------------------------------------------
BOOL CBaseMotion::GetAxisWorkParam(enum_Axis pAxis, double* pSpeed, double* pAccel, double* pDecel)
{
	//저장된 파라미터 값을 가져온다
	BOOL bResult = TRUE;
	//Machine Data에서 저장된 축의 속도 & 가속 & 감속 값을 가져온다
	
	*pSpeed = CMachineData::m_MachineDataMotor.Info.dAutoVel[pAxis];
	*pAccel = CMachineData::m_MachineDataMotor.Info.dAutoAccel[pAxis];
	*pDecel = CMachineData::m_MachineDataMotor.Info.dAutoDecel[pAxis];
	
	//최대속도 Limit 제한
	if (*pSpeed > CMachineData::m_MachineDataMotor.Info.dMaxVel[pAxis])
	{
		bResult = FALSE;
	}
	
	return bResult;
}
//----------------------------------------------------------
BOOL CBaseMotion::SetDOutputBitValue(enum_Do eBit, int nValue)
{
#ifndef SIM_MODE
	int nBit = -1;

#if 0
	if (!m_Safety.AxisAllDoSafetyCheck(eBit, nValue))
	{
		return FALSE;
	}
#endif

	SharedInfo::GetActualIoNumByEnumDo(eBit, &nBit);
	if (nBit == -1)
		return FALSE;


	Devs::MotionIf.DOutputSetBitValue(nBit, nValue);
#else
	SharedInfo::DOutputValue[eBit] = nValue;
#endif
	return TRUE;
}
//----------------------------------------------------------
BOOL CBaseMotion::SetAOutputValue(enum_Ao eChannel, double dValue)
{
	int nChannel = -1;
	/*Choi
	if (!m_Safety.AxisAllAoSafetyCheck(eChannel, dValue))
	{
		return FALSE;
	}

	SharedInfo::GetActualIoNumByEnumAo(eChannel, &nChannel);

	if (nChannel == -1)
		return FALSE;

	Devs::MotionIf.AOutputSetChannelValue(nChannel, dValue);
	*/
	return TRUE;
}
//----------------------------------------------------------
BOOL CBaseMotion::GetDInputValue(enum_Di eBit)
{
	int nBit = -1;
	
	SharedInfo::GetActualIoNumByEnumDi(eBit, &nBit);
	if (nBit == -1)
		return FALSE;
	return SharedInfo::DInputValue[nBit];
	
	return FALSE;
}
//----------------------------------------------------------
BOOL CBaseMotion::GetAinputValue(enum_Ai eChannel)
{
	int nChannel = -1;
	/*Choi
	SharedInfo::GetActualIoNumByEnumAi(eChannel, &nChannel);
	if (nChannel == -1)
		return FALSE;

	return SharedInfo::AInputValue[nChannel];
	*/
	return FALSE;
}
//----------------------------------------------------------
BOOL CBaseMotion::SimulAxisAbsMove(enum_Axis eAxisNo, double dPos, double dVel, double dAcc, double dDec)
{
	SimulMotion.nSimual_Mode	= 0;
	SimulMotion.eAxis			= eAxisNo;
	SimulMotion.dTargetPos		= dPos;
	SimulMotion.dVel			= dVel;
	SimulMotion.dAcc			= dAcc;
	SimulMotion.dDec			= dDec;
	SimulMotion.nJogDir			= 0;
	AfxBeginThread(SimulThreadProc, this);
	return TRUE;
}
//----------------------------------------------------------
BOOL CBaseMotion::SimulAxisJogMove(enum_Axis eAxisNo, double dPos, double dVel, double dAcc, double dDec)
{
	SimulMotion.nSimual_Mode	= 1;
	SimulMotion.eAxis			= eAxisNo;
	SimulMotion.dTargetPos		= dPos;
	SimulMotion.dVel			= dVel;
	SimulMotion.dAcc			= dAcc;
	SimulMotion.dDec			= dDec;
	if (dVel > 0)
	{
		SimulMotion.nJogDir = 1;
	}
	else
	{
		SimulMotion.nJogDir = -1;
	}
	m_bJogStop = FALSE;
	AfxBeginThread(SimulThreadProc, this);

	return TRUE;
}
//----------------------------------------------------------
BOOL CBaseMotion::SimulAxisJogStop(enum_Axis eAxisNo)
{
	m_bJogStop = TRUE;
	return TRUE;
}
//----------------------------------------------------------
BOOL CBaseMotion::IsSimulAixsDone()
{
	return TRUE;
}

double CBaseMotion::ConvertTo20X_X(double dPosX)
{
	double dPos = dPosX - CSystemData::m_Coordinate.Info.dOffsetReview10xTo20x_X;
	return dPos;
}

double CBaseMotion::ConvertTo20X_Y(double dPosY)
{
	double dPos = dPosY - CSystemData::m_Coordinate.Info.dOffsetReview10xTo20x_Y;
	return dPos;
}

double CBaseMotion::ConvertToPreAlign_X(double dPosX)
{
	double dPos = dPosX - CSystemData::m_Coordinate.Info.dOffsetReview10xToPreAlign_X;
	return dPos;
}

double CBaseMotion::ConvertToPreAlign_Y(double dPosY)
{
	double dPos = dPosY - CSystemData::m_Coordinate.Info.dOffsetReview10xToPreAlign_Y;
	return dPos;
}

double CBaseMotion::ConvertToAOI_X(double dPosX)
{
	double dPos = dPosX - CSystemData::m_Coordinate.Info.dOffsetReview10xToAoi_X;
	return dPos;
}

double CBaseMotion::ConvertToAOI_Y(double dPosY)
{
	double dPos = dPosY - CSystemData::m_Coordinate.Info.dOffsetReview10xToAoi_Y;
	return dPos;
}

double CBaseMotion::ConvertTo3D_X(double dPosX)
{
	double dPos = dPosX - CSystemData::m_Coordinate.Info.dOffsetReview10xTo3dCam_X;
	return dPos;
}

double CBaseMotion::ConvertTo3D_Y(double dPosY)
{
	double dPos = dPosY - CSystemData::m_Coordinate.Info.dOffsetReview10xTo3dCam_Y;
	return dPos;
}

//----------------------------------------------------------
UINT SimulThreadProc(LPVOID lpParam)
{
	CBaseMotion *pParents;
	pParents = (CBaseMotion *)lpParam;

	DOUBLE dPos = 0, dCurPos = 0;
	SimulMotion MotionData = pParents->SimulMotion;
	DOUBLE dStartTick = 0., dCurrentTick = 0., dWaitTick;
	DOUBLE dStartPos	= SharedInfo::GetCmdPos(MotionData.eAxis);
	double dMove_Pos	= 0.000;
	
	pParents->m_bStopSimulThread = FALSE;
	dStartTick = GetTickCount64();

	DOUBLE dCalAcc = fabs(MotionData.dVel / (MotionData.dAcc / 1000));

	while (1)
	{
		if (pParents->m_bStopSimulThread == TRUE)
		{
			break;
		}
		dCurrentTick = GetTickCount64();
		dWaitTick = dCurrentTick - dStartTick;
		if (dWaitTick > (1000 * 30 * 1))
		{
			break;
		}
		if (MotionData.nSimual_Mode == 0)
		{
			// Rel Mode			
			double dDiff_Pos = 0.000;
			dDiff_Pos = MotionData.dTargetPos - dStartPos;
			if (fabs(dDiff_Pos) <= 0.002)
			{
				break;
			}
			if (dDiff_Pos > 0)
			{
				dMove_Pos = (0.5 * dCalAcc * ((dCurrentTick - dStartTick) * (dCurrentTick - dStartTick) / 1000000));
				dPos = dStartPos + dMove_Pos;
				SharedInfo::SetCmdPos(MotionData.eAxis, dPos);
				SharedInfo::SetActPos(MotionData.eAxis, dPos);
				if (dPos > MotionData.dTargetPos)
				{
					break;
				}
			}
			else
			{
				dMove_Pos = (-1) * (0.5 * dCalAcc * ((dCurrentTick - dStartTick) * (dCurrentTick - dStartTick) / 1000000));
				dPos = dStartPos + dMove_Pos;
				SharedInfo::SetCmdPos(MotionData.eAxis, dPos);
				SharedInfo::SetActPos(MotionData.eAxis, dPos);
				if (dPos < MotionData.dTargetPos)
				{
					break;
				}
			}
		}
		else if (MotionData.nSimual_Mode == 1)
		{
			// Jog Mode
			if (pParents->m_bJogStop == TRUE)
			{
				break;
			}
			if (MotionData.nJogDir > 0)
			{
				dMove_Pos = (0.5 * dCalAcc * ((dCurrentTick - dStartTick) * (dCurrentTick - dStartTick) / 1000000));
				dPos = dStartPos + dMove_Pos;
				SharedInfo::SetCmdPos(MotionData.eAxis, dPos);	
				SharedInfo::SetActPos(MotionData.eAxis, dPos);
			}
			else
			{
				dMove_Pos = (-1) * (0.5 * dCalAcc * ((dCurrentTick - dStartTick) * (dCurrentTick - dStartTick) / 1000000));
				dPos = dStartPos + dMove_Pos;
				SharedInfo::SetCmdPos(MotionData.eAxis, dPos);
				SharedInfo::SetActPos(MotionData.eAxis, dPos);
			}
		}
		Sleep(1);
	}
	
	return 0;
}
//----------------------------------------------------------