// VelocityListCtrl.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CommonListCtrl.h"
#include "CheckButton.h"
#include "AdvancedEditCell.h"
#include "WizardCombo.h"

#include <iostream> 
using namespace std;
#include <fstream>


#define IDC_PAGEEDITCELL		10001
#define IDC_COMBOBOXONLISTVIEW	10002
#define IDC_ADVANCEDEDITCELL	10003
// CWeldingMethodListCtrl

//IMPLEMENT_DYNAMIC(CWeldingMethodListCtrl, CListCtrl)

CCommonListCtrl::CCommonListCtrl(int nIsFlatness /*= FALSE*/)
{
	m_nIsFlatness = nIsFlatness;

	HitItem = -1;
	m_nMaxRow = 0;

	m_nSelectedItemNumber = -1;
	m_nSelectedSubItemNumber = -1;

	m_nSelectedItemEndNumber = -1;
	m_nSelectedSubItemEndNumber = -1;

	m_pEdit = NULL;
	m_pButton = NULL;

	m_nMaxCol = 0;
	m_nMaxRow = 0;

	m_bClipboardOnOff = TRUE;
	//BkColorForSubItem(2, 2, 1, 2);

}

CCommonListCtrl::~CCommonListCtrl()
{
	//if (m_pEdit != NULL)
	//	delete m_pEdit;

	//if(m_pCombo != NULL)
	//	delete m_pCombo;
}

BEGIN_MESSAGE_MAP(CCommonListCtrl, CListCtrlCustomDraw)
	//{{AFX_MSG_MAP(CWeldingMethodListCtrl)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT, OnEndLabelEdit)
	ON_WM_KEYDOWN()
	ON_WM_KILLFOCUS()
	ON_WM_DRAWITEM()
	ON_MESSAGE(WM_CHECKSTATUS, &CCommonListCtrl::OnCheckStatus)
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWeldingMethodListCtrl message handlers

BOOL CCommonListCtrl::IsDraw()
{
	return true;
}

BOOL CCommonListCtrl::OnDraw(CDC* pDC)
{


	return false; // do default drawing as well
}

BOOL CCommonListCtrl::IsNotifyItemDraw()
{
	return true;
}

BOOL CCommonListCtrl::IsNotifySubItemDraw(int /*nItem*/, UINT /*nState*/, LPARAM /*lParam*/)
{
	return true;
}

COLORREF CCommonListCtrl::TextColorForSubItem(int nItem, int nSubItem, UINT /*nState*/, LPARAM /*lParam*/)
{
	COLORREF crTemp;
	if (nItem >= m_nSelectedItemNumber && nItem <= m_nSelectedItemEndNumber &&
		nSubItem >= m_nSelectedSubItemNumber && nSubItem <= m_nSelectedSubItemEndNumber)
	{
		crTemp = RGB(255, 255, 255);
	}
	else
	{
		crTemp = m_stCellInfo[nSubItem].crTextColorInfo;
	}

	return crTemp;
	//if (0 == nSubItem) return RGB(0, 0, 0);
	//else return CLR_DEFAULT;
}

COLORREF CCommonListCtrl::BkColorForSubItem(int nItem, int nSubItem, UINT /*nState*/, LPARAM /*lParam*/)
{
	COLORREF crTemp;
	if (nItem >= m_nSelectedItemNumber && nItem <= m_nSelectedItemEndNumber &&
		nSubItem >= m_nSelectedSubItemNumber && nSubItem <= m_nSelectedSubItemEndNumber)
	{
		crTemp = RGB(198, 198, 198);
	}
	else
	{
		crTemp = m_stCellInfo[nSubItem].crBkColorInfo;
	}

	return crTemp;
	//if (0 == nSubItem)
	//{
	//	return RGB(215, 215, 215);
	//}
	//else if (1 == nSubItem)
	//{
	//	return RGB(126, 205, 150);
	//}

	//else
	//{
	//	return CLR_DEFAULT;
	//}
}

///#################################################################///
///							For EditCell							///
///#################################################################///
void CCommonListCtrl::Resize(int cx, int cy)
{
	CRect Rect(0, 0, cx, cy);
	MoveWindow(&Rect);
	InvalidateRect(Rect);
	SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
}
int CCommonListCtrl::HitTestEx(CPoint& Point, int* pColumn)
{
	int ColumnNum = 0;
	int Row = HitTest(Point, NULL);

	HitItem = Row;

	if (pColumn) *pColumn = 0;

	// Make sure that the ListView is in LVS_REPORT
	if ((GetWindowLong(m_hWnd, GWL_STYLE) & LVS_TYPEMASK) != LVS_REPORT)
		return Row;

	// Get the top and bottom row visible
	Row = GetTopIndex();
	int Bottom = Row + GetCountPerPage();
	if (Bottom > GetItemCount())
		Bottom = GetItemCount();

	// Get the number of columns
	CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0);
	int nColumnCount = pHeader->GetItemCount();

	// Loop through the visible rows
	for (; Row <= Bottom; Row++)
	{
		// Get bounding rect of item and check whether point falls in it.
		CRect Rect;
		GetItemRect(Row, &Rect, LVIR_BOUNDS);
		if (Rect.PtInRect(Point))
		{
			// Now find the column
			for (ColumnNum = 0; ColumnNum < nColumnCount; ColumnNum++)
			{
				int ColWidth = GetColumnWidth(ColumnNum);
				if (Point.x >= Rect.left && Point.x <= (Rect.left + ColWidth))
				{
					if (pColumn)
						*pColumn = ColumnNum;
					return Row;
				}
				Rect.left += ColWidth;
			}
		}
	}
	return -1;
}

