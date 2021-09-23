// MaterialParaDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentDlg.h"
#include "ModelSubMaterialParaDlg.h"
#include "afxdialogex.h"


// CModelSubMaterialParaDlg 대화 상자

IMPLEMENT_DYNAMIC(CModelSubMaterialParaDlg, CDialogEx)


CModelSubMaterialParaDlg::CModelSubMaterialParaDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MODEL_SUB_MATERIAL_PARA_DIALOG, pParent)
{
	Create(IDD_MODEL_SUB_MATERIAL_PARA_DIALOG, pParent);
}

CModelSubMaterialParaDlg::~CModelSubMaterialParaDlg()
{
}

void CModelSubMaterialParaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CModelSubMaterialParaDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_COMBO_MATERIAL_PARA_CELL_SELECT_NO_X, &CModelSubMaterialParaDlg::OnCbnSelchangeComboMaterialParaCellSelectNoX)
	ON_CBN_SELCHANGE(IDC_COMBO_MATERIAL_PARA_CELL_SELECT_NO_Y, &CModelSubMaterialParaDlg::OnCbnSelchangeComboMaterialParaCellSelectNoY)
	ON_BN_CLICKED(IDC_BTN_MATERIAL_CELL_INFO_COPY, &CModelSubMaterialParaDlg::OnBnClickedBtnMaterialCellInfoCopy)
	ON_BN_CLICKED(IDC_BTN_MATERIAL_CELL_INFO_COPY_ALL, &CModelSubMaterialParaDlg::OnBnClickedBtnMaterialCellInfoCopyAll)
END_MESSAGE_MAP()


// CModelSubMaterialParaDlg 메시지 처리기

BOOL CModelSubMaterialParaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitCtrl();

	return TRUE;
}

void CModelSubMaterialParaDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
}

