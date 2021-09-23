#pragma once

#pragma region //System Safety
typedef struct _CSystemDataSafetyInfo
{
	double m_dSafetyPos_Min_Review10X_X;
	double m_dSafetyPos_Max_Review10X_X;
	double m_dSafetyPos_Min_Review10X_Y_In_BoxStage;
	double m_dSafetyPos_Min_Review10X_Y_In_PaperStage;
	double m_dSafetyPos_Min_Review10X_Y_In_InspectionStage;
	double m_dSafetyPos_Max_Review10X_Y;
	double m_dSafetyPos_Min_Review10X_Z;

	double m_dSafetyPos_Min_AOI_X;
	double m_dSafetyPos_Max_AOI_X;
	double m_dSafetyPos_Min_AOI_Y;
	double m_dSafetyPos_Max_AOI_Y;
	double m_dSafetyPos_Min_AOI_Z;

	double m_dSafetyPos_Min_Zoom_3D_X;
	double m_dSafetyPos_Max_Zoom_3D_X;
	double m_dSafetyPos_Min_Zoom_3D_Y;
	double m_dSafetyPos_Max_Zoom_3D_Y;
	double m_dSafetyPos_Min_Zoom_3D_Z;

	double m_dSafetyPos_Min_Loader_Z_In_Box_Stage;
	double m_dSafetyPos_Min_Loader_Z_In_Paper_Stage;
	double m_dSafetyPos_Min_Loader_Z_In_Inspection_Stage;

	double m_dDist_GantryY_To_UnloaderY;
	double m_dDist_GantryY_To_LoaderY;

	double m_dMinDist_GantryY_To_UnloaderY;
	double m_dMinDist_GantryY_To_LoaderY;

	double m_dMinDist_PaperUnloaderY_To_LoaderY;
	double m_dMinDist_PaperUnloaderX_To_LoaderX;

	int m_nUseSystemSafety;

}CSystemDataSafetyInfo, *PCSystemDataSafetyInfo;
class CSystemDataSafety : public C_FileIni
{
public:
	CSystemDataSafetyInfo Info;


	BOOL		Save();
	BOOL		Load();
};
#pragma endregion

#pragma region //System Option
typedef struct _CSystemDataOptionInfo
{
	TCHAR m_strActiveModelName[255];

	BOOL m_bImageAutoSave;		// 이미지 자동 저장 기능 사용 여부 확인
	BOOL m_bImageAutoDel;		// 이미지 자동 삭제 기능 사용 여부 확인

	INT	 m_nUserMode;			// ?
	INT	 m_nWorkMode;			// ?

	INT	 nImageDelPeriod;		// 이미지 보관 기간? 이미지 삭제 주기? 얼마나 보관할지?

	double m_dAutoFocusSpeed;
	double m_dAutoFocusUpRange;
	double m_dAutoFocusDownRange;

	int m_nAutoFocusMode;

	int m_nSmart_InMotionCheckMode;
	int m_nSmart_DelayTime;
	int m_nSmart_MaxTurnCount;
	int m_nSmart_RefTurnCount;
	double m_dSmart_LimitFocusValue;
	double m_dSmart_MinFocusValue;
	double m_dSmart_FocusTolerance;
	int m_nSmart_ScanMode;
	double m_dSmart_MinStepValue;
	double m_dSmart_MaxStepValue;
	double m_dSmart_DownDistRange;
	double m_dSmart_UpDistRange;
	double m_dSmart_Vel; //KJT 2021803 Add
	double m_dSmart_Accel;
	double m_dSmart_Decel;

	BOOL m_bAOIAlgorithmSkip;
	BOOL m_bAOIMappingGlassMode;
	double m_dAOI_Z_MappingGlassPos;

	BOOL m_bGlassMode;
	BOOL m_bAOIAgingMode;
}CSystemDataOptionInfo, *PCSystemDataOptionInfo;
class CSystemDataOption : public C_FileIni
{
public:
	CSystemDataOptionInfo Info;


	BOOL		Save();
	BOOL		Load();
};
#pragma endregion

#pragma region //System Coordinate
typedef struct _CSystemDataCoordinateInfo
{
	//Camera Offset
	double dOffsetReview10xTo20x_X;
	double dOffsetReview10xTo20x_Y;
	double dOffsetReview10xTo20x_Z;
	double dOffsetReview10xToPreAlign_X;
	double dOffsetReview10xToPreAlign_Y;
	double dOffsetReview10xToPreAlign_Z;
	double dOffsetReview10xToAoi_X;
	double dOffsetReview10xToAoi_Y;
	double dOffsetReview10xToAoi_Z;
	double dOffsetReview10xTo3dCam_X;
	double dOffsetReview10xTo3dCam_Y;
	double dOffsetReview10xTo3dCam_Z;
	double dOffsetReview10xTo50x_X;
	double dOffsetReview10xTo50x_Y;

	double dOffsetCameraZ[DIRECT_AXIS_MAX];

	//double dOffsetCamera3DMainZ;
	double d3DCam_Resolution_X;
	double d3DCam_Resolution_Y;

	//20210729 JINI
	double d10XCam_Resolution_X;
	double d10XCam_Resolution_Y;

	double d20XCam_Resolution_X;
	double d20XCam_Resolution_Y;

	double d50XCam_Resolution_X;
	double d50XCam_Resolution_Y;

	double dMax_Tension_Offset_LoaderX; //KJT 20210806 Add
	double dMax_Tension_Offset_UnloaderX;
	double dMax_Tension_Offset_PaperUnloaderX;

	double dOffsetReview10xToLaser_X; //KJT 20210824 Add
	double dOffsetReview10xToLaser_Y; //KJT 20210824 Add
	double dLaserFocusOffsetGlass;
	double dLaserFocusOffsetStick;

	int nBackLightXFwdStartDelay[eAOI_Vel_Max];
	double dBackLightXFwdAccDecScale[eAOI_Vel_Max];
	int nBackLightXBwdStartDelay[eAOI_Vel_Max];
	double dBackLightXBwdAccDecScale[eAOI_Vel_Max];
}CSystemDataCoordinateInfo, *PCSystemDataCoordinateInfo;
class CSystemDataCoordinate : public C_FileIni
{
public:

