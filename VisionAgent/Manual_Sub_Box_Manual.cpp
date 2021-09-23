// Manual_Sub_LoadingStage_Manual.cpp: 구현 파일
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "Manual_Sub_Box_Manual.h"
#include "afxdialogex.h"


// CManual_Sub_Box_Manual 대화 상자

IMPLEMENT_DYNAMIC(CManual_Sub_Box_Manual, CDialogEx)

CManual_Sub_Box_Manual::CManual_Sub_Box_Manual(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_MANUAL_SUB_BOX_MANUAL, pParent)
{
	Create(IDD_DLG_MANUAL_SUB_BOX_MANUAL, pParent);
}

CManual_Sub_Box_Manual::~CManual_Sub_Box_Manual()
{
}

void CManual_Sub_Box_Manual::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CManual_Sub_Box_Manual, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_BOX_MANUAL_LOADING_STAGE_UVW_WAIT_POS, &CManual_Sub_Box_Manual::OnBnClickedButtonManualSubBoxManualLoadingStageUvwWaitPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_BOX_MANUAL_LOADING_STAGE_UVW_STICK_LOAD_POS, &CManual_Sub_Box_Manual::OnBnClickedButtonManualSubBoxManualLoadingStageUvwStickLoadPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_BOX_MANUAL_LOADING_STAGE_UVW_STICK_UNLOAD_POS, &CManual_Sub_Box_Manual::OnBnClickedButtonManualSubBoxManualLoadingStageUvwStickUnloadPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_BOX_MANUAL_BOX_ALIGN_CAMERA_LEFT_Y_WAIT_POS, &CManual_Sub_Box_Manual::OnBnClickedButtonManualSubBoxManualBoxAlignCameraLeftYWaitPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_BOX_MANUAL_BOX_ALIGN_CAMERA_LEFT_Y_INSPECTION_POS, &CManual_Sub_Box_Manual::OnBnClickedButtonManualSubBoxManualBoxAlignCameraLeftYInspectionPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_BOX_MANUAL_BOX_ALIGN_CAMERA_RIGHT_Y_WAIT_POS2, &CManual_Sub_Box_Manual::OnBnClickedButtonManualSubBoxManualBoxAlignCameraRightYWaitPos2)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_BOX_MANUAL_BOX_ALIGN_CAMERA_RIGHT_Y_INSPECTION_POS, &CManual_Sub_Box_Manual::OnBnClickedButtonManualSubBoxManualBoxAlignCameraRightYInspectionPos)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_BOX_MANUAL_LASER_POINT, &CManual_Sub_Box_Manual::OnBnClickedButtonManualSubBoxManualLaserPoint)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_SUB_BOX_MANUAL_MAGNETIC_CHUCK, &CManual_Sub_Box_Manual::OnBnClickedButtonManualSubBoxManualMagneticChuck)
END_MESSAGE_MAP()


// CManual_Sub_Box_Manual 메시지 처리기

BOOL CManual_Sub_Box_Manual::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	InitCtrl();

	return TRUE;
}

void CManual_Sub_Box_Manual::OnShowWindow(BOOL bShow, UINT nStatus)
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

void CManual_Sub_Box_Manual::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (Is_Comp_Usable() == FALSE)	return;
}

