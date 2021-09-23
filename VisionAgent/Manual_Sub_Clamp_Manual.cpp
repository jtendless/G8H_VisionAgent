// Manual_Sub_Gripper_Manual.cpp: 구현 파일
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "Manual_Sub_Clamp_Manual.h"
#include "afxdialogex.h"


// CManual_Sub_Clamp_Manual 대화 상자

IMPLEMENT_DYNAMIC(CManual_Sub_Clamp_Manual, CDialogEx)

CManual_Sub_Clamp_Manual::CManual_Sub_Clamp_Manual(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_MANUAL_SUB_CLAMP_MANUAL, pParent)
{
	Create(IDD_DLG_MANUAL_SUB_CLAMP_MANUAL, pParent);
}

CManual_Sub_Clamp_Manual::~CManual_Sub_Clamp_Manual()
{
}

void CManual_Sub_Clamp_Manual::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CManual_Sub_Clamp_Manual, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
	ON_WM_TIMER()	
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CLAMP_MANUAL_CLAMP_1_ON, &CManual_Sub_Clamp_Manual::OnBnClickedButtonManualSubClampManualClamp1On)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CLAMP_MANUAL_CLAMP_2_ON, &CManual_Sub_Clamp_Manual::OnBnClickedButtonManualSubClampManualClamp2On)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CLAMP_MANUAL_CLAMP_3_ON, &CManual_Sub_Clamp_Manual::OnBnClickedButtonManualSubClampManualClamp3On)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CLAMP_MANUAL_CLAMP_4_ON, &CManual_Sub_Clamp_Manual::OnBnClickedButtonManualSubClampManualClamp4On)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CLAMP_MANUAL_CLAMP_5_ON, &CManual_Sub_Clamp_Manual::OnBnClickedButtonManualSubClampManualClamp5On)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CLAMP_MANUAL_CLAMP_6_ON, &CManual_Sub_Clamp_Manual::OnBnClickedButtonManualSubClampManualClamp6On)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CLAMP_MANUAL_CLAMP_7_ON, &CManual_Sub_Clamp_Manual::OnBnClickedButtonManualSubClampManualClamp7On)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CLAMP_MANUAL_CLAMP_8_ON, &CManual_Sub_Clamp_Manual::OnBnClickedButtonManualSubClampManualClamp8On)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CLAMP_MANUAL_CLAMP_1_OFF, &CManual_Sub_Clamp_Manual::OnBnClickedButtonManualSubClampManualClamp1Off)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CLAMP_MANUAL_CLAMP_2_OFF, &CManual_Sub_Clamp_Manual::OnBnClickedButtonManualSubClampManualClamp2Off)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CLAMP_MANUAL_CLAMP_3_OFF, &CManual_Sub_Clamp_Manual::OnBnClickedButtonManualSubClampManualClamp3Off)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CLAMP_MANUAL_CLAMP_4_OFF, &CManual_Sub_Clamp_Manual::OnBnClickedButtonManualSubClampManualClamp4Off)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CLAMP_MANUAL_CLAMP_5_OFF, &CManual_Sub_Clamp_Manual::OnBnClickedButtonManualSubClampManualClamp5Off)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CLAMP_MANUAL_CLAMP_6_OFF, &CManual_Sub_Clamp_Manual::OnBnClickedButtonManualSubClampManualClamp6Off)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CLAMP_MANUAL_CLAMP_7_OFF, &CManual_Sub_Clamp_Manual::OnBnClickedButtonManualSubClampManualClamp7Off)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CLAMP_MANUAL_CLAMP_8_OFF, &CManual_Sub_Clamp_Manual::OnBnClickedButtonManualSubClampManualClamp8Off)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CLAMP_MANUAL_ACTIVE_CLAMP_ON, &CManual_Sub_Clamp_Manual::OnBnClickedButtonManualSubClampManualActiveClampOn)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CLAMP_MANUAL_ALL_CLAMP_ON, &CManual_Sub_Clamp_Manual::OnBnClickedButtonManualSubClampManualAllClampOn)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CLAMP_MANUAL_ACTIVE_CLAMP_OFF, &CManual_Sub_Clamp_Manual::OnBnClickedButtonManualSubClampManualActiveClampOff)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_CLAMP_MANUAL_ALL_CLAMP_OFF, &CManual_Sub_Clamp_Manual::OnBnClickedButtonManualSubClampManualAllClampOff)
END_MESSAGE_MAP()


