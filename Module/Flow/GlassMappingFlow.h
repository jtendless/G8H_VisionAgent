#pragma once

#include "../Module/Vision/MappingProc.h"

#ifndef SIM_MODE
#include "../../WkLibVision/WkLibVision.h"
#endif

class CGlassMappingFlow : public CBaseFlow
{
public:
	CGlassMappingFlow();
	~CGlassMappingFlow();

private:

	int m_nDelayCnt;
	BOOL m_nVerification;
	BOOL m_bFlowDone;

#ifndef SIM_MODE
	stModCirclePara ModCirclePara;
	wk_MilModelFindData m_ModelFindData;
	wk_MilCameraInfo m_CameraInfo;
	wk_MilBlobData	m_BlobData;
#endif

	CWinThread*		pThread;
	VOID			ThreadFunctionEntry(VOID);
	static UINT		ThreadFunction(LPVOID lpParam);
	BOOL			m_FlowFinish;
	void(*m_StateComplete)(void *pArgument);

	CGantryMotion *pGantry;
	
	
	BOOL(CGantryMotion::*ReviewCamPosMove)(double, double, BOOL, BOOL, BOOL, BOOL, BOOL);
	BOOL(CGantryMotion::*IsReviewCamPosMove)(void);
	
	int(CGantryMotion::*ReviewCamLight)(int, int);
	
	//int m_nDirectionIndex;

	int m_nMappingPointIndexX;
	int m_nMappingPointIndexY;

	int m_nMappingPointCntX;
	int m_nMappingPointCntY;
	int m_nMaxMappingPointCntX;
	int m_nMaxMappingPointCntY;

	int m_nMappingCnt;
	int m_nMaxMappingCnt;
	
	int	m_nMappingRepeatCnt;
	int m_nMaxMappingRepeatCnt;
	int	m_nVerificationRepeatCnt;
	int m_nMaxVerificationRepeatCnt;
		
	int m_nResultCnt;

	BOOL m_bCalibDone;


	double m_MappingResultX; 
	double m_MappingResultY;

	DOUBLE dPreVisionResult[2] = { 0.0 }; //KJT 20210315 FMM

	int m_nCameraThreshold;
	
	BOOL m_bStopBit;
	double m_dDist_M10x_R10x_Y;

	

public:
#ifndef SIM_MODE
	CMappingProc	*pMappingProc;
#endif


	//int			nVerification;
	BOOL			InitProcess();
	BOOL			EndProcess();

	HANDLE			hHandle;
	BOOL			m_bTerminate;
	BOOL			IsTerminate() { return m_bTerminate; }

	BOOL			IsFlowDone();
	BOOL			Start();	
	BOOL			Stop();

	CTime m_timeStart; //KJT 20210329
	CTime m_timeStart_1Cycle; //KJT 20210417

	BOOL			FlowInterlock();

	//Data
	INT GetMappingCnt() { return m_nMappingCnt; }
	INT GetMaxMappingCnt() { return m_nMaxMappingCnt; }
	INT GetRepeatCnt() { return (m_nMappingRepeatCnt + m_nVerificationRepeatCnt); }
	INT GetMaxRepeatCnt() { return (m_nMaxMappingRepeatCnt + m_nMaxVerificationRepeatCnt); }
	DOUBLE GetMappingResultX() { return m_MappingResultX; }
	DOUBLE GetMappingResultY() { return m_MappingResultY; }
	BOOL GetVerificationFlag() { return m_nVerification; }

	BOOL IsFlowRun();

#ifndef SIM_MODE
	CWkLibVision	*pCamera;	

	//CCamAreaModul	*pAFM10X;
	//CCamAreaModul	*pAFM20X;
	//CCamAreaModul	*pAFR10X;
#endif

	BOOL m_bIndividualFlag;

	int m_nMappingID;

	int m_AlignCnt;