void CManual_Sub_Box_Manual::OnTimer(UINT_PTR nIDEvent)
{
	double dEnd_Tick, dWait_Tick;
	for (int k = 0; k < _eMANUAL_BOX_INDEX_MAX; k++)
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
	m_bMotionDone[_eMANUAL_BOX_INDEX_LOADING_STAGE_UVW_WAIT_POS] = Devs::m_BoxMotion.Is_LoadingStageUVW_WaitPos();
	m_bMotionDone[_eMANUAL_BOX_INDEX_LOADING_STAGE_UVW_STICK_LOAD_POS] = Devs::m_BoxMotion.Is_LoadingStageUVW_StickLoadPos();
	m_bMotionDone[_eMANUAL_BOX_INDEX_LOADING_STAGE_UVW_STICK_UNLOAD_POS] = Devs::m_BoxMotion.Is_LoadingStageUVW_StickUnloadPos();
	//21.02.04 sjc no box cam servo
	//m_bMotionDone[_eMANUAL_BOX_INDEX_BOX_ALIGN_CAMERA_Y_LEFT_WAIT_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_BOX_ALIGN_CAMERA_YL, CManualData::m_ManualDataBox.Info.m_dBoxAlignCameraYL_Wait_Pos);
	//m_bMotionDone[_eMANUAL_BOX_INDEX_BOX_ALIGN_CAMERA_Y_LEFT_INSPECTION_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_BOX_ALIGN_CAMERA_YL, CManualData::m_ManualDataBox.Info.m_dBoxAlignCameraYL_Inspection_Pos);

	//m_bMotionDone[_eMANUAL_BOX_INDEX_BOX_ALIGN_CAMERA_Y_RIGHT_WAIT_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_BOX_ALIGN_CAMERA_YR, CManualData::m_ManualDataBox.Info.m_dBoxAlignCameraYR_Wait_Pos);
	//m_bMotionDone[_eMANUAL_BOX_INDEX_BOX_ALIGN_CAMERA_Y_RIGHT_INSPECTION_POS] = Devs::m_BaseMotion.IsAxisMoveDone(AXIS_BOX_ALIGN_CAMERA_YR, CManualData::m_ManualDataBox.Info.m_dBoxAlignCameraYR_Inspection_Pos);
	int k = 0;
	for (k = 0; k < _eMANUAL_BOX_INDEX_MAX; k++)
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
	if (m_bPrevLaserPoint != SharedInfo::DOutputValue[_DOUT_BOX_LASER_POINT_ON])
	{
		if (SharedInfo::DOutputValue[_DOUT_BOX_LASER_POINT_ON])
			m_stLamp_LaserPoint.SetBackgroundColor(LED_LAMP_ON);
		else
			m_stLamp_LaserPoint.SetBackgroundColor(LED_LAMP_OFF);
			
	}
	m_bPrevLaserPoint = SharedInfo::DOutputValue[_DOUT_BOX_LASER_POINT_ON];
	//
	//if (m_bPrevMagneticChuck != SharedInfo::DOutputValue[_DOUT_MAGNETIC_CHUCK_ON])
	//{
	//	if (SharedInfo::DOutputValue[_DOUT_MAGNETIC_CHUCK_ON])
	//		m_stLamp_MagneticChuck.SetBackgroundColor(LED_LAMP_ON);
	//	else
	//		m_stLamp_MagneticChuck.SetBackgroundColor(LED_LAMP_OFF);

	//}
	//m_bPrevMagneticChuck = SharedInfo::DOutputValue[_DOUT_MAGNETIC_CHUCK_ON];

	//if (m_bPrevBoxStageJigLockSensor != SharedInfo::DInputValue[_DIN_LOAD_PAPER_BOX_FWD])
	//{
	//	if (Devs::m_LoaderMotion.Is_PaperBox_Fwd() == TRUE)
	//		m_stLamp_BoxStageJigLockSensor.SetBackgroundColor(LED_LAMP_ON);
	//	else
	//		m_stLamp_BoxStageJigLockSensor.SetBackgroundColor(LED_LAMP_OFF);
	//}
	//m_bPrevBoxStageJigLockSensor = SharedInfo::DInputValue[_DIN_LOAD_PAPER_BOX_FWD];

	//Lock Sensor
	//21.02.04 sjc no jig lock sensor

	//if (m_bPrevPaperStageJigLockSensor != SharedInfo::DInputValue[PAPER_STAGE_JIG_LOCK_SENSOR])
	//{
	//	if (SharedInfo::DOutputValue[PAPER_STAGE_JIG_LOCK_SENSOR])
	//		m_stLamp_PaperStageJigLockSensor.SetBackgroundColor(LED_LAMP_ON);
	//	else
	//		m_stLamp_PaperStageJigLockSensor.SetBackgroundColor(LED_LAMP_OFF);
	//}
	//m_bPrevPaperStageJigLockSensor = SharedInfo::DOutputValue[PAPER_STAGE_JIG_LOCK_SENSOR];
#pragma endregion

	CDialogEx::OnTimer(nIDEvent);
}
//--------------------------------------------------------
void	CManual_Sub_Box_Manual::InitCtrl()
{
	m_stLamp_Work[_eMANUAL_BOX_INDEX_LOADING_STAGE_UVW_WAIT_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_BOX_MANUAL_LOADING_STAGE_UVW_WAIT_POS, this);
	m_stLamp_Work[_eMANUAL_BOX_INDEX_LOADING_STAGE_UVW_STICK_LOAD_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_BOX_MANUAL_LOADING_STAGE_UVW_STICK_LOAD_POS, this);
	m_stLamp_Work[_eMANUAL_BOX_INDEX_LOADING_STAGE_UVW_STICK_UNLOAD_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_BOX_MANUAL_LOADING_STAGE_UVW_STICK_UNLOAD_POS, this);
	m_stLamp_Work[_eMANUAL_BOX_INDEX_BOX_ALIGN_CAMERA_Y_LEFT_WAIT_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_BOX_MANUAL_BOX_ALIGN_CAMERA_LEFT_Y_WAIT_POS, this);
	m_stLamp_Work[_eMANUAL_BOX_INDEX_BOX_ALIGN_CAMERA_Y_LEFT_INSPECTION_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_BOX_MANUAL_BOX_ALIGN_CAMERA_LEFT_Y_INSPECTION_POS, this);
	m_stLamp_Work[_eMANUAL_BOX_INDEX_BOX_ALIGN_CAMERA_Y_RIGHT_WAIT_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_BOX_MANUAL_BOX_ALIGN_CAMERA_RIGHT_Y_WAIT_POS, this);
	m_stLamp_Work[_eMANUAL_BOX_INDEX_BOX_ALIGN_CAMERA_Y_RIGHT_INSPECTION_POS].SubclassDlgItem(IDC_LAMP_MANUAL_SUB_BOX_MANUAL_BOX_ALIGN_CAMERA_RIGHT_Y_INSPECTION_POS, this);

	for (int k = 0; k < _eMANUAL_BOX_INDEX_MAX; k++)
	{
		m_stLamp_Work[k].SetTextColor(LLTGRAY);
		m_stLamp_Work[k].SetParaChangeColor(BK_GND);
		m_stLamp_Work[k].SetParaOriginColor(STATEBAR_NAME_BK_RGB);
		m_stLamp_Work[k].SetTextColor(LED_LAMP_OFF);
		m_stLamp_Work[k].SetBackgroundColor(LED_LAMP_OFF);
	}

	m_stLamp_LaserPoint.SubclassDlgItem(IDC_LAMP_MANUAL_SUB_BOX_MANUAL_LASER_POINT, this);
	m_stLamp_LaserPoint.SetTextColor(LLTGRAY);
	m_stLamp_LaserPoint.SetParaChangeColor(BK_GND);
	m_stLamp_LaserPoint.SetParaOriginColor(STATEBAR_NAME_BK_RGB);
	m_stLamp_LaserPoint.SetTextColor(LED_LAMP_OFF);
	m_stLamp_LaserPoint.SetBackgroundColor(LED_LAMP_OFF);

	//m_stLamp_MagneticChuck.SubclassDlgItem(IDC_LAMP_MANUAL_SUB_BOX_MANUAL_MAGNETIC_CHUCK, this);
	//m_stLamp_MagneticChuck.SetTextColor(LLTGRAY);
	//m_stLamp_MagneticChuck.SetParaChangeColor(BK_GND);
	//m_stLamp_MagneticChuck.SetParaOriginColor(STATEBAR_NAME_BK_RGB);
	//m_stLamp_MagneticChuck.SetTextColor(LED_LAMP_OFF);
	//m_stLamp_MagneticChuck.SetBackgroundColor(LED_LAMP_OFF);

	//m_stLamp_BoxStageJigLockSensor.SubclassDlgItem(IDC_LAMP_MANUAL_SUB_BOX_MANUAL_BOX_STAGE_JIG_LOCK_SENSOR, this);
	//m_stLamp_BoxStageJigLockSensor.SetTextColor(LLTGRAY);
	//m_stLamp_BoxStageJigLockSensor.SetParaChangeColor(BK_GND);
	//m_stLamp_BoxStageJigLockSensor.SetParaOriginColor(STATEBAR_NAME_BK_RGB);
	//m_stLamp_BoxStageJigLockSensor.SetTextColor(LED_LAMP_OFF);
	//m_stLamp_BoxStageJigLockSensor.SetBackgroundColor(LED_LAMP_OFF);

	m_stLamp_PaperStageJigLockSensor.SubclassDlgItem(IDC_LAMP_MANUAL_SUB_BOX_MANUAL_PAPER_STAGE_JIG_LOCK_SENSOR, this);
	m_stLamp_PaperStageJigLockSensor.SetTextColor(LLTGRAY);
	m_stLamp_PaperStageJigLockSensor.SetParaChangeColor(BK_GND);
	m_stLamp_PaperStageJigLockSensor.SetParaOriginColor(STATEBAR_NAME_BK_RGB);
	m_stLamp_PaperStageJigLockSensor.SetTextColor(LED_LAMP_OFF);
	m_stLamp_PaperStageJigLockSensor.SetBackgroundColor(LED_LAMP_OFF);
}
//--------------------------------------------------------
BOOL	CManual_Sub_Box_Manual::Is_Comp_Usable()
{
	int i = 0;
	for (i = 0; i < _eMANUAL_BOX_INDEX_MAX; i++)
	{
		if (m_stLamp_Work[i].GetSafeHwnd() == NULL)
			return FALSE;
	}

	return TRUE;
}
//--------------------------------------------------------
void	CManual_Sub_Box_Manual::InitPara()
{
	for (int k = 0; k < _eMANUAL_BOX_INDEX_MAX; k++)
	{
		m_nWork_State[k] = _eSTATE_NONE;
		m_stLamp_Work[k].SetBackgroundColor(LED_LAMP_OFF);

		m_bMotionDone[k] = FALSE;
		m_bPrevStatus_InPos[k] = FALSE;
	}

	m_bPrevLaserPoint = -1;
	m_bPrevMagneticChuck = -1;
}
//--------------------------------------------------------
void	CManual_Sub_Box_Manual::ChangeData()
{
	
}

