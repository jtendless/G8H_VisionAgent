// StudioMap.cpp : 해당 DLL의 초기화 루틴을 정의합니다.
//

#include "stdafx.h"
#include "StudioMap.h"



CStudioMap::CStudioMap(CWnd* pParent/* = NULL*/)
{

}

CStudioMap::~CStudioMap()
{

}

void CStudioMap::DoDataExchange(CDataExchange* pDX)
{
	CWnd::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CStudioMap, CWnd)
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
END_MESSAGE_MAP()

void CStudioMap::InitStudio(CRect rc, CDC *OriginDC, CDC *memDC, CBitmap *Bitmap)
{
	memDC->CreateCompatibleDC(OriginDC);
	Bitmap->CreateCompatibleBitmap(OriginDC, rc.Width(), rc.Height());
	memDC->SelectObject(Bitmap);

	SetMapMode(*memDC, MM_ANISOTROPIC);							//XY축단위 가변형으로
	memDC->SetWindowExt(m_nRealWidth, m_nRealHeight);			//논리좌표상 화면크기설정
	memDC->SetViewportExt(rc.Width(), rc.Height());					//논리좌표와 매칭할 뷰포트화면크기
	memDC->SetViewportOrg((rc.Width() / 2) - m_nViewOffsetX * rc.Width() / m_nRealWidth
		, (rc.Height() / 2) - m_nViewOffsetY * rc.Height() / m_nRealHeight);		//0점위치변경
	//mMemDC.SetROP2(R2_MERGEPENNOT);

	OriginDC->SetMapMode(MM_ANISOTROPIC);
	OriginDC->SetWindowExt(m_nRealWidth, m_nRealHeight);
	OriginDC->SetViewportExt(rc.Width(), rc.Height());
	OriginDC->SetViewportOrg((rc.Width() / 2) - m_nViewOffsetX * rc.Width() / m_nRealWidth
		, (rc.Height() / 2) - m_nViewOffsetY * rc.Height() / m_nRealHeight);
}

//축Scale 초기화
void CStudioMap::setAxisScale(_stUnitAxis* axis, double dscale, double dmin, double dmax)
{
	axis->dscale = dscale;
	axis->dmin = dmin;
	axis->dmax = dmax;
}

//축Offset 초기화
void CStudioMap::setAxisOffset(_stUnitAxis* axis, double dScale, int xoffset, int yoffset)
{
	axis->xoffset = xoffset * dScale;
	axis->yoffset = yoffset * dScale;
}

void CStudioMap::setMoverOffset(_stUnitAxis* axis, double dScale, int xoffset, int yoffset, BOOL bScopeGrid)
{
	axis->xMoverOffset = xoffset * dScale;
	axis->yMoverOffset = yoffset * dScale;
	axis->bScopeGridFlag = bScopeGrid;
}

//X축초기화
void CStudioMap::setAxisMoverX(_stUnitAxis* axis, double dScale, int nMoverwidth, int nMoverheight)
{
	int nMoverWidth = nMoverwidth * dScale;
	int nMoverHeight = nMoverheight * dScale;

	axis->scope.left = axis->dmin * axis->dscale + axis->xoffset;// -nMoverWidth / 2;
	axis->scope.right = axis->dmax * axis->dscale + axis->xoffset;// +nMoverWidth / 2;
	axis->scope.top = axis->dPosBase * axis->dscale + axis->yoffset - nMoverHeight / 2;// +axis->yMoverOffset;
	axis->scope.bottom = axis->dPosBase * axis->dscale + axis->yoffset + nMoverHeight / 2;// +axis->yMoverOffset;

	axis->Mover.left = axis->dpos * axis->dscale + axis->xoffset + axis->xMoverOffset - nMoverWidth / 2;
	axis->Mover.right = axis->dpos * axis->dscale + axis->xoffset + axis->xMoverOffset + nMoverWidth / 2;
	axis->Mover.top = axis->scope.top;
	axis->Mover.bottom = axis->scope.bottom;


}