// CManual_Sub_Clamp_Manual 메시지 처리기


BOOL CManual_Sub_Clamp_Manual::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	InitCtrl();

	return TRUE;
}
//--------------------------------------------------------
void CManual_Sub_Clamp_Manual::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
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
void CManual_Sub_Clamp_Manual::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (Is_Comp_Usable() == FALSE)	return;
}
//--------------------------------------------------------
void CManual_Sub_Clamp_Manual::OnTimer(UINT_PTR nIDEvent)
{
	int k = 0;
	CString Str = _T("");
	double dEnd_Tick, dWait_Tick;
	for (k = 0; k < _eMANUAL_INDEX_CLAMP_POS_MAX; k++)
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
	
	m_bMotionDone[_eMANUAL_INDEX_CLAMP_1_CLAMP_ON] = Devs::m_ClampMotion.Is_ClampOn(eGRIPPER_ROW1) ? TRUE : FALSE;
	m_bMotionDone[_eMANUAL_INDEX_CLAMP_2_CLAMP_ON] = Devs::m_ClampMotion.Is_ClampOn(eGRIPPER_ROW2) ? TRUE : FALSE;
	m_bMotionDone[_eMANUAL_INDEX_CLAMP_3_CLAMP_ON] = Devs::m_ClampMotion.Is_ClampOn(eGRIPPER_ROW3) ? TRUE : FALSE;
	//m_bMotionDone[_eMANUAL_INDEX_CLAMP_4_CLAMP_ON] = Devs::m_ClampMotion.Is_ClampOn(eGRIPPER_ROW4) ? TRUE : FALSE;
	//m_bMotionDone[_eMANUAL_INDEX_CLAMP_5_CLAMP_ON] = Devs::m_ClampMotion.Is_ClampOn(eGRIPPER_ROW5) ? TRUE : FALSE;
#ifdef GRIPPER_8
	m_bMotionDone[_eMANUAL_INDEX_CLAMP_6_CLAMP_ON] = Devs::m_ClampMotion.Is_ClampOn(eGRIPPER_ROW6) ? TRUE : FALSE;
	m_bMotionDone[_eMANUAL_INDEX_CLAMP_7_CLAMP_ON] = Devs::m_ClampMotion.Is_ClampOn(eGRIPPER_ROW7) ? TRUE : FALSE;
	m_bMotionDone[_eMANUAL_INDEX_CLAMP_8_CLAMP_ON] = Devs::m_ClampMotion.Is_ClampOn(eGRIPPER_ROW8) ? TRUE : FALSE;
#endif

	m_bMotionDone[_eMANUAL_INDEX_CLAMP_1_CLAMP_OFF] = Devs::m_ClampMotion.Is_ClampOff(eGRIPPER_ROW1) ? TRUE : FALSE;
	m_bMotionDone[_eMANUAL_INDEX_CLAMP_2_CLAMP_OFF] = Devs::m_ClampMotion.Is_ClampOff(eGRIPPER_ROW2) ? TRUE : FALSE;
	m_bMotionDone[_eMANUAL_INDEX_CLAMP_3_CLAMP_OFF] = Devs::m_ClampMotion.Is_ClampOff(eGRIPPER_ROW3) ? TRUE : FALSE;
	//m_bMotionDone[_eMANUAL_INDEX_CLAMP_4_CLAMP_OFF] = Devs::m_ClampMotion.Is_ClampOff(eGRIPPER_ROW4) ? TRUE : FALSE;
	//m_bMotionDone[_eMANUAL_INDEX_CLAMP_5_CLAMP_OFF] = Devs::m_ClampMotion.Is_ClampOff(eGRIPPER_ROW5) ? TRUE : FALSE;
#ifdef GRIPPER_8
	m_bMotionDone[_eMANUAL_INDEX_CLAMP_6_CLAMP_OFF] = Devs::m_ClampMotion.Is_ClampOff(eGRIPPER_ROW6) ? TRUE : FALSE;
	m_bMotionDone[_eMANUAL_INDEX_CLAMP_7_CLAMP_OFF] = Devs::m_ClampMotion.Is_ClampOff(eGRIPPER_ROW7) ? TRUE : FALSE;
	m_bMotionDone[_eMANUAL_INDEX_CLAMP_8_CLAMP_OFF] = Devs::m_ClampMotion.Is_ClampOff(eGRIPPER_ROW8) ? TRUE : FALSE;
#endif

	m_bMotionDone[_eMANUAL_INDEX_CLAMP_ACTIVE_CLAMP_ON] = Devs::m_ClampMotion.Is_ClampOn_Active() ? TRUE : FALSE;
	m_bMotionDone[_eMANUAL_INDEX_CLAMP_ACTIVE_CLAMP_OFF] = Devs::m_ClampMotion.Is_ClampOff_Active() ? TRUE : FALSE;

	m_bMotionDone[_eMANUAL_INDEX_CLAMP_ALL_CLAMP_ON] = Devs::m_ClampMotion.Is_ClampOn_All() ? TRUE : FALSE;
	m_bMotionDone[_eMANUAL_INDEX_CLAMP_ALL_CLAMP_OFF] = Devs::m_ClampMotion.Is_ClampOff_All() ? TRUE : FALSE;

	for (k = 0; k < _eMANUAL_INDEX_CLAMP_POS_MAX; k++)
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

	//Torque Value Display
	for (int i = 0; i < MAX_STRETCH_SIZE; i++)
	{
		Str.Format(_T("%.4f"), SharedInfo::m_nClampTorquedMonitorValue[i]);						m_stcSet_L[i].SetWindowText(Str);
		Str.Format(_T("%.4f"), SharedInfo::m_nClampTorquedMonitorValue[i + MAX_STRETCH_SIZE]);	m_stcSet_R[i].SetWindowText(Str);
		Str.Format(_T("%.4f"), CManualData::m_ManualDataClamp.Info.m_dClampTorque);			m_stcMeasure_L[i].SetWindowText(Str);
		Str.Format(_T("%.4f"), CManualData::m_ManualDataClamp.Info.m_dClampTorque);			m_stcMeasure_R[i].SetWindowText(Str);
	}

	CDialogEx::OnTimer(nIDEvent);
}
//--------------------------------------------------------
void	CManual_Sub_Clamp_Manual::InitCtrl()
{
	CString Str = _T("");

	m_stLamp_Work[_eMANUAL_INDEX_CLAMP_1_CLAMP_ON].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_CLAMP_MANUAL_CLAMP_1_ON, this);
	m_stLamp_Work[_eMANUAL_INDEX_CLAMP_2_CLAMP_ON].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_CLAMP_MANUAL_CLAMP_2_ON, this);
	m_stLamp_Work[_eMANUAL_INDEX_CLAMP_3_CLAMP_ON].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_CLAMP_MANUAL_CLAMP_3_ON, this);
	m_stLamp_Work[_eMANUAL_INDEX_CLAMP_4_CLAMP_ON].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_CLAMP_MANUAL_CLAMP_4_ON, this);
	m_stLamp_Work[_eMANUAL_INDEX_CLAMP_5_CLAMP_ON].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_CLAMP_MANUAL_CLAMP_5_ON, this);
