#pragma once

#include "Common/CommonDefine.h"

typedef enum
{
	eNORAML_TP,
	eAT_TP,
}enum_TP_Type;

class CInspectTPFlow : public CBaseFlow
{
public:
	CInspectTPFlow();
	~CInspectTPFlow();

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

	BOOL			Start(enum_TP_Type nTPType, int nStep);
	BOOL			Stop();

	CString m_strPath;

	CTime m_timeStart; //KJT 20210329

	BOOL			FlowInterlock();

	INT m_nKindOfTP;
	int m_nRepeatCount;
	int m_nMaxRepeatCount;
	int m_nAlignPoint;
	BOOL m_bDirReverse;

	double m_dMeasurePosXY[2][MAX_TP_COUNT];
	double m_dVisionResultValue[2][MAX_TP_COUNT];

	double m_dTargetPosX;
	double m_dTargetPosY;

	int SaveTPResult(int nRepeatCount);

	enum eTPFlow
	{
		_eINSPECT_TP_FLOW_ERROR = -1,

		_eINSPECT_TP_FLOW_IDLE = 0,
		_eINSPECT_TP_FLOW_START,
		_eINSPECT_TP_FLOW_INTERLOCK,

#pragma region //Unloader Ready
		_eINSPECT_TP_FLOW_UNLOADER_READY,
		_eINSPECT_TP_FLOW_UNLOADER_READY_CHECK,
#pragma endregion

#pragma region //Gantry ZX Ready
		_eINSPECT_TP_FLOW_GANTRY_ZX_READY,
		_eINSPECT_TP_FLOW_GANTRY_ZX_READY_CHECK,
#pragma endregion

#pragma region //Loader Ready
		_eINSPECT_TP_FLOW_LOADER_READY,
		_eINSPECT_TP_FLOW_LOADER_READY_CHECK,
#pragma endregion

#pragma region //PaperUnloader Ready
		_eINSPECT_TP_FLOW_PAPER_UNLOADER_ZXY_READY,
		_eINSPECT_TP_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK,
#pragma endregion

		_eINSPECT_TP_FLOW_SW_ALIGN_START,
		_eINSPECT_TP_FLOW_SW_ALIGN_DONE_CHECK,

		_eINSPECT_TP_FLOW_GANTRY_XY_MEASURE_POS_1ST,
		_eINSPECT_TP_FLOW_GANTRY_XY_MEASURE_POS_1ST_CHECK,
		//_eINSPECT_TP_FLOW_GANTRY_Z1_MEASURE_POS,
		//_eINSPECT_TP_FLOW_GANTRY_Z1_MEASURE_POS_CHECK,		
		_eINSPECT_TP_FLOW_GANTRY_Z3_MEASURE_POS,
		_eINSPECT_TP_FLOW_GANTRY_Z3_MEASURE_POS_CHECK,		
		_eINSPECT_TP_FLOW_GANTRY_XY_MEASURE_POS_2ND,
		_eINSPECT_TP_FLOW_GANTRY_XY_MEASURE_POS_2ND_CHECK,
		_eINSPECT_TP_FLOW_AUTOFOCUS_CHECK,
		_eINSPECT_TP_FLOW_LASER_FOCUS_START,
		_eINSPECT_TP_FLOW_LASER_FOCUS_CHECK,
		_eINSPECT_TP_FLOW_IMAGE_FOCUS_START,
		_eINSPECT_TP_FLOW_IMAGE_FOCUS_CHECK,
		_eINSPECT_TP_FLOW_GRAB_START,
		_eINSPECT_TP_FLOW_GRAB_DONE_CHECK,
		//_eINSPECT_TP_FLOW_FINISH_GANTRY_Z1_WAIT_POS,
		//_eINSPECT_TP_FLOW_FINISH_GANTRY_Z1_WAIT_POS_CHECK,		
		_eINSPECT_TP_FLOW_FINISH_GANTRY_Z3_WAIT_POS,
		_eINSPECT_TP_FLOW_FINISH_GANTRY_Z3_WAIT_POS_CHECK,		
		_eINSPECT_TP_FLOW_FINISH_GANTRY_XY_WAIT_POS,
		_eINSPECT_TP_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK,

		_eINSPECT_TP_FLOW_DONE,
	};
};

