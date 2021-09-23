// Manual_Sub_Cassette_Manual.cpp: 구현 파일
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "Manual_Sub_Cassette_Manual.h"
#include "afxdialogex.h"


// CManual_Sub_Cassette_Manual 대화 상자

IMPLEMENT_DYNAMIC(CManual_Sub_Cassette_Manual, CDialogEx)

CManual_Sub_Cassette_Manual::CManual_Sub_Cassette_Manual(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_MANUAL_SUB_CASSETTE_MANUAL, pParent)
{
	Create(IDD_DLG_MANUAL_SUB_CASSETTE_MANUAL, pParent);
}

CManual_Sub_Cassette_Manual::~CManual_Sub_Cassette_Manual()
{
}

void CManual_Sub_Cassette_Manual::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CManual_Sub_Cassette_Manual, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CASSETTE_MANUAL_CASSETTE_Z_WAIT_POS, &CManual_Sub_Cassette_Manual::OnBnClickedButtonManualSubCassetteManualCassetteZWaitPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CASSETTE_MANUAL_CASSETTE_Z_1FLOOR_POS, &CManual_Sub_Cassette_Manual::OnBnClickedButtonManualSubCassetteManualCassetteZ1floorPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CASSETTE_MANUAL_CASSETTE_Z_2FLOOR_POS, &CManual_Sub_Cassette_Manual::OnBnClickedButtonManualSubCassetteManualCassetteZ2floorPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CASSETTE_MANUAL_CASSETTE_Z_3FLOOR_POS, &CManual_Sub_Cassette_Manual::OnBnClickedButtonManualSubCassetteManualCassetteZ3floorPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CASSETTE_MANUAL_CASSETTE_Z_4FLOOR_POS, &CManual_Sub_Cassette_Manual::OnBnClickedButtonManualSubCassetteManualCassetteZ4floorPos)
	//ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CASSETTE_MANUAL_CASSETTE_Z_5FLOOR_POS, &CManual_Sub_Cassette_Manual::OnBnClickedButtonManualSubCassetteManualCassetteZ5floorPos)
	//ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CASSETTE_MANUAL_CASSETTE_Z_6FLOOR_POS, &CManual_Sub_Cassette_Manual::OnBnClickedButtonManualSubCassetteManualCassetteZ6floorPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CASSETTE_MANUAL_CST_PICK_UP_UNIT_FWD, &CManual_Sub_Cassette_Manual::OnBnClickedButtonManualSubCassetteManualCstPickUpUnitFwd)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CASSETTE_MANUAL_CST_PICK_UP_UNIT_BWD, &CManual_Sub_Cassette_Manual::OnBnClickedButtonManualSubCassetteManualCstPickUpUnitBwd)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CASSETTE_MANUAL_CST_PICK_UP_UNIT_CLAMP, &CManual_Sub_Cassette_Manual::OnBnClickedButtonManualSubCassetteManualCstPickUpUnitClamp)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CASSETTE_MANUAL_CST_PICK_UP_UNIT_UNCLAMP, &CManual_Sub_Cassette_Manual::OnBnClickedButtonManualSubCassetteManualCstPickUpUnitUnclamp)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CASSETTE_MANUAL_CST_BARCODE_READ, &CManual_Sub_Cassette_Manual::OnBnClickedButtonManualSubCassetteManualCstBarcodeRead)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CASSETTE_MANUAL_CST_BARCODE_VIEW, &CManual_Sub_Cassette_Manual::OnBnClickedButtonManualSubCassetteManualCstBarcodeView)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CASSETTE_MANUAL_PAPER_BOX_UNIT_FWD, &CManual_Sub_Cassette_Manual::OnBnClickedButtonManualSubCassetteManualPaperBoxUnitFwd)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CASSETTE_MANUAL_PAPER_BOX_UNIT_BWD, &CManual_Sub_Cassette_Manual::OnBnClickedButtonManualSubCassetteManualPaperBoxUnitBwd)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CASSETTE_MANUAL_CASSETTE_RECV_READY_FLOW, &CManual_Sub_Cassette_Manual::OnBnClickedButtonManualSubCassetteManualCassetteRecvReadyFlow)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CASSETTE_MANUAL_CASSETTE_RECV_DONE_FLOW, &CManual_Sub_Cassette_Manual::OnBnClickedButtonManualSubCassetteManualCassetteRecvDoneFlow)
