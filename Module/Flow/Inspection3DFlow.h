#pragma once


typedef enum
{
	eNORAML_3D,
	eAT_3D,
}enum_3D_Type;


class CInspection3DFlow : public CBaseFlow
{
public:
	CInspection3DFlow();
	~CInspection3DFlow();

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

	BOOL			Start(enum_3D_Type n3DType, int nStep);
	BOOL			Stop();

	CTime m_timeStart; //KJT 20210329

	CString m_strPath;

	double m_dMeasurePosXY[MAX_3D_HOLE_COUNT][2];
	//BOOL Set3DInspectionPos(double dPosX[6][1], double dPosY[6][1]);

	stPOS_XYZ GetMeasurementPos(int nMeasurementPoint);
	double m_dTargetPosX;
	double m_dTargetPosY;

	int m_nSlotCenterPos[MAX_3D_HOLE_COUNT][2];
	int m_nSlotStartPos[MAX_3D_HOLE_COUNT][2];
	int m_nSlotSize[MAX_3D_HOLE_COUNT][2];
	double m_dGradientResult[MAX_3D_HOLE_COUNT][4];

	BOOL			FlowInterlock();

	INT m_nKindOf3D;
	int m_nRepeatCount;
	int m_nMaxRepeatCount;
	int m_nMaxPosCount;
	int m_nCurPosCount;

	BOOL SaveMeasureSlotGradientResult(int nRepeatCount);

	enum eInspection3DFlow
	{
		_eINSPECT_3D_FLOW_ERROR = -1,

		_eINSPECT_3D_FLOW_IDLE = 0,
		_eINSPECT_3D_FLOW_START,
		_eINSPECT_3D_FLOW_INTERLOCK_CHECK,

#pragma region //Unloader Ready
		_eINSPECT_3D_FLOW_UNLOADER_READY,
		_eINSPECT_3D_FLOW_UNLOADER_READY_CHECK,
#pragma endregion

#pragma region //Loader Ready
		_eINSPECT_3D_FLOW_LOADER_READY,
		_eINSPECT_3D_FLOW_LOADER_READY_CHECK,
#pragma endregion

#pragma region //Box Camera Ready
		_eINSPECT_3D_FLOW_BOX_CAMERA_READY,
		_eINSPECT_3D_FLOW_BOX_CAMERA_READY_CHECK,
#pragma endregion

#pragma region //Gantry Z,X Ready
		_eINSPECT_3D_FLOW_GANTRY_ZX_READY,
		_eINSPECT_3D_FLOW_GANTRY_ZX_READY_CHECK,
#pragma endregion

		_eINSPECT_3D_FLOW_SW_ALIGN_START,
		_eINSPECT_3D_FLOW_SW_ALIGN_DONE_CHECK,

#pragma region //3D Inspection
		_eINSPECT_3D_FLOW_ACQUISITION_START,
		_eINSPECT_3D_FLOW_GANTRY_XY_INSPECTION_POS_1ST,
		_eINSPECT_3D_FLOW_GANTRY_XY_INSPECTION_POS_1ST_CHECK,
		_eINSPECT_3D_FLOW_3D_CAM_Z_INSPECTION_POS_1ST,
		_eINSPECT_3D_FLOW_3D_CAM_Z_INSPECTION_POS_1ST_CHECK,

		_eINSPECT_3D_FLOW_3D_CAM_Z_INSPECTION_POS_2ND,
		_eINSPECT_3D_FLOW_3D_CAM_Z_INSPECTION_POS_2ND_CHECK,
		_eINSPECT_3D_FLOW_GANTRY_XY_INSPECTION_POS_2ND,
		_eINSPECT_3D_FLOW_GANTRY_XY_INSPECTION_POS_2ND_CHECK,
		_eINSPECT_3D_FLOW_TRIGGER_SHOT,
		_eINSPECT_3D_FLOW_MEASURE_GRADIENT,
		_eINSPECT_3D_FLOW_ACQUISITION_STOP,
		_eINSPECT_3D_FLOW_FINISH_3D_CAM_Z_WAIT_POS,
		_eINSPECT_3D_FLOW_FINISH_3D_CAM_Z_WAIT_POS_CHECK,
		_eINSPECT_3D_FLOW_FINISH_GANTRY_XY_WAIT_POS,
		_eINSPECT_3D_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK,
#pragma endregion

		_eINSPECT_3D_FLOW_DONE,
	};
};
