#pragma once
class CStickMoveCstToCstFlow : public CBaseFlow
{
public:
	CStickMoveCstToCstFlow();
	~CStickMoveCstToCstFlow();

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

	double			m_dTargetPosUldZ;
	int				m_SourceFloor;
	int				m_SourceSlot;
	int				m_TargetFloor;
	int				m_TargetSlot;

	BOOL			FlowInterlock();

	enum eStickMoveCstToCstFlow
	{
		_eSTICK_MOVE_CST_TO_CST_FLOW_ERROR = -1,

		_eSTICK_MOVE_CST_TO_CST_FLOW_IDLE = 0,
		_eSTICK_MOVE_CST_TO_CST_FLOW_START,
		_eSTICK_MOVE_CST_TO_CST_FLOW_INTERLOCK,

#pragma region //Unloader Ready
		_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_READY,
		_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_READY_CHECK,
#pragma endregion

#pragma region //Loader Ready
		_eSTICK_MOVE_CST_TO_CST_FLOW_LOADER_READY,
		_eSTICK_MOVE_CST_TO_CST_FLOW_LOADER_READY_CHECK,
#pragma endregion

#pragma region //Box Camera Ready
		_eSTICK_MOVE_CST_TO_CST_FLOW_BOX_CAMERA_READY,
		_eSTICK_MOVE_CST_TO_CST_FLOW_BOX_CAMERA_READY_CHECK,
#pragma endregion

#pragma region //Gantry Z, XY Ready
		_eSTICK_MOVE_CST_TO_CST_FLOW_GANTRY_ZXY_READY,
		_eSTICK_MOVE_CST_TO_CST_FLOW_GANTRY_ZXY_READY_CHECK,
#pragma endregion

#pragma region //1. CST Z, PiciupUnit Send Ready
		_eSTICK_MOVE_CST_TO_CST_FLOW_CST_Z_SEND_POS,
		_eSTICK_MOVE_CST_TO_CST_FLOW_CST_Z_SEND_POS_CHECK,
		_eSTICK_MOVE_CST_TO_CST_FLOW_CST_PICKUP_UNIT_UNCLMAP_1ST,
		_eSTICK_MOVE_CST_TO_CST_FLOW_CST_PICKUP_UNIT_UNCLMAP_1ST_CHECK,
		_eSTICK_MOVE_CST_TO_CST_FLOW_CST_PICKUP_UNIT_FWD_1ST,
		_eSTICK_MOVE_CST_TO_CST_FLOW_CST_PICKUP_UNIT_FWD_1ST_CHECK,
		_eSTICK_MOVE_CST_TO_CST_FLOW_CST_PICKUP_UNIT_CLMAP,
		_eSTICK_MOVE_CST_TO_CST_FLOW_CST_PICKUP_UNIT_CLMAP_CHECK,
		_eSTICK_MOVE_CST_TO_CST_FLOW_CST_PICKUP_UNIT_BWD_1ST,
		_eSTICK_MOVE_CST_TO_CST_FLOW_CST_PICKUP_UNIT_BWD_1ST_CHECK,
#pragma endregion

#pragma region //2. Stick Load In CST
		_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_Y_LOAD_IN_CST_POS,
		_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_Y_LOAD_IN_CST_POS_CHECK,
		_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_Z_LOAD_IN_CST_POS,
		_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_Z_LOAD_IN_CST_CHECK,
		_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_VAC_ON,
		_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_STEP_DOWN,
		_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_Z_STICK_LOAD_STEP_DOWN_CHECK,
		_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_VAC_ON_CHECK,
		_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_Z_WAIT_POS,
		_eSTICK_MOVE_CST_TO_CST_FLOW_UNLOADER_Z_WAIT_POS_CHECK,
#pragma endregion

		_eSTICK_MOVE_CST_TO_CST_FLOW_DONE,
	};
};
