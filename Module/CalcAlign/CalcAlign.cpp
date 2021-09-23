#include "stdafx.h"
#include "CalcAlign.h"
#include "Common/CommonDefine.h"

CCalcAlign::CCalcAlign()
{
}


CCalcAlign::~CCalcAlign()
{
	//m_ptOrg.clear();
	//m_ptFid.clear();
}


void CCalcAlign::clearAlignPoint()
{
	m_ptOrg.clear();
	m_ptFid.clear();
	m_ptCenter = _2POINT(0 , 0);
}


void CCalcAlign::setAlignPoint(_2POINT ptOrg1, _2POINT ptOrg2, _2POINT ptFid1, _2POINT ptFid2)
{
	if ((int)m_ptOrg.size() == 4)	return;

	m_ptOrg.push_back(ptOrg1 - m_ptCenter);
	m_ptOrg.push_back(ptOrg2 - m_ptCenter);

	m_ptFid.push_back(ptFid1 - m_ptCenter);
	m_ptFid.push_back(ptFid2 - m_ptCenter);

	if ((int)m_ptOrg.size() == 2)		get2AlignResult();
	else if ((int)m_ptOrg.size() == 4)	get4AlignResult();
}


_2POINT CCalcAlign::getAlignResult(_2POINT pt)
{
	_2POINT		ptBase;
	_2POINT		ptResult;

	ptBase = pt - m_ptRefOrg;

	ptResult.dx = ptBase.dx * cos(m_TMatrix.dt) - ptBase.dy * sin(m_TMatrix.dt) + m_ptRefFid.dx;
	ptResult.dy = ptBase.dx * sin(m_TMatrix.dt) + ptBase.dy * cos(m_TMatrix.dt) + m_ptRefFid.dy;


	return ptResult;

}

_3POINT CCalcAlign::getAlignResultXYT()
{
	_3POINT ptResult;

	ptResult.dx = m_ptRefFid.dx - m_ptRefOrg.dx * cos(m_TMatrix.dt) + m_ptRefOrg.dy * sin(m_TMatrix.dt);
	ptResult.dy = m_ptRefFid.dy - m_ptRefOrg.dx * sin(m_TMatrix.dt) - m_ptRefOrg.dy * cos(m_TMatrix.dt);

	ptResult.dt = m_TMatrix.dt;

	return ptResult;
}

bool CCalcAlign::get2AlignResult()
{
	bool bResult = true;
	
	_2POINT ptOrg1 = m_ptOrg.at(0);
	_2POINT ptOrg2 = m_ptOrg.at(1);
	_2POINT ptFid1 = m_ptFid.at(0);
	_2POINT ptFid2 = m_ptFid.at(1);

	_2POINT ptOrg = (ptOrg1 + ptOrg2) / _2POINT(2, 2);
	_2POINT ptFid = (ptFid1 + ptFid2) / _2POINT(2, 2);
	
	m_ptRefOrg = ptOrg;
	m_ptRefFid = ptFid;

	m_TMatrix.dx = ptFid.dx - ptOrg.dx;
	m_TMatrix.dy = ptFid.dy - ptOrg.dy;
	m_TMatrix.dt = atan2((ptFid2.dy - ptFid1.dy), (ptFid2.dx - ptFid1.dx)) - atan2((ptOrg2.dy - ptOrg1.dy), (ptOrg2.dx - ptOrg1.dx));


	return bResult;

}


