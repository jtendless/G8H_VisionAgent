#include "stdafx.h"
#include "Devs.h"

#include "Log/Logger.h"
#include "FmmLight1.h"
#include "CIM/CimInfo.h"
#include "Data/SystemData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CClientInterface Devs::MotionIf;

#if 0
CWkLibBdc*				Devs::m_LightController;
CWkLibPua310*			Devs::m_Pua310;
#endif
CSocketManager			Devs::m_SocketLoaderBarCode;

#ifndef MIL_NOT_USE
CWkLibVision*			Devs::m_Camera6G_LT;
CWkLibVision*			Devs::m_Camera6G_RT;
CWkLibVision*			Devs::m_Camera6G_RB;
CWkLibVision*			Devs::m_Camera6G_LB;

CWkLibVision*			Devs::m_Camera8G_LT;
CWkLibVision*			Devs::m_Camera8G_RT;
CWkLibVision*			Devs::m_Camera8G_RB;
CWkLibVision*			Devs::m_Camera8G_LB;

CWkLibVision*			Devs::m_Camera10X;

MIL_ID						Devs::MilApplication;
MIL_ID						Devs::MilSysSol0;
MIL_ID						Devs::MilSysSol1;
MIL_ID						Devs::MilSysSol2;

MIL_ID						Devs::MilDigCam6G_LT;
MIL_ID						Devs::MilDigCam6G_RT;
MIL_ID						Devs::MilDigCam6G_RB;
MIL_ID						Devs::MilDigCam6G_LB;

MIL_ID						Devs::MilDigCam8G_LT;
MIL_ID						Devs::MilDigCam8G_RT;
MIL_ID						Devs::MilDigCam8G_RB;
MIL_ID						Devs::MilDigCam8G_LB;

//MIL_ID						Devs::MilDigReview10X;
#endif

#pragma region //Motion
CBaseMotion					Devs::m_BaseMotion;
CJogMotion					Devs::m_JogMotion;
CGantryMotion				Devs::m_GantryMotion;
CClampMotion				Devs::m_ClampMotion;
CStretchMotion				Devs::m_StretchMotion;
CGripperZMotion				Devs::m_GripperZMotion;
CInspectionStageMotion		Devs::m_InspectionStageMotion;
#pragma endregion


#pragma region //Flow
COrigin_AllAxis_Flow		Devs::m_Origin_AllAxis_Flow;//21.02.25 sjc add
#pragma endregion

#pragma region //Cim Module	
CCimModule				Devs::CimMotion;// = new CCimModule;

CCommFTP				Devs::m_pDfs;

void Devs::MachineStatusChange(MACHINE_STATUS_ENUM MachineStatus)
{
	CimInfo::m_MachineState = MachineStatus;
}


