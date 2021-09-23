#include "stdafx.h"
#include "Safety.h"
#include "Data/SystemData.h"
#include "Vision/SharedInfo.h"
//#include "Motion/GripperMotion.h"
#include "Log/Logger.h"

Safety::Safety()
{

}

Safety::~Safety()
{

}


BOOL Safety::AxisAllDoSafetyCheck(enum_Do eDoNum, int nValue)
{
#if 0
	if (eDoNum ==  _DO_FRM_BCR_UP && nValue == TRUE)
	{
		if (!Safety::FrameBcrUpSafetyCheck())
			return FALSE;

	}

	if (eDoNum == _DO_FRM_BCR_DN && nValue == TRUE)
	{
		if (!Safety::FrameBcrDnSafetyCheck())
			return FALSE;

	}

	if (eDoNum == _DO_FRM_BCR_X_FOR && nValue == TRUE)
	{
		if (!Safety::FrameBcrExtSafetyCheck())
			return FALSE;

	}
#endif
	return TRUE;
}

BOOL Safety::AxisAllAoSafetyCheck(enum_Ao eAoNum, double nValue)
{

	return TRUE;
}

BOOL Safety::AxisAllMotionSafetyCheck(enum_Axis eAxis, double dPos)
{
	int nAxis = (int)eAxis;
	BOOL bRet = TRUE;
	switch (nAxis)
	{
	case AXIS_GANTRY_Y1:
		bRet = Safety::GantryYMoveSafetyCheck(eAxis, dPos);
		break;

	case AXIS_GANTRY_X:
		bRet = Safety::GantryXMoveSafetyCheck(eAxis, dPos);
		break;

	case AXIS_CAMERA_Z1:
	//case AXIS_CAMERA_Z2:
		bRet = Safety::GantryZMoveSafetyCheck(eAxis, dPos);
		break;
#ifndef GRIPPER_0
	case AXIS_GRIPPER_STRETCH_L1:
	case AXIS_GRIPPER_STRETCH_L2:
	case AXIS_GRIPPER_STRETCH_L3:
	case AXIS_GRIPPER_STRETCH_R1:
	case AXIS_GRIPPER_STRETCH_R2:
	case AXIS_GRIPPER_STRETCH_R3:
		bRet = Safety::GripperStretchMoveSafetyCheck(eAxis, dPos);
		break;
#endif
	}

	if (bRet == FALSE)
	{
		SharedInfo::SetAlarm(_T("ERROR : ALL Safety Check"), 3);

		if (!SharedInfo::MachineState.bAutoStopDoneCheck)
		{
			//Devs::StopAll();
			SharedInfo::MachineState.bAutoStopDoneCheck = TRUE;

		}
	}
	return bRet;
}

