#pragma once
#include "MelsecBase.h"
#include "Motion/BaseMotion.h"
#include "CimDefine.h"



class CCimModule : public CMelsecBase, CBaseMotion
{
public:
	CCimModule();
	~CCimModule();
	//Melsec 통신 모듈.
	//CWkLibCimModule *m_pCim;


	enum
	{
		_PLC_DEV_TYPE_X = 1,
		_PLC_DEV_TYPE_Y = 2,
		_PLC_DEV_TYPE_D = 13,
		_PLC_DEV_TYPE_R = 22,
		_PLC_DEV_TYPE_B = 23,
		_PLC_DEV_TYPE_W = 24,
	};

	enum TCimSeq
	{
		eCIM_IDLE = 1,
		eCIM_START,
		eCIM_ERROR,
		eCIM_DONE,
		eCIM_EXIT,

	};

	enum Alarm
	{
		eALARM_NONE,
		eALARM_SET,
		eALARM_RESET,
		eALARM_ALL_RESET,
	};

	CWinThread*		pThread;
	VOID			RobotThreadFunctionEntry(VOID);
	static UINT		RobotThreadFunction(LPVOID lpParam);
	BOOL			m_RobotFinish;
	BOOL			m_RobotFinishOK;
	BOOL			m_CIMAlarmFlag[100];

	//State Check.
	BOOL m_bRevChk;
	BOOL m_bStateChk;

	CWinThread*		pReceiveThread;
	VOID			CimReceiveThreadFunctionEntry(VOID);
	static UINT		ReceiveThreadFunction(LPVOID lpParam);
	BOOL			m_ReceiveFinish;
	BOOL			m_ReceiveFinishOK;
	void(*m_StateComplete)(void *pArgument);

	//short	m_sChannelNo;
	//long	m_lChannelPath;
	//long	m_lNetworkNo;				//	network No. 1 fixed			
	//long	m_lStationNo;				//	station No. 1 fixed			

	//int		m_nConnected; 

	//CCriticalSection m_Critical;

	BOOL m_bUpTroubleSignalFlag;
	BOOL m_bUpTroubleSignalFallingEdgeFlag;

	BOOL m_bDownTroubleSignalFlag;
	BOOL m_bDownTroubleSignalFallingEdgeFlag;


	BOOL m_bRobotAckSignalFlag;
	BOOL m_bRobotAckSignalFallingEdgeFlag;

	DWORD m_dAliveTimer;
	DWORD m_dAliveTimerCheck;
public:
	//JobData
	int JobDataAWrite(int nAddr, JOB_DATA MeterialData);
	int JobDataBWrite(int nAddr, MASK_JOB_DATA MeterialData);

	//void  GetJobDataAFromRobot();
	//void  JobDataBRead(int nAddr);

	BOOL m_bReceivedJobReportCompleteFlag;
	BOOL m_bStoredJobReportCompleteFlag;
	BOOL m_bFetchedOutJobReportCompleteFlag;
	BOOL m_bRemovedJobReportCompleteFlag;
	BOOL m_bSentOutJobReportCompleteFlag;

	BOOL m_bProcessStartCompleteFlag;
	BOOL m_bProcessEndCompleteFlag;
	BOOL m_bProcessDataReportCompleteFlag;

	BOOL m_bSheetInfoDownloadCompleteFlag;
	BOOL m_bSheetMoveInCompleteFlag;
	BOOL m_bSheetMoveOutCompleteFlag;
	BOOL		m_bMotionDone;



	BOOL		InitProcess();
	BOOL		EndProcess();


	HANDLE		hHandle;
	BOOL		m_bTerminate;
	BOOL		IsTerminate() { return m_bTerminate; }

	BOOL		isFinish() { return m_bMotionDone; }
	BOOL		Start();
	BOOL		Stop();
	BOOL		StopCheck();

	BOOL		m_bStopBit;


	//KJT 20210407
	void		CheckAlarmReserved();
	BOOL		IsAlarmT1TimeOut(int AlarmArea);
	void		SetAlarmT1TimeOut(int AlarmArea);
	void		ClearAlarmT1TimeOut(int AlarmArea);

	BOOL		IsAliveTimeOut();
	void			SetAliveTimeOut();

	BOOL		IsT1TimeOut();
	void			SetT1TimeOut();
	void			ClearT1TimeOut();

	BOOL		IsT2TimeOut();
	void			SetT2TimeOut();
	void			ClearT2TimeOut();

	BOOL		IsT3TimeOut();
	void			SetT3TimeOut();
	void			ClearT3TimeOut();

	BOOL		IsCVTimeOut();
	void			SetCVTimeOut();
	void			ClearCVTimeOut();

