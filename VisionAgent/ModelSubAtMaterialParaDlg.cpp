// ModelSubAtMaterialParaDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentDlg.h"
#include "ModelSubAtMaterialParaDlg.h"
#include "afxdialogex.h"


// CModelSubAtMaterialParaDlg 대화 상자

IMPLEMENT_DYNAMIC(CModelSubAtMaterialParaDlg, CDialogEx)

CModelSubAtMaterialParaDlg::CModelSubAtMaterialParaDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MODEL_SUB_AT_MATERIAL_PARA_DIALOG, pParent)
{
	Create(IDD_MODEL_SUB_AT_MATERIAL_PARA_DIALOG, pParent);
}

CModelSubAtMaterialParaDlg::~CModelSubAtMaterialParaDlg()
{
}

void CModelSubAtMaterialParaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CModelSubAtMaterialParaDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_COMBO_AT_MATERIAL_PARA_CELL_SELECT_NO_X, &CModelSubAtMaterialParaDlg::OnCbnSelchangeComboMaterialParaCellSelectNoX)
	ON_CBN_SELCHANGE(IDC_COMBO_AT_MATERIAL_PARA_CELL_SELECT_NO_Y, &CModelSubAtMaterialParaDlg::OnCbnSelchangeComboMaterialParaCellSelectNoY)
	ON_BN_CLICKED(IDC_BTN_AT_MATERIAL_CELL_INFO_COPY, &CModelSubAtMaterialParaDlg::OnBnClickedBtnAtMaterialCellInfoCopy)
	ON_BN_CLICKED(IDC_BTN_AT_MATERIAL_CELL_INFO_COPY_ALL, &CModelSubAtMaterialParaDlg::OnBnClickedBtnAtMaterialCellInfoCopyAll)
END_MESSAGE_MAP()


// CModelSubAtMaterialParaDlg 메시지 처리기

BOOL CModelSubAtMaterialParaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitCtrl();

	return TRUE;
}

void CModelSubAtMaterialParaDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
}

