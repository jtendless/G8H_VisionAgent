// AlignPara2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentDlg.h"
#include "AlignPara2Dlg.h"
#include "Vision/SharedInfo.h"
#include "afxdialogex.h"


// CAlignPara2Dlg dialog

IMPLEMENT_DYNAMIC(CAlignPara2Dlg, CDialogEx)

CAlignPara2Dlg::CAlignPara2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MODEL_SUB_ALIGN_PARA2_DIALOG, pParent)
{
	Create(IDD_MODEL_SUB_ALIGN_PARA2_DIALOG, pParent);
}

CAlignPara2Dlg::~CAlignPara2Dlg()
{
}

void CAlignPara2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAlignPara2Dlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BTN_VERTICAL_PRE_ALIGN_LIGHT_ON, &CAlignPara2Dlg::OnBnClickedBtnVerticalPreAlignLightOn)
	ON_BN_CLICKED(IDC_BTN_VERTICAL_PRE_ALIGN_LIGHT_OFF, &CAlignPara2Dlg::OnBnClickedBtnVerticalPreAlignLightOff)
	ON_BN_CLICKED(IDC_BTN_VERTICAL_MAIN_ALIGN_LIGHT_ON, &CAlignPara2Dlg::OnBnClickedBtnVerticalMainAlignLightOn)
	ON_BN_CLICKED(IDC_BTN_VERTICAL_MAIN_ALIGN_LIGHT_OFF, &CAlignPara2Dlg::OnBnClickedBtnVerticalMainAlignLightOff)
	ON_BN_CLICKED(IDC_BTN_SW_ALIGN_LIGHT_ON, &CAlignPara2Dlg::OnBnClickedBtnSwAlignLightOn)
	ON_BN_CLICKED(IDC_BTN_SW_ALIGN_LIGHT_OFF, &CAlignPara2Dlg::OnBnClickedBtnSwAlignLightOff)
	ON_BN_CLICKED(IDC_BTN_MEASURE_HALF_EDGE_HOLE_LIGHT_ON, &CAlignPara2Dlg::OnBnClickedBtnTPLightOn)
	ON_BN_CLICKED(IDC_BTN_MEASURE_HALF_EDGE_HOLE_LIGHT_OFF, &CAlignPara2Dlg::OnBnClickedBtnTPLightOff)
	ON_BN_CLICKED(IDC_BTN_MEASURE_HALF_EDGE_HOLE_LIGHT_ON2, &CAlignPara2Dlg::OnBnClickedBtnMeasureHalfEdgeHoleLightOn2)
	ON_BN_CLICKED(IDC_BTN_MEASURE_HALF_EDGE_HOLE_LIGHT_ON3, &CAlignPara2Dlg::OnBnClickedBtnMeasureHalfEdgeHoleLightOn3)
END_MESSAGE_MAP()


// CAlignPara2Dlg message handlers

BOOL CAlignPara2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitCtrl();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CAlignPara2Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();
}

