#pragma once
class CMeasureCdFlow : public CBaseFlow
{
public:
	CMeasureCdFlow();
	~CMeasureCdFlow();

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

	CString m_strPath;

#ifndef SIM_MODE
	wk_MilCameraInfo m_CameraInfo;
	wk_MilBlobData m_BlobData;
	stBlobResult stResult;
#endif

	CTime m_timeStart; //KJT 20210329

	int		m_nGrabRetryCnt;

	double m_dTargetPosX;
	double m_dTargetPosY;

	int m_nMeasureCountMax;
	int m_nMeasurePoint;
	double m_dMeasurePosXY[2][100];

	double m_VisionResultCdValue[2][100];

	BOOL			FlowInterlock();

	BOOL SaveMeaureCdResult();

	int m_nMeasureType = 0;

	enum eMeasureCdFlow
	{
		_eMEASURE_CD_FLOW_ERROR = -1,

		_eMEASURE_CD_FLOW_IDLE = 0,
		_eMEASURE_CD_FLOW_START,
		_eMEASURE_CD_FLOW_INTERLOCK,

#pragma region //Unloader Ready
		_eMEASURE_CD_FLOW_UNLOADER_READY,
		_eMEASURE_CD_FLOW_UNLOADER_READY_CHECK,
#pragma endregion

#pragma region //Gantry ZX Ready
		_eMEASURE_CD_FLOW_GANTRY_ZX_READY,
		_eMEASURE_CD_FLOW_GANTRY_ZX_READY_CHECK,
#pragma endregion

#pragma region //Loader Ready
		_eMEASURE_CD_FLOW_LOADER_READY,
		_eMEASURE_CD_FLOW_LOADER_READY_CHECK,
#pragma endregion

#pragma region //PaperUnloader Ready
		_eMEASURE_CD_FLOW_PAPER_UNLOADER_ZXY_READY,
		_eMEASURE_CD_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK,
#pragma endregion

		_eMEASURE_CD_FLOW_GANTRY_XY_MEASURE_POS_1ST,
		_eMEASURE_CD_FLOW_GANTRY_XY_MEASURE_POS_1ST_CHECK,
		_eMEASURE_CD_FLOW_GANTRY_Z1_MEASURE_POS,
		_eMEASURE_CD_FLOW_GANTRY_Z1_MEASURE_POS_CHECK,
		_eMEASURE_CD_FLOW_GANTRY_XY_MEASURE_POS_2ND,
		_eMEASURE_CD_FLOW_GANTRY_XY_MEASURE_POS_2ND_CHECK,
		_eMEASURE_CD_FLOW_AUTOFOCUS_CHECK,
		_eMEASURE_CD_FLOW_LASER_FOCUS_START,
		_eMEASURE_CD_FLOW_LASER_FOCUS_CHECK,
		_eMEASURE_CD_FLOW_IMAGE_FOCUS_START,
		_eMEASURE_CD_FLOW_IMAGE_FOCUS_CHECK,
		_eMEASURE_CD_FLOW_GRAB_START,
		_eMEASURE_CD_FLOW_GRAB_DONE_CHECK,
		_eMEASURE_CD_FLOW_FINISH_GANTRY_Z1_WAIT_POS,
		_eMEASURE_CD_FLOW_FINISH_GANTRY_Z1_WAIT_POS_CHECK,
		_eMEASURE_CD_FLOW_FINISH_GANTRY_XY_WAIT_POS,
		_eMEASURE_CD_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK,

		_eMEASURE_CD_FLOW_DONE,
	};
};

