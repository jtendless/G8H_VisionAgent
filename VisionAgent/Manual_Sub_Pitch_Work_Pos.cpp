// Manual_Sub_Pitch_Work_Pos.cpp: 구현 파일
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "Manual_Sub_Pitch_Work_Pos.h"
#include "afxdialogex.h"


// CManual_Sub_Pitch_Work_Pos 대화 상자

IMPLEMENT_DYNAMIC(CManual_Sub_Pitch_Work_Pos, CDialogEx)

CManual_Sub_Pitch_Work_Pos::CManual_Sub_Pitch_Work_Pos(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_MANUAL_SUB_PITCH_WORK_POS, pParent)
{
	Create(IDD_DLG_MANUAL_SUB_PITCH_WORK_POS, pParent);
}

CManual_Sub_Pitch_Work_Pos::~CManual_Sub_Pitch_Work_Pos()
{
}

void CManual_Sub_Pitch_Work_Pos::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_COMBO_MANUAL_SUB_PITCH_WORK_SPEED_PITCH_LEFT, m_cbxSpeed_PitchLeft);
	DDX_Control(pDX, IDC_COMBO_MANUAL_SUB_PITCH_STEP_PITCH_LEFT, m_cbxStep_PitchLeft);
	DDX_Control(pDX, IDC_CHECK_MANUAL_SUB_PITCH_WORK_JOG_PITCH_LEFT, m_chbSpeed_PitchLeft);
	DDX_Control(pDX, IDC_CHECK_MANUAL_SUB_PITCH_WORK_RELATIVE_PITCH_LEFT, m_chbStep_PitchLeft);

	DDX_Control(pDX, IDC_COMBO_MANUAL_SUB_PITCH_WORK_SPEED_PITCH_RIGHT, m_cbxSpeed_PitchRight);
	DDX_Control(pDX, IDC_COMBO_MANUAL_SUB_PITCH_STEP_PITCH_RIGHT, m_cbxStep_PitchRight);
	DDX_Control(pDX, IDC_CHECK_MANUAL_SUB_PITCH_WORK_JOG_PITCH_RIGHT, m_chbSpeed_PitchRight);
	DDX_Control(pDX, IDC_CHECK_MANUAL_SUB_PITCH_WORK_RELATIVE_PITCH_RIGHT, m_chbStep_PitchRight);

	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CManual_Sub_Pitch_Work_Pos, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CManual_Sub_Pitch_Work_Pos 메시지 처리기

//------------------------------------------------------------------
BOOL CManual_Sub_Pitch_Work_Pos::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	Init_Title_Set();
	ChangeUI();
	for (int k = 0; k < _eMANUAL_WORK_PITCH_MAX; k++)
	{
		m_bIs_Motor_Run[k] = false;
	}
	return TRUE;
}
void CManual_Sub_Pitch_Work_Pos::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow == TRUE)
	{
		SetTimer(1, 100, NULL);
	}
	else if (bShow == FALSE)
	{
		KillTimer(1);
	}
	ChangeUI();
}
//------------------------------------------------------------------
void CManual_Sub_Pitch_Work_Pos::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (Is_Comp_Usable() == FALSE)	return;

	CString strSpeed[3] = { _T("LOW"), _T("MID"), _T("HIGH") };
	CString strStep[7] = { _T("0.001"), _T("0.005"), _T("0.010"), _T("0.050"), _T("0.100"), _T("0.500"), _T("1.000") };

	m_cbxSpeed_PitchLeft.ResetContent();
	m_cbxSpeed_PitchRight.ResetContent();

	for (int k = 0; k < 3; k++)
	{
		m_cbxSpeed_PitchLeft.AddString(strSpeed[k]);
		m_cbxSpeed_PitchRight.AddString(strSpeed[k]);
	}

	m_cbxStep_PitchLeft.ResetContent();
	m_cbxStep_PitchRight.ResetContent();

	for (int k = 0; k < 3; k++)
	{
		m_cbxStep_PitchLeft.AddString(strStep[k]);
		m_cbxStep_PitchRight.AddString(strStep[k]);
	}
}
//------------------------------------------------------------------
void CManual_Sub_Pitch_Work_Pos::OnTimer(UINT_PTR nIDEvent)
{
	CDialogEx::OnTimer(nIDEvent);
}
//------------------------------------------------------------------
void	CManual_Sub_Pitch_Work_Pos::Init_Title_Set()
{

}
//------------------------------------------------------------------
BOOL	CManual_Sub_Pitch_Work_Pos::Is_Comp_Usable()
{
	if (GetDlgItem(IDC_COMBO_MANUAL_SUB_PITCH_WORK_SPEED_PITCH_LEFT)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COMBO_MANUAL_SUB_PITCH_STEP_PITCH_LEFT)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_CHECK_MANUAL_SUB_PITCH_WORK_JOG_PITCH_LEFT)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_CHECK_MANUAL_SUB_PITCH_WORK_RELATIVE_PITCH_LEFT)->GetSafeHwnd() == NULL) return FALSE;

	if (GetDlgItem(IDC_COMBO_MANUAL_SUB_PITCH_WORK_SPEED_PITCH_RIGHT)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_COMBO_MANUAL_SUB_PITCH_STEP_PITCH_RIGHT)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_CHECK_MANUAL_SUB_PITCH_WORK_JOG_PITCH_RIGHT)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_CHECK_MANUAL_SUB_PITCH_WORK_RELATIVE_PITCH_RIGHT)->GetSafeHwnd() == NULL) return FALSE;

	return TRUE;
}
//------------------------------------------------------------------
void CManual_Sub_Pitch_Work_Pos::ChangeUI()
{
	//저장된 데이터를 UI에 표시
}
//------------------------------------------------------------------
void CManual_Sub_Pitch_Work_Pos::ChangeData()
{
	//UI에 기입한 내용을 SystemData 변수에 입력
}
//------------------------------------------------------------------
void CManual_Sub_Pitch_Work_Pos::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDialogEx::OnLButtonDown(nFlags, point);
}
//------------------------------------------------------------------
void CManual_Sub_Pitch_Work_Pos::OnLButtonUp(UINT nFlags, CPoint point)
{
	Devs::m_JogMotion.JogStop(m_eAxisID);

	CDialogEx::OnLButtonUp(nFlags, point);
}