//Y축초기화
void CStudioMap::setAxisMoverY(_stUnitAxis* axis, double dScale, int nMoverwidth, int nMoverheight)
{
	int nMoverWidth = nMoverwidth * dScale;
	int nMoverHeight = nMoverheight * dScale;

	axis->scope.left = axis->xoffset + (axis->dPosBase * axis->dscale) - nMoverWidth / 2;// + axis->xMoverOffset;
	axis->scope.right = axis->xoffset + (axis->dPosBase * axis->dscale) + nMoverWidth / 2;// +axis->xMoverOffset;
	axis->scope.top = axis->yoffset - (axis->dmax * axis->dscale);// -nMoverHeight / 2;
	axis->scope.bottom = axis->yoffset - (axis->dmin * axis->dscale);// +nMoverHeight / 2;

	axis->Mover.left = axis->scope.left;
	axis->Mover.right = axis->scope.right;
	axis->Mover.top = axis->yoffset + axis->yMoverOffset + (axis->dpos * axis->dscale) - nMoverHeight / 2;
	axis->Mover.bottom = axis->yoffset + axis->yMoverOffset + (axis->dpos * axis->dscale) + nMoverHeight / 2;


}

//Z축초기화
void CStudioMap::setAxisMoverZ(_stUnitAxis* axis, double dScale, int nMoverwidth, int nMoverheight)
{
	int nMoverWidth = nMoverwidth * dScale;
	int nMoverHeight = nMoverheight * dScale;

	axis->scope.left = axis->xoffset + (axis->dPosBase * axis->dscale) - nMoverWidth / 2;// + axis->xMoverOffset;
	axis->scope.right = axis->xoffset + (axis->dPosBase * axis->dscale) + nMoverWidth / 2;// +axis->xMoverOffset;
	axis->scope.top = axis->yoffset - (axis->dmax * axis->dscale);// -nMoverHeight / 2;
	axis->scope.bottom = axis->yoffset - (axis->dmin * axis->dscale);// +nMoverHeight / 2;

	axis->Mover.left = axis->scope.left;
	axis->Mover.right = axis->scope.right;
	axis->Mover.top = axis->yoffset + axis->yMoverOffset + (axis->dpos * axis->dscale) - nMoverHeight / 2;
	axis->Mover.bottom = axis->yoffset + axis->yMoverOffset + (axis->dpos * axis->dscale) + nMoverHeight / 2;

}

void CStudioMap::setAxisColor(_stUnitAxis* axis, COLORREF clrMover, COLORREF clrBase)
{
	axis->BaseColor = clrBase;
	axis->MoverColor = clrMover;
}


//Z-Bar초기화
void CStudioMap::setAxisZbar(_stUnitAxis* axis, int nleft, int ntop)
{
	axis->zbar.SetRect(nleft, ntop, nleft + 90, ntop + 50);
	axis->zscope.SetRect(nleft, ntop, nleft + 90, ntop + m_nZbarHeight + 50);
}

//X축위치
void CStudioMap::setAxisPosX(_stUnitAxis* axis, double dpos, double dPosBase)
{
	int ntemp = axis->xoffset + (int)(dpos * axis->dscale);
	axis->dpos = dpos;
	axis->dPosBase = dPosBase;
	//axis->Mover.MoveToX(ntemp - (axis->Mover.right - axis->Mover.left) / 2);
}

//Y축위치
void CStudioMap::setAxisPosY(_stUnitAxis* axis, double dpos, double dPosBase)
{
	int ntemp = axis->yoffset - (int)(dpos * axis->dscale); //위치 증가시 좌표는 감소
	axis->dpos = dpos;
	axis->dPosBase = dPosBase;
	//axis->Mover.MoveToY(ntemp - (axis->Mover.bottom - axis->Mover.top) / 2);
	//axis->zbar.MoveToY(ntemp);
}

//Z축위치
void CStudioMap::setAxisPosZ(_stUnitAxis* axis, double dpos, double dPosBase)
{
	int ntemp = axis->zscope.top - (int)((axis->dmax - dpos) * axis->dscale);  //위치 증가시 좌표는 감소
	axis->dpos = dpos;
	axis->dPosBase = dPosBase;
	//axis->zbar.MoveToY(ntemp);
}

void CStudioMap::setAxisUVWpos(_stUnitAxisUVW* axis, double du, double dv, double dw)
{
	axis->upos = du;
	axis->vpos = dv;
	axis->wpos = dw;
}


