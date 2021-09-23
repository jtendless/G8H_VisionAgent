#pragma once


// CAlignParaDlg 대화 상자

class CAlignParaDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAlignParaDlg)

public:
	CAlignParaDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CAlignParaDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODEL_SUB_ALIGN_PARA_DIALOG };
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

	//Box Left Align
	CNumEdit m_editBoxAlignLeftTargetCount;
	CNumEdit m_editBoxAlignLeftTargetX;
	CNumEdit m_editBoxAlignLeftTargetY;
	CNumEdit m_editBoxAlignLeftCoAxial;
	CNumEdit m_editBoxAlignLeftRing;
	CNumEdit m_editBoxAlignLeftThreshold;
	CComboBox m_comboBoxAlignLeftLightType;
	CComboBox m_comboBoxAlignLeftMarkType;
	CComboBox m_comboBoxAlignLeftFocusType;
	CComboBox m_comboBoxAlignLeftBlackWhiteType;
	CClrButton m_btnBoxAlignLeftLightOn;
	CClrButton m_btnBoxAlignLeftLightOff;

	//Box Align Right
	CNumEdit m_editBoxAlignRightTargetCount;
	CNumEdit m_editBoxAlignRightTargetX;
	CNumEdit m_editBoxAlignRightTargetY;
	CNumEdit m_editBoxAlignRightCoAxial;
	CNumEdit m_editBoxAlignRightRing;
	CNumEdit m_editBoxAlignRightThreshold;
	CComboBox m_comboBoxAlignRightLightType;
	CComboBox m_comboBoxAlignRightMarkType;
	CComboBox m_comboBoxAlignRightFocusType;
	CComboBox m_comboBoxAlignRightBlackWhiteType;
	CClrButton m_btnBoxAlignRightLightOn;
	CClrButton m_btnBoxAlignRightLightOff;

	//Pre Align
	CNumEdit m_editPreAlignTargetCount;
	CNumEdit m_editPreAlignTargetX;
	CNumEdit m_editPreAlignTargetY;
	CNumEdit m_editPreAlignCoAxial_L;
	CNumEdit m_editPreAlignRing_L;
	CNumEdit m_editPreAlignThreshold_L;
	CNumEdit m_editPreAlignCoAxial_R;
	CNumEdit m_editPreAlignRing_R;
	CNumEdit m_editPreAlignThreshold_R;
	CComboBox m_comboPreAlignLightType;
	CComboBox m_comboPreAlignMarkType;
	CComboBox m_comboPreAlignFocusType;
	CComboBox m_comboPreAlignBlackWhiteType;
	CClrButton m_btnPreAlignLightOn_L;
	CClrButton m_btnPreAlignLightOn_R;
	CClrButton m_btnPreAlignLightOff;

	//Main 2P Align
	CNumEdit m_editMain2PAlignTargetCount;
	CNumEdit m_editMain2PAlignTargetX;
	CNumEdit m_editMain2PAlignTargetY;
	CNumEdit m_editMain2PAlignCoAxial;
	CNumEdit m_editMain2PAlignRing;
	CNumEdit m_editMain2PAlignThreshold;
	CNumEdit m_editMain2PAlignBackLight;
	CComboBox m_comboMain2PAlignLightType;
	CComboBox m_comboMain2PAlignMarkType;
	CComboBox m_comboMain2PAlignFocusType;
	CComboBox m_comboMain2PAlignBlackWhiteType;
	CClrButton m_btnMain2PAlignLightOn;
	CClrButton m_btnMain2PAlignLightOff;

	//Edge 4P Align
	CNumEdit m_editEdge4PAlignTargetCount;
	CNumEdit m_editEdge4PAlignTargetX;
	CNumEdit m_editEdge4PAlignTargetY;
	CNumEdit m_editEdge4PAlignCoAxial;
	CNumEdit m_editEdge4PAlignRing;
	CNumEdit m_editEdge4PAlignThreshold;
	CNumEdit m_editEdge4PAlignBacklight;
	CComboBox m_comboEdge4PAlignLightType;
	CComboBox m_comboEdge4PAlignMarkType;
	CComboBox m_comboEdge4PAlignFocusType;
	CComboBox m_comboEdge4PAlignBlackWhiteType;
	CClrButton m_btnEdge4PAlignLightOn;
	CClrButton m_btnEdge4PAlignLightOff;

	//Tegkey Align
	CNumEdit m_editTegkeyAlignTargetCount;
	CNumEdit m_editTegkeyAlignTargetX;
	CNumEdit m_editTegkeyAlignTargetY;
	CNumEdit m_editTegkeyAlignCoAxial;
	CNumEdit m_editTegkeyAlignRing;
	CNumEdit m_editTegkeyAlignThreshold;
	CNumEdit m_editTegkeyAlignBacklight;
	CComboBox m_comboTegkeyAlignLightType;
	CComboBox m_comboTegkeyAlignMarkType;
	CComboBox m_comboTegkeyAlignFocusType;
	CComboBox m_comboTegkeyAlignBlackWhiteType;
	CClrButton m_btnTegkeyAlignLightOn;
	CClrButton m_btnTegkeyAlignLightOff;

	//PPA
	CNumEdit m_editPpaTargetCount;
	CNumEdit m_editPpaTargetX;
	CNumEdit m_editPpaTargetY;
	CNumEdit m_editPpaCoAxial[3];
	CNumEdit m_editPpaRing[3];
	CNumEdit m_editPpaThreshold[3];
	CNumEdit m_editPpaBacklight[3];
	CComboBox m_comboPpaLightType;
	CComboBox m_comboPpaMarkType;
	CComboBox m_comboPpaFocusType;
	CComboBox m_comboPpaBlackWhiteType;
	CClrButton m_btnPpaLightOn[3];
	CClrButton m_btnPpaLightOff;
	
	afx_msg void OnBnClickedBtnBoxAlignLeftLightOn();
	afx_msg void OnBnClickedBtnBoxAlignLeftLightOff();
	afx_msg void OnBnClickedBtnBoxAlignRightLightOn();
	afx_msg void OnBnClickedBtnBoxAlignRightLightOff();
	afx_msg void OnBnClickedBtnAlignParaPreAlignLightOnL();
	afx_msg void OnBnClickedBtnAlignParaPreAlignLightOnR();
	afx_msg void OnBnClickedBtnPreAlignLightOff();
	afx_msg void OnBnClickedBtnMain2pAlignLightOn();
	afx_msg void OnBnClickedBtnMain2pAlignLightOff();
	afx_msg void OnBnClickedBtnEdge4pAlignLightOn();
	afx_msg void OnBnClickedBtnEdge4pAlignLightOff();
	afx_msg void OnBnClickedBtnTegkeyAlignLightOn();
	afx_msg void OnBnClickedBtnTegkeyAlignLightOff();
	afx_msg void OnBnClickedBtnPpaLightOn2();
	afx_msg void OnBnClickedBtnPpaLightOff2();
	afx_msg void OnBnClickedBtnPpaLightOn3();
	afx_msg void OnBnClickedBtnPpaLightOn4();
};
