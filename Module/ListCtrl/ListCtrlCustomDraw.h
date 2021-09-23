#if !defined(AFX_LISTCTRLCUSTOMDRAW_H__F69998D3_4527_11D5_8B9C_00E04C398DD0__INCLUDED_)
#define AFX_LISTCTRLCUSTOMDRAW_H__F69998D3_4527_11D5_8B9C_00E04C398DD0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListCtrlCustomDraw.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CListCtrlCustomDraw window

class CListCtrlCustomDraw : public CListCtrl
{
// Construction
public:
	CListCtrlCustomDraw();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListCtrlCustomDraw)
	public:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CListCtrlCustomDraw();

	CFont* m_pOldItemFont;
	CFont* m_pOldSubItemFont;

	//
	// Callbacks for whole control
	//
	
	// do we want to do the drawing ourselves?
	virtual BOOL IsDraw() { return false; }
	// if we are doing the drawing ourselves
	// override and put the code in here
	// and return TRUE if we did indeed do
	// all the drawing ourselves
	virtual BOOL OnDraw(CDC* /*pDC*/) { return false; }
	// do we want to handle custom draw for
	// individual items
	virtual BOOL IsNotifyItemDraw() { return false; }
	// do we want to be notified when the
	// painting has finished
	virtual BOOL IsNotifyPostPaint() { return false; }
	// do we want to do any drawing after
	// the list control is finished
	virtual BOOL IsPostDraw() { return false; }
	// if we are doing the drawing afterwards ourselves
	// override and put the code in here
	// the return value is not used here
	virtual BOOL OnPostDraw(CDC* /*pDC*/) { return false; }
	
	//
	// Callbacks for each item
	//
	
	// return a pointer to the font to use for this item.
	// return NULL to use default
	virtual CFont* FontForItem(int /*nItem*/, UINT /*nState*/, LPARAM /*lParam*/) { return NULL; }
	// return the text color to use for this item
	// return CLR_DEFAULT to use default
	virtual COLORREF TextColorForItem(int /*nItem*/, UINT /*nState*/, LPARAM /*lParam*/) { return CLR_DEFAULT; }
	// return the background color to use for this item
	// return CLR_DEFAULT to use default
	virtual COLORREF BkColorForItem(int /*nItem*/, UINT /*nState*/, LPARAM /*lParam*/) { return CLR_DEFAULT; }
	// do we want to do the drawing for this item ourselves?
	virtual BOOL IsItemDraw(int /*nItem*/, UINT /*nState*/, LPARAM /*lParam*/) { return false; }
	// if we are doing the drawing ourselves
	// override and put the code in here
	// and return TRUE if we did indeed do
	// all the drawing ourselves
	virtual BOOL OnItemDraw(CDC* /*pDC*/, int /*nItem*/, UINT /*nState*/, LPARAM /*lParam*/) { return false; }
	// do we want to handle custom draw for
	// individual sub items
	virtual BOOL IsNotifySubItemDraw(int /*nItem*/, UINT /*nState*/, LPARAM /*lParam*/) { return false; }
	// do we want to be notified when the
	// painting has finished
	virtual BOOL IsNotifyItemPostPaint(int /*nItem*/, UINT /*nState*/, LPARAM /*lParam*/) { return false; }
	// do we want to do any drawing after
	// the list control is finished
	virtual BOOL IsItemPostDraw() { return false; }
	// if we are doing the drawing afterwards ourselves
	// override and put the code in here
	// the return value is not used here
	virtual BOOL OnItemPostDraw(CDC* /*pDC*/, int /*nItem*/, UINT /*nState*/, LPARAM /*lParam*/) { return false; }

	//
	// Callbacks for each sub item
	//
	
	// return a pointer to the font to use for this sub item.
	// return NULL to use default
	virtual CFont* FontForSubItem(int /*nItem*/, int /*nSubItem*/, UINT /*nState*/, LPARAM /*lParam*/) { return NULL; }
	// return the text color to use for this sub item
	// return CLR_DEFAULT to use default
	virtual COLORREF TextColorForSubItem(int /*nItem*/, int /*nSubItem*/, UINT /*nState*/, LPARAM /*lParam*/) { return CLR_DEFAULT; }
	// return the background color to use for this sub item
	// return CLR_DEFAULT to use default
	virtual COLORREF BkColorForSubItem(int /*nItem*/, int /*nSubItem*/, UINT /*nState*/, LPARAM /*lParam*/) { return CLR_DEFAULT; }
	// do we want to do the drawing for this sub item ourselves?
	virtual BOOL IsSubItemDraw(int /*nItem*/, int /*nSubItem*/, UINT /*nState*/, LPARAM /*lParam*/) { return false; }
	// if we are doing the drawing ourselves
	// override and put the code in here
	// and return TRUE if we did indeed do
	// all the drawing ourselves
	virtual BOOL OnSubItemDraw(CDC* /*pDC*/, int /*nItem*/, int /*nSubItem*/, UINT /*nState*/, LPARAM /*lParam*/) { return false; }
	// do we want to be notified when the
	// painting has finished
	virtual BOOL IsNotifySubItemPostPaint(int /*nItem*/, int /*nSubItem*/, UINT /*nState*/, LPARAM /*lParam*/) { return false; }
	// do we want to do any drawing after
	// the list control is finished
	virtual BOOL IsSubItemPostDraw() { return false; }
	// if we are doing the drawing afterwards ourselves
	// override and put the code in here
	// the return value is not used here
	virtual BOOL OnSubItemPostDraw(CDC* /*pDC*/, int /*nItem*/, int /*nSubItem*/, UINT /*nState*/, LPARAM /*lParam*/) { return false; }
	
	// Generated message map functions
protected:
	//{{AFX_MSG(CListCtrlCustomDraw)
	afx_msg void OnCustomdraw(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTCTRLCUSTOMDRAW_H__F69998D3_4527_11D5_8B9C_00E04C398DD0__INCLUDED_)
