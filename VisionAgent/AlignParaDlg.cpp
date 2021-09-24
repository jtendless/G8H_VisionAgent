// AlignParaDlg.cpp: 구현 파일
//test

#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentDlg.h"
#include "AlignParaDlg.h"
#include "Vision/SharedInfo.h"
#include "afxdialogex.h"


// CAlignParaDlg 대화 상자

IMPLEMENT_DYNAMIC(CAlignParaDlg, CDialogEx)

CAlignParaDlg::CAlignParaDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MODEL_SUB_ALIGN_PARA_DIALOG, pParent)
{
	Create(IDD_MODEL_SUB_ALIGN_PARA_DIALOG, pParent);
}

CAlignParaDlg::~CAlignParaDlg()
{
}

void CAlignParaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAlignParaDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BTN_BOX_ALIGN_LEFT_LIGHT_ON, &CAlignParaDlg::OnBnClickedBtnBoxAlignLeftLightOn)
	ON_BN_CLICKED(IDC_BTN_BOX_ALIGN_LEFT_LIGHT_OFF, &CAlignParaDlg::OnBnClickedBtnBoxAlignLeftLightOff)
	ON_BN_CLICKED(IDC_BTN_BOX_ALIGN_RIGHT_LIGHT_ON, &CAlignParaDlg::OnBnClickedBtnBoxAlignRightLightOn)
	ON_BN_CLICKED(IDC_BTN_BOX_ALIGN_RIGHT_LIGHT_OFF, &CAlignParaDlg::OnBnClickedBtnBoxAlignRightLightOff)
	ON_BN_CLICKED(IDC_BTN_ALIGN_PARA_PRE_ALIGN_LIGHT_ON_L, &CAlignParaDlg::OnBnClickedBtnAlignParaPreAlignLightOnL)
	ON_BN_CLICKED(IDC_BTN_ALIGN_PARA_PRE_ALIGN_LIGHT_ON_R, &CAlignParaDlg::OnBnClickedBtnAlignParaPreAlignLightOnR)
	ON_BN_CLICKED(IDC_BTN_PRE_ALIGN_LIGHT_OFF, &CAlignParaDlg::OnBnClickedBtnPreAlignLightOff)
	ON_BN_CLICKED(IDC_BTN_MAIN_2P_ALIGN_LIGHT_ON, &CAlignParaDlg::OnBnClickedBtnMain2pAlignLightOn)
	ON_BN_CLICKED(IDC_BTN_MAIN_2P_ALIGN_LIGHT_OFF, &CAlignParaDlg::OnBnClickedBtnMain2pAlignLightOff)
	ON_BN_CLICKED(IDC_BTN_EDGE_4P_ALIGN_LIGHT_ON, &CAlignParaDlg::OnBnClickedBtnEdge4pAlignLightOn)
	ON_BN_CLICKED(IDC_BTN_EDGE_4P_ALIGN_LIGHT_OFF, &CAlignParaDlg::OnBnClickedBtnEdge4pAlignLightOff)
	ON_BN_CLICKED(IDC_BTN_TEGKEY_ALIGN_LIGHT_ON, &CAlignParaDlg::OnBnClickedBtnTegkeyAlignLightOn)
	ON_BN_CLICKED(IDC_BTN_TEGKEY_ALIGN_LIGHT_OFF, &CAlignParaDlg::OnBnClickedBtnTegkeyAlignLightOff)
	ON_BN_CLICKED(IDC_BTN_PPA_LIGHT_ON2, &CAlignParaDlg::OnBnClickedBtnPpaLightOn2)
	ON_BN_CLICKED(IDC_BTN_PPA_LIGHT_ON3, &CAlignParaDlg::OnBnClickedBtnPpaLightOn3)
	ON_BN_CLICKED(IDC_BTN_PPA_LIGHT_ON4, &CAlignParaDlg::OnBnClickedBtnPpaLightOn4)
	ON_BN_CLICKED(IDC_BTN_PPA_LIGHT_OFF2, &CAlignParaDlg::OnBnClickedBtnPpaLightOff2)
END_MESSAGE_MAP()


// CAlignParaDlg 메시지 처리기

BOOL CAlignParaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitCtrl();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CAlignParaDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
}

