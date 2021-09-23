
// LLC4_AF_ModuleDlg.cpp : ���� ����
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

// CLLC4_AF_ModuleDlg ��ȭ ����

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


// CLLC4_AF_ModuleDlg �޽��� ó����

BOOL CLLC4_AF_ModuleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_ZMove_Num.SetWindowTextW(_T("10.0"));

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CLLC4_AF_ModuleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CLLC4_AF_ModuleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////


void CLLC4_AF_ModuleDlg::OnBnClickedConnect()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	CString TempString;
	long	PortNum;
	char	Com_Name[20];
	
	// �̹� ����� ����Ǿ� �ִ��� üũ
	m_ErrFlag = ATF_PingAck();
	if(m_ErrFlag == ErrOK)	{ Total_Msg(_T("�̹� ����� ����Ǿ����ϴ�.")); return;}

	m_Comport_Num.GetWindowTextW(TempString);
	PortNum = _tstol(TempString);

	sprintf(Com_Name, "\\\\.\\COM%d", PortNum);

	//	��� ����
	m_ErrFlag = ATF_OpenConnection(Com_Name, 9600);

	// ErrOK = 0, ��� ATF �Լ��� return���� 0�� �� �����۵�.
	if(m_ErrFlag != ErrOK )
	{
		Total_Msg(_T("ATF_OpenConnection ȣ�� ����"));
		return;
	}

	// LLC�� Initialize�� �Ѵ�(LLC Home���� �ٸ�)
	/*ATF_initializeLlc(NULL, &m_ErrFlag);
	
	if		(m_ErrFlag == 10) {	//iLLC_err�� 10�̸� LLC�� �� ������ �Է����־�� �մϴ�. �� �۾��� �մϴ�.
		int	LLC_Num = ATF_getObjectiveNum();
		if(LLC_Num == 0)	{ATF_setObjectiveNum(4);}
		else				{ATF_setObjectiveNum(LLC_Num);}
	}
	else if (m_ErrFlag != ErrOK) { //LLC Initialize�Լ� ȣ�⿡ �����ϸ� ��ŵ� ���� �����ش�..
		Total_Msg(_T("ATF_initializeLlc ȣ�� ����")); 
		ATF_CloseConnection(); 
		return;
	}*/


	// ��� ���� �� �⺻���� �ʱ�ȭ �۾�(Laser�� AF OFF)
	ATF_AfStop();
	Sleep(100);
	m_ErrFlag = ATF_DisableLaser();
	if(m_ErrFlag != ErrOK) {Total_Msg(_T("ATF_DisableLaser ȣ�� ����")); return;}
	Sleep(100);

	// FullStep�� MicroStep���� ����(Z�� ��� ����)
	m_ErrFlag = ATF_ReadStepPerMmConversion(&m_FullStep);
	if(m_ErrFlag != ErrOK) {Total_Msg(_T("ATF_ReadStepPerMmConversion ȣ�� ����")); return;}
	m_ErrFlag = ATF_ReadMicrostep(&m_MicroStep);
	if(m_ErrFlag != ErrOK) {Total_Msg(_T("ATF_ReadMicrostep ȣ�� ����")); return;}

	// LLC�� ���� ��ġ�� �˼� �������� �մϴ�.
	m_LLC_ObjectiveNum = -1;

	SetTimer(1, 100, NULL);
}


void CLLC4_AF_ModuleDlg::OnBnClickedDisconnect()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	// ��ſ����� ���� ���� AF�� Laser�� Off�� ��.
	ATF_AfStop();
	//if(m_ErrFlag != ErrOK) {Total_Msg(_T("ATF_AfStop ȣ�� ����")); return;}
	Sleep(100);
	ATF_DisableLaser();
	//if(m_ErrFlag != ErrOK) {Total_Msg(_T("ATF_DisableLaser ȣ�� ����")); return;}
	Sleep(100);
	KillTimer(1);
	
	// ��� ���� ����
	ATF_CloseConnection();
}


void CLLC4_AF_ModuleDlg::OnBnClickedLaserOn()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	BOOL	IsConnect = ATF_isSerialConnection();	// ��� ���� ���� Check

	if(IsConnect == TRUE)	// ����� ����� ���¸�
	{
		m_ErrFlag = ATF_EnableLaser();	// Laser On
		if(m_ErrFlag != ErrOK) {Total_Msg(_T("ATF_EnableLaser ȣ�� ����"));}

		SetTimer(1, 100, NULL);
	}
	else					// ����� ������� ���� ���¸�
	{
		Total_Msg(_T("����� ������� �ʾҽ��ϴ�."));
	}
}


void CLLC4_AF_ModuleDlg::OnBnClickedLaserOff()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	BOOL	IsConnect = ATF_isSerialConnection();	// ��� ���� ���� Check

	if(IsConnect == TRUE)	// ����� ����� ���¸�
	{
		ATF_AfStop();		// Laser�� Off�ϱ� ���� AF�� ���� ���ش�.
		Sleep(100);

		m_ErrFlag = ATF_DisableLaser();	// Laser Off
		if(m_ErrFlag != ErrOK) {Total_Msg(_T("ATF_DisableLaser ȣ�� ����"));}

		SetTimer(1, 100, NULL);
	}
	else					// ����� ������� ���� ���¸�
	{
		Total_Msg(_T("����� ������� �ʾҽ��ϴ�."));
	}
}