BOOL CAlignPara2Dlg::InitCtrl()
{
#pragma region //Vertical Pre Align
	m_editVerticalPreAlignTargetCount.SubclassDlgItem(IDC_EDIT_VERTICAL_PRE_ALIGN_TARGET_COUNT, this);
	m_editVerticalPreAlignTargetX.SubclassDlgItem(IDC_EDIT_VERTICAL_PRE_ALIGN_TRAGET_X, this);
	m_editVerticalPreAlignTargetY.SubclassDlgItem(IDC_EDIT_VERTICAL_PRE_ALIGN_TRAGET_Y, this);
	m_editVerticalPreAlignCoAxial.SubclassDlgItem(IDC_EDIT_VERTICAL_PRE_ALIGN_COAXIAL, this);
	m_editVerticalPreAlignRing.SubclassDlgItem(IDC_EDIT_VERTICAL_PRE_ALIGN_RING, this);
	m_editVerticalPreAlignThreshold.SubclassDlgItem(IDC_EDIT_VERTICAL_PRE_ALIGN_THRESHOLD, this);
	m_editVerticalPreAlignBackLight.SubclassDlgItem(IDC_EDIT_VERTICAL_PRE_ALIGN_BACKLIGHT, this);

	m_comboVerticalPreAlignLightType.SubclassDlgItem(IDC_COMBO_VERTICAL_PRE_ALIGN_LIGHT_TYPE, this);
	m_comboVerticalPreAlignLightType.ResetContent();
	m_comboVerticalPreAlignLightType.AddString(_T("Front"));
	m_comboVerticalPreAlignLightType.AddString(_T("Back"));
	m_comboVerticalPreAlignLightType.SetCurSel(0);

	m_comboVerticalPreAlignMarkType.SubclassDlgItem(IDC_COMBO_VERTICAL_PRE_ALIGN_MARK_TYPE, this);
	m_comboVerticalPreAlignMarkType.ResetContent();
	m_comboVerticalPreAlignMarkType.AddString(_T("Blob"));
	m_comboVerticalPreAlignMarkType.AddString(_T("Pattern"));
	m_comboVerticalPreAlignMarkType.SetCurSel(0);

	m_comboVerticalPreAlignFocusType.SubclassDlgItem(IDC_COMBO_VERTICAL_PRE_ALIGN_FOCUS_TYPE, this);
	m_comboVerticalPreAlignFocusType.ResetContent();
	m_comboVerticalPreAlignFocusType.AddString(_T("None"));
	m_comboVerticalPreAlignFocusType.AddString(_T("Laser"));
	m_comboVerticalPreAlignFocusType.AddString(_T("Image"));
	m_comboVerticalPreAlignFocusType.AddString(_T("Both"));
	m_comboVerticalPreAlignFocusType.SetCurSel(0);

	m_comboVerticalPreAlignBlackWhiteType.SubclassDlgItem(IDC_COMBO_VERTICAL_PRE_ALIGN_BLACK_WHITE_TYPE, this);
	m_comboVerticalPreAlignBlackWhiteType.ResetContent();
	m_comboVerticalPreAlignBlackWhiteType.AddString(_T("Black"));
	m_comboVerticalPreAlignBlackWhiteType.AddString(_T("White"));
	m_comboVerticalPreAlignBlackWhiteType.SetCurSel(0);

	m_btnVerticalPreAlignLightOn.SubclassDlgItem(IDC_BTN_VERTICAL_PRE_ALIGN_LIGHT_ON, this);
	m_btnVerticalPreAlignLightOff.SubclassDlgItem(IDC_BTN_VERTICAL_PRE_ALIGN_LIGHT_OFF, this);
#pragma endregion

#pragma region //Vertical Main Align
	m_editVerticalMainAlignTargetCount.SubclassDlgItem(IDC_EDIT_VERTICAL_MAIN_ALIGN_TARGET_COUNT, this);
	m_editVerticalMainAlignTargetX.SubclassDlgItem(IDC_EDIT_VERTICAL_MAIN_ALIGN_TRAGET_X, this);
	m_editVerticalMainAlignTargetY.SubclassDlgItem(IDC_EDIT_VERTICAL_MAIN_ALIGN_TRAGET_Y, this);
	m_editVerticalMainAlignCoAxial.SubclassDlgItem(IDC_EDIT_VERTICAL_MAIN_ALIGN_COAXIAL, this);
	m_editVerticalMainAlignRing.SubclassDlgItem(IDC_EDIT_VERTICAL_MAIN_ALIGN_RING, this);
	m_editVerticalMainAlignThreshold.SubclassDlgItem(IDC_EDIT_VERTICAL_MAIN_ALIGN_THRESHOLD, this);
	m_editVerticalMainAlignBackLight.SubclassDlgItem(IDC_EDIT_VERTICAL_MAIN_ALIGN_BACKLIGHT, this);

	m_comboVerticalMainAlignLightType.SubclassDlgItem(IDC_COMBO_VERTICAL_MAIN_ALIGN_LIGHT_TYPE, this);
	m_comboVerticalMainAlignLightType.ResetContent();
	m_comboVerticalMainAlignLightType.AddString(_T("Front"));
	m_comboVerticalMainAlignLightType.AddString(_T("Back"));
	m_comboVerticalMainAlignLightType.SetCurSel(0);

	m_comboVerticalMainAlignMarkType.SubclassDlgItem(IDC_COMBO_VERTICAL_MAIN_ALIGN_MARK_TYPE, this);
	m_comboVerticalMainAlignMarkType.ResetContent();
	m_comboVerticalMainAlignMarkType.AddString(_T("Blob"));
	m_comboVerticalMainAlignMarkType.AddString(_T("Pattern"));
	m_comboVerticalMainAlignMarkType.SetCurSel(0);

	m_comboVerticalMainAlignFocusType.SubclassDlgItem(IDC_COMBO_VERTICAL_MAIN_ALIGN_FOCUS_TYPE, this);
	m_comboVerticalMainAlignFocusType.ResetContent();
	m_comboVerticalMainAlignFocusType.AddString(_T("None"));
	m_comboVerticalMainAlignFocusType.AddString(_T("Laser"));
	m_comboVerticalMainAlignFocusType.AddString(_T("Image"));
	m_comboVerticalMainAlignFocusType.AddString(_T("Both"));
	m_comboVerticalMainAlignFocusType.SetCurSel(0);

	m_comboVerticalMainAlignBlackWhiteType.SubclassDlgItem(IDC_COMBO_VERTICAL_MAIN_ALIGN_BLACK_WHITE_TYPE, this);
	m_comboVerticalMainAlignBlackWhiteType.ResetContent();
	m_comboVerticalMainAlignBlackWhiteType.AddString(_T("Black"));
	m_comboVerticalMainAlignBlackWhiteType.AddString(_T("White"));
	m_comboVerticalMainAlignBlackWhiteType.SetCurSel(0);

	m_btnVerticalMainAlignLightOn.SubclassDlgItem(IDC_BTN_VERTICAL_MAIN_ALIGN_LIGHT_ON, this);
	m_btnVerticalMainAlignLightOff.SubclassDlgItem(IDC_BTN_VERTICAL_MAIN_ALIGN_LIGHT_OFF, this);
#pragma endregion

#pragma region //Sw Align
	m_editSwAlignTargetCount.SubclassDlgItem(IDC_EDIT_SW_ALIGN_TARGET_COUNT, this);
	m_editSwAlignTargetX.SubclassDlgItem(IDC_EDIT_SW_ALIGN_TRAGET_X, this);
	m_editSwAlignTargetY.SubclassDlgItem(IDC_EDIT_SW_ALIGN_TRAGET_Y, this);
	m_editSwAlignCoAxial.SubclassDlgItem(IDC_EDIT_SW_ALIGN_COAXIAL, this);
	m_editSwAlignRing.SubclassDlgItem(IDC_EDIT_SW_ALIGN_RING, this);
	m_editSwAlignThreshold.SubclassDlgItem(IDC_EDIT_SW_ALIGN_THRESHOLD, this);
	m_editSwAlignBacklight.SubclassDlgItem(IDC_EDIT_SW_ALIGN_BACKLIGHT, this);

	m_comboSwAlignLightType.SubclassDlgItem(IDC_COMBO_SW_ALIGN_LIGHT_TYPE, this);
	m_comboSwAlignLightType.ResetContent();
	m_comboSwAlignLightType.AddString(_T("Front"));
	m_comboSwAlignLightType.AddString(_T("Back"));
	m_comboSwAlignLightType.SetCurSel(0);

	m_comboSwAlignMarkType.SubclassDlgItem(IDC_COMBO_SW_ALIGN_MARK_TYPE, this);
	m_comboSwAlignMarkType.ResetContent();
	m_comboSwAlignMarkType.AddString(_T("Blob"));
	m_comboSwAlignMarkType.AddString(_T("Pattern"));
	m_comboSwAlignMarkType.SetCurSel(0);

	m_comboSwAlignFocusType.SubclassDlgItem(IDC_COMBO_SW_ALIGN_FOCUS_TYPE, this);
	m_comboSwAlignFocusType.ResetContent();
	m_comboSwAlignFocusType.AddString(_T("None")); //KJT 20210305
	m_comboSwAlignFocusType.AddString(_T("Laser"));
	m_comboSwAlignFocusType.AddString(_T("Image"));
	m_comboSwAlignFocusType.AddString(_T("Both"));
	m_comboSwAlignFocusType.SetCurSel(0);

	m_comboSwAlignBlackWhiteType.SubclassDlgItem(IDC_COMBO_SW_ALIGN_BLACK_WHITE_TYPE, this);
	m_comboSwAlignBlackWhiteType.ResetContent();
	m_comboSwAlignBlackWhiteType.AddString(_T("Black"));
	m_comboSwAlignBlackWhiteType.AddString(_T("White"));
	m_comboSwAlignBlackWhiteType.SetCurSel(0);

	m_btnSwAlignLightOn.SubclassDlgItem(IDC_BTN_SW_ALIGN_LIGHT_ON, this);
	m_btnSwAlignLightOff.SubclassDlgItem(IDC_BTN_SW_ALIGN_LIGHT_OFF, this);
#pragma endregion

#pragma region //Measure Half Edge Hole //KJT 20210416
	m_editTPCoAxial[0].SubclassDlgItem(IDC_EDIT_MEASURE_HALF_EDGE_HOLE_COAXIAL, this);
	m_editTPRing[0].SubclassDlgItem(IDC_EDIT_MEASURE_HALF_EDGE_HOLE_RING, this);
	m_editTPThreshold[0].SubclassDlgItem(IDC_EDIT_MEASURE_HALF_EDGE_HOLE_THRESHOLD, this);
	m_editTPBacklight[0].SubclassDlgItem(IDC_EDIT_MEASURE_HALF_EDGE_HOLE_BACKLIGHT, this);

	m_editTPCoAxial[1].SubclassDlgItem(IDC_EDIT_MEASURE_HALF_EDGE_HOLE_COAXIAL2, this);
	m_editTPRing[1].SubclassDlgItem(IDC_EDIT_MEASURE_HALF_EDGE_HOLE_RING2, this);
	m_editTPThreshold[1].SubclassDlgItem(IDC_EDIT_MEASURE_HALF_EDGE_HOLE_THRESHOLD2, this);
	m_editTPBacklight[1].SubclassDlgItem(IDC_EDIT_MEASURE_HALF_EDGE_HOLE_BACKLIGHT2, this);

	m_editTPCoAxial[2].SubclassDlgItem(IDC_EDIT_MEASURE_HALF_EDGE_HOLE_COAXIAL3, this);
	m_editTPRing[2].SubclassDlgItem(IDC_EDIT_MEASURE_HALF_EDGE_HOLE_RING3, this);
	m_editTPThreshold[2].SubclassDlgItem(IDC_EDIT_MEASURE_HALF_EDGE_HOLE_THRESHOLD3, this);
	m_editTPBacklight[2].SubclassDlgItem(IDC_EDIT_MEASURE_HALF_EDGE_HOLE_BACKLIGHT3, this);

	m_comboTPLightType.SubclassDlgItem(IDC_COMBO_MEASURE_HALF_EDGE_HOLE_LIGHT_TYPE, this);
	m_comboTPLightType.ResetContent();
	m_comboTPLightType.AddString(_T("Front"));
	m_comboTPLightType.AddString(_T("Back"));
	m_comboTPLightType.SetCurSel(0);

	m_comboTPMarkType.SubclassDlgItem(IDC_COMBO_MEASURE_HALF_EDGE_HOLE_MARK_TYPE, this);
	m_comboTPMarkType.ResetContent();
	m_comboTPMarkType.AddString(_T("Blob"));
	m_comboTPMarkType.AddString(_T("Pattern"));
	m_comboTPMarkType.SetCurSel(0);

	m_comboTPFocusType.SubclassDlgItem(IDC_COMBO_MEASURE_HALF_EDGE_HOLE_FOCUS_TYPE, this);
	m_comboTPFocusType.ResetContent();
	m_comboTPFocusType.AddString(_T("None")); //KJT 20210305
	m_comboTPFocusType.AddString(_T("Laser"));
	m_comboTPFocusType.AddString(_T("Image"));
	m_comboTPFocusType.AddString(_T("Both"));
	m_comboTPFocusType.SetCurSel(0);

	m_comboTPBlackWhiteType.SubclassDlgItem(IDC_COMBO_MEASURE_HALF_EDGE_HOLE_BLACK_WHITE_TYPE, this);
	m_comboTPBlackWhiteType.ResetContent();
	m_comboTPBlackWhiteType.AddString(_T("Black"));
	m_comboTPBlackWhiteType.AddString(_T("White"));
	m_comboTPBlackWhiteType.SetCurSel(0);

	m_btnTPLightOn.SubclassDlgItem(IDC_BTN_MEASURE_HALF_EDGE_HOLE_LIGHT_ON, this);
	m_btnTPLightOff.SubclassDlgItem(IDC_BTN_MEASURE_HALF_EDGE_HOLE_LIGHT_OFF, this);
#pragma endregion

#pragma region //light ratio
	m_editx20CoAxial.SubclassDlgItem(IDC_EDIT_X20_COAXIAL_RATIO, this);
	m_editx20Ring.SubclassDlgItem(IDC_EDIT_X20_RING_RATIO, this);
	m_editx20BackLight.SubclassDlgItem(IDC_EDIT_X20_BACKLIGHT_RATIO, this);

	m_editx50CoAxial.SubclassDlgItem(IDC_EDIT_X50_COAXIAL_RATIO, this);
	m_editx50Ring.SubclassDlgItem(IDC_EDIT_X50_RING_RATIO, this);
	m_editx50BackLight.SubclassDlgItem(IDC_EDIT_X50_BACKLIGHT_RATIO, this);
#pragma endregion

	return TRUE;
}

