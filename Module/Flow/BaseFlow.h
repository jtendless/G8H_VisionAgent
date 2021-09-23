#pragma once

//////////////////////////////////////////////////////////////////
//Set Time-Out
#define TIME_OUT_DEFAULT	(20 * 1000)			// mse
#define TIME_OUT_CYLINDER	(30 * 1000)			// mse
#define TIME_OUT_MOTION		(3 * 60 * 1000)	// msec
#define TIME_OUT_UVW_MOTION	(5*60*1000)	//msec
#define TIME_OUT_FORCE_CONTROL		(20 * 60 * 1000)	// msec
#define TIME_OUT_DUAL		(60 * 60 * 1000)	// msec
#define TIME_OUT_STATE		(60 * 60 * 1000)	// msec 5Min.
#define TIME_OUT_WELDING	(1 * 20 * 1000)	// msec
#define TIME_OUT_MOTION_X	(1 * 60 * 1000)	// msec
#define TIME_OUT_COMUNICATION (3  * 1000)	// msec
#define TIME_OUT_PROCESSING (5 * 1000) //msec

#define TIME_OUT_MAPPING		(48 * 60 * 60 * 1000)	// msec

#define TIME_OUT_PULSE (3  * 100)	// msec

#define TIME_OUT_DELAY (5*1000) //msec

#define TIME_OUT_LOADING_DELAY (15*1000) //msec
#define TIME_OUT_FLOW	(10*60*1000)	//msec

#define TIME_OUT_ROBOT_INTERFACE (10 * 60 * 1000)	// msec)

#define TIME_OUT_STRETCH_ZERO	(5  * 1000)		// msec
#define TIME_OUT_STRETCH	(1 * 15 * 1000)		// msec
#define TIME_OUT_ORIGIN		(2 * 60 * 1000)		// msec
#define TIME_OUT_STANDBY	TIME_OUT_MOTION		//( 1 * 60 * 1000)   // msec
#define TIME_OUT_UNCLAMP	(1 * 5 * 1000)		// msec
#define TIME_OUT_CF_WAIT	(20 * 1000)		// msec //180410 KJT 30->20 (by LCJ)

#define TIME_OUT_AUTO_SEQ		(20 * 60 * 1000)	// msec
#define BARCODE_DELAY (100) //msec
class CBaseFlow
{
public:
	CBaseFlow();
	~CBaseFlow();
public :
	typedef struct _GroupStepInfo
	{
		BOOL	m_bCompleteFlag;
		BOOL	m_bProcessingFlag;
		int		nStartStep;
		int		nEndStep;
		CString strGroupName;

	}GroupStepInfo, *pGroupStepInfo;
private:

	HANDLE			hMotionHandle;
	int				m_nGroupStepID;
	int				m_nCurFlowID;
	int				m_nCurFlowStep;
	int				m_nCurFlowTotalStep;// Flow, Check Total Step
	

	BOOL			*m_pMachineStopFlag;
	int				m_nRepeatCnt;
	DWORD			m_dwTimeTick;
	DWORD			m_dwTimeOut;
	
	BOOL			m_bPauseTimeOutFlag;
	CString		        m_stateName;
	CString				m_seqName;
public:
	
	DWORD			m_dwTackTime;
	BOOL			m_bManualStepFlag;
	BOOL			m_bTerminate;
	BOOL			SetTerminate(INT nValue);
	BOOL			IsTerminate() { return m_bTerminate; }
	DWORD			GetTimeOut();
	BOOL			IsTimeOut();
	void			SetTimeOut(DWORD timeout);
	void			ResetTimeOut();
	void			PauseTimeOut();

	// GroupInfo
	GroupStepInfo	m_sGroupInfo[200];
	int				m_nMaxGroupCount;
	int				GetThisStepGroupID(int nStep);
	int				ResetCompleteFlag();
	// 수행할 Step 지정 
	
	int				SetGroupStep(int nManualStep, BOOL bManualStepFlag = FALSE);
	int				SetStep(int nStatus, LPCTSTR name = NULL);
	int				SetCheckStep(int nStatus, LPCTSTR name = NULL);
	int				SetStop();
	int				SetFinish();

	// 알람을 울리고, IDLE상태로 전환 
	BOOL SetAlarm(LPCTSTR Msg);

	// 자식  Class HANDLE 획득
	void			SetHandle(HANDLE hhandle);
	void			SetCurrentStep(int nStep);
	void			SetMachineStopFlag(BOOL *MachineStopFlag);
	// 현재 step 반환  
	int				GetCurrentFlowStep();
	int				GetCurrentTotalStep();
	BOOL			GetMachineStopFlag();






};


