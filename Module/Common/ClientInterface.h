
#ifndef _CLIENT_INTERFACE_H_
#define _CLIENT_INTERFACE_H_

#include "SHMInterface.h"
#include "../../Module/ServerClient/ModbusData.h"

class CClientInterface
{
public:
	CClientInterface(void);
	virtual ~CClientInterface(void);	
	
	void *m_pParentDlg;
	int SetParentDlg(void *pDlg);

	int Delay(double ms);
	BOOL GetWriteCommStatus();
	BOOL GetReceiveCommStatus();



	int SendWriteCommandData(int nFuncAddr, byte* pby, int nSize);
	int SendReceiveCommandData(int nFuncAddr, byte * pby, int nSize);


	CMutex m_ClientMutex;
	CMutex m_StateClientMutex;
	CMutex m_VisionWriteClientMutex;
	CMutex m_VisionReceiveClientMutex;

	CModbusData m_ControlWriteModbusData;
	CModbusData m_ControlReceiveModbusData;
	CModbusData m_VisionWriteModbusData;
	CModbusData m_VisionReceiveModbusData;

	int m_nReceiveFlag;
	long m_nCount;

	int		m_nArgSize;

	/////////////////////////////////////////////////
	//typedef struct tag_SystemGetMaxAxisSize { int nMaxAxisSize; } st_SystemGetMaxAxisSize;
	int SystemGetMaxAxisSize(int nMaxAxisSize);
	
	//typedef struct tag_SystemGetMaxDInputSize { int nMaxDInputSize; } st_SystemGetMaxDInputSize;
	int SystemGetMaxDInputSize(int nMaxDInputSize);

	//typedef struct tag_SystemGetMaxDOutputSize { int nMaxDOutputSize; } st_SystemGetMaxDOutputSize;
	int SystemGetMaxDOutputSize(int nMaxDOutputSize);

	//typedef struct tag_SystemGetMaxAInputSize { int nMaxAInputSize; } st_SystemGetMaxAInputSize;
	int SystemGetMaxAInputSize(int nMaxAInputSize);

	//typedef struct tag_SystemGetMaxAOutputSize { int nMaxAOutputSize; } st_SystemGetMaxAOutputSize;
	int SystemGetMaxAOutputSize(int nMaxAOutputSize);

	//typedef struct tag_SystemGetHomeStatus{ int nHomeStatus; } st_SystemGetHomeStatus;
	int SystemGetHomeStatus(int nHomeStatus);
	//typedef struct tag_SystemGetHomeSignal{ int nHomeSignal; } st_SystemGetHomeSignal;
	int SystemGetHomeSignal(int nHomeSignal);
	//typedef struct tag_SystemGetLimitSignal{ int nPosSignal; int nNegSignal; } st_SystemGetLimitSignal;
	int SystemGetLimitSignal( int nPosSignal, int nNegSignal);
	//typedef struct tag_SystemSetServoOnStatus{ int nStatus; } st_SystemSetServoOnStatus;
	int SystemSetServoOnStatus(int nStatus);

	//typedef struct tag_SystemGetServoOnStatus{ int nStatus; } st_SystemGetServoOnStatus;
	int SystemGetServoOnStatus( int nStatus);
	//typedef struct tag_SystemGetAlarmStatus{ int nStatus; } st_SystemGetAlarmStatus;
	int SystemGetAlarmStatus( int nStatus);
	//typedef struct tag_SystemGetMotionDoneStatus{ int nStatus; } st_SystemGetMotionDoneStatus;
	int SystemGetMotionDoneStatus( int nStatus);

	//typedef struct tag_SystemMoveStop{ int nSystemNo; } st_SystemMoveStop;
	int SystemMoveStop(int nSystemNo);

	//typedef struct tag_AjinMoveStop{ int nSystemNo; } st_AjinMoveStop;
	int AjinMoveStop(int nSystemNo);

	//typedef struct tag_SystemGetStatus{ int nSystemNo; int nStatus; } st_SystemGetStatus; //0:HomeStatus, 1:ServoOnStatus, 2:AlarmStatus, 3:MotionDoneStatus
	int SystemGetStatus(int nSystemNo, int nStatus);

