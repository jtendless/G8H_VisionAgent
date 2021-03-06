// SystemMachineAxisPosSubDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "SystemSaftySubDlg.h"
#include "afxdialogex.h"
#include "../Module/Data/SystemData.h"

// CSystemSaftySubDlg 대화 상자

IMPLEMENT_DYNAMIC(CSystemSaftySubDlg, CDialogEx)

CSystemSaftySubDlg::CSystemSaftySubDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SYSTEM_SAFTY_PAGE_1_DIALOG, pParent)
{
	Create(IDD_SYSTEM_SAFTY_PAGE_1_DIALOG, pParent);
}

CSystemSaftySubDlg::~CSystemSaftySubDlg()
{
}

void CSystemSaftySubDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSystemSaftySubDlg, CDialogEx)
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CSystemSaftySubDlg 메시지 처리기
BOOL CSystemSaftySubDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitCtrl();

	return TRUE;
}

void CSystemSaftySubDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	
}

void CSystemSaftySubDlg::OnShowWindow(BOOL bShow, UINT nStatus)
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

BOOL CSystemSaftySubDlg::InitCtrl()
{
	m_editSafetyMin_Review10X_X.SubclassDlgItem(IDC_EDIT_SYSTEM_SAFETY_POS_MIN_REVIEW10X_X, this);
	m_editSafetyMax_Review10X_X.SubclassDlgItem(IDC_EDIT_SYSTEM_SAFETY_POS_MAX_REVIEW10X_X, this);
	m_editSafetyMin_Review10X_Y_In_BoxStage.SubclassDlgItem(IDC_EDIT_SYSTEM_SAFETY_POS_MIN_REVIEW10X_Y_IN_BOX_STAGE, this);
	m_editSafetyMin_Review10X_Y_In_PaperStage.SubclassDlgItem(IDC_EDIT_SYSTEM_SAFETY_POS_MIN_REVIEW10X_Y_IN_PAPER_STAGE, this);
	m_editSafetyMin_Review10X_Y_In_InspectionStage.SubclassDlgItem(IDC_EDIT_SYSTEM_SAFETY_POS_MIN_REVIEW10X_Y_IN_INSPECTION_STAGE, this);
	m_editSafetyMax_Review10X_Y.SubclassDlgItem(IDC_EDIT_SYSTEM_SAFETY_POS_MAX_REVIEW10X_Y, this);
	m_editSafetyMin_Review10X_Z.SubclassDlgItem(IDC_EDIT_SYSTEM_SAFETY_POS_MIN_REVIEW10X_Z, this);

	m_editSafetyMin_AOI_X.SubclassDlgItem(IDC_EDIT_SYSTEM_SAFETY_POS_MIN_AOI_X, this);
	m_editSafetyMax_AOI_X.SubclassDlgItem(IDC_EDIT_SYSTEM_SAFETY_POS_MAX_AOI_X, this);
	m_editSafetyMin_AOI_Y.SubclassDlgItem(IDC_EDIT_SYSTEM_SAFETY_POS_MIN_AOI_Y, this);
	m_editSafetyMax_AOI_Y.SubclassDlgItem(IDC_EDIT_SYSTEM_SAFETY_POS_MAX_AOI_Y, this);
	m_editSafetyMin_AOI_Z.SubclassDlgItem(IDC_EDIT_SYSTEM_SAFETY_POS_MIN_AOI_Z, this);

	m_editSafetyMin_3D_X.SubclassDlgItem(IDC_EDIT_SYSTEM_SAFETY_POS_MIN_3D_X, this);
	m_editSafetyMax_3D_X.SubclassDlgItem(IDC_EDIT_SYSTEM_SAFETY_POS_MAX_3D_X, this);
	m_editSafetyMin_3D_Y.SubclassDlgItem(IDC_EDIT_SYSTEM_SAFETY_POS_MIN_3D_Y, this);
	m_editSafetyMax_3D_Y.SubclassDlgItem(IDC_EDIT_SYSTEM_SAFETY_POS_MAX_3D_Y, this);
	m_editSafetyMin_3D_Z.SubclassDlgItem(IDC_EDIT_SYSTEM_SAFETY_POS_MIN_3D_Z, this);

	m_editSafetyMin_Loader_Z_In_BoxStage.SubclassDlgItem(IDC_EDIT_SYSTEM_SAFETY_POS_MIN_LOADER_Z_IN_BOX_STAGE, this);
	m_editSafetyMin_Loader_Z_In_PaperStage.SubclassDlgItem(IDC_EDIT_SYSTEM_SAFETY_POS_MIN_LOADER_Z_IN_PAPER_STAGE, this);
	m_editSafetyMin_Loader_Z_In_InspectionStage.SubclassDlgItem(IDC_EDIT_SYSTEM_SAFETY_POS_MIN_LOADER_Z_IN_INSPECTION_STAGE, this);

	m_editDist_GantryYToUnloaderY.SubclassDlgItem(IDC_EDIT_SYSTEM_SAFETY_DIST_GANTRY_Y_TO_UNLOAD_Y, this);
	m_editDist_GantryYToLoaderY.SubclassDlgItem(IDC_EDIT_SYSTEM_SAFETY_DIST_GANTRY_Y_TO_LOAD_Y, this);

	m_editMinDist_GantryYToUnloaderY.SubclassDlgItem(IDC_EDIT_SYSTEM_SAFETY_MIN_DIST_GANTRY_Y_TO_UNLOAD_Y, this);
	m_editMinDist_GantryYToLoaderY.SubclassDlgItem(IDC_EDIT_SYSTEM_SAFETY_MIN_DIST_GANTRY_Y_TO_LOAD_Y, this);

	m_editMinDist_PaperUnloaderToLoaderY.SubclassDlgItem(IDC_EDIT_SYSTEM_SAFETY_MIN_DIST_PAPER_UNLOADER_Y_TO_LOADER_Y, this);
	m_editMinDist_PaperUnloaderToLoaderX.SubclassDlgItem(IDC_EDIT_SYSTEM_SAFETY_MIN_DIST_PAPER_UNLOADER_X_TO_LOADER_X, this);

	m_chkSafetyUsage.SubclassDlgItem(IDC_CHECK_SYSTEM_SAFETY_USAGE, this);

	return TRUE;
}
BOOL CSystemSaftySubDlg::InitPara()
{
	CString Str = _T("");

	Str.Format(_T("%.5f"), CSystemData::m_Safety.Info.m_dSafetyPos_Min_Review10X_X);
	m_editSafetyMin_Review10X_X.SetWindowText(Str);
	Str.Format(_T("%.5f"), CSystemData::m_Safety.Info.m_dSafetyPos_Max_Review10X_X);
	m_editSafetyMax_Review10X_X.SetWindowText(Str);
	Str.Format(_T("%.5f"), CSystemData::m_Safety.Info.m_dSafetyPos_Min_Review10X_Y_In_BoxStage);
	m_editSafetyMin_Review10X_Y_In_BoxStage.SetWindowText(Str);
	Str.Format(_T("%.5f"), CSystemData::m_Safety.Info.m_dSafetyPos_Min_Review10X_Y_In_PaperStage);
	m_editSafetyMin_Review10X_Y_In_PaperStage.SetWindowText(Str);
	Str.Format(_T("%.5f"), CSystemData::m_Safety.Info.m_dSafetyPos_Min_Review10X_Y_In_InspectionStage);
	m_editSafetyMin_Review10X_Y_In_InspectionStage.SetWindowText(Str);
	Str.Format(_T("%.5f"), CSystemData::m_Safety.Info.m_dSafetyPos_Max_Review10X_Y);
	m_editSafetyMax_Review10X_Y.SetWindowText(Str);
	Str.Format(_T("%.5f"), CSystemData::m_Safety.Info.m_dSafetyPos_Min_Review10X_Z);
	m_editSafetyMin_Review10X_Z.SetWindowText(Str);

	Str.Format(_T("%.5f"), CSystemData::m_Safety.Info.m_dSafetyPos_Min_AOI_X);
	m_editSafetyMin_AOI_X.SetWindowText(Str);
	Str.Format(_T("%.5f"), CSystemData::m_Safety.Info.m_dSafetyPos_Max_AOI_X);
	m_editSafetyMax_AOI_X.SetWindowText(Str);
	Str.Format(_T("%.5f"), CSystemData::m_Safety.Info.m_dSafetyPos_Min_AOI_Y);
	m_editSafetyMin_AOI_Y.SetWindowText(Str);
	Str.Format(_T("%.5f"), CSystemData::m_Safety.Info.m_dSafetyPos_Max_AOI_Y);
	m_editSafetyMax_AOI_Y.SetWindowText(Str);
	Str.Format(_T("%.5f"), CSystemData::m_Safety.Info.m_dSafetyPos_Min_AOI_Z);
	m_editSafetyMin_AOI_Z.SetWindowText(Str);

	Str.Format(_T("%.5f"), CSystemData::m_Safety.Info.m_dSafetyPos_Min_Zoom_3D_X);
	m_editSafetyMin_3D_X.SetWindowText(Str);
	Str.Format(_T("%.5f"), CSystemData::m_Safety.Info.m_dSafetyPos_Max_Zoom_3D_X);
	m_editSafetyMax_3D_X.SetWindowText(Str);
	Str.Format(_T("%.5f"), CSystemData::m_Safety.Info.m_dSafetyPos_Min_Zoom_3D_Y);
	m_editSafetyMin_3D_Y.SetWindowText(Str);
	Str.Format(_T("%.5f"), CSystemData::m_Safety.Info.m_dSafetyPos_Max_Zoom_3D_Y);
	m_editSafetyMax_3D_Y.SetWindowText(Str);
	Str.Format(_T("%.5f"), CSystemData::m_Safety.Info.m_dSafetyPos_Min_Zoom_3D_Z);
	m_editSafetyMin_3D_Z.SetWindowText(Str);

	Str.Format(_T("%.5f"), CSystemData::m_Safety.Info.m_dSafetyPos_Min_Loader_Z_In_Box_Stage);
	m_editSafetyMin_Loader_Z_In_BoxStage.SetWindowText(Str);
	Str.Format(_T("%.5f"), CSystemData::m_Safety.Info.m_dSafetyPos_Min_Loader_Z_In_Paper_Stage);
	m_editSafetyMin_Loader_Z_In_PaperStage.SetWindowText(Str);
	Str.Format(_T("%.5f"), CSystemData::m_Safety.Info.m_dSafetyPos_Min_Loader_Z_In_Inspection_Stage);
	m_editSafetyMin_Loader_Z_In_InspectionStage.SetWindowText(Str);

	Str.Format(_T("%.5f"), CSystemData::m_Safety.Info.m_dDist_GantryY_To_UnloaderY);
	m_editDist_GantryYToUnloaderY.SetWindowText(Str);
	Str.Format(_T("%.5f"), CSystemData::m_Safety.Info.m_dDist_GantryY_To_LoaderY);
	m_editDist_GantryYToLoaderY.SetWindowText(Str);

	Str.Format(_T("%.5f"), CSystemData::m_Safety.Info.m_dMinDist_GantryY_To_UnloaderY);
	m_editMinDist_GantryYToUnloaderY.SetWindowText(Str);
	Str.Format(_T("%.5f"), CSystemData::m_Safety.Info.m_dMinDist_GantryY_To_LoaderY);
	m_editMinDist_GantryYToLoaderY.SetWindowText(Str);

	Str.Format(_T("%.5f"), CSystemData::m_Safety.Info.m_dMinDist_PaperUnloaderY_To_LoaderY);
	m_editMinDist_PaperUnloaderToLoaderY.SetWindowText(Str);
	Str.Format(_T("%.5f"), CSystemData::m_Safety.Info.m_dMinDist_PaperUnloaderX_To_LoaderX);
	m_editMinDist_PaperUnloaderToLoaderX.SetWindowText(Str);

	m_chkSafetyUsage.SetCheck(CSystemData::m_Safety.Info.m_nUseSystemSafety);

	return TRUE;
}
BOOL CSystemSaftySubDlg::CheckChangeData()
{
	CString Str = _T("");

	m_editSafetyMin_Review10X_X.GetWindowText(Str);
	CSystemData::m_Safety.Info.m_dSafetyPos_Min_Review10X_X = _ttof(Str);
	m_editSafetyMax_Review10X_X.GetWindowText(Str);
	CSystemData::m_Safety.Info.m_dSafetyPos_Max_Review10X_X = _ttof(Str);
	m_editSafetyMin_Review10X_Y_In_BoxStage.GetWindowText(Str);
	CSystemData::m_Safety.Info.m_dSafetyPos_Min_Review10X_Y_In_BoxStage = _ttof(Str);
	m_editSafetyMin_Review10X_Y_In_PaperStage.GetWindowText(Str);
	CSystemData::m_Safety.Info.m_dSafetyPos_Min_Review10X_Y_In_PaperStage = _ttof(Str);
	m_editSafetyMin_Review10X_Y_In_InspectionStage.GetWindowText(Str);
	CSystemData::m_Safety.Info.m_dSafetyPos_Min_Review10X_Y_In_InspectionStage = _ttof(Str);
	m_editSafetyMax_Review10X_Y.GetWindowText(Str);
	CSystemData::m_Safety.Info.m_dSafetyPos_Max_Review10X_Y = _ttof(Str);
	m_editSafetyMin_Review10X_Z.GetWindowText(Str);
	CSystemData::m_Safety.Info.m_dSafetyPos_Min_Review10X_Z = _ttof(Str);

	m_editSafetyMin_AOI_X.GetWindowText(Str);
	CSystemData::m_Safety.Info.m_dSafetyPos_Min_AOI_X = _ttof(Str);
	m_editSafetyMax_AOI_X.GetWindowText(Str);
	CSystemData::m_Safety.Info.m_dSafetyPos_Max_AOI_X = _ttof(Str);
	m_editSafetyMin_AOI_Y.GetWindowText(Str);
	CSystemData::m_Safety.Info.m_dSafetyPos_Min_AOI_Y = _ttof(Str);
	m_editSafetyMax_AOI_Y.GetWindowText(Str);
	CSystemData::m_Safety.Info.m_dSafetyPos_Max_AOI_Y = _ttof(Str);
	m_editSafetyMin_AOI_Z.GetWindowText(Str);
	CSystemData::m_Safety.Info.m_dSafetyPos_Min_AOI_Z = _ttof(Str);

	m_editSafetyMin_3D_X.GetWindowText(Str);
	CSystemData::m_Safety.Info.m_dSafetyPos_Min_Zoom_3D_X = _ttof(Str);
	m_editSafetyMax_3D_X.GetWindowText(Str);
	CSystemData::m_Safety.Info.m_dSafetyPos_Max_Zoom_3D_X = _ttof(Str);
	m_editSafetyMin_3D_Y.GetWindowText(Str);
	CSystemData::m_Safety.Info.m_dSafetyPos_Min_Zoom_3D_Y = _ttof(Str);
	m_editSafetyMax_3D_Y.GetWindowText(Str);
	CSystemData::m_Safety.Info.m_dSafetyPos_Max_Zoom_3D_Y = _ttof(Str);
	m_editSafetyMin_3D_Z.GetWindowText(Str);
	CSystemData::m_Safety.Info.m_dSafetyPos_Min_Zoom_3D_Z = _ttof(Str);

	m_editSafetyMin_Loader_Z_In_BoxStage.GetWindowText(Str);
	CSystemData::m_Safety.Info.m_dSafetyPos_Min_Loader_Z_In_Box_Stage = _ttof(Str);
	m_editSafetyMin_Loader_Z_In_PaperStage.GetWindowText(Str);
	CSystemData::m_Safety.Info.m_dSafetyPos_Min_Loader_Z_In_Paper_Stage = _ttof(Str);
	m_editSafetyMin_Loader_Z_In_InspectionStage.GetWindowText(Str);
	CSystemData::m_Safety.Info.m_dSafetyPos_Min_Loader_Z_In_Inspection_Stage = _ttof(Str);

	m_editDist_GantryYToUnloaderY.GetWindowText(Str);
	CSystemData::m_Safety.Info.m_dDist_GantryY_To_UnloaderY = _ttof(Str);
	m_editDist_GantryYToLoaderY.GetWindowText(Str);
	CSystemData::m_Safety.Info.m_dDist_GantryY_To_LoaderY = _ttof(Str);

	m_editMinDist_GantryYToUnloaderY.GetWindowText(Str);
	CSystemData::m_Safety.Info.m_dMinDist_GantryY_To_UnloaderY = _ttof(Str);
	m_editMinDist_GantryYToLoaderY.GetWindowText(Str);
	CSystemData::m_Safety.Info.m_dMinDist_GantryY_To_LoaderY = _ttof(Str);

	m_editMinDist_PaperUnloaderToLoaderY.GetWindowText(Str);
	CSystemData::m_Safety.Info.m_dMinDist_PaperUnloaderY_To_LoaderY = _ttof(Str);
	m_editMinDist_PaperUnloaderToLoaderX.GetWindowText(Str);
	CSystemData::m_Safety.Info.m_dMinDist_PaperUnloaderX_To_LoaderX = _ttof(Str);

	CSystemData::m_Safety.Info.m_nUseSystemSafety = m_chkSafetyUsage.GetCheck();

	return TRUE;
}

BOOL CSystemSaftySubDlg::SavePara()
{
	CheckChangeData();

	BOOL bRtn = CSystemData::m_Safety.Save();
	if (bRtn == TRUE)
		AfxMessageBox(_T("Save Ok"));
	else
		AfxMessageBox(_T("Save Fail !!"));

	return TRUE;
}