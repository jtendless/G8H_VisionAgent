#pragma once


// CModelSubManualParaDlg 대화 상자

class CModelSubManualParaDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CModelSubManualParaDlg)

public:
	CModelSubManualParaDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CModelSubManualParaDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODEL_SUB_MANUAL_PARA_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnDestroy();

	BOOL InitCtrl();
	BOOL InitPara();
	BOOL SavePara();
	BOOL CheckChangeData();

	CNumEdit m_editLoaderXAlignPos;
	CNumEdit m_editLoaderXPickupPos;
	CNumEdit m_editUnloaderXPickupPos;
	CNumEdit m_editPaperUnloaderXPickupPos;
};
