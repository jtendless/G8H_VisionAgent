// Manual_Sub_Stretch_Manual.cpp: 구현 파일
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "Manual_Sub_Stretch_Manual.h"
#include "afxdialogex.h"
#include "Data/ManualData.h"
#include "Motion/BaseMotion.h"


// CManual_Sub_Stretch_Manual 대화 상자

IMPLEMENT_DYNAMIC(CManual_Sub_Stretch_Manual, CDialogEx)

CManual_Sub_Stretch_Manual::CManual_Sub_Stretch_Manual(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_MANUAL_SUB_STRETCH_MANUAL, pParent)
{
	Create(IDD_DLG_MANUAL_SUB_STRETCH_MANUAL, pParent);
}

CManual_Sub_Stretch_Manual::~CManual_Sub_Stretch_Manual()
{
}

void CManual_Sub_Stretch_Manual::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CManual_Sub_Stretch_Manual, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_MANUAL_ALL_WAIT_POS, &CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualAllWaitPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_MANUAL_ACTIVE_WAIT_POS, &CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualActiveWaitPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_MANUAL_ACTIVE_FWD_POS, &CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualActiveFwdPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_MANUAL_ACTIVE_BWD_POS, &CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualActiveBwdPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_MANUAL_STRETCH_START, &CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualStretchStart)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_MANUAL_STRETCH_STOP, &CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualStretchStop)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_MANUAL_STRETCH_FORCE_ZERO, &CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualStretchForceZero)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_MANUAL_ALL_FWD_POS, &CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualAllFwdPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_MANUAL_ALL_BWD_POS, &CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualAllBwdPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_MANUAL_RELEASE_START, &CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualReleaseStart)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_MANUAL_CLAMP_ON_L1, &CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualClampOnL1)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_MANUAL_CLAMP_ON_L2, &CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualClampOnL2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_MANUAL_CLAMP_ON_L3, &CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualClampOnL3)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_MANUAL_CLAMP_ON_R1, &CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualClampOnR1)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_MANUAL_CLAMP_ON_R2, &CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualClampOnR2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_MANUAL_CLAMP_ON_R3, &CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualClampOnR3)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_MANUAL_CLAMP_OFF_L1, &CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualClampOffL1)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_MANUAL_CLAMP_OFF_L2, &CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualClampOffL2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_MANUAL_CLAMP_OFF_L3, &CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualClampOffL3)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_MANUAL_CLAMP_OFF_R1, &CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualClampOffR1)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_MANUAL_CLAMP_OFF_R2, &CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualClampOffR2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_MANUAL_CLAMP_OFF_R3, &CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualClampOffR3)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_MANUAL_CLAMP_ON_ALL, &CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualClampOnAll)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_MANUAL_CLAMP_OFF_ALL, &CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualClampOffAll)
END_MESSAGE_MAP()


// CManual_Sub_Stretch_Manual 메시지 처리기

