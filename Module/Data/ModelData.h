#pragma once
#define	MAX_DATA_ARRAY_CNT		50
#define	MAX_WELDING_LINE_CNT	10

#define FRAME_ALIGN_HOLE_CNT	4

#include "Common/CommonDefine.h"

#pragma region //MaterialPara
typedef struct _MODEL_DATA_MATERIAL_PARA
{
	//Sitck Info
	double dStickSizeX;
	double dStickSizeY;
	double dStickLeftTopX;
	double dStickLeftTopY;
	double dAlignLeftHoleX;
	double dAlignLeftHoleY;
	double dAlignRightHoleX;
	double dAlignRightHoleY;
	int nHoleShape;
	int nHoleArrange;
	double dAlignHoleSizeX;
	double dAlignHoleSizeY;
	double dStickThickness;
	double dPaperThickness;
	//Cell Info
	int nCellCountX;
	int nCellCountY;
	double dFirstCellLeftTopX;
	double dFirstCellLeftTopY;
	double dCellPitchX;
	double dCellPitchY;

	//Sub Cell Info
	double dCellLeftTopX[CELL_X_COUNT_MAX][CELL_Y_COUNT_MAX];
	double dCellLeftTopY[CELL_X_COUNT_MAX][CELL_Y_COUNT_MAX];
	double dCellSizeX[CELL_X_COUNT_MAX][CELL_Y_COUNT_MAX];
	double dCellSizeY[CELL_X_COUNT_MAX][CELL_Y_COUNT_MAX];
	int nInspectionSlotCount[CELL_X_COUNT_MAX][CELL_Y_COUNT_MAX];
	//Slot Info
	double dSlotCenterShiftX[CELL_X_COUNT_MAX][CELL_Y_COUNT_MAX];
	double dSlotCenterShiftY[CELL_X_COUNT_MAX][CELL_Y_COUNT_MAX];
	double dSlotSizeX[CELL_X_COUNT_MAX][CELL_Y_COUNT_MAX];
	double dSlotSizeY[CELL_X_COUNT_MAX][CELL_Y_COUNT_MAX];
	double dSlotAngle[CELL_X_COUNT_MAX][CELL_Y_COUNT_MAX];
	double dSlotPitchX[CELL_X_COUNT_MAX][CELL_Y_COUNT_MAX];
	double dSlotPitchY[CELL_X_COUNT_MAX][CELL_Y_COUNT_MAX];
	double dSlotTotalPitchX[CELL_X_COUNT_MAX][CELL_Y_COUNT_MAX];
	double dSlotTotalPitchY[CELL_X_COUNT_MAX][CELL_Y_COUNT_MAX];

	//Tegkey Info
	double dTegkey_LT_X;
	double dTegkey_LT_Y;
	double dTegkey_LB_X;
	double dTegkey_LB_Y;
	double dTegkey_RT_X;
	double dTegkey_RT_Y;
	double dTegkey_RB_X;
	double dTegkey_RB_Y;
	double dTegkey_SizeX;
	double dTegkey_SizeY;

	//Wing Y Offset //Skirt
	double dStickWingCenterYOffset[eGRIPPER_ROW_MAX]; //0:+

	//KJT 20210411
	int nTPRepeatCount;
	int nTPCount;
	double dTPSizeX;
	double dTPSizeY;
	double dTPPosX[MAX_TP_COUNT];
	double dTPPosY[MAX_TP_COUNT];

	//KJT 20210411
	int n3DHoleRepeatCount;
	int n3DHoleCount;
	double d3DHoleSizeX;
	double d3DHoleSizeY;
	double d3DHolePosX[MAX_3D_HOLE_COUNT];
	double d3DHolePosY[MAX_3D_HOLE_COUNT];

	double dReview10XCornerLT_X[4]; //KJT 20210824 Add
	double dReview10XCornerLT_Y[4]; //KJT 20210824 Add
	double dReview10XCornerRB_X[4]; //KJT 20210824 Add
	double dReview10XCornerRB_Y[4]; //KJT 20210824 Add
	double dReview10XCornerAngle[4]; //KJT 20210824 Add
}CMaterialParaInfo, *pCMaterialParaInfo;
class CMaterialPara
{
public:
	CMaterialPara() {}
	~CMaterialPara() {}
public:
	CMaterialParaInfo	Info;
	void	Init();
	BOOL	Save(BOOL byTensionRatio = FALSE); //KJT 20210301
	BOOL	Load();
};
#pragma endregion

