#pragma once

class COrigin_LoaderSubZ_Flow : public CBaseFlow
{
public:
	COrigin_LoaderSubZ_Flow();
	~COrigin_LoaderSubZ_Flow();

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
	enum_REMOTE_AXIS eRemoteAxis2;

	enum eOrigin_LoaderSubZ_Flow
	{
		_eORIGIN_LOADER_SUB_Z_FLOW_ERROR = -1,

		_eORIGIN_LOADER_SUB_Z_FLOW_IDLE = 0,
		_eORIGIN_LOADER_SUB_Z_FLOW_START,
		_eORIGIN_LOADER_SUB_Z_FLOW_INTERLOCK_CHECK,

		eORIGIN_LOADER_SUB_Z_FLOW_HOME_START,
		eORIGIN_LOADER_SUB_Z_FLOW_HOME_COMP_CHECK,
		eORIGIN_LOADER_SUB_Z_FLOW_WAIT_POS,
		eORIGIN_LOADER_SUB_Z_FLOW_WAIT_POS_CHECK,

		_eORIGIN_LOADER_SUB_Z_FLOW_DONE,
	};
};

