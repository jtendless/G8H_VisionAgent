#pragma once

#include "BaseMotion.h"

class CUnloaderMotion : public CBaseMotion, public CBaseFlow
{
public:
	CUnloaderMotion();
	~CUnloaderMotion();

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

	BOOL MoveAxis(enum_Axis eAxis, double dPos);
	BOOL IsMoveDone(enum_Axis eAxis, double dPos);

	double m_dUnloaderY_StickUnloadGap;
	BOOL GetUnloadYToCSTPos(double *pdTargetPosUldY);

#pragma region //PaperUnloader
	BOOL PaperUnloaderY_All_Pos(double dPos);
	BOOL PaperUnloaderY_All_WaitPos();
	BOOL PaperUnloaderY_All_LoadPaperPos();
	BOOL PaperUnloaderY_All_LoadPaperWaitingPos();
	BOOL PaperUnloaderY_All_UnloadPaperPos();
	BOOL PaperUnloaderY_All_CassetteSafetyPos();

	BOOL Is_PaperUnloaderY_All_Pos(double dPos);
	BOOL Is_PaperUnloaderY_All_WaitPos();
	BOOL Is_PaperUnloaderY_All_LoadPaperPos();
	BOOL Is_PaperUnloaderY_All_LoadPaperWaitingPos();
	BOOL Is_PaperUnloaderY_All_UnloadPaperPos();
	BOOL Is_PaperUnloaderY_All_CassetteSafetyPos();

	BOOL PaperUnloaderX_All_WaitPos();
	BOOL PaperUnloaderX_All_PickUpPos();
	BOOL Is_PaperUnloaderX_All_WaitPos();
	BOOL Is_PaperUnloaderX_All_PickUpPos();

	BOOL PaperUnloaderZ_All_WaitPos();
	BOOL PaperUnloaderZ_All_UnloadPaperPos();
	BOOL Is_PaperUnloaderZ_All_WaitPos();
	BOOL Is_PaperUnloaderZ_All_UnloadPaperPos();
#pragma endregion

#pragma region //GantryY Unloader
	BOOL GantryY_StickLoadInStagePos();
	BOOL GantryY_StickUnloadToCstPos(int nSlot);
	BOOL GantryY_StickLoadInCstPos(int nSlot);
	BOOL GantryY_StickUnloadToStagePos();

	BOOL Is_GantryY_StickLoadInStagePos();
	BOOL Is_GantryY_StickUnloadToCstPos(int nSlot);
	BOOL Is_GantryY_StickLoadInCstPos(int nSlot);
	BOOL Is_GantryY_StickUnloadToStagePos();
#pragma endregion

	BOOL Move_UnloaderY_Pos(double dPos);
	BOOL UnloaderY_WaitPos();

	//21.02.15 sjc
	BOOL UnloaderY_LoadPaperPos();
	//
	BOOL Is_UnloaderY_Pos(double dPos);
	BOOL Is_UnloaderY_WaitPos();
	BOOL Is_UnloaderY_LoadInStagePos();
	BOOL Is_UnloaderY_UnloadToCstPos(int nSlot);
	BOOL Is_UnloaderY_LoadInCstPos(int nSlot);
	BOOL Is_UnloaderY_UnloadToStagePos();
	//21.02.15 sjc
	BOOL Is_UnloaderY_LoadPaperPos();
	BOOL Is_UnloaderY_UnloadPaperPos();
	BOOL Is_UnloaderY_CassetteSafetyPos();
	//
	

	//StickUnloader X
	BOOL UnloaderX_WaitPos();
	BOOL UnloaderX_PickUpPos();
	BOOL Is_UnloaderX_WaitPos();
	BOOL Is_UnloaderX_PickUpPos();

