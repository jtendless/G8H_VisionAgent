#pragma once

#include "VisionAgent.h"
#include "VisionAgentDlg.h"
#include "VisionAgentDefine.h"
#include "Common/CommonDefine.h"
#include "Motion/MotionAgentDefine.h"
#include "FileIni/FileIni.h"
#include "Vision/MappingProc.h"

#define MAX_RECIPE_COUNT		1000

class CVisionAgentDlg;

typedef struct _ACTIVE_STATE {

	int	MachineMode;
	int MachineWorkSpeed;
	BOOL WeldingLaserUse;

	int CassetteIndexY;
	int CassetteIndexZ;
	int ActiveBankIndex;

	INT nActiveRecipeNum;

	TCHAR PanelId[256];
	TCHAR UserId[256];

	TCHAR strFrameName[100];
	int nFrameDone[50];

	int ProcessStartFlow; //enum_AutoRunFlowName
	int ProcessStep;
	int ProcessEndFlow; //enum_AutoRunFlowName

	int ProcessGlass;

	int nFinalGrade;
	int nFinalJudge;

} ACTIVE_STATE, *PACTIVE_STATE;

typedef struct _CURRENT_STATE {
	bool bErrorFlag;
	bool bAutoRunFlag;
	bool bSemiAutoRunFlag;
	bool bRecipeChangeDone;
	bool bAutoStopDoneCheck;
	bool bDoorState;
	bool bEmsState;

	int nMainStep;
	int nSubStep;
	
} CURRENT_STATE, *PCURRENT_STATE;

typedef struct _RESULT_STATE {
	INT nCnt;
	double dGap_LT_X[FILM_MAX_NUM];
	double dGap_LT_Y[FILM_MAX_NUM];
	double dGap_LB_X[FILM_MAX_NUM];
	double dGap_LB_Y[FILM_MAX_NUM];
	double dGap_RT_X[FILM_MAX_NUM];
	double dGap_RT_Y[FILM_MAX_NUM];
	double dGap_RB_X[FILM_MAX_NUM];
	double dGap_RB_Y[FILM_MAX_NUM];

	double dOffsetX[FILM_MAX_NUM];
	double dOffsetY[FILM_MAX_NUM];
	double dOffsetT[FILM_MAX_NUM];

	BOOL bResult[FILM_MAX_NUM];
} RESULT_STATE, *PRESULT_STATE;

typedef struct _ALIGN_CENTER_DIFF_INFO {
	double dDiff_BoxAlignX;
	double dDiff_PreAlignAlignX;
	double dDiff_Main2PAlignX;
	double dDiff_Tegkey2PAlignX; //KJT 20210225
}ALIGN_CENTER_DIFF_INFO, *PALIGN_CENTER_DIFF_INFO;

typedef struct _DIRECT_AXIS_HOME_INFO
{
	double dCmdPos[DIRECT_AXIS_MAX];
	BOOL	bHomeStatus[DIRECT_AXIS_MAX];

}DIRECT_AXIS_HOME_INFO, **PDIRECT_AXIS_HOME_INFO;

class DIRECT_AXIS_HOME
{
public:
	DIRECT_AXIS_HOME_INFO Info;
	BOOL Save();
	BOOL Load();
};

class SharedInfo
{
public:
	SharedInfo();
	~SharedInfo();

	static void Initialize(void);
	static void Finalize(void);

public:
	//! File path constants 
	//!
	static LPCTSTR STR_MODEL_PARA_FILE_DIR;
	static LPCTSTR STR_INSPECT_PARA_FILE_DIR;

	static LPCTSTR STR_ALARM_LIST_FILE_PATH;

	static LPCTSTR STR_SYSTEM_FILE_PATH;
	static LPCTSTR STR_VELOCITY_PARA_FILE_PATH;

	static CString VisionAgentPath;			//!< the location of executable.

#pragma region //Lable
	static LPCTSTR STR_DATA_LABEL_AXIS;
	static LPCTSTR STR_DATA_LABEL_DINPUT;
	static LPCTSTR STR_DATA_LABEL_DOUTPUT;
	static LPCTSTR STR_DATA_LABEL_AINPUT;
	static LPCTSTR STR_DATA_LABEL_AOUTPUT;
#pragma endregion
	
