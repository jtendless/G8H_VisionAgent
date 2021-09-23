#pragma once
#include "../Module/Motion/BaseMotion.h"

class COrigin_AllAxis_Flow : public CBaseFlow
{
public:
	COrigin_AllAxis_Flow();
	~COrigin_AllAxis_Flow();

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
	CBaseMotion*	m_Motion;

	int		m_nHomingAxis;
	double m_HomeStartPos;
	int m_stepFlag;
	enum eOrigin_AllAxis_Flow
	{
		_eORIGIN_ALL_AXIS_FLOW_ERROR = -1,
		_eORIGIN_ALL_AXIS_FLOW_IDLE = 0,
		_eORIGIN_ALL_AXIS_FLOW_START,
		_eORIGIN_ALL_AXIS_FLOW_INTERLOCK_CHECK,

		//DOUT SETTING
		eORIGIN_ALL_AXIS_DOUT_SET,
		eORIGIN_ALL_AXIS_SERVO_OFF,
		eORIGIN_ALL_AXIS_SERVO_OFF_CHECK,
		eORIGIN_ALL_AXIS_SERVO_ON,
		eORIGIN_ALL_AXIS_SERVO_ON_CHECK,

		eORIGIN_ALL_AXIS_Z1_HOME,
		eORIGIN_ALL_AXIS_Z2_HOME,
		eORIGIN_ALL_AXIS_Z1_HOME_CHECK,
		eORIGIN_ALL_AXIS_Z2_HOME_CHECK,
					
		_eORIGIN_ALL_AXIS_FLOW_DONE,
	};
};

