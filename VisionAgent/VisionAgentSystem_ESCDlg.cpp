// VisionAgentSystem_CoordinateDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentDlg.h"
#include "VisionAgentSystem_ESCDlg.h"
#include "afxdialogex.h"


// CVisionAgentSystem_ESCDlg 대화 상자

IMPLEMENT_DYNAMIC(CVisionAgentSystem_ESCDlg, CDialogEx)

CVisionAgentSystem_ESCDlg::CVisionAgentSystem_ESCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SYSTEM_ESC_DIALOG, pParent)
{
	Create(IDD_SYSTEM_ESC_DIALOG, pParent);
}

CVisionAgentSystem_ESCDlg::~CVisionAgentSystem_ESCDlg()
{
}

void CVisionAgentSystem_ESCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVisionAgentSystem_ESCDlg, CDialogEx)
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	
	ON_BN_CLICKED(IDC_BUTTON_VOLT_SETTING, &CVisionAgentSystem_ESCDlg::OnBnClickedButtonVoltSetting)
	ON_BN_CLICKED(IDC_BUTTON_SYSTEM_REMOTE, &CVisionAgentSystem_ESCDlg::OnBnClickedButtonSystemRemote)
	ON_BN_CLICKED(IDC_BUTTON_OUTPUT_ON, &CVisionAgentSystem_ESCDlg::OnBnClickedButtonOutputOn)
	ON_BN_CLICKED(IDC_BUTTON_OUTPUT_OFF, &CVisionAgentSystem_ESCDlg::OnBnClickedButtonOutputOff)
	ON_BN_CLICKED(IDC_BUTTON_OUTPUT_CHECK, &CVisionAgentSystem_ESCDlg::OnBnClickedButtonOutputCheck)
	ON_BN_CLICKED(IDC_BUTTON_VOLT_CHECK, &CVisionAgentSystem_ESCDlg::OnBnClickedButtonVoltCheck)
	ON_BN_CLICKED(IDC_BUTTON_TOGGLE_ON, &CVisionAgentSystem_ESCDlg::OnBnClickedButtonToggleOn)
	ON_BN_CLICKED(IDC_BUTTON_TOGGLE_OFF, &CVisionAgentSystem_ESCDlg::OnBnClickedButtonToggleOff)
	ON_BN_CLICKED(IDC_BUTTON_TOGGLE_CHECK, &CVisionAgentSystem_ESCDlg::OnBnClickedButtonToggleCheck)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_TOGGLE_CHECK2, &CVisionAgentSystem_ESCDlg::OnBnClickedButtonToggleCheck2)
	ON_BN_CLICKED(IDC_BUTTON_TOGGLE_CHECK3, &CVisionAgentSystem_ESCDlg::OnBnClickedButtonToggleCheck3)
	ON_BN_CLICKED(IDC_BUTTON_TOGGLE_CHECK4, &CVisionAgentSystem_ESCDlg::OnBnClickedButtonToggleCheck4)
	ON_BN_CLICKED(IDC_BUTTON_TOGGLE_CHECK5, &CVisionAgentSystem_ESCDlg::OnBnClickedButtonToggleCheck5)
	ON_BN_CLICKED(IDC_BUTTON_TOGGLE_CHECK6, &CVisionAgentSystem_ESCDlg::OnBnClickedButtonToggleCheck6)
	ON_BN_CLICKED(IDC_BUTTON_TOGGLE_CHECK7, &CVisionAgentSystem_ESCDlg::OnBnClickedButtonToggleCheck7)
	ON_BN_CLICKED(IDC_BUTTON_TOGGLE_CHECK8, &CVisionAgentSystem_ESCDlg::OnBnClickedButtonToggleCheck8)
	ON_BN_CLICKED(IDC_BUTTON_TOGGLE_CHECK9, &CVisionAgentSystem_ESCDlg::OnBnClickedButtonToggleCheck9)
END_MESSAGE_MAP()


// CVisionAgentSystem_ESCDlg 메시지 처리기

BOOL CVisionAgentSystem_ESCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitCtrl();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CVisionAgentSystem_ESCDlg::OnDestroy()
{
	KillTimer(1);
	CDialogEx::OnDestroy();
}

