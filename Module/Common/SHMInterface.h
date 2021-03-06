
#ifndef _SHM_INTERFACE_H_
#define _SHM_INTERFACE_H_

#include "Common/CommonDefine.h"
#include "Motion/MotionAgentDefine.h" //KJT 20200812

//SystemStatus : 0:HomeStatus, 1:ServoOnStatus, 2:AlarmStatus, 3:MotionDoneStatus

//System
typedef struct tag_SystemGetMaxAxisSize { int nMaxAxisSize; } st_SystemGetMaxAxisSize;
typedef struct tag_SystemGetMaxDInputSize { int nMaxDInputSize; } st_SystemGetMaxDInputSize;
typedef struct tag_SystemGetMaxDOutputSize { int nMaxDOutputSize; } st_SystemGetMaxDOutputSize;
typedef struct tag_SystemGetMaxAInputSize { int nMaxAInputSize; } st_SystemGetMaxAInputSize;
typedef struct tag_SystemGetMaxAOutputSize { int nMaxAOutputSize; } st_SystemGetMaxAOutputSize;

typedef struct tag_SystemGetHomeStatus{ int nHomeStatus; } st_SystemGetHomeStatus;
typedef struct tag_SystemGetHomeSignal{ int nHomeSignal; } st_SystemGetHomeSignal;
typedef struct tag_SystemGetLimitSignal{ int nPosSignal; int nNegSignal; } st_SystemGetLimitSignal;
typedef struct tag_SystemSetServoOnStatus { int nStatus; } st_SystemSetServoOnStatus;
typedef struct tag_SystemGetServoOnStatus{ int nStatus; } st_SystemGetServoOnStatus;
typedef struct tag_SystemGetAlarmStatus{ int nStatus; } st_SystemGetAlarmStatus;
typedef struct tag_SystemGetMotionDoneStatus{ int nStatus; } st_SystemGetMotionDoneStatus;

typedef struct tag_SystemMoveStop{ int nSystemNo; } st_SystemMoveStop;
typedef struct tag_AjinMoveStop { int nSystemNo; } st_AjinMoveStop;
typedef struct tag_SystemGetStatus{ int nSystemNo; int nStatus; } st_SystemGetStatus; //0:HomeStatus, 1:ServoOnStatus, 2:AlarmStatus, 3:MotionDoneStatus

//Umac
typedef struct tag_UmacPosMove { int nAxisNo; double dPos; double dVel; double dAccel; double dDecel; int nAbsRelMode; int nBackLightMove; double dAOICamOffset; BOOL bDirBwd; int nBackLightFwdDelay; int nBackLightBwdDelay; double dBackLightFwdAccDccScale; double dBackLightBwdAccDccScale;  } st_UmacPosMove; //KJT 20201113
typedef struct tag_UmacVelMove { int nAxisNo; double dVel; double dAccel; double dDecel; int nBackLightMove; } st_UmacVelMove; //KJT 20200929
typedef struct tag_UmacMoveStop { int nAxisNo; double dDecel; int nBackLightMove; } st_UmacMoveStop; //KJT 20200824
typedef struct tag_UmacHomeStart { int nAxisNo; } st_UmacHomeStart;
typedef struct tag_UmacSetServoOnStatus { int nAxisNo; int nServoOnStatus; } st_UmacSetServoOnStatus;
typedef struct tag_UmacSetAlarmClear { int nAxisNo; int nAlarmClear; } st_UmacSetAlarmClear;
typedef struct tag_UmacGetCmdPos{double dPos[MAX_UMAC_AXIS_SIZE]; } st_UmacGetCmdPos;
typedef struct tag_UmacGetActPos{double dPos[MAX_UMAC_AXIS_SIZE]; } st_UmacGetActPos;
typedef struct tag_UmacGetCmdVel{double dVel[MAX_UMAC_AXIS_SIZE]; } st_UmacGetCmdVel;
typedef struct tag_UmacGetHomeStatus{ int nHomeStatus[MAX_UMAC_AXIS_SIZE]; } st_UmacGetHomeStatus;
typedef struct tag_UmacGetHomeSignal{int nHomeSignal[MAX_UMAC_AXIS_SIZE]; } st_UmacGetHomeSignal;
typedef struct tag_UmacGetLimitSignal{  int nPosSignal[MAX_UMAC_AXIS_SIZE]; int nNegSignal[MAX_UMAC_AXIS_SIZE]; } st_UmacGetLimitSignal;
typedef struct tag_UmacGetServoOnStatus{int nStatus[MAX_UMAC_AXIS_SIZE]; } st_UmacGetServoOnStatus;
typedef struct tag_UmacGetAlarmStatus{int nStatus[MAX_UMAC_AXIS_SIZE]; } st_UmacGetAlarmStatus;
typedef struct tag_UmacGetMotionDoneStatus{int nStatus[MAX_UMAC_AXIS_SIZE]; } st_UmacGetMotionDoneStatus;

