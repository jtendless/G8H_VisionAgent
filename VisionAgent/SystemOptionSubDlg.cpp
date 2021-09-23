// SystemOptionSubDlg.cpp : 备泅 颇老涝聪促.
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentDlg.h"
#include "SystemDlg.h"
#include "SystemOptionSubDlg.h"
#include "afxdialogex.h"


// CSystemOptionSubDlg 措拳 惑磊涝聪促.

IMPLEMENT_DYNAMIC(CSystemOptionSubDlg, CDialogEx)

CSystemOptionSubDlg::CSystemOptionSubDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SYSTEM_OPTION_PAGE_1_DIALOG, pParent)
{
	Create(IDD_SYSTEM_OPTION_PAGE_1_DIALOG, pParent);
}

CSystemOptionSubDlg::~CSystemOptionSubDlg()
{
}

void CSystemOptionSubDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSystemOptionSubDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_CBN_SELCHANGE(IDC_COMBO_SYSTEM_OPTION_SMART_AUTO_FOCUS_SCAN_MODE, &CSystemOptionSubDlg::OnCbnSelchangeComboSystemOptionSmartAutoFocusScanMode)
END_MESSAGE_MAP()


// CSystemOptionSubDlg 皋矫瘤 贸府扁涝聪促.


BOOL CSystemOptionSubDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitCtrl();

	return TRUE;
}

BOOL CSystemOptionSubDlg::InitCtrl()
{
	CString strTemp = _T("");

	m_Chk_ImageAutoDel.SubclassDlgItem(IDC_CHECK_SYSTEM_OPTION_AUTO_IMAGE_DELETE, this);

	m_Edit_ImageDelPeriod.SubclassDlgItem(IDC_EDIT_SYSTEM_OPTION_AUTO_IMAGE_DELETE_PERIOD, this);

	m_comboAutoFocusMode.SubclassDlgItem(IDC_COMBO_SYSTEM_OPTION_AUTO_FOCUS_MODE, this);
	m_comboAutoFocusMode.ResetContent();
	m_comboAutoFocusMode.AddString(_T("Normal AutoFocus"));
	m_comboAutoFocusMode.AddString(_T("Smart AutoFocus"));
	m_comboAutoFocusMode.SetCurSel(0);
	
	m_comboSmart_InMotionCheckMode.SubclassDlgItem(IDC_COMBO_SYSTEM_OPTION_SMART_AUTO_FOCUS_INMOTION_CHECK_MODE, this);
	m_comboSmart_InMotionCheckMode.ResetContent();
	m_comboSmart_InMotionCheckMode.AddString(_T("Delay Time"));
	m_comboSmart_InMotionCheckMode.AddString(_T("Busy+InPos"));
	m_comboSmart_InMotionCheckMode.AddString(_T("Busy"));
	m_comboSmart_InMotionCheckMode.SetCurSel(0);
	m_editSmart_DelayTime.SubclassDlgItem(IDC_EDIT_SYSTEM_OPTION_SMART_AUTO_FOCUS_DELAY_TIME, this);
	m_editSmart_MaxTurnCount.SubclassDlgItem(IDC_EDIT_SYSTEM_OPTION_SMART_AUTO_FOCUS_MAX_TURN_COUNT, this);
	m_editSmart_RefTurnCount.SubclassDlgItem(IDC_EDIT_SYSTEM_OPTION_SMART_AUTO_FOCUS_REF_TURN_COUNT, this);
	m_editSmart_LimitFocusValue.SubclassDlgItem(IDC_EDIT_SYSTEM_OPTION_SMART_AUTO_FOCUS_LIMIT_FOCUS_VALUE, this);
	m_editSmart_MinFocusValue.SubclassDlgItem(IDC_EDIT_SYSTEM_OPTION_SMART_AUTO_FOCUS_MIN_FOCUS_VALUE, this);
	m_editSmart_FocusTolerance.SubclassDlgItem(IDC_EDIT_SYSTEM_OPTION_SMART_AUTO_FOCUS_FOCUS_TOLERANCE, this);
	m_comboSmart_ScanMode.SubclassDlgItem(IDC_COMBO_SYSTEM_OPTION_SMART_AUTO_FOCUS_SCAN_MODE, this);
	m_comboSmart_ScanMode.ResetContent();
	m_comboSmart_ScanMode.AddString(_T("Smart Scan"));
	m_comboSmart_ScanMode.AddString(_T("Single Dir Scan"));
	m_comboSmart_ScanMode.AddString(_T("Dual Dir Scan"));
	m_comboSmart_ScanMode.SetCurSel(0);
	m_editSmart_MinStepValue.SubclassDlgItem(IDC_EDIT_SYSTEM_OPTION_SMART_AUTO_FOCUS_MIN_STEP_VALUE, this);
	m_editSmart_MaxStepValue.SubclassDlgItem(IDC_EDIT_SYSTEM_OPTION_SMART_AUTO_FOCUS_MAX_STEP_VALUE, this);
	m_editSmart_DownDistRange.SubclassDlgItem(IDC_EDIT_SYSTEM_OPTION_SMART_AUTO_FOCUS_DOWN_DIST_RANGE, this);
	m_editSmart_UpDistRange.SubclassDlgItem(IDC_EDIT_SYSTEM_OPTION_SMART_AUTO_FOCUS_UP_DIST_RANGE, this);

	m_editSmart_Vel.SubclassDlgItem(IDC_EDIT_SYSTEM_OPTION_SMART_AUTO_FOCUS_VEL, this);
	m_editSmart_Accel.SubclassDlgItem(IDC_EDIT_SYSTEM_OPTION_SMART_AUTO_FOCUS_ACCEL, this);
	m_editSmart_Decel.SubclassDlgItem(IDC_EDIT_SYSTEM_OPTION_SMART_AUTO_FOCUS_DECEL, this);

	m_checkAOIMappingGlassMode.SubclassDlgItem(IDC_CHECK_SYSTEM_OPTION_AOI_MAPPING_GLASS_MODE, this);
	m_editAOI_Z_MappingGlassPos.SubclassDlgItem(IDC_EDIT_SYSTEM_OPTION_AOI_Z_MAPPING_GLASS_INSPECTION_POS, this);
	
	m_checkGlassMode.SubclassDlgItem(IDC_CHECK_SYSTEM_OPTION_GLASS_MODE, this);

	m_checkAOIAgingMode.SubclassDlgItem(IDC_CHECK_SYSTEM_OPTION_AOI_AGING_MODE, this);

	return TRUE;
}