BOOL CAlignParaDlg::InitCtrl()
{
#pragma region	//Box Align Left
	m_editBoxAlignLeftTargetCount.SubclassDlgItem(IDC_EDIT_BOX_ALIGN_LEFT_TARGET_COUNT, this);
	m_editBoxAlignLeftTargetX.SubclassDlgItem(IDC_EDIT_BOX_ALIGN_LEFT_TRAGET_X, this);
	m_editBoxAlignLeftTargetY.SubclassDlgItem(IDC_EDIT_BOX_ALIGN_LEFT_TRAGET_Y, this);
	m_editBoxAlignLeftCoAxial.SubclassDlgItem(IDC_EDIT_BOX_ALIGN_LEFT_COAXIAL, this);
	m_editBoxAlignLeftRing.SubclassDlgItem(IDC_EDIT_BOX_ALIGN_LEFT_RING, this);
	m_editBoxAlignLeftThreshold.SubclassDlgItem(IDC_EDIT_BOX_ALIGN_LEFT_THRESHOLD, this);

	m_comboBoxAlignLeftLightType.SubclassDlgItem(IDC_COMBO_BOX_ALIGN_LEFT_LIGHT_TYPE, this);
	m_comboBoxAlignLeftLightType.ResetContent();
	m_comboBoxAlignLeftLightType.AddString(_T("Front"));
	m_comboBoxAlignLeftLightType.AddString(_T("Back"));
	m_comboBoxAlignLeftLightType.SetCurSel(0);

	m_comboBoxAlignLeftMarkType.SubclassDlgItem(IDC_COMBO_BOX_ALIGN_LEFT_MARK_TYPE, this);
	m_comboBoxAlignLeftMarkType.ResetContent();
	m_comboBoxAlignLeftMarkType.AddString(_T("Blob"));
	m_comboBoxAlignLeftMarkType.AddString(_T("Pattern"));
	m_comboBoxAlignLeftMarkType.SetCurSel(0);
	
	m_comboBoxAlignLeftFocusType.SubclassDlgItem(IDC_COMBO_BOX_ALIGN_LEFT_FOCUS_TYPE, this);
	m_comboBoxAlignLeftFocusType.ResetContent();
	m_comboBoxAlignLeftFocusType.AddString(_T("None"));
	//m_comboBoxAlignLeftFocusType.AddString(_T("Laser"));
	//m_comboBoxAlignLeftFocusType.AddString(_T("Image"));
	//m_comboBoxAlignLeftFocusType.AddString(_T("Both"));
	m_comboBoxAlignLeftFocusType.SetCurSel(0);

	m_comboBoxAlignLeftBlackWhiteType.SubclassDlgItem(IDC_COMBO_BOX_ALIGN_LEFT_BLACK_WHITE_TYPE, this);
	m_comboBoxAlignLeftBlackWhiteType.ResetContent();
	m_comboBoxAlignLeftBlackWhiteType.AddString(_T("Black"));
	m_comboBoxAlignLeftBlackWhiteType.AddString(_T("White"));
	m_comboBoxAlignLeftBlackWhiteType.SetCurSel(0);

	m_btnBoxAlignLeftLightOn.SubclassDlgItem(IDC_BTN_BOX_ALIGN_LEFT_LIGHT_ON, this);
	m_btnBoxAlignLeftLightOff.SubclassDlgItem(IDC_BTN_BOX_ALIGN_LEFT_LIGHT_OFF, this);
#pragma endregion

#pragma region //Box Align Right
	m_editBoxAlignRightTargetCount.SubclassDlgItem(IDC_EDIT_BOX_ALIGN_RIGHT_TARGET_COUNT, this);
	m_editBoxAlignRightTargetX.SubclassDlgItem(IDC_EDIT_BOX_ALIGN_RIGHT_TRAGET_X, this);
	m_editBoxAlignRightTargetY.SubclassDlgItem(IDC_EDIT_BOX_ALIGN_RIGHT_TRAGET_Y, this);
	m_editBoxAlignRightCoAxial.SubclassDlgItem(IDC_EDIT_BOX_ALIGN_RIGHT_COAXIAL, this);
	m_editBoxAlignRightRing.SubclassDlgItem(IDC_EDIT_BOX_ALIGN_RIGHT_RING, this);
	m_editBoxAlignRightThreshold.SubclassDlgItem(IDC_EDIT_BOX_ALIGN_RIGHT_THRESHOLD, this);

	m_comboBoxAlignRightLightType.SubclassDlgItem(IDC_COMBO_BOX_ALIGN_RIGHT_LIGHT_TYPE, this);
	m_comboBoxAlignRightLightType.ResetContent();
	m_comboBoxAlignRightLightType.AddString(_T("Front"));
	m_comboBoxAlignRightLightType.AddString(_T("Back"));
	m_comboBoxAlignRightLightType.SetCurSel(0);

	m_comboBoxAlignRightMarkType.SubclassDlgItem(IDC_COMBO_BOX_ALIGN_RIGHT_MARK_TYPE, this);
	m_comboBoxAlignRightMarkType.ResetContent();
	m_comboBoxAlignRightMarkType.AddString(_T("Blob"));
	m_comboBoxAlignRightMarkType.AddString(_T("Pattern"));
	m_comboBoxAlignRightMarkType.SetCurSel(0);

	m_comboBoxAlignRightFocusType.SubclassDlgItem(IDC_COMBO_BOX_ALIGN_RIGHT_FOCUS_TYPE, this);
	m_comboBoxAlignRightFocusType.ResetContent();
	m_comboBoxAlignRightFocusType.AddString(_T("None"));
	//m_comboBoxAlignRightFocusType.AddString(_T("Laser"));
	//m_comboBoxAlignRightFocusType.AddString(_T("Image"));
	//m_comboBoxAlignRightFocusType.AddString(_T("Both"));
	m_comboBoxAlignRightFocusType.SetCurSel(0);

	m_comboBoxAlignRightBlackWhiteType.SubclassDlgItem(IDC_COMBO_BOX_ALIGN_RIGHT_BLACK_WHITE_TYPE, this);
	m_comboBoxAlignRightBlackWhiteType.ResetContent();
	m_comboBoxAlignRightBlackWhiteType.AddString(_T("Black"));
	m_comboBoxAlignRightBlackWhiteType.AddString(_T("White"));
	m_comboBoxAlignRightBlackWhiteType.SetCurSel(0);

	m_btnBoxAlignRightLightOn.SubclassDlgItem(IDC_BTN_BOX_ALIGN_RIGHT_LIGHT_ON, this);
	m_btnBoxAlignRightLightOff.SubclassDlgItem(IDC_BTN_BOX_ALIGN_RIGHT_LIGHT_OFF, this);
#pragma endregion

#pragma region //Pre Align
	m_editPreAlignTargetCount.SubclassDlgItem(IDC_EDIT_PRE_ALIGN_TARGET_COUNT, this);
	m_editPreAlignTargetX.SubclassDlgItem(IDC_EDIT_PRE_ALIGN_TRAGET_X, this);
	m_editPreAlignTargetY.SubclassDlgItem(IDC_EDIT_PRE_ALIGN_TRAGET_Y, this);
	m_editPreAlignCoAxial_L.SubclassDlgItem(IDC_EDIT_ALIGN_PARA_PRE_ALIGN_COAXIAL_L, this);
	m_editPreAlignRing_L.SubclassDlgItem(IDC_EDIT_ALIGN_PARA_PRE_ALIGN_RING_L, this);
	m_editPreAlignThreshold_L.SubclassDlgItem(IDC_EDIT_ALIGN_PARA_PRE_ALIGN_THRESHOLD_L, this);
	m_editPreAlignCoAxial_R.SubclassDlgItem(IDC_EDIT_ALIGN_PARA_PRE_ALIGN_COAXIAL_R, this);
	m_editPreAlignRing_R.SubclassDlgItem(IDC_EDIT_ALIGN_PARA_PRE_ALIGN_RING_R, this);
	m_editPreAlignThreshold_R.SubclassDlgItem(IDC_EDIT_ALIGN_PARA_PRE_ALIGN_THRESHOLD_R, this);

	m_comboPreAlignLightType.SubclassDlgItem(IDC_COMBO_PRE_ALIGN_LIGHT_TYPE, this);
	m_comboPreAlignLightType.ResetContent();
	m_comboPreAlignLightType.AddString(_T("Front"));
	m_comboPreAlignLightType.AddString(_T("Back"));
	m_comboPreAlignLightType.SetCurSel(0);

	m_comboPreAlignMarkType.SubclassDlgItem(IDC_COMBO_PRE_ALIGN_MARK_TYPE, this);
	m_comboPreAlignMarkType.ResetContent();
	m_comboPreAlignMarkType.AddString(_T("Blob"));
	m_comboPreAlignMarkType.AddString(_T("Pattern"));
	m_comboPreAlignMarkType.SetCurSel(0);

	m_comboPreAlignFocusType.SubclassDlgItem(IDC_COMBO_PRE_ALIGN_FOCUS_TYPE, this);
	m_comboPreAlignFocusType.ResetContent();
	m_comboPreAlignFocusType.AddString(_T("None"));
	m_comboPreAlignFocusType.AddString(_T("Laser"));
	m_comboPreAlignFocusType.AddString(_T("Image"));
	m_comboPreAlignFocusType.AddString(_T("Both"));
	m_comboPreAlignFocusType.SetCurSel(0);

	m_comboPreAlignBlackWhiteType.SubclassDlgItem(IDC_COMBO_PRE_ALIGN_BLACK_WHITE_TYPE, this);
	m_comboPreAlignBlackWhiteType.ResetContent();
	m_comboPreAlignBlackWhiteType.AddString(_T("Black"));
	m_comboPreAlignBlackWhiteType.AddString(_T("White"));
	m_comboPreAlignBlackWhiteType.SetCurSel(0);

	m_btnPreAlignLightOn_L.SubclassDlgItem(IDC_BTN_ALIGN_PARA_PRE_ALIGN_LIGHT_ON_L, this);
	m_btnPreAlignLightOff.SubclassDlgItem(IDC_BTN_PRE_ALIGN_LIGHT_OFF, this);
#pragma endregion

#pragma region //Main 2P Align
	m_editMain2PAlignTargetCount.SubclassDlgItem(IDC_EDIT_MAIN_2P_ALIGN_TARGET_COUNT, this);
	m_editMain2PAlignTargetX.SubclassDlgItem(IDC_EDIT_MAIN_2P_ALIGN_TRAGET_X, this);
	m_editMain2PAlignTargetY.SubclassDlgItem(IDC_EDIT_MAIN_2P_ALIGN_TRAGET_Y, this);
	m_editMain2PAlignCoAxial.SubclassDlgItem(IDC_EDIT_ALIGN_PARA_MAIN_2P_ALIGN_COAXIAL, this);
	m_editMain2PAlignRing.SubclassDlgItem(IDC_EDIT_MAIN_2P_ALIGN_RING, this);
	m_editMain2PAlignThreshold.SubclassDlgItem(IDC_EDIT_MAIN_2P_ALIGN_THRESHOLD, this);
	m_editMain2PAlignBackLight.SubclassDlgItem(IDC_EDIT_MAIN_2P_ALIGN_BACKLIGHT, this);

	m_comboMain2PAlignLightType.SubclassDlgItem(IDC_COMBO_MAIN_2P_ALIGN_LIGHT_TYPE, this);
	m_comboMain2PAlignLightType.ResetContent();
	m_comboMain2PAlignLightType.AddString(_T("Front"));
	m_comboMain2PAlignLightType.AddString(_T("Back"));
	m_comboMain2PAlignLightType.SetCurSel(0);

	m_comboMain2PAlignMarkType.SubclassDlgItem(IDC_COMBO_MAIN_2P_ALIGN_MARK_TYPE, this);
	m_comboMain2PAlignMarkType.ResetContent();
	m_comboMain2PAlignMarkType.AddString(_T("Blob"));
	m_comboMain2PAlignMarkType.AddString(_T("Pattern"));
	m_comboMain2PAlignMarkType.SetCurSel(0);

	m_comboMain2PAlignFocusType.SubclassDlgItem(IDC_COMBO_MAIN_2P_ALIGN_FOCUS_TYPE, this);
	m_comboMain2PAlignFocusType.ResetContent();
	m_comboMain2PAlignFocusType.AddString(_T("None"));
	m_comboMain2PAlignFocusType.AddString(_T("Laser"));
	m_comboMain2PAlignFocusType.AddString(_T("Image"));
	m_comboMain2PAlignFocusType.AddString(_T("Both"));
	m_comboMain2PAlignFocusType.SetCurSel(0);

	m_comboMain2PAlignBlackWhiteType.SubclassDlgItem(IDC_COMBO_MAIN_2P_ALIGN_BLACK_WHITE_TYPE, this);
	m_comboMain2PAlignBlackWhiteType.ResetContent();
	m_comboMain2PAlignBlackWhiteType.AddString(_T("Black"));
	m_comboMain2PAlignBlackWhiteType.AddString(_T("White"));
	m_comboMain2PAlignBlackWhiteType.SetCurSel(0);

	m_btnMain2PAlignLightOn.SubclassDlgItem(IDC_BTN_MAIN_2P_ALIGN_LIGHT_ON, this);
	m_btnMain2PAlignLightOff.SubclassDlgItem(IDC_BTN_MAIN_2P_ALIGN_LIGHT_OFF, this);
#pragma endregion

#pragma region //Edge 4P Align
	m_editEdge4PAlignTargetCount.SubclassDlgItem(IDC_EDIT_EDGE_4P_ALIGN_TARGET_COUNT, this);
	m_editEdge4PAlignTargetX.SubclassDlgItem(IDC_EDIT_EDGE_4P_ALIGN_TRAGET_X, this);
	m_editEdge4PAlignTargetY.SubclassDlgItem(IDC_EDIT_EDGE_4P_ALIGN_TRAGET_Y, this);
	m_editEdge4PAlignCoAxial.SubclassDlgItem(IDC_EDIT_ALIGN_PARA_EDGE_4P_ALIGN_COAXIAL, this);
	m_editEdge4PAlignRing.SubclassDlgItem(IDC_EDIT_EDGE_4P_ALIGN_RING, this);
	m_editEdge4PAlignThreshold.SubclassDlgItem(IDC_EDIT_EDGE_4P_ALIGN_THRESHOLD, this);
	m_editEdge4PAlignBacklight.SubclassDlgItem(IDC_EDIT_EDGE_4P_ALIGN_BACKLIGHT, this);

	m_comboEdge4PAlignLightType.SubclassDlgItem(IDC_COMBO_EDGE_4P_ALIGN_LIGHT_TYPE, this);
	m_comboEdge4PAlignLightType.ResetContent();
	m_comboEdge4PAlignLightType.AddString(_T("Front"));
	m_comboEdge4PAlignLightType.AddString(_T("Back"));
	m_comboEdge4PAlignLightType.SetCurSel(0);

	m_comboEdge4PAlignMarkType.SubclassDlgItem(IDC_COMBO_EDGE_4P_ALIGN_MARK_TYPE, this);
	m_comboEdge4PAlignMarkType.ResetContent();
	m_comboEdge4PAlignMarkType.AddString(_T("Blob"));
	m_comboEdge4PAlignMarkType.AddString(_T("Pattern"));
	m_comboEdge4PAlignMarkType.SetCurSel(0);

	m_comboEdge4PAlignFocusType.SubclassDlgItem(IDC_COMBO_EDGE_4P_ALIGN_FOCUS_TYPE, this);
	m_comboEdge4PAlignFocusType.ResetContent();
	m_comboEdge4PAlignFocusType.AddString(_T("None"));
	m_comboEdge4PAlignFocusType.AddString(_T("Laser"));
	m_comboEdge4PAlignFocusType.AddString(_T("Image"));
	m_comboEdge4PAlignFocusType.AddString(_T("Both"));
	m_comboEdge4PAlignFocusType.SetCurSel(0);

	m_comboEdge4PAlignBlackWhiteType.SubclassDlgItem(IDC_COMBO_EDGE_4P_ALIGN_BLACK_WHITE_TYPE, this);
	m_comboEdge4PAlignBlackWhiteType.ResetContent();
	m_comboEdge4PAlignBlackWhiteType.AddString(_T("Black"));
	m_comboEdge4PAlignBlackWhiteType.AddString(_T("White"));
	m_comboEdge4PAlignBlackWhiteType.SetCurSel(0);

	m_btnEdge4PAlignLightOn.SubclassDlgItem(IDC_BTN_EDGE_4P_ALIGN_LIGHT_ON, this);
	m_btnEdge4PAlignLightOff.SubclassDlgItem(IDC_BTN_EDGE_4P_ALIGN_LIGHT_OFF, this);
#pragma endregion

#pragma region //Tegkey Align
	m_editTegkeyAlignTargetCount.SubclassDlgItem(IDC_EDIT_TEGKEY_ALIGN_TARGET_COUNT, this);
	m_editTegkeyAlignTargetX.SubclassDlgItem(IDC_EDIT_TEGKEY_ALIGN_TRAGET_X, this);
	m_editTegkeyAlignTargetY.SubclassDlgItem(IDC_EDIT_TEGKEY_ALIGN_TRAGET_Y, this);
	m_editTegkeyAlignCoAxial.SubclassDlgItem(IDC_EDIT_ALIGN_PARA_TEGKEY_ALIGN_COAXIAL, this);
	m_editTegkeyAlignRing.SubclassDlgItem(IDC_EDIT_TEGKEY_ALIGN_RING, this);
	m_editTegkeyAlignThreshold.SubclassDlgItem(IDC_EDIT_TEGKEY_ALIGN_THRESHOLD, this);
	m_editTegkeyAlignBacklight.SubclassDlgItem(IDC_EDIT_TEGKEY_ALIGN_BACKLIGHT, this);

	m_comboTegkeyAlignLightType.SubclassDlgItem(IDC_COMBO_TEGKEY_ALIGN_LIGHT_TYPE, this);
	m_comboTegkeyAlignLightType.ResetContent();
	m_comboTegkeyAlignLightType.AddString(_T("Front"));
	m_comboTegkeyAlignLightType.AddString(_T("Back"));
	m_comboTegkeyAlignLightType.SetCurSel(0);

	m_comboTegkeyAlignMarkType.SubclassDlgItem(IDC_COMBO_TEGKEY_ALIGN_MARK_TYPE, this);
	m_comboTegkeyAlignMarkType.ResetContent();
	m_comboTegkeyAlignMarkType.AddString(_T("Blob"));
	m_comboTegkeyAlignMarkType.AddString(_T("Pattern"));
	m_comboTegkeyAlignMarkType.SetCurSel(0);

	m_comboTegkeyAlignFocusType.SubclassDlgItem(IDC_COMBO_TEGKEY_ALIGN_FOCUS_TYPE, this);
	m_comboTegkeyAlignFocusType.ResetContent();
	m_comboTegkeyAlignFocusType.AddString(_T("None"));
	m_comboTegkeyAlignFocusType.AddString(_T("Laser"));
	m_comboTegkeyAlignFocusType.AddString(_T("Image"));
	m_comboTegkeyAlignFocusType.AddString(_T("Both"));
	m_comboTegkeyAlignFocusType.SetCurSel(0);

	m_comboTegkeyAlignBlackWhiteType.SubclassDlgItem(IDC_COMBO_TEGKEY_ALIGN_BLACK_WHITE_TYPE, this);
	m_comboTegkeyAlignBlackWhiteType.ResetContent();
	m_comboTegkeyAlignBlackWhiteType.AddString(_T("Black"));
	m_comboTegkeyAlignBlackWhiteType.AddString(_T("White"));
	m_comboTegkeyAlignBlackWhiteType.SetCurSel(0);

	m_btnTegkeyAlignLightOn.SubclassDlgItem(IDC_BTN_TEGKEY_ALIGN_LIGHT_ON, this);
	m_btnTegkeyAlignLightOff.SubclassDlgItem(IDC_BTN_TEGKEY_ALIGN_LIGHT_OFF, this);
#pragma endregion
#pragma region // ppa move
	m_editPpaTargetCount.SubclassDlgItem(IDC_EDIT_PPA_TARGET_COUNT2, this);
	m_editPpaTargetX.SubclassDlgItem(IDC_EDIT_PPA_TRAGET_X2, this);
	m_editPpaTargetY.SubclassDlgItem(IDC_EDIT_PPA_TRAGET_Y2, this);
	m_editPpaCoAxial[0].SubclassDlgItem(IDC_EDIT_PPA_COAXIAL2, this);
	m_editPpaRing[0].SubclassDlgItem(IDC_EDIT_PPA_RING2, this);
	m_editPpaThreshold[0].SubclassDlgItem(IDC_EDIT_PPA_THRESHOLD2, this);
	m_editPpaBacklight[0].SubclassDlgItem(IDC_EDIT_PPA_BACKLIGHT2, this);

	m_editPpaCoAxial[1].SubclassDlgItem(IDC_EDIT_PPA_COAXIAL3, this);
	m_editPpaRing[1].SubclassDlgItem(IDC_EDIT_PPA_RING3, this);
	m_editPpaThreshold[1].SubclassDlgItem(IDC_EDIT_PPA_THRESHOLD3, this);
	m_editPpaBacklight[1].SubclassDlgItem(IDC_EDIT_PPA_BACKLIGHT3, this);

	m_editPpaCoAxial[2].SubclassDlgItem(IDC_EDIT_PPA_COAXIAL4, this);
	m_editPpaRing[2].SubclassDlgItem(IDC_EDIT_PPA_RING4, this);
	m_editPpaThreshold[2].SubclassDlgItem(IDC_EDIT_PPA_THRESHOLD4, this);
	m_editPpaBacklight[2].SubclassDlgItem(IDC_EDIT_PPA_BACKLIGHT4, this);

	m_comboPpaLightType.SubclassDlgItem(IDC_COMBO_PPA_LIGHT_TYPE2, this);
	m_comboPpaLightType.ResetContent();
	m_comboPpaLightType.AddString(_T("Front"));
	m_comboPpaLightType.AddString(_T("Back"));
	m_comboPpaLightType.SetCurSel(0);

	m_comboPpaMarkType.SubclassDlgItem(IDC_COMBO_PPA_MARK_TYPE2, this);
	m_comboPpaMarkType.ResetContent();
	m_comboPpaMarkType.AddString(_T("Blob"));
	m_comboPpaMarkType.AddString(_T("Pattern"));
	m_comboPpaMarkType.SetCurSel(0);

	m_comboPpaFocusType.SubclassDlgItem(IDC_COMBO_PPA_FOCUS_TYPE2, this);
	m_comboPpaFocusType.ResetContent();
	m_comboPpaFocusType.AddString(_T("None"));
	m_comboPpaFocusType.AddString(_T("Laser"));
	m_comboPpaFocusType.AddString(_T("Image"));
	m_comboPpaFocusType.AddString(_T("Both"));
	m_comboPpaFocusType.SetCurSel(0);

	m_comboPpaBlackWhiteType.SubclassDlgItem(IDC_COMBO_PPA_BLACK_WHITE_TYPE2, this);
	m_comboPpaBlackWhiteType.ResetContent();
	m_comboPpaBlackWhiteType.AddString(_T("Black"));
	m_comboPpaBlackWhiteType.AddString(_T("White"));
	m_comboPpaBlackWhiteType.SetCurSel(0);

	m_btnPpaLightOn[0].SubclassDlgItem(IDC_BTN_PPA_LIGHT_ON2, this);
	m_btnPpaLightOn[1].SubclassDlgItem(IDC_BTN_PPA_LIGHT_ON3, this);
	m_btnPpaLightOn[2].SubclassDlgItem(IDC_BTN_PPA_LIGHT_ON4, this);
	m_btnPpaLightOff.SubclassDlgItem(IDC_BTN_PPA_LIGHT_OFF2, this);
#pragma endregion
	return TRUE;
}

