// PositionKeyInDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "PositionKeyInDlg.h"
#include "afxdialogex.h"


// CPositionKeyInDlg 대화 상자

IMPLEMENT_DYNAMIC(CPositionKeyInDlg, CDialogEx)

CPositionKeyInDlg::CPositionKeyInDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_POSITION_KEY_IN, pParent)
{
	Create(IDD_DLG_POSITION_KEY_IN, pParent);
}

CPositionKeyInDlg::~CPositionKeyInDlg()
{
	
}

void CPositionKeyInDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPositionKeyInDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_GET_MANUAL_POS, &CPositionKeyInDlg::OnBnClickedBtnGetManualPos)
	ON_BN_CLICKED(IDOK, &CPositionKeyInDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CPositionKeyInDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CPositionKeyInDlg 메시지 처리기


void CPositionKeyInDlg::OnBnClickedBtnGetManualPos()
{
}

#ifndef SIM_MODE
void CPositionKeyInDlg::SetCameraInfo(CWkLibVision *ImageProc, eFindType FindType)
{
	m_pCamera = ImageProc;

	if (m_pCamera == Devs::m_Camera10X)
	{
		SetWindowTextW(_T("Review10X Cam KeyIn"));
	}
	else if (m_pCamera == Devs::m_Camera10X) //else if (m_pCamera == Devs::m_Camera20X)
	{
		SetWindowTextW(_T("Review20X Cam KeyIn"));
	}
}
#endif

BOOL CPositionKeyInDlg::Delay()
{
	while (TRUE)
	{
		PeekAndPump();

		if (!IsWindowVisible())
			break;
		Sleep(10);
	}

	return TRUE;
}



void	CPositionKeyInDlg::PeekAndPump()
{
	MSG		msg;
	while (::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
	{
		if (!AfxGetThread()->PumpMessage()) break;
	}
}

void CPositionKeyInDlg::OnBnClickedOk()
{
	m_bResult = TRUE;
	CDialogEx::OnOK();
}


void CPositionKeyInDlg::OnBnClickedCancel()
{
	m_bResult = FALSE;
	CDialogEx::OnCancel();
}


BOOL CPositionKeyInDlg::GetResult(DOUBLE &dX, DOUBLE &dY)
{
	CString strTemp = _T("");
	GetDlgItem(IDC_EDIT_MANUAL_POS_X)->GetWindowTextW(strTemp);
	dX = _ttof(strTemp);

	GetDlgItem(IDC_EDIT_MANUAL_POS_Y)->SetWindowTextW(strTemp);
	dY = _ttof(strTemp);

	return m_bResult;
}