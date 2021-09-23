// MaskDraw.cpp : implementation file
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "DrawMask.h"

// CDrawMask
IMPLEMENT_DYNAMIC(CDrawMask, CStatic)

CDrawMask::CDrawMask()
{
	m_nRealWidth	= 1000;	// 화면 크기의 백분율로 Drawing
	m_nRealHeight	= 1000;

	LOGBRUSH	lbr;
	lbr.lbStyle = BS_SOLID;
	lbr.lbHatch = 0;

	lbr.lbColor = RGB( 0,	 0,		0 );		m_Frame.CreatePen	( PS_GEOMETRIC | PS_SOLID,	1, &lbr, 0, 0 );
	lbr.lbColor = RGB( 0,    0,		0	);		m_Worked.CreatePen	( PS_GEOMETRIC | PS_SOLID,	1, &lbr, 0, 0 );

	lbr.lbColor = RGB( 127,	127,	127 );		m_Cover1.CreatePen		( PS_GEOMETRIC | PS_SOLID,	1, &lbr, 0, 0 );
	lbr.lbColor = RGB( 0,	0,		255 );		m_Cover2.CreatePen		( PS_GEOMETRIC | PS_SOLID,	1, &lbr, 0, 0 );
	lbr.lbColor = RGB( 127,	127,	127 );		m_Howling1.CreatePen	( PS_GEOMETRIC | PS_SOLID,	1, &lbr, 0, 0 );
	lbr.lbColor = RGB( 0,	255,	0	);		m_Howling2.CreatePen	( PS_GEOMETRIC | PS_SOLID,	1, &lbr, 0, 0 );

	m_Font.DeleteObject();
	m_Font.CreateFontW(
						8,
						0,
						0,
						0,
						FW_BOLD,
						0,
						0,
						0,
						0,
						0,
						0,
						2,
						0,
						_T("Consolas")
					);
}

CDrawMask::~CDrawMask()
{
}