BOOL Safety::GantryXMoveSafetyCheck(enum_Axis eAxis, double dPos)
{
	int nAxisZ;
	double dCmdPosZ = 0.0, dSafetyLimitZ = 0.0, dWorkAreaXMinus = 0.0, dWorkAreaXPlus = 0.0;
	int nAxis = (int)eAxis;
	switch (nAxis)
	{
	case AXIS_GANTRY_X:
		//nAxisZ = DIRECT_AXIS_AJIN_GANTRY_Z_R;
		//dCmdPosZ = SharedInfo::AxisCmdPos[nAxisZ];
		//dSafetyLimitZ = CSystemData::m_Safety.Info.m_dWorkArea_CCD_Minus_ZL;
		//dWorkAreaXMinus = CSystemData::m_Safety.Info.m_dWorkArea_CCD_Minus_XL;
		//dWorkAreaXPlus = CSystemData::m_Safety.Info.m_dWorkArea_CCD_Plus_XL;
		break;
	}
	//Z Axis Up Check
	if (dPos < dWorkAreaXMinus || dPos> dWorkAreaXPlus)
	{
		if (dCmdPosZ < dSafetyLimitZ)
		{
			return SharedInfo::SetAlarm(_T("ERROR : X Move Safety Check"), 4);
		}
	}
	return TRUE;

}
BOOL Safety::GantryYMoveSafetyCheck(enum_Axis eAxis, double dPos)
{
	int nAxisZ[3];
	double dCmdPosZ[3] = { 0, }, dSafetyLimitZ[3] = { 0, }, dWorkAreaYMinus = 0.0, dWorkAreaYPlus = 0.0;
	int nAxis = (int)eAxis;
	switch (nAxis)
	{
	case AXIS_GANTRY_Y1:
		//nAxisZ[0] = DIRECT_AXIS_AJIN_GANTRY_Z_R;
		//nAxisZ[1] = DIRECT_AXIS_AJIN_GANTRY_Z_M;
		//nAxisZ[2] = DIRECT_AXIS_AJIN_GANTRY_Z_L;

		//dCmdPosZ[0] = SharedInfo::VisionAxisCmdPos[nAxisZ[0]];
		//dCmdPosZ[1] = SharedInfo::VisionAxisCmdPos[nAxisZ[1]];
		//dCmdPosZ[2] = SharedInfo::VisionAxisCmdPos[nAxisZ[2]];
		//dSafetyLimitZ[0] = CSystemData::m_Safety.Info.m_dWorkArea_CCD_Minus_ZL;
		//dSafetyLimitZ[1] = CSystemData::m_Safety.Info.m_dWorkArea_CCD_Minus_ZM;
		//dSafetyLimitZ[2] = CSystemData::m_Safety.Info.m_dWorkArea_CCD_Minus_ZR;
		//dWorkAreaYMinus = CSystemData::m_Safety.Info.m_dWorkArea_CCD_Minus_Y;
		//dWorkAreaYPlus = CSystemData::m_Safety.Info.m_dWorkArea_CCD_Plus_Y;
		break;	


	}
	//Z Axis Down Check
	if (dPos < dWorkAreaYMinus || dPos > dWorkAreaYPlus)
	{
		for (int i = 0; i < 3; i++)
		{
			if (dCmdPosZ[i] < dSafetyLimitZ[i])
			{
				return SharedInfo::SetAlarm(_T("ERROR : Y Move Safety Check"), 5);
			}
		}
	}
#if 0
	//RackJack Z Down Check.
	if (!Devs::FrameMotion.IsRackJackDownPos())
	{
		return SharedInfo::SetAlarm(_T("[Interlock] Check Frame Lift Z Down"));
	}
#endif
	//Gripper Down Check.


	//if (SharedInfo::AxisCmdPos[REMOTE_AXIS_AJIN_GRIPPER_Z_LF] >= CManualData::Gripper.MaskCtrlZ + 0.1 ||
	//	SharedInfo::AxisCmdPos[REMOTE_AXIS_AJIN_GRIPPER_Z_RF] >= CManualData::Gripper.MaskCtrlZ + 0.1)
	//	return FALSE;

	//if (SharedInfo::AxisCmdPos[REMOTE_AXIS_AJIN_GRIPPER_Z_LB] >= CManualData::Gripper.MaskCtrlZ + 0.1 ||
	//	SharedInfo::AxisCmdPos[REMOTE_AXIS_AJIN_GRIPPER_Z_RB] >= CManualData::Gripper.MaskCtrlZ + 0.1)
	//	return FALSE;

	//Gantry Top, Bottom Gap Check.

	return TRUE;
}
BOOL Safety::GantryZMoveSafetyCheck(enum_Axis eAxis, double dPos)
{
	int nAxisX = -1;
	int nAxisY = -1;
	double dCmdPosX = 0.0, dCmdPosY = 0.0, dWorkAreaXMinus = 0.0, dWorkAreaXPlus = 0.0, dWorkAreaYMinus = 0.0, dWorkAreaYPlus = 0.0, dSafetyLimitZ = 0.0;
	int nAxis = (int)eAxis;

	switch (nAxis)
	{
	case AXIS_CAMERA_Z1:
		//nAxisX = REMOTE_AXIS_UMAC_GANTRY_X_L;
		//nAxisY = REMOTE_AXIS_UMAC_VIRTUAL_GANTRY_Y;
		//dWorkAreaXMinus = CSystemData::m_Safety.Info.m_dWorkArea_CCD_Minus_XL;
		//dWorkAreaXPlus = CSystemData::m_Safety.Info.m_dWorkArea_CCD_Plus_XL;
		//dWorkAreaYMinus = CSystemData::m_Safety.Info.m_dWorkArea_CCD_Minus_Y;
		//dWorkAreaYPlus = CSystemData::m_Safety.Info.m_dWorkArea_CCD_Plus_Y;
		//dSafetyLimitZ = CSystemData::m_Safety.Info.m_dWorkArea_CCD_Minus_ZL;
		break;
	//case AXIS_CAMERA_Z2:
		//nAxisX = REMOTE_AXIS_UMAC_GANTRY_X_M;
		//nAxisY = REMOTE_AXIS_UMAC_VIRTUAL_GANTRY_Y;
		//dWorkAreaXMinus = CSystemData::m_Safety.Info.m_dWorkArea_CCD_Minus_XM;
		//dWorkAreaXPlus = CSystemData::m_Safety.Info.m_dWorkArea_CCD_Plus_XM;
		//dWorkAreaYMinus = CSystemData::m_Safety.Info.m_dWorkArea_CCD_Minus_Y;
		//dWorkAreaYPlus = CSystemData::m_Safety.Info.m_dWorkArea_CCD_Plus_Y;
		//dSafetyLimitZ = CSystemData::m_Safety.Info.m_dWorkArea_CCD_Minus_ZM;
		//break;
	
	}
	//Z Axis Down Check
	dCmdPosX = SharedInfo::UmacActPos[nAxisX];
	dCmdPosY = SharedInfo::UmacActPos[nAxisY];
	if (dPos < dSafetyLimitZ)
	{
		for (int i = 0; i < 3; i++)
		{
			if (dCmdPosX < dWorkAreaXMinus || dCmdPosX > dWorkAreaXPlus || dCmdPosY < dWorkAreaYMinus || dCmdPosY > dWorkAreaYPlus)
			{
				return SharedInfo::SetAlarm(_T("ERROR : Z Move Safety Check"), 6);
			}
		}
	}
	return TRUE;
}

