// ManualGantrySubDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "ManualGantrySubDlg.h"
#include "afxdialogex.h"
#include "VisionAgentDlg.h"


// CManualGantrySubDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CManualGantrySubDlg, CDialogEx)

CManualGantrySubDlg::CManualGantrySubDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_MANUAL_SUB_GANTRY, pParent)
{
	m_bDialog_Entry = FALSE;
	Create(IDD_DLG_MANUAL_SUB_GANTRY, pParent);
}

CManualGantrySubDlg::~CManualGantrySubDlg()
{

}

void CManualGantrySubDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CManualGantrySubDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_MANUAL_TEST, &CManualGantrySubDlg::OnBnClickedBtnManualTest)

	//Set Camera Para

	//Light Turn On/Off
	
	//Set Camera Light

	//Find Mark
	ON_BN_CLICKED(IDC_BTN_MANUAL_FIND_MARK1, &CManualGantrySubDlg::OnBnClickedBtnManualFindMark1)
	ON_BN_CLICKED(IDC_BTN_MANUAL_FIND_MARK2, &CManualGantrySubDlg::OnBnClickedBtnManualFindMark2)


	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BTN_MANUAL_FIND_PATTERN_LEFT, &CManualGantrySubDlg::OnBnClickedBtnManualFindPatternLeft)
	ON_BN_CLICKED(IDC_BTN_MANUAL_FIND_PATTERN_RIGHT, &CManualGantrySubDlg::OnBnClickedBtnManualFindPatternRight)
END_MESSAGE_MAP()


// CManualGantrySubDlg 메시지 처리기입니다.

BOOL CManualGantrySubDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_Edit_GantryPosX1.SubclassDlgItem(IDC_EDIT_MANUAL_GANTRY_POS_X1, this);
	m_Edit_GantryPosY1.SubclassDlgItem(IDC_EDIT_MANUAL_GANTRY_POS_Y1, this);
	m_Edit_GantryPosZ1.SubclassDlgItem(IDC_EDIT_MANUAL_GANTRY_POS_Z1, this);

	m_Edit_GantryPosX2.SubclassDlgItem(IDC_EDIT_MANUAL_GANTRY_POS_X2, this);
	m_Edit_GantryPosY2.SubclassDlgItem(IDC_EDIT_MANUAL_GANTRY_POS_Y2, this);
	m_Edit_GantryPosZ2.SubclassDlgItem(IDC_EDIT_MANUAL_GANTRY_POS_Z2, this);

	//m_Edit_GantryGetLcValue.SubclassDlgItem()

	m_stcTestLed.SubclassDlgItem(IDC_STC_MANUAL_TEST_LED, this);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CManualGantrySubDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow)
	{
		SetTimer(1, 100, NULL);
	}
	else
	{
		KillTimer(1);
	}
}

void CManualGantrySubDlg::OnTimer(UINT_PTR nIDEvent)
{
	CString strTemp = _T("");
	DOUBLE dX = 0, dY = 0, dZ = 0;
	Devs::m_GantryMotion.ReadGantryLeftConvertMotorPos(&dX, &dY, &dZ);
	
	strTemp.Format(_T("%.5f"), dX);
	m_Edit_GantryPosX1.SetWindowTextW(strTemp);

	strTemp.Format(_T("%.5f"), dY);
	m_Edit_GantryPosY1.SetWindowTextW(strTemp);

	strTemp.Format(_T("%.5f"), dZ);
	m_Edit_GantryPosZ1.SetWindowTextW(strTemp);

	Devs::m_GantryMotion.ReadGantryRightConvertMotorPos(&dX, &dY, &dZ);

	strTemp.Format(_T("%.5f"), dX);
	m_Edit_GantryPosX2.SetWindowTextW(strTemp);

	strTemp.Format(_T("%.5f"), dY);
	m_Edit_GantryPosY2.SetWindowTextW(strTemp);

	strTemp.Format(_T("%.5f"), dZ);
	m_Edit_GantryPosZ2.SetWindowTextW(strTemp);

	//Test - LED.
	if (TRUE)
	{
		m_stcTestLed.SetBackgroundColor(GREEN);
	}
	else
	{
		m_stcTestLed.SetBackgroundColor(BTN_LAMP_OFF);
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CManualGantrySubDlg::OnBnClickedBtnManualTest()
{
	double dX = 0, dY = 0;
	Devs::m_GantryMotion.FindMark1(&dX, &dY);
}

void CManualGantrySubDlg::OnBnClickedBtnManualFindMark1()
{
	double dX = 0, dY = 0;
	Devs::m_GantryMotion.FindMark1(&dX, &dY);
}

void CManualGantrySubDlg::OnBnClickedBtnManualFindMark2()
{
	double dX = 0, dY = 0;
	Devs::m_GantryMotion.FindMark2(&dX, &dY);
}


void CManualGantrySubDlg::OnBnClickedBtnManualFindPatternLeft()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	double dX = 0, dY = 0;
	Devs::m_GantryMotion.FindPattern1(&dX, &dY);
}


void CManualGantrySubDlg::OnBnClickedBtnManualFindPatternRight()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	double dX = 0, dY = 0;
	Devs::m_GantryMotion.FindPattern2(&dX, &dY);
}

