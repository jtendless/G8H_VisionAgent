#include "stdafx.h"
#include "CimModule.h"
//#include "Vision/Devs.h"
#include "Common/CommonDefine.h"
#include "CimInfo.h"
#include "Vision/Devs.h"

CCimModule::CCimModule()
{
	
}


CCimModule::~CCimModule()
{

}

BOOL CCimModule::InitProcess()
{
	m_dAliveTimer = 30000; // 4000; //KJT 20210324

#if 0 //KJT 20210325 Temp
	MelsecOpen(151, 1, 0, 255);

	//MelsecOpen(short sChannelNo, long lChannelPath, long lNetworkNo, long lStationNo)
	pThread = AfxBeginThread(RobotThreadFunction, this);
	pThread = AfxBeginThread(ReceiveThreadFunction, this);
#endif

	return TRUE;
}

BOOL CCimModule::EndProcess()
{
	m_RobotFinish = FALSE;

	do
	{
		Sleep(10);
	} while (m_RobotFinishOK == FALSE);

	m_ReceiveFinish = FALSE;

	do
	{
		Sleep(10);
	} while (m_ReceiveFinishOK == FALSE);


	return TRUE;

}

UINT CCimModule::RobotThreadFunction(LPVOID lpParam)
{
	CCimModule* pModule = NULL;
	pModule = (CCimModule*)lpParam;

	pModule->m_RobotFinishOK = FALSE;

	pModule = (CCimModule*)lpParam;

	pModule->RobotThreadFunctionEntry();

	pModule->m_RobotFinishOK = TRUE;

	return 0;
}

UINT CCimModule::ReceiveThreadFunction(LPVOID lpParam)
{
	CCimModule* pModule = NULL;
	pModule = (CCimModule*)lpParam;
	pModule->m_ReceiveFinishOK = FALSE;	
	pModule->m_ReceiveFinish = TRUE;
	pModule->CimReceiveThreadFunctionEntry();

	pModule->m_ReceiveFinishOK = TRUE;

	return 0;
}

