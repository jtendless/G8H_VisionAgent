#pragma once

#include "Flow/BaseFlow.h"

class CAOIReviewFlow : public CBaseFlow
{
public:
	CAOIReviewFlow();
	~CAOIReviewFlow();

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

	int m_nCurLineIndex;
	int m_nFrameIndex;
	int m_nDefectIndex;
	double m_dTargetPosX;
	double m_dTargetPosY;

	BOOL GetTargetPos(double *dPosX, double *dPosY);
	BOOL CheckExistDefect(int nLineIndex, int nFrameIndex, int nDefectIndex);

	//BOOL MakeReviewDir();

	enum eAOIReviewFlow
	{
		_eAOI_REVIEW_FLOW_ERROR = -1,

		_eAOI_REVIEW_FLOW_IDLE = 0,
		_eAOI_REVIEW_FLOW_START,
		_eAOI_REVIEW_FLOW_INTERLOCK_CHECK,

#pragma region //Unloader Ready
		_eAOI_REVIEW_FLOW_UNLOADER_READY,
		_eAOI_REVIEW_FLOW_UNLOADER_READY_CHECK,
#pragma endregion

#pragma region //Loader Ready
		_eAOI_REVIEW_FLOW_LOADER_READY,
		_eAOI_REVIEW_FLOW_LOADER_READY_CHECK,
#pragma endregion

#pragma region //Box Camera Ready
		//_eAOI_REVIEW_FLOW_BOX_CAMERA_READY,
		//_eAOI_REVIEW_FLOW_BOX_CAMERA_READY_CHECK,
#pragma endregion

#pragma region //Gantry Z,X Ready
		_eAOI_REVIEW_FLOW_GANTRY_ZX_READY,
		_eAOI_REVIEW_FLOW_GANTRY_ZX_READY_CHECK,
#pragma endregion

		_eAOI_REVIEW_FLOW_CHECK_EXIST_DEFECT,
		_eAOI_REVIEW_FLOW_GANTRY_XY_DEFECT_POS,
		_eAOI_REVIEW_FLOW_GANTRY_XY_DEFECT_POS_CHECK,
		_eAOI_REVIEW_FLOW_GANTRY_Z2_INSPECTION_POS,
		_eAOI_REVIEW_FLOW_GANTRY_Z2_INSPECTION_POS_CHECK,
		//_eAOI_REVIEW_FLOW_LASER_FOCUS_START,
		//_eAOI_REVIEW_FLOW_LASER_FOCUS_CHECK,
		//_eAOI_REVIEW_FLOW_IMAGE_FOCUS_START,
		//_eAOI_REVIEW_FLOW_IMAGE_FOCUS_CHECK,
		_eAOI_REVIEW_FLOW_ZOOM_20X_MOVE,
		_eAOI_REVIEW_FLOW_ZOOM_20X_MOVE_CHECK,
		_eAOI_REVIEW_FLOW_GRAB,
		_eAOI_REVIEW_FLOW_GANTRY_Z_ALL_FINISH_WAIT_POS,
		_eAOI_REVIEW_FLOW_GANTRY_Z_ALL_FINISH_WAIT_POS_CHECK,

		_eAOI_REVIEW_FLOW_DONE,
	};
};

