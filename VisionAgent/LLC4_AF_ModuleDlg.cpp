
// LLC4_AF_ModuleDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "LLC4_AF_ModuleDlg.h"
#include "afxdialogex.h"

#include "Module\LLC4AF\INCLUDE\atf_lib_exp.h""
#include "Module\LLC4AF\INCLUDE\Sol_LLC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define ErrOK 0

CSol_LLC g_LLC;

// CLLC4_AF_ModuleDlg 대화 상자

CLLC4_AF_ModuleDlg::CLLC4_AF_ModuleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLLC4_AF_ModuleDlg::IDD, pParent)
{
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	Create(CLLC4_AF_ModuleDlg::IDD, pParent);
}

void CLLC4_AF_ModuleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMPORT_NUM, m_Comport_Num);
	DDX_Control(pDX, IDC_STATUS_COMMUNICATION, m_Status_Communication);
	DDX_Control(pDX, IDC_STATUS_INFOCUS, m_Status_Infocus);
	DDX_Control(pDX, IDC_STATUS_INRANGE, m_Status_Inrange);
	DDX_Control(pDX, IDC_STATUS_LASER, m_Status_Laser);
	DDX_Control(pDX, IDC_STATUS_AF, m_Status_AF);
	DDX_Control(pDX, IDC_STATUS_CW, m_Status_CW);
	DDX_Control(pDX, IDC_STATUS_CCW, m_Status_CCW);
	DDX_Control(pDX, IDC_ZMOVE_NUM, m_ZMove_Num);
	DDX_Control(pDX, IDC_STATUS_ZPOSITION, m_ZPosition);
	DDX_Control(pDX, IDC_STATUS_LEDCURRENT, m_Status_LEDCurrent);
	DDX_Control(pDX, IDC_STATUS_LEDPWM, m_Status_LEDPwm);
	DDX_Control(pDX, IDC_LED_PWMNUM, m_LED_PwmNum);
	DDX_Control(pDX, IDC_LED_CURRENTNUM, m_LED_CurrentNum);
	DDX_Control(pDX, IDC_STATUS_LENSSETTING, m_Status_LensSettingNum);
	DDX_Control(pDX, IDC_STATUS_LLCPOSITION, m_Status_LLCPosition);
	//DDX_Control(pDX, IDC_STATUS_LLCTIME, m_LLC_Time);
	DDX_Control(pDX, IDC_COMPORT_NUM_LLC, m_Comport_Num_LLC);
	DDX_Control(pDX, IDC_STATUS_HOME_STATUS, m_Home_Status);
	DDX_Control(pDX, IDC_STATUS_MOTOR_STATUS, m_Motor_Status);
	DDX_Control(pDX, IDC_STATUS_OBJECTIVE_POSITION, m_Objective_Position);
	DDX_Control(pDX, IDC_STATUS_COMMUNICATION3, m_Status_LLC_Communication);
}

BEGIN_MESSAGE_MAP(CLLC4_AF_ModuleDlg, CDialogEx)
	ON_WM_SHOWWINDOW()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDOK, &CLLC4_AF_ModuleDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CLLC4_AF_ModuleDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_Connect, &CLLC4_AF_ModuleDlg::OnBnClickedConnect)
	ON_BN_CLICKED(IDC_DISCONNECT, &CLLC4_AF_ModuleDlg::OnBnClickedDisconnect)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_LASER_ON, &CLLC4_AF_ModuleDlg::OnBnClickedLaserOn)
	ON_BN_CLICKED(IDC_LASER_OFF, &CLLC4_AF_ModuleDlg::OnBnClickedLaserOff)
	ON_BN_CLICKED(IDC_AF_ON, &CLLC4_AF_ModuleDlg::OnBnClickedAfOn)
	ON_BN_CLICKED(IDC_AF_OFF, &CLLC4_AF_ModuleDlg::OnBnClickedAfOff)
	ON_BN_CLICKED(IDC_Z_UP, &CLLC4_AF_ModuleDlg::OnBnClickedZUp)
	ON_BN_CLICKED(IDC_Z_DOWN, &CLLC4_AF_ModuleDlg::OnBnClickedZDown)
	ON_BN_CLICKED(IDC_Z_CLEAR, &CLLC4_AF_ModuleDlg::OnBnClickedZClear)
	ON_BN_CLICKED(IDC_Z_HOME, &CLLC4_AF_ModuleDlg::OnBnClickedZHome)
	ON_BN_CLICKED(IDC_LED_SET_PWM, &CLLC4_AF_ModuleDlg::OnBnClickedLedSetPwm)
	ON_BN_CLICKED(IDC_LED_SET_CURRENT, &CLLC4_AF_ModuleDlg::OnBnClickedLedSetCurrent)
	ON_BN_CLICKED(IDC_LLC_MOTOR_ON, &CLLC4_AF_ModuleDlg::OnBnClickedLlcMotorOn)
	ON_BN_CLICKED(IDC_LLC_MOTOR_OFF, &CLLC4_AF_ModuleDlg::OnBnClickedLlcMotorOff)
	ON_BN_CLICKED(IDC_LLC_HOME, &CLLC4_AF_ModuleDlg::OnBnClickedLlcHome)
	ON_BN_CLICKED(IDC_LLC_1, &CLLC4_AF_ModuleDlg::OnBnClickedLlc1)
	ON_BN_CLICKED(IDC_LLC_2, &CLLC4_AF_ModuleDlg::OnBnClickedLlc2)
	ON_BN_CLICKED(IDC_LLC_3, &CLLC4_AF_ModuleDlg::OnBnClickedLlc3)
	ON_BN_CLICKED(IDC_LLC_4, &CLLC4_AF_ModuleDlg::OnBnClickedLlc4)
	ON_BN_CLICKED(IDC_MAKE0, &CLLC4_AF_ModuleDlg::OnBnClickedMake0)
	ON_BN_CLICKED(IDC_Connect_LLC, &CLLC4_AF_ModuleDlg::OnBnClickedConnectLlc)
	ON_BN_CLICKED(IDC_DISCONNECT_LLC, &CLLC4_AF_ModuleDlg::OnBnClickedDisconnectLlc)
	ON_BN_CLICKED(IDC_LLC_INITIALIZE, &CLLC4_AF_ModuleDlg::OnBnClickedLlcInitialize)
END_MESSAGE_MAP()


// CLLC4_AF_ModuleDlg 메시지 처리기

BOOL CLLC4_AF_ModuleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	//ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	//ASSERT(IDM_ABOUTBOX < 0xF000);

	//CMenu* pSysMenu = GetSystemMenu(FALSE);
	//if (pSysMenu != NULL)
	//{
	//	BOOL bNameValid;
	//	CString strAboutMenu;
	//	bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
	//	ASSERT(bNameValid);
	//	if (!strAboutMenu.IsEmpty())
	//	{
	//		pSysMenu->AppendMenu(MF_SEPARATOR);
	//		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	//	}
	//}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_ZMove_Num.SetWindowTextW(_T("10.0"));

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}