VOID CCimModule::CimReceiveThreadFunctionEntry(VOID)
{
//	BYTE bValue;
//	JOB_DATA_REQUEST_REPLY_BLOCK JobDataRequestReplyBlock;
//	MASK_JOB_DATA_REQUEST_BLOCK JobDataRequestBlock;
//
//	RECIPE_REGISTER_CHECK_COMMAND_SEND_REPLY_BLOCK RecipeRegisterCheckReturnCodeBlock;
//	RECIPE_PARAMETER_REQUEST_REPY_BLOCK	RecipeParameterBlock;
//	CIM_MODE_CHANGE_COMMAND_SEND_BLOCK CimModeChangeCommandBlock;
//	CIM_MESSAGE_SET_COMMAND_SEND_BLOCK CImMessageSetCommandBlock;
//	CIM_MESSAGE_CLEAR_COMMAND_SEND_BLOCK CImMessageClearCommandBlock;
//	DATE_TIME_SET_COMMAND_SEND_BLOCK DateTimeSetCommandBlock;
//	CIM_MODE_CHANGE_COMMAND_SEND_REPLY_BLOCK CimModeChagneCommandReplyBlock;
//
//	MACHINE_MODE_CHANGE_COMMAND_SEND_REPLY_BLOCK MachineModeChangeSendReplyBlock;
//	RECIPE_REGISTER_CHECK_COMMAND_SEND_BLOCK RecipeRegisterCheckBlock;
//	RECIPE_PARAMETER_REQUESt_BLOCK RecipeParameterRequestBlock;
//	RECIPE_KEY_PARAMETER_REQUEST_BLOCK	RecipeKeyParameterRequestBlock;
//	RECIPE_KEY_PARAMETER_REQUEST_REPLY_BLOCK	RecipeKeyParamterRequestReplyBlock;
//
//	MATERIAL_STATUS_CHANGE_REPORT_BLOCK        MeterialStatusChangeReportBlock;
//
//	MAGAZINE_PROCESS_COMPLETE_REPORT_BLOCK  MagazineProcessCompleteReportBlock;
//	MAGAZINE_DATA_REQUEST_BLOCK				MagazineDataRequestBlock;
//	MAGAZINE_DATA_REQUEST_REPLY_BLOCK		MagazineDataRequestReplyBlock[6];
//
//	METERIAL_SHEET_DATA_UPDATE_REPORT_BLOCK  MeterialSheetDataUpdataReportBlock;
//
//	MATERIAL_SHEET_DATA_DOWNLOAD_REQUEST_BLOCK	MeterialSheetDataDownloadRequestBlock;
//	MATERIAL_SHEET_DATA_DOWNLOAD_REQUEST_REPLY_BLOCK	MeterialSheetDataDownloadRequestReplyBlock;
//
//
//	CV_REPORT_TIME_CHANGE_COMMAND_SEND_BLOCK		CVReportTimeChangeCommandSendBlock;
//	CV_REPORT_TIME_CHANGE_COMMAND_SEND_REPLY_BLOCK	CVReportTimeChangeCommandSendReplyBlock;
//	MACHINE_MODE_CHANGE_COMMAND_SEND_BLOCK			MachineModeChangeCommandSendBlock;
//	MACHINE_MODE_CHANGE_COMMAND_SEND_REPLY_BLOCK		MachineModeChangeCommandSendReplyBlock;
//	TRACE_DATA_REPORT_BLOCK TraceDataBlock;
//	LW_MTL_VCR_MODE_CHANGE_COMMAND_BLOCK VCRModeChangeCommandBlock;
//	LW_MTL_MATERIAL_GROUP_DATA_BLOCK MaterialGroupDataBlock;
//
//	CIM_MESSAGE_SET_COMMAND_SEND_REPLY_BLOCK CimMessageSetCommmandSendReplayBlock;
//	CIM_MESSAGE_CLEAR_COMMAND_SEND_REPLY_BLOCK CimMessageClearCommmandSendReplayBlock;
//
//	DATE_TIME_SET_COMMAND_SEND_REPLY_BLOCK DateTimeSetCommandSendReplyBlock;
//	DATA_TIME_REQUEST_REPLY_BLOCK DateTimeRequestReplyBlock;
//
//	//20201215 Night Work - Parkcm
//	MASK_RELOAD_COMMAND_SEND_BLOCK MaskReloadCommandSendBlock;
//	MASK_JOB_DOWNLOAD_SEND_SUB_BLOCK MaskJobDownloadSendSubBlock; //KJT 20210409
//	MASK_JOB_DOWNLOAD_SEND_BLOCK MaskJobDownloadSendBlock;
//	MASK_JOB_DOWNLOAD_SEND_REPLY_BLOCK MaskJobDownloadSendReplyBlock;
//	RECIPE_LAYER_INFO_REQUEST_BLOCK RecipeLayerInfoRequestBlock;
//	RECIPE_LAYER_INFO_REQUEST_REPLY_BLOCK RecipeLayerInfoRequestReplyBlock;
//	RECIPE_STEP_COUNT_REQUEST_BLOCK RecipeStepCountRequestBlock;
//	RECIPE_STEP_COUNT_REQUEST_REPLY_BLOCK RecipeStepCountRequestReplyBlock;
//	RECIPE_PARAMETER_DATA_DOWNLOAD_SEND_BLOCK RecipeParameterDataDownloadSendBlock;
//	RECIPE_PARAMETER_DATA_DOWNLOAD_SEND_REPLY_BLOCK RecipeParameterDataDownloadSendReplyBlock;
//	MASK_RELOAD_COMMAND_SEND_REPLY_BLOCK MaskReloadCommandSendReplyBlock;
//
//	CString szMsg;
//	CFile file;
//	BOOL bPrevCIMPCStatus = FALSE;
//	MASK_JOB_DATA	JobDataTemp;
//	DWORD TickCnt;
//	int wResult;
//	SYSTEMTIME LinkTime;
//	HANDLE hToken;
//	TOKEN_PRIVILEGES tp;
//	LUID luid;
//	m_bRevChk = FALSE;
//	int nValue = 1;
//	szMsg.GetBuffer(0);
//	SetAliveTimeOut();
//	SetUpstreamInlineOnOff(TRUE);
//	SetDownstreamInlineOnOff(TRUE);
//	SetLbLtmSelectedEventRun();
//	//pCim->LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//	SetTowerLampTimeOut(2000);
//	SetCIMPCOffStatusTimeOut(4000);
//	BOOL CIMPCOffStatus, CIMPCOnStatus;
//	CString Str = _T("");
//
//	BOOL LampStatusRed = FALSE, LampStatusYellow = FALSE, LampStatusGreen = FALSE, LampStatusBlue = FALSE, BusserStatus = FALSE;
//
//	SetMachineInitValue();
//
//	Etc_Msg(_T("[Cim] Send : Machine Stauts Change Report"));
//
//	SetT1TimeOut();
//	SetT3TimeOut();
//	while (m_ReceiveFinish)
//	{
//#if 0
//		//연결 초기화 될때까지 Wait
//		if (!m_pCim->IsEntry())
//			continue;
//#endif
//
//		if (IsCVTimeOut() == TRUE)
//		{
//
//			if (CimInfo::m_CVTimerCount > 0)
//			{
//				CVDataReport();
//				CimInfo::m_CVTimerCount--;
//			}
//			SetCVTimeOut();
//		}
//		int nCnt = 0;
//		if (IsT3TimeOut() == TRUE)
//		{
//			if (CimInfo::CIMMessageBufferCnt > 0)
//			{
//				if (nCnt > 9)
//				{
//					CimInfo::CIMMessageBufferCnt--;
//					continue;
//				}
//				
//				CimInfo::CIMMessageBufferCnt--;
//				nCnt++;
//				if (CimInfo::CIMMessageBufferCnt < 0)
//					CimInfo::CIMMessageBufferCnt = 0;
//			}
//			if (CimInfo::m_CimMode == 2)
//			{
//				if (CimInfo::RecipeChangeReportBlockCnt > 0)
//				{
//					LWWrite(RECIPE_CHANGE_REPORT_BLOCK_START_ADDRESS, &CimInfo::RecipeChangeReportBlockBuffer[0], sizeof(RECIPE_CHANGE_REPORT_BLOCK));
//					CimInfo::m_LBLTM.MachineEvent_RecipeChangeReport = TRUE;
//					LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//					CimInfo::RecipeChangeReportBlockCnt--;
//				}
//
//		
//			}
//			SetT3TimeOut();
//		}
//#pragma region Tower Lamp
//		if (IsTowerLampTimeOut())
//		{
//			ClearTowerLampTimeOut();
//			//Red
//			if (CimInfo::m_TowerLampStatusRed == TOWER_LAMP_ON)
//			{
//				if (SharedInfo::DOutputValue[_DOUT_TOWER_LAMP_RED] == 0)
//				{
//					SetDOutputBitValue(_DOUT_TOWER_LAMP_RED, TRUE);
//					LampStatusRed = TRUE;
//				}
//			}
//			else if (CimInfo::m_TowerLampStatusRed == TOWER_LAMP_OFF)
//			{
//				if (SharedInfo::DOutputValue[_DOUT_TOWER_LAMP_RED] == 1)
//				{
//					SetDOutputBitValue(_DOUT_TOWER_LAMP_RED, FALSE);
//					LampStatusRed = FALSE;
//				}
//			}
//			else if (CimInfo::m_TowerLampStatusRed == TOWER_LAMP_BLINK)
//			{
//				LampStatusRed = SharedInfo::DOutputValue[_DOUT_TOWER_LAMP_RED];
//				if (SharedInfo::DOutputValue[_DOUT_TOWER_LAMP_RED] == 1)
//				{
//					SetDOutputBitValue(_DOUT_TOWER_LAMP_RED, FALSE);
//				}
//				else
//				{
//					SetDOutputBitValue(_DOUT_TOWER_LAMP_RED, TRUE);
//				}
//
//			}
//			//Yellow
//			if (CimInfo::m_TowerLampStatusYellow == TOWER_LAMP_ON)
//			{
//				if (SharedInfo::DOutputValue[_DOUT_TOWER_LAMP_YELLOW] == 0)
//				{
//					SetDOutputBitValue(_DOUT_TOWER_LAMP_YELLOW, TRUE);
//					LampStatusYellow = TRUE;
//				}
//			}
//			else if (CimInfo::m_TowerLampStatusYellow == TOWER_LAMP_OFF)
//			{
//				if (SharedInfo::DOutputValue[_DOUT_TOWER_LAMP_YELLOW] == 1)
//				{
//					SetDOutputBitValue(_DOUT_TOWER_LAMP_YELLOW, FALSE);
//					LampStatusYellow = FALSE;
//				}
//			}
//			else if (CimInfo::m_TowerLampStatusYellow == TOWER_LAMP_BLINK)
//			{
//				if (CimInfo::m_TowerLampStatusRed == TOWER_LAMP_BLINK)
//				{
//					LampStatusYellow = LampStatusRed;
//					SetDOutputBitValue(_DOUT_TOWER_LAMP_YELLOW, LampStatusYellow);
//				}
//				else
//				{
//					LampStatusYellow = SharedInfo::DOutputValue[_DOUT_TOWER_LAMP_YELLOW];
//					if (LampStatusYellow == 1)
//					{
//						SetDOutputBitValue(_DOUT_TOWER_LAMP_YELLOW, FALSE);
//					}
//					else
//					{
//						SetDOutputBitValue(_DOUT_TOWER_LAMP_YELLOW, TRUE);
//					}
//
//				}
//			}
//
//			//Green
//			if (CimInfo::m_TowerLampStatusGreen == TOWER_LAMP_ON)
//			{
//				if (SharedInfo::DOutputValue[_DOUT_TOWER_LAMP_GREEN] == 0)
//				{
//					SetDOutputBitValue(_DOUT_TOWER_LAMP_GREEN, TRUE);
//					LampStatusGreen = TRUE;
//				}
//			}
//			else if (CimInfo::m_TowerLampStatusGreen == TOWER_LAMP_OFF)
//			{
//				if (SharedInfo::DOutputValue[_DOUT_TOWER_LAMP_GREEN] == 1)
//				{
//					SetDOutputBitValue(_DOUT_TOWER_LAMP_GREEN, FALSE);
//					LampStatusGreen = FALSE;
//				}
//			}
//			else if (CimInfo::m_TowerLampStatusGreen == TOWER_LAMP_BLINK)
//			{
//				if (CimInfo::m_TowerLampStatusRed == TOWER_LAMP_BLINK)
//				{
//					LampStatusGreen = LampStatusRed;
//					SetDOutputBitValue(_DOUT_TOWER_LAMP_GREEN, LampStatusGreen);
//				}
//				else if (CimInfo::m_TowerLampStatusYellow == TOWER_LAMP_BLINK)
//				{
//					LampStatusGreen = LampStatusYellow;
//					SetDOutputBitValue(_DOUT_TOWER_LAMP_GREEN, LampStatusGreen);
//				}
//				else
//				{
//					if (SharedInfo::DOutputValue[_DOUT_TOWER_LAMP_GREEN] == 1)
//					{
//						SetDOutputBitValue(_DOUT_TOWER_LAMP_GREEN, FALSE);
//					}
//					else
//					{
//						SetDOutputBitValue(_DOUT_TOWER_LAMP_GREEN, TRUE);
//					}
//				}
//
//			}
//#if 0
//			//Blue
//			if (CimInfo::m_TowerLampStatusBlue == TOWER_LAMP_ON)
//			{
//				SetDOutputBitValue(_TOWER_LAMP_BLUE, TRUE);
//				LampStatusBlue = TRUE;
//			}
//			else if (CimInfo::m_TowerLampStatusBlue == TOWER_LAMP_OFF)
//			{
//				SetDOutputBitValue(_TOWER_LAMP_BLUE, FALSE);
//				LampStatusBlue = FALSE;
//			}
//			else if (CimInfo::m_TowerLampStatusBlue == TOWER_LAMP_BLINK)
//			{
//				SetDOutputBitValue(_TOWER_LAMP_BLUE, LampStatusBlue);
//				LampStatusBlue = !LampStatusBlue;
//			}
//#endif
//
//			if (CimInfo::m_BuzzerFast == TRUE)
//			{
//				if (BusserStatus == FALSE)
//					SetDOutputBitValue(_DOUT_BUZZER_01, TRUE);
//				BusserStatus = TRUE;
//
//			}
//			else
//			{
//				if (BusserStatus == TRUE)
//					SetDOutputBitValue(_DOUT_BUZZER_01, FALSE);
//				BusserStatus = FALSE;
//			}
//			SetTowerLampTimeOut(1200);
//		}
//#pragma endregion
//#if 0
//		//Awking Open Check.
//		if (!m_pCim->IsOpen())
//		{
//			Sleep(1000);
//			continue;
//		}
//#endif
//		//Awking m_Alarm Cnt Int Max 치 이상 되는지 확인 필요.
//		if (CimInfo::m_AlarmCount > 100)
//			//CimInfo::m_AlarmCount = 0;
//			continue;
//
//#pragma region Event Receive
//		LBRead(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(CimInfo::m_LBLTM));
//		LBRead(LB_MTL_START_ADDRESS, &CimInfo::m_LBMTL, sizeof(CimInfo::m_LBMTL));
//		Sleep(100);
//
//		//Awking 없어도 되는 코드? Need Check.
//		//if (CimInfo::m_LBLTM.bMachineStatusCIMMode == TRUE)
//		//	m_pCim->GetLbMtlBufData(LB_MTL_START_ADDRESS, &CimInfo::m_LBMTL, sizeof(CimInfo::m_LBMTL));
//		//else
//		//{
//		//	continue;
//		//}
//#pragma endregion
//
//#pragma region CIM State Check
//		if (IsAliveTimeOut())
//		{
//			CimInfo::m_LBLTM.MachineStatus_MachineHeartBeatSignalBit = !CimInfo::m_LBLTM.MachineStatus_MachineHeartBeatSignalBit;
//			//위치 이동.
//			SetLbLtmSelectedEventRun();
//
//			SetAliveTimeOut();
//		}
//		//TODO Check - parkcm_20201213
//		CIMPCOnStatus = CimInfo::m_LBMTL.CIMPCStatus_NoneProcessGlassSignal;
//		//	CIMPCOnStatus = false;
//		if (CIMPCOnStatus != bPrevCIMPCStatus)
//		{
//			bPrevCIMPCStatus = CIMPCOnStatus;
//			SetCIMPCOnStatusTimeOut(4000);
//		}
//#if 0
//		if (IsCIMPCOnStatusTimeOut())
//		{
//			if (LampStatusBlue == TRUE)
//				SetDOutputBitValue(_DOUT_TOWER_LAMP_BLUE, FALSE);
//			LampStatusBlue = FALSE;
//		}
//		else
//		{
//			if (LampStatusBlue == FALSE)
//				SetDOutputBitValue(_DOUT_TOWER_LAMP_BLUE, TRUE);
//			LampStatusBlue = TRUE;
//		}
//#endif
//
//		//pCim->LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//#pragma endregion
//
/////////////////////////////////////////////////////////////////////////////////////
////Trace Data
////////////////////////////////////////////////////////////////////////////////////
//#pragma region Trace Data
//		
//		TraceDataBlock.RecipeNumber = SharedInfo::Active.nActiveRecipeNum;
//		Devs::GenerateSVList(&TraceDataBlock.SVData);
//		LWWrite(TRACE_DATA_BLOCK_START_ADDRESS, &TraceDataBlock, sizeof(LW_LTM_TRACE_DATA_BLOCK));
//#pragma endregion
//
//		///////////////////////////////////////////////////////////////////////////////////
//		//Command Reply
//		//////////////////////////////////////////////////////////////////////////////////
//#pragma region Command Reply
//
//#pragma region Cim Mode Change Command Reply //KJT 20210324
//		if (CimInfo::m_LBMTL.CIMPCCommand_CIMModeChangeCommandSend == TRUE &&
//			CimInfo::m_LBLTM.CIMPCCommandReply_CIMModeChangeCommandSendReply == FALSE &&
//			m_CIMAlarmFlag[0] == FALSE)
//		{
//			//1. Machine Cim Mode Change
//			if (CimInfo::m_CimMode == 1) //Off
//			{
//				CimInfo::m_LBLTM.MachineStatus_CIMModeBit = 0; //KJT 20210324
//			}
//			else if (CimInfo::m_CimMode == 2) //On
//			{
//				CimInfo::m_LBLTM.MachineStatus_CIMModeBit = 1; //KJT 20210324
//
//				//KJT 20210324
//				DATE_TIME_REQUEST_BLOCK DateTimeRequestBlock;
//				DateTimeRequestBlock.TouchPanelNumber = 1;
//				//Devs::CimMotion.RequestDateTime(DateTimeRequestBlock);
//			}
//
//			SetLbLtmSelectedEventRun();
//			//pCim->LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			
//
//
//			//2. Reply
//			memset(&CimModeChagneCommandReplyBlock, 0x0, sizeof(CimModeChagneCommandReplyBlock));
//			LWRead(CIM_MODE_CHANGE_COMMAND_BLOCK_START_ADDRESS, &CimModeChangeCommandBlock, sizeof(CimModeChangeCommandBlock));
//#if 1
//			if (CimInfo::m_CimMode == CimModeChangeCommandBlock.CIMMode)
//				CimModeChagneCommandReplyBlock.ReturnCode = 2; //2: Already in Desired Status
//			else
//			{
//				CimInfo::m_CimMode = CimModeChangeCommandBlock.CIMMode;
//				CimModeChagneCommandReplyBlock.ReturnCode = 1; //1:Accept
//			}
//#endif
//
//			//ReplyCimModeChangeCmdBlock(&CimModeChagneCommandReplyBlock);
//			LWWrite(CIM_MODE_CHANGE_COMMAND_REPLY_BLOCK_START_ADDRESS, &CimModeChagneCommandReplyBlock, sizeof(CimModeChagneCommandReplyBlock));
//			CimInfo::m_LBLTM.CIMPCCommandReply_CIMModeChangeCommandSendReply = TRUE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//
//			Str.Format(_T("[Cim] Send : Cim Mode Change Cmd Reply (Returncode:%d)"), CimModeChagneCommandReplyBlock.ReturnCode);
//			Etc_Msg(Str); //KJT 20210324
//			SetT2TimeOut();
//		}
//		else if (CimInfo::m_LBMTL.CIMPCCommand_CIMModeChangeCommandSend == FALSE &&
//			CimInfo::m_LBLTM.CIMPCCommandReply_CIMModeChangeCommandSendReply == TRUE)
//		{
//			CimInfo::m_LBLTM.CIMPCCommandReply_CIMModeChangeCommandSendReply = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT2TimeOut();
//		}
//		else if (IsT2TimeOut() &&
//			CimInfo::m_LBLTM.CIMPCCommandReply_CIMModeChangeCommandSendReply == TRUE)
//		{
//			m_CIMAlarmFlag[0] = TRUE;
//			CimInfo::m_LBLTM.CIMPCCommandReply_CIMModeChangeCommandSendReply = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT2TimeOut();
//			
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T2_TIMEOUT, ALARM_TYPE_ERROR, TRUE,102, _T("T2 Timeout :Cim Mode Change Command"));
//		}
//		else if (CimInfo::m_LBMTL.CIMPCCommand_CIMModeChangeCommandSend == FALSE)
//			m_CIMAlarmFlag[0] = FALSE;
//#pragma endregion
//
//
//#pragma region Machine Mode Change Command reply
//		if (CimInfo::m_LBMTL.CIMPCCommand_MachineModeChangeCommandSend == TRUE &&
//			CimInfo::m_LBLTM.CIMPCCommandReply_MachineModeChangeCommandSendReply == FALSE &&
//			m_CIMAlarmFlag[0] == FALSE)
//		{
//			memset(&MachineModeChangeCommandSendBlock, 0x0, sizeof(MachineModeChangeCommandSendBlock));
//
//			LWRead(MACHINE_MODE_CHANGE_COMMAND_SEND_BLOCK_START_ADDRESS, &MachineModeChangeCommandSendBlock, sizeof(MachineModeChangeCommandSendBlock));
//			Str.Format(_T("[Cim] << CIMPCCommand_MachineModeChangeCommandSend (MachineMode:%d)"), MachineModeChangeCommandSendBlock.MachineMode);
//			Etc_Msg(Str);
//#if 1
//			if (SharedInfo::MachinMode == MachineModeChangeCommandSendBlock.MachineMode)
//				MachineModeChangeCommandSendReplyBlock.MachineModeChangeReturnCode = 2;
//			else if (MachineModeChangeCommandSendBlock.MachineMode != 1 && MachineModeChangeCommandSendBlock.MachineMode != 5) //KJT 20210324
//				MachineModeChangeCommandSendReplyBlock.MachineModeChangeReturnCode = 3;
//			else
//			{
//				MachineModeChangeCommandSendReplyBlock.MachineModeChangeReturnCode = 1;
//
//				//KJT 20210324
//				SharedInfo::MachinMode = MachineModeChangeCommandSendBlock.MachineMode;
//				MACHINE_MODE_CHANGE_REPORT_BLOCK MachinMode;
//				MachinMode.MachineMode = SharedInfo::MachinMode;
//				//Devs::CimMotion.ReportMachineModeChange(MachinMode);
//			}
//			
//#endif
//
//			//ReplyCimModeChangeCmdBlock(&CimModeChagneCommandReplyBlock);
//			LWWrite(MACHINE_MODE_CHANGE_COMMAND_REPLY_BLOCK_START_ADDRESS, &MachineModeChangeCommandSendReplyBlock, sizeof(MachineModeChangeCommandSendReplyBlock));
//			CimInfo::m_LBLTM.CIMPCCommandReply_MachineModeChangeCommandSendReply = TRUE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//
//			Etc_Msg(_T("[Cim] Send : Machine Mode Change cmd Reply"));
//			SetT2TimeOut();
//
//			//pCim->LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//		}
//		else if (CimInfo::m_LBMTL.CIMPCCommand_MachineModeChangeCommandSend == FALSE &&
//			CimInfo::m_LBLTM.CIMPCCommandReply_MachineModeChangeCommandSendReply == TRUE)
//		{
//			CimInfo::m_LBLTM.CIMPCCommandReply_MachineModeChangeCommandSendReply = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT2TimeOut();
//		}
//		else if (IsT2TimeOut() &&
//			CimInfo::m_LBLTM.CIMPCCommandReply_MachineModeChangeCommandSendReply == TRUE)
//		{
//			m_CIMAlarmFlag[0] = TRUE;
//			CimInfo::m_LBLTM.CIMPCCommandReply_MachineModeChangeCommandSendReply = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT2TimeOut();
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T2_TIMEOUT, ALARM_TYPE_ERROR, TRUE,102, _T("T2 Timeout :MAchine Mode Change Command"));
//		}
//		else if (CimInfo::m_LBMTL.CIMPCCommand_CIMModeChangeCommandSend == FALSE)
//			m_CIMAlarmFlag[0] = FALSE;
//#pragma endregion
//
//#pragma region CimMessage Set
//		if (CimInfo::m_LBMTL.CIMPCCommand_CIMMessageSetCommandSend == TRUE &&
//			CimInfo::m_LBLTM.CIMPCCommandReply_CIMMessageSetCommandSendReply == FALSE &&
//			m_CIMAlarmFlag[1] == FALSE)
//		{
//			LWRead(CIM_MESSAGE_SET_COMMAND_BLOCK_START_ADDRESS, &CImMessageSetCommandBlock, sizeof(CIM_MESSAGE_SET_COMMAND_SEND_BLOCK));
//		
//
//		
//			CimMessageSetCommmandSendReplayBlock.ReturnCode = 1;
//			for (int i = 0; i < 10; i++)
//			{
//				if (CimInfo::CIMMessage[i].CimMessageID == CImMessageSetCommandBlock.CIMMessageID)
//					CimMessageSetCommmandSendReplayBlock.ReturnCode = 1; //1:OK
//			}
//
//			//KJT 20210324
//			if (CImMessageSetCommandBlock.CIMMessageType != eCIM_MESSAGE_TYPE_ERROR &&
//				CImMessageSetCommandBlock.CIMMessageType != eCIM_MESSAGE_TYPE_WARNING &&
//				CImMessageSetCommandBlock.CIMMessageType != eCIM_MESSAGE_TYPE_INFORMATION)
//				CimMessageSetCommmandSendReplayBlock.ReturnCode = 2; //2:NG
//
//			LWWrite(CIM_MESSAGE_SET_COMMAND_SEND_REPLY_BLOCK_START_ADDRESS, &CimMessageSetCommmandSendReplayBlock, sizeof(CimModeChagneCommandReplyBlock));
//
//
//			if (CimMessageSetCommmandSendReplayBlock.ReturnCode == 1) //1:OK
//			{
//#if 0
//				if (CimInfo::CIMMessageCnt < 9)
//				{
//					for (int i = 9; i > 0; i--)
//					{
//						CimInfo::CIMMessage[i] = CimInfo::CIMMessage[i - 1];
//					}
//
//				}
//				else
//				{
//					CimInfo::CIMMessageCnt = 9;
//				}
//#else
//					for (int i = 9; i > 0; i--)
//					{
//						memcpy(&CimInfo::CIMMessage[i], &CimInfo::CIMMessage[i - 1], sizeof(CimInfo::CIMMessage[i]));
//					}
//
//#endif
//				CimInfo::CIMMessage[0].CimMessageID = CImMessageSetCommandBlock.CIMMessageID;
//				for (int i = 0; i < 16; i++)
//					CimInfo::CIMMessage[0].CimMessage[i] = CImMessageSetCommandBlock.CIMMessageData[i];
//				GetLocalTime(&LinkTime);
//				CimInfo::CIMMessage[0].CiMReceiveDate.Format(_T("%d/%2d/%2d %2d:%2d:%2d")
//					, LinkTime.wYear, LinkTime.wMonth, LinkTime.wDay, LinkTime.wHour, LinkTime.wMinute, LinkTime.wSecond);
//
//			}
//			CimInfo::m_LBLTM.CIMPCCommandReply_CIMMessageSetCommandSendReply = TRUE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			Etc_Msg(_T("[Cim] Send : Cim Message Set cmd Reply"));
//			SetT2TimeOut();
//			CimInfo::CIMMessageCnt++;
//
//		}
//		else if (CimInfo::m_LBMTL.CIMPCCommand_CIMMessageSetCommandSend == FALSE &&
//			CimInfo::m_LBLTM.CIMPCCommandReply_CIMMessageSetCommandSendReply == TRUE)
//		{
//			CimInfo::m_LBLTM.CIMPCCommandReply_CIMMessageSetCommandSendReply = FALSE;
//			memset(&CImMessageSetCommandBlock, 0x0, sizeof(LW_MTL_CIM_MESSAGE_SET_COMMAND_BLOCK));
//
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT2TimeOut();
//		}
//		else if (IsT2TimeOut() &&
//			CimInfo::m_LBLTM.CIMPCCommandReply_CIMMessageSetCommandSendReply == TRUE)
//		{
//			CimInfo::m_LBLTM.CIMPCCommandReply_CIMMessageSetCommandSendReply = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			m_CIMAlarmFlag[1] = TRUE;
//			ClearT2TimeOut();
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T2_TIMEOUT, ALARM_TYPE_ERROR, TRUE,102, _T("T2 Timeout :Cim Message Set Command"));
//
//		}
//		else if (CimInfo::m_LBMTL.CIMPCCommand_CIMMessageSetCommandSend == FALSE)
//		{
//			m_CIMAlarmFlag[1] = FALSE;
//		}
//#pragma endregion	
//
//#pragma region CimMessage Clear
//		if (CimInfo::m_LBMTL.CIMPCCommand_CIMMessageClearCommandSend == TRUE &&
//			CimInfo::m_LBLTM.CIMPCCommandReply_CIMMessageClearCommandSendReply == FALSE &&
//			m_CIMAlarmFlag[2] == FALSE)
//		{
//			LWRead(CIM_MESSAGE_CLEAR_COMMAND_BLOCK_START_ADDRESS, &CImMessageClearCommandBlock, sizeof(CIM_MESSAGE_CLEAR_COMMAND_SEND_BLOCK));
//			memset(&CimMessageClearCommmandSendReplayBlock, 0x0, sizeof(CimMessageClearCommmandSendReplayBlock));
//			CimMessageClearCommmandSendReplayBlock.ReturnCode = 2; //2:NG
//			for (int i = 0; i < 10; i++)
//			{
//				if (CimInfo::CIMMessage[i].CimMessageID == CImMessageClearCommandBlock.CIMMessageID)
//				{
//					for (int j = i; j < 9; j++)
//					{
//						memcpy(&CimInfo::CIMMessage[j], &CimInfo::CIMMessage[j + 1], sizeof(CimInfo::CIMMessage[j]));
//					}
//					memset(&CimInfo::CIMMessage[9], 0x0, sizeof(CimInfo::CIMMessage[9]));
//					CimMessageClearCommmandSendReplayBlock.ReturnCode = 1; //1:OK
//					break;
//				}
//			}
//			
//		
//			LWWrite(CIM_MESSAGE_CLEAR_COMMAND_SEND_REPLY_BLOCK_START_ADDRESS, &CimMessageClearCommmandSendReplayBlock, sizeof(CimMessageClearCommmandSendReplayBlock));
//
//			CimInfo::m_LBLTM.CIMPCCommandReply_CIMMessageClearCommandSendReply = TRUE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			Etc_Msg(_T("[Cim] Send : Cim Message Clear cmd Reply"));
//			SetT1TimeOut();
//			CimInfo::CIMMessageCnt--;
//			if (CimInfo::CIMMessageCnt < 0)
//				CimInfo::CIMMessageCnt = 0;
//
//		}
//		else if (CimInfo::m_LBMTL.CIMPCCommand_CIMMessageClearCommandSend == FALSE &&
//			CimInfo::m_LBLTM.CIMPCCommandReply_CIMMessageClearCommandSendReply == TRUE)
//		{
//			CimInfo::m_LBLTM.CIMPCCommandReply_CIMMessageClearCommandSendReply = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT2TimeOut();
//		}
//		else if (IsT2TimeOut() && CimInfo::m_LBLTM.CIMPCCommandReply_CIMMessageClearCommandSendReply == TRUE)
//		{
//			m_CIMAlarmFlag[2] = TRUE;
//			CimInfo::m_LBLTM.CIMPCCommandReply_CIMMessageClearCommandSendReply = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT2TimeOut();
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T2_TIMEOUT, ALARM_TYPE_ERROR, TRUE,102, _T("T2 Timeout :Cim Message Clear Command"));
//
//		}
//		else if (CimInfo::m_LBMTL.CIMPCCommand_CIMMessageClearCommandSend == FALSE)
//			m_CIMAlarmFlag[2] = FALSE;
//#pragma endregion	
//
//#pragma region Date Time Set Command		
//		if (CimInfo::m_LBMTL.CIMPCCommand_DateTimeSetCommandSend == TRUE &&
//			CimInfo::m_LBLTM.CIMPCCommandReply_DateTimeSetCommandSendReply == FALSE &&
//			m_CIMAlarmFlag[3] == FALSE)
//		{
//			LWRead(DATE_TIME_SET_COMMAND_BLOCK_START_ADDRESS, &DateTimeSetCommandBlock, sizeof(DATE_TIME_SET_COMMAND_SEND_BLOCK));
//
//			GetLocalTime(&LinkTime);
//			LinkTime.wYear = DateTimeSetCommandBlock.DateTimeYear;// *10 + DateTimeSetCommandBlock.DateTime.Year.ValueX10 + 2000;
//			LinkTime.wMonth = DateTimeSetCommandBlock.DateTimeMonth;// *10 + DateTimeSetCommandBlock.DateTime.Month.ValueX10;
//			LinkTime.wDay = DateTimeSetCommandBlock.DateTimeDay;// *10 + DateTimeSetCommandBlock.DateTime.Day.ValueX10;
//			LinkTime.wHour = DateTimeSetCommandBlock.DateTimeHour;//ValueX1 * 10 + DateTimeSetCommandBlock.DateTime.Hour.ValueX10;
//			LinkTime.wMinute = DateTimeSetCommandBlock.DateTimeMinute;// .ValueX1 * 10 + DateTimeSetCommandBlock.DateTime.Minute.ValueX10;
//			LinkTime.wSecond = DateTimeSetCommandBlock.DateTimeSecond;// .ValueX1 * 10 + DateTimeSetCommandBlock.DateTime.Second.ValueX10;
//
//			OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES |
//				TOKEN_QUERY, &hToken);
//			LookupPrivilegeValue(NULL, SE_SYSTEMTIME_NAME, &luid);
//			tp.PrivilegeCount = 1;
//			tp.Privileges[0].Luid = luid;
//			tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
//			AdjustTokenPrivileges(hToken, FALSE, &tp, 0, NULL, NULL);
//			CloseHandle(hToken);
//			bValue =SetLocalTime(&LinkTime);
//
//			memset(&DateTimeSetCommandSendReplyBlock, 0x0, sizeof(DateTimeSetCommandSendReplyBlock));
//			if (bValue == TRUE)
//				DateTimeSetCommandSendReplyBlock.ReturnCode = 1; //1:OK
//			else
//				DateTimeSetCommandSendReplyBlock.ReturnCode = 2; //2:NG
//
//			LWWrite(DATE_TIME_SET_COMMAND_SEND_REPLY_BLOCK_START_ADDRESS, &DateTimeSetCommandSendReplyBlock, sizeof(DateTimeSetCommandSendReplyBlock));
//
//			CimInfo::m_LBLTM.CIMPCCommandReply_DateTimeSetCommandSendReply = TRUE;
//
//			Etc_Msg(_T("[Cim] Send : Date  Time Set Command Reply"));
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			SetT2TimeOut();
//		}
//		else if (CimInfo::m_LBMTL.CIMPCCommand_DateTimeSetCommandSend == FALSE &&
//			CimInfo::m_LBLTM.CIMPCCommandReply_DateTimeSetCommandSendReply == TRUE)
//		{
//			CimInfo::m_LBLTM.CIMPCCommandReply_DateTimeSetCommandSendReply = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT2TimeOut();
//		}
//		else if (IsT2TimeOut() &&
//			CimInfo::m_LBLTM.CIMPCCommandReply_DateTimeSetCommandSendReply == TRUE)
//		{
//			m_CIMAlarmFlag[3] = TRUE;
//			CimInfo::m_LBLTM.CIMPCCommandReply_DateTimeSetCommandSendReply = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT2TimeOut();
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T2_TIMEOUT, ALARM_TYPE_ERROR, TRUE,102, _T("T2 Timeout :Date Time Set Command"));
//		}
//		else if (CimInfo::m_LBMTL.CIMPCCommand_DateTimeSetCommandSend == FALSE)
//			m_CIMAlarmFlag[3] = FALSE;
//#pragma endregion	
//
//#pragma region Recipe Register Check Command 	
//		if (CimInfo::m_LBMTL.CIMPCCommand_RecipeRegisterCheckCommandSend == TRUE &&
//			CimInfo::m_LBLTM.CIMPCCommandReply_RecipeRegisterCheckCommandSendReply == FALSE &&
//			m_CIMAlarmFlag[4] == FALSE)
//		{
//			LWRead(RECIPE_REGISTER_CHECK_BLOCK_START_ADDRESS, &RecipeRegisterCheckBlock, sizeof(RECIPE_REGISTER_CHECK_COMMAND_SEND_BLOCK));
//			wResult = Devs::FindRecipeID(RecipeRegisterCheckBlock.RecipeNumber);
//			
//			if (wResult == -1 || RecipeRegisterCheckBlock.RecipeText !=0x2020)
//				RecipeRegisterCheckReturnCodeBlock.ReturnCode = 2;
//			else
//				RecipeRegisterCheckReturnCodeBlock.ReturnCode = 1;
//			RecipeRegisterCheckReturnCodeBlock.RecipeVersionSequenceNumber = 1;
//			LWWrite(RECIPE_REGISTER_CHECK_RETURN_CODE_START_ADDRESS, &RecipeRegisterCheckReturnCodeBlock, sizeof(RECIPE_REGISTER_CHECK_COMMAND_SEND_REPLY_BLOCK));
//			CimInfo::m_LBLTM.CIMPCCommandReply_RecipeRegisterCheckCommandSendReply = TRUE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//
//			SetT2TimeOut();
//
//		}
//		else if (CimInfo::m_LBLTM.CIMPCCommandReply_RecipeRegisterCheckCommandSendReply == TRUE &&
//			CimInfo::m_LBMTL.CIMPCCommand_RecipeRegisterCheckCommandSend == FALSE)
//		{
//			ClearT2TimeOut();
//			CimInfo::m_LBLTM.CIMPCCommandReply_RecipeRegisterCheckCommandSendReply = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//		}
//		else if (IsT2TimeOut() && CimInfo::m_LBLTM.CIMPCCommandReply_RecipeRegisterCheckCommandSendReply == TRUE)
//		{
//			m_CIMAlarmFlag[4] = TRUE;
//			CimInfo::m_LBLTM.CIMPCCommandReply_RecipeRegisterCheckCommandSendReply = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT2TimeOut();
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T2_TIMEOUT, ALARM_TYPE_ERROR, TRUE,102, _T("T2 Timeout :Recipe Register Check Command"));
//		}
//		else if (CimInfo::m_LBMTL.CIMPCCommand_RecipeRegisterCheckCommandSend == FALSE)\
//			m_CIMAlarmFlag[4] = FALSE;
//#pragma endregion		
//
//#pragma region Recipe Register Parameter Request Command 	//KJT 20210408
//		if (CimInfo::m_LBMTL.CIMPCCommand_RecipeParameterRequest == TRUE &&
//			CimInfo::m_LBLTM.CIMPCCommandReply_RecipeParameterRequestReply == FALSE &&
//			m_CIMAlarmFlag[5] == FALSE)
//		{
//			LWRead(RECIPE_PARAMETER_REQUEST_BLOCK_START_ADDRESS, &RecipeParameterRequestBlock, sizeof(RECIPE_PARAMETER_REQUESt_BLOCK));
//
//			wResult = Devs::FindRecipeID(RecipeParameterRequestBlock.RecipeNumber);
//			memset(&RecipeParameterBlock, 0x0, sizeof(RECIPE_PARAMETER_REQUEST_REPY_BLOCK));
//
//			//if (wResult != -1 && ) //if (wResult != -1 && RecipeParameterBlock.RecipeText == 0x2020)
//			if (wResult != -1 &&
//				((RecipeParameterBlock.RecipeText & 0xFF) == CimInfo::m_MachineRecipeTable.strRecipeName[wResult][0]) && (((RecipeParameterBlock.RecipeText & 0xFF00) >> 8) == CimInfo::m_MachineRecipeTable.strRecipeName[wResult][1]))
//			{
//				RecipeParameterBlock.Result = 1; //1:Recipe Exist
//				//memcpy((char*)RecipeParameterBlock.ParameterValue, (char*)CimInfo::m_MachineRecipeTable.strRecipeName[wResult], 100); //KJT 20210408
//			}
//			else
//			{
//				RecipeParameterBlock.Result = 2; //2:Recipe Not Exist
//				RecipeParameterBlock.ParameterValue[0] = 8224; //KJT 20210408 Not Empy !!
//			}
//
//			RecipeParameterBlock.RecipeText = RecipeParameterRequestBlock.RecipeText;
//			RecipeParameterBlock.RecipeNumber = RecipeParameterRequestBlock.RecipeNumber;
//			RecipeParameterBlock.RecipeVersionSequenceNumber = 1;
//			RecipeParameterBlock.UnitNumber = 1;
//			RecipeParameterBlock.RecipeStepNumber = 1;
//			memcpy((char*)RecipeParameterBlock.ParameterValue, (char*)CimInfo::m_MachineRecipeTable.strRecipeName[wResult], 100);
//			//for (int i = 0; i < 70; i++)
//				//RecipeParameterBlock.wReserved[i] = i + 1;
//
//			LWWrite(RECIPE_PAREMETER_REQUEST_REPLY_BLOCK_START_ADDRESS, &RecipeParameterBlock, sizeof(RECIPE_PARAMETER_REQUEST_REPY_BLOCK));
//			CimInfo::m_LBLTM.CIMPCCommandReply_RecipeParameterRequestReply = TRUE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			SetT2TimeOut();
//
//		}
//		else if (CimInfo::m_LBLTM.CIMPCCommandReply_RecipeParameterRequestReply == TRUE &&
//			CimInfo::m_LBMTL.CIMPCCommand_RecipeParameterRequest == FALSE)
//		{
//			ClearT2TimeOut();
//			CimInfo::m_LBLTM.CIMPCCommandReply_RecipeParameterRequestReply = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//		}
//		else if (IsT2TimeOut() && CimInfo::m_LBLTM.CIMPCCommandReply_RecipeParameterRequestReply == TRUE)
//		{
//			m_CIMAlarmFlag[5] = TRUE;
//			CimInfo::m_LBLTM.CIMPCCommandReply_RecipeParameterRequestReply = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT2TimeOut();
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T2_TIMEOUT, ALARM_TYPE_ERROR, TRUE,102, _T("T2 Timeout :Recipe Parameter Request Command"));
//		}
//		else if (CimInfo::m_LBMTL.CIMPCCommand_RecipeParameterRequest == FALSE)
//			m_CIMAlarmFlag[5] = FALSE;
//		
//#pragma endregion	
//
//
//
//
//#pragma region Recipe Key Parameter Request Reply	
//			if (CimInfo::m_LBMTL.CIMPCCommand_RecipeKeyParameterRequest == TRUE &&
//				CimInfo::m_LBLTM.CIMPCCommandReply_RecipeKeyParameterRequestReply == FALSE &&
//				m_CIMAlarmFlag[5] == FALSE)
//			{
//				LWRead(RECIPE_KEY_PARAMETER_REQUEST_BLOCK_START_ADDRESS, &RecipeKeyParameterRequestBlock, sizeof(RECIPE_KEY_PARAMETER_REQUEST_BLOCK));
//
//				wResult = Devs::FindRecipeID(RecipeKeyParameterRequestBlock.RecipeNumber);
//				//memcpy(&SharedInfo::m_MachineCameraRecipeTable.RecipeValue[wResult], &RecipeKeyParameterRequestBlock, sizeof(RecipeParameterDataDownloadSendBlock.ParameterValue));
//				memset(&RecipeKeyParamterRequestReplyBlock, 0x0, sizeof(RecipeKeyParamterRequestReplyBlock));
//				RecipeKeyParamterRequestReplyBlock.RecipeNumber = RecipeKeyParameterRequestBlock.RecipeNumber;
//				RecipeKeyParamterRequestReplyBlock.RecipeText = RecipeKeyParameterRequestBlock.RecipeText;
//
//				if (wResult != -1 && RecipeKeyParamterRequestReplyBlock.RecipeText == 0x2020)
//				{
//					RecipeKeyParamterRequestReplyBlock.Result = 1;
//					RecipeKeyParamterRequestReplyBlock.ParameterValue[0] = 'k';
//					RecipeKeyParamterRequestReplyBlock.ParameterValue[1] = 'e';
//					RecipeKeyParamterRequestReplyBlock.ParameterValue[2] = 'y';
//					RecipeKeyParamterRequestReplyBlock.ParameterValue[3] = '\r';
//				}
//				else
//				{
//					memset(RecipeKeyParamterRequestReplyBlock.ParameterValue, 0x0, sizeof(RecipeKeyParamterRequestReplyBlock.ParameterValue));
//					RecipeKeyParamterRequestReplyBlock.Result = 2;;
//				}
//
//				RecipeKeyParamterRequestReplyBlock.RecipeVersionSequenceNumber = 1;
//				RecipeKeyParamterRequestReplyBlock.UnitNumber = 1;		
//		
//				//memcpy((char*)RecipeKeyParamterRequestReplyBlock.ParameterValue, (char*)CimInfo::m_MachineRecipeTable.strRecipeName[wResult], 1034);
//
//
//				LWWrite(RECIPE_KEY_PARAMETER_REQUEST_REPLY_BLOCK_START_ADDRESS, &RecipeKeyParamterRequestReplyBlock, sizeof(RecipeKeyParamterRequestReplyBlock));
//				CimInfo::m_LBLTM.CIMPCCommandReply_RecipeKeyParameterRequestReply = TRUE;
//				LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//				SetT2TimeOut();
//
//			}
//			else if (CimInfo::m_LBLTM.CIMPCCommandReply_RecipeKeyParameterRequestReply == TRUE &&
//				CimInfo::m_LBMTL.CIMPCCommand_RecipeKeyParameterRequest == FALSE)
//			{
//				ClearT2TimeOut();
//				CimInfo::m_LBLTM.CIMPCCommandReply_RecipeKeyParameterRequestReply = FALSE;
//				LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			}
//			else if (IsT2TimeOut() && CimInfo::m_LBLTM.CIMPCCommandReply_RecipeKeyParameterRequestReply == TRUE)
//			{
//				m_CIMAlarmFlag[5] = TRUE;
//				CimInfo::m_LBLTM.CIMPCCommandReply_RecipeKeyParameterRequestReply = FALSE;
//				LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//				ClearT2TimeOut();
//
//				//KJT 20210324
//				CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T2_TIMEOUT, ALARM_TYPE_ERROR, TRUE,102, _T("T2 Timeout :Recipe Parameter Request Command"));
//			}
//			else if (CimInfo::m_LBMTL.CIMPCCommand_RecipeKeyParameterRequest == FALSE)
//				m_CIMAlarmFlag[5] = FALSE;
//
//#pragma endregion
//
//#pragma region CV Report Time Change Command Send Reply
//			if (CimInfo::m_LBMTL.CIMPCCommand_CVReportTimeChangeCommandSend == TRUE &&
//				CimInfo::m_LBLTM.CIMPCCommandReply_CVReportTimeChangeCommandSendReply == FALSE &&
//				m_CIMAlarmFlag[0] == FALSE)
//			{
//				memset(&CVReportTimeChangeCommandSendBlock, 0x0, sizeof(CVReportTimeChangeCommandSendBlock));
//
//				LWRead(CV_REPORT_TIME_CHANGE_COMMAND_SEND_BLOCK_START_ADDRESS, &CVReportTimeChangeCommandSendBlock, sizeof(CVReportTimeChangeCommandSendBlock));
//#if 1			
//				CimInfo::m_CVTimer = CVReportTimeChangeCommandSendBlock.CVReportTime *1000;
//				CimInfo::m_CVTimerCount = CVReportTimeChangeCommandSendBlock.CVRepeatCount;
//		
//#endif
//				memset(&CVReportTimeChangeCommandSendReplyBlock, 0x0, sizeof(CVReportTimeChangeCommandSendReplyBlock));
//				CVReportTimeChangeCommandSendReplyBlock.CVCommandReturnCode = 1;
//				//ReplyCimModeChangeCmdBlock(&CimModeChagneCommandReplyBlock);
//				LWWrite(CV_REPORT_TIME_CHANGE_COMMAND_SEND_REPLY_BLOCK_START_ADDRESS, &CVReportTimeChangeCommandSendReplyBlock, sizeof(CVReportTimeChangeCommandSendReplyBlock));
//				CimInfo::m_LBLTM.CIMPCCommandReply_CVReportTimeChangeCommandSendReply = TRUE;
//				LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//
//				Etc_Msg(_T("[Cim] Send : CV Report Time Change Command Send Reply"));
//				SetT2TimeOut();
//
//				//pCim->LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			}
//			else if (CimInfo::m_LBMTL.CIMPCCommand_CVReportTimeChangeCommandSend == FALSE &&
//				CimInfo::m_LBLTM.CIMPCCommandReply_CVReportTimeChangeCommandSendReply == TRUE)
//			{
//				CimInfo::m_LBLTM.CIMPCCommandReply_CVReportTimeChangeCommandSendReply = FALSE;
//				LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//				ClearT2TimeOut();
//			}
//			else if (IsT2TimeOut() &&
//				CimInfo::m_LBLTM.CIMPCCommandReply_CVReportTimeChangeCommandSendReply == TRUE)
//			{
//				m_CIMAlarmFlag[0] = TRUE;
//				CimInfo::m_LBLTM.CIMPCCommandReply_CVReportTimeChangeCommandSendReply = FALSE;
//				LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//				ClearT2TimeOut();
//
//				//KJT 20210324
//				CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T2_TIMEOUT, ALARM_TYPE_ERROR, TRUE,102, _T("T2 Timeout :MAchine Mode Change Command"));
//			}
//			else if (CimInfo::m_LBMTL.CIMPCCommand_CVReportTimeChangeCommandSend == FALSE)
//				m_CIMAlarmFlag[0] = FALSE;
//#pragma endregion
//
//#if 0
//#pragma region VCR Mode Change Command Reply	
//		if (CimInfo::m_LBMTL.bCIMPCCommandVCRModeChangeCommand == TRUE &&
//			CimInfo::m_LBLTM.bCIMPCCommandReplyVCRModeChangeCommandReply == FALSE &&
//			m_CIMAlarmFlag[6] == FALSE)
//		{
//			LWRead(VCR_MODE_CHANGE_COMMAND_BLOCK_START_ADDRESS, &VCRModeChangeCommandBlock, sizeof(LW_MTL_VCR_MODE_CHANGE_COMMAND_BLOCK));
//			if (VCRModeChangeCommandBlock.VCREnableMode == TRUE)
//			{
//				CimInfo::m_LBLTM.bMachineStatusVCREnableMode = TRUE;
//				LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			}
//			else if (VCRModeChangeCommandBlock.VCREnableMode == FALSE)
//			{
//				CimInfo::m_LBLTM.bMachineStatusVCREnableMode = FALSE;
//				if (VCRModeChangeCommandBlock.VCRNo == 1)
//					SharedInfo::m_FrameVCRReadFailOperationMode = VCRModeChangeCommandBlock.VCRReadFailOperationMode;
//				else if (VCRModeChangeCommandBlock.VCRNo == 2)
//					SharedInfo::m_CassetteVCRReadFailOperationMode = VCRModeChangeCommandBlock.VCRReadFailOperationMode;
//				else if (VCRModeChangeCommandBlock.VCRNo == 3)
//					SharedInfo::m_MaskVCRReadFailOperationMode = VCRModeChangeCommandBlock.VCRReadFailOperationMode;
//				LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			}
//			CimInfo::m_LBLTM.bCIMPCCommandReplyVCRModeChangeCommandReply = TRUE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			SetT2TimeOut();
//
//		}
//		else if (CimInfo::m_LBLTM.bCIMPCCommandReplyVCRModeChangeCommandReply == TRUE &&
//			CimInfo::m_LBMTL.bCIMPCCommandVCRModeChangeCommand == FALSE)
//		{
//			ClearT2TimeOut();
//			CimInfo::m_LBLTM.bCIMPCCommandReplyVCRModeChangeCommandReply = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//		}
//		else if (IsT2TimeOut() &&
//			CimInfo::m_LBLTM.bCIMPCCommandReplyVCRModeChangeCommandReply == TRUE)
//		{
//			m_CIMAlarmFlag[6] = TRUE;
//			CimInfo::m_LBLTM.bCIMPCCommandReplyVCRModeChangeCommandReply = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT2TimeOut();
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T2_TIMEOUT, ALARM_TYPE_ERROR, TRUE,102, _T("T2 Timeout :VCR Mode Change Command Reply	"));
//		}
//		else if (CimInfo::m_LBMTL.bCIMPCCommandVCRModeChangeCommand == FALSE)
//			m_CIMAlarmFlag[6] = FALSE;
//#pragma endregion	
//
//#pragma region Material Group Data Download
//		if (CimInfo::m_LBMTL.bCIMPCCommandMaterialGroupDataDownload == TRUE &&
//			CimInfo::m_LBLTM.bCIMPCCommandReplyMaterialGroupDataDownloadReply == FALSE &&
//			m_CIMAlarmFlag[7] == FALSE)
//		{
//			LWRead(MATERIAL_GROUP_DATA_DOWNLOAD_BLOCK_START_ADDRESS, &SharedInfo::MaterialGroupData, sizeof(LW_MTL_MATERIAL_GROUP_DATA_BLOCK));
//			CimInfo::m_LBLTM.bCIMPCCommandReplyMaterialGroupDataDownloadReply = TRUE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			SetT2TimeOut();
//
//		}
//		else if (CimInfo::m_LBLTM.bCIMPCCommandReplyMaterialGroupDataDownloadReply == TRUE &&
//			CimInfo::m_LBMTL.bCIMPCCommandMaterialGroupDataDownload == FALSE)
//		{
//			ClearT2TimeOut();
//			CimInfo::m_LBLTM.bCIMPCCommandReplyMaterialGroupDataDownloadReply = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//		}
//		else if (IsT2TimeOut() &&
//			CimInfo::m_LBLTM.bCIMPCCommandReplyMaterialGroupDataDownloadReply == TRUE)
//		{
//			m_CIMAlarmFlag[7] = TRUE;
//			CimInfo::m_LBLTM.bCIMPCCommandReplyMaterialGroupDataDownloadReply = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT2TimeOut();
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T2_TIMEOUT, ALARM_TYPE_ERROR, TRUE,102, _T("T2 Timeout :Material Group Data Download Reply	"));
//		}
//		else if (CimInfo::m_LBMTL.bCIMPCCommandVCRModeChangeCommand == FALSE)
//			m_CIMAlarmFlag[7] = FALSE;
//#pragma endregion	
//#endif
//#pragma endregion
//
//		///////////////////////////////////////////////////////////////////////////////////
//		//Request Command
//		//////////////////////////////////////////////////////////////////////////////////
//#pragma region Request Command
//
//#pragma region Sheet Information Request //KJT 20210409		
//		if (CimInfo::m_LBLTM.MachineMaterialEvent_MaterialSheetDataDownloadRequest == TRUE &&
//			CimInfo::m_LBMTL.MachineMaterialEventReply_MaterialSheetDataDownloadRequestReply == TRUE)
//		{
//			LWRead(SHEET_INFORMATION_DOWNLOAD_REPLY_BLOCK_START_ADDRESS, &MeterialSheetDataDownloadRequestReplyBlock, sizeof(MeterialSheetDataDownloadRequestReplyBlock));
//
//			//KJT 20210409
//			if (MeterialSheetDataDownloadRequestReplyBlock.ReturnCode == 2) //1:OK, 2:NG
//			{
//				CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_OTHER, ALARM_TYPE_WARNING, TRUE, 101, _T("Cim Sheet Info Return Code NG"));
//			}
//			else //??
//			{
//				szMsg.Format(_T("%s\\dat\\SheetInfo.dat"), SharedInfo::VisionAgentPath);
//
//				file.Open(szMsg, CFile::modeCreate | CFile::modeWrite);
//				file.Write(&CimInfo::SheetInfo, sizeof(CimInfo::SheetInfo));
//				file.Close();
//
//				m_bSheetInfoDownloadCompleteFlag = TRUE;
//			}
//
//			CimInfo::m_LBLTM.MachineMaterialEvent_MaterialSheetDataDownloadRequest = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//		}
//		else if (IsT1TimeOut() &&
//			CimInfo::m_LBLTM.MachineMaterialEvent_MaterialSheetDataDownloadRequest == TRUE)
//		{
//			ClearT1TimeOut();
//
//			CimInfo::m_LBLTM.MachineMaterialEvent_MaterialSheetDataDownloadRequest = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE,101, _T("T1 Timeout :Sheet Move Out Report"));
//		}
//
//		char * pValue;
//		if (CimInfo::m_LBLTM.MachineMaskEvent_MaskJobDataRequest == TRUE &&
//			CimInfo::m_LBMTL.MachineMaskEventReply_MaskJobDataRequestReply == TRUE)
//		{
//			//WORD Result = sizeof(MATERIAL_DATA_A);
//			LWRead(JOB_DATA_REQUEST_REPLY_BLOCK_START_ADDRESS, &JobDataRequestReplyBlock, sizeof(JobDataRequestReplyBlock));
//			pValue = (char*)JobDataRequestReplyBlock.JobData;
//			for (int i = 0; i < sizeof(MASK_JOB_DATA) * 2; i++)
//			{
//				if (*(pValue +i) == 0x20)			//0x2020은 ".."
//					*(pValue + i)= 0;
//			}
//			memcpy(&JobDataTemp, &JobDataRequestReplyBlock.JobData, sizeof(CimInfo::MaskJobData));
//
//		
//#if 0 //KJT 20210408 Hide. And UI Refresh!!
//			if (PPIDCheck(JobDataTemp) == -1)
//			{
//				Etc_Msg(_T("Error : Jot Data PPID NG"));
//			}
//			if (CimInfo::JobDataRequestBlock.RequestOption == 1 && memcmp(JobDataTemp.MaskJobDataBlock.Mask_JobID, CimInfo::JobDataRequestBlock.RequestMaskJobID, sizeof(CimInfo::MaskJobData.MaskJobDataBlock.Mask_JobID)))
//			{
//				Etc_Msg(_T("Error : Jot Data Job ID NG"));
//			}
//			else if (CimInfo::JobDataRequestBlock.RequestOption == 2 && JobDataTemp.MaskJobDataBlock.Mask_LotSequenceNumber  != CimInfo::JobDataRequestBlock.LotSequenceNumber)
//			{
//				Etc_Msg(_T("Error : Jot Data Lot Seq NG"));
//			}
//			else if (CimInfo::JobDataRequestBlock.RequestOption == 2 && JobDataTemp.MaskJobDataBlock.Mask_SlotSequenceNumber != CimInfo::JobDataRequestBlock.SlotSequenceNumber)
//			{
//				Etc_Msg(_T("Error : Jot Data Slot Seq NG"));
//			}
//			else
//#endif
//			{
//				for (int i = 19; i > 0; i--)
//				{
//					memcpy(&CimInfo::StoredJob[i], &CimInfo::StoredJob[i - 1], sizeof(CimInfo::StoredJob[i]));
//				}
//				memcpy(&CimInfo::StoredJob[0], &CimInfo::MaskJobData, sizeof(CimInfo::MaskJobData));
//
//				memcpy(&CimInfo::MaskJobData, &JobDataTemp, sizeof(CimInfo::MaskJobData));
//			}
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskReceivedJobReport = TRUE;
//			
//
//
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskJobDataRequest = FALSE;
//
//			SetT3TimeOut();
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//		}
//		else if (IsT1TimeOut() &&
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskJobDataRequest == TRUE)
//		{
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskJobDataRequest = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE,101, _T("T1 Timeout :Job Data Request"));
//		}
//#pragma endregion
//
//#pragma region Stored job report	
//		if (CimInfo::m_LBMTL.MachineMaskEventReply_MaskStoredJobReportReply == TRUE &&
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskStoredJobReport == TRUE)
//		{
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskStoredJobReport = FALSE;
//			m_bStoredJobReportCompleteFlag = TRUE;
//			CimInfo::m_ProductJobCount++;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//		}
//		else if (IsT1TimeOut() &&
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskStoredJobReport == TRUE)
//		{
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskStoredJobReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE,101, _T("T1 Timeout :Stored Job Report"));
//		}
//#pragma endregion
//
//
//#pragma region Machine Mode Change Report	
//		if (CimInfo::m_LBMTL.MachineEventReply_MachineModeChangeReportReply == TRUE &&
//			CimInfo::m_LBLTM.MachineEvent_MachineModeChangeReport == TRUE)
//		{
//			CimInfo::m_LBLTM.MachineEvent_MachineModeChangeReport = FALSE;
//			
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//		}
//		else if (IsT1TimeOut() &&
//			CimInfo::m_LBLTM.MachineEvent_MachineModeChangeReport == TRUE)
//		{
//			CimInfo::m_LBLTM.MachineEvent_MachineModeChangeReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE, 101, _T("T1 Timeout :Machine Mode Change Report"));
//		}
//#pragma endregion
//
//#pragma region Fetched Out job report	
//		if (CimInfo::m_LBMTL.MachineMaskEventReply_MaskFetchedOutJobReportReply == TRUE &&
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskFetchedOutJobReport == TRUE)
//		{
//			m_bFetchedOutJobReportCompleteFlag = TRUE;
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskFetchedOutJobReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//		}
//		else if (IsT1TimeOut() &&
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskFetchedOutJobReport == TRUE)
//		{
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskFetchedOutJobReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE,101, _T("T1 Timeout :Fetched Job Report"));
//		}
//#pragma endregion
//
//#pragma region Send out job report	
//		if (CimInfo::m_LBMTL.MachineMaskEventReply_MaskSentOutJobReportReply_1 == TRUE &&
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskSentOutJobReport_1 == TRUE)
//		{
//			m_bSentOutJobReportCompleteFlag = TRUE;
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskSentOutJobReport_1 = FALSE;
//			CimInfo::m_ProductJobCount--;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//		}
//		else if (IsT1TimeOut() &&
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskSentOutJobReport_1 == TRUE)
//		{
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskSentOutJobReport_1 = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE,101, _T("T1 Timeout :Send out Job Report"));
//		}
//#pragma endregion
//
//#pragma region Job Data Change Report
//		if (CimInfo::m_LBMTL.MachineMaskEventReply_MaskJobDataChangeReportReply == TRUE &&
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskJobDataChangeReport == TRUE)
//		{
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskJobDataChangeReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//		}
//		else if (IsT1TimeOut() &&
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskJobDataChangeReport == TRUE)
//		{
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskJobDataChangeReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE,101, _T("T1 Timeout :Job Data Change Report"));
//		}
//#pragma endregion
//
//#pragma region Glass Process Start Report
//		if (CimInfo::m_LBMTL.MachineMaskEventReply_MaskProcessStartReportReply == TRUE &&
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskProcessStartReport == TRUE)
//		{
//			m_bProcessStartCompleteFlag = TRUE;
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskProcessStartReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//		}
//		else if (IsT1TimeOut() &&
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskProcessStartReport == TRUE)
//		{
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskProcessStartReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE,101, _T("T1 Timeout : Process Start"));
//		}
//#pragma endregion
//
//#pragma region Glass Process End Report
//		if (CimInfo::m_LBMTL.MachineMaskEventReply_MaskProcessEndReportReply == TRUE &&
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskProcessEndReport == TRUE)
//		{
//			m_bProcessEndCompleteFlag = TRUE;
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskProcessEndReport = FALSE;
//
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//
//			DVDataReport();
//		}
//		else if (IsT1TimeOut() && CimInfo::m_LBLTM.MachineMaskEvent_MaskProcessEndReport == TRUE)
//		{
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskProcessEndReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE,101, _T("T1 Timeout : Process End"));
//		}
//#pragma endregion
//
//
//#pragma region DV Data Report
//		if (CimInfo::m_LBMTL.VariableDataEventReply_DV_Data_Report_Reply == TRUE &&
//			CimInfo::m_LBLTM.VariableDataEvent_DVDataReport == TRUE)
//		{
//			m_bProcessEndCompleteFlag = TRUE;
//			CimInfo::m_LBLTM.VariableDataEvent_DVDataReport = FALSE;
//
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//
//			
//		}
//		else if (IsT1TimeOut() && CimInfo::m_LBLTM.VariableDataEvent_DVDataReport == TRUE)
//		{
//			CimInfo::m_LBLTM.VariableDataEvent_DVDataReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE,101, _T("T1 Timeout : Process End"));
//		}
//#pragma endregion
//
//
//#pragma region CV Data Report
//		if (CimInfo::m_LBMTL.VariableDataEventReply_CD_Data_Report_Reply == TRUE &&
//			CimInfo::m_LBLTM.VariableDataEvent_CVDataReport == TRUE)
//		{
//			m_bProcessEndCompleteFlag = TRUE;
//
//			Etc_Msg(_T("CV Report Report Receive"));
//			CimInfo::m_LBLTM.VariableDataEvent_CVDataReport = FALSE;
//
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//
//
//		}
//		else if (IsT1TimeOut() && CimInfo::m_LBLTM.VariableDataEvent_CVDataReport == TRUE)
//		{
//			CimInfo::m_LBLTM.VariableDataEvent_CVDataReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE,101, _T("T1 Timeout : Process End"));
//		}
//#pragma endregion
//
//#pragma region Job Judge Report 
//		if (CimInfo::m_LBMTL.MachineMaterialEventReply_MaterialJudgeResultReportReply == TRUE &&
//			CimInfo::m_LBLTM.MachineMaterialEvent_MaterialJudgeResultReport == TRUE)
//		{
//			CimInfo::m_LBLTM.MachineMaterialEvent_MaterialJudgeResultReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//		}
//		else if (IsT1TimeOut() && CimInfo::m_LBLTM.MachineMaterialEvent_MaterialJudgeResultReport == TRUE)
//		{
//			CimInfo::m_LBLTM.MachineMaterialEvent_MaterialJudgeResultReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE,101, _T("T1 Timeout : Job Judge Report"));
//		}
//#pragma endregion
//
//
//#pragma region -layer info requeset reply block 
//		if (CimInfo::m_LBMTL.CIMPCCommand_RecipeLayerInfoRequest == TRUE &&
//			CimInfo::m_LBLTM.CIMPCCommandReply_RecipeLayerInfoRequestReply == TRUE)
//		{
//			CimInfo::m_LBLTM.CIMPCCommandReply_RecipeLayerInfoRequestReply = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//		}
//		else if (IsT1TimeOut() && CimInfo::m_LBLTM.CIMPCCommandReply_RecipeLayerInfoRequestReply == TRUE)
//		{
//			CimInfo::m_LBLTM.CIMPCCommandReply_RecipeLayerInfoRequestReply = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE,101, _T("T1 Timeout : Job Judge Report"));
//		}
//#pragma endregion
//
//
//#pragma region mask load request block 
//		if (CimInfo::m_LBMTL.MachineMaskEventReply_MaskLoadRequestReply == TRUE &&
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskLoadRequest == TRUE)
//		{
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskLoadRequest = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//		}
//		else if (IsT1TimeOut() && CimInfo::m_LBLTM.MachineMaskEvent_MaskLoadRequest == TRUE)
//		{
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskLoadRequest = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE,101, _T("T1 Timeout : Job Judge Report"));
//		}
//#pragma endregion
//
//#pragma region mask Unload request block 
//		if (CimInfo::m_LBMTL.MachineMaskEventReply_MaskUnloadRequestReply == TRUE &&
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskUnloadRequest == TRUE)
//		{
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskUnloadRequest = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//		}
//		else if (IsT1TimeOut() && CimInfo::m_LBLTM.MachineMaskEvent_MaskUnloadRequest == TRUE)
//		{
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskUnloadRequest = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE,101, _T("T1 Timeout : Job Judge Report"));
//		}
//#pragma endregion
//
//#pragma region mask load complete block 
//		if (CimInfo::m_LBMTL.MachineMaskEventReply_MaskLoadCompletedReportReply == TRUE &&
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskLoadCompletedReport == TRUE)
//		{
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskLoadCompletedReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//		}
//		else if (IsT1TimeOut() && CimInfo::m_LBLTM.MachineMaskEvent_MaskLoadCompletedReport == TRUE)
//		{
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskLoadCompletedReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE,101, _T("T1 Timeout : Job Judge Report"));
//		}
//#pragma endregion
//
//
//#pragma region mask unload complete block 
//		if (CimInfo::m_LBMTL.MachineMaskEventReply_MaskUnloadCompletedReportReply == TRUE &&
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskUnloadCompletedReport == TRUE)
//		{
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskUnloadCompletedReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//		}
//		else if (IsT1TimeOut() && CimInfo::m_LBLTM.MachineMaskEvent_MaskUnloadCompletedReport == TRUE)
//		{
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskUnloadCompletedReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE,101, _T("T1 Timeout : Job Judge Report"));
//		}
//#pragma endregion
//#if 0
//#pragma region VCR Change Report
//		if (CimInfo::m_LBMTL.bMachineEventReplyVCRModeChangeReportReply == TRUE &&
//			CimInfo::m_LBLTM.bMachineEventVCRModeChangeReport == TRUE)
//		{
//			CimInfo::m_LBLTM.bMachineEventVCRModeChangeReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//		}
//		else if (IsT1TimeOut() && CimInfo::m_LBLTM.bMachineEventVCRModeChangeReport == TRUE)
//		{
//			CimInfo::m_LBLTM.bMachineEventVCRModeChangeReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//		}
//#pragma endregion
//
//#pragma region Process Data Report		
//		if (CimInfo::m_LBMTL.bMachineEventReplyProcessDataReportReply == TRUE &&
//			CimInfo::m_LBLTM.bMachineEventProcessDataReport == TRUE)
//		{
//			m_bProcessDataReportCompleteFlag = TRUE;
//			CimInfo::m_LBLTM.bMachineEventProcessDataReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//		}
//		else if (IsT1TimeOut() && CimInfo::m_LBLTM.bMachineEventProcessDataReport == TRUE)
//		{
//			CimInfo::m_LBLTM.bMachineEventProcessDataReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE,101, _T("T1 Timeout : Process Data Report"));
//		}
//#pragma endregion
//
//#pragma region VCR Event Report
//		if (CimInfo::m_LBMTL.bMachineEventReplyVCREventReportReply == TRUE &&
//			CimInfo::m_LBLTM.bMachineEventVCREventReport == TRUE)
//		{
//			CimInfo::m_LBLTM.bMachineEventVCREventReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//		}
//		else if (IsT1TimeOut() && CimInfo::m_LBLTM.bMachineEventVCREventReport == TRUE)
//		{
//			CimInfo::m_LBLTM.bMachineEventVCREventReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE,101, _T("T1 Timeout : VCR Event Repor"));
//		}
//#pragma endregion
//#endif 
//#pragma endregion
//
//		///////////////////////////////////////////////////////////////////////////////////
//		//Machine Event Report
//		//////////////////////////////////////////////////////////////////////////////////
//#pragma region	Machine Event Report
//#pragma region Machine Status Change Report
//		if (CimInfo::m_LBLTM.MachineEvent_MachineStatusChangeReport == TRUE &&
//			CimInfo::m_LBMTL.MachineEventReply_MachineStatusChangeReportReply == TRUE)
//		{
//			ClearT1TimeOut();
//			CimInfo::m_LBLTM.MachineEvent_MachineStatusChangeReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//		}
//		else if (IsT1TimeOut() && CimInfo::m_LBLTM.MachineEvent_MachineStatusChangeReport == TRUE)
//		{
//			CimInfo::m_LBLTM.MachineEvent_MachineStatusChangeReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE,101, _T("T1 Timeout :Machine Status Change Report"));
//		}
//#pragma endregion
//
//#pragma region Auto Recipe Report
//		if (CimInfo::m_LBLTM.MachineEvent_AutoRecipeChangeModeReport == TRUE &&
//			CimInfo::m_LBMTL.MachineEventReply_AutoRecipeChangeModeReportReply == TRUE)
//		{
//			ClearT1TimeOut();
//			CimInfo::m_LBLTM.MachineEvent_AutoRecipeChangeModeReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//		}
//		else if (IsT1TimeOut() && CimInfo::m_LBLTM.MachineEvent_AutoRecipeChangeModeReport == TRUE)
//		{
//			CimInfo::m_LBLTM.MachineEvent_AutoRecipeChangeModeReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE,101, _T("T1 Timeout :Machine Status Change Report"));
//		}
//#pragma endregion
//
//
//#pragma region Date Time Request
//		if (CimInfo::m_LBLTM.MachineEvent_DateTimeRequest == TRUE &&
//			CimInfo::m_LBMTL.MachineEventReply_DateTimeRequestReply == TRUE)
//		{
//			LWRead(DATE_TIME_REQUEST_REPLY_BLOCK_START_ADDRESS, &DateTimeRequestReplyBlock, sizeof(LW_MTL_DATE_TIME_REQUEST_REPLY_BLOCK));
//
//			if (DateTimeRequestReplyBlock.DataTouchPanelNumber == 1)
//			{
//				GetLocalTime(&LinkTime);
//				LinkTime.wYear = DateTimeRequestReplyBlock.DataTimeYear;// *10 + DateTimeSetCommandBlock.DateTime.Year.ValueX10 + 2000;
//				LinkTime.wMonth = DateTimeRequestReplyBlock.DataTimeMonth;// *10 + DateTimeSetCommandBlock.DateTime.Month.ValueX10;
//				LinkTime.wDay = DateTimeRequestReplyBlock.DataTimeDay;// *10 + DateTimeSetCommandBlock.DateTime.Day.ValueX10;
//				LinkTime.wHour = DateTimeRequestReplyBlock.DataTimeHour;//ValueX1 * 10 + DateTimeSetCommandBlock.DateTime.Hour.ValueX10;
//				LinkTime.wMinute = DateTimeRequestReplyBlock.DataTimeMinute;// .ValueX1 * 10 + DateTimeSetCommandBlock.DateTime.Minute.ValueX10;
//				LinkTime.wSecond = DateTimeRequestReplyBlock.DataTimeSecond;// .ValueX1 * 10 + DateTimeSetCommandBlock.DateTime.Second.ValueX10;
//
//				OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES |
//					TOKEN_QUERY, &hToken);
//				LookupPrivilegeValue(NULL, SE_SYSTEMTIME_NAME, &luid);
//				tp.PrivilegeCount = 1;
//				tp.Privileges[0].Luid = luid;
//				tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
//				AdjustTokenPrivileges(hToken, FALSE, &tp, 0, NULL, NULL);
//				CloseHandle(hToken);
//				bValue = SetLocalTime(&LinkTime);
//			}
//			else
//			{
//				//KJT 20210324
//				CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_GLASS_OR_PANEL_INFO_ERROR, ALARM_TYPE_ERROR, TRUE,103, _T("TouchPannel ID Error"));
//			}
//
//			ClearT1TimeOut();
//			CimInfo::m_LBLTM.MachineEvent_DateTimeRequest = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			Etc_Msg(_T("Recv :Date Time Request reply"));
//		}
//		else if (IsT1TimeOut() && CimInfo::m_LBLTM.MachineEvent_DateTimeRequest == TRUE)
//		{
//			CimInfo::m_LBLTM.MachineEvent_DateTimeRequest = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE,101, _T("T1 Timeout :Date Time Request reply"));
//		}
//#pragma endregion
//
//#pragma region Current Recipe ID Change Report
//		if (CimInfo::m_LBLTM.MachineEvent_CurrentRecipeNumberChangeReport == TRUE &&
//			CimInfo::m_LBMTL.MachineEventReply_CurrentRecipeNumberChangeReportReply == TRUE)
//		{
//
//			CimInfo::m_LBLTM.MachineEvent_CurrentRecipeNumberChangeReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//			Etc_Msg(_T("Recv :Current Recipe ID Change Report reply"));
//
//		}
//		else if (IsT1TimeOut() &&
//			CimInfo::m_LBLTM.MachineEvent_CurrentRecipeNumberChangeReport == TRUE)
//		{
//			CimInfo::m_LBLTM.MachineEvent_CurrentRecipeNumberChangeReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE,101, _T("T1 Timeout :Current Recipe Change Report"));
//		}
//#pragma endregion
//
//
//#pragma region Magazine Process Complete Report
//		if (CimInfo::m_LBLTM.MachineMaterialEvent_MagazineProcessCompleteReport == TRUE &&
//			CimInfo::m_LBMTL.MachineMaterialEventReply_MagagineProcessCompleteReportReply == TRUE)
//		{
//
//			CimInfo::m_LBLTM.MachineMaterialEvent_MagazineProcessCompleteReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//			Etc_Msg(_T("Recv :Magazine Process Complete Report reply"));
//
//		}
//		else if (IsT1TimeOut() &&
//			CimInfo::m_LBLTM.MachineMaterialEvent_MagazineProcessCompleteReport == TRUE)
//		{
//			CimInfo::m_LBLTM.MachineMaterialEvent_MagazineProcessCompleteReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE,101, _T("T1 Timeout :Current Recipe Change Report"));
//		}
//#pragma endregion
//
//#pragma region Magazine Data Request
//		if (CimInfo::m_LBLTM.MachineMaterialEvent_MagazineDataRequest == TRUE &&
//			CimInfo::m_LBMTL.MachineMaterialEventReply_MagazineDataRequestReply == TRUE)
//		{
//			LWRead(MAGAZINE_DATA_REQUEST_REPLY_BLOCK_1_START_ADDRESS, &CimInfo::MagazineDataRequestReplyBlock[0], sizeof(CimInfo::MagazineDataRequestReplyBlock[0]));
//			LWRead(MAGAZINE_DATA_REQUEST_REPLY_BLOCK_2_START_ADDRESS, &CimInfo::MagazineDataRequestReplyBlock[1], sizeof(CimInfo::MagazineDataRequestReplyBlock[1]));
//			LWRead(MAGAZINE_DATA_REQUEST_REPLY_BLOCK_3_START_ADDRESS, &CimInfo::MagazineDataRequestReplyBlock[2], sizeof(CimInfo::MagazineDataRequestReplyBlock[2]));
//			LWRead(MAGAZINE_DATA_REQUEST_REPLY_BLOCK_4_START_ADDRESS, &CimInfo::MagazineDataRequestReplyBlock[3], sizeof(CimInfo::MagazineDataRequestReplyBlock[3]));
//			LWRead(MAGAZINE_DATA_REQUEST_REPLY_BLOCK_5_START_ADDRESS, &CimInfo::MagazineDataRequestReplyBlock[4], sizeof(CimInfo::MagazineDataRequestReplyBlock[4]));
//			LWRead(MAGAZINE_DATA_REQUEST_REPLY_BLOCK_6_START_ADDRESS, &CimInfo::MagazineDataRequestReplyBlock[5], sizeof(CimInfo::MagazineDataRequestReplyBlock[5]));
//			CimInfo::m_LBLTM.MachineMaterialEvent_MagazineDataRequest = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//			Etc_Msg(_T("Recv :Magazine Data Request reply"));
//
//		}
//		else if (IsT1TimeOut() &&
//			CimInfo::m_LBLTM.MachineMaterialEvent_MagazineDataRequest == TRUE)
//		{
//
//			CimInfo::m_LBLTM.MachineMaterialEvent_MagazineDataRequest = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE,101, _T("T1 Timeout :Current Recipe Change Report"));
//		}
//#pragma endregion
//#if 0
//#pragma region Recipe List Change Report
//		if (CimInfo::m_LBLTM.bMachineEventRecipeListChangeReport == TRUE &&
//			CimInfo::m_LBMTL.bMachineEventReplyRecipeListChangeReportReply == TRUE)
//		{
//			ClearT1TimeOut();
//			CimInfo::m_LBLTM.bMachineEventRecipeListChangeReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//
//		}
//		else if (IsT1TimeOut() &&
//			CimInfo::m_LBLTM.bMachineEventRecipeListChangeReport == TRUE)
//		{
//
//			CimInfo::m_LBLTM.bMachineEventRecipeListChangeReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE,101, _T("T1 Timeout :Recipe Change Report"));
//		}
//#pragma endregion
//
//#pragma region Recipe Parameter Data Change Report
//		if (CimInfo::m_LBLTM.bMachineEventRecipeParameterDataChangeReport == TRUE &&
//			CimInfo::m_LBMTL.bMachineEventReplyRecipeParameterDataChangeReportReply == TRUE)
//		{
//
//			CimInfo::m_LBLTM.bMachineEventRecipeParameterDataChangeReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//
//		}
//		else if (IsT1TimeOut() &&
//			CimInfo::m_LBLTM.bMachineEventRecipeParameterDataChangeReport == TRUE)
//		{
//			ClearT1TimeOut();
//			CimInfo::m_LBLTM.bMachineEventRecipeParameterDataChangeReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE,101, _T("T1 Timeout :Recipe Parameter Data Change Report"));
//		}
//#pragma endregion	
//#endif
//#pragma region Received job report
//		if (CimInfo::m_LBLTM.MachineMaskEvent_MaskReceivedJobReport == TRUE &&
//			CimInfo::m_LBMTL.MachineMaskEventReply_MaskReceivedJobReportReply == TRUE)
//		{
//
//			m_bReceivedJobReportCompleteFlag = TRUE;
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskReceivedJobReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//		}
//		else if (IsT1TimeOut() &&
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskReceivedJobReport == TRUE)
//		{
//			ClearT1TimeOut();
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskReceivedJobReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE,101, _T("T1 Timeout :received Job Report"));
//		}
//#pragma endregion	
//
//#pragma region Stored job report
//		if (CimInfo::m_LBLTM.MachineMaskEvent_MaskStoredJobReport == TRUE &&
//			CimInfo::m_LBMTL.MachineMaskEventReply_MaskStoredJobReportReply == TRUE)
//		{
//
//			m_bStoredJobReportCompleteFlag = TRUE;
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskStoredJobReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//		}
//		else if (IsT1TimeOut() &&
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskStoredJobReport == TRUE)
//		{
//
//			ClearT1TimeOut();
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskStoredJobReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE,101, _T("T1 Timeout :Stored Job Report"));
//		}
//#pragma endregion	
//
//#pragma region FetchedOut job report
//		if (CimInfo::m_LBLTM.MachineMaskEvent_MaskFetchedOutJobReport == TRUE &&
//			CimInfo::m_LBMTL.MachineMaskEventReply_MaskFetchedOutJobReportReply == TRUE)
//		{
//			ClearT1TimeOut();
//			m_bFetchedOutJobReportCompleteFlag = TRUE;
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskFetchedOutJobReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//		}
//		else if (IsT1TimeOut() &&
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskFetchedOutJobReport == TRUE)
//		{
//			ClearT1TimeOut();
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskFetchedOutJobReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE,101, _T("T1 Timeout :FetchedOut Job Report"));
//		}
//#pragma endregion	
//#if 0
//#pragma region Removed job report
//		if (CimInfo::m_LBLTM.MachineMaskEvent_remove == TRUE &&
//			CimInfo::m_LBMTL.bMachineEventReplyRemovedJobReportReply == TRUE)
//		{
//
//			m_bRemovedJobReportCompleteFlag = TRUE;
//			CimInfo::m_LBLTM.bMachineEventRemovedJobReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//		}
//		else if (IsT1TimeOut() &&
//			CimInfo::m_LBLTM.bMachineEventRemovedJobReport == TRUE)
//		{
//			ClearT1TimeOut();
//			CimInfo::m_LBLTM.bMachineEventRemovedJobReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE,101, _T("T1 Timeout :Removed Job Report"));
//		}
//#pragma endregion
//#endif
//#pragma region SentOut job report
//		if (CimInfo::m_LBLTM.MachineMaskEvent_MaskSentOutJobReport_1 == TRUE &&
//			CimInfo::m_LBMTL.MachineMaskEventReply_MaskSentOutJobReportReply_1 == TRUE)
//		{
//			ClearT1TimeOut();
//			m_bSentOutJobReportCompleteFlag = TRUE;
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskSentOutJobReport_1 = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//		}
//		else if (IsT1TimeOut() &&
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskSentOutJobReport_1 == TRUE)
//		{
//			ClearT1TimeOut();
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskSentOutJobReport_1 = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE,101, _T("T1 Timeout :SentOut Job Report"));
//		}
//#pragma endregion
//
//#pragma region CimMessage Confirm Report
//		if (CimInfo::m_LBLTM.MachineEvent_CIMMessageConfirmReport == TRUE &&
//			CimInfo::m_LBMTL.MachineEventReply_CIMMessageConfirmReportReply == TRUE)
//		{
//			CimInfo::m_LBLTM.MachineEvent_CIMMessageConfirmReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//
//		}
//		else if (IsT1TimeOut() &&
//			CimInfo::m_LBLTM.MachineEvent_CIMMessageConfirmReport == TRUE)
//		{
//			ClearT1TimeOut();
//			CimInfo::m_LBLTM.MachineEvent_CIMMessageConfirmReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE,101, _T("T1 Timeout :Cim Message Conrirm Report"));
//		}
//#pragma endregion
//
//#pragma region Material count Change Report
//		if (CimInfo::m_LBLTM.MachineMaterialEvent_MaterialCountChangeReport == TRUE &&
//			CimInfo::m_LBMTL.MachineMaterialEventReply_MaterialCountChangeReportReply == TRUE)
//		{
//			CimInfo::m_LBLTM.MachineMaterialEvent_MaterialCountChangeReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//
//		}
//		else if (IsT1TimeOut() &&
//			CimInfo::m_LBLTM.MachineMaterialEvent_MaterialCountChangeReport == TRUE)
//		{
//			ClearT1TimeOut();
//			CimInfo::m_LBLTM.MachineMaterialEvent_MaterialCountChangeReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE,101, _T("T1 Timeout :Material count Change Report"));
//		}
//#pragma endregion
//
//#pragma region Material Status Change Report
//		if (CimInfo::m_LBLTM.MachineMaterialEvent_MaterialStatusChangeReport == TRUE &&
//			CimInfo::m_LBMTL.MachineMaterialEventReply_MaterialStatusChangeReportReply == TRUE)
//		{
//			CimInfo::m_LBLTM.MachineMaterialEvent_MaterialStatusChangeReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//
//		}
//		else if (IsT1TimeOut() &&
//			CimInfo::m_LBLTM.MachineMaterialEvent_MaterialStatusChangeReport == TRUE)
//		{
//			ClearT1TimeOut();
//			CimInfo::m_LBLTM.MachineMaterialEvent_MaterialStatusChangeReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE,101, _T("T1 Timeout :Material Status Change Report"));
//		}
//#pragma endregion
//#if 0
//#pragma region Alarm Event
//		if (CimInfo::m_AlarmCount < 0 || CimInfo::m_AlarmCount > 5)
//			continue;
//		if (CimInfo::m_LBLTM.bMachineEventAlarmStateChangeReport == TRUE &&
//			CimInfo::m_LBMTL.bMachineEventReplyAlarmStateChangeReportReply == TRUE)
//		{
//			CimInfo::m_LBLTM.bMachineEventAlarmStateChangeReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//
//			if (CimInfo::AlarmBlock[CimInfo::m_AlarmCmdPos].AlarmState == 0 && SharedInfo::m_nCmd == eALARM_RESET)
//			{
//				CimInfo::m_AlarmCount--;
//			}
//
//
//			else if (CimInfo::AlarmBlock[CimInfo::m_AlarmCmdPos].AlarmState == 1 && SharedInfo::m_nCmd == eALARM_SET)
//			{
//				CimInfo::m_AlarmCount++;
//				CimInfo::m_AlarmMaxPos++;
//			}
//
//			if (CimInfo::m_AlarmCount == 0 || SharedInfo::m_nCmd == eALARM_ALL_RESET)
//			{
//				//CimInfo::m_LBLTM.bMachineEventAlarmStateChangeReport = TRUE;
//				CimInfo::m_LBLTM.bMachineStatusLocalAlarmState = FALSE;
//				LWWrite(ALARM_BLOCK_START_ADDRESS, &CimInfo::AlarmBlock, sizeof(CimInfo::AlarmBlock));
//				LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//				CimInfo::m_AlarmCount = 0;
//				CimInfo::m_AlarmMaxPos = 0;
//				Etc_Msg(_T("[Cim] Send : Alarm State Change Report"));
//				SetT1TimeOut();
//				//SharedInfo::m_AlarmAllClearFlag = FALSE;
//			}
//
//			SharedInfo::m_nCmd = eALARM_NONE;
//
//
//			//else if(CimInfo::m_AlarmCount == 0)// && SharedInfo::m_AlarmAllClearFlag == TRUE)
//			//{
//			//	SharedInfo::m_AlarmAllClearFlag == TRUE;
//			//}
//		}
//		else if (IsT1TimeOut() &&
//			CimInfo::m_LBLTM.bMachineEventAlarmStateChangeReport == TRUE)
//		{
//			CimInfo::m_LBLTM.bMachineEventAlarmStateChangeReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//			Etc_Msg(_T("T1 Timeout :Alarm State Change Report"));
//
//			//KJT 20210324
//			//CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE,101, _T("T1 Timeout :Alarm State Change Report"));
//		}
//#pragma endregion
//#else //KJT 20210407
//		if (CimInfo::m_AlarmAllClearFlag == TRUE) //All Reset Alarm //KJT 20210417
//		{
//			if (CimInfo::m_nAlarmReportCount > 0)
//			{
//				//Devs::CimMotion.CIMAlarmResetMessage(CimInfo::AlarmBlock[CimInfo::m_nAlarmReportCount].AlarmID);
//				Sleep(500); //!!
//				CimInfo::m_nAlarmReportCount--;
//				if (CimInfo::m_nAlarmReportCount <= 0)
//				{
//					CimInfo::m_nAlarmReportCount = 0;
//					CimInfo::m_AlarmAllClearFlag = FALSE;
//				}
//			}
//		}
//
//		if (CimInfo::m_nAlarmReserveCount > 0 &&
//			(CimInfo::m_LBLTM.MachineEvent_Alarm_1Report == FALSE || CimInfo::m_LBLTM.MachineEvent_Alarm_2Report == FALSE || CimInfo::m_LBLTM.MachineEvent_Alarm_3Report == FALSE ||
//				CimInfo::m_LBLTM.MachineEvent_Alarm_4Report == FALSE || CimInfo::m_LBLTM.MachineEvent_Alarm_5Report == FALSE))
//			CheckAlarmReserved();
//
//		if (CimInfo::m_LBLTM.MachineEvent_Alarm_1Report == TRUE &&
//			CimInfo::m_LBMTL.MachineEventReply_Alarm_1ReportReply == TRUE)
//		{
//			Etc_Msg(_T("<< MachineEventReply_Alarm_1ReportReply TRUE"));
//			CimInfo::m_LBLTM.MachineEvent_Alarm_1Report = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearAlarmT1TimeOut(0);
//		}
//		else if (IsAlarmT1TimeOut(0) && CimInfo::m_LBLTM.MachineEvent_Alarm_1Report == TRUE)
//		{
//			CimInfo::m_LBLTM.MachineEvent_Alarm_1Report = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearAlarmT1TimeOut(0);
//			Etc_Msg(_T("T1 Timeout : MachineEventReply_Alarm_1ReportReply"));
//		}
//
//		if (CimInfo::m_LBLTM.MachineEvent_Alarm_2Report == TRUE &&
//			CimInfo::m_LBMTL.MachineEventReply_Alarm_2ReportReply == TRUE)
//		{
//			Etc_Msg(_T("<< MachineEventReply_Alarm_2ReportReply TRUE"));
//			CimInfo::m_LBLTM.MachineEvent_Alarm_2Report = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearAlarmT1TimeOut(1);
//		}
//		else if (IsAlarmT1TimeOut(1) && CimInfo::m_LBLTM.MachineEvent_Alarm_2Report == TRUE)
//		{
//			CimInfo::m_LBLTM.MachineEvent_Alarm_2Report = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearAlarmT1TimeOut(1);
//			Etc_Msg(_T("T1 Timeout : MachineEventReply_Alarm_2ReportReply"));
//		}
//		if (CimInfo::m_LBLTM.MachineEvent_Alarm_3Report == TRUE &&
//			CimInfo::m_LBMTL.MachineEventReply_Alarm_3ReportReply == TRUE)
//		{
//			Etc_Msg(_T("<< MachineEventReply_Alarm_3ReportReply TRUE"));
//			CimInfo::m_LBLTM.MachineEvent_Alarm_3Report = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearAlarmT1TimeOut(2);
//		}
//		else if (IsAlarmT1TimeOut(2) && CimInfo::m_LBLTM.MachineEvent_Alarm_3Report == TRUE)
//		{
//			CimInfo::m_LBLTM.MachineEvent_Alarm_3Report = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearAlarmT1TimeOut(2);
//			Etc_Msg(_T("T1 Timeout : MachineEventReply_Alarm_3ReportReply"));
//		}
//		if (CimInfo::m_LBLTM.MachineEvent_Alarm_4Report == TRUE &&
//			CimInfo::m_LBMTL.MachineEventReply_Alarm_4ReportReply == TRUE)
//		{
//			Etc_Msg(_T("<< MachineEventReply_Alarm_4ReportReply TRUE"));
//			CimInfo::m_LBLTM.MachineEvent_Alarm_4Report = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearAlarmT1TimeOut(3);
//		}
//		else if (IsAlarmT1TimeOut(3) && CimInfo::m_LBLTM.MachineEvent_Alarm_4Report == TRUE)
//		{
//			CimInfo::m_LBLTM.MachineEvent_Alarm_4Report = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearAlarmT1TimeOut(3);
//			Etc_Msg(_T("T1 Timeout : MachineEventReply_Alarm_4ReportReply"));
//		}
//		if (CimInfo::m_LBLTM.MachineEvent_Alarm_5Report == TRUE &&
//			CimInfo::m_LBMTL.MachineEventReply_Alarm_5ReportReply == TRUE)
//		{
//			Etc_Msg(_T("<< MachineEventReply_Alarm_5ReportReply TRUE"));
//			CimInfo::m_LBLTM.MachineEvent_Alarm_5Report = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearAlarmT1TimeOut(4);
//		}
//		else if (IsAlarmT1TimeOut(4) && CimInfo::m_LBLTM.MachineEvent_Alarm_5Report == TRUE)
//		{
//			CimInfo::m_LBLTM.MachineEvent_Alarm_5Report = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearAlarmT1TimeOut(4);
//			Etc_Msg(_T("T1 Timeout : MachineEventReply_Alarm_5ReportReply"));
//		}
//#endif
//#pragma region Sheet Move In
//		if (CimInfo::m_LBLTM.MachineMaterialEvent_SheetMoveInReport == TRUE &&
//			CimInfo::m_LBMTL.MachineMaterialEventReply_SheetMoveInReportReply == TRUE)
//		{
//			CimInfo::m_LBLTM.MachineMaterialEvent_SheetMoveInReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//
//		}
//		else if (IsT1TimeOut() &&
//			CimInfo::m_LBLTM.MachineMaterialEvent_SheetMoveInReport == TRUE)
//		{
//			ClearT1TimeOut();
//			m_bSheetMoveInCompleteFlag = TRUE;
//			CimInfo::m_LBLTM.MachineMaterialEvent_SheetMoveInReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE,101, _T("T1 Timeout :Sheet Move Out Report"));
//		}
//#pragma endregion
//
//#pragma region Sheet Move Out
//		if (CimInfo::m_LBLTM.MachineMaterialEvent_SheetMoveOutReport == TRUE &&
//			CimInfo::m_LBMTL.MachineMaterialEventReply_SheetMoveOutReportReply == TRUE)
//		{
//			m_bSheetMoveOutCompleteFlag = TRUE;
//			CimInfo::m_LBLTM.MachineMaterialEvent_SheetMoveOutReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//			ClearT1TimeOut();
//
//		}
//		else if (IsT1TimeOut() &&
//			CimInfo::m_LBLTM.MachineMaterialEvent_SheetMoveOutReport == TRUE)
//		{
//			ClearT1TimeOut();
//			CimInfo::m_LBLTM.MachineMaterialEvent_SheetMoveOutReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE,101, _T("T1 Timeout :Sheet Move Out Report"));
//		}
//#pragma endregion
//
//#pragma region Sheet Data UpDate
//		if (CimInfo::m_LBLTM.MachineMaterialEvent_MaterialSheetDataUpdateReport == TRUE &&
//			CimInfo::m_LBMTL.MachineMaterialEventReply_MaterialSheetDataUpdateReportReply == TRUE)
//		{
//			CimInfo::m_LBLTM.MachineMaterialEvent_MaterialSheetDataUpdateReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//
//			szMsg.Format(_T("%s\\dat\\SheetInfo.dat"), SharedInfo::VisionAgentPath);
//
//			file.Open(szMsg, CFile::modeCreate | CFile::modeWrite);
//			file.Write(&CimInfo::SheetInfo, sizeof(SHEET_INFORMATION_BLOCK));
//			file.Close();
//
//			ClearT1TimeOut();
//
//		}
//		else if (IsT1TimeOut() &&
//			CimInfo::m_LBLTM.MachineMaterialEvent_MaterialSheetDataUpdateReport == TRUE)
//		{
//			ClearT1TimeOut();
//			CimInfo::m_LBLTM.MachineMaterialEvent_MaterialSheetDataUpdateReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE,101, _T("T1 Timeout :Sheet Move Out Report"));
//		}
//#pragma endregion
//
//#pragma region Sheet Data UpDate
//		if (CimInfo::m_LBLTM.MachineMaterialEvent_MaterialSheetDataDownloadRequest == TRUE &&
//			CimInfo::m_LBMTL.MachineMaterialEventReply_MaterialSheetDataDownloadRequestReply == TRUE)
//		{
//			CimInfo::m_LBLTM.MachineMaterialEvent_MaterialSheetDataDownloadRequest = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//
//			szMsg.Format(_T("%s\\dat\\SheetInfo.dat"), SharedInfo::VisionAgentPath);
//
//			file.Open(szMsg, CFile::modeCreate | CFile::modeWrite);
//			file.Write(&CimInfo::SheetInfo, sizeof(SHEET_INFORMATION_BLOCK));
//			file.Close();
//
//			ClearT1TimeOut();
//
//		}
//		else if (IsT1TimeOut() &&
//			CimInfo::m_LBLTM.MachineMaterialEvent_MaterialSheetDataDownloadRequest == TRUE)
//		{
//			ClearT1TimeOut();
//			CimInfo::m_LBLTM.MachineMaterialEvent_MaterialSheetDataDownloadRequest = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE,101, _T("T1 Timeout :Sheet Move Out Report"));
//		}
//#pragma endregion
//#if 0
//#pragma region Sheet Data Remove
//		if (CimInfo::m_LBLTM.bMachineEventSheetDataRemovedReport == TRUE &&
//			CimInfo::m_LBMTL.bMachineEventReplySheetDataRemovedReportReply == TRUE)
//		{
//			CimInfo::m_LBLTM.bMachineEventSheetDataRemovedReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//
//			szMsg.Format(_T("%s\\dat\\SheetInfo.dat"), SharedInfo::VisionAgentPath);
//
//			file.Open(szMsg, CFile::modeCreate | CFile::modeWrite);
//			file.Write(&CimInfo::SheetInfo, sizeof(SHEET_INFORMATION_BLOCK));
//			file.Close();
//
//			ClearT1TimeOut();
//
//		}
//		else if (IsT1TimeOut() &&
//			CimInfo::m_LBLTM.bMachineEventSheetDataRemovedReport == TRUE)
//		{
//			ClearT1TimeOut();
//			CimInfo::m_LBLTM.bMachineEventSheetDataRemovedReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE,101, _T("T1 Timeout :Sheet Move Out Report"));
//		}
//#pragma endregion
//#endif
//
//
//
//
//#pragma region Operator Login Report Reply
//		if (CimInfo::m_LBLTM.MachineEvent_OperatorLoginReport == TRUE &&
//			CimInfo::m_LBMTL.MachineEventReply_OperatorLoginReportReply == TRUE)
//		{
//			CimInfo::m_LBLTM.MachineEvent_OperatorLoginReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//
//			Etc_Msg(_T("Operator Login Report Reply"));
//
//			ClearT1TimeOut();
//
//		}
//		else if (IsT1TimeOut() &&
//			CimInfo::m_LBLTM.MachineEvent_OperatorLoginReport == TRUE)
//		{
//			ClearT1TimeOut();
//			CimInfo::m_LBLTM.MachineEvent_OperatorLoginReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE, 101,_T("T1 Timeout : Operator Login Report Reply"));
//		}
//#pragma endregion
//
//
//#pragma region Sheet Assembly Complete Report Reply
//		if (CimInfo::m_LBLTM.MachineMaterialEvent_SheetAssemblyCompleteReport == TRUE &&
//			CimInfo::m_LBMTL.MachineMaterialEventReply_SheetAssemblyCompleteReportReply == TRUE)
//		{
//			CimInfo::m_LBLTM.MachineMaterialEvent_SheetAssemblyCompleteReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//
//			Etc_Msg(_T("Sheet Assembly Complete Report Reply"));
//
//			ClearT1TimeOut();
//
//		}
//		else if (IsT1TimeOut() &&
//			CimInfo::m_LBLTM.MachineMaterialEvent_SheetAssemblyCompleteReport == TRUE)
//		{
//			ClearT1TimeOut();
//			CimInfo::m_LBLTM.MachineMaterialEvent_SheetAssemblyCompleteReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE, 101, _T("T1 Timeout : Sheet Assembly Complete Report Reply"));
//		}
//#pragma endregion
//
//
//		
//#pragma region Mask Reload Command
//		if (CimInfo::m_LBLTM.CIMPCMaskCommandReply_MaskReloadCommandSendReply == FALSE &&
//			CimInfo::m_LBMTL.CIMPCMaskCommand_MaskReloadCommandSend == TRUE)
//		{
//
//			MaskReloadCommandSendReplyBlock.MaskReloadCommandSendReplyAck = 1;
//			LWWrite(MASK_RELOAD_COMMAND_SEND_REPLY_BLOCK_START_ADDRESS, &MaskReloadCommandSendReplyBlock, sizeof(MaskReloadCommandSendReplyBlock));
//
//			CimInfo::m_LBLTM.CIMPCMaskCommandReply_MaskReloadCommandSendReply = TRUE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//
//			Etc_Msg(_T(" Mask Reload Command Reply"));
//
//			ClearT1TimeOut();
//
//		}
//		else if (CimInfo::m_LBLTM.CIMPCMaskCommandReply_MaskReloadCommandSendReply == TRUE &&
//			CimInfo::m_LBMTL.CIMPCMaskCommand_MaskReloadCommandSend == FALSE)
//		{
//			CimInfo::m_LBLTM.CIMPCMaskCommandReply_MaskReloadCommandSendReply = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//
//			
//
//			ClearT1TimeOut();
//
//		}
//		else if (IsT1TimeOut() &&
//			CimInfo::m_LBLTM.CIMPCMaskCommandReply_MaskReloadCommandSendReply == TRUE)
//		{
//			ClearT1TimeOut();
//			CimInfo::m_LBLTM.CIMPCMaskCommandReply_MaskReloadCommandSendReply = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE, 101, _T("T1 Timeout :  Mask Reload Command Reply"));
//		}
//#pragma endregion
//
//#pragma region Mask Job Download Command //KJT 20210409
//		if (CimInfo::m_LBLTM.CIMPCMaskCommandReply_MaskJobDownloadSendReply == FALSE &&
//			CimInfo::m_LBMTL.CIMPCMaskCommand_MaskJobDownloadSend == TRUE)
//		{
//			//KJT 20210409
//			MASK_JOB_DATA_BLOCK MaskJobDataBlock;
//			CimInfo::m_nCheckRecipe = 1;
//
//			//KJT 20210409
//			LWRead(MASK_JOB_DOWNLOAD_SEND_SUB_BLOCK_START_ADDRESS, &MaskJobDownloadSendSubBlock, sizeof(MaskJobDownloadSendSubBlock));
//			if (MaskJobDownloadSendSubBlock.DataExistCode != 1) //1:Exist, 2:NotExist //Cim NotExist Case
//			{
//				MaskJobDownloadSendReplyBlock.MaskJobDownloadSendReplyAck = 2; //1:Ok, 2:NG
//				CimInfo::m_nCheckRecipe = 2;
//			}
//			else
//			{ 
//				char * pValue = (char*)MaskJobDownloadSendBlock.MaskJobData;
//				memset(&MaskJobDownloadSendBlock, 0x0, sizeof(MaskJobDownloadSendBlock));
//				LWRead(MASK_JOB_DOWNLOAD_SEND_BLOCK_START_ADDRESS, &MaskJobDownloadSendBlock, sizeof(MaskJobDownloadSendBlock));
//
//				memcpy(&MaskJobDataBlock, &MaskJobDownloadSendBlock.MaskJobData, sizeof(MaskJobDataBlock));
//				int nReqRecipeNum = MaskJobDataBlock.Mask_PPID02_2;
//				int nResult = Devs::FindRecipeID(nReqRecipeNum);
//				if (nResult == -1)
//					CimInfo::m_nCheckRecipe = 3;
//				else
//				{
//					CString StrRecipeName = _T("");
//					StrRecipeName = SharedInfo::FindRecipeName(nResult);
//					if ((MaskJobDataBlock.Mask_PPID02_1 & 0xFF) != StrRecipeName[0] || ((MaskJobDataBlock.Mask_PPID02_1 & 0xFF00) >> 8) != StrRecipeName[1]) //Temp
//					{
//						CimInfo::m_nCheckRecipe = 3;
//					}
//				}
//
//				if (CimInfo::m_nCheckRecipe == 1)
//				{
//					for (int i = 0; i < sizeof(MaskJobDownloadSendBlock) * 2; i++)
//					{
//						if (*(pValue + i) == 0x20)
//							*(pValue + i) = 0;
//					}
//					for (int i = 19; i > 0; i--)
//					{
//
//						memcpy(&CimInfo::JobReceiveTime[i], &CimInfo::JobReceiveTime[i - 1], sizeof(CimInfo::JobReceiveTime[i]));
//						memcpy(&CimInfo::StoredJob[i], &CimInfo::StoredJob[i - 1], sizeof(CimInfo::StoredJob[i]));
//					}
//					GetLocalTime(&CimInfo::JobReceiveTime[0]);
//
//					memcpy(&CimInfo::MaskJobData.MaskJobDataBlock, &MaskJobDownloadSendBlock.MaskJobData, sizeof(CimInfo::MaskJobData.MaskJobDataBlock));
//					memcpy(&CimInfo::StoredJob[0], &CimInfo::MaskJobData, sizeof(CimInfo::MaskJobData));
//
//					SaveMaskJobData();
//
//					MaskJobDownloadSendReplyBlock.MaskJobDownloadSendReplyAck = 1; //1:Ok, 2:NG
//				}
//				else
//				{
//					MaskJobDownloadSendReplyBlock.MaskJobDownloadSendReplyAck = 2; //1:Ok, 2:NG
//				}
//			}
//
//			LWWrite(MASK_JOB_DOWNLOAD_COMMAND_SEND_REPLY_BLOCK_START_ADDRESS, &MaskJobDownloadSendReplyBlock, sizeof(MaskJobDownloadSendReplyBlock));
//			CimInfo::m_LBLTM.CIMPCMaskCommandReply_MaskJobDownloadSendReply = TRUE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//
//			Etc_Msg(_T(" Mask Reload Command Reply"));
//
//			SetT1TimeOut(); //KJT 20210409
//		}
//		else if (CimInfo::m_LBLTM.CIMPCMaskCommandReply_MaskJobDownloadSendReply == TRUE &&
//			CimInfo::m_LBMTL.CIMPCMaskCommand_MaskJobDownloadSend == FALSE)
//		{
//			CimInfo::m_LBLTM.CIMPCMaskCommandReply_MaskJobDownloadSendReply = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//
//			ClearT1TimeOut(); //KJT 20210409
//
//			//KJT 20210409
//			if (CimInfo::m_nCheckRecipe == 2 || CimInfo::m_nCheckRecipe == 3)
//			{
//				MASK_PROCESS_END_REPORT_BLOCK ProcessEndReportBlock;
//				CString szMsg;
//				SYSTEMTIME Time;
//				GetLocalTime(&Time);
//
//				ProcessEndReportBlock.ProcessEndTimeYear = Time.wYear;
//				ProcessEndReportBlock.ProcessEndTimeMonth = Time.wMonth;
//				ProcessEndReportBlock.ProcessEndTimeDay = Time.wDay;
//				ProcessEndReportBlock.ProcessEndTimeHour = Time.wHour;
//				ProcessEndReportBlock.ProcessEndTimeMinute = Time.wMinute;
//				ProcessEndReportBlock.ProcessEndTimeSecond = Time.wSecond;
//
//				if (CimInfo::m_nCheckRecipe == 2)
//					ProcessEndReportBlock.ProcessEndCode = 2; //2:Process End Cancel By Cim,  3:Process End Cancel By Machine
//				else if (CimInfo::m_nCheckRecipe == 3)
//					ProcessEndReportBlock.ProcessEndCode = 3; //2:Process End Cancel By Cim,  3:Process End Cancel By Machine
//
//				memset(ProcessEndReportBlock.MaskJobID, 0x0, sizeof(ProcessEndReportBlock.MaskJobID));
//				memcpy(ProcessEndReportBlock.MaskJobID, &CimInfo::MaskJobData.MaskJobDataBlock.Mask_JobID, sizeof(ProcessEndReportBlock.MaskJobID));
//
//				//20210407
//				ProcessEndReportBlock.LotSequenceNumber = CimInfo::MaskJobData.MaskJobDataBlock.Mask_LotSequenceNumber;
//				ProcessEndReportBlock.SlotSequenceNumber = CimInfo::MaskJobData.MaskJobDataBlock.Mask_SlotSequenceNumber;
//				ProcessEndReportBlock.UnitNumber = 1;
//				ProcessEndReportBlock.SlotNumber = 4;
//
//				//Devs::CimMotion.ReportEndProcess(ProcessEndReportBlock);
//
//				CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_GLASS_OR_PANEL_INFO_ERROR, ALARM_TYPE_ERROR, TRUE, 101, _T("Mask Job Data Error"));
//
//				//To Do. Auto Unload
//			}
//		}
//		else if (IsT1TimeOut() &&
//			CimInfo::m_LBLTM.CIMPCMaskCommandReply_MaskJobDownloadSendReply == TRUE)
//		{
//			ClearT1TimeOut();
//			CimInfo::m_LBLTM.CIMPCMaskCommandReply_MaskJobDownloadSendReply = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE, 101,_T("T1 Timeout :  Mask Reload Command Reply"));
//		}
//#pragma endregion
//
//
//#pragma region Recipe layter Info Report 
//		if (CimInfo::m_LBLTM.MachineEvent_RecipeLayerInfoReport == TRUE &&
//			CimInfo::m_LBMTL.MachineEventReply_RecipeLayerInfoReportReply == TRUE)
//		{
//
//
//
//			CimInfo::m_LBLTM.MachineEvent_RecipeLayerInfoReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//
//			Etc_Msg(_T("  Recipe layter Info Report Reply"));
//
//			ClearT1TimeOut();
//
//		}
//		else if (IsT1TimeOut() &&
//			CimInfo::m_LBLTM.MachineEvent_RecipeLayerInfoReport == TRUE)
//		{
//			ClearT1TimeOut();
//			CimInfo::m_LBLTM.MachineEvent_RecipeLayerInfoReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE, 101,_T("T1 Timeout :  Recipe layter Info Report Reply"));
//		}
//#pragma endregion
//
//
//
//#pragma region Mask Job Manual Move Report
//		if (CimInfo::m_LBLTM.MachineMaskEvent_MaskJobManualMoveReport == TRUE &&
//			CimInfo::m_LBMTL.MachineMaskEventReply_MaskJobManualMoveReportReply == TRUE)
//		{
//
//
//
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskJobManualMoveReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//
//			Etc_Msg(_T("[CIM]  Mask Job Manual Move Report Reply"));
//
//			ClearT1TimeOut();
//
//		}
//		else if (IsT1TimeOut() &&
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskJobManualMoveReport == TRUE)
//		{
//			ClearT1TimeOut();
//			CimInfo::m_LBLTM.MachineMaskEvent_MaskJobManualMoveReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE, 101, _T("T1 Timeout :  Recipe layter Info Report Reply"));
//		}
//#pragma endregion
//
//#pragma region Recipe Layer Info Request 
//		if (CimInfo::m_LBLTM.CIMPCCommandReply_RecipeLayerInfoRequestReply == FALSE &&
//			CimInfo::m_LBMTL.CIMPCCommand_RecipeLayerInfoRequest == TRUE)
//		{
//
//			LWRead(RECIPE_LAYER_INFO_REQUEST_BLOCK_START_ADDRESS, &RecipeLayerInfoRequestBlock, sizeof(RecipeLayerInfoRequestBlock));
//
//
//			Etc_Msg(_T(" Recipe Layer Info Request  Reply"));
//
//			memset(&RecipeLayerInfoRequestReplyBlock, 0x0, sizeof(RecipeLayerInfoRequestReplyBlock));
//			RecipeLayerInfoRequestReplyBlock.RecipeNumber = RecipeLayerInfoRequestBlock.RecipeNumber;
//			RecipeLayerInfoRequestReplyBlock.UnitRecipeText1 = RecipeLayerInfoRequestBlock.RecipeText;
//			RecipeLayerInfoRequestReplyBlock.LayerNumber1 = 1;
//			RecipeLayerInfoRequestReplyBlock.UnitNumber1 = 1;
//			RecipeLayerInfoRequestReplyBlock.RecipeNumber = SharedInfo::Active.nActiveRecipeNum;
//			RecipeLayerInfoRequestReplyBlock.RecipeVersionSequenceNumber = 1;
//
//			LWWrite(RECIPE_LAYER_INFO_REQUEST_REPLY_BLOCK_START_ADDRESS, &RecipeLayerInfoRequestReplyBlock, sizeof(RecipeLayerInfoRequestReplyBlock));
//
//			CimInfo::m_LBLTM.CIMPCCommandReply_RecipeLayerInfoRequestReply = TRUE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//
//			ClearT1TimeOut();
//
//		}
//		else if (CimInfo::m_LBLTM.CIMPCCommandReply_RecipeLayerInfoRequestReply == TRUE &&
//			CimInfo::m_LBMTL.CIMPCCommand_RecipeLayerInfoRequest == TRUE)
//		{
//			CimInfo::m_LBLTM.CIMPCCommandReply_RecipeLayerInfoRequestReply = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//		}
//		else if (IsT1TimeOut() &&
//			CimInfo::m_LBLTM.CIMPCCommandReply_RecipeLayerInfoRequestReply == TRUE)
//		{
//			ClearT1TimeOut();
//			CimInfo::m_LBLTM.CIMPCCommandReply_RecipeLayerInfoRequestReply = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE, 101,_T("T1 Timeout : Recipe Layer Info Request Reply"));
//		}
//#pragma endregion
//
//
//#pragma region Recipe Step Count Request 
//		if (CimInfo::m_LBLTM.CIMPCCommandReply_RecipeStepCountRequestReply == FALSE &&
//			CimInfo::m_LBMTL.CIMPCCommand_RecipeStepCountRequest == TRUE)
//		{
//
//			LWRead(RECIPE_STEP_COUNT_REQUEST_BLOCK_START_ADDRESS, &RecipeStepCountRequestBlock, sizeof(RecipeStepCountRequestBlock));
//
//			Etc_Msg(_T("Recipe Step Count Request  Reply"));
//
//			RecipeStepCountRequestReplyBlock.RecipeNumber = RecipeStepCountRequestBlock.RecipeNumber;
//			RecipeStepCountRequestReplyBlock.RecipeText = RecipeStepCountRequestBlock.RecipeText;
//			RecipeStepCountRequestReplyBlock.StepCount = 1;
//			RecipeStepCountRequestReplyBlock.UnitNumber = 1;
//			//RecipeStepCountRequestReplyBlock.RecipeNumber = SharedInfo::Active.nActiveRecipeNum; //KJT 20210408 Hide
//			RecipeStepCountRequestReplyBlock.RecipeVersionSequenceNumber = 1;
//
//			LWWrite(RECIPE_STEP_COUNT_REQUEST_REPLY_BLOCK_START_ADDRESS, &RecipeStepCountRequestReplyBlock, sizeof(RecipeStepCountRequestReplyBlock));
//			CimInfo::m_LBLTM.CIMPCCommandReply_RecipeStepCountRequestReply = TRUE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//
//			SetT1TimeOut(); //KJT 20210408
//
//		}
//		else if (IsT1TimeOut() &&
//			CimInfo::m_LBLTM.CIMPCCommandReply_RecipeStepCountRequestReply == TRUE)
//		{
//			ClearT1TimeOut();
//			CimInfo::m_LBLTM.CIMPCCommandReply_RecipeStepCountRequestReply = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//
//			//KJT 20210408 Hide
//			//CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE, 101,_T("T1 Timeout : Recipe Step Count Request Reply"));
//		}
//#pragma endregion
//
//
//#pragma region Recipe Change Report
//		if (CimInfo::m_LBLTM.MachineEvent_RecipeChangeReport == TRUE &&
//			CimInfo::m_LBMTL.MachineEventReply_RecipeChangeReportReply == TRUE)
//		{
//
//			Etc_Msg(_T("[CIM] Recipe Change Report Reply"));
//			CimInfo::m_LBLTM.MachineEvent_RecipeChangeReport = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//
//			ClearT1TimeOut();
//
//		}
//		else if (IsT1TimeOut() &&
//			CimInfo::m_LBLTM.CIMPCCommandReply_RecipeStepCountRequestReply == TRUE)
//		{
//			ClearT1TimeOut();
//			CimInfo::m_LBLTM.CIMPCCommandReply_RecipeStepCountRequestReply = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE, 101, _T("T1 Timeout : Recipe Step Count Request Reply"));
//		}
//#pragma endregion
//
//
//
//#pragma region Recipe Parameter Data Download Send Block
//		if (CimInfo::m_LBLTM.CIMPCCommandReply_RecipeParameterDataDownloadSendReply == FALSE &&
//			CimInfo::m_LBMTL.CIMPCCommand_RecipeParameterDataDownloadSend == TRUE)
//		{
//
//			LWRead(RECIPE_PARAMETER_DOWNLOAD_COMMAND_BLOCK_START_ADDRESS, &RecipeParameterDataDownloadSendBlock, sizeof(RecipeParameterDataDownloadSendBlock));
//
//			Etc_Msg(_T("Recipe Parameter Data Download Send Block"));
//
//			RecipeParameterDataDownloadSendReplyBlock.RecipeParameterDataDownloadResult = 1;
//
//			LWWrite(RECIPE_PARAMETER_DOWNLOAD_COMMAND_REPLY_BLOCK_START_ADDRESS, &RecipeParameterDataDownloadSendReplyBlock, sizeof(RecipeParameterDataDownloadSendReplyBlock));
//			CimInfo::m_LBLTM.CIMPCCommandReply_RecipeParameterDataDownloadSendReply = TRUE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//
//			ClearT1TimeOut();
//
//		}
//		else if (CimInfo::m_LBLTM.CIMPCCommandReply_RecipeParameterDataDownloadSendReply == TRUE &&
//			CimInfo::m_LBMTL.CIMPCCommand_RecipeParameterDataDownloadSend == TRUE)
//		{
//			CimInfo::m_LBLTM.CIMPCCommandReply_RecipeParameterDataDownloadSendReply = FALSE;
//		}
//		else if (IsT1TimeOut() &&
//			CimInfo::m_LBLTM.CIMPCCommandReply_RecipeStepCountRequestReply == TRUE)
//		{
//			ClearT1TimeOut();
//			CimInfo::m_LBLTM.CIMPCCommandReply_RecipeStepCountRequestReply = FALSE;
//			LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//
//			//KJT 20210324
//			CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, ALARM_CODE_CIM_PC_T1_TIMEOUT, ALARM_TYPE_ERROR, TRUE, 101,_T("T1 Timeout : Recipe Parameter Data Download Send Block"));
//		}
//#pragma endregion
//
//#pragma endregion
//		Sleep(200);
//
//	}
//
//	m_bRevChk = TRUE;
}
VOID CCimModule::RobotThreadFunctionEntry(VOID)
{
	CString szMsg = _T("");
	
	while (m_RobotFinish)
	{
		//연결 초기화 될때까지 Wait

#pragma region Tower Lamp
#pragma endregion

#pragma region Event Receive
		//LBRead(LB_LTM_START_ADDRESS, &SharedInfo::m_LB_MTL, sizeof(SharedInfo::m_LB_MTL));
		//LBRead(LB_MTL_START_ADDRESS, &SharedInfo::m_LB_LTM, sizeof(SharedInfo::m_LB_LTM));
#pragma endregion

		Sleep(100);
	}
}


