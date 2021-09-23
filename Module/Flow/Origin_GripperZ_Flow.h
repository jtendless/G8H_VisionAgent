#pragma once

class COrigin_GripperZ_Flow : public CBaseFlow
{
public:
	COrigin_GripperZ_Flow();
	~COrigin_GripperZ_Flow();

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

	enum_REMOTE_AXIS eRemoteAxis;

	enum eOrigin_GripperZ_Flow
	{
		_eORIGIN_GRIPPER_Z_FLOW_ERROR = -1,

		_eORIGIN_GRIPPER_Z_FLOW_IDLE = 0,
		_eORIGIN_GRIPPER_Z_FLOW_START,
		_eORIGIN_GRIPPER_Z_FLOW_INTERLOCK_CHECK,

#pragma region //GripperZ Home
		eORIGIN_GRIPPER_Z_FLOW_CLAMP_OFF,
		eORIGIN_GRIPPER_Z_FLOW_CLAMP_OFF_CHECK,
		eORIGIN_GRIPPER_Z_FLOW_HOME_START,
		eORIGIN_GRIPPER_Z_FLOW_HOME_COMP_CHECK,
		eORIGIN_GRIPPER_Z_FLOW_MOVE_WAIT_POS,
		eORIGIN_GRIPPER_Z_FLOW_MOVE_WAIT_POS_CHECK,
#pragma endregion

		_eORIGIN_GRIPPER_Z_FLOW_DONE,
	};
};