	/////////////////////////////////////////////////
	//typedef struct tag_UmacPosMove { int nAxisNo; double dPos; double dVel; double dAccel; double dDecel; int nAbsRelMode; int nBackLightMove; double dAOICamOffset; BOOL bDirBwd; int nBackLightFwdDelay; int nBackLightBwdDelay; double dBackLightFwdAccDccScale; double dBackLightBwdAccDccScale; } st_UmacPosMove; //KJT 20201113
	int UmacPosMove(int nAxisNo, double dPos, double dVel, double dAccel, double dDecel, int nAbsRelMode, int nBackLightMove = 0, double dAOICamOffset = 0.0, BOOL bDirBwd = FALSE, int nBackLightFwdDelay = 0, int nBackLightBwdDelay = 0, double dBackLightFwdAccDccScale = 1, double dBackLightBwdAccDccScale = 1); //KJT 20201113

	//typedef struct tag_UmacVelMove { int nAxisNo; double dVel; double dAccel; double dDecel; int nBackLightMove; } st_UmacVelMove; //KJT 20200929
	int UmacVelMove(int nAxisNo, double dVel, double dAccel, double dDecel, int nBackLightMove = 0); //KJT 20200929
	
	//typedef struct tag_UmacMoveStop { int nAxisNo; double dDecel; int nBackLightMove; } st_UmacMoveStop; //KJT 20200824
	int UmacMoveStop(int nAxisNo, double dDecel, int nBackLightMove = 0); //KJT 20200824
	
	//typedef struct tag_UmacHomeStart { int nAxisNo; } st_UmacHomeStart;
	int UmacHomeStart(int nAxisNo);

	//typedef struct tag_UmacSetServoOnStatus { int nAxisNo; int nServoOnStatus; } st_UmacSetServoOnStatus;
	int UmacSetServoOnStatus(int nAxisNo, int nServoOnStatus);

	//typedef struct tag_UmacSetAlarmClear { int nAxisNo; int nAlarmClear; } st_UmacSetAlarmClear;
	int UmacSetAlarmClear(int nAxisNo, int nAlarmClear);
	
	//typedef struct tag_UmacGetCmdPos{ int nAxisNo; double dPos; } st_UmacGetCmdPos;
	int UmacGetCmdPos( double dPos);
	
	//typedef struct tag_UmacGetActPos{ int nAxisNo; double dPos; } st_UmacGetActPos;
	int UmacGetActPos( double dPos);

	//typedef struct tag_UmacGetCmdVel{ int nAxisNo; double dVel; } st_UmacGetCmdVel;
	int UmacGetCmdVel(double dVel);
	
	//typedef struct tag_UmacGetHomeStatus{ int nAxisNo; int nHomeStatus; } st_UmacGetHomeStatus;
	int UmacGetHomeStatus(int nHomeStatus);

	//typedef struct tag_UmacGetHomeSignal{ int nAxisNo; int nHomeSignal; } st_UmacGetHomeSignal;
	int UmacGetHomeSignal(int nHomeSignal);	

	//typedef struct tag_UmacGetLimitSignal{ int nAxisNo; int nPosSignal; int nNegSignal; } st_UmacGetLimitSignal;
	int UmacGetLimitSignal(int nPosSignal, int nNegSignal);	

	//typedef struct tag_UmacGetServoOnStatus{ int nAxisNo; int nStatus; } st_UmacGetServoOnStatus;
	int UmacGetServoOnStatus(int nStatus);	

	//typedef struct tag_UmacGetAlarmStatus{ int nAxisNo; int nStatus; } st_UmacGetAlarmStatus;
	int UmacGetAlarmStatus(int nStatus);
	
	//typedef struct tag_UmacGetMotionDoneStatus{ int nAxisNo; int nStatus; } st_UmacGetMotionDoneStatus;
	int UmacGetMotionDoneStatus(int nStatus);
	
	//typedef struct tag_UmacGetStatus{ int nAxisNo; int nStatus; } st_UmacGetStatus; //0:HomeStatus, 1:ServoOnStatus, 2:AlarmStatus, 3:MotionDoneStatus
	int UmacGetStatus(int nStatus);