void CLLC4_AF_ModuleDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow == TRUE)
	{
		SetTimer(1, 100, NULL);

		SetTimer(2, 100, NULL);
	}
	else if (bShow == FALSE)
	{
		KillTimer(1);

		KillTimer(2);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CLLC4_AF_ModuleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CLLC4_AF_ModuleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////


void CLLC4_AF_ModuleDlg::OnBnClickedConnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString TempString;
	long	PortNum;
	char	Com_Name[20];
	
	// 이미 통신이 연결되어 있는지 체크
	m_ErrFlag = ATF_PingAck();
	if(m_ErrFlag == ErrOK)	{ Total_Msg(_T("이미 통신이 연결되었습니다.")); return;}

	m_Comport_Num.GetWindowTextW(TempString);
	PortNum = _tstol(TempString);

	sprintf(Com_Name, "\\\\.\\COM%d", PortNum);

	//	통신 연결
	m_ErrFlag = ATF_OpenConnection(Com_Name, 9600);

	// ErrOK = 0, 모든 ATF 함수는 return값이 0일 때 정상작동.
	if(m_ErrFlag != ErrOK )
	{
		Total_Msg(_T("ATF_OpenConnection 호출 실패"));
		return;
	}

	// LLC의 Initialize를 한다(LLC Home과는 다름)
	/*ATF_initializeLlc(NULL, &m_ErrFlag);
	
	if		(m_ErrFlag == 10) {	//iLLC_err가 10이면 LLC의 구 개수를 입력해주어야 합니다. 그 작업을 합니다.
		int	LLC_Num = ATF_getObjectiveNum();
		if(LLC_Num == 0)	{ATF_setObjectiveNum(4);}
		else				{ATF_setObjectiveNum(LLC_Num);}
	}
	else if (m_ErrFlag != ErrOK) { //LLC Initialize함수 호출에 실패하면 통신도 같이 끊어준다..
		Total_Msg(_T("ATF_initializeLlc 호출 실패")); 
		ATF_CloseConnection(); 
		return;
	}*/


	// 통신 연결 후 기본적인 초기화 작업(Laser와 AF OFF)
	ATF_AfStop();
	Sleep(100);
	m_ErrFlag = ATF_DisableLaser();
	if(m_ErrFlag != ErrOK) {Total_Msg(_T("ATF_DisableLaser 호출 실패")); return;}
	Sleep(100);

	// FullStep과 MicroStep값을 얻어옮(Z축 제어에 쓰임)
	m_ErrFlag = ATF_ReadStepPerMmConversion(&m_FullStep);
	if(m_ErrFlag != ErrOK) {Total_Msg(_T("ATF_ReadStepPerMmConversion 호출 실패")); return;}
	m_ErrFlag = ATF_ReadMicrostep(&m_MicroStep);
	if(m_ErrFlag != ErrOK) {Total_Msg(_T("ATF_ReadMicrostep 호출 실패")); return;}

	// LLC의 현재 위치를 알수 없음으로 합니다.
	m_LLC_ObjectiveNum = -1;

	SetTimer(1, 100, NULL);
}


void CLLC4_AF_ModuleDlg::OnBnClickedDisconnect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 통신연결을 끊기 전에 AF와 Laser를 Off해 줌.
	ATF_AfStop();
	//if(m_ErrFlag != ErrOK) {Total_Msg(_T("ATF_AfStop 호출 실패")); return;}
	Sleep(100);
	ATF_DisableLaser();
	//if(m_ErrFlag != ErrOK) {Total_Msg(_T("ATF_DisableLaser 호출 실패")); return;}
	Sleep(100);
	KillTimer(1);
	
	// 통신 연결 해제
	ATF_CloseConnection();
}


void CLLC4_AF_ModuleDlg::OnBnClickedLaserOn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL	IsConnect = ATF_isSerialConnection();	// 통신 연결 상태 Check

	if(IsConnect == TRUE)	// 통신이 연결된 상태면
	{
		m_ErrFlag = ATF_EnableLaser();	// Laser On
		if(m_ErrFlag != ErrOK) {Total_Msg(_T("ATF_EnableLaser 호출 실패"));}

		SetTimer(1, 100, NULL);
	}
	else					// 통신이 연결되지 않은 상태면
	{
		Total_Msg(_T("통신이 연결되지 않았습니다."));
	}
}


void CLLC4_AF_ModuleDlg::OnBnClickedLaserOff()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL	IsConnect = ATF_isSerialConnection();	// 통신 연결 상태 Check

	if(IsConnect == TRUE)	// 통신이 연결된 상태면
	{
		ATF_AfStop();		// Laser를 Off하기 전에 AF도 같이 꺼준다.
		Sleep(100);

		m_ErrFlag = ATF_DisableLaser();	// Laser Off
		if(m_ErrFlag != ErrOK) {Total_Msg(_T("ATF_DisableLaser 호출 실패"));}

		SetTimer(1, 100, NULL);
	}
	else					// 통신이 연결되지 않은 상태면
	{
		Total_Msg(_T("통신이 연결되지 않았습니다."));
	}
}


void CLLC4_AF_ModuleDlg::OnBnClickedAfOn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL	IsConnect = ATF_isSerialConnection();	// 통신 연결 상태 Check

	if(IsConnect == TRUE)	// 통신이 연결된 상태면
	{
		// Laser가 Off 상태라면 AF를 켜지 않는다.
		short	atf_Status= 0;
		ATF_ReadStatus(&atf_Status);
		if((atf_Status & MsEnableLaser) == 0) {	//Laser가 Off이면
			Total_Msg(_T("AF를 On하기 전에 Laser를 On해주세요."));
			return;
		}
		// AF가 On 상태라면 return.
		if((atf_Status & MsZTracking) != 0) {	//AF가 On이면
			Total_Msg(_T("이미 AF가 On 상태입니다."));
			return;
		}

		m_ErrFlag = ATF_AFTrack();	// AF On
		if(m_ErrFlag != ErrOK) {Total_Msg(_T("ATF_AFTrack 호출 실패"));}

		SetTimer(1, 100, NULL);
	}
	else					// 통신이 연결되지 않은 상태면
	{
		Total_Msg(_T("통신이 연결되지 않았습니다."));
	}
}


void CLLC4_AF_ModuleDlg::OnBnClickedAfOff()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL	IsConnect = ATF_isSerialConnection();	// 통신 연결 상태 Check

	if(IsConnect == TRUE)	// 통신이 연결된 상태면
	{
		ATF_AfStop();	// AF Off

		SetTimer(1, 100, NULL);
	}
	else					// 통신이 연결되지 않은 상태면
	{
		Total_Msg(_T("통신이 연결되지 않았습니다."));
	}
}


