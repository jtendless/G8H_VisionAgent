#pragma once
#include "resource.h"
// CVisionAgentLogDlg 대화 상자입니다.

#include "../Module/Log/LogDefine.h"

class CVisionAgentLogDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVisionAgentLogDlg)

public:
	CVisionAgentLogDlg(CWnd* pParent, INT nIndex);   // 표준 생성자입니다.
	virtual ~CVisionAgentLogDlg();

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_LOG };

	/* controls */
public:
	INT m_Index;
	CListCtrl	m_HistoryListCtrl;

	/* methods */
public:
	afx_msg LRESULT UpdateLogView(WPARAM wParam, LPARAM lParam);

public:
	CSize		m_ItemSize;
	CImageList	m_ImageList;
	int			m_nInsertItemNum;

public:
	void AddListData(CString StrTime, CString Str);
	void AddListColumn();
	void ClearListData();

	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
};