void CStudioMap::DrawAxis(CDC *pDC, _stUnitAxis *axis)
{
	CBrush BaseBrush, MoverBrush, *OldBrush;
	BaseBrush.CreateSolidBrush(axis->BaseColor);
	MoverBrush.CreateSolidBrush(axis->MoverColor);
	OldBrush = pDC->SelectObject(&BaseBrush);
	int nTop = 0;
	int nBottom = 0;

	if (axis->bScopeGridFlag)
	{
		nTop = axis->scope.top * (-1);
		nBottom = axis->scope.bottom * (-1);
		pDC->Rectangle(axis->scope.left, nTop, axis->scope.right, nBottom);
	}

	nTop = axis->Mover.top * (-1);
	nBottom = axis->Mover.bottom * (-1);

	pDC->SelectObject(&MoverBrush);
	pDC->Rectangle(axis->Mover.left, nTop, axis->Mover.right, nBottom);


	pDC->SelectObject(OldBrush);
	BaseBrush.DeleteObject();
	MoverBrush.DeleteObject();
}


void CStudioMap::DrawAxisCenter(CDC *pDC, _stUnitAxis *axis)
{
	CPen BasePen, MoverPen, *OldPen;
	//BasePen.CreatePen(0, 1axis->BaseColor);
	MoverPen.CreatePen(PS_DOT, 1, RGB(0, 0, 255));
	OldPen = pDC->SelectObject(&MoverPen);
	//pDC->SetBkMode(TRANSPARENT);
	int nTop = 0;
	int nBottom = 0;

	if (axis->bScopeGridFlag)
	{
		nTop = axis->scope.top * (-1);
		nBottom = axis->scope.bottom * (-1);
		pDC->MoveTo(axis->scope.left, nTop);
		pDC->LineTo(axis->scope.right, nTop);
		pDC->LineTo(axis->scope.right, nBottom);
		pDC->LineTo(axis->scope.left, nBottom);
		pDC->LineTo(axis->scope.left, nTop);

		pDC->MoveTo((axis->scope.right - axis->scope.left) / 2, nTop);
		pDC->LineTo((axis->scope.right - axis->scope.left) / 2, nBottom);

		pDC->MoveTo(axis->scope.left, (nTop - nBottom) / 2);
		pDC->LineTo(axis->scope.right, (nTop - nBottom) / 2);
	}

	nTop = axis->Mover.top * (-1);
	nBottom = axis->Mover.bottom * (-1);

	pDC->SelectObject(&MoverPen);
	pDC->MoveTo(axis->Mover.left, nTop);
	pDC->LineTo(axis->Mover.right, nTop);
	pDC->LineTo(axis->Mover.right, nBottom);
	pDC->LineTo(axis->Mover.left, nBottom);
	pDC->LineTo(axis->Mover.left, nTop);

	pDC->MoveTo((axis->Mover.right + axis->Mover.left) / 2, nTop);
	pDC->LineTo((axis->Mover.right + axis->Mover.left) / 2, nBottom);

	pDC->MoveTo(axis->Mover.left, (nTop + nBottom) / 2);
	pDC->LineTo(axis->Mover.right, (nTop + nBottom) / 2);

	//pDC->Rectangle(axis->Mover.left, nTop, axis->Mover.right, nBottom);


	pDC->SelectObject(OldPen);
	//BaseBrush.DeleteObject();
	MoverPen.DeleteObject();
}

void CStudioMap::SetGridData(stUnitFigure* pGrid, double nOffsetX, double nOffsetY, double nSizeX, double nSizeY, double dScale)
{
	pGrid->dScale = dScale;

	pGrid->xoffset = nOffsetX * pGrid->dScale;
	pGrid->yoffset = nOffsetY * pGrid->dScale;

	pGrid->xSize = nSizeX * pGrid->dScale;
	pGrid->ySize = nSizeY * pGrid->dScale;
}

