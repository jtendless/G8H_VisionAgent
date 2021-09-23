// VisionAgentModelDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentDlg.h"
#include "VisionAgentMachineOriginDlg.h"
#include "afxdialogex.h"

// CVisionAgentMachineOriginDlg 대화 상자

IMPLEMENT_DYNAMIC(CVisionAgentMachineOriginDlg, CDialogEx)

CVisionAgentMachineOriginDlg::CVisionAgentMachineOriginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VISION_AGENT_MACHINE_ORIGIN_DIALOG, pParent)
{
	Create(IDD_VISION_AGENT_MACHINE_ORIGIN_DIALOG, pParent);
}

CVisionAgentMachineOriginDlg::~CVisionAgentMachineOriginDlg()
{
}

void CVisionAgentMachineOriginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVisionAgentMachineOriginDlg, CDialogEx)
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_MACHINE_ORIGIN_INTERLOCK_CHECK, &CVisionAgentMachineOriginDlg::OnBnClickedMachineOriginInterlockCheck)
	ON_BN_CLICKED(IDC_MACHINE_ORIGIN_ALL_STOP_BTN, &CVisionAgentMachineOriginDlg::OnBnClickedMachineOriginAllStopBtn)
	ON_BN_CLICKED(IDC_BUTTON_MACHINE_SERVO_OFF_ALL, &CVisionAgentMachineOriginDlg::OnBnClickedMachineOriginAllServoOffBtn)
	ON_BN_CLICKED(IDC_BUTTON_MACHINE_ORIGIN_ALL, &CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineOriginAll)
	ON_BN_CLICKED(IDC_BUTTON_MACHINE_ORIGIN_GANTRY_Y, &CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineOriginGantryY)
	//ON_BN_CLICKED(IDC_BUTTON_MACHINE_ORIGIN_GANTRY_X, &CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineOriginGantryX)
	//ON_BN_CLICKED(IDC_BUTTON_MACHINE_ORIGIN_CAMERA_Z, &CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineOriginCameraZ)
	//ON_BN_CLICKED(IDC_BUTTON_MACHINE_SERVO_ON_ALL, &CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineServoOnAll)
	//ON_BN_CLICKED(IDC_BUTTON_MACHINE_ORIGIN_GRIPPER_CLAMP, &CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineOriginGripperClamp)
	//ON_BN_CLICKED(IDC_BUTTON_MACHINE_ORIGIN_GRIPPER_STRETCH, &CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineOriginGripperStretch)
	//ON_BN_CLICKED(IDC_BUTTON_MACHINE_ORIGIN_INSPECTION_STAGE, &CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineOriginInspectionStage)
	//ON_BN_CLICKED(IDC_BUTTON_MACHINE_SERVO_ON_GANTRY_Y, &CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineServoOnGantryY)
	//ON_BN_CLICKED(IDC_BUTTON_MACHINE_SERVO_ON_GANTRY_X, &CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineServoOnGantryX)
	//ON_BN_CLICKED(IDC_BUTTON_MACHINE_SERVO_ON_CAMERA_Z, &CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineServoOnCameraZ)
	//ON_BN_CLICKED(IDC_BUTTON_MACHINE_SERVO_ON_LOADING_STAGE, &CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineServoOnLoadingStage)
	//ON_BN_CLICKED(IDC_BUTTON_MACHINE_SERVO_ON_GRIPPER_CLAMP, &CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineServoOnGripperClamp)
	//ON_BN_CLICKED(IDC_BUTTON_MACHINE_SERVO_ON_GRIPPER_STRETCH, &CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineServoOnGripperStretch)
	//ON_BN_CLICKED(IDC_BUTTON_MACHINE_SERVO_ON_GRIPPER_PITCH, &CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineServoOnGripperPitch)
	//ON_BN_CLICKED(IDC_BUTTON_MACHINE_SERVO_ON_GRIPPER_WEDGE_Z, &CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineServoOnGripperWedgeZ)
	//ON_BN_CLICKED(IDC_BUTTON_MACHINE_SERVO_ON_INSPECTION_STAGE, &CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineServoOnInspectionStage)
	//ON_BN_CLICKED(IDC_BUTTON_MACHINE_SERVO_ON_MAGAZINE_LIFT, &CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineServoOnMagazineLift)
	//ON_BN_CLICKED(IDC_BUTTON_MACHINE_SERVO_OFF_GANTRY_Y, &CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineServoOffGantryY)
	//ON_BN_CLICKED(IDC_BUTTON_MACHINE_SERVO_OFF_GANTRY_X, &CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineServoOffGantryX)
	//ON_BN_CLICKED(IDC_BUTTON_MACHINE_SERVO_OFF_CAMERA_Z, &CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineServoOffCameraZ)
	//ON_BN_CLICKED(IDC_BUTTON_MACHINE_SERVO_OFF_LOADING_STAGE, &CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineServoOffLoadingStage)
	//ON_BN_CLICKED(IDC_BUTTON_MACHINE_SERVO_OFF_GRIPPER_CLAMP, &CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineServoOffGripperClamp)
	//ON_BN_CLICKED(IDC_BUTTON_MACHINE_SERVO_OFF_GRIPPER_STRETCH, &CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineServoOffGripperStretch)
	//ON_BN_CLICKED(IDC_BUTTON_MACHINE_SERVO_OFF_GRIPPER_WEDGE_Z, &CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineServoOffGripperWedgeZ)
	//ON_BN_CLICKED(IDC_BUTTON_MACHINE_SERVO_OFF_INSPECTION_STAGE, &CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineServoOffInspectionStage)
	//ON_BN_CLICKED(IDC_BUTTON_MACHINE_SERVO_OFF_INKJET, &CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineServoOffInkjet)
	//ON_BN_CLICKED(IDC_BUTTON_MACHINE_ORIGIN_PAPER, &CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineOriginPaper)
	//ON_BN_CLICKED(IDC_BUTTON_MACHINE_SERVO_ON_PAPER, &CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineServoOnPaper)
	//ON_BN_CLICKED(IDC_BUTTON_MACHINE_SERVO_OFF_PAPER, &CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineServoOffPaper)
END_MESSAGE_MAP()


// CVisionAgentMachineOriginDlg 메시지 처리기
BOOL CVisionAgentMachineOriginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitCtrl();

	return TRUE;
}

void CVisionAgentMachineOriginDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	if (bShow == TRUE) {
		
		InitPara();
		SetTimer(1, 100, NULL);
	}
	else if (bShow == FALSE)
	{
		KillTimer(1);
	}
}


void CVisionAgentMachineOriginDlg::InitCtrl()
{
	m_bDialog_Entry = TRUE;

	m_stcAllOriginLed.SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_ALL_LED, this);
	m_stcAllOriginLed.SetBackgroundColor(LLTGRAY);
	m_stcAllOriginLed.SetTextColor(BLACK);
	m_btnAllOrgin.SubclassDlgItem(IDC_BUTTON_MACHINE_ORIGIN_ALL, this);
	m_btnAllOrgin.SetColor(BLACK, LLTGRAY);
	m_stcAllServoOnOffLed.SubclassDlgItem(IDC_STATIC_MACHINE_SERVO_ON_OFF_ALL_LED, this);
	m_stcAllServoOnOffLed.SetBackgroundColor(LLTGRAY);
	m_stcAllServoOnOffLed.SetTextColor(BLACK);
	m_btnAllServoOn.SubclassDlgItem(IDC_BUTTON_MACHINE_SERVO_ON_ALL, this);
	m_btnAllServoOn.SetColor(BLACK, LLTGRAY);
	m_btnAllServoOff.SubclassDlgItem(IDC_BUTTON_MACHINE_SERVO_OFF_ALL, this);
	m_btnAllServoOff.SetColor(BLACK, LLTGRAY);