BOOL CModelSubMaterialParaDlg::InitCtrl()
{
	int i = 0;
	CString Str = _T("");

	//Stick Info
	m_editStickSizeX.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_STICK_SIZE_X, this);
	m_editStickSizeY.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_STICK_SIZE_Y, this);
	m_editStickLeftTopX.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_STICK_LEFT_TOP_X, this);
	m_editStickLeftTopY.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_STICK_LEFT_TOP_Y, this);
	m_editAlignLeftHoleX.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_ALIGN_LEFT_HOLE_X, this);
	m_editAlignLeftHoleY.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_ALIGN_LEFT_HOLE_Y, this);
	m_editAlignRightHoleX.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_ALIGN_RIGHT_HOLE_X, this);
	m_editAlignRightHoleY.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_ALIGN_RIGHT_HOLE_Y, this);

	m_comboHoleShape.SubclassDlgItem(IDC_COMBO_MATERIAL_PARA_PPA_HOLE_SHAPE, this);
	m_comboHoleShape.ResetContent();
	m_comboHoleShape.AddString(_T("RECTANGLE"));
	m_comboHoleShape.AddString(_T("RECTANGLE_45"));
	m_comboHoleShape.AddString(_T("DIAMOND"));
	m_comboHoleShape.AddString(_T("CIRCLE"));
	m_comboHoleShape.AddString(_T("ELLIPSE"));
	m_comboHoleShape.AddString(_T("ELLIPSE_45"));
	m_comboHoleShape.SetCurSel(0);

	m_comboHoleArrange.SubclassDlgItem(IDC_COMBO_MATERIAL_PARA_PPA_HOLE_ARRANGE, this);
	m_comboHoleArrange.ResetContent();
	m_comboHoleArrange.AddString(_T("RECTANGLE"));
	m_comboHoleArrange.AddString(_T("CROSS"));
	m_comboHoleArrange.SetCurSel(0);

	m_editAlignHoleSizeX.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_ALIGN_HOLE_SIZE_X, this);
	m_editAlignHoleSizeY.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_ALIGN_HOLE_SIZE_Y, this);
	m_editStickThickness.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_STICK_THICKNESS, this);
	m_editPaperThickness.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_PAPER_THICKNESS, this);

	//Cell Info
	m_editCellCountX.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_CELL_COUNT_X, this);
	m_editCellCountY.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_CELL_COUNT_Y, this);
	m_editFirstCellLeftTopX.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_CELL_BEGIN_LEFT_TOP_X, this);
	m_editFirstCellLeftTopY.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_CELL_BEGIN_LEFT_TOP_Y, this);
	m_editCellPitchX.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_CELL_PITCH_X, this);
	m_editCellPitchY.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_CELL_PITCH_Y, this);
	
	m_comboCellSelectX.SubclassDlgItem(IDC_COMBO_MATERIAL_PARA_CELL_SELECT_NO_X, this);
	m_comboCellSelectX.ResetContent();
	for (i = 0; i < CELL_X_COUNT_MAX; i++)
	{
		Str.Format(_T("%d"), i + 1);
		m_comboCellSelectX.AddString(Str);
	}
	m_comboCellSelectX.SetCurSel(0);

	m_comboCellSelectY.SubclassDlgItem(IDC_COMBO_MATERIAL_PARA_CELL_SELECT_NO_Y, this);
	m_comboCellSelectY.ResetContent();
	for (i = 0; i < CELL_Y_COUNT_MAX; i++)
	{
		Str.Format(_T("%d"), i + 1);
		m_comboCellSelectY.AddString(Str);
	}
	m_comboCellSelectY.SetCurSel(0);

	//Sub Cell Info
	m_editCellLeftTopX.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_CELL_LEFT_TOP_X, this);
	m_editCellLeftTopY.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_CELL_LEFT_TOP_Y, this);
	m_editCellSizeX.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_CELL_SIZE_X, this);
	m_editCellSizeY.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_CELL_SIZE_Y, this);

	m_comboInspectionSlotCount.SubclassDlgItem(IDC_COMBO_MATERIAL_PARA_SLOT_COUNT, this);
	m_comboInspectionSlotCount.ResetContent();
	m_comboInspectionSlotCount.AddString(_T("1x1"));
	m_comboInspectionSlotCount.AddString(_T("3x3"));
	m_comboInspectionSlotCount.AddString(_T("5x5"));
	m_comboInspectionSlotCount.SetCurSel(0);

	//Slot Info
	m_editSlotCenterShiftX.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_CELL_SLOT_CENTER_SHIFT_X, this);
	m_editSlotCenterShiftY.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_CELL_SLOT_CENTER_SHIFT_Y, this);
	m_editSlotWidth.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_CELL_SLOT_WIDTH, this);
	m_editSlotHeight.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_CELL_SLOT_HEIGHT, this);
	m_editSlotAngle.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_SLOT_ANGLE, this);
	m_editSlotPitchX.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_CELL_SLOT_PITCH_X, this);
	m_editSlotPitchY.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_CELL_SLOT_PITCH_Y, this);
	m_editSlotTotalPitchX.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_CELL_SLOT_TOTAL_PITCH_X, this);
	m_editSlotTotalPitchY.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_CELL_SLOT_TOTAL_PITCH_Y, this);

	//Cell Info Copy
	m_comboCellInfoCopySourceX.SubclassDlgItem(IDC_COMBO_MATERIAL_CELL_INFO_COPY_SOURCE_X, this);
	m_comboCellInfoCopySourceX.ResetContent();
	for (i = 0; i < CELL_X_COUNT_MAX; i++)
	{
		Str.Format(_T("%d"), i + 1);
		m_comboCellInfoCopySourceX.AddString(Str);
	}
	m_comboCellInfoCopySourceX.SetCurSel(0);

	m_comboCellInfoCopySourceY.SubclassDlgItem(IDC_COMBO_MATERIAL_CELL_INFO_COPY_SOURCE_Y, this);
	m_comboCellInfoCopySourceY.ResetContent();
	for (i = 0; i < CELL_Y_COUNT_MAX; i++)
	{
		Str.Format(_T("%d"), i + 1);
		m_comboCellInfoCopySourceY.AddString(Str);
	}
	m_comboCellInfoCopySourceY.SetCurSel(0);

	m_comboCellInfoCopyTargetX.SubclassDlgItem(IDC_COMBO_MATERIAL_CELL_INFO_COPY_TARGET_X, this);
	m_comboCellInfoCopyTargetX.ResetContent();
	for (i = 0; i < CELL_X_COUNT_MAX; i++)
	{
		Str.Format(_T("%d"), i + 1);
		m_comboCellInfoCopyTargetX.AddString(Str);
	}
	m_comboCellInfoCopyTargetX.SetCurSel(0);

	m_comboCellInfoCopyTargetY.SubclassDlgItem(IDC_COMBO_MATERIAL_CELL_INFO_COPY_TARGET_Y, this);
	m_comboCellInfoCopyTargetY.ResetContent();
	for (i = 0; i < CELL_Y_COUNT_MAX; i++)
	{
		Str.Format(_T("%d"), i + 1);
		m_comboCellInfoCopyTargetY.AddString(Str);
	}
	m_comboCellInfoCopyTargetY.SetCurSel(0);

	m_btnCellInfoCopy.SubclassDlgItem(IDC_BTN_MATERIAL_CELL_INFO_COPY, this);
	m_btnCellInfoCopy.SetColor(BLACK, LLTGRAY);

	//Tegkey Info
	m_editTegkey_LT_X.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_TEGKEY_LT_X, this);
	m_editTegkey_LT_Y.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_TEGKEY_LT_Y, this);
	m_editTegkey_LB_X.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_TEGKEY_LB_X, this);
	m_editTegkey_LB_Y.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_TEGKEY_LB_Y, this);
	m_editTegkey_RT_X.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_TEGKEY_RT_X, this);
	m_editTegkey_RT_Y.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_TEGKEY_RT_Y, this);
	m_editTegkey_RB_X.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_TEGKEY_RB_X, this);
	m_editTegkey_RB_Y.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_TEGKEY_RB_Y, this);
	m_editTegkey_SizeX.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_TEGKEY_SIZE_X, this);
	m_editTegkey_SizeY.SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_TEGKEY_SIZE_Y, this);

	//Stick Wing Y Offset
	m_editStickWingCenterYOffset[eGRIPPER_ROW1].SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_STICK_WING_CENTER_Y_OFFSET_1, this);
	m_editStickWingCenterYOffset[eGRIPPER_ROW2].SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_STICK_WING_CENTER_Y_OFFSET_2, this);
	m_editStickWingCenterYOffset[eGRIPPER_ROW3].SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_STICK_WING_CENTER_Y_OFFSET_3, this);
	//m_editStickWingCenterYOffset[eGRIPPER_ROW4].SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_STICK_WING_CENTER_Y_OFFSET_4, this);
	//m_editStickWingCenterYOffset[eGRIPPER_ROW5].SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_STICK_WING_CENTER_Y_OFFSET_5, this);
