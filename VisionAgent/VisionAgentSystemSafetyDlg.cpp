// VisionAgentSystemSafetyDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentSystemSafetyDlg.h"
#include "afxdialogex.h"


// CVisionAgentSystemSafetyDlg 대화 상자입니다.

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


// CVisionAgentSystemSafetyDlg 메시지 처리기입니다.
void CVisionAgentSystemSafetyDlg::OnShowWindow(bool bShow, UINT nStatus)
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