BOOL CModelSubAtMaterialParaDlg::InitCtrl()
{
	int i = 0;
	CString Str;

	//Stick Info
	m_editStickSizeX.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_STICK_SIZE_X, this);
	m_editStickSizeY.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_STICK_SIZE_Y, this);
	m_editStickLeftTopX.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_STICK_LEFT_TOP_X, this);
	m_editStickLeftTopY.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_STICK_LEFT_TOP_Y, this);
	m_editAlignLeftHoleX.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_ALIGN_LEFT_HOLE_X, this);
	m_editAlignLeftHoleY.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_ALIGN_LEFT_HOLE_Y, this);
	m_editAlignRightHoleX.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_ALIGN_RIGHT_HOLE_X, this);
	m_editAlignRightHoleY.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_ALIGN_RIGHT_HOLE_Y, this);

	m_comboHoleShape.SubclassDlgItem(IDC_COMBO_AT_MATERIAL_PARA_PPA_HOLE_SHAPE, this);
	m_comboHoleShape.ResetContent();
	m_comboHoleShape.AddString(_T("RECTANGLE"));
	m_comboHoleShape.AddString(_T("RECTANGLE_45"));
	m_comboHoleShape.AddString(_T("DIAMOND"));
	m_comboHoleShape.AddString(_T("CIRCLE"));
	m_comboHoleShape.AddString(_T("ELLIPSE"));
	m_comboHoleShape.AddString(_T("ELLIPSE_45"));
	m_comboHoleShape.SetCurSel(0);

	m_comboHoleArrange.SubclassDlgItem(IDC_COMBO_AT_MATERIAL_PARA_PPA_HOLE_ARRANGE, this);
	m_comboHoleArrange.ResetContent();
	m_comboHoleArrange.AddString(_T("RECTANGLE"));
	m_comboHoleArrange.AddString(_T("CROSS"));
	m_comboHoleArrange.SetCurSel(0);

	m_editAlignHoleSizeX.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_ALIGN_HOLE_SIZE_X, this);
	m_editAlignHoleSizeY.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_ALIGN_HOLE_SIZE_Y, this);
	m_editStickThickness.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_STICK_THICKNESS, this);
	m_editPaperThickness.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_PAPER_THICKNESS, this);

	//Cell Info
	m_editCellCountX.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_CELL_COUNT_X, this);
	m_editCellCountY.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_CELL_COUNT_Y, this);
	m_editFirstCellLeftTopX.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_CELL_BEGIN_LEFT_TOP_X, this);
	m_editFirstCellLeftTopY.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_CELL_BEGIN_LEFT_TOP_Y, this);
	m_editCellPitchX.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_CELL_PITCH_X, this);
	m_editCellPitchY.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_CELL_PITCH_Y, this);

	m_comboCellSelectX.SubclassDlgItem(IDC_COMBO_AT_MATERIAL_PARA_CELL_SELECT_NO_X, this);
	m_comboCellSelectX.ResetContent();
	for (i = 0; i < CELL_X_COUNT_MAX; i++)
	{
		Str.Format(_T("%d"), i + 1);
		m_comboCellSelectX.AddString(Str);
	}
	m_comboCellSelectX.SetCurSel(0);

	m_comboCellSelectY.SubclassDlgItem(IDC_COMBO_AT_MATERIAL_PARA_CELL_SELECT_NO_Y, this);
	m_comboCellSelectY.ResetContent();
	for (i = 0; i < CELL_Y_COUNT_MAX; i++)
	{
		Str.Format(_T("%d"), i + 1);
		m_comboCellSelectY.AddString(Str);
	}
	m_comboCellSelectY.SetCurSel(0);

	//Sub Cell Info
	m_editCellLeftTopX.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_CELL_LEFT_TOP_X, this);
	m_editCellLeftTopY.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_CELL_LEFT_TOP_Y, this);
	m_editCellSizeX.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_CELL_SIZE_X, this);
	m_editCellSizeY.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_CELL_SIZE_Y, this);

	m_comboInspectionSlotCount.SubclassDlgItem(IDC_COMBO_AT_MATERIAL_PARA_SLOT_COUNT, this);
	m_comboInspectionSlotCount.ResetContent();
	m_comboInspectionSlotCount.AddString(_T("1x1"));
	m_comboInspectionSlotCount.AddString(_T("3x3"));
	m_comboInspectionSlotCount.AddString(_T("5x5"));
	m_comboInspectionSlotCount.SetCurSel(0);

	//Slot Info
	m_editSlotCenterShiftX.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_CELL_SLOT_CENTER_SHIFT_X, this);
	m_editSlotCenterShiftY.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_CELL_SLOT_CENTER_SHIFT_Y, this);
	m_editSlotWidth.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_CELL_SLOT_WIDTH, this);
	m_editSlotHeight.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_CELL_SLOT_HEIGHT, this);
	m_editSlotAngle.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_SLOT_ANGLE, this);
	m_editSlotPitchX.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_CELL_SLOT_PITCH_X, this);
	m_editSlotPitchY.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_CELL_SLOT_PITCH_Y, this);
	m_editSlotTotalPitchX.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_CELL_SLOT_TOTAL_PITCH_X, this);
	m_editSlotTotalPitchY.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_CELL_SLOT_TOTAL_PITCH_Y, this);

	//Cell Info Copy
	m_comboCellInfoCopySourceX.SubclassDlgItem(IDC_COMBO_AT_MATERIAL_CELL_INFO_COPY_SOURCE_X, this);
	m_comboCellInfoCopySourceX.ResetContent();
	for (i = 0; i < CELL_X_COUNT_MAX; i++)
	{
		Str.Format(_T("%d"), i + 1);
		m_comboCellInfoCopySourceX.AddString(Str);
	}
	m_comboCellInfoCopySourceX.SetCurSel(0);

	m_comboCellInfoCopySourceY.SubclassDlgItem(IDC_COMBO_AT_MATERIAL_CELL_INFO_COPY_SOURCE_Y, this);
	m_comboCellInfoCopySourceY.ResetContent();
	for (i = 0; i < CELL_Y_COUNT_MAX; i++)
	{
		Str.Format(_T("%d"), i + 1);
		m_comboCellInfoCopySourceY.AddString(Str);
	}
	m_comboCellInfoCopySourceY.SetCurSel(0);

	m_comboCellInfoCopyTargetX.SubclassDlgItem(IDC_COMBO_AT_MATERIAL_CELL_INFO_COPY_TARGET_X, this);
	m_comboCellInfoCopyTargetX.ResetContent();
	for (i = 0; i < CELL_X_COUNT_MAX; i++)
	{
		Str.Format(_T("%d"), i + 1);
		m_comboCellInfoCopyTargetX.AddString(Str);
	}
	m_comboCellInfoCopyTargetX.SetCurSel(0);

	m_comboCellInfoCopyTargetY.SubclassDlgItem(IDC_COMBO_AT_MATERIAL_CELL_INFO_COPY_TARGET_Y, this);
	m_comboCellInfoCopyTargetY.ResetContent();
	for (i = 0; i < CELL_Y_COUNT_MAX; i++)
	{
		Str.Format(_T("%d"), i + 1);
		m_comboCellInfoCopyTargetY.AddString(Str);
	}
	m_comboCellInfoCopyTargetY.SetCurSel(0);

	m_btnCellInfoCopy.SubclassDlgItem(IDC_BTN_AT_MATERIAL_CELL_INFO_COPY, this);
	m_btnCellInfoCopy.SetColor(BLACK, LLTGRAY);
	m_btnCellInfoCopyAll.SubclassDlgItem(IDC_BTN_AT_MATERIAL_CELL_INFO_COPY_ALL, this);
	m_btnCellInfoCopyAll.SetColor(BLACK, LLTGRAY);

	//Tegkey Info
	m_editTegkey_LT_X.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_TEGKEY_LT_X, this);
	m_editTegkey_LT_Y.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_TEGKEY_LT_Y, this);
	m_editTegkey_LB_X.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_TEGKEY_LB_X, this);
	m_editTegkey_LB_Y.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_TEGKEY_LB_Y, this);
	m_editTegkey_RT_X.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_TEGKEY_RT_X, this);
	m_editTegkey_RT_Y.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_TEGKEY_RT_Y, this);
	m_editTegkey_RB_X.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_TEGKEY_RB_X, this);
	m_editTegkey_RB_Y.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_TEGKEY_RB_Y, this);
	m_editTegkey_SizeX.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_TEGKEY_SIZE_X, this);
	m_editTegkey_SizeY.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_TEGKEY_SIZE_Y, this);

	//Stick Wing Y Offset
	m_editStickWingCenterYOffset[eGRIPPER_ROW1].SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_STICK_WING_CENTER_Y_OFFSET_1, this);
	m_editStickWingCenterYOffset[eGRIPPER_ROW2].SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_STICK_WING_CENTER_Y_OFFSET_2, this);
	m_editStickWingCenterYOffset[eGRIPPER_ROW3].SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_STICK_WING_CENTER_Y_OFFSET_3, this);
	//m_editStickWingCenterYOffset[eGRIPPER_ROW4].SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_STICK_WING_CENTER_Y_OFFSET_4, this);
	//m_editStickWingCenterYOffset[eGRIPPER_ROW5].SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_STICK_WING_CENTER_Y_OFFSET_5, this);
