#pragma once
class CCameraCalFlow : public CBaseFlow
{
public:
	CCameraCalFlow();
	~CCameraCalFlow();

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
	BOOL			StateStop();

	HANDLE			hHandle;
	BOOL			m_bTerminate;
	BOOL			IsTerminate() { return m_bTerminate; }
	BOOL			IsFlowDone() { return m_bFlowDone; }

	BOOL			Start(int nCalID = eMAPPING_ID_10X);
	BOOL			Stop();

	CTime m_timeStart; //KJT 20210329

	double m_dTargetPosX;
	double m_dTargetPosY;

	CString m_strFilePath;

	int m_nCalID;

	DOUBLE m_dVisionResult[2] = { 0.0, 0.0 };
#ifndef SIM_MODE
	stModCirclePara ModCirclePara;
	wk_MilModelFindData m_ModelFindData;
	wk_MilCameraInfo m_CameraInfo;
	wk_MilBlobData	m_BlobData;
	stModResult m_ModResult;
#endif

	int m_nGrabFailRetryCnt;
	int m_nGrabRetryCnt;

	int m_nCurPoint;
	int m_nMaxRepeatCnt;
	int m_nCurRepeatCnt;

	BOOL m_bCentered;
	double m_dCenterPosX, m_dCenterPosY;
	double m_dOffsetCx, m_dOffsetCy;

	BOOL			FlowInterlock();

	int SaveCameraCalResult(int nRepeatCount);

	enum eCameraCalFlow
	{
		eCAMERA_CAL_FLOW_ERROR = -1,

		eCAMERA_CAL_FLOW_IDLE = 0,
		eCAMERA_CAL_FLOW_START,
		eCAMERA_CAL_FLOW_INTERLOCK,

#pragma region //Unloader Ready
		eCAMERA_CAL_FLOW_UNLOADER_READY,
		eCAMERA_CAL_FLOW_UNLOADER_READY_CHECK,
#pragma endregion

#pragma region //Gantry Z,X Ready
		eCAMERA_CAL_FLOW_GANTRY_ZX_READY,
		eCAMERA_CAL_FLOW_GANTRY_ZX_READY_CHECK,
#pragma endregion

#pragma region //Loader Ready
		eCAMERA_CAL_FLOW_LOADER_READY,
		eCAMERA_CAL_FLOW_LOADER_READY_CHECK,
#pragma endregion

#pragma region //PaperUnloader Ready
		eCAMERA_CAL_FLOW_PAPER_UNLOADER_ZXY_READY,
		eCAMERA_CAL_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK,
#pragma endregion

		eCAMERA_CAL_FLOW_GANTRY_XY_MEASURE_POS_1ST,
		eCAMERA_CAL_FLOW_GANTRY_XY_MEASURE_POS_1ST_CHECK,
		eCAMERA_CAL_FLOW_GANTRY_XY_MEASURE_POS_2ND,
		eCAMERA_CAL_FLOW_GANTRY_XY_MEASURE_POS_2ND_CHECK,
		eCAMERA_CAL_FLOW_CAMERA_Z1_INSPECTION_POS,
		eCAMERA_CAL_FLOW_CAMERA_Z1_INSPECTION_POS_CHECK,
		
		eCAMERA_CAL_FLOW_GANTRY_XY_CENTERING_MOVE,
		eCAMERA_CAL_FLOW_GANTRY_XY_CENTERING_MOVE_DONE_CHECK,

		eCAMERA_CAL_FLOW_AUTOFOCUS_CHECK,
		eCAMERA_CAL_FLOW_LASER_FOCUS_START,
		eCAMERA_CAL_FLOW_LASER_FOCUS_CHECK,
		eCAMERA_CAL_FLOW_IMAGE_FOCUS_START,
		eCAMERA_CAL_FLOW_IMAGE_FOCUS_CHECK,
		eCAMERA_CAL_FLOW_VISION_GRAB_CIRCLE,
		eCAMERA_CAL_FLOW_VISION_GRAB_BLOB,
		eCAMERA_CAL_FLOW_VISION_GRAB_1ST_CHECK,
		eCAMERA_CAL_FLOW_VISION_GRAB_2ND_CHECK,
		eCAMERA_CAL_FLOW_CAL_DATA,

		eCAMERA_CAL_FLOW_FINISH_GANTRY_Z1_WAIT_POS,
		eCAMERA_CAL_FLOW_FINISH_GANTRY_Z1_WAIT_POS_CHECK,
		eCAMERA_CAL_FLOW_FINISH_GANTRY_XY_WAIT_POS,
		eCAMERA_CAL_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK,

		eCAMERA_CAL_FLOW_DONE,
	};
};

