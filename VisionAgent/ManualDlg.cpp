// ManualDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentDlg.h"
#include "ManualDlg.h"
#include "afxdialogex.h"
#include "Manual_Sub_Gantry_Manual.h"
#include "Manual_Sub_Gantry_Fixed_Pos.h"
#include "Manual_Sub_Clamp_Manual.h"
#include "Manual_Sub_Clamp_Fixed_Pos.h"
#include "Manual_Sub_Stretch_Manual.h"
#include "Manual_Sub_Stretch_Fixed_Pos.h"
#include "Manual_Sub_GripperZ_Manual.h"
#include "Manual_Sub_GripperZ_Fixed_Pos.h"

// CManualDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CManualDlg, CDialogEx)

CManualDlg::CManualDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_VISION_AGENT_MANUAL_DIALOG, pParent)
{
	Create(IDD_VISION_AGENT_MANUAL_DIALOG, pParent);

	m_nCurMainBtn = 0;
}

CManualDlg::~CManualDlg()
{
}

void CManualDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
//-----------------------------------------------------------------
BEGIN_MESSAGE_MAP(CManualDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_GANTRY, &CManualDlg::OnBnClickedButtonManualGantry)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_INSPECT, &CManualDlg::OnBnClickedButtonManualInspect)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_CLAMP, &CManualDlg::OnBnClickedButtonManualClamp)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_STRETCH, &CManualDlg::OnBnClickedButtonManualStretch)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_GRIPPER_Z, &CManualDlg::OnBnClickedButtonManualGripperZ)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL, &CManualDlg::OnBnClickedButtonManual)
	ON_BN_CLICKED(IDC_BUTTON_FIXED_POS, &CManualDlg::OnBnClickedButtonFixedPos)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CManualDlg::OnBnClickedButtonClose)
END_MESSAGE_MAP()
//-----------------------------------------------------------------
BOOL CManualDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	Dialog_Init();
	return TRUE;
}

// CManualDlg 메시지 처리기입니다.
//-----------------------------------------------------------------
void CManualDlg::Dialog_Init()
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//								  버튼
	//--------------------------------------------------------------------------------------------------------
	m_btnManual[MANUAL_GANTRY_DLG].SubclassDlgItem(IDC_BUTTON_MANUAL_GANTRY, this);
	m_btnManual[MANUAL_INSPECT_DLG].SubclassDlgItem(IDC_BUTTON_MANUAL_INSPECT, this);
	m_btnManual[MANUAL_CLAMP_DLG].SubclassDlgItem(IDC_BUTTON_MANUAL_CLAMP, this);	
	m_btnManual[MANUAL_STRETCH_DLG].SubclassDlgItem(IDC_BUTTON_MANUAL_STRETCH, this);
	m_btnManual[MANUAL_GRIPPER_Z_DLG].SubclassDlgItem(IDC_BUTTON_MANUAL_GRIPPER_Z, this);

	m_btnSubManual[MANUAL_SUB_MANUAL].SubclassDlgItem(IDC_BUTTON_MANUAL, this);
	m_btnSubManual[MANUAL_SUB_FIXED_POS].SubclassDlgItem(IDC_BUTTON_FIXED_POS, this);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//								버튼 램프
	//--------------------------------------------------------------------------------------------------------
	m_stcManual_Dlg_Lamp[MANUAL_GANTRY_DLG].SubclassDlgItem(IDC_STATIC_LAMP_MANUAL_GANTRY, this);
	m_stcManual_Dlg_Lamp[MANUAL_INSPECT_DLG].SubclassDlgItem(IDC_STATIC_LAMP_MANUAL_INSPECT, this);
	m_stcManual_Dlg_Lamp[MANUAL_CLAMP_DLG].SubclassDlgItem(IDC_STATIC_LAMP_MANUAL_CLAMP, this);	
	m_stcManual_Dlg_Lamp[MANUAL_STRETCH_DLG].SubclassDlgItem(IDC_STATIC_LAMP_MANUAL_STRETCH, this);
	m_stcManual_Dlg_Lamp[MANUAL_GRIPPER_Z_DLG].SubclassDlgItem(IDC_STATIC_LAMP_MANUAL_GRIPPER_Z, this);

	m_stcManual_Dlg_Lamp[MANUAL_GANTRY_DLG].SetBackgroundColor(RGB(239, 239, 239)); //주황
	m_stcManual_Dlg_Lamp[MANUAL_INSPECT_DLG].SetBackgroundColor(RGB(239, 239, 239)); //주황
	m_stcManual_Dlg_Lamp[MANUAL_CLAMP_DLG].SetBackgroundColor(RGB(239, 239, 239)); //주황	
	m_stcManual_Dlg_Lamp[MANUAL_STRETCH_DLG].SetBackgroundColor(RGB(239, 239, 239)); //주황
	m_stcManual_Dlg_Lamp[MANUAL_GRIPPER_Z_DLG].SetBackgroundColor(RGB(239, 239, 239)); //주황

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//								SUB 버튼 램프
	//--------------------------------------------------------------------------------------------------------
	m_stcManual_Sub_Dlg_Lamp[MANUAL_SUB_MANUAL].SubclassDlgItem(IDC_STATIC_LAMP_MANUAL, this);
	m_stcManual_Sub_Dlg_Lamp[MANUAL_SUB_FIXED_POS].SubclassDlgItem(IDC_STATIC_LAMP_FIXED_POS, this);
	
	m_stcManual_Sub_Dlg_Lamp[MANUAL_SUB_MANUAL].SetBackgroundColor(RGB(239, 239, 239)); //백그라운드
	m_stcManual_Sub_Dlg_Lamp[MANUAL_SUB_FIXED_POS].SetBackgroundColor(RGB(239, 239, 239)); //백그라운드

