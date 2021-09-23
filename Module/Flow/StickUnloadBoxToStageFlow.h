#pragma once

class CStickUnloadBoxToStageFlow : public CBaseFlow
{
public:
	CStickUnloadBoxToStageFlow();
	~CStickUnloadBoxToStageFlow();

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

	BOOL			Start();
	BOOL			Stop();

	double			m_dTargetPosZ;
	double			m_dTargetPosX;

	int				m_nGroupStepIndex; //KJT 20210221
	BOOL			m_bGroupStepDone[200]; //KJT 20210221

	int             m_nMaxStepDownCount;
	int				m_nMaxVibrationCount; //KJT 20210317
	int             m_nStepDownCount;
	int				m_nVibrationCount; //KJT 20210317

	CTime			m_timeStart; //KJT 20210329

	BOOL			FlowInterlock();

	//[2]
	enum eStickUnloadBoxToStage
	{
		_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_ERROR = -1,

		_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_IDLE = 0,
		_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_START,
		_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_INTERLOCK, //INSPECTION STAGE VAC OFF ��ƽ ���� üũ.������ ERROR

#pragma region //2. Unload To Inspection Stage
		_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_INSPECTION_UVW_STICK_LOAD_POS,
		_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_INSPECTION_UVW_STICK_LOAD_POS_CHECK,
		_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_Y_STICK_UNLOAD_TO_INSPECTION_STAGE_POS,
		_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_Y_STICK_UNLOAD_TO_INSPECTION_STAGE_POS_CHECK,
		_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_UNLOAD_DOWN_POS,
		_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_Z_STICK_UNLOAD_DOWN_POS_CHECK,
		_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_INSPECTION_STAGE_VAC_ON,
		_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_INSPECTION_STAGE_VAC_ON_CHECK,
		_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_VAC_OFF,
		_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_VAC_OFF_CHECK,
		_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_Z_FINISH_WAIT_POS,
		_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_Z_FINISH_WAIT_POS_CHECK,
		_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_X_FINISH_WAIT_POS,
		_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_X_FINISH_WAIT_POS_CHECK,
		_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_Y_FINISH_WAIT_POS,
		_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_LOADER_Y_FINISH_WAIT_POS_CHECK,
#pragma endregion //2. Unload To Inspection Stage

		_eSTICK_UNLOAD_BOX_TO_STAGE_FLOW_DONE,
	};
};

