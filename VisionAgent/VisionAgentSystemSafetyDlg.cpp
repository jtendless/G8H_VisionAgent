// VisionAgentSystemSafetyDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentSystemSafetyDlg.h"
#include "afxdialogex.h"


// CVisionAgentSystemSafetyDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CVisionAgentSystemSafetyDlg, CDialogEx)

CVisionAgentSystemSafetyDlg::CVisionAgentSystemSafetyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_VISION_AGENT_SYSTEM_SAFETY_DIALOG, pParent)
{

}

CVisionAgentSystemSafetyDlg::~CVisionAgentSystemSafetyDlg()
{
}

void CVisionAgentSystemSafetyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVisionAgentSystemSafetyDlg, CDialogEx)
END_MESSAGE_MAP()


// CVisionAgentSystemSafetyDlg �޽��� ó�����Դϴ�.
void CVisionAgentSystemSafetyDlg::OnShowWindow(bool bShow, UINT nStatus)
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