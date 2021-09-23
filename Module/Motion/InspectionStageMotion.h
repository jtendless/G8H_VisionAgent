#pragma once

#include "BaseMotion.h"

class CInspectionStageMotion : public CBaseMotion, public CBaseFlow
{
public:
	CInspectionStageMotion();
	~CInspectionStageMotion();

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


	//State 시작
	BOOL			Start();
	
	BOOL IsAxisHome(UINT nAxisNo);

	BOOL InspectionStageUvw_HomeStart();

	////
	BOOL MoveAxis(enum_Axis eAxis, double dPos);
	BOOL IsMoveDone(enum_Axis eAxis, double dPos);

	double dUVWTargetPos[3];
	int UVWStagePosMove(double UVW[3], double dVel[3], double dAccel[3], double dDecel[3]);
	BOOL IsUVWStagePos(double UVW[3]);
	BOOL GetUVWPos(double *dRefPosX, double *dRefPosY, double *dDiffPosX, double *dDiffPosY, double *dUVWX, double *dUVWY, double *dUVWZ, BOOL bInspectPointFlag);

	//sunghaklee(2021.02.25)
	BOOL UVWStageAlignMove(int nAlignMode, double dCmdPointXY[4][2], double dActPointXY[4][2]); //KJT 20200830
	void Make2PointAlignData(int nNo, double dRefLeftXY[2], double dRefRightXY[2], double dObjLeftXY[2], double dObjRightXY[2], double *dX, double *dY, double *dT); //KJT 20200830

#pragma region //Inspection Stage UVW
	BOOL InspectionStageUVW_WaitPos();
	BOOL InspectionStageUVW_StickLoadPos();
	BOOL InspectionStageUVW_StickUnloadPos();

	BOOL Is_InspectionStageUVW_WaitPos();
	BOOL Is_InspectionStageUVW_StickLoadPos();
	BOOL Is_InspectionStageUVW_StickUnloadPos();
#pragma endregion

#pragma region //IO
	BOOL Inspect_Stage_Vac_On();
	BOOL Inspect_Stage_Vac_Off();

	BOOL Is_Inspect_Stage_Vac_On();
	BOOL Is_Inspect_Stage_Vac_Off();
#pragma endregion

	enum TInspectionStageMotion
	{
		eINSPECTION_STAGE_MOTION_IDLE = 0,
		eINSPECTION_STAGE_MOTION_START,

#pragma region //UVW Home (X, Y1, Y2)
		eINSPECTION_STAGE_ORIGIN_SERVO_ALL_OFF,
		eINSPECTION_STAGE_ORIGIN_SERVO_ALL_OFF_CHECK,
		eINSPECTION_STAGE_ORIGIN_STAGE_Y1_Y2_SERVO_ON,
		eINSPECTION_STAGE_ORIGIN_STAGE_Y1_Y2_SERVO_ON_CHECK,
		eINSPECTION_STAGE_ORIGIN_Y1_Y2_START,
		eINSPECTION_STAGE_ORIGIN_Y1_Y2_HOME_BIT_CHECK,
		eINSPECTION_STAGE_ORIGIN_Y1_Y2_HOME_COMPLETE_CHECK,
		eINSPECTION_STAGE_ORIGIN_Y1_Y2_ORIGIN_POS,
		eINSPECTION_STAGE_ORIGIN_Y1_Y2_ORIGIN_POS_CHECK,
		eINSPECTION_STAGE_ORIGIN_X_SERVO_ON,
		eINSPECTION_STAGE_ORIGIN_X_SERVO_ON_CHECK,
		eINSPECTION_STAGE_ORIGIN_X_START,
		eINSPECTION_STAGE_ORIGIN_X_HOME_BIT_CHECK,
		eINSPECTION_STAGE_ORIGIN_X_HOME_COMPLETE_CHECK,
		eINSPECTION_STAGE_ORIGIN_X_ORIGIN_POS,
		eINSPECTION_STAGE_ORIGIN_X_ORIGIN_POS_CHECK,
#pragma endregion

		eINSPECTION_STAGE_MOTION_DONE,
		eINSPECTION_STAGE_MOTION_EXIT
	};
};

