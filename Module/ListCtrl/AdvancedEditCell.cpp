// AdvancedEditCell.cpp : implementation file
//

#include "stdafx.h"
#include "AdvancedEditCell.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAdvancedEditCell

CAdvancedEditCell::CAdvancedEditCell(void* pCtrl, int iItem, int iSubItem, CString sInitText, int nMode)
{
	//if (nMode == 0) pStretchListCtrl = (CStretchListCtrl*)pCtrl;
	//else pVelocityListCtrl = (CVelocityListCtrl*)pCtrl;

	m_nMode = nMode;
    Item = iItem;
    SubItem = iSubItem;
    InitText = sInitText;
}

CAdvancedEditCell::~CAdvancedEditCell()
{
}


BEGIN_MESSAGE_MAP(CAdvancedEditCell, CEdit)
	//{{AFX_MSG_MAP(CAdvancedEditCell)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	ON_WM_KILLFOCUS()
    ON_WM_NCDESTROY()
    ON_WM_CHAR()
    ON_WM_CREATE()
    ON_WM_GETDLGCODE()
	ON_WM_KEYUP()
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdvancedEditCell message handlers

BOOL CAdvancedEditCell::PreTranslateMessage (MSG* pMsg) 
{
    if (pMsg->message == WM_KEYDOWN)
    {
	    if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_DELETE || 
			pMsg->wParam == VK_ESCAPE || pMsg->wParam == VK_TAB || 
			pMsg->wParam == VK_UP || pMsg->wParam == VK_DOWN || GetKeyState (VK_CONTROL))
			{
				::TranslateMessage (pMsg);
				::DispatchMessage (pMsg);
				return TRUE;		    	// DO NOT process further
			}
    }

    return CEdit::PreTranslateMessage (pMsg);
}

void CAdvancedEditCell::SetListText()
{
    CString Text;
    GetWindowText (Text);
	
	//sunghaklee(2019.01.08)
	//if (m_nMode != 2)
	//{
	//	if (IsReal(Text) == FALSE) return;
	//	if (_ttof(Text) <= 0.0) return;
	//	if (SubItem >= 4)
	//	{
	//		if (_ttof(Text) > 100.0) return;
	//	}
	//}

	//sunghaklee(2019.01.08)
	if (m_nMode == 3)
	{
		if (IsReal(Text) == FALSE) return;
		if (_ttof(Text) <= 0.0) return;
		if (SubItem >= 1)
		{
			if (_ttof(Text) < 0.0 || _ttof(Text) > 300.0) return;//Max Speed
		}
	}

    // Send Notification to parent of ListView ctrl
    LV_DISPINFO dispinfo;
    dispinfo.hdr.hwndFrom = GetParent()->m_hWnd;
    dispinfo.hdr.idFrom = GetDlgCtrlID();
    dispinfo.hdr.code = LVN_ENDLABELEDIT;

    dispinfo.item.mask = LVIF_TEXT;
    dispinfo.item.iItem = Item;
    dispinfo.item.iSubItem = SubItem;
    dispinfo.item.pszText = bEscape ? NULL : LPTSTR ((LPCTSTR) Text);
    dispinfo.item.cchTextMax = Text.GetLength();

//	TRACE( "dispinfo.item.pszText= %s \n", dispinfo.item.pszText);

    GetParent()->GetParent()->SendMessage (WM_NOTIFY, GetParent()->GetDlgCtrlID(), (LPARAM) &dispinfo);
}

BOOL CAdvancedEditCell::IsReal(CString Str)
{
	TCHAR ch;

	int nDotCount=0;
	int nLength=Str.GetLength();	
	if(nLength <1) return FALSE;

	for(int i=0; i<nLength; i++)
	{
		ch=Str.GetAt(i);

		if(i==0 && (ch=='-' || ch=='+')) { if(nLength==1) return FALSE; }
		else if(i!=0 && ch=='.') { if(++nDotCount > 1) return FALSE; }
		else if(isdigit(ch)==0) { return FALSE; }
	}
	
	return TRUE;
}

void CAdvancedEditCell::OnKillFocus (CWnd* pNewWnd) 
{
    CEdit::OnKillFocus(pNewWnd);

    SetListText();

	CString Text;
    GetWindowText (Text);

	//if( (SubItem==1 || IsReal(Text) !=FALSE) && InitText != Text)
	//{	
		//e_bPNTFileModified=TRUE;
	//}

    DestroyWindow();
}

void CAdvancedEditCell::OnNcDestroy() 
{
    CEdit::OnNcDestroy();    
	
    delete this;
}