bool CCalcAlign::get4AlignResult()
{
	bool bResult = true;

	_2POINT ptOrg1 = m_ptOrg.at(0);
	_2POINT ptOrg2 = m_ptOrg.at(1);
	_2POINT ptOrg3 = m_ptOrg.at(2);
	_2POINT ptOrg4 = m_ptOrg.at(3);
	_2POINT ptFid1 = m_ptFid.at(0);
	_2POINT ptFid2 = m_ptFid.at(1);
	_2POINT ptFid3 = m_ptFid.at(2);
	_2POINT ptFid4 = m_ptFid.at(3);

	_2POINT ptOrg;
	_2POINT ptFid;

	// 무게중심
	//getWeightCenter(ptOrg1, ptOrg2, ptOrg3, ptOrg4, ptOrg);
	//getWeightCenter(ptFid1, ptFid2, ptFid3, ptFid4, ptFid);

	ptOrg = (ptOrg1 + ptOrg2 + ptOrg3 + ptOrg4) / _2POINT(4, 4);
	ptFid = (ptFid1 + ptFid2 + ptFid3 + ptFid4) / _2POINT(4, 4);

	m_ptRefOrg = ptOrg;
	m_ptRefFid = ptFid;

	m_TMatrix.dx = ptFid.dx - ptOrg.dx;
	m_TMatrix.dy = ptFid.dy - ptOrg.dy;

	double dFidt1, dFidt2, dFidt3, dFidt4 = 0.;
	double dOrit1, dOrit2, dOrit3, dOrit4 = 0.;
	
	double dResult1, dResult2, dResult3, dResult4 = 0.;
	double dTemp1, dTemp2, dTemp3, dTemp4 = 0.;

	dFidt1 = atan2((ptFid2.dy - ptFid1.dy), (ptFid2.dx - ptFid1.dx));// - atan2((ptOrg2.dy - ptOrg1.dy), (ptOrg2.dx - ptOrg1.dx));
	dFidt2 = atan2((ptFid3.dy - ptFid4.dy), (ptFid3.dx - ptFid4.dx));// - atan2((ptOrg3.dy - ptOrg4.dy), (ptOrg3.dx - ptOrg4.dx));
	dFidt3 = atan2((ptFid1.dy - ptFid4.dy), (ptFid1.dx - ptFid4.dx));// - atan2((ptOrg1.dy - ptOrg4.dy), (ptOrg1.dx - ptOrg4.dx));
	dFidt4 = atan2((ptFid2.dy - ptFid3.dy), (ptFid2.dx - ptFid3.dx));// - atan2((ptOrg2.dy - ptOrg3.dy), (ptOrg2.dx - ptOrg3.dx));
	
	dTemp1 = dFidt1 * TO_DEGREE;
	dTemp2 = dFidt2 * TO_DEGREE;
	dTemp3 = dFidt3 * TO_DEGREE;
	dTemp4 = dFidt4 * TO_DEGREE;

	dOrit1 = atan2((ptOrg2.dy - ptOrg1.dy), (ptOrg2.dx - ptOrg1.dx));
	dOrit2 = atan2((ptOrg3.dy - ptOrg4.dy), (ptOrg3.dx - ptOrg4.dx));
	dOrit3 = atan2((ptOrg1.dy - ptOrg4.dy), (ptOrg1.dx - ptOrg4.dx));
	dOrit4 = atan2((ptOrg2.dy - ptOrg3.dy), (ptOrg2.dx - ptOrg3.dx));

	dTemp1 = dOrit1 * TO_DEGREE;
	dTemp2 = dOrit2 * TO_DEGREE;
	dTemp3 = dOrit3 * TO_DEGREE;
	dTemp4 = dOrit4 * TO_DEGREE;

	dResult1 = dFidt1 - dOrit1;
	dResult2 = dFidt2 - dOrit2;
	dResult3 = dFidt3 - dOrit3;
	dResult4 = dFidt4 - dOrit4;

	dTemp1 = dResult1 * TO_DEGREE;
	dTemp2 = dResult2 * TO_DEGREE;
	dTemp3 = dResult3 * TO_DEGREE;
	dTemp4 = dResult4 * TO_DEGREE;


	m_TMatrix.dt = (dResult1 + dResult2 + dResult3 + dResult4) / 4;

	double dTest = m_TMatrix.dt * TO_DEGREE;

	return bResult;
}