void CManual_Sub_Box_Manual::OnBnClickedButtonManualSubBoxManualLoadingStageUvwWaitPos()
{
	CString Str = _T("");
	double dVel = 1.0;
	double dAccel = dVel * 2.0;
	double dDecel = dVel * 2.0;
	double dUvwPos[3] = { 0.0, 0.0, 0.0 };
	double dUvwVel[3] = { 1.0, 1.0, 1.0 };
	double dUvwAccel[3] = { 2.0, 2.0, 2.0 };
	double dUvwDecel[3] = { 2.0, 2.0, 2.0 };
	double dUVWScale = 2;

	int nIndex = _eMANUAL_BOX_INDEX_LOADING_STAGE_UVW_WAIT_POS;

	dUvwPos[0] = CManualData::m_ManualDataBox.Info.m_dLoadingStageX_Wait_Pos;
	dUvwPos[1] = CManualData::m_ManualDataBox.Info.m_dLoadingStageY_Wait_Pos;
	dUvwPos[2] = CManualData::m_ManualDataBox.Info.m_dLoadingStageT_Wait_Pos;

	Str.Format(_T("Loading Stage Uvw Move To Wait Pos ? (X:%.5f, Y:%.5f, T:%.5f)"), dUvwPos[0], dUvwPos[1], dUvwPos[2]);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	dUvwVel[0] = dVel;
	dUvwVel[1] = dVel;
	dUvwVel[2] = dVel;
	dUvwAccel[0] = dUvwVel[0] * dUVWScale;
	dUvwAccel[1] = dUvwVel[1] * dUVWScale;
	dUvwAccel[2] = dUvwVel[2] * dUVWScale;
	dUvwDecel[0] = dUvwVel[0] * dUVWScale;
	dUvwDecel[1] = dUvwVel[1] * dUVWScale;
	dUvwDecel[2] = dUvwVel[2] * dUVWScale;

	Devs::m_BoxMotion.UVWStagePosMove(dUvwPos, dUvwVel, dUvwAccel, dUvwDecel);

	Str.Format(_T("Loading Stage UVW Move To Wait Pos X:%.5f, Y:%.5f, T:%.5f)"), dUvwPos[0], dUvwPos[1], dUvwPos[2]);
	Total_Msg(Str);

	m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
	m_dMotion_Strt_Tick[nIndex] = GetTickCount();
	m_nWork_State[nIndex] = _eSTATE_START;
}

