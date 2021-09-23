#pragma once

#include "BaseMotion.h"
#include "MotionAgentDefine.h"

class CStretchMotion : public CBaseMotion, public CBaseFlow
{
public:
	CStretchMotion();
	~CStretchMotion();

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

	VOID			MonitoringThreadFunctionEntry(VOID);
	static UINT		MonitoringThreadFunction(LPVOID lpParam);

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
	enum MOTION_MODE
	{
		eMOTION_ABS = 0,
		eMOTION_REL,
		eMOTION_VEL,
		eMOTION_MAX,
	};

	BOOL IsAxisHome(UINT nAxisNo);

	//////////////////////////////////////////////////////////////////////////
	BOOL MoveAxis(enum_Axis eAxis, double dPos);
	BOOL IsMoveDone(enum_Axis eAxis, double dPos);

	//MovePos
	//한쌍으로 Move
	BOOL Stretch_WaitPos(enum_eGRIPPER_ROW eRow);
	BOOL Stretch_FwdPos(enum_eGRIPPER_ROW eRow);
	BOOL Stretch_BwdPos(enum_eGRIPPER_ROW eRow);

	BOOL Stretch_WaitPos_All();
	BOOL Stretch_FwdPos_Active();
	BOOL Stretch_FwdPos_All();
	BOOL Stretch_BwdPos_All();

	BOOL Stretch_WaitPos_L(enum_eGRIPPER_ROW eRow);
	BOOL Stretch_FwdPos_L(enum_eGRIPPER_ROW eRow);
	BOOL Stretch_BwdPos_L(enum_eGRIPPER_ROW eRow);

	BOOL Stretch_WaitPos_R(enum_eGRIPPER_ROW eRow);
	BOOL Stretch_FwdPos_R(enum_eGRIPPER_ROW eRow);
	BOOL Stretch_BwdPos_R(enum_eGRIPPER_ROW eRow);

	//MovePosDone Check
	//한쌍으로 MoveDone check
	BOOL Is_Stretch_WaitPos(enum_eGRIPPER_ROW eRow);
	BOOL Is_Stretch_FwdPos(enum_eGRIPPER_ROW eRow);
	BOOL Is_Stretch_BwdPos(enum_eGRIPPER_ROW eRow);

	BOOL Is_Stretch_WaitPos_Active();
	BOOL Is_Stretch_WaitPos_All();
	BOOL Is_Stretch_FwdPos_Active();
	BOOL Is_Stretch_FwdPos_All();
	BOOL Is_Stretch_BwdPos_Active();
	BOOL Is_Stretch_BwdPos_All();

#pragma region //Stretch
	int ForceControlIndex;
	BOOL SendStretchSetPara();
	BOOL StretchSetStepValue(int nStepCnt, double dStepValue[MAX_STEP][MAX_STRETCH_SIZE]);
	BOOL SendReleaseSetPara();
	BOOL SetReleaseStepValue();
	BOOL StretchStart(BOOL bReleaseFlag = FALSE);
	BOOL StretchStop();
	int StretchFinish();
#pragma endregion
	//Release

#pragma region //Stretch Tension
	int m_nAxisIndex;
	int m_nAxisNo[MAX_STRETCH_AXIS_SIZE];
	double m_dStretchTargetPos[MAX_STRETCH_AXIS_SIZE];
	double m_dStretchTargetPos_L[eGRIPPER_ROW_MAX];
	double m_dStretchTargetPos_R[eGRIPPER_ROW_MAX];
	BOOL Gripper2PAlignTensionStretchMoveStart(double dDiffX1, double dDiffX2);
	BOOL Gripper2PAlignTensionStretchMoveDoneCheck();
	BOOL Gripper4PAlignTensionStretchMoveStart(double m_AlignPoint[2][4]);
	BOOL Gripper4PAlignTensionStretchMoveDoneCheck();
	BOOL Move_StretchTensionPos(int nAxisIndex, int nAxisNo[MAX_STRETCH_AXIS_SIZE], double dTargetPos[MAX_STRETCH_AXIS_SIZE]);
	BOOL Is_StretchTensionPos(int nAxisIndex, int nAxisNo[MAX_STRETCH_AXIS_SIZE], double dTargetPos[MAX_STRETCH_AXIS_SIZE]);

	BOOL StretchPosMove(int nAxisNo, double dPos);
	BOOL IsStretchPosMove(int nAxisNo, double dPos);
#pragma endregion

	enum TStretchMotion
	{
		eSTRETCH_MOTION_IDLE = 0,
		eSTRETCH_MOTION_START,

		eSTRETCH_MOTION_DONE,
		eSTRETCH_MOTION_EXIT
	};
};