//Inner True시 Size 입력해주야됨.
void CStudioMap::SetGridDrawOption(stUnitFigure* pGrid, COLORREF ColorRef, BOOL bInnerFlag, double dWidth, double dHeight, BOOL bCenterFlag, BOOL bPartExtFlag, DOUBLE dPartExtRate)
{
	pGrid->BaseColor = ColorRef;
	pGrid->bCenterFlag = bCenterFlag;
	pGrid->bInnerFlag = bInnerFlag;;

	pGrid->Width = dWidth * pGrid->dScale;
	pGrid->Height = dHeight * pGrid->dScale;

	if (bPartExtFlag)
	{
		pGrid->xSize *= dPartExtRate;
		pGrid->ySize *= dPartExtRate;
	}

	pGrid->rcOuter.left = pGrid->xoffset + pGrid->dPosX - pGrid->xSize / 2;
	pGrid->rcOuter.right = pGrid->xoffset + pGrid->dPosX + pGrid->xSize / 2;
	pGrid->rcOuter.top = pGrid->yoffset + pGrid->dPosY - pGrid->ySize / 2;
	pGrid->rcOuter.bottom = pGrid->yoffset + pGrid->dPosY + pGrid->ySize / 2;

	if (pGrid->bInnerFlag)
	{
		pGrid->rcInner.left = pGrid->rcOuter.left + pGrid->Width;
		pGrid->rcInner.right = pGrid->rcOuter.right - pGrid->Width;
		pGrid->rcInner.top = pGrid->rcOuter.top + pGrid->Height;
		pGrid->rcInner.bottom = pGrid->rcOuter.bottom - pGrid->Height;
	}
}

void CStudioMap::SetGridPos(stUnitFigure* pGrid, double dPosX, double dPosY)
{
	pGrid->dPosX = dPosX * pGrid->dScale;
 	pGrid->dPosY = dPosY * pGrid->dScale;
}

void CStudioMap::DrawCircleBorderline(CDC *pDC, stUnitFigure *pGrid)
{
	CPen SolidPen, DotPen, *OldPen;
	CRect Rect;

	DotPen.CreatePen(PS_DOT, 1, RGB(255, 0, 0));
	SolidPen.CreatePen(PS_SOLID, 1, pGrid->BaseColor);

	pDC->SetBkMode(TRANSPARENT);

	OldPen = pDC->SelectObject(&SolidPen);
	double dTop = 0;
	double dBottom = 0;

	Rect.top = pGrid->rcOuter.top * (-1);
	Rect.bottom = pGrid->rcOuter.bottom * (-1);
	Rect.left = pGrid->rcOuter.left;
	Rect.right = pGrid->rcOuter.right;

	//pDC->MoveTo(Rect.left, dTop);
	//pDC->LineTo(Rect.right, dTop);
	//pDC->LineTo(Rect.right, dBottom);
	//pDC->LineTo(Rect.left, dBottom);
	//pDC->LineTo(Rect.left, dTop);
	pDC->Ellipse(Rect);

	if (pGrid->bInnerFlag)
	{
		Rect.top = pGrid->rcInner.top * (-1);
		Rect.bottom = pGrid->rcInner.bottom * (-1);
		Rect.left = pGrid->rcInner.left;
		Rect.right = pGrid->rcInner.right;

		//pDC->MoveTo(Rect.left, dTop);
		//pDC->LineTo(Rect.right, dTop);
		//pDC->LineTo(Rect.right, dBottom);
		//pDC->LineTo(Rect.left, dBottom);
		//pDC->LineTo(Rect.left, dTop);

		pDC->Ellipse(Rect);
	}

	if (pGrid->bCenterFlag)
	{
		pDC->SelectObject(&DotPen);

		dTop = pGrid->rcOuter.top * (-1);
		dBottom = pGrid->rcOuter.bottom * (-1);
		Rect.left = pGrid->rcOuter.left;
		Rect.right = pGrid->rcOuter.right;

		pDC->MoveTo((Rect.left + Rect.right) / 2, dTop);
		pDC->LineTo((Rect.left + Rect.right) / 2, dBottom);
		pDC->MoveTo(Rect.right, (dTop + dBottom) / 2);
		pDC->LineTo(Rect.left, (dTop + dBottom) / 2);
	}

	DeleteObject(DotPen);
	pDC->SelectObject(OldPen);

	DeleteObject(SolidPen);
}