#pragma region //Combo Axis
	m_ComboAxis[MACHINE_ORIGIN_WORKSTAGE].SubclassDlgItem(IDC_COMBO_MACHINE_ORIGIN_WORKSTAGE, this);
	m_ComboAxis[MACHINE_ORIGIN_GANTRY_Y].SubclassDlgItem(IDC_COMBO_MACHINE_ORIGIN_GANTRY_Y, this);
	m_ComboAxis[MACHINE_ORIGIN_GANTRY_Z].SubclassDlgItem(IDC_COMBO_MACHINE_ORIGIN_GANTRY_Z, this);
	m_ComboAxis[MACHINE_ORIGIN_FRAME_UPDOWN].SubclassDlgItem(IDC_COMBO_MACHINE_ORIGIN_FRAME_UPDOWN, this);
	m_ComboAxis[MACHINE_ORIGIN_STAGE_UVW].SubclassDlgItem(IDC_COMBO_MACHINE_ORIGIN_STAGE_UVW, this);
	m_ComboAxis[MACHINE_ORIGIN_GLASS_POPUP_Z].SubclassDlgItem(IDC_COMBO_MACHINE_ORIGIN_GLASS_POPUP_Z, this);
	m_ComboAxis[MACHINE_ORIGIN_FRAME_GRIPPER_SSIDE].SubclassDlgItem(IDC_COMBO_MACHINE_ORIGIN_FRAME_GRIPPER_SSIDE, this);
	m_ComboAxis[MACHINE_ORIGIN_FRAME_GRIPPER_LSIDE].SubclassDlgItem(IDC_COMBO_MACHINE_ORIGIN_FRAME_GRIPPER_LSIDE, this);
	m_ComboAxis[MACHINE_ORIGIN_GLASS_RELEASE_SSIDE].SubclassDlgItem(IDC_COMBO_MACHINE_ORIGIN_GLASS_RELEASE_SSIDE, this);
	m_ComboAxis[MACHINE_ORIGIN_GLASS_RELEASE_SMOVE].SubclassDlgItem(IDC_COMBO_MACHINE_ORIGIN_GLASS_RELEASE_SMOVE, this);
	m_ComboAxis[MACHINE_ORIGIN_GLASS_RELEASE_LSIDE].SubclassDlgItem(IDC_COMBO_MACHINE_ORIGIN_GLASS_RELEASE_LSIDE, this);
	m_ComboAxis[MACHINE_ORIGIN_GLASS_RELEASE_LMOVE].SubclassDlgItem(IDC_COMBO_MACHINE_ORIGIN_GLASS_RELEASE_LMOVE, this);
	m_ComboAxis[MACHINE_ORIGIN_FRAME_TRANSFER_MOVE].SubclassDlgItem(IDC_COMBO_MACHINE_ORIGIN_FRAME_TRANSFER_MOVE, this);
	m_ComboAxis[MACHINE_ORIGIN_ROLLER_RELEASE_MOVE].SubclassDlgItem(IDC_COMBO_MACHINE_ORIGIN_ROLLER_RELEASE_MOVE, this);
	m_ComboAxis[MACHINE_ORIGIN_GLASS_RELEASE_LSIDE_R].SubclassDlgItem(IDC_COMBO_MACHINE_ORIGIN_GLASS_RELEASE_LSIDE_R, this);
	m_ComboAxis[MACHINE_ORIGIN_ROLLER_RELEASE].SubclassDlgItem(IDC_COMBO_MACHINE_ORIGIN_ROLLER_RELEASE, this);
	m_ComboAxis[MACHINE_ORIGIN_CLEANNING].SubclassDlgItem(IDC_COMBO_MACHINE_ORIGIN_CLEANNING, this);
	m_ComboAxis[MACHINE_ORIGIN_FRAME_TRANSFER_L].SubclassDlgItem(IDC_COMBO_MACHINE_ORIGIN_FRAME_TRANSFER_L, this);


	m_ComboAxis[MACHINE_ORIGIN_WORKSTAGE].ResetContent();
	m_ComboAxis[MACHINE_ORIGIN_WORKSTAGE].AddString(_T("X"));
	m_ComboAxis[MACHINE_ORIGIN_WORKSTAGE].SetCurSel(0);

	m_ComboAxis[MACHINE_ORIGIN_GANTRY_Y].ResetContent();
	m_ComboAxis[MACHINE_ORIGIN_GANTRY_Y].AddString(_T("Gantry Y1"));
	m_ComboAxis[MACHINE_ORIGIN_GANTRY_Y].AddString(_T("Gantry Y2"));
	m_ComboAxis[MACHINE_ORIGIN_GANTRY_Y].SetCurSel(0);

	m_ComboAxis[MACHINE_ORIGIN_GANTRY_Z].ResetContent();
	m_ComboAxis[MACHINE_ORIGIN_GANTRY_Z].AddString(_T("Gantry Z1"));
	m_ComboAxis[MACHINE_ORIGIN_GANTRY_Z].AddString(_T("Gantry Z2"));
	m_ComboAxis[MACHINE_ORIGIN_GANTRY_Z].SetCurSel(0);

	m_ComboAxis[MACHINE_ORIGIN_FRAME_UPDOWN].ResetContent();
	m_ComboAxis[MACHINE_ORIGIN_FRAME_UPDOWN].AddString(_T("Z1"));
	m_ComboAxis[MACHINE_ORIGIN_FRAME_UPDOWN].AddString(_T("Z2"));
	m_ComboAxis[MACHINE_ORIGIN_FRAME_UPDOWN].AddString(_T("Z3"));
	m_ComboAxis[MACHINE_ORIGIN_FRAME_UPDOWN].AddString(_T("Z4"));
	m_ComboAxis[MACHINE_ORIGIN_FRAME_UPDOWN].SetCurSel(0);

	m_ComboAxis[MACHINE_ORIGIN_STAGE_UVW].ResetContent();
	m_ComboAxis[MACHINE_ORIGIN_STAGE_UVW].AddString(_T("Y1"));
	m_ComboAxis[MACHINE_ORIGIN_STAGE_UVW].AddString(_T("Y2"));
	m_ComboAxis[MACHINE_ORIGIN_STAGE_UVW].AddString(_T("X1"));
	m_ComboAxis[MACHINE_ORIGIN_STAGE_UVW].AddString(_T("X2"));
	m_ComboAxis[MACHINE_ORIGIN_STAGE_UVW].SetCurSel(0);

	m_ComboAxis[MACHINE_ORIGIN_GLASS_POPUP_Z].ResetContent();
	m_ComboAxis[MACHINE_ORIGIN_GLASS_POPUP_Z].AddString(_T("Z"));
	m_ComboAxis[MACHINE_ORIGIN_GLASS_POPUP_Z].SetCurSel(0);


	m_ComboAxis[MACHINE_ORIGIN_FRAME_GRIPPER_SSIDE].ResetContent();
	m_ComboAxis[MACHINE_ORIGIN_FRAME_GRIPPER_SSIDE].AddString(_T("L"));
	m_ComboAxis[MACHINE_ORIGIN_FRAME_GRIPPER_SSIDE].AddString(_T("R"));
	m_ComboAxis[MACHINE_ORIGIN_FRAME_GRIPPER_SSIDE].SetCurSel(0);


	m_ComboAxis[MACHINE_ORIGIN_FRAME_GRIPPER_LSIDE].ResetContent();
	m_ComboAxis[MACHINE_ORIGIN_FRAME_GRIPPER_LSIDE].AddString(_T("L1"));
	m_ComboAxis[MACHINE_ORIGIN_FRAME_GRIPPER_LSIDE].AddString(_T("L2"));
	m_ComboAxis[MACHINE_ORIGIN_FRAME_GRIPPER_LSIDE].AddString(_T("R1"));
	m_ComboAxis[MACHINE_ORIGIN_FRAME_GRIPPER_LSIDE].AddString(_T("R2"));
	m_ComboAxis[MACHINE_ORIGIN_FRAME_GRIPPER_LSIDE].SetCurSel(0);

	m_ComboAxis[MACHINE_ORIGIN_GLASS_RELEASE_SSIDE].ResetContent();
	m_ComboAxis[MACHINE_ORIGIN_GLASS_RELEASE_SSIDE].AddString(_T("Z1"));
	m_ComboAxis[MACHINE_ORIGIN_GLASS_RELEASE_SSIDE].AddString(_T("Z2"));
	m_ComboAxis[MACHINE_ORIGIN_GLASS_RELEASE_SSIDE].AddString(_T("Z3"));
	m_ComboAxis[MACHINE_ORIGIN_GLASS_RELEASE_SSIDE].AddString(_T("Z4"));
	m_ComboAxis[MACHINE_ORIGIN_GLASS_RELEASE_SSIDE].AddString(_T("Z5"));
	m_ComboAxis[MACHINE_ORIGIN_GLASS_RELEASE_SSIDE].SetCurSel(0);

	m_ComboAxis[MACHINE_ORIGIN_GLASS_RELEASE_SMOVE].ResetContent();
	m_ComboAxis[MACHINE_ORIGIN_GLASS_RELEASE_SMOVE].AddString(_T("L"));
	m_ComboAxis[MACHINE_ORIGIN_GLASS_RELEASE_SMOVE].AddString(_T("R"));
	m_ComboAxis[MACHINE_ORIGIN_GLASS_RELEASE_SMOVE].SetCurSel(0);


	m_ComboAxis[MACHINE_ORIGIN_GLASS_RELEASE_LSIDE].ResetContent();
	m_ComboAxis[MACHINE_ORIGIN_GLASS_RELEASE_LSIDE].AddString(_T("L_Z1"));
	m_ComboAxis[MACHINE_ORIGIN_GLASS_RELEASE_LSIDE].AddString(_T("L_Z2"));
	m_ComboAxis[MACHINE_ORIGIN_GLASS_RELEASE_LSIDE].AddString(_T("L_Z3"));
	m_ComboAxis[MACHINE_ORIGIN_GLASS_RELEASE_LSIDE].AddString(_T("L_Z4"));
	m_ComboAxis[MACHINE_ORIGIN_GLASS_RELEASE_LSIDE].AddString(_T("L_Z5"));
	m_ComboAxis[MACHINE_ORIGIN_GLASS_RELEASE_LSIDE].AddString(_T("L_Z6"));
	m_ComboAxis[MACHINE_ORIGIN_GLASS_RELEASE_LSIDE].AddString(_T("L_Z7"));
	m_ComboAxis[MACHINE_ORIGIN_GLASS_RELEASE_LSIDE].AddString(_T("L_Z8"));
	m_ComboAxis[MACHINE_ORIGIN_GLASS_RELEASE_LSIDE].SetCurSel(0);

	m_ComboAxis[MACHINE_ORIGIN_GLASS_RELEASE_LMOVE].ResetContent();
	m_ComboAxis[MACHINE_ORIGIN_GLASS_RELEASE_LMOVE].AddString(_T("L_1"));
	m_ComboAxis[MACHINE_ORIGIN_GLASS_RELEASE_LMOVE].AddString(_T("L_2"));
	m_ComboAxis[MACHINE_ORIGIN_GLASS_RELEASE_LMOVE].AddString(_T("R_1"));
	m_ComboAxis[MACHINE_ORIGIN_GLASS_RELEASE_LMOVE].AddString(_T("R_2"));
	m_ComboAxis[MACHINE_ORIGIN_GLASS_RELEASE_LMOVE].SetCurSel(0);


	m_ComboAxis[MACHINE_ORIGIN_FRAME_TRANSFER_MOVE].ResetContent();
	m_ComboAxis[MACHINE_ORIGIN_FRAME_TRANSFER_MOVE].AddString(_T("X1"));
	m_ComboAxis[MACHINE_ORIGIN_FRAME_TRANSFER_MOVE].AddString(_T("X2"));
	m_ComboAxis[MACHINE_ORIGIN_FRAME_TRANSFER_MOVE].SetCurSel(0);


	m_ComboAxis[MACHINE_ORIGIN_ROLLER_RELEASE_MOVE].ResetContent();
	m_ComboAxis[MACHINE_ORIGIN_ROLLER_RELEASE_MOVE].AddString(_T("F_L"));
	m_ComboAxis[MACHINE_ORIGIN_ROLLER_RELEASE_MOVE].AddString(_T("F_R"));
	m_ComboAxis[MACHINE_ORIGIN_ROLLER_RELEASE_MOVE].AddString(_T("R_L"));
	m_ComboAxis[MACHINE_ORIGIN_ROLLER_RELEASE_MOVE].AddString(_T("R_R"));
	m_ComboAxis[MACHINE_ORIGIN_ROLLER_RELEASE_MOVE].SetCurSel(0);


	m_ComboAxis[MACHINE_ORIGIN_GLASS_RELEASE_LSIDE_R].ResetContent();
	m_ComboAxis[MACHINE_ORIGIN_GLASS_RELEASE_LSIDE_R].AddString(_T("R_Z1"));
	m_ComboAxis[MACHINE_ORIGIN_GLASS_RELEASE_LSIDE_R].AddString(_T("R_Z2"));
	m_ComboAxis[MACHINE_ORIGIN_GLASS_RELEASE_LSIDE_R].AddString(_T("R_Z3"));
	m_ComboAxis[MACHINE_ORIGIN_GLASS_RELEASE_LSIDE_R].AddString(_T("R_Z4"));
	m_ComboAxis[MACHINE_ORIGIN_GLASS_RELEASE_LSIDE_R].AddString(_T("R_Z5"));
	m_ComboAxis[MACHINE_ORIGIN_GLASS_RELEASE_LSIDE_R].AddString(_T("R_Z6"));
	m_ComboAxis[MACHINE_ORIGIN_GLASS_RELEASE_LSIDE_R].AddString(_T("R_Z7"));
	m_ComboAxis[MACHINE_ORIGIN_GLASS_RELEASE_LSIDE_R].AddString(_T("R_Z8"));
	m_ComboAxis[MACHINE_ORIGIN_GLASS_RELEASE_LSIDE_R].SetCurSel(0);


	m_ComboAxis[MACHINE_ORIGIN_ROLLER_RELEASE].ResetContent();
	m_ComboAxis[MACHINE_ORIGIN_ROLLER_RELEASE].AddString(_T("FL_Z"));
	m_ComboAxis[MACHINE_ORIGIN_ROLLER_RELEASE].AddString(_T("FR_Z"));
	m_ComboAxis[MACHINE_ORIGIN_ROLLER_RELEASE].AddString(_T("RL_Z"));
	m_ComboAxis[MACHINE_ORIGIN_ROLLER_RELEASE].AddString(_T("RR_Z"));
	m_ComboAxis[MACHINE_ORIGIN_ROLLER_RELEASE].SetCurSel(0);


	m_ComboAxis[MACHINE_ORIGIN_CLEANNING].ResetContent();
	m_ComboAxis[MACHINE_ORIGIN_CLEANNING].AddString(_T("Z1"));
	m_ComboAxis[MACHINE_ORIGIN_CLEANNING].AddString(_T("Z2"));
	m_ComboAxis[MACHINE_ORIGIN_CLEANNING].SetCurSel(0);


	m_ComboAxis[MACHINE_ORIGIN_FRAME_TRANSFER_L].ResetContent();
	m_ComboAxis[MACHINE_ORIGIN_FRAME_TRANSFER_L].AddString(_T("L"));
	m_ComboAxis[MACHINE_ORIGIN_FRAME_TRANSFER_L].SetCurSel(0);

