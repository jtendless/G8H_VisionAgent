#pragma once

class COrigin_BoxCameraYL_Flow : public CBaseFlow
{
public:
	COrigin_BoxCameraYL_Flow();
	~COrigin_BoxCameraYL_Flow();

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

	enum_REMOTE_AXIS_AJIN eRemoteAxis;

	enum eOrigin_BoxCameraYL_Flow
	{
		_eORIGIN_BOX_CAMERA_YL_FLOW_IDLE = 0,
		_eORIGIN_BOX_CAMERA_YL_FLOW_START,
		_eORIGIN_BOX_CAMERA_YL_FLOW_INTERLOCK_CHECK,

		eORIGIN_BOX_CAMERA_YL_FLOW_HOME_START,
		eORIGIN_BOX_CAMERA_YL_FLOW_HOME_COMP_CHECK,
		eORIGIN_BOX_CAMERA_YL_FLOW_WAIT_POS,
		eORIGIN_BOX_CAMERA_YL_FLOW_WAIT_POS_CHECK,

		_eORIGIN_BOX_CAMERA_YL_FLOW_ERROR,
		_eORIGIN_BOX_CAMERA_YL_FLOW_DONE,
		_eORIGIN_BOX_CAMERA_YL_FLOW_STOP,
	};
};

