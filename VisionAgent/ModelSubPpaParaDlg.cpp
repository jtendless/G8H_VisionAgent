// ModelSubPpaParaDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentDlg.h"
#include "ModelSubPpaParaDlg.h"
#include "Vision/SharedInfo.h"
#include "afxdialogex.h"


// CModelSubPpaParaDlg 대화 상자

IMPLEMENT_DYNAMIC(CModelSubPpaParaDlg, CDialogEx)

CModelSubPpaParaDlg::CModelSubPpaParaDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MODEL_SUB_PPA_PARA_DIALOG, pParent)
{
	Create(IDD_MODEL_SUB_PPA_PARA_DIALOG, pParent);
}

CModelSubPpaParaDlg::~CModelSubPpaParaDlg()
{
}

void CModelSubPpaParaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CModelSubPpaParaDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BTN_PPA_LIGHT_ON, &CModelSubPpaParaDlg::OnBnClickedBtnPpaLightOn)
	ON_BN_CLICKED(IDC_BTN_PPA_LIGHT_OFF, &CModelSubPpaParaDlg::OnBnClickedBtnPpaLightOff)
END_MESSAGE_MAP()


// CModelSubPpaParaDlg 메시지 처리기

BOOL CModelSubPpaParaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitCtrl();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CModelSubPpaParaDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
}

BOOL CModelSubPpaParaDlg::InitCtrl()
{
#pragma region //PPA
	m_editPpaTargetCount.SubclassDlgItem(IDC_EDIT_PPA_TARGET_COUNT, this);
	m_editPpaTargetX.SubclassDlgItem(IDC_EDIT_PPA_TRAGET_X, this);
	m_editPpaTargetY.SubclassDlgItem(IDC_EDIT_PPA_TRAGET_Y, this);
	
	m_editPpaCoAxial.SubclassDlgItem(IDC_EDIT_PPA_COAXIAL, this);
	m_editPpaRing.SubclassDlgItem(IDC_EDIT_PPA_RING, this);
	m_editPpaThreshold.SubclassDlgItem(IDC_EDIT_PPA_THRESHOLD, this);
	m_editPpaBacklight.SubclassDlgItem(IDC_EDIT_PPA_BACKLIGHT, this);

	m_comboPpaLightType.SubclassDlgItem(IDC_COMBO_PPA_LIGHT_TYPE, this);
	m_comboPpaLightType.ResetContent();
	m_comboPpaLightType.AddString(_T("Front"));
	m_comboPpaLightType.AddString(_T("Back"));
	m_comboPpaLightType.SetCurSel(0);

	m_comboPpaMarkType.SubclassDlgItem(IDC_COMBO_PPA_MARK_TYPE, this);
	m_comboPpaMarkType.ResetContent();
	m_comboPpaMarkType.AddString(_T("Blob"));
	m_comboPpaMarkType.AddString(_T("Pattern"));
	m_comboPpaMarkType.SetCurSel(0);

	m_comboPpaFocusType.SubclassDlgItem(IDC_COMBO_PPA_FOCUS_TYPE, this);
	m_comboPpaFocusType.ResetContent();
	m_comboPpaFocusType.AddString(_T("None"));
	m_comboPpaFocusType.AddString(_T("Laser"));
	m_comboPpaFocusType.AddString(_T("Image"));
	m_comboPpaFocusType.AddString(_T("Both"));
	m_comboPpaFocusType.SetCurSel(0);

	m_comboPpaBlackWhiteType.SubclassDlgItem(IDC_COMBO_PPA_BLACK_WHITE_TYPE, this);
	m_comboPpaBlackWhiteType.ResetContent();
	m_comboPpaBlackWhiteType.AddString(_T("Black"));
	m_comboPpaBlackWhiteType.AddString(_T("White"));
	m_comboPpaBlackWhiteType.SetCurSel(0);

	m_btnPpaLightOn.SubclassDlgItem(IDC_BTN_PPA_LIGHT_ON, this);
	m_btnPpaLightOff.SubclassDlgItem(IDC_BTN_PPA_LIGHT_OFF, this);

	// KJT 20210525
	m_comboDivX.SubclassDlgItem(IDC_COMBO_PPA_PARA_DIV_X, this);
	m_comboDivX.ResetContent();
	m_comboDivX.AddString(_T("1"));
	m_comboDivX.AddString(_T("2"));
	m_comboDivX.AddString(_T("3"));
	m_comboDivX.AddString(_T("4"));
	m_comboDivX.AddString(_T("5"));
	m_comboDivX.SetCurSel(eDiv_3);

	m_comboDivY.SubclassDlgItem(IDC_COMBO_PPA_PARA_DIV_Y, this);
	m_comboDivY.ResetContent();
	m_comboDivY.AddString(_T("1"));
	m_comboDivY.AddString(_T("2"));
	m_comboDivY.AddString(_T("3"));
	m_comboDivY.AddString(_T("4"));
	m_comboDivY.AddString(_T("5"));
	m_comboDivY.SetCurSel(eDiv_3);

	m_comboSlotQuantityXY.SubclassDlgItem(IDC_COMBO_PPA_PARA_SLOT_QUANTITY_XY, this);
	m_comboSlotQuantityXY.ResetContent();
	m_comboSlotQuantityXY.AddString(_T("1x1"));
	m_comboSlotQuantityXY.AddString(_T("3x3"));
	m_comboSlotQuantityXY.AddString(_T("5x5"));
	m_comboSlotQuantityXY.SetCurSel(eQuantity_3X3);
#pragma endregion

	return TRUE;
}

