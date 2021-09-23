#pragma once


#include "BaseMotion.h"

class CLoaderMotion : public CBaseMotion, public CBaseFlow
{
public:
	CLoaderMotion();
	~CLoaderMotion();

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

	//Loader Z
	BOOL LoaderZ_WaitPos();
	BOOL LoaderZ_StickLoadInBox1stPos();//paper
	BOOL LoaderZ_Vibration_Pos(); //KJT 20210317
	BOOL LoaderZ_PaperUnloadPos();
	BOOL LoaderZ_StickUnloadToStagePos();
	BOOL LoaderZ_StickLoadInStage1stPos();	
	BOOL LoaderZ_StickUnloadToBoxPos();

	BOOL Is_LoaderZ_WaitPos();
	BOOL Is_LoaderZ_StickLoadInBox1stPos();
	BOOL Is_LoaderZ_Vibration_Pos(); //KJT 20210317
	BOOL Is_LoaderZ_PaperUnloadPos();
	BOOL Is_LoaderZ_StickUnloadToStagePos();
	BOOL Is_LoaderZ_StickLoadInStage1stPos();	
	BOOL Is_LoaderZ_StickUnloadToBoxPos();

	//21.02.05 sjc 
	//21.02.28 sjc
	//BOOL LoaderZL_WaitPos();
	//BOOL LoaderZL_DownPos();
	//BOOL LoaderZR_WaitPos();
	//BOOL LoaderZR_DownPos();

	//BOOL Is_LoaderZL_WaitPos();
	//BOOL Is_LoaderZR_WaitPos();
	//BOOL Is_LoaderZL_DownPos();
	//BOOL Is_LoaderZR_DownPos();
	//Loader X
	BOOL LoaderX_WaitPos();
	BOOL LoaderX_AlignPos();
	BOOL LoaderX_StickPickUpPos();
	BOOL Is_LoaderX_WaitPos();
	BOOL Is_LoaderX_AlignPos();
	BOOL Is_LoaderX_StickPickUpPos();

	//21.02.15 SJC 
	//Loader Y
	BOOL LoaderY_WaitPos();
	BOOL LoaderY_Stick_LoadPos();
	BOOL LoaderY_Stick_UnloadPos();
	BOOL LoaderY_Paper_LoadPos();
	BOOL LoaderY_Paper_UnloadPos();
	BOOL LoaderY_Inspection_Pos();

	BOOL Is_LoaderY_WaitPos();
	BOOL Is_LoaderY_Stick_LoadPos();
	BOOL Is_LoaderY_Stick_UnloadPos();
	BOOL Is_LoaderY_Paper_LoadPos();
	BOOL Is_LoaderY_Paper_UnloadPos();
	BOOL Is_LoaderY_Inspection_Pos();
	//21.02.26 sjc
	BOOL LoaderZ_Inspection_Pos();
	BOOL Is_LoaderZ_Inspection_Pos();

#pragma region //IO
	BOOL	Stick_Vac_On(int nFinger);
	BOOL	Stick_Vac_Off(int nFinger);
	BOOL	Stick_Active_Vac_On();
	BOOL	Stick_Active_Vac_Off();
	BOOL	Stick_Blow_On();
	BOOL	Stick_Blow_Off();
	BOOL	Stick_All_Vac_On();
	BOOL	Stick_All_Vac_Off();
	BOOL	Is_Stick_Vac_On(int nFinger);
	BOOL	Is_Stick_Vac_Off(int nFinger);
	BOOL	Is_Stick_Active_Vac_On();
	BOOL	Is_Stick_Active_Vac_Off();
	BOOL	Is_Stick_Blow_On();
	BOOL	Is_Stick_Blow_Off();
	BOOL	Is_Stick_All_Vac_On();
	BOOL	Is_Stick_All_Vac_Off();

	BOOL	Paper_Vac_On(int nFinger);
	BOOL	Paper_Vac_Off(int nFinger);
	BOOL	Paper_Active_Vac_On();
	BOOL	Paper_Active_Vac_Off();
	BOOL	Paper_Blow_On();
	BOOL	Paper_Blow_Off();
	BOOL	Paper_All_Vac_On();
	BOOL	Paper_All_Vac_Off();
	BOOL	Is_Paper_Vac_On(int nFinger);
	BOOL	Is_Paper_Vac_Off(int nFinger);
	BOOL	Is_Paper_Active_Vac_On();
	BOOL	Is_Paper_Active_Vac_Off();
	BOOL	Is_Paper_Blow_On();
	BOOL	Is_Paper_Blow_Off();
	//BOOL	Is_Paper_All_Vac_On();
	//BOOL	Is_Paper_All_Vac_Off();

	BOOL    Is_PaperBox_Fwd();

	//Loader Cylinder UpDown
	BOOL	Cylinder_Up();
	BOOL	Is_Cylinder_Up();
	BOOL	Cylinder_Down();
	BOOL	Is_Cylinder_Down();

	BOOL	Ionizer_On();
	BOOL	Is_Ionizer_On();
	BOOL	Ionizer_Off();
	BOOL	Is_Ionizer_Off();

	BOOL	CheckLoaderFlowInterlock(CString StrFlow, int nFlow, int nStartNo);
#pragma endregion

	enum TLoaderMotion
	{
		eLOADER_MOTION_ERROR = -1,
		eLOADER_MOTION_IDLE = 0,		
		
		eLOADER_MOTION_DONE,
		eLOADER_MOTION_EXIT
	};
};