void CLLC4_AF_ModuleDlg::OnBnClickedZUp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL	IsConnect = ATF_isSerialConnection();	// 통신 연결 상태 Check

	if(IsConnect == TRUE)	// 통신이 연결된 상태면
	{
		// AF가 On 상태라면 Z축을 움직이지 않는다.
		short	atf_Status= 0;
		ATF_ReadStatus(&atf_Status);
		if((atf_Status & MsZTracking) != 0) {	//AF가 On이면
			Total_Msg(_T("AF가 On이면 Z축을 움직일 수 없습니다."));
			return;
		}

		CString cTempString;
		double	ZMove_um;
		long	Zmove_Parameter;

		m_ZMove_Num.GetWindowTextW(cTempString);
		ZMove_um = _tstof(cTempString);

		// 한번에 500um 이하로 움직이는걸 추천합니다.
		if		(ZMove_um < 0)		{ ZMove_um = 0;		m_ZMove_Num.SetWindowTextW(_T("0")); }
		else if	(ZMove_um > 500)	{ ZMove_um = 500;	m_ZMove_Num.SetWindowTextW(_T("500")); }

		Zmove_Parameter = (long)((ZMove_um*m_FullStep*m_MicroStep)/1000);	//m_FullStep:FullStep, m_MicroStep:MicroStep

		m_ErrFlag = ATF_MoveZ(Zmove_Parameter);	// Z축 이동
		if(m_ErrFlag != ErrOK) {Total_Msg(_T("ATF_MoveZ 호출 실패"));}

		SetTimer(1, 100, NULL);
	}
	else
	{
		Total_Msg(_T("통신이 연결되지 않았습니다."));
	}
}


void CLLC4_AF_ModuleDlg::OnBnClickedZDown()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL	IsConnect = ATF_isSerialConnection();	// 통신 연결 상태 Check

	if(IsConnect == TRUE)	// 통신이 연결된 상태면
	{
		// AF가 On 상태라면 Z축을 움직이지 않는다.
		short	atf_Status= 0;
		ATF_ReadStatus(&atf_Status);
		if((atf_Status & MsZTracking) != 0) {	//AF가 On이면
			Total_Msg(_T("AF가 On이면 Z축을 움직일 수 없습니다."));
			return;
		}

		CString cTempString;
		double	ZMove_um;
		long	Zmove_Parameter;

		m_ZMove_Num.GetWindowTextW(cTempString);
		ZMove_um = _tstof(cTempString);

		// 한번에 500um 이하로 움직이는걸 추천합니다.
		if		(ZMove_um < 0)		{ ZMove_um = 0;		m_ZMove_Num.SetWindowTextW(_T("0")); }
		else if	(ZMove_um > 500)	{ ZMove_um = 500;	m_ZMove_Num.SetWindowTextW(_T("500")); }

		Zmove_Parameter = (long)((ZMove_um*m_FullStep*m_MicroStep)/1000);	//m_FullStep:FullStep, m_MicroStep:MicroStep

		m_ErrFlag = ATF_MoveZ(-Zmove_Parameter);	// Z축 이동
		if(m_ErrFlag != ErrOK) {Total_Msg(_T("ATF_MoveZ 호출 실패"));}

		SetTimer(1, 100, NULL);
	}
	else
	{
		Total_Msg(_T("통신이 연결되지 않았습니다."));
	}
}


void CLLC4_AF_ModuleDlg::OnBnClickedZClear()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL	IsConnect = ATF_isSerialConnection();	// 통신 연결 상태 Check

	if(IsConnect == TRUE)	// 통신이 연결된 상태면
	{
		m_ErrFlag = ATF_WriteAbsZPos(0);	// Z축 Position값을 0으로 Clear
		if(m_ErrFlag != ErrOK) {Total_Msg(_T("ATF_WriteAbsZPos 호출 실패"));}

		SetTimer(1, 100, NULL);
	}
	else
	{
		Total_Msg(_T("통신이 연결되지 않았습니다."));
	}
}


void CLLC4_AF_ModuleDlg::OnBnClickedZHome()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL	IsConnect = ATF_isSerialConnection();	// 통신 연결 상태 Check

	if(IsConnect == TRUE)	// 통신이 연결된 상태면
	{
		// AF가 On 상태라면 Z축을 움직이지 않는다.
		short	atf_Status= 0;
		ATF_ReadStatus(&atf_Status);
		if((atf_Status & MsZTracking) != 0) {	//AF가 On이면
			Total_Msg(_T("AF가 On이면 Z축을 움직일 수 없습니다."));
			return;
		}

		// Z축 Home 시퀀스 실행 (Parameter:NULL은 Conole에서 Setting한 값을 사용한다는 의미)
		m_ErrFlag = ATF_RunHomingZ(NULL);	
		if(m_ErrFlag != ErrOK) {Total_Msg(_T("ATF_RunHomingZ 호출 실패"));}

		SetTimer(1, 100, NULL);
	}
	else
	{
		Total_Msg(_T("통신이 연결되지 않았습니다."));
	}
}


void CLLC4_AF_ModuleDlg::OnBnClickedMake0()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL	IsConnect = ATF_isSerialConnection();	// 통신 연결 상태 Check

	if(IsConnect == TRUE)	// 통신이 연결된 상태면
	{
		m_ErrFlag = ATF_Make0();
		if(m_ErrFlag != ErrOK) {Total_Msg(_T("ATF_Make0 호출 실패")); return; }
	}
	else
	{
		Total_Msg(_T("통신이 연결되지 않았습니다."));
	}
}


void CLLC4_AF_ModuleDlg::OnBnClickedLedSetPwm()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL	IsConnect = ATF_isSerialConnection();	// 통신 연결 상태 Check

	if(IsConnect == TRUE)	// 통신이 연결된 상태면
	{
		CString			cTempString;
		unsigned short	nLedPwm;

		m_LED_PwmNum.GetWindowTextW(cTempString);
		nLedPwm = (unsigned short)_tstol(cTempString);

		if((nLedPwm < 0) || (nLedPwm > 100))
		{
			Total_Msg(_T("LED Pwm은 0 ~ 100 사이의 값이어야 합니다."));
			return;
		}

		m_ErrFlag = ATF_WriteLedPwm(0, nLedPwm);	// 0번 채널을 가정합니다.
		if(m_ErrFlag != ErrOK) {Total_Msg(_T("ATF_WriteLedPwm 호출 실패"));}

		SetTimer(1, 100, NULL);
	}
	else
	{
		Total_Msg(_T("통신이 연결되지 않았습니다."));
	}
}