#ifdef GRIPPER_8
	m_editStickWingCenterYOffset[eGRIPPER_ROW6].SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_STICK_WING_CENTER_Y_OFFSET_6, this);
	m_editStickWingCenterYOffset[eGRIPPER_ROW7].SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_STICK_WING_CENTER_Y_OFFSET_7, this);
	m_editStickWingCenterYOffset[eGRIPPER_ROW8].SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_STICK_WING_CENTER_Y_OFFSET_8, this);
#endif

	m_editTensionRatioX.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_TENSION_RATIO_X, this);
	m_editTensionRatioY.SubclassDlgItem(IDC_EDIT_AT_MATERIAL_PARA_TENSION_RATIO_Y, this);

	return TRUE;
}

BOOL CModelSubAtMaterialParaDlg::InitPara()
{
	CString Str;
	int i = 0;

	//Stick Info
	m_editStickSizeX.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_AtMaterialPara.Info.dStickSizeX));
	m_editStickSizeY.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_AtMaterialPara.Info.dStickSizeY));
	m_editStickLeftTopX.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_AtMaterialPara.Info.dStickLeftTopX));
	m_editStickLeftTopY.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_AtMaterialPara.Info.dStickLeftTopY));
	m_editAlignLeftHoleX.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_AtMaterialPara.Info.dAlignLeftHoleX));
	m_editAlignLeftHoleY.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_AtMaterialPara.Info.dAlignLeftHoleY));
	m_editAlignRightHoleX.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_AtMaterialPara.Info.dAlignRightHoleX));
	m_editAlignRightHoleY.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_AtMaterialPara.Info.dAlignRightHoleY));
	m_comboHoleShape.SetCurSel(CModelData::m_AtMaterialPara.Info.nHoleShape);
	m_comboHoleArrange.SetCurSel(CModelData::m_AtMaterialPara.Info.nHoleArrange);
	m_editAlignHoleSizeX.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_AtMaterialPara.Info.dAlignHoleSizeX));
	m_editAlignHoleSizeY.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_AtMaterialPara.Info.dAlignHoleSizeY));
	m_editStickThickness.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_AtMaterialPara.Info.dStickThickness));
	m_editPaperThickness.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_AtMaterialPara.Info.dPaperThickness));

	//Cell Info
	m_editCellCountX.SetWindowText(_ToStr(_T("%d"), CModelData::m_AtMaterialPara.Info.nCellCountX));
	m_editCellCountY.SetWindowText(_ToStr(_T("%d"), CModelData::m_AtMaterialPara.Info.nCellCountY));
	m_editFirstCellLeftTopX.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_AtMaterialPara.Info.dFirstCellLeftTopX));
	m_editFirstCellLeftTopY.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_AtMaterialPara.Info.dFirstCellLeftTopY));
	m_editCellPitchX.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_AtMaterialPara.Info.dCellPitchX));
	m_editCellPitchY.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_AtMaterialPara.Info.dCellPitchY));

	//m_nSelectCellX = 0;
	//m_nSelectCellY = 0;

	m_comboCellSelectX.ResetContent();
	for (i = 0; i < CModelData::m_AtMaterialPara.Info.nCellCountX; i++)
	{
		Str.Format(_T("%d"), i + 1);
		m_comboCellSelectX.AddString(Str);
	}
	m_comboCellSelectX.SetCurSel(0);

	m_comboCellSelectY.ResetContent();
	for (i = 0; i < CModelData::m_AtMaterialPara.Info.nCellCountY; i++)
	{
		Str.Format(_T("%d"), i + 1);
		m_comboCellSelectY.AddString(Str);
	}
	m_comboCellSelectY.SetCurSel(0);

	//Sub Cell Info
	int nCurCellX = 0;
	int nCurCellY = 0;

	m_editCellLeftTopX.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_AtMaterialPara.Info.dCellLeftTopX[nCurCellX][nCurCellY]));
	m_editCellLeftTopY.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_AtMaterialPara.Info.dCellLeftTopY[nCurCellX][nCurCellY]));
	m_editCellSizeX.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_AtMaterialPara.Info.dCellSizeX[nCurCellX][nCurCellY]));
	m_editCellSizeY.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_AtMaterialPara.Info.dCellSizeY[nCurCellX][nCurCellY]));
	m_comboInspectionSlotCount.SetCurSel(CModelData::m_AtMaterialPara.Info.nInspectionSlotCount[nCurCellX][nCurCellY]);
	//Slot Info
	m_editSlotCenterShiftX.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_AtMaterialPara.Info.dSlotCenterShiftX[nCurCellX][nCurCellY]));
	m_editSlotCenterShiftY.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_AtMaterialPara.Info.dSlotCenterShiftY[nCurCellX][nCurCellY]));
	m_editSlotWidth.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_AtMaterialPara.Info.dSlotSizeX[nCurCellX][nCurCellY]));
	m_editSlotHeight.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_AtMaterialPara.Info.dSlotSizeY[nCurCellX][nCurCellY]));
	m_editSlotAngle.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_AtMaterialPara.Info.dSlotAngle[nCurCellX][nCurCellY]));
	m_editSlotPitchX.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_AtMaterialPara.Info.dSlotPitchX[nCurCellX][nCurCellY]));
	m_editSlotPitchY.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_AtMaterialPara.Info.dSlotPitchY[nCurCellX][nCurCellY]));
	m_editSlotTotalPitchX.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_AtMaterialPara.Info.dSlotTotalPitchX[nCurCellX][nCurCellY]));
	m_editSlotTotalPitchY.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_AtMaterialPara.Info.dSlotTotalPitchY[nCurCellX][nCurCellY]));

	//Cell Info Copy
	//m_nCopySelectSrcX = 0;
	//m_nCopySelectSrcY = 0;
	//m_nCopySelectTargetX = 0;
	//m_nCopySelectTargetY = 0;

	m_comboCellInfoCopySourceX.ResetContent();
	for (i = 0; i < CModelData::m_AtMaterialPara.Info.nCellCountX; i++)
	{
		Str.Format(_T("%d"), i + 1);
		m_comboCellInfoCopySourceX.AddString(Str);
	}
	m_comboCellInfoCopySourceX.SetCurSel(0);

	m_comboCellInfoCopySourceY.ResetContent();
	for (i = 0; i < CModelData::m_AtMaterialPara.Info.nCellCountY; i++)
	{
		Str.Format(_T("%d"), i + 1);
		m_comboCellInfoCopySourceY.AddString(Str);
	}
	m_comboCellInfoCopySourceY.SetCurSel(0);

	m_comboCellInfoCopyTargetX.ResetContent();
	for (i = 0; i < CModelData::m_AtMaterialPara.Info.nCellCountX; i++)
	{
		Str.Format(_T("%d"), i + 1);
		m_comboCellInfoCopyTargetX.AddString(Str);
	}
	m_comboCellInfoCopyTargetX.SetCurSel(0);

	m_comboCellInfoCopyTargetY.ResetContent();
	for (i = 0; i < CModelData::m_AtMaterialPara.Info.nCellCountY; i++)
	{
		Str.Format(_T("%d"), i + 1);
		m_comboCellInfoCopyTargetY.AddString(Str);
	}
	m_comboCellInfoCopyTargetY.SetCurSel(0);

	m_comboCellInfoCopySourceX.SetCurSel(0);
	m_comboCellInfoCopySourceY.SetCurSel(0);
	m_comboCellInfoCopyTargetX.SetCurSel(0);
	m_comboCellInfoCopyTargetY.SetCurSel(0);

	//Tegkey Info
	m_editTegkey_LT_X.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_AtMaterialPara.Info.dTegkey_LT_X));
	m_editTegkey_LT_Y.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_AtMaterialPara.Info.dTegkey_LT_Y));
	m_editTegkey_LB_X.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_AtMaterialPara.Info.dTegkey_LB_X));
	m_editTegkey_LB_Y.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_AtMaterialPara.Info.dTegkey_LB_Y));
	m_editTegkey_RT_X.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_AtMaterialPara.Info.dTegkey_RT_X));
	m_editTegkey_RT_Y.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_AtMaterialPara.Info.dTegkey_RT_Y));
	m_editTegkey_RB_X.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_AtMaterialPara.Info.dTegkey_RB_X));
	m_editTegkey_RB_Y.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_AtMaterialPara.Info.dTegkey_RB_Y));
	m_editTegkey_SizeX.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_AtMaterialPara.Info.dTegkey_SizeX));
	m_editTegkey_SizeY.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_AtMaterialPara.Info.dTegkey_SizeY));

	//Stick Wing Y Offset
	for (i = 0; i < eGRIPPER_ROW_MAX; i++)
	{
		m_editStickWingCenterYOffset[i].SetWindowText(_ToStr(_T("%.5f"), CModelData::m_AtMaterialPara.Info.dStickWingCenterYOffset[i]));
	}

	m_editTensionRatioX.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_AtMaterialPara.Info.dTensionRatioX));
	m_editTensionRatioY.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_AtMaterialPara.Info.dTensionRatioY));

	return TRUE;
}

