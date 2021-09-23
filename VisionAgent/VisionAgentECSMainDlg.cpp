// VisionAgentECSMainDlg.cpp : ±¸Çö ÆÄÀÏÀÔ´Ï´Ù.
//

#include "stdafx.h"
#include "VisionAgent.h"
#include "VisionAgentECSMainDlg.h"
#include "afxdialogex.h"

// CVisionAgentECSMainDlg ´ëÈ­ »óÀÚÀÔ´Ï´Ù.

IMPLEMENT_DYNAMIC(CVisionAgentECSMainDlg, CDialogEx)

CVisionAgentECSMainDlg::CVisionAgentECSMainDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_VISION_AGENT_ECS_MAIN_DIALOG, pParent)
{
	Create(IDD_VISION_AGENT_ECS_MAIN_DIALOG, pParent);
}

CVisionAgentECSMainDlg::~CVisionAgentECSMainDlg()
{
}

void CVisionAgentECSMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CVisionAgentECSMainDlg, CDialogEx)
	ON_BN_CLICKED(IDC_CIM_MODE_ON_BTN, &CVisionAgentECSMainDlg::OnBnClickedCimModeOnBtn)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_MACHINE_MANAGEMENT_RUN_BTN, &CVisionAgentECSMainDlg::OnBnClickedMachineManagementRunBtn)
	ON_BN_CLICKED(IDC_MACHINE_MANAGEMENT_IDLE_BTN, &CVisionAgentECSMainDlg::OnBnClickedMachineManagementIdleBtn)
	ON_BN_CLICKED(IDC_MACHINE_MANAGEMENT_PAUSE_BTN, &CVisionAgentECSMainDlg::OnBnClickedMachineManagementPauseBtn)
	ON_BN_CLICKED(IDC_MACHINE_MANAGEMENT_PM_BTN, &CVisionAgentECSMainDlg::OnBnClickedMachineManagementPmBtn)
	ON_BN_CLICKED(IDC_MACHINE_MANAGEMENT_BM_BTN, &CVisionAgentECSMainDlg::OnBnClickedMachineManagementBmBtn)
	ON_BN_CLICKED(IDC_TIMEOUT_MANAGEMENT_SET_BTN, &CVisionAgentECSMainDlg::OnBnClickedTimeoutManagementSetBtn)
	ON_BN_CLICKED(IDC_CIM_MESSAGE_CONFIRM_BTN1, &CVisionAgentECSMainDlg::OnBnClickedCimMessageConfirmBtn1)
	ON_BN_CLICKED(IDC_CIM_MESSAGE_CONFIRM_BTN2, &CVisionAgentECSMainDlg::OnBnClickedCimMessageConfirmBtn2)
	ON_BN_CLICKED(IDC_CIM_MESSAGE_CONFIRM_BTN3, &CVisionAgentECSMainDlg::OnBnClickedCimMessageConfirmBtn3)
	ON_BN_CLICKED(IDC_CIM_MESSAGE_CONFIRM_BTN4, &CVisionAgentECSMainDlg::OnBnClickedCimMessageConfirmBtn4)
	ON_BN_CLICKED(IDC_CIM_MESSAGE_CONFIRM_BTN5, &CVisionAgentECSMainDlg::OnBnClickedCimMessageConfirmBtn5)
	ON_BN_CLICKED(IDC_ALARM_MANAGEMENT_ERROR_SET_BTN, &CVisionAgentECSMainDlg::OnBnClickedAlarmManagementErrorSetBtn)
	//	ON_BN_CLICKED(IDC_JOB_MANAGEMENT_REQUEST_BTN, &CVisionAgentECSMainDlg::OnBnClickedJobManagementRequestBtn)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_UPSTREAM_INLINE_ON_BTN, &CVisionAgentECSMainDlg::OnBnClickedUpstreamInlineOnBtn)
	ON_BN_CLICKED(IDC_UPSTREAM_INLINE_OFF_BTN, &CVisionAgentECSMainDlg::OnBnClickedUpstreamInlineOffBtn)
	ON_BN_CLICKED(IDC_DOWNSTREAM_INLINE_ON_BTN, &CVisionAgentECSMainDlg::OnBnClickedDownstreamInlineOnBtn)
	ON_BN_CLICKED(IDC_DOWNSTREAM_INLINE_OFF_BTN, &CVisionAgentECSMainDlg::OnBnClickedDownstreamInlineOffBtn)
	ON_BN_CLICKED(IDC_AUTO_RECIPE_ON_BTN, &CVisionAgentECSMainDlg::OnBnClickedAutoRecipeOnBtn)
	ON_BN_CLICKED(IDC_AUTO_RECIPE_OFF_BTN, &CVisionAgentECSMainDlg::OnBnClickedAutoRecipeOffBtn)
	ON_BN_CLICKED(IDC_ALARM_MANAGEMENT_WARNING_SET_BTN, &CVisionAgentECSMainDlg::OnBnClickedAlarmManagementWarningSetBtn)
	ON_BN_CLICKED(IDC_ALARM_MANAGEMENT_RESET_BTN, &CVisionAgentECSMainDlg::OnBnClickedAlarmManagementResetBtn)
	ON_BN_CLICKED(IDC_CIM_MODE_OFF_BTN, &CVisionAgentECSMainDlg::OnBnClickedCimModeOffBtn)
	ON_BN_CLICKED(IDC_OPERATOR_CALL_BTN, &CVisionAgentECSMainDlg::OnBnClickedOperatorCallBtn)
	ON_BN_CLICKED(IDC_AUTO_CASSETTE_VCR_ON_BTN, &CVisionAgentECSMainDlg::OnBnClickedAutoCassetteVcrOnBtn)
	ON_BN_CLICKED(IDC_AUTO_CASSETTE_VCR_OFF_BTN, &CVisionAgentECSMainDlg::OnBnClickedAutoCassetteVcrOffBtn)
	ON_BN_CLICKED(IDC_AUTO_CASSETTE_VCR_KEY_IN_BTN, &CVisionAgentECSMainDlg::OnBnClickedAutoCassetteVcrKeyInBtn)
	ON_BN_CLICKED(IDC_AUTO_CASSETTE_VCR_SKIP_BTN, &CVisionAgentECSMainDlg::OnBnClickedAutoCassetteVcrSkipBtn)
	ON_BN_CLICKED(IDC_BTN_MODULE_WINDOW_OPEN, &CVisionAgentECSMainDlg::OnBnClickedBtnModuleWindowOpen)

	ON_CONTROL_RANGE(BN_CLICKED, IDC_MACHINE_MANAGEMENT_CIMPC_COMMAND_REPLY_BTN1, IDC_MACHINE_MANAGEMENT_CIMPC_COMMAND_REPLY_BTN8, &CVisionAgentECSMainDlg::OnBnClickedCIMPCCommandReplyBtn)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN1, IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN25, &CVisionAgentECSMainDlg::OnBnClickedMachineEventBtn)


	ON_BN_CLICKED(IDC_BTN_JOB_PLUS, &CVisionAgentECSMainDlg::OnBnClickedBtnJobPlus)
	ON_BN_CLICKED(IDC_BTN_JOB_MINUS, &CVisionAgentECSMainDlg::OnBnClickedBtnJobMinus)
	ON_BN_CLICKED(IDC_MACHINE_MANAGEMENT_IDLE_BTN2, &CVisionAgentECSMainDlg::OnBnClickedMachineManagementIdleBtn2)
	ON_BN_CLICKED(IDC_MACHINE_MANAGEMENT_IDLE_BTN3, &CVisionAgentECSMainDlg::OnBnClickedMachineManagementIdleBtn3)
END_MESSAGE_MAP()


// CVisionAgentECSMainDlg ¸Þ½ÃÁö Ã³¸®±âÀÔ´Ï´Ù.



void CVisionAgentECSMainDlg::RecalcLayout()
{
	CRect	rect, rcClient, rcTab;
	GetClientRect(&rcClient);
	rcTab = rcClient;
	rcTab.DeflateRect(5, 5, 5, 70);
	rect = rcTab;
	rect.DeflateRect(5, 50, 5, 5);


}