#pragma endregion
	
	//Origin Group Led
	m_stcOriginGroupLed[MACHINE_ORIGIN_WORKSTAGE].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_GROUP_LED_WORKSTAGE, this);
	m_stcOriginGroupLed[MACHINE_ORIGIN_GANTRY_Y].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_GROUP_LED_GANTRY_Y, this);
	m_stcOriginGroupLed[MACHINE_ORIGIN_GANTRY_Z].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_GROUP_LED_GANTRY_Z, this);
	m_stcOriginGroupLed[MACHINE_ORIGIN_FRAME_UPDOWN].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_GROUP_LED_FRAME_UPDOWN, this);
	m_stcOriginGroupLed[MACHINE_ORIGIN_STAGE_UVW].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_GROUP_LED_STAGE_UVW, this);
	m_stcOriginGroupLed[MACHINE_ORIGIN_GLASS_POPUP_Z].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_GROUP_LED_GLASS_POPUP_Z, this);
	m_stcOriginGroupLed[MACHINE_ORIGIN_FRAME_GRIPPER_SSIDE].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_GROUP_LED_FRAME_GRIPPER_SSIDE, this);
	m_stcOriginGroupLed[MACHINE_ORIGIN_FRAME_GRIPPER_LSIDE].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_GROUP_LED_FRAME_GRIPPER_LSIDE, this);
	m_stcOriginGroupLed[MACHINE_ORIGIN_GLASS_RELEASE_SSIDE].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_GROUP_LED_GLASS_RELEASE_SSIDE, this);
	m_stcOriginGroupLed[MACHINE_ORIGIN_GLASS_RELEASE_SMOVE].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_GROUP_LED_GLASS_RELEASE_SMOVE, this);
	m_stcOriginGroupLed[MACHINE_ORIGIN_GLASS_RELEASE_LSIDE].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_GROUP_LED_GLASS_RELEASE_LSIDE, this);
	m_stcOriginGroupLed[MACHINE_ORIGIN_GLASS_RELEASE_LMOVE].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_GROUP_LED_GLASS_RELEASE_LMOVE, this);
	m_stcOriginGroupLed[MACHINE_ORIGIN_FRAME_TRANSFER_MOVE].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_GROUP_LED_FRAME_TRANSFER_MOVE, this);
	m_stcOriginGroupLed[MACHINE_ORIGIN_ROLLER_RELEASE_MOVE].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_GROUP_LED_ROLLER_RELEASE_MOVE, this);
	m_stcOriginGroupLed[MACHINE_ORIGIN_GLASS_RELEASE_LSIDE_R].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_GROUP_LED_GLASS_RELEASE_LSIDE_R, this);
	m_stcOriginGroupLed[MACHINE_ORIGIN_ROLLER_RELEASE].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_GROUP_LED_ROLLER_RELEASE, this);
	m_stcOriginGroupLed[MACHINE_ORIGIN_CLEANNING].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_GROUP_LED_CLEANNING, this);
	m_stcOriginGroupLed[MACHINE_ORIGIN_FRAME_TRANSFER_L].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_GROUP_LED_FRAME_TRANSFER_L, this);


	//Origin Led
	m_stcOriginLed[MACHINE_ORIGIN_WORKSTAGE].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_LED_WORKSTAGE, this);
	m_stcOriginLed[MACHINE_ORIGIN_GANTRY_Y].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_LED_GANTRY_Y, this);
	m_stcOriginLed[MACHINE_ORIGIN_GANTRY_Z].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_LED_GANTRY_Z, this);
	m_stcOriginLed[MACHINE_ORIGIN_FRAME_UPDOWN].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_LED_FRAME_UPDOWN, this);
	m_stcOriginLed[MACHINE_ORIGIN_STAGE_UVW].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_LED_STAGE_UVW, this);
	m_stcOriginLed[MACHINE_ORIGIN_GLASS_POPUP_Z].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_LED_GLASS_POPUP_Z, this);
	m_stcOriginLed[MACHINE_ORIGIN_FRAME_GRIPPER_SSIDE].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_LED_FRAME_GRIPPER_SSIDE, this);
	m_stcOriginLed[MACHINE_ORIGIN_FRAME_GRIPPER_LSIDE].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_LED_FRAME_GRIPPER_LSIDE, this);
	m_stcOriginLed[MACHINE_ORIGIN_GLASS_RELEASE_SSIDE].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_LED_GLASS_RELEASE_SSIDE, this);
	m_stcOriginLed[MACHINE_ORIGIN_GLASS_RELEASE_SMOVE].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_LED_GLASS_RELEASE_SMOVE, this);
	m_stcOriginLed[MACHINE_ORIGIN_GLASS_RELEASE_LSIDE].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_LED_GLASS_RELEASE_LSIDE, this);
	m_stcOriginLed[MACHINE_ORIGIN_GLASS_RELEASE_LMOVE].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_LED_GLASS_RELEASE_LMOVE, this);
	m_stcOriginLed[MACHINE_ORIGIN_FRAME_TRANSFER_MOVE].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_LED_FRAME_TRANSFER_MOVE, this);
	m_stcOriginLed[MACHINE_ORIGIN_ROLLER_RELEASE_MOVE].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_LED_ROLLER_RELEASE_MOVE, this);
	m_stcOriginLed[MACHINE_ORIGIN_GLASS_RELEASE_LSIDE_R].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_LED_GLASS_RELEASE_LSIDE_R, this);
	m_stcOriginLed[MACHINE_ORIGIN_ROLLER_RELEASE].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_LED_ROLLER_RELEASE, this);
	m_stcOriginLed[MACHINE_ORIGIN_CLEANNING].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_LED_CLEANNING, this);
	m_stcOriginLed[MACHINE_ORIGIN_FRAME_TRANSFER_L].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_LED_FRAME_TRANSFER_L, this);


	//Origin Button
	m_BtnOrgin[MACHINE_ORIGIN_WORKSTAGE].SubclassDlgItem(IDC_BUTTON_MACHINE_ORIGIN_WORKSTAGE, this);
	m_BtnOrgin[MACHINE_ORIGIN_GANTRY_Y].SubclassDlgItem(IDC_BUTTON_MACHINE_ORIGIN_GANTRY_Y, this);
	m_BtnOrgin[MACHINE_ORIGIN_GANTRY_Z].SubclassDlgItem(IDC_BUTTON_MACHINE_ORIGIN_GANTRY_Z, this);
	m_BtnOrgin[MACHINE_ORIGIN_FRAME_UPDOWN].SubclassDlgItem(IDC_BUTTON_MACHINE_ORIGIN_FRAME_UPDOWN, this);
	m_BtnOrgin[MACHINE_ORIGIN_STAGE_UVW].SubclassDlgItem(IDC_BUTTON_MACHINE_ORIGIN_STAGE_UVW, this);
	m_BtnOrgin[MACHINE_ORIGIN_GLASS_POPUP_Z].SubclassDlgItem(IDC_BUTTON_MACHINE_ORIGIN_GLASS_POPUP_Z, this);
	m_BtnOrgin[MACHINE_ORIGIN_FRAME_GRIPPER_SSIDE].SubclassDlgItem(IDC_BUTTON_MACHINE_ORIGIN_FRAME_GRIPPER_SSIDE, this);
	m_BtnOrgin[MACHINE_ORIGIN_FRAME_GRIPPER_LSIDE].SubclassDlgItem(IDC_BUTTON_MACHINE_ORIGIN_FRAME_GRIPPER_LSIDE, this);
	m_BtnOrgin[MACHINE_ORIGIN_GLASS_RELEASE_SSIDE].SubclassDlgItem(IDC_BUTTON_MACHINE_ORIGIN_GLASS_RELEASE_SSIDE, this);
	m_BtnOrgin[MACHINE_ORIGIN_GLASS_RELEASE_SMOVE].SubclassDlgItem(IDC_BUTTON_MACHINE_ORIGIN_GLASS_RELEASE_SMOVE, this);
	m_BtnOrgin[MACHINE_ORIGIN_GLASS_RELEASE_LSIDE].SubclassDlgItem(IDC_BUTTON_MACHINE_ORIGIN_GLASS_RELEASE_LSIDE, this);
	m_BtnOrgin[MACHINE_ORIGIN_GLASS_RELEASE_LMOVE].SubclassDlgItem(IDC_BUTTON_MACHINE_ORIGIN_GLASS_RELEASE_LMOVE, this);
	m_BtnOrgin[MACHINE_ORIGIN_FRAME_TRANSFER_MOVE].SubclassDlgItem(IDC_BUTTON_MACHINE_ORIGIN_FRAME_TRANSFER_MOVE, this);
	m_BtnOrgin[MACHINE_ORIGIN_ROLLER_RELEASE_MOVE].SubclassDlgItem(IDC_BUTTON_MACHINE_ORIGIN_ROLLER_RELEASE_MOVE, this);
	m_BtnOrgin[MACHINE_ORIGIN_GLASS_RELEASE_LSIDE_R].SubclassDlgItem(IDC_BUTTON_MACHINE_ORIGIN_GLASS_RELEASE_LSIDE_R, this);
	m_BtnOrgin[MACHINE_ORIGIN_ROLLER_RELEASE].SubclassDlgItem(IDC_BUTTON_MACHINE_ORIGIN_ROLLER_RELEASE, this);
	m_BtnOrgin[MACHINE_ORIGIN_CLEANNING].SubclassDlgItem(IDC_BUTTON_MACHINE_ORIGIN_CLEANNING, this);
	m_BtnOrgin[MACHINE_ORIGIN_FRAME_TRANSFER_L].SubclassDlgItem(IDC_BUTTON_MACHINE_ORIGIN_FRAME_TRANSFER_L, this);


	//Servo OnOff Led
	m_stcServoOnOffLed[MACHINE_ORIGIN_WORKSTAGE].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_SERVO_ON_OFF_LED_WORKSTAGE, this);
	m_stcServoOnOffLed[MACHINE_ORIGIN_GANTRY_Y].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_SERVO_ON_OFF_LED_GANTRY_Y, this);
	m_stcServoOnOffLed[MACHINE_ORIGIN_GANTRY_Z].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_SERVO_ON_OFF_LED_GANTRY_Z, this);
	m_stcServoOnOffLed[MACHINE_ORIGIN_FRAME_UPDOWN].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_SERVO_ON_OFF_LED_FRAME_UPDOWN, this);
	m_stcServoOnOffLed[MACHINE_ORIGIN_STAGE_UVW].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_SERVO_ON_OFF_LED_STAGE_UVW, this);
	m_stcServoOnOffLed[MACHINE_ORIGIN_GLASS_POPUP_Z].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_SERVO_ON_OFF_LED_GLASS_POPUP_Z, this);
	m_stcServoOnOffLed[MACHINE_ORIGIN_FRAME_GRIPPER_SSIDE].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_SERVO_ON_OFF_LED_FRAME_GRIPPER_SSIDE, this);
	m_stcServoOnOffLed[MACHINE_ORIGIN_FRAME_GRIPPER_LSIDE].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_SERVO_ON_OFF_LED_FRAME_GRIPPER_LSIDE, this);
	m_stcServoOnOffLed[MACHINE_ORIGIN_GLASS_RELEASE_SSIDE].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_SERVO_ON_OFF_LED_GLASS_RELEASE_SSIDE, this);
	m_stcServoOnOffLed[MACHINE_ORIGIN_GLASS_RELEASE_SMOVE].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_SERVO_ON_OFF_LED_GLASS_RELEASE_SMOVE, this);
	m_stcServoOnOffLed[MACHINE_ORIGIN_GLASS_RELEASE_LSIDE].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_SERVO_ON_OFF_LED_GLASS_RELEASE_LSIDE, this);
	m_stcServoOnOffLed[MACHINE_ORIGIN_GLASS_RELEASE_LMOVE].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_SERVO_ON_OFF_LED_GLASS_RELEASE_LMOVE, this);
	m_stcServoOnOffLed[MACHINE_ORIGIN_FRAME_TRANSFER_MOVE].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_SERVO_ON_OFF_LED_FRAME_TRANSFER_MOVE, this);
	m_stcServoOnOffLed[MACHINE_ORIGIN_ROLLER_RELEASE_MOVE].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_SERVO_ON_OFF_LED_ROLLER_RELEASE_MOVE, this);
	m_stcServoOnOffLed[MACHINE_ORIGIN_GLASS_RELEASE_LSIDE_R].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_SERVO_ON_OFF_LED_GLASS_RELEASE_LSIDE_R, this);
	m_stcServoOnOffLed[MACHINE_ORIGIN_ROLLER_RELEASE].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_SERVO_ON_OFF_LED_ROLLER_RELEASE, this);
	m_stcServoOnOffLed[MACHINE_ORIGIN_CLEANNING].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_SERVO_ON_OFF_LED_CLEANNING, this);
	m_stcServoOnOffLed[MACHINE_ORIGIN_FRAME_TRANSFER_L].SubclassDlgItem(IDC_STATIC_MACHINE_ORIGIN_SERVO_ON_OFF_LED_FRAME_TRANSFER_L, this);


	//ServoOn Button
	m_BtnServoOn[MACHINE_ORIGIN_WORKSTAGE].SubclassDlgItem(IDC_BUTTON_MACHINE_SERVO_ON_WORKSTAGE, this);
	m_BtnServoOn[MACHINE_ORIGIN_GANTRY_Y].SubclassDlgItem(IDC_BUTTON_MACHINE_SERVO_ON_GANTRY_Y, this);
	m_BtnServoOn[MACHINE_ORIGIN_GANTRY_Z].SubclassDlgItem(IDC_BUTTON_MACHINE_SERVO_ON_GANTRY_Z, this);
	m_BtnServoOn[MACHINE_ORIGIN_FRAME_UPDOWN].SubclassDlgItem(IDC_BUTTON_MACHINE_SERVO_ON_FRAME_UPDOWN, this);
	m_BtnServoOn[MACHINE_ORIGIN_STAGE_UVW].SubclassDlgItem(IDC_BUTTON_MACHINE_SERVO_ON_STAGE_UVW, this);
	m_BtnServoOn[MACHINE_ORIGIN_GLASS_POPUP_Z].SubclassDlgItem(IDC_BUTTON_MACHINE_SERVO_ON_GLASS_POPUP_Z, this);
	m_BtnServoOn[MACHINE_ORIGIN_FRAME_GRIPPER_SSIDE].SubclassDlgItem(IDC_BUTTON_MACHINE_SERVO_ON_FRAME_GRIPPER_SSIDE, this);
	m_BtnServoOn[MACHINE_ORIGIN_FRAME_GRIPPER_LSIDE].SubclassDlgItem(IDC_BUTTON_MACHINE_SERVO_ON_FRAME_GRIPPER_LSIDE, this);
	m_BtnServoOn[MACHINE_ORIGIN_GLASS_RELEASE_SSIDE].SubclassDlgItem(IDC_BUTTON_MACHINE_SERVO_ON_GLASS_RELEASE_SSIDE, this);
	m_BtnServoOn[MACHINE_ORIGIN_GLASS_RELEASE_SMOVE].SubclassDlgItem(IDC_BUTTON_MACHINE_SERVO_ON_GLASS_RELEASE_SMOVE, this);
	m_BtnServoOn[MACHINE_ORIGIN_GLASS_RELEASE_LSIDE].SubclassDlgItem(IDC_BUTTON_MACHINE_SERVO_ON_GLASS_RELEASE_LSIDE, this);
	m_BtnServoOn[MACHINE_ORIGIN_GLASS_RELEASE_LMOVE].SubclassDlgItem(IDC_BUTTON_MACHINE_SERVO_ON_GLASS_RELEASE_LMOVE, this);
	m_BtnServoOn[MACHINE_ORIGIN_FRAME_TRANSFER_MOVE].SubclassDlgItem(IDC_BUTTON_MACHINE_SERVO_ON_FRAME_TRANSFER_MOVE, this);
	m_BtnServoOn[MACHINE_ORIGIN_ROLLER_RELEASE_MOVE].SubclassDlgItem(IDC_BUTTON_MACHINE_SERVO_ON_ROLLER_RELEASE_MOVE, this);
	m_BtnServoOn[MACHINE_ORIGIN_GLASS_RELEASE_LSIDE_R].SubclassDlgItem(IDC_BUTTON_MACHINE_SERVO_ON_GLASS_RELEASE_LSIDE_R, this);
	m_BtnServoOn[MACHINE_ORIGIN_ROLLER_RELEASE].SubclassDlgItem(IDC_BUTTON_MACHINE_SERVO_ON_ROLLER_RELEASE, this);
	m_BtnServoOn[MACHINE_ORIGIN_CLEANNING].SubclassDlgItem(IDC_BUTTON_MACHINE_SERVO_ON_CLEANNING, this);
	m_BtnServoOn[MACHINE_ORIGIN_FRAME_TRANSFER_L].SubclassDlgItem(IDC_BUTTON_MACHINE_SERVO_ON_FRAME_TRANSFER_L, this);


	//ServoOff Button
	m_BtnServoOff[MACHINE_ORIGIN_WORKSTAGE].SubclassDlgItem(IDC_BUTTON_MACHINE_SERVO_OFF_WORKSTAGE, this);
	m_BtnServoOff[MACHINE_ORIGIN_GANTRY_Y].SubclassDlgItem(IDC_BUTTON_MACHINE_SERVO_OFF_GANTRY_Y, this);
	m_BtnServoOff[MACHINE_ORIGIN_GANTRY_Z].SubclassDlgItem(IDC_BUTTON_MACHINE_SERVO_OFF_GANTRY_Z, this);
	m_BtnServoOff[MACHINE_ORIGIN_FRAME_UPDOWN].SubclassDlgItem(IDC_BUTTON_MACHINE_SERVO_OFF_FRAME_UPDOWN, this);
	m_BtnServoOff[MACHINE_ORIGIN_STAGE_UVW].SubclassDlgItem(IDC_BUTTON_MACHINE_SERVO_OFF_STAGE_UVW, this);
	m_BtnServoOff[MACHINE_ORIGIN_GLASS_POPUP_Z].SubclassDlgItem(IDC_BUTTON_MACHINE_SERVO_OFF_GLASS_POPUP_Z, this);
	m_BtnServoOff[MACHINE_ORIGIN_FRAME_GRIPPER_SSIDE].SubclassDlgItem(IDC_BUTTON_MACHINE_SERVO_OFF_FRAME_GRIPPER_SSIDE, this);
	m_BtnServoOff[MACHINE_ORIGIN_FRAME_GRIPPER_LSIDE].SubclassDlgItem(IDC_BUTTON_MACHINE_SERVO_OFF_FRAME_GRIPPER_LSIDE, this);
	m_BtnServoOff[MACHINE_ORIGIN_GLASS_RELEASE_SSIDE].SubclassDlgItem(IDC_BUTTON_MACHINE_SERVO_OFF_GLASS_RELEASE_SSIDE, this);
	m_BtnServoOff[MACHINE_ORIGIN_GLASS_RELEASE_SMOVE].SubclassDlgItem(IDC_BUTTON_MACHINE_SERVO_OFF_GLASS_RELEASE_SMOVE, this);
	m_BtnServoOff[MACHINE_ORIGIN_GLASS_RELEASE_LSIDE].SubclassDlgItem(IDC_BUTTON_MACHINE_SERVO_OFF_GLASS_RELEASE_LSIDE, this);
	m_BtnServoOff[MACHINE_ORIGIN_GLASS_RELEASE_LMOVE].SubclassDlgItem(IDC_BUTTON_MACHINE_SERVO_OFF_GLASS_RELEASE_LMOVE, this);
	m_BtnServoOff[MACHINE_ORIGIN_FRAME_TRANSFER_MOVE].SubclassDlgItem(IDC_BUTTON_MACHINE_SERVO_OFF_FRAME_TRANSFER_MOVE, this);
	m_BtnServoOff[MACHINE_ORIGIN_ROLLER_RELEASE_MOVE].SubclassDlgItem(IDC_BUTTON_MACHINE_SERVO_OFF_ROLLER_RELEASE_MOVE, this);
	m_BtnServoOff[MACHINE_ORIGIN_GLASS_RELEASE_LSIDE_R].SubclassDlgItem(IDC_BUTTON_MACHINE_SERVO_OFF_GLASS_RELEASE_LSIDE_R, this);
	m_BtnServoOff[MACHINE_ORIGIN_ROLLER_RELEASE].SubclassDlgItem(IDC_BUTTON_MACHINE_SERVO_OFF_ROLLER_RELEASE, this);
	m_BtnServoOff[MACHINE_ORIGIN_CLEANNING].SubclassDlgItem(IDC_BUTTON_MACHINE_SERVO_OFF_CLEANNING, this);
	m_BtnServoOff[MACHINE_ORIGIN_FRAME_TRANSFER_L].SubclassDlgItem(IDC_BUTTON_MACHINE_SERVO_OFF_FRAME_TRANSFER_L, this);



	for (int i = 0; i < MACHINE_ORIGIN_MAX; i++)
	{
		m_stcOriginGroupLed[i].SetBackgroundColor(LLTGRAY);
		m_stcOriginGroupLed[i].SetTextColor(BLACK);

		m_stcOriginLed[i].SetBackgroundColor(LLTGRAY);
		m_stcOriginLed[i].SetTextColor(BLACK);

		m_BtnOrgin[i].SetColor(BLACK, LLTGRAY);
		m_BtnOrgin[i].EnableWindow(FALSE);

		m_stcServoOnOffLed[i].SetBackgroundColor(LLTGRAY);
		m_stcServoOnOffLed[i].SetTextColor(BLACK);

		m_BtnServoOn[i].SetColor(BLACK, LLTGRAY);
		m_BtnServoOn[i].EnableWindow(FALSE);

		m_BtnServoOff[i].SetColor(BLACK, LLTGRAY);
		m_BtnServoOff[i].EnableWindow(FALSE);
	}

	m_CheckInterlock.SubclassDlgItem(IDC_MACHINE_ORIGIN_INTERLOCK_CHECK, this);
}

