#pragma once

#include "BaseMotion.h"
#include "Vision/MappingProc.h"
//#include "../WkLibFlow/WkLibFlow.h"
#include "Flow/BaseFlow.h"
#ifndef MIL_NOT_USE
#include "../WkLibVision/WkLibVision.h"
#endif

#define CAMERA_OFFSET_ERROR_LIMIT	2
#define GANTRY_COM_DELAY		20

class CGantryMotion	: public CBaseMotion, public CBaseFlow
{
public:
	CGantryMotion();
	~CGantryMotion();

private:
	CWinThread*		pMotionThread;
	CWinThread*		pMonitoringThread;
	int				m_nCurStep;
	DWORD			m_dwTimeTick;
	DWORD			m_dwTimeOut;
	BOOL			m_StateFinish;
	void(*m_StateComplete)(void *pArgument);
	BOOL			m_bStopBit;

	VOID			MotionThreadFunctionEntry(VOID);
	static UINT		MotionThreadFunction(LPVOID lpParam);

	double m_dPosZ;
	double m_dLaserPosZ;

	double m_dBackLightWaitPos[2];
	int BackLightYAxis;

	BOOL MoveAxis(enum_Axis eAxis, double dPos);
	BOOL MoveAxis_With_BackLightX(enum_Axis eAxis, double dPos, BOOL bWithMoveBackLightX, double dAOICamOffset = 0.0, BOOL bDirBwd = FALSE, enum_AOI_Vel_Level eAoiVelLevel = eAOI_Vel_50);
	BOOL IsMoveDone(enum_Axis eAxis, double dPos);
public:
#ifndef SIM_MODE
	CMappingProc	*pMappingProc;
#endif

	HANDLE			hMotionHandle;

	void *m_pParentDlg;
	int SetParentDlg(void *pDlg);

	BOOL			InitProcess();
	BOOL			InitParam();
	BOOL			EndProcess();
	BOOL			Stop();

	//Laser Disp Value
	DOUBLE GetLaserDispValue();

	BOOL LaserFocusMove(BOOL bIsGlass = FALSE);
	BOOL LaserFocusMoveCheck();
	BOOL LaserFocusDoneCheck();

	double m_dTargetPos_X;		//Target Pos X
	double m_dTargetPos_Y;		//Target Pos Y
	double m_dTargetPos_Z1;		//Target Pos Z1
	//double m_dTargetPos_Z2;		//Target Pos Z2
	//double m_dTargetPos_Z3;		//Target Pos Z3. 3D Cam

	BOOL m_bApplySwAlignData;	//KJT 20210312
	BOOL m_bApplyGlassMappingData; //KJT 20210425

	BOOL m_bZUp; //KJT 20210807

	BOOL m_bAutoFocusingFlag;
	int CameraZ1ImageFocusMove(double dRelPos);

	BOOL m_bMotionDone;

	BOOL m_bReviewCAMFlag;

#pragma region //PPA
	INT m_nMaxCellCntX;
	INT m_nMaxCellCntY;
	INT m_nMaxPatCntX;
	INT m_nMaxPatCntY;

	INT m_nMaxPpaCnt;

	PPA_POS PPAPos[MAX_CELL_X_COUNT][MAX_CELL_Y_COUNT][MAX_PAT_X_NUM][MAX_PAT_Y_NUM];
	DOUBLE m_dTpX[100];
	DOUBLE m_dTpY[100];
	BOOL MakeNormalPpaPosition(INT nDivX, INT nDivY);
	BOOL MakeIndividualNormalPpaPosition(INT nStickIndex, INT nDivX, INT nDivY);
	BOOL MakeAtPpaPosition(INT nDivX, INT nDivY);
	BOOL MakeIndividualAtPpaPosition(INT nStickIndex, INT nDivX, INT nDivY);
	BOOL ResetPpaData();

	BOOL CheckCamSameValue(double m_AlignVisionPreResultValueX, double m_AlignVisionResultValueX, double m_AlignVisionPreResultValueY, double m_AlignVisionResultValueY);
	BOOL GetPpaMaxMinCenterData(int nCellXNum, double *dPpaX, double *dPpaY);
#pragma endregion

#pragma region //Pos Move
	BOOL	Move_Gantry_X_Pos(double dPos, BOOL bWithMoveBackLightX, double dAOICamOffset = 0.0, BOOL bDirBwd = FALSE, enum_AOI_Vel_Level eAoiVelLevel = eAOI_Vel_50);
	BOOL	Move_Gantry_Y_Pos(double dPos);
	BOOL	Move_Gantry_Z1_Pos(double dPos); 
	//BOOL	Move_Gantry_Z2_Pos(double dPos); 
	//BOOL	Move_Gantry_Z3_Pos(double dPos); 

	BOOL	Is_Gantry_X_Pos(double dPos);
	BOOL	Is_Gantry_Y_Pos(double dPos);
	BOOL	Is_Gantry_Z1_Pos(double dPos); 
	//BOOL	Is_Gantry_Z2_Pos(double dPos); 
	//BOOL	Is_Gantry_Z3_Pos(double dPos);