	CSystemDataCoordinate()
	{
	}

	CSystemDataCoordinateInfo Info;

	BOOL		Save();
	BOOL		Load();
};
#pragma endregion

#pragma region //System Other //KJT 20210329
typedef struct _CSystemDataOtherInfo
{
	//KJT 20210329
	BOOL m_bAutoDeleteDirPathUse[MAX_AUTO_DELETE_DIR_PATH];
	int m_nFileStoreDays[MAX_AUTO_DELETE_DIR_PATH];

	double m_dHighTemperature;
	double m_dLowTemperature;
	int m_nUseTemperatureCheck;

	int m_nUseDoorOpenCheck;
	int m_nUseAuto3DConnection;

	int m_nElectricChuckVolt;

	double m_dZoom2XPos;
	double m_dZoom10XPos;
	double m_dZoom20XPos;

}CSystemDataOtherInfo, *PCSystemDataOtherInfo;
class CSystemDataOther : public C_FileIni
{
public:

	CSystemDataOther()
	{
	}

	CSystemDataOtherInfo Info;

	BOOL		Save();
	BOOL		Load();
	BOOL		InitElectricChuck();
};
#pragma endregion

#pragma region //Machine Stage Info
typedef struct _CSystemDataStageInfo
{
	double m_dParameterSizeX;
	double m_dParameterSizeY;
	double m_dParameterZ;
	double m_dParameterStartX;
	double m_dParameterStartY;
	double m_dParameterPitchX;
	double m_dParameterPitchY;
	int m_nParameterCountX;
	int m_nParameterCountY;
	int m_nParameterPitchFile;

	int m_nPointNoX;
	int m_nPointNoY;

	int m_nCalibDelay;
	int m_nCalibRepeat;
	double m_dCalib3SigmaX;
	double m_dCalib3SigmaY;
	int m_nCaliApplyCalib;

	int m_nVerifyRepeat;
	double m_dVerifyWorldX1;
	double m_dVerifyWorldY1;
	double m_dVerifyWorldX2;
	double m_dVerifyWorldY2;
	double m_dVerifyRealX1;
	double m_dVerifyRealY1;
	double m_dVerifyRealX2;
	double m_dVerifyRealY2;

	int m_nAlignPoint2_4;
	double m_dAlignLTX;
	double m_dAlignLTY;
	double m_dAlignRTX;
	double m_dAlignRTY;
	double m_dAlignLBX;
	double m_dAlignLBY;
	double m_dAlignRBX;
	double m_dAlignRBY;
	int m_nAlignTargetCount;
	double m_dAlignTargetX;
	double m_dAlignTargetY;
	double m_dAlignTargetT;
	int m_nAlignRealignCount;

	int m_nCalibVerify;

	int m_nXYTIntervalCount;
	int m_nMappingRepeatCount;
	int m_nVerificationRepeatCount;
	int m_nMappingPreAlign;
	int m_nMappingMainAlign;	
	int m_nApplyMappingResult;

}CSystemDataStageInfo, *PCSystemDataStageInfo;
class CSystemDataStage : public C_FileIni
{

public:
	CSystemDataStageInfo Info;

public:

	BOOL		Save();
	BOOL		Load();
};
#pragma endregion

#pragma region //Camera Cal Info
typedef struct _CSystemDataCameraCalInfo
{
	double m_dParameterSizeX;
	double m_dParameterSizeY;
	double m_dParameterZ;
	double m_dParameterStartX;
	double m_dParameterStartY;
	double m_dParameterPitchX;
	double m_dParameterPitchY;
	int m_nParameterCountX;
	int m_nParameterCountY;

	int m_nCalibDelay;
	int m_nCalibRepeat;
	int m_nCaliApplyCalib;
	int m_nCaliFindType; //KJT 20210820 Add

}CSystemDataCameraCalInfo, *PCSystemDataCameraCalInfo;

class CSystemDataCameraCal : public C_FileIni
{

public:
	CSystemDataCameraCalInfo Info[3];
public:

	BOOL		Init();
	BOOL		Save();
	BOOL		Load();

};
#pragma endregion

class CSystemData
{
public:
	CSystemData();
	~CSystemData();

	static class CSystemDataSafety					m_Safety;
	static class CSystemDataOption					m_Option;
	static class CSystemDataCoordinate				m_Coordinate;
	static class CSystemDataOther					m_Other; //KJT 20210329
	static class CSystemDataStage					m_Stage;
	static class CSystemDataCameraCal				m_CameraCal; //KJT 20210524

public:
	static void Initialize(void);
	static void Finalize(void);
	static BOOL Save();
	static BOOL Load();
};



