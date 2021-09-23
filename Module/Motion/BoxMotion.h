#pragma once

#include "BaseMotion.h"
//#include "../WkLibFlow/WkLibFlow.h"
#include "Flow/BaseFlow.h"
#ifndef SIM_MODE
#include "../WkLibVision/WkLibVision.h"
#endif

class CBoxMotion : public CBaseMotion, public CBaseFlow
{
public:
	CBoxMotion();
	~CBoxMotion();

private:
	CWinThread*		pMotionThread;
	CWinThread*		pMonitoringThread;
	int				m_nCurStep;
	DWORD			m_dwTimeTick;
	DWORD			m_dwTimeOut;
	BOOL			m_StateFinish;
	void(*m_StateComplete)(void *pArgument);


	VOID			MotionThreadFunctionEntry(VOID);
	static UINT		MotionThreadFunction(LPVOID lpParam);

	//VOID			MonitoringThreadFunctionEntry(VOID);
	//static UINT		MonitoringThreadFunction(LPVOID lpParam);

	BOOL			m_bStopBit;

public:

	HANDLE			hMotionHandle;

	BOOL			InitProcess();
	BOOL			EndProcess();
	BOOL			Stop();
	//이동 완료 flag
	BOOL			m_bMotionDone;

	BOOL			m_bTerminate;
	BOOL			IsTerminate() { return m_bTerminate; }

	BOOL CheckPosInterlock(double dTargetPos);

#pragma region //Vision
	BOOL FindBoxAlignPattern_Left(double *dDiffPosX, double *dDiffPosY);
	BOOL FindBoxAlignPattern_Right(double *dDiffPosX, double *dDiffPosY);
#pragma endregion

#pragma region //Uvw
	//sunghaklee(2021.02.25)
	BOOL UVWStageAlignMove(int nAlignMode, double dCmdPointXY[4][2], double dActPointXY[4][2]); //KJT 20200830
	void Make2PointAlignData(int nNo, double dRefLeftXY[2], double dRefRightXY[2], double dObjLeftXY[2], double dObjRightXY[2], double *dX, double *dY, double *dT); //KJT 20200830
#pragma endregion

	BOOL LoadingStageUvw_HomeStart();

	int UVWStagePosMove(double UVW[3], double dVel[3], double dAccel[3], double dDecel[3]);
	BOOL IsUVWStagePos(double UVW[3]);
	BOOL GetUVWPos(double *dRefPosX, double *dRefPosY, double *dDiffPosX, double *dDiffPosY, double *dUVWX, double *dUVWY, double *dUVWZ, BOOL bInspectPointFlag);
	BOOL IsAxisHome(UINT nAxisNo);

	///////////////
	//////////////////////////////////////////////////////////////////////////
	BOOL MoveAxis(enum_Axis eAxis, double dPos);
	BOOL IsMoveDone(enum_Axis eAxis, double dPos);

#pragma region //Loading Stage UVW
	BOOL LoadingStageUVW_WaitPos();
	BOOL LoadingStageUVW_StickLoadPos();
	BOOL LoadingStageUVW_StickUnloadPos();

	BOOL Is_LoadingStageUVW_WaitPos();
	BOOL Is_LoadingStageUVW_StickLoadPos();
	BOOL Is_LoadingStageUVW_StickUnloadPos();
#pragma endregion

	//BoxAlignCamera YL
	BOOL BoxAlignCameraYL_WaitPos();
	BOOL BoxAlignCameraYL_InspectionPos();

	BOOL Is_BoxAlignCameraYL_WaitPos();
	BOOL Is_BoxAlignCameraYL_InspectionPos();

	//BoxAlignCamera YR
	BOOL BoxAlignCameraYR_WaitPos();
	BOOL BoxAlignCameraYR_InspectionPos();

	BOOL Is_BoxAlignCameraYR_WaitPos();
	BOOL Is_BoxAlignCameraYR_InspectionPos();

	//Magnetic Chuck
	BOOL BoxMagnetic_Chuck_On();
	BOOL BoxMagnetic_Chuck_Off();

	BOOL Is_BoxMagnetic_Chuck_On();
	BOOL Is_BoxMagnetic_Chuck_Off();
	

	enum TLoadingStageMotion
	{
		eBOX_MOTION_ERROR = -1,
		eBOX_MOTION_IDLE = 0,		

#pragma region //UVW Home (Y1, Y2, X)
		eLOADING_STAGE_ORIGIN_SERVO_ALL_OFF,
		eLOADING_STAGE_ORIGIN_SERVO_ALL_OFF_CHECK,
		eLOADING_STAGE_ORIGIN_Y1Y2_SERVO_ON,
		eLOADING_STAGE_ORIGIN_Y1Y2_SERVO_ON_CHECK,
		eLOADING_STAGE_ORIGIN_Y1Y2_START,
		eLOADING_STAGE_ORIGIN_Y1Y2_HOME_BIT_CHECK,
		eLOADING_STAGE_ORIGIN_Y1Y2_HOME_COMPLETE_CHECK,
		eLOADING_STAGE_ORIGIN_Y1_Y2_ORIGIN_POS,
		eLOADING_STAGE_ORIGIN_Y1_Y2_ORIGIN_POS_CHECK,
		eLOADING_STAGE_ORIGIN_X_SERVO_ON,
		eLOADING_STAGE_ORIGIN_X_SERVO_ON_CHECK,
		eLOADING_STAGE_ORIGIN_X_START,
		eLOADING_STAGE_ORIGIN_X_HOME_BIT_CHECK,
		eLOADING_STAGE_ORIGIN_X_HOME_COMPLETE_CHECK,
		eLOADING_STAGE_ORIGIN_X_ORIGIN_POS,
		eLOADING_STAGE_ORIGIN_X_ORIGIN_POS_CHECK,
#pragma endregion

		eBOX_MOTION_DONE,
		eBOX_MOTION_EXIT
	};
};

