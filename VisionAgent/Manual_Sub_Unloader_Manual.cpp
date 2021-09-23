// Manual_Sub_Unloader_Manual.cpp: 구현 파일
// Manual_Sub_Unloader_Manual.cpp: 구현 파일
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "Manual_Sub_Unloader_Manual.h"
#include "afxdialogex.h"


// CManual_Sub_Unloader_Manual 대화 상자

IMPLEMENT_DYNAMIC(CManual_Sub_Unloader_Manual, CDialogEx)

CManual_Sub_Unloader_Manual::CManual_Sub_Unloader_Manual(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_MANUAL_SUB_UNLOADER_MANUAL, pParent)
{
	Create(IDD_DLG_MANUAL_SUB_UNLOADER_MANUAL, pParent);
}

CManual_Sub_Unloader_Manual::~CManual_Sub_Unloader_Manual()
{
}

void CManual_Sub_Unloader_Manual::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CManual_Sub_Unloader_Manual, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_VAC_ON_1, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualVacOn1)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_VAC_ON_2, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualVacOn2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_VAC_ON_3, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualVacOn3)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_VAC_ON_4, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualVacOn4)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_VAC_ON_5, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualVacOn5)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_VAC_ACTIVE_ON, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualVacActiveOn)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_VAC_ALL_ON, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualVacAllOn)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_VAC_OFF_1, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualVacOff1)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_VAC_OFF_2, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualVacOff2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_VAC_OFF_3, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualVacOff3)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_VAC_OFF_4, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualVacOff4)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_VAC_OFF_5, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualVacOff5)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_VAC_ACTIVE_OFF, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualVacActiveOff)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_VAC_ALL_OFF, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualVacAllOff)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_Y_WAIT_POS, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderYWaitPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_Y_LOAD_IN_STAGE_POS, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderYLoadInStagePos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_Y_UNLOAD_TO_CST_POS, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderYUnloadToCstPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_X_WAIT_POS, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderXWaitPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_Z_WAIT_POS, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderZWaitPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_Z_LOAD_IN_STAGE_POS, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderZLoadInStagePos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_Z_UNLOAD_TO_CST_POS, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderZUnloadToCstPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_Z_LOAD_IN_CST_POS, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderZLoadInCstPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_Z_UNLOAD_TO_STAGE_POS, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderZUnloadToStagePos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_Y_LOAD_IN_CST_POS, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderYLoadInCstPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_Y_UNLOAD_TO_STAGE_POS, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderYUnloadToStagePos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_Z_LOAD_PAPER_POS, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderZLoadPaperPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_Z_UNLOAD_PAPER_POS, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderZUnloadPaperPos)
	//ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_SUB_Z_LOAD_PAPER_POS, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderSubZLoadPaperPos)
	//ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_SUB_Z_UNLOAD_PAPER_POS, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderSubZUnloadPaperPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_Y_LOAD_PAPER_POS, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderYLoadPaperPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_Y_LOAD_PAPER_WAITING_POS, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderYLoadPaperWaitingPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_Y_UNLOAD_PAPER_POS, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderYUnloadPaperPos)
	//ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_SUB_Z_WAIT_POS, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderSubZWaitPos)
	//ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_SUB_Z_LOAD_IN_STAGE_POS, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderSubZLoadInStagePos)
	//ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_SUB_Z_UNLOAD_TO_CST_POS, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderSubZUnloadToCstPos)
	//ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_SUB_Z_LOAD_IN_CST_POS, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderSubZLoadInCstPos)
	//ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_SUB_Z_UNLOAD_TO_STAGE_POS, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderSubZUnloadToStagePos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_PAPER_VAC_ON_1, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualPaperVacOn1)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_PAPER_VAC_ON_2, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualPaperVacOn2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_PAPER_VAC_ON_3_4, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualPaperVacOn3_4)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_PAPER_VAC_ON_5, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualPaperVacOn5)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_PAPER_ACTIVE_VAC_ON, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualPaperActiveVacOn)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_PAPER_ALL_VAC_ON, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualPaperAllVacOn)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_PAPER_VAC_OFF_1, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualPaperVacOff1)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_PAPER_VAC_OFF_2, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualPaperVacOff2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_PAPER_VAC_OFF_3_4, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualPaperVacOff3_4)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_PAPER_VAC_OFF_5, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualPaperVacOff5)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_PAPER_ACTIVE_VAC_OFF, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualPaperActiveVacOff)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_PAPER_ALL_VAC_OFF, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualPaperAllVacOff)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_ZL_WAIT_POS, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderZlWaitPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_ZL_DOWN_POS, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderZlDownPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_IONIZER_ON, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubLoaderIonizerOn)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_LOADER_IONIZER_OFF, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubLoaderIonizerOff)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_Y_CASSETTE_SAFETY_POS, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderYCassetteSafetyPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_SUB_ZL_LOAD_PAPER_POS, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderSubZlLoadPaperPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_SUB_ZL_UNLOAD_PAPER_POS, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderSubZlUnloadPaperPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_PAPER_UNLOADER_XL_WAIT_POS, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualPaperUnloaderXlWaitPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_PAPER_VAC_ON_6, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualPaperVacOn6)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_PAPER_VAC_OFF_6, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualPaperVacOff6)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_PAPER_UNLOADER_XL_PICK_UP_POS, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualPaperUnloaderXlPickUpPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_X_PICKUP_POS, &CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderXPickupPos)
END_MESSAGE_MAP()


// CManual_Sub_Unloader_Manual 메시지 처리기

BOOL CManual_Sub_Unloader_Manual::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitCtrl();

	return TRUE;
}

