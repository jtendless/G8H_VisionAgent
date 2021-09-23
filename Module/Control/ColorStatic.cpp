#include "stdafx.h"
#include "ColorStatic.h"


CColorStatic::CColorStatic()
{
	m_ColorBrush.CreateSolidBrush(MBackgroundColor);
	m_mLimit = 0;
	m_pLimit = 100;

	m_bClick = FALSE;
	m_bBkDraw = FALSE;
	m_bTrack = FALSE;
	m_bActButton = FALSE;
	m_bNum = FALSE;
}


CColorStatic::~CColorStatic()
{
	m_ColorBrush.DeleteObject();
}
BEGIN_MESSAGE_MAP(CColorStatic, CStatic)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

HBRUSH CColorStatic::CtlColor(CDC* pDC, UINT nCtlColor)
{
	// TODO:  여기서 DC의 특성을 변경합니다.
	pDC->SetTextColor(MTextColor);
	pDC->SetBkMode(TRANSPARENT);  // we do not want to draw background when drawing text. 
	// background color comes from drawing the control background.
	if (MTransparent)
		return nullptr;  // return nullptr to indicate that the parent object 
	// should supply the brush. it has the appropriate background color.
	else
		return (HBRUSH)m_ColorBrush.m_hObject;// CreateSolidBrush(MBackgroundColor);
}

void CColorStatic::SetTransparent(bool ATransparent)
{
	MTransparent = ATransparent;
	Invalidate(false);
}

void CColorStatic::SetBackgroundColor(COLORREF AColor)
{
	//MBackgroundColor = AColor;

	if (MCurrentBackgroundColor == AColor)
		return;

	MCurrentBackgroundColor = AColor;

	m_ColorBrush.DeleteObject();
	m_ColorBrush.CreateSolidBrush(AColor);

	//MTransparent = false;
	Invalidate(FALSE);
}

void CColorStatic::SetParaOriginColor(COLORREF AColor)
{
	//MOriginalBackgroundColor = AColor;
	if (MBackgroundColor == AColor)
		return;

	MBackgroundColor = AColor;
}

void CColorStatic::SetParaChangeColor(COLORREF AColor)
{
	MChangeBackgroundColor = AColor;
}

void CColorStatic::SetTextColor(COLORREF AColor)
{
	if (MTextColor == AColor)
		return;

	MTextColor = AColor;
	Invalidate(false);
}


void CColorStatic::SetData(CString strData)
{
	CString strTemp;
	GetWindowTextW(strTemp);

	if(strTemp.Compare(strData) != 0)
		SetWindowTextW(strData);
}


BOOL CColorStatic::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case 0x1B: //Esc
			return TRUE;
			break;
		case 0x0D: //Enter
			return TRUE;
			break;
		}
	}

	return CStatic::PreTranslateMessage(pMsg);
}

void CColorStatic::SetActButton(BOOL bActbutton)
{
	m_bActButton = bActbutton;
}

void CColorStatic::SetNumButton(BOOL bNum, int mLimit, int pLimit)
{
	m_bNum = bNum;
	m_mLimit = mLimit;
	m_pLimit = pLimit;
}

void CColorStatic::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bActButton)
	{
		if (m_bTrack == FALSE)
		{
			TRACKMOUSEEVENT MouseEvent;
			::ZeroMemory(&MouseEvent, sizeof(MouseEvent));

			MouseEvent.cbSize = sizeof(MouseEvent);
			MouseEvent.dwFlags = TME_LEAVE;
			MouseEvent.hwndTrack = m_hWnd;
			MouseEvent.dwHoverTime = 0;

			m_bTrack = ::_TrackMouseEvent(&MouseEvent);
			if (m_bTrack)
			{
				SetBackgroundColor(MChangeBackgroundColor);
			}
		}
	}
	CStatic::OnMouseMove(nFlags, point);
}

void CColorStatic::OnMouseLeave()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bActButton)
	{
		if (m_bTrack == TRUE)
		{
			TRACKMOUSEEVENT MouseEvent;
			::ZeroMemory(&MouseEvent, sizeof(MouseEvent));

			MouseEvent.cbSize = sizeof(MouseEvent);
			MouseEvent.dwFlags = TME_CANCEL;
			MouseEvent.hwndTrack = m_hWnd;

			::_TrackMouseEvent(&MouseEvent);

			m_bTrack = FALSE;
			SetBackgroundColor(MBackgroundColor);
		}
	}
	CStatic::OnMouseLeave();
}

void CColorStatic::PreSubclassWindow()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	//SetBackgroundColor(MBackgroundColor);

	CStatic::PreSubclassWindow();
}


void CColorStatic::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CString strTemp;
	int nTemp;

	if (m_bNum == TRUE)
	{
		GetWindowTextW(strTemp);
		nTemp = _ttoi(strTemp);

		if (nTemp < m_pLimit)
		{
			nTemp += 1;
			strTemp.Format(_T("%d"), nTemp);
			SetWindowTextW(strTemp);
		}
	}
	CStatic::OnLButtonUp(nFlags, point);
}


void CColorStatic::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CString strTemp;
	int nTemp;

	if (m_bNum == TRUE)
	{
		GetWindowTextW(strTemp);
		nTemp = _ttoi(strTemp);

		if (nTemp > m_mLimit )
		{
			nTemp -= 1;
			strTemp.Format(_T("%d"), nTemp);
			SetWindowTextW(strTemp);
		}
	}
	CStatic::OnRButtonUp(nFlags, point);
}