BOOL CVisionAgentSystem_ESCDlg::InitCtrl()
{
	m_checkAutoDeleteDirPathUse[0].SubclassDlgItem(IDC_CHECK_SYSTEM_OTHER_AUTO_DELETE_DIR_PATH_USE_1, this);
	m_checkAutoDeleteDirPathUse[1].SubclassDlgItem(IDC_CHECK_SYSTEM_OTHER_AUTO_DELETE_DIR_PATH_USE_2, this);
	m_checkAutoDeleteDirPathUse[2].SubclassDlgItem(IDC_CHECK_SYSTEM_OTHER_AUTO_DELETE_DIR_PATH_USE_3, this);

	m_editFileStoreDay[0].SubclassDlgItem(IDC_EDIT_SYSTEM_OTHER_FILE_STORE_DAYS_1, this);
	m_editFileStoreDay[1].SubclassDlgItem(IDC_EDIT_SYSTEM_OTHER_FILE_STORE_DAYS_2, this);
	m_editFileStoreDay[2].SubclassDlgItem(IDC_EDIT_SYSTEM_OTHER_FILE_STORE_DAYS_3, this);

	m_editHighTemperature.SubclassDlgItem(IDC_EDIT_HIGH_TEMPERATURE, this);
	m_editLowTemperature.SubclassDlgItem(IDC_EDIT_LOW_TEMPERATURE, this);	

	m_chkUseTemperatureCheck.SubclassDlgItem(IDC_CHECK_TEMPERATURE_CHECK_USAGE, this);
	m_chkUseDoorOpenCheck.SubclassDlgItem(IDC_CHECK_DOOR_OPEN_CHECK_USAGE, this);	
	m_chkUseAuto3DConnection.SubclassDlgItem(IDC_CHECK_AUTO_3D_CONNECTION, this);

	m_EditVolt1.SubclassDlgItem(IDC_EDIT_VOLT_SETTING_1, this);
	m_EditVolt2.SubclassDlgItem(IDC_EDIT_VOLT_SETTING_2, this);
	m_EditReceiveData.SubclassDlgItem(IDC_EDIT_RECEIVE_DATA, this);
	return TRUE;
}

BOOL CVisionAgentSystem_ESCDlg::InitPara()
{	
	CString Str;
	int i = 0;

	//KJT 20210329
	for (i = 0; i < MAX_AUTO_DELETE_DIR_PATH; i++)
	{
		m_checkAutoDeleteDirPathUse[i].SetCheck(CSystemData::m_Other.Info.m_bAutoDeleteDirPathUse[i]);
		Str.Format(_T("%d"), CSystemData::m_Other.Info.m_nFileStoreDays[i]);
		m_editFileStoreDay[i].SetWindowText(Str);
	}
		
	Str.Format(_T("%.2f"), CSystemData::m_Other.Info.m_dHighTemperature);
	m_editHighTemperature.SetWindowText(Str);

	Str.Format(_T("%.2f"), CSystemData::m_Other.Info.m_dLowTemperature);
	m_editLowTemperature.SetWindowText(Str);

	m_chkUseTemperatureCheck.SetCheck(CSystemData::m_Other.Info.m_nUseTemperatureCheck);
	m_chkUseDoorOpenCheck.SetCheck(CSystemData::m_Other.Info.m_nUseDoorOpenCheck);
	m_chkUseAuto3DConnection.SetCheck(CSystemData::m_Other.Info.m_nUseAuto3DConnection);

	//Str.Format(_T("+%d"), CSystemData::m_Other.Info.m_nElectricChuckVolt);
	Str.Format(_T("%d"), CSystemData::m_Other.Info.m_nElectricChuckVolt);
	m_EditVolt1.SetWindowTextW(Str);

	//Str.Format(_T("-%d"), CSystemData::m_Other.Info.m_nElectricChuckVolt);
	//m_EditVolt2.SetWindowTextW(Str);

	return TRUE;
}

BOOL CVisionAgentSystem_ESCDlg::SavePara()
{
	CheckChangeData();

	BOOL bRtn = CSystemData::m_Other.Save();
	if (bRtn == TRUE)
		AfxMessageBox(_T("Save Ok"));
	else
		AfxMessageBox(_T("Save Fail !!"));

	return TRUE;
}

BOOL CVisionAgentSystem_ESCDlg::CheckChangeData()
{
	CString Str = _T("");
	int i = 0;
	int nStoreDay = 1;

	//KJT 20210329
	for (i = 0; i < MAX_AUTO_DELETE_DIR_PATH; i++)
	{
		CSystemData::m_Other.Info.m_bAutoDeleteDirPathUse[i] = m_checkAutoDeleteDirPathUse[i].GetCheck();
		
		m_editFileStoreDay[i].GetWindowText(Str);
		if (_ttoi(Str) < 0)
			nStoreDay = 1;
		else if (_ttoi(Str) >= 365)
			nStoreDay = 365;
		else
			nStoreDay = _ttoi(Str);

		CSystemData::m_Other.Info.m_nFileStoreDays[i] = nStoreDay;
	}
	
	m_editHighTemperature.GetWindowTextW(Str);
	CSystemData::m_Other.Info.m_dHighTemperature = _ttof(Str);
	
	m_editLowTemperature.GetWindowTextW(Str);
	CSystemData::m_Other.Info.m_dLowTemperature = _ttof(Str);
	
	CSystemData::m_Other.Info.m_nUseTemperatureCheck = m_chkUseTemperatureCheck.GetCheck();
	CSystemData::m_Other.Info.m_nUseDoorOpenCheck = m_chkUseDoorOpenCheck.GetCheck();
	CSystemData::m_Other.Info.m_nUseAuto3DConnection = m_chkUseAuto3DConnection.GetCheck();

	m_EditVolt1.GetWindowTextW(Str);
	CSystemData::m_Other.Info.m_nElectricChuckVolt = _ttoi(Str);

	return TRUE;
}