BOOL CVisionAgentECSMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ¿©±â¿¡ Ãß°¡ ÃÊ±âÈ­ ÀÛ¾÷À» Ãß°¡ÇÕ´Ï´Ù.
	pCimModule = &Devs::CimMotion;


	m_BtnCimOn.SubclassDlgItem(IDC_CIM_MODE_ON_BTN, this);
	m_BtnCimOn.SetColor(BLACK, LLTGRAY);
	m_BtnCimOff.SubclassDlgItem(IDC_CIM_MODE_OFF_BTN, this);
	m_BtnCimOff.SetColor(BLACK, LLTGRAY);




	m_BtnAutoRecipeOn.SubclassDlgItem(IDC_AUTO_RECIPE_ON_BTN, this);
	m_BtnAutoRecipeOn.SetColor(BLACK, LLTGRAY);
	m_BtnAutoRecipeOff.SubclassDlgItem(IDC_AUTO_RECIPE_OFF_BTN, this);
	m_BtnAutoRecipeOff.SetColor(BLACK, LLTGRAY);


	m_BtnRun.SubclassDlgItem(IDC_MACHINE_MANAGEMENT_RUN_BTN, this);
	m_BtnRun.SetColor(BLACK, LLTGRAY);
	m_BtnIdle.SubclassDlgItem(IDC_MACHINE_MANAGEMENT_IDLE_BTN, this);
	m_BtnIdle.SetColor(BLACK, LLTGRAY);
	m_BtnPause.SubclassDlgItem(IDC_MACHINE_MANAGEMENT_PAUSE_BTN, this);
	m_BtnPause.SetColor(BLACK, LLTGRAY);
	m_BtnPM.SubclassDlgItem(IDC_MACHINE_MANAGEMENT_PM_BTN, this);
	m_BtnPM.SetColor(BLACK, LLTGRAY);
	m_BtnBM.SubclassDlgItem(IDC_MACHINE_MANAGEMENT_BM_BTN, this);
	m_BtnBM.SetColor(BLACK, LLTGRAY);

	m_BtnUpstreamInlineOn.SubclassDlgItem(IDC_UPSTREAM_INLINE_ON_BTN, this);
	m_BtnUpstreamInlineOn.SetColor(BLACK, LLTGRAY);
	m_BtnUpstreamInlineOff.SubclassDlgItem(IDC_UPSTREAM_INLINE_OFF_BTN, this);
	m_BtnUpstreamInlineOff.SetColor(BLACK, LLTGRAY);

	m_BtnDownstreamInlineOn.SubclassDlgItem(IDC_DOWNSTREAM_INLINE_ON_BTN, this);
	m_BtnDownstreamInlineOn.SetColor(BLACK, LLTGRAY);
	m_BtnDownstreamInlineOff.SubclassDlgItem(IDC_DOWNSTREAM_INLINE_OFF_BTN, this);
	m_BtnDownstreamInlineOff.SetColor(BLACK, LLTGRAY);


	m_BtnCimStatus.SubclassDlgItem(IDC_CIM_MODE_ALIVE_BTN, this);
	m_BtnCimStatus.SetColor(BLACK, LLTGRAY);

	m_BtnCimPCOn.SubclassDlgItem(IDC_CIM_PC_MODE_ON_BTN, this);
	m_BtnCimPCOn.SetColor(BLACK, LLTGRAY);


	m_BtnCassetteVCROn.SubclassDlgItem(IDC_AUTO_CASSETTE_VCR_ON_BTN, this);
	m_BtnCassetteVCROn.SetColor(BLACK, LLTGRAY);
	m_BtnCassetteVCROff.SubclassDlgItem(IDC_AUTO_CASSETTE_VCR_OFF_BTN, this);
	m_BtnCassetteVCROff.SetColor(BLACK, LLTGRAY);
	m_BtnCassetteVCRKeyIn.SubclassDlgItem(IDC_AUTO_CASSETTE_VCR_KEY_IN_BTN, this);
	m_BtnCassetteVCRKeyIn.SetColor(BLACK, LLTGRAY);
	m_BtnCassetteVCRSkip.SubclassDlgItem(IDC_AUTO_CASSETTE_VCR_SKIP_BTN, this);
	m_BtnCassetteVCRSkip.SetColor(BLACK, LLTGRAY);

#if 0
	m_BtnFrameVCROn.SubclassDlgItem(IDC_AUTO_FRAME_VCR_ON_BTN, this);
	m_BtnFrameVCROn.SetColor(BLACK, LLTGRAY);
	m_BtnFrameVCROff.SubclassDlgItem(IDC_AUTO_FRAME_VCR_OFF_BTN, this);
	m_BtnFrameVCROff.SetColor(BLACK, LLTGRAY);
	m_BtnFrameVCRKeyIn.SubclassDlgItem(IDC_AUTO_FRAME_VCR_KEY_IN_BTN, this);
	m_BtnFrameVCRKeyIn.SetColor(BLACK, LLTGRAY);
	m_BtnFrameVCRSkip.SubclassDlgItem(IDC_AUTO_FRAME_VCR_SKIP_BTN, this);
	m_BtnFrameVCRSkip.SetColor(BLACK, LLTGRAY);
	m_BtnFrameVCRNomal.SubclassDlgItem(IDC_AUTO_FRAME_VCR_NOMAL_BTN, this);
	m_BtnFrameVCRNomal.SetColor(BLACK, LLTGRAY);

	m_BtnMaskVCROn.SubclassDlgItem(IDC_AUTO_MASK_VCR_ON_BTN, this);
	m_BtnMaskVCROn.SetColor(BLACK, LLTGRAY);
	m_BtnMaskVCROff.SubclassDlgItem(IDC_AUTO_MASK_VCR_OFF_BTN, this);
	m_BtnMaskVCROff.SetColor(BLACK, LLTGRAY);
	m_BtnMaskVCRKeyIn.SubclassDlgItem(IDC_AUTO_MASK_VCR_KEY_IN_BTN, this);
	m_BtnMaskVCRKeyIn.SetColor(BLACK, LLTGRAY);
	m_BtnMaskVCRSkip.SubclassDlgItem(IDC_AUTO_MASK_VCR_SKIP_BTN, this);
	m_BtnMaskVCRSkip.SetColor(BLACK, LLTGRAY);
	m_BtnMaskVCRNomal.SubclassDlgItem(IDC_AUTO_MASK_VCR_NOMAL_BTN, this);
	m_BtnMaskVCRNomal.SetColor(BLACK, LLTGRAY);

#endif
	m_BtnOperatorCall.SubclassDlgItem(IDC_OPERATOR_CALL_BTN, this);
	m_BtnOperatorCall.SetColor(BLACK, LLTGRAY);
	
	

	m_CimMessageID[0].SubclassDlgItem(IDC_CIM_MESSAGE_ID_EDIT1, this);
	m_CimMessageID[1].SubclassDlgItem(IDC_CIM_MESSAGE_ID_EDIT2, this);
	m_CimMessageID[2].SubclassDlgItem(IDC_CIM_MESSAGE_ID_EDIT3, this);
	m_CimMessageID[3].SubclassDlgItem(IDC_CIM_MESSAGE_ID_EDIT4, this);
	m_CimMessageID[4].SubclassDlgItem(IDC_CIM_MESSAGE_ID_EDIT5, this);
	m_CimMessageDate[0].SubclassDlgItem(IDC_CIM_MESSAGE_TIME_EDIT1, this);
	m_CimMessageDate[1].SubclassDlgItem(IDC_CIM_MESSAGE_TIME_EDIT2, this);
	m_CimMessageDate[2].SubclassDlgItem(IDC_CIM_MESSAGE_TIME_EDIT3, this);
	m_CimMessageDate[3].SubclassDlgItem(IDC_CIM_MESSAGE_TIME_EDIT4, this);
	m_CimMessageDate[4].SubclassDlgItem(IDC_CIM_MESSAGE_TIME_EDIT5, this);
	m_CimMessage[0].SubclassDlgItem(IDC_CIM_MESSAGE_MESSAGE_EDIT1, this);
	m_CimMessage[1].SubclassDlgItem(IDC_CIM_MESSAGE_MESSAGE_EDIT2, this);
	m_CimMessage[2].SubclassDlgItem(IDC_CIM_MESSAGE_MESSAGE_EDIT3, this);
	m_CimMessage[3].SubclassDlgItem(IDC_CIM_MESSAGE_MESSAGE_EDIT4, this);
	m_CimMessage[4].SubclassDlgItem(IDC_CIM_MESSAGE_MESSAGE_EDIT5, this);


	m_BtnCimPCCommand[0].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_CIMPC_COMMAND_BTN1, this);
	m_BtnCimPCCommand[1].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_CIMPC_COMMAND_BTN2, this);
	m_BtnCimPCCommand[2].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_CIMPC_COMMAND_BTN3, this);
	m_BtnCimPCCommand[3].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_CIMPC_COMMAND_BTN4, this);
	m_BtnCimPCCommand[4].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_CIMPC_COMMAND_BTN5, this);
	m_BtnCimPCCommand[5].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_CIMPC_COMMAND_BTN6, this);
	m_BtnCimPCCommand[6].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_CIMPC_COMMAND_BTN7, this);
	m_BtnCimPCCommand[7].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_CIMPC_COMMAND_BTN8, this);

	m_BtnCimPCCommandReply[0].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_CIMPC_COMMAND_REPLY_BTN1, this);
	m_BtnCimPCCommandReply[1].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_CIMPC_COMMAND_REPLY_BTN2, this);
	m_BtnCimPCCommandReply[2].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_CIMPC_COMMAND_REPLY_BTN3, this);
	m_BtnCimPCCommandReply[3].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_CIMPC_COMMAND_REPLY_BTN4, this);
	m_BtnCimPCCommandReply[4].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_CIMPC_COMMAND_REPLY_BTN5, this);
	m_BtnCimPCCommandReply[5].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_CIMPC_COMMAND_REPLY_BTN6, this);
	m_BtnCimPCCommandReply[6].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_CIMPC_COMMAND_REPLY_BTN7, this);
	m_BtnCimPCCommandReply[7].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_CIMPC_COMMAND_REPLY_BTN8, this);


	m_BtnMachineEvent[0].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN1, this);
	m_BtnMachineEvent[1].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN2, this);
	m_BtnMachineEvent[2].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN3, this);
	m_BtnMachineEvent[3].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN4, this);
	m_BtnMachineEvent[4].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN5, this);
	m_BtnMachineEvent[5].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN6, this);
	m_BtnMachineEvent[6].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN7, this);
	m_BtnMachineEvent[7].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN8, this);
	m_BtnMachineEvent[8].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN9, this);
	m_BtnMachineEvent[9].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN10, this);
	m_BtnMachineEvent[10].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN11, this);
	m_BtnMachineEvent[11].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN12, this);
	m_BtnMachineEvent[12].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN13, this);
	m_BtnMachineEvent[13].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN14, this);
	m_BtnMachineEvent[14].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN15, this);
	m_BtnMachineEvent[15].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN16, this);
	m_BtnMachineEvent[16].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN17, this);
	m_BtnMachineEvent[17].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN18, this);
	m_BtnMachineEvent[18].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN19, this);
	m_BtnMachineEvent[19].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN20, this);
	m_BtnMachineEvent[20].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN21, this);
	m_BtnMachineEvent[21].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN22, this);
	m_BtnMachineEvent[22].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN23, this);
	m_BtnMachineEvent[23].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN24, this);
	m_BtnMachineEvent[24].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN25, this);


	m_BtnMachineEventReply[0].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_REPLY_BTN1, this);
	m_BtnMachineEventReply[1].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_REPLY_BTN2, this);
	m_BtnMachineEventReply[2].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_REPLY_BTN3, this);
	m_BtnMachineEventReply[3].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_REPLY_BTN4, this);
	m_BtnMachineEventReply[4].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_REPLY_BTN5, this);
	m_BtnMachineEventReply[5].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_REPLY_BTN6, this);
	m_BtnMachineEventReply[6].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_REPLY_BTN7, this);
	m_BtnMachineEventReply[7].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_REPLY_BTN8, this);
	m_BtnMachineEventReply[8].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_REPLY_BTN9, this);
	m_BtnMachineEventReply[9].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_REPLY_BTN10, this);
	m_BtnMachineEventReply[10].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_REPLY_BTN11, this);
	m_BtnMachineEventReply[11].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_REPLY_BTN12, this);
	m_BtnMachineEventReply[12].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_REPLY_BTN13, this);
	m_BtnMachineEventReply[13].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_REPLY_BTN14, this);
	m_BtnMachineEventReply[14].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_REPLY_BTN15, this);
	m_BtnMachineEventReply[15].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_REPLY_BTN16, this);
	m_BtnMachineEventReply[16].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_REPLY_BTN17, this);
	m_BtnMachineEventReply[17].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_REPLY_BTN18, this);
	m_BtnMachineEventReply[18].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_REPLY_BTN19, this);
	m_BtnMachineEventReply[19].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_REPLY_BTN20, this);
	m_BtnMachineEventReply[20].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_REPLY_BTN21, this);
	m_BtnMachineEventReply[21].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_REPLY_BTN22, this);
	m_BtnMachineEventReply[22].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_REPLY_BTN23, this);
	m_BtnMachineEventReply[23].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_REPLY_BTN24, this);
	m_BtnMachineEventReply[24].SubclassDlgItem(IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_REPLY_BTN25, this);

	m_ErrorCodeCombo.SubclassDlgItem(IDC_ALARM_MANAGEMENT_ERROR_CODE_COMBO, this);
	m_ErrorMessage.SubclassDlgItem(IDC_ALARM_MANAGEMENT_ERROR_EDIT, this);
	m_ErrorID.SubclassDlgItem(IDC_ALARM_MANAGEMENT_ERROR_ID_EDIT, this);
	m_ProductJobCount.SubclassDlgItem(IDC_PRODUCT_JOB_COUNT_EDIT, this);
	m_DummyJobCount.SubclassDlgItem(IDC_DUMMY_JOB_COUNT_EDIT, this);


	m_ErrorCodeCombo.ResetContent();
	m_ErrorCodeCombo.AddString(_T("0.Danger For Human"));
	m_ErrorCodeCombo.AddString(_T("1.Machine Error"));
	m_ErrorCodeCombo.AddString(_T("2. Param O/F (Pro Error)"));
	m_ErrorCodeCombo.AddString(_T("3. Param O/F (Machine)"));
	m_ErrorCodeCombo.AddString(_T("4. Cannot Recover Trouble"));
	m_ErrorCodeCombo.AddString(_T("5. Machine Status Warning"));
	m_ErrorCodeCombo.AddString(_T("6. Process Reached"));
	m_ErrorCodeCombo.AddString(_T("7. CIM PC Caused"));
	m_ErrorCodeCombo.SetCurSel(0);


	CString szMsg;
	CFile file;
	szMsg.Format(_T("%d"), CimInfo::m_T1Timer);
	GetDlgItem(IDC_TIMEOUT_MANAGEMENT_T1_EDIT)->SetWindowText(szMsg);

	szMsg.Format(_T("%d"), CimInfo::m_T2Timer);
	GetDlgItem(IDC_TIMEOUT_MANAGEMENT_T2_EDIT)->SetWindowText(szMsg);


	szMsg.Format(_T("%d"), CimInfo::m_T3Timer);
	GetDlgItem(IDC_TIMEOUT_MANAGEMENT_T3_EDIT)->SetWindowText(szMsg);




	return TRUE;  // return TRUE unless you set the focus to a control
				  // ¿¹¿Ü: OCX ¼Ó¼º ÆäÀÌÁö´Â FALSE¸¦ ¹ÝÈ¯ÇØ¾ß ÇÕ´Ï´Ù.
}


void CVisionAgentECSMainDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ¿©±â¿¡ ¸Þ½ÃÁö Ã³¸®±â ÄÚµå¸¦ Ãß°¡ ¹×/¶Ç´Â ±âº»°ªÀ» È£ÃâÇÕ´Ï´Ù.

	CDialogEx::OnTimer(nIDEvent);
	CString szMsg, szMsgTmp;


	if (nIDEvent == 1)
	{

		szMsg.Format(_T("%d"), SharedInfo::m_ProductJobCount);
		m_ProductJobCount.SetWindowText(szMsg);
		if (CimInfo::m_CimMode == 2)
		{
			m_BtnCimOn.SetColor(BLACK, GREEN);
			m_BtnCimOff.SetColor(BLACK, LLTGRAY);
		}
		else if (CimInfo::m_CimMode == 1)
		{
			m_BtnCimOff.SetColor(BLACK, RED);
			m_BtnCimOn.SetColor(BLACK, LLTGRAY);
		}
		if (CimInfo::m_LBLTM.MachineStatus_MachineHeartBeatSignalBit == TRUE)
		{
			m_BtnCimStatus.SetColor(BLACK, GREEN);

		}
		else if (CimInfo::m_LBLTM.MachineStatus_MachineHeartBeatSignalBit == FALSE)
		{

			m_BtnCimStatus.SetColor(BLACK, LLTGRAY);
		}


		if (CimInfo::m_LBMTL.CIMPCStatus_NoneProcessGlassSignal == TRUE)
		{
			m_BtnCimPCOn.SetColor(BLACK, GREEN);
			
		}
		else if (CimInfo::m_LBMTL.CIMPCStatus_NoneProcessGlassSignal == FALSE)
		{

			m_BtnCimPCOn.SetColor(BLACK, LLTGRAY);
		}
		if (CimInfo::m_LBLTM.MachineStatus_UpstreamLinlineModeBit == TRUE)
		{
			m_BtnUpstreamInlineOn.SetColor(BLACK, GREEN);
			m_BtnUpstreamInlineOff.SetColor(BLACK, LLTGRAY);
		}
		else if (CimInfo::m_LBLTM.MachineStatus_UpstreamLinlineModeBit == FALSE)
		{
			m_BtnUpstreamInlineOn.SetColor(BLACK, LLTGRAY);
			m_BtnUpstreamInlineOff.SetColor(BLACK, GREEN);
		}

		if (CimInfo::m_LBLTM.MachineStatus_DownstreamInlineModeBit == TRUE)
		{
			m_BtnDownstreamInlineOn.SetColor(BLACK, GREEN);
			m_BtnDownstreamInlineOff.SetColor(BLACK, LLTGRAY);
		}
		else if (CimInfo::m_LBLTM.MachineStatus_DownstreamInlineModeBit == FALSE)
		{
			m_BtnDownstreamInlineOn.SetColor(BLACK, LLTGRAY);
			m_BtnDownstreamInlineOff.SetColor(BLACK, GREEN);
		}
#if 0
		if (CimInfo::m_LBLTM.bMachineStatusVCREnableMode == TRUE)
		{
			m_BtnCassetteVCROn.SetColor(BLACK, GREEN);
			m_BtnCassetteVCROff.SetColor(BLACK, LLTGRAY);
		}
		else
		{
			m_BtnCassetteVCROn.SetColor(BLACK, LLTGRAY);
			m_BtnCassetteVCROff.SetColor(BLACK, GREEN);
		}

		if (SharedInfo::m_FrameVCRReadFailOperationMode == VCR_KEY_IN)
		{
			m_BtnCassetteVCRKeyIn.SetColor(BLACK, GREEN);
			m_BtnCassetteVCRSkip.SetColor(BLACK, LLTGRAY);
		}
		else if (SharedInfo::m_FrameVCRReadFailOperationMode == VCR_SKIP)
		{
			m_BtnCassetteVCRKeyIn.SetColor(BLACK, LLTGRAY);
			m_BtnCassetteVCRSkip.SetColor(BLACK, GREEN);
		}
#endif

		if (SharedInfo::m_AutoRecipe == TRUE)
		{
			m_BtnAutoRecipeOn.SetColor(BLACK, GREEN);
			m_BtnAutoRecipeOff.SetColor(BLACK, LLTGRAY);
		} 
		
		if (SharedInfo::m_AutoRecipe == FALSE)
		{
			m_BtnAutoRecipeOn.SetColor(BLACK, LLTGRAY);
			m_BtnAutoRecipeOff.SetColor(BLACK, GREEN);
		}
		
		//MachineState
		if (m_nPrevMachineState != CimInfo::m_MachineState && CimInfo::m_MachineState == eMACHINE_STATUS_RUN)
		{
			m_BtnRun.SetColor(BLACK, GREEN);
			m_BtnIdle.SetColor(BLACK, LLTGRAY);
			m_BtnPause.SetColor(BLACK, LLTGRAY);
			m_BtnPM.SetColor(BLACK, LLTGRAY);
			m_BtnBM.SetColor(BLACK, LLTGRAY);
		}
		 if (m_nPrevMachineState != CimInfo::m_MachineState && CimInfo::m_MachineState == eMACHINE_STATUS_IDLE)
		{
			m_BtnRun.SetColor(BLACK, LLTGRAY);
			m_BtnIdle.SetColor(BLACK, GREEN);
			m_BtnPause.SetColor(BLACK, LLTGRAY);
			m_BtnPM.SetColor(BLACK, LLTGRAY);
			m_BtnBM.SetColor(BLACK, LLTGRAY);
		}
		if (m_nPrevMachineState != CimInfo::m_MachineState && CimInfo::m_MachineState == eMACHINE_STATUS_PAUSE)
		{
			m_BtnRun.SetColor(BLACK, LLTGRAY);
			m_BtnIdle.SetColor(BLACK, LLTGRAY);
			m_BtnPause.SetColor(BLACK, GREEN);
			m_BtnPM.SetColor(BLACK, LLTGRAY);
			m_BtnBM.SetColor(BLACK, LLTGRAY);
		}
		if (m_nPrevMachineState != CimInfo::m_MachineState && CimInfo::m_MachineState == eMACHINE_STATUS_BM)
		{
			m_BtnRun.SetColor(BLACK, LLTGRAY);
			m_BtnIdle.SetColor(BLACK, LLTGRAY);
			m_BtnPause.SetColor(BLACK, LLTGRAY);
			m_BtnPM.SetColor(BLACK, LLTGRAY);
			m_BtnBM.SetColor(BLACK, GREEN);
		}
		if (m_nPrevMachineState != CimInfo::m_MachineState && CimInfo::m_MachineState == eMACHINE_STATUS_PM)
		{
			m_BtnRun.SetColor(BLACK, LLTGRAY);
			m_BtnIdle.SetColor(BLACK, LLTGRAY);
			m_BtnPause.SetColor(BLACK, LLTGRAY);
			m_BtnPM.SetColor(BLACK, GREEN);
			m_BtnBM.SetColor(BLACK, LLTGRAY);
		}
		m_nPrevMachineState = CimInfo::m_MachineState;
	}
	for (int i = 0; i < 5; i++)
	{
		szMsg.Format(_T("%d"), CimInfo::CIMMessage[i].CimMessageID);
		m_CimMessageID[i].SetWindowText(szMsg);

		szMsg.Format(_T("%S"), (char*)CimInfo::CIMMessage[i].CimMessage);
		m_CimMessage[i].SetWindowText(szMsg);

		m_CimMessageDate[i].SetWindowText(CimInfo::CIMMessage[i].CiMReceiveDate);
	}

	szMsg.Format(_T("%d"), SharedInfo::m_ProductJobCount);
	m_ProductJobCount.SetWindowText(szMsg);
	szMsg.Format(_T("%d"), SharedInfo::m_DummyJobCount);
	m_DummyJobCount.SetWindowText(szMsg);


	if (CimInfo::m_LBMTL.CIMPCCommand_CIMModeChangeCommandSend == TRUE)
		m_BtnCimPCCommand[0].SetColor(BLACK, GREEN);
	else
		m_BtnCimPCCommand[0].SetColor(BLACK, LLTGRAY);

	if (CimInfo::m_LBMTL.CIMPCCommand_RecipeRegisterCheckCommandSend == TRUE)
		m_BtnCimPCCommand[1].SetColor(BLACK, GREEN);
	else
		m_BtnCimPCCommand[1].SetColor(BLACK, LLTGRAY);

	if (CimInfo::m_LBMTL.CIMPCCommand_RecipeParameterRequest == TRUE)
		m_BtnCimPCCommand[2].SetColor(BLACK, GREEN);
	else
		m_BtnCimPCCommand[2].SetColor(BLACK, LLTGRAY);

	if (CimInfo::m_LBMTL.CIMPCCommand_CIMMessageSetCommandSend == TRUE)
		m_BtnCimPCCommand[3].SetColor(BLACK, GREEN);
	else
		m_BtnCimPCCommand[3].SetColor(BLACK, LLTGRAY);

	if (CimInfo::m_LBMTL.CIMPCCommand_CIMMessageClearCommandSend == TRUE)
		m_BtnCimPCCommand[4].SetColor(BLACK, GREEN);
	else
		m_BtnCimPCCommand[4].SetColor(BLACK, LLTGRAY);

	if (CimInfo::m_LBMTL.CIMPCCommand_DateTimeSetCommandSend == TRUE)
		m_BtnCimPCCommand[5].SetColor(BLACK, GREEN);
	else
		m_BtnCimPCCommand[5].SetColor(BLACK, LLTGRAY);