BOOL Devs::TowerLampControl(int Status)
{
#if 0
	switch (Status)
	{
	case eMACHINE_STATUS_PM: //PM
		CimInfo::m_TowerLampStatusRed = TOWER_LAMP_ON;
		CimInfo::m_TowerLampStatusYellow = TOWER_LAMP_OFF;
		CimInfo::m_TowerLampStatusGreen = TOWER_LAMP_OFF;
		CimInfo::m_BuzzerFast = FALSE;
		CimInfo::m_BuzzerSlow = FALSE;
		break;
	case eMACHINE_STATUS_BM: //BM
		CimInfo::m_TowerLampStatusRed = TOWER_LAMP_BLINK;
		CimInfo::m_TowerLampStatusYellow = TOWER_LAMP_BLINK;
		CimInfo::m_TowerLampStatusGreen = TOWER_LAMP_OFF;
		CimInfo::m_BuzzerFast = TRUE;
		CimInfo::m_BuzzerSlow = FALSE;
		break;
	case eMACHINE_STATUS_PAUSE: //Pause
		CimInfo::m_TowerLampStatusRed = TOWER_LAMP_ON;
		CimInfo::m_TowerLampStatusYellow = TOWER_LAMP_BLINK;
		CimInfo::m_TowerLampStatusGreen = TOWER_LAMP_OFF;
		CimInfo::m_BuzzerFast = FALSE;
		CimInfo::m_BuzzerSlow = FALSE;
		break;
	case eMACHINE_STATUS_IDLE: //Idle
		CimInfo::m_TowerLampStatusRed = TOWER_LAMP_OFF;
		CimInfo::m_TowerLampStatusYellow = TOWER_LAMP_BLINK;
		CimInfo::m_TowerLampStatusGreen = TOWER_LAMP_OFF;
		CimInfo::m_BuzzerFast = FALSE;
		CimInfo::m_BuzzerSlow = FALSE;
		break;
	case eMACHINE_STATUS_RUN: //RUN
		CimInfo::m_TowerLampStatusRed = TOWER_LAMP_OFF;
		CimInfo::m_TowerLampStatusYellow = TOWER_LAMP_OFF;
		CimInfo::m_TowerLampStatusGreen = TOWER_LAMP_ON;
		CimInfo::m_BuzzerFast = FALSE;
		CimInfo::m_BuzzerSlow = FALSE;
		break;

	case eMACHINE_STATUS_WARNING: //Warning
		CimInfo::m_TowerLampStatusRed = TOWER_LAMP_BLINK;
		CimInfo::m_TowerLampStatusYellow = TOWER_LAMP_OFF;
		CimInfo::m_TowerLampStatusGreen = TOWER_LAMP_OFF;
		CimInfo::m_BuzzerFast = FALSE;
		CimInfo::m_BuzzerSlow = TRUE;
		break;
	}
#endif

	return TRUE;
}


#if 0 //B12 Not Use //KJT 20210325
BOOL  Devs::SetJobDataAtoB(PMATERIAL_DATA_A JobDataA, PMATERIAL_DATA_B JobDataB)
{
	memcpy(JobDataB->wLotID, JobDataA->wLotID, 10);
	memcpy(JobDataB->wMeterialID, JobDataA->wMeterialID, 10);
	memcpy(JobDataB->wOPERID, JobDataA->wOPERID, 5);
	memcpy(JobDataB->wProdID, JobDataA->wProdID, 12);
	memcpy(JobDataB->wProcessingFlag, JobDataA->wProcessingFlag, 2);
	memcpy(JobDataB->wInspectionJudgeData, JobDataA->wInspectionJudgeData, 2);
	memcpy(JobDataB->wSkipFlag, JobDataA->wSkipFlag, 2);
	memcpy(JobDataB->wInspectionFlag, JobDataA->wInspectionFlag, 2);
	memcpy(JobDataB->wMeterialSizeCode, JobDataA->wMeterialSizeCode, 2);
	memcpy(JobDataB->wMaskOffsetX, JobDataA->wMaskOffsetX, 2);
	memcpy(JobDataB->wMaskOffsetY, JobDataA->wMaskOffsetY, 2);
	memcpy(JobDataB->wMaskOffsetT, JobDataA->wMaskOffsetT, 2);
	memcpy(JobDataB->wOptionData, JobDataA->wOptionData, 6);
	JobDataB->wLotSequenceNo = JobDataA->wLotSequenceNo;
	JobDataB->wSlotSequenceNo = JobDataA->wSlotSequenceNo;
	JobDataB->wMeterialJudgeCode = JobDataA->wMeterialJudgeCode;
	JobDataB->wMeterialGradeCode = JobDataA->wMeterialGradeCode;
	JobDataB->wMode = JobDataA->wMode;
	JobDataB->unDummyDataType = JobDataA->unDummyDataType;
	JobDataB->wProcessingCount = JobDataA->wProcessingCount;
	JobDataB->wCoverUsedCount = JobDataA->wCoverUsedCount;
	JobDataB->wHousingUsedCount = JobDataA->wHousingUsedCount;

	return TRUE;
}
#endif

