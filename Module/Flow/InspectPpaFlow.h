/******************************************************************************
 * @file     InspectPpaFlow.h
 * @date     2017.6.01.12
 * @history
 *
 ******************************************************************************/
#pragma once

#include "Common/CommonDefine.h"

typedef enum
{
	eNORAML_PPA,
	eAT_PPA,
}enum_PPA_Type;

class CInspectPpaFlow : public CBaseFlow
{
private:

public:
	CInspectPpaFlow();
	virtual ~CInspectPpaFlow();

private:
#ifndef SIM_MODE
	wk_MilCameraInfo m_CameraInfo;
	wk_MilBlobData m_BlobData;
	stBlobResult stResult;
#endif

	INT m_nKindOfPpaIndex;
	//BOOL m_bAllPpaFlag;
	INT m_nAllPpaMaskCnt;

	CWinThread*		pThread;
	VOID			ThreadFunctionEntry(VOID);
	static UINT		ThreadFunction(LPVOID lpParam);
	BOOL			m_StateFinish;
	void(*m_StateComplete)(void *pArgument);

	CString m_path, m_logpath;
	//CString m_strDfsFileName; //Temp

	int		m_nGrabRetryCnt;

	BOOL m_bMotionDone; 
	BOOL m_bStopBit;
	double m_dDist_M10x_R10x_Y;
	//CMappingProc	*pMappingProc;

public:
	BOOL			InitProcess();
	BOOL			EndProcess();

	HANDLE			hHandle;
	BOOL			m_bTerminate;
	BOOL			IsTerminate() { return m_bTerminate; }
	BOOL			IsFlowDone() { return m_bMotionDone; }

	BOOL			MotionDone();
	BOOL			Start(enum_PPA_Type PPAIndex, int nStep, int nRepeat = 0);
	BOOL			Stop();

	CTime m_timeStart; //KJT 20210329

	BOOL			FlowInterlock();
	
	//int *m_pReviewCoaxial;
	//int *m_pReviewRing;
	//int *m_pReviewThreshold;
	//int *m_pReviewMarkFind;

	int m_DelayCnt;

public:
	INT m_nMaxPpaCount;
	INT m_nPpaIndex;
	int m_nRepeatCount;
	int m_nCurRepeatCount;

	int m_nCellIndexX;
	int m_nCellIndexY;
	int m_nPatIndexX;
	int m_nPatIndexY;

	//UINT m_nInspectPpaNo;	// PPA 측정 횟수, GetInspectPpaStartNo 에서 가져옴
	//UINT m_nColTextCnt;
	//UINT m_nRowTextCnt;
	//UINT m_nInspectStickNo;
	//UINT m_nInspectCellColNo;
	//UINT m_nInspectCellRowNo;

	//UINT m_nInspectCellColCnt;
	//UINT m_nInspectCellRowCnt;
	
	PPA_POS PPAPos;
	ERROR_INFO ErrorINfo;

	int m_TotalSlotCntX;
	int m_TotalSlotCntY;

	INT m_nResultIndex;
	double m_PpaResult[100][2];

	enum_CassetteFloor m_eTargetFloor;
	//enum_CassetteSlot m_eTargetSlot;

	double m_dPosZ_FirstPoint;

	enum TInspectPpaSeq
	{
		_eINSPECT_PPA_FLOW_ERROR = -1,

		_eINSPECT_PPA_FLOW_IDLE = 0,
		_eINSPECT_PPA_FLOW_START,
		_eINSPECT_PPA_FLOW_INTERLOCK,

#pragma region //Unloader Ready
		_eINSPECT_PPA_FLOW_UNLOADER_READY,
		_eINSPECT_PPA_FLOW_UNLOADER_READY_CHECK,
#pragma endregion

#pragma region //Gantry ZX Ready
		_eINSPECT_PPA_FLOW_GANTRY_ZX_READY,
		_eINSPECT_PPA_FLOW_GANTRY_ZX_READY_CHECK,
#pragma endregion

#pragma region //Loader Ready
		_eINSPECT_PPA_FLOW_LOADER_READY,
		_eINSPECT_PPA_FLOW_LOADER_READY_CHECK,
#pragma endregion

#pragma region //PaperUnloader Ready
		_eINSPECT_PPA_FLOW_PAPER_UNLOADER_ZXY_READY,
		_eINSPECT_PPA_FLOW_PAPER_UNLOADER_ZXY_READY_CHECK,
#pragma endregion

		_eINSPECT_PPA_FLOW_SW_ALIGN_START,
		_eINSPECT_PPA_FLOW_SW_ALIGN_DONE_CHECK,