#ifdef GRIPPER_8
	m_editStickWingCenterYOffset[eGRIPPER_ROW6].SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_STICK_WING_CENTER_Y_OFFSET_6, this);
	m_editStickWingCenterYOffset[eGRIPPER_ROW7].SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_STICK_WING_CENTER_Y_OFFSET_7, this);
	m_editStickWingCenterYOffset[eGRIPPER_ROW8].SubclassDlgItem(IDC_EDIT_MATERIAL_PARA_STICK_WING_CENTER_Y_OFFSET_8, this);
#endif
	return TRUE;
}

BOOL CModelSubMaterialParaDlg::InitPara()
{
	CString Str = _T("");
	int i = 0;

	//Stick Info
	m_editStickSizeX.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_MaterialPara.Info.dStickSizeX));
	m_editStickSizeY.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_MaterialPara.Info.dStickSizeY));
	m_editStickLeftTopX.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_MaterialPara.Info.dStickLeftTopX));
	m_editStickLeftTopY.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_MaterialPara.Info.dStickLeftTopY));
	m_editAlignLeftHoleX.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_MaterialPara.Info.dAlignLeftHoleX));
	m_editAlignLeftHoleY.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_MaterialPara.Info.dAlignLeftHoleY));
	m_editAlignRightHoleX.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_MaterialPara.Info.dAlignRightHoleX));
	m_editAlignRightHoleY.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_MaterialPara.Info.dAlignRightHoleY));
	m_comboHoleShape.SetCurSel(CModelData::m_MaterialPara.Info.nHoleShape);
	m_comboHoleArrange.SetCurSel(CModelData::m_MaterialPara.Info.nHoleArrange);
	m_editAlignHoleSizeX.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_MaterialPara.Info.dAlignHoleSizeX));
	m_editAlignHoleSizeY.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_MaterialPara.Info.dAlignHoleSizeY));
	m_editStickThickness.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_MaterialPara.Info.dStickThickness));
	m_editPaperThickness.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_MaterialPara.Info.dPaperThickness));

	//Cell Info
	m_editCellCountX.SetWindowText(_ToStr(_T("%d"), CModelData::m_MaterialPara.Info.nCellCountX));
	m_editCellCountY.SetWindowText(_ToStr(_T("%d"), CModelData::m_MaterialPara.Info.nCellCountY));
	m_editFirstCellLeftTopX.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_MaterialPara.Info.dFirstCellLeftTopX));
	m_editFirstCellLeftTopY.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_MaterialPara.Info.dFirstCellLeftTopY));
	m_editCellPitchX.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_MaterialPara.Info.dCellPitchX));
	m_editCellPitchY.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_MaterialPara.Info.dCellPitchY));
	
	//m_nSelectCellX = 0;
	//m_nSelectCellY = 0;

	m_comboCellSelectX.ResetContent();
	for (i = 0; i < CModelData::m_MaterialPara.Info.nCellCountX; i++)
	{
		Str.Format(_T("%d"), i + 1);
		m_comboCellSelectX.AddString(Str);
	}
	m_comboCellSelectX.SetCurSel(0);

	m_comboCellSelectY.ResetContent();
	for (i = 0; i < CModelData::m_MaterialPara.Info.nCellCountY; i++)
	{
		Str.Format(_T("%d"), i + 1);
		m_comboCellSelectY.AddString(Str);
	}
	m_comboCellSelectY.SetCurSel(0);

	//Sub Cell Info
	int nCurCellX = 0;
	int nCurCellY = 0;

	m_editCellLeftTopX.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_MaterialPara.Info.dCellLeftTopX[nCurCellX][nCurCellY]));
	m_editCellLeftTopY.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_MaterialPara.Info.dCellLeftTopY[nCurCellX][nCurCellY]));
	m_editCellSizeX.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_MaterialPara.Info.dCellSizeX[nCurCellX][nCurCellY]));
	m_editCellSizeY.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_MaterialPara.Info.dCellSizeY[nCurCellX][nCurCellY]));
	m_comboInspectionSlotCount.SetCurSel(CModelData::m_MaterialPara.Info.nInspectionSlotCount[nCurCellX][nCurCellY]);
	//Slot Info
	m_editSlotCenterShiftX.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_MaterialPara.Info.dSlotCenterShiftX[nCurCellX][nCurCellY]));
	m_editSlotCenterShiftY.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_MaterialPara.Info.dSlotCenterShiftY[nCurCellX][nCurCellY]));
	m_editSlotWidth.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_MaterialPara.Info.dSlotSizeX[nCurCellX][nCurCellY]));
	m_editSlotHeight.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_MaterialPara.Info.dSlotSizeY[nCurCellX][nCurCellY]));
	m_editSlotAngle.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_MaterialPara.Info.dSlotAngle[nCurCellX][nCurCellY]));
	m_editSlotPitchX.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_MaterialPara.Info.dSlotPitchX[nCurCellX][nCurCellY]));
	m_editSlotPitchY.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_MaterialPara.Info.dSlotPitchY[nCurCellX][nCurCellY]));
	m_editSlotTotalPitchX.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_MaterialPara.Info.dSlotTotalPitchX[nCurCellX][nCurCellY]));
	m_editSlotTotalPitchY.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_MaterialPara.Info.dSlotTotalPitchY[nCurCellX][nCurCellY]));
	
	//Cell Info Copy
	//m_nCopySelectSrcX = 0;
	//m_nCopySelectSrcY = 0;
	//m_nCopySelectTargetX = 0;
	//m_nCopySelectTargetY = 0;

	m_comboCellInfoCopySourceX.ResetContent();
	for (i = 0; i < CModelData::m_MaterialPara.Info.nCellCountX; i++)
	{
		Str.Format(_T("%d"), i + 1);
		m_comboCellInfoCopySourceX.AddString(Str);
	}
	m_comboCellInfoCopySourceX.SetCurSel(0);

	m_comboCellInfoCopySourceY.ResetContent();
	for (i = 0; i < CModelData::m_MaterialPara.Info.nCellCountY; i++)
	{
		Str.Format(_T("%d"), i + 1);
		m_comboCellInfoCopySourceY.AddString(Str);
	}
	m_comboCellInfoCopySourceY.SetCurSel(0);

	m_comboCellInfoCopyTargetX.ResetContent();
	for (i = 0; i < CModelData::m_MaterialPara.Info.nCellCountX; i++)
	{
		Str.Format(_T("%d"), i + 1);
		m_comboCellInfoCopyTargetX.AddString(Str);
	}
	m_comboCellInfoCopyTargetX.SetCurSel(0);

	m_comboCellInfoCopyTargetY.ResetContent();
	for (i = 0; i < CModelData::m_MaterialPara.Info.nCellCountY; i++)
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
	m_editTegkey_LT_X.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_MaterialPara.Info.dTegkey_LT_X));
	m_editTegkey_LT_Y.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_MaterialPara.Info.dTegkey_LT_Y));
	m_editTegkey_LB_X.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_MaterialPara.Info.dTegkey_LB_X));
	m_editTegkey_LB_Y.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_MaterialPara.Info.dTegkey_LB_Y));
	m_editTegkey_RT_X.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_MaterialPara.Info.dTegkey_RT_X));
	m_editTegkey_RT_Y.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_MaterialPara.Info.dTegkey_RT_Y));
	m_editTegkey_RB_X.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_MaterialPara.Info.dTegkey_RB_X));
	m_editTegkey_RB_Y.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_MaterialPara.Info.dTegkey_RB_Y));
	m_editTegkey_SizeX.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_MaterialPara.Info.dTegkey_SizeX));
	m_editTegkey_SizeY.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_MaterialPara.Info.dTegkey_SizeY));

	//Stick Wing Y Offset
	for (i = 0; i < eGRIPPER_ROW_MAX; i++)
	{
		m_editStickWingCenterYOffset[i].SetWindowText(_ToStr(_T("%.5f"), CModelData::m_MaterialPara.Info.dStickWingCenterYOffset[i]));
	}

	return TRUE;
}

