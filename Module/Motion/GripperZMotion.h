#pragma once

#include "BaseMotion.h"
//#include "../WkLibFlow/WkLibFlow.h"
#include "Flow/BaseFlow.h"

class CGripperZMotion : public CBaseMotion, public CBaseFlow
{
public:
	CGripperZMotion();
	~CGripperZMotion();

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

	BOOL Move_GripperLeftZ_WaitPos();
	BOOL Move_GripperLeftZ_LoadingPos();
	BOOL Move_GripperLeftZ_ClampPos();
	BOOL Move_GripperLeftZ_TensionPos();
	BOOL Move_GripperLeftZ_UnclampPos();

	BOOL Is_GripperLeftZ_WaitPos();
	BOOL Is_GripperLeftZ_LoadingPos();
	BOOL Is_GripperLeftZ_ClampPos();
	BOOL Is_GripperLeftZ_TensionPos();
	BOOL Is_GripperLeftZ_UnclampPos();

	BOOL Move_GripperRightZ_WaitPos();
	BOOL Move_GripperRightZ_LoadingPos();
	BOOL Move_GripperRightZ_ClampPos();
	BOOL Move_GripperRightZ_TensionPos();
	BOOL Move_GripperRightZ_UnclampPos();

	BOOL Is_GripperRightZ_WaitPos();
	BOOL Is_GripperRightZ_LoadingPos();
	BOOL Is_GripperRightZ_ClampPos();
	BOOL Is_GripperRightZ_TensionPos();
	BOOL Is_GripperRightZ_UnclampPos();

	enum TGripperZMotion
	{
		eGRIPPER_Z_MOTION_ERROR = -1,
		eGRIPPER_Z_MOTION_IDLE = 0,
		
		eGRIPPER_Z_MOTION_DONE,
		eGRIPPER_Z_MOTION_EXIT
	};
};