#if 0

VOID CCimModule::CimReceiveThreadFunctionEntry(VOID)
{
	CString szMsg = _T("");

	while (m_ReceiveFinish)
	{
		//연결 초기화 될때까지 Wait

#pragma region Tower Lamp
#pragma endregion

#pragma region Event Receive
		//LBRead(LB_LTM_START_ADDRESS, &SharedInfo::m_LB_MTL, sizeof(SharedInfo::m_LB_MTL));
		//LBRead(LB_MTL_START_ADDRESS, &SharedInfo::m_LB_LTM, sizeof(SharedInfo::m_LB_LTM));
#pragma endregion

		Sleep(100);
	}
}
#endif


#if 0 //B12 Not Use //KJT 20210325
int CCimModule::JobDataAWrite(int nAddr, MATERIAL_DATA_A MeterialData)
{
	int nRtn;

	nRtn = LWWrite(nAddr, &MeterialData, sizeof(MATERIAL_DATA_A));
	return nRtn;
}

int CCimModule::JobDataBWrite(int nAddr, MATERIAL_DATA_B MeterialData)
{
	int nRtn;
	nRtn = LWWrite(nAddr, &MeterialData, sizeof(MATERIAL_DATA_B));
	return nRtn;
}
void CCimModule::GetJobDataAFromRobot()
{
	WORD *JobDataTmp;
	JobDataTmp = (WORD*)malloc(sizeof(MATERIAL_DATA_A));
	//lw(RobotJobDataAddrss, JobDataTmp, sizeof(MATERIAL_DATA_A));
	//pCim->m_pMelsec->LWRead(nAddr, JobDataTmp, sizeof(MATERIAL_DATA_A));

	for (int i = 0; i < sizeof(MATERIAL_DATA_A); i++)
	{
		if (JobDataTmp[i] == 0x2020)			//0x2020은 ".."
			JobDataTmp[i] = 0;
	}

	memcpy(&CimInfo::JobDataA, JobDataTmp, sizeof(MATERIAL_DATA_A));
	free(JobDataTmp);

}
#endif