BOOL CModelSubMaterialParaDlg::CheckChangeData()
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

	m_editFirstCellLeftTopX.GetWindowText(Str); if (_ttof(Str) >= 0) { AfxMessageBox(_T("FirstCell LTX Invalid !! (Cur >= 0)")); return FALSE; }
	m_editFirstCellLeftTopY.GetWindowText(Str); if (_ttof(Str) <= 0) { AfxMessageBox(_T("FirstCell LTY Invalid !! (Cur <= 0)")); return FALSE; }
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

	//Tegkey Info
	m_editTegkey_LT_X.GetWindowText(Str); if (_ttof(Str) > 0) { AfxMessageBox(_T("Tegkey LT_X Invalid !! (Cur > 0)")); return FALSE; }
	m_editTegkey_LB_X.GetWindowText(Str); if (_ttof(Str) > 0) { AfxMessageBox(_T("Tegkey LB_X Invalid !! (Cur > 0)")); return FALSE; }
	m_editTegkey_RT_X.GetWindowText(Str); if (_ttof(Str) < 0) { AfxMessageBox(_T("Tegkey RT_X Invalid !! (Cur < 0)")); return FALSE; }
	m_editTegkey_RB_X.GetWindowText(Str); if (_ttof(Str) < 0) { AfxMessageBox(_T("Tegkey RT_X Invalid !! (Cur < 0)")); return FALSE; }