	BOOL		IsCommonTimeOut();
	void			SetCommonTimeOut(DWORD TimeOutValue);
	void			ClearCommonTimeOut();

	BOOL		IsTowerLampTimeOut();
	void			SetTowerLampTimeOut(DWORD TimeOutValue);
	void			ClearTowerLampTimeOut();

	BOOL		IsCIMPCOffStatusTimeOut();
	void			SetCIMPCOffStatusTimeOut(DWORD TimeOutValue);
	void			ClearCIMPCOffStatusTimeOut();

	BOOL		IsCIMPCOnStatusTimeOut();
	void			SetCIMPCOnStatusTimeOut(DWORD TimeOutValue);
	void			ClearCIMPCOnStatusTimeOut();

	void			CIMAlarmMessage(WORD AlarmState, WORD AlarmUnit, WORD AlarmCode, WORD AlarmType, WORD AlarmUsingFlag, WORD AlarmID, const TCHAR* AlarmText); //KJT 20210424
	void			CIMAlarmResetMessage(WORD AlarmID);
	void			CIMAlarmAllResetMessage();

	int				PPIDCheck(MASK_JOB_DATA JobData);
	char*		FindModelName(WORD wRecipeID);

	//BOOL		InitRobotCimDataReset();

	//Awking 추가함수.
	//LB 관리 함수.
	BOOL SetLbLtmSelectedEventRun();

#if 0 //B12 Not Use //KJT 20210325
	//JobData
	int JobDataAWrite(int nAddr, MATERIAL_DATA_A MeterialData);
	int JobDataBWrite(int nAddr, MATERIAL_DATA_B MeterialData);

	void  GetJobDataAFromRobot();
#endif

#if 1
	//LW 관리 함수.
	BOOL ReportCurrentRecipeNumberChangeBlock(CURRENT_RECIPE_NUMBER_CHANGE_REPORT_BLOCK MachineRecipeBlock);
	BOOL ReportRecipeChangeBlock(RECIPE_CHANGE_REPORT_BLOCK MachineRecipeBlock);
	BOOL ReportRecipeListChangeBlock(RECIPE_LAYER_INFO_REQUEST_REPLY_BLOCK MachineRecipeBlock);
	BOOL ReportCurrentRecipeBlock(PLW_LTM_CURRENT_RECIPE_BLOCK CurrentRecipeBlock);
	BOOL ReportMaterialCountBlock(PMATERIAL_COUNT_CHANGE_REPORT_BLOCK MaterialCountChangeBlock);
	BOOL ReportMaterialStatusBlock(PMATERIAL_STATUS_CHANGE_REPORT_BLOCK MaterialStatus);
	BOOL ReportMagazineProcessCompleteBlock_1(MAGAZINE_PROCESS_COMPLETE_REPORT_BLOCK MagazineProcessCompleteBlock, MAGAZINE_PROCESS_COMPLETE_REPORT_SUBBLOCK MagazineProcessCompleteSubBlock);
	BOOL ReportMagazineProcessCompleteBlock_2(MAGAZINE_PROCESS_COMPLETE_REPORT_BLOCK MagazineProcessCompleteBlock, MAGAZINE_PROCESS_COMPLETE_REPORT_SUBBLOCK MagazineProcessCompleteSubBlock);
	BOOL ReportMagazineProcessCompleteBlock_3(MAGAZINE_PROCESS_COMPLETE_REPORT_BLOCK MagazineProcessCompleteBlock, MAGAZINE_PROCESS_COMPLETE_REPORT_SUBBLOCK MagazineProcessCompleteSubBlock);
	BOOL ReportMagazineProcessCompleteBlock_4(MAGAZINE_PROCESS_COMPLETE_REPORT_BLOCK MagazineProcessCompleteBlock, MAGAZINE_PROCESS_COMPLETE_REPORT_SUBBLOCK MagazineProcessCompleteSubBlock);
	BOOL ReportMagazineProcessCompleteBlock_5(MAGAZINE_PROCESS_COMPLETE_REPORT_BLOCK MagazineProcessCompleteBlock, MAGAZINE_PROCESS_COMPLETE_REPORT_SUBBLOCK MagazineProcessCompleteSubBlock);
	BOOL ReportMagazineProcessCompleteBlock_6(MAGAZINE_PROCESS_COMPLETE_REPORT_BLOCK MagazineProcessCompleteBlock, MAGAZINE_PROCESS_COMPLETE_REPORT_SUBBLOCK MagazineProcessCompleteSubBlock);
	BOOL ReportMagazineDataRequestBlock (MAGAZINE_DATA_REQUEST_BLOCK MagazineRequestDataBlock);
	BOOL ReportMachineStatusBlock(MACHINE_STATUS_CHANGE_REPORT_BLOCK MachineStatusBlock);

	
	//Report --------------------------------------
	BOOL ReportSheetMoveInBlock(SHEET_MOVE_IN_REPORT_BLOCK SheetMoveInBlock);
	BOOL ReportSheetMoveOutBlock(SHEET_MOVE_OUT_REPORT_BLOCK SheetMoveOutBlock);
	BOOL RequestSheetInformation(PSHEET_INFORMATION_BLOCK SheetInformationRequestBlock);
	BOOL UpdateSheetInformation(METERIAL_SHEET_DATA_UPDATE_REPORT_BLOCK SheetInfo);
	BOOL DownloadSheetInformation(MATERIAL_SHEET_DATA_DOWNLOAD_REQUEST_BLOCK SheetInfo);
	BOOL RemoveSheetInformation();