	static CString STR_SAVE_IMAGE_DIR_PATH;
	static CString STR_AOI_DEFECT_INFO_FILE_PATH;
	static CString STR_AOI_DEFECT_REVIEW_PATH;
	static CString STR_3D_INSPECTION_IMAGE_PATH;

	static ACTIVE_STATE		Active;
	static void ActiveInfoSave();
	static void ActiveInfoLoad();

	static BOOL SaveRecipeTable();
	static BOOL LoadRecipeTable();

	static CURRENT_STATE MachineState;
	//static MACHINE_RECIPE_TABLE m_MachineCameraRecipeTable;
	static CStringArray m_strModelNames;

	static BOOL	bMachineStopFlag;
	static int  nAutoFocusCameraMode;

	//Tempurature
	static int TempurInterval;
	//Laser Value
	static double m_dLaserDispFVal;
	static double m_dLaserDispBVal;

	static ALARM_LIST AlarmList[100];
	static int	AlarmCount;

	//검사 결과.
	static RESULT_STATE Result;
	static void ResultInfoSave();
	static void ResultInfoLoad();

	static BOOL GetProcessTime(CTime tStart, int *nHour, int *nMin, int *nSec);

#pragma region //Align Result Center Diff Info
	static ALIGN_CENTER_DIFF_INFO AlignCenterDiffInfo;
	static void AlignCenterDiffInfoSave();
	static void AlignCenterDiffInfoLoad();
#pragma endregion

	static DIRECT_AXIS_HOME DirectAixsHome;
	//Flow State  저장 관련 - parkcm
	static int nCurFlowID;
	static int nCurFlowStep;
	static enum_Flow nPrevFlowID; //KJT 20210325

	/////////////////////////////////////////////////////////////////////////////////////////////

	static int FindCurrentRecipeNumber(CString strRecipeName);
	static int FindRecipeNumber(WORD wRecipeID);
	static CString FindRecipeName(INT nReceipeNumber);
	static BOOL RecipeCheck();
	static BOOL FindRecipeUse(INT nNumber);
	static BOOL GetIsAlignStick(INT nReceipeNumber);
	static CString GetExeFilePath();
	static int FindRecipeID(WORD wRecipeID);
	static void MachineStatusChange(MACHINE_STATUS_ENUM MachineStatus);
	
	//static CString		GetExeFolder(CString strFullDir) { return strFullDir.Left(strFullDir.ReverseFind('\\') + 1); }
	static CString		GetModelDataFolder() { return GetExeFilePath() + _T("\\Data\\Model"); }
	static CString		GetSystemDataFolder() { return GetExeFilePath() + _T("\\Data\\System"); }

	static CString		GetImageFolder() { return GetExeFilePath() + _T("\\Data\\Image"); }
	

	
	static CString	GetBeamAxisDataFolder();
	static CString GetLcmDataFolder();
	static CString GetLclDataFolder();
	static CString GetBlackLcDataFolder();
	static CString GetSamplePolDataFolder();
	static CString GetBluSettingDataFolder();

	static BOOL SetAlarm(LPCTSTR Msg, UINT nErrCode = 0);
	static BOOL SetAutoAlarm();
	static BOOL GetFlowAlarm();
	static BOOL GetAlarm();
	static BOOL ResetAlarm();
	static BOOL SetAxisAlarm(enum_Axis eAxis, enum_ErrorType eErrorType); //KJT 20210221

	
	static BOOL SaveNewModelData(LPCTSTR strDirectory);
	static void FindModelNames();
	static BOOL NewDirectoryFile(LPCTSTR RootDir);
	static BOOL InitModelData();
	static BOOL LoadModelData(CString strModelName);
	static BOOL DeleteDirectoryFile(LPCTSTR RootDir);
	static BOOL RenameDirectoryFile(LPCTSTR NewDirName, CString strCurrentName);
	static void AddMachineRecipeTable(WORD wRecipID, CString strNewDirName);
	static void ResetModel();

