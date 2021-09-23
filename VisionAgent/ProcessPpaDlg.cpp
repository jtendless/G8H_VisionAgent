// ProcessPPADlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "ProcessPPADlg.h"
#include "afxdialogex.h"


// CProcessPpaDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CProcessPpaDlg, CDialogEx)

CProcessPpaDlg::CProcessPpaDlg( CWnd* pParent /*=NULL*/)
	: CDialogEx(CProcessPpaDlg::IDD, pParent)
{
	

	Create(IDD_PROCESS_PPA_DIALOG, pParent);
}

CProcessPpaDlg::~CProcessPpaDlg()
{

}

void CProcessPpaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CProcessPpaDlg, CDialogEx)
	ON_WM_SIZE()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CProcessPpaDlg 메시지 처리기입니다.


BOOL CProcessPpaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CProcessPpaDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	
	m_nCx = cx;
	m_nCy = cy;

	RecalcLayout();
	//int sizeY = cy / 3;	
	
	//Invalidate(FALSE);
}

void CProcessPpaDlg::RecalcLayout()
{
}

void CProcessPpaDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.


}



BOOL CProcessPpaDlg::DestroyWindow()
{
	return CDialogEx::DestroyWindow();
}
