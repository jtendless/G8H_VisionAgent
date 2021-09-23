#pragma once

class CMaskTag4PAlignFlow : public CBaseFlow
{
public:
	CMaskTag4PAlignFlow();
	~CMaskTag4PAlignFlow();

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

	BOOL			Start(int nStep);
	BOOL			Stop();

	CTime m_timeStart; //KJT 20210329

	BOOL			FlowInterlock();

#pragma region //Vision
	BOOL m_bLaserFocusUseFlag;
	BOOL m_bAutoFocusUseFlag;

	double m_AlignPointValue[4][2];
	double m_AlignVisionPreResultValue[4][2];
	double m_AlignVisionResultValue[4][2];

	double m_dDiffPos[3];
	double m_dTarget[3];

	int m_AlignCnt;
#pragma endregion

	//Uvw
	BOOL GetXYTPos(double *dRefPosX, double *dRefPosY, double *dDiffPosX, double *dDiffPosY, double *ResultX, double *ResultY, double *ResultT);

#pragma region //Move Func
	double GetAlignPos_X(int nAlignCount);
	double GetAlignPos_Y(int nAlignCount);
#pragma endregion

	//Review 2Point Align
	enum eMaskTagkey4PAlign
	{
		_eMASK_TAGKEY_4P_ALIGN_FLOW_ERROR = -1,

		_eMASK_TAGKEY_4P_ALIGN_FLOW_IDLE = 0,
		_eMASK_TAGKEY_4P_ALIGN_FLOW_START,
		_eMASK_TAGKEY_4P_ALIGN_FLOW_INTERLOCK,

#pragma region //Unloader Ready
		_eMASK_TAGKEY_4P_ALIGN_FLOW_UNLOADER_READY,
		_eMASK_TAGKEY_4P_ALIGN_FLOW_UNLOADER_READY_CHECK,
#pragma endregion

#pragma region //Loader Ready
		_eMASK_TAGKEY_4P_ALIGN_FLOW_LOADER_READY,
		_eMASK_TAGKEY_4P_ALIGN_FLOW_LOADER_READY_CHECK,
#pragma endregion

#pragma region //Box Camera Ready
		_eMASK_TAGKEY_4P_ALIGN_FLOW_BOX_CAMERA_READY,
		_eMASK_TAGKEY_4P_ALIGN_FLOW_BOX_CAMERA_READY_CHECK,
#pragma endregion

#pragma region //Gantry ZX Ready
		_eMASK_TAGKEY_4P_ALIGN_FLOW_GANTRY_ZX_READY,
		_eMASK_TAGKEY_4P_ALIGN_FLOW_GANTRY_ZX_READY_CHECK,
#pragma endregion

		_eMASK_TAGKEY_4P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS,
		_eMASK_TAGKEY_4P_ALIGN_FLOW_GANTRY_XY_ALIGN_POS_CHECK,
		_eMASK_TAGKEY_4P_ALIGN_FLOW_GANTRY_Z1_ALIGN_POS,
		_eMASK_TAGKEY_4P_ALIGN_FLOW_GANTRY_Z1_ALIGN_POS_CHECK,
		_eMASK_TAGKEY_4P_ALIGN_FLOW_IMAGE_FOCUS_START,
		_eMASK_TAGKEY_4P_ALIGN_FLOW_IMAGE_FOCUS_CHECK,
		_eMASK_TAGKEY_4P_ALIGN_FLOW_4P_GRAB_START,
		_eMASK_TAGKEY_4P_ALIGN_FLOW_4P_UVW_MOVE_START,
		_eMASK_TAGKEY_4P_ALIGN_FLOW_INSPECTION_UVW_MOVE_DONE_CHECK,
		_eMASK_TAGKEY_4P_ALIGN_FLOW_FINISH_GANTRY_Z_WAIT_POS,
		_eMASK_TAGKEY_4P_ALIGN_FLOW_FINISH_GANTRY_Z_WAIT_POS_CHECK,
		_eMASK_TAGKEY_4P_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS,
		_eMASK_TAGKEY_4P_ALIGN_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK,

		_eMASK_TAGKEY_4P_ALIGN_FLOW_DONE,
	};
};