BOOL CModelSubAtMaterialParaDlg::CheckChangeData()
{
	CString Str = _T("");

	int nCurCellX = m_comboCellSelectX.GetCurSel();
	int nCurCellY = m_comboCellSelectY.GetCurSel();

#pragma region //Check Interlock  //KJT 20210502
	//Stick Info
	m_editStickSizeX.GetWindowText(Str); if (_ttof(Str) <= 0 || _ttof(Str) >= 65535) { AfxMessageBox(_T("Stick SizeX Invalid !!")); return FALSE; }
	int nStickX = _ttoi(Str); //KJT 20210727
	m_editStickSizeY.GetWindowText(Str); if (_ttof(Str) <= 0 || _ttof(Str) >= 65535) { AfxMessageBox(_T("Stick SizeY Invalid !!")); return FALSE; }
	int nStickY = _ttoi(Str); //KJT 20210727

	m_editAlignLeftHoleX.GetWindowText(Str); if (_ttof(Str) > 0) { AfxMessageBox(_T("Align Left Hole X Invalid !!")); return FALSE; }
	m_editAlignRightHoleX.GetWindowText(Str); if (_ttof(Str) < 0) { AfxMessageBox(_T("Align Right Hole X Invalid !!")); return FALSE; }

	m_editStickThickness.GetWindowText(Str); if (_ttof(Str) >= 1) { AfxMessageBox(_T("Sitck Thickness Invalid !!")); return FALSE; }
	m_editPaperThickness.GetWindowText(Str); if (_ttof(Str) >= 1) { AfxMessageBox(_T("Paper Thickness Invalid !!")); return FALSE; }

	//Cell Info
	m_editCellCountX.GetWindowText(Str); if (_ttoi(Str) >= CIM_MAX_CELL_COUNT_XY) { AfxMessageBox(_T("Cell CountX Invalid !!")); return FALSE; }
	int nCellCountX = _ttoi(Str);
	m_editCellCountY.GetWindowText(Str); if (_ttoi(Str) >= CIM_MAX_CELL_COUNT_XY) { AfxMessageBox(_T("Cell CountY Invalid !!")); return FALSE; }
	int nCellCountY = _ttoi(Str);

	m_editFirstCellLeftTopX.GetWindowText(Str); if (_ttof(Str) >= 0) { AfxMessageBox(_T("FirstCell LTX Invalid !!")); return FALSE; }
	m_editFirstCellLeftTopY.GetWindowText(Str); if (_ttof(Str) <= 0) { AfxMessageBox(_T("FirstCell LTY Invalid !!")); return FALSE; }
	m_editCellPitchX.GetWindowText(Str); if (_ttof(Str) < 0) { AfxMessageBox(_T("Cell PitchX Invalid !! (Cur < 0)")); return FALSE; }
	m_editCellPitchY.GetWindowText(Str); if (_ttof(Str) < 0) { AfxMessageBox(_T("Cell PitchY Invalid !! (Cur < 0)")); return FALSE; }

	m_editCellLeftTopX.GetWindowText(Str); if (nCurCellX == 0 && _ttof(Str) >= 0) { AfxMessageBox(_T("Cell LTX Invalid !! (Cell0 LTX >= 0)")); return FALSE; }
	m_editCellLeftTopY.GetWindowText(Str); if (nCurCellY == 0 && _ttof(Str) <= 0) { AfxMessageBox(_T("Cell LTY Invalid !! (Cell0 LTY <= 0)")); return FALSE; }

	m_editCellSizeX.GetWindowText(Str); if ((_ttof(Str) * nCellCountX) > nStickX) { AfxMessageBox(_T("Cell SizeX Invalid !!")); return FALSE; }
	m_editCellSizeY.GetWindowText(Str); if ((_ttof(Str) * nCellCountY) > nStickX) { AfxMessageBox(_T("Cell SizeY Invalid !!")); return FALSE; }

	//Slot Info
	m_editSlotCenterShiftX.GetWindowText(Str); if (_ttof(Str) < 0) { AfxMessageBox(_T("Slot CenterShiftX Invalid !! (Cur < 0)")); return FALSE; }
	m_editSlotCenterShiftY.GetWindowText(Str);  if (_ttof(Str) > 0) { AfxMessageBox(_T("Slot CenterShiftY Invalid !! (Cur > 0)")); return FALSE; }
	m_editSlotWidth.GetWindowText(Str); if (_ttof(Str) < 0) { AfxMessageBox(_T("Slot SizeX Invalid !! (Cur <= 0)")); return FALSE; }
	m_editSlotHeight.GetWindowText(Str); if (_ttof(Str) < 0) { AfxMessageBox(_T("Slot SizeY Invalid !! (Cur <= 0)")); return FALSE; }
	m_editSlotPitchX.GetWindowText(Str); if (_ttof(Str) < 0) { AfxMessageBox(_T("Slot PitchX Invalid !! (Cur < 0)")); return FALSE; }
	m_editSlotPitchY.GetWindowText(Str); if (_ttof(Str) < 0) { AfxMessageBox(_T("Slot PitchY Invalid !! (Cur < 0)")); return FALSE; }
	m_editSlotTotalPitchX.GetWindowText(Str); if (_ttof(Str) < 0) { AfxMessageBox(_T("Slot TotalPitchX Invalid !! (Cur < 0)")); return FALSE; }
	m_editSlotTotalPitchY.GetWindowText(Str); if (_ttof(Str) < 0) { AfxMessageBox(_T("Slot TotalPitchY Invalid !! (Cur < 0)")); return FALSE; }

	m_editTensionRatioX.GetWindowText(Str); if (_ttof(Str) < 0.9 || _ttof(Str) > 1.1) { AfxMessageBox(_T("TensionRatioX Invalid !!")); return FALSE; }
	m_editTensionRatioY.GetWindowText(Str); if (_ttof(Str) < 0.9 || _ttof(Str) > 1.1) { AfxMessageBox(_T("TensionRatioY Invalid !!")); return FALSE; }

	//Tegkey Info
	m_editTegkey_LT_X.GetWindowText(Str); if (_ttof(Str) > 0) { AfxMessageBox(_T("Tegkey LT_X Invalid !! (Cur > 0)")); return FALSE; }
	m_editTegkey_LB_X.GetWindowText(Str); if (_ttof(Str) > 0) { AfxMessageBox(_T("Tegkey LB_X Invalid !! (Cur > 0)")); return FALSE; }
	m_editTegkey_RT_X.GetWindowText(Str); if (_ttof(Str) < 0) { AfxMessageBox(_T("Tegkey RT_X Invalid !! (Cur < 0)")); return FALSE; }
	m_editTegkey_RB_X.GetWindowText(Str); if (_ttof(Str) < 0) { AfxMessageBox(_T("Tegkey RT_X Invalid !! (Cur < 0)")); return FALSE; }
#pragma endregion


	//Stick Info
	m_editStickSizeX.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.dStickSizeX = _ttof(Str);
	m_editStickSizeY.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.dStickSizeY = _ttof(Str);
	m_editStickLeftTopX.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.dStickLeftTopX = _ttof(Str);
	m_editStickLeftTopY.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.dStickLeftTopY = _ttof(Str);
	m_editAlignLeftHoleX.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.dAlignLeftHoleX = _ttof(Str);
	m_editAlignLeftHoleY.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.dAlignLeftHoleY = _ttof(Str);
	m_editAlignRightHoleX.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.dAlignRightHoleX = _ttof(Str);
	m_editAlignRightHoleY.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.dAlignRightHoleY = _ttof(Str);
	CModelData::m_AtMaterialPara.Info.nHoleShape = m_comboHoleShape.GetCurSel();
	CModelData::m_AtMaterialPara.Info.nHoleArrange = m_comboHoleArrange.GetCurSel();
	m_editAlignHoleSizeX.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.dAlignHoleSizeX = _ttof(Str);
	m_editAlignHoleSizeY.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.dAlignHoleSizeY = _ttof(Str);
	m_editStickThickness.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.dStickThickness = _ttof(Str);
	m_editPaperThickness.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.dPaperThickness = _ttof(Str);

	//Cell Info
	m_editCellCountX.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.nCellCountX = _ttoi(Str);
	m_editCellCountY.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.nCellCountY = _ttoi(Str);
	m_editFirstCellLeftTopX.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.dFirstCellLeftTopX = _ttof(Str);
	m_editFirstCellLeftTopY.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.dFirstCellLeftTopY = _ttof(Str);
	m_editCellPitchX.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.dCellPitchX = _ttof(Str);
	m_editCellPitchY.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.dCellPitchY = _ttof(Str);

	//Sub Cell Info
	m_editCellLeftTopX.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.dCellLeftTopX[nCurCellX][nCurCellY] = _ttof(Str);
	m_editCellLeftTopY.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.dCellLeftTopY[nCurCellX][nCurCellY] = _ttof(Str);
	m_editCellSizeX.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.dCellSizeX[nCurCellX][nCurCellY] = _ttof(Str);
	m_editCellSizeY.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.dCellSizeY[nCurCellX][nCurCellY] = _ttof(Str);
	CModelData::m_AtMaterialPara.Info.nInspectionSlotCount[nCurCellX][nCurCellY] = m_comboInspectionSlotCount.GetCurSel();

	//Slot Info
	m_editSlotCenterShiftX.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.dSlotCenterShiftX[nCurCellX][nCurCellY] = _ttof(Str);
	m_editSlotCenterShiftY.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.dSlotCenterShiftY[nCurCellX][nCurCellY] = _ttof(Str);
	m_editSlotWidth.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.dSlotSizeX[nCurCellX][nCurCellY] = _ttof(Str);
	m_editSlotHeight.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.dSlotSizeY[nCurCellX][nCurCellY] = _ttof(Str);
	m_editSlotAngle.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.dSlotAngle[nCurCellX][nCurCellY] = _ttof(Str);
	m_editSlotPitchX.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.dSlotPitchX[nCurCellX][nCurCellY] = _ttof(Str);
	m_editSlotPitchY.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.dSlotPitchY[nCurCellX][nCurCellY] = _ttof(Str);
	m_editSlotTotalPitchX.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.dSlotTotalPitchX[nCurCellX][nCurCellY] = _ttof(Str);
	m_editSlotTotalPitchY.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.dSlotTotalPitchY[nCurCellX][nCurCellY] = _ttof(Str);


	//Tegkey Info
	m_editTegkey_LT_X.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.dTegkey_LT_X = _ttof(Str);
	m_editTegkey_LT_Y.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.dTegkey_LT_Y = _ttof(Str);
	m_editTegkey_LB_X.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.dTegkey_LB_X = _ttof(Str);
	m_editTegkey_LB_Y.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.dTegkey_LB_Y = _ttof(Str);
	m_editTegkey_RT_X.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.dTegkey_RT_X = _ttof(Str);
	m_editTegkey_RT_Y.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.dTegkey_RT_Y = _ttof(Str);
	m_editTegkey_RB_X.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.dTegkey_RB_X = _ttof(Str);
	m_editTegkey_RB_Y.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.dTegkey_RB_Y = _ttof(Str);
	m_editTegkey_SizeX.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.dTegkey_SizeX = _ttof(Str);
	m_editTegkey_SizeY.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.dTegkey_SizeY = _ttof(Str);

	//Stick Wing Y Offset
	for (int i = 0; i < eGRIPPER_ROW_MAX; i++)
	{
		m_editStickWingCenterYOffset[i].GetWindowText(Str);
		CModelData::m_AtMaterialPara.Info.dStickWingCenterYOffset[i] = _ttof(Str);
	}

	m_editTensionRatioX.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.dTensionRatioX = _ttof(Str);
	m_editTensionRatioY.GetWindowText(Str);
	CModelData::m_AtMaterialPara.Info.dTensionRatioY = _ttof(Str); //KJT 20210415

	return TRUE;
}

