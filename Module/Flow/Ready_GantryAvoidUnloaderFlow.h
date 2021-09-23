#pragma once

class CReady_GantryAvoidUnloaderFlow : public CBaseFlow
{
public:
	CReady_GantryAvoidUnloaderFlow();
	~CReady_GantryAvoidUnloaderFlow();

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
	BOOL			IsFlowDone() { return m_bFlowDone; }

	BOOL			Start();
	BOOL			Stop();

	BOOL			FlowInterlock();

	enum eReady_GantryAvoidUnloaderFlow
	{
		_eREADY_GANTRY_AVOID_UNLOADER_FLOW_ERROR = -1,
		_eREADY_GANTRY_AVOID_UNLOADER_FLOW_IDLE = 0,
		_eREADY_GANTRY_AVOID_UNLOADER_FLOW_START,
		_eREADY_GANTRY_AVOID_UNLOADER_FLOW_INTERLOCK_CHECK,

		_eREADY_GANTRY_AVOID_UNLOADER_FLOW_Z_ALL_WAIT_POS,
		_eREADY_GANTRY_AVOID_UNLOADER_FLOW_Z_ALL_WAIT_POS_CHECK,
		_eREADY_GANTRY_AVOID_UNLOADER_FLOW_XY_AVOID_POS,
		_eREADY_GANTRY_AVOID_UNLOADER_FLOW_XY_AVOID_POS_CHECK,
				
		_eREADY_GANTRY_AVOID_UNLOADER_FLOW_DONE,
	};
};