void CLLC4_AF_ModuleDlg::OnBnClickedLedSetCurrent()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL	IsConnect = ATF_isSerialConnection();	// 통신 연결 상태 Check

	if(IsConnect == TRUE)	// 통신이 연결된 상태면
	{
		CString			cTempString;
		unsigned short	nLedCurrent;

		m_LED_CurrentNum.GetWindowTextW(cTempString);
		nLedCurrent = (unsigned short)_tstol(cTempString);

		if((nLedCurrent < 50) || (nLedCurrent > 800))
		{
			Total_Msg(_T("LED Current는 50 ~ 800 사이의 값이어야 합니다."));
			return;
		}

		// 반드시 10으로 나눈 값을 Parameter로 넣어야합니다.
		nLedCurrent = nLedCurrent / 10;

		m_ErrFlag = ATF_WriteLedCurrent(0, nLedCurrent); // 0번 채널을 가정합니다.
		if(m_ErrFlag != ErrOK) {Total_Msg(_T("ATF_WriteLedCurrent 호출 실패"));}

		SetTimer(1, 100, NULL);
	}
	else
	{
		Total_Msg(_T("통신이 연결되지 않았습니다."));
	}
}

void CLLC4_AF_ModuleDlg::OnBnClickedLlcMotorOn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL	IsConnect = ATF_isSerialConnection();	// 통신 연결 상태 Check
	int		Err = 0;
	CString	cTempString;

	if(IsConnect == TRUE && g_LLC.LLC_IsConnected() == true)	// 통신이 연결된 상태면
	{
		// LLC 이동하기 전에 AF를 Off(LLC를 움직이는 모든 동작 이전에는 AF를 Off해야 합니다.)
		short	atf_Status= 0;
		ATF_ReadStatus(&atf_Status);
		if((atf_Status & MsZTracking) != 0) {	//AF가 On이면
			Total_Msg(_T("AF가 On이면 LLC를 Motor On할 수 없습니다."));
			return;
		}

		// LLC Motor Enable 호출
		Err = g_LLC.LLC_MotorEnable();

		if(Err == 0)		cTempString.Format(_T("LLC_MotorEnable Success"));
		else				cTempString.Format(_T("LLC_MotorEnable Fail"));

		SetTimer(2, 100, NULL);

		Total_Msg(cTempString);
	}
	else
	{
		Total_Msg(_T("통신이 연결되지 않았습니다."));
	}
}


void CLLC4_AF_ModuleDlg::OnBnClickedLlcMotorOff()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL	IsConnect = ATF_isSerialConnection();				// 통신 연결 상태 Check
	int		Err = 0;
	CString	cTempString;

	if(IsConnect == TRUE && g_LLC.LLC_IsConnected() == true)	// 통신이 연결된 상태면
	{
		// LLC 이동하기 전에 AF를 Off(LLC를 움직이는 모든 동작 이전에는 AF를 Off해야 합니다.)
		short	atf_Status= 0;
		ATF_ReadStatus(&atf_Status);
		if((atf_Status & MsZTracking) != 0) {	//AF가 On이면
			Total_Msg(_T("AF가 On이면 LLC를 Motor Off할 수 없습니다."));
			return;
		}

		// LLC Motor Disable 호출
		Err = g_LLC.LLC_MotorDisable();

		if(Err == 0)		{ cTempString.Format(_T("LLC_MotorDisable Success"));	m_LLC_ObjectiveNum = -1; } // 함수호출에 성공하면 LLC 위치 정보를 업데이트합니다.
		else				cTempString.Format(_T("LLC_MotorDisable Fail"));

		SetTimer(2, 100, NULL);

		Total_Msg(cTempString);
	}
	else
	{
		Total_Msg(_T("통신이 연결되지 않았습니다."));
	}
}


void CLLC4_AF_ModuleDlg::OnBnClickedLlcHome()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL	IsConnect = ATF_isSerialConnection();	// 통신 연결 상태 Check
	int		Err = 0;
	CString	cTempString;

	if(IsConnect == TRUE && g_LLC.LLC_IsConnected() == true)	// 통신이 연결된 상태면
	{
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// LLC Home을 하기 전에 AF를 Off(LLC를 움직이는 모든 동작 이전에는 AF를 Off해야 합니다.)
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		short	atf_Status= 0;
		ATF_ReadStatus(&atf_Status);
		if((atf_Status & MsZTracking) != 0) {	//AF가 On이면
			Total_Msg(_T("AF가 On이면 LLC를 Homing할 수 없습니다."));
			return;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// LLC Home 호출
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		g_LLC.LLC_LlcPeriodCheck();
		if(g_LLC.LLC_IsLLCMove() == true)	return;
		Err = g_LLC.LLC_MotorHome();

		if(Err == 0)		{ cTempString.Format(_T("LLC_MotorHome Success"));	m_LLC_ObjectiveNum = -1; } // 함수호출에 성공하면 LLC 위치 정보를 업데이트합니다.
		else				cTempString.Format(_T("LLC_MotorHome Fail"));

		SetTimer(2, 100, NULL);

		Total_Msg(cTempString);
	}
	else
	{
		Total_Msg(_T("통신이 연결되지 않았습니다."));
	}
}


void CLLC4_AF_ModuleDlg::OnBnClickedLlc1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL	IsConnect = ATF_isSerialConnection();	// 통신 연결 상태 Check
	int		Err = 0;
	CString	cTempString;

	if(IsConnect == TRUE && g_LLC.LLC_IsConnected() == true)	// 통신이 연결된 상태면
	{
		// LLC 이동하기 전에 그리고 Lens Setting을 바꾸기 전에 AF를 Off(LLC를 움직이는 모든 동작 이전에는 AF를 Off해야 합니다.)
		short	atf_Status= 0;
		ATF_ReadStatus(&atf_Status);
		if((atf_Status & MsZTracking) != 0) {	//AF가 On이면
			Total_Msg(_T("AF가 On이면 Lens Setting 변경과 LLC를 이동할 수 없습니다."));
			return;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// LLC Move 호출(Parameter 0:LLC 첫째 구멍, LLC를 움직이기 전에 반드시 AF를 Off해야 합니다.)
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		g_LLC.LLC_LlcPeriodCheck();
		if(g_LLC.LLC_IsLLCMove() == true)	{ Total_Msg(_T("현재 LLC가 움직이는 중입니다. 다시 시도해 주세요"));		return; }
		Err = g_LLC.LLC_MoveToObjective(0);

		if(Err == 0)		{ cTempString.Format(_T("LLC_MoveToObjective Success"));	m_LLC_ObjectiveNum = 0; }
		else				cTempString.Format(_T("LLC_MoveToObjective Fail"));

		SetTimer(2, 100, NULL);

		Total_Msg(cTempString);

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// LLC Move를 호출한 후에 변경한 LLC에 맞는 Lens Setting으로 바꾸어 줍니다.
		// Lens Setting을 바꾸는 함수 호출 전에 반드시 AF를 Off해야 합니다. 
		// (Parameter 0: 첫째 Lens Setting)
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		m_ErrFlag = ATF_WriteObjNum(0);
		if(m_ErrFlag != ErrOK) {Total_Msg(_T("ATF_WriteObjNum 호출 실패")); return;}
	}

	else
	{
		Total_Msg(_T("통신이 연결되지 않았습니다."));
	}
}