#pragma region //AtMaterialPara
typedef struct _MODEL_DATA_AT_MATERIAL_PARA
{
	//Sitck Info
	double dStickSizeX;
	double dStickSizeY;
	double dStickLeftTopX;
	double dStickLeftTopY;
	double dAlignLeftHoleX;
	double dAlignLeftHoleY;
	double dAlignRightHoleX;
	double dAlignRightHoleY;
	int nHoleShape;
	int nHoleArrange;
	double dAlignHoleSizeX;
	double dAlignHoleSizeY;
	double dStickThickness;
	double dPaperThickness;
	//Cell Info
	int nCellCountX;
	int nCellCountY;
	double dFirstCellLeftTopX;
	double dFirstCellLeftTopY;
	double dCellPitchX;
	double dCellPitchY;

	//Sub Cell Info
	double dCellLeftTopX[CELL_X_COUNT_MAX][CELL_Y_COUNT_MAX];
	double dCellLeftTopY[CELL_X_COUNT_MAX][CELL_Y_COUNT_MAX];
	double dCellSizeX[CELL_X_COUNT_MAX][CELL_Y_COUNT_MAX];
	double dCellSizeY[CELL_X_COUNT_MAX][CELL_Y_COUNT_MAX];
	int nInspectionSlotCount[CELL_X_COUNT_MAX][CELL_Y_COUNT_MAX];
	//Slot Info
	double dSlotCenterShiftX[CELL_X_COUNT_MAX][CELL_Y_COUNT_MAX];
	double dSlotCenterShiftY[CELL_X_COUNT_MAX][CELL_Y_COUNT_MAX];
	double dSlotSizeX[CELL_X_COUNT_MAX][CELL_Y_COUNT_MAX];
	double dSlotSizeY[CELL_X_COUNT_MAX][CELL_Y_COUNT_MAX];
	double dSlotAngle[CELL_X_COUNT_MAX][CELL_Y_COUNT_MAX];
	double dSlotPitchX[CELL_X_COUNT_MAX][CELL_Y_COUNT_MAX];
	double dSlotPitchY[CELL_X_COUNT_MAX][CELL_Y_COUNT_MAX];
	double dSlotTotalPitchX[CELL_X_COUNT_MAX][CELL_Y_COUNT_MAX];
	double dSlotTotalPitchY[CELL_X_COUNT_MAX][CELL_Y_COUNT_MAX];

	//Tegkey Info
	double dTegkey_LT_X;
	double dTegkey_LT_Y;
	double dTegkey_LB_X;
	double dTegkey_LB_Y;
	double dTegkey_RT_X;
	double dTegkey_RT_Y;
	double dTegkey_RB_X;
	double dTegkey_RB_Y;
	double dTegkey_SizeX;
	double dTegkey_SizeY;

	//Wing Y Offset
	double dStickWingCenterYOffset[eGRIPPER_ROW_MAX]; //0:+

	double dTensionRatioX; //KJT 20210301
	double dTensionRatioY; //KJT 20210415

	//KJT 20210411
	int nTPRepeatCount;
	int nTPCount;
	double dTPSizeX;
	double dTPSizeY;
	double dTPPosX[MAX_TP_COUNT];
	double dTPPosY[MAX_TP_COUNT];

	//KJT 20210411
	int n3DHoleRepeatCount;
	int n3DHoleCount;
	double d3DHoleSizeX;
	double d3DHoleSizeY;
	double d3DHolePosX[MAX_3D_HOLE_COUNT];
	double d3DHolePosY[MAX_3D_HOLE_COUNT];

	double dReview10XCornerLT_X[4]; //KJT 20210824 Add
	double dReview10XCornerLT_Y[4]; //KJT 20210824 Add
	double dReview10XCornerRB_X[4]; //KJT 20210824 Add
	double dReview10XCornerRB_Y[4]; //KJT 20210824 Add
	double dReview10XCornerAngle[4]; //KJT 20210824 Add
}CAtMaterialParaInfo, *pCAtMaterialParaInfo;
class CAtMaterialPara
{
public:
	CAtMaterialPara() {}
	~CAtMaterialPara() {}
public:
	CAtMaterialParaInfo	Info;
	void	Init();
	BOOL	Save();
	BOOL	Load();
};
#pragma endregion

