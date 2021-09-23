#pragma once
#include "../Module/Control/NumEdit.h"
#include "ListCtrl/CommonListCtrl.h"
#define MODEL_CHANGE_SPREAD_MAX_COL		4
// CVisionAgentModelModelChangeDlg 대화 상자

class CVisionAgentModelModelChangeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVisionAgentModelModelChangeDlg)

public:
	CVisionAgentModelModelChangeDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CVisionAgentModelModelChangeDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODEL_SUB_MODEL_CHANGE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	bool m_bDialog_Entry;
	void UpdateUI();
	DECLARE_MESSAGE_MAP()
public:

	CCommonListCtrl *m_pListCtrl;
	CStringArray	m_procsTexts;
	void InitCtrl();
	CComboBox m_ComboModelNames;
	CStatic m_StaticCurrentName;

	CNumEdit m_EditNumber;
	CNumEdit m_EditRecipeID;

	CEdit m_EditStickRGB;

	BOOL RenameDirectoryFile(CString NewDirName);
	BOOL NewDirectoryFile(LPCTSTR RootDir);
	BOOL DeleteDirectoryFile(LPCTSTR RootDir);
	void InitListControlPara();
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedVisonAgentModelModelChangeBtnNew();
	afx_msg void OnBnClickedVisonAgentModelModelChangeBtnLoad();
	afx_msg void OnBnClickedVisonAgentModelModelChangeBtnRename();
	afx_msg void OnBnClickedVisonAgentModelModelChangeBtnDelete();
	
	void SetInitListCtrl();
	void ResetListCtrl();
	void GetListCtrl();
	afx_msg void OnDestroy();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};