void CLLC4_AF_ModuleDlg::OnBnClickedAfOn()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	BOOL	IsConnect = ATF_isSerialConnection();	// ��� ���� ���� Check

	if(IsConnect == TRUE)	// ����� ����� ���¸�
	{
		// Laser�� Off ���¶�� AF�� ���� �ʴ´�.
		short	atf_Status= 0;
		ATF_ReadStatus(&atf_Status);
		if((atf_Status & MsEnableLaser) == 0) {	//Laser�� Off�̸�
			Total_Msg(_T("AF�� On�ϱ� ���� Laser�� On���ּ���."));
			return;
		}
		// AF�� On ���¶�� return.
		if((atf_Status & MsZTracking) != 0) {	//AF�� On�̸�
			Total_Msg(_T("�̹� AF�� On �����Դϴ�."));
			return;
		}

		m_ErrFlag = ATF_AFTrack();	// AF On
		if(m_ErrFlag != ErrOK) {Total_Msg(_T("ATF_AFTrack ȣ�� ����"));}

		SetTimer(1, 100, NULL);
	}
	else					// ����� ������� ���� ���¸�
	{
		Total_Msg(_T("����� ������� �ʾҽ��ϴ�."));
	}
}


void CLLC4_AF_ModuleDlg::OnBnClickedAfOff()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	BOOL	IsConnect = ATF_isSerialConnection();	// ��� ���� ���� Check

	if(IsConnect == TRUE)	// ����� ����� ���¸�
	{
		ATF_AfStop();	// AF Off

		SetTimer(1, 100, NULL);
	}
	else					// ����� ������� ���� ���¸�
	{
		Total_Msg(_T("����� ������� �ʾҽ��ϴ�."));
	}
}


void CLLC4_AF_ModuleDlg::OnBnClickedZUp()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	BOOL	IsConnect = ATF_isSerialConnection();	// ��� ���� ���� Check

	if(IsConnect == TRUE)	// ����� ����� ���¸�
	{
		// AF�� On ���¶�� Z���� �������� �ʴ´�.
		short	atf_Status= 0;
		ATF_ReadStatus(&atf_Status);
		if((atf_Status & MsZTracking) != 0) {	//AF�� On�̸�
			Total_Msg(_T("AF�� On�̸� Z���� ������ �� �����ϴ�."));
			return;
		}

		CString cTempString;
		double	ZMove_um;
		long	Zmove_Parameter;

		m_ZMove_Num.GetWindowTextW(cTempString);
		ZMove_um = _tstof(cTempString);

		// �ѹ��� 500um ���Ϸ� �����̴°� ��õ�մϴ�.
		if		(ZMove_um < 0)		{ ZMove_um = 0;		m_ZMove_Num.SetWindowTextW(_T("0")); }
		else if	(ZMove_um > 500)	{ ZMove_um = 500;	m_ZMove_Num.SetWindowTextW(_T("500")); }

		Zmove_Parameter = (long)((ZMove_um*m_FullStep*m_MicroStep)/1000);	//m_FullStep:FullStep, m_MicroStep:MicroStep

		m_ErrFlag = ATF_MoveZ(Zmove_Parameter);	// Z�� �̵�
		if(m_ErrFlag != ErrOK) {Total_Msg(_T("ATF_MoveZ ȣ�� ����"));}

		SetTimer(1, 100, NULL);
	}
	else
	{
		Total_Msg(_T("����� ������� �ʾҽ��ϴ�."));
	}
}


void CLLC4_AF_ModuleDlg::OnBnClickedZDown()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	BOOL	IsConnect = ATF_isSerialConnection();	// ��� ���� ���� Check

	if(IsConnect == TRUE)	// ����� ����� ���¸�
	{
		// AF�� On ���¶�� Z���� �������� �ʴ´�.
		short	atf_Status= 0;
		ATF_ReadStatus(&atf_Status);
		if((atf_Status & MsZTracking) != 0) {	//AF�� On�̸�
			Total_Msg(_T("AF�� On�̸� Z���� ������ �� �����ϴ�."));
			return;
		}

		CString cTempString;
		double	ZMove_um;
		long	Zmove_Parameter;

		m_ZMove_Num.GetWindowTextW(cTempString);
		ZMove_um = _tstof(cTempString);

		// �ѹ��� 500um ���Ϸ� �����̴°� ��õ�մϴ�.
		if		(ZMove_um < 0)		{ ZMove_um = 0;		m_ZMove_Num.SetWindowTextW(_T("0")); }
		else if	(ZMove_um > 500)	{ ZMove_um = 500;	m_ZMove_Num.SetWindowTextW(_T("500")); }

		Zmove_Parameter = (long)((ZMove_um*m_FullStep*m_MicroStep)/1000);	//m_FullStep:FullStep, m_MicroStep:MicroStep

		m_ErrFlag = ATF_MoveZ(-Zmove_Parameter);	// Z�� �̵�
		if(m_ErrFlag != ErrOK) {Total_Msg(_T("ATF_MoveZ ȣ�� ����"));}

		SetTimer(1, 100, NULL);
	}
	else
	{
		Total_Msg(_T("����� ������� �ʾҽ��ϴ�."));
	}
}


void CLLC4_AF_ModuleDlg::OnBnClickedZClear()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	BOOL	IsConnect = ATF_isSerialConnection();	// ��� ���� ���� Check

	if(IsConnect == TRUE)	// ����� ����� ���¸�
	{
		m_ErrFlag = ATF_WriteAbsZPos(0);	// Z�� Position���� 0���� Clear
		if(m_ErrFlag != ErrOK) {Total_Msg(_T("ATF_WriteAbsZPos ȣ�� ����"));}

		SetTimer(1, 100, NULL);
	}
	else
	{
		Total_Msg(_T("����� ������� �ʾҽ��ϴ�."));
	}
}


