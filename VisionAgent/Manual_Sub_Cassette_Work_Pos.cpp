// Manual_Sub_Cassette_Work_Pos.cpp: 구현 파일
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "Manual_Sub_Cassette_Work_Pos.h"
#include "afxdialogex.h"


// CManual_Sub_Cassette_Work_Pos 대화 상자

IMPLEMENT_DYNAMIC(CManual_Sub_Cassette_Work_Pos, CDialogEx)

CManual_Sub_Cassette_Work_Pos::CManual_Sub_Cassette_Work_Pos(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_MANUAL_SUB_CASSETTE_WORK_POS, pParent)
{
	Create(IDD_DLG_MANUAL_SUB_CASSETTE_WORK_POS, pParent);
}

CManual_Sub_Cassette_Work_Pos::~CManual_Sub_Cassette_Work_Pos()
{
}

void CManual_Sub_Cassette_Work_Pos::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_STATIC_MANUAL_SUB_CASSETTE_WORK_CURRENT_CASSETTE_Z, m_staticCurPos_CassetteZ);
	DDX_Control(pDX, IDC_COMBO_MANUAL_SUB_CASSETTE_WORK_SPEED_CASSETTE_Z, m_cbxSpeed_CassetteZ);
	DDX_Control(pDX, IDC_COMBO_MANUAL_SUB_CASSETTE_WORK_STEP_CASSETTE_Z, m_cbxStep_CassetteZ);
	DDX_Control(pDX, IDC_CHECK_MANUAL_SUB_CASSETTE_WORK_JOG_CASSETTE_Z, m_chbSpeed_CassetteZ);
	DDX_Control(pDX, IDC_CHECK_MANUAL_SUB_CASSETTE_WORK_RELATIVE_CASSETTE_Z, m_chbStep_CassetteZ);

	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CManual_Sub_Cassette_Work_Pos, CDialogEx)
	ON_WM_SIZE()
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CManual_Sub_Cassette_Work_Pos 메시지 처리기

//------------------------------------------------------------------
BOOL CManual_Sub_Cassette_Work_Pos::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ChangeUI();
	return TRUE;
}
//------------------------------------------------------------------
void CManual_Sub_Cassette_Work_Pos::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (Is_Comp_Usable() == TRUE)
	{
		ChangeUI();
		if (bShow == TRUE)
		{
			SetTimer(1, 100, NULL);
		}
		else if (bShow == FALSE)
		{
			KillTimer(1);
		}
	}
}
//------------------------------------------------------------------
void CManual_Sub_Cassette_Work_Pos::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (Is_Comp_Usable() == FALSE)	return;

	CString strSpeed[3] = { _T("LOW"), _T("MID"), _T("HIGH") };
	CString strStep[7] = { _T("0.001"), _T("0.005"), _T("0.010"), _T("0.050"), _T("0.100"), _T("0.500"), _T("1.000") };

	m_cbxSpeed_CassetteZ.ResetContent();

	for (int k = 0; k < 3; k++)
	{
		m_cbxSpeed_CassetteZ.AddString(strSpeed[k]);
	}

	m_cbxStep_CassetteZ.ResetContent();

	for (int k = 0; k < 3; k++)
	{
		m_cbxStep_CassetteZ.AddString(strStep[k]);
	}
}
//------------------------------------------------------------------
void CManual_Sub_Cassette_Work_Pos::OnTimer(UINT_PTR nIDEvent)
{
	CString Str;

	Str.Format(_T("%.5f"), SharedInfo::GetCmdPos(AXIS_MAGAZINE_LIFT_Z));
	m_staticCurPos_CassetteZ.SetWindowText(Str);

	CDialogEx::OnTimer(nIDEvent);
}
//------------------------------------------------------------------
BOOL	CManual_Sub_Cassette_Work_Pos::Is_Comp_Usable()
{
	if (m_staticCurPos_CassetteZ.GetSafeHwnd() == NULL) return FALSE;
	if (m_cbxSpeed_CassetteZ.GetSafeHwnd() == NULL) return FALSE;
	if (m_cbxStep_CassetteZ.GetSafeHwnd() == NULL) return FALSE;
	if (m_chbSpeed_CassetteZ.GetSafeHwnd() == NULL) return FALSE;
	if (m_chbStep_CassetteZ.GetSafeHwnd() == NULL) return FALSE;

	return TRUE;
}
//------------------------------------------------------------------
void CManual_Sub_Cassette_Work_Pos::ChangeUI()
{
	//저장된 데이터를 UI에 표시
}
//------------------------------------------------------------------
void CManual_Sub_Cassette_Work_Pos::ChangeData()
{
	//UI에 기입한 내용을 SystemData 변수에 입력
}
//-----------------------------------------------------
void CManual_Sub_Cassette_Work_Pos::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CDialogEx::OnLButtonDown(nFlags, point);
}
//-----------------------------------------------------
void CManual_Sub_Cassette_Work_Pos::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CDialogEx::OnLButtonUp(nFlags, point);
}