typedef struct tag_UmacGetStatus{int nStatus[MAX_UMAC_AXIS_SIZE]; } st_UmacGetStatus; //0:HomeStatus, 1:ServoOnStatus, 2:AlarmStatus, 3:MotionDoneStatus

//Ajin
typedef struct tag_AxisTotalSetServoOnStatus { int nStatus; } st_AxisTotalSetServoOnStatus;
typedef struct tag_AxisTotalGetServoOnStatus { int nStatus; } st_AxisTotalGetServoOnStatus;
typedef struct tag_AxisPosMove { int nAxisNo; double dPos; double dVel; double dAccel; double dDecel; int nAbsRelMode; } st_AxisPosMove;
typedef struct tag_AxisVelMove { int nAxisNo; double dVel; double dAccel; double dDecel; } st_AxisVelMove;
typedef struct tag_AxisMoveStop { int nAxisNo; double dDecel; } st_AxisMoveStop;
typedef struct tag_AxisHomeStart { int nAxisNo; } st_AxisHomeStart;
typedef struct tag_AxisSignalSearch { int nAxisNo; double dVel; double dAccel; int nDetectSignal; int nSignalEdge; int nSignalMethod; } st_AxisSignalSearch;
typedef struct tag_AxisSetServoOnStatus { int nAxisNo; int nServoOnStatus; } st_AxisSetServoOnStatus;
typedef struct tag_AxisSetAlarmClear { int nAxisNo; int nAlarmClear; } st_AxisSetAlarmClear;
typedef struct tag_AxisSetCmdPos{ int nAxisNo; double dPos; } st_AxisSetCmdPos;
typedef struct tag_AxisGetCmdPos{double dPos[MAX_AXIS_SIZE]; } st_AxisGetCmdPos;
typedef struct tag_AxisGetActPos{double dPos[MAX_AXIS_SIZE]; } st_AxisGetActPos;
typedef struct tag_AxisGetCmdVel{double dVel[MAX_AXIS_SIZE]; } st_AxisGetCmdVel;
typedef struct tag_AxisGetHomeResult {int nHomeResult[MAX_AXIS_SIZE]; } st_AxisGetHomeResult;
typedef struct tag_AxisGetHomeStatus{int nHomeStatus[MAX_AXIS_SIZE]; } st_AxisGetHomeStatus;
typedef struct tag_AxisGetHomeSignal{int nHomeSignal[MAX_AXIS_SIZE]; } st_AxisGetHomeSignal;
typedef struct tag_AxisGetLimitSignal{int nPosSignal[MAX_AXIS_SIZE]; int nNegSignal[MAX_AXIS_SIZE]; } st_AxisGetLimitSignal;
typedef struct tag_AxisGetServoOnStatus{int nStatus[MAX_AXIS_SIZE]; } st_AxisGetServoOnStatus;
typedef struct tag_AxisGetAlarmStatus{int nStatus[MAX_AXIS_SIZE]; } st_AxisGetAlarmStatus;
typedef struct tag_AxisGetMotionDoneStatus{int nStatus[MAX_AXIS_SIZE]; } st_AxisGetMotionDoneStatus;
typedef struct tag_AxisGetStatus{int nStatus[MAX_AXIS_SIZE]; } st_AxisGetStatus; //0:HomeStatus, 1:ServoOnStatus, 2:AlarmStatus, 3:MotionDoneStatus

