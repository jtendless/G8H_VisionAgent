#if !defined(AFX_NUMEDIT_H__06CEFB27_19AE_4980_8690_E874F8853F9D__INCLUDED_)
#define AFX_NUMEDIT_H__06CEFB27_19AE_4980_8690_E874F8853F9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NumEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNumEdit window
#define EN_NUMCHANGE  0x0604

#define ON_EN_NUMCHANGE(id, memberFxn) \
	ON_CONTROL(EN_NUMCHANGE, id, memberFxn)


class CNumEdit : public CEdit
{
// Construction
public:
	CNumEdit();

	enum eType
	{
		TypeLong,
		TypeDouble
	};

// Attributes
protected:
	eType m_eType;
	CString m_strLastValidValue;
	UINT m_nLastSel;
	bool m_bRejectingChange;
	BOOL m_bPositiveOnly;

	CString m_strOldValue;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNumEdit)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNumEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CNumEdit)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnUpdate();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

	virtual BOOL PreTranslateMessage(MSG* pMsg);

	void PostNumChangeMessage();

public:

	float GetFloat();
	void  SetFloat(float value);
	void  SetEmpty();
	
	int	  GetInt();
	void  SetInt(int value);

	BOOL  IsEmpty();

	void  SetPositiveOnly(BOOL bEnable = TRUE);
	
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NUMEDIT_H__06CEFB27_19AE_4980_8690_E874F8853F9D__INCLUDED_)
