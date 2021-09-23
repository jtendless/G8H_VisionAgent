// MachineDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentDlg.h"
#include "MachineDlg.h"
#include "afxdialogex.h"


// CMachineDlg 대화 상자

IMPLEMENT_DYNAMIC(CMachineDlg, CDialogEx)

CMachineDlg::CMachineDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VISION_AGENT_MACHINE_DIALOG, pParent)
{
	Create(IDD_VISION_AGENT_MACHINE_DIALOG, pParent);
}

CMachineDlg::~CMachineDlg()
{
	if (m_pMachineSubOriginDlg)
	{
		m_pMachineSubOriginDlg->DestroyWindow();
		delete m_pMachineSubOriginDlg;
	}

	if (m_pMachineSubJogDlg)
	{
		m_pMachineSubJogDlg->DestroyWindow();
		delete m_pMachineSubJogDlg;
	}

	if (m_pMachineSubMotorDlg)
	{
		m_pMachineSubMotorDlg->DestroyWindow();
		delete m_pMachineSubMotorDlg;
	}
}

void CMachineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMachineDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CMachineDlg::OnBnClickedButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_MACHINE_MENU_ORIGIN, &CMachineDlg::OnBnClickedButtonMachineMenuOrigin)
	ON_BN_CLICKED(IDC_BUTTON_MACHINE_MENU_JOG, &CMachineDlg::OnBnClickedButtonMachineMenuJog)
	ON_BN_CLICKED(IDC_BUTTON_MACHINE_MENU_MOTOR, &CMachineDlg::OnBnClickedButtonMachineMenuMotor)
	ON_BN_CLICKED(IDC_BUTTON_SUB_1, &CMachineDlg::OnBnClickedButtonSub1)
	ON_BN_CLICKED(IDC_BUTTON_SUB_2, &CMachineDlg::OnBnClickedButtonSub2)
	ON_BN_CLICKED(IDC_BUTTON_SUB_3, &CMachineDlg::OnBnClickedButtonSub3)
	ON_BN_CLICKED(IDC_BUTTON_MACHINE_SAVE, &CMachineDlg::OnBnClickedButtonMachineSave)
	ON_BN_CLICKED(IDC_BUTTON_SUB_4, &CMachineDlg::OnBnClickedButtonSub4)
END_MESSAGE_MAP()


BOOL CMachineDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	Dialog_Init();
	return TRUE;
}