void CManual_Sub_Box_Manual::OnBnClickedButtonManualSubBoxManualLoadingStageUvwStickLoadPos()
{
	CString Str = _T("");
	double dVel = 1.0;
	double dAccel = dVel * 2.0;
	double dDecel = dVel * 2.0;
	double dUvwPos[3] = { 0.0, 0.0, 0.0 };
	double dUvwVel[3] = { 1.0, 1.0, 1.0 };
	double dUvwAccel[3] = { 2.0, 2.0, 2.0 };
	double dUvwDecel[3] = { 2.0, 2.0, 2.0 };
	double dUVWScale = 2;

	int nIndex = _eMANUAL_BOX_INDEX_LOADING_STAGE_UVW_STICK_LOAD_POS;

	dUvwPos[0] = CManualData::m_ManualDataBox.Info.m_dLoadingStageX_StickLoad_Pos;
	dUvwPos[1] = CManualData::m_ManualDataBox.Info.m_dLoadingStageY_StickLoad_Pos;
	dUvwPos[2] = CManualData::m_ManualDataBox.Info.m_dLoadingStageT_StickLoad_Pos;

	Str.Format(_T("Loading Stage Uvw Move To Stick Load Pos Move ? (X:%.5f, Y:%.5f, T:%.5f)"), dUvwPos[0], dUvwPos[1], dUvwPos[2]);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	dUvwVel[0] = dVel;
	dUvwVel[1] = dVel;
	dUvwVel[2] = dVel;
	dUvwAccel[0] = dUvwVel[0] * dUVWScale;
	dUvwAccel[1] = dUvwVel[1] * dUVWScale;
	dUvwAccel[2] = dUvwVel[2] * dUVWScale;
	dUvwDecel[0] = dUvwVel[0] * dUVWScale;
	dUvwDecel[1] = dUvwVel[1] * dUVWScale;
	dUvwDecel[2] = dUvwVel[2] * dUVWScale;

	Devs::m_BoxMotion.UVWStagePosMove(dUvwPos, dUvwVel, dUvwAccel, dUvwDecel);

	Str.Format(_T("Loading Stage UVW Move To Stick Load Pos X:%.5f, Y:%.5f, T:%.5f)"), dUvwPos[0], dUvwPos[1], dUvwPos[2]);
	Total_Msg(Str);

	m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
	m_dMotion_Strt_Tick[nIndex] = GetTickCount();
	m_nWork_State[nIndex] = _eSTATE_START;
}


