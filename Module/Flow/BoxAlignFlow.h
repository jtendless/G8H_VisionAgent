#pragma once

class CBoxAlignFlow : public CBaseFlow
{
public:
	CBoxAlignFlow();
	~CBoxAlignFlow();

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
	CString m_strFilePath;

	BOOL			FlowInterlock();

	int SaveBoxAlignResult();

#pragma region //BoxAlign
	double m_AlignPointValue[2][2]; //Inspection Pos
	double m_AlignVisionResultValue[2][2];

	double m_dDiffPos[3];
	double m_dTarget[3];

	int m_nGrabRetryCount;

	int m_AlignCnt;

	BOOL m_bBoxAlignGrabDone;
#pragma endregion

	double			m_dCurPos, m_dPrevPos;

	//[1]
	enum eBoxAlignFlow
	{
		_eBOX_ALIGN_FLOW_ERROR = -1,

		_eBOX_ALIGN_FLOW_IDLE = 0,
		_eBOX_ALIGN_FLOW_START,
		_eBOX_ALIGN_FLOW_INTERLOCK_CHECK,

#pragma region //Unloader Ready
		_eBOX_ALIGN_FLOW_UNLOADER_READY,
		_eBOX_ALIGN_FLOW_UNLOADER_READY_CHECK,
#pragma endregion

#pragma region //Gantry ZXY Ready
		_eBOX_ALIGN_FLOW_GANTRY_ZXY_READY,
		_eBOX_ALIGN_FLOW_GANTRY_ZXY_READY_CHECK,
#pragma endregion

#pragma region //LoaderZ Ready
		_eBOX_ALIGN_FLOW_LOADER_Z_READY,
		_eBOX_ALIGN_FLOW_LOADER_Z_READY_CHECK,
#pragma endregion

#pragma region //PaperUnloader Ready
		_eBOX_ALIGN_FLOW_PAPER_UNLOADER_ZX_READY,
		_eBOX_ALIGN_FLOW_PAPER_UNLOADER_ZX_READY_CHECK,
		_eBOX_ALIGN_FLOW_PAPER_UNLOADER_Y_SAFETY_POS,
		_eBOX_ALIGN_FLOW_PAPER_UNLOADER_Y_SAFETY_POS_CHECK,
#pragma endregion
			
		_eBOX_ALIGN_FLOW_UVW_WAIT_POS, //KJT 20210316
		_eBOX_ALIGN_FLOW_UVW_WAIT_POS_CHECK,

		_eBOX_ALIGN_FLOW_LOADER_Y_ALIGN_POS,
		_eBOX_ALIGN_FLOW_LOADER_Y_ALIGN_POS_CHECK,
		_eBOX_ALIGN_FLOW_LOADER_X_ALIGN_POS,
		_eBOX_ALIGN_FLOW_LOADER_X_ALIGN_POS_CHECK,
		_eBOX_ALIGN_FLOW_LOADER_Z_ALIGN_POS,
		_eBOX_ALIGN_FLOW_LOADER_Z_ALIGN_POS_CHECK,
		_eBOX_ALIGN_FLOW_GRAB_START,
		_eBOX_ALIGN_FLOW_UVW_MOVE_START,
		_eBOX_ALIGN_FLOW_UVW_MOVE_CHECK,
		_eBOX_ALIGN_FLOW_LOADER_Z_WAIT_POS_2ND,
		_eBOX_ALIGN_FLOW_LOADER_Z_WAIT_POS_2ND_CHECK,

		_eBOX_ALIGN_FLOW_DONE,
	};
};