BOOL CAlignPara2Dlg::InitPara()
{
	int i = 0;

	//Vertical Pre Align
	m_editVerticalPreAlignTargetCount.SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nVerticalPreAlignTargetCount));
	m_editVerticalPreAlignTargetX.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_AlignPara.Info.dVerticalPreAlignTargetX));
	m_editVerticalPreAlignTargetY.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_AlignPara.Info.dVerticalPreAlignTargetY));
	m_editVerticalPreAlignCoAxial.SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nVerticalPreAlignCoAxial));
	m_editVerticalPreAlignRing.SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nVerticalPreAlignRing));
	m_editVerticalPreAlignThreshold.SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nVerticalPreAlignThreshold));
	m_editVerticalPreAlignBackLight.SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nVerticalPreAlignBackLight));

	m_comboVerticalPreAlignLightType.SetCurSel(CModelData::m_AlignPara.Info.nVerticalPreAlignLightType);
	m_comboVerticalPreAlignMarkType.SetCurSel(CModelData::m_AlignPara.Info.nVerticalPreAlignMarkType);
	m_comboVerticalPreAlignFocusType.SetCurSel(CModelData::m_AlignPara.Info.nVerticalPreAlignFocusType);
	m_comboVerticalPreAlignBlackWhiteType.SetCurSel(CModelData::m_AlignPara.Info.nVerticalPreAlignBlackWhiteType);

	//Vertical Main Align
	m_editVerticalMainAlignTargetCount.SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nVerticalMainAlignTargetCount));
	m_editVerticalMainAlignTargetX.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_AlignPara.Info.dVerticalMainAlignTargetX));
	m_editVerticalMainAlignTargetY.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_AlignPara.Info.dVerticalMainAlignTargetY));
	m_editVerticalMainAlignCoAxial.SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nVerticalMainAlignCoAxial));
	m_editVerticalMainAlignRing.SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nVerticalMainAlignRing));
	m_editVerticalMainAlignThreshold.SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nVerticalMainAlignThreshold));
	m_editVerticalMainAlignBackLight.SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nVerticalMainAlignBackLight));

	m_comboVerticalMainAlignLightType.SetCurSel(CModelData::m_AlignPara.Info.nVerticalMainAlignLightType);
	m_comboVerticalMainAlignMarkType.SetCurSel(CModelData::m_AlignPara.Info.nVerticalMainAlignMarkType);
	m_comboVerticalMainAlignFocusType.SetCurSel(CModelData::m_AlignPara.Info.nVerticalMainAlignFocusType);
	m_comboVerticalMainAlignBlackWhiteType.SetCurSel(CModelData::m_AlignPara.Info.nVerticalMainAlignBlackWhiteType);

	//SwAlign //KJT 20210307
	m_editSwAlignTargetCount.SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nSwAlignTargetCount));
	m_editSwAlignTargetX.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_AlignPara.Info.dSwAlignTargetX));
	m_editSwAlignTargetY.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_AlignPara.Info.dSwAlignTargetY));
	m_editSwAlignCoAxial.SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nSwAlignCoAxial));
	m_editSwAlignRing.SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nSwAlignRing));
	m_editSwAlignThreshold.SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nSwAlignThreshold));
	m_editSwAlignBacklight.SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nSwAlignBacklight));
	m_comboSwAlignLightType.SetCurSel(CModelData::m_AlignPara.Info.nSwAlignLightType);
	m_comboSwAlignMarkType.SetCurSel(CModelData::m_AlignPara.Info.nSwAlignMarkType);
	m_comboSwAlignFocusType.SetCurSel(CModelData::m_AlignPara.Info.nSwAlignFocusType);
	m_comboSwAlignBlackWhiteType.SetCurSel(CModelData::m_AlignPara.Info.nSwAlignBlackWhiteType);

	//Measure TP
	for (i = 0; i < 3; i++) //KJT 20210824
	{
		m_editTPCoAxial[i].SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nTPCoAxial[i]));
		m_editTPRing[i].SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nTPRing[i]));
		m_editTPThreshold[i].SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nTPThreshold[i]));
		m_editTPBacklight[i].SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nTPBacklight[i]));
	}
	m_comboTPLightType.SetCurSel(CModelData::m_AlignPara.Info.nTPLightType);
	m_comboTPMarkType.SetCurSel(CModelData::m_AlignPara.Info.nTPMarkType);
	m_comboTPFocusType.SetCurSel(CModelData::m_AlignPara.Info.nTPFocusType);
	m_comboTPBlackWhiteType.SetCurSel(CModelData::m_AlignPara.Info.nTPBlackWhiteType);

	//X20 RATIO
	m_editx20CoAxial.SetWindowText(_ToStr(_T("%.3f"), CModelData::m_AlignPara.Info.dx20CoAxialScale));
	m_editx20Ring.SetWindowText(_ToStr(_T("%.3f"), CModelData::m_AlignPara.Info.dx20RingScale));
	m_editx20BackLight.SetWindowText(_ToStr(_T("%.3f"), CModelData::m_AlignPara.Info.dx20BackLightScale));
	//X20 RATIO
	m_editx50CoAxial.SetWindowText(_ToStr(_T("%.3f"), CModelData::m_AlignPara.Info.dx50CoAxialScale));
	m_editx50Ring.SetWindowText(_ToStr(_T("%.3f"), CModelData::m_AlignPara.Info.dx50RingScale));
	m_editx50BackLight.SetWindowText(_ToStr(_T("%.3f"), CModelData::m_AlignPara.Info.dx50BackLightScale));

	return TRUE;
}

