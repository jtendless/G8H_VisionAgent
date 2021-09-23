#pragma once

class COrigin_MasterSlaveAxis_Flow : public CBaseFlow
{
public:
	COrigin_MasterSlaveAxis_Flow();
	~COrigin_MasterSlaveAxis_Flow();

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

	BOOL			Start(enum_Axis eAxis);
	BOOL			Stop();

	BOOL			FlowInterlock();

	enum_Axis m_eAxis_Master;
	enum_Axis m_eAxis_Slave;
	int m_nRemoteAxis_Master;
	int m_nRemoteAxis_Slave;
	int m_nAxisType;

	double m_dSyncPos;

	enum eOrigin_MasterSlaveAxis_Flow
	{
		_eORIGIN_MASTER_SLAVE_AXIS_FLOW_ERROR = -1,

		_eORIGIN_MASTER_SLAVE_AXIS_FLOW_IDLE = 0,
		_eORIGIN_MASTER_SLAVE_AXIS_FLOW_START,
		_eORIGIN_MASTER_SLAVE_AXIS_FLOW_INTERLOCK_CHECK,

		_eORIGIN_MASTER_SLAVE_AXIS_FLOW_HOME_START,
		_eORIGIN_MASTER_SLAVE_AXIS_FLOW_HOME_COMP_CHECK,
		_eORIGIN_MASTER_SLAVE_AXIS_FLOW_SYNC_POS,
		_eORIGIN_MASTER_SLAVE_AXIS_FLOW_SYNC_POS_CHECK,

		_eORIGIN_MASTER_SLAVE_AXIS_FLOW_DONE,
	};
};

