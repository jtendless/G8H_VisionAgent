// ModelSubMaterialPara2Dlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "ModelSubMaterialPara2Dlg.h"
#include "afxdialogex.h"


// CModelSubMaterialPara2Dlg 대화 상자

IMPLEMENT_DYNAMIC(CModelSubMaterialPara2Dlg, CDialogEx)

CModelSubMaterialPara2Dlg::CModelSubMaterialPara2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MODEL_SUB_MATERIAL_PARA2_DIALOG, pParent)
{
	Create(IDD_MODEL_SUB_MATERIAL_PARA2_DIALOG, pParent);	
}

CModelSubMaterialPara2Dlg::~CModelSubMaterialPara2Dlg()
{
	if (m_pHalfEdgeListCtrl != NULL)
		delete[] m_pHalfEdgeListCtrl;

	if (m_p3DListCtrl != NULL)
		delete[] m_p3DListCtrl;
}

void CModelSubMaterialPara2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CModelSubMaterialPara2Dlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BT_MATERIAL_PARA_HALF_EDGE_INSERT, &CModelSubMaterialPara2Dlg::OnBnClickedBtMaterialParaHalfEdgeInsert)
	ON_BN_CLICKED(IDC_BT_MATERIAL_PARA_HALF_EDGE_DELETE, &CModelSubMaterialPara2Dlg::OnBnClickedBtMaterialParaHalfEdgeDelete)
	ON_BN_CLICKED(IDC_BT_MATERIAL_PARA_HALF_EDGE_DELETE_ALL, &CModelSubMaterialPara2Dlg::OnBnClickedBtMaterialParaHalfEdgeDeleteAll)
	ON_BN_CLICKED(IDC_BT_MATERIAL_PARA_HALF_EDGE_LOAD, &CModelSubMaterialPara2Dlg::OnBnClickedBtMaterialParaHalfEdgeLoad)
	ON_BN_CLICKED(IDC_BT_MATERIAL_PARA_3D_INSERT, &CModelSubMaterialPara2Dlg::OnBnClickedBtMaterialPara3DInsert)
	ON_BN_CLICKED(IDC_BT_MATERIAL_PARA_3D_DELETE, &CModelSubMaterialPara2Dlg::OnBnClickedBtMaterialPara3DDelete)
	ON_BN_CLICKED(IDC_BT_MATERIAL_PARA_3D_DELETE_ALL, &CModelSubMaterialPara2Dlg::OnBnClickedBtMaterialPara3DDeleteAll)
	ON_BN_CLICKED(IDC_BT_MATERIAL_PARA_3D_LOAD, &CModelSubMaterialPara2Dlg::OnBnClickedBtMaterialPara3DLoad)
END_MESSAGE_MAP()


// CModelSubMaterialPara2Dlg 메시지 처리기

BOOL CModelSubMaterialPara2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_pHalfEdgeListCtrl = NULL;
	m_p3DListCtrl = NULL;

	InitCtrl();

	return TRUE;
}

void CModelSubMaterialPara2Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();
}