void Devs::GenerateBCDField(PTIME_BCD BCDData)
{
	SYSTEMTIME LinkTime;

	GetLocalTime(&LinkTime);
	BCDData->Year.ValueX10 = (LinkTime.wYear % 100) / 10;
	BCDData->Year.ValueX1 = LinkTime.wYear % 10;
	BCDData->Month.ValueX10 = LinkTime.wMonth / 10;
	BCDData->Month.ValueX1 = LinkTime.wMonth % 10;
	BCDData->Day.ValueX10 = LinkTime.wDay / 10;
	BCDData->Day.ValueX1 = LinkTime.wDay % 10;
	BCDData->Hour.ValueX10 = LinkTime.wHour / 10;
	BCDData->Hour.ValueX1 = LinkTime.wHour % 10;
	BCDData->Minute.ValueX10 = LinkTime.wMinute / 10;
	BCDData->Minute.ValueX1 = LinkTime.wMinute % 10;
	BCDData->Second.ValueX10 = LinkTime.wSecond / 10;
	BCDData->Second.ValueX1 = LinkTime.wSecond % 10;
}

void Devs::GenerateSVList(PSV_LIST SVList)
{
/*
	int i = 0, j = 0;

	SVList->CDA_MAIN_AIR = SharedInfo::AInputValue[_AIN_CDA_MAIN_AIR];
	SVList->SUPPLY_PRESSURE = SharedInfo::AInputValue[_AIN_SUPPLY_PRESSURE];
	SVList->GANTRY_Y_AXIS_1_PRESSURE = SharedInfo::AInputValue[_AIN_GANTRY_Y_AXIS_1_PRESSURE];
	SVList->GANTRY_Y_AXIS_2_PRESSURE = SharedInfo::AInputValue[_AIN_GANTRY_Y_AXIS_2_PRESSURE];
	SVList->GANTRY_X_AXIS_1_PRESSURE = SharedInfo::AInputValue[_AIN_GANTRY_X_AXIS_1_PRESSURE];
	SVList->ISOLATOR_1_PRESSURE_ACT_H = SharedInfo::AInputValue[_AIN_ISOLATOR_1_PRESSURE_ACT_H];
	SVList->ISOLATOR_2_PRESSURE_ACT_V = SharedInfo::AInputValue[_AIN_ISOLATOR_2_PRESSURE_ACT_V];
	SVList->GANTRY_REGULATOR_Y1 = SharedInfo::AInputValue[_AIN_GANTRY_REGULATOR_Y1];
	SVList->GANTRY_REGULATOR_Y2 = SharedInfo::AInputValue[_AIN_GANTRY_REGULATOR_Y2];
	SVList->GANTRY_REGULATOR_X_TOP = SharedInfo::AInputValue[_AIN_GANTRY_REGULATOR_X_TOP];
	SVList->GANTRY_REGULATOR_X_BOTTOM = SharedInfo::AInputValue[_AIN_GANTRY_REGULATOR_X_BOTTOM];

	SVList->LoaderStickDetect = Devs::m_LoaderMotion.Is_Stick_Active_Vac_On();
	SVList->InspectionStageStickDetect = Devs::m_InspectionStageMotion.Is_Inspect_Stage_Vac_On();
	SVList->UnloaderStickDetect = Devs::m_UnloaderMotion.Is_Stick_Active_Vac_On();
	for (i = 0; i < eGRIPPER_ROW_MAX; i++)
	{
		SVList->GripperClampOn_L[i] = Devs::m_ClampMotion.Is_ClampOn((enum_eGRIPPER_ROW)i);
		SVList->GripperClampOn_R[i] = Devs::m_ClampMotion.Is_ClampOn((enum_eGRIPPER_ROW)i);
	}
*/
}
#pragma endregion

//Folder Manager
CFileManager				Devs::m_FolderManager;

CMappingProc				Devs::m_MappingProc;

CWinThread*					Devs::m_pMonitoringThread;
int							Devs::m_nIsRunningMonitoringThread;
int							Devs::m_nStopMonitoringThread;

#if 0
CMotionModule				Devs::m_MotionModule;
#endif
bool						Devs::m_bEntry;