void	CManual_Sub_Unloader_Manual::InitCtrl()
{
	int k = 0;

	m_stLamp_Work[_eMANUAL_UNLOADER_INDEX_UNLOADER_Z_WAIT_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_Z_WAIT_POS, this);
	m_stLamp_Work[_eMANUAL_UNLOADER_INDEX_UNLOADER_Z_LOAD_IN_STAGE_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_Z_LOAD_IN_STAGE_POS, this);
	m_stLamp_Work[_eMANUAL_UNLOADER_INDEX_UNLOADER_Z_UNLOAD_TO_CST_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_Z_UNLOAD_TO_CST_POS, this);
	m_stLamp_Work[_eMANUAL_UNLOADER_INDEX_UNLOADER_Z_LOAD_IN_CST_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_Z_LOAD_IN_CST_POS, this);
	m_stLamp_Work[_eMANUAL_UNLOADER_INDEX_UNLOADER_Z_UNLOAD_TO_STAGE_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_Z_UNLOAD_TO_STAGE_POS, this);
	m_stLamp_Work[_eMANUAL_UNLOADER_INDEX_UNLOADER_Z_LOAD_PAPER_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_Z_LOAD_PAPER_POS, this);
	m_stLamp_Work[_eMANUAL_UNLOADER_INDEX_UNLOADER_Z_UNLOAD_PAPER_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_Z_UNLOAD_PAPER_POS, this);
	m_stLamp_Work[_eMANUAL_UNLOADER_INDEX_UNLOADER_Z_VIBRATION_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_Z_VIBRATION_POS, this);

	m_stLamp_Work[_eMANUAL_UNLOADER_INDEX_UNLOADER_ZL_WAIT_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_ZL_WAIT_POS, this);
	m_stLamp_Work[_eMANUAL_UNLOADER_INDEX_UNLOADER_ZL_DOWN_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_ZL_DOWN_POS, this);

	m_stLamp_Work[_eMANUAL_UNLOADER_INDEX_UNLOADER_ZL_PAPER_LOAD_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_SUB_ZL_LOAD_PAPER_POS, this);
	m_stLamp_Work[_eMANUAL_UNLOADER_INDEX_UNLOADER_ZL_PAPER_UNLOAD_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_SUB_ZL_UNLOAD_PAPER_POS, this);
	
	m_stLamp_Work[_eMANUAL_UNLOADER_INDEX_GANTRY_Y_STICK_UNLOAD_TO_CST_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_Y_UNLOAD_TO_CST_POS, this);
	m_stLamp_Work[_eMANUAL_UNLOADER_INDEX_GANTRY_Y_STICK_LOAD_IN_STAGE_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_Y_LOAD_IN_STAGE_POS, this);

	//PaperUnloaderY
	m_stLamp_Work[_eMANUAL_UNLOADER_INDEX_PAPER_UNLOADER_Y_WAIT_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_Y_WAIT_POS, this);	
	m_stLamp_Work[_eMANUAL_UNLOADER_INDEX_UNLOADER_Y_LOAD_IN_CST_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_Y_LOAD_IN_CST_POS, this);
	m_stLamp_Work[_eMANUAL_UNLOADER_INDEX_UNLOADER_Y_UNLOAD_TO_STAGE_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_Y_UNLOAD_TO_STAGE_POS, this);
	m_stLamp_Work[_eMANUAL_UNLOADER_INDEX_PAPER_UNLOADER_Y_LOAD_PAPER_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_Y_LOAD_PAPER_POS, this);
	m_stLamp_Work[_eMANUAL_UNLOADER_INDEX_PAPER_UNLOADER_Y_LOAD_PAPER_WAITING_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_Y_LOAD_PAPER_WAITING_POS, this);
	m_stLamp_Work[_eMANUAL_UNLOADER_INDEX_PAPER_UNLOADER_Y_UNLOAD_PAPER_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_Y_UNLOAD_PAPER_POS, this);
	m_stLamp_Work[_eMANUAL_UNLOADER_INDEX_PAPER_UNLOADER_Y_CASSETTE_SAFETY_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_Y_CASSETTE_SAFETY_POS, this);

	//PaperUnloaderX
	m_stLamp_Work[_eMANUAL_UNLOADER_INDEX_PAPER_UNLOADER_X_ALL_WAIT_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_UNLOADER_MANUAL_PAPER_UNLOADER_XL_WAIT_POS, this);
	m_stLamp_Work[_eMANUAL_UNLOADER_INDEX_PAPER_UNLOADER_X_ALL_PICKUP_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_UNLOADER_MANUAL_PAPER_UNLOADER_XL_PICK_UP_POS, this);

	//MaskUnloader X
	m_stLamp_Work[_eMANUAL_UNLOADER_INDEX_UNLOADER_X_WAIT_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_X_WAIT_POS, this);
	m_stLamp_Work[_eMANUAL_UNLOADER_INDEX_UNLOADER_X_PICKUP_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_UNLOADER_MANUAL_UNLOADER_X_PICKUP_POS, this);

	m_stLamp_Work[_eMANUAL_UNLOADER_INDEX_IONIZER_ON].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_LOADER_IONIZER_ON, this);
	m_stLamp_Work[_eMANUAL_UNLOADER_INDEX_IONIZER_OFF].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_LOADER_IONIZER_OFF, this);

	for (k = 0; k < _eMANUAL_UNLOADER_INDEX_MAX; k++)
	{
		m_stLamp_Work[k].SetParaChangeColor(BK_GND);
		m_stLamp_Work[k].SetParaOriginColor(STATEBAR_NAME_BK_RGB);
		m_stLamp_Work[k].SetBackgroundColor(STATEBAR_NAME_BK_RGB);
		m_stLamp_Work[k].SetTextColor(LED_LAMP_OFF);
		m_stLamp_Work[k].SetBackgroundColor(LED_LAMP_OFF);
	}