BOOL Safety::GripperYMoveSafetyCheck(enum_Axis eAxis, double dPos)
{
	BOOL bResult = TRUE;
	DOUBLE dGripperGap = 0.;
	int nAxis = (int)eAxis;
#if 0
	//Transfer 가능 Z축인지 확인.
	switch (nAxis)
	{
	case AXIS_GRIPPER_Y_L:
	case AXIS_GRIPPER_Y_R:
	case AXIS_VIRTUAL_GRIPPER_Y:
		if (SharedInfo::AxisCmdPos[REMOTE_AXIS_AJIN_GRIPPER_Z_L] < CManualData::Gripper.MaskCtrlZ ||
			SharedInfo::AxisCmdPos[REMOTE_AXIS_AJIN_GRIPPER_Z_R] < CManualData::Gripper.MaskCtrlZ)
			bResult = FALSE;
		break;
	
	default:
		bResult = FALSE;
		break;
	}

	if (bResult == FALSE)
	{
		return SharedInfo::SetAlarm(_T("[Interlock] Check Gripper Z Height"));
	}

	//Gripper 끼리 충돌 가능성이 있는지 확인.
	switch (nAxis)
	{
	case AXIS_GRIPPER_Y_L:
		dGripperGap = dPos - SharedInfo::UmacActPos[REMOTE_AXIS_UMAC_GRIPPER_Y_L];
		break;
	case AXIS_GRIPPER_Y_R:
		dGripperGap = dPos - SharedInfo::UmacActPos[REMOTE_AXIS_UMAC_GRIPPER_Y_R];
		break;
	case AXIS_VIRTUAL_GRIPPER_Y:
		//Virtual Reletive dPos 
		dGripperGap = (dPos /*+  SharedInfo::UmacActPos[REMOTE_AXIS_UMAC_GRIPPER_Y_LF]*/)-SharedInfo::UmacActPos[REMOTE_AXIS_UMAC_GRIPPER_Y_LB];
		break;
	
	default:
		bResult = FALSE;
		break;
	}
	if (dGripperGap < CSystemData::m_Safety.Min_Dist_Gripper_Y)
	{
		bResult = SharedInfo::SetAlarm(_T("[Interlock] Check Gripper Y Gap Position"));
	}

	//RackJack Z Down Check.
	if (!Devs::FrameMotion.IsRackJackDownPos())
	{
		return SharedInfo::SetAlarm(_T("[Interlock] Check the Frame Rack Jack"));
	}
#endif
	return bResult;
}