//void CCimModule::JobDataBRead(int nAddr)
//{
//	MATERIAL_DATA_B MeterialData;
//	GetLwUser1BufData(nAddr, &MeterialData, sizeof(MATERIAL_DATA_B));
//	//pCim->m_pMelsec->LWRead(nAddr, &MeterialData, sizeof(MATERIAL_DATA_B));
//}

BOOL CCimModule::IsAliveTimeOut()
{

	double dLapse = 0.0;
	LARGE_INTEGER freq, start, end;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);

	dLapse = ((start.QuadPart) / (double)freq.QuadPart) * 1000; //msec


	if (m_dAliveTimerCheck == 0)
		return FALSE;

	if (dLapse - m_dAliveTimerCheck == 0)
		return  FALSE;
	else if (dLapse - m_dAliveTimerCheck > m_dAliveTimer)
	{
		m_dAliveTimerCheck = 0;
		return  TRUE;
	}
	else
		return  FALSE;

}

void CCimModule::SetAliveTimeOut()
{
	double dLapse = 0.0;
	LARGE_INTEGER freq, start, end;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);


	dLapse = ((start.QuadPart) / (double)freq.QuadPart) * 1000; //msec
	m_dAliveTimerCheck = (DWORD)(FLOAT)dLapse;
}


BOOL CCimModule::IsT1TimeOut()
{
	double dLapse = 0.0;
	LARGE_INTEGER freq, start, end;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);
	dLapse = ((start.QuadPart) / (double)freq.QuadPart) * 1000; //msec
	if (CimInfo::m_T1TimerCheck == 0)
		return FALSE;

	if (dLapse - CimInfo::m_T1TimerCheck == 0)
		return  FALSE;
	else if (dLapse - CimInfo::m_T1TimerCheck > CimInfo::m_T1Timer)
	{

		return  TRUE;
	}
	else
		return  FALSE;

}