void CLLC4_AF_ModuleDlg::OnBnClickedZHome()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	BOOL	IsConnect = ATF_isSerialConnection();	// ��� ���� ���� Check

	if(IsConnect == TRUE)	// ����� ����� ���¸�
	{
		// AF�� On ���¶�� Z���� �������� �ʴ´�.
		short	atf_Status= 0;
		ATF_ReadStatus(&atf_Status);
		if((atf_Status & MsZTracking) != 0) {	//AF�� On�̸�
			Total_Msg(_T("AF�� On�̸� Z���� ������ �� �����ϴ�."));
			return;
		}

		// Z�� Home ������ ���� (Parameter:NULL�� Conole���� Setting�� ���� ����Ѵٴ� �ǹ�)
		m_ErrFlag = ATF_RunHomingZ(NULL);	
		if(m_ErrFlag != ErrOK) {Total_Msg(_T("ATF_RunHomingZ ȣ�� ����"));}

		SetTimer(1, 100, NULL);
	}
	else
	{
		Total_Msg(_T("����� ������� �ʾҽ��ϴ�."));
	}
}


void CLLC4_AF_ModuleDlg::OnBnClickedMake0()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	BOOL	IsConnect = ATF_isSerialConnection();	// ��� ���� ���� Check

	if(IsConnect == TRUE)	// ����� ����� ���¸�
	{
		m_ErrFlag = ATF_Make0();
		if(m_ErrFlag != ErrOK) {Total_Msg(_T("ATF_Make0 ȣ�� ����")); return; }
	}
	else
	{
		Total_Msg(_T("����� ������� �ʾҽ��ϴ�."));
	}
}


void CLLC4_AF_ModuleDlg::OnBnClickedLedSetPwm()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	BOOL	IsConnect = ATF_isSerialConnection();	// ��� ���� ���� Check

	if(IsConnect == TRUE)	// ����� ����� ���¸�
	{
		CString			cTempString;
		unsigned short	nLedPwm;

		m_LED_PwmNum.GetWindowTextW(cTempString);
		nLedPwm = (unsigned short)_tstol(cTempString);

		if((nLedPwm < 0) || (nLedPwm > 100))
		{
			Total_Msg(_T("LED Pwm�� 0 ~ 100 ������ ���̾�� �մϴ�."));
			return;
		}

		m_ErrFlag = ATF_WriteLedPwm(0, nLedPwm);	// 0�� ä���� �����մϴ�.
		if(m_ErrFlag != ErrOK) {Total_Msg(_T("ATF_WriteLedPwm ȣ�� ����"));}

		SetTimer(1, 100, NULL);
	}
	else
	{
		Total_Msg(_T("����� ������� �ʾҽ��ϴ�."));
	}
}


void CLLC4_AF_ModuleDlg::OnBnClickedLedSetCurrent()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	BOOL	IsConnect = ATF_isSerialConnection();	// ��� ���� ���� Check

	if(IsConnect == TRUE)	// ����� ����� ���¸�
	{
		CString			cTempString;
		unsigned short	nLedCurrent;

		m_LED_CurrentNum.GetWindowTextW(cTempString);
		nLedCurrent = (unsigned short)_tstol(cTempString);

		if((nLedCurrent < 50) || (nLedCurrent > 800))
		{
			Total_Msg(_T("LED Current�� 50 ~ 800 ������ ���̾�� �մϴ�."));
			return;
		}

		// �ݵ�� 10���� ���� ���� Parameter�� �־���մϴ�.
		nLedCurrent = nLedCurrent / 10;

		m_ErrFlag = ATF_WriteLedCurrent(0, nLedCurrent); // 0�� ä���� �����մϴ�.
		if(m_ErrFlag != ErrOK) {Total_Msg(_T("ATF_WriteLedCurrent ȣ�� ����"));}

		SetTimer(1, 100, NULL);
	}
	else
	{
		Total_Msg(_T("����� ������� �ʾҽ��ϴ�."));
	}
}

void CLLC4_AF_ModuleDlg::OnBnClickedLlcMotorOn()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	BOOL	IsConnect = ATF_isSerialConnection();	// ��� ���� ���� Check
	int		Err = 0;
	CString	cTempString;

	if(IsConnect == TRUE && g_LLC.LLC_IsConnected() == true)	// ����� ����� ���¸�
	{
		// LLC �̵��ϱ� ���� AF�� Off(LLC�� �����̴� ��� ���� �������� AF�� Off�ؾ� �մϴ�.)
		short	atf_Status= 0;
		ATF_ReadStatus(&atf_Status);
		if((atf_Status & MsZTracking) != 0) {	//AF�� On�̸�
			Total_Msg(_T("AF�� On�̸� LLC�� Motor On�� �� �����ϴ�."));
			return;
		}

		// LLC Motor Enable ȣ��
		Err = g_LLC.LLC_MotorEnable();

		if(Err == 0)		cTempString.Format(_T("LLC_MotorEnable Success"));
		else				cTempString.Format(_T("LLC_MotorEnable Fail"));

		SetTimer(2, 100, NULL);

		Total_Msg(cTempString);
	}
	else
	{
		Total_Msg(_T("����� ������� �ʾҽ��ϴ�."));
	}
}


