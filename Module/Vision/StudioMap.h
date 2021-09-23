// StudioMap.h : StudioMap DLL�� �⺻ ��� �����Դϴ�.
//

#pragma once

#ifndef  UNITAXIS_DEFINE
#define UNITAXIS_DEFINE

#define UMTOMM	1000
struct _stUnitAxis {
	_stUnitAxis() {
		axisno = 0;
		xoffset = 0;
		yoffset = 0;
		dpos = 0;
		dPosBase = 0;
		dmin = 0;
		dmax = 0;
		dscale = 1;
		Mover.SetRect(-50, -50, 50, 50);
		scope.SetRect(-50, -50, 50, 50);
		zbar.SetRect(-40, -25, 80, 25);
		zscope.SetRect(-40, -25, 80, 25);

		BaseColor = RGB(255, 255, 255);
		MoverColor = RGB(0, 0, 0);
		bScopeGridFlag = TRUE;
	}
	int		axisno;		//���ȣ
	int		xoffset;	//0����ǥ�ɼ�(�߽ɱ���, �� ��ü)
	int		yoffset;	//0����ǥ�ɼ�(�߽ɱ���, �� ��ü)
	int		xMoverOffset;	//0����ǥ�ɼ�(�߽ɱ���)
	int		yMoverOffset;	//0����ǥ�ɼ�(�߽ɱ���)
	double	dpos;		//����ǥ��
	double  dPosBase;  //Base ��ü �� Position.(���� ���� ���� ���� Pos)
	double	dmin;		//�ּ�ġ
	double	dmax;		//�ִ�ġ	
	double	dscale;		//����
	CRect	Mover;		//Mover
	CRect	scope;		//�̵�����
	CRect	zbar;		//Z��ڽ�
	CRect	zscope;		//Z�̵�����

	COLORREF BaseColor;
	COLORREF MoverColor;

	BOOL bScopeGridFlag;
};

//struct stUnitPoint {
//	stUnitPoint() {
//		axisno = 0;
//		xoffset = 0;
//		yoffset = 0;
//
//		xSize = 0;
//		ySize = 0;
//
//		dPosX = 0;
//		dPosY = 0;
//		dScale = 1;
//
//		BaseColor = RGB(255, 255, 255);
//		bCenterFlag = TRUE;
//		bInnerFlag = FALSE;
//	}
//	int		axisno;		//���ȣ
//	int		xoffset;	//0����ǥ�ɼ�(�߽ɱ���, �� ��ü)
//	int		yoffset;	//0����ǥ�ɼ�(�߽ɱ���, �� ��ü)
//	int		xSize;   //X ������.
//	int		ySize;   //Y ������.
//	int		Width;
//	int		Height;
//
//	double		dPosX;
//	double		dPosY;
//	double	dScale;		//����
//
//	COLORREF BaseColor;
//	BOOL bCenterFlag;
//	BOOL bInnerFlag;
//};

struct stUnitFigure {
	stUnitFigure() {
		axisno = 0;
		xoffset = 0;
		yoffset = 0;

		xSize = 0;
		ySize = 0;

		//���ʿ� �ڽ� �ϳ��� �׸���.
		Width = 1;
		Height = 1;
		dScale = 1;

		dPosX = 0;
		dPosY = 0;

		BaseColor = RGB(255, 255, 255);
		bCenterFlag = TRUE;
		bInnerFlag = FALSE;
	}
	int	 axisno;		//���ȣ
	double	 xoffset;	//0����ǥ�ɼ�(�߽ɱ���, �� ��ü)
	double	 yoffset;	//0����ǥ�ɼ�(�߽ɱ���, �� ��ü)

	double	 xSize;   //X ������.
	double	 ySize;   //Y ������.
	double	 Width;
	double	Height;

	double	dPosX;
	double	dPosY;
	double	dScale;		//����

	COLORREF BaseColor;
	BOOL bCenterFlag;
	BOOL bInnerFlag;

	CRect rcOuter;
	CRect rcInner;
};

struct _stUnitAxisUVW {
	_stUnitAxisUVW() {
		axisno = 0;
		upos = 0;
		vpos = 0;
		wpos = 0;
	}
	int axisno;
	double	upos, vpos, wpos;
};