#pragma region //IO
	//Stick Vacuum
	m_stcLamp_StickVac[_eMANUAL_UNLOADER_STICK_VAC_1].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_UNLOADER_MANUAL_VAC_ON_1, this);
	m_stcLamp_StickVac[_eMANUAL_UNLOADER_STICK_VAC_2].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_UNLOADER_MANUAL_VAC_ON_2, this);
	m_stcLamp_StickVac[_eMANUAL_UNLOADER_STICK_VAC_3].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_UNLOADER_MANUAL_VAC_ON_3, this);
	m_stcLamp_StickVac[_eMANUAL_UNLOADER_STICK_VAC_4].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_UNLOADER_MANUAL_VAC_ON_4, this);
	m_stcLamp_StickVac[_eMANUAL_UNLOADER_STICK_VAC_5].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_UNLOADER_MANUAL_VAC_ON_5, this);
	m_stcLamp_StickVac[_eMANUAL_UNLOADER_STICK_VAC_ATCIVE].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_UNLOADER_MANUAL_ACTIVE_VAC_ON, this);
	m_stcLamp_StickVac[_eMANUAL_UNLOADER_STICK_VAC_ALL].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_UNLOADER_MANUAL_ALL_VAC_ON, this);
	for (k = 0; k < _eMANUAL_UNLOADER_STICK_VAC_MAX; k++)
	{
		m_stcLamp_StickVac[k].SetParaChangeColor(BK_GND);
		m_stcLamp_StickVac[k].SetParaOriginColor(STATEBAR_NAME_BK_RGB);
		m_stcLamp_StickVac[k].SetBackgroundColor(STATEBAR_NAME_BK_RGB);
		m_stcLamp_StickVac[k].SetTextColor(LED_LAMP_OFF);
		m_stcLamp_StickVac[k].SetBackgroundColor(LED_LAMP_OFF);
	}

	m_stcLamp__PaperVac[_eMANUAL_UNLOADER_PAPER_VAC_1].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_UNLOADER_MANUAL_PAPER_VAC_ON_1, this);
	m_stcLamp__PaperVac[_eMANUAL_UNLOADER_PAPER_VAC_2].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_UNLOADER_MANUAL_PAPER_VAC_ON_2, this);
	m_stcLamp__PaperVac[_eMANUAL_UNLOADER_PAPER_VAC_3_4].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_UNLOADER_MANUAL_PAPER_VAC_ON_3_4, this);
	m_stcLamp__PaperVac[_eMANUAL_UNLOADER_PAPER_VAC_5].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_UNLOADER_MANUAL_PAPER_VAC_ON_5, this);
	m_stcLamp__PaperVac[_eMANUAL_UNLOADER_PAPER_VAC_6].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_UNLOADER_MANUAL_PAPER_VAC_ON_6, this);
	m_stcLamp__PaperVac[_eMANUAL_UNLOADER_PAPER_VAC_ATCIVE].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_UNLOADER_MANUAL_PAPER_ACTIVE_VAC_ON, this);
	m_stcLamp__PaperVac[_eMANUAL_UNLOADER_PAPER_VAC_ALL].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_UNLOADER_MANUAL_PAPER_ALL_VAC_ON, this);
	for (k = 0; k < _eMANUAL_UNLOADER_PAPER_VAC_MAX; k++)
	{
		m_stcLamp_StickVac[k].SetParaChangeColor(BK_GND);
		m_stcLamp_StickVac[k].SetParaOriginColor(STATEBAR_NAME_BK_RGB);
		m_stcLamp_StickVac[k].SetBackgroundColor(STATEBAR_NAME_BK_RGB);
		m_stcLamp_StickVac[k].SetTextColor(LED_LAMP_OFF);
		m_stcLamp_StickVac[k].SetBackgroundColor(LED_LAMP_OFF);
	}

}

void	CManual_Sub_Unloader_Manual::InitPara()
{
	int k = 0;
	for (k = 0; k < _eMANUAL_UNLOADER_INDEX_MAX; k++)
	{
		m_nWork_State[k] = _eSTATE_NONE;
		m_stLamp_Work[k].SetBackgroundColor(LED_LAMP_OFF);

		m_bMotionDone[k] = FALSE;
		m_bPrevStatus_InPos[k] = FALSE;
	}

#pragma region //IO
	for (k = 0; k < _eMANUAL_UNLOADER_STICK_VAC_MAX; k++)
	{
		m_bPrevStatus_StickVac[k] = FALSE;
	}
#pragma endregion
}