#pragma region //MaterialParaAlignStick
typedef struct _MODEL_DATA_MATERIAL_PARA_ALIGN_STICK
{
	TCHAR	strID[MAX_PATH];
	int		nOrder;
	double	dSizeX;
	double	dSizeY;
	double	dPosY;

	double	dAlignMarkSizeX;
	double	dAlignMarkSizeY;
	double	dAlignMarkLTX;
	double	dAlignMarkLTY;
	double	dAlignMarkRTX;
	double	dAlignMarkRTY;

	double	dDepoMarkSizeX;
	double	dDepoMarkSizeY;
	double	dDepoMarkLTX;
	double	dDepoMarkLTY;
	double	dDepoMarkRTX;
	double	dDepoMarkRTY;

	double	dTegSizeX = 0.0;
	double	dTegSizeY = 0.0;
	double	dTegLT1X = 0.0;
	double	dTegLT1Y = 0.0;
	double	dTegRT2X = 0.0;
	double	dTegRT2Y = 0.0;

	double dSkirtPitchY = 0.0;

	double dBcrPosX = 0.0;
	double dBcrPosY = 0.0;
}CMaterialParaAlignStickInfo, *pCMaterialParaAlignStickInfo;
class CMaterialParaAlignStick
{
public:
	CMaterialParaAlignStick() {}
	~CMaterialParaAlignStick() {}
public:
	CMaterialParaAlignStickInfo	Info;
	void	Init();
	BOOL	Save();
	BOOL	Load();
};
#pragma endregion

#pragma region //AtMaterialParaAlignStick
typedef struct _MODEL_DATA_AT_MATERIAL_PARA_ALIGN_STICK
{
	TCHAR	strID[MAX_PATH];
	int		nOrder;
	double	dSizeX;
	double	dSizeY;
	double	dPosY;

	double	dAlignMarkSizeX;
	double	dAlignMarkSizeY;
	double	dAlignMarkLTX;
	double	dAlignMarkLTY;
	double	dAlignMarkRTX;
	double	dAlignMarkRTY;

	double	dDepoMarkSizeX;
	double	dDepoMarkSizeY;
	double	dDepoMarkLTX;
	double	dDepoMarkLTY;
	double	dDepoMarkRTX;
	double	dDepoMarkRTY;

	double	dTegSizeX = 0.0;
	double	dTegSizeY = 0.0;
	double	dTegLT1X = 0.0;
	double	dTegLT1Y = 0.0;
	double	dTegRT2X = 0.0;
	double	dTegRT2Y = 0.0;

	double dSkirtPitchY = 0.0;

	double dBcrPosX = 0.0;
	double dBcrPosY = 0.0;
}CAtMaterialParaAlignStickInfo, *pCAtMaterialParaAlignStickInfo;
class CAtMaterialParaAlignStick
{
public:
	CAtMaterialParaAlignStick() {}
	~CAtMaterialParaAlignStick() {}
public:
	CAtMaterialParaAlignStickInfo	Info;
	void	Init();
	BOOL	Save();
	BOOL	Load();
};
#pragma endregion