BOOL CAlignPara2Dlg::CheckChangeData()
{
	CString Str;
	int i = 0;

	//Vertical Pre Align
	m_editVerticalPreAlignTargetCount.GetWindowText(Str);
	CModelData::m_AlignPara.Info.nVerticalPreAlignTargetCount = _ttoi(Str);
	m_editVerticalPreAlignTargetX.GetWindowText(Str);
	CModelData::m_AlignPara.Info.dVerticalPreAlignTargetX = _ttof(Str);
	m_editVerticalPreAlignTargetY.GetWindowText(Str);
	CModelData::m_AlignPara.Info.dVerticalPreAlignTargetY = _ttof(Str);
	m_editVerticalPreAlignCoAxial.GetWindowText(Str);
	CModelData::m_AlignPara.Info.nVerticalPreAlignCoAxial = _ttoi(Str);
	m_editVerticalPreAlignRing.GetWindowText(Str);
	CModelData::m_AlignPara.Info.nVerticalPreAlignRing = _ttoi(Str);
	m_editVerticalPreAlignThreshold.GetWindowText(Str);
	CModelData::m_AlignPara.Info.nVerticalPreAlignThreshold = _ttoi(Str);
	m_editVerticalPreAlignBackLight.GetWindowText(Str);
	CModelData::m_AlignPara.Info.nVerticalPreAlignBackLight = _ttoi(Str);
	CModelData::m_AlignPara.Info.nVerticalPreAlignLightType = m_comboVerticalPreAlignLightType.GetCurSel();
	CModelData::m_AlignPara.Info.nVerticalPreAlignMarkType = m_comboVerticalPreAlignMarkType.GetCurSel();
	CModelData::m_AlignPara.Info.nVerticalPreAlignFocusType = m_comboVerticalPreAlignFocusType.GetCurSel();
	CModelData::m_AlignPara.Info.nVerticalPreAlignBlackWhiteType = m_comboVerticalPreAlignBlackWhiteType.GetCurSel();

	//Vertical Main Align
	m_editVerticalMainAlignTargetCount.GetWindowText(Str);
	CModelData::m_AlignPara.Info.nVerticalMainAlignTargetCount = _ttoi(Str);
	m_editVerticalMainAlignTargetX.GetWindowText(Str);
	CModelData::m_AlignPara.Info.dVerticalMainAlignTargetX = _ttof(Str);
	m_editVerticalMainAlignTargetY.GetWindowText(Str);
	CModelData::m_AlignPara.Info.dVerticalMainAlignTargetY = _ttof(Str);
	m_editVerticalMainAlignCoAxial.GetWindowText(Str);
	CModelData::m_AlignPara.Info.nVerticalMainAlignCoAxial = _ttoi(Str);
	m_editVerticalMainAlignRing.GetWindowText(Str);
	CModelData::m_AlignPara.Info.nVerticalMainAlignRing = _ttoi(Str);
	m_editVerticalMainAlignThreshold.GetWindowText(Str);
	CModelData::m_AlignPara.Info.nVerticalMainAlignThreshold = _ttoi(Str);
	m_editVerticalMainAlignBackLight.GetWindowText(Str);
	CModelData::m_AlignPara.Info.nVerticalMainAlignBackLight = _ttoi(Str);
	CModelData::m_AlignPara.Info.nVerticalMainAlignLightType = m_comboVerticalMainAlignLightType.GetCurSel();
	CModelData::m_AlignPara.Info.nVerticalMainAlignMarkType = m_comboVerticalMainAlignMarkType.GetCurSel();
	CModelData::m_AlignPara.Info.nVerticalMainAlignFocusType = m_comboVerticalMainAlignFocusType.GetCurSel();
	CModelData::m_AlignPara.Info.nVerticalMainAlignBlackWhiteType = m_comboVerticalMainAlignBlackWhiteType.GetCurSel();

	//SwAlign //KJT 20210307
	m_editSwAlignTargetCount.GetWindowText(Str);
	CModelData::m_AlignPara.Info.nSwAlignTargetCount = _ttoi(Str);
	m_editSwAlignTargetX.GetWindowText(Str);
	CModelData::m_AlignPara.Info.dSwAlignTargetX = _ttof(Str);
	m_editSwAlignTargetY.GetWindowText(Str);
	CModelData::m_AlignPara.Info.dSwAlignTargetY = _ttof(Str);
	m_editSwAlignCoAxial.GetWindowText(Str);
	CModelData::m_AlignPara.Info.nSwAlignCoAxial = _ttoi(Str);
	m_editSwAlignRing.GetWindowText(Str);
	CModelData::m_AlignPara.Info.nSwAlignRing = _ttoi(Str);
	m_editSwAlignThreshold.GetWindowText(Str);
	CModelData::m_AlignPara.Info.nSwAlignThreshold = _ttoi(Str);
	m_editSwAlignBacklight.GetWindowText(Str);
	CModelData::m_AlignPara.Info.nSwAlignBacklight = _ttoi(Str);
	CModelData::m_AlignPara.Info.nSwAlignLightType = m_comboSwAlignLightType.GetCurSel();
	CModelData::m_AlignPara.Info.nSwAlignMarkType = m_comboSwAlignMarkType.GetCurSel();
	CModelData::m_AlignPara.Info.nSwAlignFocusType = m_comboSwAlignFocusType.GetCurSel();
	CModelData::m_AlignPara.Info.nSwAlignBlackWhiteType = m_comboSwAlignBlackWhiteType.GetCurSel();


	//Measure TP
	for (i = 0; i < 3; i++) //KJT 20210824
	{
		m_editTPCoAxial[i].GetWindowText(Str);
		CModelData::m_AlignPara.Info.nTPCoAxial[i] = _ttoi(Str);
		m_editTPRing[i].GetWindowText(Str);
		CModelData::m_AlignPara.Info.nTPRing[i] = _ttoi(Str);
		m_editTPThreshold[i].GetWindowText(Str);
		CModelData::m_AlignPara.Info.nTPThreshold[i] = _ttoi(Str);
		m_editTPBacklight[i].GetWindowText(Str);
		CModelData::m_AlignPara.Info.nTPBacklight[i] = _ttoi(Str);
	}
	CModelData::m_AlignPara.Info.nTPLightType = m_comboTPLightType.GetCurSel();
	CModelData::m_AlignPara.Info.nTPMarkType = m_comboTPMarkType.GetCurSel();
	CModelData::m_AlignPara.Info.nTPFocusType = m_comboTPFocusType.GetCurSel();
	CModelData::m_AlignPara.Info.nTPBlackWhiteType = m_comboTPBlackWhiteType.GetCurSel();

	m_editx20CoAxial.GetWindowText(Str);
	CModelData::m_AlignPara.Info.dx20CoAxialScale = _ttof(Str);
	m_editx20Ring.GetWindowText(Str);
	CModelData::m_AlignPara.Info.dx20RingScale = _ttof(Str);
	m_editx20BackLight.GetWindowText(Str);
	CModelData::m_AlignPara.Info.dx20BackLightScale = _ttof(Str);

	m_editx50CoAxial.GetWindowText(Str);
	CModelData::m_AlignPara.Info.dx50CoAxialScale = _ttof(Str);
	m_editx50Ring.GetWindowText(Str);
	CModelData::m_AlignPara.Info.dx50RingScale = _ttof(Str);
	m_editx50BackLight.GetWindowText(Str);
	CModelData::m_AlignPara.Info.dx50BackLightScale = _ttof(Str);

	return TRUE;
}