	//MaskUnloader Z
	BOOL UnloaderZ_WaitPos();
	BOOL UnloaderZ_LoadInStagePos();
	BOOL UnloaderZ_UnloadToCstPos();
	BOOL UnloaderZ_LoadInCstPos();
	BOOL UnloaderZ_UnloadToStagePos();
	//21.02.15
	BOOL UnloaderZ_LoadPaperPos();
	BOOL UnloaderZ_UnloadPaperPos();
	BOOL UnloaderZ_Vibration_Pos();

	//MaskUnloader Z
	BOOL Is_UnloaderZ_WaitPos();
	BOOL Is_UnloaderZ_LoadInStagePos();
	BOOL Is_UnloaderZ_UnloadToCstPos();
	BOOL Is_UnloaderZ_LoadInCstPos();
	BOOL Is_UnloaderZ_UnloadToStagePos();
	//21.02.15 sjc
	BOOL Is_UnloaderZ_LoadPaperPos();
	BOOL Is_UnloaderZ_UnloadPaperPos();
	BOOL Is_UnloaderZ_Vibration_Pos();
	//
	//21.02.15 sjc
	//PaperUnloader Z
	

	BOOL UnloaderSubZL_LoadPaperPos();
	BOOL UnloaderSubZR_LoadPaperPos();
	BOOL UnloaderSubZL_UnloadPaperPos();
	BOOL UnloaderSubZR_UnloadPaperPos();

	BOOL Is_UnloaderSubZL_LoadPaperPos();
	BOOL Is_UnloaderSubZR_LoadPaperPos();
	BOOL Is_UnloaderSubZL_UnloadPaperPos();
	BOOL Is_UnloaderSubZR_UnloadPaperPos();


	BOOL Ionizer_On();
	BOOL Ionizer_Off();

	BOOL Is_Ionizer_On();
	BOOL Is_Ionizer_Off();


	//
#pragma region //IO
	//Stick Vac
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

	BOOL	PaperUnloader_Vac_On(int nFinger);
	BOOL	PaperUnloader_Vac_Off(int nFinger);
	BOOL	PaperUnloader_Active_Vac_On();
	BOOL	PaperUnloader_Active_Vac_Off();
	BOOL	PaperUnloader_All_Vac_On();
	BOOL	PaperUnloader_All_Vac_Off();
	BOOL	Is_PaperUnloader_Vac_On(int nFinger);
	BOOL	Is_PaperUnloader_Vac_Off(int nFinger);
	BOOL	Is_PaperUnloader_Active_Vac_On();
	BOOL	Is_PaperUnloader_Active_Vac_Off();
	BOOL	Is_PaperUnloader_All_Vac_On();
	BOOL	Is_PaperUnloader_All_Vac_Off();
	

	BOOL	Paper_Vac_On(int nFinger);
	BOOL	Paper_Vac_Off(int nFinger);
	//BOOL	Paper_Active_Vac_On();
	//BOOL	Paper_Active_Vac_Off();
	BOOL	Paper_Blow_On();
	BOOL	Paper_Blow_Off();
	BOOL	Paper_All_Vac_On();
	BOOL	Paper_All_Vac_Off();
	//BOOL	Is_Paper_Vac_On(int nFinger);
	//BOOL	Is_Paper_Vac_Off(int nFinger);
	//BOOL	Is_Paper_Active_Vac_On();
	//BOOL	Is_Paper_Active_Vac_Off();
	//BOOL	Is_Paper_All_Vac_On();
	//BOOL	Is_Paper_All_Vac_Off();

	BOOL	CheckUnloaderFlowInterlock(CString StrFlow, int nFlow, int nStartNo);
	BOOL	CheckPaperUnloaderFlowInterlock(CString StrFlow, int nFlow, int nStartNo);
#pragma endregion

	enum TUnloaderMotion
	{
		eUNLOADER_MOTION_ERROR = -1,
		eUNLOADER_MOTION_IDLE = 0,		

		eUNLOADER_MOTION_DONE,
		eUNLOADER_MOTION_EXIT
	};
};