BOOL CAlignParaDlg::InitPara()
{
	int i = 0;

	//Box Align Left
	m_editBoxAlignLeftTargetCount.SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nBoxAlignLeftTargetCount));
	m_editBoxAlignLeftTargetX.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_AlignPara.Info.dBoxAlignLeftTargetX));
	m_editBoxAlignLeftTargetY.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_AlignPara.Info.dBoxAlignLeftTargetY));
	m_editBoxAlignLeftCoAxial.SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nBoxAlignLeftCoAxial));
	m_editBoxAlignLeftRing.SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nBoxAlignLeftRing));
	m_editBoxAlignLeftThreshold.SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nBoxAlignLeftThreshold));
	m_comboBoxAlignLeftLightType.SetCurSel(CModelData::m_AlignPara.Info.nBoxAlignLeftLightType);
	m_comboBoxAlignLeftMarkType.SetCurSel(CModelData::m_AlignPara.Info.nBoxAlignLeftMarkType);
	m_comboBoxAlignLeftFocusType.SetCurSel(CModelData::m_AlignPara.Info.nBoxAlignLeftFocusType);
	m_comboBoxAlignLeftBlackWhiteType.SetCurSel(CModelData::m_AlignPara.Info.nBoxAlignLeftBlackWhiteType);

	//Box Align Right
	m_editBoxAlignRightTargetCount.SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nBoxAlignRightTargetCount));
	m_editBoxAlignRightTargetX.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_AlignPara.Info.dBoxAlignRightTargetX));
	m_editBoxAlignRightTargetY.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_AlignPara.Info.dBoxAlignRightTargetY));
	m_editBoxAlignRightCoAxial.SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nBoxAlignRightCoAxial));
	m_editBoxAlignRightRing.SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nBoxAlignRightRing));
	m_editBoxAlignRightThreshold.SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nBoxAlignRightThreshold));
	m_comboBoxAlignRightLightType.SetCurSel(CModelData::m_AlignPara.Info.nBoxAlignRightLightType);
	m_comboBoxAlignRightMarkType.SetCurSel(CModelData::m_AlignPara.Info.nBoxAlignRightMarkType);
	m_comboBoxAlignRightFocusType.SetCurSel(CModelData::m_AlignPara.Info.nBoxAlignRightFocusType);
	m_comboBoxAlignRightBlackWhiteType.SetCurSel(CModelData::m_AlignPara.Info.nBoxAlignRightBlackWhiteType);

	//PreAlign
	m_editPreAlignTargetCount.SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nPreAlignTargetCount));
	m_editPreAlignTargetX.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_AlignPara.Info.dPreAlignTargetX));
	m_editPreAlignTargetY.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_AlignPara.Info.dPreAlignTargetY));
	m_editPreAlignCoAxial_L.SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nPreAlignCoAxial_L));
	m_editPreAlignRing_L.SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nPreAlignRing_L));
	m_editPreAlignThreshold_L.SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nPreAlignThreshold_L));
	m_editPreAlignCoAxial_R.SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nPreAlignCoAxial_R));
	m_editPreAlignRing_R.SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nPreAlignRing_R));
	m_editPreAlignThreshold_R.SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nPreAlignThreshold_R));
	m_comboPreAlignLightType.SetCurSel(CModelData::m_AlignPara.Info.nPreAlignLightType);
	m_comboPreAlignMarkType.SetCurSel(CModelData::m_AlignPara.Info.nPreAlignMarkType);
	m_comboPreAlignFocusType.SetCurSel(CModelData::m_AlignPara.Info.nPreAlignFocusType);
	m_comboPreAlignBlackWhiteType.SetCurSel(CModelData::m_AlignPara.Info.nPreAlignBlackWhiteType);

	//Main2PAlign
	m_editMain2PAlignTargetCount.SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nMain2PAlignTargetCount));
	m_editMain2PAlignTargetX.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_AlignPara.Info.dMain2PAlignTargetX));
	m_editMain2PAlignTargetY.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_AlignPara.Info.dMain2PAlignTargetY));
	m_editMain2PAlignCoAxial.SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nMain2PAlignCoAxial));
	m_editMain2PAlignRing.SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nMain2PAlignRing));
	m_editMain2PAlignThreshold.SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nMain2PAlignThreshold));
	m_editMain2PAlignBackLight.SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nMain2PAlignBackLight));
	m_comboMain2PAlignLightType.SetCurSel(CModelData::m_AlignPara.Info.nMain2PAlignLightType);
	m_comboMain2PAlignMarkType.SetCurSel(CModelData::m_AlignPara.Info.nMain2PAlignMarkType);
	m_comboMain2PAlignFocusType.SetCurSel(CModelData::m_AlignPara.Info.nMain2PAlignFocusType);
	m_comboMain2PAlignBlackWhiteType.SetCurSel(CModelData::m_AlignPara.Info.nMain2PAlignBlackWhiteType);

	//Edge4PAlign
	m_editEdge4PAlignTargetCount.SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nEdge4PAlignTargetCount));
	m_editEdge4PAlignTargetX.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_AlignPara.Info.dEdge4PAlignTargetX));
	m_editEdge4PAlignTargetY.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_AlignPara.Info.dEdge4PAlignTargetY));
	m_editEdge4PAlignCoAxial.SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nEdge4PAlignCoAxial));
	m_editEdge4PAlignRing.SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nEdge4PAlignRing));
	m_editEdge4PAlignThreshold.SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nEdge4PAlignThreshold));
	m_editEdge4PAlignBacklight.SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nEdge4PAlignBacklight));
	m_comboEdge4PAlignLightType.SetCurSel(CModelData::m_AlignPara.Info.nEdge4PAlignLightType);
	m_comboEdge4PAlignMarkType.SetCurSel(CModelData::m_AlignPara.Info.nEdge4PAlignMarkType);
	m_comboEdge4PAlignFocusType.SetCurSel(CModelData::m_AlignPara.Info.nEdge4PAlignFocusType);
	m_comboEdge4PAlignBlackWhiteType.SetCurSel(CModelData::m_AlignPara.Info.nEdge4PAlignBlackWhiteType);

	//TegkeyAlign
	m_editTegkeyAlignTargetCount.SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nTegkeyAlignTargetCount));
	m_editTegkeyAlignTargetX.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_AlignPara.Info.dTegkeyAlignTargetX));
	m_editTegkeyAlignTargetY.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_AlignPara.Info.dTegkeyAlignTargetY));
	m_editTegkeyAlignCoAxial.SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nTegkeyAlignCoAxial));
	m_editTegkeyAlignRing.SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nTegkeyAlignRing));
	m_editTegkeyAlignThreshold.SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nTegkeyAlignThreshold));
	m_editTegkeyAlignBacklight.SetWindowText(_ToStr(_T("%d"), CModelData::m_AlignPara.Info.nTegkeyAlignBacklight));
	m_comboTegkeyAlignLightType.SetCurSel(CModelData::m_AlignPara.Info.nTegkeyAlignLightType);
	m_comboTegkeyAlignMarkType.SetCurSel(CModelData::m_AlignPara.Info.nTegkeyAlignMarkType);
	m_comboTegkeyAlignFocusType.SetCurSel(CModelData::m_AlignPara.Info.nTegkeyAlignFocusType);
	m_comboTegkeyAlignBlackWhiteType.SetCurSel(CModelData::m_AlignPara.Info.nTegkeyAlignBlackWhiteType);

	//PPA
	m_editPpaTargetCount.SetWindowText(_ToStr(_T("%d"), CModelData::m_PpaPara.Info.nPpaTargetCount));
	m_editPpaTargetX.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_PpaPara.Info.dPpaTargetX));
	m_editPpaTargetY.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_PpaPara.Info.dPpaTargetY));

	for (i = 0; i < 3; i++) //KJT 20210824
	{
		m_editPpaCoAxial[i].SetWindowText(_ToStr(_T("%d"), CModelData::m_PpaPara.Info.nPpaCoAxial[i]));
		m_editPpaRing[i].SetWindowText(_ToStr(_T("%d"), CModelData::m_PpaPara.Info.nPpaRing[i]));
		m_editPpaThreshold[i].SetWindowText(_ToStr(_T("%d"), CModelData::m_PpaPara.Info.nPpaThreshold[i]));
		m_editPpaBacklight[i].SetWindowText(_ToStr(_T("%d"), CModelData::m_PpaPara.Info.nPpaBacklight[i]));
	}

	m_comboPpaLightType.SetCurSel(CModelData::m_PpaPara.Info.nPpaLightType);
	m_comboPpaMarkType.SetCurSel(CModelData::m_PpaPara.Info.nPpaMarkType);
	m_comboPpaFocusType.SetCurSel(CModelData::m_PpaPara.Info.nPpaFocusType);
	m_comboPpaBlackWhiteType.SetCurSel(CModelData::m_PpaPara.Info.nPpaBlackWhiteType);

	return TRUE;
}

