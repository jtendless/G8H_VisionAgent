// InspectionParaDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentDlg.h"
#include "InspectionParaDlg.h"
#include "afxdialogex.h"


// CInspectionParaDlg 대화 상자

IMPLEMENT_DYNAMIC(CInspectionParaDlg, CDialogEx)

CInspectionParaDlg::CInspectionParaDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MODEL_SUB_INSPECTION_PARA_DIALOG, pParent)
{
	Create(IDD_MODEL_SUB_INSPECTION_PARA_DIALOG, pParent);
}

CInspectionParaDlg::~CInspectionParaDlg()
{
}

void CInspectionParaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CInspectionParaDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_COMBO_INSPECTION_PARA_DIV_COUNT_XY, &CInspectionParaDlg::OnCbnSelchangeComboInspectionParaDivCountXy)
END_MESSAGE_MAP()


// CInspectionParaDlg 메시지 처리기

BOOL CInspectionParaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitCtrl();

	return TRUE;
}

void CInspectionParaDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
}

BOOL CInspectionParaDlg::InitCtrl()
{
	m_comboPPADivXY.SubclassDlgItem(IDC_COMBO_INSPECTION_PARA_DIV_COUNT_XY, this);
	m_comboPPADivXY.ResetContent();
	m_comboPPADivXY.AddString(_T("1x1"));
	m_comboPPADivXY.AddString(_T("2x2"));
	m_comboPPADivXY.AddString(_T("3x3"));
	m_comboPPADivXY.SetCurSel(0);

	m_editDivX.SubclassDlgItem(IDC_EDIT_INSPECTION_PARA_DIV_X, this);
	m_editDivY.SubclassDlgItem(IDC_EDIT_INSPECTION_PARA_DIV_Y, this);
	m_CheckOnlyUnloadingMode.SubclassDlgItem(IDC_CHECK_INSPECTION_PARA_ONLY_UNLOADING_MODE, this);
	m_checkOnlyUnloadingModePreAlignUse.SubclassDlgItem(IDC_CHECK_INSPECTION_PARA_ONLY_UNLOADING_MODE_PRE_ALIGN_USE, this);
	m_CheckTPUse.SubclassDlgItem(IDC_CHECK_INSPECTION_PARA_MEASURE_HALF_EDGE_HOLE_FLOW_USE, this);
	m_CheckSWAlignFlowUse.SubclassDlgItem(IDC_CHECK_INSPECTION_PARA_SW_ALIGN_FLOW_USE, this); //KJT 20210315
	m_CheckPPAUse.SubclassDlgItem(IDC_CHECK_INSPECTION_PARA_PPA_FLOW_USE, this);
	m_CheckAOIUse.SubclassDlgItem(IDC_CHECK_INSPECTION_PARA_AOI_FLOW_USE, this);
	m_CheckAOIReviewUse.SubclassDlgItem(IDC_CHECK_INSPECTION_PARA_AOI_REVIEW_FLOW_USE, this);
	m_Check3dFlowUse.SubclassDlgItem(IDC_CHECK_INSPECTION_PARA_3D_FLOW_USE, this);
	
	m_comboPPAAlignMethod.SubclassDlgItem(IDC_COMBO_INSPECTION_PARA_PPA_ALIGN_METHOD, this);
	m_comboPPAAlignMethod.ResetContent();
	m_comboPPAAlignMethod.AddString(_T("None"));
	m_comboPPAAlignMethod.AddString(_T("Interpolation"));
	m_comboPPAAlignMethod.AddString(_T("X-Y-T"));
	m_comboPPAAlignMethod.SetCurSel(0);
	m_comboEdgeAlignMethod.SubclassDlgItem(IDC_COMBO_INSPECTION_PARA_EDGE_ALIGN_METHOD, this);
	m_comboEdgeAlignMethod.ResetContent();
	m_comboEdgeAlignMethod.AddString(_T("Top Y"));
	m_comboEdgeAlignMethod.AddString(_T("Vertical Y"));
	m_comboEdgeAlignMethod.AddString(_T("Individual Y"));
	m_comboEdgeAlignMethod.SetCurSel(0);

	//m_editDarkThreshold.SubclassDlgItem(IDC_EDIT_INSPECTION_PARA_AOI_DARK_THRESHOLD, this);
	//m_editBrightThreshold.SubclassDlgItem(IDC_EDIT_INSPECTION_PARA_AOI_BRIGHT_THRESHOLD, this);
	m_editAOIDefectSizeMin.SubclassDlgItem(IDC_EDIT_INSPECTION_PARA_AOI_DEFECT_SIZE_MIN, this);
	m_editAOIReviewBacklight.SubclassDlgItem(IDC_EDIT_INSPECTION_PARA_AOI_REVIEW_BACKLIGHT, this);

	m_comboPPAFocusType.SubclassDlgItem(IDC_COMBO_INSPECTION_PARA_PPA_FOCUS_TYPE, this);
	m_comboPPAFocusType.ResetContent();
	m_comboPPAFocusType.AddString(_T("Laser Focus"));
	m_comboPPAFocusType.AddString(_T("Image Focus"));
	m_comboPPAFocusType.AddString(_T("Both")); //Laser/Image Focus
	m_comboPPAFocusType.SetCurSel(0);

	m_comboPPATrackingType.SubclassDlgItem(IDC_COMBO_INSPECTION_PARA_PPA_TRACKING_TYPE, this);
	m_comboPPATrackingType.ResetContent();
	m_comboPPATrackingType.AddString(_T("None"));
	m_comboPPATrackingType.AddString(_T("Motion"));
	m_comboPPATrackingType.AddString(_T("Image"));
	m_comboPPATrackingType.SetCurSel(0);

	m_CheckInspectionStageVacuumOn.SubclassDlgItem(IDC_CHECK_INSPECTION_PARA_INSPECTION_STAGE_VACUUM_ON, this);
	m_CheckAppendixSensorUse.SubclassDlgItem(IDC_CHECK_INSPECTION_PARA_APPENDIX_VACUUM_SENSOR_USE, this);

	m_comboAlignDataUseMode.SubclassDlgItem(IDC_COMBO_INSPECTION_PARA_ALIGN_DATA_USE_MODE, this);
	m_comboAlignDataUseMode.ResetContent();
	m_comboAlignDataUseMode.AddString(_T("SW_Align"));
	m_comboAlignDataUseMode.AddString(_T("XYT_Align"));
	m_comboAlignDataUseMode.SetCurSel(0);

	m_comboMeasureCameraMode.SubclassDlgItem(IDC_COMBO_INSPECTION_PARA_MEASURE_CAMERA_MODE, this);
	m_comboMeasureCameraMode.ResetContent();
	m_comboMeasureCameraMode.AddString(_T("10X"));
	m_comboMeasureCameraMode.AddString(_T("20X"));	
	m_comboMeasureCameraMode.SetCurSel(0);

	m_comboStickTensionUseMode.SubclassDlgItem(IDC_COMBO_INSPECTION_PARA_STICK_TENSION_USE_MODE, this);
	m_comboStickTensionUseMode.ResetContent();
	m_comboStickTensionUseMode.AddString(_T("Tension_No"));
#ifndef GRIPPER_0
	m_comboStickTensionUseMode.AddString(_T("Tension_Once"));
	m_comboStickTensionUseMode.AddString(_T("Tension_Align"));
#endif
	m_comboStickTensionUseMode.SetCurSel(0);

	m_comboMaterialParaUseMode.SubclassDlgItem(IDC_COMBO_INSPECTION_PARA_MATERIAL_PARA_USE_MODE, this);
	m_comboMaterialParaUseMode.ResetContent();
	m_comboMaterialParaUseMode.AddString(_T("Normal Para"));
	m_comboMaterialParaUseMode.AddString(_T("At Para"));
	m_comboMaterialParaUseMode.SetCurSel(0);

	m_checkLoaderFinger_Stick1.SubclassDlgItem(IDC_CHECK_INSPECTION_PARA_LOADER_FINGER_USE_STICK_1, this);
	m_checkLoaderFinger_Stick2.SubclassDlgItem(IDC_CHECK_INSPECTION_PARA_LOADER_FINGER_USE_STICK_2, this);
	m_checkLoaderFinger_Stick3.SubclassDlgItem(IDC_CHECK_INSPECTION_PARA_LOADER_FINGER_USE_STICK_3, this);
	m_checkLoaderFinger_Stick4.SubclassDlgItem(IDC_CHECK_INSPECTION_PARA_LOADER_FINGER_USE_STICK_4, this);
	m_checkLoaderFinger_Stick5.SubclassDlgItem(IDC_CHECK_INSPECTION_PARA_LOADER_FINGER_USE_STICK_5, this);

	m_checkLoaderFinger_Paper1.SubclassDlgItem(IDC_CHECK_INSPECTION_PARA_LOADER_FINGER_USE_PAPER_1, this);
	m_checkLoaderFinger_Paper2.SubclassDlgItem(IDC_CHECK_INSPECTION_PARA_LOADER_FINGER_USE_PAPER_2, this);
	m_checkLoaderFinger_Paper3.SubclassDlgItem(IDC_CHECK_INSPECTION_PARA_LOADER_FINGER_USE_PAPER_3, this);
	m_checkLoaderFinger_Paper4.SubclassDlgItem(IDC_CHECK_INSPECTION_PARA_LOADER_FINGER_USE_PAPER_4, this);
	m_checkLoaderFinger_Paper5.SubclassDlgItem(IDC_CHECK_INSPECTION_PARA_LOADER_FINGER_USE_PAPER_5, this);

	m_checkUnloaderFinger_Stick1.SubclassDlgItem(IDC_CHECK_INSPECTION_PARA_UNLOADER_FINGER_USE_STICK_1, this);
	m_checkUnloaderFinger_Stick2.SubclassDlgItem(IDC_CHECK_INSPECTION_PARA_UNLOADER_FINGER_USE_STICK_2, this);
	m_checkUnloaderFinger_Stick3.SubclassDlgItem(IDC_CHECK_INSPECTION_PARA_UNLOADER_FINGER_USE_STICK_3, this);
	m_checkUnloaderFinger_Stick4.SubclassDlgItem(IDC_CHECK_INSPECTION_PARA_UNLOADER_FINGER_USE_STICK_4, this);
	m_checkUnloaderFinger_Stick5.SubclassDlgItem(IDC_CHECK_INSPECTION_PARA_UNLOADER_FINGER_USE_STICK_5, this);

	m_checkPaperUnloaderFinger_1.SubclassDlgItem(IDC_CHECK_INSPECTION_PARA_PAPER_UNLOADER_FINGER_USE_1, this);
	m_checkPaperUnloaderFinger_2.SubclassDlgItem(IDC_CHECK_INSPECTION_PARA_PAPER_UNLOADER_FINGER_USE_2, this);
	m_checkPaperUnloaderFinger_3_4.SubclassDlgItem(IDC_CHECK_INSPECTION_PARA_PAPER_UNLOADER_FINGER_USE_3_4, this);
	m_checkPaperUnloaderFinger_5.SubclassDlgItem(IDC_CHECK_INSPECTION_PARA_PAPER_UNLOADER_FINGER_USE_5, this);
	m_checkPaperUnloaderFinger_6.SubclassDlgItem(IDC_CHECK_INSPECTION_PARA_PAPER_UNLOADER_FINGER_USE_6, this);

	m_checkMappingDataUse.SubclassDlgItem(IDC_CHECK_INSPECTION_PARA_MAPPING_DATA_USE, this);
	m_checkAlignDataUse.SubclassDlgItem(IDC_CHECK_INSPECTION_PARA_ALIGN_DATA_USE, this);
	m_checkSwAlignVerifyUse.SubclassDlgItem(IDC_CHECK_INSPECTION_PARA_SW_ALIGN_VERIFY_USE, this);
	m_checkMeasureCornerR.SubclassDlgItem(IDC_CHECK_INSPECTION_PARA_MEASURE_CORNER_R, this);

	//KJT 20210315
	m_comboAOIScanSpeedLevel.SubclassDlgItem(IDC_COMBO_INSPECTION_PARA_AOI_SCAN_SPEED_LEVEL, this);
	m_comboAOIScanSpeedLevel.ResetContent();
	m_comboAOIScanSpeedLevel.AddString(_T("50"));
	m_comboAOIScanSpeedLevel.AddString(_T("100"));
	m_comboAOIScanSpeedLevel.AddString(_T("150"));
	m_comboAOIScanSpeedLevel.AddString(_T("200"));
	m_comboAOIScanSpeedLevel.AddString(_T("Auto"));
	m_comboAOIScanSpeedLevel.SetCurSel(0);

	// KJT 20210525
	m_comboDivX.SubclassDlgItem(IDC_COMBO_PPA_PARA_DIV_X2, this);
	m_comboDivX.ResetContent();
	m_comboDivX.AddString(_T("1"));
	m_comboDivX.AddString(_T("2"));
	m_comboDivX.AddString(_T("3"));
	m_comboDivX.AddString(_T("4"));
	m_comboDivX.AddString(_T("5"));
	m_comboDivX.SetCurSel(eDiv_3);

	m_comboDivY.SubclassDlgItem(IDC_COMBO_PPA_PARA_DIV_Y2, this);
	m_comboDivY.ResetContent();
	m_comboDivY.AddString(_T("1"));
	m_comboDivY.AddString(_T("2"));
	m_comboDivY.AddString(_T("3"));
	m_comboDivY.AddString(_T("4"));
	m_comboDivY.AddString(_T("5"));
	m_comboDivY.SetCurSel(eDiv_3);

	m_comboSlotQuantityXY.SubclassDlgItem(IDC_COMBO_PPA_PARA_SLOT_QUANTITY_XY2, this);
	m_comboSlotQuantityXY.ResetContent();
	m_comboSlotQuantityXY.AddString(_T("1x1"));
	m_comboSlotQuantityXY.AddString(_T("3x3"));
	m_comboSlotQuantityXY.AddString(_T("5x5"));
	m_comboSlotQuantityXY.SetCurSel(eQuantity_3X3);

	m_comboBoxStickExistType.SubclassDlgItem(IDC_COMBO_INSPECTION_PARA_BOX_STICK_EXIST_TYPE, this);
	m_comboBoxStickExistType.ResetContent();
	m_comboBoxStickExistType.AddString(_T("Stick+Paper+Paper+Stick"));
	m_comboBoxStickExistType.AddString(_T("Stick+Paper+Stick"));
	m_comboBoxStickExistType.AddString(_T("Stick+Stick"));
	m_comboBoxStickExistType.SetCurSel(0);

	return TRUE;
}