#ifdef GRIPPER_0
	m_btnManual[MANUAL_GRIPPER_Z_DLG].ShowWindow(FALSE);
	m_stcManual_Dlg_Lamp[MANUAL_GRIPPER_Z_DLG].ShowWindow(FALSE);
#endif

	m_pManual_Sub_Gantry_Manual = new CManual_Sub_Gantry_Manual(this);
	m_pManual_Sub_Gantry_Fixed_Pos = new CManual_Sub_Gantry_Fixed_Pos(this);

	m_pManual_Sub_Camp_Manual = new CManual_Sub_Clamp_Manual(this);
	m_pManual_Sub_Clamp_Fixed_Pos = new CManual_Sub_Clamp_Fixed_Pos(this);

	m_pManual_Sub_Stretch_Manual = new CManual_Sub_Stretch_Manual(this);
	m_pManual_Sub_Stretch_Fixed_Pos = new CManual_Sub_Stretch_Fixed_Pos(this);

	m_pManual_Sub_GripperZ_Manual = new CManual_Sub_GripperZ_Manual(this);
	m_pManual_Sub_GripperZ_Fixed_Pos = new CManual_Sub_GripperZ_Fixed_Pos(this);
}
//-----------------------------------------------------------------
void CManualDlg::ShowDlg(int nDlgNo, int nSubDlgNo)
{
	Dlg_HideWindow();

	for (int k = 0; k < MAX_MANUAL_DLG; k++)
	{
		if (k == nDlgNo)
		{
			m_stcManual_Dlg_Lamp[k].SetBackgroundColor(BTN_LAMP_ON);
		}
		else
		{
			m_stcManual_Dlg_Lamp[k].SetBackgroundColor(BTN_LAMP_OFF);
		}
	}
	for (int k = 0; k < MAX_MANUAL_SUB_DLG; k++)
	{
		if (k == nSubDlgNo)
		{
			m_stcManual_Sub_Dlg_Lamp[k].SetBackgroundColor(BTN_LAMP_ON);
		}
		else
		{
			m_stcManual_Sub_Dlg_Lamp[k].SetBackgroundColor(BTN_LAMP_OFF);
		}
	}
	switch (nDlgNo)
	{
	case MANUAL_GANTRY_DLG:
	{
		if (nSubDlgNo == MANUAL_SUB_MANUAL)
		{
			m_pManual_Sub_Gantry_Manual->ShowWindow(TRUE);
		}
		else if (nSubDlgNo == MANUAL_SUB_FIXED_POS)
		{
			m_pManual_Sub_Gantry_Fixed_Pos->ShowWindow(TRUE);
		}

		break;
	}
	case MANUAL_CLAMP_DLG:
	{
		if (nSubDlgNo == MANUAL_SUB_MANUAL)
		{
			m_pManual_Sub_Camp_Manual->ShowWindow(TRUE);
		}
		else if (nSubDlgNo == MANUAL_SUB_FIXED_POS)
		{
			m_pManual_Sub_Clamp_Fixed_Pos->ShowWindow(TRUE);
		}
		
		break;
	}
	case MANUAL_STRETCH_DLG:
	{
		if (nSubDlgNo == MANUAL_SUB_MANUAL)
		{
			m_pManual_Sub_Stretch_Manual->ShowWindow(TRUE);
		}
		else if (nSubDlgNo == MANUAL_SUB_FIXED_POS)
		{
			m_pManual_Sub_Stretch_Fixed_Pos->ShowWindow(TRUE);
		}

		break;
	}
	case MANUAL_GRIPPER_Z_DLG:
	{
		if (nSubDlgNo == MANUAL_SUB_MANUAL)
		{
			m_pManual_Sub_GripperZ_Manual->ShowWindow(TRUE);
		}
		else if (nSubDlgNo == MANUAL_SUB_FIXED_POS)
		{
			m_pManual_Sub_GripperZ_Fixed_Pos->ShowWindow(TRUE);
		}

		break;
	}
	}

	for (int k = 0; k < MAX_MANUAL_DLG; k++)
	{
		m_btnManual[k].SetFocus();
	}
	for (int k = 0; k < MAX_MANUAL_SUB_DLG; k++)
	{
		m_btnSubManual[k].SetFocus();
	}
}
//-----------------------------------------------------------------
BOOL CManualDlg::RecalcLayout()
{
	return TRUE;
}
//-----------------------------------------------------------------
BOOL CManualDlg::ShowData()
{
	return TRUE;
}
//-----------------------------------------------------------------
void	CManualDlg::ChangeUI()
{
	//저장된 데이터를 UI에 표시
}
//--------------------------------------------------------
void	CManualDlg::ChangeData()
{
	//UI에 기입한 내용을 SystemData 변수에 입력
}
//--------------------------------------------------------
void CManualDlg::Dlg_HideWindow()
{
	m_pManual_Sub_Gantry_Manual->ShowWindow(FALSE);
	m_pManual_Sub_Gantry_Fixed_Pos->ShowWindow(FALSE);

	m_pManual_Sub_Camp_Manual->ShowWindow(FALSE);
	m_pManual_Sub_Clamp_Fixed_Pos->ShowWindow(FALSE);

	m_pManual_Sub_Stretch_Manual->ShowWindow(FALSE);
	m_pManual_Sub_Stretch_Fixed_Pos->ShowWindow(FALSE);

	m_pManual_Sub_GripperZ_Manual->ShowWindow(FALSE);
	m_pManual_Sub_GripperZ_Fixed_Pos->ShowWindow(FALSE);
}
//-----------------------------------------------------------------
BOOL CManualDlg::DestroyWindow()
{
	//Gantry
	if (m_pManual_Sub_Gantry_Manual)
	{
		m_pManual_Sub_Gantry_Manual->DestroyWindow();
		delete m_pManual_Sub_Gantry_Manual;
	}

	if (m_pManual_Sub_Gantry_Fixed_Pos)
	{
		m_pManual_Sub_Gantry_Fixed_Pos->DestroyWindow();
		delete m_pManual_Sub_Gantry_Fixed_Pos;
	}

	//Clamp
	if (m_pManual_Sub_Camp_Manual)
	{
		m_pManual_Sub_Camp_Manual->DestroyWindow();
		delete m_pManual_Sub_Camp_Manual;
	}

	if (m_pManual_Sub_Clamp_Fixed_Pos)
	{
		m_pManual_Sub_Clamp_Fixed_Pos->DestroyWindow();
		delete m_pManual_Sub_Clamp_Fixed_Pos;
	}

	//Stretch
	if (m_pManual_Sub_Stretch_Manual)
	{
		m_pManual_Sub_Stretch_Manual->DestroyWindow();
		delete m_pManual_Sub_Stretch_Manual;
	}

	if (m_pManual_Sub_Stretch_Fixed_Pos)
	{
		m_pManual_Sub_Stretch_Fixed_Pos->DestroyWindow();
		delete m_pManual_Sub_Stretch_Fixed_Pos;
	}

	//GripperZ
	if (m_pManual_Sub_GripperZ_Manual)
	{
		m_pManual_Sub_GripperZ_Manual->DestroyWindow();
		delete m_pManual_Sub_GripperZ_Manual;
	}

	if (m_pManual_Sub_GripperZ_Fixed_Pos)
	{
		m_pManual_Sub_GripperZ_Fixed_Pos->DestroyWindow();
		delete m_pManual_Sub_GripperZ_Fixed_Pos;
	}

	return CDialogEx::DestroyWindow();
}
//-----------------------------------------------------------------
void CManualDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow == TRUE)
	{
		SetWindowPos(NULL, 960, 10, 960, 960, NULL);

		m_nCurrentNo = MANUAL_GANTRY_DLG;
		m_nCurrentSubNo = MANUAL_SUB_MANUAL;
		ShowDlg(m_nCurrentNo, m_nCurrentSubNo);
	}
	else
	{
	}
}
//-----------------------------------------------------------------
BOOL CManualDlg::Is_Comp_Safe_Hwnd()
{
	if (GetDlgItem(IDC_STATIC_LINE_W)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_LINE_H)->GetSafeHwnd() == NULL) return FALSE;

	if (GetDlgItem(IDC_BUTTON_MANUAL_GANTRY)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_BUTTON_MANUAL_INSPECT)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_BUTTON_MANUAL_CLAMP)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_LAMP_MANUAL_GANTRY)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_LAMP_MANUAL_INSPECT)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_LAMP_MANUAL_CLAMP)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_LAMP_MANUAL_STRETCH)->GetSafeHwnd() == NULL) return FALSE;

	if (GetDlgItem(IDC_BUTTON_MANUAL)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_BUTTON_FIXED_POS)->GetSafeHwnd() == NULL) return FALSE;

	if (GetDlgItem(IDC_BUTTON_CLOSE)->GetSafeHwnd() == NULL) return FALSE;
	return TRUE;
}
//----------------------------------------------------------------
void CManualDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (Is_Comp_Safe_Hwnd() == FALSE)
	{
		return;
	}
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	int nOffset = 5;
	int nLamp_Size = 5;
	int nBtn_Size_X = 70;
	int nBtn_Size_Y = 50;
	CRect RectBtn, RectLamp;
	CRect RectLine_W, RectLine_H;
	CRect RectSubDlg;

	//Gantry
	RectBtn.left = nOffset * 2;
	RectBtn.right = RectBtn.left + nBtn_Size_X;
	RectBtn.top = nOffset;
	RectBtn.bottom = RectBtn.top + nBtn_Size_Y;
	m_btnManual[MANUAL_GANTRY_DLG].MoveWindow(RectBtn);

	RectLamp.left = RectBtn.left;
	RectLamp.right = RectBtn.right;
	RectLamp.top = RectBtn.bottom + nOffset;
	RectLamp.bottom = RectLamp.top + nLamp_Size;
	m_stcManual_Dlg_Lamp[MANUAL_GANTRY_DLG].MoveWindow(RectLamp);

	//Inspect
	RectBtn.left	= RectBtn.right + nOffset;
	RectBtn.right	= RectBtn.left + nBtn_Size_X;
	m_btnManual[MANUAL_INSPECT_DLG].MoveWindow(RectBtn);

	RectLamp.left	= RectBtn.left;
	RectLamp.right	= RectBtn.right;
	m_stcManual_Dlg_Lamp[MANUAL_INSPECT_DLG].MoveWindow(RectLamp);
	//21.02.09 sjc del
	////Clamp
	//RectBtn.left = RectBtn.right + nOffset;
	//RectBtn.right = RectBtn.left + nBtn_Size_X;
	//m_btnManual[MANUAL_CLAMP_DLG].MoveWindow(RectBtn);

	//RectLamp.left = RectBtn.left;
	//RectLamp.right = RectBtn.right;
	//m_stcManual_Dlg_Lamp[MANUAL_CLAMP_DLG].MoveWindow(RectLamp);

	//Stretch
	RectBtn.left = RectBtn.right + nOffset;
	RectBtn.right = RectBtn.left + nBtn_Size_X;
	m_btnManual[MANUAL_STRETCH_DLG].MoveWindow(RectBtn);

	RectLamp.left = RectBtn.left;
	RectLamp.right = RectBtn.right;
	m_stcManual_Dlg_Lamp[MANUAL_STRETCH_DLG].MoveWindow(RectLamp);

	//21.02.09 sjc del
	////Pitch
	//RectBtn.left = RectBtn.right + nOffset;
	//RectBtn.right = RectBtn.left + nBtn_Size_X;
	//m_btnManual[MANUAL_PITCH_DLG].MoveWindow(RectBtn);

	//RectLamp.left = RectBtn.left;
	//RectLamp.right = RectBtn.right;
	//m_stcManual_Dlg_Lamp[MANUAL_PITCH_DLG].MoveWindow(RectLamp);


	//GripperZ
	RectBtn.left = RectBtn.right + nOffset;
	RectBtn.right = RectBtn.left + nBtn_Size_X;
	m_btnManual[MANUAL_GRIPPER_Z_DLG].MoveWindow(RectBtn);

	RectLamp.left = RectBtn.left;
	RectLamp.right = RectBtn.right;
	m_stcManual_Dlg_Lamp[MANUAL_GRIPPER_Z_DLG].MoveWindow(RectLamp);

	int nShift = 0;
