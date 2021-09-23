// Manual_Sub_Pitch_Manual.cpp: 구현 파일
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "Manual_Sub_Pitch_Manual.h"
#include "afxdialogex.h"


// CManual_Sub_Pitch_Manual 대화 상자

IMPLEMENT_DYNAMIC(CManual_Sub_Pitch_Manual, CDialogEx)

CManual_Sub_Pitch_Manual::CManual_Sub_Pitch_Manual(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_MANUAL_SUB_PITCH_MANUAL, pParent)
{
	Create(IDD_DLG_MANUAL_SUB_PITCH_MANUAL, pParent);
}

CManual_Sub_Pitch_Manual::~CManual_Sub_Pitch_Manual()
{
}

void CManual_Sub_Pitch_Manual::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CManual_Sub_Pitch_Manual, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_PITCH_MANUAL_WORK_POS, &CManual_Sub_Pitch_Manual::OnBnClickedButtonManualSubPitchManualWorkPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_PITCH_MANUAL_WAIT_POS, &CManual_Sub_Pitch_Manual::OnBnClickedButtonManualSubPitchManualWaitPos)
END_MESSAGE_MAP()


// CManual_Sub_Pitch_Manual 메시지 처리기

BOOL CManual_Sub_Pitch_Manual::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitCtrl();

	return TRUE;
}
//--------------------------------------------------------
void CManual_Sub_Pitch_Manual::OnShowWindow(BOOL bShow, UINT nStatus)
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
void CManual_Sub_Pitch_Manual::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (Is_Comp_Usable() == FALSE)	return;
}
//--------------------------------------------------------
void CManual_Sub_Pitch_Manual::OnTimer(UINT_PTR nIDEvent)
{
	double dEnd_Tick, dWait_Tick;
	int i = 0, k = 0;
	for (k = 0; k < _eMANUAL_INDEX_PITCH_POS_MAX; k++)
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
	BOOL bWait = TRUE, bWork = TRUE;
	int nWingIndex = 0;
	for (i = 0; i < eGRIPPER_ROW_MAX; i++)
	{
		if (Devs::m_BaseMotion.IsAxisMoveDone((enum_Axis)(AXIS_GRIPPER_PITCH_L1 + i), CManualData::m_ManualDataPitch.Info.m_dPitchLeft_WaitPos[i + 1]) == FALSE ||
			Devs::m_BaseMotion.IsAxisMoveDone((enum_Axis)(AXIS_GRIPPER_PITCH_R1 + i), CManualData::m_ManualDataPitch.Info.m_dPitchRight_WaitPos[i + 1]) == FALSE)
		{
			bWait = FALSE;
		}
		
		if (CModelData::m_StretchPara.Info.bStretchUse[i] == TRUE)
		{
			dWorkPos_L[i] = CModelData::m_MaterialPara.Info.dStickWingCenterYOffset[nWingIndex];
			dWorkPos_R[i] = CModelData::m_MaterialPara.Info.dStickWingCenterYOffset[nWingIndex];
			if (Devs::m_PitchMotion.IsPitchPosMove((enum_Axis)(AXIS_GRIPPER_PITCH_L1 + i), dWorkPos_L[i]) == FALSE ||
				Devs::m_PitchMotion.IsPitchPosMove((enum_Axis)(AXIS_GRIPPER_PITCH_R1 + i), dWorkPos_R[i]) == FALSE)
			{
				bWork = FALSE;
				break;
			}
			nWingIndex++;
		}
	}
	m_bMotionDone[_eMANUAL_INDEX_PITCH_WAIT_POS] = bWait;
	m_bMotionDone[_eMANUAL_INDEX_PITCH_WORK_POS] = bWork;
	for (k = 0; k < _eMANUAL_INDEX_PITCH_POS_MAX; k++)
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

	CDialogEx::OnTimer(nIDEvent);
}