#pragma region //InspectionPara
typedef struct _MODEL_DATA_INSPECTION_PARA
{
	BOOL bPPAUse;
	BOOL bAOIUse;
	BOOL bAOIReviewUse;
	int nPPAAlignMethod;
	int nEdgeAlignMethod;
	int nDarkThreshold;
	int nBrightThreshold;
	double dAOIDefectSizeMin;
	int nPPAFocusType; //PPA 검사시 Focusing 옵션 선택 (Image, Laser)
	int nPPATrackingType; //Image 검사 사용 여부 (None, Motion, Image)
	BOOL bInspectionStageVacuumOn; //검사시 Inspection Stage Vacuum On/Off 설정
	BOOL bAppendixSensorUse; //흡착 확인 센서 사용 여부

	double dInspectionStage_HoleZ;
	double dInspectionStage_HeightZ;

	int nAlignDataUseMode;
	int nMeasureCameraMode;
	int nStickTensionUseMode; //KJT 20210406

	BOOL bLoaderFingerUse_Stick1;
	BOOL bLoaderFingerUse_Stick2;
	BOOL bLoaderFingerUse_Stick3;
	BOOL bLoaderFingerUse_Stick4;
	BOOL bLoaderFingerUse_Stick5;
	BOOL bLoaderFingerUse_Paper1;
	BOOL bLoaderFingerUse_Paper2;
	BOOL bLoaderFingerUse_Paper3;
	BOOL bLoaderFingerUse_Paper4;
	BOOL bLoaderFingerUse_Paper5;

	BOOL bUnloaderFingerUse_Stick1;
	BOOL bUnloaderFingerUse_Stick2;
	BOOL bUnloaderFingerUse_Stick3;
	BOOL bUnloaderFingerUse_Stick4;
	BOOL bUnloaderFingerUse_Stick5;

	BOOL bPaperUnloaderFingerUse_1;
	BOOL bPaperUnloaderFingerUse_2;
	BOOL bPaperUnloaderFingerUse_3_4;
	BOOL bPaperUnloaderFingerUse_5;
	BOOL bPaperUnloaderFingerUse_6;

	BOOL bMappingDataUse;
	BOOL bAlignDataUse;
	BOOL bMeasureCornerR;

	int nAOIReviewBacklight;

	

	//KJT 20210307
	BOOL bTegkey2PAlignFlowUse;
	BOOL b3dFlowUse;

	int  nAOIScanSpeedLevel; //KJT 20210315

	BOOL bSWAlignFlowUse; //KJT 20210315

	BOOL bTPUse; //KJT 20210406

	BOOL bOnlyUnloadingMode; //KJT 20210406

	BOOL bSwAlignVerifyUse; //KJT 20210428

	int nBoxStickExistType;
	BOOL bOnlyUnloadModePreAlignUse;

}CInspectionParaInfo, *pCInspectionParaInfo;
class CInspectionPara
{
public:
	CInspectionPara() {}
	~CInspectionPara() {}
public:
	CInspectionParaInfo	Info;
	void	Init();
	BOOL	Save();
	BOOL	Load();
};
#pragma endregion

#pragma region //StretchPara
typedef struct _MODEL_DATA_STRETCH_PARA
{
	BOOL bStretchUse[eGRIPPER_ROW_MAX];
	double dStretchNewton[MAX_STEP][eGRIPPER_ROW_MAX];
	int nStepCount;
	double dSpeedMax;
	double dSpeedMin;
	double dOkRange;
	double dDecelRange;
	double dReleaseForce;
	double dMaxForce;
}CStretchParaInfo, *pCStretchParaInfo;
class CStretchPara
{
public:
	CStretchPara() {}
	~CStretchPara() {}
public:
	CStretchParaInfo 	Info;
	void	Init();
	BOOL	Save();
	BOOL	Load();
};
#pragma endregion

#pragma region //Glass Info
typedef struct  _ModelDataGlassInfo
{
	double	dGlassSizeX;
	double	dGlassSizeY;
	double	dGlassHeightZ;

	double	dGlassAlignMarkSizeX;
	double	dGlassAlignMarkSizeY;

	int		nGlassAlignPoint; //0:2Point, 1:4Point
	int		nGlassAlignApplyCalibCheck;

	double	dGlassAlignMark_LT_X;
	double	dGlassAlignMark_LT_Y;
	double	dGlassAlignMark_RT_X;
	double	dGlassAlignMark_RT_Y;
	double	dGlassAlignMark_LB_X;
	double	dGlassAlignMark_LB_Y;
	double	dGlassAlignMark_RB_X;
	double	dGlassAlignMark_RB_Y;

	int		nGlassMainAlignTargetCount;
	double	dGlassMainAlignTargetX;
	double	dGlassMainAlignTargetY;
	double	dGlassMainAlignTargetT;
	double	dGlassPreAlignTargetX;
	double	dGlassPreAlignTargetY;
	double	dGlassPreAlignTargetT;

	int		nBrightnessPreAlignCoaxial;
	int		nBrightnessPreAlignRing;
	int		nBrightnessPreAlignThreshold;

	int		nBrightness10XCoaxial;
	int		nBrightness10XRing;
	int		nBrightness10XBackLight;
	int		nBrightness10XThreshold;

	int		nBrightness20XCoaxial;
	int		nBrightness20XRing;
	int		nBrightness20XBackLight;
	int		nBrightness20XThreshold;

	int		nBrightnessPreAlignMarkSelect;
	int		nBrightnessPreAlignFindSelect;

	int		nBrightness10XLightSelect;
	int		nBrightness10XMarkSelect;
	int		nBrightness10XFindSelect;
	int		nBrightness10XFocusSelect;

	int		nBrightness20XLightSelect;
	int		nBrightness20XMarkSelect;
	int		nBrightness20XFindSelect;
	int		nBrightness20XFocusSelect;

}ModelDataGlassInfo, *PModelDataGlassInfo;

