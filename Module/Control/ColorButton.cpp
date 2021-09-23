#include "stdafx.h"
#include "ColorButton.h"


CColorButton::CColorButton()
{

}


CColorButton::~CColorButton()
{
}

BEGIN_MESSAGE_MAP(CColorButton, CButton)
END_MESSAGE_MAP()

void CColorButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	// TODO:  지정된 항목을 그리는 코드를 추가합니다.
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

	UINT nState = lpDrawItemStruct->itemState;
	CRect btnRect;
	btnRect.CopyRect(&lpDrawItemStruct->rcItem);

	CString strCaption;
	this->GetWindowText(strCaption);

	this->DrawBkGround(pDC, btnRect, GetBackGroundColor());
	this->DrawCaption(pDC, btnRect, GetForeColor(), strCaption);
	pDC->DrawEdge(btnRect, EDGE_RAISED, BF_RECT);

	if (nState & ODS_FOCUS){
		if (nState & ODS_SELECTED){
			pDC->DrawEdge(btnRect, EDGE_SUNKEN, BF_RECT);
		}
	}
	else if (nState & ODS_DISABLED){
		this->DrawCaption(pDC, btnRect, GetDisabledColor(), strCaption);
	}
}

void CColorButton::DrawBkGround(CDC *pDC, CRect rect, COLORREF color)
{
	pDC->FillSolidRect(rect, color);
}

void CColorButton::DrawCaption(CDC *pDC, CRect rect, COLORREF color, const CString& str)
{
	const COLORREF oldcolor = pDC->SetTextColor(color);
	pDC->SetBkMode(TRANSPARENT);
	pDC->DrawText(str, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	pDC->SetTextColor(oldcolor);
}
