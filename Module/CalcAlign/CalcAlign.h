#pragma once
#include <vector>
#include <math.h>
////
#ifndef _2POINT_
#define _2POINT_
struct _2POINT
{
	double	dx;
	double	dy;

	_2POINT() { dx = dy = 0; }
	_2POINT(double x, double y) { dx = x; dy = y; };

	// X, Y Swap
	void Swap()
	{
		double dTemp = dx;
		dx = dy;
		dy = dTemp;
	}

	// 두 포인트의 중심점 반환
	static _2POINT Center(_2POINT p1, _2POINT p2)
	{
		return _2POINT((p1.dx + p2.dx) / 2., (p1.dy + p2.dy) / 2.);
	}

	_2POINT operator + (const _2POINT p) { return _2POINT(dx + p.dx, dy + p.dy); }
	_2POINT operator - (_2POINT p) { return _2POINT(dx - p.dx, dy - p.dy); }
	_2POINT operator * (_2POINT p) { return _2POINT(dx * p.dx, dy * p.dy); }
	_2POINT operator / (_2POINT p)
	{
		if (p.dx == 0 || p.dy == 0)	return _2POINT(0, 0);
		return _2POINT(dx / p.dx, dy / p.dy);
	}
};
#endif

////
#ifndef _3POINT_
#define _3POINT_
struct _3POINT
{
	double dx;
	double dy;
	double dt;

	_3POINT() { dx = dy = dt = 0; }
	_3POINT(double x, double y, double t) { dx = x; dy = y; dt = t; };

	_3POINT operator + (const _3POINT p) { return _3POINT(dx + p.dx, dy + p.dy, dt + p.dt); }
	_3POINT operator - (const _3POINT p) { return _3POINT(dx - p.dx, dy - p.dy, dt - p.dt); }


};
#endif

struct _4POINT
{
	double dx1;
	double dx2;
	double dy1;
	double dy2;

	_4POINT() { dx1 = dx2 = dy1 = dy2 = 0; }
};
////
struct _UVW_INFO
{
	_4POINT dAngle;
	double dRadius;
};
////

class CCalcAlign
{
private:
	std::vector<_2POINT>	m_ptOrg;
	std::vector<_2POINT>	m_ptFid;

	_2POINT		m_ptCenter;
	_2POINT		m_ptRefOrg, m_ptRefFid;
	_3POINT		m_TMatrix;

	_UVW_INFO		m_UvwInfo;
public:
	CCalcAlign();
	~CCalcAlign();

private:
	int		getPointSize() { return (int) m_ptOrg.size(); }
	bool	get2AlignResult();
	bool	get4AlignResult();
	bool	getWeightCenter(_2POINT pt1, _2POINT pt2, _2POINT pt3, _2POINT pt4, _2POINT &ptCenter);

public:
	void	clearAlignPoint();
	void	setAlignCenter(_2POINT pt) { m_ptCenter = pt; }
	void	setAlignPoint(_2POINT ptOrg1, _2POINT ptOrg2, _2POINT ptFid1, _2POINT ptFid2);
	_2POINT getAlignResult(_2POINT pt);
	_3POINT getAlignResultXYT();

	BOOL setUvwInfo(_UVW_INFO uvwInfo);
	_4POINT getUvwResult(_3POINT pt, DOUBLE CurrentAngle);
	_4POINT getUvwResult_New(_3POINT pt, DOUBLE CurrentAngle);
};