BOOL Safety::GripperPitchMoveSafetyCheck(enum_Axis eAxis, double dPos)
{
#if 0
	if (!Devs::GripperTopMotion.IsClampOff())
	{
		return SharedInfo::SetAlarm(_T("[Interlock] Check the Clamp On"));
	}
#endif
	return TRUE;
}


BOOL Safety::GripperStretchMoveSafetyCheck(enum_Axis eAxis, double dPos)
{
#if 0
	if (!Devs::GripperMotion.IsClampOff())
	{
		if (fabs(dPos - SharedInfo::GetActPos(eAxis)) > 3)
		{
			return SharedInfo::SetAlarm(_T("[Interlock] Check the Clamp On"));
		}
	}
#endif
	return TRUE;
}


BOOL Safety::GripperZMoveSafetyCheck(enum_Axis eAxis, double dPos)
{
	return TRUE;
}
BOOL Safety::CassetteZMoveSafetyCheck()
{
	BOOL bResult;
#if 0
	//Awk 앞쪽 센서 센셍 이상. Clamp 상태로 인터락 변경.
	//if (!SharedInfo::DInputValue[_CST_RECIVE_CHK_1] || !SharedInfo::DInputValue[_CST_RECIVE_CHK_2] || SharedInfo::DInputValue[_CST_FINGER_FORWARD])
#ifdef SIM_MODE
	return TRUE;
#endif
	if (!Devs::MaskLoaderMotion.IsTRFClamp(FALSE))
	{
		return SharedInfo::SetAlarm(_T("[Interlock] Check Cst Finger Clamp."));
	}

	//Awk Cst Sensor Check.
	//if (!SharedInfo::DInputValue[_CST_FORWARD_CHK_1])
	//{
	//	return SharedInfo::SetAlarm(_T("[Interlock] Check The Cst Lot Forward."));
	//}
	//Ssming A / B Need Signal Check
	if (Devs::MaskLoaderMotion.IsCstForward1())
	{
		return SharedInfo::SetAlarm(_T("[Interlock] Check The Cst Lot Forward #1."));
	}

	if (!Devs::MaskLoaderMotion.IsCstForward2())
	{
		return SharedInfo::SetAlarm(_T("[Interlock] Check The Cst Lot Forward #2."));
	}

	if (!Devs::MaskLoaderMotion.IsTRFPos(FALSE))
	{
		return SharedInfo::SetAlarm(_T("[Interlock] Check The Cst Finger Forward."));
	}
#endif
	return TRUE;
}

BOOL Safety::AxisReadyCheck(enum_Axis eAxis)
{
	int nErrorNum = (int)eAxis;
	CString strTemp = _T("");
#if 0
	//Servo On Check.
	if (SharedInfo::GetServoOnStatus(eAxis) == FALSE)
	{
		strTemp.Format(_T("[Interlock] Check Servo On %d Motor"), nErrorNum + 1);
		return SharedInfo::SetAlarm(strTemp);
	}

	//Servo Home Check.
	if (SharedInfo::GetHomeStatus(eAxis) == FALSE)
	{
		int nErrorNum = (int)eAxis;
		CString strTemp = _T("");
		Devs::StopAll();

		strTemp.Format(_T("[Interlock] Check Home State %d Motor"), nErrorNum);
		return SharedInfo::SetAlarm(strTemp);
	}
#endif

	return TRUE;
}

BOOL Safety::CstTransferUpCheck(double dPos)
{
#if 0
	if (dPos > CManualData::Gripper.TransferZ)
	{
		if (!Devs::GantryBottomMotion.IsYZeroPos())
		{
			return SharedInfo::SetAlarm(_T("[Interlock] Check the Gantry 0 Pos"));
		}
	}
#endif
	return TRUE;
}