#ifdef GRIPPER_8
	m_stLamp_Work[_eMANUAL_INDEX_CLAMP_6_CLAMP_ON].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_CLAMP_MANUAL_CLAMP_6_ON, this);
	m_stLamp_Work[_eMANUAL_INDEX_CLAMP_7_CLAMP_ON].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_CLAMP_MANUAL_CLAMP_7_ON, this);
	m_stLamp_Work[_eMANUAL_INDEX_CLAMP_8_CLAMP_ON].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_CLAMP_MANUAL_CLAMP_8_ON, this);
#endif
	m_stLamp_Work[_eMANUAL_INDEX_CLAMP_1_CLAMP_OFF].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_CLAMP_MANUAL_CLAMP_1_OFF, this);
	m_stLamp_Work[_eMANUAL_INDEX_CLAMP_2_CLAMP_OFF].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_CLAMP_MANUAL_CLAMP_2_OFF, this);
	m_stLamp_Work[_eMANUAL_INDEX_CLAMP_3_CLAMP_OFF].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_CLAMP_MANUAL_CLAMP_3_OFF, this);
	m_stLamp_Work[_eMANUAL_INDEX_CLAMP_4_CLAMP_OFF].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_CLAMP_MANUAL_CLAMP_4_OFF, this);
	m_stLamp_Work[_eMANUAL_INDEX_CLAMP_5_CLAMP_OFF].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_CLAMP_MANUAL_CLAMP_5_OFF, this);
