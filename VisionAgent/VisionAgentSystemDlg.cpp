// VisionAgentSystemDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentSystemDlg.h"
#include "afxdialogex.h"


// CVisionAgentSystemDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CVisionAgentSystemDlg, CDialogEx)

CVisionAgentSystemDlg::CVisionAgentSystemDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SYSTEM_DIALOG, pParent)
{

}

CVisionAgentSystemDlg::~CVisionAgentSystemDlg()
{
}

void CVisionAgentSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVisionAgentSystemDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_SYSTEM_CAMERA, &CVisionAgentSystemDlg::OnBnClickedBtnSystemCamera)
	ON_BN_CLICKED(IDC_BTN_SYSTEM_SAFETY, &CVisionAgentSystemDlg::OnBnClickedBtnSystemSafety)
	ON_BN_CLICKED(IDC_BTN_SYSTEM_OPTION, &CVisionAgentSystemDlg::OnBnClickedBtnSystemOption)
	ON_BN_CLICKED(IDC_BUTTON_SYSTEM_SAVE, &CVisionAgentSystemDlg::OnBnClickedButtonSystemSave)
	ON_BN_CLICKED(IDC_BUTTON_SYSTEM_CLOSE, &CVisionAgentSystemDlg::OnBnClickedButtonSystemClose)
END_MESSAGE_MAP()


// CVisionAgentSystemDlg 메시지 처리기입니다.

BOOL CVisionAgentSystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	Dialog_Init();
	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CVisionAgentSystemDlg::Dialog_Init()
{
	CRect rect;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//								  버튼
	//--------------------------------------------------------------------------------------------------------
	m_btnSystem[SYSTEM_CAMERA_DLG].SubclassDlgItem(IDC_BTN_SYSTEM_CAMERA, this);
	m_btnSystem[SYSTEM_SAFETY_DLG].SubclassDlgItem(IDC_BTN_SYSTEM_SAFETY, this);
	m_btnSystem[SYSTEM_OPTION_DLG].SubclassDlgItem(IDC_BTN_SYSTEM_OPTION, this);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//								버튼 램프
	//--------------------------------------------------------------------------------------------------------
	m_stcSystem_Dlg_Lamp[SYSTEM_CAMERA_DLG].SubclassDlgItem(IDC_STATIC_SYSTEM_CAMERA_LAMP, this);
	m_stcSystem_Dlg_Lamp[SYSTEM_SAFETY_DLG].SubclassDlgItem(IDC_STATIC_SYSTEM_SAFETY_LAMP, this);
	m_stcSystem_Dlg_Lamp[SYSTEM_OPTION_DLG].SubclassDlgItem(IDC_STATIC_SYSTEM_OPTION_LAMP, this);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	//								다이얼로그 박스
	//--------------------------------------------------------------------------------------------------------

	GetDlgItem(IDC_STATIC_VISION_SYSTEM)->GetWindowRect(&rect);
	m_SystemCameraDlg.Create(IDD_SYSTEM_CAMERA_DIALOG, this);
	m_SystemCameraDlg.SetWindowPos(NULL, rect.left, rect.top, rect.Width(), rect.Height(), NULL);

	GetDlgItem(IDC_STATIC_VISION_SYSTEM)->GetWindowRect(&rect);
	m_SystemSafetyDlg.Create(IDD_SYSTEM_SAFETY_DIALOG, this);
	m_SystemSafetyDlg.SetWindowPos(NULL, rect.left, rect.top, rect.Width(), rect.Height(), NULL);

	GetDlgItem(IDC_STATIC_VISION_SYSTEM)->GetWindowRect(&rect);
	m_SystemOptionDlg.Create(IDD_SYSTEM_OPTION_DIALOG, this);
	m_SystemOptionDlg.SetWindowPos(NULL, rect.left, rect.top, rect.Width(), rect.Height(), NULL);

	m_nCurrentManualNo = SYSTEM_CAMERA_DLG;
	ShowDlg(m_nCurrentManualNo, NULL);
}

void CVisionAgentSystemDlg::OnBnClickedBtnSystemCamera()
{
	m_nCurrentManualNo = SYSTEM_CAMERA_DLG;
	ShowDlg(m_nCurrentManualNo, NULL);
}

void CVisionAgentSystemDlg::OnBnClickedBtnSystemSafety()
{
	m_nCurrentManualNo = SYSTEM_SAFETY_DLG;
	ShowDlg(m_nCurrentManualNo, NULL);

}


void CVisionAgentSystemDlg::OnBnClickedBtnSystemOption()
{
	m_nCurrentManualNo = SYSTEM_OPTION_DLG;
	ShowDlg(m_nCurrentManualNo, NULL);

}


void CVisionAgentSystemDlg::ShowDlg(int nDlgNo, int nSubDlgNo)
{
	Dlg_HideWindow();

	switch (nDlgNo)
	{
		//Frame Loader Manual 컨트롤
	case SYSTEM_CAMERA_DLG:
		m_SystemCameraDlg.OnShowWindow(TRUE, 0);
		m_stcSystem_Dlg_Lamp[SYSTEM_CAMERA_DLG].SetBackgroundColor(BTN_LAMP_ON);
		break;

	case SYSTEM_SAFETY_DLG:
		m_SystemSafetyDlg.OnShowWindow(TRUE, 0);
		m_stcSystem_Dlg_Lamp[SYSTEM_SAFETY_DLG].SetBackgroundColor(BTN_LAMP_ON);
		break;

	case SYSTEM_OPTION_DLG:
		m_SystemOptionDlg.OnShowWindow(TRUE, 0);
		m_stcSystem_Dlg_Lamp[SYSTEM_OPTION_DLG].SetBackgroundColor(BTN_LAMP_ON);
		break;
	}

	//버튼 최상위.
	for (int k = 0; k < MAX_SYSTEM_DLG; k++)
	{
		m_btnSystem[k].SetFocus();
	}

}

void CVisionAgentSystemDlg::Dlg_HideWindow()
{
	m_SystemCameraDlg.OnShowWindow(FALSE, 0);
	m_SystemSafetyDlg.OnShowWindow(FALSE, 0);
	m_SystemOptionDlg.OnShowWindow(FALSE, 0);

	for (int i = 0; i < MAX_SYSTEM_DLG;i++)
	{
		m_stcSystem_Dlg_Lamp[i].SetBackgroundColor(BTN_LAMP_OFF);
	}
}

void CVisionAgentSystemDlg::OnBnClickedButtonSystemSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CVisionAgentSystemDlg::OnBnClickedButtonSystemClose()
{
	OnCancel();
}