void CManual_Sub_Unloader_Manual::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	for (int k = 0; k < _eMANUAL_UNLOADER_INDEX_MAX; k++)
	{
		m_nWork_State[k] = _eSTATE_NONE;
		m_stLamp_Work[k].SetBackgroundColor(LED_LAMP_OFF);
	}

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
void CManual_Sub_Unloader_Manual::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (Is_Comp_Usable() == FALSE)	return;
}
//--------------------------------------------------------
void CManual_Sub_Unloader_Manual::OnTimer(UINT_PTR nIDEvent)
{
	double dEnd_Tick, dWait_Tick;
	int k = 0;

	for (k = 0; k < _eMANUAL_UNLOADER_INDEX_MAX; k++)
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
	//MaskUnloader Z
	m_bMotionDone[_eMANUAL_UNLOADER_INDEX_UNLOADER_Z_WAIT_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_UNLOADER_Z, CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Wait_Pos);
	m_bMotionDone[_eMANUAL_UNLOADER_INDEX_UNLOADER_Z_LOAD_IN_STAGE_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_UNLOADER_Z, CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Load_In_Stage_Pos);
	m_bMotionDone[_eMANUAL_UNLOADER_INDEX_UNLOADER_Z_UNLOAD_TO_CST_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_UNLOADER_Z, CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Unload_To_Cst_Pos);
	m_bMotionDone[_eMANUAL_UNLOADER_INDEX_UNLOADER_Z_LOAD_IN_CST_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_UNLOADER_Z, CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Load_In_Cst_Pos);
	m_bMotionDone[_eMANUAL_UNLOADER_INDEX_UNLOADER_Z_UNLOAD_TO_STAGE_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_UNLOADER_Z, CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Unload_To_Stage_Pos);
	m_bMotionDone[_eMANUAL_UNLOADER_INDEX_UNLOADER_Z_LOAD_PAPER_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_UNLOADER_Z, CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Paper_Load_Pos);
	m_bMotionDone[_eMANUAL_UNLOADER_INDEX_UNLOADER_Z_UNLOAD_PAPER_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_UNLOADER_Z, CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Paper_Unload_Pos);
	m_bMotionDone[_eMANUAL_UNLOADER_INDEX_UNLOADER_Z_VIBRATION_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_UNLOADER_Z, CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Vibration_Pos);
	
	//PaperUnloader ZL
	m_bMotionDone[_eMANUAL_UNLOADER_INDEX_UNLOADER_ZL_WAIT_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_UNLOADER_ZL, CManualData::m_ManualDataUnloader.Info.m_dUnloaderZL_Wait_Pos);
	m_bMotionDone[_eMANUAL_UNLOADER_INDEX_UNLOADER_ZL_DOWN_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_UNLOADER_ZL, CManualData::m_ManualDataUnloader.Info.m_dUnloaderZL_Down_Pos);
	
	m_bMotionDone[_eMANUAL_UNLOADER_INDEX_UNLOADER_ZL_PAPER_LOAD_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_UNLOADER_ZL, CManualData::m_ManualDataUnloader.Info.m_dUnloaderZL_Paper_Load_Pos);
	m_bMotionDone[_eMANUAL_UNLOADER_INDEX_UNLOADER_ZL_PAPER_UNLOAD_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_UNLOADER_ZL, CManualData::m_ManualDataUnloader.Info.m_dUnloaderZL_Paper_Unload_Pos);

	m_bMotionDone[_eMANUAL_UNLOADER_INDEX_GANTRY_Y_STICK_UNLOAD_TO_CST_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_VIRTUAL_GANTRY_Y, CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Unload_To_Cst_Pos);
	m_bMotionDone[_eMANUAL_UNLOADER_INDEX_GANTRY_Y_STICK_LOAD_IN_STAGE_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_VIRTUAL_GANTRY_Y, CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Load_In_Stage_Pos);

	//PaperUnloader Y
	m_bMotionDone[_eMANUAL_UNLOADER_INDEX_PAPER_UNLOADER_Y_WAIT_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_UNLOADER_YL, CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Wait_Pos);	
	m_bMotionDone[_eMANUAL_UNLOADER_INDEX_UNLOADER_Y_LOAD_IN_CST_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_UNLOADER_YL, CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Load_In_Cst_Pos);
	m_bMotionDone[_eMANUAL_UNLOADER_INDEX_UNLOADER_Y_UNLOAD_TO_STAGE_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_UNLOADER_YL, CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Unload_To_Stage_Pos);
	m_bMotionDone[_eMANUAL_UNLOADER_INDEX_PAPER_UNLOADER_Y_LOAD_PAPER_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_UNLOADER_YL, CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Paper_Load_Pos);
	m_bMotionDone[_eMANUAL_UNLOADER_INDEX_PAPER_UNLOADER_Y_LOAD_PAPER_WAITING_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_UNLOADER_YL, CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Paper_Load_Waiting_Pos);
	m_bMotionDone[_eMANUAL_UNLOADER_INDEX_PAPER_UNLOADER_Y_UNLOAD_PAPER_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_UNLOADER_YL, CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Paper_Unload_Pos);
	m_bMotionDone[_eMANUAL_UNLOADER_INDEX_PAPER_UNLOADER_Y_CASSETTE_SAFETY_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_UNLOADER_YL, CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Cassette_Safety_Pos);
	
	//PaperUnloader X
	m_bMotionDone[_eMANUAL_UNLOADER_INDEX_PAPER_UNLOADER_X_ALL_WAIT_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_UNLOADER_XL, CManualData::m_ManualDataUnloader.Info.m_dPaperUnloader_XL_Wait_Pos);
	m_bMotionDone[_eMANUAL_UNLOADER_INDEX_PAPER_UNLOADER_X_ALL_PICKUP_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_UNLOADER_XL, CModelData::m_ModelSubManualPara.Info.dPaperUnloaderX_PickUpPos);

	//StickUnloader X
	m_bMotionDone[_eMANUAL_UNLOADER_INDEX_UNLOADER_X_WAIT_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_UNLOADER_X, CManualData::m_ManualDataUnloader.Info.m_dUnloaderX_Wait_Pos);
	m_bMotionDone[_eMANUAL_UNLOADER_INDEX_UNLOADER_X_PICKUP_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_UNLOADER_X, CModelData::m_ModelSubManualPara.Info.dStickUnloaderX_PickUpPos);

	m_bMotionDone[_eMANUAL_UNLOADER_INDEX_IONIZER_ON] = Devs::m_UnloaderMotion.Is_Ionizer_On();
	m_bMotionDone[_eMANUAL_UNLOADER_INDEX_IONIZER_OFF] = Devs::m_UnloaderMotion.Is_Ionizer_Off();

	for (k = 0; k < _eMANUAL_UNLOADER_INDEX_MAX; k++)
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
	for (k = 0; k < 5; k++)
	{
		//bVacStatus[k] = SharedInfo::DInputValue[_DIN_ULD_STICK_VAC_1 + (k * 2)] && SharedInfo::DInputValue[_DIN_ULD_STICK_VAC_2 + (k * 2)];
		//bVacStatus[k] = SharedInfo::DInputValue[_DIN_ULD_STICK_VAC_1 + k];
		bVacStatus[k] = SharedInfo::DInputValue[_DIN_ULD_STICK_VAC_1 - k]; //KJT 20210723 Junying
		if (m_bPrevStatus_StickVac[k] != bVacStatus[k])
		{
			if (bVacStatus[k])
				m_stcLamp_StickVac[k].SetBackgroundColor(LED_LAMP_ON);
			else
				m_stcLamp_StickVac[k].SetBackgroundColor(LED_LAMP_OFF);
		}
		m_bPrevStatus_StickVac[k] = bVacStatus[k];
	}
	//BOOL bStatusAll = bVacStatus[_eMANUAL_UNLOADER_STICK_VAC_1] & bVacStatus[_eMANUAL_UNLOADER_STICK_VAC_2] & bVacStatus[_eMANUAL_UNLOADER_STICK_VAC_3] & bVacStatus[_eMANUAL_UNLOADER_STICK_VAC_4] & bVacStatus[_eMANUAL_UNLOADER_STICK_VAC_5];
	BOOL bStatusAll = bVacStatus[_eMANUAL_UNLOADER_STICK_VAC_1] & bVacStatus[_eMANUAL_UNLOADER_STICK_VAC_2] & bVacStatus[_eMANUAL_UNLOADER_STICK_VAC_3] & bVacStatus[_eMANUAL_UNLOADER_STICK_VAC_4] & bVacStatus[_eMANUAL_UNLOADER_STICK_VAC_5];
	if (m_bPrevStatus_StickVac[_eMANUAL_UNLOADER_STICK_VAC_ALL] != bStatusAll)
	{
		if (bStatusAll)
			m_stcLamp_StickVac[_eMANUAL_UNLOADER_STICK_VAC_ALL].SetBackgroundColor(LED_LAMP_ON);
		else
			m_stcLamp_StickVac[_eMANUAL_UNLOADER_STICK_VAC_ALL].SetBackgroundColor(LED_LAMP_OFF);
	}
	m_bPrevStatus_StickVac[_eMANUAL_UNLOADER_STICK_VAC_ALL] = bStatusAll;


	//Paper Unloader Vac
	BOOL bPaperVacStatus[5] = { FALSE, };
	for (k = 0; k < 5; k++)
	{
		bPaperVacStatus[k] = SharedInfo::DInputValue[_DIN_PAPER_VAC_LEFT_1 + k] & SharedInfo::DInputValue[_DIN_PAPER_VAC_RIGHT_1 + k];
		if (m_bPrevStatus_PaperkVac[k+ _eMANUAL_UNLOADER_PAPER_VAC_1] != bPaperVacStatus[k])
		{
			if (bPaperVacStatus[k])
				m_stcLamp__PaperVac[k + _eMANUAL_UNLOADER_PAPER_VAC_1].SetBackgroundColor(LED_LAMP_ON);
			else
				m_stcLamp__PaperVac[k + _eMANUAL_UNLOADER_PAPER_VAC_1].SetBackgroundColor(LED_LAMP_OFF);
		}
		m_bPrevStatus_PaperkVac[k + _eMANUAL_UNLOADER_PAPER_VAC_1] = bPaperVacStatus[k];
	}
	bStatusAll = bPaperVacStatus[_eMANUAL_UNLOADER_PAPER_VAC_1] & bPaperVacStatus[_eMANUAL_UNLOADER_PAPER_VAC_2] & bPaperVacStatus[_eMANUAL_UNLOADER_PAPER_VAC_3_4] & bPaperVacStatus[_eMANUAL_UNLOADER_PAPER_VAC_5] & bPaperVacStatus[_eMANUAL_UNLOADER_PAPER_VAC_6];
	if (m_bPrevStatus_StickVac[_eMANUAL_UNLOADER_PAPER_VAC_ALL] != bStatusAll)
	{
		if (bStatusAll)
			m_stcLamp__PaperVac[_eMANUAL_UNLOADER_PAPER_VAC_ALL].SetBackgroundColor(LED_LAMP_ON);
		else
			m_stcLamp__PaperVac[_eMANUAL_UNLOADER_PAPER_VAC_ALL].SetBackgroundColor(LED_LAMP_OFF);
	}
	m_bPrevStatus_PaperkVac[_eMANUAL_UNLOADER_PAPER_VAC_ALL] = bStatusAll;
#pragma endregion

	CDialogEx::OnTimer(nIDEvent);
}