Devs::Devs()
{
#ifndef MIL_NOT_USE
	m_Camera6G_LT = NULL;
	m_Camera6G_RT = NULL;
	m_Camera6G_RB = NULL;
	m_Camera6G_LB = NULL;

	m_Camera8G_LT = NULL;
	m_Camera8G_RT = NULL;
	m_Camera8G_RB = NULL;
	m_Camera8G_LB = NULL;

	m_Camera10X		= NULL;
#endif

#if 0
	m_LightController	= NULL;
	m_Pua310 = NULL;
#endif
	m_bEntry = NULL;
}


Devs::~Devs()
{

}

void Devs::Initialize(void)
{
	CString strSfCom = _T("");
	CString strSfBaudRate = _T("");

#if 0
	m_LightController = new CWkLibBdc();
	m_LightController->CreateControl();

	//m_MappingProc.Init();

	strSfCom = _T("COM2");
	strSfBaudRate = _T("19200");
	m_LightController->Open(strSfCom, strSfBaudRate);
	
	if (!m_LightController->m_bIsOpenned)
	{

	}

	m_MotionModule.InitializeAcl();

	//Pau310
	m_Pua310 = new CWkLibPua310();
	m_Pua310->CreateControl();
#endif
	
	m_MappingProc.Init();

	//CimMotion.InitProcess();

#pragma region //Motion InitProcess	
	//m_JogMotion.InitProcess();
	m_GantryMotion.InitProcess();
	m_ClampMotion.InitProcess();
	m_StretchMotion.InitProcess();
	m_GripperZMotion.InitProcess();
	m_InspectionStageMotion.InitProcess();
#pragma endregion

#pragma region //Flow InitProcess
	Devs::m_Origin_AllAxis_Flow.InitProcess();
#pragma endregion

	m_nStopMonitoringThread = 0;
	m_pMonitoringThread = AfxBeginThread(AppMonitoringThreadProc, 0, THREAD_PRIORITY_ABOVE_NORMAL, 0, CREATE_SUSPENDED);
	Sleep(100);
	m_pMonitoringThread->ResumeThread();

}

void Devs::Finalize(void)
{
	if (m_nIsRunningMonitoringThread)
	{
		m_nStopMonitoringThread = TRUE;
		do
		{
			Sleep(100);
		} while (m_nIsRunningMonitoringThread);
	}

	//CIM
	//CimMotion.EndProcess();

#pragma region //Motion EndProcess
	//m_JogMotion.EndProcess();
	m_GantryMotion.EndProcess();
	m_ClampMotion.EndProcess();
	m_StretchMotion.EndProcess();
	m_GripperZMotion.EndProcess();
	m_InspectionStageMotion.EndProcess();
#pragma endregion

#pragma region //Flow EndProcess
	Devs::m_Origin_AllAxis_Flow.EndProcess();
#pragma endregion

#if 0
	if (m_LightController != NULL) delete m_LightController;

	if (m_Pua310 != NULL)
	{
		m_Pua310->DestroyWindow();
		delete m_Pua310;
	}
#endif
}

void Devs::Reset(void)
{
	
}

void Devs::StopAll(void)
{
	m_JogMotion.StopAll();
}

VOID Devs::MachineStateCheck(void)
{
	//SharedInfo::Active.ProcessMain = Devs::AutoRunState.GetFinal();

	SharedInfo::MachineState.nMainStep = GetMainStep();

	if (SharedInfo::MachineState.nMainStep <= 0)
	{
		SharedInfo::MachineState.bAutoRunFlag = FALSE;
	}
	else
	{
		SharedInfo::MachineState.bAutoRunFlag = TRUE;
	}

	SharedInfo::MachineState.nSubStep = Devs::GetSubStep();
	if (SharedInfo::MachineState.nSubStep <= 1) //0
	{
		SharedInfo::MachineState.bSemiAutoRunFlag = FALSE;
	}
	else
	{
		SharedInfo::MachineState.bSemiAutoRunFlag = TRUE;
	}

#pragma region //KJT 20210321 CIM
	if (SharedInfo::MachineState.bErrorFlag)
		SharedInfo::m_nCurMachineState = eMACHINE_STATUS_BM;
	else if (SharedInfo::MachineState.bAutoRunFlag || SharedInfo::MachineState.bSemiAutoRunFlag)
		SharedInfo::m_nCurMachineState = eMACHINE_STATUS_RUN;

	if (SharedInfo::m_nPrevMachineState != SharedInfo::m_nCurMachineState)
	{
		if (SharedInfo::m_nCurMachineState == eMACHINE_STATUS_RUN)
			Devs::MachineStatusChange(eMACHINE_STATUS_RUN);
		else if (SharedInfo::m_nCurMachineState == eMACHINE_STATUS_IDLE)
			Devs::MachineStatusChange(eMACHINE_STATUS_IDLE);
		else if (SharedInfo::m_nCurMachineState == eMACHINE_STATUS_PAUSE)
			Devs::MachineStatusChange(eMACHINE_STATUS_PAUSE);
		if (SharedInfo::m_nCurMachineState == eMACHINE_STATUS_BM)
			Devs::MachineStatusChange(eMACHINE_STATUS_BM);
		else if (SharedInfo::m_nCurMachineState == eMACHINE_STATUS_PM)
			Devs::MachineStatusChange(eMACHINE_STATUS_PM);
	}
	SharedInfo::m_nPrevMachineState = SharedInfo::m_nCurMachineState;
#pragma endregion
}

