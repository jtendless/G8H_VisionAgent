#pragma once

#pragma region //Gantry
typedef struct _CManualDataGantryInfo
{
	//Gantry X	
	double	m_dGantry_X_Wait_Pos;

	//Gantry Y	
	double	m_dGantry_Y_Wait_Pos;
	double	m_dGantry_Y_Stick_Load_In_Box_Pos;
	double	m_dGantry_Y_Paper_Unload_Pos;
	double	m_dGantry_Y_Stick_Unload_To_Stage_Pos;
	double	m_dGantry_Y_Stick_Load_In_Stage_Pos;
	double	m_dGantry_Y_Stick_Unload_To_Box_Pos;
	//21.02.09 SJC
	double	m_dGantry_Y_Loading_Safe_Pos;
	double	m_dGantry_Y_Unloading_Safe_Pos;
	//

	//Gantry Z1 
	double	m_dGantry_Z1_Wait_Pos;	
	double	m_dGantry_Z1_PreAlign_Pos;
	double	m_dGantry_Z1_Inspection_Review_Pos;


	double	m_dGantry_Z1_Inspection_AOI_Pos;
	//Gantry Z2 
	double	m_dGantry_Z2_Wait_Pos;
	
	double	m_dGantry_Z2_Inspection_3D_Pos;//21.02.09 SJC
	double  m_dGantry_Z2_AOI_Review_Pos;

	//3D Camera Main Z -> Z3(Review cam)
	double	m_dGantry_Z3_Wait_Pos;
	
	double	m_dGantry_Z3_Mapping_Review_Pos;

	//3D Camera Sub Z
	double	m_d3D_Camera_Sub_Z_Wait_Pos;

}CManualDataGantryInfo, *pManualDataGantryInfo;

class CManualDataGantry
{
public:
	CManualDataGantry() {}
	~CManualDataGantry() {}
public:
	CManualDataGantryInfo Info;
	void		Init();
	BOOL		Save();
	BOOL		Load();
};
#pragma endregion

#pragma region //Box
typedef struct _CManualDataBoxInfo
{
	//Loading Stage X
	double	m_dLoadingStageX_Wait_Pos;
	double	m_dLoadingStageX_StickLoad_Pos;
	double	m_dLoadingStageX_StickUnload_Pos;

	//Loading Stage Y
	double	m_dLoadingStageY_Wait_Pos;
	double	m_dLoadingStageY_StickLoad_Pos;
	double	m_dLoadingStageY_StickUnload_Pos;

	//Loading Stage T
	double	m_dLoadingStageT_Wait_Pos;
	double	m_dLoadingStageT_StickLoad_Pos;
	double	m_dLoadingStageT_StickUnload_Pos;
	
}CManualDataBoxInfo, *pManualDataBoxInfo;

class CManualDataBox
{
public:
	CManualDataBox() {}
	~CManualDataBox() {}
public:
	CManualDataBoxInfo Info;
	void		Init();
	BOOL		Save();
	BOOL		Load();
};
#pragma endregion

#pragma region //Loader
typedef struct _CManualDataLoaderInfo
{
#pragma region //Loader Z
	double	m_dLoaderZ_Wait_Pos;
	double	m_dLoaderZ_StickLoadInBox1st_Pos;
	double	m_dLoaderZ_Vibration_Pos; //KJT 20210317;
	double	m_dLoaderZ_PaperUnloader_Pos;
	double	m_dLoaderZ_StickUnloadToStage_Pos;

	double	m_dLoaderZ_StickLoadInStage1st_Pos;	
	double	m_dLoaderZ_StickUnoadToBox_Pos;
		
	int		m_nLoaderZ_StepDownCount;	
	double	m_dLoaderZ_StepDownOffset;	
	double	m_dLoaderZ_StepUpOffset;	
	int		m_nLoaderZ_VibrationCount;	
	double	m_dLoaderZ_VibrationOffset; //KJT 20210317
	double	m_dLoaderZ_VibrationVel;
	

#pragma endregion

#pragma region //Loader SUB Z (ZL,ZR)
	//21.02.05 sjc ->//21.02.23 temp use need only up down pos
	//21.02.23 sjc
	double	m_dLoaderZL_Wait_Pos;
	double	m_dLoaderZR_Wait_Pos;

	double	m_dLoaderZL_Down_Pos;
	double	m_dLoaderZR_Down_Pos;

#pragma endregion

#pragma region //Loader X
	double	m_dLoaderX_Wait_Pos;
	double	m_dLoaderX_Tension_Offset;
#pragma endregion
	//21.02.10 sjc
#pragma region //Loader Y
	double	m_dLoaderY_Wait_Pos;
	double	m_dLoaderY_Stick_Load_Pos;
	double	m_dLoaderY_Stick_Unload_Pos;
	double	m_dLoaderY_Paper_Load_Pos;
	double	m_dLoaderY_Paper_Unload_Pos;
	double	m_dLoaderY_Inspection_Pos;
#pragma endregion
	//
	//21.02.26 sjc
	double	m_dLoaderZ_Inspection_Pos;
}CManualDataLoaderInfo, *pManualDataLoaderInfo;

