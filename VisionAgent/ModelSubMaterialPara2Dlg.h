#pragma once

#include "../Module/ListCtrl/HalfEdgeListCtrl.h"
#include "../Module/ListCtrl/3DListCtrl.h"

// CModelSubMaterialPara2Dlg 대화 상자

class CModelSubMaterialPara2Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CModelSubMaterialPara2Dlg)

public:
	CModelSubMaterialPara2Dlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CModelSubMaterialPara2Dlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODEL_SUB_MATERIAL_PARA2_DIALOG };
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

	CHalfEdgeListCtrl *m_pHalfEdgeListCtrl;
	C3DListCtrl *m_p3DListCtrl;

	afx_msg void OnBnClickedBtMaterialParaHalfEdgeInsert();
	afx_msg void OnBnClickedBtMaterialParaHalfEdgeDelete();
	afx_msg void OnBnClickedBtMaterialParaHalfEdgeDeleteAll();
	afx_msg void OnBnClickedBtMaterialParaHalfEdgeLoad();

	afx_msg void OnBnClickedBtMaterialPara3DInsert();
	afx_msg void OnBnClickedBtMaterialPara3DDelete();
	afx_msg void OnBnClickedBtMaterialPara3DDeleteAll();
	afx_msg void OnBnClickedBtMaterialPara3DLoad();
};