CAdvancedEditCell* CCommonListCtrl::EditSubItem(int Item, int Column)
{
	// The returned pointer should not be saved

	if (Column == 0) return NULL;

	// Make sure that the item is visible
	if (!EnsureVisible(Item, TRUE))
	{
		InsertItemEx(Item);
		if (!EnsureVisible(Item, TRUE))
			return NULL;
	}

	// Make sure that nCol is valid
	CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0);
	int nColumnCount = pHeader->GetItemCount();
	if (Column >= nColumnCount || GetColumnWidth(Column) < 5)
		return NULL;

	// Get the column offset
	int Offset = 0;
	for (int iColumn = 0; iColumn < Column; iColumn++)
		Offset += GetColumnWidth(iColumn);

	CRect Rect;
	GetItemRect(Item, &Rect, LVIR_BOUNDS);

	// Now scroll if we need to expose the column
	CRect ClientRect;
	GetClientRect(&ClientRect);
	if (Offset + Rect.left < 0 || Offset + Rect.left > ClientRect.right)
	{
		CSize Size;
		if (Offset + Rect.left > 0)
			Size.cx = -(Offset - Rect.left);
		else
			Size.cx = Offset - Rect.left;
		Size.cy = 0;
		Scroll(Size);
		Rect.left -= Size.cx;
	}

	// Get Column alignment
	LV_COLUMN lvCol;
	lvCol.mask = LVCF_FMT;
	GetColumn(Column, &lvCol);
	DWORD dwStyle;
	if ((lvCol.fmt & LVCFMT_JUSTIFYMASK) == LVCFMT_LEFT)
		dwStyle = ES_LEFT;
	else if ((lvCol.fmt & LVCFMT_JUSTIFYMASK) == LVCFMT_RIGHT)
		dwStyle = ES_RIGHT;
	else dwStyle = ES_CENTER;

	Rect.top += 2;
	Rect.bottom -= 2;

	Rect.left += Offset;
	Rect.right = Rect.left + GetColumnWidth(Column);
	if (Rect.right > ClientRect.right)
		Rect.right = ClientRect.right;

	dwStyle |= WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL;


	if (Column >= 1)
	{
		//CAdvancedEditCell *pEdit = new CAdvancedEditCell(this, Item, Column, GetItemText(Item, Column), 1);
		m_pEdit = new CAdvancedEditCell(this, Item, Column, GetItemText(Item, Column), 1);
		m_pEdit->Create(dwStyle, Rect, this, IDC_ADVANCEDEDITCELL);

		return m_pEdit;
	}

	return NULL;
}

//void CCommonListCtrl::OnEndLabelEdit(NMHDR* pNMHDR, LRESULT* pResult)
//{
//	CString strTemp;
//	LV_DISPINFO *plvDispInfo = (LV_DISPINFO *)pNMHDR;
//	LV_ITEM	*plvItem = &plvDispInfo->item;
//	BOOL bModify = FALSE;
//
//	if (m_pEdit != NULL)
//	{
//		m_pEdit->GetWindowTextW(strTemp);
//		bModify = m_pEdit->m_bModifyOk;
//		if (plvItem->iItem >= 0 && plvItem->iSubItem >= 1)
//		{
//			if (bModify == TRUE)
//			{
//				SetItemText(plvItem->iItem, plvItem->iSubItem, strTemp);
//				//HighlightSelectedItem();
//				
//			}
//		}
//	}
//	else
//	{
//		if (plvItem->iItem >= 0 && plvItem->iSubItem >= 1)
//		{
//				SetItemText(plvItem->iItem, plvItem->iSubItem, plvItem->pszText);
//				//HighlightSelectedItem();
//		}
//	}
//
//	m_pEdit = NULL;
//
//	
//	RedrawItems(GetTopIndex(), GetTopIndex() + GetCountPerPage());
//
//	*pResult = FALSE;
//	//HighlightSelectedItem();
//}

void CCommonListCtrl::OnEndLabelEdit(NMHDR* pNMHDR, LRESULT* pResult)
{
	CString strTemp;
	LV_DISPINFO *plvDispInfo = (LV_DISPINFO *)pNMHDR;
	LV_ITEM	*plvItem = &plvDispInfo->item;

	if (plvItem->iItem >= 0 && plvItem->iSubItem >= 1)
	{
		SetItemText(plvItem->iItem, plvItem->iSubItem, plvItem->pszText);

		::SendMessage(GetParent()->m_hWnd, WM_END_EDIT, (WPARAM)m_nSelectedItemNumber, (LPARAM)plvItem);
	}

	RedrawItems(GetTopIndex(), GetTopIndex() + GetCountPerPage());

	*pResult = FALSE;

	//HighlightSelectedItem();
}

