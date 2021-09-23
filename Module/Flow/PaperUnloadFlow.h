#pragma once
class CPaperUnloadFlow : public CBaseFlow
{
public:
	CPaperUnloadFlow();
	~CPaperUnloadFlow();

private:
	CWinThread*		pThread;
	VOID			ThreadFunctionEntry(VOID);
	static UINT		ThreadFunction(LPVOID lpParam);
	BOOL			m_FlowFinish;
	BOOL			m_bFlowDone;
	BOOL			m_bStopBit;
	void(*m_StateComplete)(void *pArgument);

public:
	BOOL			InitProcess();
	BOOL			EndProcess();

	HANDLE			hHandle;
	BOOL			m_bTerminate;
	BOOL			IsTerminate() { return m_bTerminate; }
	BOOL			IsFlowDone() { return m_bFlowDone; }

	BOOL			Start(enum_CassetteFloor eTargetFloor);
	BOOL			Stop();
	
	//double			m_dTargetPosZ;
	double			m_dTargetPosZ;
	double			m_dTargetPosX;

	int				m_nGroupStepIndex; //KJT 20210221
	BOOL			m_bGroupStepDone[200]; //KJT 20210221

	int             m_nMaxStepDownCount;
	int				m_nMaxVibrationCount; //KJT 20210317
	int             m_nStepDownCount;
	int				m_nVibrationCount; //KJT 20210317

	CTime m_timeStart; //KJT 20210329

	enum_CassetteFloor m_eTargetFloor;

	BOOL			FlowInterlock();

	enum ePaperUnload
	{
		_ePAPER_UNLOAD_FLOW_ERROR = -1,

		_ePAPER_UNLOAD_FLOW_IDLE = 0,
		_ePAPER_UNLOAD_FLOW_START,
		_ePAPER_UNLOAD_FLOW_INTERLOCK,

#pragma region //1. Paper Unload
		_ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_Y_PAPER_UNLOAD_POS,
		_ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_Y_PAPER_UNLOAD_POS_CHECK,
		_ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_Z_PAPER_UNLOAD_DOWN_POS,
		_ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_Z_PAPER_UNLOAD_DOWN_POS_CHECK,
		_ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_VAC_OFF,
		_ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_VAC_OFF_CHECK,
		_ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_Z_FINISH_WAIT_POS,		
		_ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_Z_FINISH_WAIT_POS_CHECK,
		_ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_Y_FINISH_WAIT_POS,
		_ePAPER_UNLOAD_FLOW_PAPER_UNLOADER_Y_FINISH_WAIT_POS_CHECK,
#pragma endregion //1. Paper Unload

#pragma region //Cst Move
		_ePAPER_UNLOAD_FLOW_CST_RECV_READY_MOVE,
		_ePAPER_UNLOAD_FLOW_CST_RECV_READY_DONE_CHECK,
		_ePAPER_UNLOAD_FLOW_CST_RECV_DONE_MOVE,
		_ePAPER_UNLOAD_FLOW_CST_RECV_DONE_DONE_CHECK,
#pragma endregion

		_ePAPER_UNLOAD_FLOW_DONE,
	};
};

