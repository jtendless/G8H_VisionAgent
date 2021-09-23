// Manual_Sub_Loader_Manual.cpp: 구현 파일
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "Manual_Sub_Loader_Manual.h"
#include "afxdialogex.h"


// CManual_Sub_Loader_Manual 대화 상자

IMPLEMENT_DYNAMIC(CManual_Sub_Loader_Manual, CDialogEx)

CManual_Sub_Loader_Manual::CManual_Sub_Loader_Manual(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_MANUAL_SUB_LOADER_MANUAL, pParent)
{
	Create(IDD_DLG_MANUAL_SUB_LOADER_MANUAL, pParent);
}

CManual_Sub_Loader_Manual::~CManual_Sub_Loader_Manual()
{
}

void CManual_Sub_Loader_Manual::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CManual_Sub_Loader_Manual, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MANUAL_LOADER_Z_WAIT_POS, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualLoaderZWaitPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LAODER_MANUAL_LOADER_Z_STICK_LOAD_IN_BOX_1ST_POS, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLaoderManualLoaderZStickLoadInBox1stPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LAODER_MANUAL_LOADER_Z_STICK_LOAD_IN_BOX_2ND_POS, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLaoderManualLoaderZStickLoadInBox2ndPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MANUAL_LOADER_Z_STICK_UNLOAD_IN_INSPECTION_STAGE_POS, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualLoaderZStickUnloadToInspectionStagePos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MANUAL_LOADER_Z_STICK_LOAD_IN_STAGE_1ST_POS, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualLoaderZStickLoadInStage1stPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MANUAL_LOADER_Z_STICK_LOAD_IN_STAGE_2ND_POS, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualLoaderZStickLoadInStage2ndPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MANUAL_LOADER_Z_STICK_UNLOAD_IN_BOX_POS, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualLoaderZStickUnloadInBoxPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MANUAL_LOADER_X_WAIT_POS, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualLoaderXWaitPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MANUAL_LOADER_X_ALIGN_POS, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualLoaderXAlignPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MANUAL_STICK_VAC_ON_1, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualStickVacOn1)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MANUAL_STICK_VAC_ON_2, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualStickVacOn2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MANUAL_STICK_VAC_ON_3, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualStickVacOn3)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MANUAL_STICK_VAC_ON_4, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualStickVacOn4)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MANUAL_STICK_VAC_ON_5, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualStickVacOn5)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MANUAL_STICK_VAC_ACTIVE_ON, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualStickVacActiveOn)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MANUAL_STICK_VAC_ALL_ON, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualStickVacAllOn)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MANUAL_STICK_VAC_OFF_1, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualStickVacOff1)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MANUAL_STICK_VAC_OFF_2, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualStickVacOff2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MANUAL_STICK_VAC_OFF_3, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualStickVacOff3)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MANUAL_STICK_VAC_OFF_4, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualStickVacOff4)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MANUAL_STICK_VAC_OFF_5, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualStickVacOff5)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MANUAL_STICK_VAC_ACTIVE_OFF, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualStickVacActiveOff)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MANUAL_STICK_VAC_ALL_OFF, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualStickVacAllOff)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MANUAL_PAPER_VAC_ON_1, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualPaperVacOn1)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MANUAL_PAPER_VAC_ON_2, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualPaperVacOn2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MANUAL_PAPER_VAC_ON_3, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualPaperVacOn3)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MANUAL_PAPER_VAC_ON_4, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualPaperVacOn4)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MANUAL_PAPER_VAC_ACTIVE_ON, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualPaperVacActiveOn)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MANUAL_PAPER_VAC_ALL_ON, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualPaperVacAllOn)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MANUAL_PAPER_VAC_OFF_1, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualPaperVacOff1)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MANUAL_PAPER_VAC_OFF_2, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualPaperVacOff2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MANUAL_PAPER_VAC_OFF_3, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualPaperVacOff3)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MANUAL_PAPER_VAC_OFF_4, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualPaperVacOff4)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MANUAL_PAPER_VAC_ACTIVE_OFF, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualPaperVacActiveOff)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MANUAL_PAPER_VAC_ALL_OFF, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualPaperVacAllOff)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MANUAL_CYLINDER_UP, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualCylinderUp)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MANUAL_CYLINDER_DOWN, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualCylinderDown)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_IONIZER_ON, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderIonizerOn)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_IONIZER_OFF, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderIonizerOff)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MANUAL_LOADER_Y_WAIT_POS, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualLoaderYWaitPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LAODER_MANUAL_LOADER_Y_STICK_LOAD_POS, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLaoderManualLoaderYStickLoadPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LAODER_MANUAL_LOADER_Y_STICK_UNLOAD_POS, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLaoderManualLoaderYStickUnloadPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LAODER_MANUAL_LOADER_Y_INSPECTION_POS, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLaoderManualLoaderYInspectionPos)

	//ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MANUAL_LOADER_ZL_WAIT_POS, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualLoaderZlWaitPos)
	//ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MANUAL_LOADER_ZL_DOWN_POS, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualLoaderZlDownPos)
	//ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MANUAL_LOADER_ZR_WAIT_POS, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualLoaderZrWaitPos)
	//ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MANUAL_LOADER_ZR_DOWN_POS, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualLoaderZrDownPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MANUAL_LOADER_BARCODE_READ, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualLoaderBarcodeRead)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MANUAL_LOADER_BARCODE_VIEW, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualLoaderBarcodeView)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_MANUAL_LOADER_X_PICK_POS, &CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualLoaderXPickPos)
END_MESSAGE_MAP()


// CManual_Sub_Loader_Manual 메시지 처리기

BOOL CManual_Sub_Loader_Manual::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	InitCtrl();

	return TRUE;
}

