#pragma once

#include "BaseMotion.h"

class CPitchMotion : public CBaseMotion, public CBaseFlow
{
public:
	CPitchMotion();
	~CPitchMotion();

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
	BOOL			ResetStopBit();
	BOOL			Stop();
	//이동 완료 flag
	BOOL			m_bMotionDone;

	BOOL			m_bTerminate;
	BOOL			IsTerminate() { return m_bTerminate; }

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
	BOOL PitchLeft_WaitPos(enum_Axis eAxis);

	BOOL PitchRight_WaitPos(enum_Axis eAxis);

	//한쌍으로 Move
	BOOL Pitch_WaitPos(enum_eGRIPPER_ROW eRow);
	BOOL Pitch_WaitPos_All();

	//MoveDone Check
	//MovePos
	BOOL Is_PitchLeft_WaitPos(enum_Axis eAxis);

	BOOL Is_PitchRight_WaitPos(enum_Axis eAxis);

	//한쌍으로 Move
	BOOL Is_Pitch_WaitPos(int nRowIndex);

	BOOL Is_Pitch_WaitPos_All();

#pragma region //Pitch Tension
	int m_nAxisIndex;
	int m_nAxisNo[MAX_STRETCH_AXIS_SIZE];
	double m_dPitchTargetPos[MAX_STRETCH_AXIS_SIZE];
	double m_dPitchTargetPos_L[eGRIPPER_ROW_MAX];
	double m_dPitchTargetPos_R[eGRIPPER_ROW_MAX];
	BOOL PitchTensionMove_L(double dOffset);
	BOOL Is_PitchTensionMove_L();
	BOOL PitchTensionMove_R(double dOffset);
	BOOL Is_PitchTensionMove_R();

	BOOL Gripper2PAlignTensionPitchMoveStart(double dDiffY1, double dDiffY2);
	BOOL Gripper2PAlignTensionPitchMoveDoneCheck();
	BOOL Gripper4PAlignTensionPitchMoveStart(double m_AlignPoint[2][4]);
	BOOL Gripper4PAlignTensionPitchMoveDoneCheck();
	BOOL Move_PitchTensionPos(int nAxisIndex, int nAxisNo[MAX_STRETCH_AXIS_SIZE], double dTargetPos[MAX_STRETCH_AXIS_SIZE]);
	BOOL Is_PitchTensionPos(int nAxisIndex, int nAxisNo[MAX_STRETCH_AXIS_SIZE], double dTargetPos[MAX_STRETCH_AXIS_SIZE]);
#pragma endregion

	BOOL PitchPosMove(enum_Axis eAxisNo, double dPos);
	BOOL IsPitchPosMove(enum_Axis eAxisNo, double dPos);

	enum TPitchMotion
	{
		ePITCH_MOTION_IDLE = 1,
		ePITCH_MOTION_START,

		ePITCH_MOTION_ERROR,
		ePITCH_MOTION_DONE,
		ePITCH_MOTION_EXIT
	};
};