//Awk 2019. 01. 13
BOOL Safety::FrameBcrUpSafetyCheck()
{
#if 0
	if (!Devs::GantryTopMotion.IsFrameLoadingPosMove())
	{
		return SharedInfo::SetAlarm(_T("[Interlock] Check the Top Gantry Frame Loading Pos"));
	}

	if (!Devs::GantryBottomMotion.IsFrameLoadingPosMove())
	{
		return SharedInfo::SetAlarm(_T("[Interlock] Check the Bottom Gantry Frame Loading Pos"));
	}
#endif
	return TRUE;
}
//Awk 2019. 01. 13
BOOL Safety::FrameBcrDnSafetyCheck()
{
#if 0
	if (!SharedInfo::DInputValue[_DI_FRM_BCR_X_BACK])
	{
		return SharedInfo::SetAlarm(_T("[Interlock] Check the BCR X Cylinder"));
	}
#endif
	return TRUE;
}

//Awk 2019. 01. 13
BOOL Safety::FrameBcrExtSafetyCheck()
{
#if 0
	if (!SharedInfo::DInputValue[_DI_FRM_BCR_UP])
	{
		return SharedInfo::SetAlarm(_T("[Interlock] First Bar Cylinder Up"));
	}
#endif
	return TRUE;
}

BOOL Safety::WsYSafetyCheck(double dPosY)
{
	double dTargetPos = 0.;
	double dDist = 0.;
#if 0
	if (SharedInfo::Active.StickTop == enum_KindOfMask::eMASK_SIDE_UP || SharedInfo::Active.StickTop == enum_KindOfMask::eMASK_SIDE_DN)
		return TRUE;

	if (dPosY > 0 || fabs(dPosY) <= CModelData::Stick.Info[SharedInfo::Active.StickTop].SizeY / 2)
	{
		dTargetPos = dPosY;
		dDist = dTargetPos - SharedInfo::AxisCmdPos[REMOTE_AXIS_AJIN_BACKLIGHT_Y2];
	}
	else
	{
		dTargetPos = dPosY;
		dDist = SharedInfo::AxisCmdPos[REMOTE_AXIS_AJIN_BACKLIGHT_Y1] - dTargetPos;
	}

	if (dDist < CSystemData::m_Safety.SupportSafetyZ)
	{
		//Awk 일단 제어에서만 확인하도록.
		//return SharedInfo::SetAlarm(_T("[Interlock] Check the Welding Support(Back Light) Distance"));
	}
#endif
	return TRUE;
}

