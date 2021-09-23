#pragma once

class CAOIFlow : public CBaseFlow
{
public:
	CAOIFlow();
	~CAOIFlow();

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

	CTime m_timeStart; //KJT 20210329

	BOOL			FlowInterlock();

	int m_nScanLineIndex = 0;
	int m_nMaxScanLineCount = 0;
	double m_dStartPosX;
	double m_dStartPosY;
	double m_dEndPosX;
	double m_dEndPosY;

	double m_dTargetPosX;
	double m_dTargetPosY;

	int m_nRetry;

	enum eAOIFlow
	{
		_eAOI_FLOW_ERROR = -1,

		_eAOI_FLOW_IDLE = 0,
		_eAOI_FLOW_START,
		_eAOI_FLOW_INTERLOCK_CHECK,

#pragma region //Unloader Ready
		_eAOI_FLOW_UNLOADER_READY,
		_eAOI_FLOW_UNLOADER_READY_CHECK,
#pragma endregion

#pragma region //Loader Ready
		_eAOI_FLOW_LOADER_READY,
		_eAOI_FLOW_LOADER_READY_CHECK,
#pragma endregion

#pragma region //Box Camera Ready
		//_eAOI_FLOW_BOX_CAMERA_READY,
		//_eAOI_FLOW_BOX_CAMERA_READY_CHECK,
#pragma endregion

#pragma region //Gantry Z,X Ready
		_eAOI_FLOW_GANTRY_ZX_READY,
		_eAOI_FLOW_GANTRY_ZX_READY_CHECK,
#pragma endregion

		_eAOI_FLOW_INSPECTION_READY_REQ,
		_eAOI_FLOW_INSPECTION_READY_CHECK,
		_eAOI_FLOW_SET_SURFACE_INFO_REQ,
		_eAOI_FLOW_SET_SURFACE_INFO_CHECK,
		_eAOI_FLOW_INSPECTION_START_END_POS_INFO_REQ,
		_eAOI_FLOW_INSPECTION_START_END_POS_INFO_CHECK,
		_eAOI_FLOW_GANTRY_XY_MOVE_TO_INSP_START_POS,
		_eAOI_FLOW_GANTRY_XY_MOVE_TO_INSP_START_POS_CHECK,
		_eAOI_FLOW_GANTRY_Z1_INSP_POS,
		_eAOI_FLOW_GANTRY_Z1_INSP_POS_CHECK,
		_eAOI_FLOW_INSPECTION_START_REQ,
		_eAOI_FLOW_INSPECTION_START_CHECK,
		_eAOI_FLOW_GANTRY_X_MOVE_TO_INSP_END_POS,
		_eAOI_FLOW_GANTRY_X_MOVE_TO_INSP_END_POS_CHECK,
		_eAOI_FLOW_RECV_AOI_DEFECT_INFO_CHECK,
		_eAOI_FLOW_FINISH_GANTRY_Z1_WAIT_POS,
		_eAOI_FLOW_FINISH_GANTRY_Z1_WAIT_POS_CHECK,
		_eAOI_FLOW_FINISH_GANTRY_XY_WAIT_POS,
		_eAOI_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK,

		_eAOI_FLOW_DONE,



	//	[6. AOI]
	//BOX CAMERA Y WAIT POS(CYD CHECK) 항상 일단 WAIT POS 간다

	//	UNLOADER VAC OFF
	//	BLOW ON
	//	BLOW OFF
	//	UNLOADER CYD UP
	//	UNLOADER Z UP
	//	UNLOADER Y WAIT

	//	LOADER VAC OFF
	//	BLOW ON
	//	BLOW OFF
	//	LOADER CYD UP
	//	LOADER Z UP

	//	CAMERA Z ALL UP
	//	GANTRY XY WAIT

	//	CLAMP OFF
	//	GRIPPER UP
	//	STRETCH WAIT
	//	PITCH WAIT

	//	//
	//	BACKLIGHT X AOI START POS(속도가 느려서 Backlight 먼저 움직이는게 낫다)
	//	GANTRY XY AOI START POS
	//	GANTRY Z AOI POS
	//	BACKLIGHT ON
	//	GANTRY XY AOI 1ST LINE START POS
	//	GANTRY XY MOVE RIGHT(MotionAgent 에서 Backlight X 같이 움직이도록 한다.VisionAgent에서 하면 느림)
	//	..
	//	GANTRY XY MOVE DONE
	//	GANTRY Y AOI 2ND LINE START POS MOVE
	//	GANTRY XY MOVE LEFT
	//	...
	//	GANTRY XY MOVE DONE
	//	AOI END
	//	BACKLIGHT OFF

	//	GANTRY Z1 WAIT POS
	//	GANTRY XY WAIT POS
	};
};