BOOL	CManual_Sub_Unloader_Manual::Is_Comp_Usable()
{
	return TRUE;
}


void	CManual_Sub_Unloader_Manual::CheckChangeData()
{
	//UI에 기입한 내용을 SystemData 변수에 입력
}

#pragma region //Stick Vacuum On
void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualVacOn1()
{
	Devs::m_UnloaderMotion.Stick_Vac_On(eVAC_UNLOADER_STICK_1);
}
void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualVacOn2()
{
	Devs::m_UnloaderMotion.Stick_Vac_On(eVAC_UNLOADER_STICK_2);
}
void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualVacOn3()
{
	Devs::m_UnloaderMotion.Stick_Vac_On(eVAC_UNLOADER_STICK_3);
}
void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualVacOn4()
{
	Devs::m_UnloaderMotion.Stick_Vac_On(eVAC_UNLOADER_STICK_4);
}
void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualVacOn5()
{
	Devs::m_UnloaderMotion.Stick_Vac_On(eVAC_UNLOADER_STICK_5);
}
void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualVacActiveOn()
{
	if (IDOK != AfxMessageBox(_T("Unload Stick Vac Active On ?"), MB_OKCANCEL)) return;

	Devs::m_UnloaderMotion.Stick_Active_Vac_On();
}
void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualVacAllOn()
{
	if (IDOK != AfxMessageBox(_T("Unload Stick Vac All On ?"), MB_OKCANCEL)) return;

	Devs::m_UnloaderMotion.Stick_Vac_On(eVAC_UNLOADER_STICK_ALL);
}
#pragma endregion

