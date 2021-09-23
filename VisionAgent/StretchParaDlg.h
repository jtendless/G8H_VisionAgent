#pragma once

// CStretchParaDlg 대화 상자

class CStretchParaDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CStretchParaDlg)

public:
	CStretchParaDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CStretchParaDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODEL_SUB_STRETCH_PARA_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedBtnStretchParaStepCountSet();

	BOOL InitCtrl();
	BOOL InitPara();
	BOOL SavePara();
	BOOL CheckChangeData();

	void BtnEnable(BOOL bEnable);

	CButton			m_chkUse[eGRIPPER_ROW_MAX];
	CNumEdit		m_editNewton[10][eGRIPPER_ROW_MAX];
	CNumEdit		m_editStepCount;
	CClrButton	m_btnStepCountSet;
	CNumEdit		m_editSpeedMax;
	CNumEdit		m_editSpeedMin;
	CNumEdit		m_editOkRange;
	CNumEdit		m_editDecelRange;
	CNumEdit		m_editReleaseForce;
	CNumEdit		m_editMaxForce;

	int m_nStepCount;
};
