// WizardCombo.cpp : implementation file
//

#include "stdafx.h"
#include "WizardCombo.h"



/////////////////////////////////////////////////////////////////////////////
// CWizardCombo

CWizardCombo::CWizardCombo(int iItem, int iSubItem, CString StrData,int ListIndex)
{	
	m_iItem = iItem;
	m_iSubItem = iSubItem;
	m_ListIndex = ListIndex;
	//m_nValue = nValue;
	m_bVK_ESCAPE = 0;	
	m_StrData = StrData;
}

CWizardCombo::~CWizardCombo()
{
	m_Font.DeleteObject();
}


BEGIN_MESSAGE_MAP(CWizardCombo, CComboBox)
	//{{AFX_MSG_MAP(CWizardCombo)
	ON_WM_CREATE()
	ON_WM_KILLFOCUS()
	ON_WM_CHAR()
	ON_WM_NCDESTROY()
	ON_CONTROL_REFLECT(CBN_CLOSEUP, OnCloseup)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWizardCombo message handlers
int CWizardCombo::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CComboBox::OnCreate(lpCreateStruct) == -1)		
		return -1;	

	CString szMsg;
	CFont* font = GetParent()->GetFont();	
	SetFont(font);
	
	m_Font.CreateFont(22, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, _T("Tahoma"));
	SetFont(&m_Font);

	m_nValue = -1;
	if (m_ListIndex == 0)
	{
		if (m_iSubItem == 3)				//TYPE
		{
			for (int i = 0; i < 32; i++)
			{
				szMsg.Format(_T("%d"), i);
				AddString(szMsg);
			}
			SetMinVisibleItems(GetCount());

			for (int i = 0; i < 32; i++)
			{
				if (m_StrData.GetLength() > 0)
				{

					szMsg.Format(_T("%d"), i);
					if (m_StrData == szMsg)
					{
						m_nValue = i;
					}
				}

			}
		}

		else if (m_iSubItem == 4)				//TYPE
		{
			AddString(_T("Use"));			// 0
			AddString(_T("No Use"));
		// 1
			if (m_StrData.GetLength() > 0)
			{
				if (m_StrData == _T("Use"))			//0
				{
					m_nValue = 0;
				}
				else if (m_StrData == _T("No Use"))		// 1
				{
					m_nValue = 1;
				}			

			}
		}
	}
	else if (m_ListIndex == 1)
	{
		if (m_iSubItem == 1)				//TYPE
		{
			AddString(_T("Vertical(|)"));			// 0
			AddString(_T("Horizontal(-)"));			// 1
			if (m_StrData.GetLength() > 0)
			{
				if (m_StrData == _T("Vertical(|)"))			//0
				{
					m_nValue = 0;
				}
				else if (m_StrData == _T("Horizontal(-)"))		// 1
				{
					m_nValue = 1;
				}

			}
		}
		else if (m_iSubItem == 6)
		{
			AddString(_T("Count"));			// 0
			AddString(_T("Pitch"));			// 1
			if (m_StrData.GetLength() > 0)
			{
				if (m_StrData == _T("Count"))			//0
				{
					m_nValue = 0;
				}
				else if (m_StrData == _T("Pitch"))		// 1
				{
					m_nValue = 1;
				}

			}
		}
		else if (m_iSubItem == 9)
		{
			AddString(_T("42135"));
			AddString(_T("24153"));
			AddString(_T("12345"));
			AddString(_T("54321"));
			if (m_StrData.GetLength() > 0)
			{
				if (m_StrData == _T("42135"))			//0
				{
					m_nValue = 0;
				}
				else if (m_StrData == _T("24153"))		// 1
				{
					m_nValue = 1;
				}
				else if (m_StrData == _T("12345"))		// 1
				{
					m_nValue = 2;
				}
				else if (m_StrData == _T("54321"))		// 1
				{
					m_nValue = 3;
				}

			}
		}
		else if (m_iSubItem == 10)		//BIT
		{

			for (int i = 0; i < 32; i++)
			{
				szMsg.Format(_T("%d"), i);
				AddString(szMsg);
			}
			SetMinVisibleItems(GetCount());
		
			for (int i = 0; i < 32; i++)
			{
				if (m_StrData.GetLength() > 0)
				{

					szMsg.Format(_T("%d"), i);
					if (m_StrData == szMsg)
					{
						m_nValue = i;
					}
				}

			}
		}
	}	

	SetCurSel(m_nValue);
	//SetFocus();	

	return 0;
}

