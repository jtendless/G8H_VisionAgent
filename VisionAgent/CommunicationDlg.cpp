// CommunicationDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentDlg.h"
#include "CommunicationDlg.h"
#include "afxdialogex.h"

// CCommunicationDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCommunicationDlg, CDialogEx)

CCommunicationDlg::CCommunicationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_COMMUNICATION, pParent)
{
	Create(IDD_DLG_COMMUNICATION, pParent);
}

CCommunicationDlg::~CCommunicationDlg()
{
	if (m_pCommunicationAIODlg)
	{
		m_pCommunicationAIODlg->DestroyWindow();
		delete m_pCommunicationAIODlg;
	}

	if (m_pCommunicationDIODlg)
	{
		m_pCommunicationDIODlg->DestroyWindow();
		delete m_pCommunicationDIODlg;
	}

}

void CCommunicationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BOOL CCommunicationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();	

	m_pCommunicationDIODlg = new CCommunicationDIODlg(this);
	m_pCommunicationAIODlg = new CCommunicationAIODlg(this);



	m_Comm_Lamp[0].SubclassDlgItem(IDC_STATIC_LAMP_DIO, this);
	m_Comm_Lamp[0].SetBackgroundColor(BTN_LAMP_ON); //주황
	m_Comm_Lamp[0].SetBackgroundColor(RGB(239, 239, 239)); //백그라운드

	m_Comm_Lamp[1].SubclassDlgItem(IDC_STATIC_LAMP_AIO, this);
	m_Comm_Lamp[1].SetBackgroundColor(BTN_LAMP_OFF); //주황
	m_Comm_Lamp[1].SetBackgroundColor(RGB(239, 239, 239)); //백그라운드
	return TRUE;
}

BEGIN_MESSAGE_MAP(CCommunicationDlg, CDialogEx)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_DIO, &CCommunicationDlg::OnBnClickedBtnDio)
	ON_BN_CLICKED(IDC_BTN_AIO, &CCommunicationDlg::OnBnClickedBtnAio)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BTN_COMMUNICATION_CLOSE, &CCommunicationDlg::OnBnClickedBtnCommunicationClose)
END_MESSAGE_MAP()

void CCommunicationDlg::OnCancel()
{
	CVisionAgentDlg *pVisionAgentDlg = (CVisionAgentDlg*)theApp.m_pMainWnd;
	pVisionAgentDlg->m_bShowCommunicationModeless = FALSE;

	CDialogEx::OnCancel();
}
//--------------------------------------------------------
void CCommunicationDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if (GetDlgItem(IDC_BTN_DIO)->GetSafeHwnd() == NULL) return;
	if (GetDlgItem(IDC_STATIC_LAMP_DIO)->GetSafeHwnd() == NULL) return;
	if (GetDlgItem(IDC_BTN_AIO)->GetSafeHwnd() == NULL) return;
	if (GetDlgItem(IDC_STATIC_LAMP_AIO)->GetSafeHwnd() == NULL) return;
	if (GetDlgItem(IDC_STATIC_LINE_W)->GetSafeHwnd() == NULL) return;
	if (GetDlgItem(IDC_STATIC_SUB_DLG)->GetSafeHwnd() == NULL) return;
	if (GetDlgItem(IDC_BTN_COMMUNICATION_CLOSE)->GetSafeHwnd() == NULL) return;
	
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	int nOffset = 5;
	int nBtn_Size_X		= 100;
	int nBtn_Size_Y		= 50;
	int nLamp_Step_Size = 5;
	CRect	RectBtn, RectLamp;
	RectBtn.left	= nOffset * 2;
	RectBtn.top		= nOffset;
	RectBtn.right	= RectBtn.left + nBtn_Size_X;
	RectBtn.bottom	= RectBtn.top + nBtn_Size_Y;
	GetDlgItem(IDC_BTN_DIO)->MoveWindow(RectBtn);
	RectLamp.left	= RectBtn.left;
	RectLamp.top	= RectBtn.bottom;
	RectLamp.right	= RectBtn.right;
	RectLamp.bottom = RectLamp.top + nLamp_Step_Size;
	GetDlgItem(IDC_STATIC_LAMP_DIO)->MoveWindow(RectLamp);

	RectBtn.left = RectBtn.right + nOffset;
	RectBtn.right = RectBtn.left + nBtn_Size_X;	
	GetDlgItem(IDC_BTN_AIO)->MoveWindow(RectBtn);
	RectLamp.left = RectLamp.right + nOffset;
	RectLamp.right = RectBtn.right;
	GetDlgItem(IDC_STATIC_LAMP_AIO)->MoveWindow(RectLamp);

	CRect	RectLine, RectSubDlg;
	RectLine.left	= nOffset;
	RectLine.top	= RectLamp.bottom + nOffset;
	RectLine.right	= cx - nBtn_Size_X - nOffset;
	RectLine.bottom	= RectLine.top + 2;
	GetDlgItem(IDC_STATIC_LINE_W)->MoveWindow(RectLine);

	RectSubDlg.left		= nOffset * 2;
	RectSubDlg.top		= RectLine.bottom + nOffset;
	RectSubDlg.right	= cx - nBtn_Size_X - (nOffset * 2);
	RectSubDlg.bottom	= cy - nBtn_Size_Y - (nOffset * 2);
	GetDlgItem(IDC_STATIC_SUB_DLG)->MoveWindow(RectSubDlg);

	GetDlgItem(IDC_STATIC_SUB_DLG)->GetWindowRect(&RectSubDlg);	
	ScreenToClient(RectSubDlg);
	m_pCommunicationDIODlg->MoveWindow(RectSubDlg);	
	m_pCommunicationAIODlg->MoveWindow(RectSubDlg);	

	RectBtn.left	= cx - nBtn_Size_X - nOffset;
	RectBtn.top		= cy - nBtn_Size_Y - nOffset;
	RectBtn.right	= cx - nOffset;
	RectBtn.bottom	= cy - nOffset;
	GetDlgItem(IDC_BTN_COMMUNICATION_CLOSE)->MoveWindow(RectBtn);

	ShowDlg(0);
}
//--------------------------------------------------------
void CCommunicationDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	SetWindowPos(NULL, 960, 10, 960, 960, NULL);
}
//--------------------------------------------------------
void	CCommunicationDlg::ShowDlg(int nDlgNo)
{
	if (nDlgNo == 0)
	{
		m_pCommunicationDIODlg->ShowWindow(SW_SHOW);
		m_Comm_Lamp[0].SetBackgroundColor(BTN_LAMP_ON);
		m_pCommunicationAIODlg->ShowWindow(SW_HIDE);
		m_Comm_Lamp[1].SetBackgroundColor(BTN_LAMP_OFF);
	}
	else
	{
		m_pCommunicationDIODlg->ShowWindow(SW_HIDE);
		m_Comm_Lamp[0].SetBackgroundColor(BTN_LAMP_OFF);
		m_pCommunicationAIODlg->ShowWindow(SW_SHOW);
		m_Comm_Lamp[1].SetBackgroundColor(BTN_LAMP_ON);
	}	
}

void CCommunicationDlg::OnBnClickedBtnDio()
{
	ShowDlg(0);
}

void CCommunicationDlg::OnBnClickedBtnAio()
{
	ShowDlg(1);
}

void CCommunicationDlg::OnBnClickedBtnCommunicationClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CVisionAgentDlg *pVisionAgentDlg;
	pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
	pVisionAgentDlg->m_bShowCommunicationModeless = FALSE;

	OnCancel();
}