void CManual_Sub_Box_Manual::OnBnClickedButtonManualSubBoxManualLoadingStageUvwStickUnloadPos()
{
	CString Str = _T("");
	double dVel = 1.0;
	double dAccel = dVel * 2.0;
	double dDecel = dVel * 2.0;
	double dUvwPos[3] = { 0.0, 0.0, 0.0 };
	double dUvwVel[3] = { 1.0, 1.0, 1.0 };
	double dUvwAccel[3] = { 2.0, 2.0, 2.0 };
	double dUvwDecel[3] = { 2.0, 2.0, 2.0 };
	double dUVWScale = 2;

	int nIndex = _eMANUAL_BOX_INDEX_LOADING_STAGE_UVW_STICK_UNLOAD_POS;

	dUvwPos[0] = CManualData::m_ManualDataBox.Info.m_dLoadingStageX_StickUnload_Pos;
	dUvwPos[1] = CManualData::m_ManualDataBox.Info.m_dLoadingStageY_StickUnload_Pos;
	dUvwPos[2] = CManualData::m_ManualDataBox.Info.m_dLoadingStageT_StickUnload_Pos;

	Str.Format(_T("Loading Stage Uvw Move To Stick Unlaod Pos Move ? (Pos X:%.5f, Y:%.5f, T:%.5f)"), dUvwPos[0], dUvwPos[1], dUvwPos[2]);
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	dUvwVel[0] = dVel;
	dUvwVel[1] = dVel;
	dUvwVel[2] = dVel;
	dUvwAccel[0] = dUvwVel[0] * dUVWScale;
	dUvwAccel[1] = dUvwVel[1] * dUVWScale;
	dUvwAccel[2] = dUvwVel[2] * dUVWScale;
	dUvwDecel[0] = dUvwVel[0] * dUVWScale;
	dUvwDecel[1] = dUvwVel[1] * dUVWScale;
	dUvwDecel[2] = dUvwVel[2] * dUVWScale;

	Devs::m_BoxMotion.UVWStagePosMove(dUvwPos, dUvwVel, dUvwAccel, dUvwDecel);

	Str.Format(_T("Loading Stage UVW Move To Stick Unload Pos X:%.5f, Y:%.5f, T:%.5f)"), dUvwPos[0], dUvwPos[1], dUvwPos[2]);
	Total_Msg(Str);

	m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
	m_dMotion_Strt_Tick[nIndex] = GetTickCount();
	m_nWork_State[nIndex] = _eSTATE_START;
}


