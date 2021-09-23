#pragma once

#include "mil.h"

#define MAX_MAPPING_ID_SIZE			2
#define MAX_XYTALIGN_ID_SIZE		20
///////////////////////////////////////////////////////////////////
//MAPPING 
#define MAX_SWMAPPING_POINT_COUNT_X				2
#define MAX_SWMAPPING_POINT_COUNT_Y				2

//#define MAX_GLASSMAPPING_POINT_COUNT_X			300
//#define MAX_GLASSMAPPING_POINT_COUNT_Y			300

#define MAX_GLASS_MAPPING_COUNT	10000
#define MAX_GLASS_MAPPING_DATA_COUNT	MAX_GLASS_MAPPING_COUNT * 6

//// PPA
//#define PPA_IMAGE_X			2448
//#define PPA_IMAGE_Y			2048
//#define AOI_IMAGE_X			12000
//#define AOI_IMAGE_Y			1000//1024
//
//// PPA Align mm/pixel cal
//#define PPA_ALIGN_PIXEL2MM_X	0.00223214	// 1 mm = 448 pixel
//#define PPA_ALIGN_PIXEL2MM_Y	0.00224215	// 1 mm = 446 pixel
//#define PPA_ALIGN_MARGIN_X	0.05		// PPA Align 시 UVW 허용 오차(mm)
//#define PPA_ALIGN_MARGIN_Y	0.05		// PPA Align 시 UVW 허용 오차(mm)
//#define PPA_ALIGN_MARGIN_T	0.005		// PPA Align 시 UVW 허용 오차(도)
//#define PPA_ALIGN_MAX_CNT		5			// 최대 align 횟수
//
//// PPA x10 mm/pixel cal
//#define PPA_X10_PIXEL2MM_X	0.00034415	// 1 mm = 2905.7 pixel
//#define PPA_X10_PIXEL2MM_Y	0.00034458	// 1 mm = 2902.1 pixel
//#define PPA_X10_MARGIN_X		0.05		// PPA Align 시 UVW 허용 오차(mm)
//#define PPA_X10_MARGIN_Y		0.05		// PPA Align 시 UVW 허용 오차(mm)
//#define PPA_X10_MARGIN_T		0.005		// PPA Align 시 UVW 허용 오차(도)
//#define PPA_X10_MAX_CNT		5			// 최대 align 횟수


struct SW_MAPPING_POS_1POINT {
	SW_MAPPING_POS_1POINT() {
		dX = 0.0;
		dY = 0.0;
	}
	double dX;
	double dY;
};

struct SW_MAPPING_POS_4POINT {
	SW_MAPPING_POS_4POINT() {
		dX1 = 0.0;
		dY1 = 0.0;
		dX2 = 0.0;
		dY2 = 0.0;
		dX3 = 0.0;
		dY3 = 0.0;
		dX4 = 0.0;
		dY4 = 0.0;
	}
	double dX1;
	double dY1;
	double dX2;
	double dY2;
	double dX3;
	double dY3;
	double dX4;
	double dY4;
};

struct SW_MAPPING_POS_4POINT_ABS {
	SW_MAPPING_POS_4POINT_ABS() {
		X1 = 0.0;
		Y1 = 0.0;
		X2 = 0.0;
		Y2 = 0.0;
		X3 = 0.0;
		Y3 = 0.0;
		X4 = 0.0;
		Y4 = 0.0;
	}
	double X1;
	double Y1;
	double X2;
	double Y2;
	double X3;
	double Y3;
	double X4;
	double Y4;
};


struct XYT_ALIGN_DATA {
	XYT_ALIGN_DATA() {
		dOriginX = 0.0;
		dOriginY = 0.0;
		dRotAngle = 0.0;
	}
	double dOriginX;
	double dOriginY;
	double dRotAngle;
};

typedef struct CDMPoint
{
public:
	double x, y, t, z;

public:
	CDMPoint(void)
	{
		x = y = t = z = 0.0;
	}

}CDMPoint;


typedef struct CGlassMark
{
	CDMPoint dFindMark;

	CGlassMark()
	{
		dFindMark.x = 0.0;
		dFindMark.y = 0.0;
	}
}CGlassMark;


//////////////////////////////////////////////////////////////////////////
//***** SW Mapping 사용법 *****
//////////////////////////////////////////////////////////////////////////