///#################################################################///
///							For ComboBox							///
///#################################################################///
CWizardCombo* CCommonListCtrl::ShowComboList(int nItem, int nCol, CString StrData)
{
	CRect rect;
	int offset = 0;

	// Make sure that the item is visible
	if (!EnsureVisible(nItem, TRUE)) return NULL;
	GetSubItemRect(nItem, nCol, LVIR_BOUNDS, rect);

	// Now scroll if we need to expose the column
	CRect rcClient;
	GetClientRect(rcClient);
	if (offset + rect.left < 0 || offset + rect.left > rcClient.right) {
		CSize size;
		size.cx = offset + rect.left;
		size.cy = 0;
		Scroll(size);
		rect.left -= size.cx;
	}

	rect.left += offset;
	rect.right = rect.left + GetColumnWidth(nCol);
	if (rect.right > rcClient.right) rect.right = rcClient.right;

	rect.bottom += m_stComboInfo[nCol].nDataQuan * rect.Height();
	//rect.bottom += 30 * rect.Height();
	DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_DISABLENOSCROLL;


	//CWizardCombo *pList = new CWizardCombo(nItem, nCol, StrData, 0);
	//*pList = new CWizardCombo(nItem, nCol, StrData, 0);
	//
	//pList->Create(dwStyle, rect, this, IDC_COMBOBOXONLISTVIEW);

	//pList->ResetContent();
	//for (int i = 0; i < m_stComboInfo[nCol].nDataQuan; i++)
	//{
	//	pList->AddString(m_stComboInfo[nCol].nListData[i]);
	//}

	//pList->ModifyStyleEx(0, WS_EX_CLIENTEDGE);
	//pList->ShowDropDown();

	m_pCombo = new CWizardCombo(nItem, nCol, StrData, 0);

	m_pCombo->Create(dwStyle, rect, this, IDC_COMBOBOXONLISTVIEW);

	m_pCombo->ResetContent();
	for (int i = 0; i < m_stComboInfo[nCol].nDataQuan; i++)
	{
		m_pCombo->AddString(m_stComboInfo[nCol].nListData[i]);
	}
	m_pCombo->SetMinVisibleItems(m_stComboInfo[nCol].nDataQuan);

	m_pCombo->ModifyStyleEx(0, WS_EX_CLIENTEDGE);
	m_pCombo->ShowDropDown();

	m_bIsCombox = TRUE;


	// The returned pointer should not be saved
	return m_pCombo;
}

void CCommonListCtrl::InsertNumber(int Item, int Column)
{
	CString ItemNum, NextItemString;

	ItemNum.Format(_T("%d"), Item + 1);

	NextItemString = GetItemText(Item + 1, 0);

	if (ItemNum != NextItemString)
	{
		InsertItem(Item + 1, ItemNum);
		m_nMaxRow++;
	}
}

int CCommonListCtrl::InsertItemEx(int Item)
{
	CString ItemNum;
	ItemNum.Format(_T("%d"), Item + 1);

	int Result = InsertItem(Item + 1, ItemNum);

	CString ItemVal, Temp;

	SetItemText(Item, 1, ItemVal);
	SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);

	return Result;
}

void CCommonListCtrl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (GetFocus() != this)
		SetFocus();

	CListCtrl::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CCommonListCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (GetFocus() != this)
		SetFocus();

	CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
}



void CCommonListCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default	

	//if (nChar == VK_DELETE)
	//{
	//	if (HitItem != -1)
	//	{
	//		int Index = HitItem;//HitTestEx (HitPt, &ColNum);
	//		if (m_nInsertItemCount == Index + 1)
	//		{
	//			DeleteItem(Index);

	//			if (m_nInsertItemCount > 0) m_nInsertItemCount--;
	//		}
	//		else
	//		{
	//			CString Str;
	//			int Interval = m_nInsertItemCount - (Index + 1);

	//			DeleteItem(Index);

	//			for (int i = 0; i<Interval; i++)
	//			{
	//				Str.Format(_T("%d"), Index);
	//				SetItemText(Index++, 0, Str);
	//			}

	//			if (m_nInsertItemCount > 0) m_nInsertItemCount--;
	//		}
	//	}
	//}

	//CListCtrl::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CCommonListCtrl::SetListColumn(CString *strData, int* nSize, int nQuan, COLORREF *crBkColorInfo, COLORREF *crTextColorInfo, int *nInputMethod)
{
	LV_COLUMN lvcolumn;
	TCHAR listcolumn[20];

	m_nMaxCol = nQuan;

	for (int i = 0; i < m_nMaxCol; i++)
	{
		//정보 저장.
		m_stCellInfo[i].ColName = strData[i];
		m_stCellInfo[i].nColSize = nSize[i];
		m_stCellInfo[i].crTextColorInfo = crTextColorInfo[i];
		m_stCellInfo[i].crBkColorInfo = crBkColorInfo[i];
		m_stCellInfo[i].nInputMethod = nInputMethod[i];

		//Setting.
		wsprintf(listcolumn, _T("%s"), strData[i]);

		lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
		lvcolumn.fmt = LVCFMT_CENTER;
		lvcolumn.pszText = (LPWSTR)listcolumn;
		lvcolumn.iSubItem = i;
		lvcolumn.cx = nSize[i];

		InsertColumn(i, &lvcolumn);
		if (i == 0)
		{
			SetColumn(i, &lvcolumn);
		}
	}
}