#ifdef GRIPPER_0
	nShift = -(nOffset + nBtn_Size_X);
#endif

	//---------------
	RectLine_W.left		= nOffset;
	RectLine_W.top		= RectLamp.bottom + nOffset;
	RectLine_W.right	= cx - nOffset - nBtn_Size_X - nLamp_Size - nOffset - 2 - nOffset;
	RectLine_W.bottom	= RectLine_W.top + 2;
	GetDlgItem(IDC_STATIC_LINE_W)->MoveWindow(RectLine_W);

	RectLine_H.left		= RectLine_W.right + nOffset;
	RectLine_H.top		= RectLine_W.bottom + nOffset;
	RectLine_H.right	= RectLine_H.left + 2;
	RectLine_H.bottom	= cy - nOffset - nBtn_Size_Y - nOffset;
	GetDlgItem(IDC_STATIC_LINE_H)->MoveWindow(RectLine_H);
	//---------------
	RectLamp.left	= RectLine_H.right + nOffset;
	RectLamp.top	= RectLine_H.top + nOffset;
	RectLamp.right	= RectLamp.left + nBtn_Size_X;
	RectLamp.bottom = RectLamp.top + nBtn_Size_Y;
	RectBtn.left	= RectLamp.left + nLamp_Size;
	RectBtn.top		= RectLamp.top;
	RectBtn.right	= RectLamp.right + nLamp_Size;
	RectBtn.bottom	= RectLamp.bottom;	
	m_btnSubManual[MANUAL_SUB_MANUAL].MoveWindow(RectBtn);
	m_stcManual_Sub_Dlg_Lamp[MANUAL_SUB_MANUAL].MoveWindow(RectLamp);

	RectBtn.top = RectBtn.bottom + nOffset;
	RectBtn.bottom = RectBtn.top + nBtn_Size_Y;
	RectLamp.top = RectBtn.top;
	RectLamp.bottom = RectBtn.bottom;
	m_btnSubManual[MANUAL_SUB_FIXED_POS].MoveWindow(RectBtn);
	m_stcManual_Sub_Dlg_Lamp[MANUAL_SUB_FIXED_POS].MoveWindow(RectLamp);

	RectBtn.left	= cx - nOffset - nBtn_Size_X;
	RectBtn.top		= cy - nOffset - nBtn_Size_Y;
	RectBtn.right	= cx - nOffset;
	RectBtn.bottom	= cy - nOffset;
	GetDlgItem(IDC_BUTTON_CLOSE)->MoveWindow(RectBtn);

	RectSubDlg.left		= RectLine_W.left	+ nOffset;
	RectSubDlg.top		= RectLine_W.bottom + nOffset;
	RectSubDlg.right	= RectLine_H.left	- nOffset;
	RectSubDlg.bottom	= RectLine_H.bottom - nOffset;
	GetDlgItem(IDC_STATIC_SUB_DLG)->MoveWindow(RectSubDlg);

	GetDlgItem(IDC_STATIC_SUB_DLG)->GetWindowRect(&RectSubDlg);
	ScreenToClient(RectSubDlg);
	
	m_pManual_Sub_Gantry_Manual->MoveWindow(RectSubDlg);
	m_pManual_Sub_Gantry_Fixed_Pos->MoveWindow(RectSubDlg);

	m_pManual_Sub_Camp_Manual->MoveWindow(RectSubDlg);
	m_pManual_Sub_Clamp_Fixed_Pos->MoveWindow(RectSubDlg);

	m_pManual_Sub_Stretch_Manual->MoveWindow(RectSubDlg);
	m_pManual_Sub_Stretch_Fixed_Pos->MoveWindow(RectSubDlg);

	m_pManual_Sub_GripperZ_Manual->MoveWindow(RectSubDlg);
	m_pManual_Sub_GripperZ_Fixed_Pos->MoveWindow(RectSubDlg);
}
//-----------------------------------------------------------------
void CManualDlg::OnBnClickedButtonManualGantry()
{
	m_nCurrentNo = MANUAL_GANTRY_DLG;
	ShowDlg(m_nCurrentNo, m_nCurrentSubNo);
}
//-----------------------------------------------------------------
void CManualDlg::OnBnClickedButtonManualInspect()
{
	m_nCurrentNo = MANUAL_INSPECT_DLG;
	ShowDlg(m_nCurrentNo, m_nCurrentSubNo);
}
//-----------------------------------------------------------------
void CManualDlg::OnBnClickedButtonManualClamp()
{
	m_nCurrentNo = MANUAL_CLAMP_DLG;
	ShowDlg(m_nCurrentNo, m_nCurrentSubNo);
}
void CManualDlg::OnBnClickedButtonManualStretch()
{
	m_nCurrentNo = MANUAL_STRETCH_DLG;
	ShowDlg(m_nCurrentNo, m_nCurrentSubNo);
}
void CManualDlg::OnBnClickedButtonManualGripperZ()
{
	m_nCurrentNo = MANUAL_GRIPPER_Z_DLG;
	ShowDlg(m_nCurrentNo, m_nCurrentSubNo);
}
//-----------------------------------------------------------------
void CManualDlg::OnBnClickedButtonManual()
{
	m_nCurrentSubNo = MANUAL_SUB_MANUAL;
	ShowDlg(m_nCurrentNo, m_nCurrentSubNo);
}
//-----------------------------------------------------------------
void CManualDlg::OnBnClickedButtonFixedPos()
{
	m_nCurrentSubNo = MANUAL_SUB_FIXED_POS;
	ShowDlg(m_nCurrentNo, m_nCurrentSubNo);
}
//-----------------------------------------------------------------
void CManualDlg::OnBnClickedButtonClose()
{
	OnCancel();
}
//-----------------------------------------------------------------
void CManualDlg::OnCancel()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CVisionAgentDlg *pVisionAgentDlg = (CVisionAgentDlg*)theApp.m_pMainWnd;
	pVisionAgentDlg->m_bShowManualModeless = FALSE;

	Dlg_HideWindow();

	CDialogEx::OnCancel();
}