void CVisionAgentMachineOriginDlg::InitPara()
{
	m_CheckInterlock.SetCheck(TRUE);
	BtnEnable(FALSE);

	m_JogMotion = &Devs::m_JogMotion;
	m_nMoving = 0;
	m_nAllOriginIng = 0;	
	memset(m_nUmacOriginIngStatus, 0x0, sizeof(m_nUmacOriginIngStatus)); //KJT 20210320
	memset(m_nRemoteAjinOriginIngStatus, 0x0, sizeof(m_nRemoteAjinOriginIngStatus)); //KJT 20210320
	memset(m_nDirectAjinOriginIngStatus, 0x0, sizeof(m_nDirectAjinOriginIngStatus)); //KJT 20210320
}

void CVisionAgentMachineOriginDlg::OnBnClickedMachineOriginInterlockCheck()
{
	int nCheckInterlock = m_CheckInterlock.GetCheck();

	if (nCheckInterlock)
	{
		m_CheckInterlock.SetCheck(TRUE);
		BtnEnable(FALSE);
	}
	else
	{
		m_CheckInterlock.SetCheck(FALSE);
		BtnEnable(TRUE);
	}
}


void CVisionAgentMachineOriginDlg::BtnEnable(bool bEnable)
{
	m_btnAllOrgin.EnableWindow(bEnable);
	m_btnAllServoOn.EnableWindow(bEnable);
	m_btnAllServoOff.EnableWindow(bEnable);

	//원점 상태 순서대로 체크.
	int i = 0;
	for (i = 0; i < MACHINE_ORIGIN_MAX; i++)
	{
		m_BtnOrgin[i].EnableWindow(bEnable);
		m_BtnServoOn[i].EnableWindow(bEnable);
		m_BtnServoOff[i].EnableWindow(bEnable);
	}

	//최종 상태에서 원점 잡아야 할 부분 부터 On/Off 버튼 살려주기.
	//m_BtnOrgin[MACHINE_ORIGIN_FRAME_LIFT].EnableWindow(TRUE);
	//m_BtnServoOn[MACHINE_ORIGIN_FRAME_LIFT].EnableWindow(TRUE);
	//m_BtnServoOff[MACHINE_ORIGIN_FRAME_LIFT].EnableWindow(TRUE);
}


