#pragma once


// CAlignPara2Dlg dialog

class CAlignPara2Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAlignPara2Dlg)

public:
	CAlignPara2Dlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CAlignPara2Dlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODEL_SUB_ALIGN_PARA2_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

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

	//Vertical Pre Align
	CNumEdit m_editVerticalPreAlignTargetCount;
	CNumEdit m_editVerticalPreAlignTargetX;
	CNumEdit m_editVerticalPreAlignTargetY;
	CNumEdit m_editVerticalPreAlignCoAxial;
	CNumEdit m_editVerticalPreAlignRing;
	CNumEdit m_editVerticalPreAlignThreshold;
	CNumEdit m_editVerticalPreAlignBackLight;
	
	CComboBox m_comboVerticalPreAlignLightType;
	CComboBox m_comboVerticalPreAlignMarkType;
	CComboBox m_comboVerticalPreAlignFocusType;
	CComboBox m_comboVerticalPreAlignBlackWhiteType;
	CClrButton m_btnVerticalPreAlignLightOn;
	CClrButton m_btnVerticalPreAlignLightOff;

	//Vertical Main Align
	CNumEdit m_editVerticalMainAlignTargetCount;
	CNumEdit m_editVerticalMainAlignTargetX;
	CNumEdit m_editVerticalMainAlignTargetY;
	CNumEdit m_editVerticalMainAlignCoAxial;
	CNumEdit m_editVerticalMainAlignRing;
	CNumEdit m_editVerticalMainAlignThreshold;
	CNumEdit m_editVerticalMainAlignBackLight;

	CComboBox m_comboVerticalMainAlignLightType;
	CComboBox m_comboVerticalMainAlignMarkType;
	CComboBox m_comboVerticalMainAlignFocusType;
	CComboBox m_comboVerticalMainAlignBlackWhiteType;
	CClrButton m_btnVerticalMainAlignLightOn;
	CClrButton m_btnVerticalMainAlignLightOff;

	//Sw Align
	CNumEdit m_editSwAlignTargetCount;
	CNumEdit m_editSwAlignTargetX;
	CNumEdit m_editSwAlignTargetY;
	CNumEdit m_editSwAlignCoAxial;
	CNumEdit m_editSwAlignRing;
	CNumEdit m_editSwAlignThreshold;
	CNumEdit m_editSwAlignBacklight;
	CComboBox m_comboSwAlignLightType;
	CComboBox m_comboSwAlignMarkType;
	CComboBox m_comboSwAlignFocusType;
	CComboBox m_comboSwAlignBlackWhiteType;
	CClrButton m_btnSwAlignLightOn;
	CClrButton m_btnSwAlignLightOff;

	//Measure Half Edge Hole
	CNumEdit m_editTPCoAxial[3];
	CNumEdit m_editTPRing[3];
	CNumEdit m_editTPThreshold[3];
	CNumEdit m_editTPBacklight[3];
	CComboBox m_comboTPLightType;
	CComboBox m_comboTPMarkType;
	CComboBox m_comboTPFocusType;
	CComboBox m_comboTPBlackWhiteType;
	CClrButton m_btnTPLightOn;
	CClrButton m_btnTPLightOff;

	//x20 light ratio
	CNumEdit m_editx20CoAxial;
	CNumEdit m_editx20Ring;
	CNumEdit m_editx20BackLight;
	//x20 light ratio
	CNumEdit m_editx50CoAxial;
	CNumEdit m_editx50Ring;
	CNumEdit m_editx50BackLight;

	afx_msg void OnBnClickedBtnVerticalPreAlignLightOn();
	afx_msg void OnBnClickedBtnVerticalPreAlignLightOff();
	afx_msg void OnBnClickedBtnVerticalMainAlignLightOn();
	afx_msg void OnBnClickedBtnVerticalMainAlignLightOff();
	afx_msg void OnBnClickedBtnSwAlignLightOn();
	afx_msg void OnBnClickedBtnSwAlignLightOff();
	afx_msg void OnBnClickedBtnTPLightOn();
	afx_msg void OnBnClickedBtnTPLightOff();
	afx_msg void OnBnClickedBtnMeasureHalfEdgeHoleLightOn2();
	afx_msg void OnBnClickedBtnMeasureHalfEdgeHoleLightOn3();
};
