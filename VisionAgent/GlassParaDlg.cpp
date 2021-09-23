// GlassParaDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentDlg.h"
#include "GlassParaDlg.h"
#include "afxdialogex.h"
#include "Data/ModelData.h"


// CGlassParaDlg 대화 상자

IMPLEMENT_DYNAMIC(CGlassParaDlg, CDialogEx)

CGlassParaDlg::CGlassParaDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MODEL_SUB_GLASS_DIALOG, pParent)
{
	Create(IDD_MODEL_SUB_GLASS_DIALOG, pParent);
}

CGlassParaDlg::~CGlassParaDlg()
{
}

void CGlassParaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGlassParaDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CGlassParaDlg 메시지 처리기

BOOL CGlassParaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitCtrl();

	return TRUE;
}

void CGlassParaDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
}

BOOL CGlassParaDlg::InitCtrl()
{
	int i = 0;
	CString Str;

	m_EditGlassSizeX.SubclassDlgItem(IDC_EDIT_MODEL_SUB_GLASS_SIZE_X, this);
	m_EditGlassSizeY.SubclassDlgItem(IDC_EDIT_MODEL_SUB_GLASS_SIZE_Y, this);
	m_EditGlassHeightZ.SubclassDlgItem(IDC_EDIT_MODEL_SUB_GLASS_HEIGHT_Z, this);

	m_EditMarkSizeX.SubclassDlgItem(IDC_EDIT_MODEL_SUB_GLASS_MARK_SIZE_X, this);
	m_EditMarkSizeY.SubclassDlgItem(IDC_EDIT_MODEL_SUB_GLASS_MARK_SIZE_Y, this);

	m_CheckApplyCalib.SubclassDlgItem(IDC_CHECK_GLASS_ALIGN_APPLY_CALIBRATION, this);

	m_BtnRadioPoint[0].SubclassDlgItem(IDC_RADIO_GLASS_ALIGN_2POINT, this);
	m_BtnRadioPoint[1].SubclassDlgItem(IDC_RADIO_GLASS_ALIGN_4POINT, this);

	m_EditMark_LT_X.SubclassDlgItem(IDC_EDIT_MODEL_SUB_GLASS_MARK_LT_X, this);
	m_EditMark_LT_Y.SubclassDlgItem(IDC_EDIT_MODEL_SUB_GLASS_MARK_LT_Y, this);
	m_EditMark_RT_X.SubclassDlgItem(IDC_EDIT_MODEL_SUB_GLASS_MARK_RT_X, this);
	m_EditMark_RT_Y.SubclassDlgItem(IDC_EDIT_MODEL_SUB_GLASS_MARK_RT_Y, this);
	m_EditMark_LB_X.SubclassDlgItem(IDC_EDIT_MODEL_SUB_GLASS_MARK_LB_X, this);
	m_EditMark_LB_Y.SubclassDlgItem(IDC_EDIT_MODEL_SUB_GLASS_MARK_LB_Y, this);
	m_EditMark_RB_X.SubclassDlgItem(IDC_EDIT_MODEL_SUB_GLASS_MARK_RB_X, this);
	m_EditMark_RB_Y.SubclassDlgItem(IDC_EDIT_MODEL_SUB_GLASS_MARK_RB_Y, this);

	m_EditTargetCount.SubclassDlgItem(IDC_EDIT_MODEL_SUB_GLASS_TARGET_COUNT, this);
	m_EditTargetX.SubclassDlgItem(IDC_EDIT_MODEL_SUB_GLASS_TARGET_X, this);
	m_EditTargetY.SubclassDlgItem(IDC_EDIT_MODEL_SUB_GLASS_TARGET_Y, this);
	m_EditTargetT.SubclassDlgItem(IDC_EDIT_MODEL_SUB_GLASS_TARGET_T, this);

	m_EditPreAlignTargetX.SubclassDlgItem(IDC_EDIT_MODEL_SUB_GLASS_PRE_ALIGN_TARGET_X, this);
	m_EditPreAlignTargetY.SubclassDlgItem(IDC_EDIT_MODEL_SUB_GLASS_PRE_ALIGN_TARGET_Y, this);
	m_EditPreAlignTargetT.SubclassDlgItem(IDC_EDIT_MODEL_SUB_GLASS_PRE_ALIGN_TARGET_T, this);

	m_EditPreAlign_Coaxial.SubclassDlgItem(IDC_EDIT_MODEL_SUB_GLASS_BRIGHTNESS_PRE_ALIGN_COAXIAL, this);
	m_EditPreAlign_Ring.SubclassDlgItem(IDC_EDIT_MODEL_SUB_GLASS_BRIGHTNESS_PRE_ALIGN_RING, this);
	m_EditPreAlign_Threshold.SubclassDlgItem(IDC_EDIT_MODEL_SUB_GLASS_BRIGHTNESS_PRE_ALIGN_THRESHOLD, this);

	m_EditReview10x_Coaxial.SubclassDlgItem(IDC_EDIT_MODEL_SUB_GLASS_BRIGHTNESS_REVIEW10X_COAXIAL, this);
	m_EditReview10x_Ring.SubclassDlgItem(IDC_EDIT_MODEL_SUB_GLASS_BRIGHTNESS_REVIEW10X_RING, this);
	m_EditReview10x_Backlight.SubclassDlgItem(IDC_EDIT_MODEL_SUB_GLASS_BRIGHTNESS_REVIEW10X_BACKLIGHT, this);
	m_EditReview10x_Threshold.SubclassDlgItem(IDC_EDIT_MODEL_SUB_GLASS_BRIGHTNESS_REVIEW10X_THRESHOLD, this);

	m_EditReview20x_Coaxial.SubclassDlgItem(IDC_EDIT_MODEL_SUB_GLASS_BRIGHTNESS_REVIEW20X_COAXIAL, this);
	m_EditReview20x_Ring.SubclassDlgItem(IDC_EDIT_MODEL_SUB_GLASS_BRIGHTNESS_REVIEW20X_RING, this);
	m_EditReview20x_Backlight.SubclassDlgItem(IDC_EDIT_MODEL_SUB_GLASS_BRIGHTNESS_REVIEW20X_BACKLIGHT, this);
	m_EditReview20x_Threshold.SubclassDlgItem(IDC_EDIT_MODEL_SUB_GLASS_BRIGHTNESS_REVIEW20X_THRESHOLD, this);

	m_ComboPreAlign_MarkType.SubclassDlgItem(IDC_COMBO_MODEL_GLASS_MARK_TYPE_PRE_ALIGN, this);
	m_ComboPreAlign_FindType.SubclassDlgItem(IDC_COMBO_MODEL_GLASS_FIND_TYPE_PRE_ALIGN, this);

	m_ComboReview10X_LightType.SubclassDlgItem(IDC_COMBO_MODEL_GLASS_LIGHT_TYPE_10X, this);
	m_ComboReview10X_MarkType.SubclassDlgItem(IDC_COMBO_MODEL_GLASS_MARK_TYPE_10X, this);
	m_ComboReview10X_FindType.SubclassDlgItem(IDC_COMBO_MODEL_GLASS_FIND_TYPE_10X, this);
	m_ComboReview10X_FocusType.SubclassDlgItem(IDC_COMBO_MODEL_GLASS_FOCUS_TYPE_10X, this);

	m_ComboReview20X_LightType.SubclassDlgItem(IDC_COMBO_MODEL_GLASS_LIGHT_TYPE_20X, this);
	m_ComboReview20X_MarkType.SubclassDlgItem(IDC_COMBO_MODEL_GLASS_MARK_TYPE_20X, this);
	m_ComboReview20X_FindType.SubclassDlgItem(IDC_COMBO_MODEL_GLASS_FIND_TYPE_20X, this);
	m_ComboReview20X_FocusType.SubclassDlgItem(IDC_COMBO_MODEL_GLASS_FOCUS_TYPE_20X, this);


	return TRUE;
}

