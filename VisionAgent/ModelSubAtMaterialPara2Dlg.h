#pragma once

#include "../Module/ListCtrl/HalfEdgeListCtrl.h"
#include "../Module/ListCtrl/3DListCtrl.h"

// CModelSubAtMaterialPara2Dlg 대화 상자

class CModelSubAtMaterialPara2Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CModelSubAtMaterialPara2Dlg)

public:
	CModelSubAtMaterialPara2Dlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CModelSubAtMaterialPara2Dlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODEL_SUB_AT_MATERIAL_PARA2_DIALOG };
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

	CNumEdit		m_editTPX[12];
	CNumEdit		m_editTPY[12];

	CNumEdit		m_editTPSizeX;
	CNumEdit		m_editTPSizeY;
	CNumEdit		m_editTPRepeatCount;
	
	CNumEdit		m_edit3DHoleX[12];
	CNumEdit		m_edit3DHoleY[12];

	CNumEdit		m_edit3DHoleSizeX;
	CNumEdit		m_edit3DHoleSizeY;
	CNumEdit		m_edit3DHoleRepeatCount;

	CHalfEdgeListCtrl *m_pATHalfEdgeListCtrl;
	C3DListCtrl *m_pAT3DListCtrl;

	afx_msg void OnBnClickedBtAtMaterialParaHalfEdgeInsert();
	afx_msg void OnBnClickedBtAtMaterialParaHalfEdgeDelete();
	afx_msg void OnBnClickedBtAtMaterialParaHalfEdgeDeleteAll();
	afx_msg void OnBnClickedBtAtMaterialParaHalfEdgeLoad();
	afx_msg void OnBnClickedBtAtMaterialPara3DInsert();
	afx_msg void OnBnClickedBtAtMaterialPara3DDelete();
	afx_msg void OnBnClickedBtAtMaterialPara3DDeleteAll();
	afx_msg void OnBnClickedBtAtMaterialPara3DLoad();
};