BOOL CAlignParaDlg::CheckChangeData()
{
	CString Str = _T("");
	int i = 0;

	//Box Align Left
	m_editBoxAlignLeftTargetCount.GetWindowText(Str);
	CModelData::m_AlignPara.Info.nBoxAlignLeftTargetCount = _ttoi(Str);
	m_editBoxAlignLeftTargetX.GetWindowText(Str);
	CModelData::m_AlignPara.Info.dBoxAlignLeftTargetX = _ttof(Str);
	m_editBoxAlignLeftTargetY.GetWindowText(Str);
	CModelData::m_AlignPara.Info.dBoxAlignLeftTargetY = _ttof(Str);
	m_editBoxAlignLeftCoAxial.GetWindowText(Str);
	CModelData::m_AlignPara.Info.nBoxAlignLeftCoAxial = _ttoi(Str);
	m_editBoxAlignLeftRing.GetWindowText(Str);
	CModelData::m_AlignPara.Info.nBoxAlignLeftRing = _ttoi(Str);
	m_editBoxAlignLeftThreshold.GetWindowText(Str);
	CModelData::m_AlignPara.Info.nBoxAlignLeftThreshold = _ttoi(Str);
	CModelData::m_AlignPara.Info.nBoxAlignLeftLightType = m_comboBoxAlignLeftLightType.GetCurSel();
	CModelData::m_AlignPara.Info.nBoxAlignLeftMarkType = m_comboBoxAlignLeftMarkType.GetCurSel();
	CModelData::m_AlignPara.Info.nBoxAlignLeftFocusType = m_comboBoxAlignLeftFocusType.GetCurSel();
	CModelData::m_AlignPara.Info.nBoxAlignLeftBlackWhiteType = m_comboBoxAlignLeftBlackWhiteType.GetCurSel();

	//Box Align Right
	m_editBoxAlignRightTargetCount.GetWindowText(Str);
	CModelData::m_AlignPara.Info.nBoxAlignRightTargetCount = _ttoi(Str);
	m_editBoxAlignRightTargetX.GetWindowText(Str);
	CModelData::m_AlignPara.Info.dBoxAlignRightTargetX = _ttof(Str);
	m_editBoxAlignRightTargetY.GetWindowText(Str);
	CModelData::m_AlignPara.Info.dBoxAlignRightTargetY = _ttof(Str);
	m_editBoxAlignRightCoAxial.GetWindowText(Str);
	CModelData::m_AlignPara.Info.nBoxAlignRightCoAxial = _ttoi(Str);
	m_editBoxAlignRightRing.GetWindowText(Str);
	CModelData::m_AlignPara.Info.nBoxAlignRightRing = _ttoi(Str);
	m_editBoxAlignRightThreshold.GetWindowText(Str);
	CModelData::m_AlignPara.Info.nBoxAlignRightThreshold = _ttoi(Str);
	CModelData::m_AlignPara.Info.nBoxAlignRightLightType = m_comboBoxAlignRightLightType.GetCurSel();
	CModelData::m_AlignPara.Info.nBoxAlignRightMarkType = m_comboBoxAlignRightMarkType.GetCurSel();
	CModelData::m_AlignPara.Info.nBoxAlignRightFocusType = m_comboBoxAlignRightFocusType.GetCurSel();
	CModelData::m_AlignPara.Info.nBoxAlignRightBlackWhiteType = m_comboBoxAlignRightBlackWhiteType.GetCurSel();

	//PreAlign
	m_editPreAlignTargetCount.GetWindowText(Str);
	CModelData::m_AlignPara.Info.nPreAlignTargetCount = _ttoi(Str);
	m_editPreAlignTargetX.GetWindowText(Str);
	CModelData::m_AlignPara.Info.dPreAlignTargetX = _ttof(Str);
	m_editPreAlignTargetY.GetWindowText(Str);
	CModelData::m_AlignPara.Info.dPreAlignTargetY = _ttof(Str);
	m_editPreAlignCoAxial_L.GetWindowText(Str);
	CModelData::m_AlignPara.Info.nPreAlignCoAxial_L = _ttoi(Str);
	m_editPreAlignRing_L.GetWindowText(Str);
	CModelData::m_AlignPara.Info.nPreAlignRing_L = _ttoi(Str);
	m_editPreAlignThreshold_L.GetWindowText(Str);
	CModelData::m_AlignPara.Info.nPreAlignThreshold_L = _ttoi(Str);
	m_editPreAlignCoAxial_R.GetWindowText(Str);
	CModelData::m_AlignPara.Info.nPreAlignCoAxial_R = _ttoi(Str);
	m_editPreAlignRing_R.GetWindowText(Str);
	CModelData::m_AlignPara.Info.nPreAlignRing_R = _ttoi(Str);
	m_editPreAlignThreshold_R.GetWindowText(Str);
	CModelData::m_AlignPara.Info.nPreAlignThreshold_R = _ttoi(Str);
	CModelData::m_AlignPara.Info.nPreAlignLightType = m_comboPreAlignLightType.GetCurSel();
	CModelData::m_AlignPara.Info.nPreAlignMarkType = m_comboPreAlignMarkType.GetCurSel();
	CModelData::m_AlignPara.Info.nPreAlignFocusType = m_comboPreAlignFocusType.GetCurSel();
	CModelData::m_AlignPara.Info.nPreAlignBlackWhiteType = m_comboPreAlignBlackWhiteType.GetCurSel();

	//Main2PAlign
	m_editMain2PAlignTargetCount.GetWindowText(Str);
	CModelData::m_AlignPara.Info.nMain2PAlignTargetCount = _ttoi(Str);
	m_editMain2PAlignTargetX.GetWindowText(Str);
	CModelData::m_AlignPara.Info.dMain2PAlignTargetX = _ttof(Str);
	m_editMain2PAlignTargetY.GetWindowText(Str);
	CModelData::m_AlignPara.Info.dMain2PAlignTargetY = _ttof(Str);
	m_editMain2PAlignCoAxial.GetWindowText(Str);
	CModelData::m_AlignPara.Info.nMain2PAlignCoAxial = _ttoi(Str);
	m_editMain2PAlignRing.GetWindowText(Str);
	CModelData::m_AlignPara.Info.nMain2PAlignRing = _ttoi(Str);
	m_editMain2PAlignThreshold.GetWindowText(Str);
	CModelData::m_AlignPara.Info.nMain2PAlignThreshold = _ttoi(Str);
	m_editMain2PAlignBackLight.GetWindowText(Str);
	CModelData::m_AlignPara.Info.nMain2PAlignBackLight = _ttoi(Str);
	CModelData::m_AlignPara.Info.nMain2PAlignLightType = m_comboMain2PAlignLightType.GetCurSel();
	CModelData::m_AlignPara.Info.nMain2PAlignMarkType = m_comboMain2PAlignMarkType.GetCurSel();
	CModelData::m_AlignPara.Info.nMain2PAlignFocusType = m_comboMain2PAlignFocusType.GetCurSel();
	CModelData::m_AlignPara.Info.nMain2PAlignBlackWhiteType = m_comboMain2PAlignBlackWhiteType.GetCurSel();

	//Edge4PAlign
	m_editEdge4PAlignTargetCount.GetWindowText(Str);
	CModelData::m_AlignPara.Info.nEdge4PAlignTargetCount = _ttoi(Str);
	m_editEdge4PAlignTargetX.GetWindowText(Str);
	CModelData::m_AlignPara.Info.dEdge4PAlignTargetX = _ttof(Str);
	m_editEdge4PAlignTargetY.GetWindowText(Str);
	CModelData::m_AlignPara.Info.dEdge4PAlignTargetY = _ttof(Str);
	m_editEdge4PAlignCoAxial.GetWindowText(Str);
	CModelData::m_AlignPara.Info.nEdge4PAlignCoAxial = _ttoi(Str);
	m_editEdge4PAlignRing.GetWindowText(Str);
	CModelData::m_AlignPara.Info.nEdge4PAlignRing = _ttoi(Str);
	m_editEdge4PAlignThreshold.GetWindowText(Str);
	CModelData::m_AlignPara.Info.nEdge4PAlignThreshold = _ttoi(Str);
	m_editEdge4PAlignBacklight.GetWindowText(Str);
	CModelData::m_AlignPara.Info.nEdge4PAlignBacklight = _ttoi(Str);
	CModelData::m_AlignPara.Info.nEdge4PAlignLightType = m_comboEdge4PAlignLightType.GetCurSel();
	CModelData::m_AlignPara.Info.nEdge4PAlignMarkType = m_comboEdge4PAlignMarkType.GetCurSel();
	CModelData::m_AlignPara.Info.nEdge4PAlignFocusType = m_comboEdge4PAlignFocusType.GetCurSel();
	CModelData::m_AlignPara.Info.nEdge4PAlignBlackWhiteType = m_comboEdge4PAlignBlackWhiteType.GetCurSel();

	//TegkeyAlign
	m_editTegkeyAlignTargetCount.GetWindowText(Str);
	CModelData::m_AlignPara.Info.nTegkeyAlignTargetCount = _ttoi(Str);
	m_editTegkeyAlignTargetX.GetWindowText(Str);
	CModelData::m_AlignPara.Info.dTegkeyAlignTargetX = _ttof(Str);
	m_editTegkeyAlignTargetY.GetWindowText(Str);
	CModelData::m_AlignPara.Info.dTegkeyAlignTargetY = _ttof(Str);
	m_editTegkeyAlignCoAxial.GetWindowText(Str);
	CModelData::m_AlignPara.Info.nTegkeyAlignCoAxial = _ttoi(Str);
	m_editTegkeyAlignRing.GetWindowText(Str);
	CModelData::m_AlignPara.Info.nTegkeyAlignRing = _ttoi(Str);
	m_editTegkeyAlignThreshold.GetWindowText(Str);
	CModelData::m_AlignPara.Info.nTegkeyAlignThreshold = _ttoi(Str);
	m_editTegkeyAlignBacklight.GetWindowText(Str);
	CModelData::m_AlignPara.Info.nTegkeyAlignBacklight = _ttoi(Str);
	CModelData::m_AlignPara.Info.nTegkeyAlignLightType = m_comboTegkeyAlignLightType.GetCurSel();
	CModelData::m_AlignPara.Info.nTegkeyAlignMarkType = m_comboTegkeyAlignMarkType.GetCurSel();
	CModelData::m_AlignPara.Info.nTegkeyAlignFocusType = m_comboTegkeyAlignFocusType.GetCurSel();
	CModelData::m_AlignPara.Info.nTegkeyAlignBlackWhiteType = m_comboTegkeyAlignBlackWhiteType.GetCurSel();

	//PPA
	m_editPpaTargetCount.GetWindowText(Str);
	CModelData::m_PpaPara.Info.nPpaTargetCount = _ttoi(Str);
	m_editPpaTargetX.GetWindowText(Str);
	CModelData::m_PpaPara.Info.dPpaTargetX = _ttof(Str);
	m_editPpaTargetY.GetWindowText(Str);
	CModelData::m_PpaPara.Info.dPpaTargetY = _ttof(Str);

	for (i = 0; i < 3; i++) //KJT 20210824
	{
		m_editPpaCoAxial[i].GetWindowText(Str);
		CModelData::m_PpaPara.Info.nPpaCoAxial[i] = _ttoi(Str);
		m_editPpaRing[i].GetWindowText(Str);
		CModelData::m_PpaPara.Info.nPpaRing[i] = _ttoi(Str);
		m_editPpaThreshold[i].GetWindowText(Str);
		CModelData::m_PpaPara.Info.nPpaThreshold[i] = _ttoi(Str);
		m_editPpaBacklight[i].GetWindowText(Str);
		CModelData::m_PpaPara.Info.nPpaBacklight[i] = _ttoi(Str);
	}

	CModelData::m_PpaPara.Info.nPpaLightType = m_comboPpaLightType.GetCurSel();
	CModelData::m_PpaPara.Info.nPpaMarkType = m_comboPpaMarkType.GetCurSel();
	CModelData::m_PpaPara.Info.nPpaFocusType = m_comboPpaFocusType.GetCurSel();
	CModelData::m_PpaPara.Info.nPpaBlackWhiteType = m_comboPpaBlackWhiteType.GetCurSel();

	return TRUE;
}

