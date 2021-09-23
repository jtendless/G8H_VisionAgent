#pragma once

#define ECS_SHEET_LIST_MAX_COL 3
#define ECS_SHEET_LIST_MAX_ROW 37
// CVisionAgentECSSheetDlg 대화 상자입니다.

class CVisionAgentECSSheetDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVisionAgentECSSheetDlg)

public:
	CVisionAgentECSSheetDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CVisionAgentECSSheetDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VISION_AGENT_ECS_SHEET_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	//TSpread*		m_Cimspread;
	//TSpread*		m_Stagespread;
	CCommonListCtrl *m_pCimListCtrl;
	CCommonListCtrl *m_pStageListCtrl;
	CString m_CurString;
	CStringArray	m_procsTexts;
	//void InitSpread();
	void InitList();
	void SetCimList(CCommonListCtrl *ListCtrl, SHEET_INFORMATION_BLOCK SheetInfo);
	void SetMachineList(CCommonListCtrl *ListCtrl, SHEET_INFORMATION_BLOCK SheetInfo);
	void GetMachineList(CCommonListCtrl *ListCtrl, PSHEET_INFORMATION_BLOCK pSheetInfo);
	char* ConvertPlcString(CString strData);

	void SetCimUI(CCommonListCtrl *ListCtrl, SHEET_INFORMATION_BLOCK SheetInfo);
	void SetMahcineUI(CCommonListCtrl *ListCtrl, SHEET_INFORMATION_BLOCK SheetInfo);



	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedMaterialCountChangeBtn();
	afx_msg void OnBnClickedMaterialStatusChangeBtn();
	afx_msg void OnBnClickedSheetMoveInBtn();
	afx_msg void OnBnClickedSheetMoveOutBtn();
	afx_msg void OnBnClickedSheetInformationRequestBtn();
	afx_msg void OnBnClickedSheetInformationUpdateBtn();
	afx_msg void OnBnClickedSheetInformationRemoveBtn();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedMagazineProcessCompleteReportBtn1();
	afx_msg void OnBnClickedMagazineProcessCompleteReportBtn2();
	afx_msg void OnBnClickedMagazineProcessCompleteReportBtn3();
	afx_msg void OnBnClickedMagazineProcessCompleteReportBtn4();
	afx_msg void OnBnClickedMagazineProcessCompleteReportBtn5();
	afx_msg void OnBnClickedMagazineProcessCompleteReportBtn6();
	afx_msg void OnBnClickedMagazineDataRequestBtn();
	afx_msg void OnBnClickedSheetInformationDownloadBtn();
	afx_msg void OnBnClickedSheetMaskLoadRequestBtn();
	afx_msg void OnBnClickedSheetMaskUnloadRequestBtn();
	afx_msg void OnBnClickedSheetMaskLoadCompleteBtn();
	afx_msg void OnBnClickedSheetMaskUnloadCompleteBtn();
	afx_msg void OnBnClickedMaterialJudgeResultBtn();
};
