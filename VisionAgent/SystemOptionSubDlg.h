#pragma once


// CSystemOptionSubDlg 대화 상자입니다.

class CSystemOptionSubDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSystemOptionSubDlg)

public:
	CSystemOptionSubDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CSystemOptionSubDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SYSTEM_OPTION_PAGE_1_DIALOG };
#endif
	BOOL InitCtrl();
	BOOL InitPara();
	BOOL CheckChangeData();
	BOOL SavePara();

	bool m_bDialog_Entry;

	CEdit m_Edit_ImageDelPeriod;

	CButton m_Chk_ImageAutoDel;

	CComboBox m_Combo_SelPolNum;

#pragma region //AutoFocus Para
	CComboBox	m_comboAutoFocusMode;

	CComboBox	m_comboSmart_InMotionCheckMode;
	CNumEdit	m_editSmart_DelayTime;
	CNumEdit	m_editSmart_MaxTurnCount;
	CNumEdit	m_editSmart_RefTurnCount;
	CNumEdit	m_editSmart_LimitFocusValue;
	CNumEdit	m_editSmart_MinFocusValue;
	CNumEdit	m_editSmart_FocusTolerance;
	CComboBox	m_comboSmart_ScanMode;
	CNumEdit	m_editSmart_MinStepValue;
	CNumEdit	m_editSmart_MaxStepValue;
	CNumEdit	m_editSmart_DownDistRange;
	CNumEdit	m_editSmart_UpDistRange;
	CNumEdit	m_editSmart_Vel; //KJT 20210803
	CNumEdit	m_editSmart_Accel;
	CNumEdit	m_editSmart_Decel;
#pragma endregion

	CButton		m_checkAOIAlgorithmSkip;
	CButton		m_checkAOIMappingGlassMode;
	CNumEdit	m_editAOI_Z_MappingGlassPos;
	CButton		m_checkGlassMode;
	CButton		m_checkAOIAgingMode;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnCbnSelchangeComboSystemOptionSmartAutoFocusScanMode();

	CNumEdit m_editZoomZDist;
};