typedef struct tag_AxisMoveAllStop { double Data[2]; } st_AxisMoveAllStop;
//Uvw
typedef struct tag_UvwSetAxisNo { int nUvwNo; int nUvwAxisNo[3]; } st_UvwSetAxisNo;
typedef struct tag_UvwPosMove { int nUvwNo; double dPos[3]; double dVel[3]; double dAccel[3]; double dDecel[3]; int nAbsRelMode; } st_UvwPosMove;
typedef struct tag_UvwMoveStop { int nUvwNo; double dDecel[3]; } st_UvwMoveStop;
typedef struct tag_UvwHomeStart { int nUvwNo; int nAxisNo; } st_UvwHomeStart;
typedef struct tag_UvwSetServoOnStatus { int nUvwNo; int nAxisNo; int nServoOnStatus; } st_UvwSetServoOnStatus;
typedef struct tag_UvwSetAlarmClear { int nUvwNo; int nAxisNo; int nAlarmClear; } st_UvwSetAlarmClear;
typedef struct tag_UvwSetCmdPos{ int nUvwNo; int nAxisNo; double dPos; } st_UvwSetCmdPos;
typedef struct tag_UvwGetCmdPos { int nUvwNo; double dPos[3]; } st_UvwGetCmdPos;
typedef struct tag_UvwGetCmdVel { int nUvwNo; double dVel[3]; } st_UvwGetCmdVel;
typedef struct tag_UvwGetHomeStatus{ int nUvwNo; int nStatus; } st_UvwGetHomeStatus;
typedef struct tag_UvwGetServoOnStatus{ int nUvwNo; int nStatus; } st_UvwGetServoOnStatus;
typedef struct tag_UvwGetAlarmStatus{ int nUvwNo; int nStatus; } st_UvwGetAlarmStatus;
typedef struct tag_UvwGetMotionDoneStatus{ int nUvwNo; int nStatus; } st_UvwGetMotionDoneStatus;
typedef struct tag_UvwGetStatus{ int nUvwNo; int nStatus; } st_UvwGetStatus; //0:HomeStatus, 1:ServoOnStatus, 2:AlarmStatus, 3:MotionDoneStatus
typedef struct tag_UvwXYTSetZero { int nUvwNo; } st_UvwXYTSetZero; //KJT 20200820
typedef struct tag_UvwGetTargetPos { int nUvwNo; double dPos[3]; } st_UvwGetTargetPos; //KJT 20200912
typedef struct tag_UvwTargetPosMove { int nUvwNo; double dPos[3]; } st_UvwTargetPosMove; //KJT 20201012

//Uvwx
typedef struct tag_UvwxSetAxisNo { int nUvwNo; int nUvwAxisNo[4]; } st_UvwxSetAxisNo;
typedef struct tag_UvwxPosMove { int nUvwNo; double dPos[4]; double dVel[4]; double dAccel[4]; double dDecel[4]; int nAbsRelMode; } st_UvwxPosMove;
typedef struct tag_UvwxMoveStop { int nUvwNo; double dDecel[4]; } st_UvwxMoveStop;
typedef struct tag_UvwxHomeStart { int nUvwNo; int nAxisNo; } st_UvwxHomeStart;
typedef struct tag_UvwxSetServoOnStatus { int nUvwNo; int nAxisNo; int nServoOnStatus; } st_UvwxSetServoOnStatus;
typedef struct tag_UvwxSetAlarmClear { int nUvwNo; int nAxisNo; int nAlarmClear; } st_UvwxSetAlarmClear;
typedef struct tag_UvwxSetCmdPos{ int nUvwNo; int nAxisNo; double dPos; } st_UvwxSetCmdPos;
typedef struct tag_UvwxGetCmdPos { int nUvwNo; double dPos[4]; } st_UvwxGetCmdPos;
typedef struct tag_UvwxGetCmdVel { int nUvwNo; double dVel[4]; } st_UvwxGetCmdVel;
typedef struct tag_UvwxGetHomeStatus{ int nUvwNo; int nStatus; } st_UvwxGetHomeStatus;
typedef struct tag_UvwxGetServoOnStatus{ int nUvwNo; int nStatus; } st_UvwxGetServoOnStatus;
typedef struct tag_UvwxGetAlarmStatus{ int nUvwNo; int nStatus; } st_UvwxGetAlarmStatus;
typedef struct tag_UvwxGetMotionDoneStatus{ int nUvwNo; int nStatus; } st_UvwxGetMotionDoneStatus;
typedef struct tag_UvwxGetStatus{ int nUvwNo; int nStatus; } st_UvwxGetStatus; //0:HomeStatus, 1:ServoOnStatus, 2:AlarmStatus, 3:MotionDoneStatus