class CModelDataGlass
{
public:
	CModelDataGlass() {}
	~CModelDataGlass() {}

public:

	ModelDataGlassInfo Info;

	void	Init();
	BOOL		Save();
	BOOL		Load();

};
#pragma endregion

#pragma region //Align Info
typedef struct  _ModelDataAlignInfo
{
	//Box Left Align
	int nBoxAlignLeftTargetCount;
	double dBoxAlignLeftTargetX;
	double dBoxAlignLeftTargetY;
	int nBoxAlignLeftCoAxial;
	int nBoxAlignLeftRing;
	int nBoxAlignLeftThreshold;
	int nBoxAlignLeftLightType;
	int nBoxAlignLeftMarkType;
	int nBoxAlignLeftFocusType;
	int nBoxAlignLeftBlackWhiteType;

	//Box Align Right
	int nBoxAlignRightTargetCount;
	double dBoxAlignRightTargetX;
	double dBoxAlignRightTargetY;
	int nBoxAlignRightCoAxial;
	int nBoxAlignRightRing;
	int nBoxAlignRightThreshold;
	int nBoxAlignRightLightType;
	int nBoxAlignRightMarkType;
	int nBoxAlignRightFocusType;
	int nBoxAlignRightBlackWhiteType;

	//Pre Align
	int nPreAlignTargetCount;
	double dPreAlignTargetX;
	double dPreAlignTargetY;
	int nPreAlignCoAxial_L;
	int nPreAlignRing_L;
	int nPreAlignThreshold_L;
	int nPreAlignCoAxial_R;
	int nPreAlignRing_R;
	int nPreAlignThreshold_R;
	int nPreAlignLightType;
	int nPreAlignMarkType;
	int nPreAlignFocusType;
	int nPreAlignBlackWhiteType;

	//Main 2P Align
	int nMain2PAlignTargetCount;
	double dMain2PAlignTargetX;
	double dMain2PAlignTargetY;
	int nMain2PAlignCoAxial;
	int nMain2PAlignRing;
	int nMain2PAlignThreshold;
	int nMain2PAlignBackLight;
	int nMain2PAlignLightType;
	int nMain2PAlignMarkType;
	int nMain2PAlignFocusType;
	int nMain2PAlignBlackWhiteType;

	//Edge 4P Align
	int nEdge4PAlignTargetCount;
	double dEdge4PAlignTargetX;
	double dEdge4PAlignTargetY;
	int nEdge4PAlignCoAxial;
	int nEdge4PAlignRing;
	int nEdge4PAlignThreshold;
	int nEdge4PAlignLightType;
	int nEdge4PAlignMarkType;
	int nEdge4PAlignFocusType;
	int nEdge4PAlignBlackWhiteType;
	int nEdge4PAlignBacklight;

	//Tegkey Align
	int nTegkeyAlignTargetCount;
	double dTegkeyAlignTargetX;
	double dTegkeyAlignTargetY;
	int nTegkeyAlignCoAxial;
	int nTegkeyAlignRing;
	int nTegkeyAlignThreshold;
	int nTegkeyAlignLightType;
	int nTegkeyAlignMarkType;
	int nTegkeyAlignFocusType;
	int nTegkeyAlignBlackWhiteType;
	int nTegkeyAlignBacklight;

	//Vertical Pre Align
	int nVerticalPreAlignTargetCount;
	double dVerticalPreAlignTargetX;
	double dVerticalPreAlignTargetY;
	int nVerticalPreAlignCoAxial;
	int nVerticalPreAlignRing;
	int nVerticalPreAlignThreshold;
	int nVerticalPreAlignBackLight;
	int nVerticalPreAlignLightType;
	int nVerticalPreAlignMarkType;
	int nVerticalPreAlignFocusType;
	int nVerticalPreAlignBlackWhiteType;

	//Vertical Main Align
	int nVerticalMainAlignTargetCount;
	double dVerticalMainAlignTargetX;
	double dVerticalMainAlignTargetY;
	int nVerticalMainAlignCoAxial;
	int nVerticalMainAlignRing;
	int nVerticalMainAlignThreshold;
	int nVerticalMainAlignBackLight;
	int nVerticalMainAlignLightType;
	int nVerticalMainAlignMarkType;
	int nVerticalMainAlignFocusType;
	int nVerticalMainAlignBlackWhiteType;

	//Sw Align //KJT 20210307
	int nSwAlignTargetCount;
	double dSwAlignTargetX;
	double dSwAlignTargetY;
	int nSwAlignCoAxial;
	int nSwAlignRing;
	int nSwAlignThreshold;
	int nSwAlignLightType;
	int nSwAlignMarkType;
	int nSwAlignFocusType;
	int nSwAlignBlackWhiteType;
	int nSwAlignBacklight;

	//Measure Half Edge Hole //KJT 20210416
	int nTPCoAxial[3];
	int nTPRing[3];
	int nTPThreshold[3];
	int nTPBacklight[3];
	int nTPLightType;
	int nTPMarkType;
	int nTPFocusType;
	int nTPBlackWhiteType;

	//x20 light scale
	double dx20CoAxialScale;
	double dx20RingScale;
	double dx20BackLightScale;
	//x50 light scale
	double dx50CoAxialScale;
	double dx50RingScale;
	double dx50BackLightScale;

}ModelDataAlignInfo, *PModelDataAlignInfo;