#pragma endregion

	//Stick Info
	m_editStickSizeX.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.dStickSizeX = _ttof(Str);
	m_editStickSizeY.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.dStickSizeY = _ttof(Str);
	m_editStickLeftTopX.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.dStickLeftTopX = _ttof(Str);
	m_editStickLeftTopY.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.dStickLeftTopY = _ttof(Str);
	m_editAlignLeftHoleX.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.dAlignLeftHoleX = _ttof(Str);
	m_editAlignLeftHoleY.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.dAlignLeftHoleY = _ttof(Str);
	m_editAlignRightHoleX.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.dAlignRightHoleX = _ttof(Str);
	m_editAlignRightHoleY.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.dAlignRightHoleY = _ttof(Str);
	CModelData::m_MaterialPara.Info.nHoleShape = m_comboHoleShape.GetCurSel();
	CModelData::m_MaterialPara.Info.nHoleArrange = m_comboHoleArrange.GetCurSel();
	m_editAlignHoleSizeX.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.dAlignHoleSizeX = _ttof(Str);
	m_editAlignHoleSizeY.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.dAlignHoleSizeY = _ttof(Str);
	m_editStickThickness.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.dStickThickness = _ttof(Str);
	m_editPaperThickness.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.dPaperThickness = _ttof(Str);

	//Cell Info
	m_editCellCountX.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.nCellCountX = _ttoi(Str);
	m_editCellCountY.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.nCellCountY = _ttoi(Str);
	m_editFirstCellLeftTopX.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.dFirstCellLeftTopX = _ttof(Str);
	m_editFirstCellLeftTopY.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.dFirstCellLeftTopY = _ttof(Str);
	m_editCellPitchX.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.dCellPitchX = _ttof(Str);
	m_editCellPitchY.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.dCellPitchY = _ttof(Str);

	//Sub Cell Info
	m_editCellLeftTopX.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.dCellLeftTopX[nCurCellX][nCurCellY] = _ttof(Str);
	m_editCellLeftTopY.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.dCellLeftTopY[nCurCellX][nCurCellY] = _ttof(Str);
	m_editCellSizeX.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.dCellSizeX[nCurCellX][nCurCellY] = _ttof(Str);
	m_editCellSizeY.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.dCellSizeY[nCurCellX][nCurCellY] = _ttof(Str);
	CModelData::m_MaterialPara.Info.nInspectionSlotCount[nCurCellX][nCurCellY] = m_comboInspectionSlotCount.GetCurSel();

	//Slot Info
	m_editSlotCenterShiftX.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.dSlotCenterShiftX[nCurCellX][nCurCellY] = _ttof(Str);
	m_editSlotCenterShiftY.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.dSlotCenterShiftY[nCurCellX][nCurCellY] = _ttof(Str);
	m_editSlotWidth.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.dSlotSizeX[nCurCellX][nCurCellY] = _ttof(Str);
	m_editSlotHeight.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.dSlotSizeY[nCurCellX][nCurCellY] = _ttof(Str);
	m_editSlotAngle.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.dSlotAngle[nCurCellX][nCurCellY] = _ttof(Str);
	m_editSlotPitchX.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.dSlotPitchX[nCurCellX][nCurCellY] = _ttof(Str);
	m_editSlotPitchY.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.dSlotPitchY[nCurCellX][nCurCellY] = _ttof(Str);
	m_editSlotTotalPitchX.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.dSlotTotalPitchX[nCurCellX][nCurCellY] = _ttof(Str);
	m_editSlotTotalPitchY.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.dSlotTotalPitchY[nCurCellX][nCurCellY] = _ttof(Str);

	//Tegkey Info
	m_editTegkey_LT_X.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.dTegkey_LT_X = _ttof(Str);
	m_editTegkey_LT_Y.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.dTegkey_LT_Y = _ttof(Str);
	m_editTegkey_LB_X.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.dTegkey_LB_X = _ttof(Str);
	m_editTegkey_LB_Y.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.dTegkey_LB_Y = _ttof(Str);
	m_editTegkey_RT_X.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.dTegkey_RT_X = _ttof(Str);
	m_editTegkey_RT_Y.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.dTegkey_RT_Y = _ttof(Str);
	m_editTegkey_RB_X.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.dTegkey_RB_X = _ttof(Str);
	m_editTegkey_RB_Y.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.dTegkey_RB_Y = _ttof(Str);
	m_editTegkey_SizeX.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.dTegkey_SizeX = _ttof(Str);
	m_editTegkey_SizeY.GetWindowText(Str);
	CModelData::m_MaterialPara.Info.dTegkey_SizeY = _ttof(Str);
	
	//Stick Skirt Y Offset
	for (int i = 0; i < eGRIPPER_ROW_MAX; i++)
	{
		m_editStickWingCenterYOffset[i].GetWindowText(Str);
		CModelData::m_MaterialPara.Info.dStickWingCenterYOffset[i] = _ttof(Str);
	}

	return TRUE;
}

