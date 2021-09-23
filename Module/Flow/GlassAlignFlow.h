#pragma once

class CGlassAlignFlow : public CBaseFlow
{
public:
	CGlassAlignFlow();
	~CGlassAlignFlow();

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

	BOOL			Start();
	BOOL			Stop();

	CTime m_timeStart; //KJT 20210329

	BOOL			FlowInterlock();

	int m_nMappingID;

	BOOL m_bPreAlignUse;
	BOOL m_bPreAlignDone;

	int				m_nGrabRetryCnt;

	double m_AlignPointValue[2][4]; 
	double m_AlignVisionPreResultValue[2][4];
	double m_AlignVisionResultValue[2][4];
	double dHorizontalPosX[2];
	double dHorizontalPosY[2];
	double dVerticalPosX[2];
	double dVerticalPosY[2];

	double m_dDiffPos[3];
	double m_dTarget[3];

	int m_nAlignCnt;
	int m_nAlignPoint;
	BOOL m_bDirReverse;
	double m_dAlign4PointPos[4][2];
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
	BOOL GetAlignPos(int nIndex,double *dPosX, double *dPosY);
	double GetVerticalPos_X_PreAlign(int nAlignCount);
	double GetVerticalPos_Y_PreAlign(int nAlignCount);
	double GetVerticalPos_X_Review(int nAlignCount);
	double GetVerticalPos_Y_Review(int nAlignCount);
	BOOL SetPreAlignUseMode(BOOL bUse);

	BOOL GetXYTPos(double *dRefPosX, double *dRefPosY, double *dDiffPosX, double *dDiffPosY, double *ResultX, double *ResultY, double *ResultT);

	int m_n4Point;

	double dCmdPointXY[4][2] = { {0.0, }, };
	double dActPointXY[4][2] = { {0.0, }, };

	enum TMaskAlignSeq
	{		
		eGLASS_ALIGN_FLOW_ERROR = -1,

		eGLASS_ALIGN_FLOW_IDLE = 0,
		eGLASS_ALIGN_FLOW_START,
		eGLASS_ALIGN_FLOW_INTERLOCK,

#pragma region //Unloader Ready
		eGLASS_ALIGN_FLOW_UNLOADER_READY,
		eGLASS_ALIGN_FLOW_UNLOADER_READY_CHECK,
#pragma endregion

#pragma region //Gantry Z,X Ready
		eGLASS_ALIGN_FLOW_GANTRY_ZX_READY,
		eGLASS_ALIGN_FLOW_GANTRY_ZX_READY_CHECK,
#pragma endregion

#pragma region //Loader Ready
		eGLASS_ALIGN_FLOW_LOADER_READY,
		eGLASS_ALIGN_FLOW_LOADER_READY_CHECK,
#pragma endregion

#pragma region //PaperUnloader Ready
		eGLASS_ALIGN_FLOW_PAPER_UNLOADER_ZXY_READY,
		eGLASS_ALIGN_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK,
#pragma endregion

#pragma region //sunghaklee : Gantry PreAlign
		eGLASS_ALIGN_FLOW_AXIS_GANTRY_PRE_ALIGN_XY_POS,
		eGLASS_ALIGN_FLOW_AXIS_GANTRY_PRE_ALIGN_XY_POS_CHECK,
		eGLASS_ALIGN_FLOW_AXIS_Z_PRE_ALGIN_CAM_DOWN_POS,
		eGLASS_ALIGN_FLOW_AXIS_Z_PRE_ALGIN_CAM_DOWN_POS_CHECK,
		eGLASS_ALIGN_FLOW_AXIS_Z_PRE_ALGIN_CAM_UP_POS,
		eGLASS_ALIGN_FLOW_AXIS_Z_PRE_ALGIN_CAM_UP_POS_CHECK,
#pragma endregion

#pragma region //ALIGN 1ST
		eGLASS_ALIGN_FLOW_AXIS_GANTRY_XY_MOVE_1ST_ALIGN_POS,
		eGLASS_ALIGN_FLOW_AXIS_GANTRY_XY_MOVE_1ST_ALIGN_POS_CHECK,
#pragma endregion
#pragma region //ALIGN REPEAT
		eGLASS_ALIGN_FLOW_AXIS_Z_REVIEW10X_CAM_DOWN_POS,
		eGLASS_ALIGN_FLOW_AXIS_Z_REVIEW10X_CAM_DOWN_POS_CHECK,
		
		eGLASS_ALIGN_FLOW_AXIS_Z_REVIEW10X_LASER_FOCUS_START,
		eGLASS_ALIGN_FLOW_AXIS_Z_REVIEW10X_LASER_FOCUS_CHECK,
		eGLASS_ALIGN_FLOW_AXIS_Z_REVIEW10X_IMAGE_FOCUS_START,
		eGLASS_ALIGN_FLOW_AXIS_Z_REVIEW10X_IMAGE_FOCUS_CHECK,

		eGLASS_ALIGN_FLOW_GRAB_START,
		eGLASS_ALIGN_FLOW_GRAB_CHECK,

		eGLASS_ALIGN_FLOW_AXIS_GANTRY_XY_MOVE_ALIGN_POS,
		eGLASS_ALIGN_FLOW_AXIS_GANTRY_XY_MOVE_ALIGN_POS_CHECK,

		eGLASS_ALIGN_FLOW_UVW_MOVE_START,
		eGLASS_ALIGN_FLOW_UVW_MOVE_CHECK,
#pragma endregion
		eGLASS_ALIGN_FLOW_AXIS_Z_FINISH_CAM_UP_POS,
		eGLASS_ALIGN_FLOW_AXIS_Z_FINISH_CAM_UP_POS_CHECK,
		
		eGLASS_ALIGN_FLOW_EXIT,

		eGLASS_ALIGN_FLOW_DONE,

	};
};

