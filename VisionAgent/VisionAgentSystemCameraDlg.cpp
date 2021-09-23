// VisionAgentSystemCameraDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentSystemCameraDlg.h"
#include "afxdialogex.h"


// CVisionAgentSystemCameraDlg 대화 상자입니다.

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


// CVisionAgentSystemCameraDlg 메시지 처리기입니다.

void CVisionAgentSystemCameraDlg::OnShowWindow(bool bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (bShow == TRUE) {
		ShowWindow(SW_SHOW);
	}
	else if (bShow == FALSE)
	{
		ShowWindow(SW_HIDE);
	}
}