INT Devs::GetMainStep()
{
	//if (m_AutoRunFlow.GetCurrentFlowStep() > 0) return m_AutoRunFlow.GetCurrentFlowStep(); //KJT 20210310

	return -1;
}

INT Devs::GetSubStep()
{
	if (m_Origin_AllAxis_Flow.GetCurrentFlowStep() > 0) return m_Origin_AllAxis_Flow.GetCurrentFlowStep();
	if (m_GantryMotion.GetCurrentFlowStep() > 0)		return m_GantryMotion.GetCurrentFlowStep();
	if (m_ClampMotion.GetCurrentFlowStep() > 0)		return m_ClampMotion.GetCurrentFlowStep();
	if (m_StretchMotion.GetCurrentFlowStep() > 0)		return m_StretchMotion.GetCurrentFlowStep();
	if (m_GripperZMotion.GetCurrentFlowStep() > 0)		return m_GripperZMotion.GetCurrentFlowStep();
	if (m_InspectionStageMotion.GetCurrentFlowStep() > 0)		return m_InspectionStageMotion.GetCurrentFlowStep();

	return -1;
}

UINT AppMonitoringThreadProc(LPVOID lpParam)
{
#if 0
	CVisionAgentDlg *pVisionAgentDlg;
	pVisionAgentDlg = (CVisionAgentDlg *)AfxGetMainWnd();
#endif
	DOUBLE dX = 0, dY = 0;
	WORD wTest = 0;
	int i = 0;
	BOOL bFlag[MAX_AUTO_DELETE_DIR_PATH] = { FALSE, };

	Devs::m_nIsRunningMonitoringThread = 1;

	CString strRoot, strDir;
	int nStoreDays = 1;
	int nMachineRunStatus = 0, nPrevMachineRunStatus = -1;
	while (!Devs::m_nStopMonitoringThread)
	{
		if (!Devs::m_bEntry)
		{
			Sleep(1000);
			continue;
		}
		if (SharedInfo::MachineState.bAutoRunFlag || SharedInfo::MachineState.bSemiAutoRunFlag)
			nMachineRunStatus = 1;
		else
			nMachineRunStatus = 0;

		if (nMachineRunStatus == 0 && nPrevMachineRunStatus != nMachineRunStatus)
		{
			if (CSystemData::m_Other.Info.m_bAutoDeleteDirPathUse[0] && bFlag[0] == FALSE) //Log
			{
				bFlag[0] = TRUE;

				nStoreDays = CSystemData::m_Other.Info.m_nFileStoreDays[0];

				strRoot.Format(_T("%s\\Log\\Alarm\\"), SharedInfo::VisionAgentPath);
				strDir.Format(_T("%s\\Log\\Alarm\\*.*"), SharedInfo::VisionAgentPath);
				SharedInfo::DeleteDirectory(strRoot, strDir, nStoreDays);

				strRoot.Format(_T("%s\\Log\\Etc\\"), SharedInfo::VisionAgentPath);
				strDir.Format(_T("%s\\Log\\Etc\\*.*"), SharedInfo::VisionAgentPath);
				SharedInfo::DeleteDirectory(strRoot, strDir, nStoreDays);

				strRoot.Format(_T("%s\\Log\\Process\\"), SharedInfo::VisionAgentPath);
				strDir.Format(_T("%s\\Log\\Process\\*.*"), SharedInfo::VisionAgentPath);
				SharedInfo::DeleteDirectory(strRoot, strDir, nStoreDays);

				strRoot.Format(_T("%s\\Log\\System\\"), SharedInfo::VisionAgentPath);
				strDir.Format(_T("%s\\Log\\System\\*.*"), SharedInfo::VisionAgentPath);
				SharedInfo::DeleteDirectory(strRoot, strDir, nStoreDays);

				strRoot.Format(_T("%s\\Log\\Total\\"), SharedInfo::VisionAgentPath);
				strDir.Format(_T("%s\\Log\\Total\\*.*"), SharedInfo::VisionAgentPath);
				SharedInfo::DeleteDirectory(strRoot, strDir, nStoreDays);

				strRoot.Format(_T("%s\\Log\\Vision\\"), SharedInfo::VisionAgentPath);
				strDir.Format(_T("%s\\Log\\Vision\\*.*"), SharedInfo::VisionAgentPath);
				SharedInfo::DeleteDirectory(strRoot, strDir, nStoreDays);

				//Total_Msg(_T("[Auto Delete File] Log Files"));

				bFlag[0] = FALSE;
			}
			if (CSystemData::m_Other.Info.m_bAutoDeleteDirPathUse[1] && bFlag[1] == FALSE) //Result Csv
			{
				bFlag[1] = TRUE;

				nStoreDays = CSystemData::m_Other.Info.m_nFileStoreDays[1];

				strRoot.Format(_T("%s\\Result\\AOI\\Defect"), SharedInfo::VisionAgentPath);
				strDir.Format(_T("%s\\Result\\AOI\\Defect\\*.*"), SharedInfo::VisionAgentPath);
				SharedInfo::DeleteDirectory(strRoot, strDir, nStoreDays);

				strRoot.Format(_T("%s\\Result\\AtPpa\\"), SharedInfo::VisionAgentPath);
				strDir.Format(_T("%s\\Result\\AtPpa\\*.*"), SharedInfo::VisionAgentPath);
				SharedInfo::DeleteDirectory(strRoot, strDir, nStoreDays);

				strRoot.Format(_T("%s\\Result\\DepoHole\\"), SharedInfo::VisionAgentPath);
				strDir.Format(_T("%s\\Result\\DepoHole\\*.*"), SharedInfo::VisionAgentPath);
				SharedInfo::DeleteDirectory(strRoot, strDir, nStoreDays);

				strRoot.Format(_T("%s\\Result\\3D\\3D_Gradient\\"), SharedInfo::VisionAgentPath);
				strDir.Format(_T("%s\\Result\\3D\\3D_Gradient\\*.*"), SharedInfo::VisionAgentPath);
				SharedInfo::DeleteDirectory(strRoot, strDir, nStoreDays);

				strRoot.Format(_T("%s\\Result\\3D\\3D_Depth\\"), SharedInfo::VisionAgentPath);
				strDir.Format(_T("%s\\Result\\3D\\3D_Depth\\*.*"), SharedInfo::VisionAgentPath);
				SharedInfo::DeleteDirectory(strRoot, strDir, nStoreDays);

				strRoot.Format(_T("%s\\Result\\Flatness\\"), SharedInfo::VisionAgentPath);
				strDir.Format(_T("%s\\Result\\Flatness\\*.*"), SharedInfo::VisionAgentPath);
				SharedInfo::DeleteDirectory(strRoot, strDir, nStoreDays);

				strRoot.Format(_T("%s\\Result\\HalfEdge\\"), SharedInfo::VisionAgentPath);
				strDir.Format(_T("%s\\Result\\HalfEdge\\*.*"), SharedInfo::VisionAgentPath);
				SharedInfo::DeleteDirectory(strRoot, strDir, nStoreDays);

				strRoot.Format(_T("%s\\Result\\Inspect\\"), SharedInfo::VisionAgentPath);
				strDir.Format(_T("%s\\Result\\Inspect\\*.*"), SharedInfo::VisionAgentPath);
				SharedInfo::DeleteDirectory(strRoot, strDir, nStoreDays);

				strRoot.Format(_T("%s\\Result\\MeasureCd\\"), SharedInfo::VisionAgentPath);
				strDir.Format(_T("%s\\Result\\MeasureCd\\*.*"), SharedInfo::VisionAgentPath);
				SharedInfo::DeleteDirectory(strRoot, strDir, nStoreDays);

				strRoot.Format(_T("%s\\Result\\NormalPpa\\"), SharedInfo::VisionAgentPath);
				strDir.Format(_T("%s\\Result\\NormalPpa\\*.*"), SharedInfo::VisionAgentPath);
				SharedInfo::DeleteDirectory(strRoot, strDir, nStoreDays);

				strRoot.Format(_T("%s\\Result\\Repeat\\"), SharedInfo::VisionAgentPath);
				strDir.Format(_T("%s\\Result\\Repeat\\*.*"), SharedInfo::VisionAgentPath);
				SharedInfo::DeleteDirectory(strRoot, strDir, nStoreDays);

				strRoot.Format(_T("%s\\Result\\CameraCal\\"), SharedInfo::VisionAgentPath);
				strDir.Format(_T("%s\\Result\\CameraCal\\*.*"), SharedInfo::VisionAgentPath);
				SharedInfo::DeleteDirectory(strRoot, strDir, nStoreDays);

				strRoot.Format(_T("%s\\Result\\DFS\\"), SharedInfo::VisionAgentPath); //KJT 20210701
				strDir.Format(_T("%s\\Result\\DFS\\*.*"), SharedInfo::VisionAgentPath);
				SharedInfo::DeleteDirectory(strRoot, strDir, nStoreDays);

				//Total_Msg(_T("[Auto Delete File] Result Files"));

				bFlag[1] = FALSE;
			}
			if (CSystemData::m_Other.Info.m_bAutoDeleteDirPathUse[2] && bFlag[2] == FALSE) //Save Image
			{
				bFlag[2] = TRUE;

				nStoreDays = CSystemData::m_Other.Info.m_nFileStoreDays[2];

				strRoot.Format(_T("%s\\3D\\"), SharedInfo::STR_SAVE_IMAGE_DIR_PATH);
				strDir.Format(_T("%s\\3D\\*.*"), SharedInfo::STR_SAVE_IMAGE_DIR_PATH);
				SharedInfo::DeleteDirectory(strRoot, strDir, nStoreDays);

				strRoot.Format(_T("%s\\AOI\\Defect\\"), SharedInfo::STR_SAVE_IMAGE_DIR_PATH);
				strDir.Format(_T("%s\\AOI\\Defect\\*.*"), SharedInfo::STR_SAVE_IMAGE_DIR_PATH);
				SharedInfo::DeleteDirectory(strRoot, strDir, nStoreDays);

				strRoot.Format(_T("%s\\AOI\\Review\\"), SharedInfo::STR_SAVE_IMAGE_DIR_PATH);
				strDir.Format(_T("%s\\AOI\\Review\\*.*"), SharedInfo::STR_SAVE_IMAGE_DIR_PATH);
				SharedInfo::DeleteDirectory(strRoot, strDir, nStoreDays);

				strRoot.Format(_T("%s\\GrabError\\"), SharedInfo::STR_SAVE_IMAGE_DIR_PATH);
				strDir.Format(_T("%s\\GrabError\\*.*"), SharedInfo::STR_SAVE_IMAGE_DIR_PATH);
				SharedInfo::DeleteDirectory(strRoot, strDir, nStoreDays);

				strRoot.Format(_T("%s\\GrabError\\CameraCal\\"), SharedInfo::STR_SAVE_IMAGE_DIR_PATH);
				strDir.Format(_T("%s\\GrabError\\CameraCal\\*.*"), SharedInfo::STR_SAVE_IMAGE_DIR_PATH);
				SharedInfo::DeleteDirectory(strRoot, strDir, nStoreDays);

				strRoot.Format(_T("%s\\GrabError\\Mapping\\"), SharedInfo::STR_SAVE_IMAGE_DIR_PATH);
				strDir.Format(_T("%s\\GrabError\\Mapping\\*.*"), SharedInfo::STR_SAVE_IMAGE_DIR_PATH);
				SharedInfo::DeleteDirectory(strRoot, strDir, nStoreDays);

				strRoot.Format(_T("%s\\GrabError\\Depo\\"), SharedInfo::STR_SAVE_IMAGE_DIR_PATH);
				strDir.Format(_T("%s\\GrabError\\Depo\\*.*"), SharedInfo::STR_SAVE_IMAGE_DIR_PATH);
				SharedInfo::DeleteDirectory(strRoot, strDir, nStoreDays);

				//strRoot.Format(_T("%s\\Mapping\\"), SharedInfo::STR_SAVE_IMAGE_DIR_PATH);
				//strDir.Format(_T("%s\\Mapping\\*.*"), SharedInfo::STR_SAVE_IMAGE_DIR_PATH);
				//SharedInfo::DeleteDirectory(strRoot, strDir, nStoreDays);

				//strRoot.Format(_T("%s\\Repeat\\"), SharedInfo::STR_SAVE_IMAGE_DIR_PATH);
				//strDir.Format(_T("%s\\Repeat\\*.*"), SharedInfo::STR_SAVE_IMAGE_DIR_PATH);
				//SharedInfo::DeleteDirectory(strRoot, strDir, nStoreDays);

				//Total_Msg(_T("[Auto Delete File] Save Image Files"));

				bFlag[2] = FALSE;
			}
		}
		nPrevMachineRunStatus = nMachineRunStatus;

		Sleep(1000);
	}

	Devs::m_nIsRunningMonitoringThread = 0;
	//	GetWindowRect
	return 0;
}

