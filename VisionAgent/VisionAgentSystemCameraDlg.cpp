// VisionAgentSystemCameraDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentSystemCameraDlg.h"
#include "afxdialogex.h"


// CVisionAgentSystemCameraDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CVisionAgentSystemCameraDlg, CDialogEx)

CVisionAgentSystemCameraDlg::CVisionAgentSystemCameraDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_VISION_AGENT_SYSTEM_CAMERA_DIALOG, pParent)
{

}

CVisionAgentSystemCameraDlg::~CVisionAgentSystemCameraDlg()
{
}

void CVisionAgentSystemCameraDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVisionAgentSystemCameraDlg, CDialogEx)
END_MESSAGE_MAP()


// CVisionAgentSystemCameraDlg �޽��� ó�����Դϴ�.

void CVisionAgentSystemCameraDlg::OnShowWindow(bool bShow, UINT nStatus)
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
