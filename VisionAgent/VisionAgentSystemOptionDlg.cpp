// VisionAgentSystemOptionDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentSystemOptionDlg.h"
#include "afxdialogex.h"


// CVisionAgentSystemOptionDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CVisionAgentSystemOptionDlg, CDialogEx)

CVisionAgentSystemOptionDlg::CVisionAgentSystemOptionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_VISION_AGENT_SYSTEM_OPTION_DIALOG, pParent)
{

}

CVisionAgentSystemOptionDlg::~CVisionAgentSystemOptionDlg()
{
}

void CVisionAgentSystemOptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVisionAgentSystemOptionDlg, CDialogEx)
END_MESSAGE_MAP()


// CVisionAgentSystemOptionDlg �޽��� ó�����Դϴ�.

void CVisionAgentSystemOptionDlg::OnShowWindow(bool bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	if (bShow == TRUE) {
		ShowWindow(SW_SHOW);
	}
	else if (bShow == FALSE)
	{
		ShowWindow(SW_HIDE);
	}
}