	BOOL    ConvertTo20XPos(double *dPosX, double *dPosY);

	////XYZ
	//BOOL Move_GantryXYZ(double dPosX, double dPosY, double dPosZ[3], int nBackLightVal = 0);
	BOOL Move_GantryXYZ(double dPosX, double dPosY, double dPosZ[3], BOOL bZUp, int nBackLightVal = 0, BOOL bApplySwAlignData = FALSE, BOOL bApplyGlassMappingData = FALSE); //KJT 20210425
	BOOL Move_GantryXYZ_Review10X(double dPosX, double dPosY, BOOL UpMoveFlag, BOOL MappingFlag = TRUE, BOOL LaserValueFlag = FALSE, BOOL bThetaFlag = FALSE, BOOL SwMappingFlag = FALSE);
	BOOL Is_MoveDone();
#pragma endregion

#pragma region //Gantry X
	BOOL	Move_Gantry_X_Wait_Pos();

	BOOL	Is_Gantry_X_Wait_Pos();								// 겐트리 X축 대기 위치 이동 완료 확인
#pragma endregion

#pragma region //Gantry Y
	BOOL	Move_Gantry_Y_Wait_Pos();
	BOOL	Move_Gantry_Y_StickLoadInBox_Pos();
	BOOL	Move_Gantry_Y_PaperUnload_Pos();
	BOOL	Move_Gantry_Y_StickUnloadToStage_Pos();

	BOOL	Move_Gantry_Y_StickLoadInStage_Pos();
	BOOL	Move_Gantry_Y_StickUnloadToBox_Pos();
	
	//21.02.15 sjc
	BOOL	Move_Gantry_Y_StickLoading_Safe_Pos();
	BOOL	Move_Gantry_Y_StickUnloading_Safe_Pos();

	BOOL	Is_Gantry_Y_Wait_Pos();								// 겐트리 Y축 대기 위치 이동 완료 확인
	BOOL	Is_Gantry_Y_StickLoadInBox_Pos();
	BOOL	Is_Gantry_Y_PaperUnload_Pos();
	BOOL	Is_Gantry_Y_StickUnloadToStage_Pos();

	BOOL	Is_Gantry_Y_StickLoadInStage_Pos();
	BOOL	Is_Gantry_Y_StickUnloadToBox_Pos();

	//21.02.15 sjc
	BOOL	Is_Gantry_Y_StickLoading_Safe_Pos();
	BOOL	Is_Gantry_Y_StickUnloading_Safe_Pos();

#pragma endregion

#pragma region //Gantry Z All Wait
	BOOL	Move_GantryZ_All_Wait_Pos();
	BOOL	Is_GantryZ_All_Wait_Pos();
#pragma endregion

#pragma region //Gantry Z1//AOI
	BOOL	Move_GantryZ1_Pos(double dPos);
	BOOL	Move_GantryZ1_Wait_Pos();
	BOOL	Move_GantryZ1_InspectionAOI_Pos();
	BOOL	Move_GantryZ1_InspectionMappingGlassPos();	
	
	BOOL	Move_GantryZ1_PreAlign_Pos();
	BOOL	Move_GantryZ1_InspectionReview_Pos();
	BOOL	Move_GantryZ1_InspectionMapping_Pos();

	BOOL	Is_Move_GantryZ1_Pos(double dPos);
	BOOL	Is_GantryZ1_Wait_Pos();
	BOOL	Is_GantryZ1_InspectionAOI_Pos();
	BOOL	Is_GantryZ1_InspectionMappingGlassPos();	

	BOOL	Is_GantryZ1_PreAlign_Pos();
	BOOL	Is_GantryZ1_InspectionReview_Pos();
	BOOL    Is_GantryZ1_InspectionMapping_Pos();

#pragma endregion

#pragma region //Gantry Z2//PreAlign & Zoom
	//BOOL	Move_GantryZ2_Pos(double dPos);
	//BOOL	Move_GantryZ2_Wait_Pos();
	//BOOL	Move_GantryZ2_PreAlign_Pos();
	//BOOL	Move_GantryZ2_Inspect_3D_Pos();
	//BOOL	Move_GantryZ2_AOI_Review_Pos();

	//BOOL	Is_Move_GantryZ2_Pos(double dPos);
	//BOOL	Is_GantryZ2_Wait_Pos();
	//BOOL	Is_GantryZ2_PreAlign_Pos();
	//BOOL	Is_GantryZ2_Inspect_3D_Pos();
	//BOOL	Is_GantryZ2_AOI_Review_Pos();

	//BOOL    Set_GantryZ2_Zoom2X();
	//BOOL    Set_GantryZ2_Zoom10X();
	//BOOL    Set_GantryZ2_Zoom20X();