		_eINSPECT_PPA_FLOW_PPA_POS_CALC,
		_eINSPECT_PPA_FLOW_GANTRY_XY_ALIGN_POS_1ST,
		_eINSPECT_PPA_FLOW_GANTRY_XY_ALIGN_POS_1ST_CHECK,
		//_eINSPECT_PPA_FLOW_GANTRY_Z1_INSPECTION_POS_1ST,
		//_eINSPECT_PPA_FLOW_GANTRY_Z1_INSPECTION_POS_1ST_CHECK,
		//_eINSPECT_PPA_FLOW_GANTRY_Z3_INSPECTION_POS_1ST,
		//_eINSPECT_PPA_FLOW_GANTRY_Z3_INSPECTION_POS_1ST_CHECK,

		//_eINSPECT_PPA_FLOW_GANTRY_Z1_INSPECTION_POS_2ND,
		//_eINSPECT_PPA_FLOW_GANTRY_Z1_INSPECTION_POS_2ND_CHECK,
		_eINSPECT_PPA_FLOW_GANTRY_XY_ALIGN_POS_2ND,
		_eINSPECT_PPA_FLOW_GANTRY_XY_ALIGN_POS_2ND_CHECK,
		_eINSPECT_PPA_FLOW_AUTOFOCUS_CHECK,
		_eINSPECT_PPA_FLOW_LASER_FOCUS_START,
		_eINSPECT_PPA_FLOW_LASER_FOCUS_CHECK,
		_eINSPECT_PPA_FLOW_IMAGE_FOCUS_START,
		_eINSPECT_PPA_FLOW_IMAGE_FOCUS_CHECK,
		_eINSPECT_PPA_FLOW_GRAB_START,
		_eINSPECT_PPA_FLOW_GRAB_DONE_CHECK,
			
		//_eINSPECT_PPA_FLOW_FINISH_GANTRY_Z1_WAIT_POS,
		//_eINSPECT_PPA_FLOW_FINISH_GANTRY_Z1_WAIT_POS_CHECK,
		_eINSPECT_PPA_FLOW_FINISH_GANTRY_Z3_WAIT_POS,
		_eINSPECT_PPA_FLOW_FINISH_GANTRY_Z3_WAIT_POS_CHECK,
		_eINSPECT_PPA_FLOW_FINISH_GANTRY_XY_WAIT_POS,
		_eINSPECT_PPA_FLOW_FINISH_GANTRY_XY_WAIT_POS_CHECK,

		_eINSPECT_PPA_FLOW_DONE,

	};

	double m_dTargetPosX;
	double m_dTargetPosY;

	double m_dMappingMovePosX;
	double m_dMappingMovePosY;

	// PPA측정 전에 Mask 자세 확인 후 측정 위치 보정
	double m_AlignPointValue[2]; // Align 포인트 저장 최대 4개 - parkcm
	double m_AlignVisionResultPpaValue[2];
	double m_AlignVisionResultCdValue[2];
	double m_ResultIndividual_CdX[MAX_PPA_NUM]; //KJT 20210524
	double m_ResultIndividual_CdY[MAX_PPA_NUM]; //KJT 20210524
	double m_AlignVisionResultCornerRValue[25][4];

	double m_AlignTotalVisionStartResultValue[10][2];
	double m_AlignTotalVisionEndResultValue[10][2];

	double m_Align10XPointValue[10][2]; // Align 포인트 저장 최대 4개 - parkcm
	double m_Align10XVisionResultValue[10][2];
	double m_Align10XTotalVisionStartResultValue[10][2];
	double m_Align10XTotalVisionEndResultValue[10][2];

	double m_AlignVisionPreResultValue[2];

	int m_AlignCnt;
	int m_CurrentRetryCnt;
	int m_TotalRetryCnt;
	int m_AF_RetryCnt;
	int m_nCurrentStickIndex;

	double m_LDS_Value[10];

	double m_dCmdPosZ;
	BOOL m_bDirectionFlag;

public:
	int SavePpaResult(ERROR_INFO resinfo);
	int CopyToDispData(int nIndex, ERROR_INFO resinfo);
	BOOL SetPPAJudgeResult();

	DOUBLE m_dPpaResult[1000][2];
	DOUBLE m_dCdResult[1000][2];
	double m_dCornerRResult[1000][25][4];

	BOOL TpCheck(INT nMaxCnt);
	BOOL CdCheck(INT nMaxCnt);
	BOOL PpaCheck(INT nMaxCnt);

	FILE* m_fp;

};