#pragma once
class CStickLoadInCstToStageFlow : public CBaseFlow
{
public:
	CStickLoadInCstToStageFlow();
	~CStickLoadInCstToStageFlow();

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

	BOOL			Start(int nStep);
	BOOL			Stop();

	BOOL			FlowInterlock();

	double			m_dTargetPosUldZ;
	double			m_dTargetPosUldX;
	double			m_dTargetPosUldY;

	enum eStickLoadInCstToStageFlow
	{
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_ERROR = -1,

		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_IDLE = 0,
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_START,
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_INTERLOCK,

#pragma region //Unloader Ready
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_READY,
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_READY_CHECK,
#pragma endregion

#pragma region //Loader Ready
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_LOADER_READY,
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_LOADER_READY_CHECK,
#pragma endregion

#pragma region //Box Camera Ready
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_BOX_CAMERA_READY,
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_BOX_CAMERA_READY_CHECK,
#pragma endregion

#pragma region //Gantry Z, XY Ready
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_GANTRY_ZXY_READY,
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_GANTRY_ZXY_READY_CHECK,
#pragma endregion

#pragma region //BoxCamY, Inspection Uvw Ready
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_BOX_CAMERA_WAIT_POS,
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_BOX_CAMERA_WAIT_POS_CHECK,
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_INSP_UVW_UNLOAD_POS,
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_INSP_UVW_UNLOAD_POS_CHECK,
#pragma endregion

#pragma region //1. CST Z, PiciupUnit Send Ready
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_Z_SEND_POS,
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_Z_SEND_POS_CHECK,
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_UNCLMAP_1ST,
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_UNCLMAP_1ST_CHECK,
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_FWD_1ST,
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_FWD_1ST_CHECK,
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_CLMAP,
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_CLMAP_CHECK,
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_BWD_1ST,
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_BWD_1ST_CHECK,
#pragma endregion

#pragma region //2. Stick Load In CST
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Y_LOAD_IN_CST_POS,
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Y_LOAD_IN_CST_POS_CHECK,
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Z_LOAD_IN_CST_POS,
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Z_LOAD_IN_CST_CHECK,
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_VAC_ON,
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_STEP_DOWN,
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Z_STICK_LOAD_STEP_DOWN_CHECK,
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_VAC_ON_CHECK,
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Z_WAIT_POS,
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Z_WAIT_POS_CHECK,
#pragma endregion

#pragma region //3. PickupUnit Wait
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_FWD_2ND,
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_FWD_2ND_CHECK,
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_UNCLMAP_2ND,
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_UNCLMAP_2ND_CHECK,
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_BWD_2ND,
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_CST_PICKUP_UNIT_BWD_2ND_CHECK,
#pragma endregion

#pragma region //3. Stick Unload To Stage
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Y_UNLOAD_TO_STAGE_POS,
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Y_UNLOAD_TO_STAGE_POS_CHECK,
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_X_TENSION_POS,
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_X_TENSION_POS_CHECK,
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Z_UNLOAD_TO_STAGE_POS,
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Z_UNLOAD_TO_STAGE_CHECK,
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_VAC_OFF,
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_VAC_OFF_CHECK,
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Z_WAIT_POS_FINISH,
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Z_WAIT_POS_FINISH_CHECK,
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_X_WAIT_POS_FINISH,
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_X_WAIT_POS_FINISH_CHECK,
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Y_WAIT_POS_FINISH,
		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_UNLOADER_Y_WAIT_POS_FINISH_CHECK,
#pragma endregion 

		_eSTICK_LOAD_IN_CST_TO_STAGE_FLOW_DONE,
	};
};

