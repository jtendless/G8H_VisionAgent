#pragma once
class COrigin_Stretch_Flow : public CBaseFlow
{
public:
	COrigin_Stretch_Flow();
	~COrigin_Stretch_Flow();

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

	enum eOrigin_Stretch_Flow
	{
		_eORIGIN_STRETCH_FLOW_ERROR = -1,

		_eORIGIN_STRETCH_FLOW_IDLE = 0,
		_eORIGIN_STRETCH_FLOW_START,
		_eORIGIN_STRETCH_FLOW_INTERLOCK_CHECK,

		_eORIGIN_STRETCH_FLOW_CLAMP_OFF,
		_eORIGIN_STRETCH_FLOW_CLAMP_OFF_CHECK,

		_eORIGIN_STRETCH_FLOW_SERVO_OFF,
		_eORIGIN_STRETCH_FLOW_SERVO_OFF_CHECK,
		_eORIGIN_STRETCH_FLOW_SERVO_ON,
		_eORIGIN_STRETCH_FLOW_SERVO_ON_CHECK,
		_eORIGIN_STRETCH_FLOW_HOME_MOVE,
		_eORIGIN_STRETCH_FLOW_HOME_BIT_OFF_CHECK,
		_eORIGIN_STRETCH_FLOW_HOME_COMP_CHECK,
		_eORIGIN_STRETCH_FLOW_WAIT_POS_MOVE,
		_eORIGIN_STRETCH_FLOW_WAIT_POS_CHECK,

		_eORIGIN_STRETCH_FLOW_DONE,
	};
};

