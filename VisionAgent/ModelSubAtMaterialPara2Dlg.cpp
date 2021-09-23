// ModelSubAtMaterialPara2Dlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "ModelSubAtMaterialPara2Dlg.h"
#include "afxdialogex.h"


// CModelSubAtMaterialPara2Dlg 대화 상자

IMPLEMENT_DYNAMIC(CModelSubAtMaterialPara2Dlg, CDialogEx)

CModelSubAtMaterialPara2Dlg::CModelSubAtMaterialPara2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MODEL_SUB_AT_MATERIAL_PARA2_DIALOG, pParent)
{
	Create(IDD_MODEL_SUB_AT_MATERIAL_PARA2_DIALOG, pParent);		
}

CModelSubAtMaterialPara2Dlg::~CModelSubAtMaterialPara2Dlg()
{
	if (m_pATHalfEdgeListCtrl != NULL)
		delete[] m_pATHalfEdgeListCtrl;

	if (m_pAT3DListCtrl != NULL)
		delete[] m_pAT3DListCtrl;
}

void CModelSubAtMaterialPara2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CModelSubAtMaterialPara2Dlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BT_AT_MATERIAL_PARA_HALF_EDGE_INSERT, &CModelSubAtMaterialPara2Dlg::OnBnClickedBtAtMaterialParaHalfEdgeInsert)
	ON_BN_CLICKED(IDC_BT_AT_MATERIAL_PARA_HALF_EDGE_DELETE, &CModelSubAtMaterialPara2Dlg::OnBnClickedBtAtMaterialParaHalfEdgeDelete)
	ON_BN_CLICKED(IDC_BT_AT_MATERIAL_PARA_HALF_EDGE_DELETE_ALL, &CModelSubAtMaterialPara2Dlg::OnBnClickedBtAtMaterialParaHalfEdgeDeleteAll)
	ON_BN_CLICKED(IDC_BT_AT_MATERIAL_PARA_HALF_EDGE_LOAD, &CModelSubAtMaterialPara2Dlg::OnBnClickedBtAtMaterialParaHalfEdgeLoad)
	ON_BN_CLICKED(IDC_BT_AT_MATERIAL_PARA_3D_INSERT, &CModelSubAtMaterialPara2Dlg::OnBnClickedBtAtMaterialPara3DInsert)
	ON_BN_CLICKED(IDC_BT_AT_MATERIAL_PARA_3D_DELETE, &CModelSubAtMaterialPara2Dlg::OnBnClickedBtAtMaterialPara3DDelete)
	ON_BN_CLICKED(IDC_BT_AT_MATERIAL_PARA_3D_DELETE_ALL, &CModelSubAtMaterialPara2Dlg::OnBnClickedBtAtMaterialPara3DDeleteAll)
	ON_BN_CLICKED(IDC_BT_AT_MATERIAL_PARA_3D_LOAD, &CModelSubAtMaterialPara2Dlg::OnBnClickedBtAtMaterialPara3DLoad)
END_MESSAGE_MAP()


// CModelSubAtMaterialPara2Dlg 메시지 처리기

BOOL CModelSubAtMaterialPara2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_pATHalfEdgeListCtrl = NULL;
	m_pAT3DListCtrl = NULL;

	InitCtrl();

	return TRUE;
}

void CModelSubAtMaterialPara2Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();
}