BOOL CModelSubMaterialParaDlg::SavePara()
{
	CheckChangeData();

	BOOL bRtn = CModelData::m_MaterialPara.Save();
	if (bRtn == TRUE)
		AfxMessageBox(_T("Save Ok"));
	else
		AfxMessageBox(_T("Save Fail !!"));

	return TRUE;
}

void CModelSubMaterialParaDlg::OnShowWindow(BOOL bShow, UINT nStatus)
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

void CModelSubMaterialParaDlg::BtnEnable(BOOL bEnable)
{
	int i = 0;

	if (bEnable)
	{
	}
	else
	{
	}
}


void CModelSubMaterialParaDlg::OnCbnSelchangeComboMaterialParaCellSelectNoX()
{
	SelectedCellChange();
}


void CModelSubMaterialParaDlg::OnCbnSelchangeComboMaterialParaCellSelectNoY()
{
	SelectedCellChange();
}

void CModelSubMaterialParaDlg::SelectedCellChange()
{
	//m_nSelectCellX = m_comboCellSelectX.GetCurSel();
	//m_nSelectCellY = m_comboCellSelectY.GetCurSel();

	int nCurCellX = m_comboCellSelectX.GetCurSel();
	int nCurCellY = m_comboCellSelectY.GetCurSel();

	//Sub Cell Info
	m_editCellLeftTopX.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_MaterialPara.Info.dCellLeftTopX[nCurCellX][nCurCellY]));
	m_editCellLeftTopY.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_MaterialPara.Info.dCellLeftTopY[nCurCellX][nCurCellY]));
	m_editCellSizeX.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_MaterialPara.Info.dCellSizeX[nCurCellX][nCurCellY]));
	m_editCellSizeY.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_MaterialPara.Info.dCellSizeY[nCurCellX][nCurCellY]));
	m_comboInspectionSlotCount.SetCurSel(CModelData::m_MaterialPara.Info.nInspectionSlotCount[nCurCellX][nCurCellY]);
	//Slot Info
	m_editSlotCenterShiftX.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_MaterialPara.Info.dSlotCenterShiftX[nCurCellX][nCurCellY]));
	m_editSlotCenterShiftY.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_MaterialPara.Info.dSlotCenterShiftY[nCurCellX][nCurCellY]));
	m_editSlotWidth.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_MaterialPara.Info.dSlotSizeX[nCurCellX][nCurCellY]));
	m_editSlotHeight.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_MaterialPara.Info.dSlotSizeY[nCurCellX][nCurCellY]));
	m_editSlotAngle.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_MaterialPara.Info.dSlotAngle[nCurCellX][nCurCellY]));
	m_editSlotPitchX.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_MaterialPara.Info.dSlotPitchX[nCurCellX][nCurCellY]));
	m_editSlotPitchY.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_MaterialPara.Info.dSlotPitchY[nCurCellX][nCurCellY]));
	m_editSlotTotalPitchX.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_MaterialPara.Info.dSlotTotalPitchX[nCurCellX][nCurCellY]));
	m_editSlotTotalPitchY.SetWindowText(_ToStr(_T("%.10f"), CModelData::m_MaterialPara.Info.dSlotTotalPitchY[nCurCellX][nCurCellY]));
}