BOOL CAlignPara2Dlg::SavePara()
{
	CheckChangeData();

	CModelData::m_AlignPara.Save();

	AfxMessageBox(_T("Save Ok"));

	return TRUE;
}

void CAlignPara2Dlg::OnShowWindow(BOOL bShow, UINT nStatus)
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

void CAlignPara2Dlg::BtnEnable(BOOL bEnable)
{
}

void CAlignPara2Dlg::OnBnClickedBtnVerticalPreAlignLightOn()
{
	int nBackLightVal[BACKLIGHT_CH_COUNT] = { BACKLIGHT_OFF_VALUE, };
	int nCoAxial = 0, nRing = 0, nBackLight = 0;
	CString Str = _T("");

	m_editVerticalPreAlignCoAxial.GetWindowText(Str);
	nCoAxial = _ttoi(Str);
	m_editVerticalPreAlignRing.GetWindowText(Str);
	nRing = _ttoi(Str);
	m_editVerticalPreAlignBackLight.GetWindowText(Str);
	nBackLight = _ttoi(Str);

	//if (m_comboVerticalPreAlignLightType.GetCurSel() == eLight_Back)
	//{
	//	for (int i = 0; i < BACKLIGHT_CH_COUNT; i++)
	//	{
	//		nBackLightVal[i] = nBackLight;
	//	}

	//	g_CommBack_Light.BackLightOn(nBackLightVal);
	//}
	//else
	//{
	////	g_CommBack_Light.BackLightOn(nBackLightVal);

	//	//21.03.01 SJC
	//	g_CommZomm_Ring.SetLight_Zoom_Ring(nRing);//prea
	//	Sleep(50);
	//	g_CommZomm_Ring.Zoom_Light_On(TRUE);//zoom ring off
	//	Sleep(50);
	//	g_CommZomm_Coaxial.SetLight_Zoom_Coaxial(nCoAxial);
	//	Sleep(50);
	//	g_CommZomm_Coaxial.Zoom_Light_On(TRUE);//Zoom coaxial off
	//	//g_CommLight_8ch.SetLight_PreAlign(nCoAxial, nRing);
	////}

	//g_CommLoader_Light.SetLight_PreAlign(nCoAxial, nRing); //KJT 20210728
}