BOOL CAlignParaDlg::SavePara()
{
	CheckChangeData();

	CModelData::m_AlignPara.Save();
	CModelData::m_PpaPara.Save();
	AfxMessageBox(_T("Save Ok"));

	return TRUE;
}

void CAlignParaDlg::OnShowWindow(BOOL bShow, UINT nStatus)
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

void CAlignParaDlg::BtnEnable(BOOL bEnable)
{
}

void CAlignParaDlg::OnBnClickedBtnBoxAlignLeftLightOn()
{
	int nCoAxial = 0, nRing = 0;
	CString Str = _T("");
	//m_editBoxAlignLeftCoAxial.GetWindowText(Str);
	//nCoAxial = _ttoi(Str);
	//m_editBoxAlignLeftRing.GetWindowText(Str);
	//nRing = _ttoi(Str);
	////21.03.01 SJC
	//g_CommLoader_Light.SetLight_Left_Loader(nRing, nCoAxial);//box align left
}


void CAlignParaDlg::OnBnClickedBtnBoxAlignLeftLightOff()
{
	//21.03.01 SJC
	//g_CommLoader_Light.SetLight_Left_Loader(0, 0);//box align left off
}


void CAlignParaDlg::OnBnClickedBtnBoxAlignRightLightOn()
{
	int nCoAxial = 0, nRing = 0;
	CString Str = _T("");
	//m_editBoxAlignRightCoAxial.GetWindowText(Str);
	//nCoAxial = _ttoi(Str);
	//m_editBoxAlignRightRing.GetWindowText(Str);
	//nRing = _ttoi(Str);
	////21.03.01 SJC
	//g_CommLoader_Light.SetLight_Right_Loader(nRing, nCoAxial);//box align right
}