void CLLC4_AF_ModuleDlg::OnBnClickedLlcMotorOff()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	BOOL	IsConnect = ATF_isSerialConnection();				// ��� ���� ���� Check
	int		Err = 0;
	CString	cTempString;

	if(IsConnect == TRUE && g_LLC.LLC_IsConnected() == true)	// ����� ����� ���¸�
	{
		// LLC �̵��ϱ� ���� AF�� Off(LLC�� �����̴� ��� ���� �������� AF�� Off�ؾ� �մϴ�.)
		short	atf_Status= 0;
		ATF_ReadStatus(&atf_Status);
		if((atf_Status & MsZTracking) != 0) {	//AF�� On�̸�
			Total_Msg(_T("AF�� On�̸� LLC�� Motor Off�� �� �����ϴ�."));
			return;
		}

		// LLC Motor Disable ȣ��
		Err = g_LLC.LLC_MotorDisable();

		if(Err == 0)		{ cTempString.Format(_T("LLC_MotorDisable Success"));	m_LLC_ObjectiveNum = -1; } // �Լ�ȣ�⿡ �����ϸ� LLC ��ġ ������ ������Ʈ�մϴ�.
		else				cTempString.Format(_T("LLC_MotorDisable Fail"));

		SetTimer(2, 100, NULL);

		Total_Msg(cTempString);
	}
	else
	{
		Total_Msg(_T("����� ������� �ʾҽ��ϴ�."));
	}
}


void CLLC4_AF_ModuleDlg::OnBnClickedLlcHome()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	BOOL	IsConnect = ATF_isSerialConnection();	// ��� ���� ���� Check
	int		Err = 0;
	CString	cTempString;

	if(IsConnect == TRUE && g_LLC.LLC_IsConnected() == true)	// ����� ����� ���¸�
	{
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// LLC Home�� �ϱ� ���� AF�� Off(LLC�� �����̴� ��� ���� �������� AF�� Off�ؾ� �մϴ�.)
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		short	atf_Status= 0;
		ATF_ReadStatus(&atf_Status);
		if((atf_Status & MsZTracking) != 0) {	//AF�� On�̸�
			Total_Msg(_T("AF�� On�̸� LLC�� Homing�� �� �����ϴ�."));
			return;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// LLC Home ȣ��
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		g_LLC.LLC_LlcPeriodCheck();
		if(g_LLC.LLC_IsLLCMove() == true)	return;
		Err = g_LLC.LLC_MotorHome();

		if(Err == 0)		{ cTempString.Format(_T("LLC_MotorHome Success"));	m_LLC_ObjectiveNum = -1; } // �Լ�ȣ�⿡ �����ϸ� LLC ��ġ ������ ������Ʈ�մϴ�.
		else				cTempString.Format(_T("LLC_MotorHome Fail"));

		SetTimer(2, 100, NULL);

		Total_Msg(cTempString);
	}
	else
	{
		Total_Msg(_T("����� ������� �ʾҽ��ϴ�."));
	}
}


void CLLC4_AF_ModuleDlg::OnBnClickedLlc1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	BOOL	IsConnect = ATF_isSerialConnection();	// ��� ���� ���� Check
	int		Err = 0;
	CString	cTempString;

	if(IsConnect == TRUE && g_LLC.LLC_IsConnected() == true)	// ����� ����� ���¸�
	{
		// LLC �̵��ϱ� ���� �׸��� Lens Setting�� �ٲٱ� ���� AF�� Off(LLC�� �����̴� ��� ���� �������� AF�� Off�ؾ� �մϴ�.)
		short	atf_Status= 0;
		ATF_ReadStatus(&atf_Status);
		if((atf_Status & MsZTracking) != 0) {	//AF�� On�̸�
			Total_Msg(_T("AF�� On�̸� Lens Setting ����� LLC�� �̵��� �� �����ϴ�."));
			return;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// LLC Move ȣ��(Parameter 0:LLC ù° ����, LLC�� �����̱� ���� �ݵ�� AF�� Off�ؾ� �մϴ�.)
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		g_LLC.LLC_LlcPeriodCheck();
		if(g_LLC.LLC_IsLLCMove() == true)	{ Total_Msg(_T("���� LLC�� �����̴� ���Դϴ�. �ٽ� �õ��� �ּ���"));		return; }
		Err = g_LLC.LLC_MoveToObjective(0);

		if(Err == 0)		{ cTempString.Format(_T("LLC_MoveToObjective Success"));	m_LLC_ObjectiveNum = 0; }
		else				cTempString.Format(_T("LLC_MoveToObjective Fail"));

		SetTimer(2, 100, NULL);

		Total_Msg(cTempString);

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// LLC Move�� ȣ���� �Ŀ� ������ LLC�� �´� Lens Setting���� �ٲپ� �ݴϴ�.
		// Lens Setting�� �ٲٴ� �Լ� ȣ�� ���� �ݵ�� AF�� Off�ؾ� �մϴ�. 
		// (Parameter 0: ù° Lens Setting)
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		m_ErrFlag = ATF_WriteObjNum(0);
		if(m_ErrFlag != ErrOK) {Total_Msg(_T("ATF_WriteObjNum ȣ�� ����")); return;}
	}

	else
	{
		Total_Msg(_T("����� ������� �ʾҽ��ϴ�."));
	}
}