BOOL CCommonListCtrl::AddListData(int nRow, CString *strData)
{
	m_nSelectedItemNumber = -1;
	m_nSelectedSubItemNumber = -1;

	m_nSelectedItemEndNumber = -1;
	m_nSelectedSubItemEndNumber = -1;

	LV_ITEM lvitem;
	int curitem = 0;
	CString Str;

	TCHAR  chData[256];

	lvitem.mask = LVIF_TEXT;

	for (int j = 0; j < m_nMaxCol; j++)
	{
		lvitem.iItem = (j == 0) ? m_nMaxRow : curitem;
		lvitem.iSubItem = j;

		wsprintf(chData, _T("%s"), strData[j]);

		switch (j)
		{
		case 0:
			lvitem.pszText = (LPWSTR)chData;
			curitem = InsertItem(&lvitem);
			break;

		default:
			lvitem.pszText = (LPWSTR)chData;
			SetItem(&lvitem);
			break;
		}
	}

	//SetScroll();

	m_nMaxRow++;

	return TRUE;
}



#define nColNum	12
void CCommonListCtrl::AddListColumn()
{
	LV_COLUMN lvcolumn;
	TCHAR *listcolumn[nColNum] = { _T("No"), _T("ID"), _T("Order"), _T("Use"), _T("Size Y"), _T("Pos Y"), _T("Offset X"), _T("Offset Y"), _T("Strech X"), _T("Strech Y"), _T("Cell X"), _T("Cell Y") };
	int width[nColNum] = { 40        , 200       , 50              , 50          , 90           , 90            , 90               ,90                , 90               , 90               , 50                      , 50 };

	for (int i = 0; i < nColNum; i++)
	{
		lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
		lvcolumn.fmt = LVCFMT_CENTER;
		lvcolumn.pszText = (LPWSTR)listcolumn[i];
		lvcolumn.iSubItem = i;
		lvcolumn.cx = width[i];

		InsertColumn(i, &lvcolumn);
	}
}
BOOL CCommonListCtrl::DeleteAllListData()
{
	if (m_nMaxRow < 1) return FALSE;

	DeleteAllItems();

	HitItem = -1;
	m_nMaxRow = 0;
	m_nSelectedItemNumber = -1;
	m_nSelectedSubItemNumber = -1;
	m_nSelectedItemEndNumber = -1;
	m_nSelectedSubItemEndNumber = -1;

	return TRUE;
}

BOOL CCommonListCtrl::DeleteListData(int nNo)
{
	int i;
	int nCount;
	TCHAR chData[256];
	LV_ITEM lvitem;

	nCount = GetItemCount();
	if (nNo >= nCount || nNo < 0) return FALSE;

	DeleteItem(nNo);

	lvitem.mask = LVIF_TEXT;
	lvitem.iSubItem = 0;

	for (i = nNo; i < nCount; i++)
	{
		//_stprintf(LvItem.pszText, _T("%d"), i);
		wsprintf(chData, _T("%d"), i + 1);

		lvitem.iItem = i;
		lvitem.pszText = (LPWSTR)chData;

		SetItem(&lvitem);
	}

	//SetScroll();

	SetFocus();

	if ((nNo - 1) >= 0)
	{
		SetItemState(nNo, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	}

	m_nMaxRow--;

	return TRUE;
}

int CCommonListCtrl::SaveListData(BOOL bIsAuto /*= FALSE*/)
{
	return 1;
}

void CCommonListCtrl::AddOffsetListData(int nIndex[2], double dPosData[6])
{
	TCHAR  chData[10][256];

	for (int i = nIndex[0]; i <= nIndex[1]; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			SetItemText(i, j + 2, chData[j]);
		}
	}
}

BOOL CCommonListCtrl::UpdateListData(int nRow, CString *strData)
{
	//m_nSelectedItemNumber = -1;
	//m_nSelectedSubItemNumber = -1;
	//m_nSelectedItemEndNumber = -1;
	//m_nSelectedSubItemEndNumber = -1;
	int curitem = 0;
	CString Str;

	for (int i = 0; i < m_nMaxCol; i++)
	{
		Str.Format(_T("%s"), strData[i]);
		SetItemText(nRow, i, Str);
	}

	//SetScroll();	//SetFocus();

	//SetFocus();

	//SetItemState(nRow, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);

	return TRUE;
}

int CCommonListCtrl::GetMaxListCount()
{
	return m_nMaxRow;
}

BOOL CCommonListCtrl::GetListData(int nRow, CString *strData)
{
	if (nRow < 0 || nRow > m_nMaxRow) return FALSE;

	for (int i = 0; i < m_nMaxCol; i++)
	{
		strData[i] = (LPCTSTR)GetItemText(nRow, i);
	}

	return TRUE;
}

BOOL CCommonListCtrl::GetListAllData(CString *strData)
{
	INT nDataCnt = 0;
	for (int j = 0; j < m_nMaxRow; j++)
	{
		for (int i = 0; i < m_nMaxCol; i++)
		{
			strData[nDataCnt] = (LPCTSTR)GetItemText(j, i);
			nDataCnt++;
		}
	}

	return TRUE;
}