void CModelSubMaterialParaDlg::OnBnClickedBtnMaterialCellInfoCopy()
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

	//CModelData::m_MaterialPara.Info.dCellLeftTopX[nTargetX][nTargetY] = CModelData::m_MaterialPara.Info.dCellLeftTopX[nSrcX][nSrcY];
	//CModelData::m_MaterialPara.Info.dCellLeftTopY[nTargetX][nTargetY] = CModelData::m_MaterialPara.Info.dCellLeftTopY[nSrcX][nSrcY];

	CModelData::m_MaterialPara.Info.dCellSizeX[nTargetX][nTargetY] = CModelData::m_MaterialPara.Info.dCellSizeX[nSrcX][nSrcY];
	CModelData::m_MaterialPara.Info.dCellSizeY[nTargetX][nTargetY] = CModelData::m_MaterialPara.Info.dCellSizeY[nSrcX][nSrcY];

	CModelData::m_MaterialPara.Info.nInspectionSlotCount[nTargetX][nTargetY] = CModelData::m_MaterialPara.Info.nInspectionSlotCount[nSrcX][nSrcY];

	CModelData::m_MaterialPara.Info.dSlotCenterShiftX[nTargetX][nTargetY] = CModelData::m_MaterialPara.Info.dSlotCenterShiftX[nSrcX][nSrcY];
	CModelData::m_MaterialPara.Info.dSlotCenterShiftY[nTargetX][nTargetY] = CModelData::m_MaterialPara.Info.dSlotCenterShiftY[nSrcX][nSrcY];

	CModelData::m_MaterialPara.Info.dSlotSizeX[nTargetX][nTargetY] = CModelData::m_MaterialPara.Info.dSlotSizeX[nSrcX][nSrcY];
	CModelData::m_MaterialPara.Info.dSlotSizeY[nTargetX][nTargetY] = CModelData::m_MaterialPara.Info.dSlotSizeY[nSrcX][nSrcY];

	CModelData::m_MaterialPara.Info.dSlotAngle[nTargetX][nTargetY] = CModelData::m_MaterialPara.Info.dSlotAngle[nSrcX][nSrcY];

	CModelData::m_MaterialPara.Info.dSlotPitchX[nTargetX][nTargetY] = CModelData::m_MaterialPara.Info.dSlotPitchX[nSrcX][nSrcY];
	CModelData::m_MaterialPara.Info.dSlotPitchY[nTargetX][nTargetY] = CModelData::m_MaterialPara.Info.dSlotPitchY[nSrcX][nSrcY];

	CModelData::m_MaterialPara.Info.dSlotTotalPitchX[nTargetX][nTargetY] = CModelData::m_MaterialPara.Info.dSlotTotalPitchX[nSrcX][nSrcY];
	CModelData::m_MaterialPara.Info.dSlotTotalPitchY[nTargetX][nTargetY] = CModelData::m_MaterialPara.Info.dSlotTotalPitchY[nSrcX][nSrcY];

	Str.Format(_T("Material Para Data Copy Cell : %d, %d -> %d, %d"), nSrcX + 1, nSrcY + 1, nTargetX + 1, nTargetY + 1);
	Total_Msg(Str);

	m_comboCellSelectX.SetCurSel(nTargetX);
	m_comboCellSelectY.SetCurSel(nTargetY);
}