void CCimModule::SetT1TimeOut()
{
	double dLapse = 0.0;
	LARGE_INTEGER freq, start, end;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);
	dLapse = ((start.QuadPart) / (double)freq.QuadPart) * 1000; //msec
	CimInfo::m_T1TimerCheck = dLapse;
}
void CCimModule::ClearT1TimeOut()
{
	CimInfo::m_T1TimerCheck = 0;
}
#pragma region //KJT 20210407 //ECS
void CCimModule::CheckAlarmReserved()
{
	//CString Str = _T("");
	//int nAlarmID = 0;

	//if (CimInfo::m_nAlarmReserveCount > 0 &&
	//	(CimInfo::m_LBLTM.MachineEvent_Alarm_1Report == FALSE || CimInfo::m_LBLTM.MachineEvent_Alarm_2Report == FALSE || CimInfo::m_LBLTM.MachineEvent_Alarm_3Report == FALSE ||
	//		CimInfo::m_LBLTM.MachineEvent_Alarm_4Report == FALSE || CimInfo::m_LBLTM.MachineEvent_Alarm_5Report == FALSE))
	//{
	//	Sleep(500); //!!
	//	if (CimInfo::m_LBLTM.MachineEvent_Alarm_1Report == FALSE)
	//	{
	//		nAlarmID = CimInfo::AlarmBlockReserve[0].AlarmID;

	//		CimInfo::AlarmReportOccuredTime[nAlarmID] = CimInfo::AlarmOccuredTimeReserve[0];
	//		CimInfo::AlarmReportBlock[nAlarmID].AlarmStatus = CimInfo::AlarmBlockReserve[0].AlarmStatus;
	//		CimInfo::AlarmReportBlock[nAlarmID].AlarmUnitNumber = CimInfo::AlarmBlockReserve[0].AlarmUnitNumber;
	//		CimInfo::AlarmReportBlock[nAlarmID].AlarmID = CimInfo::AlarmBlockReserve[0].AlarmID;
	//		CimInfo::AlarmReportBlock[nAlarmID].AlarmCode = CimInfo::AlarmBlockReserve[0].AlarmCode;
	//		CimInfo::AlarmReportBlock[nAlarmID].AlarmType = CimInfo::AlarmBlockReserve[0].AlarmType;
	//		memcpy(CimInfo::AlarmReportBlock[nAlarmID].AlarmText, CimInfo::AlarmBlockReserve[0].AlarmText, sizeof(CimInfo::AlarmBlockReserve[0].AlarmText));

	//		//KJT 20210417
	//		CimInfo::AlarmOccuredTime[CimInfo::m_nAlarmReportCount] = CimInfo::AlarmReportOccuredTime[nAlarmID]; //
	//		CimInfo::AlarmBlock[CimInfo::m_nAlarmReportCount].AlarmStatus = CimInfo::AlarmBlockReserve[0].AlarmStatus;
	//		CimInfo::AlarmBlock[CimInfo::m_nAlarmReportCount].AlarmUnitNumber = 1;
	//		CimInfo::AlarmBlock[CimInfo::m_nAlarmReportCount].AlarmID = nAlarmID;
	//		CimInfo::AlarmBlock[CimInfo::m_nAlarmReportCount].AlarmCode = CimInfo::AlarmBlockReserve[0].AlarmCode;
	//		CimInfo::AlarmBlock[CimInfo::m_nAlarmReportCount].AlarmType = CimInfo::AlarmBlockReserve[0].AlarmType;
	//		//CimInfo::AlarmBlock[CimInfo::m_nAlarmReportCount].AlarmTextUsingFlag = AlarmTextUsingFlag;
	//		memcpy(CimInfo::AlarmBlock[CimInfo::m_nAlarmReportCount].AlarmText, CimInfo::AlarmBlockReserve[0].AlarmText, sizeof(CimInfo::AlarmBlockReserve[0].AlarmText));
	//		CimInfo::m_nAlarmReportCount++;

	//		CimInfo::m_nAlarmPos[nAlarmID] = 0; //KJT 20210407

	//		LWWrite(ALARM_REPORT_BLOCK_1_START_ADDRESS, &CimInfo::AlarmReportBlock[nAlarmID], sizeof(LW_LTM_ALARM_BLOCK));
	//		CimInfo::m_LBLTM.MachineEvent_Alarm_1Report = TRUE;
	//		Str.Format(_T(">> MachineEvent_Alarm_1Report TRUE (Reserved AlarmID:%d)"), nAlarmID);
	//		Etc_Msg(Str);

	//		LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	//		SetAlarmT1TimeOut(0); //KJT 20210407

	//		CimInfo::m_AlarmMaxPos++;
	//		if (CimInfo::m_AlarmMaxPos > 5)
	//			CimInfo::m_AlarmMaxPos = 1;

	//		CimInfo::m_nAlarmReserveCount--;
	//		if (CimInfo::m_nAlarmReserveCount < 0)
	//			CimInfo::m_nAlarmReserveCount = 0;

	//		Str.Format(_T("m_nAlarmReserveCount %d"), CimInfo::m_nAlarmReserveCount);
	//		Etc_Msg(Str);

	//		for (int i = 0; i < CimInfo::m_nAlarmReserveCount; i++)
	//		{
	//			CimInfo::AlarmOccuredTimeReserve[i] = CimInfo::AlarmOccuredTimeReserve[i + 1];
	//			CimInfo::AlarmBlockReserve[i].AlarmStatus = CimInfo::AlarmBlockReserve[i + 1].AlarmStatus;
	//			CimInfo::AlarmBlockReserve[i].AlarmUnitNumber = CimInfo::AlarmBlockReserve[i + 1].AlarmUnitNumber;
	//			CimInfo::AlarmBlockReserve[i].AlarmID = CimInfo::AlarmBlockReserve[i + 1].AlarmID;
	//			CimInfo::AlarmBlockReserve[i].AlarmCode = CimInfo::AlarmBlockReserve[i + 1].AlarmCode;
	//			CimInfo::AlarmBlockReserve[i].AlarmType = CimInfo::AlarmBlockReserve[i + 1].AlarmType;
	//			memcpy(CimInfo::AlarmBlockReserve[i].AlarmText, CimInfo::AlarmBlockReserve[i + 1].AlarmText, sizeof(CimInfo::AlarmBlockReserve[i].AlarmText));
	//		}
	//	}
	//	else if (CimInfo::m_LBLTM.MachineEvent_Alarm_2Report == FALSE)
	//	{
	//		nAlarmID = CimInfo::AlarmBlockReserve[1].AlarmID;

	//		CimInfo::AlarmReportOccuredTime[nAlarmID] = CimInfo::AlarmOccuredTimeReserve[0];
	//		CimInfo::AlarmReportBlock[nAlarmID].AlarmStatus = CimInfo::AlarmBlockReserve[0].AlarmStatus;
	//		CimInfo::AlarmReportBlock[nAlarmID].AlarmUnitNumber = CimInfo::AlarmBlockReserve[0].AlarmUnitNumber;
	//		CimInfo::AlarmReportBlock[nAlarmID].AlarmID = CimInfo::AlarmBlockReserve[0].AlarmID;
	//		CimInfo::AlarmReportBlock[nAlarmID].AlarmCode = CimInfo::AlarmBlockReserve[0].AlarmCode;
	//		CimInfo::AlarmReportBlock[nAlarmID].AlarmType = CimInfo::AlarmBlockReserve[0].AlarmType;
	//		memcpy(CimInfo::AlarmReportBlock[nAlarmID].AlarmText, CimInfo::AlarmBlockReserve[0].AlarmText, sizeof(CimInfo::AlarmBlockReserve[0].AlarmText));

	//		//KJT 20210417
	//		CimInfo::AlarmOccuredTime[CimInfo::m_nAlarmReportCount] = CimInfo::AlarmReportOccuredTime[nAlarmID]; //
	//		CimInfo::AlarmBlock[CimInfo::m_nAlarmReportCount].AlarmStatus = CimInfo::AlarmBlockReserve[0].AlarmStatus;
	//		CimInfo::AlarmBlock[CimInfo::m_nAlarmReportCount].AlarmUnitNumber = 1;
	//		CimInfo::AlarmBlock[CimInfo::m_nAlarmReportCount].AlarmID = nAlarmID;
	//		CimInfo::AlarmBlock[CimInfo::m_nAlarmReportCount].AlarmCode = CimInfo::AlarmBlockReserve[0].AlarmCode;
	//		CimInfo::AlarmBlock[CimInfo::m_nAlarmReportCount].AlarmType = CimInfo::AlarmBlockReserve[0].AlarmType;
	//		//CimInfo::AlarmBlock[CimInfo::m_nAlarmReportCount].AlarmTextUsingFlag = AlarmTextUsingFlag;
	//		memcpy(CimInfo::AlarmBlock[CimInfo::m_nAlarmReportCount].AlarmText, CimInfo::AlarmBlockReserve[0].AlarmText, sizeof(CimInfo::AlarmBlockReserve[0].AlarmText));
	//		CimInfo::m_nAlarmReportCount++;

	//		CimInfo::m_nAlarmPos[nAlarmID] = 1; //KJT 20210407

	//		LWWrite(ALARM_REPORT_BLOCK_2_START_ADDRESS, &CimInfo::AlarmReportBlock[nAlarmID], sizeof(LW_LTM_ALARM_BLOCK));
	//		CimInfo::m_LBLTM.MachineEvent_Alarm_2Report = TRUE;
	//		Str.Format(_T(">> MachineEvent_Alarm_2Report TRUE (Reserved AlarmID:%d)"), nAlarmID);
	//		Etc_Msg(Str);

	//		LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	//		SetAlarmT1TimeOut(1); //KJT 20210407

	//		CimInfo::m_AlarmMaxPos++;
	//		if (CimInfo::m_AlarmMaxPos > 5)
	//			CimInfo::m_AlarmMaxPos = 1;

	//		CimInfo::m_nAlarmReserveCount--;
	//		if (CimInfo::m_nAlarmReserveCount < 0)
	//			CimInfo::m_nAlarmReserveCount = 0;

	//		Str.Format(_T("m_nAlarmReserveCount %d"), CimInfo::m_nAlarmReserveCount);
	//		Etc_Msg(Str);

	//		for (int i = 0; i < CimInfo::m_nAlarmReserveCount; i++)
	//		{
	//			CimInfo::AlarmOccuredTimeReserve[i] = CimInfo::AlarmOccuredTimeReserve[i + 1];
	//			CimInfo::AlarmBlockReserve[i].AlarmStatus = CimInfo::AlarmBlockReserve[i + 1].AlarmStatus;
	//			CimInfo::AlarmBlockReserve[i].AlarmUnitNumber = CimInfo::AlarmBlockReserve[i + 1].AlarmUnitNumber;
	//			CimInfo::AlarmBlockReserve[i].AlarmID = CimInfo::AlarmBlockReserve[i + 1].AlarmID;
	//			CimInfo::AlarmBlockReserve[i].AlarmCode = CimInfo::AlarmBlockReserve[i + 1].AlarmCode;
	//			CimInfo::AlarmBlockReserve[i].AlarmType = CimInfo::AlarmBlockReserve[i + 1].AlarmType;
	//			memcpy(CimInfo::AlarmBlockReserve[i].AlarmText, CimInfo::AlarmBlockReserve[i + 1].AlarmText, sizeof(CimInfo::AlarmBlockReserve[i].AlarmText));
	//		}
	//	}
	//	else if (CimInfo::m_LBLTM.MachineEvent_Alarm_3Report == FALSE)
	//	{
	//		nAlarmID = CimInfo::AlarmBlockReserve[2].AlarmID;

	//		CimInfo::AlarmReportOccuredTime[nAlarmID] = CimInfo::AlarmOccuredTimeReserve[0];
	//		CimInfo::AlarmReportBlock[nAlarmID].AlarmStatus = CimInfo::AlarmBlockReserve[0].AlarmStatus;
	//		CimInfo::AlarmReportBlock[nAlarmID].AlarmUnitNumber = CimInfo::AlarmBlockReserve[0].AlarmUnitNumber;
	//		CimInfo::AlarmReportBlock[nAlarmID].AlarmID = CimInfo::AlarmBlockReserve[0].AlarmID;
	//		CimInfo::AlarmReportBlock[nAlarmID].AlarmCode = CimInfo::AlarmBlockReserve[0].AlarmCode;
	//		CimInfo::AlarmReportBlock[nAlarmID].AlarmType = CimInfo::AlarmBlockReserve[0].AlarmType;
	//		memcpy(CimInfo::AlarmReportBlock[nAlarmID].AlarmText, CimInfo::AlarmBlockReserve[0].AlarmText, sizeof(CimInfo::AlarmBlockReserve[0].AlarmText));

	//		//KJT 20210417
	//		CimInfo::AlarmOccuredTime[CimInfo::m_nAlarmReportCount] = CimInfo::AlarmReportOccuredTime[nAlarmID]; //
	//		CimInfo::AlarmBlock[CimInfo::m_nAlarmReportCount].AlarmStatus = CimInfo::AlarmBlockReserve[0].AlarmStatus;
	//		CimInfo::AlarmBlock[CimInfo::m_nAlarmReportCount].AlarmUnitNumber = 1;
	//		CimInfo::AlarmBlock[CimInfo::m_nAlarmReportCount].AlarmID = nAlarmID;
	//		CimInfo::AlarmBlock[CimInfo::m_nAlarmReportCount].AlarmCode = CimInfo::AlarmBlockReserve[0].AlarmCode;
	//		CimInfo::AlarmBlock[CimInfo::m_nAlarmReportCount].AlarmType = CimInfo::AlarmBlockReserve[0].AlarmType;
	//		//CimInfo::AlarmBlock[CimInfo::m_nAlarmReportCount].AlarmTextUsingFlag = AlarmTextUsingFlag;
	//		memcpy(CimInfo::AlarmBlock[CimInfo::m_nAlarmReportCount].AlarmText, CimInfo::AlarmBlockReserve[0].AlarmText, sizeof(CimInfo::AlarmBlockReserve[0].AlarmText));
	//		CimInfo::m_nAlarmReportCount++;

	//		CimInfo::m_nAlarmPos[nAlarmID] = 2; //KJT 20210407

	//		LWWrite(ALARM_REPORT_BLOCK_3_START_ADDRESS, &CimInfo::AlarmReportBlock[nAlarmID], sizeof(LW_LTM_ALARM_BLOCK));
	//		CimInfo::m_LBLTM.MachineEvent_Alarm_3Report = TRUE;
	//		Str.Format(_T(">> MachineEvent_Alarm_3Report TRUE (Reserved AlarmID:%d)"), nAlarmID);
	//		Etc_Msg(Str);

	//		LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	//		SetAlarmT1TimeOut(2); //KJT 20210407

	//		CimInfo::m_AlarmMaxPos++;
	//		if (CimInfo::m_AlarmMaxPos > 5)
	//			CimInfo::m_AlarmMaxPos = 1;

	//		CimInfo::m_nAlarmReserveCount--;
	//		if (CimInfo::m_nAlarmReserveCount < 0)
	//			CimInfo::m_nAlarmReserveCount = 0;
	//		
	//		Str.Format(_T("m_nAlarmReserveCount %d"), CimInfo::m_nAlarmReserveCount);
	//		Etc_Msg(Str);

	//		for (int i = 0; i < CimInfo::m_nAlarmReserveCount; i++)
	//		{
	//			CimInfo::AlarmOccuredTimeReserve[i] = CimInfo::AlarmOccuredTimeReserve[i + 1];
	//			CimInfo::AlarmBlockReserve[i].AlarmStatus = CimInfo::AlarmBlockReserve[i + 1].AlarmStatus;
	//			CimInfo::AlarmBlockReserve[i].AlarmUnitNumber = CimInfo::AlarmBlockReserve[i + 1].AlarmUnitNumber;
	//			CimInfo::AlarmBlockReserve[i].AlarmID = CimInfo::AlarmBlockReserve[i + 1].AlarmID;
	//			CimInfo::AlarmBlockReserve[i].AlarmCode = CimInfo::AlarmBlockReserve[i + 1].AlarmCode;
	//			CimInfo::AlarmBlockReserve[i].AlarmType = CimInfo::AlarmBlockReserve[i + 1].AlarmType;
	//			memcpy(CimInfo::AlarmBlockReserve[i].AlarmText, CimInfo::AlarmBlockReserve[i + 1].AlarmText, sizeof(CimInfo::AlarmBlockReserve[i].AlarmText));
	//		}
	//	}
	//	else if (CimInfo::m_LBLTM.MachineEvent_Alarm_4Report == FALSE)
	//	{
	//		nAlarmID = CimInfo::AlarmBlockReserve[3].AlarmID;

	//		CimInfo::AlarmReportOccuredTime[nAlarmID] = CimInfo::AlarmOccuredTimeReserve[0];
	//		CimInfo::AlarmReportBlock[nAlarmID].AlarmStatus = CimInfo::AlarmBlockReserve[0].AlarmStatus;
	//		CimInfo::AlarmReportBlock[nAlarmID].AlarmUnitNumber = CimInfo::AlarmBlockReserve[0].AlarmUnitNumber;
	//		CimInfo::AlarmReportBlock[nAlarmID].AlarmID = CimInfo::AlarmBlockReserve[0].AlarmID;
	//		CimInfo::AlarmReportBlock[nAlarmID].AlarmCode = CimInfo::AlarmBlockReserve[0].AlarmCode;
	//		CimInfo::AlarmReportBlock[nAlarmID].AlarmType = CimInfo::AlarmBlockReserve[0].AlarmType;
	//		memcpy(CimInfo::AlarmReportBlock[nAlarmID].AlarmText, CimInfo::AlarmBlockReserve[0].AlarmText, sizeof(CimInfo::AlarmBlockReserve[0].AlarmText));

	//		//KJT 20210417
	//		CimInfo::AlarmOccuredTime[CimInfo::m_nAlarmReportCount] = CimInfo::AlarmReportOccuredTime[nAlarmID]; //
	//		CimInfo::AlarmBlock[CimInfo::m_nAlarmReportCount].AlarmStatus = CimInfo::AlarmBlockReserve[0].AlarmStatus;
	//		CimInfo::AlarmBlock[CimInfo::m_nAlarmReportCount].AlarmUnitNumber = 1;
	//		CimInfo::AlarmBlock[CimInfo::m_nAlarmReportCount].AlarmID = nAlarmID;
	//		CimInfo::AlarmBlock[CimInfo::m_nAlarmReportCount].AlarmCode = CimInfo::AlarmBlockReserve[0].AlarmCode;
	//		CimInfo::AlarmBlock[CimInfo::m_nAlarmReportCount].AlarmType = CimInfo::AlarmBlockReserve[0].AlarmType;
	//		//CimInfo::AlarmBlock[CimInfo::m_nAlarmReportCount].AlarmTextUsingFlag = AlarmTextUsingFlag;
	//		memcpy(CimInfo::AlarmBlock[CimInfo::m_nAlarmReportCount].AlarmText, CimInfo::AlarmBlockReserve[0].AlarmText, sizeof(CimInfo::AlarmBlockReserve[0].AlarmText));
	//		CimInfo::m_nAlarmReportCount++;

	//		CimInfo::m_nAlarmPos[nAlarmID] = 3; //KJT 20210407

	//		LWWrite(ALARM_REPORT_BLOCK_4_START_ADDRESS, &CimInfo::AlarmReportBlock[nAlarmID], sizeof(LW_LTM_ALARM_BLOCK));
	//		CimInfo::m_LBLTM.MachineEvent_Alarm_4Report = TRUE;
	//		Str.Format(_T(">> MachineEvent_Alarm_4Report TRUE (Reserved AlarmID:%d)"), nAlarmID);
	//		Etc_Msg(Str);

	//		LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	//		SetAlarmT1TimeOut(3); //KJT 20210407

	//		CimInfo::m_AlarmMaxPos++;
	//		if (CimInfo::m_AlarmMaxPos > 5)
	//			CimInfo::m_AlarmMaxPos = 1;

	//		CimInfo::m_nAlarmReserveCount--;
	//		if (CimInfo::m_nAlarmReserveCount < 0)
	//			CimInfo::m_nAlarmReserveCount = 0;
	//		
	//		Str.Format(_T("m_nAlarmReserveCount %d"), CimInfo::m_nAlarmReserveCount);
	//		Etc_Msg(Str);

	//		for (int i = 0; i < CimInfo::m_nAlarmReserveCount; i++)
	//		{
	//			CimInfo::AlarmOccuredTimeReserve[i] = CimInfo::AlarmOccuredTimeReserve[i + 1];
	//			CimInfo::AlarmBlockReserve[i].AlarmStatus = CimInfo::AlarmBlockReserve[i + 1].AlarmStatus;
	//			CimInfo::AlarmBlockReserve[i].AlarmUnitNumber = CimInfo::AlarmBlockReserve[i + 1].AlarmUnitNumber;
	//			CimInfo::AlarmBlockReserve[i].AlarmID = CimInfo::AlarmBlockReserve[i + 1].AlarmID;
	//			CimInfo::AlarmBlockReserve[i].AlarmCode = CimInfo::AlarmBlockReserve[i + 1].AlarmCode;
	//			CimInfo::AlarmBlockReserve[i].AlarmType = CimInfo::AlarmBlockReserve[i + 1].AlarmType;
	//			memcpy(CimInfo::AlarmBlockReserve[i].AlarmText, CimInfo::AlarmBlockReserve[i + 1].AlarmText, sizeof(CimInfo::AlarmBlockReserve[i].AlarmText));
	//		}
	//	}
	//	else if (CimInfo::m_LBLTM.MachineEvent_Alarm_5Report == FALSE)
	//	{
	//		nAlarmID = CimInfo::AlarmBlockReserve[4].AlarmID;

	//		CimInfo::AlarmReportOccuredTime[nAlarmID] = CimInfo::AlarmOccuredTimeReserve[0];
	//		CimInfo::AlarmReportBlock[nAlarmID].AlarmStatus = CimInfo::AlarmBlockReserve[0].AlarmStatus;
	//		CimInfo::AlarmReportBlock[nAlarmID].AlarmUnitNumber = CimInfo::AlarmBlockReserve[0].AlarmUnitNumber;
	//		CimInfo::AlarmReportBlock[nAlarmID].AlarmID = CimInfo::AlarmBlockReserve[0].AlarmID;
	//		CimInfo::AlarmReportBlock[nAlarmID].AlarmCode = CimInfo::AlarmBlockReserve[0].AlarmCode;
	//		CimInfo::AlarmReportBlock[nAlarmID].AlarmType = CimInfo::AlarmBlockReserve[0].AlarmType;
	//		memcpy(CimInfo::AlarmReportBlock[nAlarmID].AlarmText, CimInfo::AlarmBlockReserve[0].AlarmText, sizeof(CimInfo::AlarmBlockReserve[0].AlarmText));

	//		//KJT 20210417
	//		CimInfo::AlarmOccuredTime[CimInfo::m_nAlarmReportCount] = CimInfo::AlarmReportOccuredTime[nAlarmID]; //
	//		CimInfo::AlarmBlock[CimInfo::m_nAlarmReportCount].AlarmStatus = CimInfo::AlarmBlockReserve[0].AlarmStatus;
	//		CimInfo::AlarmBlock[CimInfo::m_nAlarmReportCount].AlarmUnitNumber = 1;
	//		CimInfo::AlarmBlock[CimInfo::m_nAlarmReportCount].AlarmID = nAlarmID;
	//		CimInfo::AlarmBlock[CimInfo::m_nAlarmReportCount].AlarmCode = CimInfo::AlarmBlockReserve[0].AlarmCode;
	//		CimInfo::AlarmBlock[CimInfo::m_nAlarmReportCount].AlarmType = CimInfo::AlarmBlockReserve[0].AlarmType;
	//		//CimInfo::AlarmBlock[CimInfo::m_nAlarmReportCount].AlarmTextUsingFlag = AlarmTextUsingFlag;
	//		memcpy(CimInfo::AlarmBlock[CimInfo::m_nAlarmReportCount].AlarmText, CimInfo::AlarmBlockReserve[0].AlarmText, sizeof(CimInfo::AlarmBlockReserve[0].AlarmText));
	//		CimInfo::m_nAlarmReportCount++;

	//		CimInfo::m_nAlarmPos[nAlarmID] = 4; //KJT 20210407

	//		LWWrite(ALARM_REPORT_BLOCK_4_START_ADDRESS, &CimInfo::AlarmReportBlock[nAlarmID], sizeof(LW_LTM_ALARM_BLOCK));
	//		CimInfo::m_LBLTM.MachineEvent_Alarm_5Report = TRUE;
	//		Str.Format(_T(">> MachineEvent_Alarm_5Report TRUE (Reserved AlarmID:%d)"), nAlarmID);
	//		Etc_Msg(Str);

	//		LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	//		SetAlarmT1TimeOut(4); //KJT 20210407

	//		CimInfo::m_AlarmMaxPos++;
	//		if (CimInfo::m_AlarmMaxPos > 5)
	//			CimInfo::m_AlarmMaxPos = 1;

	//		CimInfo::m_nAlarmReserveCount--;
	//		if (CimInfo::m_nAlarmReserveCount < 0)
	//			CimInfo::m_nAlarmReserveCount = 0;
	//		
	//		Str.Format(_T("m_nAlarmReserveCount %d"), CimInfo::m_nAlarmReserveCount);
	//		Etc_Msg(Str);

	//		for (int i = 0; i < CimInfo::m_nAlarmReserveCount; i++)
	//		{
	//			CimInfo::AlarmOccuredTimeReserve[i] = CimInfo::AlarmOccuredTimeReserve[i + 1];
	//			CimInfo::AlarmBlockReserve[i].AlarmStatus = CimInfo::AlarmBlockReserve[i + 1].AlarmStatus;
	//			CimInfo::AlarmBlockReserve[i].AlarmUnitNumber = CimInfo::AlarmBlockReserve[i + 1].AlarmUnitNumber;
	//			CimInfo::AlarmBlockReserve[i].AlarmID = CimInfo::AlarmBlockReserve[i + 1].AlarmID;
	//			CimInfo::AlarmBlockReserve[i].AlarmCode = CimInfo::AlarmBlockReserve[i + 1].AlarmCode;
	//			CimInfo::AlarmBlockReserve[i].AlarmType = CimInfo::AlarmBlockReserve[i + 1].AlarmType;
	//			memcpy(CimInfo::AlarmBlockReserve[i].AlarmText, CimInfo::AlarmBlockReserve[i + 1].AlarmText, sizeof(CimInfo::AlarmBlockReserve[i].AlarmText));
	//		}
	//	}
	//}
}
BOOL CCimModule::IsAlarmT1TimeOut(int AlarmArea)
{
	double dLapse = 0.0;
	LARGE_INTEGER freq, start, end;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);
	dLapse = ((start.QuadPart) / (double)freq.QuadPart) * 1000; //msec
	if (CimInfo::m_AlarmT1TimerCheck[AlarmArea] == 0)
		return FALSE;

	if (dLapse - CimInfo::m_AlarmT1TimerCheck[AlarmArea] == 0)
		return  FALSE;
	else if (dLapse - CimInfo::m_AlarmT1TimerCheck[AlarmArea] > CimInfo::m_T1Timer)
	{

		return  TRUE;
	}
	else
		return  FALSE;

}
void CCimModule::SetAlarmT1TimeOut(int AlarmArea)
{
	double dLapse = 0.0;
	LARGE_INTEGER freq, start, end;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);
	dLapse = ((start.QuadPart) / (double)freq.QuadPart) * 1000; //msec
	CimInfo::m_AlarmT1TimerCheck[AlarmArea] = dLapse;
}
void CCimModule::ClearAlarmT1TimeOut(int AlarmArea)
{
	CimInfo::m_AlarmT1TimerCheck[AlarmArea] = 0;
}
#pragma endregion