#pragma region //Stick Vaccum Off
void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualVacOff1()
{
	Devs::m_UnloaderMotion.Stick_Vac_Off(eVAC_UNLOADER_STICK_1);
}
void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualVacOff2()
{
	Devs::m_UnloaderMotion.Stick_Vac_Off(eVAC_UNLOADER_STICK_2);
}
void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualVacOff3()
{
	Devs::m_UnloaderMotion.Stick_Vac_Off(eVAC_UNLOADER_STICK_3);
}
void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualVacOff4()
{
	Devs::m_UnloaderMotion.Stick_Vac_Off(eVAC_UNLOADER_STICK_4);
}
void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualVacOff5()
{
	//Devs::m_UnloaderMotion.Stick_Vac_Off(eVAC_UNLOADER_STICK_5);
}
void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualVacActiveOff()
{
	if (IDOK != AfxMessageBox(_T("Unload Stick Vac Active Off ?"), MB_OKCANCEL)) return;

	Devs::m_UnloaderMotion.Stick_Active_Vac_Off();
}
void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualVacAllOff()
{
	if (IDOK != AfxMessageBox(_T("Unload Stick Vac All Off ?"), MB_OKCANCEL)) return;

	Devs::m_UnloaderMotion.Stick_Vac_Off(eVAC_UNLOADER_STICK_ALL);
}
#pragma endregion

#pragma region //Unloader Y
void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderYWaitPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;

#pragma region //Interlock
	if (Devs::m_UnloaderMotion.Is_PaperUnloaderZ_All_WaitPos() == FALSE)
	{
		Str.Format(_T("PaperUnloaderZ All Pos Check !!!"));
		AfxMessageBox(Str);
		return;
	}
