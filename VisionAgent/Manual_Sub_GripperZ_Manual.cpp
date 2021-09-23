// Manual_Sub_GripperZ_Manual.cpp : implementation file
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "Manual_Sub_GripperZ_Manual.h"
#include "afxdialogex.h"


// CManual_Sub_GripperZ_Manual dialog

IMPLEMENT_DYNAMIC(CManual_Sub_GripperZ_Manual, CDialogEx)

CManual_Sub_GripperZ_Manual::CManual_Sub_GripperZ_Manual(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_MANUAL_SUB_GRIPPER_Z_MANUAL, pParent)
{
	Create(IDD_DLG_MANUAL_SUB_GRIPPER_Z_MANUAL, pParent);
}

CManual_Sub_GripperZ_Manual::~CManual_Sub_GripperZ_Manual()
{
}

void CManual_Sub_GripperZ_Manual::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CManual_Sub_GripperZ_Manual, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_Z_MANUAL_WAIT_POS, &CManual_Sub_GripperZ_Manual::OnBnClickedButtonManualSubGripperZManualWaitPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_Z_MANUAL_LOADING_POS, &CManual_Sub_GripperZ_Manual::OnBnClickedButtonManualSubGripperZManualLoadingPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_Z_MANUAL_CLAMP_POS, &CManual_Sub_GripperZ_Manual::OnBnClickedButtonManualSubGripperZManualClampPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_Z_MANUAL_TENSION_POS, &CManual_Sub_GripperZ_Manual::OnBnClickedButtonManualSubGripperZManualTensionPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_Z_MANUAL_UNCLAMP_POS, &CManual_Sub_GripperZ_Manual::OnBnClickedButtonManualSubGripperZManualUnclampPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_Z_MANUAL_WAIT_POS2, &CManual_Sub_GripperZ_Manual::OnBnClickedButtonManualSubGripperZManualWaitPos2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_Z_MANUAL_LOADING_POS2, &CManual_Sub_GripperZ_Manual::OnBnClickedButtonManualSubGripperZManualLoadingPos2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_Z_MANUAL_CLAMP_POS3, &CManual_Sub_GripperZ_Manual::OnBnClickedButtonManualSubGripperZManualClampPos3)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_Z_MANUAL_TENSION_POS2, &CManual_Sub_GripperZ_Manual::OnBnClickedButtonManualSubGripperZManualTensionPos2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_GRIPPER_Z_MANUAL_UNCLAMP_POS2, &CManual_Sub_GripperZ_Manual::OnBnClickedButtonManualSubGripperZManualUnclampPos2)
END_MESSAGE_MAP()


// CManual_Sub_GripperZ_Manual message handlers

BOOL CManual_Sub_GripperZ_Manual::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitCtrl();

	return TRUE;
}

void CManual_Sub_GripperZ_Manual::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (Is_Comp_Usable() == FALSE)	return;
}

void	CManual_Sub_GripperZ_Manual::InitCtrl()
{
	m_stLamp_Work[_eMANUAL_WORK_INDEX_GRIPPER_Z_WAIT_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_GRIPPER_Z_MANUAL_WAIT_POS, this);
	m_stLamp_Work[_eMANUAL_WORK_INDEX_GRIPPER_Z_LOADING_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_GRIPPER_Z_MANUAL_LOADING_POS, this);
	m_stLamp_Work[_eMANUAL_WORK_INDEX_GRIPPER_Z_CLAMP_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_GRIPPER_Z_MANUAL_CLAMP_POS, this);
	m_stLamp_Work[_eMANUAL_WORK_INDEX_GRIPPER_Z_TENSTION_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_GRIPPER_Z_MANUAL_TENSION_POS, this);
	m_stLamp_Work[_eMANUAL_WORK_INDEX_GRIPPER_Z_UNCLAMP_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_GRIPPER_Z_MANUAL_UNCLAMP_POS, this);
	
	m_stLamp_Work[_eMANUAL_WORK_INDEX_GRIPPER_RIGHT_Z_WAIT_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_GRIPPER_Z_MANUAL_WAIT_POS2, this);
	m_stLamp_Work[_eMANUAL_WORK_INDEX_GRIPPER_RIGHT_Z_LOADING_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_GRIPPER_Z_MANUAL_LOADING_POS2, this);
	m_stLamp_Work[_eMANUAL_WORK_INDEX_GRIPPER_RIGHT_Z_CLAMP_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_GRIPPER_Z_MANUAL_CLAMP_POS2, this);
	m_stLamp_Work[_eMANUAL_WORK_INDEX_GRIPPER_RIGHT_Z_TENSTION_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_GRIPPER_Z_MANUAL_TENSION_POS2, this);
	m_stLamp_Work[_eMANUAL_WORK_INDEX_GRIPPER_RIGHT_Z_UNCLAMP_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_GRIPPER_Z_MANUAL_UNCLAMP_POS2, this);

	for (int k = 0; k < _eMANUAL_WORK_INDEX_GRIPPER_Z_MAX; k++)
	{
		m_stLamp_Work[k].SetParaChangeColor(BK_GND);
		m_stLamp_Work[k].SetParaOriginColor(STATEBAR_NAME_BK_RGB);
		m_stLamp_Work[k].SetBackgroundColor(STATEBAR_NAME_BK_RGB);
		m_stLamp_Work[k].SetTextColor(LED_LAMP_OFF);
		m_stLamp_Work[k].SetBackgroundColor(LED_LAMP_OFF);
	}
}