#ifdef GRIPPER_8
	m_stLamp_Work[_eMANUAL_INDEX_CLAMP_6_CLAMP_OFF].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_CLAMP_MANUAL_CLAMP_6_OFF, this);
	m_stLamp_Work[_eMANUAL_INDEX_CLAMP_7_CLAMP_OFF].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_CLAMP_MANUAL_CLAMP_7_OFF, this);
	m_stLamp_Work[_eMANUAL_INDEX_CLAMP_8_CLAMP_OFF].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_CLAMP_MANUAL_CLAMP_8_OFF, this);
#endif
	m_stLamp_Work[_eMANUAL_INDEX_CLAMP_ACTIVE_CLAMP_ON].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_CLAMP_MANUAL_ACTIVE_CLAMP_ON, this);
	m_stLamp_Work[_eMANUAL_INDEX_CLAMP_ACTIVE_CLAMP_OFF].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_CLAMP_MANUAL_ACTIVE_CLAMP_OFF, this);

	m_stLamp_Work[_eMANUAL_INDEX_CLAMP_ALL_CLAMP_ON].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_CLAMP_MANUAL_ALL_CLAMP_ON, this);
	m_stLamp_Work[_eMANUAL_INDEX_CLAMP_ALL_CLAMP_OFF].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_CLAMP_MANUAL_ALL_CLAMP_OFF, this);

	for (int k = 0; k < _eMANUAL_INDEX_CLAMP_POS_MAX; k++)
	{
		m_stLamp_Work[k].SetParaChangeColor(BK_GND);
		m_stLamp_Work[k].SetParaOriginColor(STATEBAR_NAME_BK_RGB);
		m_stLamp_Work[k].SetBackgroundColor(STATEBAR_NAME_BK_RGB);
		m_stLamp_Work[k].SetTextColor(LED_LAMP_OFF);
		m_stLamp_Work[k].SetBackgroundColor(LED_LAMP_OFF);
	}

	m_stcSet_L[eGRIPPER_ROW1].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_CLAMP_SET_L1, this);
	m_stcSet_L[eGRIPPER_ROW2].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_CLAMP_SET_L2, this);
	m_stcSet_L[eGRIPPER_ROW3].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_CLAMP_SET_L3, this);
	//m_stcSet_L[eGRIPPER_ROW4].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_CLAMP_SET_L4, this);
	//m_stcSet_L[eGRIPPER_ROW5].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_CLAMP_SET_L5, this);
#ifdef GRIPPER_8
	m_stcSet_L[eGRIPPER_ROW6].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_CLAMP_SET_L6, this);
	m_stcSet_L[eGRIPPER_ROW7].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_CLAMP_SET_L7, this);
	m_stcSet_L[eGRIPPER_ROW8].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_CLAMP_SET_L8, this);
#endif
	m_stcSet_R[eGRIPPER_ROW1].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_CLAMP_SET_R1, this);
	m_stcSet_R[eGRIPPER_ROW2].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_CLAMP_SET_R2, this);
	m_stcSet_R[eGRIPPER_ROW3].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_CLAMP_SET_R3, this);
	//m_stcSet_R[eGRIPPER_ROW4].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_CLAMP_SET_R4, this);
	//m_stcSet_R[eGRIPPER_ROW5].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_CLAMP_SET_R5, this);
#ifdef GRIPPER_8
	m_stcSet_R[eGRIPPER_ROW6].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_CLAMP_SET_R6, this);
	m_stcSet_R[eGRIPPER_ROW7].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_CLAMP_SET_R7, this);
	m_stcSet_R[eGRIPPER_ROW8].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_CLAMP_SET_R8, this);
#endif
	m_stcMeasure_L[eGRIPPER_ROW1].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_CLAMP_MEASURE_L1, this);
	m_stcMeasure_L[eGRIPPER_ROW2].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_CLAMP_MEASURE_L2, this);
	m_stcMeasure_L[eGRIPPER_ROW3].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_CLAMP_MEASURE_L3, this);
	//m_stcMeasure_L[eGRIPPER_ROW4].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_CLAMP_MEASURE_L4, this);
	//m_stcMeasure_L[eGRIPPER_ROW5].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_CLAMP_MEASURE_L5, this);
