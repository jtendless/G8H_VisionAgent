#pragma once


// CGlassParaDlg 대화 상자

class CGlassParaDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGlassParaDlg)

public:
	CGlassParaDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CGlassParaDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODEL_SUB_GLASS_DIALOG };
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

	CNumEdit    m_EditGlassSizeX, m_EditGlassSizeY;
	CNumEdit    m_EditGlassHeightZ;

	CNumEdit    m_EditMarkSizeX, m_EditMarkSizeY;
	
	CButton		m_CheckApplyCalib;
	CButton		m_BtnRadioPoint[2];

	CNumEdit	m_EditMark_LT_X, m_EditMark_LT_Y; //1
	CNumEdit	m_EditMark_RT_X, m_EditMark_RT_Y; //2
	CNumEdit	m_EditMark_LB_X, m_EditMark_LB_Y; //3
	CNumEdit    m_EditMark_RB_X, m_EditMark_RB_Y; //4

	CNumEdit    m_EditTargetCount;
	CNumEdit	m_EditTargetX, m_EditTargetY, m_EditTargetT;
	CNumEdit	m_EditPreAlignTargetX, m_EditPreAlignTargetY, m_EditPreAlignTargetT;

	CNumEdit	m_EditPreAlign_Coaxial;
	CNumEdit	m_EditPreAlign_Ring;
	CNumEdit	m_EditPreAlign_Threshold;

	CNumEdit	m_EditReview10x_Coaxial;
	CNumEdit	m_EditReview10x_Ring;
	CNumEdit	m_EditReview10x_Backlight;
	CNumEdit	m_EditReview10x_Threshold;

	CNumEdit	m_EditReview20x_Coaxial;
	CNumEdit	m_EditReview20x_Ring;
	CNumEdit	m_EditReview20x_Backlight;
	CNumEdit	m_EditReview20x_Threshold;

	CComboBox	m_ComboPreAlign_MarkType;
	CComboBox	m_ComboPreAlign_FindType;
	
	CComboBox	m_ComboReview10X_LightType;
	CComboBox	m_ComboReview10X_MarkType;
	CComboBox	m_ComboReview10X_FindType;
	CComboBox	m_ComboReview10X_FocusType;

	CComboBox	m_ComboReview20X_LightType;
	CComboBox	m_ComboReview20X_MarkType;
	CComboBox	m_ComboReview20X_FindType;
	CComboBox	m_ComboReview20X_FocusType;	
};