	/////////////////////////////////////////////////
	//typedef struct tag_AxisPosMove { int nAxisNo; double dPos; double dVel; double dAccel; double dDecel; int nAbsRelMode; } st_AxisPosMove;
	int AxisPosMove(int nAxisNo, double dPos, double dVel, double dAccel, double dDecel, int nAbsRelMode);
	
	//typedef struct tag_AxisVelMove { int nAxisNo; double dVel; double dAccel; double dDecel; } st_AxisVelMove;
	int AxisVelMove(int nAxisNo, double dVel, double dAccel, double dDecel);
	
	//typedef struct tag_AxisMoveStop { int nAxisNo; double dDecel; } st_AxisMoveStop;
	int AxisMoveStop(int nAxisNo, double dDecel);
	
	//typedef struct tag_AxisHomeStart { int nAxisNo; } st_AxisHomeStart;
	int AxisHomeStart(int nAxisNo);

	//typedef struct tag_AxisSignalSearch { int nAxisNo; double dVel; double dAccel; int nDetectSignal; int nSignalEdge; int nSignalMethod; } st_AxisSignalSearch;
	int AxisSignalSearch(int nAxisNo, double dVel, double dAccel, int nDetectSignal, int nSignalEdge, int nSignalMethod);

	//typedef struct tag_AxisSetServoOnStatus { int nAxisNo; int nServoOnStatus; } st_AxisSetServoOnStatus;
	int AxisSetServoOnStatus(int nAxisNo, int nServoOnStatus);

	//typedef struct tag_AxisSetAlarmClear { int nAxisNo; int nAlarmClear; } st_AxisSetAlarmClear;
	int AxisSetAlarmClear(int nAxisNo, int nAlarmClear);
	
	//typedef struct tag_AxisSetCmdPos{ int nAxisNo; double dPos; } st_AxisSetCmdPos;
	int AxisSetCmdPos(int nAxisNo, double dPos);

	//typedef struct tag_AxisGetCmdPos{ int nAxisNo; double dPos; } st_AxisGetCmdPos;
	int AxisGetCmdPos(double dPos);

	//typedef struct tag_AxisGetActPos{ int nAxisNo; double dPos; } st_AxisGetActPos;
	int AxisGetActPos(double dPos);
	
	//typedef struct tag_AxisGetCmdVel{ int nAxisNo; double dVel; } st_AxisGetCmdVel;
	int AxisGetCmdVel( double dVel);
	
	//typedef struct tag_AxisGetHomeResult{ int nAxisNo; int nHomeResult; } st_AxisGetHomeResult;
	int AxisGetHomeResult(int nHomeResult);

	//typedef struct tag_AxisGetHomeStatus{ int nAxisNo; int nHomeStatus; } st_AxisGetHomeStatus;
	int AxisGetHomeStatus(int nHomeStatus);

	//typedef struct tag_AxisGetHomeSignal{ int nAxisNo; int nHomeSignal; } st_AxisGetHomeSignal;
	int AxisGetHomeSignal(int nHomeSignal);
	
	//typedef struct tag_AxisGetLimitSignal{ int nAxisNo; int nPosSignal; int nNegSignal; } st_AxisGetLimitSignal;
	int AxisGetLimitSignal( int nPosSignal, int nNegSignal);	

	//typedef struct tag_AxisGetServoOnStatus{ int nAxisNo; int nStatus; } st_AxisGetServoOnStatus;
	int AxisGetServoOnStatus(int nStatus);
	
	//typedef struct tag_AxisGetAlarmStatus{ int nAxisNo; int nStatus; } st_AxisGetAlarmStatus;
	int AxisGetAlarmStatus(int nStatus);
	
	//typedef struct tag_AxisGetMotionDoneStatus{ int nAxisNo; int nStatus; } st_AxisGetMotionDoneStatus;
	int AxisGetMotionDoneStatus(int nStatus);	

	//typedef struct tag_AxisGetStatus{ int nAxisNo; int nStatus; } st_AxisGetStatus; //0:HomeStatus, 1:ServoOnStatus, 2:AlarmStatus, 3:MotionDoneStatus
	int AxisGetStatus(int nStatus);

	//typedef struct tag_UvwSetAxisNo { int nUvwNo; int nUvwAxisNo[3]; } st_UvwSetAxisNo;
	int UvwSetAxisNo(int nUvwNo, int nUvwAxisNo[3]);