BOOL CModelSubPpaParaDlg::InitPara()
{
	//PPA
	m_editPpaTargetCount.SetWindowText(_ToStr(_T("%d"), CModelData::m_PpaPara.Info.nPpaTargetCount));
	m_editPpaTargetX.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_PpaPara.Info.dPpaTargetX));
	m_editPpaTargetY.SetWindowText(_ToStr(_T("%.5f"), CModelData::m_PpaPara.Info.dPpaTargetY));
	m_editPpaCoAxial.SetWindowText(_ToStr(_T("%d"), CModelData::m_PpaPara.Info.nPpaCoAxial[0]));
	m_editPpaRing.SetWindowText(_ToStr(_T("%d"), CModelData::m_PpaPara.Info.nPpaRing[0]));
	m_editPpaThreshold.SetWindowText(_ToStr(_T("%d"), CModelData::m_PpaPara.Info.nPpaThreshold[0]));
	m_editPpaBacklight.SetWindowText(_ToStr(_T("%d"), CModelData::m_PpaPara.Info.nPpaBacklight[0]));
	m_comboPpaLightType.SetCurSel(CModelData::m_PpaPara.Info.nPpaLightType);
	m_comboPpaMarkType.SetCurSel(CModelData::m_PpaPara.Info.nPpaMarkType);
	m_comboPpaFocusType.SetCurSel(CModelData::m_PpaPara.Info.nPpaFocusType);
	m_comboPpaBlackWhiteType.SetCurSel(CModelData::m_PpaPara.Info.nPpaBlackWhiteType);

	//KJT 20210525
	m_comboDivX.SetCurSel(CModelData::m_PpaPara.Info.nDivX);
	m_comboDivY.SetCurSel(CModelData::m_PpaPara.Info.nDivY);
	m_comboSlotQuantityXY.SetCurSel(CModelData::m_PpaPara.Info.nSlotQuantityXY);

	return TRUE;
}

BOOL CModelSubPpaParaDlg::CheckChangeData()
{
	CString Str = _T("");

	//PPA
	m_editPpaTargetCount.GetWindowText(Str);
	CModelData::m_PpaPara.Info.nPpaTargetCount = _ttoi(Str);
	m_editPpaTargetX.GetWindowText(Str);
	CModelData::m_PpaPara.Info.dPpaTargetX = _ttof(Str);
	m_editPpaTargetY.GetWindowText(Str);
	CModelData::m_PpaPara.Info.dPpaTargetY = _ttof(Str);
	m_editPpaCoAxial.GetWindowText(Str);
	CModelData::m_PpaPara.Info.nPpaCoAxial[0] = _ttoi(Str);
	m_editPpaRing.GetWindowText(Str);
	CModelData::m_PpaPara.Info.nPpaRing[0] = _ttoi(Str);
	m_editPpaThreshold.GetWindowText(Str);
	CModelData::m_PpaPara.Info.nPpaThreshold[0] = _ttoi(Str);
	m_editPpaBacklight.GetWindowText(Str);
	CModelData::m_PpaPara.Info.nPpaBacklight[0] = _ttoi(Str);
	CModelData::m_PpaPara.Info.nPpaLightType = m_comboPpaLightType.GetCurSel();
	CModelData::m_PpaPara.Info.nPpaMarkType = m_comboPpaMarkType.GetCurSel();
	CModelData::m_PpaPara.Info.nPpaFocusType = m_comboPpaFocusType.GetCurSel();
	CModelData::m_PpaPara.Info.nPpaBlackWhiteType = m_comboPpaBlackWhiteType.GetCurSel();

	//KJT 20210525
	CModelData::m_PpaPara.Info.nDivX = m_comboDivX.GetCurSel();
	CModelData::m_PpaPara.Info.nDivY = m_comboDivY.GetCurSel();
	CModelData::m_PpaPara.Info.nSlotQuantityXY = m_comboSlotQuantityXY.GetCurSel();

	return TRUE;
}

BOOL CModelSubPpaParaDlg::SavePara()
{
	CheckChangeData();

	CModelData::m_PpaPara.Save();

	AfxMessageBox(_T("Save Ok"));

	return TRUE;
}

void CModelSubPpaParaDlg::OnShowWindow(BOOL bShow, UINT nStatus)
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

void CModelSubPpaParaDlg::BtnEnable(BOOL bEnable)
{
}

void CModelSubPpaParaDlg::OnBnClickedBtnPpaLightOn()
{
	int nCoAxial = 0, nRing = 0, nBackLight = 0;
	int nBackLightVal[BACKLIGHT_CH_COUNT] = { BACKLIGHT_OFF_VALUE, };

	CString Str = _T("");
	m_editPpaCoAxial.GetWindowText(Str);
	nCoAxial = _ttoi(Str);
	m_editPpaRing.GetWindowText(Str);
	nRing = _ttoi(Str);
	m_editPpaBacklight.GetWindowText(Str);
	nBackLight = _ttoi(Str);
	//21.03.01 sjc

	//if (m_comboPpaLightType.GetCurSel() == eLight_Back)
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


void CModelSubPpaParaDlg::OnBnClickedBtnPpaLightOff()
{
	int nBackLightVal[BACKLIGHT_CH_COUNT] = { BACKLIGHT_OFF_VALUE, };

	//if (m_comboPpaLightType.GetCurSel() == eLight_Back)
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

	//21.03.01 sjc
	//g_CommReview_Light.SetLight_Review(0, 0);//review light 
	//g_CommLight_8ch.SetLight_Review_Coaxial(0);
	//Sleep(20);
	//g_CommLight_12ch.SetLight_Review_Ring(0);
}