void CStudioMap::DrawBoxBorderline(CDC *pDC, stUnitFigure *pGrid)
{
	CPen SolidPen, DotPen, *OldPen;
	CRect Rect;

	DotPen.CreatePen(PS_DOT, 1, RGB(255,0,0));
	SolidPen.CreatePen(PS_SOLID, 1, pGrid->BaseColor);

	pDC->SetBkMode(TRANSPARENT);

	OldPen = pDC->SelectObject(&SolidPen);
	double dTop = 0;
	double dBottom = 0;

	dTop				= pGrid->rcOuter.top * (-1);
	dBottom		= pGrid->rcOuter.bottom * (-1);
	Rect.left			= pGrid->rcOuter.left;
	Rect.right		= pGrid->rcOuter.right;

	pDC->MoveTo(Rect.left, dTop);
	pDC->LineTo(Rect.right, dTop);
	pDC->LineTo(Rect.right, dBottom);
	pDC->LineTo(Rect.left, dBottom);
	pDC->LineTo(Rect.left, dTop);

	if (pGrid->bInnerFlag)
	{
		dTop = pGrid->rcInner.top * (-1);
		dBottom = pGrid->rcInner.bottom * (-1);
		Rect.left = pGrid->rcInner.left;
		Rect.right = pGrid->rcInner.right;

		pDC->MoveTo(Rect.left, dTop);
		pDC->LineTo(Rect.right, dTop);
		pDC->LineTo(Rect.right, dBottom);
		pDC->LineTo(Rect.left, dBottom);
		pDC->LineTo(Rect.left, dTop);
	}

	if (pGrid->bCenterFlag)
	{
		pDC->SelectObject(&DotPen);

		dTop = pGrid->rcOuter.top * (-1);
		dBottom = pGrid->rcOuter.bottom * (-1);
		Rect.left = pGrid->rcOuter.left;
		Rect.right = pGrid->rcOuter.right;

		pDC->MoveTo((Rect.left + Rect.right) / 2 , dTop);
		pDC->LineTo((Rect.left + Rect.right) / 2, dBottom);
		pDC->MoveTo(Rect.right, (dTop + dBottom) / 2);
		pDC->LineTo(Rect.left, (dTop + dBottom) / 2);
	}

	pDC->SelectObject(OldPen);

	DeleteObject(DotPen);
	DeleteObject(SolidPen);
}

void CStudioMap::DrawFgLine(CDC *pDC, stUnitFigure *FirstFg, stUnitFigure *SecondFg, COLORREF crLineColor, INT nWidth)
{
	CPen SolidPen, DotPen, *OldPen;
	CRect Rect;
	INT nStartX, nStartY;
	INT nEndX, nEndY;
	double dTop = 0;
	double dBottom = 0;

	DotPen.CreatePen(PS_DOT, nWidth, RGB(255, 0, 0));
	SolidPen.CreatePen(PS_SOLID, nWidth, crLineColor);

	pDC->SetBkMode(TRANSPARENT);

	OldPen = pDC->SelectObject(&SolidPen);
	
	dTop = FirstFg->rcOuter.top * (-1);
	dBottom = FirstFg->rcOuter.bottom * (-1);

	nStartX = (FirstFg->rcOuter.left + FirstFg->rcOuter.right) / 2;
	nStartY = (dTop + dBottom) / 2;
	
	dTop = SecondFg->rcOuter.top * (-1);
	dBottom = SecondFg->rcOuter.bottom * (-1);

	nEndX = (SecondFg->rcOuter.left + SecondFg->rcOuter.right) / 2;
	nEndY = (dTop + dBottom) / 2;
	
	pDC->MoveTo(nStartX, nStartY);
	pDC->LineTo(nEndX, nEndY);


	pDC->SelectObject(OldPen);

	DeleteObject(DotPen);
	DeleteObject(SolidPen);
}

BOOL CStudioMap::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	DOUBLE PreScale = m_dScale;
 
	if (m_dScale > 0.1)
	{
		if (zDelta < 0)
		{
			m_dScale -= m_dScale / 3;
		}
	}

	//if (m_dScale < 2)
	{
		if (zDelta > 0)
		{
			m_dScale += m_dScale / 3;
		}
	}

	m_nViewOffsetX = m_nViewOffsetX * m_dScale / PreScale;
	m_nViewOffsetY = m_nViewOffsetY * m_dScale / PreScale;

	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}

