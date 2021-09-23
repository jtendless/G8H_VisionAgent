#include "stdafx.h"
#include "SharedInfo.h"
#include "Data/ModelData.h"
#include "Data/ManualData.h"
#include "Data/MachineData.h"
#include "Data/SystemData.h"
#include "Devs.h"
#include "VisionAgentAlarmDlg.h"
#include "CIM/CimInfo.h"

//!
//! File path constants 
//!
LPCTSTR SharedInfo::STR_MODEL_PARA_FILE_DIR = _T("Data\\Model");
LPCTSTR SharedInfo::STR_INSPECT_PARA_FILE_DIR = _T("Data\\Inspect");

LPCTSTR SharedInfo::STR_ALARM_LIST_FILE_PATH = _T("Data\\Alarm\\Alarm.Txt");

LPCTSTR SharedInfo::STR_SYSTEM_FILE_PATH = _T("Data\\System\\system.xml");
LPCTSTR SharedInfo::STR_VELOCITY_PARA_FILE_PATH = _T("Data\\System\\VelocityPara.Txt");

CString SharedInfo::AllPPAPath;

CString SharedInfo::VisionAgentPath;			//!< the location of executable.

#pragma region //Label
LPCTSTR SharedInfo::STR_DATA_LABEL_AXIS = _T("Data\\Label\\AxisLabel.Txt");
LPCTSTR SharedInfo::STR_DATA_LABEL_DINPUT = _T("Data\\Label\\DInputLabel.Txt");
LPCTSTR SharedInfo::STR_DATA_LABEL_DOUTPUT = _T("Data\\Label\\DOutputLabel.Txt");
LPCTSTR SharedInfo::STR_DATA_LABEL_AINPUT = _T("Data\\Label\\AInputLabel.Txt");
LPCTSTR SharedInfo::STR_DATA_LABEL_AOUTPUT = _T("Data\\Label\\AOutputLabel.Txt");
#pragma endregion

CString SharedInfo::STR_SAVE_IMAGE_DIR_PATH = _T("D:\\SAVE_IMAGE");
CString SharedInfo::STR_AOI_DEFECT_INFO_FILE_PATH = _T("D:\\SAVE_IMAGE\\AOI\\Defect");
CString SharedInfo::STR_AOI_DEFECT_REVIEW_PATH = _T("D:\\SAVE_IMAGE\\AOI\\Review");
CString SharedInfo::STR_3D_INSPECTION_IMAGE_PATH = _T("D:\\SAVE_IMAGE\\3D");

ACTIVE_STATE			SharedInfo::Active;
CURRENT_STATE			SharedInfo::MachineState;
//MACHINE_RECIPE_TABLE	SharedInfo::m_MachineCameraRecipeTable;
RESULT_STATE			SharedInfo::Result;

ALIGN_CENTER_DIFF_INFO			SharedInfo::AlignCenterDiffInfo;

CStringArray			SharedInfo::m_strModelNames;

enum_Axis SharedInfo::m_eAxisJog;
INT SharedInfo::m_nJogDir;
int SharedInfo::m_eAxisJogInterlock;
INT SharedInfo::m_nJogInterlockDir;

double  SharedInfo::dStretchCmdPos[MAX_STRETCH_AXIS_SIZE];//Left, Right
double  SharedInfo::dStretchCmdVel[MAX_STRETCH_AXIS_SIZE];//Left, Right
double  SharedInfo::dStretchValue[MAX_STRETCH_AXIS_SIZE];//Left, Right
double  SharedInfo::dStretchTargetValue[MAX_STRETCH_AXIS_SIZE];//Left, Right
int SharedInfo::nStretchStatus[MAX_STRETCH_AXIS_SIZE];

//clamp
double SharedInfo::m_nClampTorquedMonitorValue[MAX_STRETCH_AXIS_SIZE];
double SharedInfo::dSF_LoadcellForce[MAX_SF_NUM];

double SharedInfo::dVisionoffsetX[2];
double	SharedInfo::AlignCamMarkPixelSize[2];
double	SharedInfo::AlignCamMarkPos[2];
int		SharedInfo::AlignCamMarkCD[2];
double		SharedInfo::AlignCamScore;
BOOL	SharedInfo::bResult;

BOOL	SharedInfo::bAlignVisionReceiveFlag;

BOOL SharedInfo::bAlignVisionSetLightFlag;
BOOL SharedInfo::bAlignVisionLightOnFlag;

//Machine Stop Flag - parkcm
BOOL SharedInfo::bMachineStopFlag;

DIRECT_AXIS_HOME			SharedInfo::DirectAixsHome;
//Flow State  저장 관련 - parkcm
int SharedInfo::nCurFlowID;
int SharedInfo::nCurFlowStep;
enum_Flow SharedInfo::nPrevFlowID = eBOX_ALIGN_FLOW; //KJT 20210325

PPA_POS *SharedInfo::m_pPpaResult;

double SharedInfo::dUVWTargetPos[2][3] = { 0.0, }; //KJT 20200912

enum_Camera_ViewMode SharedInfo::eCamViewMode = eCamView_6G;

BOOL SharedInfo::m_bAOIReqMoveProcessing = FALSE;

#pragma region //Repeat
REPEAT_TABLE SharedInfo::m_sRepeatTable[MAX_REPEAT_COUNT];
int			SharedInfo::m_nRepeatTableCnt;
int SharedInfo::m_nStopRepeatCnt;
int SharedInfo::m_nMoveRepeatCnt;
int SharedInfo::m_nRepeatCurPointIndex;
int SharedInfo::m_nMoveRepeatTarget;
int SharedInfo::m_nIsGlassMode;
#pragma endregion

FLATNESS_TABLE	SharedInfo::m_sFlatnessTable[MAX_FLATNESS_COUNT];
int				SharedInfo::m_nFlatnessLightCoaxial;
int				SharedInfo::m_nFlatnessLightRing;
int				SharedInfo::m_nFlatnessBackLight;
int				SharedInfo::m_nFlatnessTool;
int				SharedInfo::m_nFlatnessTableCnt;

#pragma region //Measurement Dlg Display
BOOL SharedInfo::bPreAlignGrabDone = FALSE;
BOOL SharedInfo::bMainAlignGrabDone = FALSE;
BOOL SharedInfo::bTegkey2PAlignGrabDone = FALSE;
BOOL SharedInfo::bMainEdgeAlignGrabDone = FALSE;

int SharedInfo::nVerticalAlignCurCount = 0;
int SharedInfo::nVerticalSwAlignCurCount = 0; //KJT 20210321
int SharedInfo::nRightAngleCurCount = 0;
int SharedInfo::nPreAlignCurCount = 0;
int SharedInfo::nMain2PAlignCurCount = 0;
int SharedInfo::nTegkey2PAlignCurCount = 0; //KJT 20210227
int SharedInfo::nMainEdge4PAlignCurCount = 0;
int SharedInfo::nSwAlignCurCount = 0; //KJT 20210304
int SharedInfo::nGlass4PAlignCurCount = 0; //KJT 20210314

double SharedInfo::dPreAlignVisionResultValue[2][2] = { { 0.0, 0.0 }, { 0.0, 0.0 } };
double SharedInfo::dMain2PAlignVisionResultValue[2][2] = { { 0.0, 0.0 }, { 0.0, 0.0 } };
double SharedInfo::dTegkey2PAlignVisionResultValue[2][2] = { { 0.0, 0.0 }, { 0.0, 0.0 } }; //KJT 20210227
double SharedInfo::dSwAlignVisionResultValue[2][4] = { { 0.0, 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0, 0.0 } }; //KJT 20210307
double SharedInfo::dMainEdge4PAlignVisionResultValue[2][4] = { { 0.0, 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0, 0.0 } };
#pragma endregion

double SharedInfo::dMain2PAlignResultShiftX[2] = { 0.0, 0.0 }; //KJT 20210421

BOOL SharedInfo::bTemperSend = FALSE; //KJT 2021038

int SharedInfo::m_nPrevMachineState = -1; //KJT 20210321
int SharedInfo::m_nCurMachineState = 0; //KJT 20210321

#if 0
int		SharedInfo::Umac_Axis_Home_Status[REMOTE_AXIS_UMAC_MAX];
int		SharedInfo::Umac_Axis_Home_Signal[REMOTE_AXIS_UMAC_MAX];
int		SharedInfo::Umac_Axis_PLimit_Signal[REMOTE_AXIS_UMAC_MAX];
int		SharedInfo::Umac_Axis_NLimit_Signal[REMOTE_AXIS_UMAC_MAX];
int		SharedInfo::Umac_Axis_ServoOn_Status[REMOTE_AXIS_UMAC_MAX];
int		SharedInfo::Umac_Axis_Alarm_Status[REMOTE_AXIS_UMAC_MAX];
int		SharedInfo::Umac_Axis_Isolator_Alarm;
int		SharedInfo::Umac_Axis_Status[REMOTE_AXIS_UMAC_MAX]; //0:HomeStatus, 1:ServoOnStatus, 2:AlarmStatus, 3:MotionDoneStatus
int		SharedInfo::Umac_Axis_InMotion_Status[REMOTE_AXIS_UMAC_MAX];
double	SharedInfo::Umac_Axis_Cmd_Pos[REMOTE_AXIS_UMAC_MAX];
double	SharedInfo::Umac_Axis_Act_Pos[REMOTE_AXIS_UMAC_MAX];
double	SharedInfo::Umac_Axis_Cmd_Vel[REMOTE_AXIS_UMAC_MAX];

// Ajin Axis

int		SharedInfo::Ajin_Axis_HomeStatus[REMOTE_AXIS_MAX];
int		SharedInfo::Ajin_Axis_HomeSignal[REMOTE_AXIS_MAX];
int		SharedInfo::Ajin_Axis_PLimitSignal[REMOTE_AXIS_MAX];
int		SharedInfo::Ajin_Axis_NLimitSignal[REMOTE_AXIS_MAX];
int		SharedInfo::Ajin_Axis_ServoOnStatus[REMOTE_AXIS_MAX];
int		SharedInfo::Ajin_Axis_AlarmStatus[REMOTE_AXIS_MAX];
int		SharedInfo::Ajin_Axis_InMotionStatus[REMOTE_AXIS_MAX];
int		SharedInfo::Ajin_Axis_Status[REMOTE_AXIS_MAX]; //0:HomeStatus, 1:ServoOnStatus, 2:AlarmStatus, 3:MotionDoneStatus
double	SharedInfo::Ajin_Axis_Cmd_Pos[REMOTE_AXIS_MAX];
double	SharedInfo::Ajin_Axis_Act_Pos[REMOTE_AXIS_MAX];
double	SharedInfo::Ajin_Axis_Cmd_Vel[REMOTE_AXIS_MAX];
#endif

double SharedInfo::m_dLaserDispVal;

double SharedInfo::m_dAutoFocusStartPosZ;

int SharedInfo::MotionAgentAXLOpen;
int SharedInfo::MaxAxisSize;
int SharedInfo::MaxDInputSize;
int SharedInfo::MaxDOutputSize;
int SharedInfo::MaxAInputSize;
int SharedInfo::MaxAOutputSize;

//! Common
int SharedInfo::SystemHomeStatus;
int SharedInfo::SystemHomeSignal;
int SharedInfo::SystemNLimitSignal;
int SharedInfo::SystemPLimitSignal;
int SharedInfo::SystemServoOnStatus;
int SharedInfo::SystemAlarmStatus;
int SharedInfo::SystemMotionDoneStatus;
int SharedInfo::SystemStatus; //0:HomeStatus, 1:ServoOnStatus, 2:AlarmStatus, 3:MotionDoneStatus

//Common
int SharedInfo::UmacOriginIngStatus[REMOTE_AXIS_UMAC_MAX];
int SharedInfo::RemoteAjinOriginIngStatus[MAX_AXIS_SIZE];
int SharedInfo::DirectAjinOriginIngStatus[DIRECT_AXIS_MAX];

//! Ajin
int	SharedInfo::Is_Ajin_Open;
int SharedInfo::AxisHomeResult[MAX_AXIS_SIZE];
int SharedInfo::AxisHomeStatus[MAX_AXIS_SIZE];
int SharedInfo::AxisHomeSignal[MAX_AXIS_SIZE];
int SharedInfo::AxisPLimitSignal[MAX_AXIS_SIZE];
int SharedInfo::AxisNLimitSignal[MAX_AXIS_SIZE];
int SharedInfo::AxisServoOnStatus[MAX_AXIS_SIZE];
int SharedInfo::AxisAlarmStatus[MAX_AXIS_SIZE];
int SharedInfo::AxisInMotionStatus[MAX_AXIS_SIZE];	// 0:End Move, 1:Moving
int SharedInfo::AxisStatus[MAX_AXIS_SIZE];	//0:HomeStatus, 1:ServoOnStatus, 2:AlarmStatus, 3:MotionDoneStatus
double SharedInfo::AxisCmdPos[MAX_AXIS_SIZE];
double SharedInfo::AxisActPos[MAX_AXIS_SIZE];	// wkoh 추가
double SharedInfo::AxisCmdVel[MAX_AXIS_SIZE];
double SharedInfo::AxisTorque[MAX_AXIS_SIZE];

//! Umac
int SharedInfo::Is_Umac_Open;
int SharedInfo::Umac_Isolator_Alarm; //KJT 20200812
int SharedInfo::UmacHomeStatus[MAX_UMAC_AXIS_SIZE];
int SharedInfo::UmacHomeSignal[MAX_UMAC_AXIS_SIZE];
int SharedInfo::UmacPLimitSignal[MAX_UMAC_AXIS_SIZE];
int SharedInfo::UmacNLimitSignal[MAX_UMAC_AXIS_SIZE];
int SharedInfo::UmacServoOnStatus[MAX_UMAC_AXIS_SIZE];
int SharedInfo::UmacAlarmStatus[MAX_UMAC_AXIS_SIZE];
int SharedInfo::UmacInMotionStatus[MAX_UMAC_AXIS_SIZE];
int SharedInfo::UmacStatus[MAX_UMAC_AXIS_SIZE];	//0:HomeStatus, 1:ServoOnStatus, 2:AlarmStatus, 3:MotionDoneStatus
double SharedInfo::UmacCmdPos[MAX_UMAC_AXIS_SIZE];
double SharedInfo::UmacActPos[MAX_UMAC_AXIS_SIZE];
double SharedInfo::UmacCmdVel[MAX_UMAC_AXIS_SIZE];
double SharedInfo::UmacTorque[MAX_UMAC_AXIS_SIZE];

//! VisionAgent 직접 제어 축
int SharedInfo::VisionAxisHomeResult[DIRECT_AXIS_MAX];
int SharedInfo::VisionAxisHomeStatus[DIRECT_AXIS_MAX];
int SharedInfo::VisionAxisHomeSignal[DIRECT_AXIS_MAX];
int SharedInfo::VisionAxisPLimitSignal[DIRECT_AXIS_MAX];
int SharedInfo::VisionAxisNLimitSignal[DIRECT_AXIS_MAX];
int SharedInfo::VisionAxisServoOnStatus[DIRECT_AXIS_MAX];
int SharedInfo::VisionAxisAlarmStatus[DIRECT_AXIS_MAX];
int SharedInfo::VisionAxisInMotionStatus[DIRECT_AXIS_MAX];	// 0:End Move, 1:Moving
int SharedInfo::VisionAxisStatus[DIRECT_AXIS_MAX];	//0:HomeStatus, 1:ServoOnStatus, 2:AlarmStatus, 3:MotionDoneStatus
double SharedInfo::VisionAxisCmdPos[DIRECT_AXIS_MAX]; //
double SharedInfo::VisionAxisActPos[DIRECT_AXIS_MAX];
double SharedInfo::VisionAxisCmdVel[DIRECT_AXIS_MAX];
double SharedInfo::VisionAxisTorque[DIRECT_AXIS_MAX];

#pragma region //20201030 KJT Add
#ifndef SIM_MODE
BOOL SharedInfo::bRemoteAjinSystemReadyStatus = FALSE; 
BOOL SharedInfo::bRemoteUmacSystemReadyStatus = FALSE;
BOOL SharedInfo::bDirectAjinSystemReadyStatus = FALSE;
#else
BOOL SharedInfo::bRemoteAjinSystemReadyStatus = TRUE;
BOOL SharedInfo::bRemoteUmacSystemReadyStatus = TRUE;
BOOL SharedInfo::bDirectAjinSystemReadyStatus = TRUE;
#endif
#pragma endregion

//! Dio
int SharedInfo::DInputValue[_DIN_MAX];	//MAX_DINPUT_SIZE
int SharedInfo::DOutputValue[_DOUT_MAX]; //MAX_DOUTPUT_SIZE
DWORD SharedInfo::DInputDWordValue[MAX_DINPUT_DWORD_SIZE];
DWORD SharedInfo::DOutputDWordValue[MAX_DOUTPUT_DWORD_SIZE];

//! Aio
double SharedInfo::AInputValue[MAX_AINPUT_SIZE] = { 0.0, };
double SharedInfo::AOutputValue[MAX_AOUTPUT_SIZE] = { 0.0, };

//! UVW
double SharedInfo::UvwCmdPos[MAX_UVW][3];
double SharedInfo::UvwCmdVel[MAX_UVW][3];
int SharedInfo::UvwHomeStatus[MAX_UVW];
int SharedInfo::UvwServoOnStatus[MAX_UVW];
int SharedInfo::UvwAlarmStatus[MAX_UVW];
int SharedInfo::UvwMotionDoneStatus[MAX_UVW];
int SharedInfo::UvwStatus[MAX_UVW];	//0:HomeStatus, 1:ServoOnStatus, 2:AlarmStatus, 3:MotionDoneStatus

//////////Mapping
int SharedInfo::m_nMaxMappingCountX;
int SharedInfo::m_nMaxMappingCountY;
int	SharedInfo::m_nMappingTableCnt;
MAPPING_TABLE SharedInfo::m_sMappingTable[MAX_GLASS_MAPPING_COUNT];

//////////Camera Cal //KJT 20210525
int			SharedInfo::m_nCameraCalTableCnt;
CAMERA_CAL_TABLE SharedInfo::m_CameraCalTable[MAX_CAMERA_CAL_COUNT];

//Clamp
double SharedInfo::dClampValue[eGRIPPER_ROW_MAX];//Left, Right
int SharedInfo::nClampStatus[eGRIPPER_ROW_MAX];//Left, Right
int SharedInfo::nClampAllUnClampStatus;
int SharedInfo::nClampAlarmStatus;

CString SharedInfo::m_DInputName[MAX_DINPUT_SIZE] = { _T(""), };
CString SharedInfo::m_DOutputName[MAX_DOUTPUT_SIZE] = { _T(""), };
CString SharedInfo::m_AInputName[MAX_AINPUT_SIZE] = { _T(""), };
CString SharedInfo::m_AOutputName[MAX_AOUTPUT_SIZE] = { _T(""), };

#pragma region //CIM
WORD SharedInfo::m_AlarmCount = 0;
WORD SharedInfo::m_AlarmMaxPos = 0;
WORD SharedInfo::m_AlarmCmdPos = 0;
INT	  SharedInfo::m_nCmd = 0;


WORD SharedInfo::OperatorID[10];
int SharedInfo::MachinMode;
int SharedInfo::m_nOtherAlarm[10];
int SharedInfo::MachineAutoMode; //KJT 20210324

BOOL SharedInfo::bBuzzerNotUse = FALSE; //KJT 20210225