void CAlignPara2Dlg::OnBnClickedBtnVerticalPreAlignLightOff()
{
	//21.03.01 SJC
	//g_CommLight_8ch.SetLight_PreAlign(0, 0);	
	
	//g_CommZomm_Ring.Zoom_Light_On(FALSE);//zoom ring off
	//Sleep(50);
	//g_CommZomm_Coaxial.Zoom_Light_On(FALSE);//Zoom coaxial off

	//g_CommLoader_Light.SetLight_PreAlign(0, 0); //KJT 20210728
}


void CAlignPara2Dlg::OnBnClickedBtnVerticalMainAlignLightOn()
{
	int nCoAxial = 0, nRing = 0, nBackLight = 0;
	int nBackLightVal[BACKLIGHT_CH_COUNT] = { BACKLIGHT_OFF_VALUE, };
	CString Str = _T("");
	m_editVerticalMainAlignCoAxial.GetWindowText(Str);
	nCoAxial = _ttoi(Str);
	m_editVerticalMainAlignRing.GetWindowText(Str);
	nRing = _ttoi(Str);
	m_editVerticalMainAlignBackLight.GetWindowText(Str);
	nBackLight = _ttoi(Str);

	//if (m_comboVerticalMainAlignLightType.GetCurSel() == eLight_Back)
	//{
	//	for (int i = 0; i < BACKLIGHT_CH_COUNT; i++)
	//	{
	//		nBackLightVal[i] = nBackLight;
	//	}

	//	g_CommBack_Light.BackLightOn(nBackLightVal);
	//}
	//else
	{	
		//21.03.01 sjc
		//g_CommReview_Light.SetLight_Review(nRing, nCoAxial);//review light
		//g_CommLight_8ch.SetLight_Review_Coaxial(nCoAxial);
		//Sleep(20);
		//g_CommLight_12ch.SetLight_Review_Ring(nRing);
	}
}