void CLLC4_AF_ModuleDlg::OnBnClickedLlc2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL	IsConnect = ATF_isSerialConnection();	// 통신 연결 상태 Check
	int		Err = 0;
	CString	cTempString;

	if(IsConnect == TRUE && g_LLC.LLC_IsConnected() == true)	// 통신이 연결된 상태면
	{
		// LLC 이동하기 전에 그리고 Lens Setting을 바꾸기 전에 AF를 Off(LLC를 움직이는 모든 동작 이전에는 AF를 Off해야 합니다.)
		short	atf_Status= 0;
		ATF_ReadStatus(&atf_Status);
		if((atf_Status & MsZTracking) != 0) {	//AF가 On이면
			Total_Msg(_T("AF가 On이면 Lens Setting 변경과 LLC를 이동할 수 없습니다."));
			return;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// LLC Move 호출(Parameter 1:LLC 두번째 구멍, LLC를 움직이기 전에 반드시 AF를 Off해야 합니다.)
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		g_LLC.LLC_LlcPeriodCheck();
		if(g_LLC.LLC_IsLLCMove() == true)	{ Total_Msg(_T("현재 LLC가 움직이는 중입니다. 다시 시도해 주세요"));		return; }
		Err = g_LLC.LLC_MoveToObjective(1);

		if(Err == 0)		{ cTempString.Format(_T("LLC_MoveToObjective Success"));	m_LLC_ObjectiveNum = 1; }
		else				cTempString.Format(_T("LLC_MoveToObjective Fail"));

		SetTimer(2, 100, NULL);

		Total_Msg(cTempString);

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// LLC Move를 호출한 후에 변경한 LLC에 맞는 Lens Setting으로 바꾸어 줍니다.
		// Lens Setting을 바꾸는 함수 호출 전에 반드시 AF를 Off해야 합니다. 
		// (Parameter 1: 두번째 Lens Setting)
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		m_ErrFlag = ATF_WriteObjNum(1);
		if(m_ErrFlag != ErrOK) {Total_Msg(_T("ATF_WriteObjNum 호출 실패")); return;}
	}

	else
	{
		Total_Msg(_T("통신이 연결되지 않았습니다.")); 
	}
}


void CLLC4_AF_ModuleDlg::OnBnClickedLlc3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL	IsConnect = ATF_isSerialConnection();	// 통신 연결 상태 Check
	int		Err = 0;
	CString	cTempString;

	if(IsConnect == TRUE && g_LLC.LLC_IsConnected() == true)	// 통신이 연결된 상태면
	{
		// LLC 이동하기 전에 그리고 Lens Setting을 바꾸기 전에 AF를 Off(LLC를 움직이는 모든 동작 이전에는 AF를 Off해야 합니다.)
		short	atf_Status= 0;
		ATF_ReadStatus(&atf_Status);
		if((atf_Status & MsZTracking) != 0) {	//AF가 On이면
			Total_Msg(_T("AF가 On이면 Lens Setting 변경과 LLC를 이동할 수 없습니다."));
			return;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// LLC Move 호출(Parameter 2:LLC 세번째 구멍, LLC를 움직이기 전에 반드시 AF를 Off해야 합니다.)
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		g_LLC.LLC_LlcPeriodCheck();
		if(g_LLC.LLC_IsLLCMove() == true)	{ Total_Msg(_T("현재 LLC가 움직이는 중입니다. 다시 시도해 주세요"));		return; }
		Err = g_LLC.LLC_MoveToObjective(2);

		if(Err == 0)		{ cTempString.Format(_T("LLC_MoveToObjective Success"));	m_LLC_ObjectiveNum = 2; }
		else				cTempString.Format(_T("LLC_MoveToObjective Fail"));

		SetTimer(2, 100, NULL);

		Total_Msg(cTempString);

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// LLC Move를 호출한 후에 변경한 LLC에 맞는 Lens Setting으로 바꾸어 줍니다.
		// Lens Setting을 바꾸는 함수 호출 전에 반드시 AF를 Off해야 합니다. 
		// (Parameter 2: 세번째 Lens Setting)
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		m_ErrFlag = ATF_WriteObjNum(2);
		if(m_ErrFlag != ErrOK) {Total_Msg(_T("ATF_WriteObjNum 호출 실패")); return;}
	}

	else
	{
		Total_Msg(_T("통신이 연결되지 않았습니다."));
	}
}


void CLLC4_AF_ModuleDlg::OnBnClickedLlc4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL	IsConnect = ATF_isSerialConnection();	// 통신 연결 상태 Check
	int		Err = 0;
	CString	cTempString;

	if(IsConnect == TRUE && g_LLC.LLC_IsConnected() == true)	// 통신이 연결된 상태면
	{
		// LLC 이동하기 전에 그리고 Lens Setting을 바꾸기 전에 AF를 Off(LLC를 움직이는 모든 동작 이전에는 AF를 Off해야 합니다.)
		short	atf_Status= 0;
		ATF_ReadStatus(&atf_Status);
		if((atf_Status & MsZTracking) != 0) {	//AF가 On이면
			Total_Msg(_T("AF가 On이면 Lens Setting 변경과 LLC를 이동할 수 없습니다."));
			return;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// LLC Move 호출(Parameter 3:LLC 네번째 구멍, LLC를 움직이기 전에 반드시 AF를 Off해야 합니다.)
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		g_LLC.LLC_LlcPeriodCheck();
		if(g_LLC.LLC_IsLLCMove() == true)	{ Total_Msg(_T("현재 LLC가 움직이는 중입니다. 다시 시도해 주세요"));		return; }
		Err = g_LLC.LLC_MoveToObjective(3);

		if(Err == 0)		{ cTempString.Format(_T("LLC_MoveToObjective Success"));	m_LLC_ObjectiveNum = 3; }
		else				cTempString.Format(_T("LLC_MoveToObjective Fail"));

		SetTimer(2, 100, NULL);

		Total_Msg(cTempString);

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// LLC Move를 호출하나 후에 변경할 LLC에 맞는 Lens Setting으로 바꾸어 줍니다.
		// Lens Setting을 바꾸는 함수 호출 전에 반드시 AF를 Off해야 합니다. 
		// (Parameter 3: 네번째 Lens Setting) => 4번째 Lens Setting이 안되어 있기 때문에 ATF_WriteObjNum 함수 호풀에 실패할 것입니다.
		// 추후 쓰게도면 4번째 Lens Setting을 적용하고 쓰시면 됩니다.
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		m_ErrFlag = ATF_WriteObjNum(3);
		if(m_ErrFlag != ErrOK) {Total_Msg(_T("ATF_WriteObjNum 호출 실패")); return;}
	}

	else
	{
		Total_Msg(_T("통신이 연결되지 않았습니다."));
	}
}