	double m_dGlassMappingResult[4][2];
	double TargetError;
	int m_inspectCnt;
	double m_dGainX[2];
	double m_dGainL[2];
	double m_dGainR[2];

	double m_dGainLBWD[2][2]; // BWD MOVE
	double m_dGainLFWD[2][2]; // FWD MOVE

	double m_dGainRBWD[2][2];
	double m_dGainRFWD[2][2];

	
	enum TGlassMappingSeq
	{		
		eGLASS_MAPPING_ERROR = -1,
		eGLASS_MAPPING_IDLE = 0,
		eGLASS_MAPPING_START,
		eGLASS_MAPPING_INTERLOCK_CHECK,

#pragma region //Gantry ZX Ready
		eGLASS_MAPPING_GANTRY_ZX_READY,
		eGLASS_MAPPING_GANTRY_ZX_READY_CHECK,
#pragma endregion

#pragma region //Unloader Ready
		eGLASS_MAPPING_UNLOADER_READY,
		eGLASS_MAPPING_UNLOADER_READY_CHECK,
#pragma endregion

#pragma region //Loader Ready
		eGLASS_MAPPING_LOADER_READY,
		eGLASS_MAPPING_LOADER_READY_CHECK,
#pragma endregion

#pragma region //Glass Align
		eGLASS_MAPPING_VERTICAL_ALIGN,
		eGLASS_MAPPING_VERTICAL_ALIGN_CHECK,
		eGLASS_MAPPING_GLASS_ALIGN,
		eGLASS_MAPPING_GLASS_ALIGN_CHECK,
		eGLASS_MAPPING_XYTALIGN_START,
		eGLASS_MAPPING_XYTALIGN_DONE_CHECK,
#pragma	endregion
		eGLASS_MAPPING_START_READY,
		eGLASS_MAPPING_GANTRY_XY_MOVE_MAPPING_POS,
		eGLASS_MAPPING_GANTRY_XY_MAPPING_POS_CHECK,
		//eGLASS_MAPPING_GANTRY_Z1_INSPECTION_POS,
		//eGLASS_MAPPING_GANTRY_Z1_INSPECTION_POS_CHECK,
		eGLASS_MAPPING_GANTRY_Z3_INSPECTION_POS,
		eGLASS_MAPPING_GANTRY_Z3_INSPECTION_POS_CHECK,
		eGLASS_MAPPING_LASER_FOCUS_START,
		eGLASS_MAPPING_LASER_FOCUS_CHECK,
		eGLASS_MAPPING_IMAGE_FOCUS_START,
		eGLASS_MAPPING_IMAGE_FOCUS_CHECK,
		eGLASS_MAPPING_VISION_GRAB,
		eGLASS_MAPPING_VISION_GRAB_CHECK,

		eGLASS_MAPPING_CALC_MAPPING_DATA,

		eGLASS_MAPPING_Z_MOVE_FINISH_UP_POS,
		eGLASS_MAPPING_Z_FINISH_UP_POS_CHECK,
	
		eGLASS_MAPPING_EXIT,

		eGLASS_MAPPING_DONE,
	};
	
	BOOL m_bLaserFocusUseFlag;
	BOOL m_bAutoFocusUseFlag;
	int m_nGrabRetryCnt;

	int m_StickIndex;
	int m_PosCheckFlag;
	double m_GripperZPos;
	double m_PreAlignPoint[4][2];
	double m_AlignPoint[100][2];
	double m_RefPoint[100][2];

	double RefT[2], NewPositionT[2], DiffT[2], DiffPosition[3];
	double AlignError[2];

	double m_dMappingMovePosX;
	double m_dMappingMovePosY;

	double GripperXLPos;
	double GripperXRPos;
	double GripperStrechPos[8];

	CDMPoint m_dCDMPoint;

	double m_dPosX;
	double m_dPosY;
	double m_dPosZ1;

	double m_dRefPosX;
	double m_dRefPosY;
	double m_dRefPosZ;

	BOOL bPassGrab;
};

