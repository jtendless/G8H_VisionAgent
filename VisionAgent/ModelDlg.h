// CModelDlg 대화 상자입니다.


class CVisionAgentModelModelChangeDlg;
class CModelSubMaterialParaDlg;
class CModelSubMaterialPara2Dlg; //KJT 20210411 Add
class CModelSubMaterialPara3Dlg; //KJT 20210824 Add
class CModelSubAtMaterialParaDlg;
class CModelSubAtMaterialPara2Dlg; //KJT 20210411 Add
class CModelSubAtMaterialPara3Dlg; //KJT 20210824 Add
class CModelSubMaterialParaAlignStickDlg;
class CModelSubAtMaterialParaAlignStickDlg;
class CInspectionParaDlg;
class CStretchParaDlg;
class CGlassParaDlg;
class CAlignParaDlg;
class CAlignPara2Dlg;
class CModelSubManualParaDlg;
class CModelSubPpaParaDlg;

typedef enum en_MODEL_DLG_DEF_BTN
{
	eMODEL_MENU_MODEL_CHANGE = 0,
	eMODEL_MENU_MATERIAL_PARA,
	eMODEL_MENU_AT_MATERIAL_PARA,
	eMODEL_MENU_INSPECTION_PARA,
	eMODEL_MENU_STRETCH_PARA,
	eMODEL_MENU_GLASS_PARA,
	eMODEL_MENU_ALIGN_PARA,
	eMODEL_MENU_MANUAL_PARA,
	eMODEL_MENU_PPA_PARA,

	eMODEL_MENU_MAX
}enum_MODEL_DLG_DEF_BTN;
typedef enum en_MODEL_SUB_DLG_DEF_BTN
{
	MODEL_SUB_PAGE1_DLG,
	MODEL_SUB_PAGE2_DLG,
	MODEL_SUB_PAGE3_DLG,

	MAX_MODEL_SUB_DLG
}enum_MODEL_SUB_DLG_DEF_BTN;

class CModelDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CModelDlg)

public:
	CModelDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CModelDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VISION_AGENT_MODEL_DIALOG };
#endif
protected:
	int m_nCurrentNo = 0;
	int m_nCurrentSubNo = 0;
private:
	void InitCtrl();
	void ShowDlg(int nDlgNo, int nSubDlgNo);
	void Dlg_HideWindow();

	CButton m_btnModel[eMODEL_MENU_MAX];
	CButton m_btnSubModel[MAX_MODEL_SUB_DLG];

	CClrButton Test;

	CColorStatic m_stcModel_Dlg_Lamp[eMODEL_MENU_MAX];
	CColorStatic m_stcModel_Sub_Dlg_Lamp[MAX_MODEL_SUB_DLG];

public:
	CVisionAgentModelModelChangeDlg *m_pModelChangeSubDlg;
	CModelSubMaterialParaDlg		*m_pMaterialParaDlg;
	CModelSubMaterialPara2Dlg		*m_pMaterialPara2Dlg; //KJT 20210411 Add
	CModelSubMaterialPara3Dlg		*m_pMaterialPara3Dlg; //KJT 20210824 Add
	CModelSubAtMaterialParaDlg				*m_pAtMaterialParaDlg;
	CModelSubAtMaterialPara2Dlg				*m_pAtMaterialPara2Dlg; //KJT 20210411 Add
	CModelSubAtMaterialPara3Dlg				*m_pAtMaterialPara3Dlg; //KJT 20210824 Add
	CModelSubMaterialParaAlignStickDlg		*m_pMaterialParaAlignStickDlg;
	CModelSubAtMaterialParaAlignStickDlg		*m_pAtMaterialParaAlignStickDlg;
	CInspectionParaDlg				*m_pInspectionParaDlg;
	CStretchParaDlg					*m_pStretchParaDlg;
	CGlassParaDlg					*m_pGlassParaDlg;
	CAlignParaDlg					*m_pAlignParaDlg;
	CAlignPara2Dlg					*m_pAlignPara2Dlg;
	CModelSubManualParaDlg			*m_pModelSubManualParaDlg;
	CModelSubPpaParaDlg				*m_pPpaParaDlg;

	BOOL RecalcLayout();
	BOOL ShowData();

	CString	m_strMdlName;
	BOOL	Is_Comp_Safe_Hwnd();
	void ChangeUI();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual BOOL DestroyWindow();
	afx_msg void OnBnClickedButtonModelChange();
	afx_msg void OnBnClickedButtonMaterialPara();
	afx_msg void OnBnClickedButtonAtMaterialPara();
	afx_msg void OnBnClickedButtonInspectionPara();
	afx_msg void OnBnClickedButtonStretchPara();
	afx_msg void OnBnClickedBtnModelMenuGlassPara();
	afx_msg void OnBnClickedButtonSubPage1();
	afx_msg void OnBnClickedButtonSubPage2();
	afx_msg void OnBnClickedButtonSubPage3();

	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedBtnModelSave();
	afx_msg void OnBnClickedBtnModelMenuAlignPara();
	afx_msg void OnBnClickedBtnModelMenuManualPara();
	afx_msg void OnBnClickedBtnModelMenuPpaPara();
};