#pragma once

class CCstRecvDoneFlow : public CBaseFlow
{
public:
	CCstRecvDoneFlow();
	~CCstRecvDoneFlow();

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

	enum eCstRecvReadyFlow
	{
		_eCST_RECV_DONE_FLOW_ERROR = -1,
		_eCST_RECV_DONE_FLOW_IDLE = 0,
		_eCST_RECV_DONE_FLOW_START,
		_eCST_RECV_DONE_FLOW_INTERLOCK_CHECK,

		_eCST_RECV_DONE_FLOW_CST_PICKUP_UNIT_FWD_2ND,
		_eCST_RECV_DONE_FLOW_CST_PICKUP_UNIT_FWD_2ND_CHECK,
		_eCST_RECV_DONE_FLOW_CST_PICKUP_UNIT_UNCLMAP_2ND,
		_eCST_RECV_DONE_FLOW_CST_PICKUP_UNIT_UNCLMAP_2ND_CHECK,
		_eCST_RECV_DONE_FLOW_CST_PICKUP_UNIT_BWD_2ND,
		_eCST_RECV_DONE_FLOW_CST_PICKUP_UNIT_BWD_2ND_CHECK,
				
		_eCST_RECV_DONE_FLOW_DONE,
	};
};