void SharedInfo::DfsInfoSave()
{
	CFile File;
	CString szMsg;
	szMsg.Format(_T("%s\\dat\\DfsInfo.dat"), SharedInfo::VisionAgentPath);
	File.Open(szMsg, CFile::modeCreate | CFile::modeWrite);
	//File.Write(&CimInfo::m_sDfsPara, sizeof(DFS_PARA));
	File.Close();

}
void SharedInfo::DfsInfoRead()
{
	CFile File;
	CString szMsg;
	szMsg.Format(_T("%s\\dat\\DfsInfo.dat"), SharedInfo::VisionAgentPath);
	if (File.Open(szMsg, CFile::modeRead) == FALSE)
		File.Open(szMsg, CFile::modeRead | CFile::modeCreate);
	//File.Read(&CimInfo::m_sDfsPara, sizeof(DFS_PARA));
	File.Close();

}
TCHAR* SharedInfo::GetDfsFolderDir(CString strFileName)
{
	TCHAR tTemp[1024] = _T("");
	TCHAR tTemp1[10] = _T("");
	TCHAR tTemp2[10] = _T("");
	TCHAR tTemp3[10] = _T("");
	TCHAR tTemp4[10] = _T("");
	TCHAR tTemp5[10] = _T("");
	TCHAR tTempStep[10] = _T("");

#ifdef SIM_MODE
	//Mask/Data/E63000N/6599F/BE/A/001/Test.bmp
	memcpy(tTempStep, CimInfo::m_sDfsPara.strStepId, 8);
	memcpy(tTemp1, CimInfo::m_sDfsPara.strFrameId, 10);
	memcpy(tTemp2, CimInfo::m_sDfsPara.strFrameId + 5, 4);
	memcpy(tTemp3, CimInfo::m_sDfsPara.strFrameId + 7, 2);
	memcpy(tTemp4, CimInfo::m_sDfsPara.strFrameId + 8, 6);

#else
	//memcpy(tTempStep, CimInfo::m_sDfsPara.strStepId, 8);
	memcpy(tTemp1, SharedInfo::Active.strFrameName, 10);
	memcpy(tTemp2, SharedInfo::Active.strFrameName + 5, 4);
	memcpy(tTemp3, SharedInfo::Active.strFrameName + 7, 2);
	memcpy(tTemp4, SharedInfo::Active.strFrameName + 8, 6);
#endif

	if (SharedInfo::Active.MachineMode == eMACHINE_MODE_REPAIR)
	{
		wsprintf(tTemp, _T("//Mask/Data/%04sMRR/%04s/%02s/%01s/%03s/%s"),
			tTempStep,
			tTemp1,
			tTemp2,
			tTemp3,
			tTemp4,
			strFileName);
	}
	else
	{
		wsprintf(tTemp, _T("//Mask/Data/%04s00N/%04s/%02s/%01s/%03s/%s"),
			tTempStep,
			tTemp1,
			tTemp2,
			tTemp3,
			tTemp4,
			strFileName);
	}

	return tTemp;
}
TCHAR* SharedInfo::GetDfsFileName(CString strFileName)
{
	TCHAR tTemp[1024] = _T("");
	CString strDate = _T("");
	CString strSheetNum = _T("");


	//파일 저장 Path.
	SYSTEMTIME st;

	GetLocalTime(&st);
	TCHAR	exepath[MAX_PATH];
	GetModuleFileName(NULL, exepath, sizeof(exepath));

	strDate.Format(_T("%04d%02d%02d%02d%02d%02d"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

#ifdef SIM_MODE
	wsprintf(tTemp, _T("%sIQC_%s_[%s][%s]%s"),
		CimInfo::m_sDfsPara.strUnitId,
		strDate,
		SharedInfo::FindRecipeName(SharedInfo::Active.nActiveRecipeNum), //KJT 20210329
		CimInfo::m_sDfsPara.strFrameId,
		strFileName);
#else
	//wsprintf(tTemp, _T("%sIQC_%s_[%s][%s]%s"),
	//	CimInfo::m_sDfsPara.strUnitId,
	//	strDate,
	//	SharedInfo::FindRecipeName(SharedInfo::Active.nActiveRecipeNum), //KJT 20210329
	//	SharedInfo::Active.strFrameName,
	//	strFileName);
#endif
	return tTemp;
}
#pragma endregion

int  SharedInfo::nAutoFocusCameraMode;

//Tempur
int		SharedInfo::TempurInterval;
//Laser Value
double SharedInfo::m_dLaserDispFVal;
double SharedInfo::m_dLaserDispBVal;

ALARM_LIST SharedInfo::AlarmList[100];
int	SharedInfo::AlarmCount = 0;

BOOL DIRECT_AXIS_HOME::Save()
{
#if 0
	CString szMsg;
	CFile file;
	szMsg.Format(_T("%s\\Dat\\HomeStatus.Dat"), SharedInfo::GetExeFilePath());
	file.Open(szMsg, CFile::modeCreate | CFile::modeWrite);
	file.Write(&Info, sizeof(Info));
	file.Close();
#else //KJT 20210520 AWK
	CStdioFile OutFile;
	CString StrData, strPath;
	int i;
	strPath.Format(_T("%s"), SharedInfo::VisionAgentPath);
	strPath.AppendFormat(_T("\\Data\\"));
	::CreateDirectory(strPath, NULL);
	strPath.AppendFormat(_T("Axis_Data\\"));
	::CreateDirectory(strPath, NULL);
	strPath.AppendFormat(_T("Axis_Data_Temp.txt"));

	if (OutFile.Open(strPath, CFile::modeWrite | CFile::modeCreate | CFile::typeText) == FALSE)
		return FALSE;

	StrData.Format(_T("#BEGIN\n"));
	OutFile.WriteString(StrData);

	for (i = 0; i < DIRECT_AXIS_MAX; i++)
	{
		StrData.Format(_T("[COM_POS%d]\t%.5f\n"), i, SharedInfo::VisionAxisCmdPos[i]);
		OutFile.WriteString(StrData);

		StrData.Format(_T("[HOME_STATUS%d]\t%d\n"), i, SharedInfo::VisionAxisHomeStatus[i]);
		OutFile.WriteString(StrData);
	}

	StrData.Format(_T("#END\n"));
	OutFile.WriteString(StrData);

	OutFile.Close();
#endif
	return TRUE;
}
BOOL DIRECT_AXIS_HOME::Load()
{
#if 0
	CString szMsg;
	CFile file;
	szMsg.Format(_T("%s\\Dat\\HomeStatus.Dat"), SharedInfo::GetExeFilePath());
	if (file.Open(szMsg, CFile::modeRead) == FALSE)
		file.Open(szMsg, CFile::modeRead | CFile::modeCreate);

	file.Read(&Info, sizeof(Info));
	file.Close();
#else //KJT 20210520 AWK
	CStdioFile InFile;
	CString strIndex = _T("");
	CString strSrc = _T("");
	CString strResult = _T(""), strPath;
	int nIndex = 0;
	int nFind = -1;

	strPath.Format(_T("%s"), SharedInfo::VisionAgentPath);
	strPath.AppendFormat(_T("\\Data\\"));
	::CreateDirectory(strPath, NULL);
	strPath.AppendFormat(_T("Axis_Data\\"));
	::CreateDirectory(strPath, NULL);
	strPath.AppendFormat(_T("Axis_Data.txt"));

	if (InFile.Open(strPath, CFile::modeRead | CFile::typeText) == FALSE)
		return FALSE;

	while (InFile.ReadString(strSrc) != FALSE)
	{
		strSrc.TrimLeft();
		strSrc.TrimRight();

		if (!strSrc.Compare(_T("#BEGIN")) || strSrc.GetLength() < 1) continue;
		if (!strSrc.Compare(_T("#END")) || strSrc == EOF) break;

		nFind = -1;

		strIndex.Format(_T("[COM_POS%d]"), nIndex);
		if (strSrc.Find(strIndex) != -1)
		{
			strResult = SharedInfo::LoadFileData(&InFile, strSrc, strIndex);
			SharedInfo::DirectAixsHome.Info.dCmdPos[nIndex] = _ttof(strResult);
			continue;
		}

		nFind = -1;

		strIndex.Format(_T("[HOME_STATUS%d]"), nIndex);
		if (strSrc.Find(strIndex) != -1)
		{
			strResult = SharedInfo::LoadFileData(&InFile, strSrc, strIndex);
			SharedInfo::DirectAixsHome.Info.bHomeStatus[nIndex] = (bool)(_ttoi(strResult));
		}
		nIndex++;

	}
	InFile.Close();
#endif
	return TRUE;
}

SharedInfo::SharedInfo()
{
}


SharedInfo::~SharedInfo()
{
}


void SharedInfo::Initialize(void) //KJT 20200812
{
	int k = 0;

	for (k = 0; k < DIRECT_AXIS_MAX; k++)
	{
		Is_Umac_Open = 0;	
		DirectAjinOriginIngStatus[k] = 0;
		VisionAxisHomeResult[k] = 0;
		VisionAxisHomeStatus[k] = 0;
		VisionAxisHomeSignal[k] = 0;
		VisionAxisPLimitSignal[k] = 0;
		VisionAxisNLimitSignal[k] = 0;
		VisionAxisServoOnStatus[k] = 0;
		VisionAxisAlarmStatus[k] = 0;
		VisionAxisInMotionStatus[k] = 0;	// 0:End Move, 1:Moving
		VisionAxisStatus[k] = 0;	//0:HomeStatus, 1:ServoOnStatus, 2:AlarmStatus, 3:MotionDoneStatus
		VisionAxisCmdPos[k] = 0; //
		VisionAxisActPos[k] = 0;
		VisionAxisCmdVel[k] = 0;
		VisionAxisTorque[k] = 0;
	}

	for (k = 0; k < REMOTE_AXIS_UMAC_MAX; k++)
	{
		Is_Umac_Open = 0;
		UmacOriginIngStatus[k] = 0;
		UmacHomeStatus[k] = 0;
		UmacHomeSignal[k] = 0;
		UmacPLimitSignal[k] = 0;
		UmacNLimitSignal[k] = 0;
		UmacServoOnStatus[k] = 0;
		UmacAlarmStatus[k] = 0;
		UmacStatus[k] = 0; //0:HomeStatus, 1:ServoOnStatus, 2:AlarmStatus, 3:MotionDoneStatus
		UmacInMotionStatus[k] = 0;
		UmacCmdPos[k] = 0.000;
		UmacActPos[k] = 0.000;
		UmacCmdVel[k] = 0.000;
	}
	for (k = 0; k < REMOTE_AXIS_MAX; k++)
	{
		Is_Ajin_Open = 0;
		RemoteAjinOriginIngStatus[k] = 0;
		AxisHomeResult[k] = 0;
		AxisHomeStatus[k] = 0;
		AxisHomeSignal[k] = 0;
		AxisPLimitSignal[k] = 0;
		AxisNLimitSignal[k] = 0;
		AxisServoOnStatus[k] = 0;
		AxisAlarmStatus[k] = 0;
		AxisStatus[k] = 0; //0:HomeStatus, 1:ServoOnStatus, 2:AlarmStatus, 3:MotionDoneStatus		
		AxisInMotionStatus[k] = 0;
		AxisCmdPos[k] = 0.000;
		AxisActPos[k] = 0.000;
		AxisCmdVel[k] = 0.000;
	}
	for (k = 0; k < MAX_DINPUT_SIZE; k++)
	{
		DInputValue[k] = 0;
	}
	for (k = 0; k < MAX_DOUTPUT_SIZE; k++)
	{
		DOutputValue[k] = 0;
	}
	for (k = 0; k < MAX_AINPUT_SIZE; k++)
	{
		AInputValue[k] = 0;
	}

	eCamViewMode = eCamView_6G;

	SharedInfo::Active.nActiveRecipeNum = 0;
}

void SharedInfo::Finalize(void)
{

}

void SharedInfo::ActiveInfoSave() //KJT 20210318
{
	CFile File;
	CString szFilePath, Str;
	//#if !XML_USE //dat
	szFilePath.Format(_T("%s\\dat\\ActiveInfo.dat"), GetExeFilePath());
	File.Open(szFilePath, CFile::modeCreate | CFile::modeWrite);
	File.Write(&Active, sizeof(ACTIVE_STATE));
	File.Close();
	//#else //xml
	szFilePath.Format(_T("%s\\xml\\ActiveInfo.xml"), GetExeFilePath());

	CXmlFile* xml = new CXmlFile;
	xml->SetDoc(_T("<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n\n"));
	xml->AddElem(_T("ActiveInfo"));
	xml->IntoElem();

	xml->AddElem(_T("MachineMode"), Active.MachineMode);
	xml->AddElem(_T("MachineWorkSpeed"), Active.MachineWorkSpeed);
	xml->AddElem(_T("WeldingLaserUse"), Active.WeldingLaserUse);
	xml->AddElem(_T("CassetteIndexY"), Active.CassetteIndexY);
	xml->AddElem(_T("CassetteIndexZ"), Active.CassetteIndexZ);
	xml->AddElem(_T("ActiveBankIndex"), Active.ActiveBankIndex);
	xml->AddElem(_T("nActiveRecipeNum"), Active.nActiveRecipeNum);
	xml->AddElem(_T("PanelId"), Active.PanelId);
	xml->AddElem(_T("UserId"), Active.UserId);
	xml->AddElem(_T("strFrameName"), Active.strFrameName);
	for (int i = 0; i < 50; i++)
	{
		Str.Format(_T("nFrameDone_%d"), i);
		xml->AddElem(Str, Active.nFrameDone[i]);
	}
	xml->AddElem(_T("ProcessStartFlow"), Active.ProcessStartFlow);
	xml->AddElem(_T("ProcessStep"), Active.ProcessStep);
	xml->AddElem(_T("ProcessEndFlow"), Active.ProcessEndFlow);
	xml->AddElem(_T("ProcessGlass"), Active.ProcessGlass);

	xml->OutOfElem();

	xml->Save(szFilePath);
	delete xml;
	//#endif

	Str.Format(_T("ActiveInfoSave Ok (%s)"), szFilePath);
	Total_Msg(Str);
}

void SharedInfo::ActiveInfoLoad()
{
	CFile File;
	CString szFilePath, Str;
#if !XML_USE //dat
	szFilePath.Format(_T("%s\\dat\\ActiveInfo.dat"), GetExeFilePath());
	if (File.Open(szFilePath, CFile::modeRead) == FALSE)
		File.Open(szFilePath, CFile::modeRead);
	File.Read(&Active, sizeof(ACTIVE_STATE));
	File.Close();
#else //xml
	szFilePath.Format(_T("%s\\xml\\ActiveInfo.xml"), GetExeFilePath());

	CXmlFile* xml = new CXmlFile;
	xml->Load(szFilePath);
	if (xml->FindElem(_T("ActiveInfo")))
	{
		xml->IntoElem();

		if (xml->FindElem(_T("MachineMode")))
			Active.MachineMode = _tstoi(xml->GetData());
		if (xml->FindElem(_T("MachineWorkSpeed")))
			Active.MachineWorkSpeed = _tstoi(xml->GetData());
		if (xml->FindElem(_T("WeldingLaserUse")))
			Active.WeldingLaserUse = _tstoi(xml->GetData());
		if (xml->FindElem(_T("CassetteIndexY")))
			Active.CassetteIndexY = _tstoi(xml->GetData());
		if (xml->FindElem(_T("CassetteIndexZ")))
			Active.CassetteIndexZ = _tstoi(xml->GetData());
		if (xml->FindElem(_T("ActiveBankIndex")))
			Active.ActiveBankIndex = _tstoi(xml->GetData());
		if (xml->FindElem(_T("nActiveRecipeNum")))
			Active.nActiveRecipeNum = _tstoi(xml->GetData());
		if (xml->FindElem(_T("PanelId")))
			wsprintf(Active.PanelId, _T("%s"), xml->GetData()); //KJT 20210727
		if (xml->FindElem(_T("UserId")))
			wsprintf(Active.UserId, _T("%s"), xml->GetData()); //KJT 20210727
		if (xml->FindElem(_T("strFrameName")))
			wsprintf(Active.strFrameName, _T("%s"), xml->GetData()); //KJT 20210727
		for (int i = 0; i < 50; i++)
		{
			Str.Format(_T("nFrameDone_%d"), i);
			Active.nFrameDone[i] = _tstoi(xml->GetData());
		}
		if (xml->FindElem(_T("ProcessStartFlow")))
			Active.ProcessStartFlow = _tstoi(xml->GetData());
		if (xml->FindElem(_T("ProcessStep")))
			Active.ProcessStep = _tstoi(xml->GetData());
		if (xml->FindElem(_T("ProcessEndFlow")))
			Active.ProcessEndFlow = _tstoi(xml->GetData());
		if (xml->FindElem(_T("ProcessGlass")))
			Active.ProcessGlass = _tstoi(xml->GetData());

		xml->OutOfElem();
	}
	delete xml;
#endif

	Str.Format(_T("ActiveInfoLoad Ok (%s)"), szFilePath);
	Total_Msg(Str);
}

void SharedInfo::ResultInfoSave()
{
	CFile File;
	CString szMsg;
	szMsg.Format(_T("%s\\dat\\ResultInfo.dat"), GetExeFilePath());
	File.Open(szMsg, CFile::modeCreate | CFile::modeWrite);
	File.Write(&Result, sizeof(RESULT_STATE));
	File.Close();

	CString Str = _T("");
	Str.Format(_T("ResultInfoSave Ok (%s)"), szMsg);
	Total_Msg(Str);
}

void SharedInfo::ResultInfoLoad()
{
	CFile File;
	CString szMsg;
	szMsg.Format(_T("%s\\dat\\ResultInfo.dat"), GetExeFilePath());
	if (File.Open(szMsg, CFile::modeRead) == FALSE)
		File.Open(szMsg, CFile::modeRead);
	File.Read(&Result, sizeof(RESULT_STATE));
	File.Close();

	CString Str = _T("");
	Str.Format(_T("ResultInfoLoad Ok (%s)"), szMsg);
	Total_Msg(Str);
}

BOOL SharedInfo::GetProcessTime(CTime tStart, int *nHour, int *nMin, int *nSec)
{
	CTime CurTime = CTime::GetCurrentTime();
	DWORD dStartTime = tStart.GetHour() * 3600 + tStart.GetMinute() * 60 + tStart.GetSecond();
	DWORD dCurTime = CurTime.GetHour() * 3600 + CurTime.GetMinute() * 60 + CurTime.GetSecond();

	dCurTime -= dStartTime;

	*nHour = dCurTime / 3600;
	*nMin = (dCurTime - (*nHour) * 3600) / 60;
	*nSec = dCurTime - (*nHour) * 3600 - (*nMin) * 60;

	return TRUE;
}

#pragma region //Align Result Diff Info
void SharedInfo::AlignCenterDiffInfoSave()
{
	CFile File;
	CString szMsg;
	szMsg.Format(_T("%s\\dat\\AlignCenterDiffInfo.dat"), GetExeFilePath());
	File.Open(szMsg, CFile::modeCreate | CFile::modeWrite);
	File.Write(&AlignCenterDiffInfo, sizeof(ALIGN_CENTER_DIFF_INFO));
	File.Close();

	CString Str = _T("");
	Str.Format(_T("AlignCenterDiffInfoSave Ok (%s)"), szMsg);
	Total_Msg(Str);
}
void SharedInfo::AlignCenterDiffInfoLoad()
{
	CFile File;
	CString szMsg;
	szMsg.Format(_T("%s\\dat\\AlignCenterDiffInfo.dat"), GetExeFilePath());
	if (File.Open(szMsg, CFile::modeRead) == FALSE)
		File.Open(szMsg, CFile::modeRead);
	File.Read(&AlignCenterDiffInfo, sizeof(ALIGN_CENTER_DIFF_INFO));
	File.Close();

	CString Str = _T("");
	Str.Format(_T("AlignCenterDiffInfoLoad Ok (%s)"), szMsg);
	Total_Msg(Str);
}
#pragma endregion

int SharedInfo::FindCurrentRecipeNumber(CString strRecipeName)
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

int SharedInfo::FindRecipeNumber(WORD wRecipeID)
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

CString SharedInfo::FindRecipeName(INT nReceipeNumber)
{
	CString strTemp = _T("");

	strTemp = CimInfo::m_MachineRecipeTable.strRecipeName[nReceipeNumber];

	return strTemp;
}

BOOL SharedInfo::GetIsAlignStick(INT nReceipeNumber)
{
	BOOL bRet = CimInfo::m_MachineRecipeTable.bIsAlignStick[nReceipeNumber];

	return bRet;
}

CString SharedInfo::GetExeFilePath()
{
	CString szMsg;
	CString strVisionAgentPath;
	CFile file;
	int i, nSize;
	TCHAR tchPathName[_MAX_PATH];
	GetModuleFileName(NULL, tchPathName, MAX_PATH);
	nSize = (int)wcslen(tchPathName);
	for (i = nSize; i >= 0; i--)
	{
		if (tchPathName[i] == '\\')
		{
			tchPathName[i] = NULL;
			break;
		}
	}

	strVisionAgentPath.Format(_T("%s"), tchPathName);

	return strVisionAgentPath;
}

BOOL SharedInfo::FindRecipeUse(INT nNumber)
{
	BOOL bTemp = FALSE;
	if (nNumber < 0 || nNumber > MAX_RECIPE_COUNT)
		return FALSE;

	bTemp = CimInfo::m_MachineRecipeTable.bRecipeTableUseFlag[nNumber];

	return bTemp;
}

BOOL SharedInfo::RecipeCheck()
{
	BOOL bResult, bChangeFlag = FALSE;
	CString szMsg, szMsgCmp;
	CFile file;
	int DetectCnt = 0;

	//USES_CONVERSION;

	//szMsg.Format(_T("%s\\dat\\MachineRecipeTable.dat"), SharedInfo::GetExeFilePath());
	//if (file.Open(szMsg, CFile::modeRead) == FALSE)
	//	file.Open(szMsg, CFile::modeRead | CFile::modeCreate);
	//file.Read(&m_MachineRecipeTable, sizeof(MACHINE_RECIPE_TABLE));
	//file.Close();

	//for (int i = 0; i < m_strModelNames.GetSize(); i++)
	//{
	//	szMsg = m_strModelNames.GetAt(i);
	//	bResult = FALSE;
	//	bChangeFlag = FALSE;
	//	for (int j = 0; j < MAX_RECIPE_COUNT; j++)
	//	{
	//		if (m_MachineRecipeTable.bRecipeTableUseFlag[j] == TRUE)
	//		{
	//			szMsgCmp.Format(_T("%S"), m_MachineRecipeTable.strRecipeName[j]);
	//			if (szMsgCmp == szMsg)
	//			{
	//				bResult = TRUE;
	//				DetectCnt++;
	//				break;
	//			}
	//		}
	//		if (DetectCnt == m_MachineRecipeTable.wRecipeCount && m_MachineRecipeTable.wRecipeCount != 0)
	//			break;
	//	}

	//	if (bResult == FALSE)
	//	{
	//		for (int j = 0; j < MAX_RECIPE_COUNT; j++)
	//		{
	//			if (m_MachineRecipeTable.bRecipeTableUseFlag[j] == FALSE)
	//			{
	//				m_MachineRecipeTable.bRecipeTableUseFlag[j] = TRUE;
	//				strcpy_s((char*)(m_MachineRecipeTable.strRecipeName + j), szMsg.GetLength() + 1, CT2A(szMsg));
	//				m_MachineRecipeTable.wRecipeID[j] = j;
	//				m_MachineRecipeTable.bIsAlignStick[j] = FALSE;
	//				m_MachineRecipeTable.wRecipeCount++;
	//				DetectCnt++;
	//				bChangeFlag = TRUE;
	//				break;
	//			}
	//		}
	//	}
	//}

	//if (DetectCnt < m_MachineRecipeTable.wRecipeCount)
	//{
	//	for (int i = 0; i < MAX_RECIPE_COUNT; i++)
	//	{
	//		bResult = FALSE;
	//		if (m_MachineRecipeTable.bRecipeTableUseFlag[i] == TRUE)
	//		{
	//			szMsgCmp.Format(_T("%S"), m_MachineRecipeTable.strRecipeName[i]);
	//			for (int j = 0; j < m_strModelNames.GetSize(); j++)
	//			{
	//				szMsg = m_strModelNames.GetAt(j);
	//				if (szMsgCmp == szMsg)
	//				{
	//					bResult = TRUE;
	//					break;
	//				}

	//			}
	//			if (bResult == FALSE)
	//			{
	//				m_MachineRecipeTable.bRecipeTableUseFlag[i] = FALSE;
	//				memset(m_MachineRecipeTable.strRecipeName[i], 0x0, 100);
	//				m_MachineRecipeTable.wRecipeID[i] = 0;
	//				m_MachineRecipeTable.bIsAlignStick[i] = FALSE;
	//				m_MachineRecipeTable.wRecipeCount--;
	//				bChangeFlag = TRUE;


	//			}
	//		}
	//	}

	//}
	//szMsg.Format(_T("%s\\dat\\MachineRecipeTable.dat"), GetExeFilePath());
	//file.Open(szMsg, CFile::modeCreate | CFile::modeWrite);
	//file.Write(&m_MachineRecipeTable, sizeof(MACHINE_RECIPE_TABLE));
	//file.Close();

	return bChangeFlag;
}

int SharedInfo::FindRecipeID(WORD wRecipeID)
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

void SharedInfo::MachineStatusChange(MACHINE_STATUS_ENUM MachineStatus)
{
	CimInfo::m_MachineState = MachineStatus;
}

BOOL SharedInfo::SaveModelData()
{
	CModelData::Save();
	return TRUE;
}
//----------------------------------------
BOOL SharedInfo::LoadModelData()
{
	//Load
	CModelData::Load();
	return TRUE;
}
//----------------------------------------
BOOL SharedInfo::SaveManualData()
{
	CManualData::Save();
	return TRUE;
}
//----------------------------------------
BOOL SharedInfo::LoadManualData()
{
	CManualData::m_ManualDataGantry.Init();
	CManualData::m_ManualDataBox.Init();
	CManualData::m_ManualDataLoader.Init();
	CManualData::m_ManualDataInspect.Init();
	CManualData::m_ManualDataClamp.Init();
	CManualData::m_ManualDataStretch.Init();
	CManualData::m_ManualDataPitch.Init();
	CManualData::m_ManualDataGripperZ.Init();
	CManualData::m_ManualDataUnloader.Init();
	CManualData::m_ManualDataCassette.Init();

	CManualData::Load();
	return TRUE;
}
//----------------------------------------
BOOL SharedInfo::SaveMachineData()
{
	CMachineData::Save();
	return TRUE;
}
//----------------------------------------
BOOL SharedInfo::LoadMachineData()
{
	CMachineData::m_MachineDataMotor.Init();
	CMachineData::Load();
	return TRUE;
}
//----------------------------------------
BOOL SharedInfo::SaveSystemData()
{
	CString filePath = GetExeFilePath();;
	filePath.AppendFormat(_T("Data\\"));
	::CreateDirectory(filePath, NULL);
	filePath.AppendFormat(_T("System"));
	::CreateDirectory(filePath, NULL);

	CSystemData::Save();
	return TRUE;
}
//----------------------------------------
BOOL	SharedInfo::LoadSystemData()
{
	CString filePath = GetExeFilePath();
	filePath.AppendFormat(_T("Data\\"));
	::CreateDirectory(filePath, NULL);
	filePath.AppendFormat(_T("System"));
	::CreateDirectory(filePath, NULL);	

	CSystemData::Load();

	return TRUE;

}
void SharedInfo::RemoveMachineRecipeTable(WORD wRecipID)
{
	if (wRecipID > MAX_RECIPE_COUNT)
		return;
	CFile file;

	CString szMsg = _T("");
	CimInfo::m_MachineRecipeTable.bRecipeTableUseFlag[wRecipID] = FALSE;
	memset(CimInfo::m_MachineRecipeTable.strRecipeName + (wRecipID), 0x0, 100);
	//memset(&CimInfo::m_MachineRecipeTable.strCurrentRecipeName, 0x0, 100);

	CimInfo::m_MachineRecipeTable.wRecipeID[wRecipID] = 0;
	CimInfo::m_MachineRecipeTable.bIsAlignStick[wRecipID] = FALSE;
	CimInfo::m_MachineRecipeTable.wRecipeCount--;

	SaveRecipeTable(); //KJT 20210328
}

CString SharedInfo::LoadFileData(CStdioFile* csfInFile, CString strSrcData, CString strCompData)
{
	int nPos = -1;
	int nDataLenth = 0;
	CString strResult = _T("");

	nPos = strSrcData.Find(strCompData);
	strResult = _T("-1");
	if (nPos != -1)
	{
		nPos = strSrcData.Find(_T("\t")) + 1;
		if (nPos != -1)
		{
			//TRACE(_T("DOutputLabel = %s \n"), strSrcData);
			nDataLenth = strSrcData.GetLength() - strCompData.GetLength();
			strResult = strSrcData.Mid(nPos, nDataLenth);
			strResult.TrimLeft();
			strResult.TrimRight();
		}
	}
	return strResult;
}

//----------------------------------------
BOOL SharedInfo::SaveNewModelData(LPCTSTR strDirectory)
{
	CString filePath;
	filePath.Format(_T("%s\\%s"), strDirectory, FILENAME_MODELDATA);

	try
	{
		CModelData::Save();
	}
	catch (CFileException* e)
	{
		return FALSE;
	}

	return TRUE;
}
//----------------------------------------
void SharedInfo::FindModelNames()
{
	CFileFind finder;
	CString strPathFind;
	CString strDirName;

	strPathFind.Format(_T("%s\\*.*"), GetModelDataFolder());
	BOOL bWorking = finder.FindFile(strPathFind);
	while (bWorking)
	{
		Sleep(10);
		bWorking = finder.FindNextFile();
		if (finder.IsDirectory())
		{
			strDirName = finder.GetFileName();
			if (strDirName == _T(".") || strDirName == _T("..")) continue;
			m_strModelNames.Add(strDirName);
		}
	}
}

BOOL SharedInfo::NewDirectoryFile(LPCTSTR RootDir)
{
	if (RootDir == NULL)
	{
		return FALSE;
	}

	BOOL bRval = FALSE;

	bRval = CreateDirectory(RootDir, NULL);

	if (bRval)
	{
		SaveNewModelData(RootDir);
		//Manual Data는 System처럼 동작하도록 변경. 2018. 12. 23.
		//pVisionAgentDlg->SaveNewManualData(RootDir);
	}

	return bRval;
}

BOOL SharedInfo::InitModelData()
{
	CModelData::Initialize();

	return TRUE;
}

BOOL SharedInfo::LoadModelData(CString strModelName)
{
	CString filePath, strActiveModelName;

	if (strModelName != _T(""))
	{

		strActiveModelName = Devs::FindCurrentRecipeName(SharedInfo::Active.nActiveRecipeNum);
		//filePath.Format(_T("%s\\Data\\Model\\%s\\%s"), SharedInfo::GetExeFilePath(), strModelName, FILENAME_MODELDATA);
		if (strActiveModelName != strModelName)
		{
			strActiveModelName = strModelName;
			SaveSystemData();
		}
		//else
		//{
		//	AfxMessageBox(_T("It is Selected Done"));
		//	return FALSE;
		//}
		try
		{
			CModelData::Load();
		}
		catch (CFileException* e)
		{
			return FALSE;
		}

		try
		{
			CManualData::Load();
		}
		catch (CFileException* e)
		{
			return FALSE;
		}
	}
	else
	{
		AfxMessageBox(_T("Please Select Model"));
	}

	MachineState.bRecipeChangeDone = TRUE;

	return TRUE;

	return TRUE;
}

BOOL SharedInfo::DeleteDirectoryFile(LPCTSTR RootDir)
{
	if (RootDir == NULL)
	{
		AfxMessageBox(_T("It's not Selected Model"));
		return FALSE;
	}

	BOOL bRval = FALSE;
	CString szRoot = _T("");

	// ÇØ´ç µð·ºÅä¸®ÀÇ ¸ðµç ÆÄÀÏÀ» °Ë»çÇÑ´Ù.
	szRoot.Format(_T("%s\\*.*"), RootDir);
	CFileFind find;
	bRval = find.FindFile(szRoot);
	if (bRval == FALSE)
	{
		return bRval;
	}
	while (bRval)
	{		
		bRval = find.FindNextFile();
		// . or .. ÀÎ °æ¿ì ¹«½Ã ÇÑ´Ù.  
		if (find.IsDots() == FALSE)
		{
			// Directory ÀÏ °æ¿ì Àç±ÍÈ£Ãâ ÇÑ´Ù.
			if (find.IsDirectory())
			{
				DeleteDirectoryFile(find.GetFilePath());
			}
			// fileÀÏ °æ¿ì »èÁ¦ 
			else
			{
				SetFileAttributes(find.GetFilePath(), FILE_ATTRIBUTE_ARCHIVE); //KJT 20210722
				bRval = DeleteFile(find.GetFilePath());
			}
		}
	}
	find.Close();

	SetFileAttributes(RootDir, FILE_ATTRIBUTE_ARCHIVE); //KJT 20210722
	bRval = RemoveDirectory(RootDir);
	return bRval;
}

BOOL SharedInfo::RenameDirectoryFile(LPCTSTR NewDirName, CString strSelName)
{
	CFile file;
	CString strTemp = _T("");
	CString strTemp2 = _T("");
	CString strSelectedFolderDir = _T("");
	CString strNewFoldername = _T("");
	int nPreRecipeId = -1;
	strTemp = GetModelDataFolder();

	strSelectedFolderDir = strSelName;
	strNewFoldername = strTemp;
	strTemp.Append(_T("\\"));
	strTemp += strSelectedFolderDir;

	strTemp2.AppendFormat(_T("%s"), NewDirName);
	strNewFoldername.AppendFormat(_T("\\%s"), NewDirName);



	nPreRecipeId = SharedInfo::FindCurrentRecipeNumber(strSelectedFolderDir);
	strcpy_s((char*)(CimInfo::m_MachineRecipeTable.strRecipeName + (nPreRecipeId - 1)), strTemp2.GetLength() + 1, CT2A(strTemp2));

	file.Rename(strTemp, strNewFoldername);

	SharedInfo::SaveRecipeTable(); //KJT 20210410;

	return 0;
}

void SharedInfo::AddMachineRecipeTable(WORD wRecipID, CString strNewDirName)
{
	CFile file;

	CString szMsg = _T("");
	CimInfo::m_MachineRecipeTable.bRecipeTableUseFlag[wRecipID] = TRUE;
	strcpy_s((char*)(CimInfo::m_MachineRecipeTable.strRecipeName + (wRecipID)), strNewDirName.GetLength() + 1, CT2A(strNewDirName));
	//	strcpy_s((char*)(&CimInfo::m_MachineRecipeTable.strCurrentRecipeName ), strNewDirName.GetLength() + 1, CT2A(strNewDirName));
	CimInfo::m_MachineRecipeTable.wRecipeID[wRecipID] = wRecipID;
	CimInfo::m_MachineRecipeTable.bIsAlignStick[wRecipID] = FALSE;
	CimInfo::m_MachineRecipeTable.wRecipeCount++;

	SaveRecipeTable(); //KJT 20210328
}

void SharedInfo::ResetModel()
{
	CFileFind finder;
	CString strPathFind;
	CString strDirName;

	m_strModelNames.RemoveAll();
	strPathFind.Format(_T("%s\\*.*"), GetModelDataFolder());
	BOOL bWorking = finder.FindFile(strPathFind);
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if (finder.IsDirectory())
		{
			strDirName = finder.GetFileName();
			if (strDirName == _T(".") || strDirName == _T("..")) continue;
			m_strModelNames.Add(strDirName);
		}
	}
}

BOOL SharedInfo::SaveRecipeTable()
{
	CString szFilePath, Str, Str1, Str2;
	CFile file;
	int i = 0, j = 0;

	CString szMsg;
	//CFile file;
	szMsg.Format(_T("%s\\dat\\MachineRecipeTable.dat"), SharedInfo::GetExeFilePath());
	file.Open(szMsg, CFile::modeCreate | CFile::modeWrite);
	file.Write(&CimInfo::m_MachineRecipeTable, sizeof(MACHINE_RECIPE_TABLE));
	file.Close();

	return TRUE;

	//#if !XML_USE //dat
	Str.Format(_T("%s\\dat\\MachineRecipeTable.dat"), SharedInfo::VisionAgentPath);
	file.Open(Str, CFile::modeCreate | CFile::modeWrite);
	file.Write(&CimInfo::m_MachineRecipeTable, sizeof(MACHINE_RECIPE_TABLE));
	file.Close();
	//#else
#pragma region //KJT 20210326
	szFilePath.Format(_T("%s\\xml\\MachineRecipeTable.xml"), SharedInfo::VisionAgentPath);

	/*
	CXmlFile* xml = new CXmlFile;
	xml->SetDoc(_T("<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n\n"));
	xml->AddElem(_T("MachineRecipeTable"));
	xml->IntoElem();

	xml->AddElem(_T("wRecipeCount"), CimInfo::m_MachineRecipeTable.wRecipeCount);
	for (i = 0; i < MAX_RECIPE_COUNT; i++)
	{
		Str1.Format(_T("strRecipeName_%d"), i);
		Str2.Format(_T("%S"), CimInfo::m_MachineRecipeTable.strRecipeName[i]);
		xml->AddElem(Str1, Str2);

		Str1.Format(_T("bRecipeTableUseFlag_%d"), i);
		xml->AddElem(Str1, CimInfo::m_MachineRecipeTable.bRecipeTableUseFlag[i]);

		Str1.Format(_T("wRecipeID_%d"), i);
		xml->AddElem(Str1, CimInfo::m_MachineRecipeTable.wRecipeID[i]);

		Str1.Format(_T("bIsAlignStick_%d"), i);
		xml->AddElem(Str1, CimInfo::m_MachineRecipeTable.bIsAlignStick[i]);

		//RecipeValue
		Str1.Format(_T("RecipeValue_%d_dStickSizeX"), i);
		xml->AddElem(Str1, CimInfo::m_MachineRecipeTable.RecipeValue[i].dStickSizeX);
		Str1.Format(_T("RecipeValue_%d_dStickSizeY"), i);
		xml->AddElem(Str1, CimInfo::m_MachineRecipeTable.RecipeValue[i].dStickSizeY);
		Str1.Format(_T("RecipeValue_%d_dAlignHoleLX"), i);
		xml->AddElem(Str1, CimInfo::m_MachineRecipeTable.RecipeValue[i].dAlignHoleLX);
		Str1.Format(_T("RecipeValue_%d_dAlignHoleLY"), i);
		xml->AddElem(Str1, CimInfo::m_MachineRecipeTable.RecipeValue[i].dAlignHoleLY);
		Str1.Format(_T("RecipeValue_%d_dAlignHoleRX"), i);
		xml->AddElem(Str1, CimInfo::m_MachineRecipeTable.RecipeValue[i].dAlignHoleRX);
		Str1.Format(_T("RecipeValue_%d_dAlignHoleRY"), i);
		xml->AddElem(Str1, CimInfo::m_MachineRecipeTable.RecipeValue[i].dAlignHoleRY);
		Str1.Format(_T("RecipeValue_%d_dAlignHoleSizeX"), i);
		xml->AddElem(Str1, CimInfo::m_MachineRecipeTable.RecipeValue[i].dAlignHoleSizeX);
		Str1.Format(_T("RecipeValue_%d_dAlignHoleSizeY"), i);
		xml->AddElem(Str1, CimInfo::m_MachineRecipeTable.RecipeValue[i].dAlignHoleSizeY);

		Str1.Format(_T("RecipeValue_%d_nCellCountX"), i);
		xml->AddElem(Str1, CimInfo::m_MachineRecipeTable.RecipeValue[i].nCellCountX);
		Str1.Format(_T("RecipeValue_%d_nCellCountY"), i);
		xml->AddElem(Str1, CimInfo::m_MachineRecipeTable.RecipeValue[i].nCellCountY);
		Str1.Format(_T("RecipeValue_%d_dFirstCell_LTX"), i);
		xml->AddElem(Str1, CimInfo::m_MachineRecipeTable.RecipeValue[i].dFirstCell_LTX);
		Str1.Format(_T("RecipeValue_%d_dFirstCell_LTY"), i);
		xml->AddElem(Str1, CimInfo::m_MachineRecipeTable.RecipeValue[i].dFirstCell_LTY);
		Str1.Format(_T("RecipeValue_%d_dCellSizeX"), i);
		xml->AddElem(Str1, CimInfo::m_MachineRecipeTable.RecipeValue[i].dCellSizeX);
		Str1.Format(_T("RecipeValue_%d_dCellSizeY"), i);
		xml->AddElem(Str1, CimInfo::m_MachineRecipeTable.RecipeValue[i].dCellSizeY);

		Str1.Format(_T("RecipeValue_%d_dTegkey_LTX"), i);
		xml->AddElem(Str1, CimInfo::m_MachineRecipeTable.RecipeValue[i].dTegkey_LTX);
		Str1.Format(_T("RecipeValue_%d_dTegkey_LTY"), i);
		xml->AddElem(Str1, CimInfo::m_MachineRecipeTable.RecipeValue[i].dTegkey_LTY);
		Str1.Format(_T("RecipeValue_%d_dTegkey_RTX"), i);
		xml->AddElem(Str1, CimInfo::m_MachineRecipeTable.RecipeValue[i].dTegkey_RTX);
		Str1.Format(_T("RecipeValue_%d_dTegkey_RTY"), i);
		xml->AddElem(Str1, CimInfo::m_MachineRecipeTable.RecipeValue[i].dTegkey_RTY);
		Str1.Format(_T("RecipeValue_%d_dTegkey_SizeX"), i);
		xml->AddElem(Str1, CimInfo::m_MachineRecipeTable.RecipeValue[i].dTegkey_SizeX);
		Str1.Format(_T("RecipeValue_%d_dTegkey_SizeY"), i);
		xml->AddElem(Str1, CimInfo::m_MachineRecipeTable.RecipeValue[i].dTegkey_SizeY);

		for (j = 0; j < CIM_MAX_CELL_COUNT_XY; j++)
		{
			Str1.Format(_T("RecipeValue_%d_dSlotCenterShiftX_%d"), i, j);
			xml->AddElem(Str1, CimInfo::m_MachineRecipeTable.RecipeValue[i].dSlotCenterShiftX[j]);
			Str1.Format(_T("RecipeValue_%d_dSlotCenterShiftY_%d"), i, j);
			xml->AddElem(Str1, CimInfo::m_MachineRecipeTable.RecipeValue[i].dSlotCenterShiftY[j]);
			Str1.Format(_T("RecipeValue_%d_dSlotSizeX_%d"), i, j);
			xml->AddElem(Str1, CimInfo::m_MachineRecipeTable.RecipeValue[i].dSlotSizeX[j]);
			Str1.Format(_T("RecipeValue_%d_dSlotSizeY_%d"), i, j);
			xml->AddElem(Str1, CimInfo::m_MachineRecipeTable.RecipeValue[i].dSlotSizeY[j]);
			Str1.Format(_T("RecipeValue_%d_dSlotAngle_%d"), i, j);
			xml->AddElem(Str1, CimInfo::m_MachineRecipeTable.RecipeValue[i].dSlotAngle[j]);
			Str1.Format(_T("RecipeValue_%d_dSlotPitchX_%d"), i, j);
			xml->AddElem(Str1, CimInfo::m_MachineRecipeTable.RecipeValue[i].dSlotPitchX[j]);
			Str1.Format(_T("RecipeValue_%d_dSlotPitchY_%d"), i, j);
			xml->AddElem(Str1, CimInfo::m_MachineRecipeTable.RecipeValue[i].dSlotPitchY[j]);
			Str1.Format(_T("RecipeValue_%d_dSlotTotalPitchX_%d"), i, j);
			xml->AddElem(Str1, CimInfo::m_MachineRecipeTable.RecipeValue[i].dSlotTotalPitchX[j]);
			Str1.Format(_T("RecipeValue_%d_dSlotTotalPitchY_%d"), i, j);
			xml->AddElem(Str1, CimInfo::m_MachineRecipeTable.RecipeValue[i].dSlotTotalPitchY[j]);
		}

		//Inspection Para
		Str1.Format(_T("RecipeValue_%d_nPPA_DIV_X"), i);
		xml->AddElem(Str1, CimInfo::m_MachineRecipeTable.RecipeValue[i].nPPA_DIV_X);
		Str1.Format(_T("RecipeValue_%d_nPPA_DIV_Y"), i);
		xml->AddElem(Str1, CimInfo::m_MachineRecipeTable.RecipeValue[i].nPPA_DIV_Y);
		Str1.Format(_T("RecipeValue_%d_nStickTensionUse"), i);
		xml->AddElem(Str1, CimInfo::m_MachineRecipeTable.RecipeValue[i].nStickTensionUse);

		Str1.Format(_T("RecipeValue_%d_nTegkey2PAlignFlowUse"), i);
		xml->AddElem(Str1, CimInfo::m_MachineRecipeTable.RecipeValue[i].nTegkey2PAlignFlowUse);
		Str1.Format(_T("RecipeValue_%d_nSWAlignFlowUse"), i);
		xml->AddElem(Str1, CimInfo::m_MachineRecipeTable.RecipeValue[i].nSWAlignFlowUse);
		Str1.Format(_T("RecipeValue_%d_nPPAFlowUse"), i);
		xml->AddElem(Str1, CimInfo::m_MachineRecipeTable.RecipeValue[i].nPPAFlowUse);
		Str1.Format(_T("RecipeValue_%d_nAOIFlowUse"), i);
		xml->AddElem(Str1, CimInfo::m_MachineRecipeTable.RecipeValue[i].nAOIFlowUse);
		Str1.Format(_T("RecipeValue_%d_nAOIReviewFlowUse"), i);
		xml->AddElem(Str1, CimInfo::m_MachineRecipeTable.RecipeValue[i].nAOIReviewFlowUse);
		Str1.Format(_T("RecipeValue_%d_nInspection3DFlowUse"), i);
		xml->AddElem(Str1, CimInfo::m_MachineRecipeTable.RecipeValue[i].nInspection3DFlowUse);

		Str1.Format(_T("RecipeValue_%d_dAOIDefectSizeMin"), i);
		xml->AddElem(Str1, CimInfo::m_MachineRecipeTable.RecipeValue[i].dAOIDefectSizeMin);

		Str1.Format(_T("RecipeValue_%d_dTensionNewton"), i);
		xml->AddElem(Str1, CimInfo::m_MachineRecipeTable.RecipeValue[i].dTensionNewton);
	}

	xml->OutOfElem();

	xml->Save(szFilePath);
	delete xml;
	*/
#pragma endregion
	//#endif

	Str.Format(_T("MachineRecipeTable Save Ok (%s)"), szFilePath);
	Total_Msg(Str);

	return TRUE;
}
BOOL SharedInfo::LoadRecipeTable()
{
	CString szFilePath = _T(""), Str = _T("");
	CFile file;
	int i = 0, j = 0;

	CString szMsg;
	//CFile file;

	szMsg.Format(_T("%s\\dat\\MachineRecipeTable.dat"), SharedInfo::GetExeFilePath());
	if (file.Open(szMsg, CFile::modeRead) == FALSE)
		file.Open(szMsg, CFile::modeRead | CFile::modeCreate);
	file.Read(&CimInfo::m_MachineRecipeTable, sizeof(MACHINE_RECIPE_TABLE));
	file.Close();
	
	Str.Format(_T("LoadRecipeTable Ok (%s)"), szMsg);
	Total_Msg(Str);

	return TRUE;

#if !XML_USE //dat
	szFilePath.Format(_T("%s\\dat\\MachineRecipeTable.dat"), SharedInfo::VisionAgentPath);
	if (file.Open(szFilePath, CFile::modeRead) == FALSE)
		file.Open(szFilePath, CFile::modeRead | CFile::modeCreate);
	file.Read(&CimInfo::m_MachineRecipeTable, sizeof(MACHINE_RECIPE_TABLE));
	file.Close();
#else
	szFilePath.Format(_T("%s\\xml\\MachineRecipeTable.xml"), SharedInfo::VisionAgentPath);

	/*
	CXmlFile* xml = new CXmlFile;
	xml->Load(szFilePath);
	if (xml->FindElem(_T("MachineRecipeTable")))
	{
		xml->IntoElem();

		if (xml->FindElem(_T("wRecipeCount")))
			CimInfo::m_MachineRecipeTable.wRecipeCount = _tstoi(xml->GetData());

		for (i = 0; i < MAX_RECIPE_COUNT; i++)
		{
			Str.Format(_T("strRecipeName_%d"), i);
			if (xml->FindElem(Str))
			{
				memset(CimInfo::m_MachineRecipeTable.strRecipeName[i], 0x00, sizeof(CimInfo::m_MachineRecipeTable.strRecipeName[i]));
				sprintf(CimInfo::m_MachineRecipeTable.strRecipeName[i], "%s", (char*)CT2CA(xml->GetData()));
			}

			Str.Format(_T("bRecipeTableUseFlag_%d"), i);
			if (xml->FindElem(Str))
				CimInfo::m_MachineRecipeTable.bRecipeTableUseFlag[i] = _tstoi(xml->GetData());

			Str.Format(_T("wRecipeID_%d"), i);
			if (xml->FindElem(Str))
				CimInfo::m_MachineRecipeTable.wRecipeID[i] = _tstoi(xml->GetData());

			Str.Format(_T("bIsAlignStick_%d"), i);
			if (xml->FindElem(Str))
				CimInfo::m_MachineRecipeTable.bIsAlignStick[i] = _tstoi(xml->GetData());

			//RecipeValue
			Str.Format(_T("RecipeValue_%d_dStickSizeX"), i);
			if (xml->FindElem(Str))
				CimInfo::m_MachineRecipeTable.RecipeValue[i].dStickSizeX = (FLOAT)_tstof(xml->GetData());

			Str.Format(_T("RecipeValue_%d_dStickSizeY"), i);
			if (xml->FindElem(Str))
				CimInfo::m_MachineRecipeTable.RecipeValue[i].dStickSizeY = (FLOAT)_tstof(xml->GetData());

			Str.Format(_T("RecipeValue_%d_dAlignHoleLX"), i);
			if (xml->FindElem(Str))
				CimInfo::m_MachineRecipeTable.RecipeValue[i].dAlignHoleLX = (FLOAT)_tstof(xml->GetData());

			Str.Format(_T("RecipeValue_%d_dAlignHoleLY"), i);
			if (xml->FindElem(Str))
				CimInfo::m_MachineRecipeTable.RecipeValue[i].dAlignHoleLY = (FLOAT)_tstof(xml->GetData());

			Str.Format(_T("RecipeValue_%d_dAlignHoleRX"), i);
			if (xml->FindElem(Str))
				CimInfo::m_MachineRecipeTable.RecipeValue[i].dAlignHoleRX = (FLOAT)_tstof(xml->GetData());

			Str.Format(_T("RecipeValue_%d_dAlignHoleRY"), i);
			if (xml->FindElem(Str))
				CimInfo::m_MachineRecipeTable.RecipeValue[i].dAlignHoleRY = (FLOAT)_tstof(xml->GetData());

			Str.Format(_T("RecipeValue_%d_dAlignHoleSizeX"), i);
			if (xml->FindElem(Str))
				CimInfo::m_MachineRecipeTable.RecipeValue[i].dAlignHoleSizeX = (FLOAT)_tstof(xml->GetData());

			Str.Format(_T("RecipeValue_%d_dAlignHoleSizeY"), i);
			if (xml->FindElem(Str))
				CimInfo::m_MachineRecipeTable.RecipeValue[i].dAlignHoleSizeY = (FLOAT)_tstof(xml->GetData());

			Str.Format(_T("RecipeValue_%d_nCellCountX"), i);
			if (xml->FindElem(Str))
				CimInfo::m_MachineRecipeTable.RecipeValue[i].nCellCountX = _tstoi(xml->GetData());

			Str.Format(_T("RecipeValue_%d_nCellCountY"), i);
			if (xml->FindElem(Str))
				CimInfo::m_MachineRecipeTable.RecipeValue[i].nCellCountY = _tstoi(xml->GetData());

			Str.Format(_T("RecipeValue_%d_dFirstCell_LTX"), i);
			if (xml->FindElem(Str))
				CimInfo::m_MachineRecipeTable.RecipeValue[i].dFirstCell_LTX = (FLOAT)_tstof(xml->GetData());

			Str.Format(_T("RecipeValue_%d_dFirstCell_LTY"), i);
			if (xml->FindElem(Str))
				CimInfo::m_MachineRecipeTable.RecipeValue[i].dFirstCell_LTY = (FLOAT)_tstof(xml->GetData());

			Str.Format(_T("RecipeValue_%d_dCellSizeX"), i);
			if (xml->FindElem(Str))
				CimInfo::m_MachineRecipeTable.RecipeValue[i].dCellSizeX = (FLOAT)_tstof(xml->GetData());

			Str.Format(_T("RecipeValue_%d_dCellSizeY"), i);
			if (xml->FindElem(Str))
				CimInfo::m_MachineRecipeTable.RecipeValue[i].dCellSizeY = (FLOAT)_tstof(xml->GetData());

			Str.Format(_T("RecipeValue_%d_dTegkey_LTX"), i);
			if (xml->FindElem(Str))
				CimInfo::m_MachineRecipeTable.RecipeValue[i].dTegkey_LTX = (FLOAT)_tstof(xml->GetData());

			Str.Format(_T("RecipeValue_%d_dTegkey_LTY"), i);
			if (xml->FindElem(Str))
				CimInfo::m_MachineRecipeTable.RecipeValue[i].dTegkey_LTY = (FLOAT)_tstof(xml->GetData());

			Str.Format(_T("RecipeValue_%d_dTegkey_RTX"), i);
			if (xml->FindElem(Str))
				CimInfo::m_MachineRecipeTable.RecipeValue[i].dTegkey_RTX = (FLOAT)_tstof(xml->GetData());

			Str.Format(_T("RecipeValue_%d_dTegkey_RTY"), i);
			if (xml->FindElem(Str))
				CimInfo::m_MachineRecipeTable.RecipeValue[i].dTegkey_RTY = (FLOAT)_tstof(xml->GetData());

			Str.Format(_T("RecipeValue_%d_dTegkey_SizeX"), i);
			if (xml->FindElem(Str))
				CimInfo::m_MachineRecipeTable.RecipeValue[i].dTegkey_SizeX = (FLOAT)_tstof(xml->GetData());

			Str.Format(_T("RecipeValue_%d_dTegkey_SizeY"), i);
			if (xml->FindElem(Str))
				CimInfo::m_MachineRecipeTable.RecipeValue[i].dTegkey_SizeY = (FLOAT)_tstof(xml->GetData());

			for (j = 0; j < CIM_MAX_CELL_COUNT_XY; j++)
			{
				Str.Format(_T("RecipeValue_%d_dSlotCenterShiftX_%d"), i, j);
				if (xml->FindElem(Str))
					CimInfo::m_MachineRecipeTable.RecipeValue[i].dSlotCenterShiftX[j] = (FLOAT)_tstof(xml->GetData());

				Str.Format(_T("RecipeValue_%d_dSlotCenterShiftY_%d"), i, j);
				if (xml->FindElem(Str))
					CimInfo::m_MachineRecipeTable.RecipeValue[i].dSlotCenterShiftY[j] = (FLOAT)_tstof(xml->GetData());

				Str.Format(_T("RecipeValue_%d_dSlotSizeX_%d"), i, j);
				if (xml->FindElem(Str))
					CimInfo::m_MachineRecipeTable.RecipeValue[i].dSlotSizeX[j] = (FLOAT)_tstof(xml->GetData());

				Str.Format(_T("RecipeValue_%d_dSlotSizeY_%d"), i, j);
				if (xml->FindElem(Str))
					CimInfo::m_MachineRecipeTable.RecipeValue[i].dSlotSizeY[j] = (FLOAT)_tstof(xml->GetData());

				Str.Format(_T("RecipeValue_%d_dSlotAngle_%d"), i, j);
				if (xml->FindElem(Str))
					CimInfo::m_MachineRecipeTable.RecipeValue[i].dSlotAngle[j] = (FLOAT)_tstof(xml->GetData());

				Str.Format(_T("RecipeValue_%d_dSlotPitchX_%d"), i, j);
				if (xml->FindElem(Str))
					CimInfo::m_MachineRecipeTable.RecipeValue[i].dSlotPitchX[j] = (FLOAT)_tstof(xml->GetData());

				Str.Format(_T("RecipeValue_%d_dSlotPitchY_%d"), i, j);
				if (xml->FindElem(Str))
					CimInfo::m_MachineRecipeTable.RecipeValue[i].dSlotPitchY[j] = (FLOAT)_tstof(xml->GetData());

				Str.Format(_T("RecipeValue_%d_dSlotTotalPitchX_%d"), i, j);
				if (xml->FindElem(Str))
					CimInfo::m_MachineRecipeTable.RecipeValue[i].dSlotTotalPitchX[j] = (FLOAT)_tstof(xml->GetData());

				Str.Format(_T("RecipeValue_%d_dSlotTotalPitchY_%d"), i, j);
				if (xml->FindElem(Str))
					CimInfo::m_MachineRecipeTable.RecipeValue[i].dSlotTotalPitchY[j] = (FLOAT)_tstof(xml->GetData());
			}

			//Inspection Para
			Str.Format(_T("RecipeValue_%d_nPPA_DIV_X"), i);
			if (xml->FindElem(Str))
				CimInfo::m_MachineRecipeTable.RecipeValue[i].nPPA_DIV_X = _tstoi(xml->GetData());

			Str.Format(_T("RecipeValue_%d_nPPA_DIV_Y"), i);
			if (xml->FindElem(Str))
				CimInfo::m_MachineRecipeTable.RecipeValue[i].nPPA_DIV_Y = _tstoi(xml->GetData());

			Str.Format(_T("RecipeValue_%d_nStickTensionUse"), i);
			if (xml->FindElem(Str))
				CimInfo::m_MachineRecipeTable.RecipeValue[i].nStickTensionUse = _tstoi(xml->GetData());

			Str.Format(_T("RecipeValue_%d_nTegkey2PAlignFlowUse"), i);
			if (xml->FindElem(Str))
				CimInfo::m_MachineRecipeTable.RecipeValue[i].nTegkey2PAlignFlowUse = _tstoi(xml->GetData());

			Str.Format(_T("RecipeValue_%d_nSWAlignFlowUse"), i);
			if (xml->FindElem(Str))
				CimInfo::m_MachineRecipeTable.RecipeValue[i].nSWAlignFlowUse = _tstoi(xml->GetData());

			Str.Format(_T("RecipeValue_%d_nPPAFlowUse"), i);
			if (xml->FindElem(Str))
				CimInfo::m_MachineRecipeTable.RecipeValue[i].nPPAFlowUse = _tstoi(xml->GetData());

			Str.Format(_T("RecipeValue_%d_nAOIFlowUse"), i);
			if (xml->FindElem(Str))
				CimInfo::m_MachineRecipeTable.RecipeValue[i].nAOIFlowUse = _tstoi(xml->GetData());

			Str.Format(_T("RecipeValue_%d_nAOIReviewFlowUse"), i);
			if (xml->FindElem(Str))
				CimInfo::m_MachineRecipeTable.RecipeValue[i].nAOIReviewFlowUse = _tstoi(xml->GetData());

			Str.Format(_T("RecipeValue_%d_nInspection3DFlowUse"), i);
			if (xml->FindElem(Str))
				CimInfo::m_MachineRecipeTable.RecipeValue[i].nInspection3DFlowUse = _tstoi(xml->GetData());

			Str.Format(_T("RecipeValue_%d_dAOIDefectSizeMin"), i);
			if (xml->FindElem(Str))
				CimInfo::m_MachineRecipeTable.RecipeValue[i].dAOIDefectSizeMin = (FLOAT)_tstof(xml->GetData());

			Str.Format(_T("RecipeValue_%d_dTensionNewton"), i);
			if (xml->FindElem(Str))
				CimInfo::m_MachineRecipeTable.RecipeValue[i].dTensionNewton = (FLOAT)_tstof(xml->GetData());
		}		
	}
	xml->OutOfElem();

	delete xml;
	*/
#endif

	Str.Format(_T("LoadRecipeTable Ok (%s)"), szFilePath);
	Total_Msg(Str);

	return TRUE;
}

CString SharedInfo::GetBeamAxisDataFolder()
{
	CString m_path = _T("");
	SYSTEMTIME st;

	GetLocalTime(&st);
	m_path.AppendFormat(_T("\\Result\\BeamAxis\\%04d%02d%02d%02d%02d%02d_BeamAxis.csv"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

	return GetExeFilePath() + m_path;
}

CString SharedInfo::GetLcmDataFolder()
{
	CString m_path = _T("");
	SYSTEMTIME st;

	GetLocalTime(&st);
	m_path.AppendFormat(_T("\\Result\\Lcm\\%04d%02d%02d%02d%02d%02d_Lcm.csv"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

	return GetExeFilePath() + m_path;
}

CString SharedInfo::GetLclDataFolder()
{
	CString m_path = _T("");
	SYSTEMTIME st;

	GetLocalTime(&st);
	m_path.AppendFormat(_T("\\Result\\Lcl\\%04d%02d%02d%02d%02d%02d_Lcl.csv"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

	return GetExeFilePath() + m_path;
}

CString SharedInfo::GetBlackLcDataFolder()
{
	CString m_path = _T("");
	SYSTEMTIME st;

	GetLocalTime(&st);
	m_path.AppendFormat(_T("\\Result\\BlackLc\\%04d%02d%02d%02d%02d%02d_BlackLc.csv"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

	return GetExeFilePath() + m_path;
}

CString SharedInfo::GetSamplePolDataFolder()
{
	CString m_path = _T("");
	SYSTEMTIME st;

	GetLocalTime(&st);
	m_path.AppendFormat(_T("\\Result\\SamplePol\\%04d%02d%02d%02d%02d%02d_SamplePol.csv"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

	return GetExeFilePath() + m_path;
}
CString SharedInfo::GetBluSettingDataFolder()
{
	CString m_path = _T("");
	SYSTEMTIME st;

	GetLocalTime(&st);
	m_path.AppendFormat(_T("\\Result\\SamplePol\\%04d%02d%02d%02d%02d%02d_LCAutoBlu.csv"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

	return GetExeFilePath() + m_path;
}

BOOL SharedInfo::SetAlarm(LPCTSTR Msg, UINT nErrCode /*= 0*/)
{
	CVisionAgentDlg *pVisionAgentDlg = (CVisionAgentDlg*)theApp.m_pMainWnd;

	MachineState.bErrorFlag = TRUE;	
	SharedInfo::bMachineStopFlag = TRUE;
	pVisionAgentDlg->m_pAlarmDlg->SetAlarm(Msg, nErrCode);
	pVisionAgentDlg->m_bShowAlarmModeless = TRUE;
	//m_pAlarmDlg->RecalcLayout();
	pVisionAgentDlg->m_pAlarmDlg->ShowWindow(pVisionAgentDlg->m_bShowAlarmModeless);

	return FALSE;
}

BOOL SharedInfo::SetAutoAlarm()
{
	MachineState.bErrorFlag = GetFlowAlarm();

	return MachineState.bErrorFlag;
}

BOOL SharedInfo::GetFlowAlarm()
{
	//Flow Alarm 상태 체크해서 리턴.

	//if (Devs::m_AutoRunFlow.GetAlarm())
	//	return TRUE;
	
	return FALSE;
}

BOOL SharedInfo::GetAlarm()
{
	//Flow Alarm 상태 체크해서 리턴.
	if (MachineState.bErrorFlag)
		return TRUE;

	BOOL bResult = GetFlowAlarm();
	if (bResult)
		return TRUE;
	
	return FALSE;
}

BOOL SharedInfo::ResetAlarm()
{
	BOOL bResult = FALSE;

	//Flow Stop
	
	MachineState.bSemiAutoRunFlag = FALSE;
	MachineState.bErrorFlag = FALSE;
		
	return bResult;
}

BOOL  SharedInfo::SetAxisAlarm(enum_Axis eAxis, enum_ErrorType eErrorType)
{
	CString strAlarmMsg = _T("");
	UINT nAlarmCode = 0;

	strAlarmMsg.Format(GetAxisName(eAxis));

	switch (eErrorType)
	{
	case eSERVO_OFF_ERROR: strAlarmMsg.AppendFormat(_T(" SERVO_OFF_ERROR")); break;
	case eHOME_STATUS_ERROR: strAlarmMsg.AppendFormat(_T(" HOME_STATUS_ERROR")); break;
	case eTARGET_POS_ERROR_BY_SAFETY_MIN: strAlarmMsg.AppendFormat(_T(" TARGET_POS_ERROR_BY_SAFETY_MIN")); break;
	case eTARGET_POS_ERROR_BY_SAFETY_MAX: strAlarmMsg.AppendFormat(_T(" TARGET_POS_ERROR_BY_SAFETY_MAX")); break;
	//case eNOT_WAIT_POS_ERROR: strAlarmMsg.AppendFormat(_T(" NOT_WAIT_POS_ERROR")); break;
	default:
		strAlarmMsg.AppendFormat(_T(" ??"));
		break;
	}

	//KJT 1~99 //Machine Alarm, 100~ Axis Alarm, 500~ Flow Alarm
	nAlarmCode = 100 + (eErrorType * AXIS_MAX + eAxis);

	SetAlarm(strAlarmMsg, nAlarmCode);

	return TRUE;
}

BOOL SharedInfo::GetActualAxisNoByEnumAxis(enum_Axis eAxis, int* pAxisType, int* nRemoteAxis)
{
	int nType = -1; // 0 DirectAjin, 1:RemoteUmac, 2:RemoteAjin
	int nAxis = -1;
	BOOL bResult = TRUE;

	switch (eAxis)
	{
	case AXIS_GANTRY_Y1:			nType = AXIS_TYPE_REMOTE_UMAC;		nAxis = REMOTE_AXIS_UMAC_GANTRY_Y1;		break;
	case AXIS_GANTRY_Y2:			nType = AXIS_TYPE_REMOTE_UMAC;		nAxis = REMOTE_AXIS_UMAC_GANTRY_Y2;		break;
	case AXIS_GANTRY_X:				nType = AXIS_TYPE_REMOTE_UMAC;		nAxis = REMOTE_AXIS_UMAC_GANTRY_X;		break;

	case AXIS_CAMERA_Z1:			nType = AXIS_TYPE_REMOTE_AJIN;		nAxis = REMOTE_AXIS_CAMERA_Z1;		break;
	case AXIS_CAMERA_Z2:			nType = AXIS_TYPE_REMOTE_AJIN;		nAxis = REMOTE_AXIS_CAMERA_Z2;		break;
	default: bResult = FALSE;
		break;
	}
#pragma endregion

	*pAxisType = nType;
	*nRemoteAxis = nAxis;

	return bResult;
}
//-------------------------------------------------------
enum_Axis SharedInfo::GetUmacAxisNoByActualAxis(enum_REMOTE_AXIS_UMAC eUAxis)
{
	enum_Axis eAxis = AXIS_NONE;
	switch (eUAxis)
	{
	case REMOTE_AXIS_UMAC_GANTRY_Y1:
	{
		eAxis = AXIS_GANTRY_Y1;
		break;
	}
	case REMOTE_AXIS_UMAC_GANTRY_Y2:
	{
		eAxis = AXIS_GANTRY_Y2;
		break;
	}
	case REMOTE_AXIS_UMAC_GANTRY_X:
	{
		eAxis = AXIS_GANTRY_X;
		break;
	}
	}
	
	return eAxis;
}
//-------------------------------------------------------
enum_Axis SharedInfo::GetAjinAxisNoByActualAxis(enum_REMOTE_AXIS eAAxis)
{	
	enum_Axis eAxis = (enum_Axis)-1;
	switch (eAAxis)
	{
		
	}
	return eAxis;
}

enum_Axis SharedInfo::GetVisionAxisNoByDirectAxis(enum_DIRECT_AXIS eAxis) //KJT 20200812
{
	enum_Axis eRetAxis = AXIS_NONE;
	switch (eAxis)
	{
	case DIRECT_AXIS_CAMERA_Z1:
		eRetAxis = AXIS_CAMERA_Z1;
		break;
	//case DIRECT_AXIS_AJIN_CAMERA_Z2:
	//	eRetAxis = AXIS_CAMERA_Z2;
	//	break;
	//case DIRECT_AXIS_AJIN_CAMERA_Z3:
	//	eRetAxis = AXIS_CAMERA_Z3;
	//	break;
	}

	return eRetAxis;
}
//-------------------------------------------------------
bool SharedInfo::GetInMotion(enum_Axis eAxis) //KJT 20200812
{
	int nAxisType = -1; // 0 DirectAjin, 1:RemoteUmac, 2:RemoteAjin
	int nAxisNo = -1;
	bool bRet = 0.0;

	GetActualAxisNoByEnumAxis(eAxis, &nAxisType, &nAxisNo);
	switch (nAxisType)
	{
	case AXIS_TYPE_DIRECT_AJIN :
	{
		bRet = VisionAxisInMotionStatus[nAxisNo];
		break;
	}
	case AXIS_TYPE_REMOTE_UMAC:
	{
		bRet = UmacInMotionStatus[nAxisNo];
		break;
	}
	case AXIS_TYPE_REMOTE_AJIN:
	{
		bRet = AxisInMotionStatus[nAxisNo];
		break;
	}
	}

	return bRet;
}
//---------------------------------------------------------
double SharedInfo::GetCmdPos(enum_Axis eAxis) //KJT 20200812
{
	int nAxisType = -1; // 0 DirectAjin, 1:RemoteUmac, 2:RemoteAjin
	int nAxisNo = -1;
	double dPos = 0.0;

	enum_Axis eTemp = eAxis;

	GetActualAxisNoByEnumAxis(eTemp, &nAxisType, &nAxisNo);

	switch (nAxisType)
	{
	case AXIS_TYPE_DIRECT_AJIN:
	{
		dPos = VisionAxisCmdPos[nAxisNo];
		break;
	}
	case AXIS_TYPE_REMOTE_UMAC:
	{
		dPos = UmacCmdPos[nAxisNo];
		break;
	}
	case AXIS_TYPE_REMOTE_AJIN:
	{
		dPos = AxisCmdPos[nAxisNo];
		break;
	}
	}
	return dPos;
}
//---------------------------------------------------------
double SharedInfo::SetCmdPos(enum_Axis eAxis, double dPos) //KJT 20200812
{
	int nAxisType = -1; // 0 DirectAjin, 1:RemoteUmac, 2:RemoteAjin
	int nAxisNo = -1;
	//double dPos = 0.0;

	enum_Axis eTemp = eAxis;

	GetActualAxisNoByEnumAxis(eTemp, &nAxisType, &nAxisNo);

	switch (nAxisType)
	{
	case AXIS_TYPE_DIRECT_AJIN:
	{
		VisionAxisCmdPos[nAxisNo] = dPos;
		break;
	}
	case AXIS_TYPE_REMOTE_UMAC:
	{
		UmacCmdPos[nAxisNo] = dPos;
		break;
	}
	case AXIS_TYPE_REMOTE_AJIN:
	{
		AxisCmdPos[nAxisNo] = dPos;
		break;
	}
	}
	return dPos;
}
//---------------------------------------------------------
double SharedInfo::GetActPos(enum_Axis eAxis) //KJT 20200812
{
	int nAxisType = -1; // 0 DirectAjin, 1:RemoteUmac, 2:RemoteAjin
	int nAxisNo = -1;
	double dPos = 0.0;

	enum_Axis eTemp = eAxis;

	GetActualAxisNoByEnumAxis(eTemp, &nAxisType, &nAxisNo);

	switch (nAxisType)
	{
	case AXIS_TYPE_DIRECT_AJIN:
	{
		VisionAxisActPos[nAxisNo] = dPos;
		break;
	}
	case AXIS_TYPE_REMOTE_UMAC:
	{
		dPos = UmacActPos[nAxisNo];
		break;
	}
	case AXIS_TYPE_REMOTE_AJIN:
	{
		dPos = AxisActPos[nAxisNo];
		break;
	}
	}

	return dPos;
}
//---------------------------------------------------------
double SharedInfo::SetActPos(enum_Axis eAxis, double dPos) //KJT 20200812
{
	int nAxisType = -1; // 0 DirectAjin, 1:RemoteUmac, 2:RemoteAjin
	int nAxisNo = -1;

	enum_Axis eTemp = eAxis;

	GetActualAxisNoByEnumAxis(eTemp, &nAxisType, &nAxisNo);
	switch (nAxisType)
	{
	case AXIS_TYPE_DIRECT_AJIN:
	{
		VisionAxisActPos[nAxisNo] = dPos;
		break;
	}
	case AXIS_TYPE_REMOTE_UMAC:
	{
		UmacActPos[nAxisNo] = dPos;
		break;
	}
	case AXIS_TYPE_REMOTE_AJIN:
	{
		AxisActPos[nAxisNo] = dPos;
		break;
	}
	}
	return dPos;
}
//---------------------------------------------------------
double	SharedInfo::SetCmdVel(enum_Axis eAxis, double dVel) //KJT 20200812
{
	int nAxisType = -1; // 0 DirectAjin, 1:RemoteUmac, 2:RemoteAjin
	int nAxisNo = -1;

	GetActualAxisNoByEnumAxis(eAxis, &nAxisType, &nAxisNo);
	switch (nAxisType)
	{
	case AXIS_TYPE_DIRECT_AJIN:
	{
		VisionAxisCmdVel[nAxisNo] = dVel;
		break;
	}
	case AXIS_TYPE_REMOTE_UMAC:
	{
		UmacCmdVel[nAxisNo] = dVel;
		break;
	}
	case AXIS_TYPE_REMOTE_AJIN:
	{
		AxisCmdVel[nAxisNo] = dVel;
		break;
	}
	}

	return dVel;
}

double SharedInfo::GetCmdVel(enum_Axis eAxis)
{
	int nAxisType = -1; // 0 DirectAjin, 1:RemoteUmac, 2:RemoteAjin
	int nAxisNo = -1;
	double value = 0.0;

	GetActualAxisNoByEnumAxis(eAxis, &nAxisType, &nAxisNo);
	switch (nAxisType)
	{
	case AXIS_TYPE_DIRECT_AJIN: value = VisionAxisCmdVel[nAxisNo]; break; //####
	case AXIS_TYPE_REMOTE_UMAC: value = UmacCmdVel[nAxisNo]; break;
	case AXIS_TYPE_REMOTE_AJIN: value = AxisCmdVel[nAxisNo]; break;
	}

	return value;
}
int	SharedInfo::GetHomeResult(enum_Axis eAxis)
{
	int nAxisType = -1; // 0 DirectAjin, 1:RemoteUmac, 2:RemoteAjin
	int nAxisNo = -1;
	int value = -1;

	GetActualAxisNoByEnumAxis(eAxis, &nAxisType, &nAxisNo);
	switch (nAxisType)
	{
	case AXIS_TYPE_DIRECT_AJIN: value = VisionAxisHomeResult[nAxisNo]; break; //####
	case AXIS_TYPE_REMOTE_UMAC: value = UmacHomeStatus[nAxisNo]; break;
	case AXIS_TYPE_REMOTE_AJIN: value = AxisHomeResult[nAxisNo]; break;
	}

	return value;
}
int	SharedInfo::GetHomeStatus(enum_Axis eAxis)
{
	int nAxisType = -1; // 0 DirectAjin, 1:RemoteUmac, 2:RemoteAjin
	int nAxisNo = -1;
	int value = -1;

	GetActualAxisNoByEnumAxis(eAxis, &nAxisType, &nAxisNo);
	switch (nAxisType)
	{
	case AXIS_TYPE_DIRECT_AJIN: value = VisionAxisHomeStatus[nAxisNo]; break; //####
	case AXIS_TYPE_REMOTE_UMAC: value = UmacHomeStatus[nAxisNo]; break;
	case AXIS_TYPE_REMOTE_AJIN: value = AxisHomeStatus[nAxisNo]; break;
	}

	return value;
}
int	SharedInfo::GetHomeSignal(enum_Axis eAxis)
{
	int nAxisType = -1; // 0 DirectAjin, 1:RemoteUmac, 2:RemoteAjin
	int nAxisNo = -1;
	int value = 0;

	GetActualAxisNoByEnumAxis(eAxis, &nAxisType, &nAxisNo);
	switch (nAxisType)
	{
	case AXIS_TYPE_DIRECT_AJIN: value = VisionAxisHomeSignal[nAxisNo]; break; //####
	case AXIS_TYPE_REMOTE_UMAC: value = UmacHomeSignal[nAxisNo]; break;
	case AXIS_TYPE_REMOTE_AJIN: value = AxisHomeSignal[nAxisNo]; break;
	}

	return value;
}
int	SharedInfo::GetPLimitSignal(enum_Axis eAxis)
{
	int nAxisType = -1; // 0 DirectAjin, 1:RemoteUmac, 2:RemoteAjin
	int nAxisNo = -1;
	int value = 0;

	GetActualAxisNoByEnumAxis(eAxis, &nAxisType, &nAxisNo);
	switch (nAxisType)
	{
	case AXIS_TYPE_DIRECT_AJIN: value = VisionAxisPLimitSignal[nAxisNo]; break; //####
	case AXIS_TYPE_REMOTE_UMAC: value = UmacPLimitSignal[nAxisNo]; break;
	case AXIS_TYPE_REMOTE_AJIN: value = AxisPLimitSignal[nAxisNo]; break;
	}

	return value;
}
int	SharedInfo::GetNLimitSignal(enum_Axis eAxis)
{
	int nAxisType = -1; // 0 DirectAjin, 1:RemoteUmac, 2:RemoteAjin
	int nAxisNo = -1;
	int value = 0;

	GetActualAxisNoByEnumAxis(eAxis, &nAxisType, &nAxisNo);
	switch (nAxisType)
	{
	case AXIS_TYPE_DIRECT_AJIN: value = VisionAxisNLimitSignal[nAxisNo]; break; //####
	case AXIS_TYPE_REMOTE_UMAC: value = UmacNLimitSignal[nAxisNo]; break;
	case AXIS_TYPE_REMOTE_AJIN: value = AxisNLimitSignal[nAxisNo]; break;
	}

	return value;
}
int	SharedInfo::GetServoOnStatus(enum_Axis eAxis)
{
	int nAxisType = -1; // 0 DirectAjin, 1:RemoteUmac, 2:RemoteAjin
	int nAxisNo = -1;
	int value = -1;

	GetActualAxisNoByEnumAxis(eAxis, &nAxisType, &nAxisNo);
	switch (nAxisType)
	{
	case AXIS_TYPE_DIRECT_AJIN: value = VisionAxisServoOnStatus[nAxisNo]; break; //####
	case AXIS_TYPE_REMOTE_UMAC: value = UmacServoOnStatus[nAxisNo]; break;
	case AXIS_TYPE_REMOTE_AJIN: value = AxisServoOnStatus[nAxisNo]; break; //
	}

	return value;
}


int SharedInfo::GetAlarmStatus(enum_Axis eAxis)
{
	int nAxisType = -1; // 0 DirectAjin, 1:RemoteUmac, 2:RemoteAjin
	int nAxisNo = -1;
	int value = 1;
#ifndef SIM_MODE
	GetActualAxisNoByEnumAxis(eAxis, &nAxisType, &nAxisNo);
	switch (nAxisType)
	{
	case AXIS_TYPE_DIRECT_AJIN: value = SharedInfo::VisionAxisAlarmStatus[nAxisNo]; break; //####
	case AXIS_TYPE_REMOTE_UMAC: value = SharedInfo::UmacAlarmStatus[nAxisNo]; break;
	case AXIS_TYPE_REMOTE_AJIN: value = SharedInfo::AxisAlarmStatus[nAxisNo]; break;
	}
#endif // !SIM_MODE

	return value;
}
//---------------------------------------------------------
//DI
BOOL	SharedInfo::Is_Dig_Input(int nIndex)
{
	return	DInputValue[nIndex];
}
//---------------------------------------------------------
//DO
BOOL	SharedInfo::Set_Dig_Output(int nIndex, bool bOnOff)
{
	DOutputValue[nIndex] = bOnOff;
	return Is_Dig_Output(nIndex);
}
//---------------------------------------------------------
BOOL	SharedInfo::Is_Dig_Output(int nIndex)
{
	return	DOutputValue[nIndex];
}
//---------------------------------------------------------
//AI
double	SharedInfo::Get_AI_Data(int nIndex)
{
	return AInputValue[nIndex];
}


BOOL SharedInfo::GetActualIoNumByEnumDo(enum_Do eIoNum, int* pAxisNo)
{

	*pAxisNo = (int)eIoNum;

	return TRUE;
}

BOOL SharedInfo::GetActualIoNumByEnumAo(enum_Ao eIoNum, int* pAxisNo)
{

	*pAxisNo = (int)eIoNum;

	return TRUE;
}

BOOL SharedInfo::GetActualIoNumByEnumDi(enum_Di eIoNum, int* pAxisNo)
{
	*pAxisNo = (int)eIoNum;

	return TRUE;
}

BOOL SharedInfo::GetActualIoNumByEnumAi(enum_Ai eIoNum, int* pAxisNo)
{

	*pAxisNo = (int)eIoNum;

	return TRUE;
}

int SharedInfo::SaveAlarmList()
{
	CStdioFile OutFile;

	int i, nRtn = TRUE;
	TCHAR tchPathName[256] = { NULL };
	TCHAR tchFileName[256] = { NULL };
	TCHAR tchReviewFileName[256] = { NULL };
	CString Str, StrStickID;

	wsprintf(tchPathName, _T("%s\\%s"), GetExeFilePath(), SharedInfo::STR_ALARM_LIST_FILE_PATH);

	if (OutFile.Open((LPCTSTR)tchPathName, CFile::modeWrite | CFile::modeCreate | CFile::typeText) == FALSE) return 0;

	Str.Format(_T("\t#BEGIN\n"));
	OutFile.WriteString(Str);

	for (i = 0; i < 100; i++)
	{
		if (AlarmList[i].AlarmDate.IsEmpty())
			break;

		Str.Format(_T("%s, %s, %d, %d, %s \n"), AlarmList[i].AlarmDate, AlarmList[i].AlarmTime
			, AlarmList[i].AlarmCode, AlarmList[i].AlarmLevel, AlarmList[i].AlarmText);
		OutFile.WriteString(Str);

	}

	Str.Format(_T("\t#END"));
	OutFile.WriteString(Str);

	OutFile.Close();

	return 0;
}

int SharedInfo::LoadAlarmList()
{
	CStdioFile InFile;
	CString strData, strDataTemp;
	CString strPointData[5];
	int nTokenCount = 0;
	int nTotalCount = 0;

	TCHAR* chDelimiterBlank = _T("\t");
	TCHAR* chDelimiterComma = _T(",");
	TCHAR* pchDelimiter = NULL;
	TCHAR* pchToken = NULL;
	TCHAR chData[256];
	TCHAR tchPathName[256];

	wsprintf(tchPathName, _T("%s\\%s"), GetExeFilePath(), SharedInfo::STR_ALARM_LIST_FILE_PATH);

	if (InFile.Open((LPCTSTR)tchPathName, CFile::modeRead | CFile::typeText) == FALSE) return 0;


	while (InFile.ReadString(strData) != FALSE) {
		strData.TrimLeft();
		//strData.TrimRight();

		if (!strData.Compare(_T("#BEGIN")) || strData.GetLength() < 1) continue;
		if (!strData.Compare(_T("#END")) || strData == EOF) break;

		if (!pchDelimiter) {
			if (strData.Find((LPWSTR)chDelimiterComma) != -1) {
				pchDelimiter = chDelimiterComma;
			}
			else {
				pchDelimiter = chDelimiterBlank;
			}
		}

		wsprintf(chData, _T("%s"), strData);
		pchToken = _tcstok(chData, pchDelimiter);

		nTokenCount = 0;

		while (pchToken != NULL) {

			strPointData[nTokenCount].Format(_T("%s"), pchToken);
			strPointData[nTokenCount].TrimLeft();
			strPointData[nTokenCount].TrimRight();

			//pchToken = strtok(NULL, pchDelimiter);   
			pchToken = _tcstok(NULL, pchDelimiter);
			nTokenCount++;
		}

		AlarmList[nTotalCount].AlarmDate = strPointData[0];
		AlarmList[nTotalCount].AlarmTime = strPointData[1];
		AlarmList[nTotalCount].AlarmCode = _ttoi(strPointData[2]);
		AlarmList[nTotalCount].AlarmLevel = _ttoi(strPointData[3]);
		AlarmList[nTotalCount].AlarmText = strPointData[4];

		nTotalCount++;
	}

	InFile.Close();

	AlarmCount = nTotalCount;

	return 0;
}

BOOL SharedInfo::GetAutoSpeed(enum_Axis eAxis, double *pdVel, double *pdAccel, double *pdDecel)
{
	double dVel = 0.0, dAccel = 0.0, dDecel = 0.0;
	
	dVel = CMachineData::m_MachineDataMotor.Info.dAutoVel[eAxis];
	dAccel = CMachineData::m_MachineDataMotor.Info.dAutoAccel[eAxis];
	dDecel = CMachineData::m_MachineDataMotor.Info.dAutoDecel[eAxis];

	*pdVel = dVel;
	*pdAccel = dAccel;
	*pdDecel = dDecel;

	return TRUE;
}
BOOL SharedInfo::GetManualSpeed(enum_Axis eAxis, enum_AXIS_SPEED eSpeedType, double *pdVel, double *pdAccel, double *pdDecel)
{
	double dVel = 0.0, dAccel = 0.0, dDecel = 0.0;

	switch (eSpeedType)
	{
	case eAXIS_SPEED_LOW:
		dVel = CMachineData::m_MachineDataMotor.Info.dManualLowVel[eAxis];
		dAccel = CMachineData::m_MachineDataMotor.Info.dManualLowAccel[eAxis];
		dDecel = CMachineData::m_MachineDataMotor.Info.dManualLowDecel[eAxis];
		break;
	case eAXIS_SPEED_MEDIUM:
		dVel = CMachineData::m_MachineDataMotor.Info.dManualMediumVel[eAxis];
		dAccel = CMachineData::m_MachineDataMotor.Info.dManualMediumAccel[eAxis];
		dDecel = CMachineData::m_MachineDataMotor.Info.dManualMediumDecel[eAxis];
		break;
	case eAXIS_SPEED_HIGH:
		dVel = CMachineData::m_MachineDataMotor.Info.dManualHighVel[eAxis];
		dAccel = CMachineData::m_MachineDataMotor.Info.dManualHighAccel[eAxis];
		dDecel = CMachineData::m_MachineDataMotor.Info.dManualHighDecel[eAxis];
		break;
	default:
		return FALSE;
	}
	dAccel = CMachineData::m_MachineDataMotor.Info.dAutoAccel[eAxis];
	dDecel = CMachineData::m_MachineDataMotor.Info.dAutoDecel[eAxis];

	
	//KJT 20200812 Temp
#if 1
	*pdVel = dVel;
	*pdAccel = dAccel;
	*pdDecel = dDecel;
#else
	*pdVel = 10.0;
	*pdAccel = 20.0;
	*pdDecel = 20.0;
#endif

	return TRUE;
}
CString SharedInfo::GetAxisName(enum_Axis eAxis)
{
	CString strAxisName = _T("");

	switch (eAxis)
	{
	case AXIS_GANTRY_Y1: strAxisName = _T("Gantry Y1"); break;
	case AXIS_GANTRY_Y2: strAxisName = _T("Gantry Y2"); break;
	case AXIS_CAMERA_Z1: strAxisName = _T("Gantry Z1"); break;
	case AXIS_CAMERA_Z2: strAxisName = _T("Gantry Z2"); break;
	case AXIS_GANTRY_X: strAxisName = _T("Gantry X"); break;
	}

	return strAxisName;
}

BOOL SharedInfo::CheckAllAxisServoOn(CString *strAxisName)
{
	CString Str = _T("");
	int i = 0;

	for (i = 0; i < AXIS_MAX; i++)
	{
		if (i == AXIS_GANTRY_Y1 || i == AXIS_GANTRY_Y2 /*||
			i == AXIS_INKJET_Y*/)
			continue;

		if (SharedInfo::GetServoOnStatus((enum_Axis)i) == FALSE)
		{
			Str.Format(_T("Axis%d"), i);
			*strAxisName = Str;
			return FALSE;
		}
	}

	return TRUE;
}

BOOL SharedInfo::CheckAllAxisHomeStatus(CString *strAxisName)
{
	CString Str = _T("");
	int i = 0;

	for (i = 0; i < AXIS_MAX; i++)
	{
		if (i == AXIS_GANTRY_Y1 || i == AXIS_GANTRY_Y2 /*||
			i == AXIS_INKJET_Y*/)
			continue;

		if (SharedInfo::GetHomeStatus((enum_Axis)i) == FALSE)
		{
			Str.Format(_T("Axis%d"), i);
			*strAxisName = Str;
			return FALSE;
		}
	}

	return TRUE;
}
BOOL SharedInfo::CheckSafetyPos(enum_Axis eAxis, double dTargetPos, CString *strDiscription, int *pnSafetyPosErrorBy)
{
	CString Str = _T("");

	if (dTargetPos > CMachineData::m_MachineDataMotor.Info.dSafetyPosMax[eAxis])
	{
		Str.Format(_T("%s Safety Pos Max Interlock !!"), GetAxisName(eAxis));
		*strDiscription = Str;
		*pnSafetyPosErrorBy = eTARGET_POS_ERROR_BY_SAFETY_MAX;
		return FALSE;
	}
	else if (dTargetPos < CMachineData::m_MachineDataMotor.Info.dSafetyPosMin[eAxis])
	{
		Str.Format(_T("%s Safety Pos Min Interlock !!"), GetAxisName(eAxis));
		*strDiscription = Str;
		*pnSafetyPosErrorBy = eTARGET_POS_ERROR_BY_SAFETY_MIN;
		return FALSE;
	}

	return TRUE;
}

BOOL SharedInfo::CheckSystemSafetyPos(enum_Axis eAxis, double dTargetPos, CString *strDiscription)//, int *pnSafetyPosErrorBy)
{
	if (CSystemData::m_Safety.Info.m_nUseSystemSafety == 0) return TRUE;

	CString Str = _T("");
	double dPosX, dPosY, dPosZ;
	double dVirtualLoadPosY, dVirtualUnloadPosY;

	double dLoaderYPos, dPpaperUnloaderY;
	double dLoaderXPos, dPpaperUnloaderX;

	switch (eAxis)
	{
	case AXIS_GANTRY_Y1:
		break;
	case AXIS_GANTRY_Y2:
		break;
	case AXIS_CAMERA_Z1:
		break;
	case AXIS_CAMERA_Z2:
		break;
	case AXIS_GANTRY_X:
		break;
	}

	return TRUE;
}

void SharedInfo::CStringToPChar(CString str, char pch[256])
{
	USES_CONVERSION;

	memset(pch, 0, sizeof(pch));
	char* pcBuf = W2A(str.GetBuffer());
	if (strlen(pcBuf) < sizeof(pch))
		memcpy(pch, pcBuf, strlen(pcBuf));
	else
		memcpy(pch, pcBuf, sizeof(pch));

	str.ReleaseBuffer(); //!!
}

void SharedInfo::UpdateSwAlignData(double dAlignPointValue[2][4], double dAlignResultValue[2][4]) //KJT 20210304
{
	double dCmdPosXY[4][2] = { 0.0, };
	double dActPosXY[4][2] = { 0.0, };

	//if (CModelData::m_InspectionPara.Info.nAlignDataUseMode == eALIGN_DATA_USE_SW_ALIGN) //SWAlignData
	{
		//LT
		dCmdPosXY[0][0] = dAlignPointValue[0][1];
		dCmdPosXY[0][1] = dAlignPointValue[1][1];
		//RT
		dCmdPosXY[1][0] = dAlignPointValue[0][2];
		dCmdPosXY[1][1] = dAlignPointValue[1][2];
		//LB
		dCmdPosXY[2][0] = dAlignPointValue[0][0];
		dCmdPosXY[2][1] = dAlignPointValue[1][0];
		//RB
		dCmdPosXY[3][0] = dAlignPointValue[0][3];
		dCmdPosXY[3][1] = dAlignPointValue[1][3];

		//LT
		dActPosXY[0][0] = dAlignPointValue[0][1] + dAlignResultValue[0][1];
		dActPosXY[0][1] = dAlignPointValue[1][1] + dAlignResultValue[1][1];
		//RT
		dActPosXY[1][0] = dAlignPointValue[0][2] + dAlignResultValue[0][2];
		dActPosXY[1][1] = dAlignPointValue[1][2] + dAlignResultValue[1][2];
		//LB
		dActPosXY[2][0] = dAlignPointValue[0][0] + dAlignResultValue[0][0];
		dActPosXY[2][1] = dAlignPointValue[1][0] + dAlignResultValue[1][0];
		//RB
		dActPosXY[3][0] = dAlignPointValue[0][3] + dAlignResultValue[0][3];
		dActPosXY[3][1] = dAlignPointValue[1][3] + dAlignResultValue[1][3];

		Devs::m_MappingProc.CalibSWMapping_MainBegin(eMAPPING_ID_10X);

		for (int i = 0; i < 4; i++)
		{
			Devs::m_MappingProc.CalibSWMapping_MainSetData(eMAPPING_ID_10X, i, dActPosXY[i][0], dActPosXY[i][1], dCmdPosXY[i][0], dCmdPosXY[i][1]);
		}

		Devs::m_MappingProc.CalibSWMapping_MainEnd(eMAPPING_ID_10X);

		Total_Msg(_T("CalibSWMapping Ok"));
	}
	//else //XYTAlignData
	{
		//LT
		dCmdPosXY[0][0] = dAlignPointValue[0][1];
		dCmdPosXY[0][1] = dAlignPointValue[1][1];
		//RT
		dCmdPosXY[1][0] = dAlignPointValue[0][2];
		dCmdPosXY[1][1] = dAlignPointValue[1][2];
		//RB
		dCmdPosXY[2][0] = dAlignPointValue[0][3];
		dCmdPosXY[2][1] = dAlignPointValue[1][3];
		//LB
		dCmdPosXY[3][0] = dAlignPointValue[0][0];
		dCmdPosXY[3][1] = dAlignPointValue[1][0];

		//LT
		dActPosXY[0][0] = dAlignPointValue[0][1] + dAlignResultValue[0][1];
		dActPosXY[0][1] = dAlignPointValue[1][1] + dAlignResultValue[1][1];
		//RT
		dActPosXY[1][0] = dAlignPointValue[0][2] + dAlignResultValue[0][2];
		dActPosXY[1][1] = dAlignPointValue[1][2] + dAlignResultValue[1][2];
		//RB
		dActPosXY[2][0] = dAlignPointValue[0][3] + dAlignResultValue[0][3];
		dActPosXY[2][1] = dAlignPointValue[1][3] + dAlignResultValue[1][3];
		//LB
		dActPosXY[3][0] = dAlignPointValue[0][0] + dAlignResultValue[0][0];
		dActPosXY[3][1] = dAlignPointValue[1][0] + dAlignResultValue[1][0];

		Devs::m_MappingProc.MakeXYTAlignData(eMAPPING_ID_10X, dCmdPosXY, dActPosXY);

		Total_Msg(_T("MakeXYTAlignData Ok"));
	}
}


#pragma region //Edge Align Pos.
//DO NOT USE
stPOS_XYZ SharedInfo::GetReview10X_EdgeAlignCellPosXY_LB()  //KJT 20210301
{
	stPOS_XYZ stPosXYZ;

	INT nMaxCellCntX = (INT)CModelData::m_MaterialPara.Info.nCellCountX;
	INT nMaxCellCntY = (INT)CModelData::m_MaterialPara.Info.nCellCountY;

	
	//Edge Cell LB X
	stPosXYZ.dPosX = CModelData::m_MaterialPara.Info.dCellLeftTopX[0][0] * STICK_FLIP_XY;
	stPosXYZ.dPosX += (CModelData::m_MaterialPara.Info.dCellPitchX * (nMaxCellCntX - 1)) * STICK_FLIP_XY;
	stPosXYZ.dPosX += CModelData::m_MaterialPara.Info.dSlotTotalPitchX[nMaxCellCntX - 1][0] * STICK_FLIP_XY;
	stPosXYZ.dPosX += CModelData::m_MaterialPara.Info.dSlotCenterShiftX[nMaxCellCntX - 1][0] * STICK_FLIP_XY * 2;
	stPosXYZ.dPosX += CModelData::m_MaterialPara.Info.dSlotPitchX[nMaxCellCntX - 1][0];

	//Edge Cell LB Y
	stPosXYZ.dPosY = CModelData::m_MaterialPara.Info.dCellLeftTopY[0][0] * STICK_FLIP_XY;

	//stPosXYZ.dPosZ1 = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_InspectionReview_Pos;
	//stPosXYZ.dPosAoiZ = CManualData::m_ManualDataGantry.Info.m_dGantry_Z2_Wait_Pos;
	//stPosXYZ.dPos3dZ = CManualData::m_ManualDataGantry.Info.m_d3D_Camera_Main_Z_Wait_Pos;
	

	return stPosXYZ;
}
//DO NOT USE
stPOS_XYZ SharedInfo::GetReview10X_EdgeAlignCellPosXY_LT() //KJT 20210301
{
	stPOS_XYZ stPosXYZ;

	INT nMaxCellCntX = (INT)CModelData::m_MaterialPara.Info.nCellCountX;
	INT nMaxCellCntY = (INT)CModelData::m_MaterialPara.Info.nCellCountY;

	//Edge Cell LT X
	stPosXYZ.dPosX = CModelData::m_MaterialPara.Info.dCellLeftTopX[0][0] * STICK_FLIP_XY;
	stPosXYZ.dPosX += (CModelData::m_MaterialPara.Info.dCellPitchX * (nMaxCellCntX - 1)) * STICK_FLIP_XY;
	stPosXYZ.dPosX += CModelData::m_MaterialPara.Info.dSlotTotalPitchX[nMaxCellCntX - 1][0] * STICK_FLIP_XY;
	stPosXYZ.dPosX += CModelData::m_MaterialPara.Info.dSlotCenterShiftX[nMaxCellCntX - 1][0] * STICK_FLIP_XY * 2;
	stPosXYZ.dPosX += CModelData::m_MaterialPara.Info.dSlotPitchX[nMaxCellCntX - 1][0];

	//Edge Cell LT Y
	stPosXYZ.dPosY = CModelData::m_MaterialPara.Info.dCellLeftTopY[0][0] * STICK_FLIP_XY;
	stPosXYZ.dPosY += (CModelData::m_MaterialPara.Info.dCellPitchY * (nMaxCellCntY - 1));
	stPosXYZ.dPosY += CModelData::m_MaterialPara.Info.dSlotTotalPitchY[nMaxCellCntY - 1][0];
	stPosXYZ.dPosY += CModelData::m_MaterialPara.Info.dSlotCenterShiftY[nMaxCellCntY - 1][0] * STICK_FLIP_XY * 2;

	//stPosXYZ.dPosZ1 = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_InspectionReview_Pos;
	//stPosXYZ.dPosAoiZ = CManualData::m_ManualDataGantry.Info.m_dGantry_Z2_Wait_Pos;
	//stPosXYZ.dPos3dZ = CManualData::m_ManualDataGantry.Info.m_d3D_Camera_Main_Z_Wait_Pos;

	return stPosXYZ;
}
//DO NOT USE
stPOS_XYZ SharedInfo::GetReview10X_EdgeAlignCellPosXY_RT() //KJT 20210301
{
	stPOS_XYZ stPosXYZ;

	INT nMaxCellCntX = (INT)CModelData::m_MaterialPara.Info.nCellCountX;
	INT nMaxCellCntY = (INT)CModelData::m_MaterialPara.Info.nCellCountY;

	//Edge Cell RT X
	stPosXYZ.dPosX = CModelData::m_MaterialPara.Info.dCellLeftTopX[0][0] * STICK_FLIP_XY;

	//Edge Cell RT Y
	stPosXYZ.dPosY = CModelData::m_MaterialPara.Info.dCellLeftTopY[0][0] * STICK_FLIP_XY;
	stPosXYZ.dPosY += (CModelData::m_MaterialPara.Info.dCellPitchY * (nMaxCellCntY - 1));
	stPosXYZ.dPosY += CModelData::m_MaterialPara.Info.dSlotTotalPitchY[nMaxCellCntY - 1][0];
	stPosXYZ.dPosY += CModelData::m_MaterialPara.Info.dSlotCenterShiftY[nMaxCellCntY - 1][0] * STICK_FLIP_XY * 2;

	//stPosXYZ.dPosZ1 = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_InspectionReview_Pos;
	//stPosXYZ.dPosAoiZ = CManualData::m_ManualDataGantry.Info.m_dGantry_Z2_Wait_Pos;
	//stPosXYZ.dPos3dZ = CManualData::m_ManualDataGantry.Info.m_d3D_Camera_Main_Z_Wait_Pos;

	return stPosXYZ;
}
//DO NOT USE
stPOS_XYZ SharedInfo::GetReview10X_EdgeAlignCellPosXY_RB() //KJT 20210301
{
	stPOS_XYZ stPosXYZ;

	INT nMaxCellCntX = (INT)CModelData::m_MaterialPara.Info.nCellCountX;
	INT nMaxCellCntY = (INT)CModelData::m_MaterialPara.Info.nCellCountY;

	//Edge Cell RB X
	stPosXYZ.dPosX = CModelData::m_MaterialPara.Info.dCellLeftTopX[0][0] * STICK_FLIP_XY;

	//Edge Cell RB Y
	stPosXYZ.dPosY = CModelData::m_MaterialPara.Info.dCellLeftTopY[0][0] * STICK_FLIP_XY;

	//stPosXYZ.dPosZ1 = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_InspectionReview_Pos;
	//stPosXYZ.dPosAoiZ = CManualData::m_ManualDataGantry.Info.m_dGantry_Z2_Wait_Pos;
	//stPosXYZ.dPos3dZ = CManualData::m_ManualDataGantry.Info.m_d3D_Camera_Main_Z_Wait_Pos;

	return stPosXYZ;
}

//DO NOT USE
//Tension
stPOS_XYZ SharedInfo::GetReview10X_EdgeTensionAlignCellPosXY_LB()  //KJT 20210225
{
	stPOS_XYZ stPosXYZ;

	INT nMaxCellCntX = (INT)CModelData::m_AtMaterialPara.Info.nCellCountX;
	INT nMaxCellCntY = (INT)CModelData::m_AtMaterialPara.Info.nCellCountY;

	//Edge Tension Cell LB X
	stPosXYZ.dPosX = CModelData::m_AtMaterialPara.Info.dCellLeftTopX[0][0] * STICK_FLIP_XY;
	stPosXYZ.dPosX += (CModelData::m_AtMaterialPara.Info.dCellPitchX * (nMaxCellCntX - 1)) * STICK_FLIP_XY;
	stPosXYZ.dPosX += CModelData::m_AtMaterialPara.Info.dSlotTotalPitchX[nMaxCellCntX - 1][0] * STICK_FLIP_XY;
	stPosXYZ.dPosX += CModelData::m_AtMaterialPara.Info.dSlotCenterShiftX[nMaxCellCntX - 1][0] * STICK_FLIP_XY * 2;
	stPosXYZ.dPosX += CModelData::m_AtMaterialPara.Info.dSlotPitchX[nMaxCellCntX - 1][0];

	//Edge Tension Cell LB Y
	stPosXYZ.dPosY = CModelData::m_AtMaterialPara.Info.dCellLeftTopY[0][0] * STICK_FLIP_XY;

	//stPosXYZ.dPosZ1 = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_InspectionReview_Pos;
	//stPosXYZ.dPosAoiZ = CManualData::m_ManualDataGantry.Info.m_dGantry_Z2_Wait_Pos;
	//stPosXYZ.dPos3dZ = CManualData::m_ManualDataGantry.Info.m_d3D_Camera_Main_Z_Wait_Pos;

	return stPosXYZ;
}
//DO NOT USE
stPOS_XYZ SharedInfo::GetReview10X_EdgeTensionAlignCellPosXY_LT()
{
	stPOS_XYZ stPosXYZ;

	INT nMaxCellCntX = (INT)CModelData::m_AtMaterialPara.Info.nCellCountX;
	INT nMaxCellCntY = (INT)CModelData::m_AtMaterialPara.Info.nCellCountY;

	//Edge Tension Cell LT X
	stPosXYZ.dPosX = CModelData::m_AtMaterialPara.Info.dCellLeftTopX[0][0] * STICK_FLIP_XY;
	stPosXYZ.dPosX += (CModelData::m_AtMaterialPara.Info.dCellPitchX * (nMaxCellCntX - 1)) * STICK_FLIP_XY;
	stPosXYZ.dPosX += CModelData::m_AtMaterialPara.Info.dSlotTotalPitchX[nMaxCellCntX - 1][0] * STICK_FLIP_XY;
	stPosXYZ.dPosX += CModelData::m_AtMaterialPara.Info.dSlotCenterShiftX[nMaxCellCntX - 1][0] * STICK_FLIP_XY * 2;
	stPosXYZ.dPosX += CModelData::m_AtMaterialPara.Info.dSlotPitchX[nMaxCellCntX - 1][0];

	//Edge Tension Cell LT Y
	stPosXYZ.dPosY = CModelData::m_AtMaterialPara.Info.dCellLeftTopY[0][0] * STICK_FLIP_XY;
	stPosXYZ.dPosY += (CModelData::m_AtMaterialPara.Info.dCellPitchY * (nMaxCellCntY - 1));
	stPosXYZ.dPosY += CModelData::m_AtMaterialPara.Info.dSlotTotalPitchY[nMaxCellCntY - 1][0];
	stPosXYZ.dPosY += CModelData::m_AtMaterialPara.Info.dSlotCenterShiftY[nMaxCellCntY - 1][0] * STICK_FLIP_XY * 2;

	//stPosXYZ.dPosZ1 = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_InspectionReview_Pos;
	//stPosXYZ.dPosAoiZ = CManualData::m_ManualDataGantry.Info.m_dGantry_Z2_Wait_Pos;
	//stPosXYZ.dPos3dZ = CManualData::m_ManualDataGantry.Info.m_d3D_Camera_Main_Z_Wait_Pos;

	return stPosXYZ;
}
//DO NOT USE
stPOS_XYZ SharedInfo::GetReview10X_EdgeTensionAlignCellPosXY_RT()  //KJT 20210225
{
	stPOS_XYZ stPosXYZ;

	INT nMaxCellCntX = (INT)CModelData::m_AtMaterialPara.Info.nCellCountX;
	INT nMaxCellCntY = (INT)CModelData::m_AtMaterialPara.Info.nCellCountY;

	//Edge Tension Cell RT X
	stPosXYZ.dPosX = CModelData::m_AtMaterialPara.Info.dCellLeftTopX[0][0] * STICK_FLIP_XY;

	//Edge Tension Cell RT Y
	stPosXYZ.dPosY = CModelData::m_AtMaterialPara.Info.dCellLeftTopY[0][0] * STICK_FLIP_XY;
	stPosXYZ.dPosY += (CModelData::m_AtMaterialPara.Info.dCellPitchY * (nMaxCellCntY - 1));
	stPosXYZ.dPosY += CModelData::m_AtMaterialPara.Info.dSlotTotalPitchY[nMaxCellCntY - 1][0];
	stPosXYZ.dPosY += CModelData::m_AtMaterialPara.Info.dSlotCenterShiftY[nMaxCellCntY - 1][0] * STICK_FLIP_XY * 2;

	//stPosXYZ.dPosZ1 = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_InspectionReview_Pos;
	//stPosXYZ.dPosAoiZ = CManualData::m_ManualDataGantry.Info.m_dGantry_Z2_Wait_Pos;
	//stPosXYZ.dPos3dZ = CManualData::m_ManualDataGantry.Info.m_d3D_Camera_Main_Z_Wait_Pos;

	return stPosXYZ;
}
stPOS_XYZ SharedInfo::GetReview10X_EdgeTensionAlignCellPosXY_RB()  //KJT 20210225
{
	stPOS_XYZ stPosXYZ;

	INT nMaxCellCntX = (INT)CModelData::m_AtMaterialPara.Info.nCellCountX;
	INT nMaxCellCntY = (INT)CModelData::m_AtMaterialPara.Info.nCellCountY;

	//Edge Tension Cell RB X
	stPosXYZ.dPosX = CModelData::m_AtMaterialPara.Info.dCellLeftTopX[0][0] * STICK_FLIP_XY;

	//Edge Tension Cell RB Y
	stPosXYZ.dPosY = CModelData::m_AtMaterialPara.Info.dCellLeftTopY[0][0] * STICK_FLIP_XY;

	//stPosXYZ.dPosZ1 = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_InspectionReview_Pos;
	//stPosXYZ.dPosAoiZ = CManualData::m_ManualDataGantry.Info.m_dGantry_Z2_Wait_Pos;
	//stPosXYZ.dPos3dZ = CManualData::m_ManualDataGantry.Info.m_d3D_Camera_Main_Z_Wait_Pos;

	return stPosXYZ;
}

stPOS_XYZ SharedInfo::GetReview10X_EdgeAlignSlotPosXY_LB()
{
	stPOS_XYZ stPosXYZ;

	INT nMaxCellCntX = (INT)CModelData::m_MaterialPara.Info.nCellCountX;
	INT nMaxCellCntY = (INT)CModelData::m_MaterialPara.Info.nCellCountY;

	//Edge Slot LB X
	stPosXYZ.dPosX = CModelData::m_MaterialPara.Info.dCellLeftTopX[0][nMaxCellCntY - 1];
	stPosXYZ.dPosX += CModelData::m_MaterialPara.Info.dSlotCenterShiftX[0][nMaxCellCntY - 1];
	stPosXYZ.dPosX *= STICK_FLIP_XY;

	//Edge Slot LB Y
	stPosXYZ.dPosY = CModelData::m_MaterialPara.Info.dCellLeftTopY[0][nMaxCellCntY - 1];
	stPosXYZ.dPosY += CModelData::m_MaterialPara.Info.dSlotCenterShiftY[0][nMaxCellCntY - 1];
	stPosXYZ.dPosY -= CModelData::m_MaterialPara.Info.dSlotTotalPitchY[0][nMaxCellCntY - 1];
	stPosXYZ.dPosY *= STICK_FLIP_XY;

	//stPosXYZ.dPosZ1 = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_InspectionReview_Pos;
	//stPosXYZ.dPosAoiZ = CManualData::m_ManualDataGantry.Info.m_dGantry_Z2_Wait_Pos;
	//stPosXYZ.dPos3dZ = CManualData::m_ManualDataGantry.Info.m_d3D_Camera_Main_Z_Wait_Pos;

	return stPosXYZ;
}
stPOS_XYZ SharedInfo::GetReview10X_EdgeAlignSlotPosXY_LT()
{
	stPOS_XYZ stPosXYZ;

	INT nMaxCellCntX = (INT)CModelData::m_MaterialPara.Info.nCellCountX;
	INT nMaxCellCntY = (INT)CModelData::m_MaterialPara.Info.nCellCountY;

	//Edge Slot LT X
	stPosXYZ.dPosX = CModelData::m_MaterialPara.Info.dCellLeftTopX[0][0];
	stPosXYZ.dPosX += CModelData::m_MaterialPara.Info.dSlotCenterShiftX[0][0];
	stPosXYZ.dPosX *= STICK_FLIP_XY;

	//Edge Slot LT Y
	stPosXYZ.dPosY = CModelData::m_MaterialPara.Info.dCellLeftTopY[0][0];
	stPosXYZ.dPosY += CModelData::m_MaterialPara.Info.dSlotCenterShiftY[0][0];
	stPosXYZ.dPosY *= STICK_FLIP_XY;

	//stPosXYZ.dPosZ1 = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_InspectionReview_Pos;
	//stPosXYZ.dPosAoiZ = CManualData::m_ManualDataGantry.Info.m_dGantry_Z2_Wait_Pos;
	//stPosXYZ.dPos3dZ = CManualData::m_ManualDataGantry.Info.m_d3D_Camera_Main_Z_Wait_Pos;

	return stPosXYZ;
}
stPOS_XYZ SharedInfo::GetReview10X_EdgeAlignSlotPosXY_RT()
{
	stPOS_XYZ stPosXYZ;

	INT nMaxCellCntX = (INT)CModelData::m_MaterialPara.Info.nCellCountX;
	INT nMaxCellCntY = (INT)CModelData::m_MaterialPara.Info.nCellCountY;

	//Edge Slot RT X
	stPosXYZ.dPosX = CModelData::m_MaterialPara.Info.dCellLeftTopX[nMaxCellCntX - 1][0];
	stPosXYZ.dPosX += CModelData::m_MaterialPara.Info.dSlotCenterShiftX[nMaxCellCntX - 1][0];
	stPosXYZ.dPosX += CModelData::m_MaterialPara.Info.dSlotTotalPitchX[nMaxCellCntX - 1][0];
	stPosXYZ.dPosX *= STICK_FLIP_XY;

	//Edge Slot RT Y
	stPosXYZ.dPosY = CModelData::m_MaterialPara.Info.dCellLeftTopY[nMaxCellCntX - 1][0];
	stPosXYZ.dPosY += CModelData::m_MaterialPara.Info.dSlotCenterShiftY[nMaxCellCntX - 1][0];
	stPosXYZ.dPosY *= STICK_FLIP_XY;

	//stPosXYZ.dPosZ1 = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_InspectionReview_Pos;
	//stPosXYZ.dPosAoiZ = CManualData::m_ManualDataGantry.Info.m_dGantry_Z2_Wait_Pos;
	//stPosXYZ.dPos3dZ = CManualData::m_ManualDataGantry.Info.m_d3D_Camera_Main_Z_Wait_Pos;

	return stPosXYZ;
}
stPOS_XYZ SharedInfo::GetReview10X_EdgeAlignSlotPosXY_RB()
{
	stPOS_XYZ stPosXYZ;

	INT nMaxCellCntX = (INT)CModelData::m_MaterialPara.Info.nCellCountX;
	INT nMaxCellCntY = (INT)CModelData::m_MaterialPara.Info.nCellCountY;

	//Edge Slot RB X
	stPosXYZ.dPosX = CModelData::m_MaterialPara.Info.dCellLeftTopX[nMaxCellCntX - 1][nMaxCellCntY - 1];
	stPosXYZ.dPosX += CModelData::m_MaterialPara.Info.dSlotCenterShiftX[nMaxCellCntX - 1][nMaxCellCntY - 1];
	stPosXYZ.dPosX += CModelData::m_MaterialPara.Info.dSlotTotalPitchX[nMaxCellCntX - 1][nMaxCellCntY - 1];
	stPosXYZ.dPosX *= STICK_FLIP_XY;

	//Edge Slot RB Y
	stPosXYZ.dPosY = CModelData::m_MaterialPara.Info.dCellLeftTopY[nMaxCellCntX - 1][nMaxCellCntY - 1];
	stPosXYZ.dPosY += CModelData::m_MaterialPara.Info.dSlotCenterShiftY[nMaxCellCntX - 1][nMaxCellCntY - 1];
	stPosXYZ.dPosY -= CModelData::m_MaterialPara.Info.dSlotTotalPitchY[nMaxCellCntX - 1][nMaxCellCntY - 1];
	stPosXYZ.dPosY *= STICK_FLIP_XY;

	//stPosXYZ.dPosZ1 = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_InspectionReview_Pos;
	//stPosXYZ.dPosAoiZ = CManualData::m_ManualDataGantry.Info.m_dGantry_Z2_Wait_Pos;
	//stPosXYZ.dPos3dZ = CManualData::m_ManualDataGantry.Info.m_d3D_Camera_Main_Z_Wait_Pos;

	return stPosXYZ;
}

//Tension
stPOS_XYZ SharedInfo::GetReview10X_EdgeTensionAlignSlotPosXY_LB()
{
	stPOS_XYZ stPosXYZ;

	INT nMaxCellCntX = (INT)CModelData::m_AtMaterialPara.Info.nCellCountX;
	INT nMaxCellCntY = (INT)CModelData::m_AtMaterialPara.Info.nCellCountY;

	//Edge Tension Slot LB X
	stPosXYZ.dPosX = CModelData::m_AtMaterialPara.Info.dCellLeftTopX[0][nMaxCellCntY - 1];
	stPosXYZ.dPosX += CModelData::m_AtMaterialPara.Info.dSlotCenterShiftX[0][nMaxCellCntY - 1];
	stPosXYZ.dPosX *= STICK_FLIP_XY;

	//Edge Tension Slot LB Y
	stPosXYZ.dPosY = CModelData::m_AtMaterialPara.Info.dCellLeftTopY[0][nMaxCellCntY - 1];
	stPosXYZ.dPosY += CModelData::m_AtMaterialPara.Info.dSlotCenterShiftY[0][nMaxCellCntY - 1];
	stPosXYZ.dPosY -= CModelData::m_AtMaterialPara.Info.dSlotTotalPitchY[0][nMaxCellCntY - 1];
	stPosXYZ.dPosY *= STICK_FLIP_XY;

	//stPosXYZ.dPosZ1 = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_InspectionReview_Pos;
	//stPosXYZ.dPosAoiZ = CManualData::m_ManualDataGantry.Info.m_dGantry_Z2_Wait_Pos;
	//stPosXYZ.dPos3dZ = CManualData::m_ManualDataGantry.Info.m_d3D_Camera_Main_Z_Wait_Pos;

	return stPosXYZ;
}
stPOS_XYZ SharedInfo::GetReview10X_EdgeTensionAlignSlotPosXY_LT()
{
	stPOS_XYZ stPosXYZ;

	INT nMaxCellCntX = (INT)CModelData::m_AtMaterialPara.Info.nCellCountX;
	INT nMaxCellCntY = (INT)CModelData::m_AtMaterialPara.Info.nCellCountY;

	//Edge Tension Slot LT X
	stPosXYZ.dPosX = CModelData::m_AtMaterialPara.Info.dCellLeftTopX[0][0];
	stPosXYZ.dPosX += CModelData::m_AtMaterialPara.Info.dSlotCenterShiftX[0][0];
	stPosXYZ.dPosX *= STICK_FLIP_XY;

	//Edge Tension Slot LT Y
	stPosXYZ.dPosY = CModelData::m_AtMaterialPara.Info.dCellLeftTopY[0][0];
	stPosXYZ.dPosY += CModelData::m_AtMaterialPara.Info.dSlotCenterShiftY[0][0];
	stPosXYZ.dPosY *= STICK_FLIP_XY;

	//stPosXYZ.dPosZ1 = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_InspectionReview_Pos;
	//stPosXYZ.dPosAoiZ = CManualData::m_ManualDataGantry.Info.m_dGantry_Z2_Wait_Pos;
	//stPosXYZ.dPos3dZ = CManualData::m_ManualDataGantry.Info.m_d3D_Camera_Main_Z_Wait_Pos;

	return stPosXYZ;
}
stPOS_XYZ SharedInfo::GetReview10X_EdgeTensionAlignSlotPosXY_RT()
{
	stPOS_XYZ stPosXYZ;

	INT nMaxCellCntX = (INT)CModelData::m_AtMaterialPara.Info.nCellCountX;
	INT nMaxCellCntY = (INT)CModelData::m_AtMaterialPara.Info.nCellCountY;

	//Edge Tension Slot RT X
	stPosXYZ.dPosX = CModelData::m_AtMaterialPara.Info.dCellLeftTopX[nMaxCellCntX - 1][0];
	stPosXYZ.dPosX += CModelData::m_AtMaterialPara.Info.dSlotCenterShiftX[nMaxCellCntX - 1][0];
	stPosXYZ.dPosX += CModelData::m_AtMaterialPara.Info.dSlotTotalPitchX[nMaxCellCntX - 1][0];
	stPosXYZ.dPosX *= STICK_FLIP_XY;

	//Edge Tension Slot RT Y
	stPosXYZ.dPosY = CModelData::m_AtMaterialPara.Info.dCellLeftTopY[nMaxCellCntX - 1][0];
	stPosXYZ.dPosY += CModelData::m_AtMaterialPara.Info.dSlotCenterShiftY[nMaxCellCntX - 1][0];
	stPosXYZ.dPosY *= STICK_FLIP_XY;

	//stPosXYZ.dPosZ1 = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_InspectionReview_Pos;
	//stPosXYZ.dPosAoiZ = CManualData::m_ManualDataGantry.Info.m_dGantry_Z2_Wait_Pos;
	//stPosXYZ.dPos3dZ = CManualData::m_ManualDataGantry.Info.m_d3D_Camera_Main_Z_Wait_Pos;

	return stPosXYZ;
}
stPOS_XYZ SharedInfo::GetReview10X_EdgeTensionAlignSlotPosXY_RB()
{
	stPOS_XYZ stPosXYZ;

	INT nMaxCellCntX = (INT)CModelData::m_AtMaterialPara.Info.nCellCountX;
	INT nMaxCellCntY = (INT)CModelData::m_AtMaterialPara.Info.nCellCountY;

	//Edge Tension Slot RB X
	stPosXYZ.dPosX = CModelData::m_AtMaterialPara.Info.dCellLeftTopX[nMaxCellCntX - 1][nMaxCellCntY - 1];
	stPosXYZ.dPosX += CModelData::m_AtMaterialPara.Info.dSlotCenterShiftX[nMaxCellCntX - 1][nMaxCellCntY - 1];
	stPosXYZ.dPosX += CModelData::m_AtMaterialPara.Info.dSlotTotalPitchX[nMaxCellCntX - 1][nMaxCellCntY - 1];
	stPosXYZ.dPosX *= STICK_FLIP_XY;

	//Edge Tension Slot RB Y
	stPosXYZ.dPosY = CModelData::m_AtMaterialPara.Info.dCellLeftTopY[nMaxCellCntX - 1][nMaxCellCntY - 1];
	stPosXYZ.dPosY += CModelData::m_AtMaterialPara.Info.dSlotCenterShiftY[nMaxCellCntX - 1][nMaxCellCntY - 1];
	stPosXYZ.dPosY -= CModelData::m_AtMaterialPara.Info.dSlotTotalPitchY[nMaxCellCntX - 1][nMaxCellCntY - 1];
	stPosXYZ.dPosY *= STICK_FLIP_XY;

	//stPosXYZ.dPosZ1 = CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_InspectionReview_Pos;
	//stPosXYZ.dPosAoiZ = CManualData::m_ManualDataGantry.Info.m_dGantry_Z2_Wait_Pos;
	//stPosXYZ.dPos3dZ = CManualData::m_ManualDataGantry.Info.m_d3D_Camera_Main_Z_Wait_Pos;

	return stPosXYZ;
}
#pragma endregion //Edge Align Pos. KJT20210214

void SharedInfo::LightAllOff()
{	
	//Sleep(10);
	//g_CommLoader_Light.SetLight_Left_Loader(0, 0);//Box Left
	//Sleep(10);
	//g_CommLoader_Light.SetLight_Right_Loader(0, 0);//Box Right
	//Sleep(10);

	//g_CommZomm_Coaxial.Zoom_Light_On(FALSE);//PreAlign & Zoom
	//Sleep(10);
	//g_CommZomm_Ring.Zoom_Light_On(FALSE);//PreAlign & Zoom
	//g_CommLoader_Light.SetLight_PreAlign(0, 0); //KJT 20210728
	//Sleep(10);

	//g_CommReview_Light.SetLight_Review(0, 0);//Review10X
	//Sleep(10);

	//g_CommBack_Light.BackLightOff();//Backlight
	//Sleep(10);

	//g_CommLight_8ch.SetLight_BoxAlignL(0, 0); //KJT 20210311
	//g_CommLight_8ch.SetLight_BoxAlignR(0, 0); //KJT 20210311

	//g_CommLight_8ch.SetLight_Review_Coaxial(0);
	//g_CommLight_12ch.SetLight_Review_Ring(0);
	//g_CommLight_8ch.SetLight_PreAlign(0, 0);

	//g_CommMLCLedLight.AoiLightOff();
	//g_CommMLCLedLight.BackLightOff();
}

void SharedInfo::BackLightOn(int nVal)
{
	//int nBackLightVal[BACKLIGHT_CH_COUNT] = { BACKLIGHT_OFF_VALUE, };

	//for (int i = 0; i < BACKLIGHT_CH_COUNT; i++)
	//{
	//	nBackLightVal[i] = nVal;
	//}

	//g_CommBack_Light.BackLightOn(nBackLightVal);
}

void SharedInfo::BackLightOff()
{
	//sunghaklee
	//int nBackLightVal[BACKLIGHT_CH_COUNT] = { 0, };
	//int nBackLightVal[BACKLIGHT_CH_COUNT] = { BACKLIGHT_OFF_VALUE, };	

	//g_CommBack_Light.BackLightOn(nBackLightVal);
}
void SharedInfo::GetSlotQtyXY(int *nQtyX, int *nQtyY)
{
	switch (CModelData::m_PpaPara.Info.nSlotQuantityXY)
	{
	case eQuantity_1X1:
		*nQtyX = 1;
		*nQtyY = 1;
		break;
	case eQuantity_3X3:
		*nQtyX = 3;
		*nQtyY = 3;
		break;
	case eQuantity_5X5:
		*nQtyX = 5;
		*nQtyY = 5;
		break;
	default:
		*nQtyX = 1;
		*nQtyY = 1;
		break;
	}
}
BOOL SharedInfo::LoadGlassMappingData()//KJT 20210510
{
	CString Str = _T("");

#ifndef SIM_MOD
	for (int i = 0; i < eMAPPING_ID_MAX; i++)
	{
		Devs::m_MappingProc.InitializeGlassMapping(i);
		if (Devs::m_MappingProc.LoadGlassMappingFile(i) == FALSE)
		{
			Str.Format(_T("LoadGlassMappingFile_%d Fail !!"), i);
			Alarm_Msg(Str);
			SetAlarm(Str, 100);
			return FALSE;
		}
	}
#endif

	return TRUE;
}
BOOL SharedInfo::LoadSwMappingData()//KJT 20210510
{
	CString Str = _T("");

#ifndef SIM_MOD
	for (int i = 0; i < eMAPPING_ID_MAX; i++)
	{
		Devs::m_MappingProc.InitializeSWMapping(i);
		if (Devs::m_MappingProc.LoadSWMappingFile(i) == FALSE)
		{
			Str.Format(_T("LoadSWMappingFile_%d Fail !!"), i);
			Alarm_Msg(Str);
			SetAlarm(Str, 101);
			return FALSE;
		}
	}
#endif

	return TRUE;
}
//BOOL SharedInfo::GetMappingPos(BOOL bApplySwMappingData, double *pdTargetPosX, double *pdTargetPosY) //KJT 20210312
//{
//	double dPosX = 0.0, dPosY = 0.0;
//	double dTargetPosX = 0.0, dTargetPosY = 0.0;
//	CString Str = _T("");
//
//	dPosX = *pdTargetPosX;
//	dPosY = *pdTargetPosY;
//
//	dTargetPosX = *pdTargetPosX;
//	dTargetPosY = *pdTargetPosY;
//
//#ifndef SIM_MODE //KJT 20210312
//	if (bApplySwMappingData)
//	{
//		if (CModelData::m_InspectionPara.Info.nAlignDataUseMode == eALIGN_DATA_USE_SW_ALIGN)
//		{
//			Devs::m_MappingProc.GetSWMapping_CalibPosXY(eMAPPING_ID_10X, &dTargetPosX, &dTargetPosY);
//			Str.Format(_T("SWMapping Data X:%10.5f, Y:%10.5f => X:%10.5f, Y:%10.5f"), dPosX, dPosY, dTargetPosX, dTargetPosY);
//			Total_Msg(Str);
//		}
//		else if (CModelData::m_InspectionPara.Info.nAlignDataUseMode == eALIGN_DATA_USE_XYT_ALIGN)
//		{
//			Devs::m_MappingProc.GetXYTAlign_CalibPosXY(eMAPPING_ID_10X, &dTargetPosX, &dTargetPosY);
//			Str.Format(_T("XYTMapping Data X:%10.5f, Y:%10.5f => X:%10.5f, Y:%10.5f"), dPosX, dPosY, dTargetPosX, dTargetPosY);
//			Total_Msg(Str);
//		}
//	}
//
//	dPosX = dTargetPosX;
//	dPosY = dTargetPosY;
//	if (CModelData::m_InspectionPara.Info.bMappingDataUse)
//	{
//		Devs::m_MappingProc.GetGlassMapping_CalibPosXY(eMAPPING_ID_10X, &dTargetPosX, &dTargetPosY);
//		Str.Format(_T("Mapping Data X:%10.5f, Y:%10.5f => X:%10.5f, Y:%10.5f"), dPosX, dPosY, dTargetPosX, dTargetPosY);
//		Total_Msg(Str);
//	}
//#endif
//
//	*pdTargetPosX = dTargetPosX;
//	*pdTargetPosY = dTargetPosY;
//
//	return TRUE;
//}

BOOL SharedInfo::GetMappingPos(BOOL bApplySwAlignData, BOOL bApplyGlassMappingData, double *pdTargetPosX, double *pdTargetPosY) //KJT 20210312
{
	double dPosX = 0.0, dPosY = 0.0;
	double dTargetPosX = 0.0, dTargetPosY = 0.0;
	CString Str = _T("");

	dPosX = *pdTargetPosX;
	dPosY = *pdTargetPosY;

	dTargetPosX = *pdTargetPosX;
	dTargetPosY = *pdTargetPosY;

#ifndef SIM_MODE //KJT 20210312
	if (bApplySwAlignData)
	{
		if (CModelData::m_InspectionPara.Info.nAlignDataUseMode == eALIGN_DATA_USE_SW_MAPPING_DATA)
		{
			Devs::m_MappingProc.GetSWMapping_CalibPosXY(eMAPPING_ID_10X, &dTargetPosX, &dTargetPosY);
			Str.Format(_T("SWMapping Data X:%10.5f, Y:%10.5f => X:%10.5f, Y:%10.5f"), dPosX, dPosY, dTargetPosX, dTargetPosY);
			Total_Msg(Str);
		}
		else if (CModelData::m_InspectionPara.Info.nAlignDataUseMode == eALIGN_DATA_USE_XYT_ALIGN_DATA)
		{
			Devs::m_MappingProc.GetXYTAlign_CalibPosXY(eMAPPING_ID_10X, &dTargetPosX, &dTargetPosY);
			Str.Format(_T("XYTAlign Data X:%10.5f, Y:%10.5f => X:%10.5f, Y:%10.5f"), dPosX, dPosY, dTargetPosX, dTargetPosY);
			Total_Msg(Str);
		}
	}

	dPosX = dTargetPosX;
	dPosY = dTargetPosY;
	if (bApplyGlassMappingData) //CModelData::m_InspectionPara.Info.bMappingDataUse
	{
		Devs::m_MappingProc.GetGlassMapping_CalibPosXY(eMAPPING_ID_10X, &dTargetPosX, &dTargetPosY);
		Str.Format(_T("GlassMapping Data X:%10.5f, Y:%10.5f => X:%10.5f, Y:%10.5f"), dPosX, dPosY, dTargetPosX, dTargetPosY);
		Total_Msg(Str);
	}
#endif

	*pdTargetPosX = dTargetPosX;
	*pdTargetPosY = dTargetPosY;

	return TRUE;
}

BOOL SharedInfo::DeleteDirectory(CString root, CString dir, int nStoreDays) //KJT 20210329
{
	if (dir == _T(""))
	{
		return FALSE;
	}

	CString Str;
	BOOL bRval = FALSE;
	int nRval = 0;

	CString szNextDirPath = _T("");
	CString szRoot = _T("");

	CFileFind find;

	// Directory가 존재 하는지 확인 검사
	bRval = find.FindFile(dir);
	if (bRval == FALSE)
	{
		return bRval;
	}

	while (bRval)
	{
		bRval = find.FindNextFile();
		if (find.IsDots() == TRUE)
		{
			continue;
		}

		// Directory 일 경우
		if (find.IsDirectory())
		{
			szNextDirPath.Format(_T("%s\\*.*"), find.GetFilePath());

			// Recursion function 호출
			DeleteDirectory(root, szNextDirPath, nStoreDays);
		}
		// file일 경우
		else
		{
			//파일 삭제		
			DeleteFiles(find.GetRoot(), nStoreDays, _T("*"));

			//SetFileAttributes(find.GetFilePath(), FILE_ATTRIBUTE_ARCHIVE);
			//::DeleteFile(find.GetFilePath());
		}
	}

	szRoot = find.GetRoot();

	find.Close();

	Sleep(1);

	if (szRoot != root)//삭제하지 않는다.	
	{
		HANDLE	hFind = NULL;			// File Handle
		WIN32_FIND_DATA fileinfo;		// File Information Structure	
		FILETIME localfiletime;			// 로컬파일타임(현지시각)을 저장하기 위한 변수
		SYSTEMTIME  systemtime;
		CTime CurrentTime = CTime::GetCurrentTime();
		CTimeSpan SpanTime;

		Str.Format(_T("%s*.*"), szRoot);

		hFind = FindFirstFile(Str, &fileinfo);

		FileTimeToLocalFileTime(&fileinfo.ftLastWriteTime, &localfiletime);		// 로컬파일타임으로 조정
		FileTimeToSystemTime(&localfiletime, &systemtime);						// 구조체 형식으로 변환

		CTime FileTime(systemtime.wYear, systemtime.wMonth, systemtime.wDay, 0, 0, 0);

		SpanTime = CurrentTime - FileTime;

		if (SpanTime.GetDays() >= nStoreDays)
		{
			if (hFind != INVALID_HANDLE_VALUE)
			{
				FindClose(hFind);

				SetFileAttributes(szRoot, FILE_ATTRIBUTE_ARCHIVE); //KJT 20210722
				bRval = RemoveDirectory(szRoot);
			}
			else
			{
				FindClose(hFind);
			}
		}
		else
		{
			FindClose(hFind);
		}
	}

	return bRval;
}

BOOL SharedInfo::DeleteFiles(CString dir, int nStoreDays, CString Ext) //KJT 20210329
{
	///////////////////////////////////////////////////
	HANDLE	hFind = NULL;			// File Handle
	WIN32_FIND_DATA fileinfo;		// File Information Structure	
	FILETIME localfiletime;			// 로컬파일타임(현지시각)을 저장하기 위한 변수
	SYSTEMTIME  systemtime;
	CTime CurrentTime = CTime::GetCurrentTime();
	CTimeSpan SpanTime;
	BOOL bFound = TRUE;

	CString FileName;
	CString SubFileName;

	//FileName.Format(_T("%s*.*"), dir);
	FileName.Format(_T("%s*.%s"), dir, Ext);

	SubFileName.Format(_T("%s"), dir);

	hFind = FindFirstFile(FileName, &fileinfo);

	// if the file exists and it is a directory
	//if (fileinfo.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY)
	if (INVALID_HANDLE_VALUE != hFind)
	{
		//bFound = FindNextFile(hFind, &fileinfo);
		// skip directories
		if (!(fileinfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			FileTimeToLocalFileTime(&fileinfo.ftLastWriteTime, &localfiletime);		// 로컬파일타임으로 조정
			FileTimeToSystemTime(&localfiletime, &systemtime);						// 구조체 형식으로 변환

			CTime FileTime(systemtime.wYear, systemtime.wMonth, systemtime.wDay, 0, 0, 0);

			SpanTime = CurrentTime - FileTime;

			FileName.Format(_T("%s%s"), SubFileName, fileinfo.cFileName);

			if (SpanTime.GetDays() >= nStoreDays)//m_FileStoreDay.m_nFileStore_Day3)
			{
				//if (fileinfo.)
				SetFileAttributes(FileName, FILE_ATTRIBUTE_ARCHIVE);

				::DeleteFile(FileName);
			}
		}

		do
		{
			bFound = FindNextFile(hFind, &fileinfo);

			// skip directories
			if (!(fileinfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				FileTimeToLocalFileTime(&fileinfo.ftLastWriteTime, &localfiletime);		// 로컬파일타임으로 조정
				FileTimeToSystemTime(&localfiletime, &systemtime);						// 구조체 형식으로 변환

				CTime FileTime(systemtime.wYear, systemtime.wMonth, systemtime.wDay, 0, 0, 0);

				SpanTime = CurrentTime - FileTime;

				FileName.Format(_T("%s%s"), SubFileName, fileinfo.cFileName);

				if (SpanTime.GetDays() >= nStoreDays)//m_FileStoreDay.m_nFileStore_Day3)
				{
					//if (fileinfo.)
					SetFileAttributes(FileName, FILE_ATTRIBUTE_ARCHIVE);

					::DeleteFile(FileName);
				}
			}

		} while (bFound);
	}

	FindClose(hFind);

	return bFound;
}

BOOL SharedInfo::CalTactTime(CString strName, CTime timeStart) //KJT 20210329 Add
{
	CString Str = _T("");
	DWORD dStart, dCur;
	int nHour, nMin, nSec;

	CTime timeCur = CTime::GetCurrentTime();
	dStart = timeStart.GetHour() * 3600 + timeStart.GetMinute() * 60 + timeStart.GetSecond();
	dCur = timeCur.GetHour() * 3600 + timeCur.GetMinute() * 60 + timeCur.GetSecond();

	dCur -= dStart;

	nHour = (int)((float)dCur / 3600);
	nMin = (int)(((float)dCur - nHour * 3600) / 60);
	nSec = (int)((float)dCur - nHour * 3600 - nMin * 60);

	Str.Format(_T("TackTime %s %dh %dm %dsec"), strName, nHour, nMin, nSec);
	Process_Msg(Str);

	return TRUE;
}

CString SharedInfo::CalTactTime(CTime timeStart) //KJT 20210425
{
	CString Str = _T("");
	DWORD dStart, dCur;
	int nHour, nMin, nSec;

	CTime timeCur = CTime::GetCurrentTime();
	dStart = timeStart.GetHour() * 3600 + timeStart.GetMinute() * 60 + timeStart.GetSecond();
	dCur = timeCur.GetHour() * 3600 + timeCur.GetMinute() * 60 + timeCur.GetSecond();

	dCur -= dStart;

	nHour = (int)((float)dCur / 3600);
	nMin = (int)(((float)dCur - nHour * 3600) / 60);
	nSec = (int)((float)dCur - nHour * 3600 - nMin * 60);

	Str.Format(_T("%02d:%02d:%02d"), nHour, nMin, nSec);

	return Str;
}

void SharedInfo::SaveImage(int nStorageIndex)
{
	SYSTEMTIME SysTime;
	GetLocalTime(&SysTime);

	TCHAR tchPathName[256] = { NULL };
	TCHAR tchFileName[256] = { NULL };
	TCHAR tchSaveFileName[256] = { NULL };

	if (!CSystemData::m_Option.Info.m_bImageAutoSave)
		return;

	wsprintf(tchPathName, _T("%s%04d\\%02d\\%02d\\%s"), SharedInfo::STR_SAVE_IMAGE_DIR_PATH, SysTime.wYear, SysTime.wMonth, SysTime.wDay, StoragePath[nStorageIndex]);

	CLogDefine::MakeDirectory(tchPathName);

	wsprintf(tchFileName, _T("%02d%02d%02d%03d_%s_%d_%d.jpg"), SysTime.wHour, SysTime.wMinute, SysTime.wSecond, SysTime.wMilliseconds, SharedInfo::Active.strFrameName,
		(int)UmacCmdPos[REMOTE_AXIS_UMAC_GANTRY_X], (int)UmacCmdPos[REMOTE_AXIS_UMAC_GANTRY_Y1]); //Temp

	wsprintf(tchSaveFileName, _T("%s\\%s"), tchPathName, tchFileName);

#ifndef SIM_MODE

	Devs::m_Camera10X->ImageSaveFilePath(tchSaveFileName);

#endif
}

BOOL SharedInfo::GetDiffXYT(double dCmdPointXY[4][2], double dActPointXY[4][2], double *dDiffX, double *dDiffY, double *dDiffT) //KJT 20210630
{
	double dX = 0.0, dY = 0.0, dT = 0.0;
	double dResultX = 0.0, dResultY = 0.0, dResultT = 0.0;

	//LT-LB
	Devs::m_MappingProc.Make2PointAlignData(0, 0, dCmdPointXY[0], dCmdPointXY[1], dActPointXY[0], dActPointXY[1], &dX, &dY, &dT);
	dResultX += dX;
	dResultY += dY;
	dResultT += dT;

	//RT-LT
	Devs::m_MappingProc.Make2PointAlignData(0, 1, dCmdPointXY[1], dCmdPointXY[2], dActPointXY[1], dActPointXY[2], &dX, &dY, &dT);
	dResultX += dX;
	dResultY += dY;
	dResultT += dT;

	//RT-RB
	Devs::m_MappingProc.Make2PointAlignData(0, 2, dCmdPointXY[3], dCmdPointXY[2], dActPointXY[3], dActPointXY[2], &dX, &dY, &dT);
	dResultX += dX;
	dResultY += dY;
	dResultT += dT;

	//RB-LB
	Devs::m_MappingProc.Make2PointAlignData(0, 3, dCmdPointXY[0], dCmdPointXY[3], dActPointXY[0], dActPointXY[3], &dX, &dY, &dT);
	dResultX += dX;
	dResultY += dY;
	dResultT += dT;

	dResultX /= 4.0;
	dResultY /= 4.0;
	dResultT /= 4.0;

	*dDiffX = dResultX * (-1);
	*dDiffY = dResultY * (-1);
	*dDiffT = dResultT * (-1) * TO_DEGREE;

	Process_Msg(_T("[GetDiffXYT] X:%.5f, Y:%.5f, T:%.5f"), dResultX, dResultY, dResultT);

	return TRUE;
}

CTime SharedInfo::m_timeTotalTact; //KJT 20210425
CTime SharedInfo::m_timeUnitTact;