void CAlignParaDlg::OnBnClickedBtnBoxAlignRightLightOff()
{	//21.03.01 SJC
	//g_CommLoader_Light.SetLight_Right_Loader(0, 0);//box align right off
}


void CAlignParaDlg::OnBnClickedBtnAlignParaPreAlignLightOnL()
{
	int nCoAxial = 0, nRing = 0;
	CString Str = _T("");
	m_editPreAlignCoAxial_L.GetWindowText(Str);
	nCoAxial = _ttoi(Str);
	m_editPreAlignRing_L.GetWindowText(Str);
	nRing = _ttoi(Str);

	//g_CommLoader_Light.SetLight_PreAlign(nCoAxial, nRing); //KJT 20210728

	////21.03.01 SJC
	//g_CommZomm_Ring.SetLight_Zoom_Ring(nRing);//prea
	//Sleep(50);
	//g_CommZomm_Ring.Zoom_Light_On(TRUE);//zoom ring 
	//Sleep(50);
	//g_CommZomm_Coaxial.SetLight_Zoom_Coaxial(nCoAxial);
	//Sleep(50);
	//g_CommZomm_Coaxial.Zoom_Light_On(TRUE);//Zoom coaxial 
	////g_CommLight_8ch.SetLight_PreAlign(nCoAxial, nRing);

	////////////////////////////////////////////////////////
	//m_editPreAlignCoAxial_R.GetWindowText(Str);
	//nCoAxial = _ttoi(Str);
	//m_editPreAlignRing_R.GetWindowText(Str);
	//nRing = _ttoi(Str);

	////21.03.01 SJC
	//g_CommZomm_Ring.SetLight_Zoom_Ring(nRing);//prea
	//Sleep(50);
	//g_CommZomm_Ring.Zoom_Light_On(TRUE);//zoom ring 
	//Sleep(50);
	//g_CommZomm_Coaxial.SetLight_Zoom_Coaxial(nCoAxial);
	//Sleep(50);
	//g_CommZomm_Coaxial.Zoom_Light_On(TRUE);//Zoom coaxial 
}