void CLLC4_AF_ModuleDlg::OnBnClickedLlc2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	BOOL	IsConnect = ATF_isSerialConnection();	// ��� ���� ���� Check
	int		Err = 0;
	CString	cTempString;

	if(IsConnect == TRUE && g_LLC.LLC_IsConnected() == true)	// ����� ����� ���¸�
	{
		// LLC �̵��ϱ� ���� �׸��� Lens Setting�� �ٲٱ� ���� AF�� Off(LLC�� �����̴� ��� ���� �������� AF�� Off�ؾ� �մϴ�.)
		short	atf_Status= 0;
		ATF_ReadStatus(&atf_Status);
		if((atf_Status & MsZTracking) != 0) {	//AF�� On�̸�
			Total_Msg(_T("AF�� On�̸� Lens Setting ����� LLC�� �̵��� �� �����ϴ�."));
			return;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// LLC Move ȣ��(Parameter 1:LLC �ι�° ����, LLC�� �����̱� ���� �ݵ�� AF�� Off�ؾ� �մϴ�.)
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		g_LLC.LLC_LlcPeriodCheck();
		if(g_LLC.LLC_IsLLCMove() == true)	{ Total_Msg(_T("���� LLC�� �����̴� ���Դϴ�. �ٽ� �õ��� �ּ���"));		return; }
		Err = g_LLC.LLC_MoveToObjective(1);

		if(Err == 0)		{ cTempString.Format(_T("LLC_MoveToObjective Success"));	m_LLC_ObjectiveNum = 1; }
		else				cTempString.Format(_T("LLC_MoveToObjective Fail"));

		SetTimer(2, 100, NULL);

		Total_Msg(cTempString);

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// LLC Move�� ȣ���� �Ŀ� ������ LLC�� �´� Lens Setting���� �ٲپ� �ݴϴ�.
		// Lens Setting�� �ٲٴ� �Լ� ȣ�� ���� �ݵ�� AF�� Off�ؾ� �մϴ�. 
		// (Parameter 1: �ι�° Lens Setting)
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		m_ErrFlag = ATF_WriteObjNum(1);
		if(m_ErrFlag != ErrOK) {Total_Msg(_T("ATF_WriteObjNum ȣ�� ����")); return;}
	}

	else
	{
		Total_Msg(_T("����� ������� �ʾҽ��ϴ�.")); 
	}
}


void CLLC4_AF_ModuleDlg::OnBnClickedLlc3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	BOOL	IsConnect = ATF_isSerialConnection();	// ��� ���� ���� Check
	int		Err = 0;
	CString	cTempString;

	if(IsConnect == TRUE && g_LLC.LLC_IsConnected() == true)	// ����� ����� ���¸�
	{
		// LLC �̵��ϱ� ���� �׸��� Lens Setting�� �ٲٱ� ���� AF�� Off(LLC�� �����̴� ��� ���� �������� AF�� Off�ؾ� �մϴ�.)
		short	atf_Status= 0;
		ATF_ReadStatus(&atf_Status);
		if((atf_Status & MsZTracking) != 0) {	//AF�� On�̸�
			Total_Msg(_T("AF�� On�̸� Lens Setting ����� LLC�� �̵��� �� �����ϴ�."));
			return;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// LLC Move ȣ��(Parameter 2:LLC ����° ����, LLC�� �����̱� ���� �ݵ�� AF�� Off�ؾ� �մϴ�.)
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		g_LLC.LLC_LlcPeriodCheck();
		if(g_LLC.LLC_IsLLCMove() == true)	{ Total_Msg(_T("���� LLC�� �����̴� ���Դϴ�. �ٽ� �õ��� �ּ���"));		return; }
		Err = g_LLC.LLC_MoveToObjective(2);

		if(Err == 0)		{ cTempString.Format(_T("LLC_MoveToObjective Success"));	m_LLC_ObjectiveNum = 2; }
		else				cTempString.Format(_T("LLC_MoveToObjective Fail"));

		SetTimer(2, 100, NULL);

		Total_Msg(cTempString);

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// LLC Move�� ȣ���� �Ŀ� ������ LLC�� �´� Lens Setting���� �ٲپ� �ݴϴ�.
		// Lens Setting�� �ٲٴ� �Լ� ȣ�� ���� �ݵ�� AF�� Off�ؾ� �մϴ�. 
		// (Parameter 2: ����° Lens Setting)
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		m_ErrFlag = ATF_WriteObjNum(2);
		if(m_ErrFlag != ErrOK) {Total_Msg(_T("ATF_WriteObjNum ȣ�� ����")); return;}
	}

	else
	{
		Total_Msg(_T("����� ������� �ʾҽ��ϴ�."));
	}
}