BOOL CModelSubMaterialPara2Dlg::InitCtrl()
{
	int i = 0;
	CString Str = _T("");

	m_editTPX[0].SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_HALF_EDGE_HOLE1_X, this);
	m_editTPY[0].SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_HALF_EDGE_HOLE1_Y, this);
	m_editTPX[1].SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_HALF_EDGE_HOLE2_X, this);
	m_editTPY[1].SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_HALF_EDGE_HOLE2_Y, this);
	m_editTPX[2].SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_HALF_EDGE_HOLE3_X, this);
	m_editTPY[2].SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_HALF_EDGE_HOLE3_Y, this);
	m_editTPX[3].SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_HALF_EDGE_HOLE4_X, this);
	m_editTPY[3].SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_HALF_EDGE_HOLE4_Y, this);
	m_editTPX[4].SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_HALF_EDGE_HOLE5_X, this);
	m_editTPY[4].SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_HALF_EDGE_HOLE5_Y, this);
	m_editTPX[5].SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_HALF_EDGE_HOLE6_X, this);
	m_editTPY[5].SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_HALF_EDGE_HOLE6_Y, this);
	m_editTPX[6].SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_HALF_EDGE_HOLE7_X, this);
	m_editTPY[6].SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_HALF_EDGE_HOLE7_Y, this);
	m_editTPX[7].SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_HALF_EDGE_HOLE8_X, this);
	m_editTPY[7].SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_HALF_EDGE_HOLE8_Y, this);
	m_editTPX[8].SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_HALF_EDGE_HOLE9_X, this);
	m_editTPY[8].SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_HALF_EDGE_HOLE9_Y, this);
	m_editTPX[9].SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_HALF_EDGE_HOLE10_X, this);
	m_editTPY[9].SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_HALF_EDGE_HOLE10_Y, this);
	m_editTPX[10].SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_HALF_EDGE_HOLE11_X, this);
	m_editTPY[10].SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_HALF_EDGE_HOLE11_Y, this);
	m_editTPX[11].SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_HALF_EDGE_HOLE12_X, this);
	m_editTPY[11].SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_HALF_EDGE_HOLE12_Y, this);

	m_editTPSizeX.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_HALF_EDGE_HOLE_SIZE_X, this);
	m_editTPSizeY.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_HALF_EDGE_HOLE_SIZE_Y, this);
	m_editTPRepeatCount.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_HALF_EDGE_HOLE_REPEAT_COUNT, this);

	m_edit3DHoleSizeX.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_3D_HOLE_SIZE_X, this);
	m_edit3DHoleSizeY.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_3D_HOLE_SIZE_Y, this);
	m_edit3DHoleRepeatCount.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_3D_HOLE_REPEAT_COUNT, this);

	//TP
	CImageList m_ImageList;
	m_ImageList.Create(1, 22, ILC_COLOR, 1, 1);
	m_pHalfEdgeListCtrl = new CHalfEdgeListCtrl;
	m_pHalfEdgeListCtrl->SubclassDlgItem(IDC_LIST_MATERIAL_PARA_HALF_EDGE_DATA, this);
	/// Setting
	m_pHalfEdgeListCtrl->SetImageList(&m_ImageList, LVSIL_SMALL);
	m_pHalfEdgeListCtrl->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_pHalfEdgeListCtrl->AddListColumn();

	m_pHalfEdgeListCtrl->ResetMaxListCount();


	//3D	
	m_p3DListCtrl = new C3DListCtrl;
	m_p3DListCtrl->SubclassDlgItem(IDC_LIST_MATERIAL_PARA_3D_DATA, this);
	/// Setting
	m_p3DListCtrl->SetImageList(&m_ImageList, LVSIL_SMALL);
	m_p3DListCtrl->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_p3DListCtrl->AddListColumn();

	m_p3DListCtrl->ResetMaxListCount();

	return TRUE;
}