BOOL CGlassParaDlg::InitPara()
{
	CString Str = _T("");
	int i = 0;

	Str.Format(_T("%.5f"), CModelData::m_GlassPara.Info.dGlassSizeX);
	m_EditGlassSizeX.SetWindowText(Str);
	Str.Format(_T("%.5f"), CModelData::m_GlassPara.Info.dGlassSizeY);
	m_EditGlassSizeY.SetWindowText(Str);
	Str.Format(_T("%.5f"), CModelData::m_GlassPara.Info.dGlassHeightZ);
	m_EditGlassHeightZ.SetWindowText(Str);

	Str.Format(_T("%.5f"), CModelData::m_GlassPara.Info.dGlassAlignMarkSizeX);
	m_EditMarkSizeX.SetWindowText(Str);
	Str.Format(_T("%.5f"), CModelData::m_GlassPara.Info.dGlassAlignMarkSizeY);
	m_EditMarkSizeY.SetWindowText(Str);
	
	m_CheckApplyCalib.SetCheck(CModelData::m_GlassPara.Info.nGlassAlignApplyCalibCheck);

	if (CModelData::m_GlassPara.Info.nGlassAlignPoint == 0)
	{
		m_BtnRadioPoint[0].SetCheck(TRUE);
		m_BtnRadioPoint[1].SetCheck(FALSE);
	}
	else
	{
		m_BtnRadioPoint[0].SetCheck(FALSE);
		m_BtnRadioPoint[1].SetCheck(TRUE);
	}

	Str.Format(_T("%.5f"), CModelData::m_GlassPara.Info.dGlassAlignMark_LT_X);
	m_EditMark_LT_X.SetWindowText(Str);
	Str.Format(_T("%.5f"), CModelData::m_GlassPara.Info.dGlassAlignMark_LT_Y);
	m_EditMark_LT_Y.SetWindowText(Str);
	Str.Format(_T("%.5f"), CModelData::m_GlassPara.Info.dGlassAlignMark_RT_X);
	m_EditMark_RT_X.SetWindowText(Str);
	Str.Format(_T("%.5f"), CModelData::m_GlassPara.Info.dGlassAlignMark_RT_Y);
	m_EditMark_RT_Y.SetWindowText(Str);
	Str.Format(_T("%.5f"), CModelData::m_GlassPara.Info.dGlassAlignMark_LB_X);
	m_EditMark_LB_X.SetWindowText(Str);
	Str.Format(_T("%.5f"), CModelData::m_GlassPara.Info.dGlassAlignMark_LB_Y);
	m_EditMark_LB_Y.SetWindowText(Str);
	Str.Format(_T("%.5f"), CModelData::m_GlassPara.Info.dGlassAlignMark_RB_X);
	m_EditMark_RB_X.SetWindowText(Str);
	Str.Format(_T("%.5f"), CModelData::m_GlassPara.Info.dGlassAlignMark_RB_Y);
	m_EditMark_RB_Y.SetWindowText(Str);

	Str.Format(_T("%df"), CModelData::m_GlassPara.Info.nGlassMainAlignTargetCount);
	m_EditTargetCount.SetWindowText(Str);
	Str.Format(_T("%.5f"), CModelData::m_GlassPara.Info.dGlassMainAlignTargetX);
	m_EditTargetX.SetWindowText(Str);
	Str.Format(_T("%.5f"), CModelData::m_GlassPara.Info.dGlassMainAlignTargetY);
	m_EditTargetY.SetWindowText(Str);
	Str.Format(_T("%.5f"), CModelData::m_GlassPara.Info.dGlassMainAlignTargetT);
	m_EditTargetT.SetWindowText(Str);

	Str.Format(_T("%.5f"), CModelData::m_GlassPara.Info.dGlassPreAlignTargetX);
	m_EditPreAlignTargetX.SetWindowText(Str);
	Str.Format(_T("%.5f"), CModelData::m_GlassPara.Info.dGlassPreAlignTargetY);
	m_EditPreAlignTargetY.SetWindowText(Str);
	Str.Format(_T("%.5f"), CModelData::m_GlassPara.Info.dGlassPreAlignTargetT);
	m_EditPreAlignTargetT.SetWindowText(Str);

	//Str.Format(_T("%d"), CModelData::m_GlassPara.Info.nBrightnessPreAlignCoaxial);
	//m_EditPreAlign_Coaxial.SetWindowText(Str);
	//Str.Format(_T("%d"), CModelData::m_GlassPara.Info.nBrightnessPreAlignRing);
	//m_EditPreAlign_Ring.SetWindowText(Str);
	//Str.Format(_T("%d"), CModelData::m_GlassPara.Info.nBrightnessPreAlignThreshold);
	//m_EditPreAlign_Threshold.SetWindowText(Str);

	//Str.Format(_T("%d"), CModelData::m_GlassPara.Info.nBrightness10XCoaxial);
	//m_EditReview10x_Coaxial.SetWindowText(Str);
	//Str.Format(_T("%d"), CModelData::m_GlassPara.Info.nBrightness10XRing);
	//m_EditReview10x_Ring.SetWindowText(Str);
	//Str.Format(_T("%d"), CModelData::m_GlassPara.Info.nBrightness10XBackLight);
	//m_EditReview10x_Backlight.SetWindowText(Str);
	//Str.Format(_T("%d"), CModelData::m_GlassPara.Info.nBrightness10XThreshold);
	//m_EditReview10x_Threshold.SetWindowText(Str);

	//Str.Format(_T("%d"), CModelData::m_GlassPara.Info.nBrightness20XCoaxial);
	//m_EditReview20x_Coaxial.SetWindowText(Str);
	//Str.Format(_T("%d"), CModelData::m_GlassPara.Info.nBrightness20XRing);
	//m_EditReview20x_Ring.SetWindowText(Str);
	//Str.Format(_T("%d"), CModelData::m_GlassPara.Info.nBrightness20XBackLight);
	//m_EditReview20x_Backlight.SetWindowText(Str);
	//Str.Format(_T("%d"), CModelData::m_GlassPara.Info.nBrightness20XThreshold);
	//m_EditReview20x_Threshold.SetWindowText(Str);

	//m_ComboPreAlign_MarkType.SetCurSel(CModelData::m_GlassPara.Info.nBrightnessPreAlignMarkSelect);
	//m_ComboPreAlign_FindType.SetCurSel(CModelData::m_GlassPara.Info.nBrightnessPreAlignFindSelect);

	//m_ComboReview10X_LightType.SetCurSel(CModelData::m_GlassPara.Info.nBrightness10XLightSelect);
	//m_ComboReview10X_MarkType.SetCurSel(CModelData::m_GlassPara.Info.nBrightness10XMarkSelect);
	//m_ComboReview10X_FindType.SetCurSel(CModelData::m_GlassPara.Info.nBrightness10XFindSelect);
	//m_ComboReview10X_FocusType.SetCurSel(CModelData::m_GlassPara.Info.nBrightness10XFocusSelect);

	//m_ComboReview20X_LightType.SetCurSel(CModelData::m_GlassPara.Info.nBrightness20XLightSelect);
	//m_ComboReview20X_MarkType.SetCurSel(CModelData::m_GlassPara.Info.nBrightness20XMarkSelect);
	//m_ComboReview20X_FindType.SetCurSel(CModelData::m_GlassPara.Info.nBrightness20XFindSelect);
	//m_ComboReview20X_FocusType.SetCurSel(CModelData::m_GlassPara.Info.nBrightness20XFocusSelect);

	return TRUE;
}