void CManual_Sub_Box_Manual::OnBnClickedButtonManualSubBoxManualBoxAlignCameraLeftYWaitPos()
{
	//CString Str = _T("");
	//double dPos = CManualData::m_ManualDataBox.Info.m_dBoxAlignCameraYL_Wait_Pos;
	//int nIndex = _eMANUAL_BOX_INDEX_BOX_ALIGN_CAMERA_Y_LEFT_WAIT_POS;
	//BOOL bRtn = FALSE;

	//Str.Format(_T("BoxAlign Camera YL Move ? (Wait_Pos : %.5f)"), dPos);
	//if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	//bRtn = Devs::m_BoxMotion.BoxAlignCameraYL_WaitPos();
	//if (bRtn == TRUE)
	//{
	//	m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
	//	m_dMotion_Strt_Tick[nIndex] = GetTickCount();
	//	m_nWork_State[nIndex] = _eSTATE_START;
	//}
}


void CManual_Sub_Box_Manual::OnBnClickedButtonManualSubBoxManualBoxAlignCameraLeftYInspectionPos()
{
//	CString Str = _T("");
//	BOOL bRtn = FALSE;
//
//#pragma region //Interlock
//	double dPosTemp = SharedInfo::GetActPos(AXIS_VIRTUAL_GANTRY_Y);
//	if (dPosTemp < CManualData::m_ManualDataGantry.Info.m_dGantry_Y_Wait_Pos)
//	{
//		Str.Format(_T("Gantry Y Pos Check !!! (Cur Pos < Wait Pos)"));
//		AfxMessageBox(Str);
//		return;
//	}
//#pragma endregion
//
//	int nIndex = _eMANUAL_BOX_INDEX_BOX_ALIGN_CAMERA_Y_LEFT_INSPECTION_POS;
//
//	double dPos = CManualData::m_ManualDataBox.Info.m_dBoxAlignCameraYL_Inspection_Pos;
//	Str.Format(_T("BoxAlign Camera YL Move ? (Inspection Pos : %.5f)"), dPos);
//	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;
//
//	bRtn = Devs::m_BoxMotion.BoxAlignCameraYL_InspectionPos();
//	if (bRtn == TRUE)
//	{
//		m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
//		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
//		m_nWork_State[nIndex] = _eSTATE_START;
//	}
}