	//Data Load & Save----------------------------------------
	//Model
	static BOOL SaveModelData();
	static BOOL LoadModelData();
	//Manual
	static BOOL SaveManualData();
	static BOOL LoadManualData();
	//Machine
	static BOOL SaveMachineData();
	static BOOL LoadMachineData();
	//System
	static BOOL SaveSystemData();
	static BOOL LoadSystemData();

	static void RemoveMachineRecipeTable(WORD wRecipID);

	static CString LoadFileData(CStdioFile* csfInFile, CString strSrcData, CString strCompData);

	//Axis Infomation-----------------------------
	static BOOL	GetActualAxisNoByEnumAxis(enum_Axis eAxis, int* pAxisType, int* nRemoteAxis);
	static enum_Axis GetUmacAxisNoByActualAxis(enum_REMOTE_AXIS_UMAC eUAxis);
	static enum_Axis GetAjinAxisNoByActualAxis(enum_REMOTE_AXIS eAAxis);
	static enum_Axis GetVisionAxisNoByDirectAxis(enum_DIRECT_AXIS eAxis); //KJT 20200812

	static enum_Axis	m_eAxisJog;
	static INT			m_nJogDir;
	static int			m_eAxisJogInterlock;
	static INT			m_nJogInterlockDir;

	//Stretch
	static double dStretchCmdPos[MAX_STRETCH_AXIS_SIZE];//Left, Right
	static double dStretchCmdVel[MAX_STRETCH_AXIS_SIZE];//Left, Right
	static double dStretchValue[MAX_STRETCH_AXIS_SIZE];//Left, Right
	static double dStretchTargetValue[MAX_STRETCH_AXIS_SIZE];//Left, Right
	static int nStretchStatus[MAX_STRETCH_AXIS_SIZE];

	//clamp
	static double m_nClampTorquedMonitorValue[MAX_STRETCH_AXIS_SIZE];
	static double dSF_LoadcellForce[MAX_SF_NUM];

	static double dVisionoffsetX[2];
	static double AlignCamMarkPixelSize[2];
	static double AlignCamMarkPos[2];
	static int AlignCamMarkCD[2];
	static double AlignCamScore;
	static BOOL	bResult;

	static BOOL bAlignVisionReceiveFlag;

	////////Mapping
	//MAPPING_TABLE SharedInfo::m_sMappingTable[MAX_GLASS_MAPPING_COUNT];
	//int			SharedInfo::m_nMappingTableCnt;

	static BOOL bAlignVisionSetLightFlag;
	static BOOL bAlignVisionLightOnFlag;

	//Uvw
	static double dUVWTargetPos[2][3]; //KJT 20200912

#if 0
	//UMAC Axis
	static int		Umac_Axis_Home_Status[REMOTE_AXIS_UMAC_MAX];
	static int		Umac_Axis_Home_Signal[REMOTE_AXIS_UMAC_MAX];
	static int		Umac_Axis_PLimit_Signal[REMOTE_AXIS_UMAC_MAX];
	static int		Umac_Axis_NLimit_Signal[REMOTE_AXIS_UMAC_MAX];
	static int		Umac_Axis_ServoOn_Status[REMOTE_AXIS_UMAC_MAX];
	static int		Umac_Axis_Alarm_Status[REMOTE_AXIS_UMAC_MAX];
	static int		Umac_Axis_Isolator_Alarm;
	static int		Umac_Axis_Status[REMOTE_AXIS_UMAC_MAX]; //0:HomeStatus, 1:ServoOnStatus, 2:AlarmStatus, 3:MotionDoneStatus
	static int		Umac_Axis_InMotion_Status[REMOTE_AXIS_UMAC_MAX];
	static double	Umac_Axis_Cmd_Pos[REMOTE_AXIS_UMAC_MAX];
	static double	Umac_Axis_Act_Pos[REMOTE_AXIS_UMAC_MAX];
	static double	Umac_Axis_Cmd_Vel[REMOTE_AXIS_UMAC_MAX];

