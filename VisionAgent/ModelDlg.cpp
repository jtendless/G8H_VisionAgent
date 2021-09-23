// ModelDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentDlg.h"
#include "ModelDlg.h"
#include "afxdialogex.h"
#include "VisionAgentModelModelChangeDlg.h"
#include "ModelSubMaterialParaDlg.h"
#include "ModelSubMaterialPara2Dlg.h"
#include "ModelSubMaterialPara3Dlg.h"
#include "ModelSubAtMaterialParaDlg.h"
#include "ModelSubAtMaterialPara2Dlg.h"
#include "ModelSubAtMaterialPara3Dlg.h"
#include "ModelSubMaterialParaAlignStickDlg.h"
#include "ModelSubAtMaterialParaAlignStickDlg.h"
#include "InspectionParaDlg.h"
#include "StretchParaDlg.h"
#include "GlassParaDlg.h"
#include "AlignParaDlg.h"
#include "AlignPara2Dlg.h"
#include "ModelSubManualParaDlg.h"
#include "ModelSubPpaParaDlg.h"
// CModelDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CModelDlg, CDialogEx)

CModelDlg::CModelDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_VISION_AGENT_MODEL_DIALOG, pParent)
{
	Create(IDD_VISION_AGENT_MODEL_DIALOG, pParent);
	m_nCurrentNo = 0;
}

CModelDlg::~CModelDlg()
{
	if (m_pModelChangeSubDlg)
	{
		m_pModelChangeSubDlg->DestroyWindow();
		delete m_pModelChangeSubDlg;
	}

	if (m_pMaterialParaDlg)
	{
		m_pMaterialParaDlg->DestroyWindow();
		delete m_pMaterialParaDlg;
	}
	if (m_pMaterialPara2Dlg)
	{
		m_pMaterialPara2Dlg->DestroyWindow();
		delete m_pMaterialPara2Dlg;
	}
	if (m_pMaterialPara3Dlg)
	{
		m_pMaterialPara3Dlg->DestroyWindow();
		delete m_pMaterialPara3Dlg;
	}

	if (m_pAtMaterialParaDlg)
	{
		m_pAtMaterialParaDlg->DestroyWindow();
		delete m_pAtMaterialParaDlg;
	}
	if (m_pAtMaterialPara2Dlg)
	{
		m_pAtMaterialPara2Dlg->DestroyWindow();
		delete m_pAtMaterialPara2Dlg;
	}
	if (m_pAtMaterialPara3Dlg)
	{
		m_pAtMaterialPara3Dlg->DestroyWindow();
		delete m_pAtMaterialPara3Dlg;
	}

	if (m_pMaterialParaAlignStickDlg)
	{
		m_pMaterialParaAlignStickDlg->DestroyWindow();
		delete m_pMaterialParaAlignStickDlg;
	}

	if (m_pAtMaterialParaAlignStickDlg)
	{
		m_pAtMaterialParaAlignStickDlg->DestroyWindow();
		delete m_pAtMaterialParaAlignStickDlg;
	}

	if (m_pInspectionParaDlg)
	{
		m_pInspectionParaDlg->DestroyWindow();
		delete m_pInspectionParaDlg;
	}
	if (m_pStretchParaDlg)
	{
		m_pStretchParaDlg->DestroyWindow();
		delete m_pStretchParaDlg;
	}
	if (m_pGlassParaDlg)
	{
		m_pGlassParaDlg->DestroyWindow();
		delete m_pGlassParaDlg;
	}
	if (m_pAlignParaDlg)
	{
		m_pAlignParaDlg->DestroyWindow();
		delete m_pAlignParaDlg;
	}
	if (m_pAlignPara2Dlg)
	{
		m_pAlignPara2Dlg->DestroyWindow();
		delete m_pAlignPara2Dlg;
	}
	if (m_pModelSubManualParaDlg)
	{
		m_pModelSubManualParaDlg->DestroyWindow();
		delete m_pModelSubManualParaDlg;
	}
	if (m_pPpaParaDlg)
	{
		m_pPpaParaDlg->DestroyWindow();
		delete m_pPpaParaDlg;
	}
}

void CModelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CModelDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SUB_PAGE1, &CModelDlg::OnBnClickedButtonSubPage1)
	ON_BN_CLICKED(IDC_BUTTON_SUB_PAGE2, &CModelDlg::OnBnClickedButtonSubPage2)
	ON_BN_CLICKED(IDC_BUTTON_SUB_PAGE3, &CModelDlg::OnBnClickedButtonSubPage3)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BTN_MODEL_MENU_MODEL_CHAGE, &CModelDlg::OnBnClickedButtonModelChange)
	ON_BN_CLICKED(IDC_BTN_MODEL_MENU_MATERIAL_PARA, &CModelDlg::OnBnClickedButtonMaterialPara)
	ON_BN_CLICKED(IDC_BTN_MODEL_MENU_AT_MATERIAL_PARA, &CModelDlg::OnBnClickedButtonAtMaterialPara)
	ON_BN_CLICKED(IDC_BTN_MODEL_MENU_INSPECTION_PARA, &CModelDlg::OnBnClickedButtonInspectionPara)
	ON_BN_CLICKED(IDC_BTN_MODEL_MENU_STRETCH_PARA, &CModelDlg::OnBnClickedButtonStretchPara)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_MODEL_SAVE, &CModelDlg::OnBnClickedBtnModelSave)
	ON_BN_CLICKED(IDC_BTN_MODEL_MENU_GLASS_PARA, &CModelDlg::OnBnClickedBtnModelMenuGlassPara)
	ON_BN_CLICKED(IDC_BTN_MODEL_MENU_ALIGN_PARA, &CModelDlg::OnBnClickedBtnModelMenuAlignPara)
	ON_BN_CLICKED(IDC_BTN_MODEL_MENU_MANUAL_PARA, &CModelDlg::OnBnClickedBtnModelMenuManualPara)
	ON_BN_CLICKED(IDC_BTN_MODEL_MENU_PPA_PARA, &CModelDlg::OnBnClickedBtnModelMenuPpaPara)
END_MESSAGE_MAP()


// CModelDlg 메시지 처리기입니다.