void CVisionAgentSystem_ESCDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow == TRUE)
	{
		SetTimer(1, 500, NULL);
		InitPara();
	}
	else if (bShow == FALSE)
	{
		KillTimer(1);
	}
}


void CVisionAgentSystem_ESCDlg::OnBnClickedButtonVoltSetting()
{
	// TODO: Add your control notification handler code here
	CString str, strVolt,strVolt1,strVolt2;

	//m_EditVolt1.GetWindowText(strVolt);
	////m_EditVolt2.GetWindowText(strVolt2);

	//str.Format(_T("VOLT +%s, -%s"), strVolt, strVolt);
	//g_CommESC.Esc_Send_Msg(str);
	return;
}

void CVisionAgentSystem_ESCDlg::OnBnClickedButtonVoltCheck()
{
	//g_CommESC.Esc_Send_Msg(_T("VOLT? (@1,2)"));
	return;
}


void CVisionAgentSystem_ESCDlg::OnBnClickedButtonSystemRemote()
{
	//g_CommESC.Esc_Send_Msg(_T("SYSTem:REMote"));
	return;
}


void CVisionAgentSystem_ESCDlg::OnBnClickedButtonOutputOn()
{
	//g_CommESC.Esc_Send_Msg(_T("OUTPut 1"));
	return;
}


void CVisionAgentSystem_ESCDlg::OnBnClickedButtonOutputOff()
{
	//g_CommESC.Esc_Send_Msg(_T("OUTPut 0"));
	return;
}


void CVisionAgentSystem_ESCDlg::OnBnClickedButtonOutputCheck()
{
	//g_CommESC.Esc_Send_Msg(_T("OUTPut?"));
	return;
}

void CVisionAgentSystem_ESCDlg::OnBnClickedButtonToggleOn()
{
	//g_CommESC.Esc_Send_Msg(_T("TOGGle 1"));
	return;
}


void CVisionAgentSystem_ESCDlg::OnBnClickedButtonToggleOff()
{
	//g_CommESC.Esc_Send_Msg(_T("TOGGle 0"));
	return;
}


void CVisionAgentSystem_ESCDlg::OnBnClickedButtonToggleCheck()
{
	//g_CommESC.Esc_Send_Msg(_T("TOGGle?"));
	return;
}


void CVisionAgentSystem_ESCDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	CVisionAgentDlg *pDlg = (CVisionAgentDlg *)theApp.GetMainWnd();
	CString str;
	str = pDlg->m_pch;
	m_EditReceiveData.SetWindowText(str);
	CDialogEx::OnTimer(nIDEvent);
}


void CVisionAgentSystem_ESCDlg::OnBnClickedButtonToggleCheck2()
{
	//g_CommAOILaser.AOI_Meas_Print(0);
	return;
}


void CVisionAgentSystem_ESCDlg::OnBnClickedButtonToggleCheck3()
{
	//g_CommAOILaser.AOI_Meas_Print(1);
	return;
}


void CVisionAgentSystem_ESCDlg::OnBnClickedButtonToggleCheck4()
{
	//g_CommAOILaser.AOI_Meas_Print(2);
	return;
}


void CVisionAgentSystem_ESCDlg::OnBnClickedButtonToggleCheck5()
{
	//g_CommAOILaser.AOI_Timing_ON_OFF(0,TRUE);
}


void CVisionAgentSystem_ESCDlg::OnBnClickedButtonToggleCheck6()
{
	//g_CommAOILaser.AOI_Timing_ON_OFF(0, FALSE);
}


void CVisionAgentSystem_ESCDlg::OnBnClickedButtonToggleCheck7()
{
	//g_CommAOILaser.AOI_Auto_Zero_ON_OFF(0, TRUE);
}


void CVisionAgentSystem_ESCDlg::OnBnClickedButtonToggleCheck8()
{
	//g_CommAOILaser.AOI_Auto_Zero_ON_OFF(0, FALSE);
}


void CVisionAgentSystem_ESCDlg::OnBnClickedButtonToggleCheck9()
{
	//g_CommAOILaser.AOI_Reset(0);
}
