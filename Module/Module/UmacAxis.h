#pragma once

#include "MotionModule.h"

struct MOTION_MODULE_UMAC_SUB {
	CString strUMacLabel;
	int nUmacAxisMap[7];		//Active, Real, Plc, HomeSig Master, Home Sig Slave, Resolution
};

//Awk UMac 변경시 Change필요.
struct MOTION_MODULE_UMAC {
	MOTION_MODULE_UMAC() {

		//Active, Real, Plc, Home, Index
		for (int i = 0; i < REMOTE_AXIS_UMAC_MAX; i++)
		{
			nUmacInfo[i].strUMacLabel = _T(".....");

			nUmacInfo[i].nUmacAxisMap[UMAC_CONTROL_AXIS] = NoUse;
			nUmacInfo[i].nUmacAxisMap[UMAC_REAL_AXIS] = NoUse;
			nUmacInfo[i].nUmacAxisMap[UMAC_PLC_NO] = NoUse;
			nUmacInfo[i].nUmacAxisMap[UMAC_HOME_NO] = NoUse;
			nUmacInfo[i].nUmacAxisMap[UMAC_HOME_NO_SLAVE] = NoUse;
			nUmacInfo[i].nUmacAxisMap[UMAC_VERTUAL] = NoUse;
			nUmacInfo[i].nUmacAxisMap[UMAC_RESOLUTION] = NoUse;

		}

		//UMAC_LABEL
		///////////////////////////////////////////////////////////////
		//RealAxis
		nUmacInfo[0].strUMacLabel = _T("UMAC_GANTRY_YL");
		nUmacInfo[1].strUMacLabel = _T("UMAC_GANTRY_YR");
		nUmacInfo[2].strUMacLabel = _T("UMAC_GANTRY_X");
		//VirtualAxis
		nUmacInfo[3].strUMacLabel = _T("VIRTUAL_GANTRY_Y");


		//UMAC_CONTROL_AXIS
		//////////////////////////////////////////////////////////////////////
		//RealAxis
		nUmacInfo[0].nUmacAxisMap[UMAC_CONTROL_AXIS] = NoUse;
		nUmacInfo[1].nUmacAxisMap[UMAC_CONTROL_AXIS] = NoUse;
		nUmacInfo[2].nUmacAxisMap[UMAC_CONTROL_AXIS] = Use;
		//VirtualAxis
		nUmacInfo[3].nUmacAxisMap[UMAC_CONTROL_AXIS] = Use;

		//UMAC_VERTUALLAY
		///////////////////////////////////////////////////////////////
		//RealAxis
		nUmacInfo[0].nUmacAxisMap[UMAC_VERTUAL] = NoUse;
		nUmacInfo[1].nUmacAxisMap[UMAC_VERTUAL] = NoUse;
		nUmacInfo[2].nUmacAxisMap[UMAC_VERTUAL] = NoUse;
		//VirtualAxis
		nUmacInfo[3].nUmacAxisMap[UMAC_VERTUAL] = 1;


		///////////////////////////////////////////////////////////////
		//RealAxis
		nUmacInfo[0].nUmacAxisMap[UMAC_REAL_AXIS] = 1;
		nUmacInfo[1].nUmacAxisMap[UMAC_REAL_AXIS] = 2;
		nUmacInfo[2].nUmacAxisMap[UMAC_REAL_AXIS] = 3;
		//VirtualAxis
		nUmacInfo[3].nUmacAxisMap[UMAC_REAL_AXIS] = 21;

		///////////////////////////////////////////////////////////////
		//RealAxis
		nUmacInfo[0].nUmacAxisMap[UMAC_PLC_NO] = 11;
		nUmacInfo[1].nUmacAxisMap[UMAC_PLC_NO] = 11;
		nUmacInfo[2].nUmacAxisMap[UMAC_PLC_NO] = 13;
		//VirtualAxis
		nUmacInfo[3].nUmacAxisMap[UMAC_PLC_NO] = 11;

		//UMAC_HOME_COMPLETE_NO
		///////////////////////////////////////////////////////////////
		//RealAxis
		nUmacInfo[0].nUmacAxisMap[UMAC_HOME_NO] = 5010;
		nUmacInfo[1].nUmacAxisMap[UMAC_HOME_NO] = 5020;
		nUmacInfo[2].nUmacAxisMap[UMAC_HOME_NO] = 5030;
		//VirtualAxis//VirtualAxis
		nUmacInfo[3].nUmacAxisMap[UMAC_HOME_NO] = 5010;

		//UMAC_HOME_COMPLETE_NO 2
		///////////////////////////////////////////////////////////////
		//RealAxis
		nUmacInfo[0].nUmacAxisMap[UMAC_HOME_NO_SLAVE] = 5010;
		nUmacInfo[1].nUmacAxisMap[UMAC_HOME_NO_SLAVE] = 5020;
		nUmacInfo[2].nUmacAxisMap[UMAC_HOME_NO_SLAVE] = 5030;
		//VirtualAxis//VirtualAxis
		nUmacInfo[3].nUmacAxisMap[UMAC_HOME_NO_SLAVE] = 5020;

		//UMAC_RESOLUTION
		///////////////////////////////////////////////////////////////
		//RealAxis
		nUmacInfo[0].nUmacAxisMap[UMAC_RESOLUTION] = 32000;
		nUmacInfo[1].nUmacAxisMap[UMAC_RESOLUTION] = 32000;
		nUmacInfo[2].nUmacAxisMap[UMAC_RESOLUTION] = 32000;

		//VirtualAxis//VirtualAxis
		nUmacInfo[3].nUmacAxisMap[UMAC_RESOLUTION] = 32000;

	}

