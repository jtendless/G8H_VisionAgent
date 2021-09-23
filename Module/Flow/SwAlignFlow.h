#pragma once

class CSwAlignFlow : public CBaseFlow
{
public:
	CSwAlignFlow();
	~CSwAlignFlow();

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

	////
	double m_AlignPointValue[2][4];
	double m_AlignVisionResultValue[2][4];
	double m_SwAlignPointValue[2][4];//KJT 20210305

	double m_dDiffPos[3];
	double m_dTarget[3];

	int m_nAlignPoint;

	double m_dTargetPosX;
	double m_dTargetPosY;

	double GetAlignPos_X(int nAlignCount);
	double GetAlignPos_Y(int nAlignCount);

	BOOL m_bUpdateSWAlignData;
	BOOL m_bVerify;
	BOOL m_bVerifyFirst;

	//KJT 20210419
	int m_nGrabRetryCnt = 0;
#ifndef SIM_MODE
	stModCirclePara ModCirclePara;
	wk_MilModelFindData m_ModelFindData;
	wk_MilCameraInfo m_CameraInfo;
	wk_MilBlobData	m_BlobData;
	stModResult m_ModResult;
#endif

	enum_SwAlignType m_eSwAlignType; //KJT 20210419

	//void UpdateSwAlignData();

	double dCmdPointXY[4][2] = { {0.0, }, };
	double dActPointXY[4][2] = { {0.0, }, };

	enum eSwAlign
	{
		_eSW_ALIGN_FLOW_ERROR = -1,

		_eSW_ALIGN_FLOW_IDLE = 0,
		_eSW_ALIGN_FLOW_START,
		_eSW_ALIGN_FLOW_INTERLOCK,

#pragma region //Unloader Ready
		_eSW_ALIGN_FLOW_UNLOADER_READY,
		_eSW_ALIGN_FLOW_UNLOADER_READY_CHECK,
#pragma endregion

#pragma region //Gantry Z, X Ready
		_eSW_ALIGN_FLOW_GANTRY_ZX_READY,
		_eSW_ALIGN_FLOW_GANTRY_ZX_READY_CHECK,
#pragma endregion

#pragma region //Loader Ready
		_eSW_ALIGN_FLOW_LOADER_READY,
		_eSW_ALIGN_FLOW_LOADER_READY_CHECK,
#pragma endregion

#pragma region //PaperUnloader Ready
		_eSW_ALIGN_FLOW_PAPER_UNLOADER_ZXY_READY,
		_eSW_ALIGN_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK,
#pragma endregion

		_eSW_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST,
		_eSW_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK,
		//_eSW_ALIGN_FLOW_GANTRY_Z1_INSPECTION_POS_1ST,
		//_eSW_ALIGN_FLOW_GANTRY_Z1_INSPECTION_POS_1ST_CHECK,
		_eSW_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_1ST,
		_eSW_ALIGN_FLOW_GANTRY_Z3_INSPECTION_POS_1ST_CHECK,

		//_eSW_ALIGN_FLOW_GANTRY_Z1_INSPECTION_POS_2ND,
		//_eSW_ALIGN_FLOW_GANTRY_Z1_INSPECTION_POS_2ND_CHECK,
		_eSW_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND,
		_eSW_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK,
		_eSW_ALIGN_FLOW_AUTOFOCUS_CHECK,
		_eSW_ALIGN_FLOW_LASER_FOCUS_START,
		_eSW_ALIGN_FLOW_LASER_FOCUS_CHECK,
		_eSW_ALIGN_FLOW_IMAGE_FOCUS_START,
		_eSW_ALIGN_FLOW_IMAGE_FOCUS_CHECK,
		_eSW_ALIGN_FLOW_GRAB_START,
		_eSW_ALIGN_FLOW_GRAB_DONE_CHECK,
		//_eSW_ALIGN_FLOW_FINISH_GANTRY_Z1_WAIT_POS,
		//_eSW_ALIGN_FLOW_FINISH_GANTRY_Z1_WAIT_POS_CHECK,
		_eSW_ALIGN_FLOW_FINISH_GANTRY_Z3_WAIT_POS,
		_eSW_ALIGN_FLOW_FINISH_GANTRY_Z3_WAIT_POS_CHECK,
		_eSW_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS,
		_eSW_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK,

		_eSW_ALIGN_FLOW_DONE,
	};
};

