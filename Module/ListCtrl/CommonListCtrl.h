#pragma once

// CCommonListCtrl
#include "Vision/VisionAgentDefine.h"
#include "ListCtrlCustomDraw.h"
#include "Common/CommonDefine.h"
#include <map>

#define WM_CLICK		(WM_USER+100)
#define WM_DBLCLK		(WM_USER+101)
#define WM_END_EDIT		(WM_USER+102)

#define MAX_COL_NUM 20


class CAdvancedEditCell;
class CWizardCombo;
class CCommonListCtrl : public CListCtrlCustomDraw
{
	//DECLARE_DYNAMIC(CWeldingMethodListCtrl)

public:
	CCommonListCtrl(int nIsFlatness = FALSE);
	virtual ~CCommonListCtrl();

public:

	int m_nIsFlatness;
	int m_nCheckStatus[4];


	CString m_strPreDirection;
	stCellInfo m_stCellInfo[MAX_COL_NUM];
	stComboInfo m_stComboInfo[MAX_COL_NUM];

	int m_nMaxRow;
	int m_nMaxCol;

	int m_nSelectedItemNumber;
	int m_nSelectedSubItemNumber;

	int m_nSelectedItemEndNumber;
	int m_nSelectedSubItemEndNumber;

	//// For EditCell
	CAdvancedEditCell *m_pEdit;

	CAdvancedEditCell*  EditSubItem(int Item, int Column);
	int	    HitTestEx(CPoint& Point, int* Column);
	int	    InsertItemEx(int Item);
	void	InsertNumber(int Item, int Column);
	void    Resize(int cx, int cy);
	void	DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	/// For ComboBox
	CWizardCombo *m_pCombo;
	CWizardCombo* ShowComboList(int nItem, int nCol, CString StrData);
	BOOL m_bIsCombox;
	BOOL SetColData(int nSubNum, int nQuan, CString* strData);
	CButton *m_pButton;

	CPoint HitPt;
	int HitItem;

	int m_nListCnt;

	BOOL m_bClipboardOnOff;

	void SetListColumn(CString *strData, int* nSize, int nQuan, COLORREF *crBkColorInfo, COLORREF *crTextColorInfo, int *nInputMethod);
	void ColDataWrite(CStdioFile *file);
	BOOL InitCheckCtrl();
	BOOL AddCheckCtrl(int nCol, int nCheckStatus);
	BOOL AddListData(int nRow, CString *strData);
	void AddListColumn();
	BOOL UpdateListData(int nRow, CString *strData);
	BOOL DeleteAllListData();
	BOOL DeleteListData(int nNo);

	int SaveListData(BOOL bIsAuto = FALSE);
	BOOL GetListData(int nRow, CString *strData);
	BOOL GetListAllData(CString *strData);
	void AddOffsetListData(int nIndex[2], double dPosData[6]);

	int GetSelectedItemNumber() { return m_nSelectedItemNumber; };
	int GetSelectedSubItemNumber() { return m_nSelectedSubItemNumber; };

	int GetMaxListCount();
	//BOOL GetListData(int nRow, MODEL_WELDING_METHOD_LIST *dWeldingMethodList);
	BOOL IsReal(CString Str);

	int LoadPointData(char* pchPathName);
	BOOL TapDataParsing(CString strText, CString *strResult, INT *nResultRowQuan, INT *nResultColQuan);
	BOOL ClipBoradDataMultiWrite(CString *strResult, INT nResultRowQuan, INT nResultColQuan);

	BOOL ListDataMultiRead(CString &strResult);
	void SetClipboardOption(bool bOnOff);
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

	//Clipboard값 복사하기.
	bool CopyToClipboard(CString &strText);
	bool CopyToApp(CString &strText);

	//CSV 파일 로드.
	CString LoadDataFromCsv(CString strFilePath, CString *strResult, int *nRowQuan);
	CString LoadDataFromCsvEx(CString strFilePath, CString * strResult, int * nRowQuan);
	CString SaveDataToCsv(CString strFilePath);

	CString SaveDataToCsvEx(CString strFilePath);

	void SetItemTextEx(INT nRow, INT nCol, CString strData);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEndLabelEdit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	LRESULT OnCheckStatus(WPARAM wParam, LPARAM lParam);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

