#pragma once
class CRepeatMeasureFlow : public CBaseFlow
{
public:
	CRepeatMeasureFlow();
	~CRepeatMeasureFlow();

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
	BOOL			IsFlowDone() { return m_bFlowDone; }

	BOOL			Start(REPEAT_DATA RepeatFlagData);
	BOOL			Stop();

	CTime m_timeStart; //KJT 20210329
	CTime m_timeStart_1Cycle;

	BOOL			FlowInterlock();

	CString path, logpath;
	REPEAT_DATA m_sRepeatFlagData;
	REPEAT_INFO		m_RepeatInfo[4];// [100000];
	int m_nCamNumber;
	int m_nCountDelay;
	int m_nLaserFocusDoneDelay;
	BOOL m_bWithBackLightXMove;

	double m_dTargetPosX;
	double m_dTargetPosY;
	double m_dTargetPosZ;

	double m_dGrabValue[2];
	double m_dGrabScore;
	int		m_nGrabRetryCnt;

	//CD & Corner R
	/////////////////////////////////////////////
#ifndef SIM_MODE
	wk_MilCameraInfo m_CameraInfo;
	wk_MilBlobData m_BlobData;
	stBlobResult stResult;
#endif
	double m_AlignVisionResultCdValue[2];
	double m_AlignVisionResultCornerRValue[25][4];
	///////////////////////////////////////////////////

	void FindBlob();

	int	SaveRepeatResult(REPEAT_INFO result[4], int Repeat, int Position, int Count);

	enum eRepeatMeasureFlow
	{
		_eREPEAT_MEASURE_FLOW_ERROR = -1,

		_eREPEAT_MEASURE_FLOW_IDLE = 0,
		_eREPEAT_MEASURE_FLOW_START,
		_eREPEAT_MEASURE_FLOW_INTERLOCK_CHECK,

#pragma region //Loader Ready
		_eREPEAT_MEASURE_FLOW_LOADER_READY,
		_eREPEAT_MEASURE_FLOW_LOADER_READY_CHECK,
#pragma endregion

#pragma region //Gantry Z,X Ready
		_eREPEAT_MEASURE_FLOW_GANTRY_ZX_READY,
		_eREPEAT_MEASURE_FLOW_GANTRY_ZX_READY_CHECK,
#pragma endregion

#pragma region //Unloader Ready
		_eREPEAT_MEASURE_FLOW_UNLOADER_READY,
		_eREPEAT_MEASURE_FLOW_UNLOADER_READY_CHECK,
#pragma endregion

		_eREPEAT_MEASURE_FLOW_INSPECTION_POS_CHECK,
		_eREPEAT_MEASURE_FLOW_LIGHT_ON,
		_eREPEAT_MEASURE_FLOW_GANTRY_XY_INSPECTION_POS,
		_eREPEAT_MEASURE_FLOW_GANTRY_XY_INSPECTION_POS_CHECK,
		_eREPEAT_MEASURE_FLOW_GANTRY_Z_INSPECTION_POS,
		_eREPEAT_MEASURE_FLOW_GANTRY_Z_INSPECTION_POS_CHECK,
		_eREPEAT_MEASURE_FLOW_LASER_FOCUS_START,
		_eREPEAT_MEASURE_FLOW_LASER_FOCUS_CHECK,
		_eREPEAT_MEASURE_FLOW_IMAGE_FOCUS_START,
		_eREPEAT_MEASURE_FLOW_IMAGE_FOCUS_CHECK,
		_eREPEAT_MEASURE_FLOW_GRAB,
		_eREPEAT_MEASURE_FLOW_GANTRY_Z_FINISH_POS,
		_eREPEAT_MEASURE_FLOW_GANTRY_Z_FINISH_POS_CHECK,
		_eREPEAT_MEASURE_FLOW_GANTRY_X_FINISH_POS,
		_eREPEAT_MEASURE_FLOW_GANTRY_X_FINISH_POS_CHECK,

		_eREPEAT_MEASURE_FLOW_DONE,
	};
};