BOOL CInspectionParaDlg::InitPara()
{
	//m_comboPPADivXY.SetCurSel(CModelData::m_InspectionPara.Info.nDivCountXY);
	//m_editDivX.SetWindowText(_ToStr(_T("%d"), CModelData::m_InspectionPara.Info.nDivX));
	//m_editDivY.SetWindowText(_ToStr(_T("%d"), CModelData::m_InspectionPara.Info.nDivY));
	m_CheckOnlyUnloadingMode.SetCheck(CModelData::m_InspectionPara.Info.bOnlyUnloadingMode); //KJT 20210406
	m_CheckTPUse.SetCheck(CModelData::m_InspectionPara.Info.bTPUse); //KJT 20210406
	m_CheckSWAlignFlowUse.SetCheck(CModelData::m_InspectionPara.Info.bSWAlignFlowUse); //KJT 20210315
	m_CheckPPAUse.SetCheck(CModelData::m_InspectionPara.Info.bPPAUse);
	m_CheckAOIUse.SetCheck(CModelData::m_InspectionPara.Info.bAOIUse);
	m_CheckAOIReviewUse.SetCheck(CModelData::m_InspectionPara.Info.bAOIReviewUse);
	m_Check3dFlowUse.SetCheck(CModelData::m_InspectionPara.Info.b3dFlowUse); //KJT 20210207
	m_comboPPAAlignMethod.SetCurSel(CModelData::m_InspectionPara.Info.nPPAAlignMethod);
	m_comboEdgeAlignMethod.SetCurSel(CModelData::m_InspectionPara.Info.nEdgeAlignMethod);
	//m_editDarkThreshold.SetWindowText(_ToStr(_T("%d"), CModelData::m_InspectionPara.Info.nDarkThreshold));
	//m_editBrightThreshold.SetWindowText(_ToStr(_T("%d"), CModelData::m_InspectionPara.Info.nBrightThreshold));
	m_editAOIDefectSizeMin.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_InspectionPara.Info.dAOIDefectSizeMin));
	m_editAOIReviewBacklight.SetWindowText(_ToStr(_T("%d"), CModelData::m_InspectionPara.Info.nAOIReviewBacklight));
	m_comboPPAFocusType.SetCurSel(CModelData::m_InspectionPara.Info.nPPAFocusType);
	m_comboPPATrackingType.SetCurSel(CModelData::m_InspectionPara.Info.nPPATrackingType);
	m_CheckInspectionStageVacuumOn.SetCheck(CModelData::m_InspectionPara.Info.bInspectionStageVacuumOn);
	m_CheckAppendixSensorUse.SetCheck(CModelData::m_InspectionPara.Info.bAppendixSensorUse);

	m_comboAlignDataUseMode.SetCurSel(CModelData::m_InspectionPara.Info.nAlignDataUseMode);
	m_comboMeasureCameraMode.SetCurSel(CModelData::m_InspectionPara.Info.nMeasureCameraMode);
	m_comboStickTensionUseMode.SetCurSel(CModelData::m_InspectionPara.Info.nStickTensionUseMode);
	//m_comboMaterialParaUseMode.SetCurSel(CModelData::m_InspectionPara.Info.nStickTensionUseMode);

	m_checkLoaderFinger_Stick1.SetCheck(CModelData::m_InspectionPara.Info.bLoaderFingerUse_Stick1);
	m_checkLoaderFinger_Stick2.SetCheck(CModelData::m_InspectionPara.Info.bLoaderFingerUse_Stick2);
	m_checkLoaderFinger_Stick3.SetCheck(CModelData::m_InspectionPara.Info.bLoaderFingerUse_Stick3);
	m_checkLoaderFinger_Stick4.SetCheck(CModelData::m_InspectionPara.Info.bLoaderFingerUse_Stick4);
	m_checkLoaderFinger_Stick5.SetCheck(CModelData::m_InspectionPara.Info.bLoaderFingerUse_Stick5);

	m_checkLoaderFinger_Paper1.SetCheck(CModelData::m_InspectionPara.Info.bLoaderFingerUse_Paper1);
	m_checkLoaderFinger_Paper2.SetCheck(CModelData::m_InspectionPara.Info.bLoaderFingerUse_Paper2);
	m_checkLoaderFinger_Paper3.SetCheck(CModelData::m_InspectionPara.Info.bLoaderFingerUse_Paper3);
	m_checkLoaderFinger_Paper4.SetCheck(CModelData::m_InspectionPara.Info.bLoaderFingerUse_Paper4);
	m_checkLoaderFinger_Paper5.SetCheck(CModelData::m_InspectionPara.Info.bLoaderFingerUse_Paper5);

	m_checkUnloaderFinger_Stick1.SetCheck(CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick1);
	m_checkUnloaderFinger_Stick2.SetCheck(CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick2);
	m_checkUnloaderFinger_Stick3.SetCheck(CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick3);
	m_checkUnloaderFinger_Stick4.SetCheck(CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick4);
	m_checkUnloaderFinger_Stick5.SetCheck(CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick5);

	m_checkPaperUnloaderFinger_1.SetCheck(CModelData::m_InspectionPara.Info.bPaperUnloaderFingerUse_1);
	m_checkPaperUnloaderFinger_2.SetCheck(CModelData::m_InspectionPara.Info.bPaperUnloaderFingerUse_2);
	m_checkPaperUnloaderFinger_3_4.SetCheck(CModelData::m_InspectionPara.Info.bPaperUnloaderFingerUse_3_4);
	m_checkPaperUnloaderFinger_5.SetCheck(CModelData::m_InspectionPara.Info.bPaperUnloaderFingerUse_5);
	m_checkPaperUnloaderFinger_6.SetCheck(CModelData::m_InspectionPara.Info.bPaperUnloaderFingerUse_6);

	m_checkMappingDataUse.SetCheck(CModelData::m_InspectionPara.Info.bMappingDataUse);
	m_checkAlignDataUse.SetCheck(CModelData::m_InspectionPara.Info.bAlignDataUse);
	m_checkSwAlignVerifyUse.SetCheck(CModelData::m_InspectionPara.Info.bSwAlignVerifyUse); //KJT 20210428
	m_checkMeasureCornerR.SetCheck(CModelData::m_InspectionPara.Info.bMeasureCornerR);

	m_comboAOIScanSpeedLevel.SetCurSel(CModelData::m_InspectionPara.Info.nAOIScanSpeedLevel); //KJT 20210315
	//KJT 20210525
	m_comboDivX.SetCurSel(CModelData::m_PpaPara.Info.nDivX);
	m_comboDivY.SetCurSel(CModelData::m_PpaPara.Info.nDivY);
	m_comboSlotQuantityXY.SetCurSel(CModelData::m_PpaPara.Info.nSlotQuantityXY);

	m_comboBoxStickExistType.SetCurSel(CModelData::m_InspectionPara.Info.nBoxStickExistType);

	m_checkOnlyUnloadingModePreAlignUse.SetCheck(CModelData::m_InspectionPara.Info.bOnlyUnloadModePreAlignUse);

	return TRUE;
}

