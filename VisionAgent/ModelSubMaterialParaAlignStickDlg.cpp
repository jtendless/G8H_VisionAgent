// ModelSubMaterialParaAlignStickDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "ModelSubMaterialParaAlignStickDlg.h"
#include "afxdialogex.h"


// CModelSubMaterialParaAlignStickDlg 대화 상자

IMPLEMENT_DYNAMIC(CModelSubMaterialParaAlignStickDlg, CDialogEx)

CModelSubMaterialParaAlignStickDlg::CModelSubMaterialParaAlignStickDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MODEL_SUB_MATERIAL_PARA_ALIGN_STICK_DIALOG, pParent)
{
	Create(IDD_MODEL_SUB_MATERIAL_PARA_ALIGN_STICK_DIALOG, pParent);
}

CModelSubMaterialParaAlignStickDlg::~CModelSubMaterialParaAlignStickDlg()
{
}

void CModelSubMaterialParaAlignStickDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CModelSubMaterialParaAlignStickDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CModelSubMaterialParaAlignStickDlg 메시지 처리기
BOOL CModelSubMaterialParaAlignStickDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitCtrl();

	return TRUE;
}

void CModelSubMaterialParaAlignStickDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
}

void CModelSubMaterialParaAlignStickDlg::InitCtrl()
{
	m_bDialog_Entry = TRUE;

	// Up --------------------------------------------------------------
	m_EditUpID.SubclassDlgItem(IDC_MODEL_SUB_MATERIAL_PARA_ALIGN_STICK_EDIT_UP_ID, this);
	m_EditUpOrder.SubclassDlgItem(IDC_MODEL_SUB_MATERIAL_PARA_ALIGN_STICK_EDIT_UP_ORDER, this);
	m_EditUpSizeX.SubclassDlgItem(IDC_MODEL_SUB_MATERIAL_PARA_ALIGN_STICK_EDIT_UP_SIZE_X, this);
	m_EditUpSizeY.SubclassDlgItem(IDC_MODEL_SUB_MATERIAL_PARA_ALIGN_STICK_EDIT_UP_SIZE_Y, this);
	m_EditUpPosY.SubclassDlgItem(IDC_MODEL_SUB_MATERIAL_PARA_ALIGN_STICK_EDIT_UP_POS_Y, this);
	//-------------------------------------------------------------------------

	//Up Align-----------------------------------------------------------------
	m_EditUpAlignMarkSizeX.SubclassDlgItem(IDC_MODEL_SUB_MATERIAL_PARA_ALIGN_STICK_EDIT_UP_ALIGN_MARK_SIZE_X, this);
	m_EditUpAlignMarkSizeY.SubclassDlgItem(IDC_MODEL_SUB_MATERIAL_PARA_ALIGN_STICK_EDIT_UP_ALIGN_MARK_SIZE_Y, this);
	m_EditUpAlignMarkLTX.SubclassDlgItem(IDC_MODEL_SUB_MATERIAL_PARA_ALIGN_STICK_EDIT_UP_ALIGN_MARK_LT_X, this);
	m_EditUpAlignMarkLTY.SubclassDlgItem(IDC_MODEL_SUB_MATERIAL_PARA_ALIGN_STICK_EDIT_UP_ALIGN_MARK_LT_Y, this);
	m_EditUpAlignMarkRTX.SubclassDlgItem(IDC_MODEL_SUB_MATERIAL_PARA_ALIGN_STICK_EDIT_UP_ALIGN_MARK_RT_X, this);
	m_EditUpAlignMarkRTY.SubclassDlgItem(IDC_MODEL_SUB_MATERIAL_PARA_ALIGN_STICK_EDIT_UP_ALIGN_MARK_RT_Y, this);

	//Up Depo-----------------------------------------------------------------
	m_EditUpDepoMarkSizeX.SubclassDlgItem(IDC_MODEL_SUB_MATERIAL_PARA_ALIGN_STICK_EDIT_UP_DEPO_MARK_SIZE_X, this);
	m_EditUpDepoMarkSizeY.SubclassDlgItem(IDC_MODEL_SUB_MATERIAL_PARA_ALIGN_STICK_EDIT_UP_DEPO_MARK_SIZE_Y, this);
	m_EditUpDepoMarkLTX.SubclassDlgItem(IDC_MODEL_SUB_MATERIAL_PARA_ALIGN_STICK_EDIT_UP_DEPO_MARK_LT_X, this);
	m_EditUpDepoMarkLTY.SubclassDlgItem(IDC_MODEL_SUB_MATERIAL_PARA_ALIGN_STICK_EDIT_UP_DEPO_MARK_LT_Y, this);
	m_EditUpDepoMarkRTX.SubclassDlgItem(IDC_MODEL_SUB_MATERIAL_PARA_ALIGN_STICK_EDIT_UP_DEPO_MARK_RT_X, this);
	m_EditUpDepoMarkRTY.SubclassDlgItem(IDC_MODEL_SUB_MATERIAL_PARA_ALIGN_STICK_EDIT_UP_DEPO_MARK_RT_Y, this);
	//-------------------------------------------------------------------------

	//Up Teg-----------------------------------------------------------------
	m_EditUpTegMarkSizeX.SubclassDlgItem(IDC_MODEL_SUB_MATERIAL_PARA_ALIGN_STICK_EDIT_UP_TEG_MARK_SIZE_X, this);
	m_EditUpTegMarkSizeY.SubclassDlgItem(IDC_MODEL_SUB_MATERIAL_PARA_ALIGN_STICK_EDIT_UP_TEG_MARK_SIZE_Y, this);
	m_EditUpTegMarkLTX.SubclassDlgItem(IDC_MODEL_SUB_MATERIAL_PARA_ALIGN_STICK_EDIT_UP_TEG_MARK_LT_X, this);
	m_EditUpTegMarkLTY.SubclassDlgItem(IDC_MODEL_SUB_MATERIAL_PARA_ALIGN_STICK_EDIT_UP_TEG_MARK_LT_Y, this);
	m_EditUpTegMarkRTX.SubclassDlgItem(IDC_MODEL_SUB_MATERIAL_PARA_ALIGN_STICK_EDIT_UP_TEG_MARK_RT_X, this);
	m_EditUpTegMarkRTY.SubclassDlgItem(IDC_MODEL_SUB_MATERIAL_PARA_ALIGN_STICK_EDIT_UP_TEG_MARK_RT_Y, this);
	//-------------------------------------------------------------------------

	m_EditUpSkirtPitchY.SubclassDlgItem(IDC_MODEL_SUB_MATERIAL_PARA_ALIGN_STICK_EDIT_UP_SKIRT_PITCH_Y, this);

	m_EditUpBcrPosX.SubclassDlgItem(IDC_MODEL_SUB_MATERIAL_PARA_ALIGN_STICK_EDIT_UP_BCR_POS_X, this);
	m_EditUpBcrPosY.SubclassDlgItem(IDC_MODEL_SUB_MATERIAL_PARA_ALIGN_STICK_EDIT_UP_BCR_POS_Y, this);
}

