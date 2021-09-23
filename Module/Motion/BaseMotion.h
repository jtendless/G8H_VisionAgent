#pragma once
#include "Vision/Safety.h"
#include "Dll/Ajin/include/AXM.h"
typedef struct {
	int			nSimual_Mode;
	enum_Axis eAxis;
	int nAxisType;

	double dTargetPos;
	double dVel;
	double dAcc;
	double dDec;

	int nJogDir;
	int m_bAxisMotionDone;
}SimulMotion;

class CBaseMotion
{
public:
	CBaseMotion();
	~CBaseMotion();

public:
	BOOL IsMovingCheck(double dPos1, double dPos2);
	BOOL IsSamePosition(double dPos1, double dPos2);
	BOOL IsSameUVWPosition(double dPos1, double dPos2);
	BOOL IsUmacMotionDone(int nAxisNo);
	BOOL IsAjinMotionDone(int nAxisNo);
	BOOL IsVisionMotionDone(int nAxisNo);
	BOOL IsMotionDone(enum_Axis eAxis);
	BOOL IsAxisMoveDone(enum_Axis eAxis, double dTargetPos); //KJT 20200728 Add

	//BOOL ZUpMove();
	//BOOL IsZUpMove();
	//BOOL YMove(double dPosY);
	//BOOL IsYMove(double dPosY);

	BOOL GetAxisJogParam(enum_Axis pAxis, double* pJogSpeed, double* pAccel, double* pDecel, int nSelJogSpeed);
	BOOL GetAxisWorkParam(enum_Axis pAxis, double* pSpeed, double* pAccel, double* pDecel);
	//Get Axis Data
	BOOL	GetActualAxisNoByEnumAxis(enum_Axis eAxis, int* pAxisType, int* nRemoteAxis);

	BOOL StopAll();

	BOOL UMacAxisMove(int nAxis, double dPosition, double dVel, double dAccel, double dDecel, MOTION_MODE Mode, int nWithMoveBackLightX = 0, double dAOICamOffset = 0.0, BOOL bDirBwd = FALSE, enum_AOI_Vel_Level eAoiVelLevel = eAOI_Vel_50); //KJT 20200929
	BOOL IsUMacAxisMove(int nAxis, double dPosition);
	BOOL UMacAxisStop(int nAxis, int nWithMoveBackLightX = 0); //KJT 20200824

	BOOL AjinAxisMove(int nAxis, double dPosition, double dVel, double dAcc, double dDec, MOTION_MODE Mode);
	BOOL IsAjinAxisMove(int nAxis, double dPosition);
	BOOL AjinAxisStop(int nAxis);

	BOOL VisionAxisMove(int nAxis, double dPosition, double dVel, double dAcc, double dDec, MOTION_MODE Mode);
	BOOL IsVisionAxisMove(int nAxis, double dPosition);
	BOOL VisionAxisStop(enum_DIRECT_AXIS eAxis);

	void	JogMove(enum_Axis eAxis, double dVel, double dAcc, double dDec, int nWithMoveBackLightX = 0, double dAOICamOffset = 0.0);
	void	JogStop(enum_Axis eAxis, int nWithMoveBackLightX = 0);


	BOOL	AbsMove(enum_Axis eAxis, double dPos, double dVel, double dAcc, double dDec, int nWithMoveBackLightX = 0, double dAOICamOffset = 0.0, BOOL bDirBwd = FALSE, enum_AOI_Vel_Level eAoiVelLevel = eAOI_Vel_50);
	BOOL	RelMove(enum_Axis eAxis, double dDist, double dVel, double dAcc, double dDec, int nWithMoveBackLightX = 0, double dAOICamOffset = 0.0); //KJT 20200824
public :
	BOOL *m_pMachineStopFlag;

	//Alarm Reset
	BOOL AlarmReset(enum_Axis eAxis);

	//Origin.
	BOOL OriginStart(enum_Axis nAxis);

	//Servo On.
	BOOL ServoOnOff(enum_Axis eAxis, BOOL nOnOff);

	//DO
	BOOL SetDOutputBitValue(enum_Do eBit, int nValue);
	BOOL GetDInputValue(enum_Di eBit);
	//AO
	BOOL SetAOutputValue(enum_Ao eChannel, double dValue);
	BOOL GetAinputValue(enum_Ai eChannel);

	//Simulation
	SimulMotion SimulMotion;
	int m_bStopSimulThread;
	int m_bJogStop;





	BOOL SimulAxisAbsMove(enum_Axis eAxisNo, double dPos, double dVel, double dAcc, double dDec);
	BOOL SimulAxisJogMove(enum_Axis eAxisNo, double dPos, double dVel, double dAcc, double dDec);
	BOOL SimulAxisJogStop(enum_Axis eAxisNo);

	BOOL m_bStopSimul;
	BOOL AllSimulStop();


	BOOL IsSimulAixsDone();

	BOOL m_nWithMoveBackLightX; //KJT 20200824
	BOOL m_bWithMoveAOICameraX;

	double ConvertTo20X_X(double dPosX);
	double ConvertTo20X_Y(double dPosY);	

	double ConvertToPreAlign_X(double dPosX);
	double ConvertToPreAlign_Y(double dPosY);

	double ConvertToAOI_X(double dPosX);
	double ConvertToAOI_Y(double dPosY);

	double ConvertTo3D_X(double dPosX);
	double ConvertTo3D_Y(double dPosY);

};

UINT SimulThreadProc(LPVOID lpParam);