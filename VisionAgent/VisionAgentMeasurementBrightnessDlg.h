#pragma once


// CVisionAgentMeasurementBrightnessDlg 대화 상자

class CVisionAgentMeasurementBrightnessDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVisionAgentMeasurementBrightnessDlg)

public:
	CVisionAgentMeasurementBrightnessDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CVisionAgentMeasurementBrightnessDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VISION_AGENT_MEASUREMENT_BRIGHTNESS_DIALOG  };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	//afx_msg void OnBnClicked10xLCoaxialDn10Btn();

	afx_msg void OnBnClickedUpDownBtnBtn(UINT uID);

	afx_msg void OnBnClickedBtnLightOffAll();
	afx_msg void OnBnClickedLightOnBacklightBtn();
	afx_msg void OnBnClickedLightOffBacklightBtn();
	afx_msg void OnBnClickedLightOnAoiLightOnBtn();
	afx_msg void OnBnClickedLightOnAoiLightOffBtn();

	CNumEdit m_editAoiLightVal[AOI_LIGHT_CH_COUNT];
	afx_msg void OnBnClickedBtnBrightnessReview10xLightOn();
	afx_msg void OnBnClickedBtnBrightnessPreAlignLightOn();
	afx_msg void OnBnClickedBtnBrightnessBoxAlignLeftLightOn();
	afx_msg void OnBnClickedBtnBrightnessBoxAlignRightLightOn();
	afx_msg void OnBnClickedBtnBrightnessReview10xLightOff();
	afx_msg void OnBnClickedBtnBrightnessPreAlignLightOff();
	afx_msg void OnBnClickedBtnBrightnessBoxAlignLeftLightOff();
	afx_msg void OnBnClickedBtnBrightnessBoxAlignRightLightOff();
};