BOOL CModelSubMaterialPara2Dlg::InitPara()
{
	CString Str = _T("");
	int nRowCnt, i = 0;
	double dValue[MAX_HALF_EDGE_LIST_COL] = { 0.0 };

	//TP
	m_pHalfEdgeListCtrl->DeleteAllItems();
	m_pHalfEdgeListCtrl->ResetMaxListCount(); //KJT 20210309

	Str.Format(_T("%.5f"), CModelData::m_MaterialPara.Info.dTPSizeX);
	m_editTPSizeX.SetWindowText(Str);
	Str.Format(_T("%.5f"), CModelData::m_MaterialPara.Info.dTPSizeY);
	m_editTPSizeY.SetWindowText(Str);
	Str.Format(_T("%d"), CModelData::m_MaterialPara.Info.nTPRepeatCount);
	m_editTPRepeatCount.SetWindowText(Str);
	
	for (i = 0; i < CModelData::m_MaterialPara.Info.nTPCount; i++)
	{
		//Str.Format(_T("%.5f"), CModelData::m_MaterialPara.Info.dTPPosX[i]);
		//m_editTPX[i].SetWindowText(Str);
		//Str.Format(_T("%.5f"), CModelData::m_MaterialPara.Info.dTPPosY[i]);
		//m_editTPY[i].SetWindowText(Str);

		dValue[0] = CModelData::m_MaterialPara.Info.dTPPosX[i];
		dValue[1] = CModelData::m_MaterialPara.Info.dTPPosY[i];

		m_pHalfEdgeListCtrl->AddListData(i, dValue);
	}

	//3D
	m_p3DListCtrl->DeleteAllItems();
	m_p3DListCtrl->ResetMaxListCount(); //KJT 20210309

	Str.Format(_T("%.5f"), CModelData::m_MaterialPara.Info.d3DHoleSizeX);
	m_edit3DHoleSizeX.SetWindowText(Str);
	Str.Format(_T("%.5f"), CModelData::m_MaterialPara.Info.d3DHoleSizeY);
	m_edit3DHoleSizeY.SetWindowText(Str);
	Str.Format(_T("%d"), CModelData::m_MaterialPara.Info.n3DHoleRepeatCount);
	m_edit3DHoleRepeatCount.SetWindowText(Str);

	for (i = 0; i < CModelData::m_MaterialPara.Info.n3DHoleCount; i++)
	{
		//Str.Format(_T("%.5f"), CModelData::m_MaterialPara.Info.dTPPosX[i]);
		//m_editTPX[i].SetWindowText(Str);
		//Str.Format(_T("%.5f"), CModelData::m_MaterialPara.Info.dTPPosY[i]);
		//m_editTPY[i].SetWindowText(Str);

		dValue[0] = CModelData::m_MaterialPara.Info.d3DHolePosX[i];
		dValue[1] = CModelData::m_MaterialPara.Info.d3DHolePosY[i];

		m_p3DListCtrl->AddListData(i, dValue);
	}

	return TRUE;
}

BOOL CModelSubMaterialPara2Dlg::CheckChangeData()
{
	CString Str = _T("");
	int i = 0;
	double dValue[MAX_HALF_EDGE_LIST_COL] = { 0.0 };

	//TP
	m_editTPSizeX.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.dTPSizeX = _ttof(Str);
	m_editTPSizeY.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.dTPSizeY = _ttof(Str);
	m_editTPRepeatCount.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.nTPRepeatCount = _ttoi(Str);

	CModelData::m_MaterialPara.Info.nTPCount = m_pHalfEdgeListCtrl->GetMaxListCount();

	for (i = 0; i < CModelData::m_MaterialPara.Info.nTPCount; i++)
	{
		//m_editTPX[i].GetWindowText(Str);
		//CModelData::m_MaterialPara.Info.dTPPosX[i] = _ttof(Str);
		//m_editTPY[i].GetWindowText(Str);
		//CModelData::m_MaterialPara.Info.dTPPosY[i] = _ttof(Str);

		m_pHalfEdgeListCtrl->GetListData(i, dValue);

		CModelData::m_MaterialPara.Info.dTPPosX[i] = dValue[0];
		CModelData::m_MaterialPara.Info.dTPPosY[i] = dValue[1];
	}

	//3D
	m_edit3DHoleSizeX.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.d3DHoleSizeX = _ttof(Str);
	m_edit3DHoleSizeY.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.d3DHoleSizeY = _ttof(Str);
	m_edit3DHoleRepeatCount.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.n3DHoleRepeatCount = _ttoi(Str);

	CModelData::m_MaterialPara.Info.n3DHoleCount = m_p3DListCtrl->GetMaxListCount();

	for (i = 0; i < CModelData::m_MaterialPara.Info.n3DHoleCount; i++)
	{
		//m_editTPX[i].GetWindowText(Str);
		//CModelData::m_MaterialPara.Info.dTPPosX[i] = _ttof(Str);
		//m_editTPY[i].GetWindowText(Str);
		//CModelData::m_MaterialPara.Info.dTPPosY[i] = _ttof(Str);

		m_p3DListCtrl->GetListData(i, dValue);

		CModelData::m_MaterialPara.Info.d3DHolePosX[i] = dValue[0];
		CModelData::m_MaterialPara.Info.d3DHolePosY[i] = dValue[1];
	}
	return TRUE;
}