class CModelDataAlign
{
public:
	CModelDataAlign() {}
	~CModelDataAlign() {}

public:

	ModelDataAlignInfo Info;

	void	Init();
	BOOL		Save();
	BOOL		Load();
};
#pragma endregion

#pragma region //Align Info
typedef struct  _ModelDataManualnfo
{
	double dStickLoaderX_AlignPos;
	double dStickLoaderX_PickUpPos;
	double dStickUnloaderX_PickUpPos;
	double dPaperUnloaderX_PickUpPos;
}ModelDataManualnfo, *PModelDataManualnfo;
class CModelDataManual
{
public:
	CModelDataManual() {}
	~CModelDataManual() {}

public:

	ModelDataManualnfo Info;

	void		Init();
	BOOL		Save();
	BOOL		Load();
};
#pragma endregion

#pragma region //PPA Para
typedef struct  _ModelDataPpa
{
	//PPA
	int nPpaTargetCount;
	double dPpaTargetX;
	double dPpaTargetY;
	int nPpaCoAxial[3];
	int nPpaRing[3];
	int nPpaThreshold[3];
	int nPpaBacklight[3];
	int nPpaLightType;
	int nPpaMarkType;
	int nPpaFocusType;
	int nPpaBlackWhiteType;

	//KJT 20210525
	int nDivX;
	int nDivY;
	int nSlotQuantityXY;
}ModelDataPpa, *PModelDataPpa;

class CModelDataPpa
{
public:
	CModelDataPpa() {}
	~CModelDataPpa() {}

public:

	ModelDataPpa Info;

	void		Init();
	BOOL		Save();
	BOOL		Load();
};
#pragma endregion

class CModelData
{
public:
	CModelData();
	~CModelData();

	static class CMaterialPara				m_MaterialPara;
	static class CAtMaterialPara			m_AtMaterialPara;
	static class CMaterialParaAlignStick	m_MaterialParaAlignStick;
	static class CAtMaterialParaAlignStick	m_AtMaterialParaAlignStick;
	static class CInspectionPara			m_InspectionPara;
	static class CStretchPara				m_StretchPara;
	static class CModelDataGlass			m_GlassPara;
	static class CModelDataAlign			m_AlignPara;
	static class CModelDataManual			m_ModelSubManualPara;
	static class CModelDataPpa				m_PpaPara;

public:
	static void Initialize(void);
	static void Finalize(void);

	static void Save();
	static void Load();
};
//--------------------------------------------------------------------------------
