#include "stdafx.h"
#include "CimInfo.h"
#include "Data/ModelData.h"
#include "Data/ManualData.h"
#include "Data/SystemData.h"
#include "VisionAgentDlg.h"
#include "VisionAgent.h"
#include "Vision/VisionAgentDefine.h"



CimInfo::CimInfo()
{

}


CimInfo::~CimInfo()
{

}


void CimInfo::Initialize(void)
{

}

void CimInfo::Finalize(void)
{
}

//Job Data

MASK_JOB_DATA CimInfo::MaskJobData;
MASK_JOB_DATA		CimInfo::StoredJob[20];
int			CimInfo::StoredJobCnt = 0;



MAGAZINE_DATA_REQUEST_REPLY_BLOCK		CimInfo::MagazineDataRequestReplyBlock[6];

#if 0 //B12 Not Use //KJT 20210325
MATERIAL_DATA_A CimInfo::JobDataA;
MATERIAL_DATA_B CimInfo::JobDataB;
#endif

SHEET_INFORMATION_BLOCK CimInfo::SheetInfo;
LW_MTL_MATERIAL_GROUP_DATA_BLOCK CimInfo::MaterialGroupData;
MATERIAL_STATUS_CHANGE_REPORT_BLOCK CimInfo::MaterialStatus;





BOOL CimInfo::m_bResumeCancelFlag;


WORD CimInfo::m_CimMode;
WORD CimInfo::m_UpStreamInline;
WORD CimInfo::m_DownStreamInline;

WORD CimInfo::m_AutoRecipe;

WORD CimInfo::m_MachineState;

CimMessage CimInfo::CIMMessage[10];
int CimInfo::CIMMessageCnt;
CIM_MESSAGE_CONFIRM_REPORT_BLOCK CimInfo::CimMessageConfirmReportBuffer[10];
int CimInfo::CIMMessageBufferCnt = 0;
LB_LTM CimInfo::m_LBLTM;
LB_MTL CimInfo::m_LBMTL;
DWORD	CimInfo::ProcessingTime;
TIME_BCD CimInfo::m_ProcssStartTime;
TIME_BCD CimInfo::m_ProcssEndTime;

SYSTEMTIME CimInfo::m_ProcssStartSystemTime;
SYSTEMTIME CimInfo::m_ProcssEndSystemTime;
DWORD CimInfo::m_T1Timer = 4000;
DWORD CimInfo::m_T2Timer = 2000;
DWORD CimInfo::m_T3Timer = 500;
DWORD CimInfo::m_CVTimer = 5000;
DWORD CimInfo::m_CVTimerCount = 0;
DWORD CimInfo::m_CommonTimer;
DWORD CimInfo::m_TowerLampTimer;
DWORD CimInfo::m_CIMPCOnStatusTimer;
DWORD CimInfo::m_CIMPCOffStatusTimer;

DWORD CimInfo::m_AlarmT1TimerCheck[5] = { 0, }; //KJT 20210407
DWORD CimInfo::m_T1TimerCheck;
DWORD CimInfo::m_T2TimerCheck;
DWORD CimInfo::m_T3TimerCheck;
DWORD CimInfo::m_CVTimerCheck;
DWORD CimInfo::m_CommonTimerCheck;
DWORD CimInfo::m_TowerLampTimerCheck;
DWORD CimInfo::m_CIMPCOnStatusTimerCheck;
DWORD CimInfo::m_CIMPCOffStatusTimerCheck;


BOOL CimInfo::m_TowerLampStatusRed = 1;
BOOL CimInfo::m_TowerLampStatusYellow = 1;
BOOL CimInfo::m_TowerLampStatusGreen = 1;
BOOL CimInfo::m_TowerLampStatusBlue = 1;

BOOL CimInfo::m_BuzzerFast = FALSE;
BOOL CimInfo::m_BuzzerSlow = FALSE;
CTime CimInfo::AlarmOccuredTime[100];
SYSTEMTIME	CimInfo::JobReceiveTime[20];
ALARM_REPORT_BLOCK CimInfo::AlarmBlock[100];

MACHINE_RECIPE_TABLE CimInfo::m_MachineRecipeTable; // //KJT 20210410

CTime CimInfo::AlarmReportOccuredTime[ALARM_CODE_MAX];
ALARM_REPORT_BLOCK CimInfo::AlarmReportBlock[ALARM_CODE_MAX]; //KJT 20210407

CTime CimInfo::AlarmOccuredTimeReserve[100]; //KJT 20210407
ALARM_REPORT_BLOCK CimInfo::AlarmBlockReserve[100]; //KJT 20210407


WORD CimInfo::m_AlarmCount = 0;
WORD CimInfo::m_AlarmMaxPos = 1; //KJT 20210407
WORD CimInfo::m_AlarmCmdPos = 0;
INT	  CimInfo::m_nCmd = 0;
INT CimInfo::m_nAlarmPos[ALARM_CODE_MAX] = { 0, }; //KJT 20210407
INT CimInfo::m_nAlarmReserveCount = 0; //KJT 20210407
INT CimInfo::m_nAlarmReportCount = 0; //KJT 20210412

BOOL CimInfo::m_AlarmAllClearFlag = FALSE; //KJT 20210417
WORD CimInfo::m_FrameVCRReadFailOperationMode;
WORD CimInfo::m_CassetteVCRReadFailOperationMode;
WORD CimInfo::m_MaskVCRReadFailOperationMode;


WORD CimInfo::m_ProductJobCount = 1;
WORD CimInfo::m_DummyJobCount;

RECIPE_CHANGE_REPORT_BLOCK CimInfo::RecipeChangeReportBlockBuffer[5];
int CimInfo::RecipeChangeReportBlockCnt = 0;

DFS_PARA CimInfo::m_sDfsPara;


DV_DATA_REPORT_BLOCK CimInfo::DVDataBlock;
CV_DATA_REPORT_BLOCK CimInfo::CVDataBlock;
SV_LIST CimInfo::SVData;
MASK_JOB_DATA_REQUEST_BLOCK CimInfo::JobDataRequestBlock;

int CimInfo::m_nCheckRecipe = 0; //KJT 20210409




