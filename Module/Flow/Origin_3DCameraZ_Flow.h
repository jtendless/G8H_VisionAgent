#pragma once

class COrigin_3DCameraZ_Flow : public CBaseFlow
{
public:
	COrigin_3DCameraZ_Flow();
	~COrigin_3DCameraZ_Flow();

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

	enum eOrigin_3DCameraZ_Flow
	{
		_eORIGIN_3D_CAMERA_Z_FLOW_IDLE = 0,
		_eORIGIN_3D_CAMERA_Z_FLOW_START,
		_eORIGIN_3D_CAMERA_Z_FLOW_INTERLOCK_CHECK,

		eGANTRY_MOTION_3D_CAMERA_Z_HOME_START,
		eGANTRY_MOTION_3D_CAMERA_Z_HOME_CHECK,
		eGANTRY_MOTION_3D_CAMERA_Z_WAIT_POS,
		eGANTRY_MOTION_3D_CAMERA_Z_WAIT_POS_CHECK,

		_eORIGIN_3D_CAMERA_Z_FLOW_ERROR,
		_eORIGIN_3D_CAMERA_Z_FLOW_DONE,
		_eORIGIN_3D_CAMERA_Z_FLOW_STOP,
	};
};