//Dio
typedef struct tag_DInputGetBitValue { int nBit; int nValue; } st_DInputGetBitValue;
typedef struct tag_DInputGetDWordValue { int dwValue[MAX_DINPUT_SIZE]; } st_DInputGetDWordValue;
typedef struct tag_DOutputGetBitValue { int nBit; int nValue; } st_DOutputGetBitValue;
typedef struct tag_DOutputGetDWordValue { int dwValue[MAX_DOUTPUT_SIZE]; } st_DOutputGetDWordValue;
typedef struct tag_DOutputSetBitValue { int nBit; int nValue; } st_DOutputSetBitValue;

//Aio
typedef struct tag_AInputGetChannelValue { double dValue[MAX_AINPUT_SIZE]; } st_AInputGetChannelValue;
typedef struct tag_AOutputGetChannelValue { double dValue[MAX_AOUTPUT_SIZE]; } st_AOutputGetChannelValue;
typedef struct tag_AOutputSetChannelValue { int nChannel; double dValue; } st_AOutputSetChannelValue;

//ForceControl
typedef struct tag_ForceControlStart { int nIndex; int nAxisSize;  int nAxisNo[MAX_FORCE_CONTROL_SIZE]; BOOL bReleaseFlag; } st_ForceControlStart;
typedef struct tag_ForceControlStop { int nIndex; int nAxisSize;  int nAxisNo[MAX_FORCE_CONTROL_SIZE]; double dDecel; } st_ForceControlStop;
typedef struct tag_ForceControlSetPara { int nIndex; int nUsefulAxisNo[MAX_FORCE_CONTROL_SIZE]; int nStepCount; double dMaxSpeed; double dMinSpeed; double dOkRange; double dDecRange; } st_ForceControlSetPara;
typedef struct tag_ForceControlSetStepValue { int nIndex; int nStepNo; double dStepValue[MAX_STEP][MAX_FORCE_CONTROL_SIZE]; } st_ForceControlSetStepValue;
typedef struct tag_ForceControlGetValue { int nIndex; int nAxisNo;  double dCmdPos[MAX_FORCE_CONTROL_SIZE]; double dCmdVel[MAX_FORCE_CONTROL_SIZE]; double dForceControlValue[MAX_FORCE_CONTROL_SIZE]; } st_ForceControlGetValue;
//typedef struct tag_ForceControlGetStatus { int nIndex; int nAxisNo[MAX_FORCE_CONTROL_SIZE];  int nStatus[MAX_FORCE_CONTROL_SIZE]; } st_ForceControlGetStatus;
typedef struct tag_ForceControlGetStatus { int nIndex; int nStatus[MAX_FORCE_CONTROL_SIZE]; } st_ForceControlGetStatus;

//Clamp
typedef struct tag_ClampStart { int nAxisNo; } st_ClampStart;
typedef struct tag_UnClampStart { int nAxisNo; double dDecel; } st_UnClampStart;
typedef struct tag_ClampHomeStart { int nAxisNo; } st_ClampHomeStart;
typedef struct tag_ClampSetPara { int nUsefulAxisNo[MAX_STRETCH_AXIS_SIZE]; double dTargetValue[MAX_STRETCH_AXIS_SIZE]; } st_ClampSetPara;
typedef struct tag_ClampGetValue { int nAxisNo;  double dClampValue[MAX_STRETCH_AXIS_SIZE]; } st_ClampGetValue;
typedef struct tag_ClampGetStatus{ int nAxisNo; int nStatus; } st_ClampGetStatus;


//Clamp Torque
typedef struct tag_ClampTorqueMove { int nAxisindex; int nStartAxisNo; double dTorque; double dVel; int nAccFilterSel; int nGainSel; int nSpdLoopSel; } st_ClampTorqueMove;
typedef struct tag_ClampTorqueMoveStop { int nAxisindex; int nStartAxisNo; int nMethod; } st_ClampTorqueMoveStop;
typedef struct tag_ClampTorqueSetRead { int nAxisNo; int nSelMon; } st_ClampTorqueSetRead;
typedef struct tag_ClampTorqueRead { double dMonitorValue[MAX_STRETCH_AXIS_SIZE]; } st_ClampTorqueRead;


//AOI
typedef struct tag_AoiPosMove { double dPos[2]; double dVel[2]; double dAccel[2]; double dDecel[2]; int nAbsRelMode; } st_AoiPosMove;
typedef struct tag_AoiMoveStop { double dDecel[2]; } st_AoiMoveStop;