void CVisionAgentMachineOriginDlg::OnBnClickedMachineOriginAllStopBtn()
{
	Devs::StopAll();
}

BOOL CVisionAgentMachineOriginDlg::GetAxisOriginParamByUI(en_MACHINE_ORIGIN_DEF eJogUIDefine, enum_Axis* peAxis, double* pPosAbs, double* pPosRel, double* pJogSpeed, double* pAccel, double* pDecel, CString* strDiscription)
{
	CVisionAgentDlg *pVisionAgentDlg;
	pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	BOOL bResult = TRUE;
	enum_Axis eAxis = AXIS_NONE;
	CString strPosAbs, strPosRel;
	int nSelAxis = -1, nSelJogSpeed = -1;
	double dPosAbs = 0.0, dPosRel = 0.0;

	nSelAxis = m_ComboAxis[eJogUIDefine].GetCurSel();

	return bResult;
}

BOOL CVisionAgentMachineOriginDlg::GetAxisOriginGroupParam(en_MACHINE_ORIGIN_DEF eJogUIDefine)
{
	CVisionAgentDlg *pVisionAgentDlg;
	pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	BOOL bResult = TRUE;
	enum_Axis eAxis = AXIS_NONE;

	return bResult;
}

void CVisionAgentMachineOriginDlg::OnTimer(UINT_PTR nIDEvent)
{
	CVisionAgentDlg *pVisionAgentDlg;
	pVisionAgentDlg = (CVisionAgentDlg *)theApp.m_pMainWnd;

	//int i, nAxisNo, nDInputNo, nDOutputNo, nStatus;
	int  nAxisType, nAxisNo;
	//int nAInputNo, nStatus;

	bool AllServoOnFlag = true;
	bool AllHomeFlag = true;
	double dPos = 0.0, dVel = 0.0;
	CString szMsg = _T(""), strDiscription = _T("");
	double	dPosAbs = 0.0, dPosRel = 0.0, dJogSpeed = 0.0, dAccel = 0.0, dDecel = 0.0;
	enum_Axis  eAxis = AXIS_NONE;
	int i = 0, j = 0;
	BOOL bHomeStatus = FALSE;
	BOOL bInMotion = FALSE;
	

	// jhryu 주석처리
	/*
	if (nIDEvent == 1)
	{
		if (IsWindowVisible())
		{
			for (i = 0; i < MACHINE_ORIGIN_MAX; i++)
			{
				if (!GetAxisOriginParamByUI((en_MACHINE_ORIGIN_DEF)i, &eAxis, &dPosAbs, &dPosRel, &dJogSpeed, &dAccel, &dDecel, &strDiscription))
					continue;

				if (GetAxisOriginGroupParam((en_MACHINE_ORIGIN_DEF)i))
				{
					m_stcOriginGroupLed[i].SetBackgroundColor(GREEN);
				}
				else
				{
					m_stcOriginGroupLed[i].SetBackgroundColor(RED);
				}

				if (SharedInfo::GetServoOnStatus(eAxis))
				{
					m_stcServoOnOffLed[i].SetBackgroundColor(GREEN);
				}
				else
				{
					m_stcServoOnOffLed[i].SetBackgroundColor(RED);
				}

				if (SharedInfo::GetHomeStatus(eAxis))
				{
					m_stcOriginLed[i].SetBackgroundColor(GREEN);
				}
				else 
				{
					//Ajin
					if (i >= MACHINE_ORIGIN_CAMERA_Z)
					{
						//Direct Ajin
						if (i == MACHINE_ORIGIN_CAMERA_Z)
						{
							if (SharedInfo::GetInMotion(eAxis))
							{
								SharedInfo::GetActualAxisNoByEnumAxis(eAxis, &nAxisType, &nAxisNo);

								if (++m_nDirectAjinOriginIngStatus[nAxisNo] < 8)
								{
									m_stcOriginLed[i].SetBackgroundColor(BLUE);
								}
								else if (m_nDirectAjinOriginIngStatus[nAxisNo] < 15)
								{
									m_nDirectAjinOriginIngStatus[nAxisNo] = 0;
									m_stcOriginLed[i].SetBackgroundColor(LTGRAY);
								}
							}
							else
							{
								m_stcOriginLed[i].SetBackgroundColor(RED);
							}
						}
						//Remote Ajin
						else
						{
							if (SharedInfo::GetInMotion(eAxis))
							{
								SharedInfo::GetActualAxisNoByEnumAxis(eAxis, &nAxisType, &nAxisNo);

								if (++m_nRemoteAjinOriginIngStatus[nAxisNo] < 8)
								{
									m_stcOriginLed[i].SetBackgroundColor(BLUE);
								}
								else if (m_nRemoteAjinOriginIngStatus[nAxisNo] < 15)
								{
									m_nRemoteAjinOriginIngStatus[nAxisNo] = 0;
									m_stcOriginLed[i].SetBackgroundColor(LTGRAY);
								}
							}
							else
							{
								m_stcOriginLed[i].SetBackgroundColor(RED);
							}
						}
					}
					//Umac
					else
					{	
						SharedInfo::GetActualAxisNoByEnumAxis(eAxis, &nAxisType, &nAxisNo);

						if (SharedInfo::UmacServoOnStatus[nAxisNo] == 1 && SharedInfo::UmacAlarmStatus[nAxisNo] == 0 && SharedInfo::UmacInMotionStatus[nAxisNo] == 1)
						//if (SharedInfo::UmacAlarmStatus[nAxisNo] == 0 && SharedInfo::UmacInMotionStatus[nAxisNo] == 1)
						{
							if (++m_nUmacOriginIngStatus[i] < 8)
							{
								m_stcOriginLed[i].SetBackgroundColor(BLUE);
							}
							else if (m_nUmacOriginIngStatus[i] < 15)
							{
								m_nUmacOriginIngStatus[i] = 0;
								m_stcOriginLed[i].SetBackgroundColor(LTGRAY);
							}
						}
						else
						{
							m_stcOriginLed[i].SetBackgroundColor(RED);
						}
					}					
				}
			}

			//Ssm All Servo On LED 구현
			for (int i = 0; i < AXIS_MAX; i++)
			{
				if (SharedInfo::GetServoOnStatus(enum_Axis(i)))
				{

				}
				else
				{
					AllServoOnFlag = false;
				}
			}
			if (AllServoOnFlag == true)
			{
				m_stcAllServoOnOffLed.SetBackgroundColor(GREEN);
			}
			else
			{
				m_stcAllServoOnOffLed.SetBackgroundColor(RED);
			}
			//Ssming All Home On LED
			for (int i = 0; i < AXIS_MAX; i++)
			{
				if (SharedInfo::GetHomeStatus(enum_Axis(i)) == 0)
				{
					AllHomeFlag = false;
				}
			}
			if (AllHomeFlag == true)
			{
				m_stcAllOriginLed.SetBackgroundColor(GREEN);
			}
			else
			{
				m_stcAllOriginLed.SetBackgroundColor(RED);
				//if (AllHomeFlag == true)
				//{
				//	if (m_nMoving >= 10)
				//	{
				//		m_stcAllOriginLed.SetBackgroundColor(YELLOW);
				//		if (m_nMoving >= 20) m_nMoving = 0;
				//	}
				//	else
				//	{
				//		m_stcAllOriginLed.SetBackgroundColor(DKGRAY);
				//	}
				//}
				//else
				//{
				//	m_stcAllOriginLed.SetBackgroundColor(RED);
				//}
			}
			m_nMoving++;
		}
	}
	*/ // jhryu 주석
	CDialogEx::OnTimer(nIDEvent);
}

void CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineOriginAll()
{
	int nResult = AfxMessageBox(_T("All Axis Origin Start?"), MB_OKCANCEL);
	if (nResult == IDOK)
	{
		memset(m_nUmacOriginIngStatus, 0x0, sizeof(m_nUmacOriginIngStatus)); //KJT 20210320
		memset(m_nRemoteAjinOriginIngStatus, 0x0, sizeof(m_nRemoteAjinOriginIngStatus)); //KJT 20210320
		memset(m_nDirectAjinOriginIngStatus, 0x0, sizeof(m_nDirectAjinOriginIngStatus)); //KJT 20210320

		int k = 0;

		for (k = 0; k < DIRECT_AXIS_MAX; k++)
		{			
			SharedInfo::DirectAjinOriginIngStatus[k] = 0;			
		}

		for (k = 0; k < REMOTE_AXIS_UMAC_MAX; k++)
		{	
			SharedInfo::UmacOriginIngStatus[k] = 0;			
		}
		for (k = 0; k < REMOTE_AXIS_MAX; k++)
		{	
			SharedInfo::RemoteAjinOriginIngStatus[k] = 0;			
		}

		Devs::m_Origin_AllAxis_Flow.Start();
		//pMachineOrigin->Start();
	}
}

void CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineServoOnAll()
{
	double	dPosAbs = 0.0, dPosRel = 0.0, dJogSpeed = 0.0, dAccel = 0.0, dDecel = 0.0;
	int nAxis = AXIS_NONE;

	int nResult = AfxMessageBox(_T("All Axis Servo On?"), MB_OKCANCEL);
	if (nResult == IDOK)
	{
		for (nAxis = AXIS_NONE + 1; nAxis < AXIS_MAX; nAxis++)
		{
			m_JogMotion->ServoOnOff((enum_Axis)nAxis, TRUE);
			Sleep(20); //KJT 20200811
		}
	}
}