void CModelSubMaterialParaAlignStickDlg::InitPara()
{
	CString Str;


	TCHAR szUniCode[50];
	CString szMSg, szMsg;

	//Up ---------------------------------------------------------------------
	szMsg.Format(_T("%s"), CModelData::m_MaterialParaAlignStick.Info.strID);
	m_EditUpID.SetWindowText(szMsg);

	szMSg.Format(_T("%d"), CModelData::m_MaterialParaAlignStick.Info.nOrder);
	m_EditUpOrder.SetWindowText(szMSg);

	//szMSg.Format(_T("%.5f"), CModelData::m_MaterialParaAlignStick.Info.dSizeX);
	szMSg.Format(_T("0"));
	m_EditUpSizeX.SetWindowText(szMSg);

	szMSg.Format(_T("%.5f"), CModelData::m_MaterialParaAlignStick.Info.dSizeY);
	m_EditUpSizeY.SetWindowText(szMSg);

	szMSg.Format(_T("%.5f"), CModelData::m_MaterialParaAlignStick.Info.dPosY);
	m_EditUpPosY.SetWindowText(szMSg);
	//-------------------------------------------------------------------------

	//Up [Group] Align---------------------------------------------------------
	szMSg.Format(_T("%.5f"), CModelData::m_MaterialParaAlignStick.Info.dAlignMarkSizeX);
	m_EditUpAlignMarkSizeX.SetWindowText(szMSg);

	szMSg.Format(_T("%.5f"), CModelData::m_MaterialParaAlignStick.Info.dAlignMarkSizeY);
	m_EditUpAlignMarkSizeY.SetWindowText(szMSg);

	szMSg.Format(_T("%.5f"), CModelData::m_MaterialParaAlignStick.Info.dAlignMarkLTX);
	m_EditUpAlignMarkLTX.SetWindowText(szMSg);

	szMSg.Format(_T("%.5f"), CModelData::m_MaterialParaAlignStick.Info.dAlignMarkLTY);
	m_EditUpAlignMarkLTY.SetWindowText(szMSg);

	szMSg.Format(_T("%.5f"), CModelData::m_MaterialParaAlignStick.Info.dAlignMarkRTX);
	m_EditUpAlignMarkRTX.SetWindowText(szMSg);

	szMSg.Format(_T("%.5f"), CModelData::m_MaterialParaAlignStick.Info.dAlignMarkRTY);
	m_EditUpAlignMarkRTY.SetWindowText(szMSg);
	//-------------------------------------------------------------------------

	//Up [Group] Depo---------------------------------------------------------
	szMSg.Format(_T("%.5f"), CModelData::m_MaterialParaAlignStick.Info.dDepoMarkSizeX);
	m_EditUpDepoMarkSizeX.SetWindowText(szMSg);

	szMSg.Format(_T("%.5f"), CModelData::m_MaterialParaAlignStick.Info.dDepoMarkSizeY);
	m_EditUpDepoMarkSizeY.SetWindowText(szMSg);

	szMSg.Format(_T("%.5f"), CModelData::m_MaterialParaAlignStick.Info.dDepoMarkLTX);
	m_EditUpDepoMarkLTX.SetWindowText(szMSg);

	szMSg.Format(_T("%.5f"), CModelData::m_MaterialParaAlignStick.Info.dDepoMarkLTY);
	m_EditUpDepoMarkLTY.SetWindowText(szMSg);

	szMSg.Format(_T("%.5f"), CModelData::m_MaterialParaAlignStick.Info.dDepoMarkRTX);
	m_EditUpDepoMarkRTX.SetWindowText(szMSg);

	szMSg.Format(_T("%.5f"), CModelData::m_MaterialParaAlignStick.Info.dDepoMarkRTY);
	m_EditUpDepoMarkRTY.SetWindowText(szMSg);
	//-------------------------------------------------------------------------

	//Up [Group] Teg---------------------------------------------------------
	szMSg.Format(_T("%.5f"), CModelData::m_MaterialParaAlignStick.Info.dTegSizeX);
	m_EditUpTegMarkSizeX.SetWindowText(szMSg);

	szMSg.Format(_T("%.5f"), CModelData::m_MaterialParaAlignStick.Info.dTegSizeY);
	m_EditUpTegMarkSizeY.SetWindowText(szMSg);

	szMSg.Format(_T("%.5f"), CModelData::m_MaterialParaAlignStick.Info.dTegLT1X);
	m_EditUpTegMarkLTX.SetWindowText(szMSg);

	szMSg.Format(_T("%.5f"), CModelData::m_MaterialParaAlignStick.Info.dTegLT1Y);
	m_EditUpTegMarkLTY.SetWindowText(szMSg);

	szMSg.Format(_T("%.5f"), CModelData::m_MaterialParaAlignStick.Info.dTegRT2X);
	m_EditUpTegMarkRTX.SetWindowText(szMSg);

	szMSg.Format(_T("%.5f"), CModelData::m_MaterialParaAlignStick.Info.dTegRT2Y);
	m_EditUpTegMarkRTY.SetWindowText(szMSg);
	//-------------------------------------------------------------------------

	m_EditUpSkirtPitchY.SetWindowText(_ToStr(_T("%.4f"), CModelData::m_MaterialParaAlignStick.Info.dSkirtPitchY));

	m_EditUpBcrPosX.SetWindowText(_ToStr(_T("%.4f"), CModelData::m_MaterialParaAlignStick.Info.dBcrPosX));
	m_EditUpBcrPosY.SetWindowText(_ToStr(_T("%.4f"), CModelData::m_MaterialParaAlignStick.Info.dBcrPosY));
}