#if 0
	if (CimInfo::m_LBMTL.bCIMPCCommandVCRModeChangeCommand == TRUE)
		m_BtnCimPCCommand[6].SetColor(BLACK, GREEN);
	else
		m_BtnCimPCCommand[6].SetColor(BLACK, LLTGRAY);
#
	if (CimInfo::m_LBMTL.bCIMPCCommandMaterialGroupDataDownload == TRUE)
		m_BtnCimPCCommand[7].SetColor(BLACK, GREEN);
	else
		m_BtnCimPCCommand[7].SetColor(BLACK, LLTGRAY);
#endif


	if (CimInfo::m_LBLTM.CIMPCCommandReply_CIMModeChangeCommandSendReply == TRUE)
		m_BtnCimPCCommandReply[0].SetColor(BLACK, GREEN);
	else
		m_BtnCimPCCommandReply[0].SetColor(BLACK, LLTGRAY);
	
	if (CimInfo::m_LBLTM.CIMPCCommandReply_RecipeRegisterCheckCommandSendReply == TRUE)
		m_BtnCimPCCommandReply[1].SetColor(BLACK, GREEN);
	else
		m_BtnCimPCCommandReply[1].SetColor(BLACK, LLTGRAY);
	
	if (CimInfo::m_LBLTM.CIMPCCommandReply_RecipeKeyParameterRequestReply == TRUE)
		m_BtnCimPCCommandReply[2].SetColor(BLACK, GREEN);
	else
		m_BtnCimPCCommandReply[2].SetColor(BLACK, LLTGRAY);
	
	if (CimInfo::m_LBLTM.CIMPCCommandReply_CIMMessageSetCommandSendReply == TRUE)
		m_BtnCimPCCommandReply[3].SetColor(BLACK, GREEN);
	else
		m_BtnCimPCCommandReply[3].SetColor(BLACK, LLTGRAY);
	
	if (CimInfo::m_LBLTM.CIMPCCommandReply_CIMMessageClearCommandSendReply == TRUE)
		m_BtnCimPCCommandReply[4].SetColor(BLACK, GREEN);
	else
		m_BtnCimPCCommandReply[4].SetColor(BLACK, LLTGRAY);
	
	if (CimInfo::m_LBLTM.CIMPCCommandReply_DateTimeSetCommandSendReply == TRUE)
		m_BtnCimPCCommandReply[5].SetColor(BLACK, GREEN);
	else
		m_BtnCimPCCommandReply[5].SetColor(BLACK, LLTGRAY);
#if 0
	if (CimInfo::m_LBLTM.bCIMPCCommandReplyVCRModeChangeCommandReply == TRUE)
		m_BtnCimPCCommandReply[6].SetColor(BLACK, GREEN);
	else
		m_BtnCimPCCommandReply[6].SetColor(BLACK, LLTGRAY);
	
	if (CimInfo::m_LBLTM.bCIMPCCommandReplyMaterialGroupDataDownloadReply)
		m_BtnCimPCCommandReply[7].SetColor(BLACK, GREEN);
	else
		m_BtnCimPCCommandReply[7].SetColor(BLACK, LLTGRAY);
#endif

	if (CimInfo::m_LBLTM.MachineMaskEvent_MaskReceivedJobReport)
		m_BtnMachineEvent[0].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEvent[0].SetColor(BLACK, LLTGRAY);

	if (CimInfo::m_LBLTM.MachineMaskEvent_MaskSentOutJobReport_1)
		m_BtnMachineEvent[1].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEvent[1].SetColor(BLACK, LLTGRAY);

	if (CimInfo::m_LBLTM.MachineMaskEvent_MaskStoredJobReport)
		m_BtnMachineEvent[2].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEvent[2].SetColor(BLACK, LLTGRAY);

	if (CimInfo::m_LBLTM.MachineMaskEvent_MaskFetchedOutJobReport)
		m_BtnMachineEvent[3].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEvent[3].SetColor(BLACK, LLTGRAY);

	if (CimInfo::m_LBLTM.MachineMaskEvent_MaskProcessStartReport)
		m_BtnMachineEvent[4].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEvent[4].SetColor(BLACK, LLTGRAY);

	if (CimInfo::m_LBLTM.MachineMaskEvent_MaskProcessEndReport)
		m_BtnMachineEvent[5].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEvent[5].SetColor(BLACK, LLTGRAY);

	if (CimInfo::m_LBLTM.MachineEvent_MachineStatusChangeReport)
		m_BtnMachineEvent[6].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEvent[6].SetColor(BLACK, LLTGRAY);
#if 0
	if (CimInfo::m_LBLTM.bMachineEventAlarmStateChangeReport)
		m_BtnMachineEvent[7].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEvent[7].SetColor(BLACK, LLTGRAY);
#endif

	if (CimInfo::m_LBLTM.MachineMaskEvent_MaskJobDataRequest)
		m_BtnMachineEvent[8].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEvent[8].SetColor(BLACK, LLTGRAY);

	if (CimInfo::m_LBLTM.MachineMaskEvent_MaskJobDataChangeReport)
		m_BtnMachineEvent[9].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEvent[9].SetColor(BLACK, LLTGRAY);
#if 0
	if (CimInfo::m_LBLTM.bMachineEventProcessDataReport)
		m_BtnMachineEvent[10].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEvent[10].SetColor(BLACK, LLTGRAY);
#endif

	if (CimInfo::m_LBLTM.MachineEvent_CurrentRecipeNumberChangeReport)
		m_BtnMachineEvent[11].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEvent[11].SetColor(BLACK, LLTGRAY);
#if 0
	if (CimInfo::m_LBLTM.bMachineEventRecipeListChangeReport)
		m_BtnMachineEvent[12].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEvent[12].SetColor(BLACK, LLTGRAY);
#endif
	if (CimInfo::m_LBLTM.CIMPCCommandReply_RecipeParameterDataDownloadSendReply)
		m_BtnMachineEvent[13].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEvent[13].SetColor(BLACK, LLTGRAY);

	if (CimInfo::m_LBLTM.MachineEvent_CIMMessageConfirmReport)
		m_BtnMachineEvent[14].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEvent[14].SetColor(BLACK, LLTGRAY);