class CManualDataLoader
{
public:
	CManualDataLoader() {}
	~CManualDataLoader() {}
public:
	CManualDataLoaderInfo Info;
	void		Init();
	BOOL		Save();
	BOOL		Load();
};
#pragma endregion

#pragma region //Inspect
typedef struct _CManualDataInspectInfo
{
	//Inspection Stage X
	double	m_dInspectionStageX_Wait_Pos;
	double	m_dInspectionStageX_StickLoad_Pos;
	double	m_dInspectionStageX_StickUnload_Pos;

	//Inspection Stage Y
	double	m_dInspectionStageY_Wait_Pos;
	double	m_dInspectionStageY_StickLoad_Pos;
	double	m_dInspectionStageY_StickUnload_Pos;

	//Inspection Stage T
	double	m_dInspectionStageT_Wait_Pos;
	double	m_dInspectionStageT_StickLoad_Pos;
	double	m_dInspectionStageT_StickUnload_Pos;

	//BackLight X
	double	m_dBackLightX_Wait_Pos;

}CManualDataInspectInfo, *pManualDataInspectInfo;

class CManualDataInspect
{
public:
	CManualDataInspect() {}
	~CManualDataInspect() {}
public:
	CManualDataInspectInfo Info;
	void		Init();
	BOOL		Save();
	BOOL		Load();
};
#pragma endregion

typedef struct _CManualDataClampInfo
{
	//Clamp Torque
	double m_dClampTorque;
}CManualDataClampInfo, *pManualDataClampInfo;;
class CManualDataClamp
{
public:
	CManualDataClamp() {}
	~CManualDataClamp() {}
public:
	CManualDataClampInfo Info;
	void		Init();
	BOOL		Save();
	BOOL		Load();
};

typedef struct _CManualDataStretchInfo
{
	//Stretch Left
	double m_dStretchLeft_1_WaitPos;
	double m_dStretchLeft_1_ForwardPos;
	double m_dStretchLeft_1_BackwardPos;
	//21.04.03 sjc
	double m_dStretchLeft_2_WaitPos;
	double m_dStretchLeft_2_ForwardPos;
	double m_dStretchLeft_2_BackwardPos;
	double m_dStretchLeft_3_WaitPos;
	double m_dStretchLeft_3_ForwardPos;
	double m_dStretchLeft_3_BackwardPos;

	//Stretch Right
	double m_dStretchRight_1_WaitPos;
	double m_dStretchRight_1_ForwardPos;
	double m_dStretchRight_1_BackwardPos;
	//21.04.03 sjc
	double m_dStretchRight_2_WaitPos;
	double m_dStretchRight_2_ForwardPos;
	double m_dStretchRight_2_BackwardPos;
	double m_dStretchRight_3_WaitPos;
	double m_dStretchRight_3_ForwardPos;
	double m_dStretchRight_3_BackwardPos;

}CManualDataStretchInfo, *pManualDataStretchInfo;;
class CManualDataStretch
{
public:
	CManualDataStretch() {}
	~CManualDataStretch() {}
public:
	CManualDataStretchInfo Info;
	void		Init();
	BOOL		Save();
	BOOL		Load();
};

typedef struct _CManualDataPitchInfo
{
	//Pitch Left
	double m_dPitchLeft_WaitPos[eGRIPPER_ROW_MAX];
	//Pitch Right
	double m_dPitchRight_WaitPos[eGRIPPER_ROW_MAX];

}CManualDataPitchInfo, *pManualDataPitchInfo;;
class CManualDataPitch
{
public:
	CManualDataPitch() {}
	~CManualDataPitch() {}
public:
	CManualDataPitchInfo Info;
	void		Init();
	BOOL		Save();
	BOOL		Load();
};

//--------------------------------------------
typedef struct _CManualDataGripperZInfo
{
	double m_dGripperLeftZ_WaitPos;
	double m_dGripperLeftZ_LoadingPos;
	double m_dGripperLeftZ_ClampPos;
	double m_dGripperLeftZ_TensionPos;
	double m_dGripperLeftZ_UnclampPos;
	//RIGHT GRIPPER Z
	double m_dGripperRightZ_WaitPos;
	double m_dGripperRightZ_LoadingPos;
	double m_dGripperRightZ_ClampPos;
	double m_dGripperRightZ_TensionPos;
	double m_dGripperRightZ_UnclampPos;

}CManualDataGripperZInfo, *pManualDataGripperZInfo;
class CManualDataGripperZ
{
public:
	CManualDataGripperZ() {}
	~CManualDataGripperZ() {}
public:
	CManualDataGripperZInfo Info;
	void		Init();
	BOOL		Save();
	BOOL		Load();
};