//무게중심
bool CCalcAlign::getWeightCenter(_2POINT pt1, _2POINT pt2, _2POINT pt3, _2POINT pt4, _2POINT &ptCenter)
{
	bool bResult = true;

	double a = (pt3.dy - pt1.dy) / (pt3.dx - pt1.dx);	//y = ax + b
	double b = pt1.dy - (a * pt1.dx);

	double c = (pt2.dy - pt4.dy) / (pt2.dx - pt4.dx);	//y = cx + d
	double d = pt2.dy - (c * pt2.dx);

	//두 직선의 교점
	ptCenter.dx = (d - b) / (a - c);
	ptCenter.dy = (a * ptCenter.dx) + b;


	return bResult;
}

BOOL CCalcAlign::setUvwInfo(_UVW_INFO uvwInfo)
{
	memcpy(&m_UvwInfo, &uvwInfo, sizeof(uvwInfo));
	return TRUE;
}

_4POINT CCalcAlign::getUvwResult(_3POINT pt, DOUBLE CurrentAngle)
{
	double dX1, dX2, dY1, dY2;
	double dShiftX = 0., dShiftY = 0.;
	_4POINT ptResult;
	dX1 = (cos((pt.dt + CurrentAngle + m_UvwInfo.dAngle.dx1)*TO_RADIAN) - cos((CurrentAngle + m_UvwInfo.dAngle.dx1)*TO_RADIAN)) * m_UvwInfo.dRadius;
	dX2 = (cos((pt.dt + CurrentAngle + m_UvwInfo.dAngle.dx2)*TO_RADIAN) - cos((CurrentAngle + m_UvwInfo.dAngle.dx2)*TO_RADIAN)) * m_UvwInfo.dRadius;
	dY1 = (sin((pt.dt + CurrentAngle + m_UvwInfo.dAngle.dy1)*TO_RADIAN) - sin((CurrentAngle + m_UvwInfo.dAngle.dy1)*TO_RADIAN)) * m_UvwInfo.dRadius;
	dY2 = (sin((pt.dt + CurrentAngle + m_UvwInfo.dAngle.dy2)*TO_RADIAN) - sin((CurrentAngle + m_UvwInfo.dAngle.dy2)*TO_RADIAN)) * m_UvwInfo.dRadius;

	dX1 += pt.dx;
	dX2 += pt.dx;

	dY1 += pt.dy;
	dY2 += pt.dy;

	ptResult.dx1 = -dX1;
	ptResult.dx2 = -dX2;
	ptResult.dy1 = -dY1;
	ptResult.dy2 = -dY2;

	return ptResult;
}

_4POINT CCalcAlign::getUvwResult_New(_3POINT pt, DOUBLE CurrentAngle)
{
	double dX1, dX2, dY1, dY2;
	double dShiftX = 0., dShiftY = 0.;
	_4POINT ptResult;
	dX1 = m_UvwInfo.dRadius * cos((pt.dt + CurrentAngle + m_UvwInfo.dAngle.dx1)*TO_RADIAN) - m_UvwInfo.dRadius * cos((CurrentAngle + m_UvwInfo.dAngle.dx1)*TO_RADIAN);
	dX2 = m_UvwInfo.dRadius * cos((pt.dt + CurrentAngle + m_UvwInfo.dAngle.dx2)*TO_RADIAN) - m_UvwInfo.dRadius * cos((CurrentAngle + m_UvwInfo.dAngle.dx2)*TO_RADIAN);
	dY1 = m_UvwInfo.dRadius * sin((pt.dt + CurrentAngle + m_UvwInfo.dAngle.dy1)*TO_RADIAN) - m_UvwInfo.dRadius * sin((CurrentAngle + m_UvwInfo.dAngle.dy1)*TO_RADIAN);
	dY2 = m_UvwInfo.dRadius * sin((pt.dt + CurrentAngle + m_UvwInfo.dAngle.dy2)*TO_RADIAN) - m_UvwInfo.dRadius * sin((CurrentAngle + m_UvwInfo.dAngle.dy2)*TO_RADIAN);

	dX1 += pt.dx;
	dX2 += pt.dx;

	dY1 += pt.dy;
	dY2 += pt.dy;

	ptResult.dx1 = -dX1;
	ptResult.dx2 = -dX2;
	ptResult.dy1 = -dY1;
	ptResult.dy2 = -dY2;

	return ptResult;
}