#if 0
	if (CimInfo::m_LBLTM.bMachineEventVCREventReport)
		m_BtnMachineEvent[15].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEvent[15].SetColor(BLACK, LLTGRAY);

	if (CimInfo::m_LBLTM.bMachineEventVCRModeChangeReport)
		m_BtnMachineEvent[16].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEvent[16].SetColor(BLACK, LLTGRAY);
#endif
	if (CimInfo::m_LBLTM.MachineEvent_JobJudgeResultReport)
		m_BtnMachineEvent[17].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEvent[17].SetColor(BLACK, LLTGRAY);

	if (CimInfo::m_LBLTM.MachineMaterialEvent_MaterialStatusChangeReport)
		m_BtnMachineEvent[18].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEvent[18].SetColor(BLACK, LLTGRAY);

	if (CimInfo::m_LBLTM.MachineMaterialEvent_MaterialCountChangeReport)
		m_BtnMachineEvent[19].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEvent[19].SetColor(BLACK, LLTGRAY);

	if (CimInfo::m_LBLTM.MachineMaterialEvent_SheetMoveInReport)
		m_BtnMachineEvent[20].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEvent[20].SetColor(BLACK, LLTGRAY);

	if (CimInfo::m_LBLTM.MachineMaterialEvent_SheetMoveOutReport)
		m_BtnMachineEvent[21].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEvent[21].SetColor(BLACK, LLTGRAY);

	if (CimInfo::m_LBLTM.MachineMaterialEvent_MaterialSheetDataUpdateReport)
		m_BtnMachineEvent[22].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEvent[22].SetColor(BLACK, LLTGRAY);

	if (CimInfo::m_LBLTM.MachineMaterialEvent_MaterialSheetDataDownloadRequest)
		m_BtnMachineEvent[23].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEvent[23].SetColor(BLACK, LLTGRAY);
#if 0
	if (CimInfo::m_LBLTM.bMachineEventSheetDataRemovedReport)
		m_BtnMachineEvent[24].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEvent[24].SetColor(BLACK, LLTGRAY);
#endif
	
	
	if (CimInfo::m_LBMTL.MachineMaskEventReply_MaskReceivedJobReportReply)
		m_BtnMachineEventReply[0].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEventReply[0].SetColor(BLACK, LLTGRAY);

	if (CimInfo::m_LBMTL.MachineMaskEventReply_MaskSentOutJobReportReply_1 == TRUE)
		m_BtnMachineEventReply[1].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEventReply[1].SetColor(BLACK, LLTGRAY);

	if (CimInfo::m_LBMTL.MachineMaskEventReply_MaskStoredJobReportReply)
		m_BtnMachineEventReply[2].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEventReply[2].SetColor(BLACK, LLTGRAY);

	if (CimInfo::m_LBMTL.MachineMaskEventReply_MaskFetchedOutJobReportReply == TRUE)
		m_BtnMachineEventReply[3].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEventReply[3].SetColor(BLACK, LLTGRAY);

	if (CimInfo::m_LBMTL.MachineMaskEventReply_MaskProcessStartReportReply)
		m_BtnMachineEventReply[4].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEventReply[4].SetColor(BLACK, LLTGRAY);

	if (CimInfo::m_LBMTL.MachineMaskEventReply_MaskProcessEndReportReply)
		m_BtnMachineEventReply[5].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEventReply[5].SetColor(BLACK, LLTGRAY);

	if (CimInfo::m_LBMTL.MachineEventReply_MachineStatusChangeReportReply)
		m_BtnMachineEventReply[6].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEventReply[6].SetColor(BLACK, LLTGRAY);
#if 0
	if (CimInfo::m_LBMTL.bMachineEventReplyAlarmStateChangeReportReply)
		m_BtnMachineEventReply[7].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEventReply[7].SetColor(BLACK, LLTGRAY);
#endif

	if (CimInfo::m_LBMTL.MachineMaskEventReply_MaskJobDataRequestReply)
		m_BtnMachineEventReply[8].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEventReply[8].SetColor(BLACK, LLTGRAY);

	if (CimInfo::m_LBMTL.MachineMaskEventReply_MaskJobDataChangeReportReply)
		m_BtnMachineEventReply[9].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEventReply[9].SetColor(BLACK, LLTGRAY);

#if 0
	if (CimInfo::m_LBMTL.MachineMaskEventReply_MaskReviewProcessEndReportReply)
		m_BtnMachineEventReply[10].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEventReply[10].SetColor(BLACK, LLTGRAY);
#endif
	if (CimInfo::m_LBMTL.MachineEventReply_CurrentRecipeNumberChangeReportReply	)
		m_BtnMachineEventReply[11].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEventReply[11].SetColor(BLACK, LLTGRAY);
#if 0
	if (CimInfo::m_LBMTL.bMachineEventReplyRecipeListChangeReportReply)
		m_BtnMachineEventReply[12].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEventReply[12].SetColor(BLACK, LLTGRAY);

	if (CimInfo::m_LBMTL.MachineEventReply_rerecbMachineEventReplyRecipeParameterDataChangeReportReply)
		m_BtnMachineEventReply[13].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEventReply[13].SetColor(BLACK, LLTGRAY);
#endif
	if (CimInfo::m_LBMTL.MachineEventReply_CIMMessageConfirmReportReply)
		m_BtnMachineEventReply[14].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEventReply[14].SetColor(BLACK, LLTGRAY);
#if 0
	if (CimInfo::m_LBMTL.bMachineEventReplyVCREventReportReply)
		m_BtnMachineEventReply[15].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEventReply[15].SetColor(BLACK, LLTGRAY);

	if (CimInfo::m_LBMTL.bMachineEventReplyVCRModeChangeReportReply)
		m_BtnMachineEventReply[16].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEventReply[16].SetColor(BLACK, LLTGRAY);
#endif
	if (CimInfo::m_LBMTL.MachineEventReply_JobJudgeResultReportReply)
		m_BtnMachineEventReply[17].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEventReply[17].SetColor(BLACK, LLTGRAY);

	if (CimInfo::m_LBMTL.MachineMaterialEventReply_MaterialStatusChangeReportReply)
		m_BtnMachineEventReply[18].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEventReply[18].SetColor(BLACK, LLTGRAY);

	if (CimInfo::m_LBMTL.MachineMaterialEventReply_MaterialCountChangeReportReply)
		m_BtnMachineEventReply[19].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEventReply[19].SetColor(BLACK, LLTGRAY);

	if (CimInfo::m_LBMTL.MachineMaterialEventReply_SheetMoveInReportReply)
		m_BtnMachineEventReply[20].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEventReply[20].SetColor(BLACK, LLTGRAY);

	if (CimInfo::m_LBMTL.MachineMaterialEventReply_SheetMoveOutReportReply)
		m_BtnMachineEventReply[21].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEventReply[21].SetColor(BLACK, LLTGRAY);

	if (CimInfo::m_LBMTL.MachineMaterialEventReply_MaterialSheetDataUpdateReportReply)
		m_BtnMachineEventReply[22].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEventReply[22].SetColor(BLACK, LLTGRAY);

	if (CimInfo::m_LBMTL.MachineMaterialEventReply_MaterialSheetDataDownloadRequestReply)
		m_BtnMachineEventReply[23].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEventReply[23].SetColor(BLACK, LLTGRAY);
#if 0
	if (CimInfo::m_LBMTL.bMachineEventReplySheetDataRemovedReportReply)
		m_BtnMachineEventReply[24].SetColor(BLACK, GREEN);
	else
		m_BtnMachineEventReply[24].SetColor(BLACK, LLTGRAY);
#endif


}

void CVisionAgentECSMainDlg::OnBnClickedCimModeOnBtn()
{
	CimInfo::m_CimMode = 2;
	Devs::CimMotion.SetCimModeOnOff(TRUE);
}

void CVisionAgentECSMainDlg::OnBnClickedCimModeOffBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CimInfo::m_CimMode = 1;
	Devs::CimMotion.SetCimModeOnOff(FALSE);
}

void CVisionAgentECSMainDlg::OnBnClickedMachineManagementRunBtn()
{

	Devs::CimMotion.SetMachineRun();
	Etc_Msg(_T("[Cim] Send : Machine Stauts Change Report"));
}


void CVisionAgentECSMainDlg::OnBnClickedMachineManagementIdleBtn()
{

	Devs::CimMotion.SetMachineIdle();
	Etc_Msg(_T("[Cim] Send : Machine Stauts Change Report"));
}


void CVisionAgentECSMainDlg::OnBnClickedMachineManagementPauseBtn()
{
	Devs::CimMotion.SetMachinePause();

	Etc_Msg(_T("[Cim] Send : Machine Stauts Change Report"));
}


void CVisionAgentECSMainDlg::OnBnClickedMachineManagementPmBtn()
{
	Devs::CimMotion.SetMachinePm();
	Etc_Msg(_T("[Cim] Send : Machine Stauts Change Report"));
}

void CVisionAgentECSMainDlg::OnBnClickedMachineManagementBmBtn()
{
	Devs::CimMotion.SetMachineBm();

	Etc_Msg(_T("[Cim] Send : Machine Stauts Change Report"));
}

void CVisionAgentECSMainDlg::OnBnClickedTimeoutManagementSetBtn()
{
	// TODO: ¿©±â¿¡ ÄÁÆ®·Ñ ¾Ë¸² Ã³¸®±â ÄÚµå¸¦ Ãß°¡ÇÕ´Ï´Ù.
	CString szMsg;
	CFile file;
	GetDlgItem(IDC_TIMEOUT_MANAGEMENT_T1_EDIT)->GetWindowText(szMsg);
	CimInfo::m_T1Timer = _ttoi(szMsg);

	GetDlgItem(IDC_TIMEOUT_MANAGEMENT_T2_EDIT)->GetWindowText(szMsg);
	CimInfo::m_T2Timer = _ttoi(szMsg);

	GetDlgItem(IDC_TIMEOUT_MANAGEMENT_T3_EDIT)->GetWindowText(szMsg);
	CimInfo::m_T3Timer = _ttoi(szMsg);
	Devs::CimMotion.SetT1TimeOut();

	GetDlgItem(IDC_TIMEOUT_MANAGEMENT_ALIVE_EDIT)->GetWindowText(szMsg);
	Devs::CimMotion.m_dAliveTimer = _ttoi(szMsg);
	Devs::CimMotion.SetAliveTimeOut();

	
}