//-------------------------------------------------------------------------------
BOOL CModelDlg::OnInitDialog()
{

	CDialogEx::OnInitDialog();
	CSize TabSize;

	m_nCurrentNo	= eMODEL_MENU_MODEL_CHANGE;
	m_nCurrentSubNo	= MODEL_SUB_PAGE1_DLG;

	InitCtrl();

	return TRUE; 
}
//-------------------------------------------------------------------------------
void CModelDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow == TRUE)
	{
		SetWindowPos(NULL, 960, 10, 960, 960, NULL);

		m_nCurrentNo = eMODEL_MENU_MODEL_CHANGE;
		m_nCurrentSubNo = MODEL_SUB_PAGE1_DLG;
		ShowDlg(m_nCurrentNo, m_nCurrentSubNo);
	}
	else
	{
	}
}
//-------------------------------------------------------------------------------
void CModelDlg::OnCancel()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CVisionAgentDlg *pVisionAgentDlg = (CVisionAgentDlg*)theApp.m_pMainWnd;
	pVisionAgentDlg->m_bShowModelModeless = FALSE;

	CDialogEx::OnCancel();
}
//-------------------------------------------------------------------------------
void CModelDlg::InitCtrl()
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//								  버튼
	//--------------------------------------------------------------------------------------------------------
	m_btnModel[eMODEL_MENU_MODEL_CHANGE].SubclassDlgItem(IDC_BTN_MODEL_MENU_MODEL_CHAGE, this);
	m_btnModel[eMODEL_MENU_MATERIAL_PARA].SubclassDlgItem(IDC_BTN_MODEL_MENU_MATERIAL_PARA, this);
	m_btnModel[eMODEL_MENU_AT_MATERIAL_PARA].SubclassDlgItem(IDC_BTN_MODEL_MENU_AT_MATERIAL_PARA, this);
	m_btnModel[eMODEL_MENU_INSPECTION_PARA].SubclassDlgItem(IDC_BTN_MODEL_MENU_INSPECTION_PARA, this);
	m_btnModel[eMODEL_MENU_STRETCH_PARA].SubclassDlgItem(IDC_BTN_MODEL_MENU_STRETCH_PARA, this);
	m_btnModel[eMODEL_MENU_GLASS_PARA].SubclassDlgItem(IDC_BTN_MODEL_MENU_GLASS_PARA, this);
	m_btnModel[eMODEL_MENU_ALIGN_PARA].SubclassDlgItem(IDC_BTN_MODEL_MENU_ALIGN_PARA, this);
	m_btnModel[eMODEL_MENU_MANUAL_PARA].SubclassDlgItem(IDC_BTN_MODEL_MENU_MANUAL_PARA, this);
	m_btnModel[eMODEL_MENU_PPA_PARA].SubclassDlgItem(IDC_BTN_MODEL_MENU_PPA_PARA, this);

	m_btnSubModel[MODEL_SUB_PAGE1_DLG].SubclassDlgItem(IDC_BUTTON_SUB_PAGE1, this);
	m_btnSubModel[MODEL_SUB_PAGE2_DLG].SubclassDlgItem(IDC_BUTTON_SUB_PAGE2, this);
	m_btnSubModel[MODEL_SUB_PAGE3_DLG].SubclassDlgItem(IDC_BUTTON_SUB_PAGE3, this);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//								버튼 램프
	//--------------------------------------------------------------------------------------------------------
	m_stcModel_Dlg_Lamp[eMODEL_MENU_MODEL_CHANGE].SubclassDlgItem(IDC_STATIC_LAMP_MODEL_CHANGE, this);
	m_stcModel_Dlg_Lamp[eMODEL_MENU_MODEL_CHANGE].SetBackgroundColor(BTN_LAMP_ON); //주황
	m_stcModel_Dlg_Lamp[eMODEL_MENU_MODEL_CHANGE].SetBackgroundColor(RGB(239, 239, 239)); //백그라운드

	m_stcModel_Dlg_Lamp[eMODEL_MENU_MATERIAL_PARA].SubclassDlgItem(IDC_STATIC_LAMP_MODEL_MATERIAL_PARA, this);
	m_stcModel_Dlg_Lamp[eMODEL_MENU_MATERIAL_PARA].SetBackgroundColor(BTN_LAMP_ON); //주황
	m_stcModel_Dlg_Lamp[eMODEL_MENU_MATERIAL_PARA].SetBackgroundColor(RGB(239, 239, 239)); //백그라운드

	m_stcModel_Dlg_Lamp[eMODEL_MENU_AT_MATERIAL_PARA].SubclassDlgItem(IDC_STATIC_LAMP_MODEL_AT_MATERIAL_PARA, this);
	m_stcModel_Dlg_Lamp[eMODEL_MENU_AT_MATERIAL_PARA].SetBackgroundColor(BTN_LAMP_ON); //주황
	m_stcModel_Dlg_Lamp[eMODEL_MENU_AT_MATERIAL_PARA].SetBackgroundColor(RGB(239, 239, 239)); //백그라운드

	m_stcModel_Dlg_Lamp[eMODEL_MENU_INSPECTION_PARA].SubclassDlgItem(IDC_STATIC_LAMP_MODEL_INSPECTION_PARA, this);
	m_stcModel_Dlg_Lamp[eMODEL_MENU_INSPECTION_PARA].SetBackgroundColor(BTN_LAMP_ON); //주황
	m_stcModel_Dlg_Lamp[eMODEL_MENU_INSPECTION_PARA].SetBackgroundColor(RGB(239, 239, 239)); //백그라운드

	m_stcModel_Dlg_Lamp[eMODEL_MENU_STRETCH_PARA].SubclassDlgItem(IDC_STATIC_LAMP_MODEL_STRETCH_PARA, this);
	m_stcModel_Dlg_Lamp[eMODEL_MENU_STRETCH_PARA].SetBackgroundColor(BTN_LAMP_ON); //주황
	m_stcModel_Dlg_Lamp[eMODEL_MENU_STRETCH_PARA].SetBackgroundColor(RGB(239, 239, 239)); //백그라운드

	m_stcModel_Dlg_Lamp[eMODEL_MENU_GLASS_PARA].SubclassDlgItem(IDC_STATIC_LAMP_MODEL_GLASS_PARA, this);
	m_stcModel_Dlg_Lamp[eMODEL_MENU_GLASS_PARA].SetBackgroundColor(BTN_LAMP_ON); //주황
	m_stcModel_Dlg_Lamp[eMODEL_MENU_GLASS_PARA].SetBackgroundColor(RGB(239, 239, 239)); //백그라운드

	m_stcModel_Dlg_Lamp[eMODEL_MENU_ALIGN_PARA].SubclassDlgItem(IDC_STATIC_LAMP_MODEL_ALIGN_PARA, this);
	m_stcModel_Dlg_Lamp[eMODEL_MENU_ALIGN_PARA].SetBackgroundColor(BTN_LAMP_ON); //주황
	m_stcModel_Dlg_Lamp[eMODEL_MENU_ALIGN_PARA].SetBackgroundColor(RGB(239, 239, 239));

	m_stcModel_Dlg_Lamp[eMODEL_MENU_MANUAL_PARA].SubclassDlgItem(IDC_STATIC_LAMP_MODEL_MANUAL_PARA, this);
	m_stcModel_Dlg_Lamp[eMODEL_MENU_MANUAL_PARA].SetBackgroundColor(BTN_LAMP_ON); //주황
	m_stcModel_Dlg_Lamp[eMODEL_MENU_MANUAL_PARA].SetBackgroundColor(RGB(239, 239, 239));

	m_stcModel_Dlg_Lamp[eMODEL_MENU_PPA_PARA].SubclassDlgItem(IDC_STATIC_LAMP_MODEL_PPA_PARA, this);
	m_stcModel_Dlg_Lamp[eMODEL_MENU_PPA_PARA].SetBackgroundColor(BTN_LAMP_ON); //주황
	m_stcModel_Dlg_Lamp[eMODEL_MENU_PPA_PARA].SetBackgroundColor(RGB(239, 239, 239));

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//								SUB 버튼 램프
	//--------------------------------------------------------------------------------------------------------
	m_stcModel_Sub_Dlg_Lamp[MODEL_SUB_PAGE1_DLG].SubclassDlgItem(IDC_STATIC_SUB_PAGE_LAMP_1, this);
	m_stcModel_Sub_Dlg_Lamp[MODEL_SUB_PAGE2_DLG].SubclassDlgItem(IDC_STATIC_SUB_PAGE_LAMP_2, this);
	m_stcModel_Sub_Dlg_Lamp[MODEL_SUB_PAGE3_DLG].SubclassDlgItem(IDC_STATIC_SUB_PAGE_LAMP_3, this);

	m_stcModel_Sub_Dlg_Lamp[MODEL_SUB_PAGE1_DLG].SetBackgroundColor(BTN_LAMP_OFF); //주황
	m_stcModel_Sub_Dlg_Lamp[MODEL_SUB_PAGE1_DLG].SetBackgroundColor(RGB(239, 239, 239)); //백그라운드
	m_stcModel_Sub_Dlg_Lamp[MODEL_SUB_PAGE2_DLG].SetBackgroundColor(BTN_LAMP_OFF); //주황
	m_stcModel_Sub_Dlg_Lamp[MODEL_SUB_PAGE2_DLG].SetBackgroundColor(RGB(239, 239, 239)); //백그라운드
	m_stcModel_Sub_Dlg_Lamp[MODEL_SUB_PAGE3_DLG].SetBackgroundColor(BTN_LAMP_OFF); //주황
	m_stcModel_Sub_Dlg_Lamp[MODEL_SUB_PAGE3_DLG].SetBackgroundColor(RGB(239, 239, 239)); //백그라운드	

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//								다이얼로그 박스
	//--------------------------------------------------------------------------------------------------------
	m_pModelChangeSubDlg = new CVisionAgentModelModelChangeDlg(this);
	m_pMaterialParaDlg = new CModelSubMaterialParaDlg(this);
	m_pMaterialPara2Dlg = new CModelSubMaterialPara2Dlg(this);
	m_pMaterialPara3Dlg = new CModelSubMaterialPara3Dlg(this);
	m_pAtMaterialParaDlg = new CModelSubAtMaterialParaDlg(this);
	m_pAtMaterialPara2Dlg = new CModelSubAtMaterialPara2Dlg(this);
	m_pAtMaterialPara3Dlg = new CModelSubAtMaterialPara3Dlg(this);
	m_pMaterialParaAlignStickDlg = new CModelSubMaterialParaAlignStickDlg(this);
	m_pAtMaterialParaAlignStickDlg = new CModelSubAtMaterialParaAlignStickDlg(this);
	m_pInspectionParaDlg = new CInspectionParaDlg(this);
	m_pStretchParaDlg = new CStretchParaDlg(this);
	m_pGlassParaDlg = new CGlassParaDlg(this);
	m_pAlignParaDlg = new CAlignParaDlg(this);
	m_pAlignPara2Dlg = new CAlignPara2Dlg(this);
	m_pModelSubManualParaDlg = new CModelSubManualParaDlg(this);
	m_pPpaParaDlg = new CModelSubPpaParaDlg(this);
}
//-------------------------------------------------------------------------------
void CModelDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (Is_Comp_Safe_Hwnd() == FALSE)
	{
		return;
	}
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	int	nOffset		= 5;
	int nLamp_Size	= 5;
	int nMainBtn_Size_X = 100;
	int nMainBtn_Size_Y = nMainBtn_Size_X / 2;
	CRect	RectBtn, RectLamp, RectLine, RectSubPage;
	RectBtn.left	= nOffset * 2;
	RectBtn.top		= nOffset;
	RectBtn.right	= RectBtn.left + nMainBtn_Size_X;
	RectBtn.bottom	= RectBtn.top + nMainBtn_Size_Y;	
	RectLamp.left	= RectBtn.left;
	RectLamp.top	= RectBtn.top + nLamp_Size;
	RectLamp.right	= RectBtn.right;
	RectLamp.bottom = RectBtn.bottom + nLamp_Size;
	for (int k = 0; k < eMODEL_MENU_MAX; k++)
	{
		RectBtn.left	= (nOffset * 2) + (nMainBtn_Size_X * k) + (nOffset * k);
		RectBtn.right	= RectBtn.left + nMainBtn_Size_X;
		RectLamp.left	= RectBtn.left;
		RectLamp.right	= RectBtn.right;
		m_btnModel[k].MoveWindow(RectBtn);
		m_stcModel_Dlg_Lamp[k].MoveWindow(RectLamp);
	}
	RectLine.left	= nOffset;
	RectLine.top	= RectLamp.bottom + nOffset;
	RectLine.right	= cx - nMainBtn_Size_X - nLamp_Size - (nOffset * 2);
	RectLine.bottom = RectLine.top + 2;
	GetDlgItem(IDC_STATIC_LINE_W)->MoveWindow(RectLine);
	//--------------------------------------------------------------------------------
	RectBtn.left	= cx - nMainBtn_Size_X - nOffset;
	RectBtn.top		= RectLine.top + (nOffset * 2);
	RectBtn.right	= RectBtn.left + nMainBtn_Size_X;
	RectBtn.bottom	= RectBtn.top + nMainBtn_Size_Y;
	RectLamp.left	= RectBtn.left - nLamp_Size;
	RectLamp.top	= RectBtn.top;
	RectLamp.right	= RectBtn.right - nLamp_Size;
	RectLamp.bottom = RectBtn.bottom;	
	m_btnSubModel[0].MoveWindow(RectBtn);
	m_stcModel_Sub_Dlg_Lamp[0].MoveWindow(RectLamp);
	for (int k = 1; k < MAX_MODEL_SUB_DLG; k++)
	{
		RectBtn.top		= RectBtn.top + nMainBtn_Size_Y + nOffset;
		RectBtn.bottom	= RectBtn.top + nMainBtn_Size_Y;
		RectLamp.top	= RectBtn.top;
		RectLamp.bottom = RectBtn.bottom;		
		m_btnSubModel[k].MoveWindow(RectBtn);
		m_stcModel_Sub_Dlg_Lamp[k].MoveWindow(RectLamp);
	}
	RectLine.left	= RectLamp.left - nOffset;
	RectLine.top	= RectLine.top + nOffset;
	RectLine.right	= RectLine.left + 2;
	RectLine.bottom = cy - nOffset;  //cy - nMainBtn_Size_Y - nOffset;
	GetDlgItem(IDC_STATIC_LINE_H)->MoveWindow(RectLine);

	RectBtn.left = cx - nMainBtn_Size_X - nOffset;
	RectBtn.top = cy - nMainBtn_Size_Y - nOffset;
	RectBtn.right = cx - nOffset;
	RectBtn.bottom = cy - nOffset;
	GetDlgItem(IDC_BTN_MODEL_SAVE)->MoveWindow(RectBtn);

	RectSubPage.left = nOffset;// *2;
	RectSubPage.top		= RectLine.top + nOffset;
	RectSubPage.right	= RectLine.left - nOffset;
	RectSubPage.bottom	= RectBtn.bottom - nOffset;  //RectLine.bottom - nOffset;
	GetDlgItem(IDC_STATIC_MODEL_SUB_PAGE)->MoveWindow(RectSubPage);

	GetDlgItem(IDC_STATIC_MODEL_SUB_PAGE)->GetWindowRect(&RectSubPage);
	
	ScreenToClient(RectSubPage); // 스크린 부터 화면까지의 거리 빼기

	m_pModelChangeSubDlg->MoveWindow(RectSubPage);
	m_pMaterialParaDlg->MoveWindow(RectSubPage);
	m_pMaterialPara2Dlg->MoveWindow(RectSubPage);
	m_pMaterialPara3Dlg->MoveWindow(RectSubPage);
	m_pAtMaterialParaDlg->MoveWindow(RectSubPage);
	m_pAtMaterialPara2Dlg->MoveWindow(RectSubPage);
	m_pAtMaterialPara3Dlg->MoveWindow(RectSubPage);
	m_pMaterialParaAlignStickDlg->MoveWindow(RectSubPage);
	m_pAtMaterialParaAlignStickDlg->MoveWindow(RectSubPage);
	m_pInspectionParaDlg->MoveWindow(RectSubPage);
	m_pStretchParaDlg->MoveWindow(RectSubPage);
	m_pGlassParaDlg->MoveWindow(RectSubPage);
	m_pAlignParaDlg->MoveWindow(RectSubPage);
	m_pAlignPara2Dlg->MoveWindow(RectSubPage);
	m_pModelSubManualParaDlg->MoveWindow(RectSubPage);
	m_pPpaParaDlg->MoveWindow(RectSubPage);
}
//-------------------------------------------------------------------------------
BOOL	CModelDlg::Is_Comp_Safe_Hwnd()
{
	if (GetDlgItem(IDC_BTN_MODEL_MENU_MODEL_CHAGE)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_BTN_MODEL_MENU_MATERIAL_PARA)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_BTN_MODEL_MENU_AT_MATERIAL_PARA)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_BTN_MODEL_MENU_INSPECTION_PARA)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_BTN_MODEL_MENU_STRETCH_PARA)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_BTN_MODEL_MENU_GLASS_PARA)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_BTN_MODEL_MENU_ALIGN_PARA)->GetSafeHwnd() == NULL) return FALSE;

	if (GetDlgItem(IDC_STATIC_LAMP_MODEL_CHANGE)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_LAMP_MODEL_MATERIAL_PARA)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_LAMP_MODEL_AT_MATERIAL_PARA)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_LAMP_MODEL_INSPECTION_PARA)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_LAMP_MODEL_STRETCH_PARA)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_LAMP_MODEL_GLASS_PARA)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_LAMP_MODEL_ALIGN_PARA)->GetSafeHwnd() == NULL) return FALSE;

	if (GetDlgItem(IDC_STATIC_LINE_W)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_LINE_H)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_BUTTON_SUB_PAGE1)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_BUTTON_SUB_PAGE2)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_BUTTON_SUB_PAGE3)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_SUB_PAGE_LAMP_1)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_SUB_PAGE_LAMP_2)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_SUB_PAGE_LAMP_3)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_MODEL_SUB_PAGE)->GetSafeHwnd() == NULL) return FALSE;
	return TRUE;
}
//-------------------------------------------------------------------------------
void CModelDlg::ShowDlg(int nDlgNo, int nSubDlgNo)
{
	Dlg_HideWindow();

	CString strCurModelName = SharedInfo::FindRecipeName(SharedInfo::Active.nActiveRecipeNum);
	if ((nDlgNo != eMODEL_MENU_MODEL_CHANGE) && (strCurModelName == _T("")))
	{
		nDlgNo = eMODEL_MENU_MODEL_CHANGE;
	}
	for (int k = 0; k < eMODEL_MENU_MAX; k++)
	{
		if (k == nDlgNo)
		{
			m_stcModel_Dlg_Lamp[k].SetBackgroundColor(BTN_LAMP_ON);
		}
		else
		{
			m_stcModel_Dlg_Lamp[k].SetBackgroundColor(BTN_LAMP_OFF);
		}
	}
	for (int k = 0; k < MAX_MODEL_SUB_DLG; k++)
	{
		if (k == nSubDlgNo)
		{
			m_stcModel_Sub_Dlg_Lamp[k].SetBackgroundColor(BTN_LAMP_ON);
		}
		else
		{
			m_stcModel_Sub_Dlg_Lamp[k].SetBackgroundColor(BTN_LAMP_OFF);
		}
	}
	switch (nDlgNo)
	{
	case eMODEL_MENU_MODEL_CHANGE:
	{
		if (nSubDlgNo == MODEL_SUB_PAGE1_DLG)
		{
			m_pModelChangeSubDlg->ShowWindow(TRUE);
		}
		break;
	}
	case eMODEL_MENU_MATERIAL_PARA:
	{
		if (nSubDlgNo == MODEL_SUB_PAGE1_DLG)
		{
			if (Devs::GetIsAlignSitck(SharedInfo::Active.nActiveRecipeNum) == TRUE)
				m_pMaterialParaAlignStickDlg->ShowWindow(TRUE);
			else
				m_pMaterialParaDlg->ShowWindow(TRUE);
		}
		else if (nSubDlgNo == MODEL_SUB_PAGE2_DLG)
		{
			if (Devs::GetIsAlignSitck(SharedInfo::Active.nActiveRecipeNum) == FALSE)
				m_pMaterialPara2Dlg->ShowWindow(TRUE);
		}
		else if (nSubDlgNo == MODEL_SUB_PAGE3_DLG)
		{
			if (Devs::GetIsAlignSitck(SharedInfo::Active.nActiveRecipeNum) == FALSE)
				m_pMaterialPara3Dlg->ShowWindow(TRUE);
		}
		break;
	}
	case eMODEL_MENU_AT_MATERIAL_PARA:
	{
		if (nSubDlgNo == MODEL_SUB_PAGE1_DLG)
		{
			if (Devs::GetIsAlignSitck(SharedInfo::Active.nActiveRecipeNum) == TRUE)
				m_pAtMaterialParaAlignStickDlg->ShowWindow(TRUE);
			else
				m_pAtMaterialParaDlg->ShowWindow(TRUE);
		}
		else if (nSubDlgNo == MODEL_SUB_PAGE2_DLG)
		{
			if (Devs::GetIsAlignSitck(SharedInfo::Active.nActiveRecipeNum) == FALSE)
				m_pAtMaterialPara2Dlg->ShowWindow(TRUE);
		}
		else if (nSubDlgNo == MODEL_SUB_PAGE3_DLG)
		{
			if (Devs::GetIsAlignSitck(SharedInfo::Active.nActiveRecipeNum) == FALSE)
				m_pAtMaterialPara3Dlg->ShowWindow(TRUE);
		}
		break;
	}
	case eMODEL_MENU_INSPECTION_PARA:
	{
		if (nSubDlgNo == MODEL_SUB_PAGE1_DLG)
			m_pInspectionParaDlg->ShowWindow(TRUE);
		break;
	}
	case eMODEL_MENU_STRETCH_PARA:
	{
		if (nSubDlgNo == MODEL_SUB_PAGE1_DLG)
		{
			m_pStretchParaDlg->ShowWindow(TRUE);
		}
		break;
	}
	case eMODEL_MENU_GLASS_PARA:
	{
		if (nSubDlgNo == MODEL_SUB_PAGE1_DLG)
		{
			m_pGlassParaDlg->ShowWindow(TRUE);
		}
		break;
	}
	case eMODEL_MENU_ALIGN_PARA:
	{
		if (nSubDlgNo == MODEL_SUB_PAGE1_DLG)
			m_pAlignParaDlg->ShowWindow(TRUE);
		else if (nSubDlgNo == MODEL_SUB_PAGE2_DLG)
			m_pAlignPara2Dlg->ShowWindow(TRUE);
		break;
	}
	case eMODEL_MENU_MANUAL_PARA:
	{
		if (nSubDlgNo == MODEL_SUB_PAGE1_DLG)
			m_pModelSubManualParaDlg->ShowWindow(TRUE);
		break;
	}
	case eMODEL_MENU_PPA_PARA:
	{
		if (nSubDlgNo == MODEL_SUB_PAGE1_DLG)
		{
			m_pPpaParaDlg->ShowWindow(TRUE);
		}
		break;
	}
	}

	for (int k = 0; k < eMODEL_MENU_MAX; k++)
	{
		m_btnModel[k].SetFocus();
	}
	for (int k = 0; k < MAX_MODEL_SUB_DLG; k++)
	{
		m_btnSubModel[k].SetFocus();
	}
}
//-------------------------------------------------------------------------------
BOOL CModelDlg::RecalcLayout()
{
	return TRUE;
}
//-------------------------------------------------------------------------------
BOOL CModelDlg::ShowData()
{
	return TRUE;
}
//----------------------------------------------------------------------------
void	CModelDlg::ChangeUI()
{
	//저장된 데이터를 UI에 표시
}
//-------------------------------------------------------------------------------
void CModelDlg::Dlg_HideWindow()
{
	m_pModelChangeSubDlg->ShowWindow(SW_HIDE);
	m_pMaterialParaDlg->ShowWindow(SW_HIDE);
	m_pMaterialPara2Dlg->ShowWindow(SW_HIDE);
	m_pMaterialPara3Dlg->ShowWindow(SW_HIDE);
	m_pAtMaterialParaDlg->ShowWindow(SW_HIDE);
	m_pAtMaterialPara2Dlg->ShowWindow(SW_HIDE);
	m_pAtMaterialPara3Dlg->ShowWindow(SW_HIDE);
	m_pMaterialParaAlignStickDlg->ShowWindow(SW_HIDE);
	m_pAtMaterialParaAlignStickDlg->ShowWindow(SW_HIDE);
	m_pInspectionParaDlg->ShowWindow(SW_HIDE);
	m_pStretchParaDlg->ShowWindow(SW_HIDE);
	m_pGlassParaDlg->ShowWindow(SW_HIDE);
	m_pAlignParaDlg->ShowWindow(SW_HIDE);
	m_pAlignPara2Dlg->ShowWindow(SW_HIDE);
	m_pModelSubManualParaDlg->ShowWindow(SW_HIDE);
	m_pPpaParaDlg->ShowWindow(SW_HIDE);
}
//-------------------------------------------------------------------------------
BOOL CModelDlg::DestroyWindow()
{
	return CDialogEx::DestroyWindow();
}
//-------------------------------------------------------------------------------
void CModelDlg::OnBnClickedButtonSubPage1()
{
	if (m_nCurrentNo == eMODEL_MENU_MODEL_CHANGE) return;
	m_nCurrentSubNo = MODEL_SUB_PAGE1_DLG;
	ShowDlg(m_nCurrentNo, m_nCurrentSubNo);
}
//-------------------------------------------------------------------------------
void CModelDlg::OnBnClickedButtonSubPage2()
{
	if (m_nCurrentNo == eMODEL_MENU_MODEL_CHANGE) return;
	m_nCurrentSubNo = MODEL_SUB_PAGE2_DLG;
	ShowDlg(m_nCurrentNo, m_nCurrentSubNo);
}
//-------------------------------------------------------------------------------
void CModelDlg::OnBnClickedButtonSubPage3()
{
	if (m_nCurrentNo == eMODEL_MENU_MODEL_CHANGE) return;
	m_nCurrentSubNo = MODEL_SUB_PAGE3_DLG;
	ShowDlg(m_nCurrentNo, m_nCurrentSubNo);
}
//-------------------------------------------------------------------------------
void CModelDlg::OnBnClickedButtonModelChange()
{
	m_nCurrentNo = eMODEL_MENU_MODEL_CHANGE;
	m_nCurrentSubNo = MODEL_SUB_PAGE1_DLG;
	ShowDlg(m_nCurrentNo, m_nCurrentSubNo);
}
//-------------------------------------------------------------------------------
void CModelDlg::OnBnClickedButtonMaterialPara()
{
	m_nCurrentNo = eMODEL_MENU_MATERIAL_PARA;
	m_nCurrentSubNo = MODEL_SUB_PAGE1_DLG;
	ShowDlg(m_nCurrentNo, m_nCurrentSubNo);
}
//-------------------------------------------------------------------------------
void CModelDlg::OnBnClickedButtonAtMaterialPara()
{
	m_nCurrentNo = eMODEL_MENU_AT_MATERIAL_PARA;
	m_nCurrentSubNo = MODEL_SUB_PAGE1_DLG;
	ShowDlg(m_nCurrentNo, m_nCurrentSubNo);
}
//-------------------------------------------------------------------------------
void CModelDlg::OnBnClickedButtonInspectionPara()
{
	m_nCurrentNo = eMODEL_MENU_INSPECTION_PARA;
	m_nCurrentSubNo = MODEL_SUB_PAGE1_DLG;
	ShowDlg(m_nCurrentNo, m_nCurrentSubNo);
}
//-------------------------------------------------------------------------------
void CModelDlg::OnBnClickedButtonStretchPara()
{
	m_nCurrentNo = eMODEL_MENU_STRETCH_PARA;
	m_nCurrentSubNo = MODEL_SUB_PAGE1_DLG;
	ShowDlg(m_nCurrentNo, m_nCurrentSubNo);
}
//-------------------------------------------------------------------------------
void CModelDlg::OnBnClickedBtnModelMenuGlassPara()
{
	m_nCurrentNo = eMODEL_MENU_GLASS_PARA;
	m_nCurrentSubNo = MODEL_SUB_PAGE1_DLG;
	ShowDlg(m_nCurrentNo, m_nCurrentSubNo);
}