void CAlignPara2Dlg::OnBnClickedBtnVerticalMainAlignLightOff()
{
	//int nBackLightVal[BACKLIGHT_CH_COUNT] = { BACKLIGHT_OFF_VALUE, };

	//if (m_comboVerticalMainAlignLightType.GetCurSel() == eLight_Back)
	//{
	//	g_CommBack_Light.BackLightOn(nBackLightVal);
	//}
	//else
	{
		//g_CommReview_Light.SetLight_Review(0, 0);//review light 
		//g_CommLight_8ch.SetLight_Review_Coaxial(nCoAxial);
		//Sleep(20);
		//g_CommLight_12ch.SetLight_Review_Ring(nRing);
	}
}

void CAlignPara2Dlg::OnBnClickedBtnSwAlignLightOn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int nCoAxial = 0, nRing = 0, nBackLight = 0;
	int nBackLightVal[BACKLIGHT_CH_COUNT] = { BACKLIGHT_OFF_VALUE, };
	CString Str = _T("");
	m_editSwAlignCoAxial.GetWindowText(Str);
	nCoAxial = _ttoi(Str);
	m_editSwAlignRing.GetWindowText(Str);
	nRing = _ttoi(Str);	
	m_editSwAlignBacklight.GetWindowText(Str);
	nBackLight = _ttoi(Str);
	
	//if (m_comboSwAlignLightType.GetCurSel() == eLight_Back)
	//{
	//	for (int i = 0; i < BACKLIGHT_CH_COUNT; i++)
	//	{
	//		nBackLightVal[i] = nBackLight;
	//	}

	//	g_CommBack_Light.BackLightOn(nBackLightVal);
	//}
	//else
	{
		//21.03.01 sjc
		g_CommReview_Light.SetLight_Review(nRing, nCoAxial);//review light
		//g_CommLight_8ch.SetLight_Review_Coaxial(nCoAxial);
		//Sleep(20);
		//g_CommLight_12ch.SetLight_Review_Ring(nRing);
	}
}