void CVisionAgentECSMainDlg::OnBnClickedCimMessageConfirmBtn1()
{
	// TODO: ¿©±â¿¡ ÄÁÆ®·Ñ ¾Ë¸² Ã³¸®±â ÄÚµå¸¦ Ãß°¡ÇÕ´Ï´Ù.
	CIM_MESSAGE_CONFIRM_REPORT_BLOCK CimMessageConfirmReportBlock;

	//while (TRUE)
	//{
	//	if(Devs::CimMotion.IsT3TimeOut())
	//}
	WORD CimMessage[16];
	memset(CimMessage, 0x0, sizeof(CimMessage));
	if (!memcmp(SharedInfo::CIMMessage[0].CimMessage, CimMessage, sizeof(CimMessage)))
		return;
	SharedInfo::CimMessageConfirmReportBuffer[0].CIMMessageID = SharedInfo::CIMMessage[0].CimMessageID;
	SharedInfo::CimMessageConfirmReportBuffer[0].TouchPanelNumber = 1;
	Devs::CimMotion.ReportCimMessageConfrimBlock(SharedInfo::CimMessageConfirmReportBuffer[0]);
	for (int i = 0; i < 9; i++)
	{
		memcpy(&SharedInfo::CIMMessage[i], &SharedInfo::CIMMessage[i + 1], sizeof(SharedInfo::CIMMessage[i]));
	}
	memset(&SharedInfo::CIMMessage[9], 0x0, sizeof(SharedInfo::CIMMessage[9]));

	Etc_Msg(_T("[Cim] Send : Cim  Message Confrim Report1"));
	SharedInfo::CIMMessageBufferCnt++;
}


void CVisionAgentECSMainDlg::OnBnClickedCimMessageConfirmBtn2()
{
	// TODO: ¿©±â¿¡ ÄÁÆ®·Ñ ¾Ë¸² Ã³¸®±â ÄÚµå¸¦ Ãß°¡ÇÕ´Ï´Ù.
	WORD CimMessage[16];
	memset(CimMessage, 0x0, sizeof(CimMessage));
	if (!memcmp(SharedInfo::CIMMessage[1].CimMessage, CimMessage, sizeof(CimMessage)))
		return;
	SharedInfo::CimMessageConfirmReportBuffer[1].CIMMessageID = SharedInfo::CIMMessage[1].CimMessageID;
	SharedInfo::CimMessageConfirmReportBuffer[1].TouchPanelNumber = 1;
	Devs::CimMotion.ReportCimMessageConfrimBlock(SharedInfo::CimMessageConfirmReportBuffer[1]);
	for (int i = 1; i < 9; i++)
	{
		memcpy(&SharedInfo::CIMMessage[i], &SharedInfo::CIMMessage[i + 1], sizeof(SharedInfo::CIMMessage[i]));
	}
	memset(&SharedInfo::CIMMessage[9], 0x0, sizeof(SharedInfo::CIMMessage[9]));
	
	SharedInfo::CIMMessageBufferCnt++;
}


void CVisionAgentECSMainDlg::OnBnClickedCimMessageConfirmBtn3()
{
	// TODO: ¿©±â¿¡ ÄÁÆ®·Ñ ¾Ë¸² Ã³¸®±â ÄÚµå¸¦ Ãß°¡ÇÕ´Ï´Ù.
	WORD CimMessage[16];
	memset(CimMessage, 0x0, sizeof(CimMessage));
	if (!memcmp(SharedInfo::CIMMessage[2].CimMessage, CimMessage, sizeof(CimMessage)))
		return;
	SharedInfo::CimMessageConfirmReportBuffer[2].CIMMessageID = SharedInfo::CIMMessage[2].CimMessageID;
	SharedInfo::CimMessageConfirmReportBuffer[2].TouchPanelNumber = 1;
	Devs::CimMotion.ReportCimMessageConfrimBlock(SharedInfo::CimMessageConfirmReportBuffer[2]);
	CIM_MESSAGE_CONFIRM_REPORT_BLOCK CimMessageConfirmReportBlock;
	for (int i = 2; i < 9; i++)
	{
		memcpy(&SharedInfo::CIMMessage[i], &SharedInfo::CIMMessage[i + 1], sizeof(SharedInfo::CIMMessage[i]));
	}
	memset(&SharedInfo::CIMMessage[9], 0x0, sizeof(SharedInfo::CIMMessage[9]));
	SharedInfo::CIMMessageBufferCnt++;
}



void CVisionAgentECSMainDlg::OnBnClickedCimMessageConfirmBtn4()
{
	CIM_MESSAGE_CONFIRM_REPORT_BLOCK CimMessageConfirmReportBlock;
	WORD CimMessage[16];
	memset(CimMessage, 0x0, sizeof(CimMessage));
	if (!memcmp(SharedInfo::CIMMessage[3].CimMessage, CimMessage, sizeof(CimMessage)))
		return;
	SharedInfo::CimMessageConfirmReportBuffer[3].CIMMessageID = SharedInfo::CIMMessage[3].CimMessageID;
	SharedInfo::CimMessageConfirmReportBuffer[3].TouchPanelNumber = 1;
	Devs::CimMotion.ReportCimMessageConfrimBlock(SharedInfo::CimMessageConfirmReportBuffer[3]);
	for (int i = 3; i < 9; i++)
	{
		memcpy(&SharedInfo::CIMMessage[i], &SharedInfo::CIMMessage[i + 1], sizeof(SharedInfo::CIMMessage[i]));
	}
	memset(&SharedInfo::CIMMessage[9], 0x0, sizeof(SharedInfo::CIMMessage[9]));
	SharedInfo::CIMMessageBufferCnt++;
}


void CVisionAgentECSMainDlg::OnBnClickedCimMessageConfirmBtn5()
{
	// TODO: ¿©±â¿¡ ÄÁÆ®·Ñ ¾Ë¸² Ã³¸®±â ÄÚµå¸¦ Ãß°¡ÇÕ´Ï´Ù.
	CIM_MESSAGE_CONFIRM_REPORT_BLOCK CimMessageConfirmReportBlock;
	WORD CimMessage[16];
	memset(CimMessage, 0x0, sizeof(CimMessage));
	if (!memcmp(SharedInfo::CIMMessage[4].CimMessage, CimMessage, sizeof(CimMessage)))
		return;
	SharedInfo::CimMessageConfirmReportBuffer[4].CIMMessageID = SharedInfo::CIMMessage[4].CimMessageID;
	SharedInfo::CimMessageConfirmReportBuffer[4].TouchPanelNumber = 1;
	Devs::CimMotion.ReportCimMessageConfrimBlock(SharedInfo::CimMessageConfirmReportBuffer[4]);
	for (int i = 4; i < 9; i++)
	{
		memcpy(&SharedInfo::CIMMessage[i], &SharedInfo::CIMMessage[i + 1], sizeof(SharedInfo::CIMMessage[i]));
	}
	memset(&SharedInfo::CIMMessage[9], 0x0, sizeof(SharedInfo::CIMMessage[9]));
	SharedInfo::CIMMessageBufferCnt++;
}


void CVisionAgentECSMainDlg::OnBnClickedAlarmManagementErrorSetBtn()
{
	// TODO: ¿©±â¿¡ ÄÁÆ®·Ñ ¾Ë¸² Ã³¸®±â ÄÚµå¸¦ Ãß°¡ÇÕ´Ï´Ù.
	CString szMsg, szTemp;

	TCHAR *AlarmValue;
	int AlarmCode;
	int AlarmType;

	if (SharedInfo::m_LBLTM.MachineStatus_CIMModeBit == 1)
	{
		AlarmCode = m_ErrorCodeCombo.GetCurSel();
		m_ErrorMessage.GetWindowText(szMsg);
		m_ErrorID.GetWindowTextW(szTemp);
		
		Devs::CimMotion.CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, AlarmCode, ALARM_TYPE_ERROR,104, TRUE, szMsg);
	}

	//strcpy_s((char*)AlarmBlock.AlarmText, 70, AlarmValue);

}

void CVisionAgentECSMainDlg::OnBnClickedAlarmManagementWarningSetBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString szMsg;

	TCHAR *AlarmValue;
	int AlarmCode;
	if (CimInfo::m_LBLTM.MachineStatus_CIMModeBit == 1)
	{
		AlarmCode = m_ErrorCodeCombo.GetCurSel();
		m_ErrorMessage.GetWindowText(szMsg);
		//AlarmCode = _ttoi(szMsg);
		Devs::CimMotion.CIMAlarmMessage(ALARM_STATE_SET, ALARM_UNIT_MACHINE_LEVEL, AlarmCode, ALARM_TYPE_WARNING, 105,TRUE, szMsg);
	}

}
void CVisionAgentECSMainDlg::OnBnClickedAlarmManagementResetBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString szMsg;

	TCHAR *AlarmValue;
	int AlarmID;
	int AlarmType;

	if (CimInfo::m_LBLTM.MachineStatus_CIMModeBit == 1)
	{
		m_ErrorID.GetWindowText(szMsg);
		AlarmID = _ttoi(szMsg);
		Devs::CimMotion.CIMAlarmResetMessage(AlarmID);

	}
}


void CVisionAgentECSMainDlg::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: ¿©±â¿¡ ¸Þ½ÃÁö Ã³¸®±â ÄÚµå¸¦ Ãß°¡ÇÕ´Ï´Ù.

	if (bShow == TRUE)
	{
		InitPara();

		SetTimer(1, 100, NULL);
	}
	else
		KillTimer(1);
}