BOOL CModelSubMaterialPara2Dlg::SavePara()
{
	CheckChangeData();

	BOOL bRtn = CModelData::m_MaterialPara.Save();
	if (bRtn == TRUE)
		AfxMessageBox(_T("Save Ok"));
	else
		AfxMessageBox(_T("Save Fail !!"));

	return TRUE;
}

void CModelSubMaterialPara2Dlg::OnShowWindow(BOOL bShow, UINT nStatus)
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

void CModelSubMaterialPara2Dlg::OnBnClickedBtMaterialParaHalfEdgeInsert()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nRowCnt = m_pHalfEdgeListCtrl->GetMaxListCount();

	double dValue[MAX_HALF_EDGE_LIST_COL] = { 0.0 };

	m_pHalfEdgeListCtrl->AddListData(nRowCnt, dValue);
}


void CModelSubMaterialPara2Dlg::OnBnClickedBtMaterialParaHalfEdgeDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nRowCount = 0;

	nRowCount = m_pHalfEdgeListCtrl->GetMaxListCount() - 1;
	m_pHalfEdgeListCtrl->DeleteListData(nRowCount);
}


void CModelSubMaterialPara2Dlg::OnBnClickedBtMaterialParaHalfEdgeDeleteAll()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int nRowCount = 0;

	nRowCount = m_pHalfEdgeListCtrl->GetMaxListCount() - 1;
	for (int i = nRowCount; i >= 0; i--)
	{
		m_pHalfEdgeListCtrl->DeleteListData(nRowCount);
		nRowCount--;
	}
}


void CModelSubMaterialPara2Dlg::OnBnClickedBtMaterialParaHalfEdgeLoad()
{
	// TODO: Add your control notification handler code here

	CString strTemp[MAX_3D_HOLE_COUNT];
	int nTemp = 0;
	int nCnt = 0;
	int nRowCount = 0;

	nRowCount = m_pHalfEdgeListCtrl->GetMaxListCount() - 1;
	for (int i = nRowCount; i >= 0; i--)
	{
		m_pHalfEdgeListCtrl->DeleteListData(i);

	}

	m_pHalfEdgeListCtrl->LoadDataFromCsv(SharedInfo::VisionAgentPath, strTemp, &nTemp);
}


void CModelSubMaterialPara2Dlg::OnBnClickedBtMaterialPara3DInsert()
{
	int nRowCnt = m_p3DListCtrl->GetMaxListCount();

	double dValue[MAX_HALF_EDGE_LIST_COL] = { 0.0 };

	m_p3DListCtrl->AddListData(nRowCnt, dValue);
}

void CModelSubMaterialPara2Dlg::OnBnClickedBtMaterialPara3DDelete()
{
	int nRowCount = 0;

	nRowCount = m_p3DListCtrl->GetMaxListCount() - 1;
	m_p3DListCtrl->DeleteListData(nRowCount);
}

void CModelSubMaterialPara2Dlg::OnBnClickedBtMaterialPara3DDeleteAll()
{
	int nRowCount = 0;

	nRowCount = m_p3DListCtrl->GetMaxListCount() - 1;
	for (int i = nRowCount; i >= 0; i--)
	{
		m_p3DListCtrl->DeleteListData(nRowCount);
		nRowCount--;
	}
}

void CModelSubMaterialPara2Dlg::OnBnClickedBtMaterialPara3DLoad()
{
	CString strTemp[MAX_3D_HOLE_COUNT];
	int nTemp = 0;
	int nCnt = 0;
	int nRowCount = 0;

	nRowCount = m_p3DListCtrl->GetMaxListCount() - 1;
	for (int i = nRowCount; i >= 0; i--)
	{
		m_p3DListCtrl->DeleteListData(i);

	}

	m_p3DListCtrl->LoadDataFromCsv(SharedInfo::VisionAgentPath, strTemp, &nTemp);
}