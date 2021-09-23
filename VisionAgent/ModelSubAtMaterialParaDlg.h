#pragma once


// CModelSubAtMaterialParaDlg 대화 상자

class CModelSubAtMaterialParaDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CModelSubAtMaterialParaDlg)

public:
	CModelSubAtMaterialParaDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CModelSubAtMaterialParaDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODEL_SUB_AT_MATERIAL_PARA_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnDestroy();

	afx_msg void OnCbnSelchangeComboMaterialParaCellSelectNoX();
	afx_msg void OnCbnSelchangeComboMaterialParaCellSelectNoY();

	BOOL InitCtrl();
	BOOL InitPara();
	BOOL SavePara();
	BOOL CheckChangeData();

	void BtnEnable(BOOL bEnable);

	////Control
	//Stick Info
	CNumEdit		m_editStickSizeX;
	CNumEdit		m_editStickSizeY;
	CNumEdit		m_editStickLeftTopX;
	CNumEdit		m_editStickLeftTopY;
	CNumEdit		m_editAlignLeftHoleX;
	CNumEdit		m_editAlignLeftHoleY;
	CNumEdit		m_editAlignRightHoleX;
	CNumEdit		m_editAlignRightHoleY;
	CComboBox m_comboHoleShape;
	CComboBox m_comboHoleArrange;
	CNumEdit		m_editAlignHoleSizeX;
	CNumEdit		m_editAlignHoleSizeY;
	CNumEdit		m_editStickThickness;
	CNumEdit		m_editPaperThickness;
	//Cell Info
	CNumEdit		m_editCellCountX;
	CNumEdit		m_editCellCountY;
	CNumEdit		m_editFirstCellLeftTopX;
	CNumEdit		m_editFirstCellLeftTopY;
	CNumEdit		m_editCellPitchX;
	CNumEdit		m_editCellPitchY;
	CComboBox m_comboCellSelectX;
	CComboBox m_comboCellSelectY;
	//Sub Cell Info
	CNumEdit		m_editCellLeftTopX;
	CNumEdit		m_editCellLeftTopY;
	CNumEdit		m_editCellSizeX;
	CNumEdit		m_editCellSizeY;
	CComboBox m_comboInspectionSlotCount;
	//Slot Info
	CNumEdit		m_editSlotCenterShiftX;
	CNumEdit		m_editSlotCenterShiftY;
	CNumEdit		m_editSlotWidth;
	CNumEdit		m_editSlotHeight;
	CNumEdit		m_editSlotAngle;
	CNumEdit		m_editSlotPitchX;
	CNumEdit		m_editSlotPitchY;
	CNumEdit		m_editSlotTotalPitchX;
	CNumEdit		m_editSlotTotalPitchY;
	//Cell Info Copy
	CComboBox m_comboCellInfoCopySourceX;
	CComboBox m_comboCellInfoCopySourceY;
	CComboBox m_comboCellInfoCopyTargetX;
	CComboBox m_comboCellInfoCopyTargetY;
	CClrButton	m_btnCellInfoCopy;
	CClrButton	m_btnCellInfoCopyAll;

	//Tegkey Info
	CNumEdit		m_editTegkey_LT_X;
	CNumEdit		m_editTegkey_LT_Y;
	CNumEdit		m_editTegkey_LB_X;
	CNumEdit		m_editTegkey_LB_Y;
	CNumEdit		m_editTegkey_RT_X;
	CNumEdit		m_editTegkey_RT_Y;
	CNumEdit		m_editTegkey_RB_X;
	CNumEdit		m_editTegkey_RB_Y;
	CNumEdit		m_editTegkey_SizeX;
	CNumEdit		m_editTegkey_SizeY;

	//int m_nSelectCellX, m_nSelectCellY;
	//int m_nCopySelectSrcX, m_nCopySelectSrcY, m_nCopySelectTargetX, m_nCopySelectTargetY;

	CNumEdit		m_editStickWingCenterYOffset[eGRIPPER_ROW_MAX];

	CNumEdit		m_editTensionRatioX;
	CNumEdit		m_editTensionRatioY; //KJT 20210415

	void SelectedCellChange();
	afx_msg void OnBnClickedBtnAtMaterialCellInfoCopy();
	afx_msg void OnBnClickedBtnAtMaterialCellInfoCopyAll();
};
