#pragma once
class COrigin_GantryX_Flow : public CBaseFlow
{
public:
	COrigin_GantryX_Flow();
	~COrigin_GantryX_Flow();

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

	BOOL			Start();
	BOOL			Stop();

	CTime m_timeStart; //KJT 20210329

	BOOL			FlowInterlock();

	enum eOrigin_GantryY_Flow
	{
		_eORIGIN_GANTRY_X_FLOW_ERROR = -1,

		_eORIGIN_GANTRY_X_FLOW_IDLE = 0,
		_eORIGIN_GANTRY_X_FLOW_START,
		_eORIGIN_GANTRY_X_FLOW_INTERLOCK_CHECK,

		_eORIGIN_GANTRY_X_FLOW_HOME_START,
		_eORIGIN_GANTRY_X_FLOW_HOME_BIT_OFF_CHECK,
		_eORIGIN_GANTRY_X_FLOW_HOME_COMP_CHECK,
		_eORIGIN_GANTRY_X_FLOW_MOVE_WAIT_POS,
		_eORIGIN_GANTRY_X_FLOW_MOVE_WAIT_POS_CHECK,

		_eORIGIN_GANTRY_X_FLOW_DONE,
	};
};