#pragma region //Unloader
typedef struct _MANUAL_DATA_UNLOADER_T
{
	//MaskUnloader Z
	double	m_dUnloaderZ_Wait_Pos;
	double	m_dUnloaderZ_Load_In_Stage_Pos;
	double	m_dUnloaderZ_Unload_To_Cst_Pos;
	double	m_dUnloaderZ_Load_In_Cst_Pos;
	double	m_dUnloaderZ_Unload_To_Stage_Pos;
	//21.02.15 SJC
	double	m_dUnloaderZ_Paper_Load_Pos;
	double	m_dUnloaderZ_Paper_Unload_Pos;
	double  m_dUnloaderZ_Vibration_Pos;
	
	int		m_nUnloaderZ_StepDownCount;
	double	m_dUnloaderZ_StepDownOffset;
	double	m_dUnloaderZ_StepUpOffset;
	int		m_nUnloaderZ_VibrationCount;
	double	m_dUnloaderZ_VibrationOffset; //KJT 20210317
	double	m_dUnloaderZ_VibrationVel;
	//	
		
	//
	//
	//PaperUnloader Y
	double	m_dUnloaderY_Wait_Pos;
	double	m_dUnloaderY_Load_In_Stage_Pos;
	double	m_dUnloaderY_Unload_To_Cst_Pos;
	double	m_dUnloaderY_Load_In_Cst_Pos;
	double	m_dUnloaderY_Unload_To_Stage_Pos;
	//21.02.15 SJC
	double	m_dUnloaderY_Paper_Load_Pos;
	double	m_dUnloaderY_Paper_Load_Waiting_Pos; //PaperUnloader Y
	double	m_dUnloaderY_Paper_Unload_Pos;
	double	m_dUnloaderY_Cassette_Safety_Pos;
	//

	//PaperUnloader X
	double	m_dPaperUnloader_XL_Wait_Pos;
	double	m_dPaperUnloader_XL_Tension_Offset;
	double	m_dPaperUnloader_XR_Wait_Pos;	
	double	m_dPaperUnloader_XR_Tension_Offset;

	//StickUnloader X
	double	m_dUnloaderX_Wait_Pos;
	double	m_dUnloaderX_Tension_Offset;
	
	//PaperUnloader Z
	double	m_dUnloaderZL_Wait_Pos;
	double	m_dUnloaderZL_Down_Pos;
	double	m_dUnloaderZR_Wait_Pos;
	double	m_dUnloaderZR_Down_Pos;
	double	m_dUnloaderZL_Paper_Load_Pos;
	double	m_dUnloaderZR_Paper_Load_Pos;
	double	m_dUnloaderZL_Paper_Unload_Pos;
	double	m_dUnloaderZR_Paper_Unload_Pos;
	//

}CManualDataUnloaderInfo, *pManualDataUnloaderInfo;

class CManualDataUnloader
{
public:
	CManualDataUnloader() {}
	~CManualDataUnloader() {}
public:
	CManualDataUnloaderInfo Info;
	void		Init();
	BOOL		Save();
	BOOL		Load();
};
#pragma endregion
//--------------------------------------------
#pragma region //Cassette
typedef struct _MANUAL_DATA_CASSETTE_T
{
	//Cassette Z
	double	m_dCassetteZ_Wait_Pos;
	double	m_dCassetteZ_1Floor_Pos;
	double	m_dCassetteZ_2Floor_Pos;
	double	m_dCassetteZ_3Floor_Pos;
	double	m_dCassetteZ_4Floor_Pos;
	double	m_dCassetteZ_5Floor_Pos;
	double	m_dCassetteZ_6Floor_Pos;

}CManualDataCassetteInfo, *pManualDataCassetteInfo;

class CManualDataCassette
{
public:
	CManualDataCassette() {}
	~CManualDataCassette() {}
public:
	CManualDataCassetteInfo Info;
	void		Init();
	BOOL		Save();
	BOOL		Load();
};
#pragma endregion

class CManualData
{
public:

	static CManualDataGantry				m_ManualDataGantry;
	static CManualDataBox					m_ManualDataBox;
	static CManualDataLoader				m_ManualDataLoader;
	static CManualDataInspect				m_ManualDataInspect;
	static CManualDataClamp					m_ManualDataClamp;
	static CManualDataStretch				m_ManualDataStretch;
	static CManualDataPitch					m_ManualDataPitch;
	static CManualDataGripperZ				m_ManualDataGripperZ;
	static CManualDataUnloader				m_ManualDataUnloader;
	static CManualDataCassette				m_ManualDataCassette;
public:
	CManualData();
	~CManualData();

	static void Initialize(void);
	static void Finalize(void);
	static void Save();
	static void Load();
	//---------------------------------------------------------------
};