BOOL CInspectionParaDlg::CheckChangeData()
{
	CString Str = _T("");

	CModelData::m_InspectionPara.Info.bOnlyUnloadingMode = m_CheckOnlyUnloadingMode.GetCheck(); //KJT 20210406
	CModelData::m_InspectionPara.Info.bTPUse = m_CheckTPUse.GetCheck(); //KJT 20210406
	CModelData::m_InspectionPara.Info.bSWAlignFlowUse = m_CheckSWAlignFlowUse.GetCheck(); //KJT 20210315
	CModelData::m_InspectionPara.Info.bPPAUse = m_CheckPPAUse.GetCheck();
	CModelData::m_InspectionPara.Info.bAOIUse = m_CheckAOIUse.GetCheck();
	CModelData::m_InspectionPara.Info.bAOIReviewUse = m_CheckAOIReviewUse.GetCheck();
	CModelData::m_InspectionPara.Info.b3dFlowUse = m_Check3dFlowUse.GetCheck(); //KJT 20210207
	CModelData::m_InspectionPara.Info.nPPAAlignMethod = m_comboPPAAlignMethod.GetCurSel();
	CModelData::m_InspectionPara.Info.nEdgeAlignMethod = m_comboEdgeAlignMethod.GetCurSel();
	//m_editDarkThreshold.GetWindowText(Str);
	//CModelData::m_InspectionPara.Info.nDarkThreshold = _ttoi(Str);
	//m_editBrightThreshold.GetWindowText(Str);
	//CModelData::m_InspectionPara.Info.nBrightThreshold = _ttoi(Str);
	m_editAOIDefectSizeMin.GetWindowText(Str);
	CModelData::m_InspectionPara.Info.dAOIDefectSizeMin = _ttof(Str);
	m_editAOIReviewBacklight.GetWindowText(Str);
	CModelData::m_InspectionPara.Info.nAOIReviewBacklight = _ttoi(Str);
	CModelData::m_InspectionPara.Info.nPPAFocusType = m_comboPPAFocusType.GetCurSel();
	CModelData::m_InspectionPara.Info.nPPATrackingType = m_comboPPATrackingType.GetCurSel();
	CModelData::m_InspectionPara.Info.bInspectionStageVacuumOn = m_CheckInspectionStageVacuumOn.GetCheck();
	CModelData::m_InspectionPara.Info.bAppendixSensorUse = m_CheckAppendixSensorUse.GetCheck();

	CModelData::m_InspectionPara.Info.nAlignDataUseMode = m_comboAlignDataUseMode.GetCurSel();
	CModelData::m_InspectionPara.Info.nMeasureCameraMode = m_comboMeasureCameraMode.GetCurSel();
#ifndef GRIPPER_0
	CModelData::m_InspectionPara.Info.nStickTensionUseMode = m_comboStickTensionUseMode.GetCurSel();
	//CModelData::m_InspectionPara.Info.nStickTensionUseMode = m_comboMaterialParaUseMode.GetCurSel();
#else
	CModelData::m_InspectionPara.Info.nStickTensionUseMode = eSTICK_TENSION_NO;
#endif

	CModelData::m_InspectionPara.Info.bLoaderFingerUse_Stick1 = m_checkLoaderFinger_Stick1.GetCheck();
	CModelData::m_InspectionPara.Info.bLoaderFingerUse_Stick2 = m_checkLoaderFinger_Stick2.GetCheck();
	CModelData::m_InspectionPara.Info.bLoaderFingerUse_Stick3 = m_checkLoaderFinger_Stick3.GetCheck();
	CModelData::m_InspectionPara.Info.bLoaderFingerUse_Stick4 = m_checkLoaderFinger_Stick4.GetCheck();
	CModelData::m_InspectionPara.Info.bLoaderFingerUse_Stick5 = m_checkLoaderFinger_Stick5.GetCheck();

	CModelData::m_InspectionPara.Info.bLoaderFingerUse_Paper1 = m_checkLoaderFinger_Paper1.GetCheck();
	CModelData::m_InspectionPara.Info.bLoaderFingerUse_Paper2 = m_checkLoaderFinger_Paper2.GetCheck();
	CModelData::m_InspectionPara.Info.bLoaderFingerUse_Paper3 = m_checkLoaderFinger_Paper3.GetCheck();
	CModelData::m_InspectionPara.Info.bLoaderFingerUse_Paper4 = m_checkLoaderFinger_Paper4.GetCheck();
	CModelData::m_InspectionPara.Info.bLoaderFingerUse_Paper5 = m_checkLoaderFinger_Paper5.GetCheck();

	CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick1 = m_checkUnloaderFinger_Stick1.GetCheck();
	CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick2 = m_checkUnloaderFinger_Stick2.GetCheck();
	CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick3 = m_checkUnloaderFinger_Stick3.GetCheck();
	CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick4 = m_checkUnloaderFinger_Stick4.GetCheck();
	CModelData::m_InspectionPara.Info.bUnloaderFingerUse_Stick5 = m_checkUnloaderFinger_Stick5.GetCheck();

	CModelData::m_InspectionPara.Info.bPaperUnloaderFingerUse_1 = m_checkPaperUnloaderFinger_1.GetCheck();
	CModelData::m_InspectionPara.Info.bPaperUnloaderFingerUse_2 = m_checkPaperUnloaderFinger_2.GetCheck();
	CModelData::m_InspectionPara.Info.bPaperUnloaderFingerUse_3_4 = m_checkPaperUnloaderFinger_3_4.GetCheck();
	CModelData::m_InspectionPara.Info.bPaperUnloaderFingerUse_5 = m_checkPaperUnloaderFinger_5.GetCheck();
	CModelData::m_InspectionPara.Info.bPaperUnloaderFingerUse_6 = m_checkPaperUnloaderFinger_6.GetCheck();

	CModelData::m_InspectionPara.Info.bMappingDataUse = m_checkMappingDataUse.GetCheck();
	CModelData::m_InspectionPara.Info.bAlignDataUse = m_checkAlignDataUse.GetCheck();
	CModelData::m_InspectionPara.Info.bSwAlignVerifyUse = m_checkSwAlignVerifyUse.GetCheck(); //KJT 20210428
	CModelData::m_InspectionPara.Info.bMeasureCornerR = m_checkMeasureCornerR.GetCheck();

	CModelData::m_InspectionPara.Info.nAOIScanSpeedLevel = m_comboAOIScanSpeedLevel.GetCurSel(); //KJT 20210315
	//KJT 20210525
	CModelData::m_PpaPara.Info.nDivX = m_comboDivX.GetCurSel();
	CModelData::m_PpaPara.Info.nDivY = m_comboDivY.GetCurSel();
	CModelData::m_PpaPara.Info.nSlotQuantityXY = m_comboSlotQuantityXY.GetCurSel();

	CModelData::m_InspectionPara.Info.nBoxStickExistType = m_comboBoxStickExistType.GetCurSel();

	CModelData::m_InspectionPara.Info.bOnlyUnloadModePreAlignUse = m_checkOnlyUnloadingModePreAlignUse.GetCheck();

	return TRUE;
}