CString Devs::FindCurrentRecipeName(int nRecipeID)
{	
	CString szMsg;
	szMsg.Format(_T("%S"), CimInfo::m_MachineRecipeTable.strRecipeName[nRecipeID]);
	return szMsg;
}
int Devs::FindCurrentRecipeID(CString strRecipeName)
{
	CString szMsgCmp;
	for (int i = 0; i < MAX_RECIPE_COUNT; i++)
	{
		if (CimInfo::m_MachineRecipeTable.bRecipeTableUseFlag[i] == TRUE)
		{
			szMsgCmp.Format(_T("%S"), CimInfo::m_MachineRecipeTable.strRecipeName[i]);
			if (szMsgCmp == strRecipeName)
			{
				return CimInfo::m_MachineRecipeTable.wRecipeID[i];
			}
		}
	}
	return -1;
}


int Devs::FindRecipeID(WORD wRecipeID)
{
	for (int i = 0; i < MAX_RECIPE_COUNT; i++)
	{
		if (CimInfo::m_MachineRecipeTable.bRecipeTableUseFlag[i] == TRUE)
		{

			if (CimInfo::m_MachineRecipeTable.wRecipeID[i] == wRecipeID)
			{
				return i;
			}
		}
	}
	return -1;
}

BOOL Devs::GetIsAlignSitck(int nRecipeID)
{	
	if (CimInfo::m_MachineRecipeTable.bIsAlignStick[nRecipeID] == TRUE)
		return TRUE;
	else
		return FALSE;
}

BOOL Devs::DuplicateModelNameCheck(CString strRecipeName) //KJT 20210410
{
	CString szMsgCmp;
	for (int i = 0; i < MAX_RECIPE_COUNT; i++)
	{
		if (CimInfo::m_MachineRecipeTable.bRecipeTableUseFlag[i] == TRUE)
		{
			szMsgCmp.Format(_T("%S"), CimInfo::m_MachineRecipeTable.strRecipeName[i]);
			if (szMsgCmp == strRecipeName)
			{
				return FALSE;
			}
		}
	}
	return TRUE;
}