#pragma once
class CAOIDefectPosMoveOnceFlow : public CBaseFlow
{
public:
	CAOIDefectPosMoveOnceFlow();
	~CAOIDefectPosMoveOnceFlow();

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

	BOOL			Start(double dPosX, double dPosY, BOOL bBackLightWith);
	BOOL			Stop();

	CTime m_timeStart; //KJT 20210329

	BOOL			FlowInterlock();

	double m_dTargetPosX;
	double m_dTargetPosY;
	BOOL m_bBackLightWith;

	enum eAOIDefectPosMoveOnceFlow
	{
		_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_ERROR = -1,

		_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_IDLE = 0,
		_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_START,
		_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_INTERLOCK_CHECK,

#pragma region //Unloader Ready
		_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_UNLOADER_READY,
		_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_UNLOADER_READY_CHECK,
#pragma endregion

#pragma region //Loader Ready
		_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_LOADER_READY,
		_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_LOADER_READY_CHECK,
#pragma endregion

#pragma region //Box Camera Ready
		//_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_BOX_CAMERA_READY,
		//_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_BOX_CAMERA_READY_CHECK,
#pragma endregion

#pragma region //Gantry Z,X Ready
		_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_GANTRY_ZX_READY,
		_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_GANTRY_ZX_READY_CHECK,
#pragma endregion

		_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_GANTRY_XY_MOVE_POS,
		_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_GANTRY_XY_MOVE_POS_CHECK,
		_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_GANTRY_Z_MOVE_INSPECTION_POS,
		_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_GANTRY_Z_MOVE_INSPECTION_POS_CHECK,
		//_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_LASER_FOCUS_START,
		//_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_LASER_FOCUS_CHECK,
		//_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_IMAGE_FOCUS_START,
		//_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_IMAGE_FOCUS_CHECK,
		_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_ZOOM_20X_MOVE,
		_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_ZOOM_20X_MOVE_CHECK,

		_eAOI_DEFECT_POS_MOVE_ONCE_FLOW_DONE,
	};
};