	//BOOL    Is_GantryZ2_Zoom2X();
	//BOOL    Is_GantryZ2_Zoom10X();
	//BOOL    Is_GantryZ2_Zoom20X();

#pragma endregion

#pragma region // Camera Z3//Review10X
	//BOOL	Move_GantryZ3_Pos(double dPos);
	//BOOL	Move_GantryZ3_Wait_Pos();
	//BOOL	Move_GantryZ3_InspectionReview_Pos();
	//BOOL	Move_GantryZ3_InspectionMapping_Pos();

	//BOOL	Is_Move_GantryZ3_Pos(double dPos);
	//BOOL	Is_GantryZ3_Wait_Pos();
	//BOOL	Is_GantryZ3_InspectionReview_Pos();
	//BOOL    Is_GantryZ3_InspectionMapping_Pos();
#pragma endregion


#pragma region //Vision
	BOOL FindVerticalBlob_PreAlign(double *dDiffPosX, double *dDiffPosY);
	BOOL FindVerticalBlob_Review10X(double *dDiffPosX, double *dDiffPosY);
	BOOL FindBlob_TagKey4PAlign_Review10X(double *dDiffPosX, double *dDiffPosY);
	BOOL FindBlob_SwAlign_Review10X(double *dDiffPosX, double *dDiffPosY); //KJT 20210308
	BOOL FindBlob_Edge4PAlign_Review10X(double *dDiffPosX, double *dDiffPosY);
	BOOL FindBlob_FrameMain4PAlign_Review10X(double *dDiffPosX, double *dDiffPosY);

	BOOL FindHoleBlob_2P_PreAlign(double *dDiffPosX, double *dDiffPosY, int nAlignPoint);
	BOOL FindHoleBlob_2P_Review10X(double *dDiffPosX, double *dDiffPosY);
	BOOL FindBlob_Tegkey_Review10X(double *dDiffPosX, double *dDiffPosY); //KJT 20210225
	BOOL FindBlob_TP(double *dDiffPosX, double *dDiffPosY, int nCamNo); //KJT 20210329  //KJT 20210824
	BOOL FindPattern_TP(double *dDiffPosX, double *dDiffPosY, int nCamNo); //KJT 20210824

	BOOL FindBlob_PPA_Review10X(double *dDiffPosX, double *dDiffPosY);

	BOOL RepeatFindCircle(int nCamNo, double dRadius, double *dDiffX, double *dDiffY, double *dScore);
	BOOL RepeatFindBlob(int nCamNo, int nBlackWhite, int nBin, double dSizeX, double dSizeY, double *dDiffX, double *dDiffY);

	BOOL FindCircleCentering(int nCamNo, double dRadius);
	BOOL FindBlobCentering(int nCamNo, int nBlackWhite, int nBin, double dSizeX, double dSizeY);

	double m_dReview10xTargetOffsetXTmp;
	double m_dReview10xTargetOffsetYTmp;
	double *m_dReview10xTargetOffsetX;
	double *m_dReview10xTargetOffsetY;
#pragma endregion

	BOOL CheckGantryXYZMoveInterlock();
	BOOL CheckGantryXYZFlowInterlock(CString StrFlow, int nFlow, int nStartNo);
	BOOL CameraSwap_Review10XCamToPreAlignCam();
	BOOL CameraSwap_PreAlignCamToReview10XCam();
	BOOL CameraSwap_Review10XCamToAOI();
	BOOL CameraSwap_AOIToReview10XCam();
	BOOL CameraSwap_Review10XCamTo3D();
	BOOL CameraSwap_3DToReview10XCam();
	BOOL Move_GantryXYZ_AlignHoleLeft_PreAlign();
	BOOL Move_GantryXYZ_AlignHoleRight_PreAlign();
	BOOL Move_GantryXYZ_AlignHoleLeft_Review10X();
	BOOL Move_GantryXYZ_AlignHoleRight_Review10X();

	//21.03.05 sjc
	BOOL Get_GantryXY_ReviewGlassAlignPos(int idx, double* dPosX, double* dPosY);
	BOOL Move_GantryXY_ReviewGlassAlignPos(int idx, int bWithMoveBackLightX = 0);
	BOOL Is_GantryXY_ReviewGlassAlignPos(int idx);
	enum TGantryMotionSeq
	{
		eGANTRY_MOTION_ERROR = -1,
		eGANTRY_MOTION_IDLE = 0,

#pragma region //Gantry XYZ Move
		eGANTRY_XYZ_MOVE_START,
		eGANTRY_XYZ_MOVE_INTERLOCK_CHECK,
		eGANTRY_Z_MOVE_ALL_WAIT_POS,
		eGANTRY_Z_MOVE_ALL_WAIT_POS_CHECK,
		eGANTRY_XY_MOVE_POS,
		eGANTRY_XY_MOVE_POS_CHECK,
		eGANTRY_Z_MOVE_INSPECTION_POS,
		eGANTRY_Z_MOVE_INSPECTION_POS_CHECK,
#pragma endregion

		
		eGANTRY_MOTION_DONE,
		eGANTRY_MOTION_EXIT
	};

};

