// ProcessPPADlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "ProcessPPADlg.h"
#include "afxdialogex.h"


// CProcessPpaDlg ��ȭ �����Դϴ�.

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


// CProcessPpaDlg �޽��� ó�����Դϴ�.


BOOL CProcessPpaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
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
					   // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
					   // �׸��� �޽����� ���ؼ��� CDialogEx::OnPaint()��(��) ȣ������ ���ʽÿ�.


}



BOOL CProcessPpaDlg::DestroyWindow()
{
	return CDialogEx::DestroyWindow();
}