BOOL CModelSubAtMaterialPara2Dlg::InitCtrl()
{
	int i = 0;
	CString Str = _T("");

	m_editTPX[0].SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_HALF_EDGE_HOLE1_X, this);
	m_editTPY[0].SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_HALF_EDGE_HOLE1_Y, this);
	m_editTPX[1].SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_HALF_EDGE_HOLE2_X, this);
	m_editTPY[1].SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_HALF_EDGE_HOLE2_Y, this);
	m_editTPX[2].SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_HALF_EDGE_HOLE3_X, this);
	m_editTPY[2].SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_HALF_EDGE_HOLE3_Y, this);
	m_editTPX[3].SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_HALF_EDGE_HOLE4_X, this);
	m_editTPY[3].SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_HALF_EDGE_HOLE4_Y, this);
	m_editTPX[4].SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_HALF_EDGE_HOLE5_X, this);
	m_editTPY[4].SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_HALF_EDGE_HOLE5_Y, this);
	m_editTPX[5].SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_HALF_EDGE_HOLE6_X, this);
	m_editTPY[5].SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_HALF_EDGE_HOLE6_Y, this);
	m_editTPX[6].SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_HALF_EDGE_HOLE7_X, this);
	m_editTPY[6].SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_HALF_EDGE_HOLE7_Y, this);
	m_editTPX[7].SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_HALF_EDGE_HOLE8_X, this);
	m_editTPY[7].SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_HALF_EDGE_HOLE8_Y, this);
	m_editTPX[8].SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_HALF_EDGE_HOLE9_X, this);
	m_editTPY[8].SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_HALF_EDGE_HOLE9_Y, this);
	m_editTPX[9].SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_HALF_EDGE_HOLE10_X, this);
	m_editTPY[9].SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_HALF_EDGE_HOLE10_Y, this);
	m_editTPX[10].SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_HALF_EDGE_HOLE11_X, this);
	m_editTPY[10].SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_HALF_EDGE_HOLE11_Y, this);
	m_editTPX[11].SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_HALF_EDGE_HOLE12_X, this);
	m_editTPY[11].SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_HALF_EDGE_HOLE12_Y, this);

	m_editTPSizeX.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_HALF_EDGE_HOLE_SIZE_X, this);
	m_editTPSizeY.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_HALF_EDGE_HOLE_SIZE_Y, this);
	m_editTPRepeatCount.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_HALF_EDGE_HOLE_REPEAT_COUNT, this);

	m_edit3DHoleSizeX.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_3D_HOLE_SIZE_X, this);
	m_edit3DHoleSizeY.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_3D_HOLE_SIZE_Y, this);
	m_edit3DHoleRepeatCount.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_3D_HOLE_REPEAT_COUNT, this);
		
	
	//TP
	CImageList m_ImageList;
	m_ImageList.Create(1, 22, ILC_COLOR, 1, 1);
	m_pATHalfEdgeListCtrl = new CHalfEdgeListCtrl;
	m_pATHalfEdgeListCtrl->SubclassDlgItem(IDC_LIST_AT_MATERIAL_PARA_HALF_EDGE_DATA, this);
	/// Setting
	m_pATHalfEdgeListCtrl->SetImageList(&m_ImageList, LVSIL_SMALL);
	m_pATHalfEdgeListCtrl->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_pATHalfEdgeListCtrl->AddListColumn();
	
	m_pATHalfEdgeListCtrl->ResetMaxListCount();

	//3D
	m_pAT3DListCtrl = new C3DListCtrl;
	m_pAT3DListCtrl->SubclassDlgItem(IDC_LIST_AT_MATERIAL_PARA_3D_DATA, this);
	/// Setting
	m_pAT3DListCtrl->SetImageList(&m_ImageList, LVSIL_SMALL);
	m_pAT3DListCtrl->SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_pAT3DListCtrl->AddListColumn();

	m_pAT3DListCtrl->ResetMaxListCount();

	return TRUE;
}