BOOL CVisionAgentECSMainDlg::InitPara()
{
	m_nPrevMachineState = -1;

	return TRUE;
}

void CVisionAgentECSMainDlg::OnBnClickedUpstreamInlineOnBtn()
{
	Devs::CimMotion.SetUpstreamInlineOnOff(TRUE);

}


void CVisionAgentECSMainDlg::OnBnClickedUpstreamInlineOffBtn()
{
	Devs::CimMotion.SetUpstreamInlineOnOff(FALSE);
}


void CVisionAgentECSMainDlg::OnBnClickedDownstreamInlineOnBtn()
{
	Devs::CimMotion.SetDownstreamInlineOnOff(TRUE);
}


void CVisionAgentECSMainDlg::OnBnClickedDownstreamInlineOffBtn()
{
	Devs::CimMotion.SetDownstreamInlineOnOff(FALSE);
}


void CVisionAgentECSMainDlg::OnBnClickedAutoRecipeOnBtn()
{
	SharedInfo::m_AutoRecipe = TRUE;
	Devs::CimMotion.SetAutoRecipeOnOff(TRUE);
}


void CVisionAgentECSMainDlg::OnBnClickedAutoRecipeOffBtn()
{
	SharedInfo::m_AutoRecipe = FALSE;
	Devs::CimMotion.SetAutoRecipeOnOff(FALSE);
}



void CVisionAgentECSMainDlg::OnBnClickedOperatorCallBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (OperatorCallFlag == FALSE)
	{
		OperatorCallFlag = TRUE;
		m_BtnOperatorCall.SetColor(BLACK, GREEN);
		Devs::MotionIf.DOutputSetBitValue(_DOUT_BUZZER_MELODY_03, TRUE);

	}
	else
	{
		OperatorCallFlag = FALSE;
		m_BtnOperatorCall.SetColor(BLACK, LLTGRAY);
		Devs::MotionIf.DOutputSetBitValue(_DOUT_BUZZER_MELODY_03, FALSE);

	}	
}

void CVisionAgentECSMainDlg::OnBnClickedAutoCassetteVcrOnBtn()
{
	Devs::CimMotion.SetAutoCassetteVcrOnOff(TRUE);
	
	Etc_Msg(_T("[Cim] Send : VCR Mode Change Report(VCR On)"));

}


void CVisionAgentECSMainDlg::OnBnClickedAutoCassetteVcrOffBtn()
{
	Devs::CimMotion.SetAutoCassetteVcrOnOff(FALSE);
	
	Etc_Msg(_T("[Cim] Send : VCR Mode Change Report(VCR Off)"));
}


void CVisionAgentECSMainDlg::OnBnClickedAutoCassetteVcrKeyInBtn()
{
	Devs::CimMotion.SetAutoCassetteVcrKeyInOption(VCR_KEY_IN);

	Etc_Msg(_T("[Cim] Send : VCR Mode Change Report(Key In)"));
}


void CVisionAgentECSMainDlg::OnBnClickedAutoCassetteVcrSkipBtn()
{
	Devs::CimMotion.SetAutoCassetteVcrKeyInOption(VCR_SKIP);

	Etc_Msg(_T("[Cim] Send : VCR Mode Change Report(Skip)"));
}

void CVisionAgentECSMainDlg::OnBnClickedCIMPCCommandReplyBtn(UINT id)
{
	BOOL OnOffFlag;
	switch (id)
	{
	case IDC_MACHINE_MANAGEMENT_CIMPC_COMMAND_REPLY_BTN1:
		CimInfo::m_LBLTM.CIMPCCommandReply_CIMModeChangeCommandSendReply = !CimInfo::m_LBLTM.CIMPCCommandReply_CIMModeChangeCommandSendReply;
		if (CimInfo::m_LBLTM.CIMPCCommandReply_CIMModeChangeCommandSendReply == 0)
			OnOffFlag = FALSE;
		else
			OnOffFlag = TRUE;
		break;
	case IDC_MACHINE_MANAGEMENT_CIMPC_COMMAND_REPLY_BTN2:
		CimInfo::m_LBLTM.CIMPCCommandReply_RecipeRegisterCheckCommandSendReply = !CimInfo::m_LBLTM.CIMPCCommandReply_RecipeRegisterCheckCommandSendReply;
		if (CimInfo::m_LBLTM.CIMPCCommandReply_RecipeRegisterCheckCommandSendReply == 0)
			OnOffFlag = FALSE;
		else
			OnOffFlag = TRUE;
		break;
	case IDC_MACHINE_MANAGEMENT_CIMPC_COMMAND_REPLY_BTN3:
		CimInfo::m_LBLTM.CIMPCCommandReply_RecipeParameterRequestReply = !CimInfo::m_LBLTM.CIMPCCommandReply_RecipeParameterRequestReply;
		if (CimInfo::m_LBLTM.CIMPCCommandReply_RecipeParameterRequestReply == 0)
			OnOffFlag = FALSE;
		else
			OnOffFlag = TRUE;
		break;
	case IDC_MACHINE_MANAGEMENT_CIMPC_COMMAND_REPLY_BTN4:
		CimInfo::m_LBLTM.CIMPCCommandReply_CIMMessageSetCommandSendReply = !CimInfo::m_LBLTM.CIMPCCommandReply_CIMMessageSetCommandSendReply;
		if (CimInfo::m_LBLTM.CIMPCCommandReply_CIMMessageSetCommandSendReply == 0)
			OnOffFlag = FALSE;
		else
			OnOffFlag = TRUE;
		break;
	case IDC_MACHINE_MANAGEMENT_CIMPC_COMMAND_REPLY_BTN5:
		CimInfo::m_LBLTM.CIMPCCommandReply_CIMMessageClearCommandSendReply = !CimInfo::m_LBLTM.CIMPCCommandReply_CIMMessageClearCommandSendReply;
		if (CimInfo::m_LBLTM.CIMPCCommandReply_CIMMessageClearCommandSendReply == 0)
			OnOffFlag = FALSE;
		else
			OnOffFlag = TRUE;
		break;
	case IDC_MACHINE_MANAGEMENT_CIMPC_COMMAND_REPLY_BTN6:
		CimInfo::m_LBLTM.CIMPCCommandReply_DateTimeSetCommandSendReply = !CimInfo::m_LBLTM.CIMPCCommandReply_DateTimeSetCommandSendReply;
		if (CimInfo::m_LBLTM.CIMPCCommandReply_DateTimeSetCommandSendReply == 0)
			OnOffFlag = FALSE;
		else
			OnOffFlag = TRUE;
		break;
	case IDC_MACHINE_MANAGEMENT_CIMPC_COMMAND_REPLY_BTN7:
#if 0
		CimInfo::m_LBLTM.bCIMPCCommandReplyVCRModeChangeCommandReply = !CimInfo::m_LBLTM.bCIMPCCommandReplyVCRModeChangeCommandReply;
		if (CimInfo::m_LBLTM.bCIMPCCommandReplyVCRModeChangeCommandReply == 0)
			OnOffFlag = FALSE;
		else
			OnOffFlag = TRUE;
#endif
		break;
	case IDC_MACHINE_MANAGEMENT_CIMPC_COMMAND_REPLY_BTN8:
#if 0
		CimInfo::m_LBLTM.bCIMPCCommandReplyMaterialGroupDataDownloadReply = !CimInfo::m_LBLTM.bCIMPCCommandReplyMaterialGroupDataDownloadReply;
		if (CimInfo::m_LBLTM.bCIMPCCommandReplyMaterialGroupDataDownloadReply == 0)
			OnOffFlag = FALSE;
		else
			OnOffFlag = TRUE;
#endif
		break;
	}
}