BOOL CCommonListCtrl::IsReal(CString Str)
{
	TCHAR ch;

	int nDotCount = 0;
	int nLength = Str.GetLength();
	if (nLength < 1) return FALSE;

	for (int i = 0; i < nLength; i++)
	{
		ch = Str.GetAt(i);

		if (i == 0 && (ch == '-' || ch == '+'));
		else if (i != 0 && ch == '.')
		{
			if (++nDotCount > 1) return FALSE;
		}
		else if (isdigit(ch) == 0)
		{
			return FALSE;
		}
	}

	return TRUE;
}

void CCommonListCtrl::HighlightSelectedItem()
{
	if (m_nSelectedItemNumber < 0) return;

	SetItemState(m_nSelectedItemNumber, LVIS_SELECTED, LVIS_SELECTED | LVIS_FOCUSED);
}

int CCommonListCtrl::GetItemHeight()
{
	CRect ItemRect;
	GetSubItemRect(1, 1, LVIR_BOUNDS, ItemRect);
	return ItemRect.bottom - ItemRect.top;
}

void CCommonListCtrl::SetScroll()
{
	SCROLLINFO sinfo;
	sinfo.cbSize = sizeof(sinfo);
	sinfo.fMask = SIF_RANGE;//SIF_TRACKPOS;
	::GetScrollInfo(m_hWnd, SB_VERT, &sinfo);

	int nItemHeight = GetItemHeight();
	int Pos = m_nMaxRow;//m_nSelectedItem[0];

	int iY = ((int)Pos - (int)GetScrollPos(SB_VERT)) * nItemHeight;
	//GetListCtrl().Scroll(CSize(0, iY)); 
	Scroll(CSize(0, iY));
}

void CCommonListCtrl::OnKillFocus(CWnd* pNewWnd)
{
	CListCtrl::OnKillFocus(pNewWnd);
	//HighlightSelectedItem();
}

void CCommonListCtrl::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: Add your message handler code here and/or call default

	CListCtrl::OnDrawItem(nIDCtl, lpDrawItemStruct);
}


void CCommonListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	int iItem = lpDrawItemStruct->itemID;
	CRect subRect = lpDrawItemStruct->rcItem;
	subRect.right = subRect.left;

	if (m_nSelectedItemNumber == iItem)
	{
		CDC dc;
		dc.Attach(lpDrawItemStruct->hDC);
		COLORREF col = RGB(255, 220, 220);

		dc.FillSolidRect(&(lpDrawItemStruct->rcItem), col);
		dc.Detach();
	}
	else
	{
		CDC dc;
		dc.Attach(lpDrawItemStruct->hDC);
		COLORREF col = RGB(255, 255, 255);
		dc.FillSolidRect(&(lpDrawItemStruct->rcItem), col);
		dc.Detach();
	}

	for (int i = 0; i < 5; i++)
	{
		subRect.right += GetColumnWidth(i);
		//		DrawText(lpDrawItemStruct->hDC, GetItemText(iItem, i), strlen(GetItemText(iItem, i)), subRect,  DT_CENTER|DT_VCENTER);
		subRect.left = subRect.right;
	}
}

BOOL CCommonListCtrl::PreTranslateMessage(MSG* pMsg)
{
	CString strTemp = _T("");
	CString strArray[100] = { _T(""), };
	INT nResultRowCnt = -1;
	INT nResultColCnt = -1;

	if (m_bClipboardOnOff == TRUE)
	{
		//Ctrl + C
		if (pMsg->wParam == 3)
		{
			ListDataMultiRead(strTemp);
			CopyToClipboard(strTemp);
		}

		//Ctrl + V
		if (pMsg->wParam == 22)
		{
			CopyToApp(strTemp);
			TapDataParsing(strTemp, strArray, &nResultRowCnt, &nResultColCnt);
			ClipBoradDataMultiWrite(strArray, nResultRowCnt, nResultColCnt);
		}
	}

	if ((pMsg->message == WM_KEYDOWN))
	{
		if (pMsg->wParam == VK_ESCAPE)
		{

		}
	}
	return CListCtrl::PreTranslateMessage(pMsg);
}

BOOL CCommonListCtrl::ListDataMultiRead(CString &strResult)
{
	CString strTemp = _T("");
	for (int i = m_nSelectedItemNumber; i <= m_nSelectedItemEndNumber; i++)
	{
		for (int j = m_nSelectedSubItemNumber; j <= m_nSelectedSubItemEndNumber; j++)
		{
			strTemp = GetItemText(i, j);
			strResult += strTemp;
			if ((m_nSelectedSubItemEndNumber) != j)
				strResult += _T('\t');
		}
		if ((m_nSelectedItemEndNumber) != i)
		{
			strResult += _T('\r');
			strResult += _T('\n');
		}
	}

	return TRUE;
}


int CCommonListCtrl::LoadPointData(char* pchPathName)
{

	return TRUE;
}

LRESULT CCommonListCtrl::OnCheckStatus(WPARAM wParam, LPARAM lParam)
{
	//m_nCheckStatus[wParam - 1] = lParam;

	return TRUE;
}

