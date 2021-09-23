// SystemDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentDlg.h"
#include "SystemDlg.h"
#include "afxdialogex.h"

#include "SystemOptionSubDlg.h"
#include "SystemMachineCommunicationSubDlg.h"
#include "SystemSaftySubDlg.h"
#include "VisionAgentSystem_CoordinateDlg.h"
#include "VisionAgentSystem_ESCDlg.h"

// CSystemDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CSystemDlg, CDialogEx)

CSystemDlg::CSystemDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_VISION_AGENT_SYSTEM_DIALOG, pParent)
{
	Create(IDD_VISION_AGENT_SYSTEM_DIALOG, pParent);
	m_nCurrentNo = 0;
}

CSystemDlg::~CSystemDlg()
{
	if (m_pSystemOptionSubDlg)
	{
		m_pSystemOptionSubDlg->DestroyWindow();
		delete m_pSystemOptionSubDlg;
	}	

	if (m_pSystemSaftySubDlg)
	{
		m_pSystemSaftySubDlg->DestroyWindow();
		delete m_pSystemSaftySubDlg;
	}

	if (m_pSystemCoordinateDlg)
	{
		m_pSystemCoordinateDlg->DestroyWindow();
		delete m_pSystemCoordinateDlg;
	}
	if (m_pSystemESCDlg)
	{
		m_pSystemESCDlg->DestroyWindow();
		delete m_pSystemESCDlg;
	}
}

void CSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSystemDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SUB_PAGE1, &CSystemDlg::OnBnClickedButtonSubPage1)
	ON_BN_CLICKED(IDC_BUTTON_SUB_PAGE2, &CSystemDlg::OnBnClickedButtonSubPage2)
	
	ON_BN_CLICKED(IDC_BTN_SYSTEM_CLOSE, &CSystemDlg::OnBnClickedBtnSystemClose)
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()	
	ON_BN_CLICKED(IDC_BUTTON_SYSTEM_SAFTY, &CSystemDlg::OnBnClickedButtonSystemSafty)
	ON_BN_CLICKED(IDC_BUTTON_SYSTEM_OPTION, &CSystemDlg::OnBnClickedButtonSystemOption)
	ON_BN_CLICKED(IDC_BUTTON_SYSTEM_COORDINATE, &CSystemDlg::OnBnClickedButtonSystemCoordinate)
	ON_BN_CLICKED(IDC_BTN_SYSTEM_SAVE, &CSystemDlg::OnBnClickedBtnSystemSave)
	ON_BN_CLICKED(IDC_BUTTON_SYSTEM_ESC, &CSystemDlg::OnBnClickedButtonSystemEsc)
	ON_BN_CLICKED(IDC_BUTTON_SYSTEM_OPTION2, &CSystemDlg::OnBnClickedButtonSystemOption2)
END_MESSAGE_MAP()

// CSystemDlg 메시지 처리기입니다.
//-------------------------------------------------------------------------------
BOOL CSystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	Dialog_Init();	
	return TRUE; 
}
//-------------------------------------------------------------------------------

void CSystemDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	SetWindowPos(NULL, 960, 10, 960, 960, NULL); 
}
//----------------------------------------------------------------------------
void CSystemDlg::OnBnClickedBtnSystemClose()
{
	CVisionAgentDlg *pVisionAgentDlg;
	pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	pVisionAgentDlg->m_bShowSystemModeless = FALSE;

	OnCancel();
}
//----------------------------------------------------------------------------
void CSystemDlg::OnCancel()
{
	CVisionAgentDlg *pVisionAgentDlg = (CVisionAgentDlg*)theApp.m_pMainWnd;
	pVisionAgentDlg->m_bShowSystemModeless = FALSE;
	CDialogEx::OnCancel();
}
//----------------------------------------------------------------------------
void CSystemDlg::Dialog_Init()
{	
	//m_btnSystem[SYSTEM_COMM_DLG].SubclassDlgItem(IDC_BUTTON_SYSTEM_COMM, this);	
	//m_stcSystem_Dlg_Lamp[SYSTEM_COMM_DLG].SubclassDlgItem(IDC_STATIC_SYSTEM_COMM_LAMP, this);
	//m_stcSystem_Dlg_Lamp[SYSTEM_COMM_DLG].SetBackgroundColor(BTN_LAMP_OFF);
	//--------------------
	m_btnSystem[SYSTEM_SAFTY_DLG].SubclassDlgItem(IDC_BUTTON_SYSTEM_SAFTY, this);
	m_stcSystem_Dlg_Lamp[SYSTEM_SAFTY_DLG].SubclassDlgItem(IDC_STATIC_SYSTEM_SAFTY_LAMP, this);
	m_stcSystem_Dlg_Lamp[SYSTEM_SAFTY_DLG].SetBackgroundColor(BTN_LAMP_OFF);
	//--------------------
	m_btnSystem[SYSTEM_OPTION_DLG].SubclassDlgItem(IDC_BUTTON_SYSTEM_OPTION2, this);
	m_stcSystem_Dlg_Lamp[SYSTEM_OPTION_DLG].SubclassDlgItem(IDC_STATIC_SYSTEM_OPTION_LAMP, this);
	m_stcSystem_Dlg_Lamp[SYSTEM_OPTION_DLG].SetBackgroundColor(BTN_LAMP_OFF);
	//--------------------
	m_btnSystem[SYSTEM_COORDINATE_DLG].SubclassDlgItem(IDC_BUTTON_SYSTEM_COORDINATE, this);
	m_stcSystem_Dlg_Lamp[SYSTEM_COORDINATE_DLG].SubclassDlgItem(IDC_STATIC_SYSTEM_COORDINATE_LAMP, this);
	m_stcSystem_Dlg_Lamp[SYSTEM_COORDINATE_DLG].SetBackgroundColor(BTN_LAMP_OFF);
	//--------------------21.04.09 SJC
	m_btnSystem[SYSTEM_ESC_DLG].SubclassDlgItem(IDC_BUTTON_SYSTEM_ESC, this);
	m_stcSystem_Dlg_Lamp[SYSTEM_ESC_DLG].SubclassDlgItem(IDC_STATIC_SYSTEM_ESC_LAMP, this);
	m_stcSystem_Dlg_Lamp[SYSTEM_ESC_DLG].SetBackgroundColor(BTN_LAMP_OFF);
	//--------------------
	m_btnSubSystem[SYSTEM_SUB_PAGE1_DLG].SubclassDlgItem(IDC_BUTTON_SUB_PAGE1, this);
	m_stcSystem_Sub_Dlg_Lamp[SYSTEM_SUB_PAGE1_DLG].SubclassDlgItem(IDC_STATIC_SUB_PAGE1_LAMP, this);
	m_stcSystem_Sub_Dlg_Lamp[SYSTEM_SUB_PAGE1_DLG].SetBackgroundColor(BTN_LAMP_OFF);
	//--------------------
	m_btnSubSystem[SYSTEM_SUB_PAGE2_DLG].SubclassDlgItem(IDC_BUTTON_SUB_PAGE2, this);
	m_stcSystem_Sub_Dlg_Lamp[SYSTEM_SUB_PAGE2_DLG].SubclassDlgItem(IDC_STATIC_SUB_PAGE2_LAMP, this);
	m_stcSystem_Sub_Dlg_Lamp[SYSTEM_SUB_PAGE2_DLG].SetBackgroundColor(BTN_LAMP_OFF);

	m_pSystemSaftySubDlg = new CSystemSaftySubDlg(this);
	m_pSystemOptionSubDlg = new CSystemOptionSubDlg(this);		
	m_pSystemCoordinateDlg = new CVisionAgentSystem_CoordinateDlg(this);
	m_pSystemESCDlg = new CVisionAgentSystem_ESCDlg(this);//21.04.09
}
//----------------------------------------------------------------------------
void CSystemDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (Is_Comp_Safe_Hwnd() == FALSE) return;

	CRect	RectMainBtn, RectSubBtn;
	CRect	RectMainLamp, RectSubLamp;
	CRect	RectMainLine, RectSubLine;
	CRect	RectSubDlg, RectCloseBtn;
	int		nOffset = 5;
	int		nBtn_Size_X, nBtn_Size_Y;
	int		nLamp_Size = 5;

	nBtn_Size_X = 100;
	nBtn_Size_Y = 50;

	RectMainBtn.left = nOffset;
	RectMainBtn.top = nOffset;
	RectMainBtn.right = RectMainBtn.left + nBtn_Size_X;
	RectMainBtn.bottom = RectMainBtn.top + nBtn_Size_Y;

	RectMainLamp.left = RectMainBtn.left;
	RectMainLamp.top = RectMainBtn.top + nLamp_Size;
	RectMainLamp.right = RectMainBtn.right;
	RectMainLamp.bottom = RectMainBtn.bottom + nLamp_Size;

	RectMainLine.left	= nOffset;
	RectMainLine.top	= RectMainLamp.bottom + nOffset;
	RectMainLine.right	= cx - nBtn_Size_X - nLamp_Size - (nOffset * 10);
	RectMainLine.bottom = RectMainLine.top + 2;

	RectSubLine.left	= RectMainLine.right + (nOffset * 2);
	RectSubLine.top		= RectMainLine.bottom + nOffset;
	RectSubLine.right	= RectSubLine.left + 2;
	RectSubLine.bottom = cy - nBtn_Size_Y - nOffset;

	RectSubLamp.left	= RectSubLine.right + nOffset;
	RectSubLamp.top		= RectSubLine.top + nOffset;
	RectSubLamp.right	= RectSubLamp.left + nBtn_Size_X;
	RectSubLamp.bottom	= RectSubLamp.top + nBtn_Size_Y;

	RectSubBtn.left		= RectSubLamp.left + nLamp_Size;
	RectSubBtn.top		= RectSubLamp.top;
	RectSubBtn.right	= RectSubBtn.left + nBtn_Size_X;
	RectSubBtn.bottom	= RectSubLamp.bottom;

	RectSubDlg.left		= RectMainLine.left + nOffset;
	RectSubDlg.top		= RectSubLine.top + nOffset;
	RectSubDlg.right	= RectMainLine.right - nOffset;
	RectSubDlg.bottom	= RectSubLine.bottom - nOffset;

	RectCloseBtn.left	= cx - nOffset - nBtn_Size_X;
	RectCloseBtn.top	= cy - nOffset - nBtn_Size_Y;
	RectCloseBtn.right	= RectCloseBtn.left + nBtn_Size_X;
	RectCloseBtn.bottom = RectCloseBtn.top + nBtn_Size_Y;
	//Main Btn Area
	GetDlgItem(IDC_STATIC_LINE_W)->MoveWindow(RectMainLine);

	//RectMainBtn.left = RectMainBtn.left;
	//RectMainBtn.right = RectMainBtn.right;
	//GetDlgItem(IDC_BUTTON_SYSTEM_COMM)->MoveWindow(RectMainBtn);

	//RectMainLamp.left = RectMainLamp.left;
	//RectMainLamp.right = RectMainLamp.right;
	//GetDlgItem(IDC_STATIC_SYSTEM_COMM_LAMP)->MoveWindow(RectMainLamp);

	RectMainBtn.left = RectMainBtn.left;
	RectMainBtn.right = RectMainBtn.right;
	GetDlgItem(IDC_BUTTON_SYSTEM_SAFTY)->MoveWindow(RectMainBtn);

	RectMainLamp.left = RectMainLamp.left;
	RectMainLamp.right = RectMainLamp.right;
	GetDlgItem(IDC_STATIC_SYSTEM_SAFTY_LAMP)->MoveWindow(RectMainLamp);

	RectMainBtn.left = RectMainBtn.right + nOffset;
	RectMainBtn.right = RectMainBtn.left + nBtn_Size_X;
	GetDlgItem(IDC_BUTTON_SYSTEM_OPTION2)->MoveWindow(RectMainBtn);

	RectMainLamp.left = RectMainLamp.right + nOffset;
	RectMainLamp.right = RectMainLamp.left + nBtn_Size_X;
	GetDlgItem(IDC_STATIC_SYSTEM_OPTION_LAMP)->MoveWindow(RectMainLamp);

	RectMainBtn.left = RectMainBtn.right + nOffset;
	RectMainBtn.right = RectMainBtn.left + nBtn_Size_X;
	GetDlgItem(IDC_BUTTON_SYSTEM_COORDINATE)->MoveWindow(RectMainBtn);

	RectMainLamp.left = RectMainLamp.right + nOffset;
	RectMainLamp.right = RectMainLamp.left + nBtn_Size_X;
	GetDlgItem(IDC_STATIC_SYSTEM_COORDINATE_LAMP)->MoveWindow(RectMainLamp);

	RectMainBtn.left = RectMainBtn.right + nOffset;
	RectMainBtn.right = RectMainBtn.left + nBtn_Size_X;
	GetDlgItem(IDC_BUTTON_SYSTEM_ESC)->MoveWindow(RectMainBtn);

	RectMainLamp.left = RectMainLamp.right + nOffset;
	RectMainLamp.right = RectMainLamp.left + nBtn_Size_X;
	GetDlgItem(IDC_STATIC_SYSTEM_ESC_LAMP)->MoveWindow(RectMainLamp);

	//Sub Btn Area
	GetDlgItem(IDC_STATIC_LINE_H)->MoveWindow(RectSubLine);

	RectMainBtn.top = RectMainBtn.top;
	RectMainBtn.bottom = RectMainBtn.bottom;
	GetDlgItem(IDC_BUTTON_SUB_PAGE1)->MoveWindow(RectSubBtn);

	RectSubLamp.top = RectSubLamp.top;
	RectSubLamp.bottom = RectSubLamp.bottom;
	GetDlgItem(IDC_STATIC_SUB_PAGE1_LAMP)->MoveWindow(RectSubLamp);

	RectSubBtn.top = RectSubBtn.bottom + nOffset;
	RectSubBtn.bottom = RectSubBtn.top + nBtn_Size_Y;
	GetDlgItem(IDC_BUTTON_SUB_PAGE2)->MoveWindow(RectSubBtn);

	RectSubLamp.top = RectSubLamp.bottom + nOffset;
	RectSubLamp.bottom = RectSubLamp.top + nBtn_Size_Y;
	GetDlgItem(IDC_STATIC_SUB_PAGE2_LAMP)->MoveWindow(RectSubLamp);

	GetDlgItem(IDC_STATIC_SUB_DLG)->MoveWindow(RectSubDlg);

	GetDlgItem(IDC_BTN_SYSTEM_CLOSE)->MoveWindow(RectCloseBtn);

	m_pSystemSaftySubDlg->MoveWindow(RectSubDlg);
	m_pSystemOptionSubDlg->MoveWindow(RectSubDlg);		
	m_pSystemCoordinateDlg->MoveWindow(RectSubDlg);
	m_pSystemESCDlg->MoveWindow(RectSubDlg);//21.04.09 SJC

	ShowDlg(m_nCurrentNo, m_nCurrentSubNo);
}
//----------------------------------------------------------------------------
BOOL CSystemDlg::Is_Comp_Safe_Hwnd(){
	
	if (GetDlgItem(IDC_BUTTON_SYSTEM_SAFTY)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_SYSTEM_SAFTY_LAMP)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_BUTTON_SYSTEM_OPTION2)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_SYSTEM_OPTION_LAMP)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_BUTTON_SYSTEM_COORDINATE)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_SYSTEM_COORDINATE_LAMP)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_BUTTON_SYSTEM_ESC)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_SYSTEM_ESC_LAMP)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_BUTTON_SUB_PAGE1)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_SUB_PAGE1_LAMP)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_BUTTON_SUB_PAGE2)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_SUB_PAGE2_LAMP)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_LINE_W)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_LINE_H)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_STATIC_SUB_DLG)->GetSafeHwnd() == NULL) return FALSE;
	if (GetDlgItem(IDC_BTN_SYSTEM_CLOSE)->GetSafeHwnd() == NULL) return FALSE;

	return TRUE;
}
//----------------------------------------------------------------------------
void CSystemDlg::ShowDlg(int nDlgNo, int nSubDlgNo)
{
	Dlg_HideWindow();

	for (int k = 0; k < MAX_SYSTEM_DLG; k++)
	{
		if (k == nDlgNo)
		{
			m_stcSystem_Dlg_Lamp[k].SetBackgroundColor(BTN_LAMP_ON);
		}
		else
		{
			m_stcSystem_Dlg_Lamp[k].SetBackgroundColor(BTN_LAMP_OFF);
		}
	}
	for (int k = 0; k < MAX_SYSTEM_SUB_DLG; k++)
	{
		if (k == nSubDlgNo)
		{
			m_stcSystem_Sub_Dlg_Lamp[k].SetBackgroundColor(BTN_LAMP_ON);
		}
		else
		{
			m_stcSystem_Sub_Dlg_Lamp[k].SetBackgroundColor(BTN_LAMP_OFF);
		}
	}
	switch (nDlgNo)
	{
	case SYSTEM_SAFTY_DLG:
	{
		if (nSubDlgNo == SYSTEM_SUB_PAGE1_DLG)
		{
			m_pSystemSaftySubDlg->ShowWindow(TRUE);
		}
		else if (nSubDlgNo == SYSTEM_SUB_PAGE2_DLG)
		{
		}

		break;
	}
	case SYSTEM_OPTION_DLG:
	{
		if (nSubDlgNo == SYSTEM_SUB_PAGE1_DLG)
		{
			m_pSystemOptionSubDlg->ShowWindow(TRUE);
		}
		else if (nSubDlgNo == SYSTEM_SUB_PAGE2_DLG)
		{
		}		

		break;
	}
	case SYSTEM_COORDINATE_DLG:
	{
		if (nSubDlgNo == SYSTEM_SUB_PAGE1_DLG)
		{
			m_pSystemCoordinateDlg->ShowWindow(TRUE);
		}
		else if (nSubDlgNo == SYSTEM_SUB_PAGE2_DLG)
		{
		}

		break;
	}
	case SYSTEM_ESC_DLG:
	{
		if (nSubDlgNo == SYSTEM_SUB_PAGE1_DLG)
		{
			m_pSystemESCDlg->ShowWindow(TRUE);
		}

		break;
	}
	}
	for (int k = 0; k < MAX_SYSTEM_DLG; k++)
	{
		m_btnSystem[k].SetFocus();
	}
	
	for (int k = 0; k < MAX_SYSTEM_SUB_DLG; k++)
	{
		m_btnSubSystem[k].SetFocus();
	}
}
//----------------------------------------------------------------------------
BOOL CSystemDlg::OnEraseBkgnd()
{
	return FALSE; // 깜박임 방지
}
//----------------------------------------------------------------------------
BOOL CSystemDlg::RecalcLayout()
{
	return TRUE;
}
//----------------------------------------------------------------------------
BOOL CSystemDlg::ShowData()
{
	return TRUE;
}
//----------------------------------------------------------------------------
void	CSystemDlg::ChangeUI()
{
	//저장된 데이터를 UI에 표시
}
//--------------------------------------------------------
void	CSystemDlg::ChangeData()
{
	//UI에 기입한 내용을 SystemData 변수에 입력
}
//--------------------------------------------------------
void CSystemDlg::Dlg_HideWindow()
{
	m_pSystemOptionSubDlg->ShowWindow(SW_HIDE);	
	m_pSystemSaftySubDlg->ShowWindow(SW_HIDE);
	m_pSystemCoordinateDlg->ShowWindow(SW_HIDE);
	m_pSystemESCDlg->ShowWindow(SW_HIDE);//21.04.09 SJC
}
//----------------------------------------------------------------------------
BOOL CSystemDlg::DestroyWindow()
{
	return CDialogEx::DestroyWindow();
}
//----------------------------------------------------------------------------
void CSystemDlg::OnBnClickedButtonSubPage1()
{
	m_nCurrentSubNo = SYSTEM_SUB_PAGE1_DLG;
	ShowDlg(m_nCurrentNo, m_nCurrentSubNo);
}
//----------------------------------------------------------------------------
void CSystemDlg::OnBnClickedButtonSubPage2()
{	
	m_nCurrentSubNo = SYSTEM_SUB_PAGE2_DLG;
	ShowDlg(m_nCurrentNo, m_nCurrentSubNo);	
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
void CSystemDlg::OnBnClickedButtonSystemSafty()
{
	m_nCurrentNo = SYSTEM_SAFTY_DLG;
	ShowDlg(m_nCurrentNo, m_nCurrentSubNo);
}
//----------------------------------------------------------------------------
void CSystemDlg::OnBnClickedButtonSystemOption()
{
	m_nCurrentNo = SYSTEM_OPTION_DLG;
	ShowDlg(m_nCurrentNo, m_nCurrentSubNo);
}

//change : option --> option2
void CSystemDlg::OnBnClickedButtonSystemOption2()
{
	// TODO: Add your control notification handler code here

	m_nCurrentNo = SYSTEM_OPTION_DLG;
	ShowDlg(m_nCurrentNo, m_nCurrentSubNo);
}
//----------------------------------------------------------------------------

void CSystemDlg::OnBnClickedButtonSystemCoordinate()
{
	m_nCurrentNo = SYSTEM_COORDINATE_DLG;
	ShowDlg(m_nCurrentNo, m_nCurrentSubNo);
}


void CSystemDlg::OnBnClickedButtonSystemEsc()
{
	m_nCurrentNo = SYSTEM_ESC_DLG;
	ShowDlg(m_nCurrentNo, m_nCurrentSubNo);
}

void CSystemDlg::OnBnClickedBtnSystemSave()
{
	DWORD Result;

	Result = AfxMessageBox(_T("Save?"), MB_OKCANCEL);

	BeginWaitCursor();
	if (Result == IDOK)
	{
		switch (m_nCurrentNo)
		{
		case SYSTEM_SAFTY_DLG:
			m_pSystemSaftySubDlg->SavePara();
			break;

		case SYSTEM_OPTION_DLG:
			m_pSystemOptionSubDlg->SavePara();
			break;

		case SYSTEM_COORDINATE_DLG:
			m_pSystemCoordinateDlg->SavePara();
			break;

		case SYSTEM_ESC_DLG:
			if(m_nCurrentSubNo == SYSTEM_SUB_PAGE1_DLG) m_pSystemESCDlg->SavePara();
			else
			{
			}
			break;

		}
	}
	EndWaitCursor();
}