BOOL CModelSubAtMaterialParaDlg::SavePara()
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

void CModelSubAtMaterialParaDlg::OnShowWindow(BOOL bShow, UINT nStatus)
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

void CModelSubAtMaterialParaDlg::BtnEnable(BOOL bEnable)
{
	int i = 0;

	if (bEnable)
	{
	}
	else
	{
	}
}


void CModelSubAtMaterialParaDlg::OnCbnSelchangeComboMaterialParaCellSelectNoX()
{
	SelectedCellChange();
}


void CModelSubAtMaterialParaDlg::OnCbnSelchangeComboMaterialParaCellSelectNoY()
{
	SelectedCellChange();
}

void CModelSubAtMaterialParaDlg::SelectedCellChange()
{
	//m_nSelectCellX = m_comboCellSelectX.GetCurSel();
	//m_nSelectCellY = m_comboCellSelectY.GetCurSel();

	int nCurCellX = m_comboCellSelectX.GetCurSel();
	int nCurCellY = m_comboCellSelectY.GetCurSel();

	//Sub Cell Info
	m_editCellLeftTopX.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_AtMaterialPara.Info.dCellLeftTopX[nCurCellX][nCurCellY]));
	m_editCellLeftTopY.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_AtMaterialPara.Info.dCellLeftTopY[nCurCellX][nCurCellY]));
	m_editCellSizeX.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_AtMaterialPara.Info.dCellSizeX[nCurCellX][nCurCellY]));
	m_editCellSizeY.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_AtMaterialPara.Info.dCellSizeY[nCurCellX][nCurCellY]));
	m_comboInspectionSlotCount.SetCurSel(CModelData::m_AtMaterialPara.Info.nInspectionSlotCount[nCurCellX][nCurCellY]);
	//Slot Info
	m_editSlotCenterShiftX.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_AtMaterialPara.Info.dSlotCenterShiftX[nCurCellX][nCurCellY]));
	m_editSlotCenterShiftY.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_AtMaterialPara.Info.dSlotCenterShiftY[nCurCellX][nCurCellY]));
	m_editSlotWidth.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_AtMaterialPara.Info.dSlotSizeX[nCurCellX][nCurCellY]));
	m_editSlotHeight.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_AtMaterialPara.Info.dSlotSizeY[nCurCellX][nCurCellY]));
	m_editSlotAngle.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_AtMaterialPara.Info.dSlotAngle[nCurCellX][nCurCellY]));
	m_editSlotPitchX.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_AtMaterialPara.Info.dSlotPitchX[nCurCellX][nCurCellY]));
	m_editSlotPitchY.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_AtMaterialPara.Info.dSlotPitchY[nCurCellX][nCurCellY]));
	m_editSlotTotalPitchX.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_AtMaterialPara.Info.dSlotTotalPitchX[nCurCellX][nCurCellY]));
	m_editSlotTotalPitchY.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_AtMaterialPara.Info.dSlotTotalPitchY[nCurCellX][nCurCellY]));
}

