// ModelSubAtMaterialPara3Dlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "ModelSubAtMaterialPara3Dlg.h"
#include "afxdialogex.h"


// CModelSubAtMaterialPara3Dlg 대화 상자

IMPLEMENT_DYNAMIC(CModelSubAtMaterialPara3Dlg, CDialogEx)

CModelSubAtMaterialPara3Dlg::CModelSubAtMaterialPara3Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MODEL_SUB_AT_MATERIAL_PARA3_DIALOG, pParent)
{
	Create(IDD_MODEL_SUB_AT_MATERIAL_PARA3_DIALOG, pParent);		
}

CModelSubAtMaterialPara3Dlg::~CModelSubAtMaterialPara3Dlg()
{
}

void CModelSubAtMaterialPara3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CModelSubAtMaterialPara3Dlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CModelSubAtMaterialPara3Dlg 메시지 처리기

BOOL CModelSubAtMaterialPara3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitCtrl();

	return TRUE;
}

void CModelSubAtMaterialPara3Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();
}

BOOL CModelSubAtMaterialPara3Dlg::InitCtrl()
{
	int i = 0;

	m_editCornerLT_X[0].SubclassDlgItem(IDC_EDIT_MODEL_SUB_AT_MATERIAL_PARA_CORNER_PARA_LT_X1, this);
	m_editCornerLT_Y[0].SubclassDlgItem(IDC_EDIT_MODEL_SUB_AT_MATERIAL_PARA_CORNER_PARA_LT_Y1, this);
	m_editCornerLT_X[1].SubclassDlgItem(IDC_EDIT_MODEL_SUB_AT_MATERIAL_PARA_CORNER_PARA_LT_X2, this);
	m_editCornerLT_Y[1].SubclassDlgItem(IDC_EDIT_MODEL_SUB_AT_MATERIAL_PARA_CORNER_PARA_LT_Y2, this);
	m_editCornerLT_X[2].SubclassDlgItem(IDC_EDIT_MODEL_SUB_AT_MATERIAL_PARA_CORNER_PARA_LT_X3, this);
	m_editCornerLT_Y[2].SubclassDlgItem(IDC_EDIT_MODEL_SUB_AT_MATERIAL_PARA_CORNER_PARA_LT_Y3, this);
	m_editCornerLT_X[3].SubclassDlgItem(IDC_EDIT_MODEL_SUB_AT_MATERIAL_PARA_CORNER_PARA_LT_X4, this);
	m_editCornerLT_Y[3].SubclassDlgItem(IDC_EDIT_MODEL_SUB_AT_MATERIAL_PARA_CORNER_PARA_LT_Y4, this);

	m_editCornerRB_X[0].SubclassDlgItem(IDC_EDIT_MODEL_SUB_AT_MATERIAL_PARA_CORNER_PARA_RB_X1, this);
	m_editCornerRB_Y[0].SubclassDlgItem(IDC_EDIT_MODEL_SUB_AT_MATERIAL_PARA_CORNER_PARA_RB_Y1, this);
	m_editCornerRB_X[1].SubclassDlgItem(IDC_EDIT_MODEL_SUB_AT_MATERIAL_PARA_CORNER_PARA_RB_X2, this);
	m_editCornerRB_Y[1].SubclassDlgItem(IDC_EDIT_MODEL_SUB_AT_MATERIAL_PARA_CORNER_PARA_RB_Y2, this);
	m_editCornerRB_X[2].SubclassDlgItem(IDC_EDIT_MODEL_SUB_AT_MATERIAL_PARA_CORNER_PARA_RB_X3, this);
	m_editCornerRB_Y[2].SubclassDlgItem(IDC_EDIT_MODEL_SUB_AT_MATERIAL_PARA_CORNER_PARA_RB_Y3, this);
	m_editCornerRB_X[3].SubclassDlgItem(IDC_EDIT_MODEL_SUB_AT_MATERIAL_PARA_CORNER_PARA_RB_X4, this);
	m_editCornerRB_Y[3].SubclassDlgItem(IDC_EDIT_MODEL_SUB_AT_MATERIAL_PARA_CORNER_PARA_RB_Y4, this);

	m_editCornerAngle[0].SubclassDlgItem(IDC_EDIT_MODEL_SUB_AT_MATERIAL_PARA_CORNER_PARA_ANGLE_1, this);
	m_editCornerAngle[1].SubclassDlgItem(IDC_EDIT_MODEL_SUB_AT_MATERIAL_PARA_CORNER_PARA_ANGLE_2, this);
	m_editCornerAngle[2].SubclassDlgItem(IDC_EDIT_MODEL_SUB_AT_MATERIAL_PARA_CORNER_PARA_ANGLE_3, this);
	m_editCornerAngle[3].SubclassDlgItem(IDC_EDIT_MODEL_SUB_AT_MATERIAL_PARA_CORNER_PARA_ANGLE_4, this);

	return TRUE;
}