void	CManual_Sub_Loader_Manual::InitCtrl()
{
	int k = 0;

	//Loader Z
	m_stLamp_Work[_eMANUAL_LOADER_INDEX_LOADER_Z_WAIT_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_LOADER_MANUAL_LOADER_Z_WAIT_POS, this);
	m_stLamp_Work[_eMANUAL_LOADER_INDEX_LOADER_Z_STICK_LOAD_IN_BOX_1ST_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_LOADER_MANUAL_LOADER_Z_STICK_LOAD_IN_BOX_1ST_POS, this);
	m_stLamp_Work[_eMANUAL_LOADER_INDEX_LOADER_Z_STICK_LOAD_IN_BOX_2ND_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_LOADER_MANUAL_LOADER_Z_STICK_LOAD_IN_BOX_2ND_POS, this);
	m_stLamp_Work[_eMANUAL_LOADER_INDEX_LOADER_Z_STICK_UNLOAD_TO_STAGE_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_LOADER_MANUAL_LOADER_Z_STICK_UNLOAD_TO_STAGE_POS, this);
	m_stLamp_Work[_eMANUAL_LOADER_INDEX_LOADER_Z_STICK_LOAD_IN_STAGE_1ST_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_LOADER_MANUAL_LOADER_Z_STICK_LOAD_IN_STAGE_1ST_POS, this);
	m_stLamp_Work[_eMANUAL_LOADER_INDEX_LOADER_Z_STICK_LOAD_IN_STAGE_2ND_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_LOADER_MANUAL_LOADER_Z_STICK_LOAD_IN_STAGE_2ND_POS, this);
	m_stLamp_Work[_eMANUAL_LOADER_INDEX_LOADER_Z_STICK_UNLOAD_TO_BOX_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_LOADER_MANUAL_LOADER_Z_STICK_UNLOAD_TO_BOX_POS, this);

	//21.02.05 sjc
	//LOADER ZL, ZR
	m_stLamp_Work[_eMANUAL_LOADER_INDEX_LOADER_ZL_WAIT_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_LOADER_MANUAL_LOADER_ZL_WAIT_POS, this);
	m_stLamp_Work[_eMANUAL_LOADER_INDEX_LOADER_ZR_WAIT_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_LOADER_MANUAL_LOADER_ZR_WAIT_POS, this);
	m_stLamp_Work[_eMANUAL_LOADER_INDEX_LOADER_ZL_DOWN_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_LOADER_MANUAL_LOADER_ZL_DOWN_POS, this);
	m_stLamp_Work[_eMANUAL_LOADER_INDEX_LOADER_ZR_DOWN_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_LOADER_MANUAL_LOADER_ZR_DOWN_POS, this);

	//21.02.10 sjc
	//Loader y
	m_stLamp_Work[_eMANUAL_LOADER_INDEX_LOADER_Y_WAIT_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_LOADER_MANUAL_LOADER_Y_WAIT_POS, this);
	m_stLamp_Work[_eMANUAL_LOADER_INDEX_LOADER_Y_STICK_LOAD_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_LOADER_MANUAL_LOADER_Y_STICK_LOAD_POS, this);
	m_stLamp_Work[_eMANUAL_LOADER_INDEX_LOADER_Y_STICK_UNLOAD_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_LOADER_MANUAL_LOADER_Y_STICK_UNLOAD_POS, this);
	m_stLamp_Work[_eMANUAL_LOADER_INDEX_LOADER_Y_INSPECTION_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_LOADER_MANUAL_LOADER_Y_INSPECTION_POS, this);

	//Loader X
	m_stLamp_Work[_eMANUAL_LOADER_INDEX_LOADER_X_WAIT_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_LOADER_MANUAL_LOADER_X_WAIT_POS, this);
	m_stLamp_Work[_eMANUAL_LOADER_INDEX_LOADER_X_ALIGN_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_LOADER_MANUAL_LOADER_X_ALIGN_POS, this);
	m_stLamp_Work[_eMANUAL_LOADER_INDEX_LOADER_X_PICKUP_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_LOADER_MANUAL_LOADER_X_PICKUP_POS, this);

	for (k = 0; k < _eMANUAL_LOADER_INDEX_MAX; k++)
	{
		m_stLamp_Work[k].SetParaChangeColor(BK_GND);
		m_stLamp_Work[k].SetParaOriginColor(STATEBAR_NAME_BK_RGB);
		m_stLamp_Work[k].SetBackgroundColor(STATEBAR_NAME_BK_RGB);
		m_stLamp_Work[k].SetTextColor(LED_LAMP_OFF);
		m_stLamp_Work[k].SetBackgroundColor(LED_LAMP_OFF);
	}

#pragma region //IO
	//Stick Vacuum
	m_stcLamp_StickVac[_eMANUAL_LOADER_STICK_VAC_1].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_LOADER_MANUAL_STICK_VAC_ON_1, this);
	m_stcLamp_StickVac[_eMANUAL_LOADER_STICK_VAC_2].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_LOADER_MANUAL_STICK_VAC_ON_2, this);
	m_stcLamp_StickVac[_eMANUAL_LOADER_STICK_VAC_3].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_LOADER_MANUAL_STICK_VAC_ON_3, this);
	m_stcLamp_StickVac[_eMANUAL_LOADER_STICK_VAC_4].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_LOADER_MANUAL_STICK_VAC_ON_4, this);
	m_stcLamp_StickVac[_eMANUAL_LOADER_STICK_VAC_5].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_LOADER_MANUAL_STICK_VAC_ON_5, this);
	m_stcLamp_StickVac[_eMANUAL_LOADER_STICK_VAC_ATCIVE].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_LOADER_MANUAL_STICK_ACTIVE_VAC_ON, this);
	m_stcLamp_StickVac[_eMANUAL_LOADER_STICK_VAC_ALL].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_LOADER_MANUAL_STICK_ALL_VAC_ON, this);
	for (k = 0; k < _eMANUAL_LOADER_STICK_VAC_MAX; k++)
	{
		m_stcLamp_StickVac[k].SetParaChangeColor(BK_GND);
		m_stcLamp_StickVac[k].SetParaOriginColor(STATEBAR_NAME_BK_RGB);
		m_stcLamp_StickVac[k].SetBackgroundColor(STATEBAR_NAME_BK_RGB);
		m_stcLamp_StickVac[k].SetTextColor(LED_LAMP_OFF);
		m_stcLamp_StickVac[k].SetBackgroundColor(LED_LAMP_OFF);
	}

	//Paper Vacuum
	m_stcLamp_PaperVac[_eMANUAL_LOADER_PAPER_VAC_1].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_LOADER_MANUAL_PAPER_VAC_ON_1, this);
	m_stcLamp_PaperVac[_eMANUAL_LOADER_PAPER_VAC_2].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_LOADER_MANUAL_PAPER_VAC_ON_2, this);
	m_stcLamp_PaperVac[_eMANUAL_LOADER_PAPER_VAC_3].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_LOADER_MANUAL_PAPER_VAC_ON_3, this);
	m_stcLamp_PaperVac[_eMANUAL_LOADER_PAPER_VAC_4].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_LOADER_MANUAL_PAPER_VAC_ON_4, this);
	m_stcLamp_PaperVac[_eMANUAL_LOADER_PAPER_VAC_ATCIVE].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_LOADER_MANUAL_PAPER_ACTIVE_VAC_ON, this);
	m_stcLamp_PaperVac[_eMANUAL_LOADER_PAPER_VAC_ALL].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_LOADER_MANUAL_PAPER_ALL_VAC_ON, this);
	for (k = 0; k < _eMANUAL_LOADER_PAPER_VAC_MAX; k++)
	{
		m_stcLamp_PaperVac[k].SetParaChangeColor(BK_GND);
		m_stcLamp_PaperVac[k].SetParaOriginColor(STATEBAR_NAME_BK_RGB);
		m_stcLamp_PaperVac[k].SetBackgroundColor(STATEBAR_NAME_BK_RGB);
		m_stcLamp_PaperVac[k].SetTextColor(LED_LAMP_OFF);
		m_stcLamp_PaperVac[k].SetBackgroundColor(LED_LAMP_OFF);
	}

	//Cylinder
	m_stcLamp_Cylinder[_eMANUAL_LOADER_CYLINDER_UP].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_LOADER_MANUAL_CYLINDER_UP, this);
	m_stcLamp_Cylinder[_eMANUAL_LOADER_CYLINDER_DOWN].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_LOADER_MANUAL_CYLINDER_DOWN, this);
	for (k = 0; k < _eMANUAL_LOADER_CYLINDER_MAX; k++)
	{
		m_stcLamp_Cylinder[k].SetParaChangeColor(BK_GND);
		m_stcLamp_Cylinder[k].SetParaOriginColor(STATEBAR_NAME_BK_RGB);
		m_stcLamp_Cylinder[k].SetBackgroundColor(STATEBAR_NAME_BK_RGB);
		m_stcLamp_Cylinder[k].SetTextColor(LED_LAMP_OFF);
		m_stcLamp_Cylinder[k].SetBackgroundColor(LED_LAMP_OFF);
	}

	m_stcLamp_IonizerOn.SubclassDlgItem(IDC_LAMP_MANUAL_SUB_LOADER_IONIZER_ON, this);
	m_stcLamp_IonizerOn.SetParaChangeColor(BK_GND);
	m_stcLamp_IonizerOn.SetParaOriginColor(STATEBAR_NAME_BK_RGB);
	m_stcLamp_IonizerOn.SetBackgroundColor(STATEBAR_NAME_BK_RGB);
	m_stcLamp_IonizerOn.SetTextColor(LED_LAMP_OFF);
	m_stcLamp_IonizerOn.SetBackgroundColor(LED_LAMP_OFF);
	m_stcLamp_IonizerOff.SubclassDlgItem(IDC_LAMP_MANUAL_SUB_LOADER_IONIZER_OFF, this);
	m_stcLamp_IonizerOff.SetParaChangeColor(BK_GND);
	m_stcLamp_IonizerOff.SetParaOriginColor(STATEBAR_NAME_BK_RGB);
	m_stcLamp_IonizerOff.SetBackgroundColor(STATEBAR_NAME_BK_RGB);
	m_stcLamp_IonizerOff.SetTextColor(LED_LAMP_OFF);
	m_stcLamp_IonizerOff.SetBackgroundColor(LED_LAMP_OFF);