//1. SW Mapping을 초기화 한다.
//////////////////////////////////////////////////////////////////////////
//pImageProc->ReleaseSWMapping();

//2. 4 Point 데이터를 가져온다
//////////////////////////////////////////////////////////////////////////
//int i;
//double dPosX, dPosY;
//double dMotorXY[4][2] = { 0.0 };
//double dPixelXY[4][2] = { 0.0 };
//

////Motor(Target Pos)
//dMotorXY[0][0] = pMappingProc->m_SWMapping4_Target.X1;
//dMotorXY[0][1] = pMappingProc->m_SWMapping4_Target.Y1;
//
//dMotorXY[1][0] = pMappingProc->m_SWMapping4_Target.X2;
//dMotorXY[1][1] = pMappingProc->m_SWMapping4_Target.Y2;
//
//dMotorXY[2][0] = pMappingProc->m_SWMapping4_Target.X4;
//dMotorXY[2][1] = pMappingProc->m_SWMapping4_Target.Y4;
//
//dMotorXY[3][0] = pMappingProc->m_SWMapping4_Target.X3;
//dMotorXY[3][1] = pMappingProc->m_SWMapping4_Target.Y3;
//
//
////Pixel(Real Pos)
//dPixelXY[0][0] = pMappingProc->m_SWMapping4_Actual.dX1;
//dPixelXY[0][1] = pMappingProc->m_SWMapping4_Actual.dY1;
//
//dPixelXY[1][0] = pMappingProc->m_SWMapping4_Actual.dX2;
//dPixelXY[1][1] = pMappingProc->m_SWMapping4_Actual.dY2;

//dPixelXY[2][0] = pMappingProc->m_SWMapping4_Actual.dX4;
//dPixelXY[2][1] = pMappingProc->m_SWMapping4_Actual.dY4;
//
//dPixelXY[3][0] = pMappingProc->m_SWMapping4_Actual.dX3;
//dPixelXY[3][1] = pMappingProc->m_SWMapping4_Actual.dY3;

//3. Mapping Data를 만든다.
//////////////////////////////////////////////////////////////////////////
//pMappingProc->CalibSWMapping_MainBegin();
//
//for (i = 0; i < 4; i++)
//{
//	pMappingProc->CalibSWMapping_MainSetData(i, dPixelXY[i][0], dPixelXY[i][1], dMotorXY[i][0], dMotorXY[i][1]);
//}
//
//pMappingProc->CalibSWMapping_MainEnd();


//4. 보정된 데이터를 가져온다
//////////////////////////////////////////////////////////////////////////
//pMappingProc->GetSWMapping_CalibPosXY(&dPosX, &dPosY);

class CMappingProc
{
public:
	CMappingProc();
	virtual ~CMappingProc();
	
	static CMappingProc* instance;
	static CMappingProc* Create();
	static void Delete();
	static CMappingProc* GetInstance();

#ifndef SIM_MODE
	MIL_ID	m_MilSWMapping[MAX_MAPPING_ID_SIZE];
#endif
	double	m_dSWMappingResX[MAX_MAPPING_ID_SIZE];
	double	m_dSWMappingResY[MAX_MAPPING_ID_SIZE];
	double	m_dInitSWMappingResX[MAX_MAPPING_ID_SIZE];
	double	m_dInitSWMappingResY[MAX_MAPPING_ID_SIZE];

#ifndef SIM_MODE
	MIL_ID	m_MilGlassMapping[MAX_MAPPING_ID_SIZE];
#endif
	double	m_dGlassMappingResX[MAX_MAPPING_ID_SIZE];
	double	m_dGlassMappingResY[MAX_MAPPING_ID_SIZE];
	double	m_dInitGlassMappingResX[MAX_MAPPING_ID_SIZE];
	double	m_dInitGlassMappingResY[MAX_MAPPING_ID_SIZE];

	int		m_nSWMappingCount;
	int		m_nGlassMappingCount;

	CFile	m_hSWMappingCSVFile[MAX_MAPPING_ID_SIZE];
	CFile	m_hGlassMappingCSVFile[MAX_MAPPING_ID_SIZE];

	CString m_StrLogPath;
	CString m_StrSWMappingCALFilePath[MAX_MAPPING_ID_SIZE];
	CString m_StrSWMappingCSVFilePath[MAX_MAPPING_ID_SIZE];
	CString m_StrGlassMappingCALFilePath[MAX_MAPPING_ID_SIZE];	
	CString m_StrGlassMappingCSVFilePath[MAX_MAPPING_ID_SIZE];