BEGIN_MESSAGE_MAP(CDrawMask, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CDrawMask message handlers

void CDrawMask::OnPaint()
{
	// Do not call CStatic::OnPaint() for painting messages

	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here

	
	
	return; //mhoon  사용 중지



	CBrush brush;
	CRect rc;
	
	GetClientRect(&rc);

	CDC *pDC = GetDC();

	////////////////////////////////////////////////////////
	// define real size -- mask size
	//
	pDC->SetMapMode(MM_ANISOTROPIC);

	m_nRealWidth	= rc.Width();
	m_nRealHeight	= rc.Height();
	pDC->SetWindowExt(m_nRealWidth, m_nRealHeight);

	pDC->SetViewportExt(rc.Width(), rc.Height());
	pDC->SetViewportOrg(0,0);

	// Coordinate change
	CRect rcDraw(0, 0, m_nRealWidth, m_nRealHeight);
	brush.CreateSolidBrush(RGB(64,64,64));

	pDC->FillRect(rcDraw, &brush);

	Draw_Mask( pDC );
	
//	PositionViewDrawPoint(pDC, 0, 0);

	ReleaseDC(pDC);
	// define real size -- mask size
	//
	////////////////////////////////////////////////////////
}

void CDrawMask::PositionViewPoint(CDC* pDC, FLOAT fPos_X, FLOAT fPos_Y)
{
	CFont font;
	CString strPos;
	INT pos_X = m_nRealWidth;
	INT pos_Y = m_nRealHeight;

	strPos.Format(_T("XY : %f %f"), fPos_X, fPos_Y);
	font.CreatePointFont(60, _T("궁서체"));
	pDC->SelectObject(&font);
	pDC->SetBkMode( TRANSPARENT );
	pDC->SetTextColor(RGB(0,200,9));
	pDC->TextOutW(-(pos_X/2)+3,-(pos_Y/2)+3, strPos);
}

void CDrawMask::Draw_Mask( CDC *pDC )
{
	/*
	CPointD		mImg_LT; 
	CPointD		mImg_RB;
	DOUBLE		fC_Width;
	DOUBLE		fH_Width;

	INT			nCLable		= 8;
	INT			nHLable		= 2;		

	INT			nFrameWidth	= 8;		
	INT			nFrameGab	= 4;
	INT			nMaskGab	= 3;
	INT			nDrawArea;
	INT			nGabTotal;
	CString		sMsg;

	m_pOldPen	= pDC->SelectObject( &m_Frame );
	pDC->SelectObject( GetStockObject(NULL_BRUSH) );


	// margin 10 pixel
	mImg_LT.x	= nFrameGab+nCLable;
	mImg_LT.y	= nFrameGab+nHLable;
	mImg_RB.x	= m_nRealWidth  -nFrameGab;
	mImg_RB.y	= m_nRealHeight -nFrameGab;
	pDC->Rectangle( mImg_LT.x,	mImg_LT.y,	mImg_RB.x,	mImg_RB.y );	// Frame

	mImg_LT.x	= nFrameWidth +nFrameGab +nCLable;
	mImg_LT.y	= nFrameWidth +nFrameGab +nHLable;
	mImg_RB.x	= m_nRealWidth  -(nFrameWidth +nFrameGab);
	mImg_RB.y	= m_nRealHeight -(nFrameWidth +nFrameGab);
	pDC->Rectangle( mImg_LT.x,	mImg_LT.y,	mImg_RB.x,	mImg_RB.y );	// Groove

	nDrawArea	= (m_nRealHeight-2*(nFrameWidth +nFrameGab)-nHLable);
	nGabTotal	= (pGlobalObj->m_Model->CoverInfo.nCount+1)*nMaskGab;
	fC_Width	= (DOUBLE)(nDrawArea-nGabTotal)/pGlobalObj->m_Model->CoverInfo.nCount;

	nDrawArea	= (m_nRealWidth-2*(nFrameWidth +nFrameGab)-nCLable);
	nGabTotal	= (pGlobalObj->m_Model->HowlingInfo.nCount+1)*nMaskGab;
	fH_Width	= (DOUBLE)(nDrawArea-nGabTotal)/pGlobalObj->m_Model->HowlingInfo.nCount;

	m_Font.DeleteObject();
	m_Font.CreateFontW(
						fC_Width+2,
						0,
						0,
						0,
						FW_BOLD,
						0,
						0,
						0,
						0,
						0,
						0,
						2,
						0,
						_T("Consolas")
					);
	poldFont	= (CFont*)pDC->SelectObject( m_Font );
	nOldMode	= pDC->SetBkMode( TRANSPARENT );
	pDC->SetTextColor( RGB( 255, 255, 255 ) );

	for( int i = 0; i < pGlobalObj->m_Model->CoverInfo.nCount; i++ ) {
		if( pGlobalObj->m_Model->CoverInfo.nWorked[i] )	{
			pDC->SelectObject( &m_Worked );
		} else {
			if( i%2 )	pDC->SelectObject( &m_Cover1 );
			else		pDC->SelectObject( &m_Cover2 );
		}
		
		mImg_LT.x	= 1;
		mImg_RB.x	= m_nRealWidth-1;
		
		mImg_LT.y	= nFrameWidth +nFrameGab+ +nHLable +nMaskGab*(i+1)+fC_Width*i;
		mImg_RB.y	= mImg_LT.y+fC_Width;
		pDC->Rectangle( mImg_LT.x,	mImg_LT.y,	mImg_RB.x,	mImg_RB.y );

		// Lable 	
		sMsg.Format( _T("%d"), (i+1) );		pDC->TextOutW( 2, mImg_LT.y, sMsg );
	}

	for( int i = 0; i < pGlobalObj->m_Model->HowlingInfo.nCount; i++ ) {
		if( pGlobalObj->m_Model->HowlingInfo.nWorked[i] ) {
			pDC->SelectObject( &m_Worked );
		} else {
			if( i%2 )	pDC->SelectObject( &m_Howling1 );
			else		pDC->SelectObject( &m_Howling2 );
		}
		
		mImg_LT.y	=  1;
		mImg_RB.y	=  m_nRealHeight-1; 

		mImg_LT.x	=  nFrameWidth +nFrameGab+ +nCLable +nMaskGab*(i+1)+fH_Width*i;
		mImg_RB.x	=  mImg_LT.x +fH_Width;

		pDC->Rectangle( mImg_LT.x,	mImg_LT.y,	mImg_RB.x,	mImg_RB.y );

		// Lable 	
		sMsg.Format( _T("%d"), (i+1) );	pDC->TextOutW( mImg_LT.x, 2, sMsg );
	}

	pDC->SelectObject( m_pOldPen );
	*/
}