BOOL CModelSubAtMaterialPara2Dlg::InitPara()
{
	CString Str = _T("");
	int nRowCnt, i = 0;
	double dValue[MAX_HALF_EDGE_LIST_COL] = { 0.0 };

	//TP
	m_pATHalfEdgeListCtrl->DeleteAllItems();
	m_pATHalfEdgeListCtrl->ResetMaxListCount(); //KJT 20210309

	//KJT 20210416
	Str.Format(_T("%.5f"), CModelData::m_AtMaterialPara.Info.dTPSizeX);
	m_editTPSizeX.SetWindowText(Str);
	Str.Format(_T("%.5f"), CModelData::m_AtMaterialPara.Info.dTPSizeY);
	m_editTPSizeY.SetWindowText(Str);	
	Str.Format(_T("%d"), CModelData::m_AtMaterialPara.Info.nTPRepeatCount);
	m_editTPRepeatCount.SetWindowText(Str);

	for (i = 0; i < CModelData::m_AtMaterialPara.Info.nTPCount; i++)
	{
		//Str.Format(_T("%.5f"), CModelData::m_MaterialPara.Info.dTPPosX[i]);
		//m_editTPX[i].SetWindowText(Str);
		//Str.Format(_T("%.5f"), CModelData::m_MaterialPara.Info.dTPPosY[i]);
		//m_editTPY[i].SetWindowText(Str);
	
		dValue[0] = CModelData::m_AtMaterialPara.Info.dTPPosX[i];
		dValue[1] = CModelData::m_AtMaterialPara.Info.dTPPosY[i];

		m_pATHalfEdgeListCtrl->AddListData(i, dValue);
	}	


	//3D
	m_pAT3DListCtrl->DeleteAllItems();
	m_pAT3DListCtrl->ResetMaxListCount(); //KJT 20210309

	//KJT 20210416
	Str.Format(_T("%.5f"), CModelData::m_AtMaterialPara.Info.d3DHoleSizeX);
	m_edit3DHoleSizeX.SetWindowText(Str);
	Str.Format(_T("%.5f"), CModelData::m_AtMaterialPara.Info.d3DHoleSizeY);
	m_edit3DHoleSizeY.SetWindowText(Str);
	Str.Format(_T("%d"), CModelData::m_AtMaterialPara.Info.n3DHoleRepeatCount);
	m_edit3DHoleRepeatCount.SetWindowText(Str);

	for (i = 0; i < CModelData::m_AtMaterialPara.Info.n3DHoleCount; i++)
	{
		//Str.Format(_T("%.5f"), CModelData::m_MaterialPara.Info.dTPPosX[i]);
		//m_editTPX[i].SetWindowText(Str);
		//Str.Format(_T("%.5f"), CModelData::m_MaterialPara.Info.dTPPosY[i]);
		//m_editTPY[i].SetWindowText(Str);

		dValue[0] = CModelData::m_AtMaterialPara.Info.d3DHolePosX[i];
		dValue[1] = CModelData::m_AtMaterialPara.Info.d3DHolePosY[i];

		m_pAT3DListCtrl->AddListData(i, dValue);
	}
	return TRUE;
}

BOOL CModelSubAtMaterialPara2Dlg::CheckChangeData()
{
	CString Str = _T("");
	int i = 0;
	double dValue[MAX_HALF_EDGE_LIST_COL] = { 0.0 };

	//TP
	m_editTPSizeX.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.dTPSizeX = _ttof(Str);
	m_editTPSizeY.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.dTPSizeY = _ttof(Str);
	m_editTPRepeatCount.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.nTPRepeatCount = _ttoi(Str);

	CModelData::m_AtMaterialPara.Info.nTPCount = m_pATHalfEdgeListCtrl->GetMaxListCount();

	for (i = 0; i < CModelData::m_AtMaterialPara.Info.nTPCount; i++)
	{
		//m_editTPX[i].GetWindowText(Str);
		//CModelData::m_AtMaterialPara.Info.dTPPosX[i] = _ttof(Str);
		//m_editTPY[i].GetWindowText(Str);
		//CModelData::m_AtMaterialPara.Info.dTPPosY[i] = _ttof(Str);

		m_pATHalfEdgeListCtrl->GetListData(i, dValue);

		CModelData::m_AtMaterialPara.Info.dTPPosX[i] = dValue[0];
		CModelData::m_AtMaterialPara.Info.dTPPosY[i] = dValue[1];
	}


	//3D
	m_edit3DHoleSizeX.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.d3DHoleSizeX = _ttof(Str);
	m_edit3DHoleSizeY.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.d3DHoleSizeY = _ttof(Str);
	m_edit3DHoleRepeatCount.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.n3DHoleRepeatCount = _ttoi(Str);

	CModelData::m_AtMaterialPara.Info.n3DHoleCount = m_pAT3DListCtrl->GetMaxListCount();

	for (i = 0; i < CModelData::m_AtMaterialPara.Info.n3DHoleCount; i++)
	{
		//m_editTPX[i].GetWindowText(Str);
		//CModelData::m_AtMaterialPara.Info.dTPPosX[i] = _ttof(Str);
		//m_editTPY[i].GetWindowText(Str);
		//CModelData::m_AtMaterialPara.Info.dTPPosY[i] = _ttof(Str);

		m_pAT3DListCtrl->GetListData(i, dValue);

		CModelData::m_AtMaterialPara.Info.d3DHolePosX[i] = dValue[0];
		CModelData::m_AtMaterialPara.Info.d3DHolePosY[i] = dValue[1];
	}

	return TRUE;
}