void CLLC4_AF_ModuleDlg::OnBnClickedLlc4()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	BOOL	IsConnect = ATF_isSerialConnection();	// ��� ���� ���� Check
	int		Err = 0;
	CString	cTempString;

	if(IsConnect == TRUE && g_LLC.LLC_IsConnected() == true)	// ����� ����� ���¸�
	{
		// LLC �̵��ϱ� ���� �׸��� Lens Setting�� �ٲٱ� ���� AF�� Off(LLC�� �����̴� ��� ���� �������� AF�� Off�ؾ� �մϴ�.)
		short	atf_Status= 0;
		ATF_ReadStatus(&atf_Status);
		if((atf_Status & MsZTracking) != 0) {	//AF�� On�̸�
			Total_Msg(_T("AF�� On�̸� Lens Setting ����� LLC�� �̵��� �� �����ϴ�."));
			return;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// LLC Move ȣ��(Parameter 3:LLC �׹�° ����, LLC�� �����̱� ���� �ݵ�� AF�� Off�ؾ� �մϴ�.)
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		g_LLC.LLC_LlcPeriodCheck();
		if(g_LLC.LLC_IsLLCMove() == true)	{ Total_Msg(_T("���� LLC�� �����̴� ���Դϴ�. �ٽ� �õ��� �ּ���"));		return; }
		Err = g_LLC.LLC_MoveToObjective(3);

		if(Err == 0)		{ cTempString.Format(_T("LLC_MoveToObjective Success"));	m_LLC_ObjectiveNum = 3; }
		else				cTempString.Format(_T("LLC_MoveToObjective Fail"));

		SetTimer(2, 100, NULL);

		Total_Msg(cTempString);

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// LLC Move�� ȣ���ϳ� �Ŀ� ������ LLC�� �´� Lens Setting���� �ٲپ� �ݴϴ�.
		// Lens Setting�� �ٲٴ� �Լ� ȣ�� ���� �ݵ�� AF�� Off�ؾ� �մϴ�. 
		// (Parameter 3: �׹�° Lens Setting) => 4��° Lens Setting�� �ȵǾ� �ֱ� ������ ATF_WriteObjNum �Լ� ȣǮ�� ������ ���Դϴ�.
		// ���� ���Ե��� 4��° Lens Setting�� �����ϰ� ���ø� �˴ϴ�.
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		m_ErrFlag = ATF_WriteObjNum(3);
		if(m_ErrFlag != ErrOK) {Total_Msg(_T("ATF_WriteObjNum ȣ�� ����")); return;}
	}

	else
	{
		Total_Msg(_T("����� ������� �ʾҽ��ϴ�."));
	}
}

void CLLC4_AF_ModuleDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if(nIDEvent == 1)
	{
		CString	cTempString;
		int		atf_HW_Status;
		short	atf_Status;

		int		Flag_CW, Flag_CCW;
		short	Flag_Laser, Flag_AF, Flag_InFocus, Flag_InRange;

		// ��� ���� ���θ� ǥ���Ѵ�.
		BOOL	IsConnect = ATF_isSerialConnection();	// ��� ���� ���� Check
		if(IsConnect == TRUE)	cTempString.Format(_T("ON"));
		else					cTempString.Format(_T("OFF"));
		m_Status_Communication.SetWindowTextW(cTempString);
		

		if((ATF_ReadHwStat(&atf_HW_Status)==ErrOK) && (ATF_ReadStatus(&atf_Status) == ErrOK))		// AF�� Status���� �ҷ����µ� �����ϸ�
		{

			Flag_InFocus	= atf_Status & MsInFocus;			// In Focus ���� ����(Flag_InFocus != 0�̸� In Focus ����)
			Flag_InRange	= atf_Status & MsMiv;				// In Range ���� ����(Flag_InRange != 0�̸� In Range ����)
			Flag_Laser		= atf_Status & MsEnableLaser;		// Laser On/Off ���� (Flag_Laser = 0�̸� Laser Off, Flag_Laser != 0�̸� Laser On)
			Flag_AF			= atf_Status & MsZTracking;			// AF On/Off ����(Flag_AF = 0�̸� AF Off, Flag_AF != 0�̸� AF On)
			
			Flag_CW			= atf_HW_Status & HwMotionCWLimit;	// CW Limit ����(Flag_CW = 1�̸� CW Limit)
			Flag_CCW		= atf_HW_Status & HwMotionCCWLimit; // CCW Limit ����(Flag_CCW = 1�̸� CCW Limit)

			// Laser On/Off ���θ� ǥ���Ѵ�.
			if(Flag_Laser == 0)	cTempString.Format(_T("OFF"));
			else				cTempString.Format(_T("ON"));
			m_Status_Laser.SetWindowTextW(cTempString);

			// AF On/Off ���θ� ǥ���Ѵ�.
			if(Flag_AF == 0)	cTempString.Format(_T("OFF"));
			else				cTempString.Format(_T("ON"));
			m_Status_AF.SetWindowTextW(cTempString);

			// In Focus�� InRange ǥ��(Laser�� Off�� �Ѵ� Off)
			// In Focus ���θ� ǥ���Ѵ�.
			if(Flag_InFocus == 0)	cTempString.Format(_T("OFF"));
			else					cTempString.Format(_T("ON"));
			m_Status_Infocus.SetWindowTextW(cTempString);

			// In Range ���θ� ǥ���Ѵ�.
			if(Flag_InRange == 0)	cTempString.Format(_T("OFF"));
			else					cTempString.Format(_T("ON"));
			m_Status_Inrange.SetWindowTextW(cTempString);


			// CW Limit ���θ� ǥ���Ѵ�.
			if(Flag_CW == 0)	cTempString.Format(_T("OFF"));
			else				cTempString.Format(_T("ON"));
			m_Status_CW.SetWindowTextW(cTempString);

			// CCW Limit ���θ� ǥ���Ѵ�.
			if(Flag_CCW == 0)	cTempString.Format(_T("OFF"));
			else				cTempString.Format(_T("ON"));
			m_Status_CCW.SetWindowTextW(cTempString);
		}


		// Z�� Position�� ǥ��
		int		absZ;
		m_ErrFlag	= ATF_ReadAbsZPos(&absZ);
		if(m_ErrFlag == ErrOK)
		{
			// �Լ��� ���� Step������ absZ���� um������ ��ȯ�Ѵ�.
			float	iZPositionUm = (float) ( ((float)absZ*1000.0f) / ((float)m_FullStep * (float)m_MicroStep) );
			cTempString.Format(_T("%.2f"), iZPositionUm);

			m_ZPosition.SetWindowTextW(cTempString);
		}

		unsigned short	nLedCurrent = 0, nLedPWM = 0;

		// ���� LED Current ǥ��
		m_ErrFlag = ATF_ReadLedCurrent(0, &nLedCurrent);
		if(m_ErrFlag == ErrOK)
		{
			cTempString.Format(_T("%d"), nLedCurrent*10);	//LED Current�� ���� ���� 10�� ���־�� �Ѵ�.
			m_Status_LEDCurrent.SetWindowTextW(cTempString);
		}

		// ���� LED Current ǥ��
		m_ErrFlag = ATF_ReadLedPwm(0, &nLedPWM);
		if(m_ErrFlag == ErrOK)
		{
			cTempString.Format(_T("%d"), nLedPWM);	
			m_Status_LEDPwm.SetWindowTextW(cTempString);
		}

		// ���� Lens Setting ��ȣ ǥ��
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

		// LLC ��� ���� ���� ǥ��
		bool	bIsLLCConnecte = g_LLC.LLC_IsConnected();
		if(bIsLLCConnecte == true)	cTempString.Format(_T("ON"));
		else						cTempString.Format(_T("OFF"));
		m_Status_LLC_Communication.SetWindowTextW(cTempString);


		// ���� LLC Home ���� Status ǥ��
		nStatus = g_LLC.LLC_Get_HomeStatus();
		if(nStatus == -1)		cTempString.Format(_T("Homing ����"));
		else if	(nStatus == 0)	cTempString.Format(_T("Homing ��"));
		else if (nStatus == 1)	cTempString.Format(_T("Homing �Ϸ�"));
		m_Home_Status.SetWindowTextW(cTempString);

		// ���� LLC ��ġ ��ȣ ǥ��
		nStatus = g_LLC.LLC_Get_CurrentObjective();
		cTempString.Format(_T("Current Obj Num: %d"), nStatus);

		m_Objective_Position.SetWindowTextW(cTempString);
		m_Status_LLCPosition.SetWindowTextW(cTempString);

		// ���� LLC Motor On/Off ���� ǥ��
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
	BOOL	IsConnect = ATF_isSerialConnection();	// ��� ���� ���� Check
	int		Err = 0;
	int		nReturn = -1;
	CString	cTempString;

	if (IsConnect == TRUE && g_LLC.LLC_IsConnected() == true)	// ����� ����� ���¸�
	{
		nReturn = g_LLC.LLC_Get_CurrentObjective();
	}
	else
	{
		Total_Msg(_T("����� ������� �ʾҽ��ϴ�."));
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	OnBnClickedDisconnect();
	CDialogEx::OnClose();
}


void CLLC4_AF_ModuleDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//CDialogEx::OnOK();
}


