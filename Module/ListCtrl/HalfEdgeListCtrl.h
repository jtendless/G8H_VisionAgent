#pragma once

// CHalfEdgeListCtrl
#include "ListCtrlCustomDraw.h"
#define MAX_HALF_EDGE_LIST_COL 3
class CHalfEdgeListCtrl : public CListCtrlCustomDraw
{
	//DECLARE_DYNAMIC(CHalfEdgeListCtrl)

public:
	CHalfEdgeListCtrl();
	virtual ~CHalfEdgeListCtrl();

	// Attributes
protected:
public:
	enum
	{
		ePosX = 0,
		ePosY,
		ePosZ
	};


	int m_nCheckStatus[4];

	int m_nMaxRow;
	int m_nMaxCol;

	CEdit *m_pEdit;

	//// For EditCell
	CEdit*  EditSubItem(int Item, int Column);
	int	    HitTestEx(CPoint& Point, int* Column);
	int	    InsertItemEx(int Item);
	void	InsertNumber(int Item, int Column);
	void    Resize(int cx, int cy);
	void	DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	/// For ComboBox
	CComboBox *pList;
	CComboBox* ShowList(int nItem, int nCol, CString StrData);
	BOOL m_bIsCombox;

	CButton *m_pButton;

	CPoint HitPt;
	int m_nInspectListMode;
	int HitItem;
	int m_nInsertItemCount;
	int m_nSubItemNum;
	int m_nUpdatePointNumber;
	int m_nSelectedItemNumber;

	void SetListCtrlMode(int nInspectListMode);
	void InitialVelocityListCtrl();
	void AddAllListData();
	void AddListColumn();
	//BOOL AddListData(CString StrLabel, double dPosData[6]);
	BOOL InitCheckCtrl();
	BOOL AddCheckCtrl(int nCol, int nCheckStatus);
	BOOL AddListDataString(int nRow, CString *strData);
	BOOL AddListData(int nNo, double dValue[MAX_HALF_EDGE_LIST_COL]);
	void ColDataWrite(CStdioFile *file);
	CString SaveDataToCsv(CString strFilePath);
	CString LoadDataFromCsv(CString strFilePath, CString *strResult, int *nRowQuan);
	BOOL UpdateListData(double dPosData[MAX_HALF_EDGE_LIST_COL], int SelectIndex);
	BOOL DeleteAllListData();
	BOOL DeleteListData(int nNo);
	BOOL InsertListData(int nNo);
	int SaveListData(BOOL bIsAuto = FALSE);
	void GetListData();

	void AddOffsetListData(int nIndex[2], double dPosData[MAX_HALF_EDGE_LIST_COL]);

	int GetMaxListCount();
	void	ResetMaxListCount();
	BOOL GetListData(int nRow, double dData[MAX_HALF_EDGE_LIST_COL]);
	BOOL IsReal(CString Str);

	int LoadPointData(char* pchPathName);

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL
	virtual BOOL IsDraw();
	virtual BOOL OnDraw(CDC* pDC);
	virtual BOOL IsNotifyItemDraw();
	virtual BOOL IsNotifySubItemDraw(int nItem, UINT nState, LPARAM lParam);
	virtual COLORREF TextColorForSubItem(int nItem, int nSubItem, UINT nState, LPARAM lParam);
	virtual COLORREF BkColorForSubItem(int nItem, int nSubItem, UINT nState, LPARAM lParam);

	// Implementation
public:

	int GetItemHeight();
	void SetScroll();
	void HighlightSelectedItem();

protected:
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEndLabelEdit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);

	DECLARE_MESSAGE_MAP()
	LRESULT OnCheckStatus(WPARAM wParam, LPARAM lParam);
};


