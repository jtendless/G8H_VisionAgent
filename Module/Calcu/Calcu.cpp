// WkLibCalcu.cpp : «ÿ¥Á DLL¿« √ ±‚»≠ ∑Á∆æ¿ª ¡§¿««’¥œ¥Ÿ.
//

#include "stdafx.h"
#include "Calcu.h"

CCalcu::CCalcu()
{

}

CCalcu::~CCalcu()
{

}

BOOL CCalcu::PointCoordinateTransformation(double dPosX, double dPosY, double dBaseX, double dBaseY, double dOffsetX, double dOffsetY, double dDegTheta, double *dRetX, double *dRetY)
{
	double  dCalbX = 0.0, dCalbY = 0.0;
	double dTheta = dDegTheta * RADIAN;

	dCalbX = cos(dTheta)*(dPosX - dBaseX) - sin(dTheta)*(dPosY - dBaseY) + dOffsetX;
	dCalbY = cos(dTheta)*(dPosY - dBaseY) + sin(dTheta)*(dPosX - dBaseX) + dOffsetY;

	//if (fabs(dX - dCalbX) < 2.0 && fabs(dY - dCalbY) < 2.0)
	//{
	//	*dRetX = dCalbX + dBaseX;
	//	*dRetY = dCalbY + dBaseY;

	//	return FALSE;
	//}

	*dRetX = dCalbX + dBaseX;
	*dRetY = dCalbY + dBaseY;

	return TRUE;
}

BOOL CCalcu::CoordinateTransformation(double dX, double dY, double dDegTheta, double *dRetX, double *dRetY)
{
	double  dCalbX = 0.0, dCalbY = 0.0;
	double dTheta = dDegTheta * RADIAN;

	dCalbX = cos(dTheta)*(*dRetX) - sin(dTheta)*(*dRetY) + dX;
	dCalbY = cos(dTheta)*(*dRetY) + sin(dTheta)*(*dRetX) + dY;


	if (fabs(dX - dCalbX) < 2.0 && fabs(dY - dCalbY) < 2.0)
	{
		*dRetX = dCalbX;
		*dRetY = dCalbY;

		return FALSE;
	}

	return TRUE;
}



int CCalcu::CheckWave(double(*dDataArray)[2], int nCount, double dLinearityJudgement)
{

	int DiretionFlag = 0;
	int SecondDiretionFlag = 0;
	int ThirdDiretionFlag = 0;

	for (int i = 0; i < nCount; i++)
	{
		//Î≥ÄÍ≥°Ï†ê ?ïÏù∏
		if (dDataArray[i][1] + (dLinearityJudgement / 2) < dDataArray[i + 1][1])
		{
			if (DiretionFlag == 0)
			{
				DiretionFlag = 1;
			}
			else if (DiretionFlag == -1)
			{
				SecondDiretionFlag = 1;
			}
			else if (DiretionFlag == 1 && SecondDiretionFlag == -1)
			{
				ThirdDiretionFlag = 1;
			}
			else continue;

		}
		else if (dDataArray[i][1] - (dLinearityJudgement / 2) > dDataArray[i + 1][1])
		{
			if (DiretionFlag == 0)
			{
				DiretionFlag = -1;
			}
			else if (DiretionFlag == 1)
			{
				SecondDiretionFlag = -1;
			}
			else if (DiretionFlag == -1 && SecondDiretionFlag == 1)
			{
				ThirdDiretionFlag = -1;
			}
			else continue;
		}

	}

	if (DiretionFlag == 1 && SecondDiretionFlag == 0 && ThirdDiretionFlag == 0)
		return FINE_CHECK_RIGHT_UP;
	else if (DiretionFlag == -1 && SecondDiretionFlag == 0 && ThirdDiretionFlag == 0)
		return FINE_CHECK_LEFT_UP;
	else if (DiretionFlag == 1 && SecondDiretionFlag == -1 && ThirdDiretionFlag == 0)
		return FINE_CHECK_CUP_DOWN;
	else if (DiretionFlag == -1 && SecondDiretionFlag == 1 && ThirdDiretionFlag == 0)
		return FINE_CHECK_CUP_UP;
	else if (DiretionFlag == 1 && SecondDiretionFlag == -1 && ThirdDiretionFlag == 1)
		return FINE_CHECK_S_UP;
	else //if(DiretionFlag == -1 && SecondDiretionFlag == 1 && ThirdDiretionFlag == -1)
		return FINE_CHECK_S_DOWN;

}