BOOL CManual_Sub_Stretch_Manual::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	InitCtrl();

	return TRUE;
}
//--------------------------------------------------------
void CManual_Sub_Stretch_Manual::OnShowWindow(BOOL bShow, UINT nStatus)
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
void CManual_Sub_Stretch_Manual::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (Is_Comp_Usable() == FALSE)	return;
}
//--------------------------------------------------------
void CManual_Sub_Stretch_Manual::OnTimer(UINT_PTR nIDEvent)
{
	CString Str = _T("");
	int i = 0, k = 0;
	double dEnd_Tick, dWait_Tick;
	double dSetZeroEnd_Tick, dSetZeorWait_Tick;

	if (nIDEvent == 1)
	{
		for (k = 0; k < _eMANUAL_WORK_INDEX_STRETCH_POS_MAX; k++)
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
		for (i = 0; i < eGRIPPER_ROW_MAX; i++)
		{
			if (CModelData::m_StretchPara.Info.bStretchUse[i] == TRUE)
			{
				m_bMotionDone[_eMANUAL_WORK_INDEX_STRETCH_ACTIVE_WAIT_POS] = Devs::m_StretchMotion.Is_Stretch_WaitPos_Active();
				m_bMotionDone[_eMANUAL_WORK_INDEX_STRETCH_ACTIVE_FWD_POS] = Devs::m_StretchMotion.Is_Stretch_FwdPos_Active();
				m_bMotionDone[_eMANUAL_WORK_INDEX_STRETCH_ACTIVE_BWD_POS] = Devs::m_StretchMotion.Is_Stretch_BwdPos_Active();
			}

			m_bMotionDone[_eMANUAL_WORK_INDEX_STRETCH_ALL_WAIT_POS] = Devs::m_StretchMotion.Is_Stretch_WaitPos_All();
			m_bMotionDone[_eMANUAL_WORK_INDEX_STRETCH_ALL_FWD_POS] = Devs::m_StretchMotion.Is_Stretch_FwdPos_All();
			m_bMotionDone[_eMANUAL_WORK_INDEX_STRETCH_ALL_BWD_POS] = Devs::m_StretchMotion.Is_Stretch_BwdPos_All();

			Str.Format(_T("%.4f"), SharedInfo::dSF_LoadcellForce[i]);						m_stcMeasure_L[i].SetWindowText(Str);
			Str.Format(_T("%.4f"), SharedInfo::dSF_LoadcellForce[i + MAX_STRETCH_SIZE]);	m_stcMeasure_R[i].SetWindowText(Str);
			if (SharedInfo::nStretchStatus[i] == FORCE_CONTROL_STATUS_IDLE)
				m_stcStatus_L[i].SetWindowText(_T("Idle"));
			else if (SharedInfo::nStretchStatus[i] == FORCE_CONTROL_STATUS_EMG)
				m_stcStatus_L[i].SetWindowText(_T("Emg"));
			else if (SharedInfo::nStretchStatus[i] == FORCE_CONTROL_STATUS_SUCCESS)
				m_stcStatus_L[i].SetWindowText(_T("Success"));
			else if (SharedInfo::nStretchStatus[i] == FORCE_CONTROL_STATUS_FAIL)
				m_stcStatus_L[i].SetWindowText(_T("Fail"));
			else
			{
				Str.Format(_T("%d"), SharedInfo::nStretchStatus[i]);
				m_stcStatus_L[i].SetWindowText(Str);
			}

			if (SharedInfo::nStretchStatus[i + eGRIPPER_ROW_MAX] == FORCE_CONTROL_STATUS_IDLE)
				m_stcStatus_R[i].SetWindowText(_T("Idle"));
			else if (SharedInfo::nStretchStatus[i + eGRIPPER_ROW_MAX] == FORCE_CONTROL_STATUS_EMG)
				m_stcStatus_R[i].SetWindowText(_T("Emg"));
			else if (SharedInfo::nStretchStatus[i + eGRIPPER_ROW_MAX] == FORCE_CONTROL_STATUS_SUCCESS)
				m_stcStatus_R[i].SetWindowText(_T("Success"));
			else if (SharedInfo::nStretchStatus[i + eGRIPPER_ROW_MAX] == FORCE_CONTROL_STATUS_FAIL)
				m_stcStatus_R[i].SetWindowText(_T("Fail"));
			else
			{
				Str.Format(_T("%d"), SharedInfo::nStretchStatus[i + eGRIPPER_ROW_MAX]);
				m_stcStatus_R[i].SetWindowText(Str);
			}
		}

		for (k = 0; k < _eMANUAL_WORK_INDEX_STRETCH_POS_MAX; k++)
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
	}

	CDialogEx::OnTimer(nIDEvent);
}
void	CManual_Sub_Stretch_Manual::InitCtrl()
{
	CString Str = _T("");

	m_stLamp_Work[_eMANUAL_WORK_INDEX_STRETCH_ACTIVE_WAIT_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_STRETCH_MANUAL_ACTIVE_WAIT_POS, this);
	m_stLamp_Work[_eMANUAL_WORK_INDEX_STRETCH_ACTIVE_FWD_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_STRETCH_MANUAL_ACTIVE_FWD_POS, this);
	m_stLamp_Work[_eMANUAL_WORK_INDEX_STRETCH_ACTIVE_BWD_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_STRETCH_MANUAL_ACTIVE_BWD_POS, this);

	m_stLamp_Work[_eMANUAL_WORK_INDEX_STRETCH_ALL_WAIT_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_STRETCH_MANUAL_ALL_WAIT_POS, this);
	m_stLamp_Work[_eMANUAL_WORK_INDEX_STRETCH_ALL_FWD_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_STRETCH_MANUAL_ALL_FWD_POS, this);
	m_stLamp_Work[_eMANUAL_WORK_INDEX_STRETCH_ALL_BWD_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_STRETCH_MANUAL_ALL_BWD_POS, this);

	//21.03.06 sjc
	m_stLeft_Clamp_On[0].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_STRETCH_MANUAL_CLAMP_ON_L1, this);
	m_stLeft_Clamp_On[1].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_STRETCH_MANUAL_CLAMP_ON_L2, this);
	m_stLeft_Clamp_On[2].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_STRETCH_MANUAL_CLAMP_ON_L3, this);
	m_stLeft_Clamp_Off[0].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_STRETCH_MANUAL_CLAMP_OFF_L1, this);
	m_stLeft_Clamp_Off[1].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_STRETCH_MANUAL_CLAMP_OFF_L2, this);
	m_stLeft_Clamp_Off[2].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_STRETCH_MANUAL_CLAMP_OFF_L3, this);

	m_stRight_Clamp_On[0].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_STRETCH_MANUAL_CLAMP_ON_R1, this);
	m_stRight_Clamp_On[1].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_STRETCH_MANUAL_CLAMP_ON_R2, this);
	m_stRight_Clamp_On[2].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_STRETCH_MANUAL_CLAMP_ON_R3, this);
	m_stRight_Clamp_Off[0].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_STRETCH_MANUAL_CLAMP_OFF_R1, this);
	m_stRight_Clamp_Off[1].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_STRETCH_MANUAL_CLAMP_OFF_R2, this);
	m_stRight_Clamp_Off[2].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_STRETCH_MANUAL_CLAMP_OFF_R3, this);
	//
	for (int k = 0; k < _eMANUAL_WORK_INDEX_STRETCH_POS_MAX; k++)
	{
		m_stLamp_Work[k].SetParaChangeColor(BK_GND);
		m_stLamp_Work[k].SetParaOriginColor(STATEBAR_NAME_BK_RGB);
		m_stLamp_Work[k].SetBackgroundColor(STATEBAR_NAME_BK_RGB);
		m_stLamp_Work[k].SetTextColor(LED_LAMP_OFF);
		m_stLamp_Work[k].SetBackgroundColor(LED_LAMP_OFF);
	}

	m_stcSet_L[eGRIPPER_ROW1].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_SET_L1, this);
	m_stcSet_L[eGRIPPER_ROW2].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_SET_L2, this);
	m_stcSet_L[eGRIPPER_ROW3].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_SET_L3, this);
	//m_stcSet_L[eGRIPPER_ROW4].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_SET_L4, this);
	//m_stcSet_L[eGRIPPER_ROW5].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_SET_L5, this);