void CLLC4_AF_ModuleDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(nIDEvent == 1)
	{
		CString	cTempString;
		int		atf_HW_Status;
		short	atf_Status;

		int		Flag_CW, Flag_CCW;
		short	Flag_Laser, Flag_AF, Flag_InFocus, Flag_InRange;

		// 통신 연결 여부를 표시한다.
		BOOL	IsConnect = ATF_isSerialConnection();	// 통신 연결 상태 Check
		if(IsConnect == TRUE)	cTempString.Format(_T("ON"));
		else					cTempString.Format(_T("OFF"));
		m_Status_Communication.SetWindowTextW(cTempString);
		

		if((ATF_ReadHwStat(&atf_HW_Status)==ErrOK) && (ATF_ReadStatus(&atf_Status) == ErrOK))		// AF의 Status값을 불러오는데 성공하면
		{

			Flag_InFocus	= atf_Status & MsInFocus;			// In Focus 여부 상태(Flag_InFocus != 0이면 In Focus 상태)
			Flag_InRange	= atf_Status & MsMiv;				// In Range 여부 상태(Flag_InRange != 0이면 In Range 상태)
			Flag_Laser		= atf_Status & MsEnableLaser;		// Laser On/Off 상태 (Flag_Laser = 0이면 Laser Off, Flag_Laser != 0이면 Laser On)
			Flag_AF			= atf_Status & MsZTracking;			// AF On/Off 상태(Flag_AF = 0이면 AF Off, Flag_AF != 0이면 AF On)
			
			Flag_CW			= atf_HW_Status & HwMotionCWLimit;	// CW Limit 상태(Flag_CW = 1이면 CW Limit)
			Flag_CCW		= atf_HW_Status & HwMotionCCWLimit; // CCW Limit 상태(Flag_CCW = 1이면 CCW Limit)

			// Laser On/Off 여부를 표시한다.
			if(Flag_Laser == 0)	cTempString.Format(_T("OFF"));
			else				cTempString.Format(_T("ON"));
			m_Status_Laser.SetWindowTextW(cTempString);

			// AF On/Off 여부를 표시한다.
			if(Flag_AF == 0)	cTempString.Format(_T("OFF"));
			else				cTempString.Format(_T("ON"));
			m_Status_AF.SetWindowTextW(cTempString);

			// In Focus와 InRange 표시(Laser가 Off면 둘다 Off)
			// In Focus 여부를 표시한다.
			if(Flag_InFocus == 0)	cTempString.Format(_T("OFF"));
			else					cTempString.Format(_T("ON"));
			m_Status_Infocus.SetWindowTextW(cTempString);

			// In Range 여부를 표시한다.
			if(Flag_InRange == 0)	cTempString.Format(_T("OFF"));
			else					cTempString.Format(_T("ON"));
			m_Status_Inrange.SetWindowTextW(cTempString);


			// CW Limit 여부를 표시한다.
			if(Flag_CW == 0)	cTempString.Format(_T("OFF"));
			else				cTempString.Format(_T("ON"));
			m_Status_CW.SetWindowTextW(cTempString);

			// CCW Limit 여부를 표시한다.
			if(Flag_CCW == 0)	cTempString.Format(_T("OFF"));
			else				cTempString.Format(_T("ON"));
			m_Status_CCW.SetWindowTextW(cTempString);
		}


		// Z축 Position값 표시
		int		absZ;
		m_ErrFlag	= ATF_ReadAbsZPos(&absZ);
		if(m_ErrFlag == ErrOK)
		{
			// 함수로 얻어온 Step단위의 absZ값을 um단위로 변환한다.
			float	iZPositionUm = (float) ( ((float)absZ*1000.0f) / ((float)m_FullStep * (float)m_MicroStep) );
			cTempString.Format(_T("%.2f"), iZPositionUm);

			m_ZPosition.SetWindowTextW(cTempString);
		}

		unsigned short	nLedCurrent = 0, nLedPWM = 0;

		// 현재 LED Current 표시
		m_ErrFlag = ATF_ReadLedCurrent(0, &nLedCurrent);
		if(m_ErrFlag == ErrOK)
		{
			cTempString.Format(_T("%d"), nLedCurrent*10);	//LED Current는 얻어온 값은 10배 해주어야 한다.
			m_Status_LEDCurrent.SetWindowTextW(cTempString);
		}

		// 현재 LED Current 표시
		m_ErrFlag = ATF_ReadLedPwm(0, &nLedPWM);
		if(m_ErrFlag == ErrOK)
		{
			cTempString.Format(_T("%d"), nLedPWM);	
			m_Status_LEDPwm.SetWindowTextW(cTempString);
		}

		// 현재 Lens Setting 번호 표시
		int pObj;
		m_ErrFlag = ATF_ReadObjNum(&pObj);
		if(m_ErrFlag == ErrOK)
		{
			cTempString.Format(_T("%d"), pObj);	
			m_Status_LensSettingNum.SetWindowTextW(cTempString);
		}

		KillTimer(1);

	}

	else if (nIDEvent == 2)
	{
		CString	cTempString;
		int			nStatus = -1;

		// LLC 통신 연결 여부 표시
		bool	bIsLLCConnecte = g_LLC.LLC_IsConnected();
		if(bIsLLCConnecte == true)	cTempString.Format(_T("ON"));
		else						cTempString.Format(_T("OFF"));
		m_Status_LLC_Communication.SetWindowTextW(cTempString);


		// 현재 LLC Home 여부 Status 표시
		nStatus = g_LLC.LLC_Get_HomeStatus();
		if(nStatus == -1)		cTempString.Format(_T("Homing 안함"));
		else if	(nStatus == 0)	cTempString.Format(_T("Homing 중"));
		else if (nStatus == 1)	cTempString.Format(_T("Homing 완료"));
		m_Home_Status.SetWindowTextW(cTempString);

		// 현재 LLC 위치 번호 표시
		nStatus = g_LLC.LLC_Get_CurrentObjective();
		cTempString.Format(_T("Current Obj Num: %d"), nStatus);

		m_Objective_Position.SetWindowTextW(cTempString);
		m_Status_LLCPosition.SetWindowTextW(cTempString);

		// 현재 LLC Motor On/Off 여부 표시
		nStatus = g_LLC.LLC_Get_MotorStatus();
		if		(nStatus == 0)	cTempString.Format(_T("Motor Off"));
		else if (nStatus == 1)	cTempString.Format(_T("Motor On"));
		m_Motor_Status.SetWindowTextW(cTempString);


		KillTimer(2);
	}

	CDialogEx::OnTimer(nIDEvent);
}