BOOL CModelSubMaterialParaAlignStickDlg::CheckChangeData()
{
	CString szMsg;


	m_EditUpID.GetWindowText(szMsg);
	memset(CModelData::m_MaterialParaAlignStick.Info.strID, 0x0, sizeof(CModelData::m_MaterialParaAlignStick.Info.strID));
	//_tcscpy_s(CModelData::m_MaterialParaAlignStick.Info.strID, szMsg.GetLength() + 1, szMsg.GetBuffer(0));
	//szMsg.ReleaseBuffer(); //!!
	swprintf_s(CModelData::m_MaterialParaAlignStick.Info.strID, szMsg);

	m_EditUpOrder.GetWindowText(szMsg);				CModelData::m_MaterialParaAlignStick.Info.nOrder = _ttoi(szMsg);
//	m_EditUpSizeX.GetWindowText(szMsg);				CModelData::m_MaterialParaAlignStick.Info.dSizeX = _ttof(szMsg);
	m_EditUpSizeY.GetWindowText(szMsg);				CModelData::m_MaterialParaAlignStick.Info.dSizeY = _ttof(szMsg);
	m_EditUpPosY.GetWindowText(szMsg);				CModelData::m_MaterialParaAlignStick.Info.dPosY = _ttof(szMsg);
	m_EditUpAlignMarkSizeX.GetWindowText(szMsg);	CModelData::m_MaterialParaAlignStick.Info.dAlignMarkSizeX = _ttof(szMsg);
	m_EditUpAlignMarkSizeY.GetWindowText(szMsg);	CModelData::m_MaterialParaAlignStick.Info.dAlignMarkSizeY = _ttof(szMsg);
	m_EditUpAlignMarkLTX.GetWindowText(szMsg);		CModelData::m_MaterialParaAlignStick.Info.dAlignMarkLTX = _ttof(szMsg);
	m_EditUpAlignMarkLTY.GetWindowText(szMsg);		CModelData::m_MaterialParaAlignStick.Info.dAlignMarkLTY = _ttof(szMsg);
	m_EditUpAlignMarkRTX.GetWindowText(szMsg);		CModelData::m_MaterialParaAlignStick.Info.dAlignMarkRTX = _ttof(szMsg);
	m_EditUpAlignMarkRTY.GetWindowText(szMsg);		CModelData::m_MaterialParaAlignStick.Info.dAlignMarkRTY = _ttof(szMsg);
	m_EditUpDepoMarkSizeX.GetWindowText(szMsg);		CModelData::m_MaterialParaAlignStick.Info.dDepoMarkSizeX = _ttof(szMsg);
	m_EditUpDepoMarkSizeY.GetWindowText(szMsg);		CModelData::m_MaterialParaAlignStick.Info.dDepoMarkSizeY = _ttof(szMsg);
	m_EditUpDepoMarkLTX.GetWindowText(szMsg);		CModelData::m_MaterialParaAlignStick.Info.dDepoMarkLTX = _ttof(szMsg);
	m_EditUpDepoMarkLTY.GetWindowText(szMsg);		CModelData::m_MaterialParaAlignStick.Info.dDepoMarkLTY = _ttof(szMsg);
	m_EditUpDepoMarkRTX.GetWindowText(szMsg);		CModelData::m_MaterialParaAlignStick.Info.dDepoMarkRTX = _ttof(szMsg);
	m_EditUpDepoMarkRTY.GetWindowText(szMsg);		CModelData::m_MaterialParaAlignStick.Info.dDepoMarkRTY = _ttof(szMsg);
	m_EditUpTegMarkSizeX.GetWindowText(szMsg);		CModelData::m_MaterialParaAlignStick.Info.dTegSizeX = _ttof(szMsg);
	m_EditUpTegMarkSizeY.GetWindowText(szMsg);		CModelData::m_MaterialParaAlignStick.Info.dTegSizeY = _ttof(szMsg);
	m_EditUpTegMarkLTX.GetWindowText(szMsg);		CModelData::m_MaterialParaAlignStick.Info.dTegLT1X = _ttof(szMsg);
	m_EditUpTegMarkLTY.GetWindowText(szMsg);		CModelData::m_MaterialParaAlignStick.Info.dTegLT1Y = _ttof(szMsg);
	m_EditUpTegMarkRTX.GetWindowText(szMsg);		CModelData::m_MaterialParaAlignStick.Info.dTegRT2X = _ttof(szMsg);
	m_EditUpTegMarkRTY.GetWindowText(szMsg);		CModelData::m_MaterialParaAlignStick.Info.dTegRT2Y = _ttof(szMsg);
	m_EditUpSkirtPitchY.GetWindowText(szMsg);		CModelData::m_MaterialParaAlignStick.Info.dSkirtPitchY = _ttof(szMsg);
	m_EditUpBcrPosX.GetWindowText(szMsg);			CModelData::m_MaterialParaAlignStick.Info.dBcrPosX = _ttof(szMsg);
	m_EditUpBcrPosY.GetWindowText(szMsg);			CModelData::m_MaterialParaAlignStick.Info.dBcrPosY = _ttof(szMsg);

	return TRUE;
}


void CModelSubMaterialParaAlignStickDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow == TRUE)
	{
		InitPara();
	}
}

BOOL CModelSubMaterialParaAlignStickDlg::SavePara()
{
	CheckChangeData();

	BOOL bRtn = CModelData::m_MaterialParaAlignStick.Save();
	if (bRtn == TRUE)
		AfxMessageBox(_T("Save Ok"));
	else
		AfxMessageBox(_T("Save Fail !!"));

	return TRUE;
}
