#pragma once
#include "../Module/Motion/BaseMotion.h"

class CCamera_Swap_Flow : public CBaseFlow
{
public:
	CCamera_Swap_Flow();
	~CCamera_Swap_Flow();

private:
	BOOL			m_FlowFinish;

	void(*m_StateComplete)(void *pArgument);

	CWinThread*		pThread;
	VOID			ThreadFunctionEntry(VOID);
	static UINT		ThreadFunction(LPVOID lpParam);

public:
	BOOL			m_bFlowDone;
	BOOL			m_bStopBit;

	BOOL InitProcess();
	BOOL EndProcess();

	HANDLE			hHandle;
	BOOL			m_bTerminate;
	BOOL			IsTerminate() { return m_bTerminate; }
	BOOL			Is_FlowDone() { return m_bFlowDone; }

	BOOL			Start(int nSwapMode);
	BOOL			Stop();

	BOOL			FlowInterlock();
	CBaseMotion*	m_Motion;
	int		m_nHomingAxis;
	double m_HomeStartPos;
	int m_stepFlag;
	int m_nSwap_Mode;

	enum eCamera_Swap_Flow
	{
		_eCAMERA_SWAP_FLOW_ERROR = -1,
		_eCAMERA_SWAP_FLOW_IDLE = 0,
		_eCAMERA_SWAP_FLOW_START,
		_eCAMERA_SWAP_FLOW_INTERLOCK_CHECK,

#pragma region //Unloader Ready
		_eCAMERA_SWAP_FLOW_UNLOADER_READY,
		_eCAMERA_SWAP_FLOW_UNLOADER_READY_CHECK,
#pragma endregion

#pragma region //Loader Ready
		_eCAMERA_SWAP_FLOW_LOADER_READY,
		_eCAMERA_SWAP_FLOW_LOADER_READY_CHECK,
#pragma endregion

		_eCAMERA_SWAP_FLOW_GANTRY_XYZ_POS,
		_eCAMERA_SWAP_FLOW_GANTRY_XYZ_POS_CHECK,
		
		_eCAMERA_SWAP_FLOW_DONE,
		_eCAMERA_SWAP_FLOW_STOP,
	};
};

