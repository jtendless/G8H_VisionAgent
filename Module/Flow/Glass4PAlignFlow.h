#pragma once
class CGlass4PAlignFlow : public CBaseFlow
{
public:
	CGlass4PAlignFlow();
	~CGlass4PAlignFlow();

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

	BOOL			m_bPreAlignUse;
	BOOL			m_bPreAlignDone;

	////
	double m_AlignPointValue[2][4];
	double m_AlignVisionResultValue[2][4];

	double m_dDiffPos[3];
	double m_dTarget[3];

	int m_nAlignPoint;

	double m_dTargetPosX;
	double m_dTargetPosY;

	int		m_nGrabRetryCnt;

	double GetGlass4PAlignPos_X_PreAlign(int nAlignCount);
	double GetGlass4PAlignPos_Y_PreAlign(int nAlignCount);
	double GetGlass4PAlignPos_X_Review10X(int nAlignCount);
	double GetGlass4PAlignPos_Y_Review10X(int nAlignCount);
	void SetPreAlignUseMode(BOOL bUse = FALSE);

	enum eGlass4PAlign
	{
		_eGLASS_4P_ALIGN_FLOW_ERROR = -1,

		_eGLASS_4P_ALIGN_FLOW_IDLE = 0,
		_eGLASS_4P_ALIGN_FLOW_START,
		_eGLASS_4P_ALIGN_FLOW_INTERLOCK,

#pragma region //Unloader Ready
		_eGLASS_4P_ALIGN_FLOW_UNLOADER_READY,
		_eGLASS_4P_ALIGN_FLOW_UNLOADER_READY_CHECK,
#pragma endregion

#pragma region //Loader Ready
		_eGLASS_4P_ALIGN_FLOW_LOADER_READY,
		_eGLASS_4P_ALIGN_FLOW_LOADER_READY_CHECK,
#pragma endregion

#pragma region //Box Camera Ready
		_eGLASS_4P_ALIGN_FLOW_BOX_CAMERA_READY,
		_eGLASS_4P_ALIGN_FLOW_BOX_CAMERA_READY_CHECK,
#pragma endregion

#pragma region //Gantry Z, X Ready
		_eGLASS_4P_ALIGN_FLOW_GANTRY_ZX_READY,
		_eGLASS_4P_ALIGN_FLOW_GANTRY_ZX_READY_CHECK,
#pragma endregion

		_eGLASS_4P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST,
		_eGLASS_4P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK,
#pragma region //PreAlign
		_eGLASS_4P_ALIGN_FLOW_GANTRY_Z1_PRE_ALIGN_INSPECTION_POS,
		_eGLASS_4P_ALIGN_FLOW_GANTRY_Z1_PRE_ALIGN_INSPECTION_POS_CHECK,
#pragma endregion

		_eGLASS_4P_ALIGN_FLOW_GANTRY_Z1_REVIEW10X_INSPECTION_POS,
		_eGLASS_4P_ALIGN_FLOW_GANTRY_Z1_REVIEW10X_INSPECTION_POS_CHECK,

		_eGLASS_4P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND,
		_eGLASS_4P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK,

		_eGLASS_4P_ALIGN_FLOW_AUTOFOCUS_CHECK,
		_eGLASS_4P_ALIGN_FLOW_LASER_FOCUS_START,
		_eGLASS_4P_ALIGN_FLOW_LASER_FOCUS_CHECK,
		_eGLASS_4P_ALIGN_FLOW_IMAGE_FOCUS_START,
		_eGLASS_4P_ALIGN_FLOW_IMAGE_FOCUS_CHECK,
		_eGLASS_4P_ALIGN_FLOW_GRAB_START,
		_eGLASS_4P_ALIGN_FLOW_GRAB_DONE_CHECK,
		_eGLASS_4P_ALIGN_FLOW_INSPECTION_UVW_MOVE_START,
		_eGLASS_4P_ALIGN_FLOW_INSPECTION_UVW_MOVE_DONE_CHECK,
		_eGLASS_4P_ALIGN_FLOW_FINISH_GANTRY_Z1_WAIT_POS,
		_eGLASS_4P_ALIGN_FLOW_FINISH_GANTRY_Z1_WAIT_POS_CHECK,
		_eGLASS_4P_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS,
		_eGLASS_4P_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK,

		_eGLASS_4P_ALIGN_FLOW_DONE,
	};
};