	//typedef struct tag_UvwPosMove { int nUvwNo; double dPos[3]; double dVel[3]; double dAccel[3]; double dDecel[3]; int nAbsRelMode; } st_UvwPosMove;
	int UvwPosMove(int nUvwNo, double dPos[3], double dVel[3], double dAccel[3], double dDecel[3], int nAbsRelMode);

	//typedef struct tag_UvwZeroPosMove { int nUvwNo; double dPos[3]; double dVel[3]; double dAccel[3]; double dDecel[3]; int nAbsRelMode; } st_UvwZeroPosMove;
	int UvwZeroPosMove(int nUvwNo, double dPos[3], double dVel[3], double dAccel[3], double dDecel[3], int nAbsRelMode);

	//typedef struct tag_UvwMoveStop { int nUvwNo[3]; double dDecel[3]; } st_UvwMoveStop;
	int UvwMoveStop(int nUvwNo, double dDecel[3]);

	//typedef struct tag_UvwHomeStart { int nUvwNo; int nAxisNo; } st_UvwHomeStart;
	int UvwHomeStart(int nUvwNo, int nAxisNo);

	//typedef struct tag_UvwSetServoOnStatus { int nUvwNo; int nAxisNo; int nServoOnStatus; } st_UvwSetServoOnStatus;
	int UvwSetServoOnStatus(int nUvwNo, int nAxisNo, int nServoOnStatus);

	//typedef struct tag_UvwSetAlarmClear { int nUvwNo; int nAxisNo; int nAlarmClear; } st_UvwSetAlarmClear;
	int UvwSetAlarmClear(int nUvwNo, int nAxisNo, int nAlarmClear);

	//typedef struct tag_UvwSetCmdPos{ int nUvwNo; int nAxisNo; double dPos; } st_UvwSetCmdPos;
	int UvwSetCmdPos(int nUvwNo, int nAxisNo, double dPos);

	//typedef struct tag_UvwGetCmdPos { int nUvwNo[3]; double dPos[3]; } st_UvwGetCmdPos;
	int UvwGetCmdPos(int nUvwNo, double dPos[3]);

	//typedef struct tag_UvwGetCmdVel { int nUvwNo[3]; double dVel[3]; } st_UvwGetCmdVel;
	int UvwGetCmdVel(int nUvwNo, double dPos[3]);

	//typedef struct tag_UvwGetHomeStatus{ int nUvwNo; int nStatus; } st_UvwGetHomeStatus;
	int UvwGetHomeStatus(int nUvwNo, int nStatus);
	
	//typedef struct tag_UvwGetServoOnStatus{ int nUvwNo; int nStatus; } st_UvwGetServoOnStatus;
	int UvwGetServoOnStatus(int nUvwNo, int nStatus);

	///typedef struct tag_UvwGetAlarmStatus{ int nUvwNo; int nStatus; } st_UvwGetAlarmStatus;
	int UvwGetAlarmStatus(int nUvwNo, int nStatus);

	//typedef struct tag_UvwGetMotionDoneStatus{ int nUvwNo; int nStatus; } st_UvwGetMotionDoneStatus;
	int UvwGetMotionDoneStatus(int nUvwNo, int nStatus);

	//typedef struct tag_UvwGetStatus{ int nUvwNo; int nStatus; } st_UvwGetStatus; //0:HomeStatus, 1:ServoOnStatus, 2:AlarmStatus, 3:MotionDoneStatus
	int UvwGetStatus(int nUvwNo, int nStatus);

	//typedef struct tag_UvwXYTSetZero { int nUvwNo; } st_UvwXYTSetZero; //KJT 20200820
	int UvwXYTSetZero(int nUvwNo); //KJT 20200820

	//typedef struct tag_UvwGetTargetPos { int nUvwNo; } st_UvwGetTargetPos; //KJT 20200912
	int UvwGetTargetPos(int nUvwNo, double dPos[3]); //KJT 20200912

	//typedef struct tag_UvwTargetPosMove { int nUvwNo; double dPos[3]; } st_UvwTargetPosMove; //KJT 20201012
	int UvwTargetPosMove(int nUvwNo, double dPos[3]); //KJT 20201012
	