	// Ajin Axis
	static int		Ajin_Axis_HomeStatus[REMOTE_AXIS_MAX];
	static int		Ajin_Axis_HomeSignal[REMOTE_AXIS_MAX];
	static int		Ajin_Axis_PLimitSignal[REMOTE_AXIS_MAX];
	static int		Ajin_Axis_NLimitSignal[REMOTE_AXIS_MAX];
	static int		Ajin_Axis_ServoOnStatus[REMOTE_AXIS_MAX];
	static int		Ajin_Axis_AlarmStatus[REMOTE_AXIS_MAX];
	static int		Ajin_Axis_InMotionStatus[REMOTE_AXIS_MAX];
	static int		Ajin_Axis_Status[REMOTE_AXIS_MAX]; //0:HomeStatus, 1:ServoOnStatus, 2:AlarmStatus, 3:MotionDoneStatus
	static double	Ajin_Axis_Cmd_Pos[REMOTE_AXIS_MAX];
	static double	Ajin_Axis_Act_Pos[REMOTE_AXIS_MAX];
	static double	Ajin_Axis_Cmd_Vel[REMOTE_AXIS_MAX];
#endif

	static double		m_dLaserDispVal;

	static double m_dAutoFocusStartPosZ;

	static int MotionAgentAXLOpen;
	static int MaxAxisSize;
	static int MaxDInputSize;
	static int MaxDOutputSize;
	static int MaxAInputSize;
	static int MaxAOutputSize;

	//Common
	static int SystemHomeStatus;
	static int SystemHomeSignal;
	static int SystemNLimitSignal;
	static int SystemPLimitSignal;
	static int SystemServoOnStatus;
	static int SystemAlarmStatus;
	static int SystemMotionDoneStatus;
	static int SystemStatus; //0:HomeStatus, 1:ServoOnStatus, 2:AlarmStatus, 3:MotionDoneStatus

	//Common
	static int UmacOriginIngStatus[REMOTE_AXIS_UMAC_MAX];
	static int RemoteAjinOriginIngStatus[MAX_AXIS_SIZE];
	static int DirectAjinOriginIngStatus[DIRECT_AXIS_MAX];

	//Ajin
	static int Is_Ajin_Open;
	static int AxisHomeResult[MAX_AXIS_SIZE];	
	static int AxisHomeStatus[MAX_AXIS_SIZE];
	static int AxisHomeSignal[MAX_AXIS_SIZE];
	static int AxisPLimitSignal[MAX_AXIS_SIZE];
	static int AxisNLimitSignal[MAX_AXIS_SIZE];
	static int AxisServoOnStatus[MAX_AXIS_SIZE];
	static int AxisAlarmStatus[MAX_AXIS_SIZE];
	static int AxisInMotionStatus[MAX_AXIS_SIZE];	// 0:End Move, 1:Moving
	static int AxisStatus[MAX_AXIS_SIZE];	//0:HomeStatus, 1:ServoOnStatus, 2:AlarmStatus, 3:MotionDoneStatus
	static double AxisCmdPos[MAX_AXIS_SIZE];
	static double AxisActPos[MAX_AXIS_SIZE];		//wkohÃß°¡
	static double AxisCmdVel[MAX_AXIS_SIZE];
	static double AxisTorque[MAX_AXIS_SIZE];

	//Umac
	static int Is_Umac_Open;
	static int Umac_Isolator_Alarm; //KJT 20200812
	static int UmacHomeStatus[MAX_UMAC_AXIS_SIZE];
	static int UmacHomeSignal[MAX_UMAC_AXIS_SIZE];
	static int UmacPLimitSignal[MAX_UMAC_AXIS_SIZE];
	static int UmacNLimitSignal[MAX_UMAC_AXIS_SIZE];
	static int UmacServoOnStatus[MAX_UMAC_AXIS_SIZE];
	static int UmacAlarmStatus[MAX_UMAC_AXIS_SIZE];
	static int UmacInMotionStatus[MAX_UMAC_AXIS_SIZE];
	static int UmacStatus[MAX_UMAC_AXIS_SIZE];	//0:HomeStatus, 1:ServoOnStatus, 2:AlarmStatus, 3:MotionDoneStatus
	static double UmacCmdPos[MAX_UMAC_AXIS_SIZE];
	static double UmacActPos[MAX_UMAC_AXIS_SIZE];
	static double UmacCmdVel[MAX_UMAC_AXIS_SIZE];
	static double UmacTorque[MAX_UMAC_AXIS_SIZE];

