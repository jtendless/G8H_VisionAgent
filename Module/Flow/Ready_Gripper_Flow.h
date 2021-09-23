#pragma once

class CReady_Gripper_Flow : public CBaseFlow
{
public:
	CReady_Gripper_Flow();
	~CReady_Gripper_Flow();

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

	BOOL			Start();
	BOOL			Stop();

	BOOL			FlowInterlock();

	enum eReady_Gripper_Flow
	{
		_eREADY_GRIPPER_FLOW_ERROR = -1,
		_eREADY_GRIPPER_FLOW_IDLE = 0,
		_eREADY_GRIPPER_FLOW_START,
		_eREADY_GRIPPER_FLOW_INTERLOCK_CHECK,

		_eREADY_GRIPPER_FLOW_GRIPPER_CLAMP_OFF,
		_eREADY_GRIPPER_FLOW_GRIPPER_CLAMP_OFF_CHECK,
		_eREADY_GRIPPER_FLOW_GRIPPER_STRETCH_WAIT_POS,
		_eREADY_GRIPPER_FLOW_GRIPPER_STRETCH_WAIT_POS_CHECK,
		_eREADY_GRIPPER_FLOW_GRIPPER_Z_WAIT_POS,
		_eREADY_GRIPPER_FLOW_GRIPPER_Z_WAIT_POS_CHECK,
		
		_eREADY_GRIPPER_FLOW_DONE,
	};
};