BOOL CCimModule::IsT2TimeOut()
{
	double dLapse = 0.0;
	LARGE_INTEGER freq, start, end;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);
	dLapse = ((start.QuadPart) / (double)freq.QuadPart) * 1000; //msec
	DWORD dwCheckTick = (DWORD)(FLOAT)dLapse;

	if (CimInfo::m_T2TimerCheck == 0)
		return FALSE;

	if (dwCheckTick - CimInfo::m_T2TimerCheck == 0)
		return  FALSE;
	else if (dwCheckTick - CimInfo::m_T2TimerCheck > CimInfo::m_T2Timer)
	{

		return  TRUE;
	}
	else
		return  FALSE;

}


void CCimModule::SetT2TimeOut()
{
	double dLapse = 0.0;
	LARGE_INTEGER freq, start, end;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);
	dLapse = ((start.QuadPart) / (double)freq.QuadPart) * 1000; //msec
	CimInfo::m_T2TimerCheck = (DWORD)(FLOAT)dLapse;
}
void CCimModule::ClearT2TimeOut()
{
	CimInfo::m_T2TimerCheck = 0;
}
BOOL CCimModule::IsT3TimeOut()
{
	double dLapse = 0.0;
	LARGE_INTEGER freq, start, end;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);
	dLapse = ((start.QuadPart) / (double)freq.QuadPart) * 1000; //msec
	DWORD dwCheckTick = (DWORD)(FLOAT)dLapse;

	if (CimInfo::m_T3TimerCheck == 0)
		return FALSE;

	if (dwCheckTick - CimInfo::m_T3TimerCheck == 0)
		return  FALSE;
	else if (dwCheckTick - CimInfo::m_T3TimerCheck > CimInfo::m_T3Timer)
	{

		return  TRUE;
	}
	else
		return  FALSE;

}
void CCimModule::SetT3TimeOut()
{
	double dLapse = 0.0;
	LARGE_INTEGER freq, start, end;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);
	dLapse = ((start.QuadPart) / (double)freq.QuadPart) * 1000; //msec
	CimInfo::m_T3TimerCheck = (DWORD)(FLOAT)dLapse;
}
void CCimModule::ClearT3TimeOut()
{
	CimInfo::m_T3TimerCheck = 0;
}
BOOL CCimModule::IsCommonTimeOut()
{
	double dLapse = 0.0;
	LARGE_INTEGER freq, start, end;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);
	dLapse = ((start.QuadPart) / (double)freq.QuadPart) * 1000; //msec
	DWORD dwCheckTick = (DWORD)(FLOAT)dLapse;

	if (CimInfo::m_CommonTimerCheck == 0)
		return FALSE;

	if (dwCheckTick - CimInfo::m_CommonTimerCheck == 0)
		return  FALSE;
	else if (dwCheckTick - CimInfo::m_CommonTimerCheck > CimInfo::m_CommonTimer)
	{

		return  TRUE;
	}
	else
		return  FALSE;

}


BOOL CCimModule::IsCVTimeOut()
{
	double dLapse = 0.0;
	LARGE_INTEGER freq, start, end;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);
	dLapse = ((start.QuadPart) / (double)freq.QuadPart) * 1000; //msec
	DWORD dwCheckTick = (DWORD)(FLOAT)dLapse;

	if (CimInfo::m_CVTimerCheck == 0)
		return FALSE;

	if (dwCheckTick - CimInfo::m_CVTimerCheck == 0)
		return  FALSE;
	else if (dwCheckTick - CimInfo::m_CVTimerCheck > CimInfo::m_CVTimer)
	{

		return  TRUE;
	}
	else
		return  FALSE;

}
void CCimModule::SetCVTimeOut()
{
	double dLapse = 0.0;
	LARGE_INTEGER freq, start, end;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);
	dLapse = ((start.QuadPart) / (double)freq.QuadPart) * 1000; //msec
	CimInfo::m_CVTimerCheck = (DWORD)(FLOAT)dLapse;
}
void CCimModule::ClearCVTimeOut()
{
	CimInfo::m_CVTimerCheck = 0;
}
void CCimModule::SetCommonTimeOut(DWORD TimoOutValue)
{
	double dLapse = 0.0;
	LARGE_INTEGER freq, start, end;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);
	dLapse = ((start.QuadPart) / (double)freq.QuadPart) * 1000; //msec
	CimInfo::m_CommonTimer = TimoOutValue;
	CimInfo::m_CommonTimerCheck = (DWORD)(FLOAT)dLapse;
}
void CCimModule::ClearCommonTimeOut()
{
	CimInfo::m_CommonTimerCheck = 0;
}
//KJT 20210407
void CCimModule::CIMAlarmMessage(WORD AlarmState, WORD AlarmUnit, WORD AlarmCode, WORD AlarmType, WORD AlarmTextUsingFlag, WORD AlarmID, const TCHAR* AlarmText)
{
	//CString Str = _T("");
	////KJT 20210324
	//if (CimInfo::m_AlarmMaxPos > 5)
	//{
	//	CimInfo::m_AlarmMaxPos = 1;
	//}

	//if (AlarmID < 1)
	//	AlarmID = 1;
	//if (AlarmID > 65500)
	//	AlarmID = 65500;

	//if (CimInfo::m_LBLTM.MachineEvent_Alarm_1Report == FALSE || CimInfo::m_LBLTM.MachineEvent_Alarm_2Report == FALSE || CimInfo::m_LBLTM.MachineEvent_Alarm_3Report == FALSE ||
	//	CimInfo::m_LBLTM.MachineEvent_Alarm_4Report == FALSE || CimInfo::m_LBLTM.MachineEvent_Alarm_5Report == FALSE)
	//{
	//	CString szMsg = AlarmText;

	//	CimInfo::AlarmReportOccuredTime[AlarmID] = CTime::GetCurrentTime();
	//	CimInfo::AlarmReportBlock[AlarmID].AlarmStatus = AlarmState;
	//	CimInfo::AlarmReportBlock[AlarmID].AlarmUnitNumber = 1;
	//	CimInfo::AlarmReportBlock[AlarmID].AlarmID = AlarmID;
	//	CimInfo::AlarmReportBlock[AlarmID].AlarmCode = AlarmCode;
	//	CimInfo::AlarmReportBlock[AlarmID].AlarmType = AlarmType;
	//	strcpy_s((char*)CimInfo::AlarmReportBlock[AlarmID].AlarmText, szMsg.GetLength() + 1, CT2A(szMsg));

	//	//KJT 20210412
	//	CimInfo::AlarmOccuredTime[CimInfo::m_nAlarmReportCount] = CimInfo::AlarmReportOccuredTime[AlarmID]; //
	//	CimInfo::AlarmBlock[CimInfo::m_nAlarmReportCount].AlarmStatus = AlarmState;
	//	CimInfo::AlarmBlock[CimInfo::m_nAlarmReportCount].AlarmUnitNumber = 1;
	//	CimInfo::AlarmBlock[CimInfo::m_nAlarmReportCount].AlarmID = AlarmID;
	//	CimInfo::AlarmBlock[CimInfo::m_nAlarmReportCount].AlarmCode = AlarmCode;
	//	CimInfo::AlarmBlock[CimInfo::m_nAlarmReportCount].AlarmType = AlarmType;
	//	//CimInfo::AlarmBlock[CimInfo::m_nAlarmReportCount].AlarmTextUsingFlag = AlarmTextUsingFlag;
	//	strcpy_s((char*)CimInfo::AlarmBlock[CimInfo::m_nAlarmReportCount].AlarmText, szMsg.GetLength() + 1, CT2A(szMsg));
	//	CimInfo::m_nAlarmReportCount++;

	//	CimInfo::m_nAlarmPos[AlarmID] = CimInfo::m_AlarmMaxPos; //KJT 20210407

	//	Alarm_Msg(szMsg);

	//	switch (CimInfo::m_AlarmMaxPos) //KJT 20210406
	//	{
	//	case 1:
	//		LWWrite(ALARM_REPORT_BLOCK_1_START_ADDRESS, &CimInfo::AlarmReportBlock[AlarmID], sizeof(LW_LTM_ALARM_BLOCK));
	//		CimInfo::m_LBLTM.MachineEvent_Alarm_1Report = TRUE;
	//		Str.Format(_T(">> MachineEvent_Alarm_1Report TRUE (AlarmID:%d)"), AlarmID);;
	//		Etc_Msg(Str);
	//		break;
	//	case 2:
	//		LWWrite(ALARM_REPORT_BLOCK_2_START_ADDRESS, &CimInfo::AlarmReportBlock[AlarmID], sizeof(LW_LTM_ALARM_BLOCK));
	//		CimInfo::m_LBLTM.MachineEvent_Alarm_2Report = TRUE;
	//		Str.Format(_T(">> MachineEvent_Alarm_2Report TRUE (AlarmID:%d)"), AlarmID);;
	//		Etc_Msg(Str);
	//		break;
	//	case 3:
	//		LWWrite(ALARM_REPORT_BLOCK_3_START_ADDRESS, &CimInfo::AlarmReportBlock[AlarmID], sizeof(LW_LTM_ALARM_BLOCK));
	//		CimInfo::m_LBLTM.MachineEvent_Alarm_3Report = TRUE;
	//		Str.Format(_T(">> MachineEvent_Alarm_3Report TRUE (AlarmID:%d)"), AlarmID);;
	//		Etc_Msg(Str);
	//		break;
	//	case 4:
	//		LWWrite(ALARM_REPORT_BLOCK_4_START_ADDRESS, &CimInfo::AlarmReportBlock[AlarmID], sizeof(LW_LTM_ALARM_BLOCK));
	//		CimInfo::m_LBLTM.MachineEvent_Alarm_4Report = TRUE;
	//		Str.Format(_T(">> MachineEvent_Alarm_4Report TRUE (AlarmID:%d)"), AlarmID);;
	//		Etc_Msg(Str);
	//		break;
	//	case 5:
	//		LWWrite(ALARM_REPORT_BLOCK_5_START_ADDRESS, &CimInfo::AlarmReportBlock[AlarmID], sizeof(LW_LTM_ALARM_BLOCK));
	//		CimInfo::m_LBLTM.MachineEvent_Alarm_5Report = TRUE;
	//		Str.Format(_T(">> MachineEvent_Alarm_5Report TRUE (AlarmID:%d)"), AlarmID);;
	//		Etc_Msg(Str);
	//		break;
	//	}
	//	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	//	SetAlarmT1TimeOut(CimInfo::m_AlarmMaxPos - 1); //KJT 20210407

	//	CimInfo::m_AlarmMaxPos++;
	//}
	//else
	//{
	//	if (CimInfo::m_nAlarmReserveCount < 100)
	//	{
	//		CString szMsg = AlarmText;
	//		CimInfo::AlarmOccuredTimeReserve[CimInfo::m_nAlarmReserveCount] = CTime::GetCurrentTime();
	//		CimInfo::AlarmBlockReserve[CimInfo::m_nAlarmReserveCount].AlarmStatus = AlarmState;
	//		CimInfo::AlarmBlockReserve[CimInfo::m_nAlarmReserveCount].AlarmUnitNumber = 1;
	//		CimInfo::AlarmBlockReserve[CimInfo::m_nAlarmReserveCount].AlarmID = AlarmID;
	//		CimInfo::AlarmBlockReserve[CimInfo::m_nAlarmReserveCount].AlarmCode = AlarmCode;
	//		CimInfo::AlarmBlockReserve[CimInfo::m_nAlarmReserveCount].AlarmType = AlarmType;
	//		//CimInfo::AlarmBlockReserve[CimInfo::m_AlarmMaxPos].AlarmTextUsingFlag = AlarmTextUsingFlag;
	//		strcpy_s((char*)CimInfo::AlarmBlockReserve[CimInfo::m_nAlarmReserveCount].AlarmText, szMsg.GetLength() + 1, CT2A(szMsg));

	//		CimInfo::m_nAlarmReserveCount++;
	//		
	//		CString Str = _T("");
	//		Str.Format(_T("Set AlarmBlockReserve AlarmID:%d, m_nAlarmReserveCount:%d"), AlarmID, CimInfo::m_nAlarmReserveCount);
	//		Etc_Msg(Str);
	//	}
	//}
}

BOOL CCimModule::IsTowerLampTimeOut()
{
	double dLapse = 0.0;
	LARGE_INTEGER freq, start, end;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);
	dLapse = ((start.QuadPart) / (double)freq.QuadPart) * 1000; //msec
	DWORD dwCheckTick = (DWORD)(FLOAT)dLapse;

	if (CimInfo::m_TowerLampTimerCheck == 0)
		return FALSE;

	if (dwCheckTick - CimInfo::m_TowerLampTimerCheck == 0)
		return  FALSE;
	else if (dwCheckTick - CimInfo::m_TowerLampTimerCheck > CimInfo::m_TowerLampTimer)
	{

		return  TRUE;
	}
	else
		return  FALSE;

}
void CCimModule::SetTowerLampTimeOut(DWORD TimoOutValue)
{
	double dLapse = 0.0;
	LARGE_INTEGER freq, start, end;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);
	dLapse = ((start.QuadPart) / (double)freq.QuadPart) * 1000; //msec
	CimInfo::m_TowerLampTimer = TimoOutValue;
	CimInfo::m_TowerLampTimerCheck = (DWORD)(FLOAT)dLapse;
}

void CCimModule::ClearTowerLampTimeOut()
{
	CimInfo::m_TowerLampTimerCheck = 0;
}

BOOL CCimModule::IsCIMPCOffStatusTimeOut()
{
	double dLapse = 0.0;
	LARGE_INTEGER freq, start, end;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);
	dLapse = ((start.QuadPart) / (double)freq.QuadPart) * 1000; //msec
	DWORD dwCheckTick = (DWORD)(FLOAT)dLapse;

	if (CimInfo::m_CIMPCOffStatusTimerCheck == 0)
		return FALSE;

	if (dwCheckTick - CimInfo::m_CIMPCOffStatusTimerCheck == 0)
		return  FALSE;
	else if (dwCheckTick - CimInfo::m_CIMPCOffStatusTimerCheck > CimInfo::m_CIMPCOffStatusTimer)
	{

		return  TRUE;
	}
	else
		return  FALSE;

}
void CCimModule::SetCIMPCOffStatusTimeOut(DWORD TimoOutValue)
{
	double dLapse = 0.0;
	LARGE_INTEGER freq, start, end;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);
	dLapse = ((start.QuadPart) / (double)freq.QuadPart) * 1000; //msec
	CimInfo::m_CIMPCOffStatusTimer = TimoOutValue;
	CimInfo::m_CIMPCOffStatusTimerCheck = (DWORD)(FLOAT)dLapse;
}

void CCimModule::ClearCIMPCOffStatusTimeOut()
{
	CimInfo::m_CIMPCOffStatusTimerCheck = 0;
}

BOOL CCimModule::IsCIMPCOnStatusTimeOut()
{
	double dLapse = 0.0;
	LARGE_INTEGER freq, start, end;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);
	dLapse = ((start.QuadPart) / (double)freq.QuadPart) * 1000; //msec
	DWORD dwCheckTick = (DWORD)(FLOAT)dLapse;

	if (CimInfo::m_CIMPCOnStatusTimerCheck == 0)
		return FALSE;

	if (dwCheckTick - CimInfo::m_CIMPCOnStatusTimerCheck == 0)
		return  FALSE;
	else if (dwCheckTick - CimInfo::m_CIMPCOnStatusTimerCheck > CimInfo::m_CIMPCOnStatusTimer)
	{

		return  TRUE;
	}
	else
		return  FALSE;

}
void CCimModule::SetCIMPCOnStatusTimeOut(DWORD TimoOutValue)
{
	double dLapse = 0.0;
	LARGE_INTEGER freq, start, end;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&start);
	dLapse = ((start.QuadPart) / (double)freq.QuadPart) * 1000; //msec
	CimInfo::m_CIMPCOnStatusTimer = TimoOutValue;
	CimInfo::m_CIMPCOnStatusTimerCheck = (DWORD)(FLOAT)dLapse;
}

void CCimModule::ClearCIMPCOnStatusTimeOut()
{
	CimInfo::m_CIMPCOnStatusTimerCheck = 0;
}
void	CCimModule::CIMAlarmResetMessage(WORD AlarmID)//KJT 20210407
{
	CString Str = _T("");
	CimInfo::m_AlarmCmdPos = AlarmID;
	//CimInfo::AlarmReportBlock[AlarmID].AlarmStatus = ALARM_STATE_CLEAR;
	
	//CimInfo::m_LBLTM.bMachineEventAlarmStateChangeReport = TRUE;
	//switch (CimInfo::m_AlarmMaxPos)
	//switch (CimInfo::m_nAlarmPos[AlarmID]) //KJT 20210407
	//{
	//case 1:
	//	LWWrite(ALARM_REPORT_BLOCK_1_START_ADDRESS/* + sizeof(CimInfo::AlarmBlock)*0*/, &CimInfo::AlarmReportBlock[AlarmID], sizeof(LW_LTM_ALARM_BLOCK));
	//	CimInfo::m_LBLTM.MachineEvent_Alarm_1Report = TRUE;
	//	Str.Format(_T(">> Alarm Reset. MachineEvent_Alarm_1Report TRUE (AlarmID:%d)"), AlarmID);
	//	Etc_Msg(Str);
	//	break;
	//case 2:
	//	LWWrite(ALARM_REPORT_BLOCK_2_START_ADDRESS/* + sizeof(CimInfo::AlarmBlock)*1 */, &CimInfo::AlarmReportBlock[AlarmID], sizeof(LW_LTM_ALARM_BLOCK));
	//	CimInfo::m_LBLTM.MachineEvent_Alarm_2Report = TRUE;
	//	Str.Format(_T(">> Alarm Reset. MachineEvent_Alarm_2Report TRUE (AlarmID:%d)"), AlarmID);
	//	Etc_Msg(Str);
	//	break;
	//case 3:
	//	LWWrite(ALARM_REPORT_BLOCK_3_START_ADDRESS/* + sizeof(CimInfo::AlarmBlock)*2 */, &CimInfo::AlarmReportBlock[AlarmID], sizeof(LW_LTM_ALARM_BLOCK));
	//	CimInfo::m_LBLTM.MachineEvent_Alarm_3Report = TRUE;
	//	Str.Format(_T(">> Alarm Reset. MachineEvent_Alarm_3Report TRUE (AlarmID:%d)"), AlarmID);
	//	Etc_Msg(Str);
	//	break;
	//case 4:
	//	LWWrite(ALARM_REPORT_BLOCK_4_START_ADDRESS/* + sizeof(CimInfo::AlarmBlock)*3 */, &CimInfo::AlarmReportBlock[AlarmID], sizeof(LW_LTM_ALARM_BLOCK));
	//	CimInfo::m_LBLTM.MachineEvent_Alarm_4Report = TRUE;
	//	Str.Format(_T(">> Alarm Reset. MachineEvent_Alarm_4Report TRUE (AlarmID:%d)"), AlarmID);
	//	Etc_Msg(Str);
	//	break;
	//case 5:
	//	LWWrite(ALARM_REPORT_BLOCK_5_START_ADDRESS/* + sizeof(CimInfo::AlarmBlock)*4 */, &CimInfo::AlarmReportBlock[AlarmID], sizeof(LW_LTM_ALARM_BLOCK));
	//	CimInfo::m_LBLTM.MachineEvent_Alarm_5Report = TRUE;
	//	Str.Format(_T(">> Alarm Reset. MachineEvent_Alarm_5Report TRUE (AlarmID:%d)"), AlarmID);
	//	Etc_Msg(Str);
	//	break;
	//}
	
	//CimInfo::m_AlarmCount--;
	//memset(&CimInfo::AlarmBlock[AlarmID], 0x0, sizeof(CimInfo::AlarmBlock[AlarmID]));
	CimInfo::m_AlarmMaxPos--;
	if (CimInfo::m_AlarmMaxPos < 1)
		CimInfo::m_AlarmMaxPos = 1;

	//CimInfo::m_nCmd = eALARM_RESET;

	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	//SetAlarmT1TimeOut(CimInfo::m_nAlarmPos[AlarmID] - 1);
	//CimInfo::m_nAlarmPos[AlarmID] = 0;
}

void	CCimModule::CIMAlarmAllResetMessage()
{
	//memset(CimInfo::AlarmBlock, 0, sizeof(CimInfo::AlarmBlock));
	//CimInfo::m_AlarmCount = 0;
	//CimInfo::m_AlarmPos = 0;
	//CimInfo::m_AlarmAllClearFlag = TRUE;
	CimInfo::m_nCmd = eALARM_ALL_RESET;
	for (int i = 0; i < 5; i++)
	{
		//LWWrite(ALARM_REPORT_BLOCK_1_START_ADDRESS + sizeof(CimInfo::AlarmBlock)*i, &CimInfo::AlarmBlock, sizeof(CimInfo::AlarmBlock));
	}
	CimInfo::m_LBLTM.MachineEvent_Alarm_1Report = FALSE;
	CimInfo::m_LBLTM.MachineEvent_Alarm_2Report = FALSE;
	CimInfo::m_LBLTM.MachineEvent_Alarm_3Report = FALSE;
	CimInfo::m_LBLTM.MachineEvent_Alarm_4Report = FALSE;
	CimInfo::m_LBLTM.MachineEvent_Alarm_5Report = FALSE;
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));


}

int CCimModule::PPIDCheck(MASK_JOB_DATA JobData)
{
	WORD CurrentRecipeID = 0;
	CurrentRecipeID = SharedInfo::Active.nActiveRecipeNum;
	if (CurrentRecipeID != JobData.MaskJobDataBlock.Mask_PPID02_2 || JobData.MaskJobDataBlock.Mask_PPID02_1 != 0x0)
	{
		return -1;
	}
	else
		return JobData.MaskJobDataBlock.Mask_PPID02_2;
}

char* CCimModule::FindModelName(WORD wRecipeID)
{
	CString szMsg;
	for (int i = 0; i < 999; i++)
	{
		if (CimInfo::m_MachineRecipeTable.wRecipeID[i] == wRecipeID)
		{
			return CimInfo::m_MachineRecipeTable.strRecipeName[i];
		}
	}
	return NULL;
}

BOOL CCimModule::SetLbLtmSelectedEventRun()
{
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));

	return TRUE;
}
BOOL CCimModule::ReportCurrentRecipeNumberChangeBlock(CURRENT_RECIPE_NUMBER_CHANGE_REPORT_BLOCK MachineRecipeBlock)
{
#if 1
	LWWrite(CURRENT_RECIPE_NUMBER_CHANGE_REPORT_BLOCK_START_ADDRESS, &MachineRecipeBlock, sizeof(CURRENT_RECIPE_NUMBER_CHANGE_REPORT_BLOCK));
	CimInfo::m_LBLTM.MachineEvent_CurrentRecipeNumberChangeReport = TRUE;
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	SetT1TimeOut(); //KJT 20210408
#endif
	return TRUE;
}
BOOL CCimModule::ReportRecipeChangeBlock(RECIPE_CHANGE_REPORT_BLOCK MachineRecipeBlock)
{
#if 1
	CimInfo::RecipeChangeReportBlockCnt++;
	if (CimInfo::RecipeChangeReportBlockCnt == 6)
		CimInfo::RecipeChangeReportBlockCnt = 1;
	memcpy(&CimInfo::RecipeChangeReportBlockBuffer[CimInfo::RecipeChangeReportBlockCnt -1], &MachineRecipeBlock, sizeof(MachineRecipeBlock));




	////SetT1TimeOut();
#endif
	return TRUE;
}


BOOL CCimModule::ReportRecipeListChangeBlock(RECIPE_LAYER_INFO_REQUEST_REPLY_BLOCK MachineRecipeBlock)
{
#if 1
	LWWrite(RECIPE_LAYER_INFO_REQUEST_REPLY_BLOCK_START_ADDRESS, &MachineRecipeBlock, sizeof(RECIPE_LAYER_INFO_REQUEST_REPLY_BLOCK));
	CimInfo::m_LBLTM.MachineEvent_RecipeChangeReport = TRUE;
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	SetT1TimeOut();
#endif
	return TRUE;
}



BOOL CCimModule::ReportCurrentRecipeBlock(PLW_LTM_CURRENT_RECIPE_BLOCK CurrentRecipeBlock)
{
	LWWrite(CURRENT_RECIPE_BLOCK_START_ADDRESS, CurrentRecipeBlock, sizeof(LW_LTM_CURRENT_RECIPE_BLOCK));
	CimInfo::m_LBLTM.MachineEvent_CurrentRecipeNumberChangeReport= TRUE;
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	SetT1TimeOut();

	return TRUE;
}

BOOL CCimModule::ReportMaterialCountBlock(PMATERIAL_COUNT_CHANGE_REPORT_BLOCK MaterialCountChangeBlock)
{

	LWWrite(MATERIAL_COUNT_MACHINE_BLOCK_START_ADDRESS, MaterialCountChangeBlock, sizeof(MATERIAL_COUNT_CHANGE_REPORT_BLOCK));
	CimInfo::m_LBLTM.MachineMaterialEvent_MaterialCountChangeReport = TRUE;
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	SetT1TimeOut();

	return TRUE;
}
BOOL CCimModule::ReportMagazineProcessCompleteBlock_1(MAGAZINE_PROCESS_COMPLETE_REPORT_BLOCK MagazineProcessCompleteBlock, MAGAZINE_PROCESS_COMPLETE_REPORT_SUBBLOCK MagazineProcessCompleteSubBlock)
{
	LWWrite(MAGAZINE_PROCESS_COMPLETE_REOPRT_SUB_BLOCK, &MagazineProcessCompleteSubBlock, sizeof(MagazineProcessCompleteSubBlock));
	LWWrite(MAGAZINE_PROCESS_COMPLETE_REOPRT_BLOCK_1_START_ADDRESS, &MagazineProcessCompleteBlock, sizeof(MAGAZINE_PROCESS_COMPLETE_REPORT_BLOCK));
	CimInfo::m_LBLTM.MachineMaterialEvent_MagazineProcessCompleteReport = TRUE;
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	SetT1TimeOut();

	return TRUE;

}

BOOL CCimModule::ReportMagazineProcessCompleteBlock_2(MAGAZINE_PROCESS_COMPLETE_REPORT_BLOCK MagazineProcessCompleteBlock, MAGAZINE_PROCESS_COMPLETE_REPORT_SUBBLOCK MagazineProcessCompleteSubBlock)
{
	LWWrite(MAGAZINE_PROCESS_COMPLETE_REOPRT_SUB_BLOCK, &MagazineProcessCompleteSubBlock, sizeof(MagazineProcessCompleteSubBlock));
	LWWrite(MAGAZINE_PROCESS_COMPLETE_REOPRT_BLOCK_2_START_ADDRESS, &MagazineProcessCompleteBlock, sizeof(MAGAZINE_PROCESS_COMPLETE_REPORT_BLOCK));
	CimInfo::m_LBLTM.MachineMaterialEvent_MagazineProcessCompleteReport = TRUE;
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	SetT1TimeOut();

	return TRUE;

}

BOOL CCimModule::ReportMagazineProcessCompleteBlock_3(MAGAZINE_PROCESS_COMPLETE_REPORT_BLOCK MagazineProcessCompleteBlock, MAGAZINE_PROCESS_COMPLETE_REPORT_SUBBLOCK MagazineProcessCompleteSubBlock)
{
	LWWrite(MAGAZINE_PROCESS_COMPLETE_REOPRT_SUB_BLOCK, &MagazineProcessCompleteSubBlock, sizeof(MagazineProcessCompleteSubBlock));
	LWWrite(MAGAZINE_PROCESS_COMPLETE_REOPRT_BLOCK_3_START_ADDRESS, &MagazineProcessCompleteBlock, sizeof(MAGAZINE_PROCESS_COMPLETE_REPORT_BLOCK));
	CimInfo::m_LBLTM.MachineMaterialEvent_MagazineProcessCompleteReport = TRUE;
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	SetT1TimeOut();

	return TRUE;

}

BOOL CCimModule::ReportMagazineProcessCompleteBlock_4(MAGAZINE_PROCESS_COMPLETE_REPORT_BLOCK MagazineProcessCompleteBlock, MAGAZINE_PROCESS_COMPLETE_REPORT_SUBBLOCK MagazineProcessCompleteSubBlock)
{
	LWWrite(MAGAZINE_PROCESS_COMPLETE_REOPRT_SUB_BLOCK, &MagazineProcessCompleteSubBlock, sizeof(MagazineProcessCompleteSubBlock));
	LWWrite(MAGAZINE_PROCESS_COMPLETE_REOPRT_BLOCK_4_START_ADDRESS, &MagazineProcessCompleteBlock, sizeof(MAGAZINE_PROCESS_COMPLETE_REPORT_BLOCK));
	CimInfo::m_LBLTM.MachineMaterialEvent_MagazineProcessCompleteReport = TRUE;
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	SetT1TimeOut();

	return TRUE;

}

BOOL CCimModule::ReportMagazineProcessCompleteBlock_5(MAGAZINE_PROCESS_COMPLETE_REPORT_BLOCK MagazineProcessCompleteBlock, MAGAZINE_PROCESS_COMPLETE_REPORT_SUBBLOCK MagazineProcessCompleteSubBlock)
{
	LWWrite(MAGAZINE_PROCESS_COMPLETE_REOPRT_SUB_BLOCK, &MagazineProcessCompleteSubBlock, sizeof(MagazineProcessCompleteSubBlock));
	LWWrite(MAGAZINE_PROCESS_COMPLETE_REOPRT_BLOCK_5_START_ADDRESS, &MagazineProcessCompleteBlock, sizeof(MAGAZINE_PROCESS_COMPLETE_REPORT_BLOCK));
	CimInfo::m_LBLTM.MachineMaterialEvent_MagazineProcessCompleteReport = TRUE;
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	SetT1TimeOut();

	return TRUE;

}

