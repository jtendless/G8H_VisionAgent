// VelocityListCtrl.cpp : 구현 파일입니다.
//

#include "pch.h"
#include "VisionAgentLogResultListCtrl.h"
#include "CheckButton.h"
#include "AdvancedEditCell.h"

#include "../../VisionAgent/VisionAgent.h"
#include "../../VisionAgent/VisionAgentDlg.h"

#include <iostream> 
using namespace std;
#include <fstream>

#define IDC_PAGEEDITCELL		10001
#define IDC_COMBOBOXONLISTVIEW	10002
#define IDC_ADVANCEDEDITCELL	10003
// CVisionAgentLogResultListCtrl

//IMPLEMENT_DYNAMIC(CVisionAgentLogResultListCtrl, CListCtrl)

CVisionAgentLogResultListCtrl::CVisionAgentLogResultListCtrl()
{	
	HitItem = -1;
	m_nInsertItemCount = 0;
	m_nSubItemNum = 0;
	m_nSelectedItemNumber = -1;
	m_nUpdatePointNumber = -1;	
	
	m_pEdit = NULL;	
	m_pButton = NULL;

	//BkColorForSubItem(2, 2, 1, 2);

}

CVisionAgentLogResultListCtrl::~CVisionAgentLogResultListCtrl()
{	
	if (m_pEdit != NULL)
		delete m_pEdit;
}

