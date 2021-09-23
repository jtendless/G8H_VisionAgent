// VisionAgentECSDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentECSDlg.h"
#include "afxdialogex.h"


// CVisionAgentECSDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CVisionAgentECSDlg, CDialogEx)

CVisionAgentECSDlg::CVisionAgentECSDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_VISION_AGENT_ECS_DIALOG, pParent)
{
	Create(IDD_VISION_AGENT_ECS_DIALOG, pParent);
}

CVisionAgentECSDlg::~CVisionAgentECSDlg()
{
	if (m_pMain)
	{
		m_pMain->DestroyWindow();
		delete m_pMain;
	}
	if (m_pJobManagement)
	{
		m_pJobManagement->DestroyWindow();
		delete m_pJobManagement;
	}
	if (m_pSheet)
	{
		m_pSheet->DestroyWindow();
		delete m_pSheet;
	}
	if (m_pAlarm)
	{
		m_pAlarm->DestroyWindow();
		delete m_pAlarm;
	}
	if (m_pDfs)
	{
		m_pDfs->DestroyWindow();
		delete m_pDfs;
	}
}

void CVisionAgentECSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VISION_AGENT_ECS_TAB1, m_tab1);
}


BEGIN_MESSAGE_MAP(CVisionAgentECSDlg, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_VISION_AGENT_ECS_TAB1, &CVisionAgentECSDlg::OnTcnSelChange)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CVisionAgentECSDlg 메시지 처리기입니다.


BOOL CVisionAgentECSDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_pMain = new CVisionAgentECSMainDlg(this);
	m_pJobManagement = new CVisionAgentECSJobManagementDlg(this);
	m_pSheet = new CVisionAgentECSSheetDlg(this);
	m_pAlarm = new CVisionAgentECSErrorDlg(this);
	m_pDfs = new CVisionAgentECSDfsDlg(this);

	m_tab1.InsertItem(TCIF_TEXT | TCIF_PARAM, 0, _T("Main "), 0, (LPARAM)m_pMain);
	m_tab1.InsertItem(TCIF_TEXT | TCIF_PARAM, 1, _T("Job Data "), 0, (LPARAM)m_pJobManagement);
	m_tab1.InsertItem(TCIF_TEXT | TCIF_PARAM, 2, _T("Sheet Info"), 0, (LPARAM)m_pSheet);
	m_tab1.InsertItem(TCIF_TEXT | TCIF_PARAM, 3, _T("Alarm "), 0, (LPARAM)m_pAlarm);
	m_tab1.InsertItem(TCIF_TEXT | TCIF_PARAM, 4, _T("DFS "), 0, (LPARAM)m_pDfs);
	
	m_tab1.SetCurSel(0);
	m_tab1.SetItemSize(CSize(_TAB_ITEM_SIZE_X, 40));
	RecalcLayout();

	//SharedInfo::DfsInfoRead();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}




void CVisionAgentECSDlg::RecalcLayout()
{
	CRect	rect, rcClient, rcTab;
	GetClientRect(&rcClient);
	rcTab = rcClient;
	rcTab.DeflateRect(5, 5, 5, 5);
	rect = rcTab;
	rect.DeflateRect(5, 50, 5, 5);

	m_tab1.MoveWindow(rcTab);

	m_pMain->ShowWindow(SW_HIDE);
	m_pJobManagement->ShowWindow(SW_HIDE);
	m_pSheet->ShowWindow(SW_HIDE);
	m_pAlarm->ShowWindow(SW_HIDE);
	m_pDfs->ShowWindow(SW_HIDE);

	int		nCurSel = m_tab1.GetCurSel();
	if (nCurSel == 0)
	{
		m_pMain->ShowWindow(SW_SHOW);
		m_pMain->MoveWindow(rect);
		
	}
	else if (nCurSel == 1)
	{
		m_pJobManagement->ShowWindow(SW_SHOW);
		m_pJobManagement->MoveWindow(rect);
		
	}

	else if (nCurSel == 2)
	{
		m_pSheet->ShowWindow(SW_SHOW);
		m_pSheet->MoveWindow(rect);

	}
	else if (nCurSel == 3)
	{
		m_pAlarm->ShowWindow(SW_SHOW);
		m_pAlarm->MoveWindow(rect);

	}

	else if (nCurSel == 4)
	{
		m_pDfs->ShowWindow(SW_SHOW);
		m_pDfs->MoveWindow(rect);
	}

}



void CVisionAgentECSDlg::OnTcnSelChange(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (m_tab1.GetSafeHwnd())
	{
		RecalcLayout();
	}
	*pResult = 0;
}


void CVisionAgentECSDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (m_tab1.GetSafeHwnd())
	{
		RecalcLayout();
	}
	
}