void CModelSubMaterialParaDlg::OnBnClickedBtnMaterialCellInfoCopyAll() //KJT 20210301
{
	CString Str = _T("");

	int nSrcX = m_comboCellInfoCopySourceX.GetCurSel();
	int nSrcY = m_comboCellInfoCopySourceY.GetCurSel();

	Str.Format(_T("Cell Info Copy %d, %d -> All ?"), nSrcX + 1, nSrcY + 1);
	if (IDYES != AfxMessageBox(Str, MB_YESNO))
		return;

	for (int i = 0; i < CModelData::m_MaterialPara.Info.nCellCountX; i++)
	{
		for (int j = 0; j < CModelData::m_MaterialPara.Info.nCellCountY; j++)
		{
			if (i == nSrcX && j == nSrcY)
				continue;

			//CModelData::m_MaterialPara.Info.dCellLeftTopX[i][j] = CModelData::m_MaterialPara.Info.dCellLeftTopX[nSrcX][nSrcY];
			//CModelData::m_MaterialPara.Info.dCellLeftTopY[i][j] = CModelData::m_MaterialPara.Info.dCellLeftTopY[nSrcX][nSrcY];

			CModelData::m_MaterialPara.Info.dCellSizeX[i][j] = CModelData::m_MaterialPara.Info.dCellSizeX[nSrcX][nSrcY];
			CModelData::m_MaterialPara.Info.dCellSizeY[i][j] = CModelData::m_MaterialPara.Info.dCellSizeY[nSrcX][nSrcY];

			CModelData::m_MaterialPara.Info.nInspectionSlotCount[i][j] = CModelData::m_MaterialPara.Info.nInspectionSlotCount[nSrcX][nSrcY];

			CModelData::m_MaterialPara.Info.dSlotCenterShiftX[i][j] = CModelData::m_MaterialPara.Info.dSlotCenterShiftX[nSrcX][nSrcY];
			CModelData::m_MaterialPara.Info.dSlotCenterShiftY[i][j] = CModelData::m_MaterialPara.Info.dSlotCenterShiftY[nSrcX][nSrcY];

			CModelData::m_MaterialPara.Info.dSlotSizeX[i][j] = CModelData::m_MaterialPara.Info.dSlotSizeX[nSrcX][nSrcY];
			CModelData::m_MaterialPara.Info.dSlotSizeY[i][j] = CModelData::m_MaterialPara.Info.dSlotSizeY[nSrcX][nSrcY];

			CModelData::m_MaterialPara.Info.dSlotAngle[i][j] = CModelData::m_MaterialPara.Info.dSlotAngle[nSrcX][nSrcY];

			CModelData::m_MaterialPara.Info.dSlotPitchX[i][j] = CModelData::m_MaterialPara.Info.dSlotPitchX[nSrcX][nSrcY];
			CModelData::m_MaterialPara.Info.dSlotPitchY[i][j] = CModelData::m_MaterialPara.Info.dSlotPitchY[nSrcX][nSrcY];

			CModelData::m_MaterialPara.Info.dSlotTotalPitchX[i][j] = CModelData::m_MaterialPara.Info.dSlotTotalPitchX[nSrcX][nSrcY];
			CModelData::m_MaterialPara.Info.dSlotTotalPitchY[i][j] = CModelData::m_MaterialPara.Info.dSlotTotalPitchY[nSrcX][nSrcY];
		}
	}

	Str.Format(_T("Material Para Data Copy Cell : %d, %d -> All"), nSrcX + 1, nSrcY + 1);
	Total_Msg(Str);
}