	//Uvwx
	/////////////////////////////////////////////////
	//typedef struct tag_UvwxSetAxisNo { int nUvwNo; int nUvwAxisNo[4]; } st_UvwxSetAxisNo;
	int UvwxSetAxisNo(int nUvwNo, int nUvwAxisNo[4]);
	//typedef struct tag_UvwxPosMove { int nUvwNo; double dPos[4]; double dVel[4]; double dAccel[4]; double dDecel[4]; int nAbsRelMode; } st_UvwxPosMove;
	int UvwxPosMove(int nUvwNo, double dPos[4], double dVel[4], double dAccel[4], double dDecel[4], int nAbsRelMode);
	//typedef struct tag_UvwxZeroPosMove { int nUvwNo; double dPos[4]; double dVel[4]; double dAccel[4]; double dDecel[4]; int nAbsRelMode; } st_UvwxPosMove;
	int UvwxZeroPosMove(int nUvwNo, double dPos[4], double dVel[4], double dAccel[4], double dDecel[4], int nAbsRelMode);
	//typedef struct tag_UvwxMoveStop { int nUvwNo; double dDecel[4]; } st_UvwxMoveStop;
	int UvwxMoveStop(int nUvwNo, double dDecel[4]);
	//typedef struct tag_UvwxHomeStart { int nUvwNo; int nAxisNo; } st_UvwxHomeStart;
	int UvwxHomeStart(int nUvwNo, int nAxisNo);
	//typedef struct tag_UvwxSetServoOnStatus { int nUvwNo; int nAxisNo; int nServoOnStatus; } st_UvwxSetServoOnStatus;
	int UvwxSetServoOnStatus(int nUvwNo, int nAxisNo, int nServoOnStatus);
	//typedef struct tag_UvwxSetAlarmClear { int nUvwNo; int nAxisNo; int nAlarmClear; } st_UvwxSetAlarmClear;
	int UvwxSetAlarmClear(int nUvwNo, int nAxisNo, int nAlarmClear);
	//typedef struct tag_UvwxSetCmdPos{ int nUvwNo; int nAxisNo; double dPos; } st_UvwxSetCmdPos;
	int UvwxSetCmdPos(int nUvwNo, int nAxisNo, double dPos);
	//typedef struct tag_UvwxGetCmdPos { int nUvwNo; double dPos[4]; } st_UvwxGetCmdPos;
	int UvwxGetCmdPos(int nUvwNo, double dPos[4]);
	//typedef struct tag_UvwxGetCmdVel { int nUvwNo; double dVel[4]; } st_UvwxGetCmdVel;
	int UvwxGetCmdVel(int nUvwNo, double dVel[4]);
	//typedef struct tag_UvwxGetHomeStatus{ int nUvwNo; int nStatus; } st_UvwxGetHomeStatus;
	int UvwxGetHomeStatus(int nUvwNo, int nStatus);
	//typedef struct tag_UvwxGetServoOnStatus{ int nUvwNo; int nStatus; } st_UvwxGetServoOnStatus;
	int UvwxGetServoOnStatus(int nUvwNo, int nStatus);
	//typedef struct tag_UvwxGetAlarmStatus{ int nUvwNo; int nStatus; } st_UvwxGetAlarmStatus;
	int UvwxGetAlarmStatus(int nUvwNo, int nStatus);
	//typedef struct tag_UvwxGetMotionDoneStatus{ int nUvwNo; int nStatus; } st_UvwxGetMotionDoneStatus;
	int UvwxGetMotionDoneStatus(int nUvwNo, int nStatus);
	//typedef struct tag_UvwxGetStatus{ int nUvwNo; int nStatus; } st_UvwxGetStatus; //0:HomeStatus, 1:ServoOnStatus, 2:AlarmStatus, 3:MotionDoneStatus
	int UvwxGetStatus(int nUvwNo, int nStatus);


	//typedef struct tag_CoordinateSetAxisMap { int nCoordNo; int nAxisSize; int nAxisNo[8]; } st_CoordinateSetAxisMap;
	int CoordinateSetAxisMap(int nCoordNo, int nAxisSize, int nAxisNo[8]);

