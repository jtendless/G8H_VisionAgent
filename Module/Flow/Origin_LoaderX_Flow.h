#pragma once

class COrigin_LoaderX_Flow : public CBaseFlow
{
public:
	COrigin_LoaderX_Flow();
	~COrigin_LoaderX_Flow();

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

	enum eOrigin_LoaderX_Flow
	{
		_eORIGIN_LOADER_X_FLOW_ERROR = -1,

		_eORIGIN_LOADER_X_FLOW_IDLE = 0,
		_eORIGIN_LOADER_X_FLOW_START,
		_eORIGIN_LOADER_X_FLOW_INTERLOCK_CHECK,

		eORIGIN_LOADER_X_FLOW_HOME_START,
		eORIGIN_LOADER_X_FLOW_HOME_COMP_CHECK,
		eORIGIN_LOADER_X_FLOW_WAIT_POS,
		eORIGIN_LOADER_X_FLOW_WAIT_POS_CHECK,

		_eORIGIN_LOADER_X_FLOW_DONE,
	};
};