BOOL CCimModule::ReportMagazineProcessCompleteBlock_6(MAGAZINE_PROCESS_COMPLETE_REPORT_BLOCK MagazineProcessCompleteBlock, MAGAZINE_PROCESS_COMPLETE_REPORT_SUBBLOCK MagazineProcessCompleteSubBlock)
{
	
	LWWrite(MAGAZINE_PROCESS_COMPLETE_REOPRT_SUB_BLOCK, &MagazineProcessCompleteSubBlock, sizeof(MagazineProcessCompleteSubBlock));

	LWWrite(MAGAZINE_PROCESS_COMPLETE_REOPRT_BLOCK_6_START_ADDRESS, &MagazineProcessCompleteBlock, sizeof(MAGAZINE_PROCESS_COMPLETE_REPORT_BLOCK));
	CimInfo::m_LBLTM.MachineMaterialEvent_MagazineProcessCompleteReport = TRUE;
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	SetT1TimeOut();

	return TRUE;

}

BOOL CCimModule::ReportMagazineDataRequestBlock(MAGAZINE_DATA_REQUEST_BLOCK MagazineRequestDataBlock) //KJT 20210325
{

	//LWWrite(MAGAZINE_PROCESS_COMPLETE_REOPRT_BLOCK_1_START_ADDRESS, &MagazineRequestDataBlock, sizeof(MAGAZINE_DATA_REQUEST_BLOCK));
	LWWrite(MAGAZINE_DATA_REQUESET_ADDRESS, &MagazineRequestDataBlock, sizeof(MAGAZINE_DATA_REQUEST_BLOCK)); //KJT 20210409
	CimInfo::m_LBLTM.MachineMaterialEvent_MagazineDataRequest = TRUE;
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	SetT1TimeOut();

	return TRUE;

}
BOOL CCimModule::ReportMaterialStatusBlock(PMATERIAL_STATUS_CHANGE_REPORT_BLOCK MaterialStatus)
{
	LWWrite(MATERIAL_STATUS_BLOCK_START_ADDRESS, MaterialStatus, sizeof(MATERIAL_STATUS_CHANGE_REPORT_BLOCK));
	CimInfo::m_LBLTM.MachineMaterialEvent_MaterialStatusChangeReport = TRUE;
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	SetT1TimeOut();

	return TRUE;
}

BOOL CCimModule::ReportSheetMoveInBlock(SHEET_MOVE_IN_REPORT_BLOCK SheetMoveInBlock)
{
	SheetMoveInBlock.UnitNumber = 1;
	LWWrite(SHEET_MOVE_IN_START_ADDRESS, &SheetMoveInBlock, sizeof(SHEET_MOVE_IN_REPORT_BLOCK));
	CimInfo::m_LBLTM.MachineMaterialEvent_SheetMoveInReport = TRUE;
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	SetT1TimeOut();

	return TRUE;
}

BOOL CCimModule::ReportSheetMoveOutBlock(SHEET_MOVE_OUT_REPORT_BLOCK SheetMoveOutBlock)
{
	SheetMoveOutBlock.UnitNumber = 1;
	LWWrite(SHEET_MOVE_OUT_START_ADDRESS, &SheetMoveOutBlock, sizeof(SHEET_MOVE_OUT_REPORT_BLOCK));
	CimInfo::m_LBLTM.MachineMaterialEvent_SheetMoveOutReport = TRUE;
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	SetT1TimeOut();

	return TRUE;
}

BOOL CCimModule::RequestSheetInformation(PSHEET_INFORMATION_BLOCK SheetInformationRequestBlock)
{
	LWWrite(SHEET_INFORMATION_REQUEST_START_ADDRESS, SheetInformationRequestBlock, sizeof(SHEET_INFORMATION_BLOCK));
	CimInfo::m_LBLTM.MachineMaterialEvent_MaterialSheetDataDownloadRequest = TRUE;
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	//SetT1TimeOut();

	return TRUE;
}

BOOL CCimModule::UpdateSheetInformation(METERIAL_SHEET_DATA_UPDATE_REPORT_BLOCK SheetInfo)
{
	LWWrite(METERIAL_SHEET_DATA_UPDATE_START_ADDRESS, &SheetInfo, sizeof(METERIAL_SHEET_DATA_UPDATE_REPORT_BLOCK));
	CimInfo::m_LBLTM.MachineMaterialEvent_MaterialSheetDataUpdateReport = TRUE;
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	//SetT1TimeOut();

	return TRUE;
}

BOOL CCimModule::DownloadSheetInformation(MATERIAL_SHEET_DATA_DOWNLOAD_REQUEST_BLOCK SheetInfo)
{
	LWWrite(METERIAL_SHEET_DATA_DOWNLOAD_START_ADDRESS, &SheetInfo, sizeof(MATERIAL_SHEET_DATA_DOWNLOAD_REQUEST_BLOCK));
	CimInfo::m_LBLTM.MachineMaterialEvent_MaterialSheetDataDownloadRequest = TRUE;
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	SetT1TimeOut(); //KJT 20210409

	return TRUE;
}

BOOL CCimModule::MaskLoadRequestBlock(MASK_LOAD_REQUEST_BLOCK MaskLoadRequest)
{
	LWWrite(MASK_LOAD_REQUEST_BLOCK_START_ADDRESS, &MaskLoadRequest, sizeof(MASK_LOAD_REQUEST_BLOCK));
	CimInfo::m_LBLTM.MachineMaskEvent_MaskLoadRequest = TRUE;
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	SetT1TimeOut();

	return TRUE;
}
BOOL CCimModule::MaskUnloadRequestBlock(MASK_UNLOAD_REQUEST_BLOCK MaskUnloadRequest) 
{
	LWWrite(MASK_UNLOAD_REQUEST_BLOCK_START_ADDRESS, &MaskUnloadRequest, sizeof(MASK_UNLOAD_REQUEST_BLOCK));
	CimInfo::m_LBLTM.MachineMaskEvent_MaskUnloadRequest= TRUE;
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	SetT1TimeOut();

	return TRUE;
}
BOOL CCimModule::MaskLoadCompleteBlock(MASK_LOAD_COMPLETED_REPORT_BLOCK MaskLoadComplete)
{
	LWWrite(MASK_LOAD_COMPLETE_REPORT_BLOCK_START_ADDRESS, &MaskLoadComplete, sizeof(MASK_LOAD_COMPLETED_REPORT_BLOCK));
	CimInfo::m_LBLTM.MachineMaskEvent_MaskLoadCompletedReport = TRUE;
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	SetT1TimeOut();

	return TRUE;
}
BOOL CCimModule::MaskUnoadCompleteBlock(MASK_UNLOAD_COMPLETED_REPORT_BLOCK MaskUnloadRequest) 
{
	LWWrite(MASK_UNLOAD_COMPLETE_REPORT_BLOCK_START_ADDRESS, &MaskUnloadRequest, sizeof(MASK_LOAD_COMPLETED_REPORT_BLOCK));
	CimInfo::m_LBLTM.MachineMaskEvent_MaskUnloadCompletedReport = TRUE;
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	SetT1TimeOut();

	return TRUE;
}


BOOL CCimModule::RemoveSheetInformation()
{
#if 0
	memset(&CimInfo::SheetInfo, 0x0, sizeof(SHEET_INFORMATION_BLOCK));
	CimInfo::m_LBLTM.bMachineEventSheetDataRemovedReport = TRUE;
	LWWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	//SetT1TimeOut();
#endif
	return TRUE;
}

BOOL CCimModule::SetCimModeOnOff(BOOL bOnOff)
{
	//KJT 20210324
	if (bOnOff)
	{
		DATE_TIME_REQUEST_BLOCK DateTimeRequestBlock;
		DateTimeRequestBlock.TouchPanelNumber = 1;
		//Devs::CimMotion.RequestDateTime(DateTimeRequestBlock);
	}

	CimInfo::m_LBLTM.MachineStatus_CIMModeBit = bOnOff;
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));

	return TRUE;
}
BOOL CCimModule::SetMachineAutoModeOnOff(BOOL bOnOff)
{
	SharedInfo::MachineAutoMode = bOnOff; //KJT 20210324
	CimInfo::m_LBLTM.MachineStatus_MachineAutoModeBit = bOnOff;
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));

	CString Str = _T("[CIM] Set Machine Auto Mode");
	Str.AppendFormat(_T(" %d"), bOnOff);
	Etc_Msg(Str);
	return TRUE;
}

BOOL CCimModule::ReportMachineStatusBlock(MACHINE_STATUS_CHANGE_REPORT_BLOCK MachineStatusBlock)
{
	LWWrite(MACHINE_STATUS_CHANGE_REPORT_BLOCK_START_ADDRESS, &MachineStatusBlock, sizeof(MACHINE_STATUS_CHANGE_REPORT_BLOCK));
	CimInfo::m_LBLTM.MachineEvent_MachineStatusChangeReport = TRUE;
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	//SetT1TimeOut();

	//KJT 20210407 Log
	CString Str = _T("[CIM] >> MACHINE_STATUS_CHANGE_REPORT ");
	switch (MachineStatusBlock.MachineStatus)
	{
	case eMACHINE_STATUS_PM:
		Str.AppendFormat(_T("MachineStatus:PM, "));
		break;
	case eMACHINE_STATUS_PAUSE:
		Str.AppendFormat(_T("MachineStatus:Pause, "));
		break;
	case eMACHINE_STATUS_RUN:
		Str.AppendFormat(_T("MachineStatus:Run, "));
		break;
	case eMACHINE_STATUS_IDLE:
		Str.AppendFormat(_T("MachineStatus:Idle, "));
		break;
	case eMACHINE_STATUS_BM:
		Str.AppendFormat(_T("MachineStatus:BM, "));
		break;
	case eMACHINE_STATUS_WARNING:
		Str.AppendFormat(_T("MachineStatus:Warning, "));
		break;
	case eMACHINE_STATUS_LAMP_OFF:
		Str.AppendFormat(_T("MachineStatus:LampOff, "));
		break;
	}
	Str.AppendFormat(_T("ReasonCode:%d, "), MachineStatusBlock.MachineStatusReasonCode);

	switch (MachineStatusBlock.Unit_1Status)
	{
	case eMACHINE_STATUS_PM:
		Str.AppendFormat(_T("Unit_1Status:PM"));
		break;
	case eMACHINE_STATUS_PAUSE:
		Str.AppendFormat(_T("Unit_1Status:Pause"));
		break;
	case eMACHINE_STATUS_RUN:
		Str.AppendFormat(_T("Unit_1Status:Run"));
		break;
	case eMACHINE_STATUS_IDLE:
		Str.AppendFormat(_T("Unit_1Status:Idle"));
		break;
	case eMACHINE_STATUS_BM:
		Str.AppendFormat(_T("Unit_1Status:BM"));
		break;
	case eMACHINE_STATUS_WARNING:
		Str.AppendFormat(_T("Unit_1Status:Warning"));
		break;
	case eMACHINE_STATUS_LAMP_OFF:
		Str.AppendFormat(_T("Unit_1Status:LampOff"));
		break;
	}
	Etc_Msg(Str);

	return TRUE;
}

BOOL CCimModule::SetMachineRun()
{
	Devs::MachineStatusChange(eMACHINE_STATUS_RUN);
	Devs::TowerLampControl(eMACHINE_STATUS_RUN);
	MACHINE_STATUS_CHANGE_REPORT_BLOCK MachineStatusBlock;

	//memset(&MachineStatusBlock, 0x0, sizeof(MACHINE_STATUS_CHANGE_REPORT_BLOCK));
	MachineStatusBlock.MachineStatus = eMACHINE_STATUS_RUN;
	MachineStatusBlock.MachineStatusReasonCode = 301;
	MachineStatusBlock.Unit_1Status = eMACHINE_STATUS_RUN;
	ReportMachineStatusBlock(MachineStatusBlock);

	return TRUE;
}

BOOL CCimModule::SetMachineIdle()
{
	MACHINE_STATUS_CHANGE_REPORT_BLOCK MachineStatusBlock;

	Devs::MachineStatusChange(eMACHINE_STATUS_IDLE);
	Devs::TowerLampControl(eMACHINE_STATUS_IDLE);
	memset(&MachineStatusBlock, 0x0, sizeof(MACHINE_STATUS_CHANGE_REPORT_BLOCK));
	MachineStatusBlock.MachineStatus = eMACHINE_STATUS_IDLE;
	MachineStatusBlock.MachineStatusReasonCode = 401;

	MachineStatusBlock.Unit_1Status  = eMACHINE_STATUS_IDLE;


	ReportMachineStatusBlock(MachineStatusBlock);

	return TRUE;
}

BOOL CCimModule::SetMachinePause()
{
	MACHINE_STATUS_CHANGE_REPORT_BLOCK MachineStatusBlock;

	Devs::MachineStatusChange(eMACHINE_STATUS_PAUSE);
	Devs::TowerLampControl(eMACHINE_STATUS_PAUSE);

	//memset(&MachineStatusBlock, 0x0, sizeof(MACHINE_STATUS_CHANGE_REPORT_BLOCK));
	MachineStatusBlock.MachineStatus = eMACHINE_STATUS_PAUSE;
	MachineStatusBlock.MachineStatusReasonCode = 201;
	MachineStatusBlock.Unit_1Status = eMACHINE_STATUS_PAUSE;

	ReportMachineStatusBlock(MachineStatusBlock);

	return TRUE;
}

BOOL CCimModule::SetMachinePm()
{
	MACHINE_STATUS_CHANGE_REPORT_BLOCK MachineStatusBlock;

	Devs::MachineStatusChange(eMACHINE_STATUS_PM);
	Devs::TowerLampControl(eMACHINE_STATUS_PM);

	//memset(&MachineStatusBlock, 0x0, sizeof(MACHINE_STATUS_CHANGE_REPORT_BLOCK));
	MachineStatusBlock.MachineStatus = eMACHINE_STATUS_PM;
	MachineStatusBlock.MachineStatusReasonCode = 103;
	MachineStatusBlock.Unit_1Status = eMACHINE_STATUS_PM;


	ReportMachineStatusBlock(MachineStatusBlock);

	return TRUE;
}

BOOL CCimModule::SetMachineBm()
{
	Devs::MachineStatusChange(eMACHINE_STATUS_BM);
	Devs::TowerLampControl(eMACHINE_STATUS_BM);
	MACHINE_STATUS_CHANGE_REPORT_BLOCK MachineStatusBlock;
	//memset(&MachineStatusBlock, 0x0, sizeof(MACHINE_STATUS_CHANGE_REPORT_BLOCK));
	MachineStatusBlock.MachineStatus = eMACHINE_STATUS_BM;
	MachineStatusBlock.MachineStatusReasonCode = 507;
	MachineStatusBlock.Unit_1Status = eMACHINE_STATUS_BM;


	ReportMachineStatusBlock(MachineStatusBlock);

	return TRUE;
}

BOOL CCimModule::SetMachineInitValue()
{
	MACHINE_STATUS_CHANGE_REPORT_BLOCK MachineStatusBlock;

	//SetDOutputBitValue(_DOUT_TOWER_LAMP_RED, FALSE);
	//SetDOutputBitValue(_DOUT_TOWER_LAMP_YELLOW, FALSE);
	//SetDOutputBitValue(_DOUT_TOWER_LAMP_GREEN, FALSE);
	//SetDOutputBitValue(_DOUT_TOWER_LAMP_BLUE, FALSE);

	Devs::MachineStatusChange(eMACHINE_STATUS_IDLE);
	Devs::TowerLampControl(eMACHINE_STATUS_IDLE);

	//memset(&MachineStatusBlock, 0x0, sizeof(MACHINE_STATUS_CHANGE_REPORT_BLOCK));
	MachineStatusBlock.MachineStatus = eMACHINE_STATUS_IDLE;
	MachineStatusBlock.MachineStatusReasonCode = 401;
	MachineStatusBlock.Unit_1Status = eMACHINE_STATUS_IDLE;
	//pCim->LWWrite(MACHINE_STATUS_BLOCK_START_ADDRESS, &MachineStatusBlock, sizeof(LW_LTM_MACHIN_STATUS_BLOCK));
	//CimInfo::m_LBLTM.bMachineEventMachineStatusChangeReport = TRUE;
	//pCim->LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));

	ReportMachineStatusBlock(MachineStatusBlock);
	SetCVTimeOut();
	return TRUE;
}

BOOL CCimModule::ReportCimMessageConfrimBlock(CIM_MESSAGE_CONFIRM_REPORT_BLOCK CimMessageConfirmReportBlock)
{
	LWWrite(CIM_MESSAGE_CONFRIM_REPORT_BLOCK_START_ADDRESS, &CimMessageConfirmReportBlock, sizeof(CIM_MESSAGE_CONFIRM_REPORT_BLOCK));
	CimInfo::m_LBLTM.MachineEvent_CIMMessageConfirmReport = TRUE;
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	SetT1TimeOut();

	return TRUE;
}


BOOL CCimModule::SetUpstreamInlineOnOff(BOOL bOnOff)
{
	CimInfo::m_UpStreamInline = bOnOff;
	CimInfo::m_LBLTM.MachineStatus_UpstreamLinlineModeBit = CimInfo::m_UpStreamInline;
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));


	return TRUE;
}

BOOL CCimModule::SetDownstreamInlineOnOff(BOOL bOnOff)
{
	CimInfo::m_DownStreamInline = bOnOff;
	CimInfo::m_LBLTM.MachineStatus_DownstreamInlineModeBit = CimInfo::m_DownStreamInline;
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));


	return TRUE;
}

BOOL CCimModule::SetAutoRecipeOnOff(BOOL bOnOff)
{
	AUTO_RECIPE_CHANGE_MODE_REPORT_BLOCK AutoRecipe;

	if (bOnOff)//XH_20210406  20210407
		AutoRecipe.AutoRecipeChangeMode = 1;
	else
		AutoRecipe.AutoRecipeChangeMode = 2;

	LWWrite(AUTO_RECIPE_CHANGE_MODE_REPORT_BLOCK_START_ADDRESS, &AutoRecipe, sizeof(AutoRecipe));
	CimInfo::m_LBLTM.MachineEvent_AutoRecipeChangeModeReport = TRUE;
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));

	CString Str = _T("[CIM] >> Auto Recipe Change Mode : ");
	Str.AppendFormat(_T("%d"), AutoRecipe.AutoRecipeChangeMode);
	Etc_Msg(Str);
	return TRUE;
}

BOOL CCimModule::ReportVCRModeBlock(PLW_LTM_VCR_MODE_BLOCK VCRModeBlock)
{
#if 0
	LWWrite(VCR_MODE_BLOCK_START_ADDRESS, VCRModeBlock, sizeof(VCRModeBlock));
	CimInfo::m_LBLTM.bMachineEventVCRModeChangeReport = TRUE;
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
#endif
	//SetT1TimeOut();
	return TRUE;
}

//On, Off
BOOL CCimModule::SetAutoCassetteVcrOnOff(BOOL bOnOff)
{
#if 0
	LW_LTM_VCR_MODE_BLOCK VCRModeBlock;

	memset(&VCRModeBlock, 0x0, sizeof(LW_LTM_VCR_MODE_BLOCK));
	VCRModeBlock.VCREnableMode = bOnOff;
	VCRModeBlock.VCRReadFailOperationMode = SharedInfo::m_FrameVCRReadFailOperationMode;
	CimInfo::m_LBLTM.bMachineStatusVCREnableMode = bOnOff;

	ReportVCRModeBlock(&VCRModeBlock);
	//pCim->LWWrite(VCR_MODE_BLOCK_START_ADDRESS, &VCRModeBlock, sizeof(VCRModeBlock));
	//CimInfo::m_LBLTM.bMachineEventVCRModeChangeReport = TRUE;
	//pCim->LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
#endif
	//SetT1TimeOut();
	return TRUE;
}

BOOL CCimModule::SetAutoCassetteVcrKeyInOption(INT nKeyin)
{
#if 0
	LW_LTM_VCR_MODE_BLOCK VCRModeBlock;

	memset(&VCRModeBlock, 0x0, sizeof(LW_LTM_VCR_MODE_BLOCK));
	VCRModeBlock.VCREnableMode = CimInfo::m_LBLTM.bMachineStatusVCREnableMode;

	VCRModeBlock.VCRReadFailOperationMode = nKeyin;
	SharedInfo::m_FrameVCRReadFailOperationMode = nKeyin;

	ReportVCRModeBlock(&VCRModeBlock);
	//pCim->LWWrite(VCR_MODE_BLOCK_START_ADDRESS, &VCRModeBlock, sizeof(VCRModeBlock));
	//CimInfo::m_LBLTM.bMachineEventVCRModeChangeReport = TRUE;
	//pCim->LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
#endif
	//SetT1TimeOut();
	return TRUE;
}

BOOL CCimModule::RequestEcsJobData(MASK_JOB_DATA_REQUEST_BLOCK JobDataRequestBlock)
{
	LWWrite(MASK_JOB_DATA_REQUEST_BLOCK_START_ADDRESS, &JobDataRequestBlock, sizeof(MASK_JOB_DATA_REQUEST_BLOCK));
	CimInfo::m_LBLTM.MachineMaskEvent_MaskJobDataRequest = TRUE;
	//LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));//SetT1TimeOut();
	SetT1TimeOut();
	return TRUE;
}


BOOL CCimModule::RequestDateTime(DATE_TIME_REQUEST_BLOCK DateTimeRequestBlock)
{
	LWWrite(DATE_TIME_REQUEST_BLOCK_START_ADDRESS, &DateTimeRequestBlock, sizeof(DATE_TIME_REQUEST_BLOCK));
	CimInfo::m_LBLTM.MachineEvent_DateTimeRequest = TRUE;
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));

	//SetT1TimeOut();

	Etc_Msg(_T("[CIM] >> DATE_TIME_REQUEST"));
	return TRUE;
}


BOOL CCimModule::ReportVcrEventBlock(PLW_LTM_VCR_EVENT_REPORT_BLOCK VCREventReportBlock)
{
#if 0
	LWWrite(VCR_EVENT_REPORT_BLOCK_START_ADDRESS, VCREventReportBlock, sizeof(VCREventReportBlock));
	CimInfo::m_LBLTM.bMachineEventVCREventReport = TRUE;
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
#endif
	//SetT1TimeOut();
	return TRUE;
}

BOOL CCimModule::StoredEcsJobData()
{
	LW_LTM		LWLTM;
	/*memset(&LWLTM.MaskStoredJobReportBlock, 0x0, sizeof(LWLTM.MaskStoredJobReportBlock));
	memcpy(LWLTM.MaskStoredJobReportBlock.MaskJobID, CimInfo::MaskJobData.MaskJobDataBlock.Mask_JobID, sizeof(CimInfo::MaskJobData.MaskJobDataBlock.Mask_JobID));
	LWLTM.MaskStoredJobReportBlock.LotSequenceNumber = CimInfo::MaskJobData.MaskJobDataBlock.Mask_LotSequenceNumber;
	LWLTM.MaskStoredJobReportBlock.SlotSequenceNumber = CimInfo::MaskJobData.MaskJobDataBlock.Mask_SlotSequenceNumber;
	LWLTM.MaskStoredJobReportBlock.Unit_or_Port = 1;
	LWLTM.MaskStoredJobReportBlock.UnitNumber = 1;
	LWLTM.MaskStoredJobReportBlock.SlotNumber = 1;
	LWLTM.MaskStoredJobReportBlock.PortNumber = 0;
	ReportStoredEcsJobData(LWLTM.MaskStoredJobReportBlock);*/


	return TRUE;
}


BOOL CCimModule::ReceivedEcsJobData()
{

	MASK_RECEIVED_JOB_REPORT_BLOCK ReceivedJobDataBlock;

	//memset(&ReceivedJobDataBlock, 0x0, sizeof(ReceivedJobDataBlock));
	//memcpy(&ReceivedJobDataBlock.MaskJobData, &CimInfo::MaskJobData.MaskJobDataBlock, sizeof(CimInfo::MaskJobData.MaskJobDataBlock));

	ReportReceivedEcsJobData(ReceivedJobDataBlock);

	return TRUE;
}

BOOL CCimModule::FetchedOutEcsJobData()
{
	LW_LTM		LWLTM;
	//memset(&LWLTM.MaskFetchedOutJobReportBlock, 0x0, sizeof(LWLTM.MaskFetchedOutJobReportBlock));
	//memcpy(LWLTM.MaskFetchedOutJobReportBlock.MaskJobID, CimInfo::MaskJobData.MaskJobDataBlock.Mask_JobID, sizeof(CimInfo::MaskJobData.MaskJobDataBlock.Mask_JobID));
	//LWLTM.MaskFetchedOutJobReportBlock.LotSequenceNumber = CimInfo::MaskJobData.MaskJobDataBlock.Mask_LotSequenceNumber;
	//LWLTM.MaskFetchedOutJobReportBlock.SlotSequenceNumber = CimInfo::MaskJobData.MaskJobDataBlock.Mask_SlotSequenceNumber;
	LWLTM.MaskFetchedOutJobReportBlock.Unit_or_Port = 1;
	LWLTM.MaskFetchedOutJobReportBlock.UnitNumber = 1;
	LWLTM.MaskFetchedOutJobReportBlock.SlotNumber = 1;
	LWLTM.MaskFetchedOutJobReportBlock.PortNumber = 0;
	ReportFetchedOutEcsJobData(LWLTM.MaskFetchedOutJobReportBlock);

	return TRUE;
}

BOOL CCimModule::ReportSentOutEcsJobData(PMASK_JOB_DATA JobData, JOB_COUNT_BLOCK JobCountBlock)
{

	LWWrite(MASK_SENT_OUT_JOB_REPORT_BLOCK_START_ADDRESS, JobData, sizeof(MASK_JOB_DATA));
	LWWrite(JOB_COUNT_BLOCK_START_ADDRESS, &JobCountBlock, sizeof(JOB_COUNT_BLOCK));
	CimInfo::m_LBLTM.MachineMaskEvent_MaskSentOutJobReport_1 = TRUE;
	//LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM)); 
	SetT1TimeOut();
	return TRUE;
}


BOOL CCimModule::ReportStoredEcsJobData(MASK_STORED_JOB_REPORT_BLOCK StoredJobDataBlock)
{
	LWWrite(MASK_STORED_JOB_REPORT_BLOCK_START_ADDRESS, &StoredJobDataBlock, sizeof(StoredJobDataBlock));
	CimInfo::m_LBLTM.MachineMaskEvent_MaskStoredJobReport = TRUE;
	//LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	SetT1TimeOut();
	return TRUE;
}



BOOL CCimModule::ReportReceivedEcsJobData(MASK_RECEIVED_JOB_REPORT_BLOCK ReceivedJobDataBlock)
{
	LWWrite(MASK_RECEIVED_JOB_DATA_BLOCK_START_ADDRESS, &ReceivedJobDataBlock, sizeof(MASK_RECEIVED_JOB_REPORT_BLOCK));
	CimInfo::m_LBLTM.MachineMaskEvent_MaskReceivedJobReport = TRUE;
	//LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	SetT1TimeOut();
	return TRUE;
}

BOOL CCimModule::ReportFetchedOutEcsJobData(MASK_FETCHED_OUT_JOB_REPORT_BLOCK FetchedOutJobDataBlock)
{
	LWWrite(MASK_FETCHED_OUT_JOB_REPORT_BLOCK_START_ADDRESS, &FetchedOutJobDataBlock, sizeof(FetchedOutJobDataBlock));
	CimInfo::m_LBLTM.MachineMaskEvent_MaskFetchedOutJobReport = TRUE;
	//LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	//SetT1TimeOut();
	return TRUE;
}

#if 0 //B12 Not Use //KJT 20210325
BOOL CCimModule::ReportJobDataSendBlock(PMASK_JOB_DATA JobData)
{
	LWWrite(MASK_SENT_OUT_JOB_REPORT_BLOCK_START_ADDRESS, JobData, sizeof(MATERIAL_DATA_A));

	CimInfo::m_LBLTM.MachineMaskEvent_MaskSentOutJobReport_1 = TRUE;
	//LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	//SetT1TimeOut();
	return TRUE;
}
#endif


BOOL CCimModule::ReportJobDataChangeBlock(MASK_JOB_DATA_CHANGE_REPORT_BLOCK JobData)
{
	LWWrite(MASK_JOB_DATA_CHANGE_REPORT_BLOCK_START_ADDRESS, &JobData, sizeof(MASK_JOB_DATA_CHANGE_REPORT_BLOCK));

	CimInfo::m_LBLTM.MachineMaskEvent_MaskJobDataChangeReport = TRUE;
	//LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	SetT1TimeOut();
	return TRUE;
}

BOOL CCimModule::ReportJobCntBlock(JOB_COUNT_BLOCK JobCountBlock)
{
	//LWWrite(JOB_COUNT_BLOCK_START_ADDRESS, &JobCountBlock, sizeof(JOB_COUNT_BLOCK));
	//CimInfo::m_LBLTM.MachineMaskEvent_c = TRUE;
	//LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
   //
	//SetT1TimeOut();
	return TRUE;
}

BOOL CCimModule::ReportRecipeParameterBlock(PLW_LTM_RECIPE_PARAMETER_BLOCK RecipeParameterBlock)
{
#if 0
	LWWrite(RECIPE_PARAMETER_DATA_BLOCK_START_ADDRESS, RecipeParameterBlock, sizeof(LW_LTM_RECIPE_PARAMETER_BLOCK));
	CimInfo::m_LBLTM.MachineEvent_recipe = TRUE;
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
#endif

	//SetT1TimeOut();
	return TRUE;
}




BOOL CCimModule::ReportStartProcess(MASK_PROCESS_START_REPORT_BLOCK ProcessStartReportBlock)
{
	LWWrite(JOB_PROCESS_START_REPORT_BLOCK_START_ADDRESS, &ProcessStartReportBlock, sizeof(MASK_PROCESS_START_REPORT_BLOCK));
	CimInfo::m_LBLTM.MachineMaskEvent_MaskProcessStartReport = TRUE;
	//LBWrite(MACHINE_MAXSK_START_ADDRESS, &CimInfo::m_LBLTM.MachineMaskEvent, sizeof(CimInfo::m_LBLTM.MachineMaskEvent));
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	//LBBitWrite(0xc01, 1);
	SetT1TimeOut();
	return TRUE;
}

