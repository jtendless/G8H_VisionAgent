#pragma once

class CMaskTeg4PTensionAlignFlow : public CBaseFlow
{
public:
	CMaskTeg4PTensionAlignFlow();
	~CMaskTeg4PTensionAlignFlow();

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
	BOOL m_bLaserFocusUseFlag;
	BOOL m_bAutoFocusUseFlag;

	double m_AlignPointValue[2][4];
	double m_AlignVisionPreResultValue[2][4];
	double m_AlignVisionResultValue[2][4];

	double m_AlignVisionResultPpaValue[2];
	double m_AlignVisionResultCdValue[2];

	double m_dDiffPos[3];
	double m_dTarget[3];

	int m_nAlignCnt;
#pragma endregion

#pragma region //Move Func
	double GetAlignPos_X(int nAlignCount);
	double GetAlignPos_Y(int nAlignCount);
	double m_dTargetPosX;
	double m_dTargetPosY;
#pragma endregion

	enum eTensionMainAlignTeg4P
	{
		_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_ERROR = -1,

		_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_IDLE = 0,
		_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_START,

		_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_INTERLOCK,

#pragma region //Unloader Ready
		_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_UNLOADER_READY,
		_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_UNLOADER_READY_CHECK,
#pragma endregion

#pragma region //Loader Ready
		_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_LOADER_READY,
		_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_LOADER_READY_CHECK,
#pragma endregion

#pragma region //Box Camera Ready
		_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_BOX_CAMERA_READY,
		_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_BOX_CAMERA_READY_CHECK,
#pragma endregion

#pragma region //Gantry Z,X Ready
		_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GANTRY_ZX_READY,
		_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GANTRY_ZX_READY_CHECK,
#pragma endregion

		_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GANTRY_XY_ALIGN_POS,
		_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GANTRY_XY_ALIGN_POS_CHECK,
		_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GANTRY_Z1_INSPECTION_POS,
		_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GANTRY_Z1_INSPECTION_POS_CHECK,
		_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_IMAGE_FOCUS_START,
		_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_IMAGE_FOCUS_CHECK,
		_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GRAB_START,
		_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GRIPPER_Z_TENSTION_POS,
		_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GRIPPER_Z_TENSTION_POS_CHECK,
		_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_STRETCH_TENSTION_START,
		_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_STRETCH_TENSTION_DONE_CHECK,
		_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_PITCH_TENSTION_START,
		_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_PITCH_TENSTION_DONE_CHECK,
		_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GANTRY_Z_CLAMP_POS,
		_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_GANTRY_Z_CLAMP_POS_CHECK,

		_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_FINISH_GANTRY_Z_FINISH_UP_POS,
		_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_FINISH_GANTRY_Z_FINISH_UP_POS_CHECK,
		_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_FINISH_GANTRY_XY_WAIT_POS,
		_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK,

		_eTENSION_MAIN_ALIGN_TEG_4P_FLOW_DONE,
	};
};