BOOL CCommonListCtrl::SetColData(int nSubNum, int nQuan, CString* strData)
{
	//m_stComboInfo[nSubNum].bUse = TRUE;
	m_stComboInfo[nSubNum].nDataQuan = nQuan;

	for (int i = 0; i < nQuan; i++)
	{
		m_stComboInfo[nSubNum].nListData[i] = strData[i];
	}

	return TRUE;
}


bool CCommonListCtrl::CopyToClipboard(CString &strText)
{
	INT nMemSize = strText.GetLength() + 1;
	if (OpenClipboard())
	{
		EmptyClipboard();

		HGLOBAL hClipboardData = GlobalAlloc(GMEM_DDESHARE, nMemSize);

		char* pchData;
		pchData = (char*)GlobalLock(hClipboardData);

		sprintf_s(pchData, nMemSize, "%S", (LPSTR)(LPCTSTR)strText);

		GlobalUnlock(hClipboardData);

		SetClipboardData(CF_TEXT, hClipboardData);
		CloseClipboard();

		return true;
	}

	return false;
}

bool CCommonListCtrl::CopyToApp(CString &strText)
{
	if (OpenClipboard())
	{
		//EmptyClipboard();

		HGLOBAL hClipboardData = GlobalAlloc(GMEM_DDESHARE, 4096);

		hClipboardData = GetClipboardData(CF_TEXT);

		char* pchData;
		pchData = (char*)GlobalLock(hClipboardData);

		strText.Format(_T("%s"), (CString)(LPSTR)pchData);

		GlobalUnlock(hClipboardData);

		CloseClipboard();

		return true;
	}

	return false;
}

BOOL CCommonListCtrl::TapDataParsing(CString strText, CString *strResult, INT *nResultRowQuan, INT *nResultColQuan)
{
	CString strRowTemp = _T(""), strColTemp = _T("");
	INT nColQuan = 0;
	INT nRowQuan = 0;
	INT nQuan = 0;
	while (AfxExtractSubString(strRowTemp, strText, nRowQuan, _T('\r\n')))
	{
		nColQuan = 0;
		while (AfxExtractSubString(strColTemp, strRowTemp, nColQuan, _T('\t')))
		{
			strResult[nQuan] = strColTemp.TrimLeft();
			nColQuan++;
			nQuan++;
		}

		nRowQuan++;
	}

	if (nColQuan == 0 || nRowQuan == 0)
		return FALSE;

	*nResultRowQuan = nRowQuan;
	*nResultColQuan = nColQuan;

	return TRUE;
}

BOOL CCommonListCtrl::ClipBoradDataMultiWrite(CString *strResult, INT nResultRowQuan, INT nResultColQuan)
{
	for (int i = 0; i < nResultRowQuan; i++)
	{
		for (int j = 0; j < nResultColQuan; j++)
		{
			SetItemText(m_nSelectedItemNumber + i, m_nSelectedSubItemNumber + j, strResult[(i * nResultColQuan) + j]);
		}
	}

	return TRUE;
}

void CCommonListCtrl::OnLButtonDown(UINT nFlags, CPoint Point)
{
	//sunghaklee
	if (m_nIsFlatness == TRUE)
	{
		CListCtrl::OnLButtonDown(nFlags, Point);
		
		//int i;
		int  Index;
		int ColNum;
		CString Str;

		if ((Index = HitTestEx(Point, &ColNum)) != -1)
		{
			if (ColNum > 0 && ColNum < 5)
			{
				//m_nSubItemNum = ColNum;
				DWORD dwStyle = GetWindowLong(m_hWnd, GWL_STYLE);
				dwStyle |= LVS_EDITLABELS;
				SetWindowLong(m_hWnd, GWL_STYLE, dwStyle);
				RedrawItems(GetTopIndex(), GetTopIndex() + GetCountPerPage());
				m_nSelectedItemNumber = Index;
				m_nSelectedItemEndNumber = Index;
				

				m_nSelectedSubItemNumber = ColNum;
				m_nSelectedSubItemEndNumber = ColNum;

				EditSubItem(Index, ColNum);
			}
		}
	}
	else
	{

		int  Index;
		int ColNum;

		CString Str;
		Index = HitTestEx(Point, &ColNum);
		m_nSelectedItemNumber = Index;
		m_nSelectedItemEndNumber = Index;
		//if (ColNum == 0)
		//	ColNum++;

		m_nSelectedSubItemNumber = ColNum;
		m_nSelectedSubItemEndNumber = ColNum;

		SetFocus();
		SetCapture();
	}
}

void CCommonListCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

}

void CCommonListCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (GetCapture())
	{
		int  Index;
		int ColNum;
		int nTemp;
		CString Str;
		Index = HitTestEx(point, &ColNum);
		m_nSelectedItemEndNumber = Index;

		//if (ColNum == 0)
		//	ColNum++;

		m_nSelectedSubItemEndNumber = ColNum;

		if (m_nSelectedItemNumber > m_nSelectedItemEndNumber)
		{
			nTemp = m_nSelectedItemNumber;
			m_nSelectedItemNumber = m_nSelectedItemEndNumber;
			m_nSelectedItemEndNumber = nTemp;
		}

		if (m_nSelectedSubItemNumber > m_nSelectedSubItemEndNumber)
		{
			nTemp = m_nSelectedSubItemNumber;
			m_nSelectedSubItemNumber = m_nSelectedSubItemEndNumber;
			m_nSelectedSubItemEndNumber = nTemp;
		}

		ReleaseCapture();
		Invalidate(FALSE);
	}

	::SendMessage(GetParent()->m_hWnd, WM_CLICK, (WPARAM)m_nSelectedItemNumber, (LPARAM)this);

	//CListCtrl::OnLButtonUp(nFlags, point);
}

void CCommonListCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	int  Index;
	int ColNum;

	CString Str;
	if ((Index = HitTestEx(point, &ColNum)) != -1)
	{
		//일반
		if (m_stCellInfo[ColNum].nInputMethod == eMETHOD_NORMAL)
		{
			DWORD dwStyle = GetWindowLong(m_hWnd, GWL_STYLE);
			dwStyle &= ~LVS_EDITLABELS;

			m_strPreDirection = GetItemText(Index, 1);

			Str = GetItemText(Index, ColNum);
			SetWindowLong(m_hWnd, GWL_STYLE, dwStyle);
			//m_pEdit = EditSubItem(Index, ColNum);
			EditSubItem(Index, ColNum);

		}
		//콤보
		if (m_stCellInfo[ColNum].nInputMethod == eMETHOD_COMBO)
		{
			DWORD dwStyle = GetWindowLong(m_hWnd, GWL_STYLE);
			dwStyle &= ~LVS_EDITLABELS;

			m_strPreDirection = GetItemText(Index, 1);

			Str = GetItemText(Index, ColNum);
			SetWindowLong(m_hWnd, GWL_STYLE, dwStyle);
			//m_pCombo = ShowComboList(Index, ColNum, Str);
			ShowComboList(Index, ColNum, Str);
		}
	}

	//CListCtrl::OnLButtonDblClk(nFlags, point);
	::SendMessage(GetParent()->m_hWnd, WM_DBLCLK, (WPARAM)m_nSelectedItemNumber, (LPARAM)this);
}

void CCommonListCtrl::OnRButtonDown(UINT nFlags, CPoint point)
{
	int  Index;
	int ColNum;
	int nTemp;
	CString Str;
	Index = HitTestEx(point, &ColNum);
	m_nSelectedItemEndNumber = Index;

	if (ColNum == 0)
		ColNum++;
	m_nSelectedSubItemEndNumber = ColNum;

	if (m_nSelectedItemNumber > m_nSelectedItemEndNumber)
	{
		nTemp = m_nSelectedItemNumber;
		m_nSelectedItemNumber = m_nSelectedItemEndNumber;
		m_nSelectedItemEndNumber = nTemp;
	}

	if (m_nSelectedSubItemNumber > m_nSelectedSubItemEndNumber)
	{
		nTemp = m_nSelectedSubItemNumber;
		m_nSelectedSubItemNumber = m_nSelectedSubItemEndNumber;
		m_nSelectedSubItemEndNumber = nTemp;
	}

	Invalidate(FALSE);
}



CString CCommonListCtrl::LoadDataFromCsv(CString strFilePath, CString *strResult, int *nRowQuan)
{
	CStdioFile file;
	CFileException ex;
	//char szContent[10000] = { 0, };

	int nRowCnt = 0;
	int nTrimPos = 0;
	CString szMsg;
	CString strData = _T("");
	CString strPath = strFilePath;
	CString strContent;
	CString rString;
	int nDataCount = 0;
	int nSubString = 0;
	CString strRowData[20];

	for (int i = 0; i < 20; i++)
	{
		strRowData[i] = _T("");
	}

	CFileDialog fOpenDlg(TRUE, _T("*.csv"), NULL, CFile::shareDenyNone | OFN_OVERWRITEPROMPT, _T("CSV Files(*.csv)|*.csv|"), NULL);

	fOpenDlg.m_pOFN->lpstrTitle = _T("File Load");
	fOpenDlg.m_pOFN->lpstrInitialDir = strPath;

	if (fOpenDlg.DoModal() == IDOK)
	{
		DeleteAllItems();

		strPath = fOpenDlg.GetPathName();
		if (file.Open(strPath, CFile::CFile::modeRead, &ex))
		{
			file.ReadString(strContent);		//First Line Pass

			while (file.ReadString(strContent)) //ÆÄÀÏÀ» ÇÑ ¶óÀÎ¾¿ ÀÐ¾î¶ó
			{
				//strContent.TrimRight(_T('/r/n'));
				while (AfxExtractSubString(rString, strContent, nSubString, ','))
				{
					strResult[nDataCount] = rString;
					nDataCount++;

					strRowData[nSubString] = rString;
					nSubString++;
				}

				AddListData(nRowCnt, strRowData);
				nRowCnt++;
				nSubString = 0;
			}

			m_nMaxRow = nRowCnt;
			*nRowQuan = m_nMaxRow;

			file.Close(); //ÆÄÀÏ ´Ý±â

		}
		else
		{
			AfxMessageBox(_T("File alread opened by another process."));
		}

	}

	return strPath;
}