void CModelSubAtMaterialParaDlg::OnBnClickedBtnAtMaterialCellInfoCopy()
{
	CString Str = _T("");

	int nSrcX = m_comboCellInfoCopySourceX.GetCurSel();
	int nSrcY = m_comboCellInfoCopySourceY.GetCurSel();

	int nTargetX = m_comboCellInfoCopyTargetX.GetCurSel();
	int nTargetY = m_comboCellInfoCopyTargetY.GetCurSel();

	if (nSrcX == nTargetX && nSrcY == nTargetY)
	{
		AfxMessageBox(_T("Check Cell Number !!!"));
		return;
	}

	Str.Format(_T("Cell Info Copy %d, %d -> %d, %d ?"), nSrcX + 1, nSrcY + 1, nTargetX + 1, nTargetY + 1);
	if (IDYES != AfxMessageBox(Str, MB_YESNO))
		return;

	//CModelData::m_AtMaterialPara.Info.dCellLeftTopX[nTargetX][nTargetY] = CModelData::m_AtMaterialPara.Info.dCellLeftTopX[nSrcX][nSrcY];
	//CModelData::m_AtMaterialPara.Info.dCellLeftTopY[nTargetX][nTargetY] = CModelData::m_AtMaterialPara.Info.dCellLeftTopY[nSrcX][nSrcY];

	CModelData::m_AtMaterialPara.Info.dCellSizeX[nTargetX][nTargetY] = CModelData::m_AtMaterialPara.Info.dCellSizeX[nSrcX][nSrcY];
	CModelData::m_AtMaterialPara.Info.dCellSizeY[nTargetX][nTargetY] = CModelData::m_AtMaterialPara.Info.dCellSizeY[nSrcX][nSrcY];

	CModelData::m_AtMaterialPara.Info.nInspectionSlotCount[nTargetX][nTargetY] = CModelData::m_AtMaterialPara.Info.nInspectionSlotCount[nSrcX][nSrcY];

	CModelData::m_AtMaterialPara.Info.dSlotCenterShiftX[nTargetX][nTargetY] = CModelData::m_AtMaterialPara.Info.dSlotCenterShiftX[nSrcX][nSrcY];
	CModelData::m_AtMaterialPara.Info.dSlotCenterShiftY[nTargetX][nTargetY] = CModelData::m_AtMaterialPara.Info.dSlotCenterShiftY[nSrcX][nSrcY];

	CModelData::m_AtMaterialPara.Info.dSlotSizeX[nTargetX][nTargetY] = CModelData::m_AtMaterialPara.Info.dSlotSizeX[nSrcX][nSrcY];
	CModelData::m_AtMaterialPara.Info.dSlotSizeY[nTargetX][nTargetY] = CModelData::m_AtMaterialPara.Info.dSlotSizeY[nSrcX][nSrcY];

	CModelData::m_AtMaterialPara.Info.dSlotAngle[nTargetX][nTargetY] = CModelData::m_AtMaterialPara.Info.dSlotAngle[nSrcX][nSrcY];

	CModelData::m_AtMaterialPara.Info.dSlotPitchX[nTargetX][nTargetY] = CModelData::m_AtMaterialPara.Info.dSlotPitchX[nSrcX][nSrcY];
	CModelData::m_AtMaterialPara.Info.dSlotPitchY[nTargetX][nTargetY] = CModelData::m_AtMaterialPara.Info.dSlotPitchY[nSrcX][nSrcY];

	CModelData::m_AtMaterialPara.Info.dSlotTotalPitchX[nTargetX][nTargetY] = CModelData::m_AtMaterialPara.Info.dSlotTotalPitchX[nSrcX][nSrcY];
	CModelData::m_AtMaterialPara.Info.dSlotTotalPitchY[nTargetX][nTargetY] = CModelData::m_AtMaterialPara.Info.dSlotTotalPitchY[nSrcX][nSrcY];

	Str.Format(_T("At Material Para Data Copy Cell : %d, %d -> %d, %d"), nSrcX + 1, nSrcY + 1, nTargetX + 1, nTargetY + 1);
	Total_Msg(Str);

	m_comboCellSelectX.SetCurSel(nTargetX);
	m_comboCellSelectY.SetCurSel(nTargetY);
}

