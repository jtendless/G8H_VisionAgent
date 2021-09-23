#pragma once

class CCstRecvReadyFlow : public CBaseFlow
{
public:
	CCstRecvReadyFlow();
	~CCstRecvReadyFlow();

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

	BOOL			Start(enum_CassetteFloor eFloor);
	BOOL			Stop();

	BOOL			FlowInterlock();

	enum_CassetteFloor m_eTargetFloor;

	enum eCstRecvReadyFlow
	{
		_eCST_RECV_READY_FLOW_ERROR = -1,
		_eCST_RECV_READY_FLOW_IDLE = 0,
		_eCST_RECV_READY_FLOW_START,
		_eCST_RECV_READY_FLOW_INTERLOCK_CHECK,

		_eCST_RECV_READY_FLOW_CST_Z_RECV_POS,
		_eCST_RECV_READY_FLOW_CST_Z_RECV_POS_CHECK,
		_eCST_RECV_READY_FLOW_CST_PICKUP_UNIT_UNCLMAP_1ST,
		_eCST_RECV_READY_FLOW_CST_PICKUP_UNIT_UNCLMAP_1ST_CHECK,
		_eCST_RECV_READY_FLOW_CST_PICKUP_UNIT_FWD_1ST,
		_eCST_RECV_READY_FLOW_CST_PICKUP_UNIT_FWD_1ST_CHECK,
		_eCST_RECV_READY_FLOW_CST_PICKUP_UNIT_CLMAP,
		_eCST_RECV_READY_FLOW_CST_PICKUP_UNIT_CLMAP_CHECK,
		_eCST_RECV_READY_FLOW_CST_PICKUP_UNIT_BWD_1ST,
		_eCST_RECV_READY_FLOW_CST_PICKUP_UNIT_BWD_1ST_CHECK,
				
		_eCST_RECV_READY_FLOW_DONE,
	};
};