//Alarm Check.
BOOL Safety::PowerCheck()
{
#if 0
	if (!SharedInfo::DInputValue[_MAIN_POWER_ON])
	{
		return SharedInfo::SetAlarm(_T("[Interlock] Check Main Power On"));
	}

	if (!SharedInfo::DInputValue[_MAIN_POWER_1])
	{
		return SharedInfo::SetAlarm(_T("[Interlock] Check Main Power 1"));
	}

	if (!SharedInfo::DInputValue[_MAIN_POWER_2])
	{
		return SharedInfo::SetAlarm(_T("[Interlock] Check Main Power 2"));
	}

	if (!SharedInfo::DInputValue[_DC24V_MTBREAKER])
	{
		return SharedInfo::SetAlarm(_T("[Interlock] Check 24V Power Breaker"));
	}

	if (!SharedInfo::DInputValue[_GTYF_X_Z_TRIP])
	{
		return SharedInfo::SetAlarm(_T("[Interlock] Check GTYF_X_Z_TRIP"));
	}

	if (!SharedInfo::DInputValue[_GTYB_X_Z_TRIP])
	{
		return SharedInfo::SetAlarm(_T("[Interlock] Check GTYB_X_Z_TRIP"));
	}

	if (!SharedInfo::DInputValue[_GRY_L_Y1_TRIP])
	{
		return SharedInfo::SetAlarm(_T("[Interlock] Check GRY_L_Y1_TRIP"));
	}

	if (!SharedInfo::DInputValue[_GRIP_L_Y_Z_TRIP])
	{
		return SharedInfo::SetAlarm(_T("[Interlock] Check GRIP_L_Y_Z_TRIP"));
	}

	if (!SharedInfo::DInputValue[_GRIP_R_Y_Z_TRIP])
	{
		return SharedInfo::SetAlarm(_T("[Interlock] Check GRIP_R_Y_Z_TRIP"));
	}

	if (!SharedInfo::DInputValue[_GRIP_L_FL_TRIP])
	{
		return SharedInfo::SetAlarm(_T("[Interlock] Check GRIP_R_Y_Z_TRIP"));
	}

	if (!SharedInfo::DInputValue[_GRIP_L_BL_TRIP])
	{
		return SharedInfo::SetAlarm(_T("[Interlock] Check GRIP_L_BL_TRIP"));
	}

	if (!SharedInfo::DInputValue[_GRIP_R_FL_TRIP])
	{
		return SharedInfo::SetAlarm(_T("[Interlock] Check GRIP_R_FL_TRIP"));
	}

	if (!SharedInfo::DInputValue[_GRIP_R_BL_TRIP])
	{
		return SharedInfo::SetAlarm(_T("[Interlock] Check GRIP_R_BL_TRIP"));
	}

	if (!SharedInfo::DInputValue[_CTR_X_Y_F_TRIP])
	{
		return SharedInfo::SetAlarm(_T("[Interlock] Check CTR_X_Y_F_TRIP"));
	}

	if (!SharedInfo::DInputValue[_CTR_X_Y_B_TRIP])
	{
		return SharedInfo::SetAlarm(_T("[Interlock] Check CTR_X_Y_B_TRIP"));
	}

	if (!SharedInfo::DInputValue[_FRAMELIFTZ_TRIP])
	{
		return SharedInfo::SetAlarm(_T("[Interlock] Check FRAME_LIFT_Z_TRIP"));
	}

	if (!SharedInfo::DInputValue[_CF_BL_TRIP])
	{
		return SharedInfo::SetAlarm(_T("[Interlock] Check CF_BL_TRIP"));
	}

	if (!SharedInfo::DInputValue[_WELDSPT_TRIP])
	{
		return SharedInfo::SetAlarm(_T("[Interlock] Check _WELDSPT_TRIP"));
	}

	if (!SharedInfo::DInputValue[_MASKZ_ALIGN_TRIP])
	{
		return SharedInfo::SetAlarm(_T("[Interlock] Check MASKZ_ALIGN_TRIP"));
	}

	if (!SharedInfo::DInputValue[_LASER_WELDER_TRIP])
	{
		return SharedInfo::SetAlarm(_T("[Interlock] Check LASER_WELDER_TRIP"));
	}

	if (!SharedInfo::DInputValue[_AIRDRY_ISOLATOR_TRIP])
	{
		return SharedInfo::SetAlarm(_T("[Interlock] Check AIRDRY_ISOLATOR_TRIP"));
	}
#endif
	return TRUE;
}

BOOL Safety::GantryPresureCheck()
{
#if 0
	if (!SharedInfo::DInputValue[_DIN_MAIN_AIR_PRESSURE] || !SharedInfo::DInputValue[_DIN_SUPPLY_PRESSURE] ||
		!SharedInfo::DInputValue[_DIN_GANTRY_X_AXIS1_PRESSURE] || !SharedInfo::DInputValue[_DIN_GANTRY_X_AXIS2_PRESSURE] ||
		!SharedInfo::DInputValue[_DIN_GANTRY_Y_AXIS1_PRESSURE] || !SharedInfo::DInputValue[_DIN_GANTRY_Y_AXIS2_PRESSURE])
	{
		return SharedInfo::SetAlarm(_T("[Interlock] Check Gantry Pressure"));
	}

	if (!SharedInfo::DInputValue[_DIN_ISOLATOR_1_PRESSURE_ACT_H] || !SharedInfo::DInputValue[_DIN_ISOLATOR_2_PRESSURE_ACT_V])
	{
		return SharedInfo::SetAlarm(_T("[Interlock] Check Isolator Pressure"));
	}
#endif
	return TRUE;
}