BOOL CGlassParaDlg::CheckChangeData()
{
	CString Str = _T("");

	m_EditGlassSizeX.GetWindowText(Str);
	CModelData::m_GlassPara.Info.dGlassSizeX = _ttof(Str);
	m_EditGlassSizeY.GetWindowText(Str);
	CModelData::m_GlassPara.Info.dGlassSizeY = _ttof(Str);
	m_EditGlassHeightZ.GetWindowText(Str);
	CModelData::m_GlassPara.Info.dGlassHeightZ = _ttof(Str);	

	m_EditMarkSizeX.GetWindowText(Str);
	CModelData::m_GlassPara.Info.dGlassAlignMarkSizeX = _ttof(Str);
	m_EditMarkSizeY.GetWindowText(Str);
	CModelData::m_GlassPara.Info.dGlassAlignMarkSizeY = _ttof(Str);
	
	CModelData::m_GlassPara.Info.nGlassAlignApplyCalibCheck = m_CheckApplyCalib.GetCheck();

	CModelData::m_GlassPara.Info.nGlassAlignPoint = m_BtnRadioPoint[0].GetCheck();

	m_EditMark_LT_X.GetWindowText(Str);
	CModelData::m_GlassPara.Info.dGlassAlignMark_LT_X = _ttof(Str);
	m_EditMark_LT_Y.GetWindowText(Str);
	CModelData::m_GlassPara.Info.dGlassAlignMark_LT_Y = _ttof(Str);
	m_EditMark_RT_X.GetWindowText(Str);
	CModelData::m_GlassPara.Info.dGlassAlignMark_RT_X = _ttof(Str);
	m_EditMark_RT_Y.GetWindowText(Str);
	CModelData::m_GlassPara.Info.dGlassAlignMark_RT_Y = _ttof(Str);
	m_EditMark_LB_X.GetWindowText(Str);
	CModelData::m_GlassPara.Info.dGlassAlignMark_LB_X = _ttof(Str);
	m_EditMark_LB_Y.GetWindowText(Str);
	CModelData::m_GlassPara.Info.dGlassAlignMark_LB_Y = _ttof(Str);
	m_EditMark_RB_X.GetWindowText(Str);
	CModelData::m_GlassPara.Info.dGlassAlignMark_RB_X = _ttof(Str);
	m_EditMark_RB_Y.GetWindowText(Str);
	CModelData::m_GlassPara.Info.dGlassAlignMark_RB_Y = _ttof(Str);	

	m_EditTargetCount.GetWindowText(Str);
	CModelData::m_GlassPara.Info.nGlassMainAlignTargetCount = _ttoi(Str);
	m_EditTargetX.GetWindowText(Str);
	CModelData::m_GlassPara.Info.dGlassMainAlignTargetX = _ttof(Str);
	m_EditTargetY.GetWindowText(Str);
	CModelData::m_GlassPara.Info.dGlassMainAlignTargetY = _ttof(Str);
	m_EditTargetT.GetWindowText(Str);
	CModelData::m_GlassPara.Info.dGlassMainAlignTargetT = _ttof(Str);

	m_EditPreAlignTargetX.GetWindowText(Str);
	CModelData::m_GlassPara.Info.dGlassPreAlignTargetX = _ttof(Str);
	m_EditPreAlignTargetY.GetWindowText(Str);
	CModelData::m_GlassPara.Info.dGlassPreAlignTargetY = _ttof(Str);
	m_EditPreAlignTargetT.GetWindowText(Str);
	CModelData::m_GlassPara.Info.dGlassPreAlignTargetT = _ttof(Str);

	m_EditPreAlign_Coaxial.GetWindowText(Str);
	CModelData::m_GlassPara.Info.nBrightnessPreAlignCoaxial = _ttoi(Str); //KJT 20210727
	m_EditPreAlign_Ring.GetWindowText(Str);
	CModelData::m_GlassPara.Info.nBrightnessPreAlignRing = _ttoi(Str); //KJT 20210727
	m_EditPreAlign_Threshold.GetWindowText(Str);
	CModelData::m_GlassPara.Info.nBrightnessPreAlignThreshold = _ttoi(Str);	//KJT 20210727

	m_EditReview10x_Coaxial.GetWindowText(Str);
	CModelData::m_GlassPara.Info.nBrightness10XCoaxial = _ttoi(Str); //KJT 20210727
	m_EditReview10x_Ring.GetWindowText(Str);
	CModelData::m_GlassPara.Info.nBrightness10XRing = _ttoi(Str); //KJT 20210727
	m_EditReview10x_Backlight.GetWindowText(Str);
	CModelData::m_GlassPara.Info.nBrightness10XBackLight = _ttoi(Str); //KJT 20210727
	m_EditReview10x_Threshold.GetWindowText(Str);
	CModelData::m_GlassPara.Info.nBrightness10XThreshold = _ttoi(Str); //KJT 20210727

	m_EditReview20x_Coaxial.GetWindowText(Str);
	CModelData::m_GlassPara.Info.nBrightness20XCoaxial = _ttoi(Str); //KJT 20210727
	m_EditReview20x_Ring.GetWindowText(Str);
	CModelData::m_GlassPara.Info.nBrightness20XRing = _ttoi(Str); //KJT 20210727
	m_EditReview20x_Backlight.GetWindowText(Str);
	CModelData::m_GlassPara.Info.nBrightness20XBackLight = _ttoi(Str); //KJT 20210727
	m_EditReview20x_Threshold.GetWindowText(Str);
	CModelData::m_GlassPara.Info.nBrightness20XThreshold = _ttoi(Str); //KJT 20210727

	CModelData::m_GlassPara.Info.nBrightnessPreAlignMarkSelect = m_ComboPreAlign_MarkType.GetCurSel();
	CModelData::m_GlassPara.Info.nBrightnessPreAlignFindSelect = m_ComboPreAlign_FindType.GetCurSel();

	CModelData::m_GlassPara.Info.nBrightness10XLightSelect = m_ComboReview10X_LightType.GetCurSel();
	CModelData::m_GlassPara.Info.nBrightness10XMarkSelect = m_ComboReview10X_MarkType.GetCurSel();
	CModelData::m_GlassPara.Info.nBrightness10XFindSelect = m_ComboReview10X_FindType.GetCurSel();
	CModelData::m_GlassPara.Info.nBrightness10XFocusSelect = m_ComboReview10X_FocusType.GetCurSel();

	CModelData::m_GlassPara.Info.nBrightness20XLightSelect = m_ComboReview20X_LightType.GetCurSel();
	CModelData::m_GlassPara.Info.nBrightness20XMarkSelect = m_ComboReview20X_MarkType.GetCurSel();
	CModelData::m_GlassPara.Info.nBrightness20XFindSelect = m_ComboReview20X_FindType.GetCurSel();
	CModelData::m_GlassPara.Info.nBrightness20XFocusSelect = m_ComboReview20X_FocusType.GetCurSel();

	return TRUE;
}

BOOL CGlassParaDlg::SavePara()
{
	CheckChangeData();

	BOOL bRtn = CModelData::m_GlassPara.Save();
	if (bRtn == TRUE)
		AfxMessageBox(_T("Save Ok"));
	else
		AfxMessageBox(_T("Save Fail !!"));

	return TRUE;
}

void CGlassParaDlg::OnShowWindow(BOOL bShow, UINT nStatus)
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