void CStudioMap::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetFocus();
	CWnd::OnLButtonDown(nFlags, point);
}

void CStudioMap::OnLButtonUp(UINT nFlags, CPoint point)
{


	CWnd::OnLButtonUp(nFlags, point);
}


void CStudioMap::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_dScale = m_dBaseScale;
	m_nViewOffsetX = m_nBaseOffsetX;
	m_nViewOffsetY = m_nBaseOffsetY;
	CWnd::OnLButtonDblClk(nFlags, point);
}


void CStudioMap::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect Rect;
	GetClientRect(&Rect);
	DOUBLE dOffsetX = 0., dOffsetY = 0.;

	if (GetCapture())
	{
		m_ptCur = point;

		dOffsetX = (m_ptCur.x - m_ptOrigin.x) * m_nRealWidth / Rect.Width();
		dOffsetY = (m_ptCur.y - m_ptOrigin.y) * m_nRealHeight / Rect.Height();

		m_nViewOffsetX = m_dOriginX - dOffsetX;
		m_nViewOffsetY = m_dOriginY - dOffsetY;
	}


	CWnd::OnMouseMove(nFlags, point);
}


void CStudioMap::OnMButtonDown(UINT nFlags, CPoint point)
{
	CRect Rect;
	GetClientRect(&Rect);
	if (point.y > Rect.bottom || point.y < Rect.top || point.x > Rect.right || point.x < Rect.left)
		return;

	SetCapture();
	m_ptOrigin = point;
	m_dOriginX = m_nViewOffsetX;
	m_dOriginY = m_nViewOffsetY;
	CWnd::OnMButtonDown(nFlags, point);
}


void CStudioMap::OnMButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture();

	CWnd::OnMButtonUp(nFlags, point);
}

void CStudioMap::DrawCenter(CDC *pDC)
{
	CRect Rect;

	CPen CenterPen, *OldPen;
	//BasePen.CreatePen(0, 1axis->BaseColor);
	CenterPen.CreatePen(PS_DOT, 1, RGB(255, 0, 0));
	OldPen = pDC->SelectObject(&CenterPen);
	pDC->SetBkMode(TRANSPARENT);

	pDC->MoveTo(0, m_nRealHeight);
	pDC->LineTo(0, -m_nRealHeight);

	pDC->MoveTo(m_nRealWidth, 0);
	pDC->LineTo(-m_nRealWidth, 0);


	pDC->SelectObject(OldPen);
	//BaseBrush.DeleteObject();
	CenterPen.DeleteObject();
}

void CStudioMap::SetBaseData(double dBaseScale, int nBaseOffsetX, int nBaseOffsetY)
{
	m_dBaseScale = dBaseScale;
	m_nBaseOffsetX = nBaseOffsetX;
	m_nBaseOffsetY = nBaseOffsetY;

	m_dScale = m_dBaseScale;
	m_nViewOffsetX = m_nBaseOffsetX;
	m_nViewOffsetY = m_nBaseOffsetY;
}

void CStudioMap::DrawBackGroundColor(CDC *dc, COLORREF RgbColor)
{
	CBrush	brBackgroundColor;
	brBackgroundColor.CreateSolidBrush(RgbColor);
	CRect rcDraw(-m_nRealWidth + m_nViewOffsetX, -m_nRealHeight + m_nViewOffsetY, m_nRealWidth + m_nViewOffsetX, m_nRealHeight + m_nViewOffsetY);

	dc->SelectObject(&brBackgroundColor);
	dc->FillRect(rcDraw, &brBackgroundColor);
}

void CStudioMap::DisplayToMonitor(CDC *dc, CDC *MemDC)
{
	CRect rcDraw(-m_nRealWidth + m_nViewOffsetX, -m_nRealHeight + m_nViewOffsetY, m_nRealWidth + m_nViewOffsetX, m_nRealHeight + m_nViewOffsetY);

	dc->BitBlt(rcDraw.left, rcDraw.top, rcDraw.Width(), rcDraw.Height(), MemDC, rcDraw.left, rcDraw.top, SRCCOPY);

}

BOOL CStudioMap::DestroyWindow()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CWnd::DestroyWindow();
}

void CStudioMap::DeleteWnd()
{
	//delete this;
}