#endif

class CStudioMap : public CWnd
{
	//DECLARE_DYNAMIC(CWkLibVision)

private:
	int m_nMaxPointQuan;

protected :
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:
	CStudioMap(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CStudioMap();

	void DeleteWnd();

	BOOL bEntry;

	//�ʱⰪ
	DOUBLE m_dBaseScale;
	INT m_nBaseOffsetX;
	INT m_nBaseOffsetY;

	//�⺻ ����
	INT m_nViewOffsetX;
	INT m_nViewOffsetY;

	INT m_dOriginX;
	INT m_dOriginY;

	CPoint m_ptOrigin;
	CPoint m_ptCur;


	INT m_nRealWidth;
	INT m_nRealHeight;

	INT		m_nZbarHeight;	// Z��Box Scope(����)

	DOUBLE m_dScale;

	DOUBLE m_dPartExt;
	//Studio Setting �Լ�.
	void SetBaseData(double dBaseScale, int nBaseOffsetX, int nBaseOffsetY);
	void DrawBackGroundColor(CDC *dc, COLORREF RgbColor);
	void DisplayToMonitor(CDC *dc, CDC *MemDC);

	//��� �׸���.
	//void DrawCoordinateAxisX(CDC *pDC, CPoint *pPt);
	//void DrawCoordinateAxisY(CDC *pDC, CPoint *pPt);

	//�⺻ �׸��� �Լ�.
	void SetGridData(stUnitFigure* pGrid, double nOffsetX, double nOffsetY, double nSizeX, double nSizeY, double dScale);
	void SetGridDrawOption(stUnitFigure* pGrid, COLORREF ColorRef, BOOL bInnerFlag, double nWidth, double nHeight, BOOL bCenterFlag, BOOL bPartExtFlag, DOUBLE dPartExtRate);
	void SetGridPos(stUnitFigure* pGrid, double dPosX, double dPosY);
	

	void DrawCircleBorderline(CDC *pDC, stUnitFigure* pGrid);
	void DrawBoxBorderline(CDC *pDC, stUnitFigure *pGrid);
	void DrawBoxMultiBorderline(CDC *pDC, stUnitFigure *pGrid);
	void DrawFgLine(CDC *pDC, stUnitFigure *FirstFg, stUnitFigure *SecondFg, COLORREF crLineColor, INT nWidth = 1);



	//�� �׸��� �Լ�.
	void InitStudio(CRect rc, CDC *OriginDC, CDC *memDC, CBitmap *Bitmap);

	void setAxisScale(_stUnitAxis* axis, double dscale, double dmin, double dmax);
	void setAxisOffset(_stUnitAxis* axis, double dReduceRate, int xoffset, int yoffset);
	void setMoverOffset(_stUnitAxis* axis, double dReduceRate, int xoffset, int yoffset, BOOL bScopeGrid);

	void setAxisMoverX(_stUnitAxis* axis, double dReduceRate, int nMoverwidth, int nMoverheight);
	void setAxisMoverY(_stUnitAxis* axis, double dReduceRate, int nMoverwidth, int nMoverheight);
	void setAxisMoverZ(_stUnitAxis* axis, double dReduceRate, int nMoverwidth, int nMoverheight);
	void setAxisColor(_stUnitAxis* axis, COLORREF clrMover, COLORREF clrBase);

	void setAxisZbar(_stUnitAxis* axis, int nleft, int ntop);

	void setAxisPosX(_stUnitAxis* axis, double dpos, double dPosBase = 0);
	void setAxisPosY(_stUnitAxis* axis, double dpos, double dPosBase = 0);
	void setAxisPosZ(_stUnitAxis* axis, double dpos, double dPosBase = 0);
	void setAxisUVWpos(_stUnitAxisUVW* axis, double du, double dv, double dw);

	void DrawAxis(CDC *pDC, _stUnitAxis *axis);
	void DrawAxisCenter(CDC *pDC, _stUnitAxis *axis);
	void DrawCenter(CDC *pDC);

	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	virtual BOOL DestroyWindow();
};