double CCalcu::DistanceToPoint(double x1, double y1, double x2, double y2)
{
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

INT CCalcu::GetMaximemIndex(DOUBLE *dArray, INT nArraySize)
{
	return 0;
}

INT CCalcu::Get1dClosestIndex(DOUBLE dBaseX, DOUBLE *dArrayX, INT nArraySize)
{
	INT nBeseIndex = -1;
	DOUBLE dBaseValue = 9999999;
	for (int i = 0; i < nArraySize; i++)
	{
		if (dBaseValue > dArrayX[i])
		{
			dBaseValue = dArrayX[i];
			nBeseIndex = i;
		}
	}

	return nBeseIndex;
}

INT CCalcu::Get2dClosestIndex(DOUBLE dBaseX, DOUBLE dBaseY, DOUBLE *dArrayX, DOUBLE *dArrayY, INT nArraySize)
{
	return 0;
}

int CCalcu::Hex2UnsignedDec(char* CharPoint)
{
	int iBuf[4096];
	memset(iBuf, 0, sizeof(iBuf));
	
	long lResult = 0;

	for (int i = 0; i<strlen(CharPoint); i++)
	{
		if (CharPoint[i] == '0')
			iBuf[i] = 0;
		else if (CharPoint[i] == '1')
			iBuf[i] = 1;
		else if (CharPoint[i] == '2')
			iBuf[i] = 2;
		else if (CharPoint[i] == '3')
			iBuf[i] = 3;
		else if (CharPoint[i] == '4')
			iBuf[i] = 4;
		else if (CharPoint[i] == '5')
			iBuf[i] = 5;
		else if (CharPoint[i] == '6')
			iBuf[i] = 6;
		else if (CharPoint[i] == '7')
			iBuf[i] = 7;
		else if (CharPoint[i] == '8')
			iBuf[i] = 8;
		else if (CharPoint[i] == '9')
			iBuf[i] = 9;
		else if (CharPoint[i] == 'A' || CharPoint[i] == 'a')
			iBuf[i] = 10;
		else if (CharPoint[i] == 'B' || CharPoint[i] == 'b')
			iBuf[i] = 11;
		else if (CharPoint[i] == 'C' || CharPoint[i] == 'c')
			iBuf[i] = 12;
		else if (CharPoint[i] == 'D' || CharPoint[i] == 'd')
			iBuf[i] = 13;
		else if (CharPoint[i] == 'E' || CharPoint[i] == 'e')
			iBuf[i] = 14;
		else if (CharPoint[i] == 'F' || CharPoint[i] == 'f')
			iBuf[i] = 15;

		int temp = strlen(CharPoint) - i - 1;
		lResult += iBuf[i] * pow(16.0, temp);
	}
	
	return lResult;
}

int CCalcu::Hex2SignedDec(char* CharPoint)
{
	int iBuf[256];
	int nTemp = 0;
	char cTemp[16], cResult[16];
	int  nDirection = 0;
	memset(iBuf, 0, sizeof(iBuf));
	memset(cTemp, 0, sizeof(cTemp[16]));

	int nResult = 0;

	for (int i = 0; i<strlen(CharPoint); i++)
	{
		if (CharPoint[i] == '0')
			iBuf[i] = 0;
		else if (CharPoint[i] == '1')
			iBuf[i] = 1;
		else if (CharPoint[i] == '2')
			iBuf[i] = 2;
		else if (CharPoint[i] == '3')
			iBuf[i] = 3;
		else if (CharPoint[i] == '4')
			iBuf[i] = 4;
		else if (CharPoint[i] == '5')
			iBuf[i] = 5;
		else if (CharPoint[i] == '6')
			iBuf[i] = 6;
		else if (CharPoint[i] == '7')
			iBuf[i] = 7;
		else if (CharPoint[i] == '8')
			iBuf[i] = 8;
		else if (CharPoint[i] == '9')
			iBuf[i] = 9;
		else if (CharPoint[i] == 'A' || CharPoint[i] == 'a')
			iBuf[i] = 10;
		else if (CharPoint[i] == 'B' || CharPoint[i] == 'b')
			iBuf[i] = 11;
		else if (CharPoint[i] == 'C' || CharPoint[i] == 'c')
			iBuf[i] = 12;
		else if (CharPoint[i] == 'D' || CharPoint[i] == 'd')
			iBuf[i] = 13;
		else if (CharPoint[i] == 'E' || CharPoint[i] == 'e')
			iBuf[i] = 14;
		else if (CharPoint[i] == 'F' || CharPoint[i] == 'f')
			iBuf[i] = 15;

		nTemp = strlen(CharPoint) - i - 1;
		nResult += iBuf[i] * pow(16.0, nTemp);
	}

	Dec2Bin(nResult, cResult);

	nTemp = Bin2SignedDec(cResult);

	return nTemp;
}

int CCalcu::Dec2Bin(int DecNum, char cResult[16])
{
	int npTemp[16];
	char cTemp[100];
	memset(npTemp, 0, sizeof(npTemp));
	memset(cTemp, 0, sizeof(cTemp));

	int i = 0;
	while (DecNum >= 2)
	{
		npTemp[i] = DecNum % 2;
		i++;
		DecNum = DecNum / 2;

		if (DecNum == 1)
		{
			npTemp[i] = 1;
		}
	}
	if (DecNum == 1)
	{
		npTemp[i] = 1;
	}

	sprintf_s(cTemp, "%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d",
		npTemp[15],
		npTemp[14],
		npTemp[13],
		npTemp[12],
		npTemp[11],
		npTemp[10],
		npTemp[9],
		npTemp[8],
		npTemp[7],
		npTemp[6],
		npTemp[5],
		npTemp[4],
		npTemp[3],
		npTemp[2],
		npTemp[1],
		npTemp[0]
	);

	memcpy(cResult, cTemp, strlen(cTemp));
	
	return atoi(cTemp);
}

int CCalcu::Bin2Dec(char cResult[16])
{
	int ntemp = 0;
	char cTemp[16];
	memset(cTemp, 0, sizeof(cTemp));

	cTemp[0] = cResult[0];	ntemp += atoi(cTemp) * pow(2, 15);
	cTemp[0] = cResult[1];	ntemp += atoi(cTemp) * pow(2, 14);
	cTemp[0] = cResult[2];	ntemp += atoi(cTemp) * pow(2, 13);
	cTemp[0] = cResult[3];	ntemp += atoi(cTemp) * pow(2, 12);
	cTemp[0] = cResult[4];	ntemp += atoi(cTemp) * pow(2, 11);
	cTemp[0] = cResult[5];	ntemp += atoi(cTemp) * pow(2, 10);
	cTemp[0] = cResult[6];	ntemp += atoi(cTemp) * pow(2, 9);
	cTemp[0] = cResult[7];	ntemp += atoi(cTemp) * pow(2, 8);
	cTemp[0] = cResult[8];	ntemp += atoi(cTemp) * pow(2, 7);
	cTemp[0] = cResult[9];	ntemp += atoi(cTemp) * pow(2, 6);
	cTemp[0] = cResult[10];	ntemp += atoi(cTemp) * pow(2, 5);
	cTemp[0] = cResult[11];	ntemp += atoi(cTemp) * pow(2, 4);
	cTemp[0] = cResult[12];	ntemp += atoi(cTemp) * pow(2, 3);
	cTemp[0] = cResult[13];	ntemp += atoi(cTemp) * pow(2, 2);
	cTemp[0] = cResult[14];	ntemp += atoi(cTemp) * pow(2, 1);
	cTemp[0] = cResult[15];	ntemp += atoi(cTemp) * pow(2, 0);

	return ntemp;
}



//æ’¿Ã ≈©∏È 1, //µ⁄∞° ≈©∏È 2 // ∞∞¿∏∏È 0
INT CCalcu::CompareSignedValue(char* strFirst, char* strSecond)
{
	int nCmp1, nCmp2;
	nCmp1 = strlen(strFirst);
	nCmp2 = strlen(strSecond);

	if (nCmp1 > nCmp2)
		return 1;
	else if (nCmp1 < nCmp2)
		return 2;
	else
	{
		for (int i = 0; i < nCmp1; i++)
		{
			if (strFirst[i] < strSecond[i])
				return 1;
			else if(strFirst[i] > strSecond[i])
				return 2;
		}
	}
	return 0;
}

long CCalcu::CaDec2Hex(char* Data1)
{
	long lResult = 0;

	lResult = strtoul(Data1, NULL, 16);

	return lResult;
}

long CCalcu::CaDec2DWord(char* Data1, char* Data2)
{
	char TargetData[9];
	long iResult = 0;

	memset(TargetData, 0, sizeof(TargetData));

	sprintf_s(TargetData, "%04s%04s", Data2, Data1);

	iResult = strtoul(TargetData, NULL, 16);

	return iResult;
}

LONG CCalcu::Unsigned2Signed(WORD wValue)
{
	long lResult = 0;
	char cResult[16];
	memset(cResult, 0, sizeof(cResult));
	Dec2Bin(wValue, cResult);

	lResult = Bin2SignedDec(cResult);

	return lResult;
}

int CCalcu::Bin2SignedDec(char cResult[16])
{
	char cTemp[16];
	int nDirection = 0;
	int nTemp = 0;
	cTemp[0] = cResult[0];
	nDirection = atoi(cTemp);

	if (nDirection == 1)
	{
		nTemp = -pow(2, 15);
		cTemp[0] = cResult[1];		nTemp += atoi(cTemp) * pow(2, 14);
		cTemp[0] = cResult[2];		nTemp += atoi(cTemp) * pow(2, 13);
		cTemp[0] = cResult[3];		nTemp += atoi(cTemp) * pow(2, 12);
		cTemp[0] = cResult[4];		nTemp += atoi(cTemp) * pow(2, 11);
		cTemp[0] = cResult[5];		nTemp += atoi(cTemp) * pow(2, 10);
		cTemp[0] = cResult[6];		nTemp += atoi(cTemp) * pow(2, 9);
		cTemp[0] = cResult[7];		nTemp += atoi(cTemp) * pow(2, 8);
		cTemp[0] = cResult[8];		nTemp += atoi(cTemp) * pow(2, 7);
		cTemp[0] = cResult[9];		nTemp += atoi(cTemp) * pow(2, 6);
		cTemp[0] = cResult[10];	nTemp += atoi(cTemp) * pow(2, 5);
		cTemp[0] = cResult[11];	nTemp += atoi(cTemp) * pow(2, 4);
		cTemp[0] = cResult[12];	nTemp += atoi(cTemp) * pow(2, 3);
		cTemp[0] = cResult[13];	nTemp += atoi(cTemp) * pow(2, 2);
		cTemp[0] = cResult[14];	nTemp += atoi(cTemp) * pow(2, 1);
		cTemp[0] = cResult[15];	nTemp += atoi(cTemp) * pow(2, 0);
	}
	else
	{
		nTemp = 0;
		cTemp[0] = cResult[1];		nTemp += atoi(cTemp) * pow(2, 14);
		cTemp[0] = cResult[2];		nTemp += atoi(cTemp) * pow(2, 13);
		cTemp[0] = cResult[3];		nTemp += atoi(cTemp) * pow(2, 12);
		cTemp[0] = cResult[4];		nTemp += atoi(cTemp) * pow(2, 11);
		cTemp[0] = cResult[5];		nTemp += atoi(cTemp) * pow(2, 10);
		cTemp[0] = cResult[6];		nTemp += atoi(cTemp) * pow(2, 9);
		cTemp[0] = cResult[7];		nTemp += atoi(cTemp) * pow(2, 8);
		cTemp[0] = cResult[8];		nTemp += atoi(cTemp) * pow(2, 7);
		cTemp[0] = cResult[9];		nTemp += atoi(cTemp) * pow(2, 6);
		cTemp[0] = cResult[10];	nTemp += atoi(cTemp) * pow(2, 5);
		cTemp[0] = cResult[11];	nTemp += atoi(cTemp) * pow(2, 4);
		cTemp[0] = cResult[12];	nTemp += atoi(cTemp) * pow(2, 3);
		cTemp[0] = cResult[13];	nTemp += atoi(cTemp) * pow(2, 2);
		cTemp[0] = cResult[14];	nTemp += atoi(cTemp) * pow(2, 1);
		cTemp[0] = cResult[15];	nTemp += atoi(cTemp) * pow(2, 0);
	}

	return nTemp;
}

int CCalcu::Hex2Dec(int nValue)
{
	char cResult[16];
	int nResult = 0;
	memset(cResult, 0, sizeof(cResult));

	sprintf_s(cResult, "%d", nValue);

	nResult = Hex2UnsignedDec(cResult);

	return nResult;
}

char* CCalcu::Dec2Hex(int nValue)
{
	char cResult[16];
	int nResult = 0;
	sprintf_s(cResult, "%X", nValue);
	return cResult;
}

//INT CCalcu::Dec2IntHex(int nValue)
//{
//	char cResult[16];
//	int nResult = 0;
//	sprintf_s(cResult, "%X", nValue);
//
//	return nResult;
//}

//Ref¿« 4¡°¿« X, Y «’¿Ã 0∞° µ«æÓæﬂ «—¥Ÿ.
BOOL CCalcu::GetXYTPosFor4Point(double *dRefPosX, double *dRefPosY, double *dDiffPosX, double *dDiffPosY, double *dResultX, double *dResultY, double *dResultT, double *dErrorX, double *dErrorY)
{
	double RefT[4], NewPositionT[4], DiffT[4], DiffPosition[3] = { 0, };
	//double dError;

	for (int i = 0; i < 4; i++)
	{
		RefT[i] = atan((dRefPosX[i] / dRefPosY[i]));
		NewPositionT[i] = atan((dRefPosX[i] + dDiffPosX[i]) / (dRefPosY[i] + dDiffPosY[i]));
		DiffT[i] = NewPositionT[i] - RefT[i];
		DiffPosition[0] += dDiffPosX[i];
		DiffPosition[1] += dDiffPosY[i];
		DiffPosition[2] += DiffT[i];
	}

	*dResultX = DiffPosition[0] / 4;
	*dResultY = DiffPosition[1] / 4;
	*dResultT = DiffPosition[2] / 4 * (180. / PI);

	*dResultX = -*dResultX;
	*dResultY = -*dResultY;

	//« ø‰Ω√.
	//dError = sqrt(*ResultX  * *ResultX + *ResultY * *ResultY);

	return TRUE;
}

//BOOL CCalcu::GetXYTPosBy2Point(double *dRefPosX, double *dRefPosY, double *dDiffPosX, double *dDiffPosY, double *dResultX, double *dResultY, double *dResultT)
//{
//	//Offset ±∏«œ±‚.
//	double dVisionFindPosRadious = 0;
//	double dVisionFindPosAngle = 0;
//	double dVisionFindNewPosAngle = 0;
//
//	double dBaseSizeX = 0;
//	double dBaseNewSizeX = 0;
//
//	double dBaseSizeY = 0;
//	double dBaseNewSizeY = 0;
//
//	double deltaX = 0;
//	double deltaY = 0;
//
//	double dAverMotorX = 0., dAverMotorY = 0.;
//
//	double dTemp1 = 0.;
//	double dTemp2 = 0.;
//	double dTemp3 = 0.;
//
//	///////////////////////////////////////////////////////////////////////////////////////////////
//
//	double RefT = 0.0, NewPositionT = 0.0, DiffT = 0.0, DiffPosition[3] = { 0.0, };
//	double RefX = (dRefPosX[0] + dRefPosX[1]) / 2;
//	double RefY = (dRefPosY[0] + dRefPosY[1]) / 2;
//	
//	
//
//
//	RefT = atan2((dRefPosY[1] - dRefPosY[0]), (dRefPosX[1] - dRefPosX[0]));
//	dTemp1 = RefT * DEGREE;
//
//	NewPositionT = atan2((dRefPosY[1] + dDiffPosY[1]) - (dRefPosY[0] + dDiffPosY[0])
//		, (dRefPosX[1] + dDiffPosX[1]) - (dRefPosX[0] + dDiffPosX[0]));
//	dTemp1 = NewPositionT * DEGREE;
//	
//
//	for (int i = 0; i < 2; i++)
//	{
//		dAverMotorX += dRefPosX[i];
//		dAverMotorY += dRefPosY[i];
//
//		DiffPosition[0] += dDiffPosX[i];
//		DiffPosition[1] += dDiffPosY[i];
//	}
//	DiffPosition[0] = (DiffPosition[0] / 2.0);
//	DiffPosition[1] = (DiffPosition[1] / 2.0);
//	DiffPosition[2] = NewPositionT - RefT;
//	
//	dAverMotorX /= 2;
//	dAverMotorY /= 2;
//	//*dResultT = DiffPosition[2] * DEGREE;
//	//*dResultX = (DiffPosition[0] / 2.0) + RefY * sin(*dResultT * RADIAN);
//	//*dResultY = (DiffPosition[1] / 2.0) - RefX * cos(*dResultT * RADIAN);
//
//	//Offset ±∏«œ±‚.
//	dVisionFindPosRadious = sqrt((dAverMotorX + DiffPosition[0]) * (dAverMotorX + DiffPosition[0]) + (dAverMotorY + DiffPosition[1]) * (dAverMotorY + DiffPosition[1]));
//	
//	//Angle
//	dTemp3 = DiffPosition[2] * DEGREE;
//	dVisionFindPosAngle = atan2(dAverMotorY + DiffPosition[1], dAverMotorX + DiffPosition[0]);
//	dTemp1 = dVisionFindPosAngle * DEGREE;
//	dVisionFindNewPosAngle = (dVisionFindPosAngle - DiffPosition[2]);
//	dTemp2 = dVisionFindNewPosAngle * DEGREE;
//	
//	dBaseSizeX = dVisionFindPosRadious * cos(dVisionFindPosAngle);
//	dBaseNewSizeX = dVisionFindPosRadious * cos(dVisionFindNewPosAngle);
//
//	dBaseSizeY = dVisionFindPosRadious * sin(dVisionFindPosAngle);
//	dBaseNewSizeY = dVisionFindPosRadious * sin(dVisionFindNewPosAngle);
//	
//	deltaX = dBaseNewSizeX - dBaseSizeX;
//	deltaY = dBaseNewSizeY - dBaseSizeY;
//
//	*dResultT = DiffPosition[2] * DEGREE;
//	*dResultX = DiffPosition[0] + deltaX;
//	*dResultY = DiffPosition[1] + deltaY;
//
//	return TRUE;
//}

BOOL CCalcu::GetXYTPosBy2Point(double *dRefPosX, double *dRefPosY, double *dDiffPosX, double *dDiffPosY, double *dResultX, double *dResultY, double *dResultT)
{
	//Offset ±∏«œ±‚.
	double dVisionFindPosRadious = 0;
	double dVisionBasePosRadious = 0;
	
	double dVisionFindPosAngle = 0;
	double dVisionFindNewPosAngle = 0;

	double dBaseSizeX = 0;
	double dNewSizeX = 0;

	double dBaseSizeY = 0;
	double dNewSizeY = 0;

	double deltaX = 0;
	double deltaY = 0;

	double dAverMotorX = 0., dAverMotorY = 0.;

	double dTemp1 = 0.;
	double dTemp2 = 0.;
	double dTemp3 = 0.;

	///////////////////////////////////////////////////////////////////////////////////////////////

	double RefT = 0.0, NewPositionT = 0.0, DiffT = 0.0, DiffPosition[3] = { 0.0, };
	double RefX = (dRefPosX[0] + dRefPosX[1]) / 2;
	double RefY = (dRefPosY[0] + dRefPosY[1]) / 2;

	DOUBLE dCenterPosX = 0;
	DOUBLE dCenterPosY = 0;


	RefT = atan2((dRefPosY[1] - dRefPosY[0]), (dRefPosX[1] - dRefPosX[0]));
	dTemp1 = RefT * DEGREE;

	NewPositionT = atan2((dRefPosY[1] + dDiffPosY[1]) - (dRefPosY[0] + dDiffPosY[0])
		, (dRefPosX[1] + dDiffPosX[1]) - (dRefPosX[0] + dDiffPosX[0]));
	dTemp3 = NewPositionT * DEGREE;


	for (int i = 0; i < 2; i++)
	{
		dAverMotorX += dRefPosX[i];
		dAverMotorY += dRefPosY[i];

		DiffPosition[0] += dDiffPosX[i];
		DiffPosition[1] += dDiffPosY[i];
	}

	DiffPosition[0] = (DiffPosition[0] / 2.0);
	DiffPosition[1] = (DiffPosition[1] / 2.0);
	DiffPosition[2] = NewPositionT - RefT;

	dTemp1 = RefT * DEGREE;
	dTemp3 = NewPositionT * DEGREE;

	dAverMotorX /= 2;
	dAverMotorY /= 2;
	//*dResultT = DiffPosition[2] * DEGREE;
	//*dResultX = (DiffPosition[0] / 2.0) + RefY * sin(*dResultT * RADIAN);
	//*dResultY = (DiffPosition[1] / 2.0) - RefX * cos(*dResultT * RADIAN);

	//Offset ±∏«œ±‚.
	//dVisionFindPosRadious = sqrt((dAverMotorX + DiffPosition[0]) * (dAverMotorX + DiffPosition[0]) + (dAverMotorY + DiffPosition[1]) * (dAverMotorY + DiffPosition[1]));
	dVisionBasePosRadious = sqrt((dAverMotorX) * (dAverMotorX) + (dAverMotorY) * (dAverMotorY));

	//dBaseSizeX = dVisionBasePosRadious * cos(RefT - 90 * RADIAN);
	//dNewSizeX = dVisionBasePosRadious * cos(NewPositionT - 90 * RADIAN);

	//dBaseSizeY = dVisionBasePosRadious * sin(RefT - 90 * RADIAN);
	//dNewSizeY = dVisionBasePosRadious * sin(NewPositionT - 90 * RADIAN);

	dBaseSizeX = dVisionBasePosRadious * sin(RefT);
	dNewSizeX = dVisionBasePosRadious * sin(NewPositionT);

	dBaseSizeY = dVisionBasePosRadious * cos(RefT);
	dNewSizeY = dVisionBasePosRadious * cos(NewPositionT);

	deltaX = fabs(dNewSizeX - dBaseSizeX);
	deltaY = fabs(dNewSizeY - dBaseSizeY);

	//Ref Pos∏¶ ±‚¡ÿ¿∏∑Œ ∫Ò±≥«œø© ªÛ¥Î¿ßƒ°¿« ªÁ∫–∏È¿ª √£¥¬¥Ÿ.
	dCenterPosX = dAverMotorX + DiffPosition[0];
	dCenterPosY = dAverMotorY + DiffPosition[1];


	if (DiffPosition[2] < 0)
	{
		if (dCenterPosX > 0)
		{
			if (dCenterPosY > 0)
			{
				deltaX *= -1;
				deltaY *= 1;
			}
			else
			{
				deltaX *= 1;
				deltaY *= 1;
			}
		}
		else
		{
			if (dCenterPosY > 0)
			{
				deltaX *= -1;
				deltaY *= -1;
			}
			else
			{
				deltaX *= 1;
				deltaY *= -1;
			}
		}
	}
	else
	{
		if (dCenterPosX > 0)
		{
			if (dCenterPosY > 0)
			{
				deltaX *= 1;
				deltaY *= -1;
			}
			else
			{
				deltaX *= -1;
				deltaY *= -1;
			}
		}
		else
		{
			if (dCenterPosY > 0)
			{
				deltaX *= 1;
				deltaY *= 1;
			}
			else
			{
				deltaX *= -1;
				deltaY *= 1;
			}
		}
	}

	if (dCenterPosX == 0 && dCenterPosY == 0)
	{
		deltaX = 0;
		deltaY = 0;
	}

	*dResultT = DiffPosition[2] * DEGREE;
	*dResultX = DiffPosition[0] + deltaX;
	*dResultY = DiffPosition[1] + deltaY;

	return TRUE;
}

// uvw stage - 4 axes
int CCalcu::XYTToUVW(double dX, double dY, double dT, double dAngle, double dRadius,double *X1, double *X2, double *Y1, double *Y2)
{
	double dY1, dY2, dX1, dX2;
	double dShiftX = 0., dShiftY = 0.;
	
	dShiftX = (cos((dT + 360 - dAngle)*RADIAN) - cos((360 - dAngle)*RADIAN)) * dRadius;
	//dShiftX = (cos((dT + dAngle)*RADIAN) - cos((dAngle)*RADIAN)) * dRadius;
	dShiftY = (sin((dT + dAngle)*RADIAN) - sin((dAngle)*RADIAN)) * dRadius;
	//double dShiftY2 = (sin((dT + dAngle[1])*RADIAN) - sin((dAngle[1])*RADIAN)) * dRadius[1];
	
	//double dShiftX2 = (cos((dT + dAngle[2])*RADIAN) - cos((dAngle[2])*RADIAN)) * dRadius[2];

	//Rotate Direction + Ω√∞Ë π›¥Î πÊ«‚ 
	dX1 = dShiftX;
	dX2 = -dShiftX;
	dY1 = -dShiftY;
	dY2 = dShiftY;

	*X1 = dX1 - dX;
	*X2 = dX2 - dX;
	*Y1 = dY1 - dY;
	*Y2 = dY2 - dY;

	return 0;
}

#include <afxsock.h>
BOOL CCalcu::CheckServerState(CString strIP, int iPortNum, int nWait)
{
	CAsyncSocket Socket;

	Socket.Create(0, SOCK_STREAM, 0);

	fd_set fdset;
	FD_ZERO(&fdset);
	FD_SET(Socket.m_hSocket, &fdset);
	timeval timeOut;
	timeOut.tv_sec = nWait;
	timeOut.tv_usec = 0;

	// connect∏¶ »£√‚«œ±‰ «œ¡ˆ∏∏ CAsync¿Œ ∞¸∞Ë∑Œ ∫Ì∑∞µ«¡ˆ æ ∞Ì ≈Î∞˙

	int ret = Socket.Connect(strIP, iPortNum);


	if (ret == SOCKET_ERROR && WSAGetLastError() != WSAEWOULDBLOCK)

		return FALSE;


	// ø©±‚º≠ 3√ ∞£ ∫Ì∑∞

	if (select(0, NULL, &fdset, NULL, &timeOut) == SOCKET_ERROR)
		return FALSE;


	// 3√  »ƒø° ∫Ì∑∞¿Ã «√∑»¥Ÿ∏È «ˆ¿Á º“ƒœ¿Ã ø≠∑¡ ¿÷¥¬¡ˆ »Æ¿Œ

	if (!FD_ISSET(Socket.m_hSocket, &fdset))
	{
		/// 3√ ∏∏ø° æ»ø≠∏∞ ∞Õ¿Ã∞Ì
		//closesocket(Socket.m_hSocket);
		//Socket.m_hSocket = INVALID_SOCKET;
		return FALSE;
	}

	return TRUE;
}


CString CCalcu::GetExeFilePath()
{
	CString strMsg;
	CString strExePath;
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

	strExePath.Format(_T("%s"), tchPathName);

	return strExePath;
}

BOOL CCalcu::SetTimeOut()
{
	m_ullStart = GetTickCount64();

	return TRUE;
}

BOOL CCalcu::CheckTimeOut(INT nTimeOut)
{
	ULONGLONG ullCurrunt = GetTickCount64();
	DOUBLE ullSpend = ullCurrunt - m_ullStart;

	if (ullSpend > nTimeOut)
		return TRUE;

	return FALSE;
}