void CAlignPara2Dlg::OnBnClickedBtnSwAlignLightOff()
{
	//int nBackLightVal[BACKLIGHT_CH_COUNT] = { BACKLIGHT_OFF_VALUE, };

	//if (m_comboSwAlignLightType.GetCurSel() == eLight_Back)
	//{
	//	g_CommBack_Light.BackLightOn(nBackLightVal);
	//}
	//else
	{
		//g_CommReview_Light.SetLight_Review(0, 0);//review light 
		//g_CommLight_8ch.SetLight_Review_Coaxial(nCoAxial);
		//Sleep(20);
		//g_CommLight_12ch.SetLight_Review_Ring(nRing);
	}
}

void CAlignPara2Dlg::OnBnClickedBtnTPLightOn()
{
	int nCoAxial = 0, nRing = 0, nBackLight = 0;
	int nBackLightVal[BACKLIGHT_CH_COUNT] = { BACKLIGHT_OFF_VALUE, };
	CString Str = _T("");

	m_editTPCoAxial[0].GetWindowText(Str);
	nCoAxial = _ttoi(Str);
	m_editTPRing[0].GetWindowText(Str);
	nRing = _ttoi(Str);
	m_editTPBacklight[0].GetWindowText(Str);
	nBackLight = _ttoi(Str);

	//if (m_comboTPLightType.GetCurSel() == eLight_Back)
	//{
	//	for (int i = 0; i < BACKLIGHT_CH_COUNT; i++)
	//	{
	//		nBackLightVal[i] = nBackLight;
	//	}

	//	g_CommBack_Light.BackLightOn(nBackLightVal);
	//}
	//else
	{
		//21.03.01 sjc
		//g_CommReview_Light.SetLight_Review(nRing, nCoAxial);//review light
		//g_CommLight_8ch.SetLight_Review_Coaxial(nCoAxial);
		//Sleep(20);
		//g_CommLight_12ch.SetLight_Review_Ring(nRing);
	}
}

void CAlignPara2Dlg::OnBnClickedBtnMeasureHalfEdgeHoleLightOn2()
{
	int nCoAxial = 0, nRing = 0, nBackLight = 0;
	int nBackLightVal[BACKLIGHT_CH_COUNT] = { BACKLIGHT_OFF_VALUE, };
	CString Str = _T("");

	m_editTPCoAxial[1].GetWindowText(Str);
	nCoAxial = _ttoi(Str);
	m_editTPRing[1].GetWindowText(Str);
	nRing = _ttoi(Str);
	m_editTPBacklight[1].GetWindowText(Str);
	nBackLight = _ttoi(Str);

	//if (m_comboTPLightType.GetCurSel() == eLight_Back)
	//{
	//	for (int i = 0; i < BACKLIGHT_CH_COUNT; i++)
	//	{
	//		nBackLightVal[i] = nBackLight;
	//	}

	//	g_CommBack_Light.BackLightOn(nBackLightVal);
	//}
	//else
	{
		//21.03.01 sjc
		//g_CommReview_Light.SetLight_Review(nRing, nCoAxial);//review light
		//g_CommLight_8ch.SetLight_Review_Coaxial(nCoAxial);
		//Sleep(20);
		//g_CommLight_12ch.SetLight_Review_Ring(nRing);
	}
}


void CAlignPara2Dlg::OnBnClickedBtnMeasureHalfEdgeHoleLightOn3()
{
	int nCoAxial = 0, nRing = 0, nBackLight = 0;
	int nBackLightVal[BACKLIGHT_CH_COUNT] = { BACKLIGHT_OFF_VALUE, };
	CString Str = _T("");

	m_editTPCoAxial[2].GetWindowText(Str);
	nCoAxial = _ttoi(Str);
	m_editTPRing[2].GetWindowText(Str);
	nRing = _ttoi(Str);
	m_editTPBacklight[2].GetWindowText(Str);
	nBackLight = _ttoi(Str);

	//if (m_comboTPLightType.GetCurSel() == eLight_Back)
	//{
	//	for (int i = 0; i < BACKLIGHT_CH_COUNT; i++)
	//	{
	//		nBackLightVal[i] = nBackLight;
	//	}

	//	g_CommBack_Light.BackLightOn(nBackLightVal);
	//}
	//else
	{
		//21.03.01 sjc
		//g_CommReview_Light.SetLight_Review(nRing, nCoAxial);//review light
		//g_CommLight_8ch.SetLight_Review_Coaxial(nCoAxial);
		//Sleep(20);
		//g_CommLight_12ch.SetLight_Review_Ring(nRing);
	}
}

void CAlignPara2Dlg::OnBnClickedBtnTPLightOff()
{
	//int nBackLightVal[BACKLIGHT_CH_COUNT] = { BACKLIGHT_OFF_VALUE, };

	//if (m_comboTPLightType.GetCurSel() == eLight_Back)
	//{
	//	g_CommBack_Light.BackLightOn(nBackLightVal);
	//}
	//else
	{
		//g_CommReview_Light.SetLight_Review(0, 0);//review light 
		//g_CommLight_8ch.SetLight_Review_Coaxial(nCoAxial);
		//Sleep(20);
		//g_CommLight_12ch.SetLight_Review_Ring(nRing);
	}
}