int CLLC4_AF_ModuleDlg::GetCurrentLLSPos()
{
	BOOL	IsConnect = ATF_isSerialConnection();	// 통신 연결 상태 Check
	int		Err = 0;
	int		nReturn = -1;
	CString	cTempString;

	if (IsConnect == TRUE && g_LLC.LLC_IsConnected() == true)	// 통신이 연결된 상태면
	{
		nReturn = g_LLC.LLC_Get_CurrentObjective();
	}
	else
	{
		Total_Msg(_T("통신이 연결되지 않았습니다."));
	}

	return nReturn;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CLLC4_AF_ModuleDlg::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	OnBnClickedDisconnect();
	CDialogEx::OnClose();
}


void CLLC4_AF_ModuleDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnOK();
}


void CLLC4_AF_ModuleDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnBnClickedDisconnect();
	CDialogEx::OnCancel();
}


//////////////////////////////////////////////////////////////////////////////////////////



void CLLC4_AF_ModuleDlg::OnBnClickedConnectLlc()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString		TempString;
	long		PortNum;
	int			Err = 0;
	CString		cTempString;

	m_Comport_Num_LLC.GetWindowTextW(TempString);
	PortNum = _tstol(TempString);

	Err = g_LLC.LLC_OpenComport(PortNum, "llc_offset.txt", "llc_parameter.txt");
	if(Err == 0)		cTempString.Format(_T("SUCCESS"));
	else				cTempString.Format(_T("FAIL"));

	SetTimer(2, 100, NULL);

	Total_Msg(cTempString);
}


void CLLC4_AF_ModuleDlg::OnBnClickedDisconnectLlc()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int			Err = 0;
	CString		cTempString;

	if(g_LLC.LLC_IsConnected())
	{
		Err = g_LLC.LLC_CloseComport();
	}
	if(Err == 0)		cTempString.Format(_T("SUCCESS"));
	else				cTempString.Format(_T("FAIL"));

	//Total_Msg(cTempString);

	KillTimer(2);
}


void CLLC4_AF_ModuleDlg::comportConnect()
{

	long		PortNum;
	int			Err = 0;
	char	Com_Name[20];

	// 이미 통신이 연결되어 있는지 체크
	m_ErrFlag = ATF_PingAck();
	if (m_ErrFlag == ErrOK) { Total_Msg(_T("이미 통신이 연결되었습니다.")); return; }


	PortNum = COM_PORT_LLC_ATF;

	sprintf(Com_Name, "\\\\.\\COM%d", PortNum);

	//	통신 연결
	m_ErrFlag = ATF_OpenConnection(Com_Name, 9600);

	// ErrOK = 0, 모든 ATF 함수는 return값이 0일 때 정상작동.
	if (m_ErrFlag != ErrOK)
	{
		Total_Msg(_T("ATF_OpenConnection 호출 실패"));
		return;
	}

	// 통신 연결 후 기본적인 초기화 작업(Laser와 AF OFF)
	ATF_AfStop();
	Sleep(100);
	m_ErrFlag = ATF_DisableLaser();
	if (m_ErrFlag != ErrOK) { Total_Msg(_T("ATF_DisableLaser 호출 실패")); return; }
	Sleep(100);

	// FullStep과 MicroStep값을 얻어옮(Z축 제어에 쓰임)
	m_ErrFlag = ATF_ReadStepPerMmConversion(&m_FullStep);
	if (m_ErrFlag != ErrOK) { Total_Msg(_T("ATF_ReadStepPerMmConversion 호출 실패")); return; }
	m_ErrFlag = ATF_ReadMicrostep(&m_MicroStep);
	if (m_ErrFlag != ErrOK) { Total_Msg(_T("ATF_ReadMicrostep 호출 실패")); return; }

	// LLC의 현재 위치를 알수 없음으로 합니다.
	m_LLC_ObjectiveNum = -1;

	PortNum = COM_PORT_LLC_LENS;

	CString path, section;
	TCHAR	exepath[MAX_PATH];
	char	cPath[MAX_PATH];

	//jini
	GetModuleFileName(NULL, exepath, sizeof(exepath));
	path = exepath;
	int i = path.ReverseFind('\\');
	path = path.Left(i);
	path.Append(_T("\\Data\\LLC\\llc_offset.txt"));
	strcpy_s((char*)cPath, path.GetLength() + 1, CT2A(path));

	Err = g_LLC.LLC_OpenComport(PortNum, cPath);

	if (Err == 0)
	{
		Total_Msg(_T("LLC Lens Connect Success"));

		if (CSystemData::m_Option.Info.m_bZoomCamAutoInitializeUse) //KJT 20210824 Add
			Devs::m_AutoLaserFocusFlow.Start();

		SharedInfo::ZoomConnectFlag = TRUE;
	}
	else
	{
		SharedInfo::ZoomConnectFlag = FALSE;
		Total_Msg(_T("Connect Fail"));
	}
		

}

void CLLC4_AF_ModuleDlg::LedSetPwmCurrent(int Pwm, int Current)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL	IsConnect = ATF_isSerialConnection();	// 통신 연결 상태 Check

	if (IsConnect == TRUE)	// 통신이 연결된 상태면
	{
		unsigned short	nLedPwm;

		nLedPwm = (unsigned short)Pwm;

		if ((nLedPwm < 0) || (nLedPwm > 100))
		{
			Total_Msg(_T("LED Pwm은 0 ~ 100 사이의 값이어야 합니다."));
			return;
		}

		m_ErrFlag = ATF_WriteLedPwm(0, nLedPwm);	// 0번 채널을 가정합니다.
		if (m_ErrFlag != ErrOK) { Total_Msg(_T("ATF_WriteLedPwm 호출 실패")); }


		unsigned short	nLedCurrent;

		nLedCurrent = (unsigned short)Current;

		if ((nLedCurrent < 50) || (nLedCurrent > 800))
		{
			Total_Msg(_T("LED Current는 50 ~ 800 사이의 값이어야 합니다."));
			return;
		}

		// 반드시 10으로 나눈 값을 Parameter로 넣어야합니다.
		nLedCurrent = nLedCurrent / 10;

		m_ErrFlag = ATF_WriteLedCurrent(0, nLedCurrent); // 0번 채널을 가정합니다.
		if (m_ErrFlag != ErrOK) { Total_Msg(_T("ATF_WriteLedCurrent 호출 실패")); }
	}
	else
	{
		Total_Msg(_T("통신이 연결되지 않았습니다."));
	}
}


