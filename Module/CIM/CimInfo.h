#pragma once

#include "Cimdefine.h"


#define MAX_RECIPE_COUNT		1000

class CimInfo
{
public:
	CimInfo();
	~CimInfo();

	static void Initialize(void);
	static void Finalize(void);

public:	


	//Cim Field


	static BOOL m_bResumeCancelFlag;

	static DWORD	ProcessingTime;

	static LB_LTM m_LBLTM;
	static LB_MTL m_LBMTL;

	static TIME_BCD m_ProcssStartTime;
	static TIME_BCD m_ProcssEndTime;

	static SYSTEMTIME m_ProcssStartSystemTime;
	static SYSTEMTIME m_ProcssEndSystemTime;

	static CimMessage CIMMessage[10];
	static CIM_MESSAGE_CONFIRM_REPORT_BLOCK CimMessageConfirmReportBuffer[10];
	static int CIMMessageCnt;
	static int CIMMessageBufferCnt;

	static WORD m_CimMode;
	static WORD	m_MachineState;
	static WORD m_UpStreamInline;
	static WORD m_DownStreamInline;

	static WORD m_AutoRecipe;

	static DWORD m_T1Timer;
	static DWORD m_T2Timer;
	static DWORD m_T3Timer;
	static DWORD m_CVTimer;
	static DWORD m_CVTimerCount;
	static DWORD m_CommonTimer;
	static DWORD m_TowerLampTimer;
	static DWORD m_CIMPCOnStatusTimer;
	static DWORD m_CIMPCOffStatusTimer;

	static DWORD m_AlarmT1TimerCheck[5]; //KJT 20210407
	static DWORD m_T1TimerCheck;
	static DWORD m_T2TimerCheck;
	static DWORD m_T3TimerCheck;
	static DWORD m_CVTimerCheck;
	static DWORD m_CommonTimerCheck;
	static DWORD m_TowerLampTimerCheck;
	static DWORD m_CIMPCOnStatusTimerCheck;
	static DWORD m_CIMPCOffStatusTimerCheck;


	static BOOL m_TowerLampStatusRed;
	static BOOL m_TowerLampStatusYellow;
	static BOOL m_TowerLampStatusGreen;
	static BOOL m_TowerLampStatusBlue;


	static BOOL m_BuzzerFast;
	static BOOL m_BuzzerSlow;
	static WORD m_AlarmCount;
	static WORD m_AlarmMaxPos;
	static WORD m_AlarmCmdPos;
	static INT	   m_nCmd;
	static INT m_nAlarmPos[ALARM_CODE_MAX]; //KJT 20210407
	static INT m_nAlarmReserveCount; //KJT 20210407
	static INT m_nAlarmReportCount; //KJT 20210412

	static BOOL m_AlarmAllClearFlag; //KJT 20210417
	static WORD	m_FrameVCRReadFailOperationMode;
	static WORD	m_CassetteVCRReadFailOperationMode;
	static WORD	m_MaskVCRReadFailOperationMode;


	static CTime AlarmOccuredTime[100];
	static SYSTEMTIME JobReceiveTime[20];
	static ALARM_REPORT_BLOCK AlarmBlock[100];

	static MACHINE_RECIPE_TABLE m_MachineRecipeTable;

	static CTime AlarmReportOccuredTime[ALARM_CODE_MAX]; //KJT 20210407
	static ALARM_REPORT_BLOCK AlarmReportBlock[ALARM_CODE_MAX]; //KJT 20210407

	static CTime AlarmOccuredTimeReserve[100]; //KJT 20210407
	static ALARM_REPORT_BLOCK AlarmBlockReserve[100]; //KJT 20210407
	
	static WORD m_ProductJobCount;
	static WORD m_DummyJobCount;

	static MASK_JOB_DATA MaskJobData;
	static MASK_JOB_DATA StoredJob[20];
	static int StoredJobCnt;

#if 0 //B12 Not Use //KJT 20210325
	static MATERIAL_DATA_A JobDataA;
	static MATERIAL_DATA_A JobTempDataA;
	static MATERIAL_DATA_B JobDataB;
#endif

	static SHEET_INFORMATION_BLOCK SheetInfo;
	static LW_MTL_MATERIAL_GROUP_DATA_BLOCK MaterialGroupData;
	static MATERIAL_STATUS_CHANGE_REPORT_BLOCK MaterialStatus;

	static MAGAZINE_DATA_REQUEST_REPLY_BLOCK		MagazineDataRequestReplyBlock[6];

	static DFS_PARA m_sDfsPara;


	static	RECIPE_CHANGE_REPORT_BLOCK RecipeChangeReportBlockBuffer[5];
	static	int RecipeChangeReportBlockCnt;



	static DV_DATA_REPORT_BLOCK DVDataBlock;
	static CV_DATA_REPORT_BLOCK CVDataBlock;
	static SV_LIST SVData;
	static MASK_JOB_DATA_REQUEST_BLOCK JobDataRequestBlock;

	static int m_nCheckRecipe; //KJT 20210409
};