void CModelSubAtMaterialParaDlg::OnBnClickedBtnAtMaterialCellInfoCopyAll() //KJT 20210301
{
	CString Str = _T("");

	int nSrcX = m_comboCellInfoCopySourceX.GetCurSel();
	int nSrcY = m_comboCellInfoCopySourceY.GetCurSel();

	Str.Format(_T("Cell Info Copy %d, %d -> All ?"), nSrcX + 1, nSrcY + 1);
	if (IDYES != AfxMessageBox(Str, MB_YESNO))
		return;

	for (int i = 0; i < CModelData::m_AtMaterialPara.Info.nCellCountX; i++)
	{
		for (int j = 0; j < CModelData::m_AtMaterialPara.Info.nCellCountY; j++)
		{
			if (i == nSrcX && j == nSrcY)
				continue;

			//CModelData::m_AtMaterialPara.Info.dCellLeftTopX[i][j] = CModelData::m_AtMaterialPara.Info.dCellLeftTopX[nSrcX][nSrcY];
			//CModelData::m_AtMaterialPara.Info.dCellLeftTopY[i][j] = CModelData::m_AtMaterialPara.Info.dCellLeftTopY[nSrcX][nSrcY];

			CModelData::m_AtMaterialPara.Info.dCellSizeX[i][j] = CModelData::m_AtMaterialPara.Info.dCellSizeX[nSrcX][nSrcY];
			CModelData::m_AtMaterialPara.Info.dCellSizeY[i][j] = CModelData::m_AtMaterialPara.Info.dCellSizeY[nSrcX][nSrcY];

			CModelData::m_AtMaterialPara.Info.nInspectionSlotCount[i][j] = CModelData::m_AtMaterialPara.Info.nInspectionSlotCount[nSrcX][nSrcY];

			CModelData::m_AtMaterialPara.Info.dSlotCenterShiftX[i][j] = CModelData::m_AtMaterialPara.Info.dSlotCenterShiftX[nSrcX][nSrcY];
			CModelData::m_AtMaterialPara.Info.dSlotCenterShiftY[i][j] = CModelData::m_AtMaterialPara.Info.dSlotCenterShiftY[nSrcX][nSrcY];

			CModelData::m_AtMaterialPara.Info.dSlotSizeX[i][j] = CModelData::m_AtMaterialPara.Info.dSlotSizeX[nSrcX][nSrcY];
			CModelData::m_AtMaterialPara.Info.dSlotSizeY[i][j] = CModelData::m_AtMaterialPara.Info.dSlotSizeY[nSrcX][nSrcY];

			CModelData::m_AtMaterialPara.Info.dSlotAngle[i][j] = CModelData::m_AtMaterialPara.Info.dSlotAngle[nSrcX][nSrcY];

			CModelData::m_AtMaterialPara.Info.dSlotPitchX[i][j] = CModelData::m_AtMaterialPara.Info.dSlotPitchX[nSrcX][nSrcY];
			CModelData::m_AtMaterialPara.Info.dSlotPitchY[i][j] = CModelData::m_AtMaterialPara.Info.dSlotPitchY[nSrcX][nSrcY];

			CModelData::m_AtMaterialPara.Info.dSlotTotalPitchX[i][j] = CModelData::m_AtMaterialPara.Info.dSlotTotalPitchX[nSrcX][nSrcY];
			CModelData::m_AtMaterialPara.Info.dSlotTotalPitchY[i][j] = CModelData::m_AtMaterialPara.Info.dSlotTotalPitchY[nSrcX][nSrcY];
		}
	}

	Str.Format(_T("At Material Para Data Copy Cell : %d, %d -> All"), nSrcX + 1, nSrcY + 1);
	Total_Msg(Str);
}