void CSystemOptionSubDlg::OnShowWindow(BOOL bShow, UINT nStatus)
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

BOOL CSystemOptionSubDlg::InitPara()
{
	CString Str = _T("");
	int i = 0;

	m_Chk_ImageAutoDel.SetCheck(CSystemData::m_Option.Info.m_bImageAutoDel);
	   
	Str.Format(_T("%d"), CSystemData::m_Option.Info.nImageDelPeriod);
	m_Edit_ImageDelPeriod.SetWindowTextW(Str);

	m_comboAutoFocusMode.SetCurSel(CSystemData::m_Option.Info.m_nAutoFocusMode);

	m_comboSmart_InMotionCheckMode.SetCurSel(CSystemData::m_Option.Info.m_nSmart_InMotionCheckMode);
	Str.Format(_T("%d"), CSystemData::m_Option.Info.m_nSmart_DelayTime);
	m_editSmart_DelayTime.SetWindowText(Str);
	Str.Format(_T("%d"), CSystemData::m_Option.Info.m_nSmart_MaxTurnCount);
	m_editSmart_MaxTurnCount.SetWindowText(Str);
	Str.Format(_T("%d"), CSystemData::m_Option.Info.m_nSmart_RefTurnCount);
	m_editSmart_RefTurnCount.SetWindowText(Str);
	Str.Format(_T("%.1f"), CSystemData::m_Option.Info.m_dSmart_LimitFocusValue);
	m_editSmart_LimitFocusValue.SetWindowText(Str);
	Str.Format(_T("%.1f"), CSystemData::m_Option.Info.m_dSmart_MinFocusValue);
	m_editSmart_MinFocusValue.SetWindowText(Str);
	Str.Format(_T("%.1f"), CSystemData::m_Option.Info.m_dSmart_FocusTolerance);
	m_editSmart_FocusTolerance.SetWindowText(Str);
	m_comboSmart_ScanMode.SetCurSel(CSystemData::m_Option.Info.m_nSmart_ScanMode);
	Str.Format(_T("%.5f"), CSystemData::m_Option.Info.m_dSmart_MinStepValue);
	m_editSmart_MinStepValue.SetWindowText(Str);
	Str.Format(_T("%.5f"), CSystemData::m_Option.Info.m_dSmart_MaxStepValue);
	m_editSmart_MaxStepValue.SetWindowText(Str);
	Str.Format(_T("%.1f"), CSystemData::m_Option.Info.m_dSmart_DownDistRange);
	m_editSmart_DownDistRange.SetWindowText(Str);
	Str.Format(_T("%.1f"), CSystemData::m_Option.Info.m_dSmart_UpDistRange);
	m_editSmart_UpDistRange.SetWindowText(Str);

	Str.Format(_T("%.1f"), CSystemData::m_Option.Info.m_dSmart_Vel); //KJT 20210803 Add
	m_editSmart_Vel.SetWindowText(Str);
	Str.Format(_T("%.1f"), CSystemData::m_Option.Info.m_dSmart_Accel);
	m_editSmart_Accel.SetWindowText(Str);
	Str.Format(_T("%.1f"), CSystemData::m_Option.Info.m_dSmart_Decel);
	m_editSmart_Decel.SetWindowText(Str);

	m_checkAOIAlgorithmSkip.SetCheck(CSystemData::m_Option.Info.m_bAOIAlgorithmSkip);
	m_checkAOIMappingGlassMode.SetCheck(CSystemData::m_Option.Info.m_bAOIMappingGlassMode);
	Str.Format(_T("%.5f"), CSystemData::m_Option.Info.m_dAOI_Z_MappingGlassPos);
	m_editAOI_Z_MappingGlassPos.SetWindowText(Str);

	m_checkGlassMode.SetCheck(CSystemData::m_Option.Info.m_bGlassMode);

	m_checkAOIAgingMode.SetCheck(CSystemData::m_Option.Info.m_bAOIAgingMode);

	return TRUE;
}

