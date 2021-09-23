// VisionAgentSafetyMap.cpp: 구현 파일
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentSafetyMap.h"
#include "afxdialogex.h"
#include "VisionAgentDlg.h"

// CVisionAgentSafetyMap 대화 상자

IMPLEMENT_DYNAMIC(CVisionAgentSafetyMap, CDialogEx)

CVisionAgentSafetyMap::CVisionAgentSafetyMap(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SAFETY_MAP, pParent)
{
	Create(IDD_SAFETY_MAP, pParent);
}

CVisionAgentSafetyMap::~CVisionAgentSafetyMap()
{
	KillTimer(1);
}

void CVisionAgentSafetyMap::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVisionAgentSafetyMap, CDialogEx)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CVisionAgentSafetyMap::OnBnClickedButton1)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_DOOR_1, &CVisionAgentSafetyMap::OnBnClickedButtonDoor1)
	ON_BN_CLICKED(IDC_BUTTON_DOOR_2, &CVisionAgentSafetyMap::OnBnClickedButtonDoor2)
	ON_BN_CLICKED(IDC_BUTTON_DOOR_3, &CVisionAgentSafetyMap::OnBnClickedButtonDoor3)
	ON_BN_CLICKED(IDC_BUTTON_DOOR_4, &CVisionAgentSafetyMap::OnBnClickedButtonDoor4)
END_MESSAGE_MAP()


// CVisionAgentSafetyMap 메시지 처리기

void CVisionAgentSafetyMap::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//CVisionAgentDlg *pDlg = (CVisionAgentDlg*)theApp.m_pMainWnd;
	m_bDoorStatus[0] = Devs::m_BaseMotion.GetDInputValue(_DIN_DOOR_1_OPEN);
	m_bDoorStatus[1] = Devs::m_BaseMotion.GetDInputValue(_DIN_DOOR_2_OPEN);
	m_bDoorStatus[2] = Devs::m_BaseMotion.GetDInputValue(_DIN_DOOR_3_OPEN);
	m_bDoorStatus[3] = Devs::m_BaseMotion.GetDInputValue(_DIN_DOOR_4_OPEN);

	m_bDoorDOStatus[0] = SharedInfo::DOutputValue[_DOUT_FRONT_DOOR];
	m_bDoorDOStatus[1] = SharedInfo::DOutputValue[_DOUT_RIGHT_DOOR];
	m_bDoorDOStatus[2] = SharedInfo::DOutputValue[_DOUT_BACK_DOOR];
	m_bDoorDOStatus[3] = SharedInfo::DOutputValue[_DOUT_LEFT_DOOR];

	m_bEMOStatus[0] = Devs::m_BaseMotion.GetDInputValue(_DIN_EMO_1_ON);
	m_bEMOStatus[1] = Devs::m_BaseMotion.GetDInputValue(_DIN_EMO_2_ON);
	m_bEMOStatus[2] = Devs::m_BaseMotion.GetDInputValue(_DIN_EMO_3_ON);
	m_bEMOStatus[3] = Devs::m_BaseMotion.GetDInputValue(_DIN_EMO_4_ON);
	
	for (int i = 0; i < 4; i++)
	{
		if (m_bEMOStatus[i] == TRUE)
		{
			m_btn_EMO[i].SetBackGroundColor(0x0000FF);
		}
		else
		{
			m_btn_EMO[i].SetBackGroundColor(0x00FF00);
		}

		if (m_bDoorStatus[i] == TRUE)
		{
			m_btn_Door[i].SetBackGroundColor(0x0000FF);
		}
		else if (m_bDoorDOStatus[i] == TRUE)
		{
			m_btn_Door[i].SetBackGroundColor(0xFF0000);
		}
		else
		{
			m_btn_Door[i].SetBackGroundColor(0x00FF00);
		}
	}
	m_btn_Door[1].SetWindowText(_T("D\nO\nO\nR"));
	m_btn_Door[3].SetWindowText(_T("D\nO\nO\nR"));

	Invalidate(FALSE);
	CDialogEx::OnTimer(nIDEvent);
}