	//typedef struct tag_CoordinatePosMove { int nCoordNo; double dPos[8]; double dVel; double dAccel; double dDecel; int nAbsRelMode; } st_CoordinatePosMove;
	int CoordinatePosMove(int nCoordNo, double dPos[8], double dVel, double dAccel, double dDecel, int nAbsRelMode);

	//typedef struct tag_CoordinateMoveStop { int nCoordNo; double dDecel; } st_CoordinateMoveStop;
	int CoordinateMoveStop(int nCoordNo, double dDecel);

	//typedef struct tag_CoordinateIsBusy { int nCoordNo; int nStatus; } st_CoordinateIsBusy;
	int CoordinateIsBusy(int nCoordNo, int nStatus);

	/////////////////////////////////////////////////
	//typedef struct tag_DInputGetBitValue { int nBit; int nValue; } st_DInputGetBitValue;
	int DInputGetBitValue(int nBit, int nValue);
	//typedef struct tag_DInputGetDWordValue { int nDWord; DWORD dwValue; } st_DInputGetDWordValue;
	int DInputGetDWordValue(DWORD dwValue);
	//typedef struct tag_DOutputGetBit { int nBit; int nValue; } st_DOutputGetBitValue;
	int DOutputGetBitValue(int nBit, int nValue);
	//typedef struct tag_DOutputGetDWordValue { int nDWord; DWORD dwValue; } st_DOutputGetDWordValue;
	int DOutputGetDWordValue(DWORD dwValue);
	//typedef struct tag_DOutputSetBit { int nBit; int nValue; } st_DOutputSetBitValue;
	int DOutputSetBitValue(int nBit, int nValue);
		
	/////////////////////////////////////////////////
	//typedef struct tag_AInputGetChannelValue { int nChannel; double dValue; } st_AInputGetChannelValue;
	int AInputGetChannelValue(double dValue);
	//typedef struct tag_AOutputGetChannelValue { int nChannel; double dValue; } st_AOutputGetChannelValue;
	int AOutputGetChannelValue(double dValue);
	//typedef struct tag_AOutputSetChannelValue { int nChannel; double dValue; } st_AOutputSetChannelValue;
	int AOutputSetChannelValue(int nChannel, double dValue);

	/////////////////////////////////////////////////
	//typedef struct tag_StretchStart { int nAxisSize;  int nAxisNo[MAX_STRETCH_AXIS_SIZE]; BOOL bReleaseFlag; } st_StretchStart;
	int ForceControlStart(int nIndex, int nAxisSize, int nAxisNo[MAX_STRETCH_AXIS_SIZE], BOOL bReleaseFlag);
	//typedef struct tag_StretchStop { int nAxisSize;  int nAxisNo[MAX_STRETCH_AXIS_SIZE]; double dDecel; } st_StretchStop;
	int ForceControlStop(int nIndex, int nAxisSize, int nAxisNo[MAX_STRETCH_AXIS_SIZE], double dDecel);
	//typedef struct tag_StretchSetPara { int nUsefulAxisNo[MAX_STRETCH_AXIS_SIZE]; int nStepCount; double dMaxSpeed; double dMinSpeed; double dOkRange; double dDecRange; } st_StretchSetPara;
	int ForceControlSetPara(int nIndex, int nUsefulAxisNo[MAX_STRETCH_AXIS_SIZE], int nStepCount, double dMaxSpeed, double dMinSpeed, double dOkRange, double dDecRange);
	//typedef struct tag_StretchSetStepValue { int nStepNo; double dStepValue[MAX_STRETCH_AXIS_SIZE]; } st_StretchSetStepValue;
	int ForceControlSetStepValue(int nIndex, int nStepNo, double dStepValue[MAX_STEP][MAX_STRETCH_SIZE]);
	//typedef struct tag_StretchGetValue { int nAxisNo;  double dCmdPos[MAX_STRETCH_AXIS_SIZE]; double dCmdVel[MAX_STRETCH_AXIS_SIZE]; double dStretchValue[MAX_STRETCH_AXIS_SIZE]; } st_StretchGetValue;
	int ForceControlGetValue(int nIndex, int nAxisNo, double dCmdPos[MAX_STRETCH_AXIS_SIZE], double dCmdVel[MAX_STRETCH_AXIS_SIZE], double dStretchValue[MAX_STRETCH_AXIS_SIZE]);
	//typedef struct tag_StretchGetStatus { int nAxisNo;  int nStatus; } st_StretchGetStatus;
	int ForceControlGetStatus(int nIndex, int nStatus[MAX_FORCE_CONTROL_SIZE]);