#ifdef GRIPPER_8
	m_stcMeasure_L[eGRIPPER_ROW6].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_CLAMP_MEASURE_L6, this);
	m_stcMeasure_L[eGRIPPER_ROW7].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_CLAMP_MEASURE_L7, this);
	m_stcMeasure_L[eGRIPPER_ROW8].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_CLAMP_MEASURE_L8, this);
#endif

	m_stcMeasure_R[eGRIPPER_ROW1].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_CLAMP_MEASURE_R1, this);
	m_stcMeasure_R[eGRIPPER_ROW2].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_CLAMP_MEASURE_R2, this);
	m_stcMeasure_R[eGRIPPER_ROW3].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_CLAMP_MEASURE_R3, this);
	//m_stcMeasure_R[eGRIPPER_ROW4].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_CLAMP_MEASURE_R4, this);
	//m_stcMeasure_R[eGRIPPER_ROW5].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_CLAMP_MEASURE_R5, this);
#ifdef GRIPPER_8
	m_stcMeasure_R[eGRIPPER_ROW6].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_CLAMP_MEASURE_R6, this);
	m_stcMeasure_R[eGRIPPER_ROW7].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_CLAMP_MEASURE_R7, this);
	m_stcMeasure_R[eGRIPPER_ROW8].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_CLAMP_MEASURE_R8, this);
#endif

	Str.Format(_T("1.0"));
	for (int i = 0; i < eGRIPPER_ROW_MAX; i++)
	{
		m_stcSet_L[i].SetWindowText(Str);
		m_stcSet_R[i].SetWindowText(Str);
		m_stcMeasure_L[i].SetWindowText(Str);
		m_stcMeasure_R[i].SetWindowText(Str);
	}
}
//--------------------------------------------------------
BOOL	CManual_Sub_Clamp_Manual::Is_Comp_Usable()
{
	return TRUE;
}
//--------------------------------------------------------
void	CManual_Sub_Clamp_Manual::InitPara()
{
	for (int k = 0; k < _eMANUAL_INDEX_CLAMP_POS_MAX; k++)
	{
		m_nWork_State[k] = _eSTATE_NONE;
		m_stLamp_Work[k].SetBackgroundColor(BTN_LAMP_OFF);

		m_bMotionDone[k] = FALSE;
		m_bPrevStatus_InPos[k] = FALSE;
	}
}
//--------------------------------------------------------
void	CManual_Sub_Clamp_Manual::CheckChangeData()
{
	
}

#pragma region //Clamp On Left
void CManual_Sub_Clamp_Manual::OnBnClickedButtonManualSubClampManualClamp1On()
{
	if (IDOK != AfxMessageBox(_T("Clamp On ?"), MB_OKCANCEL)) return;

	Devs::m_ClampMotion.ClampOn(eGRIPPER_ROW1);
}
void CManual_Sub_Clamp_Manual::OnBnClickedButtonManualSubClampManualClamp2On()
{
	if (IDOK != AfxMessageBox(_T("Clamp On ?"), MB_OKCANCEL)) return;

	Devs::m_ClampMotion.ClampOn(eGRIPPER_ROW2);
}
void CManual_Sub_Clamp_Manual::OnBnClickedButtonManualSubClampManualClamp3On()
{
	if (IDOK != AfxMessageBox(_T("Clamp On ?"), MB_OKCANCEL)) return;

	Devs::m_ClampMotion.ClampOn(eGRIPPER_ROW3);
}
void CManual_Sub_Clamp_Manual::OnBnClickedButtonManualSubClampManualClamp4On()
{
	if (IDOK != AfxMessageBox(_T("Clamp On ?"), MB_OKCANCEL)) return;

//	Devs::m_ClampMotion.ClampOn(eGRIPPER_ROW4);
}
void CManual_Sub_Clamp_Manual::OnBnClickedButtonManualSubClampManualClamp5On()
{
	if (IDOK != AfxMessageBox(_T("Clamp On ?"), MB_OKCANCEL)) return;

	//Devs::m_ClampMotion.ClampOn(eGRIPPER_ROW5);
}
void CManual_Sub_Clamp_Manual::OnBnClickedButtonManualSubClampManualClamp6On()
{
#ifdef GRIPPER_8
	if (IDOK != AfxMessageBox(_T("Clamp On ?"), MB_OKCANCEL)) return;

	Devs::m_ClampMotion.ClampOn(eGRIPPER_ROW6);
#endif

}
void CManual_Sub_Clamp_Manual::OnBnClickedButtonManualSubClampManualClamp7On()
{
#ifdef GRIPPER_8
	if (IDOK != AfxMessageBox(_T("Clamp On ?"), MB_OKCANCEL)) return;

	Devs::m_ClampMotion.ClampOn(eGRIPPER_ROW7);
#endif
}
void CManual_Sub_Clamp_Manual::OnBnClickedButtonManualSubClampManualClamp8On()
{
#ifdef GRIPPER_8
	if (IDOK != AfxMessageBox(_T("Clamp On ?"), MB_OKCANCEL)) return;

	Devs::m_ClampMotion.ClampOn(eGRIPPER_ROW8);
#endif
}
#pragma endregion

