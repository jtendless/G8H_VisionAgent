// NumEdit.cpp : implementation file
//

#include "stdafx.h"
#include "NumEdit.h"

#include <errno.h>



/////////////////////////////////////////////////////////////////////////////
// CNumEdit

CNumEdit::CNumEdit()
{
	m_eType = TypeDouble;
	m_bRejectingChange = false;
	m_bPositiveOnly = FALSE;
}

CNumEdit::~CNumEdit()
{
}


BEGIN_MESSAGE_MAP(CNumEdit, CEdit)
	//{{AFX_MSG_MAP(CNumEdit)
	ON_WM_CHAR()
	ON_CONTROL_REFLECT(EN_UPDATE, OnUpdate)
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNumEdit message handlers

int CNumEdit::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)
		return -1;

	ModifyStyle(ES_LEFT | ES_CENTER, ES_RIGHT);


	return 0;
}


void CNumEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	switch (nChar)
	{
	case VK_RETURN:
		{
			CString strValue;
			GetWindowText(strValue);

			if(strValue != m_strLastValidValue)
			{
				GetParent()->PostMessage(WM_COMMAND, EN_UPDATE,GetDlgCtrlID());
			}
			break;
		}

	case VK_ESCAPE:
		Undo();
		//SetWindowText(m_strLastValidValue);
		break;
	case VK_BACK:
	case 0x0A: // Shift+Enter (= linefeed)
	case VK_TAB:
		break;
	default:
		m_nLastSel = GetSel();
		GetWindowText(m_strLastValidValue);
		break;
	}

	CEdit::OnChar(nChar, nRepCnt, nFlags);
}

void CNumEdit::OnUpdate() 
{
	if (! m_bRejectingChange)
	{
		CString aValue;
		GetWindowText(aValue);
		LPTSTR aEndPtr=NULL;
		union
		{
			long aLongValue;
			double aDoubleValue;
		};

		errno = 0;
		switch (m_eType)
		{
		case TypeLong:
			aLongValue = _tcstol(aValue, &aEndPtr, 10);
			break;
		case TypeDouble:
			aDoubleValue = _tcstod(aValue, &aEndPtr);
			break;
		}

		if (! (*aEndPtr) && errno != ERANGE 
			||  (!m_bPositiveOnly && aValue == _T("-")))
		{
			m_strLastValidValue = aValue;
		}
		else
		{
			m_bRejectingChange = true;
			SetWindowText(m_strLastValidValue);
			m_bRejectingChange = false;
			SetSel(m_nLastSel);
		}
	}
}

void CNumEdit::OnSetFocus(CWnd* pOldWnd)
{
	//ModifyStyle(ES_RIGHT | ES_CENTER, ES_LEFT);
	CEdit::OnSetFocus(pOldWnd);
}

void CNumEdit::OnKillFocus(CWnd* pNewWnd)
{
	//ModifyStyle(ES_LEFT | ES_CENTER, ES_RIGHT);
	CEdit::OnKillFocus(pNewWnd);

	if(m_strOldValue != m_strLastValidValue)
	{
		PostNumChangeMessage();
	}
}



float CNumEdit::GetFloat()
{
	CString aValue;
	GetWindowText(aValue);

	return (float)_tstof(aValue);
}

void  CNumEdit::SetFloat(float value)
{
	CString aValue;

	aValue.Format(_T("%.3f"), value);
	//ModifyStyle(ES_LEFT | ES_CENTER, ES_RIGHT);
	m_strOldValue = aValue;

	SetWindowText(aValue);
	
}

void  CNumEdit::SetEmpty()
{
	SetWindowText(_T(""));
	m_strOldValue = _T("");
}


int  CNumEdit::GetInt()
{
	CString aValue;
	GetWindowText(aValue);

	return _ttoi(aValue);
}

void  CNumEdit::SetInt(int value)
{
	CString aValue;

	aValue.Format(_T("%d"), value);
	//ModifyStyle(ES_LEFT | ES_CENTER, ES_RIGHT);

	m_strOldValue = aValue;
	SetWindowText(aValue);
}

void CNumEdit::PostNumChangeMessage()
{
	m_strOldValue = m_strLastValidValue;
	UINT id = GetDlgCtrlID();
	WPARAM wParam = MAKELONG( GetDlgCtrlID(), EN_NUMCHANGE);
	GetParent()->PostMessage(WM_COMMAND, wParam, (LPARAM)this->m_hWnd);
}

BOOL CNumEdit::IsEmpty()
{
	CString strText;
	GetWindowText(strText);

	return strText.IsEmpty();
}

void CNumEdit::SetPositiveOnly(BOOL bEnable)
{
	m_bPositiveOnly = bEnable;
}


BOOL CNumEdit::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYUP)
	{
		switch(pMsg->wParam)
		{
			case VK_RETURN :
			{
				if(m_strOldValue != m_strLastValidValue)
				{
					PostNumChangeMessage();
					return TRUE;
				}
				break;
			}
			case VK_ESCAPE :
				Undo();
				return TRUE;
		}
	}

	return CEdit::PreTranslateMessage(pMsg);
}