	int CounterForceStart(int nAxisSize, int nAxisNo[MAX_COUNTER_FORCE_AXIS_SIZE]);
	//typedef struct tag_CounterForceStop { int nAxisSize;  int nAxisNo[MAX_CounterForce_AXIS_SIZE]; double dDecel; } st_CounterForceStop;
	int CounterForceStop(int nAxisSize, int nAxisNo[MAX_COUNTER_FORCE_AXIS_SIZE], double dDecel);
	//typedef struct tag_CounterForceSetPara {int nStepCount; double dMaxSpeed; double dMinSpeed; double dOkRange; double dDecRange; } st_CounterForceSetPara;
	int CounterForceSetPara(int nStepCount, double dMaxSpeed, double dMinSpeed, double dOkRange, double dDecRange);
	//typedef struct tag_CounterForceSetStepValue { int nStepNo; double dStepValue[MAX_CounterForce_AXIS_SIZE]; } st_CounterForceSetStepValue;
	int CounterForceSetStepValue(int nStepNo, double dStepValue[MAX_COUNTER_FORCE_AXIS_SIZE]);
	//typedef struct tag_CounterForceGetValue { int nAxisNo;  double dCmdPos[MAX_CounterForce_AXIS_SIZE]; double dCmdVel[MAX_CounterForce_AXIS_SIZE]; double dCounterForceValue[MAX_CounterForce_AXIS_SIZE]; } st_CounterForceGetValue;
	int CounterForceGetValue(int nAxisNo, double dCmdPos[MAX_COUNTER_FORCE_AXIS_SIZE], double dCmdVel[MAX_COUNTER_FORCE_AXIS_SIZE], double dCounterForceValue[MAX_COUNTER_FORCE_AXIS_SIZE], double dCounterForceTargetValue[MAX_COUNTER_FORCE_AXIS_SIZE]);
	//typedef struct tag_CounterForceGetStatus { int nAxisNo;  int nStatus; } st_CounterForceGetStatus;
	int CounterForceGetStatus(int nAxisNo, int nStatus);

	//typedef struct tag_ClampStart { int nAxisNo; } st_ClampStart;
	int ClampStart(int nAxisNo);
	//typedef struct tag_UnClampStart { int nAxisNo; double dDecel; } st_UnClampStart;
	int UnClampStart(int nAxisNo, double dDecel);
	//typedef struct tag_ClampHomeStart { int nAxisNo; } st_ClampHomeStart;
	int ClampHomeStart(int nAxisNo);
	//typedef struct tag_ClampSetPara { int nUsefulAxisNo[MAX_STRETCH_AXIS_SIZE]; double dTargetValue[MAX_STRETCH_AXIS_SIZE]; } st_ClampSetPara;
	int ClampSetPara(int nUsefulAxisNo[MAX_STRETCH_AXIS_SIZE], double dTargetValue[MAX_STRETCH_AXIS_SIZE]);
	//typedef struct tag_ClampGetValue { int nAxisNo;  double dClampValue[MAX_STRETCH_AXIS_SIZE]; } st_ClampGetValue;
	int ClampGetValue(int nAxisNo, double dClampValue[MAX_STRETCH_AXIS_SIZE]);	
	//typedef struct tag_ClampGetStatus{ int nAxisNo; int nStatus; } st_ClampGetStatus;
	int ClampGetStatus(int nAxisNo, int nStatus);

#if 1
	//typedef struct tag_ClampTorqueMove { int nAxisNo; double dTorque; double dVel; int nAccFilterSel; int nGainSel; int nSpdLoopSel; } st_ClampTorqueMove;
	int ClampTorqueMove( int nAxisindex, int nStartAxisNo, double dTorque, double dVel, int nAccFilterSel, int nGainSel, int nSpdLoopSel);
	//typedef struct tag_ClampTorqueMoveStop { int nAxisNo; int nMethod; } st_ClampTorqueMoveStop;
	int ClampTorqueMoveStop(int nAxisindex, int nStartAxisNo, int nMethod);
#else
	//typedef struct tag_ClampTorqueMove { int nAxisNo; double dTorque; double dVel; int nAccFilterSel; int nGainSel; int nSpdLoopSel; } st_ClampTorqueMove;
	int ClampTorqueMove(int nAxisindex, double dTorque, double dVel, int nAccFilterSel, int nGainSel, int nSpdLoopSel);
	//typedef struct tag_ClampTorqueMoveStop { int nAxisNo; int nMethod; } st_ClampTorqueMoveStop;
	int ClampTorqueMoveStop(int nAxisindex,  int nMethod);
#endif
	