END_MESSAGE_MAP()


// CManual_Sub_Cassette_Manual 메시지 처리기

BOOL CManual_Sub_Cassette_Manual::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitCtrl();

	return TRUE;
}
//--------------------------------------------------------
void CManual_Sub_Cassette_Manual::OnShowWindow(BOOL bShow, UINT nStatus)
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

void CManual_Sub_Cassette_Manual::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (Is_Comp_Usable() == FALSE)	return;
}

void	CManual_Sub_Cassette_Manual::InitCtrl()
{
	CString Str = _T("");
	int k = 0;

	m_stLamp_Work[_eMANUAL_CASSETTE_INDEX_CASSETTE_Z_WAIT_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_CASSETTE_MANUAL_CASSETTE_Z_WAIT_POS, this);
	m_stLamp_Work[_eMANUAL_CASSETTE_INDEX_CASSETTE_Z_1FLOOR_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_CASSETTE_MANUAL_CASSETTE_Z_1FLOOR_POS, this);
	m_stLamp_Work[_eMANUAL_CASSETTE_INDEX_CASSETTE_Z_2FLOOR_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_CASSETTE_MANUAL_CASSETTE_Z_2FLOOR_POS, this);
	m_stLamp_Work[_eMANUAL_CASSETTE_INDEX_CASSETTE_Z_3FLOOR_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_CASSETTE_MANUAL_CASSETTE_Z_3FLOOR_POS, this);
	m_stLamp_Work[_eMANUAL_CASSETTE_INDEX_CASSETTE_Z_4FLOOR_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_CASSETTE_MANUAL_CASSETTE_Z_4FLOOR_POS, this);
	m_stLamp_Work[_eMANUAL_CASSETTE_INDEX_CASSETTE_Z_5FLOOR_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_CASSETTE_MANUAL_CASSETTE_Z_5FLOOR_POS, this);
	m_stLamp_Work[_eMANUAL_CASSETTE_INDEX_CASSETTE_Z_6FLOOR_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_CASSETTE_MANUAL_CASSETTE_Z_6FLOOR_POS, this);

	for (k = 0; k < _eMANUAL_CASSETTE_INDEX_MAX; k++)
	{
		m_stLamp_Work[k].SetParaChangeColor(BK_GND);
		m_stLamp_Work[k].SetParaOriginColor(STATEBAR_NAME_BK_RGB);
		m_stLamp_Work[k].SetBackgroundColor(STATEBAR_NAME_BK_RGB);
		m_stLamp_Work[k].SetTextColor(LED_LAMP_OFF);
		m_stLamp_Work[k].SetBackgroundColor(LED_LAMP_OFF);
	}

#pragma region //IO
	//Paper Box Detect
	m_stcLamp_PaperBoxUnitDI[_eMANUAL_CST_PAPER_BOX_UNIT_FWD].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_CASSETTE_MANUAL_PAPER_BOX_UNIT_FWD, this);
	m_stcLamp_PaperBoxUnitDI[_eMANUAL_CST_PAPER_BOX_UNIT_BWD].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_CASSETTE_MANUAL_PAPER_BOX_UNIT_BWD, this);
	
	for (k = 0; k < _eMANUAL_CST_PAPER_BOX_UNIT_MAX; k++)
	{
		m_stcLamp_PaperBoxUnitDI[k].SetParaChangeColor(BK_GND);
		m_stcLamp_PaperBoxUnitDI[k].SetParaOriginColor(STATEBAR_NAME_BK_RGB);
		m_stcLamp_PaperBoxUnitDI[k].SetBackgroundColor(STATEBAR_NAME_BK_RGB);
		m_stcLamp_PaperBoxUnitDI[k].SetTextColor(LED_LAMP_OFF);
		m_stcLamp_PaperBoxUnitDI[k].SetBackgroundColor(LED_LAMP_OFF);
	}

	//CST Detect
	m_stcLamp_MagazineDetect[_eMANUAL_MAGAZINE_DETECT_L].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_CASSETTE_MANUAL_MAGAZINE_DETECT_L, this);
	m_stcLamp_MagazineDetect[_eMANUAL_MAGAZINE_DETECT_R].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_CASSETTE_MANUAL_MAGAZINE_DETECT_R, this);
	//m_stcLamp_MagazineDetect[_eMANUAL_CST_UNSAFE_POS_DETECT].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_CASSETTE_MANUAL_CASSETTE_UNSAFE_POS_DETECT, this);
	//m_stcLamp_MagazineDetect[_eMANUAL_CST_BWD_DETECT].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_CASSETTE_MANUAL_CASSETTE_BACKWARD_DETECT, this);
	for (k = 0; k < _eMANUAL_MAGAZINE_DETECT_MAX; k++)
	{
		m_stcLamp_MagazineDetect[k].SetParaChangeColor(BK_GND);
		m_stcLamp_MagazineDetect[k].SetParaOriginColor(STATEBAR_NAME_BK_RGB);
		m_stcLamp_MagazineDetect[k].SetBackgroundColor(STATEBAR_NAME_BK_RGB);
		m_stcLamp_MagazineDetect[k].SetTextColor(LED_LAMP_OFF);
		m_stcLamp_MagazineDetect[k].SetBackgroundColor(LED_LAMP_OFF);
	}

	//Cst PickUp Unit
	m_stcLamp_CstPickUpUnitDI[_eMANUAL_CST_PICK_UP_UNIT_FWD].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_CASSETTE_MANUAL_CST_PICK_UP_UNIT_FWD, this);
	m_stcLamp_CstPickUpUnitDI[_eMANUAL_CST_PICK_UP_UNIT_BWD].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_CASSETTE_MANUAL_CST_PICK_UP_UNIT_BWD, this);
	m_stcLamp_CstPickUpUnitDI[_eMANUAL_CST_PICK_UP_UNIT_CLAMP].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_CASSETTE_MANUAL_CST_PICK_UP_UNIT_CLAMP, this);
	m_stcLamp_CstPickUpUnitDI[_eMANUAL_CST_PICK_UP_UNIT_UNCLAMP].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_CASSETTE_MANUAL_CST_PICK_UP_UNIT_UNCLAMP, this);
	for (k = 0; k < _eMANUAL_CST_PICK_UP_UNIT_MAX; k++)
	{
		m_stcLamp_CstPickUpUnitDI[k].SetParaChangeColor(BK_GND);
		m_stcLamp_CstPickUpUnitDI[k].SetParaOriginColor(STATEBAR_NAME_BK_RGB);
		m_stcLamp_CstPickUpUnitDI[k].SetBackgroundColor(STATEBAR_NAME_BK_RGB);
		m_stcLamp_CstPickUpUnitDI[k].SetTextColor(LED_LAMP_OFF);
		m_stcLamp_CstPickUpUnitDI[k].SetBackgroundColor(LED_LAMP_OFF);
	}
