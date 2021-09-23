#pragma once

class COrigin_UnloaderY_Flow : public CBaseFlow
{
public:
	COrigin_UnloaderY_Flow();
	~COrigin_UnloaderY_Flow();

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

	enum eOrigin_UnloaderY_Flow
	{
		_eORIGIN_UNLOADER_Y_FLOW_ERROR = -1,

		_eORIGIN_UNLOADER_Y_FLOW_IDLE = 0,
		_eORIGIN_UNLOADER_Y_FLOW_START,
		_eORIGIN_UNLOADER_Y_FLOW_INTERLOCK_CHECK,

		_eORIGIN_UNLOADER_Y_FLOW_HOME_START,
		_eORIGIN_UNLOADER_Y_FLOW_HOME_COMP_CHECK,
		_eORIGIN_UNLOADER_Y_FLOW_WAIT_POS,
		_eORIGIN_UNLOADER_Y_FLOW_WAIT_POS_CHECK,

		_eORIGIN_UNLOADER_Y_FLOW_DONE,
	};
};

