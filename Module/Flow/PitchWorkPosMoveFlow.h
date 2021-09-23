#pragma once
class CPitchWorkPosMoveFlow : public CBaseFlow
{
public:
	CPitchWorkPosMoveFlow();
	~CPitchWorkPosMoveFlow();

private:
	BOOL			m_FlowFinish;

	void(*m_StateComplete)(void *pArgument);

	CWinThread*		pThread;
	VOID			ThreadFunctionEntry(VOID);
	static UINT		ThreadFunction(LPVOID lpParam);

public:
	BOOL			m_bFlowDone;
	BOOL			m_bStopBit;

	BOOL			InitProcess();
	BOOL			EndProcess();

	HANDLE			hHandle;
	BOOL			m_bTerminate;
	BOOL			IsTerminate() { return m_bTerminate; }
	BOOL			IsFlowDone() { return m_bFlowDone; }

	BOOL			Start(int nStep);
	BOOL			Stop();

	BOOL			FlowInterlock();

	int m_nCurAxisRowIndex;
	enum_REMOTE_AXIS_AJIN m_eRemoteAxisPitch_L[eGRIPPER_ROW_MAX];
	enum_REMOTE_AXIS_AJIN m_eRemoteAxisPitch_R[eGRIPPER_ROW_MAX];
	BOOL m_bLimitSignal_L[eGRIPPER_ROW_MAX];
	BOOL m_bLimitSignal_R[eGRIPPER_ROW_MAX];
	double m_dVel[eGRIPPER_ROW_MAX];

	double dWorkPos_L[eGRIPPER_ROW_MAX] = { 0.0, };
	double dWorkPos_R[eGRIPPER_ROW_MAX] = { 0.0, };

	int m_nFirstUseRowIndex;
	int m_nLastUseRowIndex;
	int m_nStickWingLastIndex;

	enum ePitchWorkPosMoveFlow
	{
		_ePITCH_WORK_POS_MOVE_FLOW_IDLE = 0,
		_ePITCH_WORK_POS_MOVE_FLOW_START,
		_ePITCH_WORK_POS_MOVE_FLOW_INTERLOCK_CHECK,

		_ePITCH_WORK_POS_MOVE_FLOW_UNUSE_ROW_UP_P_LIMIT_POS,
		_ePITCH_WORK_POS_MOVE_FLOW_UNUSE_ROW_UP_P_LIMIT_POS_CHECK,
		_ePITCH_WORK_POS_MOVE_FLOW_UNUSE_ROW_DOWN_N_LIMIT_POS,
		_ePITCH_WORK_POS_MOVE_FLOW_UNUSE_ROW_DOWN_N_LIMIT_POS_CHECK,
		_ePITCH_WORK_POS_MOVE_FLOW_USE_ROW_WORK_POS,
		_ePITCH_WORK_POS_MOVE_FLOW_USE_ROW_WORK_POS_CHECK,

		_ePITCH_WORK_POS_MOVE_FLOW_ERROR,
		_ePITCH_WORK_POS_MOVE_FLOW_DONE,
		_ePITCH_WORK_POS_MOVE_FLOW_STOP,
	};
};