void CManual_Sub_Box_Manual::OnBnClickedButtonManualSubBoxManualBoxAlignCameraRightYWaitPos2()
{
	//CString Str = _T("");
	//double dPos = CManualData::m_ManualDataBox.Info.m_dBoxAlignCameraYR_Wait_Pos;
	//int nIndex = _eMANUAL_BOX_INDEX_BOX_ALIGN_CAMERA_Y_RIGHT_WAIT_POS;
	//BOOL bRtn = FALSE;

	//Str.Format(_T("BoxAlign Camera YR Move ? (Wait_Pos : %.5f)"), dPos);
	//if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	//bRtn = Devs::m_BoxMotion.BoxAlignCameraYR_WaitPos();
	//if (bRtn == TRUE)
	//{
	//	m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
	//	m_dMotion_Strt_Tick[nIndex] = GetTickCount();
	//	m_nWork_State[nIndex] = _eSTATE_START;
	//}
}


void CManual_Sub_Box_Manual::OnBnClickedButtonManualSubBoxManualBoxAlignCameraRightYInspectionPos()
{
//	CString Str = _T("");
//	BOOL bRtn = FALSE;
//
//#pragma region //Interlock
//	double dPosTemp = SharedInfo::GetActPos(AXIS_VIRTUAL_GANTRY_Y);
//	if (dPosTemp < CManualData::m_ManualDataGantry.Info.m_dGantry_Y_Wait_Pos)
//	{
//		Str.Format(_T("Gantry Y Pos Check !!! (Cur Pos < Wait Pos)"));
//		AfxMessageBox(Str);
//		return;
//	}
//#pragma endregion
// 	
//	int nIndex = _eMANUAL_BOX_INDEX_BOX_ALIGN_CAMERA_Y_RIGHT_INSPECTION_POS;
//	
//	double dPos = CManualData::m_ManualDataBox.Info.m_dBoxAlignCameraYR_Inspection_Pos;
//	Str.Format(_T("BoxAlign Camera YR Move ? (Inspection Pos : %.5f)"), dPos);
//	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;
//
//	bRtn = Devs::m_BoxMotion.BoxAlignCameraYR_InspectionPos();
//	if (bRtn == TRUE)
//	{
//		m_stLamp_Work[nIndex].SetBackgroundColor(LED_LAMP_OFF);
//		m_dMotion_Strt_Tick[nIndex] = GetTickCount();
//		m_nWork_State[nIndex] = _eSTATE_START;
//	}
}


void CManual_Sub_Box_Manual::OnBnClickedButtonManualSubBoxManualLaserPoint()
{
	if (SharedInfo::DOutputValue[_DOUT_BOX_LASER_POINT_ON])
	{
		Devs::m_BaseMotion.SetDOutputBitValue(_DOUT_BOX_LASER_POINT_ON, FALSE);
		Total_Msg(_T("Box Laser Point Off"));
	}
	else
	{
		Devs::m_BaseMotion.SetDOutputBitValue(_DOUT_BOX_LASER_POINT_ON, TRUE);
		Total_Msg(_T("Box Laser Point On"));
	}
}


void CManual_Sub_Box_Manual::OnBnClickedButtonManualSubBoxManualMagneticChuck()
{
	//// TODO: Add your control notification handler code here

	//if (SharedInfo::DOutputValue[_DOUT_MAGNETIC_CHUCK_ON])
	//{
	//	Devs::m_BaseMotion.SetDOutputBitValue(_DOUT_MAGNETIC_CHUCK_ON, FALSE);
	//	Total_Msg(_T("Box Magnetic Chuck Off"));
	//}
	//else
	//{
	//	Devs::m_BaseMotion.SetDOutputBitValue(_DOUT_MAGNETIC_CHUCK_ON, TRUE);
	//	Total_Msg(_T("Box Magnetic Chuck On"));
	//}
}