#pragma endregion
}
void	CManual_Sub_Loader_Manual::InitPara()
{
	int k = 0;
	for (k = 0; k < _eMANUAL_LOADER_INDEX_MAX; k++)
	{
		m_nWork_State[k] = _eSTATE_NONE;
		m_stLamp_Work[k].SetBackgroundColor(LED_LAMP_OFF);

		m_bMotionDone[k] = FALSE;
		m_bPrevStatus_InPos[k] = FALSE;
	}

#pragma region //IO
	for (k = 0; k < _eMANUAL_LOADER_STICK_VAC_MAX; k++)
	{
		m_bPrevStatus_StickVac[k] = FALSE;
	}
	for (k = 0; k < _eMANUAL_LOADER_PAPER_VAC_MAX; k++)
	{
		m_bPrevStatus_PaperVac[k] = FALSE;
	}

	m_bPrevStatus_Cylinder[_eMANUAL_LOADER_CYLINDER_UP] = FALSE;
	m_bPrevStatus_Cylinder[_eMANUAL_LOADER_CYLINDER_DOWN] = FALSE;
#pragma endregion
}

void CManual_Sub_Loader_Manual::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow == TRUE)
	{
		InitPara();

		SetTimer(1, 100, NULL);
	}
	else if (bShow == FALSE)
	{
		KillTimer(1);
	}
}
//--------------------------------------------------------
void CManual_Sub_Loader_Manual::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (Is_Comp_Usable() == FALSE)	return;
}
//--------------------------------------------------------
void CManual_Sub_Loader_Manual::OnTimer(UINT_PTR nIDEvent)
{
	double dEnd_Tick, dWait_Tick;
	int k = 0;
	for (k = 0; k < _eMANUAL_LOADER_INDEX_MAX; k++)
	{
		if (m_nWork_State[k] == _eSTATE_START)
		{
			dEnd_Tick = GetTickCount();
			dWait_Tick = (dEnd_Tick - m_dMotion_Strt_Tick[k]) / 1000;
			if (dWait_Tick > 0.5)
			{
				m_dMotion_Strt_Tick[k] = GetTickCount();
				m_bWork_Lamp_State[k] = !m_bWork_Lamp_State[k];
			}
			if (m_bWork_Lamp_State[k])
			{
				m_stLamp_Work[k].SetBackgroundColor(LED_LAMP_ON);
			}
			else
			{
				m_stLamp_Work[k].SetBackgroundColor(LED_LAMP_OFF);
			}
		}
		if (m_nWork_State[k] == _eSTATE_COMPLETE)
		{
			m_stLamp_Work[k].SetBackgroundColor(LED_LAMP_ON);
			m_nWork_State[k] = _eSTATE_NONE;
		}
	}

#pragma region //Motion Done
	//Loader Z
	m_bMotionDone[_eMANUAL_LOADER_INDEX_LOADER_Z_WAIT_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_LOADER_Z, CManualData::m_ManualDataLoader.Info.m_dLoaderZ_Wait_Pos);
	m_bMotionDone[_eMANUAL_LOADER_INDEX_LOADER_Z_STICK_LOAD_IN_BOX_1ST_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_LOADER_Z, CManualData::m_ManualDataLoader.Info.m_dLoaderZ_StickLoadInBox1st_Pos);
	m_bMotionDone[_eMANUAL_LOADER_INDEX_LOADER_Z_STICK_LOAD_IN_BOX_2ND_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_LOADER_Z, CManualData::m_ManualDataLoader.Info.m_dLoaderZ_Vibration_Pos);
	m_bMotionDone[_eMANUAL_LOADER_INDEX_LOADER_Z_STICK_UNLOAD_TO_STAGE_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_LOADER_Z, CManualData::m_ManualDataLoader.Info.m_dLoaderZ_StickUnloadToStage_Pos);
	m_bMotionDone[_eMANUAL_LOADER_INDEX_LOADER_Z_STICK_LOAD_IN_STAGE_1ST_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_LOADER_Z, CManualData::m_ManualDataLoader.Info.m_dLoaderZ_StickLoadInStage1st_Pos);
	m_bMotionDone[_eMANUAL_LOADER_INDEX_LOADER_Z_STICK_LOAD_IN_STAGE_2ND_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_LOADER_Z, CManualData::m_ManualDataLoader.Info.m_dLoaderZ_Inspection_Pos);
	m_bMotionDone[_eMANUAL_LOADER_INDEX_LOADER_Z_STICK_UNLOAD_TO_BOX_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_LOADER_Z, CManualData::m_ManualDataLoader.Info.m_dLoaderZ_StickUnoadToBox_Pos);

	//21.02.10 sjc
	m_bMotionDone[_eMANUAL_LOADER_INDEX_LOADER_Y_WAIT_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_LOADER_YL, CManualData::m_ManualDataLoader.Info.m_dLoaderY_Wait_Pos);
	m_bMotionDone[_eMANUAL_LOADER_INDEX_LOADER_Y_STICK_LOAD_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_LOADER_YL, CManualData::m_ManualDataLoader.Info.m_dLoaderY_Stick_Load_Pos);
	m_bMotionDone[_eMANUAL_LOADER_INDEX_LOADER_Y_STICK_UNLOAD_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_LOADER_YL, CManualData::m_ManualDataLoader.Info.m_dLoaderY_Stick_Unload_Pos);
	m_bMotionDone[_eMANUAL_LOADER_INDEX_LOADER_Y_INSPECTION_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_LOADER_YL, CManualData::m_ManualDataLoader.Info.m_dLoaderY_Inspection_Pos);
	
	//Loder X
	m_bMotionDone[_eMANUAL_LOADER_INDEX_LOADER_X_WAIT_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_LOADER_X, CManualData::m_ManualDataLoader.Info.m_dLoaderX_Wait_Pos);
	m_bMotionDone[_eMANUAL_LOADER_INDEX_LOADER_X_ALIGN_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_LOADER_X, CModelData::m_ModelSubManualPara.Info.dStickLoaderX_AlignPos);
	m_bMotionDone[_eMANUAL_LOADER_INDEX_LOADER_X_PICKUP_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_LOADER_X, CModelData::m_ModelSubManualPara.Info.dStickLoaderX_PickUpPos);

	//Loader ZL,R
	//m_bMotionDone[_eMANUAL_LOADER_INDEX_LOADER_ZL_WAIT_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_LOADER_ZL, CManualData::m_ManualDataLoader.Info.m_dLoaderZL_Wait_Pos);
	//m_bMotionDone[_eMANUAL_LOADER_INDEX_LOADER_ZR_WAIT_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_LOADER_ZR, CManualData::m_ManualDataLoader.Info.m_dLoaderZR_Wait_Pos);
	//m_bMotionDone[_eMANUAL_LOADER_INDEX_LOADER_ZL_DOWN_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_LOADER_ZL, CManualData::m_ManualDataLoader.Info.m_dLoaderZL_Down_Pos);
	//m_bMotionDone[_eMANUAL_LOADER_INDEX_LOADER_ZR_DOWN_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_LOADER_ZR, CManualData::m_ManualDataLoader.Info.m_dLoaderZR_Down_Pos);

	for (k = 0; k < _eMANUAL_LOADER_INDEX_MAX; k++)
	{
		if (m_bPrevStatus_InPos[k] != m_bMotionDone[k])
		{
			if (m_bMotionDone[k])
			{
				m_nWork_State[k] = _eSTATE_COMPLETE;
				m_stLamp_Work[k].SetBackgroundColor(LED_LAMP_ON);
			}
			else
				m_stLamp_Work[k].SetBackgroundColor(LED_LAMP_OFF);
		}
		m_bPrevStatus_InPos[k] = m_bMotionDone[k];
	}
#pragma endregion

#pragma region //IO
	//Stick Vac
	BOOL bVacStatus[5] = { FALSE, };
	BOOL bStatusActive = FALSE;
	for (k = 0; k < 5; k++)
	{
		//bVacStatus[k] = SharedInfo::DInputValue[_DIN_LD_STICK_VAC_1 + k];
		bVacStatus[k] = SharedInfo::DInputValue[_DIN_LD_STICK_VAC_1 - k]; //KJT 20210723 Junying
		//if (m_bPrevStatus_StickVac[k] != bVacStatus[k])
		if(1)
		{
			if (bVacStatus[k])
				m_stcLamp_StickVac[k].SetBackgroundColor(LED_LAMP_ON);
			else
				m_stcLamp_StickVac[k].SetBackgroundColor(LED_LAMP_OFF);
		}
		m_bPrevStatus_StickVac[k] = bVacStatus[k];
	}
	BOOL bStatusAll = bVacStatus[_eMANUAL_LOADER_STICK_VAC_1] &
		bVacStatus[_eMANUAL_LOADER_STICK_VAC_2] &
		bVacStatus[_eMANUAL_LOADER_STICK_VAC_3] &
		bVacStatus[_eMANUAL_LOADER_STICK_VAC_4] &
		bVacStatus[_eMANUAL_LOADER_STICK_VAC_5];
	if (m_bPrevStatus_StickVac[_eMANUAL_LOADER_STICK_VAC_ALL] != bStatusAll)
	{
		if (bStatusAll)
			m_stcLamp_StickVac[_eMANUAL_LOADER_STICK_VAC_ALL].SetBackgroundColor(LED_LAMP_ON);
		else
			m_stcLamp_StickVac[_eMANUAL_LOADER_STICK_VAC_ALL].SetBackgroundColor(LED_LAMP_OFF);
	}
	m_bPrevStatus_StickVac[_eMANUAL_LOADER_STICK_VAC_ALL] = bStatusAll;

	//Paper Vac
	//for (k = 0; k < 4; k++)
	//{
	//	bVacStatus[k] = SharedInfo::DInputValue[_DIN_LD_PAPER_VAC_1 + k];
	//	//if (m_bPrevStatus_PaperVac[k] != SharedInfo::DInputValue[_DIN_LD_PAPER_VAC_1 + k])
	//	if(1)
	//	{
	//		if (SharedInfo::DInputValue[_DIN_LD_PAPER_VAC_1 + k])
	//			m_stcLamp_PaperVac[k].SetBackgroundColor(LED_LAMP_ON);
	//		else
	//			m_stcLamp_PaperVac[k].SetBackgroundColor(LED_LAMP_OFF);
	//	}
	//	m_bPrevStatus_PaperVac[k] = SharedInfo::DInputValue[_DIN_LD_PAPER_VAC_1 + k];
	//}
	//bStatusAll = bVacStatus[_eMANUAL_LOADER_PAPER_VAC_1] & 
	//	bVacStatus[_eMANUAL_LOADER_PAPER_VAC_2] & 
	//	bVacStatus[_eMANUAL_LOADER_PAPER_VAC_3] & 
	//	bVacStatus[_eMANUAL_LOADER_PAPER_VAC_4];
	//if (m_bPrevStatus_PaperVac[_eMANUAL_LOADER_PAPER_VAC_ALL] != bStatusAll)
	//{
	//	if (bStatusAll)
	//		m_stcLamp_PaperVac[_eMANUAL_LOADER_PAPER_VAC_ALL].SetBackgroundColor(LED_LAMP_ON);
	//	else
	//		m_stcLamp_PaperVac[_eMANUAL_LOADER_PAPER_VAC_ALL].SetBackgroundColor(LED_LAMP_OFF);
	//}
	//m_bPrevStatus_PaperVac[_eMANUAL_LOADER_PAPER_VAC_ALL] = bStatusAll;

	//21.02.04 SJC no cylinder
	//Cylinder
	//BOOL bCylinderStatus = FALSE;
	//for (k = 0; k < _eMANUAL_LOADER_CYLINDER_MAX; k++)
	//{
	//	bCylinderStatus = (SharedInfo::DInputValue[_DIN_LD_CYLINDER_UP_L + k] && SharedInfo::DInputValue[_DIN_LD_CYLINDER_UP_R + k]);
	//	if (m_bPrevStatus_Cylinder[k] != bCylinderStatus)
	//	{
	//		if (bCylinderStatus)
	//			m_stcLamp_Cylinder[k].SetBackgroundColor(LED_LAMP_ON);
	//		else
	//			m_stcLamp_Cylinder[k].SetBackgroundColor(LED_LAMP_OFF);

	//		m_bPrevStatus_Cylinder[k] = bCylinderStatus;
	//	}
	//}

	//Ionizer
	if (m_bPrevIonizerOn != Devs::m_LoaderMotion.Is_Ionizer_On())
	{
		if (Devs::m_LoaderMotion.Is_Ionizer_On())
			m_stcLamp_IonizerOn.SetBackgroundColor(LED_LAMP_ON);
		else
			m_stcLamp_IonizerOn.SetBackgroundColor(LED_LAMP_OFF);
	}
	m_bPrevIonizerOn = Devs::m_LoaderMotion.Is_Ionizer_On();

	if (m_bPrevIonizerOff != Devs::m_LoaderMotion.Is_Ionizer_Off())
	{
		if (Devs::m_LoaderMotion.Is_Ionizer_Off())
			m_stcLamp_IonizerOff.SetBackgroundColor(LED_LAMP_ON);
		else
			m_stcLamp_IonizerOff.SetBackgroundColor(LED_LAMP_OFF);
	}
	m_bPrevIonizerOff = Devs::m_LoaderMotion.Is_Ionizer_Off();
	
	
#pragma endregion

	CDialogEx::OnTimer(nIDEvent);
}
//--------------------------------------------------------
BOOL	CManual_Sub_Loader_Manual::Is_Comp_Usable()
{
	int i = 0;
	for (i = 0; i < _eMANUAL_LOADER_INDEX_MAX; i++)
	{
		if (m_stLamp_Work[i].GetSafeHwnd() == NULL)
			return FALSE;
	}

	return TRUE;
}
void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualLoaderZWaitPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;
	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderZ_Wait_Pos;
	int nIndex = _eMANUAL_LOADER_INDEX_LOADER_Z_WAIT_POS;

	Str.Format(_T("Loader Z Move ? (Wait_Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_LoaderMotion.LoaderZ_WaitPos();

	if (bRtn == TRUE)
	{
		m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;

		m_bPrevStatus_InPos[nIndex] = 0;
		m_bMotionDone[nIndex] = 0;
	}
}


void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLaoderManualLoaderZStickLoadInBox1stPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;
	double dPos = 0.0;

#pragma region //Interlock	
	if (Devs::m_LoaderMotion.Is_LoaderY_Stick_LoadPos() == FALSE)
	{
		AfxMessageBox(_T("Check Load Y Stick LoadPos !!!"));
		return;
	}

	//if (Devs::m_LoaderMotion.Is_PaperBox_Fwd() == FALSE)
	//{
	//	AfxMessageBox(_T("Check Loader Paper Box Stage Fwd Sensor !!!"));
	//	return;
	//}

	//IO
	//21.02.04 sjc no jig lock sensor
	//if (SharedInfo::DInputValue[BOX_STAGE_JIG_LOCK_SENSOR] == FALSE)
	//{
	//	Total_Msg(_T("Check Box Stage Jig Lock Sensor !!!"));
	//	return;
	//}
	//if (SharedInfo::DInputValue[PAPER_STAGE_JIG_LOCK_SENSOR] == FALSE)
	//{
	//	Total_Msg(_T("Check Paper Jig Lock Sensor !!!"));
	//	return;
	//}
#pragma endregion

	dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderZ_StickLoadInBox1st_Pos;
	int nIndex = _eMANUAL_LOADER_INDEX_LOADER_Z_STICK_LOAD_IN_BOX_1ST_POS;

	Str.Format(_T("Loader Z Move ? (Stick Load In Box 1st Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_LoaderMotion.LoaderZ_StickLoadInBox1stPos();

	if (bRtn == TRUE)
	{
		m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;

		m_bPrevStatus_InPos[nIndex] = 0;
		m_bMotionDone[nIndex] = 0;
	}
}


void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLaoderManualLoaderZStickLoadInBox2ndPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;
	double dPos = 0.0;

#pragma region //Interlock
	if(Devs::m_LoaderMotion.Is_LoaderY_Stick_LoadPos() == FALSE)
	{
		AfxMessageBox(_T("Check Load Y Stick LoadPos !!!"));

		return;
	}

	if (Devs::m_LoaderMotion.Is_PaperBox_Fwd() == FALSE)
	{
		AfxMessageBox(_T("Check Loader Paper Box Stage Fwd Sensor !!!"));
		return;
	}

	//IO
	//21.02.04 sjc no jig lock sensor
	//if (SharedInfo::DInputValue[BOX_STAGE_JIG_LOCK_SENSOR] == FALSE)
	//{
	//	Total_Msg(_T("Check Box Stage Jig Lock Sensor !!!"));
	//	return;
	//}
	//if (SharedInfo::DInputValue[PAPER_STAGE_JIG_LOCK_SENSOR] == FALSE)
	//{
	//	Total_Msg(_T("Check Paper Jig Lock Sensor !!!"));
	//	return;
	//}
#pragma endregion

	dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderZ_Vibration_Pos;
	int nIndex = _eMANUAL_LOADER_INDEX_LOADER_Z_STICK_LOAD_IN_BOX_2ND_POS;

	Str.Format(_T("Loader Z Move ? (Vibration Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_LoaderMotion.LoaderZ_Vibration_Pos();

	if (bRtn == TRUE)
	{
		m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;

		m_bPrevStatus_InPos[nIndex] = 0;
		m_bMotionDone[nIndex] = 0;
	}
}


void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualLoaderZStickUnloadToInspectionStagePos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;
	double dPos = 0.0;

#pragma region //Interlock
	if (Devs::m_LoaderMotion.Is_LoaderY_Stick_UnloadPos() == FALSE)
	{
		AfxMessageBox(_T("Check Load Y Stick UnLoadPos !!!"));
		return;
	}

	//if (Devs::m_LoaderMotion.Is_PaperBox_Fwd() == FALSE)
	//{
	//	AfxMessageBox(_T("Check Loader Paper Box Stage Fwd Sensor !!!"));
	//	return;
	//}

#pragma endregion

	dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderZ_StickUnloadToStage_Pos;
	int nIndex = _eMANUAL_LOADER_INDEX_LOADER_Z_STICK_UNLOAD_TO_STAGE_POS;

	Str.Format(_T("Loader Z Move ? (Stick Unload To Stage Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_LoaderMotion.LoaderZ_StickUnloadToStagePos();

	if (bRtn == TRUE)
	{
		m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;

		m_bPrevStatus_InPos[nIndex] = 0;
		m_bMotionDone[nIndex] = 0;
	}
}


void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualLoaderZStickLoadInStage1stPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;
	double dPos = 0.0;

#pragma region //Interlock
	if (Devs::m_LoaderMotion.Is_LoaderY_Stick_UnloadPos() == FALSE)
	{
		AfxMessageBox(_T("Check Load Y Stick UnLoadPos !!!"));
		return;
	}
	
	//if (Devs::m_LoaderMotion.Is_PaperBox_Fwd() == FALSE)
	//{
	//	AfxMessageBox(_T("Check Loader Paper Box Stage Fwd Sensor !!!"));
	//	return;
	//}

#pragma endregion

	dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderZ_StickLoadInStage1st_Pos;
	int nIndex = _eMANUAL_LOADER_INDEX_LOADER_Z_STICK_LOAD_IN_STAGE_1ST_POS;

	Str.Format(_T("Loader Z Move ? (Stick Load In Stage 1st Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_LoaderMotion.LoaderZ_StickLoadInStage1stPos();

	if (bRtn == TRUE)
	{
		m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;

		m_bPrevStatus_InPos[nIndex] = 0;
		m_bMotionDone[nIndex] = 0;
	}
}


void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualLoaderZStickLoadInStage2ndPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;
	double dPos = 0.0;

#pragma region //Interlock
	//if (Devs::m_LoaderMotion.Is_LoaderY_Inspection_Pos() == FALSE)
	//{
	//	AfxMessageBox(_T("Check Load Y Stick Inspection Pos !!!"));
	//	return;
	//}

	//if (Devs::m_LoaderMotion.Is_PaperBox_Fwd() == FALSE)
	//{
	//	AfxMessageBox(_T("Check Loader Paper Box Stage Fwd Sensor !!!"));
	//	return;
	//}

#pragma endregion

	dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderZ_Inspection_Pos;
	int nIndex = _eMANUAL_LOADER_INDEX_LOADER_Z_STICK_LOAD_IN_STAGE_2ND_POS;

	Str.Format(_T("Loader Z Move ? (Box Align Inspection Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_LoaderMotion.LoaderZ_Inspection_Pos();

	if (bRtn == TRUE)
	{
		m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;
	}
}


void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualLoaderZStickUnloadInBoxPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;
	double dPos = 0.0;

#pragma region //Interlock
	if (Devs::m_LoaderMotion.Is_LoaderY_Stick_LoadPos() == FALSE)
	{
		AfxMessageBox(_T("Check Load Y Stick LoadPos !!!"));
		return;
	}

	//if (Devs::m_LoaderMotion.Is_PaperBox_Fwd() == FALSE)
	//{
	//	AfxMessageBox(_T("Check Loader Paper Box Stage Fwd Sensor !!!"));
	//	return;
	//}

	//IO
	//21.02.04 sjc no jig lock sensor
	//if (SharedInfo::DInputValue[BOX_STAGE_JIG_LOCK_SENSOR] == FALSE)
	//{
	//	Total_Msg(_T("Check Box Stage Jig Lock Sensor !!!"));
	//	return;
	//}
	//if (SharedInfo::DInputValue[PAPER_STAGE_JIG_LOCK_SENSOR] == FALSE)
	//{
	//	Total_Msg(_T("Check Paper Jig Lock Sensor !!!"));
	//	return;
	//}
#pragma endregion

	dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderZ_StickUnoadToBox_Pos;
	int nIndex = _eMANUAL_LOADER_INDEX_LOADER_Z_STICK_UNLOAD_TO_BOX_POS;

	Str.Format(_T("Loader Z Move ? (Stick Unload In Box Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_LoaderMotion.LoaderZ_StickUnloadToBoxPos();

	if (bRtn == TRUE)
	{
		m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;

		m_bPrevStatus_InPos[nIndex] = 0;
		m_bMotionDone[nIndex] = 0;
	}
}


void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualLoaderXWaitPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;

#pragma region //Interlock
	double dPosTemp = SharedInfo::GetCmdPos(AXIS_LOADER_Z);
	if (dPosTemp < CManualData::m_ManualDataLoader.Info.m_dLoaderZ_Wait_Pos - 0.002)
	{
		AfxMessageBox(_T("Check Load Z WaitPos !!!"));
		return;
	}
#pragma endregion

	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderX_Wait_Pos;
	int nIndex = _eMANUAL_LOADER_INDEX_LOADER_X_WAIT_POS;

	Str.Format(_T("Loader X Move ? (Wait Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_LoaderMotion.LoaderX_WaitPos();

	if (bRtn == TRUE)
	{
		m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;

		m_bPrevStatus_InPos[nIndex] = 0;
		m_bMotionDone[nIndex] = 0;
	}
}

void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualLoaderXAlignPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;

#pragma region //Interlock
	double dPosTemp = SharedInfo::GetCmdPos(AXIS_LOADER_Z);
	if (dPosTemp < CManualData::m_ManualDataLoader.Info.m_dLoaderZ_Wait_Pos - 0.002)
	{
		AfxMessageBox(_T("Check Load Z WaitPos !!!"));
		return;
	}
#pragma endregion

	double dPos = CModelData::m_ModelSubManualPara.Info.dStickLoaderX_AlignPos;
	int nIndex = _eMANUAL_LOADER_INDEX_LOADER_X_ALIGN_POS;

	Str.Format(_T("Loader X Move ? (Align Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_LoaderMotion.LoaderX_AlignPos();

	if (bRtn == TRUE)
	{
		m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;

		m_bPrevStatus_InPos[nIndex] = 0;
		m_bMotionDone[nIndex] = 0;
	}
}

void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualLoaderXPickPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;

#pragma region //Interlock
	double dPosTemp = SharedInfo::GetCmdPos(AXIS_LOADER_Z);
	if (dPosTemp < CManualData::m_ManualDataLoader.Info.m_dLoaderZ_Wait_Pos - 0.002)
	{
		AfxMessageBox(_T("Check Load Z WaitPos !!!"));
		return;
	}
#pragma endregion

	double dPos = CModelData::m_ModelSubManualPara.Info.dStickLoaderX_PickUpPos;
	int nIndex = _eMANUAL_LOADER_INDEX_LOADER_X_PICKUP_POS;

	Str.Format(_T("Loader X Move ? (PickUp Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_LoaderMotion.LoaderX_StickPickUpPos();

	if (bRtn == TRUE)
	{
		m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;

		m_bPrevStatus_InPos[nIndex] = 0;
		m_bMotionDone[nIndex] = 0;
	}
}

#pragma region //Stick Vacuum On
void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualStickVacOn1()
{
	if (IDOK != AfxMessageBox(_T("Loader Stick Vac 1 On ?"), MB_OKCANCEL)) return;

	Devs::m_LoaderMotion.Stick_Vac_On(eVAC_LOADER_STICK_1);
}
void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualStickVacOn2()
{
	if (IDOK != AfxMessageBox(_T("Loader Stick Vac 2 On ?"), MB_OKCANCEL)) return;

	Devs::m_LoaderMotion.Stick_Vac_On(eVAC_LOADER_STICK_2);
}
void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualStickVacOn3()
{
	if (IDOK != AfxMessageBox(_T("Loader Stick Vac 3 On ?"), MB_OKCANCEL)) return;

	Devs::m_LoaderMotion.Stick_Vac_On(eVAC_LOADER_STICK_3);
}
void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualStickVacOn4()
{
	if (IDOK != AfxMessageBox(_T("Loader Stick Vac 4 On ?"), MB_OKCANCEL)) return;

	Devs::m_LoaderMotion.Stick_Vac_On(eVAC_LOADER_STICK_4);
}
void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualStickVacOn5()
{
	if (IDOK != AfxMessageBox(_T("Loader Stick Vac 5 On ?"), MB_OKCANCEL)) return;

	Devs::m_LoaderMotion.Stick_Vac_On(eVAC_LOADER_STICK_5);
}
void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualStickVacActiveOn()
{
	if (IDOK != AfxMessageBox(_T("Loader Stick Vac Active On ?"), MB_OKCANCEL)) return;

	Devs::m_LoaderMotion.Stick_Active_Vac_On();
}
void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualStickVacAllOn()
{
	if (IDOK != AfxMessageBox(_T("Loader Stick Vac All On ?"), MB_OKCANCEL)) return;

	Devs::m_LoaderMotion.Stick_Vac_On(eVAC_LOADER_STICK_ALL);
	//Total_Msg(_T("Loader Stick Vac All On"));
}
#pragma endregion

#pragma region //Stick Vacuum Off
void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualStickVacOff1()
{
	if (IDOK != AfxMessageBox(_T("Loader Stick Vac 1 Off ?"), MB_OKCANCEL)) return;
	
	Devs::m_LoaderMotion.Stick_Vac_Off(eVAC_LOADER_STICK_1);
}
void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualStickVacOff2()
{
	if (IDOK != AfxMessageBox(_T("Loader Stick Vac 2 Off ?"), MB_OKCANCEL)) return;

	Devs::m_LoaderMotion.Stick_Vac_Off(eVAC_LOADER_STICK_2);
}
void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualStickVacOff3()
{
	if (IDOK != AfxMessageBox(_T("Loader Stick Vac 3 Off ?"), MB_OKCANCEL)) return;

	Devs::m_LoaderMotion.Stick_Vac_Off(eVAC_LOADER_STICK_3);
}
void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualStickVacOff4()
{
	if (IDOK != AfxMessageBox(_T("Loader Stick Vac 4 Off ?"), MB_OKCANCEL)) return;

	Devs::m_LoaderMotion.Stick_Vac_Off(eVAC_LOADER_STICK_4);
}
void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualStickVacOff5()
{
	if (IDOK != AfxMessageBox(_T("Loader Stick Vac 5 Off ?"), MB_OKCANCEL)) return;

	Devs::m_LoaderMotion.Stick_Vac_Off(eVAC_LOADER_STICK_5);
}
void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualStickVacActiveOff()
{
	if (IDOK != AfxMessageBox(_T("Loader Stick Vac Active Off ?"), MB_OKCANCEL)) return;

	Devs::m_LoaderMotion.Stick_Active_Vac_Off();
}
void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualStickVacAllOff()
{
	if (IDOK != AfxMessageBox(_T("Loader Stick Vac All Off ?"), MB_OKCANCEL)) return;

	Devs::m_LoaderMotion.Stick_Vac_Off(eVAC_LOADER_STICK_ALL);
	//Total_Msg(_T("Loader Stick Vac All Off"));
}
#pragma endregion

#pragma region //Paper Vacuum On
void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualPaperVacOn1()
{
	if (IDOK != AfxMessageBox(_T("Loader Paper Vac 1 On ?"), MB_OKCANCEL)) return;

	Devs::m_LoaderMotion.Paper_Vac_On(eVAC_LOADER_PAPER_1);
}
void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualPaperVacOn2()
{
	if (IDOK != AfxMessageBox(_T("Loader Paper Vac 2 On ?"), MB_OKCANCEL)) return;

	Devs::m_LoaderMotion.Paper_Vac_On(eVAC_LOADER_PAPER_2);
}
void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualPaperVacOn3()
{
	if (IDOK != AfxMessageBox(_T("Loader Paper Vac 3 On ?"), MB_OKCANCEL)) return;

	Devs::m_LoaderMotion.Paper_Vac_On(eVAC_LOADER_PAPER_3);
}
void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualPaperVacOn4()
{
	if (IDOK != AfxMessageBox(_T("Loader Paper Vac 4 On ?"), MB_OKCANCEL)) return;

	Devs::m_LoaderMotion.Paper_Vac_On(eVAC_LOADER_PAPER_4);
}
void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualPaperVacActiveOn()
{
	if (IDOK != AfxMessageBox(_T("Loader Paper Vac Active On ?"), MB_OKCANCEL)) return;

	Devs::m_LoaderMotion.Paper_Active_Vac_On();
}
void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualPaperVacAllOn()
{
	if (IDOK != AfxMessageBox(_T("Loader Paper Vac All On ?"), MB_OKCANCEL)) return;

	Devs::m_LoaderMotion.Paper_Vac_On(eVAC_LOADER_PAPER_ALL);
}
#pragma endregion

#pragma region //Paper Vacuum Off
void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualPaperVacOff1()
{
	if (IDOK != AfxMessageBox(_T("Loader Paper Vac 1 Off ?"), MB_OKCANCEL)) return;

	Devs::m_LoaderMotion.Paper_Blow_On();
	Sleep(1000);
	Devs::m_LoaderMotion.Paper_Vac_Off(eVAC_LOADER_PAPER_1);
	Sleep(1000);
	Devs::m_LoaderMotion.Paper_Blow_Off();
}
void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualPaperVacOff2()
{
	if (IDOK != AfxMessageBox(_T("Loader Paper Vac 2 Off ?"), MB_OKCANCEL)) return;

	Devs::m_LoaderMotion.Paper_Blow_On();
	Sleep(1000);
	Devs::m_LoaderMotion.Paper_Vac_Off(eVAC_LOADER_PAPER_2);
	Sleep(1000);
	Devs::m_LoaderMotion.Paper_Blow_Off();
}
void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualPaperVacOff3()
{
	if (IDOK != AfxMessageBox(_T("Loader Paper Vac 3 Off ?"), MB_OKCANCEL)) return;

	Devs::m_LoaderMotion.Paper_Blow_On();
	Sleep(1000);
	Devs::m_LoaderMotion.Paper_Vac_Off(eVAC_LOADER_PAPER_3);
	Sleep(1000);	
	Devs::m_LoaderMotion.Paper_Blow_Off();
}
void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualPaperVacOff4()
{
	if (IDOK != AfxMessageBox(_T("Loader Paper Vac 4 Off ?"), MB_OKCANCEL)) return;

	Devs::m_LoaderMotion.Paper_Blow_On();
	Sleep(1000);
	Devs::m_LoaderMotion.Paper_Vac_Off(eVAC_LOADER_PAPER_4);
	Sleep(1000);	
	Devs::m_LoaderMotion.Paper_Blow_Off();
}
void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualPaperVacActiveOff()
{
	if (IDOK != AfxMessageBox(_T("Loader Paper Vac Active Off ?"), MB_OKCANCEL)) return;

	Devs::m_LoaderMotion.Paper_Active_Vac_Off();
}
void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualPaperVacAllOff()
{
	if (IDOK != AfxMessageBox(_T("Loader Paper Vac All Off ?"), MB_OKCANCEL)) return;

	Devs::m_LoaderMotion.Paper_Blow_On();
	Sleep(1000);
	Devs::m_LoaderMotion.Paper_Vac_Off(eVAC_LOADER_PAPER_ALL);
	Sleep(1000);	
	Devs::m_LoaderMotion.Paper_Blow_Off();
}
#pragma endregion

#pragma region //Cylinder
void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualCylinderUp()
{
	if (IDOK != AfxMessageBox(_T("Loader Cylinder Up ?"), MB_OKCANCEL)) return;

	Devs::m_LoaderMotion.Cylinder_Up();
}


void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualCylinderDown()
{
	if (IDOK != AfxMessageBox(_T("Loader Cylinder Down ?"), MB_OKCANCEL)) return;

	Devs::m_LoaderMotion.Cylinder_Down();
}
#pragma endregion


void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderIonizerOn()
{
	if (IDOK != AfxMessageBox(_T("Ionizer On ?"), MB_OKCANCEL)) return;

	Devs::m_LoaderMotion.Ionizer_On();
}


void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderIonizerOff()
{
	if (IDOK != AfxMessageBox(_T("Ionizer Off ?"), MB_OKCANCEL)) return;

	Devs::m_LoaderMotion.Ionizer_Off();
}

//21.02.10 sjc
void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualLoaderYWaitPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;
	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderY_Wait_Pos;
	int nIndex = _eMANUAL_LOADER_INDEX_LOADER_Y_WAIT_POS;

	dPos = SharedInfo::GetCmdPos(AXIS_LOADER_Z);	
	if (dPos < CManualData::m_ManualDataLoader.Info.m_dLoaderZ_Wait_Pos - 0.002)
	{
		AfxMessageBox(_T("Check Loader Z WaitPos !!!"));
		return;
	}

	dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderY_Wait_Pos;
	Str.Format(_T("Loader Y Move ? (Wait_Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_LoaderMotion.LoaderY_WaitPos();

	if (bRtn == TRUE)
	{
		m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;

		m_bPrevStatus_InPos[nIndex] = 0;
		m_bMotionDone[nIndex] = 0;
	}
}

void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLaoderManualLoaderYStickLoadPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;
	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderY_Stick_Load_Pos;
	int nIndex = _eMANUAL_LOADER_INDEX_LOADER_Y_STICK_LOAD_POS;

	dPos = SharedInfo::GetCmdPos(AXIS_LOADER_Z);
	if (dPos < CManualData::m_ManualDataLoader.Info.m_dLoaderZ_Wait_Pos)
	{
		AfxMessageBox(_T("Check Load Z WaitPos !!!"));
		return;
	}

	dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderY_Stick_Load_Pos;
	Str.Format(_T("Loader Y Move ? (Stick_Load_Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_LoaderMotion.LoaderY_Stick_LoadPos();

	if (bRtn == TRUE)
	{
		m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;

		m_bPrevStatus_InPos[nIndex] = 0;
		m_bMotionDone[nIndex] = 0;
	}
}

void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLaoderManualLoaderYStickUnloadPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;
	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderY_Stick_Unload_Pos;
	int nIndex = _eMANUAL_LOADER_INDEX_LOADER_Y_STICK_UNLOAD_POS;

	dPos = SharedInfo::GetCmdPos(AXIS_LOADER_Z);
	if (dPos < CManualData::m_ManualDataLoader.Info.m_dLoaderZ_Wait_Pos)
	{
		AfxMessageBox(_T("Check Load Z WaitPos !!!"));
		return;
	}

	dPos = SharedInfo::GetCmdPos(AXIS_VIRTUAL_GANTRY_Y);
	if (dPos < (CManualData::m_ManualDataGantry.Info.m_dGantry_Y_Loading_Safe_Pos - 0.02))
	{
		AfxMessageBox(_T("Check Gantry Y Loading SafePos !!!"));
		return;
	}
	
	dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderY_Stick_Unload_Pos;
	Str.Format(_T("Loader Y Move ? (Stick_Unload_Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_LoaderMotion.LoaderY_Stick_UnloadPos();

	if (bRtn == TRUE)
	{
		m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;

		m_bPrevStatus_InPos[nIndex] = 0;
		m_bMotionDone[nIndex] = 0;
	}
}

void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLaoderManualLoaderYInspectionPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;
	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderY_Inspection_Pos;
	int nIndex = _eMANUAL_LOADER_INDEX_LOADER_Y_INSPECTION_POS;

	dPos = SharedInfo::GetCmdPos(AXIS_LOADER_Z);
	if (dPos < CManualData::m_ManualDataLoader.Info.m_dLoaderZ_Wait_Pos)
	{
		AfxMessageBox(_T("Check Load Z WaitPos !!!"));
		return;
	}

	dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderY_Inspection_Pos;
	Str.Format(_T("Loader Y Move ? (Box Align Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_LoaderMotion.LoaderY_Inspection_Pos();

	if (bRtn == TRUE)
	{
		m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;

		m_bPrevStatus_InPos[nIndex] = 0;
		m_bMotionDone[nIndex] = 0;
	}
}
//
//
//void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualLoaderZlWaitPos()
//{
//	CString Str = _T("");
//	BOOL bRtn = FALSE;
//	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderZL_Wait_Pos;
//	int nIndex = _eMANUAL_LOADER_INDEX_LOADER_ZL_WAIT_POS;
//
//	Str.Format(_T("Loader ZL Move ? (Wait_Pos : %.5f)"), dPos);
//	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;
//
//	bRtn = Devs::m_LoaderMotion.LoaderZL_WaitPos();
//
//	if (bRtn == TRUE)
//	{
//		m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
//		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
//		m_nWork_State[nIndex] = _eSTATE_START;
//
//		m_bPrevStatus_InPos[nIndex] = 0;
//		m_bMotionDone[nIndex] = 0;
//	}
//}
//
//
//void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualLoaderZlDownPos()
//{
//	CString Str = _T("");
//	BOOL bRtn = FALSE;
//	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderZL_Down_Pos;
//	int nIndex = _eMANUAL_LOADER_INDEX_LOADER_ZL_DOWN_POS;
//
//	if (Devs::m_LoaderMotion.Is_PaperBox_Fwd() == FALSE)
//	{
//		AfxMessageBox(_T("Check Loader Paper Box Stage Fwd Sensor !!!"));
//		return;
//	}
//
//	Str.Format(_T("Loader ZR Move ? (Down_Pos : %.5f)"), dPos);
//	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;
//
//	bRtn = Devs::m_LoaderMotion.LoaderZL_DownPos();
//
//	if (bRtn == TRUE)
//	{
//		m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
//		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
//		m_nWork_State[nIndex] = _eSTATE_START;
//
//		m_bPrevStatus_InPos[nIndex] = 0;
//		m_bMotionDone[nIndex] = 0;
//	}
//}
//
//
//void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualLoaderZrWaitPos()
//{
//	CString Str = _T("");
//	BOOL bRtn = FALSE;
//	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderZR_Wait_Pos;
//	int nIndex = _eMANUAL_LOADER_INDEX_LOADER_ZR_WAIT_POS;
//
//	Str.Format(_T("Loader ZR Move ? (Wait_Pos : %.5f)"), dPos);
//	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;
//
//	bRtn = Devs::m_LoaderMotion.LoaderZR_WaitPos();
//
//	if (bRtn == TRUE)
//	{
//		m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
//		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
//		m_nWork_State[nIndex] = _eSTATE_START;
//
//		m_bPrevStatus_InPos[nIndex] = 0;
//		m_bMotionDone[nIndex] = 0;
//	}
//}
//
//
//void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualLoaderZrDownPos()
//{
//	CString Str = _T("");
//	BOOL bRtn = FALSE;
//	double dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderZR_Down_Pos;
//	int nIndex = _eMANUAL_LOADER_INDEX_LOADER_ZR_DOWN_POS;
//
//	if (Devs::m_LoaderMotion.Is_PaperBox_Fwd() == FALSE)
//	{
//		AfxMessageBox(_T("Check Loader Paper Box Stage Fwd Sensor !!!"));
//		return;
//	}
//
//	dPos = CManualData::m_ManualDataLoader.Info.m_dLoaderZR_Down_Pos;
//	Str.Format(_T("Loader ZR Move ? (Down_Pos : %.5f)"), dPos);
//	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;
//
//	bRtn = Devs::m_LoaderMotion.LoaderZR_DownPos();
//
//	if (bRtn == TRUE)
//	{
//		m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
//		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
//		m_nWork_State[nIndex] = _eSTATE_START;
//
//		m_bPrevStatus_InPos[nIndex] = 0;
//		m_bMotionDone[nIndex] = 0;
//	}
//}


void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualLoaderBarcodeRead()
{
	// TODO: Add your control notification handler code here

	CString szMsg = _T("");	
	GetDlgItem(IDC_EDIT_MANUAL_SUB_LOADER_MANUAL_LOADER_BARCODE_VALUE)->SetWindowText(szMsg);

	Devs::m_SocketLoaderBarCode.ReadCode();

	Sleep(100);
	szMsg = Devs::m_SocketLoaderBarCode.GetLastCode();
	GetDlgItem(IDC_EDIT_MANUAL_SUB_LOADER_MANUAL_LOADER_BARCODE_VALUE)->SetWindowText(szMsg);
}


void CManual_Sub_Loader_Manual::OnBnClickedButtonManualSubLoaderManualLoaderBarcodeView()
{
	// TODO: Add your control notification handler code here

	//CString szMsg;
	//szMsg = Devs::m_SocketLoaderBarCode.GetLastCode();
	//GetDlgItem(IDC_EDIT_MANUAL_SUB_LOADER_MANUAL_LOADER_BARCODE_VALUE)->SetWindowText(szMsg);	

	CString szMsg = _T("");
	GetDlgItem(IDC_EDIT_MANUAL_SUB_LOADER_MANUAL_LOADER_BARCODE_VALUE)->SetWindowText(szMsg);
}
