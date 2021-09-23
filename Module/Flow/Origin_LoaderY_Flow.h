#pragma once

class COrigin_LoaderY_Flow : public CBaseFlow
{
public:
	COrigin_LoaderY_Flow();
	~COrigin_LoaderY_Flow();

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

	BOOL			FlowInterlock();

	enum_REMOTE_AXIS eRemoteAxis;

	enum eOrigin_LoaderY_Flow
	{
		_eORIGIN_LOADER_Y_FLOW_ERROR = -1,

		_eORIGIN_LOADER_Y_FLOW_IDLE = 0,
		_eORIGIN_LOADER_Y_FLOW_START,
		_eORIGIN_LOADER_Y_FLOW_INTERLOCK_CHECK,

		_eORIGIN_LOADER_Y_FLOW_HOME_START,
		_eORIGIN_LOADER_Y_FLOW_HOME_COMP_CHECK,
		_eORIGIN_LOADER_Y_FLOW_WAIT_POS,
		_eORIGIN_LOADER_Y_FLOW_WAIT_POS_CHECK,

		_eORIGIN_LOADER_Y_FLOW_DONE,
	};
};