void CModelDlg::OnBnClickedBtnModelMenuAlignPara()
{
	m_nCurrentNo = eMODEL_MENU_ALIGN_PARA;
	m_nCurrentSubNo = MODEL_SUB_PAGE1_DLG;
	ShowDlg(m_nCurrentNo, m_nCurrentSubNo);
}

void CModelDlg::OnBnClickedBtnModelMenuManualPara()
{
	m_nCurrentNo = eMODEL_MENU_MANUAL_PARA;
	m_nCurrentSubNo = MODEL_SUB_PAGE1_DLG;
	ShowDlg(m_nCurrentNo, m_nCurrentSubNo);
}

void CModelDlg::OnBnClickedBtnModelMenuPpaPara()
{
	m_nCurrentNo = eMODEL_MENU_PPA_PARA;
	m_nCurrentSubNo = MODEL_SUB_PAGE1_DLG;
	ShowDlg(m_nCurrentNo, m_nCurrentSubNo);
}

void CModelDlg::OnBnClickedBtnModelSave()
{
	DWORD Result;

	Result = AfxMessageBox(_T("Save?"), MB_OKCANCEL);

	BeginWaitCursor();
	if (Result == IDOK)
	{
		switch (m_nCurrentNo)
		{
		case eMODEL_MENU_MODEL_CHANGE:
			break;

		case eMODEL_MENU_MATERIAL_PARA:
			if (Devs::GetIsAlignSitck(SharedInfo::Active.nActiveRecipeNum) == TRUE)
				m_pMaterialParaAlignStickDlg->SavePara();
			else
			{
				if (m_nCurrentSubNo == MODEL_SUB_PAGE1_DLG)
					m_pMaterialParaDlg->SavePara();
				else if (m_nCurrentSubNo == MODEL_SUB_PAGE2_DLG)
					m_pMaterialPara2Dlg->SavePara();
				else if (m_nCurrentSubNo == MODEL_SUB_PAGE3_DLG)
					m_pMaterialPara3Dlg->SavePara();
			}
			break;

		case eMODEL_MENU_AT_MATERIAL_PARA:
			if (Devs::GetIsAlignSitck(SharedInfo::Active.nActiveRecipeNum) == TRUE)
				m_pAtMaterialParaAlignStickDlg->SavePara();
			else
			{
				if (m_nCurrentSubNo == MODEL_SUB_PAGE1_DLG)
					m_pAtMaterialParaDlg->SavePara();
				else if (m_nCurrentSubNo == MODEL_SUB_PAGE2_DLG)
					m_pAtMaterialPara2Dlg->SavePara();
				else if (m_nCurrentSubNo == MODEL_SUB_PAGE3_DLG)
					m_pAtMaterialPara3Dlg->SavePara();
			}
			break;

		case eMODEL_MENU_INSPECTION_PARA:
			if (m_nCurrentSubNo == MODEL_SUB_PAGE1_DLG)
				m_pInspectionParaDlg->SavePara();
			break;

		case eMODEL_MENU_STRETCH_PARA:
			m_pStretchParaDlg->SavePara();
			break;

		case eMODEL_MENU_GLASS_PARA:
			m_pGlassParaDlg->SavePara();
			break;

		case eMODEL_MENU_ALIGN_PARA:
			if (m_nCurrentSubNo == MODEL_SUB_PAGE1_DLG)
				m_pAlignParaDlg->SavePara();
			else if (m_nCurrentSubNo == MODEL_SUB_PAGE2_DLG)
				m_pAlignPara2Dlg->SavePara();
			break;

		case eMODEL_MENU_MANUAL_PARA:
			if (m_nCurrentSubNo == MODEL_SUB_PAGE1_DLG)
				m_pModelSubManualParaDlg->SavePara();
			break;

		case eMODEL_MENU_PPA_PARA:
			m_pPpaParaDlg->SavePara();
			break;
		}
	}

#if 0 //KJT Check !!
#pragma region //KJT 20210410
	CString m_strNewDirName;
	RECIPE_CHANGE_REPORT_BLOCK MachineRecipeBlock;
	CString strActiveModelName = Devs::FindCurrentRecipeName(SharedInfo::Active.nActiveRecipeNum);

	MachineRecipeBlock.RecipeChangeType = 1;
	MachineRecipeBlock.RecipeNumber = SharedInfo::Active.nActiveRecipeNum;
	MachineRecipeBlock.RecipeText = 0;
	MachineRecipeBlock.RecipeVersionSequenceNumber = 1; //CModelData::FrameStage.Info.nRecipeVersionSequence;
	MachineRecipeBlock.UnitNumber = 1;

	memset(MachineRecipeBlock.OperatorID, 0x20, sizeof(MachineRecipeBlock.OperatorID));
	memcpy(MachineRecipeBlock.OperatorID, SharedInfo::OperatorID, sizeof(MachineRecipeBlock.OperatorID));

	MachineRecipeBlock.RecipeText = strActiveModelName[1];
	MachineRecipeBlock.RecipeText <<= 8;
	MachineRecipeBlock.RecipeText |= strActiveModelName[0];

	Devs::CimMotion.ReportRecipeChangeBlock(MachineRecipeBlock);
#pragma endregion
#endif

	EndWaitCursor();
}
