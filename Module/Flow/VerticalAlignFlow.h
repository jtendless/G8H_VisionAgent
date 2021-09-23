#pragma once

class CVerticalAlignFlow : public CBaseFlow
{
public:
	CVerticalAlignFlow();
	~CVerticalAlignFlow();

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

	BOOL			Start(int nCamIndex);
	BOOL			Stop();

	CTime m_timeStart; //KJT 20210329

	BOOL			FlowInterlock();

	int m_nMappingID;

	BOOL m_bPreAlignUse;
	BOOL m_bPreAlignDone;

	int				m_nGrabRetryCnt;

	double m_AlignPointValue[2][2]; 
	double m_AlignVisionPreResultValue[2][2];
	double m_AlignVisionResultValue[2][2];
	double dHorizontalPosX[2];
	double dHorizontalPosY[2];
	double dVerticalPosX[2];
	double dVerticalPosY[2];

	double m_dDiffPos[3];
	double m_dTarget[3];

	double m_ErrorX;
	double m_ErrorY;

	int m_nAlignCnt;
	BOOL m_bDirReverse;

	//CMappingProc	*pMappingProc;

	BOOL(CGantryMotion::*ReviewCamPosMove)(double, double, BOOL, BOOL, BOOL, BOOL, BOOL);
	BOOL(CGantryMotion::*IsReviewCamPosMove)(void);

#ifndef SIM_MODE
	CWkLibVision	*pCamera;
#endif
	BOOL m_bLaserFocusUseFlag;
	BOOL m_bAutoFocusUseFlag;
	BOOL SetHorizontalPosX(double *dPosX, double *dPosY);
	BOOL SetVerticalPosXY(double *dPosX, double *dPosY);
	double GetVerticalPos_X_PreAlign(int nAlignCount);
	double GetVerticalPos_Y_PreAlign(int nAlignCount);
	double GetVerticalPos_X_Review(int nAlignCount);
	double GetVerticalPos_Y_Review(int nAlignCount);
	BOOL SetPreAlignUseMode(BOOL bUse);

	BOOL GetXYTPos(double *dRefPosX, double *dRefPosY, double *dDiffPosX, double *dDiffPosY, double *ResultX, double *ResultY, double *ResultT);


	enum TMaskAlignSeq
	{	
		eVERTICAL_ALIGN_FLOW_ERROR = -1,

		eVERTICAL_ALIGN_FLOW_IDLE = 0,
		eVERTICAL_ALIGN_FLOW_START,
		eVERTICAL_ALIGN_FLOW_INTERLOCK,

#pragma region //Unloader Ready
		eVERTICAL_ALIGN_FLOW_UNLOADER_READY,
		eVERTICAL_ALIGN_FLOW_UNLOADER_READY_CHECK,
#pragma endregion

#pragma region //Gantry Z,X Ready
		eVERTICAL_ALIGN_FLOW_GANTRY_ZX_READY,
		eVERTICAL_ALIGN_FLOW_GANTRY_ZX_READY_CHECK,
#pragma endregion

#pragma region //Loader Ready
		eVERTICAL_ALIGN_FLOW_LOADER_READY,
		eVERTICAL_ALIGN_FLOW_LOADER_READY_CHECK,
#pragma endregion

#pragma region //PaperUnloader Ready
		eVERTICAL_ALIGN_FLOW_PAPER_UNLOADER_READY,
		eVERTICAL_ALIGN_FLOW_PAPER_UNLOADER_READY_CHECK,
#pragma endregion

		eVERTICAL_ALIGN_FLOW_AXIS_GANTRY_XY_MOVE_VERTICAL_POS,
		eVERTICAL_ALIGN_FLOW_AXIS_GANTRY_XY_VERTICA_POS_CHECK,
#pragma region //PreAlign
		eVERTICAL_ALIGN_FLOW_AXIS_Z_PRE_ALGIN_CAM_DOWN_POS,
		eVERTICAL_ALIGN_FLOW_AXIS_Z_PRE_ALGIN_CAM_DOWN_POS_CHECK,
#pragma endregion

#pragma region //Review
		eVERTICAL_ALIGN_FLOW_AXIS_Z_REVIEW10X_CAM_DOWN_POS,
		eVERTICAL_ALIGN_FLOW_AXIS_Z_REVIEW10X_CAM_DOWN_POS_CHECK,
		eVERTICAL_ALIGN_FLOW_AXIS_Z_REVIEW10X_LASER_FOCUS_START,
		eVERTICAL_ALIGN_FLOW_AXIS_Z_REVIEW10X_LASER_FOCUS_CHECK,
		eVERTICAL_ALIGN_FLOW_AXIS_Z_REVIEW10X_IMAGE_FOCUS_START,
		eVERTICAL_ALIGN_FLOW_AXIS_Z_REVIEW10X_IMAGE_FOCUS_CHECK,
#pragma endregion

		eVERTICAL_ALIGN_FLOW_GRAB_START,
		eVERTICAL_ALIGN_FLOW_UVW_MOVE_START,
		eVERTICAL_ALIGN_FLOW_UVW_MOVE_CHECK,
		eVERTICAL_ALIGN_FLOW_AXIS_Z_FINISH_CAM_UP_POS,
		eVERTICAL_ALIGN_FLOW_AXIS_Z_FINISH_CAM_UP_POS_CHECK,

		eVERTICAL_ALIGN_FLOW_DONE,

	};
};