void CLLC4_AF_ModuleDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnBnClickedDisconnect();
	CDialogEx::OnCancel();
}


//////////////////////////////////////////////////////////////////////////////////////////



void CLLC4_AF_ModuleDlg::OnBnClickedConnectLlc()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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

	// �̹� ����� ����Ǿ� �ִ��� üũ
	m_ErrFlag = ATF_PingAck();
	if (m_ErrFlag == ErrOK) { Total_Msg(_T("�̹� ����� ����Ǿ����ϴ�.")); return; }


	PortNum = COM_PORT_LLC_ATF;

	sprintf(Com_Name, "\\\\.\\COM%d", PortNum);

	//	��� ����
	m_ErrFlag = ATF_OpenConnection(Com_Name, 9600);

	// ErrOK = 0, ��� ATF �Լ��� return���� 0�� �� �����۵�.
	if (m_ErrFlag != ErrOK)
	{
		Total_Msg(_T("ATF_OpenConnection ȣ�� ����"));
		return;
	}

	// ��� ���� �� �⺻���� �ʱ�ȭ �۾�(Laser�� AF OFF)
	ATF_AfStop();
	Sleep(100);
	m_ErrFlag = ATF_DisableLaser();
	if (m_ErrFlag != ErrOK) { Total_Msg(_T("ATF_DisableLaser ȣ�� ����")); return; }
	Sleep(100);

	// FullStep�� MicroStep���� ����(Z�� ��� ����)
	m_ErrFlag = ATF_ReadStepPerMmConversion(&m_FullStep);
	if (m_ErrFlag != ErrOK) { Total_Msg(_T("ATF_ReadStepPerMmConversion ȣ�� ����")); return; }
	m_ErrFlag = ATF_ReadMicrostep(&m_MicroStep);
	if (m_ErrFlag != ErrOK) { Total_Msg(_T("ATF_ReadMicrostep ȣ�� ����")); return; }

	// LLC�� ���� ��ġ�� �˼� �������� �մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	BOOL	IsConnect = ATF_isSerialConnection();	// ��� ���� ���� Check

	if (IsConnect == TRUE)	// ����� ����� ���¸�
	{
		unsigned short	nLedPwm;

		nLedPwm = (unsigned short)Pwm;

		if ((nLedPwm < 0) || (nLedPwm > 100))
		{
			Total_Msg(_T("LED Pwm�� 0 ~ 100 ������ ���̾�� �մϴ�."));
			return;
		}

		m_ErrFlag = ATF_WriteLedPwm(0, nLedPwm);	// 0�� ä���� �����մϴ�.
		if (m_ErrFlag != ErrOK) { Total_Msg(_T("ATF_WriteLedPwm ȣ�� ����")); }


		unsigned short	nLedCurrent;

		nLedCurrent = (unsigned short)Current;

		if ((nLedCurrent < 50) || (nLedCurrent > 800))
		{
			Total_Msg(_T("LED Current�� 50 ~ 800 ������ ���̾�� �մϴ�."));
			return;
		}

		// �ݵ�� 10���� ���� ���� Parameter�� �־���մϴ�.
		nLedCurrent = nLedCurrent / 10;

		m_ErrFlag = ATF_WriteLedCurrent(0, nLedCurrent); // 0�� ä���� �����մϴ�.
		if (m_ErrFlag != ErrOK) { Total_Msg(_T("ATF_WriteLedCurrent ȣ�� ����")); }
	}
	else
	{
		Total_Msg(_T("����� ������� �ʾҽ��ϴ�."));
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

	Flag_InFocus = atf_Status & MsInFocus;			// In Focus ���� ����(Flag_InFocus != 0�̸� In Focus ����)
	Flag_InRange = atf_Status & MsMiv;				// In Range ���� ����(Flag_InRange != 0�̸� In Range ����)
	Flag_Laser = atf_Status & MsEnableLaser;		// Laser On/Off ���� (Flag_Laser = 0�̸� Laser Off, Flag_Laser != 0�̸� Laser On)
	Flag_AF = atf_Status & MsZTracking;			// AF On/Off ����(Flag_AF = 0�̸� AF Off, Flag_AF != 0�̸� AF On)

	return (Flag_Laser != 0);
}