BEGIN_MESSAGE_MAP(CVisionAgentLogResultListCtrl, CListCtrlCustomDraw)
	//{{AFX_MSG_MAP(CVisionAgentLogResultListCtrl)
	ON_WM_HSCROLL()
    ON_WM_VSCROLL()
	ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT, OnEndLabelEdit)
	ON_WM_KEYDOWN()
    ON_WM_LBUTTONDOWN()	
	ON_WM_KILLFOCUS()
	ON_WM_DRAWITEM()
	ON_MESSAGE(WM_CHECKSTATUS, &CVisionAgentLogResultListCtrl::OnCheckStatus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVisionAgentLogResultListCtrl message handlers

BOOL CVisionAgentLogResultListCtrl::IsDraw()
{
	return true;
}

BOOL CVisionAgentLogResultListCtrl::OnDraw(CDC* pDC)
{	
	/*
	DRAWITEMSTRUCT ds;
	CRect vrc;
	GetViewRect(vrc);
	CRect itemrc;
	for(int i=0; i<GetItemCount(); i++)
	{
		GetItemRect(i, itemrc, LVIR_BOUNDS);
		ds.hDC = pDC->GetSafeHdc();
		ds.itemID = i;
		ds.rcItem = itemrc;
		DrawItem(&ds);
	}
	*/
	
	return false; // do default drawing as well
}

BOOL CVisionAgentLogResultListCtrl::IsNotifyItemDraw()
{
	return true;
}

BOOL CVisionAgentLogResultListCtrl::IsNotifySubItemDraw(int /*nItem*/, UINT /*nState*/, LPARAM /*lParam*/)
{
	return true;
}

COLORREF CVisionAgentLogResultListCtrl::TextColorForSubItem(int nItem, int nSubItem, UINT /*nState*/, LPARAM /*lParam*/)
{
	if(0 ==nSubItem) return RGB(0,0,0);
	 else return CLR_DEFAULT;	
}

COLORREF CVisionAgentLogResultListCtrl::BkColorForSubItem(int nItem, int nSubItem, UINT /*nState*/, LPARAM /*lParam*/)
{

	if (0 == nSubItem) 
	{
		return RGB(215, 215, 215);	
	}
	else if( 1 == nSubItem) 
	{
		//return RGB(126, 205, 150);
		return RGB(139, 192, 191);
	}
	else if( 2 == nSubItem) 
	{
		//return RGB(126, 205, 150);
		return RGB(139, 192, 191);
	}	
	else if( 3 == nSubItem) 
	{
		return RGB(126, 205, 150);
	}	
	else if( 4 == nSubItem) 
	{
		return RGB(126, 205, 150);
	}	
	else if( 5 == nSubItem) 
	{
		return RGB(126, 205, 150);
	}	
	else if (6 == nSubItem)
	{
		return RGB(126, 205, 150);
	}
	else if (7 == nSubItem)
	{
		return RGB(126, 205, 150);
	}
	else
	{
		return CLR_DEFAULT;
	}
}

///#################################################################///
///							For EditCell							///
///#################################################################///
void CVisionAgentLogResultListCtrl::Resize (int cx, int cy)
{
    CRect Rect (0, 0, cx, cy);
    MoveWindow (&Rect);
    InvalidateRect (Rect);
    SetColumnWidth (0, LVSCW_AUTOSIZE_USEHEADER);	
}
int CVisionAgentLogResultListCtrl::HitTestEx (CPoint& Point, int* pColumn)
{
    int ColumnNum = 0;
    int Row = HitTest (Point, NULL);

    HitItem = Row;	

    if (pColumn) *pColumn = 0;

    // Make sure that the ListView is in LVS_REPORT
    if ((GetWindowLong (m_hWnd, GWL_STYLE) & LVS_TYPEMASK) != LVS_REPORT)
		return Row;

    // Get the top and bottom row visible
    Row = GetTopIndex();
    int Bottom = Row + GetCountPerPage();
    if (Bottom > GetItemCount())
	    Bottom = GetItemCount();
    
    // Get the number of columns
    CHeaderCtrl* pHeader = (CHeaderCtrl*) GetDlgItem(0);
    int nColumnCount = pHeader->GetItemCount();

    // Loop through the visible rows
    for(; Row <= Bottom; Row++)
    {
		// Get bounding rect of item and check whether point falls in it.
		CRect Rect;
		GetItemRect (Row, &Rect, LVIR_BOUNDS);
		if (Rect.PtInRect (Point))
		{
			// Now find the column
			for (ColumnNum = 0; ColumnNum < nColumnCount; ColumnNum++)
			{
				int ColWidth = GetColumnWidth (ColumnNum);
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

CEdit* CVisionAgentLogResultListCtrl::EditSubItem (int Item, int Column)
{
    // The returned pointer should not be saved

	if(Column==0) return NULL;

    // Make sure that the item is visible
    if (!EnsureVisible (Item, TRUE)) 
    {
		InsertItemEx (Item);
		if (!EnsureVisible (Item, TRUE)) 
			return NULL;
    }

    // Make sure that nCol is valid
    CHeaderCtrl* pHeader = (CHeaderCtrl*) GetDlgItem(0);
    int nColumnCount = pHeader->GetItemCount();
    if (Column >= nColumnCount || GetColumnWidth (Column) < 5)
		return NULL;

    // Get the column offset
    int Offset = 0;
    for (int iColumn = 0; iColumn < Column; iColumn++)
		Offset += GetColumnWidth (iColumn);

    CRect Rect;
    GetItemRect (Item, &Rect, LVIR_BOUNDS);

    // Now scroll if we need to expose the column
    CRect ClientRect;
    GetClientRect (&ClientRect);
    if (Offset + Rect.left < 0 || Offset + Rect.left > ClientRect.right)
    {
		CSize Size;
		if (Offset + Rect.left > 0)
			Size.cx = -(Offset - Rect.left);
		else
			Size.cx = Offset - Rect.left;
		Size.cy = 0;
		Scroll (Size);
		Rect.left -= Size.cx;
    }

    // Get Column alignment
    LV_COLUMN lvCol;
    lvCol.mask = LVCF_FMT;
    GetColumn (Column, &lvCol);
    DWORD dwStyle;
    if ((lvCol.fmt & LVCFMT_JUSTIFYMASK) == LVCFMT_LEFT)
		dwStyle = ES_LEFT;
    else if ((lvCol.fmt & LVCFMT_JUSTIFYMASK) == LVCFMT_RIGHT)
		dwStyle = ES_RIGHT;
    else dwStyle = ES_CENTER;

    Rect.left += Offset+4;
    Rect.right = Rect.left + GetColumnWidth (Column) - 3;
    if (Rect.right > ClientRect.right)
		Rect.right = ClientRect.right;

    dwStyle |= WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL;
	
	if(Column >= 1)
	{			
		CAdvancedEditCell *pEdit = new CAdvancedEditCell (this, Item, Column, GetItemText (Item, Column), 1);
		pEdit->Create (dwStyle, Rect, this, IDC_ADVANCEDEDITCELL);						
		
		return m_pEdit;
	}	
	return NULL;    
}

void CVisionAgentLogResultListCtrl::OnEndLabelEdit (NMHDR* pNMHDR, LRESULT* pResult) 
{
    LV_DISPINFO *plvDispInfo = (LV_DISPINFO *)pNMHDR;
    LV_ITEM	*plvItem = &plvDispInfo->item;

    //if (plvItem->pszText != NULL && (m_nSubItemNum==1 || IsReal(plvItem->pszText) != FALSE))
	if (plvItem->pszText != NULL && plvItem->iSubItem >= 1)
    {
		SetItemText (plvItem->iItem, plvItem->iSubItem, plvItem->pszText);
		m_nSelectedItemNumber = plvItem->iItem;
		HighlightSelectedItem();
    }	
	
	RedrawItems(GetTopIndex(), GetTopIndex() + GetCountPerPage());
	
    *pResult = FALSE;
	HighlightSelectedItem();
}

///#################################################################///
///							For ComboBox							///
///#################################################################///
CComboBox* CVisionAgentLogResultListCtrl::ShowList(int nItem, int nCol, CString StrData)
{
	CRect rect;
	int offset = 0;

	// Make sure that the item is visible
	if (!EnsureVisible(nItem, TRUE)) return NULL;
	GetSubItemRect(nItem, nCol, LVIR_BOUNDS, rect);

	// Now scroll if we need to expose the column
	CRect rcClient;
	GetClientRect(rcClient);
	if (offset + rect.left < 0 || offset + rect.left > rcClient.right){
		CSize size;
		size.cx = offset + rect.left;
		size.cy = 0;
		Scroll(size);
		rect.left -= size.cx;
	}

	rect.left += offset;
	rect.right = rect.left + GetColumnWidth(nCol);
	if (rect.right > rcClient.right) rect.right = rcClient.right;

	rect.bottom += 20 * rect.Height();
	//rect.bottom += 30 * rect.Height();
	DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_DISABLENOSCROLL;

	/*
	CComboBox *pList = new CWizardCombo(nItem, nCol, StrData);

	pList->Create(dwStyle, rect, this, IDC_COMBOBOXONLISTVIEW);
	pList->ModifyStyleEx(0, WS_EX_CLIENTEDGE);
	pList->ShowDropDown();

	m_bIsCombox = TRUE;
	*/

	// The returned pointer should not be saved
	return pList;
}

void CVisionAgentLogResultListCtrl::SetListCtrlMode(int nInspectListMode)
{
	m_nInspectListMode = nInspectListMode;
}

void CVisionAgentLogResultListCtrl::InsertNumber(int Item, int Column) 
{
	CString ItemNum, NextItemString;	

	ItemNum.Format(_T("%d"),Item+1);
	
	NextItemString=GetItemText(Item + 1, 0);

	if(ItemNum != NextItemString)
	{
		InsertItem (Item + 1, ItemNum);		
		m_nInsertItemCount++;
	}
}

int CVisionAgentLogResultListCtrl::InsertItemEx (int Item)
{
	CString ItemNum;
	ItemNum.Format(_T("%d"),Item+1);

    int Result = InsertItem (Item + 1, ItemNum);
	
    CString ItemVal, Temp;
    
    SetItemText (Item, 1, ItemVal);
    SetColumnWidth (0, LVSCW_AUTOSIZE_USEHEADER);

    return Result;
}

void CVisionAgentLogResultListCtrl::OnHScroll (UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
    if (GetFocus() != this) 
		SetFocus();

    CListCtrl::OnHScroll (nSBCode, nPos, pScrollBar);
}

void CVisionAgentLogResultListCtrl::OnVScroll (UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
    if (GetFocus() != this) 
		SetFocus();
    
    CListCtrl::OnVScroll (nSBCode, nPos, pScrollBar);
}

void CVisionAgentLogResultListCtrl::OnLButtonDown (UINT nFlags, CPoint Point) 
{
	CListCtrl::OnLButtonDown(nFlags, Point);	
	
	//int i;
	int Index;
    int ColNum;		
	CString Str;
	
    if((Index = HitTestEx (Point, &ColNum)) != -1)
    {		
		//if (ColNum > 0 && ColNum < 7)
		//{
		//	m_nSubItemNum = ColNum;
		//	DWORD dwStyle = GetWindowLong(m_hWnd, GWL_STYLE);
		//	dwStyle |= LVS_EDITLABELS;
		//	SetWindowLong(m_hWnd, GWL_STYLE, dwStyle);
		//	RedrawItems(GetTopIndex(), GetTopIndex() + GetCountPerPage());
		//	m_nSelectedItemNumber = Index;

		//	EditSubItem(Index, ColNum);
		//}
    }	
		
	//CListCtrl::OnLButtonDown (nFlags, Point);
}

void CVisionAgentLogResultListCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default	

	if(nChar==VK_DELETE)
	{
		if(HitItem !=-1)
		{	
			int Index = HitItem;//HitTestEx (HitPt, &ColNum);
			if(m_nInsertItemCount == Index+1)
			{
				DeleteItem(Index);

				if(m_nInsertItemCount > 0) m_nInsertItemCount--;
			}
			else
			{	
				CString Str;
				int Interval=m_nInsertItemCount-(Index+1);
		
				DeleteItem(Index);

				for(int i=0; i<Interval; i++) 
				{	
					Str.Format(_T("%d"), Index);
					SetItemText(Index++, 0, Str);
				}		
		
				if(m_nInsertItemCount > 0) m_nInsertItemCount--;
			}	
		}
	}

	CListCtrl::OnKeyDown(nChar, nRepCnt, nFlags);	
}

void CVisionAgentLogResultListCtrl::InitialVelocityListCtrl()
{
	m_nInsertItemCount = 0;
	DeleteAllItems();
}
//
//void CVisionAgentLogResultListCtrl::AddAllListData()
//{	
//	CVisionAgentDlg *pDlg;
//	pDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
//	
//	LV_ITEM lvitem;
//	int curitem = 0;
//	int nCount = 0, i, j = 0;
//	CString Str;
//	TCHAR  chData[4][256];
//
//	InitialVelocityListCtrl();	
//	
//	for (i = 0; i < MAX_MOTOR_NO; i++)
//	{
//		Str.Format(_T("%s"), pDlg->m_VelocityData.MotorLabel[i]);
//		wsprintf(chData[0], _T("%s"), Str);
//
//		Str.Format(_T("%.3f"), pDlg->m_VelocityData.m_WorkVelocity.m_dMotorVel[i][0]);
//		wsprintf(chData[1], _T("%s"), Str);
//
//		Str.Format(_T("%.3f"), pDlg->m_VelocityData.m_WorkVelocity.m_dMotorVel[i][1]);
//		wsprintf(chData[2], _T("%s"), Str);
//
//		Str.Format(_T("%.3f"), pDlg->m_VelocityData.m_WorkVelocity.m_dMotorVel[i][2]);
//		wsprintf(chData[3], _T("%s"), Str);
//		
//		for (j = 0; j < 4; j++){
//			lvitem.iItem = (j == 0) ? nCount : curitem;
//			lvitem.iSubItem = j;
//
//			switch (j){
//				//"No"
//			case 0:
//				lvitem.pszText = (LPWSTR)chData[0];
//				curitem = InsertItem(&lvitem);
//				break;
//
//				//"Label"
//			case 1:
//				lvitem.pszText = (LPWSTR)chData[1];
//				SetItem(&lvitem);
//				break;
//
//				//"#0"
//			case 2:
//				lvitem.pszText = (LPWSTR)chData[2];
//				SetItem(&lvitem);
//				break;
//
//				//"#1"
//			case 3:
//				lvitem.pszText = (LPWSTR)chData[3];
//				SetItem(&lvitem);
//				break;			
//			}
//		}
//		
//		nCount++;
//		m_nInsertItemCount++;		
//	}
//	
//	/*
//		while (POS != NULL){
//			CPointDataList *pCPointDataList = pDispensorDlg->m_pPointDataList->GetAt(POS);
//
//			StrData[0].Format(_T("%d"), nCount);
//
//			StrData[1] = (LPCTSTR)pCPointDataList->m_StrDataArray.GetAt(0);
//			StrData[2] = (LPCTSTR)pCPointDataList->m_StrDataArray.GetAt(1);
//			StrData[3] = (LPCTSTR)pCPointDataList->m_StrDataArray.GetAt(2);
//			StrData[4] = (LPCTSTR)pCPointDataList->m_StrDataArray.GetAt(3);
//			StrData[5] = (LPCTSTR)pCPointDataList->m_StrDataArray.GetAt(4);
//			//StrData[6] = (LPCTSTR)pCPointDataList->m_StrDataArray.GetAt(5);
//			//StrData[7] = (LPCTSTR)pCPointDataList->m_StrDataArray.GetAt(6);
//			//StrData[8] = (LPCTSTR)pCPointDataList->m_StrDataArray.GetAt(7);
//						
//			lvitem.mask = LVIF_TEXT;
//			for (j = 0; j < 6; j++){
//				lvitem.iItem = (j == 0) ? nCount : curitem;
//				lvitem.iSubItem = j;
//
//				switch (j){
//					//"No"
//				case 0:
//					lvitem.pszText = (LPWSTR)(LPCTSTR)StrData[0];
//					curitem = InsertItem(&lvitem);
//					break;
//
//					//"Label"
//				case 1:
//					lvitem.pszText = (LPWSTR)(LPCTSTR)StrData[1];
//					SetItem(&lvitem);
//					break;
//
//					//"#0"
//				case 2:
//					lvitem.pszText = (LPWSTR)(LPCTSTR)StrData[2];
//					SetItem(&lvitem);
//					break;
//
//					//"#1"
//				case 3:
//					lvitem.pszText = (LPWSTR)(LPCTSTR)StrData[3];
//					SetItem(&lvitem);
//					break;
//
//					//"#2"
//				case 4:
//					lvitem.pszText = (LPWSTR)(LPCTSTR)StrData[4];
//					SetItem(&lvitem);
//					break;
//
//					//"#3"
//				case 5:
//					lvitem.pszText = (LPWSTR)(LPCTSTR)StrData[5];
//					SetItem(&lvitem);
//					break;
//
//					//"#4"
//				case 6:
//					lvitem.pszText = (LPWSTR)(LPCTSTR)StrData[6];
//					SetItem(&lvitem);
//					break;
//
//					//"#5"
//				case 7:
//					lvitem.pszText = (LPWSTR)(LPCTSTR)StrData[7];
//					SetItem(&lvitem);
//					break;
//				}					
//			}
//
//			nCount++;
//			m_nInsertItemCount++;
//			pDispensorDlg->m_pPointDataList->GetNext(POS);
//		}
//	}	
//	*/
//}

void CVisionAgentLogResultListCtrl::AddListColumn()
{
	LV_COLUMN lvcolumn;		
	TCHAR *listcolumn[3] = { _T("No"), _T("Time"), _T("Message") };
	int width[3] = { 60, 100, 700 };
	
	for (int i=0; i<3; i++)  
	{
		lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
		lvcolumn.fmt = LVCFMT_CENTER;
		lvcolumn.pszText = (LPWSTR)listcolumn[i];		
		lvcolumn.iSubItem = i;
		lvcolumn.cx = width[i];		

		InsertColumn(i, &lvcolumn);  
	}	
}

BOOL CVisionAgentLogResultListCtrl::InitCheckCtrl()
{
	m_nSelectedItemNumber = -1;
	m_nUpdatePointNumber = -1;

	LV_ITEM lvitem;
	int curitem = 0;
	lvitem.mask = LVIF_TEXT;
	for (int j = 0; j<5; j++)
	{
		lvitem.iItem = (j == 0) ? m_nInsertItemCount : curitem;
		lvitem.iSubItem = j;

		switch (j)
		{
		case 0:
			lvitem.pszText = _T("");
			curitem = InsertItem(&lvitem);
			break;
		case 1:
			lvitem.pszText = _T("");
			SetItem(&lvitem);
			break;
		case 2:
			lvitem.pszText = _T("");
			SetItem(&lvitem);
			break;
		case 3:
			lvitem.pszText = _T("");
			SetItem(&lvitem);
			break;
		case 4:
			lvitem.pszText = _T("");
			SetItem(&lvitem);
			break;
		case 5:
			lvitem.pszText = _T("");
			SetItem(&lvitem);
			break;
		case 6:
			lvitem.pszText = _T("");
			SetItem(&lvitem);
			break;
		}
	}

	return 0;
}

BOOL CVisionAgentLogResultListCtrl::AddCheckCtrl(int nCol, int nCheckStatus)
{	
	CRect rect;
	int offset = 0;
	int nItem = 0;// , nCol = 1;

	// Make sure that the item is visible
	if (!EnsureVisible(nItem, TRUE)) return NULL;
	GetSubItemRect(nItem, nCol, LVIR_BOUNDS, rect);

	// Now scroll if we need to expose the column
	CRect rcClient;
	GetClientRect(rcClient);
	if (offset + rect.left < 0 || offset + rect.left > rcClient.right){
		CSize size;
		size.cx = offset + rect.left;
		size.cy = 0;
		Scroll(size);
		rect.left -= size.cx;
	}

	rect.left += offset;
	rect.right = rect.left + GetColumnWidth(nCol);
	if (rect.right > rcClient.right) rect.right = rcClient.right;

	//rect.bottom += 20 * rect.Height();
	//rect.bottom += 30 * rect.Height();
	//DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_DISABLENOSCROLL;
	DWORD dwStyle = WS_CHILD | WS_VISIBLE | BS_CHECKBOX;// | CBS_DROPDOWNLIST | CBS_DISABLENOSCROLL;
		
	//m_pButton = new CCheckButton();//nItem, nCol, StrData);
	CButton *pList = new CCheckButton(nCol);//nItem, nCol, StrData);

	//pList->Create(dwStyle, rect, this, IDC_COMBOBOXONLISTVIEW);
	pList->Create(_T("Used"), dwStyle, rect, this, IDC_COMBOBOXONLISTVIEW);
	pList->ModifyStyleEx(0, WS_EX_CLIENTEDGE);
	
	m_nCheckStatus[nCol - 1] = nCheckStatus;

	if (nCheckStatus == TRUE) pList->SetCheck(TRUE);

	m_bIsCombox = TRUE;	

	m_nInsertItemCount = 1;

	return 0;
}

BOOL CVisionAgentLogResultListCtrl::AddListData(CString Str[5])
{	
	m_nSelectedItemNumber = -1;
	m_nUpdatePointNumber = -1;

	LV_ITEM lvitem;		
	int curitem = 0;	
	
	TCHAR  chData[8][256];


	//_stprintf(chData[0], _T("%d"), m_nInsertItemCount);		
	//wsprintf(chData[0], _T("%d"), m_nInsertItemCount);
	wsprintf(chData[0], _T("%s"), Str[0]);
		
	wsprintf(chData[1], _T("%s"), Str[1]);
	
	wsprintf(chData[2], _T("%s"), Str[2]);	

	lvitem.mask = LVIF_TEXT;
	for (int j = 0; j < 5; j++)
	{	
		lvitem.iItem = (j==0) ? m_nInsertItemCount : curitem;
		lvitem.iSubItem = j;
	
		switch(j)
		{				
		case 0:										
			lvitem.pszText= (LPWSTR)chData[0];
			curitem=InsertItem(&lvitem);
			break;
		case 1:							
			lvitem.pszText= (LPWSTR)chData[1];
			SetItem(&lvitem);
			break;
		case 2:											
			lvitem.pszText= (LPWSTR)chData[2];
			SetItem(&lvitem);					
			break;				
		}
	}							

	//SetScroll();

	//SetFocus();

	//SetItemState(m_nInsertItemCount, LVIS_SELECTED | LVIS_FOCUSED , LVIS_SELECTED | LVIS_FOCUSED);	

	m_nInsertItemCount++;

	return TRUE;
}

BOOL CVisionAgentLogResultListCtrl::DeleteAllListData()
{	
	if(m_nInsertItemCount < 1) return FALSE;

	DeleteAllItems( );
	HitItem = -1;
	m_nInsertItemCount = 0;
	m_nSubItemNum = 0;
	m_nSelectedItemNumber = -1;
	m_nUpdatePointNumber = -1;	
	
	return TRUE;
}

BOOL CVisionAgentLogResultListCtrl::DeleteListData(int nNo)
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

	for (i = nNo; i <nCount; i++)
	{
		//_stprintf(LvItem.pszText, _T("%d"), i);
		wsprintf(chData, _T("%d"), i);

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

	m_nInsertItemCount--;

	return TRUE;
}

BOOL CVisionAgentLogResultListCtrl::InsertListData(int nNo)
{
	int i;
	int nCount;
	TCHAR chData[256];
	LV_ITEM lvitem;

	nCount = GetItemCount();
	if (nNo >= nCount || nNo < 0) return FALSE;

	wsprintf(chData, _T("%d"), nNo);

	lvitem.mask = LVIF_TEXT;
	lvitem.iItem = nNo;
	lvitem.pszText = (LPWSTR)chData;
	lvitem.iSubItem = 0;
	InsertItem(&lvitem);

	for (i = nNo + 1; i <= nCount; i++)
	{
		//_stprintf(LvItem.pszText, _T("%d"), i);
		wsprintf(chData, _T("%d"), i);

		lvitem.iItem = i;
		lvitem.pszText = (LPWSTR)chData;

		SetItem(&lvitem);
	}

	SetFocus();
	SetItemState(nNo, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);

	m_nInsertItemCount++;

	return TRUE;
}

int CVisionAgentLogResultListCtrl::SaveListData(BOOL bIsAuto /*= FALSE*/)
{		
	return 1;
}

void CVisionAgentLogResultListCtrl::GetListData()
{		
}

void CVisionAgentLogResultListCtrl::AddOffsetListData(int nIndex[2], double dPosData[6])
{	
	//CString StrOffsetData[MAX_AXIS_SIZE];	
	//TCHAR* EndPtr;
	TCHAR  chData[10][256];	
	
	for(int i=nIndex[0]; i<=nIndex[1]; i++)
	{
		for(int j=0; j<6; j++)
		{
			//StrOffsetData[j].Format("%.3f", atof(GetItemText(i,j+2))+dPosData[j]);		
			//_stprintf(chData[j], _T("%.3f"), _tcstod(GetItemText(i, j+2), &EndPtr)+dPosData[j]);					
			SetItemText(i, j+2, chData[j]);
		}
	}

	//e_bPNTFileModified=TRUE;
}

BOOL CVisionAgentLogResultListCtrl::UpdateListData(double dPosData[6], int nPNTNumber)
{
	if(m_nInsertItemCount < 1 || nPNTNumber > m_nInsertItemCount-1) return FALSE;

	if(nPNTNumber != -1) m_nUpdatePointNumber=nPNTNumber;
	else if(m_nUpdatePointNumber == -1) m_nUpdatePointNumber=m_nInsertItemCount-1;
		
	CString StrUpdateData[6];
	
	for(int i=0; i<6; i++)
	{
		StrUpdateData[i].Format(_T("%.3f"), dPosData[i]);	
		SetItemText(m_nUpdatePointNumber, i+2, StrUpdateData[i]);
	}	

	//SetScroll();

	SetFocus();

	SetItemState(nPNTNumber, LVIS_SELECTED | LVIS_FOCUSED , LVIS_SELECTED | LVIS_FOCUSED);

	return TRUE;
}

int CVisionAgentLogResultListCtrl::GetMaxListCount()
{
	return m_nInsertItemCount;
}

//int No, int nMaskY, int nCellXY[2], int nDivXY[2], double dPointXY[2]
BOOL CVisionAgentLogResultListCtrl::GetListData(int nRow, double dData[6])		
{		
	if(nRow < 0 || nRow > m_nInsertItemCount-1 ) return FALSE;
		
	dData[0] = _tstof((LPTSTR)(LPCTSTR)GetItemText(nRow, 1));
	dData[1] = _tstof((LPTSTR)(LPCTSTR)GetItemText(nRow, 2));
	dData[2] = _tstof((LPTSTR)(LPCTSTR)GetItemText(nRow, 3));
	dData[3] = _tstof((LPTSTR)(LPCTSTR)GetItemText(nRow, 4));
	dData[4] = _tstof((LPTSTR)(LPCTSTR)GetItemText(nRow, 5));	
	dData[5] = _tstof((LPTSTR)(LPCTSTR)GetItemText(nRow, 6));

	return TRUE;
}

BOOL CVisionAgentLogResultListCtrl::IsReal(CString Str)
{
	TCHAR ch;

	int nDotCount = 0;
	int nLength = Str.GetLength();	
	if(nLength < 1) return FALSE;

	for(int i=0; i<nLength; i++)
	{
		ch=Str.GetAt(i);

		if(i==0 && (ch=='-' || ch=='+'));
		else if(i!=0 && ch=='.')
		{
			if(++nDotCount>1) return FALSE;			
		}
		else if(isdigit(ch)==0)
		{
			return FALSE;						
		}
	}
	
	return TRUE;
}

void CVisionAgentLogResultListCtrl::HighlightSelectedItem()
{	
	if(m_nSelectedItemNumber < 0) return;

//	SetFocus();
//	SetItemState(m_nSelectedItemNumber, LVIS_SELECTED | LVIS_FOCUSED , LVIS_SELECTED | LVIS_FOCUSED);
	SetItemState(m_nSelectedItemNumber, LVIS_SELECTED  , LVIS_SELECTED | LVIS_FOCUSED);		
}

int CVisionAgentLogResultListCtrl::GetItemHeight()
{
	CRect ItemRect;
	GetSubItemRect(1, 1, LVIR_BOUNDS, ItemRect);
	return ItemRect.bottom - ItemRect.top;
}

void CVisionAgentLogResultListCtrl::SetScroll()
{	
	SCROLLINFO sinfo;
    sinfo.cbSize=sizeof(sinfo);
    sinfo.fMask=SIF_RANGE;//SIF_TRACKPOS;
	::GetScrollInfo(m_hWnd, SB_VERT, &sinfo);    	
	
	int nItemHeight=GetItemHeight();		
	int Pos=m_nInsertItemCount;//m_nSelectedItem[0];
	
	int iY = ((int)Pos - (int)GetScrollPos(SB_VERT)) * nItemHeight; 
    //GetListCtrl().Scroll(CSize(0, iY)); 
	Scroll(CSize(0, iY)); 	
}

void CVisionAgentLogResultListCtrl::OnKillFocus(CWnd* pNewWnd) 
{
	CListCtrl::OnKillFocus(pNewWnd);
	HighlightSelectedItem();
}

void CVisionAgentLogResultListCtrl::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	
	CListCtrl::OnDrawItem(nIDCtl, lpDrawItemStruct);
}


void CVisionAgentLogResultListCtrl::DrawItem( LPDRAWITEMSTRUCT lpDrawItemStruct )
{
	int iItem = lpDrawItemStruct->itemID;
	CRect subRect = lpDrawItemStruct->rcItem;
	subRect.right = subRect.left;

	if(m_nSelectedItemNumber == iItem)
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

	for(int i = 0; i < 5; i++)
	{
		subRect.right += GetColumnWidth(i);
//		DrawText(lpDrawItemStruct->hDC, GetItemText(iItem, i), strlen(GetItemText(iItem, i)), subRect,  DT_CENTER|DT_VCENTER);
		subRect.left = subRect.right;
	}	
}

BOOL CVisionAgentLogResultListCtrl::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	/*
	if(pMsg->message == WM_LBUTTONDOWN || pMsg->message == WM_LBUTTONDBLCLK || pMsg->message == WM_MOUSEWHEEL)	
	{
		if(IsWindow(g_KeyBox.GetSafeHwnd()) && g_KeyBox.IsWindowVisible())
			return TRUE;
	}
	*/
	
	/*
	if(pMsg->message == WM_NUMBER_KEYPAD)
	{		
		//if(pMsg->wParam == IDOK && (m_nSubItemNum==1 || IsReal((TCHAR*)pMsg->lParam) != FALSE))
		if(pMsg->wParam == IDOK)// && (IsReal((TCHAR*)pMsg->lParam) != FALSE))
		{
			SetItemText(m_nSelectedItemNumber, m_nSubItemNum, (TCHAR*)pMsg->lParam);
			RedrawItems(GetTopIndex(), GetTopIndex() + GetCountPerPage());
		}	
		
		//HighlightSelectedItem();
		if (m_pEdit != NULL)
		{
			m_pEdit->DestroyWindow();
			m_pEdit = NULL;
		}

		if(m_pNumberKeyPadDlg != NULL)
		{
			m_pNumberKeyPadDlg->DestroyWindow();
			m_pNumberKeyPadDlg = NULL;
		}

		return TRUE;
	}
	*/
	/*
	else if(pMsg->message == WM_CHAR_KEYPAD)
	{		
		//if(pMsg->wParam == IDOK && (m_nSubItemNum==1 || IsReal((TCHAR*)pMsg->lParam) != FALSE))
		if(pMsg->wParam == IDOK)// && (IsReal((TCHAR*)pMsg->lParam) != FALSE))
		{
			SetItemText(m_nSelectedItemNumber, m_nSubItemNum, (TCHAR*)pMsg->lParam);
			RedrawItems(GetTopIndex(), GetTopIndex() + GetCountPerPage());
		}	
		
		//HighlightSelectedItem();
		m_pEdit->DestroyWindow();
		m_pEdit = NULL;
		
		if(m_pCharKeyPadDlg != NULL)
		{
			m_pCharKeyPadDlg->DestroyWindow();
			m_pCharKeyPadDlg = NULL;
		}

		return TRUE;
	}	
	*/

	return CListCtrl::PreTranslateMessage(pMsg);
}


int CVisionAgentLogResultListCtrl::LoadPointData(char* pchPathName)
{	
	/*
	CDispensorDlg *pDispensorDlg;
	pDispensorDlg = (CDispensorDlg *)theApp.m_pMainWnd;

	CStdioFile InFile;
	CString strData, strDataTemp;
	CString strPointData[9];
	int nTokenCount;
	
	TCHAR* chDelimiterBlank = _T("\t");
	TCHAR* chDelimiterComma = _T(",");
	TCHAR* pchDelimiter = NULL;
	TCHAR* pchToken = NULL;
	TCHAR chData[256];

	InitialVelocityListCtrl();

	if (InFile.Open((LPCTSTR)pchPathName, CFile::modeRead | CFile::typeText) == FALSE) return 0;

	pDispensorDlg->CreatePointDataList();

	while (InFile.ReadString(strData) != FALSE){
		strData.TrimLeft();
		//strData.TrimRight();

		if (!strData.Compare(_T("#BEGIN")) || strData.GetLength() < 1) continue;
		if (!strData.Compare(_T("#END")) || strData == EOF) break;

		if (!pchDelimiter){
			if (strData.Find((LPWSTR)chDelimiterComma) != -1){
				pchDelimiter = chDelimiterComma;
			}
			else{
				pchDelimiter = chDelimiterBlank;
			}
		}

		//pchToken = strtok((LPSTR)(LPCTSTR)strData, pchDelimiter);		
		//_stprintf(chData, _T("%s"), strData);
		wsprintf(chData, _T("%s"), strData);
		pchToken = _tcstok(chData, pchDelimiter);

		nTokenCount = 0;

		while (pchToken != NULL){
			if (nTokenCount != 0){
				strPointData[nTokenCount - 1].Format(_T("%s"), pchToken);
				strPointData[nTokenCount - 1].TrimLeft();
				strPointData[nTokenCount - 1].TrimRight();
			}
			//pchToken = strtok(NULL, pchDelimiter);   
			pchToken = _tcstok(NULL, pchDelimiter);
			nTokenCount++;
		}
		pDispensorDlg->m_pPointDataList->AddTail(new CPointDataList(strPointData));
	}

	InFile.Close();
	
	AddAllListData();	
	*/

	return TRUE;
}

LRESULT CVisionAgentLogResultListCtrl::OnCheckStatus(WPARAM wParam, LPARAM lParam)
{	
	m_nCheckStatus[wParam - 1] = (int)lParam;	

	return TRUE;
}