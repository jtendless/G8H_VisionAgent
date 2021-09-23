#pragma once

#include "BaseMotion.h"

class CCassetteMotion : public CBaseMotion, public CBaseFlow
{
public:
	CCassetteMotion();
	~CCassetteMotion();

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

	BOOL MoveAxis(enum_Axis eAxis, double dPos);
	BOOL IsMoveDone(enum_Axis eAxis, double dPos);

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

	//Cassette Z
	BOOL CassetteZ_MoveFloor(enum_CassetteFloor eFloor);
	BOOL CassetteZ_WaitPos();
	BOOL CassetteZ_1FloorPos();
	BOOL CassetteZ_2FloorPos();
	BOOL CassetteZ_3FloorPos();
	BOOL CassetteZ_4FloorPos();
	//BOOL CassetteZ_5FloorPos(); //Junying TPCD Floor1~4 Use
	//BOOL CassetteZ_6FloorPos();

	BOOL Is_CassetteZ_Floor(enum_CassetteFloor eFloor);
	BOOL Is_CassetteZ_WaitPos();
	BOOL Is_CassetteZ_1FloorPos();
	BOOL Is_CassetteZ_2FloorPos();
	BOOL Is_CassetteZ_3FloorPos();
	BOOL Is_CassetteZ_4FloorPos();
	//BOOL Is_CassetteZ_5FloorPos();
	//BOOL Is_CassetteZ_6FloorPos();

	//IO
	BOOL CSTPickUpUnitFwd();
	BOOL CSTPickUpUnitBwd();
	BOOL CSTPickUpUnitClamp();
	BOOL CSTPickUpUnitUnclamp();

	BOOL Is_CSTPickUpUnitFwd();
	BOOL Is_CSTPickUpUnitBwd();
	BOOL Is_CSTPickUpUnitClamp();
	BOOL Is_CSTPickUpUnitUnclamp();


	BOOL Is_CSTSafefySensorOn();
	BOOL Is_CSTPaperSensorOn();	
	BOOL Is_CSTSafetyAndPaperSensorOn();

	BOOL CSTPaperBoxUnitFwd();
	BOOL CSTPaperBoxUnitBwd();
	
	BOOL Is_CSTPaperBoxUnitFwd();
	BOOL Is_CSTPaperBoxUnitBwd();
	

	enum TUnloaderMotion
	{
		eCASSETTE_MOTION_IDLE = 0,
		eCASSETTE_MOTION_START,

		eCASSETTE_MOTION_DONE,
		eCASSETTE_MOTION_EXIT
	};
};

