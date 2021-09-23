#pragma once


// CInspectionParaDlg 대화 상자

class CInspectionParaDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInspectionParaDlg)

public:
	CInspectionParaDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CInspectionParaDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODEL_SUB_INSPECTION_PARA_DIALOG };
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

	void BtnEnable(BOOL bEnable);

	CComboBox m_comboPPADivXY;
	CNumEdit m_editDivX; //Cell Count X
	CNumEdit m_editDivY; //Cell Count Y
	CButton m_CheckOnlyUnloadingMode; //KJT 20210406
	CButton m_CheckTPUse;
	CButton m_CheckSWAlignFlowUse; //KJT 20210315
	CButton m_CheckPPAUse;
	CButton m_CheckAOIUse;
	CButton m_CheckAOIReviewUse;
	CButton m_Check3dFlowUse; //KJT 20210307
	CComboBox m_comboPPAAlignMethod;
	CComboBox m_comboEdgeAlignMethod;
	//CNumEdit		m_editDarkThreshold;
	//CNumEdit		m_editBrightThreshold;
	CNumEdit		m_editAOIDefectSizeMin;
	CNumEdit		m_editAOIReviewBacklight;
	CComboBox m_comboPPAFocusType; //PPA 검사시 Focusing 옵션 선택 (Image, Laser)
	CComboBox m_comboPPATrackingType; //Image 검사 사용 여부 (None, Motion, Image)
	CButton m_CheckInspectionStageVacuumOn; //검사시 Inspection Stage Vacuum On/Off 설정
	CButton m_CheckAppendixSensorUse; //흡착 확인 센서 사용 여부

	CComboBox m_comboAlignDataUseMode;
	CComboBox m_comboMeasureCameraMode;
	CComboBox m_comboStickTensionUseMode;
	CComboBox m_comboMaterialParaUseMode;
	CComboBox m_comboBoxStickExistType;

	CButton m_checkOnlyUnloadingModePreAlignUse;

	CButton m_checkLoaderFinger_Stick1;
	CButton m_checkLoaderFinger_Stick2;
	CButton m_checkLoaderFinger_Stick3;
	CButton m_checkLoaderFinger_Stick4;
	CButton m_checkLoaderFinger_Stick5;
	CButton m_checkLoaderFinger_Paper1;
	CButton m_checkLoaderFinger_Paper2;
	CButton m_checkLoaderFinger_Paper3;
	CButton m_checkLoaderFinger_Paper4;
	CButton m_checkLoaderFinger_Paper5;

	CButton m_checkUnloaderFinger_Stick1;
	CButton m_checkUnloaderFinger_Stick2;
	CButton m_checkUnloaderFinger_Stick3;
	CButton m_checkUnloaderFinger_Stick4;
	CButton m_checkUnloaderFinger_Stick5;

	CButton m_checkPaperUnloaderFinger_1;
	CButton m_checkPaperUnloaderFinger_2;
	CButton m_checkPaperUnloaderFinger_3_4;
	CButton m_checkPaperUnloaderFinger_5;
	CButton m_checkPaperUnloaderFinger_6;

	CButton m_checkMappingDataUse;
	CButton m_checkAlignDataUse;
	CButton m_checkSwAlignVerifyUse;
	CButton m_checkMeasureCornerR;

	CComboBox m_comboAOIScanSpeedLevel; //KJT 20210315
	//KJT 20210524
	CComboBox m_comboDivX;
	CComboBox m_comboDivY;
	CComboBox m_comboSlotQuantityXY;

	afx_msg void OnCbnSelchangeComboInspectionParaDivCountXy();
};