//Loadcell Indigator.
typedef struct tag_st_ForceData { double dCF_LoadcellForce[MAX_CF_NUM]; double dSF_LoadcellForce[MAX_SF_NUM]; } st_ForceData;
typedef struct tag_st_StretchForceZero { int nCh; } st_StretchForceZero;
typedef struct tag_st_FrameForceZero { int nCh; } st_FrameForceZero;

//AxisMap
typedef struct tag_CoordinateSetAxisMap { int nCoordNo; int nAxisSize; int nAxisNo[8]; } st_CoordinateSetAxisMap;
typedef struct tag_CoordinatePosMove { int nCoordNo; double dPos[8]; double dVel; double dAccel; double dDecel; int nAbsRelMode; } st_CoordinatePosMove;
typedef struct tag_CoordinateMoveStop { int nCoordNo; double dDecel; } st_CoordinateMoveStop;
typedef struct tag_CoordinateIsBusy { int nCoordNo; int nStatus; } st_CoordinateIsBusy;

typedef struct tag_AjinGantryEnable { long lMasterAxisNo; long lSlaveAxisNo; DWORD uSlHomeUse; double dSlOffset; double dSlOffsetRange; } st_AjinGantryEnable;
typedef struct tag_AjinGantryDisable { long lMasterAxisNo; long lSlaveAxisNo; } st_AjinGantryDisable;

typedef struct tag_CenteringPosMove { double dX; double dY; double dT; } st_CenteringPosMove;

typedef struct tag_OtherAlarm { int Alarm[10]; } st_OtherAlarm;
//Awk
//Vision
//????.
//typedef struct tag_st_VisionFind { int nCameraIndex; int nOption;  double dMarkPixelSize[2]; int nBright[2]; int nBin; int nType; } st_VisionFind;
//typedef struct tag_st_VisionReturnData { int nCameraIndex; double dMarkPixelPos[2]; double dMarkCD[2]; int nScore;  bool bResult; } st_VisionReturnData;
//Vision--------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct tag_st_VisionFind { int nCameraIndex; int nOption;  double dMarkPixelSize[2]; int nBin; int nType; } st_VisionFind;
typedef struct tag_st_VisionReturn { int nCameraIndex; double dMarkPixelPos[2]; double dMarkCD[2]; double dScore; double dScale; bool bResult; } st_VisionReturn;

//Light ----------------------------------------------------------------------------------------------------------------------------------------------------------
typedef struct tag_st_SetLight { int nCameraIndex; int nBright[2]; } st_SetLight;
typedef struct tag_st_LightOn { int nCameraIndex; bool nOnOff; } st_LightOn;

typedef struct tag_PitchPosMove { int nAxisIndex;  int nAxisNo[MAX_STRETCH_AXIS_SIZE]; double dTargetPos[MAX_STRETCH_AXIS_SIZE]; double dCmdVel; } st_PitchPosMove;