void	CManual_Sub_Pitch_Manual::InitCtrl()
{
	m_stLamp_Work[_eMANUAL_INDEX_PITCH_WAIT_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_PITCH_MANUAL_WAIT_POS, this);
	m_stLamp_Work[_eMANUAL_INDEX_PITCH_WORK_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_PITCH_MANUAL_WORK_POS, this);

	for (int k = 0; k < _eMANUAL_INDEX_PITCH_POS_MAX; k++)
	{
		m_stLamp_Work[k].SetParaChangeColor(BK_GND);
		m_stLamp_Work[k].SetParaOriginColor(STATEBAR_NAME_BK_RGB);
		m_stLamp_Work[k].SetBackgroundColor(STATEBAR_NAME_BK_RGB);
		m_stLamp_Work[k].SetTextColor(LED_LAMP_OFF);
		m_stLamp_Work[k].SetBackgroundColor(LED_LAMP_OFF);
	}
}
//--------------------------------------------------------
BOOL	CManual_Sub_Pitch_Manual::Is_Comp_Usable()
{
	return TRUE;
}
//--------------------------------------------------------
void	CManual_Sub_Pitch_Manual::InitPara()
{
	
}
//--------------------------------------------------------
void	CManual_Sub_Pitch_Manual::CheckChangeData()
{
	
}


void CManual_Sub_Pitch_Manual::OnBnClickedButtonManualSubPitchManualWorkPos()
{
	CString Str = _T("");

#pragma region //Interlock
	for (int i = 0; i < eGRIPPER_ROW_MAX; i++)
	{
		if (SharedInfo::GetServoOnStatus((enum_Axis)(AXIS_GRIPPER_PITCH_L1 + i)) == FALSE)
		{
			Str.Format(_T("Check Pitch L%d Servo On !!!"), i + 1);
			AfxMessageBox(Str);
			return;
		}
		if (SharedInfo::GetServoOnStatus((enum_Axis)(AXIS_GRIPPER_PITCH_R1 + i)) == FALSE)
		{
			Str.Format(_T("Check Pitch R%d Servo On !!!"), i + 1);
			AfxMessageBox(Str);
			return;
		}

		if (SharedInfo::GetHomeStatus((enum_Axis)(AXIS_GRIPPER_PITCH_L1 + i)) == FALSE)
		{
			Str.Format(_T("Check Pitch L%d Home Status !!!"), i + 1);
			AfxMessageBox(Str);
			return;
		}
		if (SharedInfo::GetHomeStatus((enum_Axis)(AXIS_GRIPPER_PITCH_R1 + i)) == FALSE)
		{
			Str.Format(_T("Check Pitch R%d Home Status !!!"), i + 1);
			AfxMessageBox(Str);
			return;
		}
	}
#pragma endregion

	Devs::m_PitchWorkPosMoveFlow.Start(Devs::m_PitchWorkPosMoveFlow._ePITCH_WORK_POS_MOVE_FLOW_START);
}


void CManual_Sub_Pitch_Manual::OnBnClickedButtonManualSubPitchManualWaitPos()
{
	CString Str = _T("");

#pragma region //Interlock
	for (int i = 0; i < eGRIPPER_ROW_MAX; i++)
	{
		if (SharedInfo::GetServoOnStatus((enum_Axis)(AXIS_GRIPPER_PITCH_L1 + i)) == FALSE)
		{
			Str.Format(_T("Check Pitch L%d Servo On !!!"), i + 1);
			AfxMessageBox(Str);
			return;
		}
		if (SharedInfo::GetServoOnStatus((enum_Axis)(AXIS_GRIPPER_PITCH_R1 + i)) == FALSE)
		{
			Str.Format(_T("Check Pitch R%d Servo On !!!"), i + 1);
			AfxMessageBox(Str);
			return;
		}

		if (SharedInfo::GetHomeStatus((enum_Axis)(AXIS_GRIPPER_PITCH_L1 + i)) == FALSE)
		{
			Str.Format(_T("Check Pitch L%d Home Status !!!"), i + 1);
			AfxMessageBox(Str);
			return;
		}
		if (SharedInfo::GetHomeStatus((enum_Axis)(AXIS_GRIPPER_PITCH_R1 + i)) == FALSE)
		{
			Str.Format(_T("Check Pitch R%d Home Status !!!"), i + 1);
			AfxMessageBox(Str);
			return;
		}
	}
#pragma endregion

	Str.Format(_T("Pitch All Wait Pos Move ?"));
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	Devs::m_PitchMotion.Pitch_WaitPos_All();
}