	//! VisionAgent 직접 제어 축
	static int VisionAxisHomeResult[DIRECT_AXIS_MAX];
	static int VisionAxisHomeStatus[DIRECT_AXIS_MAX];
	static int VisionAxisHomeSignal[DIRECT_AXIS_MAX];
	static int VisionAxisPLimitSignal[DIRECT_AXIS_MAX];
	static int VisionAxisNLimitSignal[DIRECT_AXIS_MAX];
	static int VisionAxisServoOnStatus[DIRECT_AXIS_MAX];
	static int VisionAxisAlarmStatus[DIRECT_AXIS_MAX];
	static int VisionAxisInMotionStatus[DIRECT_AXIS_MAX];	// 0:End Move, 1:Moving
	static int VisionAxisStatus[DIRECT_AXIS_MAX];	//0:HomeStatus, 1:ServoOnStatus, 2:AlarmStatus, 3:MotionDoneStatus
	static double VisionAxisCmdPos[DIRECT_AXIS_MAX];
	static double VisionAxisActPos[DIRECT_AXIS_MAX];
	static double VisionAxisCmdVel[DIRECT_AXIS_MAX];
	static double VisionAxisTorque[DIRECT_AXIS_MAX];

#pragma region //20201030 KJT Add
	static BOOL bRemoteAjinSystemReadyStatus;
	static BOOL bRemoteUmacSystemReadyStatus;
	static BOOL bDirectAjinSystemReadyStatus;
#pragma endregion

	//Dio
	static int DInputValue[_DIN_MAX];	//MAX_DINPUT_SIZE
	static int DOutputValue[_DOUT_MAX];	//MAX_DOUTPUT_SIZE
	static DWORD DInputDWordValue[MAX_DINPUT_DWORD_SIZE];
	static DWORD DOutputDWordValue[MAX_DOUTPUT_DWORD_SIZE];

	//Aio
	static double AInputValue[MAX_AINPUT_SIZE];
	static double AOutputValue[MAX_AOUTPUT_SIZE];

	//UVW
	static double UvwCmdPos[MAX_UVW][3];
	static double UvwCmdVel[MAX_UVW][3];
	static int UvwHomeStatus[MAX_UVW];
	static int UvwServoOnStatus[MAX_UVW];
	static int UvwAlarmStatus[MAX_UVW];
	static int UvwMotionDoneStatus[MAX_UVW];
	static int UvwStatus[MAX_UVW];	//0:HomeStatus, 1:ServoOnStatus, 2:AlarmStatus, 3:MotionDoneStatus

	//////////Mapping
	static	int m_nMaxMappingCountX;
	static	int m_nMaxMappingCountY;
	static	int	m_nMappingTableCnt;
	static MAPPING_TABLE m_sMappingTable[MAX_GLASS_MAPPING_COUNT];

	//////////Camera Cal //KJT 20210525
	static int	m_nCameraCalTableCnt;
	static CAMERA_CAL_TABLE m_CameraCalTable[MAX_CAMERA_CAL_COUNT];

	//Clamp
	static double dClampValue[eGRIPPER_ROW_MAX];//Left, Right
	static int nClampStatus[eGRIPPER_ROW_MAX];//Left, Right
	static int nClampAllUnClampStatus;
	static int nClampAlarmStatus;

	static bool		GetInMotion(enum_Axis eAxis);
	static double	GetCmdPos(enum_Axis eAxis);
	static double	SetCmdPos(enum_Axis eAxis, double dPos);
	static double	GetActPos(enum_Axis eAxis);
	static double	SetActPos(enum_Axis eAxis, double dPos);
	static double	GetCmdVel(enum_Axis eAxis);
	static double	SetCmdVel(enum_Axis eAxis, double dVel);