	BOOL MaskLoadRequestBlock(MASK_LOAD_REQUEST_BLOCK MaskLoadRequest);
	BOOL MaskUnloadRequestBlock(MASK_UNLOAD_REQUEST_BLOCK MaskUnloadRequest);
	BOOL MaskLoadCompleteBlock(MASK_LOAD_COMPLETED_REPORT_BLOCK MaskLoadComplete);
	BOOL MaskUnoadCompleteBlock(MASK_UNLOAD_COMPLETED_REPORT_BLOCK MaskUnloadRequest);

	BOOL RequestDateTime(DATE_TIME_REQUEST_BLOCK DateTimeRequestBlock);
	//-------------------------------------------------------------
	BOOL ReportCimMessageConfrimBlock(CIM_MESSAGE_CONFIRM_REPORT_BLOCK CimMessageConfirmReportBlock);
	BOOL ReportVCRModeBlock(PLW_LTM_VCR_MODE_BLOCK VCRModeBlock);
	BOOL RequestEcsJobData(MASK_JOB_DATA_REQUEST_BLOCK JobDataRequestBlock);
	BOOL ReportStartProcess(MASK_PROCESS_START_REPORT_BLOCK ProcessStartReportBlock);
	BOOL ReportEndProcess(MASK_PROCESS_END_REPORT_BLOCK ProcessEndReportBlock);
	BOOL ReportProcessDataBlock(PLW_LTM_PROCESS_DATA_REPORT_BLOCK ProcessDataReportBlock);
	BOOL ReportJobJudgeBlock(MATERIAL_JUDGE_RESULT_REPORT_BLOCK JobJudgeReport);
	//BOOL ReportReceivedJobDataBlock(PLW_LTM_RECEIVED_JOB_DATA_BLOCK ReceivedJobDataBlock); //B12 Not Use //KJT 20210325

	//KJT
	BOOL ReportMaterialJudgeBlock(MATERIAL_JUDGE_RESULT_REPORT_BLOCK MaterialJudgeReport);

	BOOL ReportVcrEventBlock(PLW_LTM_VCR_EVENT_REPORT_BLOCK VCREventReportBlock);

	//Job Data Report
	BOOL ReportSentOutEcsJobData(PMASK_JOB_DATA JobData, JOB_COUNT_BLOCK JobCountBlock);
	BOOL ReportStoredEcsJobData(MASK_STORED_JOB_REPORT_BLOCK StoredJobDataBlock);
	BOOL ReportReceivedEcsJobData(MASK_RECEIVED_JOB_REPORT_BLOCK ReceivedJobDataBlock);
	BOOL ReportFetchedOutEcsJobData(MASK_FETCHED_OUT_JOB_REPORT_BLOCK FetchedOutJobDataBlock);
	BOOL ReportJobCntBlock(JOB_COUNT_BLOCK JobCountBlock);
	BOOL ReportRecipeParameterBlock(PLW_LTM_RECIPE_PARAMETER_BLOCK RecipeParameterBlock);
	//BOOL ReportJobDataSendBlock(PMASK_JOB_DATA JobData); //B12 Not Use //KJT 20210325
	BOOL ReportJobDataChangeBlock(MASK_JOB_DATA_CHANGE_REPORT_BLOCK JobData);

	//Reply
	BOOL ReplyCimModeChangeCmdBlock(PLW_MTL_CIM_MODE_CHANGE_COMMAND_REPLY_BLOCK CimModeChagneCommandReplyBlock);
#endif
	//잡데이터 사용 함수.
	BOOL ReceivedEcsJobData();
	BOOL StoredEcsJobData();
	BOOL FetchedOutEcsJobData();

	//Flow 사용 함수.
	BOOL SetMachineRun();
	BOOL SetMachineIdle();
	BOOL SetMachinePause();
	BOOL SetMachinePm();
	BOOL SetMachineBm();
	BOOL SetMachineInitValue();