void CVisionAgentECSMainDlg::OnBnClickedMachineEventBtn(UINT id)
{
	BOOL OnOffFlag;
	switch (id)
	{
	case IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN1:
		CimInfo::m_LBLTM.MachineMaskEvent_MaskReceivedJobReport = !CimInfo::m_LBLTM.MachineMaskEvent_MaskReceivedJobReport;
		if (CimInfo::m_LBLTM.MachineMaskEvent_MaskReceivedJobReport == 0)
			OnOffFlag = FALSE;
		else
			OnOffFlag = TRUE;		
		break;
	case IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN2:
		CimInfo::m_LBLTM.MachineMaskEvent_MaskSentOutJobReport_1 = !CimInfo::m_LBLTM.MachineMaskEvent_MaskSentOutJobReport_1;
		if (CimInfo::m_LBLTM.MachineMaskEvent_MaskSentOutJobReport_1 == 0)
			OnOffFlag = FALSE;
		else
			OnOffFlag = TRUE;
		break;
	case IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN3:
		CimInfo::m_LBLTM.MachineMaskEvent_MaskStoredJobReport = !CimInfo::m_LBLTM.MachineMaskEvent_MaskStoredJobReport;
		if (CimInfo::m_LBLTM.MachineMaskEvent_MaskStoredJobReport == 0)
			OnOffFlag = FALSE;
		else
			OnOffFlag = TRUE;
		break;
	case IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN4:
		CimInfo::m_LBLTM.MachineMaskEvent_MaskFetchedOutJobReport = !CimInfo::m_LBLTM.MachineMaskEvent_MaskFetchedOutJobReport;
		if (CimInfo::m_LBLTM.MachineMaskEvent_MaskFetchedOutJobReport == 0)
			OnOffFlag = FALSE;
		else
			OnOffFlag = TRUE;
		break;
	case IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN5:
		CimInfo::m_LBLTM.MachineMaskEvent_MaskProcessStartReport = !CimInfo::m_LBLTM.MachineMaskEvent_MaskProcessStartReport;
		if (CimInfo::m_LBLTM.MachineMaskEvent_MaskProcessStartReport == 0)
			OnOffFlag = FALSE;
		else
			OnOffFlag = TRUE;
		break;
	case IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN6:
		CimInfo::m_LBLTM.MachineMaskEvent_MaskProcessEndReport = !CimInfo::m_LBLTM.MachineMaskEvent_MaskProcessEndReport;
		if (CimInfo::m_LBLTM.MachineMaskEvent_MaskProcessEndReport == 0)
			OnOffFlag = FALSE;
		else
			OnOffFlag = TRUE;
		break;
	case IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN7:
		CimInfo::m_LBLTM.MachineEvent_MachineStatusChangeReport = !CimInfo::m_LBLTM.MachineEvent_MachineStatusChangeReport;
		if (CimInfo::m_LBLTM.MachineEvent_MachineStatusChangeReport == 0)
			OnOffFlag = FALSE;
		else
			OnOffFlag = TRUE;
		break;

	case IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN8:
#if 0
		CimInfo::m_LBLTM.bMachineEventAlarmStateChangeReport = !CimInfo::m_LBLTM.bMachineEventAlarmStateChangeReport;
		if (CimInfo::m_LBLTM.bMachineEventAlarmStateChangeReport == 0)
			OnOffFlag = FALSE;
		else
			OnOffFlag = TRUE;
#endif
		break;
	case IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN9:
		CimInfo::m_LBLTM.MachineMaskEvent_MaskJobDataRequest = !CimInfo::m_LBLTM.MachineMaskEvent_MaskJobDataRequest;
		if (CimInfo::m_LBLTM.MachineMaskEvent_MaskJobDataRequest == 0)
			OnOffFlag = FALSE;
		else
			OnOffFlag = TRUE;
		break;
	case IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN10:
		CimInfo::m_LBLTM.MachineMaskEvent_MaskJobDataChangeReport = !CimInfo::m_LBLTM.MachineMaskEvent_MaskJobDataChangeReport;
		if (CimInfo::m_LBLTM.MachineMaskEvent_MaskJobDataChangeReport == 0)
			OnOffFlag = FALSE;
		else
			OnOffFlag = TRUE;
		break;
	case IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN11:
#if 0
		CimInfo::m_LBLTM.bMachineEventProcessDataReport = !CimInfo::m_LBLTM.bMachineEventProcessDataReport;
		if (CimInfo::m_LBLTM.bMachineEventProcessDataReport == 0)
			OnOffFlag = FALSE;
		else
			OnOffFlag = TRUE;
#endif
		break;
	case IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN12:

		CimInfo::m_LBLTM.MachineEvent_CurrentRecipeNumberChangeReport = !CimInfo::m_LBLTM.MachineEvent_CurrentRecipeNumberChangeReport;
		if (CimInfo::m_LBLTM.MachineEvent_CurrentRecipeNumberChangeReport == 0)
			OnOffFlag = FALSE;
		else
			OnOffFlag = TRUE;
		break;
	case IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN13:
#if 0
		CimInfo::m_LBLTM.bMachineEventRecipeListChangeReport = !CimInfo::m_LBLTM.bMachineEventRecipeListChangeReport;
		if (CimInfo::m_LBLTM.bMachineEventRecipeListChangeReport == 0)
			OnOffFlag = FALSE;
		else
			OnOffFlag = TRUE;
#endif
		break;
	case IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN14:
#if 0
		CimInfo::m_LBLTM.CIMPCCommandReply_para = !CimInfo::m_LBLTM.bMachineEventRecipeParameterDataChangeReport;
		if (CimInfo::m_LBLTM.bMachineEventRecipeParameterDataChangeReport == 0)
			OnOffFlag = FALSE;
		else
			OnOffFlag = TRUE;
#endif
		break;
	case IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN15:
		CimInfo::m_LBLTM.MachineEvent_CIMMessageConfirmReport = !CimInfo::m_LBLTM.MachineEvent_CIMMessageConfirmReport;
		if (CimInfo::m_LBLTM.MachineEvent_CIMMessageConfirmReport == 0)
			OnOffFlag = FALSE;
		else
			OnOffFlag = TRUE;
		break;
	case IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN16:
#if 0
		CimInfo::m_LBLTM.bMachineEventVCREventReport = !CimInfo::m_LBLTM.bMachineEventVCREventReport;
		if (CimInfo::m_LBLTM.bMachineEventVCREventReport == 0)
			OnOffFlag = FALSE;
		else
			OnOffFlag = TRUE;
#endif
		break;
	case IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN17:
#if 0
		CimInfo::m_LBLTM.bMachineEventVCRModeChangeReport = !CimInfo::m_LBLTM.bMachineEventVCRModeChangeReport;
		if (CimInfo::m_LBLTM.bMachineEventVCRModeChangeReport == 0)

			OnOffFlag = FALSE;
		else
			OnOffFlag = TRUE;
#endif
		break;
	case IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN18:
		CimInfo::m_LBLTM.MachineEvent_JobJudgeResultReport = !CimInfo::m_LBLTM.MachineEvent_JobJudgeResultReport;
		if (CimInfo::m_LBLTM.MachineEvent_JobJudgeResultReport == 0)
			OnOffFlag = FALSE;
		else
			OnOffFlag = TRUE;
		break;
	case IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN19:
		CimInfo::m_LBLTM.MachineMaterialEvent_MaterialStatusChangeReport = !CimInfo::m_LBLTM.MachineMaterialEvent_MaterialStatusChangeReport;
		if (CimInfo::m_LBLTM.MachineMaterialEvent_MaterialStatusChangeReport == 0)
			OnOffFlag = FALSE;
		else
			OnOffFlag = TRUE;
		break;
	case IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN20:
		CimInfo::m_LBLTM.MachineMaterialEvent_MaterialCountChangeReport = !CimInfo::m_LBLTM.MachineMaterialEvent_MaterialCountChangeReport;
		if (CimInfo::m_LBLTM.MachineMaterialEvent_MaterialCountChangeReport == 0)
			OnOffFlag = FALSE;
		else
			OnOffFlag = TRUE;
		break;
	case IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN21:
		CimInfo::m_LBLTM.MachineMaterialEvent_SheetMoveInReport = !CimInfo::m_LBLTM.MachineMaterialEvent_SheetMoveInReport;
		if (CimInfo::m_LBLTM.MachineMaterialEvent_SheetMoveInReport == 0)
			OnOffFlag = FALSE;
		else
			OnOffFlag = TRUE;
		break;
	case IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN22:
		CimInfo::m_LBLTM.MachineMaterialEvent_SheetMoveOutReport = !CimInfo::m_LBLTM.MachineMaterialEvent_SheetMoveOutReport;
		if (CimInfo::m_LBLTM.MachineMaterialEvent_SheetMoveOutReport == 0)
			OnOffFlag = FALSE;
		else
			OnOffFlag = TRUE;
		break;
	case IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN23:
		CimInfo::m_LBLTM.MachineMaterialEvent_MaterialSheetDataUpdateReport = !CimInfo::m_LBLTM.MachineMaterialEvent_MaterialSheetDataUpdateReport;
		if (CimInfo::m_LBLTM.MachineMaterialEvent_MaterialSheetDataUpdateReport == 0)
			OnOffFlag = FALSE;
		else
			OnOffFlag = TRUE;
		break;
	case IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN24:
		CimInfo::m_LBLTM.MachineMaterialEvent_MaterialSheetDataDownloadRequest = !CimInfo::m_LBLTM.MachineMaterialEvent_MaterialSheetDataDownloadRequest;
		if (CimInfo::m_LBLTM.MachineMaterialEvent_MaterialSheetDataDownloadRequest == 0)
			OnOffFlag = FALSE;
		else
			OnOffFlag = TRUE;
		break;
	case IDC_MACHINE_MANAGEMENT_MACHINE_EVENT_BTN25:
#if 0
		CimInfo::m_LBLTM.bMachineEventSheetDataRemovedReport = !CimInfo::m_LBLTM.bMachineEventSheetDataRemovedReport;
		if (CimInfo::m_LBLTM.bMachineEventSheetDataRemovedReport == 0)
			OnOffFlag = FALSE;
		else
			OnOffFlag = TRUE;
#endif
		break;
	}

	if (OnOffFlag)
	{
		Devs::CimMotion.SetT1TimeOut();
	}

	Devs::CimMotion.SetLbLtmSelectedEventRun();
}

void CVisionAgentECSMainDlg::OnBnClickedBtnModuleWindowOpen()
{
	DATE_TIME_REQUEST_BLOCK DateTimeRequestBlock;
	DateTimeRequestBlock.TouchPanelNumber = 1;
	Devs::CimMotion.RequestDateTime(DateTimeRequestBlock);
}



void CVisionAgentECSMainDlg::OnBnClickedBtnJobPlus()
{
	// TODO: Add your control notification handler code here
	SharedInfo::m_ProductJobCount++;
}


void CVisionAgentECSMainDlg::OnBnClickedBtnJobMinus()
{
	// TODO: Add your control notification handler code here
	SharedInfo::m_ProductJobCount--;
	if ((int)(SharedInfo::m_ProductJobCount) < 0)
		SharedInfo::m_ProductJobCount = 0;
}


void CVisionAgentECSMainDlg::OnBnClickedMachineManagementIdleBtn2()
{
	// TODO: Add your control notification handler code here
	MACHINE_MODE_CHANGE_REPORT_BLOCK MachinMode;

	SharedInfo::MachinMode = 1;
	MachinMode.MachineMode = SharedInfo::MachinMode;
	Devs::CimMotion.ReportMachineModeChange(MachinMode);
}


void CVisionAgentECSMainDlg::OnBnClickedMachineManagementIdleBtn3()
{
	// TODO: Add your control notification handler code here
	MACHINE_MODE_CHANGE_REPORT_BLOCK MachinMode;
	SharedInfo::MachinMode = 5;
	MachinMode.MachineMode = SharedInfo::MachinMode;
	Devs::CimMotion.ReportMachineModeChange(MachinMode);
}