BOOL	CManual_Sub_GripperZ_Manual::Is_Comp_Usable()
{
	return TRUE;
}
//--------------------------------------------------------
void	CManual_Sub_GripperZ_Manual::InitPara()
{
	int k = 0;
	for (k = 0; k < _eMANUAL_WORK_INDEX_GRIPPER_Z_MAX; k++)
	{
		m_nWork_State[k] = _eSTATE_NONE;
		m_stLamp_Work[k].SetBackgroundColor(LED_LAMP_OFF);

		m_bMotionDone[k] = FALSE;
		m_bPrevStatus_InPos[k] = FALSE;
	}
}

void CManual_Sub_GripperZ_Manual::OnShowWindow(BOOL bShow, UINT nStatus)
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

void CManual_Sub_GripperZ_Manual::OnTimer(UINT_PTR nIDEvent)
{
	double dEnd_Tick, dWait_Tick;
	int k = 0;

	for (k = 0; k < _eMANUAL_WORK_INDEX_GRIPPER_Z_MAX; k++)
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
	//Gripper Z
#ifndef GRIPPER_0
	m_bMotionDone[_eMANUAL_WORK_INDEX_GRIPPER_Z_WAIT_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_GRIPPER_ZL, CManualData::m_ManualDataGripperZ.Info.m_dGripperLeftZ_WaitPos);
	m_bMotionDone[_eMANUAL_WORK_INDEX_GRIPPER_Z_LOADING_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_GRIPPER_ZL, CManualData::m_ManualDataGripperZ.Info.m_dGripperLeftZ_LoadingPos);
	m_bMotionDone[_eMANUAL_WORK_INDEX_GRIPPER_Z_CLAMP_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_GRIPPER_ZL, CManualData::m_ManualDataGripperZ.Info.m_dGripperLeftZ_ClampPos);
	m_bMotionDone[_eMANUAL_WORK_INDEX_GRIPPER_Z_TENSTION_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_GRIPPER_ZL, CManualData::m_ManualDataGripperZ.Info.m_dGripperLeftZ_TensionPos);
	m_bMotionDone[_eMANUAL_WORK_INDEX_GRIPPER_Z_UNCLAMP_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_GRIPPER_ZL, CManualData::m_ManualDataGripperZ.Info.m_dGripperLeftZ_UnclampPos);
	
	m_bMotionDone[_eMANUAL_WORK_INDEX_GRIPPER_RIGHT_Z_WAIT_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_GRIPPER_ZR, CManualData::m_ManualDataGripperZ.Info.m_dGripperRightZ_WaitPos);
	m_bMotionDone[_eMANUAL_WORK_INDEX_GRIPPER_RIGHT_Z_LOADING_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_GRIPPER_ZR, CManualData::m_ManualDataGripperZ.Info.m_dGripperRightZ_LoadingPos);
	m_bMotionDone[_eMANUAL_WORK_INDEX_GRIPPER_RIGHT_Z_CLAMP_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_GRIPPER_ZR, CManualData::m_ManualDataGripperZ.Info.m_dGripperRightZ_ClampPos);
	m_bMotionDone[_eMANUAL_WORK_INDEX_GRIPPER_RIGHT_Z_TENSTION_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_GRIPPER_ZR, CManualData::m_ManualDataGripperZ.Info.m_dGripperRightZ_TensionPos);
	m_bMotionDone[_eMANUAL_WORK_INDEX_GRIPPER_RIGHT_Z_UNCLAMP_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_GRIPPER_ZR, CManualData::m_ManualDataGripperZ.Info.m_dGripperRightZ_UnclampPos);
#endif
	for (k = 0; k < _eMANUAL_WORK_INDEX_GRIPPER_Z_MAX; k++)
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
void	CManual_Sub_GripperZ_Manual::CheckChangeData()
{
	//UI에 기입한 내용을 SystemData 변수에 입력
}

void CManual_Sub_GripperZ_Manual::OnBnClickedButtonManualSubGripperZManualWaitPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;
	double dPos = CManualData::m_ManualDataGripperZ.Info.m_dGripperLeftZ_WaitPos;
	int nIndex = _eMANUAL_WORK_INDEX_GRIPPER_Z_WAIT_POS;

	Str.Format(_T("Gripper Z Move ? (Wait_Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_GripperZMotion.Move_GripperLeftZ_WaitPos();

	if (bRtn == TRUE)
	{
		m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;
	}
}


void CManual_Sub_GripperZ_Manual::OnBnClickedButtonManualSubGripperZManualUnclampPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;
	double dPos = CManualData::m_ManualDataGripperZ.Info.m_dGripperLeftZ_UnclampPos;
	int nIndex = _eMANUAL_WORK_INDEX_GRIPPER_Z_UNCLAMP_POS;

	Str.Format(_T("Gripper Z Move ? (Unclamp_Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_GripperZMotion.Move_GripperLeftZ_UnclampPos();

	if (bRtn == TRUE)
	{
		m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;
	}
}


void CManual_Sub_GripperZ_Manual::OnBnClickedButtonManualSubGripperZManualLoadingPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;
	double dPos = CManualData::m_ManualDataGripperZ.Info.m_dGripperLeftZ_LoadingPos;
	int nIndex = _eMANUAL_WORK_INDEX_GRIPPER_Z_LOADING_POS;

	Str.Format(_T("Gripper Z Move ? (Loading_Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_GripperZMotion.Move_GripperLeftZ_LoadingPos();

	if (bRtn == TRUE)
	{
		m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;
	}
}


void CManual_Sub_GripperZ_Manual::OnBnClickedButtonManualSubGripperZManualClampPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;
	double dPos = CManualData::m_ManualDataGripperZ.Info.m_dGripperLeftZ_ClampPos;
	int nIndex = _eMANUAL_WORK_INDEX_GRIPPER_Z_CLAMP_POS;

	Str.Format(_T("Gripper Z Move ? (Clamp_Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_GripperZMotion.Move_GripperLeftZ_ClampPos();

	if (bRtn == TRUE)
	{
		m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;
	}
}


void CManual_Sub_GripperZ_Manual::OnBnClickedButtonManualSubGripperZManualTensionPos()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;
	double dPos = CManualData::m_ManualDataGripperZ.Info.m_dGripperLeftZ_TensionPos;
	int nIndex = _eMANUAL_WORK_INDEX_GRIPPER_Z_TENSTION_POS;

	Str.Format(_T("Gripper Z Move ? (Tension_Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_GripperZMotion.Move_GripperLeftZ_TensionPos();

	if (bRtn == TRUE)
	{
		m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;
	}
}


void CManual_Sub_GripperZ_Manual::OnBnClickedButtonManualSubGripperZManualWaitPos2()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;
	double dPos = CManualData::m_ManualDataGripperZ.Info.m_dGripperRightZ_WaitPos;
	int nIndex = _eMANUAL_WORK_INDEX_GRIPPER_RIGHT_Z_WAIT_POS;

	Str.Format(_T("Gripper Z Move ? (Wait_Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_GripperZMotion.Move_GripperRightZ_WaitPos();

	if (bRtn == TRUE)
	{
		m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;
	}
}


void CManual_Sub_GripperZ_Manual::OnBnClickedButtonManualSubGripperZManualLoadingPos2()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;
	double dPos = CManualData::m_ManualDataGripperZ.Info.m_dGripperRightZ_LoadingPos;
	int nIndex = _eMANUAL_WORK_INDEX_GRIPPER_RIGHT_Z_LOADING_POS;

	Str.Format(_T("Gripper Z Move ? (Loading_Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_GripperZMotion.Move_GripperRightZ_LoadingPos();

	if (bRtn == TRUE)
	{
		m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;
	}
}


void CManual_Sub_GripperZ_Manual::OnBnClickedButtonManualSubGripperZManualClampPos3()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;
	double dPos = CManualData::m_ManualDataGripperZ.Info.m_dGripperRightZ_ClampPos;
	int nIndex = _eMANUAL_WORK_INDEX_GRIPPER_RIGHT_Z_CLAMP_POS;

	Str.Format(_T("Gripper Z Move ? (Clamp_Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_GripperZMotion.Move_GripperRightZ_ClampPos();

	if (bRtn == TRUE)
	{
		m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;
	}
}


void CManual_Sub_GripperZ_Manual::OnBnClickedButtonManualSubGripperZManualTensionPos2()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;
	double dPos = CManualData::m_ManualDataGripperZ.Info.m_dGripperRightZ_TensionPos;
	int nIndex = _eMANUAL_WORK_INDEX_GRIPPER_RIGHT_Z_TENSTION_POS;

	Str.Format(_T("Gripper Z Move ? (Tension_Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_GripperZMotion.Move_GripperRightZ_TensionPos();

	if (bRtn == TRUE)
	{
		m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;
	}
}


void CManual_Sub_GripperZ_Manual::OnBnClickedButtonManualSubGripperZManualUnclampPos2()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;
	double dPos = CManualData::m_ManualDataGripperZ.Info.m_dGripperRightZ_UnclampPos;
	int nIndex = _eMANUAL_WORK_INDEX_GRIPPER_RIGHT_Z_UNCLAMP_POS;

	Str.Format(_T("Gripper Z Move ? (Unclamp_Pos : %.5f)"), dPos);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	bRtn = Devs::m_GripperZMotion.Move_GripperRightZ_UnclampPos();

	if (bRtn == TRUE)
	{
		m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
		m_nWork_State[nIndex] = _eSTATE_START;
	}
}
