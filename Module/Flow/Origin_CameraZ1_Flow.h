#pragma once

class COrigin_CameraZ1_Flow : public CBaseFlow
{
public:
	COrigin_CameraZ1_Flow();
	~COrigin_CameraZ1_Flow();

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

	int		m_nHomingAxis;
	double m_HomeStartPos;

	enum eOrigin_CameraZ1_Flow
	{
		_eORIGIN_CAMERA_Z1_FLOW_ERROR = -1,

		_eORIGIN_CAMERA_Z1_FLOW_IDLE = 0,
		_eORIGIN_CAMERA_Z1_FLOW_START,
		_eORIGIN_CAMERA_Z1_FLOW_INTERLOCK_CHECK,

		eORIGIN_CAMERA_Z1_FLOW_PLIMIT_POS,
		eORIGIN_CAMERA_Z1_FLOW_PLIMIT_POS_CHECK,
		eORIGIN_CAMERA_Z1_FLOW_PLIMIT_EJECT_POS,
		eORIGIN_CAMERA_Z1_FLOW_PLIMIT_EJECT_POS_CHECK,
		eORIGIN_CAMERA_Z1_FLOW_STOP_CHECK,
		eORIGIN_CAMERA_Z1_FLOW_HOME_START,
		eORIGIN_CAMERA_Z1_FLOW_HOME_COMP_CHECK,
		eORIGIN_CAMERA_Z1_FLOW_WAIT_POS,
		eORIGIN_CAMERA_Z1_FLOW_WAIT_POS_CHECK,

		_eORIGIN_CAMERA_Z1_FLOW_DONE,
	};
};