	MOTION_MODULE_UMAC_SUB nUmacInfo[REMOTE_AXIS_UMAC_MAX];		//Active, Real, Plc, Home, Home2, Index
};


typedef struct CAxisInfoUMAC{
							BOOL bPot;
							BOOL bNot;
							BOOL bVelZero;
							BOOL bServoOn;
							BOOL bAMPEnable;
							BOOL bInpos;
							LONG lFolError;
							LONG lAmpAlarm;
							BOOL bHome;
							LONG lParsingError;
							DOUBLE dCmdPos;
							DOUBLE dActPos;
							DOUBLE dActVel;
							}CAxisInfoPMAC;

const int nMaxUmacAxisCount = REMOTE_AXIS_UMAC_MAX;

class CUmacAxis
{
public:
	BOOL		m_bOpen;
	HINSTANCE	m_hPmacLib;
	BOOL		m_bDeviceOpen;	
	DOUBLE		m_dTargetPosX;
	DOUBLE		m_dTargetPosY;	
	DOUBLE		m_dPrevActPosX;
	DOUBLE		m_dPrevActPosY;

	DOUBLE     m_dTargetPos[REMOTE_AXIS_UMAC_MAX];
	DOUBLE     m_dPrevActPos[REMOTE_AXIS_UMAC_MAX];

	CAxisInfoUMAC 	m_tAxisInfo[REMOTE_AXIS_UMAC_MAX];
	
public:
	CUmacAxis(void);
	~CUmacAxis(void);
		
	MOTION_MODULE_UMAC    m_Umac;

	BOOL  UmacOpen(BOOL bOpen);
	VOID  AxisCmdResponse( CString strSender, CString &strRecver);

	BOOL IsOpen()	{ return m_bOpen;	};
	
	DOUBLE	 CtsToMM(int nIdx, LONGLONG lcts);											// UMAC Axis Uint(CTS => 1mm: 32000CTS
	LONGLONG	MMToCts(int nIdx, DOUBLE dMM);

	INT		Delay(int ms);

	VOID Reset();
	VOID ServoOn(INT32 nAxis, BOOL bOnOff);
	VOID HomeStart(INT32 nAxis);
	VOID HomeStop(INT32 nAxis);
	VOID Jog(INT32 nAxis, BOOL bDirPluse);
	VOID JogMove(INT32 nAxis, DOUBLE dVel, DOUBLE dAccel, DOUBLE dDecel, BOOL bPress);
	VOID PosMove(INT32 nAxis, DOUBLE dVel, DOUBLE dAccel, DOUBLE dDecel, DOUBLE dPos);		
	VOID RelMove(INT32 nAxis, DOUBLE dVel, DOUBLE dAccel, DOUBLE dDecel, DOUBLE dPos);
	VOID MovePos(INT32 nAxis, DOUBLE dPosCts);
	VOID RelMovePos(INT32 nAxis, DOUBLE dPosCts);
	VOID Stop(INT32 nAxis);
	BOOL IsDone( INT32 nAxis );
	VOID SetVel(INT32 nAxis, DOUBLE lVel);
	VOID SetGravityAccDec(INT32 nAxis, LONG lAccDcc);
	VOID SetAccDecTime(INT32 nAxis, LONG lSec);
	VOID SetSCurve(INT32 nAxis, LONG lmsec);
	VOID SetSafytyMotionPara(INT32 nAxis, DOUBLE dVel);
	

	void ResetHomeState(INT32 nAxis);
	BOOL HomeCompReset(INT32 nAxis);
	LONGLONG GetPosBias(INT nAxis);
	void GetStatus(INT32 nAxis);
	LONG GetAddrI08Value(INT nAxis);
	LONG GetAddrI09Value(INT nAxis);
	LONG GetAddrI10Value(INT nAxis);
	LONGLONG GetCalTable(INT32 nAxis);

	BOOL IsPOT(INT32 nAxis);
	BOOL IsNOT(INT32 nAxis);
	BOOL IsHome(INT32 nAxis);
	BOOL IsSpeedZero(INT32 nAxis);
	BOOL IsServoOn(INT32 nAxis);
	BOOL IsAmpEnable(INT32 nAxis);
	BOOL IsInPosition(INT32 nAxis);

	BOOL IsHomeComplete(INT32 nAxis);
	BOOL IsHoming(INT32 nAxis);

	LONG GetFollowError(INT32 nAxis);
	LONG GetAmpAlarm(INT32 nAxis); 
	LONG GetPhasingError(INT32 nAxis);

	DOUBLE GetInitActPosition(INT32 nAxis);
	DOUBLE GetActPosition(INT32 nAxis);
	DOUBLE GetCmdPosition(INT32 nAxis);
	DOUBLE GetActVelocity(INT32 nAxis);

	INT IsIsolatorAlarm();

	
};