void CAdvancedEditCell::OnKeyDown (UINT nChar, UINT nRepCnt, UINT nFlags) 
{
    // Up and down are in the OnKeyDown so that the user can hold down the arrow
    // keys to scroll through the entries.
	/*
    BOOL Control = GetKeyState (VK_CONTROL) < 0;
    switch (nChar)
    {
		case VK_UP :
		{
			if (Item > 0)
				pListCtrl->EditSubItem (Item - 1, SubItem);
			return;
		}
		case VK_DOWN :
		{
			pListCtrl->EditSubItem (Item + 1, SubItem);//Item + 1, SubItem);
			return;
		}
		case VK_HOME :
		{
			if (!Control)
				break;

			pListCtrl->EditSubItem (0, SubItem);
			return;
		}
		case VK_END :
		{
			if (!Control)
				break;

			int Count = pListCtrl->GetItemCount() - 1;
			pListCtrl->EditSubItem (Count, SubItem);
			return;
		}
    }
	*/
    
    CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CAdvancedEditCell::OnKeyUp (UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	/*
    switch (nChar)
    {
		case VK_NEXT :
		{
			int Count = pListCtrl->GetItemCount();
			int NewItem = Item + pListCtrl->GetCountPerPage();
			if (Count > NewItem)
				pListCtrl->EditSubItem (NewItem, SubItem);
			else
				pListCtrl->EditSubItem (Count - 1, SubItem);
			return;
		}
		case VK_PRIOR :
		{
			int NewItem = Item - pListCtrl->GetCountPerPage();
			if (NewItem > 0)
				pListCtrl->EditSubItem (NewItem, SubItem);
			else
				pListCtrl->EditSubItem (0, SubItem);
			return;
		}
    }
	*/
    
    CEdit::OnKeyUp (nChar, nRepCnt, nFlags);
}

void CAdvancedEditCell::OnChar (UINT nChar, UINT nRepCnt, UINT nFlags) 
{
    BOOL Shift = GetKeyState (VK_SHIFT) < 0;
    switch (nChar)
    {
		case VK_ESCAPE :
		{
			if (nChar == VK_ESCAPE)
				bEscape = TRUE;
			GetParent()->SetFocus();
			return;
		}
		case VK_RETURN :
		{	
			SetListText();
			//pListCtrl->EditSubItem (Item, SubItem);//Item + 1, 0);
			GetParent()->SetFocus();
			return;
		}
	/*	case VK_TAB :
		{
			if (Shift)
			{
				if (SubItem > 0)
					pListCtrl->EditSubItem (Item, SubItem - 1);
				else
				{
					if (Item > 0)
						pListCtrl->EditSubItem (Item - 1, 2);
				}
			}
			else
			{
				if (SubItem < 2)
					pListCtrl->EditSubItem (Item, SubItem + 1);
				else
					pListCtrl->EditSubItem (Item + 1, 0);
			}
			return;
		}*/
    }

    CEdit::OnChar (nChar, nRepCnt, nFlags);

    // Resize edit control if needed

    // Get text extent
    CString Text;

    GetWindowText (Text);
    CWindowDC DC (this);
    CFont *pFont = GetParent()->GetFont();
    CFont *pFontDC = DC.SelectObject (pFont);
    CSize Size = DC.GetTextExtent (Text);
    DC.SelectObject (pFontDC);
    Size.cx += 5;			   	// add some extra buffer

    // Get client rect
    CRect Rect, ParentRect;
    GetClientRect (&Rect);
    GetParent()->GetClientRect (&ParentRect);

    // Transform rect to parent coordinates
    ClientToScreen (&Rect);
    GetParent()->ScreenToClient (&Rect);

    // Check whether control needs to be resized and whether there is space to grow
    if (Size.cx > Rect.Width())
    {
		if (Size.cx + Rect.left < ParentRect.right )
			Rect.right = Rect.left + Size.cx;
		else
			Rect.right = ParentRect.right;
		MoveWindow (&Rect);
    }
}

int CAdvancedEditCell::OnCreate (LPCREATESTRUCT lpCreateStruct) 
{
    if (CEdit::OnCreate (lpCreateStruct) == -1)
		return -1;

    // Set the proper font
    CFont* Font = GetParent()->GetFont();
    SetFont (Font);

    SetWindowText (InitText);
    SetFocus();
    SetSel (0, -1);
    return 0;
}

UINT CAdvancedEditCell::OnGetDlgCode() 
{
    return CEdit::OnGetDlgCode() | DLGC_WANTARROWS | DLGC_WANTTAB;
}
