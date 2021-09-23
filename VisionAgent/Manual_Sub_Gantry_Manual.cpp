// Manual_Sub_Gantry_Manual.cpp: 구현 파일
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentDlg.h"
#include "Manual_Sub_Gantry_Manual.h"
#include "afxdialogex.h"


// CManual_Sub_Gantry_Manual 대화 상자

IMPLEMENT_DYNAMIC(CManual_Sub_Gantry_Manual, CDialogEx)

CManual_Sub_Gantry_Manual::CManual_Sub_Gantry_Manual(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_MANUAL_SUB_GANTRY_MANUAL, pParent)
{
	Create(IDD_DLG_MANUAL_SUB_GANTRY_MANUAL, pParent);
}

CManual_Sub_Gantry_Manual::~CManual_Sub_Gantry_Manual()
{
}

void CManual_Sub_Gantry_Manual::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CManual_Sub_Gantry_Manual, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CManual_Sub_Gantry_Manual 메시지 처리기
BOOL CManual_Sub_Gantry_Manual::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitCtrl();

	return TRUE;
}

void	CManual_Sub_Gantry_Manual::InitCtrl()
{
	m_stLamp_Work[_eMANUAL_WORK_INDEX_GANTRY_X_WAIT_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_GANTRY_MANUAL_GANTRY_X_WAIT_POS, this);

	for (int k = 0; k < _eMANUAL_WORK_INDEX_GANTRY_MAX; k++)
	{
		m_stLamp_Work[k].SetParaChangeColor(BK_GND);
		m_stLamp_Work[k].SetParaOriginColor(STATEBAR_NAME_BK_RGB);
		m_stLamp_Work[k].SetBackgroundColor(STATEBAR_NAME_BK_RGB);
		m_stLamp_Work[k].SetTextColor(LED_LAMP_OFF);
		m_stLamp_Work[k].SetBackgroundColor(BTN_LAMP_OFF);
	}
}

void	CManual_Sub_Gantry_Manual::InitPara()
{
	for (int k = 0; k < _eMANUAL_WORK_INDEX_GANTRY_MAX; k++)
	{
		m_nWork_State[k] = _eSTATE_NONE;
		m_stLamp_Work[k].SetBackgroundColor(BTN_LAMP_OFF);

		m_bMotionDone[k] = FALSE;
		m_bPrevStatus_InPos[k] = FALSE;
	}
}


void CManual_Sub_Gantry_Manual::OnShowWindow(BOOL bShow, UINT nStatus)
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
void CManual_Sub_Gantry_Manual::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (Is_Comp_Usable() == FALSE)	return;
}
//--------------------------------------------------------
void CManual_Sub_Gantry_Manual::OnTimer(UINT_PTR nIDEvent)
{
	double dEnd_Tick, dWait_Tick;
	int k = 0;

	//for (k = 0; k < _eMANUAL_WORK_INDEX_GANTRY_MAX; k++)
	//{
	//	if (m_nWork_State[k] == _eSTATE_START)
	//	{
	//		dEnd_Tick = GetTickCount();
	//		dWait_Tick = (dEnd_Tick - m_dMotion_Strt_Tick[k]) / 1000;
	//		if (dWait_Tick > 0.5)
	//		{
	//			m_dMotion_Strt_Tick[k] = GetTickCount();
	//			m_bWork_Lamp_State[k] = !m_bWork_Lamp_State[k];
	//		}
	//		if (m_bWork_Lamp_State[k])
	//			m_stLamp_Work[k].SetBackgroundColor(BTN_LAMP_ON);
	//		else
	//			m_stLamp_Work[k].SetBackgroundColor(BTN_LAMP_OFF);
	//	}
	//	if (m_nWork_State[k] == _eSTATE_COMPLETE)
	//	{
	//		m_stLamp_Work[k].SetBackgroundColor(BTN_LAMP_ON);
	//		m_nWork_State[k] = _eSTATE_NONE;
	//	}
	//}

#pragma region //Motion Done
	//Gantry X
	m_bMotionDone[_eMANUAL_WORK_INDEX_GANTRY_X_WAIT_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_GANTRY_X, CManualData::m_ManualDataGantry.Info.m_dGantry_X_Wait_Pos);

	for (k = 0; k < _eMANUAL_WORK_INDEX_GANTRY_MAX; k++)
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
//--------------------------------------------------------
BOOL	CManual_Sub_Gantry_Manual::Is_Comp_Usable()
{
	int i = 0;
	for (i = 0; i < _eMANUAL_WORK_INDEX_GANTRY_MAX; i++)
	{
		if (m_stLamp_Work[i].GetSafeHwnd() == NULL)
			return FALSE;
	}

	return TRUE;
}