	static int		GetHomeResult(enum_Axis eAxis);
	static int		GetHomeStatus(enum_Axis eAxis);
	static int		GetHomeSignal(enum_Axis eAxis);
	static int		GetPLimitSignal(enum_Axis eAxis);
	static int		GetNLimitSignal(enum_Axis eAxis);
	static int		GetServoOnStatus(enum_Axis eAxis);
	static int		GetAlarmStatus(enum_Axis nAxis);
	//DI	
	static	BOOL	Is_Dig_Input(int nIndex);
	//DO	
	static	BOOL	Set_Dig_Output(int nIndex, bool bOnOff);
	static	BOOL	Is_Dig_Output(int nIndex);
	//AI	
	static	double	Get_AI_Data(int nIndex);

	//IO Label Name
	static CString m_DInputName[MAX_DINPUT_SIZE];
	static CString m_DOutputName[MAX_DOUTPUT_SIZE];
	static CString m_AInputName[MAX_AINPUT_SIZE];
	static CString m_AOutputName[MAX_AOUTPUT_SIZE];

	static BOOL GetActualIoNumByEnumDo(enum_Do eIoNum, int* pAxisNo);
	static BOOL GetActualIoNumByEnumAo(enum_Ao eIoNum, int* pAxisNo);

	static BOOL GetActualIoNumByEnumDi(enum_Di eIoNum, int* pAxisNo);
	static BOOL GetActualIoNumByEnumAi(enum_Ai eIoNum, int* pAxisNo);

	static BOOL SaveAlarmList();
	static BOOL LoadAlarmList();

	static BOOL GetAutoSpeed(enum_Axis eAxis, double *pdVel, double *pdAccel, double *pdDecel);
	static BOOL GetManualSpeed(enum_Axis eAxis, enum_AXIS_SPEED eSpeedType, double *pdVel, double *pdAccel, double *pdDecel);
	static CString GetAxisName(enum_Axis eAxis);

#pragma region //CIM
	static WORD m_AlarmCount;
	static WORD m_AlarmMaxPos;
	static WORD m_AlarmCmdPos;
	static INT	m_nCmd;

	static WORD OperatorID[10];
	static int MachinMode;
	//Other Alarm
	static int m_nOtherAlarm[10];
	static int MachineAutoMode; //KJT 202120324

	static BOOL bBuzzerNotUse; //KJT 20210225

	static void DfsInfoSave();
	static void DfsInfoRead();
	static TCHAR* GetDfsFolderDir(CString strFileName);
	static TCHAR * GetDfsFileName(CString strFileName);
#pragma endregion

	static BOOL CheckAllAxisServoOn(CString *strAxisName);
	static BOOL CheckAllAxisHomeStatus(CString *strAxisName);

	static BOOL CheckSafetyPos(enum_Axis eAxis, double dTargetPos, CString *strDiscription, int *pnSafetyPosErrorBy);
	//sunghaklee
	static BOOL CheckSystemSafetyPos(enum_Axis eAxis, double dTargetPos, CString *strDiscription);// , int *pnSafetyPosErrorBy);

	static CString AllPPAPath;
	static PPA_POS *m_pPpaResult;

	static void CStringToPChar(CString str, char pch[256]);

	static void UpdateSwAlignData(double dAlignPointValue[2][4], double dAlignResultValue[2][4]);

	static enum_Camera_ViewMode eCamViewMode;

	static BOOL m_bAOIReqMoveProcessing;

#pragma region //Repeat
	static	REPEAT_TABLE	m_sRepeatTable[MAX_REPEAT_COUNT];
	static int m_nRepeatTableCnt;
	static int m_nStopRepeatCnt;
	static int m_nMoveRepeatCnt;
	static int m_nRepeatCurPointIndex;
	static int m_nMoveRepeatTarget;
	static int m_nIsGlassMode;

#pragma endregion

	static FLATNESS_TABLE m_sFlatnessTable[MAX_FLATNESS_COUNT];
	static int				m_nFlatnessLightCoaxial;
	static int				m_nFlatnessLightRing;
	static int				m_nFlatnessBackLight;
	static int				m_nFlatnessTool;
	static int				m_nFlatnessTableCnt;	

#pragma region //Measurement Dlg Display
	static BOOL bPreAlignGrabDone;
	static BOOL bMainAlignGrabDone;
	static BOOL bTegkey2PAlignGrabDone;
	static BOOL bMainEdgeAlignGrabDone;

