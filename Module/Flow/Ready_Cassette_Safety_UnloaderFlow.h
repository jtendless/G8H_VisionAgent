#pragma once

class CReady_Cassette_Safety_UnloaderFlow : public CBaseFlow
{
public:
	CReady_Cassette_Safety_UnloaderFlow();
	~CReady_Cassette_Safety_UnloaderFlow();

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

	BOOL			Start();
	BOOL			Stop();

	BOOL			FlowInterlock();

	enum eReady_Cassette_Safety_UnloaderFlow
	{
		_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_ERROR = -1,
		_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_IDLE = 0,
		_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_START,
		_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_INTERLOCK_CHECK,

#if 0 //Hide
		_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_SUB_Z_UP,//21.02.20 SJC 
		_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_SUB_Z_UP_CHECK,//21.02.20 SJC
		_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_Z_UP,
		_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_Z_UP_CHECK,
		_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_X_WAIT_POS,
		_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_X_WAIT_POS_CHECK,
		_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_Y_CASSETTE_SAFETY_POS,
		_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_UNLOADER_Y_CASSETTE_SAFETY_POS_CHECK,
#endif

		_eREADY_CASSETTE_SAFETY_UNLOADER_FLOW_DONE,
	};
};

