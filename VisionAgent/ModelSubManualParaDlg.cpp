// ModelSubManualParaDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "ModelSubManualParaDlg.h"
#include "afxdialogex.h"


// CModelSubManualParaDlg 대화 상자

IMPLEMENT_DYNAMIC(CModelSubManualParaDlg, CDialogEx)

CModelSubManualParaDlg::CModelSubManualParaDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MODEL_SUB_MANUAL_PARA_DIALOG, pParent)
{
	Create(IDD_MODEL_SUB_MANUAL_PARA_DIALOG, pParent);
}

CModelSubManualParaDlg::~CModelSubManualParaDlg()
{
}

void CModelSubManualParaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CModelSubManualParaDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CModelSubManualParaDlg 메시지 처리기

BOOL CModelSubManualParaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitCtrl();

	return TRUE;
}

void CModelSubManualParaDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
}

BOOL CModelSubManualParaDlg::InitCtrl()
{
	int i = 0;
	CString Str = _T("");

	m_editLoaderXAlignPos.SubclassDlgItem(IDC_EDIT_MODEL_SUB_MANUAL_PARA_LOADER_X_ALIGN_POS, this);
	m_editLoaderXPickupPos.SubclassDlgItem(IDC_EDIT_MODEL_SUB_MANUAL_PARA_LOADER_X_PICKUP_POS, this);
	m_editUnloaderXPickupPos.SubclassDlgItem(IDC_EDIT_MODEL_SUB_MANUAL_PARA_UNLOADER_X_PICKUP_POS, this);
	m_editPaperUnloaderXPickupPos.SubclassDlgItem(IDC_EDIT_MODEL_SUB_MANUAL_PARA_PAPER_UNLOADER_X_PICKUP_POS, this);

	return TRUE;
}

BOOL CModelSubManualParaDlg::InitPara()
{
	CString Str = _T("");
	int i = 0;

	Str.Format(_T("%.5f"), CModelData::m_ModelSubManualPara.Info.dStickLoaderX_AlignPos);
	m_editLoaderXAlignPos.SetWindowText(Str);
	Str.Format(_T("%.5f"), CModelData::m_ModelSubManualPara.Info.dStickLoaderX_PickUpPos);
	m_editLoaderXPickupPos.SetWindowText(Str);
	Str.Format(_T("%.5f"), CModelData::m_ModelSubManualPara.Info.dStickUnloaderX_PickUpPos);
	m_editUnloaderXPickupPos.SetWindowText(Str);
	Str.Format(_T("%.5f"), CModelData::m_ModelSubManualPara.Info.dPaperUnloaderX_PickUpPos);
	m_editPaperUnloaderXPickupPos.SetWindowText(Str);

	return TRUE;
}

BOOL CModelSubManualParaDlg::CheckChangeData()
{
	CString Str = _T("");

	m_editLoaderXAlignPos.GetWindowText(Str);
	CModelData::m_ModelSubManualPara.Info.dStickLoaderX_AlignPos = _ttof(Str);
	m_editLoaderXPickupPos.GetWindowText(Str);
	CModelData::m_ModelSubManualPara.Info.dStickLoaderX_PickUpPos = _ttof(Str);
	m_editUnloaderXPickupPos.GetWindowText(Str);
	CModelData::m_ModelSubManualPara.Info.dStickUnloaderX_PickUpPos = _ttof(Str);
	m_editPaperUnloaderXPickupPos.GetWindowText(Str);
	CModelData::m_ModelSubManualPara.Info.dPaperUnloaderX_PickUpPos = _ttof(Str);

	return TRUE;
}

BOOL CModelSubManualParaDlg::SavePara()
{
	CheckChangeData();

	BOOL bRtn = CModelData::m_ModelSubManualPara.Save();
	if (bRtn == TRUE)
		AfxMessageBox(_T("Save Ok"));
	else
		AfxMessageBox(_T("Save Fail !!"));

	return TRUE;
}

void CModelSubManualParaDlg::OnShowWindow(BOOL bShow, UINT nStatus)
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