#ifdef GRIPPER_8
	m_stcSet_L[eGRIPPER_ROW6].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_SET_L6, this);
	m_stcSet_L[eGRIPPER_ROW7].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_SET_L7, this);
	m_stcSet_L[eGRIPPER_ROW8].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_SET_L8, this);
#endif

	m_stcSet_R[eGRIPPER_ROW1].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_SET_R1, this);
	m_stcSet_R[eGRIPPER_ROW2].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_SET_R2, this);
	m_stcSet_R[eGRIPPER_ROW3].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_SET_R3, this);
	//m_stcSet_R[eGRIPPER_ROW4].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_SET_R4, this);
	//m_stcSet_R[eGRIPPER_ROW5].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_SET_R5, this);
#ifdef GRIPPER_8
	m_stcSet_R[eGRIPPER_ROW6].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_SET_R6, this);
	m_stcSet_R[eGRIPPER_ROW7].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_SET_R7, this);
	m_stcSet_R[eGRIPPER_ROW8].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_SET_R8, this);
#endif

	m_stcMeasure_L[eGRIPPER_ROW1].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_MEASURE_L1, this);
	m_stcMeasure_L[eGRIPPER_ROW2].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_MEASURE_L2, this);
	m_stcMeasure_L[eGRIPPER_ROW3].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_MEASURE_L3, this);
	//m_stcMeasure_L[eGRIPPER_ROW4].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_MEASURE_L4, this);
	//m_stcMeasure_L[eGRIPPER_ROW5].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_MEASURE_L5, this);
#ifdef GRIPPER_8
	m_stcMeasure_L[eGRIPPER_ROW6].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_MEASURE_L6, this);
	m_stcMeasure_L[eGRIPPER_ROW7].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_MEASURE_L7, this);
	m_stcMeasure_L[eGRIPPER_ROW8].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_MEASURE_L8, this);