	CDMPoint m_dGlassMappingPoint[MAX_GLASS_MAPPING_COUNT];
	double	m_dGlassMappingMotorX[MAX_GLASS_MAPPING_COUNT];
	double	m_dGlassMappingMotorY[MAX_GLASS_MAPPING_COUNT];
	double	m_dGlassMappingPixelX[MAX_GLASS_MAPPING_COUNT];
	double	m_dGlassMappingPixelY[MAX_GLASS_MAPPING_COUNT];

	CDMPoint m_dSWMappingPoint[MAX_SWMAPPING_POINT_COUNT_X*MAX_SWMAPPING_POINT_COUNT_Y];
	double	m_dSWMappingMotorX[MAX_SWMAPPING_POINT_COUNT_X*MAX_SWMAPPING_POINT_COUNT_Y];
	double	m_dSWMappingMotorY[MAX_SWMAPPING_POINT_COUNT_X*MAX_SWMAPPING_POINT_COUNT_Y];
	double	m_dSWMappingPixelX[MAX_SWMAPPING_POINT_COUNT_X*MAX_SWMAPPING_POINT_COUNT_Y];
	double	m_dSWMappingPixelY[MAX_SWMAPPING_POINT_COUNT_X*MAX_SWMAPPING_POINT_COUNT_Y];

	void GetStandardDeviation(double *dX, double *dY, int nCnt, double *dResultX, double *dResultY);

	int InitializeSWMapping(int nMappingID = -1);
	int InitializeGlassMapping(int nMappingID = -1);

	int ReleaseSWMapping(int nMappingID = -1);
	int ReleaseGlassMapping(int nMappingID = -1);

	int ReleaseSWMappingCSVFile(int nMappingID = -1);
	int ReleaseGlassMappingCSVFile(int nMappingID = -1);

	int SaveSWMappingFile(int nMappingID = -1);
	int SaveGlassMappingFile(int nMappingID = -1);	

	//Mapping시 마다 매번 저장하기 위해.
	int SaveBackUpMappingFile(int nMappingID);

	int LoadSWMappingFile(int nMappingID = -1);
	int LoadGlassMappingFile(int nMappingID = -1);
	int GetFindFile(CString szFile);

	BOOL SaveSWMappingCSV(CString szFilePath, BOOL bAdd);
	BOOL SaveGlassMappingCSV(int nMappingID,CString szFilePath, BOOL bAdd);
	BOOL LoadSWMappingCSV(int nMappingID, CString szFilePath, int &nReadCount);
	BOOL LoadGlassMappingCSV(int nMappingID, CString szFilePath, int &nReadCount);
	BOOL SaveSWMappingCSVEx(int nMappingID, CFile *pFile, CString szText, BOOL bOverWrite = FALSE);
	BOOL SaveGlassMappingCSVEx(int nMappingID, CFile *pFile, CString szText, BOOL bOverWrite = FALSE);

	int GetSWMapping_CalibPosXY(int nMappingID, double *dPosX, double *dPosY);
	int GetGlassMapping_CalibPosXY(int nMappingID, double *dPosX, double *dPosY);

	int GetSWMapping_PixelToWorld(int nMappingID, double& x, double& y);
	int GetGlassMapping_PixelToWorld(int nMappingID, double& x, double& y);

	int GetSWMapping_WorldToPixel(int nMappingID, double& x, double& y);
	int GetGlassMapping_WorldToPixel(int nMappingID, double& x, double& y);

	int Calculate_SWMapping(int nMappingID, int nCount, double* dMotorX, double* dMotorY, double* dPixelX, double* dPixelY, double dOrgX, double dOrgY, BOOL bRelativeOrign);
	int Calculate_GlassMapping(int nMappingID, int nCount, double* dMotorX, double* dMotorY, double* dPixelX, double* dPixelY, double dOrgX, double dOrgY, BOOL bRelativeOrign);

	int CloseSWMapping_CalibData(int nMappingID, double dOrgCx, double dOrgCy);
	int CloseGlassMapping_CalibData(int nMappingID, double dOrgCx, double dOrgCy);

