#pragma once

class CMaskEdgeAlignFlow : public CBaseFlow
{
public:
	CMaskEdgeAlignFlow();
	~CMaskEdgeAlignFlow();

private:
	BOOL			m_FlowFinish;

	void(*m_StateComplete)(void *pArgument);

	CWinThread*		pThread;
	VOID			ThreadFunctionEntry(VOID);
	static UINT		ThreadFunction(LPVOID lpParam);

private:
#ifndef SIM_MODE
	wk_MilCameraInfo m_CameraInfo;
	wk_MilBlobData m_BlobData;
	stBlobResult stResult;
#endif

public:
	BOOL			m_bFlowDone;
	BOOL			m_bStopBit;

	BOOL InitProcess();
	BOOL EndProcess();

	HANDLE			hHandle;
	BOOL			m_bTerminate;
	BOOL			IsTerminate() { return m_bTerminate; }
	BOOL			IsFlowDone() { return m_bFlowDone; }

	BOOL			Start(int nStep);
	BOOL			Stop();

	CTime m_timeStart; //KJT 20210329

	BOOL			FlowInterlock();

#pragma region //Vision
	double m_AlignPointValue[2][4];
	double m_AlignVisionResultValue[2][4];

	double m_dDiffPos[3];
	double m_dTarget[3];

	int m_nAlignPoint;
	int m_nAlignCnt;
#pragma endregion

	//Uvw
	BOOL GetXYTPos(double *dRefPosX, double *dRefPosY, double *dDiffPosX, double *dDiffPosY, double *ResultX, double *ResultY, double *ResultT);

#pragma region //Move Func
	double m_dTargetPosX;
	double m_dTargetPosY;

	double GetAlignPos_X(int nAlignCount);
	double GetAlignPos_Y(int nAlignCount);
#pragma endregion

	//void UpdateSwAlignData();

	enum eMaskEdgeAlign
	{
		_eMASK_EDGE_ALIGN_FLOW_ERROR = -1,

		_eMASK_EDGE_ALIGN_FLOW_IDLE = 0,
		_eMASK_EDGE_ALIGN_FLOW_START,
		_eMASK_EDGE_ALIGN_FLOW_INTERLOCK,
		
#pragma region //Unloader Ready
		_eMASK_EDGE_ALIGN_FLOW_UNLOADER_READY,
		_eMASK_EDGE_ALIGN_FLOW_UNLOADER_READY_CHECK,
#pragma endregion

#pragma region //Loader Ready
		_eMASK_EDGE_ALIGN_FLOW_LOADER_READY,
		_eMASK_EDGE_ALIGN_FLOW_LOADER_READY_CHECK,
#pragma endregion

#pragma region //Box Camera Ready
		_eMASK_EDGE_ALIGN_FLOW_BOX_CAMERA_READY,
		_eMASK_EDGE_ALIGN_FLOW_BOX_CAMERA_READY_CHECK,
#pragma endregion

#pragma region //Gantry Z, X Ready
		_eMASK_EDGE_ALIGN_FLOW_GANTRY_ZX_READY,
		_eMASK_EDGE_ALIGN_FLOW_GANTRY_ZX_READY_CHECK,
#pragma endregion

		_eMASK_EDGE_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST,
		_eMASK_EDGE_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK,
		//_eMASK_EDGE_ALIGN_FLOW_GANTRY_Z1_INSPECTION_POS_1ST,
		//_eMASK_EDGE_ALIGN_FLOW_GANTRY_Z1_INSPECTION_POS_1ST_CHECK,
		_eMASK_EDGE_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_1ST,
		_eMASK_EDGE_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_1ST_CHECK,

		//_eMASK_EDGE_ALIGN_FLOW_GANTRY_Z1_INSPECTION_POS_2ND,
		//_eMASK_EDGE_ALIGN_FLOW_GANTRY_Z1_INSPECTION_POS_2ND_CHECK,
		_eMASK_EDGE_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_2ND,
		_eMASK_EDGE_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_2ND_CHECK,
		_eMASK_EDGE_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND,
		_eMASK_EDGE_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK,
		_eMASK_EDGE_ALIGN_FLOW_AUTOFOCUS_CHECK,
		_eMASK_EDGE_ALIGN_FLOW_LASER_FOCUS_START,
		_eMASK_EDGE_ALIGN_FLOW_LASER_FOCUS_CHECK,
		_eMASK_EDGE_ALIGN_FLOW_IMAGE_FOCUS_START,
		_eMASK_EDGE_ALIGN_FLOW_IMAGE_FOCUS_CHECK,
		_eMASK_EDGE_ALIGN_FLOW_GRAB_START,
		_eMASK_EDGE_ALIGN_FLOW_GRAB_DONE_CHECK,
		_eMASK_EDGE_ALIGN_FLOW_INSPECTION_UVW_MOVE_START,
		_eMASK_EDGE_ALIGN_FLOW_INSPECTION_UVW_MOVE_DONE_CHECK,
		//_eMASK_EDGE_ALIGN_FLOW_FINISH_GANTRY_Z1_WAIT_POS,
		//_eMASK_EDGE_ALIGN_FLOW_FINISH_GANTRY_Z1_WAIT_POS_CHECK,
		_eMASK_EDGE_ALIGN_FLOW_FINISH_GANTRY_Z3_WAIT_POS,
		_eMASK_EDGE_ALIGN_FLOW_FINISH_GANTRY_Z3_WAIT_POS_CHECK,
		_eMASK_EDGE_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS,
		_eMASK_EDGE_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK,

		_eMASK_EDGE_ALIGN_FLOW_DONE,
	};
};