BOOL CModelSubAtMaterialPara3Dlg::InitPara()
{
	CString Str = _T("");

	for (int i = 0; i < 4; i++)
	{
		Str.Format(_T("%.5f"), CModelData::m_AtMaterialPara.Info.dReview10XCornerLT_X[i]);
		m_editCornerLT_X[i].SetWindowText(Str);
		Str.Format(_T("%.5f"), CModelData::m_AtMaterialPara.Info.dReview10XCornerLT_Y[i]);
		m_editCornerLT_Y[i].SetWindowText(Str);

		Str.Format(_T("%.5f"), CModelData::m_AtMaterialPara.Info.dReview10XCornerRB_X[i]);
		m_editCornerRB_X[i].SetWindowText(Str);
		Str.Format(_T("%.5f"), CModelData::m_AtMaterialPara.Info.dReview10XCornerRB_Y[i]);
		m_editCornerRB_Y[i].SetWindowText(Str);

		Str.Format(_T("%.5f"), CModelData::m_AtMaterialPara.Info.dReview10XCornerAngle[i]);
		m_editCornerAngle[i].SetWindowText(Str);
	}

	return TRUE;
}

BOOL CModelSubAtMaterialPara3Dlg::CheckChangeData()
{
	CString Str = _T("");
	int i = 0;

	for (int i = 0; i < 4; i++)
	{
		m_editCornerLT_X[i].GetWindowText(Str);
		CModelData::m_AtMaterialPara.Info.dReview10XCornerLT_X[i] = _ttof(Str);
		m_editCornerLT_Y[i].GetWindowText(Str);
		CModelData::m_AtMaterialPara.Info.dReview10XCornerLT_Y[i] = _ttof(Str);

		m_editCornerRB_X[i].GetWindowText(Str);
		CModelData::m_AtMaterialPara.Info.dReview10XCornerRB_X[i] = _ttof(Str);
		m_editCornerRB_Y[i].GetWindowText(Str);
		CModelData::m_AtMaterialPara.Info.dReview10XCornerRB_Y[i] = _ttof(Str);

		m_editCornerAngle[i].GetWindowText(Str);
		CModelData::m_AtMaterialPara.Info.dReview10XCornerAngle[i] = _ttof(Str);
	}

	return TRUE;
}

BOOL CModelSubAtMaterialPara3Dlg::SavePara()
{
	CheckChangeData();

	BOOL bRtn = CModelData::m_AtMaterialPara.Save();
	if (bRtn == TRUE)
		AfxMessageBox(_T("AtMaterialPara Save Ok"));
	else
		AfxMessageBox(_T("AtMaterialPara Save Fail !!"));

	bRtn = CModelData::m_MaterialPara.Save(TRUE);
	if (bRtn == TRUE)
		AfxMessageBox(_T("MaterialPara Save Ok (TensionRatio)"));
	else
		AfxMessageBox(_T("MaterialPara Save Fail (TensionRatio) !!"));

	return TRUE;
}

void CModelSubAtMaterialPara3Dlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow == TRUE)
	{
		InitPara();
	}
	else if (bShow == FALSE)
	{
	}
}