#pragma once

#include "Common/CommonDefine.h"
#include "BaseMotion.h"

class CClampMotion : public CBaseMotion, public CBaseFlow
{
public:
	CClampMotion();
	~CClampMotion();

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

	int				m_ClampStartIndex;

	//Clamp Axis No
	int m_nClampAxisL[eGRIPPER_ROW_MAX];
	int m_nClampAxisR[eGRIPPER_ROW_MAX];

	//State 시작
	BOOL			Start();
	enum MOTION_MODE
	{
		eMOTION_ABS = 0,
		eMOTION_REL,
		eMOTION_VEL,
		eMOTION_MAX,
	};

	BOOL InitPara();

	BOOL IsAxisHome(UINT nAxisNo);

	//////////////////////////////////////////////////////////////////////////
	BOOL MoveAxis(enum_Axis eAxis, double dPos);
	BOOL IsMoveDone(enum_Axis eAxis, double dPos);

	//Clamp On
	BOOL ClampOn(enum_eGRIPPER_ROW eRow); //한쌍으로
	BOOL ClampOn_Active();
	BOOL ClampOn_All();

	BOOL Is_ClampOn(enum_eGRIPPER_ROW eRow);
	BOOL Is_ClampOn_Active();
	BOOL Is_ClampOn_All();

	//Clamp Off
	BOOL ClampOff(enum_eGRIPPER_ROW eRow);
	BOOL ClampOff_Active();
	BOOL ClampOff_All();

	BOOL Is_ClampOff(enum_eGRIPPER_ROW eRow);
	BOOL Is_ClampOff_Active();
	BOOL Is_ClampOff_All();

	BOOL Is_ClampOff_Active_L();
	BOOL Is_ClampOff_Active_R();
	//21.04.03 sjc 
	BOOL Is_ClampOff_Left(enum_eGRIPPER_ROW eRow);
	BOOL Is_ClampOff_Right(enum_eGRIPPER_ROW eRow);

	enum TClampMotion
	{
		eCLAMP_MOTION_IDLE = 0,
		eCLAMP_MOTION_START,

		eCLAMP_MOTION_DONE,
		eCLAMP_MOTION_EXIT
	};
};