	//측정 Position 별 MOTOR 위치 반환
	//인자1	: POINT-X Number(0~n)
	//인자2	: POINT-Y Number(0~n)
	//반환	: 실제 MOTOR 위치
	CDMPoint GetSWMapping_Num2MotorPos(int nMappingID, int nX, int nY);
	CDMPoint GetGlassMapping_Num2MotorPos(int nMappingID, int nX, int nY);

	int SetSWMapping_RelativeOrigin(int nMappingID, double dOffsetX, double dOffsetY, double dOffsetZ, double dAngle);
	int SetGlassMapping_RelativeOrigin(int nMappingID, double dOffsetX, double dOffsetY, double dOffsetZ, double dAngle);
	
	int SetSWMapping_RelativeAngleOrigin(int nMappingID, double dAngle);
	int SetGlassMapping_RelativeAngleOrigin(int nMappingID, double dAngle);

	int MakeSWMapping_CalibPoint(int nMappingID);
	int MakeGlassMapping_CalibPoint(int nMappingID);

	//int CalibSWMapping_Main(int nRepeatCount);
	int CalibSWMapping_MainBegin(int nMappingID);
	int CalibSWMapping_MainSetData(int nMappingID, int nCount, double dPixelX, double dPixelY, double dMotorX, double dMotorY);
	int CalibSWMapping_MainEnd(int nMappingID);

	//int CalibGlassMapping_Main(int nMappingID, int nRepeatCount);
	int CalibGlassMapping_MainBegin(int nMappingID, int nCount, int nVerification = 0);
	int CalibGlassMapping_MainGetData(int nMappingID, double dRealX, double dRealY, double dDiffX, double dDiffY, double dScore, double dScale, int nVerification = 0);
	int CalibGlassMapping_MainEnd(int nMappingID, int nVerification = 0);

	//int CalibSWMappingExec(int nCountX, int nCountY);
	//int CalibGlassMappingExec(int nMappingID, int nCountX, int nCountY);

	void SetSWMapping_CalibData(int nMappingID, int nCount, double dPixelX, double dPixelY, double dMotorX, double dMotorY);
	void SetGlassMapping_CalibData(int nMappingID, int nCount, double dPixelX, double dPixelY, double dMotorX, double dMotorY);

	//Dual FMM 1번만 사용.
	XYT_ALIGN_DATA m_XYTAlignData[MAX_XYTALIGN_ID_SIZE];

	int ReleaseXYTAlignData(int nMappingID = -1);
	int GetXYTAlign_CalibPosXY(int nMappingID, double *dPosX, double *dPosY);
	void Make2PointAlignData(int nMappingID, int nNo, double dRefLeftXY[2], double dRefRightXY[2], double dObjLeftXY[2], double dObjRightXY[2], double *dX, double *dY, double *dT);
	void MakeXYTAlignData(int nMappingID, double dCmdPointXY[4][2], double dActPointXY[4][2]);
	void Make2PointVertiXYTAlignData(int nMappingID, double dCmdPointXY[2][2], double dActPointXY[2][2]);

	void Make2PointHoriXYTAlignData(int nMappingID, double dCmdPointXY[2][2], double dActPointXY[2][2]);


	int UnicodeToMultiByte(TCHAR *pSrc, CHAR *pDest, INT nLength = MAX_PATH);
	

	//Offset 가져오기.
	BOOL Get2PointSwAlignOffsetY(int nMappingID, double dBasePointX, double dOffsetPointX, double dPointY, double *dOffsetY);
	BOOL Get2PointMappingOffsetY(int nMappingID, double dPointX1, double dPointX2, double dPointY, double *dOffsetY);
	BOOL Get2PointXytAlignOffsetY(int nMappingID, double dPointX1, double dPointX2, double dPointY, double *dOffsetY);
	// S/W allign image mapping armadillo
	//SW_MAPPING_POS_1POINT SolveAxb(double dAX, double dAY, double* dRX, double* dRY);
	//SW_MAPPING_POS_1POINT m_SWMapping1;	
	//SW_MAPPING_POS_4POINT m_SWMapping4_Mapped;	// 4 측정 point 별 중심에서 벗어난 정도(mm)

	SW_MAPPING_POS_4POINT m_SWMapping4_Target;		// 측정 point (mm)
	SW_MAPPING_POS_4POINT_ABS m_SWMapping4_Actual;	// 측정 point 실제 좌표(mm)

	////////////////////////////////////////////////////////////////////////////////////
	int Init();
};