CString CCommonListCtrl::LoadDataFromCsvEx(CString strFilePath, CString *strResult, int *nRowQuan)
{
	CStdioFile file;
	CFileException ex;
	//char szContent[10000] = { 0, };

	int nRowCnt = 0;
	int nTrimPos = 0;
	CString szMsg;
	CString strData = _T("");
	CString strPath = strFilePath;
	CString strContent;
	CString rString;
	int nDataCount = 0;
	int nSubString = 0;
	CString strRowData[20];

	for (int i = 0; i < 20; i++)
	{
		strRowData[i] = _T("");
	}

	//if (fOpenDlg.DoModal() == IDOK)
	//{
	DeleteAllItems();

	if (file.Open(strPath, CFile::CFile::modeRead, &ex))
	{
		file.ReadString(strContent);							//First Line Pass

		while (file.ReadString(strContent))					//ÆÄÀÏÀ» ÇÑ ¶óÀÎ¾¿ ÀÐ¾î¶ó
		{
			//strContent.TrimRight(_T('/r/n'));
			while (AfxExtractSubString(rString, strContent, nSubString, ','))
			{
				strResult[nDataCount] = rString;
				nDataCount++;

				strRowData[nSubString] = rString;
				nSubString++;
			}

			AddListData(nRowCnt, strRowData);
			nRowCnt++;
			nSubString = 0;
		}

		m_nMaxRow = nRowCnt;
		*nRowQuan = m_nMaxRow;

		file.Close(); //ÆÄÀÏ ´Ý±â

	}
	else
	{
		AfxMessageBox(_T("File alread opened by another process."));
	}


	return strPath;
}


CString CCommonListCtrl::SaveDataToCsv(CString strFilePath)
{
	SYSTEMTIME st;
	CStdioFile file;
	CFileException ex;
	GetLocalTime(&st);
	CString szMsg = _T("");
	CString strPath = strFilePath;
	//szMsg.Format(_T("FrameMeasurementList_%04d%02d%02d_%02d%02d%02d"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	CFileDialog fOpenDlg(FALSE, _T("*.csv"), szMsg, OFN_OVERWRITEPROMPT, _T("CSV Files(*.csv)|*.csv|"), NULL);

	fOpenDlg.m_pOFN->lpstrTitle = _T("File Save");
	fOpenDlg.m_pOFN->lpstrInitialDir = strPath;

	if (fOpenDlg.DoModal() == IDOK)
	{
		strPath = fOpenDlg.GetPathName();
		// Do something useful here

		if (!file.Open(strPath, CFile::modeCreate | CFile::modeReadWrite, &ex))
			file.Open(strPath, CFile::modeReadWrite, &ex);

		ColDataWrite(&file);

		for (int i = 0; i < m_nMaxRow; i++)
		{
			szMsg = _T("");
			for (int j = 0; j < m_nMaxCol; j++)
			{
				szMsg.Append(GetItemText(i, j));

				if (j == (m_nMaxCol - 1))
				{
					szMsg.Append(_T("\n"));
				}
				else
				{
					szMsg.Append(_T(","));
				}
			}
			file.WriteString(szMsg);
		}

		file.Close();
	}

	return strPath;
}


CString CCommonListCtrl::SaveDataToCsvEx(CString strFilePath)
{
	SYSTEMTIME st;
	CStdioFile file;
	CFileException ex;
	GetLocalTime(&st);
	CString szMsg = _T("");
	CString strPath = strFilePath;
	//szMsg.Format(_T("FrameMeasurementList_%04d%02d%02d_%02d%02d%02d"), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);



		// Do something useful here

	if (!file.Open(strPath, CFile::modeCreate | CFile::modeReadWrite, &ex))
		file.Open(strPath, CFile::modeReadWrite, &ex);

	ColDataWrite(&file);

	for (int i = 0; i < m_nMaxRow; i++)
	{
		szMsg = _T("");
		for (int j = 0; j < m_nMaxCol; j++)
		{
			szMsg.Append(GetItemText(i, j));

			if (j == (m_nMaxCol - 1))
			{
				szMsg.Append(_T("\n"));
			}
			else
			{
				szMsg.Append(_T(","));
			}
		}
		file.WriteString(szMsg);
	}

	file.Close();


	return strPath;
}

//Open된 파일 연결.
void CCommonListCtrl::ColDataWrite(CStdioFile *file)
{
	CString szMsg = _T("");

	for (int i = 0; i < m_nMaxCol; i++)
	{
		szMsg.Append(m_stCellInfo[i].ColName);

		if (i == (m_nMaxCol - 1))
		{
			szMsg.Append(_T("\n"));
		}
		else
		{
			szMsg.Append(_T(","));
		}
	}

	file->WriteString(szMsg);
}

void CCommonListCtrl::SetItemTextEx(INT nRow, INT nCol, CString strData)
{
	if (strData.Compare(GetItemText(nRow, nCol)))
		SetItemText(nRow, nCol, strData);
}

void CCommonListCtrl::SetClipboardOption(bool bOnOff)
{
	m_bClipboardOnOff = bOnOff;
}