// CMachineDlg 메시지 처리기입니다.
//-----------------------------------------------------------------
void CMachineDlg::Dialog_Init()
{
	m_btnMachine[MACHINE_ORIGIN_DLG].SubclassDlgItem(IDC_BUTTON_MACHINE_MENU_ORIGIN, this);
	m_btnMachine[MACHINE_JOG_DLG].SubclassDlgItem(IDC_BUTTON_MACHINE_MENU_JOG, this);
	m_btnMachine[MACHINE_MOTOR_DLG].SubclassDlgItem(IDC_BUTTON_MACHINE_MENU_MOTOR, this);
	
	m_stcMachine_Dlg_Lamp[MACHINE_ORIGIN_DLG].SubclassDlgItem(IDC_LAMP_MACHINE_MENU_ORIGIN, this);
	m_stcMachine_Dlg_Lamp[MACHINE_JOG_DLG].SubclassDlgItem(IDC_LAMP_MACHINE_MENU_JOG, this);
	m_stcMachine_Dlg_Lamp[MACHINE_MOTOR_DLG].SubclassDlgItem(IDC_LAMP_MACHINE_MENU_MOTOR, this);

	m_btnSubMachine[MACHINE_SUB_PAGE_1].SubclassDlgItem(IDC_BUTTON_SUB_1, this);
	m_btnSubMachine[MACHINE_SUB_PAGE_2].SubclassDlgItem(IDC_BUTTON_SUB_2, this);
	m_btnSubMachine[MACHINE_SUB_PAGE_3].SubclassDlgItem(IDC_BUTTON_SUB_3, this);
	m_btnSubMachine[MACHINE_SUB_PAGE_4].SubclassDlgItem(IDC_BUTTON_SUB_4, this);

	m_stcMachine_Sub_Dlg_Lamp[MACHINE_SUB_PAGE_1].SubclassDlgItem(IDC_LAMP_SUB_1, this);
	m_stcMachine_Sub_Dlg_Lamp[MACHINE_SUB_PAGE_2].SubclassDlgItem(IDC_LAMP_SUB_2, this);
	m_stcMachine_Sub_Dlg_Lamp[MACHINE_SUB_PAGE_3].SubclassDlgItem(IDC_LAMP_SUB_3, this);
	m_stcMachine_Sub_Dlg_Lamp[MACHINE_SUB_PAGE_4].SubclassDlgItem(IDC_LAMP_SUB_4, this);

	m_stcMachine_Dlg_Lamp[MACHINE_ORIGIN_DLG].SetBackgroundColor(BTN_LAMP_OFF);
	m_stcMachine_Dlg_Lamp[MACHINE_JOG_DLG].SetBackgroundColor(BTN_LAMP_OFF);
	m_stcMachine_Dlg_Lamp[MACHINE_MOTOR_DLG].SetBackgroundColor(BTN_LAMP_OFF);

	m_stcMachine_Sub_Dlg_Lamp[MACHINE_SUB_PAGE_1].SetBackgroundColor(BTN_LAMP_OFF); //백그라운드
	m_stcMachine_Sub_Dlg_Lamp[MACHINE_SUB_PAGE_2].SetBackgroundColor(BTN_LAMP_OFF); //백그라운드
	m_stcMachine_Sub_Dlg_Lamp[MACHINE_SUB_PAGE_3].SetBackgroundColor(BTN_LAMP_OFF); //백그라운드
	m_stcMachine_Sub_Dlg_Lamp[MACHINE_SUB_PAGE_4].SetBackgroundColor(BTN_LAMP_OFF); //백그라운드

	m_pMachineSubOriginDlg = new CVisionAgentMachineOriginDlg(this);
	m_pMachineSubJogDlg = new CVisionAgentMachineJogDlg(this);
	m_pMachineSubMotorDlg = new CVisionAgentMachineMotorDlg(this);
}
//-----------------------------------------------------------------
void CMachineDlg::ShowDlg(int nDlgNo, int nSubDlgNo)
{
	Dlg_HideWindow();

	for (int k = 0; k < MAX_MACHINE_DLG; k++)
	{
		if (k == nDlgNo)
		{
			m_stcMachine_Dlg_Lamp[k].SetBackgroundColor(BTN_LAMP_ON);
		}
		else
		{
			m_stcMachine_Dlg_Lamp[k].SetBackgroundColor(BTN_LAMP_OFF);
		}
	}
	for (int k = 0; k < MAX_MACHINE_SUB_DLG; k++)
	{
		if (k == nSubDlgNo)
		{
			m_stcMachine_Sub_Dlg_Lamp[k].SetBackgroundColor(BTN_LAMP_ON);
		}
		else
		{
			m_stcMachine_Sub_Dlg_Lamp[k].SetBackgroundColor(BTN_LAMP_OFF);
		}
	}

	switch (nDlgNo)
	{
	case MACHINE_ORIGIN_DLG:
	{
		GetDlgItem(IDC_LAMP_SUB_1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LAMP_SUB_2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LAMP_SUB_3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LAMP_SUB_4)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_BUTTON_SUB_1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_SUB_2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_SUB_3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_SUB_4)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_BUTTON_SUB_1)->SetWindowTextW(_T("ORIGIN"));
		if (nSubDlgNo == MACHINE_SUB_PAGE_1)
		{
			m_pMachineSubOriginDlg->ShowWindow(SW_SHOW);
		}
		break;
	}
	case MACHINE_JOG_DLG:
	{
		GetDlgItem(IDC_LAMP_SUB_1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LAMP_SUB_2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LAMP_SUB_3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LAMP_SUB_4)->ShowWindow(SW_HIDE);
				
		GetDlgItem(IDC_BUTTON_SUB_1)->ShowWindow(SW_SHOW); 
		GetDlgItem(IDC_BUTTON_SUB_2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_SUB_3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_SUB_4)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_BUTTON_SUB_1)->SetWindowTextW(_T("JOG"));
		if (nSubDlgNo == MACHINE_SUB_PAGE_1)
		{
			m_pMachineSubJogDlg->ShowWindow(SW_SHOW);
		}
		break;
	}
	case MACHINE_MOTOR_DLG:
	{
		GetDlgItem(IDC_LAMP_SUB_1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_LAMP_SUB_2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LAMP_SUB_3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_LAMP_SUB_4)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_BUTTON_SUB_1)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_SUB_2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_SUB_3)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_SUB_4)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_BUTTON_SUB_1)->SetWindowTextW(_T("MOTOR"));
		if (nSubDlgNo == MACHINE_SUB_PAGE_1)
		{
			m_pMachineSubMotorDlg->ShowWindow(SW_SHOW);
		}
		break;
	}
	}
	for (int k = 0; k < MAX_MACHINE_DLG; k++)
	{
		m_btnMachine[k].SetFocus();
	}
	for (int k = 0; k < MAX_MACHINE_SUB_DLG; k++)
	{
		m_btnSubMachine[k].SetFocus();
	}
}
//-----------------------------------------------------------------
BOOL CMachineDlg::RecalcLayout()
{
	return TRUE;
}
//-----------------------------------------------------------------
BOOL CMachineDlg::ShowData()
{
	return TRUE;
}
//-----------------------------------------------------------------
void	CMachineDlg::ChangeUI()
{
	//저장된 데이터를 UI에 표시
}
//--------------------------------------------------------
void	CMachineDlg::CheckData()
{
	switch (m_nCurrentNo)
	{
	case MACHINE_ORIGIN_DLG:
	case MACHINE_JOG_DLG:
		break;
	case MACHINE_MOTOR_DLG:
		m_pMachineSubMotorDlg->CheckChangeData();
		break;
	}
}
//--------------------------------------------------------
void CMachineDlg::Dlg_HideWindow()
{
	m_pMachineSubOriginDlg->ShowWindow(SW_HIDE);
	m_pMachineSubJogDlg->ShowWindow(SW_HIDE);
	m_pMachineSubMotorDlg->ShowWindow(SW_HIDE);
}
//-----------------------------------------------------------------
BOOL CMachineDlg::DestroyWindow()
{

	
	return CDialogEx::DestroyWindow();
}
//-----------------------------------------------------------------
void CMachineDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow == TRUE) {
		SetWindowPos(NULL, 960, 10, 960, 960, NULL);

		m_nCurrentNo = MACHINE_ORIGIN_DLG;
		m_nCurrentSubNo = MACHINE_SUB_PAGE_1;
		ShowDlg(m_nCurrentNo, m_nCurrentSubNo);
	}
	else if (bShow == FALSE)
	{
		Dlg_HideWindow();
	}
	
}
//-----------------------------------------------------------------
BOOL CMachineDlg::Is_Comp_Safe_Hwnd()
{
	if (GetDlgItem(IDC_STATIC_LINE_W)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_LINE_H)->GetSafeHwnd() == NULL) return FALSE;

	if (GetDlgItem(IDC_BUTTON_MACHINE_MENU_ORIGIN)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_BUTTON_MACHINE_MENU_JOG)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_BUTTON_MACHINE_MENU_MOTOR)->GetSafeHwnd() == NULL) return FALSE;

	if (GetDlgItem(IDC_LAMP_MACHINE_MENU_ORIGIN)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_LAMP_MACHINE_MENU_JOG)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_LAMP_MACHINE_MENU_MOTOR)->GetSafeHwnd() == NULL) return FALSE;

	if (GetDlgItem(IDC_LAMP_SUB_1)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_LAMP_SUB_2)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_LAMP_SUB_3)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_LAMP_SUB_4)->GetSafeHwnd() == NULL) return FALSE;

	if (GetDlgItem(IDC_BUTTON_SUB_1)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_BUTTON_SUB_2)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_BUTTON_SUB_3)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_BUTTON_SUB_4)->GetSafeHwnd() == NULL) return FALSE;

	if (GetDlgItem(IDC_STATIC_SUB_DLG)->GetSafeHwnd() == NULL) return FALSE;	
	
	if (GetDlgItem(IDC_BUTTON_CLOSE)->GetSafeHwnd() == NULL) return FALSE;
	return TRUE;
}
//----------------------------------------------------------------
void CMachineDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (Is_Comp_Safe_Hwnd() == FALSE)
	{
		return;
	}
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	int nOffset = 5;
	int nBtn_Size_X = 100;
	int nBtn_Size_Y = 50;
	CRect RectBtn, RectLamp, RectSubDlg;

	RectBtn.left	= cx - nBtn_Size_X - nOffset;
	RectBtn.top		= cy - nBtn_Size_Y - nOffset;
	RectBtn.right	= cx - nOffset;
	RectBtn.bottom	= cy - nOffset;
	GetDlgItem(IDC_BUTTON_CLOSE)->MoveWindow(RectBtn);

	int nLamp_Size_Y = 3;
	RectBtn.left = nOffset;
	RectBtn.top = nOffset;
	RectBtn.right = RectBtn.left + nBtn_Size_X;
	RectBtn.bottom = RectBtn.top + nBtn_Size_Y;

	RectLamp.left = RectBtn.left;
	RectLamp.top = RectBtn.bottom;
	RectLamp.right = RectBtn.right;
	RectLamp.bottom = RectLamp.top + nLamp_Size_Y;
	GetDlgItem(IDC_BUTTON_MACHINE_MENU_ORIGIN)->MoveWindow(RectBtn);
	GetDlgItem(IDC_LAMP_MACHINE_MENU_ORIGIN)->MoveWindow(RectLamp);

	RectBtn.left = RectBtn.right + nOffset;
	RectBtn.right = RectBtn.left + nBtn_Size_X;
	RectLamp.left = RectBtn.left;
	RectLamp.right = RectBtn.right;
	GetDlgItem(IDC_BUTTON_MACHINE_MENU_JOG)->MoveWindow(RectBtn);
	GetDlgItem(IDC_LAMP_MACHINE_MENU_JOG)->MoveWindow(RectLamp);

	RectBtn.left = RectBtn.right + nOffset;
	RectBtn.right = RectBtn.left + nBtn_Size_X;
	RectLamp.left = RectBtn.left;
	RectLamp.right = RectBtn.right;
	GetDlgItem(IDC_BUTTON_MACHINE_MENU_MOTOR)->MoveWindow(RectBtn);
	GetDlgItem(IDC_LAMP_MACHINE_MENU_MOTOR)->MoveWindow(RectLamp);

	//-------------
	RectBtn.left	= cx - nOffset - nBtn_Size_X;
	RectBtn.top		= nOffset + (nBtn_Size_Y * 1.5);
	RectBtn.right	= RectBtn.left + nBtn_Size_X;
	RectBtn.bottom	= RectBtn.top + nBtn_Size_Y;

	RectLamp.left	= RectBtn.left - nLamp_Size_Y;
	RectLamp.top	= RectBtn.top;
	RectLamp.right	= RectBtn.left;
	RectLamp.bottom = RectBtn.bottom;
	GetDlgItem(IDC_BUTTON_SUB_1)->MoveWindow(RectBtn);
	GetDlgItem(IDC_LAMP_SUB_1)->MoveWindow(RectLamp);

	RectBtn.top		= RectBtn.bottom + nOffset;
	RectBtn.bottom	= RectBtn.top + nBtn_Size_Y;

	RectLamp.top	= RectBtn.top;
	RectLamp.bottom = RectBtn.bottom;
	GetDlgItem(IDC_BUTTON_SUB_2)->MoveWindow(RectBtn);
	GetDlgItem(IDC_LAMP_SUB_2)->MoveWindow(RectLamp);

	RectBtn.top = RectBtn.bottom + nOffset;
	RectBtn.bottom = RectBtn.top + nBtn_Size_Y;

	RectLamp.top = RectBtn.top;
	RectLamp.bottom = RectBtn.bottom;
	GetDlgItem(IDC_BUTTON_SUB_3)->MoveWindow(RectBtn);
	GetDlgItem(IDC_LAMP_SUB_3)->MoveWindow(RectLamp);

	RectBtn.top = RectBtn.bottom + nOffset;
	RectBtn.bottom = RectBtn.top + nBtn_Size_Y;

	RectLamp.top = RectBtn.top;
	RectLamp.bottom = RectBtn.bottom;
	GetDlgItem(IDC_BUTTON_SUB_4)->MoveWindow(RectBtn);
	GetDlgItem(IDC_LAMP_SUB_4)->MoveWindow(RectLamp);
	//-------------
	GetDlgItem(IDC_STATIC_SUB_DLG)->GetWindowRect(&RectSubDlg);
	ScreenToClient(RectSubDlg);

	m_pMachineSubOriginDlg->MoveWindow(RectSubDlg);
	m_pMachineSubJogDlg->MoveWindow(RectSubDlg);
	m_pMachineSubMotorDlg->MoveWindow(RectSubDlg);
}
//-----------------------------------------------------------------
void CMachineDlg::OnBnClickedButtonClose()
{
	OnCancel();
}
//-----------------------------------------------------------------
void CMachineDlg::OnCancel()
{
	CVisionAgentDlg *pVisionAgentDlg = (CVisionAgentDlg*)theApp.m_pMainWnd;
	pVisionAgentDlg->m_bShowMachineModeless = FALSE;

	Dlg_HideWindow();

	CDialogEx::OnCancel();
}
//-----------------------------------------------------------------
void CMachineDlg::OnBnClickedButtonMachineMenuOrigin()
{
	m_nCurrentNo = MACHINE_ORIGIN_DLG;
	ShowDlg(m_nCurrentNo, m_nCurrentSubNo);
}
//-----------------------------------------------------------------
void CMachineDlg::OnBnClickedButtonMachineMenuJog()
{
	m_nCurrentNo = MACHINE_JOG_DLG;
	ShowDlg(m_nCurrentNo, m_nCurrentSubNo);
}
//-----------------------------------------------------------------
void CMachineDlg::OnBnClickedButtonMachineMenuMotor()
{
	m_nCurrentNo = MACHINE_MOTOR_DLG;
	ShowDlg(m_nCurrentNo, m_nCurrentSubNo);
}
//-----------------------------------------------------------------
void CMachineDlg::OnBnClickedButtonSub1()
{
	m_nCurrentSubNo = MACHINE_SUB_PAGE_1;
	ShowDlg(m_nCurrentNo, m_nCurrentSubNo);
}
//-----------------------------------------------------------------
void CMachineDlg::OnBnClickedButtonSub2()
{
	m_nCurrentSubNo = MACHINE_SUB_PAGE_2;
	ShowDlg(m_nCurrentNo, m_nCurrentSubNo);
}
//-----------------------------------------------------------------
void CMachineDlg::OnBnClickedButtonSub3()
{
	m_nCurrentSubNo = MACHINE_SUB_PAGE_3;
	ShowDlg(m_nCurrentNo, m_nCurrentSubNo);
}
//-----------------------------------------------------------------
void CMachineDlg::OnBnClickedButtonSub4()
{
	m_nCurrentSubNo = MACHINE_SUB_PAGE_4;
	ShowDlg(m_nCurrentNo, m_nCurrentSubNo);
}


void CMachineDlg::OnBnClickedButtonMachineSave()
{
	DWORD Result;

	Result = AfxMessageBox(_T("Save?"), MB_OKCANCEL);

	BeginWaitCursor();
	if (Result == IDOK)
	{
		CheckData();

		switch (m_nCurrentNo)
		{
		case MACHINE_ORIGIN_DLG:
		case MACHINE_JOG_DLG:
			break;
		case MACHINE_MOTOR_DLG:
			CMachineData::m_MachineDataMotor.Save();
			break;
		}
	}
	EndWaitCursor();
}