BOOL CModelSubAtMaterialPara2Dlg::SavePara()
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

void CModelSubAtMaterialPara2Dlg::OnShowWindow(BOOL bShow, UINT nStatus)
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

void CModelSubAtMaterialPara2Dlg::OnBnClickedBtAtMaterialParaHalfEdgeInsert()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int nRowCnt = m_pATHalfEdgeListCtrl->GetMaxListCount();
	
	double dValue[MAX_HALF_EDGE_LIST_COL] = { 0.0 };

	m_pATHalfEdgeListCtrl->AddListData(nRowCnt, dValue);
}


void CModelSubAtMaterialPara2Dlg::OnBnClickedBtAtMaterialParaHalfEdgeDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int nRowCount = 0;

	nRowCount = m_pATHalfEdgeListCtrl->GetMaxListCount() - 1;
	m_pATHalfEdgeListCtrl->DeleteListData(nRowCount);
}


void CModelSubAtMaterialPara2Dlg::OnBnClickedBtAtMaterialParaHalfEdgeDeleteAll()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int nRowCount = 0;

	nRowCount = m_pATHalfEdgeListCtrl->GetMaxListCount() - 1;
	for (int i = nRowCount; i >= 0; i--)
	{
		m_pATHalfEdgeListCtrl->DeleteListData(nRowCount);
		nRowCount--;
	}	
}


void CModelSubAtMaterialPara2Dlg::OnBnClickedBtAtMaterialParaHalfEdgeLoad()
{
	// TODO: Add your control notification handler code here

	CString strTemp[MAX_TP_COUNT];
	int nTemp = 0;
	int nCnt = 0;
	int nRowCount = 0;

	nRowCount = m_pATHalfEdgeListCtrl->GetMaxListCount() - 1;
	for (int i = nRowCount; i >= 0; i--)
	{
		m_pATHalfEdgeListCtrl->DeleteListData(i);

	}
	
	m_pATHalfEdgeListCtrl->LoadDataFromCsv(SharedInfo::VisionAgentPath, strTemp, &nTemp);
}


void CModelSubAtMaterialPara2Dlg::OnBnClickedBtAtMaterialPara3DInsert()
{
	int nRowCnt = m_pAT3DListCtrl->GetMaxListCount();

	double dValue[MAX_HALF_EDGE_LIST_COL] = { 0.0 };

	m_pAT3DListCtrl->AddListData(nRowCnt, dValue);
}

void CModelSubAtMaterialPara2Dlg::OnBnClickedBtAtMaterialPara3DDelete()
{
	int nRowCount = 0;

	nRowCount = m_pAT3DListCtrl->GetMaxListCount() - 1;
	m_pAT3DListCtrl->DeleteListData(nRowCount);
}

void CModelSubAtMaterialPara2Dlg::OnBnClickedBtAtMaterialPara3DDeleteAll()
{
	int nRowCount = 0;

	nRowCount = m_pAT3DListCtrl->GetMaxListCount() - 1;
	for (int i = nRowCount; i >= 0; i--)
	{
		m_pAT3DListCtrl->DeleteListData(nRowCount);
		nRowCount--;
	}
}

void CModelSubAtMaterialPara2Dlg::OnBnClickedBtAtMaterialPara3DLoad()
{
	CString strTemp[MAX_3D_HOLE_COUNT];
	int nTemp = 0;
	int nCnt = 0;
	int nRowCount = 0;

	nRowCount = m_pAT3DListCtrl->GetMaxListCount() - 1;
	for (int i = nRowCount; i >= 0; i--)
	{
		m_pAT3DListCtrl->DeleteListData(i);

	}

	m_pAT3DListCtrl->LoadDataFromCsv(SharedInfo::VisionAgentPath, strTemp, &nTemp);
}