BOOL CCimModule::SetStartProcess()
{
	MASK_PROCESS_START_REPORT_BLOCK ProcessStartReportBlock;
	//Devs::GenerateBCDField(&CimInfo::m_ProcssStartTime);
	

	GetLocalTime(&CimInfo::m_ProcssStartSystemTime);
	memcpy(&ProcessStartReportBlock.MaskJobID, &CimInfo::MaskJobData.MaskJobDataBlock.Mask_JobID, sizeof(WORD) * 10);
	ProcessStartReportBlock.LotSequenceNumber = CimInfo::MaskJobData.MaskJobDataBlock.Mask_LotSequenceNumber;
	ProcessStartReportBlock.SlotSequenceNumber = CimInfo::MaskJobData.MaskJobDataBlock.Mask_SlotSequenceNumber;
	ProcessStartReportBlock.SlotNumber = 1;
	ProcessStartReportBlock.UnitNumber = 1;
	ProcessStartReportBlock.ProcessStartTimeYear = CimInfo::m_ProcssStartSystemTime.wYear;
	ProcessStartReportBlock.ProcessStartTimeMonth = CimInfo::m_ProcssStartSystemTime.wMonth;
	ProcessStartReportBlock.ProcessStartTimeDay = CimInfo::m_ProcssStartSystemTime.wDay;
	ProcessStartReportBlock.ProcessStartTimeHour = CimInfo::m_ProcssStartSystemTime.wHour;
	ProcessStartReportBlock.ProcessStartTimeMinute = CimInfo::m_ProcssStartSystemTime.wMinute;
	ProcessStartReportBlock.ProcessStartTimeSecond = CimInfo::m_ProcssStartSystemTime.wSecond;

	ReportStartProcess(ProcessStartReportBlock);

	//pCim->LWWrite(JOB_PROCESS_START_REPORT_BLOCK_START_ADDRESS, &ProcessStartReportBlock, sizeof(LW_LTM_JOB_PROCESS_START_REPORT_BLOCK));
	//CimInfo::m_LBLTM.bMachineEventGlassProcessStartReport = TRUE;
	//pCim->LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	SetT1TimeOut();

	return TRUE;
}

BOOL CCimModule::ReportEndProcess(MASK_PROCESS_END_REPORT_BLOCK ProcessEndReportBlock)
{

	LWWrite(DV_DATA_REPORT_BLOCK_START_ADDRESS, &CimInfo::DVDataBlock, sizeof(CimInfo::DVDataBlock));

	LWWrite(DV_LIST_REPORT_BLOCK_START_ADDRESS, &CimInfo::DVDataBlock.DVDataList, sizeof(CimInfo::DVDataBlock.DVDataList)); //KJT 20210408 ???
	
	LWWrite(MASK_JOB_PROCESS_END_REPORT_BLOCK_START_ADDRESS, &ProcessEndReportBlock, sizeof(MASK_PROCESS_END_REPORT_BLOCK));
	CimInfo::m_LBLTM.MachineMaskEvent_MaskProcessEndReport = TRUE;
	//LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	//SetT1TimeOut();
	return TRUE;
}


BOOL CCimModule::DVDataReport()
{

	LWWrite(DV_DATA_REPORT_BLOCK_START_ADDRESS, &CimInfo::DVDataBlock, sizeof(CimInfo::DVDataBlock));

	LWWrite(DV_LIST_REPORT_BLOCK_START_ADDRESS, &CimInfo::DVDataBlock.DVDataList, sizeof(CimInfo::DVDataBlock.DVDataList)); //KJT 20210408 ???

	CimInfo::m_LBLTM.VariableDataEvent_DVDataReport = TRUE;
	//LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	//SetT1TimeOut();
	return TRUE;
}

BOOL CCimModule::CVDataReport()
{

	LWWrite(CV_DATA_REPORT_BLOCK_START_ADDRESS, &CimInfo::CVDataBlock, sizeof(CimInfo::CVDataBlock));

	CimInfo::m_LBLTM.VariableDataEvent_CVDataReport = TRUE;
	Etc_Msg(_T("CV Report"));
	//LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	//SetT1TimeOut();
	return TRUE;
}

BOOL CCimModule::SetEndProcess() //KJT 20210324
{
	CString Str = _T("MASKID");
	int i = 0, j = 0;

	MASK_PROCESS_END_REPORT_BLOCK ProcessEndReportBlock;
	//Devs::GenerateBCDField(&CimInfo::m_ProcssEndTime);
	GetLocalTime(&CimInfo::m_ProcssEndSystemTime);

	memcpy(&CimInfo::DVDataBlock.JobID, &CimInfo::MaskJobData.MaskJobDataBlock.Mask_JobID, sizeof(WORD) * 10);	

	memcpy(&ProcessEndReportBlock.MaskJobID, &CimInfo::MaskJobData.MaskJobDataBlock.Mask_JobID, sizeof(WORD) * 10);
	ProcessEndReportBlock.LotSequenceNumber = CimInfo::MaskJobData.MaskJobDataBlock.Mask_LotSequenceNumber;
	ProcessEndReportBlock.SlotSequenceNumber = CimInfo::MaskJobData.MaskJobDataBlock.Mask_SlotSequenceNumber;
	ProcessEndReportBlock.SlotNumber = 1;
	ProcessEndReportBlock.UnitNumber = 1;

	ProcessEndReportBlock.ProcessEndTimeYear = CimInfo::m_ProcssEndSystemTime.wYear;
	ProcessEndReportBlock.ProcessEndTimeMonth = CimInfo::m_ProcssEndSystemTime.wMonth;
	ProcessEndReportBlock.ProcessEndTimeDay = CimInfo::m_ProcssEndSystemTime.wDay;
	ProcessEndReportBlock.ProcessEndTimeHour = CimInfo::m_ProcssEndSystemTime.wHour;
	ProcessEndReportBlock.ProcessEndTimeMinute = CimInfo::m_ProcssEndSystemTime.wMinute;
	ProcessEndReportBlock.ProcessEndTimeSecond = CimInfo::m_ProcssEndSystemTime.wSecond;

	CimInfo::DVDataBlock.LotSequenceNumber = CimInfo::MaskJobData.MaskJobDataBlock.Mask_LotSequenceNumber;
	CimInfo::DVDataBlock.SlotSequenceNumber = CimInfo::MaskJobData.MaskJobDataBlock.Mask_SlotSequenceNumber;

	CimInfo::DVDataBlock.LocalProcessStartTimeYear	= CimInfo::m_ProcssStartSystemTime.wYear;
	CimInfo::DVDataBlock.LocalProcessStartTimeMonth	= CimInfo::m_ProcssStartSystemTime.wMonth;
	CimInfo::DVDataBlock.LocalProcessStartTimeDay	= CimInfo::m_ProcssStartSystemTime.wDay;
	CimInfo::DVDataBlock.LocalProcessStartTimeHour	= CimInfo::m_ProcssStartSystemTime.wHour;
	CimInfo::DVDataBlock.LocalProcessStartTimeMinute = CimInfo::m_ProcssStartSystemTime.wMinute;
	CimInfo::DVDataBlock.LocalProcessStartTimeSecond = CimInfo::m_ProcssStartSystemTime.wSecond;

	CimInfo::DVDataBlock.LocalProcessEndTimeYear		= CimInfo::m_ProcssEndSystemTime.wYear;
	CimInfo::DVDataBlock.LocalProcessEndTimeMonth	= CimInfo::m_ProcssEndSystemTime.wMonth;
	CimInfo::DVDataBlock.LocalProcessEndTimeDay		= CimInfo::m_ProcssEndSystemTime.wDay;
	CimInfo::DVDataBlock.LocalProcessEndTimeHour		= CimInfo::m_ProcssEndSystemTime.wHour;
	CimInfo::DVDataBlock.LocalProcessEndTimeMinute	= CimInfo::m_ProcssEndSystemTime.wMinute;
	CimInfo::DVDataBlock.LocalProcessEndTimeSecond	= CimInfo::m_ProcssEndSystemTime.wSecond;
	CimInfo::DVDataBlock.UnitNumber = 1;
	CimInfo::DVDataBlock.SlotNumber = 1;
	
	//KJT 20210408 Temp
	Str = Devs::FindCurrentRecipeName(SharedInfo::Active.nActiveRecipeNum);
	CimInfo::DVDataBlock.RecipeText = Str[1];
	CimInfo::DVDataBlock.RecipeText <<= 8;
	CimInfo::DVDataBlock.RecipeText |= Str[0];

	CimInfo::DVDataBlock.RecipeNumber = SharedInfo::Active.nActiveRecipeNum;

#pragma region //DV_LIST //KJT 20210410 Check !!
	CimInfo::DVDataBlock.DVDataList.RECIPE_NUM = SharedInfo::Active.nActiveRecipeNum;
#pragma endregion

	ReportEndProcess(ProcessEndReportBlock);
	//pCim->LWWrite(JOB_PROCESS_END_REPORT_BLOCK_START_ADDRESS, &ProcessEndReportBlock, sizeof(LW_LTM_JOB_PROCESS_END_REPORT_BLOCK));
	//CimInfo::m_LBLTM.bMachineEventGlassProcessEndReport = TRUE;
	//pCim->LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	//SetT1TimeOut();
	return TRUE;
}

BOOL CCimModule::ReportProcessDataBlock(PLW_LTM_PROCESS_DATA_REPORT_BLOCK ProcessDataReportBlock)
{
#if 0
	LWWrite(PROCESS_DATA_BLOCK_START_ADDRESS, ProcessDataReportBlock, sizeof(LW_LTM_PROCESS_DATA_REPORT_BLOCK));
	CimInfo::m_LBLTM.MachineMaskEvent_process = TRUE;
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
#endif
	//SetT1TimeOut();
	return TRUE;
}

BOOL CCimModule::SetProcessData()
{
	//SYSTEMTIME LinkTime;
	//LW_LTM_PROCESS_DATA_REPORT_BLOCK ProcessDataReportBlock;
	//memcpy(&ProcessDataReportBlock.JobID, &CimInfo::MaskJobData.MaskJobDataBlock.Mask_JobID, sizeof(WORD) * 10);
	//memcpy(&ProcessDataReportBlock.LocalProcessStartTime, &CimInfo::m_ProcssStartTime, sizeof(TIME_BCD));
	//memcpy(&ProcessDataReportBlock.LocalProcessEndTime, &CimInfo::m_ProcssEndTime, sizeof(TIME_BCD));
	//ProcessDataReportBlock.SlotNo = 0;

	////Awking Need Check.
	////ProcessDataReportBlock.UnitNo = 0;
	//ProcessDataReportBlock.UnitNo = 1;
	//ProcessDataReportBlock.RecipeStepNo = 1;

	////DV 판정. 
	////Awking Mask ID 멀 넣어야 되는지 재 확인.
	////Awking Mask 별로 판정이랑 데이터 넘겨줘야되는지 확인.
	//
	//GenerateDVList(&ProcessDataReportBlock.DVData[0]);

	//ReportProcessDataBlock(&ProcessDataReportBlock);
	//pCim->LWWrite(PROCESS_DATA_BLOCK_START_ADDRESS, &ProcessDataReportBlock, sizeof(LW_LTM_PROCESS_DATA_REPORT_BLOCK));
	//CimInfo::m_LBLTM.bMachineEventProcessDataReport = TRUE;
	//pCim->LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	//SetT1TimeOut();
	return TRUE;
}

BOOL CCimModule::ReportJobJudgeBlock(MATERIAL_JUDGE_RESULT_REPORT_BLOCK JobJudgeReport)
{
	LWWrite(JOB_JUDGE_REPORT_BLOCK_START_ADDRESS, &JobJudgeReport, sizeof(MATERIAL_JUDGE_RESULT_REPORT_BLOCK));
	CimInfo::m_LBLTM.MachineMaterialEvent_MaterialJudgeResultReport = TRUE;
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	return TRUE;
}

#if 0 //B12 Not Use //KJT 20210325
BOOL CCimModule::ReportReceivedJobDataBlock(PLW_LTM_RECEIVED_JOB_DATA_BLOCK ReceivedJobDataBlock)
{
	LWWrite(MASK_RECEIVED_JOB_DATA_BLOCK_START_ADDRESS, ReceivedJobDataBlock, sizeof(LW_LTM_RECEIVED_JOB_DATA_BLOCK));
	CimInfo::m_LBLTM.MachineMaskEvent_MaskReceivedJobReport = TRUE;
	//LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	return TRUE;
}
#endif

BOOL CCimModule::ReportMaterialJudgeBlock(MATERIAL_JUDGE_RESULT_REPORT_BLOCK MaterialJudgeReport)
{
	LWWrite(MATERIAL_JUDGE_RESULT_REPORT_BLOCK_START_ADDRESS, &MaterialJudgeReport, sizeof(MATERIAL_JUDGE_RESULT_REPORT_BLOCK));
	CimInfo::m_LBLTM.MachineMaterialEvent_MaterialJudgeResultReport = TRUE;
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	return TRUE;
}

BOOL CCimModule::ReplyCimModeChangeCmdBlock(PLW_MTL_CIM_MODE_CHANGE_COMMAND_REPLY_BLOCK CimModeChagneCommandReplyBlock)
{
	LWWrite(CIM_MODE_CHANGE_COMMAND_REPLY_BLOCK_START_ADDRESS, CimModeChagneCommandReplyBlock, sizeof(LW_MTL_CIM_MODE_CHANGE_COMMAND_REPLY_BLOCK));
	CimInfo::m_LBLTM.CIMPCCommandReply_CIMModeChangeCommandSendReply = TRUE;
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));

	return TRUE;
}

BOOL CCimModule::SetJobJudge()
{
	SYSTEMTIME LinkTime;
	MATERIAL_JUDGE_RESULT_REPORT_BLOCK JobJudgeReport;
	JobJudgeReport.MaterialJudgeResult = CimInfo::MaskJobData.MaskJobDataBlock.Mask_JobJudgeCode;

	ReportJobJudgeBlock(JobJudgeReport);
	//pCim->LWWrite(JOB_JUDGE_REPORT_BLOCK_START_ADDRESS, &JobJudgeReport, sizeof(LW_LTM_JOB_JUDGE_REPORT_BLOCK));
	//CimInfo::m_LBLTM.bMachineEventJobJudgeResultReport = TRUE;
	//pCim->LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
	//SetT1TimeOut();
	return TRUE;
}

BOOL CCimModule::SetMaterialJudge()
{
	MATERIAL_JUDGE_RESULT_REPORT_BLOCK MaterialJudgeReport;
	memset(&MaterialJudgeReport, 0x0, sizeof(MaterialJudgeReport));

	CString Str = _T("");

	//Temp
	Str.Format(_T("TEST"));
	memcpy((BYTE*)MaterialJudgeReport.SheetID, ConvertPlcString(Str), sizeof(MaterialJudgeReport.SheetID));
	//strcpy_s((char*)MaterialJudgeReport.SheetID, Str.GetLength() + 1, CT2A(Str));
	MaterialJudgeReport.UnitNumber = 1; //Fixed
	MaterialJudgeReport.SlotNumber = 0; //Fixed
	MaterialJudgeReport.MaterialJudgeResult = eMaterialJudge_Good;

	ReportMaterialJudgeBlock(MaterialJudgeReport);
	SetT1TimeOut();
	return TRUE;
}
void CCimModule::GenerateDVList(PDV_LIST DVList)
{
	CString Str = _T("");
	int i = 0, j = 0;

#pragma region //DV_LIST //KJT 20210410 Check !!
	DVList->RECIPE_NUM = SharedInfo::Active.nActiveRecipeNum;
#pragma endregion
}

//BOOL CCimModule::ClearEcsError(INT nIndex)
//{
//	LWWrite(ALARM_BLOCK_START_ADDRESS, &CimInfo::AlarmBlock[nIndex], sizeof(LW_LTM_ALARM_BLOCK));
//	CimInfo::m_LBLTM.bMachineEventAlarmStateChangeReport = TRUE;
//	CimInfo::m_LBLTM.bMachineStatusLocalAlarmState = FALSE;
//
//	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//
//	//SetT1TimeOut();
//	return TRUE;
//}
//
//BOOL CCimModule::ClearEcsAllError()
//{
//	//Awking All Clear 되는지 확인.
//	CimInfo::m_LBLTM.bMachineEventAlarmStateChangeReport = TRUE;
//	CimInfo::m_LBLTM.bMachineStatusLocalAlarmState = FALSE;
//	LWWrite(ALARM_BLOCK_START_ADDRESS, &CimInfo::AlarmBlock[CimInfo::m_AlarmCount], sizeof(LW_LTM_ALARM_BLOCK));
//	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));
//	Etc_Msg(_T("[Cim] Send : Alarm State Change Report"));
//
//	SharedInfo::m_AlarmAllClearFlag = TRUE;
//	//SetT1TimeOut();
//	return TRUE;
//}

//Robot 관련 -------------------------------------------------------------------------------------------
BOOL CCimModule::ResetUpStreamStageCimData()
{
	LBBitWrite(eUPSTREAM_STAGE_RUN, FALSE);
	LBBitWrite(eUPSTREAM_STAGE_IDLE, FALSE);

	LBBitWrite(eUPSTREAM_STAGE_PIN_STATE, FALSE);
	Sleep(100);
	LBBitWrite(eUPSTREAM_STAGE_SEND_ABLE, FALSE);
	Sleep(100);
	LBBitWrite(eUPSTREAM_STAGE_SHUTTER_STATE, FALSE);
	Sleep(100);
	LBBitWrite(eUPSTREAM_STAGE_SEND_START, FALSE);
	Sleep(100);
	LBBitWrite(eUPSTREAM_STAGE_SEND_COMPLETE, FALSE);
	Sleep(200);

	return TRUE;
}

BOOL CCimModule::ResetDownStreamStageCimData()
{
	LBBitWrite(eDOWNSTREAM_STAGE_RUN, FALSE);
	LBBitWrite(eDOWNSTREAM_STAGE_IDLE, FALSE);

	LBBitWrite(eDOWNSTREAM_STAGE_PIN_STATE, FALSE);
	Sleep(100);
	LBBitWrite(eDOWNSTREAM_STAGE_RECEIVE_ABLE, FALSE);
	Sleep(100);
	LBBitWrite(eDOWNSTREAM_STAGE_SHUTTER_STATE, FALSE);
	Sleep(100);
	LBBitWrite(eDOWNSTREAM_STAGE_RECEIVE_START, FALSE);
	Sleep(100);
	LBBitWrite(eDOWNSTREAM_STAGE_RECEIVE_COMPLETE, FALSE);
	Sleep(200);

	return TRUE;
}

BOOL CCimModule::SetUpStreamInline()
{
	//pCim->LBBitWrite(eDOWNSTREAM_ROBOT_INLINE, TRUE);
	LBBitWrite(eDOWNSTREAM_STAGE_INLINE, TRUE);
	LBBitWrite(eUPSTREAM_STAGE_INLINE, TRUE);
	LBBitWrite(eUPSTREAM_STAGE_RUN, TRUE);
	LBBitWrite(eUPSTREAM_STAGE_GLASS_EXIST_ARM_1, TRUE);
	return TRUE;
}

BOOL CCimModule::SetDownStreamInline()
{
	//pCim->LBBitWrite(eDOWNSTREAM_ROBOT_INLINE, TRUE);
	LBBitWrite(eDOWNSTREAM_STAGE_INLINE, TRUE);
	LBBitWrite(eUPSTREAM_STAGE_INLINE, FALSE);
	LBBitWrite(eDOWNSTREAM_STAGE_RUN, TRUE);
	return TRUE;
}

BOOL CCimModule::IsCancleRequest()
{
	BOOL ret = FALSE;
	ret = LBBitRead(eUPSTREAM_ROBOT_CANCEL_REQUEST);
	ret |= LBBitRead(eDOWNSTREAM_ROBOT_CANCEL_REQUEST);
	ret |= LBBitRead(eUPSTREAM_STAGE_CANCEL_REQUEST);
	ret |= LBBitRead(eDOWNSTREAM_STAGE_CANCEL_REQUEST);

	return ret;
}

BOOL CCimModule::IsDownStreamRobotReceiveAble()
{
	BOOL ret = FALSE;
	ret = LBBitRead(eDOWNSTREAM_ROBOT_RECEIVE_ABLE);
	return ret;
}

BOOL CCimModule::IsDownStreamRobotJobTransferSignal1()
{
	BOOL ret = FALSE;
	ret = LBBitRead(eDOWNSTREAM_ROBOT_JOB_TRANSFER_SIGNAL_1);
	return ret;
}

BOOL CCimModule::IsDownStreamRobotReceiveComplete()
{
	BOOL ret = FALSE;
	ret = LBBitRead(eDOWNSTREAM_ROBOT_RECEIVE_COMPLETE);
	return ret;
}

BOOL CCimModule::IsUpStreamRobotSendAble()
{
	BOOL ret = FALSE;
	ret = LBBitRead(eUPSTREAM_ROBOT_SEND_ABLE);
	return ret;
}

//BOOL CCimModule::IsUpStreamRobotSendComplete()
//{
//	BOOL ret = FALSE;
//	ret = pCim->GetLbUser1BitBufData(eUPSTREAM_ROBOT_SEND_COMPLETE);
//	return ret;
//}

BOOL CCimModule::IsUpStreamRobotSendComplete()
{
	BOOL ret = FALSE;
	ret = LBBitRead(eUPSTREAM_ROBOT_SEND_COMPLETE);
	return ret;
}

BOOL CCimModule::SetSignalUpStreamFrameZLeftUp(BOOL bOnOff)
{
	LBBitWrite(eUPSTREAM_STAGE_LIFT_UP, bOnOff);

	return TRUE;
}

BOOL CCimModule::SetSignalUpStreamFrameZLeftDn(BOOL bOnOff)
{

	LBBitWrite(eUPSTREAM_STAGE_LIFT_DOWN, bOnOff);

	return TRUE;
}

BOOL CCimModule::SetSignalUpStreamFrameZPinState(BOOL bOnOff)
{
	LBBitWrite(eUPSTREAM_STAGE_PIN_STATE, bOnOff);

	return TRUE;
}

BOOL CCimModule::SetSignalUpStreamJobReportOnOff(BOOL bOnOff)
{
	LBBitWrite(CIM_RECEIVED_JOB_REPORT_ADDRESS, bOnOff);

	return TRUE;
}

BOOL CCimModule::SetSignalUpStreamStageSendAble(BOOL bOnOff)
{
	LBBitWrite(eUPSTREAM_STAGE_SEND_ABLE, bOnOff);

	return TRUE;
}

BOOL CCimModule::SetSignalUpStreamStageShutterOpen(BOOL bOnOff)
{
	LBBitWrite(eUPSTREAM_STAGE_SHUTTER_OPEN, bOnOff);

	return TRUE;
}

BOOL CCimModule::SetSignalUpStreamStageShutterState(BOOL bOnOff)
{
	LBBitWrite(eUPSTREAM_STAGE_SHUTTER_STATE, bOnOff);

	return TRUE;
}

BOOL CCimModule::SetSignalUpStreamStageShutterClose(BOOL bOnOff)
{
	LBBitWrite(eUPSTREAM_STAGE_SHUTTER_CLOSE, bOnOff);
	return TRUE;
}

BOOL CCimModule::SetSignalUpStreamStageSendStart(BOOL bOnOff)
{
	LBBitWrite(eUPSTREAM_STAGE_SEND_START, bOnOff);

	return TRUE;
}

BOOL CCimModule::SetSignalUpStreamStageSendComplete(BOOL bOnOff)
{
	LBBitWrite(eUPSTREAM_STAGE_SEND_COMPLETE, bOnOff);

	return TRUE;
}

BOOL CCimModule::SetSignalUpStreamStageGlassExistArm1(BOOL bOnOff)
{
	LBBitWrite(eUPSTREAM_STAGE_GLASS_EXIST_ARM_1, bOnOff);

	return TRUE;
}

BOOL CCimModule::SetSignalUpStreamStageRun(BOOL bOnOff)
{
	LBBitWrite(eUPSTREAM_STAGE_RUN, bOnOff);

	return TRUE;
}

BOOL CCimModule::SetSignalUpStreamStageIdle(BOOL bOnOff)
{
	LBBitWrite(eUPSTREAM_STAGE_IDLE, bOnOff);

	return TRUE;
}


BOOL CCimModule::SetIoShutterOpen(BOOL bOnOff)
{
	//SetDOutputBitValue(_IF_DO_SHUTTER, bOnOff);
	return TRUE;
}

BOOL CCimModule::SetIoFrameZPinUp(BOOL bOnOff)
{
	//SetDOutputBitValue(_IF_DO_FRAME_Z_PIN_UP, bOnOff);
	return TRUE;
}

BOOL CCimModule::SetSignalDownStreamFrameZPinState(BOOL bOnOff)
{
	LBBitWrite(eDOWNSTREAM_STAGE_PIN_STATE, bOnOff);

	return TRUE;
}

BOOL CCimModule::SetSignalDownStreamReceiveAble(BOOL bOnOff)
{
	LBBitWrite(eDOWNSTREAM_STAGE_RECEIVE_ABLE, bOnOff);

	return TRUE;
}

BOOL CCimModule::SetSignalDownStreamShutterState(BOOL bOnOff)
{
	LBBitWrite(eDOWNSTREAM_STAGE_SHUTTER_STATE, bOnOff);

	return TRUE;
}

BOOL CCimModule::SetSignalDownStreamReceiveStart(BOOL bOnOff)
{
	LBBitWrite(eDOWNSTREAM_STAGE_RECEIVE_START, bOnOff);

	return TRUE;
}

BOOL CCimModule::SetSignalDownStreamReceiveComplete(BOOL bOnOff)
{
	LBBitWrite(eDOWNSTREAM_STAGE_RECEIVE_COMPLETE, bOnOff);

	return TRUE;
}

BOOL CCimModule::SetSignalDownStreamRun(BOOL bOnOff)
{
	LBBitWrite(eDOWNSTREAM_STAGE_RUN, bOnOff);

	return TRUE;
}

BOOL CCimModule::SetSignalDownStreamIdle(BOOL bOnOff)
{
	LBBitWrite(eDOWNSTREAM_STAGE_IDLE, bOnOff);

	return TRUE;
}

//BOOL CCimModule::SetSignalDownStreamIdle(BOOL bOnOff)
//{
//	pCim->LBBitWrite(eDOWNSTREAM_STAGE_IDLE, bOnOff);
//
//	return TRUE;
//}

BOOL CCimModule::SaveMaskJobData()
{
	CString szMsg;
	CFile file;

	szMsg.Format(_T("%s\\dat\\MaskJobData.dat"), SharedInfo::VisionAgentPath);
	file.Open(szMsg, CFile::modeCreate | CFile::modeWrite);
	file.Write(&CimInfo::MaskJobData, sizeof(MASK_JOB_DATA));
	file.Close();

	return TRUE;
}

BOOL CCimModule::LoadMaskJobData()
{
	CString szMsg;
	CFile file;

	szMsg.Format(_T("%s\\dat\\MaskJobData.dat"), SharedInfo::VisionAgentPath);
	if (file.Open(szMsg, CFile::modeRead) == FALSE)
		file.Open(szMsg, CFile::modeRead | CFile::modeCreate);
	file.Read(&CimInfo::MaskJobData, sizeof(MASK_JOB_DATA));
	file.Close();

	return TRUE;
}

#if 0 //B12 Not Use //KJT 20210325
BOOL CCimModule::SaveJobDataB()
{
	CString szMsg;
	CFile file;

	szMsg.Format(_T("%s\\dat\\FrameJobDataB.dat"), SharedInfo::VisionAgentPath);
	file.Open(szMsg, CFile::modeCreate | CFile::modeWrite);
	file.Write(&CimInfo::JobDataB, sizeof(MATERIAL_DATA_B));
	file.Close();

	return TRUE;
}

BOOL CCimModule::LoadJobDataB()
{
	CString szMsg;
	CFile file;

	szMsg.Format(_T("%s\\dat\\FrameJobDataB.dat"), SharedInfo::VisionAgentPath);
	if (file.Open(szMsg, CFile::modeRead) == FALSE)
		file.Open(szMsg, CFile::modeRead | CFile::modeCreate);
	file.Read(&CimInfo::JobDataB, sizeof(MATERIAL_DATA_B));
	file.Close();

	return TRUE;

#endif

char* CCimModule::ConvertPlcString(CString strData)
{
	char cTemp[100];
	memset(cTemp, 0x00, sizeof(cTemp));
	sprintf(cTemp, "%s", (char*)CT2CA(strData));
	return cTemp;
}


//20201215 Night Work - Parkcm
BOOL CCimModule::ReportMachineModeChange(MACHINE_MODE_CHANGE_REPORT_BLOCK MachineModeChangeReport)
{
	LWWrite(MACHINE_MODE_CHANGE_REPORT_BLOCK_START_ADDRESS, &MachineModeChangeReport, sizeof(MACHINE_MODE_CHANGE_REPORT_BLOCK));
	CimInfo::m_LBLTM.MachineEvent_MachineModeChangeReport = TRUE;
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));

	return TRUE;
}

BOOL CCimModule::ReportOperatorLogin(OPERATOR_LOGIN_REPORT_BLOCK OperatorLoginReport)
{
	LWWrite(OPERATOR_LOGIN_REPORT_BLOCK_START_ADDRESS, &OperatorLoginReport, sizeof(OPERATOR_LOGIN_REPORT_BLOCK));
	CimInfo::m_LBLTM.MachineEvent_OperatorLoginReport = TRUE;
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));

	return TRUE;
}

BOOL CCimModule::ReportJobManualMove(MASK_JOB_MANUAL_MOVE_REPORT_BLOCK JobManualMoveReport)
{
	LWWrite(MASK_JOB_MANUAL_MOVE_REPOBT_BLOCK_START_ADDRESS, &JobManualMoveReport, sizeof(MASK_JOB_MANUAL_MOVE_REPORT_BLOCK));
	CimInfo::m_LBLTM.MachineMaskEvent_MaskJobManualMoveReport = TRUE;
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));

	return TRUE;
}

BOOL CCimModule::PositionJobStatus(POSITION_JOB_BLOCK PositionJobBlock)
{
	LWWrite(POSITION_JOB_REPORT_BLOCK_START_ADDRESS, &PositionJobBlock, sizeof(POSITION_JOB_BLOCK));
	return TRUE;
}

BOOL CCimModule::ReportSheetAssemblyComplete(SHEET_ASSEMBLY_COMPLETE_REPORT_BLOCK SheetAssemblyCompleteReportBlock)
{
	LWWrite(SHEET_ASSEMBLY_COMPLETE_REPORT_BLOCK_START_ADDRESS, &SheetAssemblyCompleteReportBlock, sizeof(SHEET_ASSEMBLY_COMPLETE_REPORT_BLOCK));
	CimInfo::m_LBLTM.MachineMaterialEvent_SheetAssemblyCompleteReport = TRUE;
	LBWrite(LB_LTM_START_ADDRESS, &CimInfo::m_LBLTM, sizeof(LB_LTM));

	return TRUE;
}