#pragma endregion

	int nIndex = _eMANUAL_UNLOADER_INDEX_PAPER_UNLOADER_Y_WAIT_POS;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Wait_Pos;

	Str.Format(_T("PaperUnloaderY Move ? (Wait_Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_UnloaderMotion.PaperUnloaderY_All_WaitPos();
	if (bRtn == TRUE)
	{
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;
	}
}
void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderYLoadInStagePos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;

#pragma region //Interlock
	if (SharedInfo::GetCmdPos(AXIS_UNLOADER_Z) < CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Wait_Pos - 0.002) //KJT 20210823
	{
		Str.Format(_T("Unloader Z Wait Pos Check !!!"));
		AfxMessageBox(Str);
		return;
	}
#pragma endregion

	int nIndex = _eMANUAL_UNLOADER_INDEX_GANTRY_Y_STICK_LOAD_IN_STAGE_POS;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Load_In_Stage_Pos;

	Str.Format(_T("GantryY Pos Move ? (Stick Load In Stage Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_UnloaderMotion.GantryY_StickLoadInStagePos();
	if (bRtn == TRUE)
	{
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;
	}
}
void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderYUnloadToCstPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;

#pragma region //Interlock
	if (SharedInfo::GetCmdPos(AXIS_UNLOADER_Z) < CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Wait_Pos - 0.002) //KJT 20210823
	{
		Str.Format(_T("Unloader Z Wait Pos Check !!!"));
		AfxMessageBox(Str);
		return;
	}
#pragma endregion

	int nIndex = _eMANUAL_UNLOADER_INDEX_GANTRY_Y_STICK_UNLOAD_TO_CST_POS;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Unload_To_Cst_Pos;

	Str.Format(_T("GantryY Move ? (Stick Unload To Cst Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_UnloaderMotion.GantryY_StickUnloadToCstPos(0);
	if (bRtn == TRUE)
	{
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;
	}
}
void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderYLoadInCstPos()
{
	// TODO: Add your control notification handler code here
}


void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderYUnloadToStagePos()
{
	// TODO: Add your control notification handler code here
}
#pragma endregion

#pragma region //MaskUnloader X
void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderXWaitPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;
	int nIndex = _eMANUAL_UNLOADER_INDEX_UNLOADER_X_WAIT_POS;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderX_Wait_Pos;

	Str.Format(_T("StickUnloader X Move ? (Wait Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_UnloaderMotion.UnloaderX_WaitPos();
	if (bRtn == TRUE)
	{
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;
	}
}
#pragma endregion

#pragma region //MaskUnloader Z
void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderZWaitPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;
	int nIndex = _eMANUAL_UNLOADER_INDEX_UNLOADER_Z_WAIT_POS;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Wait_Pos;

	Str.Format(_T("MaskUnloader Z Move ? (Wait Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_UnloaderMotion.UnloaderZ_WaitPos();
	if (bRtn == TRUE)
	{
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;
	}
}
void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderZLoadInStagePos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;
	int nIndex = _eMANUAL_UNLOADER_INDEX_UNLOADER_Z_LOAD_IN_STAGE_POS;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Load_In_Stage_Pos;

	Str.Format(_T("Unloader Z Move ? (Stick Load In Stage Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_UnloaderMotion.UnloaderZ_LoadInStagePos();
	if (bRtn == TRUE)
	{
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;
	}
}
void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderZUnloadToCstPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;
	int nIndex = _eMANUAL_UNLOADER_INDEX_UNLOADER_Z_UNLOAD_TO_CST_POS;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Unload_To_Cst_Pos;

	Str.Format(_T("Unloader Z Move ? (Unload To Cst Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_UnloaderMotion.UnloaderZ_UnloadToCstPos();
	if (bRtn == TRUE)
	{
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;
	}
}
void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderZLoadInCstPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;
	int nIndex = _eMANUAL_UNLOADER_INDEX_UNLOADER_Z_LOAD_IN_CST_POS;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Load_In_Cst_Pos;

	Str.Format(_T("Unloader Z Move ? (Load In Cst Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_UnloaderMotion.UnloaderZ_LoadInCstPos();
	if (bRtn == TRUE)
	{
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;
	}
}


void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderZUnloadToStagePos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;
	int nIndex = _eMANUAL_UNLOADER_INDEX_UNLOADER_Z_UNLOAD_TO_STAGE_POS;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Unload_To_Stage_Pos;

	Str.Format(_T("Unloader Z Move ? (Unload To Stage Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_UnloaderMotion.UnloaderZ_UnloadToStagePos();
	if (bRtn == TRUE)
	{
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;
	}
}
#pragma endregion


void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderZLoadPaperPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;
	int nIndex = _eMANUAL_UNLOADER_INDEX_UNLOADER_Z_LOAD_PAPER_POS;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Paper_Load_Pos;

	Str.Format(_T("Unloader Z Move ? (Load Paper Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_UnloaderMotion.UnloaderZ_LoadPaperPos();
	if (bRtn == TRUE)
	{
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;
	}
}


void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderZUnloadPaperPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;
	int nIndex = _eMANUAL_UNLOADER_INDEX_UNLOADER_Z_UNLOAD_PAPER_POS;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZ_Paper_Unload_Pos;

	Str.Format(_T("Unloader Z Move ? (Unload Paper Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_UnloaderMotion.UnloaderZ_UnloadPaperPos();
	if (bRtn == TRUE)
	{
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;
	}
}

void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderYLoadPaperPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;
	int nIndex = _eMANUAL_UNLOADER_INDEX_PAPER_UNLOADER_Y_LOAD_PAPER_POS;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Paper_Load_Pos;

	Str.Format(_T("PaperUnloaderY Move ? (Load Paper Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_UnloaderMotion.PaperUnloaderY_All_LoadPaperPos();
	if (bRtn == TRUE)
	{
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;
	}
}

void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderYLoadPaperWaitingPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;
	int nIndex = _eMANUAL_UNLOADER_INDEX_PAPER_UNLOADER_Y_LOAD_PAPER_WAITING_POS;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Paper_Load_Waiting_Pos;

	Str.Format(_T("PaperUnloader Y Move ? (Load Paper Waiting Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_UnloaderMotion.PaperUnloaderY_All_LoadPaperWaitingPos();
	if (bRtn == TRUE)
	{
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;
	}
}


void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderYUnloadPaperPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;
	int nIndex = _eMANUAL_UNLOADER_INDEX_PAPER_UNLOADER_Y_UNLOAD_PAPER_POS;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Paper_Unload_Pos;

	Str.Format(_T("PaperUnloaderY All Move ? (Unload Paper Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_UnloaderMotion.PaperUnloaderY_All_UnloadPaperPos();
	if (bRtn == TRUE)
	{
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;
	}
}


void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderYCassetteSafetyPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;
	int nIndex = _eMANUAL_UNLOADER_INDEX_PAPER_UNLOADER_Y_CASSETTE_SAFETY_POS;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderY_Cassette_Safety_Pos;

	Str.Format(_T("PaperUnloaderY All Move ? (Cassette Safety Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_UnloaderMotion.PaperUnloaderY_All_CassetteSafetyPos();
	if (bRtn == TRUE)
	{
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;
	}
}

void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualPaperVacOn1()
{
	Devs::m_UnloaderMotion.PaperUnloader_Vac_On(eVAC_UNLOADER_PAPER_1);
}


void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualPaperVacOn2()
{
	Devs::m_UnloaderMotion.PaperUnloader_Vac_On(eVAC_UNLOADER_PAPER_2);
}


void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualPaperVacOn3_4()
{
	Devs::m_UnloaderMotion.PaperUnloader_Vac_On(eVAC_UNLOADER_PAPER_3_4);
}


void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualPaperVacOn5()
{
	Devs::m_UnloaderMotion.PaperUnloader_Vac_On(eVAC_UNLOADER_PAPER_5);
}

void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualPaperVacOn6()
{
	Devs::m_UnloaderMotion.PaperUnloader_Vac_On(eVAC_UNLOADER_PAPER_6);
}

void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualPaperActiveVacOn()
{
	if (IDOK != AfxMessageBox(_T("PaperUnloader Vac Active On ?"), MB_OKCANCEL)) return;

	Devs::m_UnloaderMotion.PaperUnloader_Active_Vac_On();
}


void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualPaperAllVacOn()
{
	if (IDOK != AfxMessageBox(_T("Unload Paper Vac All On ?"), MB_OKCANCEL)) return;

	Devs::m_UnloaderMotion.PaperUnloader_Vac_On(eVAC_UNLOADER_PAPER_ALL);
}


void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualPaperVacOff1()
{
	Devs::m_UnloaderMotion.PaperUnloader_Vac_Off(eVAC_UNLOADER_PAPER_1);
}


void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualPaperVacOff2()
{
	Devs::m_UnloaderMotion.PaperUnloader_Vac_Off(eVAC_UNLOADER_PAPER_2);
}


void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualPaperVacOff3_4()
{
	Devs::m_UnloaderMotion.PaperUnloader_Vac_Off(eVAC_UNLOADER_PAPER_3_4);
}


void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualPaperVacOff5()
{
	Devs::m_UnloaderMotion.PaperUnloader_Vac_Off(eVAC_UNLOADER_PAPER_5);
}

void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualPaperVacOff6()
{
	Devs::m_UnloaderMotion.PaperUnloader_Vac_Off(eVAC_UNLOADER_PAPER_6);
}

void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualPaperActiveVacOff()
{
	if (IDOK != AfxMessageBox(_T("PaperUnload Vac Active Off ?"), MB_OKCANCEL)) return;

	Devs::m_UnloaderMotion.PaperUnloader_Active_Vac_Off();
}


void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualPaperAllVacOff()
{
	if (IDOK != AfxMessageBox(_T("Unload Paper Vac All Off ?"), MB_OKCANCEL)) return;

	Devs::m_UnloaderMotion.PaperUnloader_Vac_Off(eVAC_UNLOADER_STICK_ALL);
}




void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderZlWaitPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;
	int nIndex = _eMANUAL_UNLOADER_INDEX_UNLOADER_ZL_WAIT_POS;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZL_Wait_Pos;

	Str.Format(_T("PaperUnloaderZ All Move ? (Wait Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	//Interlock Junying TPCD
	if (SharedInfo::GetCmdPos(AXIS_LOADER_Z) < CManualData::m_ManualDataLoader.Info.m_dLoaderZ_Wait_Pos - 0.002)
	{
		AfxMessageBox(_T("LoaderZ Wait Pos Check !!"));
		return;
	}

	bRtn = Devs::m_UnloaderMotion.PaperUnloaderZ_All_WaitPos();
	if (bRtn == TRUE)
	{
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;
	}
}


void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderZlDownPos()
{
	//CString Str = _T("");
	//BOOL bRtn = FALSE;
	//int nIndex = _eMANUAL_UNLOADER_INDEX_UNLOADER_ZL_DOWN_POS;
	//double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZL_Down_Pos;

	//Str.Format(_T("Unloader ZL Move ? (Down Pos : %.5f)"), dPos);
	//if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	//bRtn = Devs::m_UnloaderMotion.PaperUnloaderZ_All_DownPos();
	//if (bRtn == TRUE)
	//{
	//	m_dMotion_Strt_Tick[nIndex] = GetTickCount();
	//	m_nWork_State[nIndex] = _eSTATE_START;
	//}
}


void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubLoaderIonizerOn()
{
	// TODO: Add your control notification handler code here

	if (IDOK != AfxMessageBox(_T("Ionizer On ?"), MB_OKCANCEL)) return;

	Devs::m_UnloaderMotion.Ionizer_On();
}


void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubLoaderIonizerOff()
{
	// TODO: Add your control notification handler code here

	if (IDOK != AfxMessageBox(_T("Ionizer Off ?"), MB_OKCANCEL)) return;

	Devs::m_UnloaderMotion.Ionizer_Off();
}

void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderSubZlLoadPaperPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;
	int nIndex = _eMANUAL_UNLOADER_INDEX_UNLOADER_ZL_PAPER_LOAD_POS;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZL_Paper_Load_Pos;

	Str.Format(_T("Unloader ZL Move ? (Paper Load Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_UnloaderMotion.UnloaderSubZL_LoadPaperPos();
	if (bRtn == TRUE)
	{
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;
	}
}


void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderSubZlUnloadPaperPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;
	int nIndex = _eMANUAL_UNLOADER_INDEX_UNLOADER_ZL_PAPER_UNLOAD_POS;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dUnloaderZL_Paper_Unload_Pos;

	Str.Format(_T("Unloader ZL Move ? (Paper Unload Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_UnloaderMotion.UnloaderSubZL_UnloadPaperPos();
	if (bRtn == TRUE)
	{
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;
	}
}

//PaperUnloader X
void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualPaperUnloaderXlWaitPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;

#pragma region //Interlock
	if (Devs::m_UnloaderMotion.PaperUnloaderZ_All_WaitPos() == FALSE)
	{
		Str.Format(_T("PaperUnloaderZL Pos Check !!!"));
		AfxMessageBox(Str);
		return;
	}
#pragma endregion

	int nIndex = _eMANUAL_UNLOADER_INDEX_PAPER_UNLOADER_X_ALL_WAIT_POS;
	double dPos = CManualData::m_ManualDataUnloader.Info.m_dPaperUnloader_XL_Wait_Pos;

	Str.Format(_T("PaperUnloaderX_All Move ? (Wait_Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_UnloaderMotion.PaperUnloaderX_All_WaitPos();
	if (bRtn == TRUE)
	{
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;
	}
}


void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualPaperUnloaderXlPickUpPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;

#pragma region //Interlock
	if (Devs::m_UnloaderMotion.PaperUnloaderZ_All_WaitPos() == FALSE)
	{
		Str.Format(_T("PaperUnloaderZL Pos Check !!!"));
		AfxMessageBox(Str);
		return;
	}
#pragma endregion

	int nIndex = _eMANUAL_UNLOADER_INDEX_PAPER_UNLOADER_X_ALL_PICKUP_POS;
	double dPos = CModelData::m_ModelSubManualPara.Info.dPaperUnloaderX_PickUpPos;

	Str.Format(_T("PaperUnloaderX_All Move ? (PickUp_Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_UnloaderMotion.PaperUnloaderX_All_PickUpPos();
	if (bRtn == TRUE)
	{
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;
	}
}


void CManual_Sub_Unloader_Manual::OnBnClickedButtonManualSubUnloaderManualUnloaderXPickupPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;
	int nIndex = _eMANUAL_UNLOADER_INDEX_UNLOADER_X_PICKUP_POS;
	double dPos = CModelData::m_ModelSubManualPara.Info.dStickUnloaderX_PickUpPos;

	Str.Format(_T("MaskUnloader X Move ? (Wait Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_UnloaderMotion.UnloaderX_PickUpPos();
	if (bRtn == TRUE)
	{
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;
	}
}