	BOOL SetCimModeOnOff(BOOL bOnOff);
	BOOL SetMachineAutoModeOnOff(BOOL bOnOff);
	BOOL SetUpstreamInlineOnOff(BOOL bOnOff);
	BOOL SetDownstreamInlineOnOff(BOOL bOnOff);
	BOOL SetAutoRecipeOnOff(BOOL bOnOff);
	BOOL SetAutoCassetteVcrOnOff(BOOL bOnOff);
	BOOL SetAutoCassetteVcrKeyInOption(INT nKeyin);

	BOOL SetStartProcess();
	BOOL SetEndProcess();

	BOOL DVDataReport();
	BOOL CVDataReport();

	BOOL SetProcessData();
	BOOL SetJobJudge();

	BOOL SetMaterialJudge();
	void GenerateDVList(PDV_LIST DVList);

	//BOOL ClearEcsError(INT nIndex);
	//BOOL ClearEcsAllError();

	//Robot 관련 -------------------------------------------------------------------------------------------
	//Write
	//Cancle Request.
	BOOL IsCancleRequest();

	//Frame Unloading
	BOOL ResetUpStreamStageCimData();
	BOOL SetUpStreamInline();

	BOOL SetSignalUpStreamFrameZLeftUp(BOOL bOnOff);
	BOOL SetSignalUpStreamFrameZLeftDn(BOOL bOnOff);
	BOOL SetSignalUpStreamFrameZPinState(BOOL bOnOff);
	BOOL SetSignalUpStreamJobReportOnOff(BOOL bOnOff);
	BOOL SetSignalUpStreamStageSendAble(BOOL bOnOff);
	BOOL SetSignalUpStreamStageShutterOpen(BOOL bOnOff);
	BOOL SetSignalUpStreamStageShutterClose(BOOL bOnOff);
	BOOL SetSignalUpStreamStageShutterState(BOOL bOnOff);
	BOOL SetSignalUpStreamStageSendStart(BOOL bOnOff);
	BOOL SetSignalUpStreamStageSendComplete(BOOL bOnOff);
	BOOL SetSignalUpStreamStageGlassExistArm1(BOOL bOnOff);
	BOOL SetSignalUpStreamStageRun(BOOL bOnOff);
	BOOL SetSignalUpStreamStageIdle(BOOL bOnOff);

	//Check.
	BOOL IsDownStreamRobotReceiveAble();
	BOOL IsDownStreamRobotJobTransferSignal1();
	BOOL IsDownStreamRobotReceiveComplete();

	//Frame Loading. ------------------------------------------
	BOOL ResetDownStreamStageCimData();
	BOOL SetDownStreamInline();

	BOOL SetSignalDownStreamFrameZPinState(BOOL bOnOff);
	BOOL SetSignalDownStreamReceiveAble(BOOL bOnOff);
	BOOL SetSignalDownStreamShutterState(BOOL bOnOff);
	BOOL SetSignalDownStreamReceiveStart(BOOL bOnOff);
	BOOL SetSignalDownStreamReceiveComplete(BOOL bOnOff);

	BOOL SetSignalDownStreamRun(BOOL bOnOff);
	BOOL SetSignalDownStreamIdle(BOOL bOnOff);

	//Check.
	BOOL IsUpStreamRobotSendAble();
	BOOL IsUpStreamRobotSendComplete();

	//IO Managerment
	BOOL SetIoShutterOpen(BOOL bOnOff);
	BOOL SetIoFrameZPinUp(BOOL bOnOff);

	//Job Data Save/Load
	BOOL SaveMaskJobData();
	BOOL LoadMaskJobData();
#if 0 //B12 Not Use  //KJT 20210325
	BOOL SaveJobDataB();
	BOOL LoadJobDataB();
#endif
	///////////////////////////////////////////////////////////////

	char* ConvertPlcString(CString strData);
	


	//20201215 Night Work - Parkcm
	BOOL ReportMachineModeChange(MACHINE_MODE_CHANGE_REPORT_BLOCK MachineModeChangeReport);
	BOOL ReportOperatorLogin(OPERATOR_LOGIN_REPORT_BLOCK OperatorLoginReport);
	BOOL ReportJobManualMove(MASK_JOB_MANUAL_MOVE_REPORT_BLOCK JobManualMoveReport);
	BOOL ReportSheetAssemblyComplete(SHEET_ASSEMBLY_COMPLETE_REPORT_BLOCK SheetAssemblyCompleteReportBlock);

	BOOL PositionJobStatus(POSITION_JOB_BLOCK PositionJobBlock);
};

