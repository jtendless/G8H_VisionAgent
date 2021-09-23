#pragma once

// CModelSubMaterialPara3Dlg 대화 상자

class CModelSubMaterialPara3Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CModelSubMaterialPara3Dlg)

public:
	CModelSubMaterialPara3Dlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CModelSubMaterialPara3Dlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODEL_SUB_MATERIAL_PARA3_DIALOG };
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

	CNumEdit		m_editCornerLT_X[4];
	CNumEdit		m_editCornerLT_Y[4];
	CNumEdit		m_editCornerRB_X[4];
	CNumEdit		m_editCornerRB_Y[4];
	CNumEdit		m_editCornerAngle[4];
};
