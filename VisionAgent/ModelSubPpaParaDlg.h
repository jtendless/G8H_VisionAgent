#pragma once


// CModelSubPpaParaDlg 대화 상자

class CModelSubPpaParaDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CModelSubPpaParaDlg)

public:
	CModelSubPpaParaDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CModelSubPpaParaDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODEL_SUB_PPA_PARA_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	BOOL InitCtrl();
	BOOL InitPara();
	BOOL SavePara();
	BOOL CheckChangeData();

	void BtnEnable(BOOL bEnable);

	//PPA
	CNumEdit m_editPpaTargetCount;
	CNumEdit m_editPpaTargetX;
	CNumEdit m_editPpaTargetY;
	CNumEdit m_editPpaCoAxial;
	CNumEdit m_editPpaRing;
	CNumEdit m_editPpaThreshold;
	CNumEdit m_editPpaBacklight;
	CComboBox m_comboPpaLightType;
	CComboBox m_comboPpaMarkType;
	CComboBox m_comboPpaFocusType;
	CComboBox m_comboPpaBlackWhiteType;
	CClrButton m_btnPpaLightOn;
	CClrButton m_btnPpaLightOff;

	//KJT 20210524
	CComboBox m_comboDivX;
	CComboBox m_comboDivY;
	CComboBox m_comboSlotQuantityXY;

	afx_msg void OnBnClickedBtnPpaLightOn();
	afx_msg void OnBnClickedBtnPpaLightOff();
};