#endif

	m_stcMeasure_R[eGRIPPER_ROW1].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_MEASURE_R1, this);
	m_stcMeasure_R[eGRIPPER_ROW2].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_MEASURE_R2, this);
	m_stcMeasure_R[eGRIPPER_ROW3].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_MEASURE_R3, this);
	//m_stcMeasure_R[eGRIPPER_ROW4].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_MEASURE_R4, this);
	//m_stcMeasure_R[eGRIPPER_ROW5].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_MEASURE_R5, this);
#ifdef GRIPPER_8
	m_stcMeasure_R[eGRIPPER_ROW6].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_MEASURE_R6, this);
	m_stcMeasure_R[eGRIPPER_ROW7].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_MEASURE_R7, this);
	m_stcMeasure_R[eGRIPPER_ROW8].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_MEASURE_R8, this);
#endif

	m_stcStatus_L[eGRIPPER_ROW1].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_STATUS_L1, this);
	m_stcStatus_L[eGRIPPER_ROW2].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_STATUS_L2, this);
	m_stcStatus_L[eGRIPPER_ROW3].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_STATUS_L3, this);
//	m_stcStatus_L[eGRIPPER_ROW4].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_STATUS_L4, this);
	//m_stcStatus_L[eGRIPPER_ROW5].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_STATUS_L5, this);
#ifdef GRIPPER_8
	m_stcStatus_L[eGRIPPER_ROW6].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_STATUS_L6, this);
	m_stcStatus_L[eGRIPPER_ROW7].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_STATUS_L7, this);
	m_stcStatus_L[eGRIPPER_ROW8].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_STATUS_L8, this);
#endif

	m_stcStatus_R[eGRIPPER_ROW1].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_STATUS_R1, this);
	m_stcStatus_R[eGRIPPER_ROW2].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_STATUS_R2, this);
	m_stcStatus_R[eGRIPPER_ROW3].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_STATUS_R3, this);
	//m_stcStatus_R[eGRIPPER_ROW4].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_STATUS_R4, this);
	//m_stcStatus_R[eGRIPPER_ROW5].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_STATUS_R5, this);
#ifdef GRIPPER_8
	m_stcStatus_R[eGRIPPER_ROW6].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_STATUS_R6, this);
	m_stcStatus_R[eGRIPPER_ROW7].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_STATUS_R7, this);
	m_stcStatus_R[eGRIPPER_ROW8].SubclassDlgItem(IDC_STATIC_MANUAL_SUB_STRETCH_STATUS_R8, this);
#endif

	m_chkLeft_ClampOn[eGRIPPER_ROW1].SubclassDlgItem(IDC_CHECK_ON_L1, this);
	m_chkLeft_ClampOn[eGRIPPER_ROW2].SubclassDlgItem(IDC_CHECK_ON_L2, this);
	m_chkLeft_ClampOn[eGRIPPER_ROW3].SubclassDlgItem(IDC_CHECK_ON_L3, this);

	m_chkRight_ClampOn[eGRIPPER_ROW1].SubclassDlgItem(IDC_CHECK_ON_R1, this);
	m_chkRight_ClampOn[eGRIPPER_ROW2].SubclassDlgItem(IDC_CHECK_ON_R2, this);
	m_chkRight_ClampOn[eGRIPPER_ROW3].SubclassDlgItem(IDC_CHECK_ON_R3, this);

	m_chkLeft_ClampOff[eGRIPPER_ROW1].SubclassDlgItem(IDC_CHECK_OFF_L1, this);
	m_chkLeft_ClampOff[eGRIPPER_ROW2].SubclassDlgItem(IDC_CHECK_OFF_L2, this);
	m_chkLeft_ClampOff[eGRIPPER_ROW3].SubclassDlgItem(IDC_CHECK_OFF_L3, this);

	m_chkRight_ClampOff[eGRIPPER_ROW1].SubclassDlgItem(IDC_CHECK_OFF_R1, this);
	m_chkRight_ClampOff[eGRIPPER_ROW2].SubclassDlgItem(IDC_CHECK_OFF_R2, this);
	m_chkRight_ClampOff[eGRIPPER_ROW3].SubclassDlgItem(IDC_CHECK_OFF_R3, this);
	

	Str.Format(_T("1.0"));
	for (int i = 0; i < eGRIPPER_ROW_MAX; i++)
	{
		m_stcSet_L[i].SetWindowText(Str);
		m_stcSet_R[i].SetWindowText(Str);
		m_stcMeasure_L[i].SetWindowText(Str);
		m_stcMeasure_R[i].SetWindowText(Str);
		m_stcStatus_L[i].SetWindowText(_T("Idle"));
		m_stcStatus_R[i].SetWindowText(_T("Idle"));
	}
}
//--------------------------------------------------------
BOOL	CManual_Sub_Stretch_Manual::Is_Comp_Usable()
{
	return TRUE;
}
//--------------------------------------------------------
void	CManual_Sub_Stretch_Manual::InitPara()
{
	int k = 0;
	for (k = 0; k < _eMANUAL_WORK_INDEX_STRETCH_POS_MAX; k++)
	{
		m_nWork_State[k] = _eSTATE_NONE;
		m_stLamp_Work[k].SetBackgroundColor(LED_LAMP_OFF);

		m_bMotionDone[k] = FALSE;
		m_bPrevStatus_InPos[k] = FALSE;
	}
}
//--------------------------------------------------------
void	CManual_Sub_Stretch_Manual::CheckChangeData()
{
	
}

void CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualActiveWaitPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;

	if (Devs::m_ClampMotion.Is_ClampOff_Active() != TRUE)
	{
		AfxMessageBox(_T("Check Active Clamp Off !!!"));
		return;
	}

	int nIndex = _eMANUAL_WORK_INDEX_STRETCH_ACTIVE_WAIT_POS;

	Str.Format(_T("Stretch Move Active Wait Pos ?"));
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	for (int i = 0; i < eGRIPPER_ROW_MAX; i++)
	{
		if (CModelData::m_StretchPara.Info.bStretchUse[i] == TRUE)
		{
			Devs::m_StretchMotion.Stretch_WaitPos((enum_eGRIPPER_ROW)i);
		}
	}

	m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
	m_dMotion_Strt_Tick[nIndex] = GetTickCount();
	m_nWork_State[nIndex] = _eSTATE_START;
}


void CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualActiveFwdPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;
	int nIndex = _eMANUAL_WORK_INDEX_STRETCH_ACTIVE_FWD_POS;

	Str.Format(_T("Stretch Move Active Fwd Pos ?"));
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	for (int i = 0; i < eGRIPPER_ROW_MAX; i++)
	{
		if (CModelData::m_StretchPara.Info.bStretchUse[i] == TRUE)
		{
			Devs::m_StretchMotion.Stretch_FwdPos((enum_eGRIPPER_ROW)i);
		}
	}

	m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
	m_dMotion_Strt_Tick[nIndex] = GetTickCount();
	m_nWork_State[nIndex] = _eSTATE_START;
}


void CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualActiveBwdPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;

#pragma region //Interlock
	if (Devs::m_ClampMotion.Is_ClampOff_Active() != TRUE)
	{
		AfxMessageBox(_T("Check Acitve Clamp Off !!!"));
		return;
	}
#pragma endregion

	int nIndex = _eMANUAL_WORK_INDEX_STRETCH_ACTIVE_BWD_POS;

	Str.Format(_T("Stretch Move Active Bwd Pos ?"));
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	for (int i = 0; i < eGRIPPER_ROW_MAX; i++)
	{
		if (CModelData::m_StretchPara.Info.bStretchUse[i] == TRUE)
		{
			Devs::m_StretchMotion.Stretch_BwdPos((enum_eGRIPPER_ROW)i);
		}
	}

	m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
	m_dMotion_Strt_Tick[nIndex] = GetTickCount();
	m_nWork_State[nIndex] = _eSTATE_START;
}

void CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualAllWaitPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;

	if (Devs::m_ClampMotion.Is_ClampOff_All() != TRUE)
	{
		AfxMessageBox(_T("Check All Clamp Off !!!"));
		return;
	}

	int nIndex = _eMANUAL_WORK_INDEX_STRETCH_ALL_WAIT_POS;

	Str.Format(_T("Stretch Move All Wait Pos ?"));
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	for (int i = 0; i < eGRIPPER_ROW_MAX; i++)
	{
		Devs::m_StretchMotion.Stretch_WaitPos((enum_eGRIPPER_ROW)i);
	}

	m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
	m_dMotion_Strt_Tick[nIndex] = GetTickCount();
	m_nWork_State[nIndex] = _eSTATE_START;
}

void CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualAllFwdPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;
	int nIndex = _eMANUAL_WORK_INDEX_STRETCH_ALL_FWD_POS;

	Str.Format(_T("Stretch Move All Fwd Pos ?"));
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	for (int i = 0; i < eGRIPPER_ROW_MAX; i++)
	{
		Devs::m_StretchMotion.Stretch_FwdPos((enum_eGRIPPER_ROW)i);
	}

	m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
	m_dMotion_Strt_Tick[nIndex] = GetTickCount();
	m_nWork_State[nIndex] = _eSTATE_START;
}


void CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualAllBwdPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;

	if (Devs::m_ClampMotion.Is_ClampOff_All() != TRUE)
	{
		AfxMessageBox(_T("Check All Clamp Off !!!"));
		return;
	}

	int nIndex = _eMANUAL_WORK_INDEX_STRETCH_ALL_BWD_POS;

	Str.Format(_T("Stretch Move All Bwd Pos ?"));
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	for (int i = 0; i < eGRIPPER_ROW_MAX; i++)
	{
		Devs::m_StretchMotion.Stretch_BwdPos((enum_eGRIPPER_ROW)i);
	}

	m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
	m_dMotion_Strt_Tick[nIndex] = GetTickCount();
	m_nWork_State[nIndex] = _eSTATE_START;
}


void CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualStretchStart()
{
	if (IDOK != AfxMessageBox(_T("Stretch Start ?"), MB_OKCANCEL)) return;

	double dStretchValue[MAX_STEP][eGRIPPER_ROW_MAX];
	memset(dStretchValue, 0x0, sizeof(dStretchValue));
	memcpy(dStretchValue, CModelData::m_StretchPara.Info.dStretchNewton, sizeof(CModelData::m_StretchPara.Info.dStretchNewton)); //??

	Devs::m_StretchMotion.StretchSetStepValue(CModelData::m_StretchPara.Info.nStepCount, dStretchValue);
	Total_Msg(_T("StretchSetStepValue"));
	(100);
	Devs::m_StretchMotion.SendStretchSetPara();
	Total_Msg(_T("SendStretchSetPara"));
	(100);

	Devs::m_StretchMotion.StretchStart();
	Total_Msg(_T("Stretch Start"));
}


void CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualStretchStop()
{
	Devs::m_StretchMotion.StretchStop();

	Total_Msg(_T("Stretch Stop"));
}


void CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualStretchForceZero()
{
	if (IDOK != AfxMessageBox(_T("Stretch Force SetZero Start ?"), MB_OKCANCEL)) return;
	for (int i = 0; i < MAX_STRETCH_SIZE; i++)
	{
		if (CModelData::m_StretchPara.Info.bStretchUse[i])
		{
			Devs::MotionIf.StretchForceZero(i);
			Sleep(200);
		}
	}

	Total_Msg(_T("Stretch Force Zero"));
}


void CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualReleaseStart()
{
	if (IDOK != AfxMessageBox(_T("Release Start ?"), MB_OKCANCEL)) return;


	double dTargetForce[MAX_STEP][MAX_STRETCH_SIZE];
	memset(dTargetForce, 0x0, sizeof(dTargetForce));

	int nStepCnt = 1;
	double dForceVal = 1.0;

	for (int i = 0; i < MAX_STRETCH_SIZE; i++)
	{
		if (CModelData::m_StretchPara.Info.bStretchUse[i])
		{
			dTargetForce[0][i] = dForceVal;
		}
	}

	Devs::m_StretchMotion.SetReleaseStepValue();
	Total_Msg(_T("SetReleaseStepValue"));
	(100);
	Devs::m_StretchMotion.SendReleaseSetPara();
	Total_Msg(_T("SendReleaseSetPara"));
	(100);

	Devs::m_StretchMotion.StretchStart(TRUE);
	Total_Msg(_T("Stretch Start"));
}


void CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualClampOnL1()
{
	// TODO: Add your control notification handler code here
	//CVisionAgentDlg* pDlg = (CVisionAgentDlg*)theApp.m_pMainWnd;
	
	SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_L1_OPEN_SOL), FALSE);
	Sleep(100);
	SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_L1_CLOSE_SOL), TRUE);
	Sleep(100);
	return;
}


void CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualClampOnL2()
{
	// TODO: Add your control notification handler code here
	SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_L2_OPEN_SOL), FALSE);
	Sleep(100);
	SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_L2_CLOSE_SOL), TRUE);
	Sleep(100);
	return;
}


void CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualClampOnL3()
{
	// TODO: Add your control notification handler code here
	
	SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_L3_OPEN_SOL), FALSE);
	Sleep(100);
	SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_L3_CLOSE_SOL), TRUE);
	Sleep(100);
	return;
}


void CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualClampOnR1()
{
	// TODO: Add your control notification handler code here
	

	SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_R1_OPEN_SOL), FALSE);
	Sleep(100);
	SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_R1_CLOSE_SOL), TRUE);
	Sleep(100);
	return;
}


void CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualClampOnR2()
{
	// TODO: Add your control notification handler code here
	
	SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_R2_OPEN_SOL), FALSE);
	Sleep(100);
	SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_R2_CLOSE_SOL), TRUE);
	Sleep(100);
	return;
}


void CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualClampOnR3()
{
	// TODO: Add your control notification handler code here
	
	SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_R3_OPEN_SOL), FALSE);
	Sleep(100);
	SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_R3_CLOSE_SOL), TRUE);
	Sleep(100);
	return;
}


void CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualClampOffL1()
{
	// TODO: Add your control notification handler code here
	
	SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_L1_OPEN_SOL), TRUE);
	Sleep(100);
	SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_L1_CLOSE_SOL), FALSE);
	Sleep(100);
	return;
}


void CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualClampOffL2()
{
	// TODO: Add your control notification handler code here
	
	SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_L2_OPEN_SOL), TRUE);
	Sleep(100);
	SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_L2_CLOSE_SOL), FALSE);
	Sleep(100);
}


void CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualClampOffL3()
{
	// TODO: Add your control notification handler code here
	
	SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_L3_OPEN_SOL), TRUE);
	Sleep(100);
	SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_L3_CLOSE_SOL), FALSE);
	Sleep(100);
}


void CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualClampOffR1()
{
	// TODO: Add your control notification handler code here
	
	SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_R1_OPEN_SOL), TRUE);
	Sleep(100);
	SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_R1_CLOSE_SOL), FALSE);
	Sleep(100);
}


void CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualClampOffR2()
{
	// TODO: Add your control notification handler code here
	
	SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_R2_OPEN_SOL), TRUE);
	Sleep(100);
	SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_R2_CLOSE_SOL), FALSE);
	Sleep(100);
}


void CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualClampOffR3()
{
	// TODO: Add your control notification handler code here
	SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_R3_OPEN_SOL), TRUE);
	Sleep(100);
	SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_R3_CLOSE_SOL), FALSE);
	Sleep(100);
}

BOOL CManual_Sub_Stretch_Manual::SetDOutputBitValue(enum_Do eBit, int nValue)
{
#ifndef SIM_MODE
	int nBit = -1;

#if 0
	if (!m_Safety.AxisAllDoSafetyCheck(eBit, nValue))
	{
		return FALSE;
	}
#endif

	SharedInfo::GetActualIoNumByEnumDo(eBit, &nBit);
	if (nBit == -1)
		return FALSE;


	Devs::MotionIf.DOutputSetBitValue(nBit, nValue);
#endif
	return TRUE;
}

void CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualClampOnAll()
{
	// TODO: Add your control notification handler code here

	if (IDOK != AfxMessageBox(_T("Do you want to execute ?"), MB_OKCANCEL)) return;

	int nStatus;

	//Left Clamp_1
	nStatus = m_chkLeft_ClampOn[eGRIPPER_ROW1].GetCheck();
	if (nStatus == 1)
	{
		SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_L1_OPEN_SOL), FALSE);
		Sleep(100);
		SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_L1_CLOSE_SOL), TRUE);
		Sleep(100);
	}
	//else
	//{
	//	SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_L1_OPEN_SOL), TRUE);
	//	Sleep(100);
	//	SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_L1_CLOSE_SOL), FALSE);
	//	Sleep(100);
	//}

	//Left Clamp_2
	nStatus = m_chkLeft_ClampOn[eGRIPPER_ROW2].GetCheck();
	if (nStatus == 1)
	{
		SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_L2_OPEN_SOL), FALSE);
		Sleep(100);
		SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_L2_CLOSE_SOL), TRUE);
		Sleep(100);
	}
	//else
	//{
	//	SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_L2_OPEN_SOL), TRUE);
	//	Sleep(100);
	//	SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_L2_CLOSE_SOL), FALSE);
	//	Sleep(100);
	//}

	//Left Clamp_3
	nStatus = m_chkLeft_ClampOn[eGRIPPER_ROW3].GetCheck();
	if (nStatus == 1)
	{
		SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_L3_OPEN_SOL), FALSE);
		Sleep(100);
		SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_L3_CLOSE_SOL), TRUE);
		Sleep(100);
	}
	//else
	//{
	//	SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_L3_OPEN_SOL), TRUE);
	//	Sleep(100);
	//	SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_L3_CLOSE_SOL), FALSE);
	//	Sleep(100);
	//}



	//Right Clamp_1
	nStatus = m_chkRight_ClampOn[eGRIPPER_ROW1].GetCheck();
	if (nStatus == 1)
	{
		SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_R1_OPEN_SOL), FALSE);
		Sleep(100);
		SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_R1_CLOSE_SOL), TRUE);
		Sleep(100);
	}
	//else
	//{
	//	SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_R1_OPEN_SOL), TRUE);
	//	Sleep(100);
	//	SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_R1_CLOSE_SOL), FALSE);
	//	Sleep(100);
	//}

	//Right Clamp_2
	nStatus = m_chkRight_ClampOn[eGRIPPER_ROW2].GetCheck();
	if (nStatus == 1)
	{
		SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_R2_OPEN_SOL), FALSE);
		Sleep(100);
		SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_R2_CLOSE_SOL), TRUE);
		Sleep(100);
	}
	//else
	//{
	//	SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_R2_OPEN_SOL), TRUE);
	//	Sleep(100);
	//	SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_R2_CLOSE_SOL), FALSE);
	//	Sleep(100);
	//}

	//Right Clamp_3
	nStatus = m_chkRight_ClampOn[eGRIPPER_ROW3].GetCheck();
	if (nStatus == 1)
	{
		SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_R3_OPEN_SOL), FALSE);
		Sleep(100);
		SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_R3_CLOSE_SOL), TRUE);
		Sleep(100);
	}
	//else
	//{
	//	SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_R3_OPEN_SOL), TRUE);
	//	Sleep(100);
	//	SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_R3_CLOSE_SOL), FALSE);
	//	Sleep(100);
	//}		
}


void CManual_Sub_Stretch_Manual::OnBnClickedButtonManualSubGripperManualClampOffAll()
{
	// TODO: Add your control notification handler code here

	if (IDOK != AfxMessageBox(_T("Do you want to execute ?"), MB_OKCANCEL)) return;

	int nStatus;

	//Left Clamp_1
	nStatus = m_chkLeft_ClampOn[eGRIPPER_ROW1].GetCheck();	
	if (nStatus == 1)
	{
		SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_L1_OPEN_SOL), TRUE);
		Sleep(100);
		SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_L1_CLOSE_SOL), FALSE);
		Sleep(100);
	}

	//Left Clamp_2
	nStatus = m_chkLeft_ClampOn[eGRIPPER_ROW2].GetCheck();
	if (nStatus == 1)
	{
		SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_L2_OPEN_SOL), TRUE);
		Sleep(100);
		SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_L2_CLOSE_SOL), FALSE);
		Sleep(100);
	}

	//Left Clamp_3
	nStatus = m_chkLeft_ClampOn[eGRIPPER_ROW3].GetCheck();
	if (nStatus == 1)
	{
		SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_L3_OPEN_SOL), TRUE);
		Sleep(100);
		SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_L3_CLOSE_SOL), FALSE);
		Sleep(100);
	}



	//Right Clamp_1
	nStatus = m_chkRight_ClampOn[eGRIPPER_ROW1].GetCheck();
	if (nStatus == 1)
	{
		SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_R1_OPEN_SOL), TRUE);
		Sleep(100);
		SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_R1_CLOSE_SOL), FALSE);
		Sleep(100);
	}

	//Right Clamp_2
	nStatus = m_chkRight_ClampOn[eGRIPPER_ROW2].GetCheck();
	if (nStatus == 1)
	{
		SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_R2_OPEN_SOL), TRUE);
		Sleep(100);
		SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_R2_CLOSE_SOL), FALSE);
		Sleep(100);
	}

	//Right Clamp_3
	nStatus = m_chkRight_ClampOn[eGRIPPER_ROW3].GetCheck();
	if (nStatus == 1)
	{
		SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_R3_OPEN_SOL), TRUE);
		Sleep(100);
		SetDOutputBitValue((enum_Do)(_DOUT_GRIPPER_R3_CLOSE_SOL), FALSE);
		Sleep(100);
	}
}