void CVisionAgentMachineOriginDlg::OnBnClickedMachineOriginAllServoOffBtn()
{
	double	dPosAbs = 0.0, dPosRel = 0.0, dJogSpeed = 0.0, dAccel = 0.0, dDecel = 0.0;
	int nAxis = AXIS_NONE;

	int nResult = AfxMessageBox(_T("All Axis Servo Off?"), MB_OKCANCEL);
	if (nResult == IDOK)
	{
		for (nAxis = AXIS_NONE + 1; nAxis < AXIS_MAX; nAxis++)
		{
			m_JogMotion->ServoOnOff((enum_Axis)nAxis, FALSE);
			Sleep(20); //KJT 20200811
		}
	}
}

void CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineOriginGantryY()
{
	CString StrDiscription = _T(""), Str = _T("");
	double	dPosAbs = 0.0, dPosRel = 0.0, dJogSpeed = 0.0, dAccel = 0.0, dDecel = 0.0;
	enum_Axis eAxis = AXIS_NONE;
	double dPosTemp = 0.0;

#pragma region //Interlock

	if (SharedInfo::GetHomeStatus(AXIS_CAMERA_Z1) != TRUE)
	{
		AfxMessageBox(_T("Camera Z1 Origin Check !!!"));
		return;
	}

	if (SharedInfo::GetServoOnStatus(AXIS_CAMERA_Z1) == 0)
	{
		AfxMessageBox(_T("Camera Z1 is servo off"));
		return;
	}

	dPosTemp = SharedInfo::GetCmdPos(AXIS_CAMERA_Z1);	
	if (dPosTemp < CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Wait_Pos - 0.002)
	{
		AfxMessageBox(_T("Camera Z1 Wait Pos Check !!!"));
		return;
	}

#pragma endregion

	if (!GetAxisOriginParamByUI(MACHINE_ORIGIN_GANTRY_Y, &eAxis, &dPosAbs, &dPosRel, &dJogSpeed, &dAccel, &dDecel, &StrDiscription))
		return;

	Str.Format(_T("%s Origin Start?"), StrDiscription);
	int nResult = AfxMessageBox(Str, MB_OKCANCEL);
	if (nResult == IDOK)
	{
		nResult = m_JogMotion->OriginStart(eAxis);		
	}
}


void CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineOriginGantryX()
{
	CString StrDiscription = _T(""), Str = _T("");
	double	dPosAbs = 0.0, dPosRel = 0.0, dJogSpeed = 0.0, dAccel = 0.0, dDecel = 0.0;
	enum_Axis eAxis = AXIS_NONE;
	double dPosTemp = 0.0;

#pragma region //Interlock
	if (SharedInfo::GetServoOnStatus(AXIS_CAMERA_Z1) == 0)
	{
		Str.Format(_T("Camera Z1 is servo off"));
		return;
	}

	if (SharedInfo::GetHomeStatus(AXIS_CAMERA_Z1) != TRUE)
	{
		AfxMessageBox(_T("Camera Z1 Origin Check !!!"));
		return;
	}

	dPosTemp = SharedInfo::GetCmdPos(AXIS_CAMERA_Z1);
	if (dPosTemp < CManualData::m_ManualDataGantry.Info.m_dGantry_Z1_Wait_Pos - 0.002)
	{
		AfxMessageBox(_T("Camera Z1 Wait Pos Check !!!"));
		return;
	}
#pragma endregion

	/*// jhryu 주석처리
	if (!GetAxisOriginParamByUI(MACHINE_ORIGIN_WORKSTAGE, &eAxis, &dPosAbs, &dPosRel, &dJogSpeed, &dAccel, &dDecel, &StrDiscription))
		return;
	*/

	Str.Format(_T("%s Origin Start?"), StrDiscription);
	int nResult = AfxMessageBox(Str, MB_OKCANCEL);
	if (nResult == IDOK)
	{
		nResult = m_JogMotion->OriginStart(eAxis);		
	}
}


void CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineOriginCameraZ()
{
	/* // jhryu 주석처리
	CString StrDiscription = _T(""), Str = _T("");
	double	dPosAbs = 0.0, dPosRel = 0.0, dJogSpeed = 0.0, dAccel = 0.0, dDecel = 0.0;
	enum_Axis eAxis = AXIS_NONE;

	if (!GetAxisOriginParamByUI(MACHINE_ORIGIN_CAMERA_Z, &eAxis, &dPosAbs, &dPosRel, &dJogSpeed, &dAccel, &dDecel, &StrDiscription))
		return;	

	Str.Format(_T("%s Origin Start?"), StrDiscription);
	int nResult = AfxMessageBox(Str, MB_OKCANCEL);
	if (nResult == IDOK)
	{
		m_JogMotion->OriginStart(eAxis);
	}
	*/
}



void CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineOriginLoadingStage()
{
	// jhryu 주석처리
	//CString StrDiscription = _T(""), Str = _T("");
	//double	dPosAbs = 0.0, dPosRel = 0.0, dJogSpeed = 0.0, dAccel = 0.0, dDecel = 0.0;
	//enum_Axis eAxis = AXIS_NONE;

	//if (!GetAxisOriginParamByUI(MACHINE_ORIGIN_LOADING_STAGE, &eAxis, &dPosAbs, &dPosRel, &dJogSpeed, &dAccel, &dDecel, &StrDiscription))
	//	return;		

	//Str.Format(_T("%s Origin Start?"), StrDiscription);
	//int nResult = AfxMessageBox(Str, MB_OKCANCEL);
	//if (nResult == IDOK)
	//{
	//	m_JogMotion->OriginStart(eAxis);
	//}
}



void CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineOriginGripperClamp()
{
	//CString StrDiscription = _T(""), Str = _T("");
	//double	dPosAbs = 0.0, dPosRel = 0.0, dJogSpeed = 0.0, dAccel = 0.0, dDecel = 0.0;
	//enum_Axis eAxis = AXIS_NONE;

	//if (!GetAxisOriginParamByUI(MACHINE_ORIGIN_GRIPPER_CLAMP, &eAxis, &dPosAbs, &dPosRel, &dJogSpeed, &dAccel, &dDecel, &StrDiscription))
	//	return;

	//Str.Format(_T("%s Origin Start?"), StrDiscription);
	//int nResult = AfxMessageBox(Str, MB_OKCANCEL);
	//if (nResult == IDOK)
	//{
	//	m_JogMotion->OriginStart(eAxis);
	//}
}


void CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineOriginGripperStretch()
{
	// jhryu 주석
	//CString StrDiscription = _T(""), Str = _T("");
	//double	dPosAbs = 0.0, dPosRel = 0.0, dJogSpeed = 0.0, dAccel = 0.0, dDecel = 0.0;
	//enum_Axis eAxis = AXIS_NONE;

	//if (!GetAxisOriginParamByUI(MACHINE_ORIGIN_GRIPPER_STRETCH, &eAxis, &dPosAbs, &dPosRel, &dJogSpeed, &dAccel, &dDecel, &StrDiscription))
	//	return;

	////if (Devs::m_ClampMotion.Is_ClampOff_All() != TRUE)
	////{
	////	AfxMessageBox(_T("Check All Clamp Off !!!"));
	////	return;
	////}

	//Str.Format(_T("%s Origin Start?"), StrDiscription);
	//int nResult = AfxMessageBox(Str, MB_OKCANCEL);
	//if (nResult == IDOK)
	//{
	//	m_JogMotion->OriginStart(eAxis);
	//}
}


void CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineOriginInspectionStage()
{

}

void CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineServoOnGantryY()
{
	CString StrDiscription = _T(""), Str = _T("");
	double	dPosAbs = 0.0, dPosRel = 0.0, dJogSpeed = 0.0, dAccel = 0.0, dDecel = 0.0;
	enum_Axis eAxis = AXIS_NONE;

	if (!GetAxisOriginParamByUI(MACHINE_ORIGIN_GANTRY_Y, &eAxis, &dPosAbs, &dPosRel, &dJogSpeed, &dAccel, &dDecel, &StrDiscription))
		return;

	Str.Format(_T("%s Servo On?"), StrDiscription);
	int nResult = AfxMessageBox(Str, MB_OKCANCEL);
	if (nResult == IDOK)
	{
		m_JogMotion->ServoOnOff(eAxis, TRUE);
	}
}


void CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineServoOnGantryX()
{

}


void CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineServoOnCameraZ()
{

}




void CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineServoOnLoadingStage()
{

}



void CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineServoOnGripperClamp()
{
	//CString StrDiscription = _T(""), Str = _T("");
	//double	dPosAbs = 0.0, dPosRel = 0.0, dJogSpeed = 0.0, dAccel = 0.0, dDecel = 0.0;
	//enum_Axis eAxis = AXIS_NONE;

	//if (!GetAxisOriginParamByUI(MACHINE_ORIGIN_GRIPPER_CLAMP, &eAxis, &dPosAbs, &dPosRel, &dJogSpeed, &dAccel, &dDecel, &StrDiscription))
	//	return;

	//Str.Format(_T("%s Servo On?"), StrDiscription);
	//int nResult = AfxMessageBox(Str, MB_OKCANCEL);
	//if (nResult == IDOK)
	//{
	//	m_JogMotion->ServoOnOff(eAxis, TRUE);
	//}
}


void CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineServoOnGripperStretch()
{

}


void CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineServoOnInspectionStage()
{

}

void CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineServoOffGantryY()
{
	CString StrDiscription = _T(""), Str = _T("");
	double	dPosAbs = 0.0, dPosRel = 0.0, dJogSpeed = 0.0, dAccel = 0.0, dDecel = 0.0;
	enum_Axis eAxis = AXIS_NONE;

	if (!GetAxisOriginParamByUI(MACHINE_ORIGIN_GANTRY_Y, &eAxis, &dPosAbs, &dPosRel, &dJogSpeed, &dAccel, &dDecel, &StrDiscription))
		return;

	Str.Format(_T("%s Servo Off?"), StrDiscription);
	int nResult = AfxMessageBox(Str, MB_OKCANCEL);
	if (nResult == IDOK)
	{
		m_JogMotion->ServoOnOff(eAxis, FALSE);
	}
}


void CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineServoOffGantryX()
{

}


void CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineServoOffCameraZ()
{

}



void CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineServoOffLoadingStage()
{

}


void CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineServoOffGripperClamp()
{
	//CString StrDiscription = _T(""), Str = _T("");
	//double	dPosAbs = 0.0, dPosRel = 0.0, dJogSpeed = 0.0, dAccel = 0.0, dDecel = 0.0;
	//enum_Axis eAxis = AXIS_NONE;

	//if (!GetAxisOriginParamByUI(MACHINE_ORIGIN_GRIPPER_CLAMP, &eAxis, &dPosAbs, &dPosRel, &dJogSpeed, &dAccel, &dDecel, &StrDiscription))
	//	return;

	//Str.Format(_T("%s Servo Off?"), StrDiscription);
	//int nResult = AfxMessageBox(Str, MB_OKCANCEL);
	//if (nResult == IDOK)
	//{
	//	m_JogMotion->ServoOnOff(eAxis, FALSE);
	//}
}


void CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineServoOffGripperStretch()
{

}


void CVisionAgentMachineOriginDlg::OnBnClickedButtonMachineServoOffInspectionStage()
{

}