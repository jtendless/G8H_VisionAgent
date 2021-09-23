#pragma once

class CAutoLaserFocusFlow : public CBaseFlow
{
public:
	CAutoLaserFocusFlow();
	~CAutoLaserFocusFlow();

private:
	BOOL			m_FlowFinish;

	void(*m_StateComplete)(void *pArgument);

	CWinThread*		pThread;
	VOID			ThreadFunctionEntry(VOID);
	static UINT		ThreadFunction(LPVOID lpParam);

public:
	BOOL			m_bFlowDone;
	BOOL			m_bStopBit;

	BOOL			m_bReadyDone;

	BOOL InitProcess();
	BOOL EndProcess();

	HANDLE			hHandle;
	BOOL			m_bTerminate;
	BOOL			IsTerminate() { return m_bTerminate; }
	BOOL			IsFlowDone() { return m_bFlowDone; }
	BOOL			IsReadyDone() { return m_bReadyDone; }

	BOOL			Start();

	BOOL			FocusStart();

	BOOL			Stop();

	CTime m_timeStart;
	CTime m_timeCycleStart;

	enum eAutoLaserFocusFlow
	{
		_eAUTO_LASER_FOCUS_FLOW_ERROR = -1,

		_eAUTO_LASER_FOCUS_FLOW_IDLE = 0,
		_eAUTO_LASER_FOCUS_FLOW_START,

		_eAUTO_LASER_FOCUS_FLOW_CONNECT_CHECK,

		_eAUTO_LASER_FOCUS_FLOW_MOTOR_CHECK,
		_eAUTO_LASER_FOCUS_FLOW_MOTOR_HOME_STATUS_CHECK,

		_eAUTO_LASER_FOCUS_FLOW_MOTOR_ON,
		_eAUTO_LASER_FOCUS_FLOW_MOTOR_ON_CHECK,
		_eAUTO_LASER_FOCUS_FLOW_MOTOR_HOME,
		_eAUTO_LASER_FOCUS_FLOW_MOTOR_HOME_CHECK,

		_eAUTO_LASER_FOCUS_FLOW_DEFAULT_CAMERA_CHECK,

		_eAUTO_LASER_FOCUS_FLOW_DEFAULT_CAMERA_SET,
		_eAUTO_LASER_FOCUS_FLOW_DEFAULT_CAMERA_SET_CHECK,

		_eAUTO_LASER_FOCUS_FLOW_LASER_CHECK,
		_eAUTO_LASER_FOCUS_FLOW_LASER_ON,
		_eAUTO_LASER_FOCUS_FLOW_LASER_ON_CHECK,

		_eAUTO_LASER_FOCUS_FLOW_AUTOFOCUS_ON,
		_eAUTO_LASER_FOCUS_FLOW_AUTOFOCUS_ON_CHECK,

		_eAUTO_LASER_FOCUS_FLOW_AUTOFOCUS_OFF,
		_eAUTO_LASER_FOCUS_FLOW_AUTOFOCUS_OFF_CHECK,

		_eAUTO_LASER_FOCUS_FLOW_DONE,
	};
};

