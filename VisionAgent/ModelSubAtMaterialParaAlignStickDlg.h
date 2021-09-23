#pragma once

#include "../Module/Control/ColorStatic.h"
#include "../Module/Control/ClrButton.h"
#include "../Module/Control/NumEdit.h"
#include "ListCtrl/CommonListCtrl.h"

// CModelSubAtMaterialParaAlignStickDlg 대화 상자

class CModelSubAtMaterialParaAlignStickDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CModelSubAtMaterialParaAlignStickDlg)

public:
	CModelSubAtMaterialParaAlignStickDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CModelSubAtMaterialParaAlignStickDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODEL_SUB_AT_MATERIAL_PARA_ALIGN_STICK_DIALOG  };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnDestroy();

	bool m_bDialog_Entry;

	void InitCtrl();
	void InitPara();
	BOOL SavePara();
	BOOL CheckChangeData();

	CEdit		m_EditUpID;
	CNumEdit	m_EditUpOrder;
	CNumEdit	m_EditUpSizeX, m_EditUpSizeY;
	CNumEdit	m_EditUpPosY;

	CEdit		m_EditDownID;
	CNumEdit	m_EditDownOrder;
	CNumEdit	m_EditDownSizeX, m_EditDownSizeY;
	CNumEdit	m_EditDownPosY;

	CNumEdit	m_EditUpAlignMarkSizeX, m_EditUpAlignMarkSizeY;
	CNumEdit	m_EditUpAlignMarkLTX, m_EditUpAlignMarkLTY;
	CNumEdit	m_EditUpAlignMarkRTX, m_EditUpAlignMarkRTY;

	CNumEdit	m_EditDownAlignMarkSizeX, m_EditDownAlignMarkSizeY;
	CNumEdit	m_EditDownAlignMarkLTX, m_EditDownAlignMarkLTY;
	CNumEdit	m_EditDownAlignMarkRTX, m_EditDownAlignMarkRTY;

	CNumEdit	m_EditUpDepoMarkSizeX, m_EditUpDepoMarkSizeY;
	CNumEdit	m_EditUpDepoMarkLTX, m_EditUpDepoMarkLTY;
	CNumEdit	m_EditUpDepoMarkRTX, m_EditUpDepoMarkRTY;

	CNumEdit	m_EditDownDepoMarkSizeX, m_EditDownDepoMarkSizeY;
	CNumEdit	m_EditDownDepoMarkLTX, m_EditDownDepoMarkLTY;
	CNumEdit	m_EditDownDepoMarkRTX, m_EditDownDepoMarkRTY;

	CNumEdit	m_EditUpTegMarkSizeX, m_EditUpTegMarkSizeY;
	CNumEdit	m_EditUpTegMarkLTX, m_EditUpTegMarkLTY;
	CNumEdit	m_EditUpTegMarkRTX, m_EditUpTegMarkRTY;

	CNumEdit	m_EditDownTegMarkSizeX, m_EditDownTegMarkSizeY;
	CNumEdit	m_EditDownTegMarkLTX, m_EditDownTegMarkLTY;
	CNumEdit	m_EditDownTegMarkRTX, m_EditDownTegMarkRTY;

	CNumEdit	m_EditUpGripperPitchPos[8];
	CNumEdit	m_EditDownGripperPitchPos[8];

	CNumEdit	m_EditUpSkirtPitchY;
	CNumEdit	m_EditDownSkirtPitchY;

	CNumEdit	m_EditUpBcrPosX, m_EditUpBcrPosY;
	CNumEdit	m_EditDnBcrPosX, m_EditDnBcrPosY;
};