	static int nVerticalAlignCurCount;
	static int nVerticalSwAlignCurCount; //KJT 20210321
	static int nRightAngleCurCount;
	static int nPreAlignCurCount;
	static int nMain2PAlignCurCount;
	static int nTegkey2PAlignCurCount; //KJT 20210227
	static int nMainEdge4PAlignCurCount;
	static int nSwAlignCurCount; //KJT 20210304
	static int nGlass4PAlignCurCount; //KJT 20210314	

	static double dPreAlignVisionResultValue[2][2];
	static double dMain2PAlignVisionResultValue[2][2];
	static double dTegkey2PAlignVisionResultValue[2][2]; //KJT 20210227
	static double dSwAlignVisionResultValue[2][4]; //KJT 20210307
	static double dMainEdge4PAlignVisionResultValue[2][4];	
#pragma endregion

	static double dMain2PAlignResultShiftX[2]; //KJT 20210421

	static BOOL bTemperSend; //KJT 2021038

	static int m_nPrevMachineState; //KJT 20210321
	static int m_nCurMachineState; //KJT 20210321

#pragma region //Edge Align Pos. //KJT 20210302
	static stPOS_XYZ GetReview10X_EdgeAlignCellPosXY_LB();
	static stPOS_XYZ GetReview10X_EdgeAlignCellPosXY_LT();
	static stPOS_XYZ GetReview10X_EdgeAlignCellPosXY_RT();
	static stPOS_XYZ GetReview10X_EdgeAlignCellPosXY_RB();
	static stPOS_XYZ GetReview10X_EdgeTensionAlignCellPosXY_LB();
	static stPOS_XYZ GetReview10X_EdgeTensionAlignCellPosXY_LT();
	static stPOS_XYZ GetReview10X_EdgeTensionAlignCellPosXY_RT();
	static stPOS_XYZ GetReview10X_EdgeTensionAlignCellPosXY_RB();

	static stPOS_XYZ GetReview10X_EdgeAlignSlotPosXY_LB();
	static stPOS_XYZ GetReview10X_EdgeAlignSlotPosXY_LT();
	static stPOS_XYZ GetReview10X_EdgeAlignSlotPosXY_RT();
	static stPOS_XYZ GetReview10X_EdgeAlignSlotPosXY_RB();
	static stPOS_XYZ GetReview10X_EdgeTensionAlignSlotPosXY_LB();
	static stPOS_XYZ GetReview10X_EdgeTensionAlignSlotPosXY_LT();
	static stPOS_XYZ GetReview10X_EdgeTensionAlignSlotPosXY_RT();
	static stPOS_XYZ GetReview10X_EdgeTensionAlignSlotPosXY_RB();
#pragma endregion

	static void LightAllOff();
	static void BackLightOn(int nVal);
	static void BackLightOff();

	static void GetSlotQtyXY(int *nQtyX, int *nQtyY); //KJT 20210527

	static BOOL LoadGlassMappingData(); //kjt 20210510
	static BOOL LoadSwMappingData(); //kjt 20210510
	//static BOOL GetMappingPos(BOOL bApplySwMappingData, double *pdTargetPosX, double *pdTargetPosY); //KJT 20210312
	static BOOL GetMappingPos(BOOL bApplySwAlignData, BOOL bApplyGlassMappingData, double *pdTargetPosX, double *pdTargetPosY); //KJT 20210425

	//KJT 20210329
	static BOOL DeleteDirectory(CString root, CString dir, int nStoreDays);
	static BOOL DeleteFiles(CString dir, int nStoreDays, CString Ext);

	static BOOL CalTactTime(CString strName, CTime timeStart); //KJT 20210329
	static CString CalTactTime(CTime timeStart); //KJT 20210425
	static CTime m_timeTotalTact; //KJT 20210425
	static CTime m_timeUnitTact; //KJT 20210425

	static void SaveImage(int nStorageIndex);//jini 20210720

	static BOOL GetDiffXYT(double dCmdPointXY[4][2], double dActPointXY[4][2], double *dDiffX, double *dDiffY, double *dDiffT); //KJT 20210630
};