typedef struct tag_StretchPosMove { int nAxisIndex;  int nAxisNo[MAX_STRETCH_AXIS_SIZE]; double dTargetPos[MAX_STRETCH_AXIS_SIZE]; double dCmdVel; } st_StretchPosMove;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef enum{
	UNKNOWN_SHM_FUNCTION = 0,

	SystemGetMaxAxisSize_Func,
	SystemGetMaxDInputSize_Func,
	SystemGetMaxDOutputSize_Func,
	SystemGetMaxAInputSize_Func,
	SystemGetMaxAOutputSize_Func,

	SystemGetHomeStatus_Func,
	SystemGetHomeSignal_Func,
	SystemGetLimitSignal_Func,
	SystemSetServoOnStatus_Func,
	SystemGetServoOnStatus_Func,
	SystemGetAlarmStatus_Func,
	SystemGetMotionDoneStatus_Func,

	SystemMoveStop_Func,
	SystemGetStatus_Func,

	UmacPosMove_Func,
	UmacVelMove_Func,
	UmacMoveStop_Func,
	UmacHomeStart_Func,
	UmacSetServoOnStatus_Func,
	UmacSetAlarmClear_Func,
	UmacGetCmdPos_Func,
	UmacGetActPos_Func,
	UmacGetCmdVel_Func,
	UmacGetHomeStatus_Func,
	UmacGetHomeSignal_Func,
	UmacGetLimitSignal_Func,
	UmacGetServoOnStatus_Func,
	UmacGetAlarmStatus_Func,
	UmacGetMotionDoneStatus_Func,
	UmacGetStatus_Func,

	AxisTotalSetServoOnStatus_Func,
	AxisTotalGetServoOnStatus_Func,
	AxisPosMove_Func,
	AxisVelMove_Func,
	AxisMoveStop_Func,
	AxisMoveAllStop_Func,

	AxisHomeStart_Func,
	AxisSignalSearch_Func,
	AxisSetServoOnStatus_Func,
	AxisSetAlarmClear_Func,
	AxisSetCmdPos_Func,
	AxisGetCmdPos_Func,

	AxisGetActPos_Func,
	AxisGetCmdVel_Func,
	AxisGetHomeResult_Func,
	AxisGetHomeStatus_Func,
	AxisGetHomeSignal_Func,
	AxisGetLimitSignal_Func,
	AxisGetServoOnStatus_Func,
	AxisGetAlarmStatus_Func,
	AxisGetMotionDoneStatus_Func,
	AxisGetStatus_Func,

	UvwSetAxisNo_Func,
	UvwPosMove_Func,
	UvwMoveStop_Func,
	UvwHomeStart_Func,
	UvwSetServoOnStatus_Func,
	UvwSetAlarmClear_Func,
	UvwSetCmdPos_Func,
	UvwGetCmdPos_Func,
	UvwGetCmdVel_Func,
	UvwGetHomeStatus_Func,
	UvwGetServoOnStatus_Func,
	UvwGetAlarmStatus_Func,
	UvwGetMotionDoneStatus_Func,
	UvwGetStatus_Func,
	UvwXYTSetZero_Func, //KJT 20200820
	UvwGetTargetPos_Func, //KJT 20200912
	UvwTargetPosMove_Func, //KJT 20201012

	UvwxSetAxisNo_Func,
	UvwxPosMove_Func,
	UvwxMoveStop_Func,
	UvwxHomeStart_Func,
	UvwxSetServoOnStatus_Func,
	UvwxSetAlarmClear_Func,
	UvwxSetCmdPos_Func,
	UvwxGetCmdPos_Func,
	UvwxGetCmdVel_Func,
	UvwxGetHomeStatus_Func,
	UvwxGetServoOnStatus_Func,
	UvwxGetAlarmStatus_Func,
	UvwxGetMotionDoneStatus_Func,
	UvwxGetStatus_Func,

	DInputGetBitValue_Func,
	DInputGetDWordValue_Func,
	DOutputGetBitValue_Func,
	DOutputGetDWordValue_Func,
	DOutputSetBitValue_Func,

	AInputGetChannelValue_Func,
	AOutputGetChannelValue_Func,
	AOutputSetChannelValue_Func,

	ForceControlStart_Func,
	ForceControlStop_Func,
	ForceControlSetPara_Func,
	ForceControlSetStepValue_Func,
	ForceControlGetValue_Func,
	ForceControlGetStatus_Func,

	ClampStart_Func,
	UnClampStart_Func,
	ClampHomeStart_Func,
	ClampSetPara_Func,
	ClampGetValue_Func,	
	ClampGetStatus_Func,
	
	ClampTorqueMove_Func,
	ClampTorqueMoveStop_Func,
	ClampTorqueSetRead_Func,
	ClampTorqueRead_Func,

	PitchPosMove_Func, //20201111
	StretchPosMove_Func, //20201111

	AjinMoveStop_Func,

	AoiPosMove_Func,
	AoiMoveStop_Func,

	

	GetForceData_Func = 302,
	StretchForceZero_Func,
	FrameForceZero_Func,

	CoordinateSetAxisMap_Func = 305,
	CoordinatePosMove_Func,
	CoordinateMoveStop_Func,
	CoordinateIsBusy_Func,

	AjinGantryEnable_Func,
	AjinGantryDisable_Func,
	
	CenteringPosMove_Func,

	GetOtherAlarm_Func,
	MotionFinish_Func = 498,

	VisionFind_Func = 500,
	VisionReturn_Func,
	SetLight_Func,
	LightOn_Func,

	MAX_SHM_FUNCTION
}ShmFuncID;

