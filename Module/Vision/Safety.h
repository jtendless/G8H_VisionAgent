#pragma once
#include "SharedInfo.h"
#include "../Common/CommonDefine.h"


class Safety
{
public:
	Safety();
	~Safety();

	BOOL AxisAllMotionSafetyCheck(enum_Axis eAxisNum, double dPos);
	BOOL AxisAllDoSafetyCheck(enum_Do eDoNum, int nValue);
	BOOL AxisAllAoSafetyCheck(enum_Ao eAoNum, double nValue);
	BOOL GantryXMoveSafetyCheck(enum_Axis eAxis, double dPos);
	BOOL GantryYMoveSafetyCheck(enum_Axis eAxis, double dPos);
	BOOL GantryZMoveSafetyCheck(enum_Axis eAxis, double dPos);
	BOOL CassetteZMoveSafetyCheck();
	BOOL FrameBcrUpSafetyCheck();
	BOOL FrameBcrDnSafetyCheck();
	BOOL FrameBcrExtSafetyCheck();
	BOOL GripperYMoveSafetyCheck(enum_Axis eAxis, double dPos);


	BOOL GripperZMoveSafetyCheck(enum_Axis eAxis, double dPos);
	BOOL WsYSafetyCheck(double dPosY);


	BOOL GripperPitchMoveSafetyCheck(enum_Axis eAxis, double dPos);
	

	BOOL GripperStretchMoveSafetyCheck(enum_Axis eAxis, double dPos);


	BOOL CstTransferUpCheck(double dPos);

	//Alarm Check.
	BOOL AxisReadyCheck(enum_Axis eAxis);
	BOOL PowerCheck();
	BOOL GantryPresureCheck();
	BOOL BacklightCollisionCheck();
	BOOL EmergercyCheck();
	BOOL TemperCheck();
	BOOL EFUCheck();
	BOOL AIR_DRYERCheck();

	BOOL VpsCheck();

	BOOL DoorCheck();
};