BOOL CLLC4_AF_ModuleDlg::GetLaserInFocusStatus()
{
	short	atf_Status;
	short	Flag_Laser, Flag_AF, Flag_InFocus, Flag_InRange;

	ATF_ReadStatus(&atf_Status);

	Flag_InFocus = atf_Status & MsInFocus;			// In Focus ���� ����(Flag_InFocus != 0�̸� In Focus ����)
	Flag_InRange = atf_Status & MsMiv;				// In Range ���� ����(Flag_InRange != 0�̸� In Range ����)
	Flag_Laser = atf_Status & MsEnableLaser;		// Laser On/Off ���� (Flag_Laser = 0�̸� Laser Off, Flag_Laser != 0�̸� Laser On)
	Flag_AF = atf_Status & MsZTracking;			// AF On/Off ����(Flag_AF = 0�̸� AF Off, Flag_AF != 0�̸� AF On)

	return (Flag_InFocus != 0);
}

BOOL CLLC4_AF_ModuleDlg::GetLaserAFStatus()
{
	short	atf_Status;
	short	Flag_Laser, Flag_AF, Flag_InFocus, Flag_InRange;

	ATF_ReadStatus(&atf_Status);

	Flag_InFocus = atf_Status & MsInFocus;			// In Focus ���� ����(Flag_InFocus != 0�̸� In Focus ����)
	Flag_InRange = atf_Status & MsMiv;				// In Range ���� ����(Flag_InRange != 0�̸� In Range ����)
	Flag_Laser = atf_Status & MsEnableLaser;		// Laser On/Off ���� (Flag_Laser = 0�̸� Laser Off, Flag_Laser != 0�̸� Laser On)
	Flag_AF = atf_Status & MsZTracking;			// AF On/Off ����(Flag_AF = 0�̸� AF Off, Flag_AF != 0�̸� AF On)

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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	BOOL	IsConnect = ATF_isSerialConnection();	// ��� ���� ���� Check

	if (IsConnect == TRUE)	// ����� ����� ���¸�
	{
		// AF�� On ���¶�� Z���� �������� �ʴ´�.
		int		atf_HW_Status;
		short	atf_Status;
		if ((ATF_ReadHwStat(&atf_HW_Status) == ErrOK) && (ATF_ReadStatus(&atf_Status) == ErrOK))		// AF�� Status���� �ҷ����µ� �����ϸ�
		{
			if ((atf_Status & MsZTracking) != 0)
				return FALSE; //AF�� On�̸�

			if ((atf_HW_Status & HwMotionZ) != 0) //0 : Stop Status
				return FALSE; //Busy

			// �ѹ��� 500um ���Ϸ� �����̴°� ��õ�մϴ�.
			if (dDist < -500)
				dDist = -500;
			else if (dDist > 500)
				dDist = 500;

			dDist *= 10.0;

			SharedInfo::bMachineStopFlag = FALSE;
			m_ErrFlag = ATF_MoveZ(dDist);	// Z�� �̵� //dDist 100�̸� 10um
			if (m_ErrFlag != ErrOK)
			{
				Total_Msg(_T("ATF_MoveZ ȣ�� ����"));
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
		Total_Msg(_T("����� ������� �ʾҽ��ϴ�."));
		return FALSE;
	}
}
int CLLC4_AF_ModuleDlg::Is_ZoomCamZ_Busy()
{
	int		atf_HW_Status;
	short	atf_Status;
	int nHwMotionFlag = 1;
	BOOL	IsConnect = ATF_isSerialConnection();	// ��� ���� ���� Check
	if (IsConnect == TRUE)	// ����� ����� ���¸�
	{
		if (ATF_ReadHwStat(&atf_HW_Status) == ErrOK)		// AF�� Status���� �ҷ����µ� �����ϸ�
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