	//typedef struct tag_ClampTorqueSetRead { int nAxisNo; int nSelMon; } st_ClampTorqueSetRead;
	int ClampTorqueSetRead(int nAxisNo, int nSelMon);
	//typedef struct tag_ClampTorqueRead { int nAxisNo; double dMonitorValue; } st_ClampTorqueRead;
	int ClampTorqueRead();

	//typedef struct tag_AoiPosMove { double dPos[2]; double dVel[2]; double dAccel[2]; double dDecel[2]; int nAbsRelMode; } st_AoiPosMove;
	int AoiPosMove(double dPos[2], double dVel[2], double dAccel[2], double dDecel[2], int nAbsRelMode);
	//typedef struct tag_AoiMoveStop { double dDecel[2]; } st_AoiMoveStop;
	int AoiMoveStop(double dDecel[2]);

	//typedef struct tag_PitchHomeStart { int nAxisSize;  int nAxisNo[MAX_STRETCH_AXIS_SIZE]; } st_PitchHomeStart;
	//int PitchHomeStart(int nAxisSize, int nAxisNo[MAX_STRETCH_AXIS_SIZE]);

	//typedef struct tag_PitchMoveStop { int nAxisSize;  int nAxisNo[MAX_STRETCH_AXIS_SIZE]; double dDecel; } st_PitchMoveStop;
	//int PitchMoveStop(int nAxisSize, int nAxisNo[MAX_STRETCH_AXIS_SIZE], double dDecel);

	//typedef struct tag_PitchPosMove { int nAxisIndex;  int nAxisNo[MAX_STRETCH_AXIS_SIZE]; double dTargetPos[MAX_STRETCH_AXIS_SIZE]; double dCmdVel; } st_PitchPosMove;
	int PitchPosMove(int nAxisIndex,  int nAxisNo[MAX_STRETCH_AXIS_SIZE], double dTargetPos[MAX_STRETCH_AXIS_SIZE], double dCmdVel);

	//typedef struct tag_StretchPosMove { int nAxisIndex;  int nAxisNo[MAX_STRETCH_AXIS_SIZE]; double dTargetPos[MAX_STRETCH_AXIS_SIZE]; double dCmdVel; } st_StretchPosMove;
	int StretchPosMove(int nAxisIndex, int nAxisNo[MAX_STRETCH_AXIS_SIZE], double dTargetPos[MAX_STRETCH_AXIS_SIZE], double dCmdVel);

	//typedef struct tag_PitchGetStatus { int nAxisNo;  int nStatus; } st_PitchGetStatus;
	//int PitchGetStatus(int nAxisNo, int nStatus);

	//typedef struct tag_st_ForceData { double dCF_LoadcellForce[MAX_CF_NUM + MAX_CENTERING_NUM]; double dSF_LoadcellForce[MAX_SF_NUM]; } st_ForceData;
	int GetForceData();

	//typedef struct tag_st_StretchForceZero { int nCh; } st_StretchForceZero;
	int StretchForceZero(int nForceNo);

	//typedef struct tag_st_ForceData {  int nCh;} st_ForceData;
	int FrameForceZero(int nForceNo);
	
	int AjinGantryEnable(void *pArg);
	int AjinGantryDisable(void *pArg);

	int CenteringPosMove(double *dPos);

	int GetAllOtherAlarm();

	//typedef struct tag_st_GetLightState  { int nCameraIndex; int nLightValue[2]; bool bOnOff; bool bCtrlDone; } st_GetLightState;
	//int GetLightState(int nCameraIndex);
	


};

#endif