typedef union{

	st_SystemGetMaxAxisSize		SystemGetMaxAxisSize_Arg;
	st_SystemGetMaxDInputSize		SystemGetMaxDInputSize_Arg;
	st_SystemGetMaxDOutputSize		SystemGetMaxDOutputSize_Arg;
	st_SystemGetMaxAInputSize		SystemGetMaxAInputSize_Arg;
	st_SystemGetMaxAOutputSize		SystemGetMaxAOutputSize_Arg;

	st_SystemGetHomeStatus			SystemGetHomeStatus_Arg;
	st_SystemGetHomeSignal			SystemGetHomeSignal_Arg;
	st_SystemGetLimitSignal			SystemGetLimitSignal_Arg;
	st_SystemSetServoOnStatus		SystemSetServoOnStatus_Arg;
	st_SystemGetServoOnStatus		SystemGetServoOnStatus_Arg;
	st_SystemGetAlarmStatus			SystemGetAlarmStatus_Arg;
	st_SystemGetMotionDoneStatus	SystemGetMotionDoneStatus_Arg;

	st_SystemMoveStop				SystemMoveStop_Arg;
	st_AjinMoveStop					AjinMoveStop_Arg;
	st_SystemGetStatus				SystemGetStatus_Arg;

	st_UmacPosMove					UmacPosMove_Arg;
	st_UmacVelMove					UmacVelMove_Arg;
	st_UmacMoveStop					UmacMoveStop_Arg;
	st_UmacHomeStart				UmacHomeStart_Arg;
	st_UmacSetServoOnStatus			UmacSetServoOnStatus_Arg;
	st_UmacSetAlarmClear			UmacSetAlarmClear_Arg;
	st_UmacGetCmdPos				UmacGetCmdPos_Arg;
	st_UmacGetActPos				UmacGetActPos_Arg;
	st_UmacGetCmdVel				UmacGetCmdVel_Arg;
	st_UmacGetHomeStatus			UmacGetHomeStatus_Arg;
	st_UmacGetHomeSignal			UmacGetHomeSignal_Arg;
	st_UmacGetLimitSignal			UmacGetLimitSignal_Arg;
	st_UmacGetServoOnStatus			UmacGetServoOnStatus_Arg;
	st_UmacGetAlarmStatus			UmacGetAlarmStatus_Arg;
	st_UmacGetMotionDoneStatus		UmacGetMotionDoneStatus_Arg;
	st_UmacGetStatus				UmacGetStatus_Arg;

	st_AxisTotalSetServoOnStatus		AxisTotalSetServoOnStatus_Arg;
	st_AxisTotalGetServoOnStatus		AxisTotalGetServoOnStatus_Arg;
	st_AxisPosMove				AxisPosMove_Arg;
	st_AxisVelMove				AxisVelMove_Arg;
	st_AxisMoveStop				AxisMoveStop_Arg;
	st_AxisHomeStart				AxisHomeStart_Arg;
	st_AxisSignalSearch			AxisSignalSearch_Arg;
	st_AxisSetServoOnStatus		AxisSetServoOnStatus_Arg;
	st_AxisSetAlarmClear			AxisSetAlarmClear_Arg;
	st_AxisSetCmdPos				AxisSetCmdPos_Arg;
	st_AxisGetCmdPos				AxisGetCmdPos_Arg;
	st_AxisGetActPos				AxisGetActPos_Arg;
	st_AxisGetCmdVel				AxisGetCmdVel_Arg;
	st_AxisGetHomeResult			AxisGetHomeResult_Arg;
	st_AxisGetHomeStatus			AxisGetHomeStatus_Arg;
	st_AxisGetHomeSignal			AxisGetHomeSignal_Arg;
	st_AxisGetLimitSignal			AxisGetLimitSignal_Arg;
	st_AxisGetServoOnStatus		AxisGetServoOnStatus_Arg;
	st_AxisGetAlarmStatus			AxisGetAlarmStatus_Arg;
	st_AxisGetMotionDoneStatus		AxisGetMotionDoneStatus_Arg;
	st_AxisGetStatus				AxisGetStatus_Arg;

	st_UvwSetAxisNo				UvwSetAxisNo_Arg;
	st_UvwPosMove					UvwPosMove_Arg;
	st_UvwMoveStop				UvwMoveStop_Arg;
	st_UvwHomeStart				UvwHomeStart_Arg;
	st_UvwSetServoOnStatus			UvwSetServoOnStatus_Arg;
	st_UvwSetAlarmClear			UvwSetAlarmClear_Arg;
	st_UvwSetCmdPos				UvwSetCmdPos_Arg;
	st_UvwGetCmdPos				UvwGetCmdPos_Arg;
	st_UvwGetCmdVel				UvwGetCmdVel_Arg;
	st_UvwGetHomeStatus			UvwGetHomeStatus_Arg;
	st_UvwGetServoOnStatus			UvwGetServoOnStatus_Arg;
	st_UvwGetAlarmStatus			UvwGetAlarmStatus_Arg;
	st_UvwGetMotionDoneStatus		UvwGetMotionDoneStatus_Arg;
	st_UvwGetStatus				UvwGetStatus_Arg;


	st_UvwxSetAxisNo				st_UvwxSetAxisNo_Arg;
	st_UvwxPosMove				st_UvwxPosMove_Arg;
	st_UvwxMoveStop				st_UvwxMoveStop_Arg;
	st_UvwxHomeStart				st_UvwxHomeStart_Arg;
	st_UvwxSetServoOnStatus		st_UvwxSetServoOnStatus_Arg;
	st_UvwxSetAlarmClear			st_UvwxSetAlarmClear_Arg;
	st_UvwxSetCmdPos				st_UvwxSetCmdPos_Arg;
	st_UvwxGetCmdPos				st_UvwxGetCmdPos_Arg;
	st_UvwxGetCmdVel				st_UvwxGetCmdVel_Arg;
	st_UvwxGetHomeStatus			st_UvwxGetHomeStatus_Arg;
	st_UvwxGetServoOnStatus		st_UvwxGetServoOnStatus_Arg;
	st_UvwxGetAlarmStatus			st_UvwxGetAlarmStatus_Arg;
	st_UvwxGetMotionDoneStatus		st_UvwxGetMotionDoneStatus_Arg;
	st_UvwxGetStatus				st_UvwxGetStatus_Arg;

	st_DInputGetBitValue			DInputGetBitValue_Arg;
	st_DInputGetDWordValue			DInputGetDWordValue_Arg;
	st_DOutputGetBitValue			DOutputGetBitValue_Arg;
	st_DOutputGetDWordValue		DOutputGetDWordValue_Arg;
	st_DOutputSetBitValue			DOutputSetBitValue_Arg;

	st_AInputGetChannelValue		AInputGetValue_Arg;
	st_AOutputGetChannelValue		AOutputGetValue_Arg;
	st_AOutputSetChannelValue		AOutputSetValue_Arg;

	st_ForceControlStart			ForceControlStart_Arg;
	st_ForceControlStop			ForceControlSop_Arg;
	st_ForceControlSetPara			ForceControlSetPara_Arg;
	st_ForceControlSetStepValue    ForceControlSetStepValue_Arg;
	st_ForceControlGetValue		ForceControlGetValue_Arg;
	st_ForceControlGetStatus		ForceControlGetStatus_Arg;

	st_ClampStart					ClampStart_Arg;
	st_UnClampStart				UnClampStart_Arg;
	st_ClampHomeStart				ClampHomeStart_Arg;
	st_ClampSetPara				ClampSetPara_Arg;
	st_ClampGetValue				ClampGetValue_Arg;	
	st_ClampGetStatus				ClampGetStatus_Arg;

	st_ClampTorqueMove				ClampTorqueMove_Arg;
	st_ClampTorqueMoveStop			ClampTorqueMoveStop_Arg;
	st_ClampTorqueSetRead			ClampTorqueSetRead_Arg;
	st_ClampTorqueRead				ClampTorqueRead_Arg;

	st_AoiPosMove					AoiPosMove_Arg;
	st_AoiMoveStop				AoiMoveStop_Arg;

	st_AxisMoveAllStop				AxisMoveAllStop_Arg;

	st_ForceData					ForceData_Arg;
	st_StretchForceZero			StretchForceZero_Arg;
	st_FrameForceZero				FrameForceZero_Arg;

	st_CoordinateSetAxisMap		CoordinateSetAxisMap_Arg;
	st_CoordinatePosMove			CoordinatePosMove_Arg;
	st_CoordinateMoveStop			CoordinateMoveStop_Arg;
	st_CoordinateIsBusy			CoordinateIsBusy_Arg;

	st_AjinGantryEnable           AjinGantryEnable_Arg;
	st_AjinGantryDisable          AjinGantryDisable_Arg;

	st_CenteringPosMove			CenteringPosMove_Arg;
	
}ShmCommandArg;

#endif

