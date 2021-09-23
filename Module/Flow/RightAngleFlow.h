#pragma once
class CRightAngleFlow : public CBaseFlow
{
public:
	CRightAngleFlow();
	~CRightAngleFlow();

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

	BOOL			Start(enum_MappingID eMappingID);
	BOOL			Stop();

	CTime m_timeStart; //KJT 20210329

	BOOL			FlowInterlock();

	int m_nMappingID;

	BOOL m_bPreAlignUse;
	BOOL m_bPreAlignDone;
	BOOL m_bGantryWaitPosSkip;

	int				m_nGrabRetryCnt = 0;

	double m_AlignPointValue[2][2];
	double m_AlignVisionResultValue[2][2];
	double dHorizontalPosX[2];
	double dHorizontalPosY[2];
	double dVerticalPosX[2];
	double dVerticalPosY[2];

	double m_dDiffPos[3];

	double m_ErrorY;

	int m_nAlignPoint;
	BOOL m_bDirReverse;

	BOOL m_bLaserFocusUseFlag;
	BOOL m_bAutoFocusUseFlag;
	BOOL SetRightAnglePosXY(double *dPosX, double *dPosY);
	double GetRightAnglePos_X_PreAlign(int nAlignCount);
	double GetRightAnglePos_Y_PreAlign(int nAlignCount);
	double GetRightAnglePos_X_Review(int nAlignCount);
	double GetRightAnglePos_Y_Review(int nAlignCount);
	void SetPreAlignUseMode(BOOL bUse = TRUE);
	void SetFinishGantryWaitPosSkip(BOOL bSkip = FALSE);

	BOOL GetXYTPos(double *dRefPosX, double *dRefPosY, double *dDiffPosX, double *dDiffPosY, double *ResultX, double *ResultY, double *ResultT);

	enum eRightAngleFlow
	{
		eRIGHT_ANGLE_FLOW_ERROR = -1,

		eRIGHT_ANGLE_FLOW_IDLE = 0,
		eRIGHT_ANGLE_FLOW_START,
		eRIGHT_ANGLE_FLOW_INTERLOCK,

#pragma region //Unloader Ready
		eRIGHT_ANGLE_FLOW_UNLOADER_READY,
		eRIGHT_ANGLE_FLOW_UNLOADER_READY_CHECK,
#pragma endregion

#pragma region //Loader Ready
		eRIGHT_ANGLE_FLOW_LOADER_READY,
		eRIGHT_ANGLE_FLOW_LOADER_READY_CHECK,
#pragma endregion

#pragma region //Box Camera Ready
		eRIGHT_ANGLE_FLOW_BOX_CAMERA_READY,
		eRIGHT_ANGLE_FLOW_BOX_CAMERA_READY_CHECK,
#pragma endregion

#pragma region //Gantry Z,X Ready
		eRIGHT_ANGLE_FLOW_GANTRY_ZX_READY,
		eRIGHT_ANGLE_FLOW_GANTRY_ZX_READY_CHECK,
#pragma endregion

		eRIGHT_ANGLE_FLOW_AXIS_GANTRY_XY_MOVE_VERTICAL_POS,
		eRIGHT_ANGLE_FLOW_AXIS_GANTRY_XY_VERTICA_POS_CHECK,
#pragma region //PreAlign
		eRIGHT_ANGLE_FLOW_AXIS_Z_PRE_ALGIN_CAM_DOWN_POS,
		eRIGHT_ANGLE_FLOW_AXIS_Z_PRE_ALGIN_CAM_DOWN_POS_CHECK,
#pragma endregion

#pragma region //Review
		eRIGHT_ANGLE_FLOW_AXIS_Z_REVIEW10X_CAM_DOWN_POS,
		eRIGHT_ANGLE_FLOW_AXIS_Z_REVIEW10X_CAM_DOWN_POS_CHECK,
		eRIGHT_ANGLE_FLOW_AXIS_Z_REVIEW10X_LASER_FOCUS_START,
		eRIGHT_ANGLE_FLOW_AXIS_Z_REVIEW10X_LASER_FOCUS_CHECK,
		eRIGHT_ANGLE_FLOW_AXIS_Z_REVIEW10X_IMAGE_FOCUS_START,
		eRIGHT_ANGLE_FLOW_AXIS_Z_REVIEW10X_IMAGE_FOCUS_CHECK,
#pragma endregion

		eRIGHT_ANGLE_FLOW_GRAB_START,
		eRIGHT_ANGLE_FLOW_FINISH_GANTRY_Z3_WAIT_POS,
		eRIGHT_ANGLE_FLOW_FINISH_GANTRY_Z3_WAIT_POS_CHECK,
		eRIGHT_ANGLE_FLOW_FINISH_GANTRY_XY_WAIT_POS,
		eRIGHT_ANGLE_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK,

		eRIGHT_ANGLE_FLOW_DONE,
	};
};

