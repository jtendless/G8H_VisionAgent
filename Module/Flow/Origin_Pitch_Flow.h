#pragma once

#include "Common/CommonDefine.h"

class COrigin_Pitch_Flow : public CBaseFlow
{
public:
	COrigin_Pitch_Flow();
	~COrigin_Pitch_Flow();

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

	int m_nCurAxisRowIndex;
	int m_nAxisPitch_L[eGRIPPER_ROW_MAX];
	int m_nAxisPitch_R[eGRIPPER_ROW_MAX];
	BOOL bLimitSignal_L[eGRIPPER_ROW_MAX];
	BOOL bLimitSignal_R[eGRIPPER_ROW_MAX];

	double m_HomeStartPos_L, m_HomeStartPos_R;

	int m_nHomeCnt;
	BOOL m_bStatusWaitPos;

	enum eOrigin_Pitch_Flow
	{
		_eORIGIN_PITCH_FLOW_IDLE = 0,
		_eORIGIN_PITCH_FLOW_START,
		_eORIGIN_PITCH_FLOW_INTERLOCK_CHECK,

#pragma region //Pitch Home
		_eORIGIN_PITCH_FLOW_SERVO_OFF,
		_eORIGIN_PITCH_FLOW_SERVO_OFF_CHECK,
		_eORIGIN_PITCH_FLOW_SERVO_ON,
		_eORIGIN_PITCH_FLOW_SERVO_ON_CHECK,
		_eORIGIN_PITCH_FLOW_N_LIMIT_POS,
		_eORIGIN_PITCH_FLOW_N_LIMIT_POS_CHECK,
		_eORIGIN_PITCH_FLOW_N_LIMIT_EJECT_POS,
		_eORIGIN_PITCH_FLOW_N_LIMIT_EJECT_POS_CHECK,
		_eORIGIN_PITCH_FLOW_HOME_MOVE,
		_eORIGIN_PITCH_FLOW_HOME_CHECK,
		_eORIGIN_PITCH_FLOW_WAIT_POS_MOVE,
		_eORIGIN_PITCH_FLOW_WAIT_POS_CHECK,
#pragma endregion

		_eORIGIN_PITCH_FLOW_ERROR,
		_eORIGIN_PITCH_FLOW_DONE,
		_eORIGIN_PITCH_FLOW_STOP,
	};
};

