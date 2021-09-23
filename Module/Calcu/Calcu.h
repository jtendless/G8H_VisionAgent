#ifndef CALCU
#define CALCU

enum
{
	FINE_CHECK_RIGHT_UP = 1,
	FINE_CHECK_LEFT_UP,
	FINE_CHECK_CUP_UP,
	FINE_CHECK_CUP_DOWN,
	FINE_CHECK_S_UP,
	FINE_CHECK_S_DOWN,
	FINE_CHECK_MAX,

};

#define PI				3.14159265358979323846264338
#define RADIAN			(PI / 180.0)
#define DEGREE			(180.0 / PI)

class CCalcu
{
public:
	CCalcu();
	~CCalcu();

	BOOL CoordinateTransformation(double dX, double dY, double dDegTheta, double *dRetX, double *dRetY);
	BOOL PointCoordinateTransformation(double dPosX, double dPosY, double dBaseX, double dBaseY, double dOffsetX, double dOffsetY, double dDegTheta, double *dRetX, double *dRetY);
	int CheckWave(double(*dDataArray)[2], int nCount, double dLinearityJudgement);

	//16진수 -> 10진수
	int Hex2iDec(char* CharPoint);
	int Hex2UnsignedDec(char* CharPoint);
	int Hex2SignedDec(char* CharPoint);

	int Hex2Dec(int nValue);

	char* Dec2Hex(int nValue);

	//INT Dec2IntHex(int nValue);

	//10진수 -> 2진수 변환.
	int Dec2Bin(int DecNum, char cResult[16]);

	//Bin2Dec
	//2진수 -> 16진수
	int Bin2Dec(char cResult[16]);
	//2진수 -> 10진수
	int Bin2SignedDec(char cResult[16]);

	//char array에서 변환.
	long CaDec2Hex(char *Data1);
	long CaDec2DWord(char* Data1, char* Data2);
	
	LONG Unsigned2Signed(WORD wValue);

	//두수 크기 비교.
	INT CompareSignedValue(char* strFirst, char* strSecond);

	//거리 계산.
	double DistanceToPoint(double x1, double y1, double x2, double y2);

	//Base 계산.
	INT GetMaximemIndex(DOUBLE *dArray, INT nArraySize);
	INT GetMinimumIndex(DOUBLE *dArray, INT nArraySize);
	
	INT Get1dClosestIndex(DOUBLE dBaseX, DOUBLE *dArrayX, INT nArraySize);
	INT Get2dClosestIndex(DOUBLE dBaseX, DOUBLE dBaseY, DOUBLE *dArrayX, DOUBLE *dArrayY, INT nArraySize);

	BOOL GetXYTPosFor4Point(double *dRefPosX, double *dRefPosY, double *dDiffPosX, double *dDiffPosY, double *dResultX, double *dResultY, double *dResultT, double *dErrorX, double *dErrorY);
	BOOL GetXYTPosBy2Point(double * dRefPosX, double * dRefPosY, double * dDiffPosX, double * dDiffPosY, double * dResultX, double * dResultY, double * dResultT);
	
	//--|||					Y1						
	//	X1

	//						--|||
	//    Y2					X2
	int XYTToUVW(double dX, double dY, double dT, double dAngle, double dRadius, double *X1, double *X2, double *Y1, double *Y2);

	BOOL CheckServerState(CString strIP, int iPortNum, int nWait);
	CString GetExeFilePath();

	//Time Out///////////////////////////////////////////////
	BOOL SetTimeOut();
	BOOL CheckTimeOut(INT nTimeOut);

	ULONGLONG m_ullStart;
	////////////////////////////////////////////////////////////
};
#endif