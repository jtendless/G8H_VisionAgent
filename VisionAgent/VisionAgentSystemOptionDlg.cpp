// VisionAgentSystemOptionDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentSystemOptionDlg.h"
#include "afxdialogex.h"


// CVisionAgentSystemOptionDlg 대화 상자입니다.

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


// CVisionAgentSystemOptionDlg 메시지 처리기입니다.

void CVisionAgentSystemOptionDlg::OnShowWindow(bool bShow, UINT nStatus)
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
