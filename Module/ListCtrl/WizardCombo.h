#if !defined(AFX_WIZARDCOMBO_H__AA020CD5_51B2_4BF8_BE03_92E2CFF8FFEA__INCLUDED_)
#define AFX_WIZARDCOMBO_H__AA020CD5_51B2_4BF8_BE03_92E2CFF8FFEA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WizardCombo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWizardCombo window

class CWizardCombo : public CComboBox
{
// Construction
public:
	CWizardCombo(int iItem, int iSubItem, CString StrData, int ListIndex);

// Attributes
private:
	int 	m_iItem;
	int 	m_iSubItem;
	int		m_nValue;
	int		m_ListIndex;
	BOOL	m_bVK_ESCAPE;	
	CString m_StrData;

// Operations
public:
	CFont m_Font;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWizardCombo)
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWizardCombo();

	// Generated message map functions
protected:
	//{{AFX_MSG(CWizardCombo)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnNcDestroy();
	afx_msg void OnCloseup();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIZARDCOMBO_H__AA020CD5_51B2_4BF8_BE03_92E2CFF8FFEA__INCLUDED_)