BOOL CWizardCombo::PreTranslateMessage(MSG* pMsg) 
{
	if( pMsg->message == WM_KEYDOWN )	
	{		
		if(pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)	
		{
			::TranslateMessage(pMsg);
			::DispatchMessage(pMsg);			
			return TRUE;
		}	
	}	
	return CComboBox::PreTranslateMessage(pMsg);
}


void CWizardCombo::OnKillFocus(CWnd* pNewWnd) 
{	
	//int nIndex = GetCurSel();
	//
	CComboBox::OnKillFocus(pNewWnd);

	//CString str;	
	//GetWindowText(str);
	//// Send Notification to parent of ListView ctrl	
	//LV_DISPINFO lvDispinfo;
	//lvDispinfo.hdr.hwndFrom = GetParent()->m_hWnd;
	//lvDispinfo.hdr.idFrom = GetDlgCtrlID();//that's us
	//lvDispinfo.hdr.code = LVN_ENDLABELEDIT;
	//lvDispinfo.item.mask = LVIF_TEXT | LVIF_PARAM;	
	//lvDispinfo.item.iItem = m_iItem;
	//lvDispinfo.item.iSubItem = m_iSubItem;
	//lvDispinfo.item.pszText = m_bVK_ESCAPE ? NULL : LPTSTR((LPCTSTR)str);
	//lvDispinfo.item.cchTextMax = str.GetLength();
	//lvDispinfo.item.lParam = GetItemData(GetCurSel());
	//if(nIndex!=CB_ERR)
	//	GetParent()->GetParent()->SendMessage(WM_NOTIFY, GetParent()->GetDlgCtrlID(), (LPARAM)&lvDispinfo);
	//PostMessage(WM_CLOSE);	
}

//need to catch the VK_ESCAPE for the notification msg
void CWizardCombo::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if(nChar == VK_ESCAPE || nChar == VK_RETURN)	
	{		
		if( nChar == VK_ESCAPE)
			m_bVK_ESCAPE = 1;
		GetParent()->SetFocus();		
		return;	
	}	
	CComboBox::OnChar(nChar, nRepCnt, nFlags);
}

//doing this hence we are "modaless" and need to clean up me self
void CWizardCombo::OnNcDestroy() 
{
	CComboBox::OnNcDestroy();		
	delete this;
}

void CWizardCombo::OnCloseup() 
{
	//GetParent()->PostMessage(WM_LBUTTONUP);
	//GetParent()->SetFocus();
	//GetParent()->PostMessage(WM_LBUTTONUP);
	int nIndex = GetCurSel();

	//CComboBox::OnKillFocus(pNewWnd);

	CString str;
	GetWindowText(str);
	// Send Notification to parent of ListView ctrl	
	LV_DISPINFO lvDispinfo;
	lvDispinfo.hdr.hwndFrom = GetParent()->m_hWnd;
	lvDispinfo.hdr.idFrom = GetDlgCtrlID();//that's us
	lvDispinfo.hdr.code = LVN_ENDLABELEDIT;
	lvDispinfo.item.mask = LVIF_TEXT | LVIF_PARAM;
	lvDispinfo.item.iItem = m_iItem;
	lvDispinfo.item.iSubItem = m_iSubItem;
	lvDispinfo.item.pszText = m_bVK_ESCAPE ? NULL : LPTSTR((LPCTSTR)str);
	lvDispinfo.item.cchTextMax = str.GetLength();
	lvDispinfo.item.lParam = GetItemData(GetCurSel());
	if (nIndex != CB_ERR)
		GetParent()->GetParent()->SendMessage(WM_NOTIFY, GetParent()->GetDlgCtrlID(), (LPARAM)&lvDispinfo);
	PostMessage(WM_CLOSE);
}

void CWizardCombo::OnSize(UINT nType, int cx, int cy) 
{
	CComboBox::OnSize(nType, cx, cy);
}