void CAlignParaDlg::OnBnClickedBtnAlignParaPreAlignLightOnR()
{
	int nCoAxial = 0, nRing = 0;
	CString Str = _T("");
	m_editPreAlignCoAxial_R.GetWindowText(Str);
	nCoAxial = _ttoi(Str);
	m_editPreAlignRing_R.GetWindowText(Str);
	nRing = _ttoi(Str);

	//g_CommLoader_Light.SetLight_PreAlign(nCoAxial, nRing); //KJT 20210728

	////21.03.01 SJC
	//g_CommZomm_Ring.SetLight_Zoom_Ring(nRing);//prea
	//Sleep(50);
	//g_CommZomm_Ring.Zoom_Light_On(TRUE);//zoom ring 
	//Sleep(50);
	//g_CommZomm_Coaxial.SetLight_Zoom_Coaxial(nCoAxial);
	//Sleep(50);
	//g_CommZomm_Coaxial.Zoom_Light_On(TRUE);//Zoom coaxial 
}



void CAlignParaDlg::OnBnClickedBtnPreAlignLightOff()
{
	////21.03.01 SJC
	//g_CommZomm_Ring.Zoom_Light_On(FALSE);//zoom ring 
	//Sleep(50);
	//g_CommZomm_Coaxial.Zoom_Light_On(FALSE);//Zoom coaxial 

	//g_CommLoader_Light.SetLight_PreAlign(0, 0); //KJT 20210728
}

