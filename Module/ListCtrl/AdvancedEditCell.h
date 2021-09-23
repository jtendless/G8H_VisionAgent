#if !defined(AFX_ADVANCEDEDITCELL_H__9CC39444_7BC3_11D5_94D0_0090272D6160__INCLUDED_)
#define AFX_ADVANCEDEDITCELL_H__9CC39444_7BC3_11D5_94D0_0090272D6160__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AdvancedEditCell.h : header file
//

#include "../Control/NumEdit.h"

/////////////////////////////////////////////////////////////////////////////
// CAdvancedEditCell window

class CAdvancedEditCell : public CNumEdit
{
// Construction
public:
	CAdvancedEditCell(void* pCtrl, int iItem, int iSubItem, CString sInitText, int nMode);
	
    void  SetListText();
	BOOL IsReal(CString Str);
   
protected:

	int         m_nMode;
    int			Item;
    int			SubItem;
    CString		InitText;
    BOOL		bEscape;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdvancedEditCell)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAdvancedEditCell();

	// Generated message map functions
protected:
	//{{AFX_MSG(CAdvancedEditCell)
		// NOTE - the ClassWizard will add and remove member functions here.
	afx_msg void OnKillFocus(CWnd* pNewWnd);
    afx_msg void OnNcDestroy();
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADVANCEDEDITCELL_H__9CC39444_7BC3_11D5_94D0_0090272D6160__INCLUDED_)