BOOL CVisionAgentSafetyMap::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	 m_btn_Door[0].SubclassDlgItem(IDC_BUTTON_DOOR_1,this);
	 m_btn_Door[1].SubclassDlgItem(IDC_BUTTON_DOOR_2, this);
	 m_btn_Door[2].SubclassDlgItem(IDC_BUTTON_DOOR_3, this);
	 m_btn_Door[3].SubclassDlgItem(IDC_BUTTON_DOOR_4, this);
	// m_btn_Door[1].set

	 m_btn_EMO[0].SubclassDlgItem(IDC_BUTTON_EMO_1, this);
	 m_btn_EMO[1].SubclassDlgItem(IDC_BUTTON_EMO_2, this);
	 m_btn_EMO[2].SubclassDlgItem(IDC_BUTTON_EMO_3, this);
	 m_btn_EMO[3].SubclassDlgItem(IDC_BUTTON_EMO_4, this);
	 SetTimer(1, 100, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CVisionAgentSafetyMap::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL bResult=FALSE;
	for (int i = 0; i < 4; i++)
	{
		bResult = bResult || m_bEMOStatus[i];
	}
	for (int i = 0; i < 3; i++)
	{
		bResult = bResult || m_bDoorStatus[i];
	}
	//if (bResult == FALSE)
	{
		ShowWindow(SW_HIDE);
		CVisionAgentDlg *pVisionAgentDlg;
		pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;
		pVisionAgentDlg->m_bShowSafetyMapModeless = FALSE;
		return;
	}
	//else
	//	return;
}


HBRUSH CVisionAgentSafetyMap::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	switch (pWnd->GetDlgCtrlID())
	{
	case IDC_STATIC:
	{
		pDC->SetBkColor(RGB(255, 255, 0));
		//hbr = (HBRUSH)RGBCOLOR_DARKCYAN;
		break;
	}
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void CVisionAgentSafetyMap::OnBnClickedButtonDoor1()
{
#if 0
	if (SharedInfo::DInputValue[_DIN_SAFETY_MODE])
	{
		AfxMessageBox(_T("Safety Mode On"));
		return;
	}
#endif
	Devs::m_BaseMotion.SetDOutputBitValue(_DOUT_FRONT_DOOR, !SharedInfo::DOutputValue[_DOUT_FRONT_DOOR]);
}


void CVisionAgentSafetyMap::OnBnClickedButtonDoor2()
{
#if 0
	if (SharedInfo::DInputValue[_DIN_SAFETY_MODE])
	{
		AfxMessageBox(_T("Safety Mode On"));
		return;
	}
#endif
	Devs::m_BaseMotion.SetDOutputBitValue(_DOUT_RIGHT_DOOR, !SharedInfo::DOutputValue[_DOUT_RIGHT_DOOR]);
}


void CVisionAgentSafetyMap::OnBnClickedButtonDoor3()
{
#if 0
	if (SharedInfo::DInputValue[_DIN_SAFETY_MODE])
	{
		AfxMessageBox(_T("Safety Mode On"));
		return;
	}
#endif
	Devs::m_BaseMotion.SetDOutputBitValue(_DOUT_BACK_DOOR, !SharedInfo::DOutputValue[_DOUT_BACK_DOOR]);
}


void CVisionAgentSafetyMap::OnBnClickedButtonDoor4()
{
#if 0
	if (SharedInfo::DInputValue[_DIN_SAFETY_MODE])
	{
		AfxMessageBox(_T("Safety Mode On"));
		return;
	}
#endif
	Devs::m_BaseMotion.SetDOutputBitValue(_DOUT_LEFT_DOOR, !SharedInfo::DOutputValue[_DOUT_LEFT_DOOR]);
}
