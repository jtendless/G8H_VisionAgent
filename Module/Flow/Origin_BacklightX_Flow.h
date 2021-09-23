#pragma once
class COrigin_BacklightX_Flow : public CBaseFlow
{
public:
	COrigin_BacklightX_Flow();
	~COrigin_BacklightX_Flow();

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

	enum_REMOTE_AXIS eRemoteAxis;

	enum eOrigin_BacklightX_Flow
	{
		_eORIGIN_BACKLIGHT_X_FLOW_ERROR = -1,

		_eORIGIN_BACKLIGHT_X_FLOW_IDLE = 0,
		_eORIGIN_BACKLIGHT_X_FLOW_START,
		_eORIGIN_BACKLIGHT_X_FLOW_INTERLOCK_CHECK,

		_eORIGIN_BACKLIGHT_X_FLOW_SERVO_OFF,
		_eORIGIN_BACKLIGHT_X_FLOW_SERVO_OFF_CHECK,
		_eORIGIN_BACKLIGHT_X_FLOW_SERVO_ON,
		_eORIGIN_BACKLIGHT_X_FLOW_SERVO_ON_CHECK,
		_eORIGIN_BACKLIGHT_X_FLOW_HOME_START,
		_eORIGIN_BACKLIGHT_X_FLOW_HOME_BIT_OFF_CHECK,
		_eORIGIN_BACKLIGHT_X_FLOW_HOME_COMP_CHECK,
		_eORIGIN_BACKLIGHT_X_FLOW_WAIT_POS,
		_eORIGIN_BACKLIGHT_X_FLOW_WAIT_POS_CHECK,

		_eORIGIN_BACKLIGHT_X_FLOW_DONE,
	};
};