#pragma endregion

	m_EditCstBarcode.SubclassDlgItem(IDC_EDIT_MANUAL_SUB_CASSETTE_BARCODE_READ_VALUE, this);

	m_comboCstTargetFloor.SubclassDlgItem(IDC_COMBO_MANUAL_CASSETTE_SUB_CST_TARGET_FLOOR, this);
	m_comboCstTargetFloor.ResetContent();
	for (k = 0; k < eCASSETTE_FLOOR_MAX; k++)
	{
		Str.Format(_T("Floor%d"), k + 1);
		m_comboCstTargetFloor.AddString(Str);
	}
	m_comboCstTargetFloor.SetCurSel(Devs::m_StickUnloadInStageToCstFlow.m_eTargetFloor);

	m_btnCstRecvReady.SubclassDlgItem(IDC_BUTTON_MANUAL_SUB_CASSETTE_MANUAL_CASSETTE_RECV_READY_FLOW, this);
	m_btnCstRecvDone.SubclassDlgItem(IDC_BUTTON_MANUAL_SUB_CASSETTE_MANUAL_CASSETTE_RECV_DONE_FLOW, this);
}

BOOL	CManual_Sub_Cassette_Manual::Is_Comp_Usable()
{
	return TRUE;
}

void	CManual_Sub_Cassette_Manual::InitPara()
{
	int k = 0;

	for (k = 0; k < _eMANUAL_CASSETTE_INDEX_MAX; k++)
	{
		m_nWork_State[k] = _eSTATE_NONE;
		m_stLamp_Work[k].SetBackgroundColor(LED_LAMP_OFF);

		m_bMotionDone[k] = FALSE;
		m_bPrevStatus_InPos[k] = FALSE;
	}

#pragma region //IO
	for (k = 0; k < _eMANUAL_CST_PICK_UP_UNIT_MAX; k++)
	{
		m_bPrevStatus_CstPickUpUnitDI[k] = FALSE;
	}
#pragma endregion
}

