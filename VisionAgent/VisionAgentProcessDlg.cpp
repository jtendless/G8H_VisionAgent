// VisionAgentProcessDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentDlg.h"
#include "VisionAgentProcessDlg.h"
#include "afxdialogex.h"


// CVisionAgentProcessDlg dialog

IMPLEMENT_DYNAMIC(CVisionAgentProcessDlg, CDialogEx)

CVisionAgentProcessDlg::CVisionAgentProcessDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VISION_AGENT_PROCESS_DIALOG, pParent)
{
	Create(IDD_VISION_AGENT_PROCESS_DIALOG, pParent);
}

CVisionAgentProcessDlg::~CVisionAgentProcessDlg()
{
}

void CVisionAgentProcessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVisionAgentProcessDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()


// CVisionAgentProcessDlg message handlers

BOOL CVisionAgentProcessDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitCtrl();

	return TRUE;
}

BOOL CVisionAgentProcessDlg::InitCtrl()
{
	CRect	rect, rcClient, rcTab, rcMap;
	GetClientRect(&rcClient);
	rcMap = rcTab = rcClient;
	rcTab.DeflateRect(505, 5, 5, 70);
	rcMap.top = 405;
	rcMap.right = 500;
	rect = rcTab;
	rect.DeflateRect(5, 50, 5, 5);

	RecalcLayout();
	m_bShowFlag = FALSE;

	return TRUE;
}

void CVisionAgentProcessDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	SetWindowPos(NULL, 960, 10, 960, 960, NULL);
}

void CVisionAgentProcessDlg::OnCancel()
{
	CVisionAgentDlg *pVisionAgentDlg = (CVisionAgentDlg*)theApp.m_pMainWnd;
	pVisionAgentDlg->m_bShowProcessDlg = FALSE;

	CDialogEx::OnCancel();
}

void CVisionAgentProcessDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	RecalcLayout();
}

BOOL CVisionAgentProcessDlg::DestroyWindow()
{
	return CDialogEx::DestroyWindow();
}

void CVisionAgentProcessDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nID == SC_CLOSE)
	{
		CVisionAgentDlg *pVisionAgentDlg;
		pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
		pVisionAgentDlg->m_CheckProcessDlg.SetCheck(FALSE);
		pVisionAgentDlg->m_bShowProcessDlg = FALSE;
		pVisionAgentDlg->m_pProcessDlg->ShowWindow(SW_HIDE);
	}
	CDialogEx::OnSysCommand(nID, lParam);
}

void CVisionAgentProcessDlg::RecalcLayout()
{
	CRect rect, rcClient, rcTab;
	CRect rcMapRef;
	CRect rcFlowSubject[3];
	CRect rcFlow[3];
	INT nSubjectSizeX = 0, nSubjectSizeY = 0;
	GetClientRect(&rcClient);

	rcTab = rcClient;
	rcTab.DeflateRect(rcClient.Width() / 3, 1, 1, 0);

	rect = rcTab;
	rect.DeflateRect(5, 50, 5, 5);

	Invalidate(false);
}