BOOL Safety::BacklightCollisionCheck()
{
#if 0
	if (!SharedInfo::DInputValue[_BACK_LIGHT_LIMIT])
	{
		return SharedInfo::SetAlarm(_T("[Interlock] Check Blu Collision"));
	}
#endif
	return TRUE;
}



BOOL Safety::EmergercyCheck()
{
#if 1
	if (SharedInfo::DInputValue[_DIN_EMO_1_ON])
	{
		return SharedInfo::SetAlarm(_T("ERROR : EMO1 On !!!"), 8);
	}

	if (SharedInfo::DInputValue[_DIN_EMO_2_ON])
	{
		return SharedInfo::SetAlarm(_T("ERROR : EMO2 On !!!"), 8);
	}

	if (SharedInfo::DInputValue[_DIN_EMO_3_ON])
	{
		return SharedInfo::SetAlarm(_T("ERROR : EMO3 On !!!"), 8);
	}

	if (SharedInfo::DInputValue[_DIN_EMS_1_ON])
	{
		return SharedInfo::SetAlarm(_T("ERROR : EMS1 On !!!"), 8);
	}

	if (SharedInfo::DInputValue[_DIN_EMS_2_ON])
	{
		return SharedInfo::SetAlarm(_T("ERROR : EMS2 On !!!"), 8);
	}
#endif
	
	return TRUE;
}

BOOL Safety::TemperCheck()
{
#if 0
	if (g_CommTempTur.m_dTempValue[MAIN_TEMPERATURE_NO] < CSystemData::m_Other.Info.m_dLowTemperature || g_CommTempTur.m_dTempValue[MAIN_TEMPERATURE_NO] > CSystemData::m_Other.Info.m_dHighTemperature)
	{
		if (CSystemData::m_Other.Info.m_nUseTemperatureCheck == 1)
		{
			return SharedInfo::SetAlarm(_T("[Interlock] Temperature Check."));
		}
		else
		{
			return TRUE;
		}
	}
#endif
	return TRUE;
}

BOOL Safety::EFUCheck()
{
#if 0
	if (SharedInfo::DInputValue[_DIN_EFU1_ALARM] || SharedInfo::DInputValue[_DIN_EFU2_ALARM] ||
		SharedInfo::DInputValue[_DIN_EFU3_ALARM] || SharedInfo::DInputValue[_DIN_EFU4_ALARM] ||
		SharedInfo::DInputValue[_DIN_EFU5_ALARM] || SharedInfo::DInputValue[_DIN_EFU6_ALARM])		
	{
		return SharedInfo::SetAlarm(_T("[Interlock] Check EFU"));
	}
#endif
	return TRUE;
}

BOOL Safety::AIR_DRYERCheck()
{
#if 0
	if (SharedInfo::DInputValue[_DIN_AIR_DRYER1_ALARM] || SharedInfo::DInputValue[_DIN_AIR_DRYER2_ALARM])
	{
		return SharedInfo::SetAlarm(_T("[Interlock] Check Air Dryer"));
	}
#endif
	return TRUE;
}

BOOL Safety::VpsCheck()
{
	//Awking A접 B접 알람 신호 확인해서 정리할 것.
#if 0
	if (SharedInfo::DInputValue[_VSP_ALARM])
	{
		return SharedInfo::SetAlarm(9);
	}
#endif

	return TRUE;
}

BOOL Safety::DoorCheck()
{
	//Awking A접 B접 알람 신호 확인해서 정리할 것.
	if (SharedInfo::DInputValue[_DIN_DOOR_1_OPEN] || SharedInfo::DInputValue[_DIN_DOOR_2_OPEN] || SharedInfo::DInputValue[_DIN_DOOR_3_OPEN] || SharedInfo::DInputValue[_DIN_DOOR_4_OPEN])
	{
		if (CSystemData::m_Other.Info.m_nUseDoorOpenCheck == 1)
		{
			return SharedInfo::SetAlarm(_T("ERROR : Door Open"), 10);
		}
		else
		{
			return TRUE;
		}
	}

	return TRUE;
}