BOOL CInspectionParaDlg::SavePara()
{
	CheckChangeData();

	BOOL bRtn = CModelData::m_InspectionPara.Save();
	BOOL bRtn2 = CModelData::m_PpaPara.Save();
	if (bRtn == TRUE && bRtn2 == TRUE)
		AfxMessageBox(_T("Save Ok"));
	else
		AfxMessageBox(_T("Save Fail !!"));

	return TRUE;
}

void CInspectionParaDlg::OnShowWindow(BOOL bShow, UINT nStatus)
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

void CInspectionParaDlg::BtnEnable(BOOL bEnable)
{
	int i = 0;

	if (bEnable)
	{
	}
	else
	{
	}
}


void CInspectionParaDlg::OnCbnSelchangeComboInspectionParaDivCountXy()
{
	switch (m_comboPPADivXY.GetCurSel())
	{
	case eQuantity_1X1:
		m_editDivX.SetWindowText(_T("1"));
		m_editDivY.SetWindowText(_T("1"));
		break;
	case eQuantity_3X3:
		m_editDivX.SetWindowText(_T("3"));
		m_editDivY.SetWindowText(_T("3"));
		break;
	case eQuantity_5X5:
		m_editDivX.SetWindowText(_T("5"));
		m_editDivY.SetWindowText(_T("5"));
		break;
	}
}