#pragma region //Clamp Off Left
void CManual_Sub_Clamp_Manual::OnBnClickedButtonManualSubClampManualClamp1Off()
{
	if (IDOK != AfxMessageBox(_T("Clamp Off ?"), MB_OKCANCEL)) return;

	Devs::m_ClampMotion.ClampOff(eGRIPPER_ROW1);
}
void CManual_Sub_Clamp_Manual::OnBnClickedButtonManualSubClampManualClamp2Off()
{
	if (IDOK != AfxMessageBox(_T("Clamp Off ?"), MB_OKCANCEL)) return;

	Devs::m_ClampMotion.ClampOff(eGRIPPER_ROW2);
}
void CManual_Sub_Clamp_Manual::OnBnClickedButtonManualSubClampManualClamp3Off()
{
	if (IDOK != AfxMessageBox(_T("Clamp Off ?"), MB_OKCANCEL)) return;

	Devs::m_ClampMotion.ClampOff(eGRIPPER_ROW3);
}
void CManual_Sub_Clamp_Manual::OnBnClickedButtonManualSubClampManualClamp4Off()
{
	if (IDOK != AfxMessageBox(_T("Clamp Off ?"), MB_OKCANCEL)) return;

	//Devs::m_ClampMotion.ClampOff(eGRIPPER_ROW4);
}
void CManual_Sub_Clamp_Manual::OnBnClickedButtonManualSubClampManualClamp5Off()
{
	if (IDOK != AfxMessageBox(_T("Clamp Off ?"), MB_OKCANCEL)) return;

	//Devs::m_ClampMotion.ClampOff(eGRIPPER_ROW5);
}
void CManual_Sub_Clamp_Manual::OnBnClickedButtonManualSubClampManualClamp6Off()
{
#ifdef GRIPPER_8
	if (IDOK != AfxMessageBox(_T("Clamp Off ?"), MB_OKCANCEL)) return;

	Devs::m_ClampMotion.ClampOff(eGRIPPER_ROW6);
#endif
}
void CManual_Sub_Clamp_Manual::OnBnClickedButtonManualSubClampManualClamp7Off()
{
#ifdef GRIPPER_8
	if (IDOK != AfxMessageBox(_T("Clamp Off ?"), MB_OKCANCEL)) return;

	Devs::m_ClampMotion.ClampOff(eGRIPPER_ROW7);
#endif
}
void CManual_Sub_Clamp_Manual::OnBnClickedButtonManualSubClampManualClamp8Off()
{
#ifdef GRIPPER_8
	if (IDOK != AfxMessageBox(_T("Clamp Off ?"), MB_OKCANCEL)) return;

	Devs::m_ClampMotion.ClampOff(eGRIPPER_ROW8);
#endif
}
#pragma endregion


#pragma region //All Clamp OnOff
void CManual_Sub_Clamp_Manual::OnBnClickedButtonManualSubClampManualActiveClampOn()
{
	Devs::m_ClampMotion.ClampOn_Active();
}
void CManual_Sub_Clamp_Manual::OnBnClickedButtonManualSubClampManualAllClampOn()
{
	Devs::m_ClampMotion.ClampOn_All();
}
void CManual_Sub_Clamp_Manual::OnBnClickedButtonManualSubClampManualActiveClampOff()
{
	Devs::m_ClampMotion.ClampOff_Active();
}
void CManual_Sub_Clamp_Manual::OnBnClickedButtonManualSubClampManualAllClampOff()
{
	Devs::m_ClampMotion.ClampOff_All();
}
#pragma endregion