BOOL CLLC4_AF_ModuleDlg::IsATFSerialConnection()
{
	return ATF_isSerialConnection();
}

BOOL CLLC4_AF_ModuleDlg::IsLLCSerialConnection()
{
	return g_LLC.LLC_IsConnected();
}

BOOL CLLC4_AF_ModuleDlg::LLCGetMotorStatus()
{
	return g_LLC.LLC_Get_MotorStatus();
}

BOOL CLLC4_AF_ModuleDlg::LLCGetHomeStatus()
{
	return g_LLC.LLC_Get_HomeStatus();
}

int	CLLC4_AF_ModuleDlg::LLCGetCurrentObjective()
{
	return g_LLC.LLC_Get_CurrentObjective();
}

BOOL CLLC4_AF_ModuleDlg::GetLaserOnStatus()
{
	short	atf_Status;
	short	Flag_Laser, Flag_AF, Flag_InFocus, Flag_InRange;

	ATF_ReadStatus(&atf_Status);

	Flag_InFocus = atf_Status & MsInFocus;			// In Focus 여부 상태(Flag_InFocus != 0이면 In Focus 상태)
	Flag_InRange = atf_Status & MsMiv;				// In Range 여부 상태(Flag_InRange != 0이면 In Range 상태)
	Flag_Laser = atf_Status & MsEnableLaser;		// Laser On/Off 상태 (Flag_Laser = 0이면 Laser Off, Flag_Laser != 0이면 Laser On)
	Flag_AF = atf_Status & MsZTracking;			// AF On/Off 상태(Flag_AF = 0이면 AF Off, Flag_AF != 0이면 AF On)

	return (Flag_Laser != 0);
}

BOOL CLLC4_AF_ModuleDlg::GetLaserInFocusStatus()
{
	short	atf_Status;
	short	Flag_Laser, Flag_AF, Flag_InFocus, Flag_InRange;

	ATF_ReadStatus(&atf_Status);

	Flag_InFocus = atf_Status & MsInFocus;			// In Focus 여부 상태(Flag_InFocus != 0이면 In Focus 상태)
	Flag_InRange = atf_Status & MsMiv;				// In Range 여부 상태(Flag_InRange != 0이면 In Range 상태)
	Flag_Laser = atf_Status & MsEnableLaser;		// Laser On/Off 상태 (Flag_Laser = 0이면 Laser Off, Flag_Laser != 0이면 Laser On)
	Flag_AF = atf_Status & MsZTracking;			// AF On/Off 상태(Flag_AF = 0이면 AF Off, Flag_AF != 0이면 AF On)

	return (Flag_InFocus != 0);
}

BOOL CLLC4_AF_ModuleDlg::GetLaserAFStatus()
{
	short	atf_Status;
	short	Flag_Laser, Flag_AF, Flag_InFocus, Flag_InRange;

	ATF_ReadStatus(&atf_Status);

	Flag_InFocus = atf_Status & MsInFocus;			// In Focus 여부 상태(Flag_InFocus != 0이면 In Focus 상태)
	Flag_InRange = atf_Status & MsMiv;				// In Range 여부 상태(Flag_InRange != 0이면 In Range 상태)
	Flag_Laser = atf_Status & MsEnableLaser;		// Laser On/Off 상태 (Flag_Laser = 0이면 Laser Off, Flag_Laser != 0이면 Laser On)
	Flag_AF = atf_Status & MsZTracking;			// AF On/Off 상태(Flag_AF = 0이면 AF Off, Flag_AF != 0이면 AF On)

	return (Flag_AF != 0);
}

void CLLC4_AF_ModuleDlg::OnBnClickedLlcInitialize()
{
	CString Str = _T("");
	BOOL bRtn = FALSE;

	Str.Format(_T("LLC Initialize ?"));
	if (IDOK != AfxMessageBox(Str, MB_OKCANCEL)) return;

	Devs::m_AutoLaserFocusFlow.Start();
}

#pragma region //KJT 20210805
BOOL CLLC4_AF_ModuleDlg::ZoomCamZMove(double dDist)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	BOOL	IsConnect = ATF_isSerialConnection();	// 통신 연결 상태 Check

	if (IsConnect == TRUE)	// 통신이 연결된 상태면
	{
		// AF가 On 상태라면 Z축을 움직이지 않는다.
		int		atf_HW_Status;
		short	atf_Status;
		if ((ATF_ReadHwStat(&atf_HW_Status) == ErrOK) && (ATF_ReadStatus(&atf_Status) == ErrOK))		// AF의 Status값을 불러오는데 성공하면
		{
			if ((atf_Status & MsZTracking) != 0)
				return FALSE; //AF가 On이면

			if ((atf_HW_Status & HwMotionZ) != 0) //0 : Stop Status
				return FALSE; //Busy

			// 한번에 500um 이하로 움직이는걸 추천합니다.
			if (dDist < -500)
				dDist = -500;
			else if (dDist > 500)
				dDist = 500;

			dDist *= 10.0;

			SharedInfo::bMachineStopFlag = FALSE;
			m_ErrFlag = ATF_MoveZ(dDist);	// Z축 이동 //dDist 100이면 10um
			if (m_ErrFlag != ErrOK)
			{
				Total_Msg(_T("ATF_MoveZ 호출 실패"));
				return FALSE;
			}
			else
				return TRUE;
		}
		else
			return FALSE;
	}
	else
	{
		Total_Msg(_T("통신이 연결되지 않았습니다."));
		return FALSE;
	}
}
int CLLC4_AF_ModuleDlg::Is_ZoomCamZ_Busy()
{
	int		atf_HW_Status;
	short	atf_Status;
	int nHwMotionFlag = 1;
	BOOL	IsConnect = ATF_isSerialConnection();	// 통신 연결 상태 Check
	if (IsConnect == TRUE)	// 통신이 연결된 상태면
	{
		if (ATF_ReadHwStat(&atf_HW_Status) == ErrOK)		// AF의 Status값을 불러오는데 성공하면
		{
			nHwMotionFlag = atf_HW_Status & HwMotionZ;
			if (nHwMotionFlag == 0) //0 : Stop Status
				return 0;
			else
				return 1;
		}
		else
			return -1;
	}
	else
	{
		return -1;
	}
}
BOOL CLLC4_AF_ModuleDlg::ZoomCamZStop()
{
	ATF_AfStop();
	Sleep(100);
	ATF_StopZMotor();

	Total_Msg(_T("ZoomStop"));

	return TRUE;
}
#pragma endregion