void	CManual_Sub_Cassette_Manual::CheckChangeData()
{
	//UI에 기입한 내용을 SystemData 변수에 입력
}

void CManual_Sub_Cassette_Manual::OnTimer(UINT_PTR nIDEvent)
{
	double dEnd_Tick, dWait_Tick;
	int k = 0;

	for (k = 0; k < _eMANUAL_CASSETTE_INDEX_MAX; k++)
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
	m_bMotionDone[_eMANUAL_CASSETTE_INDEX_CASSETTE_Z_WAIT_POS] = Devs::m_CassetteMotion.Is_CassetteZ_WaitPos();
	m_bMotionDone[_eMANUAL_CASSETTE_INDEX_CASSETTE_Z_1FLOOR_POS] = Devs::m_CassetteMotion.Is_CassetteZ_1FloorPos();
	m_bMotionDone[_eMANUAL_CASSETTE_INDEX_CASSETTE_Z_2FLOOR_POS] = Devs::m_CassetteMotion.Is_CassetteZ_2FloorPos();
	m_bMotionDone[_eMANUAL_CASSETTE_INDEX_CASSETTE_Z_3FLOOR_POS] = Devs::m_CassetteMotion.Is_CassetteZ_3FloorPos();
	m_bMotionDone[_eMANUAL_CASSETTE_INDEX_CASSETTE_Z_4FLOOR_POS] = Devs::m_CassetteMotion.Is_CassetteZ_4FloorPos();
	//m_bMotionDone[_eMANUAL_CASSETTE_INDEX_CASSETTE_Z_5FLOOR_POS] = Devs::m_CassetteMotion.Is_CassetteZ_5FloorPos();
	//m_bMotionDone[_eMANUAL_CASSETTE_INDEX_CASSETTE_Z_6FLOOR_POS] = Devs::m_CassetteMotion.Is_CassetteZ_6FloorPos();

	for (k = 0; k < _eMANUAL_CASSETTE_INDEX_MAX; k++)
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
	//Magazine Detect L
	BOOL bMagazineDetectStatus = FALSE;
	//bMagazineDetectStatus = SharedInfo::DInputValue[_DIN_MAGAZINE_SAFETY_POS_DETECT_L];
	//if (m_bPrevStatus_MagazineDetect[_eMANUAL_MAGAZINE_DETECT_L] != bMagazineDetectStatus)
	//{
		if (SharedInfo::DInputValue[_DIN_MAGAZINE_EXIST_DETECT_L])
			m_stcLamp_MagazineDetect[_eMANUAL_MAGAZINE_DETECT_L].SetBackgroundColor(LED_LAMP_ON);
		else
			m_stcLamp_MagazineDetect[_eMANUAL_MAGAZINE_DETECT_L].SetBackgroundColor(LED_LAMP_OFF);
	//}
	//m_bPrevStatus_MagazineDetect[_eMANUAL_MAGAZINE_DETECT_L] = bMagazineDetectStatus;

	////Magazine Detect R
	//bMagazineDetectStatus = SharedInfo::DInputValue[_DIN_MAGAZINE_EXIST_DETECT_1];
	//if (m_bPrevStatus_MagazineDetect[_eMANUAL_MAGAZINE_DETECT_R] != bMagazineDetectStatus)
	//{
		if (SharedInfo::DInputValue[_DIN_MAGAZINE_EXIST_DETECT_R])
			m_stcLamp_MagazineDetect[_eMANUAL_MAGAZINE_DETECT_R].SetBackgroundColor(LED_LAMP_ON);
		else
			m_stcLamp_MagazineDetect[_eMANUAL_MAGAZINE_DETECT_R].SetBackgroundColor(LED_LAMP_OFF);
	//}
	//m_bPrevStatus_MagazineDetect[_eMANUAL_MAGAZINE_DETECT_R] = bMagazineDetectStatus;

	////CST Unsafe Pos Detect
	//bMagazineDetectStatus = FALSE;
	//bMagazineDetectStatus = SharedInfo::DInputValue[_DIN_MAGAZINE_SAFETY_POS_DETECT_2];
	//if (m_bPrevStatus_MagazineDetect[_eMANUAL_CST_UNSAFE_POS_DETECT] != bMagazineDetectStatus)
	//{
	//	if (bMagazineDetectStatus)
	//		m_stcLamp_MagazineDetect[_eMANUAL_CST_UNSAFE_POS_DETECT].SetBackgroundColor(LED_LAMP_ON);
	//	else
	//		m_stcLamp_MagazineDetect[_eMANUAL_CST_UNSAFE_POS_DETECT].SetBackgroundColor(LED_LAMP_OFF);
	//}
	//m_bPrevStatus_MagazineDetect[_eMANUAL_CST_UNSAFE_POS_DETECT] = bMagazineDetectStatus;

	////CST Detect R
	//bMagazineDetectStatus = FALSE;
	//bMagazineDetectStatus = SharedInfo::DInputValue[_DIN_MAGAZINE_EXIST_DETECT_1];
	//if (m_bPrevStatus_MagazineDetect[_eMANUAL_CST_BWD_DETECT] != bMagazineDetectStatus)
	//{
	//	if (bMagazineDetectStatus)
	//		m_stcLamp_MagazineDetect[_eMANUAL_CST_BWD_DETECT].SetBackgroundColor(LED_LAMP_ON);
	//	else
	//		m_stcLamp_MagazineDetect[_eMANUAL_CST_BWD_DETECT].SetBackgroundColor(LED_LAMP_OFF);
	//}
	//m_bPrevStatus_MagazineDetect[_eMANUAL_CST_BWD_DETECT] = bMagazineDetectStatus;

	//CSTPaperBox Unit
	//BOOL bDiStatus[_eMANUAL_CST_PAPER_BOX_UNIT_MAX] = { FALSE, };
	//for (k = 0; k < _eMANUAL_CST_PAPER_BOX_UNIT_MAX; k++)
	//{
	//	bDiStatus[k] = SharedInfo::DInputValue[_DIN_PICK_UP_UNIT_FWD + k];
	//	if (m_bPrevStatus_CstPickUpUnitDI[k] != bDiStatus[k])
	//	{
	//		if (bDiStatus[k])
	//			m_stcLamp_CstPickUpUnitDI[k].SetBackgroundColor(LED_LAMP_ON);
	//		else
	//			m_stcLamp_CstPickUpUnitDI[k].SetBackgroundColor(LED_LAMP_OFF);
	//	}
	//	m_bPrevStatus_CstPickUpUnitDI[k] = bDiStatus[k];
	//}

	
	//if (Devs::m_CassetteMotion.Is_CSTPaperBoxUnitFwd())
	//{
	//	m_stcLamp_PaperBoxUnitDI[_eMANUAL_CST_PAPER_BOX_UNIT_FWD].SetBackgroundColor(LED_LAMP_ON);
	//}
	//else
	//{
	//	m_stcLamp_PaperBoxUnitDI[_eMANUAL_CST_PAPER_BOX_UNIT_FWD].SetBackgroundColor(LED_LAMP_OFF);
	//}
	//
	//if (Devs::m_CassetteMotion.Is_CSTPaperBoxUnitBwd())
	//{
	//	m_stcLamp_PaperBoxUnitDI[_eMANUAL_CST_PAPER_BOX_UNIT_BWD].SetBackgroundColor(LED_LAMP_ON);
	//}
	//else
	//{
	//	m_stcLamp_PaperBoxUnitDI[_eMANUAL_CST_PAPER_BOX_UNIT_BWD].SetBackgroundColor(LED_LAMP_OFF);
	//}

	
	
	//CST PickUp Unit
	BOOL bDiStatus[_eMANUAL_CST_PICK_UP_UNIT_MAX] = { FALSE, };
	for (k = 0; k < _eMANUAL_CST_PICK_UP_UNIT_MAX; k++)
	{
		bDiStatus[k] = SharedInfo::DInputValue[_DIN_PICK_UP_UNIT_FWD + k];
		if (m_bPrevStatus_CstPickUpUnitDI[k] != bDiStatus[k])
		{
			if (bDiStatus[k])
				m_stcLamp_CstPickUpUnitDI[k].SetBackgroundColor(LED_LAMP_ON);
			else
				m_stcLamp_CstPickUpUnitDI[k].SetBackgroundColor(LED_LAMP_OFF);
		}
		m_bPrevStatus_CstPickUpUnitDI[k] = bDiStatus[k];
	}
#pragma endregion

	if (Devs::m_CstRecvReadyFlow.GetCurrentFlowStep() > 0 || Devs::m_CstRecvDoneFlow.GetCurrentFlowStep() > 0)
	{
		m_btnCstRecvReady.EnableWindow(FALSE);
		m_btnCstRecvDone.EnableWindow(FALSE);
	}
	else
	{
		m_btnCstRecvReady.EnableWindow(TRUE);
		m_btnCstRecvDone.EnableWindow(TRUE);
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CManual_Sub_Cassette_Manual::OnBnClickedButtonManualSubCassetteManualCassetteZWaitPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;

	double dPos = CManualData::m_ManualDataCassette.Info.m_dCassetteZ_Wait_Pos;
	int nIndex = _eMANUAL_CASSETTE_INDEX_CASSETTE_Z_WAIT_POS;

	Str.Format(_T("Cassette Z Move ? (Wait_Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_CassetteMotion.CassetteZ_WaitPos();

	if (bRtn == TRUE)
	{
		m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;
	}
}


void CManual_Sub_Cassette_Manual::OnBnClickedButtonManualSubCassetteManualCassetteZ1floorPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;

	double dPos = CManualData::m_ManualDataCassette.Info.m_dCassetteZ_1Floor_Pos;
	int nIndex = _eMANUAL_CASSETTE_INDEX_CASSETTE_Z_1FLOOR_POS;

	Str.Format(_T("Cassette Z Move ? (1Floor Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_CassetteMotion.CassetteZ_1FloorPos();

	if (bRtn == TRUE)
	{
		m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;
	}
}


void CManual_Sub_Cassette_Manual::OnBnClickedButtonManualSubCassetteManualCassetteZ2floorPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;

	double dPos = CManualData::m_ManualDataCassette.Info.m_dCassetteZ_2Floor_Pos;
	int nIndex = _eMANUAL_CASSETTE_INDEX_CASSETTE_Z_2FLOOR_POS;

	Str.Format(_T("Cassette Z Move ? (2Floor Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_CassetteMotion.CassetteZ_2FloorPos();

	if (bRtn == TRUE)
	{
		m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;
	}
}


void CManual_Sub_Cassette_Manual::OnBnClickedButtonManualSubCassetteManualCassetteZ3floorPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;

	double dPos = CManualData::m_ManualDataCassette.Info.m_dCassetteZ_3Floor_Pos;
	int nIndex = _eMANUAL_CASSETTE_INDEX_CASSETTE_Z_3FLOOR_POS;

	Str.Format(_T("Cassette Z Move ? (3Floor Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_CassetteMotion.CassetteZ_3FloorPos();

	if (bRtn == TRUE)
	{
		m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;
	}
}


void CManual_Sub_Cassette_Manual::OnBnClickedButtonManualSubCassetteManualCassetteZ4floorPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;

	double dPos = CManualData::m_ManualDataCassette.Info.m_dCassetteZ_4Floor_Pos;
	int nIndex = _eMANUAL_CASSETTE_INDEX_CASSETTE_Z_4FLOOR_POS;

	Str.Format(_T("Cassette Z Move ? (4Floor Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_CassetteMotion.CassetteZ_4FloorPos();

	if (bRtn == TRUE)
	{
		m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;
	}
}

#if 0 //Junying TPCD Floor1~4 Use
void CManual_Sub_Cassette_Manual::OnBnClickedButtonManualSubCassetteManualCassetteZ5floorPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;

	double dPos = CManualData::m_ManualDataCassette.Info.m_dCassetteZ_5Floor_Pos;
	int nIndex = _eMANUAL_CASSETTE_INDEX_CASSETTE_Z_5FLOOR_POS;

	Str.Format(_T("Cassette Z Move ? (5Floor Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_CassetteMotion.CassetteZ_5FloorPos();

	if (bRtn == TRUE)
	{
		m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;
	}
}


void CManual_Sub_Cassette_Manual::OnBnClickedButtonManualSubCassetteManualCassetteZ6floorPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;

	double dPos = CManualData::m_ManualDataCassette.Info.m_dCassetteZ_6Floor_Pos;
	int nIndex = _eMANUAL_CASSETTE_INDEX_CASSETTE_Z_6FLOOR_POS;

	Str.Format(_T("Cassette Z Move ? (6Floor Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_CassetteMotion.CassetteZ_6FloorPos();

	if (bRtn == TRUE)
	{
		m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;
	}
}
#endif

void CManual_Sub_Cassette_Manual::OnBnClickedButtonManualSubCassetteManualCstPickUpUnitFwd()
{
	if (IDOK != AfxMessageBox(_T("CST PickUp Unit Forward ?"), MB_OKCANCEL)) return;

	if (Devs::m_CassetteMotion.Is_CassetteZ_WaitPos() ||
		Devs::m_CassetteMotion.Is_CassetteZ_1FloorPos() ||
		Devs::m_CassetteMotion.Is_CassetteZ_2FloorPos() ||
		Devs::m_CassetteMotion.Is_CassetteZ_3FloorPos() ||
		Devs::m_CassetteMotion.Is_CassetteZ_4FloorPos()/* ||
		Devs::m_CassetteMotion.Is_CassetteZ_5FloorPos() ||
		Devs::m_CassetteMotion.Is_CassetteZ_6FloorPos()*/) //KJT 20210810 Junying TPCD Floor1~4 Use
	{
		Devs::m_CassetteMotion.CSTPickUpUnitFwd();
	}
	else
	{
		AfxMessageBox(_T("Check CST Z Pos !!"));
	}
}


void CManual_Sub_Cassette_Manual::OnBnClickedButtonManualSubCassetteManualCstPickUpUnitBwd()
{
	if (IDOK != AfxMessageBox(_T("CST PickUp Unit Backward ?"), MB_OKCANCEL)) return;

	Devs::m_CassetteMotion.CSTPickUpUnitBwd();
}


void CManual_Sub_Cassette_Manual::OnBnClickedButtonManualSubCassetteManualCstPickUpUnitClamp()
{
	if (IDOK != AfxMessageBox(_T("CST PickUp Unit Clamp ?"), MB_OKCANCEL)) return;

	Devs::m_CassetteMotion.CSTPickUpUnitClamp();
}


void CManual_Sub_Cassette_Manual::OnBnClickedButtonManualSubCassetteManualCstPickUpUnitUnclamp()
{
	if (IDOK != AfxMessageBox(_T("CST PickUp Unit Unclamp ?"), MB_OKCANCEL)) return;

	Devs::m_CassetteMotion.CSTPickUpUnitUnclamp();
}


void CManual_Sub_Cassette_Manual::OnBnClickedButtonManualSubCassetteManualCstBarcodeRead()
{
	//Devs::m_SocketCassetteBarCode.ReadCode();
}


void CManual_Sub_Cassette_Manual::OnBnClickedButtonManualSubCassetteManualCstBarcodeView()
{
	//CString szMsg;
	//szMsg = Devs::m_SocketCassetteBarCode.GetLastCode();
	//m_EditCstBarcode.SetWindowText(szMsg);
}


void CManual_Sub_Cassette_Manual::OnBnClickedButtonManualSubCassetteManualPaperBoxUnitFwd()
{
	// TODO: Add your control notification handler code here
	CString Str;

	if (IDOK != AfxMessageBox(_T("Paper Box Forward ?"), MB_OKCANCEL)) return;	

	Devs::m_CassetteMotion.CSTPaperBoxUnitFwd();
}


void CManual_Sub_Cassette_Manual::OnBnClickedButtonManualSubCassetteManualPaperBoxUnitBwd()
{
	// TODO: Add your control notification handler code here

	if (IDOK != AfxMessageBox(_T("Paper Box Backward ?"), MB_OKCANCEL)) return;

	Devs::m_CassetteMotion.CSTPaperBoxUnitBwd();
}


void CManual_Sub_Cassette_Manual::OnBnClickedButtonManualSubCassetteManualCassetteRecvReadyFlow()
{
	if (IDOK != AfxMessageBox(_T("Cst Recv Ready Flow Start ?"), MB_OKCANCEL)) return;

	int nTargetFloor = m_comboCstTargetFloor.GetCurSel();
	Devs::m_CstRecvReadyFlow.Start((enum_CassetteFloor)nTargetFloor);
}


void CManual_Sub_Cassette_Manual::OnBnClickedButtonManualSubCassetteManualCassetteRecvDoneFlow()
{
	if (IDOK != AfxMessageBox(_T("Cst Recv Done Flow Start ?"), MB_OKCANCEL)) return;

	Devs::m_CstRecvDoneFlow.Start();
}