BOOL CSystemOptionSubDlg::CheckChangeData()
{
	CString Str    = _T("");
	double dVal = 0.0;
	int nVal1 = 0, nVal2 = 0;
	int i = 0;

#pragma region //Interlock
	//Smart Auto Focus Option
	m_editSmart_RefTurnCount.GetWindowText(Str);
	nVal1 = _ttoi(Str);
	m_editSmart_MaxTurnCount.GetWindowText(Str);
	nVal2 = _ttoi(Str);
	if (nVal1 <= 0 || nVal1 >= nVal2)
	{
		AfxMessageBox(_T("Ref Turn Count Error !! (0 < OkVal < MaxTurnCount)"));
		return FALSE;
	}
	
	if (nVal2 > 16)
	{
		AfxMessageBox(_T(" Range Error !! (RefTurnCount < OkVal <= 16)"));
		return FALSE;
	}

	m_editSmart_DownDistRange.GetWindowText(Str);
	dVal = _ttof(Str);
	if (dVal > 0.0 || dVal < -2.0)
	{
		AfxMessageBox(_T("Down Distance Range Error !! (-2.0 <= OkVal < 0.0)"));
		return FALSE;
	}

	m_editSmart_UpDistRange.GetWindowText(Str);
	dVal = _ttof(Str);
	if (dVal <= 0.0 || dVal > 2.0)
	{
		AfxMessageBox(_T("Up Distance Range Error !! (0.0 < OkVal < 2.0)"));
		return FALSE;
	}

	//KJT 20210803 Add
	m_editSmart_Vel.GetWindowText(Str);
	dVal = _ttof(Str);
	if (dVal < 0.001 || dVal > 3000.0)
	{
		AfxMessageBox(_T("Vel Range Error !! (0.001 < OkVal < 3000.0)"));
		return FALSE;
	}
	m_editSmart_Accel.GetWindowText(Str);
	dVal = _ttof(Str);
	if (dVal < 0.001 || dVal > 3000.0)
	{
		AfxMessageBox(_T("Accel Range Error !! (0.001 < OkVal < 3000.0)"));
		return FALSE;
	}
	m_editSmart_Decel.GetWindowText(Str);
	dVal = _ttof(Str);
	if (dVal < 0.001 || dVal > 3000.0)
	{
		AfxMessageBox(_T("Decel Range Error !! (0.001 < OkVal < 3000.0)"));
		return FALSE;
	}

	//AOI Option
	m_editAOI_Z_MappingGlassPos.GetWindowText(Str);
	dVal = _ttof(Str);
	if (dVal < CManualData::m_ManualDataGantry.Info.m_dGantry_Z2_Inspection_3D_Pos - 0.25)
	{
		AfxMessageBox(_T("AOI Z Mapping Glass Pos Error !! (AOI Z Insp Pos - 0.25 < OkVal"));
		return FALSE;
	}
#pragma endregion
	CSystemData::m_Option.Info.m_bImageAutoSave = TRUE;

	CSystemData::m_Option.Info.m_bImageAutoDel = m_Chk_ImageAutoDel.GetCheck();
	
	m_Edit_ImageDelPeriod.GetWindowText(Str);
	CSystemData::m_Option.Info.nImageDelPeriod = _ttoi(Str);
	if (CSystemData::m_Option.Info.nImageDelPeriod < 1)
	{
		CSystemData::m_Option.Info.nImageDelPeriod = 1;
	}
	else if (CSystemData::m_Option.Info.nImageDelPeriod > 36)
	{
		CSystemData::m_Option.Info.nImageDelPeriod = 36;
	}

#pragma region //AutoFocus Para
	CSystemData::m_Option.Info.m_nAutoFocusMode = m_comboAutoFocusMode.GetCurSel();

	CSystemData::m_Option.Info.m_nSmart_InMotionCheckMode = m_comboSmart_InMotionCheckMode.GetCurSel();
	m_editSmart_DelayTime.GetWindowText(Str);
	CSystemData::m_Option.Info.m_nSmart_DelayTime = _ttoi(Str);
	m_editSmart_MaxTurnCount.GetWindowText(Str);
	CSystemData::m_Option.Info.m_nSmart_MaxTurnCount = _ttoi(Str);
	m_editSmart_RefTurnCount.GetWindowText(Str);
	CSystemData::m_Option.Info.m_nSmart_RefTurnCount = _ttoi(Str);
	m_editSmart_LimitFocusValue.GetWindowText(Str);
	CSystemData::m_Option.Info.m_dSmart_LimitFocusValue = _ttof(Str);
	m_editSmart_MinFocusValue.GetWindowText(Str);
	CSystemData::m_Option.Info.m_dSmart_MinFocusValue = _ttof(Str);
	m_editSmart_FocusTolerance.GetWindowText(Str);
	CSystemData::m_Option.Info.m_dSmart_FocusTolerance = _ttof(Str);
	CSystemData::m_Option.Info.m_nSmart_ScanMode = m_comboSmart_ScanMode.GetCurSel();
	m_editSmart_MinStepValue.GetWindowText(Str);
	CSystemData::m_Option.Info.m_dSmart_MinStepValue = _ttof(Str);
	m_editSmart_MaxStepValue.GetWindowText(Str);
	CSystemData::m_Option.Info.m_dSmart_MaxStepValue = _ttof(Str);
	m_editSmart_DownDistRange.GetWindowText(Str);
	CSystemData::m_Option.Info.m_dSmart_DownDistRange = _ttof(Str);
	m_editSmart_UpDistRange.GetWindowText(Str);
	CSystemData::m_Option.Info.m_dSmart_UpDistRange = _ttof(Str);

	m_editSmart_Vel.GetWindowText(Str);
	CSystemData::m_Option.Info.m_dSmart_Vel = _ttof(Str);
	m_editSmart_Accel.GetWindowText(Str);
	CSystemData::m_Option.Info.m_dSmart_Accel = _ttof(Str);
	m_editSmart_Decel.GetWindowText(Str);
	CSystemData::m_Option.Info.m_dSmart_Decel = _ttof(Str);
#pragma endregion

	CSystemData::m_Option.Info.m_bAOIAlgorithmSkip = m_checkAOIAlgorithmSkip.GetCheck();
	CSystemData::m_Option.Info.m_bAOIMappingGlassMode = m_checkAOIMappingGlassMode.GetCheck();
	m_editAOI_Z_MappingGlassPos.GetWindowText(Str);
	CSystemData::m_Option.Info.m_dAOI_Z_MappingGlassPos = _ttof(Str);

	CSystemData::m_Option.Info.m_bGlassMode = m_checkGlassMode.GetCheck();

	CSystemData::m_Option.Info.m_bAOIAgingMode = m_checkAOIAgingMode.GetCheck();

	return TRUE;
}

BOOL CSystemOptionSubDlg::SavePara()
{
	if (CheckChangeData() == FALSE)
		return FALSE;

	BOOL bRtn = CSystemData::m_Option.Save();
	if (bRtn == TRUE)
		AfxMessageBox(_T("Save Ok"));
	else
		AfxMessageBox(_T("Save Fail !!"));

	if (CSystemData::m_Option.Info.m_nAutoFocusMode == eAUTO_FOCUS_NORMAL)
		Total_Msg(_T("Set Normal AutoFocus"));
	else
		Total_Msg(_T("Set Smart AutoFocus"));

	return TRUE;
}

void CSystemOptionSubDlg::OnCbnSelchangeComboSystemOptionSmartAutoFocusScanMode()
{
	m_comboSmart_ScanMode.SetCurSel(0); //SmartScan Fixed.
}