void CAlignParaDlg::OnBnClickedBtnMain2pAlignLightOn()
{
	int nCoAxial = 0, nRing = 0, nBackLight = 0;
	int nBackLightVal[BACKLIGHT_CH_COUNT] = { BACKLIGHT_OFF_VALUE, };
	CString Str = _T("");
	m_editMain2PAlignCoAxial.GetWindowText(Str);
	nCoAxial = _ttoi(Str);
	m_editMain2PAlignRing.GetWindowText(Str);
	nRing = _ttoi(Str);
	m_editMain2PAlignBackLight.GetWindowText(Str);
	nBackLight = _ttoi(Str);

	
	//if (m_comboMain2PAlignLightType.GetCurSel() == eLight_Back)
	//{
	//	for (int i = 0; i < BACKLIGHT_CH_COUNT; i++)
	//		nBackLightVal[i] = nBackLight;

	//	g_CommBack_Light.BackLightOn(nBackLightVal);
	//}
	//else
	{
		//g_CommReview_Light.SetLight_Review(nRing, nCoAxial);//review light 
		//g_CommLight_8ch.SetLight_Review_Coaxial(nCoAxial);
		//Sleep(20);
		//g_CommLight_12ch.SetLight_Review_Ring(nRing);
	}

	//21.03.01 SJC
	//g_CommReview_Light.SetLight_Review(nRing, nCoAxial);//review light
	//g_CommLight_8ch.SetLight_Review_Coaxial(nCoAxial);
	//Sleep(20);
	//g_CommLight_12ch.SetLight_Review_Ring(nRing);
}


void CAlignParaDlg::OnBnClickedBtnMain2pAlignLightOff()
{
	//21.03.01 SJC
	//g_CommReview_Light.SetLight_Review(0, 0);//review light off

	//int nBackLightVal[BACKLIGHT_CH_COUNT] = { BACKLIGHT_OFF_VALUE, };

	//if (m_comboMain2PAlignLightType.GetCurSel() == eLight_Back)
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


void CAlignParaDlg::OnBnClickedBtnEdge4pAlignLightOn()
{
	int nCoAxial = 0, nRing = 0, nBackLight = 0;
	int nBackLightVal[BACKLIGHT_CH_COUNT] = { BACKLIGHT_OFF_VALUE, };
	CString Str = _T("");
	m_editEdge4PAlignCoAxial.GetWindowText(Str);
	nCoAxial = _ttoi(Str);
	m_editEdge4PAlignRing.GetWindowText(Str);
	nRing = _ttoi(Str);
	m_editEdge4PAlignBacklight.GetWindowText(Str);
	nBackLight = _ttoi(Str);

	//21.03.01 SJC
	//g_CommReview_Light.SetLight_Review(nRing, nCoAxial);//review light
	//g_CommLight_8ch.SetLight_Review_Coaxial(nCoAxial);
	//Sleep(20);
	//g_CommLight_12ch.SetLight_Review_Ring(nRing);

	
	//if (m_comboEdge4PAlignLightType.GetCurSel() == eLight_Back)
	//{
	//	for (int i = 0; i < BACKLIGHT_CH_COUNT; i++)
	//		nBackLightVal[i] = nBackLight;

	//	g_CommBack_Light.BackLightOn(nBackLightVal);
	//}
	//else
	{
		//g_CommReview_Light.SetLight_Review(nRing, nCoAxial);//review light 
		//g_CommLight_8ch.SetLight_Review_Coaxial(nCoAxial);
		//Sleep(20);
		//g_CommLight_12ch.SetLight_Review_Ring(nRing);
	}
}


void CAlignParaDlg::OnBnClickedBtnEdge4pAlignLightOff()
{
	//21.03.01 SJC
	//g_CommReview_Light.SetLight_Review(0, 0);//review light
	//g_CommLight_8ch.SetLight_Review_Coaxial(0);
	//Sleep(20);
	//g_CommLight_12ch.SetLight_Review_Ring(0);

	//int nBackLightVal[BACKLIGHT_CH_COUNT] = { BACKLIGHT_OFF_VALUE, };

	//if (m_comboEdge4PAlignLightType.GetCurSel() == eLight_Back)
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


void CAlignParaDlg::OnBnClickedBtnTegkeyAlignLightOn()
{
}


void CAlignParaDlg::OnBnClickedBtnTegkeyAlignLightOff()
{
}

//----------
//21.06.10 sjc ppa move pos


void CAlignParaDlg::OnBnClickedBtnPpaLightOn2()
{
}

void CAlignParaDlg::OnBnClickedBtnPpaLightOn3()
{
}


void CAlignParaDlg::OnBnClickedBtnPpaLightOn4()
{
}

void CAlignParaDlg::OnBnClickedBtnPpaLightOff2()
{
}
